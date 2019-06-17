// BroadcasterMusicView.h : interface of the CBroadcasterMusicView class
//


#pragma once


class CBroadcasterMusicView : public CView
{
protected: // create from serialization only
	CBroadcasterMusicView();
	DECLARE_DYNCREATE(CBroadcasterMusicView)

// Attributes
public:
	CBroadcasterMusicDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CBroadcasterMusicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BroadcasterMusicView.cpp
inline CBroadcasterMusicDoc* CBroadcasterMusicView::GetDocument() const
   { return reinterpret_cast<CBroadcasterMusicDoc*>(m_pDocument); }
#endif

