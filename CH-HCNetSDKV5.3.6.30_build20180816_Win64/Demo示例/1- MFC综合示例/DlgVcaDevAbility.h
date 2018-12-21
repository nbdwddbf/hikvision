#if !defined(AFX_DLGVCADEVABILITY_H__5E4EB178_F2FF_4913_9FC3_191235B91123__INCLUDED_)
#define AFX_DLGVCADEVABILITY_H__5E4EB178_F2FF_4913_9FC3_191235B91123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaDevAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAbility dialog

class CDlgVcaDevAbility : public CDialog
{
// Construction
public:
	CDlgVcaDevAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaDevAbility)
	enum { IDD = IDD_DLG_VCA_DEV_ABILITY };
	int		m_iAtmChanNum;
	int		m_iVcaChanNum;
	int		m_iITSChanNum;
	int		m_iBBaseChanNum;
	int		m_iBFullChanNum;
	int		m_iBAdvanceChanNum;
	int		m_iPlateChanNum;
	int		m_iBPrisonChanNum;
	int     m_iTPSChanNum;
	int     m_iTFSChanNum;
	BOOL	m_bChkSupportChanEx;
	int		m_iPDCChanNum;
	int		m_iBPPerimeterChanNum;
	int		m_iFRecogChanNum;
	int		m_iFRetrievalChanNum;
	int		m_iFSnapChanNum;
	int		m_iFSnapBFullChanNum;
	int		m_iFSnapRecogChanNum;
	BOOL	m_bChkSupportIntelliTrack;
	int		m_iHeatMapChanNum;
	int		m_iSmartFaceDetectionChanNum;
	int		m_iSmartHeatMapChanNum;
	int		m_iSmartRoadDetectionChanNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaDevAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaDevAbility)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lServerID;
    int  m_iDevIndex;
    NET_VCA_DEV_ABILITY m_struVcaDevAbility;
    BOOL GetVcaDevAbility();
	void ShowAbility();
public:
	void UpdateWindowParam(LONG lDevIndex);
    int m_iEdcationStudentNum;
    int m_iHumanNum;
    int m_iRoadDetection;
    int m_iPersonDensityDetection;
    int m_iSafetyHelmetDetection;
    int m_iPerimeterCapture;
    int m_iHeelPDC;
    int m_i12MPLiveView;
    int m_iTeacherBehaviorDetectNum;
    int m_iMixedTargetDetection;
    int m_iFaceContrast;
    int m_iCityManagement;
    int m_iMixedTargetDetectionSmart;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADEVABILITY_H__5E4EB178_F2FF_4913_9FC3_191235B91123__INCLUDED_)
