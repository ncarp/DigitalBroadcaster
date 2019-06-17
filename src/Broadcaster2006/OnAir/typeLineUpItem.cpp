// typeLineUpItem.cpp: implementation of the typeLineUpItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <gdiplus.h>
using namespace Gdiplus;

#include "OnAirDefines.h"
#include "typeLineUpItem.h"
#include "RSViewMusicDataPlaying.h"
#include "RSViewJinglesDataOnAir.h"
#include "ExternalObjects.h"
#include "RSViewSpotOnAirData.h"
#include "RSViewVoiceInsertOnAir.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"
#include "..\include\RSBlocksDefinition.h"
#include "..\include\RSBlocksComposition.h"
#include "..\include\RSViewTraffic.h"
#include "..\include\RSViewRMs.h"
#include "..\include\RSViewTimeSignal.h"
#include "..\include\RSViewRecordings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CString g_strOnAirConnect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

typeLineUpItem::typeLineUpItem(WORD wType,long lID,DWORD64 qwTime,CString strConnect )
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(Type %d, ID %d)",wType,lID);

	WriteLogFile("typeLineUpItem::typeLineUpItem (Enter) "+strLog);
#endif

	m_strConnect = strConnect;

	m_bFadeOutIntoTake=FALSE;
	m_bFadeInOutOfTake=FALSE;
	m_bLocked=FALSE;
	m_bCanDelete=TRUE;

	m_wType=wType;
	m_lItemID=lID;

	m_lStartPos		= 0;
	m_lFadeInPos	= 0;
	m_lIntroPos		= m_lOriginalIntro = 0;
	m_lFadeOutPos	= 0;
	m_lMixPos		= m_lOriginalMix = 0;
	m_lEndPos		= 0;
	m_wRythm		= 0;
	m_nMixCount		= 0;
	m_strName		= "nd";
	m_wType			= wType;
	m_Sound			= NULL;
	m_qwStartTime	= 0;
	m_wState		= 0;
	m_bLoop			= FALSE;
	m_bPause		= FALSE;
	m_bmSpectrum	= NULL;
	m_lTrafficID	= 0;
	m_lScheduleID	= 0;
	m_lVoiceID		= 0;
	m_lBusinessID	= 0;
	m_wPrecision	= 3;
	m_bBlock		= FALSE;
	m_qwOriginalStart = 0;
	m_lArtistID		= 0;
	m_lBlockID		= 0;
	m_lBlockPos		= 0;
	m_lBlockTime	= 0;
	m_lBlockLength	= 0;
	m_lBlockFinish	= 0;

	for( int i=0; i<100; i++ )
		m_pBlock[i]=NULL;

	switch( wType )
	{
	case TYPE_MUSIC:
		m_bItemIsValid=GetMusicData(lID);
		break;
	case TYPE_JINGLE:
		m_bItemIsValid=GetJingleData(lID);
		break;
	case TYPE_SPOT:
		m_bItemIsValid=GetSpotData(lID);
		break;
	case TYPE_VOICEINSERT:
		m_bItemIsValid=GetVoiceInsert(lID);
		break;
	case TYPE_BLOCK:
		m_qwStartTime=qwTime;
		m_bItemIsValid=GetBlockData(lID);
		break;
	case TYPE_RM:
		m_bItemIsValid=GetRMData(lID);
		break;
	case TYPE_TIMESIGNAL:
		m_bItemIsValid=GetTimeSignal(lID);
		break;
	case TYPE_RECORDING:
		m_bItemIsValid=GetRecording(lID);
		break;
	default:
		m_bItemIsValid=FALSE;
	}

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::typeLineUpItem (Exit) "+strLog);
#endif
}

typeLineUpItem::~typeLineUpItem()
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(Type %d, ID %d)",m_wType,m_lItemID);
	WriteLogFile("typeLineUpItem::~typeLineUpItem (Enter) "+strLog);
#endif

	SAFE_DELETE( m_Sound );

	if( m_bmSpectrum != NULL )
	{
		
		::delete( m_bmSpectrum ) ;
		m_bmSpectrum=NULL;
	}

	for( int i=0; i<100; i++ )
	{
		typeLineUpItem *lp=(typeLineUpItem *)m_pBlock[i];
		SAFE_DELETE( lp );
	}
#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::~typeLineUpItem (Exit) "+strLog);
#endif
}

BOOL typeLineUpItem::GetMusicData(long lID)
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",lID);

	WriteLogFile("typeLineUpItem::GetMusicaData (Enter) "+strLog);
#endif

	CRSViewMusicDataPlaying	rs(g_strMainConnect);

	rs.m_strFilter.Format("ID = '%d'",lID);

	do {
		try
		{
			rs.Open();
		}
		catch(...)
		{
		}
	} while( !rs.IsOpen() );
	
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return FALSE;
	}

	rs.m_Artist.TrimRight();
	rs.m_Title.TrimRight();
	rs.m_Path.TrimRight();
	rs.m_FileType.TrimRight();

	m_lArtistID = rs.m_ArtistID;
	m_strName = rs.m_Artist;
	m_strName2 = rs.m_Title;
	m_strFileName = rs.m_Path+"\\"+rs.m_Artist+" - "+rs.m_Title+rs.m_FileType;
	m_wRythm		= (WORD)rs.m_Rythm;
	m_lStartPos		= rs.m_Start;
	m_lFadeInPos	= rs.m_FadeIn;
	m_lIntroPos		= m_lOriginalIntro = rs.m_Intro;
	m_lEndPos		= rs.m_Finish;
	m_lMixPos		= m_lOriginalMix = rs.m_Mix;
	m_lFadeOutPos	= rs.m_FadeOut;
	m_lLoopA		= rs.m_LoopA;
	m_lLoopB		= rs.m_LoopB;
	if( m_lLoopA < m_lStartPos ) m_lLoopA = m_lStartPos;
	if( m_lLoopB <= m_lLoopA ) m_lLoopB = m_lIntroPos;
	if( m_lLoopB <= m_lLoopA ) m_lLoopB = m_lMixPos;

	m_nMixCount=1;

	rs.Close();

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetMusicaData (Exit) "+strLog);
#endif

	return TRUE;
}

BOOL typeLineUpItem::GetJingleData(long lID)
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",lID);
	WriteLogFile("typeLineUpItem::GetJingleData (Enter) "+strLog);
#endif

	CRSViewJinglesDataOnAir rs(g_strMainConnect);

	rs.m_strFilter.Format("ID = '%d'",lID);
	
	do {
		try 
		{
			rs.Open();
		}
		catch(...)
		{
		}
	} while( !rs.IsOpen() );
	
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return FALSE;
	}

	rs.m_TypeName.TrimRight();
	rs.m_Name.TrimRight();
	rs.m_Path.TrimRight();
	rs.m_FileName.TrimRight();

	m_strName = rs.m_TypeName;
	m_strName2 = rs.m_Name;
	m_strFileName = rs.m_Path+"\\"+rs.m_FileName;
	m_wRythm = (WORD)rs.m_Rythm;

	m_lStartPos	= rs.m_Start;
	m_lIntroPos = m_lOriginalIntro = rs.m_Intro;
	m_lEndPos	= rs.m_Finish;
	m_lMixPos	= m_lOriginalMix = rs.m_Mix;
	m_lLoopA	= rs.m_LoopA;
	m_lLoopB	= rs.m_LoopB;

	if( m_lLoopA < m_lStartPos ) m_lLoopA = m_lStartPos;
	if( m_lLoopB <= m_lLoopA ) m_lLoopB = m_lIntroPos;
	if( m_lLoopB <= m_lLoopA ) m_lLoopB = m_lMixPos;

	m_nMixCount=1;

	rs.Close();

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetJingleData (Exit) "+strLog);
#endif
	return TRUE;
}


BOOL typeLineUpItem::GetSpotData(long ID)
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",ID);
	WriteLogFile("typeLineUpItem::GetSpotData (Enter) "+strLog);
#endif

	CRSViewSpotOnAirData rs(g_strMainConnect);

	rs.m_strFilter.Format("SpotID = '%d'",ID);

	do {
		try 
		{
			rs.Open();
		}
		catch( ... )
		{
		}
	} while( !rs.IsOpen() );
	
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return FALSE;
	}

	rs.m_CustomerName.TrimRight();
	rs.m_Name.TrimRight();
	rs.m_Path.TrimRight();
	rs.m_FileName.TrimRight();

	m_strName = rs.m_CustomerName;
	m_strName2 = rs.m_Name;
	m_strFileName = rs.m_Path+"\\"+rs.m_FileName;
	m_wRythm = 0;

	m_lStartPos	= rs.m_Start;
	m_lEndPos	= rs.m_Finish;
	m_lMixPos	= m_lOriginalMix = rs.m_Mix;
	m_lBusinessID = rs.m_TypeOfBusinessID;
	m_lVoiceID = rs.m_MainVoiceID;
	m_lArtistID = rs.m_CustomerID;

	m_lLoopA = m_lStartPos;
	m_lLoopB = m_lMixPos;

	m_nMixCount=1;

	rs.Close();
#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetSpotData (Exit) "+strLog);
#endif

	return TRUE;
}

BOOL typeLineUpItem::GetBlockData(long lID )
{

#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",lID);
	WriteLogFile("typeLineUpItem::GetBlockData (Enter) "+strLog);
#endif

	CDatabase db;
	do{
		try {
			db.OpenEx("DSN="+m_strConnect,CDatabase::noOdbcDialog);
		}
		catch(...) {};
	}while( !db.IsOpen() );

	db.SetQueryTimeout(360);

	CRSBlocksDefinition rsDef( "",&db );
	CRSBlocksComposition rsComp( "",&db );
	CRSViewTraffic rsTraff("",&db);
	CString		days[7]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	CString		strDate,
				strTime;
	FILETIME	ftDate,ftLocalDate;
	BOOL		bHeader=TRUE;
	int			nStartBlock=-1;
	int			nSpotPos=0;
	long int	lBlockTime;
	typeLineUpItem *lpItem;

	memcpy(&ftLocalDate,&m_qwStartTime,sizeof(FILETIME));
	LocalFileTimeToFileTime(&ftLocalDate,&ftDate);

	COleDateTime date( ftDate );
	strDate.Format("%4d-%2d-%2d",date.GetYear(),date.GetMonth(),date.GetDay());
	strDate.Replace(" ","0");
	
	strTime.Format("%2d:%2d:%2d",date.GetHour(),date.GetMinute(),date.GetSecond());
	strTime.Replace(" ","0");

	rsDef.m_strFilter.Format("ID = '%d'",lID);

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetBlockData (Step2) "+strLog);
#endif

	do
	{
		try {
			rsDef.Open();
		}
		catch(...){};
	}while( !rsDef.IsOpen() );

	if( rsDef.GetRecordCount()==0 )
	{
		rsDef.Close();
		return FALSE;
	}
	rsDef.m_Name.TrimRight();

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetBlockData (Step3) "+strLog);
#endif
//	AfxMessageBox(strDate+" --- "+strTime+" --- "+rsDef.m_Name);

	m_strName	= strDate;
	m_strName2	= rsDef.m_Name;
	m_wRythm	= 0;
	m_wPrecision= (WORD)rsDef.m_InsertionType;
	lBlockTime	= rsDef.m_Time;

	m_lStartPos	= 0;
	m_lEndPos	= 0;
	m_lMixPos	= 0;
	
	for( int I=0; I<100; I++ )
		m_pBlock[I]=NULL;

	m_iBlockSize=0;
	m_iNextItem=0;

	rsDef.Close();

	rsComp.m_strFilter.Format("ID = '%d' AND StartingDate<='%s' AND EndingDate>='%s' AND %s=1",
							lID,strDate,strDate,days[date.GetDayOfWeek()-1]);
	
	rsComp.m_strSort = "Position";

	do { 
		try { 
			rsComp.Open(); 
		} catch(...) {}; 
	} while( !rsComp.IsOpen() );
	
	rsTraff.m_strFilter.Format("BlockID = '%d' AND BlockDate = '%s'",lID,strDate);
	rsTraff.m_strSort = "Position, N";

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetBlockData (Step4) "+strLog);
#endif

	do 
	{ 
		try { 
			rsTraff.Open(); 
		} catch(...) {}; 
	} while( !rsTraff.IsOpen() );

	while( !rsComp.IsEOF() )
	{
		if( (rsComp.m_ItemType==TYPE_RM) || (rsComp.m_ItemType == TYPE_JINGLE) || (rsComp.m_ItemType == TYPE_TIMESIGNAL) )
		{
			lpItem = new typeLineUpItem((WORD)rsComp.m_ItemType,rsComp.m_ItemID);
			if( lpItem->m_bItemIsValid )
			{
				m_pBlock[m_iBlockSize]=(LPVOID)lpItem;
				m_iBlockSize++;
				m_lEndPos=m_lMixPos+lpItem->GetTimeToEnd();
				m_lMixPos+=lpItem->GetTimeToMix();
			}
		} 
		else if( (rsComp.m_ItemType == TYPE_SPOT) && (bHeader) && (!rsTraff.IsEOF()) )
		{
			nSpotPos++;

			if( rsTraff.m_Position==nSpotPos )
			{
				lpItem = new typeLineUpItem(TYPE_SPOT,rsTraff.m_SpotID);
				if( lpItem->m_bItemIsValid )
				{
					m_pBlock[m_iBlockSize]=(LPVOID)lpItem;
					m_iBlockSize++;
					m_lEndPos=m_lMixPos+lpItem->GetTimeToEnd();
					m_lMixPos+=lpItem->GetTimeToMix();
					lpItem->m_lTrafficID=rsTraff.m_ID;
				}
				rsTraff.MoveNext();
			}
		}
		else if( (rsComp.m_ItemType == TYPE_SPOT) && (!bHeader) && (!rsTraff.IsEOF()) )
		{
			nSpotPos ++;
			if( (rsTraff.m_Position==nSpotPos) )
			{
				lpItem = new typeLineUpItem(TYPE_SPOT,rsTraff.m_SpotID);
				if( lpItem->m_bItemIsValid )
				{
					m_pBlock[m_iBlockSize]=(LPVOID)lpItem;
					m_iBlockSize++;
					m_lEndPos=m_lMixPos+lpItem->GetTimeToEnd();
					m_lMixPos+=lpItem->GetTimeToMix();
					lpItem->m_lTrafficID=rsTraff.m_ID;
				}
				rsTraff.MoveNext();
			}
		}
		else if( (rsComp.m_ItemType == TYPE_BLOCK) && (!rsTraff.IsEOF()) )
		{
#ifdef __DEBUG_LOG
			WriteLogFile("typeLineUpItem::GetBlockData (Step5) "+strLog);
#endif
			while( (!rsTraff.IsEOF()) && (rsTraff.m_Position<=150) )
			{
				lpItem = new typeLineUpItem(TYPE_SPOT,rsTraff.m_SpotID);
				if( lpItem->m_bItemIsValid )
				{
					if( nStartBlock!=-1 )
					{
						typeLineUpItem *TempItem = (typeLineUpItem *)m_pBlock[m_iBlockSize-1];
						if( (TempItem->m_lBusinessID==lpItem->m_lBusinessID) || (TempItem->m_lVoiceID==lpItem->m_lVoiceID) )
						{
							int InsertPerfect=-1,
								Insert = m_iBlockSize,
								Pos;
							typeLineUpItem *Prev,*Next;
							
							for( Pos=nStartBlock; Pos<m_iBlockSize-1; Pos++ )
							{
								if( (Pos==0) )
								{
									Next = (typeLineUpItem *)m_pBlock[Pos];
									if( Next->m_lBusinessID!= lpItem->m_lBusinessID )
										Insert = Pos;

									if( (Next->m_lBusinessID!= lpItem->m_lBusinessID) && (Next->m_lVoiceID!=lpItem->m_lVoiceID) )
										InsertPerfect=Pos;
								} 
								else
								{
									Prev = (typeLineUpItem *)m_pBlock[Pos-1];
									Next = (typeLineUpItem *)m_pBlock[Pos];

									if( (Next->m_lBusinessID!=lpItem->m_lBusinessID) && (Prev->m_lBusinessID!=lpItem->m_lBusinessID))
										Insert=Pos;
									if( (Next->m_lBusinessID!=lpItem->m_lBusinessID) && (Prev->m_lBusinessID!=lpItem->m_lBusinessID) && (Next->m_lVoiceID!=lpItem->m_lVoiceID) && (Prev->m_lVoiceID!=lpItem->m_lVoiceID))
										InsertPerfect=Pos;
								}
								if( InsertPerfect!=-1 )
									break;
							}
							for( Pos=99; Pos>Insert; Pos-- )
								m_pBlock[Pos]=m_pBlock[Pos-1];

							m_pBlock[Insert]=(LPVOID)lpItem;
						}
						else
						{
							m_pBlock[m_iBlockSize]=(LPVOID)lpItem;
						}
					}
					else
					{
						m_pBlock[m_iBlockSize]=(LPVOID)lpItem;
						nStartBlock = m_iBlockSize;
					}

					m_iBlockSize++;
					m_lEndPos=m_lMixPos+lpItem->GetTimeToEnd();
					m_lMixPos+=lpItem->GetTimeToMix();
					lpItem->m_lTrafficID=rsTraff.m_ID;
				}
				rsTraff.MoveNext();
			}
			bHeader=FALSE;
			nSpotPos=200;
		}
		rsComp.MoveNext();
	}
	
#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetBlockData (Step6) "+strLog);
#endif

	rsComp.Close();
	rsTraff.Close();
	db.Close();

	if( m_wPrecision==2 )
		m_qwStartTime-=(DWORD64)m_lMixPos*10000;

	m_bCanDelete=FALSE;

	if( m_iBlockSize )
	{
		m_lBlockID = m_lItemID;
		m_lBlockTime = lBlockTime;

		for( int nCount=0; nCount<m_iBlockSize; nCount++ )
		{
			lpItem = (typeLineUpItem *)m_pBlock[nCount];
			lpItem->m_lBlockID = m_lItemID;
			lpItem->m_lBlockPos = nCount;
			lpItem->m_lBlockTime = lBlockTime;
			lpItem->m_lBlockLength = m_lEndPos;
			lpItem->m_lBlockFinish = (long)m_wPrecision;
		}
#ifdef __DEBUG_LOG
		WriteLogFile("typeLineUpItem::GetBlockData (Exit1) "+strLog);
#endif
		return TRUE;
	}
	else
	{
#ifdef __DEBUG_LOG
		WriteLogFile("typeLineUpItem::GetBlockData (Exit2) "+strLog);
#endif
		return FALSE;
	}
}

BOOL typeLineUpItem::GetVoiceInsert(long lID)
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",lID);
	WriteLogFile("typeLineUpItem::GetVoiceInsert (Enter) "+strLog);
#endif

	CRSViewVoiceInsertOnAir rs( m_strConnect );

	rs.m_strFilter.Format("ID = '%d'",lID);

	do {
		try
		{
			rs.Open();
		}
		catch(...)
		{
		}
	} while( !rs.IsOpen() );
	
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return FALSE;
	}

	rs.m_Name.TrimRight();
	rs.m_Path.TrimRight();
	rs.m_FileName.TrimRight();

	m_strName.LoadString(IDS_VOICEINSERT);
	m_strName2 = rs.m_Name;
	m_strFileName = rs.m_Path+"\\"+rs.m_FileName;
	m_wRythm = 0;

	m_lStartPos	= rs.m_Start;
	m_lEndPos	= rs.m_Finish;
	m_lMixPos	= rs.m_Start;
	m_lOriginalMix = rs.m_Finish;

	m_nMixCount=1;

	rs.Close();
#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetVoiceInsert (Exit) "+strLog);
#endif
	return TRUE;
}

BOOL typeLineUpItem::GetRMData(long lID)
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",lID);
	WriteLogFile("typeLineUpItem::GetRMData (Enter) "+strLog);
#endif
	CRSViewRms rs(g_strMainConnect);

	rs.m_strFilter.Format("ID = '%d'",lID);

	do {
		try
		{
			rs.Open();
		}
		catch( ... )
		{
		}
	} while( !rs.IsOpen() );
	
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return FALSE;
	}

	rs.m_Type.TrimRight();
	rs.m_Name.TrimRight();
	rs.m_Path.TrimRight();
	rs.m_FileName.TrimRight();

	m_strName = rs.m_Type;
	m_strName2 = rs.m_Name;
	m_strFileName = rs.m_Path+"\\"+rs.m_FileName;
	m_wRythm = 0;

	m_lStartPos	= rs.m_Start;
	m_lEndPos	= rs.m_Finish;
	m_lMixPos	= m_lOriginalMix = rs.m_Mix;

	m_nMixCount=1;

	rs.Close();
#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetRMData (Exit) "+strLog);
#endif
	return TRUE;
}

BOOL typeLineUpItem::GetTimeSignal( long lID )
{

#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",lID);
	WriteLogFile("typeLineUpItem::GetTimeSignal (Enter) "+strLog);
#endif

	CRSViewTimeSignal rs(g_strMainConnect );
	rs.m_strFilter.Format("ID = %d",lID);
	
	do {
		try
		{
			rs.Open();
		}
		catch(...)
		{
		}
	} while( !rs.IsOpen() );

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return FALSE;
	}

	rs.m_Name.TrimRight();
	rs.m_Path.TrimRight();
	rs.m_FolderName.TrimRight();

	m_strName.LoadString(IDS_TIMESIGNAL);
	m_strName2 = rs.m_Name;
	m_strFileName = rs.m_Path+"\\"+rs.m_FolderName;
	m_wRythm = 0;

	m_lStartPos	= 0;
	m_lEndPos	= 5000;
	m_lMixPos	= m_lOriginalMix = 4500;

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetTimeSignal (Exit) "+strLog);
#endif
	return TRUE;
}

BOOL typeLineUpItem::GetRecording( long lID )
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(ID %d)",lID);
	WriteLogFile("typeLineUpItem::GetRecording (Enter) "+strLog);
#endif

	CRSViewRecordings rs(g_strMainConnect );
	rs.m_strFilter.Format("VersionID = %d",lID);

	do {
		try
		{
			rs.Open();
		}
		catch(...)
		{
		}
	} while( !rs.IsOpen() );

	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return FALSE;
	}

	rs.m_VersionName.TrimRight();
	rs.m_Name.TrimRight();
	rs.m_Path.TrimRight();
	rs.m_FileName.TrimRight();

	m_strName = rs.m_Name;
	m_strName2 = rs.m_VersionName;
	m_strFileName = rs.m_Path+"\\"+rs.m_FileName;
	m_wRythm = 0;

	CWaveFile wave;
	long lLength;
	LPWAVEFORMATEX lpw;

	wave.Open(m_strFileName.GetBuffer(0),NULL,WAVEFILE_READ);
	lpw=wave.GetFormat();

	if( lpw!=NULL )
		lLength=(DWORD)((float)wave.GetSize()/((float)lpw->nAvgBytesPerSec/1000));
	else
		lLength=0;

	m_lEndPos = m_lMixPos = lLength;

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::GetRecording (Exit) "+strLog);
#endif
	return TRUE;
}

void typeLineUpItem::SetTimeFile()
{
	SYSTEMTIME	st;
	CString strFile;

	FileTimeToSystemTime((FILETIME*)&m_qwStartTime,&st);
	strFile.Format("\\%d-%d.wav",st.wHour,st.wMinute);
	m_strFileName += strFile;

	//////////////////////////////////////////////////////////
	// Get the sound length, and create the bitmap
	CWaveFile	*wave=new CWaveFile();
	long		dwLength;

	wave->Open(m_strFileName.GetBuffer(0),NULL,WAVEFILE_READ);

	LPWAVEFORMATEX lpw=wave->GetFormat();
	
	if( lpw!=NULL )
		dwLength=(DWORD)((float)wave->GetSize()/((float)lpw->nAvgBytesPerSec/1000));
	else
		dwLength=30000;

	m_lEndPos = dwLength-100;
	m_lMixPos = m_lOriginalMix = dwLength-600;
	m_nMixCount = 1;
	delete wave;
}

long typeLineUpItem::GetLength()
{
	return( m_lEndPos-m_lStartPos );
}

long typeLineUpItem::GetTimeToEnd()
{
	long dw;

	if( m_wState==STATE_PLAYING )
	{
		m_lCurrentPos=m_Sound->GetPosition();
		if( m_lCurrentPos<m_lEndPos )
			dw=m_lEndPos-m_lCurrentPos;
		else
			dw=0;
	}
	else
	{
		if( m_lStartPos<m_lEndPos )
			dw=m_lEndPos-m_lStartPos;
		else
			dw=0;
	}
	return dw;
}

long typeLineUpItem::GetTimeToMix()
{
	long dw;

	if( m_wState==STATE_PLAYING )
	{
		m_lCurrentPos=m_Sound->GetPosition();
		if( m_lCurrentPos<m_lMixPos )
			dw=m_lMixPos-m_lCurrentPos;
		else
			dw=0;
	}
	else
	{
		if( m_lStartPos<m_lMixPos )
			dw=m_lMixPos-m_lStartPos;
		else
			dw=0;
	}
	return dw;
}

long typeLineUpItem::GetTimeToIntro()
{
	long dw;

	if( m_wState==STATE_PLAYING )
	{
		m_lCurrentPos=m_Sound->GetPosition();
		if( m_lCurrentPos<m_lIntroPos )
			dw=m_lIntroPos-m_lCurrentPos;
		else
			dw=0;
	}
	else
	{
		if( m_lStartPos<m_lIntroPos )
			dw=m_lIntroPos-m_lStartPos;
		else
			dw=0;
	}
	return dw;
}


void typeLineUpItem::CheckFadeOut()
{
	if( m_lFadeOutPos )
		if( m_lFadeOutPos<=(long)m_Sound->GetPosition() )
		{
			m_Sound->Fade(-3000,m_lEndPos-m_lFadeOutPos);
			m_lFadeOutPos=0;
		}
}

long typeLineUpItem::GetVolume()
{
	if( m_Sound!=NULL )
		return m_Sound->m_lVolume;
	else
		return 0;
}

Bitmap* typeLineUpItem::CreateSpectrum(float xres, int height)
{
#ifdef __DEBUG_LOG
	CString strLog;
	strLog.Format("(Type %d,ID %d)",m_wType,m_lItemID);
	WriteLogFile("typeLineUpItem::CreateSpectrum (Enter) "+strLog);
#endif
	float		sizebm;
	
	float m_xres=xres;

	sizebm=(float)(m_lEndPos+10000)*m_xres;
	
	int iSizeBm=(int)sizebm;

	Bitmap		*bm=::new Bitmap( iSizeBm,height);
	Graphics	graphbm(bm);

	RectF		rectIntro(m_lStartPos*m_xres,0.0f,GetTimeToIntro()*m_xres,(float)height);
	RectF		rectMix((REAL)(m_lMixPos)*m_xres,0.0f,(REAL)(m_lEndPos-m_lMixPos)*m_xres,(float)height);
	RectF		rectEnd(m_lEndPos*m_xres,0.0f,2.0f,(float)height);

	LinearGradientBrush	brushRed(	PointF( (REAL)(m_lIntroPos-5000)*m_xres,0),
									PointF( (REAL)(m_lIntroPos)*m_xres,0),
									Color(255,255,255,0),
									Color(255,255,0,0) );

	LinearGradientBrush	brushYellow(PointF( (REAL)(m_lIntroPos-10000)*m_xres,0),
									PointF( (REAL)(m_lIntroPos-5000)*m_xres,0),
									Color(255,0,255,0),
									Color(255,255,255,0) );


	graphbm.Clear(Color(255,212,208,200));
	
	if( GetTimeToIntro()>10000 )
	{
		// the intro has green, yellow and red
		graphbm.FillRectangle(&SolidBrush(Color(255,0,255,0)),RectF(m_lStartPos*m_xres,0.0f,(GetTimeToIntro()-10000)*m_xres,(float)height) );
		graphbm.FillRectangle(&brushYellow,RectF((m_lIntroPos-10000)*m_xres,0.0f,5000*m_xres,(float)height) );
		graphbm.FillRectangle(&brushRed,RectF((m_lIntroPos-5000)*m_xres,0.0f,5000*m_xres,(float)height) );
	}
	else if( GetTimeToIntro()>5000 )
	{
		// Yellow and red
		graphbm.FillRectangle(&brushYellow,RectF((m_lStartPos)*m_xres,0.0f,(GetTimeToIntro()-5000)*m_xres,(float)height) );
		graphbm.FillRectangle(&brushRed,RectF((m_lIntroPos-5000)*m_xres,0.0f,5000*m_xres,(float)height) );
	}
	else if( GetTimeToIntro()>0 )
	{
		// red
		graphbm.FillRectangle(&brushRed,RectF((m_lStartPos)*m_xres,0.0f,GetTimeToIntro()*m_xres,(float)height) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,222,222,0)),rectMix);

	if( (m_lFadeInPos) && (m_lFadeInPos > m_lStartPos) )
	{
		// draws a path
		PointF	points[]={ PointF(0.0f,0.0f),
							PointF(0.0f,48.0f),
							PointF(m_lStartPos*m_xres,(float)height),
							PointF(m_lFadeInPos*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
		// Draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(0.0f,0.0f,m_lStartPos*m_xres,(float)height) );

	if( (m_lFadeOutPos) && (m_lFadeOutPos < m_lEndPos) )
	{
		// Draw a path
		PointF	points[]={ PointF(m_lFadeOutPos*m_xres,0.0f),
							PointF(m_lEndPos*m_xres,(float)height),
							PointF((m_lEndPos+10000)*m_xres,(float)height),
							PointF((m_lEndPos+10000)*m_xres,0.0f) };

		GraphicsPath	path;
		path.AddLines(points,4);
		graphbm.FillPath(&SolidBrush(Color(128,128,128)),&path);
	}
	else
	{
		// draws a rectangle
		graphbm.FillRectangle(&SolidBrush(Color(128,128,128)),RectF(m_lEndPos*m_xres,0.0f,10000.0f*m_xres,(float)height) );
	}

	graphbm.FillRectangle(&SolidBrush(Color(255,180,0,0)),rectEnd);

#ifdef __DEBUG_LOG
	WriteLogFile("typeLineUpItem::CreateSpectrum (Exit) "+strLog);
#endif

	return bm;

}

