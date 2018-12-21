#pragma once
#include "afxcmn.h"
#include <map>

// DlgAcsFaceAndTemplate 对话框
enum DATA_TYPE
{
    FACE,
    TEMPLATE
};

class DlgAcsFaceAndTemplate : public CDialog
{
	DECLARE_DYNAMIC(DlgAcsFaceAndTemplate)

public:
	DlgAcsFaceAndTemplate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgAcsFaceAndTemplate();

// 对话框数据
	enum { IDD = IDD_DLG_ACS_FACE_TEMPLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    LONG m_lServerID;
    int m_iDeviceIndex;
    DWORD m_dwDataLen;
    LONG m_lSetDataCfgHandle;
    LONG m_lGetDataCfgHandle;
    DWORD m_dwSendIndex;

    CListCtrl m_listFaceAndTemplate;
    CString m_csCardNo;
    CString m_csFacePath;
    CString m_csTemplatePath;
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedButtonStop();
    afx_msg void OnBnClickedButtonGet();
    afx_msg void OnBnClickedButtonSet();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonBrowseFace();
    afx_msg void OnBnClickedButtonBrowseTemplate();

    char * ReadDataFromFile(CString fileName, DATA_TYPE enumDataType);
    int GetExistItem(const NET_DVR_FACE_AND_TEMPLATE_CFG *lpDataCfg);
    void Clear();
    BOOL SendFirstPicture();
    BOOL SendNextPicture();
    void ProcessFaceCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void ProcessGetFaceCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);

    map<CString, CString> m_mTemplatePaths; //与卡号关联，存储模板数据路径
    map<CString, CString> m_mFacePaths; //与卡号关联，存储人脸数据路径
    afx_msg void OnLvnItemchangedListFaceTempalteCfg(NMHDR *pNMHDR, LRESULT *pResult);
    DWORD m_dwFaceNum;
protected:
    afx_msg LRESULT OnMsgSetFaceFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgGetFaceFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgAddFaceTolist(WPARAM wParam, LPARAM lParam);
};
