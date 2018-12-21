#if !defined(AFX_DLGLEDCONFIGRECV_H__A24D48F6_4244_400A_9D69_1164E86EFC32__INCLUDED_)
#define AFX_DLGLEDCONFIGRECV_H__A24D48F6_4244_400A_9D69_1164E86EFC32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLedConfigRecv.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfigRecv dialog

class CDlgLedConfigRecv : public CDialog
{
// Construction
public:
	CDlgLedConfigRecv(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLedConfigRecv)
	enum { IDD = IDD_DLG_LED_CONFIG_RECV };
	CListCtrl	m_listGammaY;
	CComboBox	m_cmbGroupNo;
	CComboBox	m_cmbGrayLevel;
	CComboBox	m_cmbDClkDutyRadio;
	BOOL	m_bEnableGrayUniformity;
	BOOL	m_bEnableHGrayStripes;
	BOOL	m_bClearBadPoint;
	BOOL	m_bGhostShadowEhancedMode1;
	BOOL	m_bGhostShadowEhancedMode2;
	BOOL	m_bEnableSelfdefineRegistor;
	DWORD	m_dwAfterGlowCtrl;
	DWORD	m_dwDClkPhase;
	DWORD	m_dwDClkRate;
	DWORD	m_dwEndCol;
	DWORD	m_dwEndRow;
	DWORD	m_dwGClkCountNum;
	DWORD	m_dwGClkNum;
	DWORD	m_dwGClkRate;
	DWORD	m_dwHBlank;
	DWORD	m_dwLineFeedTime;
	DWORD	m_dwLineScanNum;
	DWORD	m_dwOutputNo;
	DWORD	m_dwRefreshCompleteGrayNum;
	DWORD	m_dwRefreshRate;
	DWORD	m_dwStartCol;
	DWORD	m_dwStartRow;
	DWORD	m_dwGammaEndCol;
	DWORD	m_dwGammaEndRow;
	DWORD	m_dwGammaOutputNo;
	DWORD	m_dwGammaStartCol;
	DWORD	m_dwGammaStartRow;
	DWORD	m_dwGammaY;
	DWORD	m_dwChip1High;
	DWORD	m_dwChip1Low;
	DWORD	m_dwChip2High;
	DWORD	m_dwChip2Low;
	DWORD	m_dwChip3High;
	DWORD	m_dwChip3Low;
	DWORD	m_dwElimanateShadowy;
	DWORD	m_dwElimanateGhostShadowLevel;
	DWORD	m_dwGrayEqualize1;
	DWORD	m_dwGrayEqualize2;
	CString	m_strDClkDutyRadio;
	CString	m_strGrayLevel;
	DWORD	m_dwHighEndCol;
	DWORD	m_dwHighEndRow;
	DWORD	m_dwHighOutputNo;
	DWORD	m_dwHighStartCol;
	DWORD	m_dwHighStartRow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLedConfigRecv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLedConfigRecv)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnBasicGet();
	afx_msg void OnBtnBasicSet();
	afx_msg void OnBtnGammaGet();
	afx_msg void OnBtnGammaModify();
	afx_msg void OnBtnGammaSet();
	afx_msg void OnBtnHighGet();
	afx_msg void OnBtnHighSet();
	afx_msg void OnSelchangeComboGroupNo();
	afx_msg void OnClickListGammaY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnHighOk();
	afx_msg void OnBtnSaveConfiguration();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_LED_GAMMA_CFG m_struGammaCfg;
	int m_iCurIndex;
	NET_DVR_LED_RECV_ADVANCED_CFG m_struAdvancedCfg;
	NET_DVR_LED_RECV_REGISTOR* m_lpRegistor;
	
public:
	void Init(LONG lUserID, int iDeviceIndex){m_lUserID = lUserID; m_iDeviceIndex = iDeviceIndex;};
	void UpdateCammaTable();
    afx_msg void OnBnClickedBtnVersion();
	CComboBox m_byGammaType;
	CComboBox m_byGammaModel;
    BYTE m_byDummyGClockHighTime;
    BYTE m_byFirstGClockExtendedTime;
    BYTE m_byDummyGClockCycle;
    BOOL m_byEnabledExGradientOptimition;
    BYTE m_byChip4High;
    BYTE m_byChip4Low;
    BYTE m_byChip5High;
    BYTE m_byChip5Low;
    BYTE m_byChip6High;
    BYTE m_byChip6Low;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLEDCONFIGRECV_H__A24D48F6_4244_400A_9D69_1164E86EFC32__INCLUDED_)
