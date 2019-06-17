// RMsManagementLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "RMsManagementLeftView.h"
#include "RMs.h"
#include "..\include\RSRms.h"
#include "..\include\RSViewRms.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\PFLWnd.h"
#include "..\include\RSRadioStations.h"
#include "..\hasp\hasp.h"
#include "..\include\haspcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPFLWnd *g_wndPFL;
extern CString g_strMainConnect;
extern CString g_strBaseURL;

/////////////////////////////////////////////////////////////////////////////
// CRMsManagementLeftView

IMPLEMENT_DYNCREATE(CRMsManagementLeftView, CDigitalLeftView)

CRMsManagementLeftView::CRMsManagementLeftView()
{
}

CRMsManagementLeftView::~CRMsManagementLeftView()
{
}


BEGIN_MESSAGE_MAP(CRMsManagementLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CRMsManagementLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMsManagementLeftView drawing

void CRMsManagementLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRMsManagementLeftView diagnostics

#ifdef _DEBUG
void CRMsManagementLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CRMsManagementLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRMsManagementLeftView message handlers
void CRMsManagementLeftView::OnNew()
{
	if( !g_Permissions.bRmsAdd )
		return;

	int	par1,par2,par3,par4;

	if( HASP_HASPPROTECTION && HASP_WORKSTATION)
	{
		if( HASP_TIMEKEY )
			hasp(78,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else if( HASP_4 )
			hasp(6,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else
		{
			hasp(5,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
			if( par3!=0 )
				par3=0;
			else
				par3=-1;
		}
		if( (par3!=0) || ((par1!=HASP_IDLOW) && (HASP_IDLOW!=0)) || ((par2!=HASP_IDHIGH) && (HASP_IDHIGH!=0)) )
		{
			return;
		}
	}

	CRMs dl;

	if( dl.DoModal()==IDOK )
	{
		CRSRms rs( g_strMainConnect );
		rs.m_strSort="ID DESC";
		rs.Open();

		rs.AddNew();
		rs.m_Activ=1;
		rs.m_ArchiveID=0;
		rs.m_Date.SetDateTime(dl.m_Date.GetYear(),dl.m_Date.GetMonth(),dl.m_Date.GetDay(),0,0,0 );
		rs.m_FileName=dl.m_FileName;
		rs.m_Finish=dl.m_pTimers->m_pTimer->m_End;
		rs.m_KeyWords=dl.m_KeyWords;
		rs.m_Mix=dl.m_pTimers->m_pTimer->m_Mix;
		rs.m_Name=dl.m_Name;
		rs.m_Obs=dl.m_Obs;
		rs.m_PathID=dl.m_PathID;
		rs.m_Start=dl.m_pTimers->m_pTimer->m_Start;
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

			hType=pTree->InsertItem(dl.m_Type,8,8);
			pTree->SetItemData(hType,(DWORD)lpItem);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
			pTree->SortChildren(NULL);
		}

		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_RM;

		HTREEITEM hRM=pTree->InsertItem(dl.m_Name,9,9,hType);
		pTree->SetItemData(hRM,(DWORD)lpItem);
		pTree->SortChildren(hType);
		pTree->EnsureVisible(hRM);
		rs.Close();
	}
}

void CRMsManagementLeftView::OnDoubleClick()
{
	if( !g_Permissions.bRmsEdit )
		return;

	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_RM )
		return;

	CRSViewRms	rs( g_strMainConnect );
	
	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		CRMs dl;
		
		rs.m_Type.TrimRight();
		rs.m_Name.TrimRight();
		rs.m_KeyWords.TrimRight();
		rs.m_Obs.TrimRight();
		rs.m_Path.TrimRight();
		rs.m_FileName.TrimRight();

		dl.m_IsNew = FALSE;
		dl.m_TypeID = rs.m_TypeID;
		dl.m_Type = rs.m_Type;
		dl.m_Name = rs.m_Name;
		dl.m_KeyWords = rs.m_KeyWords;
		dl.m_Obs = rs.m_Obs;
		dl.m_Path = rs.m_Path;
		dl.m_PathID = rs.m_PathID;
		dl.m_FileName = rs.m_FileName;
		dl.m_Start = rs.m_Start;
		dl.m_Mix = rs.m_Mix;
		dl.m_End = rs.m_Finish;
		rs.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSRms rsRM( g_strMainConnect );
			rsRM.m_strFilter.Format("ID = %d",lpItem->lID);
			rsRM.Open();
			if( rsRM.GetRecordCount() )
			{
				rsRM.Edit();
				rsRM.m_Activ=1;
				rsRM.m_ArchiveID=0;
				rsRM.m_Date.SetDateTime(dl.m_Date.GetYear(),dl.m_Date.GetMonth(),dl.m_Date.GetDay(),0,0,0 );
				rsRM.m_FileName=dl.m_FileName;
				rsRM.m_Finish=dl.m_pTimers->m_pTimer->m_End;
				rsRM.m_KeyWords=dl.m_KeyWords;
				rsRM.m_Mix=dl.m_pTimers->m_pTimer->m_Mix;
				rsRM.m_Name=dl.m_Name;
				rsRM.m_Obs=dl.m_Obs;
				rsRM.m_PathID=dl.m_PathID;
				rsRM.m_Start=dl.m_pTimers->m_pTimer->m_Start;
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

					hType=pTree->InsertItem(dl.m_Type,8,8);
					pTree->SetItemData(hType,(DWORD)lpItem);
					pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
					pTree->SortChildren(NULL);
				}

				lpItem = new typeTreeItem;
				lpItem->lID = rsRM.m_ID;
				lpItem->wType = TYPE_RM;

				HTREEITEM hRM=pTree->InsertItem(dl.m_Name,9,9,hType);
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

void CRMsManagementLeftView::OnCut()
{
	if( !g_Permissions.bRmsCut )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_RM )
		return;
	
	if( AfxMessageBox(IDS_CONFIRMRMREMOVE,MB_YESNO)==IDYES )
	{
		CString		strSQL;
		CDatabase	db;
		CRSRadioStations rs(g_strMainConnect);
		rs.Open();

		strSQL.Format("UPDATE RMs SET Activ = 0 WHERE ID = %d",lpItem->lID);
		rs.m_pDatabase->ExecuteSQL(strSQL);

		while( !rs.IsEOF() )
		{
			rs.m_DSN.TrimRight();
			db.Open(rs.m_DSN);

			strSQL.Format("DELETE FROM RMsOnAir WHERE RMID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);

			db.Close();
			rs.MoveNext();
		}
		rs.Close();
		pTree->DeleteItem(hItem);
	}
}

void CRMsManagementLeftView::OnPFL()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
		return;
	
	if( lpItem->wType!=TYPE_RM )
		return;

	g_wndPFL->SetSound(TYPE_RM,lpItem->lID);
	g_wndPFL->RestoreWindow();
}

void CRMsManagementLeftView::OnSelChange()
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

		str.Format("%s\\RM.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(str);
	}
}

void CRMsManagementLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();

	CString str;
	str.LoadString(IDS_RMSMANAGEMENT);

	m_pDocument->SetTitle(str);
	
	AfxBeginThread(RefreshList,(LPVOID)this);
}

UINT CRMsManagementLeftView::RefreshList(LPVOID lp)
{
	CRMsManagementLeftView *pView = (CRMsManagementLeftView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	CRSViewRms	rs( g_strMainConnect );
	CString		strPrev;
	HTREEITEM	hType,
				hRM;
	typeTreeItem *lpItem;

	rs.m_strFilter = "Activ = 1";
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
