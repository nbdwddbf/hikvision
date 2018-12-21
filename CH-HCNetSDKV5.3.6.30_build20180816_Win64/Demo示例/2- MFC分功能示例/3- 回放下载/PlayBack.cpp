// PlayBack.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PlayBack.h"
#include "PlayBackDlg.h"
#include "HCNetSDK.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//全局变量
LOCAL_DEVICE_INFO g_struDevInfo[MAX_DEVICE]; //设备数组
CPlayBackDlg *g_pMainDlg;                    //主窗口
int g_iCurDevIndex;
int g_iCurChanIndex;

vector <NET_DVR_FINDDATA_V30> g_vecFileInfo;   //获取的文件数组


/////////////////////////////////////////////////////////////////////////////
// CPlayBackApp

BEGIN_MESSAGE_MAP(CPlayBackApp, CWinApp)
	//{{AFX_MSG_MAP(CPlayBackApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayBackApp construction

CPlayBackApp::CPlayBackApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPlayBackApp object

CPlayBackApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPlayBackApp initialization

BOOL CPlayBackApp::InitInstance()
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

	NET_DVR_Init();

	CPlayBackDlg dlg;
	m_pMainWnd = &dlg;
	g_pMainDlg = &dlg;
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

int CPlayBackApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	NET_DVR_Cleanup();
	return CWinApp::ExitInstance();
}
