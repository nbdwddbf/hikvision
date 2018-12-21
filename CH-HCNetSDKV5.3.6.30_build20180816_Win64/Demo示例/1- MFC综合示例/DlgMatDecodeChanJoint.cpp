// DlgMatDecodeChanJoint.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMatDecodeChanJoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMatDecodeChanJoint dialog


CDlgMatDecodeChanJoint::CDlgMatDecodeChanJoint(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMatDecodeChanJoint::IDD, pParent)
, m_iDeviceIndex(-1)
, m_lUserID(-1)
{
	//{{AFX_DATA_INIT(CDlgMatDecodeChanJoint)
	m_chJoint = FALSE;
	m_dwChanNum = 0;
	m_csIPV6 = _T("");
	m_dwPort = 0;
	m_csJointChanName = _T("");
	m_csJointDevName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgMatDecodeChanJoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMatDecodeChanJoint)
	DDX_Control(pDX, IDC_IPADDRESS_IPV4, m_IPV4);
	DDX_Control(pDX, IDC_COMBO_CHANNUM, m_cmChanNum);
	DDX_Check(pDX, IDC_CHECK_JONINT, m_chJoint);
	DDX_Text(pDX, IDC_EDIT_DECODECHAN_JOINT, m_dwChanNum);
	DDV_MinMaxDWord(pDX, m_dwChanNum, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_IPV6, m_csIPV6);
	DDX_Text(pDX, IDC_EDIT_PORT_JOINT, m_dwPort);
	DDV_MinMaxDWord(pDX, m_dwPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_JOINT_CHAN_NAME, m_csJointChanName);
	DDX_Text(pDX, IDC_EDIT_JOINT_DEV_NAME, m_csJointDevName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMatDecodeChanJoint, CDialog)
	//{{AFX_MSG_MAP(CDlgMatDecodeChanJoint)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNUM, OnSelchangeComboChannum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMatDecodeChanJoint message handlers

BOOL CDlgMatDecodeChanJoint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	int i = 0;
	CString csStr;
	for (i=0; i<16; i++)
	{
		csStr.Format("%d", i+1);
		m_cmChanNum.AddString(csStr);
	}
	m_cmChanNum.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboChannum();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMatDecodeChanJoint::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwChanNum = m_cmChanNum.GetCurSel() + 1;
	memset(&m_struDecodeJointParam, 0, sizeof(m_struDecodeJointParam));
	m_struDecodeJointParam.dwSize = sizeof(m_struDecodeJointParam);
	m_struDecodeJointParam.byJointed = m_chJoint;
	DWORD dwIp = 0;
	m_IPV4.GetAddress(dwIp);
	sprintf(m_struDecodeJointParam.struIP.sIpV4, IPToStr(dwIp), 16);
	sprintf((char*)m_struDecodeJointParam.struIP.byIPv6, m_csIPV6, 128);
	m_struDecodeJointParam.wChannel = m_dwChanNum;
	m_struDecodeJointParam.wPort = m_dwPort;
	memcpy(m_struDecodeJointParam.sDeviceName, m_csJointDevName, NAME_LEN);
	memcpy(m_struDecodeJointParam.sChanName, m_csJointChanName, NAME_LEN);
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DECODER_JOINT_CHAN, dwChanNum, &m_struDecodeJointParam, sizeof(m_struDecodeJointParam)))
	{
		MessageBox("NET_DVR_SET_DECODER_JOINT_CHAN FAILED");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DECODER_JOINT_CHAN FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DECODER_JOINT_CHAN SUCC");
	}
}


void CDlgMatDecodeChanJoint::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwChanNum = m_cmChanNum.GetCurSel() + 1;
	memset(&m_struDecodeJointParam, 0, sizeof(m_struDecodeJointParam));
	m_struDecodeJointParam.dwSize = sizeof(m_struDecodeJointParam);
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DECODER_JOINT_CHAN, dwChanNum, &m_struDecodeJointParam, sizeof(m_struDecodeJointParam), &dwReturn))
	{
		MessageBox("NET_DVR_GET_DECODER_JOINT_CHAN FAILED");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DECODER_JOINT_CHAN FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DECODER_JOINT_CHAN SUCC");
		m_chJoint = m_struDecodeJointParam.byJointed;
		m_dwChanNum = m_struDecodeJointParam.wChannel;
		m_dwPort = m_struDecodeJointParam.wPort;
		m_IPV4.SetAddress(ntohl(inet_addr(m_struDecodeJointParam.struIP.sIpV4)));
		m_csIPV6.Format("%s", m_struDecodeJointParam.struIP.byIPv6);
		m_csJointChanName.Format("%s", m_struDecodeJointParam.sChanName);
		m_csJointDevName.Format("%s", m_struDecodeJointParam.sDeviceName);
	}
	UpdateData(FALSE);
}

void CDlgMatDecodeChanJoint::OnSelchangeComboChannum() 
{
	// TODO: Add your control notification handler code here
	OnBtnGet();
}

void CDlgMatDecodeChanJoint::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
