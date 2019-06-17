#if !defined( __UTILS_H__ )
#define __UTILS_H__

void MultiByteConversion(CString in,WCHAR *out);
void GetTimeString(long dwTime, CString *strTime);
void GetTimeString64(DWORD64 dwTime, CString *strTime, BOOL bHorario=FALSE);

#endif