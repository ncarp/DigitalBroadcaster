#include "StdAfx.h"
#include "OnAirDefines.h"

typeArchiveItem::typeArchiveItem(WORD Type,long ID,CString Name,int Rythm,CString s1,CString s2,CString s3)
{
	wType	 = Type;
	lID		 = ID;
	strName	 = Name;
	strData1 = s1;
	strData2 = s2;
	strData3 = s3;
	lTraffID = 0;

	cColor = (float)Rythm/100;
};
