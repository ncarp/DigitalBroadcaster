#if !defined(AFX_RSVIEWMINMAXSCHEDULEYEAR_H__9C1AD1D7_4B26_4D8E_B120_B12E0146E0AD__INCLUDED_)
#define AFX_RSVIEWMINMAXSCHEDULEYEAR_H__9C1AD1D7_4B26_4D8E_B120_B12E0146E0AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewMinMaxScheduleYear.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewMinMaxScheduleYear recordset

class CRSViewMinMaxScheduleYear : public CRecordset
{
public:
	CRSViewMinMaxScheduleYear(CString str);
	DECLARE_DYNAMIC(CRSViewMinMaxScheduleYear)

// Field/Param Data
	//{{AFX_FIELD(CRSViewMinMaxScheduleYear, CRecordset)
	long	m_Min;
	long	m_Max;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewMinMaxScheduleYear)
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

#endif // !defined(AFX_RSVIEWMINMAXSCHEDULEYEAR_H__9C1AD1D7_4B26_4D8E_B120_B12E0146E0AD__INCLUDED_)
