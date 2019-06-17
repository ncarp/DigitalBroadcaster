#if !defined( __DEFINES_H )
#define __DEFINES_H

#define USE_MAIN_AUDIO___
#define __DEBUG_LOG

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
#define		CM_CONFIG		1026
#define		CM_RESET		1027
#define		CM_RENAME		1028

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
#define		CONTAINER_SURVEILLANCE		27
#define		CONTAINER_REFRESH			0

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
#define		TYPE_RECORD			22
#define		TYPE_EXPRESSION		23
#define		TYPE_RECORDLABEL	24
#define		TYPE_MUSICCATEGORIE 25
#define		TYPE_AGENCY			26
#define		TYPE_BUSINESS		27
#define		TYPE_VOICE			28
#define		TYPE_SALESMAN		29
#define		TYPE_JINGLEPLAYLIST 30

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
#define		UM_ADDTOLINEUP		WM_USER+19
#define		UM_GETNEXTITEM		WM_USER+20
#define		UM_LOGITEM			WM_USER+21
#define		UM_CALCSTARTINGTIMES WM_USER+22
#define		UM_SYNCRONIZEBLOCK	WM_USER+23
#define		UM_ADDITEM			WM_USER+24
#define		UM_GETNEXTBLOCK		WM_USER+25
#define		UM_PREPARENEXTBLOCK	WM_USER+26
#define		UM_ADDITEMBYUNCUE	WM_USER+27
#define		UM_EDIT				WM_USER+28
#define		UM_PLAYCART			WM_USER+29
#define		UM_STOPALL			WM_USER+30
#define		UM_PAUSE			WM_USER+31
#define		UM_SCROLL			WM_USER+32
#define		UM_SPACEPRESSED		WM_USER+33
#define		UM_LDBLCLK			WM_USER+34
#define		UM_REFRESH			WM_USER+35
#define		UM_HDRCLICK			WM_USER+36
#define		UM_RESETFILE		WM_USER+37
#define		UM_AUDIOTOTOP		WM_USER+38
#define		UM_SHOWLASTVIEW		WM_USER+39
#define		UM_DRAGLEAVE		WM_USER+40
#define		UM_DRAGMOVEITEM		WM_USER+41
#define		UM_SURVEILLANCETOTOP WM_USER+42

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
//	Control identifiers
#define		ID_SELECTOR				501

// Editing type
#define		EDIT_ARCHIVE	1
#define		EDIT_MUSICFILE	2
#define		EDIT_FILE		3

// Audio File Types
#define		FILETYPE_UNDEFINED	0
#define		FILETYPE_WAV		1
#define		FILETYPE_MP3		2
#define		FILETYPE_MP2		3
#define		FILETYPE_WMA		4

// User actions defines
#define		ACTION_ADD					1
#define		ACTION_EDIT					2
#define		ACTION_CUT					3
#define		ACTION_ADDONAIRJINGLE		4
#define		ACTION_EDITONAIRJINGLE		5
#define		ACTION_CUTONAIRJINGLE		6
#define		ACTION_CUTJINGLEFROMBLOCKS	7
#define		ACTION_ADDTOPLAYLIST		8
#define		ACTION_CUTFROMPLAYLIST		9
#define		ACTION_ADDTOSPONSORS		10
#define		ACTION_EDITSPONSORS			11
#define		ACTION_CUTFROMSPONSORS		12
#define		ACTION_ADDINSTRUMENTAL		13
#define		ACTION_CUTINSTRUMENTAL		14
#define		ACTION_LOG_DISCOGRAPHY		51
#define		ACTION_LOG_ONAIRMANAGEMENT	52
#define		ACTION_LOG_TRAFFIC			53
#define		ACTION_LOG_SCHEDULER		54
#define		ACTION_LOG_NEWSROOM			55

// Colors
#define		COLOR_BLACK					RGB(0,0,0)
#define		COLOR_RED					RGB(160,0,0)
#define		COLOR_GREEN					RGB(0,128,0)
#define		COLOR_BLUE					RGB(0,0,128)
#define		COLOR_JINGLES				RGB(250,251,232)

// Macros
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

// Tool bar images index
#define IDBTOOL_REFRSH		0
#define IDBTOOL_GARBAGE		1
#define IDBTOOL_PFL			2
#define IDBTOOL_INFO		3
#define IDBTOOL_MOVEUP		4
#define IDBTOOL_MOVEDOWN	5
#define IDBTOOL_NEWSOUND	6
#define IDBTOOL_NEW			7
#define IDBTOOL_LOAD		8
#define IDBTOOL_SAVE		9
#define IDBTOOL_DISCARD		10
#define IDBTOOL_NEWSCHEDULE	11
#define IDBTOOL_BACK		12
#define IDBTOOL_FORWARD		13
#define IDBTOOL_EDIT		14
#define IDBTOOL_LOCK		15
#define IDBTOOL_EXIT		16
#define IDBTOOL_NEWFOLDER	17
#define IDBTOOL_RENAME		18

// Too bar labels index
#define IDSTOOL_REFRESH			0
#define IDSTOOL_INFO			1
#define IDSTOOL_REMOVE			2
#define IDSTOOL_PFL				3
#define IDSTOOL_MOVEUP			4
#define IDSTOOL_MOVEDOWN		5
#define IDSTOOL_NEWSOUND		6
#define IDSTOOL_NEWCART			7
#define IDSTOOL_LOADCART		8
#define IDSTOOL_SAVECART		9
#define IDSTOOL_DISCARD			10
#define IDSTOOL_NEWSCHEDULE		11
#define IDSTOOL_BACK			12
#define IDSTOOL_FOWARD			13
#define IDSTOOL_STOP			14
#define IDSTOOL_NEWS			15
#define IDSTOOL_NEWVOICE		16
#define IDSTOOL_EDITSCHEDULE	17
#define IDSTOOL_EDITLINEUP		18
#define IDSTOOL_LOCK			19
#define IDSTOOL_EXIT			20
#define IDSTOOL_EDIT			21
#define IDSTOOL_NEWLIST			22
#define IDSTOOL_RENAME			23

// Tree/List view Images Index
#define IDBTREE_FOLDERSPOT		0
#define IDBTREE_SPOT			1
#define IDBTREE_FOLDERSCHEDULE	2
#define IDBTREE_SCHEDULE		3
#define IDBTREE_JINGLE			4
#define IDBTREE_USER			5
#define IDBTREE_RECORDINGTASK	6
#define IDBTREE_SOUNDRECORDING	7
#define IDBTREE_FOLDERRM		8
#define IDBTREE_RM				9
#define IDBTREE_FOLDERTEXT		10
#define IDBTREE_TEXT			11
#define IDBTREE_CARTWALL		12
#define IDBTREE_NEWSLINEUP		13
#define IDBTREE_FOLDERJINGLE	14
#define IDBTREE_FOLDERUNLISTED	15
#define IDBTREE_FOLDERMUSIC		16
#define IDBTREE_MUSIC			17
#endif