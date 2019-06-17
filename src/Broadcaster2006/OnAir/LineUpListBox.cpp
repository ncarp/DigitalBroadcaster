// LineUpListBox.cpp : implementation file
//

#include "stdafx.h"

#include <gdiplus.h>
using namespace Gdiplus;

#include "ExternalObjects.h"
#include "OnAir.h"
#include "LineUpListBox.h"
#include "typeLineUpItem.h"
#include "OnAirUtils.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineUpListBox

CLineUpListBox::CLineUpListBox()
{
	m_Color = RGB(245,245,255);
	m_Brush.CreateSolidBrush(m_Color);
}

CLineUpListBox::~CLineUpListBox()
{
}

BEGIN_MESSAGE_MAP(CLineUpListBox, CListBox)
	//{{AFX_MSG_MAP(CLineUpListBox)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SYSKEYUP()
	ON_WM_KEYUP()
	ON_WM_DELETEITEM_REFLECT()
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_MEASUREITEM_REFLECT()
	ON_CONTROL_REFLECT(LBN_DBLCLK, OnDblclk)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, OnSelchange)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(UM_CANDROP,OnCanDrop)
	ON_MESSAGE(UM_DROP,OnDrop)
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineUpListBox message handlers

HBRUSH CLineUpListBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	return m_Brush;
}

void CLineUpListBox::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CListBox::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CLineUpListBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( !CheckKey(nChar) )
		CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CLineUpListBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) 
{
	// TODO: Add your message handler code here
	
}

void CLineUpListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	typeLineUpItem	*lpItem=(typeLineUpItem *)lpDrawItemStruct->itemData;
	
	if( lpItem==NULL )
		return;

	CDC	dc;
	dc.Attach(lpDrawItemStruct->hDC);

	Graphics	graph(lpDrawItemStruct->hDC);
	WCHAR		wchar[200],
				wchart[200],
				wchar2[20],
				wchar3[20];
	
	PointF		points[]={ PointF((REAL)(lpDrawItemStruct->rcItem.left),(REAL)(lpDrawItemStruct->rcItem.top)),
							PointF((REAL)(lpDrawItemStruct->rcItem.left),(REAL)(lpDrawItemStruct->rcItem.bottom)),
							PointF((REAL)(lpDrawItemStruct->rcItem.right),(REAL)(lpDrawItemStruct->rcItem.bottom)),
							PointF((REAL)(lpDrawItemStruct->rcItem.right),(REAL)(lpDrawItemStruct->rcItem.top)) };
	SizeF		sizef(points[2].X-points[0].X,points[2].Y-points[0].Y);
	RectF		rectf(points[0],sizef);
	Rect		rcRect(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,
					lpDrawItemStruct->rcItem.right-lpDrawItemStruct->rcItem.left,
					lpDrawItemStruct->rcItem.bottom-lpDrawItemStruct->rcItem.top);

	Color	Back;
	Color	textColor;
	int		rythm = lpItem->m_wRythm;

//	if( lpDrawItemStruct->itemState&ODS_SELECTED )
//		Back.SetValue(Color::MakeARGB(255,0,0,255));
//	else

	Back.SetFromCOLORREF(m_Color);

	if( rythm<=g_iSlow )
		textColor = Color::Black;
	else if( rythm<=g_iSlowAverage )
		textColor = Color::Green;
	else if( rythm<=g_iAverage )
		textColor = Color::Red;
	else
		textColor = Color::Blue;

	StringFormat	strFormat;
	strFormat.SetAlignment(StringAlignmentFar);
	strFormat.SetLineAlignment(StringAlignmentCenter);

	StringFormat	strFormatName;
	strFormatName.SetLineAlignment(StringAlignmentCenter);

	PointF			PointLength((REAL)(lpDrawItemStruct->rcItem.right)-100.0f,points[0].Y+15),
					PointStart((REAL)(lpDrawItemStruct->rcItem.right)-5.0f,points[0].Y+15);

	LinearGradientBrush brush(Point(0,0),Point(50,0),Color(255,0,0,0),Color(255,255,0,0));

	RectF	rr((REAL)lpDrawItemStruct->rcItem.left,(REAL)lpDrawItemStruct->rcItem.bottom-2,500.0f,1);
	CString		strTemp;

	MultiByteConversion(lpItem->m_strName,wchar);
	MultiByteConversion(lpItem->m_strName2,wchart);

	switch( lpItem->m_wType )
	{
	case TYPE_MUSIC:
		break;
	case TYPE_JINGLE:
		Back = Color(255,241,239,162);
		break;
	case TYPE_SPOT:
		Back = Color(255,177,239,162);
		break;
	case TYPE_VOICEINSERT:
		Back = Color(255,177,239,226);
		break;
	case TYPE_BLOCK:
		Back = Color(255,241,175,162);
		break;
	case TYPE_RM:
		Back = Color(255,241,175,226);
		break;
	case TYPE_TIMESIGNAL:
		Back = Color(255,177,239,255);
	default:
		break;
	}
	graph.FillRectangle(&SolidBrush(Back),rectf);

	CRect trect(lpDrawItemStruct->rcItem);
	
	LinearGradientBrush temp( PointF((REAL)trect.left,(REAL)trect.top),
								PointF((REAL)trect.left,(REAL)trect.top+10),
								Back,
								Color(255,80,80,120) );

	LinearGradientBrush temp2( PointF((REAL)trect.left,(REAL)trect.bottom-10),
								PointF((REAL)trect.left,(REAL)(trect.bottom)),
								Color(255,80,80,120),
								Back);
	LinearGradientBrush brushopaque(Point(lpDrawItemStruct->rcItem.right-200,(int)points[0].Y),
								Point(lpDrawItemStruct->rcItem.right-170,(int)points[0].Y),
								Color(0,Back.GetR(),Back.GetG(),Back.GetB()),
								Back );
	LinearGradientBrush brtop( PointF(0,0),PointF(0,10),Color(192,255,255,255),Back );
	LinearGradientBrush brbottom( PointF((REAL)trect.left,(REAL)trect.bottom-10),
								PointF((REAL)trect.left,(REAL)(trect.bottom)),
								Back,
								Color(64,128,128,128) );

	if( lpDrawItemStruct->itemState&ODS_SELECTED )
	{
		graph.FillRectangle(&temp,Rect(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,trect.Width(),10));
		graph.FillRectangle(&SolidBrush(Color(255,80,80,120)),Rect(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top+10,trect.Width(),trect.Height()-20));
		graph.FillRectangle(&temp2,Rect(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.bottom-10,trect.Width(),10));
	}
	else
	{
		graph.FillRectangle(&brtop,Rect(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,trect.Width(),10));
		graph.FillRectangle(&brbottom,Rect(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.bottom-10,trect.Width(),10));
	}

//	graph.FillRectangle(g_brushSeparator,rr);

	//////////////////////////////////////////////////////////////////
	//	Start string
	GetTimeString64(lpItem->m_qwStartTime,&strTemp);

	strTemp.Delete(10,2);
	MultiByteConversion(strTemp,wchar2);
	
	//////////////////////////////////////////////////////////////////
	//	Length String
	GetTimeString(lpItem->GetLength(),&strTemp);
	strTemp.Delete(0,3);
	strTemp.Delete(7,2);
	MultiByteConversion(strTemp,wchar3);

	points[0]=points[0]+PointF(40,15);

	if( lpDrawItemStruct->itemState&ODS_SELECTED )
	{
		graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(128 ,255,255,255)) );
		points[0]=points[0]+PointF(0,20);
		graph.DrawString(wchart,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(128,255,255,255)) );
		points[0]=points[0]+PointF(-1,-21);
		graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(255,250,250,250)) );
		points[0]=points[0]+PointF(0,20);
		graph.DrawString(wchart,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(255,250,250,250)) );

		graph.FillRectangle(&SolidBrush(Color(255,80,80,120)),Rect(lpDrawItemStruct->rcItem.right-120,lpDrawItemStruct->rcItem.top,120,50));
		graph.FillRectangle(&temp,Rect(lpDrawItemStruct->rcItem.right-120,lpDrawItemStruct->rcItem.top,120,10));
		graph.FillRectangle(&temp2,Rect(lpDrawItemStruct->rcItem.right-120,lpDrawItemStruct->rcItem.bottom-10,120,10));

		graph.DrawString(wchar2,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(128,255,255,255)) );
		graph.DrawString(wchar3,-1,g_font12,PointStart+PointF(0,20),&strFormat,&SolidBrush(Color(128,255,255,255)) );

		PointLength=PointLength+PointF(-1,-1);
		PointStart=PointStart+PointF(-1,-1);

		graph.DrawString(wchar3,-1,g_font12,PointStart+PointF(0,20),&strFormat,&SolidBrush(Color(255,255,255,255)) );
		graph.DrawString(wchar2,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(255,255,255,255)) );
	}
	else 
	{
		graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(64,0,0,0)) );
		points[0]=points[0]+PointF(0,20);
		graph.DrawString(wchart,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(64,0,0,0)) );
		points[0]=points[0]+PointF(-1,-21);
		graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(textColor) );
		points[0]=points[0]+PointF(0,20);
		graph.DrawString(wchart,-1,g_font12,points[0],&strFormatName,&SolidBrush(textColor) );

		graph.FillRectangle(&brtop,Rect(lpDrawItemStruct->rcItem.right-120,lpDrawItemStruct->rcItem.top,120,10));
		graph.FillRectangle(&SolidBrush(Back),Rect(lpDrawItemStruct->rcItem.right-120,lpDrawItemStruct->rcItem.top+10,120,30));
		graph.FillRectangle(&brbottom,Rect(lpDrawItemStruct->rcItem.right-120,lpDrawItemStruct->rcItem.bottom-10,120,10));

		graph.DrawString(wchar3,-1,g_font12,PointStart+PointF(0,20),&strFormat,&SolidBrush(Color(64,0,0,0)) );
		graph.DrawString(wchar2,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(64,0,0,0)) );

		PointLength=PointLength+PointF(-1,-1);
		PointStart=PointStart+PointF(-1,-1);

		graph.DrawString(wchar3,-1,g_font12,PointStart+PointF(0,20),&strFormat,&SolidBrush(textColor) );
		graph.DrawString(wchar3,-1,g_font12,PointStart+PointF(0,20),&strFormat,&SolidBrush(Color(96,0,0,0)) );
		graph.DrawString(wchar2,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(255,0,0,212)) );
	}

	Bitmap *bmIcon;
	ImageAttributes imageAtt;
	ColorMap cMap[2];
	cMap[0].oldColor = Color(255, 212,208,200); 
	cMap[0].newColor = Color(  0, 255,255,255); 
	cMap[1].oldColor = Color(255, 255,255,255); 
	cMap[1].newColor = Color(  0, 255,255,255); 
	imageAtt.SetRemapTable(2,cMap,ColorAdjustTypeDefault);

	switch( lpItem->m_wType )
	{
	case TYPE_MUSIC:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_MUSIC));
		break;
	case TYPE_JINGLE:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_JINGLESMALL));
		break;
	case TYPE_SPOT:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_TRAFFIC));
		break;
	case TYPE_VOICEINSERT:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_VOICEINSERT));
		break;
	case TYPE_BLOCK:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_BLOCKS));
		break;
	case TYPE_RM:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_RMS));
		break;
	case TYPE_TIMESIGNAL:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_TIMESIGNAL));
		break;
	default:
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_MUSICSMALL));
		break;
	}
	graph.DrawImage(bmIcon,Rect(3,lpDrawItemStruct->rcItem.top+7,bmIcon->GetWidth(), bmIcon->GetHeight()),  // dest rect
							0, 0, bmIcon->GetWidth(), bmIcon->GetHeight(),           // source rect
						UnitPixel,
						&imageAtt);

	::delete bmIcon;

	if( lpItem->m_wType==TYPE_BLOCK )
	{
		int nPos;
		
		points[0]=points[0]+PointF(27,0);
		PointStart=PointStart+PointF(1,20);

		for( nPos=lpItem->m_iNextItem; ((nPos-lpItem->m_iNextItem)<7) && (nPos<lpItem->m_iBlockSize); nPos++ )
		{
			typeLineUpItem *lpSubItem=(typeLineUpItem *)lpItem->m_pBlock[nPos];

			MultiByteConversion(lpSubItem->m_strName+" - "+lpSubItem->m_strName2,wchar);

	
			//////////////////////////////////////////////////////////////////
			//	Start string
			GetTimeString64(lpSubItem->m_qwStartTime,&strTemp);
			//	strTemp.Delete(0,3);
			strTemp.Delete(8,4);
			MultiByteConversion(strTemp,wchar2);
	
			//////////////////////////////////////////////////////////////////
			//	Length String
			GetTimeString(lpSubItem->GetLength(),&strTemp);
			strTemp.Delete(0,3);
			strTemp.Delete(7,2);
			MultiByteConversion(strTemp,wchar3);

			points[0]=points[0]+PointF(1,30);
			PointStart=PointStart+PointF(1,30);

			if( lpDrawItemStruct->itemState&ODS_SELECTED )
			{
				graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(64,255,255,255)) );
				points[0]=points[0]+PointF(-1,-1);
				graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(128,255,255,255)) );

				graph.DrawString(wchar3,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(128,255,255,255)) );
		
				PointStart=PointStart+PointF(-1,-1);

				graph.DrawString(wchar3,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(255,255,255,255)) );
			}
			else 
			{
				graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(64,0,0,0)) );
				points[0]=points[0]+PointF(-1,-1);
				graph.DrawString(wchar,-1,g_font12,points[0],&strFormatName,&SolidBrush(Color(255,0,0,0)) );

				graph.DrawString(wchar3,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(64,0,0,0)) );

				PointStart=PointStart+PointF(-1,-1);

				graph.DrawString(wchar3,-1,g_font12,PointStart,&strFormat,&SolidBrush(Color(255,0,0,0)) );
			}

			switch( lpSubItem->m_wType )
			{
			case TYPE_MUSIC:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_MUSICSMALL));
				break;
			case TYPE_JINGLE:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_JINGLESMALL));
				break;
			case TYPE_SPOT:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_TRAFFIC));
				break;
			case TYPE_VOICEINSERT:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_VOICEINSERT));
				break;
			case TYPE_BLOCK:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_BLOCKS));
				break;
			case TYPE_RM:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_CONTAINER_RMS));
				break;
			case TYPE_TIMESIGNAL:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_TIMESIGNAL));
				break;
			default:
				bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_MUSICSMALL));
				break;
			}
			graph.DrawImage(bmIcon,Rect(23,lpDrawItemStruct->rcItem.top+20+(29*(nPos-lpItem->m_iNextItem+1)),bmIcon->GetWidth(), bmIcon->GetHeight()),  // dest rect
							0, 0, bmIcon->GetWidth(), bmIcon->GetHeight(),           // source rect
						UnitPixel,
						&imageAtt);

			::delete bmIcon;
		}

	}

	if( lpItem->m_bLocked )
	{
		bmIcon=::new Bitmap(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(IDB_TREE_LOCK));
		graph.DrawImage(bmIcon,Rect(lpDrawItemStruct->rcItem.right-100,lpDrawItemStruct->rcItem.top,bmIcon->GetWidth(), bmIcon->GetHeight()),  // dest rect
							0, 0, bmIcon->GetWidth(), bmIcon->GetHeight(),           // source rect
						UnitPixel,
						&imageAtt);
	}
	dc.Detach();
}

void CLineUpListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	typeLineUpItem *lpItem=(typeLineUpItem *)lpMeasureItemStruct->itemData;

	if( lpItem->m_wType==TYPE_BLOCK )
	{
		lpMeasureItemStruct->itemHeight = 50+30*(lpItem->m_iBlockSize);	
		if( lpMeasureItemStruct->itemHeight>255 )
			lpMeasureItemStruct->itemHeight = 255;
	}
	else
		lpMeasureItemStruct->itemHeight = 50;
}	

void CLineUpListBox::OnDblclk() 
{
	SetCurSel(-1);	
}

int CLineUpListBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_DropTarget.Register(this);	

	return 0;
}

LRESULT CLineUpListBox::OnCanDrop(WPARAM, LPARAM)
{
	return 1;
}

LRESULT CLineUpListBox::OnDrop(WPARAM, LPARAM lParam)
{
#ifdef __DEBUG_LOG
	WriteLogFile("CLineUpListBox::OnDrop (Enter)");
#endif

	typeDRAG_ITEM* lpItem=(typeDRAG_ITEM*)lParam;

	BOOL	bOutside=FALSE;
	int		iItemPos=ItemFromPoint(lpItem->DropPoint,bOutside);
	CRect	rect;

	GetItemRect(iItemPos,&rect);
	if(!( (rect.left<lpItem->DropPoint.x) && (rect.right>lpItem->DropPoint.x) && (rect.top<lpItem->DropPoint.y) && (rect.bottom>lpItem->DropPoint.y) ))
		iItemPos=-1;

	if( (lpItem->wType==DRAG_ARCHIVE) )
	{
		SetCurSel(iItemPos);
		((CLineUpWnd *)g_wndLineUp)->AddItemByClick((typeArchiveItem *)lpItem->lpItem);
	}
	else
		InsertString(iItemPos,(LPCTSTR)lpItem->lpItem);

	((CLineUpWnd *)g_wndLineUp)->CalcStartingTimes();

#ifdef __DEBUG_LOG
	WriteLogFile("CLineUpListBox::OnDrop (Exit)");
#endif

	return 1;
}

void CLineUpListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( nFlags&MK_LBUTTON )
	if( !((m_ClickPoint.x<point.x+3) && (m_ClickPoint.x>point.x-3) && 
		(m_ClickPoint.y<point.y+3) && (m_ClickPoint.y>point.y-3)) )
	{
		point = m_ClickPoint;
		BOOL	bOutside=FALSE;
		int		iItemPos=ItemFromPoint(point,bOutside);
		CRect	rect;

		GetItemRect(iItemPos,&rect);
		if( (rect.left<point.x) && (rect.right>point.x) && (rect.top<point.y) && (rect.bottom>point.y) )
		{
			typeLineUpItem*	lpItem=(typeLineUpItem*)GetItemData(iItemPos);
			SetCurSel(iItemPos);

			if( lpItem!=NULL )
			{
#ifdef __DEBUG_LOG
				WriteLogFile("CLineUpListBox::OnMouseMove - Start Drag & Drop");
#endif
				HANDLE hData=::GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,sizeof(typeDRAG_ITEM));
				typeDRAG_ITEM *lpDragItem=(typeDRAG_ITEM *)::GlobalLock(hData);
				if( lpItem->m_wType == TYPE_BLOCK )
					lpDragItem->wType=DRAG_BLOCK;
				else
					lpDragItem->wType=DRAG_LINEUP;
				lpDragItem->lpItem=(LPVOID)lpItem;
				//lpDragItem->lpItem=(LPVOID)lpItem;

				COleDataSource DataSource;
				UINT nFormat=g_nFormatLineUp;

				DataSource.CacheGlobalData(nFormat,hData);
				if( DataSource.DoDragDrop()!=DROPEFFECT_NONE )
				{
					iItemPos=GetCurSel();
					DeleteString(iItemPos);
					GetParent()->SendMessage(UM_DROP);

					((CLineUpWnd *)g_wndLineUp)->CalcStartingTimes();
				}
#ifdef __DEBUG_LOG
				WriteLogFile("CLineUpListBox::OnMouseMove - End Drag & Drop");
#endif
			}
		}
	}
}

void CLineUpListBox::OnSelchange() 
{
	
}

void CLineUpListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_ClickPoint = point;

	CListBox::OnLButtonDown(nFlags, point);
}


void CLineUpListBox::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
#ifdef __DEBUG_LOG
	WriteLogFile("CLineUpListBox::OnRButtonDblClk (Enter)");
#endif

	CListBox::OnRButtonDblClk(nFlags, point);

	if( GetCount()==0 ) 
		return;

	BOOL	bOutside;
	int		iItemPos=ItemFromPoint(point,bOutside);	
	
	if( bOutside )
		return;

	RECT	rect;
	GetItemRect(iItemPos,&rect);

	CRect crect(&rect);
	if( !crect.PtInRect(point) )
		return;

	typeLineUpItem *lpItem = (typeLineUpItem *)GetItemData(iItemPos);
	if( lpItem->m_wType==TYPE_BLOCK )
		GetParent()->SendMessage(UM_BLOCKRDBLCLK,iItemPos,(LPARAM)lpItem);

#ifdef __DEBUG_LOG
	WriteLogFile("CLineUpListBox::OnRButtonDblClk (Exit)");
#endif
}
