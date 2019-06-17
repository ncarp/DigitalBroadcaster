// JingleSelector.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "JingleSelector.h"
#include "..\include\rsViewJinglesSchedulingData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJingleSelector dialog
extern	CImageList	*g_ilTree;

CJingleSelector::CJingleSelector(CWnd* pParent /*=NULL*/)
	: CDialog(CJingleSelector::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJingleSelector)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strSort = "JingleType,Name";
}


void CJingleSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJingleSelector)
	DDX_Control(pDX, IDC_LIST1, m_cList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJingleSelector, CDialog)
	//{{AFX_MSG_MAP(CJingleSelector)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJingleSelector message handlers

BOOL CJingleSelector::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int		Pos=0;
	CString str,
			str1,
			str2;
	CRect rect;
	m_cList.GetClientRect(&rect);

	m_cList.SetImageList(g_ilTree,LVSIL_SMALL);

	str.LoadString(IDS_JINGLES);
	m_cList.InsertColumn(0,str,LVCFMT_LEFT,rect.Width()-160);

	str.LoadString(IDS_LASTSCHEDULE);
	m_cList.InsertColumn(1,str,LVCFMT_CENTER,150);

	CRSViewJinglesSchedulingData rs( m_strConnect );
	rs.m_strFilter=m_strSQL;
	rs.m_strSort=m_strSort;
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_JingleType.TrimRight();
		rs.m_Name.TrimRight();

		if( rs.IsFieldNull(&rs.m_MaxDate) )
			str="";
		else
		{
			str1.Format("%4d-%2d-%2d",rs.m_MaxDate.GetYear(),rs.m_MaxDate.GetMonth(),rs.m_MaxDate.GetDay());
			str2.Format("%2d:%2d:%2d",rs.m_MaxDate.GetHour(),rs.m_MaxDate.GetMinute(),rs.m_MaxDate.GetSecond() );
			str1.Replace(" ","0");
			str2.Replace(" ","0");
			str=str1+" "+str2;
		}

		m_cList.InsertItem(Pos,rs.m_JingleType+" - "+rs.m_Name,4);
		m_cList.SetItemText(Pos,1,str);
		m_cList.SetItemData(Pos,rs.m_JingleID);

		Pos++;
		rs.MoveNext();
	}
	rs.Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CJingleSelector::OnOK() 
{
	int Pos = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if( Pos == -1 ) return;

	m_strJingleName = m_cList.GetItemText(Pos,0);
	m_JingleID = m_cList.GetItemData(Pos);
	
	CDialog::OnOK();
}

void CJingleSelector::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOK();
	
	*pResult = 0;
}
