#if !defined(AFX_DLGVCADETECTIONCFG_H__37C0B441_29DA_4333_944E_ACD9DA7E572D__INCLUDED_)
#define AFX_DLGVCADETECTIONCFG_H__37C0B441_29DA_4333_944E_ACD9DA7E572D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaDetectionCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDetectionCfg dialog

class CDlgVcaDetectionCfg : public CDialog
{
// Construction
public:
	CDlgVcaDetectionCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgVcaDetectionCfg();
// Dialog Data
	//{{AFX_DATA(CDlgVcaDetectionCfg)
	enum { IDD = IDD_DLG_VCA_DETECTION_CFG };
	CComboBox	m_cmbChannel;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaDetectionCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaDetectionCfg)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLinkage();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnPtz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
     void AddChanInfo();
     void GetPTZInfo();
     void UpdataPTZInfo();
public:
    LONG m_lUserID;
    int m_iDevIndex;
    LONG m_lChannel;

    NET_DVR_VCA_DETECTION_CFG_V40* m_pStruDetectionCfg;
    LPNET_DVR_ALARMINCFG_V40 m_pStruAlarmInCfgV40;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADETECTIONCFG_H__37C0B441_29DA_4333_944E_ACD9DA7E572D__INCLUDED_)
