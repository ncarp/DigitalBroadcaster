// HDView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "HDView.h"
#include "Folder.h"
#include "..\include\rspath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString		g_strMainConnect;
extern CImageList	*g_ilTree;
/////////////////////////////////////////////////////////////////////////////
// CHDView

IMPLEMENT_DYNCREATE(CHDView, CListView)

CHDView::CHDView()
{
}

CHDView::~CHDView()
{
}


BEGIN_MESSAGE_MAP(CHDView, CListView)
	//{{AFX_MSG_MAP(CHDView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHDView drawing

void CHDView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CHDView diagnostics

#ifdef _DEBUG
void CHDView::AssertValid() const
{
	CListView::AssertValid();
}

void CHDView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHDView message handlers

void CHDView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	CListCtrl	*pList = &GetListCtrl();	
	CString		strTemp;

	strTemp.LoadString(IDS_FOLDERMANAGMENT);
	GetDocument()->SetTitle(strTemp);

	strTemp.LoadString(IDS_PATH);
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,250);

	strTemp.LoadString(IDS_MUSIC);
	pList->InsertColumn(2,strTemp,LVCFMT_CENTER,50);

	strTemp.LoadString(IDS_JINGLES);
	pList->InsertColumn(3,strTemp,LVCFMT_CENTER,50);

	strTemp.LoadString(IDS_SPOTS);
	pList->InsertColumn(4,strTemp,LVCFMT_CENTER,50);

	strTemp.LoadString(IDS_RMS);
	pList->InsertColumn(5,strTemp,LVCFMT_CENTER,50);

	strTemp.LoadString(IDS_TAKES);
	pList->InsertColumn(5,strTemp,LVCFMT_CENTER,50);

	strTemp.LoadString(IDS_TIME);
	pList->InsertColumn(6,strTemp,LVCFMT_CENTER,50);

	strTemp.LoadString(IDS_PRODUCER);
	pList->InsertColumn(7,strTemp,LVCFMT_CENTER,50);

	CRSPath rs(g_strMainConnect);
	int		Pos=0;

	rs.m_strSort="Music desc, Jingles desc, Spots desc, RMs desc, Takes desc, timesignal desc, producer desc, Path";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Path.TrimRight();

		pList->InsertItem(Pos,rs.m_Path,22);
		pList->SetItemData(Pos,rs.m_ID);

		if( rs.m_Music )
			pList->SetItem(Pos,1,LVIF_IMAGE,"",17,0,0,0);

		if( rs.m_Jingles )
			pList->SetItem(Pos,2,LVIF_IMAGE,"",4,0,0,0);

		if( rs.m_Spots )
			pList->SetItem(Pos,3,LVIF_IMAGE,"",1,0,0,0);

		if( rs.m_RMs )
			pList->SetItem(Pos,4,LVIF_IMAGE,"",9,0,0,0);

		if( rs.m_Takes )
			pList->SetItem(Pos,5,LVIF_IMAGE,"",5,0,0,0);

		if( rs.m_TimeSignal )
			pList->SetItem(Pos,6,LVIF_IMAGE,"",3,0,0,0);

		if( rs.m_Producer )
			pList->SetItem(Pos,7,LVIF_IMAGE,"",7,0,0,0);

		rs.MoveNext();
		Pos++;
	}
}

int CHDView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style|=LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CListCtrl *pList = &GetListCtrl();
	pList->SetImageList(g_ilTree,LVSIL_SMALL);
	
	ListView_SetExtendedListViewStyleEx(this->m_hWnd,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT);
		
	return 0;
}

void CHDView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl *pList = &GetListCtrl();
	
	int nPos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( nPos == -1 )
		return;

	long int	lID = pList->GetItemData(nPos);
	CRSPath		rs( g_strMainConnect );
	CFolder		dlg;
	rs.m_strFilter.Format("ID = '%d'",lID);
	rs.Open();

	dlg.m_strPath = rs.m_Path;
	dlg.m_strPath.TrimRight();
	dlg.m_bJingles	= rs.m_Jingles;
	dlg.m_bMusic	= rs.m_Music;
	dlg.m_bProducer	= rs.m_Producer;
	dlg.m_bRMs		= rs.m_RMs;
	dlg.m_bSpots	= rs.m_Spots;
	dlg.m_bTakes	= rs.m_Takes;
	dlg.m_bTime		= rs.m_TimeSignal;

	if( dlg.DoModal()==IDOK )
	{
		rs.Edit();
		rs.m_Path		= dlg.m_strPath;
		rs.m_Jingles	= (dlg.m_bJingles==0) ? 0:1;
		rs.m_Music		= (dlg.m_bMusic==0) ? 0:1;
		rs.m_Producer	= (dlg.m_bProducer==0) ? 0:1;
		rs.m_RMs		= (dlg.m_bRMs==0) ? 0:1;
		rs.m_Spots		= (dlg.m_bSpots==0) ? 0:1;
		rs.m_Takes		= (dlg.m_bTakes==0) ? 0:1;
		rs.m_TimeSignal = (dlg.m_bTime==0) ? 0:1;
		rs.Update();

		Refresh();
	}

	if( pResult!=NULL )
		*pResult = 0;
}

void CHDView::Refresh()
{
	CListCtrl *pList = &GetListCtrl();
	pList->DeleteAllItems();

	CRSPath rs(g_strMainConnect);
	int		Pos=0;

	rs.m_strSort="Music desc, Jingles desc, Spots desc, RMs desc, Takes desc, timesignal desc, producer desc, Path";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Path.TrimRight();

		pList->InsertItem(Pos,rs.m_Path,22);
		pList->SetItemData(Pos,rs.m_ID);

		if( rs.m_Music )
			pList->SetItem(Pos,1,LVIF_IMAGE,"",17,0,0,0);

		if( rs.m_Jingles )
			pList->SetItem(Pos,2,LVIF_IMAGE,"",4,0,0,0);

		if( rs.m_Spots )
			pList->SetItem(Pos,3,LVIF_IMAGE,"",1,0,0,0);

		if( rs.m_RMs )
			pList->SetItem(Pos,4,LVIF_IMAGE,"",9,0,0,0);

		if( rs.m_Takes )
			pList->SetItem(Pos,5,LVIF_IMAGE,"",5,0,0,0);

		if( rs.m_TimeSignal )
			pList->SetItem(Pos,6,LVIF_IMAGE,"",3,0,0,0);

		if( rs.m_Producer )
			pList->SetItem(Pos,7,LVIF_IMAGE,"",7,0,0,0);

		rs.MoveNext();
		Pos++;
	}
}

void CHDView::AddFolder()
{
	CFolder dlg;

	if( dlg.DoModal()==IDOK )
	{
		CRSPath rs( g_strMainConnect );

		rs.Open();
		rs.AddNew();
		rs.m_Path = dlg.m_strPath;
		rs.m_Jingles	= (dlg.m_bJingles==0) ? 0:1;
		rs.m_Music		= (dlg.m_bMusic==0) ? 0:1;
		rs.m_Producer	= (dlg.m_bProducer==0) ? 0:1;
		rs.m_RMs		= (dlg.m_bRMs==0) ? 0:1;
		rs.m_Spots		= (dlg.m_bSpots==0) ? 0:1;
		rs.m_Takes		= (dlg.m_bTakes==0) ? 0:1;
		rs.m_TimeSignal = (dlg.m_bTime==0) ? 0:1;
		rs.Update();
		rs.Close();

		Refresh();
	}
}
