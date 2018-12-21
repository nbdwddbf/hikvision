#if !defined(AFX_DLGPOSITIONTRACKCFG_H__785C0241_AF57_42B2_8BFA_E9426D14DF68__INCLUDED_)
#define AFX_DLGPOSITIONTRACKCFG_H__785C0241_AF57_42B2_8BFA_E9426D14DF68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPositionTrackCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPositionTrackCfg dialog

class CDlgPositionTrackCfg : public CDialog
{
// Construction
public:
	CDlgPositionTrackCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPositionTrackCfg)
	enum { IDD = IDD_DLG_POSITION_TRACKCFG };
	CComboBox	m_comboIndex;
	CComboBox	m_comboPositionID;
	CComboBox	m_comboPositionNum;
	int		m_iDwell;
	CComboBox   m_comboChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPositionTrackCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPositionTrackCfg)
	afx_msg void OnSelchangeComboPositionNum();
	afx_msg void OnBtnSetPositionTrack();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnConfirm();
	afx_msg void OnSelchangeComboIndex();
	afx_msg void OnBtnGetPositionTrack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL SetPositionTrackWnd();
    void InitComboIndex();
public:
    LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
    NET_DVR_POSITION_TRACK_CFG m_struPositionTrack;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSITIONTRACKCFG_H__785C0241_AF57_42B2_8BFA_E9426D14DF68__INCLUDED_)
