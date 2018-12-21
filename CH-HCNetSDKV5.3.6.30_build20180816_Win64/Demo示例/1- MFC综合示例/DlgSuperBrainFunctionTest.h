#pragma once
#include "afxwin.h"
#include "ATLComTime.h"
#include "afxcmn.h"
#include "XMLParamsConvert.h"

// CDlgSuperBrainFunctionTest 对话框

class CDlgSuperBrainFunctionTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSuperBrainFunctionTest)

public:
	CDlgSuperBrainFunctionTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSuperBrainFunctionTest();

// 对话框数据
	enum { IDD = IDD_DLG_SUPER_BRAIN_FUNCTION_TEST };

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
    CComboBox m_comboImportType;
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
    COleDateTime m_ctTimeStart;
    COleDateTime m_ctDateEnd;
    COleDateTime m_ctTimeEnd;
    CComboBox m_comboSearchType;
    CListCtrl m_listModeData;
    BOOL m_bSearch;
    HANDLE	m_hSearchThread;
    int m_iRowCount;
    BOOL m_bSelectItem;
    int m_iSubItem;
    int m_iLastItem;
    LONG  m_lChannel;
    afx_msg void OnBnClickedButtonSearch();
    BOOL CreateSearchHumanCondition(char* pBuf, DWORD dwBufLen, int &dwRet);
    BOOL CreateSearchFaceCondition(char* pBuf, DWORD dwBufLen, int &dwRet);
    BOOL CreateSearchVehicleCondition(char* pBuf, DWORD dwBufLen, int &dwRet);
    void SearchData();
    afx_msg void OnBnClickedButtonAddList();
    afx_msg void OnBnClickedButtonDeleteList();
    virtual BOOL OnInitDialog();
    afx_msg void OnNMClickListModeData(NMHDR *pNMHDR, LRESULT *pResult);
    CString m_strSimilarity;
    afx_msg void OnBnClickedButtonFaceSearchExport();
    BOOL m_bMutiChannel;
    CListCtrl m_listChan;
    BOOL m_bLimitSearchChannel;
    afx_msg void OnNMClickListChan(NMHDR *pNMHDR, LRESULT *pResult);
    void UpdateChanStatus();
    CComboBox m_comboAgeGroupHuman;
    CComboBox m_comboBagHuman;
    CComboBox m_comboEventTypeFace;
    CComboBox m_comboEventTypeHuman;
    CComboBox m_comboEventTypeVehicle;
    CComboBox m_comboGenderHuman;
    CComboBox m_comboGlassHuman;
    CComboBox m_comboJacketColorHuman;
    CComboBox m_comboRideHuman;
    CComboBox m_comboSearchTypeHuman;
    CComboBox m_comboColorVehicle;
    CComboBox m_comboSearchTypeFace;
    CComboBox m_comboTypeVehicle;
    CString m_strFDIDFace;
    CString m_strLisencePlateVehicle;
    CString m_strLogVehicle;
    CString m_strModelVehicle;
    CString m_strPIDFace;
    CString m_strSubLogoVehicle;
    int m_iTotalSearchResult;
    CListCtrl m_listSearchResult;
    CString m_strSimilarityFace;
    void UpadateSearchResultList();
    void GetHumanSearchResult(CXmlBase xmlBase);
    void GetFaceSearchResult(CXmlBase xmlBase);
    void GetVehicleSearchResult(CXmlBase xmlBase);
    afx_msg void OnCbnSelchangeComboSearchType();
    afx_msg void OnNMClickListSearchResult(NMHDR *pNMHDR, LRESULT *pResult);
    int m_iRecvTimeOut;
};
