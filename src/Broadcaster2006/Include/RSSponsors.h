#if !defined(AFX_RSSPONSORS_H__B042F3B6_9C9F_460D_80B2_C375B3DB7C37__INCLUDED_)
#define AFX_RSSPONSORS_H__B042F3B6_9C9F_460D_80B2_C375B3DB7C37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSSponsors.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSSponsors recordset

class CRSSponsors : public CRecordset
{
public:
	CRSSponsors(CString str);
	DECLARE_DYNAMIC(CRSSponsors)

// Field/Param Data
	//{{AFX_FIELD(CRSSponsors, CRecordset)
	long	m_SpotID;
	COleDateTime	m_StartingDate;
	COleDateTime	m_EndingDate;
	long	m_ID;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSSponsors)
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

#endif // !defined(AFX_RSSPONSORS_H__B042F3B6_9C9F_460D_80B2_C375B3DB7C37__INCLUDED_)
