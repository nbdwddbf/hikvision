// DlgRemoteControllerManage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteControllerManage.h"
#include "DlgRemoteControllerCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControllerManage dialog

DWORD WINAPI CDlgRemoteControllerManage::GetConfigThread(LPVOID lpArg)
{
	CDlgRemoteControllerManage* pThis = reinterpret_cast<CDlgRemoteControllerManage*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struRemoteControllerCfg, sizeof(pThis->m_struRemoteControllerCfg));
		if (bRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddInfoToDlg();  
		}
		else
		{
			if (bRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (bRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				g_StringLanType(szLan, "获取配置结束!", "Get route info Ending");
				g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szLan);
				//AfxMessageBox(szLan);
				break;
			}
			else if(bRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取配置失败!", "Get route info failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "未知状态", "Unknown status");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	if (-1 != pThis->m_lHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lHandle = -1;
		}
	}
	return 0 ;
}


void CDlgRemoteControllerManage::AddInfoToDlg() 
{
	//遥控器号
	if(m_struRemoteControllerCfg.wRemoteCtrllerID <= 0 || m_struRemoteControllerCfg.wRemoteCtrllerID > 32)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struRemoteControllerCfg.wRemoteCtrllerID);
	}
	m_listctrlRemoteController.InsertItem(m_iRowCount,m_sTemp);
	m_listctrlRemoteController.SetItemText(m_iRowCount, 1, m_sTemp);
	m_listctrlRemoteController.SetItemData(m_iRowCount, m_struRemoteControllerCfg.wRemoteCtrllerID);
	
	//序列号
	sprintf(m_sTemp, "%s", (char*)m_struRemoteControllerCfg.sDevSn, 16);
	m_listctrlRemoteController.SetItemText(m_iRowCount, 2, m_sTemp);
	
	//键盘地址
	if(0xff == m_struRemoteControllerCfg.byKeyboardAddr)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struRemoteControllerCfg.byKeyboardAddr);
	}
	m_listctrlRemoteController.SetItemText(m_iRowCount, 3, m_sTemp);
	
	//子系统号
	if(0xff == m_struRemoteControllerCfg.bySubSystemID)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struRemoteControllerCfg.bySubSystemID);
	}
	m_listctrlRemoteController.SetItemText(m_iRowCount, 4, m_sTemp);

    //是否允许常开
    if (0 == m_struRemoteControllerCfg.byAlwaysOpenRight)
    {
        sprintf(m_sTemp, "--");
    }
    else if (1 == m_struRemoteControllerCfg.byAlwaysOpenRight)
    {
        sprintf(m_sTemp, "Not Allow");
    }
    else
    {
        sprintf(m_sTemp, "Allow");
    }
    m_listctrlRemoteController.SetItemText(m_iRowCount, 5, m_sTemp);

    //开门方向
    if (0 == m_struRemoteControllerCfg.byOpeningDirection)
    {
        sprintf(m_sTemp, "--");
    }
    else if (1 == m_struRemoteControllerCfg.byOpeningDirection)
    {
        sprintf(m_sTemp, "Indoor Direction");
    }
    else
    {
        sprintf(m_sTemp, "Outdoor Direction");
    }
    m_listctrlRemoteController.SetItemText(m_iRowCount, 6, m_sTemp);
	
	m_iRowCount++;
}


CDlgRemoteControllerManage::CDlgRemoteControllerManage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteControllerManage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteControllerManage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struRemoteControllerCfg,0,sizeof(m_struRemoteControllerCfg));
	m_lHandle = -1;
}


void CDlgRemoteControllerManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteControllerManage)
	DDX_Control(pDX, IDC_LIST_REMOTE_CONTROLLER, m_listctrlRemoteController);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteControllerManage, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteControllerManage)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControllerManage message handlers

BOOL CDlgRemoteControllerManage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char sTemp[256];
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listctrlRemoteController.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_listctrlRemoteController.InsertColumn(0, "1", LVCFMT_LEFT, 80, -1);
	g_StringLanType(sTemp, "遥控器号", "RemoteController No");
	m_listctrlRemoteController.InsertColumn(1, sTemp, LVCFMT_LEFT, 80, -1);
	g_StringLanType(sTemp, "序列号", "Serial No");
	m_listctrlRemoteController.InsertColumn(2, sTemp, LVCFMT_LEFT, 150, -1);
	g_StringLanType(sTemp, "键盘地址", "Keyboard Addr");
	m_listctrlRemoteController.InsertColumn(3, sTemp, LVCFMT_LEFT, 80, -1);
	g_StringLanType(sTemp, "子系统号", "Subsystem No");
	m_listctrlRemoteController.InsertColumn(4, sTemp, LVCFMT_LEFT, 80, -1);
    g_StringLanType(sTemp, "是否允许常开", "Always Open Right");
    m_listctrlRemoteController.InsertColumn(5, sTemp, LVCFMT_LEFT, 80, -1);
    g_StringLanType(sTemp, "开门方向", "Opening Direction");
    m_listctrlRemoteController.InsertColumn(6, sTemp, LVCFMT_LEFT, 80, -1);
	
	return TRUE;
}

void CDlgRemoteControllerManage::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	m_listctrlRemoteController.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_ALL_REMOTECONTROLLER_LIST, NULL, 0, NULL, this);
		if (m_lHandle >= 0)
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetConfigThread), this, 0, &dwThreadId);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}

void CDlgRemoteControllerManage::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	BOOL bIsDeleted = FALSE;
	CString str;
	for(int i = 0; i < m_listctrlRemoteController.GetItemCount(); i++ )
	{
		if( m_listctrlRemoteController.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listctrlRemoteController.GetCheck(i))
		{
 			//str.Format(_T("第%d行的checkbox为选中状态"), i+1);
 			//AfxMessageBox(str);
			//int iRemoteControllerID = i + 1;
			int iRemoteControllerID = m_listctrlRemoteController.GetItemData(i);

			NET_DVR_REMOTECONTROLLER_PERMISSION_CFG struRemoteControllerCfg = {0};
			struRemoteControllerCfg.dwSize = sizeof(NET_DVR_REMOTECONTROLLER_PERMISSION_CFG);
			//strncpy((char*)struRemoteControllerCfg.sDevSn, "000000000", 16);
			//struRemoteControllerCfg.wRemoteCtrllerID = iRemoteControllerID;
			//struRemoteControllerCfg.byEnable = 0;
            struRemoteControllerCfg.bySubSystemID = 1;
            struRemoteControllerCfg.byEnableDel = 1;

			if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_REMOTECONTROLLER_PERMISION_CFG, iRemoteControllerID, &struRemoteControllerCfg, sizeof(struRemoteControllerCfg)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REMOTECONTROLLER_PERMISION_CFG");
				bIsDeleted = TRUE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REMOTECONTROLLER_PERMISION_CFG");
			}
		}
     }
	
	if (bIsDeleted)
	{
		OnBtnGet();
	}
}

void CDlgRemoteControllerManage::OnBtnAdd()
{
	// TODO: Add your control notification handler code here
	CDlgRemoteControllerCfg dlg;

    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.m_lUserID = m_lUserID;

	dlg.DoModal();

	OnBtnGet();
}
