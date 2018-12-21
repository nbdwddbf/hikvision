// Voice.h : main header file for the VOICE application
//

#if !defined(AFX_VOICE_H__82F940ED_274A_483D_8CCF_1C577E35B857__INCLUDED_)
#define AFX_VOICE_H__82F940ED_274A_483D_8CCF_1C577E35B857__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "VoiceDlg.h"
#include "GeneralDef.h"

extern CVoiceDlg *g_pMainDlg;


//Wav
#define BITS_PER_SAMPLE		16
#define CHANNEL				1
#define SAMPLES_PER_SECOND	16000

#define BIT_RATE_16000		16000
#define AUDENCSIZE          1280
#define AUDDECSIZE          80
#define BUFFER_SIZE         1280
#define BUFFER_NUM           6
#define AUDIOBUF			(80*40L)
/////////////////////////////////////////////////////////////////////////////
// CVoiceApp:
// See Voice.cpp for the implementation of this class
//

class CVoiceApp : public CWinApp
{
public:
	CVoiceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoiceApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVoiceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICE_H__82F940ED_274A_483D_8CCF_1C577E35B857__INCLUDED_)
