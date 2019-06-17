// Cart.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "OnAir.h"
#include "Cart.h"
#include "OnAirDefines.h"
#include "..\include\soundutils.h"
#include "..\include\utils.h"
#include "ExternalObjects.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCart

CCart::CCart()
{
	m_pItem=NULL;
	m_bPlaying=FALSE;
	m_wState=STATE_UNCUED;
}

CCart::~CCart()
{
}


BEGIN_MESSAGE_MAP(CCart, CStatic)
	//{{AFX_MSG_MAP(CCart)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(UM_CANDROP,OnDropQuery)
	ON_MESSAGE(UM_DROP,OnDrop)
	ON_WM_TIMER()
	ON_COMMAND( CM_CUT, OnCut )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCart message handlers

void CCart::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(&rect,&CBrush(GetSysColor(COLOR_3DFACE)));
	rect.right=50;
	dc.Draw3dRect(&rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));

	GetClientRect(&rect);
	rect.DeflateRect(50,0,101,0);
	dc.Draw3dRect(&rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));

	GetClientRect(&rect);
	rect.left = rect.right-99;
	dc.Draw3dRect(&rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));

	Graphics		graph(dc);
	StringFormat	sFormat;
	WCHAR			wchar[20];
	CString			str;

	if( m_wCartNumber<=12 )
		str.Format("%d",m_wCartNumber);
	else if (m_wCartNumber<=24 )
		str.Format("%d",m_wCartNumber-12);
	else
		str = "--";
	MultiByteConversion(str,wchar);
	
	sFormat.SetAlignment(StringAlignmentCenter);
	sFormat.SetLineAlignment(StringAlignmentCenter);
	graph.DrawString(wchar,-1,g_font36,PointF(26,26),&sFormat,&SolidBrush(Color(64,0,0,0)) );
	if( m_wCartNumber<=12 )
		graph.DrawString(wchar,-1,g_font36,PointF(24,24),&sFormat,&SolidBrush(Color(255,200,0,0)) );
	else if( m_wCartNumber<=24 )
		graph.DrawString(wchar,-1,g_font36,PointF(24,24),&sFormat,&SolidBrush(Color(255,0,200,0)) );
	else
		graph.DrawString(wchar,-1,g_font36,PointF(24,24),&sFormat,&SolidBrush(Color(255,0,0,0)) );

	DrawCart();
}

int CCart::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetClientRect(&m_rect);
	int			iViewZone=m_rect.Width()-4;
	
	m_xres=(float)iViewZone/10000.0f;

	m_DropTarget.Register(this);
	
/////////////////////////////////////////////////////////////////////////
	m_Cut = new CPlayerButton();
	m_Cut->Create(NULL,WS_VISIBLE|BS_OWNERDRAW,CRect(m_rect.right-98,2,m_rect.right-2,m_rect.bottom-2),this,CM_CUT);
	m_Cut->SetImageList(40,36,0,3);
	m_Cut->AddImage(IDB_CUT);

/////////////////////////////////////////////////////////////////////////
	//	Create the bitmaps
	CClientDC	dc(this);
	Graphics	graph(dc);

	m_bmName = ::new Bitmap(m_rect.Width()-4,48,&graph);
	
	Graphics	graphbm(m_bmName);
	graphbm.Clear(Color(198,255,255,255));

	m_bmCrono = ::new Bitmap(69,48,&graph);

	return 0;
}

LRESULT CCart::OnDropQuery(WPARAM, LPARAM)
{
	return 1; 
}

LRESULT CCart::OnDrop(WPARAM, LPARAM lParam)
{
	SAFE_DELETE( m_pItem );
	
	typeDRAG_ITEM* lpDropItem=(typeDRAG_ITEM*)lParam;
	typeLineUpItem* lpNewItem;

	if( lpDropItem->wType==DRAG_ARCHIVE )
	{
		typeArchiveItem* lpItem=(typeArchiveItem*)lpDropItem->lpItem;
		lpNewItem = new typeLineUpItem(lpItem->wType,lpItem->lID);
	}
	else
	{
		typeLineUpItem *lpItem=(typeLineUpItem *)lpDropItem->lpItem;
		lpNewItem = new typeLineUpItem(lpItem->m_wType,lpItem->m_lItemID);
	}

	if( lpNewItem->m_bItemIsValid )
	{

		m_pItem = lpNewItem;

		if( m_pItem->m_Sound==NULL )
		{
			m_pItem->m_Sound=new CAudioStream(lpDS_CARTWALL,this);

			m_pItem->m_Sound->SetFile(m_pItem->m_strFileName.GetBuffer(0));
			m_pItem->m_bmSpectrum = m_pItem->CreateSpectrum(m_xres,48);
			m_pItem->m_Sound->m_pbm=m_pItem->m_bmSpectrum;
			m_pItem->m_Sound->m_xres=m_xres;

			if( m_pItem->m_Sound->CueSound() == S_OK )
			{
				m_pItem->m_Sound->SetPosition(m_pItem->m_lStartPos);
				m_pItem->m_wState = STATE_CUED;

				if( m_pItem->m_lFadeInPos>m_pItem->m_lStartPos )
					m_pItem->m_Sound->SetVolume(-3000);
				else
					m_pItem->m_Sound->SetVolume(0);

			}
			else
			{
				SAFE_DELETE( m_pItem->m_Sound );
				m_pItem->m_Sound=NULL;
			}
		}
	
		if( m_pItem->m_Sound == NULL )
		{
			SAFE_DELETE( m_pItem );
			return 0;
		}

		m_pItem->m_Sound->SetPosition( m_pItem->m_lStartPos);

		m_wState = STATE_CUED;

		PaintBM();
		PaintCrono();

		Invalidate();
	}
	else
		SAFE_DELETE( lpNewItem );

	return 0;
}

void CCart::PaintBM()
{
	if( m_bmName==NULL )
		return; 

	Graphics	graph(m_bmName);
	Bitmap		*bmIcon;
	
	ImageAttributes imageAtt;
	ColorMap cMap[1];
	cMap[0].oldColor = Color(255, 212,208,200); // red 
	cMap[0].newColor = Color(  0, 255,255,255);  // blue
	imageAtt.SetRemapTable(1,cMap,ColorAdjustTypeDefault);

	graph.Clear(Color(198,255,255,255));

	if( m_pItem!=NULL )
	{
		switch( m_pItem->m_wType )
		{
		case TYPE_MUSIC:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_MUSIC));
			break;
		case TYPE_JINGLE:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_JINGLES));
			break;
		case TYPE_SPOT:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_TRAFFIC));
			break;
		case TYPE_VOICEINSERT:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_VOICEINSERT));
			break;
		case TYPE_RM:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_RMS));
			break;
		default:
			bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_MUSIC));
			break;
		}

		WCHAR		wchar[250];
		
		CString	strTemp=m_pItem->m_strName+"\n"+m_pItem->m_strName2;

		MultiByteConversion(strTemp,wchar);

		graph.DrawString(wchar,-1,g_font12,PointF(34,4),&SolidBrush(Color(64,0,0,0)));
		graph.DrawString(wchar,-1,g_font12,PointF(32,2),&SolidBrush(Color(255,0,0,0)));
		graph.DrawImage(bmIcon,Rect(2,10,bmIcon->GetWidth(), bmIcon->GetHeight()),  // dest rect
							0, 0, bmIcon->GetWidth(), bmIcon->GetHeight(),           // source rect
						UnitPixel,
						&imageAtt);

		::delete bmIcon;
	} 

}

void CCart::PaintCrono()
{
	Graphics graph(m_bmCrono);
	
	graph.Clear(Color(200,236,233,216));

	if( m_pItem!=NULL )
	{
		WCHAR		wchar[250];
		WCHAR		wchar2[250];
		
		if( m_pItem->m_Sound!=NULL )
		{
			CString	strTemp1;
			CString strTemp2="";
			long lTimeToIntro=m_pItem->GetTimeToIntro();

			GetTimeString(m_pItem->GetTimeToEnd(),&strTemp1);
			strTemp1.Delete(0,3);
			strTemp1.Delete(7,2);

			MultiByteConversion(strTemp1,wchar);

			graph.DrawString(wchar,-1,g_font12,PointF(2,2),&SolidBrush(Color(255,0,0,0)));

			if( lTimeToIntro )
			{
				GetTimeString(lTimeToIntro,&strTemp2);
				strTemp2.Delete(0,3);
				strTemp2.Delete(7,2);

				MultiByteConversion(strTemp2,wchar2);
				graph.DrawString(wchar2,-1,g_font12,PointF(2,24),&SolidBrush(Color(255,200,0,0)));
			}
	
		}
	}
}

void CCart::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( m_wState==STATE_CUED )
		Play();
	else if( m_wState==STATE_PLAYING )
		Stop();
}

void CCart::Play()
{
	if( m_wState == STATE_UNCUED )
		return;

	m_pItem->m_Sound->SetPosition(m_pItem->m_lStartPos);
	m_pItem->m_Sound->Play();

	if( m_wState!=STATE_PLAYING )
	{
		m_pItem->m_wState=STATE_PLAYING;
		m_wState=STATE_PLAYING;
		SetTimer(1,40,NULL);
	}
}

void CCart::Stop()
{
	if( m_wState != STATE_PLAYING )
		return;

	m_pItem->m_wState=m_wState=STATE_CUED;

	m_pItem->m_Sound->Pause();
	m_pItem->m_Sound->SetPosition( m_pItem->m_lStartPos);
	KillTimer(1);
	Invalidate();
}

void CCart::DrawCart()
{
	CClientDC	dc(this);
	Graphics	graphdc(dc);

	Bitmap		bm(m_rect.Width()-150,m_rect.Height()-2,&graphdc);
	Graphics	graph(&bm);

	PaintCrono();

	graph.Clear(Color(255,212,208,200)) ;

	if(  m_pItem!=NULL )
		graph.DrawImage(m_pItem->m_bmSpectrum,(int)0,(int)0,(int)((REAL)(m_pItem->m_Sound->GetPosition())*m_xres),0,m_rect.Width()-157,48,UnitPixel);

	graph.DrawImage(m_bmName,(int)0,(int)0);
	graph.DrawImage(m_bmCrono,(int)m_rect.right-222,(int)1);

	graphdc.DrawImage(&bm,52,1,0,0,m_rect.Width()-154,48,UnitPixel);
}

void CCart::OnTimer(UINT nIDEvent) 
{
	DrawCart();

	if( m_pItem->GetTimeToEnd()==0 )
	{
		Stop();
	}
}

void CCart::OnCut()
{
	Stop();

	SAFE_DELETE( m_pItem );
	m_wState = STATE_UNCUED;

	PaintBM();
	Invalidate();
}

void CCart::Load(WORD Type,long ID)
{
	SAFE_DELETE( m_pItem );
	
	typeLineUpItem* lpNewItem = new typeLineUpItem(Type,ID);

	if( lpNewItem->m_bItemIsValid )
	{
		m_pItem = lpNewItem;

		if( m_pItem->m_Sound==NULL )
		{
			m_pItem->m_Sound=new CAudioStream(lpDS_CARTWALL,this);

			m_pItem->m_Sound->SetFile(m_pItem->m_strFileName.GetBuffer(0));
			m_pItem->m_bmSpectrum = m_pItem->CreateSpectrum(m_xres,48);
			m_pItem->m_Sound->m_pbm=m_pItem->m_bmSpectrum;
			m_pItem->m_Sound->m_xres=m_xres;

			if( m_pItem->m_Sound->CueSound() == S_OK )
			{
				m_pItem->m_Sound->SetPosition(m_pItem->m_lStartPos);
				m_pItem->m_wState = STATE_CUED;

				if( m_pItem->m_lFadeInPos>m_pItem->m_lStartPos )
					m_pItem->m_Sound->SetVolume(-3000);
				else
					m_pItem->m_Sound->SetVolume(0);

			}
			else
			{
				SAFE_DELETE( m_pItem->m_Sound );
				m_pItem->m_Sound=NULL;
			}
		}
	
		if( m_pItem->m_Sound == NULL )
		{
			SAFE_DELETE( m_pItem );
			return ;
		}

		m_pItem->m_Sound->SetPosition( m_pItem->m_lStartPos);

		m_wState = STATE_CUED;

		PaintBM();
		PaintCrono();

		Invalidate();
	}
	else
		SAFE_DELETE( lpNewItem );
}
