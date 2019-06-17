// RecordingTask.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\RecordingTask.h"
#include "..\include\RSOnAirUsers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_strMainConnect;

/////////////////////////////////////////////////////////////////////////////
// CRecordingTask dialog


CRecordingTask::CRecordingTask(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordingTask::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecordingTask)
	m_Talent = -1;
	m_Task = _T("");
	m_Deadline = COleDateTime::GetCurrentTime();
	m_Name = _T("");
	//}}AFX_DATA_INIT
	m_TalentID = 0;
	m_TalentName = "";
}


void CRecordingTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecordingTask)
	DDX_Control(pDX, IDC_TALENT, m_cTalent);
	DDX_CBIndex(pDX, IDC_TALENT, m_Talent);
	DDX_Text(pDX, IDC_TASK, m_Task);
	DDX_DateTimeCtrl(pDX, IDC_TASKDEADLINE, m_Deadline);
	DDX_Text(pDX, IDC_TASKNAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecordingTask, CDialog)
	//{{AFX_MSG_MAP(CRecordingTask)
	ON_CBN_KILLFOCUS(IDC_TALENT, OnKillfocusTalent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordingTask message handlers

void CRecordingTask::OnKillfocusTalent() 
{
	long Pos=m_cTalent.GetCurSel();
	if( Pos==CB_ERR )
	{
		m_TalentID=0;
		m_TalentName="";
	}
	else
	{
		m_TalentID = m_cTalent.GetItemData(Pos);
		m_cTalent.GetLBText(Pos,m_TalentName);
	}
}

BOOL CRecordingTask::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	long Pos;
	CRSOnAirUsers rs( g_strMainConnect );
	rs.m_strFilter="Activ = 1";
	rs.m_strSort="Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		Pos=m_cTalent.AddString(rs.m_Name);	
		m_cTalent.SetItemData(Pos,rs.m_ID);
		rs.MoveNext();
	}
	rs.Close();

	if( m_TalentName.GetLength()!=0 )
	{
		Pos=m_cTalent.FindStringExact(-1,m_TalentName);
		m_cTalent.SetCurSel(Pos);
	}
	
	return TRUE;  
}

void CRecordingTask::OnOK() 
{
	UpdateData();

	if( m_TalentID==0 )
		return;

	if( m_Name.GetLength()==0 )
		return;

	
	CDialog::OnOK();
}
