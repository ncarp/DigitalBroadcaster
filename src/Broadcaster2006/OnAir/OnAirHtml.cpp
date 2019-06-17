// COnAirHtml.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "OnAirHtml.h"
#include "OnAirDefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnAirHtml

IMPLEMENT_DYNCREATE(COnAirHtml, CHtmlView)

COnAirHtml::COnAirHtml()
{
	//{{AFX_DATA_INIT(COnAirHtml)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COnAirHtml::~COnAirHtml()
{
}

void COnAirHtml::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COnAirHtml)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COnAirHtml, CHtmlView)
	//{{AFX_MSG_MAP(COnAirHtml)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirHtml diagnostics

#ifdef _DEBUG
void COnAirHtml::AssertValid() const
{
	CHtmlView::AssertValid();
}

void COnAirHtml::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COnAirHtml message handlers

void COnAirHtml::OnNavigateComplete2(LPCTSTR strURL) 
{
	GetParent()->SendMessage(UM_NAVIGATECOMPLETE);
	
	CHtmlView::OnNavigateComplete2(strURL);
}
