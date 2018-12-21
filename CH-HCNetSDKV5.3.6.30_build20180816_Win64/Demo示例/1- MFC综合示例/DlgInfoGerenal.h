#pragma once

string GB2UTF(const char* gb2312);
string UTF2GB(const char* utf8);
// CDlgInfoGerenal 对话框

class CDlgInfoGerenal : public CDialog
{
	DECLARE_DYNAMIC(CDlgInfoGerenal)

public:
	CDlgInfoGerenal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInfoGerenal();

// 对话框数据
	enum { IDD = IDD_DLG_INFO_DIFFUSION_GERERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnTerAdd();

    DWORD m_dwId;
    CString m_csType;
    DWORD m_dwTerminalNo;
    CString m_csValue;
    CListCtrl m_listTerminal;
    CListCtrl m_listGeneral;
    CString m_csDataType;
    CString m_csCommand;
    CString m_csRefreshD;
    int m_nCurSelTerminal;
    int m_nCurSelGeneral;
    virtual BOOL OnInitDialog();

private:
    LONG m_lUserID;
    int m_iDeviceIndex;
    int m_arrTerminal[32];
    int m_iTerminalCount;
    CString m_arrStr[32];
    CString m_csData;
    int m_iData;
public:
    afx_msg void OnBnClickedBtnGroupAdd();
    afx_msg void OnBnClickedBtnGroupList();
    afx_msg void OnBnClickedBtnClean();
    afx_msg void OnBnClickedBtnCancel();
    afx_msg void OnBnClickedBtnOk();
    afx_msg void OnBnClickedBtnTerDel();
    afx_msg void OnBnClickedBtnTerMod();
    afx_msg void OnNMClickListTerminal(NMHDR *pNMHDR, LRESULT *pResult);
    CString m_csMaterialName;
};

