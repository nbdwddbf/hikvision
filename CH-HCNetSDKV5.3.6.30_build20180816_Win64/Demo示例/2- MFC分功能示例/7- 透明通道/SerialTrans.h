// SerialTrans.h : main header file for the SERIALTRANS application
//

#if !defined(AFX_SERIALTRANS_H__8A8473FF_8939_4773_9917_5D008A82E0A7__INCLUDED_)
#define AFX_SERIALTRANS_H__8A8473FF_8939_4773_9917_5D008A82E0A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "GeneralDef.h"
/////////////////////////////////////////////////////////////////////////////
// CSerialTransApp:
// See SerialTrans.cpp for the implementation of this class
//

class CSerialTransApp : public CWinApp
{
public:
	CSerialTransApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialTransApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerialTransApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALTRANS_H__8A8473FF_8939_4773_9917_5D008A82E0A7__INCLUDED_)
