#if !defined(AFX_DLGGBT28181PROTOCOLACCESS_H__FA118BE7_2400_4900_9BFE_33BAA3996C36__INCLUDED_)
#define AFX_DLGGBT28181PROTOCOLACCESS_H__FA118BE7_2400_4900_9BFE_33BAA3996C36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGBT28181ProtocolAccess.h : header file
//
extern CClientDemoDlg *g_pMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CDlgGBT28181ProAccessUniform dialog
#include "ModifyRecord.h"
class GBT28181BM
{
public:
    BOOL Init(LPNET_DVR_GBT28181_CHANINFO_CFG lpSrc, LPNET_DVR_STREAM_INFO lpIndex,  DWORD max);             //初始化资源
    int  GetModify(LPNET_DVR_GBT28181_CHANINFO_CFG &lpModifySrc, LPNET_DVR_STREAM_INFO &lpIndex);        //获取修改过资源, 返回个数
    BOOL Update(DWORD dwNum, const NET_DVR_GBT28181_CHANINFO_CFG *ItemCfg, const NET_DVR_STREAM_INFO *struIndex);    //批量刷新项
    BOOL Update(const NET_DVR_GBT28181_CHANINFO_CFG &ItemCfg, const NET_DVR_STREAM_INFO &ItemInfo);   //刷新某一项 
    BOOL Modify(const NET_DVR_GBT28181_CHANINFO_CFG &ItemCfg, const NET_DVR_STREAM_INFO &ItemInfo);  //修改已有项
    BOOL Add(const NET_DVR_GBT28181_CHANINFO_CFG &ItemCfg, const NET_DVR_STREAM_INFO &ItemInfo);  //本地修改某一项
    int  GetNum();                         //获取数量
    bool GetSrc(LPNET_DVR_GBT28181_CHANINFO_CFG &lpSrc, LPNET_DVR_STREAM_INFO &lpIndex);    //获取原来的内存
    BOOL Del(int iIndex);       //删除某一项
    BOOL Clear();               //清楚修改记录
protected:
   
    bool ModifyCmp(const void *ItemF, const void *ItemS); //修改比较

private:
    ModRecord m_RecordInfo; 
    ModRecord m_RecordCfg;
};


class CDlgGBT28181ProAccessUniform : public CDialog
{
// Construction
public:
	CDlgGBT28181ProAccessUniform(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgGBT28181ProAccessUniform();
// Dialog Data
	//{{AFX_DATA(CDlgGBT28181ProAccessUniform)
	enum { IDD = IDD_DLG_GBT28181_PROTOCOL_UNIFORM };
	CComboBox	m_comTransProtocol;
	CComboBox	m_comProtocolVersion;
	CComboBox	m_cmbChanType;
	CComboBox	m_comDevStatus;
	CComboBox	m_comboVideoChannel;
	CComboBox	m_comboAlarmIn;
	CComboBox	m_comboStreamType;
	BOOL	m_bGBT28181Enable;
	CString	m_csIP;
	int		m_iHeartBeatInterval;
	int		m_iLocalSipPort;
	int		m_iRegisterValid;
	CString	m_csServerID;
	int		m_iServerSipPort;
	CString	m_csSipAuthenticateID;
	CString	m_csSipAuthenticatePasswd;
	CString	m_csSipUserName;
	int		m_iMaxHeartbeatTimeOut;
	CString	m_csAlarmInID;
	CString	m_csVideoChannelID;
	CString	m_csServerDomain;
	BOOL	m_BCodeChan;
	BOOL	m_BDecodeChan;
	BOOL	m_BAlarmInChan;
	DWORD	m_dwServerID;
	DWORD	m_dwVideCodeChan;
	BOOL	m_BVideoChanNotRelate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGBT28181ProAccessUniform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGBT28181ProAccessUniform)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnSelchangeComboAlarmIn();
	afx_msg void OnBtnGetalarm();
	afx_msg void OnBtnSetalarm();
	afx_msg void OnBtnSaveVideochannel();
	afx_msg void OnSelchangeComboVideoChannel();
	afx_msg void OnBtnGetVideochannel();
	afx_msg void OnBtnSetVideochannel();
	afx_msg void OnChkVm28181Notrelate();
	afx_msg void OnSelchangeChantype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
	DWORD	m_dwDevIndex;
    DWORD	m_dwAlarmOutNum;
	DWORD	m_dwAlarmInNum;
    DWORD   m_nChannel;
    DWORD   m_lStartChan;
	NET_DVR_GBT28181_ACCESS_CFG m_struGBT28181Accesscfg;
	void    GetParamFromWnd();
	void    SetParamFromWnd();
	inline BOOL ValidIPv6(BYTE *ip);
	BOOL CheckInitParam(BOOL bInit = true, int iInGroupNO = 0, int iOutGroupNO = 0);
	void CurCfgUpdate();
	CString m_csAlarmInName;
	NET_DVR_IPALARMINCFG m_struIPAlarmInCfg;
	BOOL m_bGetAlarmIn[MAX_ALARMIN_V30];
	BOOL m_bSetAlarmIn[MAX_ALARMIN_V30];
	NET_DVR_ALARMINCFG_V30 m_struAlarmInCfg[MAX_ALARMIN_V30];

	LPNET_DVR_ALARMIN_INFO m_pstruAlarmInInfoCond;
	LPNET_DVR_GBT28181_ALARMINCFG m_pstruGBT28181AlarmInCfg;

	LPNET_DVR_STREAM_INFO m_pstruStreamInfoCond;
	LPNET_DVR_GBT28181_CHANINFO_CFG m_pstruGBT28181ChanInfoCfg;
	int iAlarmInSel;

    TwoItemBM m_RecordBM;  
    int m_byTCPConnectMod;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGBT28181PROTOCOLACCESS_H__FA118BE7_2400_4900_9BFE_33BAA3996C36__INCLUDED_)
