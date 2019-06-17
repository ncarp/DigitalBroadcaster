#if !defined(AFX_RSSCHEDULETEMPLATE_H__9D1DAF57_692F_4AD8_858C_0093B84A62D2__INCLUDED_)
#define AFX_RSSCHEDULETEMPLATE_H__9D1DAF57_692F_4AD8_858C_0093B84A62D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSScheduleTemplate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSScheduleTemplate recordset

class CRSScheduleTemplate : public CRecordset
{
public:
	CRSScheduleTemplate(CString str);
	DECLARE_DYNAMIC(CRSScheduleTemplate)

// Field/Param Data
	//{{AFX_FIELD(CRSScheduleTemplate, CRecordset)
	long	m_ID;
	long	m_Type;
	CString	m_Name;
	CString	m_strSQL;
	long	m_Category;
	long	m_Expression;
	long	m_MaxLen;
	long	m_MaxRythm;
	long	m_MinLen;
	long	m_MinRythm;
	long	m_PlayList;
	long	m_ArtistQuarantine;
	long	m_RandomFactor;
	long	m_SongQuarantine;
	//}}AFX_FIELD

	CString strConnect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSScheduleTemplate)
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

#endif // !defined(AFX_RSSCHEDULETEMPLATE_H__9D1DAF57_692F_4AD8_858C_0093B84A62D2__INCLUDED_)
