#if !defined(AFX_CONFIGPROPERTY_H__3D5D34F0_7609_4E34_95BF_BCBB08A2200A__INCLUDED_)
#define AFX_CONFIGPROPERTY_H__3D5D34F0_7609_4E34_95BF_BCBB08A2200A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigProperty.h : header file
//
#include "ConfigDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigProperty

class CConfigProperty : public CPropertySheet
{
	DECLARE_DYNAMIC(CConfigProperty)

// Construction
public:
	CConfigProperty(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CConfigProperty(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CConfigDlg *dlAudio;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigProperty)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConfigProperty();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConfigProperty)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGPROPERTY_H__3D5D34F0_7609_4E34_95BF_BCBB08A2200A__INCLUDED_)
