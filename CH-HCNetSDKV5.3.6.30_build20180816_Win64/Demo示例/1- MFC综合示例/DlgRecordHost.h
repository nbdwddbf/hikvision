#if !defined(AFX_DLGRECORDHOST_H__A8F8EC3D_5767_4876_B685_57C654C7AA9C__INCLUDED_)
#define AFX_DLGRECORDHOST_H__A8F8EC3D_5767_4876_B685_57C654C7AA9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHost.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHost dialog

class DlgRecordHost : public CDialog
{
// Construction
public:
	DlgRecordHost(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRecordHost)
	enum { IDD = IDD_DLG_RECORD_HOST };
	int		m_nMirrorNum;
	UINT	m_nStartChannel;
	//}}AFX_DATA
	
	int m_iMirrorNum;
	int m_iStartChannel;
	LONG m_lServerID;
	int m_iDeviceIndex;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRecordHost)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgRecordHost)
	afx_msg void OnBtnRecordHostCfg();
	afx_msg void OnBtnSdiAutoTrack();
	afx_msg void OnBtnPublishCfg();
	afx_msg void OnBtnRecordControl();
	afx_msg void OnBtnGetEndTime();
	afx_msg void OnBtnPublish();
	afx_msg void OnBtnCourseCfg();
	afx_msg void OnBtnCurriculumCfg();
	afx_msg void OnBtnPptDetect();
    afx_msg void OnBtnBackupCfg();
	afx_msg void OnBtnRtmpCfg();
    afx_msg void OnBtnFilePublish();
    afx_msg void OnBtnFilmMode();
    afx_msg void OnBtnDirectStrategyCfg();
    afx_msg void OnBtnFrameCfg();
    afx_msg void OnBtnAudioEffectCfg();
    afx_msg void OnBtnBackgroundPicCfg();
	afx_msg void OnBtnVideoCfg();
	afx_msg void OnBtnGetRecordStatus();
	afx_msg void OnButtonGetCourseList();
	afx_msg void OnBtnImageDiffDetectionCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnClassdataStatistic();
	afx_msg void OnBnClickedBtnDirectedAdvanceCfg();
    afx_msg void OnBnClickedButtonVideoswitchconfig();
    afx_msg void OnBnClickedBtnEducationServerCfg();
    afx_msg void OnBnClickedBtnVideoTitleConfig();
    afx_msg void OnBnClickedBtnUploadLogo();
    afx_msg void OnBnClickedBtnPictureSwitchCtrl();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOST_H__A8F8EC3D_5767_4876_B685_57C654C7AA9C__INCLUDED_)
