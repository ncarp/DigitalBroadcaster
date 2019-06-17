// Nationality.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "Nationality.h"


// CNationality dialog

IMPLEMENT_DYNAMIC(CNationality, CDialog)

CNationality::CNationality(CWnd* pParent /*=NULL*/)
	: CDialog(CNationality::IDD, pParent)
	, m_strNationality(_T(""))
	, m_strCode(_T(""))
	, m_bActiv(FALSE)
	, m_bEU(FALSE)
{

}

CNationality::~CNationality()
{
}

void CNationality::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NATIONALITY, m_strNationality);
	DDV_MaxChars(pDX, m_strNationality, 100);
	DDX_Text(pDX, IDC_CODE, m_strCode);
	DDV_MaxChars(pDX, m_strCode, 10);
	DDX_Check(pDX, IDC_ACTIV, m_bActiv);
	DDX_Check(pDX, IDC_UE, m_bEU);
}


BEGIN_MESSAGE_MAP(CNationality, CDialog)
END_MESSAGE_MAP()


// CNationality message handlers
