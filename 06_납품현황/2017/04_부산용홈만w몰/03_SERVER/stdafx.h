
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


#include <afxsock.h>            // MFC 소켓 확장

#include "Xdefine.h"
#include "GlobalDef.h"
#include "InfoComm_CCM_Serv.h"
#include "Mmsystem.h"
#include "crc16.h"
#include "string_def.h"


#define STR_REPORT_FILE_NAME		"LogReport_ServApp.txt"
//#define __PRINT_LOG_DATA__
//#define __USE_FAKE_CCM__


#define MAX_NUM_LTPM_DAY			300


#define SZ_STR_DEV_NAME					24

struct INFO_CTRL_DEV_CCM {
	BOOL bUse;
	char strName[SZ_STR_DEV_NAME];
	INFO_DEV_CCM iDev;
};
struct INFO_CTRL_DEV_SCM {
	BOOL bUse;
	char strName[SZ_STR_DEV_NAME];
	INFO_DEV_SCM iDev;
};
struct INFO_CTRL_DEV_USM {
	BOOL bUse;
	char strName[SZ_STR_DEV_NAME];
	INFO_DEV_USM iDev;
};
struct INFO_CTRL_DEV_LGM {
	BOOL bUse;
	char strName[SZ_STR_DEV_NAME];
	INFO_DEV_LGM iDev;
};

struct INFO_CTRL_DEV_ALL {
	INFO_CTRL_DEV_CCM bufICDevCCM[MAX_NUM_CCM];
	INFO_CTRL_DEV_SCM bbufICDevSCM[MAX_NUM_CCM][MAX_NUM_SCM];
	INFO_CTRL_DEV_USM bbbufICDevUSM[MAX_NUM_CCM][MAX_NUM_SCM][MAX_NUM_USM];
	INFO_CTRL_DEV_LGM bbbufICDevLGM[MAX_NUM_CCM][MAX_NUM_SCM][MAX_NUM_LGM];

	int numDevCCM;
	int bufNumDevSCM[MAX_NUM_CCM];
	int bbufNumDevUSM[MAX_NUM_CCM][MAX_NUM_SCM];
	int bbufNumDevLGM[MAX_NUM_CCM][MAX_NUM_SCM];
};


enum {
	IDX_DISPI_RGN_ITEM,
	IDX_DISPI_RGN_SEL,
	IDX_DISPI_RGN_LTPM,
	IDX_DISPI_RGN_TMP_1,
	IDX_DISPI_RGN_TMP_2,
	IDX_DISPI_RGN_TMP_3,
	NUM_DISPI_RGN
};
enum {
	IDX_DISPI_PT_UL,
	IDX_DISPI_PT_UR,
	IDX_DISPI_PT_DR,
	IDX_DISPI_PT_DL,
	NUM_DISPI_PT
};
struct DOO_POINT {
	short x;
	short y;
};
struct INFO_DISP_ITEM {
	BYTE idxDevType;
	BYTE idxCCM;
	BYTE idxSCM;
	BYTE idxUSM_LGM;

	short szDI_Hor;
	short szDI_Ver;
	short nDI_Angle;
	short ptDrawOrgX;
	short ptDrawOrgY;

	DOO_POINT bbufPtDrawDisp[NUM_DISPI_RGN][NUM_DISPI_PT];

	BYTE bUseLTPM;	// "Long Term Parking Monitoring"
	BYTE LTPM_timeDay;
	BYTE LTPM_timeHour;
	BYTE LTPM_timeMin;

	BYTE bSelected;
};

#define MIN_SZ_DI_HOR				6
#define MIN_SZ_DI_VER				6

#define NUM_ZOOM_FIT_TO_SCR			-1
#define NUM_ZOOM_1_TO_1				256
#define NUM_ZOOM_MIN				(256 /16)
#define NUM_ZOOM_MAX				(256 *8)	// 16

struct INFO_ZOOM_PARAM {
	int nZoom;
	POINT ptOffset;
	SIZE szWndClient;
	SIZE szBackDrawing;
};

void SetPtDrawDisp_from_ZoomParam (INFO_DISP_ITEM *pIDI, INFO_ZOOM_PARAM *pZP);
int GetCurOpModeFromDI (INFO_DISP_ITEM *pIDI);

class CPS_ServAppView;
struct INFO_VIEW_STAT {
	HTREEITEM hTreeItem;
	CPS_ServAppView *pView;
};

#define SZ_STR_BACK_DRAWING_NAME		256
#define MAX_NUM_DISP_ITEM				8192
#define INC_NUM_DISP_ITEM				256
struct INFO_BACK_DRAWING_ITEM {
	BOOL bUse;

	char strName[SZ_STR_BACK_DRAWING_NAME];
	char strImgFilePath[MAX_PATH];

	INFO_VIEW_STAT iVS;

	int numDispItem;
	int maxDispItem;
	INFO_DISP_ITEM *bufDispItem;
};

#define MAX_NUM_MAIN_BDI		128
#define MAX_NUM_SUB_BDI			128
#define INC_NUM_BD_ITEM			32
struct INFO_BACK_DRAWING_ALL {
	int numMainBDI;
	int bufNumSubBDI[MAX_NUM_MAIN_BDI];

	int bufIdxMainBDI[MAX_NUM_MAIN_BDI];
	int bbufIdxSubBDI[MAX_NUM_MAIN_BDI][MAX_NUM_SUB_BDI];

	int numBDI;
	int maxBDI;
	INFO_BACK_DRAWING_ITEM *bufBDI;
};

struct STAT_PARKING_AREA {
	int nTotal;
	int nParked;
	int nFree;
};

void GetCurStatFromBDI (INFO_BACK_DRAWING_ITEM *pIBDI, STAT_PARKING_AREA &stPaAll, STAT_PARKING_AREA &stPa1F, STAT_PARKING_AREA &stPa2F, STAT_PARKING_AREA &stPa3F, STAT_PARKING_AREA &stPa4F, STAT_PARKING_AREA &stPa5F, STAT_PARKING_AREA &stPa6F);
void MakeStreamCurStatFromBDI (INFO_BACK_DRAWING_ITEM *pIBDI, BYTE *stPa1F, BYTE *stPa2F, BYTE *stPa3F, BYTE *stPa4F, BYTE *stPa5F, BYTE *stPa6F);
void UpdateCurDispStat ();


struct INFO_JUST_MADE_VIEW {
	volatile BOOL bInfoCopyOK;
	int idxMainBDI;
	int idxSubBDI;
};

class CWrapManNetComm;
class CPaneBD;
class CPaneInfoEboard;

struct INFO_GL_VAR_ALL {
	INFO_JUST_MADE_VIEW iJMV;
	CWrapManNetComm *pWMNC;
	CPaneBD *pPaneBD;
};

#define SZ_BUF_DUMMY_FOR_UN_GL_VAR_ALL		(16 *1024)
union UN_GL_VAR_ALL {
	BYTE bufDummy[SZ_BUF_DUMMY_FOR_UN_GL_VAR_ALL];
	INFO_GL_VAR_ALL iGVA;
};


#define STR_DEBUG_DATA_FORMAT		"DebugData_CCM%d.txt"
#define STR_INFO_BDA_FILE_NAME		"InfoBDA.dat"

struct INFO_GLOBAL {
	INFO_CTRL_DEV_ALL iCDA;
	INFO_BACK_DRAWING_ALL iBDA;
	UN_GL_VAR_ALL unGVA;
};

extern INFO_GLOBAL glInfoGlobal;
extern BOOL isConnectedCCM;

void ReadInitSettingsFromFile ();
void ReadInfoBDA ();
void WriteInfoBDA ();

int GetNumOfAllSCM ();
int GetNumOfAllUSM ();
int GetNumOfAllLGM ();



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#else
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


