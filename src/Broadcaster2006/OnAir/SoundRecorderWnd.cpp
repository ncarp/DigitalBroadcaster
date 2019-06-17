// SoundRecorderWnd.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir.h"
#include "SoundRecorderWnd.h"
#include "ExternalObjects.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundRecorderWnd

CSoundRecorderWnd::CSoundRecorderWnd()
{
}

CSoundRecorderWnd::~CSoundRecorderWnd()
{
}


BEGIN_MESSAGE_MAP(CSoundRecorderWnd, CStatic)
	//{{AFX_MSG_MAP(CSoundRecorderWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundRecorderWnd message handlers

void CSoundRecorderWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

void CSoundRecorderWnd::ShowTask(long ID)
{
	CString str;
	str.Format("%s\\RecordingTask.asp?ID=%d",g_strBaseURL,ID);
	m_pInfo->Navigate2(str);
}

int CSoundRecorderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetClientRect( &m_rect );

	CRect	rect_rec=m_rect;
	rect_rec.top=rect_rec.bottom-275;
	m_pRecorder = new CRecorder();
	m_pRecorder->m_bCanRec=TRUE;
	m_pRecorder->Create(NULL,WS_VISIBLE|SS_NOTIFY,rect_rec,this);

	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_FADEIN,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_INTRO,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_FADEOUT,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_MIX,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPA,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_LOOPB,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_START,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pTimer->m_Menu->EnableMenuItem(MN_END,MF_BYCOMMAND|MF_GRAYED);
	m_pRecorder->m_pLoopCheck->EnableWindow(FALSE);

	CRect recti=m_rect;
	recti.bottom=recti.bottom-280;

	m_pInfo = new COnAirHtml();
	m_pInfo->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,recti,this,NULL);

	return 0;
}
