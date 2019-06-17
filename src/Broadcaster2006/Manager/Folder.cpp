// Folder.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "Folder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFolder dialog


CFolder::CFolder(CWnd* pParent /*=NULL*/)
	: CDialog(CFolder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFolder)
	m_bJingles = FALSE;
	m_bMusic = FALSE;
	m_strPath = _T("");
	m_bProducer = FALSE;
	m_bRMs = FALSE;
	m_bSpots = FALSE;
	m_bTakes = FALSE;
	m_bTime = FALSE;
	//}}AFX_DATA_INIT
}


void CFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFolder)
	DDX_Check(pDX, IDC_JINGLES, m_bJingles);
	DDX_Check(pDX, IDC_MUSIC, m_bMusic);
	DDX_Text(pDX, IDC_PATH, m_strPath);
	DDX_Check(pDX, IDC_PRODUCER, m_bProducer);
	DDX_Check(pDX, IDC_RMS, m_bRMs);
	DDX_Check(pDX, IDC_SPOTS, m_bSpots);
	DDX_Check(pDX, IDC_TAKES, m_bTakes);
	DDX_Check(pDX, IDC_TIME, m_bTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFolder, CDialog)
	//{{AFX_MSG_MAP(CFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFolder message handlers

void CFolder::OnOK() 
{
	UpdateData();
	
	m_strPath.TrimRight();

	if( m_strPath.GetLength()==0 )
		return;
	
	CDialog::OnOK();
}
