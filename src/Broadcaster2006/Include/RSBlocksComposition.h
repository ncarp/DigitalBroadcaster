#if !defined(AFX_RSBLOCKSCOMPOSITION_H__6EB6D466_A18E_4E1D_A853_C30058E313A2__INCLUDED_)
#define AFX_RSBLOCKSCOMPOSITION_H__6EB6D466_A18E_4E1D_A853_C30058E313A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSBlocksComposition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSBlocksComposition recordset

class CRSBlocksComposition : public CRecordset
{
public:
	CRSBlocksComposition(CString str,CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSBlocksComposition)

// Field/Param Data
	//{{AFX_FIELD(CRSBlocksComposition, CRecordset)
	long	m_ID;
	long	m_Position;
	long	m_ItemType;
	long	m_ItemID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	long	m_Sun;
	long	m_Mon;
	long	m_Tue;
	long	m_Wed;
	long	m_Thu;
	long	m_Fri;
	long	m_Sat;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSBlocksComposition)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSBLOCKSCOMPOSITION_H__6EB6D466_A18E_4E1D_A853_C30058E313A2__INCLUDED_)
