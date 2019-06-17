// OnAirListBox.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAirUtils.h"

#include "OnAirListBox.h"
#include "..\include\utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_TICK	1

//////////////////////////////////////////////3///////////////////////////////
// COnAirListBox

COnAirListBox::COnAirListBox()
{
	m_bIsRefreshing=FALSE;
	m_color = GetSysColor(COLOR_3DFACE);
	m_Brush.CreateSolidBrush(m_color);
}

COnAirListBox::~COnAirListBox()
{
}


BEGIN_MESSAGE_MAP(COnAirListBox, CListBox)
	//{{AFX_MSG_MAP(COnAirListBox)
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_DELETEITEM_REFLECT()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_TIMER()
	ON_CONTROL_REFLECT(LBN_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnAirListBox message handlers

void COnAirListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	typeArchiveItem	*lpItem=(typeArchiveItem *)lpDrawItemStruct->itemData;
	
	if( lpItem==NULL )
		return;

	Graphics	graph(lpDrawItemStruct->hDC);
	WCHAR		wchar[200];
	PointF		points[]={ PointF((REAL)(lpDrawItemStruct->rcItem.left),(REAL)(lpDrawItemStruct->rcItem.top)),
							PointF((REAL)(lpDrawItemStruct->rcItem.left),(REAL)(lpDrawItemStruct->rcItem.bottom)),
							PointF((REAL)(lpDrawItemStruct->rcItem.right),(REAL)(lpDrawItemStruct->rcItem.bottom)),
							PointF((REAL)(lpDrawItemStruct->rcItem.right),(REAL)(lpDrawItemStruct->rcItem.top)) };
	SizeF		sizef(points[2].X-points[0].X,points[2].Y-points[0].Y);
	RectF		rectf(points[0],sizef);

	Color	Back;
	Back.SetFromCOLORREF(m_color);

	switch( lpItem->wType )
	{
	case TYPE_NOTHING:
		{
			LinearGradientBrush gb(PointF(rectf.X,rectf.Y),PointF(rectf.X,rectf.Y+rectf.Height),Back,Color(64,128,128,128));
			graph.FillRectangle(&gb,RectF(rectf.X,rectf.Y+1,rectf.Width,rectf.Height));
		}
		break;
	case TYPE_ARTIST:
	case TYPE_JINGLETYPE:
	case TYPE_CUSTOMER:
	case TYPE_RMTYPE:
	case TYPE_SPONSORBLOCK:
		{
			MultiByteConversion(lpItem->strName,wchar);

			if( (lpDrawItemStruct->itemState&ODS_SELECTED) && (lpItem->wType==TYPE_ARTIST) )
			{
				LinearGradientBrush temp( points[0],points[1],Back,Color(255,199,199,199));
				graph.FillRectangle(&temp,rectf);
			}
			else
				graph.FillRectangle(&SolidBrush(Back),rectf);

			LinearGradientBrush gb(PointF(rectf.X,rectf.Y),PointF(rectf.X,rectf.Y+rectf.Height),Color(255,255,255,255),Back);
			graph.FillRectangle(&gb,RectF(rectf.X,rectf.Y,rectf.Width,rectf.Height));

			rectf.Y+=(rectf.Height-6);
			rectf.Height=2;
			rectf.Width=500;
//			graph.FillRectangle(g_brushSeparator,rectf);

			points[0]=points[0]+PointF(20,5);
			graph.DrawString(wchar,-1,g_font24,points[0],&SolidBrush(Color(64,0,0,0)) );
			points[0]=points[0]+PointF(-1,-1);

			if( lpItem->wType==TYPE_SPONSORBLOCK )
				graph.DrawString(wchar,-1,g_font24,points[0],&SolidBrush(Color(255,200,0,0)) );
			else
				graph.DrawString(wchar,-1,g_font24,points[0],&SolidBrush(Color(255,0,0,0)) );
		}
		break;
	case TYPE_RECORDINGTASK:
		{
			PointF			Point2((REAL)m_iX1,(REAL)lpDrawItemStruct->rcItem.bottom-1);
			StringFormat	strFormat;

			strFormat.SetAlignment(StringAlignmentFar);
			strFormat.SetLineAlignment(StringAlignmentFar);

			MultiByteConversion(lpItem->strName,wchar);

			if( (lpDrawItemStruct->itemState&ODS_SELECTED) && (lpItem->wType!=TYPE_ARTIST) )
			{
				LinearGradientBrush temp( points[0],points[1],Back,Color(255,80,80,120));
				graph.FillRectangle(&temp,rectf);
			}
			else
				graph.FillRectangle(&SolidBrush(Back),rectf);

			rectf.Y+=(rectf.Height-6);
			rectf.Height=2;
			rectf.Width=500;
//			graph.FillRectangle(g_brushSeparator,rectf);

			points[0]=points[0]+PointF(20,22);

			if( lpDrawItemStruct->itemState&ODS_SELECTED )
			{
				graph.DrawString(wchar,-1,g_font24,points[0],&SolidBrush(Color(128,255,255,255)) );
				points[0]=points[0]+PointF(-3,-3);
				graph.DrawString(wchar,-1,g_font24,points[0],&SolidBrush(Color(255,0,0,0)) );

				MultiByteConversion(lpItem->strData1,wchar);
				graph.DrawString(wchar,-1,g_font12,Point2,&strFormat,&SolidBrush(Color(128,255,255,255)));
				Point2=Point2+PointF(-3,-3);
				graph.DrawString(wchar,-1,g_font12,Point2,&strFormat,&SolidBrush(Color(255,0,0,0)));
			}
			else
			{
				graph.DrawString(wchar,-1,g_font24,points[0],&SolidBrush(Color(64,0,0,0)) );
				points[0]=points[0]+PointF(-3,-3);
				graph.DrawString(wchar,-1,g_font24,points[0],&SolidBrush(Color(255,0,0,0)) );

				MultiByteConversion(lpItem->strData1,wchar);
				graph.DrawString(wchar,-1,g_font12,Point2,&strFormat,&SolidBrush(Color(64,0,0,0)));
				Point2=Point2+PointF(-3,-3);
				graph.DrawString(wchar,-1,g_font12,Point2,&strFormat,&SolidBrush(Color(255,0,0,0)));
			}
		}
		break;
	case TYPE_MUSICFILE:
		{
			PointF			Point2((REAL)m_iX1,points[0].Y),
							Point3((REAL)m_iX2,points[0].Y);

			MultiByteConversion(lpItem->strName,wchar);

			if( lpDrawItemStruct->itemState&ODS_SELECTED )
			{
				LinearGradientBrush temp( points[0],points[1],Back,Color(255,80,80,120));
				graph.FillRectangle(&temp,rectf);
			}
			else
				graph.FillRectangle(&SolidBrush(Back),rectf);

			points[0]=points[0]+PointF(20,2);

			if( lpDrawItemStruct->itemState&ODS_SELECTED )
			{
				graph.DrawString(wchar,-1,g_font12,points[0],&SolidBrush(Color(128,255,255,255)) );
				points[0]=points[0]+PointF(-1,-1);
				graph.DrawString(wchar,-1,g_font12,points[0],&SolidBrush(Color(255,0,0,0)) );
			}
			else
			{
				graph.DrawString(wchar,-1,g_font12,points[0],&SolidBrush(Color(64,0,0,0)) );
				points[0]=points[0]+PointF(-1,-1);
				graph.DrawString(wchar,-1,g_font12,points[0],&SolidBrush(Color(255,0,0,0)) );
			}
		}
		break;
	default:
		{
			WCHAR			wchar2[20],
							wchar3[20],
							wcharr[10];
			StringFormat	strFormat;
			strFormat.SetAlignment(StringAlignmentFar);
			PointF			Point2((REAL)m_iX1,points[0].Y),
							Point3((REAL)m_iX2,points[0].Y);

			LinearGradientBrush brush(Point(0,0),Point(50,0),Color(255,0,0,0),Color(255,255,0,0));
			LinearGradientBrush brushopaque(Point(lpDrawItemStruct->rcItem.right-200,(int)points[0].Y),
								Point(lpDrawItemStruct->rcItem.right-170,(int)points[0].Y),
								Color(0,Back.GetR(),Back.GetG(),Back.GetB()),
								Back );

			Color	textColor;
			int		rythm = (int)((float)lpItem->cColor*100.0f);

			RectF	rr((REAL)lpDrawItemStruct->rcItem.left+10,(REAL)lpDrawItemStruct->rcItem.bottom-7,40.0f,2);


			MultiByteConversion(lpItem->strName,wchar);
			MultiByteConversion(lpItem->strData1,wchar2);
			MultiByteConversion(lpItem->strData2,wchar3);

			if( rythm<=g_iSlow )
				textColor = Color::Black;
			else if( rythm<=g_iSlowAverage )
				textColor = Color::Green;
			else if( rythm<=g_iAverage )
				textColor = Color::Red;
			else
				textColor = Color::Blue;


			if( lpDrawItemStruct->itemState&ODS_SELECTED )
			{
				LinearGradientBrush temp( points[0],points[1],Back,Color(255,80,80,120));
				graph.FillRectangle(&temp,rectf);
			}
			else
				graph.FillRectangle(&SolidBrush(Back),rectf);

			graph.FillRectangle(&brush,rr);

			StringFormat rformat;
			rformat.SetAlignment(StringAlignmentCenter);
			PointF pointr=points[0]+PointF(30,2);
			swprintf(wcharr,L"%d bpm",(int)((REAL)lpItem->cColor*100.0f));
			
			points[0]=points[0]+PointF(60,2);

			if( ((lpItem->wType==TYPE_MUSIC) || (lpItem->wType==TYPE_JINGLE)) )
				graph.DrawString(wcharr,-1,g_fontRythm,pointr,&rformat,&brush);

			if( lpDrawItemStruct->itemState&ODS_SELECTED )
				graph.DrawString(wchar,-1,g_font12,points[0],&SolidBrush(Color(128,0,0,0)) );
			else
				graph.DrawString(wchar,-1,g_font12,points[0],&SolidBrush(Color(64,0,0,0)) );

			points[0]=points[0]+PointF(-0.5f,-0.5f);
			graph.DrawString(wchar,-1,g_font12,points[0],&SolidBrush(textColor) );

			if( lpDrawItemStruct->itemState&ODS_SELECTED )
			{
				LinearGradientBrush temp( Point(0,lpDrawItemStruct->rcItem.top),Point(0,lpDrawItemStruct->rcItem.bottom),Back,Color(255,80,80,120));
				graph.FillRectangle(&temp,m_iX1-100,lpDrawItemStruct->rcItem.top,200,22);
			}
			else
			{
				graph.FillRectangle(&brushopaque,m_iX1-100,lpDrawItemStruct->rcItem.top,30,22);
				graph.FillRectangle(&SolidBrush(Back),m_iX1-70,lpDrawItemStruct->rcItem.top,170,22);
			}

			if( lpDrawItemStruct->itemState&ODS_SELECTED )
			{
				graph.DrawString(wchar2,-1,g_font12,Point2+PointF(1,1),&strFormat,&SolidBrush(Color(128,255,255,255)));
				graph.DrawString(wchar3,-1,g_font12,Point3+PointF(1,1),&strFormat,&SolidBrush(Color(128,255,255,255)));
			}
			else
			{
				graph.DrawString(wchar2,-1,g_font12,Point2+PointF(1,1),&strFormat,&SolidBrush(Color(64,0,0,0)));
				graph.DrawString(wchar3,-1,g_font12,Point3+PointF(1,1),&strFormat,&SolidBrush(Color(64,0,0,0)));
			}

			graph.DrawString(wchar2,-1,g_font12,Point2,&strFormat,&SolidBrush(textColor));
			graph.DrawString(wchar3,-1,g_font12,Point3,&strFormat,&SolidBrush(textColor));
			graph.DrawString(wchar3,-1,g_font12,Point3,&strFormat,&SolidBrush(Color(96,0,0,0)));

		}
		break;
	}
}

void COnAirListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	typeArchiveItem *lpItem=(typeArchiveItem *)lpMeasureItemStruct->itemData;
	
	if( lpItem==NULL )
		return;

	switch( lpItem->wType )
	{
	case TYPE_NOTHING:
		lpMeasureItemStruct->itemHeight=10;
		break;
	case TYPE_ARTIST:
	case TYPE_JINGLETYPE:
	case TYPE_RECORDINGTASK:
	case TYPE_CUSTOMER:
	case TYPE_RMTYPE:
	case TYPE_SPONSORBLOCK:
		lpMeasureItemStruct->itemHeight=35;
		break;
	default:
		lpMeasureItemStruct->itemHeight=22;
		break;
	}
}

void COnAirListBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) 
{
	// TODO: Add your message handler code here
	
}

void COnAirListBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

void COnAirListBox::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey( nChar ) )
		CListBox::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void COnAirListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListBox::OnLButtonDown(nFlags, point);
}

void COnAirListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( nFlags&MK_LBUTTON )
	{
		BOOL	bOutside=FALSE;
		int		iItemPos=ItemFromPoint(point,bOutside);
		CRect	rect;

		GetItemRect(iItemPos,&rect);
		if( (rect.left<point.x) && (rect.right>point.x) && (rect.top<point.y) && (rect.bottom>point.y) )
		{
			typeArchiveItem*	lpItem=(typeArchiveItem*)GetItemData(iItemPos);

			if( lpItem!=NULL )
			{
				HANDLE hData=::GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,sizeof(typeDRAG_ITEM));
				typeDRAG_ITEM *lpDragItem=(typeDRAG_ITEM *)::GlobalLock(hData);
				switch( lpItem->wType )
				{
				case TYPE_BLOCK:
					lpDragItem->wType=DRAG_ARCHIVE;
					break;
				default:
					lpDragItem->wType=DRAG_ARCHIVE;
					break;
				}
				lpDragItem->lpItem=(LPVOID)lpItem;

				COleDataSource DataSource;
				UINT nFormat=g_nFormatArchive;

				DataSource.CacheGlobalData(nFormat,hData);
				DataSource.DoDragDrop();
			}
		}
	} 
}

int COnAirListBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	EnableToolTips(TRUE);

	return 0;
}

HBRUSH COnAirListBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	return m_Brush;
}

void COnAirListBox::OnTimer(UINT nIDEvent) 
{
}

int COnAirListBox::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
	return 1;
};

void COnAirListBox::OnDblclk() 
{
	long int lPos=GetCurSel();

	if( lPos!=LB_ERR )
	{
		typeArchiveItem* lpItem=(typeArchiveItem*)GetItemData(lPos);
		if( lpItem!=NULL )
			if( lpItem->wType == TYPE_SCHEDULE )
				GetParent()->SendMessage(UM_SCHEDULEDBLCLK);
			else if( lpItem->wType > 50 )
				((CLineUpWnd *)g_wndLineUp)->AddItemByClick(lpItem);
			else if( lpItem->wType == TYPE_MUSICFILE )
				GetParent()->SendMessage(UM_FILEDBLCLK);
			else if( lpItem->wType == TYPE_SCHEDULE )
				GetParent()->SendMessage(UM_SCHEDULEDBLCLK);
			else
				SetCurSel(-1);
	}

}

void COnAirListBox::SetBackColor(COLORREF colorref)
{
	m_color = colorref;
	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(m_color);
}