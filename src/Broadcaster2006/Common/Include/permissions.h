#if !defined __PERMISSIONS_H 
#define __PERMISSIONS_H

typedef struct {
	CString	strName;
	long	lID;
	BYTE	bManager,
			bManagerFolder,
			bManagerTime,
			bManagerLog,
		
			bDiscography,
			bDiscographyAdd,
			bDiscographyEdit,
			bDiscographyDelete,
			
			bOnAirManagement,
			bJinglesNew,
			bJinglesEdit,
			bJinglesCut,
			bJinglesOnAir,
			bBlocksAdd,
			bBlocksEdit,
			bBlocksCut,
			bPlayListAdd,
			bPlayListEdit,
			bPlayListCut,
			bPlayListEditContent,
			bInstrumentals,

			bTraffic,
			bSpotsAdd,
			bSpotsEdit,
			bSpotsCut,
			bSponsors,
			bTrafficView,
			bTrafficAdd,
			bTrafficEdit,
			bTrafficCut,

			bScheduler,
			bLineupAdd,
			bLineupEdit,
			bLineupCut,
			bCriteriaAdd,
			bCriteriaEdit,
			bCriteriaCut,
			bVoiceAdd,
			bVoiceEdit,
			bVoiceCut,
			bScheduleEdit,
			bScheduleAuto,

			bNewsRoom,
			bRmsAdd,
			bRmsEdit,
			bRmsCut,
			bRmsOnAir,
			bRmsLineup,
			bTextAdd,
			bTextEdit,
			bTextCut,
			bTextOnAir,
			bTextLineup;
} tPermissions;

long GetComputerID(CString strComputer);
void GetUserPermissions( CString strUserName, tPermissions * );
void GetUserPermissions( long lUserID, tPermissions * );
void GetComputerAndUser();
BOOL WriteDigitalLog(long lComputerID,long lUserID,long lActionID, long lTypeID = 0,long lItemID = 0,long lRadioID=0,long lXtra = 0 );
BOOL OpenDigitalRMDatabase();

#endif