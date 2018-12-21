#if !defined(AFX_DLGMATDECBIGSCRSPLICE_H__3FA5205D_10B4_4A4E_8EB1_1A14E29AA5B2__INCLUDED_)
#define AFX_DLGMATDECBIGSCRSPLICE_H__3FA5205D_10B4_4A4E_8EB1_1A14E29AA5B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMatDecBigScrSplice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMatDecBigScrSplice dialog

class CDlgMatDecBigScrSplice : public CDialog
{
// Construction
public:
	void SetBigScreenInfoToDlg();
	CDlgMatDecBigScrSplice(CWnd* pParent = NULL);   // standard constructor
    NET_DVR_MATRIX_ABILITY_V41 m_struMatrixDecAbility;
	int m_iDeviceIndex;
	NET_DVR_BIGSCREENCFG m_struBigScreenCfg;
// Dialog Data
	//{{AFX_DATA(CDlgMatDecBigScrSplice)
	enum { IDD = IDD_DLG_NETRABIGSCREEN };
	CComboBox	m_cmResolution;
	CComboBox	m_cmFormat;
	CComboBox	m_cmModeY;
	CComboBox	m_cmModeX;
	CComboBox	m_cmDecoderChanNum;
	CComboBox	m_cmScreenSeq;
	CComboBox	m_cmFollowScreenSeq;
	CComboBox	m_cmDispChanNum;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMatDecBigScrSplice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMatDecBigScrSplice)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnFollowscreenOk();
	afx_msg void OnSelchangeComboFollowscreenseq();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboScreenseq();
	//}}AFX_MSG
	void GetResolutionString(DWORD dwRes, char *lpResString);
	int m_iVGAResolutionNum;
	int m_iHDMIResolutionNum;
	int m_iDVIResolutionNum;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATDECBIGSCRSPLICE_H__3FA5205D_10B4_4A4E_8EB1_1A14E29AA5B2__INCLUDED_)
