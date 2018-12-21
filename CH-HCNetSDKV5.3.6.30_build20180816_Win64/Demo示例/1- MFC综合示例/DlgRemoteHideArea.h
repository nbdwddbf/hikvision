#pragma once
#include "afxwin.h"


// CDlgRemoteHideArea dialog

class CDlgRemoteHideArea : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteHideArea)

public:
	CDlgRemoteHideArea(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteHideArea();

// Dialog Data
	


public:
	//{{AFX_DATA(CDlgRemoteHideArea)
	enum { IDD = IDD_DLG_REMOTE_HIDE_AREA };
	BOOL m_bCheckHideAreaShow;
	BOOL m_bCheckHideAreaSet;
	CStatic m_picDetectArea;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteHideArea)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteHideArea)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnHideAreaOk();
	afx_msg void OnBnClickedBtnHideAreaExit();
	afx_msg void OnBnClickedChkHideAreaShow();
	afx_msg void OnBnClickedChkHideAreaSet();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int	m_iChanShowNum;
	LONG	m_lLoginID;
	BOOL	m_bDrawdetect;
	LONG	m_lPlayHandle;
	NET_DVR_SHELTER m_struShelter[MAX_SHELTERNUM];
	
	
};
