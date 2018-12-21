#if !defined(AFX_DLGVCAITSCALIBRATE_H__5DBCCA96_FB49_4484_80DA_A2CC9F3FF32D__INCLUDED_)
#define AFX_DLGVCAITSCALIBRATE_H__5DBCCA96_FB49_4484_80DA_A2CC9F3FF32D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaITSCalibrate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCalibrate dialog

class CDlgVcaITSCalibrate : public CDialog
{
// Construction
public:
	CDlgVcaITSCalibrate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaITSCalibrate)
	enum { IDD = IDD_DLG_VCA_ITS_CALIBRATE };
	BOOL	m_bEnable;
	float	m_fHeight;
	float	m_fWidth;
	BOOL	m_bVerify;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaITSCalibrate)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaITSCalibrate)
	afx_msg void OnBtnSetItsCalibrate();
	virtual BOOL OnInitDialog();
	afx_msg void OnChkEnable();
	afx_msg void OnCheckVerify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
    NET_DVR_CALIBRATION_CFG m_struCalibrateCfg;
    LONG    m_lPlayHandle;
    CRect   m_rcWnd;
    BOOL    m_bCloseIn;
    BOOL    m_bMouseMove;
    BOOL    m_bNeedRedraw;

    DWORD m_dwPosNum;
    NET_VCA_POLYGON m_struVcaPolygon;
    NET_DVR_LINE_SEGMENT m_struVerifyLineSeg;
    BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);
    BOOL PreDrawVerifyLine(MSG* pMsg, CPoint& pt);

    void F_DrawFun(long lRealHandle, HDC hDc, DWORD dwUser);
    void DrawFrame( HDC hDc);
    void DrawVerifyLine(HDC hDC,  NET_DVR_LINE_SEGMENT const *lpLineSegment);
    BOOL StopPlay(LONG lPlayHandle);
    LONG RealPlay();

    BOOL SetCalibrateCfg();
    BOOL GetCalibrateCfg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAITSCALIBRATE_H__5DBCCA96_FB49_4484_80DA_A2CC9F3FF32D__INCLUDED_)
