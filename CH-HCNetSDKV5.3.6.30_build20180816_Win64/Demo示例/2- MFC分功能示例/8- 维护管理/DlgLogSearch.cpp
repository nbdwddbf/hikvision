/*******************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd. 
文  件：	DlgLogSearch.cpp
开发单位：	杭州海康威视
编  写：	shizhiping
日  期：	2009.5
描  述：	远程日志查询
修  改：	
********************************************************/

#include "stdafx.h"
#include "Manage.h"
#include "DlgLogSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*************************************************
函数名:    	ParaTypeMap
函数描述:	获取日志类型字符串
输入参数:   stLogInfo-日志结构体
输出参数:   szTemp-	参数类型字符串	
返回值:	   
*************************************************/
void ParaTypeMap(NET_DVR_LOG_V30 stLogInfo, CString &szTemp)
{
	switch(stLogInfo.dwParaType)
	{
    case PARA_VIDEOOUT:
     szTemp.Format("VIDEOOUT");
     break;
    case PARA_IMAGE:
     szTemp.Format("IMAGE");
     break;
    case PARA_ENCODE:
     szTemp.Format("ENCODE");
        break;
    case PARA_NETWORK:
     szTemp.Format("NETWORK");
        break;
    case PARA_ALARM:
     szTemp.Format("ALARM");
     break;
    case PARA_EXCEPTION:
     szTemp.Format("EXCEPTION");
     break;
    case PARA_DECODER:
     szTemp.Format("DECODER");
        break;
    case PARA_RS232:
     szTemp.Format("RS232");
        break;
   case PARA_PREVIEW:
     szTemp.Format("PREVIEW");
        break;
    case PARA_SECURITY:
     szTemp.Format("SECURITY");
        break;
    case PARA_DATETIME:
     szTemp.Format("sys DATETIME");
     break;
    case PARA_FRAMETYPE:
     szTemp.Format("FRAMETYPE");
        break;
	default:
		break;
	}
}


/*************************************************
函数名:    	MinorTypeMap
函数描述:	获取日志次类型的字符串
输入参数:   stLogInfo-日志结构体
输出参数:   szTemp-	参数类型字符串	
返回值:	   
*************************************************/
void MinorTypeMap(NET_DVR_LOG_V30 stLogInfo, CString &szTemp)
{
	CString szParaType;
	switch(stLogInfo.dwMinorType)
	{
		//alarm
    case MINOR_ALARM_IN:
     szTemp.Format("ALARM_IN[%d]", stLogInfo.dwAlarmInPort);
     break;
    case MINOR_ALARM_OUT:
     szTemp.Format("ALARM_OUT[%d]",stLogInfo.dwAlarmOutPort);
     break;
    case MINOR_MOTDET_START:
     szTemp.Format("MOTDET_START[%d]", stLogInfo.dwChannel);
        break;
    case MINOR_MOTDET_STOP:
     szTemp.Format("MOTDET_STOP");
        break;
    case MINOR_HIDE_ALARM_START:
     szTemp.Format("HIDE_ALARM_START");
     break;
    case MINOR_HIDE_ALARM_STOP:
     szTemp.Format("HIDE_ALARM_STOP");
     break;
	 //exception
    case MINOR_VI_LOST:
     szTemp.Format("VI_LOST");
     break;
    case MINOR_ILLEGAL_ACCESS:
     szTemp.Format("ILLEGAL_ACCESS");
     break;
    case MINOR_HD_FULL:
     szTemp.Format("HD_FULL[%d]", stLogInfo.dwDiskNumber);
        break;
    case MINOR_HD_ERROR:
     szTemp.Format("HD_ERROR[%d]", stLogInfo.dwDiskNumber);
        break;
    case MINOR_REC_ERROR:
     szTemp.Format("REC_ERROR");
        break;
    case MINOR_DCD_LOST:
		szTemp.Format("DCD_LOST");
		break;
    case MINOR_IPC_NO_LINK:
     szTemp.Format("IPC_NO_LINK");
     break;
    case MINOR_IP_CONFLICT:
     szTemp.Format("IP_CONFLICT");
     break;
    case MINOR_NET_BROKEN:
     szTemp.Format("NET_BROKEN");
     break;
    case MINOR_VI_EXCEPTION:
     szTemp.Format("VI_EXCEPTION");
     break;
	 //operation
    case MINOR_START_DVR:
     szTemp.Format("START_DVR");
     break;
    case MINOR_STOP_DVR:
     szTemp.Format("STOP_DVR");
     break;
    case MINOR_STOP_ABNORMAL:
     szTemp.Format("STOP_ABNORMAL");
        break;
	case MINOR_REBOOT_DVR:
     szTemp.Format("REBOOT_DVR");
        break;
    case MINOR_LOCAL_LOGIN:
     szTemp.Format("LOCAL_LOGIN");
       break;
    case MINOR_LOCAL_LOGOUT:
      szTemp.Format("%s", "LOCAL_LOGOUT");
     break;
    case MINOR_LOCAL_CFG_PARM:
		ParaTypeMap(stLogInfo, szParaType);
		szTemp.Format("%s-%s", "LOCAL_CFG_PARM", szParaType.GetBuffer(0));
     break;
    case MINOR_LOCAL_PLAYBYFILE:
      szTemp.Format("%s","LOCAL_PLAYBYFILE");
        break;
    case MINOR_LOCAL_PLAYBYTIME:
      szTemp.Format("%s", "LOCAL_PLAYBYTIME");
        break;
    case MINOR_LOCAL_START_REC:
      szTemp.Format("%s", "LOCAL_START_REC");
     break;
    case MINOR_LOCAL_STOP_REC:
      szTemp.Format("%s", "LOCAL_STOP_REC");
     break;
    case MINOR_LOCAL_PTZCTRL:
      szTemp.Format("%s", "LOCAL_PTZCTRL");
     break;
    case MINOR_LOCAL_PREVIEW:
      szTemp.Format("%s", "LOCAL_PREVIEW");
     break;
    case MINOR_LOCAL_MODIFY_TIME:
      szTemp.Format("%s", "LOCAL_MODIFY_TIME");
     break;
    case MINOR_LOCAL_UPGRADE:
      szTemp.Format("%s", "LOCAL_UPGRADE");
     break;
    case MINOR_LOCAL_COPYFILE:
      szTemp.Format("%s", "LOCAL_COPYFILE");
     break;
	 
    case MINOR_LOCAL_LOCKFILE:
      szTemp.Format("%s", "LOCAL_LOCKFILE");
     break;
    case MINOR_LOCAL_UNLOCKFILE:
      szTemp.Format("%s", "LOCAL_UNLOCKFILE");
     break;
    case MINOR_LOCAL_FORMAT_HDD:
      szTemp.Format("%s", "LOCAL_FORMAT_HDD");
     break;

    case MINOR_REMOTE_LOGIN:
      szTemp.Format("%s", "REMOTE_LOGIN");
     break;
    case MINOR_REMOTE_LOGOUT:
      szTemp.Format("%s", "REMOTE_LOGOUT");
     break;
    case MINOR_REMOTE_START_REC:
      szTemp.Format("%s", "REMOTE_START_REC");
     break;
    case MINOR_REMOTE_STOP_REC:
      szTemp.Format("%s","REMOTE_STOP_REC");
     break;
    case MINOR_START_TRANS_CHAN:
      szTemp.Format("%s", "START_TRANS_CHAN");
     break;
    case MINOR_STOP_TRANS_CHAN:
      szTemp.Format("%s","STOP_TRANS_CHAN");
     break;
    case MINOR_REMOTE_GET_PARM:
		ParaTypeMap(stLogInfo, szParaType);
		szTemp.Format("%s-%s", "REMOTE_GET_PARM", szParaType.GetBuffer(0));
     break;
    case MINOR_REMOTE_CFG_PARM:
		ParaTypeMap(stLogInfo, szParaType);
		szTemp.Format("%s-%s", "REMOTE_CFG_PARM", szParaType.GetBuffer(0));
     break;
    case MINOR_REMOTE_GET_STATUS:
      szTemp.Format("%s", "REMOTE_GET_STATUS");
     break;
    case MINOR_REMOTE_ARM:
      szTemp.Format("%s", "REMOTE_ARM");
     break;
    case MINOR_REMOTE_DISARM:
      szTemp.Format("%s", "REMOTE_DISARM");
     break;
    case MINOR_REMOTE_REBOOT:
      szTemp.Format("%s", "REMOTE_REBOOT");
     break;
    case MINOR_START_VT:
      szTemp.Format("%s", "START_VT");
     break;
    case MINOR_STOP_VT:
      szTemp.Format("%s", "STOP_VT");
     break;
    case MINOR_REMOTE_UPGRADE:
      szTemp.Format("%s", "REMOTE_UPGRADE");
     break;
    case MINOR_REMOTE_PLAYBYFILE:
      szTemp.Format("%s", "REMOTE_PLAYBYFILE");
     break;
    case MINOR_REMOTE_PLAYBYTIME:
      szTemp.Format("%s", "REMOTE_PLAYBYTIME");
     break;
    case MINOR_REMOTE_PTZCTRL:
      szTemp.Format("%s", "REMOTE_PTZCTRL");
     break;
	case MINOR_REMOTE_STOP:
      szTemp.Format("%s", "REMOTE_STOP");
     break;

    case MINOR_REMOTE_LOCKFILE:
      szTemp.Format("%s", "REMOTE_LOCKFILE");
     break;
	case MINOR_REMOTE_CFGFILE_OUTPUT:
      szTemp.Format("%s", "REMOTE_CFGFILE_OUTPUT");
     break;

	case MINOR_REMOTE_CFGFILE_INTPUT:
      szTemp.Format("%s", "REMOTE_CFGFILE_INTPUT");
     break;
    case MINOR_REMOTE_FORMAT_HDD:
      szTemp.Format("%s", "REMOTE_FORMAT_HDD");
     break;
	case MINOR_REMOTE_IPC_ADD:
      szTemp.Format("%s", "REMOTE_IPC_ADD");
     break;

	case MINOR_REMOTE_IPC_DEL:
      szTemp.Format("%s", "REMOTE_IPC_DEL");
     break;
    case MINOR_REMOTE_IPC_SET:
      szTemp.Format("%s", "REMOTE_IPC_SET");
     break;
	case MINOR_LOCAL_CFGFILE_OUTPUT:
      szTemp.Format("%s", "LOCAL_CFGFILE_OUTPUT");
     break;
	case MINOR_LOCAL_CFGFILE_INPUT:
      szTemp.Format("%s", "LOCAL_CFGFILE_INPUT");
     break;
	case MINOR_LOCAL_DVR_ALARM:
      szTemp.Format("%s", "LOCAL_DVR_ALARM");
     break;
	case MINOR_REMOTE_DVR_ALARM:
      szTemp.Format("%s", "REMOTE_DVR_ALARM");
     break;
	case MINOR_IPC_ADD:
      szTemp.Format("%s", "IPC_ADD");
     break;
	case MINOR_IPC_DEL:
      szTemp.Format("%s", "IPC_DEL");
     break;
	case MINOR_IPC_SET:
      szTemp.Format("%s", "IPC_SET");
     break;

	case MINOR_HDD_INFO:
      szTemp.Format("%s", "HDD_INFO");
     break;
	case MINOR_SMART_INFO:
      szTemp.Format("%s", "SMART_INFO");
     break;
	case MINOR_REC_START:
      szTemp.Format("%s", "REC_START");
     break;
	case MINOR_REC_STOP:
      szTemp.Format("%s", "REC_STOP");
     break;
	case MINOR_REC_OVERDUE:
      szTemp.Format("%s", "REC_OVERDUE");
     break;	 
    default:
      szTemp.Format("0x%x", stLogInfo.dwMinorType);
     break;
    }
}

/*********************************************************
函数名:	        GetLogFileThread
函数描述:		日志文件获取线程
输入参数:		pParam,参数指针
输出参数:	
返回值:	
**********************************************************/
UINT GetLogFileThread(LPVOID pParam)
{
	CDlgLogSearch *pLogSearch  = (CDlgLogSearch*)pParam;
	LONG bRet = -1;
	NET_DVR_LOG_V30 struFileInfo;
	CString csTmp;
	char szLan[128] = {0};
	while (1) 
	{
		bRet = NET_DVR_FindNextLog_V30(pLogSearch->m_lLogHandle, &struFileInfo);
		if (bRet == NET_DVR_FILE_SUCCESS)
		{
			csTmp.Format("%d", pLogSearch->m_lLogNum+1);
			pLogSearch->m_listDeviceLog.InsertItem(pLogSearch->m_lLogNum, csTmp,0);
			csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struFileInfo.strLogTime.dwYear, struFileInfo.strLogTime.dwMonth, struFileInfo.strLogTime.dwDay, \
				struFileInfo.strLogTime.dwHour,struFileInfo.strLogTime.dwMinute, struFileInfo.strLogTime.dwSecond);
			pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 1, csTmp);	
			switch(struFileInfo.dwMajorType)
			{
			case 1:
				g_StringLanType(szLan, "报警", "Alarm");
				csTmp.Format("%s",szLan);
				break;
			case 2:
				g_StringLanType(szLan, "异常", "Abnormal");
				csTmp.Format("%s",szLan);
				break;
			case 3:
				g_StringLanType(szLan, "操作", "Operation");
				csTmp.Format("%s",szLan);
			    break;
			case 4:
				g_StringLanType(szLan, "附加信息", "Additional information");
				csTmp.Format("%s",szLan);
			    break;
			default:
				g_StringLanType(szLan, "未知类型", "Unknown");
				csTmp.Format("%s",szLan);
			    break;
			}
			pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 2, csTmp);
			
			MinorTypeMap(struFileInfo, csTmp);
	
			pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 3, csTmp);
	

			if (struFileInfo.dwChannel > 0)
			{
				sprintf(szLan, "chan[%d]%s-%s", struFileInfo.dwChannel,struFileInfo.sNetUser, struFileInfo.sPanelUser);
			}
			else if (struFileInfo.dwAlarmInPort)
			{
				sprintf(szLan, "[%s-%s], AlarmIn[%d]", struFileInfo.sNetUser, struFileInfo.sPanelUser, struFileInfo.dwAlarmInPort);
			}
			else if (struFileInfo.dwAlarmOutPort)
			{
				sprintf(szLan, "[%s-%s], AlarmOut[%d]", struFileInfo.sNetUser, struFileInfo.sPanelUser, struFileInfo.dwAlarmOutPort);
			}
			else
			{
				sprintf(szLan, "[%s-%s]", struFileInfo.sNetUser, struFileInfo.sPanelUser);
			}
			
			csTmp.Format("%s-%s",struFileInfo.struRemoteHostAddr.sIpV4, szLan);
			pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 4, csTmp);
			
			if (struFileInfo.dwInfoLen > 0)
			{
				csTmp.Format("%s",struFileInfo.sInfo);
			}
			else
			{
				csTmp.Format("");
			}
			
			pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 5, csTmp);

			pLogSearch->m_lLogNum++;
		}
		else
		{
			if (bRet == NET_DVR_ISFINDING)
			{
				pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
				pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("日志搜索中......");
				Sleep(5);
				continue;
			}
			if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "搜索日志", "Search Log");
				pLogSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
				pLogSearch->m_bSearch = FALSE;
				pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "搜索日志结束!", "Search log Ending");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "搜索日志", "Search Log");
				pLogSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
				pLogSearch->m_bSearch = FALSE;
				g_StringLanType(szLan, "由于服务器忙,或网络故障,搜索日志异常终止!",\
					"Since the server is busy, or network failure, search the log abnormal termination");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	CloseHandle(pLogSearch->m_hFileThread);
	pLogSearch->m_hFileThread = NULL;
	NET_DVR_FindLogClose_V30(pLogSearch->m_lLogHandle);
	return 0;
}



/////////////////////////////////////////////////////////////////////////////
// CDlgLogSearch dialog


CDlgLogSearch::CDlgLogSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogSearch::IDD, pParent)
	, m_ctTimeStart(0)
	, m_ctDateStart(0)
	, m_ctDateStop(0)
	, m_ctTimeStop(0)
	, m_lLoginID(-1)
	, m_hFileThread(NULL)
	, m_iMode(0)
	, m_iMajType(0)
	, m_iMinType(0)
	, m_bSearch(FALSE)
	, m_lLogHandle(-1)
	, m_lLogNum(0)
	, m_bChkSmart(FALSE)
{
	//{{AFX_DATA_INIT(CDlgLogSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLogSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogSearch)
	DDX_Control(pDX, IDC_COMBO_MODE, m_comboMode);
	DDX_Control(pDX, IDC_COMBO_MAJOR_TYPE, m_comboMajorType);
	DDX_Control(pDX, IDC_COMBO_MINOR_TYPE, m_comboMinorType);
	DDX_DateTimeCtrl(pDX, IDC_TIME_LOG_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_LOG_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_LOG_STOP, m_ctDateStop);
	DDX_DateTimeCtrl(pDX, IDC_TIME_LOG_STOP, m_ctTimeStop);
	DDX_Control(pDX, IDC_LIST_DEVICE_LOG, m_listDeviceLog);
	DDX_Check(pDX, IDC_CHK_SMART, m_bChkSmart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgLogSearch)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearchLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogSearch message handlers

BOOL CDlgLogSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	m_listDeviceLog.SetExtendedStyle(m_listDeviceLog.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	m_listDeviceLog.InsertColumn(0, "序号", LVCFMT_RIGHT, 60, -1);
	m_listDeviceLog.InsertColumn(1, "日志时间", LVCFMT_LEFT, 140, -1);
	m_listDeviceLog.InsertColumn(2, "主类型", LVCFMT_LEFT,80, -1);
	m_listDeviceLog.InsertColumn(3, "次类型", LVCFMT_LEFT, 150, -1);
	m_listDeviceLog.InsertColumn(4, "远程主机", LVCFMT_LEFT, 100, -1);
	m_listDeviceLog.InsertColumn(5, "描述", LVCFMT_LEFT, 251, -1);
	

	m_lLogNum = 0;
	m_lLogHandle = -1;	
	CTime ctCurTime = CTime::GetCurrentTime();
	CTime time(ctCurTime.GetYear(),ctCurTime.GetMonth(),ctCurTime.GetDay(),0,0,0);
	CTime time0(ctCurTime.GetYear(),ctCurTime.GetMonth(),ctCurTime.GetDay(),23,59,59);
	m_ctDateStart = time;
	m_ctTimeStart = time;
	m_ctDateStop = ctCurTime;
	m_ctTimeStop = time0;
	m_iMode = 2;
	m_iMajType = 0;
	m_iMinType = 0;
	m_comboMode.SetCurSel(m_iMode);
	m_comboMajorType.SetCurSel(m_iMajType);
	m_comboMinorType.SetCurSel(m_iMinType);

	//添加次类型
    AddMinorString();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*************************************************
函数名:    	AddMinorString
函数描述:	添加次类型
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CDlgLogSearch::AddMinorString()
{
    CString szTemp;
	int iSel = 0;
	m_comboMinorType.ResetContent();
	m_comboMinorType.AddString("All");
	m_comboMinorType.SetItemData(iSel, 0);
	m_comboMinorType.SetCurSel(0);

	szTemp.Format("ALARM_IN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_ALARM_IN);

	szTemp.Format("ALARM_OUT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_ALARM_OUT);

	szTemp.Format("MOTDET_START");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_MOTDET_START);

	szTemp.Format("MOTDET_STOP");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_MOTDET_STOP);

	szTemp.Format("HIDE_ALARM_START");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_HIDE_ALARM_START);

	szTemp.Format("HIDE_ALARM_STOP");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_HIDE_ALARM_STOP);
	//exception
	szTemp.Format("---Excp----------");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, 0);

	szTemp.Format("VI_LOST");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_VI_LOST);

	szTemp.Format("ILLEGAL_ACCESS");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_ILLEGAL_ACCESS);

	szTemp.Format("HD_FULL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_HD_FULL);

	szTemp.Format("HD_ERROR");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_HD_ERROR);

	szTemp.Format("REC_ERROR");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REC_ERROR);

	szTemp.Format("DCD_LOST");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_DCD_LOST);

	szTemp.Format("IPC_NO_LINK");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_IPC_NO_LINK);

	szTemp.Format("IP_CONFLICT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_IP_CONFLICT);

	szTemp.Format("NET_BROKEN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_NET_BROKEN);

	szTemp.Format("VI_EXCEPTION");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_VI_EXCEPTION);
	//operation
	szTemp.Format("%s", "---Oper----------");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, 0);
	szTemp.Format("START_DVR");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_START_DVR);

	szTemp.Format("STOP_DVR");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_STOP_DVR);

	szTemp.Format("STOP_ABNORMAL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_STOP_ABNORMAL);

	szTemp.Format("REBOOT_DVR");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REBOOT_DVR);

	szTemp.Format("LOCAL_LOGIN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_LOGIN);

	szTemp.Format("%s", "LOCAL_LOGOUT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_LOGOUT);

	szTemp.Format("LOCAL_CFG_PARM");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFG_PARM);

	szTemp.Format("%s","LOCAL_PLAYBYFILE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PLAYBYFILE);

	szTemp.Format("%s", "LOCAL_PLAYBYTIME");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PLAYBYTIME);

	szTemp.Format("%s", "LOCAL_START_REC");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_START_REC);

	szTemp.Format("%s", "LOCAL_STOP_REC");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_STOP_REC);

	szTemp.Format("%s", "LOCAL_PTZCTRL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PTZCTRL);

	szTemp.Format("%s", "LOCAL_PREVIEW");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PREVIEW);

	szTemp.Format("%s", "LOCAL_MODIFY_TIME");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MODIFY_TIME);

	szTemp.Format("%s", "LOCAL_UPGRADE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_UPGRADE);

	szTemp.Format("%s", "LOCAL_COPYFILE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COPYFILE);


	szTemp.Format("%s", "LOCAL_LOCKFILE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_LOCKFILE);

	szTemp.Format("%s", "LOCAL_UNLOCKFILE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_UNLOCKFILE);

	szTemp.Format("%s", "LOCAL_FORMAT_HDD");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FORMAT_HDD);

	szTemp.Format("%s", "LOCAL_CFGFILE_OUTPUT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFGFILE_OUTPUT);

	szTemp.Format("%s", "LOCAL_CFGFILE_INPUT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFGFILE_INPUT);

	szTemp.Format("%s", "LOCAL_DVR_ALARM");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DVR_ALARM);
	szTemp.Format("%s", "IPC_ADD");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_IPC_ADD);

	szTemp.Format("%s", "IPC_DEL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_IPC_DEL);

	szTemp.Format("%s", "IPC_SET");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_IPC_SET);
////remote 
	szTemp.Format("%s", "---Remote----------");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, 0);

	szTemp.Format("%s", "REMOTE_LOGIN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_LOGIN);

	szTemp.Format("%s", "REMOTE_LOGOUT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_LOGOUT);

	szTemp.Format("%s", "REMOTE_START_REC");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_START_REC);

	szTemp.Format("%s","REMOTE_STOP_REC");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_STOP_REC);

	szTemp.Format("%s", "START_TRANS_CHAN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_START_TRANS_CHAN);

	szTemp.Format("%s","STOP_TRANS_CHAN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_STOP_TRANS_CHAN);

	szTemp.Format("REMOTE_GET_PARM");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_PARM);

	szTemp.Format("REMOTE_CFG_PARM");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFG_PARM);

	szTemp.Format("%s", "REMOTE_GET_STATUS");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_STATUS);

	szTemp.Format("%s", "REMOTE_ARM");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_ARM);

	szTemp.Format("%s", "REMOTE_DISARM");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DISARM);

	szTemp.Format("%s", "REMOTE_REBOOT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_REBOOT);

	szTemp.Format("%s", "START_VT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_START_VT);

	szTemp.Format("%s", "STOP_VT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_STOP_VT);

	szTemp.Format("%s", "REMOTE_UPGRADE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_UPGRADE);

	szTemp.Format("%s", "REMOTE_PLAYBYFILE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PLAYBYFILE);

	szTemp.Format("%s", "REMOTE_PLAYBYTIME");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PLAYBYTIME);

	szTemp.Format("%s", "REMOTE_PTZCTRL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PTZCTRL);

	szTemp.Format("%s", "REMOTE_STOP");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_STOP);


	szTemp.Format("%s", "REMOTE_LOCKFILE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_LOCKFILE);

	szTemp.Format("%s", "REMOTE_CFGFILE_OUTPUT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFGFILE_OUTPUT);


	szTemp.Format("%s", "REMOTE_CFGFILE_INTPUT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFGFILE_INTPUT);

	szTemp.Format("%s", "REMOTE_FORMAT_HDD");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FORMAT_HDD);
	szTemp.Format("%s", "REMOTE_DVR_ALARM");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DVR_ALARM);
	szTemp.Format("%s", "REMOTE_IPC_ADD");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IPC_ADD);


	szTemp.Format("%s", "REMOTE_IPC_DEL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IPC_DEL);

	szTemp.Format("%s", "REMOTE_IPC_SET");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IPC_SET);

//information
	szTemp.Format("%s", "--INFOR-------------");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, 0);

	szTemp.Format("%s", "HDD_INFO");
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_HDD_INFO);

	szTemp.Format("%s", "SMART_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_SMART_INFO);

	szTemp.Format("%s", "REC_START");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REC_START);

	szTemp.Format("%s", "REC_STOP");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REC_STOP);
	szTemp.Format("%s", "REC_OVERDUE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REC_OVERDUE);
}

/*************************************************
函数名:    	OnBtnSearchLog
函数描述:	查询日志按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CDlgLogSearch::OnBtnSearchLog() 
{
	
	UpdateData(TRUE);
	if (!m_bSearch)
	{
		NET_DVR_TIME StartTime;
		NET_DVR_TIME StopTime;
		
		m_iMode = m_comboMode.GetCurSel();
		m_iMajType = m_comboMajorType.GetCurSel();
		m_iMinType = m_comboMinorType.GetItemData(m_comboMinorType.GetCurSel());
		StartTime.dwYear = (WORD)m_ctDateStart.GetYear();
		StartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
		StartTime.dwDay = (WORD)m_ctDateStart.GetDay();
		StartTime.dwHour = (char)m_ctTimeStart.GetHour();
		StartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
		StartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
		
		StopTime.dwYear = (WORD)m_ctDateStop.GetYear();
		StopTime.dwMonth = (WORD)m_ctDateStop.GetMonth();
		StopTime.dwDay = (WORD)m_ctDateStop.GetDay();
		StopTime.dwHour = (char)m_ctTimeStop.GetHour();
		StopTime.dwMinute = (char)m_ctTimeStop.GetMinute();
		StopTime.dwSecond = (char)m_ctTimeStop.GetSecond();
		
		LONG lLoginID = g_pMainDlg->m_struDeviceInfo.lLoginID;
		

		if(lLoginID == -1)
		{
			char csTmp[128]={0};
			g_StringLanType(csTmp,"请先注册","Login First");
			AfxMessageBox(csTmp);
			return;
		}

		m_lLogHandle = NET_DVR_FindDVRLog_V30(g_pMainDlg->m_struDeviceInfo.lLoginID, m_iMode, m_iMajType, m_iMinType, &StartTime, &StopTime, m_bChkSmart);
		if (m_lLogHandle < 0)
		{
			MessageBox("搜索日志失败!");
			return;
		}
		m_bSearch = TRUE;
		m_lLogNum = 0;
		m_listDeviceLog.DeleteAllItems();
		DWORD dwThreadId;
		if (m_hFileThread == NULL)
		{
			m_hFileThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetLogFileThread),this,0,&dwThreadId);		
		}
		if (m_hFileThread == NULL)
		{
			MessageBox("打开日志搜索线程失败");
			return;
		}
		GetDlgItem(IDC_BTN_SEARCH)->SetWindowText("停止搜索");
		m_bSearch = TRUE;
	}
	else
	{
        if (!NET_DVR_FindLogClose_V30(m_lLogHandle))
		{
		//	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FindLogClose_V30");
		}
		m_lLogHandle = -1;
		char szLan[128]={0};
		g_StringLanType(szLan, "搜索日志", "Search Log");
		GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
		m_bSearch = FALSE;
		m_lLogNum = 0;
		if (m_hFileThread)
		{
			TerminateThread(m_hFileThread, 0);
			CloseHandle(m_hFileThread);
			m_hFileThread = NULL;
		}
		
		m_hFileThread = NULL;
	}
}
