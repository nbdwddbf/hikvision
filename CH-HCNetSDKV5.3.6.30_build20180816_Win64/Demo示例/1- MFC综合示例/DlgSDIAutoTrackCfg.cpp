// DlgSDIAutoTrackCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSDIAutoTrackCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSDIAutoTrackCfg dialog


DlgSDIAutoTrackCfg::DlgSDIAutoTrackCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSDIAutoTrackCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSDIAutoTrackCfg)
	m_bEnable = FALSE;
	m_nChan = 0;
	m_sDomain = _T("");
	m_sPassword = _T("");
	m_nPort = 0;
	m_sUserName = _T("");
	m_nPriority = 0;
	m_nDirectDelayTime = 0;
	m_sChan = _T("");
	//}}AFX_DATA_INIT
	memset(&m_struAutoTrackCfg,0,sizeof(m_struAutoTrackCfg));
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
}


void DlgSDIAutoTrackCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSDIAutoTrackCfg)
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddress);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_TYPE, m_comProtocolType);
	DDX_Control(pDX, IDC_COMBO_SDI_CHAN, m_comSDIChan);
    DDX_Control(pDX, IDC_COMBO_CAMERA_TYPE, m_cmbCameraType);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDT_CHAN, m_nChan);
	DDX_Text(pDX, IDC_EDT_DOMAIN, m_sDomain);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EDT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_sUserName);
	DDX_Text(pDX, IDC_PRIORITY, m_nPriority);
	DDX_Text(pDX, IDC_DIRECT_DELAY_TIME, m_nDirectDelayTime);
	DDX_Text(pDX, IDC_CHAN, m_sChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSDIAutoTrackCfg, CDialog)
	//{{AFX_MSG_MAP(DlgSDIAutoTrackCfg)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_SDI_CHAN, OnSelchangeComboSdiChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSDIAutoTrackCfg message handlers

BOOL DlgSDIAutoTrackCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    m_cmbCameraType.ResetContent();
    
    DWORD dwIndex = 0;
    char szLan[128] = {0};
    char szLanCn[128] = {0};
    char szLanEn[128] = {0};
    
    g_StringLanType(szLan,"无意义","Reserve");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex,0);
    dwIndex++;
    
    g_StringLanType(szLan,"老师跟踪","Teacher Track");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex,1);
    dwIndex++;
    
    g_StringLanType(szLan,"学生跟踪","Student Track");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex,2);
    dwIndex++;
    
    g_StringLanType(szLan,"老师全景","Teacher panoram");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex,3);
    dwIndex++;
    
    g_StringLanType(szLan,"学生全景","Student panoram");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex,4);
    dwIndex++;
    
    g_StringLanType(szLan,"多媒体","Multi-Media");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex,5);
    dwIndex++;
    
    g_StringLanType(szLan, "教师定位", "Teacher-");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex, 6);
    dwIndex++;

    g_StringLanType(szLan, "学生定位", "Student-");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex, 7);
    dwIndex++;

    g_StringLanType(szLan, "板书定位", "Multi-Media");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex, 8);
    dwIndex++;

    g_StringLanType(szLan, "板书相机", "Multi-Media");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex, 9);
    dwIndex++;

    g_StringLanType(szLan,"未接入","No access");
    m_cmbCameraType.AddString(szLan);
    m_cmbCameraType.SetItemData(dwIndex,0xff);
    
    
    m_comSDIChan.ResetContent();
    dwIndex = 0;
    
    for (int i = 0; i< g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
        if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
        {
            m_comSDIChan.AddString(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
            m_comSDIChan.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
            dwIndex++;
        }
    }

    m_comSDIChan.SetCurSel(0);
	OnBtnGet();
	return TRUE;
}

void DlgSDIAutoTrackCfg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int sel = m_comSDIChan.GetItemData(m_comSDIChan.GetCurSel())  -1;
	
	m_struAutoTrackCfg.struSDIInfo[sel].byEnable = m_bEnable;
	m_struAutoTrackCfg.struSDIInfo[sel].byProType = (BYTE)m_comProtocolType.GetCurSel();
     m_struAutoTrackCfg.byCameraType[sel] = m_cmbCameraType.GetCurSel();

 	CString csTemp;

	BYTE nField0,nField1,nField2,nField3; 
	m_IPAddress.GetAddress(nField0,nField1,nField2,nField3);
	if(0 == nField0 && 0 == nField1 && 0 == nField2 && 0 == nField3)
	{
		csTemp = _T("");
	}
	else
	{
		csTemp.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
	}
	memset(m_struAutoTrackCfg.struSDIInfo[sel].struIP.sIpV4, 0, \
	sizeof(m_struAutoTrackCfg.struSDIInfo[sel].struIP.sIpV4));
	memcpy(m_struAutoTrackCfg.struSDIInfo[sel].struIP.sIpV4, csTemp, csTemp.GetLength());
	m_struAutoTrackCfg.struSDIInfo[sel].wDVRPort = m_nPort;
	m_struAutoTrackCfg.struSDIInfo[sel].dwChannel = m_nChan;
	m_struAutoTrackCfg.struSDIInfo[sel].byPriority = m_nPriority;
	m_struAutoTrackCfg.struSDIInfo[sel].wDirectLastTime = m_nDirectDelayTime;
	sprintf((char*)m_struAutoTrackCfg.struSDIInfo[sel].sUserName, "%s", m_sUserName);
	sprintf((char*)m_struAutoTrackCfg.struSDIInfo[sel].sPassword, "%s", m_sPassword);
	sprintf((char*)m_struAutoTrackCfg.struSDIInfo[sel].byDomain, "%s", m_sDomain);
	sprintf((char*)m_struAutoTrackCfg.struSDIInfo[sel].byChanNo, "%s", m_sChan);

    for (int i =0; i< m_cmbCameraType.GetCount(); i++)
    {
        if (m_cmbCameraType.GetItemData(i) == m_struAutoTrackCfg.byCameraType[sel])
        {
            m_cmbCameraType.SetCurSel(i);
            break;
        }
    }
}

void DlgSDIAutoTrackCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	OnBtnOk();
	char szLan[128] = {0};
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_RECORDING_AUTO_TRACK_CFG,m_iStartChannel,&m_struAutoTrackCfg,sizeof(m_struAutoTrackCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORDING_AUTO_TRACK_CFG,  %s", "Set Record auto track faild");
		g_StringLanType(szLan, "设置SDI自动跟踪配置失败", "Get Record host cfg failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORDING_AUTO_TRACK_CFG,  %s", "Set Record auto track success");
		g_StringLanType(szLan, "设置SDI自动跟踪配置成功", "Set Record auto track success");
		AfxMessageBox(szLan);
	}
	return;
}

void DlgSDIAutoTrackCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturnned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_RECORDING_AUTO_TRACK_CFG,m_iStartChannel,&m_struAutoTrackCfg,sizeof(m_struAutoTrackCfg),&dwReturnned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORDING_AUTO_TRACK_CFG,  %s", "Get Record auto track faild");
		g_StringLanType(szLan, "获取SDI自动跟踪配置失败", "Get Record auto track failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDING_AUTO_TRACK_CFG,  %s", "Get Record auto track success");
		g_StringLanType(szLan, "获取录播主机参数配置成功", "Get Record auto track success");
		AfxMessageBox(szLan);
	}
	m_comSDIChan.SetCurSel(0);
	OnSelchangeComboSdiChan();
}

void DlgSDIAutoTrackCfg::OnSelchangeComboSdiChan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int sel = m_comSDIChan.GetItemData(m_comSDIChan.GetCurSel());
    
    sel = sel -1;
    m_bEnable = m_struAutoTrackCfg.struSDIInfo[sel].byEnable;
    m_comProtocolType.SetCurSel((int)m_struAutoTrackCfg.struSDIInfo[sel].byProType);
    
    for (int i = 0; i< m_cmbCameraType.GetCount();i++)
    {
        if (m_cmbCameraType.GetItemData(i) == m_struAutoTrackCfg.byCameraType[sel])
        {
            m_cmbCameraType.SetCurSel(i);
            break;
        }
    }

	CString csDevIP;
	csDevIP.Format(_T("%s"), m_struAutoTrackCfg.struSDIInfo[sel].struIP.sIpV4);
	BYTE nField0,nField1,nField2,nField3 = 0; 
	if (csDevIP.Compare(_T("")) != 0)
	{
		int nPos0 = csDevIP.FindOneOf(".");
		nField0 = atoi(csDevIP.Left(nPos0));
		
		int nPos1 = csDevIP.Find(".", nPos0 + 1);
		nField1 = atoi(csDevIP.Mid(nPos0 + 1, nPos1 - nPos0 -1));
		
		int nPos2 = csDevIP.Find(".", nPos1 + 1);
		nField2 = atoi(csDevIP.Mid(nPos1 + 1, nPos2 - nPos1 - 1));
		
		nField3 = atoi(csDevIP.Right(csDevIP.GetLength() - (nPos2 + 1)));
		
		m_IPAddress.SetAddress(nField0, nField1, nField2, nField3);
	}
	else
	{
		m_IPAddress.SetAddress(0, 0, 0, 0);
	}
	m_nPort = m_struAutoTrackCfg.struSDIInfo[sel].wDVRPort;
	m_nChan = m_struAutoTrackCfg.struSDIInfo[sel].dwChannel;

    char szUserNameTemp[33] = {0};
    memcpy(szUserNameTemp, m_struAutoTrackCfg.struSDIInfo[sel].sUserName, sizeof(m_struAutoTrackCfg.struSDIInfo[sel].sUserName));
	m_sUserName = szUserNameTemp;

    char szPassword[17] = {0};
    memcpy(szPassword, m_struAutoTrackCfg.struSDIInfo[sel].sPassword, sizeof(m_struAutoTrackCfg.struSDIInfo[sel].sPassword));
	m_sPassword = szPassword;

	m_sDomain = m_struAutoTrackCfg.struSDIInfo[sel].byDomain;
	m_nPriority = m_struAutoTrackCfg.struSDIInfo[sel].byPriority;
	m_nDirectDelayTime = m_struAutoTrackCfg.struSDIInfo[sel].wDirectLastTime;
	m_sChan.Format("%s",(char*)m_struAutoTrackCfg.struSDIInfo[sel].byChanNo);
	UpdateData(FALSE);
}
