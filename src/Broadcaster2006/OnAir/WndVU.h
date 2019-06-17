#pragma once


// CWndVU

class CWndVU : public CStatic
{
	DECLARE_DYNAMIC(CWndVU)

public:
	Bitmap	*m_bmBack;

	CWndVU();
	virtual ~CWndVU();

protected:
	DECLARE_MESSAGE_MAP()
	void	CreateBitmaps();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};


