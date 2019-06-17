// OnAir.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include <objbase.h>
#include <initguid.h>

#include <gdiplus.h>
using namespace Gdiplus;


#include "OnAir.h"

#include "OnAirWnd.h"
#include "CartwallWnd.h"
#include "LineUpWnd.h"
#include "PFLWnd.h"
#include "AiredWnd.h"
#include "LogOn.h"
#include "..\include\SoundManager.h"
#include "..\include\RSRadioStations.h"
#include "..\common\include\utils.h"
#include "..\common\include\permissions.h"
#include "..\common\include\global.h"
#include "..\common\include\splitter_utils.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//	Debug
extern	CString g_strLogFile;
extern	int g_nLastLogHour;


/////////////////////////////////////////////////////////////////////////////
//	Global Variables
WORD	g_wAutomationMode;


/////////////////////////////////////////////////////////////////////////////
//	Drawing and color objects
CPen	*g_pLightPen=NULL;
CPen	*g_pShadowPen=NULL;
CPen	*g_pBlackPen=NULL;
CPen	*g_pFacePen=NULL;
CBrush	*g_brushBackground = new CBrush(GetSysColor(COLOR_3DFACE)),
		*g_brushMusicBack = new CBrush(RGB(250,250,255));

FontFamily			*g_fontfamilyTR;
Font				*g_font36,
					*g_font24,
					*g_font12,
					*g_fontRythm,
					*g_fontSmallTitle,
					*g_font14Bold;
Color				g_colorCaptionText,
					g_colorShadow(200,0,0,0),
					g_colorRed(255,250,0,0),
					g_colorGreen(255,0,250,0),
					g_colorFace,
					g_colorLight[]={ Color(128,255,255,255),Color(0,255,255,255),Color(0,255,255,255),Color(0,255,255,255) },
					g_colorDark[]={ Color(0,0,0,0),Color(64,0,0,0),Color(0,0,0,0),Color(0,0,0,0) };
SolidBrush			*g_brushCaptionText,
					*g_brushShadowText;
LinearGradientBrush	*g_brushSeparator;
CFont				*g_cfont24;

CBitmap				*g_bmRefresh,*g_bmRefreshDisable,*g_bmRefreshHot,
					*g_bmGarbage,*g_bmGarbageDisable,*g_bmGarbageHot,
					*g_bmToolBackground=NULL,
					*g_bmMusicFolder,*g_bmMusicSmall,
					*g_bmContainerMusic;

CImageList			*g_ilToolEnabled,*g_ilToolDisabled,*g_ilToolHot,
					*g_ilSmallIcons,
					*g_ilContainer,
					*g_ImageListToolHot,*g_ImageListToolEnabled;
char				g_lpstrToolLabels[300];
BOOL				g_bFastStart=FALSE,
					g_bNoLog=FALSE,
					g_bIsOnNetwork=FALSE,
					g_bIsAcceptingCommands=FALSE;

/////////////////////////////////////////////////////////////////////////////
//	GDI+ 
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;

/////////////////////////////////////////////////////////////////////////////
//	Drag & Drop 
UINT				g_nFormatArchive,
					g_nFormatLineUp;

/////////////////////////////////////////////////////////////////////////////
//	Global Windows
CWnd				*g_wndCartwall=NULL;
CWnd				*g_wndLineUp=NULL;
CPFLWnd				*g_wndPFL=NULL;
CTrafficInfoWnd		*g_wndTrafficInfo;
CProgInfoWnd		*g_wndProgInfo;
CAiredWnd			*g_wndAired;
CLogOn				*g_wndLogOn;

/////////////////////////////////////////////////////////////////////////////
//	Global database 
CString		g_strOnAirConnect="Broadcaster-OnAir",
			g_strMainConnect="Broadcaster",
			g_strDB="",
			g_strUserName = "",
			g_strComputerName;
long		g_lComputerID = 0,
			g_lUserID = 0;
BOOL		g_bUserCanEditMusic,
			g_bUserCanRecord,
			g_bUserCanSchedule,
			g_bUserCanDelayBlocks,
			g_bTimeOut=FALSE;
tPermissions g_Permissions;

/////////////////////////////////////////////////////////////////////////////
//	Configuration strings
CString g_strMainAudio,
		g_strPFLAudio,
		g_strCartwallAudio,
		g_strRecorderAudio;

/////////////////////////////////////////////////////////////////////////////
//	Tralha do 2000
LPDIRECTSOUND		lpDS_MAIN=NULL,
					lpDS_CARTWALL=NULL,
					lpDS_PFL=NULL;
LPDIRECTSOUNDBUFFER	lpDS_PrimaryBuffer;
BOOL				bHasSound;

LPDIRECTSOUNDCAPTURE g_pDS_Capture;
LPDIRECTSOUNDCAPTUREBUFFER g_pDS_CaptureBuffer;
LPWAVEFORMATEX		g_pwfx=NULL;

HANDLE				g_hCapture[3];
DSBPOSITIONNOTIFY	g_dspnCapture[2];

CRITICAL_SECTION g_csMPEG;
CRITICAL_SECTION csSAMPLE;
CRITICAL_SECTION g_csEndACM;
CRITICAL_SECTION csDB;

int		g_iFadeToTake;
int		g_iFadeOnIntro;

CString	g_strTempDir,
		g_strBaseURL;

CString g_strAudioOut[50],
		g_strAudioIn[50];

int		g_iSlow = 25,
		g_iSlowAverage = 75,
		g_iAverage = 125;

long	g_iDelay = 33000,
		g_iInstrumental=0;

// Mixer --------------------------------------------------------------------
BOOL	g_bMixer=FALSE;
DWORD	g_dwMixerID=0,
		g_dwMixerLineID=0;

// Splitter -----------------------------------------------------------------
int		g_nSplitters = 0;
CString g_strSplitter[50];

/////////////////////////////////////////////////////////////////////////////
// COnAirApp

BEGIN_MESSAGE_MAP(COnAirApp, CWinApp)
	//{{AFX_MSG_MAP(COnAirApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirApp construction

COnAirApp::COnAirApp()
{
	InitializeCriticalSection( &g_csMPEG );
	InitializeCriticalSection( &csSAMPLE );
	InitializeCriticalSection( &g_csEndACM );
	InitializeCriticalSection( &csDB );	

	g_strTempDir="C:\\temp";
}

COnAirApp::~COnAirApp()
{

	GdiplusShutdown(gdiplusToken);
}
/////////////////////////////////////////////////////////////////////////////
// The one and only COnAirApp object

COnAirApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COnAirApp initialization

BOOL COnAirApp::InitInstance()
{
//	ACM_InitializeCriticalSection();

	g_wAutomationMode = AUTOMATION_FULLAUTO;

	CDatabase dbOnAir;
	
	while( !dbOnAir.IsOpen() ) 
	{
		try 
		{
			dbOnAir.OpenEx("DSN="+g_strOnAirConnect,CDatabase::noOdbcDialog );
		} catch(...) {}
	}

	GetComputerNameAndID();

	g_strDB = dbOnAir.GetDatabaseName();
	g_strDB.TrimRight();
	dbOnAir.Close();

	HICON hIcon=LoadIcon(IDR_MAINFRAME);

	AfxEnableControlContainer();

	if( !AfxOleInit() )
		AfxMessageBox(IDS_ERROR_OLEINITFAILED,MB_OK);

	g_nFormatArchive=RegisterClipboardFormat("DigitalArchive");
	g_nFormatLineUp =RegisterClipboardFormat("DigitalLineUp");

	CoInitialize(NULL);

#pragma warning(disable : 4996)
	Enable3dControls();	
	
	InitializeGDIplus();

	InitGlobalBitmaps();
	
	SetRegistryKey(_T("Digital Broadcaster"));
	LoadStdProfileSettings();

	ReadConfig();
	if( g_nSplitters>0 )
	{
		typeSplitterMsg	Msg;

		memset(&Msg,0,SIZEOFSPLITTERMSG);
		Msg.wAction	= 0;
		Msg.wType	= 0;
		wsprintf(Msg.pstrMessage,"Incio de Sessão");
		SendSplitterMessage(&Msg);
	}

#ifdef __DEBUG_LOG
	COleDateTime dt = COleDateTime::GetCurrentTime();
	CString strDateTime;
	
	strDateTime.Format("%4d%2d%2d%2d%2d%2d",dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond());
	strDateTime.Replace(" ","0");
	g_strLogFile.Format("%s\\%s.txt",g_strTempDir,strDateTime);
	g_nLastLogHour = dt.GetHour();
	WriteLogFile("OnAirApp::InitInstance");
#endif

	COnAirWnd*	pWnd = new COnAirWnd();

	CString strCmd = m_lpCmdLine;
	if( strCmd.Find("noerc",0)!=-1 )
		g_bNoLog=TRUE;

	pWnd->Create(NULL,"Digital Broadcaster 2006",WS_VISIBLE|WS_POPUP,CRect(0,0,::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN)),NULL,0);
	m_pMainWnd = pWnd;

	pWnd->SetIcon(hIcon,TRUE);
	pWnd->SetIcon(hIcon,FALSE);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);

	DirectSoundEnumerate(DSEnumCallback,this);
	DirectSoundCaptureEnumerate(DSCEnumCallback,this);
	for( int N=0; N<4; N++ )
		((CLineUpWnd *)(g_wndLineUp))->m_wndPlayer[N]->m_pDS_Main = lpDS_MAIN;


	AfxBeginThread( RemoteControlMainThread,NULL );

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
void COnAirApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// COnAirApp message handlers


void COnAirApp::InitializeGDIplus()
{
/*	int cx=GetSystemMetrics(SM_CXSCREEN);
	int cy=GetSystemMetrics(SM_CYSCREEN);
	bool bWide;

	if( cx/cy>2 )
		bWice=TRUE;
	else
		bWide=FALSE; */

	OSVERSIONINFOEX osv;
	osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFO)&osv);

	GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);

	g_fontfamilyTR	= ::new FontFamily(L"Verdana");
	g_font36		= ::new Font(g_fontfamilyTR, 30, FontStyleRegular, UnitPixel);
	g_font24		= ::new Font(g_fontfamilyTR, 20, FontStyleBold, UnitPixel);
	if( osv.dwMajorVersion>=6 )
		g_font12		= ::new Font(g_fontfamilyTR, 16, FontStyleRegular, UnitPixel);
	else
		g_font12		= ::new Font(g_fontfamilyTR, 16, FontStyleBold, UnitPixel);
	g_font14Bold	= ::new Font(g_fontfamilyTR, 12, FontStyleBold, UnitPixel);
	g_fontRythm		= ::new Font(g_fontfamilyTR, 8, FontStyleRegular, UnitPixel);
	g_fontSmallTitle= ::new Font(g_fontfamilyTR, 10, FontStyleRegular, UnitPixel);
	g_cfont24		= ::new CFont();
	
	g_brushCaptionText	= ::new SolidBrush( Color(255,255,255,255) );
	g_brushShadowText	= ::new SolidBrush( Color(192,0,0,0));
	g_brushSeparator	= ::new LinearGradientBrush(Point(0,0),Point(500,0),Color(255,0,0,255),Color(0,255,255,255));

	g_colorFace.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));

	g_cfont24->CreateFont(22,0,0,0,FW_REGULAR,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FF_ROMAN,NULL);
}

void COnAirApp::InitGlobalBitmaps()
{
	CString	strRefresh,
			strInfo,
			strRemove,
			strPFL,
			strMoveUp,
			strMoveDown,
			strNewSound,
			strNewCart,
			strLoadCart,
			strSaveCart,
			strDiscard,
			strNewSchedule,
			strBack,
			strFoward,
			strStop,
			strNews,
			strNewVoice,
			strEditSchedule,
			strEditLineUp,
			strLock,
			strExit,
			strHelp;
	int		iPos=0;
	CBitmap	*bmTemp;
	
	strRefresh.LoadString(IDS_REFRESH);
	strInfo.LoadString(IDS_INFO);
	strRemove.LoadString(IDS_REMOVE);
	strPFL.LoadString(IDS_PFL);
	strMoveUp.LoadString(IDS_MOVEUP);
	strMoveDown.LoadString(IDS_MOVEDOWN);
	strNewSound.LoadString(IDS_NEWSOUND);
	strNewCart.LoadString(IDS_NEWCART);
	strLoadCart.LoadString(IDS_LOADCART);
	strSaveCart.LoadString(IDS_SAVECART);
	strDiscard.LoadString(IDS_DISCARD);
	strNewSchedule.LoadString(IDS_NEWSCHEDULE);
	strBack.LoadString(IDS_BACK);
	strFoward.LoadString(IDS_FOWARD);
	strStop.LoadString(IDS_STOP);
	strNews.LoadString(IDS_NEWS);
	strNewVoice.LoadString(IDS_NEWVOICEINSERT);
	strEditSchedule.LoadString(IDS_EDITSCHEDULE);
	strEditLineUp.LoadString(IDS_EDITLINEUP);
	strLock.LoadString(IDS_LOCK);
	strExit.LoadString(IDS_EXIT);
	strHelp.LoadString(IDS_HELP);

	memset(g_lpstrToolLabels,0,200);

	memcpy(g_lpstrToolLabels,strRefresh,strRefresh.GetLength() );
	iPos+=strRefresh.GetLength()+1;

	memcpy(g_lpstrToolLabels+iPos,strInfo,strInfo.GetLength() );
	iPos+=strInfo.GetLength()+1;

	memcpy(g_lpstrToolLabels+iPos,strRemove,strRemove.GetLength() );
	iPos+=strRemove.GetLength()+1;

	memcpy(g_lpstrToolLabels+iPos,strPFL,strPFL.GetLength() );
	iPos+=strPFL.GetLength()+1;

	memcpy(g_lpstrToolLabels+iPos,strMoveUp,strMoveUp.GetLength() );
	iPos+=strMoveUp.GetLength()+1;

	memcpy(g_lpstrToolLabels+iPos,strMoveDown,strMoveDown.GetLength() );
	iPos+=strMoveDown.GetLength()+1;

	memcpy(g_lpstrToolLabels+iPos,strNewSound,strNewSound.GetLength() );
	iPos+=strNewSound.GetLength()+1;  // 6

	memcpy(g_lpstrToolLabels+iPos,strNewCart,strNewCart.GetLength() );
	iPos+=strNewCart.GetLength()+1;  // 7

	memcpy(g_lpstrToolLabels+iPos,strLoadCart,strLoadCart.GetLength() );
	iPos+=strLoadCart.GetLength()+1;  // 8

	memcpy(g_lpstrToolLabels+iPos,strSaveCart,strSaveCart.GetLength() );
	iPos+=strSaveCart.GetLength()+1;  // 9

	memcpy(g_lpstrToolLabels+iPos,strDiscard,strDiscard.GetLength() );
	iPos+=strDiscard.GetLength()+1;  // 10

	memcpy(g_lpstrToolLabels+iPos,strNewSchedule,strNewSchedule.GetLength() );
	iPos+=strNewSchedule.GetLength()+1;  // 11

	memcpy(g_lpstrToolLabels+iPos,strBack,strBack.GetLength() );
	iPos+=strBack.GetLength()+1;  // 12

	memcpy(g_lpstrToolLabels+iPos,strFoward,strFoward.GetLength() );
	iPos+=strFoward.GetLength()+1;  // 13

	memcpy(g_lpstrToolLabels+iPos,strStop,strStop.GetLength() );
	iPos+=strStop.GetLength()+1;  // 14

	memcpy(g_lpstrToolLabels+iPos,strNews,strNews.GetLength() );
	iPos+=strNews.GetLength()+1;  // 15

	memcpy(g_lpstrToolLabels+iPos,strNewVoice,strNewVoice.GetLength() );
	iPos+=strNewVoice.GetLength()+1;  // 16

	memcpy(g_lpstrToolLabels+iPos,strEditSchedule,strEditSchedule.GetLength() );
	iPos+=strEditSchedule.GetLength()+1;  // 17

	memcpy(g_lpstrToolLabels+iPos,strEditLineUp,strEditLineUp.GetLength() );
	iPos+=strEditLineUp.GetLength()+1;  // 18

	memcpy(g_lpstrToolLabels+iPos,strLock,strLock.GetLength() );
	iPos+=strLock.GetLength()+1;  // 19

	memcpy(g_lpstrToolLabels+iPos,strExit,strExit.GetLength() );
	iPos+=strExit.GetLength()+1;  // 20

	memcpy(g_lpstrToolLabels+iPos,strHelp,strHelp.GetLength() );
	iPos+=strHelp.GetLength()+1;  // 21

	////////////////////////////////////////////////////////////////////////
	//	Enabled toolbar bitmaps
	g_bmRefresh=new CBitmap;
	g_bmRefresh->LoadBitmap(IDB_REFRESH);

	g_bmGarbage=new CBitmap;
	g_bmGarbage->LoadBitmap(IDB_GARBAGE);

	g_ilToolEnabled = new CImageList();
	g_ilToolEnabled->Create(40,36,ILC_COLOR24|ILC_MASK,0,20);
	g_ilToolEnabled->Add(g_bmRefresh,RGB(255,255,255));
	g_ilToolEnabled->Add(g_bmGarbage,RGB(255,0,0));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_PFL);
	g_ilToolEnabled->Add(bmTemp,RGB(212,208,200));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_INFO);
	g_ilToolEnabled->Add(bmTemp,RGB(212,208,200));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEUP);
	g_ilToolEnabled->Add(bmTemp,RGB(236,233,216));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEDOWN);
	g_ilToolEnabled->Add(bmTemp,RGB(236,233,216));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW_SOUND);
	g_ilToolEnabled->Add(bmTemp,RGB(236,233,216));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOAD);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_SAVE);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_DISCARD);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEWSCHEDULE);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_BACK);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_FOWARD);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EDIT);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOCK);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EXIT);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_TOOL_QUERY);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	///////////////////////////////////////////////////////////////////////
	//	Hot toolbar bitmaps
	g_ilToolHot = new CImageList();
	g_ilToolHot->Create(40,36,ILC_COLOR24|ILC_MASK,0,20);


	// Refresh - 0
	g_bmRefreshHot = new CBitmap;
	g_bmRefreshHot->LoadBitmap(IDB_REFRESH_HOT);
	g_ilToolHot->Add(g_bmRefreshHot,RGB(255,255,255));

	// Remove - 1
	g_bmGarbageHot=new CBitmap;
	g_bmGarbageHot->LoadBitmap(IDB_GARBAGE);
	g_ilToolHot->Add(g_bmGarbageHot,RGB(255,0,0));

	// PFL - 2
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_PFL);
	g_ilToolHot->Add(bmTemp,RGB(212,208,200));

	// INFO - 3
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_INFO_HOT);
	g_ilToolHot->Add(bmTemp,RGB(212,208,200));

	// MOVE UP - 4
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEUP_HOT);
	g_ilToolHot->Add(bmTemp,RGB(236,233,216));

	// MOVE DOWN - 5
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEDOWN_HOT);
	g_ilToolHot->Add(bmTemp,RGB(236,233,216));

	// New Sound - 6
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW_SOUND);
	g_ilToolHot->Add(bmTemp,RGB(236,233,216));

	// New - 7
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));


	// Load - 8
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOAD);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));


	// Save - 9
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_SAVE);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));

	// Discard 10
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_DISCARD);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));

	// New Schedule 11
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEWSCHEDULE);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));


	// Back 12
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_BACK);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));

	// Foward 13
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_FOWARD);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));

	// Edit 14
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EDIT);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));

	// Lock 15
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOCK);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));

	// exit	16
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EXIT);
	g_ilToolHot->Add(bmTemp,RGB(255,255,255));

	// help 17
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_TOOL_QUERY);
	g_ilToolEnabled->Add(bmTemp,RGB(255,255,255));

	////////////////////////////////////////////////////////////////////////////////////////
	g_bmMusicFolder = new CBitmap();
	g_bmMusicFolder->LoadBitmap(IDB_MUSICFOLDER);

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MUSICSMALL);

	g_ilSmallIcons = new CImageList();
	g_ilSmallIcons->Create(25,25,ILC_COLOR24|ILC_MASK,0,5);
	g_ilSmallIcons->Add(bmTemp,RGB(212,208,200));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_JINGLESMALL);
	g_ilSmallIcons->Add(bmTemp,RGB(212,208,200));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_VOICEINSERT);
	g_ilSmallIcons->Add(bmTemp,RGB(255,255,255));

	///////////////////////////////////////////////////////////////////////////

	g_ilContainer = new CImageList();
	g_ilContainer->Create(30,30,ILC_COLOR24|ILC_MASK,0,10);
	
	g_bmContainerMusic=new CBitmap();
	g_bmContainerMusic->LoadBitmap(IDB_CONTAINER_MUSIC);

	g_ilContainer->Add(g_bmContainerMusic,RGB(212,208,200));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_JINGLES);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_LINEUP);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_PRODUCER);
	g_ilContainer->Add(bmTemp,RGB(212,208,200));

	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_TRAFFIC);
	g_ilContainer->Add(bmTemp,RGB(212,208,200));

	// Cartwall
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_CARTWALL);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));

	// Music folder
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_MUSICFOLDER);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));

	// Music search - 7
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_MUSICSEARCH);
	g_ilContainer->Add(bmTemp,RGB(255,255,255)); 

	// Schedulling - 8
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_SCHEDULING);
	g_ilContainer->Add(bmTemp,RGB(255,255,255)); 

	// Blocks - 9
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_BLOCKS);
	g_ilContainer->Add(bmTemp,RGB(212,208,200)); 

	// Voice Insert 10
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_VOICEINSERT);
	g_ilContainer->Add(bmTemp,RGB(212,208,200));

	// Voice Insert 11
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_AIRED);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));

	// Voice Insert 12
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_INTERNET);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));

	// Voice Insert 13
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_RMS);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));

	// Bumped traffic 14
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_CONTAINER_BUMPED);
	g_ilContainer->Add(bmTemp,RGB(255,255,255));
}

LPDIRECTSOUND COnAirApp::InitializeDirectSound(LPGUID lpguid)
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

BOOL COnAirApp::ReadConfig()
{
	HKEY hConfigKey = NULL;
	HKEY hSoftKey = NULL;
	HKEY hCompanyKey = NULL;
	HKEY hAudioKey = NULL;
	DWORD dwData;
	CString strKey;
	
	if( RegOpenKeyEx(HKEY_CURRENT_USER, _T("software"), 0, KEY_WRITE|KEY_READ,&hSoftKey) == ERROR_SUCCESS )
		if( RegOpenKeyEx(hSoftKey,_T("DigitalBroadcaster"),0, KEY_WRITE|KEY_READ,&hCompanyKey) == ERROR_SUCCESS )
			if( RegOpenKeyEx(hCompanyKey,_T("Config"),0,KEY_WRITE|KEY_READ,&hConfigKey) == ERROR_SUCCESS )
				if( RegOpenKeyEx(hConfigKey,_T("Audio"),0,KEY_WRITE|KEY_READ,&hAudioKey) == ERROR_SUCCESS )
				{
					CString strValue;
					DWORD dwType, dwCount;//, dwData;

					// Emissao
					LONG lResult = RegQueryValueEx(hAudioKey,_T("Main"),NULL,&dwType,NULL, &dwCount);
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

					// Cartwall
					lResult = RegQueryValueEx(hAudioKey,_T("Cartwall"),NULL,&dwType,NULL, &dwCount);
					if (lResult == ERROR_SUCCESS)
					{
						ASSERT(dwType == REG_SZ);
						lResult = RegQueryValueEx(hAudioKey,_T("Cartwall"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strCartwallAudio=strValue;
						else
							g_strCartwallAudio="";
					}

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

					lResult = RegQueryValueEx(hAudioKey,_T("Recorder"),NULL,&dwType,NULL, &dwCount);
					if (lResult == ERROR_SUCCESS)
					{
						ASSERT(dwType == REG_SZ);
						lResult = RegQueryValueEx(hAudioKey,_T("Recorder"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strRecorderAudio=strValue;
						else
							g_strRecorderAudio="";
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

					// Temp Folder
					lResult = RegQueryValueEx(hAudioKey,_T("TempFolder"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_SZ );
						lResult = RegQueryValueEx(hAudioKey,_T("TempFolder"),NULL,&dwType,(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
						strValue.ReleaseBuffer();
						if( lResult==ERROR_SUCCESS )
							g_strTempDir = strValue;
						else
							g_strTempDir = "C:\\temp";
					}

					// Fade to Take
					lResult = RegQueryValueEx(hAudioKey,_T("FadeToTake"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("FadeToTake"),NULL,&dwType,(LPBYTE)&dwData, &dwCount);
						
						if( lResult==ERROR_SUCCESS )
							g_iFadeToTake=dwData;
						else
							g_iFadeToTake=-1500;
					}
					
					// Fade On Intro
					lResult = RegQueryValueEx(hAudioKey,_T("FadeOnIntro"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("FadeOnIntro"),NULL,&dwType,(LPBYTE)&dwData, &dwCount);
						
						if( lResult==ERROR_SUCCESS )
							g_iFadeOnIntro=dwData;
						else
							g_iFadeOnIntro=-1000;
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

					lResult = RegQueryValueEx(hAudioKey,_T("PlayerDelay"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("PlayerDelay"),NULL,&dwType,(LPBYTE)&dwData, &dwCount);
						
						if( lResult==ERROR_SUCCESS )
							g_iDelay=dwData;
						else
							g_iDelay=0;
					} 

					lResult = RegQueryValueEx(hAudioKey,_T("Instrumental"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("Instrumental"),NULL,&dwType,(LPBYTE)&dwData, &dwCount);
						
						if( lResult==ERROR_SUCCESS )
							g_iInstrumental=dwData;
						else
							g_iInstrumental=0;
					} 
	
					strKey = "Splitter_01";
					while( RegQueryValueEx(hAudioKey,strKey,NULL,&dwType,NULL,&dwCount)==ERROR_SUCCESS )
					{
						ASSERT(dwType == REG_SZ);
						lResult = RegQueryValueEx(hAudioKey,strKey,NULL,&dwType,(LPBYTE)g_strSplitter[g_nSplitters].GetBuffer(dwCount/sizeof(TCHAR)),&dwCount);
						g_nSplitters++;
						strKey.Format("Splitter_%2d",g_nSplitters+1);
						strKey.Replace(" ","0");
					}
					
                    lResult = RegQueryValueEx(hAudioKey,_T("FastStart"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType==REG_DWORD );
						lResult = RegQueryValueEx(hAudioKey,_T("FastStart"),NULL,&dwType,(LPBYTE)&dwData,&dwCount );

						if( lResult==ERROR_SUCCESS )
							g_bFastStart=dwData;
					}

					// Mixer exists ----------------------------------------------------------------------
					lResult = RegQueryValueEx(hAudioKey,_T("Mixer"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType==REG_DWORD);
						lResult = RegQueryValueEx(hAudioKey,_T("Mixer"),NULL,&dwType,(LPBYTE)&dwData,&dwCount);

						if( lResult==ERROR_SUCCESS )
							g_bMixer=(BOOL)dwData;
					}

					// Mixer ID --------------------------------------------------------------------------
					lResult = RegQueryValueEx(hAudioKey,_T("MixerID"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType==REG_DWORD);
						lResult = RegQueryValueEx(hAudioKey,_T("MixerID"),NULL,&dwType,(LPBYTE)&dwData,&dwCount);

						if( lResult==ERROR_SUCCESS )
							g_dwMixerID=dwData;
					}
	
					// Mixer Line ID ----------------------------------------------------------------------
					lResult = RegQueryValueEx(hAudioKey,_T("MixerLineID"),NULL,&dwType,NULL,&dwCount);
					if( lResult==ERROR_SUCCESS )
					{
						ASSERT(dwType==REG_DWORD);
						lResult = RegQueryValueEx(hAudioKey,_T("MixerLineID"),NULL,&dwType,(LPBYTE)&dwData,&dwCount);

						if( lResult==ERROR_SUCCESS )
							g_dwMixerLineID=dwData;
					}
				}

	if( hConfigKey!=NULL ) RegCloseKey(hConfigKey);
	if( hCompanyKey!=NULL ) RegCloseKey(hCompanyKey);
	if( hSoftKey!=NULL ) RegCloseKey(hSoftKey);

	return TRUE;
}

BOOL CALLBACK COnAirApp::DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	COnAirApp *This=(COnAirApp *)lpContext;
	LPDIRECTSOUND	lpTempDS;

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

	if( (g_strMainAudio==strTemp) ||
		(g_strPFLAudio==strTemp) ||
		(g_strCartwallAudio==strTemp) )
	{
		lpTempDS=This->InitializeDirectSound(lpGuid);

		if( g_strMainAudio==strTemp)
			lpDS_MAIN=lpTempDS;

		if( g_strPFLAudio==strTemp)
			lpDS_PFL=lpTempDS;

		if( g_strCartwallAudio==strTemp)
			lpDS_CARTWALL = lpTempDS;
	}
	return TRUE;
}

BOOL CALLBACK COnAirApp::DSCEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	COnAirApp *This=(COnAirApp *)lpContext;

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

	if( (g_strRecorderAudio==strTemp) )
		g_pDS_Capture = This->InitializeDirectSoundCapture(lpGuid);

	return TRUE;
}

LPDIRECTSOUNDCAPTURE COnAirApp::InitializeDirectSoundCapture(LPGUID lpGuid)
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

void COnAirApp::GetComputerNameAndID()
{
	CString strTemp;
	DWORD	Size=100;

	GetComputerName(strTemp.GetBuffer(100),&Size);
	strTemp.ReleaseBuffer();
	g_strComputerName = strTemp;

	g_lComputerID = GetComputerID( g_strComputerName);
}


// -----------------------------------------------------------------------------------------------------------------------------------------------
//	Remote control section
//
//
//		Main Control thread

UINT COnAirApp::RemoteControlMainThread(LPVOID)
{
	HANDLE	hPipe;
	BOOL	bConnected;
	CString	strPipeName = "\\\\.\\pipe\\OnAir_Splitter";

	while( TRUE )
	{
		hPipe = CreateNamedPipe(strPipeName,                                      
					PIPE_ACCESS_DUPLEX,
					PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_WAIT,
					PIPE_UNLIMITED_INSTANCES,
					SIZEOFSPLITTERMSG,
					SIZEOFSPLITTERMSG,
					10000,
					NULL );

		if( hPipe==INVALID_HANDLE_VALUE )
		{
			AfxMessageBox("Impossivel iniciar canal de comunicação");
		}
		else
		{
			bConnected = ConnectNamedPipe(hPipe,NULL) ?	TRUE : (GetLastError()==ERROR_PIPE_CONNECTED);
			if( bConnected )
				AfxBeginThread(RemoteControlCommunicationThread,(LPVOID)hPipe);
			else
				CloseHandle(hPipe);
		}
	}

	return( 0 );
}


// RemoteControlCommunicationThread
// This method is responsilble for reading and dispatch remote control messages

UINT COnAirApp::RemoteControlCommunicationThread( LPVOID lpPipe )
{
	HANDLE	hPipe = (HANDLE) lpPipe;
	BOOL	bSuccess;
	typeSplitterMsg	Msg;
	DWORD	nCount=0;

	while( TRUE )
	{
		bSuccess = ReadFile( hPipe,(LPVOID)&Msg,SIZEOFSPLITTERMSG,&nCount,NULL);
		if( (!bSuccess) || (nCount==0) )
			break;

		COleDateTime	dt = COleDateTime::GetCurrentTime();
		CString			strDate,
						strTime;

		strDate.Format("%4d-%2d-%2d",dt.GetYear(),dt.GetMonth(),dt.GetDay());
		strDate.Replace(" ","0");
		strTime.Format("%2d:%2d:%2d",dt.GetHour(),dt.GetMinute(),dt.GetSecond());
		strTime.Replace(" ","0");

#ifdef __DEBUG_LOG
		CString strLog;

		strLog.Format("&s - %s",Msg.strSrc,Msg.pstrMessage);
		WriteLogFile(strLog);
#endif
		
		if( Msg.wType == TYPE_BLOCK )
		{
			((CLineUpWnd *)g_wndLineUp)->RemoteControl(Msg);
		}

	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	return 0;
}
