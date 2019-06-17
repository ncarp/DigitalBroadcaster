#include "stdafx.h"
#include "BroadcasterMixer.h"

CBroadcasterMixer::CBroadcasterMixer(DWORD dwMixerId,DWORD dwLineId)
{
	if( GetMixer(dwMixerId)==NULL )
		return;


}

DWORD CBroadcasterMixer::GetLineVolume() {
	return 0;
};

void CBroadcasterMixer::SetLineVolume(DWORD dwVolume)
{
};

HMIXER CBroadcasterMixer::GetMixer(DWORD dwMixerID)
{
	MMRESULT mResult;
	HMIXER hMixer=NULL;

	mResult=mixerOpen(&hMixer,dwMixerID,NULL,NULL,MIXER_OBJECTF_MIXER);
	if( mResult!=MMSYSERR_NOERROR )
	{
		// Log error message
	}

	return hMixer;
};

