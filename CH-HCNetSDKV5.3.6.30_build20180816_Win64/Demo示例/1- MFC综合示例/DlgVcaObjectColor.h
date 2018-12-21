#if !defined(AFX_CDLGVCAOBJECTCOLOR_H__A7213137_C52B_4A88_A120_1EF8603E44BB__INCLUDED_)
#define AFX_CDLGVCAOBJECTCOLOR_H__A7213137_C52B_4A88_A120_1EF8603E44BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// CDlgVcaObjectColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaObjectColor dialog

class CDlgVcaObjectColor : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaObjectColor(CWnd* pParent = NULL);   // standard constructor
	~CDlgVcaObjectColor();

// Dialog Data
	//{{AFX_DATA(CDlgVcaObjectColor)
	enum { IDD = IDD_DLG_VCA_OBJECT_COLOR };
	CComboBox	m_comboColorMode;
	CComboBox	m_comboPicType;
	CComboBox	m_comboObjType;
	int		m_nColorHue;
	int		m_nColorBrightNess;
	int		m_nColorSaturation;
	CString	m_strPicPath;
	int		m_nPicHeight;
	int		m_nPicWidth;
	BOOL	m_bEnable;
	//}}AFX_DATA
    
	enum
	{
		COLOR_MODE_RGB = 1,
		COLOR_MODE_PIC = 2
	};

	enum
	{
		PIC_TYPE_JPG  = 1
	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaObjectColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaObjectColor)
	afx_msg void OnBtnSelPic();
	afx_msg void OnBtnSavePic();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboColorMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void InitCtrlState();
	void GetPicSize(CString strFilePath);
	BOOL ReadPicData(CString strFilePath);
	BOOL ExportPicData(CString strFilePath);
	void LoadWndContent();
	void SaveWndContent();
	BOOL GetObjectColor();
	BOOL SetObjectColor();
private:
	BYTE* m_pPicBuffer;
	DWORD m_nPicBufferLen;
	DWORD m_nPicDataLen;
	NET_DVR_OBJECT_COLOR m_struObjectColor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDLGVCAOBJECTCOLOR_H__A7213137_C52B_4A88_A120_1EF8603E44BB__INCLUDED_)
