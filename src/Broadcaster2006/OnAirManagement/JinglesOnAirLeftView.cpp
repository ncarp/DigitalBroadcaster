// JinglesOnAirLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "JinglesOnAirLeftView.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\RSViewJinglesOnAir.h"
#include "..\OnAir\RSViewJinglesDataOnAir.h"
#include "..\include\TimeSpanDefinition.h"
#include "..\include\RSjinglesOnAir.h"
#include "..\common\include\defines.h"
#include "..\common\include\permissions.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CString		g_strMainConnect;
extern	CString		g_strBaseURL;
extern	UINT		g_nFormat;
/////////////////////////////////////////////////////////////////////////////
// CJinglesOnAirLeftView

IMPLEMENT_DYNCREATE(CJinglesOnAirLeftView, CDigitalLeftView)

CJinglesOnAirLeftView::CJinglesOnAirLeftView()
{
}

CJinglesOnAirLeftView::~CJinglesOnAirLeftView()
{
}


BEGIN_MESSAGE_MAP(CJinglesOnAirLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CJinglesOnAirLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJinglesOnAirLeftView drawing

void CJinglesOnAirLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CJinglesOnAirLeftView diagnostics

#ifdef _DEBUG
void CJinglesOnAirLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CJinglesOnAirLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJinglesOnAirLeftView message handlers

void CJinglesOnAirLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();

	CString str;
	str.LoadString(IDS_ONAIRJINGLES);

	m_pDocument->SetTitle(str+" - "+m_strRadio);
	AfxBeginThread(RefreshList,(LPVOID)this);
}

UINT CJinglesOnAirLeftView::RefreshList(LPVOID lp)
{
	CJinglesOnAirLeftView *pView = (CJinglesOnAirLeftView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	CRSViewJinglesOnAir	rs( pView->m_strConnect );
	CString		strPrev;
	HTREEITEM	hType,
				hJingle;
	typeTreeItem *lpItem;

	rs.m_strSort = "JingleType, Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_JingleType )
		{
			strPrev = rs.m_JingleType;
			rs.m_JingleType.TrimRight();

			hType = pTree->InsertItem(rs.m_JingleType,14,14);
			pTree->SetItemData(hType,0);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_JingleID;
		lpItem->wType=TYPE_JINGLE;

		hJingle = pTree->InsertItem(rs.m_Name,4,4,hType);
		pTree->SetItemData(hJingle,(DWORD)lpItem);

		rs.MoveNext();
	}

	hType=pTree->InsertItem("w",0,0);
	pTree->DeleteItem(hType);
	return 0;
}

void CJinglesOnAirLeftView::OnSelChange()
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

	if( lpItem->wType==TYPE_JINGLE )
	{
		CString str;

		str.Format("%s\\JingleOnAir.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,m_strDB);
		SetView(str);
	}
}

void CJinglesOnAirLeftView::OnDoubleClick()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_JINGLE )
	{
		CRSViewJinglesOnAir rsView( m_strConnect );
		rsView.m_strFilter.Format("JingleID = %d",lpItem->lID);
		rsView.Open();

		if( rsView.GetRecordCount() )
		{
			CTimeSpanDefinition dl;
			
			rsView.m_Name.TrimRight();
			rsView.m_JingleType.TrimRight();

			dl.m_Type= rsView.m_JingleType;
			dl.m_Name	= rsView.m_Name;
			dl.m_StartingDate = rsView.m_StartingTime;
			dl.m_EndingDate = rsView.m_EndingTime;

			if( dl.DoModal()==IDOK )
			{
				rsView.Close();

				CString		strSQL;
				CDatabase	db;

				strSQL.Format("UPDATE JinglesOnAir SET StartingDate = '%d-%d-%d', EndingDate = '%d-%d-%d' WHERE JingleID = %d",
					dl.m_StartingDate.GetYear(),dl.m_StartingDate.GetMonth(),dl.m_StartingDate.GetDay(),
					dl.m_EndingDate.GetYear(),dl.m_EndingDate.GetMonth(),dl.m_EndingDate.GetDay(),
					lpItem->lID );

				db.Open(m_strConnect);
				db.ExecuteSQL(strSQL);
				db.Close();

				WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDITONAIRJINGLE,TYPE_JINGLE,lpItem->lID,m_lRadioID);
			}
			else
				rsView.Close();
		}
	}
}

void CJinglesOnAirLeftView::OnCut()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_JINGLE )
	{
		if( AfxMessageBox(IDS_CONFIRMJINGLEREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE FROM JinglesOnAir WHERE JingleID = '%d'",lpItem->lID);
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);

			if( AfxMessageBox("Pretende eliminar igualmente o jingle dos blocos publicitários",MB_YESNO)==IDOK )
			{
				strSQL.Format("DELETE FROM BlocksComposition WHERE ItemID = '%d' AND ItemType = %d",lpItem->lID,TYPE_JINGLE);
				db.ExecuteSQL(strSQL);

				WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUTJINGLEFROMBLOCKS,TYPE_JINGLE,lpItem->lID,m_lRadioID);
			}

			db.Close();

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUTONAIRJINGLE,TYPE_JINGLE,lpItem->lID,m_lRadioID);
			pTree->DeleteItem(hItem);
		}
	}
}

DROPEFFECT CJinglesOnAirLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( m_lpDragItem->Item.wType != TYPE_JINGLE )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	return DROPEFFECT_COPY;
}

BOOL CJinglesOnAirLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CRSViewJinglesOnAir	rs( m_strConnect );

	rs.m_strFilter.Format("JingleID = %d",m_lpDragItem->Item.lID);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		rs.Close();
		AfxMessageBox(IDS_JINGLEALLREADYEXISTS);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}
	else
	{
		CRSViewJinglesDataOnAir rsJingle(g_strMainConnect);
		rsJingle.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rsJingle.Open();
		rsJingle.m_TypeName.TrimRight();
		rsJingle.m_Name.TrimRight();

		CTimeSpanDefinition dl;
		dl.m_Name = rsJingle.m_Name;
		dl.m_Type = rsJingle.m_TypeName;

		if( dl.DoModal()==IDOK )
		{
			CString		strSQL;
			CDatabase	db;
					
			strSQL.Format("INSERT INTO JinglesOnAir (JingleID, StartingDate, EndingDate) VALUES ('%d', '%d-%d-%d', '%d-%d-%d')",
				m_lpDragItem->Item.lID,
				dl.m_StartingDate.GetYear(),dl.m_StartingDate.GetMonth(),dl.m_StartingDate.GetDay(),
				dl.m_EndingDate.GetYear(),dl.m_EndingDate.GetMonth(),dl.m_EndingDate.GetDay() );

			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);
			db.Close();
		
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADDONAIRJINGLE,TYPE_JINGLE,m_lpDragItem->Item.lID,m_lRadioID);
		
			CTreeCtrl *pTree=&GetTreeCtrl();
			HTREEITEM hType = FindString(rsJingle.m_TypeName);
			if( hType==NULL )
			{
				typeTreeItem *lpItem=new typeTreeItem;
				lpItem->lID=rsJingle.m_TypeID;
				lpItem->wType=TYPE_JINGLETYPE;

				hType=pTree->InsertItem(rsJingle.m_TypeName,14,14);
				pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
				pTree->SetItemData(hType,(DWORD)lpItem);
				pTree->SortChildren(NULL);
			}

			typeTreeItem *lpItem=new typeTreeItem;
			lpItem->lID=m_lpDragItem->Item.lID;
			lpItem->wType=TYPE_JINGLE;
	
			HTREEITEM hJingle= pTree->InsertItem(dl.m_Name,4,4,hType);
			pTree->SetItemData(hJingle,(DWORD)lpItem);
			pTree->EnsureVisible(hJingle);

		}
		rsJingle.Close();
	}

	m_lpDragItem=NULL;
	return DROPEFFECT_COPY;
}
