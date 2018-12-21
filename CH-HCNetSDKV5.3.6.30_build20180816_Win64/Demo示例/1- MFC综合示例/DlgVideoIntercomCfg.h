#if !defined(AFX_DLGVIDEOINTERCOMCFG_H__6BAC1EFE_F7A6_4280_9F63_0363E2F5B7BB__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMCFG_H__6BAC1EFE_F7A6_4280_9F63_0363E2F5B7BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCfg dialog

class CDlgVideoIntercomCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomCfg)
	afx_msg void OnBtnDeviceidCfg();
	afx_msg void OnBtnPrivilegePwdCfg();
	afx_msg void OnBtnRelatedevice();
	afx_msg void OnBtnNoticeData();
	afx_msg void OnBtnOperationTimeCfg();
	afx_msg void OnBtnStreamSrcInfo();
	afx_msg void OnBtnGateway();
	afx_msg void OnBtnGatewayCard();
	afx_msg void OnBtnIoinCfg();
	afx_msg void OnBtnIooutCfg();
	afx_msg void OnBtnElevatorControlCfg();
	afx_msg void OnBtnStreamCfg();
	afx_msg void OnButAcDoorconfig();
	afx_msg void OnBtnRs485();
	afx_msg void OnBtnGetDevinfo();
	afx_msg void OnBtnGetRegister();
	afx_msg void OnBtnWdr();
	afx_msg void OnBtnAuth();
	afx_msg void OnBtnAudioinVolume();
	afx_msg void OnBtnAudiooutVolume();
	afx_msg void OnBtnRoomCallCfg();
	afx_msg void OnBtnVideoCall();
	afx_msg void OnButtonAlarmCfg();
	afx_msg void OnButtonBellfileCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lServerID;
	LONG m_iDevIndex;
	void CurCfgUpadate();
	afx_msg void OnBnClickedBellfileCfg();
//	afx_msg void OnBnClickedButtonBonjourGet();
    afx_msg void OnBnClickedBtnRoomCustomCfg();
    afx_msg void OnBnClickedBtnNoticeVideoData();
    afx_msg void OnBnClickedBtnXmlCfg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMCFG_H__6BAC1EFE_F7A6_4280_9F63_0363E2F5B7BB__INCLUDED_)
