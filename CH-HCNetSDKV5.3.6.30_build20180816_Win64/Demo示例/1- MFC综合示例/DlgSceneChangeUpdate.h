#if !defined(AFX_DLGSCENECHANGEUPDATE_H__C92AD398_3993_424C_AC63_11FBDD696750__INCLUDED_)
#define AFX_DLGSCENECHANGEUPDATE_H__C92AD398_3993_424C_AC63_11FBDD696750__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSceneChangeUpdate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSceneChangeUpdate dialog

class CDlgSceneChangeUpdate : public CDialog
{
// Construction
public:
	CDlgSceneChangeUpdate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSceneChangeUpdate)
	enum { IDD = IDD_DLG_SCENE_CHANGE_UPDATE };
	CComboBox	m_cmbStreamID;
	CString	m_csStreamID;
	int		m_nStreamIDNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSceneChangeUpdate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSceneChangeUpdate)
	afx_msg void OnBtnCtrl();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	NET_DVR_SCENE_CHANGE_UPDATE_PARAM m_StruSceneChangeUpdateParam;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCENECHANGEUPDATE_H__C92AD398_3993_424C_AC63_11FBDD696750__INCLUDED_)
