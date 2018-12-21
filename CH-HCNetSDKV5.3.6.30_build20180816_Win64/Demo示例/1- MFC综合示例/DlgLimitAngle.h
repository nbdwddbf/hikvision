#if !defined(AFX_DLGLIMITANGLE_H__096C7CA1_2687_4476_B764_F330E331EB6F__INCLUDED_)
#define AFX_DLGLIMITANGLE_H__096C7CA1_2687_4476_B764_F330E331EB6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLimitAngle.h : header file
//
#include "PTZButton1.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgLimitAngle dialog

typedef enum tagLIMIT_ANGLE_TYPE
{
    POSITION_LIMIT_ANGLE,
    PATROL_LIMIT_ANGLE
}LIMIT_ANGLE_TYPE;
class CDlgLimitAngle : public CDialog
{
// Construction
public:
	CDlgLimitAngle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLimitAngle)
	enum { IDD = IDD_DLG_LIMIT_ANGLE };
	CComboBox	m_cmbChannel;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLimitAngle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLimitAngle)
	afx_msg void OnBtnSetLimitangle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetDownLimitangel();
	afx_msg void OnBtnSetLeftLimitangle();
	afx_msg void OnBtnSetRightLimitangle();
	afx_msg void OnBtnSetUpLimitangle();
	afx_msg void OnBtnGetDownLimitangel();
	afx_msg void OnBtnGetLeftLimitangle();
	afx_msg void OnBtnGetRightLimitangle();
	afx_msg void OnBtnGetUpLimitangle();
	afx_msg void OnBtnPositionPtz();
	afx_msg void OnBtnGetLimitangle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL GetPositionLimitAngle();
    BOOL SetPositionLimitAngle();
    BOOL GetPatrolLimitAngle();
    BOOL SetPatrolLimitAngle();

    void InitPTZButton();
    void GetPtzPos(NET_DVR_PTZPOS &struPtzPos);
    void SetPtzPos(NET_DVR_PTZPOS &struPtzPos);

protected:
    CPTZButton1 m_btnPtzUp;
    CPTZButton1 m_btnPtzDown;
    CPTZButton1 m_btnPtzLeft;
    CPTZButton1 m_btnPtzRight;
    CPTZButton1 m_btnZoomIn;//zoom in
    CPTZButton1 m_btnZoomOut;//zoom out
    CPTZButton1 m_btnFocusNear;//focus near
    CPTZButton1 m_btnFocusFar;//focus far
    CPTZButton1 m_btnIrisOpen;//iris open
	CPTZButton1 m_btnIrisClose;//iris close

public:
    NET_DVR_LIMIT_ANGLE m_struLimiteAngle;
    int     m_iPositionIndex;
    int     m_iPatrolIndex;
    LIMIT_ANGLE_TYPE     m_iLimitAngleType;  //  0-position  1-patral
    LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
    LONG    m_lPlayHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLIMITANGLE_H__096C7CA1_2687_4476_B764_F330E331EB6F__INCLUDED_)
