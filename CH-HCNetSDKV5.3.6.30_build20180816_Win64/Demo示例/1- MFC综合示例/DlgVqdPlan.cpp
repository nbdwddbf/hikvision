// DlgVqdPlan.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVqdPlan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD WINAPI CDlgVqdPlan::GetVqdPlanThread(LPVOID lpArg)
{
	CDlgVqdPlan* pThis = reinterpret_cast<CDlgVqdPlan*>(lpArg);
	int iRet = 0;
	char szLan[128] = {0};
	while (pThis->m_bGetNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_pStruPlanVqdCfg[pThis->m_iStruCount], sizeof(NET_DVR_PLAN_VQD_CFG));
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddVqdPlanInfoToDlg(&(pThis->m_pStruPlanVqdCfg[pThis->m_iStruCount]));
			pThis->m_iStruCount++;
		}
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				//pThis->AddVqdPlanInfoToDlg(&(pThis->m_pStruPlanVqdCfg[pThis->m_iStruCount]));
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				//pThis->AddVqdPlanInfoToDlg(&(pThis->m_pStruPlanVqdCfg[pThis->m_iStruCount]));
				g_StringLanType(szLan, "获取诊断计划列表结束!", "Get VQD Plan List Finished");
				g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, szLan);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取诊断计划列表结束!", "Get VQD Plan List failed");
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
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lHandle = -1;
		}
	}
	return 0 ;
}

DWORD WINAPI CDlgVqdPlan::GetMonitorInfoThread(LPVOID lpArg)
{
	CDlgVqdPlan* pThis = reinterpret_cast<CDlgVqdPlan*>(lpArg);
	int iRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetMonitorNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lMonitorHandle, &pThis->m_pStruStreamInfo[pThis->m_iStruCount], sizeof(NET_DVR_STREAM_INFO));
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddMonitorInfoToList(&(pThis->m_pStruStreamInfo[pThis->m_iStruCount]));
			pThis->m_iMonitorStruCount++;
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
				g_StringLanType(szLan, "获取诊断信息列表结束!", "Get VQD Info List Finished");
				g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, szLan);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取诊断信息列表结束!", "Get VQD Info List failed");
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
	if (-1 != pThis->m_lMonitorHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lMonitorHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetMonitorNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetMonitorNext = FALSE;
			pThis->m_lMonitorHandle = -1;
		}
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CDlgVqdPlan dialog


CDlgVqdPlan::CDlgVqdPlan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVqdPlan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVqdPlan)
	m_iWperiod = 0;
	m_dwStreamIDNum = 0;
	m_csStreamID = _T("");
	m_csPlanID = _T("");
	m_byMintueEnd = 0;
	m_byMintueBegin = 0;
	m_byHourEnd = 0;
	m_byHourBegin = 0;
	m_bStreak = FALSE;
	m_bSnow = FALSE;
	m_bSignal = FALSE;
	m_bPtz = FALSE;
	m_bLuma = FALSE;
	m_bFreeze = FALSE;
	m_bChroma = FALSE;
	m_bCheckFlag = FALSE;
	m_bBlur = FALSE;
	m_csStreamID1 = _T("");
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iHour31 = 0;
	m_iHour32 = 0;
	m_iHour41 = 0;
	m_iHour42 = 0;
	m_iHour51 = 0;
	m_iHour52 = 0;
	m_iHour61 = 0;
	m_iHour62 = 0;
	m_iHour71 = 0;
	m_iHour72 = 0;
	m_iHour81 = 0;
	m_iHour82 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_iMin31 = 0;
	m_iMin32 = 0;
	m_iMin41 = 0;
	m_iMin42 = 0;
	m_iMin51 = 0;
	m_iMin52 = 0;
	m_iMin61 = 0;
	m_iMin62 = 0;
	m_iMin71 = 0;
	m_iMin72 = 0;
	m_iMin81 = 0;
	m_iMin82 = 0;
	m_csListPlanID = _T("");
	m_bCycleCheck = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struPlanVqdCfg, 0, sizeof(m_struPlanVqdCfg));
	m_bGetMonitorInfo = FALSE;
	m_bSetMonitorInfo = FALSE;
	m_pStruPlanVqdCfg = NULL;
	m_pStruStreamInfo = NULL;
	m_lHandle = -1;
	m_lMonitorHandle = -1;
	memset(&m_struPlanVqdCfgTemp, 0, 64*sizeof(NET_DVR_PLAN_VQD_CFG));
}


void CDlgVqdPlan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVqdPlan)
	DDX_Control(pDX, IDC_COMBO_PLANMODE, m_comboPlanMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_LIST_VQD_PLAN, m_lstVqdPlan);
	DDX_Control(pDX, IDC_LIST_MONITOR_INFO, m_lstMonitorInfo);	
	DDX_Text(pDX, IDC_EDIT_WPERIOD, m_iWperiod);
	DDX_Text(pDX, IDC_EDIT_STREAMID_NUM, m_dwStreamIDNum);
	DDX_Text(pDX, IDC_EDIT_PLANID, m_csPlanID);
	DDX_Check(pDX, IDC_CHECK_STREAK, m_bStreak);
	DDX_Check(pDX, IDC_CHECK_SNOW, m_bSnow);
	DDX_Check(pDX, IDC_CHECK_SIGNAL, m_bSignal);
	DDX_Check(pDX, IDC_CHECK_PTZ, m_bPtz);
	DDX_Check(pDX, IDC_CHECK_LUMA, m_bLuma);
	DDX_Check(pDX, IDC_CHECK_FREEZE, m_bFreeze);
	DDX_Check(pDX, IDC_CHECK_CHROMA, m_bChroma);
	DDX_Check(pDX, IDC_CHECK_CHECKFLAG, m_bCheckFlag);
	DDX_Check(pDX, IDC_CHECK_BLUR, m_bBlur);
	DDX_Text(pDX, IDC_EDIT_STREAMID1, m_csStreamID1);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
	DDX_Check(pDX, IDC_CHK_CYCLE, m_bCycleCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVqdPlan, CDialog)
	//{{AFX_MSG_MAP(CDlgVqdPlan)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_CHECK_PTZ, OnCheckPtz)
	ON_BN_CLICKED(IDC_CHECK_SIGNAL, OnCheckSignal)
	ON_BN_CLICKED(IDC_CHECK_BLUR, OnCheckBlur)
	ON_BN_CLICKED(IDC_CHECK_FREEZE, OnCheckFreeze)
	ON_BN_CLICKED(IDC_CHECK_LUMA, OnCheckLuma)
	ON_BN_CLICKED(IDC_CHECK_SNOW, OnCheckSnow)
	ON_BN_CLICKED(IDC_CHECK_STREAK, OnCheckStreak)
	ON_BN_CLICKED(IDC_CHECK_CHROMA, OnCheckChroma)
	ON_NOTIFY(NM_CLICK, IDC_LIST_VQD_PLAN, OnClickListVqdPlan)
	ON_BN_CLICKED(IDC_BTN_DEL_MONITOR_INFO, OnBtnMoitorDel)
	ON_BN_CLICKED(IDC_BTN_SET_MOITOR_INFO, OnBtnMoitorSet)
	ON_BN_CLICKED(IDC_BTN_ADD_MONITOR_INFO, OnBtnMoitorAdd)
	ON_BN_CLICKED(IDC_BTN_DEL_PLAN, OnBtnDelPlan)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_OUT_WEEKDAY, OnSelchangeComboAlarmOutWeekday)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_CBN_SELCHANGE(IDC_COMBO_PLANMODE, OnSelchangeComboPlanmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVqdPlan message handlers

BOOL CDlgVqdPlan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pStruPlanVqdCfg = new NET_DVR_PLAN_VQD_CFG[MAX_ALARMHOST_ALARMOUT_NUM];
	memset(m_pStruPlanVqdCfg, 0, sizeof(NET_DVR_PLAN_VQD_CFG)*MAX_ALARMHOST_ALARMOUT_NUM);

	m_pStruStreamInfo = new NET_DVR_STREAM_INFO[MAX_ALARMHOST_ALARMOUT_NUM];
	memset(m_pStruStreamInfo, 0, sizeof(NET_DVR_STREAM_INFO)*MAX_ALARMHOST_ALARMOUT_NUM);

	// TODO: Add extra initialization here
	m_lstVqdPlan.SetExtendedStyle(m_lstVqdPlan.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_lstMonitorInfo.SetExtendedStyle(m_lstMonitorInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	char szLan[128] = {0};

	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstMonitorInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "监控点ID", "Monitor ID.");
	m_lstMonitorInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "计划设置状态", "Check.");
	m_lstMonitorInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 120, -1);

	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstVqdPlan.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "计划ID", "Plan ID.");
	m_lstVqdPlan.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "计划模式", "Period.");
	m_lstVqdPlan.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "视频丢失", "Signal.");
	m_lstVqdPlan.InsertColumn(3, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "图像模糊", "Blur.");
	m_lstVqdPlan.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "亮度异常", "Luma.");
	m_lstVqdPlan.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "偏色检测", "Chroma.");
	m_lstVqdPlan.InsertColumn(6, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "雪花点干扰", "Snow.");
	m_lstVqdPlan.InsertColumn(7, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "条纹干扰", "Streak.");
	m_lstVqdPlan.InsertColumn(8, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "画面冻结", "Freeze.");
	m_lstVqdPlan.InsertColumn(9, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "云台", "PTZ.");
	m_lstVqdPlan.InsertColumn(10, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "是否检测", "Check.");
	m_lstVqdPlan.InsertColumn(11, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "是否循环检测", "Cycle Check.");
	m_lstVqdPlan.InsertColumn(12, szLan, LVCFMT_LEFT, 120, -1);

	g_StringLanType(szLan, "计划设置状态", "Check.");
	m_lstVqdPlan.InsertColumn(13, szLan, LVCFMT_LEFT, 120, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVqdPlan::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szErrLan[128] = {0};
	int i = 0;

	CString strTemp;	
	int iItemCount = m_lstVqdPlan.GetItemCount();

	//修改代码
	for (i = 0; i < iItemCount; i++)
	{
		if (0 == strcmp(m_lstVqdPlan.GetItemText(i, 1), m_csPlanID))
		{
			iItemCount = i;
			m_lstVqdPlan.DeleteItem(i);
		}
	}
	

	if (iItemCount > 64)
	{
		g_StringLanType(szLan, "监控计划超过64个", "Monitor Plan is more than 64");
		AfxMessageBox(szLan);
		return;
	}
	strTemp.Format("%02d", iItemCount+1);
	m_lstVqdPlan.InsertItem(iItemCount, strTemp);
	if (m_csPlanID.GetLength() > 32)
	{
		g_StringLanType(szErrLan, "参数长度错误!", "Param Length Error");
		AfxMessageBox(szErrLan);
		return;
	}
	m_lstVqdPlan.SetItemText(iItemCount, 1, m_csPlanID);
	memcpy(&m_struPlanVqdCfgTemp[iItemCount].sPlanID, m_csPlanID, PLAN_ID_LEN);

	char sPlanMode1[32] = "";
	char sPlanMode2[32] = "";

	g_StringLanType(sPlanMode1,"即时计划","Immediate Plans");
	g_StringLanType(sPlanMode2,"周期计划","Cycle Plan");

	if (m_comboPlanMode.GetCurSel() == 0)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 2, sPlanMode1);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 2, sPlanMode2);
	}

	char sCheck[32] = "";
	g_StringLanType(sCheck,"检测","Detection [Yes]");
	char sNoCheck[32] = "";
	g_StringLanType(sNoCheck,"不检测","Detection [No]");
	
	char sCycleCheck[32] = "循环检测";
	g_StringLanType(sCycleCheck,"循环检测","Loop Detection");
	

	char sNoCycleCheck[32] = "不循环检测";
	g_StringLanType(sNoCycleCheck,"循环检测","Loop Detection [No]");

	if (TRUE == m_bSignal)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 3, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 3, sNoCheck);
	}
	if (TRUE == m_bBlur)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 4, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 4, sNoCheck);
	}
	if (TRUE == m_bLuma)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 5, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 5, sNoCheck);
	}
	if (TRUE == m_bChroma)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 6, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 6, sNoCheck);
	}
	if (TRUE == m_bSnow)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 7, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 7, sNoCheck);
	}
	if (TRUE == m_bStreak)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 8, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 8, sNoCheck);
	}
	if (TRUE == m_bFreeze)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 9, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 9, sNoCheck);
	}
	if (TRUE == m_bPtz)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 10, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 10, sNoCheck);
	}

	if (TRUE == m_bCheckFlag)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 11, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 11, sNoCheck);
	}

	if (TRUE == m_bCycleCheck)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 12, sCycleCheck);
	}
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 12, sNoCycleCheck);
	}
	
}

void CDlgVqdPlan::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	while(m_lstVqdPlan.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_lstVqdPlan.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstVqdPlan.DeleteItem(nItem);
		memset(&m_struPlanVqdCfgTemp[nItem], 0, sizeof(NET_DVR_PLAN_VQD_CFG));
	}

	m_iWperiod = 0;
	m_dwStreamIDNum = 0;
	m_csStreamID = _T("");
	m_csPlanID = _T("");
	m_byMintueEnd = 0;
	m_byMintueBegin = 0;
	m_byHourEnd = 0;
	m_byHourBegin = 0;
	m_bStreak = FALSE;
	m_bSnow = FALSE;
	m_bSignal = FALSE;
	m_bPtz = FALSE;
	m_bLuma = FALSE;
	m_bFreeze = FALSE;
	m_bChroma = FALSE;
	m_bCheckFlag = FALSE;
	m_bBlur = FALSE;
	m_csStreamID1 = _T("");
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iHour31 = 0;
	m_iHour32 = 0;
	m_iHour41 = 0;
	m_iHour42 = 0;
	m_iHour51 = 0;
	m_iHour52 = 0;
	m_iHour61 = 0;
	m_iHour62 = 0;
	m_iHour71 = 0;
	m_iHour72 = 0;
	m_iHour81 = 0;
	m_iHour82 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_iMin31 = 0;
	m_iMin32 = 0;
	m_iMin41 = 0;
	m_iMin42 = 0;
	m_iMin51 = 0;
	m_iMin52 = 0;
	m_iMin61 = 0;
	m_iMin62 = 0;
	m_iMin71 = 0;
	m_iMin72 = 0;
	m_iMin81 = 0;
	m_iMin82 = 0;
	m_csListPlanID = _T("");
	m_bCycleCheck = FALSE;
	
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnBtnSet() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};

	LPNET_DVR_PLAN_VQD_CFG pMonitorPlanCfg = NULL;
	LPNET_DVR_PLAN_VQD_CFG pMonitorPlanCfgTemp = NULL;

	int iItemCount = m_lstVqdPlan.GetItemCount();
	if (iItemCount == 0)
	{
		g_StringLanType(szLan, "请添加计划信息!", "Please Add Plan Info");
		AfxMessageBox(szLan);

		return;
	}
	pMonitorPlanCfg = new NET_DVR_PLAN_VQD_CFG[iItemCount];
	if (NULL == pMonitorPlanCfg)
	{
		g_StringLanType(szLan,"申请内存失败","new memory failed");
		AfxMessageBox(szLan);
		return;
	}
	memset(pMonitorPlanCfg, 0, iItemCount*sizeof(NET_DVR_PLAN_VQD_CFG));
	pMonitorPlanCfgTemp = pMonitorPlanCfg;

	int i = 0; 
	for (i=0; i<iItemCount; i++)
	{
		pMonitorPlanCfgTemp->dwSize = sizeof(NET_DVR_PLAN_VQD_CFG);
		
		if (0 == strcmp("即时计划", m_lstVqdPlan.GetItemText(i, 2)))
		{
			pMonitorPlanCfgTemp->byPlanMode = 0;
		} 
		else
		{
			pMonitorPlanCfgTemp->byPlanMode = 1;
		}

		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 3)))
		{
			pMonitorPlanCfgTemp->bySignal = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->bySignal = 0;
		}

		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 4)))
		{
			pMonitorPlanCfgTemp->byBlur = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byBlur = 0;
		}
		
		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 5)))
		{
			pMonitorPlanCfgTemp->byLuma = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byLuma = 0;
		}

		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 6)))
		{
			pMonitorPlanCfgTemp->byChroma = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byChroma = 0;
		}

		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 7)))
		{
			pMonitorPlanCfgTemp->bySnow = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->bySnow = 0;
		}

		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 8)))
		{
			pMonitorPlanCfgTemp->byStreak = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byStreak = 0;
		}

		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 9)))
		{
			pMonitorPlanCfgTemp->byFreeze = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byFreeze = 0;
		}

		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 10)))
		{
			pMonitorPlanCfgTemp->byPTZ = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byPTZ = 0;
		}
		
		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 11)))
		{
			pMonitorPlanCfgTemp->byCheckFlag = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byCheckFlag = 0;
		}

		if (0 == strcmp("循环检测", m_lstVqdPlan.GetItemText(i, 12)))
		{
			pMonitorPlanCfgTemp->byEnablePlanRound = 1;
		} 
		else
		{
			pMonitorPlanCfgTemp->byEnablePlanRound = 0;
		}

		CString csListPlanID = m_lstVqdPlan.GetItemText(i,1);
		csListPlanID.Format("%s", csListPlanID);
		memcpy(pMonitorPlanCfgTemp->sPlanID, csListPlanID, PLAN_ID_LEN);

		for (int k = 0; k < 64; k++)
		{
			if (0 == strcmp((char*)m_struPlanVqdCfgTemp[i].sPlanID ,(char*)pMonitorPlanCfgTemp->sPlanID))
			{
				memcpy(pMonitorPlanCfgTemp->struDetectTime, m_struPlanVqdCfgTemp[i].struDetectTime, sizeof(NET_DVR_SCHEDTIME)*MAX_DAYS*MAX_TIMESEGMENT_V30);
				break;
			}
			
		}
		pMonitorPlanCfgTemp++;
	}
	DWORD *pStatus = new DWORD[iItemCount];
	memset(pStatus, 0, sizeof(DWORD)*iItemCount);
	//int iSize = iItemCount*(sizeof(NET_DVR_MONITOR_PLAN_CFG)) + g_iStreamIDNum * 32;
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_MONITOR_PLAN_VQDCFG, iItemCount, NULL, 0, pStatus, pMonitorPlanCfg, (iItemCount*(sizeof(NET_DVR_PLAN_VQD_CFG))));	
	if (bRet)
	{
		g_StringLanType(szLan,"设置监控点计划成功","Success");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Monitor Plan Success");
		AfxMessageBox(szLan);
	}
	else
	{        
		g_StringLanType(szLan,"设置监控点计划失败","Fail to set Monitor Plan");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to set Monitor Plan");
		AfxMessageBox(szLan);
	}
	
	for (i=0; i<iItemCount; i++)
	{
		CString strStatus;
		strStatus.Format("%d", *pStatus);
		m_lstVqdPlan.SetItemText(i, 13, strStatus);
		pStatus++;
	}
	
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnBtnGet()
{
	UpdateData(TRUE);
	m_bGetMonitorInfo = TRUE;
	char szLan[128] = {0};
	m_lstVqdPlan.DeleteAllItems();
	memset(&m_struPlanVqdCfgTemp, 0, 64*sizeof(NET_DVR_PLAN_VQD_CFG));
	//清除list控件上的信息
	m_iRowCount = 0;
	m_iStruCount = 0;
	if (m_lHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	} 
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_MONITOR_PLAN_VQD, NULL, 0, NULL, this);
		if (m_lHandle >= 0)
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetVqdPlanThread), this, 0, &dwThreadId);	
		} 
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}

	m_comboWeekday.SetCurSel(0);
}

void CDlgVqdPlan::GetMonitorIDInfo(LPNET_DVR_PLAN_VQD_CFG lpInter)
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_iMonitorStruCount = 0;
	if (m_lMonitorHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	} 
	else
	{
		m_lMonitorHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_MONITORID_VQD, lpInter, sizeof(NET_DVR_PLAN_VQD_CFG), NULL, this);
		if (m_lMonitorHandle >= 0)
		{
			m_bGetNext = TRUE;
			m_bGetMonitorNext = TRUE;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetMonitorInfoThread), this, 0, &dwThreadId);	
		} 
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}

void CDlgVqdPlan::OnCheckPtz() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetDlgItem(IDC_CHECK_SIGNAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_BLUR)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_FREEZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_LUMA)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_SNOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_STREAK)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_CHROMA)->EnableWindow(FALSE);

	if (m_bPtz == FALSE)
	{
		GetDlgItem(IDC_CHECK_SIGNAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_BLUR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_FREEZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_LUMA)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SNOW)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_STREAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_CHROMA)->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CDlgVqdPlan::ChangSelect()
{
	if (m_bStreak == TRUE || m_bSnow == TRUE || m_bSignal == TRUE || m_bLuma == TRUE ||
		m_bFreeze == TRUE || m_bChroma == TRUE || m_bBlur == TRUE)
	{
		GetDlgItem(IDC_CHECK_PTZ)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_PTZ)->EnableWindow(TRUE);
	}
}

void CDlgVqdPlan::OnCheckSignal() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	ChangSelect();
	UpdateData(FALSE);
}


void CDlgVqdPlan::OnCheckBlur() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ChangSelect();
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnCheckFreeze() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ChangSelect();
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnCheckLuma() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ChangSelect();
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnCheckSnow() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ChangSelect();
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnCheckStreak() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ChangSelect();
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnCheckChroma() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ChangSelect();
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnClickListVqdPlan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char szStr[128] = {0};
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	int m_iItem = pEditCtrl->iItem;
	int m_iSubItem = pEditCtrl->iSubItem;
	CString csListPlanID;

	if (m_bGetMonitorInfo)
	{
		m_struPlanVqdCfg.dwSize = sizeof(m_struPlanVqdCfg);
		csListPlanID = "";
		csListPlanID = m_lstVqdPlan.GetItemText(m_iItem,1);
		csListPlanID.Format("%s", csListPlanID);
		memcpy(m_struPlanVqdCfg.sPlanID, csListPlanID, PLAN_ID_LEN);
		//memcpy(m_struPlanVqdCfg.sPlanID, (LPCTSTR)m_lstVqdPlan.GetItemText(m_iItem, 1), PLAN_ID_LEN);
		m_lstMonitorInfo.DeleteAllItems();
		GetMonitorIDInfo(&m_struPlanVqdCfg);
	}

	m_struPlanVqdCfg.dwSize = sizeof(m_struPlanVqdCfg);
	csListPlanID = "";
	csListPlanID = m_lstVqdPlan.GetItemText(m_iItem,1);
	csListPlanID.Format("%s", csListPlanID);
	memcpy(m_struPlanVqdCfg.sPlanID, csListPlanID, PLAN_ID_LEN);	
	//memcpy(m_csListPlanID, csListPlanID, PLAN_ID_LEN);
	m_csListPlanID = csListPlanID;
	m_csPlanID = m_lstVqdPlan.GetItemText(m_iItem, 1);
	CString csText = m_lstVqdPlan.GetItemText(m_iItem, 2);

	if (0 != strcmp("周期计划", m_lstVqdPlan.GetItemText(m_iItem, 2)))
	{
		m_comboPlanMode.SetCurSel(0);
		GetDlgItem(IDC_CHK_CYCLE)->EnableWindow(FALSE);
	}
	else
	{
		m_comboPlanMode.SetCurSel(1);
		GetDlgItem(IDC_CHK_CYCLE)->EnableWindow(TRUE);
	}


	char* sCheck = "检测";
	char* sNoCheck = "不检测";
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 3)))
	{
		m_bSignal = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 4)))
	{
		m_bBlur = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 5)))
	{
		m_bLuma = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 6)))
	{
		m_bChroma = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 7)))
	{
		m_bSnow = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 8)))
	{
		m_bStreak = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 9)))
	{
		m_bFreeze = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 10)))
	{
		m_bPtz = TRUE;
	}
	if (0 == strcmp(sCheck, m_lstVqdPlan.GetItemText(m_iItem, 11)))
	{
		m_bCheckFlag = TRUE;
	}
	if (0 == strcmp("循环检测", m_lstVqdPlan.GetItemText(m_iItem, 12)))
	{
		m_bCycleCheck = TRUE;
	}

	for (int k = 0; k < 64; k++) 
	{
		if (0 == strcmp((char*)m_struPlanVqdCfgTemp[k].sPlanID ,m_csPlanID))
		{
			m_iHour11 = m_struPlanVqdCfgTemp[k].struDetectTime[0][0].byStartHour;
			m_iMin11 = m_struPlanVqdCfgTemp[k].struDetectTime[0][0].byStartMin;
			m_iHour12 = m_struPlanVqdCfgTemp[k].struDetectTime[0][0].byStopHour;
			m_iMin12 = m_struPlanVqdCfgTemp[k].struDetectTime[0][0].byStopMin;
			m_iHour21 = m_struPlanVqdCfgTemp[k].struDetectTime[0][1].byStartHour;
			m_iMin21 = m_struPlanVqdCfgTemp[k].struDetectTime[0][1].byStartMin;
			m_iHour22 = m_struPlanVqdCfgTemp[k].struDetectTime[0][1].byStopHour;
			m_iMin22 = m_struPlanVqdCfgTemp[k].struDetectTime[0][1].byStopMin;
			m_iHour31 = m_struPlanVqdCfgTemp[k].struDetectTime[0][2].byStartHour;
			m_iMin31 = m_struPlanVqdCfgTemp[k].struDetectTime[0][2].byStartMin;
			m_iHour32 = m_struPlanVqdCfgTemp[k].struDetectTime[0][2].byStopHour;
			m_iMin32 = m_struPlanVqdCfgTemp[k].struDetectTime[0][2].byStopMin;
			m_iHour41 = m_struPlanVqdCfgTemp[k].struDetectTime[0][3].byStartHour;
			m_iMin41 = m_struPlanVqdCfgTemp[k].struDetectTime[0][3].byStartMin;
			m_iHour42 = m_struPlanVqdCfgTemp[k].struDetectTime[0][3].byStopHour;
			m_iMin42 = m_struPlanVqdCfgTemp[k].struDetectTime[0][3].byStopMin;
			m_iHour51 = m_struPlanVqdCfgTemp[k].struDetectTime[0][4].byStartHour;
			m_iMin51 = m_struPlanVqdCfgTemp[k].struDetectTime[0][4].byStartMin;
			m_iHour52 = m_struPlanVqdCfgTemp[k].struDetectTime[0][4].byStopHour;
			m_iMin52 = m_struPlanVqdCfgTemp[k].struDetectTime[0][4].byStopMin;
			m_iHour61 = m_struPlanVqdCfgTemp[k].struDetectTime[0][5].byStartHour;
			m_iMin61 = m_struPlanVqdCfgTemp[k].struDetectTime[0][5].byStartMin;
			m_iHour62 = m_struPlanVqdCfgTemp[k].struDetectTime[0][5].byStopHour;
			m_iMin62 = m_struPlanVqdCfgTemp[k].struDetectTime[0][5].byStopMin;
			m_iHour71 = m_struPlanVqdCfgTemp[k].struDetectTime[0][6].byStartHour;
			m_iMin71 = m_struPlanVqdCfgTemp[k].struDetectTime[0][6].byStartMin;
			m_iHour72 = m_struPlanVqdCfgTemp[k].struDetectTime[0][6].byStopHour;
			m_iMin72 = m_struPlanVqdCfgTemp[k].struDetectTime[0][6].byStopMin;
			m_iHour81 = m_struPlanVqdCfgTemp[k].struDetectTime[0][7].byStartHour;
			m_iMin81 = m_struPlanVqdCfgTemp[k].struDetectTime[0][7].byStartMin;
			m_iHour82 = m_struPlanVqdCfgTemp[k].struDetectTime[0][7].byStopHour;
			m_iMin82 = m_struPlanVqdCfgTemp[k].struDetectTime[0][7].byStopMin;
		}		
	}
	
	ChangSelect();
	*pResult = 0;

	UpdateData(FALSE);
}

void CDlgVqdPlan::OnBtnMoitorDel()
{
	while(m_lstMonitorInfo.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_lstMonitorInfo.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstMonitorInfo.DeleteItem(nItem);
	}
}

void CDlgVqdPlan::OnBtnMoitorSet()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	LPNET_DVR_STREAM_INFO pStreamInfoCfg = NULL;
	LPNET_DVR_STREAM_INFO pStreamInfoCfgTemp = NULL;
	
	int iItemCount = m_lstMonitorInfo.GetItemCount();
	//int iItemCount = m_lstMonitorInfo.GetSelectedCount();
	if (iItemCount == 0)
	{
		AfxMessageBox("请添加计划信息!");
		return;
	}
	pStreamInfoCfg = new NET_DVR_STREAM_INFO[iItemCount];
	if (NULL == pStreamInfoCfg)
	{
		g_StringLanType(szLan,"申请内存失败","new memory failed");
		AfxMessageBox(szLan);
		return;
	}

	memset(pStreamInfoCfg, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
	pStreamInfoCfgTemp = pStreamInfoCfg;

	CString csListPlanID;
	int i = 0; 
	for (i=0; i<iItemCount; i++)
	{
		pStreamInfoCfgTemp->dwSize = sizeof(NET_DVR_STREAM_INFO);
		csListPlanID = "";
		csListPlanID = m_lstMonitorInfo.GetItemText(i,1);
		csListPlanID.Format("%s", csListPlanID);
		memcpy(pStreamInfoCfgTemp->byID, csListPlanID, STREAM_ID_LEN);

		pStreamInfoCfgTemp++;
	}

	DWORD *pStatus = new DWORD[iItemCount];
	memset(pStatus, 0, sizeof(DWORD)*iItemCount);

	if (m_struPlanVqdCfg.dwSize == 0)
	{
		AfxMessageBox("请点击选择配置的计划!");
		return;
	}

	BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_MONITOR_INFO, iItemCount, &m_struPlanVqdCfg, sizeof(m_struPlanVqdCfg), \
		pStatus, pStreamInfoCfg, (iItemCount*(sizeof(NET_DVR_STREAM_INFO))));	
	if (bRet)
	{
		g_StringLanType(szLan,"设置监控点信息成功","Success");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Monitor Plan Success");
		AfxMessageBox(szLan);
	}
	else
	{        
		g_StringLanType(szLan,"设置监控点信息失败","Fail to set Monitor Plan");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to set Monitor Plan");
		AfxMessageBox(szLan);
	}

	for (i=0; i<iItemCount; i++)
	{
		CString strStatus;
		strStatus.Format("%d", *pStatus);
		m_lstMonitorInfo.SetItemText(i, 2, strStatus);
		pStatus++;
	}
	
	UpdateData(FALSE);

}

void CDlgVqdPlan::OnBtnMoitorAdd()
{
	UpdateData(TRUE);
	char szStr[128] = {0};
	char szLan[128] = {0};
	int i = 0;

	if (m_csStreamID1.GetLength() > 32)
	{
		g_StringLanType(szLan, "参数长度错误", "Param Length Error");
		AfxMessageBox(szLan);
		return;
	}

	int iItemCount = m_lstMonitorInfo.GetItemCount();
	//修改诊断计划
	for (i = 0; i < iItemCount; i++)
	{
		if (0 == strcmp(m_lstMonitorInfo.GetItemText(i, 1), m_csStreamID1))
		{
			iItemCount = i;
			m_lstMonitorInfo.DeleteItem(i);
		}
	}

	sprintf(szStr, "%3d", iItemCount+1);
	m_lstMonitorInfo.InsertItem(iItemCount, szStr);

	m_lstMonitorInfo.SetItemText(iItemCount, 1, m_csStreamID1);
	m_bGetMonitorInfo = FALSE;
}


void CDlgVqdPlan::AddMonitorInfoToList(LPNET_DVR_STREAM_INFO lpInter)
{
	char szStr[128] = {0};
	
	int iItemCount = m_lstMonitorInfo.GetItemCount();
	sprintf(szStr, "%3d", iItemCount+1);
	m_lstMonitorInfo.InsertItem(iItemCount, szStr);

	memset(szStr, 0, sizeof(szStr));
	memcpy(szStr, lpInter->byID, STREAM_ID_LEN);
	m_lstMonitorInfo.SetItemText(iItemCount, 1, szStr);
}

void CDlgVqdPlan::AddVqdPlanInfoToDlg(LPNET_DVR_PLAN_VQD_CFG lpInter)
{
	char szStr[128] = {0};
	int iItemCount = m_lstVqdPlan.GetItemCount();
	sprintf(szStr, "%3d", iItemCount+1);
	m_lstVqdPlan.InsertItem(iItemCount, szStr);

	memcpy(&m_struPlanVqdCfgTemp[iItemCount].sPlanID, lpInter->sPlanID, PLAN_ID_LEN);
	memcpy(&m_struPlanVqdCfgTemp[iItemCount].struDetectTime, lpInter->struDetectTime, sizeof(NET_DVR_SCHEDTIME)*MAX_TIMESEGMENT_V30*MAX_DAYS);

	memset(szStr, 0, sizeof(szStr));
	memcpy(szStr, lpInter->sPlanID, PLAN_ID_LEN);
	m_lstVqdPlan.SetItemText(iItemCount, 1, szStr);
	
	char* sPlanMode1 = "即时计划";
	char* sPlanMode2 = "周期计划";
	if (TRUE == lpInter->byPlanMode)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 2, sPlanMode2);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 2, sPlanMode1);
	}

	char* sCheck = "检测";
	char* sNoCheck = "不检测";

	char* sCycleCheck = "循环检测";
	char* sNoCycleCheck = "不循环检测";
	
	if (TRUE == lpInter->bySignal)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 3, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 3, sNoCheck);
	}
	if (TRUE == lpInter->byBlur)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 4, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 4, sNoCheck);
	}
	if (TRUE == lpInter->byLuma)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 5, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 5, sNoCheck);
	}
	if (TRUE == lpInter->byChroma)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 6, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 6, sNoCheck);
	}
	if (TRUE == lpInter->bySnow)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 7, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 7, sNoCheck);
	}
	if (TRUE == lpInter->byStreak)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 8, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 8, sNoCheck);
	}
	if (TRUE == lpInter->byFreeze)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 9, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 9, sNoCheck);
	}
	if (TRUE == lpInter->byPTZ)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 10, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 10, sNoCheck);
	}
		
	if (TRUE == lpInter->byCheckFlag)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 11, sCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 11, sNoCheck);
	}
	
	if (TRUE == lpInter->byEnablePlanRound)
	{
		m_lstVqdPlan.SetItemText(iItemCount, 12, sCycleCheck);
	} 
	else
	{
		m_lstVqdPlan.SetItemText(iItemCount, 12, sNoCycleCheck);
	}

	m_lstVqdPlan.SetItemText(iItemCount, 13, "");
}

void CDlgVqdPlan::OnBtnDelPlan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	int i = 0;
	LPNET_DVR_PLAN_VQD_CFG pMonitorPlanCfg = NULL;
	LPNET_DVR_PLAN_VQD_CFG pMonitorPlanCfgTemp = NULL;

	
	int iIndex = 0;	
	int iItemCount = m_lstVqdPlan.GetSelectedCount();

	//int iItemCount = m_lstVqdPlan.GetItemCount();
	if (iItemCount == 0)
	{
		AfxMessageBox("请选择计划信息!");
		return;
	}
	pMonitorPlanCfg = new NET_DVR_PLAN_VQD_CFG[iItemCount];
	if (NULL == pMonitorPlanCfg)
	{
		g_StringLanType(szLan,"申请内存失败","new memory failed");
		AfxMessageBox(szLan);
		return;
	}
	memset(pMonitorPlanCfg, 0, iItemCount*sizeof(NET_DVR_PLAN_VQD_CFG));
	pMonitorPlanCfgTemp = pMonitorPlanCfg;

	POSITION pos = m_lstVqdPlan.GetFirstSelectedItemPosition();  //mod 增加多选功能支持列表多选删除
	if (pos == NULL)
	{
		return;
	}
	else
	{
		while (pos)
		{
			int nItem = m_lstVqdPlan.GetNextSelectedItem(pos);
			pMonitorPlanCfgTemp->dwSize = sizeof(NET_DVR_PLAN_VQD_CFG);

			CString csListPlanID = m_lstVqdPlan.GetItemText(nItem, 1);
			csListPlanID.Format("%s", csListPlanID);
			memcpy(pMonitorPlanCfgTemp->sPlanID, csListPlanID, PLAN_ID_LEN);
			pMonitorPlanCfgTemp++;

		}
	}

// 	for (int i=0; i<iItemCount; i++)
// 	{
// 		pMonitorPlanCfgTemp->dwSize = sizeof(NET_DVR_PLAN_VQD_CFG);		
// 		WORD wPeriod = atoi(m_lstVqdPlan.GetItemText(i, 2));
// 		pMonitorPlanCfgTemp->wPeriod = wPeriod;
// 
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 3)))
// 		{
// 			pMonitorPlanCfgTemp->bySignal = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->bySignal = 0;
// 		}
// 
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 4)))
// 		{
// 			pMonitorPlanCfgTemp->byBlur = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byBlur = 0;
// 		}
// 		
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 5)))
// 		{
// 			pMonitorPlanCfgTemp->byLuma = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byLuma = 0;
// 		}
// 
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 6)))
// 		{
// 			pMonitorPlanCfgTemp->byChroma = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byChroma = 0;
// 		}
// 
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 7)))
// 		{
// 			pMonitorPlanCfgTemp->bySnow = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->bySnow = 0;
// 		}
// 
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 8)))
// 		{
// 			pMonitorPlanCfgTemp->byStreak = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byStreak = 0;
// 		}
// 
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 9)))
// 		{
// 			pMonitorPlanCfgTemp->byFreeze = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byFreeze = 0;
// 		}
// 
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 10)))
// 		{
// 			pMonitorPlanCfgTemp->byPTZ = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byPTZ = 0;
// 		}
// 		
// 		if (0 == strcmp("检测", m_lstVqdPlan.GetItemText(i, 11)))
// 		{
// 			pMonitorPlanCfgTemp->byCheckFlag = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byCheckFlag = 0;
// 		}
// 
// 		if (0 == strcmp("循环检测", m_lstVqdPlan.GetItemText(i, 12)))
// 		{
// 			pMonitorPlanCfgTemp->byEnablePlanRound = 1;
// 		} 
// 		else
// 		{
// 			pMonitorPlanCfgTemp->byEnablePlanRound = 0;
// 		}
// 
// 		CString csListPlanID = m_lstVqdPlan.GetItemText(i,1);
// 		csListPlanID.Format("%s", csListPlanID);
// 		memcpy(pMonitorPlanCfgTemp->sPlanID, csListPlanID, PLAN_ID_LEN);
// 		pMonitorPlanCfgTemp++;
// 	}
	DWORD *pStatus = new DWORD[iItemCount];
	memset(pStatus, 0, sizeof(DWORD)*iItemCount);


	BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_DEL_MONITOR_PLAN_VQD, iItemCount, NULL, 0, pStatus, pMonitorPlanCfg, (iItemCount*(sizeof(NET_DVR_PLAN_VQD_CFG))) );	
	if (bRet)
	{
		g_StringLanType(szLan,"删除监控点计划成功","Success");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Monitor Plan Success");
		AfxMessageBox(szLan);
		m_lstVqdPlan.DeleteAllItems();
		m_lstMonitorInfo.DeleteAllItems();
		OnBtnGet();
	}
	else
	{        
		g_StringLanType(szLan,"删除监控点计划失败","Fail to set Monitor Plan");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to set Monitor Plan");
		AfxMessageBox(szLan);
	}
	
	for (i=0; i<iItemCount; i++)
	{
		CString strStatus;
		strStatus.Format("%d", *pStatus);
		m_lstVqdPlan.SetItemText(i, 17, strStatus);
		pStatus++;
	}
	
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnSelchangeComboAlarmOutWeekday() 
{
	// TODO: Add your control notification handler code here
	int i = m_comboWeekday.GetCurSel();
	for (int k = 0; k < 64; k++) 
	{
		if (0 == strcmp((char*)m_struPlanVqdCfgTemp[k].sPlanID ,m_csPlanID))
		{
			m_iHour11 = m_struPlanVqdCfgTemp[k].struDetectTime[i][0].byStartHour;
			m_iMin11 = m_struPlanVqdCfgTemp[k].struDetectTime[i][0].byStartMin;
			m_iHour12 = m_struPlanVqdCfgTemp[k].struDetectTime[i][0].byStopHour;
			m_iMin12 = m_struPlanVqdCfgTemp[k].struDetectTime[i][0].byStopMin;
			m_iHour21 = m_struPlanVqdCfgTemp[k].struDetectTime[i][1].byStartHour;
			m_iMin21 = m_struPlanVqdCfgTemp[k].struDetectTime[i][1].byStartMin;
			m_iHour22 = m_struPlanVqdCfgTemp[k].struDetectTime[i][1].byStopHour;
			m_iMin22 = m_struPlanVqdCfgTemp[k].struDetectTime[i][1].byStopMin;
			m_iHour31 = m_struPlanVqdCfgTemp[k].struDetectTime[i][2].byStartHour;
			m_iMin31 = m_struPlanVqdCfgTemp[k].struDetectTime[i][2].byStartMin;
			m_iHour32 = m_struPlanVqdCfgTemp[k].struDetectTime[i][2].byStopHour;
			m_iMin32 = m_struPlanVqdCfgTemp[k].struDetectTime[i][2].byStopMin;
			m_iHour41 = m_struPlanVqdCfgTemp[k].struDetectTime[i][3].byStartHour;
			m_iMin41 = m_struPlanVqdCfgTemp[k].struDetectTime[i][3].byStartMin;
			m_iHour42 = m_struPlanVqdCfgTemp[k].struDetectTime[i][3].byStopHour;
			m_iMin42 = m_struPlanVqdCfgTemp[k].struDetectTime[i][3].byStopMin;
			m_iHour51 = m_struPlanVqdCfgTemp[k].struDetectTime[i][4].byStartHour;
			m_iMin51 = m_struPlanVqdCfgTemp[k].struDetectTime[i][4].byStartMin;
			m_iHour52 = m_struPlanVqdCfgTemp[k].struDetectTime[i][4].byStopHour;
			m_iMin52 = m_struPlanVqdCfgTemp[k].struDetectTime[i][4].byStopMin;
			m_iHour61 = m_struPlanVqdCfgTemp[k].struDetectTime[i][5].byStartHour;
			m_iMin61 = m_struPlanVqdCfgTemp[k].struDetectTime[i][5].byStartMin;
			m_iHour62 = m_struPlanVqdCfgTemp[k].struDetectTime[i][5].byStopHour;
			m_iMin62 = m_struPlanVqdCfgTemp[k].struDetectTime[i][5].byStopMin;
			m_iHour71 = m_struPlanVqdCfgTemp[k].struDetectTime[i][6].byStartHour;
			m_iMin71 = m_struPlanVqdCfgTemp[k].struDetectTime[i][6].byStartMin;
			m_iHour72 = m_struPlanVqdCfgTemp[k].struDetectTime[i][6].byStopHour;
			m_iMin72 = m_struPlanVqdCfgTemp[k].struDetectTime[i][6].byStopMin;
			m_iHour81 = m_struPlanVqdCfgTemp[k].struDetectTime[i][7].byStartHour;
			m_iMin81 = m_struPlanVqdCfgTemp[k].struDetectTime[i][7].byStartMin;
			m_iHour82 = m_struPlanVqdCfgTemp[k].struDetectTime[i][7].byStopHour;
			m_iMin82 = m_struPlanVqdCfgTemp[k].struDetectTime[i][7].byStopMin;
		}		
	}

	UpdateData(FALSE);
}

void CDlgVqdPlan::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	int i = m_comboWeekday.GetCurSel();
	int iItemCount = 0;
	for (int k = 0; k < 64; k++)
	{
		if (0 == strcmp((char*)m_struPlanVqdCfgTemp[k].sPlanID, m_csPlanID))
		{
			iItemCount = k;
			break;
		}
	}
	if (m_iHour11 > 24 || m_iHour12 > 24 || m_iHour21 > 24 || m_iHour22 > 24 || m_iHour31 > 24 || m_iHour32 > 24 || m_iHour41 > 24 || m_iHour42 > 24 || \
		m_iHour51 > 24 || m_iHour52 > 24 || m_iHour61 > 24 || m_iHour62 > 24 || m_iHour71 > 24 || m_iHour72 > 24 || m_iHour81 > 24 || m_iHour82 > 24 || \
		m_iMin11 > 60 || m_iMin12 > 60 || m_iMin21 > 60 || m_iMin22 > 60 || m_iMin31 > 60 || m_iMin32 > 60 || m_iMin41 > 60 || m_iMin42 > 60 || \
		m_iMin51 > 60 || m_iMin52 > 60 || m_iMin61 > 60 || m_iMin62 > 60 || m_iMin71 > 60 || m_iMin72 > 60 || m_iMin81 > 60 || m_iMin82 > 60)
	{
		g_StringLanType(szLan, "非法的时间参数错误", "Illegal Time number");
		AfxMessageBox(szLan);
		return;
	}
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][0].byStartHour = (BYTE)m_iHour11;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][0].byStartMin = (BYTE)m_iMin11;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][0].byStopHour = (BYTE)m_iHour12;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][0].byStopMin = (BYTE)m_iMin12;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][1].byStartHour = (BYTE)m_iHour21;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][1].byStartMin = (BYTE)m_iMin21;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][1].byStopHour = (BYTE)m_iHour22;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][1].byStopMin = (BYTE)m_iMin22;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][2].byStartHour = (BYTE)m_iHour31;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][2].byStartMin = (BYTE)m_iMin31;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][2].byStopHour = (BYTE)m_iHour32;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][2].byStopMin = (BYTE)m_iMin32;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][3].byStartHour = (BYTE)m_iHour41;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][3].byStartMin = (BYTE)m_iMin41;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][3].byStopHour = (BYTE)m_iHour42;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][3].byStopMin = (BYTE)m_iMin42;	
	
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][4].byStartHour = (BYTE)m_iHour51;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][4].byStartMin = (BYTE)m_iMin51;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][4].byStopHour = (BYTE)m_iHour52;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][4].byStopMin = (BYTE)m_iMin52;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][5].byStartHour = (BYTE)m_iHour61;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][5].byStartMin = (BYTE)m_iMin61;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][5].byStopHour = (BYTE)m_iHour62;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][5].byStopMin = (BYTE)m_iMin62;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][6].byStartHour = (BYTE)m_iHour71;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][6].byStartMin = (BYTE)m_iMin71;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][6].byStopHour = (BYTE)m_iHour72;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][6].byStopMin = (BYTE)m_iMin72;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][7].byStartHour = (BYTE)m_iHour81;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][7].byStartMin = (BYTE)m_iMin81;
	m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][7].byStopHour = (BYTE)m_iHour82;
    m_struPlanVqdCfgTemp[iItemCount].struDetectTime[i][7].byStopMin = (BYTE)m_iMin82;
	
	UpdateData(FALSE);
}

void CDlgVqdPlan::OnSelchangeComboPlanmode() 
{
	// TODO: Add your control notification handler code here
	if (m_comboPlanMode.GetCurSel() == 0)
	{
		GetDlgItem(IDC_CHK_CYCLE)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(FALSE);

		GetDlgItem(IDC_BTN_SURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ALARM_OUT_WEEKDAY)->EnableWindow(FALSE);
	} 
	else
	{
		GetDlgItem(IDC_CHK_CYCLE)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_SURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_ALARM_OUT_WEEKDAY)->EnableWindow(TRUE);
	}
}
