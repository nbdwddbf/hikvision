// DlgThirdGenerationCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgThirdGenerationCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThirdGenerationCfg dialog


CDlgThirdGenerationCfg::CDlgThirdGenerationCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThirdGenerationCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThirdGenerationCfg)
	m_strCmsIp = _T("");
	m_iCmsPort = 0;
	m_strPicIp = _T("");
	m_iPicPort = 0;
	m_strPsw = _T("");
	m_strPuId = _T("");
	m_bEnable3G = FALSE;
	m_strApn = _T("");
	m_strDialNum = _T("");
	m_strLocalIp = _T("");
	m_iOffLineTime = 0;
	m_strPassword = _T("");
	m_strRemoteIp = _T("");
	m_strUserName = _T("");
	m_iMtuSize = 0;
	m_bEnableSmsAlarm = FALSE;
	m_tmStartDate = 0;
	m_tmStartTime = 0;
	m_tmStopDate = 0;
	m_tmStopTime = 0;
	m_iSmsNum = 0;
	m_bPinLockEnable = FALSE;
	m_strPinCode = _T("");
	m_strPinNewCode = _T("");
	m_iRemainPinTime = 0;
	m_iRemainPukTime = 0;
	m_strSmsContent = _T("");
	m_iSmsSeq = 0;
	m_strPhoneNumber = _T("");
	m_strWireDnsIp = _T("");
	m_strWireLocalIp = _T("");
	m_strWireMaskIp = _T("");
	m_strWireRemoteIp = _T("");
	m_iStatus = 0;
	m_iUpMaxBitrate = 0;
	m_iDownMaxBitrate = 0;
	m_strDialStatus = _T("");
	m_iUdpPort = 0;
	m_bEnableAlarm = FALSE;
	m_strWhiteList = _T("");
	m_strUinPhone = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iPhoneCount = 0;
    m_iAlarmCount = 0;
	memset(&m_struCmsParam, 0, sizeof(m_struCmsParam));
	memset(&m_struDialRequest, 0, sizeof(m_struDialRequest));
	memset(&m_struDialParam, 0, sizeof(m_struDialParam));
	memset(&m_struSmsRelativeParam, 0, sizeof(m_struSmsRelativeParam));
	memset(&m_struDialStatus, 0, sizeof(m_struDialStatus));
}


void CDlgThirdGenerationCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThirdGenerationCfg)
	DDX_Control(pDX, IDC_TREE_WHITELIST, m_TreeAlarm);
	DDX_Control(pDX, IDC_COMBO_WHITELIST, m_WhiteListCtrl);
	DDX_Control(pDX, IDC_COMBO_MAX_BITDOWN, m_MaxDownBitCtrl);
	DDX_Control(pDX, IDC_COMBO_MAX_BITUP, m_MaxUpBitCtrl);
	DDX_Control(pDX, IDC_COMBO_REALMODE, m_RealModeCtrl);
	DDX_Control(pDX, IDC_COMBO_UIMINFO, m_UimInfoCtrl);
	DDX_Control(pDX, IDC_COMBO_STATUS1, m_StatusCtrl);
	DDX_Control(pDX, IDC_COMBO_PINCOMMAND, m_PinCommandCtrl);
	DDX_Control(pDX, IDC_LIST, m_SmsList);
	DDX_Control(pDX, IDC_COMBO_VERIFYPRO, m_VerifyProCtrl);
	DDX_Control(pDX, IDC_COMBO_TRAFFICCLASS, m_TrafficClassCtrl);
	DDX_Control(pDX, IDC_COMBO_SWITCHMODE, m_SwitchModeCtrl);
	DDX_Control(pDX, IDC_COMBO_NETTYPE, m_NetTypeCtrl);
	DDX_Control(pDX, IDC_COMBO_DIALMODE, m_DialModeCtrl);
	DDX_Control(pDX, IDC_COMBO_CONNNUM, m_ConnNumCtrl);
	DDX_Text(pDX, IDC_EDIT_CMSIP, m_strCmsIp);
	DDX_Text(pDX, IDC_EDIT_CMSPORT, m_iCmsPort);
	DDX_Text(pDX, IDC_EDIT_PICIP, m_strPicIp);
	DDX_Text(pDX, IDC_EDIT_PICPORT, m_iPicPort);
	DDX_Text(pDX, IDC_EDIT_PSW, m_strPsw);
	DDX_Text(pDX, IDC_EDIT_PUID, m_strPuId);
	DDX_Check(pDX, IDC_CHECK_ENABLE3G, m_bEnable3G);
	DDX_Text(pDX, IDC_EDIT_APN, m_strApn);
	DDX_Text(pDX, IDC_EDIT_DIALNUM1, m_strDialNum);
	DDX_Text(pDX, IDC_EDIT_LOCALIP, m_strLocalIp);
	DDX_Text(pDX, IDC_EDIT_OFFLINETIME, m_iOffLineTime);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_REMOTEIP, m_strRemoteIp);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_MTUSIZE, m_iMtuSize);
	DDX_Check(pDX, IDC_CHECK_ENABLESMSALARM, m_bEnableSmsAlarm);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_tmStartDate);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_tmStartTime);
	DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_tmStopDate);
	DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_tmStopTime);
	DDX_Text(pDX, IDC_EDIT_SMSNUM, m_iSmsNum);
	DDX_Check(pDX, IDC_CHECK_PINLOCKENABLE, m_bPinLockEnable);
	DDX_Text(pDX, IDC_EDIT_PINCODE, m_strPinCode);
	DDX_Text(pDX, IDC_EDIT_PINNEWCODE, m_strPinNewCode);
	DDX_Text(pDX, IDC_EDIT_REMAINPINTIME, m_iRemainPinTime);
	DDX_Text(pDX, IDC_EDIT_REMAINPUKTIME, m_iRemainPukTime);
	DDX_Text(pDX, IDC_EDIT_SMSCONTENT, m_strSmsContent);
	DDX_Text(pDX, IDC_EDIT_SMSSEQ, m_iSmsSeq);
	DDX_Text(pDX, IDC_EDIT_PHONENUMBER, m_strPhoneNumber);
	DDX_Text(pDX, IDC_EDIT_WIREDNSIP, m_strWireDnsIp);
	DDX_Text(pDX, IDC_EDIT_WIRELOCALIP, m_strWireLocalIp);
	DDX_Text(pDX, IDC_EDIT_WIREMASKIP, m_strWireMaskIp);
	DDX_Text(pDX, IDC_EDIT_WIREREMOTEIP, m_strWireRemoteIp);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_iStatus);
	DDX_Text(pDX, IDC_EDIT_UPMAXBITRATE, m_iUpMaxBitrate);
	DDX_Text(pDX, IDC_EDIT_DOWNMAXBITRATE, m_iDownMaxBitrate);
	DDX_Text(pDX, IDC_EDIT_DIALSTATUS, m_strDialStatus);
	DDX_Text(pDX, IDC_EDIT_CMSUDPPORT, m_iUdpPort);
	DDX_Check(pDX, IDC_CHECK_ENABLEALARM, m_bEnableAlarm);
	DDX_Text(pDX, IDC_EDIT_WHITELIST, m_strWhiteList);
	DDX_Text(pDX, IDC_EDIT_UIMPHONE, m_strUinPhone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgThirdGenerationCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgThirdGenerationCfg)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SETCMS, OnButtonSetcms)
	ON_BN_CLICKED(IDC_BUTTON_GETCMS, OnButtonGetcms)
	ON_BN_CLICKED(IDC_BUTTON_SETDIAL, OnButtonSetdial)
	ON_BN_CLICKED(IDC_BUTTON_GETDIAL, OnButtonGetdial)
	ON_BN_CLICKED(IDC_BUTTON_SETSMSRELATIVE, OnButtonSetsmsrelative)
	ON_BN_CLICKED(IDC_BUTTON_GETSMSRELATIVE, OnButtonGetsmsrelative)
	ON_BN_CLICKED(IDC_BUTTON_GETDIALSTATUS, OnButtonGetdialstatus)
	ON_BN_CLICKED(IDC_BUTTON_GETSMSLIST, OnButtonGetsmslist)
	ON_BN_CLICKED(IDC_BUTTON_SENDSMS, OnButtonSendsms)
	ON_BN_CLICKED(IDC_BUTTON_GETSMS, OnButtonGetsms)
	ON_BN_CLICKED(IDC_BUTTON_GETPINSTATUS, OnButtonGetpinstatus)
	ON_BN_CLICKED(IDC_BUTTON_SETPINCODE, OnButtonSetpincode)
	ON_EN_CHANGE(IDC_EDIT_SMSCONTENT, OnChangeEditSmscontent)
	ON_CBN_SELCHANGE(IDC_COMBO_WHITELIST, OnSelchangeComboWhitelist)
	ON_NOTIFY(NM_CLICK, IDC_TREE_WHITELIST, OnClickTreeWhitelist)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SURE, OnButtonSure)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThirdGenerationCfg message handlers

void CDlgThirdGenerationCfg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgThirdGenerationCfg::OnButtonSetcms() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struCmsParam.dwSize = sizeof(m_struCmsParam);
	memcpy(m_struCmsParam.byPassword, m_strPsw, PASSWD_LEN);
	memcpy(m_struCmsParam.sDeviceID, m_strPuId, NAME_LEN);

    if (strlen((const char *)m_struCmsParam.sDeviceID) > 32 || strlen((const char *)m_struCmsParam.byPassword) > 16)
    {
        MessageBox("PU ID length or password length is too long! please input again!");
        return;
    }
	memcpy(m_struCmsParam.struCmsAddr.sIpV4, m_strCmsIp, 16);
	memcpy(m_struCmsParam.struPicServerAddr.sIpV4, m_strPicIp, 16);
	m_struCmsParam.wCmsPort = m_iCmsPort;
	m_struCmsParam.wPicServerPort = m_iPicPort;
	m_struCmsParam.wCmsUdpPort = m_iUdpPort;

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CMSPARA, -1, &m_struCmsParam, sizeof(m_struCmsParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("set success!");
}

void CDlgThirdGenerationCfg::OnButtonGetcms() 
{
	// TODO: Add your control notification handler code here
	m_struCmsParam.dwSize = sizeof(m_struCmsParam);

	DWORD dwReturn = 0;
	
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CMSPARA, -1, &m_struCmsParam, sizeof(m_struCmsParam), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		//m_strPsw = m_struCmsParam.byPassword;
        char sBuf[32] = {0};
        strncpy(sBuf, (char *)m_struCmsParam.sDeviceID, NAME_LEN);
		m_strPuId = sBuf;
        strncpy(sBuf, (char *)m_struCmsParam.byPassword, NAME_LEN);
		m_strPsw = sBuf;
		m_strCmsIp = m_struCmsParam.struCmsAddr.sIpV4;
		m_strPicIp = m_struCmsParam.struPicServerAddr.sIpV4;
		m_iCmsPort = m_struCmsParam.wCmsPort;
		m_iPicPort = m_struCmsParam.wPicServerPort;
		m_iUdpPort = m_struCmsParam.wCmsUdpPort;
	}

	UpdateData(FALSE);

	MessageBox("get success!");
}

BOOL CDlgThirdGenerationCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    CString tmp;
    int i = 0;
    for (i = 0; i < MAX_WHITELIST_NUM; i++)
    {
        tmp.Format("White list %d", i + 1);
        m_WhiteListCtrl.AddString(tmp);
    }
    m_WhiteListCtrl.SetCurSel(0);

	char szLan[128] = {0};
	m_SmsList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "序号", "Seq");
    m_SmsList.InsertColumn(0, szLan, LVCFMT_LEFT, 40, -1);
    g_StringLanType(szLan, "状态", "Status");
    m_SmsList.InsertColumn(1, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "接收时间", "RecvTime");
    m_SmsList.InsertColumn(2, szLan, LVCFMT_LEFT, 130, -1);
	// TODO: Add extra initialization here
	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	m_tmStartDate = timeStart;
	m_tmStartTime= timeStart;
	m_tmStopDate = timeStop;
	m_tmStopTime = timeStop;

	m_ConnNumCtrl.SetCurSel(0);
	m_NetTypeCtrl.SetCurSel(0);
	m_PinCommandCtrl.SetCurSel(0);
	OnButtonGetsmsrelative();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgThirdGenerationCfg::OnButtonSetdial() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struDialRequest.byConnNum = m_ConnNumCtrl.GetCurSel();
	m_struDialRequest.byNetType = m_NetTypeCtrl.GetCurSel();

	m_struDialParam.bEnable3G = m_bEnable3G;
	m_struDialParam.byDialMethod = m_DialModeCtrl.GetCurSel();
	m_struDialParam.bySwitchMethod = m_SwitchModeCtrl.GetCurSel();
	m_struDialParam.wOffLineTime = m_iOffLineTime;	
    if (m_iOffLineTime > 65535 || m_iOffLineTime < 0)
    {
        MessageBox("The offline time is illegal, please input again!");
        return;
    }
	
	m_struDialParam.struQosParam.byTrafficClass = m_TrafficClassCtrl.GetCurSel();

	if (m_MaxUpBitCtrl.GetCurSel() == 11)
	{
		m_struDialParam.struQosParam.wMaxBitUL = m_iUpMaxBitrate;
		m_struDialParam.struQosParam.wMaxBitUL |= 0x8000;
	}
	else
	{
		m_struDialParam.struQosParam.wMaxBitUL = m_MaxUpBitCtrl.GetCurSel();
	}
	
	if (m_MaxDownBitCtrl.GetCurSel() == 11)
	{
		m_struDialParam.struQosParam.wMaxBitDL = m_iDownMaxBitrate;
		m_struDialParam.struQosParam.wMaxBitDL |= 0x8000;
	}
	else
	{
		m_struDialParam.struQosParam.wMaxBitDL = m_MaxDownBitCtrl.GetCurSel();
	}

	m_struDialParam.struPppdParam.byVerifyProtocal = m_VerifyProCtrl.GetCurSel();
	m_struDialParam.struPppdParam.wMtuSize = m_iMtuSize;
	memcpy(m_struDialParam.struPppdParam.byApn, m_strApn, NAME_LEN);
	memcpy(m_struDialParam.struPppdParam.byDialNum, m_strDialNum, NAME_LEN);
	memcpy(m_struDialParam.struPppdParam.byPassword, m_strPassword, DIALPASSWD_LEN);
	memcpy(m_struDialParam.struPppdParam.byUserName, m_strUserName, NAME_LEN);
	memcpy(m_struDialParam.struPppdParam.struLocalIp.sIpV4, m_strLocalIp, 16);
	memcpy(m_struDialParam.struPppdParam.struRemoteIp.sIpV4, m_strRemoteIp, 16);

    m_struDialParam.byEnaAlarmInDial = m_bEnableAlarm;

    memcpy(m_struDialParam.byUimNumber, m_strUinPhone, MAX_PHONE_NUM);

    if (strlen(m_strUinPhone) > MAX_PHONE_NUM || strlen(m_strApn) > NAME_LEN || strlen(m_strDialNum) > NAME_LEN \
        , strlen(m_strPassword) > DIALPASSWD_LEN || strlen(m_strUserName) > NAME_LEN)
    {
        MessageBox("The Apn's Length, DialNum's Length, Password's Length, Username's Length is too long, please input again!");
        return;
    }
	m_struDialParam.dwSize = sizeof(m_struDialParam);
	if (!NET_DVR_SetDialParam(m_lServerID, &m_struDialRequest, &m_struDialParam))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	
	MessageBox("set success!");
}

void CDlgThirdGenerationCfg::OnButtonGetdial() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struDialRequest.byConnNum = m_ConnNumCtrl.GetCurSel();
	m_struDialRequest.byNetType = m_NetTypeCtrl.GetCurSel();	
	
	if (!NET_DVR_GetDialParam(m_lServerID, &m_struDialRequest, &m_struDialParam))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	m_bEnable3G = m_struDialParam.bEnable3G;
	m_DialModeCtrl.SetCurSel(m_struDialParam.byDialMethod);
	m_SwitchModeCtrl.SetCurSel(m_struDialParam.bySwitchMethod);
	m_iOffLineTime = m_struDialParam.wOffLineTime;	
	
	m_TrafficClassCtrl.SetCurSel(m_struDialParam.struQosParam.byTrafficClass);

	if ((m_struDialParam.struQosParam.wMaxBitDL >> 15) & 0x01)
    {
        m_MaxDownBitCtrl.SetCurSel(11);		
        m_iDownMaxBitrate = (m_struDialParam.struQosParam.wMaxBitDL & 0x7fff)/* / 1024*/;
    }
    else
    {
        m_MaxDownBitCtrl.SetCurSel(m_struDialParam.struQosParam.wMaxBitDL);;			
        m_iUpMaxBitrate = 0;
    }

	if ((m_struDialParam.struQosParam.wMaxBitUL >> 15) & 0x01)
    {
        m_MaxUpBitCtrl.SetCurSel(11);		
        m_iUpMaxBitrate = (m_struDialParam.struQosParam.wMaxBitUL & 0x7fff)/* / 1024*/;
    }
    else
    {
        m_MaxUpBitCtrl.SetCurSel(m_struDialParam.struQosParam.wMaxBitUL);;			
        m_iDownMaxBitrate = 0;
    }
	
	m_VerifyProCtrl.SetCurSel(m_struDialParam.struPppdParam.byVerifyProtocal);
	m_iMtuSize = m_struDialParam.struPppdParam.wMtuSize;
	m_strApn = m_struDialParam.struPppdParam.byApn;
	m_strDialNum = m_struDialParam.struPppdParam.byDialNum;
	m_strPassword = m_struDialParam.struPppdParam.byPassword;
	m_strUserName = m_struDialParam.struPppdParam.byUserName;
	m_strLocalIp = m_struDialParam.struPppdParam.struLocalIp.sIpV4;
	m_strRemoteIp = m_struDialParam.struPppdParam.struRemoteIp.sIpV4;
    m_bEnableAlarm = m_struDialParam.byEnaAlarmInDial;
    m_strUinPhone = m_struDialParam.byUimNumber;
	
	UpdateData(FALSE);
	
	MessageBox("get success!");
}

void CDlgThirdGenerationCfg::OnButtonSetsmsrelative() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struSmsRelativeParam.dwSize = sizeof(m_struSmsRelativeParam);
	m_struSmsRelativeParam.bEnableSmsAlarm = m_bEnableSmsAlarm;

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SMSRELATIVEPARA_V50, -1, &m_struSmsRelativeParam, sizeof(m_struSmsRelativeParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("set success!");
}

void CDlgThirdGenerationCfg::GetAlarmCount()
{
    m_iAlarmCount = 31;
    m_iPhoneCount = 4;
//     int sel = m_WhiteListCtrl.GetCurSel();
//     for (int i = 0; i<32; i++)
//     {
//         if (0 != m_struSmsRelativeParam.struWhiteList[sel].byAlarmHandler[i])
//         {
//             m_iAlarmCount++;
//         }       
//     }
//     
//     for (i = 0; i<32; i++)
//     {
//         if (0 != m_struSmsRelativeParam.struWhiteList[sel].byPhonePerssion[i])
//         {
//             m_iPhoneCount++;
//         }       
//     }
}

void CDlgThirdGenerationCfg::OnButtonGetsmsrelative() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int sel = m_WhiteListCtrl.GetCurSel();

	DWORD dwReturn = 0;
    memset(&m_struSmsRelativeParam, 0, sizeof(m_struSmsRelativeParam));
    m_struSmsRelativeParam.dwSize = sizeof(m_struSmsRelativeParam);

	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SMSRELATIVEPARA_V50, -1, &m_struSmsRelativeParam, sizeof(m_struSmsRelativeParam), &dwReturn))
	{
		char szLan[16] = {0};
		sprintf(szLan, "Errcode: %d", NET_DVR_GetLastError());
		MessageBox(szLan);
		//MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	m_bEnableSmsAlarm = m_struSmsRelativeParam.bEnableSmsAlarm;
    m_strWhiteList = m_struSmsRelativeParam.struWhiteList[sel].byWhiteList;

    GetAlarmCount();
	UpdateData(FALSE);
    CreateTree();
	MessageBox("get success!");
}

void CDlgThirdGenerationCfg::OnButtonGetdialstatus() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DIALSTATUS, -1, &m_struDialStatus, sizeof(m_struDialStatus), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	m_strWireLocalIp = m_struDialStatus.struLocalIp.sIpV4;
	m_strWireRemoteIp = m_struDialStatus.struRemoteIp.sIpV4;
	m_strWireDnsIp = m_struDialStatus.struDns.sIpV4;
	m_strWireMaskIp = m_struDialStatus.struNetMask.sIpV4;

    m_iStatus = m_struDialStatus.dwSignal;
	CString tmp;
	tmp.Format("0x%x", m_struDialStatus.dwDialStatus);
    m_strDialStatus = tmp;
	int iMode = m_struDialStatus.byRealMode;
	switch(iMode)
	{
	case 12:
		m_RealModeCtrl.SetCurSel(0);
		break;
	case 14:
		m_RealModeCtrl.SetCurSel(1);
		break;
	case 18:
		m_RealModeCtrl.SetCurSel(2);
		break;
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
		m_RealModeCtrl.SetCurSel(iMode - 18);
		break;
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
		m_RealModeCtrl.SetCurSel(iMode - 21);
		break;
	default:
		m_RealModeCtrl.SetCurSel(-1);
		break;
	}

	switch(m_struDialStatus.byUimCard)
	{
	case 0:
	case 1:
		m_UimInfoCtrl.SetCurSel(m_struDialStatus.byUimCard);
		break;
	case 4:
		m_UimInfoCtrl.SetCurSel(2);
		break;
	case 11:
		m_UimInfoCtrl.SetCurSel(3);
		break;
	case 255:
		m_UimInfoCtrl.SetCurSel(4);
		break;
	default:
		m_UimInfoCtrl.SetCurSel(-1);
		break;
	}
	UpdateData(FALSE);
	MessageBox("get success!");
}

void CDlgThirdGenerationCfg::OnButtonGetsmslist() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_TIME_EX struStartTime = {0};
	struStartTime.byDay = m_tmStartDate.GetDay();
	struStartTime.byHour = m_tmStartTime.GetHour();
	struStartTime.byMinute = m_tmStartTime.GetMinute();
	struStartTime.byMonth = m_tmStartDate.GetMonth();
	struStartTime.wYear = m_tmStartDate.GetYear();
	struStartTime.bySecond = m_tmStartTime.GetSecond();

	NET_DVR_TIME_EX struStopTime = {0};
	struStopTime.byDay = m_tmStopDate.GetDay();
	struStopTime.byHour = m_tmStopTime.GetHour();
	struStopTime.byMinute = m_tmStopTime.GetMinute();
	struStopTime.byMonth = m_tmStopDate.GetMonth();
	struStopTime.wYear = m_tmStopDate.GetYear();
	struStopTime.bySecond = m_tmStopTime.GetSecond();

	NET_DVR_SMSLISTINFO struSmsListInfo = {0};
	struSmsListInfo.pSmsParam = new BYTE[10 * COMMANDLEN];
	if (struSmsListInfo.pSmsParam == NULL)
	{
		return;
	}
	
	memset(struSmsListInfo.pSmsParam, 0, 10 * COMMANDLEN);
	struSmsListInfo.dwBufLen = 10 * COMMANDLEN;
	
	if (!NET_DVR_GetSmsListInfo(m_lServerID, &struStartTime, &struStopTime, &struSmsListInfo))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	NET_DVR_SMSPARAM struSmsParam = {0};
	m_iSmsNum = struSmsListInfo.dwTotalSmsNum;
	int i = 0;
	CString tmp;
	m_SmsList.DeleteAllItems();
	for (i = 0; i < m_iSmsNum; i ++)
	{
		memcpy(&struSmsParam, struSmsListInfo.pSmsParam + i * sizeof(struSmsParam), sizeof(struSmsParam));
		tmp.Empty();
		tmp.Format("%d", struSmsParam.dwIndex);
		m_SmsList.InsertItem(i, tmp, 0);
		
		tmp.Empty();
		if (struSmsParam.byStatus == 0)
		{
			tmp = "not ready";
		}
		else
		{
			tmp = "ready yet";
		}
		m_SmsList.SetItemText(i, 1, tmp);

		tmp.Empty();
		tmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struSmsParam.struRecvTime.wYear, struSmsParam.struRecvTime.byMonth , 
										struSmsParam.struRecvTime.byDay, struSmsParam.struRecvTime.byHour ,
										struSmsParam.struRecvTime.byMinute, struSmsParam.struRecvTime.bySecond);
		m_SmsList.SetItemText(i, 2, tmp);
	}

	if (NULL != struSmsListInfo.pSmsParam)
	{
		delete []struSmsListInfo.pSmsParam;
		struSmsListInfo.pSmsParam = NULL;
	}

	UpdateData(FALSE);
}

void CDlgThirdGenerationCfg::OnButtonSendsms() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[16] = {0};
	NET_DVR_SMSCONTENT struSmsContent = {0};
	memcpy(struSmsContent.byPhoneNum, m_strPhoneNumber, MAX_PHONE_NUM);
	memcpy(struSmsContent.byMsg, m_strSmsContent, 140);

	if (!NET_DVR_SendSms(m_lServerID, &struSmsContent))
	{
		sprintf(szLan, "Errcode: %d", NET_DVR_GetLastError());
		//MessageBox(NET_DVR_GetErrorMsg());
		MessageBox(szLan);
		return;
	}

	MessageBox("send sms success!");
}

void CDlgThirdGenerationCfg::OnButtonGetsms() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_SMSCONTENT struSmsContent = {0};
	if (!NET_DVR_GetSmsContent(m_lServerID, m_iSmsSeq, &struSmsContent))
	{
		char szLan[16] = {0};
		sprintf(szLan, "Errcode: %d", NET_DVR_GetLastError());
		MessageBox(szLan);
		//MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	m_strPhoneNumber = struSmsContent.byPhoneNum;
    m_strSmsContent = struSmsContent.byMsg;
	
	MessageBox("get sms success!");
	UpdateData(FALSE);
}

void CDlgThirdGenerationCfg::OnButtonGetpinstatus() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_PINSTATUS struPinStatus = {0};
	struPinStatus.dwSize = sizeof(struPinStatus);
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PINSTATUS, -1, &struPinStatus, sizeof(struPinStatus), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	m_StatusCtrl.SetCurSel(struPinStatus.byStatus - 1);
	m_iRemainPinTime = struPinStatus.byPinTimes;
	m_iRemainPukTime = struPinStatus.byPukTimes;
	m_bPinLockEnable = struPinStatus.bEnableLock;
	MessageBox("get success!");
	UpdateData(FALSE);
}

void CDlgThirdGenerationCfg::OnButtonSetpincode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_PINCODEPARAM struPinCodeParam = {0};
	struPinCodeParam.byPinCmd = m_PinCommandCtrl.GetCurSel() + 1;
	memcpy(struPinCodeParam.byPinCode, m_strPinCode, 8);
	memcpy(struPinCodeParam.byNewPinCode, m_strPinNewCode, 8);
	struPinCodeParam.dwSize = sizeof(struPinCodeParam);

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PINCMD, -1, &struPinCodeParam, sizeof(struPinCodeParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	MessageBox("set success!");
}


void CDlgThirdGenerationCfg::OnChangeEditSmscontent() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}

void CDlgThirdGenerationCfg::OnSelchangeComboWhitelist() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int sel = m_WhiteListCtrl.GetCurSel();

    m_strWhiteList = m_struSmsRelativeParam.struWhiteList[sel].byWhiteList;

    UpdateData(FALSE);
    CreateTree();
}

void CDlgThirdGenerationCfg::OnClickTreeWhitelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
    UpdateData(TRUE);
    int sel = m_WhiteListCtrl.GetCurSel();
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    GetDlgItem(IDC_TREE_WHITELIST)->GetWindowRect(&rc);
    ScreenToClient(&rc);
    ScreenToClient(&pt);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;

    UINT uFlag = 0;
    HTREEITEM hSelect = m_TreeAlarm.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_TreeAlarm.SelectItem(hSelect);
    DWORD dwIndex = m_TreeAlarm.GetItemData(hSelect)%1000;
    BOOL bCheck = m_TreeAlarm.GetCheck(hSelect);
    if (dwIndex < m_iAlarmCount)
    {
        m_struSmsRelativeParam.struWhiteList[sel].byAlarmHandler[dwIndex] = !bCheck;
    }
    else
    {
        m_struSmsRelativeParam.struWhiteList[sel].byPhonePerssion[dwIndex - m_iAlarmCount] = !bCheck;
    }
    
    if (uFlag != LVHT_TOLEFT)
    {
        m_TreeAlarm.SetCheck(hSelect, !bCheck);
    }
    else
    {
        m_TreeAlarm.SetCheck(hSelect, bCheck);
    }
    
	*pResult = 0;
}

void CDlgThirdGenerationCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    CreateTree();
	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}
/*********************************************************
Function:	CreateTree
Desc:		Create connection between alarm output-channel 
Input:	
Output:	
Return:	
**********************************************************/
void CDlgThirdGenerationCfg::CreateTree(void)
{	
	UpdateData(TRUE);
    int sel = m_WhiteListCtrl.GetCurSel();
	m_TreeAlarm.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
    HTREEITEM hItem = NULL;
    
    for (; i < m_iAlarmCount+m_iPhoneCount; i++)
    {
        strTemp.Format(sAlarmstring[i]);
        hItem =  m_TreeAlarm.InsertItem(strTemp, TVI_ROOT);
        m_TreeAlarm.SetItemData(hItem, 1*1000 + i);	
        if (i < m_iAlarmCount)
        { 
            if (m_struSmsRelativeParam.struWhiteList[sel].byAlarmHandler[i] == 1)
            {
                m_TreeAlarm.SetCheck(hItem, TRUE);
            }
        }
        else
        {
            if (m_struSmsRelativeParam.struWhiteList[sel].byPhonePerssion[i - m_iAlarmCount] == 1)
            {
                m_TreeAlarm.SetCheck(hItem, TRUE);
            }
        }

    }

    m_TreeAlarm.Expand(m_TreeAlarm.GetRootItem(),TVE_EXPAND);	

	UpdateData(FALSE);
}

void CDlgThirdGenerationCfg::OnButtonSure() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_WhiteListCtrl.GetCurSel();
	memcpy(m_struSmsRelativeParam.struWhiteList[i].byWhiteList, m_strWhiteList, MAX_PHONE_NUM);
}
