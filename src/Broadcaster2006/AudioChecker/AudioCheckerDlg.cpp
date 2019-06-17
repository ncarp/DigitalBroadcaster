// AudioCheckerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AudioChecker.h"
#include "AudioCheckerDlg.h"
#include "..\include\RSMusicTracks.h"
#include "..\include\rsviewmusicfull.h"
#include "..\OnAir\RSViewJinglesDataOnAir.h"
#include "..\include\rsviewspotsfull.h"
#include "..\include\rsviewrms.h"
#include ".\audiocheckerdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IDirectSound *g_pDS_MAIN=NULL,
			 *g_pDS_PFL;
LPDIRECTSOUNDCAPTUREBUFFER	g_pDS_CaptureBuffer=NULL;
LPDIRECTSOUNDBUFFER g_pDSB_Primary;
HANDLE				g_hCapture[3];
LPWAVEFORMATEX		g_pwfx;
CString		g_strMainConnect="Broadcaster",
			g_strTempDir="C:\\Temp";
char		g_lpstrToolLabels[250];
CImageList	*g_ilToolBar;
CImageList	*g_ilTree;
CImageList	*g_ImageListToolHot,
			*g_ImageListToolEnabled;

CRITICAL_SECTION g_csMPEG;
CRITICAL_SECTION csSAMPLE;
CRITICAL_SECTION g_csEndACM;
CRITICAL_SECTION csDB;
CRITICAL_SECTION csACM;

CWnd		*g_wndLineUp;
CWnd		*g_wndCartwall;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAudioCheckerDlg dialog



CAudioCheckerDlg::CAudioCheckerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioCheckerDlg::IDD, pParent)
	, m_bMusic(FALSE)
	, m_bJingles(FALSE)
	, m_bSpots(FALSE)
	, m_bRMs(FALSE)
	, m_bDecompress(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bChecking = FALSE;
}

void CAudioCheckerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MUSIC, m_cMusic);
	DDX_Check(pDX, IDC_MUSIC, m_bMusic);
	DDX_Control(pDX, IDC_JINGLES, m_cJingles);
	DDX_Check(pDX, IDC_JINGLES, m_bJingles);
	DDX_Check(pDX, IDC_SPOTS, m_bSpots);
	DDX_Control(pDX, IDC_SPOTS, m_cSpots);
	DDX_Control(pDX, IDC_PROGRESS_FILE, m_cProgressFile);
	DDX_Control(pDX, IDC_PROGRESS_TOTAL, m_cProgressTotal);
	DDX_Control(pDX, IDC_PATH, m_cPath);
	DDX_Control(pDX, IDC_FILE, m_cFile);
	DDX_Control(pDX, IDC_DATAFILE, m_cDatabase);
	DDX_Control(pDX, IDOK, m_cOK);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDC_RMS, m_cRMs);
	DDX_Check(pDX, IDC_RMS, m_bRMs);
	DDX_Check(pDX, IDC_DECOMPRESS, m_bDecompress);
}

BEGIN_MESSAGE_MAP(CAudioCheckerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CAudioCheckerDlg message handlers

BOOL CAudioCheckerDlg::OnInitDialog()
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

	g_pDS_MAIN = InitializeDirectSound(NULL);
	InitializeCriticalSection( &g_csEndACM );
	InitializeCriticalSection( &g_csMPEG);

	m_lLastMusicID = theApp.GetProfileInt("AudioCheck","MusicID",0);
	m_lLastJingleID = theApp.GetProfileInt("AudioCheck","JingleID",0);
	m_lLastSpotID = theApp.GetProfileInt("AudioCheck","SpotID",0);
	m_lLastRMID = theApp.GetProfileInt("AudioCheck","RMID",0);

	if( theApp.GetProfileInt("AudioCheck","MusicCheck",0)==1 )
	{
		CRSViewMusicFull rs("Broadcaster");

		rs.m_strFilter.Format("ID = %d",m_lLastMusicID);
		rs.Open();

		if( rs.GetRecordCount()!=0 )
		{
			CString strFile;
			rs.m_Path.TrimRight();
			rs.m_Artist.TrimRight();
			rs.m_Title.TrimRight();
			rs.m_FileType.TrimRight();

			strFile.Format("%s\\%s - %s%s",rs.m_Path,rs.m_Artist,rs.m_Title,rs.m_FileType);

			if( AfxMessageBox(strFile+"\nA ultima musica parece ter provocado um erro na descompressão. Deseja eliminar o ficheiro?",MB_YESNO)==IDYES )
			{
				DeleteFile(strFile);
			}
		}
	}
	
	if( theApp.GetProfileInt("AudioCheck","JingleCheck",0)==1 )
	{
		CRSViewJinglesDataOnAir rs("Broadcaster");

		rs.m_strFilter.Format("ID = %d",m_lLastJingleID);
		rs.Open();

		if( rs.GetRecordCount()!=0 )
		{
			CString strFile;
			rs.m_Path.TrimRight();
			rs.m_FileName.TrimRight();

			strFile.Format("%s\\%s",rs.m_Path,rs.m_FileName);

			if( AfxMessageBox(strFile+"\nO ultimo Jingle parece ter provocado um erro na descompressão. Deseja eliminar o ficheiro?",MB_YESNO)==IDYES )
			{
				DeleteFile(strFile);
			}
		}
	}

	if( theApp.GetProfileInt("AudioCheck","SpotCheck",0)==1 )
	{
		CRSViewSpotsFull rs("Broadcaster");

		rs.m_strFilter.Format("ID = %d",m_lLastSpotID);
		rs.Open();

		if( rs.GetRecordCount()!=0 )
		{
			CString strFile;
			rs.m_Path.TrimRight();
			rs.m_FileName.TrimRight();

			strFile.Format("%s\\%s",rs.m_Path,rs.m_FileName);

			if( AfxMessageBox(strFile+"\nO ultimo Spot parece ter provocado um erro na descompressão. Deseja eliminar o ficheiro?",MB_YESNO)==IDYES )
			{
				DeleteFile(strFile);
			}
		}
	}

	if( theApp.GetProfileInt("AudioCheck","RMCheck",0)==1 )
	{
		CRSViewRms rs("Broadcaster");

		rs.m_strFilter.Format("ID = %d",m_lLastRMID);
		rs.Open();

		if( rs.GetRecordCount()!=0 )
		{
			CString strFile;
			rs.m_Path.TrimRight();
			rs.m_FileName.TrimRight();

			strFile.Format("%s\\%s",rs.m_Path,rs.m_FileName);

			if( AfxMessageBox(strFile+"\nO ultimo RM parece ter provocado um erro na descompressão. Deseja eliminar o ficheiro?",MB_YESNO)==IDYES )
			{
				DeleteFile(strFile);
			}
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAudioCheckerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAudioCheckerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAudioCheckerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAudioCheckerDlg::OnOK()
{
	UpdateData();

	m_cOK.EnableWindow(FALSE);
	m_cMusic.EnableWindow(FALSE);
	m_cJingles.EnableWindow(FALSE);
	m_cSpots.EnableWindow(FALSE);
	m_cRMs.EnableWindow(FALSE);

	m_bChecking = TRUE;

	if( m_bMusic )
		CheckMusicFiles();

	if( m_bJingles )
		CheckJingleFiles();

	if( m_bSpots )
		CheckSpotFiles();

	if( m_bRMs )
		CheckRMFiles();

	CDialog::OnOK();
}

void CAudioCheckerDlg::CheckMusicFiles(void)
{
	MSG Msg;
	CString strFile,
			strSQL;
	CRSMusicTracks rsMusic("Broadcaster");
	CRSViewMusicFull rs("Broadcaster");
	CDatabase db;
	HRESULT hr;

	db.Open("Broadcaster");

	rsMusic.m_strFilter="ID=0";
	rsMusic.Open();

	rs.m_strSort = "ID DESC";
	rs.Open(CRecordset::dynaset);

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}
	
	m_cProgressTotal.SetRange32(0,rs.m_ID);

	rs.m_strFilter.Format("ID > %d AND Activ=1",m_lLastMusicID);
	rs.m_strSort="ID";
	rs.Requery();

	m_cDatabase.SetWindowText("Discografia");

	m_bChecking = TRUE;

	while((!rs.IsEOF()) && (m_bChecking))
	{
		theApp.WriteProfileInt("AudioCheck","MusicID",rs.m_ID);
		theApp.WriteProfileInt("AudioCheck","MusicCheck",1);
		m_lLastMusicID = rs.m_ID;

		m_cProgressTotal.SetPos(rs.m_ID);
		rs.m_Artist.TrimRight();
		rs.m_Title.TrimRight();
		rs.m_Path.TrimRight();
		rs.m_FileType.TrimRight();

		m_cPath.SetWindowText(rs.m_Path);
		m_cFile.SetWindowText(rs.m_Artist+" - "+rs.m_Title+rs.m_FileType);
		
		strFile.Format("%s\\%s - %s%s",rs.m_Path,rs.m_Artist,rs.m_Title,rs.m_FileType);

//		AfxMessageBox(strFile);

		rs.MoveNext();

		rsMusic.m_strFilter.Format("ID=%d",m_lLastMusicID);
		rsMusic.Requery();
		rsMusic.Edit();
		rsMusic.m_Activ=0;
		rsMusic.Update();

		m_pSound=new CAudioStream(g_pDS_MAIN,this);

		m_pSound->SetFile(strFile.GetBuffer(0));
		m_pSound->m_pbm = NULL;
		m_pSound->m_xres=1.0f;
		m_pSound->m_dwSleep=1;
		m_pSound->m_bDecompressAll=TRUE;
		hr=m_pSound->CueSound();

		if( (hr==S_OK) && (m_bDecompress) )
		{
			m_pSound->SetPosition(0);

			m_cProgressFile.SetRange32(0,m_pSound->m_dwSrcSize);
			m_cProgressFile.SetPos(0);

			while( m_pSound->IsDecompressing() )
			{
				m_cProgressFile.SetPos(m_pSound->m_dwTotalBytesRead);
				while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
				Sleep(5);
			}
		}

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		delete m_pSound;

		if( hr==S_OK )
		{
			rsMusic.Requery();
			rsMusic.Edit();
			rsMusic.m_Activ=1;
			rsMusic.Update();
		}
		theApp.WriteProfileInt("AudioCheck","MusicCheck",0);
	}
}


LPDIRECTSOUND CAudioCheckerDlg::InitializeDirectSound(LPGUID lpguid)
{
	DSBUFFERDESC	dsbDesc;
	WAVEFORMATEX	WaveFormat;
	LPDIRECTSOUND	lpds;

	if( DirectSoundCreate(lpguid,&lpds,NULL)!=DS_OK )
		return FALSE;

   	if( lpds->SetCooperativeLevel(m_hWnd,DSSCL_PRIORITY)!=DS_OK )
	{
		lpds->Release();
		return FALSE;
	}

	// Obtem o buffer primário ---------------------------------------
	ZeroMemory(&dsbDesc,sizeof(DSBUFFERDESC));
	dsbDesc.dwSize=sizeof(DSBUFFERDESC);
	dsbDesc.dwFlags=DSBCAPS_PRIMARYBUFFER;

	if( lpds->CreateSoundBuffer(&dsbDesc,&g_pDSB_Primary,NULL)!=DS_OK )
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

	if( g_pDSB_Primary->SetFormat(&WaveFormat)!=DS_OK )
	{
		lpds->Release();
		return FALSE;
	}

	return lpds;
}
void CAudioCheckerDlg::OnCancel()
{
	if( m_bChecking )
	{
		m_bChecking=FALSE;
		m_cCancel.EnableWindow(FALSE);
		return;
	}
	CDialog::OnCancel();
}

void CAudioCheckerDlg::CheckJingleFiles(void)
{
	MSG Msg;	
	CString strFile,
			strSQL;
	CRSViewJinglesDataOnAir rs("Broadcaster");
	CDatabase db;
	HRESULT hr;
	
	db.Open("Broadcaster");

	rs.m_strSort = "ID DESC";
	rs.Open(CRecordset::dynaset);

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}

	m_cProgressTotal.SetRange32(0,rs.m_ID);
	m_cDatabase.SetWindowText("Jingles");

	rs.m_strFilter.Format("Activ = 1 AND ID>%d",m_lLastJingleID);
	rs.m_strSort = "ID";
	rs.Requery();

	while( !rs.IsEOF() && m_bChecking )
	{
		theApp.WriteProfileInt("AudioCheck","JingleID",rs.m_ID);
		theApp.WriteProfileInt("AudioCheck","JingleCheck",1);
		m_lLastJingleID = rs.m_ID;

		m_cProgressTotal.SetPos(rs.m_ID);
		rs.m_TypeName.TrimRight();
		rs.m_Name.TrimRight();
		rs.m_Path.TrimRight();
		rs.m_FileName.TrimRight();

		m_cPath.SetWindowText(rs.m_Path);
		m_cFile.SetWindowText(rs.m_FileName);
		
		strFile.Format("%s\\%s",rs.m_Path,rs.m_FileName);

		rs.MoveNext();

		strSQL.Format("UPDATE Jingles SET Activ=0 WHERE ID=%d",m_lLastJingleID);
		db.ExecuteSQL(strSQL);

		m_pSound=new CAudioStream(g_pDS_MAIN,this);

		m_pSound->SetFile(strFile.GetBuffer(0));
		m_pSound->m_pbm = NULL;
		m_pSound->m_xres=1.0f;
		m_pSound->m_dwSleep=1;
		m_pSound->m_bDecompressAll=TRUE;
		hr=m_pSound->CueSound();
		m_pSound->SetPosition(0);

		m_cProgressFile.SetRange32(0,m_pSound->m_dwSrcSize);
		m_cProgressFile.SetPos(0);

		while( m_pSound->IsDecompressing() )
		{
			m_cProgressFile.SetPos(m_pSound->m_dwTotalBytesRead);
			while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			Sleep(5);
		}

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		delete m_pSound;

		strSQL.Format("UPDATE Jingles SET Activ=1 WHERE ID=%d",m_lLastJingleID);
		db.ExecuteSQL(strSQL);

		theApp.WriteProfileInt("AudioCheck","JingleCheck",0);
	}
}

void CAudioCheckerDlg::CheckSpotFiles(void)
{
	MSG Msg;	
	CString strFile,
			strSQL;
	CRSViewSpotsFull rs("Broadcaster");
	CDatabase db;
	HRESULT hr;
	
	db.Open("Broadcaster");

	rs.m_strSort = "ID DESC";
	rs.Open(CRecordset::dynaset);

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}

	m_cDatabase.SetWindowText("Spots");
	m_cProgressTotal.SetRange32(0,rs.m_ID);

	rs.m_strFilter.Format("Activ = 1 AND ID>%d",m_lLastSpotID);
	rs.m_strSort = "ID";
	rs.Requery();

	while( !rs.IsEOF() && m_bChecking )
	{
		theApp.WriteProfileInt("AudioCheck","SpotID",rs.m_ID);
		theApp.WriteProfileInt("AudioCheck","SpotCheck",1);
		m_lLastSpotID = rs.m_ID;

		m_cProgressTotal.SetPos(rs.m_ID);
		rs.m_Path.TrimRight();
		rs.m_FileName.TrimRight();

		m_cPath.SetWindowText(rs.m_Path);
		m_cFile.SetWindowText(rs.m_FileName);
		
		strFile.Format("%s\\%s",rs.m_Path,rs.m_FileName);

		rs.MoveNext();

		strSQL.Format("UPDATE Spots SET Activ=0 WHERE ID=%d",m_lLastSpotID);
		db.ExecuteSQL(strSQL);

		m_pSound=new CAudioStream(g_pDS_MAIN,this);

		m_pSound->SetFile(strFile.GetBuffer(0));
		m_pSound->m_pbm = NULL;
		m_pSound->m_xres=1.0f;
		m_pSound->m_dwSleep=1;
		m_pSound->m_bDecompressAll=TRUE;
		hr=m_pSound->CueSound();
		m_pSound->SetPosition(0);

		m_cProgressFile.SetRange32(0,m_pSound->m_dwSrcSize);
		m_cProgressFile.SetPos(0);

		while( m_pSound->IsDecompressing() )
		{
			m_cProgressFile.SetPos(m_pSound->m_dwTotalBytesRead);
			while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			Sleep(5);
		}

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		delete m_pSound;

		strSQL.Format("UPDATE Spots SET Activ=1 WHERE ID=%d",m_lLastSpotID);
		db.ExecuteSQL(strSQL);

		theApp.WriteProfileInt("AudioCheck","SpotCheck",0);
	}
}

void CAudioCheckerDlg::CheckRMFiles(void)
{
	MSG Msg;	
	CString strFile,
			strSQL;
	CRSViewRms rs("Broadcaster");
	CDatabase db;
	HRESULT hr;
	
	db.Open("Broadcaster");

	rs.m_strSort = "ID DESC";
	rs.Open(CRecordset::dynaset);

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}

	m_cDatabase.SetWindowText("RMs");
	m_cProgressTotal.SetRange32(0,rs.m_ID);

	rs.m_strFilter.Format("Activ = 1 AND ID>%d",m_lLastRMID);
	rs.m_strSort = "ID";
	rs.Requery();

	while( !rs.IsEOF() && m_bChecking )
	{
		theApp.WriteProfileInt("AudioCheck","RMID",rs.m_ID);
		theApp.WriteProfileInt("AudioCheck","RMCheck",1);
		m_lLastRMID = rs.m_ID;

		m_cProgressTotal.SetPos(rs.m_ID);
		rs.m_Path.TrimRight();
		rs.m_FileName.TrimRight();

		m_cPath.SetWindowText(rs.m_Path);
		m_cFile.SetWindowText(rs.m_FileName);
		
		strFile.Format("%s\\%s",rs.m_Path,rs.m_FileName);

		rs.MoveNext();

		strSQL.Format("UPDATE RMS SET Activ=0 WHERE ID=%d",m_lLastRMID);
		db.ExecuteSQL(strSQL);

		m_pSound=new CAudioStream(g_pDS_MAIN,this);

		m_pSound->SetFile(strFile.GetBuffer(0));
		m_pSound->m_pbm = NULL;
		m_pSound->m_xres=1.0f;
		m_pSound->m_dwSleep=1;
		m_pSound->m_bDecompressAll=TRUE;
		hr=m_pSound->CueSound();
		m_pSound->SetPosition(0);

		m_cProgressFile.SetRange32(0,m_pSound->m_dwSrcSize);
		m_cProgressFile.SetPos(0);

		while( m_pSound->IsDecompressing() )
		{
			m_cProgressFile.SetPos(m_pSound->m_dwTotalBytesRead);
			while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			Sleep(5);
		}

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		delete m_pSound;

		strSQL.Format("UPDATE RMs SET Activ=1 WHERE ID=%d",m_lLastRMID);
		db.ExecuteSQL(strSQL);

		theApp.WriteProfileInt("AudioCheck","RMCheck",0);
	}
}
