#pragma once
#include "afxwin.h"
#include "atltime.h"
#include "afxcmn.h"


// CDlgRecordHostClassDataStatistic 对话框

class CDlgRecordHostClassDataStatistic : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecordHostClassDataStatistic)

public:
	CDlgRecordHostClassDataStatistic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRecordHostClassDataStatistic();

// 对话框数据
	enum { IDD = IDD_DLG_RECORD_HOST_CLASSDATA_STATISTIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bEnable;
	CComboBox m_comTargetType;
	CTime m_ctStartTime;
	CTime m_ctEndTime;
	CListCtrl m_listStatisticData;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonSearch();
	BOOL CreateClassDataControl(char* pBuf, DWORD dwBufLen, int &dwRet);
	void InitStatisticDataList();
	afx_msg LRESULT OnMsgGetStatisticDataFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgAddStatisticDataToList(WPARAM wParam, LPARAM lParam);
	void ProcessGetStatisticDataCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);

	LONG m_lUserID;
	int m_iDeviceIndex;
	LONG m_lGetStatisticDataHandle;
	CTime m_ctStartDate;
	CTime m_ctEndDate;
	afx_msg void OnClose();
};

