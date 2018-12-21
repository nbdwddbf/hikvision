// DlgHiddenInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgHiddenInfo.h"
#include "afxdialogex.h"


// CDlgHiddenInfo 对话框

IMPLEMENT_DYNAMIC(CDlgHiddenInfo, CDialogEx)

CDlgHiddenInfo::CDlgHiddenInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgHiddenInfo::IDD, pParent)
    , m_scKeyWordOne(_T(""))
    , m_scKeyWordTwo(_T(""))
    , m_scKeyWordThree(_T(""))
{

}

CDlgHiddenInfo::~CDlgHiddenInfo()
{
}

void CDlgHiddenInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FUNC_TYPE, m_cmbFuncType);
    DDX_Control(pDX, IDC_COMBO_ENANLED, m_cmbEnabled);
    DDX_Text(pDX, IDC_EDIT_KEY_WORD_ONE, m_scKeyWordOne);
    DDX_Text(pDX, IDC_EDIT_KEY_WORD_TWO, m_scKeyWordTwo);
    DDX_Text(pDX, IDC_EDIT_KEY_WORD_THREE, m_scKeyWordThree);
    DDX_Control(pDX, IDC_COMBO_FILTERID, m_cmbPosID);
}


BEGIN_MESSAGE_MAP(CDlgHiddenInfo, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgHiddenInfo::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgHiddenInfo::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDCANCEL, &CDlgHiddenInfo::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgHiddenInfo 消息处理程序


void CDlgHiddenInfo::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int tempID = m_cmbPosID.GetCurSel() + 1;
    NET_DVR_HIDDEN_INFORMATION_CFG struHiddenInfo = { 0 };
    struHiddenInfo.dwSize = sizeof(struHiddenInfo);
    struHiddenInfo.byFuncType = m_cmbFuncType.GetCurSel();
    if (struHiddenInfo.byFuncType == 0)
    {
        strncpy(struHiddenInfo.struPosInfo.szKeyWord[0], m_scKeyWordOne, KEY_WORD_LEN);
        strncpy(struHiddenInfo.struPosInfo.szKeyWord[1], m_scKeyWordTwo, KEY_WORD_LEN);
        strncpy(struHiddenInfo.struPosInfo.szKeyWord[2], m_scKeyWordThree, KEY_WORD_LEN);
    }

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &tempID;
    struCfg.dwCondSize = sizeof(tempID);
    struCfg.dwInSize = sizeof(struHiddenInfo);
    struCfg.lpInBuffer = &struHiddenInfo;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_iUserID, NET_DVR_SET_HIDDEN_INFORMATION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HIDDEN_INFORMATION ");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HIDDEN_INFORMATION ");
    }
}


void CDlgHiddenInfo::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int tempID = m_cmbPosID.GetCurSel() + 1;
    NET_DVR_HIDDEN_INFORMATION_CFG struHiddenInfo = { 0 };
    struHiddenInfo.dwSize = sizeof(struHiddenInfo);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &tempID;
    struCfg.dwCondSize = sizeof(tempID);
    struCfg.dwOutSize = sizeof(struHiddenInfo);
    struCfg.lpOutBuffer = &struHiddenInfo;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;


    if (!NET_DVR_GetSTDConfig(m_iUserID, NET_DVR_GET_HIDDEN_INFORMATION, &struCfg))
    {

        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HIDDEN_INFORMATION");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HIDDEN_INFORMATION");
    }
    m_cmbFuncType.SetCurSel(struHiddenInfo.byFuncType);
    if (struHiddenInfo.byFuncType == 0)
    {
        m_scKeyWordOne = struHiddenInfo.struPosInfo.szKeyWord[0];
        m_scKeyWordTwo = struHiddenInfo.struPosInfo.szKeyWord[1];
        m_scKeyWordThree = struHiddenInfo.struPosInfo.szKeyWord[2];
    }
    UpdateData(FALSE);
}


void CDlgHiddenInfo::OnBnClickedCancel()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialogEx::OnCancel();
}
