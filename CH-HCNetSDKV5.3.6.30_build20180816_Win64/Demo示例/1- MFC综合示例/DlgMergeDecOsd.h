#if !defined(AFX_DLGMERGEDECOSD_H__1FD3CA27_F84D_40EF_AF48_B54B7D27A363__INCLUDED_)
#define AFX_DLGMERGEDECOSD_H__1FD3CA27_F84D_40EF_AF48_B54B7D27A363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMergeDecOsd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDecOsd dialog

class CDlgMergeDecOsd : public CDialog
{
// Construction
public:
	CDlgMergeDecOsd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMergeDecOsd)
	enum { IDD = IDD_DLG_MERGE_DEV_OSD };
	CComboBox	m_cmbOSDColor;
	CComboBox	m_comboOutputNo;
	CComboBox	m_comboOsdNo;
	CComboBox	m_comboFontSize;
	BOOL	m_bShow;
	CString	m_csOsdContent;
	DWORD	m_dwX;
	DWORD	m_dwY;
	DWORD	m_dwOSDRed;
	DWORD	m_dwOSDGreen;
	DWORD	m_dwOSDBlue;
	DWORD	m_dwHeight;
	DWORD	m_dwWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMergeDecOsd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMergeDecOsd)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboOutputNo();
	afx_msg void OnSelchangeComboOsdNo();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    char m_szLan[64];

    NET_DVR_OUTPUT_OSD_CFG m_struOutputOsdCfg[16];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMERGEDECOSD_H__1FD3CA27_F84D_40EF_AF48_B54B7D27A363__INCLUDED_)
