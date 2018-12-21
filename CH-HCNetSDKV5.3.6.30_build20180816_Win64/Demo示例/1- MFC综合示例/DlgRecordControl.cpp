// DlgRecordControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRecordControl dialog


DlgRecordControl::DlgRecordControl(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRecordControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRecordControl)
	m_nDelayTime = 0;
	m_nCourseIndex = 0;
	m_bStartDefine = FALSE;
	m_bDelayDefine = FALSE;
	m_byCourseName = _T("");
	m_byCourseDescription = _T("");
	m_byInstructorName = _T("");
	m_byRecUUID = _T("");
	//}}AFX_DATA_INIT
	memset(&m_struRecordControlCfg, 0 ,sizeof(m_struRecordControlCfg));
	m_iDeviceIndex = 0;
	m_lUserID = 0;
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
}


void DlgRecordControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRecordControl)
	DDX_Control(pDX, IDC_COMBO_CMDTYPE, m_byCmdType);
	DDX_Control(pDX, IDC_COM_CMD_TYPE, m_comCmdType);
	DDX_Text(pDX, IDC_EDT_DELAY_TIME, m_nDelayTime);
	DDX_Text(pDX, IDC_EDT_COURSE_INDEX, m_nCourseIndex);
	DDX_Check(pDX, IDC_CHK_START_DEFINE, m_bStartDefine);
	DDX_Check(pDX, IDC_CHK_DELAY_DEFINE, m_bDelayDefine);
	DDX_Text(pDX, IDC_EDIT_COURSE_NAME, m_byCourseName);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_byCourseDescription);
	DDX_Text(pDX, IDC_EDIT_INSTRUCTOR, m_byInstructorName);
	DDX_Text(pDX, IDC_EDIT_UUID, m_byRecUUID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRecordControl, CDialog)
	//{{AFX_MSG_MAP(DlgRecordControl)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COM_CMD_TYPE, OnSelchangeComCmdType)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_CONTROL, OnButtonManualControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRecordControl message handlers

BOOL DlgRecordControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comCmdType.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComCmdType();

    char szLan[128];
    m_byCmdType.ResetContent();
    g_StringLanType(szLan, "¿ªÊ¼Â¼Ïñ", "startRecord");
    m_byCmdType.InsertString(0,szLan);
    g_StringLanType(szLan, "½áÊøÂ¼Ïñ", "stopRecord");
    m_byCmdType.InsertString(1,szLan);
    g_StringLanType(szLan, "ÔÝÍ£Â¼Ïñ", "pauseRecord");
    m_byCmdType.InsertString(2,szLan);
    g_StringLanType(szLan, "¼ÌÐøÂ¼Ïñ", "continueRecord");
    m_byCmdType.InsertString(3,szLan);
    g_StringLanType(szLan, "¿ªÊ¼ÆÁ±Î", "startShield");
    m_byCmdType.InsertString(4,szLan);
    g_StringLanType(szLan, "½áÊøÆÁ±Î", "stopShield");
    m_byCmdType.InsertString(5,szLan);
    m_byCmdType.SetCurSel(0);

	return TRUE;
}

void DlgRecordControl::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	OnBtnOk();
	m_struRecordControlCfg.wCmdType = (WORD)m_comCmdType.GetCurSel();
	m_struRecordControlCfg.dwSize = sizeof(m_struRecordControlCfg);
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_RECORDING_ONEKEY_CONTROL,m_iStartChannel,&m_struRecordControlCfg,sizeof(m_struRecordControlCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RECORDING_ONEKEY_CONTROL,  %s", "Record host control faild");
		g_StringLanType(szLan, "Â¼²¥Ö÷»ú¿ØÖÆÊ§°Ü", "Record host control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDINGHOST_CFG,  %s", "Record host control success");
		g_StringLanType(szLan, "Â¼²¥Ö÷»ú¿ØÖÆ³É¹¦", "Record host control success");
		AfxMessageBox(szLan);
	}
}

void DlgRecordControl::OnSelchangeComCmdType()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	int sel = m_comCmdType.GetCurSel();
	if (sel == 0)
	{
		GetDlgItem(IDC_EDT_DELAY_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_COURSE_INDEX)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_START_DEFINE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_DELAY_DEFINE)->EnableWindow(TRUE);
		m_bStartDefine = m_struRecordControlCfg.struControlInfo.struStartCfg.byUseDefine;
		m_nCourseIndex = m_struRecordControlCfg.struControlInfo.struStartCfg.wCourseIndex;
	}
	else if (sel == 4)
	{
		GetDlgItem(IDC_EDT_DELAY_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_COURSE_INDEX)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_START_DEFINE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_DELAY_DEFINE)->EnableWindow(TRUE);
		m_bDelayDefine = m_struRecordControlCfg.struControlInfo.struDelayCfg.byUseDefine;
		m_nDelayTime = m_struRecordControlCfg.struControlInfo.struDelayCfg.wDelayTime;
	}
	else
	{
		GetDlgItem(IDC_EDT_DELAY_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_COURSE_INDEX)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_START_DEFINE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_DELAY_DEFINE)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void DlgRecordControl::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_comCmdType.GetCurSel();
	if (sel == 0)
	{
		GetDlgItem(IDC_EDT_DELAY_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_COURSE_INDEX)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_START_DEFINE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_DELAY_DEFINE)->EnableWindow(TRUE);
		m_struRecordControlCfg.struControlInfo.struStartCfg.byUseDefine = m_bStartDefine;
		m_struRecordControlCfg.struControlInfo.struStartCfg.wCourseIndex = m_nCourseIndex;
	}
	else if (sel == 4)
	{
		GetDlgItem(IDC_EDT_DELAY_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_COURSE_INDEX)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_START_DEFINE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_DELAY_DEFINE)->EnableWindow(TRUE);
		m_struRecordControlCfg.struControlInfo.struDelayCfg.byUseDefine = m_bDelayDefine;
		m_struRecordControlCfg.struControlInfo.struDelayCfg.wDelayTime = m_nDelayTime;
	}
	else
	{

	}
}

void DlgRecordControl::OnButtonManualControl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    char szLan[512] = {0};
    NET_DVR_MANUAL_CURRICULUM_CFG struManualCfg = {0};
    struManualCfg.dwSize = sizeof(struManualCfg);
    sprintf((char*)(struManualCfg.byRecUUID), m_byRecUUID.GetBuffer(m_byRecUUID.GetLength()));
    sprintf((char*)(struManualCfg.byCourseName), m_byCourseName.GetBuffer(m_byCourseName.GetLength()));
    sprintf((char*)(struManualCfg.byInstructorName), m_byInstructorName.GetBuffer(m_byInstructorName.GetLength()));
    sprintf((char*)(struManualCfg.byCourseDescription), m_byCourseDescription.GetBuffer(m_byCourseDescription.GetLength()));
    struManualCfg.byCmdType = m_byCmdType.GetCurSel();

    char  szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_STD_CONTROL struSTDControl = {0};
    struSTDControl.lpCondBuffer = &struManualCfg;
    struSTDControl.dwCondSize = sizeof(struManualCfg);
    memset(szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDControl.lpStatusBuffer = szStatusBuf;
    struSTDControl.dwStatusSize = ISAPI_STATUS_LEN;
    
    if (NET_DVR_STDControl(m_lUserID, NET_DVR_MANUAL_CURRICULUM_CONTROL, &struSTDControl))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MANUAL_CURRICULUM_CONTROL");
    }
    else
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MANUAL_CURRICULUM_CONTROL");
    }
	
}
