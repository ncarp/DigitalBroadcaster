// Sound.h: interface for the CSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_H__9B39519E_D547_4B08_8E6F_B7DB805AD6E7__INCLUDED_)
#define AFX_SOUND_H__9B39519E_D547_4B08_8E6F_B7DB805AD6E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dsound.h>
#include "..\common\include\WaveFile.h"

class CSound  
{
protected:
    LPDIRECTSOUNDBUFFER* m_apDSBuffer;
    DWORD                m_dwDSBufferSize;
    CWaveFile*           m_pWaveFile;
    DWORD                m_dwNumBuffers;

    HRESULT RestoreBuffer( LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored );

public:
	long SetPosition(long Pos);
    CSound( LPDIRECTSOUNDBUFFER* apDSBuffer, DWORD dwDSBufferSize, DWORD dwNumBuffers, CWaveFile* pWaveFile );
    virtual ~CSound();

    HRESULT FillBufferWithSound( LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger );
    LPDIRECTSOUNDBUFFER GetFreeBuffer();
    LPDIRECTSOUNDBUFFER GetBuffer( DWORD dwIndex );

    HRESULT Play( DWORD dwPriority = 0, DWORD dwFlags = DSBPLAY_LOOPING );
    HRESULT Stop();
    HRESULT Reset();
    BOOL    IsSoundPlaying();
};

#endif // !defined(AFX_SOUND_H__9B39519E_D547_4B08_8E6F_B7DB805AD6E7__INCLUDED_)
