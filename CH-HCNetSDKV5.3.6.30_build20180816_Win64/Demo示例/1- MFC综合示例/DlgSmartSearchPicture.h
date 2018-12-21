#include "afxwin.h"
#if !defined(AFX_DLGSMARTSEARCHPIC_H__8D8921D7_5CD2_40D5_A33E_5AC96980E365__INCLUDED_)
#define AFX_DLGSMARTSEARCHPIC_H__8D8921D7_5CD2_40D5_A33E_5AC96980E365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSmartSearchPicture.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgSmartSearchPicture dialog

class CDlgSmartSearchPicture : public CDialog
{
// Construction
public:
	CDlgSmartSearchPicture(CWnd* pParent = NULL);   // standard constructor
    ~CDlgSmartSearchPicture();
    // Dialog Data
    //{{AFX_DATA(CDlgSmartSearchPicture)
	enum { IDD = IDD_DLG_SMART_SEARCH_PIC };
	CComboBox	m_cmbDetectFaceRet;
	CComboBox	m_cmbSex;
	CComboBox	m_cmbEyeGlass;
	CComboBox	m_cmbAge;
    CComboBox	m_comProvince;
    CComboBox	m_comboBackupType;
    CStatic	m_ShowJpegCtrl;
    CProgressCtrl	m_downProgress;
    CListCtrl	m_PicList;
    CComboBox	m_PicTypeCtrl;
    CComboBox	m_ChannelCtrl;
    CString	m_sCardNum;
    BOOL	m_bChkCard;
    CTime	m_ctDateStart;
    CTime	m_ctDateStop;
    CTime	m_ctTimeStart;
    CTime	m_ctTimeStop;
    BOOL	m_bContinue;
    CString	m_sLicense;
	float	m_fWidth;
	float	m_fX;
	float	m_fY;
	float	m_fHeight;
	BOOL	m_bDrawMaxFilter;
	BOOL	m_bDrawMiniFilter;
	BOOL	m_bEnable;
	BOOL	m_bFilterActive;
	UINT	m_dwFaceScore;
    CComboBox	m_comboCountry;
	//}}AFX_DATA
    
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDlgSmartSearchPicture)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    
    // Generated message map functions
    //{{AFX_MSG(CDlgSmartSearchPicture)
    virtual void OnOK();
    virtual void OnCancel();
    virtual BOOL OnInitDialog();
    afx_msg void OnSearchlist();
    afx_msg void OnDownload();
    afx_msg void OnCheckcard();
    afx_msg void OnClickRemotepiclist(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDestroy();
    afx_msg void OnUpload();
	afx_msg void OnSelchangePictype();
	afx_msg void OnButtonBrowseFile();
	afx_msg void OnBtnSend();
    afx_msg void OnSelchangeComboDetectFaceResult();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    
    void F_Close();
    BOOL CheckInitParam();
    void SetParentWnd(HWND *hhWnd, int iParentNum);
    void GetFindPictureParamFromWnd();
    void GetFindPictureParamFromWnd(NET_DVR_FIND_PICTURE_PARAM &struPictureParam);
    BOOL GetBackupPictureParamFromWnd_FILE(NET_DVR_BACKUP_PICTURE_PARAM &struBackPicturParam);
    BOOL GetDiskList(NET_DVR_DISKABILITY_LIST &struDiskList);
    DWORD ProcessFileSize(CString csFileSize);
    void RefreshPicShowList();
    void AddHumanFeatureInfo();
    BOOL m_bDown;
    BOOL m_bSearchDown;
    BOOL m_bBackuping;
    HANDLE m_hBackupThread;
    
    int m_iChannel;
    HWND m_hPareTabWnd;
    HWND m_hPareDlgWnd;
    LONG  m_lFileHandle;
    HANDLE m_hFileThread;
    HANDLE m_hGetThread;
    int iFileType;
    int m_iFileNum;
    int iSelServer;
    LONG m_lStartChan;
    LONG m_lServerID;
    LONG m_lServerType;
    int m_iIPChanNum;
    int m_iChanNum;
    BOOL m_bFindFile;
    char filenamedownload[256];
    int m_iDeviceIndex;
    
    POSITION  pos;
    int nSelPics;
    int nDownPics;
    NET_DVR_FIND_PICTURE_PARAM m_struFindPictureParam;
    NET_DVR_DISKABILITY_LIST  m_struDiskList;
    
    NET_DVR_SMART_SEARCH_PIC_PARA  m_struSmartPic;
    LONG    m_lBackupHandle;
    NET_DVR_FIND_PICTURE *m_pFindPicture;
    NET_VCA_FD_PROCIMG_RESULT m_struDFProcImgRet;
protected:
    CRect m_rcWnd ;
    char m_chFilename[256]; //抓图保存的位置
    CString	m_csFilePath;
    DWORD m_dwUploadFileSize;
    NET_VCA_FD_PROCIMG_CFG m_struFDProcImgCfg;
    BOOL m_bDetectSuccess;
    BYTE *m_pPicInfo;

public:
    BOOL m_bVcaRectOnly;
    CString m_strFilePath;
    int m_dwPID;
    CString m_dwUploadProgress;
    HANDLE  m_hFile;
    LONG m_iFileSize;
    LONG m_lUploadHandle;
    HANDLE	m_hUpLoadThread;
    BOOL    m_bUpLoading;
    NET_DVR_UPLOAD_FACE_ANALYSIS_DATA_OUT m_struFaceAnalysisDataOut;
    afx_msg void OnBnClickedBtnSelectFile();
    afx_msg void OnBnClickedBtnStartUpload();
    afx_msg void OnBnClickedButtonUpdate();
    CComboBox m_comBehaviorSearchType;
    BOOL m_bHumanMisinfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSMARTSEARCHPIC_H__8D8921D7_5CD2_40D5_A33E_5AC96980E365__INCLUDED_)
