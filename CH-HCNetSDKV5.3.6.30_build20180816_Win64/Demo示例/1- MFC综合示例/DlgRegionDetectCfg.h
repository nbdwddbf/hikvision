#pragma once

#include "VcaCommonOperations.h"
#include "afxwin.h"
#include "atltime.h"
#include "afxcmn.h"
// CDlgRegionDetectCfg 对话框

class CDlgRegionDetectCfg : public CDialogEx, public CVcaCommonOperations
{
	DECLARE_DYNAMIC(CDlgRegionDetectCfg)

public:
	CDlgRegionDetectCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRegionDetectCfg();

// 对话框数据
	enum { IDD = IDD_DLG_REGION_CFG };
    CString  m_csMaskName;
    BOOL m_bEnalbeFireShieldMask;
    BOOL m_bEnableOneRegion;
    CComboBox m_comMaskID;
    CComboBox m_comShieldZoom;
    CComboBox m_comRegionType;
    CComboBox m_comMaskType;
    CString  m_csMaskName2;
    BOOL m_bEnalbeSmokeShieldMask;
    BOOL m_bEnableOneRegion2;
    CComboBox m_comMaskID2;
    CComboBox m_comShieldZoom2;
    CComboBox m_comRegionType2;
    CComboBox m_comMaskType2;
    CComboBox m_comSmokerFireEnabled;
    BOOL m_bEnbaleAreScan;
    CComboBox m_comAreScanState;
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
    CRect   m_rcPlayWnd;   
    BOOL    m_bDrawEnd;
    int     m_nDrawPointNum;
    int    m_nDrawSmokePointNum;
    BOOL   m_bFireShowEnabled;
    BOOL   m_bSmokeShowEnabled;

    void    DrawRgnFun(HDC hdc);

    NET_VCA_POLYGON m_struPolyGon;
    NET_SDK_FIRESHIELDMASK_CFG  m_struFireShieldMask;
    NET_SDK_SMOKESHIELDMASK_CFG m_struSmokeShieldMask;

    NET_SDK_FIRESHIELDMASK_COND m_FireShieldMaskCond;
    NET_SDK_SMOKESHIELDMASK_COND m_SmokeShieldMaskCond;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    

	DECLARE_MESSAGE_MAP()
public:
    int m_iSubItem;
    int m_iLastItem;
    afx_msg void OnBnClickedBtnSetFireShieldMaskCfg();
    afx_msg void OnBnClickedBtnSaveFireShieldMaskCfg();
    afx_msg void OnBnClickedBtnGetFireShieldMaskCfg();
    afx_msg void OnBnClickedBtnSaveSmokeShieldMaskCfg();
    afx_msg void OnBnClickedBtnSetSmokeShieldMaskCfg();
    afx_msg void OnBnClickedBtnGetSmokeShieldMaskCfg();
    afx_msg void OnBnClickedBtnSetAreascan();
    afx_msg void OnBnClickedBtnGetAreascan();
    afx_msg void OnBnClickedBtnDelAreascan();
    afx_msg void OnBnClickedBtnAresacnIn();
    afx_msg void OnBnClickedBtnAresacnConfirm();
    afx_msg void OnBnClickedBtnAresacnStop();
    afx_msg void OnBnClickedBtnSaveScanzoom();
    afx_msg void OnBnClickedBtnGetScanzoom();   
    afx_msg void OnBnClickedBtnFireRegionDel();
    afx_msg void OnBnClickedBtnSmokeRegionDel();
    CComboBox m_cShieldAreaTransparency;
    CComboBox m_csmocktran;
    BOOL m_firedisplayShieldAreaEnabled;
    BOOL m_smokedisplayShieldAreaEnabled;
};
