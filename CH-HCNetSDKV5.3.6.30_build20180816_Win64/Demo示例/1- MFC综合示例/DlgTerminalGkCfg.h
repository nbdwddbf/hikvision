#pragma once
#include "afxwin.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度

// CDlgTerminalGkCfg 对话框

class CDlgTerminalGkCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTerminalGkCfg)

public:
	CDlgTerminalGkCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTerminalGkCfg();

// 对话框数据
	enum { IDD = IDD_DLG_GK_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGet();
    CComboBox m_cmbIpType;
    BOOL m_bEnable;
    CString m_szIPV4;
    CString m_szIPV6;
    UINT m_wPort;
    CString m_szName;
    afx_msg void OnBnClickedBtnSet();

private:
    LONG m_lUserID;
    LONG m_iDeviceIndex;

public:
    BOOL ConvertGkCfgXmlToStru(char *OutputXmlBuffer, NET_DVR_TERMINAL_GK_CFG *struGkCfg);
    BOOL ConvertGkCfgStruToXml(NET_DVR_TERMINAL_GK_CFG*pStruct, char* *pXmlBuf, DWORD &dwInputSize);
public:
    virtual BOOL OnInitDialog();
    CComboBox m_cmbType;
    BOOL m_bStatus;
    BOOL m_byBuildGk;
    CString m_csPwd;
};
