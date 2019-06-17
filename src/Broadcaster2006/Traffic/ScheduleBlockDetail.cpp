// ScheduleBlockDetail.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "ScheduleBlockDetail.h"
#include "TrafficExternals.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\include\rsBlocksDefinition.h"
#include "..\include\RSBlocksComposition.h"
#include "..\include\RSViewSpotPeriodOnTraffic.h"
#include "..\include\RSViewJinglesSmallList.h"
#include "..\include\RSViewTrafficDetails.h"
#include "..\include\RSViewRms.h"
#include "..\include\RSViewTimeSignal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CImageList *g_ilTree;

/////////////////////////////////////////////////////////////////////////////
// CScheduleBlockDetail dialog


CScheduleBlockDetail::CScheduleBlockDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CScheduleBlockDetail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScheduleBlockDetail)
	m_dEndingDate = COleDateTime::GetCurrentTime();
	m_bFri = FALSE;
	m_bMon = FALSE;
	m_strName = _T("");
	m_bSat = FALSE;
	m_dStartingDate = COleDateTime::GetCurrentTime();
	m_bSun = FALSE;
	m_bThu = FALSE;
	m_bTue = FALSE;
	m_bWed = FALSE;
	//}}AFX_DATA_INIT
}


void CScheduleBlockDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScheduleBlockDetail)
	DDX_Control(pDX, IDC_WED, m_cWed);
	DDX_Control(pDX, IDC_TUE, m_cTue);
	DDX_Control(pDX, IDC_THU, m_cThu);
	DDX_Control(pDX, IDC_SUN, m_cSun);
	DDX_Control(pDX, IDC_SAT, m_cSat);
	DDX_Control(pDX, IDC_MON, m_cMon);
	DDX_Control(pDX, IDC_FRI, m_cFri);
	DDX_Control(pDX, IDC_ENDINGDATE, m_cEndingDate);
	DDX_Control(pDX, IDC_BLOCKTREE, m_cTree);
	DDX_DateTimeCtrl(pDX, IDC_ENDINGDATE, m_dEndingDate);
	DDX_Check(pDX, IDC_FRI, m_bFri);
	DDX_Check(pDX, IDC_MON, m_bMon);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Check(pDX, IDC_SAT, m_bSat);
	DDX_DateTimeCtrl(pDX, IDC_STARTINGDATE, m_dStartingDate);
	DDX_Check(pDX, IDC_SUN, m_bSun);
	DDX_Check(pDX, IDC_THU, m_bThu);
	DDX_Check(pDX, IDC_TUE, m_bTue);
	DDX_Check(pDX, IDC_WED, m_bWed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScheduleBlockDetail, CDialog)
	//{{AFX_MSG_MAP(CScheduleBlockDetail)
	ON_NOTIFY(NM_KILLFOCUS, IDC_STARTINGDATE, OnKillfocusStartingdate)
	ON_NOTIFY(NM_KILLFOCUS, IDC_ENDINGDATE, OnKillfocusEndingdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleBlockDetail message handlers

BOOL CScheduleBlockDetail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRSBlocksDefinition		rsBlockDef(m_strConnect);
	rsBlockDef.m_strFilter.Format("ID = %d",m_lBlockID);
	rsBlockDef.Open();

	if( !rsBlockDef.m_Sun )
	{
		m_cSun.EnableWindow(FALSE);
		m_bSun=FALSE;
	}

	if( !rsBlockDef.m_Mon )
	{
		m_cMon.EnableWindow(FALSE);
		m_bMon=FALSE;
	}

	if( !rsBlockDef.m_Tue )
	{
		m_cTue.EnableWindow(FALSE);
		m_bTue=FALSE;
	}

	if( !rsBlockDef.m_Wed )
	{
		m_cWed.EnableWindow(FALSE);
		m_bWed=FALSE;
	}

	if( !rsBlockDef.m_Thu )
	{
		m_cThu.EnableWindow(FALSE);
		m_bThu=FALSE;
	}

	if( !rsBlockDef.m_Fry )
	{
		m_cFri.EnableWindow(FALSE);
		m_bFri=FALSE;
	}

	if( !rsBlockDef.m_Sat )
	{
		m_cSat.EnableWindow(FALSE);
		m_bSat=FALSE;
	}
	UpdateData(FALSE);

	m_cTree.SetImageList(g_ilTree,TVSIL_NORMAL);
	long Styles=GetWindowLong(m_cTree.m_hWnd,GWL_STYLE);
	SetWindowLong(m_cTree.m_hWnd,GWL_STYLE,Styles|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT);

	long Hour,Min,Sec;
	ldiv_t result;
	
	result = ldiv(rsBlockDef.m_Time,3600000);
	Hour=result.quot;
	result = ldiv(result.rem,60000);
	Min=result.quot;
	result = ldiv(result.rem,1000);
	Sec=result.quot;

	m_TimeOffset = COleDateTimeSpan(0,Hour,Min,Sec);

	GetBlock();

	return TRUE; 
}

void CScheduleBlockDetail::GetBlock()
{
	UpdateData();
	m_cTree.DeleteAllItems();

	CRSBlocksComposition	rsBlockComp(m_strConnect);
	CRSViewTrafficDetails	rsTraffic(m_strConnect);
	CRSViewJinglesSmallList	rsJingles(g_strMainConnect);
	CRSViewRms				rsRms( g_strMainConnect );
	CRSViewTimeSignal		rsTime( g_strMainConnect );

	HTREEITEM	hItem,
				hItem2;
	CString		strDate,
				strBlock,
				strEmptySlot,
				strTimeSignal;
	int			iPos=1;

	strTimeSignal.LoadString(IDS_TIMESIGNAL);

	strDate.Format("EndingDate>='%d-%d-%d' and StartingDate<='%d-%d-%d 23:59:59'",
		m_dStartingDate.GetYear(),m_dStartingDate.GetMonth(),m_dStartingDate.GetDay(),
		m_dEndingDate.GetYear(),m_dEndingDate.GetMonth(),m_dEndingDate.GetDay() );

	strEmptySlot.LoadString(IDS_EMPTYSLOT);
	strBlock.LoadString(IDS_BLOCK);

	rsBlockComp.m_strFilter.Format("ID = %d AND %s",m_lBlockID,strDate);
	rsBlockComp.m_strSort="Position";
	rsBlockComp.Open();
	
	while( !rsBlockComp.IsEOF() )
	{
		switch( rsBlockComp.m_ItemType )
		{
		case TYPE_JINGLE:
			rsJingles.m_strFilter.Format("ID = %d",rsBlockComp.m_ItemID);
			if( rsJingles.IsOpen() )
				rsJingles.Requery();
			else
				rsJingles.Open();
			if( rsJingles.GetRecordCount() )
			{
				rsJingles.m_Jingle.TrimRight();
				hItem=m_cTree.InsertItem(rsJingles.m_Jingle,4,4);
				m_cTree.SetItemData(hItem,0);
				m_cTree.SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
			}
			break;

		case TYPE_RM:
			rsRms.m_strFilter.Format("ID = %d",rsBlockComp.m_ItemID);
			if( rsRms.IsOpen() )
				rsRms.Requery();
			else
				rsRms.Open();

			if( rsRms.GetRecordCount() )
			{
				rsRms.m_Name.TrimRight();
				rsRms.m_Type.TrimRight();
				hItem=m_cTree.InsertItem(rsRms.m_Type+" - "+rsRms.m_Name,9,9);
				m_cTree.SetItemData(hItem,0);
				m_cTree.SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
			}
			break;

		case TYPE_TIMESIGNAL:
			rsTime.m_strFilter.Format("ID = %d",rsBlockComp.m_ItemID);

			if( rsTime.IsOpen() )
				rsTime.Requery();
			else
				rsTime.Open();

			if( rsTime.GetRecordCount() )
			{
				rsTime.m_Name.TrimRight();
				hItem=m_cTree.InsertItem(rsTime.m_Name+" - "+strTimeSignal,3,3);

				m_cTree.SetItemData(hItem,0);
				m_cTree.SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
			}
			break;

		case TYPE_SPOT:
			strDate.Format("BlockDate >= '%d-%d-%d' AND BlockDate <= '%d-%d-%d 23:59:59'",
				m_dStartingDate.GetYear(),m_dStartingDate.GetMonth(),m_dStartingDate.GetDay(),
				m_dEndingDate.GetYear(),m_dEndingDate.GetMonth(),m_dEndingDate.GetDay() );

			rsTraffic.m_strFilter.Format("%s AND BlockID = %d AND Position = %d",strDate,m_lBlockID,iPos);
			if( rsTraffic.IsOpen() )
				rsTraffic.Requery();
			else
				rsTraffic.Open();

			if( rsTraffic.GetRecordCount() )
			{
				rsTraffic.m_SpotName.TrimRight();
				rsTraffic.m_CustomerName.TrimRight();
				hItem=m_cTree.InsertItem(rsTraffic.m_CustomerName+" - "+rsTraffic.m_SpotName,1,1);
				m_cTree.SetItemData(hItem,0);
				m_cTree.SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
			}
			else
			{
				hItem=m_cTree.InsertItem(strEmptySlot,1,1);
				m_cTree.SetItemData(hItem,iPos);
			}
			iPos++;
			break;

		case TYPE_BLOCK:
			strDate.Format("BlockDate = '%d-%d-%d'",
				m_dStartingDate.GetYear(),m_dStartingDate.GetMonth(),m_dStartingDate.GetDay() );

			rsTraffic.m_strFilter.Format("%s AND BlockID = %d AND Position = 150",strDate,m_lBlockID);
			if( rsTraffic.IsOpen() )
				rsTraffic.Requery();
			else
				rsTraffic.Open();

			hItem=m_cTree.InsertItem(strBlock,0,0);
			m_cTree.SetItemData(hItem,150);
			while( !rsTraffic.IsEOF() )
			{
				rsTraffic.m_SpotName.TrimRight();
				rsTraffic.m_CustomerName.TrimRight();
				hItem2=m_cTree.InsertItem(rsTraffic.m_CustomerName+" - "+rsTraffic.m_SpotName,1,1,hItem);
				m_cTree.SetItemData(hItem2,150);
				m_cTree.SetItemState(hItem2,TVIS_BOLD,TVIS_BOLD);
				rsTraffic.MoveNext();
			}
			iPos=201;
			break;
		default:
			m_cTree.InsertItem("",2,0);
			break;
		}
		rsBlockComp.MoveNext();
	}
}

void CScheduleBlockDetail::OnOK() 
{
	UpdateData();

	if( (!m_bSun) && (!m_bMon) && (!m_bTue) && (!m_bWed) && (!m_bThu) && (!m_bFri) && (!m_bSat) )
		return;

	if( m_dStartingDate > m_dEndingDate )
		return;

	HTREEITEM hItem=m_cTree.GetSelectedItem();
	if( hItem==NULL )
		return;

	m_lPosition=m_cTree.GetItemData(hItem);
	if( m_lPosition==0 )
		return;
	
	CDialog::OnOK();
}

void CScheduleBlockDetail::OnDatetimechangeStartingdate(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	GetBlock();
	
	*pResult = 0;
}

void CScheduleBlockDetail::OnDatetimechangeEndingdate(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	GetBlock();
	
	*pResult = 0;
}

void CScheduleBlockDetail::OnKillfocusStartingdate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	GetBlock();
	
	*pResult = 0;
}

void CScheduleBlockDetail::OnKillfocusEndingdate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	GetBlock();
	
	*pResult = 0;
}
