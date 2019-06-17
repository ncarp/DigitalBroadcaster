// RSViewRms.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewRms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewRms

IMPLEMENT_DYNAMIC(CRSViewRms, CRecordset)

CRSViewRms::CRSViewRms(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewRms)
	m_ID = 0;
	m_Name = _T("");
	m_TypeID = 0;
	m_KeyWords = _T("");
	m_Obs = _T("");
	m_Activ = 0;
	m_PathID = 0;
	m_FileName = _T("");
	m_Start = 0;
	m_Mix = 0;
	m_Finish = 0;
	m_DRM35 = _T("");
	m_ArchiveID = 0;
	m_Type = _T("");
	m_Path = _T("");
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewRms::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewRms::GetDefaultSQL()
{
	return _T("[dbo].[ViewRMs]");
}

void CRSViewRms::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewRms)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[TypeID]"), m_TypeID);
	RFX_Text(pFX, _T("[KeyWords]"), m_KeyWords);
	RFX_Text(pFX, _T("[Obs]"), m_Obs, 10000);
	RFX_Long(pFX, _T("[Activ]"), m_Activ);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Long(pFX, _T("[PathID]"), m_PathID);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	RFX_Long(pFX, _T("[ArchiveID]"), m_ArchiveID);
	RFX_Text(pFX, _T("[Type]"), m_Type);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewRms diagnostics

#ifdef _DEBUG
void CRSViewRms::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewRms::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
