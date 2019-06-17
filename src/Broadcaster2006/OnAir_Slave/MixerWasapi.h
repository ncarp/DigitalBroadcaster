#pragma once
#include "mixer.h"
class CMixerWasapi : public CMixer
{
protected:
	LPCWSTR m_pwstrid;

public:
	CMixerWasapi(LPCWSTR);
	~CMixerWasapi(void);

	virtual HRESULT LineFadeIn();
	virtual HRESULT LineFadeOut();
	virtual HRESULT SetVolume(float);
	virtual float GetVolume();

protected:
	CString		m_strName;
	WCHAR		m_guid[100];
	static UINT LineFadeInThread(LPVOID);
	static UINT LineFadeOutThread(LPVOID);
};

