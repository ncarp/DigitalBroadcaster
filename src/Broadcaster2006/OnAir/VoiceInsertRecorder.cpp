// VoiceInsertRecorder.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "VoiceInsertRecorder.h"
#include "ExternalObjects.h"
#include "..\include\RSPath.h"
#include "..\Include\RSViewVoiceInsert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		ID_USER		10101
#define		ID_NAME		10102
#define		ID_PATH		10103
#define		ID_FILE		10104
/////////////////////////////////////////////////////////////////////////////
// CVoiceInsertRecorder

CVoiceInsertRecorder::CVoiceInsertRecorder()
{
}

CVoiceInsertRecorder::~CVoiceInsertRecorder()
{
}


BEGIN_MESSAGE_MAP(CVoiceInsertRecorder, CWnd)
	//{{AFX_MSG_MAP(CVoiceInsertRecorder)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_CBN_KILLFOCUS( ID_PATH,OnPathKillFocus )
	ON_CBN_SELCHANGE( ID_PATH,OnPathSelChange )
	ON_CBN_KILLFOCUS( ID_FILE,OnFileKillFocus )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVoiceInsertRecorder message handlers

int CVoiceInsertRecorder::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CString	str;
	CStatic	*s;
	CRect	rect(10,12,100,30);
	CRect	crect;

	GetClientRect(&crect);
		
	str.LoadString(IDS_TALENT);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_SONGTITLE);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,35);
	str.LoadString(IDS_PATH);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_FILE);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	///////////////////////////////////////////////////////////////////////////
	str.LoadString(IDS_REFRESH);
	rect=CRect(105,10,crect.right-10,34);
	m_pUser = new CEdit();
	m_pUser->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_GROUP|WS_CHILD|WS_VISIBLE,rect,this,ID_USER);

	rect.OffsetRect(0,24);
	m_pName= new CEdit();
	m_pName->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_NAME);
	
	rect.OffsetRect(0,35);
	rect.InflateRect(0,0,0,200);
	str.LoadString(IDS_REFRESH);

	m_pPath = new CComboBox();
	m_pPath->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_PATH);
	m_pPath->AddString("* "+str);
	m_pPath->SetItemData(0,0);
		
	rect.OffsetRect(0,24);

	m_pFile = new CComboBox();
	m_pFile->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWN|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_FILE);
	m_pFile->AddString("* "+str);
	m_pFile->SetItemData(0,0);

	m_pPath->SetCurSel(0);
	OnPathSelChange();
	m_pPath->SetCurSel(0);
	m_pPath->GetLBText(0,m_strPath);

	//////////////////////////////////////////////////////////////////////////////////
	rect.OffsetRect(0,35);
	rect.InflateRect(105,0,10,50);
	m_pRecorder=new CRecorder();
	m_pRecorder->m_bCanRec = TRUE;
	m_pRecorder->Create(NULL,WS_VISIBLE,rect,this);

	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_FADEIN,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_INTRO,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_FADEOUT,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_MIX,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPA,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPB,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pLoopCheck->EnableWindow(FALSE);
	
	m_pUser->SetWindowText(g_strUserName);
	return 0;
}

void CVoiceInsertRecorder::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	
	dc.FillRect(rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CVoiceInsertRecorder::OnPathSelChange()
{
	int		Pos = m_pPath->GetCurSel();
	
	if( Pos==CB_ERR )
		return;

	if( m_pPath->GetItemData(Pos)!=0 )
		return;

	CString str;

	CRSPath	rsPath(g_strMainConnect);
	rsPath.m_strFilter = "Takes = 1";
	rsPath.m_strSort = "Path";
	rsPath.Open();
	
	m_pPath->ResetContent();

	while( !rsPath.IsEOF() )
	{
		rsPath.m_Path.TrimRight();
		Pos=m_pPath->AddString(rsPath.m_Path);
		m_pPath->SetItemData(Pos,rsPath.m_ID);

		rsPath.MoveNext();
	}
	rsPath.Close();

	str.LoadString(IDS_REFRESH);
	Pos=m_pPath->AddString("* "+str);
	m_pPath->SetItemData(Pos,0);
}

void CVoiceInsertRecorder::OnPathKillFocus()
{
	int Pos=m_pPath->GetCurSel();
	if( Pos==CB_ERR )
		return;

	long lID=m_pPath->GetItemData(Pos);
	if( lID!=m_PathID )
	{
		m_PathID=lID;
		m_pPath->GetLBText(Pos,m_strPath);
		
		////////////////////////////////////////////////////
		//	FillFileList

		CFileFind	finder;
		BOOL		bWorking;
		CString		str;

		m_pFile->ResetContent();

		bWorking=finder.FindFile(m_strPath+"\\*.wav");

		while( bWorking )
		{
			bWorking=finder.FindNextFile();

			str=finder.GetFilePath();
			str.Replace("'","''");
			Pos=m_pFile->AddString(finder.GetFileName());

		}

	}
}

void CVoiceInsertRecorder::OnFileKillFocus()
{
	CString strFullFileName,
			strFileName;
	
	m_pFile->GetWindowText(strFileName);
	strFileName.TrimRight();

	if( strFileName.GetLength()==0 )
		return;

	if( strFileName.Find(".wav")!=strFileName.GetLength()-4 )
	{
		strFileName+=".wav";
		m_pFile->SetWindowText(strFileName);
	}

	if( strFileName!=m_strFileName)
	{
		m_strFileName=strFileName;
		strFullFileName=m_strPath+"\\"+m_strFileName;

		m_pRecorder->m_pTimer->DeleteBM();
		m_pRecorder->SetFile(strFullFileName);	
		m_pRecorder->m_pTimer->m_FadeOut=0;
		m_pRecorder->m_pTimer->m_Mix=m_pRecorder->m_pTimer->m_End-500;
		m_pRecorder->m_pTimer->PaintTimerBM();
		m_pRecorder->OnUpdateTimers(0,0);
	}
}
