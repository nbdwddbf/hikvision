#if !defined(AFX_DLGLCDMATRIXSWITCH_H__4E950542_9705_47D4_91E3_3FFCAEBA22AA__INCLUDED_)
#define AFX_DLGLCDMATRIXSWITCH_H__4E950542_9705_47D4_91E3_3FFCAEBA22AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdMatrixSwitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdMatrixSwitch dialog

class CDlgLcdMatrixSwitch : public CDialog
{
// Construction
public:
	CDlgLcdMatrixSwitch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdMatrixSwitch)
	enum { IDD = IDD_DLG_LCD_MATRIX_SWITCH };
	CListCtrl	m_listIoRelation;
	DWORD	m_dwMatrixInput;
	DWORD	m_dwScreenIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdMatrixSwitch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdMatrixSwitch)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUpdate();
	afx_msg void OnBtnSwitch();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserId;
    int m_iDeviceIndex;
    DWORD m_dwMatrixId;
    NET_DVR_MATRIX_SWITCH_INFO m_struMatrixSwitchInfo;
    NET_DVR_IO_RELATION_INFO m_struMatrixIoRelation;

private:
    void DrawList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDMATRIXSWITCH_H__4E950542_9705_47D4_91E3_3FFCAEBA22AA__INCLUDED_)
