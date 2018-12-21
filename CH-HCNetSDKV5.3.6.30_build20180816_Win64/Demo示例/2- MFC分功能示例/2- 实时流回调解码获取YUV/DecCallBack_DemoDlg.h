// DecCallBack_DemoDlg.h : header file
//

#if !defined(AFX_DECCALLBACK_DEMODLG_H__ECDDE6AD_247D_4895_B55A_F6BD7B32CB1D__INCLUDED_)
#define AFX_DECCALLBACK_DEMODLG_H__ECDDE6AD_247D_4895_B55A_F6BD7B32CB1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HCNetSDK.h"
#include "PlayM4.h"
/////////////////////////////////////////////////////////////////////////////
// CDecCallBack_DemoDlg dialog

class CDecCallBack_DemoDlg : public CDialog
{
// Construction
public:
	CDecCallBack_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDecCallBack_DemoDlg)
	enum { IDD = IDD_DECCALLBACK_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecCallBack_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDecCallBack_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONLogin();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonCapture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG lUserID;
	LONG llRealHandle;
	CComboBox n_Channel;
	NET_DVR_DEVICECFG m_struCfg;
	CStatic m_picplay;
	CBitmap m_cBackGround;
	CBitmap	m_cOverlay;
	short iPChannel;
	CIPAddressCtrl m_ctrlDeviceIP;
	CString m_csUserName;
	CString m_csPassword;
	short   m_nLoginPort;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECCALLBACK_DEMODLG_H__ECDDE6AD_247D_4895_B55A_F6BD7B32CB1D__INCLUDED_)
