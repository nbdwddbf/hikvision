// DlgLampCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLampCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLampCfg dialog


CDlgLampCfg::CDlgLampCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLampCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLampCfg)
	m_bEnable = FALSE;
	m_sLampName = _T("");
	m_sLampStatus1 = _T("");
	m_sLampStatus2 = _T("");
	m_sLampStatus3 = _T("");
	//}}AFX_DATA_INIT
	memset(&m_struLampOut,0,sizeof(m_struLampOut));
}


void CDlgLampCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLampCfg)
	DDX_Control(pDX, IDC_COMBO_LAMP, m_comboLamp);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_LAMP_NAME, m_sLampName);
	DDX_Text(pDX, IDC_LAMP_STATUS1, m_sLampStatus1);
	DDX_Text(pDX, IDC_LAMP_STATUS2, m_sLampStatus2);
	DDX_Text(pDX, IDC_LAMP_STATUS3, m_sLampStatus3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLampCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgLampCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_CBN_SELCHANGE(IDC_COMBO_LAMP, OnSelchangeComboLamp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLampCfg message handlers

BOOL CDlgLampCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLampCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	OnBtnOk();
	m_struLampOut.dwSize = sizeof(m_struLampOut);
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_LAMP_OUT,0,&m_struLampOut,sizeof(m_struLampOut)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LAMP_OUT");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_SET_LAMP_OUT failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LAMP_OUT");
    }

}

void CDlgLampCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	m_struLampOut.dwSize = sizeof(m_struLampOut);
	DWORD dwRet = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_LAMP_OUT,0,&m_struLampOut,sizeof(m_struLampOut),&dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LAMP_OUT");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_GET_LAMP_OUT failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LAMP_OUT");
    }

	m_comboLamp.SetCurSel(0);
	OnSelchangeComboLamp();
}

void CDlgLampCfg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iCurIndex = m_comboLamp.GetCurSel();
	m_struLampOut.struLampInfo[iCurIndex].byEnable = m_bEnable;
	sprintf((char*)m_struLampOut.struLampInfo[iCurIndex].byLampName,m_sLampName);
	sprintf((char*)m_struLampOut.struLampInfo[iCurIndex].byLampState1,m_sLampStatus1);
	sprintf((char*)m_struLampOut.struLampInfo[iCurIndex].byLampState2,m_sLampStatus2);
	sprintf((char*)m_struLampOut.struLampInfo[iCurIndex].byLampState3,m_sLampStatus3);
}

void CDlgLampCfg::OnSelchangeComboLamp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iCurIndex = m_comboLamp.GetCurSel();
	m_bEnable = m_struLampOut.struLampInfo[iCurIndex].byEnable;
	m_sLampName.Format("%s",m_struLampOut.struLampInfo[iCurIndex].byLampName);
	m_sLampStatus1.Format("%s",m_struLampOut.struLampInfo[iCurIndex].byLampState1);
	m_sLampStatus2.Format("%s",m_struLampOut.struLampInfo[iCurIndex].byLampState2);
	m_sLampStatus3.Format("%s",m_struLampOut.struLampInfo[iCurIndex].byLampState3);
	UpdateData(FALSE);
}
