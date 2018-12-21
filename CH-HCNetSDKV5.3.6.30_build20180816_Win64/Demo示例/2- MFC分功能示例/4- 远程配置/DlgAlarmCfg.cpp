// DlgAlarmCfg.cpp : implementation file
//
/**********************************************************
FileName:    DlgAlarmCfg.cpp
Description: 报警信息配置      
Date:        
Note: 		<全局>结构体,宏见GeneralDef.h, 全局变量,函数见config.cpp   
Modification History:      
<version>   <time>         <desc>

***********************************************************/

#include "stdafx.h"
#include "config.h"
#include "DlgAlarmCfg.h"
#include "DlgRemoteAlarmInHandle.h"
#include "DlgRemoteAlarmInPtzInvoke.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCfg dialog


CDlgAlarmCfg::CDlgAlarmCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmCfg::IDD, pParent)
	, m_csAlarmInName(_T(""))
	, m_bChkAlarmInHandle(FALSE)
	, m_iHour11(0)
	, m_iMin11(0)
	, m_iHour12(0)
	, m_iMin12(0)
	, m_iHour21(0)
	, m_iMin21(0)
	, m_iHour22(0)
	, m_iMin22(0)
	, m_iHour31(0)
	, m_iMin31(0)
	, m_iHour32(0)
	, m_iMin32(0)
	, m_iHour41(0)
	, m_iMin41(0)
	, m_iHour42(0)
	, m_iMin42(0)
	, m_iHour51(0)
	, m_iMin51(0)
	, m_iHour52(0)
	, m_iMin52(0)
	, m_iHour61(0)
	, m_iMin61(0)
	, m_iHour62(0)
	, m_iMin62(0)
	, m_iHour71(0)
	, m_iMin71(0)
	, m_iHour72(0)
	, m_iMin72(0)
	, m_iHour81(0)
	, m_iMin81(0)
	, m_iHour82(0)
	, m_iMin82(0)
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_dwAlarmInNum(0)
	, m_dwAlarmOutNum(0)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_iAlarmInIndex(-1)
	, m_iCopyAlarmIn(0)
	, m_iCopyAlarmOut(-1)
	, m_nCopyOutTime(0)
	, m_iAlarmOutIndex(-1)
	, m_csAlarmInIP(_T(""))
	, m_csAlarmOutIP(_T(""))
	, m_csAlarmInChan(_T("0"))
	, m_csAlarmOutChan(_T("0"))
	, m_iState(0)
{
}


void CDlgAlarmCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmCfg)
	DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
	DDX_Control(pDX, IDC_COMBO_ALARM_IN_TYPE, m_comboAlarmInType);
	DDX_Text(pDX, IDC_EDIT_ALARM_IN_NAME, m_csAlarmInName);
	DDX_Check(pDX, IDC_CHK_ALARM_IN_HANDLE, m_bChkAlarmInHandle);
	DDX_Control(pDX, IDC_COMBO_COPY_ALARM_IN, m_comboCopyAlarmIn);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT, m_comboAlarmOut);
	DDX_Control(pDX, IDC_COMBO_OUT_DELAY, m_comboAlarmOutDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT_COPY_DAY, m_comboCopyDay);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
	DDX_Control(pDX, IDC_COMBO_COPY_ALARM_OUT, m_comboCopyAlarmOut);
	DDX_Text(pDX, IDC_EDIT_ALARMIN_IP, m_csAlarmInIP);
	DDX_Text(pDX, IDC_EDIT_ALARMIN_CHAN, m_csAlarmInChan);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_CHAN, m_csAlarmOutChan);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_IP, m_csAlarmOutIP);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_NAME, m_csAlarmOutName);
	DDX_Text(pDX, IDC_EDIT_STATE, m_iState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_IN, OnCbnSelchangeComboAlarmIn)
	ON_BN_CLICKED(IDC_CHK_ALARM_IN_HANDLE, OnBnClickedChkAlarmInHandle)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_DAY_OK, OnBnClickedBtnAlarmOutDayOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_OUT_WEEKDAY, OnCbnSelchangeComboAlarmOutWeekday)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_OUT, OnCbnSelchangeComboAlarmOut)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_DAY_COPY, OnBnClickedBtnAlarmOutDayCopy)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_COPY, OnBnClickedBtnAlarmOutCopy)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_OK, OnBnClickedBtnAlarmInOk)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_OK, OnBnClickedBtnAlarmOutOk)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_HANDLE, OnBnClickedBtnAlarmInHandle)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_PTZ, OnBnClickedBtnAlarmInPtz)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_COPY, OnBnClickedBtnAlarmInCopy)
	ON_BN_CLICKED(IDC_BTN_SET_STATE, OnBtnSetState)
	ON_BN_CLICKED(IDC_BUTTON_ALARMCFGSETUP, OnBnClickedBtnAlarmCfgSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCfg message handlers

/*********************************************************
Function:	CheckInitParam
Desc:		检验设备的参数,并初始化对话框的相关参数
Input:	
Output:	
Return:		TRUE,设备参数相同,或正确,初始化对话框参数;FALSE,不初始化
**********************************************************/
BOOL CDlgAlarmCfg::CheckInitParam()
{
	CString sTemp;
	int i = 0;
	DWORD dwReturned = 0;
	int iAlarmInSel = 0;
	int iAlarmOutSel = 0;
	char szLan[128] = {0};
	int iDeviceIndex = 0;
	memset(&m_struIPAlarmInCfg, 0, sizeof(NET_DVR_IPALARMINCFG));
	memset(&m_struIPAlarmOutCfg, 0, sizeof(NET_DVR_IPALARMOUTCFG));
	if (iDeviceIndex == -1)
	{
		return FALSE;
	}

	m_iDeviceIndex = iDeviceIndex;
	m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
	m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	m_dwAlarmInNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum;
	m_dwAlarmOutNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum;

	m_csAlarmInName = _T("");
	m_bChkAlarmInHandle = FALSE;
	m_iHour11 = 0;
	m_iMin11 = 0;
	m_iHour12 = 0;
	m_iMin12 = 0;
	m_iHour21 = 0;
	m_iMin21 = 0;
	m_iHour22 = 0;
	m_iMin22 = 0;
	m_iHour31 = 0;
	m_iMin31 = 0;
	m_iHour32 = 0;
	m_iMin32 = 0;
	m_iHour41 = 0;
	m_iMin41 = 0;
	m_iHour42 = 0;
	m_iMin42 = 0;
	m_iHour51 = 0;
	m_iMin51 = 0;
	m_iHour52 = 0;
	m_iMin52 = 0;
	m_iHour61 = 0;
	m_iMin61 = 0;
	m_iHour62 = 0;
	m_iMin62 = 0;
	m_iHour71 = 0;
	m_iMin71 = 0;
	m_iHour72 = 0;
	m_iMin72 = 0;
	m_iHour81 = 0;
	m_iMin81 = 0;
	m_iHour82 = 0;
	m_iMin82 = 0;

	m_iAlarmInIndex = 0;
	m_iCopyAlarmIn = -1;
	m_iAlarmOutIndex = 0;
	m_iCopyAlarmOut = -1;
	m_nCopyOutTime = -1;
	m_comboWeekday.SetCurSel(-1);
	m_comboCopyDay.SetCurSel(-1);
	m_comboAlarmInType.SetCurSel(-1);
	m_comboAlarmOutDelay.SetCurSel(-1);
	m_comboAlarmIn.ResetContent();
	m_comboCopyAlarmIn.ResetContent();
	m_comboAlarmOut.ResetContent();
	m_comboCopyAlarmOut.ResetContent();

	if (m_lLoginID < 0)
	{
		return FALSE;
	}

	sTemp.Format(_T("All AlarmIn"));
	m_comboCopyAlarmIn.AddString(sTemp);
	m_comboCopyAlarmIn.SetItemData(0, -1);
	if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS90XX_HF_S)
	{
		if (DoGetIPAlarmInCfg(m_iDeviceIndex))
		{
			memcpy(&m_struIPAlarmInCfg, &g_struDeviceInfo[m_iDeviceIndex].struAlarmInCfg, sizeof(NET_DVR_IPALARMINCFG));
		}

		if (DoGetIPAlarmOutCfg(m_iDeviceIndex))
		{
			memcpy(&m_struIPAlarmOutCfg, &g_struDeviceInfo[m_iDeviceIndex].struAlarmOutCfg, sizeof(NET_DVR_IPALARMOUTCFG));
		}
	}

	for (i=0; i<MAX_ALARMIN_V30; i++)//m_dwAlarmInNum
	{	
		m_bGetAlarmIn[i] = FALSE;
		m_bSetAlarmIn[i] = FALSE;

		if (i<(int)m_dwAlarmInNum || (i>=MAX_ANALOG_ALARMIN && m_struIPAlarmInCfg.struIPAlarmInInfo[i-MAX_ANALOG_ALARMIN].byIPID > 0))
		{
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_ALARMINCFG_V30, i, &m_struAlarmInCfg[i], sizeof(NET_DVR_ALARMINCFG_V30), &dwReturned))
			{
				m_bGetAlarmIn[i] = FALSE;
				g_StringLanType(szLan, "获取报警输入参数失败", "Alarm input parameters to get the failure");
				AfxMessageBox(szLan);
				return FALSE;
			}
			if (i<(int)m_dwAlarmInNum)
			{			
				sTemp.Format(ALARM_IN_NAME, (1+i));
			}
			else
			{
				sTemp.Format(IP_ALARM_IN_NAME, (1+i-MAX_ANALOG_ALARMIN));
			}	

			m_bGetAlarmIn[i] = TRUE;
			m_comboAlarmIn.AddString(sTemp);
			m_comboAlarmIn.SetItemData(iAlarmInSel, i);
			
			m_comboCopyAlarmIn.AddString(sTemp);
			m_comboCopyAlarmIn.SetItemData(iAlarmInSel+1, i);
			iAlarmInSel++;
		}
	}
	m_comboCopyAlarmIn.SetCurSel(0);		
	m_comboAlarmIn.SetCurSel(0);
	m_iAlarmInIndex = m_comboAlarmIn.GetItemData(0);
	m_iCopyAlarmIn = m_comboAlarmIn.GetItemData(0);

	sTemp.Format(_T("All AlarmOut"));
	m_comboCopyAlarmOut.AddString(sTemp);
	m_comboCopyAlarmOut.SetItemData(0, -1);
	for (i=0; i<MAX_ALARMOUT_V30; i++)//m_dwAlarmOutNum for test
	{	
		m_bGetAlarmOut[i] = FALSE;
		m_bSetAlarmOut[i] = FALSE;

		if (i<(int)m_dwAlarmOutNum || (i>=MAX_ANALOG_ALARMOUT && m_struIPAlarmOutCfg.struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].byIPID > 0))
		{
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_ALARMOUTCFG_V30, i, &m_struAlarmOutCfg[i], sizeof(NET_DVR_ALARMOUTCFG_V30), &dwReturned))
			{
				m_bGetAlarmOut[i] = FALSE;
				g_StringLanType(szLan, "获取报警输出参数失败", "Alarm output parameters to get the failure");
				AfxMessageBox(szLan);
				return FALSE;
			}
			if (i<(int)m_dwAlarmOutNum)
			{			
				sTemp.Format(ALARM_OUT_FORMAT, 1 + i);
			}
			else if (i>=MAX_ANALOG_ALARMOUT)
			{
				sTemp.Format(IP_ALARM_OUT_NAME, 1 + i - MAX_ANALOG_ALARMOUT);
			}

			m_bGetAlarmOut[i] = TRUE;
			m_comboAlarmOut.AddString(sTemp);	
			m_comboAlarmOut.SetItemData(iAlarmOutSel, i);
			
			m_comboCopyAlarmOut.AddString(sTemp);
			m_comboCopyAlarmOut.SetItemData(iAlarmOutSel+1, i);
			iAlarmOutSel++;
		}
	}
	m_comboCopyAlarmOut.SetCurSel(0);		
	m_comboAlarmOut.SetCurSel(0);
	m_iAlarmOutIndex = m_comboAlarmOut.GetItemData(0);
	OnCbnSelchangeComboAlarmIn();
	OnCbnSelchangeComboAlarmOut();
	return TRUE;
}

/*********************************************************
  Function:	CurCfgUpdate
  Desc:		更新对应设备的参数,并刷新对应的控件
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		UpdateData(FALSE);
		EnableWindow(FALSE);
		return;
	}
	EnableWindow(TRUE);

	char cTemp[100];

	if (m_bGetAlarmIn[m_iAlarmInIndex])
	{
		m_comboAlarmInType.SetCurSel(m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType);
		m_bChkAlarmInHandle = m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle;
		ZeroMemory(cTemp, 100);
		memcpy(cTemp, m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, NAME_LEN);
		m_csAlarmInName.Format("%s", cTemp);
		if (m_bChkAlarmInHandle)
		{
			GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_BTN_ALARM_IN_COPY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ALARM_IN_OK)->EnableWindow(TRUE);
	}

	if (m_bGetAlarmOut[m_iAlarmOutIndex])
	{
		ZeroMemory(cTemp, 100);
		memcpy(cTemp, m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, NAME_LEN);
		m_comboAlarmOutDelay.SetCurSel(m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay);
		m_csAlarmOutName.Format("%s", cTemp);
		m_comboWeekday.SetCurSel(0);
		m_comboCopyDay.SetCurSel(0);
		m_iHour11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartHour;
		m_iMin11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartMin;
		m_iHour12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopHour;
		m_iMin12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopMin;
		m_iHour21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartHour;
		m_iMin21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartMin;
		m_iHour22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopHour;
		m_iMin22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopMin;
		m_iHour31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartHour;
		m_iMin31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartMin;
		m_iHour32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopHour;
		m_iMin32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopMin;
		m_iHour41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartHour;
		m_iMin41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartMin;
		m_iHour42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopHour;
		m_iMin42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopMin;
		m_iHour51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartHour;
		m_iMin51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartMin;
		m_iHour52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopHour;
		m_iMin52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopMin;
		m_iHour61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartHour;
		m_iMin61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartMin;
		m_iHour62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopHour;
		m_iMin62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopMin;
		m_iHour71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartHour;
		m_iMin71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartMin;
		m_iHour72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopHour;
		m_iMin72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopMin;
		m_iHour81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartHour;
		m_iMin81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartMin;
		m_iHour82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopHour;
		m_iMin82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopMin;
		GetDlgItem(IDC_BTN_ALARM_OUT_OK)->EnableWindow(TRUE); 
		GetDlgItem(IDC_BTN_ALARM_OUT_DAY_OK)->EnableWindow(TRUE); 
		GetDlgItem(IDC_BTN_ALARM_OUT_DAY_COPY)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);	
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarmIn
  Desc:		更新选中告警输入量对应的参数
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnCbnSelchangeComboAlarmIn()
{
	char szLan[128] = {0};
	char cTemp[100] = {0};
	DWORD dwID = 0;
	m_iAlarmInIndex = m_comboAlarmIn.GetItemData(m_comboAlarmIn.GetCurSel());
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, NAME_LEN);
	m_csAlarmInName.Format("%s", cTemp);
	m_comboAlarmInType.SetCurSel(m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType);
	m_bChkAlarmInHandle = m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle;
	if (m_iAlarmInIndex >= 0 && m_iAlarmInIndex < MAX_ANALOG_ALARMIN)
	{
		g_StringLanType(szLan, "本地", "Local");
		m_csAlarmInIP.Format(szLan);
		m_csAlarmInChan.Format("0");
	}
	else if (m_iAlarmInIndex >= MAX_ANALOG_ALARMIN && m_iAlarmInIndex < MAX_ALARMOUT_V30)
	{
		dwID = g_struDeviceInfo[m_iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo[m_iAlarmInIndex-MAX_ANALOG_ALARMIN].byIPID;
		if (dwID <= 0)
		{
			g_StringLanType(szLan, "不在线", "Offline");
			m_csAlarmInIP.Format(szLan);
			m_csAlarmInChan.Format("0");
		}
		else
		{
			m_csAlarmInIP.Format("%s", g_struDeviceInfo[m_iDeviceIndex].struIPParaCfg.struIPDevInfo[dwID-1].struIP.sIpV4);
			m_csAlarmInChan.Format("%d", m_struIPAlarmInCfg.struIPAlarmInInfo[m_iAlarmInIndex-MAX_ANALOG_ALARMIN].byAlarmIn);
		}
		
	}
	else
	{
		//g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Err m_iAlarmInIndex %d", m_iAlarmInIndex);
	}
	
	if (m_bChkAlarmInHandle)
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInHandle
  Desc:		对告警输入的处理的配置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmInHandle()
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	CDlgRemoteAlarmInHandle dlg;
	dlg.m_lpAlarmIn = &m_struAlarmInCfg[m_iAlarmInIndex];
	dlg.m_iChanCount = m_iChanCount;
	dlg.m_dwDevIndex = m_iDeviceIndex;
	dlg.m_lStartChannel = m_lStartChannel;
	dlg.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlg.m_dwAlarmInNum = m_dwAlarmInNum;
	if (dlg.DoModal()==IDOK)
	{
		m_bSetAlarmIn[m_iAlarmInIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInPtz
  Desc:		告警输入云台控制联动
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmInPtz()
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	CDlgRemoteAlarmInPtzInvoke dlg;
	dlg.m_lpAlarmIn = &m_struAlarmInCfg[m_iAlarmInIndex];
	dlg.m_iChanCount = m_iChanCount;
	dlg.m_lStartChannel = m_lStartChannel;
	if (dlg.DoModal()==IDOK)
	{
		m_bSetAlarmIn[m_iAlarmInIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInCopy
  Desc:		复制当前告警输入通道的配置到对应通道
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmInCopy()
{
	UpdateData(TRUE);
	int i;
	m_iCopyAlarmIn = m_comboCopyAlarmIn.GetItemData(m_comboCopyAlarmIn.GetCurSel());
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle = m_bChkAlarmInHandle;
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType = m_comboAlarmInType.GetCurSel();
	memcpy(m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, m_csAlarmInName, NAME_LEN);

	if (m_iCopyAlarmIn == -1)
	{
		for (i=0; i<MAX_ALARMIN_V30; i++)
		{
			if ( i<MAX_ANALOG_ALARMIN && i>=(int)m_dwAlarmInNum )
			{
				continue;
			}
			if ( i>=MAX_ANALOG_ALARMIN )
			{//不存在的数字报警通道
				if (g_struDeviceInfo[m_iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo[i-MAX_ANALOG_ALARMIN].byIPID == 0)
				{
					continue;
				}
			}
			if (m_iAlarmInIndex == i)
			{
				continue;	
			}
			memcpy(&(m_struAlarmInCfg[i]), &(m_struAlarmInCfg[m_iAlarmInIndex]), sizeof(NET_DVR_ALARMINCFG_V30));
			m_bSetAlarmIn[i] = TRUE;
		}
	}
	else
	{	
		memcpy(&(m_struAlarmInCfg[m_iCopyAlarmIn]), &(m_struAlarmInCfg[m_iAlarmInIndex]), sizeof(NET_DVR_ALARMINCFG_V30));
		m_bSetAlarmIn[m_iCopyAlarmIn] = TRUE;
	}
	
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInOk
  Desc:		完成当前输入告警的配置的设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmInOk()
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	UpdateData(TRUE);

	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle = m_bChkAlarmInHandle;
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType = m_comboAlarmInType.GetCurSel();
	memcpy(m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, m_csAlarmInName, NAME_LEN);
	m_bSetAlarmIn[m_iAlarmInIndex] = TRUE;
}

/*********************************************************
  Function:	OnBnClickedChkAlarmInHandle
  Desc:		是否进行告警输入量的处理
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedChkAlarmInHandle()
{
	UpdateData(TRUE);
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle = m_bChkAlarmInHandle;
	if (m_bChkAlarmInHandle)
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(TRUE);		
	}
	else
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarmOut
  Desc:		更新选中告警输出通道对应的参数并刷新控件
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnCbnSelchangeComboAlarmOut()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szTemp[100] = {0};
	DWORD dwID = 0;
	m_iAlarmOutIndex = m_comboAlarmOut.GetItemData(m_comboAlarmOut.GetCurSel());

	if (m_iAlarmOutIndex >= 0 && m_iAlarmOutIndex < MAX_ANALOG_ALARMOUT)
	{
		g_StringLanType(szLan, "本地", "Local");
		m_csAlarmOutIP.Format(szLan);
		m_csAlarmOutChan.Format("0");
	}
	else
	{
		dwID = g_struDeviceInfo[m_iDeviceIndex].struAlarmOutCfg.struIPAlarmOutInfo[m_iAlarmOutIndex-MAX_ANALOG_ALARMOUT].byIPID;
		if (dwID <= 0)
		{
			g_StringLanType(szLan, "不在线", "Offline");
			m_csAlarmOutIP.Format(szLan);
			m_csAlarmOutChan.Format("0");
		}
		else
		{
			m_csAlarmOutIP.Format("%s", g_struDeviceInfo[m_iDeviceIndex].struIPParaCfg.struIPDevInfo[dwID-1].struIP.sIpV4);
			m_csAlarmOutChan.Format("%d", m_struIPAlarmOutCfg.struIPAlarmOutInfo[m_iAlarmOutIndex-MAX_ANALOG_ALARMOUT].byAlarmOut);
		}
	}
	
	memcpy(szTemp, m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, NAME_LEN);
	m_csAlarmOutName.Format("%s", szTemp);
	m_comboAlarmOutDelay.SetCurSel(m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay);
	m_comboWeekday.SetCurSel(0);
	m_comboCopyDay.SetCurSel(0);

	m_iHour11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartHour;
	m_iMin11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartMin;
	m_iHour12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopHour;
	m_iMin12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopMin;
	m_iHour21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartHour;
	m_iMin21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartMin;
	m_iHour22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopHour;
	m_iMin22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopMin;
	m_iHour31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartHour;
	m_iMin31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartMin;
	m_iHour32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopHour;
	m_iMin32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopMin;
	m_iHour41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartHour;
	m_iMin41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartMin;
	m_iHour42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopHour;
	m_iMin42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopMin;
	m_iHour51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartHour;
	m_iMin51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartMin;
	m_iHour52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopHour;
	m_iMin52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopMin;
	m_iHour61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartHour;
	m_iMin61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartMin;
	m_iHour62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopHour;
	m_iMin62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopMin;
	m_iHour71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartHour;
	m_iMin71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartMin;
	m_iHour72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopHour;
	m_iMin72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopMin;
	m_iHour81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartHour;
	m_iMin81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartMin;
	m_iHour82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopHour;
	m_iMin82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopMin;

	UpdateData(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnAlarmOutOk
Desc:		完成告警输出的处理设置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmOutOk()
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	UpdateData(TRUE);
	OnBnClickedBtnAlarmOutDayOk();
	memcpy(m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, m_csAlarmOutName, NAME_LEN);
	m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay = m_comboAlarmOutDelay.GetCurSel();
	GetDlgItem(IDC_BTN_ALARM_OUT_COPY)->EnableWindow(TRUE);
	m_bSetAlarmOut[m_iAlarmOutIndex] = TRUE;
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarmOutWeekday
  Desc:		选择告警输入布防日期的参数的响应,获取参数并刷新参数对应的控件
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnCbnSelchangeComboAlarmOutWeekday()
{
	UpdateData(TRUE);
	int i = m_comboWeekday.GetCurSel();
	m_iHour11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartHour;
	m_iMin11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartMin;
	m_iHour12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopHour;
	m_iMin12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopMin;
	m_iHour21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartHour;
	m_iMin21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartMin;
	m_iHour22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopHour;
	m_iMin22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopMin;
	m_iHour31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartHour;
	m_iMin31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartMin;
	m_iHour32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopHour;
	m_iMin32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopMin;
	m_iHour41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartHour;
	m_iMin41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartMin;
	m_iHour42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopHour;
	m_iMin42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopMin;
	m_iHour51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartHour;
	m_iMin51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartMin;
	m_iHour52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopHour;
	m_iMin52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopMin;
	m_iHour61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartHour;
	m_iMin61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartMin;
	m_iHour62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopHour;
	m_iMin62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopMin;
	m_iHour71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartHour;
	m_iMin71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartMin;
	m_iHour72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopHour;
	m_iMin72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopMin;
	m_iHour81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartHour;
	m_iMin81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartMin;
	m_iHour82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopHour;
	m_iMin82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopMin;

	UpdateData(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnAlarmOutDayOk
Desc:		完称时间表设置,检验并更新对应结构中的时间表
Input:	
Output:	
Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmOutDayOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}

	int i = m_comboWeekday.GetCurSel();	
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartHour = m_iHour11;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartMin = m_iMin11;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopHour = m_iHour12;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopMin = m_iMin12;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartHour = m_iHour21;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartMin = m_iMin21;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopHour = m_iHour22;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopMin = m_iMin22;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartHour = m_iHour31;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartMin = m_iMin31;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopHour = m_iHour32;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopMin = m_iMin32;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartHour = m_iHour41;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartMin = m_iMin41;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopHour = m_iHour42;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopMin = m_iMin42;	

	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartHour = m_iHour51;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartMin = m_iMin51;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopHour = m_iHour52;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopMin = m_iMin52;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartHour = m_iHour61;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartMin = m_iMin61;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopHour = m_iHour62;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopMin = m_iMin62;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartHour = m_iHour71;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartMin = m_iMin71;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopHour = m_iHour72;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopMin = m_iMin72;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartHour = m_iHour81;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartMin = m_iMin81;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopHour = m_iHour82;
	m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopMin = m_iMin82;
	GetDlgItem(IDC_BTN_ALARM_OUT_DAY_COPY)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmOutDayCopy
  Desc:		复制选中日期的配置到对应日期
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmOutDayCopy()
{
	UpdateData(TRUE);
	int j,k;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboCopyDay.GetCurSel() - 1;

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
				memcpy(&(m_struAlarmOutCfg[i].struAlarmOutTime[j][k]), &(m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_struAlarmOutCfg[m_iCopyAlarmOut].struAlarmOutTime[m_nCopyTime][k]), &(m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmOutCopy
  Desc:		复制选中告警输出的配置到对应告警输出
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmOutCopy()
{
	UpdateData(TRUE);
//	CString sTemp;
	m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay = m_comboAlarmOutDelay.GetCurSel();
	//m_comboAlarmOut.GetLBText(m_iAlarmOutIndex, sTemp);
	memcpy(m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, m_csAlarmOutName, NAME_LEN);

	int i;
	m_iCopyAlarmOut = m_comboCopyAlarmOut.GetItemData(m_comboCopyAlarmOut.GetCurSel());	

	if (m_iCopyAlarmOut == -1)
	{
		for (i=0; i<(int)MAX_ALARMOUT_V30; i++)
		{
			
			if ( i<MAX_ANALOG_ALARMOUT && i>=(int)m_dwAlarmOutNum )
			{
				continue;
			}
			if ( i>=MAX_ANALOG_ALARMOUT )
			{//不存在的数字报警通道
				if (g_struDeviceInfo[m_iDeviceIndex].struAlarmOutCfg.struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].byIPID == 0)
				{
					continue;
				}
			}
			if (m_iAlarmOutIndex == i) 
			{
				continue;		
			}
			memcpy(&(m_struAlarmOutCfg[i]), &(m_struAlarmOutCfg[m_iAlarmOutIndex]), sizeof(NET_DVR_ALARMOUTCFG_V30));
			m_bSetAlarmOut[i] = TRUE;
			//g_bMustReboot = TRUE;
		}
	}
	else
	{	
		memcpy(&(m_struAlarmOutCfg[m_iCopyAlarmOut]), &(m_struAlarmOutCfg[m_iAlarmOutIndex]), sizeof(NET_DVR_ALARMOUTCFG_V30));
		m_bSetAlarmOut[m_iCopyAlarmOut] = TRUE;
		//g_bMustReboot = TRUE;
	}	
}

/*********************************************************
Function:	TimeTest
Desc:		校验时间正确性
Input:	
Output:	
Return:	TRUE,正确的时间表;FALSE,错误的时间表;
**********************************************************/
BOOL CDlgAlarmCfg::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
		(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
		(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
		(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = m_iHour11 * 100 + m_iMin11;
	wStartTime[1] = m_iHour21 * 100 + m_iMin21;
	wStartTime[2] = m_iHour31 * 100 + m_iMin31;
	wStartTime[3] = m_iHour41 * 100 + m_iMin41;
	wStopTime[0] = m_iHour12 * 100 + m_iMin12;
	wStopTime[1] = m_iHour22 * 100 + m_iMin22;
	wStopTime[2] = m_iHour32 * 100 + m_iMin32;
	wStopTime[3] = m_iHour42 * 100 + m_iMin42;
	wStartTime[4] = m_iHour51 * 100 + m_iMin51;
	wStartTime[5] = m_iHour61 * 100 + m_iMin61;
	wStartTime[6] = m_iHour71 * 100 + m_iMin71;
	wStartTime[7] = m_iHour81 * 100 + m_iMin81;
	wStopTime[4] = m_iHour52 * 100 + m_iMin52;
	wStopTime[5] = m_iHour62 * 100 + m_iMin62;
	wStopTime[6] = m_iHour72 * 100 + m_iMin72;
	wStopTime[7] = m_iHour82 * 100 + m_iMin82;
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

void CDlgAlarmCfg::OnBtnSetState() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_SetAlarmOut(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_iAlarmOutIndex, m_iState);
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmCfgSetup
  Desc:		设置报警配置信息
  Input:	
  Output:	
  Return:	TRUE,设置成功;FALSE,设置失败;
**********************************************************/
void CDlgAlarmCfg::OnBnClickedBtnAlarmCfgSetup() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	int i = 0;
	char szLan[128] = {0};
	for (i=0; i<(int)MAX_ALARMIN_V30; i++)//m_dwAlarmInNum
	{
		if (m_bSetAlarmIn[i])
		{
			if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_ALARMINCFG_V30, i, &(m_struAlarmInCfg[i]), sizeof(NET_DVR_ALARMINCFG_V30)))
			{
				g_StringLanType(szLan, "参数保存失败", "parameter save failed");
				AfxMessageBox(szLan);	
			}
			m_bSetAlarmIn[i] = FALSE;
		}
	}
	for (i=0; i<(int)MAX_ALARMOUT_V30; i++)//m_dwAlarmOutNum
	{
		if (m_bSetAlarmOut[i])
		{
			if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_ALARMOUTCFG_V30, i, &(m_struAlarmOutCfg[i]), sizeof(NET_DVR_ALARMOUTCFG_V30)))
			{
				g_StringLanType(szLan, "参数保存失败", "parameter save failed");
				AfxMessageBox(szLan);	
			}
			m_bSetAlarmOut[i] = FALSE;
		}		
	}	
}
