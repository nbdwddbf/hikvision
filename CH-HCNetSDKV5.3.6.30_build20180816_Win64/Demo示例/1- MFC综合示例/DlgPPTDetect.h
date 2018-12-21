#if !defined(AFX_DLGPPTDETECT_H__52586689_FDF8_4A91_9A56_1559B1BF5C66__INCLUDED_)
#define AFX_DLGPPTDETECT_H__52586689_FDF8_4A91_9A56_1559B1BF5C66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPPTDetect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPPTDetect dialog

class CDlgPPTDetect : public CDialog
{
// Construction
public:
	CDlgPPTDetect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPPTDetect)
	enum { IDD = IDD_DLG_PPT_DETECT };
	CComboBox	m_comboChannel;
	BOOL	m_bPartScreen;
	BOOL	m_bPPTDetect;
	UINT	m_height;
	UINT	m_levelDetect;
	UINT	m_width;
	UINT	m_x;
	UINT	m_y;
    DWORD	m_dwChangePixelNum;
	//}}AFX_DATA

	int m_iDeviceIndex;
	LONG m_lLoginID;
	NET_DVR_PPT_DETECT_CFG m_struPPTDetectCfg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPPTDetect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPPTDetect)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPPTDETECT_H__52586689_FDF8_4A91_9A56_1559B1BF5C66__INCLUDED_)
