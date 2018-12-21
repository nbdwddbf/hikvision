// DlgPUStream.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPUStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPUStream dialog

/*********************************************************
  Function:	CDlgPUStream
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgPUStream::CDlgPUStream(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPUStream::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPUStream)
	m_bStreamValid = FALSE;
	m_iDvrPort = 0;
	m_csPassword = _T("");
	m_iStreamPort = 0;
	m_csUserName = _T("");
	m_iDvrChannel = 0;
	//}}AFX_DATA_INIT
	memset(&m_struPUStream, 0, sizeof(NET_DVR_PU_STREAM_CFG));
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgPUStream::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPUStream)
	DDX_Control(pDX, IDC_IPADDRESS_STREAM, m_ipStream);
	DDX_Control(pDX, IDC_IPADDRESS_DVR, m_ipDvr);
	DDX_Control(pDX, IDC_COMBO_STREAM_TRANSTYPE, m_comboStreamTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_TYPE, m_comboDvrTransMode);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_PROTOCOL, m_comboDvrTransProtocol);
	DDX_Check(pDX, IDC_CHECK_STREAM_VALID, m_bStreamValid);
	DDX_Text(pDX, IDC_EDIT_DVR_PORT, m_iDvrPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_STREAM_PORT, m_iStreamPort);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_DVR_CHANNEL, m_iDvrChannel);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgPUStream, CDialog)
	//{{AFX_MSG_MAP(CDlgPUStream)
	ON_BN_CLICKED(IDC_CHECK_STREAM_VALID, OnCheckStreamValid)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPUStream message handlers

/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgPUStream::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//week day and time are 1, while initializing
	GetPUStreamPara();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	GetPUStreamPara
  Desc:		Get correlative parameters of fetching stream 
  Input:	int iWeekday 
			int iTimePeriod
  Output:	
  Return:	
**********************************************************/
BOOL CDlgPUStream::GetPUStreamPara()
{
	//device channel info
    DWORD dwReturned = 0;
    if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG, m_lChannel, &m_struPUStream, sizeof(m_struPUStream), &dwReturned))	
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG %d", m_lChannel);
        AfxMessageBox("Fail to get NET_DVR_GET_PU_STREAMCFG");
        //		OnCancel();
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG %d", m_lChannel);
    }

	DWORD ipDvr = CStringTodwIP(m_struPUStream.struDevChanInfo.struIP.sIpV4);
	m_ipDvr.SetAddress(ipDvr);
	m_iDvrPort = m_struPUStream.struDevChanInfo.wDVRPort;
	m_iDvrChannel = m_struPUStream.struDevChanInfo.byChannel;
	m_comboDvrTransMode.SetCurSel(m_struPUStream.struDevChanInfo.byTransMode);
	m_comboDvrTransProtocol.SetCurSel(m_struPUStream.struDevChanInfo.byTransProtocol);

	BYTE byUserName[NAME_LEN + 1]   = {0};
	BYTE byPassWord[PASSWD_LEN + 1] = {0};
	memcpy((char*)byUserName,m_struPUStream.struDevChanInfo.sUserName, sizeof(BYTE) * NAME_LEN);
	memcpy((char*)byPassWord, m_struPUStream.struDevChanInfo.sPassword,sizeof(BYTE) * PASSWD_LEN);

	m_csUserName = byUserName;
	m_csPassword = byPassWord;
	
	//config of Streaming media server
	m_bStreamValid = m_struPUStream.struStreamMediaSvrCfg.byValid;
	EnableStream(m_bStreamValid);
	DWORD ipStream = CStringTodwIP(m_struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4);
	m_ipStream.SetAddress(ipStream);
	m_iStreamPort = m_struPUStream.struStreamMediaSvrCfg.wDevPort;
	m_comboStreamTransType.SetCurSel(m_struPUStream.struStreamMediaSvrCfg.byTransmitType);
	UpdateData(FALSE);
	return TRUE;
}

void CDlgPUStream::OnCheckStreamValid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableStream(m_bStreamValid);
	UpdateData(FALSE);
}

BOOL CDlgPUStream::EnableStream(BOOL bEnable)
{
	GetDlgItem(IDC_IPADDRESS_STREAM)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STREAM_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_STREAM_TRANSTYPE)->EnableWindow(bEnable);
	return TRUE;
}

void CDlgPUStream::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDlgPUStream::OnBtnConfirm() 
{
	// TODO: Add your control notification handler code here
	SetVcaIvmsSched();
    OnOK();
}

/*********************************************************
  Function:	SetVcaIvmsSched
  Desc:		Set IVMS parameters of getting stream
  Input:	int nWeekday
			int nTimePeriod
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgPUStream::SetVcaIvmsSched()
{
	UpdateData(TRUE);
	//device parameters
	DWORD ipDvr = 0;
	m_ipDvr.GetAddress(ipDvr);
	CString csTemp;
	csTemp = IPToStr(ipDvr);
	sprintf(m_struPUStream.struDevChanInfo.struIP.sIpV4, "%s", csTemp.GetBuffer(0));
	
	m_struPUStream.struDevChanInfo.wDVRPort = (WORD)m_iDvrPort;
	m_struPUStream.struDevChanInfo.byChannel = (BYTE)m_iDvrChannel;
	m_struPUStream.struDevChanInfo.byTransProtocol = (BYTE)m_comboDvrTransProtocol.GetCurSel();
	m_struPUStream.struDevChanInfo.byTransMode = (BYTE)m_comboDvrTransMode.GetCurSel();
	memset(m_struPUStream.struDevChanInfo.sUserName, 0, NAME_LEN*sizeof(BYTE));
	strncpy((char*)m_struPUStream.struDevChanInfo.sUserName, (char*)m_csUserName.GetBuffer(0), NAME_LEN);
	memset(m_struPUStream.struDevChanInfo.sPassword, 0, PASSWD_LEN*sizeof(BYTE));
	strncpy((char*)m_struPUStream.struDevChanInfo.sPassword, (char*)m_csPassword.GetBuffer(0), PASSWD_LEN);

	//Streaming media server
	m_struPUStream.struStreamMediaSvrCfg.byValid = m_bStreamValid;

	DWORD ipStream = 0;
	m_ipStream.GetAddress(ipStream);
	csTemp = IPToStr(ipStream);
	sprintf(m_struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4, "%s", csTemp.GetBuffer(0));
	
	m_struPUStream.struStreamMediaSvrCfg.wDevPort = (WORD)m_iStreamPort;
	m_struPUStream.struStreamMediaSvrCfg.byTransmitType = m_comboStreamTransType.GetCurSel();


    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PU_STREAMCFG, m_lChannel, &m_struPUStream, sizeof(m_struPUStream)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PU_STREAMCFG %d", m_lChannel);
        AfxMessageBox("Fail to set IVMS para");
        return FALSE;  
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PU_STREAMCFG %d", m_lChannel);
        return TRUE;
    }

}

