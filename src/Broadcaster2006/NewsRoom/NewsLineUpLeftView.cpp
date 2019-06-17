// NewsLineUpLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "NewsLineUpLeftView.h"
#include "NewsLineUp.h"
#include "..\include\RSNewsLineUpDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_strBaseURL;

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUpLeftView

IMPLEMENT_DYNCREATE(CNewsLineUpLeftView, CDigitalLeftView)

CNewsLineUpLeftView::CNewsLineUpLeftView()
{
}

CNewsLineUpLeftView::~CNewsLineUpLeftView()
{
}


BEGIN_MESSAGE_MAP(CNewsLineUpLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CNewsLineUpLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUpLeftView drawing

void CNewsLineUpLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUpLeftView diagnostics

#ifdef _DEBUG
void CNewsLineUpLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CNewsLineUpLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUpLeftView message handlers

void CNewsLineUpLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CString str;
	str.LoadString(IDS_NEWSLINEUP);

	m_pDocument->SetTitle(str+" - "+m_strRadio);

	AfxBeginThread(RefreshList,(LPVOID)this);
}

UINT CNewsLineUpLeftView::RefreshList( LPVOID lp )
{
	CNewsLineUpLeftView *pView=(CNewsLineUpLeftView *)lp;
	CTreeCtrl *pTree = &pView->GetTreeCtrl();
	HTREEITEM hItem;
	typeTreeItem *lpItem;

	CRSNewsLineUpDefinition rs( pView->m_strConnect );
	rs.m_strSort="Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		
		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_NEWSLINEUP;

		hItem=pTree->InsertItem(rs.m_Name,13,13);
		pTree->SetItemData(hItem,(DWORD)lpItem);
		rs.MoveNext();
	}

	return 0;
}

void CNewsLineUpLeftView::OnNew()
{
	CNewsLineUp dl;

	if( dl.DoModal()==IDOK )
	{
		CDatabase	db;
		CString		strSQL;

		CRSNewsLineUpDefinition rs( m_strConnect );
		rs.m_strSort="ID DESC";

		strSQL.Format("INSERT INTO NewsLineUpDefinition (Name) VALUES ('%s')",dl.m_Name);
		db.Open( m_strConnect);
		db.ExecuteSQL(strSQL);

		rs.Open();

		for( int i=0; i<dl.m_nNews; i++ )
		{
			if( i<dl.m_nNews-1 )
				strSQL.Format("INSERT INTO NewsLineUpComponents (LineUpID,Position,NewsID,Prev,Next) VALUES (%d,%d,%d,%d,%d)",
					rs.m_ID, i+1,dl.m_lNewsID[i],i,i+2);
			else
				strSQL.Format("INSERT INTO NewsLineUpComponents (LineUpID,Position,NewsID,Prev,Next) VALUES (%d,%d,%d,%d,%d)",
					rs.m_ID, i+1,dl.m_lNewsID[i],i,0);

			db.ExecuteSQL(strSQL);
		}
		typeTreeItem *lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_NEWSLINEUP;

		rs.Close();

		CTreeCtrl	*pTree=&GetTreeCtrl();
		HTREEITEM	hItem=pTree->InsertItem(dl.m_Name,13,13);
		pTree->SetItemData(hItem,(DWORD)lpItem);

	}
}

void CNewsLineUpLeftView::OnDoubleClick()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_NEWSLINEUP )
	{
		CRSNewsLineUpDefinition rs( m_strConnect );
		rs.m_strFilter.Format("ID = %d",lpItem->lID);
		rs.Open();

		if( rs.GetRecordCount() )
		{
			CNewsLineUp	dl;
			rs.m_Name.TrimRight();
			dl.m_Name=rs.m_Name;
			dl.m_ID=rs.m_ID;
			dl.m_strConnect=m_strConnect;

			if( dl.DoModal()==IDOK )
			{
				rs.Edit();
				rs.m_Name=dl.m_Name;
				rs.Update();
				
				CString		strSQL;
				CDatabase	db;

				strSQL.Format("DELETE FROM NewsLineUpComponents WHERE LineUpID = %d",dl.m_ID);
				db.Open( m_strConnect);
				db.ExecuteSQL(strSQL);

				for( int i=0; i<dl.m_nNews; i++ )
				{
					if( i<dl.m_nNews-1 )
						strSQL.Format("INSERT INTO NewsLineUpComponents (LineUpID,Position,NewsID,Prev,Next) VALUES (%d,%d,%d,%d,%d)",
							dl.m_ID, i+1,dl.m_lNewsID[i],i,i+2);
					else
						strSQL.Format("INSERT INTO NewsLineUpComponents (LineUpID,Position,NewsID,Prev,Next) VALUES (%d,%d,%d,%d,%d)",
							dl.m_ID, i+1,dl.m_lNewsID[i],i,0);

					db.ExecuteSQL(strSQL);
				}
				pTree->SetItemText(hItem,dl.m_Name);
			}
		}
		rs.Close();
	}
}

void CNewsLineUpLeftView::OnCut() 
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_NEWSLINEUP )
	{
		if( AfxMessageBox(IDS_CONFIRMNEWSLINEUPREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE FROM NewsLineUpDefinition WHERE ID = '%d'",lpItem->lID);
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM NewsLineUpComponents WHERE LineUpID = '%d'",lpItem->lID);
			db.ExecuteSQL(strSQL);
			db.Close();

			pTree->DeleteItem(hItem);
		}
	}
}

void CNewsLineUpLeftView::OnSelChange()
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

	if( lpItem->wType==TYPE_NEWSLINEUP )
	{
		CString str;

		str.Format("%s\\NewsLineUp.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,m_strDB);
		SetView(str);
	}
}