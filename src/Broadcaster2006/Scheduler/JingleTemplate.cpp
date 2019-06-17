// JingleTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "Scheduler.h"
#include "JingleTemplate.h"
#include "JingleSelector.h"
#include "..\include\RSViewJinglesSchedulingData.h"
#include "..\include\utils.h"
#include "..\include\RSTypeOfJingle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJingleTemplate dialog
extern CString	g_strMainConnect;

CJingleTemplate::CJingleTemplate(CWnd* pParent /*=NULL*/)
	: CDialog(CJingleTemplate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJingleTemplate)
	m_Category = -1;
	m_MaxLen = 300;
	m_strMaxLenV = _T("");
	m_MaxRythm = 250;
	m_strMaxRythm = _T("");
	m_MinLen = 0;
	m_strMinLenV = _T("");
	m_MinRythm = 0;
	m_strName = _T("");
	m_strMinRythmV = _T("");
	//}}AFX_DATA_INIT
	m_TemplateID = 0;
}

void CJingleTemplate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJingleTemplate)
	DDX_Control(pDX, IDC_MINRYTHM, m_cMinRythm);
	DDX_Control(pDX, IDC_MINLEN, m_cMinLen);
	DDX_Control(pDX, IDC_MAXRYTHM, m_cMaxRythm);
	DDX_Control(pDX, IDC_MAXLEN, m_cMaxLen);
	DDX_Control(pDX, IDC_CATEGORY, m_cCategory);
	DDX_CBIndex(pDX, IDC_CATEGORY, m_Category);
	DDX_Slider(pDX, IDC_MAXLEN, m_MaxLen);
	DDX_Text(pDX, IDC_MAXLENV, m_strMaxLenV);
	DDX_Slider(pDX, IDC_MAXRYTHM, m_MaxRythm);
	DDX_Text(pDX, IDC_MAXRYTHMV, m_strMaxRythm);
	DDX_Slider(pDX, IDC_MINLEN, m_MinLen);
	DDX_Text(pDX, IDC_MINLENV, m_strMinLenV);
	DDX_Slider(pDX, IDC_MINRYTHM, m_MinRythm);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_MINRYTHMV, m_strMinRythmV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJingleTemplate, CDialog)
	//{{AFX_MSG_MAP(CJingleTemplate)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, OnTestCriteria)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJingleTemplate message handlers

BOOL CJingleTemplate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRSTypeOfJingle rsCat( g_strMainConnect );
	rsCat.m_strFilter="Activ = 1";
	rsCat.m_strSort="Name";
	rsCat.Open();

	int	Pos;
	
	CString str;
	
	str.LoadString(IDS_IRRELEVANTCRITERIA);
	Pos=m_cCategory.AddString("* "+str);
	m_cCategory.SetItemData(Pos,0);

	while( !rsCat.IsEOF() )
	{
		rsCat.m_Name.TrimRight();

		Pos=m_cCategory.AddString(rsCat.m_Name);
		m_cCategory.SetItemData(Pos,rsCat.m_ID);

		rsCat.MoveNext();
	}
	rsCat.Close();

	m_cMaxRythm.SetRange(0,250,TRUE);
	m_cMinRythm.SetRange(0,250,TRUE);
	m_cMaxRythm.SetPos(m_MaxRythm);
	m_cMinRythm.SetPos(m_MinRythm);

	m_cMaxLen.SetRange(0,300,TRUE);
	m_cMaxLen.SetPos(m_MaxLen);
	m_cMinLen.SetRange(0,300,TRUE);
	m_cMinLen.SetPos(m_MinLen);
	
	if( m_TemplateID!=0 )
	{
		Pos = m_cCategory.FindStringExact(-1,m_strType);
		if( Pos==CB_ERR )
			m_CategoryID = 0;
		else
			m_cCategory.SetCurSel(Pos);

		OnHScroll(0,0,0);
	}
		
	return TRUE;
}

void CJingleTemplate::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UpdateData();
	
	if( m_MinRythm == 0 )
		m_strMinRythmV="";
	else
		m_strMinRythmV.Format("%d bmp",m_MinRythm);

	if( m_MaxRythm == 250 )
		m_strMaxRythm="";
	else
		m_strMaxRythm.Format("%d bpm",m_MaxRythm);

	if( m_MinLen == 0 )
		m_strMinLenV = "";
	else
	{
		GetTimeString(m_MinLen*1000,&m_strMinLenV);
		m_strMinLenV.Delete(0,3);
		m_strMinLenV.Delete(5,4);
	}

	if( m_MaxLen == 300 )
		m_strMaxLenV = "";
	else
	{
		GetTimeString(m_MaxLen*1000,&m_strMaxLenV);
		m_strMaxLenV.Delete(0,3);
		m_strMaxLenV.Delete(5,4);
	}

	UpdateData(FALSE);
}

void CJingleTemplate::ComputeSQL()
{
	CString newSQL="",
			strTemp;

	UpdateData();

	///////////////////////////////////////////////////////////////////////

	if( m_Category==CB_ERR )
		m_CategoryID=0;
	else
		m_CategoryID=m_cCategory.GetItemData(m_Category);

	if( m_CategoryID!=0 )
	{
		strTemp.Format("(TypeID = '%d')",m_CategoryID);
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
			strTemp.Format("Rythm >= '%d' AND Rythm <= '%d'",m_MinRythm,m_MaxRythm);
		else if (m_MinRythm!=0)
			strTemp.Format("Rythm >= '%d'",m_MinRythm);
		else
			strTemp.Format("Rythm <= '%d'",m_MaxRythm);

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
			strTemp.Format("Length >= '%d' AND Length <= '%d'",m_MinLen*1000,m_MaxLen*1000);
		else if( m_MinLen!=0 )
			strTemp.Format("Length >= '%d' ",m_MinLen*1000);
		else
			strTemp.Format("Length <= '%d'",m_MaxLen*1000);
			
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

void CJingleTemplate::OnTestCriteria() 
{
	ComputeSQL();

	CJingleSelector dl;
	dl.m_strConnect = m_strConnect;
	dl.m_strSQL = m_strSQL;

	dl.DoModal();	
}


void CJingleTemplate::OnOK() 
{
	UpdateData();
	ComputeSQL();

	m_strName.TrimRight();
	if( m_strName.GetLength()==0 )
		return;

	CRSViewJinglesSchedulingData rs( m_strConnect );
	rs.m_strFilter = m_strSQL;
	rs.Open();
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		AfxMessageBox(IDS_INVALIDJINGLECRITERIA);
		return;
	}
	rs.Close();
	
	CDialog::OnOK();
}
