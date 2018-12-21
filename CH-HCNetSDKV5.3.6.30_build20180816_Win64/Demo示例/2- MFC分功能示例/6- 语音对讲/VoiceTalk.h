#if !defined(AFX_VOICETALK_H__6E52F51B_7040_4409_933F_8F98E381B353__INCLUDED_)
#define AFX_VOICETALK_H__6E52F51B_7040_4409_933F_8F98E381B353__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include "GeneralDef.h"
// VoiceTalk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVoiceTalk dialog

class CVoiceTalk : public CDialog
{
// Construction
public:
	LONG m_lVoiceHandle;
	BOOL m_bIsRecording;
	int  m_iCurChanIndex;

	HMMIO m_hmmio;                 //ÒôÆµÎÄ¼þ¾ä±ú
	MMCKINFO    m_mmckinfoParent;
	MMCKINFO    m_mmckinfoChild;
	WAVEFORMATEX m_struWaveFormat;
	CVoiceTalk(CWnd* pParent = NULL);   // standard constructor

public:
	void SetChanRadioState(int iNum,BYTE *ChanStatus);
	int GetCurVoiceChanIndex();
	BOOL CreateWaveFile(char *sFileName);
	void StopRecord();
	void StartRecord();
	void StartVoiceTalk();
	void StopVoiceTalk();

// Dialog Data
	//{{AFX_DATA(CVoiceTalk)
	enum { IDD = IDD_DIALOG_VOICE_TALK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoiceTalk)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVoiceTalk)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTalk();
	afx_msg void OnButtonRecord();
	afx_msg void OnRadioAudio1();
	afx_msg void OnRadioAudio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICETALK_H__6E52F51B_7040_4409_933F_8F98E381B353__INCLUDED_)
