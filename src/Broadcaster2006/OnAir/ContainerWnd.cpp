// ContainerWnd.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAir.h"
#include "ContainerWnd.h"
#include "MusicWnd.h"
#include "OnAirUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	ID_SELECTION	1001

/////////////////////////////////////////////////////////////////////////////
// CContainerWnd

CContainerWnd::CContainerWnd()
{
}

CContainerWnd::~CContainerWnd()
{
}

BEGIN_MESSAGE_MAP(CContainerWnd, CStatic)
	//{{AFX_MSG_MAP(CContainerWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE( ID_SELECTION,OnSelChange )
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContainerWnd message handlers

int CContainerWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect	rect;
	GetClientRect( &rect );
	CString	str;

	m_ctrlSelection = new CComboBoxEx();
	m_ctrlSelection->Create(CBS_DROPDOWNLIST|WS_VISIBLE,CRect(rect.left+1,rect.top+2,rect.right-1,rect.top+402),this,ID_SELECTION);
	m_ctrlSelection->SetFont(g_cfont24);
	m_ctrlSelection->SetImageList(g_ilContainer);

	str.LoadString(IDS_MUSIC);

	COMBOBOXEXITEM	cbItem;
	cbItem.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT|CBEIF_LPARAM|CBEIF_TEXT;
	cbItem.iItem=0;
	cbItem.pszText=str.GetBuffer(0);
	cbItem.cchTextMax=20;
	cbItem.iImage=0;
	cbItem.iSelectedImage=0;
	cbItem.iIndent=0;
	cbItem.lParam=CONTAINER_MUSIC;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_JINGLES);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=1;
	cbItem.iImage=1;
	cbItem.iSelectedImage=1;
	cbItem.lParam=CONTAINER_JINGLES;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_CARTWALL);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=2;
	cbItem.iImage=5;
	cbItem.iSelectedImage=5;
	cbItem.lParam=CONTAINER_CARTWALL;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_PRODUCER);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=3;
	cbItem.iImage=3;
	cbItem.iSelectedImage=3;
	cbItem.lParam=CONTAINER_PRODUCER;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_TRAFFIC);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=3;
	cbItem.iImage=4;
	cbItem.iSelectedImage=4;
	cbItem.lParam=CONTAINER_TRAFFIC;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_VOICEINSERT);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=4;
	cbItem.iImage=10;
	cbItem.iSelectedImage=10;
	cbItem.lParam=CONTAINER_VOICEINSERT;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_LINEUP);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=6;
	cbItem.iImage=2;
	cbItem.iSelectedImage=2;
	cbItem.lParam=CONTAINER_LINEUP;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_RMS);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=4;
	cbItem.iImage=13;
	cbItem.iSelectedImage=13;
	cbItem.lParam=CONTAINER_RMS;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_INTERNET);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=7;
	cbItem.iImage=12;
	cbItem.iSelectedImage=12;
	cbItem.lParam=CONTAINER_INTERNET;
	m_ctrlSelection->InsertItem(&cbItem);

	str.LoadString(IDS_AIRED);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iItem=8;
	cbItem.iImage=11;
	cbItem.iSelectedImage=11;
	cbItem.lParam=CONTAINER_AIRED;
	m_ctrlSelection->InsertItem(&cbItem);

	GetWindowRect(&rect);
	rect.DeflateRect(0,38,0,0);

	m_wndMusic=new CMusicContainerWnd();
	m_wndMusic->Create(NULL,NULL,WS_POPUP|WS_VISIBLE,rect,this);

	m_wndJingles = new CJinglesWnd();
	m_wndJingles->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	m_wndProducer = new CProducerWnd();
	m_wndProducer->Create(NULL,NULL,WS_VISIBLE|WS_POPUP,rect,this);

	m_wndComercial = new CComercialWnd();
	m_wndComercial->Create(NULL,NULL,WS_POPUP|WS_VISIBLE,rect,this);

	m_wndVoiceInsert = new CVoiceInsertWnd();
	m_wndVoiceInsert->Create(NULL,NULL,WS_POPUP|WS_VISIBLE,rect,this);

	m_wndInternet = new CInternetWnd();
	m_wndInternet->Create(NULL,NULL,WS_POPUP|WS_VISIBLE,rect,this);
	
	m_wndRMs = new CRMsWnd();
	m_wndRMs->Create(NULL,NULL,WS_POPUP|WS_VISIBLE,rect,this);

	return 0;
}

void CContainerWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

void CContainerWnd::OnSelChange() 
{
	int iCurSel=m_ctrlSelection->GetCurSel();

	if( iCurSel==CB_ERR )
		return;

	DWORD	lParam=m_ctrlSelection->GetItemData(iCurSel);
	CRect	crect;

	GetWindowRect(&crect);
	crect.DeflateRect(0,38,0,0);

	switch( lParam )
	{
	case CONTAINER_MUSIC:
		m_wndMusic->BringWindowToTop();
		break;
	case CONTAINER_JINGLES:
		m_wndJingles->BringWindowToTop();
		break;
	case CONTAINER_LINEUP:
		g_wndLineUp->MoveWindow(crect);
		g_wndLineUp->BringWindowToTop();
		break;
	case CONTAINER_PRODUCER:
		m_wndProducer->BringWindowToTop();
		break;
	case CONTAINER_TRAFFIC:
		m_wndComercial->BringWindowToTop();
		break;
	case CONTAINER_VOICEINSERT:
		m_wndVoiceInsert->BringWindowToTop();
		break;
	case CONTAINER_CARTWALL:
		g_wndCartwall->MoveWindow(crect);
		g_wndCartwall->BringWindowToTop();
		break;
	case CONTAINER_AIRED:
		g_wndAired->MoveWindow(crect);
		g_wndAired->BringWindowToTop();
		break;
	case CONTAINER_INTERNET:
		m_wndInternet->BringWindowToTop();
		break;
	case CONTAINER_RMS:
		m_wndRMs->BringWindowToTop();
		break;
	}	
}


void CContainerWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CContainerWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar)	)
		CStatic::OnSysKeyUp(nChar, nRepCnt, nFlags);
}
