#if !defined(AFX_BLOCKS_H__5050969F_C37D_451F_AE3D_494E9EEB3D41__INCLUDED_)
#define AFX_BLOCKS_H__5050969F_C37D_451F_AE3D_494E9EEB3D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Blocks.h : header file
//

typedef struct
{
	long	ID;
	WORD	Type;
	BOOL	Days[7];
	COleDateTime	StartingDate,
					EndingDate;
} typeBlockItem;

/////////////////////////////////////////////////////////////////////////////
// CBlocks dialog

class CBlocks : public CDialog
{
// Construction
public:
	CBlocks(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBlocks)
	enum { IDD = IDD_BLOCKS };
	CTreeCtrl	m_cLibrary;
	CListCtrl	m_cContents;
	BOOL	m_Fri;
	BOOL	m_Mon;
	CString	m_Name;
	int		m_Precision;
	BOOL	m_Tue;
	COleDateTime	m_Time;
	BOOL	m_Thu;
	BOOL	m_Sun;
	BOOL	m_Sat;
	BOOL	m_Wed;
	//}}AFX_DATA

	long	m_ID;
	BOOL	m_Normal,
			m_Sponsor;
	int		m_nItems;
	CString	m_strConnect;
	typeBlockItem	*m_Items[100];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlocks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBlocks)
	virtual void OnOK();
	afx_msg void OnSponsor();
	afx_msg void OnRemove();
	afx_msg void OnPfl();
	afx_msg void OnNormal();
	afx_msg void OnMoveup();
	afx_msg void OnMovedown();
	afx_msg void OnDblclkLibrary(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkContents(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOCKS_H__5050969F_C37D_451F_AE3D_494E9EEB3D41__INCLUDED_)
