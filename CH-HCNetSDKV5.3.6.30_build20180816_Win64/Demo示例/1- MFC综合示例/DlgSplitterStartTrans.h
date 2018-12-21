#if !defined(AFX_DLGSPLITTERSTARTTRANS_H__8156A120_9D74_464D_AA63_A9A6623C7555__INCLUDED_)
#define AFX_DLGSPLITTERSTARTTRANS_H__8156A120_9D74_464D_AA63_A9A6623C7555__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSplitterStartTrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitterStartTrans dialog

class CDlgSplitterStartTrans : public CDialog
{
// Construction
public:
	CDlgSplitterStartTrans(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSplitterStartTrans)
	enum { IDD = IDD_DLG_SPLITTER_START_TRANS };
	CListCtrl	m_listRecvData;
	CComboBox	m_comboChan;
	CComboBox	m_comboSerialType;
	CString	m_csData;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplitterStartTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplitterStartTrans)
	virtual BOOL OnInitDialog();	
	afx_msg void OnCreatechannel();
	afx_msg void OnDestroychannel();
	afx_msg void OnSelchangeComboSerialType();
	afx_msg void OnBtnSendData();
	afx_msg void OnBtnExit();
	afx_msg void OnClose();
	afx_msg void OnCancelMode();
	afx_msg void OnBtnSendDataAuto();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;    
    int     m_iDevIndex;
    LONG    m_lSerialHandle;
	DWORD   m_dwChan;
	void InitWnd();
    void InitSerialTypeCombo();
    void InitChannelCombo(int nChanNum);
    void InitRecvDataList();    
    BOOL AlarmHostSerialSend();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPLITTERSTARTTRANS_H__8156A120_9D74_464D_AA63_A9A6623C7555__INCLUDED_)
