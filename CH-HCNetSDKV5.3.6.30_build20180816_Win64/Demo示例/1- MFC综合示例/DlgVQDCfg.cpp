// DlgVQDCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVQDCfg.h"
#include ".\dlgremotehidealarm.h"


// CDlgRemoteHideAlarm dialog
extern LPNET_DVR_HIDEALARM_V30 g_lpHideAlarm;//view tamper area
extern LPNET_DVR_HIDEALARM_V40 g_lpHideAlarmV40;//view tamper area
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVQDCfg dialog


CDlgVQDCfg::CDlgVQDCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVQDCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVQDCfg)
	m_bChkAlarmOutMap = FALSE;
	m_bChkAudioAlarm = FALSE;
	m_bChkBlur = FALSE;
	m_bChkChroma = FALSE;
	m_bChkEnable = FALSE;
	m_bChkFreeze = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	m_bChkInvokeJPEGCapture = FALSE;
	m_bChkLuma = FALSE;
	m_bChkMonitorAlarm = FALSE;
	m_bChkPicFtp = FALSE;
	m_bChkPTZ = FALSE;
	m_bChkReportCenter = FALSE;
	m_bChkSiglose = FALSE;
	m_bChkSnow = FALSE;
	m_bChkStreak = FALSE;
	m_dwHour11 = 0;
	m_dwHour12 = 0;
	m_dwHour21 = 0;
	m_dwHour22 = 0;
	m_dwHour31 = 0;
	m_dwHour32 = 0;
	m_dwHour41 = 0;
	m_dwHour42 = 0;
	m_dwHour51 = 0;
	m_dwHour52 = 0;
	m_dwHour62 = 0;
	m_dwHour61 = 0;
	m_dwHour71 = 0;
	m_dwHour72 = 0;
	m_dwHour81 = 0;
	m_dwHour82 = 0;
	m_dwMin11 = 0;
	m_dwMin21 = 0;
	m_dwMin12 = 0;
	m_dwMin22 = 0;
	m_dwMin31 = 0;
	m_dwMin32 = 0;
	m_dwMin41 = 0;
	m_dwMin42 = 0;
	m_dwMin51 = 0;
	m_dwMin52 = 0;
	m_dwMin61 = 0;
	m_dwMin62 = 0;
	m_dwMin71 = 0;
	m_dwMin72 = 0;
	m_dwMin82 = 0;
	m_dwMin81 = 0;
	m_bDayCopy = FALSE;
	m_iAlarmOutNum = 0;
	m_iGetVQDInfoNum = 0;
	m_iRecordChanNum = 0;
	m_hVQDDiagnoseThread = NULL;
	m_bSetAllChannel = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgVQDCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVQDCfg)
	DDX_Control(pDX, IDC_TREE_RECORD_CHAN, m_treeRecordChan);
	DDX_Control(pDX, IDC_TREE_CHANNEL, m_treeChannel);
	DDX_Control(pDX, IDC_LIST_VQD_DIAGNOSE, m_listVQDDiagnose);
	DDX_Control(pDX, IDC_COMBO_GROUPNO, m_cmbGroupNo);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMOB_SNOW, m_cmbSnow);
	DDX_Control(pDX, IDC_COMOB_SIGLOSE, m_cmbSigLose);
	DDX_Control(pDX, IDC_COMOB_PTZ, m_cmbPTZ);
	DDX_Control(pDX, IDC_COMOB_LUMA, m_cmbLuma);
	DDX_Control(pDX, IDC_COMOB_FREEZE, m_cmbFreeze);
	DDX_Control(pDX, IDC_COMOB_CHROMA, m_cmbChroma);
	DDX_Control(pDX, IDC_COMOB_BLUR, m_cmbBlur);
	DDX_Control(pDX, IDC_COMBO_MOTION_WEEKDAY, m_cmbMotionWeek);
	DDX_Control(pDX, IDC_COMBO_MOTION_DAY_COPY, m_cmbMotionDayCopy);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMOB_STREAK, m_cmbStreak);
	DDX_Check(pDX, IDC_CHK_ALARMOUT_EMAP, m_bChkAlarmOutMap);
	DDX_Check(pDX, IDC_CHK_AUDIO_ALARM, m_bChkAudioAlarm);
	DDX_Check(pDX, IDC_CHK_BLUR, m_bChkBlur);
	DDX_Check(pDX, IDC_CHK_CHROMA, m_bChkChroma);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	DDX_Check(pDX, IDC_CHK_FREEZE, m_bChkFreeze);
	DDX_Check(pDX, IDC_CHK_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJPEGCapture);
	DDX_Check(pDX, IDC_CHK_LUMA, m_bChkLuma);
	DDX_Check(pDX, IDC_CHK_MONITOR_ALARM, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicFtp);
	DDX_Check(pDX, IDC_CHK_PTZ, m_bChkPTZ);
	DDX_Check(pDX, IDC_CHK_REPORT_CENTER, m_bChkReportCenter);
	DDX_Check(pDX, IDC_CHK_SIGLOSE, m_bChkSiglose);
	DDX_Check(pDX, IDC_CHK_SNOW, m_bChkSnow);
	DDX_Check(pDX, IDC_CHK_STREAK, m_bChkStreak);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_dwHour11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_dwHour12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_dwHour21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_dwHour22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_dwHour31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_dwHour32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_dwHour41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_dwHour42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_dwHour51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_dwHour52);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_dwHour62);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_dwHour61);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_dwHour71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_dwHour72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_dwHour81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_dwHour82);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_dwMin11);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_dwMin21);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_dwMin12);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_dwMin22);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_dwMin31);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_dwMin32);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_dwMin41);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_dwMin42);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_dwMin51);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_dwMin52);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_dwMin61);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_dwMin62);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_dwMin71);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_dwMin72);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_dwMin82);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_dwMin81);
	DDX_Check(pDX, IDC_CHECK_ALLCHANNEL, m_bSetAllChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVQDCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVQDCfg)
	ON_BN_CLICKED(IDC_BTN_GET_VQD_DIAGNOSE, OnBtnGetVQDDiagnose)
	ON_BN_CLICKED(IDC_BTN_VQD_LOOP_SET, OnBtnVQDLoopSet)
	ON_BN_CLICKED(IDC_BTN_VQD_LOOP_GET, OnBtnVQDLoopGet)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHK_INVOKE_ALARM_OUT, OnChkInvokeAlarmOut)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_BN_CLICKED(IDC_BTN_MOTION_DAY_COPY, OnBtnMotionDayCopy)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHANNEL, OnClickTreeChannel)
	ON_NOTIFY(NM_CLICK, IDC_TREE_RECORD_CHAN, OnClickTreeRecordChan)
	ON_CBN_SELCHANGE(IDC_COMBO_MOTION_WEEKDAY, OnSelchangeComboMotionWeekday)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_BN_CLICKED(IDC_BTN_USE_DEFAUT, OnBtnUseDefaut)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVQDCfg message handlers


/*********************************************************
Function:	GetVQDDiagnoseInfoThread
Desc:		 
Input:		 
Output:	
Return:	
**********************************************************/
UINT GetVQDDiagnoseInfoThread(LPVOID pParam)
{
	
	LONG lRet = -1;
	CString csTmp;
	char szLan[128] = {0};
	//void* pBuffer = NULL;
	DWORD dwOutBufferSize = 0 ;
	LONG lFindNext =  -1 ;
	NET_DVR_VQD_DIAGNOSE_INFO struVQDDiagnoseInfo = {0};
	CDlgVQDCfg * pVQDCfgDlg = (CDlgVQDCfg *)pParam;
	pVQDCfgDlg->m_lListNum = 0;
   // pVQDCfgDlg->UpdateData(TRUE);
	while (1)
	{
        lFindNext = NET_DVR_GetNextRemoteConfig(pVQDCfgDlg->m_lVQDDiagnoseHandle,&struVQDDiagnoseInfo, sizeof(struVQDDiagnoseInfo));
		
		if (NET_SDK_GET_NEXT_STATUS_SUCCESS == lFindNext)// 未完待续
		{
			//pVQDCfgDlg->GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态：接受中");
		//	NET_DVR_VQD_DIAGNOSE_INFO *struVQDDiagnoseInfoTemp = (NET_DVR_VQD_DIAGNOSE_INFO*)&struVQDDiagnoseInfo;
			
			pVQDCfgDlg->m_lListNum++;
			sprintf(szLan,"%d",pVQDCfgDlg->m_lListNum );
			pVQDCfgDlg->m_listVQDDiagnose.InsertItem(pVQDCfgDlg->m_lListNum,szLan);

			if (struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.dwChannelNO < g_struDeviceInfo[pVQDCfgDlg->m_iDevIndex].iAnalogChanNum +\
				g_struDeviceInfo[pVQDCfgDlg->m_iDevIndex].iStartChan)
			{
				sprintf(szLan,"Camera%d", struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.dwChannelNO);
			}
			else
			{
				sprintf(szLan,"IPCamera%02d", struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.dwChannelNO);
			}
			pVQDCfgDlg->m_listVQDDiagnose.SetItemText(pVQDCfgDlg->m_lListNum - 1,1,szLan);

			switch (struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.dwVQDType)
			{
			case VQD_BLUR_FLAG:
				g_StringLanType(szLan,"图像模糊","Blurred Image");
				break;
			case VQD_LUMA_FLAG:
				g_StringLanType(szLan,"亮度异常","Abnormal Brightness ");
				break;
			case VQD_CHROMA_FLAG:
				g_StringLanType(szLan,"图像偏色","Color Cast");
				break;
			case VQD_SNOW_FLAG:
				g_StringLanType(szLan,"雪花干扰","Snow Noise");
				break;
			case VQD_STREAK_FLAG:
				g_StringLanType(szLan,"条纹干扰","Stripe Noise");
				break;
			case VQD_FREEZE_FLAG:
				g_StringLanType(szLan,"画面冻结","Freeze Frame");
				break;
			case VQD_SIGLOSE_FLAG:
				g_StringLanType(szLan,"信号丢失","Video Lost");
				break;
			case VQD_PTZ_FLAG:
				g_StringLanType(szLan,"云台失控","PTZ Abnormal");
				break;
			case 0:
				g_StringLanType(szLan,"检测正常","Detect Normal");
				break;
			default:
				g_StringLanType(szLan,"未知异常", "Unknown exception");
				break;
			}
			pVQDCfgDlg->m_listVQDDiagnose.SetItemText(pVQDCfgDlg->m_lListNum - 1,2,szLan);

			sprintf(szLan,"%4d-%2d-%2d %2d:%2d:%2d", struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwYear,\
				struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwMonth,struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwDay,\
				struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwHour,struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwMinute,\
				struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwSecond);
			pVQDCfgDlg->m_listVQDDiagnose.SetItemText(pVQDCfgDlg->m_lListNum - 1,3,szLan);

			sprintf(szLan,"%d",struVQDDiagnoseInfo.struVQDDiagnoseExceptionInfo.byScoreValue);
			pVQDCfgDlg->m_listVQDDiagnose.SetItemText(pVQDCfgDlg->m_lListNum - 1,4,szLan);

			continue;
			pVQDCfgDlg->UpdateData(TRUE);
		}
		else if (NET_SDK_GET_NETX_STATUS_NEED_WAIT == lFindNext)	// 需等待
		{
			Sleep(5);
			continue;
		} 
		else if(NET_SDK_GET_NEXT_STATUS_FINISH == lFindNext)// 数据全部取完
		{
			//pVQDCfgDlg->GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态：结束");
			pVQDCfgDlg->m_lListNum = 0;
			break;
		}
		else// 出现异常
		{
		//	pVQDCfgDlg->GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态：异常");
			sprintf(szLan," 出现异常 %d",lFindNext);
			AfxMessageBox(szLan);
			pVQDCfgDlg->m_lListNum = 0;
			break;
		}
	}
	CloseHandle(pVQDCfgDlg->m_hVQDDiagnoseThread);
	pVQDCfgDlg->m_hVQDDiagnoseThread = NULL;
	NET_DVR_StopRemoteConfig(pVQDCfgDlg->m_lVQDDiagnoseHandle);
	
	//	pFindNasDirDlg->UpdateWindow();
	return 0;
	
}


void CDlgVQDCfg::OnBtnGetVQDDiagnose() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_listVQDDiagnose.DeleteAllItems();
	
	char szLan[1024] = {0};
	
// 	memset(m_dwGetVQDChannel,0, sizeof(m_dwGetVQDChannel));
// 	int  j = 0;
// 	for (int i = 0; i < MAX_CHANNUM_V30; i++)
// 	{
// 		if (m_bChannelChecked[i] == TRUE)
// 		{
// 			m_dwGetVQDChannel[j] = i;
// 			j++;
// 		}
// 	}

	m_lVQDDiagnoseHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_VQD_DIAGNOSE_INFO,m_dwGetVQDChannel,m_iGetVQDInfoNum*sizeof(DWORD),NULL,this) ;
	if (m_lVQDDiagnoseHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VQD_DIAGNOSE_INFO");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VQD_DIAGNOSE_INFO");
	
// 		m_iGetVQDInfoNum = 0;
// 		memset(m_dwGetVQDChannel,0, sizeof(m_dwGetVQDChannel));
		//获取查找状态
		DWORD dwState = 0;
		if (!NET_DVR_GetRemoteConfigState(m_lVQDDiagnoseHandle,&dwState))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_GET_VQD_DIAGNOSE_INFO ");
			//GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态： 获取失败");
			NET_DVR_StopRemoteConfig(m_lVQDDiagnoseHandle);
		}
		else   //开启获取进度线程
		{
			DWORD dwThreadId;
			if (m_hVQDDiagnoseThread == NULL)
			{
				m_hVQDDiagnoseThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetVQDDiagnoseInfoThread),this,0,&dwThreadId);		
			}
			if (m_hVQDDiagnoseThread == NULL)
			{
				g_StringLanType(szLan, "打开查找线程失败!", "Fail to open finding thread!");
				AfxMessageBox(szLan);
			}
		}
		
	}
}

void CDlgVQDCfg::OnBtnVQDLoopSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struVQDLoopDiagnoseCfg.dwSize = sizeof(m_struVQDLoopDiagnoseCfg);
	char szLan[128] = {0};
	char szLanCn[128] = {0};
	char szLanEn[128] = {0};
	if (!m_bDayCopy)
	{
		if (!CopyCurDayInfo())
		{
			return;
		}
		
	}

	m_struVQDLoopDiagnoseCfg.byEnable = m_bChkEnable;
	CopyVQDTypeAndSensor();
	GetHandleExceptinInfo();

	int i;
	int j = 0, k = 0;
	
	for (i=0; i< MAX_CHANNUM_V30; i++)
	{
		if (m_bAlarmOut[i] == 1)
		{
			m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut[j] = i + 1;
			j++;
		}

// 		if (m_bRecordChannel[i] == 1)
// 		{
// 			m_struVQDLoopDiagnoseCfg.dwRelRecordChan[k] = i + 1;
// 			k++;
// 		}
	}

	memset(&m_struChannelGroup, 0 ,sizeof(m_struChannelGroup));
	m_struChannelGroup.dwSize = sizeof(m_struChannelGroup);
	m_struChannelGroup.dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	m_struChannelGroup.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	DWORD dwList = 0;
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOutChanNum = j;
	if (m_bSetAllChannel)
	{
		for(i=0; i< (g_struDeviceInfo[m_iDevIndex].iDeviceChanNum - g_struDeviceInfo[m_iDevIndex].iIPChanNum) ; i++)   //设置所有的模拟通道
		{
			
			m_struChannelGroup.dwChannel =  g_struDeviceInfo[m_iDevIndex].iStartChan + i;
			
			if (!NET_DVR_SetDeviceConfig(m_lUserID,  NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG,NULL,&m_struChannelGroup,sizeof(m_struChannelGroup),\
				&dwList,&m_struVQDLoopDiagnoseCfg,sizeof(m_struVQDLoopDiagnoseCfg)))
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG,%d",m_struChannelGroup.dwChannel);
				sprintf(szLanCn,"循环诊断--模拟通道[%d]参数配置失败",m_struChannelGroup.dwChannel);
				sprintf(szLanEn,"Fail to Set VQD Loop Diagnose CFG with Camera[%d]!",m_struChannelGroup.dwChannel);
				g_StringLanType(szLan,szLanCn,szLanEn);
				AfxMessageBox(szLan);
			}
			else
			{
				if (dwList)
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VQD_LOOP_DIAGNOSE_CFG,%d",m_struChannelGroup.dwChannel);
					sprintf(szLanCn,"循环诊断--模拟通道[%d]参数配置失败",m_struChannelGroup.dwChannel);
					sprintf(szLanEn,"Fail to Set VQD Loop Diagnose CFG with Camera[%d]!",m_struChannelGroup.dwChannel);
					g_StringLanType(szLan,szLanCn,szLanEn);
					AfxMessageBox(szLan);
				}
			}
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG[%d]",m_struChannelGroup.dwChannel);
		}
		
		for(i=0; i<g_struDeviceInfo[m_iDevIndex].iIPChanNum; i++)   //设置所有的IP通道
		{
			if (g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].bEnable)
			{
				m_struChannelGroup.dwChannel =  	g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40[0].dwStartDChan + i ;
				
				if (!NET_DVR_SetDeviceConfig(m_lUserID,  NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG,NULL,&m_struChannelGroup,sizeof(m_struChannelGroup),\
					&dwList,&m_struVQDLoopDiagnoseCfg,sizeof(m_struVQDLoopDiagnoseCfg)))
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG,%d",m_struChannelGroup.dwChannel);
					sprintf(szLanCn,"循环诊断--数字通道[%d]参数配置失败",m_struChannelGroup.dwChannel);
					sprintf(szLanEn,"Fail to Set VQD Loop Diagnose CFG with IPCamera[%d]!",m_struChannelGroup.dwChannel);
					g_StringLanType(szLan,szLanCn,szLanEn);
					AfxMessageBox(szLan);
				}
				else
				{
					if (dwList)
					{
						g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG,%d",m_struChannelGroup.dwChannel);
						sprintf(szLanCn,"循环诊断--数字通道[%d]参数配置失败",m_struChannelGroup.dwChannel);
						sprintf(szLanEn,"Fail to Set VQD Loop Diagnose CFG with IPCamera[%d]!",m_struChannelGroup.dwChannel);
						g_StringLanType(szLan,szLanCn,szLanEn);
						AfxMessageBox(szLan);
					}
				}
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG");
			}

		}
	}
	else
	{	
		if (!NET_DVR_SetDeviceConfig(m_lUserID,  NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG,NULL,&m_struChannelGroup,sizeof(m_struChannelGroup),\
			&dwList,&m_struVQDLoopDiagnoseCfg,sizeof(m_struVQDLoopDiagnoseCfg)))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG [%d]",m_struChannelGroup.dwChannel);
			g_StringLanType(szLan,"循环诊断参数配置失败","Fail to Set VQD Loop Diagnose CFG!");
			AfxMessageBox(szLan);
			return;
		}
		else
		{
			if (dwList)
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VQD_LOOP_DIAGNOSE_CFG");
				g_StringLanType(szLan,"循环诊断参数配置失败","Fail to Set VQD Loop Diagnose CFG!");
				AfxMessageBox(szLan);
				return;
			}
		}
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VQD_LOOP_DIAGNOSE_CFG");
	}
//	memset(&m_struVQDLoopDiagnoseCfg,0, sizeof(m_struVQDLoopDiagnoseCfg));
//	m_iAlarmOutNum = 0;
//	m_iRecordChanNum = 0;

	g_StringLanType(szLan,"循环诊断配置完成","All Data Set Finished!");
	AfxMessageBox(szLan);


}

void CDlgVQDCfg::CopyVQDTypeAndSensor() 
{	
	UpdateData(TRUE);
	memset(m_struVQDLoopDiagnoseCfg.byVQDTypeEnable, 0, sizeof(m_struVQDLoopDiagnoseCfg.byVQDTypeEnable));
	if (m_bChkBlur)
	{	
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[0] = m_bChkBlur;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[0]   = m_cmbBlur.GetCurSel();
	}
	
	if (m_bChkLuma)
	{
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[1] = m_bChkLuma;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[1] = m_cmbLuma.GetCurSel();
	}
	
	if (m_bChkChroma)
	{
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[2] = m_bChkChroma;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[2]   = m_cmbChroma.GetCurSel();
	}
	
	
	if (m_bChkSnow)
	{
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[3] = m_bChkSnow;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[3] = m_cmbSnow.GetCurSel() ;
	}
	
	if (m_bChkStreak)
	{
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[4] = m_bChkStreak;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[4] = m_cmbStreak.GetCurSel();
	}
	
	if (m_bChkFreeze)
	{
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[5] = m_bChkFreeze;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[5] = m_cmbFreeze.GetCurSel();
	}
	
	if (m_bChkSiglose)
	{
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[6] = m_bChkSiglose;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[6] = m_cmbSigLose.GetCurSel();
	}
	
	if (m_bChkPTZ)
	{
		m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[7] = m_bChkPTZ;
		m_struVQDLoopDiagnoseCfg.byThresholdValue[7] = m_cmbPTZ.GetCurSel();
	}

}

void CDlgVQDCfg::OnBtnVQDLoopGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	memset(&m_struVQDLoopDiagnoseCfg,0,sizeof(m_struVQDLoopDiagnoseCfg));
	m_struVQDLoopDiagnoseCfg.dwSize = sizeof(m_struVQDLoopDiagnoseCfg);

	memset(&m_struChannelGroup, 0 ,sizeof(m_struChannelGroup));
	m_struChannelGroup.dwSize = sizeof(m_struChannelGroup);
	m_struChannelGroup.dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	m_struChannelGroup.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());

	DWORD dwList = 0;

	if (!NET_DVR_GetDeviceConfig(m_lUserID,  NET_DVR_GET_VQD_LOOP_DIAGNOSE_CFG,NULL,&m_struChannelGroup,sizeof(m_struChannelGroup),\
		&dwList,&m_struVQDLoopDiagnoseCfg,sizeof(m_struVQDLoopDiagnoseCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VQD_LOOP_DIAGNOSE_CFG");
		g_StringLanType(szLan,"循环诊断参数配置失败","Fail to Set VQD Loop Diagnose CFG!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		if (dwList)
		{
			char ErrorInfoEn[1024] = {0};
			char ErrorInfoCn[1024] = {0};
			sprintf(ErrorInfoEn,"Fail to Set VQD Loop Diagnose CFG!  Error[%d]",dwList);
			sprintf(ErrorInfoCn,"循环诊断参数配置失败!  Error[%d]",dwList);
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VQD_LOOP_DIAGNOSE_CFG Error[%d]",dwList);
			g_StringLanType(szLan,ErrorInfoCn,ErrorInfoEn);
			AfxMessageBox(szLan);
			return;
		}
	}
	g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VQD_LOOP_DIAGNOSE_CFG");

	//update Show Info
	if (m_struVQDLoopDiagnoseCfg.byEnable)
	{
		m_bChkEnable = TRUE;
	}
	else
	{
		m_bChkEnable = FALSE;
	}
	SetVQDTypeAndSensor();

	//show Triggered Alarm Channel Info
	SetTriggeredAlarmChannelShow(m_struChannelGroup.dwGroup);
//	SetTriggeredRecordChannelShow(m_struChannelGroup.dwGroup);
	m_cmbMotionWeek.SetCurSel(0);
	SetSchedTimeInfo(0);
	UpdateData(TRUE);
}

BOOL CDlgVQDCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	memset(&m_struVQDLoopDiagnoseCfg, 0, sizeof(m_struVQDLoopDiagnoseCfg));
	memset(&m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut, 0,sizeof(m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut));
//	memset(&m_struVQDLoopDiagnoseCfg.dwRelRecordChan, 0, sizeof(m_struVQDLoopDiagnoseCfg.dwRelRecordChan));
	AddChanInfo();

	AddThresholdInfo();

	CString csStr;
	
	m_cmbGroupNo.ResetContent();
	csStr.Format("%d",0);
	m_cmbGroupNo.AddString(csStr); 
	m_cmbGroupNo.SetCurSel(0);

	int i=0;
	for (i=0; i<MAX_ALARMOUT_V30; i++)
	{
		m_bAlarmOut[i] = FALSE; //g_lpHideAlarm->strHideAlarmHandleType.byRelAlarmOut[i];
		m_bRecordChannel[i] = FALSE;	
		m_bChannelChecked[i] = FALSE;
	}

// 	if (m_pRecvBuf == NULL)
// 	{
// 		m_pRecvBuf = new char[XML_BUF];
// 	}

	OnBtnVQDLoopGet();


	AddGroupInfo();

	AddVQDDiagnoseInfoToList();
	
	m_cmbMotionWeek.SetCurSel(0);
	m_cmbMotionDayCopy.SetCurSel(0);

	//	memset(m_dwGetVQDChannel,0, sizeof(m_dwGetVQDChannel));


	

// 	m_dwHour11 = g_lpHideAlarm->struAlarmTime[0][0]->byStartHour;
// 	m_dwMin11 = g_lpHideAlarm->struAlarmTime[0][0]->byStartMin;
// 	m_dwHour12 = g_lpHideAlarm->struAlarmTime[0][0]->byStopHour;
// 	m_dwMin12 = g_lpHideAlarm->struAlarmTime[0][0]->byStopMin;
// 	m_dwHour21 = g_lpHideAlarm->struAlarmTime[0][1]->byStartHour;
// 	m_dwMin21 = g_lpHideAlarm->struAlarmTime[0][1]->byStartMin;
// 	m_dwHour22 = g_lpHideAlarm->struAlarmTime[0][1]->byStopHour;
// 	m_dwMin22 = g_lpHideAlarm->struAlarmTime[0][1]->byStopMin;
// 	m_dwHour31 = g_lpHideAlarm->struAlarmTime[0][2]->byStartHour;
// 	m_dwMin31 = g_lpHideAlarm->struAlarmTime[0][2]->byStartMin;
// 	m_dwHour32 = g_lpHideAlarm->struAlarmTime[0][2]->byStopHour;
// 	m_dwMin32 = g_lpHideAlarm->struAlarmTime[0][2]->byStopMin;
// 	m_dwHour41 = g_lpHideAlarm->struAlarmTime[0][3]->byStartHour;
// 	m_dwMin41 = g_lpHideAlarm->struAlarmTime[0][3]->byStartMin;
// 	m_dwHour42 = g_lpHideAlarm->struAlarmTime[0][3]->byStopHour;
// 	m_dwMin42 = g_lpHideAlarm->struAlarmTime[0][3]->byStopMin;
// 	m_dwHour51 = g_lpHideAlarm->struAlarmTime[0][4]->byStartHour;
// 	m_dwMin51 = g_lpHideAlarm->struAlarmTime[0][4]->byStartMin;
// 	m_dwHour52 = g_lpHideAlarm->struAlarmTime[0][4]->byStopHour;
// 	m_dwMin52 = g_lpHideAlarm->struAlarmTime[0][4]->byStopMin;
// 	m_dwHour61 = g_lpHideAlarm->struAlarmTime[0][5]->byStartHour;
// 	m_dwMin61 = g_lpHideAlarm->struAlarmTime[0][5]->byStartMin;
// 	m_dwHour62 = g_lpHideAlarm->struAlarmTime[0][5]->byStopHour;
// 	m_dwMin62 = g_lpHideAlarm->struAlarmTime[0][5]->byStopMin;
// 	m_dwHour71 = g_lpHideAlarm->struAlarmTime[0][6]->byStartHour;
// 	m_dwMin71 = g_lpHideAlarm->struAlarmTime[0][6]->byStartMin;
// 	m_dwHour72 = g_lpHideAlarm->struAlarmTime[0][6]->byStopHour;
// 	m_dwMin72 = g_lpHideAlarm->struAlarmTime[0][6]->byStopMin;
// 	m_dwHour81 = g_lpHideAlarm->struAlarmTime[0][7]->byStartHour;
// 	m_dwMin81 = g_lpHideAlarm->struAlarmTime[0][7]->byStartMin;
// 	m_dwHour82 = g_lpHideAlarm->struAlarmTime[0][7]->byStopHour;
// 	m_dwMin82 = g_lpHideAlarm->struAlarmTime[0][7]->byStopMin;


	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVQDCfg::AddGroupInfo()
{
	CString csStr;

	m_cmbGroupNo.ResetContent();

	DWORD dwGroupNum = 0;
// 
// 	m_dwAllChanNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum + g_struDeviceInfo[m_iDevIndex].iIPChanNum;
// 
// 	for (int i = 0; i < m_dwAllChanNum /64 ;i++)
// 	{
// 		csStr.Format("%d", i);
// 		m_cmbGroupNo.AddString(csStr);
// 	}
	if (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOutChanNum % MAX_CHANNUM_V30)
	{
		dwGroupNum = m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOutChanNum / MAX_CHANNUM_V30 +1;
	}
	else
	{
		dwGroupNum = m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOutChanNum / MAX_CHANNUM_V30 ;
	}
	if (dwGroupNum == 0)
	{
		csStr.Format("%d", 0);
			m_cmbGroupNo.AddString(csStr);
	}
	else
	{
		for (int i =0; i < dwGroupNum; i++)
		{
			csStr.Format("%d", i);
			m_cmbGroupNo.AddString(csStr);
		}
	}

	m_cmbGroupNo.SetCurSel(0);
}

void CDlgVQDCfg::AddChanInfo()
{

	m_cmbChannel.ResetContent();
	char szLan[128] = {0};
	CString csStr;
	int iIndex = 0;
	int i;
	for(i=0; i< (g_struDeviceInfo[m_iDevIndex].iDeviceChanNum - g_struDeviceInfo[m_iDevIndex].iIPChanNum) ; i++)
	{
		csStr.Format("%s %d", "Camera", g_struDeviceInfo[m_iDevIndex].iStartChan + i);
		m_cmbChannel.AddString(csStr);
		m_cmbChannel.SetItemData(iIndex++, g_struDeviceInfo[m_iDevIndex].iStartChan + i);
	}
	
	for(i=0; i<g_struDeviceInfo[m_iDevIndex].iIPChanNum; i++)
	{
		if (g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].bEnable)
		{
			g_StringLanType(szLan, "IPCamera", "IPChannel");
			csStr.Format("%s %d", szLan, 1 + i);
			m_cmbChannel.AddString(csStr);
			m_cmbChannel.SetItemData(iIndex++, g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40[0].dwStartDChan + i);
		}
		
	}

	m_cmbChannel.SetCurSel(0);
}


/*********************************************************
Function:	CreateTree
Desc:		Create connection between alarm output-channel 
Input:	
Output:	
Return:	
**********************************************************/
void CDlgVQDCfg::CreateTree(void)
{
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex, m_bAlarmOut);
	g_CreateChannelTree(m_treeChannel,m_iDevIndex,m_bChannelChecked);
	g_CreateChannelTree(m_treeRecordChan, m_iDevIndex, m_bRecordChannel);

}

void CDlgVQDCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgVQDCfg::OnChkInvokeAlarmOut() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

void CDlgVQDCfg::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	m_bAlarmOut[dwIndex] = !bCheck;

	DWORD dwFindIndex = 0;
	//switch checkbox status on click
	if (m_iAlarmOutNum >= MAX_CHANNUM_V30)
	{
      g_StringLanType(szLan,"一组最多只能设置64个报警输出通道!"," group can only be set up to 64 alarm out channel");
	  AfxMessageBox(szLan);
	  return;
	}
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
		if (bCheck)
		{
			if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum)
			{
				dwFindIndex = dwIndex + 1;
			}
			else
			{
				dwFindIndex = dwIndex + g_struDeviceInfo->iStartChan;
			}
			int iIndex = FindFromArray(m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut, MAX_CHANNUM_V30, dwFindIndex);
			if (iIndex > -1)
			{
				DelFromArray(m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut, MAX_CHANNUM_V30, iIndex);
			}
			m_iAlarmOutNum--;
		}
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
		if (bCheck)
		{
			if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum)
			{
				dwFindIndex = dwIndex + 1;
			}
			else
			{
				dwFindIndex = dwIndex + g_struDeviceInfo->iStartChan;
			}
			int iIndex = FindFromArray(m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut, MAX_CHANNUM_V30, dwFindIndex);
			if (iIndex > -1)
			{
				DelFromArray(m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut, MAX_CHANNUM_V30, iIndex);
			}
			m_iAlarmOutNum--;
		}
	}

// 	if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum)
// 	{
//         m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut[m_iAlarmOutNum] = dwIndex +1;
// 	}
// 	else
// 	{
// 		m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut[m_iAlarmOutNum] = dwIndex + g_struDeviceInfo->iStartChan;
// 	}

	if (!bCheck)
	{
		m_iAlarmOutNum++;
	}

	*pResult = 0;

}

void CDlgVQDCfg::OnBtnMotionDayCopy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[256] = {0};
	if (!CopyCurDayInfo())
	{
		return;
	}
		
	m_bDayCopy = TRUE;
	int j,k;
	int i = m_cmbMotionWeek.GetCurSel();
	int m_nCopyTime = m_cmbMotionDayCopy.GetCurSel() - 1;
	
	if (m_nCopyTime == -1)
	{
		for (j=0; j<MAX_DAYS; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(m_struVQDLoopDiagnoseCfg.struAlarmTime[j][k]), &(m_struVQDLoopDiagnoseCfg.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
    else if (m_nCopyTime == 7)
    {
//         for (k = 0; k < MAX_TIMESEGMENT_V30; k++)
//         {
//             memcpy(&m_struVQDLoopDiagnoseCfg.struAlarmTime[k], &m_struVQDLoopDiagnoseCfg.struAlarmTime[i][k], sizeof(NET_DVR_SCHEDTIME));
//         }
			
    }
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_struVQDLoopDiagnoseCfg.struAlarmTime[m_nCopyTime][k]), &(m_struVQDLoopDiagnoseCfg.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}


/*********************************************************
Function:	TimeTest
Desc:		Time checking
Input:	
Output:	
Return:		TRUE,Correct time table;FALSE,incorrect time table;
**********************************************************/
BOOL CDlgVQDCfg::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_dwHour11 < 0) || (m_dwHour11 > 24) || (m_dwHour12 < 0) || (m_dwHour12 > 24) ||	\
		(m_dwHour21 < 0) || (m_dwHour21 > 24) || (m_dwHour22 < 0) || (m_dwHour22 > 24) ||	\
		(m_dwHour31 < 0) || (m_dwHour31 > 24) || (m_dwHour32 < 0) || (m_dwHour32 > 24) ||	\
		(m_dwHour41 < 0) || (m_dwHour41 > 24) || (m_dwHour42 < 0) || (m_dwHour42 > 24) ||   \
		(m_dwHour51 < 0) || (m_dwHour51 > 24) || (m_dwHour52 < 0) || (m_dwHour52 > 24) ||	\
		(m_dwHour61 < 0) || (m_dwHour61 > 24) || (m_dwHour62 < 0) || (m_dwHour62 > 24) ||	\
		(m_dwHour71 < 0) || (m_dwHour71 > 24) || (m_dwHour72 < 0) || (m_dwHour72 > 24) ||	\
		(m_dwHour81 < 0) || (m_dwHour81 > 24) || (m_dwHour82 < 0) || (m_dwHour82 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_dwMin11 < 0) || (m_dwMin11 > 60) || (m_dwMin12 < 0) || (m_dwMin12 > 60) ||	\
		(m_dwMin21 < 0) || (m_dwMin21 > 60) || (m_dwMin22 < 0) || (m_dwMin22 > 60) ||	\
		(m_dwMin31 < 0) || (m_dwMin31 > 60) || (m_dwMin32 < 0) || (m_dwMin32 > 60) ||	\
		(m_dwMin41 < 0) || (m_dwMin41 > 60) || (m_dwMin42 < 0) || (m_dwMin42 > 60) ||   \
		(m_dwMin51 < 0) || (m_dwMin51 > 60) || (m_dwMin52 < 0) || (m_dwMin52 > 60) ||	\
		(m_dwMin61 < 0) || (m_dwMin61 > 60) || (m_dwMin62 < 0) || (m_dwMin62 > 60) ||	\
		(m_dwMin71 < 0) || (m_dwMin71 > 60) || (m_dwMin72 < 0) || (m_dwMin72 > 60) ||	\
		(m_dwMin81 < 0) || (m_dwMin81 > 60) || (m_dwMin82 < 0) || (m_dwMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_dwHour11 * 100 + m_dwMin11);
	wStartTime[1] = (WORD)(m_dwHour21 * 100 + m_dwMin21);
	wStartTime[2] = (WORD)(m_dwHour31 * 100 + m_dwMin31);
	wStartTime[3] = (WORD)(m_dwHour41 * 100 + m_dwMin41);
	wStopTime[0] = (WORD)(m_dwHour12 * 100 + m_dwMin12);
	wStopTime[1] = (WORD)(m_dwHour22 * 100 + m_dwMin22);
	wStopTime[2] = (WORD)(m_dwHour32 * 100 + m_dwMin32);
	wStopTime[3] = (WORD)(m_dwHour42 * 100 + m_dwMin42);
	wStartTime[4] = (WORD)(m_dwHour51 * 100 + m_dwMin51);
	wStartTime[5] = (WORD)(m_dwHour61 * 100 + m_dwMin61);
	wStartTime[6] = (WORD)(m_dwHour71 * 100 + m_dwMin71);
	wStartTime[7] = (WORD)(m_dwHour81 * 100 + m_dwMin81);
	wStopTime[4] = (WORD)(m_dwHour52 * 100 + m_dwMin52);
	wStopTime[5] = (WORD)(m_dwHour62 * 100 + m_dwMin62);
	wStopTime[6] = (WORD)(m_dwHour72 * 100 + m_dwMin72);
	wStopTime[7] = (WORD)(m_dwHour82 * 100 + m_dwMin82);
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
			{
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}

/*********************************************************
Function:	CopyCurDayInfo
Desc:		copy  Data Info
Input:	
Output:	
Return:		TRUE,Correct time table;FALSE,incorrect time table;
**********************************************************/
BOOL CDlgVQDCfg::CopyCurDayInfo()
{

	UpdateData(TRUE);
	char szLan[256] = {0};
	if (!TimeTest())
	{
		g_StringLanType(szLan,"请输入正确的时间信息！","Please enter the correct time information!");
		AfxMessageBox(szLan);
		return FALSE;
	}
    int i = m_cmbMotionWeek.GetCurSel();

	if (i < 0 || i>7)
	{
		i = 0;
	}
    if (7 == i)
    {
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStartHour = (BYTE)m_dwHour11;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStartMin = (BYTE)m_dwMin11;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStopHour = (BYTE)m_dwHour12;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStopMin = (BYTE)m_dwMin12;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStartHour = (BYTE)m_dwHour21;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStartMin = (BYTE)m_dwMin21;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStopHour = (BYTE)m_dwHour22;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStopMin = (BYTE)m_dwMin22;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStartHour = (BYTE)m_dwHour31;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStartMin = (BYTE)m_dwMin31;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStopHour = (BYTE)m_dwHour32;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStopMin = (BYTE)m_dwMin32;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStartHour = (BYTE)m_dwHour41;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStartMin = (BYTE)m_dwMin41;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStopHour = (BYTE)m_dwHour42;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStopMin = (BYTE)m_dwMin42;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStartHour = (BYTE)m_dwHour51;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStartMin = (BYTE)m_dwMin51;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStopHour = (BYTE)m_dwHour52;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStopMin = (BYTE)m_dwMin52;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStartHour = (BYTE)m_dwHour61;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStartMin = (BYTE)m_dwMin61;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStopHour = (BYTE)m_dwHour62;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStopMin = (BYTE)m_dwMin62;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStartHour = (BYTE)m_dwHour71;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStartMin = (BYTE)m_dwMin71;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStopHour = (BYTE)m_dwHour72;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStopMin = (BYTE)m_dwMin72;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStartHour = (BYTE)m_dwHour81;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStartMin = (BYTE)m_dwMin81;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStopHour = (BYTE)m_dwHour82;
        m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStopMin = (BYTE)m_dwMin82;
//         if (!SetHideHolidayHandle(m_struVQDLoopDiagnoseCfg))
//         {
//             AfxMessageBox("Fail to set holiday handle");
//         }
    }
    else
    {
        m_struVQDLoopDiagnoseCfg.struAlarmTime[i][0].byStartHour = (BYTE)m_dwHour11;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][0].byStartMin = (BYTE)m_dwMin11;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][0].byStopHour = (BYTE)m_dwHour12;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][0].byStopMin = (BYTE)m_dwMin12;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][1].byStartHour = (BYTE)m_dwHour21;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][1].byStartMin = (BYTE)m_dwMin21;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][1].byStopHour = (BYTE)m_dwHour22;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][1].byStopMin = (BYTE)m_dwMin22;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][2].byStartHour = (BYTE)m_dwHour31;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][2].byStartMin = (BYTE)m_dwMin31;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][2].byStopHour = (BYTE)m_dwHour32;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][2].byStopMin = (BYTE)m_dwMin32;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][3].byStartHour = (BYTE)m_dwHour41;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][3].byStartMin = (BYTE)m_dwMin41;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][3].byStopHour = (BYTE)m_dwHour42;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][3].byStopMin = (BYTE)m_dwMin42;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][4].byStartHour = (BYTE)m_dwHour51;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][4].byStartMin = (BYTE)m_dwMin51;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][4].byStopHour = (BYTE)m_dwHour52;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][4].byStopMin = (BYTE)m_dwMin52;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][5].byStartHour = (BYTE)m_dwHour61;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][5].byStartMin = (BYTE)m_dwMin61;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][5].byStopHour = (BYTE)m_dwHour62;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][5].byStopMin = (BYTE)m_dwMin62;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][6].byStartHour = (BYTE)m_dwHour71;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][6].byStartMin = (BYTE)m_dwMin71;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][6].byStopHour = (BYTE)m_dwHour72;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][6].byStopMin = (BYTE)m_dwMin72;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][7].byStartHour = (BYTE)m_dwHour81;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][7].byStartMin = (BYTE)m_dwMin81;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][7].byStopHour = (BYTE)m_dwHour82;
		m_struVQDLoopDiagnoseCfg.struAlarmTime[i][7].byStopMin = (BYTE)m_dwMin82;
    }
	GetDlgItem(IDC_BTN_MOTION_DAY_COPY)->EnableWindow(TRUE);
	
	return TRUE;
}

/*********************************************************
Function:	GetHandleExceptinInfo
Desc:		copy  Handle Exceptions Info
Input:	
Output:	
Return:		NULL
**********************************************************/
void CDlgVQDCfg::GetHandleExceptinInfo()
{
	UpdateData(TRUE);
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType = 0;
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType |= (m_bChkInvokeJPEGCapture << 4);
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType |= (m_bChkAlarmOutMap<<6);
	m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);
}

/*********************************************************
Function:	SetVQDTypeAndSensor
Desc:		Set  Handle Exceptions Info
Input:	
Output:	
Return:		NULL
**********************************************************/
void CDlgVQDCfg::SetVQDTypeAndSensor()
{

	m_bChkBlur = FALSE;	
	m_bChkLuma = FALSE;
	m_bChkChroma = FALSE;
	m_bChkSnow = FALSE;	
	m_bChkStreak = FALSE;
	m_bChkFreeze = FALSE;
	m_bChkSiglose = FALSE;
	m_bChkPTZ = FALSE;	



	m_cmbBlur.SetCurSel(-1);
	m_cmbLuma.SetCurSel(-1);
	m_cmbChroma.SetCurSel(-1);
	m_cmbSnow.SetCurSel(-1);
	m_cmbStreak.SetCurSel(-1);
	m_cmbFreeze.SetCurSel(-1);
	m_cmbSigLose.SetCurSel(-1);
	m_cmbPTZ.SetCurSel(-1);

	CString strTemp;

	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[0])
	{
		m_bChkBlur = TRUE;
		m_cmbBlur.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[0]);
	}

	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[1])
	{
		m_bChkLuma = TRUE;
		m_cmbLuma.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[1]);
	}	

	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[2])
	{
		m_bChkChroma = TRUE;
		m_cmbChroma.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[2]);
	}

	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[3])
	{
		m_bChkSnow = TRUE;
		m_cmbSnow.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[3]);
	}

	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[4])
	{
		m_bChkStreak = TRUE;
		m_cmbStreak.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[4]);
	}


	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[5])
	{
		m_bChkFreeze = TRUE;
		m_cmbFreeze.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[5]);
	}
	

	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[6])
	{
		m_bChkSiglose = TRUE;
		m_cmbSigLose.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[6]);
	}	

	if (m_struVQDLoopDiagnoseCfg.byVQDTypeEnable[7])
	{
		m_bChkPTZ = TRUE;
		m_cmbPTZ.SetCurSel(m_struVQDLoopDiagnoseCfg.byThresholdValue[7] );
	}

	UpdateData(FALSE);
}

/*********************************************************
Function:	SetSchedTimeInfo
Desc:		Set  Handle Exceptions Info
Input:	
Output:	
Return:		NULL
**********************************************************/
void CDlgVQDCfg::SetSchedTimeInfo(int iIndex)
{
    UpdateData(TRUE);
	char szLan[128] = {0};
	if (iIndex < 0 || iIndex >7)
	{
		g_StringLanType(szLan,"请先选择时间","Please Select Time First!");
		AfxMessageBox(szLan);
		return;
	}

	if (iIndex < 7)
	{
		m_dwHour11 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][0].byStartHour;
		m_dwMin11  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][0].byStartMin;
		m_dwHour12 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][0].byStopHour;
		m_dwMin12  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][0].byStopMin;
		m_dwHour21 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][1].byStartHour;
		m_dwMin21  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][1].byStartMin;
		m_dwHour22 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][1].byStopHour;
		m_dwMin22  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][1].byStopMin;
		m_dwHour31 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][2].byStartHour;
		m_dwMin31  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][2].byStartMin;
		m_dwHour32 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][2].byStopHour;
		m_dwMin32  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][2].byStopMin;
		m_dwHour41 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][3].byStartHour;
		m_dwMin41  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][3].byStartMin;
		m_dwHour42 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][3].byStopHour;
		m_dwMin42  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][3].byStopMin;
		m_dwHour51 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][4].byStartHour;
		m_dwMin51  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][4].byStartMin;
		m_dwHour52 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][4].byStopHour;
		m_dwMin52  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][4].byStopMin;
		m_dwHour61 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][5].byStartHour;
		m_dwMin61  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][5].byStartMin;
		m_dwHour62 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][5].byStopHour;
		m_dwMin62  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][5].byStopMin;
		m_dwHour71 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][6].byStartHour;
		m_dwMin71  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][6].byStartMin;
		m_dwHour72 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][6].byStopHour;
		m_dwMin72  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][6].byStopMin;
		m_dwHour81 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][7].byStartHour;
		m_dwMin81  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][7].byStartMin;
		m_dwHour82 = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][7].byStopHour;
		m_dwMin82  = m_struVQDLoopDiagnoseCfg.struAlarmTime[iIndex][7].byStopMin;
	}
	else
	{
		m_dwHour11 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStartHour;
		m_dwMin11  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStartMin;
		m_dwHour12 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStopHour;
		m_dwMin12  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[0].byStopMin;
		m_dwHour21 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStartHour;
		m_dwMin21  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStartMin;
		m_dwHour22 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStopHour;
		m_dwMin22  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[1].byStopMin;
		m_dwHour31 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStartHour;
		m_dwMin31  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStartMin;
		m_dwHour32 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStopHour;
		m_dwMin32  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[2].byStopMin;
		m_dwHour41 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStartHour;
		m_dwMin41  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStartMin;
		m_dwHour42 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStopHour;
		m_dwMin42  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[3].byStopMin;
		m_dwHour51 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStartHour;
		m_dwMin51  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStartMin;
		m_dwHour52 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStopHour;
		m_dwMin52  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[4].byStopMin;
		m_dwHour61 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStartHour;
		m_dwMin61  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStartMin;
		m_dwHour62 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStopHour;
		m_dwMin62  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[5].byStopMin;
		m_dwHour71 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStartHour;
		m_dwMin71  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStartMin;
		m_dwHour72 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStopHour;
		m_dwMin72  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[6].byStopMin;
		m_dwHour81 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStartHour;
		m_dwMin81  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStartMin;
		m_dwHour82 = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStopHour;
		m_dwMin82  = m_struVQDLoopDiagnoseCfg.struHolidayAlarmTime[7].byStopMin;
	}


	UpdateData(FALSE);
}

/*********************************************************
Function:	SetTriggeredAlarmChannelShow
Desc:		Set Alarm Channel Show
Input:	
Output:	
Return:		NULL
**********************************************************/
void CDlgVQDCfg::SetTriggeredAlarmChannelShow(DWORD dwGroup)
{
	UpdateData(TRUE);


	
	memset(m_bAlarmOut, 0, MAX_CHANNUM_V30);
	int j =0;
	m_iAlarmOutNum = 0;
	for (int i = 0 ; i < MAX_CHANNUM_V30; i++ )
	{
		if (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut[i] != 0xffffffff)
		{
			m_bAlarmOut[m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwRelAlarmOut[i] - 1] = true;
			m_bChkInvokeAlarmOut = TRUE;
			m_iAlarmOutNum++;
			OnChkInvokeAlarmOut();
		//	j++;
		}
	}

	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex, m_bAlarmOut);
	
	
	//set Alarm Handle Type

 
	m_bChkMonitorAlarm = (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType & 0x1);
	m_bChkAudioAlarm = (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType>>1) & 0x1 ;
	m_bChkReportCenter = (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType>>2 )& 0x1;
	m_bChkInvokeAlarmOut = (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType>>3 )& 0x1;
	m_bChkInvokeJPEGCapture = (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType>>4  )& 0x1;
	m_bChkAlarmOutMap = (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType>>6 ) & 0x1;
	m_bChkPicFtp = (m_struVQDLoopDiagnoseCfg.struAlarmHandleType.dwHandleType >>9) & 0x1;

	UpdateData(FALSE);
}

/*********************************************************
Function:	SetTriggeredAlarmChannelShow
Desc:		Set Alarm Channel Show
Input:	
Output:	
Return:		NULL
**********************************************************/
void CDlgVQDCfg::SetTriggeredRecordChannelShow(DWORD dwGroup)
{
	UpdateData(TRUE);
/*	
	memset(m_bRecordChannel, 0, MAX_CHANNUM_V30);
	m_iRecordChanNum = 0;
	int j =0;
	for (int i = 0 ; i < MAX_CHANNUM_V30; i++ )
	{
		if (m_struVQDLoopDiagnoseCfg.dwRelRecordChan[i] != 0xffffffff)
		{
			m_bRecordChannel[m_struVQDLoopDiagnoseCfg.dwRelRecordChan[i] - 1] = true;
			m_iRecordChanNum++;
		//	j++;
		}
	}

	//g_CreateAlarmOutTree(m_treeRecordChan, m_iDevIndex, m_bRecordChannel);

	g_CreateChannelTree(m_treeRecordChan, m_iDevIndex, m_bRecordChannel);
*/
//	UpdateData(FALSE);
}

/*********************************************************
Function:	AddVQDDiagnoseInfoToList
Desc:		Add VQD Diagnose Info To List
Input:	
Output:	
Return:		NULL
**********************************************************/
void CDlgVQDCfg::AddVQDDiagnoseInfoToList()
{

	int nIndex = 0;
    char szLan[128] = {0};
	
	m_listVQDDiagnose.SetExtendedStyle(m_listVQDDiagnose.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listVQDDiagnose.InsertColumn(nIndex, szLan,LVCFMT_LEFT,40,-1);
    nIndex++;
	
	g_StringLanType(szLan, "通道号", "Channel No.");
	m_listVQDDiagnose.InsertColumn(nIndex, szLan,LVCFMT_LEFT,120,-1);
	nIndex++;
	g_StringLanType(szLan, "诊断类型", "VQD Type");
	m_listVQDDiagnose.InsertColumn(nIndex, szLan,LVCFMT_LEFT,100,-1);
	nIndex++;
	g_StringLanType(szLan, "诊断时间", "Diagnose time");
	m_listVQDDiagnose.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 120, -1);
	nIndex++;
	g_StringLanType(szLan, "得分", "Score Value");
	m_listVQDDiagnose.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 60, -1);
}

void CDlgVQDCfg::OnClickTreeChannel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_CHANNEL)->GetWindowRect(&rc);
  	ScreenToClient(&rc);
 	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeChannel.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeChannel.SelectItem(hSelect);
	DWORD dwIndex = m_treeChannel.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeChannel.GetCheck(hSelect);
	m_bChannelChecked[dwIndex] = !bCheck;
	DWORD dwFindIndex = 0;

	
	//switch checkbox status on click
	if (dwIndex >= MAX_CHANNUM_V30)
	{
		g_StringLanType(szLan,"超过设备支持的最大通道数!"," The max number of channels over device supports");
		AfxMessageBox(szLan);
		return;
	}
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeChannel.SetCheck(hSelect, !bCheck);
		if (bCheck)
		{
			if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum)
			{
				dwFindIndex = dwIndex + 1;
			}
			else
			{
				dwFindIndex = dwIndex + g_struDeviceInfo->iStartChan;
			}
			int iIndex = FindFromArray(m_dwGetVQDChannel, MAX_CHANNUM_V30, dwFindIndex);
			if (iIndex > -1)
			{
				DelFromArray(m_dwGetVQDChannel, MAX_CHANNUM_V30, iIndex);
			}
			m_iGetVQDInfoNum--;
		}
	}
	else
	{
		m_treeChannel.SetCheck(hSelect, bCheck);
		if (bCheck)
		{
			if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum)
			{
				dwFindIndex = dwIndex + 1;
			}
			else
			{
				dwFindIndex = dwIndex + g_struDeviceInfo->iStartChan;
			}
			int iIndex = FindFromArray(m_dwGetVQDChannel, MAX_CHANNUM_V30, dwFindIndex);
			if (iIndex > -1)
			{
				DelFromArray(m_dwGetVQDChannel, MAX_CHANNUM_V30, iIndex);
			}
			m_iGetVQDInfoNum--;
		}
	}
	
	if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum)
	{
        m_dwGetVQDChannel[m_iGetVQDInfoNum] = dwIndex + 1;
	}
	else
	{
		m_dwGetVQDChannel[m_iGetVQDInfoNum] = dwIndex + g_struDeviceInfo->iStartChan;
	}
	if (!bCheck)
	{
		m_iGetVQDInfoNum++;
	}



	*pResult = 0;
}

BOOL CDlgVQDCfg::DelFromArray(DWORD *dwArray, int iMaxArrayIndex, int iCurIndex)
{
	// TODO: Add your control notification handler code here
	if (dwArray == NULL)
	{
		return FALSE;
	}
 
	DWORD *pArrayTemp = (DWORD *)dwArray;
	int i;
	for (i = 0; i < iMaxArrayIndex -1; i++)
	{
        if (iCurIndex <= i)
        {
			*(pArrayTemp + i) = *(pArrayTemp + i+1);
        }
	}
    *(pArrayTemp + iMaxArrayIndex -1) = 0 ;
	return TRUE;	
}
int  CDlgVQDCfg::FindFromArray(DWORD *dwArray, int iMaxArrayIndex, DWORD dwFindValue)
{
    if (dwArray == NULL)
    {
		return -1;
    }

	for (int i = 0; i < iMaxArrayIndex ; i++)
	{
		if (dwFindValue == *(dwArray +i))
		{
			return i;
		}
	}

	return -1;
}

void CDlgVQDCfg::OnClickTreeRecordChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
/*
	UpdateData(TRUE);
	char szLan[128] = {0};
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_RECORD_CHAN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeRecordChan.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeRecordChan.SelectItem(hSelect);
	DWORD dwIndex = m_treeRecordChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeRecordChan.GetCheck(hSelect);
	m_bRecordChannel[dwIndex] = !bCheck;
	
	DWORD dwFindIndex = 0;
	//switch checkbox status on click
	if (m_iRecordChanNum >= MAX_CHANNUM_V30)
	{
		g_StringLanType(szLan,"一组最多只能设置64个触发录像通道!"," group can only be set up to 64 alarm out channel");
		AfxMessageBox(szLan);
		return;
	}

	if (uFlag != LVHT_TOLEFT)
	{
		m_treeRecordChan.SetCheck(hSelect, !bCheck);
		if (bCheck)
		{
			if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum)
			{
				dwFindIndex = dwIndex + 1;
			}
			else
			{
				dwFindIndex = dwIndex + g_struDeviceInfo->iStartChan;
			}
			int iIndex = FindFromArray(m_struVQDLoopDiagnoseCfg.dwRelRecordChan, MAX_CHANNUM_V30, dwFindIndex);
			if (iIndex > -1)
			{
				DelFromArray(m_struVQDLoopDiagnoseCfg.dwRelRecordChan, MAX_CHANNUM_V30, iIndex);
			}
			m_iRecordChanNum--;
		}
	}
	else
	{
		m_treeRecordChan.SetCheck(hSelect, bCheck);
		if (bCheck)
		{
			if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum)
			{
				dwFindIndex = dwIndex + 1;
			}
			else
			{
				dwFindIndex = dwIndex + g_struDeviceInfo->iStartChan;
			}
			int iIndex = FindFromArray(m_struVQDLoopDiagnoseCfg.dwRelRecordChan, MAX_CHANNUM_V30, dwFindIndex);
			if (iIndex > -1)
			{
				DelFromArray(m_struVQDLoopDiagnoseCfg.dwRelRecordChan, MAX_CHANNUM_V30, iIndex);
			}
			m_iRecordChanNum--;
		}
	}
	
	if (dwIndex < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum)
	{
       // m_struVQDLoopDiagnoseCfg.dwRelRecordChan[m_iRecordChanNum] = dwIndex  + 1;
	}
	else
	{
		//m_struVQDLoopDiagnoseCfg.dwRelRecordChan[m_iRecordChanNum] = dwIndex + g_struDeviceInfo->iStartChan;
	}
	if (!bCheck)
	{
		m_iRecordChanNum++;
	}
*/
	*pResult = 0;
}


void CDlgVQDCfg::OnSelchangeComboMotionWeekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_cmbMotionWeek.GetCurSel() == 7)
	{
		GetDlgItem(IDC_BTN_MOTION_DAY_COPY)->EnableWindow(FALSE);

	}
	else
	{
		GetDlgItem(IDC_BTN_MOTION_DAY_COPY)->EnableWindow(TRUE);
	
	}
	SetSchedTimeInfo(m_cmbMotionWeek.GetCurSel());
	
}

void CDlgVQDCfg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	char szLan[128] = {0};
// 	if (m_cmbMotionWeek.GetCurSel() < 0 || m_cmbMotionWeek.GetCurSel() >7)
// 	{
// 		g_StringLanType(szLan,"请选择一个合理的日期！","Please Select Day!");
// 		AfxMessageBox(szLan);
// 		return
// 	}
// 	else if (m_cmbMotionWeek.GetCurSel() < 7)
// 	{
// 		
// 	}
// 	else
// 	{
// 
// 	}
CopyCurDayInfo();	

}


void CDlgVQDCfg::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnVQDLoopGet();
}

void CDlgVQDCfg::OnBtnUseDefaut() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_bChkBlur)
	{
		m_cmbBlur.SetCurSel(60);
	}
	if (m_bChkLuma)
	{
		m_cmbLuma.SetCurSel(75);
	}
	if (m_bChkChroma)
	{
		m_cmbChroma.SetCurSel(64);
	}
	if (m_bChkSnow)
	{
		m_cmbSnow.SetCurSel(60);
	}
	if (m_bChkStreak)
	{
		m_cmbStreak.SetCurSel(25);
	}
	if (m_bChkFreeze)
	{
		m_cmbFreeze.SetCurSel(90);
	}
	if (m_bChkSiglose)
	{
		m_cmbSigLose.SetCurSel(-1);
	}
	if (m_bChkPTZ)
	{
		m_cmbPTZ.SetCurSel(-1);
	}





	UpdateData(FALSE);
}

void CDlgVQDCfg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
// 	if (m_pRecvBuf != NULL)
// 	{
// 		delete m_pRecvBuf;
// 		m_pRecvBuf = NULL;
// 	}
}

void CDlgVQDCfg::AddThresholdInfo()
{
	UpdateData(TRUE);
	char szSendBuf[256] = {0};

	char szLan[128] = {0};
// 	sprintf(szSendBuf,"<VQDAbility version='2.0'><channelNO>%d</channelNO></VQDAbility>",m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel()));
// 	if (!NET_DVR_GetDeviceAbility(m_lUserID, DEVICE_ABILITY_INFO, szSendBuf, strlen(szSendBuf), m_pRecvBuf, XML_BUF))
// 	{
// 		g_StringLanType(szLan,"获取VQD能力集失败！","Get VQD Ability  Failed");
// 		AfxMessageBox(szLan);
// 		return;
// 	}
// 	
	m_cmbSnow.ResetContent();
	m_cmbSigLose.ResetContent();
	m_cmbPTZ.ResetContent();
	m_cmbLuma.ResetContent();
	m_cmbFreeze.ResetContent();
	m_cmbChroma.ResetContent();
	m_cmbBlur.ResetContent();
	m_cmbStreak.ResetContent();

	CString csStr;
	int iIndex = 0;
	int i;
	for(i=0; i<= 100 ; i++)
	{
		csStr.Format("%d", i);
		m_cmbSnow.AddString(csStr);
		m_cmbSigLose.AddString(csStr);
		m_cmbPTZ.AddString(csStr);
		m_cmbLuma.AddString(csStr);
		m_cmbFreeze.AddString(csStr);
		m_cmbChroma.AddString(csStr);
		m_cmbStreak.AddString(csStr);
		m_cmbBlur.AddString(csStr);
		m_cmbSnow.SetItemData(iIndex++, i);
	}
}


BOOL CDlgVQDCfg::ParseNetworkAbility(char *pBuf, DWORD dwBufSize)
{

	WirteBufToFile(pBuf, dwBufSize);
	
    CMarkup	XmlMaker;
    XmlMaker.SetDoc(pBuf);
    
    ParseVQDSettingXml(XmlMaker);   
    return TRUE;
	

}
BOOL CDlgVQDCfg::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\%sVQD.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        int nError = 0;
        nError = GetLastError();
        return FALSE;
    }
    DWORD dwReturn = 0;
    WriteFile(hFile, pBuf, dwBufSize, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    
    return TRUE;
}

BOOL CDlgVQDCfg::ParseVQDSettingXml(CMarkup &struMarkup)
{
	if (struMarkup.FindElem("DiagnoseType"))
    {
        struMarkup.IntoElem();
		
        ParseThresholdXml(struMarkup);
		
        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find NetworkSetting Fail");
        return FALSE;
    }
    return TRUE;

}

BOOL CDlgVQDCfg::ParseThresholdXml(CMarkup &struMarkup)
{
	if (struMarkup.FindElem("Range"))
	{
		CString str;
		str = struMarkup.GetData();
		
//		ParseStrIndex(str, m_struNetworkAbility.struWireless.byNetworkMode, sizeof(m_struNetworkAbility.struWireless.byNetworkMode));
	}


		return TRUE;
}