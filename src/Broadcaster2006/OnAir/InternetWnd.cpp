// InternetWnd.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "InternetWnd.h"
#include "OnAirDefines.h"
#include "ExternalObjects.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInternetWnd

IMPLEMENT_DYNCREATE(CInternetWnd, CFrameWnd)


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CInternetWnd::CInternetWnd()
{
}

CInternetWnd::~CInternetWnd()
{
}


BEGIN_MESSAGE_MAP(CInternetWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CInternetWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(IDOK, OnNewAddressEnter)
	ON_COMMAND(CM_BACK, OnBack)
	ON_COMMAND(CM_FOWARD, OnFoward )
	ON_COMMAND(CM_STOP, OnStop )
	ON_COMMAND(CM_REFRESH, OnRefresh )
	ON_COMMAND(CM_INFO,OnInfo)
	ON_COMMAND(CM_QUERYBLOCKS,OnHelp )
	ON_MESSAGE(UM_NAVIGATECOMPLETE, OnNavigateComplete )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInternetWnd message handlers

int CInternetWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_TOP);
	
	TBBUTTON	buttons[7];
	buttons[0].iBitmap=12;
	buttons[0].idCommand=CM_BACK;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=12;

	buttons[1].iBitmap=13;
	buttons[1].idCommand=CM_FOWARD;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=13;

	buttons[2].iBitmap=10;
	buttons[2].idCommand=CM_STOP;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=14;

	buttons[3].iBitmap=0;
	buttons[3].idCommand=CM_REFRESH;
	buttons[3].fsState=TBSTATE_ENABLED;
	buttons[3].fsStyle=TBSTYLE_BUTTON;
	buttons[3].dwData=0;
	buttons[3].iString=0;

	buttons[4].iBitmap=10;
	buttons[4].idCommand=0;
	buttons[4].fsState=TBSTATE_ENABLED;
	buttons[4].fsStyle=TBSTYLE_SEP;
	buttons[4].dwData=0;
	buttons[4].iString=14;

	buttons[5].iBitmap=3;
	buttons[5].idCommand=CM_INFO;
	buttons[5].fsState=TBSTATE_ENABLED;
	buttons[5].fsStyle=TBSTYLE_BUTTON;
	buttons[5].dwData=0;
	buttons[5].iString=15;

	buttons[6].iBitmap=17;
	buttons[6].idCommand=CM_QUERYBLOCKS;
	buttons[6].fsState=TBSTATE_ENABLED;
	buttons[6].fsStyle=TBSTYLE_BUTTON;
	buttons[6].dwData=0;
	buttons[6].iString=21;

	m_pToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	m_pToolBar->SetButtonSize(size);
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(7,buttons);
	m_pToolBar->AutoSize();

	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);

	m_pAdress = new CComboBoxEx();
	m_pAdress->Create(CBS_DROPDOWN | WS_CHILD, CRect(0, 0, 200, 120), this, AFX_IDW_TOOLBAR + 1);

	CString str;
	str.LoadString(IDS_ADRESS);
	m_pRebar->AddBar(m_pAdress,str, NULL, RBBS_FIXEDBMP | RBBS_BREAK);

	m_pStatus = new CStatusBar();
	m_pStatus->Create(this);
	m_pStatus->SetIndicators(indicators,sizeof(indicators)/sizeof(UINT));

	CRect rect;
	GetClientRect(&rect);
	
	rect.DeflateRect(1,92,1,18);
	m_pHtml = new COnAirHtml();
	m_pHtml->Create(NULL,NULL,WS_VISIBLE,rect,this,0);
	return 0;
}

void CInternetWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect( &rect );

	dc.FillRect(rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CInternetWnd::OnNewAddressEnter()
{
	CString str;

	m_pAdress->GetEditCtrl()->GetWindowText(str);
	m_pHtml->Navigate2(str, 0, NULL);

	COMBOBOXEXITEM item;

	item.mask = CBEIF_TEXT;
	item.iItem = -1;
	item.pszText = (LPTSTR)(LPCTSTR)str;
	m_pAdress->InsertItem(&item);
}

LRESULT CInternetWnd::OnNavigateComplete( WPARAM,LPARAM )
{
	CString str = m_pHtml->GetLocationName();
	m_pAdress->GetEditCtrl()->SetWindowText(str);

	return 0;
}

void CInternetWnd::OnInfo()
{
	CString str=g_strBaseURL+"/InfoMain.asp?DB="+g_strDB;
	m_pHtml->Navigate2(str);
}

void CInternetWnd::OnBack()
{
	m_pHtml->GoBack();
}

void CInternetWnd::OnFoward()
{
	m_pHtml->GoForward();
}

void CInternetWnd::OnStop()
{
	m_pHtml->Stop();
}

void CInternetWnd::OnRefresh()
{
	m_pHtml->Refresh();
}

void CInternetWnd::OnHelp()
{
	CString str=g_strBaseURL+"/manual/onair.pdf";
	m_pHtml->Navigate2(str);
}