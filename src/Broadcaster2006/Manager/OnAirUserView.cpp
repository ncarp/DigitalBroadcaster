// OnAirUserView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "OnAirUserView.h"
#include "OnAirUSer.h"
#include "..\include\RSOnAirUsers.h"
#include "..\OnAir\OnAirDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_strMainConnect;
/////////////////////////////////////////////////////////////////////////////
// COnAirUserView

IMPLEMENT_DYNCREATE(COnAirUserView, CDigitalLeftView)

COnAirUserView::COnAirUserView()
{
}

COnAirUserView::~COnAirUserView()
{
}


BEGIN_MESSAGE_MAP(COnAirUserView, CDigitalLeftView)
	//{{AFX_MSG_MAP(COnAirUserView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirUserView drawing

void COnAirUserView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// COnAirUserView diagnostics

#ifdef _DEBUG
void COnAirUserView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void COnAirUserView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COnAirUserView message handlers

void COnAirUserView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CString strTitle;
	strTitle.LoadString(IDS_ONAIRUSERS);
	GetDocument()->SetTitle(strTitle);

	CTreeCtrl		*pTree = &GetTreeCtrl();
	typeTreeItem	*lpItem;	
	HTREEITEM		hItem;
	
	CRSOnAirUsers rs( g_strMainConnect );
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	pTree->DeleteAllItems();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		
		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_ONAIRUSER;

		hItem=pTree->InsertItem(rs.m_Name,5,5);
		pTree->SetItemData(hItem,(DWORD)lpItem);

		rs.MoveNext();
	}
}

void COnAirUserView::OnNew()
{
	COnAirUser dl;

	if( dl.DoModal()==IDOK )
	{
		CRSOnAirUsers rs( g_strMainConnect );
		CString strTemp=dl.m_Name;
		strTemp.Replace("'","''");

		rs.m_strFilter.Format("Name = '%s'",strTemp);
		
		rs.Open();
		if( rs.GetRecordCount()==0 )
			rs.AddNew();
		else
			rs.Edit();
			
		rs.m_Activ = 1;
		rs.m_Blocks = dl.m_Blocks;
		rs.m_MusicEditing = dl.m_MusicEditing;
		rs.m_Name = dl.m_Name;
		rs.m_Password = dl.m_Pass1;
		rs.m_Scheduler = dl.m_Schedule;
		rs.m_SoundRecorder = dl.m_SoundRecorder;
		rs.Update();
		rs.Requery();
		
		OnInitialUpdate();
	}
}

void COnAirUserView::OnDoubleClick()
{
	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem=pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_ONAIRUSER )
		return;

	CRSOnAirUsers rs( g_strMainConnect );
	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();
	if( rs.GetRecordCount()!=0 )
	{
		COnAirUser dl;
		dl.m_Blocks = rs.m_Blocks;
		dl.m_MusicEditing = rs.m_MusicEditing;
		dl.m_Name = rs.m_Name; dl.m_Name.TrimRight();
		dl.m_Pass1 = rs.m_Password; dl.m_Pass1.TrimRight();
		dl.m_Pass2 = rs.m_Password; dl.m_Pass2.TrimRight();
		dl.m_Schedule = rs.m_Scheduler;
		dl.m_SoundRecorder = rs.m_SoundRecorder;

		if( dl.DoModal()==IDOK )
		{
			rs.Edit();
			rs.m_Activ = 1;
			rs.m_Blocks = dl.m_Blocks;
			rs.m_MusicEditing = dl.m_MusicEditing;
			rs.m_Name = dl.m_Name;
			rs.m_Password = dl.m_Pass1;
			rs.m_Scheduler = dl.m_Schedule;
			rs.m_SoundRecorder = dl.m_SoundRecorder;
			rs.Update();

			OnInitialUpdate();
		}
	}
}

void COnAirUserView::OnCut()
{
	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem=pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_ONAIRUSER )
		return;

	if( AfxMessageBox(IDS_CONFIRMUSERREMOVE,MB_YESNO)==IDYES )
	{
		CString str;
		CDatabase db;

		db.Open(g_strMainConnect);
		str.Format("DELETE FROM OnAirUser WHERE ID=%d",lpItem->lID);
		db.ExecuteSQL(str);
		db.Close();
		OnInitialUpdate();
	}
}