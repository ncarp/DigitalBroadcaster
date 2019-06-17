#pragma once

#include <gdiplus.h>
using namespace Gdiplus;

#include "..\onair\onairplayerwnd.h"
#include "..\common\include\splitter_utils.h"
#include "..\onair\trafficinfownd.h"
#include "..\onair\proginfownd.h"
#include "mixer.h"

// COnAirSplitter

class COnAirSplitter : public CFrameWnd
{
	DECLARE_DYNAMIC(COnAirSplitter)
protected:
	CListCtrl		m_List;
	CTrafficInfoWnd *m_pTrafficInfo;
	CProgInfoWnd	*m_pProgInfo;
	CReBar			*m_pRebar;
	CToolBarCtrl	*m_pToolBar;
	
public:
	COnAirPlayerWnd	*m_pPlayer[4];
	CString			m_strConnect,
					m_strRadio,
					m_strAudio;
	BOOL			m_bEnabled,
					m_bStartBlock;
	WORD			m_wNSplitter;
	DWORD64			m_qwLineUpLength;
	long int		m_lBlockTime;

	CMixer			*m_pMixer;
/*	HMIXER				m_hMixer;
	MIXERCAPS			m_MixerCaps;
	MIXERLINE			m_MixerLine;
	MIXERLINECONTROLS	m_MixerLineControls;
	MIXERCONTROL		m_MixerControl;
	MIXERCONTROLDETAILS m_MixerControlDetails;
	MIXERCONTROLDETAILS_UNSIGNED m_MixerDetails[10]; 
	BOOL				m_bMixer;
	DWORD				m_dwMixerID,
						m_dwLineID;
	*/


public:
	COnAirSplitter();
	virtual ~COnAirSplitter();
	void	SplitterMsg( typeSplitterMsg *Msg);
	void	OnSplitterOpenBlock( CString strDate,long int lTime,long int lLength,WORD wFinish );
	void	OnSplitterCueBlock( CString strDate,long int lTime,long int lLength,WORD wFinish );
	void	OnSplitterPlayBlock( long lTime );
	DWORD64 GetPlayersTime();
	void	CutOnPlayer( long );
	typeLineUpItem *GetNextFiller( long );
	
protected:
	static UINT	LogItemThread( LPVOID );
	static UINT LineFadeInThread( LPVOID );
	static UINT LineFadeOutThread( LPVOID );

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnNcPaint();
	afx_msg void	OnPaint();
	afx_msg void	OnConfig();
	afx_msg void	OnReset();
			LRESULT	OnGetNextItem(WPARAM wParam=0,LPARAM lParam=0);
			LRESULT OnCalcStartingTimes(WPARAM wParam=0,LPARAM lParam=0);
			LRESULT OnSortPlayers(WPARAM wParam=0,LPARAM lParam=0);
			LRESULT OnStartNextPlayer(WPARAM w=0,LPARAM l=0);
			LRESULT OnLogItem(WPARAM,LPARAM);
			void ReadConfig(void);
	//		void PrepareMixer(void);
	//		void SetLineVolume(float fVol);
	//		void LineFadeIn();
	//		void LineFadeOut();
			void CheckProgram();
			void RemoveLeftOvers();
			void AddSchedule(long lID,DWORD64 qwMinTime);
			DWORD64 GetTotalLength();
			afx_msg void OnTimer(UINT nIDEvent);
};


