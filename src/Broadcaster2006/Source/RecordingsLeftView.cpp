// RecordingsLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\PFLWnd.h"
#include "..\include\RecordingsLeftView.h"
#include "..\include\RSViewRecordingTasks.h"
#include "..\include\RSViewRecordings.h"
#include "..\include\RecordingTask.h"
#include "..\include\RSRecordingTask.h"
#include "..\include\RSViewRecordingTasksSmall.h"
#include "..\include\RSRecordingVersion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordingsLeftView

extern CString g_strMainConnect;
extern CString g_strBaseURL;
extern CPFLWnd *g_wndPFL;
IMPLEMENT_DYNCREATE(CRecordingsLeftView, CDigitalLeftView)

CRecordingsLeftView::CRecordingsLeftView()
{
}

CRecordingsLeftView::~CRecordingsLeftView()
{
}


BEGIN_MESSAGE_MAP(CRecordingsLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CRecordingsLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordingsLeftView drawing

void CRecordingsLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRecordingsLeftView diagnostics

#ifdef _DEBUG
void CRecordingsLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CRecordingsLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRecordingsLeftView message handlers
void CRecordingsLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	CString str;

	str.LoadString(IDS_RECORDINGS);
	m_pDocument->SetTitle(str);

	AfxBeginThread(RefreshList,(LPVOID)this);	
}

UINT CRecordingsLeftView::RefreshList(LPVOID lp)
{
	CRecordingsLeftView *pThis = (CRecordingsLeftView *)lp;
	CTreeCtrl *pTree = &(pThis->GetTreeCtrl());

	pThis->m_bIsRefreshing=TRUE;

	CString		strPrev="",
				str;
	HTREEITEM	hUser,
				hTask,
				hRecording;
	LPtypeTreeItem lpItem;

	
	CRSViewRecordingTasksSmall	rs(g_strMainConnect);
	CRSViewRecordings		rsRec(g_strMainConnect);
	CRSRecordingVersion		rsVersion( g_strMainConnect );

	rsVersion.m_strFilter="ID = 0";
	rsVersion.m_strSort="Name";
	rsVersion.Open();

	rs.m_strSort="UserName, Name";
	rs.Open();
	
	while( !rs.IsEOF() )
	{
		if( rs.m_UserName != strPrev)
		{
			strPrev = rs.m_UserName;
			rs.m_UserName.TrimRight();

			lpItem = new typeTreeItem;
			lpItem->lID = rs.m_TalentID;
			lpItem->wType = TYPE_ONAIRUSER;

			hUser = pTree->InsertItem(rs.m_UserName,5,5);
			pTree->SetItemState(hUser,TVIS_BOLD,TVIS_BOLD);
			pTree->SetItemData(hUser,(DWORD)lpItem);
		}
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_RECORDINGTASK;

		hTask = pTree->InsertItem(rs.m_Name,6,6,hUser);
		pTree->SetItemData(hTask,(DWORD)lpItem);

		rsVersion.m_strFilter.Format("RecordingID = %d",rs.m_ID);
		rsVersion.Requery();
		while( !rsVersion.IsEOF() )
		{
			lpItem = new typeTreeItem;
			lpItem->lID=rsVersion.m_ID;
			lpItem->wType=TYPE_RECORDING;
			
			rsVersion.m_Name.TrimRight();
			hRecording = pTree->InsertItem(rsVersion.m_Name,10,10,hTask);
			pTree->SetItemData(hRecording,(DWORD)lpItem);

			rsVersion.MoveNext();
		}

		if( !rs.IsEOF() )
			rs.MoveNext();
	}

	rs.Close();
	rsVersion.Close();

	pThis->m_bIsRefreshing=FALSE;

	return 0;
}

void CRecordingsLeftView::OnNew()
{
	CRecordingTask dl;

	if( dl.DoModal()==IDOK )
	{
		CRSRecordingTask rs( g_strMainConnect );
		rs.m_strSort="ID DESC";
		rs.Open();
		rs.AddNew();

		rs.m_Completed = 0;
		rs.m_Deadline.SetDateTime(dl.m_Deadline.GetYear(),dl.m_Deadline.GetMonth(),dl.m_Deadline.GetDay(),0,0,0);
		rs.m_Name=dl.m_Name;
		rs.m_TalentID=dl.m_TalentID;
		rs.m_Todo=dl.m_Task;
		rs.Update();
		rs.Requery();

		CTreeCtrl *pTree=&GetTreeCtrl();
		HTREEITEM hUser=FindString(dl.m_TalentName);
		typeTreeItem *lpItem;

		if( hUser==NULL )
		{
			lpItem = new typeTreeItem;
			lpItem->lID=dl.m_TalentID;
			lpItem->wType=TYPE_ONAIRUSER;

			hUser = pTree->InsertItem(dl.m_TalentName,5,5);
			pTree->SetItemData(hUser,(DWORD)lpItem);
			pTree->SetItemState(hUser,TVIS_BOLD,TVIS_BOLD);
			pTree->SortChildren(NULL);
		}
		
		lpItem=new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_RECORDINGTASK;

		HTREEITEM hTask=pTree->InsertItem(dl.m_Name,6,6,hUser);
		pTree->SetItemData(hTask,(DWORD)lpItem);
		pTree->SortChildren(hUser);
		pTree->EnsureVisible(hTask);
	}
}

void CRecordingsLeftView::OnDoubleClick()
{
	CTreeCtrl *pTree=&GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_RECORDINGTASK )
		return;

	CRSViewRecordingTasks rsView( g_strMainConnect );
	rsView.m_strFilter.Format("ID = %d",lpItem->lID);
	rsView.Open();
	if( rsView.GetRecordCount() )
	{
		CRecordingTask dl;

		rsView.m_Name.TrimRight();
		rsView.m_UserName.TrimRight();
		rsView.m_Todo.TrimRight();

		dl.m_Deadline	= rsView.m_Deadline;
		dl.m_Name		= rsView.m_Name;
		dl.m_TalentID	= rsView.m_TalentID;
		dl.m_TalentName = rsView.m_UserName;
		dl.m_Task		= rsView.m_Todo;

		rsView.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSRecordingTask rs( g_strMainConnect );
			rs.m_strFilter.Format("ID = %d",lpItem->lID);
			rs.Open();

			if( rs.GetRecordCount() )
			{
				rs.Edit();

				rs.m_Completed = 0;
				rs.m_Deadline.SetDateTime(dl.m_Deadline.GetYear(),dl.m_Deadline.GetMonth(),dl.m_Deadline.GetDay(),0,0,0);
				rs.m_Name=dl.m_Name;
				rs.m_TalentID=dl.m_TalentID;
				rs.m_Todo=dl.m_Task;
				rs.Update();
				rs.Requery();

				pTree->DeleteItem(hItem);
				HTREEITEM hUser=FindString(dl.m_TalentName);
				typeTreeItem *lpItem;

				if( hUser==NULL )
				{
					lpItem = new typeTreeItem;
					lpItem->lID=dl.m_TalentID;
					lpItem->wType=TYPE_ONAIRUSER;

					hUser = pTree->InsertItem(dl.m_TalentName,5,5);
					pTree->SetItemData(hUser,(DWORD)lpItem);
					pTree->SetItemState(hUser,TVIS_BOLD,TVIS_BOLD);
					pTree->SortChildren(NULL);
				}
		
				lpItem=new typeTreeItem;
				lpItem->lID=rs.m_ID;
				lpItem->wType=TYPE_RECORDINGTASK;

				HTREEITEM hTask=pTree->InsertItem(dl.m_Name,6,6,hUser);
				pTree->SetItemData(hTask,(DWORD)lpItem);
				pTree->SortChildren(hUser);
				pTree->EnsureVisible(hTask);
			}
			rs.Close();
		}
	}
	else
		rsView.Close();
}

void CRecordingsLeftView::OnCut()
{
	CTreeCtrl *pTree=&GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_RECORDINGTASK )
		return;

	if( AfxMessageBox(IDS_CONFIRMREMOVERECORDINGTASK,MB_YESNO)==IDYES )
	{
		CDatabase db;
		db.Open( g_strMainConnect);

		CString strSQL;
		strSQL.Format("DELETE FROM RecordingTask WHERE ID = %d",lpItem->lID);
		db.ExecuteSQL(strSQL);

		strSQL.Format("DELETE FROM RecordingVersion WHERE RecordingID = %d",lpItem->lID);
		db.ExecuteSQL(strSQL);

		pTree->DeleteItem(hItem);
	}
}

void CRecordingsLeftView::OnSelChange()
{
	CTreeCtrl *pTree=&GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
	{
		SetView(g_strBaseURL+"\\EmptyPage.asp");
		return;
	}

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
	{
		SetView(g_strBaseURL+"\\EmptyPage.asp");
		return;
	}

	if( lpItem->wType==TYPE_RECORDINGTASK )
	{
		CString str;
		str.Format("%s\\RecordingTask.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(str);
		return;
	}
	else
	{
		SetView(g_strBaseURL+"\\EmptyPage.asp");
		return;
	}
}

void CRecordingsLeftView::OnPFL()
{
	CTreeCtrl *pTree=&GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_RECORDING )
		return;

	g_wndPFL->SetSound(TYPE_RECORDING,lpItem->lID);
	g_wndPFL->RestoreWindow();
}