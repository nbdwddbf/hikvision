#pragma once


// CDlgRemoteeMMC 对话框

class CDlgRemoteeMMC : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteeMMC)

public:
	CDlgRemoteeMMC(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRemoteeMMC();

// 对话框数据
	enum { IDD = IDD_DLG_eMMC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bChkeMMC;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();

public:
    LONG m_lUserID;
    int m_iDevIndex;
    int m_iStartChan;
    int m_iChanNum;
    char m_sCommand[256];
    int m_InPutXmlLen;

    CString m_csInputXml;
    char* m_pXmlOutput;
    afx_msg void OnBnClickedCancel2();
};
