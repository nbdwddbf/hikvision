#if !defined(AFX_DLGVCAVQDEVENTRULE_H__B496DE8A_E879_4332_92DB_338AEF06DDE4__INCLUDED_)
#define AFX_DLGVCAVQDEVENTRULE_H__B496DE8A_E879_4332_92DB_338AEF06DDE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaVQDEventRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaVQDEventRule dialog

class CDlgVcaVQDEventRule : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaVQDEventRule(CWnd* pParent = NULL);   // standard constructor
    enum
	{
		ALARM_TRIGGER_MODE_CONTINUOUS = 1,
		ALARM_TRIGGER_MODE_SINGLE = 2
	};
// Dialog Data
	//{{AFX_DATA(CDlgVcaVQDEventRule)
	enum { IDD = IDD_DLG_VCA_VQD_EVENTRULE };
	CComboBox	m_comboTriggerMode;
	CCheckListBox	m_listRecordChan;
    CCheckListBox	m_listOutputChan;
	CComboBox	m_comboVQDEvent;
	int		m_nAlarmThreshold;
	int		m_nTimeInterval;
	BOOL	m_bUploadPic;
	BOOL	m_bEnable;
	BOOL	m_bHandleType_Jpg;
	BOOL	m_bHandleType_Monitor;
	BOOL	m_bHandleType_Output;
	BOOL	m_bHandleType_Sound;
	BOOL	m_bHandleType_Upload;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaVQDEventRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaVQDEventRule)
	afx_msg void OnBtnSetAlarmTime();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void InitCtrlState();
protected:
	void LoadWndContent();
	void SaveWndContent();
	BOOL GetVQDEventRule();
	BOOL SetVQDEventRule();

private:
	NET_DVR_VQD_EVENT_RULE m_struVQDEventRule;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAVQDEVENTRULE_H__B496DE8A_E879_4332_92DB_338AEF06DDE4__INCLUDED_)
