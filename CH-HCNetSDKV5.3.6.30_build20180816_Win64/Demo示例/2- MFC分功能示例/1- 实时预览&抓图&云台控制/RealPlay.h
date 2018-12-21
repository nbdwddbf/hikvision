// RealPlay.h : main header file for the REALPLAY application
//

#if !defined(AFX_REALPLAY_H__7C80A991_2BBF_43C0_919C_02C3E47A0EEF__INCLUDED_)
#define AFX_REALPLAY_H__7C80A991_2BBF_43C0_919C_02C3E47A0EEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "RealPlayDlg.h"

extern CRealPlayDlg *g_pMainDlg;


/////////////////////////////////////////////////////////////////////////////
// CRealPlayApp:
// See RealPlay.cpp for the implementation of this class
//

class CRealPlayApp : public CWinApp
{
public:
	CRealPlayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealPlayApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRealPlayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALPLAY_H__7C80A991_2BBF_43C0_919C_02C3E47A0EEF__INCLUDED_)
