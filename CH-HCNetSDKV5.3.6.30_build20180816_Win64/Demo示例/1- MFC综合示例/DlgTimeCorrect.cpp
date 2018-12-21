// DlgTimeCorrect.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTimeCorrect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgTimeCorrect dialog


DlgTimeCorrect::DlgTimeCorrect(CWnd* pParent /*=NULL*/)
	: CDialog(DlgTimeCorrect::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgTimeCorrect)
	m_Date = COleDateTime::GetCurrentTime();
	m_Time = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void DlgTimeCorrect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgTimeCorrect)
	DDX_DateTimeCtrl(pDX, IDC_STATIC_DATE, m_Date);
	DDX_DateTimeCtrl(pDX, IDC_STATIC_TIME, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgTimeCorrect, CDialog)
	//{{AFX_MSG_MAP(DlgTimeCorrect)
	ON_BN_CLICKED(IDC_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgTimeCorrect message handlers

void DlgTimeCorrect::OnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    NET_DVR_TIME struTime = {0};
    struTime.dwYear = m_Date.GetYear();
    struTime.dwMonth = m_Date.GetMonth();
    struTime.dwDay = m_Date.GetDay();    
    struTime.dwHour = m_Time.GetHour();
    struTime.dwMinute = m_Time.GetMinute();
    struTime.dwSecond = m_Time.GetSecond();

    DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[128] = {0};
    if(NET_DVR_SetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_SET_TIMECORRECT,0,&struTime,sizeof(struTime)))
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_TIMECORRECT SUCC");
        g_StringLanType(szLan, "设置成功", "NET_DVR_SET_TIMECORRECT successed!");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_TIMECORRECT Failed");
        g_StringLanType(szLan, "设置失败", "NET_DVR_SET_TIMECORRECT failed!");
        AfxMessageBox(szLan);
    }
	
}
