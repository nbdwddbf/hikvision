// DlgScreenCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgScreenCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenCtrl dialog
CDlgScreenCtrl::CDlgScreenCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScreenCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgScreenCtrl)
	m_byWallNo = 1;
	m_dwHeight = 0;
	m_dwWidth = 0;
	m_dwX = 0;
	m_dwY = 0;
	m_dwAreaZoomH = 0;
	m_dwAreaZoomW = 0;
	m_dwAreaZoomX = 0;
	m_dwAreaZoomY = 0;
	//}}AFX_DATA_INIT
    m_iCommandSel = -1;
}


void CDlgScreenCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScreenCtrl)
	DDX_Control(pDX, IDC_COMBO_SERIALPROTOCOL, m_cmbSerialProto);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_AREAZOOM_Y, m_cmbAreaZoomY);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_AREAZOOM_X, m_cmbAreaZoomX);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_AREAZOOM_WIDTH, m_cmbAreaZoomWidth);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_AREAZOOM_HEIGHT, m_cmbAreaZoomHeight);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_AREA_ZOOM, m_cmbAreaZoomCmd);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_RANGE_Y, m_cmbScreenCtrlY);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_RANGE_HEIGHT, m_cmbHeight);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_RANGE_WIDTH, m_cmbWidth);
	DDX_Control(pDX, IDC_COMB_SCREENCTRL_RANGE_X, m_cmbScreenCtrlX);
	DDX_Control(pDX, IDC_COMBO_INTERFACE, m_comboInterface);
	DDX_Control(pDX, IDC_COMBO_COMMAND, m_comboCommand);
	DDX_Text(pDX, IDC_EDIT_WALL_NO, m_byWallNo);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_HEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_WIDTH, m_dwWidth);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_X, m_dwX);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_Y, m_dwY);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_HEIGHT2, m_dwAreaZoomH);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_WIDTH2, m_dwAreaZoomW);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_X2, m_dwAreaZoomX);
	DDX_Text(pDX, IDC_EDT_SCREENCTRL_Y2, m_dwAreaZoomY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScreenCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgScreenCtrl)
	ON_CBN_SELCHANGE(IDC_COMBO_COMMAND, OnSelchangeComboCommand)
	ON_BN_CLICKED(IDC_BTN_OPERATE, OnBtnOperate)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_DEC, OnBtnBrightnessDec)
	ON_BN_CLICKED(IDC_BTN_BRIGHTNESS_INC, OnBtnBrightnessInc)
	ON_BN_CLICKED(IDC_BTN_SATURATION_DEC, OnBtnSaturationDec)
	ON_BN_CLICKED(IDC_BTN_SATURATION_INC, OnBtnSaturationInc)
	ON_BN_CLICKED(IDC_BTN_CONTRAST_DEC, OnBtnContrastDec)
	ON_BN_CLICKED(IDC_BTN_CONTRAST_INC, OnBtnContrastInc)
	ON_BN_CLICKED(IDC_BTN_HUE_DEC, OnBtnHueDec)
	ON_BN_CLICKED(IDC_BTN_HUE_INC, OnBtnHueInc)
	ON_BN_CLICKED(IDC_BTN_HROZONTAL_LEFT, OnBtnHrozontalLeft)
	ON_BN_CLICKED(IDC_BTN_HROZONTAL_RIGHT, OnBtnHrozontalRight)
	ON_BN_CLICKED(IDC_BTN_VETICAL_UP, OnBtnVeticalUp)
	ON_BN_CLICKED(IDC_BTN_VETICAL_DOWN, OnBtnVeticalDown)
	ON_BN_CLICKED(IDC_BTN_POWER_ON, OnBtnPowerOn)
	ON_BN_CLICKED(IDC_BTN_POWER_OFF, OnBtnPowerOff)
	ON_BN_CLICKED(IDC_BTN_SIGNAL, OnBtnSignal)
	ON_BN_CLICKED(IDC_BTN_MENU, OnBtnMenu)
	ON_BN_CLICKED(IDC_BTN_INFO, OnBtnInfo)
	ON_BN_CLICKED(IDC_BTN_RETURN, OnBtnReturn)
	ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_LEFT, OnBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, OnBtnRight)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_ZERO, OnBtnZero)
	ON_BN_CLICKED(IDC_BTN_ONE, OnBtnOne)
	ON_BN_CLICKED(IDC_BTN_TWO, OnBtnTwo)
	ON_BN_CLICKED(IDC_BTN_THREE, OnBtnThree)
	ON_BN_CLICKED(IDC_BTN_FOUR, OnBtnFour)
	ON_BN_CLICKED(IDC_BTN_FIVE, OnBtnFive)
	ON_BN_CLICKED(IDC_BTN_SIX, OnBtnSix)
	ON_BN_CLICKED(IDC_BTN_SEVEN, OnBtnSeven)
	ON_BN_CLICKED(IDC_BTN_EIGHT, OnBtnEight)
	ON_BN_CLICKED(IDC_BTN_NINE, OnBtnNine)
	ON_BN_CLICKED(IDC_BTN_ENABLE, OnBtnEnable)
	ON_BN_CLICKED(IDC_BTN_DISABLE, OnBtnDisable)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenCtrl message handlers

BOOL CDlgScreenCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_struScreenCtrl, 0, sizeof(m_struScreenCtrl));
    m_struScreenCtrl.dwSize = sizeof(m_struScreenCtrl);
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    CString csTemp; 
    int iIndex; 
    int i= 0; 
    for (i=0; i<16; i++)
    {
        csTemp.Format("%d", i); 
        iIndex = m_cmbScreenCtrlX.AddString(csTemp); 
        m_cmbScreenCtrlX.SetItemData(iIndex, i); 
        iIndex = m_cmbScreenCtrlY.AddString(csTemp);
        m_cmbScreenCtrlY.SetItemData(iIndex, i); 
		iIndex = m_cmbAreaZoomX.AddString(csTemp);
        m_cmbAreaZoomX.SetItemData(iIndex, i); 
		iIndex = m_cmbAreaZoomY.AddString(csTemp);
        m_cmbAreaZoomY.SetItemData(iIndex, i); 


        csTemp.Format("%d", i+1); 
        iIndex = m_cmbWidth.AddString(csTemp);
        m_cmbWidth.SetItemData(iIndex, i+1); 
        iIndex = m_cmbHeight.AddString(csTemp);
        m_cmbHeight.SetItemData(iIndex, i+1); 
		iIndex = m_cmbAreaZoomWidth.AddString(csTemp);
        m_cmbAreaZoomWidth.SetItemData(iIndex, i); 
		iIndex = m_cmbAreaZoomHeight.AddString(csTemp);
        m_cmbAreaZoomHeight.SetItemData(iIndex, i); 

    }
    m_cmbScreenCtrlX.SetCurSel(0); 
    m_cmbScreenCtrlY.SetCurSel(0); 
    m_cmbHeight.SetCurSel(0); 
    m_cmbWidth.SetCurSel(0); 
	m_cmbAreaZoomX.SetCurSel(0); 
    m_cmbAreaZoomY.SetCurSel(0); 
    m_cmbAreaZoomWidth.SetCurSel(0); 
    m_cmbAreaZoomHeight.SetCurSel(0); 

	m_cmbSerialProto.ResetContent(); 
	unsigned int *pSerialProto = NULL; 
	DWORD dwNum = 0; 
	GetSerialProto(pSerialProto, dwNum); 	
	for (i=0; i<dwNum; i++)
	{
		m_cmbSerialProto.AddString((char *)pSerialProto[i]);
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgScreenCtrl::SendCommand()
{
    char szLan[64] = {0};

    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CONTROL_SCREEN, &m_struScreenCtrl, sizeof(m_struScreenCtrl)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CONTROL_SCREEN");
        g_StringLanType(szLan, "²Ù×÷ÆÁÄ»Ê§°Ü", "Screen Control fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CONTROL_SCREEN");
    }
}

void CDlgScreenCtrl::UpdateBasicInfo()
{
    UpdateData(TRUE);
    m_struScreenCtrl.byProtocol = 0xff;
    m_struScreenCtrl.byWallNo = m_byWallNo;
//     m_struScreenCtrl.struRect.dwXCoordinate = m_dwX;
//     m_struScreenCtrl.struRect.dwYCoordinate = m_dwY;
//     m_struScreenCtrl.struRect.dwWidth = m_dwWidth;
//     m_struScreenCtrl.struRect.dwHeight = m_dwHeight;

    m_struScreenCtrl.struRect.dwXCoordinate = m_cmbScreenCtrlX.GetItemData(m_cmbScreenCtrlX.GetCurSel()) * 1920;
    m_struScreenCtrl.struRect.dwYCoordinate = m_cmbScreenCtrlY.GetItemData(m_cmbScreenCtrlY.GetCurSel()) * 1920;
    m_struScreenCtrl.struRect.dwWidth = m_cmbWidth.GetItemData(m_cmbWidth.GetCurSel()) * 1920;
    m_struScreenCtrl.struRect.dwHeight = m_cmbHeight.GetItemData(m_cmbHeight.GetCurSel()) * 1920;
};

void CDlgScreenCtrl::ClearCtrlParam()
{
    memset(&m_struScreenCtrl.struControlParam, 0, sizeof(m_struScreenCtrl.struControlParam));
}

void CDlgScreenCtrl::OnSelchangeComboCommand() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    m_iCommandSel = m_comboCommand.GetCurSel() + 1;
    m_struScreenCtrl.dwCommand = m_iCommandSel;
}

void CDlgScreenCtrl::OnBtnOperate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    UpdateBasicInfo();    

    switch (m_iCommandSel)
    {
    case 1:
    case 2:
    case 7:
    case 9:
    case 10:
    case 12:
    	break;
    case 8:
    case 11:
        m_struScreenCtrl.struRect.dwXCoordinate = 0;
        m_struScreenCtrl.struRect.dwYCoordinate = 0;
        m_struScreenCtrl.struRect.dwWidth = 0xffffffff;
        m_struScreenCtrl.struRect.dwHeight = 0xffffffff;
        break;
    case 3:
        m_struScreenCtrl.struControlParam.struInputCtrl.byInputSourceType = m_comboInterface.GetCurSel();
        break;
	case 13:
		m_struScreenCtrl.struControlParam.struZoomArea.byCmd = m_cmbAreaZoomCmd.GetCurSel() +1; 
		m_struScreenCtrl.struControlParam.struZoomArea.struArea.wXCoordinate  =  m_dwAreaZoomX; // m_cmbAreaZoomX.GetCurSel() * 1920; 
		m_struScreenCtrl.struControlParam.struZoomArea.struArea.wYCoordinate  = m_dwAreaZoomY; //m_cmbAreaZoomY.GetCurSel() * 1920;
		m_struScreenCtrl.struControlParam.struZoomArea.struArea.wWidth  =  m_dwAreaZoomW;//(m_cmbAreaZoomWidth.GetCurSel() + 1) * 1920;
		m_struScreenCtrl.struControlParam.struZoomArea.struArea.wHeight  =  m_dwAreaZoomH; //(m_cmbAreaZoomHeight.GetCurSel() + 1) * 1920;
		break; 
	default:
        return;
    }

    SendCommand();
}

void CDlgScreenCtrl::OnBtnBrightnessDec() 
{
	// TODO: Add your control notification handler code here
	if (m_iCommandSel != 4)
	{
        return;
	}

    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 1;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = -1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnBrightnessInc() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 4)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 1;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = 1;
    SendCommand();
	
}

void CDlgScreenCtrl::OnBtnSaturationDec() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 4)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 3;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = -1;
    SendCommand();
	
}

void CDlgScreenCtrl::OnBtnSaturationInc() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 4)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 3;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = 1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnContrastDec() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 4)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 2;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = -1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnContrastInc() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 4)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 2;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = 1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnHueDec() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 4)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 4;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = -1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnHueInc() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 4)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byColorType = 4;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = 1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnHrozontalLeft() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 5)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struPositionCtrl.byPositionType = 1;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = -1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnHrozontalRight() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 5)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struPositionCtrl.byPositionType = 1;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = 1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnVeticalUp() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 5)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struPositionCtrl.byPositionType = 2;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = 1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnVeticalDown() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 5)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struPositionCtrl.byPositionType = 2;
    m_struScreenCtrl.struControlParam.struDisplayCtrl.byScale = -1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnPowerOn() 
{
	// TODO: Add your control notification handler code here
	if (m_iCommandSel != 6)
	{
        return;
	}

    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 1;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnPowerOff() 
{
	// TODO: Add your control notification handler code here    
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 2;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnSignal() 
{
	// TODO: Add your control notification handler code here    
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 3;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnMenu() 
{
	// TODO: Add your control notification handler code here    
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 4;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnInfo() 
{
	// TODO: Add your control notification handler code here    
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 10;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnReturn() 
{
	// TODO: Add your control notification handler code here    
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 11;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnUp() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 6;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnDown() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 7;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnLeft() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 8;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnRight() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 9;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 5;    
    SendCommand();
}

void CDlgScreenCtrl::OnBtnZero() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 0;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnOne() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 1;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnTwo() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 2;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnThree() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 3;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnFour() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 4;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnFive() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 5;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnSix() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 6;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnSeven() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 7;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnEight() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 8;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnNine() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 6)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlType = 12;
    m_struScreenCtrl.struControlParam.struSimulateRemoteCrtl.byControlParam = 9;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnEnable() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 9)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struScreenWallCtrl.byEnable = TRUE;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnDisable() 
{
	// TODO: Add your control notification handler code here
    if (m_iCommandSel != 9)
    {
        return;
    }
    
    ClearCtrlParam();
    UpdateBasicInfo();
    m_struScreenCtrl.struControlParam.struScreenWallCtrl.byEnable = FALSE;
    SendCommand();
}

void CDlgScreenCtrl::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
