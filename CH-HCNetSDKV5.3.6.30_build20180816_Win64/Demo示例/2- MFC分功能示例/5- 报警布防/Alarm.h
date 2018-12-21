// Alarm.h : main header file for the Alarm application
//

#if !defined(AFX_Alarm_H__AC9F956D_5B2E_45F7_8526_86B40DED3B7E__INCLUDED_)
#define AFX_Alarm_H__AC9F956D_5B2E_45F7_8526_86B40DED3B7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "GeneralDef.h"
#include "HCNetSDK.h"
#include "DataType.h"
//extern 
extern LOCAL_DEVICE_INFO g_struDeviceInfo[MAX_DEVICES];

extern CString IPToStr(DWORD dwIP);
extern void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn);


/////////////////////////////////////////////////////////////////////////////
// CAlarmApp:
// See Alarm.cpp for the implementation of this class
//

class CAlarmApp : public CWinApp
{
public:
	CAlarmApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAlarmApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Alarm_H__AC9F956D_5B2E_45F7_8526_86B40DED3B7E__INCLUDED_)
