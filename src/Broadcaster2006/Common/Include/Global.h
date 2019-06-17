#if !defined ( __GLOBAL_H )
#define __GLOBAL_H

#include <mmreg.h>
#include <dsound.h>
#include <gdiplus.h>

#include "..\..\common\include\permissions.h"
#include "..\..\common\include\htmlinfo.h"

using namespace Gdiplus;

// GDI+ global objects --------------------------------------------------------
extern Color				g_colorLight[],
							g_colorDark[],
							g_colorRed,
							g_colorGreen,
							g_colorFace;

extern Font					*g_font36,
							*g_font24,
							*g_font12,
							*g_fontRythm;

extern SolidBrush			*g_brushShadowText,
							*g_brushCaptionText;
extern LinearGradientBrush	*g_brushSeparator;

// GDI extern objects ----------------------------------------------------------
extern CFont		*g_CFont24;
extern CImageList	*g_ImageListContainer,
					*g_ImageListToolEnabled,
					*g_ImageListToolDisabled,
					*g_ImageListToolHot,
					*g_ImageListHeader;
extern CBrush		*g_brushBackground;
extern CBitmap		*g_bmToolBackground;

// global strings --------------------------------------------------------------
extern char			g_lpstrToolLabels[];
extern CString		g_strOnAirConnect,
					g_strMainConnect,
					g_strTempDir,
					g_strBaseURL,
					g_strDB,
					g_strUserName,
					g_strComputerName;
	

// Misc config extern objects --------------------------------------------------
extern int			g_nContainers;
extern long			g_lFadeToTake,
					g_lFadeToIntro,
					g_lComputerID,
					g_lUserID;
extern UINT			g_nFormatArchive,
					g_nFormatLineUp;
extern WORD			g_wAutomationMode;

// Global references to specific windows ---------------------------------------
extern CWnd			*g_wndCartwall,
					*g_wndLineUp;

extern CHtmlInfo	*g_wndInfo;

// Direct Sound Objects --------------------------------------------------------
extern LPDIRECTSOUND	g_pDS_MAIN,
						g_pDS_PFL;

extern LPDIRECTSOUNDCAPTURE			g_pDS_Capture;
extern LPDIRECTSOUNDCAPTUREBUFFER	g_pDS_CaptureBuffer;
extern HANDLE						g_hCapture[];	

extern LPWAVEFORMATEX	g_pwfx;

// Critical Sections -----------------------------------------------------------
extern CRITICAL_SECTION	g_csMPEG,
						g_csEndACM;

//extern CDatabase	*g_pOnAirDB,
//					*g_pDigitalRMDB;

extern tPermissions	g_Permissions;

extern int			g_iSlow,
					g_iSlowAverage,
					g_iAverage;
extern long			g_iDelay;

extern UINT			g_nFormatArchive;

#endif