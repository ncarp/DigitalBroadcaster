// MusicSelector.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "MusicSelector.h"
#include "..\Include\RSViewMusicSchedulingSata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusicSelector dialog
extern	CImageList	*g_ilTree;

CMusicSelector::CMusicSelector(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicSelector::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMusicSelector)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_strSort = "ArtistName,TrackTitle";
}


void CMusicSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMusicSelector)
	DDX_Control(pDX, IDC_LIST1, m_cList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMusicSelector, CDialog)
	//{{AFX_MSG_MAP(CMusicSelector)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicSelector message handlers

BOOL CMusicSelector::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int		Pos=0;
	CString str,
			str1,
			str2;
	CRect rect;
	m_cList.GetClientRect(&rect);

	m_cList.SetImageList(g_ilTree,LVSIL_SMALL);

	str.LoadString(IDS_MUSIC);
	m_cList.InsertColumn(0,str,LVCFMT_LEFT,rect.Width()-160);

	str.LoadString(IDS_LASTSCHEDULE);
	m_cList.InsertColumn(1,str,LVCFMT_CENTER,150);

	CRSViewMusicSchedulingSata rs( m_strConnect );
	rs.m_strFilter=m_strSQL;
	rs.m_strSort=m_strSort;
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_ArtistName.TrimRight();
		rs.m_TrackTitle.TrimRight();
		if( rs.IsFieldNull(&rs.m_MaxMusicDate) )
			str="";
		else
		{
			str1.Format("%4d-%2d-%2d",rs.m_MaxMusicDate.GetYear(),rs.m_MaxMusicDate.GetMonth(),rs.m_MaxMusicDate.GetDay());
			str2.Format("%2d:%2d:%2d",rs.m_MaxMusicDate.GetHour(),rs.m_MaxMusicDate.GetMinute(),rs.m_MaxMusicDate.GetSecond() );
			str1.Replace(" ","0");
			str2.Replace(" ","0");
			str=str1+" "+str2;
		}

		m_cList.InsertItem(Pos,rs.m_ArtistName+" - "+rs.m_TrackTitle,17);
		m_cList.SetItemText(Pos,1,str);
		m_cList.SetItemData(Pos,rs.m_TrackID);

		Pos++;
		rs.MoveNext();
	}
	rs.Close();

	return TRUE;  
}

void CMusicSelector::OnOK() 
{
	int Pos = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if( Pos == -1 ) return;

	m_strSongName = m_cList.GetItemText(Pos,0);
	m_MusicID = m_cList.GetItemData(Pos);
	
	CDialog::OnOK();
}

void CMusicSelector::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOK();
	
	*pResult = 0;
}
