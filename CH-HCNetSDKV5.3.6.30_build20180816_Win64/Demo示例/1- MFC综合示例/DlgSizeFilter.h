#if !defined(AFX_DLGSIZEFILTER_H__1B220D3D_AE9E_4884_AB8D_4E5D5B9049F1__INCLUDED_)
#define AFX_DLGSIZEFILTER_H__1B220D3D_AE9E_4884_AB8D_4E5D5B9049F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSizeFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSizeFilter dialog

class CDlgSizeFilter : public CDialog
{
// Construction
public:
	CDlgSizeFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSizeFilter)
	enum { IDD = IDD_DLG_SIZE_FILTER };
	CComboBox	m_comboMode;
	BOOL	m_bActive;
	float	m_fMaxHeight;
	float	m_fMaxWidth;
	float	m_fMinHeight;
	float	m_fMinWidth;
	BOOL	m_bSetMaxFilter;
	BOOL	m_bSetMiniFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSizeFilter)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSizeFilter)
	virtual void OnCancel();
	afx_msg void OnBtnSetSizeFilter();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboMode();
	afx_msg void OnChkActive();
	afx_msg void OnCheckSetMiniFilter();
	afx_msg void OnCheckSetMaxFilter();
	afx_msg void OnBtnPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
    NET_VCA_SIZE_FILTER m_struSizeFilter;

    BOOL m_bPreview;
    LONG m_lPlayHandle;
    CRect m_rcWnd;
    LONG    m_lPUServerID;
    NET_DVR_PU_STREAM_CFG m_struPuStream;
    int     m_nFilterMode;

    void InitWnd();
    LONG StartPlay();
    BOOL StopPlay();
    BOOL PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt);
    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSIZEFILTER_H__1B220D3D_AE9E_4884_AB8D_4E5D5B9049F1__INCLUDED_)
