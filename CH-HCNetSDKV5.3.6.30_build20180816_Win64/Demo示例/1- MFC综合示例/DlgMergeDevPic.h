#include "afxwin.h"
#if !defined(AFX_DLGMERGEDEVPIC_H__70CCB0E2_4161_4E1B_9C83_F8AF9747E476__INCLUDED_)
#define AFX_DLGMERGEDEVPIC_H__70CCB0E2_4161_4E1B_9C83_F8AF9747E476__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMergeDevPic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDevPic dialog

#define  MAX_UPLOAD_PIC_LEN    10 * 1024 * 1024    //最大图片缓存长度512KB(上层用户自己限制，客户端应根据设备能力集设置)

class CDlgMergeDevPic : public CDialog
{
// Construction
public:
	CDlgMergeDevPic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMergeDevPic)
	enum { IDD = IDD_DLG_MERGE_DEV_PIC };
	CComboBox	m_comboPicWinNo;
	CComboBox	m_comboPicNo;
	CComboBox	m_comboOutputNo;
	BOOL	m_bFlash;
	BOOL	m_bPicExist;
	BOOL	m_bShow;
	BOOL	m_bTranslucent;
	DWORD	m_dwHeight;
	CString	m_csPicName;
	CString	m_csPicPath;
	DWORD	m_dwWidth;
	DWORD	m_dwX;
	DWORD	m_dwY;
	CString	m_csUploadProgress;
	DWORD	m_dwPicHeight;
	DWORD	m_dwPicWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMergeDevPic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMergeDevPic)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboPicNo();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnUpload();
	afx_msg void OnBtnGetPicInfo();
	afx_msg void OnSelchangeComboOutputNo();
	afx_msg void OnSelchangeComboPicWinNo();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExist();
	afx_msg void OnBtnDelete();
    afx_msg void OnBnClickedBtnUploadByBuf();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBtnSetPicInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    BOOL ReadPictureInfoToBuf(const char* sFilePath);

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    LONG m_lUploadHandle;
    LONG m_lUploadByBufHandle;
    HANDLE	m_hPicUpLoadThread;


    NET_DVR_PICTURECFG m_struPicCfg;
    NET_DVR_OUTPUT_PIC_CFG m_struOutputPicCfg[4];
    char m_szLan[64];
    //用于按图片缓存上传图片的缓存区,小于10MB(上层用户自己限制)
    BYTE* m_pszUploadPicBuf;
    DWORD m_dwSendBufLen;

    static DWORD WINAPI PicUpLoadByBufThread(LPVOID pParam);
    afx_msg void OnDestroy();
    CComboBox m_cmUploadSendPicType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMERGEDEVPIC_H__70CCB0E2_4161_4E1B_9C83_F8AF9747E476__INCLUDED_)
