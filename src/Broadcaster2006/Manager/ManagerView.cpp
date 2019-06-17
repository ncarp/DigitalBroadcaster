// ManagerView.cpp : implementation of the CManagerView class
//

#include "stdafx.h"
#include "Manager.h"

#include "ManagerDoc.h"
#include "ManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManagerView

IMPLEMENT_DYNCREATE(CManagerView, CListView)

BEGIN_MESSAGE_MAP(CManagerView, CListView)
	//{{AFX_MSG_MAP(CManagerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagerView construction/destruction

CManagerView::CManagerView()
{
	// TODO: add construction code here

}

CManagerView::~CManagerView()
{
}

BOOL CManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CManagerView drawing

void CManagerView::OnDraw(CDC* pDC)
{
	CManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CManagerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CManagerView diagnostics

#ifdef _DEBUG
void CManagerView::AssertValid() const
{
	CListView::AssertValid();
}

void CManagerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CManagerDoc* CManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CManagerDoc)));
	return (CManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CManagerView message handlers
void CManagerView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
