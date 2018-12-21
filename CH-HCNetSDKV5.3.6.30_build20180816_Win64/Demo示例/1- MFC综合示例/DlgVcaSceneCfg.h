#if !defined(AFX_DLGVCASCENECFG_H__3369B73A_3DF5_422E_8C0D_BE1BBD6439C0__INCLUDED_)
#define AFX_DLGVCASCENECFG_H__3369B73A_3DF5_422E_8C0D_BE1BBD6439C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaSceneCfg.h : header file
//

class CScenePTZButton : public CButton
{
public:
	CScenePTZButton();
	
public:
	DWORD  m_dwPtzCommand;
	static LONG m_lPlayHandle;
public:
	virtual ~CScenePTZButton();
	
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	DECLARE_MESSAGE_MAP()
		
protected:
	BOOL PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand,DWORD dwStop);
};

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneCfg dialog

class CDlgVcaSceneCfg : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaSceneCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaSceneCfg)
	enum { IDD = IDD_DLG_VCA_SCENE_CFG };
	enum{   
		
		    CHAN_DIRECTION_UP           = 0x01,        
			CHAN_DIRECTION_DOWN         = 0x02,         
			CHAN_DIRECTION_BI           = 0x03,        
			CHAN_DIRECTION_EAST_WEST    = 0x04,        
			CHAN_DIRECTION_SOUTH_NORTH  = 0x05,         
			CHAN_DIRECTION_WEST_EAST    = 0x06,        
			CHAN_DIRECTION_NORTH_SOUTH  = 0x07,         
			CHAN_DIRECTION_OTHER        = 0x08          
	} ;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSceneCfg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSceneCfg)
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboSceneno();
	afx_msg void OnBtnClickedGetPtzPos();
	afx_msg void OnBtnClickedSaveSceneCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
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
	BOOL GetSceneCfg();
	BOOL SaveSceneCfg();
	
	void InitCtrlState();
	void UpdateCtrlValue();
	
	void LoadSceneParam(int nSceneIndex);
	void SaveSceneParam(int nSceneIndex);
private:
	CComboBox m_comboSceneNo;
	CComboBox m_comboDirection;
	BOOL      m_bSceneEnable;
	CString   m_strSceneName;
	int       m_nCurSceneIndex;
	int       m_nSceneID;
	int       m_nTrackTime;
    int       m_nPtzXPos;
	int       m_nPtzYPos;
	int       m_nPtzZPos;
	NET_DVR_SCENE_CFG  m_struSceneCfg;
	
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASCENECFG_H__3369B73A_3DF5_422E_8C0D_BE1BBD6439C0__INCLUDED_)
