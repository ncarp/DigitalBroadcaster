// ProducerWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "ProducerWnd.h"

#include "ExternalObjects.h"
#include "OnAirUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProducerWnd

#define ID_SELECTION	1001

IMPLEMENT_DYNCREATE(CProducerWnd, CFrameWnd)

CProducerWnd::CProducerWnd()
{
}

CProducerWnd::~CProducerWnd()
{
}


BEGIN_MESSAGE_MAP(CProducerWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CProducerWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	ON_CBN_SELCHANGE( ID_SELECTION,OnSelChange )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProducerWnd message handlers

int CProducerWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	rect;
	GetClientRect( &rect );
	CString	str;

	m_ctrlSelection = new CComboBoxEx();
	m_ctrlSelection->Create(CBS_DROPDOWNLIST|WS_VISIBLE,CRect(rect.left+20,rect.top+2,rect.right-1,rect.top+402),this,ID_SELECTION);
	m_ctrlSelection->SetFont(g_cfont24);
	m_ctrlSelection->SetImageList(g_ilContainer);

	str.LoadString(IDS_PRODUCER_SOUNDRECORDER);
	COMBOBOXEXITEM	cbItem;
	cbItem.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT|CBEIF_LPARAM|CBEIF_TEXT;
	cbItem.iItem=0;
	cbItem.pszText=str.GetBuffer(0);
	cbItem.cchTextMax=20;
	cbItem.iImage=3;
	cbItem.iSelectedImage=3;
	cbItem.iIndent=0;
	cbItem.lParam=CONTAINER_PRODUCER_RECORDING;
	m_ctrlSelection->InsertItem(&cbItem);
	
	str.LoadString(IDS_PRODUCER_PROGRAMMING);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=1;
	cbItem.iImage=8;
	cbItem.iSelectedImage=8;
	cbItem.lParam=CONTAINER_PRODUCER_SCHEDULING;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_PRODUCER_MUSICEDITING);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=2;
	cbItem.iImage=0;
	cbItem.iSelectedImage=0;
	cbItem.lParam=CONTAINER_PRODUCER_MUSICEDITING;
	m_ctrlSelection->InsertItem(&cbItem);

	m_ctrlSelection->SetCurSel(0);

	GetWindowRect(&rect);
	rect.DeflateRect(0,40,0,0);
	
	m_wndMusic = new CProducerMusicMain();
	m_wndMusic->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	m_wndScheduler = new CProducerScheduler();
	m_wndScheduler->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	m_wndSoundRecorder = new CSoundRecorderSelector();
	m_wndSoundRecorder->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	m_wndSoundRecorder->BringWindowToTop();

	return 0;
}

void CProducerWnd::OnPaint() 
{
	CPaintDC dc(this); 
	
	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE))); 
}

void CProducerWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CProducerWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CProducerWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// Do nothing
}

void CProducerWnd::OnSelChange()
{
	long int Pos = m_ctrlSelection->GetCurSel();

	if( Pos==CB_ERR )
		return;

	long int lData = m_ctrlSelection->GetItemData(Pos);

	switch( lData )
	{
	case CONTAINER_PRODUCER_RECORDING:
		m_wndSoundRecorder->BringWindowToTop();
		break;
	case CONTAINER_PRODUCER_SCHEDULING:
		m_wndScheduler->BringWindowToTop();
		break;
	case CONTAINER_PRODUCER_MUSICEDITING:
		m_wndMusic->BringWindowToTop();
		break;
	}

}
