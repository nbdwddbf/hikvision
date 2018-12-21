// DlgDeviceSelfCheckState.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDeviceSelfCheckState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgDeviceSelfCheckState dialog


DlgDeviceSelfCheckState::DlgDeviceSelfCheckState(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDeviceSelfCheckState::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDeviceSelfCheckState)
	//}}AFX_DATA_INIT
}


void DlgDeviceSelfCheckState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgDeviceSelfCheckState)
	DDX_Control(pDX, IDC_LIST_SENSOR_CHAN, m_listSensorChan);
	DDX_Control(pDX, IDC_COM_CHAN, m_comChan);
	DDX_Control(pDX, IDC_LIST_SLOT, m_listSlot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgDeviceSelfCheckState, CDialog)
	//{{AFX_MSG_MAP(DlgDeviceSelfCheckState)
	ON_BN_CLICKED(IDC_GET, OnGet)
	ON_CBN_SELCHANGE(IDC_COM_CHAN, OnSelchangeComChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgDeviceSelfCheckState message handlers
BOOL DlgDeviceSelfCheckState::OnInitDialog()
{
	CDialog::OnInitDialog();
	memset(&m_struDeviceSelfCheckState,0,sizeof(m_struDeviceSelfCheckState));
	char cstemp[256];
    int i = 0;
	for(i = 0; i < 32; i++)
	{
		sprintf(cstemp,"chan %d",i);
		m_listSlot.SetExtendedStyle(LVS_EX_CHECKBOXES);
		m_listSlot.InsertItem(i,cstemp);
		m_listSlot.SetCheck(i, FALSE);
	}
	for(i = 0; i < 128; i++)
	{
		sprintf(cstemp,"chan %d",i);
		m_listSensorChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
		m_listSensorChan.InsertItem(i,cstemp);
		m_listSensorChan.SetCheck(i, FALSE);
	}
	for (i = 0; i < 64; i++)
	{
		sprintf(cstemp,"chan %d",i);
		m_comChan.AddString(cstemp);
	}
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	UpdateData(FALSE);
	return TRUE;
}

void DlgDeviceSelfCheckState::OnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
    int i = 0;
	for (i = 0; i < 128; i++)
	{
		m_listSensorChan.SetCheck(i, FALSE);
	}
	if (NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_DEVICE_SELF_CHECK_STATE,0,&m_struDeviceSelfCheckState,sizeof(m_struDeviceSelfCheckState),&dwReturned))
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_GET_DEVICE_SELF_CHECK_STATE");
	}
	else
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_GET_DEVICE_SELF_CHECK_STATE");
        return;
    }
	for (i = 0; i < 128; i++)
	{
		if((m_struDeviceSelfCheckState.dwSensorChan[i/32] >> i)&0x01 == 1)
		{
			m_listSensorChan.SetCheck(i, TRUE);
		}
	}
	UpdateData(FALSE);
	m_comChan.SetCurSel(0);
	OnSelchangeComChan();
}

void DlgDeviceSelfCheckState::OnSelchangeComChan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int i = 0;
	for (i = 0; i < 32; i++)
	{
		m_listSlot.SetCheck(i, FALSE);
	}
	DWORD nSel = m_comChan.GetCurSel();
	for (i = 0; i < 32; i++)
	{
		if((m_struDeviceSelfCheckState.dwRS485Chan[nSel] >> i)&0x01 == 1)
		{
			m_listSlot.SetCheck(i, TRUE);
		}
	}
	UpdateData(FALSE);
}
