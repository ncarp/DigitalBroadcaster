// OnAirManagementDoc.h : interface of the COnAirManagementDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONAIRMANAGEMENTDOC_H__30255C7D_5D43_4FF2_AF2D_F5B5A9DA30EA__INCLUDED_)
#define AFX_ONAIRMANAGEMENTDOC_H__30255C7D_5D43_4FF2_AF2D_F5B5A9DA30EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COnAirManagementDoc : public CDocument
{
protected: // create from serialization only
	COnAirManagementDoc();
	DECLARE_DYNCREATE(COnAirManagementDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnAirManagementDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COnAirManagementDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COnAirManagementDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONAIRMANAGEMENTDOC_H__30255C7D_5D43_4FF2_AF2D_F5B5A9DA30EA__INCLUDED_)
