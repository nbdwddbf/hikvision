#if !defined(AFX_DLGPOSREGION_H__ECFD32E6_EE6D_4766_BC1A_FD1FC2D2FEAC__INCLUDED_)
#define AFX_DLGPOSREGION_H__ECFD32E6_EE6D_4766_BC1A_FD1FC2D2FEAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPOSRegion.h : header file
//
#define _LEFT_TOP     0 //左上
#define _LEFT_BOTTOM  1 //左下
#define _RIGHT_TOP    2 //右上
#define _RIGHT_BOTTOM 3 //右下
#define _LEFT_POS     4 //左
#define _TOP_POS      5 //上
#define _RIGHT_POS    6 //右
#define _BOTTOM_POS   7 //下

/////////////////////////////////////////////////////////////////////////////
// CDlgPOSRegion dialog

class CDlgPOSRegion : public CDialog
{
// Construction
public:
	CDlgPOSRegion(CWnd* pParent = NULL);   // standard constructor
 

// Dialog Data
	//{{AFX_DATA(CDlgPOSRegion)
	enum { IDD = IDD_DLG_POS_REGION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPOSRegion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPOSRegion)
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	private:
		CBrush m_brush;
		bool m_bGetClient;
	//	CPreviewPlay *m_pPreviewPlay;
		BOOL m_bPreview;
		
		// Start preview
		//bool StartPreview(int iDeviceID, int iCameraID);
		
		// Stop preview
		//void StopPreview(int iDeviceID, int iCameraID);
		
		// Set double screen
		void SetDoubleScreen(void);
		
		bool m_bStart;
		
		// The monitor index
		int m_nDeviceIndex; 
		
		int m_iFunPtrIndex;
		
		// Camera ID
		int m_iCameraID;
		
		void ReadyForZoom(CPoint point);
		
		int m_iZoomType;
		
		// 左键是否按下
		bool m_bLBDown;
		
		bool m_bEdge;
		
		bool m_bInRect;
		
		CPoint m_ptMoveSt;
		
		HCURSOR m_hCurDrag;
		
		bool m_bStartZoom;
		
		CPoint m_ptZoomSt;
		
		CRect m_rcClient;
		
		CRect m_rcDisplay;
	public:
		CRect m_rcRegion;
		void DrawRect(CDC *pDC);
		
		// Device ID
		int m_iDeviceID;
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		
//	POSDISPLAY m_stPOSDisplay;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSREGION_H__ECFD32E6_EE6D_4766_BC1A_FD1FC2D2FEAC__INCLUDED_)
