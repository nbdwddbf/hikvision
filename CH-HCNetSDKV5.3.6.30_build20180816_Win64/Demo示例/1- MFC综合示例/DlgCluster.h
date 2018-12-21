#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgCluster 对话框

class CDlgCluster : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCluster)

public:
	CDlgCluster(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCluster();

// 对话框数据
	enum { IDD = IDD_DLG_NVRDVR_CLUSTER };

    LONG m_lUserID;
    LONG m_lChannel;
    int m_iDeviceIndex;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonGet();
    afx_msg void OnBnClickedButtonSet();
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnBnClickedButtonAddtolist();
    afx_msg void OnBnClickedButtonDelfromlist();
    afx_msg void OnBnClickedButtonXml();
    afx_msg void OnBnClickedButtonAddall();
    //afx_msg void OnBnClickedButtonDelall();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonClearList();
    afx_msg void OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult);    
    afx_msg void OnBnClickedButtonModifyList();
    afx_msg void OnBnClickedButtonClusterCreate();

    virtual BOOL OnInitDialog();
public:   
    void Initbuff();
    BOOL ConvertModeXmlNodeToShow(const char* pXmlBuf);
    BOOL PackageModeXml(char* *pXmlBuf, DWORD &dwXmlLen);
    BOOL PackageDeviceInfoXml(char* *pXmlBuf, DWORD &dwXmlLen);
    BOOL PackageClusterInfoXml(char* *pXmlBuf, DWORD &dwXmlLen);
    BOOL PackageAllDeviceInfoXml(char* *pXmlBuf, DWORD &dwXmlLen);
    LONG GetUserID(int i);

    NET_DVR_XML_CONFIG_INPUT m_struInput;
    NET_DVR_XML_CONFIG_OUTPUT m_struOuput;

    char *m_pBuffer;
    DWORD m_dwBufferLen;

    CComboBox m_comboClusterIpMode;
    CComboBox m_comboNvrIpMode;
    CListCtrl m_listDevice;
    CComboBox m_comboClusterMode;
    CString m_csClusterIpv6;
    CString m_csNvrIpv6;
    CString m_csClusterIPv4;
    CString m_csNvrIpv4;
    CString m_csPassword;
    CString m_csPort;
    CString m_csUsername;
    CString m_csLastXml;
    BOOL m_bEnableInputXml;

    BOOL m_bEdit;
    BOOL m_bEnableEncrypt;
    int m_iSelectItem;
    BOOL m_bShowList;


    NET_DVR_USER_LOGIN_INFO m_struLoginInfo[20];
    DWORD m_dwUnitNum;
    CString m_csHttpPort;
    DWORD m_dwDeviceID;
    afx_msg void OnBnClickedButtonGetDeviceInfo();
    afx_msg void OnBnClickedBtnGetClusterStatus();
};
