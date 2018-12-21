#if !defined(AFX_DLGBVCALIBPARAMCFG_H__59F187A7_D556_4FFA_9DD6_79FAC18140A8__INCLUDED_)
#define AFX_DLGBVCALIBPARAMCFG_H__59F187A7_D556_4FFA_9DD6_79FAC18140A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBvCalibParamCfg.h : header file
//
// 双目图像矫正参数结构体
typedef struct _BINOC_RECTIFY_PARAM_
{
    float cam_internal_mat[3][3];
    float dist_coeffs[8];
    float rotate_mat[3][3];
    float project_mat[3][4];
}BINOC_RECTIFY_PARAM;

// 左右相机矫正参数
typedef struct _BV_CALIB_PARAM_
{
    float               rot[3][3];
    float               trans[3];
    float               reproject_mat[4][4];
    BINOC_RECTIFY_PARAM l_cam_param;
    BINOC_RECTIFY_PARAM r_cam_param;
}BV_CALIB_PARAM;
/////////////////////////////////////////////////////////////////////////////
// CDlgBvCalibParamCfg dialog

class CDlgBvCalibParamCfg : public CDialog
{
// Construction
public:
	CDlgBvCalibParamCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBvCalibParamCfg)
	enum { IDD = IDD_DLG_BV_CALIB_PARAM_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBvCalibParamCfg)
	protected:
	CComboBox	m_comLensType;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBvCalibParamCfg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lLoginID;
    int     m_iDevIndex;
    LONG    m_lChannel;
protected:
	BOOL    GetBvCalibParam();
    BOOL    SetBvCalibParam();

	void    LoadWndContent();
	void    SaveWndContent();
private:
	float   m_fReprojectMatrix[4][4];  

	float   m_fLCamInternalMatrix[3][3]; 
	float   m_fLDistCoeffs[8];           
	float   m_fLRotateMatrix[3][3];      
	float   m_fLProjectMatrix[3][4];     

	float   m_fRCamInternalMatrix[3][3]; 
	float   m_fRDistCoeffs[8];           
	float   m_fRRotateMatrix[3][3];      
	float   m_fRProjectMatrix[3][4];

    float   m_fRotateMatrix[3][3];
    float   m_fTransMatrix[3];
	NET_DVR_BV_CORRECT_PARAM m_struBvCalibParam;

public:
    afx_msg void OnBnClickedButtonExport();

    bool getBVCorrectParam(NET_DVR_BV_CORRECT_PARAM &bv_correct_param);
    bool toolChangeDvrToBvCalib(NET_DVR_BV_CORRECT_PARAM dvr_calib_param, BV_CALIB_PARAM &bv_calib);
    bool toolExportCalibParamToTxt(char *calib_rst_file_path, BV_CALIB_PARAM calib_param, float focalLenth);
    CString BrowseFolderParam(HWND hWnd, LPCTSTR lpTitle);
    afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBVCALIBPARAMCFG_H__59F187A7_D556_4FFA_9DD6_79FAC18140A8__INCLUDED_)
