// TextOnAirLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "TextOnAirLeftView.h"
#include "..\include\RSViewNewsOnAir.h"
#include "..\include\RSViewNews.h"
#include "..\include\TimeSpanDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	UINT	g_nFormat;
extern	CString	g_strMainConnect;
extern	CString g_strBaseURL;

/////////////////////////////////////////////////////////////////////////////
// CTextOnAirLeftView

IMPLEMENT_DYNCREATE(CTextOnAirLeftView, CDigitalLeftView)

CTextOnAirLeftView::CTextOnAirLeftView()
{
}

CTextOnAirLeftView::~CTextOnAirLeftView()
{
}


BEGIN_MESSAGE_MAP(CTextOnAirLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CTextOnAirLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextOnAirLeftView drawing

void CTextOnAirLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTextOnAirLeftView diagnostics

#ifdef _DEBUG
void CTextOnAirLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CTextOnAirLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextOnAirLeftView message handlers

DROPEFFECT CTextOnAirLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( m_lpDragItem->Item.wType != TYPE_TEXT )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	return DROPEFFECT_COPY;
}

BOOL CTextOnAirLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CRSViewNewsOnAir	rs( m_strConnect );

	rs.m_strFilter.Format("NewsID = %d",m_lpDragItem->Item.lID);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		rs.Close();
		AfxMessageBox(IDS_TEXTALLREADYEXISTS);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}
	else
	{
		CRSViewNews rsNews(g_strMainConnect);
		rsNews.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rsNews.Open();
		rsNews.m_Type.TrimRight();
		rsNews.m_Name.TrimRight();

		CTimeSpanDefinition dl;
		dl.m_Name = rsNews.m_Name;
		dl.m_Type = rsNews.m_Type;

		if( dl.DoModal()==IDOK )
		{
			CString		strSQL;
			CDatabase	db;
			db.Open(m_strConnect);
			
			strSQL.Format("INSERT INTO NewsOnAir (NewsID, StartingDate, EndingDate) VALUES ('%d', '%d-%d-%d', '%d-%d-%d')",
				m_lpDragItem->Item.lID,
				dl.m_StartingDate.GetYear(),dl.m_StartingDate.GetMonth(),dl.m_StartingDate.GetDay(),
				dl.m_EndingDate.GetYear(),dl.m_EndingDate.GetMonth(),dl.m_EndingDate.GetDay() );
			db.ExecuteSQL(strSQL);
			db.Close();
		}
		else
			return DROPEFFECT_NONE;
		
		CTreeCtrl *pTree=&GetTreeCtrl();
		HTREEITEM hType = FindString(rsNews.m_Type);
		if( hType==NULL )
		{
			typeTreeItem *lpItem=new typeTreeItem;
			lpItem->lID=rsNews.m_ID;
			lpItem->wType=TYPE_RMTYPE;

			hType=pTree->InsertItem(rsNews.m_Type,10,10);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
			pTree->SetItemData(hType,(DWORD)lpItem);
			pTree->SortChildren(NULL);
		}

		CRSViewNewsOnAir	rsOnAir( m_strConnect );
		rsOnAir.m_strSort="ID Desc";
		rsOnAir.Open();

		typeTreeItem *lpItem=new typeTreeItem;
		lpItem->lID=rsOnAir.m_ID;
		lpItem->wType=TYPE_TEXT;
	
		HTREEITEM hRM= pTree->InsertItem(dl.m_Name,11,11,hType);
		pTree->SetItemData(hRM,(DWORD)lpItem);
		pTree->EnsureVisible(hRM);

		rsNews.Close();
		rsOnAir.Close();
	}

	m_lpDragItem=NULL;
	return DROPEFFECT_COPY;
}

void CTextOnAirLeftView::OnDoubleClick()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_TEXT )
	{
		CRSViewNewsOnAir rsView( m_strConnect );
		rsView.m_strFilter.Format("ID = %d",lpItem->lID);
		rsView.Open();

		if( rsView.GetRecordCount() )
		{
			CTimeSpanDefinition dl;
			
			rsView.m_Name.TrimRight();
			rsView.m_Type.TrimRight();

			dl.m_Type= rsView.m_Type;
			dl.m_Name	= rsView.m_Name;
			dl.m_StartingDate = rsView.m_StartingDate;
			dl.m_EndingDate = rsView.m_EndingDate;

			if( dl.DoModal()==IDOK )
			{
				rsView.Close();

				CDatabase	db;
				CString		strSQL;

				strSQL.Format("UPDATE NewsOnAir SET StartingDate='%d-%d-%d',EndingDate='%d-%d-%d' WHERE ID=%d",
					dl.m_StartingDate.GetYear(),dl.m_StartingDate.GetMonth(),dl.m_StartingDate.GetDay(),
					dl.m_EndingDate.GetYear(),dl.m_EndingDate.GetMonth(),dl.m_EndingDate.GetDay(),
					lpItem->lID);

				db.Open(m_strConnect);
				db.ExecuteSQL(strSQL);
				db.Close();
			}
			else
				rsView.Close();
		}
	}
}

void CTextOnAirLeftView::OnCut() 
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_TEXT )
	{
		if( AfxMessageBox(IDS_CONFIRMTEXTREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE FROM NewsOnAir WHERE ID = '%d'",lpItem->lID);
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);
			db.Close();
			pTree->DeleteItem(hItem);
		}
	}
}

void CTextOnAirLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	CString str;
	str.LoadString(IDS_ONAIRTEXT);

	m_pDocument->SetTitle(str+" - "+m_strRadio);

	AfxBeginThread(RefreshList,(LPVOID)this);	
}

UINT CTextOnAirLeftView::RefreshList(LPVOID lp)
{
	CTextOnAirLeftView *pView = (CTextOnAirLeftView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	CRSViewNewsOnAir	rs( pView->m_strConnect );
	CString		strPrev;
	HTREEITEM	hType,
				hRM;
	typeTreeItem *lpItem;

	rs.m_strSort = "Type, Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Type )
		{
			strPrev = rs.m_Type;
			rs.m_Type.TrimRight();

			hType = pTree->InsertItem(rs.m_Type,10,10);
			pTree->SetItemData(hType,0);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_TEXT;

		hRM = pTree->InsertItem(rs.m_Name,11,11,hType);
		pTree->SetItemData(hRM,(DWORD)lpItem);

		rs.MoveNext();
	}

	hType=pTree->InsertItem("w",0,0);
	pTree->DeleteItem(hType);

	return 0;
}

void CTextOnAirLeftView::OnSelChange()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
	{
		SetView(g_strBaseURL+"\\EmptyPage.asp");
		return;
	}

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
	{
		SetView(g_strBaseURL+"\\EmptyPage.asp");
		return;
	}

	if( lpItem->wType==TYPE_TEXT )
	{
		CString str;

		str.Format("%s\\NewsOnAirInfo.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,m_strDB);
		SetView(str);
	}
}
