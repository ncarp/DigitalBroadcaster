// HtmlInfo.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\common\include\HtmlInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlInfo

IMPLEMENT_DYNCREATE(CHtmlInfo, CFrameWnd)

CHtmlInfo::CHtmlInfo()
{
}

CHtmlInfo::~CHtmlInfo()
{
}


BEGIN_MESSAGE_MAP(CHtmlInfo, CFrameWnd)
	//{{AFX_MSG_MAP(CHtmlInfo)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlInfo message handlers

int CHtmlInfo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);

	m_pView = new CDRMHtml();
	m_pView->Create(NULL,NULL,WS_VISIBLE,rect,this,21);

	m_DropTarget.Register(this);
	return 0;

}

void CHtmlInfo::OnClose() 
{
	GetWindowPlacement(&m_Placement);
	MoveWindow(-100,0,0,0);
	m_bHide=TRUE;
}

void CHtmlInfo::RestoreWindow()
{
	if( m_bHide )
	{
		SetWindowPlacement(&m_Placement);
//		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	}
	m_bHide=FALSE;
}

void CHtmlInfo::SetView( CString str )
{
	m_pView->Navigate2(str);
	RestoreWindow();
	BringWindowToTop();
}

void CHtmlInfo::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	m_pView->MoveWindow(0,0,cx,cy);	
}
