#pragma once
#include "afxwin.h"
#include "ATLComTime.h"
#include "afxcmn.h"
#include "XMLParamsConvert.h"

// CDlgFacelibSearch 对话框

class CDlgFacelibSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFacelibSearch)

public:
	CDlgFacelibSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFacelibSearch();

// 对话框数据
	enum { IDD = IDD_DLG_FACELIB_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    afx_msg LRESULT OnMsgUpdateData(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonBrowse();

    CString m_strFilePath;
    afx_msg void OnBnClickedButtonImport();
    CString m_strPicturePath;
    CString m_strModeData;
    LONG m_lUserID;
    int m_iDeviceIndex;
    CString m_strSearchID;
    int m_iMaxCountRet;
    int m_iCountStartRet;
    CString m_strSearchResult;
    CString m_strSearchStatus;
    int m_iCountResult;
    BOOL m_bRegerateID;
    int m_iStatusMaxCountRet;
    COleDateTime m_ctDateStart;
    COleDateTime m_ctDateEnd;
    CComboBox m_comboSearchType;
    BOOL m_bSearch;
    HANDLE m_hSearchThread;
    CString m_strSimilarity;
    afx_msg void OnBnClickedButtonSearch();

    BOOL CreateSearchFacelibCondition(char* pBuf, DWORD dwBufLen, int &dwRet);
    void SearchData();
    virtual BOOL OnInitDialog();
    void GetFacelibSearchResult(CXmlBase xmlBase);
    CListCtrl m_listSearchResult;
    BOOL m_bFDID;
    CComboBox m_comboCertficateType;
    CComboBox m_comboModelStatus;
    CComboBox m_comboSex;
    CString m_strCertificateNumber;
    CString m_strCity;
    CString m_strFDID;
    CString m_strName;
    CString m_strPhoneNumber;
    CString m_strProvince;
    afx_msg void OnNMClickListSearchResult(NMHDR *pNMHDR, LRESULT *pResult);
    int m_iRecvTimeOut;
    BOOL m_bBirthTime;
};
