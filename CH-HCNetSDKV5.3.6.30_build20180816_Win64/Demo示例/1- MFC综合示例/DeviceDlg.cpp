// DeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog


CDeviceDlg::CDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceDlg)
	m_strDeviceIp = _T("");
	m_strDeviceName = _T("");
	m_strDspSoftwareVersion = _T("");
	m_strGateWayIp = _T("");
	m_dwHttpPort = 0;
	m_strMaskIp = _T("");
	m_dwMainPort = 0;
	m_strSerial = _T("");
	m_strSoftwareVersion = _T("");
	m_strMacIp = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
}


void CDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceDlg)
	DDX_Control(pDX, IDC_COMBO_NET_FACE, m_NetFaceCtrl);
	DDX_Text(pDX, IDC_EDIT_DEVICE_IP, m_strDeviceIp);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_strDeviceName);
	DDX_Text(pDX, IDC_EDIT_DSP_SOFTWARE_VERSION, m_strDspSoftwareVersion);
	DDX_Text(pDX, IDC_EDIT_GATEWAY_IP, m_strGateWayIp);
	DDX_Text(pDX, IDC_EDIT_HTTP_PORT, m_dwHttpPort);
	DDX_Text(pDX, IDC_EDIT_IP_MASK, m_strMaskIp);
	DDX_Text(pDX, IDC_EDIT_MAIN_PORT, m_dwMainPort);
	DDX_Text(pDX, IDC_EDIT_SERIAL, m_strSerial);
	DDX_Text(pDX, IDC_EDIT_SOFTWARE_VERSION, m_strSoftwareVersion);
	DDX_Text(pDX, IDC_EDIT_MACIP, m_strMacIp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(CDeviceDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg message handlers
/*************************************************
函数名:    	OnBtnSave
函数描述:	保存参数
输入参数:   无
输出参数:   			
返回值:		
*************************************************/
void CDeviceDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_DeviceCfg.dwSize = sizeof(m_DeviceCfg);
    memcpy(m_DeviceCfg.sDVRName, m_strDeviceName, NAME_LEN);
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DEVICECFG, -1, &m_DeviceCfg, sizeof(m_DeviceCfg)))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DEVICECFG");
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DEVICECFG");
	}

    m_NetCfg.dwSize = sizeof(m_NetCfg);
    memcpy(m_NetCfg.struEtherNet[0].struDVRIP.sIpV4, m_strDeviceIp, 16);
    m_NetCfg.struEtherNet[0].wDVRPort = (WORD)m_dwMainPort;
    m_NetCfg.struEtherNet[0].dwNetInterface = m_NetFaceCtrl.GetCurSel() + 1;
    memcpy(m_NetCfg.struGatewayIpAddr.sIpV4, m_strGateWayIp, 16);
    memcpy(m_NetCfg.struEtherNet[0].struDVRIPMask.sIpV4, m_strMaskIp, 16);
    m_NetCfg.wHttpPortNo = (WORD)m_dwHttpPort;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_NETCFG_V30, -1, &m_NetCfg, sizeof(m_NetCfg)))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NETCFG_V30");
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_NETCFG_V30");
	}  
}
/*************************************************
函数名:    	GetDeviceParam
函数描述:	获取设备参数
输入参数:   无
输出参数:   			
返回值:		
*************************************************/
BOOL CDeviceDlg::GetDeviceParam()
{
    DWORD dwReturn = 0;
    memset(&m_NetCfg, 0, sizeof(m_NetCfg));
    m_NetCfg.dwSize = sizeof(m_NetCfg);
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_NETCFG_V30, -1, &m_NetCfg, sizeof(m_NetCfg), &dwReturn))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V30");
        MessageBox(NET_DVR_GetErrorMsg());
        return FALSE;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETCFG_V30");
	}

    m_strDeviceIp = m_NetCfg.struEtherNet[0].struDVRIP.sIpV4;
    m_strMaskIp = m_NetCfg.struEtherNet[0].struDVRIPMask.sIpV4;
    m_dwMainPort = m_NetCfg.struEtherNet[0].wDVRPort;
    m_dwHttpPort = m_NetCfg.wHttpPortNo;
    m_strGateWayIp = m_NetCfg.struGatewayIpAddr.sIpV4;
    m_NetFaceCtrl.SetCurSel(m_NetCfg.struEtherNet[0].dwNetInterface - 1);
    m_strMacIp.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_NetCfg.struEtherNet[0].byMACAddr[0], m_NetCfg.struEtherNet[0].byMACAddr[1]
                    , m_NetCfg.struEtherNet[0].byMACAddr[2], m_NetCfg.struEtherNet[0].byMACAddr[3], m_NetCfg.struEtherNet[0].byMACAddr[4]
                    , m_NetCfg.struEtherNet[0].byMACAddr[5]);

    memset(&m_DeviceCfg, 0, sizeof(m_DeviceCfg));
    m_DeviceCfg.dwSize = sizeof(m_DeviceCfg);
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DEVICECFG, -1, &m_DeviceCfg, sizeof(m_DeviceCfg), &dwReturn))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICECFG");
        MessageBox(NET_DVR_GetErrorMsg());
        return FALSE;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVICECFG");
	}

    m_strDeviceName = m_DeviceCfg.sDVRName;
    m_strSerial = m_DeviceCfg.sSerialNumber;

	if (((m_DeviceCfg.dwSoftwareVersion>>24)&0xFF) > 0)
	{
		m_strSoftwareVersion.Format("V%d.%d.%d build %02d%02d%02d",\
			(m_DeviceCfg.dwSoftwareVersion>>24)&0xFF, (m_DeviceCfg.dwSoftwareVersion>>16)&0xFF, m_DeviceCfg.dwSoftwareVersion&0xFFFF, (m_DeviceCfg.dwSoftwareBuildDate>>16)&0xFFFF, (m_DeviceCfg.dwSoftwareBuildDate>>8)&0xFF,m_DeviceCfg.dwSoftwareBuildDate&0xFF);
	}
	else
	{
		m_strSoftwareVersion.Format("V%d.%d build %02d%02d%02d",\
			(m_DeviceCfg.dwSoftwareVersion>>16)&0xFFFF, m_DeviceCfg.dwSoftwareVersion&0xFFFF, (m_DeviceCfg.dwSoftwareBuildDate>>16)&0xFFFF, (m_DeviceCfg.dwSoftwareBuildDate>>8)&0xFF,m_DeviceCfg.dwSoftwareBuildDate&0xFF);
	}
    m_strDspSoftwareVersion.Format("V%d.%d build %02d%02d%02d", (m_DeviceCfg.dwDSPSoftwareVersion>>16)&0xFFFF, m_DeviceCfg.dwDSPSoftwareVersion&0xFFFF, (m_DeviceCfg.dwDSPSoftwareBuildDate>>16)&0xFFFF-2000, (m_DeviceCfg.dwDSPSoftwareBuildDate>>8)&0xFF,m_DeviceCfg.dwDSPSoftwareBuildDate&0xFF);	
    
    UpdateData(FALSE);
    return TRUE;
}
