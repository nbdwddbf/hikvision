#if !defined(AFX_DLGGATEWAYCFG_H__33F64882_A763_444D_91BC_B07C2B8FC2A9__INCLUDED_)
#define AFX_DLGGATEWAYCFG_H__33F64882_A763_444D_91BC_B07C2B8FC2A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGatewayCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCfg dialog

class CDlgGatewayCfg : public CDialog
{
// Construction
public:
	CDlgGatewayCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGatewayCfg)
	enum { IDD = IDD_DLG_GATEWAY_CFG };
	CComboBox	m_LockWorkModeCtrl;
	CComboBox	m_comboGatewayIndex;

    CComboBox	m_comPicType;
	CComboBox	m_comboPicQuality;
	BOOL	m_bEnable;
	int		m_iDelayTime;
	CString	m_csName;
	BOOL	m_bLocalEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGatewayCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGatewayCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboGatewayIndex();
	afx_msg void OnBtnSetGateway();
	afx_msg void OnBntOpen();
	afx_msg void OnBntOpenAll();
	afx_msg void OnBntClose();
	afx_msg void OnBntCloseAll();
	afx_msg void OnBntAlwayopen();
	afx_msg void OnBntAllAlwaysopen();
	afx_msg void OnBntAlwaysclose();
	afx_msg void OnBntAllAlwaysclose();
	afx_msg void OnBntRecovery();
	afx_msg void OnBntAllRecovery();
    afx_msg void OnBntCapturePic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;        
    int     m_iDevIndex;
    DWORD   m_dwGatawayNum;     // 门禁个数 
    LONG    m_lGatewayIndex;    // 门禁索引
    NET_DVR_GATEWAY_CFG m_struGateway;

public:
    void InitWnd();
    void InitGatewayIndexCombo();
	void InitLockModeCombo();
    void SetGatewayCfgToWnd(NET_DVR_GATEWAY_CFG &struGateway);
    void GetGatewatCfgFromWnd(NET_DVR_GATEWAY_CFG &struGateway);
    
    BOOL GetGateWayCfg(NET_DVR_GATEWAY_CFG &struGateway);
    BOOL SetGateWayCfg(NET_DVR_GATEWAY_CFG &struGateway);

    BOOL ControlGateway(LONG lGatewayIndex, DWORD dwStaic);
    afx_msg void OnBnClickedBtnVisitorCallLadder();
    afx_msg void OnBnClickedBtnHouseholdCallLadder();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGATEWAYCFG_H__33F64882_A763_444D_91BC_B07C2B8FC2A9__INCLUDED_)
