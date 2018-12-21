#pragma once
#include "afxwin.h"


// CDlgIperf 对话框

class CDlgIperf : public CDialog
{
	DECLARE_DYNAMIC(CDlgIperf)

public:
	CDlgIperf(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgIperf();

// 对话框数据
	enum { IDD = IDD_DLG_IPERF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboProType();
	afx_msg void OnBnClickedBtnTest();
private:
	// 协议类型类型
	CComboBox m_ComboProType;
	CEdit m_EdtBandWidth;
	// 服务器IP
	CString m_strServerIP;
	// 服务器端口
	short m_wPort;
	UINT m_dwBandWidth;
	// 测试时间
	UINT m_dwTestTime;

protected:
	void RunIperf();
	HANDLE m_hProcess;
};
