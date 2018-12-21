#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CDlgBatchUploadBlackList 对话框

class CDlgBatchUploadBlackList : public CDialog
{
	DECLARE_DYNAMIC(CDlgBatchUploadBlackList)

public:
	CDlgBatchUploadBlackList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBatchUploadBlackList();

// 对话框数据
	enum { IDD = IDD_DLG_BATCH_UPLOAD_BLACK_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_listViewOfBlackList;
    CString m_csName;
    CComboBox m_comboxSex;
    CComboBox m_comboxNation;
    CDateTimeCtrl m_dtcBirthday;
    BOOL m_bIsLongTermValid;
    CDateTimeCtrl m_dtcValidPeriodStart;
    CDateTimeCtrl m_dtcValidPeriodEnd;
    CString m_csAddress;
    CString m_csIDNumber;
    CString m_csIssuingAuthority;
    afx_msg void OnBnClickedButtonUploadList();
    afx_msg void OnBnClickedButtonDeleteByid();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonClear();
    virtual BOOL OnInitDialog();
    afx_msg void OnClose();

public:
    LONG m_lServerID;
    int m_iDeviceIndex;

    BOOL m_bValid;
    int GetExistItem(const NET_DVR_UPLOAD_ID_BLACK_LIST_CFG *lpCardCfg);
    void ProcessUploadCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    BOOL SendFirst();
    BOOL SendNext();
    void Clear();
    DWORD m_dwSendIndex;       //下发序号
    LONG m_lUploadCfgHandle;
    DWORD m_dwNumOfBlackID;
protected:
    afx_msg LRESULT OnMsgUploadFinish(WPARAM wParam, LPARAM lParam);
};
