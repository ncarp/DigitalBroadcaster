// AiredWnd.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "AiredWnd.h"
#include "OnAirUtils.h"
#include "OnAirDefines.h"
#include "ExternalObjects.h"
#include "logger.h"
#include "..\include\RSOnAirLog.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bHaspOK;
extern BOOL g_bNoLog;
extern CLogger *g_pLogger;

/////////////////////////////////////////////////////////////////////////////
// CAiredWnd

IMPLEMENT_DYNCREATE(CAiredWnd, CFrameWnd)

CAiredWnd::CAiredWnd()
{
}

CAiredWnd::~CAiredWnd()
{
}


BEGIN_MESSAGE_MAP(CAiredWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CAiredWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_COMMAND( CM_REFRESH,OnRefresh )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiredWnd message handlers

int CAiredWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);

	CRect	crect;
	GetClientRect( &crect );

	////////////////////////////////////////////////////////////////////
	//	Create the header
	CRect	rectHeader=crect;
	rectHeader.bottom=crect.top+16;

	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|HDS_BUTTONS,rectHeader,this,87);

	crect.DeflateRect(0,17,0,64);

	TBBUTTON	buttons[5];
	buttons[0].iBitmap=0;
	buttons[0].idCommand=CM_REFRESH;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=0;

	CToolBarCtrl	*wndToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	wndToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	wndToolBar->SetButtonSize(size);
	wndToolBar->SetImageList(g_ilToolEnabled);
	wndToolBar->SetHotImageList(g_ilToolHot);
	wndToolBar->AddStrings(g_lpstrToolLabels);
	wndToolBar->AddButtons(1,buttons);
	wndToolBar->AutoSize();

	m_pRebar->AddBar(wndToolBar,NULL,g_bmToolBackground);

	// Just testing...

	m_pList=new CAiredListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,crect,this,200);
	// 
	HDITEM	hdItem;
	CString	strTemp;
	char	chTemp[50];

	strTemp.LoadString(IDS_TITLE);
	strcpy(chTemp,strTemp);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=chTemp;
	hdItem.cxy=rectHeader.Width()-200;
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	hdItem.cxy=100;
	strTemp.LoadString(IDS_DURATION);
	strcpy(chTemp,strTemp);
	m_pHeader->InsertItem(1,&hdItem);

	strTemp.LoadString(IDS_STARTINGTIME);
	strcpy(chTemp,strTemp);
	m_pHeader->InsertItem(2,&hdItem);
	m_pHeader->EnableWindow(FALSE);

	return 0;
}

void CAiredWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CAiredWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CAiredWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CAiredWnd::LogItem( typeLogItem *lpItem )
{
	if( (g_bHaspOK) && (!g_bNoLog) )
	{
		g_pLogger->AddItem(lpItem);
	}
	/*
	lpItem->lp = (LPVOID)this;
	AfxBeginThread( LogItemThread,(LPVOID)lpItem,THREAD_PRIORITY_LOWEST );
	*/
}

UINT CAiredWnd::LogItemThread( LPVOID lp )
{
/*
#ifdef __DEBUG_LOG
	WriteLogFile("CAiredWnd::LogItemThread (Enter)");
#endif
	typeLogItem *lpItem = (typeLogItem *)lp;
	CAiredWnd	*pWnd = (CAiredWnd *)lpItem->lp;
	CString strSQL,
			strDate,
			strTemp;
	COleDateTime date=COleDateTime::GetCurrentTime();
	CDatabase	db;

	if( (!g_bHaspOK) || (g_bNoLog) )
		return 0;

	do {
		try
		{
			db.OpenEx("DSN="+g_strOnAirConnect,CDatabase::noOdbcDialog);
		}
		catch(...){}
	} while( !db.IsOpen() );

	strDate.Format("%d-%d-%d %d:%d:%d",date.GetYear(),date.GetMonth(),date.GetDay(),date.GetHour(),date.GetMinute(),date.GetSecond());

	if( (lpItem->lID!= 0) )
	{
		strSQL.Format("INSERT INTO OnAirLog ([Date],[ComputerID],[UserID],[ItemID],[ItemType]) VALUES ('%s','%d','%d','%d','%d')",
			strDate,g_lComputerID,g_lUserID,lpItem->lID,lpItem->wType);
#ifdef __DEBUG_LOG
		WriteLogFile("CAiredWnd::LogItemThread SQL "+strSQL);
#endif
		try
		{
			db.ExecuteSQL(strSQL);
		}
		catch(...)
		{
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	strTemp = lpItem->strName;
	strTemp.Replace("'","''");
	
	strSQL.Format("INSERT INTO OnAirTextLog ([Date],[Log]) VALUES ('%s','%s')",
		strDate,strTemp);

#ifdef __DEBUG_LOG
	WriteLogFile("CAiredWnd::LogItemThread SQL "+strSQL);
#endif

	try
	{
		db.ExecuteSQL(strSQL);
	}
	catch(...)
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////
	if( lpItem->lTraffic )
	{
		strSQL.Format("UPDATE Traffic SET Aired = 1, AiringDate = '%s', TalentID='%d' WHERE ID = '%d'",
			strDate,g_lUserID,lpItem->lTraffic);
#ifdef __DEBUG_LOG
		WriteLogFile("CAiredWnd::LogItemThread SQL "+strSQL);
#endif

		try
		{
			db.ExecuteSQL(strSQL);
		}
		catch(...)
		{
		}
	}
	else if( lpItem->wType==TYPE_SPOT )
	{
		strSQL.Format("INSERT INTO Traffic (Aired,AiringDate,TalentID,SpotID) VALUES ('1','%s',%d,%d)",
			strDate,g_lUserID,lpItem->lID);

#ifdef __DEBUG_LOG
		WriteLogFile("CAiredWnd::LogItemThread SQL "+strSQL);
#endif

		try
		{
			db.ExecuteSQL(strSQL);
		}
		catch(...)
		{
		}
	}
	
	if( lpItem->lID!=0 )
	{
		typeLineUpItem *lpNew = new typeLineUpItem(lpItem->wType,lpItem->lID);
		SYSTEMTIME st;
		date.GetAsSystemTime(st);

		SystemTimeToFileTime(&st,(FILETIME *)&lpNew->m_qwStartTime);
		pWnd->m_pList->InsertString(0,(LPCTSTR)lpNew);
	}

	delete lpItem;

	db.Close();
#ifdef __DEBUG_LOG
	WriteLogFile("CAiredWnd::LogItemThread (Exit)");
#endif */
	return 0;
}

void CAiredWnd::OnRefresh()
{
	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(RefreshList,(LPVOID)m_pList);
}

UINT CAiredWnd::RefreshList( LPVOID lp )
{
	CAiredListBox *pList = (CAiredListBox *)lp;

	pList->m_bIsRefreshing = TRUE;
	pList->ResetContent();

	COleDateTime	dt=COleDateTime::GetCurrentTime()-COleDateTimeSpan(0,4,0,0);
	SYSTEMTIME		st;
	CRSOnAirLog		rs(g_strOnAirConnect);
	typeLineUpItem	*lpItem;

	rs.m_strFilter.Format("Date >= '%d-%d-%d %d:%d:%d'",
		dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond() );
	rs.m_strSort = "Date DESC";
	rs.Open();

	while( !rs.IsEOF() )
	{
		lpItem = new typeLineUpItem((WORD)rs.m_ItemType,rs.m_ItemID);

		rs.m_Date.GetAsSystemTime(st);
		SystemTimeToFileTime(&st,(FILETIME *)&lpItem->m_qwStartTime);
		pList->InsertString(-1,(LPCTSTR)lpItem);

		rs.MoveNext();
	}
	rs.Close();

	pList->m_bIsRefreshing = FALSE;
	return 0;
}
