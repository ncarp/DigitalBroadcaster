// DRMHtml.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\common\include\DRMHtml.h"
#include "..\..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRMHtml

IMPLEMENT_DYNCREATE(CDRMHtml, CHtmlView)

CDRMHtml::CDRMHtml()
{
	//{{AFX_DATA_INIT(CDRMHtml)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDRMHtml::~CDRMHtml()
{
}

void CDRMHtml::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDRMHtml)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDRMHtml, CHtmlView)
	//{{AFX_MSG_MAP(CDRMHtml)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRMHtml diagnostics

#ifdef _DEBUG
void CDRMHtml::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CDRMHtml::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDRMHtml message handlers

void CDRMHtml::OnNavigateComplete2(LPCTSTR strURL) 
{
	CHtmlView::OnNavigateComplete2(strURL);

	GetParent()->SendMessage(UM_NAVIGATECOMPLETE);
}

int CDRMHtml::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHtmlView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_DropTarget.Register(this);
	
	return 0;
}
