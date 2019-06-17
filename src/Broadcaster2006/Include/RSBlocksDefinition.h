#if !defined(AFX_RSBLOCKSDEFINITION_H__EB244911_6425_41F0_9566_48924D6480C9__INCLUDED_)
#define AFX_RSBLOCKSDEFINITION_H__EB244911_6425_41F0_9566_48924D6480C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSBlocksDefinition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSBlocksDefinition recordset

class CRSBlocksDefinition : public CRecordset
{
public:
	CRSBlocksDefinition(CString str,CDatabase *pdb=NULL);
	DECLARE_DYNAMIC(CRSBlocksDefinition)

// Field/Param Data
	//{{AFX_FIELD(CRSBlocksDefinition, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_Sun;
	long	m_Mon;
	long	m_Tue;
	long	m_Wed;
	long	m_Thu;
	long	m_Fry;
	long	m_Sat;
	long	m_Time;
	long	m_InsertionType;
	long	m_Sponsor;
	long	m_Activ;
	CString	m_DRM;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSBlocksDefinition)
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

#endif // !defined(AFX_RSBLOCKSDEFINITION_H__EB244911_6425_41F0_9566_48924D6480C9__INCLUDED_)
