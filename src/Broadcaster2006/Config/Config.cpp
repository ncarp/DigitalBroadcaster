// Config.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Config.h"
#include "ConfigProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString strAudioMusica;
CString strAudioMonicao;
CString strAudioCartwall;
CString strAudioRMs;
CString strAudioTakes;
CString	strURL;
CString strTempDir;
CString	strWaveFormat;
CString strWaveParam;
int		iFadeToTake;
int		iFadeOnIntro;
int		iParamSize;
int		g_iSlow,
		g_iSlowAverage,
		g_iAverage;
long	g_iDelay,
		g_iInstrumental,
		g_bMixer,
		g_lMixerID,
		g_lMixerLineID;

LPWAVEFORMATEX pwfx;

/////////////////////////////////////////////////////////////////////////////
// CConfigApp

BEGIN_MESSAGE_MAP(CConfigApp, CWinApp)
	//{{AFX_MSG_MAP(CConfigApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigApp construction

CConfigApp::CConfigApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CConfigApp object

CConfigApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CConfigApp initialization

BOOL CConfigApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(_T("DigitalBroadcaster\\"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	strAudioMusica	= GetProfileString("Audio","Main");
	strAudioMonicao = GetProfileString("Audio","PFL");
	strAudioCartwall= GetProfileString("Audio","Cartwall");
	strAudioTakes	= GetProfileString("Audio","Recorder");
	strURL			= GetProfileString("Audio","BaseURL");
	strTempDir		= GetProfileString("Audio","TempFolder","C:\\Temp");
	strWaveFormat	= GetProfileString("Audio","AudioFormat");
	strWaveParam	= GetProfileString("Audio","AudioParam");

	iFadeToTake		= GetProfileInt("Audio","FadeToTake",-2000);
	iFadeOnIntro	= GetProfileInt("Audio","FadeOnIntro",-1000);
	iParamSize		= GetProfileInt("Audio","AudioParamSize",0);
	
	g_iSlow			= GetProfileInt("Audio","MaxSlow",25);
	g_iSlowAverage	= GetProfileInt("Audio","MaxSlowAverage",75);
	g_iAverage		= GetProfileInt("Audio","MaxAverage",125);

	g_iDelay		= GetProfileInt("Audio","PlayerDelay",0);
	g_iInstrumental = GetProfileInt("Audio","Instrumental",0);

	g_bMixer		= GetProfileInt("Audio","Mixer",0);
	g_lMixerID		= GetProfileInt("Audio","MixerID",0);
	g_lMixerLineID	= GetProfileInt("Audio","MixerLineID",0);

	if( iParamSize!=0 )
	{
		pwfx = (LPWAVEFORMATEX)malloc(iParamSize);
		GetProfileBinary("Audio","WAVEFORMATEX",(LPBYTE *)&pwfx,(UINT *)&iParamSize);
	}

	CConfigProperty dlg(IDS_APPTITLE,NULL);
	m_pMainWnd = &dlg;
//	m_pMainWnd->SetIcon(LoadIcon(IDR_MAINFRAME),FALSE);

	theApp.LoadIcon(IDR_MAINFRAME);
	
	dlg.dlAudio->m_strURL=strURL;
	dlg.dlAudio->m_strTempDir=strTempDir;
	dlg.dlAudio->m_iFateToTake=iFadeToTake;
	dlg.dlAudio->m_iOnIntro=iFadeOnIntro;
	dlg.dlAudio->m_Valor1=iFadeToTake;
	dlg.dlAudio->m_Valor2=iFadeOnIntro;
	dlg.dlAudio->m_strWaveFormat = strWaveFormat;
	dlg.dlAudio->m_strWaveParam = strWaveParam;
	dlg.dlAudio->m_iSlow = g_iSlow;
	dlg.dlAudio->m_iSlowAvg = g_iSlowAverage;
	dlg.dlAudio->m_iAvg = g_iAverage;
	dlg.dlAudio->m_iDelay = g_iDelay/1000;
	dlg.dlAudio->m_iInstr = g_iInstrumental;
	dlg.dlAudio->m_bMixer = g_bMixer;
	dlg.dlAudio->m_lMixerID = g_lMixerID;
	dlg.dlAudio->m_lMixerLineID = g_lMixerLineID;

	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		WriteProfileString("Audio","Main",dlg.dlAudio->m_strMusica);
		WriteProfileString("Audio","PFL",dlg.dlAudio->m_strMonicao);
		WriteProfileString("Audio","Cartwall",dlg.dlAudio->m_strCartwall);
		WriteProfileString("Audio","Recorder",dlg.dlAudio->m_strTakes);
		WriteProfileString("Audio","BaseURL",dlg.dlAudio->m_strURL);
		WriteProfileString("Audio","TempFolder",dlg.dlAudio->m_strTempDir);
		WriteProfileString("Audio","AudioFormat",dlg.dlAudio->m_strWaveFormat);
		WriteProfileString("Audio","AudioParam",dlg.dlAudio->m_strWaveParam);
		WriteProfileInt("Audio","FadeToTake",dlg.dlAudio->m_iFateToTake);
		WriteProfileInt("Audio","FadeOnIntro",dlg.dlAudio->m_iOnIntro);

		WriteProfileInt( "Audio","AudioParamSize",dlg.dlAudio->pwfx->cbSize+sizeof(WAVEFORMATEX) );
		WriteProfileBinary( "Audio","WAVEFORMATEX",(LPBYTE)dlg.dlAudio->pwfx,dlg.dlAudio->pwfx->cbSize+sizeof(WAVEFORMATEX) );

		WriteProfileInt("Audio","MaxSlow",dlg.dlAudio->m_iSlow);
		WriteProfileInt("Audio","MaxSlowAverage",dlg.dlAudio->m_iSlowAvg);
		WriteProfileInt("Audio","MaxAverage",dlg.dlAudio->m_iAvg);

		WriteProfileInt("Audio","PlayerDelay",dlg.dlAudio->m_iDelay*1000);

		WriteProfileInt("Audio","Instrumental",dlg.dlAudio->m_iInstr);

		WriteProfileInt("Audio","Mixer",dlg.dlAudio->m_bMixer);
		WriteProfileInt("Audio","MixerID",dlg.dlAudio->m_lMixerID);
		WriteProfileInt("Audio","MixerLineID",dlg.dlAudio->m_lMixerLineID);
		WriteProfileString("Audio","MixerName",dlg.dlAudio->m_strMixer);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
