#if !defined(AFX_DLGEXCEPTIONCFG_H__EA1C43CF_714F_41A0_8B3C_455603975E41__INCLUDED_)
#define AFX_DLGEXCEPTIONCFG_H__EA1C43CF_714F_41A0_8B3C_455603975E41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExceptionCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgExceptionCfg dialog

class CDlgExceptionCfg : public CDialog
{
// Construction
public:
	CDlgExceptionCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExceptionCfg)
	enum { IDD = IDD_DIALOG_EXCEPTION_CFG };
	CTreeCtrl	m_treeAlarmOut;
	CComboBox m_comboExceptionType;
	BOOL m_bChkMonitorAlarm;
	BOOL m_bChkVoiceAlarm;
	BOOL m_bChkUploadCenter;
	BOOL m_bChkInvokeAlarmOut;
	BOOL m_bChkInvokeJpegCapture;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExceptionCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnBnClickedBtnExceptionOk();
	afx_msg void OnBnClickedChkExceptionInvokeAlarmOut();
	afx_msg void OnCbnSelchangeComboExceptionType();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExceptionCfg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	
	int m_iDeviceIndex;
	LONG	m_lLoginID;
	DWORD	m_dwAlarmOutNum;
	NET_DVR_EXCEPTION_V30 m_struExceptionInfo;
	BOOL m_bSetPara;
	int	 m_iExceptionType;
	
	void CurCfgUpdate();
	BOOL CheckInitParam();
	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
	void CreateTree(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXCEPTIONCFG_H__EA1C43CF_714F_41A0_8B3C_455603975E41__INCLUDED_)
