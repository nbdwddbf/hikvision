// PtzControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "PtzControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
   
/////////////////////////////////////////////////////////////////////////////
// CPtzControl dialog
CPtzControl *g_pTestDlg;
UINT Proc(LPVOID pParam)
{
    DWORD dwChannel = 0;
    int k = 21;
    int i = 1;
    int j = 1;
    DWORD h = 1;
    
    while (1)
    {
        //for(int k = 21; k < 25; k++)
            for(i = 1; i < 17; i++)
                for(j = 1; j < 9; j++)              
                    for(h = 1; h < 8; h++)
                    {
                        dwChannel = (dwChannel >> 16) | j;
                        dwChannel = dwChannel << 16;
                        dwChannel |= i;                        
                        if (NET_DVR_PTZControlWithSpeed_Other(g_pTestDlg->m_lServerID, dwChannel, k, 0, h)) 
                        {
                            //TRACE("send ptz control failed");
                            TRACE("dwchannel = %d;k = %d; h = %d\n", dwChannel, k, h);
                        }
                        else
                        {
                            TRACE("dwchannel = %d;k = %d; h = %d\n", dwChannel, k, h);
                            TRACE("ptz control failed!");
                        }

                        k = rand() % 4 + 21;
                        
//                         if (++k > 25)
//                         {
//                             k = 21;
//                         }
                        dwChannel = 0;
                        
                        //Sleep(10);
                    }  
                    
                    i = 1;
                    j = 1;
                    h = 1;
    }
}

CPtzControl::CPtzControl(CWnd* pParent /*=NULL*/)
	: CDialog(CPtzControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPtzControl)
	m_bWithSpeed = FALSE;
	//}}AFX_DATA_INIT
}


void CPtzControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPtzControl)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMBO_485ADDRESS, m_AddressCtrl);
	DDX_Control(pDX, IDC_COMBO_SPEED, m_SpeedCtrl);
	DDX_Control(pDX, IDC_COMBO_485PORT, m_PortCtrl);
	DDX_Check(pDX, IDC_CHECK_WITHSPEED, m_bWithSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPtzControl, CDialog)
	//{{AFX_MSG_MAP(CPtzControl)
	ON_BN_CLICKED(IDC_BTN_LEFT, OnBtnLeft)
	ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_STOPPTZ, OnBtnStopptz)
	ON_BN_CLICKED(IDC_BTN_RIGHT, OnBtnRight)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtzControl message handlers

void CPtzControl::OnBtnLeft() 
{
	// TODO: Add your control notification handler code here
	   UpdateData(TRUE);
	   
	   if (m_lServerID < 0)
	   {
		   MessageBox("not login");
		   return;
	   }
	   
	   DWORD dwChannel = 0;
	   dwChannel = (dwChannel >> 16) | m_PortCtrl.GetCurSel() + 1;
	   dwChannel = dwChannel << 16;
	   dwChannel |= m_AddressCtrl.GetCurSel() + 1;
	   if (NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, PAN_LEFT, 0, m_SpeedCtrl.GetCurSel() + 1)) 
	   {
		   MessageBox("success");
	   }
	   else
	   {
		   MessageBox("failed");
	   }
}

void CPtzControl::OnBtnUp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
    if (m_lServerID < 0)
    {
        MessageBox("not login");
        return;
    }
	
    DWORD dwChannel = 0;
    dwChannel = (dwChannel >> 16) | m_PortCtrl.GetCurSel() + 1;
    dwChannel = dwChannel << 16;
    dwChannel |= m_AddressCtrl.GetCurSel() + 1;
    if (NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, TILT_UP, 0, m_SpeedCtrl.GetCurSel() + 1)) 
    {
        MessageBox("success");
    }
    else
    {
        MessageBox("failed");
    }
   
    m_List.AddString("failed");
    UpdateData(FALSE);
}

void CPtzControl::OnBtnStopptz() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
    if (m_lServerID < 0)
    {
        MessageBox("not login");
        return;
    }
    
    DWORD dwChannel = 0;
    dwChannel = (dwChannel >> 16) | m_PortCtrl.GetCurSel() + 1;
    dwChannel = dwChannel << 16;
    dwChannel |= m_AddressCtrl.GetCurSel() + 1;
    NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, PAN_RIGHT, 1, m_SpeedCtrl.GetCurSel() + 1);
    Sleep(50);
    NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, PAN_LEFT, 1, m_SpeedCtrl.GetCurSel() + 1);
    Sleep(50);
    NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, TILT_DOWN, 1, m_SpeedCtrl.GetCurSel() + 1);
    Sleep(50);
    NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, TILT_UP, 1, m_SpeedCtrl.GetCurSel() + 1);
}
  
void CPtzControl::OnBtnRight() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_lServerID < 0)
	{
		MessageBox("not login");
		return;
	}
	
	DWORD dwChannel = 0;
	dwChannel = (dwChannel >> 16) | m_PortCtrl.GetCurSel() + 1;
	dwChannel = dwChannel << 16;
	dwChannel |= m_AddressCtrl.GetCurSel() + 1;
	if (NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, PAN_RIGHT, 0, m_SpeedCtrl.GetCurSel() + 1)) 
	{
		MessageBox("success");
	}
	else
	{
		MessageBox("failed");
	}
}

void CPtzControl::OnBtnDown() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
    if (m_lServerID < 0)
    {
        MessageBox("not login");
        return;
    }
    
    DWORD dwChannel = 0;
    dwChannel = (dwChannel >> 16) | m_PortCtrl.GetCurSel() + 1;
    dwChannel = dwChannel << 16;
    dwChannel |= m_AddressCtrl.GetCurSel() + 1;
    if (NET_DVR_PTZControlWithSpeed_Other(m_lServerID, dwChannel, TILT_DOWN, 0, m_SpeedCtrl.GetCurSel() + 1)) 
    {
        MessageBox("success");
    }
    else
    {
        MessageBox("failed");
    }
}

void CPtzControl::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lServerID < 0)
    {
        MessageBox("not login");
        return;
    }
    DWORD dwThreadID;
    if (m_Threadhandle == NULL)
    {
        m_Threadhandle = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(Proc), this, 0, &dwThreadID);
    }
    else
    {
		g_StringLanType(szLan, "已经开始发送", "Sending");
        MessageBox(szLan);
        return;
    }
    
	
    if (m_Threadhandle == NULL)
    {
		g_StringLanType(szLan, "创建发送线程失败", "Create send thread fail!");
        MessageBox(szLan);
        return;
    }
    
    g_StringLanType(szLan, "成功", "Success");
	MessageBox(szLan);
}

void CPtzControl::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	if (m_Threadhandle)
    {
        TerminateThread(m_Threadhandle, 0);
    }
    CloseHandle(m_Threadhandle);
    m_Threadhandle = NULL;
}

BOOL CPtzControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_pTestDlg = this;

	CString tmp;
	
	m_PortCtrl.ResetContent();
	for (int i = 1; i < 9; i++)
	{
		tmp.Format("%d", i);
		m_PortCtrl.AddString(tmp);
	}

	m_PortCtrl.SetCurSel(0);
	m_AddressCtrl.SetCurSel(0);
	
    m_Threadhandle = NULL;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPtzControl::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_Threadhandle)
    {
        TerminateThread(m_Threadhandle, 0);
    }
    CloseHandle(m_Threadhandle);
    m_Threadhandle = NULL;
}
