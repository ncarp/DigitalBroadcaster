// BroadcasterMusicDoc.h : interface of the CBroadcasterMusicDoc class
//


#pragma once


class CBroadcasterMusicDoc : public CDocument
{
protected: // create from serialization only
	CBroadcasterMusicDoc();
	DECLARE_DYNCREATE(CBroadcasterMusicDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CBroadcasterMusicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


