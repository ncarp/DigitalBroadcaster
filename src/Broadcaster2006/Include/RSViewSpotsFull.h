#if !defined(AFX_RSVIEWSPOTSFULL_H__5696C32B_6FC1_4DCF_8A1B_FB03ED751154__INCLUDED_)
#define AFX_RSVIEWSPOTSFULL_H__5696C32B_6FC1_4DCF_8A1B_FB03ED751154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSViewSpotsFull.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotsFull recordset

class CRSViewSpotsFull : public CRecordset
{
public:
	CRSViewSpotsFull(CString str);
	DECLARE_DYNAMIC(CRSViewSpotsFull)

// Field/Param Data
	//{{AFX_FIELD(CRSViewSpotsFull, CRecordset)
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
	CString	m_CustomerName;
	CString	m_AgencyName;
	CString	m_BusinessName;
	CString	m_Path;
	CString	m_VoiceName;
	long	m_StandardLength;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSViewSpotsFull)
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

#endif // !defined(AFX_RSVIEWSPOTSFULL_H__5696C32B_6FC1_4DCF_8A1B_FB03ED751154__INCLUDED_)
