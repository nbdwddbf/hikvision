#if !defined(AFX_DLGENCODEJOINT_H__52AF0772_9888_47CA_8386_A6173CEB46EC__INCLUDED_)
#define AFX_DLGENCODEJOINT_H__52AF0772_9888_47CA_8386_A6173CEB46EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEncodeJoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEncodeJoint dialog

class CDlgEncodeJoint : public CDialog
{
// Construction
public:
	CDlgEncodeJoint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEncodeJoint)
	enum { IDD = IDD_DLG_ENCODE_JOINT };
	CComboBox	m_comboJoint;
	int		m_iChannel;
	int		m_iDevType;
	CString	m_csIPAddr;
	int		m_iPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEncodeJoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEncodeJoint)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
    NET_DVR_ENCODE_JOINT_PARAM m_struEncodeJoint;
public:
    void InitWnd();
    BOOL GetEncodeJointParam(NET_DVR_ENCODE_JOINT_PARAM &struEncodeJoint);
    void SetEncodeJointParamToWnd(NET_DVR_ENCODE_JOINT_PARAM &struEncodeJoint);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENCODEJOINT_H__52AF0772_9888_47CA_8386_A6173CEB46EC__INCLUDED_)
