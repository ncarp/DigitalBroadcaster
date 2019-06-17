// RSSpots.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSSpots.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSSpots

IMPLEMENT_DYNAMIC(CRSSpots, CRecordset)

CRSSpots::CRSSpots(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSSpots)
	m_ID = 0;
	m_Name = _T("");
	m_CustomerID = 0;
	m_AgencyID = 0;
	m_TypeOfBusinessID = 0;
	m_PathID = 0;
	m_FileName = _T("");
	m_Start = 0;
	m_Mix = 0;
	m_Finish = 0;
	m_Ready = 0;
	m_Text = _T("");
	m_Voices = _T("");
	m_Music = _T("");
	m_MainVoiceID = 0;
	m_DRM35 = _T("");
	m_Obs = _T("");
	m_Activ = 0;
	m_StLength = 0;
	m_nFields = 20;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSSpots::GetDefaultConnect()
{
	return strConnect;
}

CString CRSSpots::GetDefaultSQL()
{
	return _T("[dbo].[Spots]");
}

void CRSSpots::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSSpots)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Long(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Long(pFX, _T("[AgencyID]"), m_AgencyID);
	RFX_Long(pFX, _T("[TypeOfBusinessID]"), m_TypeOfBusinessID);
	RFX_Long(pFX, _T("[PathID]"), m_PathID);
	RFX_Text(pFX, _T("[FileName]"), m_FileName);
	RFX_Long(pFX, _T("[Start]"), m_Start);
	RFX_Long(pFX, _T("[Mix]"), m_Mix);
	RFX_Long(pFX, _T("[Finish]"), m_Finish);
	RFX_Long(pFX, _T("[Ready]"), m_Ready);
	RFX_Text(pFX, _T("[Text]"), m_Text);
	RFX_Text(pFX, _T("[Voices]"), m_Voices);
	RFX_Text(pFX, _T("[Music]"), m_Music);
	RFX_Date(pFX, _T("[Deadline]"), m_Deadline);
	RFX_Long(pFX, _T("[MainVoiceID]"), m_MainVoiceID);
	RFX_Text(pFX, _T("[DRM35]"), m_DRM35);
	RFX_Text(pFX, _T("[Obs]"), m_Obs);
	RFX_Long(pFX, _T("[Activ]"), m_Activ); 
	RFX_Long(pFX, _T("[StandardLength]"), m_StLength);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSSpots diagnostics

#ifdef _DEBUG
void CRSSpots::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSSpots::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
