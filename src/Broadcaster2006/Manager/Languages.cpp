// Languages.h : Implementation of the CLanguages class



// CLanguages implementation

// code generated on sábado, 1 de Setembro de 2007, 01:40

#include "stdafx.h"
#include "Languages.h"
IMPLEMENT_DYNAMIC(CLanguages, CRecordset)

CLanguages::CLanguages(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Name = "";
	m_Activ = 0;
	m_DRM35 = "";
	m_Code = "";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
CString CLanguages::GetDefaultConnect()
{
	return _T("DSN=Broadcaster;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2005;WSID=PEDRO-PC;DATABASE=Broadcaster");
}

CString CLanguages::GetDefaultSQL()
{
	return _T("[dbo].[Languages]");
}

void CLanguages::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	RFX_Text(pFX, _T("[Code]"), m_Code);

}
/////////////////////////////////////////////////////////////////////////////
// CLanguages diagnostics

#ifdef _DEBUG
void CLanguages::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLanguages::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


