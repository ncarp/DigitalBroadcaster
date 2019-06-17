// Scheduler.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <objbase.h>
#include <initguid.h>

#include <gdiplus.h>
using namespace Gdiplus;

#include "Scheduler.h"
#include "MainFrm.h"
#include "SchedulerDoc.h"
#include "CalendarFrame.h"
#include "CalendarLeftView.h"
#include "ScheduleLeftView.h"
#include "ScheduleFrame.h"
#include "..\common\include\defines.h"
#include "..\common\include\permissions.h"
#include "..\common\include\htmlinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImageList	*g_ilToolBar;
CImageList	*g_ilTree;

char		g_strToolBarLabels[256];
CString		g_strMainConnect="Broadcaster",
			g_strOnAirConnect,
			g_strBaseURL,
			g_strPFLAudio,
			g_strMainAudio,
			g_strRecordAudio,
			g_strTempDir,
			g_strAudioIn[50],
			g_strAudioOut[50],
			g_strUserName,
			g_strComputerName;
UINT		g_nFormat;
int			g_iSlow=40,
			g_iSlowAverage=60,
			g_iAverage=75;
long		g_lComputerID;
tPermissions g_Permissions;
CDatabase	*g_pDigitalRMDB;
CImageList	*g_ImageListToolHot,
			*g_ImageListToolEnabled;
char		g_lpstrToolLabels[250];

LPDIRECTSOUNDBUFFER		lpDS_PrimaryBuffer;
LPDIRECTSOUND			lpDS_PFL,lpDS_MAIN;

LPDIRECTSOUNDCAPTURE		g_pDS_Capture=NULL;
LPDIRECTSOUNDCAPTUREBUFFER	g_pDS_CaptureBuffer=NULL;
LPWAVEFORMATEX				g_pwfx=NULL;

CRITICAL_SECTION g_csMPEG;
CRITICAL_SECTION csSAMPLE;
CRITICAL_SECTION g_csEndACM;
CRITICAL_SECTION csDB;
CRITICAL_SECTION csACM;

HANDLE				g_hCapture[3];
DSBPOSITIONNOTIFY	g_dspnCapture[2];

/////////////////////////////////////////////////////////////////////////////
//	GDI+ 
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
FontFamily			*g_fontfamilyTR;
Font				*g_font12,
					*g_font36;

CWnd				*g_wndCartwall=NULL,
					*g_wndLineUp=NULL;
CHtmlInfo			*g_wndInfo;


UINT				g_nFormatLineUp,
					g_nFormatArchive;

int					g_bTimeOut;

/////////////////////////////////////////////////////////////////////////////
//	Dummy function
//BOOL CheckKey(UINT nChar ) { return FALSE; }

/////////////////////////////////////////////////////////////////////////////
// CSchedulerApp

BEGIN_MESSAGE_MAP(CSchedulerApp, CWinApp)
	//{{AFX_MSG_MAP(CSchedulerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchedulerApp construction

CSchedulerApp::CSchedulerApp()
{
	InitializeCriticalSection( &g_csMPEG );
	InitializeCriticalSection( &csSAMPLE );
	InitializeCriticalSection( &g_csEndACM );
	InitializeCriticalSection( &csDB );	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSchedulerApp object

CSchedulerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSchedulerApp initialization

BOOL CSchedulerApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	#pragma warning(disable : 4996)
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	GetComputerAndUser();

	OpenDigitalRMDatabase();

	WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_LOG_SCHEDULER);

	m_pDocCalendar = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSchedulerDoc),
		RUNTIME_CLASS(CCalendarFrame), // custom MDI child frame
		RUNTIME_CLASS(CCalendarLeftView));
	AddDocTemplate(m_pDocCalendar);

	m_pDocSchedule = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSchedulerDoc),
		RUNTIME_CLASS(CScheduleFrame), // custom MDI child frame
		RUNTIME_CLASS(CScheduleLeftView));
	AddDocTemplate(m_pDocSchedule);

	InitializeGDIPlus();

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;


	
	LoadConfig();
	LoadToolBarImageList();
	LoadTreeImageList();
	
//	AfxOleInit();
	g_nFormat=RegisterClipboardFormat("DIGITALRM");

	DirectSoundEnumerate(DSEnumCallback,this);
	DirectSoundCaptureEnumerate(DSCEnumCallback,this);

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
void CSchedulerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSchedulerApp message handlers

void CSchedulerApp::InitializeGDIPlus()
{
	GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);
	g_fontfamilyTR	= ::new FontFamily(L"Times New Roman");
	g_font12		= ::new Font(g_fontfamilyTR, 18, FontStyleRegular, UnitPixel);
}

//	Load the tool bar bitmaps
void CSchedulerApp::LoadToolBarImageList()
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

	// Lock Item (17)
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_INFO);
	g_ilToolBar->Add(bm,RGB(212,208,200));

	str.LoadString(IDS_TOOL_INFO);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Estatistica (18)
	str="Estatistica";
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;
}	

void CSchedulerApp::LoadTreeImageList()
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
}

void CSchedulerApp::LoadConfig()
{
	HKEY hConfigKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	HKEY hAudioKey = NULL;
	DWORD dwData;
	
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

					// Main Audio
					lResult = RegQueryValueEx(hAudioKey,_T("Main"),NULL,&dwType,NULL, &dwCount);
					if (lResult == ERROR_SUCCESS)
					{
						ASSERT(dwType == REG_SZ);
						lResult = RegQueryValueEx(hAudioKey,_T("Main"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strMainAudio=strValue;
						else
							g_strMainAudio="";
					}

					// Record
					lResult = RegQueryValueEx(hAudioKey,_T("Recorder"),NULL,&dwType,NULL, &dwCount);
					if (lResult == ERROR_SUCCESS)
					{
						ASSERT(dwType == REG_SZ);
						lResult = RegQueryValueEx(hAudioKey,_T("Recorder"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strRecordAudio=strValue;
						else
							g_strRecordAudio="";
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
					
					// Wave Format
					lResult = RegQueryValueEx(hAudioKey,_T("AudioParamSize"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						int nSize=0;

						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("AudioParamSize"),NULL,&dwType,(LPBYTE)&nSize,&dwCount);
						if( nSize>0 )
						{
							lResult = RegQueryValueEx(hAudioKey,_T("WAVEFORMATEX"),NULL,&dwType,NULL,&dwCount);
							if( lResult==ERROR_SUCCESS )
							{
								ASSERT( dwType==REG_BINARY );

								g_pwfx = (LPWAVEFORMATEX)malloc(nSize);
								lResult = RegQueryValueEx(hAudioKey,_T("WAVEFORMATEX"),NULL,&dwType,(LPBYTE)g_pwfx,&dwCount);
							}
						}
					}
					if( g_pwfx == NULL )
					{
						g_pwfx = (LPWAVEFORMATEX)malloc(sizeof(WAVEFORMATEX));
						g_pwfx->cbSize			= 0;
						g_pwfx->nAvgBytesPerSec	= 44100 * 2 * 2;
						g_pwfx->nBlockAlign		= 4;
						g_pwfx->nChannels		= 2;
						g_pwfx->nSamplesPerSec	= 44100;
						g_pwfx->wBitsPerSample	= 16;
						g_pwfx->wFormatTag		= WAVE_FORMAT_PCM;
					}

					lResult = RegQueryValueEx(hAudioKey,_T("MaxSlow"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("MaxSlow"),NULL,&dwType,(LPBYTE)&dwData, &dwCount);
						
						if( lResult==ERROR_SUCCESS )
							g_iSlow=dwData;
						else
							g_iSlow=25;
					} 

					lResult = RegQueryValueEx(hAudioKey,_T("MaxSlowAverage"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("MaxSlowAverage"),NULL,&dwType,(LPBYTE)&dwData, &dwCount);
						
						if( lResult==ERROR_SUCCESS )
							g_iSlowAverage=dwData;
						else
							g_iSlowAverage=75;
					} 

					lResult = RegQueryValueEx(hAudioKey,_T("MaxAverage"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("MaxAverage"),NULL,&dwType,(LPBYTE)&dwData, &dwCount);
						
						if( lResult==ERROR_SUCCESS )
							g_iAverage=dwData;
						else
							g_iAverage=125;
					} 
				}

	if( hConfigKey!=NULL ) RegCloseKey(hConfigKey);
	if( hCompanyKey!=NULL ) RegCloseKey(hCompanyKey);
	if( hSoftKey!=NULL ) RegCloseKey(hSoftKey);
}

BOOL CALLBACK CSchedulerApp::DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	CSchedulerApp *This=(CSchedulerApp *)lpContext;

	CString strTemp;
	static int Cont=0;
	int n=2;

	strTemp.Format("%s",lpcstrDescription);

	for( int i=0; i<Cont; i++ )
	{
		if( strTemp==g_strAudioOut[i] )
		{
			strTemp.Format("%s (%d)",lpcstrDescription,n);
			n++;
		}
	}
	g_strAudioOut[Cont]=strTemp;
	Cont++;

#if defined USE_MAIN_AUDIO
	if( (g_strMainAudio==strTemp) )
#else
	if( (g_strPFLAudio==strTemp) )
#endif
		lpDS_PFL=This->InitializeDirectSound(lpGuid);

	return TRUE;
}

BOOL CALLBACK CSchedulerApp::DSCEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	CSchedulerApp *This=(CSchedulerApp *)lpContext;

	CString strTemp;
	static int Cont=0;
	int n=2;

	strTemp.Format("%s",lpcstrDescription);

	for( int i=0; i<Cont; i++ )
	{
		if( strTemp==g_strAudioIn[i] )
		{
			strTemp.Format("%s (%d)",lpcstrDescription,n);
			n++;
		}
	}
	g_strAudioIn[Cont]=strTemp;
	Cont++;

	if( (g_strRecordAudio==strTemp) )
		g_pDS_Capture=This->InitializeDirectSoundCapture(lpGuid);

	return TRUE;
}

LPDIRECTSOUND CSchedulerApp::InitializeDirectSound(LPGUID lpguid)
{
	DSBUFFERDESC	dsbDesc;
	WAVEFORMATEX	WaveFormat;
	LPDIRECTSOUND	lpds;

	if( DirectSoundCreate(lpguid,&lpds,NULL)!=DS_OK )
		return FALSE;

   	if( lpds->SetCooperativeLevel(m_pMainWnd->m_hWnd,DSSCL_PRIORITY)!=DS_OK )
	{
		lpds->Release();
		return FALSE;
	}

	// Obtem o buffer primário ---------------------------------------
	ZeroMemory(&dsbDesc,sizeof(DSBUFFERDESC));
	dsbDesc.dwSize=sizeof(DSBUFFERDESC);
	dsbDesc.dwFlags=DSBCAPS_PRIMARYBUFFER;
	if( lpds->CreateSoundBuffer(&dsbDesc,&lpDS_PrimaryBuffer,NULL)!=DS_OK )
	{
		lpds->Release();
		return FALSE;
	}

	// Define o formato do buffer principal --------------------------
	ZeroMemory(&WaveFormat,sizeof(WAVEFORMATEX));
	WaveFormat.wFormatTag		= WAVE_FORMAT_PCM;
	WaveFormat.nChannels		= 2;
	WaveFormat.nSamplesPerSec	= 44100;
	WaveFormat.wBitsPerSample	= 16;
	WaveFormat.nBlockAlign		= 4;
	WaveFormat.nAvgBytesPerSec	= 176400;
	if( lpDS_PrimaryBuffer->SetFormat(&WaveFormat)!=DS_OK )
	{
		lpds->Release();
		return FALSE;
	}

	return lpds;
}

LPDIRECTSOUNDCAPTURE CSchedulerApp::InitializeDirectSoundCapture(LPGUID lpGuid)
{
	LPDIRECTSOUNDCAPTURE	lpDSTemp;
	LPDIRECTSOUNDNOTIFY		lpdsNotify;
	DSCBUFFERDESC	dsbcDesc;
	WAVEFORMATEX	WaveFormat;

	// Criação de um device DirectSound
	if( DirectSoundCaptureCreate(lpGuid,&lpDSTemp,NULL)!=DS_OK )
		return NULL;

	// Define o formato de gravação --------------------------
	ZeroMemory(&WaveFormat,sizeof(WAVEFORMATEX));
	WaveFormat.wFormatTag		= WAVE_FORMAT_PCM;
	WaveFormat.nChannels		= 2;
	WaveFormat.nSamplesPerSec	= 44100;
	WaveFormat.wBitsPerSample	= 16;
	WaveFormat.nBlockAlign		= 4;
	WaveFormat.nAvgBytesPerSec	= 176400;

	// Obtem o buffer primário ---------------------------------------
	ZeroMemory(&dsbcDesc,sizeof(DSCBUFFERDESC));
	dsbcDesc.dwSize=sizeof(DSCBUFFERDESC);
	dsbcDesc.dwFlags=0;
	dsbcDesc.dwBufferBytes=WaveFormat.nAvgBytesPerSec;
	dsbcDesc.dwReserved=0;
	dsbcDesc.lpwfxFormat=&WaveFormat;

	if( lpDSTemp->CreateCaptureBuffer(&dsbcDesc,&g_pDS_CaptureBuffer,NULL)!=DS_OK )
	{
		lpDSTemp->Release();
		return FALSE;
	}

	// Criar os eventos de notificação
	g_hCapture[0]=CreateEvent(NULL,FALSE,FALSE,NULL);
	g_hCapture[1]=CreateEvent(NULL,FALSE,FALSE,NULL);
	g_hCapture[2]=CreateEvent(NULL,FALSE,FALSE,NULL);

	g_dspnCapture[0].dwOffset=dsbcDesc.dwBufferBytes/2-1;
	g_dspnCapture[0].hEventNotify=g_hCapture[0];
	g_dspnCapture[1].dwOffset=dsbcDesc.dwBufferBytes-1;
	g_dspnCapture[1].hEventNotify=g_hCapture[1];

	IDirectSoundCaptureBuffer_QueryInterface(g_pDS_CaptureBuffer,IID_IDirectSoundNotify,(VOID **)&lpdsNotify);
	IDirectSoundNotify_SetNotificationPositions(lpdsNotify,2,g_dspnCapture);

	return lpDSTemp;
}