#if !defined(AFX_DLGVCADEVCHANNEL_H__782DD9AC_179A_4CD3_B052_3D16F13B1A84__INCLUDED_)
#define AFX_DLGVCADEVCHANNEL_H__782DD9AC_179A_4CD3_B052_3D16F13B1A84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
#include <vector>
using namespace  std;
// DlgVcaDevChannel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevChannel dialog

class CDlgVcaDevChannel : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaDevChannel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaDevChannel)
	enum { IDD = IDD_DLG_VCA_DEV_CHANNEL };
	CCheckListBox	m_listChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaDevChannel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaDevChannel)
	afx_msg void OnBtnSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetSelChannel(vector<DWORD> vctChannel);
	void GetSelChannel(vector<DWORD>& vctChannel);
protected:
	void InitCtrlState();
private:
	vector<DWORD> m_vctChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADEVCHANNEL_H__782DD9AC_179A_4CD3_B052_3D16F13B1A84__INCLUDED_)
