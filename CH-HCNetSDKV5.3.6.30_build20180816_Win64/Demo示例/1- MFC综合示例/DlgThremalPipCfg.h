#pragma once
#include "VcaCommonOperations.h"
#include "afxwin.h"


// CDlgThremalPipCfg 对话框

class CDlgThremalPipCfg : public CDialogEx, public CVcaCommonOperations
{
	DECLARE_DYNAMIC(CDlgThremalPipCfg)

public:
	CDlgThremalPipCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgThremalPipCfg();

// 对话框数据
	enum { IDD = IDD_DLG_THERMAL_PIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonGet();
    afx_msg void OnBnClickedButtonSet();
    afx_msg void OnBnClickedButtonGetOsd();
    afx_msg void OnBnClickedButtonSetOsd();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    BOOL m_bPipRegion;
    CComboBox m_comboOverlapType;
    CComboBox m_comboPipMode;
    CComboBox m_comboRuleslineColor;
    int m_iColorB;
    int m_iColorG;
    int m_iColorR;
    int m_iTransparency;

    CRect   m_rcPlayWnd;
    void DrawRgnFun(HDC hdc);
    NET_VCA_POLYGON m_struPolyGon;
    NET_VCA_LINE m_struLine;
    BOOL    m_bDrawEnd;
    int     m_nDrawPointNum;
    NET_DVR_THERMAL_PIP m_struThermalPip;
    NET_DVR_THERMAL_INTELRULE_DISPLAY m_struThermalIntelruleDisplay;
    afx_msg void OnCbnSelchangeComboRuleslineColor();
    afx_msg void OnBnClickedButtonConfirmOsd();
    afx_msg void OnBnClickedButtonRemoveDrawLine();
    BOOL m_bPipEnable;
    CComboBox m_comboFontSize;
};
