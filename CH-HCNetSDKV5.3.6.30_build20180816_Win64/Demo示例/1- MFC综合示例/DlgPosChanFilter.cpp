// DlgPosChanFilter.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPosChanFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPosChanFilter dialog


CDlgPosChanFilter::CDlgPosChanFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosChanFilter::IDD, pParent)
    , m_dwTimeOut(0)
{
	//{{AFX_DATA_INIT(CDlgPosChanFilter)
	m_byColorB = 0;
	m_byColorG = 0;
	m_byColorR = 0;
	m_wDelayTime = 0;
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
	m_dwHour61 = 0;
	m_dwHour62 = 0;
	m_dwHour71 = 0;
	m_dwHour72 = 0;
	m_dwHour81 = 0;
	m_dwHour82 = 0;
	m_dwMin11 = 0;
	m_dwMin12 = 0;
	m_dwMin21 = 0;
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
	m_dwMin81 = 0;
	m_dwMin82 = 0;
	m_fRegionLenth = 0.0f;
	m_fRegionWight = 0.0f;
	m_fReginX = 0.0f;
	m_fRegionY = 0.0f;
	m_bChkAudioAlarm = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	m_bChkInvokeJepgCap = FALSE;
	m_iUserID = -1;
	m_iDevIndex = -1;
	m_bPicFtp = FALSE;
    m_bPicCloud = FALSE;
	m_bReportCenter = FALSE;
	m_bShowPosInfo = FALSE;
	m_bMonitorAlarm = FALSE;
	m_bAlarmoutEmap = FALSE;
	//}}AFX_DATA_INIT

	m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
    if (m_pbAlarmOut != NULL)
    {
        memset(m_pbAlarmOut, 0, sizeof(BOOL)*MAX_ALARMOUT_V40);
    }
	
    m_pbRecordChan =  new BOOL[MAX_CHANNUM_V40];
    if (m_pbRecordChan != NULL)
    {
        memset(m_pbRecordChan, 0, sizeof(BOOL)*MAX_CHANNUM_V40);
    }
}

CDlgPosChanFilter::~CDlgPosChanFilter()
{
	if (m_pbAlarmOut != NULL)
	{
		delete []m_pbAlarmOut;
		m_pbAlarmOut = NULL;
	}
	
	if (m_pbRecordChan != NULL)
	{
		delete []m_pbRecordChan;
		m_pbRecordChan = NULL;
	}
}
void CDlgPosChanFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPosChanFilter)
	DDX_Control(pDX, IDC_COMBO_OVERLAY_MODE, m_cmbOverlayMode);
	DDX_Control(pDX, IDC_COMBO_MOTION_DAY_COPY, m_cmbDayCopy);
	DDX_Control(pDX, IDC_COMBO_MOTION_WEEKDAY, m_cmbWeekDay);
	DDX_Control(pDX, IDC_TREE_CHAN, m_treeChan);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMBO_FONTSIZE, m_cmbFontSize);
	DDX_Control(pDX, IDC_COMBO_THEFILTERNUM, m_comboTheFilterNum);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_comboGroup);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_Text(pDX, IDC_EDIT_COLOR_B, m_byColorB);
	DDX_Text(pDX, IDC_EDIT_COLOR_G, m_byColorG);
	DDX_Text(pDX, IDC_EDIT_COLOR_R, m_byColorR);
	DDX_Text(pDX, IDC_EDIT_DELAYTIME, m_wDelayTime);
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
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_dwHour61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_dwHour62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_dwHour71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_dwHour72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_dwHour81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_dwHour82);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_dwMin11);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_dwMin12);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_dwMin21);
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
	DDX_Text(pDX, IDC_EDIT_MIN81, m_dwMin81);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_dwMin82);
	DDX_Text(pDX, IDC_EDIT_REGION_LENTH, m_fRegionLenth);
	DDX_Text(pDX, IDC_EDIT_REGION_WIGHT, m_fRegionWight);
	DDX_Text(pDX, IDC_EDIT_REGION_X, m_fReginX);
	DDX_Text(pDX, IDC_EDIT_REGION_Y, m_fRegionY);
	DDX_Check(pDX, IDC_CHK_AUDIO_ALARM, m_bChkAudioAlarm);
	DDX_Check(pDX, IDC_CHK_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJepgCap);
	DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bPicFtp);
    DDX_Check(pDX, IDC_CHK_PIC_CLOUD, m_bPicCloud);
	DDX_Check(pDX, IDC_CHK_REPORT_CENTER, m_bReportCenter);
	DDX_Check(pDX, IDC_CHK_SHOW_POSINFO, m_bShowPosInfo);
	DDX_Check(pDX, IDC_CHK_MONITOR_ALARM, m_bMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_ALARMOUT_EMAP, m_bAlarmoutEmap);
    DDX_Text(pDX, IDC_EDIT_TIME_OUT, m_dwTimeOut);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPosChanFilter, CDialog)
	//{{AFX_MSG_MAP(CDlgPosChanFilter)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, OnSelchangeComboGroup)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_CBN_EDITCHANGE(IDC_COMBO_THEFILTERNUM, OnEditchangeComboThefilternum)
	ON_CBN_SELCHANGE(IDC_COMBO_THEFILTERNUM, OnSelchangeComboThefilternum)
	ON_BN_CLICKED(IDC_BTN_MOTION_DAY_COPY, OnBtnMotionDayCopy)
	ON_CBN_SELCHANGE(IDC_COMBO_MOTION_WEEKDAY, OnSelchangeComboMotionWeekday)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAN, OnClickTreeChan)
	ON_BN_CLICKED(IDC_MOTION_DAY_OK, OnMotionDayOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPosChanFilter message handlers

BOOL CDlgPosChanFilter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_dwCurselectIndx = 0;
	// TODO: Add extra initialization here
	memset(&m_struChanFilterCfg, 0 ,sizeof(m_struChanFilterCfg));
	memset(&m_struChanGroup,0,sizeof(m_struChanGroup));
	CreateTree();

	m_cmbFontSize.SetCurSel(0);
	m_comboChannel.SetCurSel(0);
	m_comboTheFilterNum.SetCurSel(0);
	m_cmbOverlayMode.SetCurSel(0);
	m_cmbWeekDay.SetCurSel(0);

	//GetFilterCfgInfo(0);
	AddChanInfo();
	m_comboChannel.SetCurSel(0);
	m_comboGroup.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPosChanFilter::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
//	GetFilterCfgInfo(0);

}

void CDlgPosChanFilter::OnSelchangeComboGroup() 
{
	// TODO: Add your control notification handler code here
	/*char szLan[128] = {0};
	int iIndex = m_comboGroup.GetCurSel();
	if (iIndex == LB_ERR)
	{
		g_StringLanType(szLan,"请选择组号","Please select Group Number frist!");
		AfxMessageBox(szLan);
		return ;
	}
	GetFilterCfgInfo(iIndex);
*/
}

void CDlgPosChanFilter::GetFilterCfgInfo(UINT dwIndex)
{
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	int i = 0;
	//获取过滤规则信息
	memset(&m_struChanGroup, 0,sizeof(m_struChanGroup));
	m_struChanGroup.dwSize = sizeof(m_struChanGroup);
	m_struChanGroup.dwChannel = m_comboChannel.GetItemData(m_comboChannel.GetCurSel());

	if (!NET_DVR_GetDeviceConfig(m_iUserID, NET_DVR_GET_CHAN_FILTER_CFG	,1,&m_struChanGroup, sizeof(m_struChanGroup), &dwReturn,&m_struChanFilterCfg,sizeof(m_struChanFilterCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CHAN_FILTER_CFG");
		return ;
	}
	else if (dwReturn != NET_DVR_NOERROR)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CHAN_FILTER_CFG");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CHAN_FILTER_CFG");
	}
	
	UpdateData(FALSE);
}

void CDlgPosChanFilter::ShowPosFilterInfo( UINT dwTheFilterNum)  
{
/*xyqTest	m_csPosFilterName.Format("%s",m_struPosFilterCfg.struFilterCfg[dwTheFilterNum].sPosName);
	m_comboConnectMode.SetCurSel(m_struPosFilterCfg.struFilterCfg[dwTheFilterNum].dwProtocolType - 1);
	*/
}

void CDlgPosChanFilter::AddChanInfo()
{
	UpdateData(TRUE);
	int iIndex = 0;

	for (int i = 0; i < g_struDeviceInfo[m_iDevIndex].iDeviceChanNum; i++)
	{
		m_comboChannel.AddString(g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].chChanName);
		m_comboChannel.SetItemData(iIndex, g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO);
		iIndex++;
	}

	m_comboChannel.SetCurSel(0);
	UpdateData(FALSE);
}

void CDlgPosChanFilter::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	char szLan[256] = {0};
	m_struChanFilterCfg.dwSize = sizeof(m_struChanFilterCfg);
	
	m_struChanFilterCfg.byFilterID = m_comboTheFilterNum.GetCurSel() + m_comboGroup.GetCurSel() * FILTERRULE_NUM +1;
	
	GetChanFilterInfo();
	memset(&m_struChanGroup, 0,sizeof(m_struChanGroup));
	m_struChanGroup.dwSize = sizeof(m_struChanGroup);
	m_struChanGroup.dwChannel =m_comboChannel.GetItemData(m_comboChannel.GetCurSel());
	DWORD dwStatues = NET_DVR_NOERROR;
	
	if (NET_DVR_SetDeviceConfig(m_iUserID, NET_DVR_SET_CHAN_FILTER_CFG, 1,&m_struChanGroup,sizeof(m_struChanGroup), &dwStatues,&m_struChanFilterCfg, \
		sizeof(m_struChanFilterCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CHAN_FILTER_CFG");
		
	}
	else if (dwStatues != NET_DVR_NOERROR)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CHAN_FILTER_CFG");

		sprintf(szLan,"NET_DVR_SET_CHAN_FILTER_CFG Err[%d]",dwStatues);
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CHAN_FILTER_CFG");
		return;
	}
 
}

void CDlgPosChanFilter::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	DWORD dwGroupNum = 0;
	char szLan[256] = {0};
	DWORD dwReturn = 0;

	memset(&m_struChanFilterCfg, 0, sizeof(m_struChanFilterCfg));

	memset(&m_struChanGroup, 0,sizeof(m_struChanGroup));
	m_struChanGroup.dwSize = sizeof(m_struChanGroup);
	m_struChanGroup.dwChannel =m_comboChannel.GetItemData(m_comboChannel.GetCurSel());
	DWORD dwStatues = NET_DVR_NOERROR;
	 
	UINT32 dwChannelNum = 0 ;
	dwChannelNum = m_comboChannel.GetCurSel() + 1;
	if (!NET_DVR_GetDeviceConfig(m_iUserID, NET_DVR_GET_CHAN_FILTER_CFG,1,&m_struChanGroup,sizeof(m_struChanGroup),&dwStatues,&m_struChanFilterCfg, sizeof(m_struChanFilterCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T , "NET_DVR_GET_CHAN_FILTER_CFG");
				return;
	}
	else if (dwStatues != NET_DVR_NOERROR)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CHAN_FILTER_CFG");
		
		sprintf(szLan,"NET_DVR_GET_CHAN_FILTER_CFG Err[%d]",dwStatues);
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CHAN_FILTER_CFG");

	}


	//Show Relate Info
	SetChanFilterInfo();
	OnSelchangeComboMotionWeekday();

	UpdateData(FALSE);	
}


void CDlgPosChanFilter::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	int iSelectChan = -1;
	char szLan[128] = {0};
	iSelectChan = m_comboChannel.GetCurSel();
/*xyqTest	sprintf(szLan, "%s", m_struPosFilterCfg.struFilterCfg[iSelectChan].sPosName);*/
	UpdateData(FALSE);
}

void CDlgPosChanFilter::OnEditchangeComboThefilternum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwTheFilterNum = m_comboTheFilterNum.GetCurSel();
	ShowPosFilterInfo(dwTheFilterNum);
	UpdateData(FALSE);

	
}

void CDlgPosChanFilter::OnSelchangeComboThefilternum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//Get FilterNum
	DWORD dwSelectFilter = m_comboTheFilterNum.GetCurSel();
	ShowPosFilterInfo(dwSelectFilter);
	
	UpdateData(FALSE);
}
void CDlgPosChanFilter::CreateTree(void)
{
	//m_treeAlarmOut.DeleteAllItems();
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex, m_pbAlarmOut);
	m_treeChan.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
 	HTREEITEM hChanItem = NULL;
	
	g_CreateChannelTree(m_treeChan, m_iDevIndex, m_pbRecordChan);
	UpdateData(FALSE);

}

void CDlgPosChanFilter::OnBtnMotionDayCopy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int j,k;
	int i = m_cmbWeekDay.GetCurSel();
	int m_nCopyTime = m_cmbDayCopy.GetCurSel() - 1;
	
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
				memcpy(&(m_struChanFilterCfg.struAlarmSched[j][k]), &(m_struChanFilterCfg.struAlarmSched[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
	
	for (k=0; k<MAX_TIMESEGMENT_V30; k++)
	{
		memcpy(&(m_struChanFilterCfg.struAlarmSched[m_nCopyTime][k]), &(m_struChanFilterCfg.struAlarmSched[i][k]), sizeof(NET_DVR_SCHEDTIME));
	}

}

void CDlgPosChanFilter::GetChanFilterInfo()
{
	UpdateData(TRUE);
	m_struChanFilterCfg.dwSize = sizeof(m_struChanFilterCfg);

	m_struChanFilterCfg.struHandleException.dwHandleType = 0;
	m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bMonitorAlarm << 0);
	m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bChkAudioAlarm << 1);
	m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bReportCenter << 2);
	m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bChkInvokeJepgCap << 4);
	m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bAlarmoutEmap<<6);
	m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bPicFtp << 9);
    m_struChanFilterCfg.struHandleException.dwHandleType |= (m_bPicCloud << 12);

	m_struChanFilterCfg.byFilterID = m_comboTheFilterNum.GetCurSel()+1;
	m_struChanFilterCfg.byFontSize = m_cmbFontSize.GetCurSel();
	m_struChanFilterCfg.byShowPosInfo = m_bShowPosInfo;
	m_struChanFilterCfg.byOverlayMode = m_cmbOverlayMode.GetCurSel();

	m_struChanFilterCfg.dwDelayTime = m_wDelayTime;
    m_struChanFilterCfg.dwTimeOut = m_dwTimeOut;
	m_struChanFilterCfg.struOsdColor.byRed = m_byColorR;
	m_struChanFilterCfg.struOsdColor.byGreen = m_byColorG;
	m_struChanFilterCfg.struOsdColor.byBlue = m_byColorB;

	m_struChanFilterCfg.struOsdPosInfo.struStart.fX = m_fReginX;
	m_struChanFilterCfg.struOsdPosInfo.struStart.fY= m_fRegionY;

	m_struChanFilterCfg.struOsdPosInfo.struEnd.fX = m_fRegionLenth;
	m_struChanFilterCfg.struOsdPosInfo.struEnd.fY= m_fRegionWight;


    int i = 0;

	//relate Alaram chan
	DWORD dwRelNum= 0;
	memset(m_struChanFilterCfg.struHandleException.dwRelAlarmOut,0xff, MAX_CHANNUM_V30 *sizeof(DWORD));
	for( i = 0; i< MAX_ALARMOUT_V40;i++)
	{
		if (m_pbAlarmOut[i]==1)
		{
			if (m_struChanFilterCfg.struHandleException.dwRelAlarmOutChanNum < MAX_CHANNUM_V30)
			{
				m_struChanFilterCfg.struHandleException.dwRelAlarmOut[m_struChanFilterCfg.struHandleException.dwRelAlarmOutChanNum] = i;
				m_struChanFilterCfg.struHandleException.dwRelAlarmOutChanNum++;
			}
			else
			{
				break;
			}
		}
	}


	memset(m_struChanFilterCfg.dwRelRecordChan,0xff, MAX_CHANNUM_V30 *sizeof(DWORD));
	for( i = 0; i< MAX_CHANNUM_V40;i++)
	{
		if (m_pbRecordChan[i]==1)
		{
			if (m_struChanFilterCfg.dwRelRecordChanNum < MAX_CHANNUM_V30)
			{
				m_struChanFilterCfg.dwRelRecordChan[m_struChanFilterCfg.dwRelRecordChanNum] = i +1;
				m_struChanFilterCfg.dwRelRecordChanNum++;
			}
			else
			{
				break;
			}
		}
	}
 
}
void CDlgPosChanFilter::SetChanFilterInfo()
{
	m_bMonitorAlarm = (m_struChanFilterCfg.struHandleException.dwHandleType>> 0)& 0x1;
	m_bChkAudioAlarm = (m_struChanFilterCfg.struHandleException.dwHandleType>> 1)& 0x1;
	m_bReportCenter = (m_struChanFilterCfg.struHandleException.dwHandleType>> 2) & 0x1;
	m_bChkInvokeAlarmOut = (m_struChanFilterCfg.struHandleException.dwHandleType>> 3) & 0x1;
	m_bChkInvokeJepgCap = (m_struChanFilterCfg.struHandleException.dwHandleType>> 4) & 0x1;
	m_bAlarmoutEmap = (m_struChanFilterCfg.struHandleException.dwHandleType>> 6) & 0x1;
	m_bPicFtp = (m_struChanFilterCfg.struHandleException.dwHandleType>> 9) & 0x1;
    m_bPicCloud = (m_struChanFilterCfg.struHandleException.dwHandleType >> 12) & 0x1;

	if (m_struChanFilterCfg.byFilterID >0)
	{
		m_comboTheFilterNum.SetCurSel(m_struChanFilterCfg.byFilterID -1);
	}
	else
	{
		m_comboTheFilterNum.SetCurSel(0);
	}
				
	m_cmbFontSize.SetCurSel(m_struChanFilterCfg.byFontSize);
	m_bShowPosInfo = m_struChanFilterCfg.byShowPosInfo ;
	m_cmbOverlayMode.SetCurSel(m_struChanFilterCfg.byOverlayMode);
	
	m_wDelayTime =	m_struChanFilterCfg.dwDelayTime;
    m_dwTimeOut = m_struChanFilterCfg.dwTimeOut;
	m_byColorR = m_struChanFilterCfg.struOsdColor.byRed;
	m_byColorG = m_struChanFilterCfg.struOsdColor.byGreen;
	m_byColorB = m_struChanFilterCfg.struOsdColor.byBlue;

	
	m_fReginX = m_struChanFilterCfg.struOsdPosInfo.struStart.fX;
	m_fRegionY = m_struChanFilterCfg.struOsdPosInfo.struStart.fY;
	
	m_fRegionLenth = m_struChanFilterCfg.struOsdPosInfo.struEnd.fX;
	m_fRegionWight = m_struChanFilterCfg.struOsdPosInfo.struEnd.fY;

    for (int i = 0; i < m_struChanFilterCfg.struHandleException.dwRelAlarmOutChanNum; i++)
    {
        m_pbAlarmOut[m_struChanFilterCfg.struHandleException.dwRelAlarmOut[i] - 1] = 1;
    }
    HTREEITEM hTreeItem;
    CTreeCtrl *treeCtr = &m_treeAlarmOut;
    DWORD dwCount = m_treeAlarmOut.GetCount();
    hTreeItem = m_treeAlarmOut.GetRootItem();
    for (int i = 0; i < dwCount; i++)
    {
        treeCtr->SetCheck(hTreeItem, m_pbAlarmOut[i]);
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
    }

    for (int i = 0; i < m_struChanFilterCfg.dwRelRecordChanNum; i++)
    {
        m_pbRecordChan[m_struChanFilterCfg.dwRelRecordChan[i] - 1] = 1;
    }
    treeCtr = &m_treeChan;
    dwCount = m_treeChan.GetCount();
    hTreeItem = m_treeChan.GetRootItem();
    for (int i = 0; i < dwCount; i++)
    {
        treeCtr->SetCheck(hTreeItem, m_pbRecordChan[i]);
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
     }

	UpdateData(FALSE);
}

void CDlgPosChanFilter::OnSelchangeComboMotionWeekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	i = m_cmbWeekDay.GetCurSel();	
	
    if (i == 7)     // 7代表假日 需要单独获取
    {
       /* m_dwHour11 = m_struChanFilterCfg.struAlarmSched[0].byStartHour;
        m_dwMin11 = m_struChanFilterCfg.struAlarmSched[0].byStartMin;
        m_dwHour12 = m_struChanFilterCfg.struAlarmSched[0].byStopHour;
        m_dwMin12 = m_struChanFilterCfg.struAlarmSched[0].byStopMin;
        m_dwHour21 = m_struChanFilterCfg.struAlarmSched[1].byStartHour;
        m_dwMin21 = m_struChanFilterCfg.struAlarmSched[1].byStartMin;
        m_dwHour22 = m_struChanFilterCfg.struAlarmSched[1].byStopHour;
        m_dwMin22 = m_struChanFilterCfg.struAlarmSched[1].byStopMin;
        m_dwHour31 = m_struChanFilterCfg.struAlarmSched[2].byStartHour;
        m_dwMin31 = m_struChanFilterCfg.struAlarmSched[2].byStartMin;
        m_dwHour32 = m_struChanFilterCfg.struAlarmSched[2].byStopHour;
        m_dwMin32 = m_struChanFilterCfg.struAlarmSched[2].byStopMin;
        m_dwHour41 = m_struChanFilterCfg.struAlarmSched[3].byStartHour;
        m_dwMin41 = m_struChanFilterCfg.struAlarmSched[3].byStartMin;
        m_dwHour42 = m_struChanFilterCfg.struAlarmSched[3].byStopHour;
        m_dwMin42 = m_struChanFilterCfg.struAlarmSched[3].byStopMin;
        m_dwHour51 = m_struChanFilterCfg.struAlarmSched[4].byStartHour;
        m_dwMin51 = m_struChanFilterCfg.struAlarmSched[4].byStartMin;
        m_dwHour52 = m_struChanFilterCfg.struAlarmSched[4].byStopHour;
        m_dwMin52 = m_struChanFilterCfg.struAlarmSched[4].byStopMin;
        m_dwHour61 = m_struChanFilterCfg.struAlarmSched[5].byStartHour;
        m_dwMin61 = m_struChanFilterCfg.struAlarmSched[5].byStartMin;
        m_dwHour62 = m_struChanFilterCfg.struAlarmSched[5].byStopHour;
        m_dwMin62 = m_struChanFilterCfg.struAlarmSched[5].byStopMin;
        m_dwHour71 = m_struChanFilterCfg.struAlarmSched[6].byStartHour;
        m_dwMin71 = m_struChanFilterCfg.struAlarmSched[6].byStartMin;
        m_dwHour72 = m_struChanFilterCfg.struAlarmSched[6].byStopHour;
        m_dwMin72 = m_struChanFilterCfg.struAlarmSched[6].byStopMin;
        m_dwHour81 = m_struChanFilterCfg.struAlarmSched[7].byStartHour;
        m_dwMin81 = m_struChanFilterCfg.struAlarmSched[7].byStartMin;
        m_dwHour82 = m_struChanFilterCfg.struAlarmSched[7].byStopHour;
        m_dwMin82 = m_struChanFilterCfg.struAlarmSched[7].byStopMin;
		*/
    }
    else
    {
		m_dwHour11 = m_struChanFilterCfg.struAlarmSched[i][0].byStartHour;
        m_dwMin11 = m_struChanFilterCfg.struAlarmSched[i][0].byStartMin;
        m_dwHour12 = m_struChanFilterCfg.struAlarmSched[i][0].byStopHour;
        m_dwMin12 = m_struChanFilterCfg.struAlarmSched[i][0].byStopMin;
        m_dwHour21 = m_struChanFilterCfg.struAlarmSched[i][1].byStartHour;
        m_dwMin21 = m_struChanFilterCfg.struAlarmSched[i][1].byStartMin;
        m_dwHour22 = m_struChanFilterCfg.struAlarmSched[i][1].byStopHour;
        m_dwMin22 = m_struChanFilterCfg.struAlarmSched[i][1].byStopMin;
        m_dwHour31 = m_struChanFilterCfg.struAlarmSched[i][2].byStartHour;
        m_dwMin31 = m_struChanFilterCfg.struAlarmSched[i][2].byStartMin;
        m_dwHour32 = m_struChanFilterCfg.struAlarmSched[i][2].byStopHour;
        m_dwMin32 = m_struChanFilterCfg.struAlarmSched[i][2].byStopMin;
        m_dwHour41 = m_struChanFilterCfg.struAlarmSched[i][3].byStartHour;
        m_dwMin41 = m_struChanFilterCfg.struAlarmSched[i][3].byStartMin;
        m_dwHour42 = m_struChanFilterCfg.struAlarmSched[i][3].byStopHour;
        m_dwMin42 = m_struChanFilterCfg.struAlarmSched[i][3].byStopMin;
        m_dwHour51 = m_struChanFilterCfg.struAlarmSched[i][4].byStartHour;
        m_dwMin51 = m_struChanFilterCfg.struAlarmSched[i][4].byStartMin;
        m_dwHour52 = m_struChanFilterCfg.struAlarmSched[i][4].byStopHour;
        m_dwMin52 = m_struChanFilterCfg.struAlarmSched[i][4].byStopMin;
        m_dwHour61 = m_struChanFilterCfg.struAlarmSched[i][5].byStartHour;
        m_dwMin61 = m_struChanFilterCfg.struAlarmSched[i][5].byStartMin;
        m_dwHour62 = m_struChanFilterCfg.struAlarmSched[i][5].byStopHour;
        m_dwMin62 = m_struChanFilterCfg.struAlarmSched[i][5].byStopMin;
        m_dwHour71 = m_struChanFilterCfg.struAlarmSched[i][6].byStartHour;
        m_dwMin71 = m_struChanFilterCfg.struAlarmSched[i][6].byStartMin;
        m_dwHour72 = m_struChanFilterCfg.struAlarmSched[i][6].byStopHour;
        m_dwMin72 = m_struChanFilterCfg.struAlarmSched[i][6].byStopMin;
        m_dwHour81 = m_struChanFilterCfg.struAlarmSched[i][7].byStartHour;
        m_dwMin81 = m_struChanFilterCfg.struAlarmSched[i][7].byStartMin;
        m_dwHour82 = m_struChanFilterCfg.struAlarmSched[i][7].byStopHour;
        m_dwMin82 = m_struChanFilterCfg.struAlarmSched[i][7].byStopMin;
    }
	UpdateData(FALSE);
}

void CDlgPosChanFilter::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
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
	m_pbAlarmOut[dwIndex] = !bCheck;
	
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

void CDlgPosChanFilter::OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_CHAN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeChan.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeChan.SelectItem(hSelect);
	DWORD dwIndex = m_treeChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeChan.GetCheck(hSelect);
	m_pbRecordChan[dwIndex] = !bCheck;
	//
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeChan.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeChan.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

/*********************************************************
  Function:	TimeTest
  Desc:		time detection
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgPosChanFilter::TimeTest()
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

void CDlgPosChanFilter::OnMotionDayOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	
	int	i = m_cmbWeekDay.GetCurSel();	
    if (7 == i)
    {
       /* m_struHolidayHandle.struAlarmTime[0].byStartHour = (BYTE)m_dwHour11;
        m_struHolidayHandle.struAlarmTime[0].byStartMin = (BYTE)m_dwMin11;
        m_struHolidayHandle.struAlarmTime[0].byStopHour = (BYTE)m_dwHour12;
        m_struHolidayHandle.struAlarmTime[0].byStopMin = (BYTE)m_dwMin12;
        m_struHolidayHandle.struAlarmTime[1].byStartHour = (BYTE)m_dwHour21;
        m_struHolidayHandle.struAlarmTime[1].byStartMin = (BYTE)m_dwMin21;
        m_struHolidayHandle.struAlarmTime[1].byStopHour = (BYTE)m_dwHour22;
        m_struHolidayHandle.struAlarmTime[1].byStopMin = (BYTE)m_dwMin22;
        m_struHolidayHandle.struAlarmTime[2].byStartHour = (BYTE)m_dwHour31;
        m_struHolidayHandle.struAlarmTime[2].byStartMin = (BYTE)m_dwMin31;
        m_struHolidayHandle.struAlarmTime[2].byStopHour = (BYTE)m_dwHour32;
        m_struHolidayHandle.struAlarmTime[2].byStopMin = (BYTE)m_dwMin32;
        m_struHolidayHandle.struAlarmTime[3].byStartHour = (BYTE)m_dwHour41;
        m_struHolidayHandle.struAlarmTime[3].byStartMin = (BYTE)m_dwMin41;
        m_struHolidayHandle.struAlarmTime[3].byStopHour = (BYTE)m_dwHour42;
        m_struHolidayHandle.struAlarmTime[3].byStopMin = (BYTE)m_dwMin42;
        m_struHolidayHandle.struAlarmTime[4].byStartHour = (BYTE)m_dwHour51;
        m_struHolidayHandle.struAlarmTime[4].byStartMin = (BYTE)m_dwMin51;
        m_struHolidayHandle.struAlarmTime[4].byStopHour = (BYTE)m_dwHour52;
        m_struHolidayHandle.struAlarmTime[4].byStopMin = (BYTE)m_dwMin52;
        m_struHolidayHandle.struAlarmTime[5].byStartHour = (BYTE)m_dwHour61;
        m_struHolidayHandle.struAlarmTime[5].byStartMin = (BYTE)m_dwMin61;
        m_struHolidayHandle.struAlarmTime[5].byStopHour = (BYTE)m_dwHour62;
        m_struHolidayHandle.struAlarmTime[5].byStopMin = (BYTE)m_dwMin62;
        m_struHolidayHandle.struAlarmTime[6].byStartHour = (BYTE)m_dwHour71;
        m_struHolidayHandle.struAlarmTime[6].byStartMin = (BYTE)m_dwMin71;
        m_struHolidayHandle.struAlarmTime[6].byStopHour = (BYTE)m_dwHour72;
        m_struHolidayHandle.struAlarmTime[6].byStopMin = (BYTE)m_dwMin72;
        m_struHolidayHandle.struAlarmTime[7].byStartHour = (BYTE)m_dwHour81;
        m_struHolidayHandle.struAlarmTime[7].byStartMin = (BYTE)m_dwMin81;
        m_struHolidayHandle.struAlarmTime[7].byStopHour = (BYTE)m_dwHour82;
        m_struHolidayHandle.struAlarmTime[7].byStopMin = (BYTE)m_dwMin82;
		
        if (!SetAlarmInHolidayHandle(m_struHolidayHandle))
        {
            AfxMessageBox("Fail to set holiday handle");
        }
		*/
    }
    else
    {
		
        m_struChanFilterCfg.struAlarmSched[i][0].byStartHour = (BYTE)m_dwHour11;
        m_struChanFilterCfg.struAlarmSched[i][0].byStartMin = (BYTE)m_dwMin11;
        m_struChanFilterCfg.struAlarmSched[i][0].byStopHour = (BYTE)m_dwHour12;
        m_struChanFilterCfg.struAlarmSched[i][0].byStopMin = (BYTE)m_dwMin12;
        m_struChanFilterCfg.struAlarmSched[i][1].byStartHour = (BYTE)m_dwHour21;
        m_struChanFilterCfg.struAlarmSched[i][1].byStartMin = (BYTE)m_dwMin21;
        m_struChanFilterCfg.struAlarmSched[i][1].byStopHour = (BYTE)m_dwHour22;
        m_struChanFilterCfg.struAlarmSched[i][1].byStopMin = (BYTE)m_dwMin22;
        m_struChanFilterCfg.struAlarmSched[i][2].byStartHour = (BYTE)m_dwHour31;
        m_struChanFilterCfg.struAlarmSched[i][2].byStartMin = (BYTE)m_dwMin31;
        m_struChanFilterCfg.struAlarmSched[i][2].byStopHour = (BYTE)m_dwHour32;
        m_struChanFilterCfg.struAlarmSched[i][2].byStopMin = (BYTE)m_dwMin32;
        m_struChanFilterCfg.struAlarmSched[i][3].byStartHour = (BYTE)m_dwHour41;
        m_struChanFilterCfg.struAlarmSched[i][3].byStartMin = (BYTE)m_dwMin41;
        m_struChanFilterCfg.struAlarmSched[i][3].byStopHour = (BYTE)m_dwHour42;
        m_struChanFilterCfg.struAlarmSched[i][3].byStopMin = (BYTE)m_dwMin42;
        m_struChanFilterCfg.struAlarmSched[i][4].byStartHour = (BYTE)m_dwHour51;
        m_struChanFilterCfg.struAlarmSched[i][4].byStartMin = (BYTE)m_dwMin51;
        m_struChanFilterCfg.struAlarmSched[i][4].byStopHour = (BYTE)m_dwHour52;
        m_struChanFilterCfg.struAlarmSched[i][4].byStopMin = (BYTE)m_dwMin52;
        m_struChanFilterCfg.struAlarmSched[i][5].byStartHour = (BYTE)m_dwHour61;
        m_struChanFilterCfg.struAlarmSched[i][5].byStartMin = (BYTE)m_dwMin61;
        m_struChanFilterCfg.struAlarmSched[i][5].byStopHour = (BYTE)m_dwHour62;
        m_struChanFilterCfg.struAlarmSched[i][5].byStopMin = (BYTE)m_dwMin62;
        m_struChanFilterCfg.struAlarmSched[i][6].byStartHour = (BYTE)m_dwHour71;
        m_struChanFilterCfg.struAlarmSched[i][6].byStartMin = (BYTE)m_dwMin71;
        m_struChanFilterCfg.struAlarmSched[i][6].byStopHour = (BYTE)m_dwHour72;
        m_struChanFilterCfg.struAlarmSched[i][6].byStopMin = (BYTE)m_dwMin72;
        m_struChanFilterCfg.struAlarmSched[i][7].byStartHour = (BYTE)m_dwHour81;
        m_struChanFilterCfg.struAlarmSched[i][7].byStartMin = (BYTE)m_dwMin81;
        m_struChanFilterCfg.struAlarmSched[i][7].byStopHour = (BYTE)m_dwHour82;
        m_struChanFilterCfg.struAlarmSched[i][7].byStopMin = (BYTE)m_dwMin82;
    }
}
