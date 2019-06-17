#if !defined( __SPLITTER_UTILS_H )
#define __SPLITTER_UTILS_H

#define SP_PLAY		1
#define	SP_CUE		2
#define SP_OPEN		3
#define	SP_RESET	128

typedef struct 
{
	WORD		wAction;
	WORD		wType;
	WORD		wFinish;
	long int	lID;
	long int	lTime;
	long int	lLength;
	char		pstrMessage[256];
	char		strDate[20];
	char		strSrc[50];
	char		strDst[50];
}typeSplitterMsg;
#define	SIZEOFSPLITTERMSG	sizeof(typeSplitterMsg)

static	UINT	SendSplitterMsgThread(LPVOID);
BOOL	SendSplitterMessage( typeSplitterMsg *pMsg);

#endif
