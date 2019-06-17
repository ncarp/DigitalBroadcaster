// MusicTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "MusicTemplate.h"
#include "MusicSelector.h"
#include "..\include\Utils.h"
#include "..\include\RSCategories.h"
#include "..\include\RSExpressions.h"
#include "..\include\RSPlayListsDefinition.h"
#include "..\include\RSViewMusicSchedulingSata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString	g_strMainConnect;
/////////////////////////////////////////////////////////////////////////////
// CMusicTemplate dialog


CMusicTemplate::CMusicTemplate(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicTemplate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMusicTemplate)
	m_MaxLen = 900;
	m_strMaxLen = _T("");
	m_MaxRythm = 250;
	m_strMAxRythm = _T("");
	m_MinLen = 0;
	m_strMinLen = _T("");
	m_MinRythm = 0;
	m_strMinRythm = _T("");
	m_strName = _T("");
	m_Category = -1;
	m_Expression = -1;
	m_List = -1;
	m_nArtistQuarantine = 0;
	m_nRandom = 0;
	m_nSongQuarantine = 0;
	//}}AFX_DATA_INIT
	m_TemplateID = 0;
}


void CMusicTemplate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMusicTemplate)
	DDX_Control(pDX, IDC_RANDOM, m_cRandom);
	DDX_Control(pDX, IDC_MINRYTHM, m_cMinRythm);
	DDX_Control(pDX, IDC_MINLEN, m_cMinLen);
	DDX_Control(pDX, IDC_MAXRYTHM, m_cMaxRythm);
	DDX_Control(pDX, IDC_MAXLEN, m_cMaxLen);
	DDX_Control(pDX, IDC_PLAYLIST, m_cPlayList);
	DDX_Control(pDX, IDC_EXPRESSION, m_cExpression);
	DDX_Control(pDX, IDC_CATEGORIES, m_cCategories);
	DDX_Slider(pDX, IDC_MAXLEN, m_MaxLen);
	DDX_Text(pDX, IDC_MAXLENV, m_strMaxLen);
	DDX_Slider(pDX, IDC_MAXRYTHM, m_MaxRythm);
	DDX_Text(pDX, IDC_MAXRYTHMV, m_strMAxRythm);
	DDX_Slider(pDX, IDC_MINLEN, m_MinLen);
	DDX_Text(pDX, IDC_MINLENV, m_strMinLen);
	DDX_Slider(pDX, IDC_MINRYTHM, m_MinRythm);
	DDX_Text(pDX, IDC_MINRYTHMV, m_strMinRythm);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_CBIndex(pDX, IDC_CATEGORIES, m_Category);
	DDX_CBIndex(pDX, IDC_EXPRESSION, m_Expression);
	DDX_CBIndex(pDX, IDC_PLAYLIST, m_List);
	DDX_Text(pDX, IDC_ARTIST_Q, m_nArtistQuarantine);
	DDX_Slider(pDX, IDC_RANDOM, m_nRandom);
	DDX_Text(pDX, IDC_SONG_Q, m_nSongQuarantine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMusicTemplate, CDialog)
	//{{AFX_MSG_MAP(CMusicTemplate)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, OnTestCriteria)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMusicTemplate message handlers

BOOL CMusicTemplate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int		Pos;
	CString str;
	str.LoadString(IDS_IRRELEVANTCRITERIA);

	Pos=m_cCategories.AddString("* "+str);
	m_cCategories.SetItemData(Pos,0);

	CRSCategories rsCat( g_strMainConnect );
	rsCat.m_strFilter="Activ = 1";
	rsCat.m_strSort="Name";
	rsCat.Open();

	while( !rsCat.IsEOF() )
	{
		rsCat.m_Name.TrimRight();

		Pos=m_cCategories.AddString(rsCat.m_Name);
		m_cCategories.SetItemData(Pos,rsCat.m_ID);

		rsCat.MoveNext();
	}
	rsCat.Close();

	Pos = m_cPlayList.AddString("* "+str);
	m_cPlayList.SetItemData(Pos,0);

	CRSPlayListsDefinition rsList( m_strConnect );
	rsList.m_strFilter = "Activ = 1 AND OnAir = 1";
	rsList.m_strSort = "Name";
	rsList.Open();

	while( !rsList.IsEOF() )
	{
		rsList.m_Name.TrimRight();

		Pos = m_cPlayList.AddString( rsList.m_Name);
		m_cPlayList.SetItemData(Pos,rsList.m_ID);

		rsList.MoveNext();
	}
	rsList.Close();

	Pos = m_cExpression.AddString("* "+str);
	m_cExpression.SetItemData(Pos,0);

	CRSExpressions rsExp( g_strMainConnect );
	rsExp.m_strFilter = "Activ = 1";
	rsExp.m_strSort = "Name";
	rsExp.Open();

	while( !rsExp.IsEOF() )
	{
		rsExp.m_Name.TrimRight();

		Pos=m_cExpression.AddString(rsExp.m_Name);
		m_cExpression.SetItemData(Pos,rsExp.m_ID);

		rsExp.MoveNext();
	}
	rsExp.Close();

	m_cMaxRythm.SetRange(0,250,TRUE);
	m_cMinRythm.SetRange(0,250,TRUE);
	m_cMaxRythm.SetPos(m_MaxRythm);
	m_cMinRythm.SetPos(m_MinRythm);

	m_cMaxLen.SetRange(0,900,TRUE);
	m_cMaxLen.SetPos(m_MaxLen);
	m_cMinLen.SetRange(0,900,TRUE);
	m_cMinLen.SetPos(m_MinLen);

	if( m_TemplateID!=0 )
	{
		Pos = m_cExpression.FindStringExact(-1,m_strExpression);
		if( Pos==CB_ERR )
			m_ExpressionID = 0;
		else
			m_cExpression.SetCurSel(Pos);

		Pos = m_cCategories.FindStringExact(-1,m_strCategory);
		if( Pos==CB_ERR )
			m_CategoryID = 0;
		else
			m_cCategories.SetCurSel(Pos);

		Pos = m_cPlayList.FindStringExact(-1,m_strPlayList);
		if( Pos==CB_ERR )
			m_PlayListID = 0;
		else
			m_cPlayList.SetCurSel(Pos);

		OnHScroll(0,0,0);
	}

	m_cRandom.SetRange(1,10,TRUE);
	return TRUE;  
}

void CMusicTemplate::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UpdateData();
	
	if( m_MinRythm == 0 )
		m_strMinRythm="";
	else
		m_strMinRythm.Format("%d bmp",m_MinRythm);

	if( m_MaxRythm == 250 )
		m_strMAxRythm="";
	else
		m_strMAxRythm.Format("%d bpm",m_MaxRythm);

	if( m_MinLen == 0 )
		m_strMinLen = "";
	else
	{
		GetTimeString(m_MinLen*1000,&m_strMinLen);
		m_strMinLen.Delete(0,3);
		m_strMinLen.Delete(5,4);
	}

	if( m_MaxLen == 900 )
		m_strMaxLen = "";
	else
	{
		GetTimeString(m_MaxLen*1000,&m_strMaxLen);
		m_strMaxLen.Delete(0,3);
		m_strMaxLen.Delete(5,4);
	}

	UpdateData(FALSE);
}

void CMusicTemplate::ComputeSQL()
{
	CString newSQL="",
			strTemp;

	UpdateData();

	
	///////////////////////////////////////////////////////////////////////

	if( m_Category==CB_ERR )
		m_CategoryID=0;
	else
		m_CategoryID=m_cCategories.GetItemData(m_Category);

	if( m_CategoryID!=0 )
	{
		strTemp.Format("(CategoryID = '%d')",m_CategoryID);
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////
	//	Play List
	if( m_List==CB_ERR )
		m_PlayListID=0;
	else
		m_PlayListID=m_cPlayList.GetItemData(m_List);

	if( m_PlayListID!=0 )
	{
		strTemp.Format("TrackID in (Select MusicTrackID from [PlayLists-Contents] where ListID = '%d')",m_PlayListID);
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}
	
	
	///////////////////////////////////////////////////////////////////////
	//	Expression
	if( m_Expression==CB_ERR )
		m_ExpressionID=0;
	else
		m_ExpressionID=m_cExpression.GetItemData(m_Expression);
	
	if( m_ExpressionID!=0 )
	{
		strTemp.Format("(LanguageID = '%d')",m_ExpressionID);
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////
	//	Rythm

	if( (m_MinRythm!=0) || (m_MaxRythm!=250) )
	{
		if( (m_MinRythm!=0) && (m_MaxRythm!=250) )
			strTemp.Format("TrackRythm >= '%d' AND TrackRythm <= '%d'",m_MinRythm,m_MaxRythm);
		else if (m_MinRythm!=0)
			strTemp.Format("TrackRythm >= '%d'",m_MinRythm);
		else
			strTemp.Format("TrackRythm <= '%d'",m_MaxRythm);

		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	///////////////////////////////////////////////////////////////////////
	//	Length

	if( (m_MinLen!=0) || (m_MaxLen!=900) )
	{
		if( (m_MinLen!=0) && (m_MaxLen!=900) )
			strTemp.Format("TrackLength >= '%d' AND TrackLength <= '%d'",m_MinLen*1000,m_MaxLen*1000);
		else if( m_MinLen!=0 )
			strTemp.Format("TrackLength >= '%d' ",m_MinLen*1000);
		else
			strTemp.Format("TrackLength <= '%d'",m_MaxLen*1000);
			
		if( newSQL.GetLength() )
			newSQL=newSQL+" AND "+strTemp;
		else
			newSQL=strTemp;
	}

	if( newSQL != m_strSQL )
	{
		m_strSQL = newSQL;
	}

}

void CMusicTemplate::OnTestCriteria() 
{
	ComputeSQL();

	CMusicSelector dl;
	dl.m_strConnect = m_strConnect;
	dl.m_strSQL = m_strSQL;

	dl.DoModal();
}

void CMusicTemplate::OnOK() 
{
	UpdateData();
	ComputeSQL();

	m_strName.TrimRight();
	if( m_strName.GetLength()==0 )
		return;

	CRSViewMusicSchedulingSata rs( m_strConnect );
	rs.m_strFilter = m_strSQL;
	rs.Open();
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		AfxMessageBox(IDS_INVALIDCRITERIA);
		return;
	}
	rs.Close();

	CDialog::OnOK();
}
