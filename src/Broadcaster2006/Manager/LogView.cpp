// LogView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "LogView.h"
#include "..\traffic\RadioStation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString	g_strBaseURL;
/////////////////////////////////////////////////////////////////////////////
// CLogView

IMPLEMENT_DYNCREATE(CLogView, CHtmlView)

CLogView::CLogView()
{
	//{{AFX_DATA_INIT(CLogView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLogView::~CLogView()
{
}

void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogView, CHtmlView)
	//{{AFX_MSG_MAP(CLogView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogView diagnostics

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CLogView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogView message handlers

void CLogView::OnInitialUpdate() 
{
	CRadioStation dl;
	dl.DoModal();
	
	CString		str;
	str.LoadString(IDS_ONAIRLOG);
	GetDocument()->SetTitle("OnAir Log");

	Navigate2(g_strBaseURL+"/logframe.asp?DB="+dl.m_strDB,NULL,NULL);
}
