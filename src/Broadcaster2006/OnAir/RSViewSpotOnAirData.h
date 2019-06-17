#if !defined(AFX_RSVIEWSPOTONAIRDATA_H__49030E85_3540_4491_A450_F12AF8E0EFFD__INCLUDED_)
#define AFX_RSVIEWSPOTONAIRDATA_H__49030E85_3540_4491_A450_F12AF8E0EFFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSpotOnAirData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotOnAirData recordset

class CRSViewSpotOnAirData : public CRecordset
{
public:
	CRSViewSpotOnAirData(CString str);
	DECLARE_DYNAMIC(CRSViewSpotOnAirData)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSpotOnAirData, CRecordset)
	long	m_CustomerID;
	long	m_SpotID;
	CString	m_Path;
	CString	m_CustomerName;
	CString	m_Name;
	CString	m_FileName;
	long	m_Start;
	long	m_Mix;
	long	m_Finish;
	long	m_MainVoiceID;
	long	m_TypeOfBusinessID;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSpotOnAirData)
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

#endif // !defined(AFX_RSVIEWSPOTONAIRDATA_H__49030E85_3540_4491_A450_F12AF8E0EFFD__INCLUDED_)
