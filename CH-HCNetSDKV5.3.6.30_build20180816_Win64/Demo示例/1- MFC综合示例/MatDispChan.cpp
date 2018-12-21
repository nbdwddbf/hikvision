// MatDispChan.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatDispChan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DISP_TIMER	WM_USER + 1
/////////////////////////////////////////////////////////////////////////////
// CMatDispChan dialog
extern void g_IPToStr(DWORD dip, char outbuf[16]);

CMatDispChan::CMatDispChan(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDispChan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatDispChan)
	m_DIIP = _T("");
	m_DIChanNum = 0;
	m_DIUserName = _T("");
	m_DIPwd = _T("");
	m_FileName = _T("");
	m_CopyRate = 0;
	m_strStreamMediaIp = _T("");
	m_dwStreamMediaPort = 0;
	m_bUseStreamMedia = FALSE;
	m_dwPassivePort = 0;
	m_DIPort = 0;
	m_bUseUrl = FALSE;
	m_csUrl = _T("");
	m_strIpStreamId = _T("");
	m_dwDomainChannelNum = 0;
	m_strDomainName = _T("");
	m_strDomainRemoteName = _T("");
	m_strDomainRemotePass = _T("");
	m_strDomainServerIp = _T("");
	m_wDomainServerPort = 0;
	m_strDomainStreamID = _T("");
	m_strDomainStreamMediaIp = _T("");
	m_wDomainStreamMediaPort = 0;
	m_bDomainUseStreamMedia = FALSE;
	m_wDomainDevPort = 0;
	//}}AFX_DATA_INIT
	m_iChanSel = -1;
    memset(&m_struProtoList, 0, sizeof(m_struProtoList));
}


void CMatDispChan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDispChan)
	DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANSMODE, m_comboDomainTransMode);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANS_PRO, m_comboDomainTransPro);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_STREAMMEDIAPRO, m_comboDomainStreamMediaPro);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_SERVER_TYPE, m_comboDomainServerType);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_FACTYPE, m_comboDomainFacType);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_CHANNEL_TYPE, m_comboDomainChannelType);
	DDX_Control(pDX, IDC_COMBO_CHAN_TYPE, m_comboChannelType);
	DDX_Control(pDX, IDC_COMBO_STREAM_MODE, m_comboStreamMode);
	DDX_Control(pDX, IDC_COMBO_FACTYPE, m_FacTypeCtrl);
	DDX_Control(pDX, IDC_COMBOSTREAMTYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBOPASSIVETRANSPROTOL, m_ComboPassiveTransProtol);
	DDX_Control(pDX, IDC_COMBOSTREAMMEDIAPRO, m_ComboStreamMediaPro);
	DDX_Control(pDX, IDC_COMBOGETSTREAMMODE, m_ComboGetStreamMode);
	DDX_Control(pDX, IDC_COMBOISLINK, m_IsLinkCombo);
	DDX_Control(pDX, IDC_CHANCOMBO, m_ChanCombo);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_EndDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_StartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartDate);
	DDX_Control(pDX, IDC_TRANSMODECOMBO2, m_DIModeCombo);
	DDX_Control(pDX, IDC_PROTOCOLTYPECOMBO2, m_DIProTypeCombo);
	DDX_Control(pDX, IDC_COMBODECSTATE, m_DecStateCombo);
    DDX_Text(pDX, IDC_LINKIP2, m_DIIP);
	DDX_Text(pDX, IDC_LINKCHAN2, m_DIChanNum);
	DDX_Text(pDX, IDC_USERNAME2, m_DIUserName);
	DDX_Text(pDX, IDC_PASSWD2, m_DIPwd);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_EDITCOPYRATE, m_CopyRate);
	DDX_Text(pDX, IDC_STREAMMEDIAIP, m_strStreamMediaIp);
	DDX_Text(pDX, IDC_STREAMMEDIAPORT, m_dwStreamMediaPort);
	DDX_Check(pDX, IDC_USESTREAMMEDIA, m_bUseStreamMedia);
	DDX_Text(pDX, IDC_PASSIVEPORT, m_dwPassivePort);
	DDX_Text(pDX, IDC_LINKPORT2, m_DIPort);
	DDV_MinMaxDWord(pDX, m_DIPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_URL, m_csUrl);
	DDX_Text(pDX, IDC_EDIT_IP_STREAMID, m_strIpStreamId);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_CHANNEL_NUMBER, m_dwDomainChannelNum);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_NAME, m_strDomainName);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_REMOTENAME, m_strDomainRemoteName);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_REMOTEPASS, m_strDomainRemotePass);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_SERVER_IP, m_strDomainServerIp);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_SERVER_PORT, m_wDomainServerPort);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMID, m_strDomainStreamID);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMMEDIAIP, m_strDomainStreamMediaIp);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMMEDIAPORT2, m_wDomainStreamMediaPort);
	DDX_Check(pDX, IDC_CHK_DOMAIN_USESTREAMMEDIA, m_bDomainUseStreamMedia);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_DEV_PORT, m_wDomainDevPort);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CMatDispChan, CDialog)
	//{{AFX_MSG_MAP(CMatDispChan)
	ON_CBN_SELCHANGE(IDC_CHANCOMBO, OnSelchangeChancombo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_USESTREAMMEDIA, OnUsestreammedia)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM_MODE, OnSelchangeComboStreamMode)
	ON_BN_CLICKED(IDC_CHK_DOMAIN_USESTREAMMEDIA, OnChkDomainUsestreammedia)
	ON_CBN_SELCHANGE(IDC_COMBOGETSTREAMMODE, OnSelchangeCombogetstreammode)
	ON_CBN_SELCHANGE(IDC_COMBODECSTATE, OnSelchangeCombodecstate)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN_TYPE, OnSelchangeComboChanType)
	ON_CBN_SELCHANGE(IDC_COMBO_DOMAIN_CHANNEL_TYPE, OnSelchangeComboDomainChannelType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatDispChan message handlers

BOOL CMatDispChan::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString tmp;
	int i=0;
	int ChanNo = -1;
	char szLan[128] = {0};
	m_vGetStatus.resize(m_iChannelnumber);
	m_vbGetInfo.resize(m_iChannelnumber);
	TRACE("\nm_iChannelnumber = %d\n", m_iChannelnumber);

	
	for(i=0; i<m_iChannelnumber; i++)
	{
		ChanNo = m_lStartChan+i;
		g_StringLanType(szLan, "通道", "Chan");
		tmp.Format("%s %d", szLan, ChanNo);
		m_ChanCombo.AddString(tmp);
	
		GetChanStatus(ChanNo, i);
	}

	for (i=0; i<m_iChannelnumber; ++i)
	{
		if (m_vbGetInfo[i])
		{
			ShowChanInfo(i);
			if (m_vGetStatus[i])
			{
				m_IsLinkCombo.SetCurSel(m_DecChanStatus[i].dwIsLinked);
				TRACE("m_DecChanStatus[i].dwIsLinked = %d\n", m_DecChanStatus[i].dwIsLinked);
				m_CopyRate = m_DecChanStatus[i].dwStreamCpRate;
			}
			else
			{
				g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "Get Chan%d Status ERR ", i+m_lStartChan);
				AfxMessageBox(tmp);
			}
			break;
		}
	}

    if (NET_DVR_GetIPCProtoList(m_lServerID, &m_struProtoList))
    {
        for (int i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
        {
            memset(szLan, 0, DESC_LEN);
            memcpy(szLan, m_struProtoList.struProto[i].byDescribe, DESC_LEN);
            m_FacTypeCtrl.AddString(szLan);
			m_comboDomainFacType.AddString(szLan);
        }
        m_FacTypeCtrl.SetCurSel(0);
		m_comboDomainFacType.SetCurSel(0);
    } 

    m_ChanCombo.SetCurSel(0);
	OnSelchangeChancombo();
	UpdateData(FALSE);

	SetTimer(DISP_TIMER, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMatDispChan::GetChanStatus(DWORD DecChanNum, int index)
{
	CString tmp;

	ZeroMemory(&m_DecChanStatus[index], sizeof(m_DecChanStatus[index]));
	m_DecChanStatus->dwSize = sizeof(m_DecChanStatus[index]);
	if (!NET_DVR_MatrixGetDecChanStatus(m_lServerID, DecChanNum, &m_DecChanStatus[index]))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_MatrixGetDecChanStatus");	
        //MessageBox("NET_DVR_MatrixGetDecChanStatus failed");
		m_vGetStatus[index] = FALSE;
	}
	else
	{
       //  MessageBox("NET_DVR_MatrixGetDecChanStatus succ");
		m_vGetStatus[index] = TRUE;
	}

	ZeroMemory(&m_DecChanInfo[index], sizeof(m_DecChanInfo[index]));
	m_DecChanInfo[index].dwSize = sizeof(m_DecChanInfo[index]);
	if (!NET_DVR_MatrixGetDecChanInfo_V41(m_lServerID, DecChanNum, &m_DecChanInfo[index]))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_MatrixGetDecChanInfo");
        //TRACE("获取NET_DVR_MatrixGetDecChanInfo_V41 错误:%d", NET_DVR_GetLastError());
		m_vbGetInfo[index] = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_MatrixGetDecChanInfo");
        //TRACE("NET_DVR_MatrixGetDecChanInfo_V41 成功");
		m_vbGetInfo[index] = TRUE;
	}

	return TRUE;
}

void CMatDispChan::ShowChanInfo(int index)
{
	int i = 0;
	if(index < 0 || index > m_iChannelnumber-1)
	{
		return;
	}

	UpdateData(TRUE);
	CString tmp;
	if(!m_vbGetInfo[index])
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "m_vbGetInfo false %d Err!", index + m_lStartChan);
	}
	else
	{
		m_ComboGetStreamMode.SetCurSel(m_DecChanInfo[index].dwGetStreamMode - 1);
		OnSelchangeCombogetstreammode();
		m_comboStreamMode.SetCurSel(m_DecChanInfo[index].byStreamMode);
		m_DecStateCombo.SetCurSel(m_DecChanInfo[index].dwPlayMode);
		OnSelchangeCombodecstate();
		
		switch (m_DecChanInfo[index].byStreamMode)
		{
		case 0:
			break;
		case 1:		/*IP或域名取流*/
			m_comboChannelType.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChanType);
			UpdateData(FALSE);
			OnSelchangeComboChanType();
			m_strIpStreamId.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byStreamId);
			m_DIIP.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress);
			m_DIPort = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort;
			m_DIChanNum = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel;
			m_DIProTypeCombo.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol);
			m_DIModeCombo.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode);

			for(i = 0; i < m_struProtoList.dwProtoNum; i++)
			{
				if (m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType == m_struProtoList.struProto[i].dwType) 
				{
					m_FacTypeCtrl.SetCurSel(i);
					break;
				}
			}
			
			m_DIUserName.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName);
			m_DIPwd.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword);
						
			m_bUseStreamMedia = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid;
			if (m_bUseStreamMedia)
			{
				m_strStreamMediaIp.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress);
				m_dwStreamMediaPort = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort;
				m_ComboStreamMediaPro.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType);
			}
			break;
		case 2:		/*URL取流*/
			m_csUrl.Format("%s", m_DecChanInfo[index].uDecStreamMode.struUrlInfo.strURL);
			break;
		case 3:		/*DDNS动态取流*/
			m_strDomainName.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDevAddress);
			m_wDomainDevPort = m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDevPort;
			m_comboDomainServerType.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsType);
			m_strDomainServerIp.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsAddress);
			m_wDomainServerPort = m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDdnsPort;
			m_comboDomainTransPro.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransProtocol);
			m_comboDomainTransMode.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransMode);
			m_strDomainRemoteName.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sUserName);
			m_strDomainRemotePass.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sPassword);
			m_comboDomainChannelType.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byChanType);
			
			for(i = 0; i < m_struProtoList.dwProtoNum; i++)
			{
				if (m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byFactoryType == m_struProtoList.struProto[i].dwType) 
				{
					m_comboDomainFacType.SetCurSel(i);
					break;
				}
			}
			//m_comboDomainFacType.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byFactoryType);
			m_strDomainStreamID.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byStreamId);
			m_dwDomainChannelNum = m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.dwChannel;
			
			m_bDomainUseStreamMedia = m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struMediaServer.byValid;
			if (m_bDomainUseStreamMedia)
			{
				m_strDomainStreamMediaIp.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struMediaServer.byAddress);
				m_wDomainStreamMediaPort = m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struMediaServer.wDevPort;
				m_comboDomainStreamMediaPro.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDdnsDecInfo.struMediaServer.byTransmitType);
			}
			break;
		default:
			break;
		}
		UpdateData(FALSE);
		m_comboStreamMode.SetCurSel(m_DecChanInfo[index].byStreamMode);
		OnSelchangeComboStreamMode();
		
		if (m_DecChanInfo[index].dwPlayMode == 2)
		{
			SYSTEMTIME sysTime;
			ZeroMemory(&sysTime, sizeof(sysTime));
			sysTime.wYear = (WORD)m_DecChanInfo[index].StartTime.dwYear;
			sysTime.wMonth = (WORD)m_DecChanInfo[index].StartTime.dwMonth;
			sysTime.wDay = (WORD)m_DecChanInfo[index].StartTime.dwDay;
			sysTime.wHour = (WORD)m_DecChanInfo[index].StartTime.dwHour;
			sysTime.wMinute = (WORD)m_DecChanInfo[index].StartTime.dwMinute;
			sysTime.wSecond = (WORD)m_DecChanInfo[index].StartTime.dwSecond;
			m_StartDate.SetTime(&sysTime);
			m_StartTime.SetTime(&sysTime);
			ZeroMemory(&sysTime, sizeof(sysTime));
			sysTime.wYear = (WORD)m_DecChanInfo[index].StopTime.dwYear;
			sysTime.wMonth = (WORD)m_DecChanInfo[index].StopTime.dwMonth;
			sysTime.wDay = (WORD)m_DecChanInfo[index].StopTime.dwDay;
			sysTime.wHour = (WORD)m_DecChanInfo[index].StopTime.dwHour;
			sysTime.wMinute = (WORD)m_DecChanInfo[index].StopTime.dwMinute;
			sysTime.wSecond = (WORD)m_DecChanInfo[index].StopTime.dwSecond;
			m_EndDate.SetTime(&sysTime);
			m_EndTime.SetTime(&sysTime);

			m_FileName.Empty();
		}
		else if (m_DecChanInfo[index].dwPlayMode == 3)
		{
			m_FileName.Format("%s", m_DecChanInfo[index].sFileName);
			
			CTime now = CTime::GetCurrentTime();
			m_StartDate.SetTime(&now);
			m_StartTime.SetTime(&now);
			m_EndDate.SetTime(&now);
			m_EndTime.SetTime(&now);
		}
		else
		{
			CTime now = CTime::GetCurrentTime();
			m_StartDate.SetTime(&now);
			m_StartTime.SetTime(&now);
			m_EndDate.SetTime(&now);
			m_EndTime.SetTime(&now);
			m_FileName.Empty();
		}
        TRACE("lll ----- m_DecChanInfo[index].struPassiveMode.wTransProtol = %d", m_DecChanInfo[index].struPassiveMode.wTransProtol);
        m_ComboPassiveTransProtol.SetCurSel(m_DecChanInfo[index].struPassiveMode.wTransProtol);
        m_dwPassivePort = m_DecChanInfo[index].struPassiveMode.wPassivePort;
        m_comboStreamType.SetCurSel(m_DecChanInfo[index].struPassiveMode.byStreamType - 1);
	}
	UpdateData(FALSE);
}

void CMatDispChan::OnSelchangeChancombo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_ChanCombo.GetCurSel();
	
	ShowChanInfo(sel);
	if (!m_vGetStatus[sel])
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "GetChanStatus %d Err!", sel + m_lStartChan);
	}
	else
	{
		m_IsLinkCombo.SetCurSel(m_DecChanStatus[sel].dwIsLinked);
		m_CopyRate = m_DecChanStatus[sel].dwStreamCpRate;
	}
	
	UpdateData(FALSE);
    
}

#if (_MSC_VER >= 1500)	//vs2008
void CMatDispChan::OnTimer(UINT_PTR nIDEvent)
#else
void CMatDispChan::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == DISP_TIMER)
	{
		UpdateData(TRUE);
		int sel = m_ChanCombo.GetCurSel();

		GetChanStatus(sel+m_lStartChan, sel);

		ShowChanInfo(sel);

		UpdateData(TRUE);
		if (!m_vGetStatus[sel])
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "GetChanStatus %d Err!", sel + m_lStartChan);
		}
		else
		{
			m_IsLinkCombo.SetCurSel(m_DecChanStatus[sel].dwIsLinked);
			TRACE("m_DecChanStatus[i].dwIsLinked = %d\n", m_DecChanStatus[sel].dwIsLinked);
			m_CopyRate = m_DecChanStatus[sel].dwStreamCpRate;
		}

		UpdateData(FALSE);
       
	}

	CDialog::OnTimer(nIDEvent);
}

void CMatDispChan::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(DISP_TIMER);

	CDialog::OnCancel();
}

void CMatDispChan::OnUsestreammedia() 
{
	UpdateData(TRUE);
    if (m_bUseStreamMedia)
    {
        GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(TRUE);
        GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(TRUE);
		UpdateData(FALSE);
    }
    else
    {
        GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(FALSE);
        GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(FALSE);
    }	
    UpdateData(FALSE);	
}

void CMatDispChan::EnableIpOrDomainGroup(BOOL IsEnable)
{
	
	UINT id[]={IDC_LINKIP2, IDC_LINKPORT2, IDC_LINKCHAN2, IDC_COMBO_FACTYPE, IDC_USERNAME2, IDC_PASSWD2, IDC_TRANSMODECOMBO2, IDC_PROTOCOLTYPECOMBO2,\
				IDC_COMBO_CHAN_TYPE, IDC_EDIT_IP_STREAMID, IDC_USESTREAMMEDIA, IDC_STREAMMEDIAIP, IDC_STREAMMEDIAPORT, IDC_COMBOSTREAMMEDIAPRO};
	for (int i = 0; i < sizeof(id)/sizeof(UINT); i++)
	{
		GetDlgItem(id[i])->EnableWindow(IsEnable);
	}
	
	if (IsEnable)
	{
		OnUsestreammedia();
		OnSelchangeComboChanType();
	}
}

void CMatDispChan::EnableURLGroup(BOOL IsEnable)
{
	GetDlgItem(IDC_EDIT_URL)->EnableWindow(IsEnable);
}

void CMatDispChan::EnableDynamicDDNSGroup(BOOL IsEnable)
{
	
	UINT id[]={IDC_EDIT_DOMAIN_NAME, IDC_EDIT_DOMAIN_DEV_PORT, IDC_COMBO_DOMAIN_SERVER_TYPE, IDC_EDIT_DOMAIN_SERVER_IP, IDC_EDIT_DOMAIN_SERVER_PORT, IDC_COMBO_DOMAIN_TRANS_PRO,\
		IDC_COMBO_DOMAIN_TRANSMODE, IDC_EDIT_DOMAIN_REMOTENAME, IDC_EDIT_DOMAIN_REMOTEPASS, IDC_COMBO_DOMAIN_CHANNEL_TYPE, IDC_COMBO_DOMAIN_FACTYPE,\
		IDC_EDIT_DOMAIN_STREAMID, IDC_EDIT_DOMAIN_CHANNEL_NUMBER, IDC_CHK_DOMAIN_USESTREAMMEDIA, IDC_EDIT_DOMAIN_STREAMMEDIAIP, IDC_EDIT_DOMAIN_STREAMMEDIAPORT2, IDC_COMBO_DOMAIN_STREAMMEDIAPRO};
	for (int i = 0; i < sizeof(id)/sizeof(UINT); i++)
	{
		GetDlgItem(id[i])->EnableWindow(IsEnable);
	}
	if (IsEnable)
	{
		OnChkDomainUsestreammedia();
		OnSelchangeComboDomainChannelType();
	}
}

void CMatDispChan::OnSelchangeComboStreamMode() 
{
	switch (m_comboStreamMode.GetCurSel())
	{
	case 0: /*无效*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 1:	/*IP或域名取流*/
		EnableIpOrDomainGroup(TRUE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 2:	/*URL取流*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(TRUE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 3:	/*动态域名解析取流*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(TRUE);
		break;
	default:
		break;
	}	
}

void CMatDispChan::OnChkDomainUsestreammedia() 
{
	UpdateData(TRUE);
    if (m_bDomainUseStreamMedia)
    {
        GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAIP)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAPORT2)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_DOMAIN_STREAMMEDIAPRO)->EnableWindow(TRUE);
		UpdateData(FALSE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAIP)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAPORT2)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_DOMAIN_STREAMMEDIAPRO)->EnableWindow(FALSE);
    }	
    UpdateData(FALSE);	
}

void CMatDispChan::OnSelchangeCombogetstreammode() 
{
	int isel = m_ChanCombo.GetCurSel();
	if (m_ComboGetStreamMode.GetCurSel() == 0)/*主动解码*/
	{
		GetDlgItem(IDC_COMBOPASSIVETRANSPROTOL)->EnableWindow(FALSE);
		GetDlgItem(IDC_PASSIVEPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBOSTREAMTYPE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_COMBOPASSIVETRANSPROTOL)->EnableWindow(TRUE);
		GetDlgItem(IDC_PASSIVEPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBOSTREAMTYPE)->EnableWindow(TRUE);

		m_ComboPassiveTransProtol.SetCurSel(m_DecChanInfo[isel].struPassiveMode.wTransProtol);
		m_dwPassivePort = m_DecChanInfo[isel].struPassiveMode.wTransProtol;
		m_comboStreamType.SetCurSel(m_DecChanInfo[isel].struPassiveMode.byStreamType);

	}
	
}

void CMatDispChan::OnSelchangeCombodecstate() 
{
	UINT id[] = {IDC_RADIO_PLAY_BY_TIME, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER2, IDC_DATETIMEPICKER3, IDC_DATETIMEPICKER4, IDC_RADIO_PLAY_BY_NAME, IDC_FILENAME};
	for (int i = 0; i< sizeof(id)/sizeof(UINT); i++)
	{
		GetDlgItem(id[i])->EnableWindow(FALSE);
	}
	((CButton*)GetDlgItem(IDC_RADIO_PLAY_BY_TIME))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_PLAY_BY_NAME))->SetCheck(FALSE);

	switch (m_DecStateCombo.GetCurSel())
	{
	case 0:			/*动态解码*/
		break;
	case 1:			/*轮训*/
		break;
	case 2:			/*按时间回放*/
		((CButton*)GetDlgItem(IDC_RADIO_PLAY_BY_TIME))->SetCheck(TRUE);
		GetDlgItem(IDC_RADIO_PLAY_BY_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER3)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(TRUE);
		break;
	case 3:			/*按文件回放*/
		((CButton*)GetDlgItem(IDC_RADIO_PLAY_BY_NAME))->SetCheck(TRUE);
		GetDlgItem(IDC_RADIO_PLAY_BY_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_FILENAME)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
	
}

void CMatDispChan::OnSelchangeComboChanType() 
{
	UpdateData(TRUE);
	
	GetDlgItem(IDC_LINKCHAN2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_IP_STREAMID)->EnableWindow(FALSE);
	switch (m_comboChannelType.GetCurSel())
	{
	case 0:
	case 1:
		break;
	case 2:
		GetDlgItem(IDC_EDIT_IP_STREAMID)->EnableWindow(TRUE);
		GetDlgItem(IDC_LINKCHAN2)->EnableWindow(FALSE);
		break;
	default:
		break;
	}
		UpdateData(FALSE);
	
}

void CMatDispChan::OnSelchangeComboDomainChannelType() 
{
	UpdateData(TRUE);
	
	GetDlgItem(IDC_EDIT_DOMAIN_CHANNEL_NUMBER)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DOMAIN_STREAMID)->EnableWindow(FALSE);
	switch (m_comboDomainChannelType.GetCurSel())
	{
	case 0:
	case 1:
		break;
	case 2:
		GetDlgItem(IDC_EDIT_DOMAIN_STREAMID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOMAIN_CHANNEL_NUMBER)->EnableWindow(FALSE);
		break;
	default:
		break;
	}
		UpdateData(FALSE);
	
}
