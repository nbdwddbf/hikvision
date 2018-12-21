// DlgGatewayCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGatewayCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCfg dialog


CDlgGatewayCfg::CDlgGatewayCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGatewayCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGatewayCfg)
	m_bEnable = FALSE;
	m_iDelayTime = 0;
	m_csName = _T("");
	m_bLocalEnable = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;        
    m_iDevIndex = -1;
    m_dwGatawayNum = 0;     // 门禁个数 
    m_lGatewayIndex = -1;    // 门禁索引
    memset(&m_struGateway, 0, sizeof(m_struGateway));

}


void CDlgGatewayCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGatewayCfg)
    DDX_Control(pDX, IDC_COMBO_LOCKWORKMODE, m_LockWorkModeCtrl);
    DDX_Control(pDX, IDC_COMBO_GATEWAY_INDEX, m_comboGatewayIndex);
    DDX_Control(pDX, IDC_COMBO_PICTYPE, m_comPicType);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_comboPicQuality);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_iDelayTime);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDX_Check(pDX, IDC_CHK_LOCAL_ENABLE, m_bLocalEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGatewayCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgGatewayCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_GATEWAY_INDEX, OnSelchangeComboGatewayIndex)
	ON_BN_CLICKED(IDC_BTN_SET_GATEWAY, OnBtnSetGateway)
	ON_BN_CLICKED(IDC_BNT_OPEN, OnBntOpen)
	ON_BN_CLICKED(IDC_BNT_OPEN_ALL, OnBntOpenAll)
	ON_BN_CLICKED(IDC_BNT_CLOSE, OnBntClose)
	ON_BN_CLICKED(IDC_BNT_CLOSE_ALL, OnBntCloseAll)
	ON_BN_CLICKED(IDC_BNT_ALWAYOPEN, OnBntAlwayopen)
	ON_BN_CLICKED(IDC_BNT_ALL_ALWAYSOPEN, OnBntAllAlwaysopen)
	ON_BN_CLICKED(IDC_BNT_ALWAYSCLOSE, OnBntAlwaysclose)
	ON_BN_CLICKED(IDC_BNT_ALL_ALWAYSCLOSE, OnBntAllAlwaysclose)
	ON_BN_CLICKED(IDC_BNT_RECOVERY, OnBntRecovery)
	ON_BN_CLICKED(IDC_BNT_ALL_RECOVERY, OnBntAllRecovery)
    ON_BN_CLICKED(IDC_BUTTON_CAPTURE_PIC, OnBntCapturePic)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_VISITOR_CALL_LADDER, &CDlgGatewayCfg::OnBnClickedBtnVisitorCallLadder)
    ON_BN_CLICKED(IDC_BTN_HOUSEHOLD_CALL_LADDER, &CDlgGatewayCfg::OnBnClickedBtnHouseholdCallLadder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCfg message handlers

BOOL CDlgGatewayCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_dwGatawayNum = (m_dwGatawayNum == 0)?128:m_dwGatawayNum; 
    InitWnd();	
	
    m_comboGatewayIndex.SetCurSel(0);

    OnSelchangeComboGatewayIndex();
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGatewayCfg::InitWnd()
{
    InitGatewayIndexCombo();
	InitLockModeCombo();
}

void CDlgGatewayCfg::InitGatewayIndexCombo()
{
    char szLan[128] = {0};
    m_comboGatewayIndex.ResetContent();
    for (int i = 0; i < m_dwGatawayNum; i++)
    {
        sprintf(szLan, "Gateway %d", i+1);
        m_comboGatewayIndex.InsertString(i, szLan);
        m_comboGatewayIndex.SetItemData(i, i+1);
    }

    //图片质量初始化
    m_comboPicQuality.ResetContent();
    m_comboPicQuality.InsertString(0,"最好");
    m_comboPicQuality.InsertString(1,"较好");
    m_comboPicQuality.InsertString(2,"一般");
    m_comboPicQuality.SetCurSel(0);

//     m_comPicType.ResetContent();
//     m_comPicType.InsertString(0,"CIF");
//     m_comPicType.InsertString(1,"QCIF");
//     m_comPicType.InsertString(2,"D1");
//     m_comPicType.SetCurSel(0);

    m_comPicType.ResetContent();
    for (int j = 0; j < 256; j++)
    {
        sprintf(szLan, "%d", j);
        m_comPicType.InsertString(j, szLan);
        m_comPicType.SetItemData(j, j);
    }
    m_comPicType.SetCurSel(0);
}

void CDlgGatewayCfg::InitLockModeCombo()
{
	char szLan[128] = {0};
	m_LockWorkModeCtrl.ResetContent();
	g_StringLanType(szLan, "通电开锁", "Power to unlock");
	m_LockWorkModeCtrl.AddString(szLan);
	g_StringLanType(szLan, "断电开锁", "Power Lock");
	m_LockWorkModeCtrl.AddString(szLan);
}

void CDlgGatewayCfg::SetGatewayCfgToWnd(NET_DVR_GATEWAY_CFG &struGateway)
{    
	char strTemp[33] = {0};
    m_bEnable = struGateway.byEnable;
    m_iDelayTime = struGateway.wDelayTime;
    memcpy(strTemp, struGateway.byName, NAME_LEN);
	m_csName.Format("%s", strTemp);
    m_bLocalEnable = struGateway.byLocalEnable;
    m_LockWorkModeCtrl.SetCurSel(struGateway.byLockWorkMode);
}

void CDlgGatewayCfg::GetGatewatCfgFromWnd(NET_DVR_GATEWAY_CFG &struGateway)
{
    struGateway.byEnable = m_bEnable;
    struGateway.wDelayTime = m_iDelayTime;
    struGateway.byLocalEnable = m_bLocalEnable;
    strncpy((char *)struGateway.byName, m_csName.GetBuffer(0), sizeof(struGateway.byName));
    struGateway.byLockWorkMode = m_LockWorkModeCtrl.GetCurSel();
}

BOOL CDlgGatewayCfg::GetGateWayCfg(NET_DVR_GATEWAY_CFG &struGateway)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_GATEWAY_CFG, m_lGatewayIndex, &struGateway, sizeof(struGateway), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_GATEWAY_CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GATEWAY_CFG");
        return FALSE;
    }
}

BOOL CDlgGatewayCfg::SetGateWayCfg(NET_DVR_GATEWAY_CFG &struGateway)
{
    DWORD dwReturn = 0;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_GATEWAY_CFG, m_lGatewayIndex, &struGateway, sizeof(struGateway)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_GATEWAY_CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GATEWAY_CFG");
        return FALSE;
    }
}

void CDlgGatewayCfg::OnSelchangeComboGatewayIndex() 
{
    UpdateData(TRUE); 
    m_lGatewayIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());	
    
    if (!GetGateWayCfg(m_struGateway))
    {
//        AfxMessageBox("Fail to get gateway config");
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to get gateway config");
    }

    SetGatewayCfgToWnd(m_struGateway);
    UpdateData(FALSE);
}

void CDlgGatewayCfg::OnBtnSetGateway() 
{
    UpdateData(TRUE);
    GetGatewatCfgFromWnd(m_struGateway);
    if (!SetGateWayCfg(m_struGateway))
    {
        AfxMessageBox("Fail to set gateway config");
    }
}

BOOL CDlgGatewayCfg::ControlGateway(LONG lGatewayIndex, DWORD dwStaic)
{
    if (NET_DVR_ControlGateway(m_lServerID, lGatewayIndex, dwStaic))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ControlGateway");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ControlGateway");
        return FALSE;
    }
}

void CDlgGatewayCfg::OnBntOpen() 
{
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 1))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntOpenAll() 
{
    if (!ControlGateway(-1, 1))
    {
        AfxMessageBox("Fail to control gateway");
    }
    
}

void CDlgGatewayCfg::OnBntClose() 
{
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 0))
    {
        AfxMessageBox("Fail to control gateway");
    }
    
}

void CDlgGatewayCfg::OnBntCloseAll() 
{
    if (!ControlGateway(-1, 0))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntAlwayopen() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 2))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntAllAlwaysopen() 
{
	// TODO: Add your control notification handler code here
    if (!ControlGateway(-1 , 2))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntAlwaysclose() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 3))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntAllAlwaysclose() 
{
	// TODO: Add your control notification handler code here
    if (!ControlGateway(-1 , 3))
    {
        AfxMessageBox("Fail to control gateway");
    }
}



void CDlgGatewayCfg::OnBntRecovery() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 4))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntAllRecovery() 
{
	// TODO: Add your control notification handler code here
    if (!ControlGateway(-1 , 4))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntCapturePic() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char cFilename[256] = {0};
    CString sTemp;

    int iChanIndex = 0;
    CTime time = CTime::GetCurrentTime();

    sTemp.Format("%s\\", g_struLocalParam.chPictureSavePath);
    DWORD dwRet = GetFileAttributes(sTemp);
    if ((dwRet == -1) || !(dwRet & FILE_ATTRIBUTE_DIRECTORY))
    {
        CreateDirectory(sTemp, NULL);
 	}

    NET_DVR_JPEGPARA struJpegPara;
	memset(&struJpegPara, 0, sizeof(NET_DVR_JPEGPARA));
	struJpegPara.wPicQuality = (WORD)m_comboPicQuality.GetCurSel(); 
    struJpegPara.wPicSize = (WORD)m_comPicType.GetCurSel();
    int iChanShowNum = 0; //iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
    sprintf(cFilename, "%s\\JPEG_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.jpg", \
        g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, iChanShowNum,	\
        time.GetYear(), time.GetMonth(), time.GetDay(), \
        time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());

    if (NET_DVR_CaptureJPEGPicture(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanShowNum, &struJpegPara, cFilename))
    {
        CString sTemp;	
        sTemp.Format("JPEG capture succ %s!",cFilename);
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CaptureJPEGPicture file[%s]", cFilename);
        AfxMessageBox(sTemp); 
        return;
    }
    else
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CaptureJPEGPicture");
        AfxMessageBox("JPEG capture failed!");
    }
 	
}


void CDlgGatewayCfg::OnBnClickedBtnVisitorCallLadder()
{
    // TODO:  在此添加控件通知处理程序代码
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex, 5))
    {
        AfxMessageBox("Fail to visitor call ladder");
    }
}


void CDlgGatewayCfg::OnBnClickedBtnHouseholdCallLadder()
{
    // TODO:  在此添加控件通知处理程序代码
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex, 6))
    {
        AfxMessageBox("Fail to household call ladder");
    }
}
