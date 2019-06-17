// SponsorsLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "SponsorsLeftView.h"
#include "TrafficExternals.h"
#include "Sponsor.h"
#include "..\include\RSViewSponsors.h"
#include "..\include\RSSponsors.h"
#include "..\include\RSViewSpotsList.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\common\include\defines.h"
#include "..\common\include\global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT		g_nFormat;
/////////////////////////////////////////////////////////////////////////////
// CSponsorsLeftView

IMPLEMENT_DYNCREATE(CSponsorsLeftView, CDigitalLeftView)

CSponsorsLeftView::CSponsorsLeftView()
{
}

CSponsorsLeftView::~CSponsorsLeftView()
{
}


BEGIN_MESSAGE_MAP(CSponsorsLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CSponsorsLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSponsorsLeftView drawing

void CSponsorsLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSponsorsLeftView diagnostics

#ifdef _DEBUG
void CSponsorsLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CSponsorsLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSponsorsLeftView message handlers

void CSponsorsLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CString str;
	str.LoadString(IDS_SPONSORS);
	m_pDocument->SetTitle(str+" - "+m_strRadio);

	AfxBeginThread(RefreshList,this);	
}

UINT CSponsorsLeftView::RefreshList(LPVOID lp)
{
	CSponsorsLeftView *pThis = (CSponsorsLeftView *)lp;
	CTreeCtrl *pTree = &pThis->GetTreeCtrl();

	pThis->m_bIsRefreshing=TRUE;

	CString		strPrevCustomer="";
	HTREEITEM	hCustomer,
				hSpot;
	typeTreeItem *lpItem;

	CRSViewSponsors	 rs( pThis->m_strConnect );

	rs.m_strSort="CustomerName, SpotName";
	rs.Open();
		
	while( !rs.IsEOF() )
	{
		if( rs.m_CustomerName!= strPrevCustomer )
		{
			strPrevCustomer = rs.m_CustomerName;
			rs.m_CustomerName.TrimRight();
			
			lpItem = new typeTreeItem;
			lpItem->wType = TYPE_CUSTOMER;
			lpItem->lID = rs.m_CustomerID;

			hCustomer = pTree->InsertItem(rs.m_CustomerName,0,0);
			pTree->SetItemData(hCustomer,(DWORD)lpItem);
			pTree->SetItemState(hCustomer,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_SpotName.TrimRight();
		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_SpotID;
		lpItem->wType=TYPE_SPOT;

		hSpot = pTree->InsertItem(rs.m_SpotName,1,1,hCustomer);
		pTree->SetItemData(hSpot,(DWORD)lpItem);

		rs.MoveNext();
	}

	rs.Close();
	pThis->m_bIsRefreshing=FALSE;

	return 0;
}

void CSponsorsLeftView::OnSelChange()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
	{
		strURL.Format("%s\\EmptyPage.asp",g_strBaseURL);
		SetView(strURL);
		return;
	}

	switch( lpItem->wType )
	{
	case TYPE_CUSTOMER:
		strURL.Format("%s\\Customer.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(strURL);
		break;
	case TYPE_SPOT:
		strURL.Format("%s\\Sponsor.asp?SponsorID=%d&DB=%s",g_strBaseURL,lpItem->lID,m_strDB);
		SetView(strURL);
		break;
 	default:
		strURL.Format("%s\\EmptyPage.asp",g_strBaseURL);
		SetView(strURL);
		break;
	}
}

void CSponsorsLeftView::OnDoubleClick()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_SPOT )
	{
		CRSViewSponsors rsView( m_strConnect );
		rsView.m_strFilter.Format("SpotID = %d",lpItem->lID);
		rsView.Open();

		if( rsView.GetRecordCount() )
		{
			CSponsor dl;
			
			rsView.m_CustomerName.TrimRight();
			rsView.m_SpotName.TrimRight();

			dl.m_CustomerName = rsView.m_CustomerName;
			dl.m_SpotName	= rsView.m_SpotName;
			dl.m_dStartingDate = rsView.m_StartingDate;
			dl.m_dEndingDate = rsView.m_EndingDate;

			if( dl.DoModal()==IDOK )
			{
				rsView.Close();

				CRSSponsors rs( m_strConnect );
				rs.m_strFilter.Format("SpotID = %d",lpItem->lID);
				rs.Open();
				
				if( rs.GetRecordCount() )
				{
					rs.Edit();
					rs.m_StartingDate = dl.m_dStartingDate;
					rs.m_EndingDate = dl.m_dEndingDate;
					rs.Update();
				}
				rs.Close();
				WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDITSPONSORS,TYPE_SPOT,lpItem->lID,m_lRadioID);
			}
			else
				rsView.Close();
		}
	}
}

void CSponsorsLeftView::CutSponsor() 
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	if( lpItem->wType == TYPE_SPOT )
	{
		if( AfxMessageBox(IDS_CONFIRMSPONSORREMOVE,MB_YESNO)==IDYES )
		{
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE FROM Sponsors WHERE SpotID = '%d'",lpItem->lID);
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);
			db.Close();

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUTFROMSPONSORS,TYPE_SPOT,lpItem->lID,m_lRadioID);

			pTree->DeleteItem(hItem);
		}
	}
}
DROPEFFECT CSponsorsLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( m_lpDragItem->Item.wType != TYPE_SPOT )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	return DROPEFFECT_COPY;
}

void CSponsorsLeftView::OnDragLeave() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDigitalLeftView::OnDragLeave();
}

DROPEFFECT CSponsorsLeftView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDigitalLeftView::OnDragOver(pDataObject, dwKeyState, point);
}

BOOL CSponsorsLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CRSSponsors	rs( m_strConnect );

	rs.m_strFilter.Format("SpotID = %d",m_lpDragItem->Item.lID);
	rs.m_strSort = "ID DESC";

	rs.Open();
	if( rs.GetRecordCount() )
	{
		rs.Close();
		AfxMessageBox(IDS_SPONSORALLREADYEXISTS);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}
	else
	{
		CRSViewSpotsList rsSpots(g_strMainConnect);
		rsSpots.m_strFilter.Format("ID = %d",m_lpDragItem->Item.lID);
		rsSpots.Open();
		rsSpots.m_CustomerName.TrimRight();
		rsSpots.m_Name.TrimRight();

		CSponsor dl;
		dl.m_CustomerName = rsSpots.m_CustomerName;
		dl.m_SpotName = rsSpots.m_Name;

		if( dl.DoModal()==IDOK )
		{
			CString		strSQL;
			CDatabase	db;
			db.Open(m_strConnect);
			
			strSQL.Format("INSERT INTO Sponsors (SpotID, StartingDate, EndingDate) VALUES ('%d', '%d-%d-%d', '%d-%d-%d')",
				m_lpDragItem->Item.lID,
				dl.m_dStartingDate.GetYear(),dl.m_dStartingDate.GetMonth(),dl.m_dStartingDate.GetDay(),
				dl.m_dEndingDate.GetYear(),dl.m_dEndingDate.GetMonth(),dl.m_dEndingDate.GetDay() );
			db.ExecuteSQL(strSQL);
			db.Close();

			rs.Requery();
		
			CTreeCtrl *pTree=&GetTreeCtrl();
			HTREEITEM hCustomer = FindString(rsSpots.m_CustomerName);
			if( hCustomer==NULL )
			{
				typeTreeItem *lpItem=new typeTreeItem;
				lpItem->lID=rsSpots.m_CustomerID;
				lpItem->wType=TYPE_CUSTOMER;

				hCustomer=pTree->InsertItem(rsSpots.m_CustomerName,0,0);
				pTree->SetItemState(hCustomer,TVIS_BOLD,TVIS_BOLD);
				pTree->SetItemData(hCustomer,(DWORD)lpItem);
				pTree->SortChildren(NULL);
			}

			typeTreeItem *lpItem=new typeTreeItem;
			lpItem->lID=rs.m_SpotID;
			lpItem->wType=TYPE_SPOT;
	
			HTREEITEM hSpot = pTree->InsertItem(dl.m_SpotName,1,1,hCustomer);
			pTree->SetItemData(hSpot,(DWORD)lpItem);
			pTree->EnsureVisible(hSpot);

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADDTOSPONSORS,TYPE_SPOT,lpItem->lID,m_lRadioID);
		}
		rsSpots.Close();
	}

	m_lpDragItem=NULL;
	return DROPEFFECT_COPY;
}
