// RMLineUpLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "RMLineUpLeftView.h"
#include "LineUpName.h"
#include "..\include\RSCartwallDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpLeftView

IMPLEMENT_DYNCREATE(CRMLineUpLeftView, CDigitalLeftView)

CRMLineUpLeftView::CRMLineUpLeftView()
{
}

CRMLineUpLeftView::~CRMLineUpLeftView()
{
}


BEGIN_MESSAGE_MAP(CRMLineUpLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CRMLineUpLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpLeftView drawing

void CRMLineUpLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpLeftView diagnostics

#ifdef _DEBUG
void CRMLineUpLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CRMLineUpLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRMLineUpLeftView message handlers
void CRMLineUpLeftView::OnNew()
{
	CLineUpName dl;

	if( dl.DoModal()==IDOK )
	{
		CDatabase	db;
		CString		strSQL,
					str=dl.m_Name;
		str.Replace("'","''");

		CRSCartwallDefinition rs(m_strConnect);
		rs.m_strFilter.Format("Name = '%s'",str);
		rs.m_strSort="ID DESC";

		strSQL.Format("INSERT INTO CartwallDefinition (Name,UserID,Info) VALUES ('%s',0,1)",str);
		db.Open(m_strConnect);
		db.ExecuteSQL(strSQL);
		rs.Open();

		for( int i=0; i<50; i++ )
		{
			strSQL.Format("INSERT INTO CartwallContents (CartwallID,Position) VALUES ('%d','%d')",rs.m_ID,i);
			db.ExecuteSQL(strSQL);
		}
		
		typeTreeItem *lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_RMLINEUP;

		CTreeCtrl *pTree=&GetTreeCtrl();
		HTREEITEM hItem=pTree->InsertItem(dl.m_Name,12,12);
		pTree->SetItemData(hItem,(DWORD)lpItem);

		rs.Close();
	}
}

void CRMLineUpLeftView::OnDoubleClick()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_RMLINEUP )
	{
		CRSCartwallDefinition rs( m_strConnect );
		rs.m_strFilter.Format("ID = %d",lpItem->lID);
		rs.Open();
		if( rs.GetRecordCount() )
		{
			CLineUpName	dl;
			rs.m_Name.TrimRight();
			dl.m_Name=rs.m_Name;

			if( dl.DoModal()==IDOK )
			{
				rs.Edit();
				rs.m_Name=dl.m_Name;
				rs.Update();

				pTree->SetItemText(hItem,dl.m_Name);
			}
		}
		rs.Close();
	}
}

void CRMLineUpLeftView::OnCut()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_RMLINEUP )
	{
		if( AfxMessageBox(IDS_CONFIRMRMLINEUPREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE FROM CartwallDefinition WHERE ID = '%d'",lpItem->lID);
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM CartwallContents WHERE CartwallID = '%d'",lpItem->lID);
			db.ExecuteSQL(strSQL);
			db.Close();

			pTree->DeleteItem(hItem);
		}
	}
}

UINT CRMLineUpLeftView::RefreshList(LPVOID lp)
{
	CRMLineUpLeftView *pView=(CRMLineUpLeftView *)lp;
	CTreeCtrl *pTree = &pView->GetTreeCtrl();
	HTREEITEM hItem;
	typeTreeItem *lpItem;

	CRSCartwallDefinition rs( pView->m_strConnect );
	rs.m_strFilter.Format("Info = 1");
	rs.m_strSort="Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		
		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_RMLINEUP;

		hItem=pTree->InsertItem(rs.m_Name,12,12);
		pTree->SetItemData(hItem,(DWORD)lpItem);
		rs.MoveNext();
	}
	return 0;
}

void CRMLineUpLeftView::OnInitialUpdate() 
{
	CString str;
	str.LoadString(IDS_RMLINEUP);

	CDigitalLeftView::OnInitialUpdate();
	
	m_pDocument->SetTitle(str+" - "+m_strRadio);

	AfxBeginThread(RefreshList,(LPVOID)this);
	
}

void CRMLineUpLeftView::OnSelChange()
{
	CTreeCtrl	*pTree=&GetTreeCtrl();
	HTREEITEM	hItem=pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_RMLINEUP )
		m_pViewCart->SetCartView(lpItem->lID);
}