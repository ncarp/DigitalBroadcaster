// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Config.h"
#include "ConfigDlg.h"
#include <mmreg.h>
#include <dsound.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString strAudioMusica;
extern CString strAudioMonicao;
extern CString strAudioCartwall;
extern CString strAudioRMs;
extern CString strAudioTakes;
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

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CConfigDlg::IDD)

	, m_strMixer(_T(""))
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_strMusica = _T("");
	m_strMonicao = _T("");
	m_strCartwall = _T("");
	m_strTakes = _T("");
	m_strURL = _T("");
	m_iFateToTake = 0;
	m_iOnIntro = 0;
	m_strTempDir = _T("");
	m_Valor2 = 0;
	m_Valor1 = 0;
	m_iAvg = 0;
	m_iSlow = 0;
	m_iSlowAvg = 0;
	m_iDelay = 0;
	m_iInstr = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pwfx = NULL;
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_INSTV, m_cInstV);
	DDX_Control(pDX, IDC_INSTR, m_cInstr);
	DDX_Control(pDX, IDC_DELAY, m_cDelay);
	DDX_Control(pDX, IDC_DELAYV, m_cDelayV);
	DDX_Control(pDX, IDC_SLOW, m_cSlow);
	DDX_Control(pDX, IDC_AVG, m_cAvg);
	DDX_Control(pDX, IDC_SLOWAVGV, m_cSlowAvgV);
	DDX_Control(pDX, IDC_SLOWAVG, m_cSlowAvg);
	DDX_Control(pDX, IDC_SLOWV, m_cSlowV);
	DDX_Control(pDX, IDC_AVGV, m_cAvgV);
	DDX_Control(pDX, IDC_PARAM, m_cParam);
	DDX_Control(pDX, IDC_FORMAT, m_cFormat);
	DDX_Control(pDX, IDC_ONINTRO, m_ctrlOnIntro);
	DDX_Control(pDX, IDC_FADE, m_ctrlFadeToTake);
	DDX_Control(pDX, IDC_GRAVACAOTAKES, m_Takes);
	DDX_Control(pDX, IDC_CARTWALL, m_Cartwall);
	DDX_Control(pDX, IDC_AUDIOMONICAO, m_Monicao);
	DDX_Control(pDX, IDC_AUDIOMUSICA, m_Musica);
	DDX_CBString(pDX, IDC_AUDIOMUSICA, m_strMusica);
	DDX_CBString(pDX, IDC_AUDIOMONICAO, m_strMonicao);
	DDX_CBString(pDX, IDC_CARTWALL, m_strCartwall);
	DDX_CBString(pDX, IDC_GRAVACAOTAKES, m_strTakes);
	DDX_Text(pDX, IDC_URL, m_strURL);
	DDX_Slider(pDX, IDC_FADE, m_iFateToTake);
	DDX_Slider(pDX, IDC_ONINTRO, m_iOnIntro);
	DDX_Text(pDX, IDC_TEMP, m_strTempDir);
	DDX_Text(pDX, IDC_VALOR2, m_Valor2);
	DDX_Text(pDX, IDC_VALOR1, m_Valor1);
	DDX_Slider(pDX, IDC_AVG, m_iAvg);
	DDX_Slider(pDX, IDC_SLOW, m_iSlow);
	DDX_Slider(pDX, IDC_SLOWAVG, m_iSlowAvg);
	DDX_Slider(pDX, IDC_DELAY, m_iDelay);
	DDX_Slider(pDX, IDC_INSTR, m_iInstr);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MIXER, m_cMixer);
	DDX_CBString(pDX, IDC_MIXER, m_strMixer);
}

BEGIN_MESSAGE_MAP(CConfigDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_FORMAT, OnSelchangeFormat)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_AUDIOMUSICA, &CConfigDlg::OnCbnSelchangeAudiomusica)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	DirectSoundEnumerate(DSEnumCallback,this);
	DirectSoundCaptureEnumerate(DSEnumCaptureCallback,this);

	acmDriverEnum( acmDriverEnumCallback,(DWORD)this,NULL);

	AddMixers();

	long Pos=m_Musica.FindStringExact(-1,strAudioMusica);
	m_Musica.SetCurSel(Pos);

	Pos=m_Monicao.FindStringExact(-1,strAudioMonicao);
	m_Monicao.SetCurSel(Pos);

	Pos=m_Cartwall.FindStringExact(-1,strAudioCartwall);
	m_Cartwall.SetCurSel(Pos);

	Pos=m_Takes.FindStringExact(-1,strAudioTakes);
	m_Takes.SetCurSel(Pos);

	m_ctrlFadeToTake.SetRange(-3000,0);
	m_ctrlFadeToTake.SetPos(m_iFateToTake);

	m_ctrlOnIntro.SetRange(-3000,0);
	m_ctrlOnIntro.SetPos(m_iOnIntro);

	m_cSlow.SetRange(0,250,TRUE);
	m_cSlow.SetPos(m_iSlow);

	m_cSlowAvg.SetRange(0,250,TRUE);
	m_cSlowAvg.SetPos(m_iSlowAvg);

	m_cAvg.SetRange(0,250,TRUE);
	m_cAvg.SetPos(m_iAvg);

	m_cDelay.SetRange(0,120,TRUE);
	m_cDelay.SetPos(m_iDelay);
	CString str;

	str.Format("%d bmp",m_iSlow);
	m_cSlowV.SetWindowText(str);

	str.Format("%d bmp",m_iSlowAvg);
	m_cSlowAvgV.SetWindowText(str);

	str.Format("%d bmp",m_iAvg);
	m_cAvgV.SetWindowText(str);

	m_cInstr.SetRange(0,300,TRUE);
	m_cInstr.SetPos(m_iInstr);
	str.Format("%d sec",m_iInstr);
	m_cInstV.SetWindowText(str);

	Pos = m_cFormat.FindStringExact(-1,m_strWaveFormat);
	m_cFormat.SetCurSel(Pos);

	OnSelchangeFormat();
	Pos = m_cParam.FindStringExact(-1,m_strWaveParam);
	m_cParam.SetCurSel(Pos);

	if( m_bMixer )
	{
	}
	else
	{
		m_cMixer.EnableWindow(FALSE);
		m_cMixerLine.EnableWindow(FALSE);
	}
	 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConfigDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConfigDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CALLBACK CConfigDlg::DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	CConfigDlg *This=(CConfigDlg *)lpContext;
	CString strTemp;
	int Count=1;
	int Pos = This->m_Monicao.FindStringExact(-1,lpcstrDescription);
	
	strTemp.Format("%s",lpcstrDescription);

	while( Pos!=CB_ERR )
	{
		Count++;
		strTemp.Format("%s (%d)",lpcstrDescription,Count);
		Pos = This->m_Monicao.FindStringExact(-1,strTemp);
	}
	

	This->m_Monicao.AddString(strTemp);
	This->m_Musica.AddString(strTemp);
	This->m_Cartwall.AddString(strTemp);

	return TRUE;
}

BOOL CALLBACK CConfigDlg::DSEnumCaptureCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	CConfigDlg *This=(CConfigDlg *)lpContext;
	CString strTemp;
	int Count=1;
	int Pos = This->m_Takes.FindStringExact(-1,lpcstrDescription);
	
	strTemp.Format("%s",lpcstrDescription);

	while( Pos!=CB_ERR )
	{
		Count++;
		strTemp.Format("%s (%d)",lpcstrDescription,Count);
		Pos = This->m_Takes.FindStringExact(-1,strTemp);
	}

	This->m_Takes.AddString(strTemp);
	return TRUE;
}

void CConfigDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UpdateData();
	
	m_Valor1=m_iFateToTake;
	m_Valor2=m_iOnIntro;

	if( m_iSlowAvg < m_iSlow )
		m_iSlowAvg=m_iSlow;

	if( m_iAvg < m_iSlowAvg )
		m_iAvg = m_iSlowAvg;

	UpdateData(FALSE);

	CString str;

	str.Format("%d bmp",m_iSlow);
	m_cSlowV.SetWindowText(str);

	str.Format("%d bmp",m_iSlowAvg);
	m_cSlowAvgV.SetWindowText(str);

	str.Format("%d bmp",m_iAvg);
	m_cAvgV.SetWindowText(str);

	str.Format("%d sec",m_iDelay);
	m_cDelayV.SetWindowText(str);
	
	str.Format("%d sec",m_iInstr);
	m_cInstV.SetWindowText(str);

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CALLBACK CConfigDlg::acmDriverEnumCallback( HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport )
{
	ACMDRIVERDETAILS	add;
	CConfigDlg			*This = (CConfigDlg *)dwInstance;
	int					nPos;

	if( fdwSupport & ACMDRIVERDETAILS_SUPPORTF_CODEC )
	{
		add.cbStruct = sizeof(ACMDRIVERDETAILS);

		acmDriverDetails(hadid,&add,0);

		nPos=This->m_cFormat.AddString(add.szLongName);
		This->m_cFormat.SetItemData(nPos,(DWORD)(UINT)hadid);
	}

	return TRUE;
}

void CConfigDlg::OnSelchangeFormat() 
{
	MMRESULT	mmr;
	DWORD		cbwfx;

	UpdateData();

	int nPos=m_cFormat.GetCurSel();
	if( nPos==CB_ERR )
		return;
	
/*	if( m_nSample==-1 )
		return;

	switch( m_nSample )
	{
	case 0:
		m_dwSampleRate = 8000;
		break;
	case 1:
		m_dwSampleRate = 16000;
		break;
	case 2:
		m_dwSampleRate = 32000;
		break;
	case 3:
		m_dwSampleRate = 44100;
		break;
	case 4:
		m_dwSampleRate = 48000;
		break;
	}
*/
	HACMDRIVERID		hadid = (HACMDRIVERID)(UINT)m_cFormat.GetItemData(nPos);
	HACMDRIVER			had;
	ACMFORMATDETAILS	afd;	
	LPWAVEFORMATEX		pwfx;

	ACMDRIVERDETAILS add;
	add.cbStruct = sizeof(ACMDRIVERDETAILS);
	mmr=acmDriverDetails(hadid,&add,0L);

	mmr=acmDriverOpen(&had,hadid,0);
	mmr = acmMetrics((HACMOBJ)had, ACM_METRIC_MAX_SIZE_FORMAT, &cbwfx);
	if (MMSYSERR_NOERROR != mmr)
		return ;

	pwfx = (LPWAVEFORMATEX)malloc(cbwfx);
	if( pwfx == NULL )
		return;

	memset(&afd, 0, sizeof(afd));

	afd.cbStruct = sizeof(afd);
	afd.dwFormatTag = WAVE_FORMAT_UNKNOWN;
	afd.dwFormatIndex=0;
	afd.cbwfx = cbwfx;
	afd.pwfx = pwfx;

	pwfx->cbSize = (UINT)cbwfx-sizeof(WAVEFORMATEX);
	pwfx->nAvgBytesPerSec = 176400;
	pwfx->nBlockAlign = 4;
	pwfx->wBitsPerSample = 16;
	pwfx->nChannels = 2;
	pwfx->nSamplesPerSec = 44100;
	pwfx->wFormatTag = WAVE_FORMAT_PCM;

	m_cParam.ResetContent();
	mmr=acmFormatEnum(had,
		&afd,acmFormatEnumCallback,
		(DWORD)&m_cParam,
		ACM_FORMATENUMF_CONVERT  );	

	if( m_cParam.GetCount()==0 )
	{
		ACMFORMATTAGDETAILS	aftd;

		aftd.cbStruct = sizeof(ACMFORMATTAGDETAILS);
		aftd.dwFormatTagIndex=1;
		mmr=acmFormatDetails(had,&afd,ACM_FORMATTAGDETAILSF_INDEX);
	}

	acmDriverClose(had,0);
}

BOOL CALLBACK CConfigDlg::acmFormatEnumCallback( HACMDRIVERID hadid, LPACMFORMATDETAILS pafd, DWORD dwInstance, DWORD fdwSupport )
{
	CComboBox *param = (CComboBox *)dwInstance;
	int		nPos;
	LPVOID	lpData = malloc(pafd->cbwfx);

	memcpy(lpData,pafd->pwfx,pafd->cbwfx);

	nPos = param->AddString(pafd->szFormat);
	param->SetItemData(nPos,(DWORD)lpData);

	return TRUE;
}

void CConfigDlg::OnOK() 
{
	int nPos = m_cParam.GetCurSel();
	
	if( nPos == CB_ERR )
		return;

	m_cFormat.GetWindowText( m_strWaveFormat );
	m_cParam.GetWindowText( m_strWaveParam );
	pwfx = (LPWAVEFORMATEX)m_cParam.GetItemData(nPos);

	nPos = m_cMixer.GetCurSel();
	if( nPos==CB_ERR )
	{
		m_bMixer=0;
		m_lMixerID=0;
		m_lMixerLineID=0;
	}
	else
	{
		typeMixerLine *pMixer=(typeMixerLine *)m_cMixer.GetItemData(nPos);

		m_bMixer=1;
		m_lMixerID = pMixer->dwMixerID;
		m_lMixerLineID = pMixer->dwLineID;
	}

	CPropertyPage::OnOK();
}

bool CConfigDlg::AddMixers(void)
{
	int		nMixer = mixerGetNumDevs(),
			nLine,
			nLineCount;
	long	Pos;
	MIXERCAPS	MixerCaps;
	MIXERLINE	MixerLine;
	MMRESULT	uError;

	for( int Cont=0; Cont<nMixer; Cont++ )
	{
		mixerGetDevCaps(Cont,&MixerCaps,sizeof(MIXERCAPS));

		MixerLine.cbStruct=sizeof(MIXERLINE);
		MixerLine.dwDestination=0;
			
		uError=mixerGetLineInfo((HMIXEROBJ)Cont,&MixerLine,MIXER_GETLINEINFOF_DESTINATION|MIXER_OBJECTF_MIXER);
		nLineCount = MixerLine.cConnections;

		for( nLine=0; nLine<nLineCount; nLine++ )
		{
			MixerLine.cbStruct=sizeof(MIXERLINE);
			MixerLine.dwDestination=0;
			MixerLine.dwSource=nLine;
			uError=mixerGetLineInfo((HMIXEROBJ)Cont,&MixerLine,MIXER_GETLINEINFOF_SOURCE|MIXER_OBJECTF_MIXER);
			if( uError==MMSYSERR_NOERROR )
			{
				typeMixerLine *pLine = new typeMixerLine;
				pLine->dwLineID = MixerLine.dwLineID;
				pLine->dwMixerID = Cont;

				Pos=m_cMixer.AddString(CString(MixerCaps.szPname)+" - "+CString(MixerLine.szName));
				m_cMixer.SetItemData(Pos,(DWORD)pLine);
			}
		}
	}
	return true;
}

void CConfigDlg::OnCbnSelchangeAudiomusica()
{
	// TODO: Add your control notification handler code here
}
