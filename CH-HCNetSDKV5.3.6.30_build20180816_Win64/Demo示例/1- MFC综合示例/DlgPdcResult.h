#if !defined(AFX_DLGPDCRESULT_H__DF8FC47D_0B2E_41E2_8E88_7CB1EC8195CC__INCLUDED_)
#define AFX_DLGPDCRESULT_H__DF8FC47D_0B2E_41E2_8E88_7CB1EC8195CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPdcResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcResult dialog

class CDlgPdcResult : public CDialog
{
// Construction
public:
	CDlgPdcResult(CWnd* pParent = NULL);   // standard constructor
	~CDlgPdcResult();

// Dialog Data
	//{{AFX_DATA(CDlgPdcResult)
	enum { IDD = IDD_DLG_PDC_RESULT };
	CComboBox	m_cmbChannel;
	CComboBox	m_comReportType;
	CListCtrl	m_lstPdcResult;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	DWORD	m_dwTerminalNo;
	BOOL	m_bEnableProgram;
	DWORD	m_dwScheduleNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPdcResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPdcResult)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetPdcResult();
	afx_msg void OnBtnCleanPdcResult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long  m_lServerID; // 用户ID
    int   m_iDevIndex; // 设备索引
	long  m_lChannel;

	int	 m_iStruCount;
	BOOL m_bGetNext;
	LONG m_lHandle;
	HANDLE m_hGetInfoThread;
	NET_DVR_PDC_QUERY_COND m_struPdcResultCond;
    //	LPNET_DVR_PDC_RESULT m_pStruPdcResult;
    NET_DVR_PDC_RESULT m_struPdcResult;

	static DWORD WINAPI GetPdcResultThread(LPVOID lpPdcResult);
	void AddPdcResultLst(LPNET_DVR_PDC_RESULT lpInter);
    BOOL m_bTriggerPeopleCountingData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPDCRESULT_H__DF8FC47D_0B2E_41E2_8E88_7CB1EC8195CC__INCLUDED_)
