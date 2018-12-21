#if !defined(AFX_DLGREMOTEIPACCESS_H__DA5A49ED_C450_47D4_8541_74E92AA55F2C__INCLUDED_)
#define AFX_DLGREMOTEIPACCESS_H__DA5A49ED_C450_47D4_8541_74E92AA55F2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteIPAccess.h : header file
//

#include "DlgIPAccessCfgDDNS.h"
#include "DlgIPAccessCfgIPServer.h"
#include "DlgIPAccessCfgStreamServer.h"
#include "DlgIPAccessCfgEasyDDNS.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteIPAccess dialog
char *GetDeviceAddress(LPNET_DVR_IPDEVINFO_V31 lpDeviceInfo);
void SetDeviceAddress(LPNET_DVR_IPDEVINFO_V31 lpDevInfo, char *lpAddress);
class CDlgRemoteIPAccess : public CDialog
{
// Construction
public:	
	DWORD m_dwDevIndex;
	CDlgRemoteIPAccess(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteIPAccess();

	int m_iCurSel;//the select item index in the list
	int m_iCurChanNO;    //0-MAX_CHANNUM_V30 + groupNO*64
	int m_iCurChanIndex; //0-MAX_CHANNUM_V30
	BOOL m_bCurEnable;   //is the channel added or not
	int m_iSelAccessType;
	BOOL m_bAnalogChange;

	CImageList m_TreeImage;
	NET_DVR_IPPARACFG_V40 m_struIPParaCfgV40;
	NET_DVR_IPALARMOUTCFG m_struIPAlarmOutCfg;
	NET_DVR_IPALARMINCFG m_struIPAlarmInCfg;
	NET_DVR_IPC_PROTO_LIST m_struProtoList;
	void CheckInitParam();
	void UpdateGroup(int iGroupNO);
	void EnableInfoCtrl(BOOL bEnable);
	void SetCtrlStat(int iStat);
	void UpdateDataByGroupNo(DWORD dwGroupNO);
	BOOL FindDataByIp(char *lpDevIpAddress,  LPDWORD dwIPDevIndex,DWORD dwProtoType = 0);
	DWORD m_dwStartChan;
	char m_szProType[64];//协议类型字符串
	char* ProIndexToStr(int iProType);
	void DeleteDevIPByIP(DWORD dwIPID, DWORD dwIPChanIndex);
// Dialog Data
	//{{AFX_DATA(CDlgRemoteIPAccess)
	enum { IDD = IDD_DLG_REMOTE_IP_ACCESS_CFG };
	CComboBox	m_comboIPStreamType;
	CComboBox	m_comboTransProtocol;
	CComboBox	m_comboTransProtTypeUrl;
	CComboBox	m_comboChannelGroupNO;
	CComboBox	m_comboStreamType;
	CComboBox	m_comboProType;
	CListCtrl	m_listIPChan;
	CString	m_csDevIP;
	UINT	m_uDevPort;
	CString	m_csDevPwd;
	CString	m_ceDevUserName;
	int		m_iIPDevChan;
	BOOL	m_bStreamUrlEnable;
	CString	m_csStreamServerUrl;
	int		m_iDeviceIdUrl;
	int		m_iChannelNumUrl;
	CString	m_strActivatePwd;
    LPNET_DVR_PROTO_TYPE m_lpProtoType;
    NET_DVR_IPC_PROTO_LIST_V41 m_struProtocolListV41;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteIPAccess)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteIPAccess)
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBtnAddIPChan();
	afx_msg void OnClickListIPChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnEnable();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnQuickAdd();
	afx_msg void OnSelchangeComboStreamType();
	afx_msg void OnBtnStreamUrlSet();
	afx_msg void OnSelchangeComboChannelGroupNo();
	afx_msg void OnButtonUpdateProList();
	afx_msg void OnButtonCustomPro();
	afx_msg void OnBtnGetDevChannel();
	afx_msg void OnBtnActivate();
	afx_msg void OnSelchangeComboProtype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void GetCurChanNo();

public:
	void ShowInfoByGetStreamType(int iType);
	void ShowDeviceInfo(BOOL bShow);
	void ShowStreamUrl(BOOL bShow);

	//Set channel information by the type of getting stream.
	void SetChannelInfobyStreamType(BOOL bAnalog);

	//Is enable or online?
	void ShowIsEnableOrOnlineInList(int iRowIndex, int iColumnIndex, int iArrayIndex);
	void GetIsEnableString(BOOL bEnable, char *pStrEnable);

	void SetChannelEnable(BOOL bEnable);

public:
	DWORD m_dwMode; //取流模式
	CDlgIPAccessCfgDDNS *m_pDlgIPAccessDDNS;
	CDlgIPAccessCfgIPServer *m_pDlgIPAccessIPServer;
	CDlgIPAccessCfgStreamServer *m_pDlgIPAccessStreamServer;
	DlgIPAccessCfgEasyDDNS *m_pDlgIPAccessCfgEasyDDNS;
    CComboBox m_cmbCameraType;
    BOOL m_bIPCActivatePassword;
    BOOL m_bAutoTiming;
    CString m_strRtspUrl;
    afx_msg void OnCbnSelchangeComboDvrTransProtocol();
    BOOL m_bEnableCertValidation;
    BOOL m_bEnableDefaltPort;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTEIPACCESS_H__DA5A49ED_C450_47D4_8541_74E92AA55F2C__INCLUDED_)
