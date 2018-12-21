#pragma once
#include "afxcmn.h"



class CDlgAcsMoudleStatus : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAcsMoudleStatus)

public:
	CDlgAcsMoudleStatus(CWnd* pParent = NULL);
	virtual ~CDlgAcsMoudleStatus();

	enum { IDD = IDD_DLG_ACS_MOUDLE_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGet();
	CListCtrl m_listOnlineStatus;

	LONG m_lUserID;
	int m_iDeviceIndex;
	CListCtrl m_listDesmantelStatus;
};
