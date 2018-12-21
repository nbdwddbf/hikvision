// DlgStreamMediaCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgStreamMediaCfg.h"
#include "afxdialogex.h"


// CDlgStreamMediaCfg 对话框

IMPLEMENT_DYNAMIC(CDlgStreamMediaCfg, CDialog)

CDlgStreamMediaCfg::CDlgStreamMediaCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStreamMediaCfg::IDD, pParent)
    , m_csRelatedChannel(_T(""))
    , m_csStatus(_T(""))
    , m_csStreamID(_T(""))
    , m_csUrl(_T(""))
{

}

CDlgStreamMediaCfg::~CDlgStreamMediaCfg()
{
}

void CDlgStreamMediaCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_RELATEAD_CHANNLE, m_csRelatedChannel);
    DDX_Text(pDX, IDC_EDIT_STATUS, m_csStatus);
    DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_csStreamID);
    DDX_Text(pDX, IDC_EDIT_STREAM_URL, m_csUrl);
    DDX_Control(pDX, IDC_LIST_STREAM_MEDIA_CFG, m_listCtrlStreamMediaCfg);
}


BEGIN_MESSAGE_MAP(CDlgStreamMediaCfg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgStreamMediaCfg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgStreamMediaCfg::OnBnClickedButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgStreamMediaCfg::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgStreamMediaCfg::OnBnClickedButtonGet)
    ON_NOTIFY(NM_CLICK, IDC_LIST_STREAM_MEDIA_CFG, OnClickListStreamMediaCfg)
END_MESSAGE_MAP()


// CDlgStreamMediaCfg 消息处理程序


BOOL CDlgStreamMediaCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    m_listCtrlStreamMediaCfg.SetExtendedStyle(m_listCtrlStreamMediaCfg.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "序号", "Serial No.");
    m_listCtrlStreamMediaCfg.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "流ID", "Stream ID");
    m_listCtrlStreamMediaCfg.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "关联通道", "Related channel");
    m_listCtrlStreamMediaCfg.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "地址", "Url");
    m_listCtrlStreamMediaCfg.InsertColumn(3, szLan, LVCFMT_LEFT, 150, -1);

    g_StringLanType(szLan, "状态", "status");
    m_listCtrlStreamMediaCfg.InsertColumn(4, szLan, LVCFMT_LEFT, 50, -1);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgStreamMediaCfg::OnBnClickedButtonAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    CString strTemp;

    // 	if ("" == m_strStreamID)
    // 	{
    // 		g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
    // 		AfxMessageBox(szLan);
    // 		return;
    // 	}

    int iItemCount = m_listCtrlStreamMediaCfg.GetItemCount();
    if (iItemCount > 64)
    {
        g_StringLanType(szLan, "流ID超过64个", "Stream ID is more than 64");
        AfxMessageBox(szLan);
        return;
    }
    strTemp.Format("%02d", iItemCount + 1);
    m_listCtrlStreamMediaCfg.InsertItem(iItemCount, strTemp);
    m_listCtrlStreamMediaCfg.SetItemText(iItemCount, 1, m_csStreamID);
    m_listCtrlStreamMediaCfg.SetItemText(iItemCount, 2, m_csRelatedChannel);
    m_listCtrlStreamMediaCfg.SetItemText(iItemCount, 3, m_csUrl);
}


void CDlgStreamMediaCfg::OnBnClickedButtonDel()
{
    // TODO:  在此添加控件通知处理程序代码
    while (m_listCtrlStreamMediaCfg.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED) != -1)
    {
        int nItem = m_listCtrlStreamMediaCfg.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
        m_listCtrlStreamMediaCfg.DeleteItem(nItem);
    }
}


void CDlgStreamMediaCfg::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[128] = { 0 };

    LPNET_DVR_STREAM_MEDIA_CFG pStreamMediaCfg = &m_struStreamMediaCfg[0];
    LPNET_DVR_STREAM_MEDIA_CFG pTempStreamMediaCfg = pStreamMediaCfg;

    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;

    int iItemCount = m_listCtrlStreamMediaCfg.GetItemCount();

    LPNET_DVR_STREAM_INFO pstruStreamID = NULL;
    LPNET_DVR_STREAM_INFO pTempStreamID = NULL;
    if (0 == iItemCount)
    {
        // 		if ("" == m_strStreamID)
        // 		{
        // 			g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
        // 			AfxMessageBox(szLan);
        // 			return;
        // 		}
        pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO;
        if (NULL == pstruStreamID)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pstruStreamID, 0, sizeof(NET_DVR_STREAM_INFO));
        pstruStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
        pstruStreamID->dwChannel = atoi(m_csRelatedChannel);
        strncpy((char*)pstruStreamID->byID, m_csStreamID, STREAM_ID_LEN);

        pStreamMediaCfg->dwSize = sizeof(NET_DVR_STREAM_MEDIA_CFG);
        //char szTemp[MAX_URL_LEN + 1] = {0};
        memcpy(pStreamMediaCfg->sUrl, m_csUrl.GetBuffer(0), MAX_URL_LEN);

        DWORD dwStatus = 0;
        BOOL bRet = NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_MEDIA_CFG, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamMediaCfg, sizeof(NET_DVR_STREAM_MEDIA_CFG));

        if (bRet && (0 == dwStatus))
        {
            g_StringLanType(szLan, "设置成功", "Success");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "succeed to set");
            AfxMessageBox(szLan);
        }
        else
        {
            g_StringLanType(szLan, "设置失败", "Fail");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set");
            AfxMessageBox(szLan);
        }

        m_csStatus.Format("%d", dwStatus);
    }
    else
    {
        // 申请iItemCount个NET_DVR_STREAM_INFO
        pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO[iItemCount];
        if (NULL == pstruStreamID)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pstruStreamID, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
        pTempStreamID = pstruStreamID;

        int i = 0;
        for (i = 0; i < iItemCount; i++)
        {
            pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
            strncpy((char*)pTempStreamID->byID, m_listCtrlStreamMediaCfg.GetItemText(i, 1), STREAM_ID_LEN);
            pTempStreamID->dwChannel = atoi(m_listCtrlStreamMediaCfg.GetItemText(i, 2));

            pTempStreamMediaCfg->dwSize = sizeof(NET_DVR_STREAM_MEDIA_CFG);

            memcpy(pTempStreamMediaCfg->sUrl, m_listCtrlStreamMediaCfg.GetItemText(i, 3), MAX_URL_LEN);

            pTempStreamID++;
            pTempStreamMediaCfg++;
        }

        DWORD *pStatus = new DWORD[iItemCount];
        memset(pStatus, 0, sizeof(DWORD)*iItemCount);

        if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_MEDIA_CFG, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamMediaCfg, iItemCount*sizeof(NET_DVR_STREAM_MEDIA_CFG)))
        {
            g_StringLanType(szLan, "批量设置成功", "Succeed to set");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Stream media config");
            AfxMessageBox(szLan);
        }
        else
        {
            g_StringLanType(szLan, "批量设置失败", "Fail to set");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set media config");
            AfxMessageBox(szLan);
        }

        for (i = 0; i < iItemCount; i++)
        {
            CString strStatus;
            strStatus.Format("%d", *pStatus);
            m_listCtrlStreamMediaCfg.SetItemText(i, 4, strStatus);
            pStatus++;
        }
    }

    UpdateData(FALSE);
}


void CDlgStreamMediaCfg::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    DWORD dwReturn = 0;
    CString strTemp;

    LPNET_DVR_STREAM_MEDIA_CFG pStreamMediaCfg = &m_struStreamMediaCfg[0];
    LPNET_DVR_STREAM_MEDIA_CFG pTempStreamMediaCfg = pStreamMediaCfg;

    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;

    int iItemCount = m_listCtrlStreamMediaCfg.GetItemCount();

    LPNET_DVR_STREAM_INFO pstruStreamID = NULL;
    LPNET_DVR_STREAM_INFO pTempStreamID = NULL;
    if (0 == iItemCount)
    {
        // 		if ("" == m_strStreamID)
        // 		{
        // 			g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
        // 			AfxMessageBox(szLan);
        // 			return;
        // 		}
        pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO;
        if (NULL == pstruStreamID)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pstruStreamID, 0, sizeof(NET_DVR_STREAM_INFO));
        pstruStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
        pstruStreamID->dwChannel = atoi(m_csRelatedChannel);
        strncpy((char*)pstruStreamID->byID, m_csStreamID, STREAM_ID_LEN);

        // 返回的状态
        DWORD dwStatus = 0;

        BOOL bRet = NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_MEDIA_CFG, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamMediaCfg, sizeof(NET_DVR_STREAM_MEDIA_CFG));


        if (bRet && (0 == dwStatus))
        {
            g_StringLanType(szLan, "获取成功", "Get success");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get success");
            AfxMessageBox(szLan);
        }
        else
        {
            g_StringLanType(szLan, "获取失败", "Fail to Get");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set");
            AfxMessageBox(szLan);
            return;
        }

        m_csStatus.Format("%d", dwStatus);
    }
    else
    {
        // 申请iItemCount个NET_DVR_STREAM_INFO
        pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO[iItemCount];
        if (NULL == pstruStreamID)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pstruStreamID, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
        pTempStreamID = pstruStreamID;

        DWORD *pStatus = new DWORD[iItemCount];
        memset(pStatus, 0, sizeof(DWORD)*iItemCount);

        int i = 0;
        for (i = 0; i < iItemCount; i++)
        {
            pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
            strncpy((char*)pTempStreamID->byID, m_listCtrlStreamMediaCfg.GetItemText(i, 1), STREAM_ID_LEN);
            pTempStreamID->dwChannel = atoi(m_listCtrlStreamMediaCfg.GetItemText(i, 2));
            pTempStreamID++;
        }


        if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_MEDIA_CFG, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamMediaCfg, iItemCount*sizeof(NET_DVR_STREAM_MEDIA_CFG)))
        {
            g_StringLanType(szLan, "批量获取成功", "Get success");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get success");
            AfxMessageBox(szLan);
        }
        else
        {
            delete pStatus;
            g_StringLanType(szLan, "批量获取失败", "Fail to get");
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to get");
            AfxMessageBox(szLan);
            return;
        }

        for (i = 0; i < iItemCount; i++)
        {

            m_listCtrlStreamMediaCfg.SetItemText(i, 3, (char*)pTempStreamMediaCfg->sUrl);

            CString strStatus;
            strStatus.Format("%d", *pStatus);
            m_listCtrlStreamMediaCfg.SetItemText(i, 4, strStatus);

            pStatus++;
            pTempStreamMediaCfg++;
        }
    }

    UpdateData(FALSE);
}

void CDlgStreamMediaCfg::OnClickListStreamMediaCfg(NMHDR* pNMHDR, LRESULT* pResult)
{
    int nItem = 0;
    CString strChannel;

    POSITION pos = m_listCtrlStreamMediaCfg.GetFirstSelectedItemPosition();
    if (pos == NULL)
        TRACE0("No items were selected!\n");
    else
    {
        nItem = m_listCtrlStreamMediaCfg.GetNextSelectedItem(pos);

        //显示信息
        m_csStreamID = m_listCtrlStreamMediaCfg.GetItemText(nItem, 1);
        m_csRelatedChannel = m_listCtrlStreamMediaCfg.GetItemText(nItem, 2);
        m_csUrl = m_listCtrlStreamMediaCfg.GetItemText(nItem, 3);
        m_csStatus = m_listCtrlStreamMediaCfg.GetItemText(nItem, 4);

        UpdateData(FALSE);
    }
    *pResult = 0;
}

