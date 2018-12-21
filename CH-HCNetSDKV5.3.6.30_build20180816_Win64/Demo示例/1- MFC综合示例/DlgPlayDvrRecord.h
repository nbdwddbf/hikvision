#if !defined(AFX_DLGPLAYDVRRECORD_H__08E3EDF0_4B04_4DC0_BABD_278E1A6D4951__INCLUDED_)
#define AFX_DLGPLAYDVRRECORD_H__08E3EDF0_4B04_4DC0_BABD_278E1A6D4951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlayDvrRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayDvrRecord dialog

class CDlgPlayDvrRecord : public CDialog
{
// Construction
public:
	CDlgPlayDvrRecord(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgPlayDvrRecord();
// Dialog Data
	//{{AFX_DATA(CDlgPlayDvrRecord)
	enum { IDD = IDD_DLG_PLAY_DVR_RECORD };
	CComboBox	m_cmRecordChannel;
	CComboBox	m_comboRecordType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlayDvrRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlayDvrRecord)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStartRecord();
	afx_msg void OnBtnStopRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	int  m_iDeviceIndex;	
	int  m_iChanIndex;	
	int  m_iChanCount;
	LONG m_lChannel;
	LONG m_lRecordType;
	LONG m_lStartChan;
	LONG m_lLoginID;
	

    void SetParentWnd(HWND *hhWnd, int iParentNum);
	BOOL CheckInitParam();
	void InitComboBox();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYDVRRECORD_H__08E3EDF0_4B04_4DC0_BABD_278E1A6D4951__INCLUDED_)
