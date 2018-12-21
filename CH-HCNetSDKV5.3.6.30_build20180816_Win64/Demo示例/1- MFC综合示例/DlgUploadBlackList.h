#include "afxcmn.h"
#include "afxwin.h"
#if !defined(AFX_DLGUPLOADBLACKLIST_H__5157B0AE_EC89_409A_A3BC_A1CFC13737E0__INCLUDED_)
#define AFX_DLGUPLOADBLACKLIST_H__5157B0AE_EC89_409A_A3BC_A1CFC13737E0__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CDlgUploadBlackList 对话框

#define UPLOAD_BLACK_LIST_TIMER WM_USER+103

class CDlgUploadBlackList : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUploadBlackList)

public:
	CDlgUploadBlackList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUploadBlackList();

    LONG m_lServerID;
    int m_iDeviceIndex;
    LONG m_lChannel;

// 对话框数据
	enum { IDD = IDD_DLG_ACS_UPLOAD_BLACK_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGetFilepath();

    CString m_strFilePath;
    LONG m_iFileSize;
    LONG m_lUploadHandle;
    LONG m_lDownloadHandle;

    BOOL m_bUploading;        //正在上传
    BOOL m_bDownloading;      //正在下载

	LONG    m_timerHandle;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnUplaod();
    afx_msg void OnBnClickedBtnStop();
    afx_msg void OnBnClickedBtnExit();
    CString m_szDowndFilePath;
    CProgressCtrl m_ctrlProgress;
    CStatic m_statProgress;
    afx_msg void OnBnClickedBtnSetFilepath();
    afx_msg void OnBnClickedBtnDownload();
    afx_msg void OnCbnSelchangeCmbUpload();
    afx_msg void OnCbnSelchangeCmbDownload();
    CComboBox m_cmbUploadType;
    CComboBox m_cmbDownLoadType;
    DWORD m_dwUploadAudioNo;
    DWORD m_dwDownloadAudioNo;
};
#endif // !defined(AFX_DLGUPLOADBLACKLIST_H__5157B0AE_EC89_409A_A3BC_A1CFC13737E0__INCLUDED_)
