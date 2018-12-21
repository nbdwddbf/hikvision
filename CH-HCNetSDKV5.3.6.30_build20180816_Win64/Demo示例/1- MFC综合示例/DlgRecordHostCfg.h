#if !defined(AFX_DLGRECORDHOSTCFG_H__B3CCD31D_EB37_42BF_987B_69B3F7CF779E__INCLUDED_)
#define AFX_DLGRECORDHOSTCFG_H__B3CCD31D_EB37_42BF_987B_69B3F7CF779E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostCfg dialog

class DlgRecordHostCfg : public CDialog
{
// Construction
public:
	DlgRecordHostCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRecordHostCfg)
	enum { IDD = IDD_DLG_RECORD_HOST_CFG };
	CComboBox	m_comRecordType;
	UINT	m_DelayTime;
    int		m_iChannel;
    int		m_iPicStayTime;
    int		m_iTVScreenNo;
	//}}AFX_DATA
	LONG m_lUserID;
	int m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRecordHostCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	NET_DVR_RECORDING_HOST_CFG m_struRecordHostCfg;

	
// Implementation
protected:
	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgRecordHostCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
    afx_msg void OnBtnTv();
    afx_msg void OnBtnTvGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bCourseDataStorageEnabled;
    int m_iStatureLowerLimit;
    afx_msg void OnBnClickedButtonGetHumanInfo();
    afx_msg void OnBnClickedButtonSetHumanInfo();
    BOOL CreateHumanInfoCfg(char* pBuf, DWORD dwBufLen, int &dwRet);
    BOOL m_bElectronicEnlargeMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTCFG_H__B3CCD31D_EB37_42BF_987B_69B3F7CF779E__INCLUDED_)
