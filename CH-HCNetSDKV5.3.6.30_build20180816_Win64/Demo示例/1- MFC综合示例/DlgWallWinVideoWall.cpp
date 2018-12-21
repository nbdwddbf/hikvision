// DlgWallWin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallWinVideoWall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWallWinVideoWall dialog

CDlgWallWinVideoWall::CDlgWallWinVideoWall (CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallWinVideoWall::IDD, pParent)
    ,m_byMaxWallNo(16)
    ,m_byMinWallNo(1)
{
	//{{AFX_DATA_INIT(CDlgWallWinVideoWall )
	m_bEnable = FALSE;
	m_dwLayer = 0;
	m_wH = 0;
	m_wW = 0;
	m_wX = 0;
	m_wY = 0;
	m_byTransparency = 0;
	m_byWinMode = 0;
	m_bTransparency = FALSE;
	m_dwWinNo = 0;
	m_dwSubwinNo = 0;
	m_BEnableSpartan = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgWallWinVideoWall ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWallWinVideoWall )
	DDX_Control(pDX, IDC_COMB_VW_WINTYPE, m_cmbWinType);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_WIN_WALLNO, m_CombWallNo);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_WIN_SUBWIN_SCALESTATUS, m_CombScaleStatus);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_WIN_SUBWIN_DECODELAY, m_CombDelayDelay);
	DDX_Control(pDX, IDC_LIST_WINCFG, m_listWinCfg);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_LAYER, m_dwLayer);
	DDX_Text(pDX, IDC_EDIT_WIN_H, m_wH);
	DDX_Text(pDX, IDC_EDIT_WIN_W, m_wW);
	DDX_Text(pDX, IDC_EDIT_X, m_wX);
	DDX_Text(pDX, IDC_EDIT_Y, m_wY);
	DDX_Text(pDX, IDC_EDIT_TRANSPARENCY, m_byTransparency);
	DDV_MinMaxByte(pDX, m_byTransparency, 0, 100);
	DDX_Text(pDX, IDC_EDIT_WINMODE, m_byWinMode);
	DDX_Check(pDX, IDC_CHECK_TRANSPARENCY, m_bTransparency);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_WIN_WINNO, m_dwWinNo);
	DDX_Text(pDX, IDC_EDT_WIN_SUBWINNO, m_dwSubwinNo);
	DDX_Check(pDX, IDC_CHK_WIN_SUBWIN_SPARTAN, m_BEnableSpartan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallWinVideoWall , CDialog)
	//{{AFX_MSG_MAP(CDlgWallWinVideoWall )
	ON_NOTIFY(NM_CLICK, IDC_LIST_WINCFG, OnClickListWincfg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_SET_PRO, OnBtnSetPro)
	ON_BN_CLICKED(IDC_BTN_GET_PRO, OnBtnGetPro)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_SET_WALL_CFG, OnBtnSetWallCfg)
	ON_BN_CLICKED(IDC_BTN_GET_WALL_CFG, OnBtnGetWallCfg)
	ON_BN_CLICKED(IDC_BTN_WIN_TOP, OnBtnWinTop)
	ON_BN_CLICKED(IDC_BTN_WIN_BOTTOM, OnBtnWinBottom)
	ON_BN_CLICKED(IDC_BTN_CLOSE_ALL_WIN, OnBtnCloseAllWin)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_WIN_SUBWINSET, OnBtnSubwinSet)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_WIN_SUBWINREFRESH, OnBtnSubwinRefresh)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_WIN_REFREAH, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMB_VIDEOWALL_WIN_WALLNO, OnSelchangeWinWallNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallWinVideoWall  message handlers

BOOL CDlgWallWinVideoWall ::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString cs;
	m_iCurSel = -1;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_dwWinCount = 0;
    m_dwModifyNum = 0; 
	char szLan[128] = {0};
	memset(m_dwStatus, 0, sizeof(m_dwStatus));
	memset(m_struList, 0, sizeof(m_struList));
	memset(m_dwWinNum, 0xff, sizeof(m_dwWinNum));
    memset(m_dwModifyRecord, 0xff, sizeof(m_dwModifyRecord)); 
	memset(&m_struWallWinParam, 0, sizeof(m_struWallWinParam));
	memset(&m_struWallCfg, 0, sizeof(m_struWallCfg));
    
	m_listWinCfg.SetExtendedStyle(m_listWinCfg.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "窗口号", "Window");
	m_listWinCfg.InsertColumn(0, szLan,LVCFMT_LEFT,80,-1);
	m_listWinCfg.InsertColumn(1, "X",LVCFMT_LEFT,80,-1);
    m_listWinCfg.InsertColumn(2, "Y",LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "宽", "width");
	m_listWinCfg.InsertColumn(3, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "高", "Height");
	m_listWinCfg.InsertColumn(4, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "图层号", "Layer Number");
	m_listWinCfg.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "使能", "Enable");
	m_listWinCfg.InsertColumn(6, szLan, LVCFMT_LEFT, 80,-1);
//     g_StringLanType(szLan, "窗口类型", "Enable");
// 	m_listWinCfg.InsertColumn(7, szLan, LVCFMT_LEFT, 80,-1);
    InitVaildWallNo(); 
	OnBtnGetAll();
	// TODO: Add extra initialization here
	m_cmbWinType.SetCurSel(0); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWallWinVideoWall ::OnClickListWincfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listWinCfg.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
 	}
    DWORD dwData; 
    m_iCurSel = m_listWinCfg.GetNextSelectedItem(iPos);
    dwData = m_listWinCfg.GetItemData(m_iCurSel); 
	m_bEnable = m_struList[m_iCurSel].byEnable;
	m_wX = m_struList[dwData].struRect.dwXCoordinate;
	m_wY = m_struList[dwData].struRect.dwYCoordinate;
	m_wW = m_struList[dwData].struRect.dwWidth;
	m_wH = m_struList[dwData].struRect.dwHeight;
	m_dwLayer = m_struList[dwData].dwLayerIndex;
    m_dwWinNo = m_struList[dwData].dwWindowNo & 0xffff; 
//    m_cmbWinType.SetCurSel(m_struList[dwData].byWinType); 
    UpdateData(FALSE);
	*pResult = 0;
}

void CDlgWallWinVideoWall ::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	NET_DVR_VIDEOWALLWINDOWPOSITION struWinPos = {0}; 
    DWORD dwWallNo = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
	struWinPos.dwSize = sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION);
	struWinPos.byEnable = m_bEnable;
	struWinPos.dwWindowNo = m_dwWinNo + (dwWallNo<<24);
	struWinPos.dwLayerIndex = 0;
	struWinPos.struRect.dwXCoordinate = m_wX;
	struWinPos.struRect.dwYCoordinate = m_wY;
	struWinPos.struRect.dwWidth = m_wW;
	struWinPos.struRect.dwHeight = m_wH;
//   struWinPos.byWinType = m_cmbWinType.GetCurSel();    
    int i=0; 
    if ((struWinPos.dwWindowNo & 0xffff) != 0)
    {
        for (i=0; i<m_dwWinCount; i++)
        {
            if (struWinPos.dwWindowNo == m_struList[i].dwWindowNo)
            {
                break; 
            }
        }
        if ( i >= m_dwWinCount)
        {
            if (m_dwWinCount >= MAX_WALL_WIN_COUNT )
            {
                char szLan[128]; 
                g_StringLanType(szLan, "窗口数不能超过256", "It is not allowed more than 256 window");
                AfxMessageBox(szLan);
                return ; 
            }
            m_dwWinCount ++; 
        }
    }
    else
       i = m_dwWinCount ++; 
    m_struList[i] = struWinPos;
    UpdateRecord(i);                                                //更新修改记录
    //UpdateWinList(struWinPos); 
    DrawList(); 
    UpdateData(FALSE);
}

void CDlgWallWinVideoWall ::DrawList()
{
	int i = 0, j=0;
	CString cs;
    m_listWinCfg.DeleteAllItems();
    for(i = 0, j=0; i < m_dwWinCount; i++)
	{	
        if ( m_struList[i].dwWindowNo == 0 && m_struList[i].byEnable == FALSE )
        {
            continue; 
        }
		cs.Format("%d",  m_struList[i].dwWindowNo & 0xffff);
		m_listWinCfg.InsertItem(j, cs, 0);
       
		cs.Format("%d", m_struList[i].struRect.dwXCoordinate);
		m_listWinCfg.SetItemText(j, 1, cs);
		cs.Format("%d", m_struList[i].struRect.dwYCoordinate);
		m_listWinCfg.SetItemText(j, 2, cs);
		cs.Format("%d", m_struList[i].struRect.dwWidth);
		m_listWinCfg.SetItemText(j, 3, cs);
		cs.Format("%d", m_struList[i].struRect.dwHeight);
		m_listWinCfg.SetItemText(j, 4, cs);
		cs.Format("%d", m_struList[i].dwLayerIndex);
		m_listWinCfg.SetItemText(j, 5, cs);
		if (m_struList[i].byEnable == 0)
		{
			cs.Format("Disable");
		}
		else
		{
			cs.Format("Enable");
		}
		m_listWinCfg.SetItemText(j, 6, cs);
//         if (m_struList[i].byWinType == 0 )
//         {
//             cs.Format("普通"); 
//         }
//         else 
//         {
//             cs.Format("虚拟屏"); 
//         }
//        m_listWinCfg.SetItemText(j, 7, cs);
//		m_listWinCfg.SetItemData(i, m_dwWinNum[i]);
        m_listWinCfg.SetItemData(j, i); 
        j++; 
	}
}

//设置修改过的项
void CDlgWallWinVideoWall ::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    if ( !HasModify())
    {
        return ; 
    }
	memset(m_dwStatus, 0, sizeof(m_dwStatus));
	int i = 0;
	int j = 0;
	char cs[128] = {0};
	char szLan[128] = {0};
    LPNET_DVR_VIDEOWALLWINDOWPOSITION lpModify; 
    LPDWORD lpWinNumEx; 
    lpModify = GetModify(); 
    lpWinNumEx = WinNumtoEx(); 
 
    NET_DVR_IN_PARAM struInputPapam ={0};
    NET_DVR_OUT_PARAM struOutputPapam ={0}; 
    struInputPapam.struCondBuf.pBuf = lpWinNumEx; 
    struInputPapam.struCondBuf.nLen = m_dwModifyNum * sizeof(DWORD);
    struInputPapam.struInParamBuf.pBuf = m_struModifyList; 
    struInputPapam.struInParamBuf.nLen = m_dwModifyNum * sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION);
    struOutputPapam.lpStatusList = m_dwStatus; 
    struOutputPapam.struOutBuf.pBuf = m_dwRetWinNum; 
    struOutputPapam.struOutBuf.nLen = m_dwModifyNum*sizeof(DWORD); 

    if (!NET_DVR_SetDeviceConfigEx(m_lUserID, NET_DVR_SET_VIDEOWALLWINDOWPOSITION, m_dwModifyNum, &struInputPapam, &struOutputPapam))
    {
        g_StringLanType(szLan, "设置窗口位置尝试失败", "Failed to set");
        sprintf(szLan, "%s, Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_VIDEOWALLWINDOWPOSITION");
        return;
    }
    else
    {       
        sprintf(cs, "The WinNum failed to set :\n");
        for(i = 0; i < m_dwModifyNum; i++)
        {
            if (m_dwStatus[i] > 0)
            {
                sprintf(cs, "%s %d\n", cs, m_struModifyList[i].dwWindowNo);
                j++;
            }
        }
        if (j > 0)
        {
            AfxMessageBox(cs);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_VIDEOWALLWINDOWPOSITION");
        }
        OnBtnGetAll(); 
    }
}
// 刷新该项
void CDlgWallWinVideoWall ::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	char szLan[128] = {0};
    NET_DVR_VIDEOWALLWINDOWPOSITION struWinPos = {0}; 
    DWORD    dwWinNoEx = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
    dwWinNoEx = m_dwWinNo + (dwWinNoEx << 24); 
    DWORD    dwStatus = 0; 
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLWINDOWPOSITION, 1, &dwWinNoEx, 4, &dwStatus, &struWinPos, sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION)))
	{
		g_StringLanType(szLan, "获取窗口信息失败", "Access to window information failed");
        sprintf(szLan, "%s, Error Code %d", szLan, NET_DVR_GetLastError()); 
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLWINDOWPOSITION");
		return ;
	}
    DelModifyRecord(m_dwWinNo); 
    UpdateWinList(struWinPos); 
    DrawList();
	UpdateData(FALSE);
}

void CDlgWallWinVideoWall ::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgWallWinVideoWall ::OnBtnSetPro() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_iCurSel == -1)
	{
		g_StringLanType(szLan, "未选中窗口号", "Window is not selected");
		AfxMessageBox(szLan);
		return;
	}
	m_struWallWinParam.dwSize = sizeof(NET_DVR_WALLWINPARAM);
	m_struWallWinParam.byTransparency = (BYTE)m_bTransparency;
	m_struWallWinParam.byWinMode = m_byWinMode; 
    DWORD    dwWinNoEx = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
    dwWinNoEx = m_dwWinNo + (dwWinNoEx << 24); 
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_WALLWINPARAM_SET, dwWinNoEx, &m_struWallWinParam, sizeof(m_struWallWinParam)))
	{
		g_StringLanType(szLan, "设置窗口信息失败", "Failed to set");
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWINPARAM_SET");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLWINPARAM_SET");
	}

}

//获取单个窗口属性
void CDlgWallWinVideoWall ::OnBtnGetPro() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_iCurSel == -1)
	{
		g_StringLanType(szLan, "未选中窗口号", "Window is not selected");
		AfxMessageBox(szLan);
		return;
	}
	DWORD dwReturned = 0;
    DWORD    dwWinNoEx = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
    dwWinNoEx = m_dwWinNo + (dwWinNoEx << 24); 
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_WALLWINPARAM_GET, dwWinNoEx, &m_struWallWinParam, sizeof(m_struWallWinParam), &dwReturned))
	{
		g_StringLanType(szLan, "获取窗口属性失败", "Failed to refresh the windows");
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWINPARAM_GET");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLWINPARAM_GET");
		m_bTransparency = m_struWallWinParam.byTransparency;
		m_byWinMode = m_struWallWinParam.byWinMode;
		UpdateData(FALSE);
	}
}
//获取所有窗口位置信息
void CDlgWallWinVideoWall ::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	int i,j = 0;
	CString cs;
	char szLan[128] = {0};
    char *pTemp = new char[4 + MAX_WALL_WIN_COUNT *sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION)];
	memset(pTemp, 0, 4 + MAX_WALL_WIN_COUNT *sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION));
    DWORD dwWallNo = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
    dwWallNo <<= 24; 
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLWINDOWPOSITION, 0xffffffff, &dwWallNo, 4, NULL, pTemp, 4 + MAX_WALL_WIN_COUNT * sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION)))
	{
		g_StringLanType(szLan, "获取窗口信息失败", "Access to window information failed");
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLWINDOWPOSITION");
		//return FALSE;
	}
	else
	{
		m_dwWinCount = *((DWORD*)pTemp);
		memcpy(m_struList, pTemp + 4, m_dwWinCount * sizeof(NET_DVR_VIDEOWALLWINDOWPOSITION));
		for (i = 0; i < m_dwWinCount; i++)
		{
//			m_dwWinNum[i] = m_struList[i].dwWindowNo & 0xffff;
            m_dwWinNum[i] = m_struList[i].dwWindowNo ;
		}
        for ( ; i < MAX_WALL_WIN_COUNT; i++)
        {
            m_dwWinNum[i] = 0xffffffff; 
        }
        // 消除修改记录
        m_dwModifyNum = 0; 
        memset(m_dwModifyRecord, 0, sizeof(m_dwModifyRecord));
	
    }	
	delete []pTemp;
	pTemp = NULL;
	DrawList();
	UpdateData(FALSE);
}

void CDlgWallWinVideoWall ::OnBtnSetWallCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struWallCfg.dwSize = sizeof(NET_DVR_WALL_CFG);
	m_struWallCfg.byTransparency = m_byTransparency;	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_WALL_CFG, 0, &m_struWallCfg, sizeof(NET_DVR_WALL_CFG)))
	{
		g_StringLanType(szLan, "设置失败", "Set fail");
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WALL_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WALL_CFG");
	}
}

void CDlgWallWinVideoWall ::OnBtnGetWallCfg() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_WALL_CFG, 0, &m_struWallCfg, sizeof(NET_DVR_WALL_CFG), &dwReturned))
	{
		g_StringLanType(szLan, "获取失败", "Get fail");
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WALL_CFG");
	}
	else
	{
		m_byTransparency = m_struWallCfg.byTransparency;
		UpdateData(FALSE);
	}
}

void CDlgWallWinVideoWall ::OnBtnWinTop() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	char szLan[64] = {0};
	DWORD dwWinNumEX = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel());
    dwWinNumEX = m_dwWinNo + (dwWinNumEX << 24); 

    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SWITCH_WIN_TOP, &dwWinNumEX, sizeof(DWORD)))
    {
        g_StringLanType(szLan, "置顶错误", "Failed to Set Window Top");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SWITCH_WIN_TOP");
        
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SWITCH_WIN_TOP");
	}	
}

void CDlgWallWinVideoWall ::OnBtnWinBottom() 
{
	// TODO: Add your control notification handler code here
	char szLan[64] = {0};	
    DWORD dwWinNumEX = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel());
    dwWinNumEX = m_dwWinNo + (dwWinNumEX << 24); 

	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SWITCH_WIN_BOTTOM, &dwWinNumEX, sizeof(DWORD)))
	{
        g_StringLanType(szLan, "置底错误", "Failed to Set Window Bottom");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SWITCH_WIN_BOTTOM");
	
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SWITCH_WIN_BOTTOM");
	}	
}

void CDlgWallWinVideoWall::OnBtnCloseAllWin() 
{
	// TODO: Add your control notification handler code here
    DWORD dwWallNo =  m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel());
    dwWallNo <<= 24; 
    char szLan[128] = {0}; 
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_VIDEOWALLWINDOW_CLOSEALL, &dwWallNo, sizeof(dwWallNo)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CLOSE_ALL_WND");
        g_StringLanType(szLan, "关闭所有窗口失败", "Failed to close all the windows");
        sprintf(szLan, "%s, Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CLOSE_ALL_WND");
	}
}



LPDWORD CDlgWallWinVideoWall::WinNumtoEx()
{
    UpdateData(TRUE); 
    memset(m_dwWinNumEx, 0, sizeof(m_dwWinNumEx)); 
    DWORD dwWallNo = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
    for (int i=0; i<m_dwModifyNum; i++)
    {
        m_dwWinNumEx[i] = (m_struModifyList[i].dwWindowNo &0xffff) + (dwWallNo << 24) ; 
    }
    return m_dwWinNumEx; 
}


BOOL CDlgWallWinVideoWall::UpdateWinList(NET_DVR_VIDEOWALLWINDOWPOSITION &WinPos)
{
  
    int i=0;
    for (i=0; i<m_dwWinCount; i++)
    {
        if ( WinPos.dwWindowNo == m_dwWinNum[i])
        {
            m_struList[i] = WinPos; 
            return TRUE; 
        }
    }
    char szLan[128] = {0}; 
    if (m_dwWinCount >= MAX_WALL_WIN_COUNT)
    {
        g_StringLanType(szLan, "窗口数不能超过256", "It is not allowed more than 256 window");
        AfxMessageBox(szLan);
        return FALSE; 
    }
    m_struList[i] = WinPos; 
    m_dwWinCount ++; 
    return TRUE; 
}


BOOL CDlgWallWinVideoWall::UpdateRecord(DWORD index)
{
    int i = 0;
    for (i=0 ; i<m_dwModifyNum; i++)
    {
        if ( m_dwModifyRecord[i] == index )
        {
            // 存在修改记录
           return TRUE; 
        }
    }
    //增加修改记录
    if ( m_dwModifyNum >= MAX_WALL_WIN_COUNT)
    {
        char szLan[128] ={0}; 
        g_StringLanType(szLan, "传入Index有误", "Parameter Index is error");
        AfxMessageBox(szLan);
        return FALSE; 
    }
    m_dwModifyRecord[i] = index; 
    m_dwModifyNum ++; 
    return TRUE; 
}


LPNET_DVR_VIDEOWALLWINDOWPOSITION CDlgWallWinVideoWall::GetModify()
{
    memset(m_struModifyList, 0, sizeof(m_struModifyList)); 
    for (int i=0; i<m_dwModifyNum; i++)
    {
        m_struModifyList[i] = m_struList[m_dwModifyRecord[i]]; 
    }
    return m_struModifyList; 
}

BOOL CDlgWallWinVideoWall::HasModify()
{
    return (m_dwModifyNum != 0)?TRUE:FALSE;
}

//删除修改记录
BOOL CDlgWallWinVideoWall::DelModifyRecord(DWORD WinNo)
{
    int i = 0; 
    for (i=0; i<m_dwModifyNum; i++)
    {
        if (m_struList[m_dwModifyRecord[i] ].dwWindowNo == WinNo)
        {
            break; 
        }
    }
    if (i<m_dwModifyNum)
    {
        for ( ; i<m_dwModifyNum -1; i++)
        {
            m_dwModifyRecord[i] = m_dwModifyRecord[i+1]; 
        }
        m_dwModifyNum --; 
    }
    return TRUE; 
}

void CDlgWallWinVideoWall::OnBtnSubwinSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwChannelEx = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
    dwChannelEx  =   (dwChannelEx<<24) + (m_dwSubwinNo<<16) + (m_dwWinNo && 0xffff);
    NET_DVR_MATRIX_DECCHAN_CONTROL struDecChanControl ={0}; 
    struDecChanControl.dwSize = sizeof(struDecChanControl);
    struDecChanControl.byEnableSpartan = m_BEnableSpartan; 
    struDecChanControl.byDecodeDelay = m_CombDelayDelay.GetCurSel(); 
    struDecChanControl.byDecChanScaleStatus = m_CombScaleStatus.GetCurSel(); 
    CString csError; 
    if ( !NET_DVR_MatrixSetDecChanCfg(m_lUserID, dwChannelEx, &struDecChanControl))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixSetDecChanCfg");
        csError.Format("设置子窗口属性失败, Error Code %d", NET_DVR_GetLastError() ); 
        AfxMessageBox(csError); 
        return ; 
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixSetDecChanCfg");
    OnBtnSubwinRefresh();  
}

void CDlgWallWinVideoWall::OnBtnSubwinRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwChannelEx = m_CombWallNo.GetItemData(m_CombWallNo.GetCurSel()); 
    dwChannelEx  =   (dwChannelEx<<24) + (m_dwSubwinNo<<16) + (m_dwWinNo && 0xffff);
    NET_DVR_MATRIX_DECCHAN_CONTROL struDecChanControl ={0}; 
    struDecChanControl.dwSize = sizeof(struDecChanControl );
    CString csError; 
    if ( !NET_DVR_MatrixGetDecChanCfg(m_lUserID, dwChannelEx, &struDecChanControl))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetDecChanCfg");
        csError.Format("刷新子窗口属性失败, Error Code %d", NET_DVR_GetLastError() ); 
        AfxMessageBox(csError); 
        return ; 
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetDecChanCfg");
    m_BEnableSpartan = struDecChanControl.byEnableSpartan; 
    m_CombDelayDelay.SetCurSel(struDecChanControl.byDecodeDelay); 
    m_CombScaleStatus.SetCurSel(struDecChanControl.byDecChanScaleStatus); 
    UpdateData(FALSE); 
}

void  CDlgWallWinVideoWall::SetWallRange(BYTE byMax, BYTE byMin)
{
    m_byMaxWallNo = byMax; 
    m_byMinWallNo = byMin;  
}


void CDlgWallWinVideoWall::InitVaildWallNo()
{
    NET_DVR_VIDEOWALLDISPLAYMODE struDisplayMode = {0}; 
    struDisplayMode.dwSize = sizeof(struDisplayMode);
//    DWORD dwRet;  
    m_CombWallNo.ResetContent(); 
    BYTE bySelWallNo = m_byWallNo; 
    DWORD dwMarkIndex =0; 
    char szlan[10]; 
    //轮询查询墙
    int i=0; 
    for (i=m_byMinWallNo; i<m_byMaxWallNo; i++)
    {    
//         if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYMODE, i, &struDisplayMode, sizeof(struDisplayMode), &dwRet))
        {
            sprintf(szlan, "%d", i); 
            int itemIndex = m_CombWallNo.AddString(szlan);
            m_CombWallNo.SetItemData(itemIndex, i); 
            if ( bySelWallNo == i)
            {
                dwMarkIndex = itemIndex; 
            }
        }
    }
    if (i!=m_byMinWallNo)
    {
        m_CombWallNo.SetCurSel(dwMarkIndex); 
    }
}

void CDlgWallWinVideoWall::OnSelchangeWinWallNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    int iSel = m_CombWallNo.GetCurSel(); 
    m_byWallNo = m_CombWallNo.GetItemData(iSel); 
    OnBtnGetAll(); 

}
