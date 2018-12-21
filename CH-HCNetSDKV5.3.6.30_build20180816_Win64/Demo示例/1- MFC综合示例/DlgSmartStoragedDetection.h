#if !defined(AFX_DLGSMARTSTORAGEDDETECTION_H__14315925_0EA3_473F_9C66_DBDAFA573226__INCLUDED_)
#define AFX_DLGSMARTSTORAGEDDETECTION_H__14315925_0EA3_473F_9C66_DBDAFA573226__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSmartStoragedDetection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSmartStoragedDetection dialog

class CDlgSmartStoragedDetection : public CDialog
{
// Construction
public:
	CDlgSmartStoragedDetection(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSmartStoragedDetection)
	enum { IDD = IDD_DLG_SMART_STORAGEDETECTION };
	CComboBox	m_comSDCardState;
	CComboBox	m_comHealthState;
	BOOL	m_ChkEnable;
	DWORD	m_dwBadBlocks;
	CString	m_csPassWD;
    CString m_csUnlockPassWD;
	DWORD	m_dwAbnormalPowerLoss;
	CString	m_csOriginalPassWD;
    BYTE    m_byRemainingLife;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSmartStoragedDetection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSmartStoragedDetection)
	afx_msg void OnBtnGetStoragedetectionState();
	afx_msg void OnBtnGetStoragedetectionRwlock();
	afx_msg void OnBtnSetStoragedetectionRwlock();
    afx_msg void OnBtnSetStoragedetectionUnlock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lLoginID;
    INT  m_iDeviceIndex;
    LONG m_lChannel;
    
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSMARTSTORAGEDDETECTION_H__14315925_0EA3_473F_9C66_DBDAFA573226__INCLUDED_)
