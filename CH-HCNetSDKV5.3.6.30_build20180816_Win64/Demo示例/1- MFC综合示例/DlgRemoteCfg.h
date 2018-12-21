#pragma once
#include "afxcmn.h"
#include "SubDlgDeviceCfg.h"
#include "SubDlgChanCfg.h"
#include "SubDlgSerialCfg.h"
#include "SubDlgAlarmCfg.h"
#include "SubDlgUserCfg.h"
#include "SubDlgExceptionCfg.h"
#include "SubDlgATMInfoCfg.h"
#include "SubDlgMatDeccfg.h"
#include "DlgZeroChanCfg.h"
#include "SubDlgNetworkCfg.h"

// CDlgRemoteCfg dialog

class CDlgRemoteCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteCfg)

public:
	CDlgRemoteCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteCfg();

// Dialog Data


public:
	//{{AFX_DATA(CDlgRemoteCfg)
	enum { IDD = IDD_DLG_REMOTE_CFG };
	CTabCtrl m_tabRemoteCfg;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabRemoteCfg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRemoteSavePara();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnReboot();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	void RemoteConfigUpdate(int iConfigType);
	void SetDeviceIndex(int iDeviceIndex);
	void EnabeSubConfig(BOOL bEnable);
	void ChangeCurConfigWnd(int iConfigType);

	CSubDlgDeviceCfg m_subDlgDeviceCfg;
	CSubDlgChanCfg	m_subDlgChanCfg;
	CSubDlgSerialCfg m_subDlgSerialCfg;
	CSubDlgAlarmCfg m_subDlgAlarmCfg;
	CSubDlgUserCfg m_subDlgUserCfg;
	CSubDlgExceptionCfg	m_subDlgExceptionCfg;
	CSubDlgATMInfoCfg m_subDlgATMInfoCfg;
    CDlgZeroChanCfg m_subDlgZeroChanCfg;
	CMatDecCFG m_subDlgMatDecCfg;
	CSubDlgNetworkCfg m_subDlgNetworkCfg;

	int m_iDeviceIndex;
	LONG m_lLoginID;
	int m_iRemoteConfigType;
	// selected channel index
	int m_iChanIndex;
	void TabSet(void);
	int m_iDeviceType;
};
