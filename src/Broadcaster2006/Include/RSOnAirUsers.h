#if !defined(AFX_RSONAIRUSERS_H__D2E8FD2F_305D_4829_ABD5_D55D144AE3BC__INCLUDED_)
#define AFX_RSONAIRUSERS_H__D2E8FD2F_305D_4829_ABD5_D55D144AE3BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSOnAirUsers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSOnAirUsers recordset

class CRSOnAirUsers : public CRecordset
{
public:
	CRSOnAirUsers(CString str);
	DECLARE_DYNAMIC(CRSOnAirUsers)

// Field/Param Data
	//{{AFX_FIELD(CRSOnAirUsers, CRecordset)
	long	m_ID;
	CString	m_Name;
	CString	m_Password;
	CString	m_StationAccess;
	long	m_Activ;
	long	m_Blocks;
	long	m_MusicEditing;
	long	m_Scheduler;
	long	m_SoundRecorder;
	//}}AFX_FIELD

	CString strConnect;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSOnAirUsers)
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

#endif // !defined(AFX_RSONAIRUSERS_H__D2E8FD2F_305D_4829_ABD5_D55D144AE3BC__INCLUDED_)
