// NewsRoomDoc.h : interface of the CNewsRoomDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWSROOMDOC_H__0803F816_866E_49A1_8854_5A0E6CB1DCD1__INCLUDED_)
#define AFX_NEWSROOMDOC_H__0803F816_866E_49A1_8854_5A0E6CB1DCD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNewsRoomDoc : public CDocument
{
protected: // create from serialization only
	CNewsRoomDoc();
	DECLARE_DYNCREATE(CNewsRoomDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewsRoomDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNewsRoomDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNewsRoomDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSROOMDOC_H__0803F816_866E_49A1_8854_5A0E6CB1DCD1__INCLUDED_)
