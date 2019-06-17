// RMs.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "RMs.h"
#include "..\include\RSPath.h"
#include "..\include\RSViewRMFiles.h"
#include "..\include\RSTypeOfRM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CString	g_strMainConnect;

/////////////////////////////////////////////////////////////////////////////
// CRMs dialog


CRMs::CRMs(CWnd* pParent /*=NULL*/)
	: CDialog(CRMs::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRMs)
	m_KeyWords = _T("");
	m_Date = COleDateTime::GetCurrentTime();
	m_Name = _T("");
	m_Type = _T("");
	m_Obs = _T("");
	//}}AFX_DATA_INIT
	m_IsNew = TRUE;
}

CRMs::~CRMs()
{
	delete m_pTimers;
}

void CRMs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRMs)
	DDX_Control(pDX, IDC_RM_TYPE, m_cType);
	DDX_Control(pDX, IDC_RM_PATH, m_cPath);
	DDX_Control(pDX, IDC_RM_FILENAME, m_cFileName);
	DDX_Text(pDX, IDC_RM_KEYWORDS, m_KeyWords);
	DDX_DateTimeCtrl(pDX, IDC_RM_DATE, m_Date);
	DDX_Text(pDX, IDC_RM_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 100);
	DDX_CBString(pDX, IDC_RM_TYPE, m_Type);
	DDV_MaxChars(pDX, m_Type, 100);
	DDX_Text(pDX, IDC_RM_OBS, m_Obs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRMs, CDialog)
	//{{AFX_MSG_MAP(CRMs)
	ON_CBN_SELCHANGE(IDC_RM_TYPE, OnSelchangeRmType)
	ON_CBN_KILLFOCUS(IDC_RM_TYPE, OnKillfocusRmType)
	ON_CBN_KILLFOCUS(IDC_RM_PATH, OnKillfocusRmPath)
	ON_CBN_KILLFOCUS(IDC_RM_FILENAME, OnKillfocusRmFilename)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMs message handlers

void CRMs::OnSelchangeRmType() 
{
	int Pos=m_cType.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cType.GetItemData(Pos);
	if( lData==0 )
	{
		CRSTypeOfRM rs(g_strMainConnect);
		rs.m_strFilter="Activ = 1";
		rs.m_strSort="Name";
		rs.Open();

		m_cType.ResetContent();

		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_cType.AddString(rs.m_Name);
			m_cType.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}
		rs.Close();

		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_cType.AddString(str);
		m_cType.SetItemData(Pos,0);
	}
}

void CRMs::OnKillfocusRmType() 
{
	CString str;
	m_cType.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
	{
		m_TypeID=0;
		return;
	}
	

	CRSTypeOfRM	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cType.SetWindowText(rs.m_Name);
		m_TypeID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWTYPEOFRM,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cType.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_TypeID=rs.m_ID;
		}
		else
		{
			m_cType.SetWindowText("");
			m_TypeID=0;
		}
	}
	rs.Close();	
}

void CRMs::OnKillfocusRmPath() 
{
	int Pos=m_cPath.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long	lID=m_cPath.GetItemData(Pos);
	CString	strTemp;

	if( lID!=m_PathID )
	{
		m_PathID=lID;
		m_cPath.GetLBText(Pos,m_Path);
		
		CFileFind	finder;
		BOOL		bWorking;

		m_cFileName.ResetContent();

		bWorking=finder.FindFile(m_Path+"\\*.*");

		while( bWorking )
		{
			bWorking=finder.FindNextFile();
	
			strTemp = finder.GetFileName();
			strTemp.MakeLower();
			if( (strTemp.Find(".mp3",0)==strTemp.GetLength()-4) || (strTemp.Find(".wav",0)==strTemp.GetLength()-4) )
				Pos=m_cFileName.AddString(finder.GetFileName());
		}

	}	
}

void CRMs::OnKillfocusRmFilename() 
{
/*	int Pos=m_cFileName.GetCurSel();
	if( Pos==CB_ERR )
		return; */

	CString strFullFileName,
			strFileName;
	
	m_cFileName.GetWindowText(strFileName);

	if( strFileName!=m_FileName)
	{
		m_FileName=strFileName;
		strFullFileName=m_Path+"\\"+m_FileName;

		m_pTimers->m_pTimer->DeleteBM();
		m_pTimers->SetFile(strFullFileName);	
		m_pTimers->m_pTimer->m_FadeOut=0;
		m_pTimers->m_pTimer->m_Mix=m_pTimers->m_pTimer->m_End-500;
		m_pTimers->m_pTimer->PaintTimerBM();
		m_pTimers->OnUpdateTimers(0,0);
	}
}

int CRMs::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect crect;
	GetClientRect(&crect);
	crect.DeflateRect(10,255,10,40);

	m_pTimers = new CRecorder();
	m_pTimers->m_bCanRec = TRUE;
	m_pTimers->Create(NULL,WS_VISIBLE|WS_BORDER,crect,this);

	return 0;
}

BOOL CRMs::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString str;
	long	Pos;

	str.LoadString(IDS_REFRESH);

	m_cType.AddString(str);
	m_cType.SetItemData(0,0);

	CRSPath	rs(g_strMainConnect);
	rs.m_strFilter = "RMs = 1";
	rs.m_strSort = "Path";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Path.TrimRight();
		Pos=m_cPath.AddString(rs.m_Path);
		m_cPath.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	rs.Close();
	
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_FADEIN,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_INTRO,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_FADEOUT,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPA,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPB,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pLoopCheck->EnableWindow(FALSE);
	m_pTimers->m_pRec->SetImageList(50,50,0,1);
	m_pTimers->m_pRec->AddImage(IDB_RECOFF);
	
	if( !m_IsNew )
	{
		long Pos = m_cPath.FindStringExact(-1,m_Path);
		m_cPath.SetCurSel(Pos);
		
		CFileFind	finder;
		BOOL		bWorking;
		CString		str;

		CRSViewRMFiles	rs(g_strMainConnect);

		rs.m_strFilter="FileName = 'zz'";
		rs.Open();

		m_cFileName.ResetContent();

		bWorking=finder.FindFile(m_Path+"\\*.wav");

		while( bWorking )
		{
			bWorking=finder.FindNextFile();

			str=finder.GetFilePath();
			str.Replace("'","''");
			rs.m_strFilter.Format("FileName = '%s'",str);
			rs.Requery();

			if( rs.GetRecordCount()==0 )
			{
				Pos=m_cFileName.AddString(finder.GetFileName());
			}
		}

		rs.Close();

		Pos=m_cFileName.AddString(m_FileName);
		m_cFileName.SetCurSel(Pos);

		m_pTimers->SetFile(m_Path+"\\"+m_FileName);
		m_pTimers->m_pTimer->m_End=m_End;
		m_pTimers->m_pTimer->m_Mix=m_Mix;
		m_pTimers->m_pTimer->m_Start=m_Start;
		m_pTimers->m_pTimer->m_FadeOut=0;
		m_pTimers->OnUpdateTimers(0,0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRMs::OnOK() 
{
	UpdateData();

	if( m_TypeID==0 )
		return;

	m_Name.TrimRight();
	if( m_Name.GetLength()==0 )
		return;

	
	CDialog::OnOK();
}
