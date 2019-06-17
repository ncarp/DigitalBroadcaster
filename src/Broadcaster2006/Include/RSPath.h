#if !defined(AFX_RSPATH_H__B7528395_4E90_4523_9D21_732CA20DB70C__INCLUDED_)
#define AFX_RSPATH_H__B7528395_4E90_4523_9D21_732CA20DB70C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSPath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSPath recordset

class CRSPath : public CRecordset
{
public:
	CRSPath(CString str);
	DECLARE_DYNAMIC(CRSPath)

// Field/Param Data
	//{{AFX_FIELD(CRSPath, CRecordset)
	long	m_ID;
	CString	m_Path;
	long	m_Music;
	long	m_Jingles;
	long	m_Spots;
	long	m_RMs;
	long	m_TimeSignal;
	long	m_Takes;
	long	m_Producer;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSPath)
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

#endif // !defined(AFX_RSPATH_H__B7528395_4E90_4523_9D21_732CA20DB70C__INCLUDED_)
