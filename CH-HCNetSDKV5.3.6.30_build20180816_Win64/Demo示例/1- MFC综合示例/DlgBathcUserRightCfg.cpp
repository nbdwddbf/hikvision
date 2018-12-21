// DlgBathcUserRightCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgBathcUserRightCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBathcUserRightCfg dialog


CDlgBathcUserRightCfg::CDlgBathcUserRightCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBathcUserRightCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBathcUserRightCfg)
	m_bAddMonitorPointRight = FALSE;
	m_bModMonitorPointRight = FALSE;
	m_bDelMonitorPointRight = FALSE;
	m_bSetRecordPlanRight = FALSE;
	m_bDelRecordPlanRight = FALSE;
	m_bSetAlarmRecordRight = FALSE;
	m_bRecordBackupRight = FALSE;
	m_bRecordDownloadRight = FALSE;
	m_bRecordDelRight = FALSE;
	m_bBackupRecordDelRight = FALSE;
	m_bSetBackupVolumeRight = FALSE;
	m_bRecordPlayRight = FALSE;
	m_bLogDeleteRight = FALSE;
	m_bLogDownloadRight = FALSE;
	m_bAddUserRight = FALSE;
	m_bDelUserRight = FALSE;
	m_bModUserRight = FALSE;
	m_bAllcoUserRightRight = FALSE;
	m_strPassword = _T("");
	m_strUserName = _T("");
	m_dwStatus = 0;
	m_bRecordPlanRight = FALSE;
	m_bRecordRight = FALSE;
	//}}AFX_DATA_INIT

	for (int i=0; i<32; i++)
	{
		memset(&m_struUserRightCfg[i], 0, sizeof(NET_DVR_USER_RIGHT_CFG));
		memset(&m_struUserCond[i], 0, sizeof(NET_DVR_USER_COND));
	}	
}


void CDlgBathcUserRightCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBathcUserRightCfg)
	DDX_Control(pDX, IDC_LIST_USER, m_lstUserRight);
	DDX_Check(pDX, IDC_CHECK_ADD_MONITOR_POINT_RIGHT, m_bAddMonitorPointRight);
	DDX_Check(pDX, IDC_CHECK_MOD_MONITOR_POINT_RIGHT, m_bModMonitorPointRight);
	DDX_Check(pDX, IDC_CHECK_DEL_MONITOR_POINT_RIGHT, m_bDelMonitorPointRight);
	DDX_Check(pDX, IDC_CHECK_SET_RECORD_PLAN_RIGHT, m_bSetRecordPlanRight);
	DDX_Check(pDX, IDC_CHECK_DEL_RECORD_PLAN_RIGHT, m_bDelRecordPlanRight);
	DDX_Check(pDX, IDC_CHECK_SET_ALARM_RECORD_RIGHT, m_bSetAlarmRecordRight);
	DDX_Check(pDX, IDC_CHECK_RECORD_BACKUP_RIGHT, m_bRecordBackupRight);
	DDX_Check(pDX, IDC_CHECK_RECORD_DOWNLOAD_RIGHT, m_bRecordDownloadRight);
	DDX_Check(pDX, IDC_CHECK_RECORD_DEL_RIGHT, m_bRecordDelRight);
	DDX_Check(pDX, IDC_CHECK_BACKUP_RECORD_DEL_RIGHT, m_bBackupRecordDelRight);
	DDX_Check(pDX, IDC_CHECK_SET_BACUP_VOLUME_RIGHT, m_bSetBackupVolumeRight);
	DDX_Check(pDX, IDC_CHECK_RECORD_PLAY_RIGHT, m_bRecordPlayRight);
	DDX_Check(pDX, IDC_CHECK_LOG_DELETE_RIGHT, m_bLogDeleteRight);
	DDX_Check(pDX, IDC_CHECK_LOG_DOWNLOAD_RIGHT, m_bLogDownloadRight);
	DDX_Check(pDX, IDC_CHECK_ADD_USER_RIGHT, m_bAddUserRight);
	DDX_Check(pDX, IDC_CHECK_DEL_USER_RIGHT, m_bDelUserRight);
	DDX_Check(pDX, IDC_CHECK_MOD_USER_RIGHT, m_bModUserRight);
	DDX_Check(pDX, IDC_CHK_ALLOC_USER_RIGHT_RIGHT, m_bAllcoUserRightRight);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_dwStatus);
	DDX_Check(pDX, IDC_CHECK_RECORD_PLAN_RIGHT, m_bRecordPlanRight);
	DDX_Check(pDX, IDC_CHECK_RECORD_RIGHT, m_bRecordRight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBathcUserRightCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgBathcUserRightCfg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_LIST, OnButtonAddList)
	ON_BN_CLICKED(IDC_BUTTON_DEL_LIST, OnButtonDelList)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, OnClickListUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBathcUserRightCfg message handlers

BOOL CDlgBathcUserRightCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lstUserRight.SetExtendedStyle(m_lstUserRight.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	int iIndex = 0;
	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 50, -1);
	iIndex++;
	
	g_StringLanType(szLan, "用户名", "User name");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "密码", "Password");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "添加监控点权限", "Add Monitor Point Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "修改监控点权限", "Mod Monitor Point Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "删除监控点权限", "Del Monitor Point Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLan, "制定录像计划权限", "Set Record Plan Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;

	g_StringLanType(szLan, "删除录像计划权限", "Del Record Plan Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "录像计划权限", "Valid Record Plan Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLan, "录像权限", "Start Record Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLan, "报警录像设定权限", "Set Alarm Record Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	

	g_StringLanType(szLan, "录像存档权限", "Record Backup Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "录像下载权限", "Record Download Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "录像删除权限", "Record Delete Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "删除存档录像权限", "Del Backup Record Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "设置存档卷权限", "Set Backup Volume Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "录像回放权限", "Record PlayBack Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLan, "日志清空权限", "Log Delete Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "日志下载权限", "Log Download Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "添加用户权限", "Add User Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLan, "删除用户权限", "Del User Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "修改用户权限", "Mod User Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "用户权限分配权限", "Alloc User Right");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "状态", "status");
	m_lstUserRight.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 50, -1);
	iIndex++;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBathcUserRightCfg::OnButtonAddList() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString strTemp;
	
	// 	if ("" == m_strStreamID)
	// 	{
	// 		g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
	// 		AfxMessageBox(szLan);
	// 		return;
	// 	}
	
	int iItemCount = m_lstUserRight.GetItemCount();
	if (iItemCount > 32)
	{
		g_StringLanType(szLan,"超过32个","more than 32");
		AfxMessageBox(szLan);
		return;
	}
	int iIndex = 1;
	strTemp.Format("%02d", iItemCount+1);
	m_lstUserRight.InsertItem(iItemCount, strTemp);
	m_lstUserRight.SetItemText(iItemCount, iIndex, m_strUserName);
	iIndex++;

	m_lstUserRight.SetItemText(iItemCount, iIndex, m_strPassword);
	iIndex++;

	strTemp.Format("%d", m_bAddMonitorPointRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;

	strTemp.Format("%d", m_bModMonitorPointRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;

	strTemp.Format("%d", m_bDelMonitorPointRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;

	strTemp.Format("%d", m_bSetRecordPlanRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;

	strTemp.Format("%d", m_bDelRecordPlanRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;


	strTemp.Format("%d", m_bRecordPlanRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bRecordRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;

	strTemp.Format("%d", m_bSetAlarmRecordRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bRecordBackupRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;

	strTemp.Format("%d", m_bRecordDownloadRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bRecordDelRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bBackupRecordDelRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bSetBackupVolumeRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bRecordPlayRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	
	strTemp.Format("%d", m_bLogDeleteRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bLogDownloadRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bAddUserRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bDelUserRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bModUserRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;
	
	strTemp.Format("%d", m_bAllcoUserRightRight);
	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
	iIndex++;

// 	strTemp.Format("%d", m_dwStatus);
// 	m_lstUserRight.SetItemText(iItemCount, iIndex, strTemp);
// 	iIndex++;
}

void CDlgBathcUserRightCfg::OnButtonDelList() 
{
	// TODO: Add your control notification handler code here
	while(m_lstUserRight.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_lstUserRight.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstUserRight.DeleteItem(nItem);
	}
}

void CDlgBathcUserRightCfg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	LPNET_DVR_USER_RIGHT_CFG pUserRightCfg = &m_struUserRightCfg[0];
	LPNET_DVR_USER_COND pstruUserCond = &m_struUserCond[0];
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstUserRight.GetItemCount();
	if (0 == iItemCount || 1 == iItemCount)
	{
		strncpy((char*)pstruUserCond->szUserName, m_strUserName, NAME_LEN);
		//strncpy((char*)pstruUserCond->szPassword, m_strPassword, NAME_LEN);

		pUserRightCfg->dwSize = sizeof(NET_DVR_USER_RIGHT_CFG);
		pUserRightCfg->byAddMonitoringPointRight = m_bAddMonitorPointRight;
		pUserRightCfg->byModMonitoringPointRight = m_bModMonitorPointRight;
		pUserRightCfg->byDelMonitoringPointRight = m_bDelMonitorPointRight;
		pUserRightCfg->bySetRecordPlanRight = m_bSetRecordPlanRight;
		pUserRightCfg->byDelRecordPlanRight = m_bDelRecordPlanRight;
		pUserRightCfg->byEnableOrDisableRecordPlanRight = m_bRecordPlanRight;
		pUserRightCfg->byManualRecordRight = m_bRecordRight;
		pUserRightCfg->bySetAlarmRecordRight = m_bSetAlarmRecordRight;
		pUserRightCfg->byRecordBackupRight = m_bRecordBackupRight;
		pUserRightCfg->byRecordDownloadRight = m_bRecordDownloadRight;
		pUserRightCfg->byRecordDeleteRight = m_bRecordDelRight;
		pUserRightCfg->byDelBackupRecordRight = m_bBackupRecordDelRight;
		pUserRightCfg->bySetBackupVolumeRight = m_bSetBackupVolumeRight;
		pUserRightCfg->byRecordPlayBackRight = m_bRecordPlayRight;
		pUserRightCfg->byLogDeleteRight = m_bLogDeleteRight;
		pUserRightCfg->byLogDownloadRight = m_bLogDownloadRight;
		pUserRightCfg->byAddUserRight = m_bAddUserRight;
		pUserRightCfg->byDelUserRight = m_bDelUserRight;
		pUserRightCfg->byModUserRight = m_bModUserRight;
		pUserRightCfg->byAllocUserRight = m_bAllcoUserRightRight;


		BOOL bRet = NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_USER_RIGHT_CFG, iItemCount, &m_struUserCond[0], sizeof(NET_DVR_USER_COND), &m_dwStatus, &m_struUserRightCfg[0], sizeof(NET_DVR_USER_RIGHT_CFG));
		if (bRet && (0 == m_dwStatus))
		{
			g_StringLanType(szLan,"设置成功","Succeed to set");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"设置失败","Fail to set");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
		}

	}
	else
	{
		int i = 0; 
		for (i=0; i<iItemCount; i++)
		{
			strncpy((char*)pstruUserCond->szUserName, m_lstUserRight.GetItemText(i, 1), NAME_LEN);
			//strncpy((char*)pstruUserCond->szPassword, m_lstUserRight.GetItemText(i, 2), NAME_LEN);

			pUserRightCfg->dwSize = sizeof(NET_DVR_USER_RIGHT_CFG);
			pUserRightCfg->byAddMonitoringPointRight = atoi(m_lstUserRight.GetItemText(i, 3));
			pUserRightCfg->byModMonitoringPointRight = atoi(m_lstUserRight.GetItemText(i, 4));
			pUserRightCfg->byDelMonitoringPointRight = atoi(m_lstUserRight.GetItemText(i, 5));
			pUserRightCfg->bySetRecordPlanRight = atoi(m_lstUserRight.GetItemText(i, 6));
			pUserRightCfg->byDelRecordPlanRight = atoi(m_lstUserRight.GetItemText(i, 7));
			pUserRightCfg->byEnableOrDisableRecordPlanRight = atoi(m_lstUserRight.GetItemText(i, 8));
			pUserRightCfg->byManualRecordRight = atoi(m_lstUserRight.GetItemText(i, 9));
			pUserRightCfg->bySetAlarmRecordRight = atoi(m_lstUserRight.GetItemText(i, 10));
			pUserRightCfg->byRecordBackupRight = atoi(m_lstUserRight.GetItemText(i, 11));
			pUserRightCfg->byRecordDownloadRight = atoi(m_lstUserRight.GetItemText(i, 12));
			pUserRightCfg->byRecordDeleteRight = atoi(m_lstUserRight.GetItemText(i, 13));
			pUserRightCfg->byDelBackupRecordRight = atoi(m_lstUserRight.GetItemText(i, 14));
			pUserRightCfg->bySetBackupVolumeRight = atoi(m_lstUserRight.GetItemText(i, 15));
			pUserRightCfg->byRecordPlayBackRight = atoi(m_lstUserRight.GetItemText(i, 16));
			pUserRightCfg->byLogDeleteRight = atoi(m_lstUserRight.GetItemText(i, 17));
			pUserRightCfg->byLogDownloadRight = atoi(m_lstUserRight.GetItemText(i, 18));
			pUserRightCfg->byAddUserRight = atoi(m_lstUserRight.GetItemText(i, 19));
			pUserRightCfg->byDelUserRight = atoi(m_lstUserRight.GetItemText(i, 20));
			pUserRightCfg->byModUserRight = atoi(m_lstUserRight.GetItemText(i, 21));
			pUserRightCfg->byAllocUserRight = atoi(m_lstUserRight.GetItemText(i, 22));
	
			pstruUserCond++;
			pUserRightCfg++;
		}

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);

		DWORD *pStatusTemp = pStatus;

		if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_USER_RIGHT_CFG, iItemCount, &m_struUserCond[0], iItemCount*sizeof(NET_DVR_USER_COND), pStatus, &m_struUserRightCfg[0], iItemCount*sizeof(NET_DVR_USER_RIGHT_CFG)))
		{
			g_StringLanType(szLan,"批量设置成功","Succeed to set");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"批量设置失败","Fail to set");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
		}

		for (i=0; i<iItemCount; i++)
		{
			CString strStatus;
			strStatus.Format("%d", *pStatusTemp);
			m_lstUserRight.SetItemText(i, 24, strStatus);
			pStatusTemp++;
		}

		if (NULL != pStatus)
		{
			delete[] pStatus;
			pStatus = NULL;
		}
	}

	UpdateData(FALSE);
}

void CDlgBathcUserRightCfg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};
	DWORD dwReturn = 0;
	CString strTemp;

	LPNET_DVR_USER_RIGHT_CFG pUserRightCfg = &m_struUserRightCfg[0];
	LPNET_DVR_USER_COND pstruUserCond = &m_struUserCond[0];
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstUserRight.GetItemCount();
	
	if (0 == iItemCount || 1 == iItemCount)
	{
		strncpy((char*)pstruUserCond->szUserName, m_strUserName, NAME_LEN);
		//strncpy((char*)pstruUserCond->szPassword, m_strPassword, NAME_LEN);
		
		BOOL bRet = NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_USER_RIGHT_CFG, iItemCount, &m_struUserCond[0], sizeof(NET_DVR_USER_COND), &m_dwStatus, &m_struUserRightCfg[0], sizeof(NET_DVR_USER_RIGHT_CFG));

		if (bRet && (0 == m_dwStatus))
		{
			g_StringLanType(szLan,"获取成功","Success to get");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"获取失败","Fail to get");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
			return;
		}

		m_bAddMonitorPointRight = pUserRightCfg->byAddMonitoringPointRight;
		m_bModMonitorPointRight = pUserRightCfg->byModMonitoringPointRight;
		m_bDelMonitorPointRight = pUserRightCfg->byDelMonitoringPointRight;
		m_bSetRecordPlanRight = pUserRightCfg->bySetRecordPlanRight;
		m_bDelRecordPlanRight = pUserRightCfg->byDelRecordPlanRight;
		m_bRecordPlanRight = pUserRightCfg->byEnableOrDisableRecordPlanRight;
		m_bRecordRight = pUserRightCfg->byManualRecordRight;
		m_bSetAlarmRecordRight = pUserRightCfg->bySetAlarmRecordRight;
		m_bRecordBackupRight = pUserRightCfg->byRecordBackupRight;
		m_bRecordDownloadRight = pUserRightCfg->byRecordDownloadRight;
		m_bRecordDelRight = pUserRightCfg->byRecordDeleteRight;
		m_bBackupRecordDelRight = pUserRightCfg->byDelBackupRecordRight;
		m_bSetBackupVolumeRight = pUserRightCfg->bySetBackupVolumeRight;
		m_bRecordPlayRight = pUserRightCfg->byRecordPlayBackRight;
		m_bLogDeleteRight = pUserRightCfg->byLogDeleteRight;
		m_bLogDownloadRight = pUserRightCfg->byLogDownloadRight;
		m_bAddUserRight = pUserRightCfg->byAddUserRight;
		m_bDelUserRight = pUserRightCfg->byDelUserRight;
		m_bModUserRight = pUserRightCfg->byModUserRight;
		m_bAllcoUserRightRight = pUserRightCfg->byAllocUserRight;

	}
	else
	{
	
		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);
		DWORD *pStatusTemp = pStatus;
			
		int i = 0; 	
		for (i=0; i<iItemCount; i++)
		{
			strncpy((char*)pstruUserCond->szUserName, m_lstUserRight.GetItemText(i, 1), NAME_LEN);
			//strncpy((char*)pstruUserCond->szPassword, m_lstUserRight.GetItemText(i, 2), NAME_LEN);
			pstruUserCond++;
		}

		
		if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_USER_RIGHT_CFG, iItemCount, &m_struUserCond[0], iItemCount*sizeof(NET_DVR_USER_COND), pStatus, &m_struUserRightCfg[0], iItemCount*sizeof(NET_DVR_USER_RIGHT_CFG)))
		{
			g_StringLanType(szLan,"批量获取成功","Success to get");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
		}
		else
		{
			delete[] pStatus;
			g_StringLanType(szLan,"批量获取失败","Fail to get");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_USER_RIGHT_CFG");
			AfxMessageBox(szLan);
			return;
		}

		for (i=0; i<iItemCount; i++)
		{
			strTemp.Format("%d", pUserRightCfg->byAddMonitoringPointRight);
			m_lstUserRight.SetItemText(i, 3, strTemp);

			strTemp.Format("%d", pUserRightCfg->byModMonitoringPointRight);
			m_lstUserRight.SetItemText(i, 4, strTemp);

			strTemp.Format("%d", pUserRightCfg->byDelMonitoringPointRight);
			m_lstUserRight.SetItemText(i, 5, strTemp);

			strTemp.Format("%d", pUserRightCfg->bySetRecordPlanRight);
			m_lstUserRight.SetItemText(i, 6, strTemp);

			strTemp.Format("%d", pUserRightCfg->byDelRecordPlanRight);
			m_lstUserRight.SetItemText(i, 7, strTemp);

			strTemp.Format("%d", pUserRightCfg->byEnableOrDisableRecordPlanRight);
			m_lstUserRight.SetItemText(i, 8, strTemp);

			strTemp.Format("%d", pUserRightCfg->byManualRecordRight);
			m_lstUserRight.SetItemText(i, 9, strTemp);

			strTemp.Format("%d", pUserRightCfg->bySetAlarmRecordRight);
			m_lstUserRight.SetItemText(i, 10, strTemp);

			strTemp.Format("%d", pUserRightCfg->byRecordBackupRight);
			m_lstUserRight.SetItemText(i, 11, strTemp);

			strTemp.Format("%d", pUserRightCfg->byRecordDownloadRight);
			m_lstUserRight.SetItemText(i, 12, strTemp);

			strTemp.Format("%d", pUserRightCfg->byRecordDeleteRight);
			m_lstUserRight.SetItemText(i, 13, strTemp);

			strTemp.Format("%d", pUserRightCfg->byDelBackupRecordRight);
			m_lstUserRight.SetItemText(i, 14, strTemp);

			strTemp.Format("%d", pUserRightCfg->bySetBackupVolumeRight);
			m_lstUserRight.SetItemText(i, 15, strTemp);

			strTemp.Format("%d", pUserRightCfg->byRecordPlayBackRight);
			m_lstUserRight.SetItemText(i, 16, strTemp);

			strTemp.Format("%d", pUserRightCfg->byLogDeleteRight);
			m_lstUserRight.SetItemText(i, 17, strTemp);

			strTemp.Format("%d", pUserRightCfg->byLogDownloadRight);
			m_lstUserRight.SetItemText(i, 18, strTemp);

			strTemp.Format("%d", pUserRightCfg->byAddUserRight);
			m_lstUserRight.SetItemText(i, 19, strTemp);

			strTemp.Format("%d", pUserRightCfg->byDelUserRight);
			m_lstUserRight.SetItemText(i, 20, strTemp);

			strTemp.Format("%d", pUserRightCfg->byModUserRight);
			m_lstUserRight.SetItemText(i, 21, strTemp);

			strTemp.Format("%d", pUserRightCfg->byAllocUserRight);
			m_lstUserRight.SetItemText(i, 22, strTemp);

			strTemp.Format("%d", *pStatus);
			m_lstUserRight.SetItemText(i, 23, strTemp);
			
			pStatusTemp++;
			pUserRightCfg++;
		}

		if (NULL != pStatus)
		{
			delete[] pStatus;
			pStatus = NULL;
		}
	}

	UpdateData(FALSE);
}

void CDlgBathcUserRightCfg::OnClickListUser(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strChannel;
	
	POSITION pos = m_lstUserRight.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
		nItem = m_lstUserRight.GetNextSelectedItem(pos);

		//显示信息
		m_bAddMonitorPointRight = atoi(m_lstUserRight.GetItemText(nItem, 3));
		m_bModMonitorPointRight = atoi(m_lstUserRight.GetItemText(nItem, 4));
		m_bDelMonitorPointRight = atoi(m_lstUserRight.GetItemText(nItem, 5));
		m_bSetRecordPlanRight = atoi(m_lstUserRight.GetItemText(nItem, 6));
		m_bDelRecordPlanRight = atoi(m_lstUserRight.GetItemText(nItem, 7));
		m_bRecordPlanRight = atoi(m_lstUserRight.GetItemText(nItem, 8));
		m_bRecordRight = atoi(m_lstUserRight.GetItemText(nItem, 10));
		m_bSetAlarmRecordRight = atoi(m_lstUserRight.GetItemText(nItem, 12));
		m_bRecordBackupRight = atoi(m_lstUserRight.GetItemText(nItem, 13));
		m_bRecordDownloadRight = atoi(m_lstUserRight.GetItemText(nItem, 14));
		m_bRecordDelRight = atoi(m_lstUserRight.GetItemText(nItem, 15));
		m_bBackupRecordDelRight = atoi(m_lstUserRight.GetItemText(nItem, 16));
		m_bSetBackupVolumeRight = atoi(m_lstUserRight.GetItemText(nItem, 17));
		m_bRecordPlayRight = atoi(m_lstUserRight.GetItemText(nItem, 18));
		m_bLogDeleteRight = atoi(m_lstUserRight.GetItemText(nItem, 19));
		m_bLogDownloadRight = atoi(m_lstUserRight.GetItemText(nItem, 20));
		m_bAddUserRight = atoi(m_lstUserRight.GetItemText(nItem, 21));
		m_bDelUserRight = atoi(m_lstUserRight.GetItemText(nItem, 22));
		m_bModUserRight = atoi(m_lstUserRight.GetItemText(nItem, 23));
		m_bAllcoUserRightRight = atoi(m_lstUserRight.GetItemText(nItem, 24));
		
		UpdateData(FALSE);
	}

	*pResult = 0;
}
