// VoiceInsert.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "VoiceInsert.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\include\RSPath.h"
#include "..\include\RSOnAirUsers.h"
#include "..\include\RSViewVoiceInsert.h"
#include ".\voiceinsert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString	g_strMainConnect;
/////////////////////////////////////////////////////////////////////////////
// CVoiceInsert dialog


CVoiceInsert::CVoiceInsert(CWnd* pParent /*=NULL*/)
	: CDialog(CVoiceInsert::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoiceInsert)
	m_strName = _T("");
	m_User = -1;
	//}}AFX_DATA_INIT
	m_ID = 0;
}

CVoiceInsert::~CVoiceInsert()
{
	delete m_pTimers;
}


void CVoiceInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoiceInsert)
	DDX_Control(pDX, IDC_FILE, m_cFile);
	DDX_Control(pDX, IDC_USER, m_cUser);
	DDX_Control(pDX, IDC_PATH, m_cPath);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_CBIndex(pDX, IDC_USER, m_User);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVoiceInsert, CDialog)
	//{{AFX_MSG_MAP(CVoiceInsert)
	ON_WM_CREATE()
	ON_CBN_KILLFOCUS(IDC_FILE, OnKillfocusFile)
	ON_CBN_KILLFOCUS(IDC_PATH, OnKillfocusPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoiceInsert message handlers

int CVoiceInsert::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	rect;
	GetClientRect(&rect);

	rect.DeflateRect(10,125,10,50);
	m_pTimers = new CRecorder();
	m_pTimers->m_bCanRec=TRUE;
	m_pTimers->Create(NULL,WS_VISIBLE|WS_BORDER,rect,this);
	
	return 0;
}

BOOL CVoiceInsert::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int Pos;

	CRSPath	rsPath(g_strMainConnect);
	rsPath.m_strFilter = "Takes = 1";
	rsPath.m_strSort = "Path";
	rsPath.Open();

	while( !rsPath.IsEOF() )
	{
		rsPath.m_Path.TrimRight();
		Pos=m_cPath.AddString(rsPath.m_Path);
		m_cPath.SetItemData(Pos,rsPath.m_ID);

		rsPath.MoveNext();
	}
	rsPath.Close();

	if( m_ID == 0 )
	{
		m_cPath.SetCurSel(0);
	}
	else
	{
		Pos = m_cPath.FindStringExact(-1,m_strPath);
		m_cPath.SetCurSel(Pos);
	}
	OnKillfocusPath();
	
	CRSOnAirUsers rsUser( g_strMainConnect );
	rsUser.m_strFilter="Activ = 1";
	rsUser.m_strSort="Name";
	rsUser.Open();

	while( !rsUser.IsEOF() )
	{
		rsUser.m_Name.TrimRight();
		Pos=m_cUser.AddString(rsUser.m_Name);	
		m_cUser.SetItemData(Pos,rsUser.m_ID);
		rsUser.MoveNext();
	}
	rsUser.Close();

	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_FADEIN,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_INTRO,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_FADEOUT,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_MIX,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPA,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPB,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pLoopCheck->EnableWindow(FALSE);
	m_pTimers->m_bCanRec = TRUE;

	Pos = m_cUser.FindStringExact(-1,m_strUser );
	if( Pos==CB_ERR )
		m_UserID = 0;
	else
		m_cUser.SetCurSel(Pos);

	Pos = m_cPath.FindStringExact(-1,m_strPath);
	if( Pos!=CB_ERR )
		m_cPath.SetCurSel(Pos);

	m_cFile.SetWindowText(m_strFileName);
	m_pTimers->SetFile(m_strPath+"\\"+m_strFileName);

	if( m_ID!= 0 )
	{
		m_pTimers->m_pTimer->m_Start = m_Start;
		m_pTimers->m_pTimer->m_End = m_End;
		m_pTimers->m_pTimer->m_Mix = m_End+10000;
		m_pTimers->m_pTimer->m_FadeOut = m_End+10000;
		m_pTimers->OnUpdateTimers(0,0);
	}
	else
	{
		m_pTimers->m_pTimer->m_Start = 0;
		m_pTimers->m_pTimer->m_End = 0;
		m_pTimers->m_pTimer->m_Mix = 0;
		m_pTimers->m_pTimer->m_FadeOut = 0;
		m_pTimers->OnUpdateTimers(0,0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVoiceInsert::OnKillfocusFile() 
{
	CString strFullFileName,
			strFileName;
	
	m_cFile.GetWindowText(strFileName);
	strFileName.TrimRight();

	if( strFileName.GetLength()==0 )
	{
		m_pTimers->m_pTimer->DeleteBM();
		m_pTimers->SetFile("");	
		return;
	}

	if( (strFileName.Find(".wav")!=strFileName.GetLength()-4) &&
		(strFileName.Find(".mp3")!=strFileName.GetLength()-4) )
	{
		strFileName+=".wav";
		m_cFile.SetWindowText(strFileName);
	}

	if( strFileName!=m_strFileName)
	{
		m_strFileName=strFileName;
		strFullFileName=m_strPath+"\\"+m_strFileName;

		m_pTimers->m_pTimer->DeleteBM();
		m_pTimers->SetFile(strFullFileName);	
		m_pTimers->m_pTimer->m_FadeOut=0;
		m_pTimers->m_pTimer->m_Mix=m_pTimers->m_pTimer->m_End;
		m_pTimers->m_pTimer->PaintTimerBM();
		m_pTimers->OnUpdateTimers(0,0);
	}
}

void CVoiceInsert::OnKillfocusPath() 
{
	int Pos=m_cPath.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lID=m_cPath.GetItemData(Pos);
	m_PathID=lID;
	m_cPath.GetLBText(Pos,m_strPath);
	FillFileList();
}

void CVoiceInsert::FillFileList()
{
	CFileFind	finder;
	BOOL		bWorking;
	CString		str,
				strFile,
				strTemp;
	int			Pos;

	m_cFile.GetWindowTextA(strFile);
	m_cFile.ResetContent();

	bWorking=finder.FindFile(m_strPath+"\\*.*");

	while( bWorking )
	{
		bWorking=finder.FindNextFile();
		
		strTemp = finder.GetFileName();
		strTemp.MakeLower();
		if( (strTemp.Find(".mp3",0)==strTemp.GetLength()-4) || (strTemp.Find(".wav",0)==strTemp.GetLength()-4) )
				Pos=m_cFile.AddString(finder.GetFileName());
	}

	m_cFile.SetWindowTextA(strFile);
	if( strFile.GetLength()!=0 )
		m_strFileName="";

	OnKillfocusFile();
}

void CVoiceInsert::OnOK() 
{
	UpdateData();
	
	if( m_User == CB_ERR )
		return;

	if( m_pTimers->m_wMode==STATE_RECORDING )
		return;

	m_cUser.GetLBText(m_User,m_strUser);
	m_UserID = m_cUser.GetItemData(m_User);

	m_strName.TrimRight();
	if( m_strName.GetLength()==0 )
		return;

	m_strFileName.TrimRight();
	if( m_strFileName.GetLength()==0 )
		return;

	if( m_PathID == 0 )
		return;

	m_Start = m_pTimers->m_pTimer->m_Start;
	m_End	= m_pTimers->m_pTimer->m_End;

	if( m_End <= m_Start )
		return;

	CDialog::OnOK();
}

void CVoiceInsert::OnCancel()
{
	if( m_pTimers->m_wMode==STATE_RECORDING )
		return;

	CDialog::OnCancel();
}
