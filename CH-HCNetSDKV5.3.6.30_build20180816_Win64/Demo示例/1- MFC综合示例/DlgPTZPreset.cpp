/**********************************************************
FileName:    DlgPTZPreset.cpp
Description: PTZ preset     
Date:        2008/06/28
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/28>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPTZPreset.h"
#include ".\dlgptzpreset.h"

extern BOOL PTZPresetAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCommand, DWORD dwPresetIndex, char *szCmdString);
// CDlgPTZPreset dialog
/*********************************************************
  Function:	CDlgPTZPreset
  Desc:		constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgPTZPreset, CDialog)
CDlgPTZPreset::CDlgPTZPreset(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPTZPreset::IDD, pParent)
	, m_bAuto(FALSE)
    , m_wSensitivity(0)
{
	m_iDevIndex = -1;
	m_lLoginID = -1;
	m_lChanNum = -1;
}

/*********************************************************
  Function:	~CDlgPTZPreset
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgPTZPreset::~CDlgPTZPreset()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPTZPreset::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPTZPreset)
    DDX_Control(pDX, IDC_COMBO_WIPER_MODE, m_comboWiperMode);
    DDX_Control(pDX, IDC_COMBO_PRESET_SETUP, m_comboPreset);
    DDX_Text(pDX, IDC_EDIT_TIME_INTERVAL, m_byWorkTimeInterval);
    DDX_Text(pDX, IDC_EDIT_CONTINUE_TIME, m_dwContinueWorkTime);
    //}}AFX_DATA_MAP

    DDX_Text(pDX, IDC_EDIT_SENSITIVITY_RAIN, m_wSensitivity);
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgPTZPreset, CDialog)
	//{{AFX_MSG_MAP(CDlgPTZPreset)	
	ON_BN_CLICKED(IDC_BTN_PRESET_ADD, OnBnClickedBtnPresetAdd)
	ON_BN_CLICKED(IDC_BTN_PRESET_DEL, OnBnClickedBtnPresetDel)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_PTZ_TRAN, OnBtnPtzTran)
	ON_BN_CLICKED(IDC_BTN_DO, OnBtnDo)
	ON_BN_CLICKED(IDC_BTN_PTZ_LIGHT, OnBtnPtzLight)
	ON_BN_CLICKED(IDC_BTN_WIPER, OnBtnWiper)
	ON_BN_CLICKED(IDC_BTN_GET_WIPER, OnBtnGetWiper)
	ON_BN_CLICKED(IDC_BTN_SET_WIPER, OnBtnSetWiper)
	ON_CBN_SELCHANGE(IDC_COMBO_WIPER_MODE, OnSelchangeComboWiperMode)
	ON_BN_CLICKED(IDC_BTN_LINEAR_SCAN, OnBtnLinearScan)
	ON_BN_CLICKED(IDC_BTN_CLE_ALL_SEQ, OnBtnCleAllSeq)
	ON_BN_CLICKED(IDC_BTN_CLE_ALL_CRUISE, OnBtnCleAllCruise)
	ON_BN_CLICKED(IDC_BTN_ALL_CLE_PREST, OnBtnAllClePrest)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgPTZPreset message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPTZPreset::OnInitDialog()
{
	CDialog::OnInitDialog();

	int i=0;
	char szNum[8] = {0};
	for (i=0; i<301/*MAX_PRESET_V30+2*/; i++)//0 and 257 just for test
	{
		sprintf(szNum, "%d", i);
		m_comboPreset.AddString(szNum);
	}
	m_comboPreset.SetCurSel(1);

	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }
	
	m_iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	if (m_iDevIndex >= 0)
	{
		m_lLoginID = g_struDeviceInfo[m_iDevIndex].lLoginID;
		//	m_lChanNum = g_struDeviceInfo[m_iDevIndex].struChanInfo[m_iDevIndex].iChannelNO;
		m_lChanNum = iChanIndex + g_struDeviceInfo[m_iDevIndex].iStartChan;
	}
    AddResolution();
	
	memset(&m_struWiperInfo, 0, sizeof(m_struWiperInfo));
	m_comboWiperMode.SetCurSel(0);
	GetDlgItem(IDC_STATIC_TIME_INTERVAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TIME_INTERVAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TIME_INTERVAL_UNIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CONTINUE_TIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CONTINUE_TIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CONTINUE_TIME_UNIT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_SENSITIVITY_RAIN)->ShowWindow(SW_HIDE);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedBtnPresetAdd
  Desc:		add presets
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPTZPreset::OnBnClickedBtnPresetAdd()
{
	UpdateData(TRUE);
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPreset = m_comboPreset.GetCurSel();
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, SET_PRESET, iPreset, "SET_PRESET");
}

/*********************************************************
  Function:	OnBnClickedBtnPresetDel
  Desc:		delete presets
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPTZPreset::OnBnClickedBtnPresetDel()
{
	UpdateData(TRUE);
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPreset = m_comboPreset.GetCurSel();
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, CLE_PRESET, iPreset, "CLE_PRESET");
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgPTZPreset::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgPTZPreset::OnBtnPtzTran() 
{
	// TODO: Add your control notification handler code here
	char  sCodeBuf[128] = {0};
    sCodeBuf[0] = (char)0xa0;

    sCodeBuf[1] = (char)0x00;

    sCodeBuf[2] = (char)0x00;

    sCodeBuf[3] = (char)0x07;

    sCodeBuf[4] = (char)0x00;

    sCodeBuf[5] = (char)0x63;

    sCodeBuf[6] = (char)0xaf;

    sCodeBuf[7] = (char)0x6b;
	if (g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle >= 0)
	{
		if (!NET_DVR_TransPTZ_EX(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, sCodeBuf, 8))
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_FAIL_T, "NET_DVR_TransPTZ_EX");
		}
	}

}

extern BOOL PTZControlAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCommand,DWORD dwStop, char *szCmdString);
void CDlgPTZPreset::OnBtnDo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, PAN_AUTO, 0, "PAN_AUTO");
}

void CDlgPTZPreset::OnBtnPtzLight() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	for (int i = 0; i<100; i++)
	{
		if (i%2 == 0)
		{
			PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, LIGHT_PWRON, 0, "LIGHT_PWRON");	
		}
		else
		{
			PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex+1, iChanIndex, LIGHT_PWRON, 0, "LIGHT_PWRON");	
		}
		
	}
}

void CDlgPTZPreset::OnBtnWiper() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, WIPER_PWRON, 0, "WIPER_PWRON");	
	Sleep(2000);
	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, WIPER_PWRON, 1, "WIPER_PWRON");
	
}

void CDlgPTZPreset::OnBtnSetWiper() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struWiperInfo, 0, sizeof(m_struWiperInfo));
	m_struWiperInfo.dwSize = sizeof(m_struWiperInfo);
	m_struWiperInfo.byWiperWorkMode = m_comboWiperMode.GetCurSel();
	if(1 == m_comboWiperMode.GetCurSel())
	{
		m_struWiperInfo.ustruWiperModeParam.struWiperContinueWorkParam.byWorkTimeInterval = m_byWorkTimeInterval;
		m_struWiperInfo.ustruWiperModeParam.struWiperContinueWorkParam.dwContinueWorkTime = m_dwContinueWorkTime;
	}
    else if (2 == m_comboWiperMode.GetCurSel())
    {
        m_struWiperInfo.wSensitivity = m_wSensitivity;
    }

	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_WIPERINFO_CFG, m_lChanNum, &m_struWiperInfo, sizeof(m_struWiperInfo)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_WIPERINFO_CFG");
    }
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_WIPERINFO_CFG");
	}
	UpdateData(FALSE);
}

void CDlgPTZPreset::OnBtnGetWiper() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struWiperInfo, 0, sizeof(m_struWiperInfo));
	
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_WIPERINFO_CFG, m_lChanNum, &m_struWiperInfo, sizeof(m_struWiperInfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIPERINFO_CFG");
    }
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIPERINFO_CFG");
	}
	
    SetResolutionCurSel(m_struWiperInfo.byWiperWorkMode);
	OnSelchangeComboWiperMode();
	UpdateData(FALSE);
}

void CDlgPTZPreset::OnSelchangeComboWiperMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (0 == m_comboWiperMode.GetItemData(m_comboWiperMode.GetCurSel()))
	{
		GetDlgItem(IDC_STATIC_TIME_INTERVAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TIME_INTERVAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TIME_INTERVAL_UNIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CONTINUE_TIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CONTINUE_TIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CONTINUE_TIME_UNIT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_SENSITIVITY_RAIN)->ShowWindow(SW_HIDE);
	}
    else if (1 == m_comboWiperMode.GetItemData(m_comboWiperMode.GetCurSel()))
	{
		GetDlgItem(IDC_STATIC_TIME_INTERVAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TIME_INTERVAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TIME_INTERVAL_UNIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CONTINUE_TIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CONTINUE_TIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CONTINUE_TIME_UNIT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_SENSITIVITY_RAIN)->ShowWindow(SW_HIDE);
		
		m_byWorkTimeInterval = m_struWiperInfo.ustruWiperModeParam.struWiperContinueWorkParam.byWorkTimeInterval;
		m_dwContinueWorkTime = m_struWiperInfo.ustruWiperModeParam.struWiperContinueWorkParam.dwContinueWorkTime;
	}
    else if (2 == m_comboWiperMode.GetItemData(m_comboWiperMode.GetCurSel()))
    {
        GetDlgItem(IDC_STATIC_TIME_INTERVAL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_TIME_INTERVAL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_TIME_INTERVAL_UNIT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CONTINUE_TIME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_CONTINUE_TIME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CONTINUE_TIME_UNIT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_SENSITIVITY_RAIN)->ShowWindow(SW_SHOW);

        m_wSensitivity = m_struWiperInfo.wSensitivity;
    }
	UpdateData(FALSE);
}

void CDlgPTZPreset::OnBtnLinearScan() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	if (iChanIndex >= 0 && iDevIndex >= 0)
	{
		PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, LINEAR_SCAN, 0, "LINEAR_SCAN");	
	}

}


void CDlgPTZPreset::OnBtnCleAllSeq() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	if (iChanIndex >= 0 && iDevIndex >= 0)
	{
		PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, CLE_ALL_SEQ, 0, "CLE_ALL_SEQ");
	}
}

void CDlgPTZPreset::OnBtnCleAllCruise() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	if (iChanIndex >= 0 && iDevIndex >= 0)
	{
		PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, CLE_ALL_CRUISE, 0, "CLE_ALL_CRUISE");
	}
}

void CDlgPTZPreset::OnBtnAllClePrest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	if (iChanIndex >= 0 && iDevIndex >= 0)
	{
		PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, CLE_ALL_PRESET, 0, "CLE_ALL_PRESET");
	}
}

void CDlgPTZPreset::AddResolution()
{
    char szLan[128] = { 0 };
    m_comboWiperMode.ResetContent();
    int index = 0;

    g_StringLanType(szLan, "单次模式", "Single");
    m_comboWiperMode.InsertString(index, szLan);
    m_comboWiperMode.SetItemData(index, 0);
    index++;

    g_StringLanType(szLan, "持续模式", "Continue");
    m_comboWiperMode.InsertString(index, szLan);
    m_comboWiperMode.SetItemData(index, 1);
    index++;

    g_StringLanType(szLan, "自动模式", "Auto");
    m_comboWiperMode.InsertString(index, szLan);
    m_comboWiperMode.SetItemData(index, 2);
    index++;
}

void CDlgPTZPreset::SetResolutionCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboWiperMode.GetCount(); i++)
    {
        if (m_comboWiperMode.GetItemData(i) == dwData)
        {
            m_comboWiperMode.SetCurSel(i);
            return;
        }
    }
}