#if !defined(AFX_DLGAREAMASKCFG_H__F6BF7EC3_514E_4B74_9EC2_A26910E0B803__INCLUDED_)
#define AFX_DLGAREAMASKCFG_H__F6BF7EC3_514E_4B74_9EC2_A26910E0B803__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAreaMaskCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAreaMaskCfg dialog


class CDlgAreaMaskCfg : public CDialog
{
// Construction
public:
	CDlgAreaMaskCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

	LONG m_lPlayHandle;
	void DrawRgnFun(HDC hdc);

// Dialog Data
	//{{AFX_DATA(CDlgAreaMaskCfg)
	enum { IDD = IDD_DLG_AREA_MASK_CFG };
	CComboBox	m_cmbChan;
	CStatic	m_picAreaMask;
	CComboBox	m_cmbMaskThick;
	BOOL	m_bChkEnableMask;
	BOOL	m_bChkMaskShow;
	BOOL	m_bChkMaskSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAreaMaskCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAreaMaskCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedChkMaskShow();
	afx_msg void OnBnClickedChkMaskSet();
	afx_msg void OnSelchangeCmbChan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bDrawdetect;
	
	CRect m_rcPlayWnd;
	int m_nCurDrawType;
	int m_nDrawPointNum;
private:
    void OnStartPlay();
    void OnStopPlay();
public:
    BOOL m_bAutoMask;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAREAMASKCFG_H__F6BF7EC3_514E_4B74_9EC2_A26910E0B803__INCLUDED_)
