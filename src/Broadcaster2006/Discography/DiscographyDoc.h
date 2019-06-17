// DiscographyDoc.h : interface of the CDiscographyDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCOGRAPHYDOC_H__1BC450E1_4456_49AA_9C89_A2E2FB8BAE89__INCLUDED_)
#define AFX_DISCOGRAPHYDOC_H__1BC450E1_4456_49AA_9C89_A2E2FB8BAE89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDiscographyDoc : public CDocument
{
protected: // create from serialization only
	CDiscographyDoc();
	DECLARE_DYNCREATE(CDiscographyDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiscographyDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDiscographyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDiscographyDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISCOGRAPHYDOC_H__1BC450E1_4456_49AA_9C89_A2E2FB8BAE89__INCLUDED_)
