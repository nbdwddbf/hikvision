/**********************************************************
FileName:    SubDlgExceptionCfg.cpp
Description: Set exception message configuration     
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgExceptionCfg.h"
#include ".\subdlgexceptioncfg.h"


// CSubDlgExceptionCfg dialog
/*********************************************************
  Function:	CSubDlgExceptionCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgExceptionCfg, CDialog)
CSubDlgExceptionCfg::CSubDlgExceptionCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgExceptionCfg::IDD, pParent)
	, m_bChkMonitorAlarm(FALSE)
	, m_bChkVoiceAlarm(FALSE)
	, m_bChkUploadCenter(FALSE)
	, m_bChkInvokeAlarmOut(FALSE)
	, m_bChkInvokeJpegCapture(FALSE)
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_dwAlarmOutNum(0)
	, m_iExceptionType(0)
	, m_bSetPara(FALSE)
{
	m_pStruExceptionInfo = new NET_DVR_EXCEPTION_V40;
	//memset(m_pStruExceptionInfo, 0, sizeof(m_pStruExceptionInfo));
	if (m_pStruExceptionInfo != NULL)
	{
		memset(m_pStruExceptionInfo,0, sizeof(NET_DVR_EXCEPTION_V40));
	}
	
    m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
    if(m_pbAlarmOut != NULL)
    {
        memset(m_pbAlarmOut, 0, sizeof(BOOL)*MAX_ALARMOUT_V40);
    }
}

/*********************************************************
  Function:	~CSubDlgExceptionCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgExceptionCfg::~CSubDlgExceptionCfg()
{
	if (m_pbAlarmOut != NULL)
    {
        delete[] m_pbAlarmOut;
        m_pbAlarmOut = NULL;
    }
    
    if(m_pStruExceptionInfo != NULL)
    {
        delete m_pStruExceptionInfo;
        m_pStruExceptionInfo = NULL;
    }
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgExceptionCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgExceptionCfg)
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMBO_EXCEPTION_TYPE, m_comboExceptionType);
	DDX_Check(pDX, IDC_CHK_EXCEPTION_MONITOR_ALARM, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_EXCEPTION_AUDIO_ALARM, m_bChkVoiceAlarm);
	DDX_Check(pDX, IDC_CHK_EXCEPTION_REPORT_CENTER, m_bChkUploadCenter);
	DDX_Check(pDX, IDC_CHK_EXCEPTION_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
	//}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgExceptionCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgExceptionCfg)	
	ON_BN_CLICKED(IDC_BTN_EXCEPTION_OK, OnBnClickedBtnExceptionOk)
	ON_BN_CLICKED(IDC_CHK_EXCEPTION_INVOKE_ALARM_OUT, OnBnClickedChkExceptionInvokeAlarmOut)
	ON_CBN_SELCHANGE(IDC_COMBO_EXCEPTION_TYPE, OnCbnSelchangeComboExceptionType)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSubDlgExceptionCfg message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CSubDlgExceptionCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	return TRUE;
}

/*********************************************************
	Function:	CheckInitParam
	Desc:		Chek and update device parameters
	Input:	
	Output:	
	Return:	TRUE,device parameter checking correct,init parameter display on dialog box;FALSE,do not init
**********************************************************/
BOOL CSubDlgExceptionCfg::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

// 	if (g_pMainDlg->IsCurDevMatDec(iDeviceIndex))
// 	{
//         //return FALSE;
// 	}

	if (iDeviceIndex == -1)
	{
		return FALSE;
	}

	if (m_iDeviceIndex == iDeviceIndex)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_dwAlarmOutNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum;
	}
	m_comboExceptionType.SetCurSel(-1);
	m_bChkMonitorAlarm = FALSE;
	m_bChkVoiceAlarm = FALSE;
	m_bChkUploadCenter = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	m_bChkInvokeJpegCapture = FALSE;
	if (m_lLoginID < 0)
	{
		return FALSE;
	}
	DWORD dwReturned;
	CString sTemp;
	char szLan[128] = {0};
	m_iExceptionType = 0;
	m_comboExceptionType.SetCurSel(m_iExceptionType);
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_EXCEPTIONCFG_V40, 0, m_pStruExceptionInfo, sizeof(NET_DVR_EXCEPTION_V40), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_EXCEPTIONCFG_V40");

		g_StringLanType(szLan, "获取异常配置失败", "Get exception configure failed");
		AfxMessageBox(szLan);
		return FALSE;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_EXCEPTIONCFG_V40");
    }
	return TRUE;
}

/*********************************************************
Function:	CurCfgUpdate
Desc:		update selected device parameter and refresh control
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgExceptionCfg::CurCfgUpdate() 
{
	if (!CheckInitParam())
	{
		
		EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}
	int i = 0;
	EnableWindow(TRUE);

	m_bChkMonitorAlarm = m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType &0x01;
	m_bChkVoiceAlarm = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>1)&0x01;
	m_bChkUploadCenter = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>4)&0x01;
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
	memset(m_pbAlarmOut,0, sizeof(BOOL)*MAX_ALARMOUT_V40);
	for (i = 0; i < MAX_ALARMOUT_V40 ;i++)
	{        
		if (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[i] != INVALID_VALUE_UINT32 && m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[i]< MAX_ALARMOUT_V40)
		{
			m_pbAlarmOut[m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[i]] = 1;
		}
	}
	CreateTree();
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnExceptionOk
  Desc:		confirm exception configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgExceptionCfg::OnBnClickedBtnExceptionOk()
{
	UpdateData(TRUE);
	int i=0;
	m_iExceptionType = m_comboExceptionType.GetCurSel();
	m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType = 0;
	m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType |= (m_bChkMonitorAlarm << 0);
	m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType |= (m_bChkVoiceAlarm << 1);
	m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType |= (m_bChkUploadCenter << 2);
	m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType |= (m_bChkInvokeJpegCapture << 4);
	DWORD dwCurRelAlarmOutNum = 0;
    memset(m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut, INVALID_VALUE_UINT32, sizeof(DWORD)*MAX_ALARMOUT_V40);
    for (i=0; i<MAX_ALARMOUT_V40; i++)
    {
        if (m_pbAlarmOut[i])
        {
            m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[dwCurRelAlarmOutNum++] = i;
        }        
    }
	
	m_bSetPara = TRUE;
}

/*********************************************************
  Function:	OnBnClickedChkExceptionInvokeAlarmOut
  Desc:		enable alarm output settings for exception
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgExceptionCfg::OnBnClickedChkExceptionInvokeAlarmOut()
{
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

/*********************************************************
  Function:	OnCbnSelchangeComboExceptionType
  Desc:		update exception parameters
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgExceptionCfg::OnCbnSelchangeComboExceptionType()
{
	int i = 0;	
	memset(m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut, 0xffffffff, sizeof(DWORD)*MAX_ALARMOUT_V40);
    DWORD dwCurRelAlarmOutNum = 0;
	for (i=0; i<MAX_ALARMOUT_V40; i++)
	{
        if (m_pbAlarmOut[i])
        {
            m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[dwCurRelAlarmOutNum++] = i;
        }
		
	}
	
	UpdateData(TRUE);

	m_iExceptionType = m_comboExceptionType.GetCurSel();
	m_bChkMonitorAlarm = m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType &0x01;
	m_bChkVoiceAlarm = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>1)&0x01;
	m_bChkUploadCenter = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwHandleType>>4)&0x01;
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
	memset(m_pbAlarmOut, 0,sizeof(BOOL) * MAX_ALARMOUT_V40);
	for (i=0; i<MAX_ALARMOUT_V40; i++)
	{
        if (m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[i] != INVALID_VALUE_UINT32 && m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[i]< MAX_ALARMOUT_V40)
        {
            m_pbAlarmOut[m_pStruExceptionInfo->struExceptionHandle[m_iExceptionType].dwRelAlarmOut[i]] = 1;
        }
	}
	CreateTree();
	UpdateData(FALSE);
}

/*********************************************************
Function:	CfgSetup
Desc:		set exception message handling method
Input:	
Output:	
Return:	TRUE,settinsg succeeds;FALSE,settings failed;
**********************************************************/
BOOL CSubDlgExceptionCfg::CfgSetup()
{
	CString sTemp;
	char szLan[128] = {0};
	if (m_bSetPara)
	{
		if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_EXCEPTIONCFG_V40, 0, m_pStruExceptionInfo, sizeof(NET_DVR_EXCEPTION_V40)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_EXCEPTIONCFG_V40"); 
			g_StringLanType(szLan, "参数保存失败", "Save parameter failed");
			AfxMessageBox(szLan);
			return FALSE;		
		}
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EXCEPTIONCFG_V40"); 
        }
		m_bSetPara = FALSE;
	}
	return TRUE;
}

/*********************************************************
  Function:	OnClickTreeAlarmOut
  Desc:		invoke the correponding alarm chan
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgExceptionCfg::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	//g_ClickAlarmOutItem(m_treeAlarmOut, hSelect, uFlag);	
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	m_pbAlarmOut[dwIndex] = !bCheck;
	
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else//LVHT_TOLEFT
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}

	*pResult = 0;
}


/*********************************************************
  Function:	CreateTree
  Desc:		Create connection between Alarm output and device index
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgExceptionCfg::CreateTree(void)
{
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDeviceIndex, m_pbAlarmOut);
}

/*********************************************************
  Function:	OnPaint
  Desc:		paint the tree
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgExceptionCfg::OnPaint() 
{
	CreateTree();
	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}
