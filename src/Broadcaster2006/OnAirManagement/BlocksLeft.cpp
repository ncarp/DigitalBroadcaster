// BlocksLeft.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "BlocksLeft.h"
#include "Blocks.h"
#include "..\include\RSBlocksDefinition.h"
#include "..\common\include\global.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG_NEW
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_strBaseURL;
/////////////////////////////////////////////////////////////////////////////
// CBlocksLeft

IMPLEMENT_DYNCREATE(CBlocksLeft, CDigitalLeftView)

CBlocksLeft::CBlocksLeft()
{
}

CBlocksLeft::~CBlocksLeft()
{
}


BEGIN_MESSAGE_MAP(CBlocksLeft, CDigitalLeftView)
	//{{AFX_MSG_MAP(CBlocksLeft)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlocksLeft drawing

void CBlocksLeft::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CBlocksLeft diagnostics

#ifdef _DEBUG
void CBlocksLeft::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CBlocksLeft::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBlocksLeft message handlers
void CBlocksLeft::OnNew()
{
	if( !g_Permissions.bBlocksAdd )
		return;

	CBlocks	dl;

	if( dl.DoModal()==IDOK )
	{
		CRSBlocksDefinition rsDef( m_strConnect );
		CDatabase	db;
		CString		strSQL;
		db.Open(m_strConnect);

		rsDef.m_strSort="ID DESC";
		rsDef.Open();

		rsDef.AddNew();
		rsDef.m_Activ = 1;
		rsDef.m_Fry = dl.m_Fri;
		rsDef.m_InsertionType = dl.m_Precision+1;
		rsDef.m_Mon = dl.m_Mon;
		rsDef.m_Name = dl.m_Name;
		rsDef.m_Sat = dl.m_Sat;
		rsDef.m_Sponsor = dl.m_Sponsor;
		rsDef.m_Sun = dl.m_Sun;
		rsDef.m_Thu = dl.m_Thu;
		rsDef.m_Tue = dl.m_Tue;
		rsDef.m_Wed = dl.m_Wed;
		rsDef.m_Time = dl.m_Time.GetHour()*3600000+dl.m_Time.GetMinute()*60000+dl.m_Time.GetSecond()*1000;
		if( (rsDef.m_Time==0) && (rsDef.m_InsertionType==2))
			rsDef.m_Time=86399999;
		else if( rsDef.m_InsertionType==2 )
			rsDef.m_Time--;
		rsDef.Update();
		rsDef.Requery();

		for( int i=0; i<dl.m_nItems; i++ )
		{
			if( (dl.m_Items[i]->Type==TYPE_BLOCK) || (dl.m_Items[i]->Type==TYPE_SPOT) )
			{
				strSQL.Format("INSERT INTO BlocksComposition (ID,Position, ItemType) VALUES (%d,%d,%d)",rsDef.m_ID,i,dl.m_Items[i]->Type);
				db.ExecuteSQL(strSQL);
			}
			else
			{
				strSQL.Format("INSERT INTO BlocksComposition (ID,Position, ItemType,ItemID,StartingDate,EndingDate,Sun,Mon,Tue,Wed,Thu,Fri,Sat) VALUES (%d,%d,%d,%d,'%d-%d-%d','%d-%d-%d',%d,%d,%d,%d,%d,%d,%d)",
					rsDef.m_ID,
					i,
					dl.m_Items[i]->Type,
					dl.m_Items[i]->ID,
					dl.m_Items[i]->StartingDate.GetYear(),dl.m_Items[i]->StartingDate.GetMonth(),dl.m_Items[i]->StartingDate.GetDay(),
					dl.m_Items[i]->EndingDate.GetYear(),dl.m_Items[i]->EndingDate.GetMonth(),dl.m_Items[i]->EndingDate.GetDay(),
					dl.m_Items[i]->Days[0],
					dl.m_Items[i]->Days[1],
					dl.m_Items[i]->Days[2],
					dl.m_Items[i]->Days[3],
					dl.m_Items[i]->Days[4],
					dl.m_Items[i]->Days[5],
					dl.m_Items[i]->Days[6]);
				db.ExecuteSQL(strSQL);
			}
		}
		
		CTreeCtrl *pTree=&GetTreeCtrl();
		typeTreeItem *lpItem = new typeTreeItem;
		lpItem->lID = rsDef.m_ID;
		lpItem->wType = TYPE_BLOCK;
		HTREEITEM hItem = pTree->InsertItem(dl.m_Name,0,0);
		pTree->SetItemData(hItem,(DWORD)lpItem);

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_BLOCK,lpItem->lID,m_lRadioID);

		rsDef.Close();
	}
}

void CBlocksLeft::OnDoubleClick()
{
	if( !g_Permissions.bBlocksEdit )
		return;

	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	CRSBlocksDefinition rs( m_strConnect );
	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		int			Hour,Min,Sec;
		ldiv_t		temp;
		CBlocks	dl;
		
		rs.m_Name.TrimRight();

		if( rs.m_InsertionType==2 )
			rs.m_Time++;

		temp=ldiv(rs.m_Time,3600000);
		Hour=temp.quot;
		
		temp=ldiv(temp.rem,60000);
		Min=temp.quot;

		temp=ldiv(temp.rem,1000);
		Sec=temp.quot;

		if( Hour==24 )
			Hour=Min=Sec=0;

		dl.m_Name=rs.m_Name;
		dl.m_Sun = rs.m_Sun;
		dl.m_Mon = rs.m_Mon;
		dl.m_Tue = rs.m_Tue;
		dl.m_Wed = rs.m_Wed;
		dl.m_Thu = rs.m_Thu;
		dl.m_Fri = rs.m_Fry;
		dl.m_Sat = rs.m_Sat;
		dl.m_Time.SetTime(Hour,Min,Sec);
		dl.m_Precision = rs.m_InsertionType-1;
		dl.m_Sponsor = rs.m_Sponsor;
		dl.m_ID = rs.m_ID;
		dl.m_strConnect = m_strConnect;

		if( dl.DoModal()==IDOK )
		{
			rs.Edit();
			rs.m_Activ = 1;
			rs.m_Fry = dl.m_Fri;
			rs.m_InsertionType = dl.m_Precision+1;
			rs.m_Mon = dl.m_Mon;
			rs.m_Name = dl.m_Name;
			rs.m_Sat = dl.m_Sat;
			rs.m_Sponsor = dl.m_Sponsor;
			rs.m_Sun = dl.m_Sun;
			rs.m_Thu = dl.m_Thu;
			rs.m_Tue = dl.m_Tue;
			rs.m_Wed = dl.m_Wed;
			rs.m_Time = dl.m_Time.GetHour()*3600000+dl.m_Time.GetMinute()*60000+dl.m_Time.GetSecond()*1000;
			if( (rs.m_Time==0) && (rs.m_InsertionType==2))
				rs.m_Time=86399999;
			else if( rs.m_InsertionType==2 )
				rs.m_Time--;
			rs.Update();
			
			CDatabase	db;
			CString		strSQL;

			strSQL.Format("DELETE From BlocksComposition WHERE ID = %d",dl.m_ID);

			db.Open(m_strConnect);
			db.ExecuteSQL(strSQL);

			for( int i=0; i<dl.m_nItems; i++ )
			{
				if( (dl.m_Items[i]->Type==TYPE_BLOCK) || (dl.m_Items[i]->Type==TYPE_SPOT) )
				{
					strSQL.Format("INSERT INTO BlocksComposition (ID,Position, ItemType) VALUES (%d,%d,%d)",dl.m_ID,i,dl.m_Items[i]->Type);
					db.ExecuteSQL(strSQL);
				}
				else
				{
					strSQL.Format("INSERT INTO BlocksComposition (ID,Position, ItemType,ItemID,StartingDate,EndingDate,Sun,Mon,Tue,Wed,Thu,Fri,Sat) VALUES (%d,%d,%d,%d,'%d-%d-%d','%d-%d-%d',%d,%d,%d,%d,%d,%d,%d)",
						dl.m_ID,
						i,
						dl.m_Items[i]->Type,
						dl.m_Items[i]->ID,
						dl.m_Items[i]->StartingDate.GetYear(),dl.m_Items[i]->StartingDate.GetMonth(),dl.m_Items[i]->StartingDate.GetDay(),
						dl.m_Items[i]->EndingDate.GetYear(),dl.m_Items[i]->EndingDate.GetMonth(),dl.m_Items[i]->EndingDate.GetDay(),
						dl.m_Items[i]->Days[0],
						dl.m_Items[i]->Days[1],
						dl.m_Items[i]->Days[2],
						dl.m_Items[i]->Days[3],
						dl.m_Items[i]->Days[4],
						dl.m_Items[i]->Days[5],
						dl.m_Items[i]->Days[6]);
					db.ExecuteSQL(strSQL);
				}
			}
		
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_BLOCK,dl.m_ID,m_lRadioID);

			pTree->SetItemText(hItem,dl.m_Name);
		}
	}
	rs.Close();
}

void CBlocksLeft::OnCut()
{
	if( !g_Permissions.bBlocksCut )
		return;

	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( AfxMessageBox(IDS_CONFIRMBLOCKREMOVE,MB_YESNO)==IDYES )
	{
		CDatabase	dbOnAir;
		CString		strSQL;
		
		dbOnAir.Open(m_strConnect);

		strSQL.Format("DELETE FROM BlocksDefinition WHERE ID = %d",lpItem->lID);
		dbOnAir.ExecuteSQL(strSQL);

		strSQL.Format("DELETE FROM BlocksComposition WHERE ID = %d",lpItem->lID);
		dbOnAir.ExecuteSQL(strSQL);

		strSQL.Format("DELETE FROM Traffic WHERE BlockID = %d AND Aired = 0",lpItem->lID);
		dbOnAir.ExecuteSQL(strSQL);

		dbOnAir.Close();

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUT,TYPE_BLOCK,lpItem->lID,m_lRadioID);

		pTree->DeleteItem(hItem);

	}
}

void CBlocksLeft::OnSelChange()
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

	if( lpItem->wType==TYPE_BLOCK)
	{
		CString str;

		str.Format("%s\\Block.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,m_strDB);
		SetView(str);
	}
}

void CBlocksLeft::OnInitialUpdate() 
{
	CDigitalLeftView::OnInitialUpdate();
	
	CString str;
	str.LoadString(IDS_BLOCKSMANAGEMENT);
	m_pDocument->SetTitle(str+" - "+m_strRadio);

	if( (g_Permissions.bOnAirManagement) )
		AfxBeginThread(RefreshList,(LPVOID)this);
	else
	{
		str += " - Sem Acesso!";
		m_pDocument->SetTitle(str);
	}
}

UINT CBlocksLeft::RefreshList( LPVOID lp)
{
	CBlocksLeft *pView = (CBlocksLeft *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();
	HTREEITEM	hItem;
	typeTreeItem *lpItem;

	CRSBlocksDefinition rs( pView->m_strConnect );
	rs.m_strFilter = "Activ = 1";
	rs.m_strSort = "Time";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID = rs.m_ID;
		lpItem->wType = TYPE_BLOCK;

		hItem = pTree->InsertItem(rs.m_Name,0,0);
		pTree->SetItemData(hItem,(DWORD)lpItem);
	//	pTree->SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);

		rs.MoveNext();
	}
	rs.Close();

	return 0;
}