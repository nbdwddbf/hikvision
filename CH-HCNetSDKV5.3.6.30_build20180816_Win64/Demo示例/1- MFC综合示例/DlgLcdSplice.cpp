// DlgLcdSplice.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdSplice.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSplice dialog

CDlgLcdSplice::CDlgLcdSplice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdSplice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdSplice)
	m_byWallNo = 0;
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
    m_byWallNo = 1;
    m_iLastSel = -1;
    m_lCfgHandle = -1;
    m_dwCfgNo = 1;
    m_bExitThread = FALSE;
    m_lHandle = NULL;
}


void CDlgLcdSplice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdSplice)
	DDX_Control(pDX, IDC_STATIC_STATUS, m_csStatus);
	DDX_Control(pDX, IDC_COMBO_Y, m_comboY);
	DDX_Control(pDX, IDC_COMBO_X, m_comboX);
	DDX_Control(pDX, IDC_COMBO_WIDTH, m_comboWidth);
	DDX_Control(pDX, IDC_COMBO_SPLICE_NO, m_comboSpliceNo);
	DDX_Control(pDX, IDC_COMBO_HEIGHT, m_comboHeight);
	DDX_Text(pDX, IDC_EDIT_WALL_NO, m_byWallNo);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdSplice, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdSplice)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_CBN_SELCHANGE(IDC_COMBO_SPLICE_NO, OnSelchangeComboSpliceNo)
	//}}AFX_MSG_MAP
    
    ON_MESSAGE(WM_PROC_LCD_SPLICE, OnMessUpdateInterface)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSplice message handlers
UINT LcdSpliceWaitThread(LPVOID pParam)
{
    CDlgLcdSplice *ptr = (CDlgLcdSplice *)pParam;

    int i = 0;
    if (ptr->m_iConfigType == 0)
    {
        for (i = 0; i < SPLICE_NUM; i++)
        {
            if (!NET_DVR_SendRemoteConfig(ptr->m_lCfgHandle, ENUM_MSC_SEND_DATA, (char *)&ptr->m_struSpliceParam[i], sizeof(NET_DVR_MSC_SPLICE_CFG)))
            {
                g_pMainDlg->AddLog(ptr->m_iDeviceIndex, OPERATION_FAIL_T, "ENUM_MSC_SEND_DATA");
                NET_DVR_StopRemoteConfig(ptr->m_lCfgHandle);
                OutputDebugString("LcdSpliceWaitThread exit 1!");
                ptr->m_lHandle = NULL;
                return 0;
            }
        }
    }
    else
    {
        for (i = 0; i < SPLICE_NUM; i++)
        {
            if (!NET_DVR_SendRemoteConfig(ptr->m_lCfgHandle, ENUM_MSC_SEND_DATA, (char *)&ptr->m_struSpliceCond[i], sizeof(NET_DVR_MSC_SPLICE_CFG)))
            {
                g_pMainDlg->AddLog(ptr->m_iDeviceIndex, OPERATION_FAIL_T, "ENUM_MSC_SEND_DATA");
                OutputDebugString("LcdSpliceWaitThread exit 2!");
                NET_DVR_StopRemoteConfig(ptr->m_lCfgHandle);
                ptr->m_lHandle = NULL;
                return 0;
            }
            Sleep(100); 
        }
    }

    while (!ptr->m_bExitThread)
    {
        Sleep(500);        
    }

    if (ptr->m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(ptr->m_lCfgHandle);
        ptr->m_lCfgHandle = -1;
    } 
    
    ::PostMessage(ptr->m_hWnd, WM_PROC_LCD_SPLICE, NULL, NULL);
    OutputDebugString("LcdSpliceWaitThread exit 3!");    
    return 0;
}

void CALLBACK LcdSpliceCallBack(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgLcdSplice *ptr = (CDlgLcdSplice *)pUserData;
    DWORD dwStatus;
    char szLan[64] = {0};
    NET_DVR_MSC_SPLICE_CFG *lpData = NULL;

    switch (dwType)
    {
    case NET_SDK_CALLBACK_TYPE_STATUS:
        dwStatus = *((DWORD *)lpBuffer);
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            sprintf(szLan, "Splice %d success", ptr->m_dwCfgNo);
            ptr->m_csStatus.SetWindowText(szLan);
//             if (ptr->m_dwCfgNo == SPLICE_NUM)
//             {
//                 ptr->m_bExitThread = TRUE;
//             }
//             ptr->m_dwCfgNo++;
//            ptr->ShowDataNotToSave(); 
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            sprintf(szLan, "Splice %d processing", ptr->m_dwCfgNo);
            ptr->m_csStatus.SetWindowText(szLan);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            sprintf(szLan, "Splice %d fail", ptr->m_dwCfgNo);
            ptr->m_csStatus.SetWindowText(szLan);
            ptr->m_dwCfgNo++;
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            sprintf(szLan, "Config exception");
            ptr->m_csStatus.SetWindowText(szLan); 
            ptr->m_bExitThread = TRUE;
        }
    	break;
    case NET_SDK_CALLBACK_TYPE_DATA:
        lpData = (NET_DVR_MSC_SPLICE_CFG *)lpBuffer;
        memcpy(&ptr->m_struSpliceParam[ptr->m_dwCfgNo - 1], lpData, sizeof(NET_DVR_MSC_SPLICE_CFG));
        if (ptr->m_dwCfgNo == SPLICE_NUM)
        {
            ptr->m_bExitThread = TRUE;
        }        
        sprintf(szLan, "Splice %d success", ptr->m_dwCfgNo);
        ptr->m_csStatus.SetWindowText(szLan);
        ptr->m_dwCfgNo++;
        break;
    default:
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "SPLICE_SET CallBack unknow status %d", dwType);
        return;
    }
    
    if (ptr->m_dwCfgNo >= SPLICE_NUM)
    {
        sprintf(szLan, "Splice config over");
        ptr->m_csStatus.SetWindowText(szLan);
        ptr->m_bExitThread = TRUE;
    }

//    ptr->UpdateData(FALSE);
}

BOOL CDlgLcdSplice::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    memset(m_struSpliceCond, 0, sizeof(m_struSpliceCond));
    memset(m_struSpliceParam, 0, sizeof(m_struSpliceParam));

    int i = 0;
    CString csTemp;

    for (i = 0; i < SPLICE_NUM; i++)
    {
        csTemp.Format("%d", i);
        m_comboX.AddString(csTemp);
        m_comboY.AddString(csTemp);
        csTemp.Format("%d", i+1);
        m_comboWidth.AddString(csTemp);
        m_comboHeight.AddString(csTemp);

        m_struSpliceCond[i].dwSize = sizeof(m_struSpliceCond[i]);
        m_struSpliceCond[i].bySpliceNo = i+1; 
        m_struSpliceCond[i].byWallNo = 1; 

        m_struSpliceParam[i].dwSize = sizeof(m_struSpliceParam[i]);
    }
	m_comboSpliceNo.SetCurSel(0); 
  
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdSplice::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[64] = {0};
    DWORD dwThreadId = 0;
    SaveLastData();
    if (m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lCfgHandle);
        m_lCfgHandle = -1;
    }
    
    if (m_lHandle != NULL)
    {
        m_bExitThread = TRUE;
        WaitForSingleObject(m_lHandle, INFINITE);
        CloseHandle(m_lHandle);
        m_lHandle = NULL;
    }
    
    m_dwCfgNo = 1;
    m_bExitThread = FALSE;
    m_iConfigType = 0;

    m_lCfgHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_SCREEN_SPLICE_SET, NULL, 0, LcdSpliceCallBack, this);
    
    if (m_lCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_SPLICE_SET");
        g_StringLanType(szLan, "设置屏幕拼接参数失败", "Set splice parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_SPLICE_SET");
        m_lHandle = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(LcdSpliceWaitThread), this, 0, &dwThreadId);
        if (m_lHandle == NULL)
        {
            g_StringLanType(szLan, "创建等待线程失败", "Create wait thread fail");
            NET_DVR_StopRemoteConfig(m_lCfgHandle);
            return;
        }            
    }
}

void CDlgLcdSplice::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[64] = {0};
    DWORD dwThreadId = 0;
    
    if (m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lCfgHandle);
        m_lCfgHandle = -1;
    }
    
    if (m_lHandle != NULL)
    {
        m_bExitThread = TRUE;
        WaitForSingleObject(m_lHandle, INFINITE);
        CloseHandle(m_lHandle);
        m_lHandle = NULL;
    }
    
    m_dwCfgNo = 1;
    m_bExitThread = FALSE;
    m_iConfigType = 1;

    m_lCfgHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_SCREEN_SPLICE_GET, NULL, 0, LcdSpliceCallBack, this);
    
    if (m_lCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_SPLICE_GET");
        g_StringLanType(szLan, "获取屏幕拼接参数失败", "Get splice parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_SPLICE_GET");
        m_lHandle = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(LcdSpliceWaitThread), this, 0, &dwThreadId);
        if (m_lHandle == NULL)
        {
            g_StringLanType(szLan, "创建等待线程失败", "Create wait thread fail");
            NET_DVR_StopRemoteConfig(m_lCfgHandle);
            return;
        }            
    }
}

void CDlgLcdSplice::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    if (m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lCfgHandle);
        m_lCfgHandle = -1;
    }
    
    if (m_lHandle != NULL)
    {
        TerminateThread(m_lHandle, 0);
        CloseHandle(m_lHandle);
        m_lHandle = NULL;
    }

    CDialog::OnCancel();
}

void CDlgLcdSplice::SaveLastData()
{
    UpdateData(TRUE);
    if (m_iLastSel == CB_ERR)
    {
        return;
    }

    m_struSpliceCond[m_iLastSel].bySpliceNo = m_iLastSel + 1;
    m_struSpliceCond[m_iLastSel].byWallNo = m_byWallNo;

    m_struSpliceParam[m_iLastSel].bySpliceNo = m_iLastSel + 1;
    m_struSpliceParam[m_iLastSel].byWallNo = m_byWallNo;
    m_struSpliceParam[m_iLastSel].byEnable = m_bEnable;
    m_struSpliceParam[m_iLastSel].struRectCfg.dwXCoordinate = m_comboX.GetCurSel() * 1920;
    m_struSpliceParam[m_iLastSel].struRectCfg.dwYCoordinate = m_comboY.GetCurSel() * 1920;
    m_struSpliceParam[m_iLastSel].struRectCfg.dwWidth = (m_comboWidth.GetCurSel() + 1) * 1920;
    m_struSpliceParam[m_iLastSel].struRectCfg.dwHeight = (m_comboHeight.GetCurSel() + 1) * 1920;

}
void CDlgLcdSplice::OnSelchangeComboSpliceNo() 
{
	// TODO: Add your control notification handler code here
    ShowDataNotToSave(FALSE); 
// 	UpdateData(TRUE);
//     int iSel = m_comboSpliceNo.GetCurSel();
//     if (CB_ERR == iSel)
//     {
//         return;
//     }
// 
//     
//     
//     m_byWallNo = m_struSpliceParam[iSel].byWallNo;
//     m_bEnable = m_struSpliceParam[iSel].byEnable;
//     m_comboX.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwXCoordinate/1920);
//     m_comboY.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwYCoordinate/1920);
//     m_comboWidth.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwWidth/1920 - 1);
//     m_comboHeight.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwHeight/1920 - 1);
// 
//     m_iLastSel = iSel;
}

void CDlgLcdSplice::ShowDataNotToSave(BOOL BjustShow)
{
    UpdateData(TRUE);
    int iSel = m_comboSpliceNo.GetCurSel();
    if (CB_ERR == iSel)
    {
        return;
    }
    if (! BjustShow )
    {
        SaveLastData();
    }
    m_byWallNo = m_struSpliceParam[iSel].byWallNo;
    m_bEnable = m_struSpliceParam[iSel].byEnable;
    UpdateData(FALSE); 
    m_comboX.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwXCoordinate/1920);
    m_comboY.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwYCoordinate/1920);
    m_comboWidth.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwWidth/1920 - 1);
    m_comboHeight.SetCurSel(m_struSpliceParam[iSel].struRectCfg.dwHeight/1920 - 1);  
    m_iLastSel = iSel;
} 

LRESULT CDlgLcdSplice::OnMessUpdateInterface(WPARAM wParam, LPARAM lParam)
{
    ShowDataNotToSave(); 
	return 0;
}