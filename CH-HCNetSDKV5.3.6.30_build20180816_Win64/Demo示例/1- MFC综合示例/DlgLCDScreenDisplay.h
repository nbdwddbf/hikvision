#if !defined(AFX_DLGLCDSCREENDISPLAY_H__0D96701C_F506_4BA4_B717_17682B102FBE__INCLUDED_)
#define AFX_DLGLCDSCREENDISPLAY_H__0D96701C_F506_4BA4_B717_17682B102FBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLCDScreenDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLCDScreenDisplay dialog

class CDlgLCDScreenDisplay : public CDialog
{
// Construction
public:
	CDlgLCDScreenDisplay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLCDScreenDisplay)
	enum { IDD = IDD_DLG_SCREEN_DISPLAY };
	CComboBox	m_cmbTempState;
	CComboBox	m_cmbFanExceptionStatus;
	CComboBox	m_cmbImageMod;
	CComboBox	m_comEdgeEnable;
	CComboBox	m_comDisplayMode;
	CComboBox	m_comCfgType;
	BYTE	m_byBackLight;
	BYTE	m_byBrightnessLevel;
	BYTE	m_byContrastLevel;
	BYTE	m_bySharpnessLevel;
	BYTE	m_bySaturationLevel;
	BYTE	m_byHueLevel;
	BYTE	m_byRed;
	BYTE	m_byGreen;
	BYTE	m_byBlue;
	BYTE	m_byBlueOffset;
	BYTE	m_byGreenOffset;
	BYTE	m_byRedOffset;
	BYTE	m_byGainB;
	BYTE	m_byGainG;
	BYTE	m_byGainR;
	BYTE	m_byOffsetR;
	BYTE	m_byOffsetG;
	BYTE	m_byOffsetB;
	BYTE	m_byLeftEdge;
	BYTE	m_byLowerEdge;
	BYTE	m_byRightEdge;
	BYTE	m_byTopEdge;
	BOOL	m_bMute;
	BOOL	m_bLogoShow;
	BOOL	m_bFnastatus;
	int		m_iBalance;
	int		m_iLCDVolume;
	int		m_iTemperature;
	int		m_iHours;
	CString	m_szVersion;
	int		m_iDisplayMod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLCDScreenDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLCDScreenDisplay)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboCfgType();
	afx_msg void OnBtnSaveCfg();
	afx_msg void OnBtnSetCfg();
	afx_msg void OnBtnGetCfg();
	afx_msg void OnSelchangeComboDisplayMode();
	afx_msg void OnSelchangeComboEnableEdge();
	afx_msg void OnBtnGetAudio();
	afx_msg void OnBtnGetLogo();
	afx_msg void OnBtnSetAudio();
	afx_msg void OnBtnSetLogo();
	afx_msg void OnBtnScreenstatus();
	afx_msg void OnRadioDisplayMod();
	afx_msg void OnRadioImageMod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void initDisplay();

	LONG m_lUserID;
	int m_iDevIndex;

	NET_DVR_SCREEN_DISPLAY_CFG m_struDisplay;
    NET_DVR_LCD_AUDIO_CFG m_struLCDAudio;
    NET_DVR_BOOT_LOGO_CFG m_struBootLogo;
    NET_DVR_SCREEN_WORK_STATE m_struScreenWorkState;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDSCREENDISPLAY_H__0D96701C_F506_4BA4_B717_17682B102FBE__INCLUDED_)
