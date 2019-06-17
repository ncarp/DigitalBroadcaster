#if !defined( __ONAIRDEFINES_H__ )
#define __ONAIRDEFINES_H__

/////////////////////////////////////////////////////////////////////////
//	Comand identifiers
#define		CM_REFRESH		1001
#define		CM_INFO			1002
#define		CM_PFL			1003
#define		CM_REMOVE		1004
#define		CM_MOVEUP		1005
#define		CM_MOVEDOWN		1006
#define		CM_NEWSOUND		1007
#define		CM_NEW			1008
#define		CM_LOAD			1009
#define		CM_SAVE			1010
#define		CM_DISCARD		1011
#define		CM_EDIT			1012
#define		CM_CUT			1013
#define		CM_SCHEDULE		1014
#define		CM_QUERYBLOCKS	1015
#define		CM_EDITLINEUP	1016
#define		CM_LOCK			1017
#define		CM_BACK			1018
#define		CM_FOWARD		1019
#define		CM_STOP			1020
#define		CM_LINEUP		1021
#define		CM_DELAY1		1022
#define		CM_DELAY2		1023
#define		CM_DELAY5		1024
#define		CM_SKIP			1025
#define		CM_STATISTICS	1026

//	Control identifiers
#define		ID_LIST			2001
#define		ID_HEADER		2002

// Container IDs
#define		CONTAINER_MUSIC				1
#define		CONTAINER_MUSIC_DISCOGRAPHY 2
#define		CONTAINER_MUSIC_PLAYLIST	3
#define		CONTAINER_MUSIC_CATEGORY	4
#define		CONTAINER_MUSIC_SEARCH		5
#define		CONTAINER_JINGLES			6
#define		CONTAINER_LINEUP			7
#define		CONTAINER_PRODUCER			8
#define		CONTAINER_TRAFFIC			9
#define		CONTAINER_TRAFFIC_SPONSORS	10
#define		CONTAINER_TRAFFIC_SCREENS	11
#define		CONTAINER_TRAFFIC_DELAYED	12
#define		CONTAINER_CARTWALL			13
#define		CONTAINER_INTERNET			14
#define		CONTAINER_BLOCOS			15
#define		CONTAINER_PATROCINIOS		16
#define		CONTAINER_PUB_NAOEMITIDA	17
#define		CONTAINER_INFO				18
#define		CONTAINER_RMS				19
#define		CONTAINER_LOG				20
#define		CONTAINER_PRODUCER_RECORDING	21
#define		CONTAINER_PRODUCER_SCHEDULING	22
#define		CONTAINER_PRODUCER_MUSICEDITING	23
#define		CONTAINER_VOICEINSERT		24
#define		CONTAINER_AIRED				26

//	Item type definitions
#define		TYPE_NOTHING		0
#define		TYPE_ARTIST			1
#define		TYPE_JINGLETYPE		2
#define		TYPE_RECORDINGTASK	3
#define		TYPE_CUSTOMER		4
#define		TYPE_RECORDING		5
#define		TYPE_MUSICFILE		6
#define		TYPE_TRAFFICSCHEDULE 7
#define		TYPE_ONAIRUSER		8
#define		TYPE_RMTYPE			9
#define		TYPE_TEXT			10
#define		TYPE_RMLINEUP		11
#define		TYPE_NEWSLINEUP		12
#define		TYPE_PLAYLIST		13
#define		TYPE_YEAR			14
#define		TYPE_MONTH			15
#define		TYPE_DAY			16
#define		TYPE_MUSICTEMPLATE	17
#define		TYPE_JINGLETEMPLATE 18
#define		TYPE_USER			19
#define		TYPE_SCHEDULEDRAG	20
#define		TYPE_SPONSORBLOCK	21

#define		TYPE_MUSIC			51
#define		TYPE_JINGLE			52
#define		TYPE_SPOT			53
#define		TYPE_VOICEINSERT	54
#define		TYPE_SCHEDULE		55
#define		TYPE_BLOCK			56
#define		TYPE_RM				57
#define		TYPE_TIMESIGNAL		58


/////////////////////////////////////////////////////////////////////////
//	User messages
#define		UM_SORTPLAYERS		WM_USER+1
#define		UM_STARTNEXTPLAYER	WM_USER+2
#define		UM_SETPLAYEROPTIONS	WM_USER+3
#define		UM_DROP				WM_USER+4
#define		UM_CANDROP			WM_USER+5
#define		UM_MAKESPACE		WM_USER+6
#define		UM_VOLUMECHANGE		WM_USER+7
#define		UM_USERLOGOFF		WM_USER+8
#define		UM_FILEDBLCLK		WM_USER+9
#define		UM_UPDATETIMERS		WM_USER+10
#define		UM_GOTO				WM_USER+11
#define		UM_SETPAUSE			WM_USER+12
#define		UM_SETLOOP			WM_USER+13
#define		UM_NAVIGATECOMPLETE WM_USER+14
#define		UM_SCHEDULEDBLCLK	WM_USER+15
#define		UM_SELCHANGE		WM_USER+16
#define		UM_BLOCKRDBLCLK		WM_USER+17
#define		UM_PLAYERSTOPED		WM_USER+18
#define		UM_LOGMESSAGE		WM_USER+19

#define		SORT_CUE		1
#define		SORT_UNCUE		2
#define		SORT_PLAY		3

/////////////////////////////////////////////////////////////////////////
//	Player states
#define		STATE_UNCUED	1
#define		STATE_CUED		2
#define		STATE_PLAYING	3
#define		STATE_RECORDING 4

/////////////////////////////////////////////////////////////////////////
//	Automation mode
#define		AUTOMATION_NONE			0
#define		AUTOMATION_FULLAUTO		1
#define		AUTOMATION_LIVEASSIST	2
#define		AUTOMATION_MANUAL		3

/////////////////////////////////////////////////////////////////////////
//	Structures
typedef struct
{
	long		lID;
	WORD		wType;
	COLORREF	clr;
}typeTreeItem;
typedef typeTreeItem* LPtypeTreeItem;

typedef struct
{
	typeTreeItem	Item;
	char			strName[255];
	LPVOID			lpData;
}typeTreeDrag;

class typeArchiveItem
{
public:
	typeArchiveItem(WORD Type,long ID,CString Name,int Rythm,CString s1="",CString s2="",CString s3="");
public:
	WORD		wType;
	long		lID;
	long		lTraffID;
	CString		strName;
	CString		strData1;
	CString		strData2;
	CString		strData3;
	float		cColor;
};

typedef struct
{
	WORD	wType;
	LPVOID	lpItem;
	CPoint	DropPoint;
}typeDRAG_ITEM;


#define DRAG_ARCHIVE	1
#define DRAG_LINEUP		2
#define DRAG_BLOCK		3

#endif //onairdefines.h