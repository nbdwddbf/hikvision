/**********************************************************
FileName:    DlgRemoteKey.cpp
Description: remote panel key      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteKey.h"
#include ".\dlgremotekey.h"


// CDlgRemoteKey dialog
int g_nOutput = 0;

/*********************************************************
  Function:	CDlgRemoteKey
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteKey, CDialog)
CDlgRemoteKey::CDlgRemoteKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteKey::IDD, pParent)
	, m_lServerID(-1)
{
	m_iPanSel = -1;
}
/*********************************************************
  Function:	~CDlgRemoteKey
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteKey::~CDlgRemoteKey()
{
}
/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteKey)
	DDX_Radio(pDX, IDC_RBTN_IRIS_INCREASE, m_iPanSel);
    //}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteKey, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteKey)	
	ON_BN_CLICKED(IDC_REMOTE_KEY_EXIT, OnBnClickedRemoteKeyExit)
	ON_BN_CLICKED(IDC_BTN_0, OnBnClickedBtn0)
	ON_BN_CLICKED(IDC_BTN_2, OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN_1, OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN_3, OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN_4, OnBnClickedBtn4)
	ON_BN_CLICKED(IDC_BTN_5, OnBnClickedBtn5)
	ON_BN_CLICKED(IDC_BTN_6, OnBnClickedBtn6)
	ON_BN_CLICKED(IDC_BTN_7, OnBnClickedBtn7)
	ON_BN_CLICKED(IDC_BTN_8, OnBnClickedBtn8)
	ON_BN_CLICKED(IDC_BTN_9, OnBnClickedBtn9)
	ON_BN_CLICKED(IDC_BTN_MAIN_MENU, OnBnClickedBtnMainMenu)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_REC, OnBnClickedBtnRec)
	ON_BN_CLICKED(IIDC_BTN_MULTI, OnBnClickedBtnMulti)
	ON_BN_CLICKED(IDC_BTN_A, OnBnClickedBtnA)
	ON_BN_CLICKED(IDC_BTN_OK, OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_ESC, OnBnClickedBtnEsc)
	ON_BN_CLICKED(IDC_BTN_UP, OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_LEFT, OnBnClickedBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, OnBnClickedBtnRight)
	ON_BN_CLICKED(IDC_BTN_SYS_INFO, OnBnClickedBtnSysInfo)
	ON_BN_CLICKED(IDC_BTN_VOIP, OnBnClickedBtnVoip)
	ON_BN_CLICKED(IDC_BTN_PAN, OnBnClickedBtnPan)
	ON_BN_CLICKED(IDC_BTN_START, OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_16, OnBtn16)
	ON_BN_CLICKED(IDC_BTN_15, OnBtn15)
	ON_BN_CLICKED(IDC_BTN_14, OnBtn14)
	ON_BN_CLICKED(IDC_BTN_13, OnBtn13)
	ON_BN_CLICKED(IDC_BTN_12, OnBtn12)
	ON_BN_CLICKED(IDC_BTN_11, OnBtn11)
	ON_BN_CLICKED(IDC_BTN_START_PANEL, OnBtnStartPanel)
	ON_BN_CLICKED(IDC_BTN_STOP_PANEL, OnBtnStopPanel)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()


// CDlgRemoteKey message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteKey::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedRemoteKeyExit
  Desc:		exit remote panel key control
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedRemoteKeyExit()
{
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnBnClickedBtn0
  Desc:		press panel key 0
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn0()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_0);
}

/*********************************************************
Function:	OnBnClickedBtn1
Desc:		press panel key 1
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn1()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_1);
}

/*********************************************************
Function:	OnBnClickedBtn2
Desc:		press panel key 2
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn2()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_2);
}

/*********************************************************
Function:	OnBnClickedBtn3
Desc:		press panel key 3
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn3()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_3);
}

/*********************************************************
Function:	OnBnClickedBtn4
Desc:		press panel key 4
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn4()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_4);
}

/*********************************************************
Function:	OnBnClickedBtn5
Desc:		press panel key 5
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn5()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_5);
}

/*********************************************************
Function:	OnBnClickedBtn6
Desc:		press panel key 6
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn6()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_6);
}

/*********************************************************
Function:	OnBnClickedBtn7
Desc:		press panel key 7
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn7()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_7);
}

/*********************************************************
Function:	OnBnClickedBtn8
Desc:		press panel key 8
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn8()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_8);
}

/*********************************************************
Function:	OnBnClickedBtn9
Desc:		press panel key 9
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtn9()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_9);
}

/*********************************************************
  Function:	OnBtn16
  Desc:		click the button on the panel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtn16() 
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_16);	
}

/*********************************************************
  Function:	OnBtn15
  Desc:		as click the button 15 on the panel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtn15() 
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_15);	
}

/*********************************************************
  Function:	OnBtn14
  Desc:		Click the button 14 on the panel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtn14() 
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_14);	
}

/*********************************************************
  Function:	OnBtn13
  Desc:		as click the button 13 on the panel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtn13() 
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_13);
}

/*********************************************************
  Function:	OnBtn12
  Desc:		as click the button 12 on the panel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtn12() 
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_12);
}
/*********************************************************
  Function:	OnBtn11
  Desc:		as click the button 11 on the panel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtn11() 
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_11);
}

/*********************************************************
Function:	OnBnClickedBtnMainMenu
Desc:		press panel key to display main menu
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnMainMenu()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_MENU);//12
}

/*********************************************************
  Function:	OnBnClickedBtnEdit
  Desc:		press panel key [edit]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnEdit()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_EDIT);//19
}

/*********************************************************
  Function:	OnBnClickedBtnPlay
  Desc:		press panel key [play]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnPlay()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_PLAY);//22
}

/*********************************************************
  Function:	OnBnClickedBtnRec
  Desc:		press panel key [record]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnRec()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_REC);//23
}

/*********************************************************
  Function:	OnBnClickedBtnMulti
  Desc:		press panel key [multi]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnMulti()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_M);//multi-screen-split display
}

/*********************************************************
  Function:	OnBnClickedBtnA
  Desc:		press panel key [A]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnA()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_A);
}

/*********************************************************
  Function:	OnBnClickedBtnOk
  Desc:		press panel key [enter]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnOk()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_ENTER);//13
}

/*********************************************************
  Function:	OnBnClickedBtnEsc
  Desc:		press panel key [exit]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnEsc()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_CANCEL);//14
}

/*********************************************************
  Function:	OnBnClickedBtnUp
  Desc:		press panel key PTZ up
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnUp()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_UP);
}

/*********************************************************
Function:	OnBnClickedBtnDown
Desc:		press panel key PTZ down
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnDown()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_DOWN);
}

/*********************************************************
Function:	OnBnClickedBtnLeft
Desc:		press panel key PTZ right
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnLeft()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_LEFT);//
}

/*********************************************************
Function:	OnBnClickedBtnRight
Desc:		press panel key PTZ right
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnRight()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_RIGHT);//
}

/*********************************************************
Function:	OnBnClickedBtnSysInfo
Desc:		press panel key [F2]
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnSysInfo()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_F2);
}

/*********************************************************
Function:	OnBnClickedBtnVoip
Desc:		press panel key [F1]
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnVoip()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_F1);
}

/*********************************************************
Function:	OnBnClickedBtnPan
Desc:		press panel key [Pan]
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnPan()
{
	UpdateData(TRUE);
	NET_DVR_ClickKey(m_lServerID, KEY_CODE_PAN);
}

/*********************************************************
Function:	OnBnClickedBtnStart
Desc:		press panel key [start]
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnStart()
{
	UpdateData(TRUE);
	switch (m_iPanSel) 
	{
	case 0:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_AP1_START);
		break;
	case 1:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_AP2_START);
		break;
	case 2:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_FOCUS1_START);
		break;
	case 3:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_FOCUS2_START);
		break;
	case 4:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_B1_START);
		break;
	case 5:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_B2_START);
		break;
	case 6:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_UP_START);
		break;
	case 7:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_DOWN_START);
		break;
	case 8:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_LEFT_START);
		break;
	case 9:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_RIGHT_START);
		break;
	default:
		break;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnStop
  Desc:		press panel key [stop]
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteKey::OnBnClickedBtnStop()
{
	UpdateData(TRUE);
	switch (m_iPanSel)
	{
	case 0:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_AP1_STOP);
		break;
	case 1:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_AP2_STOP);
		break;
	case 2:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_FOCUS1_STOP);
		break;
	case 3:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_FOCUS2_STOP);
		break;
	case 4:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_B1_STOP);
		break;
	case 5:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_B2_STOP);
		break;
	case 6:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_UP_STOP);
		break;
	case 7:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_DOWN_STOP);
		break;
	case 8:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_LEFT_STOP);
		break;
	case 9:
		NET_DVR_ClickKey(m_lServerID, KEY_PTZ_RIGHT_STOP);
		break;
	default:
		break;
	}
}

/*********************************************************
  Function:	OnBtnStartPanel
  Desc:		enable to operate the panel key 
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtnStartPanel() 
{
	// TODO: Add your control notification handler code here
	if (NET_DVR_LockPanel(m_lServerID))
	{
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_LockPanel");
	}
	else
	{
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_LockPanel");
	}	
}

/*********************************************************
  Function:	OnBtnStopPanel
  Desc:		disable to operate the panel key
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteKey::OnBtnStopPanel() 
{
	if (NET_DVR_UnLockPanel(m_lServerID))
	{
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UnLockPanel");
	}
	else
	{
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UnLockPanel");
	}		
}
