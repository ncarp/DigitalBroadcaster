// RSViewERC.h : Implementation of the CRSViewERC class



// CRSViewERC implementation

// code generated on segunda-feira, 3 de Setembro de 2007, 12:11

#include "stdafx.h"
#include "RSViewERC.h"
IMPLEMENT_DYNAMIC(CRSViewERC, CRecordset)

CRSViewERC::CRSViewERC(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_AirDate;
	m_Title = "";
	m_Artist = "";
	m_LangCode = "";
	m_NatCode = "";
	m_EU = 0;
	m_Length = 0;
	m_RecordingDate;
	m_Category = "";
	m_nFields = 9;
	m_nDefaultType = snapshot;
}

CString CRSViewERC::GetDefaultConnect()
{
	return _T("DSN=Broadcaster-OnAir;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2005;WSID=PEDRO-PC;DATABASE=OnAir");
}

CString CRSViewERC::GetDefaultSQL()
{
	return _T("[dbo].[ViewERC]");
}

void CRSViewERC::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Date(pFX, _T("[AirDate]"), m_AirDate);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Artist]"), m_Artist);
	RFX_Text(pFX, _T("[LangCode]"), m_LangCode);
	RFX_Text(pFX, _T("[NatCode]"), m_NatCode);
	RFX_Long(pFX, _T("[EU]"), m_EU);
	RFX_Long(pFX, _T("[Length]"), m_Length);
	RFX_Date(pFX, _T("[RecordingDate]"), m_RecordingDate);
	RFX_Text(pFX, _T("[Category]"), m_Category);

}
/////////////////////////////////////////////////////////////////////////////
// CRSViewERC diagnostics

#ifdef _DEBUG
void CRSViewERC::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewERC::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


