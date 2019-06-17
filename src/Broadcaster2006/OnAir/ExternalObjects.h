#if !defined( __EXTERNALOBJECTS_H__ )
#define __EXTERNALOBJECTS_H__

//#include <afxcmn.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "CartwallWnd.h"
#include "LineUpWnd.h"
#include "PFLWnd.h"
#include "TrafficInfoWnd.h"
#include "ProgInfoWnd.h"
#include "AiredWnd.h"
#include "Logon.h"
#include "LogonBack.h"
#include "StatusWnd.h"
#include "MusicInfo.h"
#include "..\include\SoundManager.h"

//extern CCartwallWnd			*g_wndCartwall;

extern CPFLWnd				*g_wndPFL;
extern CStatusWnd			*g_wndStatus;	
extern CTrafficInfoWnd		*g_wndTrafficInfo;
extern CProgInfoWnd			*g_wndProgInfo;
extern CAiredWnd			*g_wndAired;
extern CLogOn				*g_wndLogOn;
extern CLogOnBack			*g_wndLogOnBack;
extern CMusicInfo			*g_wndMusicInfo;

extern FontFamily			*g_fontfamilyTR;

extern Font					*g_font36,
							*g_font24,
							*g_font12,
							*g_fontRythm,
							*g_fontSmallTitle,
							*g_font14Bold;

extern Color				g_colorCaptionText;
extern Color				g_colorLight[];
extern Color				g_colorDark[];
extern Color				g_colorShadow,
							g_colorRed,
							g_colorGreen,
							g_colorFace;

extern SolidBrush			*g_brushCaptionText,
							*g_brushShadowText;
extern LinearGradientBrush	*g_brushSeparator;

extern CFont				*g_cfont24;

extern CImageList			*g_ilToolEnabled,
							*g_ilToolHot,
							*g_ilSmallIcons,
							*g_ilContainer;

extern CBitmap				*g_bmRefresh,
							*g_bmToolBackground;

extern CBrush				*g_brushBackground,
							*g_brushMusicBack;

extern CString				g_strMainConnect,
							g_strOnAirConnect,
							g_strBaseURL,
							g_strDB,
							g_strUserName;
//extern CDatabase			*g_pOnAirDB;

extern char					g_lpstrToolLabels[];

extern CSoundManager*		g_MainSound;

extern LPDIRECTSOUND		lpDS_PFL,
							lpDS_CARTWALL;

extern UINT					g_nFormatArchive,
							g_nFormatLineUp;

extern WORD					g_wAutomationMode;
extern long					g_lComputerID;
extern long					g_lUserID;
extern int					g_iFadeToTake,
							g_iFadeOnIntro;

extern	BOOL				g_bUserCanEditMusic,
							g_bUserCanRecord,
							g_bUserCanSchedule,
							g_bUserCanDelayBlocks,
							
							g_bTimeOut,
							g_bIsOnNetwork,
							g_bIsAcceptingCommands;

extern CString				g_strSplitter[50];
extern int					g_nSplitters;

#endif
