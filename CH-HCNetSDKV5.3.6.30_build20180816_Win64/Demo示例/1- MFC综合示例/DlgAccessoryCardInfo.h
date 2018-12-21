#pragma once


// CDlgAccessoryCardInfo 对话框

class CDlgAccessoryCardInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAccessoryCardInfo)

public:
	CDlgAccessoryCardInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAccessoryCardInfo();

// 对话框数据
	enum { IDD = IDD_DLG_ACCESSORY_CARDINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CString m_szAccessoryCardInfo;
    int m_lUserID;
    int m_lChanNo;
    int m_iDevIndex;
    afx_msg void OnBnClickedBtnGet();
    afx_msg void OnBnClickedCancel();
};
#pragma once


