#if !defined(AFX_DLGCENTERPOINT_H__FDEDEF27_B8B1_4EAA_AF8D_BF7B9844F9D5__INCLUDED_)
#define AFX_DLGCENTERPOINT_H__FDEDEF27_B8B1_4EAA_AF8D_BF7B9844F9D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgCenterPoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCenterPoint dialog

class DlgCenterPoint : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	DlgCenterPoint(CWnd* pParent = NULL);   // standard constructor
    ~DlgCenterPoint();
    enum
    {
        DRAW_TYPE_NONE      = 0,          //不画图
        DRAW_TYPE_LANE_BOUNDARY_LINE = 1, //车道边界线
        DRAW_TYPE_LANE_LINE   = 2,        //车道线
        DRAW_TYPE_PLATE_RECOG_RGN   = 3   //牌识区别
	};

// Dialog Data
	//{{AFX_DATA(DlgCenterPoint)
	enum { IDD = IDD_DLG_CENTER_POINT };

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCenterPoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCenterPoint)
    afx_msg void OnDestroy();
    afx_msg void OnBtnDrawPlateRecogRgn();
    afx_msg void OnBtnSave();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);;
    afx_msg void OnBtnEndDraw();
	afx_msg void OnButtonGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    void DrawRgnFun(HDC hdc);
protected:
    void InitCtrlState();
protected:
    void LoadWndContent();
    void SaveWndContent();
    
    void LoadViaLaneWndContent(int nLaneIndex);
    void SaveViaLaneWndContent(int nLaneIndex);
    BOOL SetITCTriggerCfg();
    //   	long StartRealPlay();  // 开始预览 
    //     BOOL StopRealPlay();  // 停止预览
public:
//     LONG m_lServerID;
//     LONG m_lChannel;
// 	int  m_iDevIndex;

private:
    int  m_iTriggerMode;
    LONG m_lPlayHandle;
    CRect m_rcPlayWnd;
    NET_DVR_CENTER_POINT_CFG m_struCenterPointCfg;
    int m_nCurDrawType;
    int m_nCurLaneIndex;
    int m_nDrawPointNum;
    BOOL m_bFirstDrawLaneBoundary;
    BOOL m_bFirstDrawLaneLine;
    NET_DVR_CALIBRATION m_struCalibration;
	char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCENTERPOINT_H__FDEDEF27_B8B1_4EAA_AF8D_BF7B9844F9D5__INCLUDED_)
