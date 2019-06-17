// AudioStream.cpp: implementation of the CAudioStream class.
//
//////////////////////////////////////////////////////////////////////
#include <stdafx.h>
#include <objbase.h>
#include <initguid.h>

#include <mmsystem.h>
#include <dsound.h>
#include <msacm.h>

#include "..\..\common\include\AudioStream.h"
#include "..\..\common\include\global.h"
#include "..\..\common\include\utils.h"
#include "..\..\common\include\defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAudioStream::CAudioStream(LPDIRECTSOUND lpds, CWnd *p)
{
	m_pDS		= lpds;
	m_pDSB		= NULL;
	m_pParent	= p;
	
	GetTempFileName(g_strTempDir,"DRM",0,m_strFilePcmAudio.GetBuffer(100));
	m_strFilePcmAudio.ReleaseBuffer();

	m_filePcmAudio	= new CFile( m_strFilePcmAudio,
								 CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone );

	m_pWave	= NULL;
	m_pMp3	= NULL;
		
	m_hEvent[0]=CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hEvent[1]=CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hEvent[2]=CreateEvent(NULL,FALSE,FALSE,NULL);

	m_bDecompressing = FALSE;
	m_bDecompressAll = FALSE;
	m_bStopDecompressing = FALSE;
	m_bPlaying = FALSE;
	m_bExitPlay = FALSE;
	m_bFading = FALSE;
	m_bRecording = FALSE;
	m_bExitRec = FALSE;

	m_dwPlayMode = ASMODEPLAY_STOP;
	m_dwSleep = 25;
}


CAudioStream::~CAudioStream()
{
	if( m_bFading )
	{
//		m_bStopFading=TRUE;
		do 
			Sleep(50);
		while( m_bFading );
	}
		
	if( m_bPlaying==TRUE )
	{
		m_bExitPlay=TRUE;
		do 
			Sleep(50);
		while( m_bPlaying );
	}
	
	if( m_bDecompressing )
	{
		m_bStopDecompressing=TRUE;
		do 
			Sleep(50);
		while( m_bDecompressing );
	}

	if( m_pDSB!=NULL )
		m_pDSB->Release();

	CloseHandle( m_hEvent[0] );
	CloseHandle( m_hEvent[1] );
	CloseHandle( m_hEvent[2] );

	if( m_filePcmAudio != NULL )
	{
		try
		{
			m_filePcmAudio->Close();
		}
		catch(...) {}

		try
		{
			delete m_filePcmAudio;
		}
		catch(...) {}

		try
		{
			CFile::Remove( m_strFilePcmAudio );
		}
		catch(...) {}
	}

	SAFE_DELETE( m_pWave )
	SAFE_DELETE( m_pMp3 );
}

long CAudioStream::GetPosition()
{
	DWORD64	dwCurTime;
	DWORD64 dwTimeElapsed;

	if( m_pDSB!=NULL )
	{
		if( m_bPlaying )
		{
			GetSystemTimeAsFileTime((FILETIME *)&dwCurTime);
			dwTimeElapsed=dwCurTime-m_qwStartingTime;
			dwTimeElapsed=dwTimeElapsed/10000+m_dwStartPos;
		}
		else
			dwTimeElapsed=m_dwStartPos;

		return (DWORD)dwTimeElapsed;
	}
	else
		return 0;

	return 0;
}

long CAudioStream::GetTimeToEnd()
{
	return 0;
}

void CAudioStream::SetFile(CString strFile)
{
	m_strWavFile = strFile;
	m_strFileType = GetFileType(strFile);
	m_strFileType.MakeUpper();

	if( m_strFileType==".WAV" )
		m_pWave = new CWaveFile();
	else if( m_strFileType==".MP3" )
		m_pMp3 = new CMp3File();
}

DWORD CAudioStream::ReadAudioData( LPVOID lpBuffer,DWORD dwSize )
{
	memset(lpBuffer,0,dwSize);

	m_filePcmAudio->Read(lpBuffer,dwSize);

	m_dwFileReadPos=(DWORD)m_filePcmAudio->GetPosition();

	return ASERR_NOERROR;
};

void CAudioStream::CreateSpectrum()
{

}

HRESULT CAudioStream::CueSound()
{
	HRESULT				hResult;
	DSBUFFERDESC		dsbDesc;
	LPDIRECTSOUNDNOTIFY	lpdsn;
	DSBPOSITIONNOTIFY	dsbpn[2];

	m_dwSrcSize=0;

	if( m_pWave )
	{
		hResult=m_pWave->Open(m_strWavFile.GetBuffer(0),m_pwfx,WAVEFILE_READ);

		if( hResult==S_OK )
		{
			m_pwfx = m_pWave->m_pwfx;
			m_dwSrcSize = m_pWave->GetSize();
		}
		else 
			return hResult;
	}
	else if( m_pMp3 )
	{
		hResult = m_pMp3->Open(m_strWavFile.GetBuffer(0));
		if( hResult == S_OK )
		{
			hResult = m_pMp3->GetAudioFormat();
			if( hResult==S_OK )
			{
				m_pwfx = (LPWAVEFORMATEX)m_pMp3->m_pwfx;
				m_dwSrcSize = m_pMp3->m_dwDataSize;
			}
			else
				return hResult;
		}
		else
			return hResult;
	}
	else
		return DSERR_UNINITIALIZED;

	m_bDecompressing=TRUE;
	m_pWaveDecompress = AfxBeginThread(WaveDecompress,this,THREAD_PRIORITY_NORMAL);

//	m_pwfx=WaveIO->GetFormat();
	m_wfxPcm.wFormatTag		= WAVE_FORMAT_PCM;
	m_wfxPcm.nSamplesPerSec	= m_pwfx->nSamplesPerSec;
	m_wfxPcm.nChannels		= m_pwfx->nChannels;
	m_wfxPcm.wBitsPerSample	= 16;
	m_wfxPcm.nBlockAlign	= 2*m_wfxPcm.nChannels;
	m_wfxPcm.nAvgBytesPerSec = m_wfxPcm.nSamplesPerSec*m_wfxPcm.nBlockAlign;
	
	memset(&dsbDesc,0,sizeof(DSBUFFERDESC));
	dsbDesc.dwSize=sizeof(DSBUFFERDESC);
	dsbDesc.dwFlags = DSBCAPS_GLOBALFOCUS | 
                           DSBCAPS_CTRLPOSITIONNOTIFY | 
                           DSBCAPS_GETCURRENTPOSITION2 |
						   DSBCAPS_CTRLVOLUME |
						   DSBCAPS_LOCSOFTWARE ;
	dsbDesc.dwBufferBytes	= m_wfxPcm.nSamplesPerSec*m_wfxPcm.nChannels*4;
	dsbDesc.lpwfxFormat		= &m_wfxPcm;

	if( hResult=m_pDS->CreateSoundBuffer(&dsbDesc,&m_pDSB,NULL ) != DS_OK )
		return hResult;
	else
		m_dwBufferSize=dsbDesc.dwBufferBytes;

	// Criar os events
	dsbpn[0].dwOffset=dsbDesc.dwBufferBytes/2;
	dsbpn[0].hEventNotify=m_hEvent[0];
	dsbpn[1].dwOffset=dsbDesc.dwBufferBytes-1;
	dsbpn[1].hEventNotify=m_hEvent[1];

	m_pDSB->QueryInterface(IID_IDirectSoundNotify,(VOID **)&lpdsn);
	lpdsn->SetNotificationPositions(2,dsbpn);
	lpdsn->Release();

	m_dwBufferSizeSamples=m_dwBufferSize/(m_wfxPcm.nChannels*2);

	return hResult;
}

// -------------------------------------------------------------------
//	Rotina para calcular os dados de vizualição do ficheiro wave
UINT CAudioStream::WaveDecompress( LPVOID as )
{
	CAudioStream *This=(CAudioStream *)as;
	CFile			FileAudio( This->m_strFilePcmAudio,
								CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone );
//	CFile			FileView( This->strFileWaveView,
//								CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone );
	LPWAVEFORMATEX	WaveFormatSRC=(LPWAVEFORMATEX)malloc(sizeof(WAVEFORMATEX)+This->m_pwfx->cbSize);
	WAVEFORMATEX	WaveFormatDST;
	ACMSTREAMHEADER	ashDST;
	HANDLE			hBufferSRC,
					hBufferDST;
	BYTE			*lpBufferSRC;
	short			*lpBufferDST;
	HACMSTREAM	hasDST;
//	short	iViewData[1000];
	int				iViewDataCount=0,
					nBlocksCount=0;
	float			fOffset,
					fResolution,
					x=0.0f,
					xres=This->m_xres,
					YScale=48.0f/37276.0f;
	DWORD			dwOffset=0,
					dwLimit;

	This->m_dwTotalBytesRead=0;
	
	MMRESULT		mmr;
	
	Graphics *graph=NULL;
	
	if( This->m_pbm!=NULL )
		graph=::new Graphics(This->m_pbm);

	This->m_bDecompressing=TRUE;

	memcpy(WaveFormatSRC,This->m_pwfx,sizeof(WAVEFORMATEX)+This->m_pwfx->cbSize );
	WaveFormatDST.cbSize		= 0;
	WaveFormatDST.wFormatTag	= WAVE_FORMAT_PCM;
	WaveFormatDST.nChannels		= WaveFormatSRC->nChannels;
	WaveFormatDST.nSamplesPerSec= WaveFormatSRC->nSamplesPerSec;
	WaveFormatDST.nAvgBytesPerSec=WaveFormatDST.nChannels*WaveFormatDST.nSamplesPerSec*2;
	WaveFormatDST.wBitsPerSample= 16;
	WaveFormatDST.nBlockAlign	= WaveFormatSRC->nChannels*2;

	fResolution=(float)((float)(WaveFormatSRC->nSamplesPerSec)/1000)*(float)(WaveFormatSRC->nChannels);
	fOffset=0;

	// Abrir os streams de conversão ---------------------------------
	if( acmStreamOpen(&hasDST,NULL,WaveFormatSRC,&WaveFormatDST,NULL,NULL,NULL,ACM_STREAMOPENF_NONREALTIME) )
	{
		return ASERR_INVALIDFORMAT;
	}

	// Preparar os buffers -------------------------------------------
	long int nBlocks=WaveFormatSRC->nAvgBytesPerSec/WaveFormatSRC->nBlockAlign;
	DWORD nBufferSizeSRC=nBlocks*WaveFormatSRC->nBlockAlign;
	DWORD nBufferSizeDST;
	DWORD nBytesRead;
	
	// Calculo do tamanho dos buffers
	acmStreamSize(hasDST,nBufferSizeSRC,&nBufferSizeDST,ACM_STREAMSIZEF_SOURCE);

	// Reservar espaço
	hBufferSRC = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeSRC);
	if( hBufferSRC == NULL ) 
	{
		return ASERR_NOMEM;
	}
	lpBufferSRC=(BYTE *)GlobalLock(hBufferSRC);

	hBufferDST = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeDST);
	if( hBufferDST == NULL )
	{
		return ASERR_NOMEM;
	}
	lpBufferDST=(short *)GlobalLock(hBufferDST);
	
	// Prepara os Headers para a compressao --------------------------
	memset(&ashDST,0,sizeof(ACMSTREAMHEADER) );
	ashDST.cbStruct=sizeof(ACMSTREAMHEADER) ;
	ashDST.pbSrc=(LPBYTE)lpBufferSRC;
	ashDST.cbSrcLength=nBufferSizeSRC;
	ashDST.pbDst=(LPBYTE)lpBufferDST;
	ashDST.cbDstLength=nBufferSizeDST;
	if( acmStreamPrepareHeader(hasDST,&ashDST,0) )
		return ASERR_UNKNOWN;

	while( !This->m_bStopDecompressing )
	{
		This->ReadFromSrc( (lpBufferSRC+dwOffset),nBufferSizeSRC-dwOffset,&nBytesRead );
		This->m_dwTotalBytesRead += nBytesRead;

		if( nBytesRead<nBufferSizeSRC-dwOffset )
			ashDST.cbSrcLength=nBytesRead;
		
		EnterCriticalSection( &g_csMPEG );
		
		try 
		{
			mmr=acmStreamConvert(hasDST,&ashDST,ACM_STREAMCONVERTF_BLOCKALIGN);
		}
		catch(...) {};

		LeaveCriticalSection( &g_csMPEG );

		if( ashDST.cbSrcLength>ashDST.cbSrcLengthUsed )
		{
			dwOffset=ashDST.cbSrcLength-ashDST.cbSrcLengthUsed;
			memcpy(lpBufferSRC,lpBufferSRC+ashDST.cbSrcLengthUsed,dwOffset);
		}
		else
			dwOffset=0;

		FileAudio.Write(lpBufferDST,ashDST.cbDstLengthUsed);
		nBlocksCount++;
		
		dwLimit=(ashDST.cbDstLengthUsed/sizeof(short));
		
		if( graph!=NULL )
		{
			while( fOffset<dwLimit )
			{
				x=(float)iViewDataCount*xres;
				graph->DrawLine( &Pen(Color(255,0,0,0),1.0f) ,x,(REAL)(24+(lpBufferDST[(int)fOffset]*YScale)),x,(REAL)(24-(lpBufferDST[(int)fOffset]*YScale)) );
					
				fOffset+=fResolution;
				iViewDataCount++;
			}
		}
		fOffset=fOffset-(float)dwLimit;

		if( This->m_dwTotalBytesRead >= This->GetSrcSize() )
			break;
#ifdef _ONAIR_
		else
		{
			if( !This->m_dwPlayMode == ASMODEPLAY_PLAY )
				Sleep(100);

			if( !This->m_bDecompressAll )
				if( (This->m_dwPlayMode == ASMODEPLAY_PLAY) || (FileAudio.GetLength()>This->m_dwFileReadPos+This->m_dwBufferSize) )
					while( (FileAudio.GetLength()>This->m_dwFileReadPos+This->m_dwBufferSize*5) && (!This->m_bStopDecompressing) )
						Sleep(25);
				else
					while( (FileAudio.GetLength()>This->m_dwFileReadPos+This->m_dwBufferSize*11) && (!This->m_bStopDecompressing) )
						Sleep(250);
			else
				Sleep(25);
		}
#else
		else
			Sleep(This->m_dwSleep);
#endif
	}
	
	EnterCriticalSection( &g_csEndACM );
	acmStreamUnprepareHeader( hasDST,&ashDST,0 );
	acmStreamClose(hasDST,0);
	LeaveCriticalSection( &g_csEndACM );

	FileAudio.Close();

	if( graph!=NULL )
		::delete graph;

	free( WaveFormatSRC );

	GlobalUnlock( hBufferSRC );
	GlobalFree( hBufferSRC );
	
	GlobalUnlock( hBufferDST );
	GlobalFree( hBufferDST );

	This->m_bDecompressing=FALSE;

	return 0;
};


HRESULT CAudioStream::SetPosition( DWORD newPosition ) 
{
	if( m_pDSB==NULL )
		return 0;

	LPVOID	lpBuffer1;
	LPVOID	lpBuffer2;
	DWORD	dwSize1;
	DWORD	dwSize2;
	DWORD	dwSamplePos=(DWORD)((float)newPosition*(float)(m_pwfx->nSamplesPerSec)/1000);
	DWORD	dwFilePos=dwSamplePos*2*m_pwfx->nChannels;
	
	if( (m_bDecompressing) && (m_filePcmAudio->GetLength()<(dwFilePos+m_dwBufferSize) ) ) 
	{
//		m_DecThread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		m_dwFileReadPos=dwFilePos+m_dwBufferSize;
	}

	m_dwSamplesRead=dwSamplePos;
	m_filePcmAudio->Seek(dwFilePos,CFile::begin);

	m_pDSB->Lock(0,m_dwBufferSize,&lpBuffer1,&dwSize1,&lpBuffer2,&dwSize2,DSBLOCK_ENTIREBUFFER );
	if( lpBuffer1!=NULL ) 
		ReadAudioData(lpBuffer1,dwSize1);
	if( lpBuffer2!=NULL )
		ReadAudioData(lpBuffer2,dwSize2);

	m_pDSB->Unlock(lpBuffer1,dwSize1,lpBuffer2,0);
	m_pDSB->SetCurrentPosition(0);
	
	m_dwStartPos=newPosition;
	GetSystemTimeAsFileTime((LPFILETIME)&m_qwStartingTime);
	m_dwFileReadPos=dwFilePos+m_dwBufferSize;

	return 0;
}

void CAudioStream::SetVolume( long lVolume )
{
	if( m_pDSB==NULL )
		return;

	if( lVolume>-2999 )
		m_pDSB->SetVolume(lVolume);
	else
		m_pDSB->SetVolume(-10000);
		
	m_lVolume=lVolume;
}

// -------------------------------------------------------------------
//	Rotina para fazer o STOP
void CAudioStream::Stop()
{
	if( m_pDSB )
		SetEvent(m_hEvent[2]);
}

void CAudioStream::Play() 
{
	if( m_pDSB==NULL )
		return;

	if( m_bDecompressing )
		m_pWaveDecompress->SetThreadPriority(THREAD_PRIORITY_NORMAL);

	m_dwPlayMode = ASMODEPLAY_PLAY;
	m_pDSB->Play(NULL,0,DSBPLAY_LOOPING);
	m_pDSB->SetCurrentPosition(0);
	ResetEvent(m_hEvent[2]);
//	m_pDSB->Play(NULL,0,DSBPLAY_LOOPING);
//	ResetEvent(m_hEvent[2]);

	m_pPlayThread=AfxBeginThread(PlayThread,this,THREAD_PRIORITY_TIME_CRITICAL);
	GetSystemTimeAsFileTime((FILETIME *)&m_qwStartingTime);

	return;
};

void CAudioStream::Pause()
{
	if( m_pDSB )
		m_pDSB->Stop();

	m_bPlaying=FALSE;
}

BOOL CAudioStream::Rec() 
{
	if( g_pDS_CaptureBuffer == NULL )
		return -1;

	LPWAVEFORMATEX	pwfx	= new WAVEFORMATEX;
	pwfx->cbSize			= sizeof(WAVEFORMATEX);
	pwfx->nAvgBytesPerSec	= 176400;
	pwfx->nBlockAlign		= 4;
	pwfx->nChannels			= 2;
	pwfx->nSamplesPerSec	= 44100;
	pwfx->wBitsPerSample	= 16;
	pwfx->wFormatTag		= WAVE_FORMAT_PCM;

	SAFE_DELETE( m_pWave );
	m_pWave = new CWaveFile();
	
	if( m_pWave->Open(m_strWavFile.GetBuffer(0),g_pwfx,WAVEFILE_WRITE)!=S_OK )
	{
		SAFE_DELETE( m_pWave );

		return FALSE;
	}

	m_pbm = ::new Bitmap(20000,48,PixelFormat32bppARGB);

	AfxBeginThread( RecThread,(LPVOID)this );
	GetSystemTimeAsFileTime( (FILETIME *)&m_qwStartingTime );

	return 0;	
}

void CAudioStream::StopRec()
{
	SetEvent(g_hCapture[2]);

	while( m_bRecording )
		Sleep(100);
	
	m_pWave->Close();
	delete m_pWave;
	m_pWave=NULL;

	::delete m_pbm;
	m_pbm=NULL;
}

UINT CAudioStream::RecThread(LPVOID lp )
{
	CAudioStream *This = (CAudioStream *)lp;
	int			Cont=0;
	short int	*lpBuffer,*lpBuffer2;
	DWORD		Size,
				Size2,
				dwEvent,
				dwMyReadCursor=0,
				dwReadPos,
				dwNumBytes,
				dwSamples=0;
	UINT		nWrote,
				cb;
	float		YScale=48.0f/37276.0f,
				xres = This->m_xres*500.0f/440.0f,
				x=0.0f;
	MMRESULT	mmr;
	Graphics	graph(This->m_pbm);

	This->m_bRecording=TRUE;

	This->CreateRecConvertionStream();

	g_pDS_CaptureBuffer->Start(DSCBSTART_LOOPING);

	while( This->m_bExitRec==FALSE )
	{
		dwEvent=MsgWaitForMultipleObjects(3,g_hCapture,FALSE,INFINITE,0);
		
		if( dwEvent<=2 )
		{
			if( dwEvent==2 ) 
			{
				This->m_bExitRec=TRUE;
			}
			else
			{
				g_pDS_CaptureBuffer->GetCurrentPosition(NULL,&dwReadPos);

				if (dwReadPos < dwMyReadCursor)
					dwReadPos += 176400;

				dwNumBytes = dwReadPos - dwMyReadCursor;

				g_pDS_CaptureBuffer->Lock(dwMyReadCursor,dwNumBytes,(LPVOID *)&lpBuffer,&Size,(LPVOID *)&lpBuffer2,&Size2,0 );

				if( x > This->m_xres*10000 )
				{
					x=0;
					graph.Clear(Color(0,0,0,0));
				}

				if( lpBuffer!=NULL )
				{
					for( int d=0; d< (int)Size/2; d+=100 )
					{
						graph.DrawLine( &Pen(Color(255,0,0,0),1.0f) ,x,(REAL)(24+(lpBuffer[d]*YScale)),x,(REAL)(24-(lpBuffer[d]*YScale)) );
						x+=xres;
					}

					if( This->ConvertionStream.has!=NULL )
					{
						memcpy(This->ConvertionStream.lpBufferSrc+This->ConvertionStream.lDataOnBuffer,
						lpBuffer,
						Size );
						This->ConvertionStream.lDataOnBuffer += Size;
					}
					else
						This->m_pWave->Write(Size,(LPBYTE)lpBuffer,&nWrote);
				}
				if( lpBuffer2!=NULL )
				{
					for( int d=0; d< (int)Size/2; d+=100 )
					{
						graph.DrawLine( &Pen(Color(255,0,0,0),1.0f) ,x,(REAL)(24+(lpBuffer[d]*YScale)),x,(REAL)(24-(lpBuffer[d]*YScale)) );
						x+=xres;
					}

					if( This->ConvertionStream.has!=NULL )
					{
						memcpy(This->ConvertionStream.lpBufferSrc+This->ConvertionStream.lDataOnBuffer,
						lpBuffer2,
						Size2 );
						This->ConvertionStream.lDataOnBuffer += Size2;
					}
					else
						This->m_pWave->Write(Size2,(LPBYTE)lpBuffer2,&nWrote);
				}

				g_pDS_CaptureBuffer->Unlock(lpBuffer,Size,lpBuffer2,Size2);

				// Converts the PCM audio data
				if( This->ConvertionStream.has!=NULL )
				{
					This->ConvertionStream.ash.cbSrcLength = This->ConvertionStream.lDataOnBuffer;

					EnterCriticalSection( &g_csMPEG );

					mmr = acmStreamConvert(This->ConvertionStream.has,
											&This->ConvertionStream.ash,
											ACM_STREAMCONVERTF_BLOCKALIGN );

					LeaveCriticalSection( &g_csMPEG );

					This->m_pWave->Write(This->ConvertionStream.ash.cbDstLengthUsed,
										This->ConvertionStream.lpBufferDst,
										&cb );

					dwSamples = This->ConvertionStream.ash.cbSrcLengthUsed/(This->ConvertionStream.pwfx->nChannels * 2);
					This->m_pWave->m_dwSize += dwSamples;

					if( This->ConvertionStream.ash.cbSrcLengthUsed < (ULONG)This->ConvertionStream.lDataOnBuffer )
					{
						This->ConvertionStream.lDataOnBuffer = This->ConvertionStream.ash.cbSrcLength-This->ConvertionStream.ash.cbSrcLengthUsed;
						memcpy(This->ConvertionStream.lpBufferSrc,
								This->ConvertionStream.lpBufferSrc+This->ConvertionStream.ash.cbSrcLengthUsed,
								This->ConvertionStream.lDataOnBuffer );	
					}
					else
						This->ConvertionStream.lDataOnBuffer=0;
				}

				dwMyReadCursor += dwNumBytes;
				if (dwMyReadCursor >= 176400)
					dwMyReadCursor -= 176400;

			}
		}
	}

	g_pDS_CaptureBuffer->Stop();
	This->m_bRecording = FALSE;
	This->CloseRecConvertionStream();

	return 0;
}


UINT CAudioStream::PlayThread(LPVOID T)
{
	CAudioStream *This=(CAudioStream *)T;
	int		Cont=0;
	LPVOID	lpBuffer,
			lpBuffer2;
	DWORD	Size,
			Size2;
	DWORD	dwEvent;

	This->m_bPlaying=TRUE;

	while( This->m_bExitPlay==FALSE )
	{
		dwEvent=MsgWaitForMultipleObjects(3,This->m_hEvent,FALSE,INFINITE,0);

		if( dwEvent<=2 )
		{
			if( dwEvent==2 ) 
			{
				DWORD dwTick=GetTickCount();	

				This->m_bExitPlay=TRUE;
				This->m_pDSB->Lock(0,This->m_dwBufferSize/2,&lpBuffer,&Size,&lpBuffer2,&Size2,DSBLOCK_ENTIREBUFFER );
				if( lpBuffer!=NULL )
					memset(lpBuffer,0,Size);
				if( lpBuffer2!=NULL )
					memset(lpBuffer2,0,Size2);
				This->m_pDSB->Unlock(lpBuffer,Size,lpBuffer2,Size2);
				//MessageBeep(0);
			}
			else
			{
				if( dwEvent==1 ) 
				{
					This->m_pDSB->Lock(This->m_dwBufferSize/2,This->m_dwBufferSize/2,&lpBuffer,&Size,&lpBuffer2,&Size2,0 );
					This->m_dwSamplesRead += This->m_dwBufferSizeSamples;
					ResetEvent(This->m_hEvent[1]);
				}
				else
				{
					This->m_pDSB->Lock(0,This->m_dwBufferSize/2,&lpBuffer,&Size,&lpBuffer2,&Size2,0 );
					ResetEvent(This->m_hEvent[2]);
				}
				if( lpBuffer!=NULL )
					This->ReadAudioData(lpBuffer,Size);
				if( lpBuffer2!=NULL )
					This->ReadAudioData(lpBuffer2,Size2);
				This->m_pDSB->Unlock(lpBuffer,Size,lpBuffer2,Size2);

				if( !ResetEvent(This->m_hEvent[0]) || !ResetEvent(This->m_hEvent[1]) ) {};
			}
		}
	}
	
	This->m_pDSB->Lock(0,This->m_dwBufferSize/2,&lpBuffer,&Size,&lpBuffer2,&Size2,DSBLOCK_ENTIREBUFFER );
	if( lpBuffer!=NULL )
		memset(lpBuffer,0,Size);
	if( lpBuffer2!=NULL )
		memset(lpBuffer2,0,Size2);
	This->m_pDSB->Unlock(lpBuffer,Size,lpBuffer2,Size2);
	This->m_pDSB->Stop();

/*	if( This->Parent!=NULL )
		This->Parent->PostMessage( WM_USER_AUDIOSTOP ); */

	This->m_bPlaying=FALSE;
	return 0;
}


void CAudioStream::Fade(long End,DWORD Duration)
{
	if( m_bFading )
		return;

	m_lFadeStartVol = m_lVolume;
	m_lFadeEndVol = End;
	m_dwFadeStartTime = GetTickCount();
	m_dwFadeEndTime=GetTickCount()+Duration;
	m_bFading=TRUE;

	AfxBeginThread(FadeThread,this,THREAD_PRIORITY_HIGHEST);
}

UINT CAudioStream::FadeThread(LPVOID T)
{
	CAudioStream *This=(CAudioStream *)T;
	This->m_bFading=TRUE;

	float fVolDif=(float)(This->m_lFadeEndVol-This->m_lFadeStartVol);
	float fTimeDif=(float)(This->m_dwFadeEndTime-This->m_dwFadeStartTime);
	float fTimeElapsed=0;
	float fVolume;

	while( (fTimeElapsed<fTimeDif) && (This->m_bExitPlay==FALSE) )
	{
		Sleep(50);
		fVolume=(float)This->m_lFadeStartVol+fVolDif*fTimeElapsed/fTimeDif;
		This->SetVolume((long)fVolume);
		fTimeElapsed=(float)(GetTickCount()-This->m_dwFadeStartTime);
	}

	This->SetVolume(This->m_lFadeEndVol);
	This->m_bFading=FALSE;

	return(0);
}

void CAudioStream::ReadFromSrc(LPBYTE pBuffer,DWORD dwSizeToRead,DWORD *pdwSizeRead)
{
	if( m_pWave!=NULL )
		m_pWave->Read(pBuffer,dwSizeToRead,pdwSizeRead);
	else if( m_pMp3!=NULL )
		m_pMp3->Read(pBuffer,dwSizeToRead,pdwSizeRead);
	else
	{
		memset(pBuffer,0,dwSizeToRead);
		*pdwSizeRead=0;
	}
}

DWORD CAudioStream::GetSrcSize()
{
	DWORD dwResult=0;

	if( m_pWave!=NULL )
		dwResult = m_pWave->GetSize();
	else if ( m_pMp3!=NULL )
		dwResult = m_pMp3->m_dwDataSize;

	return dwResult;
}


BOOL CAudioStream::CreateRecConvertionStream()
{
	MMRESULT		mmr;
	WAVEFORMATEX	wfxSrc;
	
	wfxSrc.cbSize			= 0;
	wfxSrc.nAvgBytesPerSec	= 2 * 2 * 44100;
	wfxSrc.nBlockAlign		= 4;
	wfxSrc.nChannels		= 2;
	wfxSrc.nSamplesPerSec	= 44100;
	wfxSrc.wBitsPerSample	= 16;
	wfxSrc.wFormatTag		= WAVE_FORMAT_PCM;

	ConvertionStream.pwfx = g_pwfx;
	ConvertionStream.lDataOnBuffer = 0;

	if( ConvertionStream.pwfx == NULL )
	{
		ConvertionStream.has=NULL;
		return FALSE;
	}

	// Open the convertion stream +++++++++++++++++++++++++++++++++++++++++++
	mmr = acmStreamOpen(&ConvertionStream.has,
		NULL,
		&wfxSrc,
		ConvertionStream.pwfx,
		NULL,
		NULL,
		NULL,
		ACM_STREAMOPENF_NONREALTIME );

	if( mmr != 0 )
	{
		ConvertionStream.has=NULL;
		return FALSE;
	}

	// Get the buffer sizes +++++++++++++++++++++++++++++++++++++++++++++++++
	ConvertionStream.cbBufferSrc = wfxSrc.nAvgBytesPerSec * 4;

	mmr = acmStreamSize( ConvertionStream.has,
		ConvertionStream.cbBufferSrc,
		&ConvertionStream.cbBufferDst,
		ACM_STREAMSIZEF_SOURCE );
	
	// Get the source buffer ++++++++++++++++++++++++++++++++++++++++++++++++
	ConvertionStream.hBufferSrc = GlobalAlloc( GMEM_MOVEABLE|GMEM_SHARE , 
		ConvertionStream.cbBufferSrc );

	if( ConvertionStream.hBufferSrc == NULL ) 
	{
		acmStreamClose( ConvertionStream.has,0 );
		ConvertionStream.has=NULL;
		return FALSE;
	}
	ConvertionStream.lpBufferSrc=(BYTE *)GlobalLock(ConvertionStream.hBufferSrc);

	// Get the destination buffer +++++++++++++++++++++++++++++++++++++++++++
	ConvertionStream.hBufferDst = GlobalAlloc( GMEM_MOVEABLE|GMEM_SHARE ,
		ConvertionStream.cbBufferDst );

	if( ConvertionStream.hBufferDst == NULL )
	{
		GlobalUnlock(ConvertionStream.hBufferSrc);
		GlobalFree(ConvertionStream.hBufferSrc);
		acmStreamClose( ConvertionStream.has,0 );
		ConvertionStream.has=NULL;
		return FALSE;
	}
	ConvertionStream.lpBufferDst=(BYTE *)GlobalLock(ConvertionStream.hBufferDst);

	// Prepare's the stream headers +++++++++++++++++++++++++++++++++++++++++
	memset(&ConvertionStream.ash,0,sizeof(ACMSTREAMHEADER) );

	ConvertionStream.ash.cbStruct	= sizeof(ACMSTREAMHEADER) ;
	ConvertionStream.ash.pbSrc		= (LPBYTE)ConvertionStream.lpBufferSrc;
	ConvertionStream.ash.cbSrcLength= ConvertionStream.cbBufferSrc;
	ConvertionStream.ash.pbDst		= (LPBYTE)ConvertionStream.lpBufferDst;
	ConvertionStream.ash.cbDstLength= ConvertionStream.cbBufferDst;

	mmr = acmStreamPrepareHeader(ConvertionStream.has,&ConvertionStream.ash,0);
	if( mmr!=0 )
	{
		GlobalUnlock(ConvertionStream.hBufferSrc);
		GlobalFree(ConvertionStream.hBufferSrc);

		GlobalUnlock(ConvertionStream.hBufferDst);
		GlobalFree(ConvertionStream.hBufferDst);

		acmStreamClose(ConvertionStream.has,0);

		ConvertionStream.has=NULL;
		return FALSE;
	}

	return TRUE;
}

void CAudioStream::CloseRecConvertionStream()
{
	if( ConvertionStream.has != NULL )
	{
		acmStreamUnprepareHeader(ConvertionStream.has,
			&ConvertionStream.ash,
			0 );

		GlobalUnlock( ConvertionStream.hBufferSrc);
		GlobalFree( ConvertionStream.hBufferSrc);

		GlobalUnlock( ConvertionStream.hBufferDst );
		GlobalFree( ConvertionStream.lpBufferDst );
		
		acmStreamClose(ConvertionStream.has,0);
		
		ConvertionStream.has = NULL;
	}
}

long CAudioStream::GetDecompressedSize()
{
	long lResult = (long)m_filePcmAudio->GetLength();

	lResult = lResult / (m_pwfx->nSamplesPerSec * m_pwfx->nChannels * 2);

	return lResult;
}

DWORD CAudioStream::GetLength()
{
	float lResult=(float)m_dwSrcSize*1000.0f;

	lResult = lResult / (float)m_pwfx->nAvgBytesPerSec;

	return (DWORD)lResult;
}