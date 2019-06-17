// DiscographyView.cpp : implementation of the CDiscographyView class
//

#include "stdafx.h"
#include "Discography.h"

#include "DiscographyDoc.h"
#include "DiscographyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiscographyView

IMPLEMENT_DYNCREATE(CDiscographyView, CListView)

BEGIN_MESSAGE_MAP(CDiscographyView, CListView)
	//{{AFX_MSG_MAP(CDiscographyView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiscographyView construction/destruction

CDiscographyView::CDiscographyView()
{
	// TODO: add construction code here

}

CDiscographyView::~CDiscographyView()
{
}

BOOL CDiscographyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDiscographyView drawing

void CDiscographyView::OnDraw(CDC* pDC)
{
	CDiscographyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CDiscographyView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CDiscographyView diagnostics

#ifdef _DEBUG
void CDiscographyView::AssertValid() const
{
	CListView::AssertValid();
}

void CDiscographyView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDiscographyDoc* CDiscographyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiscographyDoc)));
	return (CDiscographyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiscographyView message handlers
void CDiscographyView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
