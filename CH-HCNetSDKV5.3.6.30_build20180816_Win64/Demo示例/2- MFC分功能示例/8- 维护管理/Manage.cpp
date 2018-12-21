// Manage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Manage.h"
#include "ManageDlg.h"
#include "GeneralDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//全局变量
CManageDlg *g_pMainDlg = NULL;
/////////////////////////////////////////////////////////////////////////////
// CManageApp

BEGIN_MESSAGE_MAP(CManageApp, CWinApp)
	//{{AFX_MSG_MAP(CManageApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageApp construction

CManageApp::CManageApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CManageApp object

CManageApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CManageApp initialization

BOOL CManageApp::InitInstance()
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
	CManageDlg dlg;
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

int CManageApp::ExitInstance() 
{  
	NET_DVR_Cleanup();
	
	return CWinApp::ExitInstance();
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
/*#ifdef DEMO_LAN_CN
	sprintf(szDstLan, "%s", szLanCn);	
#else	
	sprintf(szDstLan, "%s", szLanEn);
#endif
	return;*/
    WORD wLangID=PRIMARYLANGID(::GetSystemDefaultLangID());
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