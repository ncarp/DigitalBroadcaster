// MusicInfo.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "MusicInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusicInfo

IMPLEMENT_DYNCREATE(CMusicInfo, CFrameWnd)

CMusicInfo::CMusicInfo()
{
}

CMusicInfo::~CMusicInfo()
{
}


BEGIN_MESSAGE_MAP(CMusicInfo, CFrameWnd)
	//{{AFX_MSG_MAP(CMusicInfo)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicInfo message handlers

void CMusicInfo::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CFrameWnd::OnSysCommand(nID,lParam);
}

void CMusicInfo::OnClose() 
{
	GetWindowPlacement(&m_Placement);
	MoveWindow(0,0,0,0);
	m_bHide=TRUE;
}

int CMusicInfo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);

	m_pView = new COnAirHtml();
	m_pView->Create(NULL,NULL,WS_VISIBLE,rect,this,21);

	return 0;
}

void CMusicInfo::RestoreWindow()
{
	if( m_bHide )
	{
		SetWindowPlacement(&m_Placement);
		SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	}
	m_bHide=FALSE;
}

void CMusicInfo::SetView( CString str )
{
	m_pView->Navigate2(str);
	RestoreWindow();
	BringWindowToTop();
}