// SoundRecorderSelector.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "SoundRecorderSelector.h"
#include "OnAirUtils.h"
#include "ExternalObjects.h"
#include "..\include\RSViewRecordings.h"
#include "..\include\RSPath.h"
#include "..\include\RSRecordingVersion.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundRecorderSelector

IMPLEMENT_DYNCREATE(CSoundRecorderSelector, CFrameWnd)

CSoundRecorderSelector::CSoundRecorderSelector()
{
}

CSoundRecorderSelector::~CSoundRecorderSelector()
{
}


BEGIN_MESSAGE_MAP(CSoundRecorderSelector, CFrameWnd)
	//{{AFX_MSG_MAP(CSoundRecorderSelector)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	ON_COMMAND( CM_REFRESH, OnRefresh )
	ON_COMMAND( CM_NEWSOUND, OnNewVersion )
	ON_COMMAND( CM_SAVE, OnSave )
	ON_COMMAND( CM_DISCARD, OnDiscard )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundRecorderSelector message handlers

int CSoundRecorderSelector::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	buttons[1].iBitmap=6;
	buttons[1].idCommand=CM_NEWSOUND;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=6;

	buttons[2].iBitmap=9;
	buttons[2].idCommand=CM_SAVE;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=9;

	buttons[3].iBitmap=10;
	buttons[3].idCommand=CM_DISCARD;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_BUTTON;
	buttons[3].dwData=0;
	buttons[3].iString=10;

	m_pToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
//	m_pToolBar->SetButtonSize(size);
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(4,buttons);
	m_pToolBar->AutoSize();

	m_pToolBar->HideButton(CM_SAVE);
	m_pToolBar->HideButton(CM_DISCARD);

	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);
	
	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,crect,this,200);
	m_pList->m_iX1=rectHeader.right-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->m_iX2=50000;
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
	strTemp.LoadString(IDS_DEADLINE);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(1,&hdItem);

	// Create the recording window
	crect.top-=17;
	m_pWndRecord = new CSoundRecorderWnd();
	m_pWndRecord->Create(NULL,WS_VISIBLE|SS_NOTIFY,crect,this);
	
	m_pWndRecord->MoveWindow(0,0,0,0);

	return 0;
}

void CSoundRecorderSelector::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CSoundRecorderSelector::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CSoundRecorderSelector::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// Do nothing
}

void CSoundRecorderSelector::OnRefresh()
{
	if( !m_pList->m_bIsRefreshing )
	{
		AfxBeginThread(ThreadRefresh,(LPVOID)this->m_pList);	
	}
}

void CSoundRecorderSelector::OnNewVersion()
{
	if( !g_bUserCanRecord )
		return;

	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_RECORDINGTASK )
		return;

	CRect rect;
	GetClientRect(&rect);

	rect.DeflateRect(0,0,0,67);
	m_pList->MoveWindow(0,0,0,0);
	m_pWndRecord->MoveWindow(rect);
	m_pWndRecord->ShowTask(lpItem->lID);

	m_pToolBar->HideButton(CM_REFRESH);
	m_pToolBar->HideButton(CM_NEWSOUND);
	m_pToolBar->HideButton(CM_SAVE,FALSE);
	m_pToolBar->HideButton(CM_DISCARD,FALSE);
	m_pToolBar->AutoSize();

	CRSPath rsPath( g_strMainConnect );
	rsPath.m_strFilter="Producer = 1";
	rsPath.Open();

	if( rsPath.GetRecordCount()==0 )
		return;

	m_pWndRecord->m_PathID = rsPath.m_ID;
	m_pWndRecord->m_strPath = rsPath.m_Path; m_pWndRecord->m_strPath.TrimRight();
	rsPath.Close();

	CRSRecordingVersion rs( g_strMainConnect );
	int Cont=1;
	rs.m_strFilter="Name = 'Take 1'";
	rs.Open();

	while( rs.GetRecordCount()!=0 )
	{
		Cont++;
		rs.m_strFilter.Format("Name = 'Take %d'",Cont);
		rs.Requery();
	}

	m_pWndRecord->m_RecordingID=lpItem->lID;
	m_pWndRecord->m_strFileName.Format("%s - %s - Take %d.wav",g_strUserName,lpItem->strName,Cont);
	m_pWndRecord->m_strName.Format("Take %d",Cont);
	m_pWndRecord->m_pRecorder->SetFile(m_pWndRecord->m_strPath+"\\"+m_pWndRecord->m_strFileName);
	rs.Close();

}

UINT CSoundRecorderSelector::ThreadRefresh(LPVOID lp)
{
	CRSViewRecordings	rs(g_strMainConnect);
	COnAirListBox*		pList=(COnAirListBox*)lp;
	CString				strPrevTask="";
	CString				strDeadline;

	typeArchiveItem*	lpItem;

	pList->m_bIsRefreshing=TRUE;
	pList->ResetContent();

	rs.m_strSort="Deadline, Name";
	rs.m_strFilter.Format("Completed = '0' AND TalentID='%d'",g_lUserID);
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( rs.m_Name!=strPrevTask )
		{
			strPrevTask=rs.m_Name;
			rs.m_Name.TrimRight();
			strDeadline.Format("%d-%d-%d %d:%d",rs.m_Deadline.year,
												rs.m_Deadline.month,
												rs.m_Deadline.day,
												rs.m_Deadline.hour,
												rs.m_Deadline.minute );
			lpItem = new typeArchiveItem(TYPE_RECORDINGTASK,rs.m_ID,rs.m_Name,0,strDeadline);
			
			pList->InsertString(-1,(LPCTSTR)lpItem);
		}
		if( !rs.IsFieldNull(&rs.m_VersionID) )
		{
			rs.m_VersionName.TrimRight();

			lpItem = new typeArchiveItem(TYPE_RECORDING,rs.m_VersionID,rs.m_VersionName,0);
			
			pList->InsertString(-1,(LPCTSTR)lpItem);
		}
		rs.MoveNext();
	}
	rs.Close();
	pList->m_bIsRefreshing=FALSE;
	return (0);
}

void CSoundRecorderSelector::OnDiscard()
{
	CRect rect;
	GetClientRect(&rect);

	rect.DeflateRect(0,17,0,67);
	m_pList->MoveWindow(rect);
	m_pWndRecord->MoveWindow(0,0,0,0);
//	m_pWndRecord->ShowTask(lpItem->lID);

	m_pToolBar->HideButton(CM_REFRESH,FALSE);
	m_pToolBar->HideButton(CM_NEWSOUND,FALSE);
	m_pToolBar->HideButton(CM_SAVE,TRUE);
	m_pToolBar->HideButton(CM_DISCARD,TRUE);
	m_pToolBar->AutoSize();

	m_pWndRecord->m_pRecorder->KillFile();
}

void CSoundRecorderSelector::OnSave()
{
	CRSRecordingVersion rs( g_strMainConnect );
	rs.m_strFilter="ID = 0";
	rs.Open();
	rs.AddNew();

	rs.m_Deleted = 0;
	rs.m_FileName = m_pWndRecord->m_strFileName;
	rs.m_Name = m_pWndRecord->m_strName;
	rs.m_PathID = m_pWndRecord->m_PathID;
	rs.m_RecordingID = m_pWndRecord->m_RecordingID;
	rs.Update();

	OnRefresh();

	OnDiscard();
}