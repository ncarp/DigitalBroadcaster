#include "stdafx.h"
#include "Logger.h"
#include "OnAirDefines.h"
#include "ExternalObjects.h"
#include "..\common\include\defines.h"
#include "..\common\include\utils.h"

CLogger *g_pLogger = new CLogger();

CLogger::CLogger(void)
{
	m_pWorkerThread = AfxBeginThread(WorkerThread,this,THREAD_PRIORITY_IDLE);
}

CLogger::~CLogger(void)
{
	m_pWorkerThread->ExitInstance();
}

BOOL CLogger::AddItem( typeLogItem *pItem) 
{
	BOOL bLock = Lock(-1);
	if( bLock )
	{
		pItem->dateTime=COleDateTime::GetCurrentTime();
		m_listLog.AddHead(pItem);
		Unlock();
	}
	return TRUE;
}

typeLogItem *CLogger::GetItem()
{
	typeLogItem *pReturn=NULL;
	BOOL bLock = Lock();
	if( bLock )
	{
		if( !m_listLog.IsEmpty() )
		{
			pReturn = m_listLog.RemoveTail();
		}
		Unlock();
	}
	return pReturn;
}

BOOL CLogger::Lock(DWORD dwTimeout)
{
	return m_mx.Lock(dwTimeout);
}

BOOL CLogger::Unlock()
{
	return m_mx.Unlock();
}

UINT CLogger::WorkerThread(LPVOID lpData)
{
	CLogger		*pLogger=(CLogger *)lpData;
	CDatabase	db;
	CString		strSQL,
				strDate;
	typeLogItem	*pItem=NULL;

	do {
		pItem=pLogger->GetItem();

		if( pItem!=NULL )
		{
#ifdef __DEBUG_LOG
			WriteLogFile("CLogger::WorkerThread Open Database");
#endif
			// Open data base 
			do {
				try {
					db.OpenEx("DSN="+g_strOnAirConnect,CDatabase::noOdbcDialog);
				} catch(...) {};
			} while( !db.IsOpen() );

			while( pItem!=NULL )
			{
				// Prepare string with date and time +++++++++++++++++++++++++++++++++++++++++++++++
				strDate.Format("%d-%d-%d %d:%d:%d",
					pItem->dateTime.GetYear(),
					pItem->dateTime.GetMonth(),
					pItem->dateTime.GetDay(),
					pItem->dateTime.GetHour(),
					pItem->dateTime.GetMinute(),
					pItem->dateTime.GetSecond() );

				// OnAirLog ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				if( (pItem->lID!= 0) )
				{
					strSQL.Format("INSERT INTO OnAirLog ([Date],[ComputerID],[UserID],[ItemID],[ItemType]) VALUES ('%s','%d','%d','%d','%d')",
						strDate,
						g_lComputerID,
						g_lUserID,
						pItem->lID,
						pItem->wType );
#ifdef __DEBUG_LOG
					WriteLogFile("CLogger::WorkerThread SQL "+strSQL);
#endif
					try {
						db.ExecuteSQL(strSQL);
					} catch(...) {}
				}

				// OnAirTextLog ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				CString strName = pItem->strName;
				strName.Replace("'","''");
	
				strSQL.Format("INSERT INTO OnAirTextLog ([Date],[Log]) VALUES ('%s','%s')",
					strDate,strName);

#ifdef __DEBUG_LOG
				WriteLogFile("CLogger::WorkerThread SQL "+strSQL);
#endif

				try	{
					db.ExecuteSQL(strSQL);
				} catch(...) {}

				// Traffic --------------------------------------------------------------------------
				if( pItem->lTraffic )
				{
					strSQL.Format("UPDATE Traffic SET Aired = 1, AiringDate = '%s', TalentID='%d' WHERE ID = '%d'",
							strDate,
							g_lUserID,
							pItem->lTraffic);
#ifdef __DEBUG_LOG
					WriteLogFile("CLogger::WorkerThread SQL "+strSQL);
#endif

					try {
						db.ExecuteSQL(strSQL);
					}catch(...) {}
				}
				else if( pItem->wType==TYPE_SPOT )
				{
					strSQL.Format("INSERT INTO Traffic (Aired,AiringDate,TalentID,SpotID) VALUES ('1','%s',%d,%d)",
						strDate,g_lUserID,pItem->lID);

#ifdef __DEBUG_LOG
					WriteLogFile("CLogger::WorkerThread SQL "+strSQL);
#endif

					try {
						db.ExecuteSQL(strSQL);
					} catch(...) {}
				}

				delete pItem;
				pItem=pLogger->GetItem();
			}

			// Close database
#ifdef __DEBUG_LOG
			WriteLogFile("CLogger::WorkerThread Close Database");
#endif
			db.Close();
		}

		Sleep(1000);
	} while( TRUE );

	return 0;
}