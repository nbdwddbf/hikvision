#if !defined(AFX_TRANSPARENTTRANS_H__F0CB67F8_60CB_4DD3_A447_B00D8B02B3CB__INCLUDED_)
#define AFX_TRANSPARENTTRANS_H__F0CB67F8_60CB_4DD3_A447_B00D8B02B3CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransparentTrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransparentTrans dialog

class CTransparentTrans : public CDialog
{
// Construction
public:
	CTransparentTrans(CWnd* pParent = NULL);   // standard constructor
	int m_iDeviceIndex;
	int	m_iChanCount;//preview channel number
	LONG m_lStartChannel;//NET_DVR_DECODERCFG
	int m_iSelSerialIndex;
	LONG m_lServerID;
	LONG m_lSerialChan;
	LONG m_lSerialID;
// Dialog Data
	//{{AFX_DATA(CTransparentTrans)
	enum { IDD = IDD_DLG_SERIAL_TRANSPARENT };
	CComboBox	m_comboSend;
	CComboBox	m_comboSerialType;
	CComboBox	m_comboChan;
	CListCtrl	m_RecvDataList;
	CString	m_csContent;
	UINT	m_dwSerialNo;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentTrans)
	virtual BOOL OnInitDialog();
	afx_msg void OnCreatechannel();
	afx_msg void OnDestroychannel();
	afx_msg void OnSenddata();
	afx_msg void OnSelchangeComboSerialType();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void EnableControl(BOOL bEnable);
	NET_DVR_TRIAL_SYSTEM_INFO m_struSystemInfo;
    BOOL  m_bIsTrial; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTTRANS_H__F0CB67F8_60CB_4DD3_A447_B00D8B02B3CB__INCLUDED_)
