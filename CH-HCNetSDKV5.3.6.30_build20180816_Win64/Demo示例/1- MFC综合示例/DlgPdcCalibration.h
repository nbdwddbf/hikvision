#if !defined(AFX_DLGPDCCALIBRATION_H__AF6999F9_B674_4D78_A3DD_A8BF285BEF1C__INCLUDED_)
#define AFX_DLGPDCCALIBRATION_H__AF6999F9_B674_4D78_A3DD_A8BF285BEF1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPdcCalibration.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcCalibration dialog
#include "Picture.h"
class CDlgPdcCalibration : public CDialog
{
// Construction
public:
	CDlgPdcCalibration(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPdcCalibration)
	enum { IDD = IDD_DLG_PDC_CALIBRATION };
	BOOL	m_bVerifyCalibration;
	BOOL	m_bDraw;
	BOOL	m_bEnable;
	BOOL	m_bLine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPdcCalibration)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPdcCalibration)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetCalibration();
	afx_msg void OnButtonRecapture();
	afx_msg void OnPaint();
	afx_msg void OnChkVerifyCalibrtion();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChkDraw();
    afx_msg void OnChkLine();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL SetCalibrationWnd(NET_DVR_CALIBRATION_CFG struCalibration);
    BOOL SetCalibration();
    BOOL CaptureBmp(); // 预览抓bmp图
    void DrawCalibration();
    void DrawVerifyCalibration();
    long StartRealPlay();
    BOOL StopRealPlay();
    void PdcLineCalibration(/*HDC hDc*/);
public :
    NET_DVR_CALIBRATION_CFG m_struCalibrationCfg; // 标定参数 
    long        m_lServerID; // 用户ID
    int         m_iDevIndex; //设备索引
    long        m_lChannel;  // 用户通道号
    long        m_lPlayHandle; // 预览句柄
    NET_DVR_PDC_CALIBRATION m_struPdcCalibration;
    NET_DVR_PDC_LINE_CALIBRATION m_struPdcLineCalib;
    char m_chFilename[256]; //抓图保存的位置
    CPicture m_pic;
    CDC* m_pDCRect;
    CRect m_rcWndRect;
    BOOL m_bMouseMove;
    NET_VCA_POINT m_struVerifyPoint;
    NET_VCA_RECT m_struVerifyRect;
    BOOL m_bDrawRect;
    int m_iCalibrationType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPDCCALIBRATION_H__AF6999F9_B674_4D78_A3DD_A8BF285BEF1C__INCLUDED_)
