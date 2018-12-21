#if !defined(AFX_DLGFISHEYEPTZCONTROL_H__5DD24E47_6F94_4288_88CB_3D343A0464C1__INCLUDED_)
#define AFX_DLGFISHEYEPTZCONTROL_H__5DD24E47_6F94_4288_88CB_3D343A0464C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
#include "DlgFisheyePtzPlayWnd.h"
// DlgFishEyePtzControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFishEyePtzControl dialog

class CDlgFishEyePtzControl : public CDialog
{
// Construction
public:
	CDlgFishEyePtzControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFishEyePtzControl)
	enum { IDD = IDD_DLG_FISHEYE_PTZ_CONTROL };
	CComboBox	m_comboPtzChannel;
	CListBox	m_listCallbackData;
	float	m_fPtzX;
	float	m_fPtzY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFishEyePtzControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFishEyePtzControl)
	afx_msg void OnDestroy();
	afx_msg void OnBtnCreateLonglink();
	afx_msg void OnBtnCloseLonglink();
	afx_msg void OnBtnGetPtzPoint();
	afx_msg void OnBtnSetPtzPoint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSelchangeComboPtzChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL StartRealPlay();
	BOOL StopRealPlay();

protected:
	void InitCtrlState();
	BOOL GetChannelStreamStatus(LONG lChannel,BYTE& byStreamStatus);
public:
	LONG m_lServerID;
	LONG m_lChannel;
	int  m_iDevIndex;
	LONG   m_lFishEyeCfgHandle;

	void SendDragPtzPos(CPoint pt);
	void AddFishEyeCallbackData(CString strData);
	void DrawTrackDevFun(HDC hdc);
	CRect m_rcPlayWnd;
	BOOL m_bDragFishEyePTZ;
	CPoint m_ptOriDrag;
	DWORD   m_dwPtzChannel;
	LONG m_lRealHandle;

	CDlgFisheyePtzPlayWnd m_dlgPtzPlayWnd;
	BYTE m_byCurChannelStreamStatus;
private:
	CPen m_penRed;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFISHEYEPTZCONTROL_H__5DD24E47_6F94_4288_88CB_3D343A0464C1__INCLUDED_)
