#if !defined(AFX_DLGVIDEOINTERCOMRELATEDEVCFG_H__A740A645_B1A2_459F_A335_E493834DE37B__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMRELATEDEVCFG_H__A740A645_B1A2_459F_A335_E493834DE37B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomRelateDevCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomRelateDevCfg dialog

class CDlgVideoIntercomRelateDevCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomRelateDevCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomRelateDevCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_RELATEDEV_CFG };
	CComboBox	m_byIndoorConnectMode;
	CComboBox	m_byOutInConnectMode;
	CComboBox	m_cmbOutDoorType;
	CString	m_strManageUnitIP;
	CString	m_strOutdoorUnitIP;
	CString	m_strSIPServerIP;
	CString	m_csAgainIPAddr;
	CString	m_csCentralIP;
	int	m_wCentralPort;
	CString	m_struIndoorUnit;
	//}}AFX_DATA
	enum VIDEO_INTERCOM_DEV_TYPE_ENUM
	{
		ENUM_OUTDOOR_UINT = 1, 
		ENUM_MANAGE_UINT = 2, 
		ENUM_INDOOR_UINT = 3,
        ENUM_FENCE_UINT = 4,
        ENUM_VILLA_OUTDOOR_UNIT = 5,
        ENUM_AGAIN_UNIT = 6,
        ENUM_ID_REG_DEVICE = 7
	};


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomRelateDevCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomRelateDevCfg)
	afx_msg void OnRadioIndoorUnit();
	afx_msg void OnRadioManageUnit();
	afx_msg void OnRadioOutdoorUnit();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnRadioFenceUnit();
	afx_msg void OnRadioAgainUnit();
	afx_msg void OnRadioVillaOutdoorUnit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void CheckRaidoBtn();
protected:
	BOOL GetVideoIntercomRelateDevCfg();
	BOOL SetVideoIntercomRelateDevCfg();
	void ShowParamToWnd(NET_DVR_VIDEO_INTERCOM_RELATEDEV_CFG* pRelateDevCfg);
	void GetParamFromWnd(NET_DVR_VIDEO_INTERCOM_RELATEDEV_CFG* pRelateDevCfg);
private:
	int m_nUnitType;
public:
	LONG m_lServerID;
	LONG m_iDevIndex;
    CString m_csManagedID;
    afx_msg void OnRadioIdRegUnit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMRELATEDEVCFG_H__A740A645_B1A2_459F_A335_E493834DE37B__INCLUDED_)
