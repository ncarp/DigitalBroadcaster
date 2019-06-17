// ErcCreateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "ErcCreateDlg.h"
#include "rsviewerc.h"
#include "..\include\rsradiostations.h"
#include "..\XM8dist\include\xm8calls.h"


// CErcCreateDlg dialog

IMPLEMENT_DYNAMIC(CErcCreateDlg, CDialog)

CErcCreateDlg::CErcCreateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CErcCreateDlg::IDD, pParent)
{

}

CErcCreateDlg::~CErcCreateDlg()
{
}

void CErcCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDOK, m_cOK);
}


BEGIN_MESSAGE_MAP(CErcCreateDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CErcCreateDlg message handlers

BOOL CErcCreateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cList.EnableWindow(FALSE);
	m_cList.InsertColumn(0,"Data",LVCFMT_CENTER,150);
	m_cList.InsertColumn(1,"Total",LVCFMT_CENTER,50);
	m_cList.InsertColumn(2,"pt",LVCFMT_CENTER,50);
	m_cList.InsertColumn(3,"pt-PT",LVCFMT_CENTER,50);
	m_cList.InsertColumn(4,"Novas",LVCFMT_CENTER,50);
	
	m_cOK.EnableWindow(FALSE);

	SetTimer(1001,1000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CErcCreateDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(1001);

	CRSRadioStations rsRadio("Broadcaster");
	rsRadio.m_strFilter.Format("ID = '%d'",m_lRadioID);
	rsRadio.Open();
	if( rsRadio.GetRecordCount()==0 )
	{
		AfxMessageBox("A rádio não foi encontrada no sistema!");
		rsRadio.Close();
		OnOK();
		return;
	}
	
	CString strConnection = rsRadio.m_DSN.TrimRight();
	CDatabase db;;
	db.Open(strConnection);

	CString strFile,
			strTemp,
			strRadio="Teste",
			strTime,
			strDuration,
			strDate,
			strYear,
			strPort;
	CStringW strw;
	int		nPos=0,
			nMusicTotal=0,
			nPortTotal=0,
			nPortEUTotal=0,
			nPortNewTotal=0;
	int		nMusicDay,
			nPortDay,
			nPortEUDay,
			nPortNewDay;
	CString strTxt;
	MSG		msg;
	COleDateTimeSpan oneYear(365,0,0,0);

	CRSViewERC rs(&db);
	COleDateTime Start(m_DateStart.GetYear(),
						m_DateStart.GetMonth(),
						m_DateStart.GetDay(),
						0,0,0);
	COleDateTime End=Start+COleDateTimeSpan(1,0,0,0);
	
	rs.m_strFilter.Format("AirDate>='%d-%d-%d' and AirDate<'%d-%d-%d'",
		Start.GetYear(),Start.GetMonth(),Start.GetDay(),
		End.GetYear(),End.GetMonth(),End.GetDay() );
	rs.m_strSort="AirDate";
	rs.Open();

	rsRadio.m_Adress.TrimRight();

	while(Start<=m_DateFinish)
	{	
		strDate.Format("%d-%2d-%2d",Start.GetYear(),Start.GetMonth(),Start.GetDay());
		strDate.Replace(" ","0");
		strFile.Format("%s\\ERCRATIOS-%s-%s.xml",m_strFolder,rsRadio.m_Adress,strDate);

		XM8_newFile("ERCRATIO");
		XM8_newGroup("ALIAS");
		XM8_putGroup("ALIAS",rsRadio.m_Adress.GetBuffer());
		XM8_newGroup("PLAYLIST");
		XM8_getFrstGroup("PLAYLIST",1);
		XM8_newGroup("DATE");
		XM8_putGroup("DATE",strDate.GetBuffer());

		nMusicDay=0;
		nPortDay=0;
		nPortEUDay=0;
		nPortNewDay=0;

		m_cList.InsertItem(nPos,strDate);
		
		if( rs.GetRecordCount()!=0 )
		{
			rs.MoveFirst();
			while(!rs.IsEOF())
			{
				nMusicDay++;

				strTime.Format("%2d:%2d:%2d",rs.m_AirDate.GetHour(),rs.m_AirDate.GetMinute(),rs.m_AirDate.GetSecond());
				strTime.Replace(" ","0");
				strDuration.Format("%d",rs.m_Length);
				rs.m_Artist.TrimRight(); 
				rs.m_Title.TrimRight(); 
				rs.m_Category.TrimRight();
				strYear.Format("%4d-%2d-%2d",rs.m_RecordingDate.GetYear(),rs.m_RecordingDate.GetMonth(),rs.m_RecordingDate.GetDay());
				strYear.Replace(" ","0");

				if( (rs.m_LangCode.Find("pt")==0) || (rs.m_NatCode=="pt") )
				{
					nPortTotal++;
					nPortDay++;
					strPort="1";

					if( (rs.m_AirDate-oneYear)<=rs.m_RecordingDate )
					{
						nPortNewDay++;
						nPortNewTotal++;
					}

					if( (rs.m_LangCode.Find("pt")==0) && (rs.m_EU==1) )
					{
						nPortEUTotal++;
						nPortEUDay++;
					}
				}
				else
					strPort="0";
				
				strw=rs.m_Title;

				XM8_newGroup("SONG");
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("TIME",CleanString(strTime).GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("DURATION",strDuration.GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("ARTIST",CleanString(rs.m_Artist).Trim().GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("MUSICTRACK",CleanString(rs.m_Title).GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("NATIONALITY",rs.m_NatCode.GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("EXPRESSION",rs.m_LangCode.GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("YEAR",strYear.GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("PORTUGUESEM",strPort.GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGrpPutVal("GENRE",CleanString(rs.m_Category).GetBuffer());
				XM8_getLastGroup("SONG",2);
				XM8_newGroup("ISRC");
				XM8_getLastGroup("SONG",2);
		
				rs.MoveNext();
				XM8_getLastGroup("PLAYLIST",1);

				strTxt.Format("%d",nMusicDay);
				m_cList.SetItemText(nPos,1,strTxt);

				strTxt.Format("%d",nPortDay);
				m_cList.SetItemText(nPos,2,strTxt);

				strTxt.Format("%d",nPortEUDay);
				m_cList.SetItemText(nPos,3,strTxt);

				strTxt.Format("%d",nPortNewDay);
				m_cList.SetItemText(nPos,4,strTxt);

				while (PeekMessage(&msg,m_hWnd,0,0,PM_REMOVE)) 
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
		
		nPos++;

		XM8_writeFile(strFile.GetBuffer());
		XM8_reset();

		Start = Start+COleDateTimeSpan(1,0,0,0);
		End = Start+COleDateTimeSpan(1,0,0,0);
		rs.m_strFilter.Format("AirDate>='%d-%d-%d' and AirDate<'%d-%d-%d'",
						Start.GetYear(),Start.GetMonth(),Start.GetDay(),
						End.GetYear(),End.GetMonth(),End.GetDay() );
		rs.Requery();
	}

	m_cOK.EnableWindow(TRUE);
}

CString CErcCreateDlg::CleanString( CString strIn)
{
	CString str=strIn;

	str.MakeUpper();
	str.TrimRight();
	// A
	str.Replace("Á","A");
	str.Replace("À","A");
	str.Replace("Ã","A");
	str.Replace("Â","A");
	// E
	str.Replace("É","E");
	str.Replace("È","E");
	str.Replace("Ê","E");
	// I
	str.Replace("Í","I");
	str.Replace("Ì","I");
	str.Replace("Î","I");
	// O
	str.Replace("Ó","O");
	str.Replace("Ò","O");
	str.Replace("Õ","O");
	str.Replace("Ô","O");
	// U
	str.Replace("Ú","U");
	str.Replace("Ù","U");
	str.Replace("Û","U");
	// Ç
	str.Replace("Ç","C");
	// '
	str.Replace("´","'");
	str.Replace("`","'");

	return str;
}
