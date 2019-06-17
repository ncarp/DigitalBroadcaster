// TextManagementLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "TextManagementLeftView.h"
#include "NewsText.h"
#include "..\include\RSViewNewsList.h"
#include "..\include\RSViewNews.h"
#include "..\include\RSNews.h"
#include "..\include\RSRadioStations.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString	g_strMainConnect;
extern CString	g_strBaseURL;
/////////////////////////////////////////////////////////////////////////////
// CTextManagementLeftView

IMPLEMENT_DYNCREATE(CTextManagementLeftView, CDigitalLeftView)

CTextManagementLeftView::CTextManagementLeftView()
{
}

CTextManagementLeftView::~CTextManagementLeftView()
{
}


BEGIN_MESSAGE_MAP(CTextManagementLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CTextManagementLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextManagementLeftView drawing

void CTextManagementLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTextManagementLeftView diagnostics

#ifdef _DEBUG
void CTextManagementLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CTextManagementLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextManagementLeftView message handlers

void CTextManagementLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CString str;
	str.LoadString(IDS_TEXTMANAGEMENT);

	m_pDocument->SetTitle(str);

	AfxBeginThread(RefreshList,(LPVOID)this);
}

UINT CTextManagementLeftView::RefreshList(LPVOID lp)
{
	CTextManagementLeftView *pView = (CTextManagementLeftView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	CRSViewNewsList	rs( g_strMainConnect );
	CString		strPrev;
	HTREEITEM	hType,
				hNews;
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

		hNews = pTree->InsertItem(rs.m_Name,11,11,hType);
		pTree->SetItemData(hNews,(DWORD)lpItem);

		rs.MoveNext();
	}

	hType=pTree->InsertItem("w",0,0);
	pTree->DeleteItem(hType);

	return 0;
}

void CTextManagementLeftView::OnNew()
{
	if( !g_Permissions.bTextAdd )
		return;

	CNewsText dl;

	if( dl.DoModal()==IDOK )
	{
		CRSNews rs( g_strMainConnect );
		rs.m_strSort="ID DESC";
		rs.Open();

		rs.AddNew();
		rs.m_Activ = 1;
		rs.m_Date.SetDateTime(dl.m_Date.GetYear(),dl.m_Date.GetMonth(),dl.m_Date.GetDay(),0,0,0);
		rs.m_Name=dl.m_Name;
		rs.m_NewsText=dl.m_Text;
		rs.m_TypeID=dl.m_TypeID;
		rs.Update();
		rs.Requery();

		CTreeCtrl *pTree=&GetTreeCtrl();
		HTREEITEM hType=FindString(dl.m_Type);
		typeTreeItem *lpItem;

		if( hType==NULL )
		{
			lpItem = new typeTreeItem;
			lpItem->lID = dl.m_TypeID;
			lpItem->wType=0;

			hType=pTree->InsertItem(dl.m_Type,10,10);
			pTree->SetItemData(hType,(DWORD)lpItem);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
			pTree->SortChildren(NULL);
		}

		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_TEXT;

		HTREEITEM hRM=pTree->InsertItem(dl.m_Name,11,11,hType);
		pTree->SetItemData(hRM,(DWORD)lpItem);
		pTree->SortChildren(hType);
		pTree->EnsureVisible(hRM);
		rs.Close();
	}
}

void CTextManagementLeftView::OnCut()
{
	if( !g_Permissions.bTextCut )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_TEXT )
		return;
	
	if( AfxMessageBox(IDS_CONFIRMTEXTREMOVE,MB_YESNO)==IDYES )
	{
		CString		strSQL;
		CDatabase	db;
		CRSRadioStations rs(g_strMainConnect);
		rs.Open();

		strSQL.Format("UPDATE News SET Activ = 0 WHERE ID = %d",lpItem->lID);
		rs.m_pDatabase->ExecuteSQL(strSQL);

		while( !rs.IsEOF() )
		{
			rs.m_DSN.TrimRight();
			db.Open(rs.m_DSN);

			strSQL.Format("DELETE FROM NewsOnAir WHERE NewsID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);

			db.Close();
			rs.MoveNext();
		}
		rs.Close();
		pTree->DeleteItem(hItem);
	}
}

void CTextManagementLeftView::OnDoubleClick()
{
	if( !g_Permissions.bTextEdit )
		return;

	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_TEXT )
		return;

	CRSViewNews	rs( g_strMainConnect );
	
	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		CNewsText dl;
		
		rs.m_Type.TrimRight();
		rs.m_Name.TrimRight();
		rs.m_KeyWords.TrimRight();
		rs.m_NewsText.TrimRight();

		dl.m_TypeID = rs.m_TypeID;
		dl.m_Type = rs.m_Type;
		dl.m_Name = rs.m_Name;
		dl.m_KeyWords = rs.m_KeyWords;
		dl.m_Text = rs.m_NewsText;
		rs.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSNews rsRM( g_strMainConnect );
			rsRM.m_strFilter.Format("ID = %d",lpItem->lID);
			rsRM.Open();
			if( rsRM.GetRecordCount() )
			{
				rsRM.Edit();
				rsRM.m_Activ=1;
				rsRM.m_Date.SetDateTime(dl.m_Date.GetYear(),dl.m_Date.GetMonth(),dl.m_Date.GetDay(),0,0,0 );
				rsRM.m_KeyWords=dl.m_KeyWords;
				rsRM.m_Name=dl.m_Name;
				rsRM.m_NewsText=dl.m_Text;
				rsRM.m_TypeID=dl.m_TypeID;

				rsRM.Update();
				rsRM.Requery();

				pTree->DeleteItem(hItem);
				HTREEITEM hType=FindString(dl.m_Type);
				typeTreeItem *lpItem;

				if( hType==NULL )
				{
					lpItem = new typeTreeItem;
					lpItem->lID = dl.m_TypeID;
					lpItem->wType=0;

					hType=pTree->InsertItem(dl.m_Type,10,10);
					pTree->SetItemData(hType,(DWORD)lpItem);
					pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
					pTree->SortChildren(NULL);
				}

				lpItem = new typeTreeItem;
				lpItem->lID = rsRM.m_ID;
				lpItem->wType = TYPE_TEXT;

				HTREEITEM hRM=pTree->InsertItem(dl.m_Name,11,11,hType);
				pTree->SetItemData(hRM,(DWORD)lpItem);
				pTree->SortChildren(hType);
				pTree->EnsureVisible(hRM);
			}
			rsRM.Close();
		}
	}
	else
		rs.Close();
}

void CTextManagementLeftView::OnSelChange()
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

		str.Format("%s\\NewsText.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(str);
	}
}