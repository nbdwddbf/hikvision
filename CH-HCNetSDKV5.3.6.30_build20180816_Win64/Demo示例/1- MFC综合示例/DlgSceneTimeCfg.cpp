// DlgSceneTimeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSceneTimeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSceneTimeCfg dialog


CDlgSceneTimeCfg::CDlgSceneTimeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSceneTimeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSceneTimeCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lServerID   = -1;
    m_iDevIndex   = -1;
    m_lChannel    = -1;
	memset(&m_struSceneTimeCfg,0,sizeof(m_struSceneTimeCfg));
	memset(&m_struSceneCfg    ,0,sizeof(m_struSceneCfg));
	m_struSceneTimeCfg.dwSize = sizeof(m_struSceneTimeCfg);
}


void CDlgSceneTimeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSceneTimeCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER1_START,m_dtArryTimeBegin[0]);
    DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER2_START,m_dtArryTimeBegin[1]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER3_START,m_dtArryTimeBegin[2]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER4_START,m_dtArryTimeBegin[3]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER5_START,m_dtArryTimeBegin[4]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER6_START,m_dtArryTimeBegin[5]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER7_START,m_dtArryTimeBegin[6]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER8_START,m_dtArryTimeBegin[7]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER9_START,m_dtArryTimeBegin[8]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER10_START,m_dtArryTimeBegin[9]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER11_START,m_dtArryTimeBegin[10]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER12_START,m_dtArryTimeBegin[11]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER13_START,m_dtArryTimeBegin[12]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER14_START,m_dtArryTimeBegin[13]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER15_START,m_dtArryTimeBegin[14]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER16_START,m_dtArryTimeBegin[15]);

	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER1_END,m_dtArryTimeEnd[0]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER2_END,m_dtArryTimeEnd[1]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER3_END,m_dtArryTimeEnd[2]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER4_END,m_dtArryTimeEnd[3]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER5_END,m_dtArryTimeEnd[4]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER6_END,m_dtArryTimeEnd[5]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER7_END,m_dtArryTimeEnd[6]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER8_END,m_dtArryTimeEnd[7]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER9_END,m_dtArryTimeEnd[8]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER10_END,m_dtArryTimeEnd[9]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER11_END,m_dtArryTimeEnd[10]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER12_END,m_dtArryTimeEnd[11]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER13_END,m_dtArryTimeEnd[12]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER14_END,m_dtArryTimeEnd[13]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER15_END,m_dtArryTimeEnd[14]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER16_END,m_dtArryTimeEnd[15]);

	DDX_Control(pDX,IDC_DATETIMEPICKER1_START,m_dtCtrlArryTimeBegin[0]);
    DDX_Control(pDX,IDC_DATETIMEPICKER2_START,m_dtCtrlArryTimeBegin[1]);
	DDX_Control(pDX,IDC_DATETIMEPICKER3_START,m_dtCtrlArryTimeBegin[2]);
	DDX_Control(pDX,IDC_DATETIMEPICKER4_START,m_dtCtrlArryTimeBegin[3]);
	DDX_Control(pDX,IDC_DATETIMEPICKER5_START,m_dtCtrlArryTimeBegin[4]);
	DDX_Control(pDX,IDC_DATETIMEPICKER6_START,m_dtCtrlArryTimeBegin[5]);
	DDX_Control(pDX,IDC_DATETIMEPICKER7_START,m_dtCtrlArryTimeBegin[6]);
	DDX_Control(pDX,IDC_DATETIMEPICKER8_START,m_dtCtrlArryTimeBegin[7]);
	DDX_Control(pDX,IDC_DATETIMEPICKER9_START,m_dtCtrlArryTimeBegin[8]);
	DDX_Control(pDX,IDC_DATETIMEPICKER10_START,m_dtCtrlArryTimeBegin[9]);
	DDX_Control(pDX,IDC_DATETIMEPICKER11_START,m_dtCtrlArryTimeBegin[10]);
	DDX_Control(pDX,IDC_DATETIMEPICKER12_START,m_dtCtrlArryTimeBegin[11]);
	DDX_Control(pDX,IDC_DATETIMEPICKER13_START,m_dtCtrlArryTimeBegin[12]);
	DDX_Control(pDX,IDC_DATETIMEPICKER14_START,m_dtCtrlArryTimeBegin[13]);
	DDX_Control(pDX,IDC_DATETIMEPICKER15_START,m_dtCtrlArryTimeBegin[14]);
	DDX_Control(pDX,IDC_DATETIMEPICKER16_START,m_dtCtrlArryTimeBegin[15]);

	DDX_Control(pDX,IDC_DATETIMEPICKER1_END,m_dtCtrlArryTimeEnd[0]);
	DDX_Control(pDX,IDC_DATETIMEPICKER2_END,m_dtCtrlArryTimeEnd[1]);
	DDX_Control(pDX,IDC_DATETIMEPICKER3_END,m_dtCtrlArryTimeEnd[2]);
	DDX_Control(pDX,IDC_DATETIMEPICKER4_END,m_dtCtrlArryTimeEnd[3]);
	DDX_Control(pDX,IDC_DATETIMEPICKER5_END,m_dtCtrlArryTimeEnd[4]);
	DDX_Control(pDX,IDC_DATETIMEPICKER6_END,m_dtCtrlArryTimeEnd[5]);
	DDX_Control(pDX,IDC_DATETIMEPICKER7_END,m_dtCtrlArryTimeEnd[6]);
	DDX_Control(pDX,IDC_DATETIMEPICKER8_END,m_dtCtrlArryTimeEnd[7]);
	DDX_Control(pDX,IDC_DATETIMEPICKER9_END,m_dtCtrlArryTimeEnd[8]);
	DDX_Control(pDX,IDC_DATETIMEPICKER10_END,m_dtCtrlArryTimeEnd[9]);
	DDX_Control(pDX,IDC_DATETIMEPICKER11_END,m_dtCtrlArryTimeEnd[10]);
	DDX_Control(pDX,IDC_DATETIMEPICKER12_END,m_dtCtrlArryTimeEnd[11]);
	DDX_Control(pDX,IDC_DATETIMEPICKER13_END,m_dtCtrlArryTimeEnd[12]);
	DDX_Control(pDX,IDC_DATETIMEPICKER14_END,m_dtCtrlArryTimeEnd[13]);
	DDX_Control(pDX,IDC_DATETIMEPICKER15_END,m_dtCtrlArryTimeEnd[14]);
	DDX_Control(pDX,IDC_DATETIMEPICKER16_END,m_dtCtrlArryTimeEnd[15]);

	DDX_Control(pDX,IDC_COMBO1, m_comboArryScene[0]);
	DDX_Control(pDX,IDC_COMBO2, m_comboArryScene[1]);
	DDX_Control(pDX,IDC_COMBO3, m_comboArryScene[2]);
	DDX_Control(pDX,IDC_COMBO4, m_comboArryScene[3]);
	DDX_Control(pDX,IDC_COMBO5, m_comboArryScene[4]);
	DDX_Control(pDX,IDC_COMBO6, m_comboArryScene[5]);
	DDX_Control(pDX,IDC_COMBO7, m_comboArryScene[6]);
	DDX_Control(pDX,IDC_COMBO8, m_comboArryScene[7]);
	DDX_Control(pDX,IDC_COMBO9, m_comboArryScene[8]);
	DDX_Control(pDX,IDC_COMBO10, m_comboArryScene[9]);
	DDX_Control(pDX,IDC_COMBO11, m_comboArryScene[10]);
	DDX_Control(pDX,IDC_COMBO12, m_comboArryScene[11]);
	DDX_Control(pDX,IDC_COMBO13, m_comboArryScene[12]);
	DDX_Control(pDX,IDC_COMBO14, m_comboArryScene[13]);
	DDX_Control(pDX,IDC_COMBO15, m_comboArryScene[14]);
	DDX_Control(pDX,IDC_COMBO16, m_comboArryScene[15]);

	DDX_Check(pDX,IDC_CHECK1,m_bArryActive[0]);
	DDX_Check(pDX,IDC_CHECK2,m_bArryActive[1]);
	DDX_Check(pDX,IDC_CHECK3,m_bArryActive[2]);
	DDX_Check(pDX,IDC_CHECK4,m_bArryActive[3]);
	DDX_Check(pDX,IDC_CHECK5,m_bArryActive[4]);
	DDX_Check(pDX,IDC_CHECK6,m_bArryActive[5]);
	DDX_Check(pDX,IDC_CHECK7,m_bArryActive[6]);
	DDX_Check(pDX,IDC_CHECK8,m_bArryActive[7]);
	DDX_Check(pDX,IDC_CHECK9,m_bArryActive[8]);
	DDX_Check(pDX,IDC_CHECK10,m_bArryActive[9]);
	DDX_Check(pDX,IDC_CHECK11,m_bArryActive[10]);
	DDX_Check(pDX,IDC_CHECK12,m_bArryActive[11]);
	DDX_Check(pDX,IDC_CHECK13,m_bArryActive[12]);
	DDX_Check(pDX,IDC_CHECK14,m_bArryActive[13]);
	DDX_Check(pDX,IDC_CHECK15,m_bArryActive[14]);
	DDX_Check(pDX,IDC_CHECK16,m_bArryActive[15]);
}


BEGIN_MESSAGE_MAP(CDlgSceneTimeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSceneTimeCfg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSceneTimeCfg message handlers

BOOL CDlgSceneTimeCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	char szError[64] = "\0";
	BOOL bInitSuc    = TRUE;
	if (bInitSuc && !GetSceneCfg(m_struSceneCfg))
	{
		g_StringLanType(szError, "获取场景配置信息失败", "Get Scene cfg failed!");
		bInitSuc = FALSE;
	}
	if (bInitSuc && !GetSceneTimeCfg())
	{
		g_StringLanType(szError, "获取场景时间段配置信息失败", "Get Scene time cfg failed!");
		bInitSuc = FALSE;
	}

	if (!bInitSuc)
	{
		AfxMessageBox(szError);
	}
    InitCtrlState();
	InitWndContent();
	UpdateData(FALSE);

	return TRUE;
}

void CDlgSceneTimeCfg::InitCtrlState()
{
	for (int i = 0; i < MAX_SCENE_TIMESEG_NUM; i++)
	{
		m_dtCtrlArryTimeBegin[i].SetFormat(_T("HH:mm"));
		m_dtCtrlArryTimeEnd[i].SetFormat(_T("HH:mm"));
	}
}

void CDlgSceneTimeCfg::OnBtnSave() 
{   
	if (!ValidateParams())
	{
		return;
	}
	GetWndContent();
    
	char szError[32] = "\0";
	if (SaveSceneTimeCfg())
	{
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

BOOL CDlgSceneTimeCfg::GetSceneTimeCfg()
{
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_TIME_CFG, 1,(LPVOID)&m_lChannel, sizeof(m_lChannel),
		&dwStatus,&m_struSceneTimeCfg, sizeof(m_struSceneTimeCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_TIME_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_TIME_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgSceneTimeCfg::SaveSceneTimeCfg()
{
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
	m_struSceneTimeCfg.dwSize = sizeof(m_struSceneTimeCfg);
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_TIME_CFG,1,(LPVOID)&m_lChannel, sizeof(m_lChannel),
		&dwStatus,&m_struSceneTimeCfg, sizeof(m_struSceneTimeCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_TIME_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_TIME_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgSceneTimeCfg::InitWndContent()
{  
	for (int i = 0; i < MAX_SCENE_TIMESEG_NUM; i++)
	{   
		const NET_DVR_ONE_SCENE_TIME& struOneSceneTime = m_struSceneTimeCfg.struSceneTime[i];
		m_bArryActive[i]     = struOneSceneTime.byActive;
		m_dtArryTimeBegin[i] = COleDateTime::GetCurrentTime();
		m_dtArryTimeEnd[i]   = COleDateTime::GetCurrentTime();
		m_dtArryTimeBegin[i].SetTime(min(23,struOneSceneTime.struEffectiveTime.byStartHour),min(59,struOneSceneTime.struEffectiveTime.byStartMin),0);
		m_dtArryTimeEnd[i].SetTime(min(23,struOneSceneTime.struEffectiveTime.byStopHour),min(59,struOneSceneTime.struEffectiveTime.byStopMin),0);

        int nIndex = 0;
		for (int j = 0; j < MAX_ITS_SCENE_NUM; j++)
		{   
			const NET_DVR_ONE_SCENE_CFG& struOneSceneCfg = m_struSceneCfg.struSceneCfg[j];

			if (struOneSceneCfg.dwSceneID > 0 && struOneSceneCfg.byEnable)
			{
				m_comboArryScene[i].InsertString(nIndex,CString(struOneSceneCfg.bySceneName));
				m_comboArryScene[i].SetItemData(nIndex,struOneSceneCfg.dwSceneID);

				if (struOneSceneTime.dwSceneID == struOneSceneCfg.dwSceneID)
				{
					m_comboArryScene[i].SetCurSel(nIndex);
				}
				nIndex++;
			}
		}
	}
}


void CDlgSceneTimeCfg::GetWndContent()
{
	UpdateData(TRUE);

	for (int i = 0; i < MAX_SCENE_TIMESEG_NUM; i++)
	{
		NET_DVR_ONE_SCENE_TIME& struOneSceneTime = m_struSceneTimeCfg.struSceneTime[i];

		struOneSceneTime.byActive                      = m_bArryActive[i];
		if (m_bArryActive[i])
		{
			struOneSceneTime.struEffectiveTime.byStartHour = m_dtArryTimeBegin[i].GetHour();
			struOneSceneTime.struEffectiveTime.byStartMin  = m_dtArryTimeBegin[i].GetMinute();
			struOneSceneTime.struEffectiveTime.byStopHour  = m_dtArryTimeEnd[i].GetHour();
			struOneSceneTime.struEffectiveTime.byStopMin   = m_dtArryTimeEnd[i].GetMinute();
			
			int nSelSceneIndex = m_comboArryScene[i].GetCurSel();
			if (nSelSceneIndex != CB_ERR)
			{
				struOneSceneTime.dwSceneID = m_comboArryScene[i].GetItemData(nSelSceneIndex);
			}
		}
	}
}

BOOL CDlgSceneTimeCfg::ValidateParams()
{   
	UpdateData(TRUE);
    
	BOOL bValid = TRUE;

	char szCnLan[128]   = "\0";
	char szEnLan[128]   = "\0";
	char szErrInfo[128] = "\0";

	for (int i = 0; i < MAX_SCENE_TIMESEG_NUM; i++)
	{
		if (m_bArryActive[i])
		{
			if (m_dtArryTimeBegin[i] >= m_dtArryTimeEnd[i])
			{   
				bValid = FALSE;
				sprintf(szCnLan,"场景时间段 [%d] 参数不合理,开始时间需小于结束时间",i + 1);
				sprintf(szEnLan,"Scene time segment [%d] parameter is not correct,begintime must less than endtime",i + 1);
				break;
			}
			else if (m_comboArryScene[i].GetCurSel() == CB_ERR)
			{
				bValid = FALSE;
				sprintf(szCnLan,"场景时间段 [%d] 参数不合理,请选择要关联的场景",i + 1);
				sprintf(szEnLan,"Scene time segment [%d] parameter is not correct,please select a associated scene first",i + 1);
				break;
			}
		}
	}

	if (!bValid)
	{
		g_StringLanType(szErrInfo, szCnLan, szEnLan);
		AfxMessageBox(szErrInfo);
	}
	return bValid;
}
