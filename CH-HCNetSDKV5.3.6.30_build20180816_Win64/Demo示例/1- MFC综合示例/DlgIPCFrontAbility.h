#if !defined(AFX_DLGIPCFRONTABILITY_H__8B41EBA8_0773_48A4_AC4B_6C8AC40C0BE1__INCLUDED_)
#define AFX_DLGIPCFRONTABILITY_H__8B41EBA8_0773_48A4_AC4B_6C8AC40C0BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPCFrontAbility.h : header file
//
#include "Markup.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgIPCFrontAbility dialog
#define MAX_WHILTE_BALANCE_MODE     32
#define MAX_EXPOSURE_MODE           32
#define MAX_EXPOSURE_SER            32
typedef struct tagCAMERA_WHITE_BALANCE
{
    BYTE    byWhiteBalanceMode[MAX_WHILTE_BALANCE_MODE];
}CAMERA_WHITE_BALANCE, *LPCAMERA_WHITE_BALANCE;

typedef struct tagCAMERA_EXPOSURE
{		
    BYTE    byExposureMode[MAX_EXPOSURE_MODE];
    BYTE    byExposureSet[MAX_EXPOSURE_SER];
    DWORD   dwMinExposureUserSet;
    DWORD   dwMaxExposureUserSet;
}CAMERA_EXPOSURE, *LPCAMERA_EXPOSURE;

#define  MAX_IRIS_MODE 32
typedef struct tagCAMERA_IRIS_MODE
{
    BYTE    byIrisMode[MAX_IRIS_MODE];
}CAMERA_IRIS_MODE, *LPCAMERA_IRIS_MODE;

typedef struct tagCAMERA_GAINLEVEL
{
    DWORD   dwMinGainLevel;
    DWORD   dwMaxGainLevel;
}CAMERA_GAINLEVEL, *LPCAMERA_GAINLEVEL;

typedef struct tagCAMERA_BRIGTH_LEVEL
{
    DWORD   dwMinBrightLevel;
    DWORD   dwMaxBrightLevel;
}CAMERA_BRIGTH_LEVEL, *LPCAMERA_BRIGTH_LEVEL;

typedef struct tagCAMERA_CONTRAST_LEVEL
{
    DWORD   dwMinContrastLevel;
    DWORD   dwMaxContrastLevel;
}CAMERA_CONTRAST_LEVEL, *LPCAMERA_CONTRAST_LEVEL;

typedef struct tagCAMERA_SHARP_LEVEL
{
    DWORD   dwMinSharpnessLevel;
    DWORD   dwMaxSharpnessLevel;
}CAMERA_SHARP_LEVEL, *LPCAMERA_SHARP_LEVEL;

typedef struct tagCAMERA_SATURATION_LEVEL
{   
    DWORD   dwMinSaturationLevel;
    DWORD   dwMaxSaturationLevel;
}CAMERA_SATURATION_LEVEL, *LPCAMERA_SATURATION_LEVEL;

#define MAX_FILTER_TYPE 32
typedef struct tagCAMERA_DAYLIGHT_FILTER
{
    BYTE    byFilterType[MAX_FILTER_TYPE];
}CAMERA_DAYLIGHT_FILTER, *LPCAMERA_DAYLIGHT_FILTER;

#define  MAX_SWITCH_SCHED_ENABLE    8
#define  MAX_FILTER_LEVEL           32
typedef struct tagCAMERA_SWITCH_SCHEDULE
{  
    BYTE    bySwitchScheduleEnabled[MAX_SWITCH_SCHED_ENABLE];
    BYTE    byDayToNightFilterLevel[MAX_FILTER_LEVEL];
    BYTE    byNightToDayFilterLevel[MAX_FILTER_LEVEL];
    DWORD   dwMinDayNightFilterTime;
    DWORD   dwMaxDayNightFilterTime;
}CAMERA_SWITCH_SCHEDULE, *LPCAMERA_SWITCH_SCHEDULE;

#define MAX_BACKLIGHT_MODE  32
typedef struct tagCAMERA_BACKLIGHT
{
    BYTE    byBacklightMode[MAX_BACKLIGHT_MODE];
}CAMERA_BACKLIGHT, *LPCAMERA_BACKLIGHT;

#define MAX_MIRROR 32
typedef struct tagCAMERA_MIRROR
{
    BYTE    byMirror[MAX_MIRROR];
}CAMERA_MIRROR, *LPCAMERA_MIRROR;

#define MAX_LOCAL_OUTPUT 32
typedef struct tagCAMERA_LOCALOUTPUT
{   
    BYTE    byLocalOutput[MAX_LOCAL_OUTPUT];
}CAMERA_LOCALOUTPUT, *LPCAMERA_LOCALOUTPUT;

typedef struct tagCAMERA_PARAM
{
    CAMERA_WHITE_BALANCE    struWhiteBalance;
    CAMERA_EXPOSURE         struExposure;
    CAMERA_IRIS_MODE        struIrisMode;
    CAMERA_GAINLEVEL        struGainLevel;
    CAMERA_BRIGTH_LEVEL     struBrightLevel;
    CAMERA_CONTRAST_LEVEL   struContrastLevel;
    CAMERA_SHARP_LEVEL      struSharpLevel;
    CAMERA_SATURATION_LEVEL struSaturationLevel;
    CAMERA_DAYLIGHT_FILTER  struDaylightFilter;
    CAMERA_SWITCH_SCHEDULE  struSwitchSchedule;
    CAMERA_BACKLIGHT        struBackLight;
    CAMERA_MIRROR           struMirror;
    CAMERA_LOCALOUTPUT      struLocalOutput;
}CAMERA_PARAM, *LPCAMERA_PARAM;

class CDlgIPCFrontAbility : public CDialog
{
// Construction
public:
	CDlgIPCFrontAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIPCFrontAbility)
	enum { IDD = IDD_DLG_IPC_FRONT_ABILITY };
	CListBox	m_listWhiteBalanceMode;
	CListBox	m_listSwitchSchedEnable;
	CListBox	m_listNightToDayFilterLevel;
	CListBox	m_listMirror;
	CListBox	m_listLocalOutput;
	CListBox	m_listIrisMode;
	CListBox	m_listExposureSet;
	CListBox	m_listExposureMode;
	CListBox	m_listDaylightFilterType;
	CListBox	m_listDayToNightFilterLevel;
	CListBox	m_listBackLightMode;
	int		m_iMaxContrastLevel;
	int		m_iMaxDayNightFilterTime;
	int		m_iMaxExposure;
	int		m_iMaxGainLevel;
	int		m_iMaxSaturationLevel;
	int		m_iMaxSharpLevel;
	int		m_iMinBrightLevel;
	int		m_iMinContrastLevel;
	int		m_iMinDayNightFilterTime;
	int		m_iMinExposure;
	int		m_iMinGainLevel;
	int		m_iMinSaturationLevel;
	int		m_iMinSharpLevel;
	int		m_iMaxBrightLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPCFrontAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPCFrontAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    char*   m_pRecvBuf;
    LONG    m_lServerID;
    int     m_iDevIndex;
    CAMERA_PARAM m_struCameraParam;
public:
    BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
 
    BOOL GetIPCFrontAbility();
    BOOL ParseIPCFrontAbility(char *pBuf, DWORD dwBufSize);
    BOOL ParseIPCFrontAbilityXml(CMarkup &struMarkup);
    BOOL ParseWhilteBalanceXml(CMarkup &struMarkup);
    BOOL ParseExposureXml(CMarkup &struMarkup);
    BOOL ParseIrisModeXml(CMarkup &struMarkup);
    BOOL ParseGainLevelXml(CMarkup &struMarkup);
    BOOL ParseBrightLevelXml(CMarkup &struMarkup);
    BOOL ParseContrastLevelXml(CMarkup &struMarkup);
    BOOL ParseSharpLevelXml(CMarkup &struMarkup);
    BOOL ParseSaturationLevelXml(CMarkup &struMarkup);
    BOOL ParseDayligthFilterXml(CMarkup &struMarkup);
    BOOL ParseSwitchScheduleXml(CMarkup &struMarkup);
    BOOL ParseBackLightXml(CMarkup &struMarkup);
    BOOL ParseMirrorXml(CMarkup &struMarkup);
    BOOL ParseLocalOutput(CMarkup &struMarkup);

    void SetWhiteBalanceToWnd(CAMERA_WHITE_BALANCE &struWhiteBalance);
    void SetExposureToWnd(CAMERA_EXPOSURE &struExposure);
    void SetIrisModeToWnd(CAMERA_IRIS_MODE &struIrisMode);
    void SetGainLevelToWnd(CAMERA_GAINLEVEL &struGainLevel);
    void SetBrightLevelToWnd(CAMERA_BRIGTH_LEVEL &struBrightLevel);
    void SetContrastLevelToWnd(CAMERA_CONTRAST_LEVEL &struContrastLevel);
    void SetSharpLevelToWnd(CAMERA_SHARP_LEVEL &struSharpLevel);
    void SetSaturationLevel(CAMERA_SATURATION_LEVEL &struSaturationLevel);;
    void SetDayligthFilterToWnd(CAMERA_DAYLIGHT_FILTER &struDaylightFilter);
    void SetSwitchScheduleToWnd(CAMERA_SWITCH_SCHEDULE &struSwitchSchedule);
    void SetBackLightToWnd(CAMERA_BACKLIGHT &struBackLight);
    void SetMirrorToWnd(CAMERA_MIRROR &struMirror);
    void SetLocalOutputToWnd(CAMERA_LOCALOUTPUT &struLocakOutput);
    void SetIPCFrontAbilityToWnd(CAMERA_PARAM &struCameraParam);

    void ParseStrIndex(CString strIndex, byte* array, int iArrayLength);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPCFRONTABILITY_H__8B41EBA8_0773_48A4_AC4B_6C8AC40C0BE1__INCLUDED_)
