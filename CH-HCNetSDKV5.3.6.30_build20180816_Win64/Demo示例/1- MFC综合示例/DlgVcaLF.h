#if !defined(AFX_DLGVCALF_H__E986C18F_2D67_4FE6_BD01_39224C548FA8__INCLUDED_)
#define AFX_DLGVCALF_H__E986C18F_2D67_4FE6_BD01_39224C548FA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaLF.h : header file
//
#include "PTZButton1.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaLF dialog

class CDlgVcaLF : public CDialog
{
// Construction
public:
	CDlgVcaLF(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaLF)
	enum { IDD = IDD_DLG_VCA_LF };
	CComboBox	m_comboCalPointNum;
	CComboBox	m_comboPointIndex;
	float	m_fCurVcaPointX;
	float	m_fCurVcaPointY;
	BOOL	m_bLFEnable;
	UINT	m_iFollowChan;
	UINT	m_iMainChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaLF)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaLF)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnCancel();
	afx_msg void OnSelchangeComboPointIndex();
	afx_msg void OnBtnAddCalPoint();
	afx_msg void OnSelchangeComboCalPointNum();
	afx_msg void OnCheckLfEnable();
	afx_msg void OnRadioManualCtrl();
	afx_msg void OnRadioAlarmTrack();
	afx_msg void OnRadioTargetTrack();
	afx_msg void OnBtnLfCfg();
	afx_msg void OnBtnPreview();
	afx_msg void OnBtnPreview2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long	m_lServerID;	
	int		m_iDevIndex;	

	int		m_iVcaChannel;
	int		m_iLFChannel;
	long	m_lPlayHandle1;
	long	m_lPlayHandle2;
	CRect	m_rect1;
	CRect	m_rect2;
	
	NET_DVR_TRACK_MODE m_struLFTrackMode;
	NET_DVR_TRACK_CFG m_struLFCfg;
	NET_DVR_CB_POINT m_struCurCBPPoint;
    NET_DVR_PU_STREAM_CFG m_struPUStream;
   
    LONG    m_lPUMainServerID;
    LONG    m_lPUSubServerID;

	CPTZButton1 m_btnPtzUp;
	CPTZButton1 m_btnPtzDown;
	CPTZButton1 m_btnPtzLeft;
	CPTZButton1 m_btnPtzRight;
	CPTZButton1 m_btnZoomIn;//zoom in
	CPTZButton1 m_btnZoomOut;//zoom out

public:
	long StartPlay(int iUserID, int iChannel, HWND hPlayWnd, LONG &lServerID);
	BOOL StopPlay();
	void AddCalPoint();
	BOOL GetLFCfg();
	BOOL SetLFCfg();
	BOOL GetLFTrackMode();
	BOOL SetLfTrackMode();
	BOOL GetPtzPos();
	BOOL SetPtzPos();
	BOOL RefreshTrackMode();
	BOOL RefreshLFCfg(int nIndex); // 刷新第几个标定

	void EnableLFWnd(BOOL bEnable);

    BOOL GetPUStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream, LONG lChannel);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCALF_H__E986C18F_2D67_4FE6_BD01_39224C548FA8__INCLUDED_)
