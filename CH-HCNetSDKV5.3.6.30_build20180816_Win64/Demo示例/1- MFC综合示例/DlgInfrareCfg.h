#include "afxwin.h"
#if !defined(AFX_DLGINFRARECFG_H__6071661E_2F50_40C6_BA57_A86B140436F0__INCLUDED_)
#define AFX_DLGINFRARECFG_H__6071661E_2F50_40C6_BA57_A86B140436F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfrareCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfrareCfg dialog

class CDlgInfrareCfg : public CDialog
{
// Construction
public:
	CDlgInfrareCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfrareCfg)
	enum { IDD = IDD_DLG_INFRARE_CFG };
	CComboBox	m_comMinShutterSet;
	CComboBox	m_comMaxShutterSet;
	CComboBox	m_comboTriggertype;
	CComboBox	m_comboShutterSet;
	CComboBox	m_comboInitializeLens;
	CComboBox	m_comboImageStabilizeLevel;
	CComboBox	m_comboHighSensitivity;
	CComboBox	m_comboCameraIrCorrect;
	CComboBox	m_comboExposureModeSet;
	CComboBox	m_comboControlMode;
	CComboBox	m_comboZoomSpeedLevel;
	CComboBox	m_comboFocusSpeedLevel;
	CComboBox	m_comboAutoFocusMode;
	CComboBox	m_comboFocusMode;
	CComboBox	m_comboLowLightLimtLevel;
	CComboBox	m_comboLowLightLimt;
	int		m_iMinFocusDistance;
	int		m_iIrBrightness;
	int		m_iIrSensitivity;
	int		m_iChromaSuppress;
	float	m_flrisset;
	float	m_fGainSet;
	float	m_fGainLimit;
	float	m_fExposureCompenSate;
	int		m_iOpticalZoom;
	int		m_iDigtitalZoom;
	int		m_iBrightnessLimit;
	BYTE	m_byMaxIrisSet;
	BYTE	m_byMinIrisSet;
	float	m_fOpticalZoomLevel;
	CString	m_csFocusPos;
	CString	m_csPhyRatio;
	//}}AFX_DATA
    LONG m_lChannel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfrareCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfrareCfg)
	afx_msg void OnBtnLowlightSet();
	afx_msg void OnBtnLowlightGet();
	afx_msg void OnBtnFocusmodeSet();
	afx_msg void OnBtnFocusmodeGet();
	afx_msg void OnBtnInfrareSet();
	afx_msg void OnBtnInfrareGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeComboControlMode();
	afx_msg void OnBtnAemodecfgGet();
	afx_msg void OnBtnAemodecfgSet();
	afx_msg void OnSelchangeComboExposuremode();
	afx_msg void OnBtnRestartSupport();
	afx_msg void OnBtnRestoreSupport();
	afx_msg void OnBtnPhyRatioSet();
	afx_msg void OnBtnPhyRatioGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	    int m_iDevIndex;
		NET_DVR_INFRARE_CFG  struInfrareCfg;
		NET_DVR_AEMODECFG struAemodeCfg;
		NET_DVR_PHY_RATIO m_struPhyRatio;
        CComboBox m_ExposureLeve;
        BYTE m_byFocusSensitivity;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFRARECFG_H__6071661E_2F50_40C6_BA57_A86B140436F0__INCLUDED_)
