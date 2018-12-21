// DlgVCADetionCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVCADetionCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgVCADetionCfg dialog


DlgVCADetionCfg::DlgVCADetionCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVCADetionCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgVCADetionCfg)
	m_ChannelNo = 0;
	m_CuriseNo = 0;
	m_bEnable = FALSE;
	m_bEnableCurise = FALSE;
	m_bEnablePreset = 0;
	m_bEnablePTZTrack = FALSE;
	m_GroupNo = 0;
	m_MaxRelAlarmOutChanNum = 0;
	m_MaxRelRecordChanNum = 0;
	m_PTZTrack = 0;
	m_RelAlarmOutChanNum = 0;
	m_RelRecordChanNum = 0;
	m_Preset = 0;
	m_bMintorAlarm = FALSE;
	m_bNoResponse = FALSE;
	m_bUpCenter = FALSE;
	m_bVoiceAlarm = FALSE;
	m_bWirelessAlarm = FALSE;
	m_bLinkageMap = FALSE;
	m_bJpegCapture = FALSE;
	m_bAlarmOut = FALSE;
	m_bCaptureUploadFTP = FALSE;
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
	m_Num = 0;
	//}}AFX_DATA_INIT
	memset(&m_dwAlarmOut, 0 , sizeof(m_dwAlarmOut));
	m_GetStru = FALSE;
    	m_struChannelGroup.reserve(0);
}


void DlgVCADetionCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgVCADetionCfg)
	DDX_Control(pDX, IDC_TREE_CHAN, m_treeChan);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COM_COUNT, m_comCount);
	DDX_Control(pDX, IDC_COM_MAX_DAY, m_comMaxDay);
	DDX_Control(pDX, IDC_COM_CHAN_NO, m_comChanNo);
	DDX_Text(pDX, IDC_CHANNEL_NO, m_ChannelNo);
	DDX_Text(pDX, IDC_CURISE_NO, m_CuriseNo);
	DDX_Check(pDX, IDC_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_ENABLE_CURISE, m_bEnableCurise);
	DDX_Check(pDX, IDC_ENABLE_PRESET, m_bEnablePreset);
	DDX_Check(pDX, IDC_ENABLE_PTZ_TRACK, m_bEnablePTZTrack);
	DDX_Text(pDX, IDC_GROUP_NO, m_GroupNo);
	DDX_Text(pDX, IDC_MAX_REL_ALARM_OUT_CHAN_NUM, m_MaxRelAlarmOutChanNum);
	DDX_Text(pDX, IDC_MAX_REL_RECORD_CHAN_NUM, m_MaxRelRecordChanNum);
	DDX_Text(pDX, IDC_PTZ_TRACK, m_PTZTrack);
	DDX_Text(pDX, IDC_REL_ALARM_OUT_CHAN_NUM, m_RelAlarmOutChanNum);
	DDX_Text(pDX, IDC_REL_RECORD_CHAN_NUM, m_RelRecordChanNum);
	DDX_Text(pDX, IDC_PRESET, m_Preset);
	DDX_Check(pDX, IDC_MONITOR_ALARM, m_bMintorAlarm);
	DDX_Check(pDX, IDC_NO_RESPONSE, m_bNoResponse);
	DDX_Check(pDX, IDC_UP_CENTER, m_bUpCenter);
	DDX_Check(pDX, IDC_VOICE_ALARM, m_bVoiceAlarm);
	DDX_Check(pDX, IDC_WIRELESS_ALARM, m_bWirelessAlarm);
	DDX_Check(pDX, IDC_lINKAGE_MAP, m_bLinkageMap);
	DDX_Check(pDX, IDC_JPEG_CAPTURE, m_bJpegCapture);
	DDX_Check(pDX, IDC_ALARM_OUT, m_bAlarmOut);
	DDX_Check(pDX, IDC_CAPTURE_UPLOAD_FTP, m_bCaptureUploadFTP);
	DDX_Text(pDX, IDC_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_MIN82, m_iMin82);
	DDX_Text(pDX, IDC_NUM, m_Num);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgVCADetionCfg, CDialog)
	//{{AFX_MSG_MAP(DlgVCADetionCfg)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_GET, OnGet)
	ON_BN_CLICKED(IDC_ENABLE_CURISE, OnEnableCurise)
	ON_BN_CLICKED(IDC_ENABLE_PTZ_TRACK, OnEnablePtzTrack)
	ON_EN_CHANGE(IDC_CURISE_NO, OnChangeCuriseNo)
	ON_EN_CHANGE(IDC_PTZ_TRACK, OnChangePtzTrack)
	ON_BN_CLICKED(IDC_ENABLE, OnEnable)
	ON_EN_CHANGE(IDC_MAX_REL_ALARM_OUT_CHAN_NUM, OnChangeMaxRelAlarmOutChanNum)
	ON_EN_CHANGE(IDC_REL_ALARM_OUT_CHAN_NUM, OnChangeRelAlarmOutChanNum)
	ON_EN_CHANGE(IDC_MAX_REL_RECORD_CHAN_NUM, OnChangeMaxRelRecordChanNum)
	ON_EN_CHANGE(IDC_REL_RECORD_CHAN_NUM, OnChangeRelRecordChanNum)
	ON_EN_CHANGE(IDC_CHANNEL_NO, OnChangeChannelNo)
	ON_EN_CHANGE(IDC_GROUP_NO, OnChangeGroupNo)
	ON_CBN_SELCHANGE(IDC_COM_COUNT, OnSelchangeComCount)
	ON_CBN_SELCHANGE(IDC_COM_MAX_DAY, OnSelchangeComMaxDay)
	ON_CBN_SELCHANGE(IDC_COM_CHAN_NO, OnSelchangeComChanNo)
	ON_BN_CLICKED(IDC_ENABLE_PRESET, OnEnablePreset)
	ON_EN_CHANGE(IDC_PRESET, OnChangePreset)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAN, OnClickTreeChan)
	ON_BN_CLICKED(IDC_BTN_EXCEPTIONOK, OnBtnExceptionok)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgVCADetionCfg message handlers
BOOL DlgVCADetionCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ChannelNo = 0;
	UpdateData(FALSE);
	return TRUE;
}

void DlgVCADetionCfg::OnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
    }
    
//     if (m_struChannelGroup.empty())
//     {
//         AfxMessageBox("请先输入个数，点确认");
//         return;
//     }

	if(!m_comCount.GetCount())
	{
		AfxMessageBox("请先配置条件");
		return;
	}
	for (int count = 0; count < m_Num; count++)
	{
		vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
		while(count > 0)
		{
			it++;
			count--;
		}
		m_struChannelGroup[m_comCount.GetCurSel()].dwSize = sizeof(m_struChannelGroup);
		m_struChannelGroup[m_comCount.GetCurSel()].dwChannel = m_ChannelNo;
		m_struChannelGroup[m_comCount.GetCurSel()].dwGroup = m_GroupNo;
		it->dwSize = sizeof(m_struVcaDetionCfg);
		it->dwMaxRelRecordChanNum = m_MaxRelRecordChanNum;
		it->dwRelRecordChanNum = m_RelRecordChanNum;
		it->struHandleException.dwMaxRelAlarmOutChanNum = m_MaxRelAlarmOutChanNum;
		it->struHandleException.dwRelAlarmOutChanNum = m_RelAlarmOutChanNum;
		it->byEnable = m_bEnable;
		if (m_bNoResponse)
		{
			it->struHandleException.dwHandleType = 0;
		}
		
		for (int i = 0; i < m_Num; i++)
		{
			m_struVcaDetionCfg[i].dwSize = sizeof(NET_DVR_VCA_DETION_CFG);
			m_struChannelGroup[i].dwSize = sizeof(NET_DVR_CHANNEL_GROUP);
		}
	}
	
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	DWORD dwStatus[1024] = {0};
	char szLan[128] = {0};
    char szLanCn[128] = {0};
    char szLanEn[128] = {0};
    BOOL  bRet = NET_DVR_SetDeviceConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_SET_VCA_DETION_CFG,m_Num,&m_struChannelGroup[0],m_Num*sizeof(NET_DVR_CHANNEL_GROUP),&dwStatus,&m_struVcaDetionCfg[0],m_Num*sizeof(NET_DVR_VCA_DETION_CFG));
	if(!bRet)
	{
		g_pMainDlg->AddLog(dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_DETION_CFG,  %s", "Set vca detion config faild");
		g_StringLanType(szLan, "参数保存失败", "Set vca detion config failed");
		AfxMessageBox(szLan);
		//return FALSE;
	}
	else
	{
        for (int i = 0; i < m_Num; i++)
        {
            if (dwStatus[i] != 0)
            {
                sprintf(szLanCn,"通道[%d]获取参数失败,错误码[%d]",  m_struChannelGroup[i].dwChannel, dwStatus[i]);
                sprintf(szLanEn,"channel[%d]Set vca detion config failed Err[%d]",  m_struChannelGroup[i].dwChannel, dwStatus[i]);

                g_StringLanType(szLan, szLanCn, szLanEn);
                AfxMessageBox(szLan);
            } 
        }

		g_pMainDlg->AddLog(dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_DETION_CFG %s", "Set vca detion config succeed");
	}
}

void DlgVCADetionCfg::OnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
	}

	if(!m_comCount.GetCount())
	{
		AfxMessageBox("请先配置条件");
		return;
	}
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	DWORD dwStatus[128] = {0};
    char szLan[128] = {0};
    char szLanCn[128] = {0};
    char szLanEn[128] = {0};
	for (int i = 0; i < m_Num; i++)
	{
		m_struChannelGroup[i].dwSize = sizeof(NET_DVR_CHANNEL_GROUP);
	}
	
    BOOL  bRet = NET_DVR_GetDeviceConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_GET_VCA_DETION_CFG,m_Num,&m_struChannelGroup[0],\
        m_Num*sizeof(NET_DVR_CHANNEL_GROUP),&dwStatus,&m_struVcaDetionCfg[0],m_Num*sizeof(NET_DVR_VCA_DETION_CFG));
	if(!bRet)
	{
		g_pMainDlg->AddLog(dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_DETION_CFG,  %s", "Get vca detion config faild");
		g_StringLanType(szLan, "获取参数失败", "Get vca detion config failed");
		AfxMessageBox(szLan);
		return;
	}
	else 
	{
        for (int i = 0; i < m_Num; i++)
        {
            if (dwStatus[i] != 0)
            {
                sprintf(szLanCn,"通道[%d]获取参数失败,错误码[%d]",  m_struChannelGroup[i].dwChannel, dwStatus[i]);
                sprintf(szLanEn,"channel[%d]Get vca detion config failed Err[%d]",  m_struChannelGroup[i].dwChannel, dwStatus[i]);
                
                g_StringLanType(szLan, szLanCn, szLanEn);
                AfxMessageBox(szLan);
            }
            
        }
		m_GetStru = TRUE;
		g_pMainDlg->AddLog(dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_DETION_CFG %s", "Get vca detion config succeed");
	}
	OnSelchangeComCount();
}

void DlgVCADetionCfg::OnEnableCurise() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_bEnableCurise = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	GetDlgItem(IDC_CURISE_NO)->EnableWindow(TRUE);
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	m_bEnablePreset = FALSE;
	m_bEnablePTZTrack = FALSE;
	it->byPresetNo[m_comChanNo.GetCurSel()] = 0;
	it->byPTZTrack[m_comChanNo.GetCurSel()] = 0;
	it->byEnablePreset[m_comChanNo.GetCurSel()] = 0;
	it->byEnablePtzTrack[m_comChanNo.GetCurSel()] = 0;
	m_PTZTrack = 0;
	m_Preset = 0;
	char szLan[128] = {0};
	if (m_comChanNo.GetCurSel() == -1||m_comCount.GetCurSel() == -1)
	{
		g_StringLanType(szLan, "请先选择通道号","select channel no first");
		AfxMessageBox(szLan);
		return;
	}
	it->byEnableCruise[m_comChanNo.GetCurSel()] = m_bEnableCurise;
	GetDlgItem(IDC_PRESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_PTZ_TRACK)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void DlgVCADetionCfg::OnEnablePtzTrack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_bEnablePTZTrack = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	GetDlgItem(IDC_PTZ_TRACK)->EnableWindow(TRUE);
	m_bEnablePreset = FALSE;
	m_bEnableCurise = FALSE;
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	it->byPresetNo[m_comChanNo.GetCurSel()] = 0;
	it->byCruiseNo[m_comChanNo.GetCurSel()] = 0;
	it->byEnableCruise[m_comChanNo.GetCurSel()] = 0;
	it->byEnablePreset[m_comChanNo.GetCurSel()] = 0;
	m_CuriseNo = 0;
	m_Preset = 0;
	char szLan[128] = {0};
	if (m_comChanNo.GetCurSel() == -1||m_comCount.GetCurSel() == -1)
	{
		g_StringLanType(szLan, "请先选择通道号","select channel no first");
		AfxMessageBox(szLan);
		return;
	}
	it->byEnablePtzTrack[m_comChanNo.GetCurSel()] = m_bEnablePTZTrack;
	GetDlgItem(IDC_PRESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_CURISE_NO)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void DlgVCADetionCfg::OnChangeCuriseNo() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_CuriseNo = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comChanNo.GetCurSel() == -1||m_comCount.GetCurSel() == -1)
	{
		return;
	}
	if (!m_bEnableCurise)
	{
		return;
	}
	it->byCruiseNo[m_comChanNo.GetCurSel()] = m_CuriseNo;
}

void DlgVCADetionCfg::OnChangePtzTrack() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_PTZTrack = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comChanNo.GetCurSel() == -1||m_comCount.GetCurSel() == -1)
	{
		return;
	}
	it->byPTZTrack[m_comChanNo.GetCurSel()] = m_PTZTrack;
}


void DlgVCADetionCfg::OnEnable() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_bEnable = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comCount.GetCurSel() == -1)
	{
		return;
	}
	it->byEnable = m_bEnable;
}

void DlgVCADetionCfg::OnChangeMaxRelAlarmOutChanNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_MaxRelAlarmOutChanNum = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comCount.GetCurSel() == -1)
	{
		return;
	}
	it->struHandleException.dwMaxRelAlarmOutChanNum = m_MaxRelAlarmOutChanNum;
}

void DlgVCADetionCfg::OnChangeRelAlarmOutChanNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_RelAlarmOutChanNum = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comCount.GetCurSel() == -1)
	{
		return;
	}
	it->struHandleException.dwRelAlarmOutChanNum = m_RelAlarmOutChanNum;
}

void DlgVCADetionCfg::OnChangeMaxRelRecordChanNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_MaxRelRecordChanNum = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comCount.GetCurSel() == -1)
	{
		return;
	}
	it->dwMaxRelRecordChanNum = m_MaxRelRecordChanNum;
}

void DlgVCADetionCfg::OnChangeRelRecordChanNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_RelRecordChanNum = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comCount.GetCurSel() == -1)
	{
		return;
	}
	it->dwRelRecordChanNum = m_RelRecordChanNum;
}

void DlgVCADetionCfg::OnChangeChannelNo() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_ChannelNo = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comCount.GetCurSel() == -1)
	{
		return;
	}
	m_struChannelGroup[m_comCount.GetCurSel()].dwChannel = m_ChannelNo;
}

void DlgVCADetionCfg::OnChangeGroupNo() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_GroupNo = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comCount.GetCurSel() == -1)
	{
		return;
	}
	m_struChannelGroup[m_comCount.GetCurSel()].dwGroup = m_GroupNo;
}

void DlgVCADetionCfg::OnSelchangeComCount() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_comCount.SetCurSel(-1);
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int i = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	int count = 0;
	while(count < i)
	{
		it++;
		count++;
		//i--;
	}
	m_bEnable = it->byEnable;
	m_ChannelNo = m_struChannelGroup[count].dwChannel;
	m_GroupNo = m_struChannelGroup[count].dwGroup;

	m_MaxRelAlarmOutChanNum = it->struHandleException.dwMaxRelAlarmOutChanNum;
	m_bNoResponse = (it->struHandleException.dwHandleType == 0)?1:0;
	m_bMintorAlarm = it->struHandleException.dwHandleType&0x01;
	m_bVoiceAlarm = (it->struHandleException.dwHandleType >> 1)&0x01;
	m_bUpCenter = (it->struHandleException.dwHandleType >> 2)&0x01;
	m_bAlarmOut = (it->struHandleException.dwHandleType >> 3)&0x01;
	m_bCaptureUploadFTP = (it->struHandleException.dwHandleType >> 4)&0x01;
	m_bWirelessAlarm = (it->struHandleException.dwHandleType >> 5)&0x01;
	m_bLinkageMap = (it->struHandleException.dwHandleType >> 6)&0x01;
	m_bJpegCapture = (it->struHandleException.dwHandleType >> 9)&0x01;
	m_RelAlarmOutChanNum = it->struHandleException.dwRelAlarmOutChanNum;
	UpdateData(FALSE);
	m_comMaxDay.SetCurSel(0);
	OnSelchangeComMaxDay();

	m_MaxRelRecordChanNum = it->dwMaxRelRecordChanNum;
	m_RelRecordChanNum = it->dwRelRecordChanNum;
	
	m_bEnablePreset = it->byEnablePreset[0];
	m_Preset = it->byPresetNo[0];
	m_PTZTrack = it->byPTZTrack[0];
	m_bEnablePTZTrack = it->byEnablePtzTrack[0];
	m_bEnableCurise = it->byEnableCruise[0];
	m_CuriseNo = it->byCruiseNo[0];
	if (m_bEnablePTZTrack)
	{
		GetDlgItem(IDC_CURISE_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_PRESET)->EnableWindow(FALSE);
	}
	else if (m_bEnableCurise)
	{
		GetDlgItem(IDC_PTZ_TRACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_PRESET)->EnableWindow(FALSE);
	}
	else if (m_bEnablePreset)
	{
		GetDlgItem(IDC_CURISE_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_PTZ_TRACK)->EnableWindow(FALSE);
	}
	else;
	UpdateData(FALSE);
	m_comChanNo.SetCurSel(0);
	UpdateData(FALSE);
	for (i=0;i<MAX_CHANNUM_V30;i++)
	{
		m_dwAlarmOut[i] = m_struVcaDetionCfg[m_comCount.GetCurSel()].struHandleException.dwRelAlarmOut[i];
	}
	CreateTree();
	UpdateData(FALSE);
}

void DlgVCADetionCfg::OnSelchangeComMaxDay() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_comMaxDay.SetCurSel(-1);
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int i = m_comMaxDay.GetCurSel();
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
    if (i != 7)  //非假日
    {
        m_iHour11 = it->struAlarmSched[i][0].byStartHour;
        m_iMin11 = it->struAlarmSched[i][0].byStartMin;
        m_iHour12 = it->struAlarmSched[i][0].byStopHour;
        m_iMin12 = it->struAlarmSched[i][0].byStopMin;
        m_iHour21 = it->struAlarmSched[i][1].byStartHour;
        m_iMin21 = it->struAlarmSched[i][1].byStartMin;
        m_iHour22 = it->struAlarmSched[i][1].byStopHour;
        m_iMin22 = it->struAlarmSched[i][1].byStopMin;
        m_iHour31 = it->struAlarmSched[i][2].byStartHour;
        m_iMin31 = it->struAlarmSched[i][2].byStartMin;
        m_iHour32 = it->struAlarmSched[i][2].byStopHour;
        m_iMin32 = it->struAlarmSched[i][2].byStopMin;
        m_iHour41 = it->struAlarmSched[i][3].byStartHour;
        m_iMin41 = it->struAlarmSched[i][3].byStartMin;
        m_iHour42 = it->struAlarmSched[i][3].byStopHour;
        m_iMin42 = it->struAlarmSched[i][3].byStopMin;
        m_iHour51 = it->struAlarmSched[i][4].byStartHour;
        m_iMin51 = it->struAlarmSched[i][4].byStartMin;
        m_iHour52 = it->struAlarmSched[i][4].byStopHour;
        m_iMin52 = it->struAlarmSched[i][4].byStopMin;
        m_iHour61 = it->struAlarmSched[i][5].byStartHour;
        m_iMin61 = it->struAlarmSched[i][5].byStartMin;
        m_iHour62 = it->struAlarmSched[i][5].byStopHour;
        m_iMin62 = it->struAlarmSched[i][5].byStopMin;
        m_iHour71 = it->struAlarmSched[i][6].byStartHour;
        m_iMin71 = it->struAlarmSched[i][6].byStartMin;
        m_iHour72 = it->struAlarmSched[i][6].byStopHour;
        m_iMin72 = it->struAlarmSched[i][6].byStopMin;
        m_iHour81 = it->struAlarmSched[i][7].byStartHour;
        m_iMin81 = it->struAlarmSched[i][7].byStartMin;
        m_iHour82 = it->struAlarmSched[i][7].byStopHour;
    m_iMin82 = it->struAlarmSched[i][7].byStopMin;
    }
    else
    {
        m_iHour11 = it->struHolidayTime[0].byStartHour;
        m_iMin11 = it->struHolidayTime[0].byStartMin;
        m_iHour12 = it->struHolidayTime[0].byStopHour;
        m_iMin12 = it->struHolidayTime[0].byStopMin;
        m_iHour21 = it->struHolidayTime[1].byStartHour;
        m_iMin21 = it->struHolidayTime[1].byStartMin;
        m_iHour22 = it->struHolidayTime[1].byStopHour;
        m_iMin22 = it->struHolidayTime[1].byStopMin;
        m_iHour31 = it->struHolidayTime[2].byStartHour;
        m_iMin31 = it->struHolidayTime[2].byStartMin;
        m_iHour32 = it->struHolidayTime[2].byStopHour;
        m_iMin32 = it->struHolidayTime[2].byStopMin;
        m_iHour41 = it->struHolidayTime[3].byStartHour;
        m_iMin41 = it->struHolidayTime[3].byStartMin;
        m_iHour42 = it->struHolidayTime[3].byStopHour;
        m_iMin42 = it->struHolidayTime[3].byStopMin;
        m_iHour51 = it->struHolidayTime[4].byStartHour;
        m_iMin51 = it->struHolidayTime[4].byStartMin;
        m_iHour52 = it->struHolidayTime[4].byStopHour;
        m_iMin52 = it->struHolidayTime[4].byStopMin;
        m_iHour61 = it->struHolidayTime[5].byStartHour;
        m_iMin61 = it->struHolidayTime[5].byStartMin;
        m_iHour62 = it->struHolidayTime[5].byStopHour;
        m_iMin62 = it->struHolidayTime[5].byStopMin;
        m_iHour71 = it->struHolidayTime[6].byStartHour;
        m_iMin71 = it->struHolidayTime[6].byStartMin;
        m_iHour72 = it->struHolidayTime[6].byStopHour;
        m_iMin72 = it->struHolidayTime[6].byStopMin;
        m_iHour81 = it->struHolidayTime[7].byStartHour;
        m_iMin81 = it->struHolidayTime[7].byStartMin;
        m_iHour82 = it->struHolidayTime[7].byStopHour;
    m_iMin82 = it->struHolidayTime[7].byStopMin;
    }

	UpdateData(FALSE);
}

void DlgVCADetionCfg::OnSelchangeComChanNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	m_RelRecordChanNum = it->dwRelRecordChan[m_comChanNo.GetCurSel()];
	if (it->byEnableCruise[m_comChanNo.GetCurSel()])
	{
		m_CuriseNo = it->byCruiseNo[m_comChanNo.GetCurSel()];
	}
	else if (it->byEnablePtzTrack[m_comChanNo.GetCurSel()])
	{
		m_PTZTrack = it->byPTZTrack[m_comChanNo.GetCurSel()];
	}
	else if (it->byEnablePreset[m_comChanNo.GetCurSel()])
	{
		m_Preset = it->byPresetNo[m_comChanNo.GetCurSel()];
	}
	UpdateData(FALSE);
}

void DlgVCADetionCfg::OnEnablePreset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_bEnablePreset = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	GetDlgItem(IDC_PRESET)->EnableWindow(TRUE);
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	m_bEnableCurise = FALSE;
	m_bEnablePTZTrack = FALSE;
	it->byPTZTrack[m_comChanNo.GetCurSel()] = 0;
	it->byCruiseNo[m_comChanNo.GetCurSel()] = 0;
	it->byEnableCruise[m_comChanNo.GetCurSel()] = 0;
	it->byEnablePtzTrack[m_comChanNo.GetCurSel()] = 0;
	m_PTZTrack = 0;
	m_CuriseNo = 0;
	char szLan[128] = {0};
	if (m_comChanNo.GetCurSel() == -1||m_comCount.GetCurSel() == -1)
	{
		g_StringLanType(szLan, "请先选择通道号","select channel no first");
		AfxMessageBox(szLan);
		return;
	}
	it->byEnablePreset[m_comChanNo.GetCurSel()] = m_bEnablePreset;
	GetDlgItem(IDC_CURISE_NO)->EnableWindow(FALSE);
	GetDlgItem(IDC_PTZ_TRACK)->EnableWindow(FALSE);
	UpdateData(FALSE);
}



void DlgVCADetionCfg::OnChangePreset() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		m_Preset = 0;
		UpdateData(FALSE);
		AfxMessageBox("请先输入个数");
		return;
	}
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
	if (m_comChanNo.GetCurSel() == -1||m_comCount.GetCurSel() == -1)
	{
		return;
	}
	if (!m_bEnablePreset)
	{
		return;
	}
	it->byPresetNo[m_comChanNo.GetCurSel()] = m_Preset;
}

void DlgVCADetionCfg::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
	}
	int	i = m_comMaxDay.GetCurSel();	
	int count = m_comCount.GetCurSel();
	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	while(count > 0)
	{
		it++;
		count--;
	}
    if ( i != 7) //非假日
    {
        it->struAlarmSched[i][0].byStartHour = (BYTE)m_iHour11;
        it->struAlarmSched[i][0].byStartMin = (BYTE)m_iMin11;
        it->struAlarmSched[i][0].byStopHour = (BYTE)m_iHour12;
        it->struAlarmSched[i][0].byStopMin = (BYTE)m_iMin12;
        it->struAlarmSched[i][1].byStartHour = (BYTE)m_iHour21;
        it->struAlarmSched[i][1].byStartMin = (BYTE)m_iMin21;
        it->struAlarmSched[i][1].byStopHour = (BYTE)m_iHour22;
        it->struAlarmSched[i][1].byStopMin = (BYTE)m_iMin22;
        it->struAlarmSched[i][2].byStartHour = (BYTE)m_iHour31;
        it->struAlarmSched[i][2].byStartMin = (BYTE)m_iMin31;
        it->struAlarmSched[i][2].byStopHour = (BYTE)m_iHour32;
        it->struAlarmSched[i][2].byStopMin = (BYTE)m_iMin32;
        it->struAlarmSched[i][3].byStartHour = (BYTE)m_iHour41;
        it->struAlarmSched[i][3].byStartMin = (BYTE)m_iMin41;
        it->struAlarmSched[i][3].byStopHour = (BYTE)m_iHour42;
        it->struAlarmSched[i][3].byStopMin = (BYTE)m_iMin42;
        
        it->struAlarmSched[i][4].byStartHour = (BYTE)m_iHour51;
        it->struAlarmSched[i][4].byStartMin = (BYTE)m_iMin51;
        it->struAlarmSched[i][4].byStopHour = (BYTE)m_iHour52;
        it->struAlarmSched[i][4].byStopMin = (BYTE)m_iMin52;
        it->struAlarmSched[i][5].byStartHour = (BYTE)m_iHour61;
        it->struAlarmSched[i][5].byStartMin = (BYTE)m_iMin61;
        it->struAlarmSched[i][5].byStopHour = (BYTE)m_iHour62;
        it->struAlarmSched[i][5].byStopMin = (BYTE)m_iMin62;
        it->struAlarmSched[i][6].byStartHour = (BYTE)m_iHour71;
        it->struAlarmSched[i][6].byStartMin = (BYTE)m_iMin71;
        it->struAlarmSched[i][6].byStopHour = (BYTE)m_iHour72;
        it->struAlarmSched[i][6].byStopMin = (BYTE)m_iMin72;
        it->struAlarmSched[i][7].byStartHour = (BYTE)m_iHour81;
        it->struAlarmSched[i][7].byStartMin = (BYTE)m_iMin81;
        it->struAlarmSched[i][7].byStopHour = (BYTE)m_iHour82;
    it->struAlarmSched[i][7].byStopMin = (BYTE)m_iMin82;
    }
    else
    {
        it->struHolidayTime[0].byStartHour = (BYTE)m_iHour11;
        it->struHolidayTime[0].byStartMin = (BYTE)m_iMin11;
        it->struHolidayTime[0].byStopHour = (BYTE)m_iHour12;
        it->struHolidayTime[0].byStopMin = (BYTE)m_iMin12;
        it->struHolidayTime[1].byStartHour = (BYTE)m_iHour21;
        it->struHolidayTime[1].byStartMin = (BYTE)m_iMin21;
        it->struHolidayTime[1].byStopHour = (BYTE)m_iHour22;
        it->struHolidayTime[1].byStopMin = (BYTE)m_iMin22;
        it->struHolidayTime[2].byStartHour = (BYTE)m_iHour31;
        it->struHolidayTime[2].byStartMin = (BYTE)m_iMin31;
        it->struHolidayTime[2].byStopHour = (BYTE)m_iHour32;
        it->struHolidayTime[2].byStopMin = (BYTE)m_iMin32;
        it->struHolidayTime[3].byStartHour = (BYTE)m_iHour41;
        it->struHolidayTime[3].byStartMin = (BYTE)m_iMin41;
        it->struHolidayTime[3].byStopHour = (BYTE)m_iHour42;
        it->struHolidayTime[3].byStopMin = (BYTE)m_iMin42;
        
        it->struHolidayTime[4].byStartHour = (BYTE)m_iHour51;
        it->struHolidayTime[4].byStartMin = (BYTE)m_iMin51;
        it->struHolidayTime[4].byStopHour = (BYTE)m_iHour52;
        it->struHolidayTime[4].byStopMin = (BYTE)m_iMin52;
        it->struHolidayTime[5].byStartHour = (BYTE)m_iHour61;
        it->struHolidayTime[5].byStartMin = (BYTE)m_iMin61;
        it->struHolidayTime[5].byStopHour = (BYTE)m_iHour62;
        it->struHolidayTime[5].byStopMin = (BYTE)m_iMin62;
        it->struHolidayTime[6].byStartHour = (BYTE)m_iHour71;
        it->struHolidayTime[6].byStartMin = (BYTE)m_iMin71;
        it->struHolidayTime[6].byStopHour = (BYTE)m_iHour72;
        it->struHolidayTime[6].byStopMin = (BYTE)m_iMin72;
        it->struHolidayTime[7].byStartHour = (BYTE)m_iHour81;
        it->struHolidayTime[7].byStartMin = (BYTE)m_iMin81;
        it->struHolidayTime[7].byStopHour = (BYTE)m_iHour82;
        it->struHolidayTime[7].byStopMin = (BYTE)m_iMin82;
    }
   
}

void DlgVCADetionCfg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
	}
	GetDlgItem(IDC_COM_COUNT)->EnableWindow(TRUE);
	m_comCount.ResetContent();
	CString sTemp;
	int i = 0;
	for (i = 0;i < m_Num;i++)
	{
		sTemp.Format("第%d个配置",i+1);
		m_comCount.AddString(sTemp);
	}
	m_comCount.SetCurSel(0);
	m_struVcaDetionCfg.reserve(m_Num);
	m_struChannelGroup.reserve(m_Num);

	for(i = 0; i < m_Num; i++)
	{
		m_struVcaDetionCfg[i].byEnable = 0;
		m_struVcaDetionCfg[i].dwMaxRelRecordChanNum = 0;
		m_struVcaDetionCfg[i].dwRelRecordChanNum = 0;
		m_struVcaDetionCfg[i].struHandleException.dwHandleType = 0;
		m_struVcaDetionCfg[i].struHandleException.dwMaxRelAlarmOutChanNum = 0;
		m_struVcaDetionCfg[i].struHandleException.dwRelAlarmOutChanNum = 0;
		for (int m = 0; m < MAX_DAYS; m++)
		{
			for (int n = 0; n < MAX_TIMESEGMENT_V30; n++)
			{
				m_struVcaDetionCfg[i].struAlarmSched[m][n].byStartHour = 0;
				m_struVcaDetionCfg[i].struAlarmSched[m][n].byStartMin = 0;
				m_struVcaDetionCfg[i].struAlarmSched[m][n].byStopHour = 0;
				m_struVcaDetionCfg[i].struAlarmSched[m][n].byStopMin = 0;
			}
		}
		for (int j = 0; j < MAX_CHANNUM_V30; j++)
		{
			m_struVcaDetionCfg[i].dwRelRecordChan[j] = 0;
			m_struVcaDetionCfg[i].struHandleException.dwRelAlarmOut[j] = 0;
			m_struVcaDetionCfg[i].byCruiseNo[j] = 0;
			m_struVcaDetionCfg[i].byEnableCruise[j] = 0;
			m_struVcaDetionCfg[i].byEnablePreset[j] = 0;
			m_struVcaDetionCfg[i].byEnablePtzTrack[j] = 0;
			m_struVcaDetionCfg[i].byPTZTrack[j] = 0;
			m_struVcaDetionCfg[i].byPresetNo[j] = 0;
			m_struVcaDetionCfg[i].dwRelRecordChan[j] = 0;
			
		}
		m_struChannelGroup[i].dwGroup = 0;
		m_struChannelGroup[i].dwChannel = 0;
	}
	UpdateData(FALSE);
//	memset(&m_struVcaDetionCfg,0,sizeof(m_struVcaDetionCfg));
//	memset(&m_struChannelGroup,0,sizeof(m_struChannelGroup));
}

/*********************************************************
  Function:	CreateTree
  Desc:		Create alarm output-video channel connection
  Input:	
  Output:	
  Return:	
**********************************************************/
void DlgVCADetionCfg::CreateTree(void)
{
	//m_treeAlarmOut.DeleteAllItems();
	UpdateData(TRUE);
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	int iDStartChannel = g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan;
	int iAnaChanCount = g_struDeviceInfo[iDeviceIndex].iAnalogChanNum;
	m_treeChan.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	int iChanShow = 0;
	if (m_RelRecordChanNum)
	{
		for (i = 0; i < MAX_CHANNUM_V30; i++)
		{
			iChanShow = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO;
			
			if ((i < iAnaChanCount) && g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
			{
				strTemp.Format(ANALOG_C_FORMAT, iChanShow);
				hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeChan.SetItemData(hChanItem, iChanShow/*0*1000 + i*/);	
				if (0xffffffff != m_struVcaDetionCfg[m_comCount.GetCurSel()].dwRelRecordChan[i])
				{
					m_treeChan.SetCheck(hChanItem, TRUE);
				}
			}
			else if (i >= iAnaChanCount && g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
			{
				strTemp.Format(DIGITAL_C_FORMAT, iChanShow - iDStartChannel + 1);
				hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeChan.SetItemData(hChanItem, iChanShow/*0*1000 + i*/);	
				if (0xffffffff != m_struVcaDetionCfg[m_comCount.GetCurSel()].dwRelRecordChan[i])
				{
					m_treeChan.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}
	
	m_treeChan.SelectItem(hChanItem);
	m_treeChan.Expand(m_treeChan.GetRootItem(),TVE_EXPAND);	
	UpdateWindow();
	UpdateData(FALSE);

	if (!m_bAlarmOut)
	{
		return;
	}
	m_treeAlarmOut.DeleteAllItems();
	CString strTempAlarmOut =_T("");
	CString strChanTmpAlarmOut = _T("");
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		iChanShow = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO;
		
		if ((i < iAnaChanCount) && g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
		{
			strTempAlarmOut.Format(ANALOG_C_FORMAT, iChanShow);
			hChanItem =  m_treeAlarmOut.InsertItem(strTempAlarmOut, 0, 0, TVI_ROOT);
			m_treeAlarmOut.SetItemData(hChanItem, iChanShow/*0*1000 + i*/);	
			if (0xffffffff != m_struVcaDetionCfg[m_comCount.GetCurSel()].struHandleException.dwRelAlarmOut[i])
			{
				m_treeAlarmOut.SetCheck(hChanItem, TRUE);
			}
		}
		else if (i >= iAnaChanCount && g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
		{
			strTempAlarmOut.Format(DIGITAL_C_FORMAT, iChanShow);
			hChanItem =  m_treeAlarmOut.InsertItem(strTempAlarmOut, 0, 0, TVI_ROOT);
			m_treeAlarmOut.SetItemData(hChanItem, iChanShow/*0*1000 + i*/);	
			if (0xffffffff != m_dwAlarmOut[i])
			{
				m_treeAlarmOut.SetCheck(hChanItem, TRUE);
			}
		}
	}
	m_treeAlarmOut.SelectItem(hChanItem);
	m_treeAlarmOut.Expand(m_treeAlarmOut.GetRootItem(),TVE_EXPAND);	
	
}

void DlgVCADetionCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	if (m_Num == 0)
	{
		return;
	}
	else
	{
		CreateTree();
	}
}

void DlgVCADetionCfg::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
	}
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
	if (bCheck)
	{
		m_dwAlarmOut[dwIndex] = dwIndex + 1;
	}
	else
	{
		m_dwAlarmOut[dwIndex] = 0xffffffff;
	}
	//switch checkbox status on click
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

void DlgVCADetionCfg::OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
	}
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
	if (bCheck)
	{
		m_struVcaDetionCfg[m_comCount.GetCurSel()].dwRelRecordChan[dwIndex] = dwIndex + 1;
	}
	else
	{
		m_struVcaDetionCfg[m_comCount.GetCurSel()].dwRelRecordChan[dwIndex] = 0xffffffff;
	}
	//switch checkbox status on click
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

void DlgVCADetionCfg::OnBtnExceptionok() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_comCount.GetCurSel();
	if (m_Num == 0)
	{
		AfxMessageBox("请先输入个数");
		return;
	}
//	vector<NET_DVR_VCA_DETION_CFG>::iterator it = m_struVcaDetionCfg.begin();
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bMintorAlarm << 0);
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bVoiceAlarm << 1);
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bUpCenter << 2);
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bAlarmOut << 3);
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bCaptureUploadFTP << 4);
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bWirelessAlarm << 5);
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bLinkageMap<<6);
	m_struVcaDetionCfg[sel].struHandleException.dwHandleType |= (m_bJpegCapture << 9);

	for (int i=0; i < MAX_CHANNUM_V30; i++)
	{
		if (m_dwAlarmOut[i] != 0xffffffff)
		{
			m_struVcaDetionCfg[sel].struHandleException.dwRelAlarmOut[i] = (DWORD)m_dwAlarmOut[i];
		}	
	}
}
