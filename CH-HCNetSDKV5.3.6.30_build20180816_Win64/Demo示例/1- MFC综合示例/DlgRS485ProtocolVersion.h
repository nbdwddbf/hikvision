#pragma once


// CDlgRS485ProtocolVersion 对话框

class CDlgRS485ProtocolVersion : public CDialog
{
	DECLARE_DYNAMIC(CDlgRS485ProtocolVersion)

public:
	CDlgRS485ProtocolVersion(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRS485ProtocolVersion();
    CString  m_csVersion;
    LONG m_lUserID;
// 对话框数据
	enum { IDD = IDD_DLG_RS485_VERSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGet();
};
