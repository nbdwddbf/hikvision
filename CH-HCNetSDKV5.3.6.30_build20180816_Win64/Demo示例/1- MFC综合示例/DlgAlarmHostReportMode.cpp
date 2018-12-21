// DlgAlarmHostReportMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostReportMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostReportMode dialog


CDlgAlarmHostReportMode::CDlgAlarmHostReportMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostReportMode::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
	, m_pStruReportCenter(NULL)
	, m_iCenterNum(-1)
	, m_iChanNum(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostReportMode)
	m_bValid = FALSE;
	m_bCheckSend1 = FALSE;
	m_bCheckSend2 = FALSE;
	m_bCheckSend3 = FALSE;
	m_bCheckSend4 = FALSE;
	m_bCheckSend5 = FALSE;
	m_bCheckSend6 = FALSE;
	//}}AFX_DATA_INIT
	//m_pStruReportCenter = new NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V30[MAX_CENTERGROUP_NUM];
	m_dwBufLen = /*MAX_CENTERGROUP_NUM*/7 * sizeof(NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40) + 4;
	m_lpOutBuffer = new char[m_dwBufLen];
}

CDlgAlarmHostReportMode::~CDlgAlarmHostReportMode()
{
	//delete[] m_pStruReportCenter;
	delete[] m_lpOutBuffer;
	m_pStruReportCenter = NULL;
}

void CDlgAlarmHostReportMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostReportMode)
	DDX_Control(pDX, IDC_LIST_ZONE_REPORT, m_listZoneReport);
	DDX_Control(pDX, IDC_LIST_NONZONE_REPORT, m_listNonZoneReport);
	DDX_Control(pDX, IDC_COMBO_CENTER, m_cmCenter);
	DDX_Control(pDX, IDC_COMBO_DATATYPE, m_cmDataType);
	DDX_Check(pDX, IDC_CHECK_VALID, m_bValid);
	DDX_Check(pDX, IDC_CHECK_SEND1, m_bCheckSend1);
	DDX_Check(pDX, IDC_CHECK_SEND2, m_bCheckSend2);
	DDX_Check(pDX, IDC_CHECK_SEND3, m_bCheckSend3);
	DDX_Check(pDX, IDC_CHECK_SEND4, m_bCheckSend4);
	DDX_Check(pDX, IDC_CHECK_SEND5, m_bCheckSend5);
	DDX_Check(pDX, IDC_CHECK_SEND6, m_bCheckSend6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostReportMode, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostReportMode)
	ON_CBN_SELCHANGE(IDC_COMBO_CENTER, OnSelchangeComboCenter)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_MULTI_SET, OnBtnMultiSet)
	ON_BN_CLICKED(IDC_BTN_SINGLE_GET, OnBtnSingleGet)
	ON_BN_CLICKED(IDC_BTN_MULTI_GET, OnBtnMultiGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostReportMode message handlers

BOOL CDlgAlarmHostReportMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitComboBox();
	CString csStr;
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(m_lpOutBuffer, 0, m_dwBufLen);
	m_pStruReportCenter = (LPNET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40)((char*)m_lpOutBuffer + 4);
	NET_DVR_ALARMHOST_ABILITY struAbility = {0};
	struAbility.dwSize = sizeof(NET_DVR_ALARMHOST_ABILITY);
	if(!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAbility, sizeof(NET_DVR_ALARMHOST_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility FAILED");
		m_iCenterNum = 2;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceAbility SUCC");
		m_iCenterNum = struAbility.byCenterGroupNum;
	}
	int i=0;
	m_cmCenter.ResetContent();
	for (i=0; i<m_iCenterNum; i++)
	{
		g_StringLanType(szLan, "中心", "Center");  
		csStr.Format("%s%d", szLan, i+1);
		m_cmCenter.AddString(csStr);
	}

	//初始化通道
	m_iChanNum = m_iCenterNum * 4;
	for (i=0; i<m_iChanNum; i++)
	{
		g_StringLanType(szLan, "关", "Close");
		csStr.Format(szLan);
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("T1");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("T2");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("N1");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("N2");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("G1");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("G2");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
        csStr.Format("N3");
        ((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
        csStr.Format("N4");
        ((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
	}
    for (i = 0; i < m_iChanNum; i++)
    {
        g_StringLanType(szLan, "主卡中心1", "primary-1");
        csStr.Format(szLan);
        ((CComboBox*)GetDlgItem(g_struNetCard[i]))->AddString(csStr);
        g_StringLanType(szLan, "主卡中心2", "primary-2");
        csStr.Format(szLan);
        ((CComboBox*)GetDlgItem(g_struNetCard[i]))->AddString(csStr);
        g_StringLanType(szLan, "扩展卡中心1", "extend-1");
        csStr.Format(szLan);
        ((CComboBox*)GetDlgItem(g_struNetCard[i]))->AddString(csStr);
        g_StringLanType(szLan, "扩展卡中心2", "extend-2");
        csStr.Format(szLan);
        ((CComboBox*)GetDlgItem(g_struNetCard[i]))->AddString(csStr);
    }
	for (i=0; i<m_iChanNum; i++)
	{
		((CComboBox*)GetDlgItem(g_struMode[i]))->SetCurSel(0);
	}
    for (i = 0; i < m_iChanNum; i++)
    {
        ((CComboBox*)GetDlgItem(g_struNetCard[i]))->SetCurSel(0);
    }

	m_listZoneReport.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listNonZoneReport.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<struAbility.wLocalAlarmInNum + struAbility.wExpandAlarmInNum; i++)
	{
		csStr.Format("Zone%d", i+1);
		m_listZoneReport.InsertItem(i, csStr);
	}

	int iIndex = 0;
	g_StringLanType(szLan, "软防区报告", "Soft zone");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "系统状态报告", "System state");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "取消报告", "Cancel");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "测试报告", "Test");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "布防报告", "Arm");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "撤防报告", "Disarm");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "挟持报告", "Duress alarm");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "报警恢复报告", "Alarm restore");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "旁路报告", "Bypass");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "旁路恢复报告", "Bypass restore");
	m_listNonZoneReport.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "探测器连接状态报告（上线、离线）", "Detector Connection");
    m_listNonZoneReport.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "探测器电量状态报告（电压正常、欠压）", "Detector Power");
    m_listNonZoneReport.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "视频报警报告", "Video Alarm");
    m_listNonZoneReport.InsertItem(iIndex++, szLan);

	UpdateData(FALSE);
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void CDlgAlarmHostReportMode::InitComboBox()
{
	char szLan[128] = {0};
	m_cmDataType.ResetContent();
	g_StringLanType(szLan, "报警数据", "ALARM DATA");
	m_cmDataType.AddString(szLan);
	g_StringLanType(szLan, "非报警数据", "NORAML DATA");
	m_cmDataType.AddString(szLan);
	g_StringLanType(szLan, "所有数据", "ALL DATA");
	m_cmDataType.AddString(szLan);
	g_StringLanType(szLan, "防区报警", "ZONE ALARM");
	m_cmDataType.AddString(szLan);
	g_StringLanType(szLan, "非防区报警", "NON ZONE ALARM");
	m_cmDataType.AddString(szLan);
	UpdateData(FALSE);
} 

void CDlgAlarmHostReportMode::OnSelchangeComboCenter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwCenterIndex = m_cmCenter.GetCurSel();
	if (dwCenterIndex > m_iCenterNum)
	{
		dwCenterIndex = 0;
	}
	EnableCheckWindow(dwCenterIndex);
	NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40 struReportMode = {0};
	memcpy(&struReportMode, &m_pStruReportCenter[dwCenterIndex], sizeof(struReportMode));
	m_cmDataType.SetCurSel(struReportMode.byDataType - 1);
	m_bValid = struReportMode.byValid;
	m_bCheckSend1 = struReportMode.byDealFailCenter[0];
	m_bCheckSend2 = struReportMode.byDealFailCenter[1];
	m_bCheckSend3 = struReportMode.byDealFailCenter[2];
	m_bCheckSend4 = struReportMode.byDealFailCenter[3];
	m_bCheckSend5 = struReportMode.byDealFailCenter[4];
	m_bCheckSend6 = struReportMode.byDealFailCenter[5];

	int i=0;
	for (i=0; i<m_listZoneReport.GetItemCount(); i++)
	{
		m_listZoneReport.SetCheck(i, FALSE);
	}

	for (i=0; i<m_listZoneReport.GetItemCount(); i++)
	{
		m_listZoneReport.SetCheck(i, (BOOL)struReportMode.byZoneReport[i]);
	}

	for (i=0; i<m_listNonZoneReport.GetItemCount(); i++) 
	{
		m_listNonZoneReport.SetCheck(i, FALSE);
	}

	for (i=0; i<m_listNonZoneReport.GetItemCount(); i++) 
	{
		m_listNonZoneReport.SetCheck(i, (BOOL)struReportMode.byNonZoneReport[i]);
	}
	UpdateData(FALSE);
}

void CDlgAlarmHostReportMode::EnableCheckWindow(DWORD dwCenterIndex) 
{
	int i = 0;
	for (i=0; i<m_iCenterNum; i++)
	{
		GetDlgItem(g_struCheckSend[i])->EnableWindow(TRUE);
	}
	GetDlgItem(g_struCheckSend[dwCenterIndex])->EnableWindow(FALSE);
}

void CDlgAlarmHostReportMode::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwCenterIndex = m_cmCenter.GetCurSel();
	NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40 struReportMode = {0};
	struReportMode.dwSize = sizeof(struReportMode);
	struReportMode.byDataType = m_cmDataType.GetCurSel() + 1;
	struReportMode.byValid = m_bValid;
	struReportMode.byDealFailCenter[0] = m_bCheckSend1;
	struReportMode.byDealFailCenter[1] = m_bCheckSend2;
	struReportMode.byDealFailCenter[2] = m_bCheckSend3;
	struReportMode.byDealFailCenter[3] = m_bCheckSend4;
	struReportMode.byDealFailCenter[4] = m_bCheckSend5;
	struReportMode.byDealFailCenter[5] = m_bCheckSend6;

	int i=0; 
	for (i=0; i<m_listZoneReport.GetItemCount(); i++)
	{
		struReportMode.byZoneReport[i] = m_listZoneReport.GetCheck(i);
	}
	for (i=0; i<m_listNonZoneReport.GetItemCount(); i++)
	{
		struReportMode.byNonZoneReport[i] = m_listNonZoneReport.GetCheck(i);
	}
	
	for (i=0; i<m_iCenterNum; i++)
	{
		m_pStruReportCenter[i].dwSize = sizeof(NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40);
		//报警中心序号
		m_dwCenterNo[i] = i+1;
	}

	memcpy(&m_pStruReportCenter[dwCenterIndex], &struReportMode, sizeof(struReportMode));
}

void CDlgAlarmHostReportMode::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//if (!NET_DVR_AlarmHostGetReportMode(m_lUserID, m_pStruReportCenter, dwBufLen))
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40, 0xffffffff, NULL, 0,  &m_dwStatusList, m_lpOutBuffer, m_dwBufLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		g_StringLanType(szLan, "获取上传方式失败", "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 SUCC");
	}
	SetReportMode();
	m_cmCenter.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboCenter();
}

void CDlgAlarmHostReportMode::SetReportMode()
{
	int iCenterIndex = 0;
	int iStartIndex = 0;
	int i = 0;
	int iReportMode = 0;//1-T1 2-T2
    int iNetCard = 0;
	for (iCenterIndex=0; iCenterIndex<m_iCenterNum; iCenterIndex++)
	{
		iStartIndex = 4*iCenterIndex;
		for (i = 0; i<MAX_REPORTCHAN_NUM; i++)
		{
			iReportMode = m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i];
            iNetCard = m_pStruReportCenter[iCenterIndex].byAlarmNetCard[i];
            //1-8为有效值，其他值都归为0（关）
			if (iReportMode>=1 && iReportMode<=8)
			{
				((CComboBox*)GetDlgItem(g_struMode[i+iStartIndex]))->SetCurSel(iReportMode);
                ((CComboBox*)GetDlgItem(g_struNetCard[i + iStartIndex]))->SetCurSel(iNetCard);
			}
			else
			{
				((CComboBox*)GetDlgItem(g_struMode[i+iStartIndex]))->SetCurSel(0);
                ((CComboBox*)GetDlgItem(g_struNetCard[i + iStartIndex]))->SetCurSel(0);
			}
		}
	}
	UpdateData(FALSE);
}
void CDlgAlarmHostReportMode::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnSure();
	int iCenterIndex = 0;
	int iStartIndex = 0;
	int i = 0;
	int iReportMode = 0;//1-T1 2-T2
    int iNetCard = 0;
	for (iCenterIndex=0; iCenterIndex<m_iCenterNum; iCenterIndex++)
	{
		iStartIndex = 4*iCenterIndex;
		for (i = 0; i<4; i++)
		{
			iReportMode = ((CComboBox*)GetDlgItem(g_struMode[i+iStartIndex]))->GetCurSel();
            iNetCard = ((CComboBox*)GetDlgItem(g_struNetCard[i + iStartIndex]))->GetCurSel();
            //1-8为有效值，其他值都归为0（关）
            if (iReportMode >= 1 && iReportMode <= 8)
			{
				m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i] = iReportMode;
                m_pStruReportCenter[iCenterIndex].byAlarmNetCard[i] = iNetCard;
			}
			else
			{
				m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i] = 0;
                m_pStruReportCenter[iCenterIndex].byAlarmNetCard[i] = 0;
			}
		}
	}
	int iIndex = m_cmCenter.GetCurSel() + 1;
 	if(!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40, 1, &iIndex, sizeof(DWORD), m_dwStatusList, &m_pStruReportCenter[iIndex-1], m_iCenterNum * sizeof(NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		g_StringLanType(szLan, "设置上传方式失败", "NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		MessageBox(szLan);
	}
	else
	{
		char szTemp[128] = {0};
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40 SUCC");
		sprintf(szTemp, "status = %d", m_dwStatusList[0]);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szTemp);
	}
}

void CDlgAlarmHostReportMode::OnBtnMultiSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnSure();
	int iCenterIndex = 0;
	int iStartIndex = 0;
	int i = 0;
	int iReportMode = 0;//1-T1 2-T2
    int iNetCard = 0;
	for (iCenterIndex=0; iCenterIndex<m_iCenterNum; iCenterIndex++)
	{
		iStartIndex = 4*iCenterIndex;
		for (i = 0; i<4; i++)
		{
			iReportMode = ((CComboBox*)GetDlgItem(g_struMode[i+iStartIndex]))->GetCurSel();
            iNetCard = ((CComboBox*)GetDlgItem(g_struNetCard[i + iStartIndex]))->GetCurSel();
            //1-8为有效值，其他值都归为0（关）
            if (iReportMode >= 1 && iReportMode <= 8)
			{
				m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i] = iReportMode;
                m_pStruReportCenter[iCenterIndex].byAlarmNetCard[i] = iNetCard;
			}
			else
			{
				m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i] = 0;
                m_pStruReportCenter[iCenterIndex].byAlarmNetCard[i] = 0;
			}
		}
	}
	int iIndex = m_cmCenter.GetCurSel() + 1;
	//m_dwCenterNo[5] = 6;
	//m_iCenterNum = 6;
	//m_pStruReportCenter[6].dwSize = sizeof(NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40);
	if(!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40, m_iCenterNum, &m_dwCenterNo, m_iCenterNum*sizeof(DWORD), m_dwStatusList, m_pStruReportCenter, m_iCenterNum * sizeof(NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40)))
	//if(!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40, m_iCenterNum, NULL, 0, NULL, m_pStruReportCenter, m_iCenterNum * sizeof(NET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		g_StringLanType(szLan, "设置上传方式失败", "NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMHOST_REPORT_CENTER_V40 SUCC");
		char szTemp[128] = {0};
		for (int i=0; i<m_iCenterNum; i++)
		{
			sprintf(szTemp, "status%d = %d", i+1, m_dwStatusList[i]);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szTemp);
		}
	}
}

void CDlgAlarmHostReportMode::OnBtnSingleGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex =  m_cmCenter.GetCurSel() + 1;
	//if (!NET_DVR_AlarmHostGetReportMode(m_lUserID, m_pStruReportCenter, dwBufLen))
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40, 1, &iIndex, sizeof(DWORD),  &m_dwStatusList, &m_pStruReportCenter[iIndex-1], m_dwBufLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		g_StringLanType(szLan, "获取上传方式失败", "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 SUCC");
	}
	SetReportMode();
	OnSelchangeComboCenter();
}

void CDlgAlarmHostReportMode::OnBtnMultiGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//test
	//m_dwCenterNo[5] = 7;
	int i = 0;
	for (i=0; i<m_iCenterNum; i++)
	{
		m_dwCenterNo[i] = i+1;
	}
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40, m_iCenterNum, &m_dwCenterNo, m_iCenterNum*sizeof(DWORD),  &m_dwStatusList, m_pStruReportCenter, m_dwBufLen))
	//if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40, m_iCenterNum, NULL, 0,  NULL, m_pStruReportCenter, m_dwBufLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		g_StringLanType(szLan, "获取上传方式失败", "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 FAILED");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_REPORT_CENTER_V40 SUCC");
	}
	SetReportMode();
	m_cmCenter.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboCenter();
}
