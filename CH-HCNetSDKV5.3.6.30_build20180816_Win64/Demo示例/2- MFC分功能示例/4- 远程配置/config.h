// config.h : main header file for the CONFIG application

/**********************************************************
FileName:    config.h
Description: 该头文件导出所有要使用到的全局的结构体、宏、变量、函数, 在大部分的文件中需要包含该头文件   
Date:        
Note: 		 <全局>结构体,宏见GeneralDef.h, 变量,函数见ClientDemo.cpp   
Modification History:      
<version>    <time>         <desc>

***********************************************************/

#if !defined(AFX_CONFIG_H__42FE0A8B_CBAA_43ED_AA04_FA68666B99EB__INCLUDED_)
#define AFX_CONFIG_H__42FE0A8B_CBAA_43ED_AA04_FA68666B99EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "GeneralDef.h"
#include "HCNetSDK.h"



#define DETECT_AREA_LEFT 10//侦测区域最左坐标
#define DETECT_AREA_TOP 10//侦测区域最上坐标

//全局变量和全局函数在这里extern，其它文件包含config.h即可调用。
extern STRU_DEVICE_INFO g_struDeviceInfo[MAX_DEVICES];
extern LONG g_lUserID;
extern LPNET_DVR_MOTION_V30 g_lpMotionDetect;
extern LPNET_DVR_HIDEALARM_V30 g_lpHideAlarm;
extern LPNET_DVR_VILOST_V30 g_lpVILost;

extern void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn);
extern void g_CreateAlarmOutTree(CTreeCtrl &m_treeAlarmOut, int iDeviceIndex, BOOL *bAlarmOut);
extern BOOL DoGetDeviceResoureCfg(int iDeviceIndex);
extern void RefreshIPDevLocalCfg(int iDeviceIndex);
extern BOOL DoGetIPAlarmInCfg(int iDeviceIndex);
extern BOOL DoGetIPAlarmOutCfg(int iDeviceIndex);
extern BOOL CheckIPStr(CString ip);

/////////////////////////////////////////////////////////////////////////////
// CConfigApp:
// See config.cpp for the implementation of this class
//

class CConfigApp : public CWinApp
{
public:
	CConfigApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CConfigApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIG_H__42FE0A8B_CBAA_43ED_AA04_FA68666B99EB__INCLUDED_)
