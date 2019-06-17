// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Discography.h"

#include "DiscographyDoc.h"
#include "LeftView.h"
#include "FileSelection.h"
#include "Music.h"
#include "Artist.h"
#include "..\include\RSViewMusicFull.h"
#include "..\include\rsViewDiscography.h"
#include "..\include\RSMusicTracks.h"
#include "..\include\RSViewArtistFull.h"
#include "..\include\RSArtists.h"
#include "..\include\RSRadioStations.h"
#include "..\OnAir\PFLWnd.h"
#include "..\hasp\hasp.h"
#include "..\include\haspcode.h"
#include "..\common\include\utils.h"
#include "..\common\include\defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString	g_strMainConnect,
				g_strBaseURL;
extern CPFLWnd	*g_wndPFL;
/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CDigitalLeftView)

BEGIN_MESSAGE_MAP(CLeftView, CDigitalLeftView)
	//{{AFX_MSG_MAP(CLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDigitalLeftView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CDiscographyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CDigitalLeftView::OnInitialUpdate();

	CString str;
	str.LoadString(IDS_DISCOGRAPHY);
	m_pDocument->SetTitle(str);
	
	if( g_Permissions.bDiscography )
		AfxBeginThread( RefreshList,(LPVOID)this);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CDigitalLeftView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CDigitalLeftView::Dump(dc);
}

CDiscographyDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiscographyDoc)));
	return (CDiscographyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

UINT CLeftView::RefreshList( LPVOID lp )
{
	CLeftView *pView = (CLeftView *)lp;
	CTreeCtrl	*pTree = &pView->GetTreeCtrl();

	pTree->DeleteAllItems();

	CRSViewDiscography	rs( g_strMainConnect );
	CString		strPrev;
	HTREEITEM	hArtist,
				hMusic;
	typeTreeItem *lpItem;

	rs.m_strSort = "Artist, Title";
	rs.Open();

	while( !rs.IsEOF() )
	{
		if( strPrev!=rs.m_Artist )
		{
			strPrev = rs.m_Artist;
			rs.m_Artist.TrimRight();
			
			lpItem = new typeTreeItem;
			lpItem->lID = rs.m_ArtistID;
			lpItem->wType = TYPE_ARTIST;

			hArtist = pTree->InsertItem(rs.m_Artist,16,16);
			pTree->SetItemData(hArtist,(DWORD)lpItem);
			pTree->SetItemState(hArtist,TVIS_BOLD,TVIS_BOLD);
		}
		rs.m_Title.TrimRight();

		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_MUSIC;

		hMusic = pTree->InsertItem(rs.m_Title,17,17,hArtist);
		pTree->SetItemData(hMusic,(DWORD)lpItem);

		rs.MoveNext();
	}

	return 0;
}

void CLeftView::OnNew()
{
	int	par1,par2,par3,par4;

	if( HASP_HASPPROTECTION && HASP_WORKSTATION )
	{
		if( HASP_TIMEKEY )
			hasp(78,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else if( HASP_4 )
			hasp(6,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
		else
		{
			hasp(5,0,0,HASP_PASS1,HASP_PASS2,&par1,&par2,&par3,&par4);
			if( par3!=0 )
				par3=0;
			else
				par3=-1;
		}
		if( (par3!=0) || ((par1!=HASP_IDLOW) && (HASP_IDLOW!=0)) || ((par2!=HASP_IDHIGH) && (HASP_IDHIGH!=0)) )
		{
			return;
		}
	}

	CFileSelection *dlsel = new CFileSelection();
	dlsel->Create(IDD_FILESELECTION,this);
	dlsel->ShowWindow(SW_SHOW);

/*
	CFileSelection dlsel;	if( dlsel.DoModal()!=IDOK )
		return;

	CMusic	dl;
	int Pos = dlsel.m_strFileName.Find(" - ",0);
	if( Pos < 0 )
		return;

	dl.m_strArtist = dlsel.m_strFileName.Mid(0,Pos);
	dl.m_strTitle = dlsel.m_strFileName.Mid(Pos+3,dlsel.m_strFileName.GetLength()-Pos-7);
	dl.m_strFileName = dlsel.m_strPath+"\\"+dlsel.m_strFileName;
	
	if( dl.DoModal()==IDOK )
	{
		CRSMusicTracks rs( g_strMainConnect );
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
		rs.m_PathID = dlsel.m_PathID;
		rs.m_Producer = dl.m_strProducer;
		rs.m_RecordID = dl.m_CDID;
		rs.m_RecordLabelID = dl.m_LabelID;
		rs.m_Rythm = dl.m_Rythm;
		rs.m_Start = dl.m_pTimers->m_pTimer->m_Start;
		rs.m_Studio = dl.m_strStudio;
		rs.m_Title = dl.m_strTitle;

		rs.Update();
		rs.Requery();

		CTreeCtrl		*pTree=&GetTreeCtrl();
		HTREEITEM		hArtist = FindString(dl.m_strArtist),
						hSong;
		typeTreeItem	*lpItem;

		if( hArtist==NULL )
		{
			lpItem = new typeTreeItem;
			lpItem->lID=dl.m_ArtistID;
			lpItem->wType=TYPE_ARTIST;

			hArtist = pTree->InsertItem(dl.m_strArtist,16,16);
			pTree->SetItemData(hArtist,(DWORD)lpItem);
			pTree->SetItemState(hArtist,TVIS_BOLD,TVIS_BOLD);

			pTree->SortChildren(NULL);
		}
		lpItem = new typeTreeItem;
		lpItem->lID=rs.m_ID;
		lpItem->wType=TYPE_MUSIC;

		hSong = pTree->InsertItem(dl.m_strTitle,17,17,hArtist);
		pTree->SetItemData(hSong,(DWORD)lpItem);
		pTree->SortChildren(hArtist);
		pTree->EnsureVisible(hSong);

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_ADD,TYPE_MUSIC,rs.m_ID);
	} */
}

void CLeftView::OnDoubleClick()
{
	if( !g_Permissions.bDiscographyEdit )
		return;

	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem == NULL )
		return;

	if( lpItem->wType == TYPE_ARTIST )
		OnEditArtist( hItem );
	else
		OnEditSong( hItem );
}

void CLeftView::OnRDoubleClick()
{
	OnPFL();
}

void CLeftView::OnPFL()
{
	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem == NULL )
		return;

	if( lpItem->wType != TYPE_MUSIC )
		return;

	g_wndPFL->SetSound(TYPE_MUSIC,lpItem->lID);
	g_wndPFL->RestoreWindow();
	
}


void CLeftView::OnEditSong( HTREEITEM hSong )
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	typeTreeItem	*lpItem = (typeTreeItem *)pTree->GetItemData( hSong );
	CRSViewMusicFull rsView( g_strMainConnect );
	
	rsView.m_strFilter.Format("ID = %d",lpItem->lID);
	rsView.Open();
	if( rsView.GetRecordCount() )
	{
		CMusic	dl;
		rsView.m_Path.TrimRight();
		rsView.m_FileType.TrimRight();
		rsView.m_Artist.TrimRight();
		rsView.m_Title.TrimRight();

		dl.m_ArtistID = rsView.m_ArtistID;
		dl.m_strArtist = rsView.m_Artist;
		dl.m_strTitle = rsView.m_Title;
		dl.m_CategoryID = rsView.m_CategoryID;
		dl.m_strType = rsView.m_Category;
		dl.m_ExpressionID = rsView.m_LanguageID;
		dl.m_strExpression = rsView.m_Expression;
		dl.m_Rythm = rsView.m_Rythm;
		dl.m_CDID = rsView.m_RecordID;
		dl.m_strCD = rsView.m_Record;
		dl.m_dDate = rsView.m_Date;
		dl.m_LabelID = rsView.m_RecordLabelID;
		dl.m_strLabel = rsView.m_Label;
		dl.m_strProducer = rsView.m_Producer;
		dl.m_strComposer = rsView.m_Music;
		dl.m_strLirycs = rsView.m_Lyrics;
		dl.m_strMusicians = rsView.m_Musicians;
		dl.m_strStudio = rsView.m_Studio;
		dl.m_strRemarcks = rsView.m_Obs;
		dl.m_strFileName = rsView.m_Path+"\\"+rsView.m_Artist+" - "+rsView.m_Title+rsView.m_FileType;
		dl.m_strPath = rsView.m_Path;
		dl.m_PathID = rsView.m_PathID;
		dl.m_strFileType = rsView.m_FileType;
		dl.m_SongID = rsView.m_ID;
		dl.m_bIsNew=FALSE;
		dl.m_Start	= rsView.m_Start;
		dl.m_FadeIn	= rsView.m_FadeIn;
		dl.m_FadeOut= rsView.m_FadeOut;
		dl.m_Intro	= rsView.m_Intro;
		dl.m_Mix	= rsView.m_Mix;
		dl.m_End	= rsView.m_Finish;
		dl.m_LoopA	= rsView.m_LoopA;
		dl.m_LoopB	= rsView.m_LoopB;
		
		rsView.Close();
		if( dl.DoModal()==IDOK )
		{
			dl.m_pTimers->OnStop();
			delete dl.m_pTimers->m_pSound;
			dl.m_pTimers->m_pSound = NULL;

			CRSMusicTracks rs( g_strMainConnect );

			rs.m_strFilter.Format("ID = %d",dl.m_SongID);
			rs.Open();

			if( rs.GetRecordCount() )
			{
				BOOL	bNeedToChangeFile = FALSE;
				BOOL	bFileChanged = FALSE;
				CString	strNewFileName;

				strNewFileName = dl.m_strPath+"\\"+dl.m_strArtist+" - "+dl.m_strTitle+dl.m_strFileType;
				if( dl.m_strFileName != strNewFileName )
				{
					bNeedToChangeFile = TRUE;
					bFileChanged = (rename(dl.m_strFileName,strNewFileName)==0);
				}
				rs.Edit();
				if( bFileChanged )
				{
					rs.m_ArtistID = dl.m_ArtistID;
					rs.m_Title = dl.m_strTitle;
				}
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
				//rs.m_FileType = ".wav";
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
				rs.m_PathID = dl.m_PathID;
				rs.m_Producer = dl.m_strProducer;
				rs.m_RecordID = dl.m_CDID;
				rs.m_RecordLabelID = dl.m_LabelID;
				rs.m_Rythm = dl.m_Rythm;
				rs.m_Start = dl.m_pTimers->m_pTimer->m_Start;
				rs.m_Studio = dl.m_strStudio;
				rs.Update();

				if( bFileChanged )
				{
					pTree->DeleteItem(hSong);
					HTREEITEM		hArtist = FindString(dl.m_strArtist);
					typeTreeItem	*lpItem;

					if( hArtist==NULL )
					{
						lpItem = new typeTreeItem;
						lpItem->lID=dl.m_ArtistID;
						lpItem->wType=TYPE_ARTIST;

						hArtist = pTree->InsertItem(dl.m_strArtist,16,16);
						pTree->SetItemData(hArtist,(DWORD)lpItem);
						pTree->SetItemState(hArtist,TVIS_BOLD,TVIS_BOLD);
				
						pTree->SortChildren(NULL);
					}
					lpItem = new typeTreeItem;
					lpItem->lID=rs.m_ID;
					lpItem->wType=TYPE_MUSIC;

					hSong = pTree->InsertItem(dl.m_strTitle,17,17,hArtist);
					pTree->SetItemData(hSong,(DWORD)lpItem);
					pTree->SortChildren(hArtist);
					pTree->EnsureVisible(hSong);
				}

				WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_MUSIC,lpItem->lID);

				if( bNeedToChangeFile && !bFileChanged )
					AfxMessageBox(IDS_COULDNOTRENAMEFILE);
			}
		}
	}
	else
		rsView.Close();
}

void CLeftView::OnEditArtist( HTREEITEM hArtist )
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
 	typeTreeItem	*lpItem= (typeTreeItem *)pTree->GetItemData(hArtist);

	CRSViewArtistFull rsView( g_strMainConnect );
	rsView.m_strFilter.Format("ID = %d",lpItem->lID);
	rsView.Open();

	if( rsView.GetRecordCount() )
	{
		CArtist dl;
	
		rsView.m_Name.TrimRight();
		rsView.m_Adress.TrimRight();
		rsView.m_eMail.TrimRight();
		rsView.m_FanClub.TrimRight();
		rsView.m_Label.TrimRight();
		rsView.m_Name.TrimRight();
		rsView.m_Nationality.TrimRight();
		rsView.m_Obs.TrimRight();
		rsView.m_www.TrimRight();

		dl.m_Name = rsView.m_Name;
		dl.m_Adress = rsView.m_Adress;
		dl.m_Date = rsView.m_Birthdate;
		dl.m_eMail = rsView.m_eMail;
		dl.m_FanClub = rsView.m_FanClub;
		dl.m_Label = rsView.m_Label;
		dl.m_Name = rsView.m_Name;
		dl.m_Nationality = rsView.m_Nationality;
		dl.m_Remarks = rsView.m_Obs;
		dl.m_WWW = rsView.m_www;
		dl.m_ArtistID = rsView.m_ID;
		dl.m_LabelID = rsView.m_RecordLabelID;
		dl.m_NationalityID = rsView.m_NationalityID;
		rsView.Close();

		if( dl.DoModal()==IDOK )
		{
			CRSArtists rs( g_strMainConnect,NULL );

			rs.m_strFilter.Format("ID = %d",dl.m_ArtistID);
			rs.Open();
			if( rs.GetRecordCount() )
			{
				rs.Edit();
				rs.m_Activ = 1;
				rs.m_Adress = dl.m_Adress;
				rs.m_Birthdate.year = dl.m_Date.GetYear();
				rs.m_Birthdate.month = dl.m_Date.GetMonth();
				rs.m_Birthdate.day = dl.m_Date.GetDay();
				rs.m_Birthdate.hour = 0;
				rs.m_Birthdate.minute = 0;
				rs.m_Birthdate.second = 0;
				rs.m_Birthdate.fraction = 0;
				rs.m_eMail = dl.m_eMail;
				rs.m_FanClub = dl.m_FanClub;
				rs.m_NationalityID = dl.m_NationalityID;
				rs.m_Obs = dl.m_Remarks;
				rs.m_RecordLabelID = dl.m_LabelID;
				rs.m_www = dl.m_WWW;
				rs.Update();
			}
			rs.Close();
			WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_EDIT,TYPE_ARTIST,lpItem->lID);
		}
	}
	else
		rsView.Close();
}

void CLeftView::OnCut()
{
	CTreeCtrl *pTree = &GetTreeCtrl();
	HTREEITEM hItem = pTree->GetSelectedItem();

	if( hItem==NULL )
		return;

	typeTreeItem *lpItem = (typeTreeItem *)pTree->GetItemData(hItem);
	if( lpItem == NULL )
		return;

	if( lpItem->wType != TYPE_MUSIC )
		return;

	if( AfxMessageBox(IDS_CONFIRMMUSICREMOVE,MB_YESNOCANCEL)==IDYES )
	{
		CRSRadioStations	rs( g_strMainConnect );
		CDatabase			db;
		CString				strSQL;

		strSQL.Format("UPDATE MusicTracks SET Activ = '0' WHERE ID = '%d'",lpItem->lID);
		rs.Open();
		rs.m_pDatabase->ExecuteSQL(strSQL);

		while( !rs.IsEOF() )
		{
			rs.m_DSN.TrimRight();
			strSQL.Format("DELETE FROM [PlayLists-Contents] WHERE MusicTrackID = '%d'",lpItem->lID);

			db.Open(rs.m_DSN);
			db.ExecuteSQL(strSQL);

			strSQL.Format("DELETE FROM Scheduling WHERE ItemType = '%d' AND ItemID = '%d'",TYPE_MUSIC,lpItem->lID);
			db.ExecuteSQL(strSQL);
			db.Close();
			rs.MoveNext();
		}

		rs.Close();

		WriteDigitalLog(g_lComputerID,g_Permissions.lID,ACTION_CUT,TYPE_MUSIC,lpItem->lID);

		pTree->DeleteItem(hItem);
	}
}

void CLeftView::OnSelChange()
{
	CTreeCtrl		*pTree = &GetTreeCtrl();
	HTREEITEM		hItem = pTree->GetSelectedItem();
	LPtypeTreeItem	lpItem = (LPtypeTreeItem)pTree->GetItemData(hItem);
	CString			strURL;

	if( lpItem==NULL )
	{
		strURL.Format("%s\\EmptyPage.asp",g_strBaseURL);
		SetView(strURL);
		return;
	}

	switch( lpItem->wType )
	{
	case TYPE_MUSIC:
		strURL.Format("%s\\Song.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(strURL);
		break;
	case TYPE_ARTIST:
		strURL.Format("%s\\Artist.asp?ID=%d",g_strBaseURL,lpItem->lID);
		SetView(strURL);
		break;
	default:
		strURL.Format("%s\\EmptyPage.asp",g_strBaseURL);
		SetView(strURL);
		break;
	}
}