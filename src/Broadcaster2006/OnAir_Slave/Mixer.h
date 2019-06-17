#pragma once

class CMixer
{
public:
	virtual HRESULT SetVolume(float vol);
	virtual float GetVolume();
	virtual HRESULT LineFadeOut();
	virtual HRESULT LineFadeIn();
};

