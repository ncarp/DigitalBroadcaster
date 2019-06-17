// Manager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Manager.h"

#include "MainFrm.h"
#include "OnAirUserFrame.h"
#include "ManagerDoc.h"
#include "OnAirUserView.h"
#include "HDFrame.h"
#include "HDView.h"
#include "TimeFrame.h"
#include "TimeView.h"
#include "LogFrame.h"
#include "LogView.h"
#include "UserFrame.h"
#include "UserView.h"
#include "..\common\include\permissions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImageList	*g_ilToolBar;
CImageList	*g_ilTree;

char		g_strToolBarLabels[512];
CString		g_strMainConnect="Broadcaster",
			g_strPFLAudio,
			g_strBaseURL,
			g_strTempDir,
			g_strComputerName,
			g_strUserName;
long int	g_lComputerID,
			g_lUserID;
UINT		g_nFormat;

tPermissions	g_Permissions;
CDatabase		*g_pDigitalRMDB;

/////////////////////////////////////////////////////////////////////////////
// CManagerApp

BEGIN_MESSAGE_MAP(CManagerApp, CWinApp)
	//{{AFX_MSG_MAP(CManagerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagerApp construction

CManagerApp::CManagerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CManagerApp object

CManagerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CManagerApp initialization

BOOL CManagerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	#pragma warning(disable : 4996)
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	LoadConfig();
	
	LoadTreeImageList();
	LoadToolBarImageList();
	GetComputerAndUser();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	pDocOnAirUser = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CManagerDoc),
		RUNTIME_CLASS(COnAirUserFrame), // custom MDI child frame
		RUNTIME_CLASS(COnAirUserView));
	AddDocTemplate(pDocOnAirUser);

	pDocHD = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CManagerDoc),
		RUNTIME_CLASS(CHDFrame),
		RUNTIME_CLASS(CHDView) );
	AddDocTemplate(pDocHD);

	pDocTime = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CManagerDoc),
		RUNTIME_CLASS(CTimeFrame),
		RUNTIME_CLASS(CTimeView) );
	AddDocTemplate(pDocTime);

	pDocLog = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CManagerDoc),
		RUNTIME_CLASS(CLogFrame),
		RUNTIME_CLASS(CLogView) );
	AddDocTemplate(pDocLog);

	pDocUser = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CManagerDoc),
		RUNTIME_CLASS(CUserFrame),
		RUNTIME_CLASS(CUserView) );
	AddDocTemplate(pDocUser);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;


	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

// App command to run the dialog
void CManagerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CManagerApp message handlers

void CManagerApp::LoadToolBarImageList()
{
	CBitmap *bm;
	CString str;
	int		strSize=0;

	//  Reset the tool label
	memset(g_strToolBarLabels,0,256);

	//	Create the image list
	g_ilToolBar = new CImageList();
	g_ilToolBar->Create(40,36,ILC_COLOR24|ILC_MASK,0,10);

	// new Spot (0)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWSPOT);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWSPOT);
	memcpy(g_strToolBarLabels,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Edit (1)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_EDIT);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_EDIT);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Cut (2)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_CUT);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_CUT);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Cut (3)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWTRAFFICSCHEDULE);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWSCHEDULE);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Procurar blocos (4)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_QUERYBLOCKS);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_QUERYBLOCKS);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// New Sound (5)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWSOUND);
	g_ilToolBar->Add(bm,RGB(212,208,200));

	str.LoadString(IDS_TOOL_NEWSOUND);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// PFL (6)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_PFL);
	g_ilToolBar->Add(bm,RGB(212,208,200));

	str.LoadString(IDS_TOOL_PFL);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// New RM (7)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWRM);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWRM);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Text RM (8)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWTEXT);
	g_ilToolBar->Add(bm,RGB(212,208,200));

	str.LoadString(IDS_TOOL_NEWTEXT);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Novo alinhamento de RM (9)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWCARTWALL);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWLINEUP);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// New Line Up (10)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWNEWSLINEUP);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWLINEUP);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// New Line Up (11)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWJINGLE);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWJINGLE);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// New Line Up (12)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWBLOCK);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWBLOCK);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// New New Play List (13)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWPLAYLIST);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWPLAYLIST);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Edit Line up (14)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_EDIT);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_EDITLINEUP);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Save Line up (15)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_SAVE);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_SAVE);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Lock Item (16)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_LOCK);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_LOCK);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// New Folder (17)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_NEWFOLDER);
	g_ilToolBar->Add(bm,RGB(255,255,255));

	str.LoadString(IDS_TOOL_NEWFOLDER);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	str.LoadString(IDS_TOOL_NEWTIME);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;
}	

void CManagerApp::LoadTreeImageList()
{
	CBitmap  *bm;

	g_ilTree = new CImageList();
	g_ilTree->Create(20,20,ILC_COLOR24|ILC_MASK,0,30);

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_SPOT);
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_SPOT);
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_SCHEDULE); // (2)
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_SCHEDULE); // (3)
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_JINGLE); // 4
	g_ilTree->Add(bm,RGB(255,255,255)); 

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_USER); // 5
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_RECORDINGTASK); // 6
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_SOUNDRECORDING); // 7
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_RM); // 8
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_RM); // 9
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_TEXT); // 10
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_TEXT); // 11
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_CARTWALL); // 12
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_NEWSLINEUP); // 13
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_JINGLE); // 14
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_UNLISTED); // 15
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_MUSIC); // 16
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_MUSIC); // 17
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_TEMPLATE); // 18
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_LOCK); // 19
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_NEWTEMPLATE); // 20
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDERUSER); // 21
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER); // 22
	g_ilTree->Add(bm,RGB(255,255,255));
}

void CManagerApp::LoadConfig()
{
	HKEY hConfigKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	HKEY hAudioKey = NULL;
	
	if( RegOpenKeyEx(HKEY_CURRENT_USER, _T("software"), 0, KEY_WRITE|KEY_READ,&hSoftKey) == ERROR_SUCCESS )
		if( RegOpenKeyEx(hSoftKey,_T("DigitalBroadcaster"),0, KEY_WRITE|KEY_READ,&hCompanyKey) == ERROR_SUCCESS )
			if( RegOpenKeyEx(hCompanyKey,_T("Config"),0,KEY_WRITE|KEY_READ,&hConfigKey) == ERROR_SUCCESS )
				if( RegOpenKeyEx(hConfigKey,_T("Audio"),0,KEY_WRITE|KEY_READ,&hAudioKey) == ERROR_SUCCESS )
				{
					CString strValue;
					DWORD dwType, dwCount;//, dwData;
					int lResult;

					// Monicao
					lResult = RegQueryValueEx(hAudioKey,_T("PFL"),NULL,&dwType,NULL, &dwCount);
					if (lResult == ERROR_SUCCESS)
					{
						ASSERT(dwType == REG_SZ);
						lResult = RegQueryValueEx(hAudioKey,_T("PFL"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strPFLAudio=strValue;
						else
							g_strPFLAudio="";
					}

					// Internet server
					lResult = RegQueryValueEx(hAudioKey,_T("BaseURL"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_SZ );
						lResult = RegQueryValueEx(hAudioKey,_T("BaseURL"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strBaseURL=strValue;
						else
							g_strBaseURL="";
					}

					// Temp dir
					lResult = RegQueryValueEx(hAudioKey,_T("TempFolder"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_SZ );
						lResult = RegQueryValueEx(hAudioKey,_T("TempFolder"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strTempDir=strValue;
						else
							g_strTempDir="C:\\temp";
					}

				}

	if( hConfigKey!=NULL ) RegCloseKey(hConfigKey);
	if( hCompanyKey!=NULL ) RegCloseKey(hCompanyKey);
	if( hSoftKey!=NULL ) RegCloseKey(hSoftKey);

}

