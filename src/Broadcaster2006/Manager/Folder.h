#if !defined(AFX_FOLDER_H__16BE86A9_8777_44FF_B15E_A7E723180DBD__INCLUDED_)
#define AFX_FOLDER_H__16BE86A9_8777_44FF_B15E_A7E723180DBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Folder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFolder dialog

class CFolder : public CDialog
{
// Construction
public:
	CFolder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFolder)
	enum { IDD = IDD_FOLDER };
	BOOL	m_bJingles;
	BOOL	m_bMusic;
	CString	m_strPath;
	BOOL	m_bProducer;
	BOOL	m_bRMs;
	BOOL	m_bSpots;
	BOOL	m_bTakes;
	BOOL	m_bTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFolder)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDER_H__16BE86A9_8777_44FF_B15E_A7E723180DBD__INCLUDED_)
