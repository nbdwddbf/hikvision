#if !defined(AFX_DLGUNIFORMINTERFACE_H__31D90626_6AED_45E2_9CCC_6D14C557F0DA__INCLUDED_)
#define AFX_DLGUNIFORMINTERFACE_H__31D90626_6AED_45E2_9CCC_6D14C557F0DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUniformInterface.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUniformInterface dialog

class CDlgUniformInterface : public CDialog
{
// Construction
public:
	CDlgUniformInterface(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUniformInterface)
	enum { IDD = IDD_DLG_UNIFORM_INTERFACE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUniformInterface)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUniformInterface)
	afx_msg void OnBtnVideowallCreatewall();
	afx_msg void OnBtnSence();
	afx_msg void OnBtnPicPreview();
	afx_msg void OnBtnPic();
	afx_msg void OnBtnBasemap();
	afx_msg void OnBtnWallWinStatus();
	afx_msg void OnButVideowallElse();
	afx_msg void OnButVmAudiocfg();
	afx_msg void OnButVmGbt28181();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lServerID; 
	LONG m_iDeviceIndex; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUNIFORMINTERFACE_H__31D90626_6AED_45E2_9CCC_6D14C557F0DA__INCLUDED_)
