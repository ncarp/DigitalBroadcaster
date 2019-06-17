#if !defined(AFX_RSTRAFFIC_H__988DFD9B_CE24_4787_807D_216153F411A0__INCLUDED_)
#define AFX_RSTRAFFIC_H__988DFD9B_CE24_4787_807D_216153F411A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSTraffic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSTraffic recordset

class CRSTraffic : public CRecordset
{
public:
	CRSTraffic(CString str);
	DECLARE_DYNAMIC(CRSTraffic)

// Field/Param Data
	//{{AFX_FIELD(CRSTraffic, CRecordset)
	long	m_ID;
	long	m_BlockID;
	COleDateTime	m_BlockDate;
	long	m_ScheduleID;
	float	m_Value;
	long	m_Aired;
	COleDateTime	m_AiringDate;
	long	m_TalentID;
	long	m_Suspend;
	long	m_Position;
	long	m_SpotID;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTraffic)
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

#endif // !defined(AFX_RSTRAFFIC_H__988DFD9B_CE24_4787_807D_216153F411A0__INCLUDED_)
