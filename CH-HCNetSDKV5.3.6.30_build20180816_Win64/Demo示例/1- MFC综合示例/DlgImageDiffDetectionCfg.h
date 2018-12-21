#if !defined(AFX_DLGIMAGEDIFFDETECTIONCFG_H__B39FD512_3BFE_4A21_8553_B6C6AE3B03E1__INCLUDED_)
#define AFX_DLGIMAGEDIFFDETECTIONCFG_H__B39FD512_3BFE_4A21_8553_B6C6AE3B03E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
#include "afxwin.h"
// DlgImageDiffDetectionCfg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgImageDiffDetectionCfg dialog

typedef void(CALLBACK *fDrawFun)(
                                 LONG      lRealHandle,
                                 HDC       hDc,
                                 DWORD     dwUser
								 );

class CDlgImageDiffDetectionCfg : public CDialog, public CVcaCommonOperations
{
// Construction
public:
	CDlgImageDiffDetectionCfg(CWnd* pParent = NULL);   // standard constructor
    ~CDlgImageDiffDetectionCfg();
    void DrawRgnFun(HDC hdc);
    enum
    {
        DRAW_TYPE_NONE      = 0, // ²»»­Í¼
        DRAW_TYPE_RECTANGLE = 1 // »­¾ØÐÎÇøÓò
    };

// Dialog Data
	//{{AFX_DATA(CDlgImageDiffDetectionCfg)
	enum { IDD = IDD_DLG_RECORD_IMAGE_DIFF_DETECTION };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImageDiffDetectionCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImageDiffDetectionCfg)
	afx_msg void OnBtnGetImageDiffDetectionCfg();
    afx_msg void OnBtnSetImageDiffDetectionCfg();
    afx_msg void OnBtnClearFrame();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CRect m_rcPlayWnd;
    int m_nCurDrawType;
    BOOL m_bCheckEnabled;
    BYTE m_byThreshold;
    BYTE m_bySensitivity;
    BOOL m_bStart;
    NET_VCA_POLYGON m_struVacPloygon;
public:
    CComboBox m_comboVideoInputType;
    int m_iChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMAGEDIFFDETECTIONCFG_H__B39FD512_3BFE_4A21_8553_B6C6AE3B03E1__INCLUDED_)
