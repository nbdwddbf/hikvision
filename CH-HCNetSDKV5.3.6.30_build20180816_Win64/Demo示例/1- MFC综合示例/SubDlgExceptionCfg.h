#pragma once
#include "afxwin.h"


// CSubDlgExceptionCfg dialog

class CSubDlgExceptionCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgExceptionCfg)

public:
	CSubDlgExceptionCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgExceptionCfg();

// Dialog Data
public:

	//{{AFX_DATA(CSubDlgExceptionCfg)
	enum { IDD = IDD_SUB_DLG_EXCEPTION_CFG };
	CTreeCtrl	m_treeAlarmOut;
	CComboBox m_comboExceptionType;
	BOOL m_bChkMonitorAlarm;
	BOOL m_bChkVoiceAlarm;
	BOOL m_bChkUploadCenter;
	BOOL m_bChkInvokeAlarmOut;
	BOOL m_bChkInvokeJpegCapture;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CSubDlgExceptionCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgExceptionCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnExceptionOk();
	afx_msg void OnBnClickedChkExceptionInvokeAlarmOut();
	afx_msg void OnCbnSelchangeComboExceptionType();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	LONG	m_lLoginID;
	DWORD	m_dwAlarmOutNum;
	NET_DVR_EXCEPTION_V40* m_pStruExceptionInfo;
	BOOL m_bSetPara;
	int	 m_iExceptionType;
	
	void CurCfgUpdate();
	BOOL CheckInitParam();
	BOOL CfgSetup();
	int m_iDeviceIndex;
	BOOL *m_pbAlarmOut;
	void CreateTree(void);
};
