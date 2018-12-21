#if !defined(AFX_DLGROICFG_H__9F513273_B06C_4B1D_BD21_ED0735EF77B2__INCLUDED_)
#define AFX_DLGROICFG_H__9F513273_B06C_4B1D_BD21_ED0735EF77B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRoiCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRoiCfg dialog

class CDlgRoiCfg : public CDialog
{
// Construction
public:
	CDlgRoiCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRoiCfg)
	enum { IDD = IDD_DLG_ROI_CFG };
	CComboBox	m_comboTrackType;
	CComboBox	m_comboType;
	CComboBox	m_comboImageQualityLevel;
	CComboBox	m_comboStreamType;
	CComboBox	m_comboRoiID;
	CStatic	m_wndPlay;
	BOOL	m_bSingleEnable;
	CString	m_csRoiName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRoiCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	BOOL Play();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRoiCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOut();
	afx_msg void OnRadioFixroi();
	afx_msg void OnRadioTrackroi();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnGetRoiinfo();
	afx_msg void OnSelchangeComboRoiid();
	afx_msg void OnBtnGetall();
	afx_msg void OnBtnTrack();
	afx_msg void OnBtnTrackGet();
	afx_msg void OnBtnTestCompressv30();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lLoginID;
	int     m_iDeviceIndex;
	LONG    m_lChannel;
	LONG	m_lPlayHandle;
	CRect   m_rcWnd;
	NET_VCA_RECT m_struRoiRect[8]; //¹Ì¶¨ÇøÓò
	BOOL    m_bFixRoi;
	BOOL    m_bTrackRoi;
	DWORD   m_dwRoiID;
	BOOL    m_bMouseMove;
	NET_DVR_ROI_DETECT_CFG m_struRoiDetectCfg[24];
	NET_DVR_ROI_DETECT_COND m_struRoiDetectCond[24];
	NET_DVR_MUL_STREAM_CHANNEL_GROUP m_struChannelGroup;
	NET_DVR_ROI_DETECT_NUM m_struRoidetectNum;

	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	void F_DrawRect(HDC hDc);
	void DrawITCRect(HDC hDc, NET_VCA_RECT struRect,  CRect rcWnd, DWORD dwCurRect, COLORREF color);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROICFG_H__9F513273_B06C_4B1D_BD21_ED0735EF77B2__INCLUDED_)
