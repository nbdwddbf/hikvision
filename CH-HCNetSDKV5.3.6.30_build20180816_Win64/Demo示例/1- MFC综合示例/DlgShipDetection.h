#if !defined(AFX_DLGSHIPDETECTION_H__C9D0DE79_2879_4774_9D23_7102F67ADDAF__INCLUDED_)
#define AFX_DLGSHIPDETECTION_H__C9D0DE79_2879_4774_9D23_7102F67ADDAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgShipDetection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgShipDetection dialog

class CDlgShipDetection : public CDialog
{
// Construction
public:
	CDlgShipDetection(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgShipDetection)
	enum { IDD = IDD_DLG_SHIP_DETECTION };
	CListCtrl	m_listShipDetection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShipDetection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgShipDetection)
	afx_msg void OnBtnGet();
	afx_msg void OnButtonDeleteShipInfo();
	LRESULT StopShipsNoList(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lUserID;
    int     m_iDevIndex;
    LONG    m_lChannel;
	LONG    m_lShipDetectionHandle;

	void ProcGetShipsNoList(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
	void AddShipsNoListItem(const NET_DVR_SHIPSCOUNT_CFG &Item);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSHIPDETECTION_H__C9D0DE79_2879_4774_9D23_7102F67ADDAF__INCLUDED_)
