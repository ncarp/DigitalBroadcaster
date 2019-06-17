// MusicContainerWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "MusicContainerWnd.h"
#include "OnAirUtils.h"
#include "ExternalObjects.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusicContainerWnd

#define ID_SELECTION		1001

IMPLEMENT_DYNCREATE(CMusicContainerWnd, CFrameWnd)

CMusicContainerWnd::CMusicContainerWnd()
{
}

CMusicContainerWnd::~CMusicContainerWnd()
{
}


BEGIN_MESSAGE_MAP(CMusicContainerWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CMusicContainerWnd)
	ON_WM_SYSCOMMAND()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE( ID_SELECTION,OnSelChange )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicContainerWnd message handlers

void CMusicContainerWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CMusicContainerWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CMusicContainerWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

int CMusicContainerWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	rect;
	GetClientRect(&rect);
	CString	str;

	str.LoadString(IDS_MUSIC_DISCOGRAPHY);
	m_ctrlSelection = new CComboBoxEx();
	m_ctrlSelection->Create(CBS_DROPDOWNLIST|WS_VISIBLE|CBS_OWNERDRAWFIXED,CRect(rect.left+20,rect.top+2,rect.right-1,rect.top+402),this,ID_SELECTION);
	m_ctrlSelection->SetFont(g_cfont24);
	m_ctrlSelection->SetImageList(g_ilContainer);

	COMBOBOXEXITEM	cbItem;
	cbItem.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT|CBEIF_LPARAM|CBEIF_TEXT;
	cbItem.iItem=0;
	cbItem.pszText=str.GetBuffer(0);
	cbItem.cchTextMax=20;
	cbItem.iImage=0;
	cbItem.iSelectedImage=0;
	cbItem.iIndent=0;
	cbItem.lParam=CONTAINER_MUSIC_DISCOGRAPHY;
	m_ctrlSelection->InsertItem(&cbItem);
	
	str.LoadString(IDS_MUSIC_PLAYLIST);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=1;
	cbItem.iImage=6;
	cbItem.iSelectedImage=6;
	cbItem.lParam=CONTAINER_MUSIC_PLAYLIST;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_MUSIC_CATEGORY);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=2;
	cbItem.iImage=6;
	cbItem.iSelectedImage=6;
	cbItem.lParam=CONTAINER_MUSIC_CATEGORY;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_MUSIC_SEARCH);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=3;
	cbItem.iImage=7;
	cbItem.iSelectedImage=7;
	cbItem.lParam=CONTAINER_MUSIC_SEARCH;
	m_ctrlSelection->InsertItem(&cbItem);
	
	m_ctrlSelection->SetCurSel(0);

	GetWindowRect(&rect);
	rect.DeflateRect(0,40,0,0);

	///////////////////////////////////////////////////////////////////////////
	//	Child windows creation

	//	Full discography
	m_wndMusicDiscography = new CMusicWnd();
	m_wndMusicDiscography->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this,0);

	//	Play List
	m_wndMusicPlayList = new CMusicPlayListWnd();
	m_wndMusicPlayList->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	// Categories
	m_wndMusicCategory = new CMusicCategoryWnd();
	m_wndMusicCategory->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	// Search
	m_wndMusicSearch = new CMusicSearchWnd();
	m_wndMusicSearch->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	m_wndMusicDiscography->BringWindowToTop();
	return 0;
}

void CMusicContainerWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

HBRUSH CMusicContainerWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CBrush(GetSysColor(COLOR_3DFACE));
	
	AfxMessageBox("Teste");

	return hbr;
}

void CMusicContainerWnd::OnSelChange()
{
	int iCurSel=m_ctrlSelection->GetCurSel();

	if( iCurSel==CB_ERR )
		return;

	DWORD	lParam=m_ctrlSelection->GetItemData(iCurSel);
	CRect	crect;

	switch( lParam )
	{
	case CONTAINER_MUSIC_DISCOGRAPHY:
		m_wndMusicDiscography->BringWindowToTop();
		break;
	case CONTAINER_MUSIC_PLAYLIST:
		m_wndMusicPlayList->BringWindowToTop();
		break;
	case CONTAINER_MUSIC_CATEGORY:
		m_wndMusicCategory->BringWindowToTop();
		break;
	case CONTAINER_MUSIC_SEARCH:
		m_wndMusicSearch->BringWindowToTop();
	}
}