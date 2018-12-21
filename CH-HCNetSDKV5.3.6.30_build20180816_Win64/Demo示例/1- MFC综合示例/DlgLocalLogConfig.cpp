/**********************************************************
FileName:    DlgLocalLogConfig.cpp
Description: local log configuration deal   
Date:        2008/06/03
Note: 		 <global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp     
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/03>       <created>
***********************************************************/
#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgLocalLogConfig.h"
#include ".\dlglocallogconfig.h"


// CDlgLocalLogConfig dialog
/*********************************************************
  Function:	CDlgLocalLogConfig
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgLocalLogConfig, CDialog)
CDlgLocalLogConfig::CDlgLocalLogConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocalLogConfig::IDD, pParent)
	, m_bChkAlarmInfo(TRUE)
	, m_bChkSuccInfo(TRUE)
	, m_bChkFailInfo(TRUE)
	, m_bChkAutoSaveLog(TRUE)
	, m_bChkOutputDebugString(FALSE)
{
	InitializeCriticalSection(&m_csLock);
}

/*********************************************************
  Function:	~CDlgLocalLogConfig
  Desc:		Destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgLocalLogConfig::~CDlgLocalLogConfig()
{
	DeleteCriticalSection(&m_csLock);
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgLocalLogConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocalLogConfig)
	DDX_Check(pDX, IDC_CHK_ALARM_INFO, m_bChkAlarmInfo);
	DDX_Check(pDX, IDC_CHK_SUCC_LOG, m_bChkSuccInfo);
	DDX_Check(pDX, IDC_CHK_FAIL_INFO, m_bChkFailInfo);
	DDX_Check(pDX, IDC_CHK_AUTO_SAVE_LOG, m_bChkAutoSaveLog);
	DDX_Check(pDX, IDC_CHK_OUTPUTDEBUG, m_bChkOutputDebugString);
    //}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgLocalLogConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgLocalLogConfig)	
	ON_BN_CLICKED(IDC_BTN_LOCAL_LOG_OK, OnBnClickedBtnLocalLogOk)
	ON_BN_CLICKED(IDC_BTN_LOCAL_LOG_EXIT, OnBnClickedBtnLocalLogExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgLocalLogConfig message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgLocalLogConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bChkAutoSaveLog = g_struLocalParam.bAutoSaveLog;
	
	m_bChkAlarmInfo = g_struLocalParam.bAlarmInfo;
	m_bChkSuccInfo = g_struLocalParam.bSuccLog;
	m_bChkFailInfo = g_struLocalParam.bFailLog;
	m_bChkOutputDebugString = g_struLocalParam.bOutputDebugString;
	UpdateData(FALSE);
	return TRUE;  
}

/*********************************************************
  Function:	OnBnClickedBtnLocalLogOk
  Desc:		conform
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgLocalLogConfig::OnBnClickedBtnLocalLogOk()
{
	UpdateData(TRUE);
	EnterCriticalSection(&m_csLock);
	g_struLocalParam.bAutoSaveLog = m_bChkAutoSaveLog;

	g_struLocalParam.bAlarmInfo = m_bChkAlarmInfo;
	g_struLocalParam.bSuccLog = m_bChkSuccInfo;
	g_struLocalParam.bFailLog = m_bChkFailInfo;
	g_struLocalParam.bOutputDebugString = m_bChkOutputDebugString;
	g_pMainDlg->CreateNewLogFile(g_struLocalParam.bAutoSaveLog);
	LeaveCriticalSection(&m_csLock);
	WriteLocalConfig();
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnLocalLogExit
  Desc:		exit
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgLocalLogConfig::OnBnClickedBtnLocalLogExit()
{
	CDialog::OnCancel();
}
