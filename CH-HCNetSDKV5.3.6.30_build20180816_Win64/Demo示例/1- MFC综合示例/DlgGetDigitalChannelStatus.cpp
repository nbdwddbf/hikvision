// DlgGetDigitalChannelStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGetDigitalChannelStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGetDigitalChannelStatus dialog


CDlgGetDigitalChannelStatus::CDlgGetDigitalChannelStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetDigitalChannelStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGetDigitalChannelStatus)
	m_strDChannelStatus = _T("");
	//}}AFX_DATA_INIT
}


void CDlgGetDigitalChannelStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGetDigitalChannelStatus)
	DDX_Text(pDX, IDC_EDIT_CHANNEL_STATUS, m_strDChannelStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGetDigitalChannelStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgGetDigitalChannelStatus)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGetDigitalChannelStatus message handlers

void CDlgGetDigitalChannelStatus::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	m_strDChannelStatus = "";

	NET_DVR_DIGITAL_CHANNEL_STATE struDChannelState = {0};
	DWORD dwReturnValue = 0; 
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DIGITAL_CHANNEL_STATE, 0, &struDChannelState, sizeof(struDChannelState), &dwReturnValue))
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "»ñÈ¡Ê§°Ü!", "Fail to Get !");
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
        AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
	}
	
    NET_DVR_DIGITAL_CHANNEL_SECURITY_STATUS struSecurityStatus = {0};
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DIGITAL_CHAN_SECURITY_STATUS, 0, &struSecurityStatus, sizeof(struSecurityStatus), &dwReturnValue))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DIGITAL_CHAN_SECURITY_STATUS");
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DIGITAL_CHAN_SECURITY_STATUS");
    }

	CString strTemp;
    int i = 0;
	for (i=0; i<64; i++)
	{
		switch (struDChannelState.byDigitalChanState[i])
        {
        case NET_SDK_DC_STATUS_CONNECTED:
            strTemp.Format("DigitalChanState[%d] is Connected\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_CONNECTING:
            strTemp.Format("DigitalChanState[%d] is Connecting\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_BAND_WIDTH_EXCEED:
            strTemp.Format("DigitalChanState[%d] is Band Width Exceed\r\n",  i );
            break;
        case NET_SDK_DC_STATUS_DOMAIN_ERROR:
            strTemp.Format("DigitalChanState[%d] is Domain Error\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_CHANNEL_ERROR:
            strTemp.Format("DigitalChanState[%d] is Channel Error\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_ACCOUNT_ERROR:
            strTemp.Format("DigitalChanState[%d] is Account Error\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_STREAM_TYPE_NOT_SUPPORT:
            strTemp.Format("DigitalChanState[%d] is not support Stream Type \r\n",  i);
            break;
        case NET_SDK_DC_STATUS_CONFLICT_WITH_DVR:
            strTemp.Format("DigitalChanState[%d] is Conflict With Dvr\r\n",  i);
            break;
			
        case NET_SDK_DC_STATUS_CONFLICT_WITH_IPC:
            strTemp.Format("DigitalChanState[%d] is Conflict with IPC\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_NETWORK_UNREACHBALE:
            strTemp.Format("DigitalChanState[%d] is NetWork Unreachbale\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_IPC_NOT_EXIST:
            strTemp.Format("DigitalChanState[%d] is IPC not Exit\r\n",  i);
            break;
            
        case NET_SDK_DC_STATUS_IPC_EXCEPTION:
            strTemp.Format("DigitalChanState[%d] is IPC Exception\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_RESOLUTION_NOT_SUPPORT:
            strTemp.Format("DigitalChanState[%d] is Not Support Resolution \r\n",  i);
            break;
        case NET_SDK_DC_STATUS_OTHER_ERROR:
            strTemp.Format("DigitalChanState[%d] is Other Error \r\n",  i);
            break;
        case NET_SDK_DC_STATUS_IPC_LAN_ERR :
            strTemp.Format("DigitalChanState[%d] is language mismatch\r\n", i);
            break;
        case NET_SDK_DC_STATUS_USER_LOCKED:
            strTemp.Format("DigitalChanState[%d] is user locked\r\n", i);
            break;
        case NET_SDK_DC_STATUS_NOT_ACTIVATED:
            strTemp.Format("DigitalChanState[%d] is not activated\r\n",  i);
            break;
        case NET_SDK_DC_STATUS_USER_NOT_EXIST:
            strTemp.Format("DigitalChanState[%d] is user not exist\r\n", i);
            break;
        case NET_SDK_DC_STATUS_IPC_UNREGISTERED:
            strTemp.Format("DigitalChanState[%d] is ipc unregistered\r\n", i);
            break;
        case NET_SDK_DC_STATUS_POE_PORT_DETECTING:
            strTemp.Format("DigitalChanState[%d] is poe port detecting\r\n", i);
            break;
        default:
            strTemp.Format("DigitalChanState[%d] is UnKnown Error \r\n",  i);
            break;
        }
        m_strDChannelStatus += strTemp;
        strTemp.Format("DigitalChanState[%d] security status is[%d]\r\n", i, struSecurityStatus.byDigitalChanPasswordStatus[i]);
        m_strDChannelStatus += strTemp;
    }
	
	for (i = 0; i < MAX_CHANNUM_V30*3; i++)
	{
		switch (struDChannelState.byDigitalChanStateEx[i])
        {
        case NET_SDK_DC_STATUS_CONNECTING:
            strTemp.Format("DigitalChanState[%d] is Connected\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_BAND_WIDTH_EXCEED:
            strTemp.Format("DigitalChanState[%d] is Band Width Exceed\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_DOMAIN_ERROR:
            strTemp.Format("DigitalChanState[%d] is Domain Error\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_CHANNEL_ERROR:
            strTemp.Format("DigitalChanState[%d] is Channel Error\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_ACCOUNT_ERROR:
            strTemp.Format("DigitalChanState[%d] is Account Error\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_STREAM_TYPE_NOT_SUPPORT:
            strTemp.Format("DigitalChanState[%d] is not support Stream Type \r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_CONFLICT_WITH_DVR:
            strTemp.Format("DigitalChanState[%d] is Conflict With Dvr\r\n",  i+64);
            break;
			
        case NET_SDK_DC_STATUS_CONFLICT_WITH_IPC:
            strTemp.Format("DigitalChanState[%d] is Conflict with IPC\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_NETWORK_UNREACHBALE:
            strTemp.Format("DigitalChanState[%d] is NetWork Unreachbale\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_IPC_NOT_EXIST:
            strTemp.Format("DigitalChanState[%d] is IPC not Exit\r\n",  i+64);
            break;
            
        case NET_SDK_DC_STATUS_IPC_EXCEPTION:
            strTemp.Format("DigitalChanState[%d] is IPC Exception\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_RESOLUTION_NOT_SUPPORT:
            strTemp.Format("DigitalChanState[%d] is Not Support Resolution \r\n", i+64);
            break;
        case NET_SDK_DC_STATUS_OTHER_ERROR:
            strTemp.Format("DigitalChanState[%d] is Other Error \r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_IPC_LAN_ERR :
            strTemp.Format("DigitalChanState[%d] is language mismatch\r\n", i+64);
            break;
        case NET_SDK_DC_STATUS_USER_LOCKED:
            strTemp.Format("DigitalChanState[%d] is user locked\r\n", i+64);
            break;
        case NET_SDK_DC_STATUS_NOT_ACTIVATED:
            strTemp.Format("DigitalChanState[%d] is not activated\r\n",  i+64);
            break;
        case NET_SDK_DC_STATUS_USER_NOT_EXIST:
            strTemp.Format("DigitalChanState[%d] is user not exist\r\n", i+64);
            break;
        case NET_SDK_DC_STATUS_IPC_UNREGISTERED:
            strTemp.Format("DigitalChanState[%d] is ipc unregistered\r\n", i+64);
            break;
        default:
            strTemp.Format("DigitalChanState[%d] is UnKnown Error \r\n",  i+64);
            break;
        }
        m_strDChannelStatus += strTemp;
        strTemp.Format("DigitalChanState[%d] security status is[%d]\r\n", i+64, struSecurityStatus.byDigitalChanPasswordStatus[i+64]);
        m_strDChannelStatus += strTemp;
	}
	
	UpdateData(FALSE);
}

BOOL CDlgGetDigitalChannelStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
