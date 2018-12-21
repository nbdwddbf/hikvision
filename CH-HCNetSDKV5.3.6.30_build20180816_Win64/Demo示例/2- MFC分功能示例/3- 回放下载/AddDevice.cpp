// AddDevice.cpp : implementation file
//

#include "stdafx.h"
#include "PlayBack.h"
#include "AddDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddDevice dialog


CAddDevice::CAddDevice(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDevice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddDevice)
	m_csNodeName = _T("dev");
	m_nPort = 8000;
	m_csUser = _T("admin");
	m_csPWD = _T("12345");
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(NodeName,0,30);
	memset(DeviceIP,0,30);
	memset(UserName,0,30);
	memset(Password,0,30);
	Port=8000;
}


void CAddDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddDevice)
	DDX_Control(pDX, IDC_IPADDRESS_DEV, m_ctrlIP);
	DDX_Text(pDX, IDC_EDIT_NODE, m_csNodeName);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_PWD, m_csPWD);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddDevice, CDialog)
	//{{AFX_MSG_MAP(CAddDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddDevice message handlers

BOOL CAddDevice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlIP.SetAddress(172,7,94,6);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddDevice::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	BYTE nField0, nField1, nField2, nField3;
	m_ctrlIP.GetAddress(nField0,nField1,nField2,nField3);
	sprintf(DeviceIP,"%d.%d.%d.%d",nField0, nField1, nField2, nField3);
	
	strcpy(NodeName,m_csNodeName.GetBuffer(m_csNodeName.GetLength()));
	strcpy(UserName,m_csUser.GetBuffer(m_csUser.GetLength()));
	strcpy(Password,m_csPWD.GetBuffer(m_csPWD.GetLength()));
	Port=m_nPort;
	CDialog::OnOK();
}
