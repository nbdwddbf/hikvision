#if !defined(AFX_DLGPOSFILTEREFFECT_H__6E68E89D_3BFA_4F50_9795_47A321151021__INCLUDED_)
#define AFX_DLGPOSFILTEREFFECT_H__6E68E89D_3BFA_4F50_9795_47A321151021__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPosFilterEffect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPosFilterEffect dialog

#define  MSG_PULL_TEST_EFFECT_RECEIVEDATA_SHOW WM_USER + 1007 

class CDlgPosFilterEffect : public CDialog
{
// Construction
public:
	CDlgPosFilterEffect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPosFilterEffect)
	enum { IDD = IDD_DLG_POS_FILTER_EFFECT };
	short	m_wPort;
	CString	m_csRecvData;
	CString	m_csFilterData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPosFilterEffect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPosFilterEffect)
	afx_msg void OnBtnStartRecvdata();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnChangeEffectDataShow(WPARAM wParam, LPARAM lParam);
public:
	void StartNetNakedDataListen();
	void StopNetNakedDataListen();
	CString GenericIgnoreStringInfo(CString strData);
	CString GenericEndStringInfo(CString strData);
	CString GenericNewLineInfo(CString strData);
	bool ParseHexString(char *strHex, int &nLen);
	char ConvertHexToChar(char *strHex, int nLen);
	int GetHexNumber(int n);

public:
	// critical section
	CRITICAL_SECTION m_stDataCritiacl;

	NET_DVR_POS_FILTER_CFG m_struFilterCfg;
	NET_DVR_NAKED_DATA_PARAM m_struNakedDataParam;
	LONG  m_lUserId;
	LONG m_lStartListenHandle;
	DWORD m_dwTheFilterNum;  // the num of select
	BOOL m_bStartListen;
	int m_iDevIndex;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSFILTEREFFECT_H__6E68E89D_3BFA_4F50_9795_47A321151021__INCLUDED_)
