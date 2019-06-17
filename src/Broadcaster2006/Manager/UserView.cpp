// UserView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "UserView.h"
#include "UserDlg.h"
#include "..\common\include\defines.h"
#include "..\common\include\rssystemusers.h"
#include "..\common\include\global.h"
#include "..\common\include\permissions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilTree;

/////////////////////////////////////////////////////////////////////////////
// CUserView

IMPLEMENT_DYNCREATE(CUserView, CListView)

CUserView::CUserView()
{
}

CUserView::~CUserView()
{
}


BEGIN_MESSAGE_MAP(CUserView, CListView)
	//{{AFX_MSG_MAP(CUserView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserView drawing

void CUserView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CUserView diagnostics

#ifdef _DEBUG
void CUserView::AssertValid() const
{
	CListView::AssertValid();
}

void CUserView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUserView message handlers

int CUserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style|=LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CListCtrl *pList = &GetListCtrl();
	pList->SetImageList(g_ilTree,LVSIL_SMALL);
	
	ListView_SetExtendedListViewStyleEx(this->m_hWnd,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT);

	return 0;
}

void CUserView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	CString		strLabel="";
	CListCtrl	*pList = &GetListCtrl();
	
	strLabel.LoadString(IDS_SYSTEMUSERS);

	GetDocument()->SetTitle(strLabel);
	
	pList->InsertColumn(0,strLabel,LVCFMT_LEFT,250);
	pList->InsertColumn(1,"",LVCFMT_CENTER,30);
	pList->InsertColumn(2,"",LVCFMT_CENTER,30);
	pList->InsertColumn(3,"",LVCFMT_CENTER,30);
	pList->InsertColumn(4,"",LVCFMT_CENTER,30);
	pList->InsertColumn(5,"",LVCFMT_CENTER,30);
	pList->InsertColumn(6,"",LVCFMT_CENTER,30);

	RefreshList();
}

void CUserView::RefreshList()
{
	CListCtrl		*pList = &GetListCtrl();
	int				Pos=0;
	CRSSystemUsers	rs( g_strMainConnect );

	pList->DeleteAllItems();

	rs.m_strFilter = "Permission is not null";
	rs.m_strSort = "Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		pList->InsertItem(Pos,rs.m_Name,5);
		pList->SetItemData(Pos,(DWORD)rs.m_Id);

		if( rs.m_Permission.GetAt(1)==1 )
			pList->SetItem(Pos,1,LVIF_IMAGE,"",17,0,0,0);

		if( rs.m_Permission.GetAt(5)==1 )
			pList->SetItem(Pos,2,LVIF_IMAGE,"",4,0,0,0);

		if( rs.m_Permission.GetAt(17)==1 )
			pList->SetItem(Pos,3,LVIF_IMAGE,"",1,0,0,0);

		if( rs.m_Permission.GetAt(26)==1 )
			pList->SetItem(Pos,4,LVIF_IMAGE,"",3,0,0,0);

		if( rs.m_Permission.GetAt(38)==1 )
			pList->SetItem(Pos,5,LVIF_IMAGE,"",9,0,0,0);

		if( (rs.m_Permission.GetAt(0)==1) || (rs.m_Permission.GetAt(49)==1) || (rs.m_Permission.GetAt(50)==1) || (rs.m_Permission.GetAt(51)==1) )
			pList->SetItem(Pos,6,LVIF_IMAGE,"",5,0,0,0);

		rs.MoveNext();
		Pos++;
	}
}

void CUserView::OnAddUser()
{
	CUserDlg	dlg;

	if( dlg.DoModal()==IDOK )
	{
		CRSSystemUsers	rs( g_strMainConnect );
		rs.Open();

		rs.AddNew();
		rs.m_Name = dlg.m_strName;
		rs.m_Permission.SetSize(55);

		rs.m_Permission.SetAt( 0,(BYTE)dlg.m_bManagerUser);
		rs.m_Permission.SetAt( 1,(BYTE)dlg.m_bDiscography);
		rs.m_Permission.SetAt( 2,(BYTE)dlg.m_bNewMusic);
		rs.m_Permission.SetAt( 3,(BYTE)dlg.m_bEditMusic);
		rs.m_Permission.SetAt( 4,(BYTE)dlg.m_bDeleteMusic);

		rs.m_Permission.SetAt( 5,(BYTE)dlg.m_bOnAirManagement );
		rs.m_Permission.SetAt( 6,(BYTE)dlg.m_bJinglesNew );
		rs.m_Permission.SetAt( 7,(BYTE)dlg.m_bJinglesEdit );
		rs.m_Permission.SetAt( 8,(BYTE)dlg.m_bJinglesCut );
		rs.m_Permission.SetAt( 9,(BYTE)dlg.m_bJinglesOnAir );

		rs.m_Permission.SetAt(10,(BYTE)dlg.m_bBlocksAdd );
		rs.m_Permission.SetAt(11,(BYTE)dlg.m_bBlocksEdit);
		rs.m_Permission.SetAt(12,(BYTE)dlg.m_bBlocksCut );

		rs.m_Permission.SetAt(13,(BYTE)dlg.m_bPlayListAdd );
		rs.m_Permission.SetAt(14,(BYTE)dlg.m_bPlayListEdit );
		rs.m_Permission.SetAt(15,(BYTE)dlg.m_bPlayListCut );
		rs.m_Permission.SetAt(16,(BYTE)dlg.m_bPlayListEditContents );

		rs.m_Permission.SetAt(17,(BYTE)dlg.m_bTraffic );
		rs.m_Permission.SetAt(18,(BYTE)dlg.m_bSpotsAdd );
		rs.m_Permission.SetAt(19,(BYTE)dlg.m_bSpotsEdit );
		rs.m_Permission.SetAt(20,(BYTE)dlg.m_bSpotsCut );
		rs.m_Permission.SetAt(21,(BYTE)dlg.m_bSponsors );
		rs.m_Permission.SetAt(22,(BYTE)dlg.m_bTrafficView );
		rs.m_Permission.SetAt(23,(BYTE)dlg.m_bTrafficAdd );
		rs.m_Permission.SetAt(24,(BYTE)dlg.m_bTrafficEdit );
		rs.m_Permission.SetAt(25,(BYTE)dlg.m_bTrafficCut );

		rs.m_Permission.SetAt(26,(BYTE)dlg.m_bScheduler );
		rs.m_Permission.SetAt(27,(BYTE)dlg.m_bLineupAdd );
		rs.m_Permission.SetAt(28,(BYTE)dlg.m_bLineupEdit );
		rs.m_Permission.SetAt(29,(BYTE)dlg.m_bLineupCut );
		rs.m_Permission.SetAt(30,(BYTE)dlg.m_bCriteriaAdd );
		rs.m_Permission.SetAt(31,(BYTE)dlg.m_bCriteriaEdit );
		rs.m_Permission.SetAt(32,(BYTE)dlg.m_bCriteriaCut );
		rs.m_Permission.SetAt(33,(BYTE)dlg.m_bVoiceAdd );
		rs.m_Permission.SetAt(34,(BYTE)dlg.m_bVoiceEdit );
		rs.m_Permission.SetAt(35,(BYTE)dlg.m_bCriteriaCut );
		rs.m_Permission.SetAt(36,(BYTE)dlg.m_bScheduleAuto );
		rs.m_Permission.SetAt(37,(BYTE)dlg.m_bScheduleEdit );

		rs.m_Permission.SetAt(38,(BYTE)dlg.m_bNewsRoom );
		rs.m_Permission.SetAt(39,(BYTE)dlg.m_bRmsAdd );
		rs.m_Permission.SetAt(40,(BYTE)dlg.m_bRmsEdit );
		rs.m_Permission.SetAt(41,(BYTE)dlg.m_bRmsCut );
		rs.m_Permission.SetAt(42,(BYTE)dlg.m_bRmsOnAir );
		rs.m_Permission.SetAt(43,(BYTE)dlg.m_bRmsLineup );
		rs.m_Permission.SetAt(44,(BYTE)dlg.m_bTextAdd );
		rs.m_Permission.SetAt(45,(BYTE)dlg.m_bTextEdit );
		rs.m_Permission.SetAt(46,(BYTE)dlg.m_bTextCut );
		rs.m_Permission.SetAt(47,(BYTE)dlg.m_bTextOnAir );
		rs.m_Permission.SetAt(48,(BYTE)dlg.m_bTextLineup );

		rs.m_Permission.SetAt(49,(BYTE)dlg.m_bManagerFolder );
		rs.m_Permission.SetAt(50,(BYTE)dlg.m_bManagerTime );
		rs.m_Permission.SetAt(51,(BYTE)dlg.m_bManagerLog );

		rs.m_Permission.SetAt(52,(BYTE)dlg.m_bInstrumentals );

		rs.Update();

		RefreshList();
	}
}

void CUserView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl *pList = &GetListCtrl();
	
	int nPos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( nPos == -1 )
		return;
	
	long int	 lUserID = pList->GetItemData(nPos);
	CUserDlg	 dlg;
	tPermissions Perm;

	GetUserPermissions(lUserID,&Perm);
	dlg.m_strName			= Perm.strName;
	dlg.m_bDiscography		= Perm.bDiscography;
	dlg.m_bDeleteMusic		= Perm.bDiscographyDelete;
	dlg.m_bEditMusic		= Perm.bDiscographyEdit;
	dlg.m_bNewMusic			= Perm.bDiscographyAdd;
	dlg.m_bOnAirManagement	= Perm.bOnAirManagement;
	dlg.m_bJinglesNew		= Perm.bJinglesNew;
	dlg.m_bJinglesEdit		= Perm.bJinglesEdit;
	dlg.m_bJinglesCut		= Perm.bJinglesCut;
	dlg.m_bJinglesOnAir		= Perm.bJinglesOnAir;
	dlg.m_bBlocksAdd		= Perm.bBlocksAdd;
	dlg.m_bBlocksEdit		= Perm.bBlocksEdit;
	dlg.m_bBlocksCut		= Perm.bBlocksCut;
	dlg.m_bPlayListAdd		= Perm.bPlayListAdd;
	dlg.m_bPlayListEdit		= Perm.bPlayListEdit;
	dlg.m_bPlayListCut		= Perm.bPlayListCut;
	dlg.m_bTraffic			= Perm.bTraffic;
	dlg.m_bTrafficAdd		= Perm.bTrafficAdd;
	dlg.m_bTrafficCut		= Perm.bTrafficCut;
	dlg.m_bTrafficEdit		= Perm.bTrafficEdit;
	dlg.m_bTrafficView		= Perm.bTrafficView;
	dlg.m_bSponsors			= Perm.bSponsors;
	dlg.m_bSpotsAdd			= Perm.bSpotsAdd;
	dlg.m_bSpotsEdit		= Perm.bSpotsEdit;
	dlg.m_bSpotsCut			= Perm.bSpotsCut;
	dlg.m_bScheduleAuto		= Perm.bScheduleAuto;
	dlg.m_bScheduleEdit		= Perm.bScheduleEdit;
	dlg.m_bScheduler		= Perm.bScheduler;
	dlg.m_bLineupAdd		= Perm.bLineupAdd;
	dlg.m_bLineupCut		= Perm.bLineupCut;
	dlg.m_bLineupEdit		= Perm.bLineupEdit;
	dlg.m_bCriteriaAdd		= Perm.bCriteriaAdd;
	dlg.m_bCriteriaCut		= Perm.bCriteriaCut;
	dlg.m_bCriteriaEdit		= Perm.bCriteriaEdit;
	dlg.m_bVoiceAdd			= Perm.bVoiceAdd;
	dlg.m_bVoiceCut			= Perm.bVoiceCut;
	dlg.m_bVoiceEdit		= Perm.bVoiceEdit;
	dlg.m_bNewsRoom			= Perm.bNewsRoom;
	dlg.m_bRmsAdd			= Perm.bRmsAdd;
	dlg.m_bRmsEdit			= Perm.bRmsEdit;
	dlg.m_bRmsCut			= Perm.bRmsCut;
	dlg.m_bRmsLineup		= Perm.bRmsLineup;
	dlg.m_bRmsOnAir			= Perm.bRmsOnAir;
	dlg.m_bTextAdd			= Perm.bTextAdd;
	dlg.m_bTextCut			= Perm.bTextCut;
	dlg.m_bTextEdit			= Perm.bTextEdit;
	dlg.m_bTextLineup		= Perm.bTextLineup;
	dlg.m_bTextOnAir		= Perm.bTextOnAir;
	dlg.m_bManagerFolder	= Perm.bManagerFolder;
	dlg.m_bManagerLog		= Perm.bManagerLog;
	dlg.m_bManagerTime		= Perm.bManagerTime;
	dlg.m_bManagerUser		= Perm.bManager;
	dlg.m_bInstrumentals	= Perm.bInstrumentals;

	dlg.m_bPlayListEditContents	= Perm.bPlayListEditContent;

	if( dlg.DoModal()==IDOK )
	{
		CRSSystemUsers rs( g_strMainConnect );

		rs.m_strFilter.Format("ID = '%d'",lUserID );
		rs.Open();

		if( rs.GetRecordCount() )
		{
			rs.Edit();
			rs.m_Name = dlg.m_strName;

		//	rs.m_Permission.SetSize(100);

			rs.m_Permission.SetAt( 0,(BYTE)dlg.m_bManagerUser);
			rs.m_Permission.SetAt( 1,(BYTE)dlg.m_bDiscography);
			rs.m_Permission.SetAt( 2,(BYTE)dlg.m_bNewMusic);
			rs.m_Permission.SetAt( 3,(BYTE)dlg.m_bEditMusic);
			rs.m_Permission.SetAt( 4,(BYTE)dlg.m_bDeleteMusic);

			rs.m_Permission.SetAt( 5,(BYTE)dlg.m_bOnAirManagement );
			rs.m_Permission.SetAt( 6,(BYTE)dlg.m_bJinglesNew );
			rs.m_Permission.SetAt( 7,(BYTE)dlg.m_bJinglesEdit );
			rs.m_Permission.SetAt( 8,(BYTE)dlg.m_bJinglesCut );
			rs.m_Permission.SetAt( 9,(BYTE)dlg.m_bJinglesOnAir );

			rs.m_Permission.SetAt(10,(BYTE)dlg.m_bBlocksAdd );
			rs.m_Permission.SetAt(11,(BYTE)dlg.m_bBlocksEdit);
			rs.m_Permission.SetAt(12,(BYTE)dlg.m_bBlocksCut );

			rs.m_Permission.SetAt(13,(BYTE)dlg.m_bPlayListAdd );
			rs.m_Permission.SetAt(14,(BYTE)dlg.m_bPlayListEdit );
			rs.m_Permission.SetAt(15,(BYTE)dlg.m_bPlayListCut );
			rs.m_Permission.SetAt(16,(BYTE)dlg.m_bPlayListEditContents );

			rs.m_Permission.SetAt(17,(BYTE)dlg.m_bTraffic );
			rs.m_Permission.SetAt(18,(BYTE)dlg.m_bSpotsAdd );
			rs.m_Permission.SetAt(19,(BYTE)dlg.m_bSpotsEdit );
			rs.m_Permission.SetAt(20,(BYTE)dlg.m_bSpotsCut );
			rs.m_Permission.SetAt(21,(BYTE)dlg.m_bSponsors );
			rs.m_Permission.SetAt(22,(BYTE)dlg.m_bTrafficView );
			rs.m_Permission.SetAt(23,(BYTE)dlg.m_bTrafficAdd );
			rs.m_Permission.SetAt(24,(BYTE)dlg.m_bTrafficEdit );
			rs.m_Permission.SetAt(25,(BYTE)dlg.m_bTrafficCut );

			rs.m_Permission.SetAt(26,(BYTE)dlg.m_bScheduler );
			rs.m_Permission.SetAt(27,(BYTE)dlg.m_bLineupAdd );
			rs.m_Permission.SetAt(28,(BYTE)dlg.m_bLineupEdit );
			rs.m_Permission.SetAt(29,(BYTE)dlg.m_bLineupCut );
			rs.m_Permission.SetAt(30,(BYTE)dlg.m_bCriteriaAdd );
			rs.m_Permission.SetAt(31,(BYTE)dlg.m_bCriteriaEdit );
			rs.m_Permission.SetAt(32,(BYTE)dlg.m_bCriteriaCut );
			rs.m_Permission.SetAt(33,(BYTE)dlg.m_bVoiceAdd );
			rs.m_Permission.SetAt(34,(BYTE)dlg.m_bVoiceEdit );
			rs.m_Permission.SetAt(35,(BYTE)dlg.m_bVoiceCut );
			rs.m_Permission.SetAt(36,(BYTE)dlg.m_bScheduleAuto );
			rs.m_Permission.SetAt(37,(BYTE)dlg.m_bScheduleEdit );

			rs.m_Permission.SetAt(38,(BYTE)dlg.m_bNewsRoom );
			rs.m_Permission.SetAt(39,(BYTE)dlg.m_bRmsAdd );
			rs.m_Permission.SetAt(40,(BYTE)dlg.m_bRmsEdit );
			rs.m_Permission.SetAt(41,(BYTE)dlg.m_bRmsCut );
			rs.m_Permission.SetAt(42,(BYTE)dlg.m_bRmsOnAir );
			rs.m_Permission.SetAt(43,(BYTE)dlg.m_bRmsLineup );
			rs.m_Permission.SetAt(44,(BYTE)dlg.m_bTextAdd );
			rs.m_Permission.SetAt(45,(BYTE)dlg.m_bTextEdit );
			rs.m_Permission.SetAt(46,(BYTE)dlg.m_bTextCut );
			rs.m_Permission.SetAt(47,(BYTE)dlg.m_bTextOnAir );
			rs.m_Permission.SetAt(48,(BYTE)dlg.m_bTextLineup );

			rs.m_Permission.SetAt(49,(BYTE)dlg.m_bManagerFolder );
			rs.m_Permission.SetAt(50,(BYTE)dlg.m_bManagerTime );
			rs.m_Permission.SetAt(51,(BYTE)dlg.m_bManagerLog );

			rs.m_Permission.SetAt(52,(BYTE)dlg.m_bInstrumentals);

			rs.Update();

			RefreshList();
		}
		rs.Close();
	}

	if( pResult!=NULL )
		*pResult = 0;
}

void CUserView::OnCutUser()
{
	CListCtrl *pList = &GetListCtrl();
	
	int nPos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( nPos == -1 )
		return;
	
	long int lUserID = pList->GetItemData(nPos);

	if( AfxMessageBox(IDS_CONFIRMUSERREMOVE,MB_YESNO)==IDYES )
	{
		CString str;
		CDatabase db;

		db.Open(g_strMainConnect);
		str.Format("DELETE FROM SystemUsers WHERE ID=%d",lUserID);
		db.ExecuteSQL(str);
		db.Close();
		pList->DeleteItem(nPos);
	}
}
