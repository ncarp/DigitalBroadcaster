#if !defined(AFX_RSVIEWJINGLESSCHEDULINGDATA_H__9E1001FC_45A3_4705_A228_4F62FF3A0A7B__INCLUDED_)
#define AFX_RSVIEWJINGLESSCHEDULINGDATA_H__9E1001FC_45A3_4705_A228_4F62FF3A0A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewJinglesSchedulingData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewJinglesSchedulingData recordset

class CRSViewJinglesSchedulingData : public CRecordset
{
public:
	CRSViewJinglesSchedulingData(CString str);
	DECLARE_DYNAMIC(CRSViewJinglesSchedulingData)

// Field/Param Data
	//{{AFX_FIELD(CRSViewJinglesSchedulingData, CRecordset)
	long	m_JingleID;
	COleDateTime m_StartingDate;
	COleDateTime m_EndingDate;
	CString	m_Name;
	long	m_Rythm;
	long	m_Length;
	long	m_Intro;
	CString	m_JingleType;
	COleDateTime m_MaxDate;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewJinglesSchedulingData)
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

#endif // !defined(AFX_RSVIEWJINGLESSCHEDULINGDATA_H__9E1001FC_45A3_4705_A228_4F62FF3A0A7B__INCLUDED_)
