// CalendarRightView.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "CalendarRightView.h"
#include "CopySchedule.h"
#include "..\OnAir\PFLWnd.h"
#include "..\include\RSScheduleHeadline.h"
#include "..\include\RSViewSchedule.h"
#include "..\include\RSViewWorkingSchedule.h"
#include "..\include\RSViewMusicSchedulingSata.h"
#include "..\include\RSViewJinglesSchedulingData.h"
#include "..\include\RSVoiceInsert.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\common\include\defines.h"
#include "..\include\rsjinglesonair.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList	*g_ilTree;
extern CPFLWnd		*g_wndPFL;
extern UINT			g_nFormat;

/////////////////////////////////////////////////////////////////////////////
// CCalendarRightView

IMPLEMENT_DYNCREATE(CCalendarRightView, CListView)

CCalendarRightView::CCalendarRightView()
{
}

CCalendarRightView::~CCalendarRightView()
{
}


BEGIN_MESSAGE_MAP(CCalendarRightView, CListView)
	//{{AFX_MSG_MAP(CCalendarRightView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarRightView drawing

void CCalendarRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarRightView diagnostics

#ifdef _DEBUG
void CCalendarRightView::AssertValid() const
{
	CListView::AssertValid();
}

void CCalendarRightView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCalendarRightView message handlers

int CCalendarRightView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style|=LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CListView::OnInitialUpdate();
	CListCtrl *pList=&GetListCtrl();

	pList->SetImageList(g_ilTree,LVSIL_SMALL);

	return 0;
}

void CCalendarRightView::SetYear( int year )
{
	int			Cont;
	CString		strTemp;
	CListCtrl	*pList=&GetListCtrl();

	for( Cont=0; Cont<5; Cont++ )
		pList->DeleteColumn(0);

	strTemp.LoadString(IDS_MONTHS);
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,200);
	pList->DeleteAllItems();

	for( Cont=0; Cont<12; Cont++ )
	{
		strTemp.LoadString(IDS_JANUARY+Cont);
		pList->InsertItem(Cont,strTemp,2);
		pList->SetItemData(Cont,0);
	}

	m_Year = year;
	m_Month = 0;
	m_Day = 0;
}

void CCalendarRightView::SetMonth(int year, int month)
{
	int			Cont;
	CString		strTemp,
				strMonth,
				strDay;
	CListCtrl	*pList=&GetListCtrl();
	typeTreeItem *lpItem;

	for( Cont=0; Cont<5; Cont++ )
		pList->DeleteColumn(0);

	strTemp.LoadString(IDS_DAYS);
	pList->DeleteAllItems();
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,200);

	COleDateTime		dt(year,month,1,0,0,0);
	COleDateTimeSpan	ts(1,0,0,0);

	while( dt.GetMonth()==month )
	{
		lpItem = new typeTreeItem;
		lpItem->lID = dt.GetDay();
		lpItem->wType = TYPE_DAY;
		lpItem->clr = COLOR_BLACK;

		strTemp.LoadString(IDS_SUN+dt.GetDayOfWeek()-1);
		strDay.Format("%d, %s",dt.GetDay(),strTemp);
		pList->InsertItem(dt.GetDay()-1,strDay,2);
		pList->SetItemData(dt.GetDay()-1,(DWORD)lpItem);
		dt+=ts;
	}

	m_Year = year;
	m_Month = month;
	m_Day = 0;
}

void CCalendarRightView::SetDay(int year,int month,int day)
{
	int			Cont;
	CString		strTemp,
				str1,
				str2;
	CRect		rect;
	CRSScheduleHeadline rs( m_strConnect );
	CListCtrl			*pList=&GetListCtrl();
	typeTreeItem		*lpItem;

	for( Cont=0; Cont<5; Cont++ )
		pList->DeleteColumn(0);

	pList->GetWindowRect(&rect);
	strTemp.LoadString(IDS_DAYS);
	pList->DeleteAllItems();
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,rect.Width()-1);


	rs.m_strFilter.Format("Date >= '%d-%d-%d' AND Date <= '%d-%d-%d 23:59:59'",
					year,month,day,year,month,day);
	rs.m_strSort="Date";
	
	rs.Open();
	Cont=0;
	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		str1.Format("%2d:%2d:%2d",rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond());
		str2.Format("%2d:%2d:%2d",rs.m_EndingDate.GetHour(),rs.m_EndingDate.GetMinute(),rs.m_EndingDate.GetSecond());
		str1.Replace(" ","0");
		str2.Replace(" ","0");

		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_SCHEDULE;
		lpItem->clr = COLOR_BLACK;

		pList->InsertItem(Cont,str1+" - "+str2+" »» "+rs.m_Name,3);
		pList->SetItemData(Cont,(DWORD)lpItem);
		rs.MoveNext();
		Cont++;
	}
	rs.Close();

	m_Year = year;
	m_Month = month;
	m_Day = day;
}

void CCalendarRightView::SetSchedule(long lID )
{
	CListCtrl	*pList=&GetListCtrl();
	CRect		rect;
	CString		strTemp;
	int			Cont;
	int			iImage;
	typeTreeItem *lpItem;

	for( Cont=0; Cont<5; Cont++ )
		pList->DeleteColumn(0);

	pList->GetWindowRect(&rect);
	strTemp.LoadString(IDS_LINEUP);
	pList->DeleteAllItems();
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,rect.Width()/2-1);

	strTemp.LoadString(IDS_TEMPLATE);
	pList->InsertColumn(2,strTemp,LVCFMT_LEFT,rect.Width()/2-1);

	CDatabase db;
	db.Open(m_strConnect);

	CRSViewSchedule	rs( "",&db );
	rs.m_pDatabase->SetQueryTimeout(300);
	rs.m_strFilter.Format("ScheduleID = %d",lID);
	rs.m_strSort = "ItemOrder";
	rs.Open();

	Cont=0;
	while( !rs.IsEOF() )
	{
		rs.m_Type.TrimRight();
		rs.m_Name.TrimRight();
		rs.m_TemplateName.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->wType = (WORD)rs.m_ItemType;
		lpItem->lID = rs.m_ItemID;

		if( rs.m_Rythm <= g_iSlow )
			lpItem->clr = COLOR_BLACK;
		else if( rs.m_Rythm <= g_iSlowAverage )
			lpItem->clr = COLOR_GREEN;
		else if( rs.m_Rythm <= g_iAverage )
			lpItem->clr = COLOR_RED;
		else
			lpItem->clr = COLOR_BLUE;

		switch( lpItem->wType )
		{
		case TYPE_MUSIC:
			iImage=17;
			break;
		case TYPE_JINGLE:
			iImage=4;
			break;
		case TYPE_SPOT:
			iImage=1;
			break;
		case TYPE_VOICEINSERT:
			iImage=5;
			break;
		case TYPE_TIMESIGNAL:
			iImage=3;
			break;
		case TYPE_RM:
			iImage=9;
			break;
		default:
			iImage=0;
			break;
		}

		pList->InsertItem(Cont,rs.m_Type+" - "+rs.m_Name,iImage);
		pList->SetItemText(Cont,1,rs.m_TemplateName);
		pList->SetItemData(Cont,(DWORD)lpItem);
		
		Cont++;
		rs.MoveNext();
	}
	rs.Close();

}

void CCalendarRightView::OnPFL()
{
	CListCtrl *pList = &GetListCtrl();
	long Pos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1 ) 
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pList->GetItemData(Pos);

	if( lpItem==NULL ) return;

	if( lpItem->wType==TYPE_VOICEINSERT)
		g_wndPFL->SetSound(lpItem->wType,lpItem->lID,m_strConnect);
	else
		g_wndPFL->SetSound(lpItem->wType,lpItem->lID);

	g_wndPFL->RestoreWindow();
}

void CCalendarRightView::OnInfo()
{
	CListCtrl *pList = &GetListCtrl();
	long Pos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1 ) 
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pList->GetItemData(Pos);

	if( lpItem==NULL ) return;

	CString strURL = "";

	switch( lpItem->wType )
	{
	case TYPE_MUSIC:
		strURL.Format("%s/OnAirSong.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,m_strDB);
		break;
	case TYPE_SCHEDULE:
		strURL.Format("%s/ViewSchedule.asp?ID=%d&RadioID=%d",g_strBaseURL,lpItem->lID,m_lRadioID);
		break;
	case TYPE_DAY:
		strURL.Format("%s/ViewDaySchedule.asp?Date=%d-%d-%d&RadioID=%d",
			g_strBaseURL,
			m_Year,
			m_Month,
			lpItem->lID,
			m_lRadioID );
		break;
	}

	if( strURL!="" )
		g_wndInfo->SetView(strURL);
}

void CCalendarRightView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW*	pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl*		pList = &GetListCtrl();

	typeTreeItem *lpItem=(typeTreeItem *)pList->GetItemData(pNMListView->iItem);

	if( lpItem==NULL )
		return;

	COleDateTime dt;
	if( lpItem->wType == TYPE_DAY )
	{
		dt = COleDateTime(m_Year,m_Month,lpItem->lID,0,0,0);
	}
	else
		dt = COleDateTime(m_Year,m_Month,m_Day,0,0,0);

	HANDLE		hData=::GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,sizeof(typeTreeDrag));
	typeTreeDrag	*lpItemDrag=(typeTreeDrag *)::GlobalLock(hData);
	CString		strTemp = pList->GetItemText(pNMListView->iItem,0);
	lpItemDrag->Item.lID=lpItem->lID;
	lpItemDrag->Item.wType=lpItem->wType;
	lpItemDrag->lpData = &dt;

	strcpy(lpItemDrag->strName,strTemp);
	
	m_OldPoint.x=m_OldPoint.y=-23000; 
	
	COleDataSource DataSource;
	
	DataSource.CacheGlobalData(g_nFormat,hData);
	long result=DataSource.DoDragDrop();

//	if( result==DROPEFFECT_MOVE)
//		OnDragMove();
	
	*pResult = 0;
}

void CCalendarRightView::GenerateSchedule( typeCopySchedule *lpData )
{
	int		Pos = 0,
			Cont;
	CString sqlData,
			strSQL,
			strDate,
			strScheduleName;
	BOOL	bInsert;

	CDatabase db;
	db.Open(m_strConnect);
	db.SetQueryTimeout(300);

	CRSViewMusicSchedulingSata		rsMusic( "",&db );
	CRSViewJinglesSchedulingData	rsJingle( m_strConnect );
	CRSViewWorkingSchedule			rs( "",&db );
	CRSVoiceInsert					rsVoice( m_strConnect );
	CRSScheduleHeadline				rsHead( m_strConnect );

	// Get the schedule name
	rsHead.m_strFilter.Format("ID = '%d'",lpData->lScheduleID );
	rsHead.Open();
	if( rsHead.GetRecordCount()==0 )
		return;

	strScheduleName = rsHead.m_Name;
	strScheduleName.TrimRight();
	rsHead.Close();

	// Opens the schedule recordset
	rs.m_strFilter.Format("ScheduleID = %d",lpData->lTemplateID);
	rs.m_strSort="ItemOrder";
	rs.Open();

	rsMusic.m_strSort = "MaxMusicDate";

	COleDateTime	temp,
					temp2;
	COleDateTimeSpan ts;
	long	lItemType,
			lItemID,
			lArtistID;
	int		nRandLimit=0;
	int		iTake = 0,
			iMinPos,iMaxPos;
	COLORREF clr;
	CRect	rect;
	CString	strTemp;
	
	CListCtrl	*pList = &GetListCtrl();

	pList->DeleteAllItems();

	for( Cont=0; Cont<5; Cont++ )
		pList->DeleteColumn(0);

	pList->GetWindowRect(&rect);
	strTemp.LoadString(IDS_LINEUP);
	pList->DeleteAllItems();
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,rect.Width()/2-1);

	strTemp.LoadString(IDS_TEMPLATE);
	pList->InsertColumn(2,strTemp,LVCFMT_LEFT,rect.Width()/2-1);

	srand( (unsigned)time( NULL ) );

	while( !rs.IsEOF() )
	{
		rs.m_strFilter.Format("ScheduleID = %d and ItemOrder >= %d",lpData->lTemplateID,rs.m_ItemOrder);
		rs.Requery();

		if( rs.IsFieldNull(&rs.m_ArtistQuarantine) )
			temp = lpData->dtStart-COleDateTimeSpan(0,2,0,0);
		else
			temp = lpData->dtStart-COleDateTimeSpan(0,rs.m_ArtistQuarantine,0,0);

		if( rs.IsFieldNull(&rs.m_SongQuarantine) )
			temp2 = lpData->dtStart-COleDateTimeSpan(0,2,0,0);
		else
			temp2 = lpData->dtStart-COleDateTimeSpan(0,rs.m_SongQuarantine,0,0);

		sqlData.Format("((MaxArtistDate is null OR MaxArtistDate < '%d-%d-%d %d:%d:%d') AND (MaxMusicDate is null OR MaxMusicDate < '%d-%d-%d %d:%d:%d'))",
			temp.GetYear(),temp.GetMonth(),temp.GetDay(),temp.GetHour(),temp.GetMinute(),temp.GetSecond(),
			temp2.GetYear(),temp2.GetMonth(),temp2.GetDay(),temp2.GetHour(),temp2.GetMinute(),temp2.GetSecond() );

		bInsert=FALSE;
		clr = COLOR_BLACK;

		if( (rs.m_ItemType==TYPE_MUSIC) && (lpData->bMusic) )
		{
			if( lpData->bNewMusic )
			{
				rsMusic.m_strFilter=rs.m_strSQL;
				rsMusic.m_strSort = "MaxMusicDate";

				if( rsMusic.m_strFilter.GetLength()==0 )
					rsMusic.m_strFilter = sqlData;
				else
					rsMusic.m_strFilter+=(" AND "+sqlData);
				if( rsMusic.IsOpen() )
					rsMusic.Requery();
				else
				{
					rsMusic.Open();
				}

				if( rsMusic.GetRecordCount()==0 )
				{
					rsMusic.m_strFilter=rs.m_strSQL;
					rsMusic.m_strSort = "MaxArtistDate, MaxMusicDate";
					rsMusic.Requery();
					if( rsMusic.GetRecordCount()!=0 )
					{
						ts=COleDateTimeSpan(0,0,3,0);
						bInsert=TRUE;
						lArtistID = rsMusic.m_ArtistID;
						lItemID = rsMusic.m_TrackID;
						lItemType = TYPE_MUSIC;

						if( rsMusic.m_TrackRythm <= g_iSlow )
							clr = COLOR_BLACK;
						else if( rsMusic.m_TrackRythm <= g_iSlowAverage )
							clr = COLOR_GREEN;
						else if( rsMusic.m_TrackRythm <= g_iAverage )
							clr = COLOR_RED;
						else
							clr = COLOR_BLUE;

						rsMusic.m_ArtistName.TrimRight();
						rsMusic.m_TrackTitle.TrimRight();

						pList->InsertItem(Pos,rsMusic.m_ArtistName+" - "+rsMusic.m_TrackTitle,17);
						lpData->dtStart+=COleDateTimeSpan(0,0,3,0);

						typeTreeItem *lpTreeItem = new typeTreeItem;
						lpTreeItem->lID = 0;
						lpTreeItem->wType = 0;
						lpTreeItem->clr = clr;
						pList->SetItemData(Pos,(DWORD)lpTreeItem);
						pList->SetItemText(Pos,2,rs.m_Name);

						strSQL.Format("UPDATE SchedulingTemplate SET LastPos='0' WHERE ID='%d'",rs.m_TemplateID);
						db.ExecuteSQL(strSQL);
					}
				}
				else
				{
					int	nTries = 0;
					CString strTries;

					if( rs.IsFieldNull(&rs.m_RandomFactor) )
					{
						nRandLimit = RAND_MAX/11;
						nRandLimit = nRandLimit + ((rand()/11));
					}
					else
					{
						nRandLimit = RAND_MAX/11*(rs.m_RandomFactor-1);
						nRandLimit = nRandLimit + ((rand()/11)); //*(12-rs.m_RandomFactor));
					}

					if( rs.IsFieldNull(&rs.m_LastPos) )
					{
						iMinPos=0;
						iMaxPos=0;
					}
					else
					{
						iMinPos = rs.m_LastPos-rs.m_RandomFactor;
						iMaxPos = rs.m_LastPos+rs.m_RandomFactor;
					}

					while( (((nTries>iMinPos) && (nTries<iMaxPos)) || (rand()<nRandLimit)) && (!rsMusic.IsFieldNull(&rsMusic.m_MaxMusicDate)) )
					{
						if( rsMusic.IsEOF() )
						{
							rsMusic.MoveFirst();
						}
						else
							rsMusic.MoveNext();

						nTries++;
					}
					ts=COleDateTimeSpan(0,0,3,0);
					bInsert=TRUE;
					lArtistID = rsMusic.m_ArtistID;
					lItemID = rsMusic.m_TrackID;
					lItemType = TYPE_MUSIC;

					rsMusic.m_ArtistName.TrimRight();
					rsMusic.m_TrackTitle.TrimRight();

					if( rsMusic.m_TrackRythm <= g_iSlow )
						clr = COLOR_BLACK;
					else if( rsMusic.m_TrackRythm <= g_iSlowAverage )
						clr = COLOR_GREEN;
					else if( rsMusic.m_TrackRythm <= g_iAverage )
						clr = COLOR_RED;
					else
						clr = COLOR_BLUE;

					
					if( rsMusic.IsFieldNull(&rsMusic.m_MaxMusicDate) )
						strTries.Format("(*) - ");
					else
						strTries.Format("(%d) - ",nTries);

					pList->InsertItem(Pos,strTries+rsMusic.m_ArtistName+" - "+rsMusic.m_TrackTitle,17);
					
					typeTreeItem *lpTreeItem = new typeTreeItem;
					lpTreeItem->lID = 0;
					lpTreeItem->wType = 0;
					lpTreeItem->clr = clr;
					pList->SetItemData(Pos,(DWORD)lpTreeItem);
					pList->SetItemText(Pos,1,rs.m_Name);

					strSQL.Format("UPDATE SchedulingTemplate SET LastPos='%d' WHERE ID='%d'",nTries,rs.m_TemplateID);
					db.ExecuteSQL(strSQL);
				}
			}
			else
			{
				bInsert=TRUE;
				ts=COleDateTimeSpan(0,0,3,30);

				lArtistID = rs.m_ItemParentID;
				lItemID = rs.m_ItemID;
				lItemType = TYPE_MUSIC;
				pList->InsertItem(Pos," ",17);
			}
		}
		else if( (rs.m_ItemType==TYPE_JINGLE) && (lpData->bJingles) )
		{
			if( lpData->bNewJingles )
			{
				if( rs.m_TemplateID!=0 )
				{
					rsJingle.m_strFilter = rs.m_strSQL;
					rsJingle.m_strSort = "MaxDate";

					if( rsJingle.IsOpen() )
						rsJingle.Requery();
					else
						rsJingle.Open();
					
					if( rsJingle.GetRecordCount()!=0 )
					{
						bInsert = TRUE;
						ts=COleDateTimeSpan(0,0,0,10);

						lArtistID = 0;
						lItemID = rsJingle.m_JingleID;
						lItemType = TYPE_JINGLE;
						pList->InsertItem(Pos,rsJingle.m_Name,4);
					}
				}
				else
				{
					// Verificar se o Jingle está em emissão
					CRSJinglesOnAir rsJ(m_strConnect);
					rsJ.m_strFilter.Format("JingleID = '%d'",rs.m_ItemID);
					rsJ.Open();

					if( rsJ.GetRecordCount()!=0 )
					{
						if( (rsJ.m_StartingDate<=lpData->dtStart) && (rsJ.m_EndingDate>=lpData->dtStart) )
						{
							// Insert the same original jingle
							bInsert=TRUE;
							ts=COleDateTimeSpan(0,0,0,10);
							lpData->dtStart+=ts;

							lArtistID = rs.m_ItemParentID;
							lItemID = rs.m_ItemID;
							lItemType = TYPE_JINGLE;
							pList->InsertItem(Pos," ",4);
						}
					}
					rsJ.Close();
				}
			}
			else
			{
				// Verificar se o Jingle está em emissão
				CRSJinglesOnAir rsJ(m_strConnect);
				rsJ.m_strFilter.Format("JingleID = '%d'",rs.m_ItemID);
				rsJ.Open();

				if( rsJ.GetRecordCount()!=0 )
				{
					if( (rsJ.m_StartingDate<=lpData->dtStart) && (rsJ.m_EndingDate>=lpData->dtStart) )
					{
						// Insert the same original jingle
						bInsert=TRUE;
						ts=COleDateTimeSpan(0,0,0,10);
						lpData->dtStart+=ts;

						lArtistID = rs.m_ItemParentID;
						lItemID = rs.m_ItemID;
						lItemType = TYPE_JINGLE;
						pList->InsertItem(Pos," ",4);
					}
				}
				rsJ.Close();

			}
		}
		else if( (rs.m_ItemType==TYPE_VOICEINSERT) && (lpData->bVoice) )
		{
			if( lpData->bNewVoice )
			{
				// Computes a new voice insert
				rsVoice.m_strFilter.Format("ID = '%d'",rs.m_ItemID);
				if( rsVoice.IsOpen() )
					rsVoice.Requery();
				else
					rsVoice.Open();

				long int	lUserID = rsVoice.m_TalentID;
				long int	lPathID = rsVoice.m_Path;

				CString		strNewTake,
							strTemp;	
				
				do {
					iTake++;
					strNewTake.Format("%s - %s - Take %d",lpData->dtStart.Format("%Y-%m-%d"),strScheduleName,iTake);
					strTemp=strNewTake;
					strTemp.Replace("'","''");
					rsVoice.m_strFilter.Format("FileName = '%s.wav'",strTemp);
					
					rsVoice.Requery();
				} while( rsVoice.GetRecordCount()!=0 );

				// Add the new voice insert
				rsVoice.AddNew();
				rsVoice.m_Activ = 1;
				rsVoice.m_FileName = strNewTake+".wav";
				rsVoice.m_Finish = 0;
				rsVoice.m_Name = strNewTake;
				rsVoice.m_Path = lPathID;
				rsVoice.m_Start = 0;
				rsVoice.m_TalentID = lUserID;
				rsVoice.Update();
				rsVoice.Requery();
	
				// Insert the new voice insert into the schedule
				bInsert=TRUE;
				ts=COleDateTimeSpan(0,0,0,1);

				lArtistID = 0;
				lItemID = rsVoice.m_ID;
				lItemType = TYPE_VOICEINSERT;
				pList->InsertItem(Pos,strNewTake,4);
			}
			else
			{
				// Insert the original voice insert
				bInsert=TRUE;
				ts=COleDateTimeSpan(0,0,0,1);

				lArtistID = rs.m_ItemParentID;
				lItemID = rs.m_ItemID;
				lItemType = TYPE_VOICEINSERT;
				pList->InsertItem(Pos," ",4);
			}
		}
		else if( lpData->bOthers )
		{
			bInsert = TRUE;
			ts=COleDateTimeSpan(0,0,0,10);

			lArtistID = 0;
			lItemID = rs.m_ItemID;
			lItemType = rs.m_ItemType;
			pList->InsertItem(Pos,"",20);
		}

		if( bInsert )
		{
			strDate.Format("%d-%d-%d %d:%d:%d",lpData->dtStart.GetYear(),lpData->dtStart.GetMonth(),lpData->dtStart.GetDay(),lpData->dtStart.GetHour(),lpData->dtStart.GetMinute(),lpData->dtStart.GetSecond() );

			if( lpData->bBlocked )
			{
				strSQL.Format("INSERT INTO Scheduling (Date,ItemOrder,ItemType,ItemID,ItemParentID,ScheduleID,Priority,TemplateID) VALUES ('%s',%d,%d,%d,%d,%d,%d,%d)",
					strDate,Pos,lItemType,lItemID,lArtistID,lpData->lScheduleID,rs.m_Priority,rs.m_TemplateID,1);
			}
			else
			{
				strSQL.Format("INSERT INTO Scheduling (Date,ItemOrder,ItemType,ItemID,ItemParentID,ScheduleID,Priority,TemplateID) VALUES ('%s',%d,%d,%d,%d,%d,%d,%d)",
								strDate,Pos,lItemType,lItemID,lArtistID,lpData->lScheduleID,0,rs.m_TemplateID);
			}
			db.ExecuteSQL(strSQL);

			if( (lItemType!=TYPE_VOICEINSERT) && (lpData->nRadios!=0) )
			{
				for( int N=0; N<lpData->nRadios; N++ )
				{
					strSQL.Format("INSERT INTO [%s].dbo.Scheduling (Date,ItemOrder,ItemType,ItemID,ItemParentID,ScheduleID,Priority,TemplateID) VALUES ('%s',%d,%d,%d,%d,%d,%d,%d)",
						lpData->tRadios[N].strDBName,
						strDate,Pos,lItemType,lItemID,lArtistID,lpData->tRadios[N].lScheduleID,0,0);
					db.ExecuteSQL(strSQL);
				}
			}
			pList->EnsureVisible(Pos,FALSE);

			Pos++;
			lpData->dtStart+=ts;
		}
		rs.MoveNext();

	}

	rs.Close();
	db.Close();

//	AfxMessageBox("Teste");
	SetSchedule(lpData->lScheduleID);
}

UINT CCalendarRightView::GenerateScheduleThread( LPVOID lp )
{

	typeCopySchedule *lpData = (typeCopySchedule *)lp;
	CCalendarRightView *pView=(CCalendarRightView *)lpData->wndView;

	pView->m_bWorking=TRUE;
	pView->GetParent()->EnableWindow(FALSE);
	pView->GenerateSchedule(lpData);
	pView->GetParent()->EnableWindow(TRUE);
	pView->m_bWorking=FALSE;

	return 0;
}
void CCalendarRightView::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CCalendarRightView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnPFL();	
	*pResult = 0;
}


void CCalendarRightView::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW *nmCD=(NMLVCUSTOMDRAW *)pNMHDR;
	typeTreeItem *lpItem=(typeTreeItem *)nmCD->nmcd.lItemlParam;

	switch( nmCD->nmcd.dwDrawStage )
	{
	case CDDS_PREPAINT:
		*pResult=CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		if( lpItem )
		{
			switch( lpItem->wType)
			{
			case TYPE_BLOCK:
				nmCD->clrTextBk=RGB(241,175,162);
				nmCD->clrText=RGB(0,0,0);
				break;
			case TYPE_JINGLE:
				nmCD->clrTextBk=RGB(241,239,162);
				nmCD->clrText = lpItem->clr;
				break;
			case TYPE_SPOT:
				nmCD->clrTextBk=RGB(177,239,162);
				break;
			case TYPE_RM:
				nmCD->clrTextBk=RGB(241,175,226);
				break;
			case TYPE_VOICEINSERT:
				nmCD->clrTextBk=RGB(177,239,226);
				break;
			case TYPE_TIMESIGNAL:
				nmCD->clrTextBk=RGB(177,239,255);
				break;
			default:
				nmCD->clrTextBk=RGB(255,255,255);
				nmCD->clrText = lpItem->clr;
				break;
			}
		}
		*pResult=CDRF_NEWFONT;
		break;
	default:
		*pResult=CDRF_DODEFAULT;
		break;
	}
}
