// DlgITCIOinCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITCIOinCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITCIOinCfg dialog
#define MAX_MUN 128

CDlgITCIOinCfg::CDlgITCIOinCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITCIOinCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITCIOinCfg)
	m_bAlarmHost = FALSE;
	m_bArm = FALSE;
	m_bCard = FALSE;
	m_bEnable = FALSE;
	m_bEpolice = FALSE;
	m_bHVT = FALSE;
	m_bNoMatching = FALSE;
	m_bNoPlateColor = FALSE;
	m_bPlateColor = FALSE;
	m_bRelay = FALSE;
	m_bRS485 = FALSE;
	m_bSingleIO = FALSE;
	m_csCardNum = _T("");
	m_csPlateNum = _T("");
	m_csCardNumVeh = _T("");
	m_csPlateNumVeh = _T("");
	m_csCardNoTemp = _T("");
	m_csLicenseTemp = _T("");
	m_dwDataIndexTemp = 0;
	m_startDate = COleDateTime::GetCurrentTime();
	m_startTime = COleDateTime::GetCurrentTime();
	m_stopDate = COleDateTime::GetCurrentTime();
	m_stopTime = COleDateTime::GetCurrentTime();
	m_startMilliSec = 0;
	m_stopMilliSec = 0;
	m_bCheckStartTime = FALSE;
	m_bCheckStopTime = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_byIOInNum = 0;
	m_byRelayNum = 0;
	m_lHandle = -1;
	m_hGetInfoThread = NULL;
	m_bGetNext = FALSE;
	m_iStruCount = 0;
	m_pStruVehInfo = NULL;
	m_iItem = 0;
	m_lSyncVehHandle = -1;
	m_bCheckSet = FALSE;
}

CDlgITCIOinCfg::~CDlgITCIOinCfg()
{
	char szLan[128] = {0};
	
	if (m_lSyncVehHandle >=0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lSyncVehHandle))
		{
			g_StringLanType(szLan, "同步黑白名单数据停止失败", "Vehicle Black and White List Stop Failed");
			AfxMessageBox(szLan);
			return;
		}
	}

	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			g_StringLanType(szLan, "同步黑白名单数据停止失败", "Vehicle Black and White List Stop Failed");
			AfxMessageBox(szLan);
			return;
		}
	} 
}

void CDlgITCIOinCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITCIOinCfg)
	DDX_Control(pDX, IDC_COMBO_OPERATE_TYPE_VEH, m_comOperateTypeVeh);
	DDX_Control(pDX, IDC_COMBO_DEL_COND, m_comDelCond);
	DDX_Control(pDX, IDC_COMBO_TRIGGER_MODE, m_comTriggerMode);
	DDX_Control(pDX, IDC_COMBO_CTRL_MODE, m_comCtrlMode);
	DDX_Control(pDX, IDC_COMBO_PLATETYPE_TEMP, m_comPlateTypeTemp);
	DDX_Control(pDX, IDC_COMBO_PLATECOLOR_TEMP, m_comPlateColorTemp);
	DDX_Control(pDX, IDC_COMBO_LISTTYPE_TEMP, m_comListTypeTemp);
	DDX_Control(pDX, IDC_COMBO_LIST_TYPE_VEHICLE, m_comListTypeVeh);
	DDX_Control(pDX, IDC_LIST_VEHICLE, m_lstVehicle);
	DDX_Control(pDX, IDC_COMBO_LAMP_LANE_NO, m_comLampLaneNo);
	DDX_Control(pDX, IDC_COMBO_LAMP_CTRL, m_comLampCtrl);
	DDX_Control(pDX, IDC_COMBO_PLATE_TYPE, m_comPlateType);
	DDX_Control(pDX, IDC_COMBO_PLATE_COLOR, m_comPlateColor);
	DDX_Control(pDX, IDC_COMBO_OPERATE_TYPE, m_comOperateType);
	DDX_Control(pDX, IDC_COMBO_LANE_NO, m_comLaneNo);
	DDX_Control(pDX, IDC_COMBO_GATE_CTRL, m_comGateCtrl);
	DDX_Control(pDX, IDC_COMBO_VEHICLE_CONTROL, m_comVehicleControl);
	DDX_Control(pDX, IDC_COMBO_RELAY_NUM, m_comRelayNum);
	DDX_Control(pDX, IDC_COMBO_RELAY_INFO, m_comRelayInfo);
	DDX_Control(pDX, IDC_COMBO_LANE, m_comLane);
	DDX_Control(pDX, IDC_COMBO_IOIN_NO, m_comIOInNum);
	DDX_Control(pDX, IDC_COMBO_GATE_TYPE, m_comGateType);
	DDX_Control(pDX, IDC_COMBO_GATE_SINGLE_IO, m_comGateSingleIO);
	DDX_Control(pDX, IDC_COMBO_LIST_DEL_TYPE_VEHICLE, m_comDelListType);
	DDX_Check(pDX, IDC_CHECK_ALARM_HOST, m_bAlarmHost);
	DDX_Check(pDX, IDC_CHECK_ARM, m_bArm);
	DDX_Check(pDX, IDC_CHECK_CARD, m_bCard);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_EPOLICE, m_bEpolice);
	DDX_Check(pDX, IDC_CHECK_HVT, m_bHVT);
	DDX_Check(pDX, IDC_CHECK_NO_MATCHING, m_bNoMatching);
	DDX_Check(pDX, IDC_CHECK_NO_PLATE_COLOR, m_bNoPlateColor);
	DDX_Check(pDX, IDC_CHECK_PLATE_COLOR, m_bPlateColor);
	DDX_Check(pDX, IDC_CHECK_RELAY, m_bRelay);
	DDX_Check(pDX, IDC_CHECK_RS485, m_bRS485);
	DDX_Check(pDX, IDC_CHECK_SINGLE_IO, m_bSingleIO);
	DDX_Text(pDX, IDC_EDIT_CARD_NUM, m_csCardNum);
	DDX_Text(pDX, IDC_EDIT_PLATE_NUM, m_csPlateNum);
	DDX_Text(pDX, IDC_EDIT_CARD_NUM_VEHICLE, m_csCardNumVeh);
	DDX_Text(pDX, IDC_EDIT_PLATE_NUM_VEHICLE, m_csPlateNumVeh);
	DDX_Text(pDX, IDC_EDIT_CARDNO_TEMP, m_csCardNoTemp);
	DDX_Text(pDX, IDC_EDIT_SLICENSE_TEMP, m_csLicenseTemp);
	DDX_Text(pDX, IDC_EDIT_DATAINDEX_TEMP, m_dwDataIndexTemp);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
	DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
	DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
	DDX_Text(pDX, IDC_START_MILLISEC, m_startMilliSec);
	DDX_Text(pDX, IDC_STOP_MILLISEC, m_stopMilliSec);
	DDX_Check(pDX, IDC_CHECK_START_TIME, m_bCheckStartTime);
	DDX_Check(pDX, IDC_CHECK_STOP_TIME, m_bCheckStopTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITCIOinCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgITCIOinCfg)
	ON_BN_CLICKED(IDC_BTN_GET_ENTRANCE, OnBtnGetEntrance)
	ON_BN_CLICKED(IDC_BTN_SET_ENTRANCE, OnBtnSetEntrance)
	ON_CBN_SELCHANGE(IDC_COMBO_LANE, OnSelchangeComboLane)
	ON_CBN_SELCHANGE(IDC_COMBO_RELAY_NUM, OnSelchangeComboRelayNum)
	ON_CBN_SELCHANGE(IDC_COMBO_VEHICLE_CONTROL, OnSelchangeComboVehicleControl)
	ON_CBN_SELCHANGE(IDC_COMBO_IOIN_NO, OnSelchangeComboIoinNo)
	ON_BN_CLICKED(IDC_BTN_GATE_CTRL, OnBtnGateCtrl)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_LAMP_CTRL, OnBtnLampCtrl)
	ON_BN_CLICKED(IDC_BTN_VEHICLE_CONTROL, OnBtnVehicleControl)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_VEHICLE, OnClickListVehicle)
	ON_BN_CLICKED(IDC_BTN_SYNC_VEHICLE_CONTROL, OnBtnSyncVehicleControl)
	ON_BN_CLICKED(IDC_BTN_SEND_VEH_DATA, OnBtnSendVehData)
	ON_BN_CLICKED(IDC_BTN_STOP_VEH_DATA, OnBtnStopVehData)
	ON_BN_CLICKED(IDC_BTN_CREATE_LINK, OnBtnCreateLink)
	ON_CBN_SELCHANGE(IDC_COMBO_DEL_COND, OnSelchangeComboDelCond)
	ON_CBN_SELCHANGE(IDC_COMBO_OPERATE_TYPE, OnSelchangeComboOperateType)
	ON_BN_CLICKED(IDC_BTN_SAVE_ENTRANCE, OnBtnSaveEntrance)
	ON_BN_CLICKED(IDC_CHECK_START_TIME, OnCheckStartTime)
	ON_BN_CLICKED(IDC_CHECK_STOP_TIME, OnCheckStopTime)
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	ON_CBN_SELCHANGE(IDC_COMBO_OPERATE_TYPE_VEH, OnSelchangeComboOperateTypeVeh)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VEHICLE, OnDblclkListVehicle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITCIOinCfg message handlers



BOOL CDlgITCIOinCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(TRUE);

	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	m_comListTypeTemp.SetCurSel(0);
	m_comPlateTypeTemp.SetCurSel(0);
	m_comPlateColorTemp.SetCurSel(0);

	m_comListTypeVeh.SetCurSel(0);

	m_comLane.SetCurSel(0);
	// TODO: Add extra initialization here
	int i = 0;
	for (; i<m_byIOInNum; i++)
	{
		CString str;
		str.Format(_T("IOIn %d"),i + 1);
		m_comIOInNum.AddString(str);
	}
	m_comIOInNum.SetCurSel(0);

	for (i = 0; i<m_byRelayNum; i++)
	{
		CString str;
		str.Format(_T("Relay %d"),i + 1);
		m_comRelayNum.AddString(str);
	}
	m_comRelayNum.SetCurSel(0);

	char szLanTemp[128] = {0};
	m_lstVehicle.SetExtendedStyle(m_lstVehicle.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	//g_StringLanType(szLanTemp, "数据流水号", "Data Index");
    //m_lstVehicle.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 0, -1);
	g_StringLanType(szLanTemp, "车牌号码", "Plate No.");
    m_lstVehicle.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "名单属性", "List Type");
	m_lstVehicle.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车牌类型", "Plate Type");
    m_lstVehicle.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLanTemp, "车牌颜色", "Plate Color");
    m_lstVehicle.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "卡号", "Card No.");
    m_lstVehicle.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "有效开始时间", "Start Time");
    m_lstVehicle.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLanTemp, "有效结束时间", "Stop Time");
    m_lstVehicle.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 100, -1);

	m_pStruVehInfo = new NET_DVR_VEHICLE_CONTROL_LIST_INFO[MAX_ALARMHOST_ALARMOUT_NUM];
	memset(&m_struEntrance, 0, sizeof(NET_DVR_ENTRANCE_CFG));
	memset(m_pStruVehInfo, 0, sizeof(NET_DVR_VEHICLE_CONTROL_LIST_INFO)*MAX_ALARMHOST_ALARMOUT_NUM);
	memset(&m_struDelVehicleInfo, 0, sizeof(NET_DVR_VEHICLE_CONTROL_DELINFO));
	memset(&m_struVehCond, 0, sizeof(m_struVehCond));
	m_comCtrlMode.SetCurSel(0);
	m_comTriggerMode.SetCurSel(0);

	GetDlgItem(IDC_COMBO_DEL_COND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_PLATE_NUM_VEHICLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CARD_NUM_VEHICLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_LIST_TYPE_VEHICLE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SEND_VEH_DATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP_VEH_DATA)->EnableWindow(FALSE);

	m_comLaneNo.SetCurSel(0);
	m_comGateCtrl.SetCurSel(0);

	m_comLampLaneNo.SetCurSel(0);
	m_comLampCtrl.SetCurSel(0);
	
// 	m_startDate.SetDate(0, 0, 0);
// 	m_startTime.SetTime(0, 0, 0);
// 	
// 	m_stopDate.SetDate(0, 0, 0);
// 	m_stopTime.SetTime(0, 0, 0);
	
	m_bCheckStartTime = 0;
//	m_bCheckStopTime = 0;

	m_comOperateType.SetCurSel(0);
	OnSelchangeComboOperateType();
	m_comPlateColor.SetCurSel(0);
	m_comPlateType.SetCurSel(0);
	m_comDelCond.SetCurSel(0);
	m_comDelListType.SetCurSel(0);
	OnSelchangeComboDelCond();
	
	m_comOperateTypeVeh.SetCurSel(0);
	OnSelchangeComboOperateTypeVeh();

	UpdateData(FALSE);

	OnCheckStartTime();
//	OnCheckStopTime();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgITCIOinCfg::ListTest()
{
	char szLan[128] = {0};
	NET_DVR_VEHICLE_CONTROL_COND queryCondition = {0};
	
	queryCondition.dwChannel = 1;
	queryCondition.byListType = 0xff;
	queryCondition.dwOperateType = VCA_OPERATE_INDEX_TYPE;
	queryCondition.dwDataIndex = 0xffffffff;

	for (;;)
	{
		m_lSyncVehHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_VEHICLELIST_CTRL_START/*NET_DVR_VEHICLE_CONTROL_LIST_START*/,NULL,0,NULL,NULL);
		
		if (m_lSyncVehHandle >= 0)
		{
			if (!NET_DVR_StopRemoteConfig(m_lSyncVehHandle))
			{
				g_StringLanType(szLan, "同步黑白名单数据停止失败", "Vehicle Black and White List Stop Failed");
				AfxMessageBox(szLan);
				return;
			}
			m_lSyncVehHandle = -1;
		}



		m_lHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_ALL_VEHICLE_CONTROL_LIST, &queryCondition, sizeof(queryCondition), NULL, NULL);
		
		if (m_lHandle >= 0)
		{
			if (!NET_DVR_StopRemoteConfig(m_lHandle))
			{
				g_StringLanType(szLan, "同步黑白名单数据停止失败", "Vehicle Black and White List Stop Failed");
				AfxMessageBox(szLan);
				return;
			}
			m_lHandle = -1;
		}
	}


}

void CDlgITCIOinCfg::OnBtnGetEntrance() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	if(0 == m_comLane.GetCurSel())
// 	{
// 		return;
// 	}

	DWORD dwReturn = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	int size = m_comLane.GetCurSel() + 1;
	DWORD *pStatus = new DWORD[size];
    memset(pStatus, 0, sizeof(DWORD)*m_comLane.GetCurSel());
	memset(&m_struEntrance, 0, sizeof(NET_DVR_ENTRANCE_CFG));
	m_struGateCond.byLaneNo = m_comLane.GetCurSel() + 1;

	if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_ENTRANCE_PARAMCFG, m_comLane.GetCurSel() + 1, &m_struGateCond, \
		sizeof(NET_DVR_BARRIERGATE_COND)*(m_comLane.GetCurSel() + 1), pStatus, &m_struEntrance, (m_comLane.GetCurSel() + 1)*sizeof(NET_DVR_ENTRANCE_CFG)))
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < m_comLane.GetCurSel()+1; i++)
		{
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "获取出入口参数失败", "Get IOIn Param configuration failed");
				sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;			 
        }
	}
	else
	{
		delete [] pStatus;
		g_StringLanType(szLan, "获取出入口参数失败", "Get IOIn Param configuration failed");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
		AfxMessageBox(szTemp);
		return;	
	}

	delete [] pStatus;
	UpdateData(FALSE);
	OnSelchangeComboLane() ;

}

void CDlgITCIOinCfg::OnBtnSetEntrance() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	if(0 == m_comLane.GetCurSel())
// 	{
// 		return;
// 	}
	LPNET_DVR_ENTRANCE_CFG pstruEntranceTmp = &m_struEntrance;
	pstruEntranceTmp += m_comLane.GetCurSel();
	pstruEntranceTmp->dwSize = sizeof(NET_DVR_ENTRANCE_CFG);
	
	pstruEntranceTmp->byEnable = m_bEnable;

	pstruEntranceTmp->byBarrierGateCtrlMode = m_comCtrlMode.GetCurSel();
	
	pstruEntranceTmp->dwRelateTriggerMode = 0;
// 	pstruEntranceTmp->dwRelateTriggerMode |= (m_bSingleIO << 1);
// 	pstruEntranceTmp->dwRelateTriggerMode |= (m_bRS485 << 2);
// 	pstruEntranceTmp->dwRelateTriggerMode |= (m_bHVT << 5);
// 	pstruEntranceTmp->dwRelateTriggerMode |= (m_bEpolice << 9);
	if (0 == m_comTriggerMode.GetCurSel())
	{
		pstruEntranceTmp->dwRelateTriggerMode = 0x2;
	}
	else if(1 == m_comTriggerMode.GetCurSel())
	{
		pstruEntranceTmp->dwRelateTriggerMode = 0x4;
	}
	else if(2 == m_comTriggerMode.GetCurSel())
	{
		pstruEntranceTmp->dwRelateTriggerMode = 0x40;
	}
// 	else if(3 == m_comTriggerMode.GetCurSel())
// 	{	
// 		pstruEntranceTmp->dwRelateTriggerMode = 0x20;
// 	}
// 	else if (4 == m_comTriggerMode.GetCurSel())
// 	{
// 		pstruEntranceTmp->dwRelateTriggerMode = 0x20000;
// 	}
	pstruEntranceTmp->dwMatchContent = 0;
	pstruEntranceTmp->dwMatchContent |= (m_bPlateColor << 0);
	pstruEntranceTmp->dwMatchContent |= (m_bNoPlateColor << 1);
	pstruEntranceTmp->dwMatchContent |= (m_bCard << 2);

// 	for (int i = 0; i<m_byRelayNum; i++)
// 	{
// 		pstruEntranceTmp->struRelayRelateInfo[i].byAccessDevInfo = m_comRelayInfo.GetCurSel();
// 	}
// 	
// 	for (i = 0; i<m_byIOInNum; i++)
// 	{
// 		pstruEntranceTmp->byGateSingleIO[i] = m_comGateSingleIO.GetCurSel();
// 	}
// 	
// 	for (i = 0; i<3; i++)
// 	{
// 		pstruEntranceTmp->struVehicleCtrl[i].byGateOperateType = m_comGateType.GetCurSel();
// 
// 		pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType |= (m_bRelay << 0);
// 		pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType |= (m_bArm << 1);
// 		pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType |= (m_bAlarmHost << 2);
// 	}

	
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	DWORD *pStatus = new DWORD[m_comLane.GetCurSel() + 1];
    memset(pStatus, 0, sizeof(DWORD)*m_comLane.GetCurSel() + 1);
//	memset(&m_struEntrance, 0, sizeof(NET_DVR_ENTRANCE_CFG));
	m_struGateCond.byLaneNo = m_comLane.GetCurSel() + 1;

	if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_ENTRANCE_PARAMCFG, m_comLane.GetCurSel() + 1, &m_struGateCond, (m_comLane.GetCurSel()+1)*sizeof(NET_DVR_BARRIERGATE_COND), \
		pStatus, &m_struEntrance, (m_comLane.GetCurSel()+1)*sizeof(NET_DVR_ENTRANCE_CFG)))
	{
		g_StringLanType(szLan, "设置出入口参数失败", "Set IOIn Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		delete [] pStatus;
		UpdateData(FALSE);
		return;
	}
	else
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < m_comLane.GetCurSel()+1; i++)
		{
			
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "设置出入口参数失败", "Set IOIn Param configuration failed");
				sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				UpdateData(FALSE);
				return;
			}
			pStatusTmp++;
		}
	}
	delete [] pStatus;
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnSelchangeComboLane() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	if(0 == m_comLane.GetCurSel())
// 	{
// 		return;
// 	}

	LPNET_DVR_ENTRANCE_CFG pstruEntranceTmp = &m_struEntrance;
	pstruEntranceTmp += m_comLane.GetCurSel();
	
	m_bEnable = pstruEntranceTmp->byEnable;
	m_comCtrlMode.SetCurSel(pstruEntranceTmp->byBarrierGateCtrlMode);

// 	m_bSingleIO = (pstruEntranceTmp->dwRelateTriggerMode>>1)&0x01;
// 	m_bRS485 = (pstruEntranceTmp->dwRelateTriggerMode>>2)&0x01;
// 	m_bHVT = (pstruEntranceTmp->dwRelateTriggerMode>>5)&0x01;
// 	m_bEpolice = (pstruEntranceTmp->dwRelateTriggerMode>>9)&0x01;
	if (0x2 == pstruEntranceTmp->dwRelateTriggerMode)
	{
		m_comTriggerMode.SetCurSel(0);
	}
	else if(0x4 == pstruEntranceTmp->dwRelateTriggerMode)
	{
		m_comTriggerMode.SetCurSel(1);
	}	
	else if (0x40 == pstruEntranceTmp->dwRelateTriggerMode)
	{
		m_comTriggerMode.SetCurSel(2);
	}
// 	else
// 	{
// 		m_comTriggerMode.SetCurSel(0);
// 	}
// 	else if(0x20 == pstruEntranceTmp->dwRelateTriggerMode)
// 	{	
// 		m_comTriggerMode.SetCurSel(3);
// 	}
// 	else if (0x20000 == pstruEntranceTmp->dwRelateTriggerMode)
// 	{
// 		m_comTriggerMode.SetCurSel(4);
// 	}

	
	m_bPlateColor = (pstruEntranceTmp->dwMatchContent)&0x01;
	m_bNoPlateColor = (pstruEntranceTmp->dwMatchContent>>1)&0x01;
	m_bCard = (pstruEntranceTmp->dwMatchContent>>2)&0x01;
	
	m_comRelayNum.SetCurSel(0);
	m_comRelayInfo.SetCurSel(pstruEntranceTmp->struRelayRelateInfo[0].byAccessDevInfo);
	
	m_comIOInNum.SetCurSel(0);
	m_comGateSingleIO.SetCurSel(pstruEntranceTmp->byGateSingleIO[0]);
	
	m_comVehicleControl.SetCurSel(0);
	m_comGateType.SetCurSel(pstruEntranceTmp->struVehicleCtrl[0].byGateOperateType);
	m_bRelay = (pstruEntranceTmp->struVehicleCtrl[0].wAlarmOperateType)&0x01;
	m_bArm = (pstruEntranceTmp->struVehicleCtrl[0].wAlarmOperateType>>1)&0x01;
	m_bAlarmHost = (pstruEntranceTmp->struVehicleCtrl[0].wAlarmOperateType>>2)&0x01;
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnSelchangeComboRelayNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	if(0 == m_comLane.GetCurSel())
// 	{
// 		return;
// 	}
	int i = m_comRelayNum.GetCurSel();
	LPNET_DVR_ENTRANCE_CFG pstruEntranceTmp = &m_struEntrance;
	pstruEntranceTmp += m_comLane.GetCurSel();
	m_comRelayInfo.SetCurSel(pstruEntranceTmp->struRelayRelateInfo[i].byAccessDevInfo);
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnSelchangeComboVehicleControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	if(0 == m_comLane.GetCurSel())
// 	{
// 		return;
// 	}
	LPNET_DVR_ENTRANCE_CFG pstruEntranceTmp = &m_struEntrance;
	pstruEntranceTmp += m_comLane.GetCurSel();

	int i = m_comVehicleControl.GetCurSel();
	m_comGateType.SetCurSel(pstruEntranceTmp->struVehicleCtrl[i].byGateOperateType);
	m_bRelay = (pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType)&0x01;
	m_bArm = (pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType>>1)&0x01;
	m_bAlarmHost = (pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType>>2)&0x01;
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnSelchangeComboIoinNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	if(0 == m_comLane.GetCurSel())
// 	{
// 		return;
// 	}
	int i = m_comIOInNum.GetCurSel();
	LPNET_DVR_ENTRANCE_CFG pstruEntranceTmp = &m_struEntrance;
	pstruEntranceTmp += m_comLane.GetCurSel();
	m_comGateSingleIO.SetCurSel(pstruEntranceTmp->byGateSingleIO[i]);
	UpdateData(FALSE);
}


void CDlgITCIOinCfg::OnBtnGateCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struGateCFG.dwSize = sizeof(NET_DVR_BARRIERGATE_CFG);
	m_struGateCFG.dwChannel = 1;
	m_struGateCFG.byLaneNo = m_comLaneNo.GetCurSel() + 1;
	m_struGateCFG.byBarrierGateCtrl = m_comGateCtrl.GetCurSel();

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_BARRIERGATE_CTRL, &m_struGateCFG, sizeof(NET_DVR_BARRIERGATE_CFG)))
	{
		g_StringLanType(szLan, "道闸控制失败", "Gate control failed");
		AfxMessageBox(szLan);
	}


	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struDelVehicleInfo.dwSize = sizeof(NET_DVR_VEHICLE_CONTROL_DELINFO);
	memcpy(m_struDelVehicleInfo.sLicense, m_csPlateNum, sizeof(m_struDelVehicleInfo.sLicense));
	memcpy(m_struDelVehicleInfo.sCardNo, m_csCardNum, sizeof(m_struDelVehicleInfo.sCardNo));
	if(0 == m_comOperateType.GetCurSel())
	{
		m_struDelVehicleInfo.byOperateType = 0;
	}
	else if(1 == m_comOperateType.GetCurSel())
	{
		m_struDelVehicleInfo.byOperateType = 0xff;
	}

	if(5 == m_comPlateColor.GetCurSel())
	{
		m_struDelVehicleInfo.byPlateColor = 0xff;
	}
	else
	{
		m_struDelVehicleInfo.byPlateColor = m_comPlateColor.GetCurSel();
	}

	m_struDelVehicleInfo.byPlateType = m_comPlateType.GetCurSel();
	m_struDelVehicleInfo.byListType = m_comDelListType.GetCurSel();

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_VEHICLE_DELINFO_CTRL, &m_struDelVehicleInfo, sizeof(NET_DVR_VEHICLE_CONTROL_DELINFO)))
	{
		g_StringLanType(szLan, "删除设备内黑名单数据库信息失败", "Delete Vehicle Info failed");
		sprintf(szLan, "%s 错误码：%d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}

	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnBtnLampCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struLampCtrl.dwSize = sizeof(NET_DVR_GATELAMP_INFO);
	m_struLampCtrl.dwChannel = 1;
	m_struLampCtrl.byLaneNo = m_comLampLaneNo.GetCurSel() + 1;
	m_struLampCtrl.byBrightlampCtrl = m_comLampCtrl.GetCurSel();
	
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_GATELAMP_CTRL, &m_struLampCtrl, sizeof(NET_DVR_GATELAMP_INFO)))
	{
		g_StringLanType(szLan, "常亮灯功能控制失败", "Lamp control failed");
		AfxMessageBox(szLan);
	}
	
	
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::CurCfgUpdate()
{
	int i = 0;
	for (; i<m_byIOInNum; i++)
	{
		CString str;
		str.Format(_T("Alarm Input port %d"),i + 1);
		m_comIOInNum.AddString(str);
	}
	m_comIOInNum.SetCurSel(0);
	
	for (i = 0; i<m_byRelayNum; i++)
	{
		CString str;
		str.Format(_T("Relay %d"),i + 1);
		m_comRelayNum.AddString(str);
	}
	m_comRelayNum.SetCurSel(0);
	OnBtnGetEntrance();
}

DWORD WINAPI CDlgITCIOinCfg::GetVehInfoThread(LPVOID lpVehInfo)
{
	//UpdateData(TRUE);
	CDlgITCIOinCfg* pThis = reinterpret_cast<CDlgITCIOinCfg*>(lpVehInfo);
	int iRet = 0;
	char szLan[128] = {0};
	char szInfoBuf[128] = {0};
	while (pThis->m_bGetNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_pStruVehInfo[pThis->m_iStruCount], sizeof(NET_DVR_VEHICLE_CONTROL_LIST_INFO)); 
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			int iItemCount = pThis->m_lstVehicle.GetItemCount();
			pThis->AddVehInfotoDlg(iItemCount, &pThis->m_pStruVehInfo[pThis->m_iStruCount]);
			pThis->m_iStruCount++;
		}
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
// 				CString str;
// 				str.Format(_T("%d"),pThis->m_lstVehicle.GetItemCount());
// 				pThis->GetDlgItem(IDC_EDIT_VEHICLE_INF0_COUNT)->GetWindowText(str);
				g_StringLanType(szLan, "长连接获取黑白名单数据结束!", "Get Black and White List Finish");
				sprintf(szInfoBuf, "%s[Info Count:%d]", szLan, pThis->m_lstVehicle.GetItemCount());
				AfxMessageBox(szInfoBuf);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "长连接获取黑白名单数据失败", "Get Black and White List failed");
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
	//UpdateData(FALSE);
	return 0 ;
}

void CDlgITCIOinCfg::AddVehInfotoDlg(int iItemCount, LPNET_DVR_VEHICLE_CONTROL_LIST_INFO lpInter)
{
	char szLan[128] = {0};

	if (iItemCount >= m_lstVehicle.GetItemCount())
	{
		m_lstVehicle.InsertItem(m_lstVehicle.GetItemCount(), "");
	}

	char szStr[128] = {0};
// 	sprintf(szStr, "%d", lpInter->dwDataIndex);
// 	m_lstVehicle.SetItemText(iItemCount, 0, szStr);

	memset(szStr, 0, sizeof(szStr));
	memcpy(szStr, lpInter->sLicense, MAX_LICENSE_LEN);
	m_lstVehicle.SetItemText(iItemCount, 0, szStr);

// 	char* sListType0 = "白名单";
// 	char* sListType1 = "黑名单";

	if (0 == lpInter->byListType)
	{
		g_StringLanType(szLan, "白名单", "White List");
		m_lstVehicle.SetItemText(iItemCount, 1, szLan);	
	}
	else if (1 == lpInter->byListType)
	{
		g_StringLanType(szLan, "黑名单", "Black List");
		m_lstVehicle.SetItemText(iItemCount, 1, szLan);
	}

// 	char* sPlateType0 = "标准民用车与军车";
// 	char* sPlateType1 = "02式民用车牌";
// 	char* sPlateType2 = "武警车";
// 	char* sPlateType3 = "警车";
// 	char* sPlateType4 = "民用车双行尾牌";
// 	char* sPlateType5 = "使馆车牌";
// 	char* sPlateType6 = "农用车";
// 	char* sPlateType7 = "摩托车";

	if (VCA_STANDARD92_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "标准民用车与军车", "civil and military ");	
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);	
	}
	else if (VCA_STANDARD02_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "02式民用车牌", "02 type of civil license");	
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
	else if (VCA_WJPOLICE_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "武警车", "Police Car");
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
	else if (VCA_JINGCHE_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "警车", "Police Wagon");
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
	else if (STANDARD92_BACK_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "民用车双行尾牌", "Double license");
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
	else if (VCA_SHIGUAN_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "使馆车", "Embassy license");
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
	else if (VCA_NONGYONG_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "农用车", "Agricultural license");	
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
	else if (VCA_MOTO_PLATE == lpInter->byPlateType)
	{
		g_StringLanType(szLan, "摩托车车牌", "Motorcycle license");
		m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
    else if (NEW_ENERGY_PLATE == lpInter->byPlateType)
    {
        g_StringLanType(szLan, "新能源车车牌", "new energy license");	
        m_lstVehicle.SetItemText(iItemCount, 2, szLan);
	}
	
// 	char* sPlateColor0 = "蓝色车牌";
// 	char* sPlateColor1 = "黄色车牌";
// 	char* sPlateColor2 = "白色车牌";
// 	char* sPlateColor3 = "黑色车牌";
// 	char* sPlateColor4 = "绿色车牌";
// 	char* sPlateColor5 = "其他";

	if (VCA_BLUE_PLATE == lpInter->byPlateColor)
	{
		g_StringLanType(szLan, "蓝色车牌", "Blue plate");
		m_lstVehicle.SetItemText(iItemCount, 3, szLan);	
	}
	else if (VCA_YELLOW_PLATE == lpInter->byPlateColor)
	{
		g_StringLanType(szLan, "黄色车牌", "Yellow plate");
		m_lstVehicle.SetItemText(iItemCount, 3, szLan);
	}
	else if (VCA_WHITE_PLATE == lpInter->byPlateColor)
	{
		g_StringLanType(szLan, "白色车牌", "White plate");
		m_lstVehicle.SetItemText(iItemCount, 3, szLan);
	}
	else if (VCA_BLACK_PLATE == lpInter->byPlateColor)
	{
		g_StringLanType(szLan, "黑色车牌", "Black plate");
		m_lstVehicle.SetItemText(iItemCount, 3, szLan);
	}
	else if (VCA_GREEN_PLATE == lpInter->byPlateColor)
	{
		g_StringLanType(szLan, "绿色车牌", "Green plate");
		m_lstVehicle.SetItemText(iItemCount, 3, szLan);
	}
	else if (VCA_OTHER == lpInter->byPlateColor)
	{
		g_StringLanType(szLan, "其他", "Other");
		m_lstVehicle.SetItemText(iItemCount, 3, szLan);
	}

	memset(szStr, 0, sizeof(szStr));
	memcpy(szStr, lpInter->sCardNo, MAX_CARDNO_LEN);
	m_lstVehicle.SetItemText(iItemCount, 4, szStr);

	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d-%d-%d %d:%d:%d", lpInter->struStartTime.wYear, lpInter->struStartTime.byMonth, \
		lpInter->struStartTime.byDay, lpInter->struStartTime.byHour, lpInter->struStartTime.byMinute,\
		lpInter->struStartTime.bySecond/*, lpInter->struStartTime.wMilliSec*/);
	char* strTemp = "0-0-0 0:0:0";
	if (0 == strcmp(szStr, strTemp))
	{
		m_lstVehicle.SetItemText(iItemCount, 5, "");
	}
	else
	{
		m_lstVehicle.SetItemText(iItemCount, 5, szStr);
	}
	

	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d-%d-%d %d:%d:%d", lpInter->struStopTime.wYear, lpInter->struStopTime.byMonth, \
		lpInter->struStopTime.byDay, lpInter->struStopTime.byHour, lpInter->struStopTime.byMinute,\
		lpInter->struStopTime.bySecond/*, lpInter->struStopTime.wMilliSec*/);
	if (0 == strcmp(szStr, strTemp))
	{
		m_lstVehicle.SetItemText(iItemCount, 6, "");
	}
	else
	{
		m_lstVehicle.SetItemText(iItemCount, 6, szStr);
	}
}

void CDlgITCIOinCfg::OnBtnVehicleControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	//memset(&m_struVehCond, 0, sizeof(m_struVehCond));
	m_struVehCond.dwChannel = 1;
	memcpy(m_struVehCond.sLicense, m_csPlateNumVeh, sizeof(m_struVehCond.sLicense));
	memcpy(m_struVehCond.sCardNo, m_csCardNumVeh, sizeof(m_struVehCond.sCardNo));
	if(2 == m_comListTypeVeh.GetCurSel())
	{
		m_struVehCond.byListType = 0xff;
	}
	else 
	{
		m_struVehCond.byListType = m_comListTypeVeh.GetCurSel();
	}

	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			m_bGetNext = FALSE;
			g_StringLanType(szLan, "同步黑白名单数据停止失败", "Vehicle Black and White List Stop Failed");
			AfxMessageBox(szLan);
			return;
		}
		//g_StringLanType(szLan, "请求长连接获取黑白名单数据失败", "Ask Get Black and White List failed");
		//AfxMessageBox(szLan);
		//return;
	} 

	m_lHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_ALL_VEHICLE_CONTROL_LIST, &m_struVehCond, sizeof(m_struVehCond), NULL, NULL);
	if (m_lHandle >= 0)
	{
		m_bGetNext = TRUE;
		DWORD dwThreadId;
		m_lstVehicle.DeleteAllItems();
		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetVehInfoThread), this, 0, &dwThreadId);
	}
	else
	{
		m_bGetNext = FALSE;
		g_StringLanType(szLan, "请求长连接获取黑白名单数据失败", "Ask Get Black and White List failed");
		sprintf(szLan, "%s 错误码：%d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
	
}

// void CDlgITCIOinCfg::OnClickListVehicle(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	// TODO: Add your control notification handler code here
// 
// }

void CDlgITCIOinCfg::AnalysisTime(CString strTime)
{
	if ("" == strTime)
	{
		return;
	}

	memset(&m_struTime, 0, sizeof(m_struTime));	
	CString csYear, csMon, csDay, csHour, csMin, csSec, csMilliSec;
	int nPos0 = strTime.FindOneOf("-");
	csYear = strTime.Left(nPos0);
	m_struTime.wYear = atoi(csYear);

	int nPos1 = strTime.Find("-", nPos0 + 1);
	csMon = strTime.Mid(nPos0 + 1, nPos1 - nPos0 -1);
	m_struTime.byMonth = atoi(csMon);

	int nPos2 = strTime.Find(" ", nPos1 + 1);
	csDay = strTime.Mid(nPos1 + 1, nPos2 - nPos1 -1);
	m_struTime.byDay = atoi(csDay);

	int nPos3 = strTime.Find(":", nPos2 + 1);
	csHour = strTime.Mid(nPos2 + 1, nPos3 - nPos2 -1);
	m_struTime.byHour = atoi(csHour);

	int nPos4 = strTime.Find(":", nPos3 + 1);
	csMin = strTime.Mid(nPos3 + 1, nPos4 - nPos3 -1);
	m_struTime.byMinute = atoi(csMin);

	int nPos5 = strTime.Find(" ", nPos4 + 1);
	csSec = strTime.Mid(nPos4 + 1, nPos5 - nPos4 -1);
	m_struTime.bySecond = atoi(csSec);

// 	csMilliSec = strTime.Right(strTime.GetLength() - (nPos5 + 1));
// 	m_struTime.wMilliSec = atoi(csMilliSec);
}

void CDlgITCIOinCfg::OnBtnSyncVehicleControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bCheckSet = TRUE;
	char szLan[128] = {0};
	memset(&m_struVehInfo, 0, sizeof(NET_DVR_VEHICLE_CONTROL_LIST_INFO));
	m_struVehInfo.dwSize = sizeof(NET_DVR_VEHICLE_CONTROL_LIST_INFO);
	m_struVehInfo.dwChannel = 1;
	m_struVehInfo.dwDataIndex = 0;
	memset(m_struVehInfo.sOperateIndex, 0, sizeof(MAX_OPERATE_INDEX_LEN));
	
// 	CString str = _T("123456");
// 	memcpy(m_struVehInfo.sOperateIndex, str, MAX_OPERATE_INDEX_LEN);
	if (0 == m_csLicenseTemp.Compare(_T("")))
	{
		m_bCheckSet = FALSE;
		g_StringLanType(szLan, "请输入车牌号！", "Please enter the license plate number!");
		AfxMessageBox(szLan);
		return;
	}
	memcpy(m_struVehInfo.sLicense, m_csLicenseTemp, MAX_LICENSE_LEN);
	m_struVehInfo.byListType = m_comListTypeTemp.GetCurSel();
	m_struVehInfo.byPlateType = m_comPlateTypeTemp.GetCurSel();
	if (5 == m_comPlateColorTemp.GetCurSel())
	{
		m_struVehInfo.byPlateColor = 0xff;
	}
	else
	{
		m_struVehInfo.byPlateColor = m_comPlateColorTemp.GetCurSel();
	}
	memcpy(m_struVehInfo.sCardNo, m_csCardNoTemp, MAX_CARDNO_LEN);

	if (m_bCheckStartTime)
	{
		if (m_startDate > m_stopDate)
		{
			m_bCheckSet = FALSE;
			g_StringLanType(szLan, "开始时间不能大于结束时间！", "The start time is not greater than the end time!");
			AfxMessageBox(szLan);
			return;
		}
		else if (m_startDate == m_stopDate)
		{
			if (m_startTime > m_stopTime)
			{
				m_bCheckSet = FALSE;
				g_StringLanType(szLan, "开始时间不能大于结束时间！", "The start time is not greater than the end time!");
				AfxMessageBox(szLan);
				return;
			}
		}

		m_struVehInfo.struStartTime.wYear = m_startDate.GetYear();
		m_struVehInfo.struStartTime.byMonth = m_startDate.GetMonth();
		m_struVehInfo.struStartTime.byDay = m_startDate.GetDay();
		m_struVehInfo.struStartTime.byHour = m_startTime.GetHour();
		m_struVehInfo.struStartTime.byMinute = m_startTime.GetMinute();
		m_struVehInfo.struStartTime.bySecond = m_startTime.GetSecond();
		//m_struVehInfo.struStartTime.wMilliSec = m_startMilliSec;
		
		m_struVehInfo.struStopTime.wYear = m_stopDate.GetYear();
		m_struVehInfo.struStopTime.byMonth = m_stopDate.GetMonth();
		m_struVehInfo.struStopTime.byDay = m_stopDate.GetDay();
		m_struVehInfo.struStopTime.byHour = m_stopTime.GetHour();
		m_struVehInfo.struStopTime.byMinute = m_stopTime.GetMinute();
		m_struVehInfo.struStopTime.bySecond = m_stopTime.GetSecond();
		//m_struVehInfo.struStopTime.wMilliSec = m_stopMilliSec;
	}
	else
	{
		memset(&m_struVehInfo.struStartTime, 0, sizeof(NET_DVR_TIME_V30));
		memset(&m_struVehInfo.struStopTime, 0, sizeof(NET_DVR_TIME_V30));
	}


// 	if (m_iItem>0)
// 	{
// 		AddVehInfotoDlg(m_iItem, &m_struVehInfo);
// 	}

	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnBtnSendVehData() 
{
	// TODO: Add your control notification handler code here
	OnBtnSyncVehicleControl();

	UpdateData(TRUE);
	if (m_bCheckSet)
	{
		char szLan[128] = {0};
		char szLanTemp[16] = {0};
		if (m_lSyncVehHandle < 0)
		{
			g_StringLanType(szLan, "建立连接失败", "Create Link Failed");
			AfxMessageBox(szLan);
			return;
		}

// 		NET_DVR_VEHICLE_CONTROL_LIST_INFO m_struVehInfoTemp[MAX_MUN] = {0};
// 		for (int i = 0; i < MAX_MUN; i++)
// 		{
// 			m_struVehInfoTemp[i].dwSize = sizeof(NET_DVR_VEHICLE_CONTROL_LIST_INFO);
// 			if(i==50 || i==78)
// 			{
// 				sprintf(szLanTemp, "");
// 			}
// 			else
// 			{
// 				sprintf(szLanTemp, "1234%d", i);	
// 			}
// 			
// 			memcpy(m_struVehInfoTemp[i].sLicense, szLanTemp, 16);
// 		}
// 		
		if (!NET_DVR_SendRemoteConfig(m_lSyncVehHandle,0,(char*)&m_struVehInfo,sizeof(m_struVehInfo)/**MAX_MUN*/))
		{
			g_StringLanType(szLan, "同步黑白名单数据发送失败", "Vehicle Black and White List Send Failed");
			sprintf(szLan, "%s 错误码：%d", szLan, NET_DVR_GetLastError());
			AfxMessageBox(szLan);
			return;
		}

// 		if (!NET_DVR_SendRemoteConfig(m_lSyncVehHandle,DVR_VEHICLE_CONTROL_LIST,(char*)&m_struVehInfo,sizeof(m_struVehInfo)))
// 		{
// 			g_StringLanType(szLan, "同步黑白名单数据发送失败", "Vehicle Black and White List Send Failed");
// 			sprintf(szLan, "%s 错误码：%d", szLan, NET_DVR_GetLastError());
// 			AfxMessageBox(szLan);
// 			return;
// 		}
		
		GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SEND_VEH_DATA)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_STOP_VEH_DATA)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnBtnStopVehData() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	if (m_lSyncVehHandle < 0)
	{
	//	g_StringLanType(szLan, "建立连接失败", "Create Link Failed");
	//	AfxMessageBox(szLan);
		return;
	}

	
	if (!NET_DVR_StopRemoteConfig(m_lSyncVehHandle))
	{
		g_StringLanType(szLan, "同步黑白名单数据停止失败", "Vehicle Black and White List Stop Failed");
		sprintf(szLan, "%s 错误码：%d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}

	m_lSyncVehHandle = -1;
	GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SEND_VEH_DATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP_VEH_DATA)->EnableWindow(FALSE);

}

void CALLBACK VehicleCtrlCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	char szLan[128] = {0};
	
	if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD *)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			AfxMessageBox("设备发送信息成功");
		}
		else if(dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
		{
			AfxMessageBox("设备发送信息处理中");	
		}
		else if(dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
		{
			char* pBuf = new char[dwBufLen]; 
			memcpy(pBuf, /*(char*)*/lpBuffer, dwBufLen);
			char* pBufTemp = pBuf;
			pBufTemp += 4;
			for (int i = 0; i < (dwBufLen-4)/4; i++)
			{
				if (*(DWORD*)(pBufTemp) != 0)
				{
					sprintf(szLan, "第 %d 组数据的错误码是: %d", i+1, *(DWORD*)(pBufTemp));
					AfxMessageBox(szLan);
				}
				pBufTemp += 4;
			}
		}
		else if(dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
		{
			AfxMessageBox("设备返回异常");	
		}
	}
	return;
}

void CDlgITCIOinCfg::OnBtnCreateLink() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	if (m_lSyncVehHandle >= 0)
	{
		g_StringLanType(szLan, "连接已经建立", "Has already been created Link");
		AfxMessageBox(szLan);
		return;
	} 


	m_lSyncVehHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_VEHICLELIST_CTRL_START/*NET_DVR_VEHICLE_CONTROL_LIST_START*/,NULL,0,VehicleCtrlCB,this);

	if (m_lSyncVehHandle < 0)
	{
		g_StringLanType(szLan, "同步黑白名单数据连接失败", "Vehicle Black and White List Link Failed");
		sprintf(szLan, "%s 错误码：%d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}

	GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SEND_VEH_DATA)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP_VEH_DATA)->EnableWindow(TRUE);
}

void CDlgITCIOinCfg::OnSelchangeComboDelCond() 
{
	// TODO: Add your control notification handler code here
	m_struDelVehicleInfo.dwDelType = 0;
	if (0 == m_comDelCond.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LIST_DEL_TYPE_VEHICLE)->EnableWindow(FALSE);
		m_struDelVehicleInfo.dwDelType = VCA_LICENSE_TYPE;

	}
	else if (1 == m_comDelCond.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LIST_DEL_TYPE_VEHICLE)->EnableWindow(FALSE);
		m_struDelVehicleInfo.dwDelType = VCA_PLATECOLOR_TYPE;
	}
	else if (2 == m_comDelCond.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LIST_DEL_TYPE_VEHICLE)->EnableWindow(FALSE);
		m_struDelVehicleInfo.dwDelType |= VCA_LICENSE_TYPE;
		m_struDelVehicleInfo.dwDelType |= VCA_PLATECOLOR_TYPE;
	}
	else if (3 == m_comDelCond.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LIST_DEL_TYPE_VEHICLE)->EnableWindow(FALSE);
		m_struDelVehicleInfo.dwDelType = VCA_CARDNO_TYPE;
	}
	else if (4 == m_comDelCond.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LIST_DEL_TYPE_VEHICLE)->EnableWindow(FALSE);
		m_struDelVehicleInfo.dwDelType = VCA_PLATETYPE_TYPE;
	}
	else if (5 == m_comDelCond.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LIST_DEL_TYPE_VEHICLE)->EnableWindow(TRUE);
		m_struDelVehicleInfo.dwDelType = VCA_LISTTYPE_TYPE;
	}

}

void CDlgITCIOinCfg::OnSelchangeComboOperateType() 
{
	// TODO: Add your control notification handler code here
	if (1 == m_comOperateType.GetCurSel())
	{
		GetDlgItem(IDC_COMBO_DEL_COND)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);
	}
	else if (0 == m_comOperateType.GetCurSel())
	{
		GetDlgItem(IDC_COMBO_DEL_COND)->EnableWindow(TRUE);
		OnSelchangeComboDelCond();
// 		GetDlgItem(IDC_EDIT_PLATE_NUM)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_CARD_NUM)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_COMBO_PLATE_COLOR)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_COMBO_PLATE_TYPE)->EnableWindow(FALSE);
	}
}

void CDlgITCIOinCfg::OnBtnSaveEntrance() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	if(0 == m_comLane.GetCurSel())
// 	{
// 		return;
// 	}

	LPNET_DVR_ENTRANCE_CFG pstruEntranceTmp = &m_struEntrance;
	pstruEntranceTmp += m_comLane.GetCurSel();
	
	int i = m_comVehicleControl.GetCurSel();
	pstruEntranceTmp->struVehicleCtrl[i].byGateOperateType = m_comGateType.GetCurSel();
	pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType = 0;
	pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType |= (m_bRelay << 0);
	pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType |= (m_bArm << 1);
	pstruEntranceTmp->struVehicleCtrl[i].wAlarmOperateType |= (m_bAlarmHost << 2);
	
	i = m_comRelayNum.GetCurSel();
	pstruEntranceTmp->struRelayRelateInfo[i].byAccessDevInfo = m_comRelayInfo.GetCurSel();

	i = m_comIOInNum.GetCurSel();
	pstruEntranceTmp->byGateSingleIO[i] = m_comGateSingleIO.GetCurSel();


	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnCheckStartTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!m_bCheckStartTime)
	{
		GetDlgItem(IDC_START_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_START_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP_TIME)->EnableWindow(FALSE);
	} 
	else
	{
		GetDlgItem(IDC_START_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_START_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STOP_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STOP_TIME)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnCheckStopTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!m_bCheckStopTime)
	{
		GetDlgItem(IDC_STOP_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STOP_TIME)->EnableWindow(FALSE);
	} 
	else
	{
		GetDlgItem(IDC_STOP_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STOP_TIME)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

void CDlgITCIOinCfg::OnSelchangeComboOperateTypeVeh() 
{
	// TODO: Add your control notification handler code here
	m_struVehCond.dwOperateType = 0;
	if (0 == m_comOperateTypeVeh.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM_VEHICLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CARD_NUM_VEHICLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LIST_TYPE_VEHICLE)->EnableWindow(FALSE);
		m_struVehCond.dwOperateType = VCA_LICENSE_TYPE;
		
	}
	else if (1 == m_comOperateTypeVeh.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM_VEHICLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARD_NUM_VEHICLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LIST_TYPE_VEHICLE)->EnableWindow(FALSE);
		m_struVehCond.dwOperateType = VCA_CARDNO_TYPE;
	}
	else if (2 == m_comOperateTypeVeh.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_PLATE_NUM_VEHICLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CARD_NUM_VEHICLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LIST_TYPE_VEHICLE)->EnableWindow(TRUE);
		m_struVehCond.dwOperateType = VCA_LISTTYPE_TYPE;
	}
}

void CDlgITCIOinCfg::OnDblclkListVehicle(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);
	char szStr[128] = {0};
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	m_iItem = pEditCtrl->iItem;
	int m_iSubItem = pEditCtrl->iSubItem;
	CString csTemp;

	if (m_iItem >= 0)
	{
// 		m_struVehInfo.dwSize = sizeof(NET_DVR_VEHICLE_CONTROL_LIST_INFO);
// 		m_struVehInfo.dwChannel = 1;

// 		csTemp = "";
// 		csTemp = m_lstVehicle.GetItemText(m_iItem, 0);
// 		memcpy(szStr, csTemp, csTemp.GetLength());
// 		m_dwDataIndexTemp = atoi(szStr);

		//csTemp = "";
		m_csLicenseTemp = m_lstVehicle.GetItemText(m_iItem, 0);
		//memcpy(m_struVehInfo.sLicense, csTemp, MAX_LICENSE_LEN);

		csTemp = "";
		csTemp = m_lstVehicle.GetItemText(m_iItem, 1);
		if ("白名单" == csTemp)
		{
			m_comListTypeTemp.SetCurSel(0);
		}
		else if ("黑名单" == csTemp)
		{
			m_comListTypeTemp.SetCurSel(1);
		}

		csTemp = "";
		csTemp = m_lstVehicle.GetItemText(m_iItem, 2);
		if ("标准民用车与军车" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(0);
		}
		else if ("02式民用车牌" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(1);
		}
		else if ("武警车" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(2);
		}
		else if ("警车" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(3);
		}
		else if ("民用车双行尾牌" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(4);
		}
		else if("使馆车牌" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(5);
		}
		else if ("农用车" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(6);
		}
		else if("摩托车" == csTemp)
		{
			m_comPlateTypeTemp.SetCurSel(7);
		}
	

		csTemp = "";
		csTemp = m_lstVehicle.GetItemText(m_iItem, 3);
		if ("蓝色车牌" == csTemp)
		{
			m_comPlateColorTemp.SetCurSel(0);
		}
		else if ("黄色车牌" == csTemp)
		{
			m_comPlateColorTemp.SetCurSel(1);
		}
		else if ("白色车牌" == csTemp)
		{
			m_comPlateColorTemp.SetCurSel(2);
		}
		else if ("黑色车牌" == csTemp)
		{
			m_comPlateColorTemp.SetCurSel(3);
		}
		else if ("绿色车牌" == csTemp)
		{
			m_comPlateColorTemp.SetCurSel(4);
		}
		else if("其他" == csTemp)
		{
			m_comPlateColorTemp.SetCurSel(5);
		}
		
		//csTemp = "";
		m_csCardNoTemp = m_lstVehicle.GetItemText(m_iItem, 4);
		//memcpy(m_struVehInfo.sCardNo, csTemp, MAX_CARDNO_LEN);

		csTemp = "";
		csTemp = m_lstVehicle.GetItemText(m_iItem, 5);

		if (0 != csTemp.Compare(_T("")))
		{
			m_bCheckStartTime = TRUE;

			AnalysisTime(csTemp);
			m_startDate.SetDate(m_struTime.wYear, m_struTime.byMonth, m_struTime.byDay);
			m_startTime.SetTime(m_struTime.byHour, m_struTime.byMinute, m_struTime.bySecond);
			//m_startMilliSec = m_struTime.wMilliSec;
		}
		else
		{
			m_bCheckStartTime = FALSE;
		}

		csTemp = "";
		csTemp = m_lstVehicle.GetItemText(m_iItem, 6);

		if (0 != csTemp.Compare(_T("")))
		{
			m_bCheckStartTime = TRUE;

			AnalysisTime(csTemp);
			m_stopDate.SetDate(m_struTime.wYear, m_struTime.byMonth, m_struTime.byDay);
			m_stopTime.SetTime(m_struTime.byHour, m_struTime.byMinute, m_struTime.bySecond);
			//m_stopMilliSec = m_struTime.wMilliSec;
		} 
		else
		{
			m_bCheckStartTime = FALSE;
		}

	
	}
	*pResult = 0;
	UpdateData(FALSE);
	OnCheckStartTime(); 
}

void CDlgITCIOinCfg::OnBtnTest()
{
	ListTest();
}