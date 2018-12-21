#if !defined(AFX_DLGISPPARAMCFG_H__739C8147_D630_4EDB_A10F_F760EC8FD980__INCLUDED_)
#define AFX_DLGISPPARAMCFG_H__739C8147_D630_4EDB_A10F_F760EC8FD980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgISPParamCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgISPParamCfg dialog

class CDlgISPParamCfg : public CDialog
{
// Construction
public:
	CDlgISPParamCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgISPParamCfg)
	enum { IDD = IDD_DLG_ISP_PARAMCFG };
	CComboBox	m_comboWhiteBalanceModeN;
	CComboBox	m_comboWDRWorkTypeN;
	CComboBox	m_comboNoiseMoveModeN;
	CComboBox	m_comboLightInhibitLevelN;
	CComboBox	m_comboGrayLevelN;
	CComboBox	m_comboDehazeModeN;
	CComboBox	m_comboBackLightModeN;
	CComboBox	m_comElecteSwitchN;
	CComboBox	m_comboWDRWorkType;
	CComboBox	m_comboNoiseMoveMode;
	CComboBox	m_comboLightInhibitLevel;
	CComboBox	m_comboGrayLevel;
	CComboBox	m_comboDehazeMode;
	CComboBox	m_comboBackLightMode;
	CComboBox	m_comElecteSwitch;
	CComboBox	m_comboWhiteBalanceMode;
	CComboBox	m_comboWorkType;
	COleDateTime	m_TimeStart;
	COleDateTime	m_TimeStop;
	BOOL	m_bChkLightInhibitEn;
	BYTE	m_byBGain;
	int		m_iBrightness;
	int		m_iContrast;
	BYTE	m_byDehazeLevel;
	BYTE	m_byRGain;
	int		m_iGain;
	BYTE	m_byNormalLevel;
	int		m_iSharpness;
	BYTE	m_byElectLevel;
	int		m_iBackLightModeLevel;
	BYTE	m_bySpectralLevel;
	BYTE	m_byTemporalLevel;
	int		m_iVedioExposure;
	int		m_iWDRContrastLevel;
	int		m_iWDRLevel1;
	int		m_iWDRLevel2;
	BOOL	m_bChkLightInhibitEnN;
	BYTE	m_byBGainN;
	int		m_iBackLightModeLevelN;
	int		m_iBrightnessN;
	int		m_iContrastN;
	BYTE	m_byDehazeLevelN;
	BYTE	m_byElectLevelN;
	int		m_iGainN;
	BYTE	m_byNormalLevelN;
	BYTE	m_byRGainN;
	int		m_iSharpnessN;
	BYTE	m_bySpectralLevelN;
	BYTE	m_byTemporalLevelN;
	int		m_iVedioExposureN;
	int		m_iWDRContrastLevelN;
	int		m_iWDRLevel1N;
	int		m_iWDRLevel2N;
	int		m_iDBackLightX1;
	int		m_iNBackLightX1;
	int		m_iDBackLightX2;
	int		m_iNBackLightX2;
	int		m_iNBackLightY1;
	int		m_iDBackLightY2;
	int		m_iNBackLightY2;
	int		m_iDBackLightY1;
	int		m_iExposureUserSetD;
	int		m_iExposureUserSetN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgISPParamCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgISPParamCfg)
	afx_msg void OnBtnSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lServerID;
	int m_iDeviceIndex;
	NET_DVR_ISP_CAMERAPARAMCFG m_struISPCameraParamCfg;
	void OnGetParamFormWnd();
	void OnSetParamToWnd();
	void InitWnd();
	LPNET_DVR_ISP_CAMERAPARAMCFG m_pstruISPCameraParamcfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGISPPARAMCFG_H__739C8147_D630_4EDB_A10F_F760EC8FD980__INCLUDED_)
