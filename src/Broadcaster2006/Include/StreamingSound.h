// StreamingSound.h: interface for the CStreamingSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAMINGSOUND_H__696FFDA8_31B3_4C9C_8DA3_11A22F70A9AE__INCLUDED_)
#define AFX_STREAMINGSOUND_H__696FFDA8_31B3_4C9C_8DA3_11A22F70A9AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\include\WaveFile.h"
#include "..\include\sound.h"

class CStreamingSound : public CSound
{
protected:
	CWinThread	*m_wtNotification;
	HANDLE	m_hNotificationEvent; 
    DWORD	m_dwLastPlayPos;
    DWORD	m_dwPlayProgress;
    DWORD	m_dwNotifySize;
    DWORD	m_dwNextWriteOffset;
    BOOL	m_bFillNextNotificationWithSilence;

public:
	DWORD dwFadeEndTime;
	DWORD dwFadeStartTime;
	long lFadeEndVol;
	long lFadeStartVol;
	void Fade( long startVol,long endVol, long time);
	void SetVolume(long Vol);
	DWORD GetCurrentPos();
	DWORD64 m_qwPlayStart;
	HRESULT Stop();
	HRESULT SetNotifications();
	CStreamingSound( LPDIRECTSOUNDBUFFER pDSBuffer, DWORD dwDSBufferSize, CWaveFile* pWaveFile );
	HRESULT Play( DWORD dwPriority = 0, DWORD dwFlags = DSBPLAY_LOOPING );

protected:
	static UINT FadeThread(LPVOID T);
	HRESULT HandleWaveStreamNotification(  );
	static UINT HandleNotificationsThread(LPVOID);
	virtual ~CStreamingSound();

};

#endif // !defined(AFX_STREAMINGSOUND_H__696FFDA8_31B3_4C9C_8DA3_11A22F70A9AE__INCLUDED_)
