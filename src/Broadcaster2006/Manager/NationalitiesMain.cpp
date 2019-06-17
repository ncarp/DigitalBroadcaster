// NationalitiesMain.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "NationalitiesMain.h"
#include "RSNationalities.h"
#include "Nationality.h"


// CNationalitiesMain dialog

IMPLEMENT_DYNAMIC(CNationalitiesMain, CDialog)

CNationalitiesMain::CNationalitiesMain(CWnd* pParent /*=NULL*/)
	: CDialog(CNationalitiesMain::IDD, pParent)
{

}

CNationalitiesMain::~CNationalitiesMain()
{
}

void CNationalitiesMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_cList);
}


BEGIN_MESSAGE_MAP(CNationalitiesMain, CDialog)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CNationalitiesMain::OnNMDblclkList)
END_MESSAGE_MAP()


// CNationalitiesMain message handlers

int CNationalitiesMain::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CNationalitiesMain::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cList.InsertColumn(0,"Nacionalidade",LVCFMT_LEFT,400);
	m_cList.InsertColumn(1,"Código",LVCFMT_LEFT,200);
	m_cList.InsertColumn(2,"Activo",LVCFMT_CENTER,50);
	m_cList.InsertColumn(3,"UE",LVCFMT_CENTER,40);

	CRSNationalities rs;
	
	rs.m_strSort="Nationality";
	rs.Open();

	int nPos=0;

	while( !rs.IsEOF() )
	{
		m_cList.InsertItem(nPos,rs.m_Nationality.TrimRight());
		m_cList.SetItemText(nPos,1,(CString)rs.m_Code);
		m_cList.SetItemText(nPos,2,(rs.m_Activ==0)?" ":"X");
		m_cList.SetItemText(nPos,3,(rs.m_EU==0)?" ":"X");
		m_cList.SetItemData(nPos,(DWORD_PTR)rs.m_ID);

		rs.MoveNext();
		nPos++;
	}

	rs.Close();

	return TRUE;
}

void CNationalitiesMain::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if( nPos==-1)
		return;

	int lID = m_cList.GetItemData(nPos);
	CRSNationalities rs;

	rs.m_strFilter.Format("ID = '%d'",lID);
	rs.Open();

	CNationality dlg;
	dlg.m_strCode = rs.m_Code;
	dlg.m_strNationality = rs.m_Nationality;
	dlg.m_bActiv = rs.m_Activ;
	dlg.m_bEU = rs.m_EU;

	if( dlg.DoModal()==IDOK )
	{
		rs.Edit();
		rs.m_Nationality=dlg.m_strNationality;
		rs.m_Code = dlg.m_strCode;
		rs.m_Activ = dlg.m_bActiv;
		rs.m_EU = dlg.m_bEU;

		m_cList.SetItemText(nPos,0,rs.m_Nationality.TrimRight());
		m_cList.SetItemText(nPos,1,(CString)rs.m_Code);
		m_cList.SetItemText(nPos,2,(rs.m_Activ==0)?" ":"X");
		m_cList.SetItemText(nPos,3,(rs.m_EU==0)?" ":"X");

		rs.Update();
	}

	rs.Close();

	*pResult = 0;
}
