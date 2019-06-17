#pragma once


// CControlWnd frame

#include "..\onair\mainclockwnd.h"
#include "SplitterLogo.h"

class CControlWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CControlWnd)
protected:
	CMainClockWnd	m_wndClock;
	CSplitterLogo	m_wndLogo;

public:
	CListCtrl		m_wndList;

public:
	CControlWnd();           // protected constructor used by dynamic creation
	virtual ~CControlWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};


