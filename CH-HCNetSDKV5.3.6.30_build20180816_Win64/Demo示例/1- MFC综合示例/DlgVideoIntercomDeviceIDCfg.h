#if !defined(AFX_DLGVIDEOINTERCOMDEVICEIDCFG_H__5733F10E_D440_4CD7_BE59_EF4A43F0FE47__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMDEVICEIDCFG_H__5733F10E_D440_4CD7_BE59_EF4A43F0FE47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomDeviceIDCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomDeviceIDCfg dialog

class CDlgVideoIntercomDeviceIDCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomDeviceIDCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomDeviceIDCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_DEVICEID_CFG };
	int		m_nIndoorFloorNumber;
	int		m_nIndoorRoomNumber;
	int		m_nManageDevIndex;
	int		m_nManagePeriod;
	int		m_nOutdoorBuildingNumber;
	int		m_nOutdoorDevIndex;
	int		m_nOutdoorFloorNumber;
	int		m_nOutdoorPeriod;
	int		m_nOutdoorUnitNumber;
	int		m_nDevIndex;
	BOOL	m_bChkAutoReg;
	int		m_nFenceDevIndex;
	int		m_nFencePeriod;
	int		m_nVillaOutDoorDevIndex;
	int		m_nVillaOutDoorBuildingNum;
	int		m_nVillaOutDoorFloorNumber;
	int		m_nVillaOutDoorPeriod;
	int		m_nVillaOutDoorUnitNum;
	//}}AFX_DATA
	enum VIDEO_INTERCOM_DEV_TYPE_ENUM
	{
		ENUM_OUTDOOR_UINT = 1, 
		ENUM_MANAGE_UINT = 2, 
		ENUM_INDOOR_UINT = 3,
		ENUM_FENCE_UINT = 4,
        ENUM_VILLA_OUTDOOR_UNIT = 5,
        ENUM_AGAIN_UINT = 6,
        ENUM_ID_REG_DEVICE = 7
	};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomDeviceIDCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomDeviceIDCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSave();
	afx_msg void OnRadioIndoorUnit();
	afx_msg void OnRadioManageUnit();
	afx_msg void OnRadioOutdoorUnit();
	afx_msg void OnRadioFence();
	afx_msg void OnRadioVillaOutdoorUnit();
	afx_msg void OnRadioAgainUnit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void CheckRaidoBtn();
private:
	BOOL GetVideoIntercomDeviceIDCfg();
	BOOL SetVideoIntercomDeviceIDCfg();
	void ShowParamToWnd(NET_DVR_VIDEO_INTERCOM_DEVICEID_CFG* pDeviceIDCfg);
	void GetParamFromWnd(NET_DVR_VIDEO_INTERCOM_DEVICEID_CFG* pDeviceIDCfg);
private:
	int m_nUnitType;
public:
	LONG m_lServerID;
	LONG m_iDevIndex;
    int m_nAgainOutDoorPeriod;
    int m_nAgainOutDoorBuildingNum;
    int m_nAgainOutDoorUnitNum;
    int m_nAgainOutDoorFloorNumber;
    int m_nAgainOutDoorDevIndex;
    afx_msg void OnRadioIDRegUnit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMDEVICEIDCFG_H__5733F10E_D440_4CD7_BE59_EF4A43F0FE47__INCLUDED_)
