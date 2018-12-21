#if !defined(AFX_DLGLCDSERIAL_H__962853ED_4045_4D12_9FD2_2AE6C12B5DD0__INCLUDED_)
#define AFX_DLGLCDSERIAL_H__962853ED_4045_4D12_9FD2_2AE6C12B5DD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdSerial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSerial dialog

class CDlgLcdSerial : public CDialog
{
// Construction
public:
	CDlgLcdSerial(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdSerial)
	enum { IDD = IDD_DLG_LCD_SERIAL };
	CComboBox	m_comboSerialProtocol;
	CComboBox	m_comboDistSerialSet;
	DWORD	m_dwCurrentSerial;
	BYTE	m_bySerialNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdSerial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdSerial)
	virtual BOOL OnInitDialog();
	afx_msg void OnButDistSerialGet();
	afx_msg void OnButDistCurrentserialGet();
	afx_msg void OnButDistCurrentserialSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserId;
    int m_iDeviceIndex;
    NET_DVR_SERIAL_CONTROL m_struSerialCtrl;
    NET_DVR_USING_SERIALPORT m_struUsingSerialPort;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDSERIAL_H__962853ED_4045_4D12_9FD2_2AE6C12B5DD0__INCLUDED_)
