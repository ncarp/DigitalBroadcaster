// Teste.cpp : implementation file
//

#include "stdafx.h"
#include "Discography.h"
#include "Teste.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Teste

IMPLEMENT_DYNCREATE(Teste, CFormView)

Teste::Teste()
	: CFormView(Teste::IDD)
{
	//{{AFX_DATA_INIT(Teste)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Teste::~Teste()
{
}

void Teste::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Teste)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Teste, CFormView)
	//{{AFX_MSG_MAP(Teste)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Teste diagnostics

#ifdef _DEBUG
void Teste::AssertValid() const
{
	CFormView::AssertValid();
}

void Teste::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Teste message handlers
