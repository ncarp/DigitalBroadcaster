
#include <afxwin.h>
#include <mmsystem.h>


class CBroadcasterMixer
{
protected:
	DWORD m_dwMixerId;
	DWORD m_dwLineId;
	HMIXER m_hMixer;

public:
	CBroadcasterMixer(DWORD dwMixerId,DWORD dwLineId);
	void SetLineVolume(DWORD dwVolume);
	DWORD GetLineVolume();

	static HMIXER GetMixer(DWORD dwMixerId);
};
