#if !defined(AFX_IVMSATMREGION_H__5996D066_8164_439D_9ED2_11444783A5B3__INCLUDED_)
#define AFX_IVMSATMREGION_H__5996D066_8164_439D_9ED2_11444783A5B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaEnterRegion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVCAAtmRegion dialog

class CDlgVcaEnterRegion : public CDialog
{
// Construction
public:
	CDlgVcaEnterRegion(CWnd* pParent = NULL);   // standard constructor

	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color);
	BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
	BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
	BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
	BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
	BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
    
    BOOL GetEnterRegion();
    BOOL SetEnterRegion();
    LONG StartPlay();
    BOOL StopPlay();
    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);

    LONG m_lPUServerID;
	long m_lServerID;
	int  m_iDevIndex;
	int m_iChannel;
	long  m_lPlayHandle;
	NET_VCA_ENTER_REGION m_struVCAEnterRegion;
	NET_VCA_POLYGON m_struPolygon;
	CRect m_rcWndRect;
	BOOL m_bMouseMove;
	BOOL m_bCloseIn;
	DWORD m_dwPosNum;

	BOOL m_bNeedRedraw;

    NET_DVR_PU_STREAM_CFG m_struPuStream;
// Dialog Data
	//{{AFX_DATA(CDlgVcaEnterRegion)
	enum { IDD = IDD_DLG_VCA_ENTER_REGION };
	BOOL	m_bDrawPolygon;
	BOOL	m_bActive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaEnterRegion)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaEnterRegion)
	afx_msg void OnChkDrawPolygon();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCheckActive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVMSATMREGION_H__5996D066_8164_439D_9ED2_11444783A5B3__INCLUDED_)
