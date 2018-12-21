#if !defined(AFX_DLGLITESTORAGE_H__20C4AC76_E8E9_4905_A2D7_A83957F4AB55__INCLUDED_)
#define AFX_DLGLITESTORAGE_H__20C4AC76_E8E9_4905_A2D7_A83957F4AB55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLiteStorage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLiteStorage dialog

class CDlgLiteStorage : public CDialog
{
// Construction
public:
	CDlgLiteStorage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLiteStorage)
	enum { IDD = IDD_DLG_LITESTORAGE11 };
	BOOL	m_bEnable;
	float	m_fCapacity;
	int		m_iStorageTime;
    CComboBox	m_comboLevel;
    int		m_iStorageTimeLow;
    int		m_iStorageTimeMedium;
    int		m_iStorageTimeHigh;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLiteStorage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLiteStorage)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lChannel;
    LONG m_lLoginID;
    NET_DVR_LITESTORAGE m_strLiteStorage;
    int m_iDeviceIndex;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLITESTORAGE_H__20C4AC76_E8E9_4905_A2D7_A83957F4AB55__INCLUDED_)
