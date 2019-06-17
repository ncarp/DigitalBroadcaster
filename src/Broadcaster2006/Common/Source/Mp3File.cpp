// Mp3File.cpp: implementation of the CMp3File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <winsock.h>

#include "..\INCLUDE\Mp3File.h"
#include "..\include\defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MPEG_VERSION_25			0x00
#define MPEG_VERSION_RESERVED	0x01
#define MPEG_VERSION_2			0x02
#define MPEG_VERSION_1			0x03

#define MPEG_LAYER_RESERVED		0x00
#define MPEG_LAYER_III			0x01
#define MPEG_LAYER_II			0x02
#define MPEG_LAYER_I			0x03

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMp3File::CMp3File()
{
	m_pwfx = NULL;
	m_dwFileSize = 0xffffffff;
}

CMp3File::~CMp3File()
{
	if( m_dwFileSize!=0xffffffff )
		m_File.Close();
}

HRESULT CMp3File::Open(CString strFile)
{
	UINT	ret,
			padding=0;
	DWORD	dwSize;

	if( m_File.Open(strFile,CFile::modeRead|CFile::shareDenyNone)==0 )
		return E_FAIL;

	m_dwFileSize = (DWORD)m_File.GetLength();
	
	ret = m_File.Read(&m_ID3Header,sizeof(ID3Header));
	if( ret!=sizeof(ID3Header) )
		return E_FAIL;

	if( strncmp(m_ID3Header.tag,"ID3",3) )
	{
		m_File.SeekToBegin();
		m_dwDataSize = m_dwFileSize;

		return GetAudioFormat();
	}

	dwSize =	( m_ID3Header.size[3] & 0x7f	   ) |
				((m_ID3Header.size[2] & 0x7f) << 7 ) |
				((m_ID3Header.size[1] & 0x7f) << 14) |
				((m_ID3Header.size[0] & 0x7f) << 21);

	if( m_ID3Header.flags & (1 << 6) )
	{
		unsigned	extHeaderSize;
		long		lNet;

		if( m_File.Read(&extHeaderSize,sizeof(unsigned))!=sizeof(int) )
			return S_OK;

		m_File.Seek(sizeof(DWORD)+sizeof(WORD),SEEK_CUR);
		if( m_File.Read(&lNet,sizeof(long))!=-1 )
			return E_FAIL;

		padding = ntohl(lNet);
	}
	m_File.Seek(dwSize+padding,SEEK_CUR);
	m_dwDataSize = m_dwFileSize-(DWORD)m_File.GetPosition();

	return GetAudioFormat();
}

HRESULT CMp3File::GetAudioFormat()
{
	SAFE_DELETE( m_pwfx );
	
	char	header[4];
	WORD	bitrateindex [16][5] =
				{0	,0	,0	,0	,0
				,32	,32	,32	,32	,8
				,64	,48	,40	,48	,16
				,96	,56	,48	,56	,24
				,128,64	,56	,64	,32
				,160,80	,64	,80	,40
				,192,96	,80	,96	,48
				,224,112,96	,112,56
				,256,128,112,128,64
				,288,160,128,144,80
				,320,192,160,160,96
				,352,224,192,176,112
				,384,256,224,192,128
				,416,320,256,224,144
				,448,384,320,256,160
				,0	,0	,0	,0	,0 	};
	
	DWORD	samplerateindex [4][3] = {
					44100,	22050,	11025,
					48000,	24000,	12000,
					32000,	16000,	8000,
					0,		0,		0};
	BOOL	bFormatFound = FALSE,
			bEndOfFile = FALSE;

	while( !bFormatFound && !bEndOfFile )
	{
		if( m_File.Read(header,4)!=4 )
			bEndOfFile=TRUE;
		else
		{
			if( ((header[0] & 0xff) != 0xff) || ((header[1] & 0xe0) != 0xe0 ) || ((header[1] & 0x06)!=0x02))
			{
				m_dwDataSize--;
				m_File.Seek(-3,SEEK_CUR);
			}
			else
			{
				m_File.Seek(-4,SEEK_CUR);
				bFormatFound=TRUE;
			}
		}
	}

	BYTE	mpegVersion = (header[1] & 0x18) >> 3,
			layer		= (header[1] & 0x06) >> 1,
			crc			= (header[1] & 0x01),
			bitrate		= (header[2] & 0xf0) >> 4,
			samplerate	= (header[2] & 0x0c) >> 2,
			padding		= (header[2] & 0x02) >> 1,
			channelmode = (header[3] & 0xc0) >> 6,
			extension	= (header[3] & 0x30) >> 4,
			emphasis	= (header[3] & 0x03);
	int		nBitRate,
			nSampleRate,
			nChannels;

	if( mpegVersion == MPEG_VERSION_RESERVED )
		return E_FAIL;

	if( layer == MPEG_LAYER_RESERVED )
		return E_FAIL;

	if( (mpegVersion == MPEG_VERSION_1) && (layer==MPEG_LAYER_I) )
		nBitRate = 0;
	else if( (mpegVersion == MPEG_VERSION_1) && (layer==MPEG_LAYER_II) )
		nBitRate = 1;
	else if( (mpegVersion == MPEG_VERSION_1) && (layer==MPEG_LAYER_III) )
		nBitRate = 2;
	else if( ((mpegVersion == MPEG_VERSION_2) || (mpegVersion==MPEG_VERSION_25)) && (layer==MPEG_LAYER_I) )
		nBitRate = 3;
	else if( ((mpegVersion == MPEG_VERSION_2) || (mpegVersion==MPEG_VERSION_25)) && ((layer==MPEG_LAYER_I) || (layer==MPEG_LAYER_III)) )
		nBitRate = 4;
	else 
		return E_FAIL;


	if( samplerate==0x03 )
		return E_FAIL;
	if( mpegVersion == MPEG_VERSION_1 )
		nSampleRate= 0;
	else if( mpegVersion == MPEG_VERSION_2 )
		nSampleRate= 1;
	else
		nSampleRate= 2;

	if( channelmode == 0x03 )
		nChannels = 1;
	else
		nChannels = 2;

	m_pwfx = (LPMPEGLAYER3WAVEFORMAT)malloc(sizeof(MPEGLAYER3WAVEFORMAT));
	m_pwfx->wfx.wFormatTag		= WAVE_FORMAT_MPEGLAYER3;
	m_pwfx->wfx.nChannels		= nChannels;
	m_pwfx->wfx.nSamplesPerSec	= samplerateindex[samplerate][nSampleRate];
	m_pwfx->wfx.nAvgBytesPerSec = bitrateindex[bitrate][nBitRate]*128;
	m_pwfx->wfx.nBlockAlign		= 1;
	m_pwfx->wfx.wBitsPerSample	= 0;
	m_pwfx->wfx.cbSize			= sizeof(MPEGLAYER3WAVEFORMAT)-sizeof(WAVEFORMATEX);
	m_pwfx->wID					= MPEGLAYER3_ID_MPEG;
	m_pwfx->fdwFlags			= 0;
	m_pwfx->nCodecDelay			= 0;
	m_pwfx->nFramesPerBlock		= 1;

	if( (mpegVersion & 0x01)==0x01 )
		m_pwfx->nBlockSize = (WORD)((144*bitrateindex[bitrate][nBitRate]*1000)/samplerateindex[samplerate][nSampleRate]);
	else
		m_pwfx->nBlockSize = (WORD)((77*bitrateindex[bitrate][nBitRate]*1000)/samplerateindex[samplerate][nSampleRate]);


	return S_OK;
}

void CMp3File::Read(LPBYTE pBuffer,DWORD dwSize,DWORD *pdwRead)
{
	*pdwRead = m_File.Read( pBuffer,dwSize );
}