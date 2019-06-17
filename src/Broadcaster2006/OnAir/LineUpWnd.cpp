// LineUpWnd.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "OnAir.h"
#include "LineUpWnd.h"
#include "OnAirPlayerWnd.h"
#include "typeLineUpItem.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"
#include "..\common\include\rsviewinstrumentals.h"
#include "..\common\include\splitter_utils.h"
#include "..\include\RSSchedule.h"
#include "..\include\RSScheduleHeadline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_LINEUP_LIST		101

extern long g_iInstrumental;
extern DWORD	g_dwMixerID;
extern DWORD	g_dwMixerLineID;
extern BOOL		g_bMixer;

CPlayersLogQueue *g_pPlayersLogQueue=new CPlayersLogQueue;

/////////////////////////////////////////////////////////////////////////////
// CLineUpWnd

IMPLEMENT_DYNCREATE(CLineUpWnd, CFrameWnd)


CLineUpWnd::CLineUpWnd()
{
	m_qwLineUpLength=0;
}

CLineUpWnd::~CLineUpWnd()
{
}


BEGIN_MESSAGE_MAP(CLineUpWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CLineUpWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	ON_COMMAND( CM_REMOVE,OnRemove )
	ON_COMMAND( CM_MOVEUP,OnMoveUp )
	ON_COMMAND( CM_MOVEDOWN,OnMoveDown)
	ON_COMMAND( CM_PFL,OnPFL)
	ON_COMMAND( CM_INFO,OnInfo)
	ON_MESSAGE( UM_SORTPLAYERS,OnSortPlayers )
	ON_MESSAGE( UM_STARTNEXTPLAYER, OnStartNextPlayer )
	ON_MESSAGE( UM_MAKESPACE,OnMakeSpace)
	ON_MESSAGE( UM_BLOCKRDBLCLK,OnBlockRDblClk)
	ON_MESSAGE( UM_PLAYERSTOPED,OnPlayerStoped )
	ON_MESSAGE( UM_SPACEPRESSED,OnSpacePressed )
	ON_MESSAGE( UM_PAUSE, OnPause )
	ON_MESSAGE( UM_SCROLL, OnScroll )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineUpWnd message handlers

int CLineUpWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	rect;
	GetClientRect(&rect);
	rect.bottom=rect.top+75;

	for( int n=0; n<4; n++ )
	{
		m_wndPlayer[n]=new COnAirPlayerWnd();
		m_wndPlayer[n]->Create(NULL,WS_VISIBLE|SS_NOTIFY,rect,this);
		m_wndPlayer[n]->m_wPlayerPos=n;
		m_wndPlayer[n]->m_wPlayerState=STATE_UNCUED;

		rect.OffsetRect(0,75);
	}

	////////////////////////////////////////////////////////////////////////////
	// Header creation 
	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|HDS_BUTTONS,CRect(0,0,0,0),this,87);
	
	HDITEM	hdItem;
	CString	strTemp;

	strTemp.LoadString(IDS_TITLE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=0;
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	strTemp.LoadString(IDS_STARTINGTIME);
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=120;
	m_pHeader->InsertItem(2,&hdItem);
	m_pHeader->EnableWindow(FALSE);

	//////////////////////////////////////////////////////////////////////////////
	//	ReBar
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);

	TBBUTTON	buttons[9];
	buttons[0].iBitmap=4;
	buttons[0].idCommand=CM_MOVEUP;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=4;

	buttons[1].iBitmap=5;
	buttons[1].idCommand=CM_MOVEDOWN;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=5;

	buttons[2].iBitmap=5;
	buttons[2].idCommand=0;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBBS_SEPARATOR;
	buttons[2].dwData=0;
	buttons[2].iString=5;

	buttons[3].iBitmap=10;
	buttons[3].idCommand=CM_REMOVE;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_BUTTON;
	buttons[3].dwData=0;
	buttons[3].iString=2;

	buttons[4].iBitmap=5;
	buttons[4].idCommand=0;
	buttons[4].fsState=TBSTATE_ENABLED;
	buttons[4].fsStyle=TBBS_SEPARATOR;
	buttons[4].dwData=0;
	buttons[4].iString=5;

	buttons[5].iBitmap=2;
	buttons[5].idCommand=CM_PFL;
	buttons[5].fsState=TBSTATE_ENABLED;
	buttons[5].fsStyle=TBSTYLE_BUTTON;
	buttons[5].dwData=0;
	buttons[5].iString=3;

	buttons[6].iBitmap=3;
	buttons[6].idCommand=CM_INFO;
	buttons[6].fsState=TBSTATE_ENABLED;
	buttons[6].fsStyle=TBSTYLE_BUTTON;
	buttons[6].dwData=0;
	buttons[6].iString=1;

	buttons[7].iBitmap=5;
	buttons[7].idCommand=0;
	buttons[7].fsState=TBSTATE_ENABLED;
	buttons[7].fsStyle=TBBS_SEPARATOR;
	buttons[7].dwData=0;
	buttons[7].iString=5;

	
	m_pToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	m_pToolBar->SetButtonSize(size);
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->SetDisabledImageList(g_ilToolEnabled);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(8,buttons);
	m_pToolBar->AutoSize();

	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);

	////////////////////////////////////////////////////////////////////////////////
	//	LineUp list
	m_pList = new CLineUpListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,rect,this,ID_LINEUP_LIST);

	return 0;
}

void CLineUpWnd::OnSize(UINT nType, int cx, int cy) 
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnSize (Enter)");
#endif
	CFrameWnd::OnSize(nType, cx, cy);
	
	CRect	rect(0,0,cx,75);
	for( int n=0; n<4; n++ )
	{
		m_wndPlayer[n]->MoveWindow(rect);
		rect.OffsetRect(0,75);
	}

	rect.DeflateRect(0,0,0,55);
	m_pHeader->MoveWindow(rect);

	rect.top+=20;
	rect.bottom=cy-66;

	m_pList->MoveWindow(rect);

	HDITEM	hdItem;
	hdItem.mask=HDI_WIDTH;
	hdItem.cxy=rect.right-120;
	m_pHeader->SetItem(0,&hdItem);

#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnSize (Exit)");
#endif
}

void CLineUpWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)) );
}

void CLineUpWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CLineUpWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CLineUpWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// Do nothing
}

void CLineUpWnd::AddItemByClick( typeArchiveItem* lpItem )
{
#ifdef __DEBUG_LOG
		WriteLogFile("CLineUpWnd::AddItemByClick (Enter)");
#endif

	if( lpItem->wType==TYPE_SCHEDULE )
	{
		AddSchedule(lpItem->lID);
		return;
	}

	DWORD64		qwTime=0;
	long int	Pos=m_pList->GetCurSel();

	if( lpItem->wType==TYPE_BLOCK )
	{
		CalcStartingTimes();
		if( Pos!=LB_ERR )
		{
			typeLineUpItem *lpTemp = (typeLineUpItem *)m_pList->GetItemData(Pos);
			qwTime = lpTemp->m_qwStartTime;
		}
		else 
		{
			FILETIME	ftUTC,
						ST;

			GetSystemTimeAsFileTime(&ftUTC);
			FileTimeToLocalFileTime(&ftUTC,&ST);
			memcpy(&qwTime,&ST,8);
			qwTime+=GetTotalLength();
		}
		
	}

	typeLineUpItem* lpNewItem = new typeLineUpItem(lpItem->wType,lpItem->lID,qwTime);

	if( lpNewItem->m_bItemIsValid )
	{
		lpNewItem->m_lTrafficID=lpItem->lTraffID;
		m_pList->InsertString(Pos,(LPCTSTR)lpNewItem);
		CalcStartingTimes();
	}
	else
		SAFE_DELETE( lpNewItem );

#ifdef __DEBUG_LOG
		WriteLogFile("CLineUpWnd::AddItemByClick (Eextit)");
#endif

}

void CLineUpWnd::AddSchedule(long ID,DWORD64 qwMinLength )
{
#ifdef __DEBUG_LOG
		WriteLogFile("CLineUpWnd::AddSchedule (Enter)");
#endif

	CDatabase db;
	do {
		db.OpenEx("DSN="+g_strOnAirConnect,CDatabase::noOdbcDialog);
	} while( !db.IsOpen() );

	if( g_bTimeOut ) 
		db.SetQueryTimeout(1);
	else
		db.SetQueryTimeout(360);

	CRSSchedule	rs("",&db );
	typeLineUpItem *lpItem;
	long	Pos;
	MSG		msg;
	DWORD64 qwCurTime;
	FILETIME	ftUTC, ST;

	GetSystemTimeAsFileTime(&ftUTC);
	FileTimeToLocalFileTime(&ftUTC,&ST);
	memcpy(&qwCurTime,&ST,8);

	Pos = m_pList->GetCurSel();
	if( Pos==LB_ERR )
		qwCurTime += GetTotalLength();
	else
	{
		CalcStartingTimes();
		lpItem = (typeLineUpItem *)m_pList->GetItemData(Pos);
		qwCurTime = lpItem->m_qwStartTime;
	}

	rs.m_strFilter.Format("ScheduleID = %d",ID );
	rs.m_strSort="ItemOrder";
	rs.Open();

	while( !rs.IsEOF() )
	{
		lpItem = new typeLineUpItem((WORD)rs.m_ItemType,rs.m_ItemID);
		if( lpItem->m_bItemIsValid )
		{
			Pos=m_pList->GetCurSel();
			lpItem->m_bLocked = rs.m_Priority;
			m_pList->InsertString(Pos,(LPCTSTR)lpItem);
		}
		else
			SAFE_DELETE( lpItem );

		rs.MoveNext();

		while (PeekMessage(&msg,m_hWnd,0,0,PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	rs.Close();

	CalcStartingTimes();

	if( qwMinLength!=0 )
	{
		int nCount = m_pList->GetCount();
		for( Pos=0; Pos<nCount; Pos++ )
		{
			lpItem = (typeLineUpItem *)m_pList->GetItemData(Pos);
			if( lpItem->m_qwStartTime < qwCurTime+qwMinLength )
				lpItem->m_bCanDelete = FALSE;
		}
	}
	db.Close();

#ifdef __DEBUG_LOG
		WriteLogFile("CLineUpWnd::AddSchedule (Exit)");
#endif

}


void CLineUpWnd::RemoveLeftOvers()
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::RemoveLeftovers (Enter)");
#endif
	typeLineUpItem *lpItem;
	int nCount=m_pList->GetCount();
	int	nPos=0;
	BOOL bFirstUnlock = FALSE;

	while( nPos<m_pList->GetCount() )
	{
		lpItem = (typeLineUpItem *)m_pList->GetItemData(nPos);

		if( !bFirstUnlock && !lpItem->m_bLocked )
			bFirstUnlock=TRUE;

		if( (lpItem->m_bCanDelete && bFirstUnlock) )
		{
			m_pList->DeleteString(nPos);
			delete lpItem;
		}
		else
			nPos++;
	}

#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::RemoveLeftovers (Exit)");
#endif
}

typeLineUpItem* CLineUpWnd::GetFirstItem()
{
#ifdef __DEBUG_LOG
		WriteLogFile("CLineUpWnd::GetFirstItem (Enter)");
#endif

	if( m_pList->GetCount()==0)
		return NULL;

	typeLineUpItem* lpResult;
	typeLineUpItem* lpItem=(typeLineUpItem*)m_pList->GetItemData(0);

	if( lpItem->m_wType==TYPE_BLOCK )
	{
		lpResult=(typeLineUpItem *)(lpItem->m_pBlock[lpItem->m_iNextItem]);
		if( lpResult!=NULL )
		{
			lpItem->m_pBlock[lpItem->m_iNextItem]=NULL;
			lpItem->m_lEndPos-=lpResult->GetTimeToMix();
			lpItem->m_lMixPos-=lpResult->GetTimeToMix();
			lpResult->m_bBlock=TRUE;
			if( lpResult->m_wType==TYPE_TIMESIGNAL )
			{
				DWORD64 qwCurTime;
				FILETIME tempFT;

				GetSystemTimeAsFileTime(&tempFT);
				FileTimeToLocalFileTime(&tempFT,(FILETIME*)&qwCurTime);

				lpResult->m_qwStartTime=qwCurTime+GetPlayersTime();
			}
		}

		lpItem->m_iNextItem++;
		m_pList->SetItemHeight(0,30*(lpItem->m_iBlockSize-lpItem->m_iNextItem+1));
		m_pList->Invalidate();

		if( lpItem->m_iNextItem>=lpItem->m_iBlockSize )
		{
			m_pList->DeleteString(0);
			delete lpItem;
		}
	}
	else
	{
		if( (g_wndTrafficInfo->m_pNextBlock!=NULL) && (!lpItem->m_bLocked) )
		{
			FILETIME	ft;
			DWORD64		qwTime;

			GetSystemTimeAsFileTime(&ft);
			FileTimeToLocalFileTime(&ft,(LPFILETIME)&qwTime);
			qwTime += ((CLineUpWnd *)g_wndLineUp)->GetPlayersTime();

			if( qwTime>=(g_wndTrafficInfo->m_pNextBlock->m_qwStartTime-30000000) )
			{
				m_pList->InsertString(0,(LPCTSTR)g_wndTrafficInfo->m_pNextBlock);

				// Log Item -----------------------------------------------------------------------
				typeLogItem *lpLog=new typeLogItem;
				lpLog->wType = 0;
				lpLog->lID = 0;
				lpLog->lTraffic = 0;
				wsprintf(lpLog->strName,"--> Line Up - Insert Block - %s - %s",g_wndTrafficInfo->m_pNextBlock->m_strName,g_wndTrafficInfo->m_pNextBlock->m_strName2);
				g_wndAired->LogItem(lpLog);
				// --------------------------------------------------------------------------------

				if( (g_nSplitters>0)  )
				{
					typeSplitterMsg	Msg;

					memset(&Msg,0,SIZEOFSPLITTERMSG);
					Msg.wAction	= SP_CUE;
					Msg.wType	= TYPE_BLOCK;
					Msg.wFinish	= g_wndTrafficInfo->m_pNextBlock->m_wPrecision;
				
					wsprintf(Msg.pstrMessage,"Cue Block: %s - %s",
								g_wndTrafficInfo->m_pNextBlock->m_strName,
								g_wndTrafficInfo->m_pNextBlock->m_strName2);
					SendSplitterMessage(&Msg);
				}

				if( (g_wndTrafficInfo->m_pNextBlock->m_wPrecision!=3) && (qwTime>g_wndTrafficInfo->m_pNextBlock->m_qwStartTime) )
					CutOnPlayer( (long)((qwTime-g_wndTrafficInfo->m_pNextBlock->m_qwStartTime)/10000));

				g_wndTrafficInfo->GetNextBlockThread( (LPVOID)g_wndTrafficInfo );

				return GetFirstItem();
			}
			else // Check for instrumental replacement
			{
				if( (g_iInstrumental>0) && (g_wAutomationMode!=2374) && (lpItem->m_wType == TYPE_MUSIC) && (g_wndTrafficInfo->m_pNextBlock->m_wPrecision != 3) )
				{
					if( (lpItem->GetLength()>g_iInstrumental*1000) && (g_wndTrafficInfo->m_pNextBlock->m_qwStartTime-qwTime<(DWORD64)g_iInstrumental*10000000) )
					{
#ifdef __DEBUG_LOG
						WriteLogFile("CLineUpWnd::GetFirstItem (Enter Inst Replace)");
#endif

						CString					strSQL,
												strRythm;
						CRSViewInstrumentals	rsInst( g_strOnAirConnect);

						if( lpItem->m_wRythm <= g_iSlow )
							strRythm.Format("Rythm <= %d",g_iSlow);
						else if( lpItem->m_wRythm <= g_iSlowAverage )
							strRythm.Format("Rythm >= %d AND Rythm <= %d",g_iSlow,g_iSlowAverage);
						else if( lpItem->m_wRythm <= g_iAverage )
							strRythm.Format("Rythm >= %d AND Rythm <= %d",g_iSlowAverage,g_iAverage);
						else
							strRythm.Format("Rythm >= %d",g_iAverage);

//						strSQL.Format("SELECT [ID],[TypeID],[ElementID],[LastDate],[Title],[Artist],abs([length]-%d) AS [Length],[Rythm] FROM ViewInstrumentals",
//										(g_wndTrafficInfo->m_pNextBlock->m_qwStartTime-qwTime)/10000 );

						strSQL.Format("abs(Length-%d)<3000",(g_wndTrafficInfo->m_pNextBlock->m_qwStartTime-qwTime)/10000);

						rsInst.m_strSort = "Length, LastDate";
						rsInst.m_strFilter = strSQL+" AND "+strRythm;
						rsInst.Open();

						if( rsInst.GetRecordCount()!=0 )
						{
							lpResult = new typeLineUpItem((WORD)rsInst.m_TypeID,rsInst.m_ElementID);
							if( lpResult->m_bItemIsValid )
							{
								// Log Item -----------------------------------------------------------------------
								typeLogItem *lpLog=new typeLogItem;
								lpLog->wType = 0;
								lpLog->lID = 0;
								lpLog->lTraffic = 0;
								wsprintf(lpLog->strName,"--> Instrumental - 1 - %s - %s",lpResult->m_strName,lpResult->m_strName2);
								g_wndAired->LogItem(lpLog);
#ifdef __DEBUG_LOG
								WriteLogFile("CLineUpWnd::GetFirstItem (Exit Inst Replace 1)");
#endif
								return lpResult;
							}
							else 
							SAFE_DELETE( lpResult );
						}
						else
						{
							rsInst.m_strFilter = strSQL;
							rsInst.Requery();
							if( rsInst.GetRecordCount()!=0 )
							{
								lpResult = new typeLineUpItem((WORD)rsInst.m_TypeID,rsInst.m_ElementID);
								if( lpResult->m_bItemIsValid )
								{
									// Log Item -----------------------------------------------------------------------
									typeLogItem *lpLog=new typeLogItem;
									lpLog->wType = 0;
									lpLog->lID = 0;
									lpLog->lTraffic = 0;
									wsprintf(lpLog->strName,"--> Instrumental - 2 - %s - %s",lpResult->m_strName,lpResult->m_strName2);
									g_wndAired->LogItem(lpLog);

#ifdef __DEBUG_LOG
									WriteLogFile("CLineUpWnd::GetFirstItem (Exit Inst Replace 2)");
#endif
									return lpResult;
								}
								else
									SAFE_DELETE(lpResult);
							}
							else
							{
								rsInst.m_strFilter.Format("Length > %d",(g_wndTrafficInfo->m_pNextBlock->m_qwStartTime-qwTime)/10000);
								rsInst.Requery();

								if( rsInst.GetRecordCount()!=0 )
								{
									lpResult = new typeLineUpItem((WORD)rsInst.m_TypeID,rsInst.m_ElementID);
									if( lpResult->m_bItemIsValid )
									{
										// Log Item -----------------------------------------------------------------------
										typeLogItem *lpLog=new typeLogItem;
										lpLog->wType = 0;
										lpLog->lID = 0;
										lpLog->lTraffic = 0;
										wsprintf(lpLog->strName,"--> Instrumental - 3 - %s - %s",strSQL,lpResult->m_strName2);
										g_wndAired->LogItem(lpLog);

#ifdef __DEBUG_LOG
										WriteLogFile("CLineUpWnd::GetFirstItem (Exit Inst Replace 3)");
#endif
										return lpResult;
									}
									else
										SAFE_DELETE( lpResult);
								}
							}	
						}
					}
				}
			}
		}

		lpResult=lpItem;
		m_pList->DeleteString(0);
	}
 
	CalcStartingTimes();

#ifdef __DEBUG_LOG
	WriteLogFile("CLineUpWnd::GetFirstItem (Exit)");
#endif
	return lpResult;
}

void CLineUpWnd::CalcStartingTimes()
{
	long int nItems=m_pList->GetCount();
	long int nCont=0;
	typeLineUpItem* lpItem;
	FILETIME	ST,ftUTC;
	DWORD64		qwTime;

	m_qwLineUpLength=0;

	GetSystemTimeAsFileTime(&ftUTC);
	FileTimeToLocalFileTime(&ftUTC,&ST);
	memcpy(&qwTime,&ST,8);
	qwTime+=GetPlayersTime();

	while( nCont<nItems ) 
	{
		lpItem=(typeLineUpItem*)m_pList->GetItemData(nCont);
		if( lpItem!=NULL )
		{
			lpItem->m_qwStartTime=qwTime;
			
			if( lpItem->m_wType==TYPE_BLOCK )
			{
				DWORD64 qwTemp=qwTime;
				for( int I=lpItem->m_iNextItem; I<lpItem->m_iBlockSize; I++ )
				{
					typeLineUpItem *lpTemp = (typeLineUpItem *)lpItem->m_pBlock[I];
					lpTemp->m_qwStartTime=qwTemp;
					qwTemp+=(DWORD64)(lpTemp->GetTimeToMix())*10000;
				}
			}
		
			qwTime+=(DWORD64)(lpItem->GetTimeToMix())*10000;
			m_qwLineUpLength+=(DWORD64)(lpItem->GetTimeToMix())*10000;
		}
		nCont++;
	}
//	tbAlinhamento->Crono->qwLineup=qwLineup;
	m_pList->Invalidate(FALSE);
}

LRESULT CLineUpWnd::OnSortPlayers(WPARAM wPlayer, LPARAM wAction)
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnSortPlayers (Enter)");
#endif

	int Cont;
	COnAirPlayerWnd* wndTemp;
	CRect Rect1,Rect2,Rect3;
	GetWindowRect(&Rect3);

	switch( wAction )
	{
	case SORT_CUE:
		for( Cont=wPlayer; Cont>0; Cont-- )
		{
			if( m_wndPlayer[Cont-1]->m_wPlayerState==STATE_UNCUED )
			{
				wndTemp=m_wndPlayer[Cont];
				m_wndPlayer[Cont]=m_wndPlayer[Cont-1];	
				m_wndPlayer[Cont-1]=wndTemp;

				m_wndPlayer[Cont-1]->GetWindowRect(&Rect2);
				m_wndPlayer[Cont]->GetWindowRect(&Rect1);

				Rect1.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));
				Rect2.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));

				m_wndPlayer[Cont-1]->MoveWindow(&Rect1,FALSE);
				m_wndPlayer[Cont-1]->m_wPlayerPos--;
				m_wndPlayer[Cont-1]->Invalidate(FALSE);

				m_wndPlayer[Cont]->MoveWindow(&Rect2,FALSE);
				m_wndPlayer[Cont]->m_wPlayerPos++;
				m_wndPlayer[Cont]->Invalidate(FALSE);
			}
		}
		break;
	case SORT_PLAY:
		for( Cont=wPlayer; Cont>0; Cont-- )
		{
			if( m_wndPlayer[Cont-1]->m_wPlayerState!=STATE_PLAYING )
			{
				wndTemp=m_wndPlayer[Cont];
				m_wndPlayer[Cont]=m_wndPlayer[Cont-1];	
				m_wndPlayer[Cont-1]=wndTemp;

				m_wndPlayer[Cont-1]->GetWindowRect(&Rect2);
				m_wndPlayer[Cont]->GetWindowRect(&Rect1);

				Rect1.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));
				Rect2.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));

				m_wndPlayer[Cont-1]->MoveWindow(&Rect1,FALSE);
				m_wndPlayer[Cont-1]->m_wPlayerPos--;
				m_wndPlayer[Cont-1]->Invalidate(FALSE);

				m_wndPlayer[Cont]->MoveWindow(&Rect2,FALSE);
				m_wndPlayer[Cont]->m_wPlayerPos++;
				m_wndPlayer[Cont]->Invalidate(FALSE);
			}
		}
		break;
	case SORT_UNCUE:
		for( Cont=wPlayer; Cont<3; Cont++ )
		{
			if( m_wndPlayer[Cont+1]->m_wPlayerState!=STATE_UNCUED )
			{
				wndTemp=m_wndPlayer[Cont];
				m_wndPlayer[Cont]=m_wndPlayer[Cont+1];	
				m_wndPlayer[Cont+1]=wndTemp;

				m_wndPlayer[Cont+1]->GetWindowRect(&Rect2);
				m_wndPlayer[Cont]->GetWindowRect(&Rect1);

				Rect1.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));
				Rect2.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));

				m_wndPlayer[Cont+1]->MoveWindow(&Rect1,FALSE);
				m_wndPlayer[Cont+1]->m_wPlayerPos++;
				m_wndPlayer[Cont+1]->Invalidate(FALSE);

				m_wndPlayer[Cont]->MoveWindow(&Rect2,FALSE);
				m_wndPlayer[Cont]->m_wPlayerPos--;
				m_wndPlayer[Cont]->Invalidate(FALSE);
			}
		}
		break;
	}

	ResetTimers();
	LogPlayers();

#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnSortPlayers (Exit)");
#endif
	return 0;
}

LRESULT CLineUpWnd::OnStartNextPlayer(WPARAM w, LPARAM)
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnStartNextPlayer (Enter)");
#endif
	if( g_wAutomationMode == AUTOMATION_MANUAL )
		return 0;

	for( int Cont=w; Cont<4; Cont++ )
	{
		if( m_wndPlayer[Cont]->m_wPlayerState==STATE_CUED )
		{
			m_wndPlayer[Cont]->CmPlay();
			break;
		}
	}
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnStartNextPlayer (Exit)");
#endif
	return 0;
}

void CLineUpWnd::AddItemByUnload(typeLineUpItem *lpItem)
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::AddItemByUnload (Enter)");
#endif
	m_pList->InsertString(0,(LPCTSTR)lpItem);

	CalcStartingTimes();
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::AddItemByUnload (Exit)");
#endif
}

void CLineUpWnd::OnRemove()
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnRemove (Enter)");
#endif
	int Pos=m_pList->GetCurSel();

	if( Pos==LB_ERR )
		return;

	typeLineUpItem*	lpItem = (typeLineUpItem*)m_pList->GetItemData(Pos);
	m_pList->DeleteString(Pos);
	m_pList->SetCurSel(Pos);

	SAFE_DELETE( lpItem );
	CalcStartingTimes();
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnRemove (Exit)");
#endif
}

LRESULT CLineUpWnd::OnMakeSpace(WPARAM w, LPARAM)
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnMakeSpace (Enter)");
#endif
	m_wndPlayer[3]->OnUnCue();
	
	for( WORD Cont=3; Cont>w; Cont-- )
	{
		m_wndPlayer[Cont]->m_lpItem			= m_wndPlayer[Cont-1]->m_lpItem;
		m_wndPlayer[Cont]->m_wPlayerState	= m_wndPlayer[Cont-1]->m_wPlayerState;
		m_wndPlayer[Cont]->UpdateButtons();

		m_wndPlayer[Cont]->Invalidate();
	}
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::OnMakeSpace (Exit)");
#endif
	return 0;
}

LRESULT CLineUpWnd::OnSpacePressed(WPARAM,LPARAM)
{
	BOOL	bMix=FALSE;

	for( int i=3; i>=0; i-- )
		if( m_wndPlayer[i]->m_wPlayerState==STATE_PLAYING )
		{
			if( m_wndPlayer[i]->m_lpItem->m_bPause )
			{
				m_wndPlayer[i]->m_lpItem->m_bPause=FALSE;
				m_wndPlayer[i]->m_lpItem->m_Sound->Play();
				m_wndPlayer[i]->m_pOptions->m_pPause->m_bLight=FALSE;
				m_wndPlayer[i]->m_pOptions->m_pPause->Invalidate();
			}
			else
			{
				bMix=TRUE;
				m_wndPlayer[i]->CmMix();
			}
			break;
		}

	if( (!bMix) && (m_wndPlayer[0]->m_wPlayerState==STATE_CUED) )
		m_wndPlayer[0]->CmPlay();

	return 0;
}

DWORD64 CLineUpWnd::GetPlayersTime()
{
	DWORD64 dwResult=0;

	for( int Cont=0; Cont<4; Cont++ )
		dwResult+=m_wndPlayer[Cont]->GetTimeToMix();
	
	return dwResult;
}

DWORD64 CLineUpWnd::GetTotalLength()
{
	return m_qwLineUpLength+GetPlayersTime();
}

DWORD64 CLineUpWnd::GetLastTrackTimeToMix()
{
	for( int iCont=3; iCont>=0; iCont-- )
		if( m_wndPlayer[iCont]->m_wPlayerState==STATE_PLAYING )
			if( m_wndPlayer[iCont]->m_lpItem->GetTimeToMix()>0 )
				return (DWORD64)(m_wndPlayer[iCont]->m_lpItem->GetTimeToMix())*10000;

	return 0;
}

void CLineUpWnd::OnMoveUp()
{
	long Pos=m_pList->GetCurSel();

	if( Pos==LB_ERR )
		return;

	DWORD dwItem=m_pList->GetItemData(Pos);
	m_pList->DeleteString(Pos);
	Pos--;
	Pos=m_pList->InsertString(Pos,(LPSTR)dwItem);
	m_pList->SetCurSel(Pos);
	CalcStartingTimes();
}	

void CLineUpWnd::OnMoveDown()
{
	long Pos=m_pList->GetCurSel();
	long Count=m_pList->GetCount();
	
	if( Pos!=LB_ERR )
	{
		DWORD dwItem=m_pList->GetItemData(Pos);
		m_pList->DeleteString(Pos);
		
		Pos++;
		if( Pos>=Count )
			Pos=0;
		
		Pos=m_pList->InsertString(Pos,(LPSTR)dwItem);
		m_pList->SetCurSel(Pos);

		CalcStartingTimes();
	}
}

void CLineUpWnd::OnPFL()
{
	long Pos=m_pList->GetCurSel();

	if( Pos==LB_ERR )
		return;

	typeLineUpItem *lpItem=(typeLineUpItem*)m_pList->GetItemData(Pos);
	if( lpItem->m_wType != TYPE_BLOCK )
	{
		g_wndPFL->SetSound(lpItem);
		g_wndPFL->RestoreWindow();
	}
}

void CLineUpWnd::ResetTimers()
{
#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::ResetTimers (Enter)");
#endif
	for( int iPlayer=0; iPlayer<4; iPlayer++ )
		m_wndPlayer[iPlayer]->ResetMixAndIntro();

	if( m_wndPlayer[0]->m_wPlayerState!=STATE_UNCUED )
	{
		if( m_wndPlayer[0]->m_lpItem->m_wType==TYPE_VOICEINSERT )
		{
			if( m_wndPlayer[1]->m_wPlayerState!=STATE_UNCUED )
			{
				m_wndPlayer[0]->m_lpItem->m_lMixPos = 
					m_wndPlayer[0]->m_lpItem->m_lOriginalMix = m_wndPlayer[0]->m_lpItem->m_lEndPos-m_wndPlayer[1]->m_lpItem->GetTimeToIntro();

				if( m_wndPlayer[0]->m_lpItem->m_lMixPos < m_wndPlayer[0]->m_lpItem->m_lStartPos )
					m_wndPlayer[0]->m_lpItem->m_lMixPos = m_wndPlayer[0]->m_lpItem->m_lStartPos;

				if( m_wndPlayer[1]->m_lpItem->GetTimeToIntro()>0 )
				{
					m_wndPlayer[1]->m_lpItem->m_Sound->SetVolume(g_iFadeOnIntro);
					m_wndPlayer[1]->m_lpItem->m_bFadeInOutOfTake=TRUE;
				}

				if( m_wndPlayer[1]->m_lpItem->GetTimeToIntro() > m_wndPlayer[0]->m_lpItem->GetTimeToEnd()+500 )
				{
					m_wndPlayer[1]->m_lpItem->m_lIntroPos=m_wndPlayer[1]->m_lpItem->m_lStartPos+(m_wndPlayer[0]->m_lpItem->m_lEndPos - m_wndPlayer[0]->m_lpItem->m_lMixPos);
					m_wndPlayer[1]->m_lpItem->m_lOriginalIntro=m_wndPlayer[1]->m_lpItem->m_lIntroPos;
				}
			}
		}
	}
	else
		return;


	if( m_wndPlayer[1]->m_wPlayerState==STATE_CUED )
	{
		if( m_wndPlayer[1]->m_lpItem->m_wType==TYPE_VOICEINSERT )
		{
			if( m_wndPlayer[2]->m_wPlayerState==STATE_CUED )
			{
				m_wndPlayer[1]->m_lpItem->m_lMixPos = 
					m_wndPlayer[1]->m_lpItem->m_lOriginalMix = m_wndPlayer[1]->m_lpItem->m_lEndPos-m_wndPlayer[2]->m_lpItem->GetTimeToIntro();

				if( m_wndPlayer[1]->m_lpItem->m_lMixPos < m_wndPlayer[1]->m_lpItem->m_lStartPos )
					m_wndPlayer[1]->m_lpItem->m_lMixPos = m_wndPlayer[1]->m_lpItem->m_lStartPos ;

				if( m_wndPlayer[2]->m_lpItem->GetTimeToIntro()>0 )
				{
					m_wndPlayer[2]->m_lpItem->m_Sound->SetVolume(g_iFadeOnIntro);
					m_wndPlayer[2]->m_lpItem->m_bFadeInOutOfTake=TRUE;
				}

				if( m_wndPlayer[1]->m_lpItem->GetTimeToMix()==0 )
					m_wndPlayer[2]->m_lpItem->m_lIntroPos=m_wndPlayer[2]->m_lpItem->m_lStartPos+m_wndPlayer[1]->m_lpItem->GetTimeToEnd();

				else if( m_wndPlayer[0]->m_lpItem->m_wType==TYPE_MUSIC )
				{
					m_wndPlayer[0]->m_lpItem->m_lMixPos-=m_wndPlayer[1]->m_lpItem->GetTimeToMix();
					m_wndPlayer[0]->m_lpItem->m_bFadeOutIntoTake=TRUE;
				}
			}
		}
	}
	else
		return;

	if( m_wndPlayer[2]->m_wPlayerState==STATE_CUED )
	{
		if( m_wndPlayer[2]->m_lpItem->m_wType==TYPE_VOICEINSERT )
		{
			if( m_wndPlayer[3]->m_wPlayerState==STATE_CUED )
			{
				m_wndPlayer[2]->m_lpItem->m_lMixPos = 
					m_wndPlayer[2]->m_lpItem->m_lOriginalMix = m_wndPlayer[2]->m_lpItem->m_lEndPos-m_wndPlayer[3]->m_lpItem->GetTimeToIntro();

				if( m_wndPlayer[2]->m_lpItem->m_lMixPos < m_wndPlayer[2]->m_lpItem->m_lStartPos )
					m_wndPlayer[2]->m_lpItem->m_lMixPos = m_wndPlayer[2]->m_lpItem->m_lStartPos;

				if( m_wndPlayer[3]->m_lpItem->GetTimeToIntro()>0 )
				{
					m_wndPlayer[3]->m_lpItem->m_Sound->SetVolume(g_iFadeOnIntro);
					m_wndPlayer[3]->m_lpItem->m_bFadeInOutOfTake=TRUE;
				}

				if( m_wndPlayer[2]->m_lpItem->GetTimeToMix()==0 )
					m_wndPlayer[3]->m_lpItem->m_lIntroPos=m_wndPlayer[3]->m_lpItem->m_lStartPos+m_wndPlayer[2]->m_lpItem->GetTimeToEnd();
				else if( m_wndPlayer[1]->m_lpItem->m_wType==TYPE_MUSIC )
				{
					m_wndPlayer[1]->m_lpItem->m_lMixPos-=m_wndPlayer[2]->m_lpItem->GetTimeToMix();
					m_wndPlayer[1]->m_lpItem->m_bFadeOutIntoTake=TRUE;
				}

				if( (m_wndPlayer[3]->m_lpItem->m_wType==TYPE_VOICEINSERT) )
					if( m_wndPlayer[2]->m_lpItem->m_wType==TYPE_MUSIC )
						m_wndPlayer[3]->m_lpItem->m_lMixPos = m_wndPlayer[3]->m_lpItem->m_lStartPos ;
			}
		}
	}
	else
		return;

#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::ResetTimers (Exit)");
#endif
}

void CLineUpWnd::CutOnPlayer( long l )
{
	for( int i=3; i>=0; i-- )
	{
		if( m_wndPlayer[i]->m_wPlayerState!=STATE_UNCUED )
		{
			if( (m_wndPlayer[i]->m_lpItem->GetTimeToMix()>=l) && (m_wndPlayer[i]->m_lpItem->m_wType==TYPE_MUSIC) )
			{
				m_wndPlayer[i]->m_lpItem->m_lMixPos-=l;
				m_wndPlayer[i]->m_lpItem->m_lOriginalMix = m_wndPlayer[i]->m_lpItem->m_lMixPos;
				m_wndPlayer[i]->m_lpItem->m_lFadeOutPos=m_wndPlayer[i]->m_lpItem->m_lMixPos-500;
				m_wndPlayer[i]->m_lpItem->m_lEndPos=m_wndPlayer[i]->m_lpItem->m_lMixPos+2000;
				break;
			}
		}
	}
}

LRESULT CLineUpWnd::OnPause(WPARAM,LPARAM) 
{
	for( int Cont=3; Cont>=0; Cont-- )
	{
		if( m_wndPlayer[Cont]->m_wPlayerState == STATE_PLAYING )
		{
			m_wndPlayer[Cont]->OnSwitchPause();
			break;
		}
	}

	return 0;
}

LRESULT CLineUpWnd::OnScroll(WPARAM,LPARAM) 
{
	for( int Cont=3; Cont>=0; Cont-- )
	{
		if( m_wndPlayer[Cont]->m_wPlayerState == STATE_PLAYING )
		{
			m_wndPlayer[Cont]->OnSwitchLoop();
			break;
		}
	}

	return 0;
}

void CLineUpWnd::GetStartupSchedule()
{
	CRSScheduleHeadline rs( g_strOnAirConnect );
	COleDateTime dt=COleDateTime::GetCurrentTime();
	CString strDate;

	strDate.Format("%d-%d-%d %d:%d:%d",dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond());
	rs.m_strFilter.Format("Date <= '%s' AND EndingDate >= '%s'",strDate,strDate);
	rs.Open();
	
	if( rs.GetRecordCount()==0 )
		return;

	AddSchedule(rs.m_ID);
	
	COleDateTimeSpan dts=dt-rs.m_Date;
	double	dwTemp=dts.GetTotalSeconds();
	DWORD64	qwExcess=(DWORD64)dwTemp*10000000;
	DWORD64 qwRemoved=0;
	
	typeLineUpItem *lpItem;
	
	while( (qwExcess>qwRemoved) && m_pList->GetCount()!=0 )
	{
		lpItem = (typeLineUpItem *)m_pList->GetItemData(0);
		qwRemoved += (DWORD64)(lpItem->GetLength())*10000;
		m_pList->DeleteString(0);
		delete lpItem;
	}
	
	for( int i=0; i<4; i ++ )
		if( ((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->m_wPlayerState==STATE_UNCUED )
			((CLineUpWnd *)g_wndLineUp)->m_wndPlayer[3]->CmCue();
	
}

void CLineUpWnd::OnInfo()
{
	long int nSel = m_pList->GetCurSel();

	if (nSel==LB_ERR )
		return;

	typeLineUpItem *lpItem = (typeLineUpItem *)m_pList->GetItemData(nSel);
	if( lpItem->m_wType!=TYPE_MUSIC )
		return;

	CString strURL;
	strURL.Format("%s\\OnAirSong.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->m_lItemID,g_strDB);
	g_wndMusicInfo->SetView(strURL);
}

LRESULT CLineUpWnd::OnBlockRDblClk(WPARAM wParam, LPARAM lParam)
{
	if( !g_bUserCanDelayBlocks )
		return 0;

	typeLineUpItem *lpItem=(typeLineUpItem *)lParam;

	for( int I=lpItem->m_iNextItem; I<lpItem->m_iBlockSize; I++ )
	{
		typeLineUpItem *lpBlockItem = (typeLineUpItem *)lpItem->m_pBlock[I];
		lpBlockItem->m_bBlock=TRUE;
		lpBlockItem->m_bCanDelete=FALSE;

		m_pList->InsertString(wParam,(LPCTSTR)lpBlockItem);
		wParam++;
	}
	m_pList->DeleteString(wParam);

	CalcStartingTimes();

	return 0;
}

LRESULT CLineUpWnd::OnPlayerStoped(WPARAM,LPARAM)
{
	if( g_wAutomationMode == AUTOMATION_MANUAL )
		return 0;

	BOOL	bPlaying	= FALSE,
			bCued		= FALSE;

	for( int i=0; i<4; i++ )
	{
		if( m_wndPlayer[i]->m_wPlayerState==STATE_CUED )
			bCued=TRUE;
		if( m_wndPlayer[i]->m_wPlayerState==STATE_PLAYING )
			bPlaying=TRUE;
	}

	if( !bPlaying && bCued )
		OnSpacePressed();

	return 0;
}


void CLineUpWnd::LogPlayers()
{
	tLogPlayers log;

	log.dateTime = COleDateTime::GetCurrentTime();

	for( int cont=0; cont<4; cont++ )
	{
		if( m_wndPlayer[cont]->m_wPlayerState!=STATE_UNCUED )
		{
			log.Player[cont].lItemID	 = m_wndPlayer[cont]->m_lpItem->m_lItemID;
			log.Player[cont].lItemType	 = m_wndPlayer[cont]->m_lpItem->m_wType;
			log.Player[cont].strArtist	 = m_wndPlayer[cont]->m_lpItem->m_strName;
			log.Player[cont].strTitle	 = m_wndPlayer[cont]->m_lpItem->m_strName2;
			log.Player[cont].lArtistID	 = m_wndPlayer[cont]->m_lpItem->m_lArtistID;
		}
		else
		{
			log.Player[cont].lItemID	 = 0;
			log.Player[cont].lItemType	 = 0;
			log.Player[cont].strArtist	 = "";
			log.Player[cont].strTitle	 = "";
			log.Player[cont].lArtistID	 = 0;
		}
	}

	g_pPlayersLogQueue->AddItem(log);
}

UINT CLineUpWnd::LogPlayersThread(LPVOID lp)
{
	/*
#ifdef __DEBUG_LOG 
	CWinThread *pThread=AfxGetThread();
	CString strThreadID=" ()";

	if( pThread!=NULL )
		strThreadID.Format(" (ID - %d)",pThread->m_nThreadID);

	WriteLogFile("CLineUpWnd::LogPlayersThread (Enter)");
#endif
	CString		strSQL,
				str1,
				str2;
	long		I;
	CDatabase	dbOnAirDB;
	tLogPlayers *pPlayer;
	LPVOID		*pData=(LPVOID *)lp;

	Sleep(g_iDelay);

	do {
		try {
			dbOnAirDB.OpenEx("DSN="+g_strOnAirConnect,CDatabase::noOdbcDialog);
		} catch(...) {};
	} while( !dbOnAirDB.IsOpen() );

	for( I=0; I<4; I++ )
	{
		pPlayer = (tLogPlayers *)pData[I];

		strSQL.Format("DELETE FROM Players WHERE [Order]='%d'",I);

		try {
			dbOnAirDB.ExecuteSQL(strSQL);
		} catch( ... ) {};

		str1 = pPlayer->strArtist;
		str2 = pPlayer->strTitle;

		str1.Replace("'","''");
		str2.Replace("'","''");

		strSQL.Format("INSERT INTO Players ([Order],ItemType,ItemID,ArtistID,ArtistName,TrackTitle) VALUES ('%d','%d','%d','%d','%s','%s')",
				I,
				pPlayer->lItemType,
				pPlayer->lItemID,
				pPlayer->lArtistID,
				str1,
				str2 );

#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::LogPlayersThread (SQL) - "+strSQL+strThreadID);
#endif	

		try {
			dbOnAirDB.ExecuteSQL(strSQL);
		} catch( ... ) {};

		delete pPlayer;
	}

	dbOnAirDB.Close();
	delete pData;

#ifdef __DEBUG_LOG 
	WriteLogFile("CLineUpWnd::LogPlayersThread (Exit)"+strThreadID);
#endif */
	return 0; 
}
void CLineUpWnd::OpenAuxMixer(void)
{
	MMRESULT mResult;

	mResult=mixerOpen(&m_hMixer,g_dwMixerID,(DWORD)m_hWnd,NULL,MIXER_OBJECTF_MIXER|CALLBACK_WINDOW);
	if( mResult!=MMSYSERR_NOERROR )
	{
		AfxMessageBox("Não foi possivel abrir o mixer!");
		g_bMixer=FALSE;
		m_hMixer=NULL;
		return;
	}

	mResult=mixerGetDevCaps(g_dwMixerID,&m_MixerCaps,sizeof(MIXERCAPS));
	if( mResult!=MMSYSERR_NOERROR )
	{
		AfxMessageBox("Não foi possivel obter a descrição do Mixer!");
		g_bMixer=FALSE;
		mixerClose(m_hMixer);
		m_hMixer=FALSE;
		return;
	}

	m_MixerLine.cbStruct=sizeof(MIXERLINE);
	m_MixerLine.dwLineID=g_dwMixerLineID;

	mResult = mixerGetLineInfo((HMIXEROBJ)m_hMixer,&m_MixerLine,MIXER_GETLINEINFOF_LINEID|MIXER_OBJECTF_HMIXER);
	if( mResult!=MMSYSERR_NOERROR )
	{
		AfxMessageBox("Não foi possivel obter a informação da linha do mixer!");
		g_bMixer=FALSE;
		mixerClose(m_hMixer);
		m_hMixer=FALSE;
		return;
	}

	m_MixerLineControls.cbStruct=sizeof(MIXERLINECONTROLS);
	m_MixerLineControls.dwLineID=g_dwMixerLineID;
	m_MixerLineControls.dwControlType=MIXERCONTROL_CONTROLTYPE_VOLUME;
	m_MixerLineControls.cControls=1;
	m_MixerLineControls.cbmxctrl=sizeof(MIXERCONTROL);
	m_MixerLineControls.pamxctrl=&m_MixerControl;

	mResult = mixerGetLineControls((HMIXEROBJ)m_hMixer,&m_MixerLineControls,MIXER_GETLINECONTROLSF_ONEBYTYPE|MIXER_OBJECTF_HMIXER);
	if( mResult!=MMSYSERR_NOERROR )
	{
		AfxMessageBox("Não foi possivel obter o controle de volume para a linha do mixer!");
		g_bMixer=FALSE;
		mixerClose(m_hMixer);
		m_hMixer=FALSE;
		return;
	}

	m_MixerControlDetails.cbStruct=sizeof(MIXERCONTROLDETAILS);
	m_MixerControlDetails.dwControlID=m_MixerControl.dwControlID;
	m_MixerControlDetails.cChannels=m_MixerLine.cChannels;
	m_MixerControlDetails.cMultipleItems=0;
	m_MixerControlDetails.cbDetails=sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	m_MixerControlDetails.paDetails=&m_MixerDetails;

	mResult = mixerGetControlDetails((HMIXEROBJ)m_hMixer,&m_MixerControlDetails,MIXER_GETCONTROLDETAILSF_VALUE|MIXER_OBJECTF_HMIXER);
}


void CLineUpWnd::RemoteControl(typeSplitterMsg msg)
{
	if( g_wAutomationMode!=AUTOMATION_FULLAUTO )
		return;

	CString	strTime;
	
	strTime.Format("%d",msg.lTime);

	switch( msg.wAction )
	{
	case SP_OPEN:
		//OpenBlock(Msg->strDate,Msg->lTime,Msg->lLength,Msg->wFinish);
		break;
	case SP_PLAY:
		//m_lBlockTime = Msg->lTime;
		//m_bStartBlock=TRUE;
		// OnSplitterPlayBlock(Msg->lTime);
		break;
	case SP_CUE:

		//OnSplitterCueBlock(Msg->strDate,Msg->lTime,Msg->lLength,Msg->wFinish);
		break;
	}
}

CPlayersLogQueue::CPlayersLogQueue()
{
	mutexQueue = new CMutex();
	pWorkThread = AfxBeginThread(WorkThread,(LPVOID)this,THREAD_PRIORITY_IDLE);
}

void CPlayersLogQueue::AddItem(tLogPlayers newItem)
{
	BOOL bLocked=mutexQueue->Lock(250);

	if( bLocked )
	{
		logQueue.AddHead(newItem);
		mutexQueue->Unlock();
	}
}

tLogPlayers *CPlayersLogQueue::GetItem()
{
	tLogPlayers *pLastItem=NULL; 
	BOOL bLocked=mutexQueue->Lock(250);

	if( bLocked )
	{
		if( !logQueue.IsEmpty() )
		{
			tLogPlayers temp = logQueue.GetTail();
			if( (temp.dateTime+COleDateTimeSpan(0,0,0,10))<=COleDateTime::GetCurrentTime() )
			{
				logQueue.RemoveTail();
				pLastItem = new tLogPlayers;
				pLastItem->dateTime = temp.dateTime;

				for( int cont=0; cont<4; cont++ )
				{
					pLastItem->Player[cont].lArtistID	= temp.Player[cont].lArtistID;
					pLastItem->Player[cont].lItemID		= temp.Player[cont].lItemID;
					pLastItem->Player[cont].lItemType	= temp.Player[cont].lItemType;
					pLastItem->Player[cont].strArtist	= temp.Player[cont].strArtist;
					pLastItem->Player[cont].strTitle	= temp.Player[cont].strTitle;
				}
			}
		}
		mutexQueue->Unlock();
	}
	return pLastItem;
}

BOOL CPlayersLogQueue::Lock(DWORD dwTimeout)
{
	BOOL bResult=mutexQueue->Lock(dwTimeout);
	return bResult;
}

BOOL CPlayersLogQueue::Unlock()
{
	BOOL bResult=mutexQueue->Unlock();
	return bResult;
}

UINT CPlayersLogQueue::WorkThread(LPVOID lpData)
{
	BOOL		bLocked;
	tLogPlayers *pLogItem;
	CDatabase	db;
	CString		strSQL;
	int			c;

	do {	
		pLogItem = g_pPlayersLogQueue->GetItem();
		if( pLogItem!=NULL )
		{
			// Open database
			#ifdef __DEBUG_LOG 
			WriteLogFile("CPlayersLogQueue::WorkThread (Open DB)");
			#endif	

			do {
				try {
					db.OpenEx("DSN="+g_strOnAirConnect,CDatabase::noOdbcDialog);
				} catch(...) {};
			} while( !db.IsOpen() );

			while( pLogItem!=NULL )
			{
				// Delete Players data
				strSQL = "DELETE FROM [Players]";

				try {
					db.ExecuteSQL(strSQL);
				} catch(...) {};

				// Add nem players data
				for( c=0; c<4; c++ )
				{
					pLogItem->Player[0].strArtist.Replace("'","''");
					pLogItem->Player[0].strTitle.Replace("'","''");

					strSQL.Format("INSERT INTO Players ([Order],ItemType,ItemID,ArtistID,ArtistName,TrackTitle) VALUES ('%d','%d','%d','%d','%s','%s')",
									c,
									pLogItem->Player[c].lItemType,
									pLogItem->Player[c].lItemID,
									pLogItem->Player[c].lArtistID,
									pLogItem->Player[c].strArtist,
									pLogItem->Player[c].strTitle );

					#ifdef __DEBUG_LOG 
					WriteLogFile("CPlayersLogQueue::WorkThread (SQL) "+strSQL);
					#endif	

					try {
						db.ExecuteSQL(strSQL);
					} catch(...) {};
				}
				// delete item
				delete pLogItem;
				// Get new item
				pLogItem=g_pPlayersLogQueue->GetItem();
			}
			// Close database
			#ifdef __DEBUG_LOG 
			WriteLogFile("CPlayersLogQueue::WorkThread (Close DB)");
			#endif	
			db.Close();
		}
		Sleep(1000);
	} while( TRUE );

	return 0;
};

