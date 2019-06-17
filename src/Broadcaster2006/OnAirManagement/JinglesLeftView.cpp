// JinglesLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "JinglesLeftView.h"
#include "Jingles.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\PFLWnd.h"
#include "..\include\rsViewJinglesList.h"
#include "..\include\rsRadioStations.h"
#include "..\include\rsJingles.h"
#include "..\OnAir\RSViewJinglesDataOnAir.h"
#include "..\hasp\hasp.h"
#include "..\include\haspcode.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CString	g_strMainConnect;
extern	CString	g_strBaseURL;
extern	CPFLWnd	*g_wndPFL;

/////////////////////////////////////////////////////////////////////////////
// CJinglesLeftView

IMPLEMENT_DYNCREATE(CJinglesLeftView, CDigitalLeftView)

CJinglesLeftView::CJinglesLeftView()
{
}

CJinglesLeftView::~CJinglesLeftView()
{
}


BEGIN_MESSAGE_MAP(CJinglesLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CJinglesLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJinglesLeftView drawing

void CJinglesLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CJinglesLeftView diagnostics

#ifdef _DEBUG
void CJinglesLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CJinglesLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJinglesLeftView message handlers

void CJinglesLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CString str;
	str.LoadString(IDS_JINGLESMANAGEMENT);

	m_pDocument->SetTitle(str);

	if( g_Permissions.bOnAirManagement )
		AfxBeginThread(RefreshList,(LPVOID)this);	
	else
		str += " - Sem acesso!";

	m_pDocument->SetTitle(str);
}

UINT CJinglesLeftView::RefreshList(LPVOID lp)
{
	CJinglesLeftView *pView = (CJinglesLeftView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	CRSViewJinglesList	rs( g_strMainConnect );
	CString		strPrev;
	HTREEITEM	hType,
				hJingle;
	typeTreeItem *lpItem;

	rs.m_strSort = "Type, Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Type )
		{
			strPrev = rs.m_Type;
			rs.m_Type.TrimRight();

			hType = pTree->InsertItem(rs.m_Type,14,14);
			pTree->SetItemData(hType,0);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_JINGLE;

		hJingle = pTree->InsertItem(rs.m_Name,4,4,hType);
		pTree->SetItemData(hJingle,(DWORD)lpItem);

		rs.MoveNext();
	}

	hType=pTree->InsertItem("w",4,4);
	pTree->DeleteItem(hType);
	return 0;
}

void CJinglesLeftView::OnPFL()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
		return;
	
	if( lpItem->wType!=TYPE_JINGLE )
		return;

	g_wndPFL->SetSound(TYPE_JINGLE,lpItem->lID);
	g_wndPFL->RestoreWindow();
}

void CJinglesLeftView::OnSelChange()
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

		str.Format("%s\\Jingle.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(str);
	}
}

void CJinglesLeftView::OnCut()
{
	if( !g_Permissions.bJinglesCut )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_JINGLE )
		return;
	
	if( AfxMessageBox(IDS_CONFIRMJINGLEREMOVE,MB_YESNO)==IDYES )
	{
		CString		strSQL;
		CDatabase	db;
		CRSRadioStations rs(g_strMainConnect);
		rs.Open();

		strSQL.Format("UPDATE Jingles SET Activ = 0 WHERE ID = %d",lpItem->lID);
		rs.m_pDatabase->ExecuteSQL(strSQL);

		while( !rs.IsEOF() )
		{
			rs.m_DSN.TrimRight();
			db.Open(rs.m_DSN);

			strSQL.Format("DELETE FROM JinglesOnAir WHERE JingleID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM BlocksComposition WHERE ItemType = '%d' AND ItemID = '%d'",TYPE_JINGLE,lpItem->lID);
			db.ExecuteSQL(strSQL);
			db.Close();
			rs.MoveNext();
		}
		rs.Close();

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUT,TYPE_JINGLE,lpItem->lID,0);

		pTree->DeleteItem(hItem);
	}
}

void CJinglesLeftView::OnNew()
{
	int	par1,par2,par3,par4;

	if( HASP_HASPPROTECTION & HASP_WORKSTATION)
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

	if( !g_Permissions.bJinglesNew )
		return;

	CJingles dl;

	if( dl.DoModal()==IDOK )
	{
		CRSJingles rs( g_strMainConnect );
		rs.m_strSort="ID DESC";
		rs.Open();

		rs.AddNew();
		rs.m_Activ=1;
		rs.m_TypeID		= dl.m_TypeID;
		rs.m_Name		= dl.m_Name;
		rs.m_PathID		= dl.m_PathID;
		rs.m_FileName	= dl.m_FileName;
		rs.m_Ready		= 1;
		rs.m_Rythm		= dl.m_Rythm;
		rs.m_Start		= dl.m_pTimers->m_pTimer->m_Start;
		rs.m_Intro		= dl.m_pTimers->m_pTimer->m_Intro;
		rs.m_LoopA		= dl.m_pTimers->m_pTimer->m_LoopA;
		rs.m_LoopB		= dl.m_pTimers->m_pTimer->m_LoopB;
		rs.m_Mix		= dl.m_pTimers->m_pTimer->m_Mix;
		rs.m_Finish		= dl.m_pTimers->m_pTimer->m_End;
		
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

			hType=pTree->InsertItem(dl.m_Type,14,14);
			pTree->SetItemData(hType,(DWORD)lpItem);
			pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
			pTree->SortChildren(NULL);
		}

		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_JINGLE;

		HTREEITEM hJingle=pTree->InsertItem(dl.m_Name,4,4,hType);
		pTree->SetItemData(hJingle,(DWORD)lpItem);
		pTree->SortChildren(hType);
		pTree->EnsureVisible(hJingle);
		rs.Close();

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_JINGLE,lpItem->lID);
	}

}

void CJinglesLeftView::OnDoubleClick()
{
	if( !g_Permissions.bJinglesEdit )
		return;

	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem=(typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_JINGLE )
		return;

	CRSViewJinglesDataOnAir	rs( g_strMainConnect );
	
	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		CJingles dl;
		
		rs.m_TypeName.TrimRight();
		rs.m_Name.TrimRight();
		rs.m_Path.TrimRight();
		rs.m_FileName.TrimRight();

		dl.m_IsNew = FALSE;
		dl.m_TypeID = rs.m_TypeID;
		dl.m_Type = rs.m_TypeName;
		dl.m_Name = rs.m_Name;
		dl.m_Path = rs.m_Path;
//		dl.m_PathID = rs.m_Path;
		dl.m_FileName = rs.m_FileName;
		dl.m_Start = rs.m_Start;
		dl.m_Mix = rs.m_Mix;
		dl.m_End = rs.m_Finish;
		dl.m_Intro = rs.m_Intro;
		dl.m_LoopA = rs.m_LoopA;
		dl.m_LoopB = rs.m_LoopB;
		dl.m_Rythm = rs.m_Rythm;
		rs.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSJingles rsJingles( g_strMainConnect );
			rsJingles.m_strFilter.Format("ID = %d",lpItem->lID);
			rsJingles.Open();
			if( rsJingles.GetRecordCount() )
			{
				rsJingles.Edit();

				rsJingles.m_Activ		= 1;
				rsJingles.m_TypeID		= dl.m_TypeID;
				rsJingles.m_Name		= dl.m_Name;
				rsJingles.m_PathID		= dl.m_PathID;
				rsJingles.m_FileName	= dl.m_FileName;
				rsJingles.m_Ready		= 1;
				rsJingles.m_Rythm		= dl.m_Rythm;
				rsJingles.m_Start		= dl.m_pTimers->m_pTimer->m_Start;
				rsJingles.m_Intro		= dl.m_pTimers->m_pTimer->m_Intro;
				rsJingles.m_LoopA		= dl.m_pTimers->m_pTimer->m_LoopA;
				rsJingles.m_LoopB		= dl.m_pTimers->m_pTimer->m_LoopB;
				rsJingles.m_Mix			= dl.m_pTimers->m_pTimer->m_Mix;
				rsJingles.m_Finish		= dl.m_pTimers->m_pTimer->m_End;

				rsJingles.Update();
				rsJingles.Requery();

				pTree->DeleteItem(hItem);
				HTREEITEM hType=FindString(dl.m_Type);
				typeTreeItem *lpItem;

				if( hType==NULL )
				{
					lpItem = new typeTreeItem;
					lpItem->lID = dl.m_TypeID;
					lpItem->wType=0;

					hType=pTree->InsertItem(dl.m_Type,14,14);
					pTree->SetItemData(hType,(DWORD)lpItem);
					pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
					pTree->SortChildren(NULL);
				}

				lpItem = new typeTreeItem;
				lpItem->lID = rsJingles.m_ID;
				lpItem->wType = TYPE_JINGLE;

				HTREEITEM hJingle=pTree->InsertItem(dl.m_Name,4,4,hType);
				pTree->SetItemData(hJingle,(DWORD)lpItem);
				pTree->SortChildren(hType);
				pTree->EnsureVisible(hJingle);

				WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_JINGLE,lpItem->lID);
			}
			rsJingles.Close(); 
		} 
	}
	else
		rs.Close();
}


void CJinglesLeftView::OnRDoubleClick()
{
	OnPFL();
};