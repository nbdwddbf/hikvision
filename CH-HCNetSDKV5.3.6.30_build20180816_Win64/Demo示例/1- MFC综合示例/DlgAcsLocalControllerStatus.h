#pragma once
#include "afxcmn.h"


// CDlgAcsLocalControllerStatus 对话框

class CDlgAcsLocalControllerStatus : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAcsLocalControllerStatus)

public:
	CDlgAcsLocalControllerStatus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAcsLocalControllerStatus();

// 对话框数据
	enum { IDD = IDD_DLG_ACS_LOCAL_CONTROLLER_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnMsgGetStatusFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgAddStatusToList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUpdateData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnNMClickListLocalControllerStatus(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
public:
	int m_iLocalController;
	CListCtrl m_listLocalControllerStatus;
	int m_iSelectItem;
	LONG m_lServerID;
	LONG m_iDevIndex;
	LONG m_lGetStatusHandle;
	LONG m_lSetStatusHandle;	

	void AddToStatusList(const NET_DVR_LOCAL_CONTROLLER_STATUS& struStatusInfo, const WORD wLocalControllerNo);
	void ProcessGetStatusCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
	LPNET_DVR_LOCAL_CONTROLLER_STATUS GetSelItem();
	void UpdateSubList(const NET_DVR_LOCAL_CONTROLLER_STATUS *lpStatus);
	CListCtrl m_listMagneticStatus;
	CListCtrl m_listDoorLockStatus;
	CListCtrl m_listReaderStatus;
	afx_msg void OnClose();
};
