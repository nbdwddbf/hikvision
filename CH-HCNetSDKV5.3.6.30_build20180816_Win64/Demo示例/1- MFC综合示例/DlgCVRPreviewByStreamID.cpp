// DlgCVRPreviewByStreamID.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCVRPreviewByStreamID.h"
#include "afxdialogex.h"


// CDlgCVRPreviewByStreamID 对话框

STREAMID_PREVIEWINFO g_StreamIDPreviewInfo[1024];

IMPLEMENT_DYNAMIC(CDlgCVRPreviewByStreamID, CDialogEx)

void __stdcall PreviewRemoteConfigCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgCVRPreviewByStreamID *pThis = (CDlgCVRPreviewByStreamID*)pUserData;
    LPNET_DVR_STREAM_INFO lpStreamInfo = NULL;
    CString strTemp;
    HTREEITEM hRoot = pThis->m_treeStreamIDList.GetRootItem();
    HTREEITEM hStreamID = NULL;
    switch (dwType)
    {
    case NET_SDK_CALLBACK_TYPE_STATUS:
        g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Get stream id status[%d]", (DWORD)lpBuffer);
        break;
    case NET_SDK_CALLBACK_TYPE_DATA:
        lpStreamInfo = (LPNET_DVR_STREAM_INFO)lpBuffer;
        if (strlen((char*)lpStreamInfo->byID) == 0 && lpStreamInfo->dwChannel != 0xffffffff)
        {
            strTemp.Format("%d", lpStreamInfo->dwChannel);
            hStreamID = pThis->m_treeStreamIDList.InsertItem(strTemp, 1, 1, hRoot, TVI_LAST);
            pThis->m_treeStreamIDList.SetItemData(hStreamID, pThis->m_treeStreamIDList.GetCount() - 1);
            memset(&g_StreamIDPreviewInfo[pThis->m_treeStreamIDList.GetCount() - 1], 0, sizeof(STREAMID_PREVIEWINFO));
            g_StreamIDPreviewInfo[pThis->m_treeStreamIDList.GetCount() - 1].struPreviewInfo.lChannel = lpStreamInfo->dwChannel;
            break;
        }
        else
        {
            strTemp.Format("%s", lpStreamInfo->byID);
            hStreamID = pThis->m_treeStreamIDList.InsertItem(strTemp, 1, 1, hRoot, TVI_LAST);
            pThis->m_treeStreamIDList.SetItemData(hStreamID, pThis->m_treeStreamIDList.GetCount() - 1);
            memset(&g_StreamIDPreviewInfo[pThis->m_treeStreamIDList.GetCount() - 1], 0, sizeof(STREAMID_PREVIEWINFO));
            strncpy((char *)g_StreamIDPreviewInfo[pThis->m_treeStreamIDList.GetCount() - 1].struPreviewInfo.byStreamID, (const char*)lpStreamInfo->byID, sizeof(lpStreamInfo->byID));
            g_StreamIDPreviewInfo[pThis->m_treeStreamIDList.GetCount() - 1].struPreviewInfo.lChannel = 0xffffffff;
            break;
        }
    default:
        break;

    }

}

CDlgCVRPreviewByStreamID::CDlgCVRPreviewByStreamID(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCVRPreviewByStreamID::IDD, pParent)
{
    m_hLongCfgHandle = -1;
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_strStreamID = _T("");
    for (int i = 0; i < 4; i++)
    {
        m_szlPlayHandle[i] = -1;
    }
    m_iWinIndex = 0;
}

CDlgCVRPreviewByStreamID::~CDlgCVRPreviewByStreamID()
{
}

void CDlgCVRPreviewByStreamID::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_STREAM_ID, m_treeStreamIDList);
}


BEGIN_MESSAGE_MAP(CDlgCVRPreviewByStreamID, CDialogEx)
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_STREAM_ID, &CDlgCVRPreviewByStreamID::OnNMDblclkTreeStreamId)
    ON_NOTIFY(NM_CLICK, IDC_TREE_STREAM_ID, &CDlgCVRPreviewByStreamID::OnNMClickTreeStreamId)
    ON_WM_LBUTTONDOWN()
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgCVRPreviewByStreamID 消息处理程序

BOOL CDlgCVRPreviewByStreamID::OnInitDialog()
{
    CDialog::OnInitDialog();
    CreateTree();

    GetDlgItem(IDC_STATIC_PREVIEW1)->GetWindowRect(&m_rcPlayWnd1);
    ScreenToClient(&m_rcPlayWnd1);

    GetDlgItem(IDC_STATIC_PREVIEW2)->GetWindowRect(&m_rcPlayWnd2);
    ScreenToClient(&m_rcPlayWnd2);

    GetDlgItem(IDC_STATIC_PREVIEW3)->GetWindowRect(&m_rcPlayWnd3);
    ScreenToClient(&m_rcPlayWnd3);

    GetDlgItem(IDC_STATIC_PREVIEW4)->GetWindowRect(&m_rcPlayWnd4);
    ScreenToClient(&m_rcPlayWnd4);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
Function:	CreateTree
Desc:		create device tree
Input:
Output:
Return:
**********************************************************/
void CDlgCVRPreviewByStreamID::CreateTree(void)
{
    m_treeStreamIDList.DeleteAllItems();
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "流ID列表", "Stream ID List");
    HTREEITEM hRoot = m_treeStreamIDList.InsertItem(szLan, TREE_ALL, TREE_ALL);
    GetStreamSrc();
    m_treeStreamIDList.Expand(hRoot, TVE_EXPAND);
    m_treeStreamIDList.Expand(m_treeStreamIDList.GetRootItem(), TVE_EXPAND);
    UpdateData(FALSE);
}

void CDlgCVRPreviewByStreamID::GetStreamSrc()
{
    // TODO: Add your control notification handler code here
    //
    UpdateData(TRUE);
    char szLan[128] = { 0 };

    m_hLongCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_STREAM_INFO, NULL, 0, PreviewRemoteConfigCallback, this);
    if (-1 == m_hLongCfgHandle)
    {
        //g_StringLanType(szLan,"获取流信息失败","Fail to get stream info");
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to get stream info");
        return;
    }
    else
    {
        //g_StringLanType(szLan,"获取流信息成功","Get stream info success");
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Get Stream info");
        UpdateData(FALSE);
    }
}

void CDlgCVRPreviewByStreamID::OnNMDblclkTreeStreamId(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码
    *pResult = 0;
    HTREEITEM hSelect = m_treeStreamIDList.GetSelectedItem();
    if (NULL == hSelect)//it works to double click device tree only while preview
    {
        return;
    }
    if (hSelect == m_treeStreamIDList.GetRootItem())
    {
        return;
    }
    m_strStreamID = m_treeStreamIDList.GetItemText(hSelect);

    PlayStreamID(m_treeStreamIDList.GetItemData(hSelect), m_iWinIndex);
}


void CDlgCVRPreviewByStreamID::OnNMClickTreeStreamId(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码
    *pResult = 0;
    HTREEITEM hSelect = m_treeStreamIDList.GetSelectedItem();
    if (NULL == hSelect)//it works to double click device tree only while preview
    {
        return;
    }
    if (hSelect == m_treeStreamIDList.GetRootItem())
    {
        return;
    }
    m_strStreamID = m_treeStreamIDList.GetItemText(hSelect);
}

void CDlgCVRPreviewByStreamID::PlayStreamID(int iTreeIndex, int iWinIndex)
{
    // TODO: Add your control notification handler code here
    //
    if (iWinIndex < 0 || iWinIndex > 3)
    {
        return;
    }
    if (m_szlPlayHandle[iWinIndex] >= 0)
    {
        if (!NET_DVR_StopRealPlay(m_szlPlayHandle[iWinIndex]))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
            m_szlPlayHandle[iWinIndex] = -1;
            switch (iWinIndex)
            {
            case 0:
                GetDlgItem(IDC_STATIC_PREVIEW1)->RedrawWindow();
                break;
            case 1:
                GetDlgItem(IDC_STATIC_PREVIEW2)->RedrawWindow();
                break;
            case 2:
                GetDlgItem(IDC_STATIC_PREVIEW3)->RedrawWindow();
                break;
            case 3:
                GetDlgItem(IDC_STATIC_PREVIEW4)->RedrawWindow();
                break;
            default:
                break;
            }
        }
    }
    else
    {
        switch (iWinIndex)
        {
        case 0:
            g_StreamIDPreviewInfo[iTreeIndex].struPreviewInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PREVIEW1)->m_hWnd;
            break;
        case 1:
            g_StreamIDPreviewInfo[iTreeIndex].struPreviewInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PREVIEW2)->m_hWnd;
            break;
        case 2:
            g_StreamIDPreviewInfo[iTreeIndex].struPreviewInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PREVIEW3)->m_hWnd;
            break;
        case 3:
            g_StreamIDPreviewInfo[iTreeIndex].struPreviewInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PREVIEW4)->m_hWnd;
            break;
        default:
            break;
        }
        m_szlPlayHandle[iWinIndex] = NET_DVR_RealPlay_V40(m_lServerID, &g_StreamIDPreviewInfo[iTreeIndex].struPreviewInfo, NULL, NULL);
    }
}

void CDlgCVRPreviewByStreamID::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    CDialogEx::OnLButtonDown(nFlags, point);

    UpdateData(TRUE);

    if (m_rcPlayWnd1.PtInRect(point))
    {
        m_iWinIndex = 0;
    }
    else if (m_rcPlayWnd2.PtInRect(point))
    {
        m_iWinIndex = 1;
    }
    else if (m_rcPlayWnd3.PtInRect(point))
    {
        m_iWinIndex = 2;
    }
    else if (m_rcPlayWnd4.PtInRect(point))
    {
        m_iWinIndex = 3;
    }
    UpdateData(FALSE);
}


void CDlgCVRPreviewByStreamID::OnClose()
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    for (int i = 0; i < 4; i++)
    {
        if (m_szlPlayHandle[i] >= 0)
        {
            if (!NET_DVR_StopRealPlay(m_szlPlayHandle[i]))
            {
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
            }
            else
            {
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
            }
        }
    }
    CDialogEx::OnClose();
}
