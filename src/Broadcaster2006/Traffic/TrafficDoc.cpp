// TrafficDoc.cpp : implementation of the CTrafficDoc class
//

#include "stdafx.h"
#include "Traffic.h"

#include "TrafficDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrafficDoc

IMPLEMENT_DYNCREATE(CTrafficDoc, CDocument)

BEGIN_MESSAGE_MAP(CTrafficDoc, CDocument)
	//{{AFX_MSG_MAP(CTrafficDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficDoc construction/destruction

CTrafficDoc::CTrafficDoc()
{
	// TODO: add one-time construction code here

}

CTrafficDoc::~CTrafficDoc()
{
}

BOOL CTrafficDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTrafficDoc serialization

void CTrafficDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTrafficDoc diagnostics

#ifdef _DEBUG
void CTrafficDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTrafficDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTrafficDoc commands
