// ScheduleBlocks.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "ScheduleBlocks.h"
#include "SheduleDlg.h"
#include "ScheduleBlockDetail.h"
#include "TrafficExternals.h"
#include "..\include\utils.h"
#include "..\include\RSRadioStations.h"
#include "..\include\RSBlocksDefinition.h"
#include "..\Include\RSViewBlocksStatusOnSpots.h"
#include "..\include\RSViewTrafficScheduleBlocks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList *g_ilTree;

/////////////////////////////////////////////////////////////////////////////
// CScheduleBlocks property page

IMPLEMENT_DYNCREATE(CScheduleBlocks, CPropertyPage)

CScheduleBlocks::CScheduleBlocks() : CPropertyPage(CScheduleBlocks::IDD)
{
	//{{AFX_DATA_INIT(CScheduleBlocks)
	//}}AFX_DATA_INIT
	m_lStationID=0;
	m_nBlocks=0;
	m_bIsNew=TRUE;
	m_bIsWorking=FALSE;
}

CScheduleBlocks::~CScheduleBlocks()
{
}

void CScheduleBlocks::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScheduleBlocks)
	DDX_Control(pDX, IDC_SELECTED, m_cSelected);
	DDX_Control(pDX, IDC_BLOCKS, m_cBlocks);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScheduleBlocks, CPropertyPage)
	//{{AFX_MSG_MAP(CScheduleBlocks)
	ON_NOTIFY(NM_DBLCLK, IDC_BLOCKS, OnDblclkBlocks)
	ON_BN_CLICKED(IDC_BUTTON1, OnRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_SELECTED, OnDblclkSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleBlocks message handlers

BOOL CScheduleBlocks::OnSetActive() 
{
	CPropertyPage::OnSetActive();

	CSheduleDlg *pdl=(CSheduleDlg *)GetParent();
	typeBlockDetail *lpItem;
	BOOL		bNeedToRefreshList=FALSE,
				bNeedToRefreshSelected=FALSE;
	int			nBlocksSelected=m_cSelected.GetItemCount();
	int			nCont;
		
	if( m_lStationID != pdl->m_pMain->m_lStationID )
	{
		m_lStationID = pdl->m_pMain->m_lStationID;
		bNeedToRefreshList=TRUE;
	}

	if( m_dInicialDate!=pdl->m_pMain->m_dStartingDate )
	{
		COleDateTime PrevInitialDate = m_dInicialDate;

		m_dInicialDate.SetDateTime(pdl->m_pMain->m_dStartingDate.GetYear(),pdl->m_pMain->m_dStartingDate.GetMonth(),pdl->m_pMain->m_dStartingDate.GetDay(),0,0,0);
		bNeedToRefreshSelected=TRUE;
		bNeedToRefreshList=TRUE;

		for( nCont=0; nCont<nBlocksSelected; nCont++ )
		{
			lpItem = (typeBlockDetail *)m_cSelected.GetItemData(nCont);
			if( lpItem->StartingDate==PrevInitialDate )
				lpItem->StartingDate=m_dInicialDate;
		}
	}

	if( m_dEndingDate!=pdl->m_pMain->m_dEndingDate )
	{
		COleDateTime PrevEndingDate = m_dEndingDate;

		m_dEndingDate.SetDateTime(pdl->m_pMain->m_dEndingDate.GetYear(),pdl->m_pMain->m_dEndingDate.GetMonth(),pdl->m_pMain->m_dEndingDate.GetDay(),0,0,0);
		bNeedToRefreshSelected=TRUE;

		for( nCont=0; nCont<nBlocksSelected; nCont++ )
		{
			lpItem = (typeBlockDetail *)m_cSelected.GetItemData(nCont);
			if( lpItem->EndingDate==PrevEndingDate )
				lpItem->EndingDate=m_dEndingDate;
		}
	}

	if( bNeedToRefreshSelected )
	{
		CString strTemp;

		for( nCont=0; nCont<nBlocksSelected; nCont++ )
		{
			lpItem = (typeBlockDetail *)m_cSelected.GetItemData(nCont);
			strTemp.Format("%d-%d-%d a %d-%d-%d",lpItem->StartingDate.GetYear(),
													lpItem->StartingDate.GetMonth(),
													lpItem->StartingDate.GetDay(),
													lpItem->EndingDate.GetYear(),
													lpItem->EndingDate.GetMonth(),
													lpItem->EndingDate.GetDay() );
			m_cSelected.SetItemText(nCont,3,strTemp);
		}
	}

	if( bNeedToRefreshList )
		AfxBeginThread(FillBlocksList,(LPVOID)this);

	CheckData();

	return TRUE;
}

UINT CScheduleBlocks::FillBlocksList( LPVOID lp )
{
	CScheduleBlocks *pThis=(CScheduleBlocks *)lp;
	
	if( pThis->m_bIsWorking )
		return 0;

	pThis->m_bIsWorking=TRUE;

	CRSRadioStations rsRadio( g_strMainConnect );
	rsRadio.m_strFilter.Format("ID = '%d'",pThis->m_lStationID);
	rsRadio.Open();
	pThis->m_strConnect=rsRadio.m_DSN;
	rsRadio.Close();
	pThis->m_strConnect.TrimRight();
		
	CRSBlocksDefinition rsBlocksDef( pThis->m_strConnect );
	CRSViewBlocksStatusOnSpots rsStatus( pThis->m_strConnect );
	long	Pos=0;
	CString	strDate;

	strDate.Format("%d-%d-%d",pThis->m_dInicialDate.GetYear(),pThis->m_dInicialDate.GetMonth(),pThis->m_dInicialDate.GetDay());

	rsBlocksDef.m_strFilter = "Activ = 1";
	rsBlocksDef.m_strSort = "Time";
	rsBlocksDef.Open();

	while( !rsBlocksDef.IsEOF() )
	{
		rsBlocksDef.m_Name.TrimRight();
		pThis->m_cBlocks.InsertItem(Pos,rsBlocksDef.m_Name);
		pThis->m_cBlocks.SetItemData(Pos,rsBlocksDef.m_ID);

		rsStatus.m_strFilter.Format("BlockID = '%d' AND BlockDate='%s'",rsBlocksDef.m_ID,strDate);
		if( rsStatus.IsOpen() )
			rsStatus.Requery();
		else
			rsStatus.Open();

		if( rsStatus.GetRecordCount() )
		{
			CString strTemp;

			strTemp.Format("%d",rsStatus.m_nSpots);
			pThis->m_cBlocks.SetItemText(Pos,1,strTemp);

			GetTimeString(rsStatus.m_SpotsLength,&strTemp);
			strTemp.Delete(0,3);
			strTemp.Delete(5,4);
			pThis->m_cBlocks.SetItemText(Pos,2,strTemp);
		}
		
		rsBlocksDef.MoveNext();
		Pos++;
	}
	if( rsStatus.IsOpen() )
		rsStatus.Close();

	rsBlocksDef.Close();
	
	pThis->m_bIsWorking=FALSE;
	pThis->CheckData();

	return TRUE;
}

BOOL CScheduleBlocks::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString strTemp;
	int		Pos=0;

	m_cBlocks.SetImageList(g_ilTree,LVSIL_SMALL);
	m_cSelected.SetImageList(g_ilTree,LVSIL_SMALL);

	strTemp.LoadString(IDS_BLOCKS);
	m_cBlocks.InsertColumn(0,strTemp,LVCFMT_LEFT,300);

	strTemp.LoadString(IDS_SPOTSNUMBER);
	m_cBlocks.InsertColumn(1,strTemp,LVCFMT_CENTER,100);

	strTemp.LoadString(IDS_SPOTSLENGTH);
	m_cBlocks.InsertColumn(2,strTemp,LVCFMT_CENTER,100);

	strTemp.LoadString(IDS_SELECTEDBLOCKS);
	m_cSelected.InsertColumn(0,strTemp,LVCFMT_LEFT,200);

	strTemp.LoadString(IDS_POSITION);
	m_cSelected.InsertColumn(1,strTemp,LVCFMT_CENTER,100);

	strTemp.LoadString(IDS_AIRINGDAYS);
	m_cSelected.InsertColumn(2,strTemp,LVCFMT_CENTER,100);

	strTemp.LoadString(IDS_AIRINGPERIOD);
	m_cSelected.InsertColumn(3,strTemp,LVCFMT_CENTER,100);

	if( !m_bIsNew )
	{
		AfxBeginThread(FillBlocksList,(LPVOID)this);

		CRSViewTrafficScheduleBlocks rs(m_strConnect);
		typeBlockDetail *lpItem;
		long	Pos;
		long	Hour,Min,Sec;
		ldiv_t result;
		CString	str,
				strDays[7];

		strDays[0].LoadString(IDS_SUN);
		strDays[1].LoadString(IDS_MON);
		strDays[2].LoadString(IDS_TUE);
		strDays[3].LoadString(IDS_WED);
		strDays[4].LoadString(IDS_THU);
		strDays[5].LoadString(IDS_FRI);
		strDays[6].LoadString(IDS_SAT);;

		rs.m_strFilter.Format("ScheduleID = %d",m_lScheduleID);
		rs.m_strSort="Time";
		rs.Open();
		while( !rs.IsEOF() )
		{
			result = ldiv(rs.m_Time,3600000);
			Hour=result.quot;
			result = ldiv(result.rem,60000);
			Min=result.quot;
			result = ldiv(result.rem,1000);
			Sec=result.quot;

			rs.m_Name.TrimRight();
			lpItem = new typeBlockDetail;

			lpItem->Days[0]		=rs.m_Sun;
			lpItem->Days[1]		=rs.m_Mon;
			lpItem->Days[2]		=rs.m_Tue;
			lpItem->Days[3]		=rs.m_Wed;
			lpItem->Days[4]		= rs.m_Thu;
			lpItem->Days[5]		= rs.m_Fri;
			lpItem->Days[6]		= rs.m_Sat;
			lpItem->EndingDate	= rs.m_EndingDate;
			lpItem->ID			= rs.m_BlockID;
			lpItem->Position	= rs.m_Position;
			lpItem->StartingDate= rs.m_StartingDate;
			lpItem->TimeOffset	= COleDateTimeSpan(0,Hour,Min,Sec);

			Pos=m_cSelected.GetItemCount();

			m_cSelected.InsertItem(Pos,rs.m_Name,3);
			m_cSelected.SetItemData(Pos,(DWORD)lpItem);

			if( lpItem->Position < 150 )
				str.Format("%d",lpItem->Position);
			else if( lpItem->Position > 200 )
				str.Format("%d",200-lpItem->Position);
			else
				str.LoadString(IDS_BLOCK);
			m_cSelected.SetItemText(Pos,1,str);

			str="";
			for( int i=0; i<7; i++ )
				if( lpItem->Days[i] ) str+=strDays[i]+" ";
			m_cSelected.SetItemText(Pos,2,str);

			str.Format("%d-%d-%d a %d-%d-%d",lpItem->StartingDate.GetYear(),
											lpItem->StartingDate.GetMonth(),
											lpItem->StartingDate.GetDay(),
											lpItem->EndingDate.GetYear(),
											lpItem->EndingDate.GetMonth(),
											lpItem->EndingDate.GetDay() );
			m_cSelected.SetItemText(Pos,3,str);

			rs.MoveNext();
		}
		rs.Close();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScheduleBlocks::OnDblclkBlocks(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	long Pos = m_cBlocks.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1 ) 
		return;

	CScheduleBlockDetail dlg;
	CString str=m_cBlocks.GetItemText(Pos,0);
	
	dlg.m_strName=str;
	dlg.m_bSun = TRUE;
	dlg.m_bMon = TRUE;
	dlg.m_bTue = TRUE;
	dlg.m_bWed = TRUE;
	dlg.m_bThu = TRUE;
	dlg.m_bFri = TRUE;
	dlg.m_bSat = TRUE;
	dlg.m_dStartingDate = m_dInicialDate;
	dlg.m_dEndingDate = m_dEndingDate;
	dlg.m_strConnect = m_strConnect;
	dlg.m_lBlockID = m_cBlocks.GetItemData(Pos);

	if( dlg.DoModal()==IDOK )
	{
		CString strDays[7];
		strDays[0].LoadString(IDS_SUN);
		strDays[1].LoadString(IDS_MON);
		strDays[2].LoadString(IDS_TUE);
		strDays[3].LoadString(IDS_WED);
		strDays[4].LoadString(IDS_THU);
		strDays[5].LoadString(IDS_FRI);
		strDays[6].LoadString(IDS_SAT);

		typeBlockDetail *lpItem = new typeBlockDetail;
		lpItem->ID			= dlg.m_lBlockID;
		lpItem->Days[0]		= dlg.m_bSun;
		lpItem->Days[1]		= dlg.m_bMon;
		lpItem->Days[2]		= dlg.m_bTue;
		lpItem->Days[3]		= dlg.m_bWed;
		lpItem->Days[4]		= dlg.m_bThu;
		lpItem->Days[5]		= dlg.m_bFri;
		lpItem->Days[6]		= dlg.m_bSat;
		lpItem->StartingDate.SetDateTime(dlg.m_dStartingDate.GetYear(),dlg.m_dStartingDate.GetMonth(),dlg.m_dStartingDate.GetDay(),0,0,0);
		lpItem->EndingDate.SetDateTime(dlg.m_dEndingDate.GetYear(),dlg.m_dEndingDate.GetMonth(),dlg.m_dEndingDate.GetDay(),0,0,0);
		lpItem->TimeOffset	= dlg.m_TimeOffset;
		lpItem->Position	= dlg.m_lPosition;

		Pos=m_cSelected.GetNextItem(-1,LVNI_SELECTED);
		if( Pos==-1 )
			Pos=m_cSelected.GetItemCount();

		m_cSelected.InsertItem(Pos,str,3);
		m_cSelected.SetItemData(Pos,(DWORD)lpItem);

		if( lpItem->Position < 150 )
			str.Format("%d",lpItem->Position);
		else if( lpItem->Position > 200 )
			str.Format("%d",200-lpItem->Position);
		else
			str.LoadString(IDS_BLOCK);
		m_cSelected.SetItemText(Pos,1,str);

		str="";
		for( int i=0; i<7; i++ )
			if( lpItem->Days[i] ) str+=strDays[i]+" ";
		m_cSelected.SetItemText(Pos,2,str);

		str.Format("%d-%d-%d a %d-%d-%d",dlg.m_dStartingDate.GetYear(),
											dlg.m_dStartingDate.GetMonth(),
											dlg.m_dStartingDate.GetDay(),
											dlg.m_dEndingDate.GetYear(),
											dlg.m_dEndingDate.GetMonth(),
											dlg.m_dEndingDate.GetDay() );
		m_cSelected.SetItemText(Pos,3,str);
		CheckData();
	}
}

LRESULT CScheduleBlocks::OnWizardNext() 
{
	m_nBlocks=m_cSelected.GetItemCount();
	
	for( int i=0; i<m_nBlocks; i++ )
		m_blocks[i]=(typeBlockDetail *)m_cSelected.GetItemData(i);

	return CPropertyPage::OnWizardNext();
}

void CScheduleBlocks::CheckData()
{
	if( (m_cSelected.GetItemCount()) && (!m_bIsWorking) )
		((CPropertySheet *)GetParent())->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	else
		((CPropertySheet *)GetParent())->SetWizardButtons(PSWIZB_BACK);
}

BOOL CScheduleBlocks::OnWizardFinish() 
{
	m_nBlocks=m_cSelected.GetItemCount();
	
	for( int i=0; i<m_nBlocks; i++ )
		m_blocks[i]=(typeBlockDetail *)m_cSelected.GetItemData(i);

	
	return CPropertyPage::OnWizardFinish();
}

void CScheduleBlocks::OnRemove() 
{
	int Pos=m_cSelected.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1) 
		return;

	m_cSelected.DeleteItem(Pos);
	CheckData();	
}

void CScheduleBlocks::OnDblclkSelected(NMHDR* pNMHDR, LRESULT* pResult) 
{
	long Pos = m_cSelected.GetNextItem(-1,LVNI_SELECTED);
	if( Pos==-1 ) 
		return;

	CScheduleBlockDetail dlg;
	CString str=m_cSelected.GetItemText(Pos,0);
	typeBlockDetail *lpItem=(typeBlockDetail *)m_cSelected.GetItemData(Pos);
	
	dlg.m_strName=str;
	dlg.m_bSun = lpItem->Days[0];
	dlg.m_bMon = lpItem->Days[1];
	dlg.m_bTue = lpItem->Days[2];
	dlg.m_bWed = lpItem->Days[3];
	dlg.m_bThu = lpItem->Days[4];
	dlg.m_bFri = lpItem->Days[5];
	dlg.m_bSat = lpItem->Days[6];
	dlg.m_dStartingDate = lpItem->StartingDate;
	dlg.m_dEndingDate = lpItem->EndingDate;
	dlg.m_strConnect = m_strConnect;
	dlg.m_lBlockID = lpItem->ID;

	if( dlg.DoModal()==IDOK )
	{	
		CString str;
		CString strDays[7];

		strDays[0].LoadString(IDS_SUN);
		strDays[1].LoadString(IDS_MON);
		strDays[2].LoadString(IDS_TUE);
		strDays[3].LoadString(IDS_WED);
		strDays[4].LoadString(IDS_THU);
		strDays[5].LoadString(IDS_FRI);
		strDays[6].LoadString(IDS_SAT);

		lpItem->Days[0] = dlg.m_bSun;
		lpItem->Days[1] = dlg.m_bMon;
		lpItem->Days[2] = dlg.m_bTue;
		lpItem->Days[3] = dlg.m_bWed;
		lpItem->Days[4] = dlg.m_bThu;
		lpItem->Days[5] = dlg.m_bFri;
		lpItem->Days[6] = dlg.m_bSat;
		lpItem->StartingDate = dlg.m_dStartingDate;
		lpItem->EndingDate = dlg.m_dEndingDate;
		lpItem->Position = dlg.m_lPosition;

		if( lpItem->Position < 150 )
			str.Format("%d",lpItem->Position);
		else if( lpItem->Position > 200 )
			str.Format("%d",200-lpItem->Position);
		else
			str.LoadString(IDS_BLOCK);
		m_cSelected.SetItemText(Pos,1,str);

		str="";
		for( int i=0; i<7; i++ )
			if( lpItem->Days[i] ) str+=strDays[i]+" ";
		m_cSelected.SetItemText(Pos,2,str);

		str.Format("%d-%d-%d a %d-%d-%d",dlg.m_dStartingDate.GetYear(),
											dlg.m_dStartingDate.GetMonth(),
											dlg.m_dStartingDate.GetDay(),
											dlg.m_dEndingDate.GetYear(),
											dlg.m_dEndingDate.GetMonth(),
											dlg.m_dEndingDate.GetDay() );
		m_cSelected.SetItemText(Pos,3,str);
	}
	
	*pResult = 0;
}
