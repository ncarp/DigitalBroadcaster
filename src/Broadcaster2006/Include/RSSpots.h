#if !defined(AFX_RSSPOTS_H__34FEF9F5_3A23_4A06_9CAE_AFE472A95F32__INCLUDED_)
#define AFX_RSSPOTS_H__34FEF9F5_3A23_4A06_9CAE_AFE472A95F32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSSpots.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSSpots recordset

class CRSSpots : public CRecordset
{
public:
	CRSSpots(CString str);
	DECLARE_DYNAMIC(CRSSpots)

// Field/Param Data
	//{{AFX_FIELD(CRSSpots, CRecordset)
	long	m_ID;
	CString	m_Name;
	long	m_CustomerID;
	long	m_AgencyID;
	long	m_TypeOfBusinessID;
	long	m_PathID;
	CString	m_FileName;
	long	m_Start;
	long	m_Mix;
	long	m_Finish;
	long	m_Ready;
	CString	m_Text;
	CString	m_Voices;
	CString	m_Music;
	COleDateTime	m_Deadline;
	long	m_MainVoiceID;
	CString	m_DRM35;
	CString	m_Obs;
	long	m_Activ;
	long	m_StLength;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSSpots)
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

#endif // !defined(AFX_RSSPOTS_H__34FEF9F5_3A23_4A06_9CAE_AFE472A95F32__INCLUDED_)
