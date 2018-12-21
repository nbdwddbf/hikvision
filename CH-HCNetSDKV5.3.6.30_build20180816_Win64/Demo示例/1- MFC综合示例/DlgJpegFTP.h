#if !defined(AFX_JPEGFTP_H__39FF7E80_EC20_4719_92E9_4151BD17BF0E__INCLUDED_)
#define AFX_JPEGFTP_H__39FF7E80_EC20_4719_92E9_4151BD17BF0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JpegFTP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJpegFTP dialog

class CJpegFTP : public CDialog
{
// Construction
public:
	CJpegFTP(CWnd* pParent = NULL);   // standard constructor
	int		m_iChannelnumber;
	LONG	m_lServerID;
	CString m_ServerIP;
	LONG	m_lStartChannel;
	int m_AlarmInNum;
	NET_DVR_FTPCFG m_ftpcfg;
	NET_DVR_JPEGCFG_V30 m_jpegcfg;
	int		m_nChanSel;
	void InitUI();
// Dialog Data
	//{{AFX_DATA(CJpegFTP)
	enum { IDD = IDD_DLG_JPEGFTP };
	CComboBox	m_UseFTPUpCtrl;
	CComboBox	m_SaveHDCtrl;
	CComboBox	m_QualityCtrl;
	CComboBox	m_PicSizeCtrl;
	CComboBox	m_NameItemCtrl;
	CComboBox	m_NameElementCtrl;
	CComboBox	m_DirMode2Ctrl;
	CComboBox	m_DirMode1Ctrl;
	CComboBox	m_DirLevelCtrl;
	CComboBox	m_ChanNumCtrl;
	CComboBox	m_AlarmInCtrl;
	DWORD	m_CardLen1;
	DWORD	m_CardLen2;
	CString	m_Delimiter;
	CString	m_EndSign1;
	CString	m_EndSign2;
	DWORD	m_EveryTimes;
	DWORD	m_FTPport;
	CString	m_FTPpsw;
	short	m_StartPos1;
	short	m_StartPos2;
	CString	m_StartSgin1;
	CString	m_StartSgin2;
	UINT	m_UpInterval;
	CString	m_FTPname;
	BOOL	m_bChan232_1;
	BOOL	m_bChan232_10;
	BOOL	m_bChan232_11;
	BOOL	m_bChan232_12;
	BOOL	m_bChan232_13;
	BOOL	m_bChan232_14;
	BOOL	m_bChan232_15;
	BOOL	m_bChan232_16;
	BOOL	m_bChan485_1;
	BOOL	m_bChan485_2;
	BOOL	m_bChan485_3;
	BOOL	m_bChan232_2;
	BOOL	m_bChan485_4;
	BOOL	m_bChan485_5;
	BOOL	m_bChan485_6;
	BOOL	m_bChan485_7;
	BOOL	m_bChan485_8;
	BOOL	m_bChan485_9;
	BOOL	m_bChan485_10;
	BOOL	m_bChan485_11;
	BOOL	m_bChan485_12;
	BOOL	m_bChan485_13;
	BOOL	m_bChan232_3;
	BOOL	m_bChan485_14;
	BOOL	m_bChan485_15;
	BOOL	m_bChan485_16;
	BOOL	m_bChanAlarm_1;
	BOOL	m_bChanAlarm_2;
	BOOL	m_bChanAlarm_3;
	BOOL	m_bChanAlarm_4;
	BOOL	m_bChanAlarm_5;
	BOOL	m_bChanAlarm_6;
	BOOL	m_bChanAlarm_7;
	BOOL	m_bChan232_4;
	BOOL	m_bChanAlarm_8;
	BOOL	m_bChanAlarm_9;
	BOOL	m_bChanAlarm_10;
	BOOL	m_bChanAlarm_11;
	BOOL	m_bChanAlarm_12;
	BOOL	m_bChanAlarm_13;
	BOOL	m_bChanAlarm_14;
	BOOL	m_bChanAlarm_15;
	BOOL	m_bChanAlarm_16;
	BOOL	m_bChan232_5;
	BOOL	m_bChan232_6;
	BOOL	m_bChan232_7;
	BOOL	m_bChan232_8;
	BOOL	m_bChan232_9;
	CString	m_FTPIP;
	UINT	m_CapInterval;
	BOOL	m_bCatchMode1;
	BOOL	m_bCatchMode2;
	BOOL	m_bCatchMode3;
	BOOL	m_bCatchMode4;
	BOOL	m_bCatchMode5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJpegFTP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
protected:
	void F_Show232ChanCtrl();
	void F_Show485ChanCtrl();
	void F_ShowAlarmInChanCtrl(int chan);
	void F_Set232ChanCtrl();
	void F_Set485ChanCtrl();
	void F_SetAlarmInChanCtrl(int chan);

	// Generated message map functions
	//{{AFX_MSG(CJpegFTP)
	afx_msg void OnButcancle();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombonameitem();
	afx_msg void OnSelchangeComboalarmin();
	afx_msg void OnSelchangeCombochannum();
	afx_msg void OnButalarminok();
	afx_msg void OnButpicqualityok();
	afx_msg void OnButjpegname();
	afx_msg void OnButsavejpeg();
	afx_msg void OnButsaveftp();
	afx_msg void OnButcatpic();
	afx_msg void OnSelchangeCombodirlevel();
	afx_msg void OnButtonUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPEGFTP_H__39FF7E80_EC20_4719_92E9_4151BD17BF0E__INCLUDED_)
