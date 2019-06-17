// CalendarLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "CalendarLeftView.h"
#include "Schedule.h"
#include "SchedulerDoc.h"
#include "CopySchedule.h"
#include "DaysDlg.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\include\RSViewMinMaxScheduleYear.H"
#include "..\include\RSScheduleHeadline.h"
#include "..\include\RSSchedule.h"
#include "..\include\rsradiostations.h"
#include "..\common\include\global.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CSchedulerApp	theApp;
extern  UINT			g_nFormat;
/////////////////////////////////////////////////////////////////////////////
// CCalendarLeftView

IMPLEMENT_DYNCREATE(CCalendarLeftView, CDigitalLeftView)

CCalendarLeftView::CCalendarLeftView()
{
}

CCalendarLeftView::~CCalendarLeftView()
{
}


BEGIN_MESSAGE_MAP(CCalendarLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CCalendarLeftView)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarLeftView drawing

void CCalendarLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarLeftView diagnostics

#ifdef _DEBUG
void CCalendarLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CCalendarLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCalendarLeftView message handlers

void CCalendarLeftView::OnInitialUpdate() 
{
	m_pDocument->SetTitle("");
	CDigitalLeftView::OnInitialUpdate();
	
	COleDateTime	date,
					maxDate;
	COleDateTime	odt=COleDateTime::GetCurrentTime();
	COleDateTimeSpan timespan(1,0,0,0);	
	
	CRSViewMinMaxScheduleYear rs( m_strConnect );
	rs.Open();

	if( rs.GetRecordCount()!=0 )
	{
		date.SetDateTime(rs.m_Min-1,1,1,0,0,0);
		maxDate.SetDateTime(rs.m_Max+1,12,31,0,0,0);
	}
	else
	{
		date.SetDateTime( odt.GetYear()-1,1,1,0,0,0);
		maxDate.SetDateTime(odt.GetYear()+1,12,31,0,0,0);
	}

	CTreeCtrl		*pTree=&GetTreeCtrl();	

	HTREEITEM		hYear,
					hMonth,
					hDay,
					hCurDay;
	CString			strTemp,
					strTemp2;
	typeTreeItem	*lpItem;
	int				iYear=0,iMonth=0;
	
	while( date < maxDate )
	{
		if( date.GetYear()!=iYear )
		{
			// Insert new year
			iYear = date.GetYear();
			strTemp.Format("%d",iYear);

			lpItem = new typeTreeItem;
			lpItem->lID=iYear;
			lpItem->wType=TYPE_YEAR;
			
			hYear=pTree->InsertItem(strTemp,2,2);
			pTree->SetItemData(hYear,(DWORD)lpItem);
			if( iYear==odt.GetYear() )
				pTree->SetItemState(hYear,TVIS_BOLD,TVIS_BOLD);
		}

		if( date.GetMonth()!=iMonth )
		{
			// New Month
			iMonth=date.GetMonth();
			strTemp.LoadString(IDS_JANUARY+iMonth-1);

			lpItem = new typeTreeItem;
			lpItem->lID=iMonth;
			lpItem->wType=TYPE_MONTH;

			hMonth=pTree->InsertItem(strTemp,2,2,hYear);
			pTree->SetItemData(hMonth,(DWORD)lpItem);
			if( (iYear==odt.GetYear()) && (iMonth==odt.GetMonth()) )
				pTree->SetItemState(hMonth,TVIS_BOLD,TVIS_BOLD);
		}

		strTemp2.LoadString(IDS_SUN-1+date.GetDayOfWeek());
		strTemp.Format("%d, %s",date.GetDay(),strTemp2);

		lpItem = new typeTreeItem;
		lpItem->lID=date.GetDay();
		lpItem->wType=TYPE_DAY;

		hDay=pTree->InsertItem(strTemp,2,2,hMonth);
		pTree->SetItemData(hDay,(DWORD)lpItem );
		if( (iYear==odt.GetYear()) && (iMonth==odt.GetMonth()) && (lpItem->lID==odt.GetDay()) )
		{
			hCurDay=hDay;
			pTree->SetItemState(hDay,TVIS_BOLD,TVIS_BOLD);
		}

		pTree->InsertItem(NULL,3,3,hDay);

		date+=timespan;
	}	
	pTree->EnsureVisible(hCurDay);
	pTree->Select(hCurDay,TVGN_CARET);
}

void CCalendarLeftView::OnExpanding( HTREEITEM hItem )
{

	if( hItem==NULL )
		return;
	
	CTreeCtrl	*pTree = &GetTreeCtrl();
	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType==TYPE_DAY )
	{
		HTREEITEM		hMonth = pTree->GetParentItem(hItem),
						hYear = pTree->GetParentItem(hMonth),
						hNewItem;
		typeTreeItem	*lpMonth = (typeTreeItem *)pTree->GetItemData(hMonth),
						*lpYear = (typeTreeItem *)pTree->GetItemData(hYear),
						*lpNew;

		CRSScheduleHeadline rs( m_strConnect );
		
		CString				str1,str2;

		DeleteAllChildItems(hItem);

		rs.m_strFilter.Format("Date >= '%d-%d-%d' AND Date <= '%d-%d-%d 23:59:59'",
							lpYear->lID,lpMonth->lID,lpItem->lID,
							lpYear->lID,lpMonth->lID,lpItem->lID );
		rs.m_strSort="Date";

	
		rs.Open();
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			str1.Format("%2d:%2d:%2d",rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond());
			str2.Format("%2d:%2d:%2d",rs.m_EndingDate.GetHour(),rs.m_EndingDate.GetMinute(),rs.m_EndingDate.GetSecond());
			str1.Replace(" ","0");
			str2.Replace(" ","0");

			lpNew = new typeTreeItem;
			lpNew->lID = rs.m_ID;
			lpNew->wType = TYPE_SCHEDULE;

			hNewItem = pTree->InsertItem(str1+" - "+str2+" »» "+rs.m_Name,3,3,hItem);
			pTree->SetItemData(hNewItem,(DWORD)lpNew);
			rs.MoveNext();
		}

		rs.Close();

	}
}

void CCalendarLeftView::OnSelChange()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem(),
				hYear,
				hMonth,
				hDay;
	CString		strYear,
				strMonth,
				strDay,
				strSchedule,
				str;

	if( hItem == NULL )
		return;

	typeTreeItem	*lpItem = (typeTreeItem *)pTree->GetItemData(hItem),
					*lpYear,
					*lpMonth;

	if( lpItem == NULL )
		return;

	switch( lpItem->wType )
	{
	case TYPE_YEAR:
		strYear=pTree->GetItemText(hItem);
		m_pDocument->SetTitle(strYear);
		m_pRightView->SetYear(lpItem->lID);
		break;
	case TYPE_MONTH:
		strMonth=pTree->GetItemText(hItem);
		hYear=pTree->GetParentItem(hItem);
		strYear=pTree->GetItemText(hYear);
		lpYear=(typeTreeItem *)pTree->GetItemData(hYear);
		
		m_pDocument->SetTitle(strYear+", "+strMonth);
		m_pRightView->SetMonth(lpYear->lID,lpItem->lID);
		break;
	case TYPE_DAY:
		strDay	= pTree->GetItemText(hItem);
		hMonth	= pTree->GetParentItem(hItem);
		hYear	= pTree->GetParentItem(hMonth);
		lpMonth = (typeTreeItem *)pTree->GetItemData(hMonth);
		lpYear	= (typeTreeItem *)pTree->GetItemData(hYear);
		strMonth= pTree->GetItemText(hMonth);
		strYear = pTree->GetItemText(hYear);

		m_pDocument->SetTitle(strYear+", "+strMonth+" - "+strDay);
		m_pRightView->SetDay(lpYear->lID,lpMonth->lID,lpItem->lID);
		break;
	case TYPE_SCHEDULE:
		hDay	= pTree->GetParentItem(hItem);
		hMonth	= pTree->GetParentItem(hDay);
		hYear	= pTree->GetParentItem(hMonth);
		
		strDay	= pTree->GetItemText(hDay);
		strMonth= pTree->GetItemText(hMonth);
		strYear = pTree->GetItemText(hYear);
		strSchedule = pTree->GetItemText(hItem);
		
		m_pDocument->SetTitle(strYear+", "+strMonth+" - "+strDay+" -- "+strSchedule);
		m_pRightView->SetSchedule(lpItem->lID);
		break;
	}
}

void CCalendarLeftView::OnNew()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem == NULL ) return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

	if( lpItem==NULL ) return;

	if( lpItem->wType != TYPE_DAY ) return;

	HTREEITEM		hMonth = pTree->GetParentItem(hItem),
					hYear = pTree->GetParentItem(hMonth);
	typeTreeItem	*lpYear = (typeTreeItem *)pTree->GetItemData(hYear),
					*lpMonth = (typeTreeItem *)pTree->GetItemData(hMonth),
					*lpDay = lpItem;

	Schedule	dl;
	dl.m_Length.SetTime(1,0,0);
	dl.m_EndingDate = dl.m_StartingTime+COleDateTimeSpan(0,1,0,0);
	dl.m_Year = lpYear->lID;
	dl.m_Month = lpMonth->lID;
	dl.m_Day = lpDay->lID;

	if( dl.DoModal()==IDOK )
	{
		CString	str1,
				str2;
		CRSScheduleHeadline rs( m_strConnect );

		rs.m_strSort="ID DESC";
		rs.Open();

		rs.AddNew();
		rs.m_Date.SetDateTime(dl.m_Year,dl.m_Month,dl.m_Day,dl.m_StartingTime.GetHour(),dl.m_StartingTime.GetMinute(),dl.m_StartingTime.GetSecond() );
		rs.m_EndingDate = rs.m_Date+COleDateTimeSpan(0,dl.m_Length.GetHour(),dl.m_Length.GetMinute(),dl.m_Length.GetSecond() );
		rs.m_Name = dl.m_Name;
		rs.m_Priority = dl.m_Precision;
		rs.m_TemplateID = 0;
		rs.Update();
		rs.Requery();
	
		typeTreeItem *lpNewItem = new typeTreeItem;
		lpNewItem->lID = rs.m_ID;
		lpNewItem->wType = TYPE_SCHEDULE;

		str1.Format("%2d:%2d:%2d",rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond());
		str2.Format("%2d:%2d:%2d",rs.m_EndingDate.GetHour(),rs.m_EndingDate.GetMinute(),rs.m_EndingDate.GetSecond());
		str1.Replace(" ","0");
		str2.Replace(" ","0");

		HTREEITEM hNewItem = pTree->InsertItem(str1+" - "+str2+" »» "+dl.m_Name,3,3,hItem);
		pTree->SetItemData(hNewItem,(DWORD)lpNewItem);
		pTree->SortChildren(hItem);
		m_pRightView->SetDay(lpYear->lID,lpMonth->lID,lpDay->lID);
		
		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_SCHEDULE,lpNewItem->lID,m_lRadioID);

		rs.Close();
	}
}

void CCalendarLeftView::OnEditHeadline()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem == NULL ) return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

	if( lpItem==NULL ) return;

	if( lpItem->wType != TYPE_SCHEDULE ) return;

	CRSScheduleHeadline rs( m_strConnect );

	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		Schedule dl;

		rs.m_Name.TrimRight();

		dl.m_Year = rs.m_Date.GetYear();
		dl.m_Month = rs.m_Date.GetMonth();
		dl.m_Day=rs.m_Date.GetDay();
		dl.m_Length = rs.m_EndingDate-rs.m_Date;
		dl.m_StartingTime = rs.m_Date;
		dl.m_EndingDate = rs.m_EndingDate;
		dl.m_Name = rs.m_Name;
		dl.m_Precision = rs.m_Priority;

		if( dl.DoModal()==IDOK )
		{
			CString str1,
					str2;

			rs.Edit();
			rs.m_Date.SetDateTime(dl.m_Year,dl.m_Month,dl.m_Day,dl.m_StartingTime.GetHour(),dl.m_StartingTime.GetMinute(),dl.m_StartingTime.GetSecond() );
			rs.m_EndingDate = rs.m_Date+COleDateTimeSpan(0,dl.m_Length.GetHour(),dl.m_Length.GetMinute(),dl.m_Length.GetSecond() );
			rs.m_Name = dl.m_Name;
			rs.m_Priority = dl.m_Precision;
			rs.m_TemplateID = 0;

			str1.Format("%2d:%2d:%2d",rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond());
			str2.Format("%2d:%2d:%2d",rs.m_EndingDate.GetHour(),rs.m_EndingDate.GetMinute(),rs.m_EndingDate.GetSecond());
			str1.Replace(" ","0");
			str2.Replace(" ","0");

			rs.Update();

			pTree->SetItemText(hItem,str1+" - "+str2+" »» "+dl.m_Name);
			pTree->SortChildren( pTree->GetParentItem(hItem) );

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_SCHEDULE,lpItem->lID,m_lRadioID);
		}
		
	}
	rs.Close();
}

void CCalendarLeftView::OnEditSchedule()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem == NULL ) return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

	if( lpItem==NULL ) return;

	if( lpItem->wType != TYPE_SCHEDULE ) return;

	CSchedulerDoc *pDoc=(CSchedulerDoc *)theApp.m_pDocSchedule->OpenDocumentFile(NULL);
	pDoc->m_ScheduleID	= lpItem->lID;
	pDoc->m_strConnect	= m_strConnect;
	pDoc->m_strDB		= m_strDB;
	pDoc->m_strRadio	= m_strRadio;

	WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_SCHEDULE,lpItem->lID,m_lRadioID,1);

	pDoc->UpdateAllViews(this);
}

void CCalendarLeftView::OnCut()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem == NULL ) return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

	if( lpItem==NULL ) return;

	if( lpItem->wType != TYPE_SCHEDULE ) return;

	if( AfxMessageBox(IDS_CONFIRMSCHEDULEREMOVE,MB_YESNO)==IDYES )
	{
		CDatabase	db;
		CString		strSQL;

		strSQL.Format("DELETE From SchedulingHeadlines WHERE ID = %d",lpItem->lID );
		db.Open(m_strConnect);
		db.ExecuteSQL(strSQL);

		strSQL.Format("DELETE From Scheduling WHERE ScheduleID = %d",lpItem->lID );
		db.ExecuteSQL(strSQL);

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUT,TYPE_SCHEDULE,lpItem->lID,m_lRadioID);

		pTree->DeleteItem(hItem);
	}
}

void CCalendarLeftView::OnDoubleClick()
{
	if( !g_Permissions.bScheduleEdit && 
			!g_Permissions.bCriteriaAdd && !g_Permissions.bCriteriaCut && !g_Permissions.bCriteriaEdit &&
			!g_Permissions.bVoiceAdd && !g_Permissions.bVoiceCut && !g_Permissions.bVoiceEdit )
		return;

	OnEditSchedule();
}

DROPEFFECT CCalendarLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( (m_lpDragItem->Item.wType != TYPE_SCHEDULE) &&
		(m_lpDragItem->Item.wType != TYPE_DAY) )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	return DROPEFFECT_COPY;
}

void CCalendarLeftView::OnDragLeave() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDigitalLeftView::OnDragLeave();
}

DROPEFFECT CCalendarLeftView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !g_Permissions.bScheduleAuto )
		return DROPEFFECT_NONE ;

	CDigitalLeftView::OnDragOver(pDataObject, dwKeyState, point);

	CTreeCtrl	*pTree=&GetTreeCtrl();
	UINT		uFlags;

	HTREEITEM hItem=pTree->HitTest(point,&uFlags);
	
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
		if( lpItem != NULL )
		{
			if( lpItem->wType == TYPE_DAY )
			{
				HTREEITEM hDrop=pTree->GetDropHilightItem();
				if( hDrop!=hItem )
				{
					DrawDragItem(m_lpDragItem->strName,point);
					pTree->SelectDropTarget(hItem);
					DrawDragItem(m_lpDragItem->strName,point);
				}
		
				if( dwKeyState & MK_SHIFT )
					return DROPEFFECT_MOVE;
				else
					return DROPEFFECT_COPY;
			}
		}
	}

	HTREEITEM hDrop=pTree->GetDropHilightItem();
	if( hDrop!=NULL )
	{
		DrawDragItem(m_lpDragItem->strName,point);
		pTree->SelectDropTarget(NULL);
		DrawDragItem(m_lpDragItem->strName,point);
	}
	return DROPEFFECT_NONE;
}

BOOL CCalendarLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CTreeCtrl	*pTree=&GetTreeCtrl();
	UINT		uFlags;

	HTREEITEM hItem=pTree->HitTest(point,&uFlags);

	if( (hItem == NULL) || !(TVHT_ONITEM & uFlags))
	{
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return DROPEFFECT_NONE;

	if( ((m_lpDragItem->Item.wType==TYPE_SCHEDULE) && (lpItem->wType != TYPE_DAY)) ||
		((m_lpDragItem->Item.wType==TYPE_DAY) && (lpItem->wType != TYPE_DAY)) )
		return DROPEFFECT_NONE;

	if( m_lpDragItem->Item.wType==TYPE_SCHEDULE ) 
		CopySchedule( hItem );

	if( m_lpDragItem->Item.wType==TYPE_DAY )
		if( m_lpDragItem->lpData!=NULL )
		{
			typeCopySchedule *lp = new typeCopySchedule;
			lp->hItem = hItem;
			lp->wndView = this;
			lp->dtStart = *(COleDateTime *)m_lpDragItem->lpData;
			
			AfxBeginThread(CopyDayThread,(LPVOID)lp);
			Sleep(1000);
		}

	pTree->SelectDropTarget(NULL);

	return DROPEFFECT_COPY;
}

UINT CCalendarLeftView::CopyDayThread( LPVOID lp )
{
	typeCopySchedule *lpData = (typeCopySchedule *)lp;
	CCalendarLeftView *pView = (CCalendarLeftView *)lpData->wndView;

	pView->GetParent()->EnableWindow(FALSE);
	pView->CopyDay(lpData);
	pView->GetParent()->EnableWindow(TRUE);

	return 0;
}

void CCalendarLeftView::CopyDay( typeCopySchedule *lpData )
{
	HTREEITEM hDay = (HTREEITEM)lpData->hItem;
	CTreeCtrl*	pTree = &GetTreeCtrl();
	HTREEITEM	hMonth = pTree->GetParentItem(hDay);
	HTREEITEM	hYear = pTree->GetParentItem(hMonth);
	typeTreeItem *lpDay = (typeTreeItem *)pTree->GetItemData(hDay);
	typeTreeItem *lpMonth = (typeTreeItem *)pTree->GetItemData(hMonth);
	typeTreeItem *lpYear = (typeTreeItem *)pTree->GetItemData(hYear);

//	AfxMessageBox("Copy Day 1");

	COleDateTime	*pOriginalDate = &lpData->dtStart,
					Start = COleDateTime(lpYear->lID,lpMonth->lID,lpDay->lID,0,0,0),
					End;
	COleDateTimeSpan	tempDTS;
	CString			strStart,strEnd;
	BOOL			bConflict=FALSE;
	int				nDays = 0;

//	AfxMessageBox("Copy Day 2");

	if( pOriginalDate->GetDayOfWeek()==Start.GetDayOfWeek() )
	{
		CDaysDlg	dlg;

		dlg.m_nDays=7;
		if( dlg.DoModal()!=IDOK )
			return;

		nDays = dlg.m_nDays-1;
	}

//	AfxMessageBox("Copy Day 3");

	End = *pOriginalDate+COleDateTimeSpan(nDays,0,0,0);

	strStart.Format("%d-%d-%d", pOriginalDate->GetYear(),pOriginalDate->GetMonth(),pOriginalDate->GetDay());
	strEnd.Format("%d-%d-%d 23:59:59",End.GetYear(),End.GetMonth(),End.GetDay() );
	
	CRSScheduleHeadline rs( m_strConnect );
	rs.m_strFilter.Format("[Date]>='%s' AND [Date]<='%s'",strStart,strEnd);
	rs.m_strSort="[Date]";
	rs.Open();

//	AfxMessageBox("Copy Day 3\n"+rs.m_strFilter);

	if(  rs.GetRecordCount()==0 )
		return;

	while( !rs.IsEOF() )
	{
		tempDTS = COleDateTime(rs.m_Date.GetYear(),rs.m_Date.GetMonth(),rs.m_Date.GetDay(),0,0,0)-COleDateTime(pOriginalDate->GetYear(),pOriginalDate->GetMonth(),pOriginalDate->GetDay(),0,0,0);
		Start = COleDateTime(lpYear->lID,lpMonth->lID,lpDay->lID,rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond())+tempDTS;
		End = Start+(rs.m_EndingDate-rs.m_Date);

		if( CheckForConflict(Start,End) )
			bConflict=TRUE;
		rs.MoveNext();
	}
	
//	AfxMessageBox("Copy Day 4");

	if( bConflict )
	{
		AfxMessageBox(IDS_SCHEDULECONFLICT);
		return;
	}

	CCopySchedule dl;
//	AfxMessageBox("Copy Day 5");
	if( dl.DoModal()==IDOK )
	{
		long				Priority;
		CString				strName;
		HTREEITEM			hSchedule ;
		CRSScheduleHeadline rsNew( m_strConnect );
		typeCopySchedule	NewSchedule;

		NewSchedule.bJingles = dl.m_bJingles;
		NewSchedule.bMusic = dl.m_bMusic;
		NewSchedule.bNewJingles = dl.m_Data.bNewJingles;
		NewSchedule.bNewMusic = dl.m_Data.bNewMusic;
		NewSchedule.bNewVoice = dl.m_Data.bNewVoice;
		NewSchedule.bOthers = dl.m_bOther;
		NewSchedule.bVoice = dl.m_bVoice;
		NewSchedule.bCopyAll = dl.m_bCopyAll;
		NewSchedule.wndView = this;
		NewSchedule.nRadios = 0;
		NewSchedule.bBlocked = dl.m_bBlocked;

		if( dl.m_bCopyAll )
		{
			CRSRadioStations rsRadios(g_strMainConnect);
			rsRadios.m_strSort="Name";
			rsRadios.Open();

			while( !rsRadios.IsEOF() )
			{
				rsRadios.m_DSN.TrimRight();
				if( rsRadios.m_DSN!=m_strConnect )
				{
					rsRadios.m_DB.TrimRight();
					NewSchedule.tRadios[NewSchedule.nRadios].strDBName=rsRadios.m_DB;
					NewSchedule.tRadios[NewSchedule.nRadios].strDSN=rsRadios.m_DSN;
					NewSchedule.nRadios++;
				}
				rsRadios.MoveNext();
			}
			rsRadios.Close();
		}

		rsNew.Open();
		rs.MoveFirst();

		while( !rs.IsEOF() )
		{
			NewSchedule.lTemplateID = rs.m_ID;
//			NewSchedule.dtStart.SetDateTime(lpYear->lID,lpMonth->lID,lpDay->lID,rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond() );
			NewSchedule.dtStart.SetDateTime(lpYear->lID,lpMonth->lID,lpDay->lID,0,0,0);
			NewSchedule.dtStart += (rs.m_Date-*pOriginalDate );
	
			rs.m_Name.TrimRight();

			strName.Format("A gerar programa '%s' para %d-%d-%d %d:%d:%d",
				rs.m_Name,
				NewSchedule.dtStart.GetYear(),
				NewSchedule.dtStart.GetMonth(),
				NewSchedule.dtStart.GetDay(),
				NewSchedule.dtStart.GetHour(),
				NewSchedule.dtStart.GetMinute(),
				NewSchedule.dtStart.GetSecond() );

			GetParent()->GetParent()->SetWindowText(strName);
			
			Priority = rs.m_Priority;
			strName = rs.m_Name; strName.TrimRight();
			
			rsNew.m_strFilter.Format("TemplateID = %d",NewSchedule.lTemplateID);
			rsNew.m_strSort = "ID DESC";

			rsNew.AddNew();

			rsNew.m_Name = strName;
			rsNew.m_Date = NewSchedule.dtStart;
			rsNew.m_EndingDate = rsNew.m_Date + (rs.m_EndingDate-rs.m_Date);
			rsNew.m_Priority = Priority;
			rsNew.m_TemplateID = NewSchedule.lTemplateID;
			rsNew.Update();

			rsNew.m_strFilter.Format("[Date]='%d-%d-%d %d:%d:%d'",
						NewSchedule.dtStart.GetYear(),
						NewSchedule.dtStart.GetMonth(),
						NewSchedule.dtStart.GetDay(),
						NewSchedule.dtStart.GetHour(),
						NewSchedule.dtStart.GetMinute(),
						NewSchedule.dtStart.GetSecond() );
			rsNew.Requery();
			NewSchedule.lScheduleID = rsNew.m_ID;

			strName.Format("%d-%d-%d %d:%d:%d - %s",
				NewSchedule.dtStart.GetYear(),
				NewSchedule.dtStart.GetMonth(),
				NewSchedule.dtStart.GetDay(),
				NewSchedule.dtStart.GetHour(),
				NewSchedule.dtStart.GetMinute(),
				NewSchedule.dtStart.GetSecond(), 
				rs.m_Name );
			
			hSchedule = pTree->InsertItem(strName,3,3,hDay);
			typeTreeItem *lpNew = new typeTreeItem;
			lpNew->lID = rsNew.m_ID;
			lpNew->wType = TYPE_SCHEDULE;
			pTree->SetItemData(hSchedule,(DWORD)lpNew);
			pTree->EnsureVisible(hSchedule);

			Start = COleDateTime(lpYear->lID,lpMonth->lID,lpDay->lID,rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond());

			NewSchedule.lRadioID = m_lRadioID;

			if( dl.m_bCopyAll )
			{
				CRSScheduleHeadline *rsTemp;
				for( int N=0; N<NewSchedule.nRadios; N++ )
				{
					rsTemp = new CRSScheduleHeadline( NewSchedule.tRadios[N].strDSN );
					rsTemp->m_strSort = "ID DESC";
					rsTemp->Open();
					rsTemp->AddNew();
					rsTemp->m_Name = strName;
					rsTemp->m_Date = NewSchedule.dtStart;
					rsTemp->m_EndingDate = rsNew.m_Date + (rs.m_EndingDate-rs.m_Date);
					rsTemp->m_Priority = Priority;
					rsTemp->m_TemplateID = 0;
					rsTemp->Update();
					rsTemp->m_strFilter.Format("[Date]='%d-%d-%d %d:%d:%d'",
						NewSchedule.dtStart.GetYear(),
						NewSchedule.dtStart.GetMonth(),
						NewSchedule.dtStart.GetDay(),
						NewSchedule.dtStart.GetHour(),
						NewSchedule.dtStart.GetMinute(),
						NewSchedule.dtStart.GetSecond() );
					rsTemp->Requery();
					NewSchedule.tRadios[N].lScheduleID = rsTemp->m_ID;
					rsTemp->Close();
					delete rsTemp;
				}
			}

			m_pRightView->GenerateSchedule(&NewSchedule);
			
			WriteDigitalLog( g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_SCHEDULE,NewSchedule.lScheduleID,m_lRadioID,NewSchedule.lTemplateID);

			EnableWindow(TRUE);
			m_pRightView->EnableWindow(TRUE);
			rs.MoveNext();
		}
		OnExpanding(hDay);
	}
	rs.Close();
}

void CCalendarLeftView::CopySchedule( HTREEITEM hDay )
{
	CTreeCtrl*	pTree = &GetTreeCtrl();
	HTREEITEM	hMonth = pTree->GetParentItem(hDay);
	HTREEITEM	hYear = pTree->GetParentItem(hMonth);
	typeTreeItem *lpDay = (typeTreeItem *)pTree->GetItemData(hDay);
	typeTreeItem *lpMonth = (typeTreeItem *)pTree->GetItemData(hMonth);
	typeTreeItem *lpYear = (typeTreeItem *)pTree->GetItemData(hYear);
	
	CRSScheduleHeadline rs( m_strConnect );
	rs.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
	rs.Open();
	if( rs.GetRecordCount()!=0 )
	{
		COleDateTime	Start(lpYear->lID,lpMonth->lID,lpDay->lID,rs.m_Date.GetHour(),rs.m_Date.GetMinute(),rs.m_Date.GetSecond());
		COleDateTime	End = Start+(rs.m_EndingDate-rs.m_Date);

		if( CheckForConflict(Start,End) )
		{
			AfxMessageBox(IDS_SCHEDULECONFLICT);
			return;
		}
		CCopySchedule dl;

		if( dl.DoModal()==IDOK )
		{
			long	TemplateID = rs.m_ID,
					Priority = rs.m_Priority;
			CString strName = rs.m_Name; strName.TrimRight();

			rs.m_strFilter.Format("TemplateID = %d",TemplateID);
			rs.m_strSort = "ID DESC";

			rs.AddNew();

			rs.m_Name = strName;
			rs.m_Date = Start;
			rs.m_EndingDate = End;
			rs.m_Priority = Priority;
			rs.m_TemplateID = TemplateID;
			rs.Update();
			rs.m_strFilter.Format("[Date]='%d-%d-%d %d:%d:%d'",
						Start.GetYear(),
						Start.GetMonth(),
						Start.GetDay(),
						Start.GetHour(),
						Start.GetMinute(),
						Start.GetSecond() );
			rs.Requery();

			HTREEITEM hSchedule = pTree->InsertItem(strName,10,10,hDay);
			typeTreeItem *lpNew = new typeTreeItem;
			lpNew->lID = rs.m_ID;
			lpNew->wType = TYPE_SCHEDULE;
			pTree->SetItemData(hSchedule,(DWORD)lpNew);
			pTree->SelectItem(hSchedule);
			pTree->EnsureVisible(hSchedule);
			m_pRightView->SetSchedule(lpNew->lID);

			typeCopySchedule *pData = new typeCopySchedule;
			pData->bJingles = dl.m_Data.bJingles;
			pData->bNewJingles = dl.m_Data.bNewJingles;
			pData->bMusic = dl.m_Data.bMusic;
			pData->bNewMusic = dl.m_Data.bNewMusic;
			pData->bVoice = dl.m_Data.bVoice;
			pData->bNewVoice = dl.m_Data.bNewVoice;
			pData->bOthers = dl.m_Data.bOthers;
			pData->bBlocked = dl.m_Data.bBlocked;
			pData->lTemplateID = TemplateID;
			pData->lScheduleID = lpNew->lID;
			pData->dtStart = Start;
			pData->wndView = (CWnd *)m_pRightView;
			pData->lRadioID = m_lRadioID;
			pData->nRadios = 0;

			if( dl.m_bCopyAll )
			{
				CRSRadioStations rsRadios(g_strMainConnect);
				rsRadios.m_strSort="Name";
				rsRadios.Open();

				while( !rsRadios.IsEOF() )
				{
					rsRadios.m_DSN.TrimRight();
					if( rsRadios.m_DSN!=m_strConnect )
					{
						rsRadios.m_DB.TrimRight();
						pData->tRadios[pData->nRadios].strDBName=rsRadios.m_DB;
						pData->tRadios[pData->nRadios].strDSN=rsRadios.m_DSN;
						pData->nRadios++;
					}
					rsRadios.MoveNext();
				}
				rsRadios.Close();

				CRSScheduleHeadline *rsTemp;
				for( int N=0; N<pData->nRadios; N++ )
				{
					rsTemp = new CRSScheduleHeadline( pData->tRadios[N].strDSN );
					rsTemp->m_strSort = "ID DESC";
					rsTemp->Open();
					rsTemp->AddNew();
					rsTemp->m_Name = strName;
					rsTemp->m_Date = Start;
					rsTemp->m_EndingDate = End;
					rsTemp->m_Priority = Priority;
					rsTemp->m_TemplateID = 0;
					rsTemp->Update();
					rsTemp->m_strFilter.Format("[Date]='%d-%d-%d %d:%d:%d'",
						Start.GetYear(),
						Start.GetMonth(),
						Start.GetDay(),
						Start.GetHour(),
						Start.GetMinute(),
						Start.GetSecond() );
					rsTemp->Requery();
					pData->tRadios[N].lScheduleID = rsTemp->m_ID;
					rsTemp->Close();
					delete rsTemp;
				}
			}

			WriteDigitalLog( g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_SCHEDULE,pData->lScheduleID,m_lRadioID,pData->lTemplateID);

			AfxBeginThread( (m_pRightView->GenerateScheduleThread),(LPVOID)pData);
		}
	}
}

BOOL CCalendarLeftView::CheckForConflict(COleDateTime Start,COleDateTime End )
{
	CString		strStart,
				strEnd;
	BOOL		bResult;
	CRSScheduleHeadline rs( m_strConnect );
	
	strStart.Format("%d-%d-%d %d:%d:%d",
					Start.GetYear(),Start.GetMonth(),Start.GetDay(),
					Start.GetHour(),Start.GetMinute(),Start.GetSecond() );
	strEnd.Format("%d-%d-%d %d:%d:%d",
					End.GetYear(),End.GetMonth(),End.GetDay(),
					End.GetHour(),End.GetMinute(),End.GetSecond() );

	rs.m_strFilter.Format("(Date > '%s' AND Date < '%s') OR (EndingDate > '%s' AND EndingDate < '%s') OR (Date <= '%s' AND EndingDate >= '%s')",
		strStart,strEnd,strStart,strEnd,strStart,strEnd);
	rs.Open();	
	bResult = (rs.GetRecordCount()!=0);
	rs.Close();

	return bResult;
}

void CCalendarLeftView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	CTreeCtrl	*pTree=&GetTreeCtrl();
	UINT		Flags;
	HTREEITEM	hItem=pTree->HitTest(pNMTreeView->ptDrag,&Flags);
	
	if( hItem==NULL )
		return;

	typeTreeItem	*lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	COleDateTime	dt;
	
	HANDLE		hData=::GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,sizeof(typeTreeDrag));
	typeTreeDrag	*lpItemDrag=(typeTreeDrag *)::GlobalLock(hData);
	CString		strTemp = pTree->GetItemText(hItem);
	lpItemDrag->Item.lID=lpItem->lID;
	lpItemDrag->Item.wType=lpItem->wType;
	if( lpItem->wType==TYPE_DAY )
	{
		HTREEITEM		hMonth=pTree->GetParentItem(hItem),
						hYear=pTree->GetParentItem(hMonth);
		typeTreeItem	*lpMonth = (typeTreeItem *)pTree->GetItemData(hMonth),
						*lpYear = (typeTreeItem *)pTree->GetItemData(hYear);
		
		dt=COleDateTime(lpYear->lID,lpMonth->lID,lpItem->lID,0,0,0);
		lpItemDrag->lpData = &dt;
	}
	else
		lpItemDrag->lpData = NULL;
	strcpy(lpItemDrag->strName,strTemp);
	
//	m_lpDragItem=lpItemDrag;
	m_OldPoint.x=m_OldPoint.y=-23000; 
	pTree->SelectItem(hItem);
	
	COleDataSource DataSource;
	
	DataSource.CacheGlobalData(g_nFormat,hData);
	long result=DataSource.DoDragDrop();

	if( result==DROPEFFECT_MOVE)
		OnDragMove();

	*pResult = result;
}

void CCalendarLeftView::OnInfo()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem(),
				hMonth,
				hYear;
	
	if( hItem==NULL )
		return;

	typeTreeItem	*lpItem = (typeTreeItem *)pTree->GetItemData(hItem),
					*lpMonth,
					*lpYear;

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
		hMonth = pTree->GetParentItem(hItem);
		hYear = pTree->GetParentItem(hMonth);

		lpYear = (typeTreeItem *)pTree->GetItemData(hYear);
		lpMonth = (typeTreeItem *)pTree->GetItemData(hMonth);

		strURL.Format("%s/ViewDaySchedule.asp?Date=%d-%d-%d&RadioID=%d",
			g_strBaseURL,
			lpYear->lID,
			lpMonth->lID,
			lpItem->lID,
			m_lRadioID );
		break;
	}

	if( strURL!="" )
		g_wndInfo->SetView(strURL);
}