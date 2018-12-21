#if !defined(AFX_DLGMODIFYRECORD_H__A589D14A_E163_41F7_8A18_30E9B65BC32D__INCLUDED_)
#define AFX_DLGMODIFYRECORD_H__A589D14A_E163_41F7_8A18_30E9B65BC32D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgModifyRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgModifyRecord dialog

#include "ModifyRecord.h"
class CDlgModifyRecord : public CDialog
{
// Construction
public:
	CDlgModifyRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgModifyRecord)
	enum { IDD = IDD_DLG_MODIFYRECORD };
	CListCtrl	m_lstScreenM;
	CListCtrl	m_lstScreen;
	DWORD	m_dwOutputNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgModifyRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgModifyRecord)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelModify();
	afx_msg void OnBtnModify();
	afx_msg void OnBtnUpdatemodify();
	afx_msg void OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	void DrawList();
private:
	NET_DVR_VIDEOWALLDISPLAYPOSITION m_struWallParam[256];   //位置
	ModRecord m_DispPosBM;  //位置结构体管理

	int m_iCurSel;    //正在选择
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMODIFYRECORD_H__A589D14A_E163_41F7_8A18_30E9B65BC32D__INCLUDED_)
