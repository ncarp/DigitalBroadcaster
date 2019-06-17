// NewsRoomView.cpp : implementation of the CNewsRoomView class
//

#include "stdafx.h"
#include "NewsRoom.h"

#include "NewsRoomDoc.h"
#include "NewsRoomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomView

IMPLEMENT_DYNCREATE(CNewsRoomView, CListView)

BEGIN_MESSAGE_MAP(CNewsRoomView, CListView)
	//{{AFX_MSG_MAP(CNewsRoomView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomView construction/destruction

CNewsRoomView::CNewsRoomView()
{
	// TODO: add construction code here

}

CNewsRoomView::~CNewsRoomView()
{
}

BOOL CNewsRoomView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomView drawing

void CNewsRoomView::OnDraw(CDC* pDC)
{
	CNewsRoomDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CNewsRoomView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomView diagnostics

#ifdef _DEBUG
void CNewsRoomView::AssertValid() const
{
	CListView::AssertValid();
}

void CNewsRoomView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CNewsRoomDoc* CNewsRoomView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNewsRoomDoc)));
	return (CNewsRoomDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomView message handlers
void CNewsRoomView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
