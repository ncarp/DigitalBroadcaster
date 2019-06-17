// LogOn.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "LogOn.h"
#include "LogOnBack.h"
#include "ExternalObjects.h"
#include "..\include\RSOnAirUsers.h"
#include "..\common\include\rssystemusers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogOn

extern CLogOnBack *g_wndLogOnBack;

#define ID_USER		1001
#define ID_PASS		1002
#define ID_OK		1003

IMPLEMENT_DYNCREATE(CLogOn, CFrameWnd)

CLogOn::CLogOn()
{
}

CLogOn::~CLogOn()
{
}


BEGIN_MESSAGE_MAP(CLogOn, CFrameWnd)
	//{{AFX_MSG_MAP(CLogOn)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_COMMAND( ID_OK, OnOK )
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE( ID_USER,OnUserSelChange )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogOn message handlers

int CLogOn::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
	
	CString str;
	str.LoadString(IDS_LOGON);

	CStatic *s;
	s=new CStatic();
	s->Create("User:",WS_VISIBLE|SS_RIGHT,CRect(10,30,80,54),this);

	s=new CStatic();
	s->Create("Password:",WS_VISIBLE|SS_RIGHT,CRect(10,60,80,84),this);

	m_pOK = new CButton();
	m_pOK->Create(str,WS_VISIBLE,CRect(rect.CenterPoint().x-75,rect.bottom-40,rect.CenterPoint().x+75,rect.bottom-10),this,ID_OK);

	CRect crect=CRect(90,30,rect.right-10,154);
	m_pUser = new CComboBox();
	m_pUser->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,crect,this,ID_USER);

	crect.OffsetRect(0,30);
	crect.DeflateRect(0,0,0,100);
	m_pPass = new CEdit();
	m_pPass->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_PASSWORD|WS_TABSTOP|WS_GROUP|WS_CHILD|WS_VISIBLE,crect,this,ID_PASS);

	str.LoadString(IDS_REFRESH);

	m_pUser->AddString("* "+str);
	m_pUser->SetItemData(0,0);

	return 0;
}

void CLogOn::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CFrameWnd::OnSysCommand(nID,lParam);
}

void CLogOn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect( &rect);
	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CLogOn::OnOK()
{
	int Pos=m_pUser->GetCurSel();
	if( Pos==CB_ERR )
		return;

	long UserID = m_pUser->GetItemData(Pos);

	CString strPass;

	m_pPass->GetWindowText(strPass);
	strPass.TrimRight();
	strPass.Replace("'","''");

	CRSOnAirUsers rs( g_strMainConnect );
	rs.m_strFilter.Format("ID = %d AND Password = '%s'",UserID,strPass);
	rs.Open();

	if( rs.GetRecordCount()==0 )
		return;

	m_pPass->SetWindowText("");
	m_pUser->SetCurSel(-1);

	g_bUserCanEditMusic = (rs.m_MusicEditing==1);
	g_bUserCanSchedule = (rs.m_Scheduler==1);
	g_bUserCanDelayBlocks = (rs.m_Blocks==1);
	g_bUserCanRecord = (rs.m_SoundRecorder==1 );
	g_lUserID = rs.m_ID;
	g_strUserName = rs.m_Name; g_strUserName.TrimRight();

	SetWindowPos(&wndBottom,-500,0,0,0,SWP_NOSIZE);
	g_wndLogOnBack->SetWindowPos(&wndBottom,0,0,0,0,0);
	g_wAutomationMode = AUTOMATION_LIVEASSIST;
	g_wndStatus->Invalidate();

	// Log Item -----------------------------------------------------------------------
	typeLogItem *lpLog=new typeLogItem;
	lpLog->wType = 0;
	lpLog->lID = 0;
	lpLog->lTraffic = 0;
	wsprintf(lpLog->strName,"--> User Log On - %s",g_strUserName);
	g_wndAired->LogItem(lpLog);
	// --------------------------------------------------------------------------------

	CString			strTemp;
	CRSSystemUsers	rsUser(g_strMainConnect );

	strTemp.Format("OnAir - %s",g_strUserName);
	strTemp.Replace("'","''");

	rsUser.m_strFilter.Format("Name = '%s'",strTemp);
	rsUser.Open();

	if( rsUser.GetRecordCount()==0 )
	{
		CString strSQL;

		strSQL.Format("INSERT INTO SystemUsers (Name) VALUES ('%s')",strTemp);
		rsUser.m_pDatabase->ExecuteSQL(strSQL);
		rsUser.Requery();
	}
	
	g_Permissions.lID = rsUser.m_Id;
	g_Permissions.strName.Format("OnAir - %s",g_strUserName);
}

void CLogOn::OnClose() 
{
}

void CLogOn::OnUserSelChange()
{
	long Pos=m_pUser->GetCurSel();
	if( Pos==CB_ERR )
		return;

	long Data=m_pUser->GetItemData(Pos);
	if( Data!=0 )
		return;

	m_pUser->ResetContent();

	CRSOnAirUsers rs( g_strMainConnect );
	rs.m_strSort="Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		Pos=m_pUser->AddString(rs.m_Name);
		m_pUser->SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	rs.Close();

	CString str;
	str.LoadString(IDS_REFRESH);

	Pos=m_pUser->AddString("* "+str);
	m_pUser->SetItemData(Pos,0);
}