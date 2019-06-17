// RMsOnAirLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "RMsOnAirLeftView.h"
#include "..\include\TimeSpanDefinition.h"
#include "..\include\RSViewRms.h"
#include "..\include\RSViewRMsOnAir.h"
#include "..\include\RSRMsOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT		g_nFormat;
extern CString	g_strMainConnect;
extern CString	g_strBaseURL; 
/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirLeftView

IMPLEMENT_DYNCREATE(CRMsOnAirLeftView, CDigitalLeftView)

CRMsOnAirLeftView::CRMsOnAirLeftView()
{
}

CRMsOnAirLeftView::~CRMsOnAirLeftView()
{
}


BEGIN_MESSAGE_MAP(CRMsOnAirLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CRMsOnAirLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirLeftView drawing

void CRMsOnAirLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirLeftView diagnostics

#ifdef _DEBUG
void CRMsOnAirLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CRMsOnAirLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRMsOnAirLeftView message handlers

void CRMsOnAirLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();

	CString str;
	str.LoadString(IDS_ONAIRRMS);
	m_pDocument->SetTitle(str+" - "+m_strRadio);

	AfxBeginThread(RefreshList,(LPVOID)this);
	
}

UINT CRMsOnAirLeftView::RefreshList(LPVOID lp)
{
	CRMsOnAirLeftView *pView = (CRMsOnAirLeftView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	CRSViewRMsOnAir	rs( pView->m_strConnect );
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

			hType = pTree->InsertItem(rs.m_Type,8,8);
			pTree->SetItemData(hType,0);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_RM;

		hRM = pTree->InsertItem(rs.m_Name,9,9,hType);
		pTree->SetItemData(hRM,(DWORD)lpItem);

		rs.MoveNext();
	}

	hType=pTree->InsertItem("w",0,0);
	pTree->DeleteItem(hType);

	return 0;

}

DROPEFFECT CRMsOnAirLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( m_lpDragItem->Item.wType != TYPE_RM )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	return DROPEFFECT_COPY;
}

BOOL CRMsOnAirLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CRSViewRMsOnAir	rs( m_strConnect );

	rs.m_strFilter.Format("RMID = %d",m_lpDragItem->Item.lID);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		rs.Close();
		AfxMessageBox(IDS_RMALLREADYEXISTS);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}
	else
	{
		CRSViewRms rsRM(g_strMainConnect);
		rsRM.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rsRM.Open();
		rsRM.m_Type.TrimRight();
		rsRM.m_Name.TrimRight();

		CTimeSpanDefinition dl;
		dl.m_Name = rsRM.m_Name;
		dl.m_Type = rsRM.m_Type;

		if( dl.DoModal()==IDOK )
		{
			CString		strSQL;
			CDatabase	db;
			db.Open(m_strConnect);
			
			strSQL.Format("INSERT INTO RMsOnAir (RMID, StartingDate, EndingDate) VALUES ('%d', '%d-%d-%d', '%d-%d-%d')",
				m_lpDragItem->Item.lID,
				dl.m_StartingDate.GetYear(),dl.m_StartingDate.GetMonth(),dl.m_StartingDate.GetDay(),
				dl.m_EndingDate.GetYear(),dl.m_EndingDate.GetMonth(),dl.m_EndingDate.GetDay() );
			db.ExecuteSQL(strSQL);
			db.Close();
		}
		
		CTreeCtrl *pTree=&GetTreeCtrl();
		HTREEITEM hType = FindString(rsRM.m_Type);
		if( hType==NULL )
		{
			typeTreeItem *lpItem=new typeTreeItem;
			lpItem->lID=rsRM.m_ID;
			lpItem->wType=TYPE_RMTYPE;

			hType=pTree->InsertItem(rsRM.m_Type,8,8);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
			pTree->SetItemData(hType,(DWORD)lpItem);
			pTree->SortChildren(NULL);
		}

		CRSViewRMsOnAir		rsOnAir( m_strConnect );
		rsOnAir.m_strSort = "ID Desc";
		rsOnAir.Open();

		typeTreeItem *lpItem=new typeTreeItem;
		lpItem->lID=rsOnAir.m_ID;
		lpItem->wType=TYPE_RM;
	
		HTREEITEM hRM= pTree->InsertItem(dl.m_Name,9,9,hType);
		pTree->SetItemData(hRM,(DWORD)lpItem);
		pTree->EnsureVisible(hRM);

		rsRM.Close();
	}

	m_lpDragItem=NULL;
	return DROPEFFECT_COPY;
}

void CRMsOnAirLeftView::OnDoubleClick()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_RM )
	{
		CRSViewRMsOnAir rsView( m_strConnect );
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

				CRSRMsOnAir rs( m_strConnect );
				rs.m_strFilter.Format("ID = %d",lpItem->lID);
				rs.Open();
				if( rs.GetRecordCount() )
				{
					rs.Edit();
					rs.m_StartingDate = dl.m_StartingDate;
					rs.m_EndingDate = dl.m_EndingDate;
					rs.Update();
				}
				rs.Close();
			}
			else
				rsView.Close();
		}
	}
}

void CRMsOnAirLeftView::OnSelChange()
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

	if( lpItem->wType==TYPE_RM )
	{
		CString str;

		str.Format("%s\\RMOnAir.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,m_strDB);
		SetView(str);
	}
}

void CRMsOnAirLeftView::OnCut() 
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_RM )
	{
		if( AfxMessageBox(IDS_CONFIRMRMREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE FROM RMsOnAir WHERE ID = '%d'",lpItem->lID);
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);
			db.Close();
			pTree->DeleteItem(hItem);
		}
	}
}