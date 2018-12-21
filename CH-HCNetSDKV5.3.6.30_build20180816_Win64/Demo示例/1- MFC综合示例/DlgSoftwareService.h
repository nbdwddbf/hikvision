#pragma once
#include "afxwin.h"


// CDlgSoftwareService 对话框

class CDlgSoftwareService : public CDialog
{
	DECLARE_DYNAMIC(CDlgSoftwareService)

public:
	CDlgSoftwareService(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSoftwareService();

// 对话框数据
	enum { IDD = IDD_DLG_IPC_SOFTWARE_SERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGet();
    afx_msg void OnBnClickedBtnSet();
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    CComboBox m_cmbThirdStreamEnabled;
    NET_DVR_SOFTWARE_SERVICE_CFG m_strSoftwareService;
    CComboBox m_cmbSubStream;
};
