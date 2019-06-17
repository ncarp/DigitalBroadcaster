// SchedulerDoc.cpp : implementation of the CSchedulerDoc class
//

#include "stdafx.h"
#include "Scheduler.h"

#include "SchedulerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchedulerDoc

IMPLEMENT_DYNCREATE(CSchedulerDoc, CDocument)

BEGIN_MESSAGE_MAP(CSchedulerDoc, CDocument)
	//{{AFX_MSG_MAP(CSchedulerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchedulerDoc construction/destruction

CSchedulerDoc::CSchedulerDoc()
{
	m_ScheduleID = 0;
}

CSchedulerDoc::~CSchedulerDoc()
{
}

BOOL CSchedulerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSchedulerDoc serialization

void CSchedulerDoc::Serialize(CArchive& ar)
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
// CSchedulerDoc diagnostics

#ifdef _DEBUG
void CSchedulerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSchedulerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSchedulerDoc commands
