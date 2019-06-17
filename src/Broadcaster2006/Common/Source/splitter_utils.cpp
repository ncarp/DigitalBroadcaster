#include "stdafx.h"
#include "..\..\common\include\splitter_utils.h"

extern	CString	g_strSplitter[];
extern	int		g_nSplitters;
extern	CString g_strComputerName;

BOOL SendSplitterMessage( typeSplitterMsg *pMsg )
{
	if( pMsg==NULL )
		return FALSE;

	strcpy(pMsg->strSrc,g_strComputerName);

	for( int I=0; I<g_nSplitters; I++ )
	{
		typeSplitterMsg	*tempMsg = new typeSplitterMsg;

		memcpy(tempMsg,pMsg,sizeof(typeSplitterMsg));
		strcpy(tempMsg->strDst,g_strSplitter[I]);

		AfxBeginThread(SendSplitterMsgThread,(LPVOID)tempMsg);
	}
	return TRUE;
}


UINT SendSplitterMsgThread( LPVOID pData )
{
	typeSplitterMsg	*pMsg = (typeSplitterMsg *)pData;
	HANDLE			hPipe;
	DWORD			nCount=0,
					dwMode;
	BOOL			fSuccess;
	CString			strPipe;
	
	strPipe.Format("\\\\%s\\pipe\\OnAir_Splitter",pMsg->strDst);

	while (1) 
	{ 
		hPipe = CreateFile( 
					strPipe, //lpszPipename,   // pipe name 
					GENERIC_READ |  // read and write access 
					GENERIC_WRITE, 
					0,              // no sharing 
					NULL,           // no security attributes
					OPEN_EXISTING,  // opens existing pipe 
					0,              // default attributes 
					NULL);          // no template file 
 
   // Break if the pipe handle is valid. 
 
		if (hPipe != INVALID_HANDLE_VALUE) 
		{
			break; 
		}
 
	// Exit if an error other than ERROR_PIPE_BUSY occurs. 
 
		if (GetLastError() != ERROR_PIPE_BUSY) 
			break; 
 
	// All pipe instances are busy, so wait for 20 seconds. 
 
		if (! WaitNamedPipe(strPipe, 20000) ) 
			break; 
	}
	if( hPipe!=INVALID_HANDLE_VALUE )
	{
		dwMode = PIPE_READMODE_MESSAGE; 
		fSuccess = SetNamedPipeHandleState( 
						hPipe,    // pipe handle 
						&dwMode,  // new pipe mode 
						NULL,     // don't set maximum bytes 
						NULL);    // don't set maximum time 
		if (fSuccess) 
		{
			WriteFile(hPipe,pData,SIZEOFSPLITTERMSG,&nCount,NULL);
//			ReadFile(hPipe,pData,SIZEOFSPLITTERMSG,&nCount,NULL);
		}

		CloseHandle(hPipe);
	}

	delete pMsg;
	pMsg = NULL;

	return( 0 );
}