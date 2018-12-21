/**********************************************************
FileName:    DlgAddDevice.cpp
Description: add device    
Date:        2008/05/17
Note: 		<global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAddDevice.h"
#include ".\dlgadddevice.h"
#include "DlgAsynloginWait.h"

// CDlgAddDevice dialog
/*********************************************************
  Function:	CDlgAddDevice
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/

static int countryID[300];
static string countryName[300];
static CString appKey;
static CString appSecret;
bool m_gbAsynLogin = false;//异步登录开关
int m_giAsynLoginReturn;//异步登录状态
int m_giErrNo;//异步登录错误码
const char* m_gpErrMsg = NULL;
CDlgAsynloginWait* m_gpDlgAsynloginWait = NULL;//异步登录等待窗口

extern void CALLBACK LoginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void* pUser);
typedef struct{
	HWND m_hwnd;
	HWND mList_hwnd;
	char access_token[100];
	char domain[100];
} threadParam;
threadParam param;

typedef struct{
	CString name;
	CString serial;
	CString domain;
	CString ipAddr;
	CString port;
} deviceInfo;
deviceInfo device;

IMPLEMENT_DYNAMIC(CDlgAddDevice, CDialog)

CDlgAddDevice::CDlgAddDevice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddDevice::IDD, pParent)
	, m_csNodeName(_T(""))
	, m_nLoginPort(8000)
	, m_csUserName(_T("admin"))
	, m_csPwd(_T("abcd1234"))
	, m_iDeviceIndex(-1)
	, m_bChkGetIPByIPServer(FALSE)
	, m_csDeviceName(_T(""))
	, m_csDevSN(_T("E0120110526CCRR403594603"))
	, m_iIPServerPort(80)	
	, m_csDevAddr(_T("172.9.3.97"))
	, m_csDDNSAddr(_T("www.hiddns.com"))
{

}

/*********************************************************
  Function:	~CDlgAddDevice
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgAddDevice::~CDlgAddDevice()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAddDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddDevice)
	DDX_Text(pDX, IDC_EDIT_NODE_NAME, m_csNodeName);
	DDX_Text(pDX, IDC_DEVICE_USERNAME, m_csUserName);
	DDX_Text(pDX, IDC_DEVICE_PSW, m_csPwd);
	DDX_Check(pDX, IDC_CHK_GET_IP_BY_IPSERVER, m_bChkGetIPByIPServer);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_csDeviceName);
	DDX_Text(pDX, IDC_EDIT_ADD_DEV_SN, m_csDevSN);
	DDX_Text(pDX, IDC_IPSERVER_PORT, m_iIPServerPort);
	DDX_Text(pDX, IDC_DEVICE_PORT, m_nLoginPort);
	DDV_MinMaxInt(pDX, m_nLoginPort, 0, 65535);
	DDX_Text(pDX, IDC_DEVICE_ADDR, m_csDevAddr);
	DDV_MaxChars(pDX, m_csDevAddr, 128);
	DDX_Text(pDX, IDC_EDIT_DDNS_ADDR, m_csDDNSAddr);
	DDX_Control(pDX, IDC_COMBO_PROXY, m_cmbProxyType);
	DDX_Control(pDX, IDC_AREALIST, m_cmbAreaList);
	DDX_Control(pDX, IDC_EZVIZDEVICELIST, m_DeviceList);
    DDX_Control(pDX, IDC_COM_LOGIN_MODE, m_cmbLoginMode);
    DDX_Control(pDX, IDC_COM_HTTPS, m_cmbHttps);
    //}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	
  Output:	
  Return:	
**********************************************************/

BEGIN_MESSAGE_MAP(CDlgAddDevice, CDialog)
//{{AFX_MSG_MAP(CDlgAddDevice)
	ON_BN_CLICKED(IDC_ADD_DEVICE_OK, OnBnClickedAddDeviceOk)
	ON_BN_CLICKED(IDC_EXIT, OnBnClickedExit)
	ON_BN_CLICKED(IDC_BTN_GET_DEV_IP, OnBnClickedBtnGetDevIp)
	ON_BN_CLICKED(IDC_CHK_GET_IP_BY_IPSERVER, OnBnClickedChkGetIpByIPServer)
	ON_BN_CLICKED(IDC_ACTIVATE_DEVICE, OnActivateDevice)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_REFRESH, &CDlgAddDevice::OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_EZVIZLOGIN, &CDlgAddDevice::OnBnClickedEzvizlogin)
	ON_BN_CLICKED(IDC_DEVCONFIRM, &CDlgAddDevice::OnBnClickedDevconfirm)
	ON_BN_CLICKED(IDC_CHECKHCDDNS, OnBnClickedAutoPolling)
	ON_NOTIFY(NM_DBLCLK, IDC_EZVIZDEVICELIST, &CDlgAddDevice::OnNMDblclkEzvizdevicelist)
	ON_BN_CLICKED(IDC_USEHCACCOUNT, &CDlgAddDevice::OnBnClickedUsehcaccount)
	ON_BN_CLICKED(IDC_USEDEVACCOUNT, &CDlgAddDevice::OnBnClickedUsedevaccount)
	ON_MESSAGE(WM_DDNSAREALIST, GetAreaList)
	ON_MESSAGE(WM_DDNSGETDEVICELIST, GetDeviceList)
END_MESSAGE_MAP()


LRESULT CDlgAddDevice::GetAreaList(WPARAM wParam, LPARAM lParam)  //get message and show area list
{
	int size = (int)lParam;
	if (size == 0){
		return 0;
	}
	for (int i = 0; i < size; i++){
		m_cmbAreaList.AddString(countryName[i].c_str());
		if (countryName[i] == "China"){
			m_cmbAreaList.SetCurSel(i);
		}
	}
	if (((CButton*)GetDlgItem(IDC_USEHCACCOUNT))->GetCheck() && ((CButton*)GetDlgItem(IDC_CHECKHCDDNS))->GetCheck()){
		GetDlgItem(IDC_EZVIZLOGIN)->EnableWindow(true);
	}
	return (LRESULT)0;
}

LRESULT CDlgAddDevice::GetDeviceList(WPARAM wParam, LPARAM lParam)	//get message and show the data
{
	deviceInfo* device = (deviceInfo*)wParam;
	int k = m_DeviceList.GetItemCount();
	m_DeviceList.InsertItem(k, device->name);
	m_DeviceList.SetItemText(k, 1, device->serial);
	m_DeviceList.SetItemText(k, 2, device->domain);
	m_DeviceList.SetItemText(k, 3, device->ipAddr);
	m_DeviceList.SetItemText(k, 4, device->port);
	return (LRESULT)0;
}

DWORD ThreadGetAreaList(LPVOID pParam)		//sub thread to execute network operation
{
	char szLan[256] = { 0 };
	HWND hAreaList = (HWND)pParam;
	string retData = get_area_list();		//get area list
	if (retData == ""){
		g_pMainDlg->AddLog(-1, DDNS_FAIL_T, "Get Area List");
		g_StringLanType(szLan, "获取国家列表失败！", "Failed to get area list!");
		return (DWORD)0;
	}

	g_pMainDlg->AddLog(-1, DDNS_SUCC_T, "Get Area List");
	g_StringLanType(szLan, "获取国家列表成功！", "Get area list successfully!");

	Document dom;
	dom.Parse(retData.c_str());
	assert(dom.HasMember("data"));
	const Value &arealist = dom["data"];
	for (SizeType i = 0; i < arealist.Size(); i++){
		countryName[i] = arealist[i]["name"].GetString();
		countryID[i] = arealist[i]["id"].GetInt();
	}
	PostMessage(hAreaList, WM_DDNSAREALIST, (WPARAM)0, (LPARAM)arealist.Size());
	return (DWORD)0;
}

DWORD ThreadGetDeviceList(LPVOID pParam)	// sub thread to execute network operation
{
	char szLan[256] = { 0 };
	threadParam* param = (threadParam*)pParam;
	EzvizDDNSAPI m_Ezviz;
	m_Ezviz.setToken(param->access_token);
	m_Ezviz.setDomain(param->domain);

	string retData = m_Ezviz.get_ddns_info_of_my_devices(m_Ezviz.getToken());
	if (retData == ""){
		g_pMainDlg->AddLog(-1, DDNS_FAIL_T, "Get Device List");
		g_StringLanType(szLan, "获取设备列表出错！", "Failed to get device list!");
		return 0;
	}

	Document dom;
	dom.Parse(retData.c_str());
	string code = dom["code"].GetString();
	if (code != "200"){
		string msg = dom["msg"].GetString();
		string ErrorCode = "错误码: " + code + " ";
		string ErrorMsg = "错误信息: " + msg;
		string log = ErrorCode + ErrorMsg;
		g_pMainDlg->AddLog(-1, DDNS_FAIL_T, log.c_str());
		g_StringLanType(szLan, "获取设备列表出错！", "Error occurred while getting device list!");
	}
	else{
		if (dom["page"]["total"].GetInt() == 0){
			g_pMainDlg->AddLog(-1, DDNS_FAIL_T, "Get Device List");
			g_StringLanType(szLan, "设备列表为空, 没有设备！", "The device list is empty, no device!");
		}
		else{
			PostMessage(param->mList_hwnd, LVM_DELETEALLITEMS, 0, 0);
			const Value &devicelist = dom["data"];
			for (SizeType i = 0; i < devicelist.Size(); i++){

				device.name = (CString)devicelist[i]["deviceName"].GetString();
				device.serial = (CString)devicelist[i]["subSerial"].GetString();
				device.domain = (CString)devicelist[i]["domain"].GetString();
				device.ipAddr = (CString)devicelist[i]["deviceIp"].GetString();
				int port = devicelist[i]["mappingHiddnsCmdPort"].GetInt();
				CString devicePort;
				devicePort.Format(_T("%d"), port);
				device.port = devicePort;

				SendMessage(param->m_hwnd, WM_DDNSGETDEVICELIST, (WPARAM)&device, 0);
			}
		}
		g_pMainDlg->AddLog(-1, DDNS_SUCC_T, "Get Device List");
		g_StringLanType(szLan, "获取设备列表成功！", "Get device list successfully!");
	}
	return 0;
}

DWORD ThreadGetToken(LPVOID pParam)
{
	char szLan[256] = { 0 };
	threadParam *parameter = (threadParam*)pParam;
	string key = (CStringA)appKey;
	string secret = (CStringA)appSecret;
	string retData = get_access_token(key, secret);

	if (retData.find("200") != -1){
		Document dom;
		dom.Parse(retData.c_str());
		const Value &info = dom["data"];
		string accessToken, areaDomain;
		accessToken = info["accessToken"].GetString();
		areaDomain = info["areaDomain"].GetString();
		strcpy(param.access_token, accessToken.c_str());
		strcpy(param.domain, areaDomain.c_str());
		AfxBeginThread((AFX_THREADPROC)ThreadGetDeviceList, &param);	//new thread
		return 0;
	}
	else{
		g_pMainDlg->AddLog(-1, DDNS_FAIL_T, "Get Access Token");
		g_StringLanType(szLan, "获取AccessToken失败！", "Fail to get access token!");
		return 1;
	}
}

/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgAddDevice::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(TRUE);
	m_csNodeName.Format("dev%02d", m_iDeviceIndex);	
	GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
	OnBnClickedChkGetIpByIPServer();
    m_cmbProxyType.SetCurSel(0);
    m_cmbLoginMode.SetCurSel(0);
    m_cmbHttps.SetCurSel(0);
	UpdateData(FALSE);

	//2017-8-14 Add HCDDNS Device List;
	//Set device list header according to language
#ifdef DEMO_LAN_CN
	m_DeviceList.InsertColumn(0, _T("设备名"), LVCFMT_LEFT, 100, -1);
	m_DeviceList.InsertColumn(1, _T("序列号"), LVCFMT_LEFT, 60, -1);
	m_DeviceList.InsertColumn(2, _T("域名"), LVCFMT_LEFT, 100, -1);
	m_DeviceList.InsertColumn(3, _T("IP地址"), LVCFMT_LEFT, 100, -1);
	m_DeviceList.InsertColumn(4, _T("端口"), LVCFMT_LEFT, 60, -1);
#else
	m_DeviceList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100, -1);
	m_DeviceList.InsertColumn(1, _T("Serial"), LVCFMT_LEFT, 60, -1);
	m_DeviceList.InsertColumn(2, _T("Domain"), LVCFMT_LEFT, 100, -1);
	m_DeviceList.InsertColumn(3, _T("IP Address"), LVCFMT_LEFT, 100, -1);
	m_DeviceList.InsertColumn(4, _T("Port"), LVCFMT_LEFT, 60, -1);
#endif
	m_DeviceList.SetExtendedStyle(m_DeviceList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	((CButton*)GetDlgItem(IDC_USEHCACCOUNT))->SetCheck(true);
	//Init area list
	AfxBeginThread((AFX_THREADPROC)ThreadGetAreaList, this->m_hWnd);

	return TRUE;
}

/*********************************************************
  Function:	OnBnClickedAddDeviceOk
  Desc:		add device ok response function, log in and get device basic info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAddDevice::OnBnClickedAddDeviceOk()
{
	char szDeviceIP[128] = {0};
	char cUserName[100] = {0};
	char cPassword[100] = {0};
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;//the info get when login
	LONG lUserID = -1;
	NET_DVR_NETCFG_V30 struNetCfg = {0};
	NET_DVR_DEVICECFG_V40 struDevCfg = {0};
	
	DWORD dwReturned = 0;
	CString csTemp;

	int nErr = 0;
	UpdateData(TRUE);

	if (m_csDevAddr.GetLength() <= 0 || m_csDevAddr.GetLength() > 128)
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "设备地址长度为1~128!", "please input the device address in 1 and 128 characters!");
		AfxMessageBox(szLan);
		return;
	}
	if (m_nLoginPort <= 0)
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "非法的端口号!", "illeage port!");
		AfxMessageBox(szLan);
		return;
	}
	if ((strlen(m_csUserName) > 32) || (strlen(m_csPwd) > 16))
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "用户名不能超过32位和密码不能超过16位!", "user name should be shorter than 32 BYTES and pwd should be shorter than 16 BYTES!");
		AfxMessageBox(szLan);
		return;
	}

	sprintf(szDeviceIP, "%s", m_csDevAddr.GetBuffer(m_csDevAddr.GetLength()));
	strncpy(cUserName, m_csUserName, NAME_LEN);
	strncpy(cPassword, m_csPwd, PASSWD_LEN);
	if (strncmp(m_csNodeName.GetBuffer(0), "All", 3)==0)//Use "All.X" X means the device number，From 192.168.1.Y To 192.168.1.X+Y
	{
		strtok(m_csNodeName.GetBuffer(0), ".");
		
		nErr = atoi(strtok(NULL, "."));
		nErr = min(nErr, MAX_DEVICES-m_iDeviceIndex);
		sprintf(cPassword, "%s", strtok(szDeviceIP, "."));;
		strcat(cPassword, ".");
		strcat(cPassword, strtok(NULL, "."));
		strcat(cPassword, ".");
		strcat(cPassword, strtok(NULL, "."));
		int lastnum = atoi(strtok(NULL, "."));
		int iDeviceIndex = 0;
		for (int i = 0; i<nErr; i++)
		{
			iDeviceIndex = m_iDeviceIndex+i;
			sprintf(g_struDeviceInfo[iDeviceIndex].chLoginUserName, "admin");
			sprintf(g_struDeviceInfo[iDeviceIndex].chLoginPwd, "abcd1234");
			sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceIP, "%s.%d", cPassword, lastnum+i);
			g_struDeviceInfo[iDeviceIndex].iDeviceIndex = m_iDeviceIndex+i;
			g_struDeviceInfo[iDeviceIndex].iDeviceChanNum = 1;
			g_struDeviceInfo[iDeviceIndex].lDevicePort = m_nLoginPort;
            g_struDeviceInfo[iDeviceIndex].byHttps = m_cmbHttps.GetCurSel();    //0-http 1-https 2-自适应
            g_struDeviceInfo[iDeviceIndex].byLoginMode = m_cmbLoginMode.GetCurSel();  //0-private 1-ISAPI 2-自适应
			sprintf(g_struDeviceInfo[iDeviceIndex].chLocalNodeName, "%s", g_struDeviceInfo[iDeviceIndex].chDeviceIP);
			g_pMainDlg->RedrawDeviceNode(iDeviceIndex+1000);
		}
		
		g_SaveDeviceConfig();
		CDialog::OnOK();
		return;
	}
	memset(&struDeviceInfo, 0, sizeof(NET_DVR_DEVICEINFO_V30));

	if (m_csNodeName.GetLength() == 0)
	{
		m_csNodeName.Format("%s", szDeviceIP);
	}

	memcpy(szDeviceIP, NULL, 0);

    m_giAsynLoginReturn = 0;
    m_giErrNo = 0;
    m_gpErrMsg = NULL;
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
   // struLoginInfo.byVerifyMode = 2;
    if (m_gbAsynLogin)
    {
        struLoginInfo.bUseAsynLogin = true;
        struLoginInfo.cbLoginResult = LoginResultCallBack;
        struLoginInfo.pUser = &struDeviceInfoV40;
    }
    else
    {
        struLoginInfo.bUseAsynLogin = false;
    }
    memcpy(struLoginInfo.sDeviceAddress, szDeviceIP, NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, cUserName, NAME_LEN);
    memcpy(struLoginInfo.sPassword, cPassword, PASSWD_LEN);
    struLoginInfo.wPort = m_nLoginPort;
    struLoginInfo.byProxyType = m_cmbProxyType.GetCurSel();
    g_struDeviceInfo[m_iDeviceIndex].byProxyType = struLoginInfo.byProxyType;

    /*
    10.7.35.88  hik12345 //http->https重定向 (ISAPI 自适应)
    10.66.109.3 hik12345 //
    10.7.35.14  hik12345
    10.7.34.163 hik12345

    */
    //struLoginInfo.byUseTransport = 1;
    //struLoginInfo.byRes3[119] = 2;
    struLoginInfo.byHttps = m_cmbHttps.GetCurSel();    //0-http 1-https 2-自适应
    struLoginInfo.byLoginMode = m_cmbLoginMode.GetCurSel();  //0-private 1-ISAPI 2-自适应

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (m_gbAsynLogin)
    {
        m_gpDlgAsynloginWait = new CDlgAsynloginWait();
        m_gpDlgAsynloginWait->DoModal();
        delete m_gpDlgAsynloginWait;
        m_gpDlgAsynloginWait = NULL;
    }
    if ((m_gbAsynLogin && m_giAsynLoginReturn == 2) || lUserID < 0)
	{
        char szLan[128] = {0};
		nErr = NET_DVR_GetLastError();
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_Login_V30[%s]", szDeviceIP);
        if (m_giAsynLoginReturn != 0)
        {
            nErr = m_giErrNo;
        }
        if (nErr == NET_DVR_PASSWORD_ERROR)
        {
            g_StringLanType(szLan, "用户名密码错误!", "user name or password error!");
            AfxMessageBox(szLan);
            if(1 == struDeviceInfoV40.bySupportLock)
            {
                sprintf(szLan, "还剩%d尝试机会", struDeviceInfoV40.byRetryLoginTime);
                AfxMessageBox(szLan);
            }
        }
        else if (nErr == NET_DVR_USER_LOCKED)
        {
            if(1 == struDeviceInfoV40.bySupportLock)
            {
                sprintf(szLan, "IP被锁定，剩余锁定时间%dS", struDeviceInfoV40.dwSurplusLockTime);
                AfxMessageBox(szLan);
            }
        }
        else		//TODO: other error value
        {
            char szLan[256] = {0};
            g_StringLanType(szLan, "由于网络原因或DVR忙, 注册失败!", "net error or dvr is busy!");
            AfxMessageBox(szLan);
        }
        if (lUserID)
        {
            NET_DVR_Logout_V30(lUserID);
        }
        m_giAsynLoginReturn = 0;
        return;
    }
    else
    {
        g_struDeviceInfo[m_iDeviceIndex].byLoginModeRes = struDeviceInfoV40.byLoginMode;
        if (struDeviceInfoV40.byLoginMode == 0)
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "登录成功，采用协议为私有协议", "Login SUCC, Use Private");
            //AfxMessageBox(szLan);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szLan);
        }
        else
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "登录成功，采用协议为ISAPI", "Login SUCC, Use ISAPI");
            //AfxMessageBox(szLan);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szLan);
        }

        if (1 == struDeviceInfoV40.byPasswordLevel)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "默认密码，请修改", "default password, please change the password");
            AfxMessageBox(szLan);
        }
        else if(3 == struDeviceInfoV40.byPasswordLevel)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "风险密码，请修改", "risk password, please change the password");
            AfxMessageBox(szLan);
        }
        memcpy(&struDeviceInfo, &struDeviceInfoV40.struDeviceV30, sizeof(struDeviceInfo));
    }
    m_giAsynLoginReturn = 0;

	if(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo == NULL)
    {
        g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo =  new STRU_CHANNEL_INFO[MAX_CHANNUM_V40];
		
        if(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
        for (int i= 0; i < MAX_CHANNUM_V40; i++ )
        {
            memset(&g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i], 0, sizeof(STRU_CHANNEL_INFO));
            g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].lRealHandle = -1;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChanIndex = -1;
        }
        
    }
    else
    {
        memset(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo, 0, sizeof(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[0])*MAX_CHANNUM_V40);
        for (int i = 0; i < MAX_CHANNUM_V40; i++)
        {
            memset(&g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i], 0, sizeof(STRU_CHANNEL_INFO));
            g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].lRealHandle = -1;
            g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChanIndex = -1;
        }
    }
	
    if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40 == NULL)
    {
        g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40 = new NET_DVR_IPALARMINCFG_V40;
		
        if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40 == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
		
        memset(g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40, 0, sizeof(NET_DVR_IPALARMINCFG_V40));
    }
	
    if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40 == NULL)
    {
        g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40 =  new NET_DVR_IPALARMOUTCFG_V40;
        if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40 == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
		
        memset(g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40, 0, sizeof(NET_DVR_IPALARMOUTCFG_V40));
    }
	
    g_struDeviceInfo[m_iDeviceIndex].byCharaterEncodeType = struDeviceInfoV40.byCharEncodeType;
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, "%s", cUserName);
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chLoginPwd, "%s", cPassword);
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, "%s", szDeviceIP);

	g_struDeviceInfo[m_iDeviceIndex].lLoginID = lUserID;
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chSerialNumber, "%s", struDeviceInfo.sSerialNumber);
	g_struDeviceInfo[m_iDeviceIndex].iDeviceIndex = m_iDeviceIndex;
	g_struDeviceInfo[m_iDeviceIndex].iDeviceType = struDeviceInfo.wDevType;  //用扩展字段表示设备类型
	g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum = struDeviceInfo.byChanNum + struDeviceInfo.byIPChanNum  + struDeviceInfo.byHighDChanNum*256;
	g_struDeviceInfo[m_iDeviceIndex].iStartChan = struDeviceInfo.byStartChan;
	g_struDeviceInfo[m_iDeviceIndex].iDiskNum = struDeviceInfo.byDiskNum;
	g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum = struDeviceInfo.byAlarmOutPortNum;
	g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum = struDeviceInfo.byAlarmInPortNum;
	g_struDeviceInfo[m_iDeviceIndex].iAudioNum = struDeviceInfo.byAudioChanNum;
	g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum = struDeviceInfo.byChanNum;
	g_struDeviceInfo[m_iDeviceIndex].iIPChanNum = struDeviceInfo.byIPChanNum +  struDeviceInfo.byHighDChanNum*256;
    g_struDeviceInfo[m_iDeviceIndex].byZeroChanNum = struDeviceInfo.byZeroChanNum;
	g_struDeviceInfo[m_iDeviceIndex].byStartDTalkChan = struDeviceInfo.byStartDTalkChan;
    g_struDeviceInfo[m_iDeviceIndex].byLanguageType = struDeviceInfo.byLanguageType;
	g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum = struDeviceInfo.byMirrorChanNum;
	g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo = struDeviceInfo.wStartMirrorChanNo;
	g_struDeviceInfo[m_iDeviceIndex].byAudioInputChanNum = struDeviceInfo.byVoiceInChanNum;
    g_struDeviceInfo[m_iDeviceIndex].byStartAudioInputChanNo = struDeviceInfo.byStartVoiceInChanNo;
	if (struDeviceInfo.bySupport & 0x80)
	{
		g_struDeviceInfo[m_iDeviceIndex].byMainProto = struDeviceInfo.byMainProto + 2;
		g_struDeviceInfo[m_iDeviceIndex].bySubProto = struDeviceInfo.bySubProto + 2;
	}
	else
	{
		g_struDeviceInfo[m_iDeviceIndex].byMainProto = struDeviceInfo.byMainProto;
		g_struDeviceInfo[m_iDeviceIndex].bySubProto = struDeviceInfo.bySubProto;
	}    

	sprintf(g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName, "%s", m_csNodeName.GetBuffer(0));
	g_struDeviceInfo[m_iDeviceIndex].lDevicePort = m_nLoginPort;
    g_struDeviceInfo[m_iDeviceIndex].byHttps = m_cmbHttps.GetCurSel();    //0-http 1-https 2-自适应
    g_struDeviceInfo[m_iDeviceIndex].byLoginMode = m_cmbLoginMode.GetCurSel();  //0-private 1-ISAPI 2-自适应
	g_struDeviceInfo[m_iDeviceIndex].bySupport1 = struDeviceInfo.bySupport1;
    g_struDeviceInfo[m_iDeviceIndex].bySupport2 = struDeviceInfo.bySupport2;
	g_struDeviceInfo[m_iDeviceIndex].bySupport7 = struDeviceInfo.bySupport7;
    g_struDeviceInfo[m_iDeviceIndex].byLanguageType = struDeviceInfo.byLanguageType;

    char sIPV6Addr[130] = { 0 };
    int i = 0;
    for (; i < sizeof(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP); i++)
    {
        if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == '\0')
        {
            break;
        }
        else if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == ':')
        {
            sIPV6Addr[i] = '.';
        }
        else
        {
            sIPV6Addr[i] = g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i];
        }
    }
    strncpy(g_struDeviceInfo[m_iDeviceIndex].chDeviceIPInFileName, sIPV6Addr, sizeof(sIPV6Addr));


	if (!NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_NETCFG_V30, 0, &struNetCfg, sizeof(NET_DVR_NETCFG_V30), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V30");	
	}
	else
	{		
					//sprintf(g_struDeviceInfo[m_iDeviceIndex].chDevNetCard1IP, "%s", struNetCfg.struEtherNet[0].struDVRIP.sIpV4);
        if (!g_ValidIPv6((BYTE *)(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP)))
        {
            sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "%s", struNetCfg.struMulticastIpAddr.sIpV4);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "multi-cast ipv4[%s]", struNetCfg.struMulticastIpAddr.sIpV4);
        }
        else
		{
			sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "%s", struNetCfg.struMulticastIpAddr.byIPv6);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "multi-cast ipv6[%s]", struNetCfg.struMulticastIpAddr.byIPv6);
		}
        
#if 0
		//IPv6 mcast test	

		memset(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, 0, sizeof(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP));
		sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "ff02::1234");
#endif		
	}
    //2011-12-29
	//if (!NET_DVR_GetDVRConfig(lUserID,NET_DVR_GET_DEVICECFG_V40,0,&struDevCfg,sizeof(NET_DVR_DEVICECFG_V40),&dwReturned))
    NET_DVR_DEVICEINFO_V40 struDevInfoV40 = { 0 };
    if (!NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_DEV_LOGIN_RET_INFO, 0, &struDevInfoV40, sizeof(NET_DVR_DEVICEINFO_V40), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEV_LOGIN_RET_INFO");
	}
    else
	{
        //
        struDevCfg.byDVRType = struDevInfoV40.struDeviceV30.byDVRType;
        struDevCfg.wDevType = struDevInfoV40.struDeviceV30.wDevType;
        struDevCfg.byChanNum = struDevInfoV40.struDeviceV30.byChanNum;
        struDevCfg.byStartChan = struDevInfoV40.struDeviceV30.byStartChan;
        struDevCfg.byIPChanNum = struDevInfoV40.struDeviceV30.byIPChanNum;
        struDevCfg.byZeroChanNum = struDevInfoV40.struDeviceV30.byZeroChanNum;

		if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType != (int)struDevCfg.wDevType)
		{
			char szLan[256] = {0};
			char szLanShow[256] = {0};
			g_StringLanType(szLan, "登陆返回设备类型值与获取设备参数返回设备类型值不同", "returned device type is different between login and get device config");
			sprintf(szLanShow,"%s %d,%d",szLan,g_struDeviceInfo[m_iDeviceIndex].iDeviceType,struDevCfg.wDevType);
			AfxMessageBox(szLanShow);
		}
		
		sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceName,"%s",struDevCfg.byDevTypeName);
		g_struDeviceInfo[m_iDeviceIndex].dwDevSoftVer = struDevCfg.dwSoftwareVersion;
        ClassifyDevClass(g_struDeviceInfo[m_iDeviceIndex].chDeviceClassName, 100, struDevCfg.wDevClass);
	}


    //Analog Chan Info
    
    if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_B20_MSU_NP || \
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_MMC_B20_CLASS || \
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_B21_MCU_NP_CLASS || \
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_C20N_VWMS || \
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_AIOH_MCU_NP ||  //B20/B21/C20N主控
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_Y10_MCU)
    {
        int nAllChanNums = 0;
        int nPreChanNums = 0;
        NET_DVR_ALLSUBSYSTEMINFO_V40 struSubSystemInfoV40 = { 0 };
        if (NET_DVR_MatrixGetSubSystemInfo_V40(lUserID, &struSubSystemInfoV40))
        {
            for (int nSysCnt = 0; nSysCnt < MAX_SUBSYSTEM_NUM_V40; nSysCnt++)
            {
                if (struSubSystemInfoV40.struSubSystemInfo[nSysCnt].bySubSystemType == 2 &&
                    struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byBelongBoard != 0xff &&
                    struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums != 0)
                {
                    for (int nChanCnt = 0; nChanCnt < struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums; nChanCnt++)
                    {
                        DWORD dwDevNo = 1;
                        DWORD dwBelongBoard = struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byBelongBoard;
                        DWORD dwChanNo = struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceStartNum + nChanCnt;
                        g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iDeviceIndex = m_iDeviceIndex;
                        g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iChanIndex = nPreChanNums + nChanCnt;
                        g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].bEnable = TRUE;
                        g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
                        sprintf(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].chChanName, "Camera_%d_%d_%d", dwDevNo, dwBelongBoard, dwChanNo);
                        g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iChannelNO = dwDevNo << 24 | dwBelongBoard << 16 | dwChanNo;
                    }
                    nAllChanNums += struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums;
                    nPreChanNums = nAllChanNums;
                }
            }
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "获取主板子系统信息失败", "failed to get subsystem information");
            AfxMessageBox(szLan);
            return;
        }
        g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum = nAllChanNums;

        if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_C20N_VWMS || g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_Y10_MCU) //C20N服务器有预监通道
        {
            int iMinWallNo = 0;
            int iMaxWallNo = 0;

            char *pszBuf = new char[XML_BUF];
            memset(pszBuf, 0, XML_BUF);
            if (!NET_DVR_GetDeviceAbility(lUserID, WALL_ABILITY, NULL, 0, pszBuf, XML_BUF))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility WALL_ABILITY");
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "获取电视墙能力集失败", "failed to get video wall ability");
                AfxMessageBox(szLan);
                return;
            }

            char *pStart = strstr(pszBuf, "<wallNo min=\"");
            if (pStart == NULL)
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                AfxMessageBox(szLan);
                return;
            }
            pStart += strlen("<wallNo min=\"");
            char* pEnd = strstr(pStart, "\"");
            if (pEnd == NULL)
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                AfxMessageBox(szLan);
            }
            char sMinWallNo[32] = { 0 };
            memcpy(sMinWallNo, pStart, pEnd - pStart);
            iMinWallNo = atoi(sMinWallNo); //从能力集中解析到电视墙编号的最小值

            pStart = strstr(pEnd, "max=\"");
            if (pStart == NULL)
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                AfxMessageBox(szLan);
                return;
            }
            pStart += strlen("max=\"");
            pEnd = strstr(pStart, "\"");
            if (pEnd == NULL)
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                AfxMessageBox(szLan);
                return;
            }
            char sMaxWallNo[32] = { 0 };
            memcpy(sMaxWallNo, pStart, pEnd - pStart);
            iMaxWallNo = atoi(sMaxWallNo); //从能力集中解析到电视墙编号的最大值

            //生成电视墙预监通道
            for (int nChanCnt = iMinWallNo; nChanCnt < iMaxWallNo + 1; nChanCnt++)
            {
                g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iDeviceIndex = m_iDeviceIndex;
                g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iChanIndex = nPreChanNums + nChanCnt - iMinWallNo;
                g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].bEnable = TRUE;
                g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iChanType = DEMO_CHANNEL_TYPE_IP;
                sprintf(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].chChanName, "PreMonitor_%02d", nChanCnt);
                g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iChannelNO = 0xff000000 | nChanCnt;
            }
            nAllChanNums += (iMaxWallNo - iMinWallNo + 1);
            nPreChanNums = nAllChanNums;

            g_struDeviceInfo[m_iDeviceIndex].iIPChanNum = iMaxWallNo - iMinWallNo + 1;
        }

        g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum = nAllChanNums;
    }
	else
	{
		for (int i = 0; i <  g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum; i++)
		{
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iDeviceIndex = m_iDeviceIndex;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChanIndex = i;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO = i + g_struDeviceInfo[m_iDeviceIndex].iStartChan;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable = TRUE;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
			sprintf(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName, ANALOG_C_FORMAT, i+g_struDeviceInfo[m_iDeviceIndex].iStartChan);
		}
	}

    if (g_struDeviceInfo[m_iDeviceIndex].byZeroChanNum > 0)
    {
        for (int i=0; i<g_struDeviceInfo[m_iDeviceIndex].byZeroChanNum; i++)
        {
                g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].iDeviceIndex = m_iDeviceIndex;
                g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].iChanIndex = i+ZERO_CHAN_INDEX;
                sprintf(g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].chChanName, "ZeroChan%d", i);	
                //analog devices
                if (1)
                {
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].bEnable = TRUE;
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].dwImageType = CHAN_ORIGINAL;
                    //				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
                }
                else
                {
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].dwImageType = CHAN_OFF_LINE;
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].bEnable = FALSE;		
                }
        }
    }

	if ((g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum > 0) && (g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo > (g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum -1)))
    {
        for (int i=0; i<g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && i < 16; i++)
        {
			g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iDeviceIndex = m_iDeviceIndex;
			g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChanIndex = i + MIRROR_CHAN_INDEX;
			g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO = i + g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo;
			sprintf(g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].chChanName, "MirrorChan%d", i+1);	
			//analog devices
			if (1)
			{
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].bEnable = TRUE;
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].dwImageType = CHAN_ORIGINAL;
				//				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
			}
			else
			{
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].dwImageType = CHAN_OFF_LINE;
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].bEnable = FALSE;		
			}
        }
    }
    
	//g_pMainDlg->DoGetDeviceResoureCfg(m_iDeviceIndex);
	//new IP channel parameters
    if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum >=  0)
    {    
        if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum == 0)
        {
            g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 =new NET_DVR_IPPARACFG_V40;
            memset(g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40, 0, sizeof(NET_DVR_IPPARACFG_V40));
        }
        else
        {
            if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum % MAX_CHANNUM_V30 == 0)
            {
                g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 =new NET_DVR_IPPARACFG_V40[g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30];
                for (int i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30; i++)
                {
                    memset(&g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[i], 0, sizeof(NET_DVR_IPPARACFG_V40));
                }
            }
            else
            {
                g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 =new NET_DVR_IPPARACFG_V40[g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30 + 1];
                for (int i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30 + 1; i++)
                {
                    memset(&g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[i], 0, sizeof(NET_DVR_IPPARACFG_V40));
                }
            }
        }
        if (g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
        g_pMainDlg->DoGetDeviceResoureCfg(m_iDeviceIndex);
    }
     
	g_SaveDeviceConfig();
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedExit
  Desc:		exit, no adding
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAddDevice::OnBnClickedExit()
{
	CDialog::OnCancel();
}

/*********************************************************
Function:	OnBnClickedChkGetIpByIPServer
Desc:		get IP address of the device through IPServer
Input:	
Output:	
Return:	
**********************************************************/
void CDlgAddDevice::OnBnClickedChkGetIpByIPServer()
{
	UpdateData(TRUE);
    if (m_bChkGetIPByIPServer)
    {
		GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEVICE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GET_DEV_IP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ADD_DEV_SN)->EnableWindow(TRUE);
	 	GetDlgItem(IDC_DEVICE_ADDR)->EnableWindow(FALSE);	
    }
	else
	{
		GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEVICE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ADD_DEV_SN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_GET_DEV_IP)->EnableWindow(FALSE);
	 	GetDlgItem(IDC_DEVICE_ADDR)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnGetDevIp
  Desc:		get IP address
  Input:	
  Output:	
  Return:	
**********************************************************/
#define IPSERVER_PORT 7071
void CDlgAddDevice::OnBnClickedBtnGetDevIp()
{
	UpdateData(TRUE);
	char szGetDevIP[128] = {0};		
	sprintf(g_struLocalParam.chIPServerIP, "%s", m_csDDNSAddr.GetBuffer(0));
	DWORD dwPort = 0;
	if (!NET_DVR_GetDVRIPByResolveSvr_EX(m_csDDNSAddr.GetBuffer(0), (WORD)m_iIPServerPort/*IPSERVER_PORT*/, (BYTE *)(m_csDeviceName.GetBuffer(0)), (WORD)m_csDeviceName.GetLength(),\
		(BYTE *)m_csDevSN.GetBuffer(0), (WORD)m_csDevSN.GetLength(), szGetDevIP, &dwPort))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetDVRIPByResolveSvr");
		char szLan[1024] = {0};
		g_StringLanType(szLan, "获取设备地址失败!", "get device address error!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetDVRIPByResolveSvr");
		m_csDevAddr = szGetDevIP;
		m_nLoginPort = dwPort;
	}	
	UpdateData(FALSE);
}

void CDlgAddDevice::OnActivateDevice() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	char szLan[256] = {0};
    if ((strlen(m_csPwd) > 16))
    {
        g_StringLanType(szLan, "密码不能超过16位！", "pwd should be shorter than 16 BYTES!");
        AfxMessageBox(szLan);
        return;
	}

    if (strstr(m_csPwd, m_csUserName) != NULL)
    {
        char szLan[128] = { 0 };
        g_StringLanType(szLan, "密码不能包含用户名", "Password can not include the user name");
        AfxMessageBox(szLan);
        return;
    }
    NET_DVR_ACTIVATECFG struActivateCfg = {0};
    struActivateCfg.dwSize = sizeof(struActivateCfg);
    memcpy(struActivateCfg.sPassword, m_csPwd.GetBuffer(0), m_csPwd.GetLength());
	if(!NET_DVR_ActivateDevice(m_csDevAddr.GetBuffer(0), m_nLoginPort, &struActivateCfg))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ActivateDevice");
        LONG dwErr = NET_DVR_GetLastError();
        AfxMessageBox(NET_DVR_GetErrorMsg(&dwErr));
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ActivateDevice");
		g_StringLanType(szLan, "设备激活成功！", "The Device is activated successfully!");
        AfxMessageBox(szLan);
	}
}

void CDlgAddDevice::OnBnClickedRefresh()
{
	// TODO:  在此添加控件通知处理程序代码
	m_cmbAreaList.Clear();
	GetDlgItem(IDC_EZVIZLOGIN)->EnableWindow(false);
	AfxBeginThread((AFX_THREADPROC)ThreadGetAreaList, this->m_hWnd);
}

void CDlgAddDevice::OnBnClickedEzvizlogin()
{
	// TODO:  在此添加控件通知处理程序代码
	CEzvizLogin dlg;

	int index = m_cmbAreaList.GetCurSel();
	ostringstream stream;
	stream << index;
	dlg.setArea(stream.str());										//convert string to int

	int state = dlg.DoModal();										//jump to web browser

	param.m_hwnd = this->m_hWnd;									//begin thread to get device list
	strcpy(param.access_token, dlg.accessToken.c_str());
	strcpy(param.domain, dlg.areaDomain.c_str());					//set token and domain
	param.mList_hwnd = GetDlgItem(IDC_EZVIZDEVICELIST)->GetSafeHwnd();
	AfxBeginThread((AFX_THREADPROC)ThreadGetDeviceList, &param);	//new thread

}

void CDlgAddDevice::OnBnClickedAutoPolling()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECKHCDDNS);
	int state = pBtn->GetCheck();
	if (state == 1) // Selected
	{
		(CButton*)GetDlgItem(IDC_USEHCACCOUNT)->EnableWindow(true);
		(CButton*)GetDlgItem(IDC_USEDEVACCOUNT)->EnableWindow(true);
		(CListCtrl*)GetDlgItem(IDC_EZVIZDEVICELIST)->EnableWindow(true);
		if (((CButton*)GetDlgItem(IDC_USEHCACCOUNT))->GetCheck())
		{
			(CButton*)GetDlgItem(IDC_REFRESH)->EnableWindow(true);
			(CComboBox*)GetDlgItem(IDC_AREALIST)->EnableWindow(true);
			if (m_cmbAreaList.GetCount())
			{
				(CButton*)GetDlgItem(IDC_EZVIZLOGIN)->EnableWindow(true);
			}
		}
		else
		{
			(CButton*)GetDlgItem(IDC_DEVCONFIRM)->EnableWindow(true);
			(CEdit*)GetDlgItem(IDC_APPKEY)->EnableWindow(true);
			(CEdit*)GetDlgItem(IDC_APPSECRET)->EnableWindow(true);
		}
	}
	else			// Cancel
	{
		(CButton*)GetDlgItem(IDC_USEHCACCOUNT)->EnableWindow(false);
		(CButton*)GetDlgItem(IDC_USEDEVACCOUNT)->EnableWindow(false);
		(CButton*)GetDlgItem(IDC_REFRESH)->EnableWindow(false);
		(CButton*)GetDlgItem(IDC_EZVIZLOGIN)->EnableWindow(false);
		(CComboBox*)GetDlgItem(IDC_AREALIST)->EnableWindow(false);
		(CListCtrl*)GetDlgItem(IDC_EZVIZDEVICELIST)->EnableWindow(false);
		(CButton*)GetDlgItem(IDC_DEVCONFIRM)->EnableWindow(false);
		(CEdit*)GetDlgItem(IDC_APPKEY)->EnableWindow(false);
		(CEdit*)GetDlgItem(IDC_APPSECRET)->EnableWindow(false);
	}
}

void CDlgAddDevice::OnBnClickedDevconfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	param.m_hwnd = this->m_hWnd;									//begin thread to get device list
	param.mList_hwnd = GetDlgItem(IDC_EZVIZDEVICELIST)->GetSafeHwnd();
	GetDlgItemText(IDC_APPKEY, appKey);
	GetDlgItemText(IDC_APPSECRET, appSecret);
	AfxBeginThread((AFX_THREADPROC)ThreadGetToken, &param);			//new thread
}

void CDlgAddDevice::OnNMDblclkEzvizdevicelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	int index = pNMItemActivate->iItem;
	if (index >= 0 && index < m_DeviceList.GetItemCount()){			//judge data area
		CString IPAddr = m_DeviceList.GetItemText(index, 3);
		CString Port = m_DeviceList.GetItemText(index, 4);
		SetDlgItemText(IDC_DEVICE_ADDR, IPAddr);
		SetDlgItemText(IDC_DEVICE_PORT, Port);
	}
	*pResult = 0;
}

void CDlgAddDevice::OnBnClickedUsehcaccount()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_USEHCACCOUNT))->GetCheck()){
		(CButton*)GetDlgItem(IDC_DEVCONFIRM)->EnableWindow(false);
		(CEdit*)GetDlgItem(IDC_APPKEY)->EnableWindow(false);
		(CEdit*)GetDlgItem(IDC_APPSECRET)->EnableWindow(false);
		(CButton*)GetDlgItem(IDC_REFRESH)->EnableWindow(true);
		(CButton*)GetDlgItem(IDC_EZVIZLOGIN)->EnableWindow(true);
		(CComboBox*)GetDlgItem(IDC_AREALIST)->EnableWindow(true);
	}
}

void CDlgAddDevice::OnBnClickedUsedevaccount()
{
	// TODO:  在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_USEDEVACCOUNT))->GetCheck()){
		(CButton*)GetDlgItem(IDC_DEVCONFIRM)->EnableWindow(true);
		(CEdit*)GetDlgItem(IDC_APPKEY)->EnableWindow(true);
		(CEdit*)GetDlgItem(IDC_APPSECRET)->EnableWindow(true);
		(CButton*)GetDlgItem(IDC_REFRESH)->EnableWindow(false);
		(CButton*)GetDlgItem(IDC_EZVIZLOGIN)->EnableWindow(false);
		(CComboBox*)GetDlgItem(IDC_AREALIST)->EnableWindow(false);
	}
}
