#if !defined(AFX_PRODUCERMUSICEDITING_H__98572CDE_0743_4EF4_B758_211141AF094A__INCLUDED_)
#define AFX_PRODUCERMUSICEDITING_H__98572CDE_0743_4EF4_B758_211141AF094A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProducerMusicEditing.h : header file
//
#include "Recorder.h"
/////////////////////////////////////////////////////////////////////////////
// CProducerMusicEditing window

class CProducerMusicEditing : public CWnd
{
// Construction
public:
	CProducerMusicEditing();

// Attributes
public:
	CEdit		*m_pArtist,
				*m_pTitle,
				*m_pRythmV,
				*m_pProducer,
				*m_pLyrics,
				*m_pComposer,
				*m_pStudio,
				*m_pMusicians,
				*m_pRemarks;
	CComboBox	*m_pCategory,
				*m_pExpression,
				*m_pCDTitle,
				*m_pLabel;
	CSliderCtrl *m_pRythm;
	CDateTimeCtrl *m_pDate;
	CRecorder	*m_pRecorder;

	long		m_Artist,
				m_Category,
				m_Expression,
				m_Rythm,
				m_Record,
				m_Label,
				m_PathID;
	int			m_nPos;
	CString		m_ArtistName,
				m_SongTitle,
				m_FileName,
				m_FileType;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProducerMusicEditing)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetFile( long lPathID,CString strFileName,CString strFileType=".wav");
	BOOL SaveSong();
	virtual ~CProducerMusicEditing();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProducerMusicEditing)
	afx_msg void OnPaint();
	afx_msg void OnCategoryChange();
	afx_msg void OnCategoryKill();
	afx_msg void OnExpressionChange();
	afx_msg void OnExpressionKill();
	afx_msg void OnRecordKill();
	afx_msg void OnRecordChange();
	afx_msg void OnLabelChange();
	afx_msg void OnLabelKill();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRODUCERMUSICEDITING_H__98572CDE_0743_4EF4_B758_211141AF094A__INCLUDED_)
