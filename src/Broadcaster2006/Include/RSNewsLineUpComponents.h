#if !defined(AFX_RSNEWSLINEUPCOMPONENTS_H__2C78E28F_0733_4A28_8CE5_5569872A533E__INCLUDED_)
#define AFX_RSNEWSLINEUPCOMPONENTS_H__2C78E28F_0733_4A28_8CE5_5569872A533E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSNewsLineUpComponents.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSNewsLineUpComponents recordset

class CRSNewsLineUpComponents : public CRecordset
{
public:
	CRSNewsLineUpComponents(CString str);
	DECLARE_DYNAMIC(CRSNewsLineUpComponents)

// Field/Param Data
	//{{AFX_FIELD(CRSNewsLineUpComponents, CRecordset)
	long	m_LineUpID;
	long	m_Position;
	long	m_NewsID;
	long	m_Prev;
	long	m_Next;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSNewsLineUpComponents)
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

#endif // !defined(AFX_RSNEWSLINEUPCOMPONENTS_H__2C78E28F_0733_4A28_8CE5_5569872A533E__INCLUDED_)
