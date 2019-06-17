// ErcMainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "ErcMainDlg.h"
#include "folderdlg.h"
#include "erccreatedlg.h"
#include "..\include\rsradiostations.h"
#include "..\common\include\folderdialog.h"


// CErcMainDlg dialog

IMPLEMENT_DYNAMIC(CErcMainDlg, CDialog)

CErcMainDlg::CErcMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CErcMainDlg::IDD, pParent)
	, m_strFolder(_T(""))
	, m_nRadio(0)
	, m_DateStart(COleDateTime::GetCurrentTime())
	, m_DateFinish(COleDateTime::GetCurrentTime())
{

}

CErcMainDlg::~CErcMainDlg()
{
}

void CErcMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATION, m_cStation);
	DDX_Text(pDX, IDC_FOLDER, m_strFolder);
	DDX_Control(pDX, IDC_FOLDER, m_cFolder);
	DDX_CBIndex(pDX, IDC_STATION, m_nRadio);
	DDX_DateTimeCtrl(pDX, IDC_START, m_DateStart);
	DDX_DateTimeCtrl(pDX, IDC_END, m_DateFinish);
}


BEGIN_MESSAGE_MAP(CErcMainDlg, CDialog)
	ON_BN_CLICKED(IDC_CHOOSEFOLDER, &CErcMainDlg::OnBnClickedChoosefolder)
END_MESSAGE_MAP()

BOOL CErcMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nPos;
	CRSRadioStations rs("Broadcaster");

	rs.Open();
	while( !rs.IsEOF() )
	{
		nPos=m_cStation.AddString(rs.m_Name.TrimRight());
		m_cStation.SetItemData(nPos,rs.m_ID);
		rs.MoveNext();
	}
	rs.Close();

	return TRUE;
}

// CErcMainDlg message handlers


void CErcMainDlg::OnBnClickedChoosefolder()
{
	UpdateData();

	CFolderDialog dlg(NULL,m_strFolder);
	
	if( dlg.DoModal()==IDOK )
	{
		m_cFolder.SetWindowTextA(dlg.GetFolderPath());
	}
}

void CErcMainDlg::OnOK()
{
	UpdateData();

	if( m_nRadio==CB_ERR )
	{
		AfxMessageBox("Tem que seleccionar uma rádio");
		return;
	}

	if( m_DateFinish < m_DateStart )
	{
		AfxMessageBox("A data final é anterior à data final");
	}

	if( m_strFolder.GetLength()==0 )
	{
		AfxMessageBox("Tem que seleccionar a pasta onde guardar os ficheiros");
	}

	long lRadioID = m_cStation.GetItemData(m_nRadio);

	CErcCreateDlg dlg;

	dlg.m_lRadioID = lRadioID;
	dlg.m_DateStart = m_DateStart;
	dlg.m_DateFinish = m_DateFinish;
	dlg.m_strFolder = m_strFolder.TrimRight();
	dlg.DoModal();

	CDialog::OnOK();
}
