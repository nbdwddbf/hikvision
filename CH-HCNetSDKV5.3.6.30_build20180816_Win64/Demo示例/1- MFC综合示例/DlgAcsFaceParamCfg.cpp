// DlgAcsFaceParamCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsFaceParamCfg.h"
#include "afxdialogex.h"

#define WM_MSG_SET_FACE_PARAM_FINISH 1002
#define WM_MSG_GET_FACE_PARAM_FINISH 1003
#define WM_MSG_ADD_FACE_PARAM_TOLIST 1004

void CALLBACK g_fSetFaceParamCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
void CALLBACK g_fGetFaceParamCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);

// CDlgAcsFaceParamCfg 对话框

IMPLEMENT_DYNAMIC(CDlgAcsFaceParamCfg, CDialog)

CDlgAcsFaceParamCfg::CDlgAcsFaceParamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsFaceParamCfg::IDD, pParent)
{
    m_csCardNo = _T("");
    m_csFacePath = _T("");
    m_dwFaceID = 0;
    m_dwFaceNum = 0;
    m_dwDataType = 0;

    m_lpRecordCardCfg = NULL;
    m_lSetFaceParamCfgHandle = -1;
    m_lGetFaceParamCfgHandle = -1;
    m_dwSendIndex = 0;
    m_lpNowSendFace = NULL;
    m_dwCardReaderNo = 0;
    memset(&m_struDelFaceParam, 0, sizeof(m_struDelFaceParam));
    memset(&m_struFaceParamOne, 0, sizeof(m_struFaceParamOne));
    memset(&m_struDelFace, 0, sizeof(m_struDelFace));
    bFailedFaceInfo = FALSE;
}

CDlgAcsFaceParamCfg::~CDlgAcsFaceParamCfg()
{
    if (m_lpRecordCardCfg != NULL)
    {
        for (int i = 0; i < 1000; i++)
        {
            if (m_lpRecordCardCfg[i] != NULL)
            {
                delete (LPNET_DVR_FACE_PARAM_CFG)m_lpRecordCardCfg[i];
            }
        }
        delete m_lpRecordCardCfg;
        m_lpRecordCardCfg = NULL;
    }
}

void CDlgAcsFaceParamCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_ENABLE_CARD_READER, m_treeEnableCardReader);
    DDX_Control(pDX, IDC_TREE_READER_STATUS, m_treeReaderStatus);
    DDX_Control(pDX, IDC_TREE_FACE_ID, m_treeDelFace);
    DDX_Control(pDX, IDC_LIST_FACE_CFG, m_listFaceParamCfg);
    DDX_Control(pDX, IDC_COMBO_MODE, m_comboDelMode);
    DDX_Check(pDX, IDC_CHECK_CLEAR_ALL_CARD, m_byClearAllCard);
    DDX_Text(pDX, IDC_EDIT_CARD, m_csCardNo);
    DDX_Text(pDX, IDC_EDIT_FACE_PATH, m_csFacePath);
    DDX_Text(pDX, IDC_EDIT_FACE_ID, m_dwFaceID);
    DDX_Text(pDX, IDC_EDIT_FACE_NUMBER, m_dwFaceNum);
    DDX_Text(pDX, IDC_EDIT_CARD_READER_NO, m_dwCardReaderNo);
    DDX_Control(pDX, IDC_COMBO_FACEDATATYPE, m_comboFaceDataType);
}

BOOL CDlgAcsFaceParamCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    char szLan[128] = { 0 };

    m_comboDelMode.SetCurSel(0);
    m_comboFaceDataType.SetCurSel(0);

    m_listFaceParamCfg.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "编号", "No");
    m_listFaceParamCfg.InsertColumn(0, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "人脸关联卡号", "Card No");
    m_listFaceParamCfg.InsertColumn(1, szLan, LVCFMT_LEFT, 160, -1);
    g_StringLanType(szLan, "人脸数据路径", "Face Data Path");
    m_listFaceParamCfg.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "人脸编号", "Face No");
    m_listFaceParamCfg.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "人脸数据类型", "Face Data TYPE");
	m_listFaceParamCfg.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "建模失败错误码", "Module failed error code");
    m_listFaceParamCfg.InsertColumn(5, szLan, LVCFMT_LEFT, 160, -1);
    //g_StringLanType(szLan, "建模失败描述", "Module failed error msg");
    //m_listFaceParamCfg.InsertColumn(6, szLan, LVCFMT_LEFT, 160, -1);

    CreateTree();

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgAcsFaceParamCfg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgAcsFaceParamCfg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_STOP, &CDlgAcsFaceParamCfg::OnBnClickedButtonStop)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgAcsFaceParamCfg::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgAcsFaceParamCfg::OnBnClickedButtonGet)
    ON_MESSAGE(WM_MSG_SET_FACE_PARAM_FINISH, OnMsgSetFaceParamCfgFinish)
    ON_MESSAGE(WM_MSG_GET_FACE_PARAM_FINISH, OnMsgGetFaceParamCfgFinish)
    ON_MESSAGE(WM_MSG_ADD_FACE_PARAM_TOLIST, OnMsgAddFaceParamCfgToList)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgAcsFaceParamCfg::OnBnClickedButtonDel)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FACE_CFG, &CDlgAcsFaceParamCfg::OnLvnItemchangedListFaceCfg)
    ON_BN_CLICKED(IDC_BTN_GET_FAILED_FACE_INFO, &CDlgAcsFaceParamCfg::OnBnClickedBtnGetFailedFaceInfo)
END_MESSAGE_MAP()

LRESULT CDlgAcsFaceParamCfg::OnMsgSetFaceParamCfgFinish(WPARAM wParam, LPARAM lParam)
{
    if (!NET_DVR_StopRemoteConfig(m_lSetFaceParamCfgHandle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig failed");
        return 0;
    }
    m_lSetFaceParamCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACE_PARAM_CFG Set finish");
    return 0;
}

LRESULT CDlgAcsFaceParamCfg::OnMsgGetFaceParamCfgFinish(WPARAM wParam, LPARAM lParam)
{
    NET_DVR_StopRemoteConfig(m_lGetFaceParamCfgHandle);
    m_lGetFaceParamCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Get finish");
    return 0;
}

LRESULT CDlgAcsFaceParamCfg::OnMsgAddFaceParamCfgToList(WPARAM wParam, LPARAM lParam)
{
    if (!lParam)
    {
        bFailedFaceInfo = FALSE;
        LPNET_DVR_FACE_PARAM_CFG lpCardCfg = (LPNET_DVR_FACE_PARAM_CFG)wParam;
        if (lpCardCfg->dwSize == 0)
        {
            return 0;
        }

        AddToFaceParamList(*lpCardCfg);
        delete lpCardCfg;
    }
    else
    {
        bFailedFaceInfo = TRUE;
        LPNET_DVR_FAILED_FACE_INFO lpInfo = (LPNET_DVR_FAILED_FACE_INFO)wParam;
        if (lpInfo->dwSize == 0)
        {
            return 0;
        }
        AddToList(*lpInfo);
        delete lpInfo;
    }

    UpdateData(FALSE);
    return 0;
}

void CDlgAcsFaceParamCfg::AddToList(const NET_DVR_FAILED_FACE_INFO& struFailedFaceInfo)
{
    char szLan[64] = { 0 };
    int iInsertIndex = m_listFaceParamCfg.GetItemCount() + 1;

    CString strItem = "";
    strItem.Format("%d", iInsertIndex);
    int iItemIndex = m_listFaceParamCfg.InsertItem(iInsertIndex, strItem);

    sprintf(szLan, "%s", struFailedFaceInfo.byCardNo);
    m_listFaceParamCfg.SetItemText(iItemIndex, 1, szLan);
    m_listFaceParamCfg.SetItemText(iItemIndex, 2, "/");
    m_listFaceParamCfg.SetItemText(iItemIndex, 3, "/");
    m_listFaceParamCfg.SetItemText(iItemIndex, 4, "/");

    sprintf(szLan, "%d", struFailedFaceInfo.byErrorCode);
    m_listFaceParamCfg.SetItemText(iItemIndex, 5, szLan);
    //sprintf(szLan, "%s", struFailedFaceInfo.byErrorMsg);
    //m_listFaceParamCfg.SetItemText(iItemIndex, 6, szLan);
}

// CDlgAcsFaceParamCfg 消息处理程序
void CDlgAcsFaceParamCfg::OnBnClickedButtonAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_FACE_PARAM_CFG struFaceParamCfg = { 0 };
    UpdateFaceParamCfg(struFaceParamCfg);
    AddToFaceParamList(struFaceParamCfg);
}


void CDlgAcsFaceParamCfg::OnBnClickedButtonStop()
{
    // TODO:  在此添加控件通知处理程序代码
    m_listFaceParamCfg.DeleteAllItems();
    LPDWORD lpArr = GetFaceParamCfgPoint();
    for (int i = 0; i < 1000; i++)
    {
        if (lpArr[i] == NULL)
        {
            return;
        }
        delete[](LPNET_DVR_FACE_PARAM_CFG)lpArr[i];
        lpArr[i] = NULL;
    }
    bFailedFaceInfo = FALSE;
}


void CDlgAcsFaceParamCfg::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lSetFaceParamCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSetFaceParamCfgHandle);
    }
    UpdateData(TRUE);
    NET_DVR_FACE_PARAM_COND struCond = { 0 };
    struCond.dwSize = sizeof(struCond);
    struCond.dwFaceNum = m_dwFaceNum;
    m_lSetFaceParamCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_SET_FACE_PARAM_CFG, &struCond, sizeof(struCond), g_fSetFaceParamCallback, this);
    if (m_lSetFaceParamCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACE_PARAM_CFG failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACE_PARAM_CFG success");
    }

    //发送第一张卡, 失败关闭连接
    m_dwSendIndex = 0;
    if (!SendFirstFace())
    {
        NET_DVR_StopRemoteConfig(m_lSetFaceParamCfgHandle);
        m_lSetFaceParamCfgHandle = -1;
    }
}


void CDlgAcsFaceParamCfg::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lGetFaceParamCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lGetFaceParamCfgHandle);
    }

    m_listFaceParamCfg.DeleteAllItems();
    LPDWORD lpArr = GetFaceParamCfgPoint();
    for (int i = 0; i < 1000; i++)
    {
        if (lpArr[i] == NULL)
        {
            break;
        }
        delete[](LPNET_DVR_FACE_PARAM_CFG)lpArr[i];
        lpArr[i] = NULL;
    }
    UpdateData(TRUE);
    NET_DVR_FACE_PARAM_COND struCond = { 0 };
    struCond.dwSize = sizeof(struCond);
    struCond.dwFaceNum = m_dwFaceNum;
    struCond.byFaceID = m_dwFaceID;
    
    memcpy(struCond.byCardNo, m_csCardNo.GetBuffer(m_csCardNo.GetLength()), m_csCardNo.GetLength());

    GetTreeSel();
    memcpy(struCond.byEnableCardReader, m_struFaceParamOne.byEnableCardReader, sizeof(m_struFaceParamOne.byEnableCardReader));
    
    m_lGetFaceParamCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_FACE_PARAM_CFG, &struCond, sizeof(struCond), g_fGetFaceParamCallback, this);
    if (m_lGetFaceParamCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACE_PARAM_CFG failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACE_PARAM_CFG success");
    }
}

BOOL CDlgAcsFaceParamCfg::UpdateFaceParamCfg(NET_DVR_FACE_PARAM_CFG &struFaceParamCfg)
{
    UpdateData(TRUE);
    struFaceParamCfg.byFaceDataType = m_comboFaceDataType.GetCurSel();
    struFaceParamCfg.dwSize = sizeof(struFaceParamCfg);
    memcpy(struFaceParamCfg.byCardNo, m_csCardNo.GetBuffer(m_csCardNo.GetLength()), m_csCardNo.GetLength());
    GetTreeSel();
    memcpy(struFaceParamCfg.byEnableCardReader, m_struFaceParamOne.byEnableCardReader, sizeof(struFaceParamCfg.byEnableCardReader));
    struFaceParamCfg.byFaceID = m_dwFaceID;
    memcpy(struFaceParamCfg.byRes, m_csFacePath.GetBuffer(m_csFacePath.GetLength()), m_csFacePath.GetLength());
    if (m_comboFaceDataType.GetCurSel() == 0)
    {
        m_dwDataType = ENUM_ACS_SEND_DATA;
    }
    if (m_comboFaceDataType.GetCurSel() == 1)
    {
        m_dwDataType = ENUM_ACS_INTELLIGENT_IDENTITY_DATA;
    }

    return TRUE;
}

void CDlgAcsFaceParamCfg::CreateTree()
{
    CString strTemp = _T("");

    int i = 0;
    m_treeEnableCardReader.DeleteAllItems();

    HTREEITEM hChanItem = NULL;
    HTREEITEM hFirstItem = NULL;

    for (i = 0; i < sizeof(m_struFaceParamOne.byEnableCardReader); i++)
    {
        strTemp.Format("CardReader %d", i + 1);
        hChanItem = m_treeEnableCardReader.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeEnableCardReader.SetItemData(hChanItem, i);

        if (m_struFaceParamOne.byEnableCardReader[i])
        {
            m_treeEnableCardReader.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeEnableCardReader.SelectItem(hFirstItem);
    m_treeEnableCardReader.Expand(m_treeEnableCardReader.GetRootItem(), TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeDelFace.DeleteAllItems();
    for (i = 0; i < sizeof(m_struDelFace.struProcessMode.struByCard.byFaceID); i++)
    {
        strTemp.Format("id %d", i + 1);
        hChanItem = m_treeDelFace.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeDelFace.SetItemData(hChanItem, i);

        if (m_struDelFace.struProcessMode.struByCard.byFaceID[i])
        {
            m_treeDelFace.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeDelFace.SelectItem(hFirstItem);
    m_treeDelFace.Expand(m_treeDelFace.GetRootItem(), TVE_EXPAND);
}

void CDlgAcsFaceParamCfg::GetTreeSel()
{
    UpdateData(TRUE);
    memset(&m_struFaceParamOne.byEnableCardReader, 0, sizeof(m_struFaceParamOne.byEnableCardReader));

    int i = 0;
    HTREEITEM hTreeItem;

    BOOL bCheck;
    DWORD dwIndex;
    DWORD dwCount = 0;
    CTreeCtrl *treeCtr = &m_treeEnableCardReader;
    dwCount = m_treeEnableCardReader.GetCount();
    hTreeItem = m_treeEnableCardReader.GetRootItem();

    for (i = 0; i < dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struFaceParamOne.byEnableCardReader[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
    }

    memset(&m_struDelFaceParam.struProcessMode.struByCard.byFaceID, 0, sizeof(m_struDelFaceParam.struProcessMode.struByCard.byFaceID));
    treeCtr = &m_treeDelFace;
    hTreeItem = m_treeDelFace.GetRootItem();
    dwCount = m_treeDelFace.GetCount();
    for (i = 0; i < dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struDelFaceParam.struProcessMode.struByCard.byFaceID[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
    }
}

void CDlgAcsFaceParamCfg::SetTreeSel(NET_DVR_FACE_PARAM_CFG *struFaceParamCfg)
{
    memset(&m_struFaceParamOne.byEnableCardReader, 0, sizeof(m_struFaceParamOne.byEnableCardReader));

    int i = 0;
    HTREEITEM hTreeItem;

    DWORD dwCount = 0;
    CTreeCtrl *treeCtr = &m_treeEnableCardReader;
    dwCount = m_treeEnableCardReader.GetCount();
    hTreeItem = m_treeEnableCardReader.GetRootItem();

    for (i = 0; i < dwCount; i++)
    {
        treeCtr->SetCheck(hTreeItem, struFaceParamCfg->byEnableCardReader[i]);
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
    }

    UpdateData(FALSE);
}

void CDlgAcsFaceParamCfg::AddToFaceParamList(const NET_DVR_FACE_PARAM_CFG& struCardInfo)
{
    LPNET_DVR_FACE_PARAM_CFG pCardInfo = NULL;
    int iItemIndex = GetExistItem(&struCardInfo);
    if (iItemIndex == -1)
    {
        pCardInfo = new NET_DVR_FACE_PARAM_CFG;
        if (pCardInfo == NULL)
        {
            return;
        }
        int iSize = sizeof(NET_DVR_FACE_PARAM_CFG);
        int nItemCount = m_listFaceParamCfg.GetItemCount();

        CString strItem = "";
        strItem.Format("%d", nItemCount + 1);
        iItemIndex = m_listFaceParamCfg.InsertItem(nItemCount, strItem);
        m_listFaceParamCfg.SetItemData(nItemCount, (DWORD)pCardInfo);
    }
    else
    {
        pCardInfo = (LPNET_DVR_FACE_PARAM_CFG)m_listFaceParamCfg.GetItemData(iItemIndex);
    }
    memcpy(pCardInfo, &struCardInfo, sizeof(struCardInfo));
    UpdateList(iItemIndex, *pCardInfo);
    LPDWORD lpArr = GetFaceParamCfgPoint();
    lpArr[iItemIndex] = (DWORD)pCardInfo;

}

int CDlgAcsFaceParamCfg::GetExistItem(const NET_DVR_FACE_PARAM_CFG *lpCardCfg)
{
    int nItemCount = m_listFaceParamCfg.GetItemCount();
    int i = 0;
    LPNET_DVR_FACE_PARAM_CFG lpTemp = NULL;
    for (i = 0; i < nItemCount; i++)
    {
        lpTemp = (LPNET_DVR_FACE_PARAM_CFG)m_listFaceParamCfg.GetItemData(i);
        if (!lpCardCfg)
        {
            continue;
        }
        if (strcmp((char *)lpCardCfg->byCardNo, (char *)lpTemp->byCardNo) == 0 && lpCardCfg->byFaceID == lpTemp->byFaceID)
        {
            return i;
        }
    }
    return -1;
}

void CDlgAcsFaceParamCfg::UpdateList(int iInsertIndex, const NET_DVR_FACE_PARAM_CFG& m_struFaceParamCfg)
{
    char szLan[1024] = { 0 };

    sprintf(szLan, "%d", iInsertIndex);
    sprintf(szLan, "%s", m_struFaceParamCfg.byCardNo);
    m_listFaceParamCfg.SetItemText(iInsertIndex, 1, szLan);
    sprintf(szLan, "%s", m_struFaceParamCfg.byRes);
    m_listFaceParamCfg.SetItemText(iInsertIndex, 2, szLan);
    sprintf(szLan, "%d", m_struFaceParamCfg.byFaceID);
    m_listFaceParamCfg.SetItemText(iInsertIndex, 3, szLan);
    sprintf(szLan, "%d", m_struFaceParamCfg.byFaceDataType);
	m_listFaceParamCfg.SetItemText(iInsertIndex, 4, szLan);

    m_listFaceParamCfg.SetItemText(iInsertIndex, 5, "/");
    //m_listFaceParamCfg.SetItemText(iInsertIndex, 6, "/");
}

LPDWORD CDlgAcsFaceParamCfg::GetFaceParamCfgPoint()
{
    if (!m_lpRecordCardCfg)
    {
        const int iMaxCardNum = 1000;
        m_lpRecordCardCfg = new DWORD[iMaxCardNum];
        memset(m_lpRecordCardCfg, 0, sizeof(DWORD)*iMaxCardNum);
    }
    return m_lpRecordCardCfg;
}

BOOL CDlgAcsFaceParamCfg::SendFirstFace()
{
    if (m_lSetFaceParamCfgHandle == -1)
    {
        return FALSE;
    }
    
    m_dwSendIndex = 0;
    if (m_listFaceParamCfg.GetItemCount() < 1)
    {
        return FALSE;
    }
    LPDWORD lpArr = GetFaceParamCfgPoint();
    m_lpNowSendFace = (LPNET_DVR_FACE_PARAM_CFG)lpArr[m_dwSendIndex];
    /*m_lpNowSendFace = new NET_DVR_FACE_PARAM_CFG;
    memset(m_lpNowSendFace, 0, sizeof(NET_DVR_FACE_PARAM_CFG));
    m_lpNowSendFace->dwSize = sizeof(NET_DVR_FACE_PARAM_CFG);
    m_lpNowSendFace->byFaceID = 1;
    m_lpNowSendFace->byEnableCardReader[0] = 1;
    memset(m_lpNowSendFace->byCardNo, 49, 10);*/

    /*FILE* fp = NULL;
    char szPath[1024] = { 0 };
    int iInsertIndex = 5;
    sprintf(szPath, "%d_facedata.dat", iInsertIndex);
    fp = fopen(szPath, "wb");
    if (fp == NULL)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "fopen write failed");
    }

    m_lpNowSendFace->pFaceBuffer = new char[1500];
    memset(m_lpNowSendFace->pFaceBuffer, 5, 1500);
    m_lpNowSendFace->dwFaceLen = 1500;

    fwrite(m_lpNowSendFace->pFaceBuffer, m_lpNowSendFace->dwFaceLen, 1, fp);
    fclose(fp);*/

    m_lpNowSendFace->pFaceBuffer = new char[200 * 1024];

    FILE* fp = NULL;
    fp = fopen((const char *)m_lpNowSendFace->byRes, "rb"); //只供读取
    if (fp == NULL)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "HPR_ReadFile failed");
        return TRUE;
    }
    fseek(fp, 0L, SEEK_END);
    int len = ftell(fp);
    if (len >= 200 * 1024)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Face picture too big, exceed 200k");
        return FALSE;
    }
    m_lpNowSendFace->dwFaceLen = len;
    rewind(fp);
    fread(m_lpNowSendFace->pFaceBuffer, 1, m_lpNowSendFace->dwFaceLen, fp);
    fclose(fp);

    /*m_lpNowSendFace->pFaceBuffer = new char[1500];
    memset(m_lpNowSendFace->pFaceBuffer, 1, 1500);
    m_lpNowSendFace->dwFaceLen = 1500;*/
    if (!NET_DVR_SendRemoteConfig(m_lSetFaceParamCfgHandle, m_dwDataType, (char *)m_lpNowSendFace, sizeof(*m_lpNowSendFace)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendFace->byCardNo);
        if (m_lpNowSendFace->pFaceBuffer != NULL)
        {
            delete[] m_lpNowSendFace->pFaceBuffer;
        }
        m_lpNowSendFace->pFaceBuffer = NULL;
        return FALSE;
    }
    if (m_lpNowSendFace->pFaceBuffer != NULL)
    {
        delete[] m_lpNowSendFace->pFaceBuffer;
    }
    m_lpNowSendFace->pFaceBuffer = NULL;
    return TRUE;
}

BOOL CDlgAcsFaceParamCfg::SendNextFace()
{
    if (m_lSetFaceParamCfgHandle == -1)
    {
        return FALSE;
    }

    LPDWORD lpArr = GetFaceParamCfgPoint();

    m_dwSendIndex++;
    if (m_dwSendIndex >= m_listFaceParamCfg.GetItemCount())
    {
        return TRUE;
    }
    if (lpArr == NULL)
    {
        return FALSE;
    }
    m_lpNowSendFace = (LPNET_DVR_FACE_PARAM_CFG)lpArr[m_dwSendIndex];

    m_lpNowSendFace->pFaceBuffer = new char[200 * 1024];

    FILE* fp = NULL;
    fp = fopen((const char *)m_lpNowSendFace->byRes, "rb"); //只供读取
    if (fp == NULL)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "HPR_ReadFile failed");
        return TRUE;
    }
    fseek(fp, 0L, SEEK_END);
    int len = ftell(fp);
    if (len >= 200 * 1024)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Face picture too big, exceed 200k");
        return FALSE;
    }
    m_lpNowSendFace->dwFaceLen = len;
    rewind(fp);
    fread(m_lpNowSendFace->pFaceBuffer, 1, m_lpNowSendFace->dwFaceLen, fp);
    fclose(fp);
    
    /*m_lpNowSendFace = new NET_DVR_FACE_PARAM_CFG;
    memset(m_lpNowSendFace, 0, sizeof(NET_DVR_FACE_PARAM_CFG));
    m_lpNowSendFace->dwSize = sizeof(NET_DVR_FACE_PARAM_CFG);
    m_lpNowSendFace->byFaceID = 1;
    m_lpNowSendFace->byEnableCardReader[0] = 1;
    memset(m_lpNowSendFace->byCardNo, 49, 10);*/
    /*m_lpNowSendFace->pFaceBuffer = new char[1500];
    memset(m_lpNowSendFace->pFaceBuffer, 1, 1500);
    m_lpNowSendFace->dwFaceLen = 1500;*/
    if (!NET_DVR_SendRemoteConfig(m_lSetFaceParamCfgHandle, m_dwDataType, (char *)m_lpNowSendFace, sizeof(*m_lpNowSendFace)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendFace->byCardNo);
        if (m_lpNowSendFace->pFaceBuffer != NULL)
        {
            delete[] m_lpNowSendFace->pFaceBuffer;
        }
        m_lpNowSendFace->pFaceBuffer = NULL;
        //发送失败  关闭连接
        PostMessage(WM_MSG_SET_FACE_PARAM_FINISH, 0, 0);
        return FALSE;
    }
    if (m_lpNowSendFace->pFaceBuffer != NULL)
    {
        delete[] m_lpNowSendFace->pFaceBuffer;
    }
    m_lpNowSendFace->pFaceBuffer = NULL;
    return TRUE;
}

void CALLBACK g_fSetFaceParamCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAcsFaceParamCfg* pDlg = (CDlgAcsFaceParamCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessSetFaceParamCfgCallbackData(dwType, lpBuffer, dwBufLen);
}

void CALLBACK g_fGetFaceParamCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAcsFaceParamCfg* pDlg = (CDlgAcsFaceParamCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetFaceParamCfgCallbackData(dwType, lpBuffer, dwBufLen);
}

void CALLBACK g_fGetFailedFaceInfoCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAcsFaceParamCfg* pDlg = (CDlgAcsFaceParamCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetFailedFaceInfoCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgAcsFaceParamCfg::ProcessGetFailedFaceInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_FAILED_FACE_INFO lpCardCfg = new NET_DVR_FAILED_FACE_INFO;
        memcpy(lpCardCfg, lpBuffer, sizeof(*lpCardCfg));
        PostMessage(WM_MSG_ADD_FACE_PARAM_TOLIST, (WPARAM)lpCardCfg, 1);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_GET_FACE_PARAM_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            //0-表示未知错误
            DWORD dwErrCode = 0;
            if (dwBufLen == 8)
            {
                dwErrCode = *(DWORD*)((char *)lpBuffer + 4);
            }
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetFailedFace(after upgrade device) STATUS_FAILED, Error code %d", dwErrCode);
        }
    }
}

void CDlgAcsFaceParamCfg::ProcessSetFaceParamCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
            strncpy(szCardNumber, (char*)(lpBuffer)+4, ACS_CARD_NO_LEN);
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetFaceParam PROCESSING %s", szCardNumber);

            SendNextFace();
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "SetFaceParam Err:NET_SDK_CALLBACK_STATUS_FAILED");

            SendNextFace();
        }
        //下面两个关闭长连接
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetFaceParam SUCCESS");
            PostMessage(WM_MSG_SET_FACE_PARAM_FINISH, 0, 0);

        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetFaceParam Exception");
            PostMessage(WM_MSG_SET_FACE_PARAM_FINISH, 0, 0);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetFaceParam SUCCESS");
            PostMessage(WM_MSG_SET_FACE_PARAM_FINISH, 0, 0);
        }

    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_FACE_PARAM_STATUS struCfg = { 0 };
        memcpy(&struCfg, lpBuffer, sizeof(struCfg));

        int i;
        BOOL bSendOk = FALSE;
        for (i = 0; i < sizeof(struCfg.byCardReaderRecvStatus); i++)
        {
            if (struCfg.byCardReaderRecvStatus[i] == 1)
            {
                bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetFaceParam PROCESSING,CardNo:%s", struCfg.byCardNo);
            }
        }
        if (!bSendOk)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "SetFaceParam Failed,CardNo:%s", struCfg.byCardNo);
        }

        SendNextFace();
    }
}

void CDlgAcsFaceParamCfg::ProcessGetFaceParamCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_FACE_PARAM_CFG lpCardCfg = new NET_DVR_FACE_PARAM_CFG;
        memcpy(lpCardCfg, lpBuffer, sizeof(*lpCardCfg));

        int i;
        BOOL bSendOk = FALSE;
        for (i = 0; i < sizeof(lpCardCfg->byEnableCardReader); i++)
        {
            if (lpCardCfg->byEnableCardReader[i] == 1)
            {
                bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GetFaceParam PROCESSING %s,CardReader %d", lpCardCfg->byCardNo, i);
            }
        }
        if (!bSendOk)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetFaceParam Failed,CardNo:%s", lpCardCfg->byCardNo);
        }

        FILE* fp = NULL;
        char szPath[1024] = { 0 };
        sprintf(szPath, "%s_%d_facedata.dat", lpCardCfg->byCardNo, lpCardCfg->byFaceID);
        m_csFacePath = szPath;
        memcpy(lpCardCfg->byRes, m_csFacePath.GetBuffer(), m_csFacePath.GetLength());
        fp = fopen(m_csFacePath, "wb");
        if (fp == NULL)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "fopen write failed");
        }

        fwrite(lpCardCfg->pFaceBuffer, lpCardCfg->dwFaceLen, 1, fp);
        fclose(fp);

        PostMessage(WM_MSG_ADD_FACE_PARAM_TOLIST, (WPARAM)lpCardCfg, 0);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_GET_FACE_PARAM_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            //0-表示未知错误
            DWORD dwErrCode = 0;
            if (dwBufLen == 8)
            {
                dwErrCode = *(DWORD*)((char *)lpBuffer + 4);
            }
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetFace STATUS_FAILED, Error code %d", dwErrCode);
        }
    }
}


void CDlgAcsFaceParamCfg::OnBnClickedButtonDel()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE); 
    NET_DVR_FACE_PARAM_CTRL struDelCfg;
    memset(&struDelCfg, 0, sizeof(NET_DVR_FACE_PARAM_CTRL));
    struDelCfg.dwSize = sizeof(NET_DVR_FACE_PARAM_CTRL);
    struDelCfg.byMode = m_comboDelMode.GetCurSel();
    if (struDelCfg.byMode == 0)
    {
        memcpy(struDelCfg.struProcessMode.struByCard.byCardNo, m_csCardNo.GetBuffer(m_csCardNo.GetLength()), m_csCardNo.GetLength());
        GetTreeSel();
        memcpy(struDelCfg.struProcessMode.struByCard.byEnableCardReader, m_struFaceParamOne.byEnableCardReader, sizeof(m_struFaceParamOne.byEnableCardReader));
        memcpy(struDelCfg.struProcessMode.struByCard.byFaceID, m_struDelFaceParam.struProcessMode.struByCard.byFaceID, sizeof(m_struDelFaceParam.struProcessMode.struByCard.byFaceID));
    } 
    else
    {
        struDelCfg.struProcessMode.struByReader.dwCardReaderNo = m_dwCardReaderNo;
        struDelCfg.struProcessMode.struByReader.byClearAllCard = m_byClearAllCard;
        memcpy(struDelCfg.struProcessMode.struByReader.byCardNo, m_csCardNo.GetBuffer(m_csCardNo.GetLength()), m_csCardNo.GetLength());
    }
    if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_DEL_FACE_PARAM_CFG, &struDelCfg, sizeof(struDelCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_FACE_PARAM_CFG FAILED");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_FACE_PARAM_CFG SUCC");
    }
}


void CDlgAcsFaceParamCfg::OnLvnItemchangedListFaceCfg(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    if (LVIF_STATE == pNMLV->uChanged && (pNMLV->uNewState & LVIS_SELECTED))
    {
        int iItemIndex = pNMLV->iItem;
        if (-1 != iItemIndex && !bFailedFaceInfo)
        {
            LPNET_DVR_FACE_PARAM_CFG pCardInfo = (LPNET_DVR_FACE_PARAM_CFG)m_listFaceParamCfg.GetItemData(iItemIndex);
            m_csCardNo = pCardInfo->byCardNo;
            m_csFacePath = pCardInfo->byRes;
            m_dwFaceID = pCardInfo->byFaceID;
            m_comboFaceDataType.SetCurSel(pCardInfo->byFaceDataType);
            SetTreeSel(pCardInfo);
            UpdateData(FALSE);
        }
    }

    *pResult = 0;
}


void CDlgAcsFaceParamCfg::OnBnClickedBtnGetFailedFaceInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lGetFaceParamCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lGetFaceParamCfgHandle);
    }

    m_listFaceParamCfg.DeleteAllItems();
    LPDWORD lpArr = GetFaceParamCfgPoint();
    for (int i = 0; i < 1000; i++)
    {
        if (lpArr[i] == NULL)
        {
            break;
        }
        delete[](LPNET_DVR_FACE_PARAM_CFG)lpArr[i];
        lpArr[i] = NULL;
    }
    UpdateData(TRUE);


    NET_DVR_FAILED_FACE_COND struCond = { 0 };
    struCond.dwSize = sizeof(struCond);

    m_lGetFaceParamCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_FAILED_FACE_INFO, &struCond, sizeof(struCond), g_fGetFailedFaceInfoCallback, this);
    if (m_lGetFaceParamCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FAILED_FACE_INFO failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FAILED_FACE_INFO success");
    }
}
