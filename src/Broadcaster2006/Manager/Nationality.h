#pragma once


// CNationality dialog

class CNationality : public CDialog
{
	DECLARE_DYNAMIC(CNationality)

public:
	CNationality(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNationality();

// Dialog Data
	enum { IDD = IDD_NATIONALITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNationality;
	CString m_strCode;
	BOOL m_bActiv;
	BOOL m_bEU;
};
