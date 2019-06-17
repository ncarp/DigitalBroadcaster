// Traffic.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include <objbase.h>
#include <initguid.h>

#include "Traffic.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "MainFrm.h"
#include "TrafficDoc.h"
#include "TrafficManagmentFrame.h"
#include "TrafficManagmentLeftView.h"
#include "SponsorsFrame.h"
#include "SponsorsLeftView.h"
#include "..\include\RecordingsFrame.h"
#include "..\include\RecordingsLeftView.h"
#include "..\common\include\permissions.h"
#include "..\common\include\defines.h"
#include "..\common\include\global.h"
#include "..\common\include\htmlinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Font		*g_font36;

CImageList	*g_ilToolBar;
CImageList	*g_ilTree;

char		g_strToolBarLabels[256];
CString		g_strMainConnect="Broadcaster",
			g_strOnAirConnect,
			g_strBaseURL,
			g_strPFLAudio,
			g_strMainAudio,
			g_strTempDir,
			g_strAudioOut[50],
			g_strUserName,
			g_strComputerName;
UINT		g_nFormat,
			g_nFormatLineUp,
			g_nFormatArchive;
long		g_lComputerID;
BOOL		g_bTimeOut;

CDatabase	*g_pDigitalRMDB;
tPermissions g_Permissions;
CImageList	*g_ImageListToolHot,
			*g_ImageListToolEnabled;
char		g_lpstrToolLabels[250];

LPDIRECTSOUNDBUFFER	lpDS_PrimaryBuffer;
LPDIRECTSOUND		lpDS_PFL,lpDS_MAIN;

LPWAVEFORMATEX		g_pwfx=NULL;

LPDIRECTSOUNDCAPTUREBUFFER g_pDS_CaptureBuffer=NULL;
HANDLE				g_hCapture[3];
DSBPOSITIONNOTIFY	g_dspnCapture[2];

CRITICAL_SECTION g_csMPEG;
CRITICAL_SECTION csSAMPLE;
CRITICAL_SECTION g_csEndACM;
CRITICAL_SECTION csDB;
CRITICAL_SECTION csACM;

/////////////////////////////////////////////////////////////////////////////
//	GDI+ 
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
FontFamily			*g_fontfamilyTR;
Font				*g_font12;

CWnd	*g_wndLineUp = NULL,
		*g_wndCartwall = NULL;

CHtmlInfo	*g_wndInfo = NULL;

/////////////////////////////////////////////////////////////////////////////
// CTrafficApp

BEGIN_MESSAGE_MAP(CTrafficApp, CWinApp)
	//{{AFX_MSG_MAP(CTrafficApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficApp construction

CTrafficApp::CTrafficApp()
{
	InitializeCriticalSection( &g_csMPEG );
	InitializeCriticalSection( &csSAMPLE );
	InitializeCriticalSection( &g_csEndACM );
	InitializeCriticalSection( &csDB );
}

CTrafficApp::~CTrafficApp()
{
	GdiplusShutdown(gdiplusToken);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTrafficApp object

CTrafficApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTrafficApp initialization

BOOL CTrafficApp::InitInstance()
{
	AfxEnableControlContainer();

	AfxOleInit();
	g_nFormat=RegisterClipboardFormat("DIGITALRM");

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

	InitializeGDIPlus();

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  

	GetComputerAndUser();

	OpenDigitalRMDatabase();

	WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_LOG_TRAFFIC,0,0);

	m_pDocTrafficManagment = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTrafficDoc),
		RUNTIME_CLASS(CTrafficManagmentFrame), // custom MDI child frame
		RUNTIME_CLASS(CTrafficManagmentLeftView));
	AddDocTemplate(m_pDocTrafficManagment);

	m_pDocSponsors = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTrafficDoc),
		RUNTIME_CLASS(CSponsorsFrame), // custom MDI child frame
		RUNTIME_CLASS(CSponsorsLeftView));
	AddDocTemplate(m_pDocSponsors);

	m_pDocRecordings = new CMultiDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTrafficDoc),
		RUNTIME_CLASS(CRecordingsFrame),
		RUNTIME_CLASS(CRecordingsLeftView));
	AddDocTemplate(m_pDocRecordings);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	InitializeCriticalSection( &csACM );

	LoadConfig();
	LoadToolBarImageList();
	LoadTreeImageList();
	DirectSoundEnumerate(DSEnumCallback,this);

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	if( g_wndInfo==NULL )
		return TRUE;

	CString str;
	
	str.Format("%s/trafficalert.asp",g_strBaseURL);

	if( g_wndInfo->m_pView->GetLocationURL()==str )
		g_wndInfo->RestoreWindow();
	else
		g_wndInfo->SetView(str);
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
void CTrafficApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CTrafficApp::InitializeGDIPlus()
{
	GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);
	g_fontfamilyTR	= ::new FontFamily(L"Times New Roman");
	g_font12		= ::new Font(g_fontfamilyTR, 18, FontStyleRegular, UnitPixel);
}

/////////////////////////////////////////////////////////////////////////////
//	Load the tool bar bitmaps
void CTrafficApp::LoadToolBarImageList()
{
	CBitmap *bm;
	CString str;
	int		strSize=0;

	//  Reset the tool label
	memset(g_strToolBarLabels,0,256);

	//	Create the image list
	g_ilToolBar = new CImageList();
	g_ilToolBar->Create(40,36,ILC_COLOR24|ILC_MASK,0,20);

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

	str.LoadString(IDS_TOOL_NEWTRAFFICSCHEDULE);
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
	g_ilToolBar->Add(bm,RGB(212,208,200));

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
	g_ilToolBar->Add(bm,RGB(212,208,200));

	str.LoadString(IDS_TOOL_NEWLINEUP);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;

	// Info
	bm = new CBitmap();
	bm->LoadBitmap(IDB_TOOL_INFO);
	g_ilToolBar->Add(bm,RGB(212,208,200));

	str.LoadString(IDS_TOOL_TRAFFICLIST);
	memcpy(g_strToolBarLabels+strSize,str,str.GetLength() );
	strSize+=str.GetLength()+1;
}

void CTrafficApp::LoadTreeImageList()
{
	CBitmap  *bm;

	g_ilTree = new CImageList();
	g_ilTree->Create(20,20,ILC_COLOR24|ILC_MASK,0,20);

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_SPOT);
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_SPOT);
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_FOLDER_SCHEDULE);
	g_ilTree->Add(bm,RGB(255,255,255));

	bm = new CBitmap();
	bm->LoadBitmap(IDB_TREE_SCHEDULE);
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
}


void CTrafficApp::LoadConfig()
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

BOOL CALLBACK CTrafficApp::DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	CTrafficApp *This=(CTrafficApp*)lpContext;

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

LPDIRECTSOUND CTrafficApp::InitializeDirectSound(LPGUID lpguid)
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

/////////////////////////////////////////////////////////////////////////////
// CTrafficApp message handlers

