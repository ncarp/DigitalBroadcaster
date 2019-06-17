// ConvertAudioFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConvertAudioFolder.h"
#include "ConvertAudioFolderDlg.h"
#include ".\convertaudiofolderdlg.h"
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include <io.h>
#include "..\common\include\wavefile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CConvertAudioFolderDlg dialog



CConvertAudioFolderDlg::CConvertAudioFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvertAudioFolderDlg::IDD, pParent)
	, m_strBitrate(_T(""))
	, m_bDelete(FALSE)
	, m_bOverwrite(FALSE)
	, m_bLowercase(FALSE)
	, m_strSource(_T(""))
	, m_strDestination(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvertAudioFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BITRATE, m_strBitrate);
	DDX_Check(pDX, IDC_DELETE, m_bDelete);
	DDX_Check(pDX, IDC_OVERWRITE, m_bOverwrite);
	DDX_Check(pDX, IDC_OVERWRITE2, m_bLowercase);
	DDX_Control(pDX, IDC_PROGRESS, m_cProgress);
	DDX_Control(pDX, IDC_SRC, m_cSource);
	DDX_Text(pDX, IDC_SRC, m_strSource);
	DDX_Control(pDX, IDC_DST, m_cDestination);
	DDX_Text(pDX, IDC_DST, m_strDestination);
	DDX_Control(pDX, IDC_FILENAME, m_cFileName);
	DDX_Control(pDX, IDC_CODEC, m_cCodec);
	DDX_Control(pDX, IDC_SAMPLERATE, m_cSampleRate);
	DDX_Control(pDX, IDC_BITRATE, m_cBitRate);
}

BEGIN_MESSAGE_MAP(CConvertAudioFolderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CConvertAudioFolderDlg message handlers

BOOL CConvertAudioFolderDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConvertAudioFolderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConvertAudioFolderDlg::OnPaint() 
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
HCURSOR CConvertAudioFolderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CConvertAudioFolderDlg::ConvertAudioFile(CString strSource, CString strDestination)
{
		CWaveFile		fileSrc,
					fileDst;
	CFile			fileTmp;
	BOOL			bPCM = FALSE;
	CString			strTempFile="C:\\Temp\\tempfile.tmp",
					strTemp;
	HANDLE			hBufferSRC;
	HANDLE			hBufferDST;
	BYTE			*lpBufferSRC;
	short			*lpBufferDST;
	MMRESULT		mmr;
	MSG				Msg;
	WAVEFORMATEX	wfPCM;
	MPEG1WAVEFORMAT	wfMPEG;

	fileSrc.Open(strSource.GetBuffer(0),NULL,WAVEFILE_READ);
	if( fileSrc.m_pwfx->wFormatTag==WAVE_FORMAT_PCM )
	{
		bPCM=TRUE;
		wfPCM.cbSize		= 0;
		wfPCM.wFormatTag	= WAVE_FORMAT_PCM;
		wfPCM.nChannels		= fileSrc.m_pwfx->nChannels;
		wfPCM.nSamplesPerSec= fileSrc.m_pwfx->nSamplesPerSec;
		wfPCM.nAvgBytesPerSec=fileSrc.m_pwfx->nAvgBytesPerSec;
		wfPCM.wBitsPerSample= fileSrc.m_pwfx->wBitsPerSample;
		wfPCM.nBlockAlign	= fileSrc.m_pwfx->nBlockAlign;

		m_cCodec.SetWindowText("PCM Audio");
		
		strTemp.Format("%d Hz",wfPCM.nSamplesPerSec);
		if( wfPCM.nChannels==1 )
			strTemp = "Mono, "+strTemp;
		else
			strTemp = "Stereo, "+strTemp;
		m_cSampleRate.SetWindowText(strTemp);

		strTemp.Format("%d kbps",wfPCM.nAvgBytesPerSec/128);
		m_cBitRate.SetWindowText(strTemp);
	} 
	else
	{
		HACMSTREAM		hasPCM;
		ACMSTREAMHEADER ashPCM;
		LPMPEG1WAVEFORMAT tempFmt;

		if( (fileSrc.m_pwfx->wFormatTag==WAVE_FORMAT_MPEG) )
		{
			tempFmt=(LPMPEG1WAVEFORMAT)fileSrc.m_pwfx;
			tempFmt->wfx.cbSize=sizeof(MPEG1WAVEFORMAT)-sizeof(WAVEFORMATEX);
			tempFmt->dwPTSHigh	= 0;
			tempFmt->dwPTSLow	= 0;
		}

		m_cProgress.SetRange32(0,fileSrc.GetSize());

		fileTmp.Open(strTempFile,CFile::modeCreate|CFile::modeReadWrite,NULL);

		wfPCM.cbSize		= 0;
		wfPCM.wFormatTag	= WAVE_FORMAT_PCM;
		wfPCM.nChannels		= fileSrc.m_pwfx->nChannels;
		wfPCM.nSamplesPerSec= fileSrc.m_pwfx->nSamplesPerSec;
		wfPCM.nAvgBytesPerSec=fileSrc.m_pwfx->nChannels*wfPCM.nSamplesPerSec*2;
		wfPCM.wBitsPerSample= 16;
		wfPCM.nBlockAlign	= wfPCM.nChannels*2;
		
		// Abrir os streams de conversão ---------------------------------
		if( acmStreamOpen(&hasPCM,NULL,fileSrc.m_pwfx,&wfPCM,NULL,NULL,NULL,ACM_STREAMOPENF_NONREALTIME) )
		{
			return FALSE;
		}

		// Get the codec name 
		HACMDRIVERID		hID;
		ACMDRIVERDETAILS	acmDetails;
		acmDetails.cbStruct = sizeof(acmDetails);
	
		acmDriverID((HACMOBJ)hasPCM,&hID,0);
		acmDriverDetails(hID,&acmDetails,0);
		m_cCodec.SetWindowText(acmDetails.szLongName);

		strTemp.Format("%d Hz",fileSrc.m_pwfx->nSamplesPerSec);
		if( fileSrc.m_pwfx->nChannels==1 )
			strTemp = "Mono, "+strTemp;
		else
			strTemp = "Stereo, "+strTemp;
		m_cSampleRate.SetWindowText(strTemp);

		strTemp.Format("%d bps",fileSrc.m_pwfx->nAvgBytesPerSec*8);
		m_cBitRate.SetWindowText(strTemp);

		if( fileSrc.m_pwfx->wFormatTag==WAVE_FORMAT_MPEG )
		{
			LPMPEG1WAVEFORMAT pFmt=(LPMPEG1WAVEFORMAT)fileSrc.m_pwfx;
			strTemp.Format("%d bps",pFmt->dwHeadBitrate);
			//AfxMessageBox(strTemp);
		}

		// Preparar os buffers -------------------------------------------
		long int	nBlocks=fileSrc.m_pwfx->nAvgBytesPerSec/fileSrc.m_pwfx->nBlockAlign;
		DWORD		nBufferSizeSRC=nBlocks*fileSrc.m_pwfx->nBlockAlign;
		DWORD		nBufferSizeDST;
		DWORD		nBytesRead;
		DWORD		dwOffset=0;
		DWORD		ReadPos=0;
		BOOL		bStopDecompress=FALSE;
	
		// Calculo do tamanho dos buffers
		acmStreamSize(hasPCM,nBufferSizeSRC,&nBufferSizeDST,ACM_STREAMSIZEF_SOURCE);

		// Reservar espaço
		hBufferSRC = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeSRC);
		if( hBufferSRC == NULL ) 
		{
			return FALSE;
		}
		lpBufferSRC=(BYTE *)GlobalLock(hBufferSRC);

		hBufferDST = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeDST);
		if( hBufferDST == NULL )
		{
			return FALSE;
		}
		lpBufferDST=(short *)GlobalLock(hBufferDST);
	
		// Prepara os Headers para a compressao --------------------------
		memset(&ashPCM,0,sizeof(ACMSTREAMHEADER) );
		ashPCM.cbStruct=sizeof(ACMSTREAMHEADER) ;
		ashPCM.pbSrc=(LPBYTE)lpBufferSRC;
		ashPCM.cbSrcLength=nBufferSizeSRC;
		ashPCM.pbDst=(LPBYTE)lpBufferDST;
		ashPCM.cbDstLength=nBufferSizeDST;
		if( acmStreamPrepareHeader(hasPCM,&ashPCM,0) )
			return FALSE;

		while( !bStopDecompress )
		{
			fileSrc.Read( (LPBYTE)(lpBufferSRC+dwOffset),nBufferSizeSRC-dwOffset,&nBytesRead);

			ReadPos+=nBytesRead;

			if( nBytesRead<nBufferSizeSRC-dwOffset )
			{
				ashPCM.cbSrcLength=nBytesRead;
				bStopDecompress=TRUE;
			}
		
			mmr=acmStreamConvert(hasPCM,&ashPCM,ACM_STREAMCONVERTF_BLOCKALIGN);
		
			if( ashPCM.cbSrcLength>ashPCM.cbSrcLengthUsed )
			{
				dwOffset=ashPCM.cbSrcLength-ashPCM.cbSrcLengthUsed;
				memcpy(lpBufferSRC,lpBufferSRC+ashPCM.cbSrcLengthUsed,dwOffset);
			}
			else
				dwOffset=0;

			fileTmp.Write(lpBufferDST,ashPCM.cbDstLengthUsed);
			
			m_cProgress.SetPos(ReadPos);

			while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
			{strTemp.Format("%d Hz",wfPCM.nSamplesPerSec);
		if( wfPCM.nChannels==1 )
			strTemp = "Mono, "+strTemp;
		else
			strTemp = "Stereo, "+strTemp;
		m_cSampleRate.SetWindowText(strTemp);

		strTemp.Format("%d kbps",wfPCM.nAvgBytesPerSec/1024);
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			} 
		}
	
		acmStreamUnprepareHeader( hasPCM,&ashPCM,0 );
		acmStreamClose(hasPCM,0);

		GlobalUnlock( hBufferSRC );
		GlobalFree( hBufferSRC );
	
		GlobalUnlock( hBufferDST );
		GlobalFree( hBufferDST );
	}

	HACMSTREAM		hasMPEG;
	ACMSTREAMHEADER ashMPEG;


	wfMPEG.wfx.cbSize = sizeof(MPEG1WAVEFORMAT)-sizeof(WAVEFORMATEX);

	strTemp.Format("%d bps",fileSrc.m_pwfx->nAvgBytesPerSec);
	//AfxMessageBox(strTemp);

/*	if( fileSrc.m_pwfx->wFormatTag!=WAVE_FORMAT_MPEG )
		wfMPEG.wfx.nAvgBytesPerSec = 16000*wfPCM.nChannels;
	else if( fileSrc.m_pwfx->nAvgBytesPerSec<=16000 )
		wfMPEG.wfx.nAvgBytesPerSec = 16000;
	else
		wfMPEG.wfx.nAvgBytesPerSec = fileSrc.m_pwfx->nAvgBytesPerSec; */

	wfMPEG.wfx.nAvgBytesPerSec = 16000*wfPCM.nChannels;

	wfMPEG.wfx.nBlockAlign		= 1;
	wfMPEG.wfx.nChannels		= wfPCM.nChannels;
	wfMPEG.wfx.nSamplesPerSec	= wfPCM.nSamplesPerSec;
	wfMPEG.wfx.wBitsPerSample	= 16;
	wfMPEG.wfx.wFormatTag		= WAVE_FORMAT_MPEG;
	wfMPEG.fwHeadLayer			= ACM_MPEG_LAYER2;
	wfMPEG.wHeadEmphasis		= 1;
	wfMPEG.fwHeadFlags			= ACM_MPEG_ID_MPEG1;
	if( wfPCM.nChannels==2 )
		wfMPEG.fwHeadMode = ACM_MPEG_JOINTSTEREO;
	else
		wfMPEG.fwHeadMode = ACM_MPEG_SINGLECHANNEL;
	wfMPEG.dwHeadBitrate		= wfMPEG.wfx.nAvgBytesPerSec*8;
	wfMPEG.dwPTSHigh			= 0;
	wfMPEG.dwPTSLow				= 0;
	wfMPEG.fwHeadModeExt		= 0;
	
	mmr = acmStreamOpen(&hasMPEG,NULL,&wfPCM,(LPWAVEFORMATEX)&wfMPEG,NULL,NULL,NULL,ACM_STREAMOPENF_NONREALTIME);

	// Preparar os buffers -------------------------------------------
	long int	nBlocks=wfPCM.nAvgBytesPerSec/wfPCM.nBlockAlign;
	DWORD		nBufferSizeSRC=nBlocks*wfPCM.nBlockAlign;
	DWORD		nBufferSizeDST;
	DWORD		nBytesRead;
	DWORD		dwOffset=0;
	DWORD		ReadPos;
	BOOL		bStopDecompress=FALSE;
	UINT		uWrite;
	
	// Calculo do tamanho dos buffers
	acmStreamSize(hasMPEG,nBufferSizeSRC,&nBufferSizeDST,ACM_STREAMSIZEF_SOURCE);

	// Reservar espaço
	hBufferSRC = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeSRC);
	if( hBufferSRC == NULL ) 
	{
		return FALSE;
	}
	lpBufferSRC=(BYTE *)GlobalLock(hBufferSRC);

	hBufferDST = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeDST);
	if( hBufferDST == NULL )
	{
		return FALSE;
	}
	lpBufferDST=(short *)GlobalLock(hBufferDST);
	
	// Prepara os Headers para a compressao --------------------------
	memset(&ashMPEG,0,sizeof(ACMSTREAMHEADER) );
	ashMPEG.cbStruct=sizeof(ACMSTREAMHEADER) ;
	ashMPEG.pbSrc=(LPBYTE)lpBufferSRC;
	ashMPEG.cbSrcLength=nBufferSizeSRC;
	ashMPEG.pbDst=(LPBYTE)lpBufferDST;
	ashMPEG.cbDstLength=nBufferSizeDST;

	if( acmStreamPrepareHeader(hasMPEG,&ashMPEG,0) )
		return FALSE;

	if( bPCM )
	{
		ReadPos = fileSrc.GetSize();
	}
	else
	{
		ReadPos = (DWORD)fileTmp.GetLength();
		fileTmp.SeekToBegin();
	}

	fileDst.Open(strDestination.GetBuffer(0),(LPWAVEFORMATEX)&wfMPEG,WAVEFILE_WRITE);
	m_cProgress.SetRange32(0,ReadPos);

	while( !bStopDecompress )
	{
		if( bPCM )
			fileSrc.Read( (LPBYTE)(lpBufferSRC+dwOffset),nBufferSizeSRC-dwOffset,&nBytesRead);
		else
			nBytesRead = fileTmp.Read( (LPVOID)(lpBufferSRC+dwOffset),nBufferSizeSRC-dwOffset);

		ReadPos-=nBytesRead;

		if( nBytesRead<nBufferSizeSRC-dwOffset )
		{
			ashMPEG.cbSrcLength=nBytesRead;
			bStopDecompress=TRUE;
		}
		
		mmr=acmStreamConvert(hasMPEG,&ashMPEG,ACM_STREAMCONVERTF_BLOCKALIGN);
		
		if( ashMPEG.cbSrcLength>ashMPEG.cbSrcLengthUsed )
		{
			dwOffset=ashMPEG.cbSrcLength-ashMPEG.cbSrcLengthUsed;
			memcpy(lpBufferSRC,lpBufferSRC+ashMPEG.cbSrcLengthUsed,dwOffset);
		}
		else
			dwOffset=0;

		fileDst.Write(ashMPEG.cbDstLengthUsed,(LPBYTE)lpBufferDST,&uWrite);
	//	fileTmp.Write(lpBufferDST,ashMPEG.cbDstLengthUsed);
			
		m_cProgress.SetPos(ReadPos);

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	
	acmStreamUnprepareHeader( hasMPEG,&ashMPEG,0 );
	acmStreamClose(hasMPEG,0);

	GlobalUnlock( hBufferSRC );
	GlobalFree( hBufferSRC );
	
	GlobalUnlock( hBufferDST );
	GlobalFree( hBufferDST );

	return TRUE;
}

void CConvertAudioFolderDlg::OnBnClickedOk()
{
	MSG		Msg;
	BOOL	bFound;
	CString	strFileName;

	UpdateData();
	CFileFind finder;

	theApp.WriteProfileString("Convert","InputPath",m_strSource);
	theApp.WriteProfileString("Convert","OutputPath",m_strDestination);

	m_cSource.EnableWindow(FALSE);
	m_cDestination.EnableWindow(FALSE);

	bFound=finder.FindFile(m_strSource+"\\*.wav",0);
	while( bFound )
	{
		bFound=finder.FindNextFile();
		m_cFileName.SetWindowText(finder.GetFileName());

		strFileName = finder.GetFileName();

		if( m_bLowercase )
			strFileName = FileName2LowerCase(strFileName);

		if( _access(m_strDestination+"\\"+strFileName,0)==0 )
		{
			if( m_bOverwrite )
				DeleteFile(m_strDestination+"\\"+strFileName);
			else
				continue;
		}

		ConvertAudioFile(finder.GetFilePath(),m_strDestination+"\\"+strFileName);

		if( m_bDelete )
			DeleteFile(finder.GetFilePath());

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

	//	bFound=FALSE;
	}
	
	m_strSource.TrimRight();
	m_strDestination.TrimRight();

	OnOK();
}


CString CConvertAudioFolderDlg::FileName2LowerCase(CString str)
{
	CString strTemp;
	int I;

	str.MakeLower();
	str.TrimRight();
	I = str.GetLength();

	if( I>0 )
	{
		strTemp = str.GetAt(0);
		strTemp.MakeUpper();
		str.SetAt(0,strTemp.GetAt(0));

		for( int n=1; n<I-1; n++ )
		{
			if( str.GetAt(n)==' ' )
			{
				strTemp = str.GetAt(n+1);
				strTemp.MakeUpper();

				str.SetAt(n+1,strTemp.GetAt(0));
			}
		}
	}
	return str;
}
