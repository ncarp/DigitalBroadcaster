#if !defined(AFX_PLAYLIST_H__99F6ACEC_DAEC_4EC5_BB67_7853348217AC__INCLUDED_)
#define AFX_PLAYLIST_H__99F6ACEC_DAEC_4EC5_BB67_7853348217AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayList dialog

class CPlayList : public CDialog
{
// Construction
public:
	CPlayList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayList)
	enum { IDD = IDD_PLAYLIST };
	BOOL	m_OnAir;
	CString	m_Name;
	//}}AFX_DATA
	CString m_strConnect;
	long	m_ID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayList)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLIST_H__99F6ACEC_DAEC_4EC5_BB67_7853348217AC__INCLUDED_)
