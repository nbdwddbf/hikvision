#if !defined(AFX_DLGFISHEYETRACKCFG_H__ECF1C5AF_5AD2_4B87_8434_37589C1D3B9A__INCLUDED_)
#define AFX_DLGFISHEYETRACKCFG_H__ECF1C5AF_5AD2_4B87_8434_37589C1D3B9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
#include "DlgVcaSceneCfg.h"
// DlgFisheyeTrackCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeTrackCfg dialog

class CDlgFisheyeTrackCfg : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgFisheyeTrackCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFisheyeTrackCfg)
	enum { IDD = IDD_DLG_FISHEYE_TRACK_CFG };

	enum
	{   
		OP_TYPE_NONE = 0,
		OP_TYPE_CALIB = 1,
		OP_TYPE_TRACK = 2
	};

	enum
	{
		TRANS_MODE_NETSDK = 0,
		TRANS_MODE_RS485  = 1
	};

	CComboBox	m_comboCalibPtNO;
	CComboBox       m_comboTransMode;
	float	m_fFisheyePtX;
	float   m_fFisheyePtY;
	int		m_nTrackDevPosP;
	int		m_nTrackDevPosT;
	int		m_nTrackDevPosZ;
	int		m_nTrackDevHPosP;
	int		m_nTrackDevHPosT;
	int  	m_nTrackDevHPosZ;
	BOOL    m_bTrackDevEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFisheyeTrackCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFisheyeTrackCfg)
	afx_msg void OnBtnFisheyeStartrealplay();
	afx_msg void OnBtnFisheyeStoprealplay();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSetFisheyePt();
	afx_msg void OnBtnTrackdevCfg();
	afx_msg void OnBtnTrackdevStartrealplay();
	afx_msg void OnBtnTrackdevStoprealplay();
	afx_msg void OnSelchangeComboCalibPtNo();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnCalibPtNum();
	afx_msg void OnBtnGetTrackdevHorizonPos();
	afx_msg void OnBtnGetTrackdevCalibPos();
	afx_msg void OnRadioCalib();
	afx_msg void OnRadioTrack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DrawTrackDevFun(HDC hdc);
	void DrawFisheyeFun(HDC hdc);
private:
	WORD DecToHex(WORD wDec)
	{
		return (wDec / 1000) * 4096 + ((wDec % 1000) / 100) * 256 + ((wDec % 100) / 10) * 16 + (wDec % 10);
	}
	
	WORD HexToDec(WORD wHex)
	{
		return (wHex / 4096) * 1000 + ((wHex % 4096) / 256) * 100 + ((wHex % 256) / 16) * 10 + (wHex % 16);
	}
protected:
	void InitCtrlState();
	BOOL GetTrackDevParam();
	BOOL SetTrackDevParam();
	void LoadWndContent();
	void SaveWndContent();
	void LoadCalibPointToWnd(int nIndex);
	void SaveCalibPointFromWnd(int nIndex);
	void StartTrackDevRealPlay();
	void StopTrackDevRealPlay();
	void LoginTrackDev();
	void LogoutTrackDev();
    void EnableCalib(BOOL bEnable);
	
private:
	NET_DVR_TRACK_DEV_PARAM m_struTrackDevParam;
	int m_nCurCBIndex;
	BOOL m_bIsFisheyePlaying;
	LONG m_lTrackDevRealhandle;
	LONG m_lTrackDevUserID;
	CRect m_rcFisheyePlayWnd;
	CRect m_rcTrackDevPlayWnd;

private:
	CScenePTZButton m_btnUp;
	CScenePTZButton m_btnDown;
	CScenePTZButton m_btnLeft;
	CScenePTZButton m_btnRight;
	CScenePTZButton m_btnZoomIn;
	CScenePTZButton m_btnZoomOut;
	CScenePTZButton m_btnFocusNear;
	CScenePTZButton m_btnFocusFar;
	CScenePTZButton m_btnIrisClose;
	CScenePTZButton m_btnIrisOpen;

    int m_nOperationType;
	CPoint m_ptTrack;
	BOOL   m_bDrawTrackPoint;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFISHEYETRACKCFG_H__ECF1C5AF_5AD2_4B87_8434_37589C1D3B9A__INCLUDED_)
