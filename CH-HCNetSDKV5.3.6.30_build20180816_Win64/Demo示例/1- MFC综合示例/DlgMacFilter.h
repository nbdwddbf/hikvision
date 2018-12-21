#pragma once


// CDlgMacFilter 对话框

class CDlgMacFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMacFilter)

public:
	CDlgMacFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMacFilter();

// 对话框数据
	enum { IDD = IDD_DLG_MAC_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CComboBox m_enable;
    CComboBox m_permit;
    CListCtrl m_maclist;
    afx_msg void OnBnClickedButtonGet();
    afx_msg void OnBnClickedButtonSet();
    LONG m_lServerID;
    int m_iDeviceIndex;
    LONG m_lChannel;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_MACFILTER_CFG m_struBuiltinMACFILTER;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonAddmac();
    int idtemp = 0;
    CString m_macaddress;
    CEdit m_adrescon;
};
