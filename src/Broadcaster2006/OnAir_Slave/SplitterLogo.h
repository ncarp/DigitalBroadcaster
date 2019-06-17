#pragma once


// CSplitterLogo
#include <gdiplus.h>
using namespace Gdiplus;

class CSplitterLogo : public CStatic
{
	DECLARE_DYNAMIC(CSplitterLogo)
protected:
	Bitmap *m_bmBack;
public:
	CSplitterLogo();
	virtual ~CSplitterLogo();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


