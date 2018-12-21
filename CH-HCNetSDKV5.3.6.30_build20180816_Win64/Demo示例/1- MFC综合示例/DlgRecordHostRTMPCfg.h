#if !defined(AFX_DLGRECORDHOSTRTMPCFG_H__931742C2_B985_442A_BC51_C58F8A397383__INCLUDED_)
#define AFX_DLGRECORDHOSTRTMPCFG_H__931742C2_B985_442A_BC51_C58F8A397383__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostRTMPCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostRTMPCfg dialog

class CDlgRecordHostRTMPCfg : public CDialog
{
// Construction
public:
	CDlgRecordHostRTMPCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostRTMPCfg)
	enum { IDD = IDD_DLG_RECORD_HOST_RTMP_CFG1 };
		// NOTE: the ClassWizard will add data members here
	CComboBox	m_comStreamType;
    CComboBox	m_comChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostRTMPCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL    m_bEnRTMP;
	DWORD   m_dwPacketLen;
	CString m_strRTMPURL;
	NET_DVR_RTMP_CFG m_struRTMPCfg;


    BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostRTMPCfg)
	afx_msg void OnBtnGet(); 
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;

    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTRTMPCFG_H__931742C2_B985_442A_BC51_C58F8A397383__INCLUDED_)
