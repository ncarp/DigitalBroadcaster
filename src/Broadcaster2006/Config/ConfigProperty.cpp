// ConfigProperty.cpp : implementation file
//

#include "stdafx.h"
#include "Config.h"
#include "ConfigProperty.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigProperty

IMPLEMENT_DYNAMIC(CConfigProperty, CPropertySheet)

CConfigProperty::CConfigProperty(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	dlAudio = new CConfigDlg();

	AddPage(dlAudio);
}

CConfigProperty::CConfigProperty(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
		dlAudio = new CConfigDlg();

	AddPage(dlAudio);
}

CConfigProperty::~CConfigProperty()
{
}


BEGIN_MESSAGE_MAP(CConfigProperty, CPropertySheet)
	//{{AFX_MSG_MAP(CConfigProperty)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigProperty message handlers
