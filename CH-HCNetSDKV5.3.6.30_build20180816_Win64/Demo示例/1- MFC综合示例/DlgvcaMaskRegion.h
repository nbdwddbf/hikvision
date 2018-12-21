#if !defined(AFX_DLGVCAMASKREGION_H__51DB5986_D6FA_47B9_947D_7A74F7FD7853__INCLUDED_)
#define AFX_DLGVCAMASKREGION_H__51DB5986_D6FA_47B9_947D_7A74F7FD7853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaMaskRegion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaMaskRegion dialog

class CDlgVcaMaskRegion : public CDialog
{
	// Dialog Data
	//{{AFX_DATA(CDlgVcaMaskRegion)
	enum { IDD = IDD_DLG_VCA_MASK_REGION };
	CComboBox	m_cmbChannel;
	BOOL	m_bPolygon1;
	BOOL	m_bPolygon2;
	BOOL	m_bPolygon3;
	BOOL	m_bPolygon4;
	BOOL	m_bDrawPolygon;
	BOOL	m_bActive1;
	BOOL	m_bActive2;
	BOOL	m_bActive3;
	BOOL	m_bActive4;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaMaskRegion)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgVcaMaskRegion)
	afx_msg void OnChkDrawPolygon();
	afx_msg void OnCheckPolygon1();
	afx_msg void OnCheckPolygon2();
	afx_msg void OnCheckPolygon3();
	afx_msg void OnCheckPolygon4();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeEditMaskNum();
	afx_msg void OnCheckMaskActive();
	afx_msg void OnDestroy();
	afx_msg void OnRadioPolygon1();
	afx_msg void OnRadioPolygon2();
	afx_msg void OnRadioPolygon3();
	afx_msg void OnRadioPolygon4();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
        // Construction
public:
    CDlgVcaMaskRegion(CWnd* pParent = NULL);   // standard constructor
    
    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
    void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,   COLORREF color);
    BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
    void F_AddLabel(HDC hDc, DWORD dwRuleID);
    BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
    BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
    void F_DrawArrowhead(HDC hDc, DWORD dwRuleID, int direction);
    
    void EnableDrawPolygon(BOOL Enable);
    
    BOOL GetMaskRegion();
    BOOL SetMaskRegion();

    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
    LONG StartPlay();
    BOOL StopPlay();
    
    long m_lServerID;
    int  m_iDevIndex;
    int m_iChannel;
    long  m_lPlayHandle;
    
    NET_VCA_MASK_REGION_LIST m_struMaskRegionList;
    NET_VCA_POLYGON m_struPolygon[MAX_MASK_REGION_NUM];
    CRect m_rcWndRect;
    BOOL m_bMouseMove[MAX_MASK_REGION_NUM];
    BOOL m_bCloseIn[MAX_MASK_REGION_NUM];
    DWORD m_dwPosNum;
    BOOL m_bNeedRedraw[MAX_MASK_REGION_NUM];
    int m_iPolygonId;
    
    LONG    m_lPUServerID;
    NET_DVR_PU_STREAM_CFG m_struPuStream;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAMASKREGION_H__51DB5986_D6FA_47B9_947D_7A74F7FD7853__INCLUDED_)
