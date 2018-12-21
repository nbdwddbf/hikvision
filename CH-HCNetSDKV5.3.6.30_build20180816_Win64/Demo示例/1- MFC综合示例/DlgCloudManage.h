#if !defined(AFX_DLGCLOUDMANAGE_H__34BAF85D_B4FB_4ECE_AA94_72C61A0D4D60__INCLUDED_)
#define AFX_DLGCLOUDMANAGE_H__34BAF85D_B4FB_4ECE_AA94_72C61A0D4D60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCloudManage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudManage dialog

class CDlgCloudManage : public CDialog
{
// Construction
public:
	CDlgCloudManage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCloudManage)
	enum { IDD = IDD_DLG_CLOUD_MANAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCloudManage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCloudManage)
	afx_msg void OnBtnCloudUrlCfg();
	afx_msg void OnBtnCloudCfg();
	afx_msg void OnBtnCloudUploadstrategyCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int m_lUserID;
    int m_lChanNo;
    int m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOUDMANAGE_H__34BAF85D_B4FB_4ECE_AA94_72C61A0D4D60__INCLUDED_)
