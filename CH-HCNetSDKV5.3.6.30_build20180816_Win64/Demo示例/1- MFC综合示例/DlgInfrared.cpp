// DlgInfrared.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfrared.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_DLG_INFRARED_LEARN_RETURN		WM_USER + 1

void CALLBACK g_SubDlgInfraredLearnCB(DWORD dwDataType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgInfrared *pThis = static_cast<CDlgInfrared*>(pUserData);
    
    HWND hWnd = pThis->GetSafeHwnd();
    
    DWORD dwTemp = 0;
    if (NULL == hWnd)
    {
        return;
    }
    if (dwDataType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
         dwTemp = *((DWORD*)lpBuffer);
            ::PostMessage(hWnd,WM_DLG_INFRARED_LEARN_RETURN, (DWORD)dwTemp,dwBufLen);
    }
    
}

/////////////////////////////////////////////////////////////////////////////
// CDlgInfrared dialog


CDlgInfrared::CDlgInfrared(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfrared::IDD, pParent)
    ,m_lUserID(-1)
    ,m_iDevIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgInfrared)
	m_csCmd1Name = _T("");
	m_csCmd10Name = _T("");
	m_csCmd11Name = _T("");
	m_csCmd12Name = _T("");
	m_csCmd13Name = _T("");
	m_csCmd14Name = _T("");
	m_csCmd15Name = _T("");
	m_csCmd16Name = _T("");
	m_csCmd17Name = _T("");
	m_csCmd18Name = _T("");
	m_csCmd19Name = _T("");
	m_csCmd2Name = _T("");
	m_csCmd20Name = _T("");
	m_csCmd21Name = _T("");
	m_csCmd22Name = _T("");
	m_csCmd23Name = _T("");
	m_csCmd24Name = _T("");
	m_csCmd25Name = _T("");
	m_csCmd26Name = _T("");
	m_csCmd27Name = _T("");
	m_csCmd28Name = _T("");
	m_csCmd29Name = _T("");
	m_csCmd3Name = _T("");
	m_csCmd30Name = _T("");
	m_csCmd31Name = _T("");
	m_csCmd32Name = _T("");
	m_csCmd4Name = _T("");
	m_csCmd5Name = _T("");
	m_csCmd6Name = _T("");
	m_csCmd7Name = _T("");
	m_csCmd8Name = _T("");
	m_csCmd9Name = _T("");
	m_csInfraredPortName = _T("");
	m_csInfraredCtrlName = _T("");
	m_bSave = FALSE;
    m_lInfraredHandle = -1;
	m_bSaveLearnCmd = TRUE;
    m_bStopLearn = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgInfrared::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfrared)
	DDX_Control(pDX, IDC_CMB_INFRARED_PORT_CTRL_LEARN, m_cmbIRPortLearn);
	DDX_Control(pDX, IDC_CMB_CMD_CTRL_NAME_LEARN, m_cmbCtrlLearn);
	DDX_Control(pDX, IDC_CMB_CMD_CTRL_NAME, m_cmbCMDCtrlName);
	DDX_Control(pDX, IDC_CMB_INFRARED_PORT_CTRL, m_cmbInfraredCtrl);
	DDX_Control(pDX, IDC_CMB_INFRARED_PORT, m_cmbInfraredPort);
	DDX_Text(pDX, IDC_EDIT_CMD1_NAME, m_csCmd1Name);
	DDX_Text(pDX, IDC_EDIT_CMD10_NAME, m_csCmd10Name);
	DDX_Text(pDX, IDC_EDIT_CMD11_NAME, m_csCmd11Name);
	DDX_Text(pDX, IDC_EDIT_CMD12_NAME, m_csCmd12Name);
	DDX_Text(pDX, IDC_EDIT_CMD13_NAME, m_csCmd13Name);
	DDX_Text(pDX, IDC_EDIT_CMD14_NAME, m_csCmd14Name);
	DDX_Text(pDX, IDC_EDIT_CMD15_NAME, m_csCmd15Name);
	DDX_Text(pDX, IDC_EDIT_CMD16_NAME, m_csCmd16Name);
	DDX_Text(pDX, IDC_EDIT_CMD17_NAME, m_csCmd17Name);
	DDX_Text(pDX, IDC_EDIT_CMD18_NAME, m_csCmd18Name);
	DDX_Text(pDX, IDC_EDIT_CMD19_NAME, m_csCmd19Name);
	DDX_Text(pDX, IDC_EDIT_CMD2_NAME, m_csCmd2Name);
	DDX_Text(pDX, IDC_EDIT_CMD20_NAME, m_csCmd20Name);
	DDX_Text(pDX, IDC_EDIT_CMD21_NAME, m_csCmd21Name);
	DDX_Text(pDX, IDC_EDIT_CMD22_NAME, m_csCmd22Name);
	DDX_Text(pDX, IDC_EDIT_CMD23_NAME, m_csCmd23Name);
	DDX_Text(pDX, IDC_EDIT_CMD24_NAME, m_csCmd24Name);
	DDX_Text(pDX, IDC_EDIT_CMD25_NAME, m_csCmd25Name);
	DDX_Text(pDX, IDC_EDIT_CMD26_NAME, m_csCmd26Name);
	DDX_Text(pDX, IDC_EDIT_CMD27_NAME, m_csCmd27Name);
	DDX_Text(pDX, IDC_EDIT_CMD28_NAME, m_csCmd28Name);
	DDX_Text(pDX, IDC_EDIT_CMD29_NAME, m_csCmd29Name);
	DDX_Text(pDX, IDC_EDIT_CMD3_NAME, m_csCmd3Name);
	DDX_Text(pDX, IDC_EDIT_CMD30_NAME, m_csCmd30Name);
	DDX_Text(pDX, IDC_EDIT_CMD31_NAME, m_csCmd31Name);
	DDX_Text(pDX, IDC_EDIT_CMD32_NAME, m_csCmd32Name);
	DDX_Text(pDX, IDC_EDIT_CMD4_NAME, m_csCmd4Name);
	DDX_Text(pDX, IDC_EDIT_CMD5_NAME, m_csCmd5Name);
	DDX_Text(pDX, IDC_EDIT_CMD6_NAME, m_csCmd6Name);
	DDX_Text(pDX, IDC_EDIT_CMD7_NAME, m_csCmd7Name);
	DDX_Text(pDX, IDC_EDIT_CMD8_NAME, m_csCmd8Name);
	DDX_Text(pDX, IDC_EDIT_CMD9_NAM, m_csCmd9Name);
	DDX_Text(pDX, IDC_EDIT_INFRARED_PORT_NAME, m_csInfraredPortName);
	DDX_Text(pDX, IDC_EDIT_INFRARED_PORT_NAME_CTRL, m_csInfraredCtrlName);
	DDX_Check(pDX, IDC_CHK_SAVE, m_bSaveLearnCmd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfrared, CDialog)
	//{{AFX_MSG_MAP(CDlgInfrared)
	ON_BN_CLICKED(IDC_BTN_IR_NAME_CFG_SET, OnBtnIrNameCfgSet)
	ON_BN_CLICKED(IDC_BTN_IR_NAME_CFG_GET, OnBtnIrNameCfgGet)
	ON_BN_CLICKED(IDC_BTN_SEND_CTRL_CMD, OnBtnSendCtrlCmd)
	ON_CBN_SELCHANGE(IDC_CMB_INFRARED_PORT_CTRL, OnSelchangeCmbInfraredPortCtrl)
	ON_BN_CLICKED(IDC_BTN_LEARN, OnBtnLearn)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP_LEARN, OnBtnStopLearn)
    ON_MESSAGE(WM_DLG_INFRARED_LEARN_RETURN, OnChangeInfraredLearnStatus)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfrared message handlers

void CDlgInfrared::OnBtnIrNameCfgSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    if (m_cmbInfraredPort.GetCurSel() < 0)
    {
        return;
    }
    
    memset(&m_struInfraredCmdNameCfg, 0, sizeof(m_struInfraredCmdNameCfg));
    m_struInfraredCmdNameCfg.dwSize = sizeof(m_struInfraredCmdNameCfg);
    memcpy(m_struInfraredCmdNameCfg.sIROutName, m_csInfraredPortName,MAX_IR_CMD_NAME_LEN);
    
    char szLan[1024] = {0};
    char szTemp[1024] = {0};

   
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[0].sCmdName, m_csCmd1Name,m_csCmd1Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[1].sCmdName, m_csCmd2Name,m_csCmd2Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[2].sCmdName, m_csCmd3Name,m_csCmd3Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[3].sCmdName, m_csCmd4Name,m_csCmd4Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[4].sCmdName, m_csCmd5Name,m_csCmd5Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[5].sCmdName, m_csCmd6Name,m_csCmd6Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[6].sCmdName, m_csCmd7Name,m_csCmd7Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[7].sCmdName, m_csCmd8Name,m_csCmd8Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[8].sCmdName, m_csCmd9Name,m_csCmd9Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[9].sCmdName, m_csCmd10Name,m_csCmd10Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[10].sCmdName, m_csCmd11Name,m_csCmd11Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[11].sCmdName, m_csCmd12Name,m_csCmd12Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[12].sCmdName, m_csCmd13Name,m_csCmd13Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[13].sCmdName, m_csCmd14Name,m_csCmd14Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[14].sCmdName, m_csCmd15Name,m_csCmd15Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[15].sCmdName, m_csCmd16Name,m_csCmd16Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[16].sCmdName, m_csCmd17Name,m_csCmd17Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[17].sCmdName, m_csCmd18Name,m_csCmd18Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[18].sCmdName, m_csCmd19Name,m_csCmd19Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[19].sCmdName, m_csCmd20Name,m_csCmd20Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[20].sCmdName, m_csCmd21Name,m_csCmd21Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[21].sCmdName, m_csCmd22Name,m_csCmd22Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[22].sCmdName, m_csCmd23Name,m_csCmd23Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[23].sCmdName, m_csCmd24Name,m_csCmd24Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[24].sCmdName, m_csCmd25Name,m_csCmd25Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[25].sCmdName, m_csCmd26Name,m_csCmd26Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[26].sCmdName, m_csCmd27Name,m_csCmd27Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[27].sCmdName, m_csCmd28Name,m_csCmd28Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[28].sCmdName, m_csCmd29Name,m_csCmd29Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[29].sCmdName, m_csCmd30Name,m_csCmd30Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[30].sCmdName, m_csCmd31Name,m_csCmd31Name.GetLength());
    memcpy(m_struInfraredCmdNameCfg.struIRCmdInfo[31].sCmdName, m_csCmd32Name,m_csCmd32Name.GetLength());
 

     if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_INFRARED_CMD_NAME_CFG,m_cmbInfraredPort.GetCurSel() +1,\
        &m_struInfraredCmdNameCfg, sizeof(m_struInfraredCmdNameCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_INFRARED_CMD_NAME_CFG IROut Port[%d]", m_cmbInfraredPort.GetCurSel() + 1);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_INFRARED_CMD_NAME_CFG IROut Port[%d]", m_cmbInfraredPort.GetCurSel() +1);
    }

    
	
}

BOOL CDlgInfrared::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_cmbInfraredPort.SetCurSel(0);
    m_cmbInfraredCtrl.SetCurSel(0);
    memset(&m_struInfraredCmdNameCfg, 0, sizeof(m_struInfraredCmdNameCfg));
    memset(&m_struIROutPutCtrlCfg, 0, sizeof(m_struIROutPutCtrlCfg));
    memset(&m_struInfraredLearnInfo,0,sizeof(m_struInfraredLearnInfo));
    memset(&m_struInfraredEnd,0,sizeof(m_struInfraredEnd));
    OnGetInfraredPortName(m_cmbInfraredPort.GetCurSel()+1);
    ShowChangeCMDNameInfo();
    ShowCMDCtrlInfo();
    char szLan[1024] = {0};
    m_cmbCtrlLearn.ResetContent();
    for (int i = 0 ; i< MAX_IR_CMD_NUM; i++)
    {
        sprintf(szLan,"IfraredCmd%02d",i+1);

        m_cmbCtrlLearn.AddString(szLan);
        m_cmbCtrlLearn.SetItemData(i,i+1);
    }

    m_cmbCtrlLearn.SetCurSel(0);
    m_cmbIRPortLearn.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfrared::OnBtnIrNameCfgGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    if (m_cmbInfraredPort.GetCurSel() < 0)
    {
        return;
    }
    
    OnGetInfraredPortName(m_cmbInfraredPort.GetCurSel() + 1);
    ShowChangeCMDNameInfo();
   
}
 
void CDlgInfrared::ShowChangeCMDNameInfo() 
{
     m_csInfraredPortName = m_struInfraredCmdNameCfg.sIROutName;
    
    m_csCmd1Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[0].sCmdName;
    m_csCmd2Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[1].sCmdName;
    m_csCmd3Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[2].sCmdName;
    m_csCmd4Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[3].sCmdName;
    m_csCmd5Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[4].sCmdName;
    m_csCmd6Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[5].sCmdName;
    m_csCmd7Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[6].sCmdName;
    m_csCmd8Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[7].sCmdName;
    m_csCmd9Name  = m_struInfraredCmdNameCfg.struIRCmdInfo[8].sCmdName;
    m_csCmd10Name = m_struInfraredCmdNameCfg.struIRCmdInfo[9].sCmdName;
    m_csCmd11Name = m_struInfraredCmdNameCfg.struIRCmdInfo[10].sCmdName;
    m_csCmd12Name = m_struInfraredCmdNameCfg.struIRCmdInfo[11].sCmdName;
    m_csCmd13Name = m_struInfraredCmdNameCfg.struIRCmdInfo[12].sCmdName;
    m_csCmd14Name = m_struInfraredCmdNameCfg.struIRCmdInfo[13].sCmdName;
    m_csCmd15Name = m_struInfraredCmdNameCfg.struIRCmdInfo[14].sCmdName;
    m_csCmd16Name = m_struInfraredCmdNameCfg.struIRCmdInfo[15].sCmdName;
    m_csCmd17Name = m_struInfraredCmdNameCfg.struIRCmdInfo[16].sCmdName;
    m_csCmd18Name = m_struInfraredCmdNameCfg.struIRCmdInfo[17].sCmdName;
    m_csCmd19Name = m_struInfraredCmdNameCfg.struIRCmdInfo[18].sCmdName;
    m_csCmd20Name = m_struInfraredCmdNameCfg.struIRCmdInfo[19].sCmdName;
    m_csCmd21Name = m_struInfraredCmdNameCfg.struIRCmdInfo[20].sCmdName;
    m_csCmd22Name = m_struInfraredCmdNameCfg.struIRCmdInfo[21].sCmdName;
    m_csCmd23Name = m_struInfraredCmdNameCfg.struIRCmdInfo[22].sCmdName;
    m_csCmd24Name = m_struInfraredCmdNameCfg.struIRCmdInfo[23].sCmdName;
    m_csCmd25Name = m_struInfraredCmdNameCfg.struIRCmdInfo[24].sCmdName;
    m_csCmd26Name = m_struInfraredCmdNameCfg.struIRCmdInfo[25].sCmdName;
    m_csCmd27Name = m_struInfraredCmdNameCfg.struIRCmdInfo[26].sCmdName;
    m_csCmd28Name = m_struInfraredCmdNameCfg.struIRCmdInfo[27].sCmdName;
    m_csCmd29Name = m_struInfraredCmdNameCfg.struIRCmdInfo[28].sCmdName;
    m_csCmd30Name = m_struInfraredCmdNameCfg.struIRCmdInfo[29].sCmdName;
    m_csCmd31Name = m_struInfraredCmdNameCfg.struIRCmdInfo[30].sCmdName;
    m_csCmd32Name = m_struInfraredCmdNameCfg.struIRCmdInfo[31].sCmdName;
    
    UpdateData(FALSE);
}

void CDlgInfrared::ShowCMDCtrlInfo() 
{
    UpdateData(TRUE);

    m_csInfraredCtrlName = m_struInfraredCmdNameCfg.sIROutName;

    m_cmbCMDCtrlName.ResetContent();
    CString strTemp;
    char szLan[12] = {0};
   	g_StringLanType(szLan, "无", "NULL");

    
    DWORD dwIndex = 0;
    for (int i = 0 ; i < MAX_IR_CMD_NUM; i++)
    {
        strTemp = m_struInfraredCmdNameCfg.struIRCmdInfo[i].sCmdName;
        if (strTemp.IsEmpty())
        {
            m_cmbCMDCtrlName.AddString(szLan);
        }
        else
        {
            m_cmbCMDCtrlName.AddString(strTemp);
        }
        m_cmbCMDCtrlName.SetItemData(dwIndex,i +1);
        dwIndex++;
    }

    m_cmbCMDCtrlName.SetCurSel(0);

    UpdateData(FALSE);
    
}
void CDlgInfrared::OnBtnSendCtrlCmd() 
{
	// TODO: Add your control notification handler code here

    UpdateData(TRUE);
    m_struIROutPutCtrlCfg.dwSize = sizeof(m_struIROutPutCtrlCfg);
    if ((m_cmbInfraredCtrl.GetCurSel() < 0) ||(m_cmbCMDCtrlName.GetCurSel() < 0))
    {
        return;
    }
    m_struIROutPutCtrlCfg.byIROutPort = m_cmbInfraredCtrl.GetCurSel() +1 ;
    m_struIROutPutCtrlCfg.byIRCmdIndex = m_cmbCMDCtrlName.GetItemData(m_cmbCMDCtrlName.GetCurSel());

    if (NET_DVR_RemoteControl(m_lUserID,NET_DVR_INFRARED_OUTPUT_CONTROL,&m_struIROutPutCtrlCfg,sizeof(m_struIROutPutCtrlCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_INFRARED_OUTPUT_CONTROL IROut Port[%d]", m_struIROutPutCtrlCfg.byIROutPort);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_INFRARED_OUTPUT_CONTROL IROut Port[%d]", m_struIROutPutCtrlCfg.byIROutPort);
    }

    
}

void CDlgInfrared::OnSelchangeCmbInfraredPortCtrl() 
{
	// TODO: Add your control notification handler code here
    if (m_cmbInfraredCtrl.GetCurSel() < 0)        
    {
        return;
    }
    

    OnGetInfraredPortName(m_cmbInfraredCtrl.GetCurSel() + 1);

    ShowCMDCtrlInfo();
}

void CDlgInfrared::OnGetInfraredPortName(DWORD dwIRPort) 
{
    DWORD dwRet = 0;
    
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_INFRARED_CMD_NAME_CFG,dwIRPort,\
        &m_struInfraredCmdNameCfg, sizeof(m_struInfraredCmdNameCfg),&dwRet))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_INFRARED_CMD_NAME_CFG IR Out Port[%d]", m_cmbInfraredPort.GetCurSel());
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_INFRARED_CMD_NAME_CFG IR Out Port[%d]", m_cmbInfraredPort.GetCurSel());
    }
}
void CDlgInfrared::OnBtnLearn() 
{
	// TODO: Add your control notification handler code here
    UpdateData(FALSE);
    char szLan[1024] = {0};
    if (m_lInfraredHandle < 0)
	{
        g_StringLanType(szLan,"请先建立连接","establish connection First"); 
        AfxMessageBox(szLan);
        return;
	}
    m_bStopLearn = FALSE;
    memset(&m_struInfraredLearnInfo,0,sizeof(m_struInfraredLearnInfo));
    m_struInfraredLearnInfo.dwSize = sizeof(m_struInfraredLearnInfo);
    m_struInfraredLearnInfo.byIROutPort = m_cmbIRPortLearn.GetCurSel() +1;
    m_struInfraredLearnInfo.byIRCmdIndex = m_cmbCtrlLearn.GetItemData(m_cmbCtrlLearn.GetCurSel());

    if (!NET_DVR_SendRemoteConfig(m_lInfraredHandle,ENUM_SEND_LEARN_IR_CMD_START,(char*)&m_struInfraredLearnInfo,sizeof(m_struInfraredLearnInfo)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T,"ENUM_SEND_LEARN_IR_CMD_START");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T,"ENUM_SEND_LEARN_IR_CMD_START");

        GetDlgItem(IDC_BTN_LEARN)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_STOP_LEARN)->EnableWindow(TRUE);
    }

    UpdateData(FALSE);
    
}

void CDlgInfrared::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	if (m_lInfraredHandle > -1)
	{
        return;
	}

    m_lInfraredHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_START_INFRARED_LEARN,NULL,0,g_SubDlgInfraredLearnCB,this);
    if (m_lInfraredHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_START_INFRARED_LEARN");
    }
    else
    {
        GetDlgItem(IDC_BTN_LEARN)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_LEARN)->EnableWindow(TRUE);
        
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_START_INFRARED_LEARN");
    }

    UpdateData(FALSE);
}

void CDlgInfrared::OnBtnStopLearn() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[1024] = {0};
    if (m_lInfraredHandle < 0)
    {
        g_StringLanType(szLan,"请先建立连接","establish connection First"); 
        AfxMessageBox(szLan);
        return;
    }
    
    memset(&m_struInfraredEnd,0,sizeof(m_struInfraredEnd));
    m_struInfraredEnd.dwSize = sizeof(m_struInfraredEnd);
    m_struInfraredEnd.bySaveLearnInfo = !m_bSaveLearnCmd;
    if (!m_bStopLearn)
    {
        if (!NET_DVR_SendRemoteConfig(m_lInfraredHandle,ENUM_SEND_LEARN_IR_CMD_END,(char*)&m_struInfraredEnd,sizeof(m_struInfraredEnd)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T,"ENUM_SEND_LEARN_IR_CMD_END");
            GetDlgItem(IDC_STATIC_LEARN_STATUS)->SetWindowText("Learn Failed");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T,"ENUM_SEND_LEARN_IR_CMD_END");

            GetDlgItem(IDC_BTN_LEARN)->EnableWindow(TRUE);
            GetDlgItem(IDC_BTN_STOP_LEARN)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_LEARN_STATUS)->SetWindowText("Learn Finish");
            m_bStopLearn = TRUE;

            if (m_lInfraredHandle < 0)
            {
                g_StringLanType(szLan,"请先建立连接","establish connection First"); 
                AfxMessageBox(szLan);
                return;
            }
            
            
            if (!NET_DVR_StopRemoteConfig(m_lInfraredHandle))
            {
                g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopRemoteConfig");
            }
            else
            {
                g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopRemoteConfig");
                GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
                GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
                GetDlgItem(IDC_BTN_LEARN)->EnableWindow(FALSE);
                GetDlgItem(IDC_BTN_STOP_LEARN)->EnableWindow(FALSE);
                m_lInfraredHandle = -1;
            }
            Sleep(3000);
            GetDlgItem(IDC_STATIC_LEARN_STATUS)->SetWindowText("......");
            UpdateData(FALSE);
        }
    }
    

    UpdateData(FALSE);
}

LRESULT CDlgInfrared::OnChangeInfraredLearnStatus(WPARAM wParam, LPARAM lParam)
{
    char szLan[1024] = {0};
    char szLanCn[1024] = {0};
    char szLanEn[1024] = {0};
    
    DWORD  dwStatus= (DWORD  )wParam;
    
    
    if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
    {
        GetDlgItem(IDC_BTN_LEARN)->EnableWindow(TRUE);

        GetDlgItem(IDC_STATIC_LEARN_STATUS)->SetWindowText("Learn Success");
        GetDlgItem(IDC_STATIC_LEARN_STATUS)->ShowWindow(SW_SHOW);
    }
    else  if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
    {
        GetDlgItem(IDC_STATIC_LEARN_STATUS)->SetWindowText("Learning");
        //GetDlgItem(IDC_BTN_LEARN)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_STATIC_LEARN_STATUS)->SetWindowText("Learn Failed");
        GetDlgItem(IDC_BTN_LEARN)->EnableWindow(TRUE);


        OnBtnStopLearn();
    }
    UpdateData(FALSE);
    return NULL;
}

void CDlgInfrared::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
    char szLan[1024] = {0};
    if (m_lInfraredHandle < 0)
    {
        g_StringLanType(szLan,"请先建立连接","establish connection First"); 
        AfxMessageBox(szLan);
        return;
    }
    

    if (!NET_DVR_StopRemoteConfig(m_lInfraredHandle))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopRemoteConfig");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopRemoteConfig");
        GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_LEARN)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_STOP_LEARN)->EnableWindow(FALSE);
        m_lInfraredHandle = -1;
    }
      GetDlgItem(IDC_STATIC_LEARN_STATUS)->SetWindowText("......");
    UpdateData(FALSE);	
}
