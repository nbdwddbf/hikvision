#pragma once

#include "afxwin.h"
#include "VcaCommonOperations.h"
#include "afxcmn.h"
// CDlgEagleCfg 对话框

class CDlgEagleCfg : public CDialogEx, public CVcaCommonOperations
{
	DECLARE_DYNAMIC(CDlgEagleCfg)

public:
	CDlgEagleCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgEagleCfg();

// 对话框数据
	enum { IDD = IDD_DLG_EAGLECFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonEaget();
    afx_msg void OnBnClickedButtonEaset();
    CComboBox m_eagleability;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_EAGLEFOCUSING_CTRL m_struBuiltin_EAGLEFOCUSING_CTRL;
    NET_DVR_EAGLEFOCUSING_CALCFG m_struBuiltin_EAGLEFOCUSING_CALCFG;
    CComboBox m_eagle_cal_ablity;
    CComboBox m_eagle_rule;
    afx_msg void OnBnClickedButtonAdd();

    int idtemp = 0;
    CRect   m_rcPlayWnd;
    void DrawRgn(HDC hdc);
    NET_VCA_LINE m_struLine;
    afx_msg void OnBnClickedButtonCalGet();
    afx_msg void OnBnClickedButtonCalSet();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    CComboBox m_cmbScene;
    BOOL    m_bDrawEnd;
    int     m_nDrawPointNum;
    NET_VCA_POLYGON m_strVacRegion;
    short m_wRate;
    BYTE m_bySpotNum;
    afx_msg void OnCbnSelchangeCmbScene();
    afx_msg void OnBnClickedBtnDel();
    afx_msg void OnBnClickedBtnGotoScen();
};
