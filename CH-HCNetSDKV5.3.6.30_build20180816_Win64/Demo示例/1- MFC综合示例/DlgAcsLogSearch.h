#pragma once
#include "afxwin.h"

// CDlgAcsLogSearch 对话框

class CDlgAcsLogSearch : public CDialog
{
	DECLARE_DYNAMIC(CDlgAcsLogSearch)

public:
	CDlgAcsLogSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAcsLogSearch();

// 对话框数据
	enum { IDD = IDD_DLG_ACS_LOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnMsgAddAcsEventToList(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgGetAcsEventFinish(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnSearch();
    afx_msg void OnBnClickedBtnExit();
    LONG m_lUserID;
    int m_iDeviceIndex;
    NET_DVR_ACS_EVENT_COND m_struAcsEventCond;
    int AddMinorAllString(int iStartSel);
    int AddMinorAlarmString(int iStartSel);
    int AddMinorExceptionString(int iStartSel);
    int AddMinorOperationString(int iStartSel);
    int AddMinorEventString(int iStartSel);
    CComboBox m_cmbMajorType;
    CComboBox m_cmbMinorType;
    COleDateTime m_startDate;
    COleDateTime m_startTime;
    COleDateTime m_stopDate;
    COleDateTime m_stopTime;
    CListCtrl m_listDeviceLog;
    CString m_csCardNo;
    CString m_csName;
    BOOL m_bPictureEnable;
    DWORD m_dwBeginSerialNo;
    DWORD m_dwEndSerialNo;
    afx_msg void OnCbnSelchangeComboMajorType();
    static void AlarmMinorTypeMap(LPNET_DVR_ACS_EVENT_CFG lpAcsEventCfg, CString &szTemp);
    static void ExceptionMinorTypeMap(LPNET_DVR_ACS_EVENT_CFG lpAcsEventCfg, CString &szTemp);
    static void OperationMinorTypeMap(LPNET_DVR_ACS_EVENT_CFG lpAcsEventCfg, CString &szTemp);
    static void EventMinorTypeMap(LPNET_DVR_ACS_EVENT_CFG lpAcsEventCfg, CString &szTemp);
    LONG m_lGetAcsEvent;
    void ProcessGetAcsEventCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    LONG m_lLogNum;
    CComboBox m_comInductiveEventType;
    CComboBox m_comSearchType;
    int m_iChannel;
    CString m_strMonitorId;
};
