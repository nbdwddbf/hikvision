// DlgIscsiCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIscsiCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIscsiCfg dialog


CDlgIscsiCfg::CDlgIscsiCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIscsiCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIscsiCfg)
	m_bEnable = FALSE;
	m_csNvtIndexCode = _T("");
	m_iPort = 0;
	m_csIpAddr = _T("");
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struIscsiCfg, 0, sizeof(m_struIscsiCfg));
}


void CDlgIscsiCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIscsiCfg)
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_NVT_INDEX_CODE, m_csNvtIndexCode);
	DDV_MaxChars(pDX, m_csNvtIndexCode, 64);
	DDX_Text(pDX, IDC_EDIT_VRM_PORT, m_iPort);
	DDV_MinMaxInt(pDX, m_iPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_VRM_ADDR, m_csIpAddr);
	DDV_MaxChars(pDX, m_csIpAddr, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIscsiCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgIscsiCfg)
	ON_EN_CHANGE(IDC_EDIT_VRM_PORT, OnChangeEditVrmPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIscsiCfg message handlers

BOOL CDlgIscsiCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DWORD dwReturn = 0;
	if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ISCSI_CFG,  -1, &m_struIscsiCfg, sizeof(m_struIscsiCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ISCSI_CFG");
        MessageBox("Fail to get ISCSI config");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ISCSI_CFG");
    }
    m_bEnable = m_struIscsiCfg.byEnable;
    m_csIpAddr = m_struIscsiCfg.struVrmAddr.sIpV4;
    m_iPort = m_struIscsiCfg.wVrmPort;
    
    strcpy(m_csNvtIndexCode.GetBuffer(0), m_struIscsiCfg.chNvtIndexCode);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIscsiCfg::OnOK() 
{
    UpdateData(TRUE);
    memset(&m_struIscsiCfg, 0, sizeof(m_struIscsiCfg));
    m_struIscsiCfg.byEnable = m_bEnable;
    strncpy(m_struIscsiCfg.chNvtIndexCode, m_csNvtIndexCode.GetBuffer(0), m_csNvtIndexCode.GetLength());
    strncpy(m_struIscsiCfg.struVrmAddr.sIpV4, m_csIpAddr.GetBuffer(0), m_csIpAddr.GetLength());
    m_struIscsiCfg.wVrmPort = m_iPort;

    if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ISCSI_CFG,  -1, &m_struIscsiCfg, sizeof(m_struIscsiCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ISCSI_CFG");
        MessageBox("Fail to set ISCSI config");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ISCSI_CFG");
        MessageBox("Succ to set ISCSI£¬Restart active");
    }
	//CDialog::OnOK();
}

void CDlgIscsiCfg::OnChangeEditVrmPort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
