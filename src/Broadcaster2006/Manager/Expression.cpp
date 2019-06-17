// Expression.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "Expression.h"


// CExpression dialog

IMPLEMENT_DYNAMIC(CExpression, CDialog)

CExpression::CExpression(CWnd* pParent /*=NULL*/)
	: CDialog(CExpression::IDD, pParent)
	, m_strName(_T(""))
	, m_strCode(_T(""))
	, m_bActiv(FALSE)
{

}

CExpression::~CExpression()
{
}

void CExpression::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EXPRESSION, m_strName);
	DDV_MaxChars(pDX, m_strName, 100);
	DDX_Text(pDX, IDC_CODE, m_strCode);
	DDV_MaxChars(pDX, m_strCode, 10);
	DDX_Check(pDX, IDC_ACTIV, m_bActiv);
}


BEGIN_MESSAGE_MAP(CExpression, CDialog)
END_MESSAGE_MAP()


// CExpression message handlers
