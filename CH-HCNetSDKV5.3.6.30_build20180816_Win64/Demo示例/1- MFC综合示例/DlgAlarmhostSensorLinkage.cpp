// DlgAlarmhostSensorLinkage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmhostSensorLinkage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostSensorLinkage dialog
DWORD WINAPI CDlgAlarmhostSensorLinkage::GetConfigThread(LPVOID lpArg)
{
	CDlgAlarmhostSensorLinkage* pThis = reinterpret_cast<CDlgAlarmhostSensorLinkage*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struSensor, sizeof(pThis->m_struSensor));
		if (bRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddInfoToStru();
			pThis->SetDlgItemText(IDC_PROGRESS_STATIC,"正在获取...");
		}
		else
		{
			if (bRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				pThis->SetDlgItemText(IDC_PROGRESS_STATIC,"等待...");
				Sleep(5);
				continue;
			}
			if (bRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				pThis->SetDlgItemText(IDC_PROGRESS_STATIC,"获取结束...");
				g_StringLanType(szLan, "获取配置结束!", "Get route info Ending");
				g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szLan);
				//AfxMessageBox(szLan);
				break;
			}
			else if(bRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				pThis->SetDlgItemText(IDC_PROGRESS_STATIC,"获取失败...");
				g_StringLanType(szLan, "获取配置失败!", "Get route info failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				pThis->SetDlgItemText(IDC_PROGRESS_STATIC,"未知状态...");
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

void CDlgAlarmhostSensorLinkage::AddInfoToStru()
{
	memcpy(&m_struSensorlist[m_struSensor.byChan],&m_struSensor,sizeof(m_struSensorlist[0]));
}

CDlgAlarmhostSensorLinkage::CDlgAlarmhostSensorLinkage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmhostSensorLinkage::IDD, pParent)
	,m_iDeviceIndex(-1)
	,m_lUserID(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmhostSensorLinkage)
	m_chJointByAlarmType = FALSE;
	//}}AFX_DATA_INIT
	m_lHandle = -1;
}


void CDlgAlarmhostSensorLinkage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmhostSensorLinkage)
	DDX_Control(pDX, IDC_LIST_SIREN_LINKAGE_BY_TYPE, m_listSirenType);
	DDX_Control(pDX, IDC_LIST_ALARMOUT_LINKAGE_BY_TYPE, m_listSensorType);
	DDX_Control(pDX, IDC_COMBO_SENSOR_JOINT_ALARMOUT, m_cmAlarmOutChan);
	DDX_Control(pDX, IDC_COMBO_SENSOR_INDEX, m_cmSensorIndex);
	DDX_Control(pDX, IDC_LIST_SIREN_LINKAGE, m_listSiren);
	DDX_Control(pDX, IDC_LIST_ALARMOUT_LINKAGE, m_listAlarmOut);
	DDX_Check(pDX, IDC_CHECK_JOINT_BY_ALARMTYPE, m_chJointByAlarmType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmhostSensorLinkage, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmhostSensorLinkage)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR_INDEX, OnSelchangeComboSensorIndex)
	ON_BN_CLICKED(IDC_CHECK_JOINT_BY_ALARMTYPE, OnCheckJointByAlarmtype)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR_JOINT_ALARMOUT, OnSelchangeComboSensorJointAlarmout)
	ON_BN_CLICKED(IDC_BTN_GETA_ALL, OnBtnGetaAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostSensorLinkage message handlers

BOOL CDlgAlarmhostSensorLinkage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(&m_struSensor, 0, sizeof(m_struSensor));
	memset(&m_struSensorlist,0,sizeof(m_struSensorlist));
	DWORD dwReturn = 0;
	m_bGetAll = FALSE;
	m_bGetNext = FALSE;
    if (NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility)))
    {
        char szLan[128] = {0};
        g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
    }
    else
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
        return FALSE;
    }	

	CString csStr;
	int i=0;
	for (i=0; i<m_struAlarmHostAbility.wTotalSensorNum; i++)
	{
		csStr.Format("%d", i+1);
		m_cmSensorIndex.AddString(csStr);
	}

	for (i=0; i<m_struAlarmHostAbility.wTotalAlarmOutNum; i++)
	{
		csStr.Format("%d", i+1);
		m_cmAlarmOutChan.AddString(csStr);
	}
	InitListWnd();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmhostSensorLinkage::InitListWnd() 
{
	char szLan[128] = {0};
	int iBitIndex = 0;
	BOOL bBitState = 0;
    m_listAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listSiren.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listSensorType.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listSirenType.SetExtendedStyle(LVS_EX_CHECKBOXES);

	int i = 0; 
	for (i=0; i<m_struAlarmHostAbility.wTotalAlarmOutNum; i++)
	{
		sprintf(szLan, "Alarmout %d", i+1);
		m_listAlarmOut.InsertItem(i, szLan);
	}

	for (i=0; i<m_struAlarmHostAbility.wSirenNum; i++)
	{
		sprintf(szLan, "Siren %d", i+1);
		m_listSiren.InsertItem(i, szLan);
	}
	
	int iIndex = 0;
	m_listSensorType.InsertItem(iIndex++, "Limit1");
	m_listSensorType.InsertItem(iIndex++, "Limit2");
	m_listSensorType.InsertItem(iIndex++, "Limit3");
	m_listSensorType.InsertItem(iIndex++, "Limit4");
	m_listSensorType.InsertItem(iIndex++, "Fault");

	iIndex = 0;
	m_listSirenType.InsertItem(iIndex++, "Limit1");
	m_listSirenType.InsertItem(iIndex++, "Limit2");
	m_listSirenType.InsertItem(iIndex++, "Limit3");
	m_listSirenType.InsertItem(iIndex++, "Limit4");
	m_listSirenType.InsertItem(iIndex++, "Fault");
}



void CDlgAlarmhostSensorLinkage::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	int i = 0;
	int iIndex = m_cmSensorIndex.GetCurSel() + 1;
	m_struSensor.dwSize = sizeof(m_struSensor);

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_SENSOR_JOINT_CFG, iIndex, &m_struSensor, sizeof(m_struSensor), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Get sensor linkage failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Get sensor linkage successful");
	}

	//clear
	for (i=0; i<m_listAlarmOut.GetItemCount(); i++)
	{
		m_listAlarmOut.SetCheck(i, 0);
	}
	
	for (i=0; i<m_listSiren.GetItemCount(); i++)
	{
		m_listSiren.SetCheck(i, 0);
	}
	//set data
	for (i=0; i<m_listAlarmOut.GetItemCount(); i++)
	{
		m_listAlarmOut.SetCheck(i, m_struSensor.bySensorJointAlarmOut[i]);
	}

	for (i=0; i<m_listSiren.GetItemCount(); i++)
	{
		m_listSiren.SetCheck(i, m_struSensor.bySensorJointSiren[i]);
	}

	for (i=0; i<m_listSirenType.GetItemCount(); i++)
	{
		m_listSirenType.SetCheck(i, (BOOL)((m_struSensor.bySesorAlarmTypeJointSiren[0]>>i)&0x01));
	}

	m_cmAlarmOutChan.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboSensorJointAlarmout();
	UpdateData(FALSE);
}

void CDlgAlarmhostSensorLinkage::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	OnBtnSave();
	UpdateData(TRUE);
	int i = 0;	
	for (i=0; i<m_listAlarmOut.GetItemCount(); i++)
	{
		m_struSensor.bySensorJointAlarmOut[i] = m_listAlarmOut.GetCheck(i);
	}

	for (i=0; i<m_listSiren.GetItemCount(); i++)
	{
		m_struSensor.bySensorJointSiren[i] = m_listSiren.GetCheck(i);
	}

	int iIndex = m_cmSensorIndex.GetCurSel() + 1;
	m_struSensor.dwSize = sizeof(m_struSensor);
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMHOST_SENSOR_JOINT_CFG, iIndex, &m_struSensor, sizeof(m_struSensor)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set sensor linkage failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set sensor linkage successful");
	}
}

void CDlgAlarmhostSensorLinkage::OnSelchangeComboSensorIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bGetAll)
	{
		int i = 0;
		int iIndex = m_cmSensorIndex.GetCurSel();
		memcpy(&m_struSensor,&m_struSensorlist[iIndex],sizeof(m_struSensor));
		for (i=0; i<m_listAlarmOut.GetItemCount(); i++)
		{
			m_listAlarmOut.SetCheck(i, 0);
		}
		
		for (i=0; i<m_listSiren.GetItemCount(); i++)
		{
			m_listSiren.SetCheck(i, 0);
		}
		//set data
		for (i=0; i<m_listAlarmOut.GetItemCount(); i++)
		{
			m_listAlarmOut.SetCheck(i, m_struSensor.bySensorJointAlarmOut[i]);
		}
		
		for (i=0; i<m_listSiren.GetItemCount(); i++)
		{
			m_listSiren.SetCheck(i, m_struSensor.bySensorJointSiren[i]);
		}
		
		for (i=0; i<m_listSirenType.GetItemCount(); i++)
		{
			m_listSirenType.SetCheck(i, (BOOL)((m_struSensor.bySesorAlarmTypeJointSiren[0]>>i)&0x01));
		}
		
		m_cmAlarmOutChan.SetCurSel(0);
		UpdateData(FALSE);
		OnSelchangeComboSensorJointAlarmout();
		UpdateData(FALSE);
	}
	else
	{
		OnBtnGet();
	}
}

void CDlgAlarmhostSensorLinkage::OnCheckJointByAlarmtype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(1 == m_chJointByAlarmType)
	{
		GetDlgItem(IDC_LIST_ALARMOUT_LINKAGE_BY_TYPE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CHAN_NO)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_SENSOR_JOINT_ALARMOUT)->ShowWindow(TRUE);
		g_StringLanType(m_szTemp, "模拟量类型联动触发器", "Sensor Type");
		SetDlgItemText(IDC_STATIC1, m_szTemp);
		GetDlgItem(IDC_LIST_ALARMOUT_LINKAGE)->ShowWindow(FALSE);
		GetDlgItem(IDC_BTN_SAVE)->ShowWindow(TRUE);

		g_StringLanType(m_szTemp, "模拟量类型联动警号", "Sensor Type");
		SetDlgItemText(IDC_STATIC2, m_szTemp);
		GetDlgItem(IDC_LIST_SIREN_LINKAGE)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_SIREN_LINKAGE_BY_TYPE)->ShowWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_LIST_ALARMOUT_LINKAGE_BY_TYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_CHAN_NO)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_SENSOR_JOINT_ALARMOUT)->ShowWindow(FALSE);
		g_StringLanType(m_szTemp, "报警输出（触发器）", "Alarmout");
		SetDlgItemText(IDC_STATIC1, m_szTemp);
		GetDlgItem(IDC_LIST_ALARMOUT_LINKAGE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_SAVE)->ShowWindow(FALSE);

		g_StringLanType(m_szTemp, "警号", "Siren");
		SetDlgItemText(IDC_STATIC2, m_szTemp);
		GetDlgItem(IDC_LIST_SIREN_LINKAGE_BY_TYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_SIREN_LINKAGE)->ShowWindow(TRUE);
	}
	UpdateData(FALSE);
}

void CDlgAlarmhostSensorLinkage::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iAlarmoutNo = m_cmAlarmOutChan.GetCurSel();
	BYTE bySensorType = 0;
	m_struSensor.bySensorAlarmTypeJointAlarmOut[iAlarmoutNo] = 0;
	int i=0;
	for (i=0; i<m_listSensorType.GetItemCount(); i++)
	{
		bySensorType = m_listSensorType.GetCheck(i);
		bySensorType = bySensorType << i;
		m_struSensor.bySensorAlarmTypeJointAlarmOut[iAlarmoutNo] |= bySensorType;
	}

	m_struSensor.bySesorAlarmTypeJointSiren[0] = 0;
	for (i=0; i<m_listSirenType.GetItemCount(); i++)
	{
		bySensorType = m_listSirenType.GetCheck(i) << i;
		m_struSensor.bySesorAlarmTypeJointSiren[0] |= bySensorType;
	}
	UpdateData(FALSE);
}

void CDlgAlarmhostSensorLinkage::OnSelchangeComboSensorJointAlarmout() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iAlarmoutNo = m_cmAlarmOutChan.GetCurSel();
	BYTE bySensorType = 0;
	int i=0;
	for (i=0; i<m_listSensorType.GetItemCount(); i++)
	{
		m_listSensorType.SetCheck(i, FALSE);
	}

	for (i=0; i<m_listSensorType.GetItemCount(); i++)
	{
		m_listSensorType.SetCheck(i, (BOOL)((m_struSensor.bySensorAlarmTypeJointAlarmOut[iAlarmoutNo]>>i) & 0x01));
	}
	UpdateData(FALSE);
}


void CDlgAlarmhostSensorLinkage::OnBtnGetaAll() 
{
	// TODO: Add your control notification handler code here
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_ALL_ALARM_SENSOR_JOINT, NULL, 0, NULL, this);
		if (m_lHandle>=0)
		{
			m_bGetNext = TRUE;
			m_bGetAll = TRUE;
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