#if !defined(AFX_TRAFFICINFOWND_H__A4E53D2E_3C04_4504_A29B_3CA0C6F857FB__INCLUDED_)
#define AFX_TRAFFICINFOWND_H__A4E53D2E_3C04_4504_A29B_3CA0C6F857FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrafficInfoWnd.h : header file
//

#include "typeLineUpItem.h"
/////////////////////////////////////////////////////////////////////////////
// CTrafficInfoWnd window

class CTrafficInfoWnd : public CStatic
{
// Construction
public:
	CTrafficInfoWnd();

// Attributes
public:
	Bitmap	*m_bmCrono;
	Bitmap	*m_bmBack;
	CBitmap *m_bmSpot,
			*m_bmJingle;
	typeLineUpItem* m_pNextBlock;
	CString	m_strOnAirConnect;

protected:
	DWORD64 m_qwLastBlock;
	DWORD64 m_qwBlockTime;
	CString m_strInfo;
	BOOL	m_bAutoStartBlock;
	CMenu	*m_Menu,
			*m_ContentMenu;
// Operations
public:
	void OnRefresh();
	void OnLineUp();
	void OnDelay1();
	void OnDelay2();
	void OnDelay5();
	void OnSkip();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficInfoWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBackBitmap(CClientDC *dc);
	void SetCronoBitmap( CClientDC *dc);
	void GetNextBlock( );
	void PaintCrono();
	void CheckBlockEntry();
	void Sync();
	virtual ~CTrafficInfoWnd();

	static UINT GetNextBlockThread( LPVOID lp);
	// Generated message map functions
protected:
	//{{AFX_MSG(CTrafficInfoWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysColorChange();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAFFICINFOWND_H__A4E53D2E_3C04_4504_A29B_3CA0C6F857FB__INCLUDED_)
