// typeLineUpItem.h: interface for the typeLineUpItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPELINEUPITEM_H__380FD8DC_2B6C_45BB_96A2_08A9520EFA4E__INCLUDED_)
#define AFX_TYPELINEUPITEM_H__380FD8DC_2B6C_45BB_96A2_08A9520EFA4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\include\AudioStream.h"

extern	CString	g_strOnAirConnect;

class typeLineUpItem  
{
public:
	Bitmap* CreateSpectrum(float xres,int height);
	long GetVolume();
	void CheckFadeOut();
	long GetTimeToIntro();
	long GetTimeToMix();
	long GetTimeToEnd();
	long GetLength();
	BOOL GetJingleData(long lID);
	BOOL GetMusicData(long lID);
	BOOL GetBlockData(long lID);
	BOOL GetSpotData(long ID);
	BOOL GetVoiceInsert(long lID);
	BOOL GetRMData(long lID);
	BOOL GetTimeSignal( long lID );
	BOOL GetRecording( long lID );
	void SetTimeFile();

	typeLineUpItem(WORD wType,long lID,DWORD64 qwTime=0,CString strConnect = g_strOnAirConnect);
	virtual ~typeLineUpItem();

	DWORD64		m_qwStartTime,
				m_qwOriginalStart;
	BOOL m_bItemIsValid;

	WORD		m_wType;
	long		m_lItemID;
	CString		m_strName;
	CString		m_strName2;

	
	BOOL		m_bFadeInOutOfTake;
	BOOL		m_bFadeOutIntoTake;
	BOOL		m_bPause;
	BOOL		m_bLoop;
	BOOL		m_bLocked;
	WORD		m_wState;
	WORD		m_wRythm;
	WORD		m_wPrecision;
	BOOL		m_bBlock;
	BOOL		m_bCanDelete;
	int			m_nMixCount;
	long		m_lOriginalIntro;
	long		m_lOriginalMix;
	long		m_lStartPos;
	long		m_lFadeInPos;
	long		m_lIntroPos;
	long		m_lFadeOutPos;
	long		m_lMixPos;
	long		m_lEndPos;
	long		m_lLoopA;
	long		m_lLoopB;
	long		m_lCurrentPos;

	long		m_lTrafficID;
	long		m_lScheduleID;
	long		m_lVoiceID;
	long		m_lBusinessID;
	long		m_lArtistID;

	LPVOID		m_pBlock[100];
	int			m_iBlockSize;
	int			m_iNextItem;
	long		m_lBlockID;
	long		m_lBlockTime;
	long		m_lBlockPos;
	long		m_lBlockLength;
	long		m_lBlockFinish;

	CAudioStream	*m_Sound;
	Bitmap			*m_bmSpectrum;
	CString			m_strFileName;
	CString			m_strConnect;
};

#endif // !defined(AFX_TYPELINEUPITEM_H__380FD8DC_2B6C_45BB_96A2_08A9520EFA4E__INCLUDED_)
