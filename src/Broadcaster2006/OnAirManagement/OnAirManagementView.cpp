// OnAirManagementView.cpp : implementation of the COnAirManagementView class
//

#include "stdafx.h"
#include "OnAirManagement.h"

#include "OnAirManagementDoc.h"
#include "OnAirManagementView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementView

IMPLEMENT_DYNCREATE(COnAirManagementView, CListView)

BEGIN_MESSAGE_MAP(COnAirManagementView, CListView)
	//{{AFX_MSG_MAP(COnAirManagementView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementView construction/destruction

COnAirManagementView::COnAirManagementView()
{
	// TODO: add construction code here

}

COnAirManagementView::~COnAirManagementView()
{
}

BOOL COnAirManagementView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementView drawing

void COnAirManagementView::OnDraw(CDC* pDC)
{
	COnAirManagementDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void COnAirManagementView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementView printing

BOOL COnAirManagementView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COnAirManagementView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COnAirManagementView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementView diagnostics

#ifdef _DEBUG
void COnAirManagementView::AssertValid() const
{
	CListView::AssertValid();
}

void COnAirManagementView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

COnAirManagementDoc* COnAirManagementView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COnAirManagementDoc)));
	return (COnAirManagementDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementView message handlers
void COnAirManagementView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
