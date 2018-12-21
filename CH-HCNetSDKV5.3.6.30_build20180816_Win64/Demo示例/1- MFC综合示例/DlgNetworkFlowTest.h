#if !defined(AFX_DLGNETWORKFLOWTEST_H__AFB4C12A_703D_471C_8042_5AF3BFA4A2B4__INCLUDED_)
#define AFX_DLGNETWORKFLOWTEST_H__AFB4C12A_703D_471C_8042_5AF3BFA4A2B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetworkFlowTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkFlowTest dialog

class CDlgNetworkFlowTest : public CDialog
{
// Construction
public:
	CDlgNetworkFlowTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetworkFlowTest)
	enum { IDD = IDD_DLG_NETWORK_FLOW_TEST };
	CComboBox	m_comboCardIndex;
	int		m_iInterval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetworkFlowTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetworkFlowTest)
	afx_msg void OnBtnFlowTest();
	afx_msg void OnBtnStopTest();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lServerID;
    int  m_iDevIndex;
    LONG m_lHandle;
    NET_DVR_FLOW_TEST_PARAM m_struFlowTestParam;
public:
    void SetFlowTestText(LPNET_DVR_FLOW_INFO pFlowInfo);
    LONG StartNetworkFlowTest(NET_DVR_FLOW_TEST_PARAM &sturFlowTestParam, FLOWTESTCALLBACK fFlowtestCallback, void* pUser);
    BOOL StopTest(LONG lHandle);
	void InitWnd();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETWORKFLOWTEST_H__AFB4C12A_703D_471C_8042_5AF3BFA4A2B4__INCLUDED_)
