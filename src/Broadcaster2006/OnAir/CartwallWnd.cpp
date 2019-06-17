// CartwallWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "CartwallWnd.h"
#include "ExternalObjects.h"
#include "OnAirDefines.h"
#include "OnAirUtils.h"
#include "NewCartwall.h"
#include "OpenCartwall.h"
#include "..\common\include\defines.h"
#include "..\include\CartwallComponents.h"
#include "..\include\RSCartwallDefinition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCartwallWnd

IMPLEMENT_DYNCREATE(CCartwallWnd, CFrameWnd)

CCartwallWnd::CCartwallWnd()
{
	m_strCartName = "";
}

CCartwallWnd::~CCartwallWnd()
{
}


BEGIN_MESSAGE_MAP(CCartwallWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CCartwallWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYUP()
	ON_WM_SYSCOMMAND()
	ON_WM_SYSKEYUP()
	ON_COMMAND( CM_NEW, OnNew )
	ON_COMMAND( CM_SAVE, OnSave )
	ON_COMMAND( CM_LOAD, OnLoad )
	ON_MESSAGE( UM_PLAYCART, OnPlayCart )
	ON_MESSAGE( UM_STOPALL, OnStopAll )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCartwallWnd message handlers

LRESULT CCartwallWnd::OnPlayCart(WPARAM nChar,LPARAM)
{
	SHORT State = GetKeyState(VK_CAPITAL);

	if( State & 0x0001 )
		m_pList->m_Carts[nChar+12]->Play();
	else
		m_pList->m_Carts[nChar]->Play();

	return 0;
}

int CCartwallWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);

	CRect	crect;
	GetClientRect( &crect );

	TBBUTTON	buttons[5];
	buttons[0].iBitmap=7;
	buttons[0].idCommand=CM_NEW;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=7;

	buttons[1].iBitmap=8;
	buttons[1].idCommand=CM_LOAD;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=8;

	buttons[2].iBitmap=9;
	buttons[2].idCommand=CM_SAVE;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=9;

	m_pToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	m_pToolBar->SetButtonSize(size);
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(3,buttons);
	m_pToolBar->AutoSize();

	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);

	crect.DeflateRect(2,2,2,40);
	m_pList=new CCartwallList();
	m_pList->Create(NULL,NULL,WS_VISIBLE|WS_VSCROLL|WS_CLIPCHILDREN,crect,this,0);
	return 0;
}


void CCartwallWnd::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
//_pToolBar->AutoSize();	
}

LRESULT CCartwallWnd::OnStopAll(WPARAM,LPARAM)
{
	for( int iCont=0; iCont<50; iCont++ )
		m_pList->m_Carts[iCont]->Stop();

	return 0;
}

void CCartwallWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )	
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCartwallWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
}

void CCartwallWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CCartwallWnd::OnNew()
{
	if( AfxMessageBox(IDS_CONFIRMNEWCARTWALL,MB_YESNO)==IDYES )
	{
		for( int iCont=0; iCont<50; iCont++ )
			m_pList->m_Carts[iCont]->OnCut();
	}
	m_strCartName="";
}

void CCartwallWnd::OnLoad()
{
	COpenCartwall dl;

	if( dl.DoModal()==IDOK )
	{
		int Pos;
		for( Pos=0; Pos<50; Pos++ )
			m_pList->m_Carts[Pos]->OnCut();

		CCartwallComponents rs( g_strOnAirConnect );
		rs.m_strFilter.Format("CartwallID = %d",dl.m_CartID);
		rs.m_strSort="Position";
		rs.Open();
		
		while( !rs.IsEOF() )
		{
			m_pList->m_Carts[rs.m_Position]->Load((WORD)rs.m_Type,rs.m_ElementID);
			
			rs.MoveNext();
		}

		if( dl.m_Info )
		{
			m_strCartName = "";
			m_CartwallID = 0;
		}
		else
		{
			m_strCartName = dl.m_strCartName;
			m_CartwallID = dl.m_CartID;
		}

		rs.Close();
	}
}

void CCartwallWnd::OnSave()
{
	if( m_strCartName=="" )
	{
		CNewCartwall dl;

		dl.m_Name=m_strCartName;


		if( dl.DoModal()==IDOK )
		{
			CRSCartwallDefinition rs( g_strOnAirConnect );
			CString str=dl.m_Name;
			str.Replace("'","''");

			rs.m_strFilter.Format("Name = '%s'",str);
			rs.Open();
			if( rs.GetRecordCount()!=0 )
			{
				if( rs.m_Info )
				{
					AfxMessageBox(IDS_INFOCARTWALL);
					return;
				}

				if( AfxMessageBox(IDS_CARTWALLEXISTS,MB_YESNO)==IDNO )
					return;

				m_CartwallID = rs.m_ID;
			}
			else
			{
				rs.AddNew();
				rs.m_Info=0;
				rs.m_Name=dl.m_Name;
				rs.m_UserID = 0;
				rs.Update();
				rs.m_strSort="ID DESC";
				rs.Requery();
				m_strCartName = dl.m_Name;
				m_CartwallID = rs.m_ID;
			}
			rs.Close();
		}
		else
			return;
	}
	
	////////////////////////////////
	// Gravar alterações a um cartwall existente
	CDatabase db;
	CString	strSQL;

	db.Open( g_strOnAirConnect );
	strSQL.Format("DELETE FROM CartwallContents WHERE CartwallID = %d",m_CartwallID);
	db.ExecuteSQL(strSQL);

	WORD Type;
	long ElementID;

	for( int Pos=0; Pos<50; Pos++ )
	{
		if( m_pList->m_Carts[Pos]->m_pItem==NULL )
		{
			Type = 0;
			ElementID = 0;
		}
		else
		{
			Type = m_pList->m_Carts[Pos]->m_pItem->m_wType;
			ElementID = m_pList->m_Carts[Pos]->m_pItem->m_lItemID;
		}
		strSQL.Format("INSERT INTO CartwallContents (CartwallID,Position,Type,ElementID,AutoFade,Loop) VALUES (%d,%d,%d,%d,0,0)",
			m_CartwallID,Pos,Type,ElementID);
		db.ExecuteSQL(strSQL);
	}
	db.Close();
}

