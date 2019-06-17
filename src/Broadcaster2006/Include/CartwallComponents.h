#if !defined(AFX_CARTWALLCOMPONENTS_H__512CB1D2_FE28_4024_B4C5_5AED3D3D5792__INCLUDED_)
#define AFX_CARTWALLCOMPONENTS_H__512CB1D2_FE28_4024_B4C5_5AED3D3D5792__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CartwallComponents.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCartwallComponents recordset

class CCartwallComponents : public CRecordset
{
public:
	CCartwallComponents(CString str);
	DECLARE_DYNAMIC(CCartwallComponents)

// Field/Param Data
	//{{AFX_FIELD(CCartwallComponents, CRecordset)
	long	m_CartwallID;
	long	m_Position;
	long	m_Type;
	long	m_ElementID;
	long	m_AutoFade;
	long	m_Loop;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCartwallComponents)
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

#endif // !defined(AFX_CARTWALLCOMPONENTS_H__512CB1D2_FE28_4024_B4C5_5AED3D3D5792__INCLUDED_)
