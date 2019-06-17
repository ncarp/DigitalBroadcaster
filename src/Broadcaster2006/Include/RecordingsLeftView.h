#if !defined(AFX_RECORDINGSLEFTVIEW_H__559DCCE7_0526_4F65_B4E3_D32B3D8FD97A__INCLUDED_)
#define AFX_RECORDINGSLEFTVIEW_H__559DCCE7_0526_4F65_B4E3_D32B3D8FD97A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordingsLeftView.h : header file
//
#include "..\include\DigitalLeftView.h"

/////////////////////////////////////////////////////////////////////////////
// CRecordingsLeftView view

class CRecordingsLeftView : public CDigitalLeftView
{
protected:
	CRecordingsLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRecordingsLeftView)

// Attributes
public:
	BOOL	m_bIsRefreshing;
// Operations
public:
			void	OnDoubleClick();
			void	OnNew();
			void	OnCut();
			void	OnPFL();
	virtual void	OnSelChange();
	static	UINT	RefreshList(LPVOID);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordingsLeftView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRecordingsLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRecordingsLeftView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDINGSLEFTVIEW_H__559DCCE7_0526_4F65_B4E3_D32B3D8FD97A__INCLUDED_)
