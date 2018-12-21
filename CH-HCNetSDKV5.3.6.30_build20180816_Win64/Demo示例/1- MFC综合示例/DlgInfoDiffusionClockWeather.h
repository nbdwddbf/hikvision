#if !defined(AFX_DLGINFODIFFUSIONCLOCKWEATHER_H__DDFCF73E_E6C7_4ED5_8C71_4A286C525A98__INCLUDED_)
#define AFX_DLGINFODIFFUSIONCLOCKWEATHER_H__DDFCF73E_E6C7_4ED5_8C71_4A286C525A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionClockWeather.h : header file
//
#include "InfoDiffusionParamsConvert.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionClockWeather dialog

class CDlgInfoDiffusionClockWeather : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionClockWeather(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionClockWeather)
	enum { IDD = IDD_DLG_WEATHER };
	BOOL	m_byAir;
	BOOL	m_byCity;
	BOOL	m_byContent;
	BOOL	m_byHum;
	BOOL	m_byTemp;
	BOOL	m_byUpdate;
	BOOL	m_byDate;
	BOOL	m_byIcon;
	BOOL	m_byWind;
	DWORD	m_dwAirBackB;
	DWORD	m_dwAirBackG;
	DWORD	m_dwAirBackR;
	DWORD	m_dwAirFontB;
	DWORD	m_dwAirFontG;
	DWORD	m_dwAirFontR;
	DWORD	m_dwAirFontSize;
	DWORD	m_dwAirH;
	DWORD	m_dwAirW;
	DWORD	m_dwAirX;
	DWORD	m_dwAirY;
	DWORD	m_dwCityBackB;
	DWORD	m_dwCityBackG;
	DWORD	m_dwCityBackR;
	DWORD	m_dwCityFontB;
	DWORD	m_dwCityFontG;
	DWORD	m_dwCityFontR;
	DWORD	m_dwCityFontSize;
	DWORD	m_dwCityH;
	DWORD	m_dwCityW;
	DWORD	m_dwCityX;
	DWORD	m_dwCityY;
	DWORD	m_dwContentBackB;
	DWORD	m_dwContentBackG;
	DWORD	m_dwContentBackR;
	DWORD	m_dwContentFontB;
	DWORD	m_dwContentFontG;
	DWORD	m_dwContentFontR;
	DWORD	m_dwContentFontSize;
	DWORD	m_dwContentH;
	DWORD	m_dwContentW;
	DWORD	m_dwContentY;
	DWORD	m_dwContentX;
	DWORD	m_dwDateBackB;
	DWORD	m_dwDateBackG;
	DWORD	m_dwDateBackR;
	DWORD	m_dwDateFontB;
	DWORD	m_dwDateFontG;
	DWORD	m_dwDateFontR;
	DWORD	m_dwDateFontSize;
	DWORD	m_dwDateH;
	DWORD	m_dwDateW;
	DWORD	m_dwDateX;
	DWORD	m_dwDateY;
	DWORD	m_dwHumBackB;
	DWORD	m_dwHumBackG;
	DWORD	m_dwHumBackR;
	DWORD	m_dwHumFontB;
	DWORD	m_dwHumFontG;
	DWORD	m_dwHumFontR;
	DWORD	m_dwHumFontSize;
	DWORD	m_dwHumH;
	DWORD	m_dwHumX;
	DWORD	m_dwHumY;
	DWORD	m_dwTempBackB;
	DWORD	m_dwTempBackG;
	DWORD	m_dwTempBackR;
	DWORD	m_dwTempFontB;
	DWORD	m_dwTempFontG;
	DWORD	m_dwTempFontR;
	DWORD	m_dwTempFontSize;
	DWORD	m_dwTempH;
	DWORD	m_dwTempW;
	DWORD	m_dwTempX;
	DWORD	m_dwTempY;
	DWORD	m_dwUpdateBackB;
	DWORD	m_dwUpdateBackG;
	DWORD	m_dwUpdateBackR;
	DWORD	m_dwUpdateFontB;
	DWORD	m_dwUpdateFontG;
	DWORD	m_dwUpdateFontR;
	DWORD	m_dwUpdateFontSize;
	DWORD	m_dwUpdateH;
	DWORD	m_dwUpdateW;
	DWORD	m_dwUpdateX;
	DWORD	m_dwUpdateY;
	DWORD	m_dwWeateBackPic;
	DWORD	m_dwWeaIconW;
	DWORD	m_dwWeaH;
	DWORD	m_dwWeaIconH;
	DWORD	m_dwWeaIconX;
	DWORD	m_dwWeaIconY;
	DWORD	m_dwWeaW;
	DWORD	m_dwWindFontB;
	DWORD	m_dwWindFontG;
	DWORD	m_dwWindFontR;
	DWORD	m_dwWindBackB;
	DWORD	m_dwWindBackG;
	DWORD	m_dwWindBackR;
	DWORD	m_dwWindFontSize;
	DWORD	m_dwWindX;
	DWORD	m_dwWindY;
	DWORD	m_dwWindH;
	DWORD	m_dwHumW;
	DWORD	m_dwWindW;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionClockWeather)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionClockWeather)
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LPNET_DVR_MATERIAL m_struMaterial;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONCLOCKWEATHER_H__DDFCF73E_E6C7_4ED5_8C71_4A286C525A98__INCLUDED_)
