// RealPlay.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RealPlay.h"
#include "RealPlayDlg.h"
#include "GeneralDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//全局变量
CRealPlayDlg *g_pMainDlg = NULL;

/////////////////////////////////////////////////////////////////////////////
// CRealPlayApp

BEGIN_MESSAGE_MAP(CRealPlayApp, CWinApp)
	//{{AFX_MSG_MAP(CRealPlayApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealPlayApp construction

CRealPlayApp::CRealPlayApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRealPlayApp object

CRealPlayApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRealPlayApp initialization

BOOL CRealPlayApp::InitInstance()
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

    NET_DVR_Init();          //Init SDK

	CRealPlayDlg dlg;
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

int CRealPlayApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	NET_DVR_Cleanup();
	return CWinApp::ExitInstance();
}
