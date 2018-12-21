// DlgWallVirLED.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallVirLED.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWallVirLED dialog


CDlgWallVirLED::CDlgWallVirLED(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallVirLED::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWallVirLED)
	m_byFontColU = 0;
	m_byFontColV = 0;
	m_byFontColY = 0;
	m_dwHeight = 0;
	m_dwLEDNo = 1;
	m_dwWallNo = 1;
	m_dwWidth = 0;
	m_dwX = 0;
	m_dwY = 0;
	m_csLEDContent = _T("");
	m_byBackgroundU = 0;
	m_byBackgroundV = 0;
	m_byBackgroundY = 0;
	m_BEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgWallVirLED::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWallVirLED)
	DDX_Control(pDX, IDC_COMB_VLED_MOVESPEED, m_cmbMoveSpeed);
	DDX_Control(pDX, IDC_COMB_VLED_MOVEDIRECTION, m_cmbMoveDirection);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_VIR_MOVEMODE, m_CombMoveMode);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_VIR_FONTSIZE, m_CombFontSize);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_VIR_DISMODE, m_CombDisplayMode);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_FONTCOLORU, m_byFontColU);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_FONTCOLORV, m_byFontColV);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_FONTCOLORY, m_byFontColY);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_HEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_LEDNO, m_dwLEDNo);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_WALLNO, m_dwWallNo);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_WIDTH, m_dwWidth);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_XCOORDINATE, m_dwX);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_VIR_YCOORDINATE, m_dwY);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_VIR_LEDCONTENT, m_csLEDContent);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_BACKGROUNDU, m_byBackgroundU);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_BACKGROUNDV, m_byBackgroundV);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_VIR_BACKGROUNDY, m_byBackgroundY);
	DDX_Check(pDX, IDC_CHK_VIDEOWALL_VIR_LEDENABLE, m_BEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallVirLED, CDialog)
	//{{AFX_MSG_MAP(CDlgWallVirLED)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_VIR_REFRESH, OnBtnVirRefresh)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_VIR_LEDSET, OnBtnVirLedset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallVirLED message handlers

void CDlgWallVirLED::OnBtnVirRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_VIRTUALLED_PARAM struVirPapam = {0}; 
    struVirPapam.dwSize = sizeof(struVirPapam);
    DWORD dwChannelEx = m_dwLEDNo + (m_dwWallNo << 24); 
    DWORD dwRet;
    CString csError; 
    if ( !NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIRTUALLED, dwChannelEx, &struVirPapam, sizeof(struVirPapam),  &dwRet))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIRTUALLED");
        csError.Format("À¢–¬–Èƒ‚LED Ù–‘ ß∞‹, Error Code %d", NET_DVR_GetLastError()); 
        AfxMessageBox(csError); 
        return ; 
    }
    m_BEnable = struVirPapam.byEnable; 
    m_CombDisplayMode.SetCurSel(struVirPapam.byDispMode-1); 
    m_byFontColY = struVirPapam.struContentColor.byRed; 
    m_byFontColU = struVirPapam.struContentColor.byGreen; 
    m_byFontColV = struVirPapam.struContentColor.byBlue;
    m_byBackgroundY = struVirPapam.struBackColor.byRed; 
    m_byBackgroundU = struVirPapam.struBackColor.byGreen; 
    m_byBackgroundV = struVirPapam.struBackColor.byBlue; 

    m_csLEDContent.Format("%s", (char *)struVirPapam.byLedContent); 
    m_CombFontSize.SetCurSel(struVirPapam.byFontSize-1); 
    m_CombMoveMode.SetCurSel(struVirPapam.byMoveMode-1); 
    m_cmbMoveDirection.SetCurSel(struVirPapam.byMoveDirection-1); 
    m_cmbMoveSpeed.SetCurSel(struVirPapam.byMoveSpeed-1); 
    m_dwX = struVirPapam.struRect.dwXCoordinate ; 
    m_dwY = struVirPapam.struRect.dwYCoordinate; 
    m_dwWidth = struVirPapam.struRect.dwWidth; 
    m_dwHeight = struVirPapam.struRect.dwHeight; 
    UpdateData(FALSE); 
}

void CDlgWallVirLED::OnBtnVirLedset() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_VIRTUALLED_PARAM struVirPapam = {0}; 
    UpdateLedPapam(struVirPapam);
    DWORD dwChannelEx = m_dwLEDNo + (m_dwWallNo << 24); 
    CString csError; 
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_VIRTUALLED, dwChannelEx, &struVirPapam, sizeof(struVirPapam)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIRTUALLED");
        csError.Format("…Ë÷√–Èƒ‚LED Ù–‘ ß∞‹, Error Code %d", NET_DVR_GetLastError()); 
        AfxMessageBox(csError); 
        return ; 
    }
    OnBtnVirRefresh(); 
}

BOOL CDlgWallVirLED::UpdateLedPapam(NET_DVR_VIRTUALLED_PARAM &Papam)
{
    UpdateData(TRUE); 
    Papam.dwSize = sizeof(Papam);
    Papam.byEnable = m_BEnable; 
    Papam.byDispMode = m_CombDisplayMode.GetCurSel()+1; 
    Papam.struContentColor.byRed = m_byFontColY; 
    Papam.struContentColor.byGreen = m_byFontColU; 
    Papam.struContentColor.byBlue = m_byFontColV; 
    Papam.struBackColor.byRed    = m_byBackgroundY; 
    Papam.struBackColor.byGreen = m_byBackgroundU; 
    Papam.struBackColor.byBlue = m_byBackgroundV; 

    strcpy((char *)Papam.byLedContent, (LPCTSTR)m_csLEDContent);
    Papam.dwContentNum  = strlen((char *)Papam.byLedContent); 
    Papam.byFontSize = m_CombFontSize.GetCurSel() +1; 
    Papam.byMoveMode = m_CombMoveMode.GetCurSel() +1; 
    Papam.byMoveSpeed = m_cmbMoveSpeed.GetCurSel() +1; 
    Papam.byMoveDirection = m_cmbMoveDirection.GetCurSel() +1; 
    Papam.struRect.dwXCoordinate = m_dwX; 
    Papam.struRect.dwYCoordinate = m_dwY; 
    Papam.struRect.dwWidth = m_dwWidth; 
    Papam.struRect.dwHeight = m_dwHeight; 
    return TRUE; 
}
