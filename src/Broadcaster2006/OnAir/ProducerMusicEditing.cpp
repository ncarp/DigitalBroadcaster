// ProducerMusicEditing.cpp : implementation file
//

#include "stdafx.h"
#include "onair.h"
#include "ProducerMusicEditing.h"
#include "ExternalObjects.h"
#include "RSRecord.h"
#include "..\common\include\utils.h"
#include "..\include\RSExpressions.h"
#include "..\include\RSCategories.h"
#include "..\include\RSRecordLabel.h"
#include "..\include\RSPath.h"
#include "..\include\RSArtists.h"
#include "..\include\RSViewMusicFiles.h"
#include "..\include\RSMusicTracks.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_ARTIST		1001
#define	ID_TITLE		1002
#define ID_CATEGORY		1003
#define ID_EXPRESSION	1004
#define ID_RYTHM		1005
#define ID_RYTHMV		1006
#define ID_CDTITLE		1007
#define ID_CDDATE		1008
#define ID_LABEL		1009

/////////////////////////////////////////////////////////////////////////////
// CProducerMusicEditing

CProducerMusicEditing::CProducerMusicEditing()
{
	m_Artist=0;
	m_Category=0;
	m_Expression=0;
	m_Record=0;
	m_Label=0;
}

CProducerMusicEditing::~CProducerMusicEditing()
{
}


BEGIN_MESSAGE_MAP(CProducerMusicEditing, CWnd)
	//{{AFX_MSG_MAP(CProducerMusicEditing)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(ID_CATEGORY,OnCategoryChange)
	ON_CBN_KILLFOCUS(ID_CATEGORY,OnCategoryKill)
	ON_CBN_SELCHANGE(ID_EXPRESSION,OnExpressionChange)
	ON_CBN_KILLFOCUS(ID_EXPRESSION,OnExpressionKill)
	ON_CBN_KILLFOCUS(ID_CDTITLE,OnRecordKill)
	ON_CBN_SELCHANGE(ID_CDTITLE,OnRecordChange)
	ON_CBN_SELCHANGE(ID_LABEL,OnLabelChange)
	ON_CBN_KILLFOCUS(ID_LABEL,OnLabelKill)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProducerMusicEditing message handlers

void CProducerMusicEditing::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	rect;
	GetClientRect(&rect);

	dc.FillRect(rect,&CBrush(GetSysColor(COLOR_3DFACE)));
}

int CProducerMusicEditing::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CString	str;
	CStatic	*s;
	CRect	rect(10,12,100,30);
	CRect	crect;

	GetClientRect(&crect);
		
	str.LoadString(IDS_ARTIST);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_SONGTITLE);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,35);
	str.LoadString(IDS_CATEGORY);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_EXPRESSION);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_RYTHM);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,35);
	str.LoadString(IDS_CDTITLE);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_RECORDINGDATE);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_RECORDLABEL);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,35);
	str.LoadString(IDS_MUSICPRODUCER);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_MUSICCOMPOSER);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_LYRICS);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_MUSICIANS);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,100);
	str.LoadString(IDS_STUDIO);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	rect.OffsetRect(0,24);
	str.LoadString(IDS_REMARKS);
	s=new CStatic();
	s->Create(str,WS_VISIBLE|SS_RIGHT,rect,this);

	///////////////////////////////////////////////////////////////////////
	//	Create the input controls
	rect=CRect(105,10,crect.right-10,34);
	m_pArtist = new CEdit();
	m_pArtist->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_GROUP|WS_CHILD|WS_VISIBLE,rect,this,ID_ARTIST);

	rect.OffsetRect(0,24);
	m_pTitle = new CEdit();
	m_pTitle->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_TITLE);
	
	rect.OffsetRect(0,35);
	rect.InflateRect(0,0,0,200);
	str.LoadString(IDS_REFRESH);

	m_pCategory = new CComboBox();
	m_pCategory->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWN|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_CATEGORY);
	m_pCategory->AddString("* "+str);
	m_pCategory->SetItemData(0,0);
	
	rect.OffsetRect(0,24);

	m_pExpression = new CComboBox();
	m_pExpression->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWN|WS_VSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_EXPRESSION);
	m_pExpression->AddString("* "+str);
	m_pExpression->SetItemData(0,0);

	rect.OffsetRect(0,24);
	rect.DeflateRect(0,0,70,200);
	m_pRythm = new CSliderCtrl();
	m_pRythm->Create(WS_VISIBLE|TBS_HORZ,rect,this,ID_RYTHM);
	m_pRythm->SetRange(0,250);
	
	m_pRythmV = new CEdit();
	m_pRythmV->CreateEx(WS_EX_RIGHT|WS_EX_CLIENTEDGE,"Edit","0 bpm",ES_READONLY|WS_TABSTOP|WS_CHILD|WS_VISIBLE,
		CRect(rect.right+5,rect.top,rect.right+70,rect.bottom),
		this,ID_RYTHMV);

	rect.InflateRect(0,0,70,200);
	rect.OffsetRect(0,35);

	m_pCDTitle = new CComboBox();
	m_pCDTitle->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWN|WS_TABSTOP|WS_VSCROLL|WS_CHILD|WS_VISIBLE,rect,this,ID_CDTITLE);
	m_pCDTitle->AddString("* "+str);
	m_pCDTitle->SetItemData(0,0);

	rect.OffsetRect(0,24);
	rect.DeflateRect(0,0,0,200);
	m_pDate = new CDateTimeCtrl();
	m_pDate->Create(WS_VISIBLE|DTS_SHORTDATECENTURYFORMAT,rect,this,ID_CDDATE);

	rect.OffsetRect(0,24);
	rect.InflateRect(0,0,0,200);
	m_pLabel = new CComboBox();
	m_pLabel->CreateEx(WS_EX_CLIENTEDGE,"ComboBox",NULL,CBS_DROPDOWN|WS_TABSTOP|WS_VSCROLL|WS_CHILD|WS_VISIBLE,rect,this,ID_LABEL);
	m_pLabel->AddString("* "+str);
	m_pLabel->SetItemData(0,0);

	rect.OffsetRect(0,35);
	rect.DeflateRect(0,0,0,200);
	m_pProducer = new CEdit();
	m_pProducer->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rect,this,ID_TITLE);

	rect.OffsetRect(0,24);
	m_pComposer = new CEdit();
	m_pComposer->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rect,this,ID_TITLE);

	rect.OffsetRect(0,24);
	m_pLyrics = new CEdit();
	m_pLyrics->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rect,this,ID_TITLE);

	rect.OffsetRect(0,24);
	rect.InflateRect(0,0,0,76);
	m_pMusicians = new CEdit();
	m_pMusicians->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_VSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_TITLE);

	rect.OffsetRect(0,100);
	rect.DeflateRect(0,0,0,76);
	m_pStudio = new CEdit();
	m_pStudio->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_TABSTOP|WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL,rect,this,ID_TITLE);

	rect.OffsetRect(0,24);
	rect.InflateRect(0,0,0,76);
	m_pRemarks = new CEdit();
	m_pRemarks->CreateEx(WS_EX_CLIENTEDGE,"Edit",NULL,WS_VSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_TABSTOP|WS_CHILD|WS_VISIBLE,rect,this,ID_TITLE);

	rect.OffsetRect(0,120);
	rect.InflateRect(105,0,10,175);
	m_pRecorder=new CRecorder();
	m_pRecorder->Create(NULL,WS_VISIBLE,rect,this);

	m_nPos=0;
	if( rect.bottom > crect.bottom )
		SetScrollRange(SB_VERT,0,rect.bottom-crect.bottom);
	else
		SetScrollRange(SB_VERT,0,0);

	return 0;	
}

void CProducerMusicEditing::OnCategoryChange ()
{
	long Pos=m_pCategory->GetCurSel();
	long Data=m_pCategory->GetItemData(Pos);

	m_Category=Data;

	if( Data==0 )
	{
		CRSCategories	rs(g_strMainConnect);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Name";
		rs.Open();

		m_pCategory->ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_pCategory->AddString(rs.m_Name);
			m_pCategory->SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}
		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_pCategory->AddString("* "+str);
		m_pCategory->SetItemData(Pos,0);
	}
	else
	{
		m_Category=Data;
	}
}

void CProducerMusicEditing::OnCategoryKill()
{
	CString str;
	m_pCategory->GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_Category=0;
		return;	
	}

	CRSCategories	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();
	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_pCategory->SetWindowText(rs.m_Name);
		m_Category=rs.m_ID;

		if( rs.m_Activ==0 )
		{
			rs.Edit();
			rs.m_Activ=1;
			rs.Update();
		}
	}
	else
	{
		if( AfxMessageBox(IDS_NEWCATEGORY,MB_YESNO)==IDYES )
		{
			m_pCategory->GetWindowText(str);
			str.TrimRight();
			str.MakeUpper();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_Category=rs.m_ID;

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_MUSICCATEGORIE,m_Category);
		}
		else
		{
			m_pCategory->SetWindowText("");
			m_Category=0;
		}
	}
}

void CProducerMusicEditing::OnExpressionChange ()
{
	long Pos=m_pExpression->GetCurSel();
	long Data=m_pExpression->GetItemData(Pos);

	m_Expression=Data;

	if( Data==0 )
	{
		CRSExpressions	rs(g_strMainConnect);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Name";
		rs.Open();

		m_pExpression->ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_pExpression->AddString(rs.m_Name);
			m_pExpression->SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}
		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_pExpression->AddString("* "+str);
		m_pExpression->SetItemData(Pos,0);
	}
}	

void CProducerMusicEditing::OnExpressionKill()
{
	CString str;
	m_pExpression->GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_Expression=0;
		return;	
	}

	CRSExpressions	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_pExpression->SetWindowText(rs.m_Name);
		m_Expression=rs.m_ID;

		if( rs.m_Activ==0 )
		{
			rs.Edit();
			rs.m_Activ=1;
			rs.Update();
		}
	}
	else
	{
		if( AfxMessageBox(IDS_NEWEXPRESSION,MB_YESNO)==IDYES )
		{
			m_pExpression->GetWindowText(str);
			str.TrimRight();
			str.MakeUpper();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_Expression=rs.m_ID;

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_EXPRESSION,m_Expression);
		}
		else
		{
			m_pExpression->SetWindowText("");
			m_Expression=0;
		}
	}
}

void CProducerMusicEditing::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Rythm=m_pRythm->GetPos();
	CString str;
	str.Format("%d bpm",m_Rythm);
	m_pRythmV->SetWindowText(str);		

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CProducerMusicEditing::OnRecordChange()
{
	long Pos=m_pCDTitle->GetCurSel();
	long Data=m_pCDTitle->GetItemData(Pos);

	m_Record=Data;

	if( Data==0 )
	{
		CRSRecord	rs(g_strMainConnect);
		rs.m_strFilter.Format("ArtistID = '0' OR ArtistID = '%d'",m_Artist);
		rs.m_strSort="Title";
		rs.Open();

		m_pCDTitle->ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Title.TrimRight();
			Pos=m_pCDTitle->AddString(rs.m_Title);
			m_pCDTitle->SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}

		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_pCDTitle->AddString("* "+str);
		m_pCDTitle->SetItemData(Pos,0);
	}
}

void CProducerMusicEditing::OnRecordKill()
{
	CString str;
	m_pCDTitle->GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_Record=0;
		return;	
	}

	CRSRecord	rs(g_strMainConnect);
	rs.m_strFilter.Format("Title = '%s' AND ArtistID='%d'",str,m_Artist);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Title.TrimRight();
		m_pCDTitle->SetWindowText(rs.m_Title);
		m_Record=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWRECORD,MB_YESNO)==IDYES )
		{
			m_pCDTitle->GetWindowText(str);
			str.TrimRight();

			rs.AddNew();
			rs.m_ArtistID=m_Artist;
			rs.m_Title=str;
			rs.Update();

			rs.Requery();
			m_Record=rs.m_ID;

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_RECORD,m_Record);
		}
		else
		{
			m_pCDTitle->SetWindowText("");
			m_Record=0;
		}
	}
}

void CProducerMusicEditing::OnLabelChange()
{
	long Pos=m_pLabel->GetCurSel();
	long Data=m_pLabel->GetItemData(Pos);

	m_Label=Data;

	if( Data==0 )
	{
		CRSRecordLabel	rs(g_strMainConnect);
		rs.m_strFilter="Activ <> 0";
		rs.m_strSort="Name";
		rs.Open();

		m_pLabel->ResetContent();
	
		while( !rs.IsEOF() )
		{
			rs.m_Name.TrimRight();
			Pos=m_pLabel->AddString(rs.m_Name);
			m_pLabel->SetItemData(Pos,rs.m_ID);
			rs.MoveNext();
		}

		CString str;
		str.LoadString(IDS_REFRESH);
		Pos=m_pLabel->AddString("* "+str);
		m_pLabel->SetItemData(Pos,0);
	}
}

void CProducerMusicEditing::OnLabelKill()
{
	CString str;
	m_pLabel->GetWindowText(str);
	str.TrimRight();
	str.Replace("'","''");

	if(str.GetLength()==0)
	{
		m_Label=0;
		return;	
	}

	CRSRecordLabel	rs(g_strMainConnect);
	rs.m_strFilter.Format("Name = '%s'",str);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Name.TrimRight();
		m_pLabel->SetWindowText(rs.m_Name);
		m_Label=rs.m_ID;
	}
	else
	{
		if( AfxMessageBox(IDS_NEWLABEL,MB_YESNO)==IDYES )
		{
			m_pLabel->GetWindowText(str);
			str.TrimRight();

			rs.AddNew();
			rs.m_Activ=1;
			rs.m_Name=str;
			rs.Update();

			rs.Requery();
			m_Label=rs.m_ID;

			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_RECORDLABEL,m_Label);
		}
		else
		{
			m_pLabel->SetWindowText("");
			m_Label=0;
		}
	}
}

void CProducerMusicEditing::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch( nSBCode )
	{
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK: 
		SetScrollPos(SB_VERT,nPos);
		ScrollWindow(0,m_nPos-nPos);
		m_nPos=nPos;
		break;
	}
}

BOOL CProducerMusicEditing::SetFile(long lPathID, CString strFileName, CString strFileType)
{
	CRSPath	rs(g_strMainConnect);

	int Pos = strFileName.Find(" - ",0);
	m_ArtistName=strFileName.Mid(0,Pos);
	m_SongTitle=strFileName.Mid(Pos+3);
	m_SongTitle.Delete(m_SongTitle.GetLength()-4,4);
	m_FileType = GetFileType(strFileName);
	
	m_pArtist->SetWindowText(m_ArtistName);
	m_pTitle->SetWindowText(m_SongTitle);

	rs.m_strFilter.Format("ID = '%d'",lPathID);
	rs.Open();
	
	rs.m_Path.TrimRight();
	CString strCompleteFileName=rs.m_Path+"\\"+strFileName;
	rs.Close();

	CString strTemp=strCompleteFileName;
	strTemp.Replace("'","''");

	CRSViewMusicFiles	rsFiles(g_strMainConnect);
	rsFiles.m_strFilter.Format("FileName = '%s'",strTemp);
	rsFiles.Open();

	if( rsFiles.GetRecordCount() )
	{
		rsFiles.Close();
		return FALSE;
	}
	rsFiles.Close();

	strTemp=m_ArtistName;
	strTemp.Replace("'","''");

	CRSArtists rsArtist( g_strMainConnect,NULL );
	rsArtist.m_strFilter.Format("Name = '%s'",strTemp);
	rsArtist.Open();

	if( rsArtist.GetRecordCount() )
		m_Artist = rsArtist.m_ID;
	else
	{
		rsArtist.AddNew();
		rsArtist.m_Activ=1;
		rsArtist.m_Name=m_ArtistName;
		rsArtist.Update();
		rsArtist.Requery();
		m_Artist = rsArtist.m_ID;

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_ARTIST,m_Artist);
	}
	m_pRecorder->SetFile(strCompleteFileName);
	
	m_PathID = lPathID;
	
	m_pCategory->SetCurSel(-1);
	m_pExpression->SetCurSel(-1);
	m_pCDTitle->SetCurSel(-1);
	m_pLabel->SetCurSel(-1);
	m_pProducer->SetWindowText("");
	m_pComposer->SetWindowText("");
	m_pLyrics->SetWindowText("");
	m_pMusicians->SetWindowText("");
	m_pStudio->SetWindowText("");
	m_pRemarks->SetWindowText("");

	return TRUE;
}

BOOL CProducerMusicEditing::SaveSong()
{
	if( (m_Category==0) || (m_Expression==0) )
	{
		AfxMessageBox(IDS_SONGMANDATORY);
		return FALSE;
	}

	CRSMusicTracks rs(g_strMainConnect);
	COleDateTime dt;

	m_pDate->GetTime(dt);

	rs.Open();
	rs.AddNew();

	rs.m_ArtistID=m_Artist;
	rs.m_Title=m_SongTitle;
	rs.m_CategoryID=m_Category;
	rs.m_LanguageID=m_Expression;
	rs.m_Rythm=m_Rythm;
	rs.m_RecordID=m_Record;
	rs.m_Date.year=dt.GetYear();
	rs.m_Date.month=dt.GetMonth();
	rs.m_Date.day=dt.GetDay();
	rs.m_Date.hour=0;
	rs.m_Date.minute=0;
	rs.m_Date.second=0;
	rs.m_Date.fraction=0;
	rs.m_RecordLabelID=m_Label;
	m_pProducer->GetWindowText(rs.m_Producer);
	m_pComposer->GetWindowText(rs.m_Music);
	m_pLyrics->GetWindowText(rs.m_Lyrics);
	m_pMusicians->GetWindowText(rs.m_Musicians);
	m_pStudio->GetWindowText(rs.m_Studio);
	m_pRemarks->GetWindowText(rs.m_Obs);
	rs.m_Start	= m_pRecorder->m_pTimer->m_Start;
	rs.m_FadeIn	= m_pRecorder->m_pTimer->m_FadeIn;
	rs.m_Intro	= m_pRecorder->m_pTimer->m_Intro;
	rs.m_FadeOut= m_pRecorder->m_pTimer->m_FadeOut;
	rs.m_Mix	= m_pRecorder->m_pTimer->m_Mix;
	rs.m_Finish	= m_pRecorder->m_pTimer->m_End;
	rs.m_LoopA	= m_pRecorder->m_pTimer->m_LoopA;
	rs.m_LoopB	= m_pRecorder->m_pTimer->m_LoopB;
	rs.m_Activ = 1;
	rs.m_Available = 1;
	rs.m_FileType = m_FileType;
	rs.m_PathID = m_PathID;
	
	if( rs.m_Intro<rs.m_Start ) rs.m_Intro=rs.m_Start;


	rs.Update();

	rs.m_strFilter.Format("ArtistID='%d'",m_Artist);
	rs.m_strSort="ID DESC";
	rs.Requery();

	WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_MUSIC,rs.m_ID);

	rs.Close();

	m_pRecorder->KillFile();

	return TRUE;
}
