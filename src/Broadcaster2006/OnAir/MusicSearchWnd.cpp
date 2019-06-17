// MusicSearchWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "OnAirDefines.h"
#include "OnAirUtils.h"
#include "ExternalObjects.h"
#include "MusicSearchWnd.h"
#include "..\include\utils.h"
#include "..\include\RSCategories.h"
#include "..\include\RSPlayListsDefinition.h"
#include "..\include\RSExpressions.h"
#include "RSViewMusicTracksOnAir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	ID_ARTIST		10001
#define	ID_TITLE		10002
#define ID_CATEGORY		10003
#define ID_PLAYLIST		10004
#define ID_EXPRESSION	10005
#define ID_RYTHM		10006
#define ID_LENGTH		10007
#define ID_INTRO		10008
#define ID_RYTHMMIN		10009
#define ID_RYTHMMAX		10010
#define ID_LENGTHMIN	10011
#define ID_LENGTHMAX	10012
#define ID_INTROMIN		10013
#define ID_INTROMAX		10014

/////////////////////////////////////////////////////////////////////////////
// CMusicSearchWnd

IMPLEMENT_DYNCREATE(CMusicSearchWnd, CFrameWnd)

CMusicSearchWnd::CMusicSearchWnd()
{
	m_wSortBy=0;
	m_bSortAsc=TRUE;
}

CMusicSearchWnd::~CMusicSearchWnd()
{
}


BEGIN_MESSAGE_MAP(CMusicSearchWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CMusicSearchWnd)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_MESSAGE( UM_DOUBLECHANGE, OnDoubleChange )
	ON_CBN_SELCHANGE( ID_CATEGORY,OnCategorySelChange )
	ON_CBN_SELCHANGE( ID_PLAYLIST,OnPlayListSelChange )
	ON_CBN_SELCHANGE( ID_EXPRESSION,OnExpressionSelChange )
	ON_NOTIFY( HDN_TRACK, ID_HEADER, OnHeaderNotify )
	ON_NOTIFY( HDN_ITEMCLICK, ID_HEADER, OnHeaderClick )
	ON_COMMAND( CM_REFRESH, OnRefresh )
	ON_COMMAND( CM_PFL, OnPFL )
	ON_COMMAND( CM_INFO, OnInfo )
	ON_EN_KILLFOCUS( ID_ARTIST,OnItemKill )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicSearchWnd message handlers

int CMusicSearchWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	////////////////////////////////////////////////////////////////////
	//	Create the image list for the header
	m_ilHeader = new CImageList();
	m_ilHeader->Create(16,16,ILC_MASK,1,2);

	CBitmap *temp;
	temp = new CBitmap();
	temp->LoadBitmap(IDB_SORTASC);
	m_ilHeader->Add(temp,RGB(255,255,255));

	temp = new CBitmap();
	temp->LoadBitmap(IDB_SORTDESC);
	m_ilHeader->Add(temp,RGB(255,255,255));

	////////////////////////////////////////////////////////////////////
	//	Create the ReBar control
	m_pRebar = new CReBar();
	m_pRebar->Create(this,RBS_BANDBORDERS,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_BOTTOM);

	CRect	crect;
	GetClientRect(&crect);

	////////////////////////////////////////////////////////////////////
	//	Create the header
	CRect	rectHeader=crect;
	rectHeader.bottom=crect.top+20;
	rectHeader.OffsetRect(0,204);

	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|WS_CHILD|HDS_BUTTONS,rectHeader,this,ID_HEADER );
	m_pHeader->SetImageList(m_ilHeader);

	crect.DeflateRect(0,225,0,67);

	TBBUTTON	buttons[5];
	buttons[0].iBitmap=0;
	buttons[0].idCommand=CM_REFRESH;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=0;

	buttons[1].iBitmap	= 2;
	buttons[1].idCommand= CM_PFL;
	buttons[1].fsState	= TBSTATE_ENABLED;
	buttons[1].fsStyle	= TBSTYLE_BUTTON;
	buttons[1].dwData	= 0;
	buttons[1].iString	= 3;

	buttons[2].iBitmap=3;
	buttons[2].idCommand=CM_INFO;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=1;

	CToolBarCtrl	*wndToolBar=new CToolBarCtrl();
	CSize			size(40,40);

	wndToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,100),this,292);
	wndToolBar->SetButtonSize(size);
	wndToolBar->SetImageList(g_ilToolEnabled);
	wndToolBar->SetHotImageList(g_ilToolHot);
	wndToolBar->AddStrings(g_lpstrToolLabels);
	wndToolBar->AddButtons(3,buttons);
	wndToolBar->AutoSize();

	m_pRebar->AddBar(wndToolBar,NULL,g_bmToolBackground);

	// Just testing...

	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,crect,this,ID_LIST);
	m_pList->m_iX1=rectHeader.right-70-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->m_iX2=rectHeader.right-GetSystemMetrics(SM_CXVSCROLL);
	m_pList->SetBackColor(RGB(235,235,255));

	// 
	HDITEM	hdItem;
	CString	strTemp;

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText="";
	hdItem.cxy=57;
	hdItem.cchTextMax=0;
	hdItem.iImage=0;
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(1,&hdItem);

	strTemp.LoadString(IDS_TITLE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH|HDI_IMAGE;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=rectHeader.Width()-197-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.iImage=0;
	hdItem.fmt=HDF_CENTER|HDF_STRING|HDI_IMAGE;
	m_pHeader->InsertItem(1,&hdItem);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	hdItem.cxy=70;
	hdItem.iImage=3;
	strTemp.LoadString(IDS_DURATION);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(2,&hdItem);

	strTemp.LoadString(IDS_INTRO);
	hdItem.pszText=strTemp.GetBuffer(0);
	m_pHeader->InsertItem(3,&hdItem);
//	m_pHeader->EnableWindow(FALSE);

	////////////////////////////////////////////////////////////
	//	Static titles
	CString		str,
				strRefresh;
	CRect		rect;
	GetClientRect(&rect);

	strRefresh.LoadString(IDS_REFRESH);
	strRefresh="<"+strRefresh+">";

	str.LoadString(IDS_ARTIST);
	CRect srect=CRect(5,8,100,25);
	crect=CRect( 105,5,rect.right-5,29);

	CStatic*	pTemp=new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);
	
	srect.OffsetRect(0,24);
	str.LoadString(IDS_SONGTITLE);
	pTemp = new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);

	srect.OffsetRect(0,24);
	str.LoadString(IDS_CATEGORY);
	pTemp = new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);

	srect.OffsetRect(0,24);
	str.LoadString(IDS_PLAYLIST);
	pTemp = new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);

	srect.OffsetRect(0,24);
	str.LoadString(IDS_EXPRESSION);
	pTemp = new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);

	srect.OffsetRect(0,24);
	str.LoadString(IDS_RYTHM);
	pTemp = new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);

	srect.OffsetRect(0,24);
	str.LoadString(IDS_LENGTH);
	pTemp = new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);

	srect.OffsetRect(0,24);
	str.LoadString(IDS_INTRO);
	pTemp = new CStatic();
	pTemp->Create(str,WS_VISIBLE|SS_RIGHT,srect,this);

	m_pArtist = new CEdit();
	m_pArtist->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,crect,this,ID_ARTIST);

	crect.OffsetRect(0,24);
	m_pTitle = new CEdit();
	m_pTitle->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,crect,this,ID_TITLE);

	crect.OffsetRect(0,24);
	crect.InflateRect(0,0,0,100);
	m_pCategory = new CComboBox();
	m_pCategory->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,crect,this,ID_CATEGORY);
	m_pCategory->AddString("*");
	m_pCategory->SetItemData(0,0);
	m_pCategory->AddString(strRefresh);
	m_pCategory->SetItemData(1,-1);
	m_pCategory->SetCurSel(0);

	crect.OffsetRect(0,24);
	m_pPlayList = new CComboBox();
	m_pPlayList->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,crect,this,ID_PLAYLIST);
	m_pPlayList->AddString("*");
	m_pPlayList->SetItemData(0,0);
	m_pPlayList->AddString(strRefresh);
	m_pPlayList->SetItemData(1,-1);
	m_pPlayList->SetCurSel(0);

	crect.OffsetRect(0,24);
	m_pExpression = new CComboBox();
	m_pExpression->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,crect,this,ID_EXPRESSION);
	m_pExpression->AddString("*");
	m_pExpression->SetItemData(0,0);
	m_pExpression->AddString(strRefresh);
	m_pExpression->SetItemData(1,-1);
	m_pExpression->SetCurSel(0);
	
	crect.DeflateRect(0,0,0,100);
	crect.OffsetRect(0,24);

	CRect	rectmax = crect,
			rectmin = crect;
	rectmin.right=rectmin.left+45;
	rectmax.left=rectmax.right-45;

	crect.DeflateRect(50,0,50,0);

	m_pRythm = new CDoubleSlider();
	m_pRythm->Create(NULL,WS_VISIBLE|SS_NOTIFY,crect,this,ID_RYTHM);

	m_pRythmMin = new CEdit();
	m_pRythmMin->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rectmin,this,ID_RYTHMMIN);

	m_pRythmMax = new CEdit();
	m_pRythmMax->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rectmax,this,ID_RYTHMMAX);

	crect.OffsetRect(0,24);
	rectmax.OffsetRect(0,24);
	rectmin.OffsetRect(0,24);
	m_pLength = new CDoubleSlider();
	m_pLength->Create(NULL,WS_VISIBLE|SS_NOTIFY,crect,this,ID_LENGTH);

	m_pLengthMin = new CEdit();
	m_pLengthMin->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rectmin,this,ID_LENGTHMIN);

	m_pLengthMax = new CEdit();
	m_pLengthMax->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rectmax,this,ID_LENGTHMAX);

	crect.OffsetRect(0,24);
	rectmax.OffsetRect(0,24);
	rectmin.OffsetRect(0,24);
	m_pIntro = new CDoubleSlider();
	m_pIntro->Create(NULL,WS_VISIBLE|SS_NOTIFY,crect,this,ID_INTRO);

	m_pIntroMin = new CEdit();
	m_pIntroMin->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rectmin,this,ID_INTROMIN);

	m_pIntroMax = new CEdit();
	m_pIntroMax->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rectmax,this,ID_INTROMAX);

	return 0;
}

void CMusicSearchWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )	
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMusicSearchWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CMusicSearchWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// Do nothing
}

void CMusicSearchWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CMusicSearchWnd::OnCategorySelChange()
{
	long Pos=m_pCategory->GetCurSel();
	DWORD Data=m_pCategory->GetItemData(Pos);
	if( Data==(DWORD)-1 )
		RefreshCategories();
}

void CMusicSearchWnd::RefreshCategories()
{
	int	iPos;
	CString strRefresh;

	strRefresh.LoadString(IDS_REFRESH);
	strRefresh="<"+strRefresh+">";

	m_pCategory->ResetContent();
	m_pCategory->EnableWindow(FALSE);

	CRSCategories	rs(g_strMainConnect);
	rs.m_strFilter="Activ <> 0 and ID in (select DISTINCT CategoryID from MusicTracks)";
	rs.m_strSort="Name";
	rs.Open();

	iPos=m_pCategory->AddString("*");
	m_pCategory->SetItemData(iPos,0);

	if( rs.GetRecordCount() )
	{
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			iPos=m_pCategory->AddString(rs.m_Name);
			m_pCategory->SetItemData(iPos,rs.m_ID);
			rs.MoveNext();
		}
		m_pCategory->EnableWindow();
	}	
	
	iPos=m_pCategory->AddString(strRefresh);
	m_pCategory->SetItemData(iPos,-1);

	rs.Close();
}

void CMusicSearchWnd::OnPlayListSelChange()
{
	long lPos=m_pPlayList->GetCurSel();
	long lData=m_pPlayList->GetItemData(lPos);

	if( lData==-1 )
		RefreshPlayLists();
}

void CMusicSearchWnd::RefreshPlayLists()
{
	int	iPos;
	CString strRefresh;

	strRefresh.LoadString(IDS_REFRESH);
	strRefresh="<"+strRefresh+">";

	m_pPlayList->ResetContent();
	m_pPlayList->EnableWindow(FALSE);

	m_pPlayList->AddString("*");
	m_pPlayList->SetItemData(0,0);

	CRSPlayListsDefinition	rs(g_strOnAirConnect);
	rs.m_strFilter="Activ <> 0 AND OnAir <> 0";
	rs.m_strSort="Name";
	rs.Open();

	if( rs.GetRecordCount() )
	{
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			iPos=m_pPlayList->AddString(rs.m_Name);
			m_pPlayList->SetItemData(iPos,rs.m_ID);
			rs.MoveNext();
		}
		m_pPlayList->EnableWindow();
	}	

	iPos=m_pPlayList->AddString(strRefresh);
	m_pPlayList->SetItemData(iPos,-1);

	m_pPlayList->SetCurSel(0);
	m_pPlayList->EnableWindow();

	rs.Close();

}

void CMusicSearchWnd::OnExpressionSelChange()
{
	long lPos=m_pExpression->GetCurSel();
	long lData=m_pExpression->GetItemData(lPos);

	if( lData==-1 )
		RefreshExpressions();
}

void CMusicSearchWnd::RefreshExpressions()
{
	int	iPos;
	CString strRefresh;

	strRefresh.LoadString(IDS_REFRESH);
	strRefresh="<"+strRefresh+">";

	m_pExpression->ResetContent();
	m_pExpression->EnableWindow(FALSE);

	m_pExpression->AddString("*");
	m_pExpression->SetItemData(0,0);

	CRSExpressions	rs(g_strMainConnect);
	rs.m_strFilter="Activ <> 0";
	rs.m_strSort="Name";
	rs.Open();

	if( rs.GetRecordCount() )
	{
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			iPos=m_pExpression->AddString(rs.m_Name);
			m_pExpression->SetItemData(iPos,rs.m_ID);
			rs.MoveNext();
		}
	}	

	iPos=m_pExpression->AddString(strRefresh);
	m_pExpression->SetItemData(iPos,-1);

	m_pExpression->SetCurSel(0);
	m_pExpression->EnableWindow();

	rs.Close();
}

void CMusicSearchWnd::OnHeaderNotify( NMHDR * pNotifyStruct, LRESULT * result )
{
//	AfxMessageBox("#TETS");
	*result=1;	
}

LRESULT CMusicSearchWnd::OnDoubleChange(WPARAM Left,LPARAM ID)
{
	CString str;

	switch( ID )
	{
	case ID_RYTHM:
		if( Left )
		{
			str.Format("%d",(long)(m_pRythm->m_fLeft*250));
			m_pRythmMin->SetWindowText(str);
		}
		else
		{
			str.Format("%d",(long)(m_pRythm->m_fRight*250));
			m_pRythmMax->SetWindowText(str);
		}
		break;
	case ID_LENGTH:
		if( Left )
		{
			GetTimeString((long)(m_pLength->m_fLeft*900000),&str);
			str.Delete(0,3);
			str.Delete(6,3);
			m_pLengthMin->SetWindowText(str);
		}
		else
		{
			GetTimeString((long)(m_pLength->m_fRight*900000),&str);
			str.Delete(0,3);
			str.Delete(6,3);
			m_pLengthMax->SetWindowText(str);
		}
		break;
	case ID_INTRO:
		if( Left )
		{
			str.Format("%d s",(long)(m_pIntro->m_fLeft*120));
			m_pIntroMin->SetWindowText(str);
		}
		else
		{
			str.Format("%d s",(long)(m_pIntro->m_fRight*120));
			m_pIntroMax->SetWindowText(str);
		}
		break;
	}

	return 0;
}

void CMusicSearchWnd::OnHeaderClick( NMHDR * pNotifyStruct, LRESULT * result )
{
	LPNMHEADER ns = (LPNMHEADER)pNotifyStruct;

	if( ns->iItem == m_wSortBy )
		m_bSortAsc=!m_bSortAsc;
	else
		m_bSortAsc=TRUE;

	m_wSortBy=ns->iItem;

	HDITEM    curItem;
	
	for( int I=0; I<4; I++ )
	{
		m_pHeader->GetItem(I, &curItem);
		curItem.mask= HDI_IMAGE | HDI_FORMAT;
		curItem.fmt= HDF_CENTER | HDF_IMAGE | HDF_STRING;

		if( I!=m_wSortBy )
		{
			curItem.mask= HDI_FORMAT;
			curItem.fmt= HDF_CENTER | HDF_STRING;
			curItem.iImage = 2;
		}
		else if( m_bSortAsc )
		{
			curItem.mask= HDI_IMAGE | HDI_FORMAT;
			curItem.fmt= HDF_CENTER | HDF_IMAGE | HDF_STRING;
			curItem.iImage = 0;
		}
		else
		{
			curItem.mask= HDI_IMAGE | HDI_FORMAT;
			curItem.fmt= HDF_CENTER | HDF_IMAGE | HDF_STRING;
			curItem.iImage = 1;
		}

		m_pHeader->SetItem(I, &curItem);
	}

	OnRefresh();

	*result=1;	
}

void CMusicSearchWnd::OnRefresh()
{
	if( !m_pList->m_bIsRefreshing )
	{
		PrepareSQL();
		AfxBeginThread(ThreadRefresh,(LPVOID)this);
		m_pList->EnableWindow();
	}
}

void CMusicSearchWnd::PrepareSQL()
{
	CString strArtist,
			strTitle,
			newSQL="",
			strTemp;
	int		iPos;
	long	lCategory,
			lPlayList,
			lExpression,
			lRythmMin,lRythmMax,
			lLengthMin,lLengthMax,
			lIntroMin,lIntroMax;

	m_pArtist->GetWindowText(strArtist);
	strArtist.TrimRight();
	if( strArtist.GetLength() )
	{
		strArtist.Replace("'","''");
		strTemp.Format("ArtistName LIKE '%%%s%%'",strArtist);
		newSQL = strTemp;
	}

	m_pTitle->GetWindowText(strTitle);
	strTitle.TrimRight();
	if( strTitle.GetLength() )
	{
		strTitle.Replace("'","''");
		strTemp.Format("TrackTitle LIKE '%%%s%%'",strTitle);
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////

	iPos=m_pCategory->GetCurSel();
	if( iPos==CB_ERR )
		lCategory=0;
	else
		lCategory=m_pCategory->GetItemData(iPos);

	if( lCategory!=0 )
	{
		strTemp.Format("TrackID in (Select ID from Broadcaster.dbo.MusicTracks where CategoryID = '%d')",lCategory);
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////
	//	Play List
	iPos=m_pPlayList->GetCurSel();
	if( iPos==CB_ERR )
		lPlayList=0;
	else
		lPlayList=m_pPlayList->GetItemData(iPos);

	if( lPlayList!=0 )
	{
		strTemp.Format("TrackID in (Select MusicTrackID from [PlayLists-Contents] where ListID = '%d')",lPlayList);
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}
	
	
	///////////////////////////////////////////////////////////////////////
	//	Expression
	iPos=m_pExpression->GetCurSel();
	if( iPos==CB_ERR )
		lExpression=0;
	else
		lExpression=m_pExpression->GetItemData(iPos);
	
	if( lExpression!=0 )
	{
		strTemp.Format("TrackID in (Select ID from Broadcaster.dbo.MusicTracks where LanguageID = '%d')",lExpression);
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////
	//	Rythm
	lRythmMin = (long)(m_pRythm->m_fLeft*250.0f);
	lRythmMax = (long)(m_pRythm->m_fRight*250.0f);

	if( (lRythmMin!=0) || (lRythmMax!=250) )
	{
		strTemp.Format("TrackRythm >= '%d' AND TrackRythm <= '%d'",lRythmMin,lRythmMax);

		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////
	//	Length
	lLengthMin = (long)(m_pLength->m_fLeft*900000.0f);
	lLengthMax = (long)(m_pLength->m_fRight*900000.0f);

	if( (lLengthMin!=0) || (lLengthMax!=900000) )
	{
		strTemp.Format("TrackLength >= '%d' AND TrackLength <= '%d'",lLengthMin,lLengthMax);

		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////
	//	Intro
	lIntroMin = (long)(m_pIntro->m_fLeft*120000.0f);
	lIntroMax = (long)(m_pIntro->m_fRight*120000.0f);

	if( (lLengthMin!=0) || (lLengthMax!=120000) )
	{
		strTemp.Format("TrackIntroTime >= '%d' AND TrackIntroTime <= '%d'",lIntroMin,lIntroMax);

		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	if( newSQL != m_SQLQuery )
	{
		m_pList->EnableWindow(FALSE);
		m_SQLQuery = newSQL;
	}
}

UINT CMusicSearchWnd::ThreadRefresh(LPVOID v)
{
	CDatabase	db;
	db.Open(g_strOnAirConnect);
	if( g_bTimeOut ) 
		db.SetQueryTimeout(1);
	else
		db.SetQueryTimeout(360);

	CRSViewMusicTracksOnAir	rs("",&db);
	typeArchiveItem			*lpItem;
	int						Pos=0;
	CString					strPrevArtist="";
	CString					strTemp;
	CMusicSearchWnd			*pThis=(CMusicSearchWnd *)v;

	pThis->m_pList->m_bIsRefreshing=TRUE;
	pThis->m_pHeader->EnableWindow(FALSE);

	pThis->m_pList->ResetContent();

	rs.m_strFilter=pThis->m_SQLQuery;
	
	switch( pThis->m_wSortBy )
	{
	case 0:
		if( pThis->m_bSortAsc )
			rs.m_strSort="TrackRythm ASC, ArtistName, TrackTitle";
		else
			rs.m_strSort="TrackRythm DESC, ArtistName, TrackTitle";
		break;
	case 1:
		if( pThis->m_bSortAsc )
			rs.m_strSort="ArtistName ASC, TrackTitle ASC";
		else
			rs.m_strSort="ArtistName DESC, TrackTitle DESC";
		break;
	case 2:
		if( pThis->m_bSortAsc )
			rs.m_strSort="TrackLength ASC";
		else
			rs.m_strSort="TrackLength DESC";
		break;
	case 3:
		if( pThis->m_bSortAsc )
			rs.m_strSort="TrackIntroTime ASC";
		else
			rs.m_strSort="TrackIntroTime DESC";
		break;
	}

	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_ArtistName.TrimRight();
		rs.m_TrackTitle.TrimRight();
		lpItem = new typeArchiveItem(TYPE_MUSIC,rs.m_TrackID,rs.m_ArtistName+" - "+rs.m_TrackTitle,rs.m_TrackRythm);
		GetTimeString(rs.m_TrackLength,&(lpItem->strData1));
		lpItem->strData1.Delete(0,3);
		lpItem->strData1.Delete(7,2);

		if( rs.m_TrackIntroTime>0 )
		{
			GetTimeString(rs.m_TrackIntroTime,&(lpItem->strData2));
			lpItem->strData2.Delete(0,4);
			lpItem->strData2.Delete(6,2);
		}
		else
			lpItem->strData2="nd";


		pThis->m_pList->InsertString(-1,(LPCTSTR)lpItem);

		Pos++;
		rs.MoveNext();
	}

	pThis->m_pList->m_bIsRefreshing=FALSE;
	pThis->m_pHeader->EnableWindow(TRUE);

	return 0;
}

void CMusicSearchWnd::OnItemKill()
{
	PrepareSQL();
}

void CMusicSearchWnd::OnPFL()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	if( lpItem->wType==TYPE_MUSIC )
	{
		g_wndPFL->SetSound(lpItem);
		g_wndPFL->RestoreWindow();
	}
}

void CMusicSearchWnd::OnInfo()
{
	long int lPos=m_pList->GetCurSel();

	if( lPos==LB_ERR )
		return;

	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(lPos);
	if( lpItem==NULL )
		return;

	CString strURL;
	if( lpItem->wType==TYPE_MUSIC )
	{
		strURL.Format("%s\\OnAirSong.asp?ID=%d&DB=%s",g_strBaseURL,lpItem->lID,g_strDB);
		g_wndMusicInfo->SetView(strURL);
	}
	else
	{
		strURL.Format("%s\\Artist.asp?ID=%d",g_strBaseURL,lpItem->lID);
		g_wndMusicInfo->SetView(strURL);
	}
}