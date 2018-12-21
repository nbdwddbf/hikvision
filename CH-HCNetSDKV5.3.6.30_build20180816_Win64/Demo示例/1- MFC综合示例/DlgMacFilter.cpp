// DlgMacFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgMacFilter.h"
#include "afxdialogex.h"


// CDlgMacFilter 对话框

IMPLEMENT_DYNAMIC(CDlgMacFilter, CDialogEx)

CDlgMacFilter::CDlgMacFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMacFilter::IDD, pParent)
{

}

CDlgMacFilter::~CDlgMacFilter()
{
}

void CDlgMacFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_enable);
    DDX_Control(pDX, IDC_COMBO_MACTYPE, m_permit);
    DDX_Control(pDX, IDC_LIST_MAC, m_maclist);
    DDX_Text(pDX, IDC_EDIT_MACINPUT, m_macaddress);
    DDX_Control(pDX, IDC_EDIT_MACINPUT, m_adrescon);
}


BEGIN_MESSAGE_MAP(CDlgMacFilter, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgMacFilter::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgMacFilter::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_ADDMAC, &CDlgMacFilter::OnBnClickedButtonAddmac)
END_MESSAGE_MAP()


// CDlgMacFilter 消息处理程序


void CDlgMacFilter::OnBnClickedButtonGet()
{
    NET_DVR_STD_CONFIG struCfg = { 0 };
    memset(&m_struBuiltinMACFILTER, 0, sizeof(m_struBuiltinMACFILTER));
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struBuiltinMACFILTER;
    struCfg.dwOutSize = sizeof(m_struBuiltinMACFILTER);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_MACFILTER_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_MACFILTER_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_MACFILTER_CFG");

    }

    m_enable.SetCurSel(m_struBuiltinMACFILTER.byEnabled);
    m_permit.SetCurSel(m_struBuiltinMACFILTER.byPermissionType);

    m_maclist.DeleteAllItems();
    char szMacAddrString[48] = { 0 };
    for (int i = 0; i < sizeof(m_struBuiltinMACFILTER.szMacAddress) / 6; i++)
    {
        CString stridtemp;
        stridtemp.Format("%d", i + 1);
        m_maclist.InsertItem(i, stridtemp);
        sprintf(szMacAddrString, "%x-%x-%x-%x-%x-%x",
            m_struBuiltinMACFILTER.szMacAddress[i][0],
            m_struBuiltinMACFILTER.szMacAddress[i][1],
            m_struBuiltinMACFILTER.szMacAddress[i][2],
            m_struBuiltinMACFILTER.szMacAddress[i][3],
            m_struBuiltinMACFILTER.szMacAddress[i][4],
            m_struBuiltinMACFILTER.szMacAddress[i][5]);
        m_maclist.SetItemText(i, 1, szMacAddrString);
    }

    UpdateData(FALSE);
}


void CDlgMacFilter::OnBnClickedButtonSet()
{
    UpdateData(TRUE);

    m_struBuiltinMACFILTER.dwSize = sizeof(m_struBuiltinMACFILTER);
    m_struBuiltinMACFILTER.byEnabled = m_enable.GetCurSel();
    m_struBuiltinMACFILTER.byPermissionType = m_permit.GetCurSel();
    for (int i = 0; i < m_maclist.GetItemCount(); i++)
    {
        CString strMac = m_maclist.GetItemText(i, 1);
        if (-1 != strMac.Find("-"))
        {
            sscanf(m_maclist.GetItemText(i, 1), "%02x-%02x-%02x-%02x-%02x-%02x"\
                , &m_struBuiltinMACFILTER.szMacAddress[i][0]
                , &m_struBuiltinMACFILTER.szMacAddress[i][1]
                , &m_struBuiltinMACFILTER.szMacAddress[i][2]
                , &m_struBuiltinMACFILTER.szMacAddress[i][3]
                , &m_struBuiltinMACFILTER.szMacAddress[i][4]
                , &m_struBuiltinMACFILTER.szMacAddress[i][5]
                );
        }
        else
        {
            sscanf(m_maclist.GetItemText(i, 1), "%02x:%02x:%02x:%02x:%02x:%02x"\
                , &m_struBuiltinMACFILTER.szMacAddress[i][0]
                , &m_struBuiltinMACFILTER.szMacAddress[i][1]
                , &m_struBuiltinMACFILTER.szMacAddress[i][2]
                , &m_struBuiltinMACFILTER.szMacAddress[i][3]
                , &m_struBuiltinMACFILTER.szMacAddress[i][4]
                , &m_struBuiltinMACFILTER.szMacAddress[i][5]
                );
        }
        
    }

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struBuiltinMACFILTER;
    struCfg.dwInSize = sizeof(m_struBuiltinMACFILTER);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_MACFILTER_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_MACFILTER_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_MACFILTER_CFG");
        OutputDebugString(m_szStatusBuf);
    }
}


void CDlgMacFilter::OnBnClickedButtonAddmac()
{
    ++idtemp;
    CString stridtemp;
    stridtemp.Format("%d", idtemp);
    m_maclist.InsertItem(idtemp - 1, stridtemp);

    CString addresstemp;
    m_adrescon.GetWindowText(addresstemp);
    m_maclist.SetItemText(idtemp - 1, 1, addresstemp);
}


BOOL CDlgMacFilter::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_maclist.InsertColumn(0, "ID", LVCFMT_LEFT, 40, 0);// 插入列 
    m_maclist.InsertColumn(1, "MAC", LVCFMT_LEFT, 50, 1);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
