// DRMDropTarget.h: interface for the CDRMDropTarget class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRMDROPTARGET_H__7B1F440B_7C2F_4F1B_8E57_B4C328B68682__INCLUDED_)
#define AFX_DRMDROPTARGET_H__7B1F440B_7C2F_4F1B_8E57_B4C328B68682__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DRAG_SRC_ARCHIVE	1
#define DRAG_SRC_LINEUP		2

typedef struct 
{
	WORD wSrc;
	WORD wType;
	long lID;
	CPoint DropPoint;
	CImageList	*pDragImage;
}DRAGITEMDATA, *LPDRAGITEMDATA;



#define DRAG_ARCHIVE	1
#define DRAG_LINEUP		2
#define DRAG_BLOCK		3

class CDRMDropTarget : public COleDropTarget  
{
public:
	CImageList	*m_pImageList;

public:
	CDRMDropTarget();
	virtual ~CDRMDropTarget();

protected:
	virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );
	virtual void OnDragLeave(CWnd* pWnd);
};

#endif // !defined(AFX_DRMDROPTARGET_H__7B1F440B_7C2F_4F1B_8E57_B4C328B68682__INCLUDED_)
