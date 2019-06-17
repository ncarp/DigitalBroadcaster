// VoiceInsertWnd.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "VoiceInsertWnd.h"
#include "OnAirUtils.h"
#include "ExternalObjects.h"
#include "..\include\RSVoiceInsert.h"
#include "..\include\Utils.h"
#include "..\include\RSVoiceInsert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVoiceInsertWnd

IMPLEMENT_DYNCREATE(CVoiceInsertWnd, CFrameWnd)

CVoiceInsertWnd::CVoiceInsertWnd()
{
}

CVoiceInsertWnd::~CVoiceInsertWnd()
{
}


BEGIN_MESSAGE_MAP(CVoiceInsertWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CVoiceInsertWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
	ON_COMMAND( CM_REFRESH,OnRefresh )
	ON_COMMAND( CM_PFL, OnPFL)
	ON_COMMAND( CM_NEWSOUND, OnVoiceInsert)
	ON_COMMAND( CM_SAVE, OnSave )
	ON_COMMAND( CM_DISCARD, OnDiscard )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoiceInsertWnd message handlers

int CVoiceInsertWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
		m_pRebar = new CReBar();
	m_pRebar->Create(this,CCS_TOP|CCS_NOPARENTALIGN|CCS_NODIVIDER|RBS_AUTOSIZE,WS_VISIBLE|CBRS_BOTTOM);

	CRect	crect;
	GetClientRect( &crect );

	////////////////////////////////////////////////////////////////////
	//	Create the header
	CRect	rectHeader=crect;
	rectHeader.bottom=crect.top+16;

	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|HDS_BUTTONS,rectHeader,this,87);

	crect.DeflateRect(0,17,0,67);

	TBBUTTON	buttons[5];
	buttons[0].iBitmap=0;
	buttons[0].idCommand=CM_REFRESH;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=0;

	buttons[1].iBitmap=2;
	buttons[1].idCommand=CM_PFL;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=3;

	buttons[2].iBitmap=6;
	buttons[2].idCommand=CM_NEWSOUND;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=16;

	buttons[3].iBitmap=9;
	buttons[3].idCommand=CM_SAVE;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_BUTTON;
	buttons[3].dwData=0;
	buttons[3].iString=9;

	buttons[4].iBitmap=10;
	buttons[4].idCommand=CM_DISCARD;
	buttons[4].fsState=TBSTATE_ENABLED ;
	buttons[4].fsStyle=TBSTYLE_BUTTON;
	buttons[4].dwData=0;
	buttons[4].iString=10;

	m_pToolBar=new CToolBarCtrl();

	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(5,buttons);
	m_pToolBar->AutoSize();

	m_pToolBar->HideButton(CM_SAVE);
	m_pToolBar->HideButton(CM_DISCARD);
	m_pToolBar->AutoSize();

	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);
	
	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,crect,this,200);
	m_pList->m_iX1=rectHeader.right-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->m_iX2=50000;

	m_pRecorder = new CVoiceInsertRecorder();
	m_pRecorder->Create(NULL,NULL,WS_VISIBLE,crect,this,1);
	m_pRecorder->MoveWindow(0,0,0,0);
	// 
	HDITEM	hdItem;
	CString	strTemp;

	strTemp.LoadString(IDS_TITLE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=rectHeader.Width()-140-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	hdItem.cxy=140;
	strTemp.LoadString(IDS_LENGTH);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(1,&hdItem);

	return 0;
}

void CVoiceInsertWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CVoiceInsertWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CVoiceInsertWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )	
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CVoiceInsertWnd::OnRefresh()
{
	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(RefreshThread,(LPVOID)m_pList);
}

void CVoiceInsertWnd::OnVoiceInsert()
{
	if( !g_bUserCanRecord )
		return;

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(0,17,0,67);

	m_pList->MoveWindow(0,0,0,0);
	m_pRecorder->MoveWindow(rect);
	
	m_pToolBar->HideButton(CM_REFRESH);
	m_pToolBar->HideButton(CM_PFL);
	m_pToolBar->HideButton(CM_NEWSOUND);
	m_pToolBar->HideButton(CM_SAVE,FALSE);
	m_pToolBar->HideButton(CM_DISCARD,FALSE);
	m_pToolBar->AutoSize();

	m_pRecorder->m_pName->SetWindowText("");
	m_pRecorder->m_pFile->SetWindowText("");
	m_pRecorder->m_pUser->SetWindowText(g_strUserName);
	m_pRecorder->m_strFileName="";
	m_pRecorder->m_pRecorder->SetFile("");
}

void CVoiceInsertWnd::OnSave()
{
	CString strFileName,
			strName;
	long	lPathID;

	int	Pos = m_pRecorder->m_pPath->GetCurSel();
	if( Pos==CB_ERR )
		return;

	lPathID = m_pRecorder->m_pPath->GetItemData(Pos);
	if( lPathID==0 )
		return;

	m_pRecorder->m_pFile->GetWindowText(strFileName);
	if( strFileName.GetLength()==0 )
		return;

	m_pRecorder->m_pName->GetWindowText(strName);
	strName.TrimRight();
	if( strName.GetLength()==0 )
		return;

	CRSVoiceInsert rs( g_strOnAirConnect );
	rs.Open();

	rs.AddNew();
	
	rs.m_Activ = 1;
	rs.m_FileName = strFileName;
	rs.m_Finish = m_pRecorder->m_pRecorder->m_pTimer->m_End;
	rs.m_Name = strName;
	rs.m_Path = lPathID;
	rs.m_Start = m_pRecorder->m_pRecorder->m_pTimer->m_Start;
	rs.m_TalentID = g_lUserID;

	rs.Update();
	rs.Close();

	m_pRecorder->m_pRecorder->KillFile();
	OnRefresh();

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(0,17,0,67);

	m_pList->MoveWindow(rect);
	m_pRecorder->MoveWindow(0,0,0,0);
	
	m_pToolBar->HideButton(CM_REFRESH,FALSE);
	m_pToolBar->HideButton(CM_PFL,FALSE);
	m_pToolBar->HideButton(CM_NEWSOUND,FALSE);
	m_pToolBar->HideButton(CM_SAVE);
	m_pToolBar->HideButton(CM_DISCARD);
	m_pToolBar->AutoSize();
}

void CVoiceInsertWnd::OnDiscard()
{
	m_pRecorder->m_pRecorder->KillFile();

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(0,17,0,67);

	m_pList->MoveWindow(rect);
	m_pRecorder->MoveWindow(0,0,0,0);
	
	m_pToolBar->HideButton(CM_REFRESH,FALSE);
	m_pToolBar->HideButton(CM_PFL,FALSE);
	m_pToolBar->HideButton(CM_NEWSOUND,FALSE);
	m_pToolBar->HideButton(CM_SAVE);
	m_pToolBar->HideButton(CM_DISCARD);
	m_pToolBar->AutoSize();
}

UINT CVoiceInsertWnd::RefreshThread(LPVOID lpv)
{
	CRSVoiceInsert		rs(g_strOnAirConnect);
	COnAirListBox*		pList=(COnAirListBox*)lpv;
	CString				strLength;
	typeArchiveItem*	lpItem;

	pList->m_bIsRefreshing=TRUE;
	pList->ResetContent();

	rs.m_strSort="Name";
	rs.m_strFilter.Format("Activ=1 AND TalentID=%d",g_lUserID);
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		GetTimeString(rs.m_Finish-rs.m_Start,&strLength);
		strLength.Delete(0,3);
		strLength.Delete(7,2);

		lpItem = new typeArchiveItem(TYPE_VOICEINSERT,rs.m_ID,rs.m_Name,0,strLength,"");
			
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}
	rs.Close();
	pList->m_bIsRefreshing=FALSE;

	return 0;
}

void CVoiceInsertWnd::OnPFL()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType==TYPE_VOICEINSERT )
	{
		g_wndPFL->SetSound(lpItem);
		g_wndPFL->RestoreWindow();
	}
}
