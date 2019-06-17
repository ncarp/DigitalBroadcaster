#if !defined(AFX_ONAIRUSER_H__4A6B6F17_F3FC_416E_8DA7_ACB2D8F3B640__INCLUDED_)
#define AFX_ONAIRUSER_H__4A6B6F17_F3FC_416E_8DA7_ACB2D8F3B640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnAirUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COnAirUser dialog

class COnAirUser : public CDialog
{
// Construction
public:
	COnAirUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COnAirUser)
	enum { IDD = IDD_ONAIRUSER };
	BOOL	m_Blocks;
	BOOL	m_MusicEditing;
	CString	m_Name;
	CString	m_Pass1;
	CString	m_Pass2;
	BOOL	m_Schedule;
	BOOL	m_SoundRecorder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COnAirUser)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRUSER_H__4A6B6F17_F3FC_416E_8DA7_ACB2D8F3B640__INCLUDED_)
