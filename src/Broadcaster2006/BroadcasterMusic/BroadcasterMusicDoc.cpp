// BroadcasterMusicDoc.cpp : implementation of the CBroadcasterMusicDoc class
//

#include "stdafx.h"
#include "BroadcasterMusic.h"

#include "BroadcasterMusicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBroadcasterMusicDoc

IMPLEMENT_DYNCREATE(CBroadcasterMusicDoc, CDocument)

BEGIN_MESSAGE_MAP(CBroadcasterMusicDoc, CDocument)
END_MESSAGE_MAP()


// CBroadcasterMusicDoc construction/destruction

CBroadcasterMusicDoc::CBroadcasterMusicDoc()
{
	// TODO: add one-time construction code here

}

CBroadcasterMusicDoc::~CBroadcasterMusicDoc()
{
}

BOOL CBroadcasterMusicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CBroadcasterMusicDoc serialization

void CBroadcasterMusicDoc::Serialize(CArchive& ar)
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


// CBroadcasterMusicDoc diagnostics

#ifdef _DEBUG
void CBroadcasterMusicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBroadcasterMusicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBroadcasterMusicDoc commands
