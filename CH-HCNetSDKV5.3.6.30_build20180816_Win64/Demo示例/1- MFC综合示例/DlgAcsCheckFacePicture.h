#pragma once


// CDlgAcsCheckFacePicture 对话框

class CDlgAcsCheckFacePicture : public CDialog
{
	DECLARE_DYNAMIC(CDlgAcsCheckFacePicture)

public:
	CDlgAcsCheckFacePicture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAcsCheckFacePicture();

// 对话框数据
	enum { IDD = IDD_DLG_ACS_CHECK_FACE_PICTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    LONG m_lServerID;
    int m_iDeviceIndex;
    CListCtrl m_listPicture;
    DWORD m_dwPictureLen;
    CString m_szPictureName;
    DWORD m_dwPictureNo;
    DWORD m_dwLen;
    LONG m_lUploadPicCfgHandle;
    DWORD m_dwSendIndex;       //校验序号
    virtual BOOL OnInitDialog();
    char * ReadPictureFromFile(CString csFileName);
    char * ReadTemplateFromFile(CString fileName);
    int GetExistItem(const NET_DVR_CHECK_FACE_PICTURE_CFG *lpCheckFacePictureCfg);
    void Clear();
    BOOL SendFirstPicture();
    BOOL SendNextPicture();
    void ProcessCheckFacePictureCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);

    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonClear();
    afx_msg void OnBnClickedButtonUpload();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonBrowse();
    afx_msg LRESULT OnMsgCheckFacePictureCfgFinish(WPARAM wParam, LPARAM lParam);
    BOOL m_bEnableTemplate;
    DWORD m_dwTemplateLen;
    CString m_csTemplatePath;
    afx_msg void OnBnClickedButtonBrowse2();
};
