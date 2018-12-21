// VoiceDlg.h : header file
//

#if !defined(AFX_VOICEDLG_H__EF593A93_2D32_43D4_9479_D4EAA4A043A7__INCLUDED_)
#define AFX_VOICEDLG_H__EF593A93_2D32_43D4_9479_D4EAA4A043A7__INCLUDED_

#include "TalkMR.h"	// Added by ClassView
#include "VoiceTalk.h"	// Added by ClassView
#include "GeneralDef.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVoiceDlg dialog

class CVoiceDlg : public CDialog
{
// Construction
public:

	BOOL GetDevWorkState();
	BOOL DoLogin();
	int m_iVoiceChanNum;
//	LONG m_lUserID;
	BOOL m_bIsLogin;
//	NET_DVR_WORKSTATE_V30 m_DeviceState;
	LOCAL_DEVICE_INFO  m_DeviceInfo;           //设备信息
	CTalkMR m_TalkMR;
	CVoiceTalk m_VoiceTalk;
	CVoiceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVoiceDlg)
	enum { IDD = IDD_VOICE_DIALOG };
	CIPAddressCtrl	m_ctrlDevIp;
	CTabCtrl	m_ctrlTab;
	UINT	m_nDevPort;
	CString	m_csUser;
	CString	m_csPWD;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoiceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVoiceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTabVoice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonLogin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOICEDLG_H__EF593A93_2D32_43D4_9479_D4EAA4A043A7__INCLUDED_)
