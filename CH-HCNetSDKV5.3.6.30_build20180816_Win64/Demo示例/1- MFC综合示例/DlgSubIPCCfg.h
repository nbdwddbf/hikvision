#if !defined(AFX_DLGSUBIPCCFG_H__5FCC9E34_44A9_4D91_ABB9_B24C13DF2804__INCLUDED_)
#define AFX_DLGSUBIPCCFG_H__5FCC9E34_44A9_4D91_ABB9_B24C13DF2804__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSubIPCCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSubIPCCfg dialog

class CDlgSubIPCCfg : public CDialog
{
// Construction
public:
	CDlgSubIPCCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSubIPCCfg)
	enum { IDD = IDD_SUB_DLG_IPC_CFG };
	CComboBox	m_comboAlarmIn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSubIPCCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSubIPCCfg)
	afx_msg void OnBtnCcdconfig();
	afx_msg void OnBtnDetectFace();
	afx_msg void OnBtnIpcSpecial();
	afx_msg void OnBtnIpcSpecialex();
	afx_msg void OnBtnUpgradeIpc();
	afx_msg void OnBtnImExportIpcCfgFile();
	afx_msg void OnBtnRoi();
	afx_msg void OnBtnPtzScope();
	afx_msg void OnBtnIpcintell();
	afx_msg void OnBtnDevserver();
	afx_msg void OnBtnGbt28181Protocol();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCameraSetupcfg();
	afx_msg void OnBtnFisheye();
	afx_msg void OnBtnStreamAttachinfoCfg();
	afx_msg void OnBtnPtzcfgctrl();
	afx_msg void OnBtnIpcPlateRecog();
	afx_msg void OnBtnWireless();
	afx_msg void OnBtnRemotecontrolStatus();
	afx_msg void OnBtn3gConfig();
	afx_msg void OnBtnCloudstorageTestCfg();
	afx_msg void OnBtnMonitorLocation();
	afx_msg void OnBtnLitestorage11();
	afx_msg void OnBtnMastreslaveTracking();
	afx_msg void OnBtnVehRecog();
	afx_msg void OnBtnFireDetection();
	afx_msg void OnBtnGisInfo();
	afx_msg void OnBtnStreamFrame();
	afx_msg void OnBtnPersonnelStatistics();
	afx_msg void OnBtnWirelessServer();
	afx_msg void OnBtnTimeCorrect();
	afx_msg void OnBtnConnectList();
    afx_msg void OnBtnExternalDev();
	afx_msg void OnButtonThermalDoubleSpectrum();
	afx_msg void OnBtnThscreen();
    afx_msg void OnBtnBatteryPower();
	afx_msg void OnBtnPanoramaimage();
    afx_msg void OnBtnOnlineUserList();
	afx_msg void OnButtonSmartStoragedetection();
	afx_msg void OnBtnPrivateProtocl();
	afx_msg void OnBtnFtpupload();
	afx_msg void OnBtnThreeDimSpeedPtz();
    afx_msg void OnBnClickedBtnAnrArmingHost();
    afx_msg void OnBnClickedButtonOispara();
    afx_msg void OnBnClickedButtonMac();
    afx_msg void OnBnClickedButtonEaglecfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void CurCfgUpdate();
	BOOL CheckInitParam();
	LONG m_lUserID;
	LONG m_lChannel;
	LONG m_lDeviceIndex;
	LONG m_lChanCount;
	LONG m_lAnaChanCount;
	LONG m_lDStartChannel;
	LONG m_lAlarmOutNum;
	LONG m_lStartChan;
	LONG m_lAlarmInNum;
    afx_msg void OnBnClickedBtnSmartCalibration();
    afx_msg void OnBnClickedBtnTest();
    afx_msg void OnBnClickedBtnEagleeyeCfg();
    afx_msg void OnBnClickedBtnCalib();
    afx_msg void OnBnClickedBtnUplpanoramic();
    afx_msg void OnBnClickedBtnGetVechicleInfo();
    afx_msg void OnBnClickedBtnFirmwareVersion();
    afx_msg void OnBnClickedFireptzexcfg();
    afx_msg void OnBnClickedBtnSoftwareService();
    afx_msg void OnBnClickedBtnFaceData();
    afx_msg void OnBnClickedBtnUploadHd();
    afx_msg void OnBnClickedBtnPosinfo();
    afx_msg void OnBnClickedBtnGetVcaVersionList();
    afx_msg void OnBnClickedBtnSecuCfg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUBIPCCFG_H__5FCC9E34_44A9_4D91_ABB9_B24C13DF2804__INCLUDED_)
