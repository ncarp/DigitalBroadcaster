// TimeView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "TimeView.h"
#include "timeDlg.h"
#include "..\include\rsviewtimesignal.h"
#include "..\include\rstime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList	*g_ilTree;
extern CString		g_strMainConnect;

/////////////////////////////////////////////////////////////////////////////
// CTimeView

IMPLEMENT_DYNCREATE(CTimeView, CListView)

CTimeView::CTimeView()
{
}

CTimeView::~CTimeView()
{
}


BEGIN_MESSAGE_MAP(CTimeView, CListView)
	//{{AFX_MSG_MAP(CTimeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeView drawing

void CTimeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTimeView diagnostics

#ifdef _DEBUG
void CTimeView::AssertValid() const
{
	CListView::AssertValid();
}

void CTimeView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTimeView message handlers

int CTimeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style|=LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CListCtrl *pList = &GetListCtrl();
	pList->SetImageList(g_ilTree,LVSIL_SMALL);
	
	ListView_SetExtendedListViewStyleEx(this->m_hWnd,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT,LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT);

	return 0;
}

void CTimeView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	CListCtrl	*pList = &GetListCtrl();	
	CString		strTemp;

	strTemp.LoadString(IDS_TIMESIGNALDEFINITION);
	GetDocument()->SetTitle(strTemp);

	strTemp.LoadString(IDS_NAME);
	pList->InsertColumn(1,strTemp,LVCFMT_LEFT,250);

	strTemp.LoadString(IDS_PATH);
	pList->InsertColumn(2,strTemp,LVCFMT_LEFT,250);

	strTemp.LoadString(IDS_FOLDER);
	pList->InsertColumn(2,strTemp,LVCFMT_LEFT,250);

	RefreshList();
}

void CTimeView::RefreshList()
{
	CListCtrl	*pList = &GetListCtrl();
	int			nPos=0;
	CRSViewTimeSignal	rs( g_strMainConnect );

	pList->DeleteAllItems();

	rs.m_strSort = "Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		rs.m_FolderName.TrimRight();
		rs.m_Path.TrimRight();

		pList->InsertItem(nPos,rs.m_Name,3);
		pList->SetItemText(nPos,1,rs.m_Path);
		pList->SetItemText(nPos,2,rs.m_FolderName);
		pList->SetItemData(nPos,rs.m_ID);

		nPos++;
		rs.MoveNext();
	}
}

void CTimeView::OnNew()
{
	CTimeDlg dlg;

	if( dlg.DoModal()==IDOK )
	{
		CRSTime rs( g_strMainConnect );

		rs.Open();
		rs.AddNew();
		rs.m_Name = dlg.m_strName;
		rs.m_PathID = dlg.m_lPathID;
		rs.m_FolderName = dlg.m_strFolder;
		rs.Update();
		rs.Close();

		RefreshList();
	}
}

void CTimeView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl *pList = &GetListCtrl();
	
	int nPos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( nPos == -1 )
		return;

	long int	lID = pList->GetItemData(nPos);
	CRSViewTimeSignal rs( g_strMainConnect );
	
	rs.m_strFilter.Format("ID = '%d'",lID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		CTimeDlg dlg;
		
		dlg.m_strFolder = rs.m_FolderName;	dlg.m_strFolder.TrimRight();
		dlg.m_strName = rs.m_Name;			dlg.m_strName.TrimRight();
		dlg.m_strPath = rs.m_Path;			dlg.m_strPath.TrimRight();

		rs.Close();

		if( dlg.DoModal()==IDOK )
		{
			CRSTime rsTime(g_strMainConnect);

			rsTime.m_strFilter.Format("ID = '%d'",lID);
			rsTime.Open();
			rsTime.Edit();
			rsTime.m_Name = dlg.m_strName;
			rsTime.m_FolderName = dlg.m_strFolder;
			rsTime.m_PathID = dlg.m_lPathID;
			rsTime.Update();
			rsTime.Close();

			RefreshList();
		}
	}

	if( pResult!=NULL )
		*pResult = 0;
}

void CTimeView::OnCut()
{
	CListCtrl *pList = &GetListCtrl();
	
	int nPos = pList->GetNextItem(-1,LVNI_SELECTED);
	if( nPos == -1 )
		return;

	long int	lID = pList->GetItemData(nPos);

	if( AfxMessageBox(IDS_CONFIRMTIMEREMOVE,MB_YESNO)==IDYES )
	{
		CString		strSQL;
		CDatabase	db;

		strSQL.Format("DELETE FROM Time WHERE ID='%d'",lID);

		db.Open(g_strMainConnect);
		db.ExecuteSQL(strSQL);
		db.Close();
		RefreshList();
	}
}
