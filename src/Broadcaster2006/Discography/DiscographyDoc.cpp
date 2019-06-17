// DiscographyDoc.cpp : implementation of the CDiscographyDoc class
//

#include "stdafx.h"
#include "Discography.h"

#include "DiscographyDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiscographyDoc

IMPLEMENT_DYNCREATE(CDiscographyDoc, CDocument)

BEGIN_MESSAGE_MAP(CDiscographyDoc, CDocument)
	//{{AFX_MSG_MAP(CDiscographyDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiscographyDoc construction/destruction

CDiscographyDoc::CDiscographyDoc()
{
	// TODO: add one-time construction code here

}

CDiscographyDoc::~CDiscographyDoc()
{
}

BOOL CDiscographyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDiscographyDoc serialization

void CDiscographyDoc::Serialize(CArchive& ar)
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
// CDiscographyDoc diagnostics

#ifdef _DEBUG
void CDiscographyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDiscographyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiscographyDoc commands
