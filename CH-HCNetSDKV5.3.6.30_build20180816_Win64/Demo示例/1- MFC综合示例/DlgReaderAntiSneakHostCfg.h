#if !defined(AFX_DLGREADERANTISNEAKHOSTCFG_H__396A4349_59EB_4295_8E9D_E94503472A92__INCLUDED_)
#define AFX_DLGREADERANTISNEAKHOSTCFG_H__396A4349_59EB_4295_8E9D_E94503472A92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgReaderAntiSneakHostCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgReaderAntiSneakHostCfg dialog

class DlgReaderAntiSneakHostCfg : public CDialog
{
// Construction
public:
	DlgReaderAntiSneakHostCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgReaderAntiSneakHostCfg)
	enum { IDD = IDD_DLG_READER_ANTI_SNEAKZ_HOST_CFG };
    CComboBox	m_cmReaderCfg;
    CComboBox	m_cmSneakReaderInfo;
    BOOL    m_byEnable;
	int		m_byAntiSnealHostNo;
    int		m_wReaderID;
    int		m_byAntiSnealHostNoNext;
    int		m_wFollowUpCardReader;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgReaderAntiSneakHostCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int m_iDeviceIndex;
    long m_lUserID;
	NET_DVR_ANTI_SNEAK_MULTI_HOST_READERS_CFG m_struAntiSneakCfg;

	// Generated message map functions
	//{{AFX_MSG(DlgReaderAntiSneakHostCfg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeStruReaderCfg();
    afx_msg void OnSelchangeStruSneakReaderInfo();
    afx_msg void OnBtnSure();
    afx_msg void OnBtnSure2();
    afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREADERANTISNEAKHOSTCFG_H__396A4349_59EB_4295_8E9D_E94503472A92__INCLUDED_)
