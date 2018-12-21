#if !defined(AFX_DLGDECWINSTATUS_H__4369AFB5_8FB5_4672_BFB6_047821A86290__INCLUDED_)
#define AFX_DLGDECWINSTATUS_H__4369AFB5_8FB5_4672_BFB6_047821A86290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDecWinStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDecWinStatus dialog

class CDlgDecWinStatus : public CDialog
{
// Construction
public:
	CDlgDecWinStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDecWinStatus)
	enum { IDD = IDD_DLG_DEC_WIN_STATUS };
	CComboBox	m_comboStreamType;
	CComboBox	m_comboPackType;
	CComboBox	m_comboDecEnable;
	DWORD	m_dwAFrameNum;
	BYTE	m_byAFrameRate;
	DWORD	m_wPicHeight;
	DWORD	m_wPicWidth;
	DWORD	m_dwSubWinNum;
	DWORD	m_dwVFrameNum;
	BYTE	m_byVFrameRate;
	DWORD	m_dwWinNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDecWinStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDecWinStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUpdate();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_WALLWIN_INFO m_struWallWinInfo;
	NET_DVR_WALL_WIN_STATUS m_struWallWinStatus; 
	void ShowData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDECWINSTATUS_H__4369AFB5_8FB5_4672_BFB6_047821A86290__INCLUDED_)
