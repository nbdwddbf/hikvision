#if !defined(AFX_MATPASSIVE_H__0269B17C_F6E2_4F8C_A979_A46C8041B623__INCLUDED_)
#define AFX_MATPASSIVE_H__0269B17C_F6E2_4F8C_A979_A46C8041B623__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatPassive.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatPassive dialog
//#define SUPPORT_WRITEFILE  1 //是否支持写文件(针对抓屏)
#define WM_DESKDATA          		WM_USER + 8    //
class CMatPassive : public CDialog
{
// Construction
public:
	CMatPassive(CWnd* pParent = NULL);   // standard constructor
    
	int m_iDeviceIndex;
    LONG m_lServerID;
    int m_iChannelNumber;
    LONG m_lStartChan;
    LONG m_lDevStartChan;

	NET_DVR_MATRIX_PASSIVEMODE m_PassiveMode; 
//	   static LONG m_lPassiveHandle[32];
//	   static LONG m_lUserID[32];
//     static LONG m_lRealHandle[32];
//     static HANDLE m_hFileThread[32];
//     static HANDLE m_hFileHandle[32];
//     static HANDLE m_hExitThread[32];
//     static HANDLE m_hThreadExit[32];
//     static LONG  m_lSel[32];
//     static CString m_strRecordFilePath[32];
#ifdef SUPPORT_SCE
	static HANDLE m_hDeskHandle;
#endif
#if SUPPORT_WRITEFILE
	static HANDLE m_hRecordHandle;
    static HANDLE m_hRecordHandle1;
#endif
	LRESULT DeskDataSend(WPARAM wParam, LPARAM lParam);

    // Dialog Data
	//{{AFX_DATA(CMatPassive)
	enum { IDD = IDD_DLG_MAT_PASSIVEDECODE };
	CComboBox	m_comboStreamType;
	CComboBox	m_GetStreamModeCtrl;
	CComboBox	m_DevChanCtrl;
	CIPAddressCtrl	m_ctrlDeviceIP;
	CComboBox	m_ComboTranPro;
	CComboBox	m_DecChanCombo;
	CString	m_strMcastIp;
	DWORD	m_dwPort;
	CString	m_csUserName;
	CString	m_csPsw;
	int		m_nLoginPort;
	CString	m_strFilePath;
	BOOL	m_bCycle;
	int		m_iStreamSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatPassive)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatPassive)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombodecchan();
	afx_msg void OnSure();
	afx_msg void OnSelchangeCombotranpro();
	afx_msg void OnStoppassivedecode();
	afx_msg void OnSenddata();
	afx_msg void OnStopsenddata();
	afx_msg void OnLogin();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnResume();
	afx_msg void OnBtnFast();
	afx_msg void OnBtnAudiooff();
	afx_msg void OnBtnAudioon();
	afx_msg void OnBtnNormal();
	afx_msg void OnBtnOnebyone();
	afx_msg void OnBtnSlow();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATPASSIVE_H__0269B17C_F6E2_4F8C_A979_A46C8041B623__INCLUDED_)
