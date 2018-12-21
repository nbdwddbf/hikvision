// DlgVideoIntercomAlarmCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomAlarmCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgVideoIntercomAlarmCfg dialog


DlgVideoIntercomAlarmCfg::DlgVideoIntercomAlarmCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVideoIntercomAlarmCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgVideoIntercomAlarmCfg)
	m_byDoorNotCloseAlarm = FALSE;
	//}}AFX_DATA_INIT
}


void DlgVideoIntercomAlarmCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgVideoIntercomAlarmCfg)
	DDX_Check(pDX, IDC_CHECK_NOT_CLOSE_DOOR, m_byDoorNotCloseAlarm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgVideoIntercomAlarmCfg, CDialog)
	//{{AFX_MSG_MAP(DlgVideoIntercomAlarmCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgVideoIntercomAlarmCfg message handlers

void DlgVideoIntercomAlarmCfg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    DWORD dwReturn;

    NET_DVR_VIDEO_INTERCOM_ALARM_CFG struAlarmCfg ={0};
    if(NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_VIDEO_INTERCOM_ALARM_CFG,0,&struAlarmCfg,sizeof(struAlarmCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEO_INTERCOM_ALARM_CFG SUCC");
        g_StringLanType(szLan, "获取成功", "NET_DVR_GET_VIDEO_INTERCOM_ALARM_CFG successed!");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEO_INTERCOM_ALARM_CFG Failed");
        g_StringLanType(szLan, "获取失败", "NET_DVR_GET_VIDEO_INTERCOM_ALARM_CFG failed!");
        AfxMessageBox(szLan);
    }
    m_byDoorNotCloseAlarm = struAlarmCfg.byDoorNotCloseAlarm;
    UpdateData(FALSE);

}

void DlgVideoIntercomAlarmCfg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_VIDEO_INTERCOM_ALARM_CFG struAlarmCfg ={0};
    struAlarmCfg.byDoorNotCloseAlarm = m_byDoorNotCloseAlarm;
    struAlarmCfg.dwSize = sizeof(struAlarmCfg);
    
    char szLan[128] = {0};
    if(NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_VIDEO_INTERCOM_ALARM_CFG,0,&struAlarmCfg,sizeof(struAlarmCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEO_INTERCOM_ALARM_CFG SUCC");
        g_StringLanType(szLan, "设置成功", "NET_DVR_SET_VIDEO_INTERCOM_ALARM_CFG successed!");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEO_INTERCOM_ALARM_CFG Failed");
        g_StringLanType(szLan, "设置失败", "NET_DVR_SET_VIDEO_INTERCOM_ALARM_CFG failed!");
        AfxMessageBox(szLan);
    }
}
