// DigitalLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\DigitalLeftView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList	*g_ilTree;
extern UINT			g_nFormat;
/////////////////////////////////////////////////////////////////////////////
// CDigitalLeftView

IMPLEMENT_DYNCREATE(CDigitalLeftView, CTreeView)

CDigitalLeftView::CDigitalLeftView()
{
	m_lpDragItem=NULL;
}

CDigitalLeftView::~CDigitalLeftView()
{
}


BEGIN_MESSAGE_MAP(CDigitalLeftView, CTreeView)
	//{{AFX_MSG_MAP(CDigitalLeftView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRDblclk)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitalLeftView drawing

void CDigitalLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDigitalLeftView diagnostics

#ifdef _DEBUG
void CDigitalLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDigitalLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDigitalLeftView message handlers

int CDigitalLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CTreeCtrl *pTree = &GetTreeCtrl();

	pTree->SetImageList(g_ilTree,TVSIL_NORMAL);
	pTree->SetImageList(g_ilTree,TVSIL_STATE);

	long Styles=GetWindowLong(pTree->m_hWnd,GWL_STYLE);
	SetWindowLong(pTree->m_hWnd,GWL_STYLE,Styles|TVS_SHOWSELALWAYS|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT);
	
	m_DropTarget.Register(this);

	return 0;
}

void CDigitalLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnSelChange();

	*pResult = 0;
}

void CDigitalLeftView::OnSelChange()
{
}

void CDigitalLeftView::SetView(CString strURL)
{
	CSplitterWnd	*pSplitter = (CSplitterWnd *)GetParent();
	CHtmlView		*pView = (CHtmlView *)pSplitter->GetPane(0,1);

	pView->Navigate2(strURL);
}

void CDigitalLeftView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnDoubleClick();
	
	*pResult = 0;
}

void CDigitalLeftView::OnDoubleClick()
{
}

void CDigitalLeftView::OnRDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnRDoubleClick();
	*pResult = 0;
}

void CDigitalLeftView::OnRDoubleClick()
{
}

HTREEITEM CDigitalLeftView::FindString(CString str)
{
	CTreeCtrl		*pTree=&GetTreeCtrl();
	HTREEITEM		hItem=pTree->GetNextItem(NULL,TVGN_CHILD);
	CString strTemp;

	str.MakeUpper();

	while( hItem!=NULL )
	{
		strTemp=pTree->GetItemText(hItem);
		strTemp.MakeUpper();
		if( strTemp>=str )
			break;

		hItem=pTree->GetNextItem(hItem,TVGN_NEXT);
	}

	if( strTemp==str )
		return hItem;
	
	return NULL;
}

HTREEITEM CDigitalLeftView::FindChildString(HTREEITEM hParent,CString str)
{
	CTreeCtrl		*pTree=&GetTreeCtrl();
	HTREEITEM		hItem=pTree->GetChildItem(hParent);
	CString strTemp;

	str.MakeUpper();

	while( hItem!=NULL )
	{
		strTemp=pTree->GetItemText(hItem);
		strTemp.MakeUpper();
		if( strTemp>=str )
			break;

		hItem=pTree->GetNextItem(hItem,TVGN_NEXT);
	}

	if( strTemp==str )
		return hItem;
	
	return NULL;
}

void CDigitalLeftView::DrawDragItem(char *strName,CPoint point)
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

void CDigitalLeftView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
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

	HANDLE		hData=::GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,sizeof(typeTreeDrag));
	typeTreeDrag	*lpItemDrag=(typeTreeDrag *)::GlobalLock(hData);
	CString		strTemp = pTree->GetItemText(hItem);
	lpItemDrag->Item.lID=lpItem->lID;
	lpItemDrag->Item.wType=lpItem->wType;
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

DROPEFFECT CDigitalLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{

	return (DROPEFFECT_NONE);
}

void CDigitalLeftView::OnDragLeave() 
{
	if( m_lpDragItem == NULL )
		return ;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;
	m_lpDragItem=NULL;
	
}

DROPEFFECT CDigitalLeftView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( m_lpDragItem == NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint=point;
	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
		
	return ( DROPEFFECT_COPY );
}

BOOL CDigitalLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CTreeView::OnDrop(pDataObject, dropEffect, point);
}

void CDigitalLeftView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnExpanding(pNMTreeView->itemNew.hItem);

	*pResult = 0;
}

void CDigitalLeftView::DeleteAllChildItems(HTREEITEM hItem)
{
	CTreeCtrl	*pTree=&GetTreeCtrl();
	
	while( pTree->ItemHasChildren(hItem) )
		pTree->DeleteItem(pTree->GetChildItem(hItem));
}