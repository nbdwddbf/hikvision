#pragma once

#include "afxwin.h"
#include "VcaCommonOperations.h"

// CDlgSmartCalib 对话框

class CDlgSmartCalib : public CDialogEx, public CVcaCommonOperations
{
	DECLARE_DYNAMIC(CDlgSmartCalib)

public:
	CDlgSmartCalib(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSmartCalib();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

// 对话框数据
	enum { IDD = IDD_DLG_IPC_SMART_CALIBRATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bMinTarget;
    BOOL m_bMaxTarget;
    CComboBox m_cmbRuleID;
    CComboBox m_bSmartType;
    CRect   m_rcPlayWnd;
    NET_VCA_POINT m_struMAxPoint;
    NET_VCA_POLYGON m_strMaxVacRegion;
    NET_VCA_POLYGON m_strMinVacRegion;
    NET_DVR_SMARTCALIBRATION_REGION_CFG m_struSmartCalib;
    NET_DVR_SMARTCALIBRATION_COND m_struSmartCalibCond;
    void DrawSmartRgn(HDC hdc);
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnSet();
    afx_msg void OnBnClickedBtnGet();
    BOOL m_bMouseMove;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    afx_msg void OnCbnSelchangeCmbRuleId();
    afx_msg void OnBnClickedBtnSave();
    afx_msg void OnBnClickedChkMaxTarget();
    afx_msg void OnBnClickedChkMinTarget();
    afx_msg void OnBnClickedCancel();
    CComboBox m_cmbMode;
    CComboBox m_cmbStrategy;
    CComboBox m_cmbPriority;
};
