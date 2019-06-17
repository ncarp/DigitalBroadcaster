// RSViewSpotsFull.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RSViewSpotsFull.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotsFull

IMPLEMENT_DYNAMIC(CRSViewSpotsFull, CRecordset)

CRSViewSpotsFull::CRSViewSpotsFull(CString str)
	: CRecordset(NULL)
{
	//{{AFX_FIELD_INIT(CRSViewSpotsFull)
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
	m_CustomerName = _T("");
	m_AgencyName = _T("");
	m_BusinessName = _T("");
	m_Path = _T("");
	m_VoiceName = _T("");
	m_StandardLength = 0;
	m_nFields = 25;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	strConnect.Format("ODBC;DSN=%s",str);
}


CString CRSViewSpotsFull::GetDefaultConnect()
{
	return strConnect;
}

CString CRSViewSpotsFull::GetDefaultSQL()
{
	return _T("[dbo].[ViewSpotFull]");
}

void CRSViewSpotsFull::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSViewSpotsFull)
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
	RFX_Text(pFX, _T("[CustomerName]"), m_CustomerName);
	RFX_Text(pFX, _T("[AgencyName]"), m_AgencyName);
	RFX_Text(pFX, _T("[BusinessName]"), m_BusinessName);
	RFX_Text(pFX, _T("[Path]"), m_Path);
	RFX_Text(pFX, _T("[VoiceName]"), m_VoiceName);
	RFX_Long(pFX, _T("[StandardLength]"), m_StandardLength);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSViewSpotsFull diagnostics

#ifdef _DEBUG
void CRSViewSpotsFull::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSViewSpotsFull::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
