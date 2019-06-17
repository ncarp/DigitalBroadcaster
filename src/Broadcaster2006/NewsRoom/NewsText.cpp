// NewsText.cpp : implementation file
//

#include "stdafx.h"
#include "NewsRoom.h"
#include "NewsText.h"
#include "..\include\RSTypeOfRM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CString	g_strMainConnect;
/////////////////////////////////////////////////////////////////////////////
// CNewsText dialog

CNewsText::CNewsText(CWnd* pParent /*=NULL*/)
	: CDialog(CNewsText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewsText)
	m_Date = COleDateTime::GetCurrentTime();
	m_KeyWords = _T("");
	m_Name = _T("");
	m_Text = _T("");
	m_Type = _T("");
	//}}AFX_DATA_INIT
}


void CNewsText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewsText)
	DDX_Control(pDX, IDC_TEXTTYPE, m_cType);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_Date);
	DDX_Text(pDX, IDC_KEYWORDS, m_KeyWords);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_TEXT, m_Text);
	DDV_MaxChars(pDX, m_Text, 32000);
	DDX_CBString(pDX, IDC_TEXTTYPE, m_Type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewsText, CDialog)
	//{{AFX_MSG_MAP(CNewsText)
	ON_CBN_KILLFOCUS(IDC_TEXTTYPE, OnKillfocusTexttype)
	ON_CBN_SELCHANGE(IDC_TEXTTYPE, OnSelchangeTexttype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewsText message handlers

BOOL CNewsText::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;

	str.LoadString(IDS_REFRESH);

	m_cType.AddString(str);
	m_cType.SetItemData(0,0);
	
	return TRUE;  
}

void CNewsText::OnOK() 
{
	UpdateData();

	if( m_TypeID==0 )
		return;

	m_Name.TrimRight();
	if( m_Name.GetLength()==0 )
		return;
	
	CDialog::OnOK();
}

void CNewsText::OnKillfocusTexttype() 
{
	CString str;
	m_cType.GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if( str.GetLength()==0 )
	{
		m_TypeID = 0;
		return;
	}

	CRSTypeOfRM	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_cType.SetWindowText(rs.m_Name);
		m_TypeID=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWTEXT,MB_YESNO)==IDYES )
		{
			rs.AddNew();
			m_cType.GetWindowText(rs.m_Name);
			rs.Update();

			rs.Requery();
			m_TypeID=rs.m_ID;
		}
		else
		{
			m_cType.SetWindowText("");
			m_TypeID=0;
		}
	}
	rs.Close();	
}

void CNewsText::OnSelchangeTexttype() 
{
	int Pos=m_cType.GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lData=m_cType.GetItemData(Pos);
	if( lData==0 )
	{
		CRSTypeOfRM rs(g_strMainConnect);
		rs.m_strFilter="Activ = 1";
		rs.m_strSort="Name";
		rs.Open();

		m_cType.ResetContent();

		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_cType.AddString(rs.m_Name);
			m_cType.SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}
		rs.Close();

		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_cType.AddString(str);
		m_cType.SetItemData(Pos,0);
	}
}
