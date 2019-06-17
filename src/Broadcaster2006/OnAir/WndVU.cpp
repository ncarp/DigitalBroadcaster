// WndVU.cpp : implementation file
//

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "WndVU.h"
#include "ExternalObjects.h"

// CWndVU

IMPLEMENT_DYNAMIC(CWndVU, CStatic)

CWndVU::CWndVU()
{

}

CWndVU::~CWndVU()
{
}


BEGIN_MESSAGE_MAP(CWndVU, CStatic)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CWndVU message handlers



int CWndVU::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	CreateBitmaps();

	return 0;
}

void CWndVU::CreateBitmaps()
{
	CRect rect;
	GetClientRect(&rect);

	m_bmBack = ::new Bitmap(rect.Width(),rect.Height());
	Graphics	graph(m_bmBack);
	
	PointF pointsLight[] = {	PointF(0.0f,0.0f),
								PointF(0.0f,(REAL)rect.Height()), 
								PointF((REAL)rect.Width()*3.1f,(REAL)rect.Height()*0.001f), 
								PointF((REAL)rect.Width(),0.0f) };
	GraphicsPath pathLight;
	pathLight.AddLines(pointsLight,4);
	PathGradientBrush brushLight(&pathLight);
	int iCount=4;

	brushLight.SetSurroundColors(g_colorLight,&iCount);
	brushLight.SetCenterColor(g_colorLight[0]);
	brushLight.SetCenterPoint(pointsLight[0]);

	graph.FillRectangle(&SolidBrush(Color::Black),RectF(0.0f,0.0f,(REAL)rect.Width(),(REAL)rect.Height()));
	graph.FillPath(&brushLight,&pathLight);
}

void CWndVU::OnPaint()
{
	CPaintDC dc(this); 

	Graphics dcGraph(dc);
	dcGraph.DrawImage(m_bmBack,PointF(0,0));
}
