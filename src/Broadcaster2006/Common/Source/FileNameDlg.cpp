// ..\common\source\FileNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include <id3\tag.h>
#include "..\Include\FileNameDlg.h"
#include "..\include\utils.h"

// CFileNameDlg dialog

IMPLEMENT_DYNAMIC(CFileNameDlg, CDialog)

CFileNameDlg::CFileNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileNameDlg::IDD, pParent)
	, m_strFileName(_T(""))
{

}

CFileNameDlg::~CFileNameDlg()
{
}

void CFileNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILENAME, m_cFileName);
	DDX_CBString(pDX, IDC_FILENAME, m_strFileName);
}


BEGIN_MESSAGE_MAP(CFileNameDlg, CDialog)
END_MESSAGE_MAP()


// CFileNameDlg message handlers

BOOL CFileNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nPos;
	CString strTemp,
			str1,
			str2;

	m_strFileName.Trim();

	nPos = m_strFileName.Find(" - ");
	
	if( nPos==CB_ERR )
	{
		nPos = m_strFileName.Find("-");
		if( nPos!=CB_ERR )
		{
			str1 = m_strFileName.Mid(0,nPos);
			str2 = m_strFileName.Mid(nPos+1,m_strFileName.GetLength()-nPos);
		}
	}
	else
	{
		str1 = m_strFileName.Mid(0,nPos);
		str2 = m_strFileName.Mid(nPos+2,m_strFileName.GetLength()-nPos);
	}

	strTemp = m_strFileName;
	strTemp.MakeUpper();
	m_cFileName.AddString(strTemp);

	strTemp = ConvertFileName2LowerCase(strTemp);
	m_cFileName.AddString(strTemp);

	if( nPos!=CB_ERR )
	{
		str1.Trim();
		str2.Trim();

		strTemp.Format("%s - %s",str1,str2);
		strTemp.MakeUpper();
		m_cFileName.AddString(strTemp);

		strTemp = ConvertFileName2LowerCase(strTemp);
		m_cFileName.AddString(strTemp);

		strTemp.Format("%s - %s",str2,str1);
		strTemp.MakeUpper();
		m_cFileName.AddString(strTemp);

		strTemp = ConvertFileName2LowerCase(strTemp);
		m_cFileName.AddString(strTemp);
	}

	m_strType.MakeLower();

	if( m_strType==".mp3" )
	{
		CString strFile;
		ID3_Tag id3Tag;
		int nTags;

		strFile.Format("%s\\%s%s",m_strPath,m_strFileName,m_strType);
		nTags=id3Tag.Link(strFile);

		if( nTags>0 )
		{
			str1="Artist";
			str2="Title";

			ID3_Frame *pFrame = id3Tag.Find(ID3FID_TITLE);
			if( pFrame!=NULL )
			{
				char str[256];
				ID3_Field* pField = pFrame->GetField(ID3FN_TEXT);
				if( pField!=NULL )
				{
					pField->Get(str,256);
					str1=str;
			//		AfxMessageBox("Title: "+str1);
				}
				//delete pFrame;
			}

			pFrame = id3Tag.Find(ID3FID_LEADARTIST);
			if( pFrame!=NULL )
			{
				char str[256];
				ID3_Field* pField = pFrame->GetField(ID3FN_TEXT);
				if( pField!=NULL )
				{
					pField->Get(str,256);
					str2=str;
				//	AfxMessageBox("Artist: "+str2);
				}
				//delete pFrame;
			}
			
			strTemp.Format("%s - %s",str2,str1);
			strTemp.MakeUpper();
			m_cFileName.AddString(strTemp);

			strTemp = ConvertFileName2LowerCase(strTemp);
			m_cFileName.AddString(strTemp);
		}
	}

	return TRUE;  
}
