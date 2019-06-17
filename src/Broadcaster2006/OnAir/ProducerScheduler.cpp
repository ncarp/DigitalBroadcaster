// ProducerScheduler.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "ProducerScheduler.h"
#include "ExternalObjects.h"
#include "..\include\RSScheduleHeadline.h"
#include "..\include\RSBlocksDefinition.h"
#include "..\include\RSViewSchedule.h"
#include "..\Scheduler\Schedule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_DATE		1001
#define ID_HEADER1	1002

/////////////////////////////////////////////////////////////////////////////
// CProducerScheduler

IMPLEMENT_DYNCREATE(CProducerScheduler, CFrameWnd)

CProducerScheduler::CProducerScheduler()
{
}

CProducerScheduler::~CProducerScheduler()
{
}


BEGIN_MESSAGE_MAP(CProducerScheduler, CFrameWnd)
	//{{AFX_MSG_MAP(CProducerScheduler)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND( CM_REFRESH,OnRefresh )
	ON_COMMAND( CM_EDITLINEUP, OnEditSchedule )
	ON_COMMAND( CM_DISCARD, OnExit )
	ON_COMMAND( CM_LOCK, OnLock )
	ON_COMMAND( CM_REMOVE, OnRemove )
	ON_COMMAND( CM_PFL, OnPFL )
	ON_COMMAND( CM_NEW, OnNew )
	ON_COMMAND( CM_EDIT, OnEdit )
	ON_MESSAGE( UM_DROP, OnDrop )
	ON_MESSAGE( UM_SCHEDULEDBLCLK, OnScheduleDoubleClick )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProducerScheduler message handlers

int CProducerScheduler::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect crect;
	CRect rect;
	CString	strTemp;

	GetClientRect(&crect);

	/////////////////////////////////////////////////////////////////////////
	//	Create the ReBar
	m_pRebar = new CReBar();
	m_pRebar->Create(this,CCS_TOP|CCS_NOPARENTALIGN|CCS_NODIVIDER|RBS_AUTOSIZE,WS_VISIBLE|CBRS_BOTTOM);

	/////////////////////////////////////////////////////////////////////////
	//	Create the Buttons
	TBBUTTON	buttons[9];
	buttons[0].iBitmap=0;
	buttons[0].idCommand=CM_REFRESH;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=0;

	buttons[1].iBitmap=11;
	buttons[1].idCommand=CM_NEW;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=11;

	buttons[2].iBitmap=14;
	buttons[2].idCommand=CM_EDIT;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=17;

	buttons[3].iBitmap=14;
	buttons[3].idCommand=CM_EDITLINEUP;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_BUTTON;
	buttons[3].dwData=0;
	buttons[3].iString=18;

	buttons[4].iBitmap=16;
	buttons[4].idCommand=CM_DISCARD;
	buttons[4].fsState=TBSTATE_ENABLED;
	buttons[4].fsStyle=TBSTYLE_BUTTON;
	buttons[4].dwData=0;
	buttons[4].iString=20;

	buttons[5].iBitmap=15;
	buttons[5].idCommand=CM_LOCK;
	buttons[5].fsState=TBSTATE_ENABLED;
	buttons[5].fsStyle=TBSTYLE_BUTTON;
	buttons[5].dwData=0;
	buttons[5].iString=19;

	buttons[6].iBitmap=10;
	buttons[6].idCommand=CM_REMOVE;
	buttons[6].fsState=TBSTATE_ENABLED;
	buttons[6].fsStyle=TBSTYLE_BUTTON;
	buttons[6].dwData=0;
	buttons[6].iString=2;

	buttons[7].iBitmap=2;
	buttons[7].idCommand=CM_PFL;
	buttons[7].fsState=TBSTATE_ENABLED;
	buttons[7].fsStyle=TBSTYLE_BUTTON;
	buttons[7].dwData=0;
	buttons[7].iString=3;

	/////////////////////////////////////////////////////////////////////////
	//	Create the ToolBar
	m_pToolBar = new CToolBarCtrl();
	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);

	// Set up the tool bar
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(8,buttons);
	m_pToolBar->AutoSize();

	// Add the toolbar to the ReBar
	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);

	// Hide the unused buttons
	m_pToolBar->HideButton(CM_DISCARD);
	m_pToolBar->HideButton(CM_LOCK);
	m_pToolBar->HideButton(CM_REMOVE);
	m_pToolBar->HideButton(CM_PFL);

	///////////////////////////////////////////////////////////////////////
	//	Create the date selector
	rect=crect;
	rect.DeflateRect(35,2,2,0);
	rect.bottom=rect.top+37;
	rect.right=rect.left+150;
	m_pDate=new CDateTimeCtrl();
	m_pDate->Create(WS_VISIBLE|WS_CHILD|DTS_SHORTDATECENTURYFORMAT,rect,this,ID_DATE);
	m_pDate->SetFont(g_cfont24);

	////////////////////////////////////////////////////////////////////////
	//	Create the header
	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|HDS_BUTTONS,CRect(crect.left,crect.top+38,crect.right,crect.top+54),this,ID_HEADER1);
	
	HDITEM	hdItem;
	
	strTemp.LoadString(IDS_SCHEDULE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=crect.Width()-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	/////////////////////////////////////////////////////////////////////////
	//	Create the List box
	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,CRect(crect.left,crect.top+55,crect.right,crect.bottom-67),this,200);
	m_pList->m_iX1=50000;
	m_pList->m_iX2=50000;

	m_pSchedule = new CSchedulerListBox();
	m_pSchedule->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,CRect(0,0,0,0),this,201);

	return 0;
}

void CProducerScheduler::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

BOOL CProducerScheduler::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if( wParam == ID_DATE )
	{
		LPNMHDR nm=(LPNMHDR)lParam;
		if( nm->code == DTN_DATETIMECHANGE )
			OnChangeDate();
	}

	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CProducerScheduler::OnChangeDate()
{
	m_pDate->EnableWindow(FALSE);

	CRSScheduleHeadline rs( g_strOnAirConnect );
	COleDateTime		dt,dtf;
	COleDateTimeSpan	ts(1,0,0,0);
	typeArchiveItem		*lpItem;
	CString				str1,str2;

	m_pList->ResetContent();
	m_pDate->GetTime(dt);
	dtf=dt+ts;

	m_Year = dt.GetYear();
	m_Month= dt.GetMonth();
	m_Day = dt.GetDay();

	rs.m_strFilter.Format("Date >= '%d-%d-%d' AND Date < '%d-%d-%d'",
							dt.GetYear(),dt.GetMonth(),dt.GetDay(),
							dtf.GetYear(),dtf.GetMonth(),dtf.GetDay() );
	rs.m_strSort="Date";
//	AfxMessageBox(rs.m_strFilter);
	
	rs.Open();
	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		str1.Format("%2d:%2d:%2d",rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond());
		str2.Format("%2d:%2d:%2d",rs.m_EndingDate.GetHour(),rs.m_EndingDate.GetMinute(),rs.m_EndingDate.GetSecond());
		str1.Replace(" ","0");
		str2.Replace(" ","0");

		lpItem = new typeArchiveItem(TYPE_SCHEDULE,rs.m_ID,str1+"-"+str2+"  "+rs.m_Name,0);

		m_pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}

	rs.Close();
	m_pDate->EnableWindow(TRUE);
}

void CProducerScheduler::OnRefresh()
{
	OnChangeDate();
}

void CProducerScheduler::OnEditSchedule()
{
	if( !g_bUserCanSchedule )
		return;

	int Pos = m_pList->GetCurSel();
	if( Pos==LB_ERR )
		return;

	typeArchiveItem *lpItem = (typeArchiveItem *)m_pList->GetItemData(Pos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_SCHEDULE )
		return;
	
	m_ScheduleID = lpItem->lID;

	m_pToolBar->HideButton(CM_REFRESH);
	m_pToolBar->HideButton(CM_NEW);
	m_pToolBar->HideButton(CM_EDIT);
	m_pToolBar->HideButton(CM_EDITLINEUP);
	

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(0,55,0,67);
	m_pList->MoveWindow(0,0,0,0);
	m_pSchedule->MoveWindow(rect);
	m_pSchedule->EnableWindow(FALSE);
	m_pDate->EnableWindow(FALSE);

	AfxBeginThread( SetSchedule, (LPVOID)this );
}

UINT CProducerScheduler::SetSchedule(LPVOID lp )
{
	CProducerScheduler *pWnd = (CProducerScheduler *)lp;

	//////////////////////////////////////////////////////////////////////
	//  Get the schedule Headline
	CRSScheduleHeadline rsHead( g_strOnAirConnect );
	rsHead.m_strFilter.Format("ID = %d",pWnd->m_ScheduleID);
	rsHead.Open();
	rsHead.m_Name.TrimRight();

//	pDoc->SetTitle(rsHead.m_Date.Format()+" »» "+rsHead.m_Name);
	
	pWnd->m_EndingTime = rsHead.m_EndingDate;
	pWnd->m_StartingTime = rsHead.m_Date;

	rsHead.Close();

	pWnd->GetScheduleBlocks();

	CRSViewSchedule	rs( g_strOnAirConnect );
	rs.m_strFilter.Format("ScheduleID = %d",pWnd->m_ScheduleID);
	rs.m_strSort = "ItemOrder";
	rs.Open();

	typeLineUpItem *lpItem;

	pWnd->m_pSchedule->ResetContent();

	while( !rs.IsEOF() )
	{
		lpItem = new typeLineUpItem((WORD)rs.m_ItemType,rs.m_ItemID);
		if( lpItem->m_bItemIsValid )
		{
			lpItem->m_bLocked = rs.m_Priority;
			pWnd->m_pSchedule->AddString((LPCTSTR)lpItem);
		}
		else
			delete lpItem;
		rs.MoveNext();
	}

	rs.Close();

	pWnd->InsertBlocks();

	pWnd->m_pToolBar->HideButton(CM_REMOVE,FALSE);
	pWnd->m_pToolBar->HideButton(CM_PFL,FALSE);
	pWnd->m_pToolBar->HideButton(CM_LOCK,FALSE);
	pWnd->m_pToolBar->HideButton(CM_DISCARD,FALSE);

	pWnd->m_pSchedule->EnableWindow();

	return 0;
}

void CProducerScheduler::GetScheduleBlocks()
{
	long	StartTime = m_StartingTime.GetHour()*3600000+m_StartingTime.GetMinute()*60000+m_StartingTime.GetSecond()*1000,
			EndTime = m_EndingTime.GetHour()*3600000+m_EndingTime.GetMinute()*60000+m_EndingTime.GetSecond()*1000;
			
	CString days[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	SYSTEMTIME	st;
	DWORD64		qwTime;

	typeLineUpItem *lpItem;

	CRSBlocksDefinition	rs( g_strOnAirConnect );
	rs.m_strSort = "Time";

	if( m_StartingTime.GetDay()==m_EndingTime.GetDay() )
		rs.m_strFilter.Format("Time >= %d AND Time < %d AND %s = 1 AND Sponsor = 0",StartTime,EndTime,days[m_StartingTime.GetDayOfWeek()-1]);
	else
		rs.m_strFilter.Format("Time >= %d AND %s = 1 AND Sponsor = 0",StartTime,days[m_StartingTime.GetDayOfWeek()-1]);

	rs.Open();
	m_StartingTime.GetAsSystemTime(st);

	SystemTimeToFileTime(&st,(FILETIME *)&qwTime);
	m_nBlocks=0;

	while( !rs.IsEOF() )
	{
		
		lpItem = new typeLineUpItem(TYPE_BLOCK,rs.m_ID,qwTime+(DWORD64)(rs.m_Time-StartTime)*10000,g_strOnAirConnect);
		if( lpItem->m_bItemIsValid )
		{
			lpItem->m_qwOriginalStart = lpItem->m_qwStartTime;
			m_Blocks[m_nBlocks]=lpItem;
			m_nBlocks++;
		}
		rs.MoveNext();
	}

	if( m_StartingTime.GetDay()!=m_EndingTime.GetDay() )
	{
		rs.m_strFilter.Format("Time < %d AND %s = 1 AND Sponsor = 0",EndTime,days[m_EndingTime.GetDayOfWeek()-1]);
		rs.Requery();
		
		m_EndingTime.GetAsSystemTime(st);
		SystemTimeToFileTime(&st,(FILETIME *)&qwTime);

		while( !rs.IsEOF() )
		{
		
			lpItem = new typeLineUpItem(TYPE_BLOCK,rs.m_ID,qwTime+rs.m_Time*10000,g_strOnAirConnect);
			if( lpItem->m_bItemIsValid )
			{
				m_Blocks[m_nBlocks]=lpItem;
				m_nBlocks++;
			}
			rs.MoveNext();
		}
	}
}

void CProducerScheduler::InsertBlocks()
{
	SYSTEMTIME		st;
	DWORD64			qwTime;
	CString			str;

	m_StartingTime.GetAsSystemTime(st);
	SystemTimeToFileTime(&st,(FILETIME *)&qwTime);

	int	nBlock=0,
		nItems = m_pSchedule->GetCount(),
		nPos;
	typeLineUpItem *lpItem;

	for( nPos=0; nPos<nItems; nPos++ )
	{
		lpItem = (typeLineUpItem *)m_pSchedule->GetItemData(nPos);
		
		if( (nBlock < m_nBlocks) && (!lpItem->m_bLocked)  )
		{
			if( m_Blocks[nBlock]->m_qwOriginalStart <= qwTime )
			{
				m_Blocks[nBlock]->m_qwStartTime = qwTime;
				qwTime += (DWORD64)m_Blocks[nBlock]->m_lEndPos*10000;
				
				m_pSchedule->InsertString(nPos,(LPCTSTR)m_Blocks[nBlock]);
				nBlock++;
				nItems++;

				continue;
			}
		}
		lpItem->m_qwStartTime = qwTime;

		qwTime+=(DWORD64)lpItem->m_lMixPos*10000;
	}
	m_pSchedule->Invalidate();
}

void CProducerScheduler::RemoveBlocks()
{
	int					nItems = m_pSchedule->GetCount();
	typeLineUpItem		*lpItem;

	for( int Pos=0; Pos<nItems; Pos++ )
	{
		lpItem = (typeLineUpItem*)m_pSchedule->GetItemData(Pos);
		if( lpItem->m_wType == TYPE_BLOCK )
		{
			m_pSchedule->DeleteString(Pos);
			Pos--;
			nItems--;
		}
	}
}

void CProducerScheduler::SaveLineUp()
{
	int			nItems = m_pSchedule->GetCount(),
				nOrder = 0,
				iPriority;
	CDatabase	db;
	CString		strSQL,
				strDate;
	SYSTEMTIME	st;
	typeLineUpItem *lpItem;

	strSQL.Format("DELETE FROM Scheduling WHERE ScheduleID = %d",m_ScheduleID);
	db.Open( g_strOnAirConnect );
	db.ExecuteSQL( strSQL );

	for( int Pos=0; Pos<nItems; Pos ++ )
	{
		lpItem = (typeLineUpItem *)m_pSchedule->GetItemData(Pos);
		if( lpItem->m_wType != TYPE_BLOCK )
		{
			if( lpItem->m_bLocked )
				iPriority=1;
			else
				iPriority=0;

			FileTimeToSystemTime((FILETIME *)&lpItem->m_qwStartTime,&st);
			strDate.Format("%d-%d-%d %d:%d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

			strSQL.Format("INSERT INTO Scheduling (Date,ItemOrder,ItemType,ItemID,ItemParentID,ScheduleID,Priority,TemplateID) VALUES ('%s',%d,%d,%d,%d,%d,%d,%d)",
				strDate,nOrder,lpItem->m_wType,lpItem->m_lItemID,lpItem->m_lArtistID,m_ScheduleID,iPriority,0);
			db.ExecuteSQL(strSQL);

			nOrder++;
		}
	}
	db.Close();
}

void CProducerScheduler::OnExit() 
{
	m_pToolBar->HideButton(CM_DISCARD);
	m_pToolBar->HideButton(CM_REMOVE);
	m_pToolBar->HideButton(CM_PFL);
	m_pToolBar->HideButton(CM_LOCK);
	m_pToolBar->HideButton(CM_REFRESH,FALSE);
	m_pToolBar->HideButton(CM_EDIT,FALSE);
	m_pToolBar->HideButton(CM_EDITLINEUP,FALSE);
	m_pToolBar->HideButton(CM_NEW,FALSE);

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(0,55,0,67);
	m_pSchedule->MoveWindow(0,0,0,0);
	m_pList->MoveWindow(&rect);
	m_pDate->EnableWindow();
}

void CProducerScheduler::OnLock()
{
	int Pos = m_pSchedule->GetCurSel();

	if( Pos==LB_ERR )
		return;

	typeLineUpItem *lpItem = (typeLineUpItem *)m_pSchedule->GetItemData(Pos);
	if( lpItem == NULL )
		return;

	if( lpItem->m_wType==TYPE_BLOCK )
		return;

	lpItem->m_bLocked= !lpItem->m_bLocked;

	RemoveBlocks();
	InsertBlocks();
	SaveLineUp();
}

void CProducerScheduler::OnRemove()
{
	int Pos = m_pSchedule->GetCurSel();

	if( Pos==LB_ERR )
		return;

	typeLineUpItem *lpItem = (typeLineUpItem *)m_pSchedule->GetItemData(Pos);
	if( lpItem == NULL )
		return;

	if( lpItem->m_wType==TYPE_BLOCK )
		return;

	m_pSchedule->DeleteString(Pos);

	RemoveBlocks();
	InsertBlocks();
	SaveLineUp();
}

void CProducerScheduler::OnPFL()
{
	int Pos = m_pSchedule->GetCurSel();

	if( Pos==LB_ERR )
		return;

	typeLineUpItem *lpItem = (typeLineUpItem *)m_pSchedule->GetItemData(Pos);
	if( lpItem == NULL )
		return;

	if( lpItem->m_wType==TYPE_BLOCK )
		return;

	g_wndPFL->SetSound(lpItem);
	g_wndPFL->RestoreWindow();
}


LRESULT CProducerScheduler::OnDrop(WPARAM,LPARAM)
{
	RemoveBlocks();
	InsertBlocks();
	SaveLineUp();
	return 0;
}

LRESULT CProducerScheduler::OnScheduleDoubleClick(WPARAM,LPARAM)
{
	OnEditSchedule();
	return 0;
}

void CProducerScheduler::OnNew() 
{
	if( !g_bUserCanSchedule )
		return;

	Schedule dl;
	dl.m_Year = m_Year;
	dl.m_Month = m_Month;
	dl.m_Day = m_Day;

	if( dl.DoModal()==IDOK )
	{
		CRSScheduleHeadline rs( g_strOnAirConnect );
		rs.m_strFilter="ID = 0";
		rs.Open();

		rs.AddNew();
		rs.m_Date.SetDateTime(m_Year,m_Month,m_Day,dl.m_StartingTime.GetHour(),m_StartingTime.GetMinute(),m_StartingTime.GetSecond());
		rs.m_EndingDate = rs.m_Date + COleDateTimeSpan(0,dl.m_Length.GetHour(),dl.m_Length.GetMinute(),dl.m_Length.GetSecond());
		rs.m_Name = dl.m_Name;
		rs.m_Priority = dl.m_Precision;
		rs.m_TemplateID=0;
		rs.Update();
		rs.Close();

		OnRefresh();
	}
}

void CProducerScheduler::OnEdit()
{
	if( !g_bUserCanSchedule )
		return;

	int Pos = m_pList->GetCurSel();
	if( Pos == LB_ERR )
		return;

	typeArchiveItem *lpItem = (typeArchiveItem *)m_pList->GetItemData(Pos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType != TYPE_SCHEDULE )
		return;

	CRSScheduleHeadline rs( g_strOnAirConnect );
	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();
	
	if( rs.GetRecordCount()==0 )
		return ;

	Schedule dl;

	dl.m_Name = rs.m_Name; dl.m_Name.TrimRight();
	dl.m_StartingTime = rs.m_Date;
	dl.m_EndingDate = rs.m_EndingDate;
	dl.m_Length = rs.m_EndingDate-rs.m_Date;
	dl.m_Precision = rs.m_Priority;
	dl.m_Year = m_Year;
	dl.m_Month = m_Month;
	dl.m_Day = m_Day;

	if( dl.DoModal()==IDOK )
	{
		rs.Edit();
		rs.m_Date.SetDateTime(m_Year,m_Month,m_Day,dl.m_StartingTime.GetHour(),m_StartingTime.GetMinute(),m_StartingTime.GetSecond());
		rs.m_EndingDate = rs.m_Date + COleDateTimeSpan(0,dl.m_Length.GetHour(),dl.m_Length.GetMinute(),dl.m_Length.GetSecond());
		rs.m_Name = dl.m_Name;
		rs.m_Priority = dl.m_Precision;
		rs.m_TemplateID=0;
		rs.Update();
		rs.Close();

		OnRefresh();
	}
}
