#include "stdafx.h"
#include <Windows.h>
#include <InitGuid.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <FunctionDiscoveryKeys_devpkey.h>
#include <devicetopology.h>
#include <endpointvolume.h>
#include "MixerWasapi.h"

CMixerWasapi::CMixerWasapi(LPCWSTR pwstrid)
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator=NULL;
	IMMDevice *pDevice=NULL;

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL, CLSCTX_INPROC_SERVER,__uuidof(IMMDeviceEnumerator),(void**)&pEnumerator);
	if( hr==S_OK )
	{
		hr = pEnumerator->GetDevice(pwstrid,&pDevice);
		if( hr=S_OK )
		{
			LPWSTR ppstrId=NULL;

			pDevice->GetId(&ppstrId);
			wcscpy_s(m_guid,wcslen(ppstrId),ppstrId);

			CoTaskMemFree(ppstrId);

			IPropertyStore *pPropStore;
			hr = pDevice->OpenPropertyStore(STGM_READ,&pPropStore);
			if( hr==S_OK )
			{
				PROPVARIANT var;
				PropVariantInit(&var);

				hr = pPropStore->GetValue(PKEY_AudioEndpoint_GUID,&var);
				if( hr==S_OK )
					m_strName=var.bstrVal;
				else
					m_strName="N.D.";

				PropVariantClear(&var);

				pPropStore->Release();
			}
			pDevice->Release();
		}
		pEnumerator->Release();
	}
}


CMixerWasapi::~CMixerWasapi(void)
{

}

HRESULT CMixerWasapi::SetVolume(float vol)
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator=NULL;
	IMMDevice *pDevice=NULL;
	IAudioEndpointVolume *pVolume;

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_SERVER,__uuidof(IMMDeviceEnumerator),(void **)&pEnumerator);
	if( hr==S_OK )
	{
		hr = pEnumerator->GetDevice(m_pwstrid,&pDevice);
		if( hr==S_OK )
		{
			hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_INPROC_SERVER,NULL,(void **)&pVolume);
			if( hr=S_OK )
			{
				pVolume->SetMasterVolumeLevelScalar(vol,NULL);
				pVolume->Release();
			}
			pDevice->Release();
		}
		pEnumerator->Release();
	}

	return S_OK;
}

float CMixerWasapi::GetVolume()
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator=NULL;
	IMMDevice *pDevice=NULL;
	IAudioEndpointVolume *pVolume;
	float vol=0.0f;

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_SERVER,__uuidof(IMMDeviceEnumerator),(void **)&pEnumerator);
	if( hr==S_OK )
	{
		hr = pEnumerator->GetDevice(m_pwstrid,&pDevice);
		if( hr==S_OK )
		{
			hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_INPROC_SERVER,NULL,(void **)&pVolume);
			if( hr=S_OK )
			{
				hr=pVolume->GetMasterVolumeLevelScalar(&vol);
				if( hr!=S_OK )
					vol = -1.0f;

				pVolume->Release();
			}
			pDevice->Release();
		}
		pEnumerator->Release();
	}

	return vol;
}

HRESULT CMixerWasapi::LineFadeIn()
{
	AfxBeginThread( LineFadeInThread,(LPVOID)m_pwstrid );

	return S_OK;
}

HRESULT CMixerWasapi::LineFadeOut()
{
	AfxBeginThread( LineFadeOutThread,(LPVOID)m_pwstrid );

	return S_OK;
}

UINT CMixerWasapi::LineFadeInThread( LPVOID data )
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator=NULL;
	IMMDevice *pDevice=NULL;
	IAudioEndpointVolume *pVolume;

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_SERVER,__uuidof(IMMDeviceEnumerator),(void **)&pEnumerator);
	if( hr==S_OK )
	{
		hr = pEnumerator->GetDevice((LPCWSTR)data,&pDevice);
		if( hr==S_OK )
		{
			hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_INPROC_SERVER,NULL,(void **)&pVolume);
			if( hr=S_OK )
			{
				for( int i=0; i<100; i++ )
				{
					pVolume->SetMasterVolumeLevelScalar(0.01f*(float)i,NULL);
					Sleep(15);
				}
				pVolume->SetMasterVolumeLevelScalar(1.0f,NULL);
				pVolume->Release();
			}
			pDevice->Release();
		}
		pEnumerator->Release();
	}

	return 0;
}

UINT CMixerWasapi::LineFadeOutThread( LPVOID data )
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator=NULL;
	IMMDevice *pDevice=NULL;
	IAudioEndpointVolume *pVolume;

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_SERVER,__uuidof(IMMDeviceEnumerator),(void **)&pEnumerator);
	if( hr==S_OK )
	{
		hr = pEnumerator->GetDevice((LPCWSTR)data,&pDevice);
		if( hr==S_OK )
		{
			hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_INPROC_SERVER,NULL,(void **)&pVolume);
			if( hr=S_OK )
			{
				for( int i=100; i>0; i-- )
				{
					pVolume->SetMasterVolumeLevelScalar(0.01f*(float)i,NULL);
					Sleep(15);
				}
				pVolume->SetMasterVolumeLevelScalar(0.0f,NULL);
				pVolume->Release();
			}
			pDevice->Release();
		}
		pEnumerator->Release();
	}

	return 0;
}