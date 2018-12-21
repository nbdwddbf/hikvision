#if !defined(AFX_DLGREGIONLIST_H__97E22C71_4CE0_40CB_9C3B_90045C44F4B2__INCLUDED_)
#define AFX_DLGREGIONLIST_H__97E22C71_4CE0_40CB_9C3B_90045C44F4B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRegionList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRegionList dialog
typedef enum tagREGION_TYPE
{
    MASK_REGION = 1,
    REFERENCE_REGION
}REGION_TYPE;

class CDlgRegionList : public CDialog
{
// Construction
public:
	CDlgRegionList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRegionList)
	enum { IDD = IDD_DLG_REGION_LIST };
	CComboBox	m_comboRegionIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRegionList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRegionList)
	afx_msg void OnBtnSetup();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboRegionIndex();
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    DWORD   m_dwRegionType;
    LONG    m_lServerID;
    LONG    m_lChannel;
    LONG    m_iDevIndex;
    NET_DVR_REGION_LIST m_struRegionList;
    NET_DVR_PU_STREAM_CFG m_struPUStream;
    LONG    m_lPUServerID;

    LONG    m_lPlayHandle;
    CRect   m_rcWnd;
    int     m_iCurRegion;

    BOOL m_bCloseIn[MAX_LANE_NUM]; 
    BOOL m_bNeedRedraw[MAX_LANE_NUM]; 
    BOOL m_bMouseMove[MAX_LANE_NUM]; 
    DWORD m_dwPosNum;

    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
    BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);

    BOOL SetMaskRegion();
    BOOL GetMaskRegion();
    BOOL SetReferenceRegion();
    BOOL GetReferenceRegion();


    LONG StartPlay();
    BOOL StopPlay(LONG lPlayHandle);
    void InitDrawParam();
    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREGIONLIST_H__97E22C71_4CE0_40CB_9C3B_90045C44F4B2__INCLUDED_)
