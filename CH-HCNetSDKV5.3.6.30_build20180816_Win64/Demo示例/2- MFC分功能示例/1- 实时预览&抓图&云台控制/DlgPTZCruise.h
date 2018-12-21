#if !defined(AFX_DLGPTZCRUISE_H__8C5EEE22_BD56_413F_8ECB_18686CC9103E__INCLUDED_)
#define AFX_DLGPTZCRUISE_H__8C5EEE22_BD56_413F_8ECB_18686CC9103E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPTZCruise.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPTZCruise dialog

class CDlgPTZCruise : public CDialog
{
// Construction
public:
	BOOL Set_NET_DVR_PTZCruise(int iChanIndex, DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput);
	CDlgPTZCruise(CWnd* pParent = NULL);   // standard constructor

public:
	int m_iCruiseNum;
	int m_iSeqPoint;
	int m_iPresetNum;
	int m_iSeqDwell;//time interval
	int m_iSeqSpeed;
	int m_iChanNum;       //通道号，不是通道索引
// Dialog Data
	//{{AFX_DATA(CDlgPTZCruise)
	enum { IDD = IDD_DLG_PTZ_CRUISE };
	CComboBox m_comboSeqPreset;
	CComboBox m_comboSeqTime;
	CComboBox m_comboSeqSpeed;
	CComboBox m_comboPoint;
	CComboBox m_comboCruiseRoute;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPTZCruise)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPTZCruise)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZCRUISE_H__8C5EEE22_BD56_413F_8ECB_18686CC9103E__INCLUDED_)
