// AudioStream.h: interface for the CAudioStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIOSTREAM_H__10793F9A_5CDB_4F20_AFCD_7ED58BFC02A0__INCLUDED_)
#define AFX_AUDIOSTREAM_H__10793F9A_5CDB_4F20_AFCD_7ED58BFC02A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmreg.h>
#include <mmsystem.h>
#include <msacm.h>
#include <gdiplus.h>

#include "..\..\common\include\global.h"
#include "..\..\common\include\wavefile.h"
#include "..\..\common\include\mp3file.h"

#define ASERR_NOERROR		0
#define ASERR_FAIL			1
#define ASERR_NOMODEDEFINED 2
#define ASERR_NOMEM			3
#define ASERR_INVALIDFORMAT 4
#define ASERR_UNKNOWN		-1

#define ASMODE_NOTDEFINED	0
#define ASMODE_DIRECTPLAY	1
#define ASMODE_DIRECTREC	2
#define ASMODE_MCIPLAY		3
#define ASMODE_MCIREC		4

#define ASCUE_NOTCUED		0
#define ASCUE_CUEING		1
#define ASCUE_CUED			2

#define ASVIEW_DONTCREATE	0
#define ASVIEW_CREATE		1

#define ASMODEPLAY_PLAY		1
#define ASMODEPLAY_STOP		2
#define ASMODEPLAY_PAUSE	3
#define ASMODEPLAY_LOOP		4

typedef struct {
	LPWAVEFORMATEX	pwfx;
	HACMSTREAM		has;
	HANDLE			hBufferDst,
					hBufferSrc;
	ULONG			cbBufferDst;
	ULONG			cbBufferSrc;
	LPBYTE			lpBufferDst,
					lpBufferSrc;
	ACMSTREAMHEADER ash;
	long			lDataOnBuffer;
	CString			strPath;
} AUDIOCONVERTIONSTREAM;

class CAudioStream  : public CObject
{
// Data members
public:
	CWnd				*m_pParent;
	LPDIRECTSOUND		m_pDS;
	LPDIRECTSOUNDBUFFER	m_pDSB;
	LPWAVEFORMATEX		m_pwfx;
	Bitmap				*m_pbm;
	float				m_xres;
	long				m_lVolume,
						m_lFadeStartVol,
						m_lFadeEndVol;
	WAVEFORMATEX		m_wfxPcm;
	DWORD				m_dwBufferSize,
						m_dwBufferSizeSamples,
						m_dwFileReadPos,
						m_dwSamplesRead,
						m_dwStartPos,
						m_dwPlayMode,
						m_dwFadeStartTime,
						m_dwFadeEndTime,
						m_dwSrcSize,
						m_dwTotalBytesRead,
						m_dwSleep;
	DWORD64				m_qwStartingTime;
	BOOL				m_bDecompressAll;

protected:
	CString		m_strFilePcmAudio,
				m_strWavFile,
				m_strFileType;
	CFile		*m_filePcmAudio;
	CWaveFile	*m_pWave;
	CMp3File	*m_pMp3;
	HANDLE		m_hEvent[3];
	CWinThread	*m_pWaveDecompress,
				*m_pPlayThread;
	BOOL		m_bDecompressing,
				m_bStopDecompressing,
				m_bPlaying,
				m_bExitPlay,
				m_bFading,
				m_bRecording,
				m_bExitRec;
	AUDIOCONVERTIONSTREAM ConvertionStream;

// Implementation
protected:
	static UINT	WaveDecompress( LPVOID );
	static UINT PlayThread( LPVOID );
	static UINT	FadeThread( LPVOID );
	static UINT RecThread( LPVOID );
		   BOOL CreateRecConvertionStream();
		   void	CloseRecConvertionStream();
public:
	HRESULT CueSound();
	HRESULT	SetPosition( DWORD dwPos );
	void CreateSpectrum();
	void SetFile( CString strFile );
	void SetVolume( long lVolume );
	void Fade( long, DWORD );
	void Stop();
	void Play();
	void Pause();
	BOOL Rec();
	void StopRec();
	void ReadFromSrc( BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead );
	long GetTimeToEnd();
	long GetPosition();
	long GetDecompressedSize();
	DWORD	ReadAudioData( LPVOID,DWORD );
	DWORD GetSrcSize();
	DWORD GetLength();
	BOOL  IsDecompressing() {return m_bDecompressing;};
	CAudioStream( LPDIRECTSOUND lpds=g_pDS_MAIN, CWnd *p = NULL );
	virtual ~CAudioStream();

};

#endif // !defined(AFX_AUDIOSTREAM_H__10793F9A_5CDB_4F20_AFCD_7ED58BFC02A0__INCLUDED_)
