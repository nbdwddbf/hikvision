#if !defined(AFX_DLGPRODUCTACS_H__1D4557FA_057E_4031_B854_C06D9A21342C__INCLUDED_)
#define AFX_DLGPRODUCTACS_H__1D4557FA_057E_4031_B854_C06D9A21342C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProductAcs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProductAcs dialog

class CDlgProductAcs : public CDialog
{
// Construction
public:
	CDlgProductAcs(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProductAcs)
	enum { IDD = IDD_SUBDLG_PRODUCT_ACS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProductAcs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProductAcs)
	afx_msg void OnBtnAcsWorkStatus();
	afx_msg void OnButPlanConfig();
	afx_msg void OnButDoorConfig();
	afx_msg void OnBtnAcsGroupCfg();
	afx_msg void OnBtnAcsMultiCard();
	afx_msg void OnBtnAcsClear();
	afx_msg void OnBtnSneakAndLock();
	afx_msg void OnButAlarminAndout();
	afx_msg void OnButAcAlarmUser();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCardCfg();
	afx_msg void OnBtnCaseSensor();
	afx_msg void OnButAcRemotecontrol();
	afx_msg void OnButAcRs485();
	afx_msg void OnButAcCardreadercfg();
    afx_msg void OnButCmsCfg();
    afx_msg void OnButAlarmHostNetCfg();
    afx_msg void OnButAlarmHostWirelessNetworkCfg();
    afx_msg void OnButAlarmHostReportCenterV40();
    afx_msg void OnButSmsRelativePara();
    afx_msg void OnButPhoneDoorRightCfg();
    afx_msg void OnButFingerPrintCfg();
    afx_msg void OnButPasswdOpenDoor();
    afx_msg void OnButEventCardLinkageCfg();
    afx_msg void OnButAntiSneakHostCfg();
    afx_msg void OnButReaderAntiSneakHostCfg();
    afx_msg void OnButAcsCfg();
	afx_msg void OnBtnCardUserInfo();
    afx_msg void OnButFaceDetect();
    afx_msg void OnButSnapCfg();
    afx_msg void OnButAcsExternalDevCfg();
    afx_msg void OnButAcsPersonnelChannelCfg();
	afx_msg void OnBtnGateTimeCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
	LONG m_lChannel;
    void CurCfgUpadate();
	afx_msg void OnBnClickedButtonWiegandCfg();
	afx_msg void OnBnClickedButtonMoudleStatus();
    afx_msg void OnBnClickedBtnCaptureFingerPrint();
    afx_msg void OnBnClickedBtnAcsXmlDiffusion();
    afx_msg void OnBnClickedBtnAcsAttendance();
    afx_msg void OnBnClickedButtonLocalControllerStatus();
    afx_msg void OnBnClickedButtonOnlineLocalController();
    afx_msg void OnBnClickedBtnAlarmhostAbility();
    afx_msg void OnBnClickedBtnZoomCode();
    afx_msg void OnBnClickedBtnTriggerCode();
    afx_msg void OnBnClickedBtnLocalControllerCfg();
    afx_msg void OnBnClickedBtnUsbDeviceManage();
    afx_msg void OnBnClickedBtnExternModule();
    afx_msg void OnBnClickedBtnAcsFaceParamCfg();
    afx_msg void OnBnClickedBtnCaptureFace();
    afx_msg void OnBnClickedBtnUploadCertificateBlackList();
    afx_msg void OnBnClickedBtnGetRegisterInfo();
    afx_msg void OnBnClickedBtnGetAcsEvent();
    afx_msg void OnBnClickedBtnSetExamInfo();
    afx_msg void OnBnClickedBtnSetExamineeInfo();
    afx_msg void OnBnClickedBtnSearchExamCompareResult();
    afx_msg void OnBnClickedBtnUploadBlackListPicture();
    afx_msg void OnBnClickedBtnUploadBlackList();
    afx_msg void OnBnClickedBtnCheckFacePicture();
    afx_msg void OnBnClickedBtnFaceTemplate();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRODUCTACS_H__1D4557FA_057E_4031_B854_C06D9A21342C__INCLUDED_)
