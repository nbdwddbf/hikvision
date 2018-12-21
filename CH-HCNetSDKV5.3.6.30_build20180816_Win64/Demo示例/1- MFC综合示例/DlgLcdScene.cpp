// DlgLcdScene.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdScene.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdScene dialog


CDlgLcdScene::CDlgLcdScene(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdScene::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdScene)
	m_dwCopyScene = 0;
	m_csSceneName = _T("");
	m_dwSceneNum = 0;
	m_dwSceneNumOperate = 0;
	m_dwWallNo = 1;
	m_bEnable = FALSE;
	m_dwWallNoOperate = 0;
	m_dwSceneNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgLcdScene::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdScene)
	DDX_Control(pDX, IDC_LIST_SCENE, m_listScene);
	DDX_Control(pDX, IDC_COMBO_SCENE_OPERATE, m_comboSceneOperate);
	DDX_Text(pDX, IDC_EDIT_COPY_SCENE, m_dwCopyScene);
	DDX_Text(pDX, IDC_EDIT_SCENE_NAME, m_csSceneName);
	DDX_Text(pDX, IDC_EDIT_SCENE_NUM, m_dwSceneNum);
	DDX_Text(pDX, IDC_EDIT_SCENE_NUM_OPERATE, m_dwSceneNumOperate);
	DDX_Text(pDX, IDC_EDIT_WALL_NO, m_dwWallNo);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_WALLNO_OPERATE, m_dwWallNoOperate);
	DDX_Text(pDX, IDC_EDIT_SCENE_NO, m_dwSceneNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdScene, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdScene)	
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_MODE_SET, OnBtnModeSet)
	ON_BN_CLICKED(IDC_BTN_MODE_GET, OnBtnModeGet)
	ON_BN_CLICKED(IDC_BTN_SCENE_GET, OnBtnSceneGet)
	ON_BN_CLICKED(IDC_BTN_CONTROL, OnBtnControl)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE_OPERATE, OnSelchangeComboSceneOperate)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCENE, OnClickListScene)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdScene message handlers

BOOL CDlgLcdScene::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_dwSetCount = 0;
    m_iCurSel = -1;
    memset(&m_struSenceName, 0, sizeof(m_struSenceName));    
    memset(&m_dwStatus, 0, sizeof(m_dwStatus));
    memset(&m_struSceneControlInfo, 0, sizeof(m_struSceneControlInfo));
    
    int i = 0;
    for (i = 0; i < LCD_SCENE_NUM; i++)
    {
        m_struSenceName[i].dwSize = sizeof(m_struSenceName[i]);
        m_struSceneNo[i].dwSize = sizeof(m_struSceneNo[i]);
        m_struSceneNo[i].dwWindowNo = 1 << 24;
        m_struSceneNo[i].dwSceneNo = i + 1;
    }	
    
    m_struSceneControlInfo.dwSize = sizeof(m_struSceneControlInfo);

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[128] = {0};
    m_listScene.SetExtendedStyle(m_listScene.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "场景号", "Scene No.");
    m_listScene.InsertColumn(0, szLan, LVCFMT_LEFT, 80);
    g_StringLanType(szLan, "场景名", "Scene Name");
    m_listScene.InsertColumn(1, szLan, LVCFMT_LEFT, 200);
    g_StringLanType(szLan, "使能", "Enable");
    m_listScene.InsertColumn(2, szLan, LVCFMT_LEFT, 80);
    
    OnBtnModeGet();
    OnSelchangeComboSceneOperate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgLcdScene::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    if (-1 == m_iCurSel)
    {
        g_StringLanType(szLan, "未选中条目", "Item is not selected");
        AfxMessageBox(szLan);
        return;
    }   
    
    CString cs;

    m_struSceneNo[m_iCurSel].dwSize = sizeof(m_struSceneNo[m_iCurSel]);
    m_struSceneNo[m_iCurSel].dwSceneNo = m_dwSceneNo;
    m_struSceneNo[m_iCurSel].dwWindowNo = m_dwWallNo << 24;    
    
    m_struSenceName[m_iCurSel].dwSize = sizeof(NET_DVR_WALLSCENECFG);
    m_struSenceName[m_iCurSel].byEnable = m_bEnable;
//    strncpy((char *)m_struSenceName[m_iCurSel].sSceneName, m_csSceneName, m_csSceneName.GetLength());
    strcpy((char *)m_struSenceName[m_iCurSel].sSceneName, (LPCTSTR)m_csSceneName); 
    cs.Format("%d_%d", m_struSceneNo[m_iCurSel].dwWindowNo >> 24, m_struSceneNo[m_iCurSel].dwSceneNo);
    m_listScene.SetItemText(m_iCurSel, 0, cs);
    
    cs.Format("%s", m_struSenceName[m_iCurSel].sSceneName);
	m_listScene.SetItemText(m_iCurSel, 1, cs);

    if (m_bEnable)
    {
        m_listScene.SetItemText(m_iCurSel, 2, "enable");
    }
    else
    {
        m_listScene.SetItemText(m_iCurSel, 2, "disable");
    }
}

void CDlgLcdScene::OnBtnModeSet() 
{
	// TODO: Add your control notification handler code here
    memset(m_dwStatus, 0, sizeof(m_dwStatus));
    int i = 0;
    int j = 0;
    char cs[128] = {0};
    char szLan[128] = {0};
    
    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_SCREEN_SCENE_PARAM, LCD_SCENE_NUM, m_struSceneNo, LCD_SCENE_NUM*sizeof(m_struSceneNo[0]), m_dwStatus, m_struSenceName, LCD_SCENE_NUM*sizeof(NET_DVR_WALLSCENECFG)))
    {
        g_StringLanType(szLan, "设置失败", "Failed to set");
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_SCENE_PARAM");
        return;
    }
    else
    {
        sprintf(cs, "Fail Scene num:\n");
        for(i = 0; i < LCD_SCENE_NUM; i++)
        {
            if (m_dwStatus[i] > 0)
            {
                sprintf(cs, "%s %d_%d\n", cs, m_struSceneNo[i].dwWindowNo >> 24, m_struSceneNo[i].dwSceneNo);
                j++;
            }
        }
        if (j > 0)
        {
            AfxMessageBox(cs);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_SCENE_PARAM");
        }
    }
    
}

void CDlgLcdScene::OnBtnModeGet() 
{
	// TODO: Add your control notification handler code here
    int i = 0;
    BOOL bOneFail = FALSE;
    char cs[2048] = {0};
    CString csTemp;
    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_SCREEN_SCENE_PARAM, LCD_SCENE_NUM, m_struSceneNo, LCD_SCENE_NUM * sizeof(m_struSceneNo[0]), m_dwStatus, m_struSenceName, LCD_SCENE_NUM * sizeof(NET_DVR_WALLSCENECFG)))
    {
        i = NET_DVR_GetLastError();
        sprintf(cs, "error code: %d", i);
        AfxMessageBox(cs);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_SCENE_PARAM");		
        //return;
    }
    else
    {
        sprintf(cs, "Not succeed:\n");
        for (i = 0; i < LCD_SCENE_NUM; i++)
        {
            if (m_dwStatus[i] > 0)
            {
                csTemp = m_listScene.GetItemText(i, 0);
                sprintf(cs, "%sScene No.: %s\n", cs, csTemp);
                bOneFail = TRUE;
            }
        }
        
        if (bOneFail)
        {
            AfxMessageBox(cs);
            m_dwSetCount = 0;		
            memset(m_dwStatus, 0, sizeof(m_dwStatus));           
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_SCENE_PARAM");
            m_dwSetCount = 0;		
            memset(m_dwStatus, 0, sizeof(m_dwStatus));            
        }
        
        DrawList();
	}
}

void CDlgLcdScene::OnBtnSceneGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    NET_DVR_VIDEO_WALL_INFO struTemp = {0};
    struTemp.dwSize = sizeof(struTemp);
    struTemp.dwWindowNo = m_dwWallNo << 24;

    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_CURRENT_SCREEN_SCENE, 1, &struTemp, sizeof(struTemp), NULL, &m_dwSceneNum, sizeof(m_dwSceneNum)))
    {
        MessageBox("NET_DVR_GET_CURRENT_SCREEN_SCENE FAILD");
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CURRENT_SCREEN_SCENE");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CURRENT_SCREEN_SCENE");
        UpdateData(FALSE);
	}
}

void CDlgLcdScene::OnBtnControl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    DWORD dwSceneCmd = m_comboSceneOperate.GetCurSel() + 1;
    if (dwSceneCmd == 0)
    {
        g_StringLanType(szLan, "请选择操作命令", "Please select the operating command");
        AfxMessageBox(szLan);
        return;
    }

    m_struSceneControlInfo.dwSize = sizeof(m_struSceneControlInfo);
    m_struSceneControlInfo.dwCmd = dwSceneCmd;
    m_struSceneControlInfo.struVideoWallInfo.dwSize = sizeof(m_struSceneControlInfo.struVideoWallInfo);
    m_struSceneControlInfo.struVideoWallInfo.dwWindowNo = m_dwWallNoOperate << 24;
    m_struSceneControlInfo.struVideoWallInfo.dwSceneNo = m_dwSceneNumOperate;

    if (!NET_DVR_RemoteControl(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SCREEN_SCENE_CONTROL, &m_struSceneControlInfo, sizeof(m_struSceneControlInfo)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_SCENE_CONTROL");
        MessageBox("NET_DVR_SCREEN_SCENE_CONTROL FAILED");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_SCENE_CONTROL");
        MessageBox("NET_DVR_SCREEN_SCENE_CONTROL SUCC");
	}
}

void CDlgLcdScene::OnSelchangeComboSceneOperate() 
{
	// TODO: Add your control notification handler code here
    if (m_comboSceneOperate.GetCurSel() == 3)
    {
        GetDlgItem(IDC_EDIT_COPY_SCENE)->ShowWindow(SW_HIDE);
    }
    else
    {
        m_dwCopyScene = 0;
        GetDlgItem(IDC_EDIT_COPY_SCENE)->ShowWindow(SW_HIDE);
	}
}

void CDlgLcdScene::DrawList()
{
    int i = 0;
    CString cs;
    m_listScene.DeleteAllItems();

    for(i = 0; i < LCD_SCENE_NUM; i++)
    {
        
        cs.Format("%d_%d",  m_struSceneNo[i].dwWindowNo >> 24, m_struSceneNo[i].dwSceneNo);
        m_listScene.InsertItem(i, cs, 0);
        if (m_struSenceName[i].byEnable)
        {
            cs.Format("%s", m_struSenceName[i].sSceneName);
            m_listScene.SetItemText(i, 1, cs);
            if (m_struSenceName[i].byEnable)
            {
                m_listScene.SetItemText(i, 2, "enable");
            }
            else
            {
                m_listScene.SetItemText(i, 2, "disable");
            }            
        }        
    }
}

void CDlgLcdScene::OnClickListScene(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    POSITION  iPos = m_listScene.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    m_iCurSel = m_listScene.GetNextSelectedItem(iPos);
    
    m_dwWallNo = m_struSceneNo[m_iCurSel].dwWindowNo >> 24;
    m_dwSceneNo = m_struSceneNo[m_iCurSel].dwSceneNo;
    m_bEnable = m_struSenceName[m_iCurSel].byEnable;
    m_csSceneName.Format("%s", m_struSenceName[m_iCurSel].sSceneName);
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgLcdScene::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
