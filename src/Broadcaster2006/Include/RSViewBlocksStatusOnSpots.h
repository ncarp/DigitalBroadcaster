#if !defined(AFX_RSVIEWBLOCKSSTATUSONSPOTS_H__A9BC7FDA_3EFE_4E5F_BF16_ECF35F47281A__INCLUDED_)
#define AFX_RSVIEWBLOCKSSTATUSONSPOTS_H__A9BC7FDA_3EFE_4E5F_BF16_ECF35F47281A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewBlocksStatusOnSpots.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewBlocksStatusOnSpots recordset

class CRSViewBlocksStatusOnSpots : public CRecordset
{
public:
	CRSViewBlocksStatusOnSpots(CString str);
	DECLARE_DYNAMIC(CRSViewBlocksStatusOnSpots)

// Field/Param Data
	//{{AFX_FIELD(CRSViewBlocksStatusOnSpots, CRecordset)
	long	m_BlockID;
	CTime	m_BlockDate;
	long	m_nSpots;
	long	m_SpotsLength;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewBlocksStatusOnSpots)
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

#endif // !defined(AFX_RSVIEWBLOCKSSTATUSONSPOTS_H__A9BC7FDA_3EFE_4E5F_BF16_ECF35F47281A__INCLUDED_)
