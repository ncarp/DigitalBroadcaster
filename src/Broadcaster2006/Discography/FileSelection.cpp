// FileSelection.cpp : implementation file
//

#include "stdafx.h"
#include "Discography.h"
#include "FileSelection.h"
#include "music.h"
#include "..\include\RSPath.h"
#include "..\include\RSViewMusicFiles.h"
#include "..\include\rsMusicTracks.h"
#include "..\common\include\utils.h"
#include "..\common\include\FileNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSelection dialog

extern CString g_strMainConnect;

CFileSelection::CFileSelection(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSelection::IDD, pParent)
	, m_strDetails(_T(""))
{
	//{{AFX_DATA_INIT(CFileSelection)
	m_cList = _T("");
	m_Unedit = FALSE;
	//}}AFX_DATA_INIT
	m_bWorking=FALSE;
	m_bStop=FALSE;
}


void CFileSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSelection)
	DDX_Control(pDX, IDC_UNEDIT, m_cUnedit);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_PATH, m_Path);
	DDX_LBString(pDX, IDC_LIST1, m_cList);
	DDX_Check(pDX, IDC_UNEDIT, m_Unedit);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, ID_RENAME, m_cRename);
	DDX_Control(pDX, ID_DELETE, m_cDelete);
	DDX_Control(pDX, IDC_FILEDETAILS, m_cDetails);
	DDX_Text(pDX, IDC_FILEDETAILS, m_strDetails);
}


BEGIN_MESSAGE_MAP(CFileSelection, CDialog)
	//{{AFX_MSG_MAP(CFileSelection)
	ON_CBN_SELCHANGE(IDC_PATH, OnSelchangePath)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeFileList)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_RENAME, &CFileSelection::OnBnClickedRename)
	ON_BN_CLICKED(ID_DELETE, &CFileSelection::OnBnClickedDelete)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSelection message handlers

BOOL CFileSelection::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int	Pos;
	CRSPath rs( g_strMainConnect );
	rs.m_strFilter = "Music = 1";
	rs.m_strSort = "Path";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Path.TrimRight();

		Pos=m_Path.AddString(rs.m_Path);
		m_Path.SetItemData(Pos,rs.m_ID);

		rs.MoveNext();
	}
	rs.Close();

	m_OK.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileSelection::OnSelchangePath() 
{
	m_OK.EnableWindow(FALSE);
	UpdateData();

	int Pos = m_Path.GetCurSel();
	if( Pos==CB_ERR )
		return;

	m_Path.GetLBText(Pos,m_strPath);
	m_PathID = m_Path.GetItemData(Pos);

	m_Path.EnableWindow(FALSE);
	m_cUnedit.EnableWindow(FALSE);

	RefreshFileList( (LPVOID)this );
}

UINT CFileSelection::RefreshFileList( LPVOID lp )
{
	CFileSelection *pdl=(CFileSelection *)lp;
			
	CFileFind	finder;
	CString		str,	
				strTemp;
	int			Pos=0;
	int			nFiles=0;
	BOOL		bWorking;
	MSG			Msg;

	pdl->m_bWorking = TRUE;

	CRSViewMusicFiles	rs(g_strMainConnect);
	rs.m_strFilter="FileName = 'zz'";
	rs.Open();

	pdl->m_List.ResetContent();


	bWorking=finder.FindFile(pdl->m_strPath+"\\*.*");
	while( bWorking )
	{
		nFiles++;
		bWorking=finder.FindNextFile();
	}

	pdl->m_Progress.SetRange(0,nFiles);

	bWorking=finder.FindFile(pdl->m_strPath+"\\*.*");
	while( (bWorking) && (!pdl->m_bStop) )
	{
		bWorking=finder.FindNextFile();

		strTemp=finder.GetFilePath();
		strTemp.MakeLower();
		if( (strTemp.Find(".mp3",0)!=strTemp.GetLength()-4) && (strTemp.Find(".wav",0)!=strTemp.GetLength()-4) )
			continue;

		str=finder.GetFilePath();
		str.Replace("'","''");

		if( pdl->m_Unedit )
		{
			rs.m_strFilter.Format("FileName = '%s' AND Activ <> 0",str);
			rs.Requery();

			if( rs.GetRecordCount()==0 )
			{
				pdl->m_List.AddString(finder.GetFileName());
			}
		}
		else
		{
			pdl->m_List.AddString(finder.GetFileName() );
		}
		Pos++;
		pdl->m_Progress.SetPos(Pos);

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}

	pdl->m_Progress.SetPos(0);
	pdl->m_Path.EnableWindow(TRUE);
	pdl->m_cUnedit.EnableWindow(TRUE);
	pdl->m_bWorking=FALSE;

	return 0;
}

void CFileSelection::OnSelchangeFileList() 
{
	int Pos = m_List.GetCurSel();
	if( Pos==LB_ERR )
	{
		m_OK.EnableWindow(FALSE);
		return;
	}

	m_List.GetText(Pos,m_strFileName);
	
	CRSViewMusicFiles rs( g_strMainConnect );
	CString str = m_strPath+"\\"+m_strFileName;
	str.Replace("'","''");

	rs.m_strFilter.Format("FileName = '%s' AND Activ <> 0",str);
	rs.Open();
	if( rs.GetRecordCount() == 0 )
	{
		m_OK.EnableWindow();
		m_cRename.EnableWindow();
		m_cDelete.EnableWindow();
	}
	else
	{
		m_OK.EnableWindow(FALSE);
		m_cRename.EnableWindow(FALSE);
		m_cDelete.EnableWindow(FALSE);
	}

	SetFileDetails();

	rs.Close();
}

void CFileSelection::OnOK() 
{
	CMusic	dl;
	int Pos = m_strFileName.Find(" - ",0);
	if( Pos < 0 )
		return;

	dl.m_strArtist = m_strFileName.Mid(0,Pos);
	dl.m_strTitle = m_strFileName.Mid(Pos+3,m_strFileName.GetLength()-Pos-7);
	dl.m_strFileName = m_strPath+"\\"+m_strFileName;
	
	if( dl.DoModal()==IDOK )
	{
		CRSMusicTracks rs( g_strMainConnect );
		rs.m_strFilter.Format("ArtistID=%d",dl.m_ArtistID);
		rs.m_strSort="ID DESC";

		rs.Open();
		rs.AddNew();
		rs.m_ArtistID = dl.m_ArtistID;
		rs.m_Activ = 1;
		rs.m_Available = 1;
		rs.m_CategoryID = dl.m_CategoryID;
		rs.m_Date.year = dl.m_dDate.GetYear();
		rs.m_Date.month = dl.m_dDate.GetMonth();
		rs.m_Date.day = dl.m_dDate.GetDay();
		rs.m_Date.hour=0;
		rs.m_Date.minute=0;
		rs.m_Date.second=0;
		rs.m_Date.fraction=0;
		rs.m_FadeIn = dl.m_pTimers->m_pTimer->m_FadeIn;
		rs.m_FadeOut = dl.m_pTimers->m_pTimer->m_FadeOut;
		rs.m_FileType = GetFileType(dl.m_pTimers->m_strFileName);
		rs.m_Finish = dl.m_pTimers->m_pTimer->m_End;
		rs.m_Intro = dl.m_pTimers->m_pTimer->m_Intro;
		rs.m_LanguageID = dl.m_ExpressionID;
		rs.m_LoopA = dl.m_pTimers->m_pTimer->m_LoopA;
		rs.m_LoopB = dl.m_pTimers->m_pTimer->m_LoopB;
		rs.m_Lyrics = dl.m_strLirycs;
		rs.m_Mix = dl.m_pTimers->m_pTimer->m_Mix;
		rs.m_Music = dl.m_strComposer;
		rs.m_Musicians = dl.m_strMusicians;
		rs.m_Obs = dl.m_strRemarcks;
		rs.m_PathID = m_PathID;
		rs.m_Producer = dl.m_strProducer;
		rs.m_RecordID = dl.m_CDID;
		rs.m_RecordLabelID = dl.m_LabelID;
		rs.m_Rythm = dl.m_Rythm;
		rs.m_Start = dl.m_pTimers->m_pTimer->m_Start;
		rs.m_Studio = dl.m_strStudio;
		rs.m_Title = dl.m_strTitle;

		rs.Update();
//		rs.Requery();

		OnSelchangeFileList();
	}
}

void CFileSelection::OnCancel() 
{
	m_bStop = TRUE;
	CDialog::OnCancel();
}

void CFileSelection::OnBnClickedRename()
{
	int lPos = m_List.GetCurSel();

	if( lPos==LB_ERR )
		return;

	CString strFullFileName;

	if( m_PathID==0 )
		return;

	strFullFileName.Format("%s\\%s",m_strPath,m_strFileName);
	
	CFileNameDlg dlg;

	dlg.m_strPath = m_strPath;
	dlg.m_strFileName = m_strFileName.Mid(0,m_strFileName.GetLength()-4);
	dlg.m_strType = GetFileType(m_strFileName);

	if( dlg.DoModal()==IDOK )
	{
		CString strNewFileName;

		strNewFileName.Format("%s\\%s%s",m_strPath,dlg.m_strFileName,dlg.m_strType);
		if( MoveFile(strFullFileName,strNewFileName) )
		{
			m_List.DeleteString(lPos);
			lPos = m_List.InsertString(lPos,dlg.m_strFileName+dlg.m_strType);
			m_List.SetCurSel(lPos);
			OnSelchangeFileList();
		}
	} 
}

void CFileSelection::SetFileDetails()
{
	m_strDetails="";
	m_cDetails.SetWindowTextA(m_strDetails);

	int nPos = m_List.GetCurSel();

	if( nPos==LB_ERR )
		return;

}

void CFileSelection::OnBnClickedDelete()
{
	if( !g_Permissions.bDiscographyDelete )
	{
		AfxMessageBox(IDS_DENIED);
		return;
	}

	int nPos = m_List.GetCurSel();

	if( nPos==LB_ERR )
		return;

	if( m_PathID==0 )
		return;

	if( AfxMessageBox(IDS_CONFIRMDELETEFILE,MB_YESNO)==IDNO )
		return;

	CString strFileName;

	strFileName.Format("%s\\%s",m_strPath,m_strFileName);

	if( DeleteFile(strFileName)!=0 )
	{
		m_List.DeleteString(nPos);
	}
}
