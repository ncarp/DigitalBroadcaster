#if !defined(AFX_SOUNDRECORDERWND_H__10FFD5A7_3986_4525_9AC2_709C1C263EBC__INCLUDED_)
#define AFX_SOUNDRECORDERWND_H__10FFD5A7_3986_4525_9AC2_709C1C263EBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoundRecorderWnd.h : header file
//

#include <afxhtml.h>
#include "OnAirHtml.h"

/////////////////////////////////////////////////////////////////////////////
// CSoundRecorderWnd window

#include "recorder.h"

class CSoundRecorderWnd : public CStatic
{
// Construction
public:
	CSoundRecorderWnd();

// Attributes
public:
	CRecorder	*m_pRecorder;
	COnAirHtml	*m_pInfo;

	long	m_PathID,
			m_RecordingID;
	CString m_strFileName,
			m_strPath,
			m_strName;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundRecorderWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	CRect m_rect;
	void ShowTask(long ID);
	virtual ~CSoundRecorderWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSoundRecorderWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDRECORDERWND_H__10FFD5A7_3986_4525_9AC2_709C1C263EBC__INCLUDED_)
