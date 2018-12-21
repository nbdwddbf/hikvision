#if !defined(AFX_DLGVIDEOOUT_H__6B077155_9C57_4AB2_A884_324330B991F3__INCLUDED_)
#define AFX_DLGVIDEOOUT_H__6B077155_9C57_4AB2_A884_324330B991F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoOut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoOut dialog

class CDlgVideoOut : public CDialog
{
// Construction
public:
	CDlgVideoOut(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoOut)
	enum { IDD = IDD_DLG_VIDEOOUT };
	CComboBox	m_cmBNCChan;
	CComboBox	m_cmVideoFormat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoOut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoOut)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComboBncChannel();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	int m_iDeviceIndex;
	long m_lUserID;
	int m_iCurBNCChan;
	NET_DVR_VIDEOOUT_V30 m_struVideoOut; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOOUT_H__6B077155_9C57_4AB2_A884_324330B991F3__INCLUDED_)
