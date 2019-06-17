// NewsRoomDoc.cpp : implementation of the CNewsRoomDoc class
//

#include "stdafx.h"
#include "NewsRoom.h"

#include "NewsRoomDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomDoc

IMPLEMENT_DYNCREATE(CNewsRoomDoc, CDocument)

BEGIN_MESSAGE_MAP(CNewsRoomDoc, CDocument)
	//{{AFX_MSG_MAP(CNewsRoomDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomDoc construction/destruction

CNewsRoomDoc::CNewsRoomDoc()
{
	// TODO: add one-time construction code here

}

CNewsRoomDoc::~CNewsRoomDoc()
{
}

BOOL CNewsRoomDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNewsRoomDoc serialization

void CNewsRoomDoc::Serialize(CArchive& ar)
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
// CNewsRoomDoc diagnostics

#ifdef _DEBUG
void CNewsRoomDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNewsRoomDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNewsRoomDoc commands
