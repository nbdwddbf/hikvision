#if !defined(AFX_DLGVQDCFG_H__53A754B1_6C12_4CC0_A1F9_143AE72CCFC5__INCLUDED_)
#define AFX_DLGVQDCFG_H__53A754B1_6C12_4CC0_A1F9_143AE72CCFC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVQDCfg.h : header file
//
#include "Markup.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVQDCfg dialog

class CDlgVQDCfg : public CDialog
{
// Construction
public:
	CDlgVQDCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVQDCfg)
	enum { IDD = IDD_DLG_VQD };
	CTreeCtrl	m_treeRecordChan;
	CTreeCtrl	m_treeChannel;
	CListCtrl	m_listVQDDiagnose;
	CComboBox	m_cmbGroupNo;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_cmbSnow;
	CComboBox	m_cmbSigLose;
	CComboBox	m_cmbPTZ;
	CComboBox	m_cmbLuma;
	CComboBox	m_cmbFreeze;
	CComboBox	m_cmbChroma;
	CComboBox	m_cmbBlur;
	CComboBox	m_cmbMotionWeek;
	CComboBox	m_cmbMotionDayCopy;
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbStreak;
	BOOL	m_bChkAlarmOutMap;
	BOOL	m_bChkAudioAlarm;
	BOOL	m_bChkBlur;
	BOOL	m_bChkChroma;
	BOOL	m_bChkEnable;
	BOOL	m_bChkFreeze;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkInvokeJPEGCapture;
	BOOL	m_bChkLuma;
	BOOL	m_bChkMonitorAlarm;
	BOOL	m_bChkPicFtp;
	BOOL	m_bChkPTZ;
	BOOL	m_bChkReportCenter;
	BOOL	m_bChkSiglose;
	BOOL	m_bChkSnow;
	BOOL	m_bChkStreak;
	UINT	m_dwHour11;
	UINT	m_dwHour12;
	UINT	m_dwHour21;
	UINT	m_dwHour22;
	UINT	m_dwHour31;
	UINT	m_dwHour32;
	UINT	m_dwHour41;
	UINT	m_dwHour42;
	UINT	m_dwHour51;
	UINT	m_dwHour52;
	UINT	m_dwHour62;
	UINT	m_dwHour61;
	UINT	m_dwHour71;
	UINT	m_dwHour72;
	UINT	m_dwHour81;
	UINT	m_dwHour82;
	UINT	m_dwMin11;
	UINT	m_dwMin21;
	UINT	m_dwMin12;
	UINT	m_dwMin22;
	UINT	m_dwMin31;
	UINT	m_dwMin32;
	UINT	m_dwMin41;
	UINT	m_dwMin42;
	UINT	m_dwMin51;
	UINT	m_dwMin52;
	UINT	m_dwMin61;
	UINT	m_dwMin62;
	UINT	m_dwMin71;
	UINT	m_dwMin72;
	UINT	m_dwMin82;
	UINT	m_dwMin81;
	BOOL	m_bSetAllChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVQDCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVQDCfg)
	afx_msg void OnBtnGetVQDDiagnose();
	afx_msg void OnBtnVQDLoopSet();
	afx_msg void OnBtnVQDLoopGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChkInvokeAlarmOut();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnMotionDayCopy();
	afx_msg void OnClickTreeChannel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeRecordChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboMotionWeekday();
	afx_msg void OnBtnOk();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnBtnUseDefaut();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_iDevIndex;
	LONG m_lUserID;
	BOOL	m_bAlarmOut[MAX_ALARMOUT_V30];
	BOOL    m_bChannelChecked[MAX_CHANNUM_V30];
	BOOL    m_bRecordChannel[MAX_CHANNUM_V30];
	DWORD   m_dwGetVQDChannel[MAX_CHANNUM_V30];
	LONG m_lListNum;
	BOOL m_bDayCopy;
	LONG m_lVQDDiagnoseHandle;
	HANDLE m_hVQDDiagnoseThread;

	NET_DVR_VQD_LOOP_DIAGNOSE_CFG m_struVQDLoopDiagnoseCfg;
	NET_DVR_CHANNEL_GROUP m_struChannelGroup;


	void CreateTree(void);
	
protected:
	void AddChanInfo();
	void AddGroupInfo();
	void AddThresholdInfo();
	int m_dwAllChanNum;
	BOOL TimeTest();
	BOOL CopyCurDayInfo();
	void CopyVQDTypeAndSensor();
	void GetHandleExceptinInfo();
	void SetVQDTypeAndSensor();
	void SetSchedTimeInfo(int iIndex);
	void SetTriggeredAlarmChannelShow(DWORD dwGroup);
	void SetTriggeredRecordChannelShow(DWORD dwGroup);
	int m_iAlarmOutNum;
	int m_iRecordChanNum;
	int m_iGetVQDInfoNum;
	void AddVQDDiagnoseInfoToList();
	BOOL DelFromArray(DWORD *dwArray, int iMaxIndex, int iCurIndex);
	int  FindFromArray(DWORD *dwArray, int iMaxArrayIndex, DWORD dwFindValue);
	char*   m_pRecvBuf;

	int m_iMaxThreosholdValue[32];
	int m_iDefaultThreosholdValue[32];
	BOOL ParseNetworkAbility(char *pBuf, DWORD dwBufSize);
	BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL ParseVQDSettingXml(CMarkup &struMarkup);
	BOOL ParseThresholdXml(CMarkup &struMarkup);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVQDCFG_H__53A754B1_6C12_4CC0_A1F9_143AE72CCFC5__INCLUDED_)
