/**********************************************************
FileName:    DlgVcaIvmsSched.cpp
Description: IVMS Stream schedule    
Date:        2009/07/10
Note: 		
    <version> <time>         <desc>
    <1.0    > <2009/07/10>       <created>
***********************************************************/
// DlgVcaIvmsSched.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaIvmsSched.h"
#include "DlgVcaIvmsCfg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaIvmsSched dialog
extern CDlgVcaIvmsCfg *g_pDlgVcaIvmsCfg;

/*********************************************************
  Function:	CDlgVcaIvmsSched
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgVcaIvmsSched::CDlgVcaIvmsSched(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaIvmsSched::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaIvmsSched)
	m_bStreamValid = FALSE;
	m_iDvrPort = 0;
	m_csPassword = _T("");
	m_iStreamPort = 0;
	m_csUserName = _T("");
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iDvrChannel = 0;
	//}}AFX_DATA_INIT
	memset(&m_struTime, 0, sizeof(NET_DVR_SCHEDTIME));
	memset(&m_struPUStream, 0, sizeof(NET_DVR_PU_STREAM_CFG));
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVcaIvmsSched::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaIvmsSched)
	DDX_Control(pDX, IDC_IPADDRESS_STREAM, m_ipStream);
	DDX_Control(pDX, IDC_IPADDRESS_DVR, m_ipDvr);
	DDX_Control(pDX, IDC_COMBO_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_TIME_PERIOD, m_comboTimePeriod);
	DDX_Control(pDX, IDC_COMBO_STREAM_TRANSTYPE, m_comboStreamTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_TYPE, m_comboDvrTransMode);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_PROTOCOL, m_comboDvrTransProtocol);
	DDX_Check(pDX, IDC_CHECK_STREAM_VALID, m_bStreamValid);
	DDX_Text(pDX, IDC_EDIT_DVR_PORT, m_iDvrPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_STREAM_PORT, m_iStreamPort);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
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
BEGIN_MESSAGE_MAP(CDlgVcaIvmsSched, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaIvmsSched)
	ON_BN_CLICKED(IDC_CHECK_STREAM_VALID, OnCheckStreamValid)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, OnSelchangeComboWeekday)
	ON_CBN_SELCHANGE(IDC_COMBO_TIME_PERIOD, OnSelchangeComboTimePeriod)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaIvmsSched message handlers

/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgVcaIvmsSched::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//week day and time are 1, while initializing
	m_comboWeekday.SetCurSel(0);
	m_comboTimePeriod.SetCurSel(0);

	GetPUStreamPara(0,0);

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
BOOL CDlgVcaIvmsSched::GetPUStreamPara(int iWeekday = 0, int iTimePeriod = 0)
{
	memcpy(&m_struTime, &g_pDlgVcaIvmsCfg->m_struIVMSStreamCfg.struDevSched[iWeekday][iTimePeriod].struTime,
		sizeof(NET_DVR_SCHEDTIME));
	m_iHour11 = m_struTime.byStartHour;
	m_iHour12 = m_struTime.byStopHour;
	m_iMin11 = m_struTime.byStartMin;
	m_iMin12 = m_struTime.byStopMin;
	
	memcpy(&m_struPUStream, &g_pDlgVcaIvmsCfg->m_struIVMSStreamCfg.struDevSched[iWeekday][iTimePeriod].struPUStream,
		sizeof(NET_DVR_PU_STREAM_CFG));
	
	//device channel info
	DWORD ipDvr = CStringTodwIP(m_struPUStream.struDevChanInfo.struIP.sIpV4);
	m_ipDvr.SetAddress(ipDvr);
	m_iDvrPort = m_struPUStream.struDevChanInfo.wDVRPort;
	m_iDvrChannel = m_struPUStream.struDevChanInfo.byChannel;
	m_comboDvrTransMode.SetCurSel(m_struPUStream.struDevChanInfo.byTransMode);
	m_comboDvrTransProtocol.SetCurSel(m_struPUStream.struDevChanInfo.byTransProtocol);
	m_csUserName = m_struPUStream.struDevChanInfo.sUserName;
	m_csPassword = m_struPUStream.struDevChanInfo.sPassword;
	
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

void CDlgVcaIvmsSched::OnCheckStreamValid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableStream(m_bStreamValid);
	UpdateData(FALSE);
}

BOOL CDlgVcaIvmsSched::EnableStream(BOOL bEnable)
{
	GetDlgItem(IDC_IPADDRESS_STREAM)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STREAM_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_STREAM_TRANSTYPE)->EnableWindow(bEnable);
	return TRUE;
}

void CDlgVcaIvmsSched::OnSelchangeComboWeekday() 
{
	// TODO: Add your control notification handler code here
	int nWeekday = m_comboWeekday.GetCurSel();
	int nTimePeriod = m_comboTimePeriod.GetCurSel();	
	GetPUStreamPara(nWeekday, nTimePeriod);
}

void CDlgVcaIvmsSched::OnSelchangeComboTimePeriod() 
{
	// TODO: Add your control notification handler code here
	int nWeekday = m_comboWeekday.GetCurSel();
	int nTimePeriod = m_comboTimePeriod.GetCurSel();
	GetPUStreamPara(nWeekday, nTimePeriod);
}

void CDlgVcaIvmsSched::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDlgVcaIvmsSched::OnBtnConfirm() 
{
	// TODO: Add your control notification handler code here
	int nWeekday = m_comboWeekday.GetCurSel();
	int nTimePeriod = m_comboTimePeriod.GetCurSel();
	SetVcaIvmsSched(nWeekday,nTimePeriod);
}

/*********************************************************
  Function:	SetVcaIvmsSched
  Desc:		Set IVMS parameters of getting stream
  Input:	int nWeekday
			int nTimePeriod
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsSched::SetVcaIvmsSched(int nWeekday, int nTimePeriod)
{
	UpdateData(TRUE);
	m_struTime.byStartHour = (BYTE)m_iHour11; 
	m_struTime.byStartMin = (BYTE)m_iMin11;
	m_struTime.byStopHour = (BYTE)m_iHour12;
	m_struTime.byStopMin = (BYTE)m_iMin12;
	memcpy(&g_pDlgVcaIvmsCfg->m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struTime,
		&m_struTime, sizeof(NET_DVR_SCHEDTIME));
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
	strncpy((char*)m_struPUStream.struDevChanInfo.sUserName, (char*)m_csUserName.GetBuffer(0), NAME_LEN-1);
	memset(m_struPUStream.struDevChanInfo.sPassword, 0, PASSWD_LEN*sizeof(BYTE));
	strncpy((char*)m_struPUStream.struDevChanInfo.sPassword, (char*)m_csPassword.GetBuffer(0), PASSWD_LEN-1);

	//Streaming media server
	m_struPUStream.struStreamMediaSvrCfg.byValid = m_bStreamValid;

	DWORD ipStream = 0;
	m_ipStream.GetAddress(ipStream);
	csTemp = IPToStr(ipStream);
	sprintf(m_struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4, "%s", csTemp.GetBuffer(0));
	
	m_struPUStream.struStreamMediaSvrCfg.wDevPort = (WORD)m_iStreamPort;
	m_struPUStream.struStreamMediaSvrCfg.byTransmitType = m_comboStreamTransType.GetCurSel();

	memcpy(&g_pDlgVcaIvmsCfg->m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struPUStream,
		&m_struPUStream, sizeof(NET_DVR_PU_STREAM_CFG));

	return TRUE;	
}

