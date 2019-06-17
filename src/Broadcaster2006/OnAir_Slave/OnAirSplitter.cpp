// OnAirSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir_Slave.h"
#include "OnAirSplitter.h"
#include "Splitterconfigdlg.h"
#include ".\onairsplitter.h"
#include "..\onair\externalobjects.h"
#include "..\onair\airedwnd.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"
#include "..\include\rsblocksdefinition.h"
#include "..\common\include\rsviewinstrumentals.h"
#include "..\include\RSSchedule.h"

// COnAirSplitter
extern CLogger *g_pLogger;

IMPLEMENT_DYNAMIC(COnAirSplitter, CFrameWnd)
COnAirSplitter::COnAirSplitter()
{
	m_strConnect = "";
	m_bStartBlock=FALSE;
	m_qwLineUpLength=0;
}

COnAirSplitter::~COnAirSplitter()
{
}


BEGIN_MESSAGE_MAP(COnAirSplitter, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_COMMAND( CM_CONFIG,OnConfig )
	ON_COMMAND( CM_RESET,OnReset )
	ON_MESSAGE( UM_GETNEXTITEM,OnGetNextItem )
	ON_MESSAGE( UM_SORTPLAYERS,OnSortPlayers )
	ON_MESSAGE( UM_STARTNEXTPLAYER,OnStartNextPlayer)
	ON_MESSAGE( UM_LOGMESSAGE,OnLogItem)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// COnAirSplitter message handlers

int COnAirSplitter::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ReadConfig();

	CDatabase db;

	try{
		m_bEnabled=db.OpenEx("DSN="+m_strConnect,CDatabase::noOdbcDialog);
	} 
	catch( ... ) 
	{
		m_bEnabled=FALSE;
	}

	//if( m_bMixer )
	//	PrepareMixer();

	//if( m_bMixer )
	//	SetLineVolume(1.0f);

	CRect	rect;

	GetClientRect(&rect);
	rect.bottom = rect.top+100;
	rect.right= rect.left+rect.Width()/2-1;
	
	m_pTrafficInfo = new CTrafficInfoWnd;

	if( m_bEnabled )
		m_pTrafficInfo->m_strOnAirConnect = m_strConnect;
	else
		m_pTrafficInfo->m_strOnAirConnect="";

	m_pTrafficInfo->Create(NULL,WS_VISIBLE,rect,this);
	
	rect.OffsetRect(rect.Width(),0);
	m_pProgInfo = new CProgInfoWnd();
	if( m_bEnabled )
		m_pProgInfo->m_strOnAirConnect = m_strConnect;
	else
		m_pProgInfo->m_strOnAirConnect = "";
	m_pProgInfo->Create(NULL,WS_VISIBLE,rect,this);

	rect.bottom-=25;
	rect.OffsetRect(0,102);
	rect.left-=(rect.Width()+1);

	for(int i=0; i<4; i++ )
	{
		m_pPlayer[i] = new COnAirPlayerWnd();
		m_pPlayer[i]->Create(NULL,WS_VISIBLE,rect,this);
		m_pPlayer[i]->EnableWindow(FALSE);
		m_pPlayer[i]->m_wPlayerState = STATE_UNCUED;
		m_pPlayer[i]->m_wPlayerPos = i;

		rect.OffsetRect(0,75);
	}
	
	GetClientRect(&rect);
	rect.DeflateRect(0,406,0,67);

	m_List.Create(WS_VISIBLE|LVS_REPORT,rect,this,1);
	m_List.SetBkColor(RGB(236,244,255));
	m_List.InsertColumn(0,"Data",LVCFMT_LEFT,60);
	m_List.InsertColumn(1,"Hora",LVCFMT_LEFT,60);
	m_List.InsertColumn(2,"Descrição",LVCFMT_LEFT,rect.Width()-220);
	m_List.InsertColumn(3,"Bloco",LVCFMT_LEFT,100);

	//////////////////////////////////////////////////////////////////////////////
	//	ReBar
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);

	TBBUTTON	buttons[9];
	buttons[0].iBitmap=18;
	buttons[0].idCommand=CM_CONFIG;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=22;

	buttons[1].iBitmap=4;
	buttons[1].idCommand=0;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_SEP;
	buttons[1].dwData=0;
	buttons[1].iString=4;

	buttons[2].iBitmap=16;
	buttons[2].idCommand=CM_RESET;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=23;
	
	m_pToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	m_pToolBar->SetButtonSize(size);
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->SetDisabledImageList(g_ilToolEnabled);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(3,buttons);
	m_pToolBar->AutoSize();

	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);

	SetTimer(1,1,NULL);

	return 0;
}

void COnAirSplitter::OnSysCommand(UINT nID, LPARAM lParam)
{
	if( nID!=SC_CLOSE )
		CFrameWnd::OnSysCommand(nID, lParam);
}

void COnAirSplitter::OnNcPaint()
{
	CWindowDC	dc( this );
	CRect		rect;
	

	GetWindowRect(&rect);
	rect.OffsetRect(0-rect.left,0-rect.top);

	dc.Draw3dRect(&rect,GetSysColor(COLOR_ACTIVECAPTION),GetSysColor(COLOR_ACTIVECAPTION)); 
	rect.DeflateRect(1,1,1,1);
	dc.Draw3dRect(&rect,GetSysColor(COLOR_INACTIVECAPTION),GetSysColor(COLOR_INACTIVECAPTION)); }

void COnAirSplitter::OnPaint()
{
	CPaintDC	dc(this); 
	CRect		rect;

	GetClientRect(&rect);
	dc.FillRect(rect,&CBrush(GetSysColor(COLOR_INACTIVECAPTION)));
}

void COnAirSplitter::SplitterMsg( typeSplitterMsg *Msg)
{
	int		nPos = m_List.GetItemCount();
	CString	strTime;
	
	strTime.Format("%d",Msg->lTime);

	switch( Msg->wAction )
	{
	case SP_OPEN:
		//OpenBlock(Msg->strDate,Msg->lTime,Msg->lLength,Msg->wFinish);
		break;
	case SP_PLAY:
		m_lBlockTime = Msg->lTime;
		m_bStartBlock=TRUE;
		// OnSplitterPlayBlock(Msg->lTime);
		break;
	case SP_CUE:
		OnSplitterCueBlock(Msg->strDate,Msg->lTime,Msg->lLength,Msg->wFinish);
		break;
	}
}

void COnAirSplitter::OnSplitterOpenBlock(CString strDate,long lTime,long lLength,WORD wFinish)
{
	int nYear,
		nMonth,
		nDay;

	nYear  = atol(strDate.Mid(0,4));
	nMonth = atol(strDate.Mid(5,2));
	nDay   = atol(strDate.Mid(8,2));

	if( nYear<1900 ) return;
	if( (nMonth>12) || (nMonth<1) ) return;
	if( (nDay>31) || (nDay<1) )	return;

	COleDateTime	dt;
	SYSTEMTIME		st;
	DWORD64			qwTime;
	dt.SetDateTime(nYear,nMonth,nDay,0,0,0);
	dt.GetAsSystemTime(st);
	SystemTimeToFileTime(&st,(LPFILETIME)&qwTime);
	qwTime = qwTime+lTime*10000;

	CRSBlocksDefinition	rsDef(m_strConnect);
	CString				strDays[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

	rsDef.m_strFilter.Format("Time = %d AND %s = 1",lTime,strDays[dt.GetDayOfWeek()-1]);
	rsDef.Open();

	if( rsDef.GetRecordCount() )
	{
		typeLineUpItem	*pBlock = new typeLineUpItem(TYPE_BLOCK,rsDef.m_ID,qwTime,m_strConnect),
						*pItem;
		
		int nPos = 0,
			nPosList;
		CString strTime;

		while( nPos < pBlock->m_iBlockSize )
		{
			nPosList = m_List.GetItemCount();
			pItem = (typeLineUpItem *)pBlock->m_pBlock[nPos];

			GetTimeString(pBlock->m_lBlockTime,&strTime);

			m_List.InsertItem(nPosList,strDate);
			m_List.SetItemText(nPosList,1,strTime);
			m_List.SetItemText(nPosList,2,pItem->m_strName+" - "+pItem->m_strName2);
			m_List.SetItemText(nPosList,3,pBlock->m_strName2);
			m_List.SetItemData(nPosList,(DWORD)pItem);
			nPos++;
		}
		while( (m_List.GetItemCount()) && (m_pPlayer[3]->m_wPlayerState==STATE_UNCUED) )
			m_pPlayer[3]->CmCue();

		delete pBlock;
	}
	rsDef.Close();
}

void COnAirSplitter::OnSplitterCueBlock(CString strDate,long lTime,long lLength,WORD wFinish)
{
	int				nPos = 0,
					nPosList;
	CString			strTime,
					strSQL;
	typeLineUpItem	*pItem;
	CDatabase		db;
	COleDateTime	dt=COleDateTime::GetCurrentTime();

	GetTimeString(lTime,&strTime);
	db.Open(m_strConnect);

	if( m_pTrafficInfo==NULL )
		return;

	if( m_pTrafficInfo->m_pNextBlock==NULL )
		return;

	if( m_pTrafficInfo->m_pNextBlock->m_lBlockTime != lTime )
		return;

	long lTotalLength = m_pTrafficInfo->m_pNextBlock->m_lEndPos;

	if( wFinish==2 ) // wFinish==3
	{
		while( lTotalLength<lLength )
		{
			pItem = GetNextFiller( lLength-lTotalLength );

			if( pItem==NULL )
				break;

			lTotalLength +=pItem->GetTimeToMix();
			nPosList = m_List.GetItemCount();
			pItem->m_bLocked = TRUE;
			pItem->m_lBlockTime = lTime;
			m_List.InsertItem(nPosList,strDate);
			m_List.SetItemText(nPosList,1,strTime);
			m_List.SetItemText(nPosList,2,pItem->m_strName+" - "+pItem->m_strName2);
			m_List.SetItemText(nPosList,3,m_pTrafficInfo->m_pNextBlock->m_strName2);
			m_List.SetItemData(nPosList,(DWORD)pItem);
			
			if( lTotalLength>lLength )
			{
				pItem->m_lMixPos -= ( lTotalLength-lLength );
				pItem->m_lFadeOutPos = pItem->m_lMixPos;
				pItem->m_lEndPos = pItem->m_lMixPos+1500;
			}

			strSQL.Format("UPDATE Instrumentals SET LastDate='%d-%d-%d %d:%d:%d' where TypeID=%d AND ElementID=%d",
				dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond(),
				pItem->m_wType, pItem->m_lItemID );
			db.ExecuteSQL(strSQL);
		}
	}

	while( nPos < m_pTrafficInfo->m_pNextBlock->m_iBlockSize )
	{
		nPosList = m_List.GetItemCount();
		pItem = (typeLineUpItem *)m_pTrafficInfo->m_pNextBlock->m_pBlock[nPos];
		pItem->m_bLocked = TRUE;
		m_List.InsertItem(nPosList,strDate);
		m_List.SetItemText(nPosList,1,strTime);
		m_List.SetItemText(nPosList,2,pItem->m_strName+" - "+pItem->m_strName2);
		m_List.SetItemText(nPosList,3,m_pTrafficInfo->m_pNextBlock->m_strName2);
		m_List.SetItemData(nPosList,(DWORD)pItem);
		nPos++;
	}

	if( wFinish!=2 ) // wFinish==3
	{
		while( lTotalLength<lLength )
		{
			pItem = GetNextFiller( lLength-lTotalLength );

			if( pItem==NULL )
				break;

			lTotalLength +=pItem->GetTimeToMix();
			nPosList = m_List.GetItemCount();
			pItem->m_bLocked = TRUE;
			pItem->m_lBlockTime = lTime;
			m_List.InsertItem(nPosList,strDate);
			m_List.SetItemText(nPosList,1,strTime);
			m_List.SetItemText(nPosList,2,pItem->m_strName+" - "+pItem->m_strName2);
			m_List.SetItemText(nPosList,3,m_pTrafficInfo->m_pNextBlock->m_strName2);
			m_List.SetItemData(nPosList,(DWORD)pItem);
			
			if( lTotalLength>lLength )
			{
				pItem->m_lMixPos -= ( lTotalLength-lLength );
				pItem->m_lFadeOutPos = pItem->m_lMixPos;
				pItem->m_lEndPos = pItem->m_lMixPos+1500;
			}
			strSQL.Format("UPDATE Instrumentals SET LastDate='%d-%d-%d %d:%d:%d' where TypeID=%d AND ElementID=%d",
				dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond(),
				pItem->m_wType, pItem->m_lItemID );
			db.ExecuteSQL(strSQL);
		}
	}

	m_pTrafficInfo->GetNextBlock();
	m_pTrafficInfo->Sync();

	while( (m_List.GetItemCount()) && (m_pPlayer[3]->m_wPlayerState==STATE_UNCUED) )
		m_pPlayer[3]->CmCue();

	db.Close();
}

void COnAirSplitter::OnSplitterPlayBlock( long lTime )
{
	m_bStartBlock=FALSE;

	if( m_pPlayer[0]->m_wPlayerState == STATE_UNCUED )
		return;

	if( m_pPlayer[0]->m_wPlayerState == STATE_PLAYING )
	{
	}
	else
	{
		if( m_pPlayer[0]->m_lpItem->m_lBlockTime==lTime )
		{
			m_pMixer->LineFadeOut();
			m_pPlayer[0]->CmPlay();
		}
	} 
}

LRESULT COnAirSplitter::OnGetNextItem(WPARAM,LPARAM)
{
	if( m_List.GetItemCount()==0)
		return 0;

	typeLineUpItem* lpResult;
	typeLineUpItem* lpItem=(typeLineUpItem*)m_List.GetItemData(0);

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
//		m_pList->SetItemHeight(0,30*(lpItem->m_iBlockSize-lpItem->m_iNextItem+1));
//		m_pList->Invalidate();

		if( lpItem->m_iNextItem>=lpItem->m_iBlockSize )
		{
			m_List.DeleteItem(0);
			delete lpItem;
		}
	}
	else
	{
		if( m_pTrafficInfo!=NULL )
		if( (m_pTrafficInfo->m_pNextBlock!=NULL) && (!lpItem->m_bLocked) )
		{
			FILETIME	ft;
			DWORD64		qwTime;

			GetSystemTimeAsFileTime(&ft);
			FileTimeToLocalFileTime(&ft,(LPFILETIME)&qwTime);
			qwTime += GetPlayersTime();

			if( qwTime>=(m_pTrafficInfo->m_pNextBlock->m_qwStartTime-30000000) )
			{
				m_List.InsertItem(0,"Bloco");
				m_List.SetItemData(0,(DWORD)m_pTrafficInfo->m_pNextBlock);

				if( (m_pTrafficInfo->m_pNextBlock->m_wPrecision!=3) && (qwTime>m_pTrafficInfo->m_pNextBlock->m_qwStartTime) )
					CutOnPlayer( (long)((qwTime-m_pTrafficInfo->m_pNextBlock->m_qwStartTime)/10000));

				m_pTrafficInfo->GetNextBlockThread( (LPVOID)m_pTrafficInfo );

				return OnGetNextItem();
			}
			else // Check for instrumental replacement
			{
			/*	if( (g_iInstrumental>0) && (g_wAutomationMode!=2374) && (lpItem->m_wType == TYPE_MUSIC) && (g_wndTrafficInfo->m_pNextBlock->m_wPrecision != 3) )
				{
					if( (lpItem->GetLength()>g_iInstrumental*1000) && (g_wndTrafficInfo->m_pNextBlock->m_qwStartTime-qwTime<(DWORD64)g_iInstrumental*10000000) )
					{
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

										return lpResult;
									}
									else
										SAFE_DELETE( lpResult);
								}
							}	
						}
					}
				}
			*/
			}
		}

		lpResult=lpItem;
		m_List.DeleteItem(0);
	}
 
	OnCalcStartingTimes(); 

	return (LRESULT)lpResult;
}

LRESULT COnAirSplitter::OnCalcStartingTimes(WPARAM,LPARAM)
{
	long int nItems=m_List.GetItemCount();
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
		lpItem=(typeLineUpItem*)m_List.GetItemData(nCont);
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

		nCont++;
	}
//	tbAlinhamento->Crono->qwLineup=qwLineup;
//	m_pList->Invalidate(FALSE);

	return 0;
}

DWORD64 COnAirSplitter::GetPlayersTime()
{
	return 0;
}
void COnAirSplitter::CutOnPlayer( long lTime )
{
}

LRESULT COnAirSplitter::OnSortPlayers(WPARAM wPlayer, LPARAM wAction)
{
	int Cont;
	COnAirPlayerWnd* wndTemp;
	CRect Rect1,Rect2,Rect3;
	GetWindowRect(&Rect3);

	switch( wAction )
	{
	case SORT_CUE:
		for( Cont=wPlayer; Cont>0; Cont-- )
		{
			if( m_pPlayer[Cont-1]->m_wPlayerState==STATE_UNCUED )
			{
				wndTemp=m_pPlayer[Cont];
				m_pPlayer[Cont]=m_pPlayer[Cont-1];	
				m_pPlayer[Cont-1]=wndTemp;

				m_pPlayer[Cont-1]->GetWindowRect(&Rect2);
				m_pPlayer[Cont]->GetWindowRect(&Rect1);

				Rect1.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));
				Rect2.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));

				m_pPlayer[Cont-1]->MoveWindow(&Rect1,FALSE);
				m_pPlayer[Cont-1]->m_wPlayerPos--;
				m_pPlayer[Cont-1]->Invalidate(FALSE);

				m_pPlayer[Cont]->MoveWindow(&Rect2,FALSE);
				m_pPlayer[Cont]->m_wPlayerPos++;
				m_pPlayer[Cont]->Invalidate(FALSE);
			}
		}
		break;
	case SORT_PLAY:
		for( Cont=wPlayer; Cont>0; Cont-- )
		{
			if( m_pPlayer[Cont-1]->m_wPlayerState!=STATE_PLAYING )
			{
				wndTemp=m_pPlayer[Cont];
				m_pPlayer[Cont]=m_pPlayer[Cont-1];	
				m_pPlayer[Cont-1]=wndTemp;

				m_pPlayer[Cont-1]->GetWindowRect(&Rect2);
				m_pPlayer[Cont]->GetWindowRect(&Rect1);

				Rect1.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));
				Rect2.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));

				m_pPlayer[Cont-1]->MoveWindow(&Rect1,FALSE);
				m_pPlayer[Cont-1]->m_wPlayerPos--;
				m_pPlayer[Cont-1]->Invalidate(FALSE);

				m_pPlayer[Cont]->MoveWindow(&Rect2,FALSE);
				m_pPlayer[Cont]->m_wPlayerPos++;
				m_pPlayer[Cont]->Invalidate(FALSE);
			}
		}
		break;
	case SORT_UNCUE:
		for( Cont=wPlayer; Cont<3; Cont++ )
		{
			if( m_pPlayer[Cont+1]->m_wPlayerState!=STATE_UNCUED )
			{
				wndTemp=m_pPlayer[Cont];
				m_pPlayer[Cont]=m_pPlayer[Cont+1];	
				m_pPlayer[Cont+1]=wndTemp;

				m_pPlayer[Cont+1]->GetWindowRect(&Rect2);
				m_pPlayer[Cont]->GetWindowRect(&Rect1);

				Rect1.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));
				Rect2.OffsetRect(-(Rect3.left+2),-(Rect3.top+2));

				m_pPlayer[Cont+1]->MoveWindow(&Rect1,FALSE);
				m_pPlayer[Cont+1]->m_wPlayerPos++;
				m_pPlayer[Cont+1]->Invalidate(FALSE);

				m_pPlayer[Cont]->MoveWindow(&Rect2,FALSE);
				m_pPlayer[Cont]->m_wPlayerPos--;
				m_pPlayer[Cont]->Invalidate(FALSE);
			}
		}
		break;
	}

//	ResetTimers();
//	LogPlayers();

	return 0;
}

LRESULT COnAirSplitter::OnStartNextPlayer(WPARAM w,LPARAM)
{
	BOOL bStarted = FALSE;

	for( int Cont=w; Cont<4; Cont++ )
	{
		if( m_pPlayer[Cont]->m_wPlayerState==STATE_CUED )
		{
			m_pPlayer[Cont]->CmPlay();
			bStarted=TRUE;
			break;
		}
	}
	if( !bStarted )
		m_pMixer->LineFadeIn();

	return 0;
}

typeLineUpItem *COnAirSplitter::GetNextFiller( long lLength )
{
	typeLineUpItem			*pResult=NULL;
	CString					strSQL;
	CRSViewInstrumentals	rsInst( m_strConnect);


//						strSQL.Format("SELECT [ID],[TypeID],[ElementID],[LastDate],[Title],[Artist],abs([length]-%d) AS [Length],[Rythm] FROM ViewInstrumentals",
//										(g_wndTrafficInfo->m_pNextBlock->m_qwStartTime-qwTime)/10000 );

	strSQL.Format("abs(Length-%d)<1000",lLength);

	rsInst.m_strSort = "Length, LastDate";
	rsInst.m_strFilter = strSQL;
	rsInst.Open();

	if( rsInst.GetRecordCount()!=0 )
	{
		do {
			pResult = new typeLineUpItem((WORD)rsInst.m_TypeID,rsInst.m_ElementID);
			rsInst.MoveNext();
		} while( (pResult->m_bItemIsValid) && (!rsInst.IsEOF()) );
		
		if( !pResult->m_bItemIsValid ) 
			SAFE_DELETE( pResult );
	}

	if( pResult!=NULL )
		return pResult;

	rsInst.m_strFilter.Format("Length < %d",lLength);
	rsInst.m_strSort = "LastDate";
	rsInst.Requery();
							
	if( rsInst.GetRecordCount()!=0 )
	{
		do {
			pResult = new typeLineUpItem((WORD)rsInst.m_TypeID,rsInst.m_ElementID);
			rsInst.MoveNext();
		} while( (!pResult->m_bItemIsValid) && (!rsInst.IsEOF()) );

		if( !pResult->m_bItemIsValid )
			SAFE_DELETE(pResult);
	}							
	
	if( pResult!=NULL )
		return pResult;

	rsInst.m_strFilter.Format("Length < %d",lLength);
	rsInst.m_strSort = "LastDate";
	rsInst.Requery();
							
	if( rsInst.GetRecordCount()!=0 )
	{
		do {
			pResult = new typeLineUpItem((WORD)rsInst.m_TypeID,rsInst.m_ElementID);
			rsInst.MoveNext();
		} while( (!pResult->m_bItemIsValid) && (!rsInst.IsEOF()) );

		if( !pResult->m_bItemIsValid )
			SAFE_DELETE(pResult);
	}

	rsInst.m_strFilter.Format("Length > %d",lLength);
	rsInst.m_strSort = "Length";
	rsInst.Requery();
							
	if( rsInst.GetRecordCount()!=0 )
	{
		do {
			pResult = new typeLineUpItem((WORD)rsInst.m_TypeID,rsInst.m_ElementID);
			rsInst.MoveNext();
		} while( (!pResult->m_bItemIsValid) && (!rsInst.IsEOF()) );

		if( !pResult->m_bItemIsValid )
			SAFE_DELETE(pResult);
	}

	return pResult;
}

LRESULT COnAirSplitter::OnLogItem(WPARAM wParam,LPARAM lParam)
{
	typeLogItem *pItem = (typeLogItem *)lParam;
	pItem->dateTime = COleDateTime::GetCurrentTime();
	g_pLogger->AddItem(pItem);

	//AfxBeginThread(LogItemThread,(LPVOID)lParam);

	return 0;
}

UINT COnAirSplitter::LogItemThread(LPVOID pData)
{
	//typeLogItem *lpItem = (typeLogItem *)pData;
	//CString strSQL,
	//		strDate,
	//		strTemp;
	//COleDateTime date=COleDateTime::GetCurrentTime();
	//CDatabase	db;

	//db.Open( ((COnAirSplitter *)lpItem->lp)->m_strConnect);

	//strDate.Format("%d-%d-%d %d:%d:%d",date.GetYear(),date.GetMonth(),date.GetDay(),date.GetHour(),date.GetMinute(),date.GetSecond());

	//if( lpItem->lID != 0 )
	//{
	//	strSQL.Format("INSERT INTO OnAirLog ([Date],[ComputerID],[UserID],[ItemID],[ItemType]) VALUES ('%s','%d','%d','%d','%d')",
	//		strDate,g_lComputerID,g_lUserID,lpItem->lID,lpItem->wType);
	//	try
	//	{
	//		db.ExecuteSQL(strSQL);
	//	}
	//	catch(...)
	//	{
	//	}
	//}

	///////////////////////////////////////////////////////////////////////////////////////
	//strTemp = lpItem->strName;
	//strTemp.Replace("'","''");

	//
	//strSQL.Format("INSERT INTO OnAirTextLog ([Date],[Log]) VALUES ('%s','%s')",strDate,strTemp);
	//try
	//{
	//	db.ExecuteSQL(strSQL);
	//}
	//catch(...)
	//{
	//}

	///////////////////////////////////////////////////////////////////////////////////////
	//if( lpItem->lTraffic )
	//{
	//	strSQL.Format("UPDATE Traffic SET Aired = 1, AiringDate = '%s', TalentID='%d' WHERE ID = '%d'",
	//		strDate,g_lUserID,lpItem->lTraffic);
	//	try
	//	{
	//		db.ExecuteSQL(strSQL);
	//	}
	//	catch(...)
	//	{
	//	}
	//}
	//else if( lpItem->wType==TYPE_SPOT )
	//{
	//	strSQL.Format("INSERT INTO Traffic (Aired,AiringDate,TalentID,SpotID) VALUES ('1','%s',%d,%d)",
	//		strDate,g_lUserID,lpItem->lID);
	//	try
	//	{
	//		db.ExecuteSQL(strSQL);
	//	}
	//	catch(...)
	//	{
	//	}
	//}
	//
	//delete lpItem;

	return 0;
}

void COnAirSplitter::OnConfig()
{
	CSplitterConfigDlg	dlg;
	CString strSplitter;

	strSplitter.Format("%d",m_wNSplitter);
	
	if( dlg.DoModal()==IDOK )
	{
		CWinApp	*pApp = AfxGetApp();
		
		pApp->WriteProfileString(strSplitter,"RadioName",dlg.m_strRadioName);
		pApp->WriteProfileString(strSplitter,"DSN",dlg.m_strConnect);
		pApp->WriteProfileString(strSplitter,"AudioOut",dlg.m_strAudioOut);
		pApp->WriteProfileInt(strSplitter,"MixerControl",dlg.m_bLine);
		pApp->WriteProfileInt(strSplitter,"MixerID",dlg.m_Mixer.dwMixerID);
		pApp->WriteProfileInt(strSplitter,"LineID",dlg.m_Mixer.dwLineID);
	}
}

void COnAirSplitter::ReadConfig(void)
{
	CString strSplitter;
    CWinApp	*pApp = AfxGetApp();

	strSplitter.Format("%d",m_wNSplitter);

	m_strRadio = pApp->GetProfileString(strSplitter,"RadioName");
	m_strConnect = pApp->GetProfileString(strSplitter,"DSN");
	m_strAudio = pApp->GetProfileString(strSplitter,"AudioOut");

	bool bMixer = pApp->GetProfileInt(strSplitter,"MixerControl",0);
	DWORD dwMixerID = pApp->GetProfileInt(strSplitter,"MixerID",0);
	DWORD dwLineID = pApp->GetProfileInt(strSplitter,"LineID",0);
}

//void COnAirSplitter::PrepareMixer(void)
//{
//	MMRESULT mResult;
//
//	mResult=mixerOpen(&m_hMixer,m_dwMixerID,(DWORD)m_hWnd,NULL,MIXER_OBJECTF_MIXER|CALLBACK_WINDOW);
//	if( mResult!=MMSYSERR_NOERROR )
//	{
//		AfxMessageBox("Não foi possivel abrir o mixer!");
//		m_bMixer=FALSE;
//		m_hMixer=NULL;
//		return;
//	}
//
//	mResult=mixerGetDevCaps(m_dwMixerID,&m_MixerCaps,sizeof(MIXERCAPS));
//	if( mResult!=MMSYSERR_NOERROR )
//	{
//		AfxMessageBox("Não foi possivel obter a descrição do Mixer!");
//		m_bMixer=FALSE;
//		mixerClose(m_hMixer);
//		m_hMixer=FALSE;
//		return;
//	}
//
//	m_MixerLine.cbStruct=sizeof(MIXERLINE);
//	m_MixerLine.dwLineID=m_dwLineID;
//
//	mResult = mixerGetLineInfo((HMIXEROBJ)m_hMixer,&m_MixerLine,MIXER_GETLINEINFOF_LINEID|MIXER_OBJECTF_HMIXER);
//	if( mResult!=MMSYSERR_NOERROR )
//	{
//		AfxMessageBox("Não foi possivel obter a informação da linha do mixer!");
//		m_bMixer=FALSE;
//		mixerClose(m_hMixer);
//		m_hMixer=FALSE;
//		return;
//	}
//
//	m_MixerLineControls.cbStruct=sizeof(MIXERLINECONTROLS);
//	m_MixerLineControls.dwLineID=m_dwLineID;
//	m_MixerLineControls.dwControlType=MIXERCONTROL_CONTROLTYPE_VOLUME;
//	m_MixerLineControls.cControls=1;
//	m_MixerLineControls.cbmxctrl=sizeof(MIXERCONTROL);
//	m_MixerLineControls.pamxctrl=&m_MixerControl;
//
//	mResult = mixerGetLineControls((HMIXEROBJ)m_hMixer,&m_MixerLineControls,MIXER_GETLINECONTROLSF_ONEBYTYPE|MIXER_OBJECTF_HMIXER);
//	if( mResult!=MMSYSERR_NOERROR )
//	{
//		AfxMessageBox("Não foi possivel obter o controle de volume para a linha do mixer!");
//		m_bMixer=FALSE;
//		mixerClose(m_hMixer);
//		m_hMixer=FALSE;
//		return;
//	}
//
//	m_MixerControlDetails.cbStruct=sizeof(MIXERCONTROLDETAILS);
//	m_MixerControlDetails.dwControlID=m_MixerControl.dwControlID;
//	m_MixerControlDetails.cChannels=m_MixerLine.cChannels;
//	m_MixerControlDetails.cMultipleItems=0;
//	m_MixerControlDetails.cbDetails=sizeof(MIXERCONTROLDETAILS_UNSIGNED);
//	m_MixerControlDetails.paDetails=&m_MixerDetails;
//
//	mResult = mixerGetControlDetails((HMIXEROBJ)m_hMixer,&m_MixerControlDetails,MIXER_GETCONTROLDETAILSF_VALUE|MIXER_OBJECTF_HMIXER);
//}

//void COnAirSplitter::SetLineVolume( float fVol )
//{
//	float newVol = fVol * (float)m_MixerControl.Bounds.dwMaximum;
//
//	m_MixerDetails[0].dwValue=(DWORD)newVol;
//	m_MixerDetails[1].dwValue=(DWORD)newVol;
//	mixerSetControlDetails((HMIXEROBJ)m_hMixer,&m_MixerControlDetails,MIXER_SETCONTROLDETAILSF_VALUE|MIXER_OBJECTF_HMIXER);
//}
	
//void COnAirSplitter::LineFadeIn()
//{
//	AfxBeginThread(LineFadeInThread,(LPVOID)this);
//}

//void COnAirSplitter::LineFadeOut()
//{
//	AfxBeginThread(LineFadeOutThread,(LPVOID)this);
//}

//UINT COnAirSplitter::LineFadeInThread(LPVOID lp)
//{
//	COnAirSplitter	*pWnd = (COnAirSplitter *)lp;
//
//	for( float fVol=0.0f; fVol<=1.0f; fVol+=0.01f )
//	{
//		Sleep(5);
//		pWnd->SetLineVolume(fVol);
//	}
//
//	return 0;
//}

//UINT COnAirSplitter::LineFadeOutThread(LPVOID lp)
//{
//	COnAirSplitter	*pWnd = (COnAirSplitter *)lp;
//
//	for( float fVol=1.0f; fVol>=0.0f; fVol-=0.01f )
//	{
//		Sleep(5);
//		pWnd->SetLineVolume(fVol);
//	}
//
//	return 0;
//}

void COnAirSplitter::OnReset()
{
	if( AfxMessageBox("Tem a certeza que pretente reiniciar?",MB_YESNO)!=IDYES )
		return;

	while( m_pPlayer[0]->m_wPlayerState!=STATE_UNCUED )
	{
		if( m_pPlayer[0]->m_wPlayerState==STATE_PLAYING )
			m_pPlayer[0]->CmStop();
		else
			m_pPlayer[0]->OnUnCue();
	}
	while( m_List.GetItemCount() )
		m_List.DeleteItem(0);

}
void COnAirSplitter::OnTimer(UINT nIDEvent)
{
	if( !m_bEnabled )
		return;

	if( m_bStartBlock )
		OnSplitterPlayBlock(m_lBlockTime);

	CheckProgram();

	/*
	if( m_pPlayer[0]->m_wPlayerState==STATE_UNCUED )
	{
		OnSplitterCueBlock("--:--:--",m_pTrafficInfo->m_pNextBlock->m_lBlockTime,60000,0);
		return;
	}

	if( m_pPlayer[0]->m_wPlayerState==STATE_CUED )
		m_pPlayer[0]->CmPlay();
*/
}

void COnAirSplitter::CheckProgram()
{
	if( m_pProgInfo->m_pNextProg==NULL )
		return;

	FILETIME	ftUTC;
	DWORD64		qwCurTime;

	GetSystemTimeAsFileTime(&ftUTC);
	FileTimeToLocalFileTime(&ftUTC,(LPFILETIME)&qwCurTime);
	
	if( ( qwCurTime + GetPlayersTime() ) > (m_pProgInfo->m_qwStart-50000000) )
	{
		RemoveLeftOvers();
		AddSchedule(m_pProgInfo->m_pNextProg->lID,m_pProgInfo->m_qwMinLength );
		
		for( int i=0; i<4; i ++ )
			if( m_pPlayer[3]->m_wPlayerState==STATE_UNCUED )
				m_pPlayer[3]->CmCue();

		m_pProgInfo->m_qwStartPlaying = m_pProgInfo->m_qwStart;

		m_pProgInfo->GetNextProg();
	}

	if( (m_pProgInfo->m_qwStartPlaying!=0) && ( (qwCurTime+GetPlayersTime()) > m_pProgInfo->m_qwStartPlaying) )
	{
		if( m_pPlayer[0]->m_wPlayerState!=STATE_PLAYING )
			if( m_pPlayer[0]->m_wPlayerState!=STATE_UNCUED )
			{
				m_pMixer->LineFadeOut();
				m_pPlayer[0]->CmPlay();
			}
		m_pProgInfo->m_qwStartPlaying=0;
	} 
}

void COnAirSplitter::AddSchedule(long ID,DWORD64 qwMinLength )
{
	CDatabase db;
	do {
		db.OpenEx("DSN="+m_strConnect,CDatabase::noOdbcDialog);
	} while( !db.IsOpen() );

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

	Pos = m_List.GetSelectionMark();
	if( Pos==-1 )
		qwCurTime += GetTotalLength();
	else
	{
		OnCalcStartingTimes();
		lpItem = (typeLineUpItem *)m_List.GetItemData(Pos);
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
			Pos=m_List.GetItemCount();
			lpItem->m_bLocked = rs.m_Priority;
			m_List.InsertItem(Pos,"");
			m_List.SetItemData(Pos,(DWORD_PTR)lpItem);
			m_List.SetItemText(Pos,2,lpItem->m_strName+" - "+lpItem->m_strName2);
		}
		else
			SAFE_DELETE( lpItem );

		rs.MoveNext();

/*		while (PeekMessage(&msg,m_hWnd,0,0,PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} */
	}
	rs.Close();

	OnCalcStartingTimes();

	if( qwMinLength!=0 )
	{
		int nCount = m_List.GetItemCount();
		for( Pos=0; Pos<nCount; Pos++ )
		{
			lpItem = (typeLineUpItem *)m_List.GetItemData(Pos);
			if( lpItem->m_qwStartTime < qwCurTime+qwMinLength )
				lpItem->m_bCanDelete = FALSE;
		}
	}
}

void COnAirSplitter::RemoveLeftOvers()
{
	typeLineUpItem *lpItem;
	int nCount=m_List.GetItemCount();
	int	nPos=0;
	BOOL bFirstUnlock = FALSE;

	while( nPos<m_List.GetItemCount() )
	{
		lpItem = (typeLineUpItem *)m_List.GetItemData(nPos);

		if( !bFirstUnlock && !lpItem->m_bLocked )
			bFirstUnlock=TRUE;

		if( (lpItem->m_bCanDelete && bFirstUnlock) )
		{
			m_List.DeleteItem(nPos);
			delete lpItem;
		}
		else
			nPos++;
	}
}

DWORD64 COnAirSplitter::GetTotalLength()
{
	return 0;
}