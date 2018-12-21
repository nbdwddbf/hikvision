// DlgAcsSmsCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsSmsCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAcsSmsCfg dialog


DlgAcsSmsCfg::DlgAcsSmsCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsSmsCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAcsSmsCfg)
    m_byPhonePerssion = FALSE;
    m_sPhoneNo = _T("");
    m_sAcsPassword = _T("");
	//}}AFX_DATA_INIT
    memset(&m_struSmsCfg, 0, sizeof(m_struSmsCfg));
}


void DlgAcsSmsCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsSmsCfg)
    DDX_Control(pDX, IDC_COMBO_WHITE_LIST, m_comboWhiteList);
    DDX_Check(pDX, IDC_CHECK_DOOR, m_byPhonePerssion);
    DDX_Text(pDX, IDC_EDIT_PHONE, m_sPhoneNo);
    DDX_Text(pDX, IDC_EDIT_ACS_PASSWORD, m_sAcsPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsSmsCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsSmsCfg)
    ON_CBN_SELCHANGE(IDC_COMBO_WHITE_LIST, OnSelchangeWhiteList)
    ON_BN_CLICKED(IDC_BUTTON_SURE, OnBtnSure)
    ON_BN_CLICKED(IDC_BUTTON_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsSmsCfg message handlers

BOOL DlgAcsSmsCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    
    CString csStr;
    char szLan[128] = {0};
    
    for (int i = 0; i<NET_SDK_MAX_WHITELIST_NUM_32; i++)
    {
        g_StringLanType(szLan, "手机", "phone");
        csStr.Format("%s %d", szLan, i+1);
        m_comboWhiteList.InsertString(i, csStr);
    }
    m_comboWhiteList.SetCurSel(0);
    //OnBtnGet();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAcsSmsCfg::OnSelchangeWhiteList() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwReaderIndex = m_comboWhiteList.GetCurSel();
    if (m_struSmsCfg.struWhiteList[dwReaderIndex].byPhonePerssion[4] == 1)
    {
        m_byPhonePerssion = TRUE;
    } 
    else
    {
        m_byPhonePerssion = FALSE;
    }
    m_sPhoneNo.Format("%s",m_struSmsCfg.struWhiteList[dwReaderIndex].byWhiteList);    
    m_sAcsPassword.Format("%s", m_struSmsCfg.struWhiteList[dwReaderIndex].byAcsPassword);
    UpdateData(FALSE);
}

void DlgAcsSmsCfg::OnBtnSure() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwReaderIndex = m_comboWhiteList.GetCurSel();
    if (m_byPhonePerssion)
    {
        m_struSmsCfg.struWhiteList[dwReaderIndex].byPhonePerssion[4] = 1;
    } 
    else
    {
        m_struSmsCfg.struWhiteList[dwReaderIndex].byPhonePerssion[4] = 0;
    }
    memset(m_struSmsCfg.struWhiteList[dwReaderIndex].byWhiteList, 0, sizeof(m_struSmsCfg.struWhiteList[dwReaderIndex].byWhiteList));
    memcpy(m_struSmsCfg.struWhiteList[dwReaderIndex].byWhiteList, m_sPhoneNo.GetBuffer(m_sPhoneNo.GetLength()), m_sPhoneNo.GetLength());
    memset(m_struSmsCfg.struWhiteList[dwReaderIndex].byAcsPassword, 0, sizeof(m_struSmsCfg.struWhiteList[dwReaderIndex].byAcsPassword));
    memcpy(m_struSmsCfg.struWhiteList[dwReaderIndex].byAcsPassword, m_sAcsPassword.GetBuffer(m_sAcsPassword.GetLength()), m_sAcsPassword.GetLength());
    UpdateData(FALSE);
}

void DlgAcsSmsCfg::OnBtnGet() 
{
    // TODO: Add your control notification handler code here
    DWORD dwReturn = 0;
    char szLan[1024];
    m_struSmsCfg.dwSize = sizeof(m_struSmsCfg);
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SMSRELATIVEPARA_V50, 0, &m_struSmsCfg, sizeof(m_struSmsCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SMSRELATIVEPARA_V50 Failed");
        g_StringLanType(szLan, "获取手机白名单参数失败", "get white list cfg Failed");
        MessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SMSRELATIVEPARA_V50 SUCC");
        m_comboWhiteList.SetCurSel(0);
        if (m_struSmsCfg.struWhiteList[0].byPhonePerssion[4] == 1)
        {
            m_byPhonePerssion = TRUE;
        } 
        else
        {
            m_byPhonePerssion = FALSE;
        }
        m_sPhoneNo.Format("%s",m_struSmsCfg.struWhiteList[0].byWhiteList);
        m_sAcsPassword.Format("%s", m_struSmsCfg.struWhiteList[0].byAcsPassword);
        UpdateData(FALSE);
    }
}

void DlgAcsSmsCfg::OnBtnSet() 
{
    // TODO: Add your control notification handler code here
    //OnBtnSure();
    char szLan[1024];
    m_struSmsCfg.dwSize = sizeof(m_struSmsCfg);
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SMSRELATIVEPARA_V50, 0, &m_struSmsCfg, sizeof(m_struSmsCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SMSRELATIVEPARA_V50 Failed");
        g_StringLanType(szLan, "获取手机白名单参数失败", "get white list cfg Failed");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SMSRELATIVEPARA_V50 SUCC");
    }
}
