// RSNationalities.h : Implementation of the CRSNationalities class



// CRSNationalities implementation

// code generated on sexta-feira, 31 de Agosto de 2007, 17:16

#include "stdafx.h"
#include "RSNationalities.h"
IMPLEMENT_DYNAMIC(CRSNationalities, CRecordset)

CRSNationalities::CRSNationalities(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Nationality = "";
	m_ZoneID = 0;
	m_Activ = 0;
	m_Code = "";
	m_EU = 0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
CString CRSNationalities::GetDefaultConnect()
{
	return _T("DSN=Broadcaster;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2005;WSID=PEDRO-PC;DATABASE=Broadcaster");
}

CString CRSNationalities::GetDefaultSQL()
{
	return _T("[dbo].[Nationalities]");
}

void CRSNationalities::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Nationality]"), m_Nationality);
	RFX_Long(pFX, _T("[ZoneID]"), m_ZoneID);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[Code]"), m_Code);
	RFX_Long(pFX, _T("[EU]"), m_EU);

}
/////////////////////////////////////////////////////////////////////////////
// CRSNationalities diagnostics

#ifdef _DEBUG
void CRSNationalities::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSNationalities::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


