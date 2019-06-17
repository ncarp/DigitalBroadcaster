// OnAirManagementDoc.cpp : implementation of the COnAirManagementDoc class
//

#include "stdafx.h"
#include "OnAirManagement.h"

#include "OnAirManagementDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementDoc

IMPLEMENT_DYNCREATE(COnAirManagementDoc, CDocument)

BEGIN_MESSAGE_MAP(COnAirManagementDoc, CDocument)
	//{{AFX_MSG_MAP(COnAirManagementDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementDoc construction/destruction

COnAirManagementDoc::COnAirManagementDoc()
{
	// TODO: add one-time construction code here

}

COnAirManagementDoc::~COnAirManagementDoc()
{
}

BOOL COnAirManagementDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COnAirManagementDoc serialization

void COnAirManagementDoc::Serialize(CArchive& ar)
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
// COnAirManagementDoc diagnostics

#ifdef _DEBUG
void COnAirManagementDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COnAirManagementDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COnAirManagementDoc commands
