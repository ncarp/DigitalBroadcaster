#if !defined(AFX_RSVIEWSCHEDULINGTEMPLATE_H__A1BA301E_D938_415C_9234_DA8D179134FE__INCLUDED_)
#define AFX_RSVIEWSCHEDULINGTEMPLATE_H__A1BA301E_D938_415C_9234_DA8D179134FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSchedulingTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSchedulingTemplate recordset

class CRSViewSchedulingTemplate : public CRecordset
{
public:
	CRSViewSchedulingTemplate(CString str);
	DECLARE_DYNAMIC(CRSViewSchedulingTemplate)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSchedulingTemplate, CRecordset)
	long	m_ID;
	long	m_Type;
	CString	m_Name;
	CString	m_CategoryName;
	long	m_Category;
	long	m_PlayList;
	CString	m_PlayListName;
	long	m_Expression;
	CString	m_ExpressionName;
	long	m_MinRythm;
	long	m_MaxRythm;
	long	m_MinLen;
	long	m_MaxLen;
	long	m_ArtistQuarantine;
	long	m_RandomFactor;
	long	m_SongQuarantine;
	//}}AFX_FIELD
	
	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSchedulingTemplate)
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

#endif // !defined(AFX_RSVIEWSCHEDULINGTEMPLATE_H__A1BA301E_D938_415C_9234_DA8D179134FE__INCLUDED_)
