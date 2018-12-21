#if !defined(AFX_DLGACSCASESENSOR_H__44408C4E_5BFC_47E1_8CFC_1D722EE11B24__INCLUDED_)
#define AFX_DLGACSCASESENSOR_H__44408C4E_5BFC_47E1_8CFC_1D722EE11B24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsCaseSensor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAcsCaseSensor dialog

class CDlgAcsCaseSensor : public CDialog
{
// Construction
public:
	CDlgAcsCaseSensor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAcsCaseSensor)
	enum { IDD = IDD_DLG_ACS_CASE_SENSOR };
	CTreeCtrl	m_treeDoorOpen;
	CTreeCtrl	m_treeDoorClose;
	CTreeCtrl	m_treeCardReaderBuzzer;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_comboCaseSensorNo;
	BOOL	m_bHostBuzzer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAcsCaseSensor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAcsCaseSensor)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnClickTreeCardReaderBuzzer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeDoorOpen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeDoorClose(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    NET_DVR_CASE_SENSOR_CFG m_struCaseSensorCfg[MAX_CASE_SENSOR_NUM];

private:
    void CreateTree();

private:
    void GetTreeSel(); 

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSCASESENSOR_H__44408C4E_5BFC_47E1_8CFC_1D722EE11B24__INCLUDED_)
