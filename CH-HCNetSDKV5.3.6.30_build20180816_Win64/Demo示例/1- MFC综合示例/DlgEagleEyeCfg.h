#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgEagleEyeCfg 对话框

class CDlgEagleEyeCfg : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgEagleEyeCfg)

public:
    CDlgEagleEyeCfg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlgEagleEyeCfg();

    // 对话框数据
    enum { IDD = IDD_DLG_EAGLEEYE_CFG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedBtnCalibGet();
    afx_msg void OnBnClickedBtnCalibSet();
    afx_msg void OnBnClickedBtnSetGotoscene();
    afx_msg void OnBnClickedBtnCalib();
    afx_msg void OnBnClickedBtnCalibDel();
    afx_msg void OnCbnSelchangeComboCalibmode();
    afx_msg void OnBnClickedSetTrackratio();
    afx_msg void OnBnClickedBtnTrackGet();
    afx_msg void OnBnClickedBtnTrackSet();
    void F_DrawFrameEagle(HDC hDc);
    BOOL SetDataToCalibList(NET_DVR_SLAVECAMERA_CALIB_V51* m_struSlaveCameraCalibCfgV51);
    BOOL Play(NET_DVR_CLIENTINFO* struClientInfo, LONG loginID, int index);
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
    LONG m_lPlayHandle;
    BOOL m_bMouseMove;
    DWORD m_wTrackTime;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_SLAVECAMERA_CALIB_V51 m_struSlaveCameraCalibCfgV51;
    NET_DVR_SLAVECAMERA_COND m_struSlaveCameraCond;
    NET_DVR_RESOLUTION_SWITCH m_struResolutionSwitch;
    NET_DVR_PANORAMA_LINKAGE m_struLinkage;
    NET_DVR_GOTOSCENE_COND m_strGotoSceneCond;
    NET_DVR_TRACK_INITPOSTION m_struTrackInitPosition;
    NET_DVR_TRACK_MODE m_struTrackMode;
    NET_DVR_TRACK_INITPOSTION m_struTrackInitPostion;
    NET_DVR_MANUAL_TRACKRATIO m_struManualTrackRatio;
    NET_VCA_POINT m_struTrackPoint;
    NET_VCA_POLYGON m_struRegionTemp;
    NET_DVR_TRACKING m_struTracking;
    NET_DVR_MANUAL_TRACKRATIO m_struTrackingInfo;
    CComboBox m_comboCalibMode;
    CComboBox m_comboSlaveCameraID;
    CComboBox m_comboSceneID;
    CListCtrl m_lstCalib;
    CComboBox m_comboGotoSceneId;
    CRect   m_rcEagleWnd;
    CButton m_btnDel;
    CButton m_btnCalib;
    CComboBox m_combEnabled;
    CComboBox m_SetFollowInitPositionCtrl;
    afx_msg void OnBnClickedSetinitpositionButton();
    CComboBox m_FcIDCoefficientCtrl;
    int m_Coefficient;
    afx_msg void OnBnClickedBtnCoefficientGet();
    afx_msg void OnBnClickedBtnCoefficientSet();
    CComboBox m_resolutiontypectrl;
    afx_msg void OnBnClickedGetResolutiontypeButton();
    afx_msg void OnBnClickedSetResolutiontypeButton();
    afx_msg void OnBnClickedGetLinkageButton();
    afx_msg void OnBnClickedSetLinkageButton();
    CComboBox m_cmbLinkage;
};
