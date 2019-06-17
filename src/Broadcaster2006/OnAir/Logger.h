#pragma once
#include <afxmt.h>

typedef struct 
{
	char strName[255];
	long lID;
	long lTraffic;
	WORD wType;
	COleDateTime dateTime;
} typeLogItem;


class CLogger
{
protected:
	CList <typeLogItem *> m_listLog;
	CWinThread *m_pWorkerThread;
	CMutex	m_mx;

public:
	CLogger(void);
	~CLogger(void);

	BOOL AddItem( typeLogItem *);
	typeLogItem *GetItem();
	BOOL Lock(DWORD dwTimeout=-1);
	BOOL Unlock();
protected: 
	static UINT WorkerThread(LPVOID lpData);
};
