#if !defined(AFX_DLGVCALANECFG_H__AB91C645_1063_4275_B0A4_3069C8039056__INCLUDED_)
#define AFX_DLGVCALANECFG_H__AB91C645_1063_4275_B0A4_3069C8039056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaLaneCfg.h : header file
//
#include "DrawFun.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaLaneCfg dialog

class CDlgVcaLaneCfg : public CDialog
{
// Construction
public:
	CDlgVcaLaneCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaLaneCfg)
	enum { IDD = IDD_DLG_VCA_LANECFG };
	CComboBox	m_comboLaneIndex;
	BOOL	m_bEnbale;
	CString	m_csLaneName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaLaneCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaLaneCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetLanecfg();
	afx_msg void OnSelchangeComboLaneIndex();
	afx_msg void OnRadioDrawPolygon();
	afx_msg void OnRadioDrawDirection();
	afx_msg void OnBtnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
    void InitWnd();
    void InitDrawParam();
    BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);
    BOOL PreDrawDirectionMsg(MSG* pMsg, CPoint &pt);
    void SetLaneWnd();
private:
    LONG    m_lPlayHandle;
private:
    LONG StartPlay();
    BOOL StopPlay(LONG lPlayHandle);
public:
    DWORD   m_dwDrawType; // 1- polygon  2-Direction
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
    NET_DVR_LANE_CFG m_struLaneCfg;
    LONG    m_lPUServerID;
    NET_DVR_PU_STREAM_CFG m_struPUStream;
    
    NET_VCA_POLYGON m_struVcaPolygon[MAX_LANE_NUM];
    BOOL m_bCloseIn[MAX_LANE_NUM]; 
    BOOL m_bNeedRedraw[MAX_LANE_NUM]; 
    BOOL m_bMouseMove[MAX_LANE_NUM]; 
    BOOL m_bDirectMouseMove;
    DWORD m_dwPosNum;
    int  m_iCurLaneID;   
    CRect m_rcWnd;
public:
//    CDrawFun    m_DrawFun;
    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
    void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color);
    void DrawOneLane(COLORREF color);
    
    BOOL GetLaneCfg();
    BOOL SetLaneCfg();
    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCALANECFG_H__AB91C645_1063_4275_B0A4_3069C8039056__INCLUDED_)
