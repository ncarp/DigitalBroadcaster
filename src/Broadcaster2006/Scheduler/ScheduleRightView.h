#if !defined(AFX_SCHEDULERIGHTVIEW_H__92264448_3B30_4452_87F3_0E8E8A6B39CF__INCLUDED_)
#define AFX_SCHEDULERIGHTVIEW_H__92264448_3B30_4452_87F3_0E8E8A6B39CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScheduleRightView.h : header file
//
#include "..\OnAir\TypeLineUpItem.h"
#include "..\OnAir\OnAirDefines.h"
#include "ScheduleLeftView.h"
/////////////////////////////////////////////////////////////////////////////
// CScheduleRightView view

typedef struct 
{
	WORD	wType;
	long	lID,
			lTemplateID,
			lArtistID;
	CString strName,
			strTemplate,
			strIntro,
			strLength;
	DWORD64 qwStart,
			qwLength,
			qwOriginalLen;
	DWORD	dwIntro;
	BOOL	bLocked;
	int		iImage,
			iRythm;
} typeScheduleItem;

class CScheduleRightView : public CListView
{
protected:
	CScheduleRightView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScheduleRightView)

// Attributes
public:
	COleDropTarget	m_DropTarget;
	typeTreeDrag	*m_lpDragItem;
	CPoint			m_OldPoint;
	CScheduleLeftView *m_pLeft;
	typeLineUpItem	*m_lpBlock[100];
	int				m_nBlocks;

// Operations
public:
	void EditVoiceInsert( int Pos,typeScheduleItem *pItem);
	void	OnPFL();
	void	OnCut();
	void	DrawDragItem( char *strName,CPoint point );
	BOOL	GetDraggedItem( typeScheduleItem *lpItem );
	void	GetScheduleBlocks();
	void	RemoveBlocks();
	void	InsertBlocks();
	void	OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	void	OnLockItem();
	void	SaveSchedule();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScheduleRightView)
	public:
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScheduleRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CScheduleRightView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULERIGHTVIEW_H__92264448_3B30_4452_87F3_0E8E8A6B39CF__INCLUDED_)
