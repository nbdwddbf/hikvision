#pragma once
#include "afxwin.h"


// CDlgCVRResourceIPCfg 对话框

class CDlgCVRResourceIPCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCVRResourceIPCfg)

public:
	CDlgCVRResourceIPCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCVRResourceIPCfg();

// 对话框数据
	enum { IDD = IDD_DLG_CVR_RESOURCE_IP_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CComboBox m_comboAddressType;
    CComboBox m_comboIPVersion;
    CString m_strIPv4Address;
    CString m_strIPv6Address;
    CString m_strIPv4SubnetMask;
    CString m_strIPv6SubnetMask;
    afx_msg void OnBnClickedButtonGet();
    afx_msg void OnBnClickedButtonSet();

    LONG m_lUserID;
    int m_iDeviceIndex;
    BOOL CreateResourceIPCfg(char* pBuf, DWORD dwBufLen, int &dwRet);
};
