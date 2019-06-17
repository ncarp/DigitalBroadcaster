// TrafficManagmentLeftView.cpp : implementation file
//

#include "stdafx.h"
#include "Traffic.h"
#include "TrafficManagmentLeftView.h"
#include "Customer.h"
#include "SheduleDlg.h"
#include "Spot.h"
#include "..\include\RSViewSpotsList.h"
#include "..\include\RSTrafficScheduleDefinition.h"
#include "..\include\RSViewTrafficSchedule.h"
#include "..\include\RSViewCustomersFull.h"
#include "..\include\RSScheduleDefinition.h"
#include "..\include\RSScheduleBlocks.h"
#include "..\include\RSScheduleSpots.h"
#include "..\include\RSTraffic.h"
#include "..\include\RSSpots.h"
#include "..\include\RSViewSpotsFull.h"
#include "..\include\RSCustomer.h"
#include "..\include\RSRadioStations.h"
#include "TrafficExternals.h"
#include "..\OnAir\OnAirDefines.h"
#include "..\OnAir\PFLWnd.h"
#include "..\hasp\hasp.h"
#include "..\include\haspcode.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPFLWnd *g_wndPFL;

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentLeftView

IMPLEMENT_DYNCREATE(CTrafficManagmentLeftView, CDigitalLeftView)

CTrafficManagmentLeftView::CTrafficManagmentLeftView()
{
	m_bIsRefreshing=FALSE;
}

CTrafficManagmentLeftView::~CTrafficManagmentLeftView()
{
}


BEGIN_MESSAGE_MAP(CTrafficManagmentLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CTrafficManagmentLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentLeftView drawing

void CTrafficManagmentLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentLeftView diagnostics

#ifdef _DEBUG
void CTrafficManagmentLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CTrafficManagmentLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTrafficManagmentLeftView message handlers

void CTrafficManagmentLeftView::OnInitialUpdate() 
{
	m_pDocument->SetTitle("Gestão de publicidade");
	
	AfxBeginThread(RefreshList,(LPVOID)this);
}

UINT CTrafficManagmentLeftView::RefreshList(LPVOID lp)
{
	CTrafficManagmentLeftView *pThis = (CTrafficManagmentLeftView *)lp;
	CTreeCtrl *pTree = &pThis->GetTreeCtrl();

	pThis->m_bIsRefreshing=TRUE;

	CString		strPrevCustomer="",
				strSchedule,
				str;
	HTREEITEM	hCustomer,
				hSpot,
				hScheduleRoot,
				hSchedule;
	LPtypeTreeItem lpItem;

	strSchedule.LoadString(IDS_TRAFFICSCHEDULE);
	CRSViewSpotsList			 rs( g_strMainConnect);
	CRSTrafficScheduleDefinition rsTraffic(g_strMainConnect);

	rs.m_strSort="CustomerName, Name";
	rs.Open();
	
	rsTraffic.m_strSort="StartingDate";
	
	while( !rs.IsEOF() )
	{
		if( rs.m_CustomerName!= strPrevCustomer )
		{
			strPrevCustomer = rs.m_CustomerName;
			rs.m_CustomerName.TrimRight();
			
			lpItem = new typeTreeItem;
			lpItem->wType = TYPE_CUSTOMER;
			lpItem->lID = rs.m_CustomerID;

			hCustomer = pTree->InsertItem(rs.m_CustomerName,0,0);
			pTree->SetItemData(hCustomer,(DWORD)lpItem);
			pTree->SetItemState(hCustomer,TVIS_BOLD,TVIS_BOLD);

			hScheduleRoot = pTree->InsertItem(strSchedule,2,2,hCustomer);
			pTree->SetItemState(hScheduleRoot,TVIS_BOLD,TVIS_BOLD);
			pTree->SetItemData(hScheduleRoot,0);

			rsTraffic.m_strFilter.Format("CustomerID = '%d'",rs.m_CustomerID);
			if( rsTraffic.IsOpen() )
				rsTraffic.Requery();
			else
				rsTraffic.Open();
			
			while( !rsTraffic.IsEOF() )
			{
				str.Format(IDS_FORMAT_FROMTO,
						rsTraffic.m_StartingDate.year,rsTraffic.m_StartingDate.month,rsTraffic.m_StartingDate.day,
						rsTraffic.m_EndingDate.year,rsTraffic.m_EndingDate.month,rsTraffic.m_EndingDate.day);
				hSchedule = pTree->InsertItem(str,3,3,hScheduleRoot);

				lpItem = new typeTreeItem;
				lpItem->lID = rsTraffic.m_ID;
				lpItem->wType = TYPE_TRAFFICSCHEDULE;
				pTree->SetItemData(hSchedule,(DWORD)lpItem);

				rsTraffic.MoveNext();
			}
		}
		rs.m_Name.TrimRight();
		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_SPOT;

		hSpot = pTree->InsertItem(rs.m_Name,1,1,hCustomer);
		pTree->SetItemData(hSpot,(DWORD)lpItem);

		rs.MoveNext();
	}

	rs.Close();
	pThis->m_bIsRefreshing=FALSE;

	return 0;
}

void CTrafficManagmentLeftView::OnSelChange()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
	{
		strURL.Format("%s\\EmptyPage.asp",g_strBaseURL);
		SetView(strURL);
		return;
	}

	switch( lpItem->wType )
	{
	case TYPE_CUSTOMER:
		strURL.Format("%s\\Customer.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(strURL);
		break;
	case TYPE_SPOT:
		strURL.Format("%s\\Spot.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(strURL);
		break;
	case TYPE_TRAFFICSCHEDULE:
		if( !g_Permissions.bTrafficView )
			break;
		strURL.Format("%s\\TrafficSchedule.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(strURL);
		break;
	default:
		strURL.Format("%s\\EmptyPage.asp",g_strBaseURL);
		SetView(strURL);
		break;
	}
}	

void CTrafficManagmentLeftView::OnDoubleClick()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	switch( lpItem->wType )
	{
	case TYPE_CUSTOMER:
		EditCustomer();
		break;
	case TYPE_SPOT:
		EditSpot();
		break;
	case TYPE_TRAFFICSCHEDULE:
		EditSchedule();
		break;
		
	default:
		break;
	}
}	

void CTrafficManagmentLeftView::OnCut() 
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	if( lpItem==NULL )
		return;

	switch( lpItem->wType )
	{
	case TYPE_CUSTOMER:
		CutCustomer();
		break;
	case TYPE_SPOT:
		CutSpot();
		break;
	case TYPE_TRAFFICSCHEDULE:
		CutSchedule();
		break;
		
	default:
		break;
	}
}

void CTrafficManagmentLeftView::CutCustomer()
{
	if( !g_Permissions.bSpotsCut )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	CRSSpots	rs(g_strMainConnect);
	rs.m_strFilter.Format("CustomerID = '%d' AND Activ = 1",lpItem->lID);
	rs.Open();

	if( rs.GetRecordCount() )
		AfxMessageBox(IDS_CANTDELETECUSTOMER);
	else
	{
		if( AfxMessageBox(IDS_CONFIRMCUSTOMERREMOVE,MB_YESNO)==IDYES )
		{
			CString strSQL;

			strSQL.Format("UPDATE Customers SET Activ = 0 WHERE ID = %d",lpItem->lID);
			rs.m_pDatabase->ExecuteSQL(strSQL);
			
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUT,TYPE_CUSTOMER,lpItem->lID);

			pTree->DeleteItem(hItem);
		}
	}
	rs.Close();
}

void CTrafficManagmentLeftView::CutSpot()
{
	if( !g_Permissions.bSpotsCut )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	
	if( AfxMessageBox(IDS_CONFIRMSPOTREMOVE,MB_YESNO)==IDYES )
	{
		CString		strSQL;
		CDatabase	db;
		CRSRadioStations rs(g_strMainConnect);
		rs.Open();

		strSQL.Format("UPDATE Spots SET Activ = 0 WHERE ID = %d",lpItem->lID);
		rs.m_pDatabase->ExecuteSQL(strSQL);

		strSQL.Format("DELETE FROM TrafficScheduleSpots WHERE SpotID = %d",lpItem->lID);
		rs.m_pDatabase->ExecuteSQL(strSQL);

		while( !rs.IsEOF() )
		{
			rs.m_DSN.TrimRight();
			db.Open(rs.m_DSN);

			strSQL.Format("DELETE FROM Sponsors WHERE SpotID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM Traffic WHERE SpotID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);

			db.Close();
			rs.MoveNext();
		}
		rs.Close();
		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUT,TYPE_SPOT,lpItem->lID);

		pTree->DeleteItem(hItem);
	}
}

void CTrafficManagmentLeftView::CutSchedule()
{
	if( !g_Permissions.bTrafficCut )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	
	if( AfxMessageBox(IDS_CONFIRMSCHEDULEREMOVE,MB_YESNO)==IDYES )
	{
		CString strDSN,
				strSQL;
		long	lStationID=0;

		CRSViewTrafficSchedule rs(g_strMainConnect);
		
		rs.m_strFilter.Format("ID = %d",lpItem->lID);
		rs.Open();
		if( rs.GetRecordCount() )
		{
			lStationID=rs.m_StationID;
			rs.m_DSN.TrimRight();
			strDSN = rs.m_DSN;
			rs.Close();

			CDatabase db;

			db.Open(strDSN);

			strSQL.Format("DELETE FROM Traffic WHERE ScheduleID = '%d' AND Aired = 0",lpItem->lID);
			db.SetQueryTimeout(120);
			db.ExecuteSQL(strSQL);
			db.Close();

			db.Open(g_strMainConnect);

			strSQL.Format("DELETE FROM TrafficScheduleDefinition WHERE ID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM TrafficScheduleBlocks WHERE ScheduleID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM TrafficScheduleSpots WHERE ScheduleID = %d",lpItem->lID);
			db.ExecuteSQL(strSQL);
						
			db.Close();
		}
		else
			rs.Close();

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_TRAFFICSCHEDULE,lpItem->lID,lStationID);

		pTree->DeleteItem(hItem);
	}
}

void CTrafficManagmentLeftView::NewSpot()
{
	if( !g_Permissions.bSpotsAdd )
		return;

	int	par1,par2,par3,par4;

	if( HASP_HASPPROTECTION && HASP_WORKSTATION)
	{
		if( HASP_TIMEKEY )
			hasp(78,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else if( HASP_4 )
			hasp(6,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else
		{
			hasp(5,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
			if( par3!=0 )
				par3=0;
			else
				par3=-1;
		}
		if( (par3!=0) || ((par1!=HASP_IDLOW) && (HASP_IDLOW!=0)) || ((par2!=HASP_IDHIGH) && (HASP_IDHIGH!=0)) )
		{
			return;
		}
	}

	CSpot	dl;

	if( dl.DoModal()==IDOK )
	{
		CString strSQL;
		CRSSpots rs(g_strMainConnect);
		rs.m_strSort="ID Desc";
		rs.m_strFilter.Format("CustomerID = %d",dl.m_CustomerID);
		rs.Open();
		rs.AddNew();
		rs.m_Activ=1;
		rs.m_AgencyID	= dl.m_AgencyID;
		rs.m_CustomerID	= dl.m_CustomerID;
		rs.m_FileName	= dl.m_FileName;
		rs.m_Finish		= dl.m_pTimers->m_pTimer->m_End;
		rs.m_MainVoiceID= dl.m_VoiceID;
		rs.m_Mix		= dl.m_pTimers->m_pTimer->m_Mix;
		rs.m_Name		= dl.m_Name;
		rs.m_Obs		= dl.m_OBS;
		rs.m_PathID		= dl.m_PathID;
		rs.m_Ready		= 1;
		rs.m_Start		= dl.m_pTimers->m_pTimer->m_Start;
		rs.m_TypeOfBusinessID = dl.m_BusinessID;
		rs.Update();

		rs.Requery();

		strSQL.Format("UPDATE Customers SET Activ=1 WHERE ID=%d",dl.m_CustomerID);
		rs.m_pDatabase->ExecuteSQL(strSQL);

		CTreeCtrl		*pTree=&GetTreeCtrl();
		HTREEITEM		hCustomer= FindString(dl.m_Customer),
						hSpot;
		typeTreeItem	*lpItem;

		if( hCustomer==NULL )
		{
			HTREEITEM	hSchedule;
			CString		strTemp;
			
			strTemp.LoadString(IDS_TRAFFICSCHEDULE);
			lpItem = new typeTreeItem;
			lpItem->lID=dl.m_CustomerID;
			lpItem->wType=TYPE_CUSTOMER;

			hCustomer = pTree->InsertItem(dl.m_Customer,0,0);
			pTree->SetItemData(hCustomer,(DWORD)lpItem);
			pTree->SetItemState(hCustomer,TVIS_BOLD,TVIS_BOLD);

			hSchedule = pTree->InsertItem(strTemp,2,2,hCustomer);
			pTree->SetItemData(hSchedule,0);
			pTree->SetItemState(hSchedule,TVIS_BOLD,TVIS_BOLD);

			pTree->SortChildren(NULL);
		}
		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_SPOT;

		hSpot = pTree->InsertItem(dl.m_Name,1,1,hCustomer);
		pTree->SetItemData(hSpot,(DWORD)lpItem);
		pTree->SortChildren(hCustomer);
		pTree->EnsureVisible(hSpot);

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_SPOT,lpItem->lID);
	}
}

void CTrafficManagmentLeftView::EditSpot()
{
	if( !g_Permissions.bSpotsEdit )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);

	CRSViewSpotsFull rs(g_strMainConnect );
	rs.m_strFilter.Format("ID = %d",lpItem->lID);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		CSpot dl;
		
		rs.m_Name.TrimRight();
		rs.m_CustomerName.TrimRight();
		rs.m_BusinessName.TrimRight();
		rs.m_AgencyName.TrimRight();
		rs.m_VoiceName.TrimRight();
		rs.m_FileName.TrimRight();
		rs.m_Path.TrimRight();

		dl.m_Customer		= rs.m_CustomerName;
		dl.m_CustomerID		= rs.m_CustomerID;
		dl.m_Name			= rs.m_Name;
		dl.m_Business		= rs.m_BusinessName;
		dl.m_BusinessID		= rs.m_TypeOfBusinessID;
		dl.m_Agency			= rs.m_AgencyName;
		dl.m_AgencyID		= rs.m_AgencyID;
		dl.m_Voice			= rs.m_VoiceName;
		dl.m_VoiceID		= rs.m_MainVoiceID;
		dl.m_Path			= rs.m_Path;
		dl.m_PathID			= rs.m_PathID;
		dl.m_FileName		= rs.m_FileName;
		dl.m_OBS			= rs.m_Obs;
		dl.m_Start			= rs.m_Start;
		dl.m_Mix			= rs.m_Mix;
		dl.m_End			= rs.m_Finish;
		dl.m_IsNew			= FALSE;
		dl.m_nStandardLength = rs.m_StandardLength;

		rs.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSSpots rsSpots(g_strMainConnect);
			rsSpots.m_strSort="ID Desc";
			rsSpots.m_strFilter.Format("ID = %d",lpItem->lID);
			rsSpots.Open();

			if( rsSpots.GetRecordCount() )
			{
				CString strSQL;

				rsSpots.Edit();
				rsSpots.m_Activ			=1;
				rsSpots.m_AgencyID		= dl.m_AgencyID;
				rsSpots.m_CustomerID	= dl.m_CustomerID;
				rsSpots.m_FileName		= dl.m_FileName;
				rsSpots.m_Finish		= dl.m_pTimers->m_pTimer->m_End;
				rsSpots.m_MainVoiceID	= dl.m_VoiceID;
				rsSpots.m_Mix			= dl.m_pTimers->m_pTimer->m_Mix;
				rsSpots.m_Name			= dl.m_Name;
				rsSpots.m_Obs			= dl.m_OBS;
				rsSpots.m_PathID		= dl.m_PathID;
				rsSpots.m_Ready			= 1;
				rsSpots.m_Start			= dl.m_pTimers->m_pTimer->m_Start;
				rsSpots.m_TypeOfBusinessID = dl.m_BusinessID;
				rsSpots.m_StLength = dl.m_nStandardLength;
				rsSpots.Update();
				pTree->SetItemText(hItem,dl.m_Name);

				strSQL.Format("UPDATE Customers SET Activ=1 WHERE ID=%d",dl.m_CustomerID);
				rsSpots.m_pDatabase->ExecuteSQL(strSQL);
			}
			rs.Close();

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_SPOT,lpItem->lID);
		}
	}
	else
		rs.Close();
}

void CTrafficManagmentLeftView::EditCustomer()
{
	if( !g_Permissions.bSpotsEdit )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CRSViewCustomersFull rs(g_strMainConnect);

	rs.m_strFilter.Format("ID = '%d'",lpItem->lID);
	rs.Open();

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}
	
	rs.m_Adress.TrimRight();
	rs.m_Agency.TrimRight();
	rs.m_Business.TrimRight();
	rs.m_Contact.TrimRight();
	rs.m_eMail.TrimRight();
	rs.m_Fax.TrimRight();
	rs.m_nc.TrimRight();
	rs.m_Name.TrimRight();
	rs.m_Obs.TrimRight();
	rs.m_Phone.TrimRight();
	rs.m_Salesperson.TrimRight();
	rs.m_www.TrimRight();
	rs.m_ZIP.TrimRight();
	rs.m_NC2.TrimRight();
	rs.m_Name2.TrimRight();
	rs.m_Number.TrimRight();
	rs.m_CelPhone.TrimRight();
	
	CCustomer dlg;

	dlg.m_strAdress		= rs.m_Adress;
	dlg.m_strAgency		= rs.m_Agency;
	dlg.m_strBusiness	= rs.m_Business;
	dlg.m_strContact	= rs.m_Contact;
	dlg.m_stremail		= rs.m_eMail;
	dlg.m_strFax		= rs.m_Fax;
	dlg.m_strFN			= rs.m_nc;
	dlg.m_strName		= rs.m_Name;
	dlg.m_strOBS		= rs.m_Obs;
	dlg.m_strPhone		= rs.m_Phone;
	dlg.m_strSales		= rs.m_Salesperson;
	dlg.m_strWWW		= rs.m_www;
	dlg.m_strZIP		= rs.m_ZIP;
	dlg.m_CustomerID	= rs.m_ID;
	dlg.m_AgencyID		= rs.m_AgencyID;
	dlg.m_BusinessID	= rs.m_BusinessTypeID;
	dlg.m_SalesID		= rs.m_SalespersonID;
	dlg.m_strNumber		= rs.m_Number;
	dlg.m_strName2		= rs.m_Name2;
	dlg.m_strNC2		= rs.m_NC2;
	dlg.m_strCelPhone	= rs.m_CelPhone;

	rs.Close();
	if( dlg.DoModal()==IDOK )
	{
		CRSCustomer	rs(g_strMainConnect);
		rs.m_strFilter.Format("ID = '%d'",dlg.m_CustomerID);
		rs.Open();

		if( rs.GetRecordCount() )
		{
			rs.Edit();
			rs.m_Activ			= 1;
			rs.m_Adress			= dlg.m_strAdress;
			rs.m_AgencyID		= dlg.m_AgencyID;
			rs.m_BusinessTypeID	= dlg.m_BusinessID;
			rs.m_Contact		= dlg.m_strContact;
			rs.m_eMail			= dlg.m_stremail;
			rs.m_Fax			= dlg.m_strFax;
			rs.m_Name			= dlg.m_strName;
			rs.m_nc				= dlg.m_strFN;
			rs.m_Obs			= dlg.m_strOBS;
			rs.m_Phone			= dlg.m_strPhone;
			rs.m_SalespersonID	= dlg.m_SalesID;
			rs.m_www			= dlg.m_strWWW;
			rs.m_ZIP			= dlg.m_strZIP;
			rs.m_Number			= dlg.m_strNumber;
			rs.m_Name2			= dlg.m_strName2;
			rs.m_NC2			= dlg.m_strNC2;
			rs.m_CelPhone		= dlg.m_strCelPhone;
			rs.Update();
			rs.Close();
			pTree->SetItemText(hItem,dlg.m_strName);
		}
		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,dlg.m_CustomerID);
	}
}

void CTrafficManagmentLeftView::EditSchedule()
{
	if( !g_Permissions.bTrafficEdit )
		return;

	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CRSViewTrafficSchedule rs(g_strMainConnect);

	rs.m_strFilter.Format("ID = %d",lpItem->lID );
	rs.Open();

	if( rs.GetRecordCount() )
	{
		CSheduleDlg dl(IDS_TRAFFICSCHEDULE,this,0);
		CScheduleMain	*pMain=dl.m_pMain;
		CScheduleSpots	*pSpots=dl.m_pSpots;
		CScheduleBlocks *pBlocks=dl.m_pBlocks;

		rs.m_CustomerName.TrimRight();
		rs.m_DSN.TrimRight();
		rs.m_RadioName.TrimRight();

		pSpots->m_bIsNew		= FALSE;
		pSpots->m_lScheduleID	= rs.m_ID;
		pSpots->m_lCustomerID	= rs.m_CustomerID;
		pSpots->m_dEndingDate.SetDateTime( rs.m_EndingDate.GetYear(),rs.m_EndingDate.GetMonth(),rs.m_EndingDate.GetDay(),0,0,0);
		pSpots->m_dStartingDate.SetDateTime( rs.m_StartingDate.GetYear(),rs.m_StartingDate.GetMonth(),rs.m_StartingDate.GetDay(),0,0,0);	

		pBlocks->m_bIsNew		= FALSE;
		pBlocks->m_lScheduleID	= rs.m_ID;
		pBlocks->m_strConnect	= rs.m_DSN;
		pBlocks->m_lStationID	= rs.m_StationID;
		pBlocks->m_dEndingDate.SetDateTime( rs.m_EndingDate.GetYear(),rs.m_EndingDate.GetMonth(),rs.m_EndingDate.GetDay(),0,0,0);
		pBlocks->m_dInicialDate.SetDateTime( rs.m_StartingDate.GetYear(),rs.m_StartingDate.GetMonth(),rs.m_StartingDate.GetDay(),0,0,0);	

		if( rs.m_StartingDate < COleDateTime::GetCurrentTime() )
			rs.m_StartingDate = COleDateTime::GetCurrentTime();

		pMain->m_bByNumber		= rs.m_Type != 0;
		pMain->m_bTotalValue	= rs.m_TypeOfValue== 0;
		pMain->m_bIsNew			= FALSE;
		pMain->m_dEndingDate.SetDate(rs.m_EndingDate.GetYear(),rs.m_EndingDate.GetMonth(),rs.m_EndingDate.GetDay() );
		pMain->m_dFinalHour.SetTime(rs.m_EndingDate.GetHour(),rs.m_EndingDate.GetMinute(),rs.m_EndingDate.GetSecond() );
		pMain->m_dStartingDate.SetDate(rs.m_StartingDate.GetYear(),rs.m_StartingDate.GetMonth(),rs.m_StartingDate.GetDay() );
		pMain->m_dStartingHour.SetTime(rs.m_StartingDate.GetHour(),rs.m_StartingDate.GetMinute(),rs.m_StartingDate.GetSecond() );
		pMain->m_fValue		= rs.m_Value;
		pMain->m_iNumber	= rs.m_Insertions;
		pMain->m_lCustomerID= rs.m_CustomerID;
		pMain->m_lStationID	= rs.m_StationID;
		pMain->m_strCustomer= rs.m_CustomerName;
		pMain->m_strStation	= rs.m_RadioName;
		pMain->m_lScheduleID = rs.m_ID;
		pMain->m_strPI		= rs.m_DRM35;

		if( dl.DoModal()==ID_WIZFINISH ) 
		{
			CRSScheduleDefinition	rsDef( g_strMainConnect );
			CRSScheduleBlocks		rsBlocks(g_strMainConnect);
			CRSScheduleSpots		rsSpots(g_strMainConnect);

			rsDef.m_strFilter.Format("ID = %d",pMain->m_lScheduleID);
			rsDef.Open();

			if( rsDef.GetRecordCount()!=0 )
			{
				///////////////////////////////////////////////////////////////
				//	Delete old data
				CDatabase	db;
				CString		strSQL;

				db.Open(g_strMainConnect);

				strSQL.Format("DELETE FROM TrafficScheduleBlocks WHERE ScheduleID = '%d'",pMain->m_lScheduleID);
				db.ExecuteSQL(strSQL);
			
				strSQL.Format("DELETE FROM TrafficScheduleSpots WHERE ScheduleID = '%d'",pMain->m_lScheduleID);
				db.ExecuteSQL(strSQL);

				db.Close();
				db.Open(pBlocks->m_strConnect);

				strSQL.Format("Delete FROM Traffic WHERE ScheduleID = '%d' and Aired=0",pMain->m_lScheduleID);
				db.SetQueryTimeout(120);
				db.ExecuteSQL(strSQL);
				db.Close();

				//////////////////////////////////////////////////////////////////
				//	Main data
				int		Cont;

				rsDef.Edit();

				rsDef.m_CustomerID	= pMain->m_lCustomerID;

				rsDef.m_EndingDate.SetDateTime( pMain->m_dEndingDate.GetYear(),
						pMain->m_dEndingDate.GetMonth(),
						pMain->m_dEndingDate.GetDay(),
						pMain->m_dFinalHour.GetHour(),
						pMain->m_dFinalHour.GetMinute(),
						pMain->m_dFinalHour.GetSecond() );

				rsDef.m_StartingDate.SetDateTime(pMain->m_dStartingDate.GetYear(),
						pMain->m_dStartingDate.GetMonth(),
						pMain->m_dStartingDate.GetDay(),
						pMain->m_dStartingHour.GetHour(),
						pMain->m_dStartingHour.GetMinute(),
						pMain->m_dStartingHour.GetSecond() );

				rsDef.m_Insertions	= pMain->m_iNumber;
				rsDef.m_StationID	= pMain->m_lStationID;
				rsDef.m_Suspend		= 0;
				rsDef.m_Type		= (pMain->m_bByNumber==0) ? 0 : 1;
				rsDef.m_TypeOfValue = (pMain->m_bTotalValue) ? 0 : 1;
				rsDef.m_Value		= pMain->m_fValue;
				rsDef.m_DRM35		= pMain->m_strPI;

				rsDef.Update();

				rsBlocks.m_strFilter.Format("ScheduleID = %d",pMain->m_lScheduleID);
				rsBlocks.Open();

				for( Cont=0; Cont<pBlocks->m_nBlocks; Cont++ )
				{
					rsBlocks.AddNew();
					rsBlocks.m_BlockID		= pBlocks->m_blocks[Cont]->ID;
					rsBlocks.m_ScheduleID	= pMain->m_lScheduleID;
					rsBlocks.m_Sun			= pBlocks->m_blocks[Cont]->Days[0];
					rsBlocks.m_Mon			= pBlocks->m_blocks[Cont]->Days[1];
					rsBlocks.m_Tue			= pBlocks->m_blocks[Cont]->Days[2];
					rsBlocks.m_Wed			= pBlocks->m_blocks[Cont]->Days[3];
					rsBlocks.m_Thu			= pBlocks->m_blocks[Cont]->Days[4];
					rsBlocks.m_Fri			= pBlocks->m_blocks[Cont]->Days[5];
					rsBlocks.m_Sat			= pBlocks->m_blocks[Cont]->Days[6];
					rsBlocks.m_StationID	= pMain->m_lStationID;
					rsBlocks.m_Position		= pBlocks->m_blocks[Cont]->Position;

					rsBlocks.m_StartingDate.SetDateTime(pBlocks->m_blocks[Cont]->StartingDate.GetYear(),
										pBlocks->m_blocks[Cont]->StartingDate.GetMonth(),
										pBlocks->m_blocks[Cont]->StartingDate.GetDay(),
										0,0,0);
					rsBlocks.m_EndingDate.SetDateTime(pBlocks->m_blocks[Cont]->EndingDate.GetYear(),
										pBlocks->m_blocks[Cont]->EndingDate.GetMonth(),
										pBlocks->m_blocks[Cont]->EndingDate.GetDay(),
										0,0,0);

					rsBlocks.m_Value		= 0;
					rsBlocks.Update();
				}
				rsBlocks.Close();

				rsSpots.m_strFilter.Format("ScheduleID = %d",pMain->m_lScheduleID);
				rsSpots.Open();

				for( Cont=0; Cont<pSpots->m_nSpots; Cont++ )
				{
					rsSpots.AddNew();

					rsSpots.m_ScheduleID	= pMain->m_lScheduleID;
					rsSpots.m_Position		= Cont;
					rsSpots.m_EndingDate.SetDateTime(pSpots->m_Spots[Cont]->EndingDate.GetYear(),
										pSpots->m_Spots[Cont]->EndingDate.GetMonth(),
										pSpots->m_Spots[Cont]->EndingDate.GetDay(),
										0,0,0);
					rsSpots.m_StartingDate.SetDateTime(pSpots->m_Spots[Cont]->StartingDate.GetYear(),
										pSpots->m_Spots[Cont]->StartingDate.GetMonth(),
										pSpots->m_Spots[Cont]->StartingDate.GetDay(),
										0,0,0);
					rsSpots.m_SpotID		= pSpots->m_Spots[Cont]->ID;
					rsSpots.m_Sun			= pSpots->m_Spots[Cont]->Days[0];
					rsSpots.m_Mon			= pSpots->m_Spots[Cont]->Days[1];
					rsSpots.m_Tue			= pSpots->m_Spots[Cont]->Days[2];
					rsSpots.m_Wed			= pSpots->m_Spots[Cont]->Days[3];
					rsSpots.m_Thu			= pSpots->m_Spots[Cont]->Days[4];
					rsSpots.m_Fri			= pSpots->m_Spots[Cont]->Days[5];
					rsSpots.m_Sat			= pSpots->m_Spots[Cont]->Days[6];
					
					rsSpots.Update();
				}
				rsSpots.Close();
		
				long	nInserts=0,
						MaxInserts;
				float	fTotalValue=0.0f;

				COleDateTimeSpan OneDay(1,0,0,0);
				COleDateTime	StartingDate,
								EndingDate,
								TempDate,
								CurrentDate,
								BlockDate;

				StartingDate.SetDateTime(pMain->m_dStartingDate.GetYear(),
								pMain->m_dStartingDate.GetMonth(),
								pMain->m_dStartingDate.GetDay(),
								pMain->m_dStartingHour.GetHour(),
								pMain->m_dStartingHour.GetMinute(),
								pMain->m_dStartingHour.GetSecond() );

				if( pMain->m_bByNumber )
				{
					EndingDate=COleDateTime(2500,12,31,0,0,0);
					MaxInserts=pMain->m_iNumber;
				}
				else
				{
					EndingDate.SetDateTime(pMain->m_dEndingDate.GetYear(),
								pMain->m_dEndingDate.GetMonth(),
								pMain->m_dEndingDate.GetDay(),
								pMain->m_dFinalHour.GetHour(),
								pMain->m_dFinalHour.GetMinute(),
								pMain->m_dFinalHour.GetSecond() );
					MaxInserts=999999;
				}

				CurrentDate.SetDateTime(pMain->m_dStartingDate.GetYear(),
								pMain->m_dStartingDate.GetMonth(),
								pMain->m_dStartingDate.GetDay(),
								0,0,0 );
	
				int nAnterior=0;
				int nSpot=0;
				CString strDates;

				CRSTraffic rsTraffic(pBlocks->m_strConnect);
				rsTraffic.m_strFilter="ScheduleID = 0";
				rsTraffic.Open();
		
				while( (CurrentDate<EndingDate) && (nInserts<MaxInserts) )
				{
					for( Cont=0; Cont<pBlocks->m_nBlocks; Cont++ )
					{
						BlockDate = CurrentDate + pBlocks->m_blocks[Cont]->TimeOffset;

						strDates.Format("nStarting - %s\nEnding %s\nTemp %s\nBlock %s\nCurrent %s",
						
					StartingDate.Format(),
					EndingDate.Format(),
					TempDate.Format(),
					BlockDate.Format(),
					CurrentDate.Format() );

//				AfxMessageBox(strDates);

						if( (pBlocks->m_blocks[Cont]->Days[CurrentDate.GetDayOfWeek()-1]) && 
							(pBlocks->m_blocks[Cont]->StartingDate <= CurrentDate ) && 
							(pBlocks->m_blocks[Cont]->EndingDate >= CurrentDate ) &&
							(BlockDate >= StartingDate ) && (BlockDate <= EndingDate) )
						{
							nAnterior=nSpot;
							do
							{
								nSpot++;
								if( nSpot>=pSpots->m_nSpots )
									nSpot=0;
							} while( (nSpot!=nAnterior) && 
								!( (pSpots->m_Spots[nSpot]->Days[CurrentDate.GetDayOfWeek()-1]) && (pSpots->m_Spots[nSpot]->StartingDate<=CurrentDate) && (pSpots->m_Spots[nSpot]->EndingDate>=CurrentDate) ) );
					
							if( (pSpots->m_Spots[nSpot]->Days[CurrentDate.GetDayOfWeek()-1]) && (pSpots->m_Spots[nSpot]->StartingDate<=CurrentDate) && (pSpots->m_Spots[nSpot]->EndingDate>=CurrentDate ) )
							{
								// Bingo
								rsTraffic.AddNew();
								rsTraffic.m_BlockDate.SetDateTime(BlockDate.GetYear(),BlockDate.GetMonth(),BlockDate.GetDay(),0,0,0);
								rsTraffic.m_BlockID		= pBlocks->m_blocks[Cont]->ID;
								rsTraffic.m_Position	= pBlocks->m_blocks[Cont]->Position;
								rsTraffic.m_ScheduleID	= pMain->m_lScheduleID;
								rsTraffic.m_SpotID		= pSpots->m_Spots[nSpot]->ID;
								rsTraffic.m_Suspend		= 0;
								rsTraffic.m_Aired		= 0;
								rsTraffic.Update();

								nInserts++;
							}
						}
						if( nInserts>=MaxInserts )
							break;
					}
					CurrentDate+=OneDay;
				} 
				float		fInsertValue = (dl.m_pMain->m_bTotalValue) ? (float)dl.m_pMain->m_fValue/(float)nInserts : dl.m_pMain->m_fValue;

				strSQL.Format("UPDATE Traffic SET Value = '%4.6f' WHERE ScheduleID = '%d'",fInsertValue,pMain->m_lScheduleID);
				db.Open(dl.m_pBlocks->m_strConnect);
				db.SetQueryTimeout(240);
				db.ExecuteSQL(strSQL);
				db.Close();

				WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_TRAFFICSCHEDULE,pMain->m_lScheduleID,pMain->m_lStationID);
			}

			CString str;

			str.Format(IDS_FORMAT_FROMTO,
					rsDef.m_StartingDate.GetYear(),rsDef.m_StartingDate.GetMonth(),rsDef.m_StartingDate.GetDay(),
					rsDef.m_EndingDate.GetYear(),rsDef.m_EndingDate.GetMonth(),rsDef.m_EndingDate.GetDay() );
				
			pTree->SetItemText(hItem,str);
				
			rsDef.Close();
		}
		
	}
	rs.Close();
}

void CTrafficManagmentLeftView::NewSchedule()
{
	if( !g_Permissions.bTrafficAdd )
		return;

	int	par1,par2,par3,par4;

	if( HASP_HASPPROTECTION && HASP_WORKSTATION)
	{
		if( HASP_TIMEKEY )
			hasp(78,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else if( HASP_4 )
			hasp(6,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else
		{
			hasp(5,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
			if( par3!=0 )
				par3=0;
			else
				par3=-1;
		}
		if( (par3!=0) || ((par1!=HASP_IDLOW) && (HASP_IDLOW!=0)) || ((par2!=HASP_IDHIGH) && (HASP_IDHIGH!=0)) )
		{
			return;
		}
	}

	CSheduleDlg dl(IDS_TRAFFICSCHEDULE,this,0);

	dl.m_pMain->m_dStartingHour.SetTime(0,0,0);
	dl.m_pMain->m_dFinalHour.SetTime(23,59,59);

	if( dl.DoModal()==ID_WIZFINISH )
	{
		int		Cont;
		long	CaleID;
		CRSScheduleDefinition	rsDef(g_strMainConnect);
		CRSScheduleBlocks		rsBlocks(g_strMainConnect);
		CRSScheduleSpots		rsSpots(g_strMainConnect);
		CScheduleBlocks			*pBlocks=dl.m_pBlocks;
		CScheduleSpots			*pSpots=dl.m_pSpots;

		rsDef.m_strSort="ID DESC";

		rsDef.m_strFilter.Format("CustomerID = '%d' AND StationID='%d'",
			dl.m_pMain->m_lCustomerID,
			dl.m_pMain->m_lStationID );

		rsDef.Open();

		rsDef.AddNew();
		rsDef.m_CustomerID	= dl.m_pMain->m_lCustomerID;

		rsDef.m_EndingDate.SetDateTime( dl.m_pMain->m_dEndingDate.GetYear(),
						dl.m_pMain->m_dEndingDate.GetMonth(),
						dl.m_pMain->m_dEndingDate.GetDay(),
						dl.m_pMain->m_dFinalHour.GetHour(),
						dl.m_pMain->m_dFinalHour.GetMinute(),
						dl.m_pMain->m_dFinalHour.GetSecond() );

		rsDef.m_StartingDate.SetDateTime(dl.m_pMain->m_dStartingDate.GetYear(),
						dl.m_pMain->m_dStartingDate.GetMonth(),
						dl.m_pMain->m_dStartingDate.GetDay(),
						dl.m_pMain->m_dStartingHour.GetHour(),
						dl.m_pMain->m_dStartingHour.GetMinute(),
						dl.m_pMain->m_dStartingHour.GetSecond() );

		rsDef.m_Insertions	= dl.m_pMain->m_iNumber;
		rsDef.m_StationID	= dl.m_pMain->m_lStationID;
		rsDef.m_Suspend		= 0;
		rsDef.m_Type		= (dl.m_pMain->m_bByNumber) ? 1 : 0;
		rsDef.m_TypeOfValue = (dl.m_pMain->m_bTotalValue) ? 0 : 1;
		rsDef.m_Value		= dl.m_pMain->m_fValue;
		rsDef.m_DRM35		= dl.m_pMain->m_strPI;

		rsDef.Update();
		rsDef.Requery();

		CaleID=rsDef.m_ID;
		

		rsBlocks.m_strFilter.Format("ScheduleID = %d",CaleID);
		rsBlocks.Open();

		for( Cont=0; Cont<dl.m_pBlocks->m_nBlocks; Cont++ )
		{
			rsBlocks.AddNew();
			rsBlocks.m_BlockID		= dl.m_pBlocks->m_blocks[Cont]->ID;
			rsBlocks.m_ScheduleID	= CaleID;
			rsBlocks.m_Sun			= dl.m_pBlocks->m_blocks[Cont]->Days[0];
			rsBlocks.m_Mon			= dl.m_pBlocks->m_blocks[Cont]->Days[1];
			rsBlocks.m_Tue			= dl.m_pBlocks->m_blocks[Cont]->Days[2];
			rsBlocks.m_Wed			= dl.m_pBlocks->m_blocks[Cont]->Days[3];
			rsBlocks.m_Thu			= dl.m_pBlocks->m_blocks[Cont]->Days[4];
			rsBlocks.m_Fri			= dl.m_pBlocks->m_blocks[Cont]->Days[5];
			rsBlocks.m_Sat			= dl.m_pBlocks->m_blocks[Cont]->Days[6];
			rsBlocks.m_StationID	= dl.m_pMain->m_lStationID;
			rsBlocks.m_Position		= dl.m_pBlocks->m_blocks[Cont]->Position;

			rsBlocks.m_StartingDate.SetDateTime(dl.m_pBlocks->m_blocks[Cont]->StartingDate.GetYear(),
										dl.m_pBlocks->m_blocks[Cont]->StartingDate.GetMonth(),
										dl.m_pBlocks->m_blocks[Cont]->StartingDate.GetDay(),
										0,0,0);
			rsBlocks.m_EndingDate.SetDateTime(dl.m_pBlocks->m_blocks[Cont]->EndingDate.GetYear(),
										dl.m_pBlocks->m_blocks[Cont]->EndingDate.GetMonth(),
										dl.m_pBlocks->m_blocks[Cont]->EndingDate.GetDay(),
										0,0,0);

			rsBlocks.m_Value		= 0;
			rsBlocks.Update();
		}
		rsBlocks.Close();

		rsSpots.m_strFilter.Format("ScheduleID = %d",0);
		rsSpots.Open();
		for( Cont=0; Cont<dl.m_pSpots->m_nSpots; Cont++ )
		{
			rsSpots.AddNew();

			rsSpots.m_ScheduleID	= CaleID;
			rsSpots.m_Position		= Cont;
			rsSpots.m_EndingDate.SetDateTime(dl.m_pSpots->m_Spots[Cont]->EndingDate.GetYear(),
										dl.m_pSpots->m_Spots[Cont]->EndingDate.GetMonth(),
										dl.m_pSpots->m_Spots[Cont]->EndingDate.GetDay(),
										0,0,0);
			rsSpots.m_StartingDate.SetDateTime(dl.m_pSpots->m_Spots[Cont]->StartingDate.GetYear(),
										dl.m_pSpots->m_Spots[Cont]->StartingDate.GetMonth(),
										dl.m_pSpots->m_Spots[Cont]->StartingDate.GetDay(),
										0,0,0);
			rsSpots.m_SpotID		= dl.m_pSpots->m_Spots[Cont]->ID;
			rsSpots.m_Sun			= dl.m_pSpots->m_Spots[Cont]->Days[0];
			rsSpots.m_Mon			= dl.m_pSpots->m_Spots[Cont]->Days[1];
			rsSpots.m_Tue			= dl.m_pSpots->m_Spots[Cont]->Days[2];
			rsSpots.m_Wed			= dl.m_pSpots->m_Spots[Cont]->Days[3];
			rsSpots.m_Thu			= dl.m_pSpots->m_Spots[Cont]->Days[4];
			rsSpots.m_Fri			= dl.m_pSpots->m_Spots[Cont]->Days[5];
			rsSpots.m_Sat			= dl.m_pSpots->m_Spots[Cont]->Days[6];
					
			rsSpots.Update();
		}
		rsSpots.Close();
		
		long	nInserts=0,
				MaxInserts;
		float	fTotalValue=0.0f;

		COleDateTimeSpan OneDay(1,0,0,0);
		COleDateTime	StartingDate,
						EndingDate,
						TempDate,
						BlockDate,
						CurrentDate;	// DataActual contem a meia noite de cada dia;

		StartingDate.SetDateTime(dl.m_pMain->m_dStartingDate.GetYear(),
								dl.m_pMain->m_dStartingDate.GetMonth(),
								dl.m_pMain->m_dStartingDate.GetDay(),
								dl.m_pMain->m_dStartingHour.GetHour(),
								dl.m_pMain->m_dStartingHour.GetMinute(),
								dl.m_pMain->m_dStartingHour.GetSecond() );

		if( dl.m_pMain->m_bByNumber )
		{
			EndingDate=COleDateTime(2500,12,31,0,0,0);
			MaxInserts=dl.m_pMain->m_iNumber;
		}
		else
		{
			EndingDate.SetDateTime(dl.m_pMain->m_dEndingDate.GetYear(),
								dl.m_pMain->m_dEndingDate.GetMonth(),
								dl.m_pMain->m_dEndingDate.GetDay(),
								dl.m_pMain->m_dFinalHour.GetHour(),
								dl.m_pMain->m_dFinalHour.GetMinute(),
								dl.m_pMain->m_dFinalHour.GetSecond() );
			MaxInserts=999999;
		}

		CurrentDate.SetDateTime(dl.m_pMain->m_dStartingDate.GetYear(),
								dl.m_pMain->m_dStartingDate.GetMonth(),
								dl.m_pMain->m_dStartingDate.GetDay(),
								0,0,0 );
	
		int nAnterior=0;
		int nSpot=0;

		CRSTraffic rsTraffic(dl.m_pBlocks->m_strConnect);
		rsTraffic.m_strFilter="ScheduleID = 0";
		rsTraffic.Open();
		CString strDates;
		
		while( (CurrentDate<EndingDate) && (nInserts<MaxInserts) )
		{
			for( Cont=0; Cont<dl.m_pBlocks->m_nBlocks; Cont++ )
			{
				BlockDate = CurrentDate + pBlocks->m_blocks[Cont]->TimeOffset;
				
				strDates.Format("Starting - %s\nEnding %s\nTemp %s\nBlock %s\nCurrent %s",
					StartingDate.Format(),
					EndingDate.Format(),
					TempDate.Format(),
					BlockDate.Format(),
					CurrentDate.Format() );

		//		AfxMessageBox(strDates);

				if( (pBlocks->m_blocks[Cont]->Days[CurrentDate.GetDayOfWeek()-1]) && 
					(pBlocks->m_blocks[Cont]->StartingDate <= CurrentDate ) && 
					(pBlocks->m_blocks[Cont]->EndingDate >= CurrentDate ) &&
					(BlockDate >= StartingDate ) && (BlockDate <= EndingDate) )
				{
					nAnterior=nSpot;
					do
					{
						nSpot++;
						if( nSpot>=pSpots->m_nSpots )
							nSpot=0;
					} while( (nSpot!=nAnterior) && 
						!( (pSpots->m_Spots[nSpot]->Days[CurrentDate.GetDayOfWeek()-1]) && (pSpots->m_Spots[nSpot]->StartingDate<=CurrentDate) && (pSpots->m_Spots[nSpot]->EndingDate>=CurrentDate) ) );
				
					if( (pSpots->m_Spots[nSpot]->Days[CurrentDate.GetDayOfWeek()-1]) && (pSpots->m_Spots[nSpot]->StartingDate<=CurrentDate) && (pSpots->m_Spots[nSpot]->EndingDate>=CurrentDate ) )
					{
						// Bingo
						rsTraffic.AddNew();
						rsTraffic.m_BlockDate.SetDateTime(BlockDate.GetYear(),BlockDate.GetMonth(),BlockDate.GetDay(),0,0,0 );
						rsTraffic.m_BlockID		= dl.m_pBlocks->m_blocks[Cont]->ID;
						rsTraffic.m_Position	= dl.m_pBlocks->m_blocks[Cont]->Position;
						rsTraffic.m_ScheduleID	= CaleID;
						rsTraffic.m_SpotID		= dl.m_pSpots->m_Spots[nSpot]->ID;
						rsTraffic.m_Suspend		= 0;
						rsTraffic.m_Aired		= 0;
						
						rsTraffic.Update();
						nInserts++;
					}
				}
				if( nInserts>=MaxInserts )
					break;
			}
			CurrentDate+=OneDay;
		} 

		CDatabase	db;
		CString		strSQL;
		float		fInsertValue = (dl.m_pMain->m_bTotalValue) ? dl.m_pMain->m_fValue/nInserts : dl.m_pMain->m_fValue;

		strSQL.Format("UPDATE Traffic SET Value = '%4.2f' WHERE ScheduleID = '%d'",fInsertValue,CaleID);
		db.Open(dl.m_pBlocks->m_strConnect);
		db.SetQueryTimeout(240);
		db.ExecuteSQL(strSQL);
		db.Close();
		
		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_TRAFFICSCHEDULE,CaleID,dl.m_pMain->m_lStationID);

		HTREEITEM	hCustomer=FindString(dl.m_pMain->m_strCustomer);
		if( hCustomer!=NULL )
		{
			CTreeCtrl		*pTree=&GetTreeCtrl();
			HTREEITEM		hRoot = pTree->GetChildItem(hCustomer);
			typeTreeItem	*lpItem = (typeTreeItem *)pTree->GetItemData(hRoot);

			while( (lpItem!=NULL) && (hRoot!=NULL) )
				hRoot = pTree->GetNextItem(hRoot,TVGN_NEXT);

			if( hRoot!=NULL )
			{
				HTREEITEM hNew;
				CString str;
		
				str.Format(IDS_FORMAT_FROMTO,
					rsDef.m_StartingDate.GetYear(),rsDef.m_StartingDate.GetMonth(),rsDef.m_StartingDate.GetDay(),
					rsDef.m_EndingDate.GetYear(),rsDef.m_EndingDate.GetMonth(),rsDef.m_EndingDate.GetDay() );
				
				lpItem = new typeTreeItem;
				lpItem->lID = rsDef.m_ID;
				lpItem->wType=TYPE_TRAFFICSCHEDULE;

				hNew = pTree->InsertItem(str,3,3,hRoot);
				pTree->SetItemData(hNew,(DWORD)lpItem);
				
			}
		}
		rsDef.Close();

		
	}
}
	
void CTrafficManagmentLeftView::PFL()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
		return;
	
	if( lpItem->wType!=TYPE_SPOT )
		return;

	g_wndPFL->SetSound(TYPE_SPOT,lpItem->lID);
	g_wndPFL->RestoreWindow();
}

void CTrafficManagmentLeftView::OnRDoubleClick()
{
	PFL();
}