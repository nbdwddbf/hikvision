// DlgVcaVQDEventRule.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaVQDEventRule.h"
#include "DlgVcaAlarmTimeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaVQDEventRule dialog


CDlgVcaVQDEventRule::CDlgVcaVQDEventRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaVQDEventRule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaVQDEventRule)
	m_nAlarmThreshold = 0;
	m_nTimeInterval = 0;
	m_bUploadPic = FALSE;
	m_bEnable = FALSE;
	m_bHandleType_Jpg = FALSE;
	m_bHandleType_Monitor = FALSE;
	m_bHandleType_Output = FALSE;
	m_bHandleType_Sound = FALSE;
	m_bHandleType_Upload = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struVQDEventRule,0,sizeof(m_struVQDEventRule));
}


void CDlgVcaVQDEventRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaVQDEventRule)
	DDX_Control(pDX, IDC_COMBO_TRIGGER_MODE, m_comboTriggerMode);
	DDX_Control(pDX, IDC_LIST_RECORD_CHAN, m_listRecordChan);
	DDX_Control(pDX, IDC_LIST_ALARMOUTPUT_CHAN, m_listOutputChan);
	DDX_Control(pDX, IDC_COMBO_VQD_EVENT, m_comboVQDEvent);
	DDX_Text(pDX, IDC_EDIT_ALARM_THRESHOLD, m_nAlarmThreshold);
	DDX_Text(pDX, IDC_EDIT_TIME_INTERVAL, m_nTimeInterval);
	DDX_Check(pDX, IDC_CHECK_UPLOAD_PIC, m_bUploadPic);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_JPG, m_bHandleType_Jpg);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_MONITOR, m_bHandleType_Monitor);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_OUTPUT, m_bHandleType_Output);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_SOUND, m_bHandleType_Sound);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_UPLOAD, m_bHandleType_Upload);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaVQDEventRule, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaVQDEventRule)
	ON_BN_CLICKED(IDC_BTN_SET_ALARMTIME, OnBtnSetAlarmTime)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaVQDEventRule message handlers
BOOL CDlgVcaVQDEventRule::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCtrlState();
	return TRUE;
}

void CDlgVcaVQDEventRule::OnBtnSetAlarmTime() 
{
	CDlgVcaAlarmTimeCfg dlg;
	dlg.InitAlarmTimeCfg(m_struVQDEventRule.struAlarmTime);
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetAlarmTimeCfg(m_struVQDEventRule.struAlarmTime);
	}
}

void CDlgVcaVQDEventRule::OnBtnGet() 
{
	char szError[32] = "\0";
	if (!GetVQDEventRule())
	{
       	g_StringLanType(szError, "获取失败","Get failed");
		AfxMessageBox(szError);
		
	}
	else
	{
		LoadWndContent();
	}
}

void CDlgVcaVQDEventRule::OnBtnSave() 
{
	SaveWndContent();
	
	char szError[32] = "\0";
	if (SetVQDEventRule())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaVQDEventRule::InitCtrlState()
{   
	m_comboVQDEvent.ResetContent();
	m_comboTriggerMode.ResetContent();

	char szText[64] = "\0";
	g_StringLanType(szText, "图像模糊", "Image Blur");
	m_comboVQDEvent.InsertString(0,szText);
	m_comboVQDEvent.SetItemData(0,ENUM_VQD_EVENT_BLUR);
    
	g_StringLanType(szText, "亮度异常", "Brightness Abnormal");
	m_comboVQDEvent.InsertString(1,szText);
	m_comboVQDEvent.SetItemData(1,ENUM_VQD_EVENT_LUMA);
    
	g_StringLanType(szText, "图像偏色", "Image Colour Cast ");
	m_comboVQDEvent.InsertString(2,szText);
	m_comboVQDEvent.SetItemData(2,ENUM_VQD_EVENT_CHROMA);

	g_StringLanType(szText, "雪花干扰", "Snowflakes Interference");
	m_comboVQDEvent.InsertString(3,szText);
	m_comboVQDEvent.SetItemData(3,ENUM_VQD_EVENT_SNOW);

	g_StringLanType(szText, "条纹干扰", "Streak Interference");
	m_comboVQDEvent.InsertString(4,szText);
	m_comboVQDEvent.SetItemData(4,ENUM_VQD_EVENT_STREAK);

	g_StringLanType(szText, "画面冻结", "Image Freeze");
	m_comboVQDEvent.InsertString(5,szText);
	m_comboVQDEvent.SetItemData(5,ENUM_VQD_EVENT_FREEZE);

	g_StringLanType(szText, "信号丢失", "Signal Loss");
	m_comboVQDEvent.InsertString(6,szText);
	m_comboVQDEvent.SetItemData(6,ENUM_VQD_EVENT_SIGNAL_LOSS);

	g_StringLanType(szText, "云台失控", "PTZ Abnormal");
	m_comboVQDEvent.InsertString(7,szText);
	m_comboVQDEvent.SetItemData(7,ENUM_VQD_EVENT_PTZ);

	g_StringLanType(szText, "场景突变", "Scene Change");
	m_comboVQDEvent.InsertString(8,szText);
	m_comboVQDEvent.SetItemData(8,ENUM_VQD_EVENT_SCNENE_CHANGE);

	g_StringLanType(szText, "视频异常", "Video Abnormal");
	m_comboVQDEvent.InsertString(9,szText);
	m_comboVQDEvent.SetItemData(9,ENUM_VQD_EVENT_VIDEO_ABNORMAL);

	g_StringLanType(szText, "视频遮挡", "Video Block");
	m_comboVQDEvent.InsertString(10,szText);
	m_comboVQDEvent.SetItemData(10,ENUM_VQD_EVENT_VIDEO_BLOCK);
    
	g_StringLanType(szText, "持续触发", "Continuous");
	m_comboTriggerMode.InsertString(0,szText);
	m_comboTriggerMode.SetItemData(0,ALARM_TRIGGER_MODE_CONTINUOUS);

	g_StringLanType(szText, "单次触发", "Single");
	m_comboTriggerMode.InsertString(1,szText);
	m_comboTriggerMode.SetItemData(1,ALARM_TRIGGER_MODE_SINGLE);

	m_comboVQDEvent.SetCurSel(0);
	m_comboTriggerMode.SetCurSel(0);

	char szLan[128] = {0};
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
	int i = 0;

	for (i = 0; i < MAX_IP_ALARMOUT; i++)
	{
		DWORD dwID       = g_struDeviceInfo[m_iDevIndex].struAlarmOutCfg.struIPAlarmOutInfo[i].byIPID;
		DWORD dwAlarmOut = g_struDeviceInfo[m_iDevIndex].struAlarmOutCfg.struIPAlarmOutInfo[i].byAlarmOut;
		if (dwID != 0)
		{   
			sprintf(sbufCn, "IP输出 %d", (i+1));
			sprintf(sbufEn, "IPAlarmOut %d", (i+1));
            g_StringLanType(szLan, sbufCn, sbufEn);
			m_listOutputChan.InsertString(i,szLan);
			m_listOutputChan.SetItemData(i,dwAlarmOut);
		}
	}
	
    int nChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    m_listRecordChan.ResetContent();
    for (i = 0; i < nChannelnumber; i++)
    {
        sprintf(sbufCn, "通道%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listRecordChan.InsertString(i, szLan);
    }
}

void CDlgVcaVQDEventRule::LoadWndContent()
{   
	m_bEnable = m_struVQDEventRule.byEnable;
	
	NET_DVR_VQD_EVENT_PARAM& struEventParam = m_struVQDEventRule.struEventParam;
	m_nAlarmThreshold = struEventParam.byThreshold;
	m_bUploadPic      = struEventParam.byUploadPic;
	m_nTimeInterval   = struEventParam.dwTimeInterval;
    
	int i =0;
	int nItemCount  = m_comboTriggerMode.GetCount();
	for (i = 0; i < nItemCount; i++)
	{
		if (m_comboTriggerMode.GetItemData(i) == struEventParam.byTriggerMode)
		{
			m_comboTriggerMode.SetCurSel(i);
			break;
		}
	}
	
	m_bHandleType_Monitor  = m_struVQDEventRule.struHandleType.dwHandleType & 0x01 ? TRUE : FALSE;
    m_bHandleType_Sound    = m_struVQDEventRule.struHandleType.dwHandleType & 0x02 ? TRUE : FALSE;
    m_bHandleType_Upload   = m_struVQDEventRule.struHandleType.dwHandleType & 0x04 ? TRUE : FALSE;
    m_bHandleType_Output   = m_struVQDEventRule.struHandleType.dwHandleType & 0x08 ? TRUE : FALSE;
    m_bHandleType_Jpg      = m_struVQDEventRule.struHandleType.dwHandleType & 0x10 ? TRUE : FALSE;
	
	
    for (i = 0; i < MAX_ALARMOUT_V30; i++)
    {   
		if (i >= m_listOutputChan.GetCount())
		{
			break;
		}
		
        if (m_struVQDEventRule.struHandleType.byRelAlarmOut[i])
		{   
			m_listOutputChan.SetCheck(i,TRUE);
		}
		else
		{
			m_listOutputChan.SetCheck(i,FALSE);
		}
    }
	
	int nChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
	for (i = 0; i < nChannelnumber; i++)
    {
        if (m_struVQDEventRule.byRelRecordChan[i])
		{
			m_listRecordChan.SetCheck(i,TRUE);
		}
		else
		{
			m_listRecordChan.SetCheck(i,FALSE);
		}
    }

	UpdateData(FALSE);
}

void CDlgVcaVQDEventRule::SaveWndContent()
{
	UpdateData(TRUE);

	m_struVQDEventRule.dwSize = sizeof(m_struVQDEventRule);
	m_struVQDEventRule.byEnable = m_bEnable;
	
	NET_DVR_VQD_EVENT_PARAM& struEventParam = m_struVQDEventRule.struEventParam;
	struEventParam.byThreshold    = m_nAlarmThreshold;
	struEventParam.byTriggerMode  = m_comboTriggerMode.GetItemData(m_comboTriggerMode.GetCurSel());
	struEventParam.byUploadPic    = m_bUploadPic;
	struEventParam.dwTimeInterval = m_nTimeInterval;

	m_struVQDEventRule.struHandleType.dwHandleType = 0;
	
	if (m_bHandleType_Monitor)
	{
		m_struVQDEventRule.struHandleType.dwHandleType |= 0x01;
	}
	if (m_bHandleType_Sound)
	{
		m_struVQDEventRule.struHandleType.dwHandleType |= 0x02;
	}
	
	if (m_bHandleType_Upload)
	{
		m_struVQDEventRule.struHandleType.dwHandleType |= 0x04;
	}
	
	if (m_bHandleType_Output)
	{
		m_struVQDEventRule.struHandleType.dwHandleType |= 0x08;
	}
	
	if (m_bHandleType_Jpg)
	{
		m_struVQDEventRule.struHandleType.dwHandleType |= 0x10;
	}
    
	int i = 0;
    for (i = 0; i < MAX_ALARMOUT_V30; i++)
    {   
		if (i >= m_listOutputChan.GetCount())
		{
			break;
		}
        m_struVQDEventRule.struHandleType.byRelAlarmOut[i] = m_listOutputChan.GetCheck(i);
    }
    
	int nChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
	for (i = 0; i < nChannelnumber; i++)
    {
        m_struVQDEventRule.byRelRecordChan[i] = m_listRecordChan.GetCheck(i);
	}
}

BOOL CDlgVcaVQDEventRule::GetVQDEventRule()
{   
	DWORD dwVQDEventType = m_comboVQDEvent.GetItemData(m_comboVQDEvent.GetCurSel());

	NET_DVR_VQD_EVENT_COND struEventCond = {0};
	struEventCond.dwChannel   = m_lChannel;
	struEventCond.dwEventType = dwVQDEventType;

	DWORD dwStatus = 0;
	BOOL  bRet     = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_VQD_EVENT_RULE, 1,(LPVOID)&struEventCond, sizeof(struEventCond),
		&dwStatus,&m_struVQDEventRule, sizeof(m_struVQDEventRule)))
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VQD_EVENT_RULE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VQD_EVENT_RULE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaVQDEventRule::SetVQDEventRule()
{   
	DWORD dwVQDEventType = m_comboVQDEvent.GetItemData(m_comboVQDEvent.GetCurSel());
	
	NET_DVR_VQD_EVENT_COND struEventCond = {0};
	struEventCond.dwChannel   = m_lChannel;
	struEventCond.dwEventType = dwVQDEventType;

	DWORD dwStatus = 0;
	BOOL  bRet     = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_VQD_EVENT_RULE,1,(LPVOID)&struEventCond, sizeof(struEventCond),
		&dwStatus,&m_struVQDEventRule, sizeof(m_struVQDEventRule)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VQD_EVENT_RULE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VQD_EVENT_RULE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}