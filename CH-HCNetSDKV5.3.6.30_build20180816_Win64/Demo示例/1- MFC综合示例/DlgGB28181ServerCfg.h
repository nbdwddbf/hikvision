#if !defined(AFX_DLGGB28181SERVERCFG_H__5D8B4F57_2AC1_40E1_9579_05C1B03D87B5__INCLUDED_)
#define AFX_DLGGB28181SERVERCFG_H__5D8B4F57_2AC1_40E1_9579_05C1B03D87B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGB28181ServerCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGB28181ServerCfg dialog

class CDlgGB28181ServerCfg : public CDialog
{
// Construction
public:
	CDlgGB28181ServerCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGB28181ServerCfg)
	enum { IDD = IDD_DLG_GB28181_SERVER };
	CString	m_csPasswd;
	UINT	m_dwTimes;
	short	m_wPort;
	UINT	m_dwRegisterValid;
	CString	m_csServerID;
    BOOL    m_bAutoAddIpc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGB28181ServerCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGB28181ServerCfg)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    int m_iDevIndex;
private:
    NET_DVR_GB28181_SERVICE_CFG m_struServerCfg;
      char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGB28181SERVERCFG_H__5D8B4F57_2AC1_40E1_9579_05C1B03D87B5__INCLUDED_)
