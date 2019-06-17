#pragma once


// COnAirContainerWnd frame

class COnAirContainerWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(COnAirContainerWnd)
public:
	COnAirContainerWnd();           // protected constructor used by dynamic creation
	virtual ~COnAirContainerWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};


