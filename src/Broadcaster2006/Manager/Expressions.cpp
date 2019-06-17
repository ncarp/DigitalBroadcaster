// Expressions.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "Expressions.h"
#include "Expression.h"
#include "Languages.h"

// CExpressions dialog

IMPLEMENT_DYNAMIC(CExpressions, CDialog)

CExpressions::CExpressions(CWnd* pParent /*=NULL*/)
	: CDialog(CExpressions::IDD, pParent)
{

}

CExpressions::~CExpressions()
{
}

void CExpressions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_cList);
}


BEGIN_MESSAGE_MAP(CExpressions, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CExpressions::OnNMDblclkList)
END_MESSAGE_MAP()


// CExpressions message handlers

void CExpressions::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if( nPos==-1 ) 
		return;

	long int lID = m_cList.GetItemData(nPos);
	CLanguages rs;
	rs.m_strFilter.Format("ID = '%d'",lID);
	rs.Open();

	CExpression dlg;
	dlg.m_strName=rs.m_Name.TrimRight();
	dlg.m_strCode = rs.m_Code.TrimRight();
	dlg.m_bActiv = rs.m_Activ;

	if( dlg.DoModal()==IDOK )
	{
		rs.Edit();

		rs.m_Name = dlg.m_strName;
		rs.m_Code = dlg.m_strCode;
		rs.m_Activ = dlg.m_bActiv;
		
		m_cList.SetItemText(nPos,0,rs.m_Name.TrimRight());
		m_cList.SetItemText(nPos,1,rs.m_Code.TrimRight());
		m_cList.SetItemText(nPos,2,(rs.m_Activ==0)?" ":"X");

		rs.Update();
	}

	rs.Close();

	*pResult = 0;
}

BOOL CExpressions::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cList.InsertColumn(0,"Expressão",LVCFMT_LEFT,150);
	m_cList.InsertColumn(1,"Código",LVCFMT_LEFT,70);
	m_cList.InsertColumn(2,"Activo",LVCFMT_CENTER,40);

	CLanguages rs;
	rs.m_strSort="Name";
	rs.Open();

	int nPos=0;

	while( !rs.IsEOF() )
	{
		m_cList.InsertItem(nPos,rs.m_Name.TrimRight());
		m_cList.SetItemText(nPos,1,rs.m_Code.TrimRight());
		m_cList.SetItemText(nPos,2,(rs.m_Activ==0)?" ":"X");
		m_cList.SetItemData(nPos,(DWORD_PTR)rs.m_ID);
		rs.MoveNext();
		nPos++;
	}

	rs.Close();
	return TRUE;  
}

