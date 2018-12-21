#if !defined(AFX_DLGPASSIVETRANSCODE_H__BB2689F9_70F8_41FD_97E8_0D4057476193__INCLUDED_)
#define AFX_DLGPASSIVETRANSCODE_H__BB2689F9_70F8_41FD_97E8_0D4057476193__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPassiveTransCode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPassiveTransCode dialog

#include "DlgPassiveWin.h"
#define MAX_PASSIVE_TRANS_NUM   128

class CDlgPassiveTransCode : public CDialog
{
// Construction
public:
	CDlgPassiveTransCode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPassiveTransCode)
	enum { IDD = IDD_DLG_PASSIVE_TRANS_CODE };
	CComboBox	m_comboSrcStreamType;
	CComboBox	m_comboCallBackType;
	CComboBox	m_comboStream;
	CComboBox	m_comboProtocol;
	CComboBox	m_comboGetStreamMode;
	CComboBox	m_comboDevChan;
	CComboBox	m_comboStreamType;	
	CComboBox	m_comboVideoBitrate;
	CComboBox	m_comboVEncType;
	CComboBox	m_comboResolution;
	CComboBox	m_comboPicQuality;
	CComboBox	m_comboFrameRate;
	CComboBox	m_comboFormatType;
	CComboBox	m_comboEncComplexity;
	CComboBox	m_comboCmpType;
	CComboBox	m_comboBPFrame;
	CComboBox	m_comboBitrateType;
	CComboBox	m_comboAEncType;
	DWORD	m_dwChannel;
	DWORD	m_dwIInterval;
	CString	m_csStreamId;
	DWORD	m_dwBitrate;
	BOOL	m_bChannel;
	CString	m_csDevIP;
	DWORD	m_dwPort;
	CString	m_csPassword;
	CString	m_csUserName;
	CString	m_csFilePath;
	DWORD	m_dwStreamSize;
	BOOL	m_bCycleRead;
	BOOL	m_bSaveFile;
	BOOL	m_bSavePreFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPassiveTransCode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPassiveTransCode)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStartPassiveTrans();
	afx_msg void OnSelchangeComboCmpType();
	afx_msg void OnChkChannel();
	afx_msg void OnBtnSendData();
	afx_msg void OnBtnStopPassiveTrans();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnDisp();
	afx_msg void OnBtnBrowse();
	afx_msg void OnDestroy();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDeviceIndex;
	int m_iSelCmpType;
	LONG m_lPassiveTransHandle/*[MAX_PASSIVE_TRANS_NUM]*/;
	LONG m_lDevUserID/*[MAX_PASSIVE_TRANS_NUM]*/;
	LONG m_lRealPlayHandle/*[MAX_PASSIVE_TRANS_NUM]*/;
	char m_pHead[100];    
    char m_pFileData[100]; //保存文件的头40字节
	HANDLE m_hSendEvent;
	HANDLE m_hHeadGetEvent;
	HANDLE m_hExitFileThread;
	NET_DVR_STREAM_INFO m_struStreamInfo;
	NET_DVR_PASSIVETRANSINFO m_struPassiveTransInfo;
	NET_DVR_COMPRESSIONCFG_V30 m_struCmpCfgV30;
	NET_DVR_COMPRESSIONCFG_ABILITY m_struCompressionCfgAblity;
	char m_pSdpInfo[2 * 1024];
	CDlgPassiveWin m_dlgDisp;
	HANDLE m_hFile;
	HANDLE m_hFilePre;

	HANDLE m_hSrcFile;
	HANDLE m_hFileThread;
	BOOL m_bNeedSendAgain;
	BOOL m_bGbStream;
	DWORD m_dwStreamType;

	void InsertMainResolution();
	void InsertSubResolution();
	void InsertFrame();
	void InsertBitrateType();
	void InsertBitrate();
	void InsertStreamType();
	void InsertPicQuality();
	void InsertBpFrame();
	void InsertVideoEnc();
	void InsertAudioEnc();
	void InsertVEncComplexity();
	void InsertFormatType();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPASSIVETRANSCODE_H__BB2689F9_70F8_41FD_97E8_0D4057476193__INCLUDED_)
