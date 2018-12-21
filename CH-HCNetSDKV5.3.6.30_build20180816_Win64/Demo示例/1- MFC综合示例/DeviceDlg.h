#if !defined(AFX_DEVICEDLG_H__D50B20D8_564E_4F71_B23C_8D413C17F79D__INCLUDED_)
#define AFX_DEVICEDLG_H__D50B20D8_564E_4F71_B23C_8D413C17F79D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog

class CDeviceDlg : public CDialog
{
// Construction
public:
	CDeviceDlg(CWnd* pParent = NULL);   // standard constructor

    LONG m_lServerID;
	int  m_iDeviceIndex;
    BOOL GetDeviceParam();
    NET_DVR_NETCFG_V30 m_NetCfg;
    NET_DVR_DEVICECFG m_DeviceCfg;
// Dialog Data
	//{{AFX_DATA(CDeviceDlg)
	enum { IDD = IDD_DLG_SPLITTER_DEVICE_CFG };
	CComboBox	m_NetFaceCtrl;
	CString	m_strDeviceIp;
	CString	m_strDeviceName;
	CString	m_strDspSoftwareVersion;
	CString	m_strGateWayIp;
	DWORD	m_dwHttpPort;
	CString	m_strMaskIp;
	DWORD	m_dwMainPort;
	CString	m_strSerial;
	CString	m_strSoftwareVersion;
	CString	m_strMacIp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeviceDlg)
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEDLG_H__D50B20D8_564E_4F71_B23C_8D413C17F79D__INCLUDED_)
