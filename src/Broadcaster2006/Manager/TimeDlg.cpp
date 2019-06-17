// TimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "TimeDlg.h"
#include "..\include\rsPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString	g_strMainConnect;

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg dialog


CTimeDlg::CTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeDlg)
	m_nFolder = -1;
	m_strName = _T("");
	m_nPath = -1;
	//}}AFX_DATA_INIT
}


void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeDlg)
	DDX_Control(pDX, IDC_PATH, m_ctrlPath);
	DDX_Control(pDX, IDC_FOLDER, m_ctrlFolder);
	DDX_CBIndex(pDX, IDC_FOLDER, m_nFolder);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_CBIndex(pDX, IDC_PATH, m_nPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeDlg)
	ON_CBN_SELCHANGE(IDC_PATH, OnSelchangePath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeDlg message handlers

BOOL CTimeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int nPos;
	CRSPath	rs( g_strMainConnect );
	rs.m_strFilter = "TimeSignal = 1";
	rs.m_strSort = "Path";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Path.TrimRight();
		nPos=m_ctrlPath.AddString( rs.m_Path );
		m_ctrlPath.SetItemData(nPos,rs.m_ID);

		rs.MoveNext();
	}

	if( m_strPath.GetLength()!=0 )
	{
		nPos=m_ctrlPath.FindStringExact(-1,m_strPath);
		m_ctrlPath.SetCurSel(nPos);

		if( nPos!=CB_ERR )
		{
			OnSelchangePath();
			nPos=m_ctrlFolder.FindStringExact(-1,m_strFolder);
			m_ctrlFolder.SetCurSel(nPos);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTimeDlg::OnSelchangePath() 
{
	CString strPath;
	int		nPos=m_ctrlPath.GetCurSel();

	m_ctrlPath.GetLBText(nPos,strPath);

	CFileFind	finder;
	BOOL		bWorking;
	CString		str;

	m_ctrlFolder.ResetContent();

	bWorking=finder.FindFile(strPath+"\\*.*");

	while( bWorking )
	{
		bWorking=finder.FindNextFile();
		if( (finder.IsDirectory()) && (!finder.IsDots()) )
			nPos=m_ctrlFolder.AddString(finder.GetFileName());
	}
}

void CTimeDlg::OnOK() 
{
	UpdateData();
	
	m_strName.TrimRight();
	if( m_strName.GetLength()==0 )
		return;

	if( m_nPath==CB_ERR )
		return;
	
	m_ctrlPath.GetLBText(m_nPath,m_strPath);
	m_lPathID=m_ctrlPath.GetItemData(m_nPath);

	if( m_nFolder==CB_ERR )
		return;
	
	m_ctrlFolder.GetLBText(m_nFolder,m_strFolder);

	CDialog::OnOK();
}
