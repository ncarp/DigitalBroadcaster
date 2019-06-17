#include "stdafx.h"
#include "..\..\common\include\permissions.h"
#include "..\..\common\include\rssystemusers.h"
#include "..\..\common\include\global.h"
#include "..\..\common\include\rscomputers.h"

extern BOOL g_bSQLAut;

void GetUserPermissions( CString strUserName, tPermissions *p )
{
	CRSSystemUsers rs( g_strMainConnect );
	rs.m_strFilter.Format("Name = '%s'",strUserName);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Permission.SetSize(100);

		p->bManager			= rs.m_Permission.GetAt(0);

		p->bDiscography			= rs.m_Permission.GetAt(1);
		p->bDiscographyAdd		= rs.m_Permission.GetAt(2);
		p->bDiscographyEdit		= rs.m_Permission.GetAt(3);
		p->bDiscographyDelete	= rs.m_Permission.GetAt(4);

		p->bOnAirManagement		= rs.m_Permission.GetAt(5);
		p->bJinglesNew			= rs.m_Permission.GetAt(6);
		p->bJinglesEdit			= rs.m_Permission.GetAt(7);
		p->bJinglesCut			= rs.m_Permission.GetAt(8);
		p->bJinglesOnAir		= rs.m_Permission.GetAt(9);

		p->bBlocksAdd			= rs.m_Permission.GetAt(10);
		p->bBlocksEdit			= rs.m_Permission.GetAt(11);
		p->bBlocksCut			= rs.m_Permission.GetAt(12);

		p->bPlayListAdd			= rs.m_Permission.GetAt(13);
		p->bPlayListEdit		= rs.m_Permission.GetAt(14);
		p->bPlayListCut			= rs.m_Permission.GetAt(15);
		p->bPlayListEditContent = rs.m_Permission.GetAt(16);

		p->bTraffic				= rs.m_Permission.GetAt(17);
		p->bSpotsAdd			= rs.m_Permission.GetAt(18);
		p->bSpotsEdit			= rs.m_Permission.GetAt(19);
		p->bSpotsCut			= rs.m_Permission.GetAt(20);
		p->bSponsors			= rs.m_Permission.GetAt(21);
		p->bTrafficView			= rs.m_Permission.GetAt(22);
		p->bTrafficAdd			= rs.m_Permission.GetAt(23);
		p->bTrafficEdit			= rs.m_Permission.GetAt(24);
		p->bTrafficCut			= rs.m_Permission.GetAt(25);

		p->bScheduler			= rs.m_Permission.GetAt(26);
		p->bLineupAdd			= rs.m_Permission.GetAt(27);
		p->bLineupEdit			= rs.m_Permission.GetAt(28);
		p->bLineupCut			= rs.m_Permission.GetAt(29);
		p->bCriteriaAdd			= rs.m_Permission.GetAt(30);
		p->bCriteriaEdit		= rs.m_Permission.GetAt(31);
		p->bCriteriaCut			= rs.m_Permission.GetAt(32);
		p->bVoiceAdd			= rs.m_Permission.GetAt(33);
		p->bVoiceEdit			= rs.m_Permission.GetAt(34);
		p->bVoiceCut			= rs.m_Permission.GetAt(35);
		p->bScheduleAuto		= rs.m_Permission.GetAt(36);
		p->bScheduleEdit		= rs.m_Permission.GetAt(37);

		p->bNewsRoom			= rs.m_Permission.GetAt(38);
		p->bRmsAdd				= rs.m_Permission.GetAt(39);
		p->bRmsEdit				= rs.m_Permission.GetAt(40);
		p->bRmsCut				= rs.m_Permission.GetAt(41);
		p->bRmsOnAir			= rs.m_Permission.GetAt(42);
		p->bRmsLineup			= rs.m_Permission.GetAt(43);
		p->bTextAdd				= rs.m_Permission.GetAt(44);
		p->bTextEdit			= rs.m_Permission.GetAt(45);
		p->bTextCut				= rs.m_Permission.GetAt(46);
		p->bTextOnAir			= rs.m_Permission.GetAt(47);
		p->bTextLineup			= rs.m_Permission.GetAt(48);

		p->bManagerFolder		= rs.m_Permission.GetAt(49);
		p->bManagerTime			= rs.m_Permission.GetAt(50);
		p->bManagerLog			= rs.m_Permission.GetAt(51);

		p->bInstrumentals		= rs.m_Permission.GetAt(52);

		p->strName = rs.m_Name;
		p->lID = rs.m_Id;
	}
	else
	{
		rs.m_strFilter="";
		rs.Requery();
		memset(p,0,sizeof(tPermissions));

		if( !rs.GetRecordCount() )
		{
			rs.AddNew();
			rs.m_Name = strUserName;
			rs.m_Permission.SetAt(0,(BYTE)1);
			rs.Update();
			
			p->bManager = 1;
		}
	}
}

void GetUserPermissions( long lID, tPermissions *p )
{
	CRSSystemUsers rs( g_strMainConnect );
	
	rs.m_strFilter.Format("ID = '%d'",lID);
	rs.Open();

	if( rs.GetRecordCount() )
	{
		rs.m_Permission.SetSize(100);

		p->bManager				= rs.m_Permission.GetAt(0);

		p->bDiscography			= rs.m_Permission.GetAt(1);
		p->bDiscographyAdd		= rs.m_Permission.GetAt(2);
		p->bDiscographyEdit		= rs.m_Permission.GetAt(3);
		p->bDiscographyDelete	= rs.m_Permission.GetAt(4);

		p->bOnAirManagement		= rs.m_Permission.GetAt(5);
		p->bJinglesNew			= rs.m_Permission.GetAt(6);
		p->bJinglesEdit			= rs.m_Permission.GetAt(7);
		p->bJinglesCut			= rs.m_Permission.GetAt(8);
		p->bJinglesOnAir		= rs.m_Permission.GetAt(9);

		p->bBlocksAdd			= rs.m_Permission.GetAt(10);
		p->bBlocksEdit			= rs.m_Permission.GetAt(11);
		p->bBlocksCut			= rs.m_Permission.GetAt(12);

		p->bPlayListAdd			= rs.m_Permission.GetAt(13);
		p->bPlayListEdit		= rs.m_Permission.GetAt(14);
		p->bPlayListCut			= rs.m_Permission.GetAt(15);
		p->bPlayListEditContent = rs.m_Permission.GetAt(16);

		p->bTraffic				= rs.m_Permission.GetAt(17);
		p->bSpotsAdd			= rs.m_Permission.GetAt(18);
		p->bSpotsEdit			= rs.m_Permission.GetAt(19);
		p->bSpotsCut			= rs.m_Permission.GetAt(20);
		p->bSponsors			= rs.m_Permission.GetAt(21);
		p->bTrafficView			= rs.m_Permission.GetAt(22);
		p->bTrafficAdd			= rs.m_Permission.GetAt(23);
		p->bTrafficEdit			= rs.m_Permission.GetAt(24);
		p->bTrafficCut			= rs.m_Permission.GetAt(25);

		p->bScheduler			= rs.m_Permission.GetAt(26);
		p->bLineupAdd			= rs.m_Permission.GetAt(27);
		p->bLineupEdit			= rs.m_Permission.GetAt(28);
		p->bLineupCut			= rs.m_Permission.GetAt(29);
		p->bCriteriaAdd			= rs.m_Permission.GetAt(30);
		p->bCriteriaEdit		= rs.m_Permission.GetAt(31);
		p->bCriteriaCut			= rs.m_Permission.GetAt(32);
		p->bVoiceAdd			= rs.m_Permission.GetAt(33);
		p->bVoiceEdit			= rs.m_Permission.GetAt(34);
		p->bVoiceCut			= rs.m_Permission.GetAt(35);
		p->bScheduleAuto		= rs.m_Permission.GetAt(36);
		p->bScheduleEdit		= rs.m_Permission.GetAt(37);

		p->bNewsRoom			= rs.m_Permission.GetAt(38);
		p->bRmsAdd				= rs.m_Permission.GetAt(39);
		p->bRmsEdit				= rs.m_Permission.GetAt(40);
		p->bRmsCut				= rs.m_Permission.GetAt(41);
		p->bRmsOnAir			= rs.m_Permission.GetAt(42);
		p->bRmsLineup			= rs.m_Permission.GetAt(43);
		p->bTextAdd				= rs.m_Permission.GetAt(44);
		p->bTextEdit			= rs.m_Permission.GetAt(45);
		p->bTextCut				= rs.m_Permission.GetAt(46);
		p->bTextOnAir			= rs.m_Permission.GetAt(47);
		p->bTextLineup			= rs.m_Permission.GetAt(48);

		p->bManagerFolder		= rs.m_Permission.GetAt(49);
		p->bManagerTime			= rs.m_Permission.GetAt(50);
		p->bManagerLog			= rs.m_Permission.GetAt(51);

		p->bInstrumentals		= rs.m_Permission.GetAt(52);

		p->strName = rs.m_Name;
		p->lID = rs.m_Id;
	}
	else
	{
		memset(p,0,sizeof(tPermissions));
	}
}

long GetComputerID( CString strComp )
{
	CRSComputers	rs;
	long			lID=0;

	rs.m_strFilter.Format("Name = '%s'",strComp);
	rs.Open();

	if( rs.GetRecordCount()==0 )
	{
		rs.AddNew();
		rs.m_Name = strComp;
		rs.Update();
		rs.Requery();
	}
	lID = rs.m_ID;
	rs.Close();

	return lID;
}


void GetComputerAndUser()
{
	CString strTemp;
	DWORD	Size=100;

	GetUserName(strTemp.GetBuffer( 100),&Size);
	strTemp.ReleaseBuffer();
	
	g_strUserName = strTemp;
	GetUserPermissions(strTemp,&g_Permissions);
	
	GetComputerName(strTemp.GetBuffer(100),&Size);
	strTemp.ReleaseBuffer();
	g_strComputerName = strTemp;

	g_lComputerID = GetComputerID( g_strComputerName);
}

BOOL OpenDigitalRMDatabase()
{
	return FALSE;
}

BOOL WriteDigitalLog(long lComputerID,long lUserID,long lActionID, long lTypeID,long lItemID,long lRadioID, long lXtra )
{
	CString strSQL;
	CDatabase db;

	db.Open(g_strMainConnect);

	strSQL.Format("INSERT INTO [Log] (ComputerID, UserID, ActionID, TypeID, ItemID, lRadioID, XTRA) VALUES ('%d','%d','%d','%d','%d','%d','%d')",
		lComputerID,lUserID,lActionID,lTypeID,lItemID,lRadioID,lXtra );

	db.ExecuteSQL(strSQL);
	db.Close();

	return TRUE;
}