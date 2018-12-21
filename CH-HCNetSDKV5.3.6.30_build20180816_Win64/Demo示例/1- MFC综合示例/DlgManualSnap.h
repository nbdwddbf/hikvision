#if !defined(AFX_DLGMANUALSNAP_H__A28A9B0A_3D6B_44D8_8EDC_E5D3AD511092__INCLUDED_)
#define AFX_DLGMANUALSNAP_H__A28A9B0A_3D6B_44D8_8EDC_E5D3AD511092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgManualSnap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgManualSnap dialog

class CDlgManualSnap : public CDialog
{
// Construction
public:
	CDlgManualSnap(CWnd* pParent = NULL);   // standard constructor
	~CDlgManualSnap();
// Dialog Data
	//{{AFX_DATA(CDlgManualSnap)
	enum { IDD = IDD_DLG_MANUAL_SNAP };
	CComboBox	m_comSnapTimes;
	CComboBox	m_comVehicleColor;
	CListCtrl	m_RealtimeList;
	BOOL	m_bOSDClose;
	int		m_iVehicleIndex;
	CString	m_csTrafficLight;
	BYTE	m_byLaneNo;
	DWORD	m_dwSnapWaitTime;
	DWORD	m_dwIntervalTime1;
	DWORD	m_dwIntervalTime2;
	DWORD	m_dwIntervalTime3;
	DWORD	m_dwIntervalTime4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManualSnap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManualSnap)
	afx_msg void OnBtnManualSnap();
	afx_msg void OnBtnPTZCtrl();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnContinuousShoot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CRect       m_rcWndRect;   //预览窗口大小
    BOOL        m_bCloseIn;
	LONG        m_lServerID; // 用户ID
    int         m_iDevIndex; // 设备索引
	LONG        m_lChannel;
	LONG        m_lPlayHandle;
	NET_DVR_MANUALSNAP m_struManualSnap;
    NET_DVR_PLATE_RESULT m_struResult;

	long StartRealPlay();  // 开始预览 
    BOOL StopRealPlay();  // 停止预览
    int m_iChannelID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANUALSNAP_H__A28A9B0A_3D6B_44D8_8EDC_E5D3AD511092__INCLUDED_)
