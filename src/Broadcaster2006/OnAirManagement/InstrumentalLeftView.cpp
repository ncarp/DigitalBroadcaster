// InstrumentalLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "InstrumentalLeftView.h"
#include "..\common\include\rsInstrumentals.h"
#include "..\common\include\rsviewinstrumentals.h"
#include "..\common\include\permissions.h"
#include "..\common\include\global.h"
#include "..\common\include\defines.h"
#include "..\OnAir\PFLWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT		g_nFormat;
extern CPFLWnd	*g_wndPFL;

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalLeftView

IMPLEMENT_DYNCREATE(CInstrumentalLeftView, CDigitalLeftView)

CInstrumentalLeftView::CInstrumentalLeftView()
{
}

CInstrumentalLeftView::~CInstrumentalLeftView()
{
}


BEGIN_MESSAGE_MAP(CInstrumentalLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CInstrumentalLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalLeftView drawing

void CInstrumentalLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalLeftView diagnostics

#ifdef _DEBUG
void CInstrumentalLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CInstrumentalLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInstrumentalLeftView message handlers

DROPEFFECT CInstrumentalLeftView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	if( !pDataObject->IsDataAvailable( g_nFormat ) )
		return DROPEFFECT_NONE;

	HGLOBAL hData=pDataObject->GetGlobalData(g_nFormat);
	m_lpDragItem=(typeTreeDrag *)::GlobalLock(hData);

	if( (m_lpDragItem->Item.wType != TYPE_JINGLE) ) //&& (m_lpDragItem->Item.wType!=TYPE_MUSIC) )
	{
		::GlobalUnlock(hData);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}

	return DROPEFFECT_COPY;	
}

BOOL CInstrumentalLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	if( m_lpDragItem==NULL )
		return DROPEFFECT_NONE;

	DrawDragItem(m_lpDragItem->strName,m_OldPoint);
	m_OldPoint.x=m_OldPoint.y=-32000;

	CRSInstrumentals rs( m_strConnect );

	rs.m_strFilter.Format("TypeID = '%d' AND ElementID = '%d'",
							m_lpDragItem->Item.wType,
							m_lpDragItem->Item.lID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.Close();
//		AfxMessageBox(IDS_JINGLEALLREADYEXISTS);
		m_lpDragItem=NULL;
		return DROPEFFECT_NONE;
	}
	else
	{
		CString strSQL;

		strSQL.Format("INSERT INTO Instrumentals (TypeID,ElementID) VALUES ('%d','%d')",
						m_lpDragItem->Item.wType,
						m_lpDragItem->Item.lID );

		rs.m_pDatabase->ExecuteSQL(strSQL);

		CRSViewInstrumentals rsView(m_strConnect);
		rsView.m_strFilter.Format("TypeID = '%d' AND ElementID = '%d'",
									m_lpDragItem->Item.wType,
									m_lpDragItem->Item.lID);
		rsView.Open();
		rsView.m_Title.TrimRight();
		rsView.m_Artist.TrimRight();

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADDINSTRUMENTAL,rsView.m_TypeID,rsView.m_ElementID,m_lRadioID,rsView.m_ID);
		
		CTreeCtrl	*pTree=&GetTreeCtrl();
		HTREEITEM	hItem;

		if( rsView.m_TypeID==TYPE_MUSIC )
		{
			HTREEITEM hArtist=FindString(rsView.m_Artist);
			
			if( hArtist==NULL )
			{
				hArtist = pTree->InsertItem(rsView.m_Artist,16,16,m_hMusic);
				pTree->SetItemData(hArtist,0);
				pTree->SetItemState(hArtist,TVIS_BOLD,TVIS_BOLD);
			}


			typeTreeItem *lpItem=new typeTreeItem;
			lpItem->lID=rsView.m_ElementID;
			lpItem->wType=TYPE_MUSIC;

			hItem=pTree->InsertItem(rsView.m_Title,17,17,hArtist);
			pTree->SetItemData(hItem,(DWORD)lpItem);
			pTree->EnsureVisible(hItem);
		}
		else
		{
			HTREEITEM hType=FindString(rsView.m_Artist);
			
			if( hType==NULL )
			{
				hType= pTree->InsertItem(rsView.m_Artist,4,4,m_hJingles);
				pTree->SetItemData(hType,0);
				pTree->SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
			}


			typeTreeItem *lpItem=new typeTreeItem;
			lpItem->lID=rsView.m_ElementID;
			lpItem->wType=TYPE_JINGLE;

			hItem=pTree->InsertItem(rsView.m_Title,4,4,hType);
			pTree->SetItemData(hItem,(DWORD)lpItem);
			pTree->EnsureVisible(hItem);
		}

		rsView.Close();
	}

	m_lpDragItem=NULL;
	return DROPEFFECT_COPY;
}

void CInstrumentalLeftView::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CTreeCtrl				*pTree = &GetTreeCtrl();
	CRSViewInstrumentals	rs( m_strConnect );
	CString					strLast="";
	HTREEITEM				hParent,
							hItem;
	typeTreeItem			*pItem;

	rs.m_strSort = "TypeID,Artist,Title";
	rs.Open();

	m_hMusic=pTree->InsertItem("Musicas",17,17);
	m_hJingles=pTree->InsertItem("Jingles",4,4);
	
	pTree->SetItemState(m_hMusic,TVIS_BOLD,TVIS_BOLD);
	pTree->SetItemState(m_hJingles,TVIS_BOLD,TVIS_BOLD);

	while( !rs.IsEOF()  )
	{
		rs.m_Artist.TrimRight();
		if( (rs.m_Artist != strLast) )
		{
			if( rs.m_TypeID==TYPE_MUSIC )
				hParent = pTree->InsertItem(rs.m_Artist,16,16,m_hMusic);
			else
				hParent = pTree->InsertItem(rs.m_Artist,14,14,m_hJingles);

			pTree->SetItemState(hParent,TVIS_BOLD,TVIS_BOLD);
			pTree->SetItemData(hParent,(DWORD)NULL);
			strLast = rs.m_Artist;
		}

		rs.m_Title.TrimRight();
		if( rs.m_TypeID==TYPE_MUSIC )
			hItem = pTree->InsertItem(rs.m_Title,17,17,hParent);
		else
			hItem = pTree->InsertItem(rs.m_Title,4,4,hParent);

		pItem = new typeTreeItem;
		pItem->lID = rs.m_ElementID;
		pItem->wType = (WORD)rs.m_TypeID;
		pTree->SetItemData(hItem,(DWORD)pItem);

		rs.MoveNext();
	}

	rs.Close();
}


void CInstrumentalLeftView::OnSelChange()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();
	CString		strURL;

	strURL.Format("%s/emptypage.asp",g_strBaseURL);

	if( hItem!=NULL )
	{
		typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

		if( lpItem!=NULL )
		{
			switch( lpItem->wType )
			{
			case TYPE_MUSIC:
				strURL.Format("%s/song.asp?ID=%d",g_strBaseURL,lpItem->lID);
				break;
			case TYPE_JINGLE:
				strURL.Format("%s/jingle.asp?ID=%d",g_strBaseURL,lpItem->lID);
				break;
			}
		}
	}

	SetView(strURL);
}

void CInstrumentalLeftView::OnPFL()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem!=NULL )
	{
		typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

		if( lpItem!=NULL )
		{
			g_wndPFL->SetSound(lpItem->wType,lpItem->lID);
			g_wndPFL->RestoreWindow();
		}
	}
}

void CInstrumentalLeftView::OnRDoubleClick()
{
	OnPFL();
};

void CInstrumentalLeftView::OnCut()
{
	CTreeCtrl	*pTree = &GetTreeCtrl();
	HTREEITEM	hItem = pTree->GetSelectedItem();

	if( hItem!=NULL )
	{
		typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);

		if( lpItem!=NULL )
		{
			CString		strSQL;
			CDatabase	db;

			strSQL.Format("DELETE FROM Instrumentals WHERE TypeID=%d AND ElementID=%d",lpItem->wType,lpItem->lID);
			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);

			pTree->DeleteItem(hItem);
		}
	}
}
