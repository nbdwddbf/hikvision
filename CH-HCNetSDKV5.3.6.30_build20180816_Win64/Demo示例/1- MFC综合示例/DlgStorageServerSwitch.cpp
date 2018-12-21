// DlgStorageServerSwitch.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgStorageServerSwitch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStorageServerSwitch dialog


CDlgStorageServerSwitch::CDlgStorageServerSwitch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStorageServerSwitch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStorageServerSwitch)
	m_bAllAddInfoSwitch = FALSE;
	m_bAllPicSwitch = FALSE;
	//}}AFX_DATA_INIT

    m_iDevIndex = -1;
    m_lChannel = -1;
    m_lServerID = -1;
}


void CDlgStorageServerSwitch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStorageServerSwitch)
	DDX_Check(pDX, IDC_CHK_ADDINFO_SWITCH, m_bAllAddInfoSwitch);
	DDX_Check(pDX, IDC_CHK_PIC_SWITCH, m_bAllPicSwitch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStorageServerSwitch, CDialog)
	//{{AFX_MSG_MAP(CDlgStorageServerSwitch)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStorageServerSwitch message handlers

void CDlgStorageServerSwitch::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    int i = 0;
    NET_DVR_STORAGE_SERVER_SWITCH_CFG struServerSwitch = {0};
    struServerSwitch.dwSize = sizeof(NET_DVR_STORAGE_SERVER_SWITCH_CFG);
    if (m_bAllPicSwitch)
    {
        for (i = 0; i < MAX_PIC_SWITCH_STORAGE_SERVER; i++)
        {
            struServerSwitch.byPicEnable[i] = 1;
        }

    }
    else
    {
        for (i = 0; i < MAX_PIC_SWITCH_STORAGE_SERVER; i++)
        {
            struServerSwitch.byPicEnable[i] = 0;
        }
    }

    if (m_bAllAddInfoSwitch)
    {
        for (i = 0; i < MAX_INFO_SWITCH_STORAGE_SERVER; i++)
        {
            struServerSwitch.byAddInfoEnable[i] = 1;
        }
    }
    else
    {
        for (i = 0; i < MAX_INFO_SWITCH_STORAGE_SERVER; i++)
        {
            struServerSwitch.byAddInfoEnable[i] = 0;
        }
    }


    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_STORAGE_SERVER_SWITCH, m_lChannel, &struServerSwitch, sizeof(struServerSwitch)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_STORAGE_SERVER_SWITCH");
        return;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_STORAGE_SERVER_SWITCH");
        return;
    }	
}

void CDlgStorageServerSwitch::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

    NET_DVR_STORAGE_SERVER_SWITCH_CFG struServerSwitch = {0};
    DWORD dwReturn = 0;
    int i = 0;
    BOOL bEnable = FALSE;
    //BOOL bDistable = TRUE;

    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_STORAGE_SERVER_SWITCH, m_lChannel, &struServerSwitch, sizeof(struServerSwitch), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_STORAGE_SERVER_SWITCH");


        bEnable = TRUE;
        for (i = 0; i < MAX_PIC_SWITCH_STORAGE_SERVER; i++)
        {
            if (0 == struServerSwitch.byPicEnable[i])
            {
                bEnable = FALSE;
            } 
        }
        
        if(bEnable)
        {
            m_bAllPicSwitch = 1;
        }
        else
        {
            m_bAllPicSwitch = 0;
        }

        bEnable = TRUE;
        
        for (i = 0; i < MAX_PIC_SWITCH_STORAGE_SERVER; i++)
        {
            if (0 == struServerSwitch.byAddInfoEnable[i])
            {
                bEnable = FALSE;
            } 
        }

        if(bEnable)
        {
            m_bAllAddInfoSwitch = 1;
        }
        else
        {
            m_bAllAddInfoSwitch = 0;
        }

        UpdateData(FALSE);
        return;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_STORAGE_SERVER_SWITCH");
        return;
    }
   
}
