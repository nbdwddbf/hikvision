// DlgSmartStoragedDetection.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSmartStoragedDetection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSmartStoragedDetection dialog


CDlgSmartStoragedDetection::CDlgSmartStoragedDetection(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSmartStoragedDetection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSmartStoragedDetection)
	m_ChkEnable = FALSE;
	m_dwBadBlocks = 0;
	m_csPassWD = _T("");
	m_dwAbnormalPowerLoss = 0;
	m_csOriginalPassWD = _T("");
    m_csUnlockPassWD = _T(""); 
	//}}AFX_DATA_INIT
    m_lLoginID = -1;
    m_iDeviceIndex = -1;
    m_lChannel = -1;
    m_byRemainingLife = 0;
    memset(m_szStatusBuf, 0, sizeof(m_szStatusBuf));
}


void CDlgSmartStoragedDetection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSmartStoragedDetection)
	DDX_Control(pDX, IDC_COMBO_SDCARDSTATE, m_comSDCardState);
	DDX_Control(pDX, IDC_COMBO_HEALTHSTATE, m_comHealthState);
	DDX_Check(pDX, IDC_CHK_ENABLED, m_ChkEnable);
	DDX_Text(pDX, IDC_EDIT_BADBLOCKS, m_dwBadBlocks);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_csPassWD);
	DDX_Text(pDX, IDC_EDIT_ABNORMALPOWERLOSS, m_dwAbnormalPowerLoss);
	DDX_Text(pDX, IDC_EDIT_ORIGINAL_PASSWD, m_csOriginalPassWD);
    DDX_Text(pDX, IDC_EDIT_REMAININGLIFE, m_byRemainingLife);
    DDX_Text(pDX, IDC_EDIT_UNLOCK_PASSWD, m_csUnlockPassWD);
    
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSmartStoragedDetection, CDialog)
	//{{AFX_MSG_MAP(CDlgSmartStoragedDetection)
	ON_BN_CLICKED(IDC_BTN_GET_STORAGEDETECTION_STATE, OnBtnGetStoragedetectionState)
	ON_BN_CLICKED(IDC_BTN_GET_STORAGEDETECTION_RWLOCK, OnBtnGetStoragedetectionRwlock)
	ON_BN_CLICKED(IDC_BTN_SET_STORAGEDETECTION_RWLOCK, OnBtnSetStoragedetectionRwlock)
    ON_BN_CLICKED(IDC_BTN_SET_STORAGEDETECTION_UNLOCK, OnBtnSetStoragedetectionUnlock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSmartStoragedDetection message handlers

void CDlgSmartStoragedDetection::OnBtnGetStoragedetectionState() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STORAGE_DETECTION struStorageDet = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struStorageDet;
    struCfg.dwOutSize = sizeof(struStorageDet);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_STORAGEDETECTION_STATE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STORAGEDETECTION_STATE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STORAGEDETECTION_STATE");
    }
    
    m_comHealthState.SetCurSel(struStorageDet.byHealthState);
    m_comSDCardState.SetCurSel(struStorageDet.bySDCardState);
    m_dwAbnormalPowerLoss = struStorageDet.wAbnormalPowerLoss;
    m_dwBadBlocks = struStorageDet.wBadBlocks;
    m_byRemainingLife = struStorageDet.byRemainingLife;
    UpdateData(FALSE);
}

void CDlgSmartStoragedDetection::OnBtnGetStoragedetectionRwlock() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STORAGE_RWLOCK struStorageRWLock = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struStorageRWLock;
    struCfg.dwOutSize = sizeof(struStorageRWLock);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_STORAGEDETECTION_RWLOCK, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STORAGEDETECTION_RWLOCK");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STORAGEDETECTION_RWLOCK");
    }
    
    m_ChkEnable = struStorageRWLock.byEnabled;
    m_csPassWD.Format(_T(""), struStorageRWLock.szPassWD);
    m_csOriginalPassWD.Format(_T(""), struStorageRWLock.szOriginalPassWD);

    UpdateData(FALSE);
}

void CDlgSmartStoragedDetection::OnBtnSetStoragedetectionRwlock() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_STORAGE_RWLOCK struStorageRWLock = {0};
    struStorageRWLock.byEnabled = m_ChkEnable;
    memcpy(struStorageRWLock.szPassWD,  m_csPassWD.GetBuffer(0), m_csPassWD.GetLength());
    memcpy(struStorageRWLock.szOriginalPassWD,  m_csOriginalPassWD.GetBuffer(0), m_csOriginalPassWD.GetLength());
    struStorageRWLock.dwSize = sizeof(struStorageRWLock);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &struStorageRWLock;
    struCfg.dwInSize = sizeof(struStorageRWLock);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_STORAGEDETECTION_RWLOCK, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STORAGEDETECTION_RWLOCK");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STORAGEDETECTION_RWLOCK");
    }
}

void CDlgSmartStoragedDetection::OnBtnSetStoragedetectionUnlock() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_STORAGE_UNLOCK struStorageUnLock = {0};
    memcpy(struStorageUnLock.szPassWD,  m_csUnlockPassWD.GetBuffer(0), m_csUnlockPassWD.GetLength());
    struStorageUnLock.dwSize = sizeof(struStorageUnLock);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &struStorageUnLock;
    struCfg.dwInSize = sizeof(struStorageUnLock);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_STORAGEDETECTION_UNLOCK, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STORAGEDETECTION_UNLOCK");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STORAGEDETECTION_UNLOCK");
    }
}

