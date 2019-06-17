// Jingles.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "Jingles.h"
#include "..\include\RSPath.h"
#include "..\include\RSViewJingleFiles.h"
#include "..\include\RSTypeOfJingle.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_strMainConnect;

/////////////////////////////////////////////////////////////////////////////
// CJingles dialog


CJingles::CJingles(CWnd* pParent /*=NULL*/)
	: CDialog(CJingles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJingles)
	m_Name = _T("");
	m_Rythm = 0;
	m_RythmV = _T("");
	m_Type = _T("");
	//}}AFX_DATA_INIT
	m_IsNew = TRUE;
	m_Rythm = 0;
}

CJingles::~CJingles()
{
	delete m_pTimers;
}

void CJingles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJingles)
	DDX_Control(pDX, IDC_RYTHM_V, m_cRythmV);
	DDX_Control(pDX, IDC_RYTHM, m_cRythm);
	DDX_Control(pDX, IDC_TYPE, m_cType);
	DDX_Control(pDX, IDC_PATH, m_cPath);
	DDX_Control(pDX, IDC_FILE, m_cFile);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Slider(pDX, IDC_RYTHM, m_Rythm);
	DDX_Text(pDX, IDC_RYTHM_V, m_RythmV);
	DDX_CBString(pDX, IDC_TYPE, m_Type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJingles, CDialog)
	//{{AFX_MSG_MAP(CJingles)
	ON_WM_CREATE()
	ON_CBN_KILLFOCUS(IDC_PATH, OnKillfocusPath)
	ON_CBN_SELCHANGE(IDC_PATH, OnSelchangePath)
	ON_WM_HSCROLL()
	ON_CBN_KILLFOCUS(IDC_FILE, OnKillfocusFile)
	ON_CBN_KILLFOCUS(IDC_TYPE, OnKillfocusType)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJingles message handlers

BOOL CJingles::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	long	Pos;

	str.LoadString(IDS_REFRESH);

	m_cType.AddString(str);
	m_cType.SetItemData(0,0);

	CRSPath	rs(g_strMainConnect);
	rs.m_strFilter = "Jingles = 1";
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
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_FADEOUT,MF_BYCOMMAND|MF_GRAYED);
	
	m_pTimers->m_pRec->SetImageList(50,50,0,1);
	m_pTimers->m_pRec->AddImage(IDB_RECOFF);
	
	m_cRythm.SetRange(0,250);
	m_cRythm.SetPos(m_Rythm);

	if( !m_IsNew )
	{
		long Pos = m_cPath.FindStringExact(-1,m_Path);
		m_cPath.SetCurSel(Pos);
		m_PathID = m_cPath.GetItemData(Pos);
		
		CFileFind	finder;
//		BOOL		bWorking;
		CString		str;
		/*
		CRSViewJingleFiles	rs(g_strMainConnect);

		rs.m_strFilter="FileName = 'zz'";
		rs.Open();

		m_cFile.ResetContent();

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
				Pos=m_cFile.AddString(finder.GetFileName());
			}
		}

		rs.Close(); */

		Pos=m_cFile.AddString(m_FileName);
		m_cFile.SetCurSel(Pos);

		m_pTimers->SetFile(m_Path+"\\"+m_FileName);
		m_pTimers->m_pTimer->m_End=m_End;
		m_pTimers->m_pTimer->m_Mix=m_Mix;
		m_pTimers->m_pTimer->m_Start=m_Start;
		m_pTimers->m_pTimer->m_FadeOut=0;
		m_pTimers->m_pTimer->m_LoopA=m_LoopA;
		m_pTimers->m_pTimer->m_LoopB=m_LoopB;
		m_pTimers->m_pTimer->m_Intro=m_Intro;
		m_pTimers->OnUpdateTimers(0,0);

	}
	return TRUE; 
}

int CJingles::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect crect;
	GetClientRect(&crect);
	crect.DeflateRect(10,165,10,40);

	m_pTimers = new CRecorder();
	m_pTimers->Create(NULL,WS_VISIBLE|WS_BORDER,crect,this);
	
	return 0;
}

void CJingles::OnKillfocusPath() 
{
	int Pos=m_cPath.GetCurSel();
	if( Pos==CB_ERR )
		return;

	CString	strTemp;
	long	lID=m_cPath.GetItemData(Pos);

	if( (lID!=m_PathID) || (!m_IsNew) )
	{
		m_IsNew = TRUE;

		m_PathID=lID;
		m_cPath.GetLBText(Pos,m_Path);
		
		CFileFind	finder;
		BOOL		bWorking;
		CString		str;

		m_cFile.ResetContent();

		bWorking=finder.FindFile(m_Path+"\\*.*");

		while( bWorking )
		{
			bWorking=finder.FindNextFile();

			strTemp = finder.GetFileName();
			strTemp.MakeLower();
			if( (strTemp.Find(".mp3",0)==strTemp.GetLength()-4) || (strTemp.Find(".wav",0)==strTemp.GetLength()-4) )
				Pos=m_cFile.AddString(finder.GetFileName());
		}

	}
}

void CJingles::OnSelchangePath() 
{
	// TODO: Add your control notification handler code here
	
}

void CJingles::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int		Pos=m_cRythm.GetPos();
	CString str;

	str.Format("%d bmp",Pos);
	m_cRythmV.SetWindowText(str);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CJingles::OnKillfocusFile() 
{
	int Pos=m_cFile.GetCurSel();
	if( Pos==CB_ERR )
		return;

	CString strFullFileName,
			strFileName;
	
	m_cFile.GetLBText(Pos,strFileName);
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

void CJingles::OnKillfocusType() 
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

	CRSTypeOfJingle	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s' AND Activ = 1",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cType.SetWindowText(rs.m_Name);
		m_TypeID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWTYPEOFJINGLE,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cType.GetWindowText(rs.m_Name);
			rs.Update();
			rs.Requery();

			m_TypeID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_JINGLETYPE,rs.m_ID);
		}
		else
		{
			m_cType.SetWindowText("");
			m_TypeID=0;
		}
	}
	rs.Close();		
}

void CJingles::OnSelchangeType() 
{
	int Pos=m_cType.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cType.GetItemData(Pos);
	if( lData==0 )
	{
		CRSTypeOfJingle rs(g_strMainConnect);
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

void CJingles::OnOK() 
{
	UpdateData();

	if( m_TypeID == 0 )
		return;

	m_Name.TrimRight();
	if( m_Name.GetLength()==0 )
		return;

	if( m_PathID == 0 )
		return;

	if( m_FileName.GetLength()==0 )
		return;

	CDialog::OnOK();
}
