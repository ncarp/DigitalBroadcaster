// SchedulerView.cpp : implementation of the CSchedulerView class
//

#include "stdafx.h"
#include "Scheduler.h"

#include "SchedulerDoc.h"
#include "SchedulerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchedulerView

IMPLEMENT_DYNCREATE(CSchedulerView, CListView)

BEGIN_MESSAGE_MAP(CSchedulerView, CListView)
	//{{AFX_MSG_MAP(CSchedulerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchedulerView construction/destruction

CSchedulerView::CSchedulerView()
{
	// TODO: add construction code here

}

CSchedulerView::~CSchedulerView()
{
}

BOOL CSchedulerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSchedulerView drawing

void CSchedulerView::OnDraw(CDC* pDC)
{
	CSchedulerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CSchedulerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CSchedulerView diagnostics

#ifdef _DEBUG
void CSchedulerView::AssertValid() const
{
	CListView::AssertValid();
}

void CSchedulerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CSchedulerDoc* CSchedulerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSchedulerDoc)));
	return (CSchedulerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSchedulerView message handlers
void CSchedulerView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
