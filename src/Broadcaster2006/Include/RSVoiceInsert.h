#if !defined(AFX_RSVOICEINSERT_H__00EEBD29_5B77_4B48_B985_FC43C2BB2197__INCLUDED_)
#define AFX_RSVOICEINSERT_H__00EEBD29_5B77_4B48_B985_FC43C2BB2197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSVoiceInsert.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSVoiceInsert recordset

class CRSVoiceInsert : public CRecordset
{
public:
	CRSVoiceInsert(CString str);
	DECLARE_DYNAMIC(CRSVoiceInsert)

// Field/Param Data
	//{{AFX_FIELD(CRSVoiceInsert, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_FileName;
	long	m_Path;
	long	m_Start;
	long	m_Finish;
	long	m_TalentID;
	long	m_Activ;
	//}}AFX_FIELD

	CString m_strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSVoiceInsert)
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

#endif // !defined(AFX_RSVOICEINSERT_H__00EEBD29_5B77_4B48_B985_FC43C2BB2197__INCLUDED_)
