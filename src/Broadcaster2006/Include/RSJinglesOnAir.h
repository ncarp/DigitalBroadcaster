#if !defined(AFX_RSJINGLESONAIR_H__D0CE8685_9930_4C23_91FF_AFD63FFDA328__INCLUDED_)
#define AFX_RSJINGLESONAIR_H__D0CE8685_9930_4C23_91FF_AFD63FFDA328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSJinglesOnAir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSJinglesOnAir recordset

class CRSJinglesOnAir : public CRecordset
{
public:
	CRSJinglesOnAir(CString str);
	DECLARE_DYNAMIC(CRSJinglesOnAir)

// Field/Param Data
	//{{AFX_FIELD(CRSJinglesOnAir, CRecordset)
	long	m_JingleID;
	COleDateTime m_StartingDate;
	COleDateTime m_EndingDate;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSJinglesOnAir)
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

#endif // !defined(AFX_RSJINGLESONAIR_H__D0CE8685_9930_4C23_91FF_AFD63FFDA328__INCLUDED_)
