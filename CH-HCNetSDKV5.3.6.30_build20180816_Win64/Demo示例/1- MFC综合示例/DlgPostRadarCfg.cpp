// DlgPostRadarCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPostRadarCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPostRadarCfg dialog


CDlgPostRadarCfg::CDlgPostRadarCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPostRadarCfg::IDD, pParent)
	, m_bCheckPost(FALSE)
	, m_bOverSpeed(FALSE)
	, m_dwLowSpeedLimit(0)
	, m_dwBigCarLowSpeedLimit(0)

{
	//{{AFX_DATA_INIT(CDlgPostRadarCfg)
	m_dwBigCarSignSpeed = 0;
	m_dwBigCarSpeedLimit = 0;
	m_dwInterval = 0;
	m_dwSignSpeed = 0;
	m_dwSpeedLimit = 0;
	m_dwAngleCorrect = 0;
	m_dwSensitivity = 0;
	m_dwSpeedLowLimit = 0;
	m_byID = 0;
	m_dwTrigDistance = 0;
	m_csSoftwareVersion = _T("");
	//}}AFX_DATA_INIT

    m_lLoginID = -1;
    m_iDeviceIndex = -1;
    m_lChannel = -1;
    memset(m_szStatusBuf, 0, sizeof(m_szStatusBuf));
    memset(m_szLan, 0, sizeof(m_szLan));
    
}


void CDlgPostRadarCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPostRadarCfg)
	DDX_Control(pDX, IDC_COMBO_DETECTMODE, m_comDetectMode);
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_comWorkMode);
	DDX_Control(pDX, IDC_COMBO_SPEEDTYPE, m_comSpeedType);
	DDX_Control(pDX, IDC_COMBO_DIRECTIONFILTER, m_comDirectionFilter);
	DDX_Control(pDX, IDC_COMBO_LANETYPE, m_comLaneType);
	DDX_Text(pDX, IDC_EDIT_BIGCAR_SIGNSPEED, m_dwBigCarSignSpeed);
	DDX_Text(pDX, IDC_EDIT_BIGCAR_SPEEDLIMIT, m_dwBigCarSpeedLimit);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_dwInterval);
	DDX_Text(pDX, IDC_EDIT_SIGNSPEED, m_dwSignSpeed);
	DDX_Text(pDX, IDC_EDIT_SPEEDLIMIT, m_dwSpeedLimit);
	DDX_Text(pDX, IDC_EDIT_ANGLECORRECT, m_dwAngleCorrect);
	DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_dwSensitivity);
	DDX_Text(pDX, IDC_EDIT_SPEEDLOWLIMIT, m_dwSpeedLowLimit);
	DDX_Text(pDX, IDC_EDIT_ID, m_byID);
	DDX_Text(pDX, IDC_EDIT_TRIGDISTANCE, m_dwTrigDistance);
	DDX_Text(pDX, IDC_EDIT_SOFTWAREVERSION, m_csSoftwareVersion);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHK_CHECKPOST, m_bCheckPost);
	DDX_Check(pDX, IDC_CHK_OVERSPEED, m_bOverSpeed);
	//  DDX_Text(pDX, IDC_EDIT_BIGCAR_LOWSPEED_LIMIT, m_dwLowSpeedLimit);
	//  DDX_Text(pDX, IDC_EDIT_BIGCAR_LOWSPEED_LIMIT, m_dwBigCarLowSpeedLimit);
	DDX_Text(pDX, IDC_EDIT_LOWSPEED_LIMIT, m_dwLowSpeedLimit);
	DDX_Text(pDX, IDC_EDIT_BIGCAR_LOWSPEED_LIMIT, m_dwBigCarLowSpeedLimit);
}


BEGIN_MESSAGE_MAP(CDlgPostRadarCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPostRadarCfg)
	ON_BN_CLICKED(IDC_BTN_SET_POSTRADAR, OnBtnSetPostradar)
	ON_BN_CLICKED(IDC_BTN_GET_POSTRADAR, OnBtnGetPostradar)
	ON_BN_CLICKED(IDC_BTN_GET_POSTRADAR_RECOM, OnBtnGetPostradarRecom)
	ON_BN_CLICKED(IDC_BTN_SET_POSTRADARPARAM, OnBtnSetPostradarparam)
	ON_BN_CLICKED(IDC_BTN_GET_POSTRADARPARAM_RECOM, OnBtnGetPostradarparamRecom)
	ON_BN_CLICKED(IDC_BTN_GET_POSTRADARPARAM, OnBtnGetPostradarparam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPostRadarCfg message handlers

void CDlgPostRadarCfg::OnBtnSetPostradar() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_POSTRADARSPEED_CFG struPostRadaeSpeedCfg = {0};
    if (3 == m_comLaneType.GetCurSel())
    {
        struPostRadaeSpeedCfg.byLaneType = 0xff;
    } 
    else
    {
        struPostRadaeSpeedCfg.byLaneType = m_comLaneType.GetCurSel();
    }
    
    struPostRadaeSpeedCfg.dwInterval = m_dwInterval;
    struPostRadaeSpeedCfg.dwSignSpeed = m_dwSignSpeed ;
    struPostRadaeSpeedCfg.dwSpeedLimit = m_dwSpeedLimit;
    struPostRadaeSpeedCfg.dwBigCarSignSpeed = m_dwBigCarSignSpeed;
    struPostRadaeSpeedCfg.dwBigCarSpeedLimit = m_dwBigCarSpeedLimit;

	struPostRadaeSpeedCfg.dwLowSpeedLimit = m_dwLowSpeedLimit;
	struPostRadaeSpeedCfg.dwBigCarLowSpeedLimit = m_dwBigCarLowSpeedLimit;
	struPostRadaeSpeedCfg.byCheckPostEnabled = m_bCheckPost;
	struPostRadaeSpeedCfg.byOverSpeedEnabled = m_bOverSpeed;

    struPostRadaeSpeedCfg.dwSize = sizeof(struPostRadaeSpeedCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &struPostRadaeSpeedCfg;
    struCfg.dwInSize = sizeof(struPostRadaeSpeedCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    

    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_POSTRADARSPEED_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POSTRADARSPEED_CFG");
        sprintf(m_szLan, "NET_DVR_SET_POSTRADARSPEED_CFG fail! \r\nError Code:%d. \r\nError Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(m_szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POSTRADARSPEED_CFG");
    }
}

void CDlgPostRadarCfg::OnBtnGetPostradar() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_POSTRADARSPEED_CFG struPostRadaeSpeedCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struPostRadaeSpeedCfg;
    struCfg.dwOutSize = sizeof(struPostRadaeSpeedCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_POSTRADARSPEED_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POSTRADARSPEED_CFG");
        sprintf(m_szLan, "NET_DVR_GET_POSTRADARSPEED_CFG fail! \r\nError Code:%d. \r\nError Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(m_szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POSTRADARSPEED_CFG");
    }
    
    if (struPostRadaeSpeedCfg.byLaneType == 0xff)
    {
        m_comLaneType.SetCurSel(3);
    } 
    else
    {
        m_comLaneType.SetCurSel(struPostRadaeSpeedCfg.byLaneType);
    }
    m_dwInterval = struPostRadaeSpeedCfg.dwInterval;
    m_dwSignSpeed = struPostRadaeSpeedCfg.dwSignSpeed;
    m_dwSpeedLimit = struPostRadaeSpeedCfg.dwSpeedLimit;
    m_dwBigCarSignSpeed = struPostRadaeSpeedCfg.dwBigCarSignSpeed;
    m_dwBigCarSpeedLimit = struPostRadaeSpeedCfg.dwBigCarSpeedLimit;

	m_dwLowSpeedLimit = struPostRadaeSpeedCfg.dwLowSpeedLimit;
	m_dwBigCarLowSpeedLimit = struPostRadaeSpeedCfg.dwBigCarLowSpeedLimit;
	m_bCheckPost = struPostRadaeSpeedCfg.byCheckPostEnabled;
	m_bOverSpeed = struPostRadaeSpeedCfg.byOverSpeedEnabled;

    UpdateData(FALSE);
}

void CDlgPostRadarCfg::OnBtnGetPostradarRecom() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_POSTRADARSPEED_CFG struPostRadaeSpeedCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struPostRadaeSpeedCfg;
    struCfg.dwOutSize = sizeof(struPostRadaeSpeedCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_POSTRADARSPEED_RECOM_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POSTRADARSPEED_RECOM_CFG");
        sprintf(m_szLan, "NET_DVR_GET_POSTRADARSPEED_RECOM_CFG fail! \r\nError Code:%d. \r\nError Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(m_szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POSTRADARSPEED_RECOM_CFG");
    }
    
    if (struPostRadaeSpeedCfg.byLaneType == 0xff)
    {
        m_comLaneType.SetCurSel(3);
    } 
    else
    {
        m_comLaneType.SetCurSel(struPostRadaeSpeedCfg.byLaneType);
    }
    
    m_dwInterval = struPostRadaeSpeedCfg.dwInterval;
    m_dwSignSpeed = struPostRadaeSpeedCfg.dwSignSpeed;
    m_dwSpeedLimit = struPostRadaeSpeedCfg.dwSpeedLimit;
    m_dwBigCarSignSpeed = struPostRadaeSpeedCfg.dwBigCarSignSpeed;
    m_dwBigCarSpeedLimit = struPostRadaeSpeedCfg.dwBigCarSpeedLimit;

	m_dwLowSpeedLimit = struPostRadaeSpeedCfg.dwLowSpeedLimit;
	m_dwBigCarLowSpeedLimit = struPostRadaeSpeedCfg.dwBigCarLowSpeedLimit;
	m_bCheckPost = struPostRadaeSpeedCfg.byCheckPostEnabled;
	m_bOverSpeed = struPostRadaeSpeedCfg.byOverSpeedEnabled;

    UpdateData(FALSE);
}

void CDlgPostRadarCfg::OnBtnSetPostradarparam() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_POSTRADARPARAM_CFG struPostRadaeParam = {0};
    struPostRadaeParam.byID = m_byID;
    memcpy(struPostRadaeParam.bySoftWareVersion, m_csSoftwareVersion.GetBuffer(0), m_csSoftwareVersion.GetLength());
    //struPostRadaeParam.byDetectMode = m_comDetectMode.GetCurSel();
    if (5 == m_comWorkMode.GetCurSel())
    {
        struPostRadaeParam.byWorkMode = 0xff;
    } 
    else
    {
        struPostRadaeParam.byWorkMode = m_comWorkMode.GetCurSel();
    }
    
    if (3 == m_comSpeedType.GetCurSel())
    {
        struPostRadaeParam.bySpeedType = 0xff;
    } 
    else
    {
        struPostRadaeParam.bySpeedType = m_comSpeedType.GetCurSel();
    }
    
    struPostRadaeParam.byDirectionFilter = m_comDirectionFilter.GetCurSel();
    struPostRadaeParam.dwAngleCorrect = m_dwAngleCorrect;
    struPostRadaeParam.dwSensitivity = m_dwSensitivity;
    struPostRadaeParam.dwSpeedLowLimit = m_dwSpeedLowLimit;
    struPostRadaeParam.dwTrigDistance = m_dwTrigDistance;
    struPostRadaeParam.dwSize = sizeof(struPostRadaeParam);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &struPostRadaeParam;
    struCfg.dwInSize = sizeof(struPostRadaeParam);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_POSTRADARPARAM_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POSTRADARPARAM_CFG");
        sprintf(m_szLan, "NET_DVR_SET_POSTRADARPARAM_CFG fail! \r\nError Code:%d. \r\nError Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(m_szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POSTRADARPARAM_CFG");
    }
}

void CDlgPostRadarCfg::OnBtnGetPostradarparamRecom() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_POSTRADARPARAM_CFG struPostRadaeParam = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struPostRadaeParam;
    struCfg.dwOutSize = sizeof(struPostRadaeParam);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_POSTRADARPARAM_RECOM_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POSTRADARPARAM_RECOM_CFG");
        sprintf(m_szLan, "NET_DVR_GET_POSTRADARPARAM_RECOM_CFG fail! \r\nError Code:%d. \r\nError Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(m_szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POSTRADARPARAM_RECOM_CFG");
    }
 
    m_byID = struPostRadaeParam.byID;
    m_csSoftwareVersion.Format(_T("%s"), struPostRadaeParam.bySoftWareVersion);
   // m_comDetectMode.SetCurSel(struPostRadaeParam.byDetectMode);
    if(struPostRadaeParam.byWorkMode == 0xff)
    {
        m_comWorkMode.SetCurSel(5);
    }
    else
    {
        m_comWorkMode.SetCurSel(struPostRadaeParam.byWorkMode);
    }
    
    if(struPostRadaeParam.bySpeedType == 0xff)
    {
        m_comSpeedType.SetCurSel(3);
    }
    else
    {
        m_comSpeedType.SetCurSel(struPostRadaeParam.bySpeedType);
    }
    m_comDirectionFilter.SetCurSel(struPostRadaeParam.byDirectionFilter);
    m_dwAngleCorrect = struPostRadaeParam.dwAngleCorrect;
    m_dwSensitivity = struPostRadaeParam.dwSensitivity;
    m_dwSpeedLowLimit = struPostRadaeParam.dwSpeedLowLimit;
    m_dwTrigDistance = struPostRadaeParam.dwTrigDistance;


    UpdateData(FALSE);
}

void CDlgPostRadarCfg::OnBtnGetPostradarparam() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_POSTRADARPARAM_CFG struPostRadaeParam = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struPostRadaeParam;
    struCfg.dwOutSize = sizeof(struPostRadaeParam);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_POSTRADARPARAM_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POSTRADARPARAM_CFG");
        sprintf(m_szLan, "NET_DVR_GET_POSTRADARPARAM_CFG fail! \r\nError Code:%d. \r\nError Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(m_szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POSTRADARPARAM_CFG");
    }
    
    m_byID = struPostRadaeParam.byID;
    m_csSoftwareVersion.Format(_T("%s"), struPostRadaeParam.bySoftWareVersion);
   // m_comDetectMode.SetCurSel(struPostRadaeParam.byDetectMode);
    if(struPostRadaeParam.byWorkMode == 0xff)
    {
        m_comWorkMode.SetCurSel(5);
    }
    else
    {
        m_comWorkMode.SetCurSel(struPostRadaeParam.byWorkMode);
    }

    if(struPostRadaeParam.bySpeedType == 0xff)
    {
        m_comSpeedType.SetCurSel(3);
    }
    else
    {
        m_comSpeedType.SetCurSel(struPostRadaeParam.bySpeedType);
    }
    
    m_comDirectionFilter.SetCurSel(struPostRadaeParam.byDirectionFilter);
    m_dwAngleCorrect = struPostRadaeParam.dwAngleCorrect;
    m_dwSensitivity = struPostRadaeParam.dwSensitivity;
    m_dwSpeedLowLimit = struPostRadaeParam.dwSpeedLowLimit;
    m_dwTrigDistance = struPostRadaeParam.dwTrigDistance;
    
    
    UpdateData(FALSE);
}

BOOL CDlgPostRadarCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_comLaneType.SetCurSel(0);
    m_comDetectMode.SetCurSel(0);
	m_comWorkMode.SetCurSel(0);
    m_comSpeedType.SetCurSel(0);
    m_comDirectionFilter.SetCurSel(0);


    OnBtnGetPostradar();
    OnBtnGetPostradarparam();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
