// ProducerMusicMain.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "ProducerMusicMain.h"
#include "OnAirDefines.h"
#include "OnAirUtils.h"
#include "ExternalObjects.h"
#include "..\common\include\utils.h"
#include "..\include\RSPath.h"
#include "..\include\RSViewMusicFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_SELECTION	1001

/////////////////////////////////////////////////////////////////////////////
// CProducerMusicMain

IMPLEMENT_DYNCREATE(CProducerMusicMain, CFrameWnd)

CProducerMusicMain::CProducerMusicMain()
{
	m_PathID=0;
}

CProducerMusicMain::~CProducerMusicMain()
{
}


BEGIN_MESSAGE_MAP(CProducerMusicMain, CFrameWnd)
	//{{AFX_MSG_MAP(CProducerMusicMain)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_COMMAND( CM_REFRESH,RefreshFileList)
	ON_COMMAND( CM_SAVE,OnSave )
	ON_COMMAND( CM_DISCARD,OnDiscard )
	ON_CBN_SELCHANGE( ID_SELECTION,OnSelChange )
	ON_MESSAGE( UM_FILEDBLCLK,OnDblClk )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProducerMusicMain message handlers

int CProducerMusicMain::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CString	strTemp;

	/////////////////////////////////////////////////////////////////////////
	//	Get the client's rect
	CRect	rect;
	GetClientRect(&rect);

	/////////////////////////////////////////////////////////////////////////
	//	Create the ReBar
	m_pRebar = new CReBar();
	m_pRebar->Create(this,CCS_TOP|CCS_NOPARENTALIGN|CCS_NODIVIDER|RBS_AUTOSIZE,WS_VISIBLE|CBRS_BOTTOM);
	
	/////////////////////////////////////////////////////////////////////////
	//	Create the Buttons
	TBBUTTON	buttons[5];
	buttons[0].iBitmap=0;
	buttons[0].idCommand=CM_REFRESH;
	buttons[0].fsState=TBSTATE_ENABLED;
	buttons[0].fsStyle=TBSTYLE_BUTTON;
	buttons[0].dwData=0;
	buttons[0].iString=0;

	buttons[1].iBitmap=9;
	buttons[1].idCommand=CM_SAVE;
	buttons[1].fsState=TBSTATE_ENABLED;
	buttons[1].fsStyle=TBSTYLE_BUTTON;
	buttons[1].dwData=0;
	buttons[1].iString=9;

	buttons[2].iBitmap=10;
	buttons[2].idCommand=CM_DISCARD;
	buttons[2].fsState=TBSTATE_ENABLED;
	buttons[2].fsStyle=TBSTYLE_BUTTON;
	buttons[2].dwData=0;
	buttons[2].iString=10;

	/////////////////////////////////////////////////////////////////////////
	//	Create the ToolBar
	m_pToolBar = new CToolBarCtrl();
	m_pToolBar->Create(TBSTYLE_FLAT|CCS_BOTTOM,CRect(10,10,100,0),this,292);

	// Set up the tool bar
	m_pToolBar->SetImageList(g_ilToolEnabled);
	m_pToolBar->SetHotImageList(g_ilToolHot);
	m_pToolBar->AddStrings(g_lpstrToolLabels);
	m_pToolBar->AddButtons(3,buttons);
	m_pToolBar->AutoSize();

	// Add the toolbar to the ReBar
	m_pRebar->AddBar(m_pToolBar,NULL,g_bmToolBackground);

	// Hide the unused buttons
	m_pToolBar->HideButton(CM_SAVE);
	m_pToolBar->HideButton(CM_DISCARD);

	/////////////////////////////////////////////////////////////////////////
	//	Create the path selector
	m_ctrlSelection = new CComboBoxEx();
	m_ctrlSelection->Create(CBS_DROPDOWNLIST|WS_VISIBLE|CBS_OWNERDRAWFIXED,CRect(rect.left+40,rect.top+2,rect.right-1,rect.top+402),this,ID_SELECTION);
	m_ctrlSelection->SetFont(g_cfont24);
	m_ctrlSelection->SetImageList(g_ilContainer);

	/////////////////////////////////////////////////////////////////////////
	//	Create and setup the header
	m_pHeader = new CHeaderCtrl();
	m_pHeader->Create(WS_VISIBLE|HDS_BUTTONS,CRect(rect.left,rect.top+38,rect.right,rect.top+54),this,87);

	HDITEM	hdItem;
	
	strTemp.LoadString(IDS_SOUNDFILE);

	hdItem.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hdItem.pszText=strTemp.GetBuffer(0);
	hdItem.cxy=rect.Width()-GetSystemMetrics(SM_CXVSCROLL);
	hdItem.cchTextMax=strTemp.GetLength();
	hdItem.fmt=HDF_CENTER|HDF_STRING;
	m_pHeader->InsertItem(0,&hdItem);

	/////////////////////////////////////////////////////////////////////////
	//	Create the file list
	m_pList=new COnAirListBox();
	m_pList->Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY|LBS_OWNERDRAWVARIABLE|LBS_NOINTEGRALHEIGHT,CRect(rect.left,rect.top+55,rect.right,rect.bottom-67),this,200);
	m_pList->m_iX1=50000;
	m_pList->m_iX2=50000;

	/////////////////////////////////////////////////////////////////////////
	//	Populate the path list
	RefreshPathList();

	/////////////////////////////////////////////////////////////////////////
	//	Create the Music Editing window
	GetClientRect(&rect);
	rect.DeflateRect(0,0,0,65);

	m_pEdit = new CProducerMusicEditing();
//	m_pEdit->Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_VSCROLL,rect,this,1);
	m_pEdit->CreateEx(WS_EX_CONTROLPARENT,NULL,NULL,WS_VISIBLE|WS_CHILD|WS_VSCROLL,rect,this,1);
	m_pEdit->MoveWindow(0,0,0,0);

	return 0;
}

void CProducerMusicMain::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CProducerMusicMain::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CFrameWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CProducerMusicMain::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// Just sit still
}

void CProducerMusicMain::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CProducerMusicMain::RefreshPathList()
{
	CRSPath	rs(g_strMainConnect);
	CString	str;

	rs.m_strFilter="Music = '1'";
	rs.m_strSort="Path";
	rs.Open();

	COMBOBOXEXITEM	cbItem;

	cbItem.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT|CBEIF_LPARAM|CBEIF_TEXT;
	cbItem.iItem=0;
	cbItem.pszText=rs.m_Path.GetBuffer(0);
	cbItem.cchTextMax=20;
	cbItem.iImage=6;
	cbItem.iSelectedImage=6;
	cbItem.iIndent=0;

	m_ctrlSelection->ResetContent();

	while( !rs.IsEOF() )
	{
		rs.m_Path.TrimRight();
		cbItem.lParam=rs.m_ID;
		cbItem.pszText=rs.m_Path.GetBuffer(0);
		m_ctrlSelection->InsertItem(&cbItem);

		rs.MoveNext();
		cbItem.iItem++;
	}

	str.LoadString(IDS_REFRESH);
	cbItem.pszText=str.GetBuffer(0);
	cbItem.iImage=50;
	cbItem.iSelectedImage=50;
	cbItem.lParam=0;
	m_ctrlSelection->InsertItem(&cbItem);

	rs.Close();
}

void CProducerMusicMain::RefreshFileList()
{
	if( !g_bUserCanEditMusic )
		return;

	if( m_PathID==0 )
		return;

	if( !m_pList->m_bIsRefreshing )
		AfxBeginThread(RefreshThread,(LPVOID)this,THREAD_PRIORITY_LOWEST);
}

void CProducerMusicMain::OnSelChange()
{
	int Pos=m_ctrlSelection->GetCurSel();

	if( Pos==CB_ERR )
	{
		m_PathID=0;
		return;
	}

	m_PathID=m_ctrlSelection->GetItemData(Pos);
	
	if( m_PathID==0 )
	{
		RefreshPathList();
		m_strPath="";
	}
	else
	{
		CRSPath	rs(g_strMainConnect);

		rs.m_strFilter.Format("ID = '%d'",m_PathID);
		rs.Open();
		if( rs.GetRecordCount() )
		{
			rs.m_Path.TrimRight();
			m_strPath=rs.m_Path;

			RefreshFileList();
		}
		rs.Close();
	}
}

UINT CProducerMusicMain::RefreshThread(LPVOID p)
{
	CProducerMusicMain	*pWnd=(CProducerMusicMain *)p;
	CFileFind	finder;
	BOOL		bWorking;
	CString		str,
				strFileType;
	typeArchiveItem*	lpItem;
	CRSViewMusicFiles	rs(g_strMainConnect);

	rs.m_strFilter="FileName = 'zz'";
	rs.Open();

	pWnd->m_pList->m_bIsRefreshing=TRUE;
	pWnd->m_pList->ResetContent();
	pWnd->m_ctrlSelection->EnableWindow(FALSE);

	bWorking=finder.FindFile(pWnd->m_strPath+"\\*.*");

	while( bWorking )
	{
		bWorking=finder.FindNextFile();

		str=finder.GetFilePath();

		strFileType = GetFileType(str);
		strFileType.MakeLower();
		
		if( (strFileType==".wav") || (strFileType==".mp3") )
		{
			str.Replace("'","''");
			rs.m_strFilter.Format("FileName = '%s' AND Activ <> 0",str);
			try {
				rs.Requery();
			}
			catch( ... ) {}

			if( rs.GetRecordCount()==0 )
			{
				lpItem = new typeArchiveItem(TYPE_MUSICFILE,pWnd->m_PathID,finder.GetFileName(),0);
				pWnd->m_pList->InsertString(-1,(LPCTSTR)lpItem);
			}
		}
	}

	rs.Close();

	pWnd->m_pList->m_bIsRefreshing=FALSE;
	pWnd->m_ctrlSelection->EnableWindow(TRUE);

	return 0;
}

LRESULT	CProducerMusicMain::OnDblClk(WPARAM,LPARAM)
{
	if( !g_bUserCanEditMusic )
		return 0;

	long Pos=m_pList->GetCurSel();
	typeArchiveItem* lpItem=(typeArchiveItem*)m_pList->GetItemData(Pos);
	
	if( !m_pEdit->SetFile(lpItem->lID,lpItem->strName) )
	{
		m_pList->DeleteString(Pos);
		delete lpItem;
		return 0;
	}

	CRect	rect;
	GetClientRect(&rect);
	rect.DeflateRect(0,0,0,65);

	m_ctrlSelection->MoveWindow(0,0,0,0);
	m_pHeader->MoveWindow(0,0,0,0);
	m_pList->MoveWindow(0,0,0,0);
	m_pEdit->MoveWindow(rect);

	m_pToolBar->HideButton(CM_REFRESH,TRUE);
	m_pToolBar->HideButton(CM_SAVE,FALSE);
	m_pToolBar->HideButton(CM_DISCARD,FALSE);

	return 0;
}

void CProducerMusicMain::OnDiscard()
{
	CRect	rect;
	GetClientRect(&rect);

	m_ctrlSelection->MoveWindow(CRect(rect.left+40,rect.top+2,rect.right-1,rect.top+402));
	m_pHeader->MoveWindow(CRect(rect.left,rect.top+38,rect.right,rect.top+54));
	m_pList->MoveWindow(CRect(rect.left,rect.top+55,rect.right,rect.bottom-67));
	m_pEdit->MoveWindow(0,0,0,0);

	m_pToolBar->HideButton(CM_REFRESH,FALSE);
	m_pToolBar->HideButton(CM_SAVE,TRUE);
	m_pToolBar->HideButton(CM_DISCARD,TRUE);
	
	m_pEdit->m_pRecorder->KillFile();
}

void CProducerMusicMain::OnSave()
{
	if( !m_pEdit->SaveSong() )
		return;

	CRect	rect;
	GetClientRect(&rect);

	m_ctrlSelection->MoveWindow(CRect(rect.left+40,rect.top+2,rect.right-1,rect.top+402));
	m_pHeader->MoveWindow(CRect(rect.left,rect.top+38,rect.right,rect.top+54));
	m_pList->MoveWindow(CRect(rect.left,rect.top+55,rect.right,rect.bottom-67));
	m_pEdit->MoveWindow(0,0,0,0);

	m_pToolBar->HideButton(CM_REFRESH,FALSE);
	m_pToolBar->HideButton(CM_SAVE,TRUE);
	m_pToolBar->HideButton(CM_DISCARD,TRUE);
}