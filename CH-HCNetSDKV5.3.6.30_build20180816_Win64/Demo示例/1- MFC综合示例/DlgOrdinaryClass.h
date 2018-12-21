#pragma once


// CDlgOrdinaryClass 对话框

class CDlgOrdinaryClass : public CDialog
{
	DECLARE_DYNAMIC(CDlgOrdinaryClass)

public:
	CDlgOrdinaryClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOrdinaryClass();
    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_ORDINARY_CLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_iDevIndex;
    long m_lServerID;
    afx_msg void OnBnClickedBtnGetOrdinaryClass();
    afx_msg void OnBnClickedBtnSetOrdinaryClass();
    int m_iOrdinaryClassNo;
    CComboBox m_cmbEnable;
    CString m_csClassName;
    int m_iAttendanceRuleNo;
    DWORD m_dwTimeID[4];
    CString m_csOnDutyTime[4];
    CString m_csOffDutyTime[4];
    BOOL CreateOrdianaryClassXml(char* pBuf, DWORD dwBufLen, int &dwRet);
};
