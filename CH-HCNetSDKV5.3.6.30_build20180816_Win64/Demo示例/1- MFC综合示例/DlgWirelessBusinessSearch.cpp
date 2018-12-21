// DlgWirelessBusinessSearch.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWirelessBusinessSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWirelessBusinessSearch dialog


CDlgWirelessBusinessSearch::CDlgWirelessBusinessSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWirelessBusinessSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWirelessBusinessSearch)
	m_csCommOperatorNum = _T("");
	m_cs3GBusiness = _T("");
	m_csSearchCode = _T("");
	//}}AFX_DATA_INIT
}


void CDlgWirelessBusinessSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWirelessBusinessSearch)
	DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_csCommOperatorNum);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_cs3GBusiness);
	DDX_Text(pDX, IDC_EDIT_CODE, m_csSearchCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWirelessBusinessSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgWirelessBusinessSearch)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWirelessBusinessSearch message handlers

void CDlgWirelessBusinessSearch::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	char szLan[128] = {0};

	NET_DVR_ALARMHOST_WIRELESS_BUSINESS_INFO struAlarmHostWirelessBusinessInfo = {0};
	NET_DVR_ALARMHOST_WIRELESS_BUSINESS_COND struAlarmHostWirelessBusinessCond = {0};

	struAlarmHostWirelessBusinessCond.dwSize = sizeof(NET_DVR_ALARMHOST_WIRELESS_BUSINESS_COND);
	struAlarmHostWirelessBusinessCond.byBusinessType = m_cmbType.GetCurSel();
	strncpy((char*)struAlarmHostWirelessBusinessCond.byCommOperatorNum, m_csCommOperatorNum, NAME_LEN);
	strncpy((char*)struAlarmHostWirelessBusinessCond.byQueryCode, m_csSearchCode, 16);

	DWORD dwStatusList = -1;

	BOOL iRet = NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ALARMHOST_WIRELESS_BUSINNESS_INFO, 1, &struAlarmHostWirelessBusinessCond, sizeof(NET_DVR_ALARMHOST_WIRELESS_BUSINESS_COND),  &dwStatusList, &struAlarmHostWirelessBusinessInfo, sizeof(NET_DVR_ALARMHOST_WIRELESS_BUSINESS_INFO));
	if (!iRet || dwStatusList != 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_WIRELESS_BUSINNESS_INFO FAILED");
		g_StringLanType(szLan, "²éÑ¯Ê§°Ü", "search failed");
		//int iError = NET_DVR_GetLastError();
		MessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_WIRELESS_BUSINNESS_INFO SUCC");
	}

	char sz3GBusiness[1024+1] = {0};
	strncpy(sz3GBusiness, (char*)struAlarmHostWirelessBusinessInfo.by3GBusiness, 1024);
	m_cs3GBusiness.Format("%s", sz3GBusiness);

	UpdateData(FALSE);
}
