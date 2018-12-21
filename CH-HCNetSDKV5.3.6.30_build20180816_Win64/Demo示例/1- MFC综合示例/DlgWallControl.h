#if !defined(AFX_DLGWALLCONTROL_H__02956BCB_5FE7_4537_A9D4_F0AFA5A5AF82__INCLUDED_)
#define AFX_DLGWALLCONTROL_H__02956BCB_5FE7_4537_A9D4_F0AFA5A5AF82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWallControl dialog
#define BASEWIDTH 1920
#define BASEHEIGHT 1920
class CDlgWallControl : public CDialog
{
// Construction
public:
	CDlgWallControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallControl)
	enum { IDD = IDD_Dlg_VIDEOWALL_WALLCONTORL };
	CComboBox	m_CmColorType;
	CComboBox	m_CmWidth;
	CComboBox	m_CmWallNo;
	CComboBox	m_CmSerialPro;
	CComboBox	m_CmPosType;
	CComboBox	m_CmPosAjd;
	CComboBox	m_CmOperator;
	CComboBox	m_CmInputSource;
	CComboBox	m_CmHeight;
	CComboBox	m_CmColorAdj;
	BYTE	m_bySerialNo;
	DWORD	m_dwX;
	DWORD	m_dwY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnButWcontrolSet();
	afx_msg void OnSelchangeOperator();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    void    SetWallRange(BYTE byMax, BYTE byMin); 
    void    SetInitWallNo(BYTE byWallNo) { m_byWallNo = byWallNo; }
    void    InitVaildWallNo();                //初始化有效的墙号范围
    BOOL    UpdateControlStru(LPNET_DVR_SCREEN_CONTROL_V41 lpStru);        //更新界面内容到结构体

    LONG  m_lUserID;
	LONG  m_iDeviceIndex;
private:
    BYTE m_byWallNo;
    BYTE m_byMaxWallNo; 
    BYTE m_byMinWallNo; 

protected:

public:
    DWORD m_dwSubboard;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLCONTROL_H__02956BCB_5FE7_4537_A9D4_F0AFA5A5AF82__INCLUDED_)
