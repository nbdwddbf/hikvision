/**********************************************************
FileName:    SubDlgATMInfoCfg.cpp
Description: ATM configuration      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgATMInfoCfg.h"
#include ".\subdlgatminfocfg.h"


// CSubDlgATMInfoCfg dialog
/*********************************************************
  Function:	CSubDlgATMInfoCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgATMInfoCfg, CDialog)
CSubDlgATMInfoCfg::CSubDlgATMInfoCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgATMInfoCfg::IDD, pParent)
	, m_csATMIP(_T(""))
	, m_iATMPort(0)
	, m_dwMsgStartPos(0)
	, m_csAcceptBusTypeCode(_T(""))
	, m_dwMsgLen(0)
	, m_csMsgInfo(_T(""))
	, m_dwCardLenInfoStart(0)
	, m_dwCardLenInfoLen(0)
	, m_dwCardNumInfoStart(0)
	, m_dwCardNumInfoLen(0)
	, m_dwBusinessStart(0)
	, m_dwBusinessLen(0)
	, m_csListenBusTypeCode(_T(""))
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_bNewPort(FALSE)
	, m_iInputMode(NET_LISTEN)
	, m_iFrameType(0)
	, m_nATMPort(0)
	, m_bSetPara(FALSE)
	, m_wCardAtmPort(0)
{
	memset(&m_struATMInfo, 0, sizeof(m_struATMInfo));
}

/*********************************************************
  Function:	~CSubDlgATMInfoCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgATMInfoCfg::~CSubDlgATMInfoCfg()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgATMInfoCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgATMInfoCfg)
	DDX_Control(pDX, IDC_COMBO_INPUT_TYPE, m_comboInputType);
	DDX_Text(pDX, IDC_EDIT_ATMIP, m_csATMIP);
	DDX_Control(pDX, IDC_COMBO_ATM_TYPE2, m_comboATMType2);
	DDX_Control(pDX, IDC_COMBO_ATM_TYPE, m_comboATMType);
	DDX_Text(pDX, IDC_EDIT_ATM_PORT, m_iATMPort);
	DDX_Text(pDX, IDC_EDIT_MSG_START, m_dwMsgStartPos);
	DDX_Control(pDX, IDC_COMBO_ACCEPT_FRAME_TYPE, m_comboAcceptFrameType);
	DDX_Text(pDX, IDC_EDIT_ACCEPT_BUSINESS_CODE, m_csAcceptBusTypeCode);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_LEN, m_dwMsgLen);
	DDX_Text(pDX, IDC_EDIT_MSG_INFO, m_csMsgInfo);
	DDX_Text(pDX, IDC_EDIT_CARD_NUM_LEN_INFO_START, m_dwCardLenInfoStart);
	DDX_Text(pDX, IDC_EDIT_CARD_NUM_LEN_INFO_LEN, m_dwCardLenInfoLen);
	DDX_Text(pDX, IDC_EDIT_CARD_NUM_INFO_START, m_dwCardNumInfoStart);
	DDX_Text(pDX, IDC_EDIT_CARD_NUM_INFO_LEN, m_dwCardNumInfoLen);
	DDX_Text(pDX, IDC_EDIT_BUSINESS_START, m_dwBusinessStart);
	DDX_Text(pDX, IDC_EDIT_BUSINESS_LEN, m_dwBusinessLen);
	DDX_Control(pDX, IDC_COMBO_LISTEN_FRAME_TYPE, m_comboListenFrameType);
	DDX_Text(pDX, IDC_EDIT_LISTEN_BUSINESS_CODE, m_csListenBusTypeCode);
	DDX_Text(pDX, IDC_EDIT_CARD_CATCH_ATM_PORT, m_wCardAtmPort);
	DDX_Control(pDX, IDC_COMBO_PROTO_TYPE, m_comboProtoType);
        //}}AFX_DATA_MAP
	
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgATMInfoCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgATMInfoCfg)	
	ON_BN_CLICKED(ID_BTN_ATM_OK, OnBnClickedBtnAtmOk)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUT_TYPE, OnCbnSelchangeComboInputType)
	ON_CBN_SELCHANGE(IDC_COMBO_LISTEN_FRAME_TYPE, OnCbnSelchangeComboListenFrameType)
	ON_CBN_SELCHANGE(IDC_COMBO_ACCEPT_FRAME_TYPE, OnCbnSelchangeComboAcceptFrameType)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CSubDlgATMInfoCfg message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CSubDlgATMInfoCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	EnableControl(m_iInputMode, m_bNewPort);
	return TRUE;
}

/*********************************************************
Function:	CheckInitParam
Desc:		check and update device parameters
Input:	
Output:	
Return:	TRUE,cheking correct and update theparameters;FALSE,not update
**********************************************************/
BOOL CSubDlgATMInfoCfg::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	if (iDeviceIndex == -1)
	{
		return FALSE;
	}

// 	if (g_pMainDlg->IsCurDevMatDec(iDeviceIndex))
// 	{
// 		return FALSE;
// 	}
	if (m_iDeviceIndex == iDeviceIndex)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	}
	m_bSetPara = FALSE;
	m_iInputMode = 0;
	m_iFrameType = 0;
	m_comboInputType.SetCurSel(-1);
	m_csATMIP = _T("");
	m_comboATMType2.SetCurSel(-1);
	m_comboATMType.SetCurSel(-1);
	m_iATMPort = 0;
	m_dwMsgStartPos = 0;
	m_comboAcceptFrameType.SetCurSel(-1);
	m_csAcceptBusTypeCode = _T("");
	m_dwMsgLen = 0;
	m_csMsgInfo = _T("");
	m_dwCardLenInfoStart = 0;
	m_dwCardLenInfoLen = 0;
	m_dwCardNumInfoStart = 0;
	m_dwCardNumInfoLen = 0;
	m_dwBusinessStart = 0;
	m_dwBusinessLen = 0;
	m_comboListenFrameType.SetCurSel(-1);
	m_csListenBusTypeCode = _T("");
	//EnableControl(m_iInputMode, m_bNewPort);
	if (m_lLoginID < 0)
	{
		return FALSE;
	}
	if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType != 90)
	{
		if (!NET_DVR_GetATMPortCFG(m_lLoginID, &m_nATMPort))
		{
			m_bNewPort = FALSE;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetATMPortCFG");
//			return FALSE;
		}
		else
		{
			m_bNewPort = TRUE;
		}
	}

	if (!NET_DVR_ClientGetframeformat(m_lLoginID, &m_struATMInfo))
	{
		
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ClientGetframeformat_V30");
		return FALSE;
	}
// 	if (m_struATMInfo.wATMPort == 0)
// 	{
// 		m_bNewPort = FALSE;
// 	}
// 	else
// 	{
// 		m_bNewPort = TRUE;
// 	}

	return TRUE;
}

/*********************************************************
Function:	CurCfgUpdate
Desc:		update device parameters and update the controls
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgATMInfoCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		UpdateData(FALSE);
		EnableWindow(FALSE);
		return;
	}
	EnableWindow(TRUE);
	
	if (m_bNewPort)
	{
		m_comboInputType.SetCurSel(m_struATMInfo.dwInputMode);
		m_comboATMType2.SetCurSel(m_struATMInfo.dwATMType);
		m_csATMIP.Format("%s", m_struATMInfo.sATMIP);
		m_comboATMType.SetCurSel(m_struATMInfo.dwATMType);
		m_comboListenFrameType.SetCurSel(m_iFrameType);
		m_csListenBusTypeCode.Format("%s", m_struATMInfo.frameTypeCode[m_iFrameType].code);
		switch (m_struATMInfo.dwInputMode)
		{
		case NET_LISTEN:
			m_iInputMode = NET_LISTEN;
			m_csATMIP.Format("%s", m_struATMInfo.sATMIP);
			m_comboATMType.SetCurSel(m_struATMInfo.dwATMType);
			m_dwMsgStartPos = m_struATMInfo.dwFrameSignBeginPos;
			m_dwMsgLen = m_struATMInfo.dwFrameSignLength;
			m_csMsgInfo.Format("%s", m_struATMInfo.byFrameSignContent);
			m_dwCardLenInfoStart = m_struATMInfo.dwCardLengthInfoBeginPos;
			m_dwCardLenInfoLen = m_struATMInfo.dwCardLengthInfoLength;
			m_dwCardNumInfoStart = m_struATMInfo.dwCardNumberInfoBeginPos;
			m_dwCardNumInfoLen = m_struATMInfo.dwCardNumberInfoLength;
			m_dwBusinessStart = m_struATMInfo.dwBusinessTypeBeginPos;
			m_dwBusinessLen = m_struATMInfo.dwBusinessTypeLength;
			m_comboListenFrameType.SetCurSel(m_iFrameType);
			m_csListenBusTypeCode.Format("%s", m_struATMInfo.frameTypeCode[m_iFrameType].code);
			break;
		case NET_ACCEPT:
			m_iATMPort = m_nATMPort;
			m_iInputMode = NET_ACCEPT;
			break;
		case SERIAL_INPUT_DIRECTLY:				
			m_iInputMode = SERIAL_INPUT_DIRECTLY;
			break;
		case SERIAL_ATM_CMD_INPUT:
			m_iInputMode = SERIAL_ATM_CMD_INPUT;
			break;
		default:
			break;
		}
	}
	else
	{
		m_comboInputType.SetCurSel(m_struATMInfo.dwInputMode);
		m_csATMIP.Format("%s", m_struATMInfo.sATMIP);
		m_comboATMType.SetCurSel(m_struATMInfo.dwATMType);
		//m_comboAcceptFrameType.SetCurSel(m_iFrameType);
		//m_csAcceptBusTypeCode.Format("%s", m_struATMInfo.frameTypeCode[m_iFrameType].code);
		switch (m_struATMInfo.dwInputMode)
		{
		case NET_LISTEN:
			m_iInputMode = NET_LISTEN;
			m_dwMsgStartPos = m_struATMInfo.dwFrameSignBeginPos;
			m_dwMsgLen = m_struATMInfo.dwFrameSignLength;
			m_csMsgInfo.Format("%s", m_struATMInfo.byFrameSignContent);
			m_dwCardLenInfoStart = m_struATMInfo.dwCardLengthInfoBeginPos;
			m_dwCardLenInfoLen = m_struATMInfo.dwCardLengthInfoLength;
			m_dwCardNumInfoStart = m_struATMInfo.dwCardNumberInfoBeginPos;
			m_dwCardNumInfoLen = m_struATMInfo.dwCardNumberInfoLength;
			m_dwBusinessStart = m_struATMInfo.dwBusinessTypeBeginPos;
			m_dwBusinessLen = m_struATMInfo.dwBusinessTypeLength;
			m_comboListenFrameType.SetCurSel(m_iFrameType);
			m_csListenBusTypeCode.Format("%s", m_struATMInfo.frameTypeCode[m_iFrameType].code);
			break;
		case NET_ACCEPT:
		case SERIAL_INPUT_DIRECTLY:
		case SERIAL_ATM_CMD_INPUT:
			m_iInputMode = NET_ACCEPT;
			m_comboAcceptFrameType.SetCurSel(m_iFrameType);
			m_csAcceptBusTypeCode.Format("%s", m_struATMInfo.frameTypeCode[m_iFrameType].code);
			break;
		default:
			break;
		}
	}
	EnableControl(m_iInputMode, m_bNewPort);

	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnAtmOk
  Desc:		confirm ATM configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgATMInfoCfg::OnBnClickedBtnAtmOk()
{
	UpdateData(TRUE);

	if (m_bNewPort)
	{
		m_struATMInfo.dwInputMode = m_comboInputType.GetCurSel();

		switch (m_struATMInfo.dwInputMode)
		{
		case NET_LISTEN:
			memcpy(m_struATMInfo.sATMIP, m_csATMIP,16);
			m_struATMInfo.dwATMType = m_comboATMType.GetCurSel();
			m_struATMInfo.dwFrameSignBeginPos = m_dwMsgStartPos;
			m_struATMInfo.dwFrameSignLength = m_dwMsgLen;
			memcpy(m_struATMInfo.byFrameSignContent,m_csMsgInfo,12);
			m_struATMInfo.dwCardLengthInfoBeginPos = m_dwCardLenInfoStart;
			m_struATMInfo.dwCardLengthInfoLength = m_dwCardLenInfoLen;
			m_struATMInfo.dwCardNumberInfoBeginPos = m_dwCardNumInfoStart;
			m_struATMInfo.dwCardNumberInfoLength = m_dwCardNumInfoLen;
			m_struATMInfo.dwBusinessTypeBeginPos = m_dwBusinessStart;
			m_struATMInfo.dwBusinessTypeLength = m_dwBusinessLen;
			memcpy(m_struATMInfo.frameTypeCode[m_iFrameType].code,m_csListenBusTypeCode,12);
			break;
		case NET_ACCEPT:
			m_nATMPort = (WORD)m_iATMPort;
			break;
		case SERIAL_INPUT_DIRECTLY:
			m_struATMInfo.dwATMType = m_comboATMType2.GetCurSel();
			break;
		case SERIAL_ATM_CMD_INPUT:
			break;
		default:
			break;
		}

	}
	else
	{
		m_struATMInfo.dwInputMode = m_comboInputType.GetCurSel();
		memcpy(m_struATMInfo.sATMIP,m_csATMIP,16);
		m_struATMInfo.dwATMType = m_comboATMType.GetCurSel();
		if (m_struATMInfo.dwInputMode == NET_LISTEN)
		{
			m_struATMInfo.dwFrameSignBeginPos = m_dwMsgStartPos;
			m_struATMInfo.dwFrameSignLength = m_dwMsgLen;
			memcpy(m_struATMInfo.byFrameSignContent,m_csMsgInfo,12);
			m_struATMInfo.dwCardLengthInfoBeginPos = m_dwCardLenInfoStart;
			m_struATMInfo.dwCardLengthInfoLength = m_dwCardLenInfoLen;
			m_struATMInfo.dwCardNumberInfoBeginPos = m_dwCardNumInfoStart;
			m_struATMInfo.dwCardNumberInfoLength = m_dwCardNumInfoLen;
			m_struATMInfo.dwBusinessTypeBeginPos = m_dwBusinessStart;
			m_struATMInfo.dwBusinessTypeLength = m_dwBusinessLen;
			memcpy(m_struATMInfo.frameTypeCode[m_iFrameType].code,m_csListenBusTypeCode,12);
		}
		else
		{
			memcpy(m_struATMInfo.frameTypeCode[m_iFrameType].code,m_csAcceptBusTypeCode,12);
		}	
	}
	m_bSetPara = TRUE;
	g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();  
}

/*********************************************************
Function:	CfgSetup
Desc:		Set ATM parameters
Input:	
Output:	
Return:	TRUE,setting succeeds;FALSE,setting fails;
**********************************************************/
BOOL CSubDlgATMInfoCfg::CfgSetup()
{
	CString sTemp;
	char szLan[128] = {0};
	if (m_bSetPara)
	{
		if (!NET_DVR_ClientSetframeformat(m_lLoginID, &(m_struATMInfo)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ClientSetframeformat"); 

			g_StringLanType(szLan, "参数保存失败", "Save failed");
			AfxMessageBox(szLan);	
			return FALSE;		
		}

		if (m_struATMInfo.dwInputMode == NET_ACCEPT)
		{
// 			if (!NET_DVR_SetATMPortCFG(m_lLoginID, m_nATMPort))
// 			{
// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetATMPortCFG");
// 				g_StringLanType(szLan, "参数保存失败", "Save failed");
// 				AfxMessageBox(szLan);		
// 				return FALSE;
// 			}
		}

		m_bSetPara = FALSE;
	}
	g_bMustReboot = TRUE;
	return TRUE;
}

/*********************************************************
  Function:	OnCbnSelchangeComboInputType
  Desc:		atm info input type
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgATMInfoCfg::OnCbnSelchangeComboInputType()
{
	UpdateData(TRUE);

	switch (m_comboInputType.GetCurSel())
	{
	case 0:
		m_iInputMode = 0;
		break;
	case 1:
		m_iInputMode = 1;
		break;
	case 2:
		m_iInputMode = 2;
		break;
	case 3:
		m_iInputMode = 3;
		break;
	default:
		break;
	}

	EnableControl(m_iInputMode, m_bNewPort);
}

/*********************************************************
  Function:	OnCbnSelchangeComboListenFrameType
  Desc:		listen type
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgATMInfoCfg::OnCbnSelchangeComboListenFrameType()
{
	UpdateData(TRUE);
	memcpy(m_struATMInfo.frameTypeCode[m_iFrameType].code,m_csListenBusTypeCode,12);
	m_iFrameType = m_comboListenFrameType.GetCurSel();
	m_csListenBusTypeCode.Format("%s", m_struATMInfo.frameTypeCode[m_iFrameType].code);

	UpdateData(FALSE);
}

/*********************************************************
  Function:	EnableControl
  Desc:		update control according to the input mode
  Input:	iInputMode,input mode;bNewPort,whether to use other ports
  Output:	
  Return:	
**********************************************************/
void CSubDlgATMInfoCfg::EnableControl(int iInputMode, BOOL bNewPort)
{
	char szLan[128] = {0};
	if (bNewPort)
	{
		GetDlgItem(IDC_COMBO_ACCEPT_FRAME_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ACCEPT_BUSINESS_CODE)->ShowWindow(SW_HIDE);
		if (iInputMode == NET_LISTEN)
		{	
			GetDlgItem(IDC_EDIT_ATMIP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_ATM_PORT)->ShowWindow(SW_HIDE);	
			GetDlgItem(IDC_COMBO_ATM_TYPE2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_ATM_TYPE)->ShowWindow(SW_SHOW);		
			GetDlgItem(IDC_STATIC_ATM_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_ATM_IP)->ShowWindow(SW_SHOW);	
			g_StringLanType(szLan, "ATM IP地址", "ATM IP Address");
			GetDlgItem(IDC_STATIC_ATM_IP)->SetWindowText(szLan);
			g_StringLanType(szLan, "报文标志位", "Frame ID");
			GetDlgItem(IDC_STATIC_MSG_INFO_ALL)->SetWindowText(szLan);
			g_StringLanType(szLan, "起始位置", "Start Position");
			GetDlgItem(IDC_STATIC_MSG_INFO_START)->SetWindowText(szLan);
			g_StringLanType(szLan, "长度", "Length");
			GetDlgItem(IDC_STATIC_MSG_INFO_LEN)->SetWindowText(szLan);
			GetDlgItem(IDC_STATIC_MSG_INFO_ALL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_MSG_INFO_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_MSG_INFO_LEN)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_EDIT_MESSAGE_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_MSG_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_MSG_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_MSG_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_LEN_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_LEN_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_LEN_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_NUM_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_NUM_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_NUM_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_BUSINESS_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_BUSINESS_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_BUSINESS_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LISTEN_CODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LISTEN_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_BUSINESS_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_BUSINESS_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_LISTEN_FRAME_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LISTEN_BUSINESS_CODE)->ShowWindow(SW_SHOW);
		}
		else if (iInputMode == NET_ACCEPT)
		{
			GetDlgItem(IDC_EDIT_ATMIP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ATM_PORT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_ATM_TYPE2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_ATM_TYPE)->ShowWindow(SW_HIDE);		
			GetDlgItem(IDC_STATIC_ATM_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ATM_IP)->ShowWindow(SW_SHOW);	
			g_StringLanType(szLan, "本地端口", "Local Port");
			GetDlgItem(IDC_STATIC_ATM_IP)->SetWindowText(szLan);

			GetDlgItem(IDC_STATIC_MSG_INFO_ALL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MESSAGE_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_CODE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_LISTEN_FRAME_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_LISTEN_BUSINESS_CODE)->ShowWindow(SW_HIDE);
		}
		else if (iInputMode == SERIAL_INPUT_DIRECTLY)
		{	
			GetDlgItem(IDC_EDIT_ATMIP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ATM_PORT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_ATM_TYPE2)->ShowWindow(SW_SHOW);	
			GetDlgItem(IDC_COMBO_ATM_TYPE)->ShowWindow(SW_HIDE);		
			GetDlgItem(IDC_STATIC_ATM_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ATM_IP)->ShowWindow(SW_SHOW);	
			g_StringLanType(szLan, "ATM类型", "ATM Type");
			GetDlgItem(IDC_STATIC_ATM_IP)->SetWindowText("ATM类型");

			GetDlgItem(IDC_STATIC_MSG_INFO_ALL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MESSAGE_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_CODE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_LISTEN_FRAME_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_LISTEN_BUSINESS_CODE)->ShowWindow(SW_HIDE);
		}
		else if (iInputMode == SERIAL_ATM_CMD_INPUT)
		{
			GetDlgItem(IDC_EDIT_ATMIP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ATM_PORT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_ATM_TYPE2)->ShowWindow(SW_HIDE);	
			GetDlgItem(IDC_COMBO_ATM_TYPE)->ShowWindow(SW_HIDE);		
			GetDlgItem(IDC_STATIC_ATM_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ATM_IP)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_MSG_INFO_ALL)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MESSAGE_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_CODE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_LISTEN_FRAME_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_LISTEN_BUSINESS_CODE)->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		GetDlgItem(IDC_EDIT_ATM_PORT)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_COMBO_ATM_TYPE2)->ShowWindow(SW_HIDE);
		if (iInputMode == NET_LISTEN)
		{
			g_StringLanType(szLan, "报文标志位", "Frame ID");
			GetDlgItem(IDC_STATIC_MSG_INFO_ALL)->SetWindowText(szLan);
			g_StringLanType(szLan, "起始位置", "Start Position");
			GetDlgItem(IDC_STATIC_MSG_INFO_START)->SetWindowText(szLan);
			g_StringLanType(szLan, "长度", "Length");
			GetDlgItem(IDC_STATIC_MSG_INFO_LEN)->SetWindowText(szLan);
			GetDlgItem(IDC_COMBO_ACCEPT_FRAME_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ACCEPT_BUSINESS_CODE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MESSAGE_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_MSG_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_MSG_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_MSG_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_LEN_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_LEN_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_LEN_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_NUM_INFO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_NUM_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_CARD_NUM_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_BUSINESS_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_BUSINESS_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_BUSINESS_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LISTEN_CODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LISTEN_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_BUSINESS_START)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_BUSINESS_LEN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_LISTEN_FRAME_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LISTEN_BUSINESS_CODE)->ShowWindow(SW_SHOW);
		}
		else
		{
			g_StringLanType(szLan, "交易类型", "Trade Type");
			GetDlgItem(IDC_STATIC_MSG_INFO_ALL)->SetWindowText(szLan);
			g_StringLanType(szLan, "类型", "Type");
			GetDlgItem(IDC_STATIC_MSG_INFO_START)->SetWindowText(szLan);
			g_StringLanType(szLan, "代码", "Code");
			GetDlgItem(IDC_STATIC_MSG_INFO_LEN)->SetWindowText(szLan);
			GetDlgItem(IDC_COMBO_ACCEPT_FRAME_TYPE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_ACCEPT_BUSINESS_CODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_MESSAGE_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_MSG_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_LEN_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_INFO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_CARD_NUM_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_CODE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LISTEN_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_LEN_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_CARD_NUM_INFO_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_START)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_BUSINESS_LEN)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_LISTEN_FRAME_TYPE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_LISTEN_BUSINESS_CODE)->ShowWindow(SW_HIDE);
		}
	}

}
/*********************************************************
  Function:	OnCbnSelchangeComboAcceptFrameType
  Desc:		switch listen mode and refresh the control
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgATMInfoCfg::OnCbnSelchangeComboAcceptFrameType()
{
	UpdateData(TRUE);
	memcpy(m_struATMInfo.frameTypeCode[m_iFrameType].code,m_csAcceptBusTypeCode,12);
	m_iFrameType = m_comboAcceptFrameType.GetCurSel();
	m_csAcceptBusTypeCode.Format("%s", m_struATMInfo.frameTypeCode[m_iFrameType].code);

	UpdateData(FALSE);
}
