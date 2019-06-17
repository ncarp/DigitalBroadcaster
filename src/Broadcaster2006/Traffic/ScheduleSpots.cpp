// ScheduleSpots.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "ScheduleSpots.h"
#include "TrafficExternals.h"
#include "SheduleDlg.h"
#include "ScheduleSpotDetail.h"
#include "..\include\rsviewspotslist.h"
#include "..\include\RSViewTrafficScheduleSpots.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList *g_ilTree;

/////////////////////////////////////////////////////////////////////////////
// CScheduleSpots property page

IMPLEMENT_DYNCREATE(CScheduleSpots, CPropertyPage)

CScheduleSpots::CScheduleSpots() : CPropertyPage(CScheduleSpots::IDD)
{
	//{{AFX_DATA_INIT(CScheduleSpots)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lCustomerID=0;
	m_bIsNew=TRUE;
}

CScheduleSpots::~CScheduleSpots()
{
}

void CScheduleSpots::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScheduleSpots)
	DDX_Control(pDX, IDC_SPOTS, m_cSpots);
	DDX_Control(pDX, IDC_LIST2, m_cSelected);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScheduleSpots, CPropertyPage)
	//{{AFX_MSG_MAP(CScheduleSpots)
	ON_BN_CLICKED(IDC_BUTTON1, OnRemove)
	ON_BN_CLICKED(IDC_BUTTON2, OnMoveUp)
	ON_BN_CLICKED(IDC_BUTTON3, OnMoveDown)
	ON_NOTIFY(NM_DBLCLK, IDC_SPOTS, OnDblclkSpots)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleSpots message handlers

void CScheduleSpots::OnRemove() 
{	
	int Pos=m_cSelected.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;

	m_cSelected.DeleteItem(Pos);
	CheckData();
}

void CScheduleSpots::OnMoveUp() 
{
	int Pos=m_cSelected.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;
	
	int NewPos;
	LVITEM Item;

	CString strNome=m_cSelected.GetItemText(Pos,0);
	CString strDataI=m_cSelected.GetItemText(Pos,1);
	CString strDataF=m_cSelected.GetItemText(Pos,2);
	int nImage=m_cSelected.GetItemState(Pos,LVIF_IMAGE);

	Item.mask=LVIF_IMAGE|LVIF_INDENT;
	Item.iItem=Pos;
	Item.iSubItem=0;
	m_cSelected.GetItem(&Item);

	typeSpotDetail *lpItem=(typeSpotDetail *)m_cSelected.GetItemData(Pos);

	if( Pos==0 )
		NewPos=m_cSelected.GetItemCount()-1;
	else
		NewPos=Pos-1;

	m_cSelected.DeleteItem(Pos);
	Item.iItem=m_cSelected.InsertItem(NewPos,strNome);
	m_cSelected.SetItem(&Item);
	m_cSelected.SetItemText(NewPos,1,strDataI);
	m_cSelected.SetItemText(NewPos,2,strDataF);
	m_cSelected.SetItemData(NewPos,(DWORD)lpItem);
	m_cSelected.SetItemState(NewPos,LVIS_SELECTED,LVIS_SELECTED);	
}

void CScheduleSpots::OnMoveDown() 
{
	int Pos=m_cSelected.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;
	
	int NewPos;
	LVITEM Item;

	CString strNome=m_cSelected.GetItemText(Pos,0);
	CString strDataI=m_cSelected.GetItemText(Pos,1);
	CString strDataF=m_cSelected.GetItemText(Pos,2);
	int nImage=m_cSelected.GetItemState(Pos,LVIF_IMAGE);

	Item.mask=LVIF_IMAGE|LVIF_INDENT;
	Item.iItem=Pos;
	Item.iSubItem=0;
	m_cSelected.GetItem(&Item);

	typeSpotDetail *lpItem=(typeSpotDetail *)m_cSelected.GetItemData(Pos);

	if( Pos==m_cSelected.GetItemCount()-1 )
		NewPos=0;
	else
		NewPos=Pos+1;

	m_cSelected.DeleteItem(Pos);
	Item.iItem=m_cSelected.InsertItem(NewPos,strNome);
	m_cSelected.SetItem(&Item);
	m_cSelected.SetItemText(NewPos,1,strDataI);
	m_cSelected.SetItemText(NewPos,2,strDataF);
	m_cSelected.SetItemData(NewPos,(DWORD)lpItem);
	m_cSelected.SetItemState(NewPos,LVIS_SELECTED,LVIS_SELECTED);
}

BOOL CScheduleSpots::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString strTemp;

	strTemp.LoadString(IDS_CUSTOMERSPOTS);
	m_cSpots.InsertColumn(0,strTemp,LVCFMT_CENTER,495);

	strTemp.LoadString(IDS_SPOTSTOSCHEDULE);
	m_cSelected.InsertColumn(0,strTemp,LVCFMT_CENTER,195);

	strTemp.LoadString(IDS_AIRINGPERIOD);
	m_cSelected.InsertColumn(1,strTemp,LVCFMT_CENTER,132);

	strTemp.LoadString(IDS_AIRINGDAYS);
	m_cSelected.InsertColumn(2,strTemp,LVCFMT_CENTER,170);
	
	m_cSpots.SetImageList(g_ilTree,LVSIL_SMALL);
	m_cSelected.SetImageList(g_ilTree,LVSIL_SMALL);

	if( !m_bIsNew )
	{
		FillSpotsList();

		CString	str,
				strDays[7];
		long	Pos;
		typeSpotDetail *lpItem;

		strDays[0].LoadString(IDS_SUN);
		strDays[1].LoadString(IDS_MON);
		strDays[2].LoadString(IDS_TUE);
		strDays[3].LoadString(IDS_WED);
		strDays[4].LoadString(IDS_THU);
		strDays[5].LoadString(IDS_FRI);
		strDays[6].LoadString(IDS_SAT);

		CRSViewTrafficScheduleSpots rs(g_strMainConnect);
		rs.m_strFilter.Format("ScheduleID = %d",m_lScheduleID);
		rs.m_strSort="Position";
		rs.Open();

		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			
			lpItem = new typeSpotDetail;
			lpItem->Days[0]		= rs.m_Sun;
			lpItem->Days[1]		= rs.m_Mon;
			lpItem->Days[2]		= rs.m_Tue;
			lpItem->Days[3]		= rs.m_Wed;
			lpItem->Days[4]		= rs.m_Thu;
			lpItem->Days[5]		= rs.m_Fri;
			lpItem->Days[6]		= rs.m_Sat;
			lpItem->EndingDate	= rs.m_EndingDate;
			lpItem->StartingDate= rs.m_StartingDate;
			lpItem->ID			= rs.m_SpotID;

			Pos = m_cSelected.GetItemCount();

			m_cSelected.InsertItem(Pos,rs.m_Name,1);
		
			strTemp.Format("%d-%d-%d a %d-%d-%d",lpItem->StartingDate.GetYear(),
											lpItem->StartingDate.GetMonth(),
											lpItem->StartingDate.GetDay(),
											lpItem->EndingDate.GetYear(),
											lpItem->EndingDate.GetMonth(),
											lpItem->EndingDate.GetDay() );

			m_cSelected.SetItemText(Pos,1,strTemp);

			strTemp="";
			for( int i=0; i<7; i++ )
				if( lpItem->Days[i] ) strTemp+=strDays[i]+" ";

			m_cSelected.SetItemText(Pos,2,strTemp);
			m_cSelected.SetItemData(Pos,(DWORD)lpItem);

			rs.MoveNext();
		}
	}

	CheckData();

	return TRUE;  
}

BOOL CScheduleSpots::OnSetActive() 
{
	CSheduleDlg *pParent=(CSheduleDlg *)GetParent();
	pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);	
	
	typeSpotDetail *lpItem;
	BOOL	bRefresh=FALSE;
	int		nSpots=m_cSelected.GetItemCount();
	int		nPos;

	if( m_lCustomerID!=pParent->m_pMain->m_lCustomerID )
	{
		m_lCustomerID=pParent->m_pMain->m_lCustomerID;
		m_cSpots.DeleteAllItems();
		m_cSelected.DeleteAllItems();

		FillSpotsList();
	}

	if( m_dStartingDate != pParent->m_pMain->m_dStartingDate )
	{
		COleDateTime	dPrev=m_dStartingDate;

		m_dStartingDate = pParent->m_pMain->m_dStartingDate;
		for( nPos=0; nPos<nSpots; nPos++ )
		{
			lpItem = (typeSpotDetail *)m_cSelected.GetItemData(nPos);
			if( lpItem->StartingDate==dPrev )
				lpItem->StartingDate=m_dStartingDate;
		}
		bRefresh=TRUE;
	}

	if( m_dEndingDate != pParent->m_pMain->m_dEndingDate )
	{
		COleDateTime dPrev = m_dEndingDate;

		m_dEndingDate = pParent->m_pMain->m_dEndingDate;

		for( nPos=0; nPos<nSpots; nPos++ )
		{
			lpItem = (typeSpotDetail *)m_cSelected.GetItemData(nPos);
			if( lpItem->EndingDate==dPrev )
				lpItem->EndingDate=m_dEndingDate;
		}
		bRefresh=TRUE;
	}

	if( bRefresh )
	{
		CString strTemp;
		for( nPos=0; nPos<nSpots; nPos++ )
		{
			lpItem = (typeSpotDetail *)m_cSelected.GetItemData(nPos);
			strTemp.Format("%d-%d-%d a %d-%d-%d",lpItem->StartingDate.GetYear(),
													lpItem->StartingDate.GetMonth(),
													lpItem->StartingDate.GetDay(),
													lpItem->EndingDate.GetYear(),
													lpItem->EndingDate.GetMonth(),
													lpItem->EndingDate.GetDay() );
			m_cSelected.SetItemText(nPos,1,strTemp);
		}
	}
	CheckData();

	return CPropertyPage::OnSetActive();
}

void CScheduleSpots::FillSpotsList()
{
	CRSViewSpotsList rs(g_strMainConnect);
	int		iPos=0;
	
	rs.m_strFilter.Format("CustomerID = %d",m_lCustomerID);
	rs.m_strSort="Name";
	rs.Open();

	if( rs.GetRecordCount() )
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			m_cSpots.InsertItem(iPos,rs.m_Name,1);
			m_cSpots.SetItemData(iPos,rs.m_ID);
			rs.MoveNext();
			iPos++;
		}

	rs.Close();
}

void CScheduleSpots::OnDblclkSpots(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString strTemp;
	long Pos=m_cSpots.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1 ) return;

	CScheduleSpotDetail dl(this);
	strTemp=m_cSpots.GetItemText(Pos,0);

	dl.m_strName	= strTemp;
	dl.m_bSun		= TRUE;
	dl.m_bMon		= TRUE;
	dl.m_bTue		= TRUE;
	dl.m_bWed		= TRUE;
	dl.m_bThu		= TRUE;
	dl.m_bFri		= TRUE;
	dl.m_bSat		= TRUE;

	dl.m_dStartingDate = m_dStartingDate;
	dl.m_dEndingDate=m_dEndingDate;
	dl.m_dEndingLimit=m_dEndingDate;
	dl.m_dStartingLimit=m_dStartingDate;

	if( dl.DoModal()==IDOK )
	{
		CString strDays[7];
		strDays[0].LoadString(IDS_SUN);
		strDays[1].LoadString(IDS_MON);
		strDays[2].LoadString(IDS_TUE);
		strDays[3].LoadString(IDS_WED);
		strDays[4].LoadString(IDS_THU);
		strDays[5].LoadString(IDS_FRI);
		strDays[6].LoadString(IDS_SAT);

		typeSpotDetail *lpItem = new typeSpotDetail;
		lpItem->EndingDate.SetDateTime(dl.m_dEndingDate.GetYear(),dl.m_dEndingDate.GetMonth(),dl.m_dEndingDate.GetDay(),0,0,0);
		lpItem->StartingDate.SetDateTime(dl.m_dStartingDate.GetYear(),dl.m_dStartingDate.GetMonth(),dl.m_dStartingDate.GetDay(),0,0,0);
		lpItem->ID=m_cSpots.GetItemData(Pos);
		lpItem->Days[0]=dl.m_bSun;
		lpItem->Days[1]=dl.m_bMon;
		lpItem->Days[2]=dl.m_bTue;
		lpItem->Days[3]=dl.m_bWed;
		lpItem->Days[4]=dl.m_bThu;
		lpItem->Days[5]=dl.m_bFri;
		lpItem->Days[6]=dl.m_bSat;

		Pos=m_cSelected.GetNextItem(-1,LVNI_SELECTED);
		if( Pos==-1 )
			Pos=0;

		m_cSelected.InsertItem(Pos,strTemp,1);
		
		strTemp.Format("%d-%d-%d a %d-%d-%d",dl.m_dStartingDate.GetYear(),
											dl.m_dStartingDate.GetMonth(),
											dl.m_dStartingDate.GetDay(),
											dl.m_dEndingDate.GetYear(),
											dl.m_dEndingDate.GetMonth(),
											dl.m_dEndingDate.GetDay() );
		m_cSelected.SetItemText(Pos,1,strTemp);

		strTemp="";
		for( int i=0; i<7; i++ )
			if( lpItem->Days[i] ) strTemp+=strDays[i]+" ";

		m_cSelected.SetItemText(Pos,2,strTemp);
		m_cSelected.SetItemData(Pos,(DWORD)lpItem);
		
	}
	CheckData(); 

	*pResult = 0;
}

void CScheduleSpots::CheckData()
{
	CPropertySheet *pParent=(CPropertySheet *)GetParent();
	
	if( m_cSelected.GetItemCount() )
		pParent->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	else
		pParent->SetWizardButtons(PSWIZB_BACK);

}

LRESULT CScheduleSpots::OnWizardNext() 
{
	m_nSpots = m_cSelected.GetItemCount();
	
	for( int i=0; i<m_nSpots; i++ )
		m_Spots[i]=(typeSpotDetail *)m_cSelected.GetItemData(i);

	return CPropertyPage::OnWizardNext();
}

void CScheduleSpots::OnDblclkSelected(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString strTemp;
	long Pos=m_cSelected.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1 ) return;

	CScheduleSpotDetail dl(this);
	strTemp=m_cSelected.GetItemText(Pos,0);
	typeSpotDetail *lpItem = (typeSpotDetail *)m_cSelected.GetItemData(Pos);

	dl.m_strName	= strTemp;
	dl.m_bSun		= lpItem->Days[0];
	dl.m_bMon		= lpItem->Days[1];
	dl.m_bTue		= lpItem->Days[2];
	dl.m_bWed		= lpItem->Days[3];
	dl.m_bThu		= lpItem->Days[4];
	dl.m_bFri		= lpItem->Days[5];
	dl.m_bSat		= lpItem->Days[6];

	dl.m_dStartingDate	= lpItem->StartingDate;
	dl.m_dEndingDate	= lpItem->EndingDate;
	dl.m_dEndingLimit	= m_dEndingDate;
	dl.m_dStartingLimit	= m_dStartingDate;

	if( dl.DoModal()==IDOK )
	{
		CString strDays[7];
		strDays[0].LoadString(IDS_SUN);
		strDays[1].LoadString(IDS_MON);
		strDays[2].LoadString(IDS_TUE);
		strDays[3].LoadString(IDS_WED);
		strDays[4].LoadString(IDS_THU);
		strDays[5].LoadString(IDS_FRI);
		strDays[6].LoadString(IDS_SAT);

		lpItem->EndingDate.SetDateTime(dl.m_dEndingDate.GetYear(),dl.m_dEndingDate.GetMonth(),dl.m_dEndingDate.GetDay(),0,0,0);
		lpItem->StartingDate.SetDateTime(dl.m_dStartingDate.GetYear(),dl.m_dStartingDate.GetMonth(),dl.m_dStartingDate.GetDay(),0,0,0);
//		lpItem->ID=m_cSpots.GetItemData(Pos);
		lpItem->Days[0]=dl.m_bSun;
		lpItem->Days[1]=dl.m_bMon;
		lpItem->Days[2]=dl.m_bTue;
		lpItem->Days[3]=dl.m_bWed;
		lpItem->Days[4]=dl.m_bThu;
		lpItem->Days[5]=dl.m_bFri;
		lpItem->Days[6]=dl.m_bSat;

		m_cSelected.SetItemText(Pos,0,strTemp);
		
		strTemp.Format("%d-%d-%d a %d-%d-%d",dl.m_dStartingDate.GetYear(),
											dl.m_dStartingDate.GetMonth(),
											dl.m_dStartingDate.GetDay(),
											dl.m_dEndingDate.GetYear(),
											dl.m_dEndingDate.GetMonth(),
											dl.m_dEndingDate.GetDay() );
		m_cSelected.SetItemText(Pos,1,strTemp);

		strTemp="";
		for( int i=0; i<7; i++ )
			if( lpItem->Days[i] ) strTemp+=strDays[i]+" ";

		m_cSelected.SetItemText(Pos,2,strTemp);
	}
	CheckData(); 
	
	*pResult = 0;
}
