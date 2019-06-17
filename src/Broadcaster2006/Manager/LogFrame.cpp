// LogFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "LogFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogFrame

IMPLEMENT_DYNCREATE(CLogFrame, CMDIChildWnd)

CLogFrame::CLogFrame()
{
}

CLogFrame::~CLogFrame()
{
}


BEGIN_MESSAGE_MAP(CLogFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CLogFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogFrame message handlers
