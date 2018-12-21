// PlayBack.h : main header file for the PLAYBACK application
//

#if !defined(AFX_PLAYBACK_H__4EAF9B60_44B2_4B34_A35F_ADAD057C4241__INCLUDED_)
#define AFX_PLAYBACK_H__4EAF9B60_44B2_4B34_A35F_ADAD057C4241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "GeneralDef.h"
#include "PlayBackDlg.h"
#include <vector>

using  std::vector; 


extern LOCAL_DEVICE_INFO g_struDevInfo[MAX_DEVICE]; //设备数组
extern CPlayBackDlg *g_pMainDlg;                    //主窗口
extern int g_iCurDevIndex;
extern int g_iCurChanIndex;
extern vector <NET_DVR_FINDDATA_V30> g_vecFileInfo;

/////////////////////////////////////////////////////////////////////////////
// CPlayBackApp:
// See PlayBack.cpp for the implementation of this class
//

class CPlayBackApp : public CWinApp
{
public:
	CPlayBackApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayBackApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPlayBackApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACK_H__4EAF9B60_44B2_4B34_A35F_ADAD057C4241__INCLUDED_)
