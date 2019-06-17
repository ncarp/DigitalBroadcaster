// Spot.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "Spot.h"
#include "TrafficExternals.h"
#include "..\include\RSPath.h"
#include "..\include\RSViewSpotFiles.h"
#include "..\include\RSCustomer.h"
#include "..\include\RSBusiness.h" 
#include "..\include\RSAgency.h"
#include "..\include\RSVoices.h"
#include "..\common\include\utils.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpot dialog


CSpot::CSpot(CWnd* pParent /*=NULL*/)
	: CDialog(CSpot::IDD, pParent)
	, m_nStandardLength(0)
{
	//{{AFX_DATA_INIT(CSpot)
	m_Name = _T("");
	m_OBS = _T("");
	m_Agency = _T("");
	m_Business = _T("");
	m_Customer = _T("");
	m_Voice = _T("");
	//}}AFX_DATA_INIT
	m_PathID=0;
	m_CustomerID=0;
	m_AgencyID=0;
	m_BusinessID=0;
	m_VoiceID=0;
	m_FileName="";
	m_IsNew=TRUE;
}


void CSpot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpot)
	DDX_Control(pDX, IDC_VOICE, m_cVoice);
	DDX_Control(pDX, IDC_CUSTOMER, m_cCustomer);
	DDX_Control(pDX, IDC_BUSINESS, m_cBusiness);
	DDX_Control(pDX, IDC_AGENCY, m_cAgency);
	DDX_Control(pDX, IDC_FILENAME, m_cFile);
	DDX_Control(pDX, IDC_PATH, m_cPath);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_OBS, m_OBS);
	DDX_CBString(pDX, IDC_AGENCY, m_Agency);
	DDX_CBString(pDX, IDC_BUSINESS, m_Business);
	DDX_CBString(pDX, IDC_CUSTOMER, m_Customer);
	DDX_CBString(pDX, IDC_VOICE, m_Voice);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_STANDARDLENGTH, m_nStandardLength);
}


BEGIN_MESSAGE_MAP(CSpot, CDialog)
	//{{AFX_MSG_MAP(CSpot)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_CUSTOMER, OnSelchangeCustomer)
	ON_CBN_KILLFOCUS(IDC_CUSTOMER, OnKillfocusCustomer)
	ON_CBN_SELCHANGE(IDC_BUSINESS, OnSelchangeBusiness)
	ON_CBN_KILLFOCUS(IDC_BUSINESS, OnKillfocusBusiness)
	ON_CBN_KILLFOCUS(IDC_AGENCY, OnKillfocusAgency)
	ON_CBN_SELCHANGE(IDC_AGENCY, OnSelchangeAgency)
	ON_CBN_KILLFOCUS(IDC_VOICE, OnKillfocusVoice)
	ON_CBN_SELCHANGE(IDC_VOICE, OnSelchangeVoice)
	ON_CBN_KILLFOCUS(IDC_PATH, OnKillfocusPath)
	ON_CBN_SELCHANGE(IDC_PATH, OnSelchangePath)
	ON_CBN_KILLFOCUS(IDC_FILENAME, OnKillfocusFilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpot message handlers

BOOL CSpot::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	long	Pos;
	CString str;

	str.LoadString(IDS_REFRESH);

	m_cCustomer.AddString(str);
	m_cCustomer.SetItemData(0,0);

	m_cBusiness.AddString(str);
	m_cBusiness.SetItemData(0,0);

	m_cAgency.AddString(str);
	m_cAgency.SetItemData(0,0);

	m_cVoice.AddString(str);
	m_cVoice.SetItemData(0,0);

	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_FADEIN,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_INTRO,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_FADEOUT,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPA,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPB,MF_BYCOMMAND|MF_GRAYED);
	m_pTimers->m_pLoopCheck->EnableWindow(FALSE);
	m_pTimers->m_pRec->SetImageList(50,50,0,1);
	m_pTimers->m_pRec->AddImage(IDB_RECOFF);

	CRSPath	rs(g_strMainConnect);
	rs.m_strFilter = "Spots = 1";
	rs.m_strSort = "Path";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Path.TrimRight();
		Pos=m_cPath.AddString(rs.m_Path);
		m_cPath.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	rs.Close();

	if( !m_IsNew )
	{
		m_cCustomer.EnableWindow(FALSE);
		
		Pos = m_cPath.FindStringExact(-1,m_Path);
		m_cPath.SetCurSel(Pos);

		FillFileList();
		Pos=m_cFile.AddString(m_FileName);
		m_cFile.SetCurSel(Pos);

		m_pTimers->SetFile(m_Path+"\\"+m_FileName);
		m_pTimers->m_pTimer->m_End=m_End;
		m_pTimers->m_pTimer->m_Mix=m_Mix;
		m_pTimers->m_pTimer->m_Start=m_Start;
		m_pTimers->m_pTimer->m_FadeOut=0;
		m_pTimers->OnUpdateTimers(0,0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CSpot::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect	rect;
	GetClientRect(&rect);

	rect.DeflateRect(10,320,10,50);
	m_pTimers = new CRecorder();
	m_pTimers->Create(NULL,WS_VISIBLE|WS_BORDER,rect,this);

	return 0;
}

void CSpot::OnSelchangeCustomer() 
{
	int Pos=m_cCustomer.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cCustomer.GetItemData(Pos);
	if( lData==0 )
		FillCustomersList();

}

void CSpot::OnKillfocusCustomer() 
{
	CString str;
	m_cCustomer.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
		return;

	CRSCustomer	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cCustomer.SetWindowText(rs.m_Name);
		m_CustomerID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWCUSTOMER,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cCustomer.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_CustomerID=rs.m_ID;

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_CUSTOMER,m_CustomerID);
		}
		else
		{
			m_cCustomer.SetWindowText("");
			m_CustomerID=0;
		}
	}
	rs.Close();
}

void CSpot::OnSelchangeBusiness() 
{
	int Pos=m_cBusiness.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cBusiness.GetItemData(Pos);
	if( lData==0 )
		FillBusinessList();
}

void CSpot::OnKillfocusBusiness() 
{
	CString str;
	m_cBusiness.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
		return;

	CRSBusiness	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cBusiness.SetWindowText(rs.m_Name);
		m_BusinessID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWBUSINESS,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cBusiness.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_BusinessID=rs.m_ID;

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_BUSINESS,m_BusinessID);
		}
		else
		{
			m_cBusiness.SetWindowText("");
			m_BusinessID=0;
		}
	}
	rs.Close();
}

void CSpot::OnKillfocusAgency() 
{
	CString str;
	m_cAgency.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
		return;

	CRSAgency	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cAgency.SetWindowText(rs.m_Name);
		m_AgencyID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWAGENCY,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cAgency.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_AgencyID=rs.m_ID;
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_AGENCY,m_AgencyID);
		}
		else
		{
			m_cAgency.SetWindowText("");
			m_AgencyID=0;
		}
	}
	rs.Close();
}

void CSpot::OnSelchangeAgency() 
{
	int Pos=m_cAgency.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cAgency.GetItemData(Pos);
	if( lData==0 )
		FillAgencyList();
}

void CSpot::OnKillfocusVoice() 
{
	CString str;
	m_cVoice.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
		return;

	CRSVoices	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cVoice.SetWindowText(rs.m_Name);
		m_VoiceID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWVOICE,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cVoice.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_VoiceID=rs.m_ID;

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_VOICE,m_VoiceID);
		}
		else
		{
			m_cVoice.SetWindowText("");
			m_VoiceID=0;
		}
	}
	rs.Close();
}

void CSpot::OnSelchangeVoice() 
{
	int Pos=m_cVoice.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cVoice.GetItemData(Pos);
	if( lData==0 )
		FillVoicesList();
}

void CSpot::OnKillfocusPath() 
{
	int Pos=m_cPath.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lID=m_cPath.GetItemData(Pos);
	if( lID!=m_PathID )
	{
		m_PathID=lID;
		m_cPath.GetLBText(Pos,m_Path);
		FillFileList();
	}
}

void CSpot::OnSelchangePath() 
{
	// TODO: Add your control notification handler code here
	
}

void CSpot::OnKillfocusFilename() 
{
	int Pos=m_cFile.GetCurSel();
	if( Pos==CB_ERR )
		return;

	CString strFullFileName,
			strFileName;
	
	m_cFile.GetLBText(Pos,strFileName);
	if( strFileName!=m_FileName)
	{
		m_FileName=strFileName;
		strFullFileName=m_Path+"\\"+m_FileName;
		m_pTimers->m_pTimer->DeleteBM();
		m_pTimers->SetFile(strFullFileName);	
		m_pTimers->m_pTimer->m_FadeOut=0;
		m_pTimers->m_pTimer->m_Mix=m_pTimers->m_pTimer->m_End-500;
		m_pTimers->m_pTimer->PaintTimerBM();
		m_pTimers->OnUpdateTimers(0,0);
	}
}

void CSpot::FillFileList() 
{
	CFileFind	finder;
	BOOL		bWorking;
	int			Pos;
	CString		strTemp;

	m_cFile.ResetContent();

	bWorking=finder.FindFile(m_Path+"\\*.*");

	while( bWorking )
	{
		bWorking=finder.FindNextFile();

		strTemp = GetFileType(finder.GetFileName());
		strTemp.MakeLower();

		if( (strTemp==".mp3") || (strTemp==".wav") )
			Pos=m_cFile.AddString(finder.GetFileName());
	}

}

void CSpot::FillCustomersList()
{
	CString	str;
	long	Pos;
	CRSCustomer rs(g_strMainConnect);
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	m_cCustomer.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_cCustomer.AddString(rs.m_Name);
		m_cCustomer.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	
	str.LoadString(IDS_REFRESH);
	Pos=m_cCustomer.AddString(str);
	m_cCustomer.SetItemData(Pos,0);
	rs.Close();
}

void CSpot::FillBusinessList()
{
	CString	str;
	long	Pos;
	CRSBusiness rs(g_strMainConnect);
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	m_cBusiness.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_cBusiness.AddString(rs.m_Name);
		m_cBusiness.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	
	str.LoadString(IDS_REFRESH);
	Pos=m_cBusiness.AddString(str);
	m_cBusiness.SetItemData(Pos,0);
	rs.Close();
}

void CSpot::FillAgencyList()
{
	CString	str;
	long	Pos;
	CRSAgency rs(g_strMainConnect);
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	m_cAgency.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_cAgency.AddString(rs.m_Name);
		m_cAgency.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	
	str.LoadString(IDS_REFRESH);
	Pos=m_cAgency.AddString(str);
	m_cAgency.SetItemData(Pos,0);

	rs.Close();
}

void CSpot::FillVoicesList()
{
	CString	str;
	long	Pos;
	CRSVoices rs(g_strMainConnect);
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	m_cVoice.ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_cVoice.AddString(rs.m_Name);
		m_cVoice.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	
	str.LoadString(IDS_REFRESH);
	Pos=m_cVoice.AddString(str);
	m_cVoice.SetItemData(Pos,0);

	rs.Close();
}

void CSpot::OnOK() 
{
	UpdateData();

	if( m_CustomerID==0 )
		return;

	if( m_BusinessID==0 )
		return;

	if( m_Customer.GetLength()==0 )
		return;
	
	CDialog::OnOK();
}
