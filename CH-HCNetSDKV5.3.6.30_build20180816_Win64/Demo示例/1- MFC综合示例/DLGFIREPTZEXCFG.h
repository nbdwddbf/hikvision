#pragma once
#include "afxwin.h"


// CDLGFIREPTZEXCFG 对话框

class CDLGFIREPTZEXCFG : public CDialogEx
{
	DECLARE_DYNAMIC(CDLGFIREPTZEXCFG)

public:
	CDLGFIREPTZEXCFG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDLGFIREPTZEXCFG();

// 对话框数据
	enum { IDD = IDD_DLG_FIREPTZEXCFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    float m_PTZEXPan;
    float m_PTZEXTilt;
    float m_PTZEXZoom;
    int m_PTZEXdwFocus;
    int m_PTZEXdwFocalLen;
    float m_SpeedEX_HorizontalSpeed;
    CComboBox m_comZoomType;
    afx_msg void OnBnClickedButtonPtzexGte();
    afx_msg void OnBnClickedButtonPtzexSet();

    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_THERMALPOWER_PARAM m_struBuiltinTHERMALPOWER;
    NET_DVR_PTZABSOLUTEEX_CFG m_struBuiltinPTZABSOLUTEEX;
    float m_SpeedEX_VerticalSpeed;
};
