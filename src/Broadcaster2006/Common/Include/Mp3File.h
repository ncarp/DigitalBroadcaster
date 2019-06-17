// Mp3File.h: interface for the CMp3File class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP3FILE_H__D15F0E76_4FFA_457F_A2BD_17CFA9E2113B__INCLUDED_)
#define AFX_MP3FILE_H__D15F0E76_4FFA_457F_A2BD_17CFA9E2113B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>

struct ID3Header
{
   char          tag[3];
   unsigned char versionMajor;
   unsigned char versionRevision;
   unsigned char flags;
   unsigned char size[4];
};

class CMp3File  
{
protected:
	CFile		m_File;
	ID3Header	m_ID3Header;

public:
	LPMPEGLAYER3WAVEFORMAT	m_pwfx;
	DWORD			m_dwFileSize,
					m_dwDataSize;
	CMp3File();
	virtual ~CMp3File();
	
	HRESULT	Open(CString strFile);
	HRESULT	GetAudioFormat();

	void	Read( LPBYTE pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead );
};

#endif // !defined(AFX_MP3FILE_H__D15F0E76_4FFA_457F_A2BD_17CFA9E2113B__INCLUDED_)
