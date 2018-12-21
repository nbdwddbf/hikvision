// DecoderCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DecoderCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDecoderCfg dialog


CDecoderCfg::CDecoderCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecoderCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecoderCfg)
	m_iDecodeAddress = 0;
	m_strIp = _T("192.0.0.64");
	m_iPort = 8000;
	m_strPsw = _T("12345");
	m_strUser = _T("admin");
	m_iCodeChannel = 1;
	//}}AFX_DATA_INIT
}


void CDecoderCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecoderCfg)
	DDX_Control(pDX, IDC_COMBO_SERIAL_TYPE, m_comboSerialType);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
	DDX_Control(pDX, IDC_COMBO_SLOT, m_SlotCtrl);
	DDX_Control(pDX, IDC_COMBO_DECODERCHANNEL, m_DecoderChannelCtrl);
	DDX_Control(pDX, IDC_COMBO_485_BAUD, m_485BaudCtrl);
	DDX_Control(pDX, IDC_COMBO_SLOTNUM, m_SlotNumCtrl);
	DDX_Control(pDX, IDC_COMBO_485_STOP_BIT, m_485StopBitCtrl);
	DDX_Control(pDX, IDC_COMBO_485_FLOW, m_485FlowCtrl);
	DDX_Control(pDX, IDC_COMBO_485_DATA_BIT, m_485DataBitCtrl);
	DDX_Control(pDX, IDC_COMBO_485_CHECK_BIT, m_485CheckBitCtrl);
	DDX_Control(pDX, IDC_COMBO_485_CHANNEL, m_485ChannelCtrl);
	DDX_Control(pDX, IDC_COMBO_DECODE_TYPE, m_combo485DecodeType);
	DDX_Text(pDX, IDC_EDIT_DECODE_ADDRESS, m_iDecodeAddress);
	DDX_Text(pDX, IDC_EDIT_IP_ADDR, m_strIp);
	DDX_Text(pDX, IDC_EDIT_DEV_PORT, m_iPort);
	DDX_Text(pDX, IDC_EDIT_PSW, m_strPsw);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_CODECHANNEL, m_iCodeChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDecoderCfg, CDialog)
	//{{AFX_MSG_MAP(CDecoderCfg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SAVEALL, OnBtnSaveall)
	ON_BN_CLICKED(IDC_BTN_SAVE2, OnBtnSave2)
	ON_CBN_SELCHANGE(IDC_COMBO_SLOTNUM, OnSelchangeComboSlotnum)
	ON_CBN_SELCHANGE(IDC_COMBO_485_CHANNEL, OnSelchangeCombo485Channel)
	ON_CBN_SELCHANGE(IDC_COMBO_DECODERCHANNEL, OnSelchangeComboDecoderchannel)
	ON_CBN_SELCHANGE(IDC_COMBO_SLOT, OnSelchangeComboSlot)
	ON_BN_CLICKED(IDC_BTN_SAVEASSOCIATE, OnBtnSaveassociate)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_WORK_MODE, OnSelchangeComboWorkMode)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIAL_TYPE, OnSelchangeComboSerialType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecoderCfg message handlers

BOOL CDecoderCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_bSelOtherCombo = FALSE;
	m_comboSerialType.SetCurSel(1);
	CheckInit();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}  

BOOL CDecoderCfg::CheckInit()
{	
	char szPtz[DESC_LEN+1] = {0};
	NET_DVR_PTZCFG m_struPtzCfg;
	memset(&m_struPtzCfg, 0, sizeof(NET_DVR_PTZCFG));
	if (!NET_DVR_GetPTZProtocol_Ex(m_lServerID, 1, &m_struPtzCfg))
	{		
		MessageBox(NET_DVR_GetErrorMsg());
		//return FALSE;
	}
	else
	{
		m_combo485DecodeType.ResetContent();
		for (int i = 0; i < (int)m_struPtzCfg.dwPtzNum; i++)
		{
			memset(szPtz, 0, DESC_LEN);
			memcpy(szPtz, m_struPtzCfg.struPtz[i].byDescribe, DESC_LEN);
			m_combo485DecodeType.AddString(szPtz);
			m_combo485DecodeType.SetItemData(i, m_struPtzCfg.struPtz[i].dwType);
		}
	}

	CString tmp;
	m_485ChannelCtrl.ResetContent();
	m_DecoderChannelCtrl.ResetContent();
    int j = 0;
	for (j = 1; j < 9; j++)
	{
		tmp.Format("%d", j);
		m_485ChannelCtrl.AddString(tmp);
		m_DecoderChannelCtrl.AddString(tmp);
	}

	m_SlotNumCtrl.ResetContent();
	m_SlotCtrl.ResetContent();
	for (j = 0; j < 16; j++)
	{		
		tmp.Format("%d", j + 1);
		m_SlotNumCtrl.AddString(tmp);
		m_SlotCtrl.AddString(tmp);
	}

	m_485ChannelCtrl.SetCurSel(0);
	m_SlotNumCtrl.SetCurSel(0);
	m_DecoderChannelCtrl.SetCurSel(0);
	m_SlotCtrl.SetCurSel(0);
//	NET_DVR_PTZCFG struPtzCfg = {0};
//	if (!NET_DVR_GetPTZProtocol_Ex(m_lServerID, 1, &struPtzCfg))
//	{
//		MessageBox(NET_DVR_GetErrorMsg());
//		return FALSE;
//	}
//	else
//	{
//		//m_iNum = struPtzCfg.dwPtzNum;
//		m_combo485DecodeType.ResetContent();
//		for (int i = 0;i < struPtzCfg.dwPtzNum;i++)
//		{
//			m_combo485DecodeType.AddString((const char *)struPtzCfg.struPtz[i].byDescribe);
//		}
//	}
	
	m_bSelOtherCombo = TRUE;
	OnSelchangeComboWorkMode();
	UpdateData(FALSE);
	return TRUE;
}


void CDecoderCfg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	SaveData();
	UpdateData(TRUE);
	int i485Num = m_485ChannelCtrl.GetCurSel() + 1;
	int iSlotNum = m_SlotNumCtrl.GetCurSel() + 1;
	DWORD dwChannel = 0;
    dwChannel = (dwChannel >> 16) | i485Num;
    dwChannel = dwChannel << 16;
    dwChannel |= iSlotNum;

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DECODERCFG, dwChannel, &m_struDecoderCfg, sizeof(m_struDecoderCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DECODERCFG");
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DECODERCFG");	
}

void CDecoderCfg::OnBtnSaveall() 
{
	// TODO: Add your control notification handler code here
	SaveData();
	UpdateData(TRUE);
	int i485Num = 0;
	int iSlotNum = 0;
	DWORD dwChannel = 0;

	
	for (i485Num = 1; i485Num < 9; i485Num ++)
		for (iSlotNum = 1; iSlotNum < 17; iSlotNum++)
		{
			dwChannel = (dwChannel >> 16) | i485Num;
			dwChannel = dwChannel << 16;
			dwChannel |= iSlotNum;
			TRACE2("\n i485Num = %d, iSlotNum = %d", i485Num, iSlotNum);
			if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DECODERCFG, dwChannel, &m_struDecoderCfg, sizeof(m_struDecoderCfg)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DECODERCFG");
				MessageBox(NET_DVR_GetErrorMsg());
				return;
			}
			dwChannel = 0;
			Sleep(50);
		}

	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DECODERCFG");
	AfxMessageBox("Success");
}

void CDecoderCfg::OnBtnSave2() 
{
	// TODO: Add your control notification handler code here
	SaveData();
	UpdateData(TRUE);
	int i485Num = m_485ChannelCtrl.GetCurSel() + 1;
	DWORD dwChannel = 0;

	for (int i = 1; i < 17; i++)
	{
		dwChannel = (dwChannel >> 16) | i485Num;
		dwChannel = dwChannel << 16;
		dwChannel |= i;
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DECODERCFG, dwChannel, &m_struDecoderCfg, sizeof(m_struDecoderCfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DECODERCFG");
			MessageBox(NET_DVR_GetErrorMsg());
			return;
		}		
		Sleep(50);
	}

	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DECODERCFG");
}

void CDecoderCfg::SaveData()
{
    UpdateData(TRUE);
	if (m_comboSerialType.GetCurSel() == 0)
	{
		memset(&m_struRs232Cfg, 0, sizeof(m_struRs232Cfg));
		m_struRs232Cfg.dwSize = sizeof(m_struRs232Cfg);
		m_struRs232Cfg.dwBaudRate = m_485BaudCtrl.GetCurSel();
		m_struRs232Cfg.byDataBit = m_485DataBitCtrl.GetCurSel();
		m_struRs232Cfg.byStopBit = m_485StopBitCtrl.GetCurSel();
		m_struRs232Cfg.byParity = m_485CheckBitCtrl.GetCurSel();
		m_struRs232Cfg.byFlowcontrol = m_485FlowCtrl.GetCurSel();
		m_struRs232Cfg.dwWorkMode = m_comboWorkMode.GetCurSel() + 1;
	}
	else
	{
		memset(&m_struDecoderCfg, 0, sizeof(m_struDecoderCfg));
		m_struDecoderCfg.byDataBit = m_485DataBitCtrl.GetCurSel();
		m_struDecoderCfg.byFlowcontrol = m_485FlowCtrl.GetCurSel();
		m_struDecoderCfg.byParity = m_485CheckBitCtrl.GetCurSel();
		m_struDecoderCfg.byStopBit = m_485StopBitCtrl.GetCurSel();
		m_struDecoderCfg.dwBaudRate = m_485BaudCtrl.GetCurSel();
		m_struDecoderCfg.wDecoderAddress = m_iDecodeAddress;
		m_struDecoderCfg.wDecoderType = m_combo485DecodeType.GetCurSel();
	    m_struDecoderCfg.dwSize = sizeof(m_struDecoderCfg);
	}	
}

void CDecoderCfg::OnSelchangeComboSlotnum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i485Num = m_485ChannelCtrl.GetCurSel() + 1;
	int iSlotNum = m_SlotNumCtrl.GetCurSel() + 1;

	DWORD dwChannel = 0;
	DWORD dwReturned = 0;
    dwChannel = (dwChannel >> 16) | i485Num;
    dwChannel = dwChannel << 16;
    dwChannel |= iSlotNum;
	memset(&m_struDecoderCfg, 0, sizeof(m_struDecoderCfg));
	m_struDecoderCfg.dwSize = sizeof(m_struDecoderCfg);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DECODERCFG, dwChannel, &m_struDecoderCfg, sizeof(m_struDecoderCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DECODERCFG");	
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DECODERCFG");			
	}
	
	m_485DataBitCtrl.SetCurSel(m_struDecoderCfg.byDataBit);
	m_485FlowCtrl.SetCurSel(m_struDecoderCfg.byFlowcontrol);
	m_485CheckBitCtrl.SetCurSel(m_struDecoderCfg.byParity);
	m_485StopBitCtrl.SetCurSel(m_struDecoderCfg.byStopBit);
	m_485BaudCtrl.SetCurSel(m_struDecoderCfg.dwBaudRate);
	m_iDecodeAddress = m_struDecoderCfg.wDecoderAddress;
	m_combo485DecodeType.SetCurSel(m_struDecoderCfg.wDecoderType);

	UpdateData(FALSE);
}

void CDecoderCfg::OnSelchangeCombo485Channel() 
{
	// TODO: Add your control notification handler code here

	m_bSelOtherCombo = TRUE;
	DWORD dwReturned = 0;
	
	DWORD dwChannel = m_485ChannelCtrl.GetCurSel() + 1;//((m_485ChannelCtrl.GetCurSel() + 1) << 16) | 0xffff;
	
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_RS485_WORK_MODE, dwChannel, &m_struWorkMode, sizeof(m_struWorkMode), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RS485_WORK_MODE");	
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		m_comboWorkMode.SetCurSel(m_struWorkMode.byWorkMode);
		OnSelchangeComboWorkMode();
	}

	if (m_comboWorkMode.GetCurSel() == 0)
	{
		OnSelchangeComboSlotnum();
	}
	else
	{		
		dwChannel = ((m_485ChannelCtrl.GetCurSel() + 1) << 16) | 0xffff;		
		
		if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DECODERCFG, dwChannel, &m_struDecoderCfg, sizeof(m_struDecoderCfg), &dwReturned))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DECODERCFG");	
			MessageBox(NET_DVR_GetErrorMsg());
			return;
		}
		else
		{
			m_485DataBitCtrl.SetCurSel(m_struDecoderCfg.byDataBit);
			m_485FlowCtrl.SetCurSel(m_struDecoderCfg.byFlowcontrol);
			m_485CheckBitCtrl.SetCurSel(m_struDecoderCfg.byParity);
			m_485StopBitCtrl.SetCurSel(m_struDecoderCfg.byStopBit);
			m_485BaudCtrl.SetCurSel(m_struDecoderCfg.dwBaudRate);
			m_iDecodeAddress = m_struDecoderCfg.wDecoderAddress;
	        m_combo485DecodeType.SetCurSel(m_struDecoderCfg.wDecoderType);
		}
		
		UpdateData(FALSE);		
	}	
}

void CDecoderCfg::OnSelchangeComboDecoderchannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int chan = m_DecoderChannelCtrl.GetCurSel() + 1;
	int slot = m_SlotCtrl.GetCurSel() + 1;

	memset(&m_struCodeSplitterAssociate, 0, sizeof(m_struCodeSplitterAssociate));
	m_struCodeSplitterAssociate.dwSize = sizeof(m_struCodeSplitterAssociate);

	if (!NET_DVR_GetCodeSplitterAssociate(m_lServerID, chan, slot, &m_struCodeSplitterAssociate)) 
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetCodeSplitterAssociate");	
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetCodeSplitterAssociate");
	}

	m_strIp = m_struCodeSplitterAssociate.struIP.sIpV4;
	m_iPort = m_struCodeSplitterAssociate.wPort;
	m_strUser = m_struCodeSplitterAssociate.sUserName;
	m_strPsw = m_struCodeSplitterAssociate.sPassword;
	m_iCodeChannel = m_struCodeSplitterAssociate.byChan;
	UpdateData(FALSE);
}

void CDecoderCfg::OnSelchangeComboSlot() 
{
	// TODO: Add your control notification handler code here
	OnSelchangeComboDecoderchannel();
}

void CDecoderCfg::OnBtnSaveassociate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int chan = m_DecoderChannelCtrl.GetCurSel() + 1;
	int slot = m_SlotCtrl.GetCurSel() + 1;

	memset(&m_struCodeSplitterAssociate, 0, sizeof(m_struCodeSplitterAssociate));
	m_struCodeSplitterAssociate.dwSize = sizeof(m_struCodeSplitterAssociate);
	
	memcpy(m_struCodeSplitterAssociate.struIP.sIpV4, m_strIp, 16);
	m_struCodeSplitterAssociate.wPort = m_iPort;
	memcpy(m_struCodeSplitterAssociate.sUserName, m_strUser, NAME_LEN);
	memcpy(m_struCodeSplitterAssociate.sPassword, m_strPsw, PASSWD_LEN);
	m_struCodeSplitterAssociate.byChan = m_iCodeChannel;
	
	if (!NET_DVR_SetCodeSplitterAssociate(m_lServerID, chan, slot, &m_struCodeSplitterAssociate)) 
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetCodeSplitterAssociate");
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetCodeSplitterAssociate");
	}
}

void CDecoderCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	SaveData();

	if (m_comboSerialType.GetCurSel() == 0)
	{
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_RS232CFG, 0, &m_struRs232Cfg, sizeof(m_struRs232Cfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RS232CFG");
			AfxMessageBox(NET_DVR_GetErrorMsg());
		}

		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RS232CFG");
	}
	else
	{
		DWORD dwChannel = ((m_485ChannelCtrl.GetCurSel() + 1) << 16) | 0xffff;
				
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DECODERCFG, dwChannel, &m_struDecoderCfg, sizeof(m_struDecoderCfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DECODERCFG");
			MessageBox(NET_DVR_GetErrorMsg());
			return;
		}
	    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DECODERCFG");		
	}	
}

void CDecoderCfg::OnSelchangeComboWorkMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (/*m_comboSerialType.GetCurSel() != 0*/1)
	{
		switch (m_comboWorkMode.GetCurSel())
		{
		case 0:			
			if (m_comboSerialType.GetCurSel() == 0)
			{
				GetDlgItem(IDC_STATIC_CHANNEL_NUM)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_485_CHANNEL)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_SLOT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_SLOTNUM)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTN_SET)->ShowWindow(SW_SHOW);				
				
				GetDlgItem(IDC_STATIC_RATE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_485_BAUD)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_DATA_BIT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_485_DATA_BIT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_STOP_BIT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_485_STOP_BIT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_CHECK)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_485_CHECK_BIT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_FLOW)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_485_FLOW)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_DECODER)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO_DECODE_TYPE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_DECODER_ADDR)->ShowWindow(SW_HIDE);
	            GetDlgItem(IDC_EDIT_DECODE_ADDRESS)->ShowWindow(SW_HIDE);
				
				GetDlgItem(IDC_COMBO_SLOTNUM)->ShowWindow(SW_HIDE);				
				GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTN_SAVE2)->ShowWindow(SW_HIDE);
			    GetDlgItem(IDC_BTN_SAVEALL)->ShowWindow(SW_HIDE);
			}
			else
			{				
				GetDlgItem(IDC_STATIC_DECODER)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_COMBO_DECODE_TYPE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_DECODER_ADDR)->ShowWindow(SW_SHOW);
	            GetDlgItem(IDC_EDIT_DECODE_ADDRESS)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_STATIC_SLOT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_COMBO_SLOTNUM)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTN_SET)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BTN_SAVE2)->ShowWindow(SW_SHOW);
			    GetDlgItem(IDC_BTN_SAVEALL)->ShowWindow(SW_SHOW);
			}			
			break;
		case 1:
		case 2:
			GetDlgItem(IDC_STATIC_RATE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_485_BAUD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_DATA_BIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_485_DATA_BIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_STOP_BIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_485_STOP_BIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CHECK)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_485_CHECK_BIT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_FLOW)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_485_FLOW)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_DECODER)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_DECODE_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_DECODER)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_DECODE_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_DECODER_ADDR)->ShowWindow(SW_HIDE);
		    GetDlgItem(IDC_EDIT_DECODE_ADDRESS)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_SLOT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_SLOTNUM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_SET)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_SAVE2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_SAVEALL)->ShowWindow(SW_HIDE);
			break;
		default:
			GetDlgItem(IDC_STATIC_SLOT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SLOTNUM)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_SET)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_SAVE2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_SAVEALL)->ShowWindow(SW_SHOW);
			break;
		} 	
	}	

	if (m_comboSerialType.GetCurSel() == 1 && !m_bSelOtherCombo)
	{
		DWORD dwChannel = m_485ChannelCtrl.GetCurSel() + 1;		
		memset(&m_struWorkMode, 0, sizeof(m_struWorkMode));
		m_struWorkMode.dwSize = sizeof(m_struWorkMode);
		m_struWorkMode.byWorkMode = m_comboWorkMode.GetCurSel();
		
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_RS485_WORK_MODE, dwChannel, &m_struWorkMode, sizeof(m_struWorkMode)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RS485_WORK_MODE");
			MessageBox(NET_DVR_GetErrorMsg());
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RS485_WORK_MODE");
		}
	}
	else
	{
		m_bSelOtherCombo = FALSE;
	}
}

void CDecoderCfg::OnSelchangeComboSerialType() 
{
	// TODO: Add your control notification handler code here
	m_bSelOtherCombo = TRUE;

	if (m_comboSerialType.GetCurSel() == 0)
	{
		GetDlgItem(IDC_STATIC_CHANNEL_NUM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_485_CHANNEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SLOT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_SLOTNUM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SAVE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SAVEALL)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_RATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_485_BAUD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DATA_BIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_485_DATA_BIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_STOP_BIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_485_STOP_BIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CHECK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_485_CHECK_BIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FLOW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_485_FLOW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DECODER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_DECODE_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DECODER_ADDR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DECODE_ADDRESS)->ShowWindow(SW_HIDE);
		
		DWORD dwReturned = 0;
		if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_RS232CFG, 0, &m_struRs232Cfg, sizeof(m_struRs232Cfg), &dwReturned))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RS232CFG");
			AfxMessageBox(NET_DVR_GetErrorMsg());
		}
		else
		{
			m_485DataBitCtrl.SetCurSel(m_struRs232Cfg.byDataBit);
			m_485FlowCtrl.SetCurSel(m_struRs232Cfg.byFlowcontrol);
			m_485CheckBitCtrl.SetCurSel(m_struRs232Cfg.byParity);
			m_485StopBitCtrl.SetCurSel(m_struRs232Cfg.byStopBit);
			m_485BaudCtrl.SetCurSel(m_struRs232Cfg.dwBaudRate);
			m_comboWorkMode.SetCurSel(m_struRs232Cfg.dwWorkMode - 1);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RS232CFG");
		}
	}
	else
	{
		GetDlgItem(IDC_STATIC_CHANNEL_NUM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_485_CHANNEL)->ShowWindow(SW_SHOW);		

		GetDlgItem(IDC_STATIC_RATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_485_BAUD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DATA_BIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_485_DATA_BIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_STOP_BIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_485_STOP_BIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CHECK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_485_CHECK_BIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FLOW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_485_FLOW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DECODER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_DECODE_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DECODER_ADDR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DECODE_ADDRESS)->ShowWindow(SW_SHOW);		
	}

	OnSelchangeComboWorkMode();
}
