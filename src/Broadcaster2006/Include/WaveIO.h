// WaveIO.h: interface for the CWaveIO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEIO_H__A7C69D08_C326_47A8_AD31_050270FC6893__INCLUDED_)
#define AFX_WAVEIO_H__A7C69D08_C326_47A8_AD31_050270FC6893__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <io.h>
#include <mmsystem.h>
#include <mmreg.h>

#define WAVEF_CREATE	0x00000001
#define WAVEF_PLAY		0x00000002

#define	WAVEERR_NOERROR			0
#define WAVEERR_FILENOTWAVE		1
#define WAVEERR_FILECORRUPT		2
#define WAVEERR_FILENOTFOUND	3
#define WAVEERR_NOMEM			4
#define WAVEERR_NODATA			5
#define WAVEERR_NOFORMAT		6
#define WAVEERR_INVALIDFILENAME 7

class CWaveIO : public CObject
{
public:
	LPWAVEFORMATEX	lpWaveFormat;
protected:
	DWORD			dwBytesRead;
	DWORD			dwBytesWrite;
	DWORD			dwDataSize;
	DWORD			dwBufferSize;
	DWORD			dwFormatSize;
	
	DWORD			dwFlags;
	HMMIO			hMMIO;
	MMIOINFO		mmIOInfo;
	MMCKINFO		m_ck;          // Multimedia RIFF chunk
    MMCKINFO		m_ckRiff;      // Use in opening a WAVE file
	MMIOINFO		m_mmioinfoOut;
	
	HANDLE			hWaveFormat;
	BOOL			bReadyToPlay;
	BOOL			bReadyToRec;
	CString			strFileName;
public:
	CWaveIO();
	virtual ~CWaveIO();
	
	int				Initialize(CString strFile,DWORD Flags=0);
	int				ReadBuffer(LPVOID lpBuffer,DWORD dwSize);
	LPWAVEFORMATEX	GetFormat() {return lpWaveFormat; };
	DWORD			GetFormatSize() {return dwFormatSize; };
	DWORD			GetDataSize() {return dwDataSize; };
	DWORD			GetBytesRead() {return dwBytesRead; };
	DWORD			GetBytesWrite() {return dwBytesWrite; };
	void			GetErrorString(char *strError,DWORD dwError);

	int				InitializeForRec( CString strFile );
	int				WriteMMIO();
	int				WriteData(UINT nSizeToWrite,BYTE *pbData);
	int				CloseRec();
protected:
	int		OpenFile();
	void	CloseFile();
	int		ReadWaveFormat();
};

#endif // !defined(AFX_WAVEIO_H__A7C69D08_C326_47A8_AD31_050270FC6893__INCLUDED_)
