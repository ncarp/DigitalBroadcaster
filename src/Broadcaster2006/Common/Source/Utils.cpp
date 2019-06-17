#include "stdafx.h"
#include "..\include\defines.h"
#include "..\include\utils.h"
#include "..\include\global.h"
#include "..\..\instoremedia\resource.h"

CString g_strLogFile;
int		g_nLastLogHour=-1;

// ------------------------------------------------------------------------
//	Função para escrever o log em ficheiro texto (debug)
void WriteLogFile(CString strMsg)
{
	CStdioFile logFile;
	COleDateTime dt = COleDateTime::GetCurrentTime();
	if( dt.GetHour()!=g_nLastLogHour )
	{
		CString strDateTime;

		strDateTime.Format("%4d%2d%2d%2d%2d%2d",dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond());
		strDateTime.Replace(" ","0");

		g_strLogFile.Format("%s\\%s.txt",g_strTempDir,strDateTime);
		g_nLastLogHour = dt.GetHour();

		WriteLogFile("WriteLogFile - New hour");
	}
	
	if( logFile.Open(g_strLogFile,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::typeText|CFile::shareDenyNone) )
	{
		CString strDateTime,
				strLog;

		strDateTime.Format("%4d-%2d-%2d|%2d:%2d:%2d",dt.GetYear(),dt.GetMonth(),dt.GetDay(),dt.GetHour(),dt.GetMinute(),dt.GetSecond());
		strDateTime.Replace(" ","0");
		strLog.Format("%s - %s\n",strDateTime,strMsg);
		
		logFile.SeekToEnd();
		logFile.WriteString(strLog);
		logFile.Close();
	}
}
///////////////////////////////////////////////////////////////////////////
//	Helper function to conver a CString into a WCHAR
void MultiByteConversion( CString in,WCHAR *out )
{
	int inSize=in.GetLength();
	
	MultiByteToWideChar(CP_ACP,0,(LPCSTR)in,inSize+1,out,inSize+1);
}

///////////////////////////////////////////////////////////////////////////
//	Helper function to convert a 32 bit time, in miliseconds, into a string
void GetTimeString(long dwTime, CString *strTime)
{
	FILETIME FT;
	SYSTEMTIME ST;
	DWORD64		qwTime=(DWORD64)dwTime*10000;

	if( dwTime<0 ) dwTime=0;
	
	memcpy(&FT,&qwTime,8);
	FileTimeToSystemTime(&FT,&ST);

	strTime->Format("%2d:%2d:%2d.%3d",ST.wHour,ST.wMinute,ST.wSecond,ST.wMilliseconds);
	strTime->Replace(" ","0");
};

void GetTimeString64(DWORD64 dwTime, CString *strTime, BOOL bHorario)
{
	FILETIME FT,LFT;
	SYSTEMTIME ST;

	memcpy(&FT,&dwTime,8);

	if( bHorario )
	{
		FileTimeToLocalFileTime(&FT,&LFT);
		FileTimeToSystemTime(&LFT,&ST);
	}
	else
		FileTimeToSystemTime(&FT,&ST);

	strTime->Format("%2d:%2d:%2d.%3d",ST.wHour,ST.wMinute,ST.wSecond,ST.wMilliseconds);
	strTime->Replace(" ","0");
}

///////////////////////////////////////////////////////////////////////////
//	Helper function, to check id a f key was pressed
BOOL CheckKey(UINT nChar )
{
	if( g_wndCartwall==NULL )
		return FALSE;

	if( g_wndLineUp==NULL )
		return FALSE;

	if( (nChar>=VK_F1) && (nChar<=VK_F12) )
		g_wndCartwall->SendMessage(UM_PLAYCART,nChar-VK_F1);
	else if( nChar==VK_ESCAPE )
		g_wndCartwall->SendMessage(UM_STOPALL);
	else if( nChar==VK_SPACE )
		g_wndLineUp->SendMessage(UM_SPACEPRESSED);
	else if( nChar==VK_PAUSE )
		g_wndLineUp->SendMessage(UM_PAUSE);
	else if( nChar==145 )
		g_wndLineUp->SendMessage(UM_SCROLL);
	else if( nChar==VK_RETURN )
		g_wndLineUp->BringWindowToTop();
	else
		return FALSE;

	return TRUE;
};

CString GetFileType( CString strFile )
{
	int n = strFile.ReverseFind('.');
	CString strResult;

	if( n != -1 )
		strResult = strFile.Mid(n,strFile.GetLength()-n);
	else
		strResult="";

	return strResult;
}

CString GetFilePath( CString strFile )
{
	CString strResult="";
	int n = strFile.ReverseFind('\\');

	if( n>0 )
		strResult = strFile.Mid(0,n);
	else if( n=0 )
		strResult = "\\";

	return strResult;
}

void TrimTimeString( CString *strTime,int Left )
{
	if( strTime->GetLength()==0 )
		return;

	while( (strTime->GetAt(0)=='0') || (strTime->GetAt(0)==':') )
	{
		strTime->Delete(0);
		if( strTime->GetLength()==0 )
			break;
	}

	if( (Left!=0) && (strTime->GetLength()>=Left) )
		strTime->Delete(strTime->GetLength()-Left,Left);
}

void LoadToolBitmaps()
{
	CBitmap	*bmTemp;

	////////////////////////////////////////////////////////////////////////
	//	Enabled toolbar bitmaps
	g_ImageListToolEnabled = new CImageList();
	g_ImageListToolEnabled->Create(40,36,ILC_COLOR24|ILC_MASK,0,100);

	// IDTOOL_REFRSH
	bmTemp=new CBitmap;
	bmTemp->LoadBitmap(IDB_REFRESH);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDTOOL_GARBAGE
	bmTemp=new CBitmap;
	bmTemp->LoadBitmap(IDB_GARBAGE);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,0,0));

	// IDTOOL_PFL
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_PFL);
	g_ImageListToolEnabled->Add(bmTemp,RGB(212,208,200));

	// IDTOOL_INFO
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_INFO);
	g_ImageListToolEnabled->Add(bmTemp,RGB(212,208,200));

	// IDTOOL_MOVEUP
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEUP);
	g_ImageListToolEnabled->Add(bmTemp,RGB(236,233,216));

	// IDB_TOOL_MOVEDOWN
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEDOWN);
	g_ImageListToolEnabled->Add(bmTemp,RGB(236,233,216));

	// IDB_TOOL_NEWSOUND
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW_SOUND);
	g_ImageListToolEnabled->Add(bmTemp,RGB(236,233,216));

	// IDB_TOOL_NEW
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_LOAD
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOAD);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_SAVE
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_SAVE);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_DISCARD
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_DISCARD);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_NEWSCHEDULE
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEWSCHEDULE);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_BACK
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_BACK);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_FORWARD
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_FOWARD);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_EDIT
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EDIT);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_LOCK
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOCK);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDB_TOOL_EXIT
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EXIT);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDBTOOL_NEWFOLDER
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEWFOLDER);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	// IDBTOOL_RENAME
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_RENAME);
	g_ImageListToolEnabled->Add(bmTemp,RGB(255,255,255));

	///////////////////////////////////////////////////////////////////////
	//	Hot toolbar bitmaps
	g_ImageListToolHot = new CImageList();
	g_ImageListToolHot->Create(40,36,ILC_COLOR24|ILC_MASK,0,100);


	// Refresh - 0
	bmTemp = new CBitmap;
	bmTemp->LoadBitmap(IDB_REFRESH_HOT);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// Remove - 1
	bmTemp = new CBitmap;
	bmTemp->LoadBitmap(IDB_GARBAGE);
	g_ImageListToolHot->Add(bmTemp,RGB(255,0,0));

	// PFL - 2
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_PFL);
	g_ImageListToolHot->Add(bmTemp,RGB(212,208,200));

	// INFO - 3
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_INFO_HOT);
	g_ImageListToolHot->Add(bmTemp,RGB(212,208,200));

	// MOVE UP - 4
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEUP_HOT);
	g_ImageListToolHot->Add(bmTemp,RGB(236,233,216));

	// MOVE DOWN - 5
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_MOVEDOWN_HOT);
	g_ImageListToolHot->Add(bmTemp,RGB(236,233,216));

	// New Sound - 6
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW_SOUND);
	g_ImageListToolHot->Add(bmTemp,RGB(236,233,216));

	// New - 7
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEW);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));


	// Load - 8
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOAD);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));


	// Save - 9
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_SAVE);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// Discard 10
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_DISCARD);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// New Schedule 11
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEWSCHEDULE);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// Back 12
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_BACK);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// Foward 13
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_FOWARD);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// Edit 14
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EDIT);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// Lock 15
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_LOCK);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// exit	16
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_EXIT);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// IDBTOOL_NEWFOLDER
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_NEWFOLDER);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));

	// IDBTOOL_RENAME
	bmTemp = new CBitmap();
	bmTemp->LoadBitmap(IDB_RENAME);
	g_ImageListToolHot->Add(bmTemp,RGB(255,255,255));
}

void LoadToolLabels()
{
	CString	strRefresh,
			strInfo,
			strRemove,
			strPFL,
			strMoveUp,
			strMoveDown,
			strNewSound,
			strNewCart,
			strLoadCart,
			strSaveCart,
			strDiscard,
			strNewSchedule,
			strBack,
			strFoward,
			strStop,
			strNews,
			strNewVoice,
			strEditSchedule,
			strEditLineUp,
			strLock,
			strExit,
			strEdit,
			strNewList,
			strRename;
	int		iPos=0;
	
	strRefresh.LoadString(IDS_REFRESH);
	strInfo.LoadString(IDS_INFO);
	strRemove.LoadString(IDS_REMOVE);
	strPFL.LoadString(IDS_PFL);
	strMoveUp.LoadString(IDS_MOVEUP);
	strMoveDown.LoadString(IDS_MOVEDOWN);
	strNewSound.LoadString(IDS_NEWSOUND);
	strNewCart.LoadString(IDS_NEWCART);
	strLoadCart.LoadString(IDS_LOADCART);
	strSaveCart.LoadString(IDS_SAVECART);
	strDiscard.LoadString(IDS_DISCARD);
	strNewSchedule.LoadString(IDS_NEWSCHEDULE);
	strBack.LoadString(IDS_BACK);
	strFoward.LoadString(IDS_FOWARD);
	strStop.LoadString(IDS_STOP);
	strNews.LoadString(IDS_NEWS);
	strNewVoice.LoadString(IDS_NEWVOICEINSERT);
	strEditSchedule.LoadString(IDS_EDITSCHEDULE);
	strEditLineUp.LoadString(IDS_EDITLINEUP);
	strLock.LoadString(IDS_LOCK);
	strExit.LoadString(IDS_EXIT);
	strEdit.LoadString(IDS_EDIT);
	strNewList.LoadString(IDS_NEWLIST);
	strRename.LoadString(IDS_RENAME);

	memset(g_lpstrToolLabels,0,200);

	// 0
	memcpy(g_lpstrToolLabels,strRefresh,strRefresh.GetLength() );
	iPos+=strRefresh.GetLength()+1;

	// 1
	memcpy(g_lpstrToolLabels+iPos,strInfo,strInfo.GetLength() );
	iPos+=strInfo.GetLength()+1;

	// 2
	memcpy(g_lpstrToolLabels+iPos,strRemove,strRemove.GetLength() );
	iPos+=strRemove.GetLength()+1;

	// 3
	memcpy(g_lpstrToolLabels+iPos,strPFL,strPFL.GetLength() );
	iPos+=strPFL.GetLength()+1;

	// 4
	memcpy(g_lpstrToolLabels+iPos,strMoveUp,strMoveUp.GetLength() );
	iPos+=strMoveUp.GetLength()+1;

	// 5
	memcpy(g_lpstrToolLabels+iPos,strMoveDown,strMoveDown.GetLength() );
	iPos+=strMoveDown.GetLength()+1;

	// 6
	memcpy(g_lpstrToolLabels+iPos,strNewSound,strNewSound.GetLength() );
	iPos+=strNewSound.GetLength()+1;  // 6

	// 7
	memcpy(g_lpstrToolLabels+iPos,strNewCart,strNewCart.GetLength() );
	iPos+=strNewCart.GetLength()+1;  // 7

	// 8
	memcpy(g_lpstrToolLabels+iPos,strLoadCart,strLoadCart.GetLength() );
	iPos+=strLoadCart.GetLength()+1;  // 8

	// 9
	memcpy(g_lpstrToolLabels+iPos,strSaveCart,strSaveCart.GetLength() );
	iPos+=strSaveCart.GetLength()+1;  // 9

	// 10
	memcpy(g_lpstrToolLabels+iPos,strDiscard,strDiscard.GetLength() );
	iPos+=strDiscard.GetLength()+1;  // 10

	// 11
	memcpy(g_lpstrToolLabels+iPos,strNewSchedule,strNewSchedule.GetLength() );
	iPos+=strNewSchedule.GetLength()+1;  // 11

	// 12
	memcpy(g_lpstrToolLabels+iPos,strBack,strBack.GetLength() );
	iPos+=strBack.GetLength()+1;  // 12

	// 13
	memcpy(g_lpstrToolLabels+iPos,strFoward,strFoward.GetLength() );
	iPos+=strFoward.GetLength()+1;  // 13

	// 14
	memcpy(g_lpstrToolLabels+iPos,strStop,strStop.GetLength() );
	iPos+=strStop.GetLength()+1;  // 14

	// 15
	memcpy(g_lpstrToolLabels+iPos,strNews,strNews.GetLength() );
	iPos+=strNews.GetLength()+1;  // 15

	// 16
	memcpy(g_lpstrToolLabels+iPos,strNewVoice,strNewVoice.GetLength() );
	iPos+=strNewVoice.GetLength()+1;  // 16

	// 17
	memcpy(g_lpstrToolLabels+iPos,strEditSchedule,strEditSchedule.GetLength() );
	iPos+=strEditSchedule.GetLength()+1;  // 17

	// 18
	memcpy(g_lpstrToolLabels+iPos,strEditLineUp,strEditLineUp.GetLength() );
	iPos+=strEditLineUp.GetLength()+1;  // 18

	// 19
	memcpy(g_lpstrToolLabels+iPos,strLock,strLock.GetLength() );
	iPos+=strLock.GetLength()+1;  // 19

	// 20
	memcpy(g_lpstrToolLabels+iPos,strExit,strExit.GetLength() );
	iPos+=strExit.GetLength()+1;  // 20

	// 21
	memcpy(g_lpstrToolLabels+iPos,strEdit,strEdit.GetLength() );
	iPos+=strEdit.GetLength()+1;

	// IDSTOOL_NEWLIST
	memcpy(g_lpstrToolLabels+iPos,strNewList,strNewList.GetLength() );
	iPos+=strNewList.GetLength()+1;

	// IDSTOOL_RENAME
	memcpy(g_lpstrToolLabels+iPos,strRename,strRename.GetLength() );
	iPos+=strRename.GetLength()+1;

}

CString ConvertFileName2LowerCase( CString str )
{
	CString strTemp;
	int I;

	str.MakeLower();
	str.TrimRight();
	I = str.GetLength();

	if( I>0 )
	{
		strTemp = str.GetAt(0);
		strTemp.MakeUpper();
		str.SetAt(0,strTemp.GetAt(0));

		for( int n=1; n<I-1; n++ )
		{
			if( str.GetAt(n)==' ' )
			{
				strTemp = str.GetAt(n+1);
				strTemp.MakeUpper();

				str.SetAt(n+1,strTemp.GetAt(0));
			}
		}
	}
	return str;
}