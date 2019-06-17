// Blocks.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "Blocks.h"
#include "BlockDetail.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\PFLWnd.h"
#include "..\include\RSViewJinglesList.h"
#include "..\include\RSTime.h"
#include "..\include\RSBlocksComposition.h"
#include "..\include\RSViewJinglesSmallList.h"
#include "..\include\RSViewRms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilTree;
extern	CString		g_strMainConnect;
extern	CPFLWnd		*g_wndPFL;

/////////////////////////////////////////////////////////////////////////////
// CBlocks dialog


CBlocks::CBlocks(CWnd* pParent /*=NULL*/)
	: CDialog(CBlocks::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlocks)
	m_Fri = FALSE;
	m_Mon = FALSE;
	m_Name = _T("");
	m_Precision = -1;
	m_Tue = FALSE;
	m_Time = COleDateTime::GetCurrentTime();
	m_Thu = FALSE;
	m_Sun = FALSE;
	m_Sat = FALSE;
	m_Wed = FALSE;
	//}}AFX_DATA_INIT
	m_Sponsor=m_Normal=FALSE;
	m_ID = 0;
}


void CBlocks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlocks)
	DDX_Control(pDX, IDC_LIBRARY, m_cLibrary);
	DDX_Control(pDX, IDC_CONTENTS, m_cContents);
	DDX_Check(pDX, IDC_FRI, m_Fri);
	DDX_Check(pDX, IDC_MON, m_Mon);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_CBIndex(pDX, IDC_PRECISION, m_Precision);
	DDX_Check(pDX, IDC_TUE, m_Tue);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_Time);
	DDX_Check(pDX, IDC_THU, m_Thu);
	DDX_Check(pDX, IDC_SUN, m_Sun);
	DDX_Check(pDX, IDC_SAT, m_Sat);
	DDX_Check(pDX, IDC_WED, m_Wed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlocks, CDialog)
	//{{AFX_MSG_MAP(CBlocks)
	ON_BN_CLICKED(IDC_SPONSOR, OnSponsor)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
//	ON_BN_CLICKED(IDC_PFL, OnPfl)
	ON_BN_CLICKED(IDC_NORMAL, OnNormal)
	ON_BN_CLICKED(IDC_MOVEUP, OnMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnMovedown)
	ON_NOTIFY(NM_DBLCLK, IDC_LIBRARY, OnDblclkLibrary)
	ON_NOTIFY(NM_DBLCLK, IDC_CONTENTS, OnDblclkContents)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlocks message handlers

void CBlocks::OnOK() 
{
	UpdateData();

	m_Name.TrimRight();
	if( m_Name.GetLength()==0 )
		return;
	
	if( !( m_Sun || m_Tue || m_Mon || m_Wed || m_Thu || m_Fri || m_Sat ) )
		return;

	if( m_Precision==CB_ERR )
		return;

	if( !( m_Normal || m_Sponsor ) )
		return;

	m_nItems = m_cContents.GetItemCount();
	for( int i=0; i<m_nItems; i++ )
		m_Items[i]=(typeBlockItem *)m_cContents.GetItemData(i);

	CDialog::OnOK();
}

void CBlocks::OnSponsor() 
{
	m_Normal=FALSE;
	m_Sponsor=TRUE;
}

void CBlocks::OnRemove() 
{
	int Pos=m_cContents.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1)
		return;
	
	typeBlockItem *lpItem=(typeBlockItem *)m_cContents.GetItemData(Pos);
	if( lpItem==NULL )
		return;

	if( lpItem->Type==TYPE_BLOCK )
		return;

	m_cContents.DeleteItem(Pos);
	
}

void CBlocks::OnPfl() 
{
	HTREEITEM		hItem = m_cLibrary.GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)m_cLibrary.GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
		return;
	
	if( lpItem->wType!=TYPE_JINGLE )
		return;

	g_wndPFL->SetSound(TYPE_JINGLE,lpItem->lID);
	g_wndPFL->RestoreWindow();
}

void CBlocks::OnNormal() 
{
	m_Normal=TRUE;
	m_Sponsor=FALSE;
}

void CBlocks::OnMoveup() 
{
	int Pos=m_cContents.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;
	
	int NewPos;
	LVITEM Item;

	CString strName=m_cContents.GetItemText(Pos,0);
	CString strData=m_cContents.GetItemText(Pos,1);
	int nImage=m_cContents.GetItemState(Pos,LVIF_IMAGE);

	Item.mask=LVIF_IMAGE|LVIF_INDENT;
	Item.iItem=Pos;
	Item.iSubItem=0;
	m_cContents.GetItem(&Item);

	DWORD lpItem = m_cContents.GetItemData(Pos);

	if( Pos==0 )
		NewPos=m_cContents.GetItemCount()-1;
	else
		NewPos=Pos-1;

	m_cContents.DeleteItem(Pos);
	Item.iItem=m_cContents.InsertItem(NewPos,strName);
	m_cContents.SetItem(&Item);
	m_cContents.SetItemText(NewPos,1,strData);
	m_cContents.SetItemData(NewPos,lpItem);
	m_cContents.SetItemState(NewPos,LVIS_SELECTED,LVIS_SELECTED);
}

void CBlocks::OnMovedown() 
{
	int Pos=m_cContents.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;
	
	int NewPos;
	LVITEM Item;

	CString strName=m_cContents.GetItemText(Pos,0);
	CString strData=m_cContents.GetItemText(Pos,1);
	int nImage=m_cContents.GetItemState(Pos,LVIF_IMAGE);

	Item.mask=LVIF_IMAGE|LVIF_INDENT;
	Item.iItem=Pos;
	Item.iSubItem=0;
	m_cContents.GetItem(&Item);

	DWORD lpItem=m_cContents.GetItemData(Pos);

	if( Pos==m_cContents.GetItemCount()-1 )
		NewPos=0;
	else
		NewPos=Pos+1;

	m_cContents.DeleteItem(Pos);
	Item.iItem=m_cContents.InsertItem(NewPos,strName);
	m_cContents.SetItem(&Item);
	m_cContents.SetItemText(NewPos,1,strData);
	m_cContents.SetItemData(NewPos,lpItem);
	m_cContents.SetItemState(NewPos,LVIS_SELECTED,LVIS_SELECTED);
	
}

void CBlocks::OnDblclkLibrary(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	HTREEITEM hItem = m_cLibrary.GetSelectedItem();
	if( hItem==NULL )
		return;

	typeTreeItem *lpItem=(typeTreeItem *)m_cLibrary.GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( (lpItem->wType==TYPE_RM) || (lpItem->wType==TYPE_JINGLE) || (lpItem->wType==TYPE_SPOT) || (lpItem->wType==TYPE_TIMESIGNAL) )
	{
		int	Pos = m_cContents.GetNextItem(-1,LVNI_SELECTED);
		if( Pos == -1 )
			Pos = m_cContents.GetItemCount();

		if( lpItem->wType==TYPE_SPOT )
		{
			CString strItem=m_cLibrary.GetItemText(hItem);
			typeBlockItem *lpBlockItem = new typeBlockItem;
			lpBlockItem->Type = lpItem->wType;
			lpBlockItem->ID = 0;
			

			LVITEM	lvItem;
			lvItem.mask=LVIF_INDENT|LVIF_PARAM;
			lvItem.iItem=Pos;
			lvItem.iSubItem=0;
			lvItem.iIndent=1;
			lvItem.lParam=(DWORD)lpBlockItem;
		
			m_cContents.InsertItem(Pos,strItem,1);
			m_cContents.SetItem(&lvItem);
		}
		else
		{
			HTREEITEM hParent=m_cLibrary.GetParentItem(hItem);
			CString	strParent=m_cLibrary.GetItemText(hParent),
					strItem=m_cLibrary.GetItemText(hItem),
					strTemp,
					strDate;
			int		iImage;

			if( lpItem->wType==TYPE_JINGLE )
				iImage=4;
			else
				iImage=3;

			typeBlockItem *lpBlockItem = new typeBlockItem;
			lpBlockItem->Type = lpItem->wType;
			lpBlockItem->ID = lpItem->lID;
			lpBlockItem->EndingDate.SetDateTime(2500,12,31,0,0,0);
			lpBlockItem->StartingDate = COleDateTime::GetCurrentTime();
			lpBlockItem->Days[0] = 1;
			lpBlockItem->Days[1] = 1;
			lpBlockItem->Days[2] = 1;
			lpBlockItem->Days[3] = 1;
			lpBlockItem->Days[4] = 1;
			lpBlockItem->Days[5] = 1;
			lpBlockItem->Days[6] = 1;

			strDate.Format(IDS_FORMAT_FROMTO,lpBlockItem->StartingDate.GetYear(),lpBlockItem->StartingDate.GetMonth(),lpBlockItem->StartingDate.GetDay(),
								2500,12,31);
			
			strTemp.LoadString(IDS_SUN);
			strDate+=(", "+strTemp);
			strTemp.LoadString(IDS_MON);
			strDate+=(", "+strTemp);
			strTemp.LoadString(IDS_TUE);
			strDate+=(", "+strTemp);
			strTemp.LoadString(IDS_WED);
			strDate+=(", "+strTemp);
			strTemp.LoadString(IDS_THU);
			strDate+=(", "+strTemp);
			strTemp.LoadString(IDS_FRI);
			strDate+=(", "+strTemp);
			strTemp.LoadString(IDS_SAT);
			strDate+=(", "+strTemp);

			LVITEM	lvItem;
			lvItem.mask=LVIF_INDENT|LVIF_PARAM;
			lvItem.iItem=Pos;
			lvItem.iSubItem=0;
			lvItem.iIndent=0;
			lvItem.lParam=(DWORD)lpBlockItem;
		
			m_cContents.InsertItem(Pos,strParent+" - "+strItem,iImage);
			m_cContents.SetItem(&lvItem);
			m_cContents.SetItemText(Pos,1,strDate);
		}
	}
}

void CBlocks::OnDblclkContents(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	int Pos=m_cContents.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1)
		return;
	
	typeBlockItem *lpItem=(typeBlockItem *)m_cContents.GetItemData(Pos);
	if( lpItem==NULL )
		return;

	if( lpItem->Type==TYPE_BLOCK )
		return;

	if( lpItem->Type==TYPE_SPOT )
		return;

	CBlockDetail dl;
	dl.m_Name			= m_cContents.GetItemText(Pos,0);
	dl.m_StartingDate	= lpItem->StartingDate;
	dl.m_EndingDate		= lpItem->EndingDate;
	dl.m_Sun			= lpItem->Days[0];
	dl.m_Mon			= lpItem->Days[1];
	dl.m_Tue			= lpItem->Days[2];
	dl.m_Wed			= lpItem->Days[3];
	dl.m_Thu			= lpItem->Days[4];
	dl.m_Fri			= lpItem->Days[5];
	dl.m_Sat			= lpItem->Days[6];
	if( dl.DoModal()==IDOK )
	{
		CString strDate,
				strTemp;

		lpItem->StartingDate	= dl.m_StartingDate;
		lpItem->EndingDate		= dl.m_EndingDate;
		lpItem->Days[0]			= dl.m_Sun;
		lpItem->Days[1]			= dl.m_Mon;
		lpItem->Days[2]			= dl.m_Tue;
		lpItem->Days[3]			= dl.m_Wed;
		lpItem->Days[4]			= dl.m_Thu;
		lpItem->Days[5]			= dl.m_Fri;
		lpItem->Days[6]			= dl.m_Sat;

	
		strDate.Format(IDS_FORMAT_FROMTO,lpItem->StartingDate.GetYear(),lpItem->StartingDate.GetMonth(),lpItem->StartingDate.GetDay(),
								lpItem->EndingDate.GetYear(),lpItem->EndingDate.GetMonth(),lpItem->EndingDate.GetDay() );
		
		if( dl.m_Sun )
		{
			strTemp.LoadString(IDS_SUN);
			strDate+=(", "+strTemp);
		}
		if( dl.m_Mon )
		{
			strTemp.LoadString(IDS_MON);
			strDate+=(", "+strTemp);
		}
		if( dl.m_Tue )
		{
			strTemp.LoadString(IDS_TUE);
			strDate+=(", "+strTemp);
		}
		if( dl.m_Wed )
		{
			strTemp.LoadString(IDS_WED);
			strDate+=(", "+strTemp);
		}
		if( dl.m_Thu )
		{
			strTemp.LoadString(IDS_THU);
			strDate+=(", "+strTemp);
		}
		if( dl.m_Fri )
		{
			strTemp.LoadString(IDS_FRI);
			strDate+=(", "+strTemp);
		}
		if( dl.m_Sat )
		{
			strTemp.LoadString(IDS_SAT);
			strDate+=(", "+strTemp);
		}
		m_cContents.SetItemText(Pos,1,strDate);
	}
}

BOOL CBlocks::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rect;
	CString	strPrev,
			strTemp;

	m_cLibrary.SetImageList(g_ilTree,TVSIL_NORMAL);
	m_cContents.SetImageList(g_ilTree,LVSIL_SMALL);

	m_cContents.GetClientRect(&rect);


	m_cContents.InsertColumn(0,"Item",LVCFMT_LEFT,rect.Width()/2);
	m_cContents.InsertColumn(1,"Días para emisión",LVCFMT_LEFT,rect.Width()/2);

	strTemp.LoadString(IDS_SPOTS);

	HTREEITEM	hJingleRoot,
				hJingleType,
				hJingle,
				hTimeRoot,
				hTime,
				hRMRoot,
				hRMType,
				hRM,
				hSpot = m_cLibrary.InsertItem(strTemp,1,1);

	typeTreeItem *lpItem=new typeTreeItem;
	lpItem->lID=0;
	lpItem->wType=TYPE_SPOT;
	m_cLibrary.SetItemData(hSpot,(DWORD)lpItem);

	hJingleRoot=m_cLibrary.InsertItem("Jingles",4,4);
	m_cLibrary.SetItemData(hJingleRoot,0);

	CRSViewJinglesList	rs( g_strMainConnect );
	
	rs.m_strSort="Type, Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Type )
		{
			strPrev = rs.m_Type;
			rs.m_Type.TrimRight();

			hJingleType = m_cLibrary.InsertItem(rs.m_Type,14,14,hJingleRoot);
			m_cLibrary.SetItemData(hJingleType,0);
			m_cLibrary.SetItemState(hJingleType,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_JINGLE;

		hJingle = m_cLibrary.InsertItem(rs.m_Name,4,4,hJingleType);
		m_cLibrary.SetItemData(hJingle,(DWORD)lpItem);

		rs.MoveNext();
	}
	rs.Close();

	CRSTime	rsTime( g_strMainConnect );
	rsTime.m_strSort="Name";
	rsTime.Open();

	strTemp.LoadString(IDS_TIMESIGNAL);
	hTimeRoot = m_cLibrary.InsertItem(strTemp,2,2);

	while( !rsTime.IsEOF() )
	{
		lpItem = new typeTreeItem;
		lpItem->lID=rsTime.m_ID;
		lpItem->wType=TYPE_TIMESIGNAL;
		rsTime.m_Name.TrimRight();

		hTime = m_cLibrary.InsertItem(rsTime.m_Name,3,3,hTimeRoot);
		m_cLibrary.SetItemData(hTime,(DWORD)lpItem);

		rsTime.MoveNext();
	}
	rsTime.Close();

	CRSViewRms rsRms( g_strMainConnect );
	rsRms.m_strSort = "Type, Name";
	rsRms.m_strFilter = "Activ = '1'";
	rsRms.Open();

	strTemp = "RMs";
	hRMRoot = m_cLibrary.InsertItem(strTemp,9,9);

	while( !rsRms.IsEOF() )
	{
		if( strPrev!=rsRms.m_Type )
		{
			strPrev = rsRms.m_Type;
			rsRms.m_Type.TrimRight();

			hRMType = m_cLibrary.InsertItem(rsRms.m_Type,8,8,hRMRoot);
			m_cLibrary.SetItemData(hRMType,0);
			m_cLibrary.SetItemState(hRMType,TVIS_BOLD,TVIS_BOLD);
		}
		rsRms.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rsRms.m_ID;
		lpItem->wType=TYPE_RM;

		hRM = m_cLibrary.InsertItem(rsRms.m_Name,9,9,hRMType);
		m_cLibrary.SetItemData(hRM,(DWORD)lpItem);

		rsRms.MoveNext();
	}

	if( m_ID!=0 )
	{
		SendDlgItemMessage(IDC_SPONSOR,BM_SETCHECK,m_Sponsor);
		SendDlgItemMessage(IDC_NORMAL,BM_SETCHECK,!m_Sponsor);
		m_Normal = !m_Sponsor;

		CRSBlocksComposition	rsBlockComp(m_strConnect);
		CRSViewJinglesSmallList	rsJingles(g_strMainConnect);
		CRSTime					rsTime(g_strMainConnect);

		CString		strDate,
					strBlock,
					strSpot,
					strTimeSignal,
					strTemp;
		int			iPos=0;
		typeBlockItem *lpBlockItem;
		LVITEM		lvItem;

		strBlock.LoadString(IDS_BLOCK);
		strSpot.LoadString(IDS_SPOTS);
		strTimeSignal.LoadString(IDS_TIMESIGNAL);

		rsBlockComp.m_strFilter.Format("ID = %d",m_ID);
		rsBlockComp.m_strSort="Position";
		rsBlockComp.Open();
	
		while( !rsBlockComp.IsEOF() )
		{
			switch( rsBlockComp.m_ItemType )
			{
			case TYPE_JINGLE:
				rsJingles.m_strFilter.Format("ID = %d",rsBlockComp.m_ItemID);
				if( rsJingles.IsOpen() )
					rsJingles.Requery();
				else
					rsJingles.Open();

				if( rsJingles.GetRecordCount() )
				{
					rsJingles.m_Jingle.TrimRight();

					lpBlockItem = new typeBlockItem;
					lpBlockItem->Type = TYPE_JINGLE;
					lpBlockItem->ID = rsJingles.m_ID;
					lpBlockItem->EndingDate = rsBlockComp.m_EndingDate;
					lpBlockItem->StartingDate = rsBlockComp.m_StartingDate;
					lpBlockItem->Days[0] = rsBlockComp.m_Sun;
					lpBlockItem->Days[1] = rsBlockComp.m_Mon;
					lpBlockItem->Days[2] = rsBlockComp.m_Tue;
					lpBlockItem->Days[3] = rsBlockComp.m_Wed;
					lpBlockItem->Days[4] = rsBlockComp.m_Thu;
					lpBlockItem->Days[5] = rsBlockComp.m_Fri;
					lpBlockItem->Days[6] = rsBlockComp.m_Sat;

					strDate.Format(IDS_FORMAT_FROMTO,lpBlockItem->StartingDate.GetYear(),lpBlockItem->StartingDate.GetMonth(),lpBlockItem->StartingDate.GetDay(),
								lpBlockItem->EndingDate.GetYear(),lpBlockItem->EndingDate.GetMonth(),lpBlockItem->EndingDate.GetDay() );
			
					if( lpBlockItem->Days[0] )
					{
						strTemp.LoadString(IDS_SUN);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[1] )
					{
						strTemp.LoadString(IDS_MON);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[2] )
					{
						strTemp.LoadString(IDS_TUE);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[3] )
					{
						strTemp.LoadString(IDS_WED);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[4] )
					{
						strTemp.LoadString(IDS_THU);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[5] )
					{
						strTemp.LoadString(IDS_FRI);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[6] )
					{
						strTemp.LoadString(IDS_SAT);
						strDate+=(", "+strTemp);
					}

					lvItem.mask=LVIF_IMAGE|LVIF_INDENT|LVIF_PARAM;
					lvItem.iItem=iPos;
					lvItem.iSubItem=0;
					lvItem.iImage=4;
					lvItem.iIndent=0;
					lvItem.lParam=(DWORD)lpBlockItem;
		
					m_cContents.InsertItem(iPos,rsJingles.m_Jingle,4);
					m_cContents.SetItem(&lvItem);
					m_cContents.SetItemText(iPos,1,strDate);
					iPos++;
				}
				break;
			case TYPE_TIMESIGNAL:
				rsTime.m_strFilter.Format("ID = %d",rsBlockComp.m_ItemID);
				if( rsTime.IsOpen() )
					rsTime.Requery();
				else
					rsTime.Open();

				if( rsTime.GetRecordCount() )
				{
					rsTime.m_Name.TrimRight();

					lpBlockItem = new typeBlockItem;
					lpBlockItem->Type = TYPE_TIMESIGNAL;
					lpBlockItem->ID = rsTime.m_ID;
					lpBlockItem->EndingDate = rsBlockComp.m_EndingDate;
					lpBlockItem->StartingDate = rsBlockComp.m_StartingDate;
					lpBlockItem->Days[0] = rsBlockComp.m_Sun;
					lpBlockItem->Days[1] = rsBlockComp.m_Mon;
					lpBlockItem->Days[2] = rsBlockComp.m_Tue;
					lpBlockItem->Days[3] = rsBlockComp.m_Wed;
					lpBlockItem->Days[4] = rsBlockComp.m_Thu;
					lpBlockItem->Days[5] = rsBlockComp.m_Fri;
					lpBlockItem->Days[6] = rsBlockComp.m_Sat;

					strDate.Format(IDS_FORMAT_FROMTO,lpBlockItem->StartingDate.GetYear(),lpBlockItem->StartingDate.GetMonth(),lpBlockItem->StartingDate.GetDay(),
								lpBlockItem->EndingDate.GetYear(),lpBlockItem->EndingDate.GetMonth(),lpBlockItem->EndingDate.GetDay() );
			
					if( lpBlockItem->Days[0] )
					{
						strTemp.LoadString(IDS_SUN);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[1] )
					{
						strTemp.LoadString(IDS_MON);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[2] )
					{
						strTemp.LoadString(IDS_TUE);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[3] )
					{
						strTemp.LoadString(IDS_WED);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[4] )
					{
						strTemp.LoadString(IDS_THU);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[5] )
					{
						strTemp.LoadString(IDS_FRI);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[6] )
					{
						strTemp.LoadString(IDS_SAT);
						strDate+=(", "+strTemp);
					}

					lvItem.mask=LVIF_IMAGE|LVIF_INDENT|LVIF_PARAM;
					lvItem.iItem=iPos;
					lvItem.iSubItem=0;
					lvItem.iImage=3;
					lvItem.iIndent=0;
					lvItem.lParam=(DWORD)lpBlockItem;
		
					m_cContents.InsertItem(iPos,rsTime.m_Name,3);
					m_cContents.SetItem(&lvItem);
					m_cContents.SetItemText(iPos,1,strDate);
					iPos++;
				}
				break;
			case TYPE_RM:
				rsRms.m_strFilter.Format("ID = %d",rsBlockComp.m_ItemID);
				if( rsRms.IsOpen() )
					rsRms.Requery();
				else
					rsRms.Open();

				if( rsRms.GetRecordCount() )
				{
					rsRms.m_Name.TrimRight();

					lpBlockItem = new typeBlockItem;
					lpBlockItem->Type = TYPE_RM;
					lpBlockItem->ID = rsRms.m_ID;
					lpBlockItem->EndingDate = rsBlockComp.m_EndingDate;
					lpBlockItem->StartingDate = rsBlockComp.m_StartingDate;
					lpBlockItem->Days[0] = rsBlockComp.m_Sun;
					lpBlockItem->Days[1] = rsBlockComp.m_Mon;
					lpBlockItem->Days[2] = rsBlockComp.m_Tue;
					lpBlockItem->Days[3] = rsBlockComp.m_Wed;
					lpBlockItem->Days[4] = rsBlockComp.m_Thu;
					lpBlockItem->Days[5] = rsBlockComp.m_Fri;
					lpBlockItem->Days[6] = rsBlockComp.m_Sat;

					strDate.Format(IDS_FORMAT_FROMTO,lpBlockItem->StartingDate.GetYear(),lpBlockItem->StartingDate.GetMonth(),lpBlockItem->StartingDate.GetDay(),
								lpBlockItem->EndingDate.GetYear(),lpBlockItem->EndingDate.GetMonth(),lpBlockItem->EndingDate.GetDay() );
			
					if( lpBlockItem->Days[0] )
					{
						strTemp.LoadString(IDS_SUN);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[1] )
					{
						strTemp.LoadString(IDS_MON);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[2] )
					{
						strTemp.LoadString(IDS_TUE);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[3] )
					{
						strTemp.LoadString(IDS_WED);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[4] )
					{
						strTemp.LoadString(IDS_THU);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[5] )
					{
						strTemp.LoadString(IDS_FRI);
						strDate+=(", "+strTemp);
					}

					if( lpBlockItem->Days[6] )
					{
						strTemp.LoadString(IDS_SAT);
						strDate+=(", "+strTemp);
					}

					lvItem.mask=LVIF_IMAGE|LVIF_INDENT|LVIF_PARAM;
					lvItem.iItem=iPos;
					lvItem.iSubItem=0;
					lvItem.iImage=3;
					lvItem.iIndent=0;
					lvItem.lParam=(DWORD)lpBlockItem;
		
					m_cContents.InsertItem(iPos,rsRms.m_Name,3);
					m_cContents.SetItem(&lvItem);
					m_cContents.SetItemText(iPos,1,strDate);
					iPos++;
				}
				break;
			case TYPE_SPOT:
				lpBlockItem = new typeBlockItem;
				lpBlockItem->Type = TYPE_SPOT;
				lpBlockItem->ID = 0;

				lvItem.mask=LVIF_IMAGE|LVIF_INDENT|LVIF_PARAM;
				lvItem.iItem=iPos;
				lvItem.iSubItem=0;
				lvItem.iImage=1;
				lvItem.iIndent=1;
				lvItem.lParam=(DWORD)lpBlockItem;
		
				m_cContents.InsertItem(iPos,strSpot,4);
				m_cContents.SetItem(&lvItem);
				iPos++;
				break;
			case TYPE_BLOCK:
				lpBlockItem = new typeBlockItem;
				lpBlockItem->Type = TYPE_BLOCK;
				lpBlockItem->ID = 0;

				lvItem.mask=LVIF_IMAGE|LVIF_INDENT|LVIF_PARAM;
				lvItem.iItem=iPos;
				lvItem.iSubItem=0;
				lvItem.iImage=1;
				lvItem.iIndent=1;
				lvItem.lParam=(DWORD)lpBlockItem;
		
				m_cContents.InsertItem(iPos,strBlock,4);
				m_cContents.SetItem(&lvItem);
				iPos++;
				break;
			break;
			}
			rsBlockComp.MoveNext();
		}

	}

	if( m_cContents.GetItemCount()==0 )
	{
		typeBlockItem *lpItem = new typeBlockItem;
		lpItem->Type = TYPE_BLOCK;
		lpItem->ID = 150;

		LVITEM	lvItem;
		lvItem.mask=LVIF_IMAGE|LVIF_INDENT|LVIF_PARAM;
		lvItem.iItem=0;
		lvItem.iSubItem=0;
		lvItem.iImage=0;
		lvItem.iIndent=1;
		lvItem.lParam=(DWORD)lpItem;
		
		m_cContents.InsertItem(0,"Bloco de publicidade",11);
		m_cContents.SetItem(&lvItem);
	}
	return TRUE;  
}
