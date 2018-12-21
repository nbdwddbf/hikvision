#pragma once
#include "afxwin.h"


// CDlgPtzNotification 对话框

class CDlgPtzNotification : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPtzNotification)

public:
	CDlgPtzNotification(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPtzNotification();

// 对话框数据
	enum { IDD = IDD_DLG_PTZ_NOTIFICTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnSet();
    afx_msg void OnBnClickedBtnGet();
    afx_msg void OnBnClickedBtnSave();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedPotrol();
    afx_msg void OnBnClickedPattern();
    afx_msg void OnCbnSelchangeCmbChan();
    virtual BOOL OnInitDialog();
    CComboBox m_cmbChan;
    DWORD m_dwPresetChan;
    DWORD m_dwCruiseChan;
    DWORD m_dwTrackChan;
    DWORD m_dwCruisePointNo;
    DWORD m_dwPresetPointNo;
    DWORD m_dwTrackPointNo;
    DWORD m_dwPresetNum;
    DWORD m_dwCruiseNum;
    DWORD m_dwTrackNum;
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;
    CComboBox m_cmbType;
    //NET_DVR_PTZ_NOTIFICATION m_struPtzNotification;
    NET_DVR_PTZ_NOTIFICATION_COND m_struPtzNotificationCond;
    NET_DVR_PTZ_NOTIFICATION_CFG m_struPtzNotificationCfg;
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
    BOOL m_bPattern;
    BOOL m_bPatrol;
    BOOL m_bPreset;

    afx_msg void OnBnClickedPreset();
};
