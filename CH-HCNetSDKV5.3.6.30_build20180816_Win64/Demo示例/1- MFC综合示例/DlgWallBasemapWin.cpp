// DlgWallBasemapWin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallBasemapWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWallBasemapWin dialog


CDlgWallBasemapWin::CDlgWallBasemapWin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallBasemapWin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWallBasemapWin)
	m_bEnable = FALSE;
	m_bShowEnable = FALSE;
	m_dwBasemapNo = 0;
	m_dwHeight = 0;
	m_byOut1 = 0;
	m_byOut2 = 0;
	m_byOut3 = 0;
	m_byOut4 = 0;
	m_dwWidth = 0;
	m_dwX = 0;
	m_dwY = 0;
	m_byWallNo = 1;
	//}}AFX_DATA_INIT
}


void CDlgWallBasemapWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWallBasemapWin)
	DDX_Control(pDX, IDC_COMBO_BASEMAP_WIN_NO, m_comboBasemapWinNo);
	DDX_Control(pDX, IDC_COMBO_BASEMAP_TYPE, m_comboBasemapType);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHK_SHOW_ENAbLE, m_bShowEnable);
	DDX_Text(pDX, IDC_EDIT_BASEMAP_NUM, m_dwBasemapNo);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDIT_OUT1, m_byOut1);
	DDX_Text(pDX, IDC_EDIT_OUT2, m_byOut2);
	DDX_Text(pDX, IDC_EDIT_OUT3, m_byOut3);
	DDX_Text(pDX, IDC_EDIT_OUT4, m_byOut4);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_dwWidth);
	DDX_Text(pDX, IDC_EDIT_X, m_dwX);
	DDX_Text(pDX, IDC_EDIT_Y, m_dwY);
	DDX_Text(pDX, IDC_EDT_BASEMAP_WALLNO, m_byWallNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallBasemapWin, CDialog)
	//{{AFX_MSG_MAP(CDlgWallBasemapWin)
	ON_BN_CLICKED(IDC_BTN_BASEMAP_WIN_SET, OnBtnBasemapWinSet)
	ON_BN_CLICKED(IDC_BTN_BASEMAP_WIN_GET, OnBtnBasemapWinGet)
	ON_BN_CLICKED(IDC_BTN_BASEMAP_SET, OnBtnBasemapSet)
	ON_BN_CLICKED(IDC_BTN_BASEMAP_GET, OnBtnBasemapGet)
	ON_CBN_SELCHANGE(IDC_COMBO_BASEMAP_TYPE, OnSelchangeComboBasemapType)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTN_CANCLE, OnBtnCancle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallBasemapWin message handlers

BOOL CDlgWallBasemapWin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_dwBasemapNo = 0;
	memset(&m_struBasemapControlCfg, 0 ,sizeof(m_struBasemapControlCfg));
	memset(&m_struBasemapWinCfg, 0, sizeof(m_struBasemapWinCfg));
	m_comboBasemapWinNo.SetCurSel(0); 
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgWallBasemapWin::OnBtnBasemapWinSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[64] = {0};

	if (m_comboBasemapWinNo.GetCurSel() == -1)
	{
		g_StringLanType(szLan, "ÇëÑ¡Ôñµ×Í¼´°¿ÚºÅ", "Please select basemap win no");
		AfxMessageBox(szLan);
		return;		
	}
    
	m_dwBasemapWinNo = m_comboBasemapWinNo.GetCurSel() + 1;
    DWORD dwChannelEx = m_byWallNo; 
    dwChannelEx = m_dwBasemapWinNo + (dwChannelEx << 24); 
	m_struBasemapWinCfg.dwSize = sizeof(m_struBasemapWinCfg);
	m_struBasemapWinCfg.byEnable = m_bEnable;
	m_struBasemapWinCfg.struWinPosition.dwXCoordinate = m_dwX;
	m_struBasemapWinCfg.struWinPosition.dwYCoordinate = m_dwY;
	m_struBasemapWinCfg.struWinPosition.dwHeight = m_dwHeight;
	m_struBasemapWinCfg.struWinPosition.dwWidth = m_dwWidth;

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_BASEMAP_WIN_CFG, dwChannelEx, &m_struBasemapWinCfg, sizeof(m_struBasemapWinCfg)))
	{
        CString csError; 
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BASEMAP_WIN_CFG");
        csError.Format("ÉèÖÃ´°¿ÚÊ§°Ü, Error Code %d",   NET_DVR_GetLastError()); 
		AfxMessageBox(csError);
		return;
	}
	
	AfxMessageBox("Success");
}

void CDlgWallBasemapWin::OnBtnBasemapWinGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	char szLan[64] = {0};
	DWORD dwReturned = 0;

	if (m_comboBasemapWinNo.GetCurSel() == -1)
	{
		g_StringLanType(szLan, "ÇëÑ¡Ôñµ×Í¼´°¿ÚºÅ", "Please select basemap win no");
		MessageBox(szLan);
		return;		
	}

	m_dwBasemapWinNo = m_comboBasemapWinNo.GetCurSel() + 1;
    DWORD dwChannelEx = m_byWallNo; 
    dwChannelEx = m_dwBasemapWinNo + (dwChannelEx << 24); 
	memset(&m_struBasemapWinCfg, 0, sizeof(m_struBasemapWinCfg));
    CString csError; 
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_BASEMAP_WIN_CFG, dwChannelEx, &m_struBasemapWinCfg, sizeof(m_struBasemapWinCfg), &dwReturned))
	{
        csError.Format("»ñÈ¡´°¿ÚÊ§°Ü, Error Code %d",   NET_DVR_GetLastError()); 
		MessageBox(csError);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BASEMAP_WIN_CFG");
		return;
	}

	m_bEnable = m_struBasemapWinCfg.byEnable;
	m_dwX = m_struBasemapWinCfg.struWinPosition.dwXCoordinate;
	m_dwY = m_struBasemapWinCfg.struWinPosition.dwYCoordinate;
	m_dwHeight = m_struBasemapWinCfg.struWinPosition.dwHeight;
	m_dwWidth = m_struBasemapWinCfg.struWinPosition.dwWidth;

	UpdateData(FALSE);
}

void CDlgWallBasemapWin::OnBtnBasemapSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[64] = {0};
    NET_DVR_BASEMAP_CONTROL_CFG struControlCfg ={0}; 
    struControlCfg.dwSize = sizeof(struControlCfg); 
	if (m_comboBasemapWinNo.GetCurSel() == -1)
	{
		g_StringLanType(szLan, "ÇëÑ¡Ôñµ×Í¼´°¿ÚºÅ", "Please select basemap win no");
		AfxMessageBox(szLan);
		return;		
	}	
	m_dwBasemapWinNo = m_comboBasemapWinNo.GetCurSel() + 1;
	
    
	if (m_bShowEnable)
	{
		if (m_comboBasemapType.GetCurSel() == -1)
		{
			g_StringLanType(szLan, "ÇëÑ¡Ôñµ×Í¼ÀàÐÍ", "Please select basemap type");
			AfxMessageBox(szLan);
			return;
		}		
	}
    struControlCfg.byEnable = m_bShowEnable; 
    struControlCfg.byBaseMapType = m_comboBasemapType.GetCurSel() + 1;
    DWORD dwChannelEx = m_byWallNo; 
    dwChannelEx = m_dwBasemapWinNo + (dwChannelEx << 24); 
	if (m_comboBasemapType.GetCurSel() == 0)
	{
		struControlCfg.dwBaseMapNo = m_dwBasemapNo;
	}
	else
	{
		struControlCfg.dwBaseMapNo = (((DWORD)m_byOut1)<<24) | (((DWORD)m_byOut2)<<16) | (((DWORD)m_byOut3)<<8) | ((DWORD)m_byOut4); 
	}
	 
	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_BASEMAP_CFG, dwChannelEx, &struControlCfg, sizeof(struControlCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BASEMAP_CFG");
		CString csError; 
        csError.Format("ÉèÖÃ´°¿Ú²ÎÊýÊ§°Ü, Error Code %d",   NET_DVR_GetLastError()); 
        MessageBox(csError); 
		return;
	}
	OnBtnBasemapGet(); 
}

void CDlgWallBasemapWin::OnBtnBasemapGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[64] = {0};
	DWORD dwReturned = 0;
	if (m_comboBasemapWinNo.GetCurSel() == -1)
	{
		g_StringLanType(szLan, "ÇëÑ¡Ôñµ×Í¼´°¿ÚºÅ", "Please select basemap win no");
		AfxMessageBox(szLan);
		return;		
	}
    
	NET_DVR_BASEMAP_CONTROL_CFG struControlCfg ={0}; 
	m_dwBasemapWinNo = m_comboBasemapWinNo.GetCurSel() + 1;
    DWORD dwChannelEx = m_byWallNo; 
    dwChannelEx = m_dwBasemapWinNo + (dwChannelEx << 24); 
	memset(&m_struBasemapControlCfg, 0, sizeof(m_struBasemapControlCfg));
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_BASEMAP_CFG, dwChannelEx, &struControlCfg, sizeof(struControlCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BASEMAP_CFG");
        CString csError; 
        csError.Format("»ñÈ¡´°¿Ú²ÎÊýÊ§°Ü, Error Code %d",   NET_DVR_GetLastError()); 
        MessageBox(csError); 
		return;
	}
	
	m_bShowEnable = struControlCfg.byEnable;
	m_comboBasemapType.SetCurSel(struControlCfg.byBaseMapType - 1);
    UpdateData(FALSE); 
	OnSelchangeComboBasemapType();
	if (struControlCfg.byBaseMapType == 1)
	{
		m_dwBasemapNo = struControlCfg.dwBaseMapNo;
	}
	else if (struControlCfg.byBaseMapType == 2)
	{
		m_byOut1 = struControlCfg.dwBaseMapNo >> 24;
		m_byOut2 = struControlCfg.dwBaseMapNo >> 16;
		m_byOut3 = struControlCfg.dwBaseMapNo >> 8;
		m_byOut4 = struControlCfg.dwBaseMapNo;
	}
	UpdateData(FALSE);
}

void CDlgWallBasemapWin::OnSelchangeComboBasemapType() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	if (m_comboBasemapType.GetCurSel() == -1)
	{
		return;
	}

	char szLan[64] = {0};

	if (m_comboBasemapType.GetCurSel() == 0)
	{
		g_StringLanType(szLan, "Í¼Æ¬ÐòºÅ", "Picture No");
		GetDlgItem(IDC_STATIC_BASEMAP)->SetWindowText(szLan);
		GetDlgItem(IDC_EDIT_BASEMAP_NUM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_OUT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_OUT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_OUT3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_OUT4)->ShowWindow(SW_HIDE);
	}
	else
	{
		g_StringLanType(szLan, "ÊäÈë¿ÚºÅ", "Input No");
		GetDlgItem(IDC_STATIC_BASEMAP)->SetWindowText(szLan);
		GetDlgItem(IDC_EDIT_BASEMAP_NUM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_OUT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_OUT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_OUT3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_OUT4)->ShowWindow(SW_SHOW);
	}

	UpdateData(FALSE);	
}

void CDlgWallBasemapWin::OnBtnCancle() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
