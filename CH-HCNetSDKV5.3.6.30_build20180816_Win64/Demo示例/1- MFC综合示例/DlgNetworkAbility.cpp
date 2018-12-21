// DlgNetworkAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNetworkAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkAbility dialog


CDlgNetworkAbility::CDlgNetworkAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetworkAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNetworkAbility)
	m_iWPAMax = 0;
	m_iWPAMin = 0;
	//}}AFX_DATA_INIT
    m_pRecvBuf = NULL;
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struNetworkAbility, 0, sizeof(m_struNetworkAbility));
}


void CDlgNetworkAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetworkAbility)
	DDX_Control(pDX, IDC_LIST_WEP_KEYLENGTH, m_listWEPKeylength);
	DDX_Control(pDX, IDC_LIST_NETWORK_MODE, m_listNetworkMode);
	DDX_Control(pDX, IDC_LIST_INTERFACE_MODE, m_listInterfaceMode);
	DDX_Control(pDX, IDC_LIST_AUTH_TYPE, m_listAuthType);
	DDX_Text(pDX, IDC_EDIT_WPA_MAX, m_iWPAMax);
	DDX_Text(pDX, IDC_EDIT_WPA_MIN, m_iWPAMin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetworkAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgNetworkAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkAbility message handlers

BOOL CDlgNetworkAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    if (m_pRecvBuf == NULL)
    {
        m_pRecvBuf = new char[XML_BUF];
    }
    
    GetNetworkAbility();

    ParseNetworkAbility(m_pRecvBuf, strlen(m_pRecvBuf));

    SetNetworkAbilityToWnd(m_struNetworkAbility);
    UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgNetworkAbility::GetNetworkAbility()
{
    if (NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_NETWORK_ABILITY, NULL, 0, m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_NETWORK_ABILITY");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_NETWORK_ABILITY");
        return TRUE;
    }
}

void CDlgNetworkAbility::PostNcDestroy() 
{
    if (m_pRecvBuf != NULL)
    {
        delete []m_pRecvBuf;
        m_pRecvBuf = NULL;
    }
    
	CDialog::PostNcDestroy();
}

BOOL CDlgNetworkAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\%s.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        int nError = 0;
        nError = GetLastError();
        return FALSE;
    }
    DWORD dwReturn = 0;
    WriteFile(hFile, pBuf, dwBufSize, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseNetworkAbility(char *pBuf, DWORD dwBufSize)
{
    WirteBufToFile(pBuf, dwBufSize);

    CMarkup	XmlMaker;
    XmlMaker.SetDoc(pBuf);
    
    ParseNetworkSettingXml(XmlMaker);   
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseNetworkSettingXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("NetworkSetting"))
    {
        struMarkup.IntoElem();

        ParseWirelessSettingXml(struMarkup);

        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find NetworkSetting Fail");
        return FALSE;
    }
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseWirelessSettingXml(CMarkup &struMarkup)
{

    if (struMarkup.FindElem("WirelessSetting"))
    {
        struMarkup.IntoElem();
        
        ParseInterfaceModeXml(struMarkup);
        ParseNetworkModeXml(struMarkup);
        ParseSecurityModeXml(struMarkup);
        struMarkup.OutOfElem();
    } 
    else
    {
        AfxMessageBox("Find WirelessSetting Fail");
    }
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseInterfaceModeXml(CMarkup &struMarkup)
{
 
    if (struMarkup.FindElem("InterfaceMode"))
    {
        struMarkup.IntoElem();

        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struNetworkAbility.struWireless.byInterfaceMode, sizeof(m_struNetworkAbility.struWireless.byInterfaceMode));
        }

        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find InterfaceMode Fail");
    }
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseNetworkModeXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("NetworkMode"))
    {
        struMarkup.IntoElem();

        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struNetworkAbility.struWireless.byNetworkMode, sizeof(m_struNetworkAbility.struWireless.byNetworkMode));
        }

        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find NetworkMode fail");
    }
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseSecurityModeXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("SecurityMode"))
    {
        struMarkup.IntoElem();
        
        ParseSecurityNoneXml(struMarkup);
        ParseSecurityWEPXml(struMarkup);
        ParseSecurityWPAPSKXml(struMarkup);        
        
    struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find SecurityMode fail");
    }
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseSecurityNoneXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("NONE"))
    {
        struMarkup.IntoElem();

        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find NONE Fail");
    }
    return TRUE;
}

BOOL CDlgNetworkAbility::ParseSecurityWEPXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("WEP"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("AuthenticationType"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struNetworkAbility.struWireless.struSecurityMode.struWep.byAuthenticationType, sizeof(m_struNetworkAbility.struWireless.struSecurityMode.struWep.byAuthenticationType));
            }
            struMarkup.OutOfElem();
        }

        if (struMarkup.FindElem("WEPKeyLength"))
        {
            struMarkup.IntoElem();

            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struNetworkAbility.struWireless.struSecurityMode.struWep.byWepKeyLength, sizeof(m_struNetworkAbility.struWireless.struSecurityMode.struWep.byWepKeyLength));
            }

            struMarkup.OutOfElem();
        }
            
        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find Wep fail");
    }

    return TRUE;
}

BOOL CDlgNetworkAbility::ParseSecurityWPAPSKXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("WPA_PSK"))
    {
        struMarkup.IntoElem();

        if (struMarkup.FindElem("WPA_PSK KeyLength"))
        {
            struMarkup.IntoElem();
            
            if (struMarkup.FindElem("Min"))
            {
                m_struNetworkAbility.struWireless.struSecurityMode.struWpaPsk.byMiniLength = atoi(struMarkup.GetData());
            }
            
            if (struMarkup.FindElem("Max"))
            {
                m_struNetworkAbility.struWireless.struSecurityMode.struWpaPsk.byMaxLength = atoi(struMarkup.GetData());
            }
            struMarkup.OutOfElem();
        }

        struMarkup.OutOfElem();
    }
    else
    {
       AfxMessageBox("Find WPA_PSK Fail");
    }
    return TRUE;
}


void CDlgNetworkAbility::ParseStrIndex(CString strIndex, byte* array, int iArrayLength)
{
    CString strTemp1 = _T("");
    CString strTemp2 = _T("");
    int iIndex = -1;
    
    strTemp1.Format("%s", strIndex);
    
    iIndex = strTemp1.Find(',', 0);
    
    //当没有','时，直接转换为数字
    if (-1 == iIndex)
    {
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp1) >= iArrayLength || atoi(strTemp1) < 0)
        {
            return;
        }
        array[atoi(strTemp1)] = 1;
        return;
    }
    
    //解析strIndex，设置数组的值
    while (iIndex != -1 )
    {
        strTemp2.Format("%s", strTemp1.Left(iIndex));
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
        {
            return;
        }
        array[atoi(strTemp2)] = 1;
        strTemp1.Delete(0, iIndex + 1);
        iIndex = strTemp1.Find(',', 0);
    }
    
    //若转换得到的数字大于数组的维数或者小于0，则返回
    if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
    {
        return;
    }
    array[atoi(strTemp1)] = 1;
}

void CDlgNetworkAbility::SetNetworkAbilityToWnd(NETWORK_ABILITY_PARAM &struNetworkAbility)
{
    SetWirelessToWnd(struNetworkAbility.struWireless);
}

void CDlgNetworkAbility::SetWirelessToWnd(WIRELESS_ABILITY_PARAM &struWireless)
{
    char szLan[128] = {0};
    int i = 0;
    m_listInterfaceMode.ResetContent();
    for (i = 0; i <ARRAY_SIZE(struWireless.byInterfaceMode); i++)
    {
        if (1 == struWireless.byInterfaceMode[i])
        {
            sprintf(szLan, "%d", i);
            m_listInterfaceMode.AddString(szLan);
        }
    }

    m_listNetworkMode.ResetContent();

    for (i = 0; i < ARRAY_SIZE(struWireless.byNetworkMode); i++)
    {
        if (1 == struWireless.byNetworkMode[i])
        {
            sprintf(szLan, "%d", i);
            m_listNetworkMode.AddString(szLan);
        }
    }
    SetSecurityModeToWnd(struWireless.struSecurityMode);
}

void CDlgNetworkAbility::SetSecurityModeToWnd(SECURITY_MODE &struSecurity)
{
    SetWEPToWnd(struSecurity.struWep);
    SetWAPPSKToWnd(struSecurity.struWpaPsk);
}

void CDlgNetworkAbility::SetWEPToWnd(SECURITY_WEP &struWep)
{
    char szLan[128] = {0};
    m_listAuthType.ResetContent();
    int i = 0;
    for (i = 0; i < ARRAY_SIZE(struWep.byAuthenticationType); i++)
    {
        if (1 == struWep.byAuthenticationType[i])
        {
            sprintf(szLan, "%d", i);
            m_listAuthType.AddString(szLan);
        }
    }
    
    m_listWEPKeylength.ResetContent();
    for (i = 0; i < ARRAY_SIZE(struWep.byWepKeyLength); i++)
    {
        if (1 == struWep.byWepKeyLength[i])
        {
            sprintf(szLan, "%d", i);
            m_listWEPKeylength.AddString(szLan);
        }
    }
    
}

void CDlgNetworkAbility::SetWAPPSKToWnd(SERCURITY_WPA_PSK &struWpaPsk)
{
    m_iWPAMax = struWpaPsk.byMaxLength;
    m_iWPAMin = struWpaPsk.byMiniLength;
}
