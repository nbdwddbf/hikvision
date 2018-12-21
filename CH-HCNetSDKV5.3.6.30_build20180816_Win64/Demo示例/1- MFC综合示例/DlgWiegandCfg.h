#pragma once
#include "afxwin.h"


// CDlgWiegandCfg 对话框

class CDlgWiegandCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWiegandCfg)

public:
	CDlgWiegandCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWiegandCfg();

// 对话框数据
	enum { IDD = IDD_DLG_ACS_WIEGAND_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int m_iWiegandNo;
	CComboBox m_cmbCommunicationDirection;
	CComboBox m_cmbWiegandMode;
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonSet();

	LONG m_lUserID;
	int m_iDeviceIndex;
	BOOL CreateWiegandCfg(char* pBuf, DWORD dwBufLen, int &dwRet);
	afx_msg void OnCbnSelchangeComboCommunicationDirection();
};
