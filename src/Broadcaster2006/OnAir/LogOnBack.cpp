// LogOnBack.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "LogOnBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogOnBack

IMPLEMENT_DYNCREATE(CLogOnBack, CFrameWnd)

CLogOnBack::CLogOnBack()
{
}

CLogOnBack::~CLogOnBack()
{
}


BEGIN_MESSAGE_MAP(CLogOnBack, CFrameWnd)
	//{{AFX_MSG_MAP(CLogOnBack)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogOnBack message handlers

void CLogOnBack::OnSysCommand(UINT nID, LPARAM lParam) 
{
}
