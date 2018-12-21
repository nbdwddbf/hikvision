// Alarm.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Alarm.h"
#include "AlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LOCAL_DEVICE_INFO g_struDeviceInfo[MAX_DEVICES];

void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn);
/////////////////////////////////////////////////////////////////////////////
// CAlarmApp

BEGIN_MESSAGE_MAP(CAlarmApp, CWinApp)
	//{{AFX_MSG_MAP(CAlarmApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmApp construction

CAlarmApp::CAlarmApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAlarmApp object

CAlarmApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAlarmApp initialization

BOOL CAlarmApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	NET_DVR_Init();  // init DVR
	CAlarmDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CString IPToStr(DWORD dwIP)
{
	CString strIP = _T("");
	WORD add1,add2,add3,add4;
	
	add1=(WORD)(dwIP&255);
	add2=(WORD)((dwIP>>8)&255);
	add3=(WORD)((dwIP>>16)&255);
	add4=(WORD)((dwIP>>24)&255);
	strIP.Format("%d.%d.%d.%d",add4,add3,add2,add1);
	return strIP;
}

/*********************************************************
Function:	g_StringLanType
Desc:		get the current operation language string type
Input:	szLanCn, Chinese string; szLanEn, English string;
Output:	szDstLan, current string
Return:	none
**********************************************************/
void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn)
{
#ifdef DEMO_LAN_CN
	sprintf(szDstLan, "%s", szLanCn);	
#else	
	//sprintf(szDstLan, "%s", szLanEn);
	sprintf(szDstLan, "%s", szLanCn);
#endif
	return;
    WORD wLangID=(WORD)(PRIMARYLANGID(::GetSystemDefaultLangID()));
    switch(wLangID)
    {
	case LANG_ENGLISH:
		sprintf(szDstLan, "%s", szLanEn);
		break;
	case LANG_CHINESE:
		sprintf(szDstLan, "%s", szLanCn);
		break;
	default:
		sprintf(szDstLan, "%s", szLanEn);
		break;
	}	
}

