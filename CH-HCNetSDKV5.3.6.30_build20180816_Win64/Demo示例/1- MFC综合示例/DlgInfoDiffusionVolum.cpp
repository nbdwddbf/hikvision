// DlgInfoDiffusionVolum.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionVolum.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionVolum dialog


CDlgInfoDiffusionVolum::CDlgInfoDiffusionVolum(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionVolum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionVolum)
	m_dwVolum = 0;
	m_dtDate = COleDateTime::GetCurrentTime();
	m_dtTime = COleDateTime::GetCurrentTime();
	m_dtTimeEnd = COleDateTime::GetCurrentTime();
	m_dtDateEnd = COleDateTime::GetCurrentTime();
	m_dwGetID = 0;
	m_dwGroupId = 0;
	m_dwTerminalId = 0;
	//}}AFX_DATA_INIT

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    memset(&m_struVolumeCfg, 0, sizeof(m_struVolumeCfg));
    m_struVolumeCfg.dwSize = sizeof(m_struVolumeCfg);
    m_nCurSelSpan = -1;
    m_nCurSelTerminal = -1;
    m_nCurSelGroup = -1;
    m_pOutputXmlBuffer = new char[MAX_LEN_XML];
    memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
}


void CDlgInfoDiffusionVolum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionVolum)
	DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
	DDX_Control(pDX, IDC_LIST_GROUP, m_listGroup);
	DDX_Control(pDX, IDC_COMBO_OPERA_TYPE, m_cmbOperType);
	DDX_Control(pDX, IDC_LIST_SPAN, m_listSpan);
	DDX_Control(pDX, IDC_COMBO_WEEKDAY, m_cmbWeekday);
	DDX_Control(pDX, IDC_COMBO_PLAN_TYPE, m_cmbPlanType);
	DDX_Text(pDX, IDC_EDIT_VOLUM, m_dwVolum);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_DATE, m_dtDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_TIME, m_dtTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_TIME_END, m_dtTimeEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_DATE2_END, m_dtDateEnd);
	DDX_Text(pDX, IDC_EDIT_CFG_ID, m_dwGetID);
	DDX_Text(pDX, IDC_EDIT_GROUPID, m_dwGroupId);
	DDX_Text(pDX, IDC_EDIT_TER_ID, m_dwTerminalId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionVolum, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionVolum)
	ON_BN_CLICKED(IDC_BTN_PLAN_SPAN_ADD, OnBtnPlanSpanAdd)
	ON_BN_CLICKED(IDC_BTN_PLAN_SPAN_DEL, OnBtnPlanSpanDel)
	ON_BN_CLICKED(IDC_BTN_PLAN_SPAN_MOD, OnBtnPlanSpanMod)
	ON_CBN_SELCHANGE(IDC_COMBO_PLAN_TYPE, OnSelchangeComboPlanType)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, OnSelchangeComboWeekday)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_SPAN, OnClickListSpan)
	ON_BN_CLICKED(IDC_BTN_TER_ADD, OnBtnTerAdd)
	ON_BN_CLICKED(IDC_BTN_TER_DEL, OnBtnTerDel)
	ON_BN_CLICKED(IDC_BTN_TER_MOD, OnBtnTerMod)
	ON_BN_CLICKED(IDC_BTN_VOLUE_GET, OnBtnVolueGet)
	ON_BN_CLICKED(IDC_BTN_VOLUME_SET, OnBtnVolumeSet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_GROUP, OnClickListGroup)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, OnClickListTerminal)
	ON_BN_CLICKED(IDC_BTN_GROUP_ADD, OnBtnGroupAdd)
	ON_BN_CLICKED(IDC_BTN_GROUP_DEL, OnBtnGroupDel)
	ON_BN_CLICKED(IDC_BTN_GROUP_MOD, OnBtnGroupMod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionVolum message handlers


void CDlgInfoDiffusionVolum::OnBtnPlanSpanAdd() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int nSel = m_cmbPlanType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType;
    m_cmbPlanType.GetLBText(nSel,strPlanType);
    CString str;
    int nSpanIndex = -1;
    int nSpanCnt = 0;
    strcpy(m_struVolumeCfg.struVolumePlan.sPlanType,strPlanType);
    if(0 == strcmp(strPlanType,"daily"))
    {
        for(nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY;nSpanCnt++)
        {
            if(0 == m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanCnt].dwSpanID)
            {
                nSpanIndex = nSpanCnt;
                break;
            }
        }
        if(nSpanIndex < 0)
        {
            char szLan1[512] = {0};
            char szLan2[512] = {0};
            g_StringLanType(szLan1, "时段数量已达上限", "The number of span is limited.");
            g_StringLanType(szLan2, "定时开关机管理", "Shut down Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].dwVolume = m_dwVolum;
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].dwSpanID = nSpanIndex+1;
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTime.dwYear = m_dtDate.GetYear();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTime.dwMonth = m_dtDate.GetMonth();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTime.dwDay = m_dtDate.GetDay();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTime.dwHour = m_dtTime.GetHour();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTime.dwMinute = m_dtTime.GetMinute();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTime.dwSecond = m_dtTime.GetSecond();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTimeEnd.dwYear = m_dtDateEnd.GetYear();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTimeEnd.dwMonth = m_dtDateEnd.GetMonth();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTimeEnd.dwDay = m_dtDateEnd.GetDay();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTimeEnd.dwHour = m_dtTimeEnd.GetHour();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTimeEnd.dwMinute = m_dtTimeEnd.GetMinute();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex].struTimeEnd.dwSecond = m_dtTimeEnd.GetSecond();
        NET_DVR_VOLUME_SPAN *lpSpan = &m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanIndex];
        str.Format("%d",nSpanIndex+1);
        m_listSpan.InsertItem(nSpanIndex,str);
        m_listSpan.SetItemState(nSpanIndex, 0, -1);
        m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
        m_listSpan.SetFocus();
        m_nCurSelSpan = nSpanIndex;
        str.Format("%d",lpSpan->dwVolume);
        m_listSpan.SetItemText(nSpanIndex,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 2, str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTimeEnd.dwYear,
            lpSpan->struTimeEnd.dwMonth,
            lpSpan->struTimeEnd.dwDay,
            lpSpan->struTimeEnd.dwHour,
            lpSpan->struTimeEnd.dwMinute,
            lpSpan->struTimeEnd.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 3, str);
    }
    else if(0 == strcmp(strPlanType,"weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if(nSel == CB_ERR)
        {
            return;
        }
        m_cmbWeekday.GetLBText(nSel,m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].sWeekday);
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].dwDayID = nSel+1;
        for(nSpanCnt = 0;nSpanCnt < MAX_SPANS_A_DAY;nSpanCnt++)
        {
            if(0 == m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanCnt].dwSpanID)
            {
                nSpanIndex = nSpanCnt;
                break;
            }
        }
        if(nSpanIndex < 0)
        { 
            char szLan1[512] = {0};
            char szLan2[512] = {0};
            g_StringLanType(szLan1, "时段数量已达上限", "The number of span is limited.");
            g_StringLanType(szLan2, "定时开关机管理", "Shutdown Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].dwVolume = m_dwVolum;
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].dwSpanID = nSpanIndex+1;
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwYear = m_dtDate.GetYear();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwMonth = m_dtDate.GetMonth();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwDay = m_dtDate.GetDay();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwHour = m_dtTime.GetHour();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwMinute = m_dtTime.GetMinute();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwSecond = m_dtTime.GetSecond();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTimeEnd.dwYear = m_dtDateEnd.GetYear();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTimeEnd.dwMonth = m_dtDateEnd.GetMonth();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTimeEnd.dwDay = m_dtDateEnd.GetDay();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTimeEnd.dwHour = m_dtTimeEnd.GetHour();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTimeEnd.dwMinute = m_dtTimeEnd.GetMinute();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTimeEnd.dwSecond = m_dtTimeEnd.GetSecond();
        NET_DVR_VOLUME_SPAN *lpSpan = &m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanIndex];
        
        str.Format("%d",nSpanIndex+1);
        m_listSpan.InsertItem(nSpanIndex,str);
        m_listSpan.SetItemState(nSpanIndex, 0, -1);
        m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
        m_listSpan.SetFocus();
        m_nCurSelSpan = nSpanIndex;
        str.Format("%d",lpSpan->dwVolume);
        m_listSpan.SetItemText(nSpanIndex,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 2, str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTimeEnd.dwYear,
            lpSpan->struTimeEnd.dwMonth,
            lpSpan->struTimeEnd.dwDay,
            lpSpan->struTimeEnd.dwHour,
            lpSpan->struTimeEnd.dwMinute,
            lpSpan->struTimeEnd.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 3, str);
    }
}

void CDlgInfoDiffusionVolum::OnBtnPlanSpanDel() 
{
	// TODO: Add your control notification handler code here
    if (m_nCurSelSpan < 0)
    {
        char szLan1[512] = {0};
        char szLan2[512] = {0};
        g_StringLanType(szLan1, "请选择计划时段", "Please choose a plan first.");
        g_StringLanType(szLan2, "音量管理", "Shut down Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    int nSel = m_cmbPlanType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType;
    m_cmbPlanType.GetLBText(nSel, strPlanType);
    CString str;
    if (0 == strcmp(strPlanType, "daily"))
    {
        for (int nSpanCnt = m_nCurSelSpan; nSpanCnt < m_listSpan.GetItemCount()-1; nSpanCnt++)
        {
            m_listSpan.SetItemText(nSpanCnt, 1, m_listSpan.GetItemText(nSpanCnt+1, 1));
            m_listSpan.SetItemText(nSpanCnt, 2, m_listSpan.GetItemText(nSpanCnt+1, 2));
            m_listSpan.SetItemText(nSpanCnt, 3, m_listSpan.GetItemText(nSpanCnt+1, 3));
            memcpy(&m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanCnt], 
                &m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanCnt+1],
                sizeof(LPNET_DVR_VOLUME_SPAN));
            m_struVolumeCfg.struVolumePlan.struDailyPlan[nSpanCnt].dwSpanID = nSpanCnt+1;
        }
        NET_DVR_VOLUME_SPAN *lpSpan = &m_struVolumeCfg.struVolumePlan.struDailyPlan[m_listSpan.GetItemCount()-1];
        memset(lpSpan, 0, sizeof(*lpSpan));
        m_listSpan.DeleteItem(m_listSpan.GetItemCount()-1);
    }
    else if (0 == strcmp(strPlanType, "weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if (nSel ==CB_ERR)
        {
            return;
        }
        for (int nSpanCnt = m_nCurSelSpan; nSpanCnt < m_listSpan.GetItemCount()-1; nSpanCnt++)
        {
            m_listSpan.SetItemText(nSpanCnt, 1, m_listSpan.GetItemText(nSpanCnt+1, 1));
            m_listSpan.SetItemText(nSpanCnt, 2, m_listSpan.GetItemText(nSpanCnt+1, 2));
            m_listSpan.SetItemText(nSpanCnt, 3, m_listSpan.GetItemText(nSpanCnt+1, 3));
            memcpy(&m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanCnt], 
                &m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanCnt+1],
                sizeof(LPNET_DVR_VOLUME_SPAN));
            m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[nSpanCnt].dwSpanID = nSpanCnt+1;
        }
        NET_DVR_VOLUME_SPAN *lpSpan = &m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_listSpan.GetItemCount()-1];
        memset(lpSpan, 0, sizeof(*lpSpan));
        m_listSpan.DeleteItem(m_listSpan.GetItemCount()-1);
        if (m_listSpan.GetItemCount() == 0)
        {
            m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].dwDayID = 0;
        }
    }
}

void CDlgInfoDiffusionVolum::OnBtnPlanSpanMod() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if(m_nCurSelSpan < 0)
    {
        char szLan1[512] = {0};
        char szLan2[512] = {0};
        g_StringLanType(szLan1, "请选择计划时段", "Please choose a Plan first.");
        g_StringLanType(szLan2, "开关机管理", "Shutdown Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    int nSel = m_cmbPlanType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType ;
    m_cmbPlanType.GetLBText(nSel,strPlanType);
    CString str;
    if(0 == strcmp(strPlanType,"daily"))
    {
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].dwVolume = m_dwVolum;
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwYear = m_dtDate.GetYear();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwMonth = m_dtDate.GetMonth();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwDay = m_dtDate.GetDay();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwHour = m_dtTime.GetHour();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwMinute = m_dtTime.GetMinute();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwSecond = m_dtTime.GetSecond();

        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwYear = m_dtDateEnd.GetYear();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwMonth = m_dtDateEnd.GetMonth();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwDay = m_dtDateEnd.GetDay();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwHour = m_dtTimeEnd.GetHour();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwMinute = m_dtTimeEnd.GetMinute();
        m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwSecond = m_dtTimeEnd.GetSecond();

        NET_DVR_VOLUME_SPAN *lpSpan = &m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan];
        
        str.Format("%d",lpSpan->dwVolume);
        m_listSpan.SetItemText(m_nCurSelSpan,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 2, str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTimeEnd.dwYear,
            lpSpan->struTimeEnd.dwMonth,
            lpSpan->struTimeEnd.dwDay,
            lpSpan->struTimeEnd.dwHour,
            lpSpan->struTimeEnd.dwMinute,
            lpSpan->struTimeEnd.dwSecond);
            m_listSpan.SetItemText(m_nCurSelSpan, 3, str);
    }
    else if(0 == strcmp(strPlanType,"weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if(nSel == CB_ERR)
        {
            return;
        }
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].dwVolume = m_dwVolum;
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwYear = m_dtDate.GetYear();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMonth = m_dtDate.GetMonth();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwDay = m_dtDate.GetDay();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwHour = m_dtTime.GetHour();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMinute = m_dtTime.GetMinute();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwSecond = m_dtTime.GetSecond();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwYear = m_dtDateEnd.GetYear();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwMonth = m_dtDateEnd.GetMonth();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwDay = m_dtDateEnd.GetDay();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwHour = m_dtTimeEnd.GetHour();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwMinute = m_dtTimeEnd.GetMinute();
        m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwSecond = m_dtTimeEnd.GetSecond();

        NET_DVR_VOLUME_SPAN *lpSpan = &m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan];
        
        str.Format("%d",lpSpan->dwVolume);
        m_listSpan.SetItemText(m_nCurSelSpan,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 2, str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTimeEnd.dwYear,
            lpSpan->struTimeEnd.dwMonth,
            lpSpan->struTimeEnd.dwDay,
            lpSpan->struTimeEnd.dwHour,
            lpSpan->struTimeEnd.dwMinute,
            lpSpan->struTimeEnd.dwSecond);
            m_listSpan.SetItemText(m_nCurSelSpan, 3, str);
        
    }
}


void CDlgInfoDiffusionVolum::UpdateList()
{
    m_cmbPlanType.SetCurSel(m_cmbPlanType.FindString(-1,m_struVolumeCfg.struVolumePlan.sPlanType));
    OnSelchangeComboPlanType();
    if(0 == strcmp(m_struVolumeCfg.szOperType,"byTerminal"))
    {
        m_listTerminal.DeleteAllItems();
        CString str;
        for(int nTer = 0;nTer < m_struVolumeCfg.dwTerminalNo;nTer++)
        {
            str.Format("%d",nTer+1);
            m_listTerminal.InsertItem(nTer,str);
            str.Format("%d",m_struVolumeCfg.dwListTerminal[nTer]);
            m_listTerminal.SetItemText(nTer,1,str);
        }
    }
    else if(0 == strcmp(m_struVolumeCfg.szOperType,"byGroup"))
    {
        m_listGroup.DeleteAllItems();
        CString str;
        for(int nGroup = 0;nGroup < m_struVolumeCfg.dwGroupNo;nGroup++)
        {
            str.Format("%d",nGroup+1);
            m_listGroup.InsertItem(nGroup,str);
            str.Format("%d",m_struVolumeCfg.dwListGroup[nGroup]);
            m_listGroup.SetItemText(nGroup,1,str);
        }
    }
    UpdateData(FALSE);

}
void CDlgInfoDiffusionVolum::InitVolumePlanList()
{
    DWORD dwExStyle = m_listSpan.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
    m_listSpan.SetExtendedStyle(dwExStyle);
    
    char szLan[512] = {0};
    g_StringLanType(szLan, "序号", "Index");
    m_listSpan.InsertColumn(0, szLan);
    m_listSpan.SetColumnWidth(0, 40);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "音量", "Volume");
    m_listSpan.InsertColumn(1, szLan);
    m_listSpan.SetColumnWidth(1, 80);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "开始时间", "Start Time");
    m_listSpan.InsertColumn(2, szLan);
    m_listSpan.SetColumnWidth(2, 120);

    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "结束时间", "Start Time");
    m_listSpan.InsertColumn(3, szLan);
    m_listSpan.SetColumnWidth(3, 120);
    
    dwExStyle = m_listGroup.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
    m_listGroup.SetExtendedStyle(dwExStyle);
    
    g_StringLanType(szLan, "序号", "Index");
    m_listGroup.InsertColumn(0, szLan);
    m_listGroup.SetColumnWidth(0, 60);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "终端组编号", "Group No.");
    m_listGroup.InsertColumn(1, szLan);
    m_listGroup.SetColumnWidth(1, 80);
    
    dwExStyle = m_listTerminal.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
    m_listTerminal.SetExtendedStyle(dwExStyle);
    g_StringLanType(szLan, "序号", "Index");
    m_listTerminal.InsertColumn(0, szLan);
    m_listTerminal.SetColumnWidth(0, 60);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "终端编号", "Terminal No.");
    m_listTerminal.InsertColumn(1, szLan);
	m_listTerminal.SetColumnWidth(1, 100);


}
void CDlgInfoDiffusionVolum::RefreshVolumeSpanList(NET_DVR_VOLUME_PLAN *lpVolume, CString strPlanType, int nWeekday/* = -1当strPlanType为weekly时有效*/)
{
    if(lpVolume == NULL)
    {
        return;
    }
    m_listSpan.DeleteAllItems();
    int nSpanCnt = 0;
    CString str;
    if(0 == strcmp(strPlanType,"daily"))
    {
        for(nSpanCnt = 0;nSpanCnt < MAX_SPANS_A_DAY;nSpanCnt++)
        {
            NET_DVR_VOLUME_SPAN *lpSpan = &lpVolume->struDailyPlan[nSpanCnt];
            if(0 == lpSpan->dwSpanID)
            {
                break;
            }
            str.Format("%d",nSpanCnt+1);
            m_listSpan.InsertItem(nSpanCnt,str);
            str.Format("%d",lpSpan->dwVolume);
            m_listSpan.SetItemText(nSpanCnt,1,str);
            str.Format("%04d-%02d-%02d %02d:%02d:%02d",
                lpSpan->struTime.dwYear,
                lpSpan->struTime.dwMonth,
                lpSpan->struTime.dwDay,
                lpSpan->struTime.dwHour,
                lpSpan->struTime.dwMinute,
                lpSpan->struTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 2, str);
            str.Format("%04d-%02d-%02d %02d:%02d:%02d",
                lpSpan->struTimeEnd.dwYear,
                lpSpan->struTimeEnd.dwMonth,
                lpSpan->struTimeEnd.dwDay,
                lpSpan->struTimeEnd.dwHour,
                lpSpan->struTimeEnd.dwMinute,
                lpSpan->struTimeEnd.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 3, str);
        }
    }
    else if(0 == strcmp(strPlanType,"weekly"))
    {
        if(nWeekday == -1)
        {
            return;
        }
        for(nSpanCnt = 0;nSpanCnt < MAX_SPANS_A_DAY;nSpanCnt++)
        {
            NET_DVR_VOLUME_SPAN *lpSpan = &lpVolume->struWeekyPlan[nWeekday].struSpanList[nSpanCnt];
            if(0 == lpSpan->dwSpanID)
            {
                break;
            }
            str.Format("%d",nSpanCnt+1);
            m_listSpan.InsertItem(nSpanCnt,str);
            str.Format("%d",lpSpan->dwVolume);
            m_listSpan.SetItemText(nSpanCnt,1,str);
            str.Format("%04d-%02d-%02d %02d:%02d:%02d",
                lpSpan->struTime.dwYear,
                lpSpan->struTime.dwMonth,
                lpSpan->struTime.dwDay,
                lpSpan->struTime.dwHour,
                lpSpan->struTime.dwMinute,
                lpSpan->struTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 2, str);
            str.Format("%04d-%02d-%02d %02d:%02d:%02d",
                lpSpan->struTimeEnd.dwYear,
                lpSpan->struTimeEnd.dwMonth,
                lpSpan->struTimeEnd.dwDay,
                lpSpan->struTimeEnd.dwHour,
                lpSpan->struTimeEnd.dwMinute,
                lpSpan->struTimeEnd.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 3, str);
        }
    }
    

}

void CDlgInfoDiffusionVolum::OnSelchangeComboPlanType() 
{
	// TODO: Add your control notification handler code here
    int nSel = m_cmbPlanType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType ;
    m_cmbPlanType.GetLBText(nSel,strPlanType);
    if(0 == strcmp(strPlanType,"daily"))
    {
        GetDlgItem(IDC_COMBO_WEEKDAY)->EnableWindow(FALSE);
        RefreshVolumeSpanList(&m_struVolumeCfg.struVolumePlan,strPlanType);
    }
    else if(0 == strcmp(strPlanType,"weekly"))
    {
        GetDlgItem(IDC_COMBO_WEEKDAY)->EnableWindow(TRUE);
        m_cmbWeekday.SetCurSel(0);
        OnSelchangeComboWeekday();
    }
}

void CDlgInfoDiffusionVolum::OnSelchangeComboWeekday() 
{
	// TODO: Add your control notification handler code here
    int nSel = m_cmbPlanType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType ;
    m_cmbPlanType.GetLBText(nSel,strPlanType);
    nSel = m_cmbWeekday.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    RefreshVolumeSpanList(&m_struVolumeCfg.struVolumePlan,strPlanType,nSel);
}

BOOL CDlgInfoDiffusionVolum::OnInitDialog() 
{
	CDialog::OnInitDialog();
    InitVolumePlanList();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionVolum::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
    if(m_pOutputXmlBuffer!=NULL)
    {
        delete[] m_pOutputXmlBuffer;
        m_pOutputXmlBuffer = NULL;
    }

}


void CDlgInfoDiffusionVolum::OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_listSpan.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelSpan = m_listSpan.GetNextSelectedItem(pos);

        if(0==strcmp(m_struVolumeCfg.struVolumePlan.sPlanType,"daily"))
        {
            m_dwVolum = m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].dwVolume;
            m_dtDate.SetDate(m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwYear,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwMonth,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwDay);
            m_dtTime.SetTime(m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwHour,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwMinute,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTime.dwSecond);
            m_dtDateEnd.SetDate(m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwYear,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwMonth,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwDay);
            m_dtTimeEnd.SetTime(m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwHour,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwMinute,
                m_struVolumeCfg.struVolumePlan.struDailyPlan[m_nCurSelSpan].struTimeEnd.dwSecond);
        }
        else if(0 == strcmp(m_struVolumeCfg.struVolumePlan.sPlanType,"weekly"))
        {

            int nSel = m_cmbWeekday.GetCurSel();
            if(nSel == CB_ERR)
            {
                return;
            }
            m_dwVolum = m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].dwVolume;
            m_dtDate.SetDate(m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwYear,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMonth,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwDay);
            m_dtTime.SetTime(m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwHour,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMinute,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwSecond);

           
            m_dtDateEnd.SetDate(m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwYear,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwMonth,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwDay);
            m_dtTimeEnd.SetTime(m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwHour,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwMinute,
                m_struVolumeCfg.struVolumePlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTimeEnd.dwSecond);
            
        }
        
    }
    UpdateData(FALSE);
	*pResult = 0;
}

void CDlgInfoDiffusionVolum::OnBtnTerAdd() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString str;
    int nIndex = m_listTerminal.GetItemCount();
    str.Format("%d",nIndex+1);
    m_listTerminal.InsertItem(nIndex,str);
    str.Format("%d",m_dwTerminalId);
    m_listTerminal.SetItemText(nIndex,1,str);
    m_listTerminal.SetItemState(m_nCurSelTerminal,0,-1);
    m_listTerminal.SetItemState(nIndex,LVIS_SELECTED,LVIS_SELECTED);
    m_listTerminal.SetFocus();
    m_nCurSelTerminal = nIndex;
    m_struVolumeCfg.dwListTerminal[nIndex] = m_dwTerminalId;
    m_struVolumeCfg.dwTerminalNo++;
}

void CDlgInfoDiffusionVolum::OnBtnTerDel() 
{
	// TODO: Add your control notification handler code here
    for(int nTerminal = m_nCurSelTerminal;nTerminal < m_listTerminal.GetItemCount();nTerminal++)
    {
        m_struVolumeCfg.dwListTerminal[nTerminal] = m_struVolumeCfg.dwListTerminal[nTerminal+1];
        m_listTerminal.SetItemText(nTerminal, 1, m_listTerminal.GetItemText(nTerminal+1, 1));
    }
    m_struVolumeCfg.dwListTerminal[m_listTerminal.GetItemCount()-1] = 0;
    m_listTerminal.DeleteItem(m_listTerminal.GetItemCount()-1);
    m_nCurSelTerminal = -1;
    m_struVolumeCfg.dwTerminalNo--;
}

void CDlgInfoDiffusionVolum::OnBtnTerMod() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString str;
    str.Format("%d",m_dwTerminalId);
    m_listTerminal.SetItemText(m_nCurSelTerminal,1,str);
    m_struVolumeCfg.dwListTerminal[m_nCurSelTerminal] = m_dwTerminalId;
}

void CDlgInfoDiffusionVolum::OnBtnVolueGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString strCommand;
    strCommand.Format("GET /ISAPI/Publish/TerminalMgr/volumePlanCfg/%d/volumePlan\r\n",m_dwGetID);
    NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    
    char szStatusBuff[1024] = {0};
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
    struOutputParam.dwOutBufferSize = MAX_LEN_XML;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);
    
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    
    memset(&m_struVolumeCfg.struVolumePlan,0,sizeof(m_struVolumeCfg.struVolumePlan));
    m_struVolumeCfg.struVolumePlan.dwSize = sizeof(m_struVolumeCfg.struVolumePlan);
    ConvertVolumePlanParamsXmlToStru(m_pOutputXmlBuffer, &m_struVolumeCfg.struVolumePlan);
    UpdateList();
    
    UpdateData(FALSE);
}

void CDlgInfoDiffusionVolum::OnBtnVolumeSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struVolumeCfg.dwSize = sizeof(m_struVolumeCfg);
    int nSel = m_cmbPlanType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType;
    m_cmbPlanType.GetLBText(nSel,strPlanType);
    strcpy(m_struVolumeCfg.struVolumePlan.sPlanType,strPlanType);
    nSel = m_cmbOperType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strOperType;
    m_cmbOperType.GetLBText(nSel,strOperType);
    strcpy(m_struVolumeCfg.szOperType,strOperType);
    char *pInputBuff = NULL;
    DWORD dwInputSize = 0;
    ConvertVolumePlanParamStruToXml(&m_struVolumeCfg,&pInputBuff,dwInputSize);
    
    CString strCommand;
    strCommand.Format("PUT /ISAPI/Publish/TerminalMgr/volumePlanCfg\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;
    
    char szStatusBuff[1024] = {0};
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);
    
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    
    
    pInputBuff = NULL;
    
    UpdateData(FALSE);
    
}

void CDlgInfoDiffusionVolum::OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_listGroup.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelGroup = m_listGroup.GetNextSelectedItem(pos);
        m_dwGroupId = m_struVolumeCfg.dwListGroup[m_nCurSelGroup];
        UpdateData(FALSE);
    }
	*pResult = 0;
}

void CDlgInfoDiffusionVolum::OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
        m_dwTerminalId = m_struVolumeCfg.dwListTerminal[m_nCurSelTerminal];
        UpdateData(FALSE);
    }
	*pResult = 0;
}

void CDlgInfoDiffusionVolum::OnBtnGroupAdd() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString str;
    int nIndex = m_listGroup.GetItemCount();
    str.Format("%d",nIndex+1);
    m_listGroup.InsertItem(nIndex,str);
    str.Format("%d",m_dwGroupId);
    m_listGroup.SetItemText(nIndex,1,str);
    m_listGroup.SetItemState(m_nCurSelGroup,0,-1);
    m_listGroup.SetItemState(nIndex,LVIS_SELECTED,LVIS_SELECTED);
    m_listGroup.SetFocus();
    m_nCurSelGroup = nIndex;
    m_struVolumeCfg.dwListGroup[nIndex] = m_dwGroupId;
    m_struVolumeCfg.dwGroupNo++;
}

void CDlgInfoDiffusionVolum::OnBtnGroupDel() 
{
	// TODO: Add your control notification handler code here
    for(int nGroup = m_nCurSelGroup;nGroup < m_listGroup.GetItemCount();nGroup++)
    {
        m_struVolumeCfg.dwListGroup[nGroup]=m_struVolumeCfg.dwListGroup[nGroup+1];
        m_listGroup.SetItemText(nGroup, 1, m_listGroup.GetItemText(nGroup+1, 1));
    }
    m_struVolumeCfg.dwListGroup[m_listGroup.GetItemCount()-1] = 0;
    m_listGroup.DeleteItem(m_listGroup.GetItemCount()-1);
    m_nCurSelGroup = -1;
    m_struVolumeCfg.dwGroupNo--;
}

void CDlgInfoDiffusionVolum::OnBtnGroupMod() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString str;
    str.Format("%d",m_dwGroupId);
    m_listGroup.SetItemText(m_nCurSelGroup,1,str);
    m_struVolumeCfg.dwListGroup[m_nCurSelGroup] = m_dwGroupId;
}
