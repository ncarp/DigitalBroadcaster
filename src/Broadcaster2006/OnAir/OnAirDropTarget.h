#if !defined( __ONAIRDROPTARGET_H__ )
#define __ONAIRDROPTARGET_H__

class COnAirDropTarget : public COleDropTarget
{
public:
	COnAirDropTarget();
	~COnAirDropTarget();

protected:
	virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );
};

#endif