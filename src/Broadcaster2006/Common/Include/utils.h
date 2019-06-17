#if !defined( __UTILS_H__ )
#define __UTILS_H__

void WriteLogFile(CString strMsg);
void MultiByteConversion(CString in,WCHAR *out);
void GetTimeString(long dwTime, CString *strTime);
void GetTimeString64(DWORD64 dwTime, CString *strTime, BOOL bHorario=FALSE);
BOOL CheckKey(UINT nChar );
CString GetFileType( CString strFile );
CString GetFilePath( CString strFile);
void TrimTimeString( CString *strTime,int Left=0 );
void LoadToolBitmaps();
void LoadToolLabels();
CString ConvertFileName2LowerCase( CString str );

#endif