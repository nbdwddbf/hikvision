/*******************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd. 
文  件：	DlgCheckTime.cpp
开发单位：	杭州海康威视
编  写：	shizhiping
日  期：	2009.5
描  述：	校时对话框
修  改：	
********************************************************/
#include "stdafx.h"
#include "Manage.h"
#include "DlgCheckTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckTime dialog


CDlgCheckTime::CDlgCheckTime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCheckTime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCheckTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCheckTime)
	DDX_DateTimeCtrl(pDX, IDC_CHECK_TIME, m_checkTime);
	DDX_DateTimeCtrl(pDX, IDC_CHECK_DATE, m_checkDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCheckTime, CDialog)
	//{{AFX_MSG_MAP(CDlgCheckTime)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_TIME, OnButtonCheckTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckTime message handlers

/*************************************************
函数名:    	OnButtonCheckTime
函数描述:	校时
输入参数:   
输出参数:   			
返回值:		
*************************************************/
void CDlgCheckTime::OnButtonCheckTime() 
{	
	UpdateData(TRUE);
    NET_DVR_TIME CurTime;
    CurTime.dwYear = m_checkDate.GetYear();
    CurTime.dwMonth = m_checkDate.GetMonth();
    CurTime.dwDay = m_checkDate.GetDay();
    CurTime.dwHour = m_checkTime.GetHour();
    CurTime.dwMinute = m_checkTime.GetMinute();
	CurTime.dwSecond = m_checkTime.GetSecond();
	LONG lLoginID = g_pMainDlg->m_struDeviceInfo.lLoginID;
	if(lLoginID == -1)
	{
		MessageBox("请先登录");
		return;
	}
	BOOL ret = NET_DVR_SetDVRConfig(lLoginID, NET_DVR_SET_TIMECFG, 0, &CurTime, sizeof(NET_DVR_TIME));
	if(ret)
	{
		MessageBox("校时成功!");
	}
	else
	{
		MessageBox("校时失败!");
	}
	
}
