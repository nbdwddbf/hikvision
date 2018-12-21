#if !defined(AFX_DLGACSPHONEDOORRIGHTCFG_H__5251E060_3171_45FB_BC33_B19EA1240D28__INCLUDED_)
#define AFX_DLGACSPHONEDOORRIGHTCFG_H__5251E060_3171_45FB_BC33_B19EA1240D28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsPhoneDoorRightCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAcsPhoneDoorRightCfg dialog

class DlgAcsPhoneDoorRightCfg : public CDialog
{
// Construction
public:
	DlgAcsPhoneDoorRightCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAcsPhoneDoorRightCfg)
	enum { IDD = IDD_DLG_ACS_PHONE_DOOR_RIGHT_CFG };
    CTreeCtrl	m_treeOpen;
    CTreeCtrl	m_treeClose;
    CTreeCtrl	m_treeNormalOpen;
    CTreeCtrl	m_treeNormalClose;
    CTreeCtrl	m_treeArm;
    CTreeCtrl	m_treeDisArm;
    CComboBox	m_comboChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAcsPhoneDoorRightCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAcsPhoneDoorRightCfg)
    virtual BOOL OnInitDialog();
    afx_msg void OnBtnSet();
    afx_msg void OnBtnGet();
    afx_msg void OnClickTreeOpen(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeClose(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeNormalOpen(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeNormalClose(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeArm(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeDisArm(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    NET_DVR_PHONE_DOOR_RIGHT_CFG m_struPhoneDoorRightCfg;
    
private:
    void CreateTree();
    void GetTreeSel(); 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSPHONEDOORRIGHTCFG_H__5251E060_3171_45FB_BC33_B19EA1240D28__INCLUDED_)
