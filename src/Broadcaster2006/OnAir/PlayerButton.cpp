// PlayerButton.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"
#include "PlayerButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayerButton

CPlayerButton::CPlayerButton()
{
	m_bLight=0;
	m_pImages=NULL;
}

CPlayerButton::~CPlayerButton()
{
}


BEGIN_MESSAGE_MAP(CPlayerButton, CButton)
	//{{AFX_MSG_MAP(CPlayerButton)
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayerButton message handlers

void CPlayerButton::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	CPoint point=rect.CenterPoint();
	point-=m_bmSize;

	dc.FillRect(rect,&CBrush(GetSysColor(COLOR_3DFACE)) );

	if( m_bLight )
		m_pImages->Draw(&dc,1,point,0);
	else
		m_pImages->Draw(&dc,0,point,0);
}

void CPlayerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC	dc;
	dc.Attach(lpDrawItemStruct->hDC);
	
	CRect rect;
	GetClientRect(&rect);
	CPoint point=rect.CenterPoint();
	point-=m_bmSize;

	if( lpDrawItemStruct->itemState&ODS_SELECTED )
	{
		dc.Draw3dRect(rect,RGB(128,128,128),RGB(255,255,255));

		if( m_bLight )
			m_pImages->Draw(&dc,1,point,0);
		else
			m_pImages->Draw(&dc,0,point,0);
	}
	else
	{
		dc.FillRect( &rect,&CBrush(GetSysColor(COLOR_3DFACE)) );
		if( m_bLight )
			m_pImages->Draw(&dc,1,point,0);
		else
			m_pImages->Draw(&dc,0,point,0);
	}
	dc.Detach();
}

void CPlayerButton::AddImage(int ID,COLORREF cr)
{
	CBitmap*	pbm = new CBitmap();
	pbm->LoadBitmap(ID);

	m_pImages->Add(pbm,cr);
}

void CPlayerButton::SetImageList(int cx, int cy, int start, int end)
{
	if( m_pImages!=NULL )
		delete m_pImages;

	m_pImages = new CImageList();
	m_pImages->Create(cx,cy,ILC_COLOR24|ILC_MASK,start,end);
	m_pImages->SetBkColor(CLR_NONE);
	m_nImages=0;
	m_bmSize=CSize(cx/2,cy/2);
}

void CPlayerButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CPlayerButton::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CButton::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CPlayerButton::OnSysCommand(UINT nID, LPARAM lParam) 
{

}

void CPlayerButton::PaintBM()
{

}
