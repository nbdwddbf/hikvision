#if !defined(AFX_DLGVCABASELINESCENE_H__2301BC9E_1241_4E1F_AC35_B5E9287C2BD2__INCLUDED_)
#define AFX_DLGVCABASELINESCENE_H__2301BC9E_1241_4E1F_AC35_B5E9287C2BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaBaselineScene.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBaselineScene dialog

class CDlgVcaBaselineScene : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaBaselineScene(CWnd* pParent = NULL);   // standard constructor
   
	enum DOWNLOAD_STATUS
	{
		DOWNLOAD_STATUS_FINISH = 1,
		DOWNLOAD_STATUS_PROCESSING = 2,
		DOWNLOAD_STATUS_FAILED = 3,
		DOWNLOAD_STATUS_NETWORK_ERROR = 4
	};
// Dialog Data
	//{{AFX_DATA(CDlgVcaBaselineScene)
	enum { IDD = IDD_DLG_VCA_BASELINE_SCENE };
	CProgressCtrl	m_ctrlDownloadProgress;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaBaselineScene)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaBaselineScene)
	afx_msg void OnBtnUpdateBaselineScene();
	afx_msg void OnBtnGetBaselineScenePic();
	afx_msg void OnBtnGetBaselineScene();
	afx_msg void OnBtnSetBaselineScene();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg LRESULT OnMsgDownloadFinished(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL GetBaseLineSceneCfg();
	BOOL SetBaseLineSceneCfg();
	BOOL UpdateBaseLineScene();
	void DownloadBaseLinePic();
	void LoadBaseLineWndContent();
	void SaveBaseLineWndContent();
private:
	NET_DVR_BASELINE_SCENE m_struBaselienScene;
	NET_DVR_CONTROL_BASELINE_SCENE_PARAM m_struCtrlBaselineSceneParam;
	LONG m_lDownloadHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCABASELINESCENE_H__2301BC9E_1241_4E1F_AC35_B5E9287C2BD2__INCLUDED_)
