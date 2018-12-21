#if !defined(AFX_DLGTHIRDGENERATIONCFG_H__78E6FACD_F792_4228_AF86_3DAEF602FD14__INCLUDED_)
#define AFX_DLGTHIRDGENERATIONCFG_H__78E6FACD_F792_4228_AF86_3DAEF602FD14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThirdGenerationCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThirdGenerationCfg dialog
#define  COMMANDLEN 1024

static char sAlarmstring[35][32] = 
{
    "HDD Full" ,
    "HDD Error" ,
    "Cable DisConnect" ,
    "IP Conflict" ,
    "Illegal Access" ,
    "Vi Exception" ,
    "VS Mismatch" ,
    "Vi Lost" ,
    "Audio Lost" ,
    "AlarmIn Exc" ,
    "Mask Alarm" ,
    "Modect" ,
    "Record Exc" ,
	"Wireless Exception" ,
	"PIR Exception" ,
	"CallHelp Exception" ,
	"Audio Detection" ,
	"SceneChange Detection" ,
	"Defocus Detection" ,
	"Face Detection" ,
	"Line Detection" ,
	"Field Detection" ,
	"Region Exiting Detection" ,	
	"Region Entrance Detection" ,
	"Loitering Detection" ,
	"Group Detection" ,
	"RapidMode Detection" ,
	"Parking Detection" ,
	"UnattendedBaggage Detection" ,
	"AttendedBaggage Detection" ,
    "DataTraffic Excess",
    "Support SMS Alarm" ,
    "Support SMS Ctrl" ,
	"Support SMS Reboot",
    "Support Call Ctrl"
};
class CDlgThirdGenerationCfg : public CDialog
{
// Construction
public:
	CDlgThirdGenerationCfg(CWnd* pParent = NULL);   // standard constructor

	NET_DVR_CMSPARAM m_struCmsParam;

	NET_DVR_DIALREQUEST m_struDialRequest;
	NET_DVR_DIALPARAM   m_struDialParam;
	NET_DVR_SMSRELATIVEPARAM_V50 m_struSmsRelativeParam;

	NET_DVR_DIALSTATUS m_struDialStatus;

	LONG m_lServerID;

// Dialog Data
	//{{AFX_DATA(CDlgThirdGenerationCfg)
	enum { IDD = IDD_DLG_3GCONFIG };
	CTreeCtrl	m_TreeAlarm;
	CComboBox	m_WhiteListCtrl;
	CComboBox	m_MaxDownBitCtrl;
	CComboBox	m_MaxUpBitCtrl;
	CComboBox	m_RealModeCtrl;
	CComboBox	m_UimInfoCtrl;
	CComboBox	m_StatusCtrl;
	CComboBox	m_PinCommandCtrl;
	CListCtrl	m_SmsList;
	CComboBox	m_VerifyProCtrl;
	CComboBox	m_TrafficClassCtrl;
	CComboBox	m_SwitchModeCtrl;
	CComboBox	m_NetTypeCtrl;
	CComboBox	m_DialModeCtrl;
	CComboBox	m_ConnNumCtrl;
	CString	m_strCmsIp;
	int		m_iCmsPort;
	CString	m_strPicIp;
	int		m_iPicPort;
	CString	m_strPsw;
	CString	m_strPuId;
	BOOL	m_bEnable3G;
	CString	m_strApn;
	CString	m_strDialNum;
	CString	m_strLocalIp;
	int		m_iOffLineTime;
	CString	m_strPassword;
	CString	m_strRemoteIp;
	CString	m_strUserName;
	int		m_iMtuSize;
	BOOL	m_bEnableSmsAlarm;
	CTime	m_tmStartDate;
	CTime	m_tmStartTime;
	CTime	m_tmStopDate;
	CTime	m_tmStopTime;
	int		m_iSmsNum;
	BOOL	m_bPinLockEnable;
	CString	m_strPinCode;
	CString	m_strPinNewCode;
	int		m_iRemainPinTime;
	int		m_iRemainPukTime;
	CString	m_strSmsContent;
	int		m_iSmsSeq;
	CString	m_strPhoneNumber;
	CString	m_strWireDnsIp;
	CString	m_strWireLocalIp;
	CString	m_strWireMaskIp;
	CString	m_strWireRemoteIp;
	int		m_iStatus;
	int		m_iUpMaxBitrate;
	int		m_iDownMaxBitrate;
	CString	m_strDialStatus;
	int		m_iUdpPort;
	BOOL	m_bEnableAlarm;
	CString	m_strWhiteList;
	CString	m_strUinPhone;
	//}}AFX_DATA

    int     m_iPhoneCount;
    int     m_iAlarmCount;

    void	CreateTree(void);
    void    GetAlarmCount();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThirdGenerationCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgThirdGenerationCfg)
	afx_msg void OnButtonExit();
	afx_msg void OnButtonSetcms();
	afx_msg void OnButtonGetcms();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetdial();
	afx_msg void OnButtonGetdial();
	afx_msg void OnButtonSetsmsrelative();
	afx_msg void OnButtonGetsmsrelative();
	afx_msg void OnButtonGetdialstatus();
	afx_msg void OnButtonGetsmslist();
	afx_msg void OnButtonSendsms();
	afx_msg void OnButtonGetsms();
	afx_msg void OnButtonGetpinstatus();
	afx_msg void OnButtonSetpincode();
	afx_msg void OnChangeEditSmscontent();
	afx_msg void OnSelchangeComboWhitelist();
	afx_msg void OnClickTreeWhitelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnButtonSure();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHIRDGENERATIONCFG_H__78E6FACD_F792_4228_AF86_3DAEF602FD14__INCLUDED_)
