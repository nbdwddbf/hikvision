#if !defined(AFX_DLGZEROCHANCFG_H__0203D6FE_BCAD_49F4_A8EF_7CA2E4D39497__INCLUDED_)
#define AFX_DLGZEROCHANCFG_H__0203D6FE_BCAD_49F4_A8EF_7CA2E4D39497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgZeroChanCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgZeroChanCfg dialog

class CDlgZeroChanCfg : public CDialog
{
// Construction
public:
	CDlgZeroChanCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgZeroChanCfg)
	enum { IDD = IDD_SUB_DLG_ZEROCHAN_CFG };
	CComboBox	m_comboPreviewType;
	CComboBox	m_comboFrameRate;
	CComboBox	m_comboBitRate;
	int	    	m_iBitRate;
	BOOL    	m_bEnableZeroChanCfg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgZeroChanCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgZeroChanCfg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChkZerochancfg();
	afx_msg void OnSelchangeComboMaxBitRate();
	afx_msg void OnBtnPreviewcfg();
	afx_msg void OnButtonPreviewSwitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: // fun
    void EnableZeroChanCfg(BOOL bEnable);
    void  CurCfgUpdate();
    BOOL CheckInitParam();
public: // mem
    NET_DVR_ZEROCHANCFG    m_struZeroChanCfg;   
    NET_DVR_ZERO_ZOOMCFG   m_struZeroZoomCfg;  
    NET_DVR_PREVIEWCFG_V30 m_struMainPreviewCfg;
    NET_DVR_PREVIEWCFG_V30 m_struAuxPreviewCfg;
    int     m_iDevIndex;
    long    m_lServerID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGZEROCHANCFG_H__0203D6FE_BCAD_49F4_A8EF_7CA2E4D39497__INCLUDED_)
