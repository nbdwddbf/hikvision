// DlgLcdServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdServer.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdServer dialog


CDlgLcdServer::CDlgLcdServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdServer)
	m_bEable = FALSE;
	m_csCode = _T("");
	m_csIP = _T("");
	m_csPassWord = _T("");
	m_dwPort = 0;
	m_csUserName = _T("");
	m_dwWallNo = 1;
	m_bEnablePos = FALSE;
	//}}AFX_DATA_INIT
    m_iLastSel = -1;
}


void CDlgLcdServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdServer)
	DDX_Control(pDX, IDC_COMBO_LCD_OPERATE_TYPE, m_comboLcdOperateType);
	DDX_Control(pDX, IDC_COMBO_POS_Y, m_comboY);
	DDX_Control(pDX, IDC_COMBO_POS_X, m_comboX);
	DDX_Control(pDX, IDC_COMBO_ADD_TYPE, m_comboAddType);
	DDX_Control(pDX, IDC_COMBO_SCREEN_INDEX, m_comboScreenIndex);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEable);
	DDX_Text(pDX, IDC_EDIT_CODE, m_csCode);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassWord);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_WALL_NO, m_dwWallNo);
	DDX_Check(pDX, IDC_CHK_ENABLE_POS, m_bEnablePos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdServer, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdServer)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_CBN_SELCHANGE(IDC_COMBO_SCREEN_INDEX, OnSelchangeComboScreenIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_ADD_TYPE, OnSelchangeComboAddType)
	ON_BN_CLICKED(IDC_BTN_SET_ALL, OnBtnSetAll)
	ON_BN_CLICKED(IDC_BTN_SET_SINGLE, OnBtnSetSingle)
	ON_BN_CLICKED(IDC_BTN_GET_SINGLE, OnBtnGetSingle)
	ON_BN_CLICKED(IDC_BTN_LCD_OPERATE, OnBtnLcdOperate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdServer message handlers

BOOL CDlgLcdServer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    int i = 0;
    CString csTemp;
    for (i = 0; i < SCREEN_NUM; i++)
    {
        csTemp.Format("%d", i + 1);
        m_comboScreenIndex.AddString(csTemp);
    }

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    memset(m_struScreenIndex, 0, sizeof(m_struScreenIndex));
    memset(m_struPosition, 0, sizeof(m_struPosition));
    memset(m_dwStatusListIndex, 0, sizeof(m_dwStatusListIndex));
    memset(m_dwStatusListPos, 0, sizeof(m_dwStatusListPos));

	for (i = 0; i < SCREEN_NUM; i++)
	{
        m_dwIndex[i] = (i + 1) | 0x01000000;
        m_struScreenIndex[i].dwSize = sizeof(m_struScreenIndex[i]); 
        m_struPosition[i].dwSize = sizeof(m_struPosition[i]); 
	}

    OnBtnGetAll();
    OnSelchangeComboAddType();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdServer::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[64] = {0};

    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_SCREEN_INDEX_GET, SCREEN_NUM, m_dwIndex, sizeof(m_dwIndex), m_dwStatusListIndex, m_struScreenIndex, sizeof(m_struScreenIndex)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_INDEX_GET");
        g_StringLanType(szLan, "获取屏幕索引参数失败", "Get Screen index parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_INDEX_GET");        
    }

    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_SCREEN_POSITION, SCREEN_NUM, m_dwIndex, sizeof(m_dwIndex), m_dwStatusListPos, m_struPosition, sizeof(m_struPosition)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_POSITION");
        g_StringLanType(szLan, "获取屏幕位置参数失败", "Get Screen position parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_POSITION");
    }

    OnSelchangeComboScreenIndex();
}

void CDlgLcdServer::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}

void CDlgLcdServer::OnSelchangeComboScreenIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
    int iSel = m_comboScreenIndex.GetCurSel();

    if (iSel == CB_ERR)
    {
        return;
    }
    
    if (iSel != m_iLastSel)
    {
        SaveCurrentData();
    }    

    m_bEable = m_struScreenIndex[iSel].byEnbale;
    m_comboAddType.SetCurSel(m_struScreenIndex[iSel].byDevAddType);
    OnSelchangeComboAddType();
    if (m_struScreenIndex[iSel].byDevAddType == 0)
    {
        m_csCode = m_struScreenIndex[iSel].struScreenBaseInfo.byScreenAddress;
    }
    else
    {
        m_csIP = m_struScreenIndex[iSel].struScreenBaseInfo.struIPInfo.struIPAddr.sIpV4;
        m_dwPort = m_struScreenIndex[iSel].struScreenBaseInfo.struIPInfo.wPort;
        m_csUserName = m_struScreenIndex[iSel].struScreenBaseInfo.struIPInfo.byUserName;
        m_csPassWord = m_struScreenIndex[iSel].struScreenBaseInfo.struIPInfo.byPassWord;
    }

    m_bEnablePos = m_struPosition[iSel].byEnable;
    if (m_bEnablePos)
    {
        m_dwWallNo = m_struPosition[iSel].dwVideoWallNo >> 24;
        m_comboX.SetCurSel(m_struPosition[iSel].struRectCfg.dwXCoordinate/1920);
        m_comboY.SetCurSel(m_struPosition[iSel].struRectCfg.dwYCoordinate/1920);
    }
    else
    {
        m_dwWallNo = 0;
        m_comboX.SetCurSel(CB_ERR);
        m_comboY.SetCurSel(CB_ERR);
    }

    m_iLastSel = iSel;
    UpdateData(FALSE);
}

void CDlgLcdServer::OnSelchangeComboAddType() 
{
	// TODO: Add your control notification handler code here
	
    int iSel = m_comboAddType.GetCurSel();

    if (iSel == CB_ERR)
    {
        GetDlgItem(IDC_STATIC_IP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_IP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PSW)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_CODE)->ShowWindow(SW_HIDE);
    }
    else if (iSel == 1)
    {
        GetDlgItem(IDC_STATIC_IP)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_IP)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PSW)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_CODE)->ShowWindow(SW_HIDE);
    }
    else if (iSel == 0)
    {
        GetDlgItem(IDC_STATIC_IP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_IP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PSW)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CODE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_CODE)->ShowWindow(SW_SHOW);
    }
}

void CDlgLcdServer::OnBtnSetAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int i = 0;
    char szLan[64] = {0};

    for (i = 0; i < SCREEN_NUM; i++)
    {
        m_struScreenIndex[i].dwSize = sizeof(NET_DVR_SCREEN_INDEX_CFG);
    }

    for (i = 0; i < SCREEN_NUM; i++)
    {
        m_struPosition[i].dwSize = sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION);
    }

    SaveCurrentData();

    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SCREEN_INDEX_SET, SCREEN_NUM, m_dwIndex, sizeof(m_dwIndex), m_dwStatusListIndex, \
        m_struScreenIndex, sizeof(m_struScreenIndex)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_INDEX_SET");
        g_StringLanType(szLan, "设置屏幕索引参数失败", "Set screen index parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_INDEX_SET");
    }

    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_SCREEN_POSITION, SCREEN_NUM, m_dwIndex, sizeof(m_dwIndex), m_dwStatusListPos, \
        m_struPosition, sizeof(m_struPosition)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_POSITION");
        g_StringLanType(szLan, "设置屏幕位置参数失败", "Set screen position parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_POSITION");
    }
}

void CDlgLcdServer::SaveCurrentData()
{
    UpdateData(TRUE);
    if (m_iLastSel == CB_ERR)
    {
        return;
    }
    memset( &m_struScreenIndex[m_iLastSel], 0 , sizeof(m_struScreenIndex[m_iLastSel])); 
    m_struScreenIndex[m_iLastSel].dwSize = sizeof(m_struScreenIndex[m_iLastSel]); 
    m_struScreenIndex[m_iLastSel].byEnbale = m_bEable;
    m_struScreenIndex[m_iLastSel].byDevAddType = m_comboAddType.GetCurSel();
    if (m_struScreenIndex[m_iLastSel].byDevAddType == 1)
    {
        memcpy(m_struScreenIndex[m_iLastSel].struScreenBaseInfo.struIPInfo.struIPAddr.sIpV4, m_csIP, min(16, m_csIP.GetLength()));
        m_struScreenIndex[m_iLastSel].struScreenBaseInfo.struIPInfo.wPort = m_dwPort;
        memcpy(m_struScreenIndex[m_iLastSel].struScreenBaseInfo.struIPInfo.byUserName, m_csUserName, min(NAME_LEN, m_csUserName.GetLength()));
        memcpy(m_struScreenIndex[m_iLastSel].struScreenBaseInfo.struIPInfo.byPassWord, m_csPassWord, min(PASSWD_LEN, m_csPassWord.GetLength()));
    }
    else
    {
        memcpy(m_struScreenIndex[m_iLastSel].struScreenBaseInfo.byScreenAddress, m_csCode, min(MAX_SCREEN_ADDRESS_LEN, m_csCode.GetLength()));
    }

    m_struPosition[m_iLastSel].byEnable = m_bEnablePos;
    m_struPosition[m_iLastSel].dwVideoWallNo = m_dwWallNo << 24;
    if (m_comboX.GetCurSel() == CB_ERR)
    {
        m_struPosition[m_iLastSel].struRectCfg.dwXCoordinate = 0;
    }
    else
    {
        m_struPosition[m_iLastSel].struRectCfg.dwXCoordinate = m_comboX.GetCurSel() * 1920;
    }
    
    if (m_comboY.GetCurSel() == CB_ERR)
    {
        m_struPosition[m_iLastSel].struRectCfg.dwYCoordinate = 0;
    }
    else
    {
        m_struPosition[m_iLastSel].struRectCfg.dwYCoordinate = m_comboY.GetCurSel() * 1920;
    }
}

void CDlgLcdServer::OnBtnSetSingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (m_iLastSel == -1)
    {
        return;
    }
    char szLan[64] = {0};

    SaveCurrentData();
    
    m_struScreenIndex[m_iLastSel].dwSize = sizeof(NET_DVR_SCREEN_INDEX_CFG);

    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SCREEN_INDEX_SET, 1, &m_dwIndex[m_iLastSel], sizeof(m_dwIndex[m_iLastSel]), \
        &m_dwStatusListIndex[m_iLastSel], &m_struScreenIndex[m_iLastSel], sizeof(m_struScreenIndex[m_iLastSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_INDEX_SET");
        g_StringLanType(szLan, "设置屏幕索引参数失败", "Set screen index parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_INDEX_SET");
    }
    
    m_struPosition[m_iLastSel].dwSize = sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION);

    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_SCREEN_POSITION, 1, &m_dwIndex[m_iLastSel], sizeof(m_dwIndex[m_iLastSel]), \
        &m_dwStatusListPos[m_iLastSel], &m_struPosition[m_iLastSel], sizeof(m_struPosition[m_iLastSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_POSITION");
        g_StringLanType(szLan, "设置屏幕位置参数失败", "Set screen position parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_POSITION");
    }
}

void CDlgLcdServer::OnBtnGetSingle() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_iLastSel == -1)
    {
        return;
    }
    char szLan[64] = {0};
    
    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_SCREEN_INDEX_GET, 1, &m_dwIndex[m_iLastSel], sizeof(m_dwIndex[m_iLastSel]), \
        &m_dwStatusListIndex[m_iLastSel], &m_struScreenIndex[m_iLastSel], sizeof(m_struScreenIndex[m_iLastSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_INDEX_GET");
        g_StringLanType(szLan, "获取屏幕索引参数失败", "Get Screen index parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_INDEX_GET");        
    }
    
    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_SCREEN_POSITION, 1, &m_dwIndex[m_iLastSel], sizeof(m_dwIndex[m_iLastSel]), \
        &m_dwStatusListPos[m_iLastSel], &m_struPosition[m_iLastSel], sizeof(m_struPosition[m_iLastSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_POSITION");
        g_StringLanType(szLan, "获取屏幕位置参数失败", "Get Screen position parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_POSITION");
    }
    
    OnSelchangeComboScreenIndex();
}

#include "DlgScreenCtrl.h"
#include "DlgLcdSplice.h"
#include "DlgLcdParamCfg.h"
#include "DlgLcdScene.h"
#include "DlgLcdSwitchCfg.h"
#include "DlgLcdSerial.h"
#include "DlgVCSExternalMatrix.h"
#include "DlgLcdUserCfg.h"
void CDlgLcdServer::OnBtnLcdOperate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int iSel = m_comboLcdOperateType.GetCurSel();
// 屏幕控制
// 屏幕拼接
// 屏幕相关参数配置
// 屏幕场景
// 屏幕开关机配置
// 串口相关
// 矩阵配置
// 用户参数
    switch (iSel)
    {
    case 0:
        {
            CDlgScreenCtrl dlg;
            dlg.m_lUserID = m_lUserID;
            dlg.DoModal();
        }
    	break;
    case 1:
        {
            CDlgLcdSplice dlg;
            dlg.m_lUserID = m_lUserID;
            dlg.DoModal();
        }
        break;
    case 2:
        {
            CDlgLcdParamCfg dlg;
            dlg.m_lUserId = m_lUserID;
            dlg.DoModal();
        }
        break;
    case 3:
        {
            CDlgLcdScene dlg;
            dlg.m_lUserID = m_lUserID;
            dlg.DoModal();
        }
        break;
    case 4:
        {
            CDlgLcdSwitchCfg dlg;
            dlg.m_lUserId = m_lUserID;
            dlg.DoModal();
        }
        break;
    case 5:
        {
            CDlgLcdSerial dlg;
            dlg.m_lUserId = m_lUserID;
            dlg.DoModal();
        }
        break;
    case 6:
        {
            CDlgVCSExternalMatrix dlg;            
            dlg.DoModal();
        }
        break;
    case 7:
        {
            CDlgLcdUserCfg dlg;
            dlg.m_lUserId = m_lUserID;
            dlg.DoModal();
        }
        break;
    default:
        break;
    }    
}
