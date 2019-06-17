#if !defined(AFX_SHEDULEDLG_H__F8DE039A_0B50_477A_8F71_8FC5BC816773__INCLUDED_)
#define AFX_SHEDULEDLG_H__F8DE039A_0B50_477A_8F71_8FC5BC816773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SheduleDlg.h : header file
//
#include "ScheduleMain.h"
#include "ScheduleSpots.h"
#include "ScheduleBlocks.h"

/////////////////////////////////////////////////////////////////////////////
// CSheduleDlg

class CSheduleDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheduleDlg)

// Construction
public:
	CSheduleDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CScheduleMain	*m_pMain;
	CScheduleSpots	*m_pSpots;
	CScheduleBlocks *m_pBlocks;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheduleDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheduleDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheduleDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEDULEDLG_H__F8DE039A_0B50_477A_8F71_8FC5BC816773__INCLUDED_)
