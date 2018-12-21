#if !defined(AFX_DLGINFODIFFUSIONPLAY_H__856E2359_D3BE_4AF6_977C_F16716FA0D15__INCLUDED_)
#define AFX_DLGINFODIFFUSIONPLAY_H__856E2359_D3BE_4AF6_977C_F16716FA0D15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionPlay.h : header file
//

#include "InfoDiffusionParamsConvert.h"
#include "ATLComTime.h"
#include "afxcmn.h"

#define MAX_LEN_XML  10*1024*1024   //xml最大长度
#define IMAGE_BUFFER 10*1024*1024   //图像缓冲区

//结束长连接消息
const int WM_STOP_REMOTE_CFG = WM_USER + 1;

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionPlay dialog

class CDlgInfoDiffusionPlay : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionPlay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionPlay)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_PLAY };
	CComboBox	m_cmbFontDirect;
	CComboBox	m_cmbPlayMode;
	CComboBox	m_cmbCtrlType;
	CComboBox	m_cmbInsertType;
	CComboBox	m_cmbTargetType;
	CComboBox   m_cmbPlanType;
	CListCtrl	m_listTerminal;
	DWORD	m_dwTerminalID;
	DWORD	m_dwProgramID;
	DWORD	m_dwProgramDuration;
	DWORD	m_dwPrtScnID;
	DWORD	m_dwMaterialID;
	DWORD	m_dwPlayCount;
	DWORD	m_dwPositionHeight;
	DWORD	m_dwPositionWidth;
	DWORD	m_dwPositionX;
	DWORD	m_dwPositionY;
	BOOL	m_bFontEnable;
	DWORD	m_dwFontSize;
	DWORD	m_dwFontSpeed;
	DWORD	m_dwBackBlue;
	DWORD	m_dwBackGreen;
	DWORD	m_dwBackRed;
	DWORD	m_dwFontBlue;
	DWORD	m_dwFontGreen;
	DWORD	m_dwFontRed;
	BOOL	m_bPlanEnable;
	DWORD	m_dwTransparent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionPlay)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboCtrlType();
	afx_msg void OnSelchangeComboInsertType();
	afx_msg void OnSelchangeComboTargetType();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnControl();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnMod();
	afx_msg void OnBtnPrtscn();
	afx_msg void OnDestroy();
	afx_msg void OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboPlayMode();
	//}}AFX_MSG
    LRESULT OnStopRemoteConfig(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;
	
	int m_nCurSelTerminal;
	
	char* m_pOutputXmlBuffer;
	char* m_pImageBuffer;

	LPNET_DVR_PLAY_CONTROL m_lpControl;
    LONG m_lConfigHandle;

public:
	void InitTerminalCtrlList();
	void RefreshTernimalList(CString strTargetType);
    COleDateTime m_dateTime;
    COleDateTime m_timeTime;
    void ShowReleaseProgress(DWORD dwProgress, CString strTips);
    DWORD GetRemoteConfigState();
    void StopRemoteConfig();
    CString m_csCtrlType;
    CProgressCtrl m_progressInsertPlay;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONPLAY_H__856E2359_D3BE_4AF6_977C_F16716FA0D15__INCLUDED_)
