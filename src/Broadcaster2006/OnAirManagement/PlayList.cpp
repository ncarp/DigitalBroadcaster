// PlayList.cpp : implementation file
//

#include "stdafx.h"
#include "OnAirManagement.h"
#include "PlayList.h"
#include "..\include\rsPlayListsDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayList dialog


CPlayList::CPlayList(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayList)
	m_OnAir = FALSE;
	m_Name = _T("");
	//}}AFX_DATA_INIT
	m_ID=0;
}


void CPlayList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayList)
	DDX_Check(pDX, IDC_CHECK1, m_OnAir);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayList, CDialog)
	//{{AFX_MSG_MAP(CPlayList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayList message handlers

void CPlayList::OnOK() 
{
	UpdateData();

	m_Name.TrimRight();
	if( m_Name.GetLength() == 0 )
		return;
	
	CString str=m_Name;
	str.Replace("'","''");

	CRSPlayListsDefinition rs( m_strConnect );
	rs.m_strFilter.Format("Name = '%s' AND Activ = 1 AND ID <> %d",str,m_ID);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		rs.Close();
		return;
	}
	rs.Close();

	CDialog::OnOK();
}
