/ ScheduleRightView.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "ScheduleRightView.h"
#include "SchedulerDoc.h"
#include "MusicSelector.h"
#include "JingleSelector.h"
#include "VoiceInsert.H"
#include "..\include\rsvoiceinsert.h"
#include "..\include\rsPath.h"
#include "..\include\RSBlocksDefinition.h"
//#include "..\include\utils.h"
#include "..\include\rsScheduleTemplate.h"
#include "..\include\RSViewSchedule.h"
#include "..\include\RSViewRms.h"
#include "..\include\RSViewVoiceInsert.h"
#include "..\include\RSScheduleHeadline.h"
#include "..\OnAir\typeLineUpItem.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\RSViewMusicDataPlaying.h"
#include "..\OnAir\RSViewJinglesDataOnAir.h"
#include "..\OnAir\RSViewSpotOnAirData.h"
#include "..\OnAir\pflwnd.h"
#include "..\include\RSOnAirUsers.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CPFLWnd		*g_wndPFL;
extern	CImageList	*g_ilTree;
extern	UINT		g_nFormat;
extern	CString		g_strMainConnect;

/////////////////////////////////////////////////////////////////////////////
// CScheduleRightView

IMPLEMENT_DYNCREATE(CScheduleRightView, CListView)

CScheduleRightView::CScheduleRightView()
{
	m_OldPoint.x = m_OldPoint.y = 32000;
}

CScheduleRightView::~CScheduleRightView()
{
}


BEGIN_MESSAGE_MAP(CScheduleRightView, CListView)
	//{{AFX_MSG_MAP(CScheduleRightView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleRightView drawing

void CScheduleRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CScheduleRightView diagnostics

#ifdef _DEBUG
void CScheduleRightView::AssertValid() const
{
	CListView::AssertValid();
}

void CScheduleRightView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScheduleRightView message handlers

void CScheduleRightView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CSchedulerDoc *pDoc = (CSchedulerDoc *)m_pDocument;

	if( pDoc->m_ScheduleID==0 ) return;

	CListCtrl	*pList=&GetListCtrl();
	CRect		rect;
	CString		strTemp;
	int			Cont;
	typeScheduleItem *lpItem;

	for( Cont=0; Cont<5; Cont++ )
		pList->DeleteColumn(0);

	GetScheduleBlocks();

	pList->GetWindowRect(&rect);
	strTemp.LoadString(IDS_LINEUP);
	pList->DeleteAllItems();
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,250);

	strTemp.LoadString(IDS_TEMPLATE);
	pList->InsertColumn(2,strTemp,LVCFMT_LEFT,150);

	strTemp.LoadString(IDS_INTRO);
	pList->InsertColumn(3,strTemp,LVCFMT_RIGHT,50);

	strTemp.LoadString(IDS_LENGTH);
	pList->InsertColumn(5,strTemp,LVCFMT_RIGHT,75);

	strTemp.LoadString(IDS_TIME);
	pList->InsertColumn(5,strTemp,LVCFMT_RIGHT,75);

	CRSViewSchedule	rs( pDoc->m_strConnect );
	rs.m_strFilter.Format("ScheduleID = %d",pDoc->m_ScheduleID);
	rs.m_strSort = "ItemOrder";
	rs.Open();

	Cont=0;
	while( !rs.IsEOF() )
	{
		rs.m_Type.TrimRight();
		rs.m_Name.TrimRight();
		rs.m_TemplateName.TrimRight();

		lpItem = new typeScheduleItem;
		lpItem->bLocked = rs.m_Priority;
		lpItem->dwIntro = (rs.m_Intro > rs.m_Start ) ? rs.m_Intro-rs.m_Start : 0;
		lpItem->lArtistID = rs.m_TypeID;
		lpItem->lID = rs.m_ItemID;
		lpItem->lTemplateID = rs.m_TemplateID;
		lpItem->qwLength = (DWORD64)(rs.m_Mix-rs.m_Start)*10000;
		lpItem->qwOriginalLen = lpItem->qwLength;
		lpItem->qwStart = 0;
		lpItem->strTemplate = rs.m_TemplateName;
		lpItem->strName = rs.m_Type + " - " + rs.m_Name;
		lpItem->wType = (WORD)rs.m_ItemType;
		lpItem->iRythm = rs.m_Rythm;

		switch( lpItem->wType )
		{
		case TYPE_MUSIC:
			lpItem->iImage=17;
			break;
		case TYPE_JINGLE:
			lpItem->iImage=4;
			break;
		case TYPE_SPOT:
			lpItem->iImage=1;
			break;
		case TYPE_VOICEINSERT:
			lpItem->iImage=5;
			break;
		case TYPE_TIMESIGNAL:
			lpItem->iImage=3;
			break;
		case TYPE_RM:
			lpItem->iImage=9;
			break;
		default:
			lpItem->iImage=0;
			break;
		}
	
		if( lpItem->dwIntro==0 )
			lpItem->strIntro="";
		else
		{
			GetTimeString( lpItem->dwIntro,&lpItem->strIntro);
			lpItem->strIntro.Delete(10,2);
			TrimTimeString(&lpItem->strIntro);
		}

		GetTimeString64(lpItem->qwLength,&lpItem->strLength);
		lpItem->strLength.Delete(10,2);
		TrimTimeString(&lpItem->strLength);

		if( lpItem->wType == TYPE_VOICEINSERT )
		{
			lpItem->qwLength = 0;
			lpItem->qwOriginalLen = 0;
		}

		pList->InsertItem(Cont,lpItem->strName,lpItem->iImage);
		pList->SetItemText(Cont,1,lpItem->strTemplate);
		pList->SetItemText(Cont,2,lpItem->strIntro);
		pList->SetItemText(Cont,3,lpItem->strLength);
		if( lpItem->bLocked )
			pList->SetItem(Cont,4,LVIF_IMAGE,"",19,0,0,0);

		pList->SetItemData(Cont,(DWORD)lpItem);
		
		Cont++;

		rs.MoveNext();
	}
	rs.Close();

	InsertBlocks();
}

int CScheduleRightView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style|=LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CListCtrl *pList = &GetListCtrl();
	pList->SetImageList(g_ilTree,LVSIL_SMALL);
	
	ListView_SetExtendedListViewStyleEx(this->m_hWnd,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT);
	m_DropTarget.Register(this);

	return 0;
}

DROPEFFECT CScheduleRightView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( (m_lpDragItem->Item.wType != TYPE_SPOT) &&
		(m_lpDragItem->Item.wType != TYPE_JINGLE) &&
		(m_lpDragItem->Item.wType != TYPE_MUSIC) &&
		(m_lpDragItem->Item.wType != TYPE_RM) &&
		(m_lpDragItem->Item.wType != TYPE_TIMESIGNAL) &&
		(m_lpDragItem->Item.wType != TYPE_VOICEINSERT) &&
		(m_lpDragItem->Item.wType != TYPE_MUSICTEMPLATE) && 
		(m_lpDragItem->Item.wType != TYPE_SCHEDULEDRAG) &&
		(m_lpDragItem->Item.wType != TYPE_JINGLETEMPLATE) )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	return DROPEFFECT_COPY;
}

void CScheduleRightView::OnDragLeave() 
{
	if( m_lpDragItem == NULL )
		return ;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;
	m_lpDragItem=NULL;
}

DROPEFFECT CScheduleRightView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !g_Permissions.bScheduleEdit )
		return DROPEFFECT_NONE;

	if( m_lpDragItem == NULL )
		return DROPEFFECT_NONE;


	CListCtrl	*pList = &GetListCtrl();
	UINT		uFlags;
	int			nItem=pList->HitTest(point,&uFlags);
	
	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint=point;
	DrawDragItem(m_lpDragItem->strName,m_OldPoint);

	if (uFlags & LVHT_ONITEMLABEL)
	{
		UINT uState=pList->GetItemState(nItem,LVIS_SELECTED);
		if( !(uState & LVIS_SELECTED) )
		{
			DrawDragItem(m_lpDragItem->strName,m_OldPoint);
			pList->SetItem(nItem, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED,LVIS_SELECTED, 0);
			m_OldPoint.x=m_OldPoint.y=45000;
		}
	}
	else
	{
		int Pos=pList->GetNextItem(-1,LVNI_SELECTED);
		if( Pos!= -1 )
			pList->SetItemState(Pos,0,LVIS_SELECTED);
	}

	return ( DROPEFFECT_COPY );
}

BOOL CScheduleRightView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CListCtrl	*pList = &GetListCtrl();
	int			Pos=pList->GetNextItem(-1,LVNI_SELECTED);

	if( Pos==-1 )
		Pos=pList->GetItemCount();

	if( m_lpDragItem->Item.wType != TYPE_SCHEDULEDRAG )
	{
		typeScheduleItem *lpItem = new typeScheduleItem;
		lpItem->lArtistID = 0;

		if( GetDraggedItem( lpItem )==FALSE ) return TRUE;

		lpItem->bLocked=FALSE;

		pList->InsertItem(Pos,lpItem->strName,lpItem->iImage);
		pList->SetItemText(Pos,1,lpItem->strTemplate);
		pList->SetItemText(Pos,2,lpItem->strIntro);
		pList->SetItemText(Pos,3,lpItem->strLength);
		pList->SetItemData(Pos,(DWORD)lpItem);
		
		RemoveBlocks();
		InsertBlocks();
		SaveSchedule();
	}
	else
	{
		if( Pos!=m_lpDragItem->Item.lID )
		{
			pList->DeleteItem(m_lpDragItem->Item.lID);
			if( Pos>m_lpDragItem->Item.lID )
				Pos--;

			typeScheduleItem *lpItem = (typeScheduleItem *)m_lpDragItem->lpData;

			pList->InsertItem(Pos,lpItem->strName,lpItem->iImage);
			pList->SetItemText(Pos,1,lpItem->strTemplate);
			pList->SetItemText(Pos,2,lpItem->strIntro);
			pList->SetItemText(Pos,3,lpItem->strLength);
			pList->SetItemData(Pos,(DWORD)lpItem);

			RemoveBlocks();
			InsertBlocks();
			SaveSchedule();
		}

		return DROPEFFECT_MOVE;
	}

	return TRUE;
}

void CScheduleRightView::DrawDragItem(char *strName,CPoint point)
{
	CClientDC	dc(this);

	CDC	compDC;
	CBitmap	bm;
	CBitmap *oldbm;
	CSize	size;

	size=dc.GetTextExtent(strName,strlen(strName) );
	bm.CreateCompatibleBitmap(&dc,size.cx,size.cy);
	compDC.CreateCompatibleDC(&dc);
	oldbm=compDC.SelectObject(&bm);

	compDC.SetTextColor(RGB(0,0,0));
	compDC.FillRect(&CRect(0,0,size.cx,size.cy),&CBrush(RGB(255,255,255)));
	compDC.DrawText(strName,&CRect(0,0,size.cx,size.cy),DT_LEFT);
	
	compDC.InvertRect(&CRect(0,0,size.cx,size.cy));
	dc.BitBlt(point.x,point.y,size.cx,size.cy, &compDC,0,0, SRCINVERT);

	compDC.SelectObject(oldbm);
}

BOOL CScheduleRightView::GetDraggedItem( typeScheduleItem *lpItem )
{
	CSchedulerDoc *pDoc = (CSchedulerDoc *)m_pDocument;

	lpItem->iRythm = 0;

	if( m_lpDragItem->Item.wType == TYPE_MUSIC )
	{
		CRSViewMusicDataPlaying	rs( g_strMainConnect );
		rs.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID );
		rs.Open();

		if( rs.GetRecordCount()==0 ) return FALSE;

		CTreeCtrl *pTree = &m_pLeft->GetTreeCtrl();
		HTREEITEM hMusic = pTree->GetSelectedItem();
		HTREEITEM hArtist = pTree->GetParentItem(hMusic);
		HTREEITEM hTemplate = pTree->GetParentItem( hArtist );
		typeTreeItem *lpTemp = (typeTreeItem *)pTree->GetItemData(hTemplate);

		lpItem->strTemplate = pTree->GetItemText(hTemplate);
		lpItem->strName = pTree->GetItemText( hArtist )+" - "+pTree->GetItemText(hMusic);
		lpItem->lTemplateID = lpTemp->lID;
		lpItem->lID = rs.m_ID;
		lpItem->lArtistID = rs.m_ArtistID;
		lpItem->wType = TYPE_MUSIC;
		lpItem->iImage = 17;
		lpItem->qwLength = (DWORD64)(rs.m_Mix-rs.m_Start)*10000;
		lpItem->dwIntro = ( rs.m_Intro > rs.m_Start ) ? rs.m_Intro-rs.m_Start : 0;

		GetTimeString(lpItem->dwIntro,&lpItem->strIntro);
		lpItem->strIntro.Delete(10,2);
		TrimTimeString(&lpItem->strIntro);

		GetTimeString64(lpItem->qwLength,&lpItem->strLength);
		lpItem->strLength.Delete(10,2);
		TrimTimeString(&lpItem->strLength);

		lpItem->iRythm = rs.m_Rythm;

		rs.Close();
		return TRUE;
	}

	if( (m_lpDragItem->Item.wType==TYPE_MUSICTEMPLATE) && (m_lpDragItem->Item.lID!=0) )
	{
		CRSScheduleTemplate rs( pDoc->m_strConnect );
		rs.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rs.Open();
		if( rs.GetRecordCount()==0 ) return FALSE;

		CMusicSelector dl;

		rs.m_strSQL.TrimRight();

		dl.m_strConnect = pDoc->m_strConnect;
		dl.m_strSort = "MaxMusicDate";
		dl.m_strSQL = rs.m_strSQL;

		CString sqlDate;
		sqlDate.Format("(MaxArtistDate is null OR MaxArtistDate < '%d-%d-%d %d:%d:%d')",pDoc->m_ScheduleDate.GetYear(),pDoc->m_ScheduleDate.GetMonth(),pDoc->m_ScheduleDate.GetDay(),pDoc->m_ScheduleDate.GetHour(),pDoc->m_ScheduleDate.GetMinute(),pDoc->m_ScheduleDate.GetSecond() );

		if( dl.m_strSQL.GetLength()==0 )
			dl.m_strSQL = sqlDate;
		else
			dl.m_strSQL+=(" AND "+sqlDate);

		if( dl.DoModal()==IDOK )
		{
			CRSViewMusicDataPlaying	rsMusic( g_strMainConnect );
			rsMusic.m_strFilter.Format("ID = %d",dl.m_MusicID );
			rsMusic.Open();

			rs.m_Name.TrimRight();
			
			lpItem->strTemplate = rs.m_Name;
			lpItem->lTemplateID = rs.m_ID;

			lpItem->lID = rsMusic.m_ID;
			lpItem->lArtistID = rsMusic.m_ArtistID;
			lpItem->wType = TYPE_MUSIC;
			lpItem->strName = dl.m_strSongName;
			lpItem->iImage = 17;
			lpItem->qwLength = (DWORD64)(rsMusic.m_Mix-rsMusic.m_Start)*10000;
			lpItem->dwIntro = ( rsMusic.m_Intro > rsMusic.m_Start ) ? rsMusic.m_Intro-rsMusic.m_Start : 0;

			GetTimeString(lpItem->dwIntro,&lpItem->strIntro);
			lpItem->strIntro.Delete(10,2);
			TrimTimeString(&lpItem->strIntro);

			GetTimeString64(lpItem->qwLength,&lpItem->strLength);
			lpItem->strLength.Delete(10,2);
			TrimTimeString(&lpItem->strLength);

			return TRUE;
		}
		else
			return FALSE;
	}

	if( m_lpDragItem->Item.wType==TYPE_JINGLE )
	{
		CRSViewJinglesDataOnAir rs( g_strMainConnect );
		rs.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rs.Open();
		if( rs.GetRecordCount()==0 ) return 0;

		CTreeCtrl *pTree = &m_pLeft->GetTreeCtrl();
		HTREEITEM hJingle = pTree->GetSelectedItem();
		HTREEITEM hType = pTree->GetParentItem(hJingle);
		HTREEITEM hTemp = pTree->GetParentItem(hType);

		lpItem->lTemplateID = 0;
		lpItem->strTemplate="";
		typeTreeItem	*lpTemp = (typeTreeItem *)pTree->GetItemData(hTemp);
		if( lpTemp!=NULL )
			if( (lpTemp->lID!=0) && (lpTemp->wType==TYPE_JINGLETEMPLATE) )
			{
				lpItem->lTemplateID = lpTemp->lID;
				lpItem->strTemplate = pTree->GetItemText(hTemp);
			}
		
		rs.m_Name.TrimRight();
		rs.m_TypeName.TrimRight();

		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_JINGLE;

		lpItem->strName = rs.m_TypeName+" - "+rs.m_Name;
		lpItem->iImage = 4;
		lpItem->qwLength = (DWORD64)(rs.m_Mix-rs.m_Start)*10000;
		lpItem->dwIntro = ( rs.m_Intro > rs.m_Start ) ? rs.m_Intro-rs.m_Start : 0;

		GetTimeString(lpItem->dwIntro,&lpItem->strIntro);
		lpItem->strIntro.Delete(10,2);
		TrimTimeString(&lpItem->strIntro);

		GetTimeString64(lpItem->qwLength,&lpItem->strLength);
		lpItem->strLength.Delete(10,2);
		TrimTimeString(&lpItem->strLength);

		return TRUE;
	}

	if( (m_lpDragItem->Item.wType==TYPE_JINGLETEMPLATE) && (m_lpDragItem->Item.lID!=0) )
	{
		CRSScheduleTemplate rsTemp( pDoc->m_strConnect );
		rsTemp.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rsTemp.Open();

		if( rsTemp.GetRecordCount()==0 ) 
			return FALSE;

		CJingleSelector dl;
		dl.m_strConnect = pDoc->m_strConnect;
		dl.m_strSort = "MaxDate";
		dl.m_strSQL = rsTemp.m_strSQL;
		dl.m_strSQL.TrimRight();
		if( dl.DoModal()==IDOK )
		{
			CRSViewJinglesDataOnAir rs(g_strMainConnect);
			rs.m_strFilter.Format("ID = %d",dl.m_JingleID);
			rs.Open();
			if( rs.GetRecordCount()==0 )
				return FALSE;

			lpItem->lTemplateID = rsTemp.m_ID;
			lpItem->strTemplate=rsTemp.m_Name;

			lpItem->lID = rs.m_ID;
			lpItem->wType = TYPE_JINGLE;

			lpItem->bLocked = 0;
			lpItem->dwIntro = (rs.m_Intro > rs.m_Start) ? rs.m_Intro-rs.m_Start : 0;
			lpItem->qwLength = (DWORD64)(rs.m_Mix-rs.m_Start);
			lpItem->qwStart = 0;
			lpItem->iImage = 4;

			GetTimeString(lpItem->dwIntro,&lpItem->strIntro);
			lpItem->strIntro.Delete(10,2);
			TrimTimeString(&lpItem->strIntro);

			GetTimeString64(lpItem->qwLength,&lpItem->strLength);
			lpItem->strLength.Delete(10,2);
			TrimTimeString(&lpItem->strLength);

			lpItem->strName = dl.m_strJingleName;
			lpItem->strTemplate.TrimRight();

			return TRUE;
		}
		else
			return FALSE;
	}

	if( m_lpDragItem->Item.wType==TYPE_SPOT )
	{
		CRSViewSpotOnAirData rs( g_strMainConnect );
		rs.m_strFilter.Format("SpotID = %d",m_lpDragItem->Item.lID);
		rs.Open();
		if( rs.GetRecordCount()==0 ) return FALSE;
		
		lpItem->lTemplateID = 0;
		lpItem->strTemplate="";
		
		rs.m_Name.TrimRight();
		rs.m_CustomerName.TrimRight();

		lpItem->lID = rs.m_SpotID;
		lpItem->wType = TYPE_SPOT;
		lpItem->strName = rs.m_CustomerName+" - "+rs.m_Name;
		lpItem->iImage = 1;
		lpItem->qwLength = (DWORD64)(rs.m_Mix-rs.m_Start)*10000;
		lpItem->dwIntro = 0;
		lpItem->strIntro="";

		GetTimeString64(lpItem->qwLength,&lpItem->strLength);
		lpItem->strLength.Delete(10,2);
		TrimTimeString(&lpItem->strLength);

		return TRUE;
	}

	if( m_lpDragItem->Item.wType==TYPE_RM)
	{
		CRSViewRms rs( g_strMainConnect );
		rs.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rs.Open();
		if( rs.GetRecordCount()==0 ) return FALSE;
		
		lpItem->lTemplateID = 0;
		lpItem->strTemplate="";
		
		rs.m_Name.TrimRight();
		rs.m_Type.TrimRight();

		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_RM;
		lpItem->strName = rs.m_Type+" - "+rs.m_Name;
		lpItem->iImage = 9;
		lpItem->qwLength = (DWORD64)(rs.m_Mix-rs.m_Start)*10000;
		lpItem->dwIntro = 0;
		lpItem->strIntro="";

		GetTimeString64(lpItem->qwLength,&lpItem->strLength);
		lpItem->strLength.Delete(10,2);
		TrimTimeString(&lpItem->strLength);

		return TRUE;
	}

	if( m_lpDragItem->Item.wType==TYPE_TIMESIGNAL )
	{
		CTreeCtrl *pTree = &m_pLeft->GetTreeCtrl();
		HTREEITEM hSignal = pTree->GetSelectedItem();
		HTREEITEM hParent = pTree->GetParentItem(hSignal);

		lpItem->lID = m_lpDragItem->Item.lID;
		lpItem->wType = TYPE_TIMESIGNAL;
		lpItem->strName = pTree->GetItemText(hParent)+" - "+pTree->GetItemText(hSignal);
		lpItem->iImage = 3;
		lpItem->qwLength = 0;
		lpItem->dwIntro = 0;
		lpItem->strIntro="";
		lpItem->strLength="";
		
		return TRUE;
	}

	if( (m_lpDragItem->Item.wType==TYPE_VOICEINSERT) && (m_lpDragItem->Item.lID!=0) )
	{
		CRSViewVoiceInsert rs( pDoc->m_strConnect );
		rs.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rs.Open();

		if( rs.GetRecordCount()==0 )
			return FALSE;

		lpItem->lTemplateID = 0;
		lpItem->strTemplate="";
		
		rs.m_Name.TrimRight();
		rs.m_User.TrimRight();

		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_VOICEINSERT;
		lpItem->strName = rs.m_User+" - "+rs.m_Name;
		lpItem->iImage = 5;
		lpItem->qwLength = 0;
		lpItem->dwIntro = 0;
		lpItem->strIntro="";
		lpItem->strLength="";
		return TRUE;
	}


	if( (m_lpDragItem->Item.wType==TYPE_VOICEINSERT) && (m_lpDragItem->Item.lID==0) )
	{
		CVoiceInsert dlg;
	
		CRSPath	rsPath(g_strMainConnect);
		rsPath.m_strFilter="Takes = '1'";
		rsPath.m_strSort="ID";
		rsPath.Open();
		if( rsPath.GetRecordCount()==0 ) return FALSE;
		rsPath.m_Path.TrimRight();

		CSchedulerDoc	*pDoc = (CSchedulerDoc *)m_pDocument;
		if( pDoc->m_ScheduleID==NULL ) return FALSE;

		CRSScheduleHeadline rsHead( pDoc->m_strConnect );
		rsHead.m_strFilter.Format("ID = %d",pDoc->m_ScheduleID);
		rsHead.Open();
		rsHead.m_Name.TrimRight();

		CString strSchedule=rsHead.m_Date.Format("%Y-%m-%d")+" - "+rsHead.m_Name,
				strFile,
				strTemp;
		int nTake=0;

		CRSVoiceInsert rsVoice( pDoc->m_strConnect );
		rsVoice.m_strFilter="FileName = 'nothing'";
		rsVoice.Open();

		do {
			nTake++;
			strFile.Format("%s - Take %d",strSchedule,nTake);
			strTemp=strFile;
			strTemp.Replace("'","''");
			rsVoice.m_strFilter.Format("FileName = '%s.wav'",strTemp);
			rsVoice.Requery();
		} while( rsVoice.GetRecordCount()!=0 );


		dlg.m_strConnect = pDoc->m_strConnect;
		dlg.m_PathID = rsPath.m_ID;
		dlg.m_strFileName = strFile+".wav";
		dlg.m_strName = strFile;
		dlg.m_strPath = rsPath.m_Path;
		
		if( dlg.DoModal()==IDOK )
		{
			// Adds the new voice insert to the database
			rsVoice.AddNew();

			rsVoice.m_Activ = 1;
			rsVoice.m_FileName = dlg.m_strFileName; 
			rsVoice.m_Finish = dlg.m_End;
			rsVoice.m_Name = dlg.m_strName;
			rsVoice.m_Path = dlg.m_PathID;
			rsVoice.m_Start = dlg.m_Start;
			rsVoice.m_TalentID = dlg.m_UserID;

			rsVoice.Update();
			
			strTemp = dlg.m_strFileName;
			strTemp.Replace("'","''");

			rsVoice.m_strSort = "ID DESC";
			rsVoice.m_strFilter.Format("FileName = '%s'",strTemp);

			rsVoice.Requery();

			// Add the voice insert to the tree view
			CSplitterWnd *wndSplitter=(CSplitterWnd *)GetParent();
			CScheduleLeftView *wndLeft=(CScheduleLeftView *)wndSplitter->GetPane(0,0);
			CTreeCtrl *pTree = &wndLeft->GetTreeCtrl();
			CString strTemp;

			strTemp.LoadString(IDS_VOICEINSERT);
			HTREEITEM hVoiceRoot = wndLeft->FindString(strTemp);

			HTREEITEM hUser = wndLeft->FindChildString(hVoiceRoot,dlg.m_strUser);
			if( hUser==NULL )
			{
				hUser = pTree->InsertItem(dlg.m_strUser,21,21,hVoiceRoot);
				pTree->SetItemData(hUser,0);
			}
			typeTreeItem *lpTreeItem = new typeTreeItem;
			lpTreeItem->lID = rsVoice.m_ID;
			lpTreeItem->wType = TYPE_VOICEINSERT;

			HTREEITEM hVoice = pTree->InsertItem(dlg.m_strName,5,5,hUser);
			pTree->SetItemData(hVoice,(DWORD)lpTreeItem);

			// Add the voice insert to the drag item
			lpItem->lID = rsVoice.m_ID;
			lpItem->lTemplateID = 0;
			lpItem->strTemplate="";
		
			lpItem->wType = TYPE_VOICEINSERT;
			lpItem->strName = dlg.m_strUser+" - "+dlg.m_strName;
			lpItem->iImage = 5;
			lpItem->qwLength = 0;
			lpItem->dwIntro = 0;
			lpItem->strIntro="";
			lpItem->strLength="";
			return TRUE;

		}
		else
			return FALSE;
	}
	return FALSE;
}

void CScheduleRightView::OnPFL()
{
	CSchedulerDoc *pDoc=(CSchedulerDoc *)GetDocument();

	CListCtrl *pList = &GetListCtrl();
	int Pos = pList->GetNextItem(-1,LVNI_SELECTED);

	if( Pos==-1 ) return;

	typeScheduleItem *pItem = (typeScheduleItem *)pList->GetItemData(Pos);

	if( pItem==NULL ) return;

	if( pItem->wType==TYPE_BLOCK )
		return;

	if( pItem->wType==TYPE_VOICEINSERT)
		g_wndPFL->SetSound(pItem->wType,pItem->lID,pDoc->m_strConnect);
	else
		g_wndPFL->SetSound(pItem->wType,pItem->lID);

	g_wndPFL->RestoreWindow();
}

void CScheduleRightView::GetScheduleBlocks()
{
	CSchedulerDoc *pDoc = (CSchedulerDoc *)GetDocument();

	long	StartTime = pDoc->m_ScheduleDate.GetHour()*3600000+pDoc->m_ScheduleDate.GetMinute()*60000+pDoc->m_ScheduleDate.GetSecond()*1000,
			EndTime = pDoc->m_EndingDate.GetHour()*3600000+pDoc->m_EndingDate.GetMinute()*60000+pDoc->m_EndingDate.GetSecond()*1000;
			
	CString days[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	SYSTEMTIME	st;
	DWORD64		qwTime;

	typeLineUpItem *lpItem;

	CRSBlocksDefinition	rs( pDoc->m_strConnect );
	rs.m_strSort = "Time";

	if( pDoc->m_ScheduleDate.GetDay()==pDoc->m_EndingDate.GetDay() )
		rs.m_strFilter.Format("Time >= %d AND Time < %d AND %s = 1 AND Sponsor = 0",StartTime,EndTime,days[pDoc->m_ScheduleDate.GetDayOfWeek()-1]);
	else
		rs.m_strFilter.Format("Time >= %d AND %s = 1 AND Sponsor = 0",StartTime,days[pDoc->m_ScheduleDate.GetDayOfWeek()-1]);

	rs.Open();
	pDoc->m_ScheduleDate.GetAsSystemTime(st);

	SystemTimeToFileTime(&st,(FILETIME *)&qwTime);
	m_nBlocks=0;

	while( !rs.IsEOF() )
	{
		
		lpItem = new typeLineUpItem(TYPE_BLOCK,rs.m_ID,qwTime+(DWORD64)(rs.m_Time-StartTime)*10000,pDoc->m_strConnect);
		if( lpItem->m_bItemIsValid )
		{
			m_lpBlock[m_nBlocks]=lpItem;
			m_nBlocks++;
		}
		rs.MoveNext();
	}

	if( pDoc->m_ScheduleDate.GetDay()!=pDoc->m_EndingDate.GetDay() )
	{
		rs.m_strFilter.Format("Time < %d AND %s = 1 AND Sponsor = 0",EndTime,days[pDoc->m_EndingDate.GetDayOfWeek()-1]);
		rs.Requery();
		
		COleDateTime	dtTemp = COleDateTime( pDoc->m_EndingDate.GetYear(),
												pDoc->m_EndingDate.GetMonth(),
												pDoc->m_EndingDate.GetDay(),
												0,0,0 );

		dtTemp.GetAsSystemTime(st);
		SystemTimeToFileTime(&st,(FILETIME *)&qwTime);

		while( !rs.IsEOF() )
		{
		
			lpItem = new typeLineUpItem(TYPE_BLOCK,rs.m_ID,qwTime+(DWORD64)(rs.m_Time)*10000,pDoc->m_strConnect);
			if( lpItem->m_bItemIsValid )
			{
				m_lpBlock[m_nBlocks]=lpItem;
				m_nBlocks++;
			}
			rs.MoveNext();
		}
	}
}

void CScheduleRightView::RemoveBlocks() 
{
	CListCtrl *pList = &GetListCtrl();

	int					nItems = pList->GetItemCount();
	typeScheduleItem	*lpItem;

	for( int Pos=0; Pos<nItems; Pos++ )
	{
		lpItem = (typeScheduleItem *)pList->GetItemData(Pos);
		if( lpItem->wType == TYPE_BLOCK )
		{
			pList->DeleteItem(Pos);
			Pos--;
			nItems--;
		}
	}
}

void CScheduleRightView::InsertBlocks()
{
	CListCtrl		*pList = &GetListCtrl();
	CSchedulerDoc	*pDoc = (CSchedulerDoc *)GetDocument();
	SYSTEMTIME		st;
	DWORD64			qwTime;
	CString			str;
	typeScheduleItem *lpItem;

	pDoc->m_ScheduleDate.GetAsSystemTime(st);
	SystemTimeToFileTime(&st,(FILETIME *)&qwTime);

	int	nBlock=0,
		nItems=pList->GetItemCount(),
		nPos;
	
	for( nPos=0; nPos<nItems; nPos++ )
	{
		lpItem = (typeScheduleItem *)pList->GetItemData(nPos);
		
		if( (nBlock < m_nBlocks) && (!lpItem->bLocked)  )
		{
			if( m_lpBlock[nBlock]->m_qwStartTime <= qwTime )
			{
				lpItem = new typeScheduleItem;
				lpItem->bLocked=1;
				lpItem->dwIntro=0;
				lpItem->iImage=0;
				lpItem->lID=0;
				lpItem->lTemplateID=0;
				lpItem->qwLength=(DWORD64)(m_lpBlock[nBlock]->m_lEndPos)*10000;
				lpItem->qwOriginalLen=lpItem->qwLength;
				lpItem->strIntro="";

				GetTimeString64(lpItem->qwLength,&lpItem->strLength);
				lpItem->strLength.Delete(10,2);
				TrimTimeString(&lpItem->strLength);

				lpItem->strName = m_lpBlock[nBlock]->m_strName+" - "+m_lpBlock[nBlock]->m_strName2;
				lpItem->wType = TYPE_BLOCK;
				if( m_lpBlock[nBlock]->m_wPrecision==3 )
					lpItem->qwStart = qwTime;
				else
				{
					lpItem->qwStart = m_lpBlock[nBlock]->m_qwStartTime;
					qwTime = m_lpBlock[nBlock]->m_qwStartTime;
				}

				GetTimeString64(lpItem->qwStart,&str);
				str.Delete(8,4);
				
				pList->InsertItem(nPos,lpItem->strName,lpItem->iImage);
				pList->SetItemText(nPos,1,lpItem->strTemplate);
				pList->SetItemText(nPos,2,lpItem->strIntro);
				pList->SetItemText(nPos,3,lpItem->strLength);
				pList->SetItemText(nPos,4,str);
				pList->SetItemData(nPos,(DWORD)lpItem);

				qwTime += lpItem->qwOriginalLen;

				nBlock++;
				nItems++;

				continue;
			}
		}
		lpItem->qwStart = qwTime;
		GetTimeString64(lpItem->qwStart,&str);
		str.Delete(8,4);

		pList->SetItemText(nPos,4,str);

		qwTime+=lpItem->qwLength;
	}
}

void CScheduleRightView::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW *nmCD=(NMLVCUSTOMDRAW *)pNMHDR;
	typeScheduleItem *lpItem=(typeScheduleItem *)nmCD->nmcd.lItemlParam;

	switch( nmCD->nmcd.dwDrawStage )
	{
	case CDDS_PREPAINT:
		*pResult=CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		if( lpItem )
		{
			COLORREF clr;

			if( lpItem->iRythm < g_iSlow )
				clr = COLOR_BLACK;
			else if( lpItem->iRythm < g_iSlowAverage )
				clr = COLOR_GREEN;
			else if( lpItem->iRythm < g_iAverage )
				clr = COLOR_RED;
			else
				clr = COLOR_BLUE;

			switch( lpItem->wType)
			{
			case TYPE_BLOCK:
				nmCD->clrTextBk=RGB(241,175,162);
				nmCD->clrText=RGB(0,0,0);
				break;
			case TYPE_JINGLE:
				nmCD->clrTextBk=RGB(241,239,162);
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
				nmCD->clrText = clr;
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

void CScheduleRightView::OnLockItem()
{
	if( !g_Permissions.bScheduleEdit )
		return;

	CListCtrl *pList = &GetListCtrl();
	int nPos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( nPos == -1 )
		return;

	typeScheduleItem *lpItem = (typeScheduleItem *)pList->GetItemData(nPos);
	if( lpItem->wType == TYPE_BLOCK )
		return;

	pList->DeleteItem(nPos);

	if( lpItem->bLocked )
		lpItem->bLocked=FALSE;
	else
		lpItem->bLocked=TRUE;

	pList->InsertItem(nPos,lpItem->strName,lpItem->iImage);
	pList->SetItemText(nPos,1,lpItem->strTemplate);
	pList->SetItemText(nPos,2,lpItem->strIntro);
	pList->SetItemText(nPos,3,lpItem->strLength);
	if( lpItem->bLocked )
		pList->SetItem(nPos,4,LVIF_IMAGE,"",19,0,0,0);
	pList->SetItemData(nPos,(DWORD)lpItem);
	pList->SetItemState(nPos,LVIS_SELECTED,LVIS_SELECTED);

	RemoveBlocks();
	InsertBlocks();
	SaveSchedule();
}

void CScheduleRightView::SaveSchedule()
{
	CSchedulerDoc	*pDoc = (CSchedulerDoc *)GetDocument();
	CListCtrl		*pList = &GetListCtrl();
	int				nItems = pList->GetItemCount(),
					nOrder = 0,
					iPriority;
	CDatabase		db;
	CString			strSQL,
					strDate;
	SYSTEMTIME		st;
	typeScheduleItem *lpItem;

	strSQL.Format("DELETE FROM Scheduling WHERE ScheduleID = %d",pDoc->m_ScheduleID);
	db.Open( pDoc->m_strConnect );
	db.ExecuteSQL( strSQL );

	for( int Pos=0; Pos<nItems; Pos ++ )
	{
		lpItem = (typeScheduleItem *)pList->GetItemData(Pos);
		if( lpItem->wType != TYPE_BLOCK )
		{
			if( lpItem->bLocked )
				iPriority=1;
			else
				iPriority=0;

			FileTimeToSystemTime((FILETIME *)&lpItem->qwStart,&st);
			strDate.Format("%d-%d-%d %d:%d:%d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

			strSQL.Format("INSERT INTO Scheduling (Date,ItemOrder,ItemType,ItemID,ItemParentID,ScheduleID,Priority,TemplateID) VALUES ('%s',%d,%d,%d,%d,%d,%d,%d)",
				strDate,nOrder,lpItem->wType,lpItem->lID,lpItem->lArtistID,pDoc->m_ScheduleID,iPriority,lpItem->lTemplateID);
			db.ExecuteSQL(strSQL);

			nOrder++;
		}
	}
	db.Close();
}

void CScheduleRightView::OnCut()
{
	if( !g_Permissions.bScheduleEdit )
		return;

	CListCtrl *pList = &GetListCtrl();
	int nPos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( nPos == -1 )
		return;

	typeScheduleItem *lpItem = (typeScheduleItem *)pList->GetItemData(nPos);
	if( lpItem->wType == TYPE_BLOCK )
		return;

	pList->DeleteItem(nPos);

	RemoveBlocks();
	InsertBlocks();
	SaveSchedule();
}

void CScheduleRightView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	CListCtrl*	pList=&GetListCtrl();
	UINT		Flags;
	int			Pos=pList->HitTest(pNMListView->ptAction,&Flags);
	
	if( Pos==-1 )
		return;

	typeScheduleItem	*lpItem=(typeScheduleItem*)pList->GetItemData(Pos);
	if( lpItem==NULL )
		return;

	HANDLE		hData=::GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,sizeof(typeTreeDrag));
	typeTreeDrag	*lpItemDrag=(typeTreeDrag *)::GlobalLock(hData);
	CString		strTemp = pList->GetItemText(Pos,0);
	lpItemDrag->Item.lID=Pos;
	lpItemDrag->Item.wType=TYPE_SCHEDULEDRAG;
	lpItemDrag->lpData = (LPVOID)lpItem;
	strcpy(lpItemDrag->strName,strTemp);
	
//	m_lpDragItem=lpItemDrag;
	m_OldPoint.x=m_OldPoint.y=-23000; 
//	pTree->SelectItem(hItem);
	
	COleDataSource DataSource;
	
	DataSource.CacheGlobalData(g_nFormat,hData);
	long result=DataSource.DoDragDrop();

	if( result==DROPEFFECT_MOVE)
	{
	
	}

	*pResult = 0;
}

void CScheduleRightView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CSchedulerDoc *pDoc=(CSchedulerDoc *)GetDocument();

	CListCtrl *pList = &GetListCtrl();
	int Pos = pList->GetNextItem(-1,LVNI_SELECTED);

	if( Pos==-1 ) return;

	typeScheduleItem *pItem = (typeScheduleItem *)pList->GetItemData(Pos);

	if( pItem==NULL ) return;

	if( pItem->wType==TYPE_BLOCK )
		return;

	if( pItem->wType==TYPE_VOICEINSERT)
		EditVoiceInsert(Pos,pItem);
	else
	{
		g_wndPFL->SetSound(pItem->wType,pItem->lID);
		g_wndPFL->RestoreWindow();	
	}
		
	*pResult = 0;
}

void CScheduleRightView::EditVoiceInsert(int Pos, typeScheduleItem *pItem)
{
	if( !g_Permissions.bVoiceEdit )
		return;

	CListCtrl		*pList = &GetListCtrl();
	CSchedulerDoc	*pDoc=(CSchedulerDoc *)GetDocument();
	CRSVoiceInsert	rsVoice( pDoc->m_strConnect );

	rsVoice.m_strFilter.Format("ID = %d",pItem->lID );
	rsVoice.Open();
	if( rsVoice.GetRecordCount()==0 )
	{
		rsVoice.Open();
		return;
	}

	CRSPath rsPath( g_strMainConnect );
	rsPath.m_strFilter.Format("ID = %d",rsVoice.m_Path);
	rsPath.Open();
	if( rsPath.GetRecordCount()==0 )
	{
		rsPath.m_strFilter= "Takes = 1";
		rsPath.m_strSort = "ID DESC";
		rsPath.Requery();

		if( rsPath.GetRecordCount()==0 )
		{
			rsPath.Close();
			rsVoice.Close();
			return;
		}
	}
	
	CRSOnAirUsers rsUser( g_strMainConnect );
	rsUser.m_strFilter.Format("ID = %d",rsVoice.m_TalentID);
	rsUser.Open();
	if( rsUser.GetRecordCount()==0 )
	{
		rsUser.m_strFilter = "Activ = 1";
		rsUser.m_strSort = "ID";
		rsUser.Requery();
		if( rsUser.GetRecordCount()==0 )
		{
			rsVoice.Close();
			rsPath.Close();
			rsUser.Close();
			return;
		}
	}

	CVoiceInsert	dl(this);
	dl.m_End = rsVoice.m_Finish;
	dl.m_ID = rsVoice.m_ID;
	dl.m_PathID = rsPath.m_ID;
	dl.m_Start = rsVoice.m_Start;
	dl.m_strConnect = pDoc->m_strConnect;
	dl.m_strFileName = rsVoice.m_FileName; dl.m_strFileName.TrimRight();
	dl.m_strName = rsVoice.m_Name; dl.m_strName.TrimRight();
	dl.m_strPath = rsPath.m_Path; dl.m_strPath.TrimRight();
	dl.m_strUser = rsUser.m_Name; dl.m_strUser.TrimRight();
	dl.m_UserID = rsUser.m_ID;
	rsPath.Close();
	rsUser.Close();

	if( dl.DoModal()==IDOK )
	{
		rsVoice.Edit();
		rsVoice.m_Activ = 1;
		rsVoice.m_FileName = dl.m_strFileName;
		rsVoice.m_Finish = dl.m_End;
		rsVoice.m_Name = dl.m_strName;
		rsVoice.m_Path = dl.m_PathID;
		rsVoice.m_Start = dl.m_Start;
		rsVoice.m_TalentID = dl.m_UserID;
		rsVoice.Update();
		
		pList->SetItemText( Pos,0,dl.m_strName );
	}
	rsVoice.Close();
}

void CScheduleRightView::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnPFL();	
	*pResult = 0;
}

void CScheduleRightView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnPFL();
	*pResult = 0;
}
