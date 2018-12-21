#if !defined(AFX_DLGTRIALDVR_H__AB17D1A1_77F0_4012_860E_973C26384DF5__INCLUDED_)
#define AFX_DLGTRIALDVR_H__AB17D1A1_77F0_4012_860E_973C26384DF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrialDVR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialDVR dialog

class CDlgTrialDVR : public CDialog
{
// Construction
public:
	CDlgTrialDVR(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTrialDVR)
	enum { IDD = IDD_DLG_TRIAL_DVR };
	short	m_wHDMINum;
	short	m_wIPNum;
	short	m_wPIPNum;
	short	m_wSDINum;
	short	m_wHDMIStartNo;
	short	m_wIPStartNo;
	short	m_wPIPStartNo;
	short	m_wSDIStartNo;
	short	m_wVGAStartNo;
	short	m_wVGANum;
	short	m_wPOEStartNo;
	short	m_wYPBPRStartNo;
	short	m_wPOENum;
	short	m_wYPBPRNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrialDVR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrialDVR)
	virtual void OnCancel();
	afx_msg void OnBtnAudioActivation();
	afx_msg void OnBtnInfrared();
	afx_msg void OnBtnGetSystemInfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPipCfg();
	afx_msg void OnBtnRemotePlay();
	afx_msg void OnBtnCaseInfo();
	afx_msg void OnBtnMicrophoneStatus();
	afx_msg void OnBtnTrialHostStatus();
	afx_msg void OnBtnLocalInput();
	afx_msg void OnBtnLampInfo();
	afx_msg void OnBtnLampControl();
    afx_msg void OnButtonConfigCameraType();
    afx_msg void OnButtonMixAudioInParamCfg();
    afx_msg void OnButtonMixAudioOutParamCfg();
    afx_msg void OnButtonVideoOutResolutionCfg();
    afx_msg void OnButtonMultilStreamRelChanCfg();
    afx_msg void OnButtonRemotePowerOn();
    afx_msg void OnButtonWifiDHCPCfg();
    afx_msg void OnButtonGetWifiClientListInfo();
    afx_msg void OnButtonAudioInVolumeCfg();
    afx_msg void OnButtonAudioOutVolumeCfg();
    afx_msg void OnButtonMaskAreaParamCfg();
    afx_msg void OnButtonAudioDiacriticalCfg();
    afx_msg void OnBtnInChannelVideLossCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int m_lUserID;
    int m_iDevIndex;
    int m_lChannel;

    NET_DVR_TRIAL_SYSTEM_INFO m_struTrialSysInfo;
    NET_DVR_PICCFG_V30  m_struPicCfgV30;
private:
    void ConvertVilostV40T0V30(NET_DVR_VILOST_V40 *pViLostV40, NET_DVR_VILOST_V30 *pViLostV30,BOOL bV40ToV30);

public:
    afx_msg void OnBnClickedBtnAudioMix();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRIALDVR_H__AB17D1A1_77F0_4012_860E_973C26384DF5__INCLUDED_)
