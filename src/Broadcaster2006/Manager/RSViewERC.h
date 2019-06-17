// RSViewERC.h : Declaration of the CRSViewERC

#pragma once

// code generated on segunda-feira, 3 de Setembro de 2007, 12:11

class CRSViewERC : public CRecordset
{
public:
	CRSViewERC(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSViewERC)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	COleDateTime	m_AirDate;
	CStringA	m_Title;
	CStringA	m_Artist;
	CStringA	m_LangCode;
	CStringA	m_NatCode;
	long	m_EU;
	long	m_Length;
	COleDateTime	m_RecordingDate;
	CStringA	m_Category;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


