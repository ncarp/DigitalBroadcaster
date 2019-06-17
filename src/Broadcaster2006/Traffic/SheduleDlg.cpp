// SheduleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "SheduleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSheduleDlg

IMPLEMENT_DYNAMIC(CSheduleDlg, CPropertySheet)

CSheduleDlg::CSheduleDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pMain	= new CScheduleMain();
	m_pSpots= new CScheduleSpots();
	m_pBlocks=new CScheduleBlocks();

	AddPage(m_pMain);
	AddPage(m_pSpots);
	AddPage(m_pBlocks);

	SetWizardMode();
}


CSheduleDlg::~CSheduleDlg()
{
}


BEGIN_MESSAGE_MAP(CSheduleDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CSheduleDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheduleDlg message handlers
