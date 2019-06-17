// BroadcasterMusicView.cpp : implementation of the CBroadcasterMusicView class
//

#include "stdafx.h"
#include "BroadcasterMusic.h"

#include "BroadcasterMusicDoc.h"
#include "BroadcasterMusicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBroadcasterMusicView

IMPLEMENT_DYNCREATE(CBroadcasterMusicView, CView)

BEGIN_MESSAGE_MAP(CBroadcasterMusicView, CView)
END_MESSAGE_MAP()

// CBroadcasterMusicView construction/destruction

CBroadcasterMusicView::CBroadcasterMusicView()
{
	// TODO: add construction code here

}

CBroadcasterMusicView::~CBroadcasterMusicView()
{
}

BOOL CBroadcasterMusicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBroadcasterMusicView drawing

void CBroadcasterMusicView::OnDraw(CDC* /*pDC*/)
{
	CBroadcasterMusicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CBroadcasterMusicView diagnostics

#ifdef _DEBUG
void CBroadcasterMusicView::AssertValid() const
{
	CView::AssertValid();
}

void CBroadcasterMusicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBroadcasterMusicDoc* CBroadcasterMusicView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBroadcasterMusicDoc)));
	return (CBroadcasterMusicDoc*)m_pDocument;
}
#endif //_DEBUG


// CBroadcasterMusicView message handlers
