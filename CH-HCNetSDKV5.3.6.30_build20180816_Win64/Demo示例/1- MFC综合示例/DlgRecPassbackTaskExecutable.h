#pragma once
#include "afxcmn.h"


// CDlgRecPassbackTaskExecutable 对话框

class CDlgRecPassbackTaskExecutable : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecPassbackTaskExecutable)

public:
	CDlgRecPassbackTaskExecutable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRecPassbackTaskExecutable();


    LONG m_lUserID;
    int m_iDevIndex;
    LONG m_lSearchTaskExecutableHandle;
    NET_DVR_REC_PASSBACK_MANUAL_EXECUTABLE_SEND m_struRecPassBackExecutableSend;
    NET_DVR_REC_PASSBACK_MANUAL_EXECUTABLE_RET m_struRecPassBackExecutableRet;
    int m_nItemCount;

// 对话框数据
	enum { IDD = IDD_DLG_REC_PASS_BACK_EXECUTABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnAdd();
    CString m_csStreamID;
    int m_nChannel;
    CListCtrl m_listCtrlTaskExecutable;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnRemove();
    afx_msg void OnBnClickedBtnSet();
    afx_msg void OnBnClickedBtnStop();
};
