#if !defined __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "..\include\StreamingSound.h"

class CSoundManager  
{
protected:
    LPDIRECTSOUND m_pDS;

public:
    CSoundManager();
    ~CSoundManager();

    HRESULT Initialize( LPGUID lpGuid, HWND hWnd, DWORD dwCoopLevel, DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate );
    inline  LPDIRECTSOUND GetDirectSound() { return m_pDS; }
    HRESULT SetPrimaryBufferFormat( DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate );

    HRESULT CreateStreaming( CStreamingSound** ppStreamingSound, CString strWaveFileName );
};

#endif 
