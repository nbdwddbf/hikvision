#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define TIMER_UPDOWNLOAD_THIRD_PROGRESS 1 //上传下载进度定时器
// CDlgDyanmicPic 对话框

class CDlgDyanmicPic : public CDialog
{
	DECLARE_DYNAMIC(CDlgDyanmicPic)

public:
	CDlgDyanmicPic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDyanmicPic();

// 对话框数据
	enum { IDD = IDD_DLG_INFO_DIFFUSION_DYNAMIC_PIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonOk();

public:
    CString m_csCancelType;
    CString m_csDisplayType;
    CString m_csFileType;
    CString m_csPicType;
    DWORD m_dwDuration;
    DWORD m_dwFileSize;
    DWORD m_dwMaterialId;
    DWORD m_dwTerminalNo;
    CListCtrl m_listTerminal;
    CString  m_csFilePath;
    int m_nCurSelTerminal;
    int m_nCurSelOrg;
    afx_msg void OnBnClickedBtnTerAdd();

    int m_arrTerminal[64];
    int m_iTerminalCount;
    int m_arrOrg[64];
    int m_iOrgCount;
    afx_msg void OnBnClickedBtnMaterialChoose();
    CProgressCtrl m_ctrlProgress;
    CStatic m_statProgress;

private:
    LONG m_lUserID;
    int m_iDeviceIndex;
    LONG m_lHandle;
    bool m_bUploading;
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedBtnTerDel();
    afx_msg void OnBnClickedBtnTerMod();
    afx_msg void OnNMClickListTerminal(NMHDR *pNMHDR, LRESULT *pResult);
    virtual BOOL OnInitDialog();
    CString m_csMaterialName;
    DWORD m_iOrg;
    CListCtrl m_listOrg;
    afx_msg void OnBnClickedBtnTerAdd2();
    DWORD m_iOrgNo;
};
