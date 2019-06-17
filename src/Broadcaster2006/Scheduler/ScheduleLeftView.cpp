// ScheduleLeftView.cpp : implementation file
//

#include "stdafx.h"
#include <io.h>
#include "Scheduler.h"
#include "SchedulerDoc.h"
#include "ScheduleLeftView.h"
#include "MusicTemplate.h"
#include "JingleTemplate.h"
#include "VoiceInsert.h"
#include "..\include\RSTime.h"
#include "..\include\rsScheduleHeadline.h"
#include "..\include\RSScheduleTemplate.h"
#include "..\include\RSViewRMsOnAir.h"
#include "..\include\RSViewVoiceInsert.h"
#include "..\include\RSViewSchedulingTemplate.h"
#include "..\include\RSViewScheduleJingleTemplate.h"
#include "..\include\RSVoiceInsert.h"
#include "..\OnAir\PFLWnd.h"
#include "..\OnAir\RSViewOnAirSponsors.h"
#include "..\OnAir\RSViewJinglesOnAir.h"
#include "..\OnAir\RSViewMusicTracksOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScheduleLeftView

extern CString	g_strMainConnect;
extern CPFLWnd	*g_wndPFL;

IMPLEMENT_DYNCREATE(CScheduleLeftView, CDigitalLeftView)

CScheduleLeftView::CScheduleLeftView()
{
}

CScheduleLeftView::~CScheduleLeftView()
{
}


BEGIN_MESSAGE_MAP(CScheduleLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CScheduleLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleLeftView drawing

void CScheduleLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CScheduleLeftView diagnostics

#ifdef _DEBUG
void CScheduleLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CScheduleLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScheduleLeftView message handlers

void CScheduleLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}

void CScheduleLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CSchedulerDoc	*pDoc = (CSchedulerDoc *)m_pDocument;
	
	if( pDoc->m_ScheduleID==0 ) return;

	CRSScheduleHeadline rsHead( pDoc->m_strConnect );
	rsHead.m_strFilter.Format("ID = %d",pDoc->m_ScheduleID);
	rsHead.Open();
	rsHead.m_Name.TrimRight();

	pDoc->SetTitle(rsHead.m_Date.Format()+" »» "+rsHead.m_Name);
	
	pDoc->m_EndingDate = rsHead.m_EndingDate;
	pDoc->m_ScheduleDate = rsHead.m_Date;

	rsHead.Close();

	AfxBeginThread(RefreshList,(LPVOID)this);
}

UINT CScheduleLeftView::RefreshList( LPVOID lp )
{
	CScheduleLeftView *pView = (CScheduleLeftView *)lp;
	CSchedulerDoc	*pDoc = (CSchedulerDoc *)pView->GetDocument();
	CTreeCtrl		*pTree = &pView->GetTreeCtrl();
	
	HTREEITEM	hItem,
				hTemplate;
	CString		str;
	str.LoadString( IDS_TEMPLATE );

	hTemplate = pTree->InsertItem("* "+str,18,18);
	pTree->SetItemData(hTemplate,0);

	str.LoadString(IDS_MUSIC);
	pView->m_hTemplateMusic = pTree->InsertItem(str,17,17,hTemplate);
	pTree->SetItemData(pView->m_hTemplateMusic,0);

	typeTreeItem *lpItem = new typeTreeItem;
	lpItem->lID = 0;
	lpItem->wType = TYPE_MUSICTEMPLATE;

	str.LoadString(IDS_NEW);
	hItem = pTree->InsertItem("* "+str,20,20,pView->m_hTemplateMusic);
	pTree->SetItemData(hItem,(DWORD)lpItem);

	CRSScheduleTemplate rsTemp( pDoc->m_strConnect );
	
	rsTemp.m_strFilter.Format("Type = %d",TYPE_MUSIC);
	rsTemp.m_strSort = "Name";
	rsTemp.Open();
	while( !rsTemp.IsEOF() )
	{
		lpItem = new typeTreeItem;
		lpItem->lID = rsTemp.m_ID;
		lpItem->wType = TYPE_MUSICTEMPLATE;
		
		rsTemp.m_Name.TrimRight();

		hItem = pTree->InsertItem(rsTemp.m_Name,18,18,pView->m_hTemplateMusic);
		pTree->SetItemData(hItem,(DWORD)lpItem);
		pTree->InsertItem("",0,0,hItem);
		rsTemp.MoveNext();
	}

	///////////////////////////////////////////////////////////////////////////
	str.LoadString(IDS_JINGLES);
	pView->m_hTemplateJingles = pTree->InsertItem(str,4,4,hTemplate);
	pTree->SetItemData(pView->m_hTemplateJingles,0);

	lpItem = new typeTreeItem;
	lpItem->lID = 0;
	lpItem->wType = TYPE_JINGLETEMPLATE;

	str.LoadString(IDS_NEW);
	hItem = pTree->InsertItem("* "+str,20,20,pView->m_hTemplateJingles);
	pTree->SetItemData(hItem,(DWORD)lpItem);

	rsTemp.m_strFilter.Format("Type = %d",TYPE_JINGLE);
	rsTemp.m_strSort = "Name";
	rsTemp.Requery();

	while( !rsTemp.IsEOF() )
	{
		lpItem = new typeTreeItem;
		lpItem->lID = rsTemp.m_ID;
		lpItem->wType = TYPE_JINGLETEMPLATE;
		
		rsTemp.m_Name.TrimRight();

		hItem = pTree->InsertItem(rsTemp.m_Name,18,18,pView->m_hTemplateJingles);
		pTree->SetItemData(hItem,(DWORD)lpItem);
		pTree->InsertItem("",0,0,hItem);
		rsTemp.MoveNext();
	}

	///////////////////////////////////////////////////////////////////////////
	//	Jingles
	HTREEITEM	hJingleRoot;
	
	str.LoadString(IDS_JINGLES);
	hJingleRoot = pTree->InsertItem(str,4,4);
	pTree->SetItemData(hJingleRoot,0);

	HTREEITEM	hJingleType,
				hJingle;
	CRSViewJinglesOnAir rsJingle( pDoc->m_strConnect );
	rsJingle.m_strFilter.Format("StartingDate < '%d-%d-%d 23:59:59' AND EndingDate >= '%d-%d-%d'",
		pDoc->m_ScheduleDate.GetYear(),pDoc->m_ScheduleDate.GetMonth(),pDoc->m_ScheduleDate.GetDay(),
		pDoc->m_ScheduleDate.GetYear(),pDoc->m_ScheduleDate.GetMonth(),pDoc->m_ScheduleDate.GetDay() );
	rsJingle.m_strSort = "JingleType,Name";
	rsJingle.Open();

	str="";
	while( !rsJingle.IsEOF() )
	{
		if( rsJingle.m_JingleType!=str )
		{
			lpItem = new typeTreeItem;
			lpItem->lID = 0;
			lpItem->wType = TYPE_JINGLETYPE;

			str=rsJingle.m_JingleType;
			rsJingle.m_JingleType.TrimRight();
			hJingleType=pTree->InsertItem(rsJingle.m_JingleType,14,14,hJingleRoot);
			pTree->SetItemData(hJingleType,(DWORD)lpItem);
		}
		rsJingle.m_Name.TrimRight();
		lpItem = new typeTreeItem;
		lpItem->lID =  rsJingle.m_JingleID;
		lpItem->wType = TYPE_JINGLE;

		hJingle = pTree->InsertItem(rsJingle.m_Name,4,4,hJingleType);
		pTree->SetItemData(hJingle,(DWORD)lpItem);
		rsJingle.MoveNext();
	}
	rsJingle.Close();

	//////////////////////////////////////////////////////////////////////////////
	//	Spots
	HTREEITEM	hSpotRoot;
	
	str.LoadString(IDS_SPONSORS);
	hSpotRoot = pTree->InsertItem(str,1,1);
	pTree->SetItemData(hSpotRoot,0);

	HTREEITEM	hCustomer,
				hSpot;
	CRSViewOnAirSponsors rsSpot( pDoc->m_strConnect );
	rsSpot.m_strFilter.Format("StartingDate < '%d-%d-%d 23:59:59' AND EndingDate >= '%d-%d-%d'",
		pDoc->m_ScheduleDate.GetYear(),pDoc->m_ScheduleDate.GetMonth(),pDoc->m_ScheduleDate.GetDay(),
		pDoc->m_ScheduleDate.GetYear(),pDoc->m_ScheduleDate.GetMonth(),pDoc->m_ScheduleDate.GetDay() );
	rsSpot.m_strSort = "CustomerName,SpotName";
	rsSpot.Open();

	str="";
	while( !rsSpot.IsEOF() )
	{
		if( rsSpot.m_CustomerName!=str )
		{
			lpItem = new typeTreeItem;
			lpItem->lID = 0;
			lpItem->wType = TYPE_CUSTOMER;

			str=rsSpot.m_CustomerName;
			rsSpot.m_CustomerName.TrimRight();
			hCustomer=pTree->InsertItem(rsSpot.m_CustomerName,0,0,hSpotRoot);
			pTree->SetItemData(hCustomer,(DWORD)lpItem);
		}
		rsSpot.m_SpotName.TrimRight();
		lpItem = new typeTreeItem;
		lpItem->lID =  rsSpot.m_SpotID;
		lpItem->wType = TYPE_SPOT;

		hSpot = pTree->InsertItem(rsSpot.m_SpotName,1,1,hCustomer);
		pTree->SetItemData(hSpot,(DWORD)lpItem);
		rsSpot.MoveNext();
	}
	rsSpot.Close();

	//////////////////////////////////////////////////////////////////////////////
	//	RMs
	HTREEITEM	hRMRoot;
	
	str.LoadString(IDS_ONAIRRMS);
	hRMRoot = pTree->InsertItem(str,9,9);
	pTree->SetItemData(hRMRoot,0);

	HTREEITEM	hRMType,
				hRM;
	CRSViewRMsOnAir rsRM( pDoc->m_strConnect );
	rsRM.m_strFilter.Format("StartingDate < '%d-%d-%d 23:59:59' AND EndingDate >= '%d-%d-%d'",
		pDoc->m_ScheduleDate.GetYear(),pDoc->m_ScheduleDate.GetMonth(),pDoc->m_ScheduleDate.GetDay(),
		pDoc->m_ScheduleDate.GetYear(),pDoc->m_ScheduleDate.GetMonth(),pDoc->m_ScheduleDate.GetDay() );
	rsRM.m_strSort = "Type,Name";
	rsRM.Open();

	str="";
	while( !rsRM.IsEOF() )
	{
		if( rsRM.m_Type!=str )
		{
			lpItem = new typeTreeItem;
			lpItem->lID = 0;
			lpItem->wType = TYPE_RMTYPE;

			str=rsRM.m_Type;
			rsRM.m_Type.TrimRight();
			hRMType=pTree->InsertItem(rsRM.m_Type,8,8,hRMRoot);
			pTree->SetItemData(hRMType,(DWORD)lpItem);
		}
		rsRM.m_Name.TrimRight();
		lpItem = new typeTreeItem;
		lpItem->lID =  rsRM.m_RMID;
		lpItem->wType = TYPE_RM;

		hRM = pTree->InsertItem(rsRM.m_Name,9,9,hRMType);
		pTree->SetItemData(hRM,(DWORD)lpItem);
		rsRM.MoveNext();
	}
	rsRM.Close();

	//////////////////////////////////////////////////////////////////////////////
	//	Time Signal
	HTREEITEM	hTimeRoot;
	CString		strFileName;
	
	str.LoadString(IDS_TIMESIGNAL);
	hTimeRoot = pTree->InsertItem(str,2,2);
	pTree->SetItemData(hRMRoot,0);

	HTREEITEM	hTime;
	CRSTime rsTime( g_strMainConnect );
	rsTime.m_strSort = "Name";
	rsTime.Open();

	str="";
	while( !rsTime.IsEOF() )
	{
		rsTime.m_Name.TrimRight();
		lpItem = new typeTreeItem;
		lpItem->lID =  rsTime.m_ID;
		lpItem->wType = TYPE_TIMESIGNAL;

		hTime = pTree->InsertItem(rsTime.m_Name,3,3,hTimeRoot);
		pTree->SetItemData(hTime,(DWORD)lpItem);
		rsTime.MoveNext();
	}
	rsTime.Close();

	/////////////////////////////////////////////////////////////////////////////
	//	Voice Inserts
	HTREEITEM	hVoiceRoot;
	
	str.LoadString(IDS_VOICEINSERT);
	hVoiceRoot = pTree->InsertItem(str,5,5);
	pTree->SetItemData(hVoiceRoot,0);

	HTREEITEM	hUser,
				hVoice;

	str.LoadString(IDS_NEWVOICEINSERT);
	lpItem = new typeTreeItem;
	lpItem->lID = 0;
	lpItem->wType = TYPE_VOICEINSERT;

	hVoice=pTree->InsertItem(str,5,5,hVoiceRoot);
	pTree->SetItemData(hVoice,(DWORD)lpItem);

	CRSViewVoiceInsert rsVoice( pDoc->m_strConnect );
	rsVoice.m_strFilter = "Activ = 1";
	rsVoice.m_strSort = "[User], Name";
	rsVoice.Open();
	str="";

	while( !rsVoice.IsEOF() )
	{
		if( rsVoice.m_User!=str )
		{
			lpItem = new typeTreeItem;
			lpItem->lID = 0;
			lpItem->wType = TYPE_USER;

			str=rsVoice.m_User;
			rsVoice.m_User.TrimRight();
			hUser=pTree->InsertItem(rsVoice.m_User,21,21,hVoiceRoot);
			pTree->SetItemData(hUser,(DWORD)lpItem);
		}
		rsVoice.m_PathName.TrimRight();
		rsVoice.m_FileName.TrimRight();
		strFileName=rsVoice.m_PathName+"\\"+rsVoice.m_FileName;

		if( access(strFileName,0)==0 )
		{
			rsVoice.m_Name.TrimRight();
			lpItem = new typeTreeItem;
			lpItem->lID =  rsVoice.m_ID;
			lpItem->wType = TYPE_VOICEINSERT;

			hVoice = pTree->InsertItem(rsVoice.m_Name,5,5,hUser);
			pTree->SetItemData(hVoice,(DWORD)lpItem);
		}
		else
		{
			CString strSQL;
			strSQL.Format("UPDATE VoiceInserts SET Activ=0 WHERE ID=%d",rsVoice.m_ID);
			rsVoice.m_pDatabase->ExecuteSQL(strSQL);
		}
		rsVoice.MoveNext();
	}
	rsVoice.Close();


	hItem = pTree->InsertItem("",0,0);
	pTree->DeleteItem(hItem);
	return 0;
}

void CScheduleLeftView::OnExpanding( HTREEITEM hItem )
{
	if( hItem == NULL ) return;
	
	CTreeCtrl		*pTree = &GetTreeCtrl();
	typeTreeItem	*lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

	if( lpItem== NULL ) return;

	if( (lpItem->wType==TYPE_MUSICTEMPLATE) && (lpItem->lID!=0) )
		ExpandMusicTemplate(hItem,lpItem->lID);

	if( (lpItem->wType==TYPE_JINGLETEMPLATE) && (lpItem->lID!=0) )
		ExpandJingleTemplate(hItem,lpItem->lID);
}

void CScheduleLeftView::ExpandMusicTemplate( HTREEITEM hItem, long lID )
{
	CSchedulerDoc	*pDoc = (CSchedulerDoc *)m_pDocument;
	CTreeCtrl		*pTree = &GetTreeCtrl();

	DeleteAllChildItems( hItem );
	CRSScheduleTemplate rs( pDoc->m_strConnect );
	rs.m_strFilter.Format("ID = %d",lID);
	rs.Open();
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}

	rs.m_strSQL.TrimRight();

	CRSViewMusicTracksOnAir rsMusic( pDoc->m_strConnect );
	rsMusic.m_strFilter = rs.m_strSQL;
	rsMusic.m_strSort = "ArtistName, TrackTitle";
	rsMusic.Open();

	HTREEITEM	hArtist,
				hSong;
	CString		strPrev="";
	typeTreeItem *lpItem;

	while( !rsMusic.IsEOF() )
	{
		if( strPrev!=rsMusic.m_ArtistName )
		{
			strPrev = rsMusic.m_ArtistName;
			rsMusic.m_ArtistName.TrimRight();
			
			lpItem = new typeTreeItem;
			lpItem->lID = 0;
			lpItem->wType = TYPE_ARTIST;

			hArtist = pTree->InsertItem(rsMusic.m_ArtistName,16,16,hItem);
			pTree->SetItemData(hArtist,(DWORD)lpItem);
		}

		lpItem = new typeTreeItem;
		lpItem->lID = rsMusic.m_TrackID;
		lpItem->wType = TYPE_MUSIC;
		rsMusic.m_TrackTitle.TrimRight();

		hSong = pTree->InsertItem(rsMusic.m_TrackTitle,17,17,hArtist);
		pTree->SetItemData(hSong,(DWORD)lpItem);

		rsMusic.MoveNext();
	}
	rs.Close();
	rsMusic.Close();
}

void CScheduleLeftView::ExpandJingleTemplate( HTREEITEM hItem, long lID )
{
	CSchedulerDoc	*pDoc = (CSchedulerDoc *)m_pDocument;
	CTreeCtrl		*pTree = &GetTreeCtrl();

	DeleteAllChildItems( hItem );
	CRSScheduleTemplate rs( pDoc->m_strConnect );
	rs.m_strFilter.Format("ID = %d",lID);
	rs.Open();

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}

	rs.m_strSQL.TrimRight();

	CRSViewJinglesOnAir rsJingle( pDoc->m_strConnect );
	rsJingle.m_strFilter = rs.m_strSQL;
	rsJingle.m_strSort = "JingleType, Name";
	rsJingle.Open();

	HTREEITEM	hType,
				hJingle;
	CString		strPrev="";
	typeTreeItem *lpItem;

	while( !rsJingle.IsEOF() )
	{
		if( strPrev!=rsJingle.m_JingleType)
		{
			strPrev = rsJingle.m_JingleType;
			rsJingle.m_JingleType.TrimRight();
			
			lpItem = new typeTreeItem;
			lpItem->lID = 0;
			lpItem->wType = TYPE_JINGLETYPE;

			hType = pTree->InsertItem(rsJingle.m_JingleType,14,14,hItem);
			pTree->SetItemData(hType,(DWORD)lpItem);
		}

		lpItem = new typeTreeItem;
		lpItem->lID = rsJingle.m_JingleID;
		lpItem->wType = TYPE_JINGLE;
		rsJingle.m_Name.TrimRight();

		hJingle = pTree->InsertItem(rsJingle.m_Name,4,4,hType);
		pTree->SetItemData(hJingle,(DWORD)lpItem);

		rsJingle.MoveNext();
	}
	rs.Close();
	rsJingle.Close();
}

void CScheduleLeftView::OnDoubleClick()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem == NULL ) return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	
	if( lpItem==NULL ) return;

	if( lpItem->wType == TYPE_MUSICTEMPLATE)
	{
		if( lpItem->lID==0 )
			AddMusicTemplate( hItem );
		else
			EditMusicTemplate( hItem );
	}
	else if( lpItem->wType==TYPE_JINGLETEMPLATE )
	{
		if( lpItem->lID==0 )
			AddJingleTemplate( hItem );
		else
			EditJingleTemplate( hItem );
	}
	else if( lpItem->wType==TYPE_VOICEINSERT )
	{
		if( lpItem->lID==0 )
			AddVoiceInsert(hItem);
		else
			EditVoiceInsert(hItem);
	}
}


void CScheduleLeftView::AddMusicTemplate( HTREEITEM hItem )
{
	if( !g_Permissions.bCriteriaAdd )
		return;

	CSchedulerDoc *pDoc = (CSchedulerDoc *)GetDocument();

	CMusicTemplate dl;
	dl.m_strConnect = pDoc->m_strConnect;

	if( dl.DoModal()==IDOK )
	{
		CRSScheduleTemplate rs( pDoc->m_strConnect );
		rs.m_strSort="ID DESC";
		rs.Open();
		rs.AddNew();

		rs.m_Category = dl.m_CategoryID;
		rs.m_Expression = dl.m_ExpressionID;
		rs.m_MaxLen = dl.m_MaxLen;
		rs.m_MaxRythm = dl.m_MaxRythm;
		rs.m_Name = dl.m_strName;
		rs.m_MinLen = dl.m_MinLen;
		rs.m_MinRythm = dl.m_MinRythm;
		rs.m_PlayList = dl.m_PlayListID;
		rs.m_Type = TYPE_MUSIC;
		rs.m_strSQL = dl.m_strSQL;
		rs.m_ArtistQuarantine = dl.m_nArtistQuarantine;
		rs.m_SongQuarantine = dl.m_nSongQuarantine;
		rs.m_RandomFactor = dl.m_nRandom;

		rs.Update();
		rs.Requery();

		typeTreeItem *lpNewItem = new typeTreeItem;
		lpNewItem->lID = rs.m_ID;
		lpNewItem->wType = TYPE_MUSICTEMPLATE;

		CTreeCtrl *pTree = &GetTreeCtrl();
		HTREEITEM hNewItem = pTree->InsertItem(dl.m_strName,18,18,pTree->GetParentItem(hItem));
		pTree->SetItemData(hNewItem,(DWORD)lpNewItem);
		pTree->InsertItem("",18,18,hNewItem);
	}
}

void CScheduleLeftView::EditMusicTemplate( HTREEITEM hItem )
{
	if( !g_Permissions.bCriteriaEdit )
		return;

	CSchedulerDoc *pDoc = (CSchedulerDoc *)GetDocument();
	CTreeCtrl *pTree = &GetTreeCtrl();
	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	
	CRSViewSchedulingTemplate rs( pDoc->m_strConnect );
	rs.m_strFilter.Format("ID = %d",lpItem->lID );
	rs.Open();

	if( rs.GetRecordCount() != 0 )
	{
		CMusicTemplate dl;
		
		rs.m_Name.TrimRight();
		rs.m_CategoryName.TrimRight();
		rs.m_ExpressionName.TrimRight();
		rs.m_PlayListName.TrimRight();

		dl.m_strCategory = rs.m_CategoryName;
		dl.m_CategoryID = rs.m_Category;
		dl.m_strExpression = rs.m_ExpressionName;
		dl.m_ExpressionID = rs.m_Expression;
		dl.m_strPlayList = rs.m_PlayListName;
		dl.m_PlayListID = rs.m_PlayList;
		dl.m_MaxLen = rs.m_MaxLen;
		dl.m_MaxRythm = rs.m_MaxRythm;
		dl.m_MinLen = rs.m_MinLen;
		dl.m_MinRythm = rs.m_MinRythm;
		dl.m_strName = rs.m_Name;
		dl.m_strConnect = pDoc->m_strConnect;
		dl.m_TemplateID = rs.m_ID;
		dl.m_nArtistQuarantine = rs.m_ArtistQuarantine;
		dl.m_nSongQuarantine = rs.m_SongQuarantine;
		dl.m_nRandom = rs.m_RandomFactor;
		
		rs.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSScheduleTemplate rsTemp( pDoc->m_strConnect );
			rsTemp.m_strFilter.Format( "ID = %d",dl.m_TemplateID );
			rsTemp.Open();
			if( rsTemp.GetRecordCount()!=0 )
			{
				rsTemp.Edit();

				rsTemp.m_Category = dl.m_CategoryID;
				rsTemp.m_Expression = dl.m_ExpressionID;
				rsTemp.m_MaxLen = dl.m_MaxLen;
				rsTemp.m_MaxRythm = dl.m_MaxRythm;
				rsTemp.m_MinLen = dl.m_MinLen;
				rsTemp.m_MinRythm = dl.m_MinRythm;
				rsTemp.m_Name = dl.m_strName;
				rsTemp.m_PlayList = dl.m_PlayListID;
				rsTemp.m_strSQL = dl.m_strSQL;
				rsTemp.m_Type = TYPE_MUSIC;
				rsTemp.m_SongQuarantine = dl.m_nSongQuarantine;
				rsTemp.m_ArtistQuarantine = dl.m_nArtistQuarantine;
				rsTemp.m_RandomFactor = dl.m_nRandom;

				rsTemp.Update();

				pTree->SetItemText(hItem,dl.m_strName);
			}
			rsTemp.Close();
		}
	}
	else
		rs.Close();
}

void CScheduleLeftView::AddJingleTemplate( HTREEITEM hItem )
{
	if( !g_Permissions.bCriteriaAdd )
		return;

	CSchedulerDoc *pDoc = (CSchedulerDoc *)GetDocument();

	CJingleTemplate dl;
	
	dl.m_strConnect = pDoc->m_strConnect;
	dl.m_Date = pDoc->m_ScheduleDate;

	if( dl.DoModal() == IDOK )
	{
		CRSScheduleTemplate rs( pDoc->m_strConnect );
		rs.m_strSort="ID DESC";
		rs.Open();
		rs.AddNew();

		rs.m_Category = dl.m_CategoryID;
		rs.m_Expression = 0;
		rs.m_MaxLen = dl.m_MaxLen;
		rs.m_MaxRythm = dl.m_MaxRythm;
		rs.m_Name = dl.m_strName;
		rs.m_MinLen = dl.m_MinLen;
		rs.m_MinRythm = dl.m_MinRythm;
		rs.m_PlayList = 0;
		rs.m_Type = TYPE_JINGLE;
		rs.m_strSQL = dl.m_strSQL;
		rs.Update();
		rs.Requery();

		typeTreeItem *lpNewItem = new typeTreeItem;
		lpNewItem->lID = rs.m_ID;
		lpNewItem->wType = TYPE_JINGLETEMPLATE;

		CTreeCtrl *pTree = &GetTreeCtrl();
		HTREEITEM hNewItem = pTree->InsertItem(dl.m_strName,18,18,pTree->GetParentItem(hItem));
		pTree->SetItemData(hNewItem,(DWORD)lpNewItem);
		pTree->InsertItem("",18,18,hNewItem);
	}
}

void CScheduleLeftView::EditJingleTemplate( HTREEITEM hItem )
{
	if( !g_Permissions.bCriteriaEdit )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	CSchedulerDoc	*pDoc = (CSchedulerDoc *)GetDocument();
	typeTreeItem	*lpItem = (typeTreeItem*)pTree->GetItemData(hItem);
	CRSViewScheduleJingleTemplate rs( pDoc->m_strConnect );
	rs.m_strFilter.Format("ID = %d",lpItem->lID );
	rs.Open();

	if( rs.GetRecordCount()!=0 )
	{
		CJingleTemplate dl;

		dl.m_strConnect = pDoc->m_strConnect;
		dl.m_strName = rs.m_Name; dl.m_strName.TrimRight();
		dl.m_strType = rs.m_TypeName; dl.m_strType.TrimRight();
		dl.m_CategoryID = rs.m_TypeID;
		dl.m_Date = pDoc->m_ScheduleDate;
		dl.m_MaxLen = rs.m_MaxLen;
		dl.m_MaxRythm = rs.m_MaxRythm;
		dl.m_MinLen = rs.m_MinLen;
		dl.m_MinRythm = rs.m_MinRythm;
		dl.m_TemplateID = rs.m_ID;
		
		rs.Close();
		if( dl.DoModal()==IDOK )
		{
			CRSScheduleTemplate rsTemp( pDoc->m_strConnect );
			rsTemp.m_strFilter.Format( "ID = %d",dl.m_TemplateID );
			rsTemp.Open();

			if( rsTemp.GetRecordCount()!=0 )
			{
				rsTemp.Edit();

				rsTemp.m_Category = dl.m_CategoryID;
				rsTemp.m_Expression = 0;
				rsTemp.m_MaxLen = dl.m_MaxLen;
				rsTemp.m_MaxRythm = dl.m_MaxRythm;
				rsTemp.m_MinLen = dl.m_MinLen;
				rsTemp.m_MinRythm = dl.m_MinRythm;
				rsTemp.m_Name = dl.m_strName;
				rsTemp.m_PlayList = 0;
				rsTemp.m_strSQL = dl.m_strSQL;
				rsTemp.m_Type = TYPE_JINGLE;

				rsTemp.Update();

				pTree->SetItemText(hItem,dl.m_strName);
			}
			rsTemp.Close();
		}
	}
	else
		rs.Close();
}

void CScheduleLeftView::AddVoiceInsert( HTREEITEM hItem )
{
	if( !g_Permissions.bVoiceAdd )
		return;

	CSchedulerDoc *pDoc = (CSchedulerDoc *)GetDocument();
	CVoiceInsert dl;
	
	dl.m_strConnect = pDoc->m_strConnect;
	if( dl.DoModal()==TRUE )
	{
		CRSVoiceInsert rs( pDoc->m_strConnect );
		rs.m_strSort = "ID DESC";
		rs.Open();

		rs.AddNew();

		rs.m_Activ = 1;
		rs.m_FileName = dl.m_strFileName;
		rs.m_Finish = dl.m_End;
		rs.m_Name = dl.m_strName;
		rs.m_Path = dl.m_PathID;
		rs.m_Start = dl.m_Start;
		rs.m_TalentID = dl.m_UserID;

		rs.Update();
		rs.Requery();

		CTreeCtrl *pTree = &GetTreeCtrl();
		HTREEITEM hVoiceRoot = pTree->GetParentItem(hItem);

		HTREEITEM hUser = FindChildString(hVoiceRoot,dl.m_strUser);
		if( hUser==NULL )
		{
			hUser = pTree->InsertItem(dl.m_strUser,21,21,hVoiceRoot);
			pTree->SetItemData(hUser,0);
		}
		typeTreeItem *lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_VOICEINSERT;

		HTREEITEM hVoice = pTree->InsertItem(dl.m_strName,5,5,hUser);
		pTree->SetItemData(hVoice,(DWORD)lpItem);
	}
}

void CScheduleLeftView::EditVoiceInsert( HTREEITEM hItem )
{
	if( !g_Permissions.bVoiceEdit )
		return;

	CSchedulerDoc	*pDoc = (CSchedulerDoc *)GetDocument();
	CTreeCtrl		*pTree = &GetTreeCtrl();
	typeTreeItem	*lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

	CRSViewVoiceInsert rsView( pDoc->m_strConnect);
	rsView.m_strFilter.Format("ID = %d",lpItem->lID );
	rsView.Open();

	if( rsView.GetRecordCount()!=0 )
	{
		CVoiceInsert dl;

		dl.m_strConnect = pDoc->m_strConnect;
		dl.m_End = rsView.m_Finish;
		dl.m_ID = rsView.m_ID;
		dl.m_PathID = rsView.m_Path;
		dl.m_Start = rsView.m_Start;
		dl.m_strFileName = rsView.m_FileName; dl.m_strFileName.TrimRight();
		dl.m_strName = rsView.m_Name; dl.m_strName.TrimRight();
		dl.m_strPath = rsView.m_PathName; dl.m_strPath.TrimRight();
		dl.m_strUser = rsView.m_User; dl.m_strUser.TrimRight();
		dl.m_UserID = rsView.m_TalentID;
		rsView.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSVoiceInsert rs( pDoc->m_strConnect );
			rs.m_strFilter.Format("ID = %d",lpItem->lID);
			rs.Open();

			if( rs.GetRecordCount() )
			{
				rs.Edit();

				rs.m_Activ = 1;
				rs.m_FileName = dl.m_strFileName;
				rs.m_Finish = dl.m_End;
				rs.m_Name = dl.m_strName;
				rs.m_Path = dl.m_PathID;
				rs.m_Start = dl.m_Start;
				rs.m_TalentID = dl.m_UserID;

				rs.Update();

				HTREEITEM hVoiceRoot = pTree->GetParentItem( pTree->GetParentItem(hItem) );
				pTree->DeleteItem(hItem);

				HTREEITEM hUser = FindChildString(hVoiceRoot,dl.m_strUser);

				if( hUser==NULL )
				{
					hUser = pTree->InsertItem(dl.m_strUser,8,8,hVoiceRoot);
					pTree->SetItemData(hUser,0);
				}

				HTREEITEM hVoice = pTree->InsertItem(dl.m_strName,5,5,hUser);
				pTree->SetItemData(hVoice,(DWORD)lpItem);
			}
			rs.Close();
		}
	}
	else
		rsView.Close();
}

void CScheduleLeftView::OnPFL()
{
	CSchedulerDoc *pDoc = (CSchedulerDoc *)GetDocument();
	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem= pTree->GetSelectedItem();

	if( hItem==NULL ) return;

	typeTreeItem *pItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( pItem==NULL ) return;

	if( pItem->lID==0 ) return;

	if( (pItem->wType!=TYPE_MUSIC) && 
		(pItem->wType!=TYPE_JINGLE) &&
		(pItem->wType!=TYPE_SPOT) && 
		(pItem->wType!=TYPE_RM) &&
		(pItem->wType!=TYPE_VOICEINSERT) ) return;

	g_wndPFL->SetSound(pItem->wType,pItem->lID,pDoc->m_strConnect);
	g_wndPFL->RestoreWindow();
}

void CScheduleLeftView::OnCut()
{
	CSchedulerDoc *pDoc = (CSchedulerDoc *)GetDocument();
	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem= pTree->GetSelectedItem();

	if( hItem==NULL ) return;

	typeTreeItem *pItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( pItem==NULL ) return;

	if( pItem->lID==0 ) return;
	
	if( pItem->wType==TYPE_MUSICTEMPLATE )
	{
		if( !g_Permissions.bCriteriaCut )
			return;

		if( AfxMessageBox(IDS_CONFIRMMUSICTEMPLATEREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase db;
			CString strSQL;

			strSQL.Format("DELETE FROM SchedulingTemplate WHERE ID = '%d'",pItem->lID);
			db.Open(pDoc->m_strConnect);
			db.ExecuteSQL(strSQL);

			strSQL.Format("UPDATE Scheduling SET TemplateID = 0 WHERE TemplateID = '%d'",pItem->lID);
			db.ExecuteSQL(strSQL);

			pTree->DeleteItem(hItem);
		}
	}

	if( pItem->wType==TYPE_JINGLETEMPLATE )
	{
		if( !g_Permissions.bCriteriaCut )
			return;

		if( AfxMessageBox(IDS_CONFIRMJINGLETEMPLATEREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase db;
			CString strSQL;

			strSQL.Format("DELETE FROM SchedulingTemplate WHERE ID = '%d'",pItem->lID);
			db.Open(pDoc->m_strConnect);
			db.ExecuteSQL(strSQL);

			strSQL.Format("UPDATE Scheduling SET TemplateID = 0 WHERE TemplateID = '%d'",pItem->lID);
			db.ExecuteSQL(strSQL);

			pTree->DeleteItem(hItem);
		}
	}

	if( pItem->wType==TYPE_VOICEINSERT )
	{
		if( !g_Permissions.bVoiceCut )
			return;

		if( AfxMessageBox(IDS_CONFIRMVOICEINSERTREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase db;
			CString strSQL;

			strSQL.Format("UPDATE VoiceInserts SET Activ = 0 WHERE ID = '%d'",pItem->lID);
			db.Open(pDoc->m_strConnect);
			db.ExecuteSQL(strSQL);

			pTree->DeleteItem(hItem);
		}
	}
}

void CScheduleLeftView::OnRDoubleClick()
{
	OnPFL();
}

void CScheduleLeftView::OnRButtonDblClk()
{
	OnPFL();
}
