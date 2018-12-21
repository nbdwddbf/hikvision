#pragma once
#include "afxwin.h"


// CDlgCapturePictureV50 对话框

class CDlgCapturePictureV50 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCapturePictureV50)

public:
	CDlgCapturePictureV50(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCapturePictureV50();

// 对话框数据
	enum { IDD = IDD_DLG_CAPTURE_PICTURE_V50 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
    virtual void OnCancel();
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnExit();
    afx_msg void OnBnClickedBtnCapturePictureV50Exit();
    afx_msg void OnBnClickedBtnCapturePictureV50();
    PCHANNEL_INFO m_pChanInfo;
    BOOL GetCompressCfgAbility(DWORD dwIPChanIndex);
    void GetResolutionAbility();
    NET_DVR_COMPRESSIONCFG_ABILITY *m_pCompresscfgAbility;
    int m_iDeviceIndex;
    CComboBox m_cmbPictureReslution;
    CComboBox m_cmbPictureQuality;
    CComboBox m_cmbPicutureFormat;
    CComboBox m_cmbCaptureType;
    DWORD m_dwPicLen;

};
