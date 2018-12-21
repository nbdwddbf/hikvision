// DlgFTPUpload.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFTPUpload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFTPUpload dialog


CDlgFTPUpload::CDlgFTPUpload(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFTPUpload::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFTPUpload)
	m_strCameraName = _T("");
	m_uCameraNameNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgFTPUpload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFTPUpload)
	DDX_Control(pDX, IDC_COMBO_FTPUPLOAD_PARMA, m_cmbFTPUploadParam);
	DDX_Control(pDX, IDC_COMBO_RULE_TYPE_ITEM, m_cmbRuleTypeItem);
	DDX_Control(pDX, IDC_COMBO_PICMODE, m_byPicMode);
	DDX_Control(pDX, IDC_COMBO_EVENT_TYPE, m_byEventMode);
	DDX_Text(pDX, IDC_EDIT_CAMERA_NAME, m_strCameraName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFTPUpload, CDialog)
	//{{AFX_MSG_MAP(CDlgFTPUpload)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_PICMODE, OnSelchangeComboPicmode)
	ON_CBN_SELCHANGE(IDC_COMBO_RULE_TYPE_ITEM, OnSelchangeComboRuleTypeItem)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_FTPUPLOAD_PARMA, OnSelchangeComboFtpuploadParma)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFTPUpload message handlers
BOOL CDlgFTPUpload::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    OnitCombox();

    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgFTPUpload::OnitCombox()
{

    memset(&m_struMacFilter, 0, sizeof(m_struMacFilter));
    CString csStr;
    int i = 0;
    char szLan[128] = {0};
  
    m_byEventMode.ResetContent();    
    g_StringLanType(szLan, "默认", "default");
    m_byEventMode.InsertString(0, szLan);
    g_StringLanType(szLan, "车辆检测", "Vehicle detection");
    m_byEventMode.InsertString(1, szLan);
    m_byEventMode.SetCurSel(0);

    m_byPicMode.ResetContent();    
    g_StringLanType(szLan, "默认", "default");
    m_byPicMode.InsertString(0, szLan);
    g_StringLanType(szLan, "自定义", "custom");
    m_byPicMode.InsertString(1, szLan);
    m_byPicMode.SetCurSel(0);

    m_cmbRuleTypeItem.ResetContent();    
    g_StringLanType(szLan, "capture_time", "capture_time");
    m_cmbRuleTypeItem.InsertString(0, szLan);
    g_StringLanType(szLan, "plate_No", "plate_No");
    m_cmbRuleTypeItem.InsertString(1, szLan);
    g_StringLanType(szLan, "alarm_type", "alarm_type");
    m_cmbRuleTypeItem.InsertString(2, szLan);
    g_StringLanType(szLan, "camera_name", "camera_name");
    m_cmbRuleTypeItem.InsertString(3, szLan);
    m_cmbRuleTypeItem.SetCurSel(0);
    m_cmbRuleTypeItem.EnableWindow(false);
    

    m_cmbFTPUploadParam.ResetContent();
    for (i = 0; i < 12; i++)
    {
        sprintf(szLan, "%d", i+1);
        m_cmbFTPUploadParam.InsertString(i, szLan);
        m_cmbFTPUploadParam.SetItemData(i, i);
    }
    m_cmbFTPUploadParam.SetCurSel(0);
    GetDlgItem(IDC_EDIT_CAMERA_NAME)->EnableWindow(FALSE);
    m_cmbFTPUploadParam.EnableWindow(FALSE);

    
}
void CDlgFTPUpload::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgFTPUpload::OnBtnGet() 
{
	// TODO: Add your control notification handler code here 
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &m_struMacFilter;
    struCfg.dwOutSize = sizeof(m_struMacFilter);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_FTPUPLOAD_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FTPUPLOAD_CFG");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FTPUPLOAD_CFG");
        m_byEventMode.SetCurSel(m_struMacFilter.byEventType);
        m_byPicMode.SetCurSel(m_struMacFilter.byMode);
        m_cmbFTPUploadParam.SetCurSel(0);      
        OnSelchangeComboPicmode();
    } 
    UpdateData(FALSE);       
}

void CDlgFTPUpload::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &m_struMacFilter;
    struCfg.dwInSize = sizeof(m_struMacFilter);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    m_struMacFilter.dwSize = sizeof(m_struMacFilter);
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_FTPUPLOAD_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_FTPUPLOAD_CFG");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_FTPUPLOAD_CFG");
    }
}

void CDlgFTPUpload::OnSelchangeComboPicmode() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_byPicMode.GetCurSel() == 1)
    {
        m_cmbRuleTypeItem.EnableWindow(true);
        m_cmbFTPUploadParam.EnableWindow(true); 
    }
    else
    {
        GetDlgItem(IDC_EDIT_CAMERA_NAME)->EnableWindow(FALSE);
        m_cmbRuleTypeItem.EnableWindow(FALSE);
        m_cmbFTPUploadParam.EnableWindow(FALSE);
    }
    OnSelchangeComboRuleTypeItem();
    OnSelchangeComboFtpuploadParma();
    UpdateData(FALSE);
}

int CDlgFTPUpload::RuleTypeItemSzToNo(char* szStr)
{
    UpdateData(TRUE);
    int i = m_cmbFTPUploadParam.GetCurSel();
    if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "capture_time"))
    {
        return 0;  
    }
    else if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "plate_No"))
    {
        return 1;
    }
    else if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "alarm_type"))
    {
        return 2;
    }
    else if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "camera_name"))
    {   
        return 3;
    }
    return 0;
}

void CDlgFTPUpload::OnSelchangeComboRuleTypeItem() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbFTPUploadParam.GetCurSel();
    if (m_cmbRuleTypeItem.GetCurSel() == 3)
    {
        GetDlgItem(IDC_EDIT_CAMERA_NAME)->EnableWindow(TRUE);
        m_strCameraName.Format("%s", m_struMacFilter.struCustomVehicle[i].szCameraName); 
    }
    else
    {
        GetDlgItem(IDC_EDIT_CAMERA_NAME)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}

int CDlgFTPUpload::RuleTypeItemNo(int i)
{
    UpdateData(TRUE);

    if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "capture_time"))
    {
        return 0;  
    }
    else if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "plate_No"))
    {
        return 1;
    }
    else if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "alarm_type"))
    {
        return 2;
    }
    else if (0 == strcmp(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, "camera_name"))
    {   
        return 3;
    }
    return 0;
}



char* CDlgFTPUpload::RuleTypeItemsz()
{
    UpdateData(TRUE);
    if (0 == m_cmbRuleTypeItem.GetCurSel())
    {
        return "capture_time";  
    }
    else if (1 == m_cmbRuleTypeItem.GetCurSel())
    {
        return "plate_No";
    }
    else if (2 == m_cmbRuleTypeItem.GetCurSel())
    {
        return "alarm_type";
    }
    else if (3 == m_cmbRuleTypeItem.GetCurSel())
    {   
        return "camera_name";
    }
    AfxMessageBox("RuleTypeItemsz err!");
    return NULL;
}

void CDlgFTPUpload::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struMacFilter.byEventType = m_byEventMode.GetCurSel();
    m_struMacFilter.byMode = m_byPicMode.GetCurSel();

    if (m_struMacFilter.byMode == 1)
    {
        int i = m_cmbFTPUploadParam.GetCurSel();
        memcpy(m_struMacFilter.struCustomVehicle[i].szRuleTypeItem, RuleTypeItemsz(),MAX_SINGLE_FTPPICNAME_LEN); 
        if (m_cmbRuleTypeItem.GetCurSel() == 3)
        {
           memcpy(m_struMacFilter.struCustomVehicle[i].szCameraName, m_strCameraName, MAX_CAMNAME_LEN); 
        }
    }
}

void CDlgFTPUpload::OnSelchangeComboFtpuploadParma() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbFTPUploadParam.GetCurSel();
    m_cmbRuleTypeItem.SetCurSel(RuleTypeItemSzToNo(m_struMacFilter.struCustomVehicle[i].szCameraName));
    if (m_cmbRuleTypeItem.GetCurSel() == 3)
    {
        GetDlgItem(IDC_EDIT_CAMERA_NAME)->EnableWindow(TRUE);
        m_strCameraName.Format("%s", m_struMacFilter.struCustomVehicle[i].szCameraName); 
    }
    else
    {
        GetDlgItem(IDC_EDIT_CAMERA_NAME)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);    
}
