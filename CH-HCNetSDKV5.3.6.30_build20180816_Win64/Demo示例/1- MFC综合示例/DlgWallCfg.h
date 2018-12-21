#if !defined(AFX_DLGWALLCFG_H__E39FB209_F61B_43EB_A4EE_547DCB33027B__INCLUDED_)
#define AFX_DLGWALLCFG_H__E39FB209_F61B_43EB_A4EE_547DCB33027B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWallCfg dialog
#define MAX_COUNT    256

#define HEIGHT 128
#define WIDTH  128

class CDlgWallCfg : public CDialog
{
// Construction
public:
	CDlgWallCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallCfg)
	enum { IDD = IDD_DLG_WALL_CFG };
	CComboBox	m_comboResolution;
	CComboBox	m_comboOutput;
	CComboBox	m_comboLevel;
	CListCtrl	m_listScreen;
	CComboBox	m_comboY;
	CComboBox	m_comboX;
	BOOL	m_bEnable;
	BOOL	m_bDzd;
	BOOL	m_bFgb;
	BOOL	m_bQgyz;
	BYTE	m_byBrightness;
	BYTE	m_byContrast;
	BYTE	m_byGray;
	BYTE	m_byHue;
	BYTE	m_bySaturation;
	BYTE	m_bySharpness;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();		
	afx_msg void OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnSaveCfg();
	afx_msg void OnBtnSetCfg();
	afx_msg void OnBtnGetCfg();
	afx_msg void OnSelchangeComboOutput();
	afx_msg void OnBtnUpdateOutput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserID;
	LONG m_iDeviceIndex;
	DWORD m_dwCount;
	DWORD m_dwDispNum;
	int m_iCurSel;
	LONG  m_lDispChan[MAX_COUNT];
	LONG m_lDispChanSet[MAX_COUNT];
    DWORD m_dwStatus[MAX_COUNT];
	NET_DVR_SINGLEWALLPARAM m_struWallParam[MAX_COUNT];
	NET_DVR_SINGLEWALLPARAM m_struWallParamSet[MAX_COUNT];
	NET_DVR_MATRIX_ABILITY_V41 m_struAblity;

    NET_DVR_WALLOUTPUTPARAM m_struOutput[MAX_COUNT];
	NET_DVR_WALLOUTPUTPARAM m_struOutputSet[MAX_COUNT];
	LONG m_lDispOutputSet[MAX_COUNT];
	DWORD m_dwOutputSet;
	void DrawList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLCFG_H__E39FB209_F61B_43EB_A4EE_547DCB33027B__INCLUDED_)
