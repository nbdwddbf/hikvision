// DlgVcaResetCounterCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaResetCounterCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaResetCounterCfg dialog


CDlgVcaResetCounterCfg::CDlgVcaResetCounterCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaResetCounterCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaResetCounterCfg)
	m_bChkResetCounter = FALSE;
	m_byResetTimeHour = 0;
	m_byResetTimeMin = 0;
	m_byResetTimeSec = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1; 
    m_iDevIndex = -1; 
	m_iVcaChan = 0;
    m_bHideGetCtrl = FALSE;
	memset(&m_struResetCounterCfg, 0, sizeof(m_struResetCounterCfg));
}


void CDlgVcaResetCounterCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaResetCounterCfg)
	DDX_Control(pDX, IDC_COMBO_MODE, m_comMode);
	DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
	DDX_Check(pDX, IDC_CHK_RESET_COUNTER, m_bChkResetCounter);
	DDX_Text(pDX, IDC_RESET_TIME_HOUR, m_byResetTimeHour);
	DDX_Text(pDX, IDC_RESET_TIME_MIN, m_byResetTimeMin);
	DDX_Text(pDX, IDC_RESET_TIME_SEC, m_byResetTimeSec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaResetCounterCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaResetCounterCfg)
	ON_BN_CLICKED(IDC_TIME_OK2, OnTimeOk2)
	ON_BN_CLICKED(IDC_TIME_COPY2, OnTimeCopy2)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBOCOPYTIME, OnSelchangeCombocopytime)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaResetCounterCfg message handlers
BOOL CDlgVcaResetCounterCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    if (m_bHideGetCtrl)
    {
        GetDlgItem(IDC_BTN_GET)->ShowWindow(SW_HIDE);
    }
	//OnBtnGet();
	return TRUE;
}

/*********************************************************
Function:	F_TimeTest
Desc:		Check Fortify time
Input:	
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaResetCounterCfg::F_TimeTest()
{
	int i = 0;
	int j = 0;
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_byResetTimeHour < 0) || (m_byResetTimeHour > 24) )
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_byResetTimeMin < 0) || (m_byResetTimeMin > 60) )
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_byResetTimeSec < 0) || (m_byResetTimeSec > 60) )
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	
	return TRUE;
}

void CDlgVcaResetCounterCfg::SetTimeToWnd(NET_DVR_TIME_EX const *pTime)
{
    m_byResetTimeHour = pTime->byHour;
	m_byResetTimeMin = pTime->byMinute;
	m_byResetTimeSec = pTime->bySecond;
}

void CDlgVcaResetCounterCfg::GetTimeFromWnd(NET_DVR_TIME_EX *pTime)
{
    pTime->byHour = m_byResetTimeHour;
	pTime->byMinute = m_byResetTimeMin;
	pTime->bySecond = m_byResetTimeSec;
}

void CDlgVcaResetCounterCfg::OnTimeOk2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    GetTimeFromWnd(&m_struResetCounterCfg.struTime[i]);
}

void CDlgVcaResetCounterCfg::OnTimeCopy2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int j;
    int i = m_comboWeekday.GetCurSel();
    int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
    
    if(m_nCopyTime == -1)
    {
        for(j=0; j<MAX_DAYS; j++)
        {
            if(j == i)
                continue;
            memcpy(&(m_struResetCounterCfg.struTime[j]), &(m_struResetCounterCfg.struTime[i]), sizeof(NET_DVR_TIME_EX));
        }
    }
    else
    {
        memcpy(&(m_struResetCounterCfg.struTime[m_nCopyTime]), &(m_struResetCounterCfg.struTime[i]), sizeof(NET_DVR_TIME_EX));
    }
}

void CDlgVcaResetCounterCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
    DWORD dwReturn;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_RESET_COUNTER, m_iVcaChan, &m_struResetCounterCfg, sizeof(m_struResetCounterCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RESET_COUNTER Fail");
        g_StringLanType(szLan, "获取定时重置数据配置失败", "Fail to get reset counter config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RESET_COUNTER Success");
    }

	m_bChkResetCounter = m_struResetCounterCfg.byEnable;
	m_comboWeekday.SetCurSel(0);
    m_comMode.SetCurSel(m_struResetCounterCfg.byMode);
	SetTimeToWnd(&m_struResetCounterCfg.struTime[0]);
	UpdateData(FALSE);
}

void CDlgVcaResetCounterCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struResetCounterCfg.dwSize =  sizeof(m_struResetCounterCfg);
    m_struResetCounterCfg.byEnable = m_bChkResetCounter;
    m_struResetCounterCfg.byMode = m_comMode.GetCurSel();
    char szLan[128] = {0};
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_RESET_COUNTER, m_iVcaChan, &m_struResetCounterCfg, sizeof(m_struResetCounterCfg)))
    {
//		char szLan[16] = {0};
		sprintf(szLan, "Errcode: %d", NET_DVR_GetLastError());
// 		MessageBox(szLan);
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RESET_COUNTER");
//         g_StringLanType(szLan, "设置定时重置数据配置失败", "Fail to set reset counter config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RESET_COUNTER");
    }
}

void CDlgVcaResetCounterCfg::OnSelchangeCombocopytime() 
{
	// TODO: Add your control notification handler code here
// 	int	i = m_comboWeekday.GetCurSel();	
//     SetTimeToWnd(&m_struResetCounterCfg.struTime[i]);
//     UpdateData(FALSE);
}

void CDlgVcaResetCounterCfg::OnSelchangeComboweekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int	i = m_comboWeekday.GetCurSel();	
    SetTimeToWnd(&m_struResetCounterCfg.struTime[i]);
    UpdateData(FALSE);

}
