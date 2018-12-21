// DlgRecordPublishCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordPublishCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRecordPublishCfg dialog


DlgRecordPublishCfg::DlgRecordPublishCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRecordPublishCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRecordPublishCfg)
	m_bRecordPublish = FALSE;
	m_sPath = _T("");
	m_sPassword = _T("");
	m_nPort = 0;
	m_sUrl = _T("");
	m_sUserName = _T("");
	m_sIP = _T("");
	m_bRecordMainStream = FALSE;
	m_bRecordStreamThree = FALSE;
	m_bRecordSubStream = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struPublishCfg,0,sizeof(m_struPublishCfg));
	m_lUserID = 0;
	m_iDeviceIndex = 0;
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
}


void DlgRecordPublishCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRecordPublishCfg)
	DDX_Control(pDX, IDC_COMBO_RECORD_CHAN, m_comRecordChan);
	DDX_Control(pDX, IDC_COMBO_PUBLISH_TYPE, m_comPublishType);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_TYPE, m_comProtocolType);
    DDX_Control(pDX, IDC_COMBO_ADDRESS_TYPE, m_comAddressType);
    DDX_Control(pDX, IDC_COMBO_DIR_LEVEL, m_comDirLevel);
    DDX_Control(pDX, IDC_COMBO_FIRST_DIRMODE, m_comFirstDirMoe);
    DDX_Control(pDX, IDC_COMBO_SECORD_DIRMODE, m_comSecordDirMode);
    DDX_Control(pDX, IDC_COMBO_TIMER_MODE, m_cmbTimerMode);
	DDX_Check(pDX, IDC_CHK_RECORD_PUBLISH, m_bRecordPublish);
	DDX_Text(pDX, IDC_EDT_DIR_PATH, m_sPath);
	DDX_Text(pDX, IDC_EDT_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EDT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDT_URL, m_sUrl);
	DDX_Text(pDX, IDC_EDT_USER_NAME, m_sUserName);
	DDX_Text(pDX, IDC_EDT_IP, m_sIP);
    DDX_Text(pDX, IDC_EDIT_FIRST_USERDIR, m_csFirstUserDir);
    DDX_Text(pDX, IDC_EDIT_SECOND_USERDIR, m_csSecordUserDir);
    DDX_Text(pDX, IDC_EDIT_HOUR_TIMER, m_byHour);
    DDX_Text(pDX, IDC_EDIT_MIN_TIMER, m_byMin);
    DDX_Check(pDX, IDC_RECORD_MAIN_STREAM, m_bRecordMainStream);
    DDX_Check(pDX, IDC_RECORD_STREAM_THREE, m_bRecordStreamThree);
    DDX_Check(pDX, IDC_RECORD_SUB_STREAM, m_bRecordSubStream);
    DDX_Check(pDX, IDC_CHK_UPLOADBYTIME, m_bUploadByTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRecordPublishCfg, CDialog)
	//{{AFX_MSG_MAP(DlgRecordPublishCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_RECORD_OK, OnBtnRecordOk)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORD_CHAN, OnSelchangeComboRecordChan)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRecordPublishCfg message handlers
BOOL DlgRecordPublishCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    DWORD dwIndex = 0;
    m_comRecordChan.ResetContent();

    int i = 0;

    for ( i = 0; i< g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
        if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
        {
            m_comRecordChan.AddString(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
            m_comRecordChan.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
            dwIndex++;
        }
    }
    
    for( i = 0; i < g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum;i++)
    {
        if (i == 0)
        {
            m_comRecordChan.AddString(g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].chChanName);
            m_comRecordChan.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO);
            dwIndex++;
        }
    }
    
	m_comRecordChan.SetCurSel(0);

    m_byHour = 0;
    m_byMin = 0;
    m_bUploadByTime = FALSE;
	OnBtnGet();
	return TRUE;
}

void DlgRecordPublishCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	//OnBtnRecordOk();
	UpdateData(TRUE);
	
	m_struPublishCfg.dwSize = sizeof(m_struPublishCfg);
    if (m_comAddressType.GetCurSel() < 0)
    {
        m_struPublishCfg.byPublishType = 0;
    }
    else
    {
        m_struPublishCfg.byPublishType = m_comAddressType.GetCurSel();
    }

	if (0 == m_struPublishCfg.byPublishType)
	{
		sprintf((char*)m_struPublishCfg.struPublishAddr.struHttpCfg.strUrl,"%s",m_sUrl);
	}
	else if (1 == m_struPublishCfg.byPublishType)
	{
		sprintf((char*)m_struPublishCfg.struPublishAddr.struFtpCfg.byAddress,"%s",m_sIP);
		m_struPublishCfg.struPublishAddr.struFtpCfg.byProtocolType = m_comProtocolType.GetCurSel();
		m_struPublishCfg.struPublishAddr.struFtpCfg.wFTPPort = (WORD)m_nPort;
		sprintf((char*)m_struPublishCfg.struPublishAddr.struFtpCfg.szCustomDir,"%s",m_sPath);
		sprintf((char*)m_struPublishCfg.struPublishAddr.struFtpCfg.szUserName,"%s",m_sUserName);
		sprintf((char*)m_struPublishCfg.struPublishAddr.struFtpCfg.szPassWord,"%s",m_sPassword);
	}
    else if (2 == m_struPublishCfg.byPublishType)
    {
        sprintf((char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.byAddress,"%s",m_sIP);
        m_struPublishCfg.struPublishAddr.struDirFtpCfg.byProtocolType = m_comProtocolType.GetCurSel();
        m_struPublishCfg.struPublishAddr.struDirFtpCfg.wFTPPort = (WORD)m_nPort;
        sprintf((char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.szUserName,"%s",m_sUserName);
		sprintf((char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.szPassWord,"%s",m_sPassword);
        m_struPublishCfg.struPublishAddr.struDirFtpCfg.byDirLevel = m_comDirLevel.GetCurSel();
        m_struPublishCfg.struPublishAddr.struDirFtpCfg.byTopDirMode = m_comFirstDirMoe.GetCurSel() +1;
        if(m_struPublishCfg.struPublishAddr.struDirFtpCfg.byTopDirMode == 4)
        {
            m_struPublishCfg.struPublishAddr.struDirFtpCfg.byTopDirMode = 0xff;
            sprintf((char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.byTopCustomDir,"%s", m_csFirstUserDir);
        }

        m_struPublishCfg.struPublishAddr.struDirFtpCfg.bySubDirMode = m_comSecordDirMode.GetCurSel() +1;


        if ( m_struPublishCfg.struPublishAddr.struDirFtpCfg.bySubDirMode == 5)
        {
            m_struPublishCfg.struPublishAddr.struDirFtpCfg.bySubDirMode =0xff;
            sprintf((char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.bySubCustomDir,"%s", m_csSecordUserDir);
        }
    }

    if (m_bUploadByTime)
    {
        m_struPublishCfg.byUploadTime  = 2;
    }
    else
    {
        m_struPublishCfg.byUploadTime  = 1;
    }
    m_struPublishCfg.byTimerMode = m_cmbTimerMode.GetCurSel() +1;
    m_struPublishCfg.byUoploadStartMin = m_byMin;
    m_struPublishCfg.byUploadStartHour = m_byHour;
	char szLan[128] = {0};
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_RECORDING_PUBLISH_CFG,m_iStartChannel,&m_struPublishCfg,sizeof(m_struPublishCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORDING_PUBLISH_CFG,  %s", "Set record publish faild");
		g_StringLanType(szLan, "设置发布配置失败", "Get record publish cfg failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORDING_PUBLISH_CFG,  %s", "Set record publish sucess");
		g_StringLanType(szLan, "设置发布配置成功", "Set record publish sucess");
		AfxMessageBox(szLan);
	}
	return;
}

void DlgRecordPublishCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturnned = 0;
	char szLan[128] = {0};
	memset(&m_struPublishCfg,0,sizeof(m_struPublishCfg));
	if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_RECORDING_PUBLISH_CFG,m_iStartChannel,&m_struPublishCfg,sizeof(m_struPublishCfg),&dwReturnned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORDING_PUBLISH_CFG,  %s", "Get record publish faild");
		g_StringLanType(szLan, "获取发布配置失败", "Get record publish failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDING_PUBLISH_CFG,  %s", "Get Record record publish success");
		g_StringLanType(szLan, "获取发布配置成功", "Get record publish success");
		AfxMessageBox(szLan);
	}



	m_comPublishType.SetCurSel((UINT)m_struPublishCfg.byPublishType);

	if (m_struPublishCfg.byPublishType == 0)
	{
		m_comAddressType.SetCurSel(0);
		m_sUrl.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struHttpCfg.strUrl);
	}
	else if (m_struPublishCfg.byPublishType == 1)
	{
        m_comAddressType.SetCurSel(1);
        m_sIP.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struFtpCfg.byAddress);
        m_comProtocolType.SetCurSel((UINT)m_struPublishCfg.struPublishAddr.struFtpCfg.byProtocolType);
        m_nPort = (UINT)m_struPublishCfg.struPublishAddr.struFtpCfg.wFTPPort;
        m_sPath.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struFtpCfg.szCustomDir);
        m_sUserName.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struFtpCfg.szUserName);
		m_sPassword.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struFtpCfg.szPassWord);
	}
    else 
	{
		m_comAddressType.SetCurSel(2);
		m_sIP.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.byAddress);
		m_comProtocolType.SetCurSel((UINT)m_struPublishCfg.struPublishAddr.struFtpCfg.byProtocolType);
		m_nPort = (UINT)m_struPublishCfg.struPublishAddr.struDirFtpCfg.wFTPPort;
		m_sUserName.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.szUserName);
		m_sPassword.Format("%s",(char*)m_struPublishCfg.struPublishAddr.struDirFtpCfg.szPassWord);

        m_comDirLevel.SetCurSel(m_struPublishCfg.struPublishAddr.struDirFtpCfg.byDirLevel);
        if (m_struPublishCfg.struPublishAddr.struDirFtpCfg.byTopDirMode != 0xff)
        {
            m_comFirstDirMoe.SetCurSel(m_struPublishCfg.struPublishAddr.struDirFtpCfg.byTopDirMode -1);
        }
        else
        {
            m_comFirstDirMoe.SetCurSel(3);
            m_csFirstUserDir.Format("%s",m_struPublishCfg.struPublishAddr.struDirFtpCfg.byTopCustomDir); 
        }

        if ( m_struPublishCfg.struPublishAddr.struDirFtpCfg.bySubDirMode != 0xff)
        {
            m_comSecordDirMode.SetCurSel(m_struPublishCfg.struPublishAddr.struDirFtpCfg.bySubDirMode -1);
        }
        else
        {
            m_comSecordDirMode.SetCurSel(4);
            m_csSecordUserDir.Format("%s",m_struPublishCfg.struPublishAddr.struDirFtpCfg.bySubCustomDir); 
        }

	}

	m_comRecordChan.SetCurSel(0);

    if (m_struPublishCfg.byUploadTime == 2)
    {
    m_bUploadByTime = TRUE;
    }
    else
    {
    m_bUploadByTime = FALSE;
    }

    m_cmbTimerMode.SetCurSel(m_struPublishCfg.byTimerMode -1);
    if (m_struPublishCfg.byTimerMode == 2)
    {
        m_byMin = m_struPublishCfg.byUoploadStartMin;
        m_byHour = m_struPublishCfg.byUploadStartHour;
    }


	UpdateData(FALSE);
	OnSelchangeComboRecordChan();
	return;
}

void DlgRecordPublishCfg::OnBtnRecordOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_comRecordChan.GetItemData(m_comRecordChan.GetCurSel());
    if (sel == g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[0].iChannelNO)
    {
        m_struPublishCfg.struDirectChanPublish.byPublish = m_bRecordPublish;
        m_struPublishCfg.struDirectChanPublish.dwStreamType = 0;
        m_struPublishCfg.struDirectChanPublish.dwStreamType |= (m_bRecordMainStream << 0);
        m_struPublishCfg.struDirectChanPublish.dwStreamType |= (m_bRecordSubStream << 1);
        m_struPublishCfg.struDirectChanPublish.dwStreamType |= (m_bRecordStreamThree << 2);
    }
    else
    {
        sel = sel -1;
        m_struPublishCfg.struChanPublish[sel].byPublish = m_bRecordPublish;
        m_struPublishCfg.struChanPublish[sel].dwStreamType = 0;
        m_struPublishCfg.struChanPublish[sel].dwStreamType |= (m_bRecordMainStream << 0);
        m_struPublishCfg.struChanPublish[sel].dwStreamType |= (m_bRecordSubStream << 1);
        m_struPublishCfg.struChanPublish[sel].dwStreamType |= (m_bRecordStreamThree << 2);
    }
}

void DlgRecordPublishCfg::OnSelchangeComboRecordChan() 
{
	// TODO: Add your control notification handler code here
UpdateData(TRUE);
	int sel = m_comRecordChan.GetItemData(m_comRecordChan.GetCurSel());

    if (sel == g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[0].iChannelNO)
    {
        m_bRecordPublish = m_struPublishCfg.struDirectChanPublish.byPublish;
        m_bRecordMainStream = m_struPublishCfg.struDirectChanPublish.dwStreamType&0x01;
        m_bRecordSubStream = (m_struPublishCfg.struDirectChanPublish.dwStreamType >> 1)&0x01;
        m_bRecordStreamThree = (m_struPublishCfg.struDirectChanPublish.dwStreamType >> 2)&0x01;
    }
    else
    {
        m_bRecordPublish = m_struPublishCfg.struChanPublish[sel-1].byPublish;
        m_bRecordMainStream = m_struPublishCfg.struChanPublish[sel-1].dwStreamType&0x01;
        m_bRecordSubStream = (m_struPublishCfg.struChanPublish[sel-1].dwStreamType >> 1)&0x01;
        m_bRecordStreamThree = (m_struPublishCfg.struChanPublish[sel-1].dwStreamType >> 2)&0x01;
    }
	UpdateData(FALSE);
}

void DlgRecordPublishCfg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	sprintf((char*)m_struPublishCfg.struPublishAddr.struHttpCfg.strUrl,"%s",m_sUrl);
}

void DlgRecordPublishCfg::OnBtnBrowse() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*","*",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if (dlg.DoModal()==IDOK)
	{
		m_sPath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}