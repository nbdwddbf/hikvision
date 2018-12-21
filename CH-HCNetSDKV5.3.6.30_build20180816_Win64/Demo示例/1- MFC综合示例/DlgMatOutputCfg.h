#if !defined(AFX_DLGMATOUTPUTCFG_H__B008AA8A_1C1E_4DB8_AAC3_FEC2999475DE__INCLUDED_)
#define AFX_DLGMATOUTPUTCFG_H__B008AA8A_1C1E_4DB8_AAC3_FEC2999475DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMatOutputCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMatOutputCfg dialog
#define MAX_OUTPUT_NUM 120
class CDlgMatOutputCfg : public CDialog
{
// Construction
public:
	CDlgMatOutputCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMatOutputCfg)
	enum { IDD = IDD_DLG_MAT_OUTPUT_CFG };
	CComboBox	m_cmbLightInhibit;
	CComboBox	m_comboSubWinNum;
	CListCtrl	m_listOutput;
	CComboBox	m_comboWinMode;
	CComboBox	m_comboVideoFarmat;
	CComboBox	m_comboSubSysNum;
	CComboBox	m_comboSubSysDispNum;
	CComboBox	m_comboSubWinRes;
	CComboBox	m_comboScale;
	CComboBox	m_comboResolution;
	CComboBox	m_comboPsY;
	CComboBox	m_comboPsX;
	CComboBox	m_comboAudioSubWin;
	BOOL	m_bAudio;
	DWORD	m_dwHeight;
	DWORD	m_dwWidth;
	BOOL	m_BVEffcetEnable;
	BYTE	m_byBrightness;
	BYTE	m_byContrast;
	BYTE	m_byGray;
	BYTE	m_byHue;
	BYTE	m_bySharpness;
	BYTE	m_bySaturation;
	BOOL	m_BSmarkIR;
	BOOL	m_BLowLight;
	BOOL	m_BLightInhibit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMatOutputCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMatOutputCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboSubsysNum();
	afx_msg void OnSelchangeComboSubsysDispnum();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnGetOutput();
	afx_msg void OnBtnSetOutput();
	afx_msg void OnBtnSave();
	afx_msg void OnClickListOutput(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboSubwinNum();
	afx_msg void OnBtnResSave();
	afx_msg void OnSelchangeComboWindowMode();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lServerID;
	LONG m_lSubSysID;
	int m_iDeviceIndex;
	DWORD m_dwDispNum;
	int m_iCurSel;
	NET_DVR_ALLSUBSYSTEMINFO_V40 m_struAllSubSysInfo;
	NET_DVR_MATRIX_VOUTCFG m_struOutputCfg[MAX_OUTPUT_NUM];
	NET_DVR_MATRIX_VOUTCFG m_struOutputCfgSet[MAX_OUTPUT_NUM];
	LONG m_lOutputNum[MAX_OUTPUT_NUM];
	BOOL m_bParamSaved[MAX_OUTPUT_NUM];
	NET_DVR_MATRIX_ABILITY_V41 m_struDecoderAbility;
	void GetResolutionString(DWORD dwRes, char *lpResString);
	void GetResolutionDword(DWORD *dwRes, CString lpResString);
	void AddDataToList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATOUTPUTCFG_H__B008AA8A_1C1E_4DB8_AAC3_FEC2999475DE__INCLUDED_)
