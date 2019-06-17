// ComercialWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "ComercialWnd.h"
#include "ExternalObjects.h"
#include "OnAirUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComercialWnd

#define ID_SELECTION	1001

CComercialWnd::CComercialWnd()
{
}

CComercialWnd::~CComercialWnd()
{
}


BEGIN_MESSAGE_MAP(CComercialWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CComercialWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	ON_CBN_SELCHANGE( ID_SELECTION,OnSelChange )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComercialWnd message handlers

void CComercialWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

int CComercialWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect	rect;
	GetClientRect(&rect);

	m_ctrlSelection = new CComboBoxEx();
	m_ctrlSelection->Create(CBS_DROPDOWNLIST|WS_VISIBLE,CRect(rect.left+20,rect.top+2,rect.right-1,rect.top+402),this,ID_SELECTION);
	m_ctrlSelection->SetFont(g_cfont24);
	m_ctrlSelection->SetImageList(g_ilContainer);

	CString str;
	str.LoadString(IDS_TRAFFIC_SPONSORS);

	COMBOBOXEXITEM	cbItem;
	cbItem.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT|CBEIF_LPARAM|CBEIF_TEXT;
	cbItem.iItem=0;
	cbItem.pszText=str.GetBuffer(0);
	cbItem.cchTextMax=20;
	cbItem.iImage=4;
	cbItem.iSelectedImage=4;
	cbItem.iIndent=0;
	cbItem.lParam=CONTAINER_TRAFFIC_SPONSORS;
	m_ctrlSelection->InsertItem(&cbItem);
	
	str.LoadString(IDS_TRAFFIC_BLOCKS);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=1;
	cbItem.iImage=9;
	cbItem.iSelectedImage=9;
	cbItem.lParam=CONTAINER_TRAFFIC_SCREENS;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_TRAFFIC_BUMPED);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=2;
	cbItem.iImage=14;
	cbItem.iSelectedImage=14;
	cbItem.lParam=CONTAINER_TRAFFIC_DELAYED;
	m_ctrlSelection->InsertItem(&cbItem);
	m_ctrlSelection->SetCurSel(0);

	//////////////////////////////////////////////////////////////////////////////
	//	Child window Creation

	// Get the window rect
	GetWindowRect(&rect);
	rect.DeflateRect(0,40,0,0);

	// Sponsors window
	m_wndSponsors = new CSponsorsWnd();
	m_wndSponsors->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this,0);

	// Blocks window
	m_wndBlocks = new CBlocksWnd();
	m_wndBlocks->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this,0);

	// Bumped Windows
	m_wndBumped = new CTrafficBumpedWnd();
	m_wndBumped->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this,0);

	// Make sure the sponsor window is on top
	m_wndSponsors->BringWindowToTop();

	return 0;
}

void CComercialWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CComercialWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CComercialWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CComercialWnd::OnSelChange()
{
	long int nSel=m_ctrlSelection->GetCurSel();

	if( nSel==CB_ERR )
		return;

	LPARAM lID= m_ctrlSelection->GetItemData(nSel);

	switch( lID )
	{
	case CONTAINER_TRAFFIC_SPONSORS:
		m_wndSponsors->BringWindowToTop();
		break;
	case CONTAINER_TRAFFIC_SCREENS:
		m_wndBlocks->BringWindowToTop();
		break;
	case CONTAINER_TRAFFIC_DELAYED:
		m_wndBumped->BringWindowToTop();
		break;
	}
}
