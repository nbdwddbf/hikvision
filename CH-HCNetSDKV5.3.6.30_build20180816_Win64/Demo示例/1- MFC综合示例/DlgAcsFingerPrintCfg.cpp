// DlgAcsFingerPrintCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsFingerPrintCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CALLBACK g_fSetFingerPrintCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
void CALLBACK g_fGetFingerPrintCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
UINT __cdecl  g_fSendFingerPrintCfgThread(LPVOID pParam);
UINT __cdecl  g_fShowFingerPrintListThread(LPVOID pParam);
#define WM_MSG_SET_FINGERPRINT_FINISH 1002
#define WM_MSG_GET_FINGERPRINT_FINISH 1003
#define WM_MSG_ADD_FINGERPRINT_TOLIST 1004
#define WM_MSG_UPDATEDATA_INTERFACE   1005
#define WM_DEL_FINGER_PRINT_FINISH    1006

/////////////////////////////////////////////////////////////////////////////
// DlgAcsFingerPrintCfg dialog


DlgAcsFingerPrintCfg::DlgAcsFingerPrintCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsFingerPrintCfg::IDD, pParent)
    , m_dwNowSendItem(0)
    , m_iSelListItem(-1)
    , m_lpRecordCardCfg(NULL)
    ,m_pDisplayListThread(NULL)
    ,m_dwBatchAddNum(0)
    ,m_lpNowSendCard(NULL)
	,m_byLastCardSendTime(0)
{
	//{{AFX_DATA_INIT(DlgAcsFingerPrintCfg)
    m_byClearAllCard = FALSE;
    m_byCallbackMode = FALSE;
    m_sCardNo = _T("");
    m_sFingerPrintPath = _T("");
    m_byFingerPrintID = 0;
	m_dwFingerPrintLen = 0;
    m_dwCardReaderNo = 0;
    m_dwCardNum = 0;
    //}}AFX_DATA_INIT
    m_lSetFingerPrintCfgHandle = -1;
    m_lGetFingerPrintCfgHandle = -1;
    m_hStopProcEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
    m_pProcThread = NULL;
}

DlgAcsFingerPrintCfg::~DlgAcsFingerPrintCfg()
{
    CloseHandle(m_hStopProcEvent);
    
    if (m_pProcThread != NULL && !m_pProcThread->m_bAutoDelete)
    {
        delete m_pProcThread;
    }
    
    if ( m_lpRecordCardCfg )
    {
        LPDWORD lpArr = m_lpRecordCardCfg;
        //         for (int i=0; i<m_dwCardNum; i++)
        //         {
        //             delete (LPNET_DVR_CARD_PASSWD_CFG)lpArr[i]; 
        //         }
        delete [] m_lpRecordCardCfg; 
    }
}

void DlgAcsFingerPrintCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsFingerPrintCfg)
	DDX_Control(pDX, IDC_LIST_FINGER_PRINT_CFG, m_listFingerPrintCfg);
	DDX_Control(pDX, IDC_COMBO_FINGER_TYPE, m_comboFingerType);
    DDX_Control(pDX, IDC_TREE_ENABLE_CARD_READER, m_treeEnableCardReader);
    DDX_Control(pDX, IDC_TREE_FINGER_PRINT_ID, m_treeDelFingerPrint);
    DDX_Control(pDX, IDC_COMBO_MODE, m_comboDelMode);
    DDX_Check(pDX, IDC_CHECK_CLEAR_ALL_CARD, m_byClearAllCard);
    DDX_Check(pDX, IDC_CHECK_NO_BLOCK, m_byCallbackMode);
    DDX_Text(pDX, IDC_EDIT_FINGER_PRINT_ID, m_byFingerPrintID);
    DDX_Text(pDX, IDC_EDIT_FINGER_PRINT_LENGTH, m_dwFingerPrintLen);
    DDX_Text(pDX, IDC_EDIT_CARD, m_sCardNo);
    DDX_Text(pDX, IDC_EDIT_FINGER_PRINT_PATH, m_sFingerPrintPath);
    DDX_Text(pDX, IDC_EDIT_FINGER_PRINT_NUMBER, m_dwCardNum);
    DDX_Text(pDX, IDC_EDIT_CARD_READER_NO, m_dwCardReaderNo);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsFingerPrintCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsFingerPrintCfg)
    //ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnBtnSetFingerPrintcfg)
    ON_BN_CLICKED(IDC_BUTTON_GET, OnBtnGetAllFingerPrint)
    ON_BN_CLICKED(IDC_BUTTON_ADD, OnBtnAddToList)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBtnDel)
    ON_NOTIFY(NM_CLICK, IDC_TREE_ENABLE_CARD_READER, OnClickTreeEnableCardReader)
    ON_NOTIFY(NM_CLICK, IDC_TREE_FINGER_PRINT_ID, OnClickTreeDelFingerPrint)
    ON_BN_CLICKED(IDC_BUTTON_STOP, OnBtnStopSend)

    ON_WM_CLOSE()
    ON_WM_DESTROY()
    ON_MESSAGE(WM_MSG_SET_FINGERPRINT_FINISH,OnMsgSetFingerPrintCfgFinish)
    ON_MESSAGE(WM_MSG_GET_FINGERPRINT_FINISH,OnMsgGetFingerPrintCfgFinish)
    ON_MESSAGE(WM_MSG_ADD_FINGERPRINT_TOLIST,OnMsgAddFingerPrintCfgToList)
    ON_MESSAGE(WM_DEL_FINGER_PRINT_FINISH, OnMsgDelFingerPrintFinish)
    ON_MESSAGE(WM_MSG_UPDATEDATA_INTERFACE,OnMsgUpdateData)
	//ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)	
	ON_NOTIFY(NM_CLICK, IDC_LIST_FINGER_PRINT_CFG, OnClickListScreen)
	//ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
    //}}AFX_MSG_MAP
    END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsFingerPrintCfg message handlers

LRESULT DlgAcsFingerPrintCfg::OnMsgDelFingerPrintFinish(WPARAM wParam, LPARAM lParam)
{
    DWORD dwType = (DWORD)wParam;
    char szLan[256] = { 0 };

    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_FINGER_PRINT_INFO_STATUS_V50 pStruCaptureFace = (LPNET_DVR_FINGER_PRINT_INFO_STATUS_V50)lParam;

        sprintf(szLan, "Device delete finger print status is:[%d], card reader no is:[%d]", pStruCaptureFace->byStatus, pStruCaptureFace->dwCardReaderNo);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szLan);

        UpdateData(FALSE);

    }
    else
    {
        if (!NET_DVR_StopRemoteConfig(m_lRemoteHandle))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig");
            m_lRemoteHandle = -1;
        }

    }

    return NULL;
}

BOOL DlgAcsFingerPrintCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_dwCount = 0;
	m_dwDispNum = 0;
	m_iCurSel = -1;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan)); 
	memset(m_lDispChan, 0, sizeof(m_lDispChan));
	memset(m_lDispChanSet, 0, sizeof(m_lDispChanSet));
	memset(m_dwStatus, 0, sizeof(m_dwStatus));
	memset(m_struFingerPrintCfg, 0, sizeof(m_struFingerPrintCfg));
	memset(&m_struAblity, 0, sizeof(m_struAblity));
	memset(&m_struFingerPrintCfgSet, 0, sizeof(m_struFingerPrintCfgSet));

    m_lPapamCount = 0; 
    m_lRecordCount = 0; 
	memset(&m_struOutput, 0, sizeof(m_struOutput));
	memset(&m_struOutputSet, 0, sizeof(m_struOutputSet));
	memset(&m_lDispOutputSet, 0, sizeof(m_lDispOutputSet));
    memset(m_dwRecordPapam, 0, sizeof(m_dwRecordPapam)); 
	m_dwOutputSet = 0;
	CString tmp;
	int i = 0;
    int ChanNo = -1;
    char szLan[128] = {0};

	
	m_listFingerPrintCfg.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "编号", "DispChan No.");
	m_listFingerPrintCfg.InsertColumn(0, szLan, LVCFMT_LEFT,80, -1);	
    g_StringLanType(szLan, "指纹关联卡号", "VideoWall No.");
    m_listFingerPrintCfg.InsertColumn(1, szLan,LVCFMT_LEFT,80, -1); 


	g_StringLanType(szLan, "指纹编号", "Fingerprint Num");
	m_listFingerPrintCfg.InsertColumn(2, szLan,LVCFMT_LEFT,80,-1);

	g_StringLanType(szLan, "指纹类型", "Fingerprint Type");
    m_listFingerPrintCfg.InsertColumn(3, szLan,LVCFMT_LEFT,80,-1);	




	g_StringLanType(szLan, "指纹数据长度", "Enable");
	m_listFingerPrintCfg.InsertColumn(4, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "指纹图片路径", "LinkMode");
    m_listFingerPrintCfg.InsertColumn(5, szLan,LVCFMT_LEFT,120,-1);

    m_comboFingerType.ResetContent();
	g_StringLanType(szLan, "普通指纹", "Common Fingerprint");
    m_comboFingerType.InsertString(0,szLan);
	g_StringLanType(szLan, "胁迫指纹", "Duress Fingerprint");
    m_comboFingerType.InsertString(1,szLan);
    m_comboFingerType.SetCurSel(0);

    m_comboDelMode.ResetContent();
	g_StringLanType(szLan, "按卡号删除", "Delete by CardNum");
    m_comboDelMode.InsertString(0,szLan);
	g_StringLanType(szLan, "按读卡器删除", "Delete by CardReader");
    m_comboDelMode.InsertString(1,szLan);
    m_comboDelMode.SetCurSel(0);


    CreateTree();

//	OnBtnGetAll();
  
	i = 0;
    //OnBtnGetAll(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAcsFingerPrintCfg::OnClose()
{
    static BOOL bNotifyQuit = FALSE;
    if ((m_pProcThread   != NULL &&  WaitForSingleObject(m_pProcThread->m_hThread,0) != WAIT_OBJECT_0))
    {  
        if (!bNotifyQuit)
        {
            SetEvent(m_hStopProcEvent);
            if (m_pProcThread != NULL)
            {
                m_pProcThread->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
            }
            
            PostMessage(WM_CLOSE);
            bNotifyQuit = TRUE;
        }
        PostMessage(WM_CLOSE);
        return;
    }
    
    bNotifyQuit = FALSE;
    CDialog::OnClose();
}

void DlgAcsFingerPrintCfg::OnDestroy()
{
    StopProcThread();
    CDialog::OnDestroy();
}

LRESULT DlgAcsFingerPrintCfg::OnMsgSetFingerPrintCfgFinish(WPARAM wParam,LPARAM lParam)
{   
    NET_DVR_StopRemoteConfig(m_lSetFingerPrintCfgHandle);
    m_lSetFingerPrintCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FINGERPRINT_CFG Set finish");
    //ShowSelListItem(); 
    return 0;
}

LRESULT DlgAcsFingerPrintCfg::OnMsgGetFingerPrintCfgFinish(WPARAM wParam,LPARAM lParam)
{
    NET_DVR_StopRemoteConfig(m_lGetFingerPrintCfgHandle);
    m_lGetFingerPrintCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FINGERPRINT_CFG Get finish");
    //ShowSelListItem(); 
    return 0;
}

LRESULT DlgAcsFingerPrintCfg::OnMsgAddFingerPrintCfgToList(WPARAM wParam,LPARAM lParam)
{
    LPNET_DVR_FINGER_PRINT_CFG lpCardCfg = (LPNET_DVR_FINGER_PRINT_CFG)wParam; 
    if ( lpCardCfg->dwSize == 0)
    {
        return 0; 
    }
    AddToFingerPrintList(*lpCardCfg); 
    delete lpCardCfg; 
    return 0; 
}

LRESULT DlgAcsFingerPrintCfg::OnMsgUpdateData(WPARAM wParam,LPARAM lParam)
{
    DWORD dwTrue = (DWORD)wParam; 
    UpdateData(dwTrue); 
    return 0; 
}

BOOL DlgAcsFingerPrintCfg::StartProcThread()
{
    if (m_pProcThread != NULL)
    {
        StopProcThread();
    }
    m_pProcThread = AfxBeginThread(g_fSendFingerPrintCfgThread,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);
    if (m_pProcThread != NULL)
    {
        m_pProcThread->m_bAutoDelete = FALSE;
        m_pProcThread->ResumeThread();
    }
    BOOL bResult =  m_pProcThread != NULL;
    return bResult;
}

BOOL DlgAcsFingerPrintCfg::StopProcThread()
{
    BOOL bResult = TRUE;	
    if (m_pProcThread != NULL)
    {   
        DWORD dwResult = WaitForSingleObject(m_pProcThread->m_hThread,5 * 1000);
        if (dwResult == WAIT_TIMEOUT)
        {   
            DWORD dwExitCode = 0;
            if (GetExitCodeThread(m_pProcThread->m_hThread,&dwExitCode) && dwExitCode == STILL_ACTIVE)
            {   
                bResult = TerminateThread(m_pProcThread->m_hThread,0);
            }
        }		
        if (bResult)
        {
            if (!m_pProcThread->m_bAutoDelete)
            {
                delete m_pProcThread;
                m_pProcThread = NULL;
            }
        }
    }
    if (m_pDisplayListThread != NULL)
    {   
        DWORD dwResult = WaitForSingleObject(m_pDisplayListThread->m_hThread,0);
        if (dwResult == WAIT_TIMEOUT)
        {   
            DWORD dwExitCode = 0;
            if (GetExitCodeThread(m_pDisplayListThread->m_hThread,&dwExitCode) && dwExitCode == STILL_ACTIVE)
            {   
                bResult = TerminateThread(m_pDisplayListThread->m_hThread,0);
            }
        }		
        if (bResult)
        {
            if (!m_pDisplayListThread->m_bAutoDelete)
            {
                delete m_pDisplayListThread;
                m_pDisplayListThread = NULL;
            }
        }
    }
    return bResult;
}

void DlgAcsFingerPrintCfg::CreateTree()
{
    CString strTemp =_T("");
    CString strChanTmp = _T("");
    int i = 0;
    m_treeEnableCardReader.DeleteAllItems();
    
    HTREEITEM hChanItem = NULL;
    HTREEITEM hFirstItem = NULL;
       
    for (i = 0; i < sizeof(m_struFingerPrintOne.byEnableCardReader); i++)
    {
        strTemp.Format("CardReader %d", i + 1);
        hChanItem = m_treeEnableCardReader.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeEnableCardReader.SetItemData(hChanItem, i);

        if (m_struFingerPrintOne.byEnableCardReader[i])
        {
            m_treeEnableCardReader.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeEnableCardReader.SelectItem(hFirstItem);
    m_treeEnableCardReader.Expand(m_treeEnableCardReader.GetRootItem(), TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeDelFingerPrint.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID); i++)
    {
        strTemp.Format("id %d", i + 1);
        hChanItem = m_treeDelFingerPrint.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeDelFingerPrint.SetItemData(hChanItem, i);
        
        if (m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID[i])
        {
            m_treeDelFingerPrint.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeDelFingerPrint.SelectItem(hFirstItem);
	m_treeDelFingerPrint.Expand(m_treeDelFingerPrint.GetRootItem(),TVE_EXPAND);
}

void DlgAcsFingerPrintCfg::GetTreeSel()
{
    UpdateData(TRUE); 
    memset(&m_struFingerPrintOne.byEnableCardReader, 0 , sizeof(m_struFingerPrintOne.byEnableCardReader));
    
    int i = 0; 
    HTREEITEM hTreeItem;
    
    BOOL bCheck;
    DWORD dwIndex;
    DWORD dwCount = 0; 
    CTreeCtrl *treeCtr = &m_treeEnableCardReader; 
    dwCount = m_treeEnableCardReader.GetCount(); 
    hTreeItem = m_treeEnableCardReader.GetRootItem();
    
    for ( i=0; i<dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struFingerPrintOne.byEnableCardReader[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

    memset(&m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID, 0 , sizeof(m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID));
    treeCtr = &m_treeDelFingerPrint;
    hTreeItem = m_treeDelFingerPrint.GetRootItem();
    dwCount = m_treeDelFingerPrint.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }
} 

void DlgAcsFingerPrintCfg::OnClickTreeEnableCardReader(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeEnableCardReader.ScreenToClient(&pt);
    m_treeEnableCardReader.GetWindowRect(&rc);
    m_treeEnableCardReader.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeEnableCardReader.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeEnableCardReader.SelectItem(hSelect);
    DWORD dwIndex = m_treeEnableCardReader.GetItemData(hSelect);
    BOOL bCheck = m_treeEnableCardReader.GetCheck(hSelect);
    m_treeEnableCardReader.SetCheck(hSelect, !bCheck);
    m_struFingerPrintOne.byEnableCardReader[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)//LVHT_TOLEFT)
    {
        m_treeEnableCardReader.SetCheck(hSelect, !bCheck);
        m_struFingerPrintOne.byEnableCardReader[dwIndex] = !bCheck;
    }
    else
    {
        m_treeEnableCardReader.SetCheck(hSelect, bCheck);
        m_struFingerPrintOne.byEnableCardReader[dwIndex] = bCheck;
    }
    UpdateData(FALSE); 
    *pResult = 0;
}

void DlgAcsFingerPrintCfg::OnClickTreeDelFingerPrint(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeDelFingerPrint.ScreenToClient(&pt);   
    m_treeDelFingerPrint.GetWindowRect(&rc);
    m_treeDelFingerPrint.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeDelFingerPrint.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeDelFingerPrint.SelectItem(hSelect);
    DWORD dwIndex = m_treeDelFingerPrint.GetItemData(hSelect);
    BOOL bCheck = m_treeDelFingerPrint.GetCheck(hSelect);
    m_treeDelFingerPrint.SetCheck(hSelect, !bCheck);
    m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeDelFingerPrint.SetCheck(hSelect, !bCheck);
        m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID[dwIndex] = !bCheck;
    }
    else
    {
        m_treeDelFingerPrint.SetCheck(hSelect, bCheck);
        m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}


void DlgAcsFingerPrintCfg::OnBtnAddToList() 
{
    NET_DVR_FINGER_PRINT_CFG struFingerPrintCfg = {0}; 
    UpdateFingerPrintCfg(struFingerPrintCfg);
    AddToFingerPrintList(struFingerPrintCfg);
    //UpdateSubList(&struCardCfg);
    
}

void DlgAcsFingerPrintCfg::OnDeleteitemListCard(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    // TODO: Add your control notification handler code here
    // 	GATEWAY_CARD_INFO* pCardInfo = (GATEWAY_CARD_INFO*)pNMListView->lParam;
    // 	if (pCardInfo != NULL)
    // 	{
    // 		delete pCardInfo;
    // 	}	
    // 	*pResult = 0;
}


int DlgAcsFingerPrintCfg::GetExistItem(const NET_DVR_FINGER_PRINT_CFG *lpCardCfg)
{
    int nItemCount = m_listFingerPrintCfg.GetItemCount();
    int i = 0; 
    LPNET_DVR_FINGER_PRINT_CFG lpTemp = NULL; 
    for (i=0; i<nItemCount; i++)
    {
        lpTemp = (LPNET_DVR_FINGER_PRINT_CFG)  m_listFingerPrintCfg.GetItemData(i);
        if ( ! lpCardCfg )
        {
            continue; 
        }
        if ( strcmp((char *)lpCardCfg->byCardNo, (char *)lpTemp->byCardNo) == 0 && lpCardCfg->byFingerPrintID==lpTemp->byFingerPrintID)
        {
            return i; 
        }
    }
    return -1; 
} 


void DlgAcsFingerPrintCfg::AddToFingerPrintList(const NET_DVR_FINGER_PRINT_CFG& struCardInfo)
{
    LPNET_DVR_FINGER_PRINT_CFG pCardInfo = NULL; 
    int iItemIndex   = GetExistItem(&struCardInfo); 
    if ( iItemIndex == -1)
    {
        pCardInfo = new NET_DVR_FINGER_PRINT_CFG;        
        int iSize = sizeof(NET_DVR_FINGER_PRINT_CFG);
        int nItemCount = m_listFingerPrintCfg.GetItemCount();
        
        CString strItem = "";
        strItem.Format("%d",nItemCount + 1);
        iItemIndex = m_listFingerPrintCfg.InsertItem(nItemCount,strItem);
        m_listFingerPrintCfg.SetItemData(nItemCount,(DWORD)pCardInfo);
    }
    else
    {
        pCardInfo = (LPNET_DVR_FINGER_PRINT_CFG)m_listFingerPrintCfg.GetItemData(iItemIndex); 
    }
    memcpy(pCardInfo,&struCardInfo,sizeof(struCardInfo));
    UpdateList(iItemIndex, *pCardInfo); 
    LPDWORD lpArr = GetFingerPrintCfgPoint();    
    lpArr[iItemIndex] = (DWORD)pCardInfo;
    
}

LPDWORD DlgAcsFingerPrintCfg::GetFingerPrintCfgPoint()
{
    if ( !m_lpRecordCardCfg)
    {
        const int iMaxCardNum = 1000; 
        m_lpRecordCardCfg = new DWORD[iMaxCardNum]; 
        memset(m_lpRecordCardCfg,0,sizeof(DWORD)*iMaxCardNum);
    }
    return m_lpRecordCardCfg; 
} 

void DlgAcsFingerPrintCfg::UpdateList(int iInsertIndex, const NET_DVR_FINGER_PRINT_CFG& m_struFingerPrintCfg)
{ 
    char szLan[1024] = {0};
    sprintf(szLan, "%d", iInsertIndex);
    //m_listFingerPrintCfg.InsertItem(iInsertIndex, szLan);
    sprintf(szLan, "%s", m_struFingerPrintCfg.byCardNo); 
    m_listFingerPrintCfg.SetItemText(iInsertIndex, 1, szLan);
    sprintf(szLan, "%d", m_struFingerPrintCfg.byFingerPrintID);
    m_listFingerPrintCfg.SetItemText(iInsertIndex, 2, szLan);
    sprintf(szLan, "%d", m_struFingerPrintCfg.byFingerType);
    m_listFingerPrintCfg.SetItemText(iInsertIndex, 3, szLan);
    sprintf(szLan, "%d", m_struFingerPrintCfg.dwFingerPrintLen);
    m_listFingerPrintCfg.SetItemText(iInsertIndex, 4, szLan);
    sprintf(szLan, "%s", m_struFingerPrintCfg.byFingerData); 
    m_listFingerPrintCfg.SetItemText(iInsertIndex, 5, szLan);

    FILE* fp = NULL;
    char szPath[1024] = {0};
    sprintf(szPath, "%d fingerprint.dat", iInsertIndex);
    fp=fopen(szPath,"wb");
    if (fp == NULL)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "fopen write failed");
    }

    //fread(struFingerPrintCfg.byFingerData, 1, m_dwFingerPrintLen , fp);
    fwrite(m_struFingerPrintCfg.byFingerData, m_struFingerPrintCfg.dwFingerPrintLen, 1, fp);
    fclose(fp);


//     CString strItem = "";
//     strItem.Format("%d",iInsertIndex + 1);
//     //    m_listFingerPrintCfg.InsertItem(iInsertIndex,strItem);
//     
//     m_listFingerPrintCfg.SetItemText(iInsertIndex,1, (char *)struCardInfo.byCardNo);
//     //     if ( struCardInfo.dwModifyParamType &0x1)
//     //     {
//     
//     strItem = (struCardInfo.byCardValid )?"Yes":"No";
//     m_listFingerPrintCfg.SetItemText(iInsertIndex,2, strItem);
//     //    }
//     //     if (struCardInfo.dwModifyParamType &0x2)
//     //     {
//     strItem = (struCardInfo.struValid.byEnable )?"Yes":"No";
//     m_listFingerPrintCfg.SetItemText(iInsertIndex,8, strItem);
//     if ( struCardInfo.struValid.byEnable )
//     {
//         const NET_DVR_TIME_EX *lpTimeEx = & struCardInfo.struValid.struBeginTime; 
//         strItem.Format("%d-%d-%d, %2d:%2d:%2d", lpTimeEx->wYear, lpTimeEx->byMonth, lpTimeEx->byDay, lpTimeEx->byHour, lpTimeEx->byMinute, lpTimeEx->bySecond);
//         m_listFingerPrintCfg.SetItemText(iInsertIndex, 9, strItem); 
//         lpTimeEx = & struCardInfo.struValid.struEndTime;
//         strItem.Format("%d-%d-%d, %2d:%2d:%2d", lpTimeEx->wYear, lpTimeEx->byMonth, lpTimeEx->byDay, lpTimeEx->byHour, lpTimeEx->byMinute, lpTimeEx->bySecond);
//         m_listFingerPrintCfg.SetItemText(iInsertIndex, 10, strItem); 
//     }
//     //    }
//     //     if(struCardInfo.dwModifyParamType &0x4)
//     //     {
//     char *p ; 
//     if (struCardInfo.byCardType == 0 || struCardInfo.byCardType > 7)
//     {
//         p = pCardType[0];
//     }
//     else 
//         p = pCardType[struCardInfo.byCardType];
//     m_listFingerPrintCfg.SetItemText(iInsertIndex, 4, p); 
//     //    }
//     //     if(struCardInfo.dwModifyParamType &0x10)
//     //     {
//     strItem = (struCardInfo.byLeaderCard )?"Yes":"No";
//     m_listFingerPrintCfg.SetItemText(iInsertIndex, 5, strItem);
//     
//     //    }
//     //     if (struCardInfo.dwModifyParamType &0x20)
//     //     {
//     strItem.Format("%d", struCardInfo.dwMaxSwipeTime); 
//     m_listFingerPrintCfg.SetItemText(iInsertIndex, 6, strItem);
//     //    }
//     strItem.Format("%d", struCardInfo.dwSwipeTime); 
//     m_listFingerPrintCfg.SetItemText(iInsertIndex, 7, strItem);  
//     //     if (struCardInfo.dwModifyParamType &0x80)
//     //     {
//     char szCardPassTemp[CARD_PASSWORD_LEN+1] = {0}; 
//     memcpy(szCardPassTemp, struCardInfo.byCardPassword, sizeof(struCardInfo.byCardPassword)); 
//     strItem.Format("%s", szCardPassTemp); 
//     m_listFingerPrintCfg.SetItemText(iInsertIndex, 3, strItem);
    //    }
    
}

void DlgAcsFingerPrintCfg::OnBtnSetFingerPrintcfg() 
{
    if (m_lSetFingerPrintCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSetFingerPrintCfgHandle);
    }
    UpdateData(TRUE); 
    NET_DVR_FINGER_PRINT_INFO_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwFingerPrintNum = m_dwCardNum;
    //struCond.byCheckCardNo = (BYTE)m_BcheckCardNo; 
    struCond.byCallbackMode = m_byCallbackMode;
    LPDWORD lpArr = GetFingerPrintCfgPoint();
    m_lSetFingerPrintCfgHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_SET_FINGERPRINT_CFG,&struCond,sizeof(struCond),g_fSetFingerPrintCallback,this);
    if (m_lSetFingerPrintCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FINGERPRINT_CFG failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FINGERPRINT_CFG succ");
    }
    //	StartProcThread();
    //发送第一张卡, 失败关闭连接
    m_dwSendIndex = 0;
    if ( !SendFirstCard())
    {
        NET_DVR_StopRemoteConfig(m_lSetFingerPrintCfgHandle);
        m_lSetFingerPrintCfgHandle = -1;
    }
    
}

void DlgAcsFingerPrintCfg::OnBtnGetAllFingerPrint() 
{
    if (m_lGetFingerPrintCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lGetFingerPrintCfgHandle);
    }
    //清除所有卡项
    //    ClearList(); 
    m_listFingerPrintCfg.DeleteAllItems(); 
    UpdateData(TRUE); 
    NET_DVR_FINGER_PRINT_INFO_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwFingerPrintNum = m_dwCardNum;
    struCond.byFingerPrintID = m_byFingerPrintID;
    memcpy(struCond.byCardNo, m_sCardNo.GetBuffer(m_sCardNo.GetLength()), m_sCardNo.GetLength());  
    //memcpy(struCond.byCardNo, )
    GetTreeSel();
    memcpy(struCond.byEnableCardReader, m_struFingerPrintOne.byEnableCardReader, sizeof(m_struFingerPrintOne.byEnableCardReader)); 
    
    m_lGetFingerPrintCfgHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_FINGERPRINT_CFG,&struCond,sizeof(struCond),g_fGetFingerPrintCallback,this);
    if (m_lGetFingerPrintCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FINGERPRINT_CFG failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FINGERPRINT_CFG succ");
    }
}

void CALLBACK g_fDelFingerPrintStatusCallBack(DWORD dwType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
    DlgAcsFingerPrintCfg *pThis = (DlgAcsFingerPrintCfg*)pUserData;
    DWORD dwTemp = 0;
	char szLan[128] = {0};

	HWND hWnd = pThis->GetSafeHwnd();
	if (NULL == hWnd)
	{
		return;
	}
	
    switch (dwType)
    {
    case NET_SDK_CALLBACK_TYPE_STATUS:
		{
			dwTemp = *((DWORD*)pRecvDataBuffer);
            g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Delete Finger Print CallBack");
            ::PostMessage(hWnd, WM_DEL_FINGER_PRINT_FINISH, (DWORD)dwTemp, dwType);
		}
		break;
    case NET_SDK_CALLBACK_TYPE_PROGRESS:
        g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Delete Finger Print CallBack Processing");
        break;
    case NET_SDK_CALLBACK_TYPE_DATA:
        {
            char *pDataBuf = new char[sizeof(NET_DVR_FINGER_PRINT_INFO_STATUS_V50)];
            if (pDataBuf == NULL)
            {
                dwType = NET_SDK_CALLBACK_STATUS_FAILED;
                break;
            }
            memset(pDataBuf, 0, sizeof(NET_DVR_FINGER_PRINT_INFO_STATUS_V50));
            memcpy(pDataBuf, pRecvDataBuffer, sizeof(NET_DVR_FINGER_PRINT_INFO_STATUS_V50));
						
            LPNET_DVR_FINGER_PRINT_INFO_STATUS_V50 pDelFingerPrintTemp = (NET_DVR_FINGER_PRINT_INFO_STATUS_V50*)pDataBuf;
            sprintf(szLan, "Device delete finger print status is:[%d], card reader no is:[%d]", pDelFingerPrintTemp->byStatus, pDelFingerPrintTemp->dwCardReaderNo);

            g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szLan);
            ::PostMessage(hWnd, WM_DEL_FINGER_PRINT_FINISH, NET_SDK_CALLBACK_TYPE_DATA, (LONG)pDataBuf);
        }
        break;
    default:
        break;
        
	}
    
}

void DlgAcsFingerPrintCfg::OnBtnDel() 
{
    UpdateData(TRUE);

    if (m_lRemoteHandle >= 0)
    {
        NET_DVR_StopRemoteConfig(m_lRemoteHandle);
    }

    NET_DVR_FINGER_PRINT_INFO_CTRL_V50 struDelCfg;
    memset(&struDelCfg, 0, sizeof(NET_DVR_FINGER_PRINT_INFO_CTRL_V50));
    struDelCfg.dwSize = sizeof(NET_DVR_FINGER_PRINT_INFO_CTRL_V50);
    struDelCfg.byMode = m_comboDelMode.GetCurSel();
    if (struDelCfg.byMode == 0)
    {
        //struDelCfg.struProcessMode.uLen
        memcpy(struDelCfg.struProcessMode.struByCard.byCardNo, m_sCardNo.GetBuffer(m_sCardNo.GetLength()), m_sCardNo.GetLength());
        GetTreeSel();
        memcpy(struDelCfg.struProcessMode.struByCard.byEnableCardReader, m_struFingerPrintOne.byEnableCardReader, sizeof(m_struFingerPrintOne.byEnableCardReader));
        memcpy(struDelCfg.struProcessMode.struByCard.byFingerPrintID, m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID, sizeof(m_struDelFingerPrint.struProcessMode.struByCard.byFingerPrintID));
    }
    else
    {
        struDelCfg.struProcessMode.struByReader.dwCardReaderNo = m_dwCardReaderNo;
        struDelCfg.struProcessMode.struByReader.byClearAllCard = m_byClearAllCard;
        memcpy(struDelCfg.struProcessMode.struByReader.byCardNo, m_sCardNo.GetBuffer(m_sCardNo.GetLength()), m_sCardNo.GetLength());
    }
    /*if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_DEL_FINGERPRINT_CFG, &struDelCfg, sizeof(struDelCfg)))
    {
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DEL_FINGERPRINT_CFG FAILED");
    return;
    }
    else
    {
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_DEL_FINGERPRINT_CFG SUCC");
    }*/
    m_lRemoteHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_DEL_FINGERPRINT_CFG_V50, &struDelCfg, sizeof(struDelCfg), g_fDelFingerPrintStatusCallBack, this);
    if (m_lRemoteHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DEL_FINGERPRINT_CFG_V50");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_DEL_FINGERPRINT_CFG_V50");
    }
}

void DlgAcsFingerPrintCfg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_comboX.GetCurSel() == CB_ERR || m_comboY.GetCurSel() == CB_ERR)
	{
		g_StringLanType(szLan, "请选择坐标", "Please select Coordinate");
		AfxMessageBox(szLan);
		return;
	}
    NET_DVR_FINGER_PRINT_CFG struFingerPrintCfg ={0}; 
    UpdateFingerPrintCfg(struFingerPrintCfg); 
    UpdateOutputNum(struFingerPrintCfg);

    DrawList(); 
	UpdateData(FALSE);
    
}

// void DlgAcsFingerPrintCfg::OnBtnSet() 
// {
// 	// TODO: Add your control notification handler code here
// 	memset(m_dwStatus, 0, sizeof(m_dwStatus)); 
//     LPNET_DVR_VIDEOWALLDISPLAYPOSITION lpDisplayPos = GetModifyDisplayPos();
//     LONG *  lDisplayChan = GetModifyChan(); 
//     char csError[1024]={0};
//     char csNum[128] = {0};
//     if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_VIDEOWALLDISPLAYPOSITION, m_dwCount, lDisplayChan, 4 * m_dwCount, m_dwStatus, lpDisplayPos, m_dwCount * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
//     {
//         sprintf(csError, "设置修改失败, Error code: %d", NET_DVR_GetLastError());
//         AfxMessageBox(csError);
//         g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEOWALLDISPLAYPOSITION");
//         return;
//     }
//     g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEOWALLDISPLAYPOSITION");
//     int i = 0; 
//     BOOL bOneFail = FALSE; 
//     for (i = 0; i <m_dwCount; i++)
//     {
//         if (m_dwStatus[i] > 0)
//         {
//             sprintf(csNum, "%d ", lpDisplayPos[i].dwDisplayNo);
//             strcat(csError, csNum); 
//             bOneFail = TRUE;
// 	    } 	
//     }
//     if (bOneFail)
//     {
// //        sprintf(csError, "the outputnum failed to set: %s ", csError); 
//         AfxMessageBox(csError); 
//         return ; 
//     }
//     OnBtnGetAll(); 
// 	
// }

//输出号位置获取
// void DlgAcsFingerPrintCfg::OnBtnGet() 
// {
// 	// TODO: Add your control notification handler code here
//     UpdateData(TRUE); 
//     POSITION  iPos = m_listFingerPrintCfg.GetFirstSelectedItemPosition();
//     if (iPos == NULL)
//     {
//         return;
// 	}
//     NET_DVR_VIDEOWALLDISPLAYPOSITION struDisplayPos={0}; 
//     struDisplayPos.dwSize = sizeof(struDisplayPos); 
//     DWORD dwDispChan = m_dwOutputNum; 
// 	CString csTemp;
//     char szLan[128]={0}; 
// 	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYPOSITION, 1, &dwDispChan, sizeof(dwDispChan), NULL, &struDisplayPos, sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
// 	{
// 		sprintf(szLan, "刷新该项失败, Error code %d",NET_DVR_GetLastError());
// 		AfxMessageBox(szLan);
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");		
// 		//return;
// 	}
//     else
//     {
//         NewOutputNum(struDisplayPos); 
//         DrawList(); 
//     }
// }

void DlgAcsFingerPrintCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void DlgAcsFingerPrintCfg::DrawList()
{
    m_listFingerPrintCfg.DeleteAllItems(); 
	int i = 0;
	int j = 0;
	char szLan[128] = {0};
	for(i = 0; i < m_dwDispNum; i++)
	{
		sprintf(szLan, "%d", i);
		m_listFingerPrintCfg.InsertItem(i, szLan);
        sprintf(szLan, "%s", m_struFingerPrintCfg[i].byCardNo); 
        m_listFingerPrintCfg.SetItemText(i, 1, szLan);
		sprintf(szLan, "%d", m_struFingerPrintCfg[i].byFingerPrintID);
		m_listFingerPrintCfg.SetItemText(i, 2, szLan);
		sprintf(szLan, "%d", m_struFingerPrintCfg[i].byFingerType);
		m_listFingerPrintCfg.SetItemText(i, 3, szLan);
        sprintf(szLan, "%d", m_struFingerPrintCfg[i].dwFingerPrintLen);
		m_listFingerPrintCfg.SetItemText(i, 4, szLan);
        sprintf(szLan, "%s", m_struFingerPrintCfg[i].byFingerData); 
        m_listFingerPrintCfg.SetItemText(i, 5, szLan);
	}
}

void DlgAcsFingerPrintCfg::OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    LPNET_DVR_FINGER_PRINT_CFG lpCardCfg  = GetSelItem();

    if (lpCardCfg == NULL)
    {
        return;
    }

    m_sCardNo.Format("%s",lpCardCfg->byCardNo);
    m_dwFingerPrintLen = lpCardCfg->dwFingerPrintLen;
    memcpy(m_struFingerPrintOne.byEnableCardReader, lpCardCfg->byEnableCardReader, sizeof(lpCardCfg->byEnableCardReader));
    CreateTree();
    m_byFingerPrintID = lpCardCfg->byFingerPrintID;
    m_comboFingerType.SetCurSel(lpCardCfg->byFingerType);
    m_sFingerPrintPath.Format("%s",lpCardCfg->byFingerData);

    *pResult = 0;
    UpdateData(FALSE);
}

LPNET_DVR_FINGER_PRINT_CFG DlgAcsFingerPrintCfg::GetSelItem(char *lpCardNo)
{
    UpdateData(TRUE);
    POSITION  iPos = m_listFingerPrintCfg.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return NULL;
    }
    int iCurSel = m_listFingerPrintCfg.GetNextSelectedItem(iPos);
    m_iSelListItem = iCurSel;
    m_listFingerPrintCfg.SetItemState( m_iSelListItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
    if ( lpCardNo )
    {
        m_listFingerPrintCfg.GetItemText(iCurSel, 1, lpCardNo,  ACS_CARD_NO_LEN);
    }
    LPNET_DVR_FINGER_PRINT_CFG lpCardCfg = (LPNET_DVR_FINGER_PRINT_CFG) m_listFingerPrintCfg.GetItemData(iCurSel);
    return lpCardCfg; 
} 

// void DlgAcsFingerPrintCfg::OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	// TODO: Add your control notification handler code here
// 	POSITION  iPos = m_listFingerPrintCfg.GetFirstSelectedItemPosition();
//     if (iPos == NULL)
//     {
//         return;
//     }
//  	m_iCurSel = m_listFingerPrintCfg.GetNextSelectedItem(iPos);
//     m_sCardNo.Format("%s",m_struFingerPrintCfg[m_iCurSel].byCardNo);
//     m_dwFingerPrintLen = m_struFingerPrintCfg[m_iCurSel].dwFingerPrintLen;
//     m_byFingerPrintID = m_struFingerPrintCfg[m_iCurSel].byFingerPrintID;
//     m_comboFingerType.SetCurSel(m_struFingerPrintCfg[m_iCurSel].byFingerType);    
// 	UpdateData(FALSE);
// 	*pResult = 0;
// }

// void DlgAcsFingerPrintCfg::OnBtnGetAll() 
// {
// 	// TODO: Add your control notification handler code here
//     UpdateData(TRUE); 
// 	int i = 0;
// 	BOOL bOneFail = FALSE;
// 	char cs[1024] = {0};
// 	CString csTemp;
// 	char *pTemp = new char[4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)];
// 	memset(pTemp, 0, 4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION));
// // 	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYPOSITION, 0xffffffff, NULL, 0, NULL, pTemp, 4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
// // 	{
// // 		sprintf(cs, "获取所有位置失败, Error code: %d", NET_DVR_GetLastError());
// // 		AfxMessageBox(cs);
// // 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");		
// // 		//return;
// // 	}
//     DWORD dwWallNo = m_byWallNo; 
//     dwWallNo <<= 24; 
//     if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYPOSITION, 0xffffffff, &dwWallNo, sizeof(DWORD), NULL, pTemp, 4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
//     {
//         sprintf(cs, "获取墙所有输出位置失败, Error code: %d", NET_DVR_GetLastError());
//         AfxMessageBox(cs);
//         g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");		
//         //return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");
// 		m_dwDispNum = *((DWORD*)pTemp);	
// 		memcpy(m_struWallParam, pTemp + 4, m_dwDispNum * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION));
// 		memset(m_dwStatus, 0, sizeof(m_dwStatus));
//         ClearModify(); 	
// 		m_comboOutput.ResetContent();
// 		for (i = 0; i<m_dwDispNum; i++)
// 		{	
//             m_lDispChan[i] = m_struWallParam[i].dwDisplayNo; 
// 			sprintf(cs, "%d", m_lDispChan[i]);
// 			m_comboOutput.AddString(cs);
// 			m_comboOutput.SetItemData(i, m_lDispChan[i]);
// 		}
//         m_lPapamCount = m_dwDispNum; 
// 	}
// 	delete []pTemp;
// 	//m_listFingerPrintCfg.DeleteAllItems();
// 	DrawList();
//     m_listFingerPrintCfg.UpdateData(FALSE); 
//     m_listFingerPrintCfg.SetItemState(m_iCurSel, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
// }


//更新项记录
BOOL DlgAcsFingerPrintCfg::UpdateOutputNum(const NET_DVR_FINGER_PRINT_CFG &struFingerPrintCfg)
{
    //判断是否新修改项
    int  i=0; 
	int j = 0;
    for (i=0; i<m_dwDispNum; i++)
    {
        
    }
 
    m_struFingerPrintCfg[i] = struFingerPrintCfg; 
    if (i >= m_dwDispNum)
    {
        //新项
        m_dwDispNum ++; 
        //添加修改记录
        m_lDispChanSet[m_dwCount] = i; 
        m_dwCount ++; 
    }
    else
    {
        //原有项
        // 判断是否添加修改记录
        for(j=0; j<m_dwCount; j++)
        {
            if (m_lDispChanSet[j] == i)
            {
                break; 
            }
        }
        if(j>=m_dwCount)
        {
            m_lDispChanSet[m_dwCount] = i; 
            m_dwCount ++; 
        }
    }
    return TRUE; 
}

//更新界面数值到变量
BOOL DlgAcsFingerPrintCfg::UpdateFingerPrintCfg(NET_DVR_FINGER_PRINT_CFG &struFingerPrintCfg)
{
    UpdateData(TRUE); 
    struFingerPrintCfg.dwSize = sizeof(struFingerPrintCfg);
    memcpy(struFingerPrintCfg.byCardNo, m_sCardNo.GetBuffer(m_sCardNo.GetLength()), m_sCardNo.GetLength());   
    struFingerPrintCfg.dwFingerPrintLen = m_dwFingerPrintLen; 
    GetTreeSel();
    memcpy(struFingerPrintCfg.byEnableCardReader, m_struFingerPrintOne.byEnableCardReader, sizeof(struFingerPrintCfg.byEnableCardReader)); 
    struFingerPrintCfg.byFingerPrintID = m_byFingerPrintID;                                
    struFingerPrintCfg.byFingerType = m_comboFingerType.GetCurSel();

    //HPR_HANDLE hFileHandle = HPR_OpenFile(m_sFingerPrintPath, HPR_READ|HPR_BINARY, HPR_ATTR_READONLY);
    //HPR_UINT32 NumberOfBytesRead; 
//     if (HPR_ReadFile(hFileHandle, struFingerPrintCfg.szFingerData, m_dwFingerPrintLen, &NumberOfBytesRead) != HPR_OK)
//     {
//         g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "HPR_ReadFile failed");
//         return TRUE; 
//     }

    FILE* fp = NULL;
    fp=fopen(m_sFingerPrintPath,"rb"); //只供读取
    if (fp == NULL)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "HPR_ReadFile failed");
        return TRUE; 
    }
    fseek(fp, 0L, SEEK_END);
    int len = ftell(fp);
    rewind(fp);
    fread(struFingerPrintCfg.byFingerData, 1, m_dwFingerPrintLen , fp);
    fclose(fp);
    




    //memcpy(struFingerPrintCfg.szFingerData, m_sFingerPrintPath.GetBuffer(m_sFingerPrintPath.GetLength()), m_sFingerPrintPath.GetLength());   
    //struFingerPrintCfg.pFingerData = strtmp;
    //sprintf(struFingerPrintCfg.byCardNo,"%s",m_sCardNo.GetBuffer(m_sCardNo.GetLength())); 
    
    return TRUE; 
}

BOOL DlgAcsFingerPrintCfg::NewOutputNum(const NET_DVR_FINGER_PRINT_CFG &struDisplayPos)
{
    int  i=0; 
    for (i=0; i<m_dwDispNum; i++)
    {
//         if ( struDisplayPos.dwDisplayNo == m_struFingerPrintCfgSet[i].dwDisplayNo)
//         {
//             break; 
//         }
    }
    m_struFingerPrintCfg[i] = struDisplayPos; 
    if (i >= m_dwDispNum)
    {
        //新项
        m_dwDispNum ++; 
    }
    else
    {
        //原有项
        //判断是否添加修改记录 删除修改记录
        int j; 
        int iCount = m_dwCount;
        for(j=0; j<iCount; j++)
        {
            if (m_lDispChanSet[j] == i)
            {
                break; 
            }
        }
        for ( ; j<iCount; j++)
        {
            m_lDispChanSet[j] = m_lDispChanSet[j+1]; 
        }
        if ( m_dwCount )
        {
            m_dwCount --; 
        }     
    }
    return TRUE; 
} 

//获取修改过项
LPNET_DVR_FINGER_PRINT_CFG DlgAcsFingerPrintCfg::GetModifyDisplayPos()                             
{
    memset(m_struFingerPrintCfgSet, 0, sizeof(m_struFingerPrintCfgSet));
    for (int i=0; i<m_dwCount; i++)
    {
        m_struFingerPrintCfgSet[i] = m_struFingerPrintCfg[m_lDispChanSet[i]]; 
        //m_ModifyChan[i] = m_struFingerPrintCfgSet[i].dwDisplayNo; 
    }
    return m_struFingerPrintCfgSet; 
}    

LONG * DlgAcsFingerPrintCfg::GetModifyChan()                                                                //获取修改过显示输出号数组
{   
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan));
    for (int i=0; i<m_dwCount; i++)
    {
       // m_ModifyChan[i] = m_struFingerPrintCfg[m_lDispChanSet[i] ].dwDisplayNo ;
    }
    return m_ModifyChan; 
}

BOOL DlgAcsFingerPrintCfg::ClearModify()
{
    memset(m_struFingerPrintCfgSet, 0, sizeof(m_struFingerPrintCfgSet));
    m_dwCount = 0; 
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan)); 
    return TRUE; 
}

LONG * DlgAcsFingerPrintCfg::GetModifyPapamChan()
{
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan));
    for (int i=0; i<m_lRecordCount; i++)
    {
        m_ModifyChan[i] = m_lDispChan[m_dwRecordPapam[i] ];
    }
    return m_ModifyChan; 
}

void CALLBACK g_fSetFingerPrintCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    DlgAcsFingerPrintCfg* pDlg = (DlgAcsFingerPrintCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessSetFingerPrintCfgCallbackData(dwType,lpBuffer,dwBufLen);
}

void CALLBACK g_fGetFingerPrintCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    DlgAcsFingerPrintCfg* pDlg = (DlgAcsFingerPrintCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetFingerPrintCfgCallbackData(dwType,lpBuffer,dwBufLen);
}

void DlgAcsFingerPrintCfg::ProcessSetFingerPrintCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{   
    CString strItem = "";
    //     if (dwType != NET_SDK_CALLBACK_TYPE_STATUS)
    //     {
    //g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "recv unknow type[%d]", dwType);
    //return;
    //}
    
    
    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {   
            char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
            strncpy(szCardNumber,(char*)(lpBuffer) + 4,ACS_CARD_NO_LEN);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s", szCardNumber);
            //SetFingerPrintCfgState(szCardNumber,TRUE);
            SendNextFingerPrint(); 
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "SetFingerPrint Err:NET_SDK_CALLBACK_STATUS_FAILED");

            SendNextFingerPrint();
        }
        //下面两个关闭长连接
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint SUCCESS");
            PostMessage(WM_MSG_SET_FINGERPRINT_FINISH,0,0);
            
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint Excepiyion");
            PostMessage(WM_MSG_SET_FINGERPRINT_FINISH,0,0);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint SUCCESS");
            PostMessage(WM_MSG_SET_FINGERPRINT_FINISH,0,0);
        }
        
    }
    else if ( dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_FINGER_PRINT_STATUS struCfg = {0};
        memcpy(&struCfg, lpBuffer, sizeof(struCfg));

        int i;
        BOOL bSendOk = FALSE;
        for (i=0; i<sizeof(struCfg.byCardReaderRecvStatus); i++)
        {
            if (struCfg.byCardReaderRecvStatus[i] == 1)
            {
                bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.dwCardReaderNo);
            }
			else if(struCfg.byCardReaderRecvStatus[i] == 2)
			{
				bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.dwCardReaderNo);
			}
			else if(struCfg.byCardReaderRecvStatus[i] == 3)
			{
				bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.dwCardReaderNo);
			}
			else if(struCfg.byCardReaderRecvStatus[i] == 4)
			{
				bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.dwCardReaderNo);
			}else if(struCfg.byCardReaderRecvStatus[i] == 5)
			{
				bSendOk = TRUE;
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, byErrorMsg: %s, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.byErrorMsg,struCfg.dwCardReaderNo );
			}
			else if(struCfg.byCardReaderRecvStatus[i] == 6)
			{
				bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.dwCardReaderNo);
			}
			else if(struCfg.byCardReaderRecvStatus[i] == 7)
			{
				bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.dwCardReaderNo);
			}
			else if(struCfg.byCardReaderRecvStatus[i] == 8)
			{
				bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "SetFingerPrint PROCESSING %s,CardReader %d, dwCardReaderNo: %d", struCfg.byCardNo, i, struCfg.dwCardReaderNo);
			}



        }
        if (!bSendOk)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "SetFingerPrint Failed,CardNo:%s", struCfg.byCardNo);
        }
        if (m_byCallbackMode == 0 || struCfg.byTotalStatus == 1)
        {
            SendNextFingerPrint();
        }
    }
}

void DlgAcsFingerPrintCfg::ProcessGetFingerPrintCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{   
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_FINGER_PRINT_CFG lpCardCfg =  new NET_DVR_FINGER_PRINT_CFG; 
        memcpy(lpCardCfg, lpBuffer, sizeof(*lpCardCfg)); 

        int i;
        BOOL bSendOk = FALSE;
        for (i=0; i<sizeof(lpCardCfg->byEnableCardReader); i++)
        {
            if (lpCardCfg->byEnableCardReader[i] == 1)
            {
                bSendOk = TRUE;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "GetFingerPrint PROCESSING %s,CardReader %d", lpCardCfg->byCardNo, i);
            }
        }
        if (!bSendOk)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GetFingerPrint Failed,CardNo:%s", lpCardCfg->byCardNo);
        }

        PostMessage(WM_MSG_ADD_FINGERPRINT_TOLIST, (WPARAM)lpCardCfg,0);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_GET_FINGERPRINT_FINISH,0,0);
        }
        else if ( dwStatus == NET_SDK_CALLBACK_STATUS_FAILED )
        {
            char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
            DWORD dwErrCode = *(DWORD*)((char *)lpBuffer + 4); 
            strncpy(szCardNumber,(char*)(lpBuffer) + 8,ACS_CARD_NO_LEN);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GetCard STATUS_FAILED, Error code %d, Card Number %s", dwErrCode,  szCardNumber);
        }
    }
}

void DlgAcsFingerPrintCfg::SendFingerPrintData(LPNET_DVR_FINGER_PRINT_CFG lpCardCfg, DWORD dwDiffTime)
{
}

void DlgAcsFingerPrintCfg::SendFingerPrintData()
{   
    if (m_lSetFingerPrintCfgHandle == -1)
    {
        return;
    }
    LPNET_DVR_FINGER_PRINT_CFG lpCardCfg = NULL; 
//     if ( m_BSendSel )
//     {
//         //         lpCardCfg = GetSelItem();
//         SendCardData( m_lpSelSendCardCfg ); 
//         m_BSendSel = FALSE; 
//         m_lpSelSendCardCfg = NULL; 
//         return; 
//     }
    int nItemCount = m_listFingerPrintCfg.GetItemCount();
    LPDWORD lpArr = GetFingerPrintCfgPoint();
    DWORD beforeWait = 0;  
    DWORD afterWait = 0;
    for (int i = 0; i < nItemCount; i++)
    {
        
        //        lpCardCfg = (LPNET_DVR_FINGER_PRINT_CFG) m_listFingerPrintCfg.GetItemData(i);
        lpCardCfg = (LPNET_DVR_FINGER_PRINT_CFG)lpArr[i]; 
        if ( ! lpCardCfg )
        {
            continue; 
        }
        //		beforeWait = GetTickCount(); 
        if ( i%10 == 9 && WaitForSingleObject(m_hStopProcEvent,0) == WAIT_OBJECT_0)
        {
            break;
        }
        //		afterWait = GetTickCount(); 
        m_dwNowSendItem = i; 
        SendFingerPrintData(lpCardCfg, afterWait-beforeWait); 
    }
}


UINT __cdecl  g_fSendFingerPrintCfgThread(LPVOID pParam)
{
    DlgAcsFingerPrintCfg* pDlg = (DlgAcsFingerPrintCfg*)pParam;
    if (pParam != NULL)
    {
        pDlg->SendFingerPrintData();
    }
    return 0;
}

UINT __cdecl  g_fShowFingerPrintListThread(LPVOID pParam)
{
    DlgAcsFingerPrintCfg* pDlg = (DlgAcsFingerPrintCfg*)pParam;
    if (pParam != NULL)
    {
        pDlg->BatchAddFingerPrintToList();
    }
    return 0;    	
}

BOOL DlgAcsFingerPrintCfg::SendFirstCard()
{
    if ( m_lSetFingerPrintCfgHandle == -1)
    {
        return FALSE; 
    }
//     if ( m_BSendSel )
//     {
//         //         lpCardCfg = GetSelItem();
//         SendCardData( m_lpSelSendCardCfg ); 
//         m_BSendSel = FALSE; 
//         m_lpSelSendCardCfg = NULL; 
//         return TRUE; 
//     }
    m_dwSendIndex = 0; 
    if( m_dwCardNum < 1)
    {
        return FALSE; 
    }
    LPDWORD lpArr = GetFingerPrintCfgPoint();
    m_lpNowSendCard = (LPNET_DVR_FINGER_PRINT_CFG)lpArr[m_dwSendIndex];
    if (!NET_DVR_SendRemoteConfig(m_lSetFingerPrintCfgHandle,3/*ENUM_ACS_SEND_DATA*/, (char *)m_lpNowSendCard ,sizeof(*m_lpNowSendCard)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendCard->byCardNo);        
        return FALSE; 
    }
    return TRUE; 
} 

//重发
BOOL DlgAcsFingerPrintCfg::ReSendLastFingerPrint()
{
    if ( m_lSetFingerPrintCfgHandle == -1)
    {
        return FALSE; 
    }
    m_byLastCardSendTime ++; 
//     if ( m_byLastCardSendTime >= MAX_RESEND_CARD_TIME)
//     {
//         return FALSE; 
//     }
    if (!NET_DVR_SendRemoteConfig(m_lSetFingerPrintCfgHandle,3/*ENUM_ACS_SEND_DATA*/, (char *)m_lpNowSendCard ,sizeof(*m_lpNowSendCard)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendCard->byCardNo);        
        return FALSE; 
    }
    return TRUE; 
}     

//发送下一张
BOOL DlgAcsFingerPrintCfg::SendNextFingerPrint()
{
    if ( m_lSetFingerPrintCfgHandle == -1)
    {
        return FALSE; 
    }
     
    LPDWORD lpArr = GetFingerPrintCfgPoint();

    m_dwSendIndex++; 
    if ( m_dwSendIndex >= m_dwCardNum)
    {
        //PostMessage(WM_MSG_SET_FINGERPRINT_FINISH,0,0);
        return TRUE; 
    }
    if(lpArr == NULL)
    {
        return FALSE;
    }
    m_lpNowSendCard = (LPNET_DVR_FINGER_PRINT_CFG)lpArr[m_dwSendIndex];
    if (!NET_DVR_SendRemoteConfig(m_lSetFingerPrintCfgHandle,3/*ENUM_ACS_SEND_DATA*/, (char *)m_lpNowSendCard ,sizeof(*m_lpNowSendCard)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendCard->byCardNo);    
        //发送失败  关闭连接
        PostMessage(WM_MSG_SET_FINGERPRINT_FINISH,0,0);
        return FALSE; 
    }
    return TRUE; 
}  

void DlgAcsFingerPrintCfg::BatchAddFingerPrintToList()
{
    LPNET_DVR_FINGER_PRINT_CFG pCardInfo = NULL; 
    LPDWORD lpArr = GetFingerPrintCfgPoint(); 
    int i = 0; 
    int nItemCount = m_listFingerPrintCfg.GetItemCount();   
    CString strItem ;
    //m_csBatchFlag.Format("adding"); 
    PostMessage(WM_MSG_UPDATEDATA_INTERFACE, FALSE,0);
    for (i=0; i<m_dwCardNum; i++)
    {
        pCardInfo = (LPNET_DVR_FINGER_PRINT_CFG)lpArr[i];                   
        strItem.Format("%d",nItemCount + 1);
        int iItemIndex = m_listFingerPrintCfg.InsertItem(nItemCount,strItem);
        m_listFingerPrintCfg.SetItemData(iItemIndex,(DWORD)pCardInfo);
        UpdateList(iItemIndex, *pCardInfo); 
        nItemCount ++; 
    }
    //m_csBatchFlag.Format("finish add"); 
    PostMessage(WM_MSG_UPDATEDATA_INTERFACE, FALSE,0);
}

void DlgAcsFingerPrintCfg::OnBtnStopSend() 
{
    // TODO: Add your control notification handler code here
    StopProcThread(); 
}
