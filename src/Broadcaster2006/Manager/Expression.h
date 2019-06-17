#pragma once


// CExpression dialog

class CExpression : public CDialog
{
	DECLARE_DYNAMIC(CExpression)

public:
	CExpression(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExpression();

// Dialog Data
	enum { IDD = IDD_EXPRESSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strCode;
	BOOL m_bActiv;
};
