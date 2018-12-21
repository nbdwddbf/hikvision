// DlgFibreDev.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFibreDev.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFibreDev dialog


CDlgFibreDev::CDlgFibreDev(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFibreDev::IDD, pParent)
    , m_dwSlots(0)
    , m_sMacAddr(_T(""))
    , m_sGateWay(_T(""))
    , m_sMask(_T(""))
    , m_sNewestSoftWareVer(_T(""))
    , m_sHardVer(_T(""))
    , m_dwFuncSlots(0)
    , m_sHardwareVer(_T(""))
    , m_sModelName(_T(""))
    , m_sPortName(_T(""))
    , m_dwRecvByteSpeed(0)
    , m_dwRecvPackets(0)
    , m_dwRecvPacketSpeed(0)
    , m_dwSendByteSpeed(0)
    , m_dwSendPackets(0)
    , m_dwSendPacketSpeed(0)
    , m_dwStatePortNo(0)
{
	//{{AFX_DATA_INIT(CDlgFibreDev)
	m_strPeerDevName = _T("");
	m_strPortMacAddr = _T("");
	m_strPortRemarks = _T("");
	m_strPeerPortID = _T("");
	m_strPeerPortMacAddr = _T("");
	m_strPeerPortRemarks = _T("");
	m_bEnableSetlldp = FALSE;
	m_bEnableGetlldp = FALSE;
	m_bEnablellpd = FALSE;
	m_dwHoldTime = 0;
	m_dwPacketTime = 0;
	m_dwReiniTime = 0;
	m_bySlotNo = 0;
	m_byPortNo = 0;
	m_dwStatusCardNum = 0;
	m_dwCRCPacket = 0;
	m_dwFragement = 0;
	m_dwFuncPortNum = 0;
	m_szSerialNo = _T("");
	m_szIPAddr = _T("");
	m_dwLostPacker = 0;
	m_dwNetPortNum = 0;
	m_szPortName = _T("");
	m_dwRecvByte = 0;
	m_dwSendByte = 0;
	m_szSeralNo = _T("");
	m_szTypeName = _T("");
	m_dwMainSlotNo = 0;
	m_dwSlotNum = 0;
	m_bPortEnable = FALSE;
	m_bEnable = FALSE;
	m_bCardEnable = FALSE;
	m_strPortNameNet = _T("");
	m_dwSlotUsedNum = 0;
	m_szSoftwareVer = _T("");
	m_szFuncSoftwareVer = _T("");
	m_dwFuncSlotNo = 0;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_lpConfigParam = NULL;
	m_lpFibreTopoInfo = NULL;
	m_lpCardTopoInfo = NULL;
	m_lpPortTopoInfo = NULL;
}


void CDlgFibreDev::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgFibreDev)
    DDX_Control(pDX, IDC_COMBO_PORTTYP_NET, m_cmbPortTypeNet);
    DDX_Control(pDX, IDC_COMBO_WORK_MOD, m_cmbWorkMod);
    DDX_Control(pDX, IDC_COMBO_PEER_WORK_MOD, m_cmbPeerWorkMod);
    DDX_Control(pDX, IDC_COMBO_PORT_TYPE, m_cmbPortType);
    DDX_Control(pDX, IDC_COMBO_PEER_BAND_WIDTH, m_cmbPeerBandWidth);
    DDX_Control(pDX, IDC_COMBO_BAND_WIDTH, m_cmbBandWidth);
    DDX_Control(pDX, IDC_COMBO_CARD_TYPE, m_cmbCardType);
    DDX_Control(pDX, IDC_COMBO_STRUTYPE, m_comboStruType);
    DDX_Control(pDX, IDC_COMBO_FUNC_STRUTYPE, m_comboFuncStruType);
    DDX_Control(pDX, IDC_COMBO_FUNCCARDINDEX, m_comboFuncCardIndex);
    DDX_Control(pDX, IDC_COMBO_FUNC_WORK_MODE, m_comboFuncWorkMode);
    DDX_Control(pDX, IDC_COMBO_FUNC_PORTINDEX, m_comboFuncPortIndex);
    DDX_Control(pDX, IDC_COMBO_FUNC_INDEX, m_comboFuncIndex);
    DDX_Control(pDX, IDC_COMBO_FUNC_BANDWIDTH, m_comboFuncBandWidth);
    DDX_Control(pDX, IDC_COMBO_CAEDSTAT_INDEX, m_comboCardIndex);
    DDX_Control(pDX, IDC_COMBO_STATUS_PORTTYPE, m_comboStatusPortTye);
    DDX_Control(pDX, IDC_COMBO_POWERTYPE, m_comboPowerType);
    DDX_Control(pDX, IDC_COMBO_PORTTYP, m_comboPortType);
    DDX_Control(pDX, IDC_COMBO_LINKSTATE, m_comboLinkState);
    DDX_Control(pDX, IDC_COMBO_NETPORTWIDTH, m_comboNetPortWidth);
    DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
    DDX_Control(pDX, IDC_COMBO_NETPORT_INDEX, m_comboNetPortIndex);
    DDX_Control(pDX, IDC_COMBO_INDEX, m_comboIndex);
    DDX_Control(pDX, IDC_COMBO_FIBRE_PORT_ID, m_comboPortID);
    DDX_Control(pDX, IDC_COMBO_FIBRE_CARD_ID, m_comboCardID);
    DDX_Text(pDX, IDC_EDIT_FIBRE_PDEV_NAME, m_strPeerDevName);
    DDX_Text(pDX, IDC_EDIT_FIBRE_PORT_MAC, m_strPortMacAddr);
    DDX_Text(pDX, IDC_EDIT_FIBRE_PORT_REMARKS, m_strPortRemarks);
    DDX_Text(pDX, IDC_EDIT_FIBRE_PPORT_ID, m_strPeerPortID);
    DDX_Text(pDX, IDC_EDIT_FIBRE_PPORT_MAC, m_strPeerPortMacAddr);
    DDX_Text(pDX, IDC_EDIT_FIBRE_PPORT_REMARKS, m_strPeerPortRemarks);
    DDX_Check(pDX, IDC_CHECK_ENABLE_SETLLDP, m_bEnableSetlldp);
    DDX_Check(pDX, IDC_CHECK_ENABLEGETLLDP, m_bEnableGetlldp);
    DDX_Check(pDX, IDC_CHECK_ENABLELLDP, m_bEnablellpd);
    DDX_Text(pDX, IDC_EDIT_HOLD_SECOND, m_dwHoldTime);
    DDX_Text(pDX, IDC_EDIT_PACKERTIME, m_dwPacketTime);
    DDX_Text(pDX, IDC_EDIT_REINITIME, m_dwReiniTime);
    DDX_Text(pDX, IDC_EDIT_SLOTNO, m_bySlotNo);
    DDX_Text(pDX, IDC_EDIT_PORTNO, m_byPortNo);
    DDX_Text(pDX, IDC_EDIT_CARDNO, m_dwStatusCardNum);
    DDX_Text(pDX, IDC_EDIT_CRC, m_dwCRCPacket);
    DDX_Text(pDX, IDC_EDIT_FRAGEMENT, m_dwFragement);
    DDX_Text(pDX, IDC_EDIT_FUNC_PORTNO, m_dwFuncPortNum);
    DDX_Text(pDX, IDC_EDIT_FUNC_SERIALNO, m_szSerialNo);
    DDX_Text(pDX, IDC_EDIT_IP_ADDR, m_szIPAddr);
    DDX_Text(pDX, IDC_EDIT_LOSTPACKER, m_dwLostPacker);
    DDX_Text(pDX, IDC_EDIT_PORT, m_dwNetPortNum);
    DDX_Text(pDX, IDC_EDIT_PORTNAME, m_szPortName);
    DDX_Text(pDX, IDC_EDIT_RECVBYTE, m_dwRecvByte);
    DDX_Text(pDX, IDC_EDIT_SENDBYTE, m_dwSendByte);
    DDX_Text(pDX, IDC_EDIT_SERIALNO, m_szSeralNo);
    DDX_Text(pDX, IDC_EDIT_TYPENAME, m_szTypeName);
    DDX_Text(pDX, IDC_EDIT_SLOT_NO_BASIC, m_dwMainSlotNo);
    DDX_Text(pDX, IDC_EDIT_SLOT_NUM, m_dwSlotNum);
    DDX_Check(pDX, IDC_CHECK_PORT_ENABLE, m_bPortEnable);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
    DDX_Check(pDX, IDC_CHECK_CARD_ENABLE, m_bCardEnable);
    DDX_Text(pDX, IDC_EDIT_PORTNAME_NET, m_strPortNameNet);
    DDX_Text(pDX, IDC_EDIT_SLOT_USED_NUM, m_dwSlotUsedNum);
    DDX_Text(pDX, IDC_EDIT_SOFTWAREVER, m_szSoftwareVer);
    DDX_Text(pDX, IDC_EDIT_FUNC_SOFTVER, m_szFuncSoftwareVer);
    DDX_Text(pDX, IDC_EDIT_BASIC_FUNC_SLOTNO, m_dwFuncSlotNo);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_SLOTS, m_dwSlots);
    DDX_Text(pDX, IDC_EDIT_MAC_ADDR, m_sMacAddr);
    DDX_Text(pDX, IDC_EDIT_GATE_WAY, m_sGateWay);
    DDX_Text(pDX, IDC_EDIT_MASK, m_sMask);
    DDX_Text(pDX, IDC_EDIT_FUNC_NEWSOFTVER, m_sNewestSoftWareVer);
    DDX_Text(pDX, IDC_EDIT_FUNC_HARDVER, m_sHardVer);
    DDX_Text(pDX, IDC_EDIT_FUNC_SLOTS, m_dwFuncSlots);
    DDX_Text(pDX, IDC_EDIT_HARDWAREVER, m_sHardwareVer);
    DDX_Control(pDX, IDC_COMBO_CARDTYPE, m_cmbType);
    DDX_Text(pDX, IDC_EDIT_FUNC_MODEL, m_sModelName);
    DDX_Control(pDX, IDC_COMBO_DUPLEXMODE, m_cmbDuplexMode);
    DDX_Control(pDX, IDC_COMBO_PORTSPEED, m_cmbPortSpeed);
    DDX_Text(pDX, IDC_EDIT_PTNAME, m_sPortName);
    DDX_Text(pDX, IDC_EDIT_RECVBYTESSPEED, m_dwRecvByteSpeed);
    DDX_Text(pDX, IDC_EDIT_RECVPACKETS, m_dwRecvPackets);
    DDX_Text(pDX, IDC_EDIT_RECVPAKSPEED, m_dwRecvPacketSpeed);
    DDX_Text(pDX, IDC_EDIT_SENDBYTESPEED, m_dwSendByteSpeed);
    DDX_Text(pDX, IDC_EDIT_SENDPACKETS, m_dwSendPackets);
    DDX_Text(pDX, IDC_EDIT_SENDPAKSPEED, m_dwSendPacketSpeed);
    DDX_Text(pDX, IDC_EDIT_STATE_PORT_NO, m_dwStatePortNo);
}


BEGIN_MESSAGE_MAP(CDlgFibreDev, CDialog)
	//{{AFX_MSG_MAP(CDlgFibreDev)
	ON_BN_CLICKED(IDC_BTN_FIBRE_PORT_REMARKS_GET, OnBtnFibrePortRemarksGet)
	ON_BN_CLICKED(IDC_BTN_FIBRE_PORT_REMARKS_SET, OnBtnFibrePortRemarksSet)
	ON_CBN_SELCHANGE(IDC_COMBO_FIBRE_CARD_ID, OnSelchangeComboFibreCardId)
	ON_CBN_SELCHANGE(IDC_COMBO_FIBRE_PORT_ID, OnSelchangeComboFibrePortId)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_GET_LLDP, OnBtnGetLldp)
	ON_BN_CLICKED(IDC_BTN_SET_LLDP, OnBtnSetLldp)
	ON_BN_CLICKED(IDC_BTN_SET_LLDPCFG, OnBtnSetLldpcfg)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, OnSelchangeComboIndex)
	ON_BN_CLICKED(IDC_BTN_GET_NETINFO, OnBtnGetNetinfo)
	ON_BN_CLICKED(IDC_BTN_CONVERT_GET, OnBtnConvertGet)
	ON_CBN_SELCHANGE(IDC_COMBO_NETPORT_INDEX, OnSelchangeComboNetportIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNC_PORTINDEX, OnSelchangeComboFuncPortindex)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCCARDINDEX, OnSelchangeComboFunccardindex)
	ON_CBN_SELCHANGE(IDC_COMBO_CAEDSTAT_INDEX, OnSelchangeComboCaedstatIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNC_INDEX, OnSelchangeComboFuncIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_CARD_TYPE, OnSelchangeComboCardType)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	//}}AFX_MSG_MAP
    ON_CBN_SELCHANGE(IDC_COMBO_CARDTYPE, &CDlgFibreDev::OnCbnSelchangeComboCardtype)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFibreDev message handlers

void CDlgFibreDev::OnBtnFibrePortRemarksGet() 
{
	// TODO: Add your control notification handler code here
	if (m_lpCardTopoInfo == NULL || m_lpPortTopoInfo == NULL)
	{
		return;
	}
	LPNET_DVR_STD_CONFIG lpConfigParam = new(std::nothrow) NET_DVR_STD_CONFIG;
	LPNET_DVR_FC_COND lpCondParam = new(std::nothrow) NET_DVR_FC_COND;
	LPNET_DVR_FC_PORT_REMARKS lpRemarks = new(std::nothrow) NET_DVR_FC_PORT_REMARKS;
	if (lpConfigParam == NULL || lpCondParam == NULL || lpRemarks == NULL)
	{
		AfxMessageBox("内存分配失败");
		return;
	}
	memset(lpConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
	memset(lpCondParam, 0, sizeof(NET_DVR_FC_COND));
	memset(lpRemarks, 0, sizeof(NET_DVR_FC_PORT_REMARKS));
	lpCondParam->dwSize = sizeof(NET_DVR_FC_COND);
	lpRemarks->dwSize = sizeof(NET_DVR_FC_PORT_REMARKS);
	lpCondParam->dwSlotNo = m_lpCardTopoInfo->dwCardNo;
	lpCondParam->dwPortNo = m_lpPortTopoInfo->dwPortNo;
	lpConfigParam->lpCondBuffer = lpCondParam;
	lpConfigParam->dwCondSize = sizeof(NET_DVR_FC_COND);
	lpConfigParam->lpOutBuffer = lpRemarks;
	lpConfigParam->dwOutSize = sizeof(NET_DVR_FC_PORT_REMARKS);
	if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_FC_PORT_REMARKS, lpConfigParam))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetSTDConfig NET_DVR_GET_FC_PORT_REMARKS");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetSTDConfig NET_DVR_GET_FC_PORT_REMARKS");
	}
	m_strPortRemarks = lpRemarks->byLocalRemarks;
	m_strPeerPortRemarks = lpRemarks->byPeerRemarks;
	delete lpRemarks;
	delete lpCondParam;
	memset(lpConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
	delete lpConfigParam;
	UpdateData(FALSE);
}

void CDlgFibreDev::OnBtnFibrePortRemarksSet() 
{
	// TODO: Add your control notification handler code here
	if (m_lpCardTopoInfo == NULL || m_lpPortTopoInfo == NULL)
	{
		return;
	}
	UpdateData(TRUE);
	LPNET_DVR_STD_CONFIG lpConfigParam = new(std::nothrow) NET_DVR_STD_CONFIG;
	LPNET_DVR_FC_COND lpCondParam = new(std::nothrow) NET_DVR_FC_COND;
	LPNET_DVR_FC_PORT_REMARKS lpRemarks = new(std::nothrow) NET_DVR_FC_PORT_REMARKS;
	if (lpConfigParam == NULL || lpCondParam == NULL || lpRemarks == NULL)
	{
		AfxMessageBox("内存分配失败");
		return;
	}
	memset(lpConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
	memset(lpCondParam, 0, sizeof(NET_DVR_FC_COND));
	memset(lpRemarks, 0, sizeof(NET_DVR_FC_PORT_REMARKS));
	lpCondParam->dwSize = sizeof(NET_DVR_FC_COND);
	lpRemarks->dwSize = sizeof(NET_DVR_FC_PORT_REMARKS);
	lpCondParam->dwSlotNo = m_lpCardTopoInfo->dwCardNo;
	lpCondParam->dwPortNo = m_lpPortTopoInfo->dwPortNo;
	strcpy((char*)lpRemarks->byLocalRemarks, m_strPortRemarks);
	strcpy((char*)lpRemarks->byPeerRemarks, m_strPeerPortRemarks);
	lpConfigParam->lpCondBuffer = lpCondParam;
	lpConfigParam->dwCondSize = sizeof(NET_DVR_FC_COND);
	lpConfigParam->lpInBuffer = lpRemarks;
	lpConfigParam->dwInSize = sizeof(NET_DVR_FC_PORT_REMARKS);
	if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_FC_PORT_REMARKS, lpConfigParam))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetSTDConfig NET_DVR_SET_FC_PORT_REMARKS");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetSTDConfig NET_DVR_SET_FC_PORT_REMARKS");
	}
	delete lpRemarks;
	delete lpCondParam;
	memset(lpConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
	delete lpConfigParam;
}

BOOL CDlgFibreDev::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFibreDev::OnSelchangeComboFibreCardId() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_comboCardID.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	m_lpCardTopoInfo = &m_lpFibreTopoInfo->struFCCardTopology[nSel];
	m_bCardEnable = m_lpCardTopoInfo->byEnable;
	m_dwSlotUsedNum = m_lpCardTopoInfo->dwSlotNum;
	m_strPortMacAddr.Format("%02X-%02X-%02X-%02X-%02X-%02X",
		m_lpCardTopoInfo->byLocalMac[0],
		m_lpCardTopoInfo->byLocalMac[1],
		m_lpCardTopoInfo->byLocalMac[2],
		m_lpCardTopoInfo->byLocalMac[3],
		m_lpCardTopoInfo->byLocalMac[4],
		m_lpCardTopoInfo->byLocalMac[5]);
	m_comboPortID.ResetContent();
	for (int nPortCnt = 0; nPortCnt < MAX_SINGLE_CARD_PORT_NO; nPortCnt++)
	{
		DWORD dwPortID = m_lpCardTopoInfo->struFCPortTopology[nPortCnt].dwPortNo;
		if (dwPortID != 0)
		{
			CString strPortID;
			strPortID.Format("%d", dwPortID);
			m_comboPortID.AddString(strPortID);
		}
	}
	m_comboPortID.SetCurSel(0);
	OnSelchangeComboFibrePortId();
	UpdateData(FALSE);
}

void CDlgFibreDev::OnSelchangeComboFibrePortId() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_comboPortID.GetCurSel();
	if (nSel == CB_ERR)
	{
		m_cmbPortType.SetCurSel(-1);
		m_cmbWorkMod.SetCurSel(-1);
		m_cmbBandWidth.SetCurSel(-1);
		m_strPortMacAddr = _T("");
		m_strPeerDevName = _T("");
		m_strPeerPortID = _T("");
		m_cmbPeerWorkMod.SetCurSel(-1);
		m_cmbPeerBandWidth.SetCurSel(-1);
		m_strPeerPortMacAddr = _T("");
		UpdateData(FALSE);
		return;
	}
	m_lpPortTopoInfo = &m_lpCardTopoInfo->struFCPortTopology[nSel];
	m_cmbPortType.SetCurSel(m_lpPortTopoInfo->byPortType-1);
	m_cmbWorkMod.SetCurSel(m_lpPortTopoInfo->byLocalWorkMode-1);
	m_cmbBandWidth.SetCurSel(m_lpPortTopoInfo->byLocalBandWidth-1);
	m_strPeerDevName = m_lpPortTopoInfo->byPeerTypeName;
	m_strPeerPortID.Format("%d", m_lpPortTopoInfo->dwPeerPortNo);
	m_cmbPeerWorkMod.SetCurSel(m_lpPortTopoInfo->byPeerWorkMode-1);
	m_cmbPeerBandWidth.SetCurSel(m_lpPortTopoInfo->byPeerBandWidth-1);
	m_strPeerPortMacAddr.Format("%02X-%02X-%02X-%02X-%02X-%02X",
		m_lpPortTopoInfo->byPeerMac[0],
		m_lpPortTopoInfo->byPeerMac[1],
		m_lpPortTopoInfo->byPeerMac[2],
		m_lpPortTopoInfo->byPeerMac[3],
		m_lpPortTopoInfo->byPeerMac[4],
		m_lpPortTopoInfo->byPeerMac[5]);
	UpdateData(FALSE);
}

void CDlgFibreDev::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_lpFibreTopoInfo;
	memset(m_lpConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
	delete m_lpConfigParam;
}

void CDlgFibreDev::OnBtnGetLldp() 
{
	// TODO: Add your control notification handler code here
    memset(&m_strulldpCfg, 0, sizeof(NET_DVR_LLDP_CFG));
	m_strulldpCfg.dwSize = sizeof(m_strulldpCfg);
    NET_DVR_STD_CONFIG struConfigParam;
    memset(&struConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
    struConfigParam.lpOutBuffer = &m_strulldpCfg;
    struConfigParam.dwOutSize = sizeof(m_strulldpCfg);
	
	
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_LLDP_CFG, &struConfigParam))
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GET_LLDP_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GET_LLDP_CFG");
    }
	
    m_bEnablellpd = m_strulldpCfg.byEnabled;
    m_dwHoldTime = m_strulldpCfg.dwHoldTime;
    m_dwPacketTime = m_strulldpCfg.dwPacketTime;
    m_dwReiniTime = m_strulldpCfg.dwReiniTime;
	
	m_comboIndex.ResetContent();
	for (int iCnt =0; iCnt < MAX_PORT_NUM; iCnt++)
	{
		CString str;
		str.Format("%d", iCnt);
		m_comboIndex.AddString(str);
	}
    m_comboIndex.SetCurSel(0);
    OnSelchangeComboIndex();

    UpdateData(FALSE);
    
}

void CDlgFibreDev::OnBtnSetLldp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    m_strulldpCfg.byEnabled = m_bEnablellpd;
    m_strulldpCfg.dwReiniTime = m_dwReiniTime;
    m_strulldpCfg.dwHoldTime = m_dwHoldTime;
    m_strulldpCfg.dwPacketTime = m_dwPacketTime;

    NET_DVR_STD_CONFIG struConfigParam;
    memset(&struConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
    struConfigParam.lpInBuffer = &m_strulldpCfg;
    struConfigParam.dwInSize = sizeof(m_strulldpCfg);


    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_LLDP_CFG, &struConfigParam))
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SET_LLDP_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SET_LLDP_CFG");
        return;
    }
}

void CDlgFibreDev::OnBtnSetLldpcfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int iIndex = m_comboIndex.GetCurSel();
    m_strulldpCfg.struLLDPPortCfg[iIndex].byEnabledRx = (BYTE)m_bEnableGetlldp;
    m_strulldpCfg.struLLDPPortCfg[iIndex].byEnabledTx = (BYTE)m_bEnableSetlldp;
    m_strulldpCfg.struLLDPPortCfg[iIndex].byPortNo = m_byPortNo;
    m_strulldpCfg.struLLDPPortCfg[iIndex].byCardNo = m_bySlotNo;
}

void CDlgFibreDev::OnSelchangeComboIndex() 
{
	// TODO: Add your control notification handler code here
	int iIndex = m_comboIndex.GetCurSel();

    m_byPortNo = m_strulldpCfg.struLLDPPortCfg[iIndex].byPortNo;
    m_bySlotNo = m_strulldpCfg.struLLDPPortCfg[iIndex].byCardNo;
    m_bEnableGetlldp = m_strulldpCfg.struLLDPPortCfg[iIndex].byEnabledRx;
    m_bEnableSetlldp = m_strulldpCfg.struLLDPPortCfg[iIndex].byEnabledTx;

    UpdateData(FALSE);
}

void CDlgFibreDev::OnBtnGetNetinfo() 
{
	// TODO: Add your control notification handler code here
    memset(&m_struFiberConvertBasic, 0, sizeof(m_struFiberConvertBasic));
	m_struFiberConvertBasic.dwSize = sizeof(m_struFiberConvertBasic);
    
    NET_DVR_STD_CONFIG struConfigParam;
    memset(&struConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
    struConfigParam.lpOutBuffer = &m_struFiberConvertBasic;
    struConfigParam.dwOutSize = sizeof(m_struFiberConvertBasic);
    
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_FIBER_CONVERT_BASIC_INFO_V50, &struConfigParam))
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GET_FIBER_CONVERT_BASIC_INFO_V50");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GET_FIBER_CONVERT_BASIC_INFO_V50");
    }
    
    m_comboPowerType.SetCurSel(m_struFiberConvertBasic.byPowerType - 1);
	m_dwSlotNum = m_struFiberConvertBasic.dwSlotNum;
    m_dwMainSlotNo = m_struFiberConvertBasic.struNetCardInfo.byMainSlotNo;
    m_szTypeName = m_struFiberConvertBasic.struNetCardInfo.byTypeName;
    m_szSeralNo = m_struFiberConvertBasic.struNetCardInfo.bySerialNo;
    m_szSoftwareVer = m_struFiberConvertBasic.struNetCardInfo.bySoftwareVersion;
    m_sHardwareVer = m_struFiberConvertBasic.struNetCardInfo.byHardwareVersion;
    m_szIPAddr = m_struFiberConvertBasic.struNetCardInfo.struIPAddr.sIpV4;
    m_sMask = m_struFiberConvertBasic.struNetCardInfo.struMask.sIpV4;
    m_sGateWay = m_struFiberConvertBasic.struNetCardInfo.struGateway.sIpV4;
    char sTemp[32] = { 0 };
    sprintf(sTemp, "%x-%x-%x-%x-%x-%x", m_struFiberConvertBasic.struNetCardInfo.byMacAddr[0],
        m_struFiberConvertBasic.struNetCardInfo.byMacAddr[1],
        m_struFiberConvertBasic.struNetCardInfo.byMacAddr[2],
        m_struFiberConvertBasic.struNetCardInfo.byMacAddr[3],
        m_struFiberConvertBasic.struNetCardInfo.byMacAddr[4],
        m_struFiberConvertBasic.struNetCardInfo.byMacAddr[5]
        );
    m_sMacAddr = sTemp;
    m_dwSlots = m_struFiberConvertBasic.struNetCardInfo.bySlotNums;
    m_comboStruType.SetCurSel(m_struFiberConvertBasic.struNetCardInfo.byStructureType - 1);
	UpdateData(FALSE);

    m_comboNetPortIndex.SetCurSel(0);
    m_cmbType.SetCurSel(0);
    m_comboFuncCardIndex.SetCurSel(0);
    
    OnSelchangeComboNetportIndex();
    OnSelchangeComboFunccardindex();
}

void CDlgFibreDev::OnBtnConvertGet() 
{
	// TODO: Add your control notification handler code here

    memset(&m_struFiberConbertState, 0, sizeof(m_struFiberConbertState));
	m_struFiberConbertState.dwSize = sizeof(m_struFiberConbertState);
    
    NET_DVR_STD_CONFIG struConfigParam;
    memset(&struConfigParam, 0, sizeof(struConfigParam));
    struConfigParam.lpOutBuffer = &m_struFiberConbertState;
    struConfigParam.dwOutSize = sizeof(m_struFiberConbertState);
    
    
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_FIBER_CONVERT_WORK_STATE_V50, &struConfigParam))
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GET_FIBER_CONVERT_WORK_STATE_V50");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GET_FIBER_CONVERT_WORK_STATE_V50");
    }
    
    m_cmbCardType.SetCurSel(0);
	OnSelchangeComboCardType();
}


void CDlgFibreDev::OnSelchangeComboNetportIndex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);    
    int iIndex = m_comboNetPortIndex.GetCurSel();
	if (iIndex == CB_ERR)
	{
		return;
	}
    m_dwNetPortNum = m_struFiberConvertBasic.struNetCardInfo.struPortInfo[iIndex].dwPortNo;
    m_strPortNameNet = m_struFiberConvertBasic.struNetCardInfo.struPortInfo[iIndex].byPortName;
    m_comboWorkMode.SetCurSel((int)m_struFiberConvertBasic.struNetCardInfo.struPortInfo[iIndex].byWorkMode - 1);
    m_comboNetPortWidth.SetCurSel((int)m_struFiberConvertBasic.struNetCardInfo.struPortInfo[iIndex].byBandWidth - 1);
    m_cmbPortTypeNet.SetCurSel(m_struFiberConvertBasic.struNetCardInfo.struPortInfo[iIndex].byPortType - 1);
    UpdateData(FALSE);
}

void CDlgFibreDev::OnSelchangeComboFuncPortindex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
    int iIndex = m_comboFuncCardIndex.GetCurSel();
    int iPindex = m_comboFuncPortIndex.GetCurSel();
	if (iIndex == CB_ERR || iPindex == CB_ERR)
	{
		return;
	}
    if (m_cmbType.GetCurSel() == 0) //接收卡
    {
        SelchangeComboRecvCardPortIndex(iIndex, iPindex);
    }
    else if (m_cmbType.GetCurSel() == 1) //发送机
    {
        SelchangeComboRemoteSendCardPortIndex(iIndex, iPindex);
    }
    else
    {
        return; //未知卡类型
    }
}

void CDlgFibreDev::SelchangeComboRecvCardPortIndex(int iIndex, int iPindex)
{
    m_dwFuncPortNum = m_struFiberConvertBasic.struFuncCardInfo[iIndex].struPortInfo[iPindex].dwPortNo;
    m_szPortName = m_struFiberConvertBasic.struFuncCardInfo[iIndex].struPortInfo[iPindex].byPortName;
    m_comboFuncWorkMode.SetCurSel(m_struFiberConvertBasic.struFuncCardInfo[iIndex].struPortInfo[iPindex].byWorkMode - 1);
    m_comboFuncBandWidth.SetCurSel(m_struFiberConvertBasic.struFuncCardInfo[iIndex].struPortInfo[iPindex].byBandWidth - 1);
    m_comboPortType.SetCurSel(m_struFiberConvertBasic.struFuncCardInfo[iIndex].struPortInfo[iPindex].byPortType - 1);
    UpdateData(FALSE);
}

void CDlgFibreDev::SelchangeComboRemoteSendCardPortIndex(int iIndex, int iPindex)
{
    m_dwFuncPortNum = m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].struPortInfo[iPindex].dwPortNo;
    m_szPortName = m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].struPortInfo[iPindex].byPortName;
    m_comboFuncWorkMode.SetCurSel(m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].struPortInfo[iPindex].byWorkMode - 1);
    m_comboFuncBandWidth.SetCurSel(m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].struPortInfo[iPindex].byBandWidth - 1);
    m_comboPortType.SetCurSel(m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].struPortInfo[iPindex].byPortType - 1);
    UpdateData(FALSE);
}

void CDlgFibreDev::OnSelchangeComboFunccardindex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	int iIndex = m_comboFuncCardIndex.GetCurSel();
	if (iIndex == CB_ERR)
	{
		return;
	}
    if (m_cmbType.GetCurSel() == 0) //接收卡
    {
        SelchangeComboRecvCardIndex(iIndex);
    }
    else if (m_cmbType.GetCurSel() == 1) //发送机
    {
        SelchangeComboRemoteSendCardIndex(iIndex);
    }
    else
    {
        return; //未知卡类型
    }
   
}

void CDlgFibreDev::SelchangeComboRecvCardIndex(int iIndex)
{
    m_dwFuncSlotNo = m_struFiberConvertBasic.struFuncCardInfo[iIndex].byMainSlotNo;
    m_sModelName = m_struFiberConvertBasic.struFuncCardInfo[iIndex].byTypeName;
    m_szSerialNo = m_struFiberConvertBasic.struFuncCardInfo[iIndex].bySerialNo;
    m_szFuncSoftwareVer = m_struFiberConvertBasic.struFuncCardInfo[iIndex].bySoftwareVersion;
    if (m_struFiberConvertBasic.struFuncCardInfo[iIndex].byIsVerMismatch)
    {
        m_sNewestSoftWareVer = m_struFiberConvertBasic.struFuncCardInfo[iIndex].byNewestSoftwareVersion;
    }
    else
    {
        m_sNewestSoftWareVer = _T("");
    }
    m_sHardVer = m_struFiberConvertBasic.struFuncCardInfo[iIndex].byHardwareVersion;
    m_dwFuncSlots = m_struFiberConvertBasic.struFuncCardInfo[iIndex].bySlotNums;
    m_comboFuncStruType.SetCurSel(m_struFiberConvertBasic.struFuncCardInfo[iIndex].byStructureType - 1);

    UpdateData(FALSE);
    m_comboFuncPortIndex.SetCurSel(0);
    OnSelchangeComboFuncPortindex();
}

void CDlgFibreDev::SelchangeComboRemoteSendCardIndex(int iIndex)
{
    m_dwFuncSlotNo = m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].byMainSlotNo;
    m_sModelName = m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].byTypeName;
    m_szSerialNo = _T("");
    m_szFuncSoftwareVer = m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].bySoftwareVersion;
    if (m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].byIsVerMismatch)
    {
        m_sNewestSoftWareVer = m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].byNewestSoftwareVersion;
    }
    else
    {
        m_sNewestSoftWareVer = _T("");
    }
    m_sHardVer = m_struFiberConvertBasic.struRemoteSendCardInfo[iIndex].byHardwareVersion;
    m_dwFuncSlots = 0;
    m_comboFuncStruType.SetCurSel(-1);

    UpdateData(FALSE);
    m_comboFuncPortIndex.SetCurSel(0);
    OnSelchangeComboFuncPortindex();
}

void CDlgFibreDev::OnSelchangeComboCaedstatIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iCardType = m_cmbCardType.GetCurSel();
	if (iCardType == CB_ERR)
	{
		return;
	}
    int iIndex = m_comboCardIndex.GetCurSel();
	if (iCardType == CB_ERR)
	{
		return;
	}
	if (iCardType == 0) //网管卡
	{
        m_bPortEnable = m_struFiberConbertState.struNetCardState.struPortState[iIndex].byPortNo;
        m_dwStatePortNo = m_struFiberConbertState.struNetCardState.struPortState[iIndex].byPortNo;
        m_comboStatusPortTye.SetCurSel(m_struFiberConbertState.struNetCardState.struPortState[iIndex].byPortType - 1);
        m_comboLinkState.SetCurSel(m_struFiberConbertState.struNetCardState.struPortState[iIndex].byLinkState);
        m_cmbPortSpeed.SetCurSel(m_struFiberConbertState.struNetCardState.struPortState[iIndex].byPortSpeed - 1);
        m_cmbDuplexMode.SetCurSel(m_struFiberConbertState.struNetCardState.struPortState[iIndex].byPortDuplexMode - 1);
        m_sPortName = m_struFiberConbertState.struNetCardState.struPortState[iIndex].byPortName;
        m_dwSendByte = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwSendBytes;
        m_dwSendByteSpeed = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwSendByteSpeed;
        m_dwSendPackets = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwSendPackets;
        m_dwSendPacketSpeed = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwSendPacketSpeed;
        m_dwRecvByte = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwRecvBytes;
        m_dwRecvByteSpeed = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwRecvByteSpeed;
        m_dwRecvPackets = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwRecvPackets;
        m_dwRecvPacketSpeed = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwRecvPacketSpeed;
        m_dwCRCPacket = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwRecvCrcErrPackets;
        m_dwLostPacker = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwRecvLostPackets;
        m_dwFragement = m_struFiberConbertState.struNetCardState.struPortState[iIndex].dwRecvFragmentPackets;
	}
	else if (iCardType == 1)//接收卡
	{
        int iPindex = m_comboFuncIndex.GetCurSel();
        if (iPindex == CB_ERR)
        {
            return;
        }
        m_bPortEnable = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].byPortNo;
        m_dwStatePortNo = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].byPortNo;
        m_comboStatusPortTye.SetCurSel(m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].byPortType - 1);
        m_comboLinkState.SetCurSel(m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].byLinkState);
        m_cmbPortSpeed.SetCurSel(m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].byPortSpeed - 1);
        m_cmbDuplexMode.SetCurSel(m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].byPortDuplexMode - 1);
        m_sPortName = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].byPortName;
        m_dwSendByte = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwSendBytes;
        m_dwSendByteSpeed = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwSendByteSpeed;
        m_dwSendPackets = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwSendPackets;
        m_dwSendPacketSpeed = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwSendPacketSpeed;
        m_dwRecvByte = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwRecvBytes;
        m_dwRecvByteSpeed = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwRecvByteSpeed;
        m_dwRecvPackets = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwRecvPackets;
        m_dwRecvPacketSpeed = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwRecvPacketSpeed;
        m_dwCRCPacket = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwRecvCrcErrPackets;
        m_dwLostPacker = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwRecvLostPackets;
        m_dwFragement = m_struFiberConbertState.struFuncCardState[iPindex].struPortState[iIndex].dwRecvFragmentPackets;
        
	}
    else if (iCardType == 2) //发送机
    {
        int iPindex = m_comboFuncIndex.GetCurSel();
        if (iPindex == CB_ERR)
        {
            return;
        }
        m_bPortEnable = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].byPortNo;
        m_dwStatePortNo = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].byPortNo;
        m_comboStatusPortTye.SetCurSel(m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].byPortType - 1);
        m_comboLinkState.SetCurSel(m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].byLinkState);
        m_cmbPortSpeed.SetCurSel(m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].byPortSpeed - 1);
        m_cmbDuplexMode.SetCurSel(m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].byPortDuplexMode - 1);
        m_sPortName = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].byPortName;
        m_dwSendByte = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwSendBytes;
        m_dwSendByteSpeed = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwSendByteSpeed;
        m_dwSendPackets = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwSendPackets;
        m_dwSendPacketSpeed = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwSendPacketSpeed;
        m_dwRecvByte = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwRecvBytes;
        m_dwRecvByteSpeed = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwRecvByteSpeed;
        m_dwRecvPackets = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwRecvPackets;
        m_dwRecvPacketSpeed = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwRecvPacketSpeed;
        m_dwCRCPacket = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwRecvCrcErrPackets;
        m_dwLostPacker = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwRecvLostPackets;
        m_dwFragement = m_struFiberConbertState.struRemoteSendCardState[iPindex].struPortState[iIndex].dwRecvFragmentPackets;
    }
    else
    {
        return;
    }

    UpdateData(FALSE);
}

void CDlgFibreDev::OnSelchangeComboFuncIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    int iCardType = m_cmbCardType.GetCurSel();
    if (iCardType == CB_ERR)
    {
        return;
    }
    int iIndex = m_comboFuncIndex.GetCurSel();
	if (iIndex == CB_ERR)
	{
		return;
	}
    if (iCardType == 0) //网管卡
    {
        return;
    }
    else if (iCardType == 1) //接收卡
    {
        m_dwStatusCardNum = m_struFiberConbertState.struFuncCardState[iIndex].byMainSlotNo;
        m_bEnable = m_struFiberConbertState.struFuncCardState[iIndex].byMainSlotNo > 0 ? TRUE : FALSE;
    }
    else if (iCardType == 2) //发送机
    {
        m_dwStatusCardNum = m_struFiberConbertState.struRemoteSendCardState[iIndex].byMainSlotNo;
        m_bEnable = m_struFiberConbertState.struRemoteSendCardState[iIndex].byMainSlotNo > 0 ? TRUE : FALSE;
    }
    else
    {
        return;
    }

	UpdateData(FALSE);
	m_comboCardIndex.SetCurSel(0);
    OnSelchangeComboCaedstatIndex();
}

void CDlgFibreDev::OnSelchangeComboCardType()
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbCardType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	if (nSel == 0) //网管卡
	{
        GetDlgItem(IDC_COMBO_FUNC_INDEX)->EnableWindow(FALSE);
        m_dwStatusCardNum = m_struFiberConbertState.struNetCardState.byMainSlotNo;
        m_bEnable = m_struFiberConbertState.struNetCardState.byMainSlotNo;
        UpdateData(FALSE);
        m_comboCardIndex.SetCurSel(0);
        OnSelchangeComboCaedstatIndex();
	}
	else if (nSel == 1 || nSel == 2) //接收卡
	{
        GetDlgItem(IDC_COMBO_FUNC_INDEX)->EnableWindow(TRUE);
        m_comboFuncIndex.SetCurSel(0);
        OnSelchangeComboFuncIndex();
	}
    else
    {
        return;
    }
}

void CDlgFibreDev::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	m_lpConfigParam = new(std::nothrow) NET_DVR_STD_CONFIG;
	if (m_lpConfigParam == NULL)
	{
		AfxMessageBox("内存分配失败");
	}
	else
	{
		m_lpFibreTopoInfo = new(std::nothrow) NET_DVR_FIBER_CONVERT_TOPOLOGY;
		if (m_lpFibreTopoInfo == NULL)
		{
			AfxMessageBox("内存分配失败");
		}
		else
		{
			memset(m_lpConfigParam, 0, sizeof(NET_DVR_STD_CONFIG));
			memset(m_lpFibreTopoInfo, 0, sizeof(NET_DVR_FIBER_CONVERT_TOPOLOGY));
			m_lpFibreTopoInfo->dwSize = sizeof(NET_DVR_FIBER_CONVERT_TOPOLOGY);
			m_lpConfigParam->lpOutBuffer = m_lpFibreTopoInfo;
			m_lpConfigParam->dwOutSize = sizeof(NET_DVR_FIBER_CONVERT_TOPOLOGY);
			if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_FIBER_CONVERT_TOPOLOGY, m_lpConfigParam))
			{
				g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetSTDConfig NET_DVR_GET_FIBER_CONVERT_TOPOLOGY");
			}
			else
			{
				g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetSTDConfig NET_DVR_GET_FIBER_CONVERT_TOPOLOGY");
				m_comboCardID.ResetContent();
				for (int nCardCnt = 0; nCardCnt < MAX_FC_CARD_NUM; nCardCnt++)
				{
					CString strCardID;
					strCardID.Format("%d", nCardCnt);
					m_comboCardID.AddString(strCardID);
				}
				m_comboCardID.SetCurSel(0);
				OnSelchangeComboFibreCardId();
			}
		}
	}
	UpdateData(FALSE);
}

void CDlgFibreDev::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CDlgFibreDev::OnCbnSelchangeComboCardtype()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_cmbType.GetCurSel() == 0) //接收卡
    {
        GetDlgItem(IDC_EDIT_FUNC_SERIALNO)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_FUNC_SLOTS)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_FUNC_STRUTYPE)->EnableWindow(TRUE);
    }
    else if (m_cmbType.GetCurSel() == 1) //发送机
    {
        GetDlgItem(IDC_EDIT_FUNC_SERIALNO)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_FUNC_SLOTS)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_FUNC_STRUTYPE)->EnableWindow(FALSE);
    }
    else
    {
        return; //未知卡类型
    }
}
