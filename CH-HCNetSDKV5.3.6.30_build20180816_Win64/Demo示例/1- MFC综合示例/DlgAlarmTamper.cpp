// DlgAlarmTamper.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmTamper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmTamper dialog


CDlgAlarmTamper::CDlgAlarmTamper(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmTamper::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmTamper)
	m_bChkUploadAlarmRecoveryReport = FALSE;
	m_fTamperResistorManual = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgAlarmTamper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmTamper)
	DDX_Control(pDX, IDC_LIST_SIREN_OUT, m_listSirenOut);
	DDX_Control(pDX, IDC_LIST_ALARM_OUT, m_listAlarmOut);
	DDX_Control(pDX, IDC_COMBO_TEMPER, m_comboTamper);
	DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
	DDX_Check(pDX, IDC_CHECK_UPLOAD_ALARM_RECOVERY_REPORT, m_bChkUploadAlarmRecoveryReport);
	DDX_Control(pDX, IDC_CMB_TAMPER_RESISTOR, m_cmbTamperResistor);
	DDX_Text(pDX, IDC_EDIT_TAMPER_RESISTOR_MANUAL, m_fTamperResistorManual);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmTamper, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmTamper)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_CMB_TAMPER_RESISTOR, OnSelchangeCmbTamperResistor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmTamper message handlers

BOOL CDlgAlarmTamper::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	NET_DVR_ALARMHOST_ABILITY struAlarmHostAbility = {0};
	struAlarmHostAbility.dwSize = sizeof(NET_DVR_ALARMHOST_ABILITY);
	DWORD dwReturn = 0;
    if (NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAlarmHostAbility, sizeof(struAlarmHostAbility)))
    {
        char szLan[128] = {0};
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
		return FALSE;
    }
	char szLan[128] = {0};
	m_comboAlarmIn.ResetContent();
    int i = 0;
	for ( i = 0; i < (struAlarmHostAbility.wLocalAlarmInNum + struAlarmHostAbility.wExpandAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", i + 1);
        m_comboAlarmIn.InsertString(i, szLan);
        m_comboAlarmIn.SetItemData(i, i);
    }
    
    if (i > 0)
    {
        m_comboAlarmIn.SetCurSel(0);
    }

	m_listAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < (struAlarmHostAbility.wLocalAlarmOutNum + struAlarmHostAbility.wExpandAlarmOutNum); i++)
    {
        sprintf(szLan, "Alarm Out %d", (i+1));
        m_listAlarmOut.InsertItem(i, szLan);
    }

	m_listSirenOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < struAlarmHostAbility.wSirenNum; i++)
    {
        sprintf(szLan, "Siren %d", (i+1));
        m_listSirenOut.InsertItem(i, szLan);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmTamper::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LONG lAlarmIn = m_comboAlarmIn.GetItemData(m_comboAlarmIn.GetCurSel());
    DWORD dwReturn = 0;
	NET_DVR_TAMPER_ALARMIN_PARAM struAlarmTamper = {0};
	struAlarmTamper.dwSize = sizeof(NET_DVR_TAMPER_ALARMIN_PARAM);
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_TAMPER_ALARMIN_PARAM, lAlarmIn, &struAlarmTamper, sizeof(struAlarmTamper), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TAMPER_ALARMIN_PARAM");
    }
    else   
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TAMPER_ALARMIN_PARAM");
        return;
    }

	int i = 0;
    for (i = 0; i < m_listAlarmOut.GetItemCount(); i++ )
    {
        if (1==  struAlarmTamper.byAssociateAlarmOut[i])
        {
            m_listAlarmOut.SetCheck(i, TRUE);
        }
        else
        {
            m_listAlarmOut.SetCheck(i, FALSE);
        }
    }
	
    for (i = 0; i < m_listSirenOut.GetItemCount(); i++)
    {
        if (1 == struAlarmTamper.byAssociateSirenOut[i])
        {
            m_listSirenOut.SetCheck(i, TRUE);
        }
        else
        {
            m_listSirenOut.SetCheck(i, FALSE);
        }
    }
	m_bChkUploadAlarmRecoveryReport = struAlarmTamper.byUploadAlarmRecoveryReport;
	m_comboTamper.SetCurSel(struAlarmTamper.byTamperType);

	OnSelchangeCmbTamperResistor();
	if (struAlarmTamper.byTamperResistor == 0xff)
	{
		m_fTamperResistorManual = struAlarmTamper.fTamperResistorManual;
		m_cmbTamperResistor.SetCurSel(6);
	}
	else
	{
		m_cmbTamperResistor.SetCurSel(struAlarmTamper.byTamperResistor);
	}

	UpdateData(FALSE);
}

void CDlgAlarmTamper::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_TAMPER_ALARMIN_PARAM struAlarmTamper = {0};
	struAlarmTamper.dwSize = sizeof(NET_DVR_TAMPER_ALARMIN_PARAM);
	int i = 0;
    for (i = 0; i < m_listAlarmOut.GetItemCount(); i++)
    {
        if (TRUE == m_listAlarmOut.GetCheck(i))
        {
            struAlarmTamper.byAssociateAlarmOut[i] = 1;
        }
        else
        {
            struAlarmTamper.byAssociateAlarmOut[i] = 0;
        }
    }
    
    for (i = 0; i < m_listSirenOut.GetItemCount(); i++)
    {
        if (TRUE == m_listSirenOut.GetCheck(i))
        {
            struAlarmTamper.byAssociateSirenOut[i] = 1;
        }
        else
        {
            struAlarmTamper.byAssociateSirenOut[i] = 0;
        }
    }
	struAlarmTamper.byTamperType = m_comboTamper.GetCurSel();
	struAlarmTamper.byUploadAlarmRecoveryReport = m_bChkUploadAlarmRecoveryReport;
	
	if (m_cmbTamperResistor.GetCurSel() == 6)
	{
		struAlarmTamper.fTamperResistorManual = m_fTamperResistorManual;
		struAlarmTamper.byTamperResistor = 0xff;
	} 
	else
	{
		struAlarmTamper.byTamperResistor = m_cmbTamperResistor.GetCurSel();
	}

	LONG lAlarmIn = m_comboAlarmIn.GetItemData(m_comboAlarmIn.GetCurSel());
    if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_TAMPER_ALARMIN_PARAM, lAlarmIn, &struAlarmTamper, sizeof(struAlarmTamper)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TAMPER_ALARMIN_PARAM");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TAMPER_ALARMIN_PARAM");
    }
}

void CDlgAlarmTamper::OnSelchangeCmbTamperResistor() 
{
	// TODO: Add your control notification handler code here
	if (m_cmbTamperResistor.GetCurSel() == 6)
	{
		GetDlgItem(IDC_EDIT_TAMPER_RESISTOR_MANUAL)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_EDIT_TAMPER_RESISTOR_MANUAL)->EnableWindow(FALSE);
	}
}
