// SerialTransDlg.h : header file
//

#if !defined(AFX_SERIALTRANSDLG_H__52949285_99B6_4B1A_A2A0_842D1930650D__INCLUDED_)
#define AFX_SERIALTRANSDLG_H__52949285_99B6_4B1A_A2A0_842D1930650D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GeneralDef.h"
#include <Afxmt.h>



/////////////////////////////////////////////////////////////////////////////
// CSerialTransDlg dialog

class CSerialTransDlg : public CDialog
{
// Construction
public:
	CSerialTransDlg(CWnd* pParent = NULL);	// standard constructor

public:
	BOOL m_bIsSending;
	int m_iCurSerialType;
	int m_iSerialChan;
	int m_iCurInterface;      //发送接口，0-长连接，需建立透明通道  1-不需要建立透明通道
	BOOL DoLogin();
	BOOL m_bIsLogin;
	LONG m_lSerialHandle;
	LOCAL_DEVICE_INFO m_struDeviceInfo;
	char m_DataBuf[DATABUF_LEN];
	int m_DataLen;
// Dialog Data
	//{{AFX_DATA(CSerialTransDlg)
	enum { IDD = IDD_SERIALTRANS_DIALOG };
	CListCtrl	m_RecvDataList;
	CComboBox	m_comboInterface;
	CComboBox	m_comboChan;
	CComboBox	m_comboSerialType;
	CIPAddressCtrl	m_ctrlDevIp;
	UINT	m_nDevPort;
	CString	m_csUser;
	CString	m_csPWD;
	CString	m_csDataSend;
	UINT	m_iSendInterval;
	BOOL	m_bSendContinual;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSerialTransDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLogin();
	afx_msg void OnSelchangeComboSerialType();
	afx_msg void OnButtonSerialstart();
	afx_msg void OnButtonSend();
	afx_msg void OnSelchangeComboChan();
	afx_msg void OnButtonSerialstop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALTRANSDLG_H__52949285_99B6_4B1A_A2A0_842D1930650D__INCLUDED_)
