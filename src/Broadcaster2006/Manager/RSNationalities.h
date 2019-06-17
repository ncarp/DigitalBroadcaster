// RSNationalities.h : Declaration of the CRSNationalities

#pragma once

// code generated on sexta-feira, 31 de Agosto de 2007, 17:16

class CRSNationalities : public CRecordset
{
public:
	CRSNationalities(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSNationalities)


	long	m_ID;
	CStringA	m_Nationality;
	long	m_ZoneID;
	long	m_Activ;
	CStringA	m_Code;
	long	m_EU;

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


