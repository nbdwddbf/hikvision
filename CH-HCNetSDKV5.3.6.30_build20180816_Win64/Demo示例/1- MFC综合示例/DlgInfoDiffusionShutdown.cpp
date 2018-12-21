// DlgInfoDiffusionShutdown.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionShutdown.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionShutdown dialog


CDlgInfoDiffusionShutdown::CDlgInfoDiffusionShutdown(CWnd* pParent /*=NULL*/)
: CDialog(CDlgInfoDiffusionShutdown::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgInfoDiffusionShutdown)
    m_tmDate = COleDateTime::GetCurrentTime();
    m_tmTime = COleDateTime::GetCurrentTime();
	m_dwGetID = 0;
	m_dwGroupId = 0;
	m_dwTerminalId = 0;
	//}}AFX_DATA_INIT
    
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    memset(&m_strSwitchCfg, 0, sizeof(m_strSwitchCfg));
    m_strSwitchCfg.dwSize = sizeof(m_strSwitchCfg);
    m_nCurSelSpan = -1;
    m_nCurSelGroup = -1;
    m_nCurSelTerminal = -1;
    m_pOutputXmlBuffer = new char[MAX_LEN_XML];
    memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
}


void CDlgInfoDiffusionShutdown::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionShutdown)
	DDX_Control(pDX, IDC_COMBO_PLAN_TYPE, m_cmbPlanType);
	DDX_Control(pDX, IDC_COMBO_OPERA_TYPE, m_cmbOperType);
	DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
	DDX_Control(pDX, IDC_LIST_GROUP, m_listGroup);
    DDX_Control(pDX, IDC_COMBO_SWITCH_TYPE, m_cmbSwitchType);
    DDX_Control(pDX, IDC_LIST_SPAN, m_listSpan);
    DDX_Control(pDX, IDC_COMBO_WEEKDAY, m_cmbWeekday);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_DATE, m_tmDate);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_TIME, m_tmTime);
	DDX_Text(pDX, IDC_EDIT_CFG_ID, m_dwGetID);
	DDX_Text(pDX, IDC_EDIT_GROUPID, m_dwGroupId);
	DDX_Text(pDX, IDC_EDIT_TER_ID, m_dwTerminalId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionShutdown, CDialog)
//{{AFX_MSG_MAP(CDlgInfoDiffusionShutdown)

ON_BN_CLICKED(IDC_BTN_PLAN_SPAN_ADD, OnBtnPlanSpanAdd)
ON_BN_CLICKED(IDC_BTN_PLAN_SPAN_DEL, OnBtnPlanSpanDel)
ON_BN_CLICKED(IDC_BTN_PLAN_SPAN_MOD, OnBtnPlanSpanMod)
ON_CBN_SELCHANGE(IDC_COMBO_PLAN_TYPE, OnSelchangeComboPlanType)
ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, OnSelchangeComboWeekday)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_SPAN, OnClickListSpan)
	ON_BN_CLICKED(IDC_BTN_GROUP_ADD, OnBtnGroupAdd)
	ON_BN_CLICKED(IDC_BTN_GROUP_DEL, OnBtnGroupDel)
	ON_BN_CLICKED(IDC_BTN_GROUP_MOD, OnBtnGroupMod)
	ON_BN_CLICKED(IDC_BTN_TER_ADD, OnBtnTerAdd)
	ON_BN_CLICKED(IDC_BTN_TER_DEL, OnBtnTerDel)
	ON_BN_CLICKED(IDC_BTN_TER_MOD, OnBtnTerMod)
	ON_NOTIFY(NM_CLICK, IDC_LIST_GROUP, OnClickListGroup)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, OnClickListTerminal)
	ON_BN_CLICKED(IDC_BTN_SWITCH_SET, OnBtnSwitchSet)
	ON_BN_CLICKED(IDC_BTN_SWITCH_GET, OnBtnSwitchGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionShutdown message handlers






void CDlgInfoDiffusionShutdown::OnBtnPlanSpanAdd() 
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
    strcpy(m_strSwitchCfg.struSwitchPlan.sPlanType, strPlanType);
    CString str;
    int nSpanIndex = -1;
    int nSpanCnt = 0;
    if(0 == strcmp(strPlanType,"daily"))
    {
        for(nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY;nSpanCnt++)
        {
            if(0 == m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanCnt].dwSpanID)
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
        
        nSel = m_cmbSwitchType.GetCurSel();
        if(nSel == CB_ERR)
        {
            return;
        }
        CString strSwitchType;
        m_cmbSwitchType.GetLBText(nSel,strSwitchType);
        NET_DVR_SWITCH_SPAN *lpSpan = &m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex];

        strcpy(m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].sSwitchType, strSwitchType);
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].dwSpanID = nSpanIndex+1;
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].struTime.dwYear = m_tmDate.GetYear();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].struTime.dwMonth = m_tmDate.GetMonth();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].struTime.dwDay = m_tmDate.GetDay();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].struTime.dwHour = m_tmTime.GetHour();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].struTime.dwMinute = m_tmTime.GetMinute();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanIndex].struTime.dwSecond = m_tmTime.GetSecond();

        strcpy(lpSpan->sSwitchType, strSwitchType);
        lpSpan->dwSpanID = nSpanIndex+1;
        lpSpan->struTime.dwYear = m_tmDate.GetYear();
        lpSpan->struTime.dwMonth = m_tmDate.GetMonth();
        lpSpan->struTime.dwDay = m_tmDate.GetDay();
        lpSpan->struTime.dwHour = m_tmTime.GetHour();
        lpSpan->struTime.dwMinute = m_tmTime.GetMinute();
        lpSpan->struTime.dwSecond = m_tmTime.GetSecond();
        
        str.Format("%d",nSpanIndex+1);
        m_listSpan.InsertItem(nSpanIndex,str);
        m_listSpan.SetItemState(nSpanIndex, 0, -1);
        m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
        m_listSpan.SetFocus();
        m_nCurSelSpan = nSpanIndex;
        str.Format("%s",lpSpan->sSwitchType);
        m_listSpan.SetItemText(nSpanIndex,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 2, str);
    }
    else if(0 == strcmp(strPlanType,"weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if(nSel == CB_ERR)
        {
            return;
        }
        m_cmbWeekday.GetLBText(nSel,m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].sWeekday);
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].dwDayID = nSel+1;
        nSpanIndex = -1;
        for(nSpanCnt = 0;nSpanCnt < MAX_SPANS_A_DAY;nSpanCnt++)
        {
            if(0 == m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanCnt].dwSpanID)
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
        int nSelType = m_cmbSwitchType.GetCurSel();
        if( nSelType == CB_ERR)
        {
            return;
        }
        CString strSwitchType;
        m_cmbSwitchType.GetLBText(nSelType,strSwitchType);
        strcpy(m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].sSwitchType, strSwitchType);
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].dwSpanID = nSpanIndex+1;
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwYear = m_tmDate.GetYear();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwMonth = m_tmDate.GetMonth();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwDay = m_tmDate.GetDay();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwHour = m_tmTime.GetHour();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwMinute = m_tmTime.GetMinute();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex].struTime.dwSecond = m_tmTime.GetSecond();
        
        NET_DVR_SWITCH_SPAN *lpSpan = &m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanIndex];
        str.Format("%d",nSpanIndex+1);
        m_listSpan.InsertItem(nSpanIndex,str);
        m_listSpan.SetItemState(nSpanIndex, 0, -1);
        m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
        m_listSpan.SetFocus();
        m_nCurSelSpan = nSpanIndex;
        
        str.Format("%s",lpSpan->sSwitchType);
        m_listSpan.SetItemText(nSpanIndex,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 2, str);
    }
}

void CDlgInfoDiffusionShutdown::OnBtnPlanSpanDel() 
{
    // TODO: Add your control notification handler code here
    if (m_nCurSelSpan < 0)
    {
        char szLan1[512] = {0};
        char szLan2[512] = {0};
        g_StringLanType(szLan1, "请选择计划时段", "Please choose a plan first.");
        g_StringLanType(szLan2, "定时开关机管理", "Shut down Management");
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
            memcpy(&m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanCnt], 
                &m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanCnt+1],
                sizeof(LPNET_DVR_SWITCH_SPAN));
            m_strSwitchCfg.struSwitchPlan.struDailyPlan[nSpanCnt].dwSpanID = nSpanCnt+1;
        }
        NET_DVR_SWITCH_SPAN *lpSpan = &m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_listSpan.GetItemCount()-1];
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
            memcpy(&m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanCnt], 
                &m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanCnt+1],
                sizeof(LPNET_DVR_SWITCH_SPAN));
            m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[nSpanCnt].dwSpanID = nSpanCnt+1;
        }
        NET_DVR_SWITCH_SPAN *lpSpan = &m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_listSpan.GetItemCount()-1];
        memset(lpSpan, 0, sizeof(*lpSpan));
        m_listSpan.DeleteItem(m_listSpan.GetItemCount()-1);
        if (m_listSpan.GetItemCount() == 0)
        {
            m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].dwDayID = 0;
        }
    }
}

void CDlgInfoDiffusionShutdown::OnBtnPlanSpanMod() 
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
    strcpy(m_strSwitchCfg.struSwitchPlan.sPlanType,strPlanType);
    nSel = m_cmbSwitchType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strSwitchType;
    m_cmbSwitchType.GetLBText(nSel,strSwitchType);
    CString str;
    
    if(0 == strcmp(strPlanType,"daily"))
    {
        NET_DVR_SWITCH_SPAN *lpSpan = &m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan];
        strcpy(m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].sSwitchType, strSwitchType);
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwYear = m_tmDate.GetYear();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwMonth = m_tmDate.GetMonth();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwDay = m_tmDate.GetDay();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwHour = m_tmTime.GetHour();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwMinute = m_tmTime.GetMinute();
        m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwSecond = m_tmTime.GetSecond();

        strcpy(lpSpan->sSwitchType,strSwitchType);
        lpSpan->struTime.dwYear = m_tmDate.GetYear();
        lpSpan->struTime.dwMonth = m_tmDate.GetMonth();
        lpSpan->struTime.dwDay = m_tmDate.GetDay();
        lpSpan->struTime.dwHour = m_tmTime.GetHour();
        lpSpan->struTime.dwMinute = m_tmTime.GetMinute();
        lpSpan->struTime.dwSecond = m_tmTime.GetSecond();
        
        str.Format("%s",lpSpan->sSwitchType);
        m_listSpan.SetItemText(m_nCurSelSpan,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 2, str);
    }
    else if(0 == strcmp(strSwitchType,"weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if(nSel == CB_ERR)
        {
            return;
        }
        NET_DVR_SWITCH_SPAN *lpSpan = &m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan];
        strcpy(m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].sSwitchType, strSwitchType);
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwYear = m_tmDate.GetYear();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMonth = m_tmDate.GetMonth();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwDay = m_tmDate.GetDay();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwHour = m_tmTime.GetHour();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMinute = m_tmTime.GetMinute();
        m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwSecond = m_tmTime.GetSecond();
        strcpy(lpSpan->sSwitchType,strSwitchType);
        lpSpan->struTime.dwYear = m_tmDate.GetYear();
        lpSpan->struTime.dwMonth = m_tmDate.GetMonth();
        lpSpan->struTime.dwDay = m_tmDate.GetDay();
        lpSpan->struTime.dwHour = m_tmTime.GetHour();
        lpSpan->struTime.dwMinute = m_tmTime.GetMinute();
        lpSpan->struTime.dwSecond = m_tmTime.GetSecond();
        
        str.Format("%s",lpSpan->sSwitchType);
        m_listSpan.SetItemText(m_nCurSelSpan,1,str);
        str.Format("%04d-%02d-%02d %02d:%02d:%02d",
            lpSpan->struTime.dwYear,
            lpSpan->struTime.dwMonth,
            lpSpan->struTime.dwDay,
            lpSpan->struTime.dwHour,
            lpSpan->struTime.dwMinute,
            lpSpan->struTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 2, str);
        
    }
    
}


void CDlgInfoDiffusionShutdown::OnSelchangeComboWeekday()
{
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
    RefreshSwitchSpanList(&m_strSwitchCfg.struSwitchPlan,strPlanType,nSel);
    
}

void CDlgInfoDiffusionShutdown::OnSelchangeComboPlanType()
{
   // m_cmbPlanType.SetCurSel(m_cmbPlanType.FindString(-1,m_strSwitchCfg.struSwitchPlan.sPlanType));

    int nSel = m_cmbPlanType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType ;
    m_cmbPlanType.GetLBText(nSel,strPlanType);
    if(0 == strcmp(m_strSwitchCfg.struSwitchPlan.sPlanType,"daily"))
    {
        GetDlgItem(IDC_COMBO_WEEKDAY)->EnableWindow(FALSE);
        RefreshSwitchSpanList(&m_strSwitchCfg.struSwitchPlan,m_strSwitchCfg.struSwitchPlan.sPlanType);
    }
    else if(0 == strcmp(m_strSwitchCfg.struSwitchPlan.sPlanType,"weekly"))
    {
        GetDlgItem(IDC_COMBO_WEEKDAY)->EnableWindow(TRUE);
        m_cmbWeekday.SetCurSel(0);
        OnSelchangeComboWeekday();
    }
    
}

void CDlgInfoDiffusionShutdown::UpdateList()
{
    m_cmbPlanType.SetCurSel(m_cmbPlanType.FindString(-1,m_strSwitchCfg.struSwitchPlan.sPlanType));

    int nSel = m_cmbOperType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strOperType;
    m_cmbOperType.GetLBText(nSel,strOperType);
    strcpy(m_strSwitchCfg.szOperType,strOperType);
    OnSelchangeComboPlanType();

    if(0 == strcmp(m_strSwitchCfg.szOperType,"byTerminal"))
    {
        m_listTerminal.DeleteAllItems();
        CString str;
        for(int nTer = 0;nTer < m_strSwitchCfg.dwTerminalNo;nTer++)
        {
            str.Format("%d",nTer+1);
            m_listTerminal.InsertItem(nTer,str);
            str.Format("%d",m_strSwitchCfg.dwListTerminal[nTer]);
            m_listTerminal.SetItemText(nTer,1,str);
        }
    }
    else if(0 == strcmp(m_strSwitchCfg.szOperType,"byGroup"))
    {
        m_listGroup.DeleteAllItems();
        CString str;
        for(int nGroup = 0;nGroup < m_strSwitchCfg.dwGroupNo;nGroup++)
        {
           str.Format("%d",nGroup+1);
           m_listGroup.InsertItem(nGroup,str);
           str.Format("%d",m_strSwitchCfg.dwListGroup[nGroup]);
           m_listGroup.SetItemText(nGroup,1,str);
        }
    }
    UpdateData(FALSE);
}
void CDlgInfoDiffusionShutdown::InitSwitchPlanList()
{
    DWORD dwExStyle = m_listSpan.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
    m_listSpan.SetExtendedStyle(dwExStyle);
    
    char szLan[512] = {0};
    g_StringLanType(szLan, "序号", "Index");
    m_listSpan.InsertColumn(0, szLan);
    m_listSpan.SetColumnWidth(0, 40);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "开关类型", "SwitchType");
    m_listSpan.InsertColumn(1, szLan);
    m_listSpan.SetColumnWidth(1, 80);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "时间", "Start Time");
    m_listSpan.InsertColumn(2, szLan);
    m_listSpan.SetColumnWidth(2, 120);
  

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
void CDlgInfoDiffusionShutdown::RefreshSwitchSpanList(NET_DVR_SWITCH_PLAN *lpSwitch, CString strPlanType, int nWeekday /*= -1当strPlanType为weekly时有效*/)
{
    if(lpSwitch == NULL)
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
            NET_DVR_SWITCH_SPAN *lpSpan = &lpSwitch->struDailyPlan[nSpanCnt];
            if(0 == lpSpan->dwSpanID)
            {
                break;
            }
            str.Format("%d",nSpanCnt+1);
            m_listSpan.InsertItem(nSpanCnt,str);
            str.Format("%s",lpSpan->sSwitchType);
            m_listSpan.SetItemText(nSpanCnt,1,str);
            str.Format("%04d-%02d-%02d %02d:%02d:%02d",
                lpSpan->struTime.dwYear,
                lpSpan->struTime.dwMonth,
                lpSpan->struTime.dwDay,
                lpSpan->struTime.dwHour,
                lpSpan->struTime.dwMinute,
                lpSpan->struTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 2, str);
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
            NET_DVR_SWITCH_SPAN *lpSpan = &lpSwitch->struWeekyPlan[nWeekday].struSpanList[nSpanCnt];
            if(0 == lpSpan->dwSpanID)
            {
                break;
            }
            str.Format("%d",nSpanCnt+1);
            m_listSpan.InsertItem(nSpanCnt,str);
            str.Format("%s",lpSpan->sSwitchType);
            m_listSpan.SetItemText(nSpanCnt,1,str);
            str.Format("%04d-%02d-%02d %02d:%02d:%02d",
                lpSpan->struTime.dwYear,
                lpSpan->struTime.dwMonth,
                lpSpan->struTime.dwDay,
                lpSpan->struTime.dwHour,
                lpSpan->struTime.dwMinute,
                lpSpan->struTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 2, str);
        }
    }
    
    
}

BOOL CDlgInfoDiffusionShutdown::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    InitSwitchPlanList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionShutdown::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
    delete[] m_pOutputXmlBuffer;
	m_pOutputXmlBuffer = NULL;

	
}

void CDlgInfoDiffusionShutdown::OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listSpan.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelSpan = m_listSpan.GetNextSelectedItem(pos);
        int nSel = m_cmbPlanType.GetCurSel();
        if(nSel == CB_ERR)
        {
            return;
        }
        CString strPlanType;
        m_cmbPlanType.GetLBText(nSel,strPlanType);
        if(0==strcmp(strPlanType,"daily"))
        {
           // m_cmbSwitchType.SetCurSel() = m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].sSwitchType;
            m_cmbSwitchType.SetCurSel(m_cmbSwitchType.FindString(-1,m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].sSwitchType));
            m_tmDate.SetDate(m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwYear,
                m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwMonth,
                m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwDay);
            m_tmTime.SetTime(m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwHour,
                m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwMinute,
                m_strSwitchCfg.struSwitchPlan.struDailyPlan[m_nCurSelSpan].struTime.dwSecond);
        }
        else if(0 == strcmp(strPlanType,"weekly"))
        {
            nSel = m_cmbWeekday.GetCurSel();
            if(nSel == CB_ERR)
            {
                return;
            }
           // m_cmbSwitchType.SetCurSel() = m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].sSwitchType;
            m_cmbWeekday.SetCurSel(m_cmbWeekday.FindString(-1,m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].sWeekday));
            m_cmbSwitchType.SetCurSel(m_cmbSwitchType.FindString(-1,m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].sSwitchType));
            m_tmDate.SetDate(m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwYear,
                m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMonth,
                m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwDay);
            m_tmTime.SetTime(m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwHour,
                m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwMinute,
                m_strSwitchCfg.struSwitchPlan.struWeekyPlan[nSel].struSpanList[m_nCurSelSpan].struTime.dwSecond);

        }

    }
    UpdateData(FALSE);
	*pResult = 0;
}


void CDlgInfoDiffusionShutdown::OnBtnGroupAdd() 
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
    m_strSwitchCfg.dwListGroup[nIndex] = m_dwGroupId;
    m_strSwitchCfg.dwGroupNo++;
    

}

void CDlgInfoDiffusionShutdown::OnBtnGroupDel() 
{
	// TODO: Add your control notification handler code here
	for(int nGroup = m_nCurSelGroup;nGroup < m_listGroup.GetItemCount();nGroup++)
    {
        m_strSwitchCfg.dwListGroup[nGroup]=m_strSwitchCfg.dwListGroup[nGroup+1];
        m_listGroup.SetItemText(nGroup, 1, m_listGroup.GetItemText(nGroup+1, 1));
    }
    m_strSwitchCfg.dwListGroup[m_listGroup.GetItemCount()-1] = 0;
    m_listGroup.DeleteItem(m_listGroup.GetItemCount()-1);
    m_nCurSelGroup = -1;
    m_strSwitchCfg.dwGroupNo--;
}

void CDlgInfoDiffusionShutdown::OnBtnGroupMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CString str;
    str.Format("%d",m_dwGroupId);
    m_listGroup.SetItemText(m_nCurSelGroup,1,str);
    m_strSwitchCfg.dwListGroup[m_nCurSelGroup] = m_dwGroupId;
}

void CDlgInfoDiffusionShutdown::OnBtnTerAdd() 
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
    m_strSwitchCfg.dwListTerminal[nIndex] = m_dwTerminalId;
    m_strSwitchCfg.dwTerminalNo++;
}

void CDlgInfoDiffusionShutdown::OnBtnTerDel() 
{
	// TODO: Add your control notification handler code here
	for(int nTerminal = m_nCurSelTerminal;nTerminal < m_listTerminal.GetItemCount();nTerminal++)
    {
        m_strSwitchCfg.dwListTerminal[nTerminal] = m_strSwitchCfg.dwListTerminal[nTerminal+1];
        m_listTerminal.SetItemText(nTerminal, 1, m_listTerminal.GetItemText(nTerminal+1, 1));
    }
    m_strSwitchCfg.dwListTerminal[m_listTerminal.GetItemCount()-1] = 0;
    m_listTerminal.DeleteItem(m_listTerminal.GetItemCount()-1);
    m_nCurSelTerminal = -1;
    m_strSwitchCfg.dwTerminalNo--;
}

void CDlgInfoDiffusionShutdown::OnBtnTerMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CString str;
    str.Format("%d",m_dwTerminalId);
    m_listTerminal.SetItemText(m_nCurSelTerminal,1,str);
    m_strSwitchCfg.dwListTerminal[m_nCurSelTerminal] = m_dwTerminalId;
}

void CDlgInfoDiffusionShutdown::OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listGroup.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelGroup = m_listGroup.GetNextSelectedItem(pos);
        m_dwGroupId = m_strSwitchCfg.dwListGroup[m_nCurSelGroup];
        UpdateData(FALSE);
    }
	*pResult = 0;
}

void CDlgInfoDiffusionShutdown::OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
        m_dwTerminalId = m_strSwitchCfg.dwListTerminal[m_nCurSelTerminal];
        UpdateData(FALSE);
    }
	*pResult = 0;
}

void CDlgInfoDiffusionShutdown::OnBtnSwitchSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_strSwitchCfg.dwSize = sizeof(m_strSwitchCfg);
    int nSel = m_cmbPlanType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strPlanType;
    m_cmbPlanType.GetLBText(nSel,strPlanType);
    strcpy(m_strSwitchCfg.struSwitchPlan.sPlanType,strPlanType);
    nSel = m_cmbOperType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strOperType;
    m_cmbOperType.GetLBText(nSel,strOperType);
    strcpy(m_strSwitchCfg.szOperType,strOperType);
    char *pInputBuff = NULL;
    DWORD dwInputSize = 0;
    ConvertPlanParamStruToXml(&m_strSwitchCfg,&pInputBuff,dwInputSize);
    
    CString strCommand;
    strCommand.Format("PUT /ISAPI/Publish/TerminalMgr/switchPlanCfg\r\n");
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
        //delete[] pInputBuff;
        //pInputBuff = NULL;
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    
    
    pInputBuff = NULL;
    
    UpdateData(FALSE);
    
}

void CDlgInfoDiffusionShutdown::OnBtnSwitchGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString strCommand;
    strCommand.Format("GET /ISAPI/Publish/TerminalMgr/switchPlanCfg/%d/switchPlan\r\n",m_dwGetID);
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
    
    memset(&m_strSwitchCfg.struSwitchPlan,0,sizeof(m_strSwitchCfg.struSwitchPlan));
    m_strSwitchCfg.struSwitchPlan.dwSize = sizeof(m_strSwitchCfg.struSwitchPlan);
    ConvertPlanParamsXmlToStru(m_pOutputXmlBuffer, &m_strSwitchCfg.struSwitchPlan);
    UpdateList();
    
    UpdateData(FALSE);

}
