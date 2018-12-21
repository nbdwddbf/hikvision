// DlgLiteStorage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLiteStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLiteStorage dialog


CDlgLiteStorage::CDlgLiteStorage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLiteStorage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLiteStorage)
	m_bEnable = FALSE;
	m_fCapacity = 0.0f;
	m_iStorageTime = 0;
    m_lChannel = 0;
    m_lLoginID = -1;
    m_iDeviceIndex = -1;

    m_iStorageTimeLow = 0;
    m_iStorageTimeMedium = 0;
    m_iStorageTimeHigh = 0;

	//}}AFX_DATA_INIT
    memset(&m_strLiteStorage, 0, sizeof(m_strLiteStorage));
    memset(&m_szStatusBuf, 0, ISAPI_STATUS_LEN);
}


void CDlgLiteStorage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLiteStorage)
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_CAPACITY, m_fCapacity);
	DDX_Text(pDX, IDC_EDIT_STORAGETIME, m_iStorageTime);
    DDX_Control(pDX, IDC_COMBO_LEVEL, m_comboLevel);
    DDX_Text(pDX, IDC_EDIT_STORAGETIME_LOW, m_iStorageTimeLow);
    DDX_Text(pDX, IDC_EDIT_STORAGETIME_MEDIUM, m_iStorageTimeMedium);
    DDX_Text(pDX, IDC_EDIT_STORAGETIME_HIGH, m_iStorageTimeHigh);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLiteStorage, CDialog)
	//{{AFX_MSG_MAP(CDlgLiteStorage)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLiteStorage message handlers

void CDlgLiteStorage::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
    NET_DVR_STD_CONFIG struCfg = {0};
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lChannel = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_strLiteStorage;
    struCfg.dwOutSize = sizeof(m_strLiteStorage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_LITESTORAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LITESTORAGE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LITESTORAGE");
    }

    m_bEnable = m_strLiteStorage.byEnable;
    m_fCapacity = m_strLiteStorage.fCapacity;
    m_iStorageTime = m_strLiteStorage.byStorageTime;
    m_comboLevel.SetCurSel(m_strLiteStorage.byLevel);
    m_iStorageTimeLow = m_strLiteStorage.byDefLowStorageTime;
    m_iStorageTimeMedium = m_strLiteStorage.byDefMediumStorageTime;
    m_iStorageTimeHigh = m_strLiteStorage.byDefHighStorageTime;
    UpdateData(FALSE);
}

void CDlgLiteStorage::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
    m_strLiteStorage.byEnable = m_bEnable;
    m_strLiteStorage.fCapacity = m_fCapacity;
    m_strLiteStorage.byStorageTime = m_iStorageTime;
    m_strLiteStorage.byLevel = m_comboLevel.GetCurSel();
    m_strLiteStorage.dwSize = sizeof(m_strLiteStorage);

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_strLiteStorage;
    struCfg.dwInSize = sizeof(m_strLiteStorage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_LITESTORAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LITESTORAGE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LITESTORAGE");
    }

}
