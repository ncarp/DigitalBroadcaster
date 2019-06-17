#if !defined(AFX_MUSICSEARCHWND_H__5E6A893F_4029_4B4F_8D6D_7265EA200658__INCLUDED_)
#define AFX_MUSICSEARCHWND_H__5E6A893F_4029_4B4F_8D6D_7265EA200658__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicSearchWnd.h : header file
//
#include "OnAirListBox.h"
#include "..\include\DoubleSlider.h"

/////////////////////////////////////////////////////////////////////////////
// CMusicSearchWnd frame

class CMusicSearchWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMusicSearchWnd)
public:
	CMusicSearchWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CReBar*			m_pRebar;
	COnAirListBox*	m_pList;
	CHeaderCtrl*	m_pHeader;
	CString			m_SQLQuery;

protected:
	CEdit			*m_pArtist,
					*m_pTitle,
					*m_pRythmMin,
					*m_pRythmMax,
					*m_pLengthMin,
					*m_pLengthMax,
					*m_pIntroMin,
					*m_pIntroMax;
	CComboBox		*m_pCategory,
					*m_pPlayList,
					*m_pExpression;
	CDoubleSlider	*m_pRythm,
					*m_pLength,
					*m_pIntro;
	CImageList		*m_ilHeader; 
	WORD			m_wSortBy;
	BOOL			m_bSortAsc;

// Operations
public:
	void RefreshExpressions();
	void RefreshPlayLists();
	void RefreshCategories();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicSearchWnd)
	public:
	//}}AFX_VIRTUAL

// Implementation
protected:
	static UINT ThreadRefresh(LPVOID v);
	virtual ~CMusicSearchWnd();

	LRESULT OnDoubleChange(WPARAM Left,LPARAM ID );
	void	OnRefresh();
	void	OnPFL();
	void	OnInfo();
	void	PrepareSQL();

	// Generated message map functions
	//{{AFX_MSG(CMusicSearchWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnHeaderNotify( NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnHeaderClick( NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnCategorySelChange();
	afx_msg void OnPlayListSelChange();
	afx_msg void OnExpressionSelChange();
	afx_msg void OnItemKill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICSEARCHWND_H__5E6A893F_4029_4B4F_8D6D_7265EA200658__INCLUDED_)
