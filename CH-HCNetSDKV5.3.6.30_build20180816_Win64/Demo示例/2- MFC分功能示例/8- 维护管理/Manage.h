// Manage.h : main header file for the MANAGE application
//

#if !defined(AFX_MANAGE_H__F8C915BC_7F13_4C9D_B7A7_D786F11327F9__INCLUDED_)
#define AFX_MANAGE_H__F8C915BC_7F13_4C9D_B7A7_D786F11327F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ManageDlg.h"


extern CManageDlg *g_pMainDlg;
void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn);
/////////////////////////////////////////////////////////////////////////////
// CManageApp:
// See Manage.cpp for the implementation of this class
//

class CManageApp : public CWinApp
{
public:
	CManageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CManageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGE_H__F8C915BC_7F13_4C9D_B7A7_D786F11327F9__INCLUDED_)
