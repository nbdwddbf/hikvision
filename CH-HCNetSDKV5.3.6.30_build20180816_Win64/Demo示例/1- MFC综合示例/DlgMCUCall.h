#include "afxwin.h"
#if !defined(AFX_DLGMCUCALL_H__A10583B8_AC37_4319_9569_C84A32B3911D__INCLUDED_)
#define AFX_DLGMCUCALL_H__A10583B8_AC37_4319_9569_C84A32B3911D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUCall.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUCall dialog
#define MAX_COUNT    256
class CDlgMCUCall : public CDialog
{
// Construction
public:
	CDlgMCUCall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMCUCall)
	enum { IDD = IDD_DLG_MCU_CALL };
	CListCtrl	m_lstResult;
	CComboBox	m_cmbCallType;
	CComboBox	m_cmbProtoType;
	CComboBox	m_cmbAnswerType;
	CComboBox	m_cmbOperateType;
	CString	m_csTerminalUrl;
	BYTE	m_byVolumn;
	BOOL	m_chkMute;
	BOOL	m_DisableAudioInput;
	CString	m_csSearchID;
	DWORD	m_dwMaxCount;
	DWORD	m_dwSearchPos;
	CTime	m_dtStart;
	CTime	m_dtStop;
	CTime	m_tStart;
	CTime	m_tStop;
	CString	m_csResultStatus;
	BYTE	m_byVolumeIn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUCall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUCall)
	afx_msg void OnButControlSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnButCallcfgGet();
	afx_msg void OnButCallcfgSet();
	afx_msg void OnButCallcfgQuery();
	afx_msg LRESULT AddList(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	 

	
private:
	LONG m_lUserID;
	LONG m_iDeviceIndex;
	BYTE m_byResultSearchID[MAX_SEARCH_ID_LEN]; //ËÑË÷±êÊ¶·û 
	CWinThread* m_pProcThread; 
	NET_DVR_CALL_QUERY_COND m_struQueryCond; 
	NET_DVR_CALL_QUERY_SINGLE m_struQuerySingle[MAX_COUNT]; 
	NET_DVR_CALL_QUERY_SINGLE m_struQuerySingleForDraw[MAX_COUNT]; 
	NET_DVR_CALL_QUERY_RESULT m_struQueryResult; 
public:
	void DrawList(const NET_DVR_CALL_QUERY_RESULT &struQueryResult, BOOL bRedraw=TRUE); 
	void QueryNextResult();
	DWORD m_dwChannel;
	CComboBox m_ctrlGainType;
	BOOL m_bSimulate;
	BOOL m_bDigital;
	DWORD m_dwSimulate;
	DWORD m_dwDigital;
	CString m_csGainType;
	BOOL m_bHMS;
	DWORD m_dwSity;
	DWORD m_HMSTime;
	CComboBox m_cmbHMSType;
    int m_CallRate;
    CComboBox m_comboTransmissionProtocol;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUCALL_H__A10583B8_AC37_4319_9569_C84A32B3911D__INCLUDED_)
