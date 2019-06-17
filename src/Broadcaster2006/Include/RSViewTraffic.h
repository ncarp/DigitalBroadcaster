#if !defined(AFX_RSVIEWTRAFFIC_H__5AA91D3F_A5AE_416F_8759_5DF229C97E36__INCLUDED_)
#define AFX_RSVIEWTRAFFIC_H__5AA91D3F_A5AE_416F_8759_5DF229C97E36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewTraffic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewTraffic recordset

class CRSViewTraffic : public CRecordset
{
public:
	CRSViewTraffic(CString str="",CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSViewTraffic)

// Field/Param Data
	//{{AFX_FIELD(CRSViewTraffic, CRecordset)
	long	m_ID;
	long	m_BlockID;
	TIMESTAMP_STRUCT	m_BlockDate;
	long	m_Position;
	long	m_SpotID;
	long	m_TypeOfBusinessID;
	long	m_MainVoiceID;
	long	m_N;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewTraffic)
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

#endif // !defined(AFX_RSVIEWTRAFFIC_H__5AA91D3F_A5AE_416F_8759_5DF229C97E36__INCLUDED_)
