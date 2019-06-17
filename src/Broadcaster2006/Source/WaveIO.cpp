// WaveIO.cpp: implementation of the CWaveIO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\INCLUDE\WaveIO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWaveIO::CWaveIO()
{
	dwBufferSize=0;
	dwBytesRead=0;
	dwBytesWrite=0;
	dwDataSize=0;
	hMMIO=NULL;
	hWaveFormat=NULL;
	lpWaveFormat=NULL;
}

CWaveIO::~CWaveIO()
{
	if( hMMIO!=NULL )
		mmioClose(hMMIO,0);

	if( lpWaveFormat!=NULL ) 
	{
		GlobalUnlock(hWaveFormat);
		GlobalFree(hWaveFormat);
	}
}

// ----------------------------------------------------------------------
//	Rotina para inicializar um novo ficheiro
int CWaveIO::Initialize(CString strFile,DWORD Flags )
{
	dwFlags=Flags;
	if( hMMIO!=NULL )
	{
		// Estava um ficheiro aberto! Bora lá fechar o gajo -------------
		mmioClose(hMMIO,0);
		if( lpWaveFormat!=NULL )
		{
			GlobalUnlock(hWaveFormat);
			GlobalFree(hWaveFormat);
		}
	}

	// Verificar se existe o ficheiro -----------------------------------
	if( (access(strFile,0)!=0) && (dwFlags & WAVEF_PLAY ) )
		return WAVEERR_FILENOTFOUND;

	// Copia o nome do ficheiro -----------------------------------------
	strFileName=strFile;

	// Abrir o ficheiro -------------------------------------------------
	return OpenFile();
};

// Rotina para abrir o ficheiro -----------------------------------------
int CWaveIO::OpenFile() 
{
	memset( &mmIOInfo,0,sizeof(MMIOINFO));
	bReadyToPlay=FALSE;
	bReadyToRec=FALSE;

	// Abrir o ficheiro -------------------------------------------------
	hMMIO=mmioOpen((LPSTR)(LPCTSTR(strFileName)),&mmIOInfo,MMIO_DENYWRITE);
	if( hMMIO==NULL )
	{
		if( dwFlags & WAVEF_PLAY )
			return WAVEERR_FILENOTFOUND;
		else
		{
			hMMIO=mmioOpen( (LPSTR)(LPCTSTR(strFileName)),&mmIOInfo,MMIO_DENYWRITE|MMIO_CREATE);
			if( hMMIO!=NULL )
			{
				bReadyToPlay=FALSE;
				bReadyToRec=FALSE;
				return WAVEERR_NOERROR;
			}
			else
				return WAVEERR_INVALIDFILENAME;
		}
	}

	if( (dwFlags & WAVEF_PLAY) )
		return ReadWaveFormat();
	else
		return WAVEERR_NOERROR;
};

// ----------------------------------------------------------------------
//	Rotina para ler o formato do wave
int CWaveIO::ReadWaveFormat() 
{
	MMCKINFO mmckInfo;
	MMCKINFO mmckSubChunk;
	MMRESULT mmResult;

	// procurar o chunk WAVE --------------------------------------------
	mmckInfo.fccType=mmioFOURCC('W','A','V','E');
	mmResult=mmioDescend(hMMIO,&mmckInfo,NULL,MMIO_FINDRIFF);
	if( mmResult!=MMSYSERR_NOERROR ) 
	{
		CloseFile();
		return WAVEERR_FILENOTWAVE;
	}

	// Procurar o subchunck fmt (FORMATO DO WAVE) -----------------------
	mmckSubChunk.ckid=mmioFOURCC('f','m','t',' ');
	mmResult=mmioDescend(hMMIO,&mmckSubChunk,&mmckInfo,MMIO_FINDCHUNK);
	if( mmResult!=MMSYSERR_NOERROR ) 
	{
		CloseFile();
		return WAVEERR_FILECORRUPT;
	}

	// Obter o tamanho do FORMATO ---------------------------------------
	dwFormatSize=(WORD)mmckSubChunk.cksize;

	// Reservar espaço para os dados do formato
	hWaveFormat=GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,dwFormatSize);
	if( hWaveFormat==NULL ) 
	{
		CloseFile();
		return WAVEERR_NOMEM;
	}
	lpWaveFormat=(WAVEFORMATEX *)GlobalLock(hWaveFormat);
	if( lpWaveFormat==NULL )
	{
		CloseFile();
		GlobalFree(hWaveFormat);
		hWaveFormat=NULL;
		return WAVEERR_NOMEM;
	}

	// Le o formato do wave ---------------------------------------------
	if( mmioRead(hMMIO,(HPSTR)lpWaveFormat,dwFormatSize)!=(int)dwFormatSize )
	{
		CloseFile();
		GlobalUnlock(hWaveFormat);
		GlobalFree(hWaveFormat);
		hWaveFormat=NULL;
		lpWaveFormat=NULL;
		return WAVEERR_NOFORMAT;
	}
	if( (lpWaveFormat->wFormatTag==WAVE_FORMAT_MPEG) )
	{
		LPMPEG1WAVEFORMAT temp=(LPMPEG1WAVEFORMAT)lpWaveFormat;
		lpWaveFormat->cbSize=sizeof(MPEG1WAVEFORMAT)-sizeof(WAVEFORMATEX);
		temp->dwPTSHigh=0;
		temp->dwPTSLow=0;
		temp->fwHeadModeExt=0;
	}

	// Sai do formato ---------------------------------------------------
	mmioAscend(hMMIO,&mmckSubChunk,0);

	// Procura o subchunk DATA ------------------------------------------
	mmckSubChunk.ckid=mmioFOURCC('d','a','t','a');
	mmResult=mmioDescend(hMMIO,&mmckSubChunk,&mmckInfo,MMIO_FINDCHUNK);
	if( mmResult!=MMSYSERR_NOERROR )
	{
		CloseFile();
		GlobalUnlock(hWaveFormat);
		GlobalFree(hWaveFormat);
		hWaveFormat=NULL;
		lpWaveFormat=NULL;
		return WAVEERR_NODATA;
	}

	// Obtem o tamanho dos dados ----------------------------------------
	dwDataSize=mmckSubChunk.cksize;
	
	return WAVEERR_NOERROR;
};

// ----------------------------------------------------------------------
//	Rotina para ler um bloco de dados
int CWaveIO::ReadBuffer(LPVOID lpBuffer,DWORD dwSize ) 
{
	memset(lpBuffer,0,dwSize);
	int iResult=mmioRead(hMMIO,(HPSTR)lpBuffer,dwSize);
	dwBytesRead+=iResult;
	return iResult;
}

// ----------------------------------------------------------------------
//	Rotina para fechar o ficheiro
void CWaveIO::CloseFile() 
{
	mmioClose(hMMIO,0);
	hMMIO=NULL;
};

///////////////////////////////////////////////////////////////////////////
//	Prepares the File for recording
int CWaveIO::InitializeForRec(CString strFile )
{
	hMMIO = mmioOpen( strFile.GetBuffer(0), NULL, MMIO_ALLOCBUF  | 
                                                  MMIO_READWRITE | 
                                                  MMIO_CREATE );
	if( hMMIO==NULL )
		return WAVEERR_INVALIDFILENAME;

	WriteMMIO( );

	return WAVEERR_NOERROR;
}

int CWaveIO::WriteMMIO()
{
	DWORD			dwFactChunk; // Contains the actual fact chunk. Garbage until WaveCloseWriteFile.
    MMCKINFO		ckOut1;
	
    dwFactChunk = (DWORD)-1;

    // Create the output file RIFF chunk of form type 'WAVE'.
    m_ckRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');       
    m_ckRiff.cksize = 0;

    mmioCreateChunk( hMMIO, &m_ckRiff, MMIO_CREATERIFF );
    
    m_ck.ckid = mmioFOURCC('f', 'm', 't', ' ');
    m_ck.cksize = sizeof(WAVEFORMATEX);   

    mmioCreateChunk( hMMIO, &m_ck, 0 );
    
    // Write the PCMWAVEFORMAT structure to the 'fmt ' chunk if its that type. 
    if( lpWaveFormat->wFormatTag == WAVE_FORMAT_PCM )
    {
        mmioWrite( hMMIO,(HPSTR)lpWaveFormat,sizeof(PCMWAVEFORMAT) );
    }   
    else 
    {
    }  
    
	mmioAscend( hMMIO, &m_ck, 0 );
    
    ckOut1.ckid = mmioFOURCC('f', 'a', 'c', 't');
    ckOut1.cksize = 0;

    mmioCreateChunk( hMMIO, &ckOut1, 0 );
    
    mmioWrite( hMMIO, (HPSTR)&dwFactChunk, sizeof(dwFactChunk));
    
    mmioAscend( hMMIO, &ckOut1, 0 );

	m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
	m_ck.cksize = 0;

	mmioCreateChunk( hMMIO, &m_ck, 0 ) ;

	mmioGetInfo( hMMIO, &m_mmioinfoOut, 0 ) ;

	return WAVEERR_NOERROR;
}

int CWaveIO::CloseRec()
{
	m_mmioinfoOut.dwFlags |= MMIO_DIRTY;

	mmioSetInfo( hMMIO, &m_mmioinfoOut, 0 );
    
        // Ascend the output file out of the 'data' chunk -- this will cause
        // the chunk size of the 'data' chunk to be written.
    mmioAscend( hMMIO, &m_ck, 0 );
    
        // Do this here instead...
	mmioAscend( hMMIO, &m_ckRiff, 0 );
        
    mmioSeek( hMMIO, 0, SEEK_SET );

	mmioDescend( hMMIO, &m_ckRiff, NULL, 0 );
    
	m_ck.ckid = mmioFOURCC('f', 'a', 'c', 't');

    if( 0 == mmioDescend( hMMIO, &m_ck, &m_ckRiff, MMIO_FINDCHUNK ) ) 
    {
		DWORD dwSamples = 0;
		mmioWrite( hMMIO, (HPSTR)&dwSamples, sizeof(DWORD) );
        mmioAscend( hMMIO, &m_ck, 0 ); 
	}
    
        // Ascend the output file out of the 'RIFF' chunk -- this will cause
        // the chunk size of the 'RIFF' chunk to be written.
    mmioAscend( hMMIO, &m_ckRiff, 0 );
    
    mmioClose( hMMIO, 0 );
    hMMIO= NULL;

	return WAVEERR_NOERROR;
}

int CWaveIO::WriteData(UINT nSizeToWrite,BYTE *pbData)
{
	int SizeWrote=0;
    UINT cT;

    for( cT = 0; cT < nSizeToWrite; cT++ )
    {       
        if( m_mmioinfoOut.pchNext == m_mmioinfoOut.pchEndWrite )
        {
            m_mmioinfoOut.dwFlags |= MMIO_DIRTY;
            mmioAdvance( hMMIO, &m_mmioinfoOut, MMIO_WRITE );
        }

        *((BYTE*)m_mmioinfoOut.pchNext) = *((BYTE*)pbData+cT);
        (BYTE*)m_mmioinfoOut.pchNext++;

        SizeWrote++;
    }

    return SizeWrote;
}
