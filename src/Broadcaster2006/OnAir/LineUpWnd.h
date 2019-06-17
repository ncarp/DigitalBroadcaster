#if !defined(AFX_LINEUPWND_H__FC71C80D_E35D_4E00_A150_837E51AC863E__INCLUDED_)
#define AFX_LINEUPWND_H__FC71C80D_E35D_4E00_A150_837E51AC863E__INCLUDED_

#include <afxmt.h>
#include "OnAirPlayerWnd.h"
#include "LineUpListBox.h"
#include "..\common\include\splitter_utils.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineUpWnd.h : header file
//

#include "OnAirDefines.h"

typedef struct
{
	COleDateTime dateTime;
	struct
	{
		long	lItemType,
				lItemID,
				lArtistID;
		CString	strArtist,
				strTitle;
	} Player[4];
} tLogPlayers;

class CPlayersLogQueue
{
	CWinThread *pWorkThread;
	CList<tLogPlayers> logQueue;
	CMutex	*mutexQueue;

public:
	CPlayersLogQueue();
	void AddItem(tLogPlayers);
	tLogPlayers * GetItem();
	BOOL Lock(DWORD dwTimeout=-1);
	BOOL Unlock();
	static UINT WorkThread(LPVOID);
};

/////////////////////////////////////////////////////////////////////////////
// CLineUpWnd frame

class CLineUpWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CLineUpWnd)
public:
	CLineUpWnd();           // protected constructor used by dynamic creation
	
// Attributes
public:
	COnAirPlayerWnd	*m_wndPlayer[4];
	CHeaderCtrl		*m_pHeader;
	CReBar			*m_pRebar;
	CLineUpListBox	*m_pList;
	CToolBarCtrl	*m_pToolBar;
	BOOL			*m_bLogging;
	tLogPlayers		m_Log[4];

// Mixer
	HMIXER				m_hMixer;
	MIXERCAPS			m_MixerCaps;
	MIXERLINE			m_MixerLine;
	MIXERLINECONTROLS	m_MixerLineControls;
	MIXERCONTROL		m_MixerControl;
	MIXERCONTROLDETAILS m_MixerControlDetails;
	MIXERCONTROLDETAILS_UNSIGNED m_MixerDetails[10];
// Operations
public:
	LRESULT OnBlockRDblClk( WPARAM,LPARAM);
	void OnInfo();
	LRESULT OnPause(WPARAM=0,LPARAM=0);
	LRESULT OnScroll(WPARAM=0,LPARAM=0);
	void ResetTimers();
	void OnPFL();
	void OnMoveDown();
	void OnMoveUp();
	void RemoveLeftOvers();
	void GetStartupSchedule();
	void RemoteControl( typeSplitterMsg msg );
	DWORD64 GetLastTrackTimeToMix();
	DWORD64 GetTotalLength();
	DWORD64 GetPlayersTime();
	LRESULT OnSpacePressed(WPARAM=0,LPARAM=0);
	LRESULT OnMakeSpace(WPARAM,LPARAM);
	void OnRemove();
	void AddItemByUnload( typeLineUpItem* lpItem);
	LRESULT OnStartNextPlayer(WPARAM w,LPARAM);
	LRESULT OnSortPlayers(WPARAM,LPARAM);
	LRESULT	OnPlayerStoped(WPARAM,LPARAM);
	DWORD64 m_qwLineUpLength;
	void CalcStartingTimes();
	typeLineUpItem* GetFirstItem();
	void AddItemByClick(typeArchiveItem *lpItem);
	void AddSchedule( long ID,DWORD64 qwMinLength=0 );
	void CutOnPlayer( long l );
	void LogPlayers();
	static UINT LogPlayersThread(LPVOID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineUpWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLineUpWnd();

	// Generated message map functions
	//{{AFX_MSG(CLineUpWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void OpenAuxMixer(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEUPWND_H__FC71C80D_E35D_4E00_A150_837E51AC863E__INCLUDED_)
