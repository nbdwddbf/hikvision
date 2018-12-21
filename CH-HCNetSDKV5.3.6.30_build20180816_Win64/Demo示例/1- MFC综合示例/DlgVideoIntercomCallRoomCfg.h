#if !defined(AFX_DLGVIDEOINTERCOMCALLROOMCFG_H__D547EA62_CF79_4D16_9C40_F2DD1552A4D2__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMCALLROOMCFG_H__D547EA62_CF79_4D16_9C40_F2DD1552A4D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomCallRoomCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCallRoomCfg dialog

class CDlgVideoIntercomCallRoomCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomCallRoomCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomCallRoomCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_CALL_ROOM_CFG };
	CComboBox	m_cmbButtonNumber;
	int		m_iFloorNumber;
	short	m_nRoomNumber;
	BOOL	m_bCallManageCenter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomCallRoomCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomCallRoomCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    int m_iDevIndex;
private:
    NET_DVR_CALL_ROOM_CFG m_struCallRoomCfg;

public:
    CString m_csCalledName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMCALLROOMCFG_H__D547EA62_CF79_4D16_9C40_F2DD1552A4D2__INCLUDED_)
