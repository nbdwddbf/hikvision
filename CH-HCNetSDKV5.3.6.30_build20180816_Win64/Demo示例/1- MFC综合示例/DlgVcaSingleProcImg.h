#if !defined(AFX_DLGVCASINGLEPROCIMG_H__FBB529EC_30F7_4E46_8CA7_8C3B77B61DAB__INCLUDED_)
#define AFX_DLGVCASINGLEPROCIMG_H__FBB529EC_30F7_4E46_8CA7_8C3B77B61DAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSingleProcImg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSingleProcImg dialog
#include "Picture.h"

class CDlgVcaSingleProcImg : public CDialog
{
// Construction
public:
	CDlgVcaSingleProcImg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaSingleProcImg)
	enum { IDD = IDD_DLG_VCA_SINGLE_PROCIMG };
	CComboBox	m_comboChoosePicNo;
	CComboBox	m_comboSensitivity;
	BOOL	m_bDrawMaxFilter;
	BOOL	m_bDrawMiniFilter;
	BOOL	m_bChkFilterActive;
	BOOL	m_bChkDrawPolygon;
	DWORD	m_dwImageWidth;
	BOOL	m_bChkEnable;
	DWORD	m_dwImageHeight;
	CString	m_csFilePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSingleProcImg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSingleProcImg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChkDrawMaxfilter();
	afx_msg void OnButtonRecapture();
	afx_msg void OnChkFilterActive();
	afx_msg void OnChkDrawMinifilter();
	afx_msg void OnChkDrawPolygon();
	afx_msg void OnBtnSend();
	virtual void PostNcDestroy(); 
	afx_msg void OnBtnScan();
	afx_msg void OnBtnGetPicmodel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    BOOL SetCalibrationWnd(NET_DVR_CALIBRATION_CFG struCalibration);
    BOOL SetCalibration();
    BOOL CaptureBmp(); // 预览抓bmp图
    void DrawFilter();
    void DrawPolygon();
    long StartRealPlay();
    BOOL StopRealPlay();
public :
    long        m_lServerID; // 用户ID
    int         m_iDevIndex; //设备索引
    long        m_lChannel;  // 用户通道号
    long        m_lPlayHandle; // 预览句柄
    char m_chFilename[256]; //抓图保存的位置
    CPicture m_pic;
    CDC* m_pDCRect;
    CRect m_rcWndRect;
    BOOL m_bMouseMove;
    NET_VCA_POINT m_struVerifyPoint;
    NET_VCA_RECT m_struVerifyRect;
    BOOL m_bDrawRect;
	
	char    m_csPicDir[MAX_PATH];
	NET_VCA_FD_PROCIMG_CFG m_struFDProcImgCfg;
	NET_VCA_RECT m_struMaxFilter;
	NET_VCA_RECT m_struMiniFilter;
	DWORD   m_dwPosNum; 
	BOOL    m_bCloseIn;
    BOOL    m_bMouseMovePolggon;
    BOOL    m_bNeedRedraw;
	DWORD   m_dwFileSize;
	LOCAL_FACE_PICTURE_INFO m_struFacePicInfo[MAX_HUMAN_PICTURE_NUM];
	LPNET_VCA_FD_PROCIMG_RESULT m_pStruRecvBuf;
	BOOL    m_bDetectSuccess;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASINGLEPROCIMG_H__FBB529EC_30F7_4E46_8CA7_8C3B77B61DAB__INCLUDED_)
