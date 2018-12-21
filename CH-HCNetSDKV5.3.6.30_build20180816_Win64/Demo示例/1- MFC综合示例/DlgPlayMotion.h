#if !defined(AFX_DLGPLAYMOTION_H__F1C33271_6554_417D_A0FA_57D824B56848__INCLUDED_)
#define AFX_DLGPLAYMOTION_H__F1C33271_6554_417D_A0FA_57D824B56848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlayMotion.h : header file
//
#include "plaympeg4.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPlayMotion dialog
#define MOTION_NUM 4
class CDlgPlayMotion : public CDialog
{
// Construction
public:
	CDlgPlayMotion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPlayMotion)
	enum { IDD = IDD_DLG_PLAY_MOTION };
	CComboBox	m_cmbSex;
	CComboBox	m_cmbAdvance;
	CComboBox	m_cmbEyeGlass;
	CComboBox	m_cmbColorRate;
	CComboBox	m_cmbColorR;
	CComboBox	m_cmbColorG;
	CComboBox	m_cmbColorB;
	CComboBox	m_cmbAge;
	CComboBox	m_cmbIntrusionCurArea;
	CComboBox	m_cmbCurArea;
	CComboBox	m_cmbTraversePlaneDirction;
	CComboBox	m_cmbSearchType;
	CListCtrl	m_listMotionTime;
	CComboBox	m_comboSearchSense;
	CTime	m_ctDateStart;
	CTime	m_ctDateStop;
	CTime	m_ctTimeStart;
	CTime	m_ctTimeStop;
	int		m_iTime;
	UINT	m_dwIntrusionDuration;
	UINT	m_dwIntrusionRate;
	UINT	m_dwIntrusionSensitivity;
	UINT	m_dwTravesePlaneSensitivity;
	UINT	m_dwTraversePlanePreTime;
	UINT	m_dwTraversePlaneDelayTime;
	UINT	m_dwIntrusionPreTime;
	UINT	m_dwIntrusionDelayTime;
	float	m_fPanPos;
	float	m_fTitlePos;
	float	m_fZoomPos;
	CString	m_csStreamID;
	CComboBox	m_cmbRelatedChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlayMotion)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlayMotion)
	afx_msg void OnBtnMotionSearch();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPreview();
	afx_msg void OnClickListMotionTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListMotionTime(NMHDR* pNMHDR, LRESULT* pResult);
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnSelchangeComboSearchType();
	afx_msg void OnBtnClearpic();
	afx_msg void OnBtnGetPtz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CRect   m_rcWnd;
    LONG    m_lChannel;
    LONG    m_lServerID;
    int     m_iDevIndex;
    NET_DVR_SMART_SEARCH_PARAM_V40 m_struSmartSearchV40; 
    LONG    m_lSearchHandle;
    NET_VCA_RECT m_struRect[MOTION_NUM];
    LONG    m_lRealPlayHandle;
    BOOL    m_bMouseMove[MOTION_NUM];
    BOOL    m_bDrawed[MOTION_NUM];
	BOOL    m_bMouseMoveTranverse;
    BOOL    m_bDrawedTranverse;
    HANDLE m_hFindThread;
    int     m_iDrawingIndex;
    int     m_iPreviewState;    
    LONG    m_lPlayBackHandle;
    NET_DVR_TIME m_struStartTime;
    NET_DVR_TIME m_struStopTime;
    int  m_iItemSel;
	DWORD  m_dwSearchType;
    //保存当前的索引值
    int m_iLineNo;
	int m_iFieldNo;
	
    DWORD m_dwPosNum; 
    BOOL m_bCloseIn;
    BOOL m_bMouseMovePolygon;
    
public:
    long StartPlay();

    BOOL StopPlay();
    void SetParentWnd(HWND *hhWnd, int iParentNum);
    BOOL CheckInitParam();
    void BtnRemoteFileStop();
    void BtnRemotFilePlay();
    void PlayBack();
    void StopPlayBack();
	void ShowSetInfo(DWORD dwSearchType);
    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	
    BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);
	BOOL PreDrawLineMsg(MSG* pMsg, CPoint &pt);
    BOOL PreDrawMotionMsg(MSG* pMsg, CPoint &pt1);
    void CleanMotionPic();
    void AddHumanFeatureInfo();
    void AddObjectIFeatureInfo();
protected:
    void F_DrawMotion(HDC hDc);
    void F_DrawLine(HDC hDc);
	void F_DrawPolygon(HDC hDc);
    PTZ_INFO m_struPTZInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYMOTION_H__F1C33271_6554_417D_A0FA_57D824B56848__INCLUDED_)
