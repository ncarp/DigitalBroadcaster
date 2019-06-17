// NewsLineUp.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "NewsLineUp.h"
#include "..\onair\onairdefines.h"
#include "..\include\rsviewnewslist.h"
#include "..\include\RSViewNewsLineUpTitles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CImageList	*g_ilTree;
extern	CString		g_strMainConnect;

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUp dialog


CNewsLineUp::CNewsLineUp(CWnd* pParent /*=NULL*/)
	: CDialog(CNewsLineUp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewsLineUp)
	m_Name = _T("");
	//}}AFX_DATA_INIT
	m_ID=0;
}


void CNewsLineUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewsLineUp)
	DDX_Control(pDX, IDC_NEWS, m_cNews);
	DDX_Control(pDX, IDC_LINEUP, m_cLineUp);
	DDX_Text(pDX, IDC_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewsLineUp, CDialog)
	//{{AFX_MSG_MAP(CNewsLineUp)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_MOVEUP, OnMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnMovedown)
	ON_NOTIFY(NM_DBLCLK, IDC_NEWS, OnDblclkNews)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewsLineUp message handlers

void CNewsLineUp::OnOK() 
{
	UpdateData();

	m_Name.TrimRight();

	if( m_Name.GetLength()==0 )
		return;
	
	m_nNews = m_cLineUp.GetItemCount();
	for( int i=0; i<m_nNews; i++ )
		m_lNewsID[i]=m_cLineUp.GetItemData(i);

	CDialog::OnOK();
}

void CNewsLineUp::OnRemove() 
{
	int Pos=m_cLineUp.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;

	m_cLineUp.DeleteItem(Pos);
}

void CNewsLineUp::OnMoveup() 
{
	int Pos=m_cLineUp.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;
	
	int NewPos;

	CString strName=m_cLineUp.GetItemText(Pos,0);
	long	lID = m_cLineUp.GetItemData(Pos);

	if( Pos==0 )
		NewPos=m_cLineUp.GetItemCount()-1;
	else
		NewPos=Pos-1;

	m_cLineUp.DeleteItem(Pos);

	m_cLineUp.InsertItem(NewPos,strName,11);
	m_cLineUp.SetItemData(NewPos,lID);
	m_cLineUp.SetItemState(NewPos,LVIS_SELECTED,LVIS_SELECTED);
}

void CNewsLineUp::OnMovedown() 
{
	int Pos=m_cLineUp.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;
	
	int NewPos = Pos;

	CString strName=m_cLineUp.GetItemText(Pos,0);
	long	lID = m_cLineUp.GetItemData(Pos);


	if( Pos==m_cLineUp.GetItemCount()-1 )
		NewPos=0;
	else
		NewPos=Pos+1;

	m_cLineUp.DeleteItem(Pos);

	m_cLineUp.InsertItem(NewPos,strName,11);
	m_cLineUp.SetItemData(NewPos,lID);
	m_cLineUp.SetItemState(NewPos,LVIS_SELECTED,LVIS_SELECTED);
}

void CNewsLineUp::OnDblclkNews(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	HTREEITEM hItem=m_cNews.GetSelectedItem();
	if( hItem==NULL )
		return;
	
	typeTreeItem *lpItem = (typeTreeItem *)m_cNews.GetItemData(hItem);
	if( lpItem==NULL )
		return;

	if( lpItem->wType!=TYPE_TEXT )
		return;

	HTREEITEM hType = m_cNews.GetParentItem(hItem);
	
	CString strType = m_cNews.GetItemText(hType);
	CString strName = m_cNews.GetItemText(hItem);

	int Pos=m_cLineUp.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1 )
		Pos=m_cLineUp.GetItemCount();

	m_cLineUp.InsertItem(Pos,strType+" - "+strName,11);
	m_cLineUp.SetItemData(Pos,lpItem->lID);
}

BOOL CNewsLineUp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cNews.SetImageList(g_ilTree,TVSIL_NORMAL);
	m_cLineUp.SetImageList(g_ilTree,LVSIL_SMALL);

	CRSViewNewsList	rs( g_strMainConnect );
	CString		strPrev;
	HTREEITEM	hType,
				hNews;
	typeTreeItem *lpItem;

	rs.m_strSort = "Type, Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Type )
		{
			strPrev = rs.m_Type;
			rs.m_Type.TrimRight();

			hType = m_cNews.InsertItem(rs.m_Type,10,10);
			m_cNews.SetItemData(hType,0);
			m_cNews.SetItemState(hType,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Name.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_TEXT;

		hNews = m_cNews.InsertItem(rs.m_Name,11,11,hType);
		m_cNews.SetItemData(hNews,(DWORD)lpItem);

		rs.MoveNext();
	}

	hType=m_cNews.InsertItem("w",0,0);
	m_cNews.DeleteItem(hType);

	CString str;
	CRect	crect;
	int		Pos=0;
	m_cLineUp.GetWindowRect(&crect);
	str.LoadString(IDS_NEWSLINEUP);
	m_cLineUp.InsertColumn(0,str,LVCFMT_LEFT,crect.Width()-4);

	if( m_ID!= 0 )
	{
		CRSViewNewsLineUpTitles rs( m_strConnect );
		rs.m_strFilter.Format("LineUpID = %d",m_ID);
		rs.m_strSort="Position";
		rs.Open();
		
		while( !rs.IsEOF() )
		{
			rs.m_News.TrimRight();
			m_cLineUp.InsertItem(Pos,rs.m_News,11);
			m_cLineUp.SetItemData(Pos,rs.m_NewsID);

			Pos++;
			rs.MoveNext();
		}
	}
	return TRUE; 
}
