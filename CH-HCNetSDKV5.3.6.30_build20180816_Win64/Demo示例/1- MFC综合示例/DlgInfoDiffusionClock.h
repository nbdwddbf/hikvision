#if !defined(AFX_DLGINFODIFFUSIONCLOCK_H__C953B100_F24B_4539_9DD9_70A34067CCC1__INCLUDED_)
#define AFX_DLGINFODIFFUSIONCLOCK_H__C953B100_F24B_4539_9DD9_70A34067CCC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionClock.h : header file
//
#include "InfoDiffusionParamsConvert.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionClock dialog

class CDlgInfoDiffusionClock : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionClock(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionClock)
	enum { IDD = IDD_DLG_CLOCK };
	BOOL	m_bIconEnable;
	BOOL	m_bHmsEnable;
	BOOL	m_bWeekEnable;
	BOOL	m_bYmdEnable;
	DWORD	m_dwBackPic;
	DWORD	m_dwClockH;
	DWORD	m_dwIconH;
	CString	m_szIconType;
	DWORD	m_dwIconW;
	DWORD	m_dwIconX;
	DWORD	m_dwIconY;
	DWORD	m_dwClockW;
	DWORD	m_dwHmsBackB;
	DWORD	m_dwHmsBackG;
	DWORD	m_dwHmsBackR;
	DWORD	m_dwHmsFontB;
	DWORD	m_dwHmsFontG;
	DWORD	m_dwHmsFontR;
	DWORD	m_dwWeekBackB;
	DWORD	m_dwWeekBackG;
	DWORD	m_dwWeekBackR;
	DWORD	m_dwWeekFontB;
	DWORD	m_dwWeekFontG;
	DWORD	m_dwWeekFontR;
	DWORD	m_dwWeekFontSize;
	DWORD	m_dwWeekH;
	DWORD	m_dwWeekW;
	DWORD	m_dwWeekX;
	DWORD	m_dwWeekY;
	DWORD	m_dwYmdFontB;
	DWORD	m_dwYmdBackB;
	DWORD	m_dwYmdBackG;
	DWORD	m_dwYmdBackR;
	DWORD	m_dwYmdFontSize;
	DWORD	m_dwYmdFontG;
	DWORD	m_dwYmdH;
	DWORD	m_dwYmdW;
	DWORD	m_dwYmdX;
	DWORD	m_dwYmdY;
	DWORD	m_dwYmsFontSize;
	DWORD	m_dwYmsH;
	DWORD	m_dwYmsW;
	DWORD	m_dwYmsX;
	DWORD	m_dwYmsY;
	DWORD	m_dwYmdFontR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionClock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionClock)
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	LONG m_lUserID;
	int m_iDeviceIndex;
		
	char* m_pOutputXmlBuffer;

public:
	LPNET_DVR_MATERIAL m_struMaterial;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONCLOCK_H__C953B100_F24B_4539_9DD9_70A34067CCC1__INCLUDED_)
