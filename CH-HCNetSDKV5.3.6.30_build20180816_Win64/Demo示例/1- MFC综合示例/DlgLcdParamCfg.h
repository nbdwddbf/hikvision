#if !defined(AFX_DLGLCDPARAMCFG_H__958AEEAA_4D9F_4652_9F91_86FF698DC97F__INCLUDED_)
#define AFX_DLGLCDPARAMCFG_H__958AEEAA_4D9F_4652_9F91_86FF698DC97F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdParamCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdParamCfg dialog

class CDlgLcdParamCfg : public CDialog
{
// Construction
public:
	CDlgLcdParamCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdParamCfg)
	enum { IDD = IDD_DLG_LCD_PARAM_CFG };
	CComboBox	m_cmbTemperatureStatus;
	CComboBox	m_cmbExceptStatus;
	CComboBox	m_comboImageMode;
	CComboBox	m_comboNoSignal;
	CStatic	m_csStatus;
	CComboBox	m_comboY;
	CComboBox	m_comboX;
	CComboBox	m_comboWorkMode;
	CComboBox	m_comboWidth;
	CComboBox	m_comboTransparent;
	CComboBox	m_comboSourcePip;
	CComboBox	m_comboScreenNo;
	CComboBox	m_comboParamType;
	CComboBox	m_comboLanguage;
	CComboBox	m_comboInterface;
	CComboBox	m_comboHeight;
	CComboBox	m_comboFanStatus;
	CComboBox	m_comboDuration;
	CComboBox	m_comboDisplayMode;
	CComboBox	m_comboDefogMode;
	CComboBox	m_comboDefogLevel;
	CComboBox	m_comboDefogEnable;
	CComboBox	m_comboPipColor;
	BOOL	m_bAutoAdjust;
	BOOL	m_bEnableEdge;
	BOOL	m_bEnablePip;
	BOOL	m_bEnableLogo;
	BYTE	m_byBackLight;
	BYTE	m_byBlue;
	int		m_iBoardTemp;
	BYTE	m_byBrightness;
	BYTE	m_byBlueOffset;
	BYTE	m_byClock;
	BYTE	m_byContrast;
	BYTE	m_byGainB;
	BYTE	m_byGainG;
	BYTE	m_byGainR;
	BYTE	m_byGreen;
	DWORD	m_dwPipHeight;
	BYTE	m_byGreenOffset;
	BYTE	m_byHorizontal;
	BYTE	m_byHue;
	BYTE	m_byLeft;
	BYTE	m_byLower;
	BYTE	m_byOffsetB;
	BYTE	m_byOffsetG;
	BYTE	m_byOffsetR;
	BYTE	m_byPhase;
	BYTE	m_byRed;
	BYTE	m_byRedOffset;
	BYTE	m_byRight;
	BYTE	m_bySaturation;
	BYTE	m_bySharpness;
	CString	m_csSoftVersion;
	BYTE	m_byTempValue;
	BYTE	m_byTop;
	BYTE	m_byVertical;
	BYTE	m_byWallNo;
	DWORD	m_dwPipWidth;
	DWORD	m_dwWorkingHours;
	DWORD	m_dwPipX;
	DWORD	m_dwPipY;
	BOOL	m_bEnableMute;
	int		m_iBalance;
	DWORD	m_dwVolume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdParamCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdParamCfg)
	virtual BOOL OnInitDialog();	
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeComboScreenNo();
    afx_msg LRESULT OnMessUpdateInterface(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserId;
    int m_iDeviceIndex;
    LONG m_lCfgHandle;
    HANDLE m_hThread;
    BOOL m_bExitThread;
    DWORD m_dwCfgNum;
    DWORD m_dwCurrentScreenNo;

    NET_DVR_MSC_SCREEN_PARAM_COND m_struCond;
    NET_DVR_MSC_SCREEN_REMOTE_CFG m_struSet;
    LPNET_DVR_MSC_SCREEN_PARAM_CFG m_lpScreenParam;

private:
    void SaveParam();
    static UINT LcdParamCfgWaitThread(LPVOID pParam);
    BOOL m_BPressGetParamBut;     //点击获取参数按钮

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDPARAMCFG_H__958AEEAA_4D9F_4652_9F91_86FF698DC97F__INCLUDED_)
