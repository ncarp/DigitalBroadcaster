// Music.cpp : implementation file
//

#include "stdafx.h"
#include "Discography.h"
#include "Music.h"
#include "..\include\RSCategories.h"
#include "..\include\RSExpressions.h"
#include "..\include\RSRecordLabel.h"
#include "..\include\RSArtists.h"
#include "..\onair\RSRecord.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusic dialog

extern CString	g_strMainConnect;

CMusic::CMusic(CWnd* pParent /*=NULL*/)
	: CDialog(CMusic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMusic)
	m_strArtist = _T("");
	m_strTitle = _T("");
	m_strType = _T("");
	m_strExpression = _T("");
	m_Rythm = 0;
	m_strCD = _T("");
	m_strComposer = _T("");
	m_dDate = COleDateTime::GetCurrentTime();
	m_strLabel = _T("");
	m_strLirycs = _T("");
	m_strMusicians = _T("");
	m_strProducer = _T("");
	m_strRemarcks = _T("");
	m_strStudio = _T("");
	//}}AFX_DATA_INIT
	m_bIsNew = TRUE;
	m_CategoryID = 0;
	m_ExpressionID = 0;
	m_ArtistID = 0;
	m_CDID = 0;
	m_LabelID = 0;
}

CMusic::~CMusic()
{
//	m_pTimers->OnStop();
	delete m_pTimers;
}

void CMusic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMusic)
	DDX_Control(pDX, IDC_LABEL, m_cLabel);
	DDX_Control(pDX, IDC_CD, m_cCD);
	DDX_Control(pDX, IDC_RYTHMV, m_cRythmV);
	DDX_Control(pDX, IDC_RYTHM, m_cRythm);
	DDX_Control(pDX, IDC_EXPRESSION, m_cExpression);
	DDX_Control(pDX, IDC_TYPE, m_cType);
	DDX_Control(pDX, IDC_TITLE, m_cTitle);
	DDX_Control(pDX, IDC_ARTIST, m_cArtist);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDOK, m_cOK);
	DDX_CBString(pDX, IDC_ARTIST, m_strArtist);
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	DDX_CBString(pDX, IDC_TYPE, m_strType);
	DDX_CBString(pDX, IDC_EXPRESSION, m_strExpression);
	DDX_Slider(pDX, IDC_RYTHM, m_Rythm);
	DDX_CBString(pDX, IDC_CD, m_strCD);
	DDX_Text(pDX, IDC_COMPOSER, m_strComposer);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_dDate);
	DDX_CBString(pDX, IDC_LABEL, m_strLabel);
	DDX_Text(pDX, IDC_LYRICS, m_strLirycs);
	DDX_Text(pDX, IDC_MUSICIANS, m_strMusicians);
	DDX_Text(pDX, IDC_PRODUCER, m_strProducer);
	DDX_Text(pDX, IDC_REMARKS, m_strRemarcks);
	DDX_Text(pDX, IDC_STUDIO, m_strStudio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMusic, CDialog)
	//{{AFX_MSG_MAP(CMusic)
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	ON_CBN_KILLFOCUS(IDC_TYPE, OnKillfocusType)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	ON_CBN_KILLFOCUS(IDC_EXPRESSION, OnKillfocusExpression)
	ON_CBN_SELCHANGE(IDC_EXPRESSION, OnSelchangeExpression)
	ON_WM_HSCROLL()
	ON_CBN_KILLFOCUS(IDC_CD, OnKillfocusCd)
	ON_CBN_SELCHANGE(IDC_CD, OnSelchangeCd)
	ON_CBN_KILLFOCUS(IDC_LABEL, OnKillfocusLabel)
	ON_CBN_SELCHANGE(IDC_LABEL, OnSelchangeLabel)
	ON_CBN_SELCHANGE(IDC_ARTIST, OnSelchangeArtist)
	ON_CBN_KILLFOCUS(IDC_ARTIST, OnKillfocusArtist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusic message handlers

int CMusic::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect crect;
	GetClientRect(&crect);
	crect.DeflateRect(10,475,10,-40);

	m_pTimers = new CRecorder();
	m_pTimers->Create(NULL,WS_VISIBLE|WS_BORDER,crect,this);
	
	m_nPos=0;
	SetScrollRange(SB_VERT,0,100);

	return 0;
}

BOOL CMusic::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect crect;
	GetClientRect(&crect);
	
	m_cCancel.MoveWindow(CRect(crect.right-200,crect.bottom+50,crect.right-110,crect.bottom+75));	
	m_cOK.MoveWindow(CRect(crect.right-100,crect.bottom+50,crect.right-10,crect.bottom+75));

	int y=GetSystemMetrics(SM_CYSCREEN);
	if( y>768)
	{
		CRect rect;
		GetWindowRect(&rect);
		rect.InflateRect(0,0,0,100);
		MoveWindow(rect);
		SetScrollRange(SB_VERT,0,0);
	}
	////////////////////////////////////////////////////////////////////////////////////////

	CString str,
			strTemp;
	int		nPos;

	str.LoadString(IDS_REFRESH);

	m_cArtist.AddString(str);
	m_cArtist.SetItemData(0,0);

	strTemp=m_strType;
	strTemp.TrimRight();
	m_cType.AddString(str);
	m_cType.SetItemData(0,0);
	m_cType.SetCurSel(0);
	OnSelchangeType();
	nPos=m_cType.FindStringExact(-1,strTemp);
	m_cType.SetCurSel(nPos);
	if( nPos!=CB_ERR )
		OnSelchangeType();

	strTemp=m_strExpression;
	strTemp.TrimRight();
	m_cExpression.AddString(str);
	m_cExpression.SetItemData(0,0);
	m_cExpression.SetCurSel(0);
	OnSelchangeExpression();
	nPos=m_cExpression.FindStringExact(-1,strTemp);
	m_cExpression.SetCurSel(nPos);
	if( nPos!=CB_ERR )
		OnSelchangeExpression();

	m_cRythm.SetRange(0,250,TRUE);
	m_cRythm.SetPos(m_Rythm);

	m_cCD.AddString(str);
	m_cCD.SetItemData(0,0);

	m_cLabel.AddString(str);
	m_cLabel.SetItemData(0,0);

	str.Format("%d bpm",m_Rythm);
	m_cRythmV.SetWindowText(str);

	m_pTimers->SetFile(m_strFileName);


	if( m_bIsNew )
	{
		m_cTitle.EnableWindow(FALSE);
		m_cArtist.EnableWindow(FALSE);

		CString strTemp = m_strArtist;
		strTemp.Replace("'","''");

		CRSArtists rsArtist( g_strMainConnect,NULL );
		rsArtist.m_strFilter.Format("Name = '%s'",strTemp);
		rsArtist.Open();

		if( rsArtist.GetRecordCount() )
			m_ArtistID = rsArtist.m_ID;
		else
		{
			rsArtist.AddNew();
			rsArtist.m_Activ=1;
			rsArtist.m_Name=m_strArtist;
			rsArtist.Update();
			rsArtist.Requery();
			m_ArtistID = rsArtist.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_ARTIST,rsArtist.m_ID);
		}
	}
	else
	{
		m_pTimers->m_pTimer->m_Start	= m_Start;
		m_pTimers->m_pTimer->m_FadeIn	= m_FadeIn;
		m_pTimers->m_pTimer->m_Intro	= m_Intro;
		m_pTimers->m_pTimer->m_FadeOut	= m_FadeOut;
		m_pTimers->m_pTimer->m_Mix		= m_Mix;
		m_pTimers->m_pTimer->m_End		= m_End;
		m_pTimers->m_pTimer->m_LoopA	= m_LoopA;
		m_pTimers->m_pTimer->m_LoopB	= m_LoopB;
		m_pTimers->OnUpdateTimers(0,0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMusic::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch( nSBCode )
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK: 
		SetScrollPos(SB_VERT,nPos);
		ScrollWindow(0,m_nPos-nPos);
		m_nPos=nPos;
		break;
	}
}

void CMusic::OnKillfocusType() 
{
	CString str;
	m_cType.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_CategoryID=0;
		return;	
	}

	CRSCategories	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cType.SetWindowText(rs.m_Name);
		m_CategoryID=rs.m_ID;

		if( rs.m_Activ==0 )
		{
			rs.Edit();
			rs.m_Activ=1;
			rs.Update();
		}
	}
	else
	{
		if( AfxMessageBox(IDS_NEWCATEGORY,MB_YESNO)==IDYES )
		{
			m_cType.GetWindowText(str);
			str.TrimRight();
			str.MakeUpper();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_CategoryID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_MUSICCATEGORIE,m_CategoryID);
		}
		else
		{
			m_cType.SetWindowText("");
			m_CategoryID=0;
		}
	}
}

void CMusic::OnSelchangeType() 
{
	int Pos = m_cType.GetCurSel();
	if( Pos==CB_ERR )
	{
		m_CategoryID=0;
		return;
	}

	long lID = m_cType.GetItemData(Pos);
	if( lID == 0 )
	{
		CRSCategories	rs(g_strMainConnect);
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
		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_cType.AddString(str);
		m_cType.SetItemData(Pos,0);
		m_CategoryID=0;
	}
	else
		m_CategoryID = lID;
}

void CMusic::OnKillfocusExpression() 
{
	CString str;
	m_cExpression.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_ExpressionID=0;
		return;	
	}

	CRSExpressions	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cExpression.SetWindowText(rs.m_Name);
		m_ExpressionID=rs.m_ID;

		if( rs.m_Activ==0 )
		{
			rs.Edit();
			rs.m_Activ=1;
			rs.Update();
		}
	}
	else
	{
		if( AfxMessageBox(IDS_NEWEXPRESSION,MB_YESNO)==IDYES )
		{
			m_cExpression.GetWindowText(str);
			str.TrimRight();
			str.MakeUpper();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_ExpressionID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_EXPRESSION,m_ExpressionID);
		}
		else
		{
			m_cExpression.SetWindowText("");
			m_ExpressionID=0;
		}
	}
}

void CMusic::OnSelchangeExpression() 
{
	long Pos=m_cExpression.GetCurSel();
	long Data=m_cExpression.GetItemData(Pos);

	m_ExpressionID=Data;

	if( Data==0 )
	{
		CRSExpressions	rs(g_strMainConnect);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Name";
		rs.Open();

		m_cExpression.ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_cExpression.AddString(rs.m_Name);
			m_cExpression.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}
		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_cExpression.AddString(str);
		m_cExpression.SetItemData(Pos,0);
	}	
}

void CMusic::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Rythm=m_cRythm.GetPos();

	CString str;
	str.Format("%d bpm",m_Rythm);

	m_cRythmV.SetWindowText(str);		
}

void CMusic::OnKillfocusCd() 
{
	CString str;
	m_cCD.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_CDID=0;
		return;	
	}

	CRSRecord	rs(g_strMainConnect);
	rs.m_strFilter.Format("Title = '%s' AND ArtistID='%d'",str,m_ArtistID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Title.TrimRight();
		m_cCD.SetWindowText(rs.m_Title);
		m_CDID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWRECORD,MB_YESNO)==IDYES )
		{
			m_cCD.GetWindowText(str);
			str.TrimRight();

			rs.AddNew();
			rs.m_ArtistID=m_ArtistID;
			rs.m_Title=str;
			rs.Update();

			rs.Requery();
			m_CDID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_RECORD,m_CDID);
		}
		else
		{
			m_cCD.SetWindowText("");
			m_CDID=0;
		}
	}	
}

void CMusic::OnSelchangeCd() 
{
	long Pos=m_cCD.GetCurSel();
	long Data=m_cCD.GetItemData(Pos);

	m_CDID=Data;

	if( Data==0 )
	{
		CRSRecord	rs(g_strMainConnect);
		rs.m_strFilter.Format("ArtistID = '0' OR ArtistID = '%d'",m_ArtistID);
		rs.m_strSort="Title";
		rs.Open();

		m_cCD.ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Title.TrimRight();
			Pos=m_cCD.AddString(rs.m_Title);
			m_cCD.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}

		CString str;
		str.LoadString(IDS_REFRESH);

		Pos=m_cCD.AddString("* "+str);
		m_cCD.SetItemData(Pos,0);
	}
}

void CMusic::OnKillfocusLabel() 
{
	CString str;
	m_cLabel.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_LabelID=0;
		return;	
	}

	CRSRecordLabel	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cLabel.SetWindowText(rs.m_Name);
		m_LabelID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWLABEL,MB_YESNO)==IDYES )
		{
			m_cLabel.GetWindowText(str);
			str.TrimRight();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_LabelID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_RECORDLABEL,m_LabelID);
		}
		else
		{
			m_cLabel.SetWindowText("");
			m_LabelID=0;
		}
	}
}

void CMusic::OnSelchangeLabel() 
{
	long Pos=m_cLabel.GetCurSel();
	long Data=m_cLabel.GetItemData(Pos);

	m_LabelID=Data;

	if( Data==0 )
	{
		CRSRecordLabel	rs(g_strMainConnect);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Name";
		rs.Open();

		m_cLabel.ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_cLabel.AddString(rs.m_Name);
			m_cLabel.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}

		CString str;
		str.LoadString(IDS_REFRESH);

		Pos=m_cLabel.AddString(str);
		m_cLabel.SetItemData(Pos,0);
	}
}

void CMusic::OnOK() 
{
	if( m_ArtistID == 0)
		return;

	m_strTitle.TrimRight();
	if( m_strTitle.GetLength()==0 )
		return;

	if( m_CategoryID == 0 )
		return;

	if( m_ExpressionID == 0 )
		return;
	
	m_Start		= m_pTimers->m_pTimer->m_Start;
	m_FadeIn	= m_pTimers->m_pTimer->m_FadeIn;
	m_Intro		= m_pTimers->m_pTimer->m_Intro;
	m_FadeOut	= m_pTimers->m_pTimer->m_FadeOut;
	m_Mix		= m_pTimers->m_pTimer->m_Mix;
	m_End		= m_pTimers->m_pTimer->m_End;
	m_LoopA		= m_pTimers->m_pTimer->m_LoopA;
	m_LoopB		= m_pTimers->m_pTimer->m_LoopB;

	CDialog::OnOK();
}

void CMusic::OnSelchangeArtist() 
{
	long Pos=m_cArtist.GetCurSel();
	long Data=m_cArtist.GetItemData(Pos);

	m_ArtistID=Data;

	if( Data==0 )
	{
		CRSArtists	rs(g_strMainConnect,NULL);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Name";
		rs.Open();

		m_cArtist.ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_cArtist.AddString(rs.m_Name);
			m_cArtist.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}

		CString str;
		str.LoadString(IDS_REFRESH);

		Pos=m_cArtist.AddString(str);
		m_cArtist.SetItemData(Pos,0);
	}
}

void CMusic::OnKillfocusArtist() 
{
	CString str;
	m_cArtist.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_ArtistID=0;
		return;	
	}

	CRSArtists rs(g_strMainConnect,NULL);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cArtist.SetWindowText(rs.m_Name);
		m_ArtistID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWARTIST,MB_YESNO)==IDYES )
		{
			m_cArtist.GetWindowText(str);
			str.TrimRight();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_ArtistID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_ARTIST,m_ArtistID);
		}
		else
		{
			m_cArtist.SetWindowText("");
			m_ArtistID=0;
		}
	}	
}
