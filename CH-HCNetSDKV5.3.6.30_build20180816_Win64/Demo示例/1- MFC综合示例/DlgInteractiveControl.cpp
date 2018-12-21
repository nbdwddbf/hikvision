// DlgInteractiveControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInteractiveControl.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveControl dialog


CDlgInteractiveControl::CDlgInteractiveControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInteractiveControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInteractiveControl)
	m_dwMarkBlue = 0;
	m_dwMarkGreen = 0;
	m_dwMarkRed = 0;
	m_dwPage = 0;
	m_dwRemoterParam = 0;
	m_dwSplotLightRadius = 0;
	m_dwX = 0;
	m_dwY = 0;
	m_dwFileIndex = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(&m_struScreenCtrlCmd, 0, sizeof(m_struScreenCtrlCmd));
	m_struScreenCtrlCmd.dwSize = sizeof(m_struScreenCtrlCmd);
	m_lCtrlHandle = -1;
	m_bGraspMsg = FALSE;
	m_bLButtonDown = FALSE;
}


void CDlgInteractiveControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInteractiveControl)
	DDX_Control(pDX, IDC_COMBO_MEDIA_OPERATE, m_cmbMediaOperate);
	DDX_Control(pDX, IDC_COMBO_MARK_TYPE, m_cmbMarkType);
	DDX_Control(pDX, IDC_STAT_PPT_STATUS, m_statPPTStatus);
	DDX_Control(pDX, IDC_COMBO_REMOTE_CTRL, m_cmbRemoteCtrl);
	DDX_Control(pDX, IDC_COMBO_SPOTLIGHT, m_cmbSplotLight);
	DDX_Control(pDX, IDC_COMBO_PPT, m_cmbPPT);
	DDX_Control(pDX, IDC_COMBO_MARK_TOOLS, m_cmbMarkTools);
	DDX_Control(pDX, IDC_COMBO_LINE_SIZE, m_cmbLineSize);
	DDX_Control(pDX, IDC_COMBO_CTRL_TYPE, m_cmbCtrlType);
	DDX_Text(pDX, IDC_EDIT_MARK_BLUE, m_dwMarkBlue);
	DDX_Text(pDX, IDC_EDIT_MARK_GREEN, m_dwMarkGreen);
	DDX_Text(pDX, IDC_EDIT_MARK_RED, m_dwMarkRed);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_dwPage);
	DDX_Text(pDX, IDC_EDIT_SPOTLIGHT_RADIUS, m_dwSplotLightRadius);
	DDX_Text(pDX, IDC_EDIT_X, m_dwX);
	DDX_Text(pDX, IDC_EDIT_Y, m_dwY);
	DDX_Text(pDX, IDC_EDIT_FILE_INDEX, m_dwFileIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInteractiveControl, CDialog)
	//{{AFX_MSG_MAP(CDlgInteractiveControl)
	ON_BN_CLICKED(IDC_BTN_CONTROL_OK, OnBtnControlOk)
	ON_BN_CLICKED(IDC_BTN_INTERACTIVE_EXIT, OnBtnInteractiveExit)
	ON_CBN_SELCHANGE(IDC_COMBO_CTRL_TYPE, OnSelchangeComboCtrlType)
	ON_CBN_SELCHANGE(IDC_COMBO_PPT, OnSelchangeComboPpt)
	ON_CBN_SELCHANGE(IDC_COMBO_MARK_TOOLS, OnSelchangeComboMarkTools)
	ON_CBN_SELCHANGE(IDC_COMBO_SPOTLIGHT, OnSelchangeComboSpotlight)
	ON_CBN_SELCHANGE(IDC_COMBO_MARK_TYPE, OnSelchangeComboMarkType)
	ON_WM_DESTROY()
	ON_WM_MOUSEWHEEL()
	ON_CBN_SELCHANGE(IDC_COMBO_REMOTE_CTRL, OnSelchangeComboRemoteCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveControl message handlers

void CALLBACK g_RemoteConfigCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	if (dwType != NET_SDK_CALLBACK_TYPE_DATA)
	{
		return;
	}
	if (dwBufLen != sizeof(NET_DVR_SCREEN_RESPONSE_CMD))
	{
		return;
	}
	NET_DVR_SCREEN_RESPONSE_CMD struResponse = {0};
	memcpy(&struResponse, lpBuffer, dwBufLen);
	CDlgInteractiveControl* pDlg = (CDlgInteractiveControl*)pUserData;
	CString str;
	if (struResponse.byResponseCmd == 1) //PPT状态
	{
		if (struResponse.struResonseParam.struPPTParam.byCurrentState == 1)
		{
			str.Format("正在放映PPT[%d][第%d页]", struResponse.struResonseParam.struPPTParam.dwFileIndex, struResponse.struResonseParam.struPPTParam.dwCurrentPage);
		}
		else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 2)
		{
			str.Format("停止PPT放映[%d]", struResponse.struResonseParam.struPPTParam.dwFileIndex);
		}
		else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 3)
		{
			str.Format("PPT文件已关闭[%d]", struResponse.struResonseParam.struPPTParam.dwFileIndex);
		}
		else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 4)
		{
			str.Format("PPT受保护或生产预览图失败[%d]", struResponse.struResonseParam.struPPTParam.dwFileIndex);
		}
		else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 5)
		{
			str.Format("打开放映成功[%d][共%d页]", struResponse.struResonseParam.struPPTParam.dwFileIndex, struResponse.struResonseParam.struPPTParam.dwTotalPageNum);
		}
		else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 6)
		{
			str.Format("打开放映失败[%d]", struResponse.struResonseParam.struPPTParam.dwFileIndex);
		}
		else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 7)
		{
			str.Format("PPT内容为空[%d]", struResponse.struResonseParam.struPPTParam.dwFileIndex);
		}
		else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 8)
		{
			str.Format("缩略图生成失败[%d][第%d页]", struResponse.struResonseParam.struPPTParam.dwFileIndex, struResponse.struResonseParam.struPPTParam.dwCurrentPage);
		}
        else if (struResponse.struResonseParam.struPPTParam.byCurrentState == 9)
		{
			str.Format("缩略图生成成功[%d][第%d页]", struResponse.struResonseParam.struPPTParam.dwFileIndex, struResponse.struResonseParam.struPPTParam.dwCurrentPage);
		}
        else
        {
            str.Format("未知错误[PPT状态]");
        }
	}
	else if (struResponse.byResponseCmd == 2) //文件状态
	{
        if (struResponse.struResonseParam.struFileParam.byFileState == 1)
        {
            str.Format("文件不存在[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else if (struResponse.struResonseParam.struFileParam.byFileState == 2)
        {
            str.Format("打开文件失败[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else if (struResponse.struResonseParam.struFileParam.byFileState == 3)
        {
            str.Format("打开文件成功[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else if (struResponse.struResonseParam.struFileParam.byFileState == 4)
        {
            str.Format("应用程序不存在[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else if (struResponse.struResonseParam.struFileParam.byFileState == 5)
        {
            str.Format("运行应用程序成功[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else if (struResponse.struResonseParam.struFileParam.byFileState == 6)
        {
            str.Format("运行应用程序失败[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else if (struResponse.struResonseParam.struFileParam.byFileState == 7)
        {
            str.Format("退出应用程序成功[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else if (struResponse.struResonseParam.struFileParam.byFileState == 8)
        {
            str.Format("退出应用程序失败[%d]", struResponse.struResonseParam.struFileParam.dwErrorFileIndex);
        }
        else
        {
            str.Format("未知错误[文件状态]");
        }
	}
    else
    {
        str.Format("未知回应状态类型");
    }
	pDlg->m_statPPTStatus.SetWindowText(str);
}

void CDlgInteractiveControl::OnBtnControlOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int nSel = m_cmbCtrlType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	memset(&m_struScreenCtrlCmd, 0, sizeof(m_struScreenCtrlCmd));
	m_struScreenCtrlCmd.dwSize = sizeof(m_struScreenCtrlCmd);
	m_struScreenCtrlCmd.byCmdType = nSel+1;
	switch (nSel+1)
	{
	case 1: //鼠标
		{
			m_bGraspMsg = TRUE;
			break;
		}
	case 2: //标注
		{
			int nMarkType = m_cmbMarkType.GetCurSel();
			if (nMarkType == CB_ERR)
			{
				return;
			}
			m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.byMarkEvent = nMarkType+1;
			if (nMarkType+1 == 1) //正常标注
			{
				nSel = m_cmbMarkTools.GetCurSel();
				if (nSel == CB_ERR)
				{
					return;
				}
				m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.byMarkTool = nSel+1;
				if (nSel+1 == 1) //画笔
				{
					m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.struColor.byBlue = m_dwMarkBlue;
					m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.struColor.byGreen = m_dwMarkGreen;
					m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.struColor.byRed = m_dwMarkRed;
				}
				int nLine = m_cmbLineSize.GetCurSel();
				if (nLine == CB_ERR)
				{
					return;
				}
				m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.byLineWidth = nLine+1;
				m_bGraspMsg = TRUE;
			}
			else
			{
				m_bGraspMsg = FALSE;
			}
			break;
		}
	case 3: //键盘
		{
			m_bGraspMsg = TRUE;
			break;
		}
	case 4: //PPT
		{
			nSel = m_cmbPPT.GetCurSel();
			if (nSel == CB_ERR)
			{
				return;
			}
			m_struScreenCtrlCmd.struScreenCtrlParam.struPPTParam.byPPTAction = nSel+1;
			if (nSel+1 == 8) //激光笔
			{
				m_bGraspMsg = TRUE;
			}
			else
			{
				if (nSel+1 == 7) //跳转需要具体数值
				{
					m_struScreenCtrlCmd.struScreenCtrlParam.struPPTParam.dwPPTNo = m_dwPage;
				}
				m_bGraspMsg = FALSE;
			}
			break;
		}
	case 5: //远程控制
		{
			nSel = m_cmbRemoteCtrl.GetCurSel();
			if (nSel == CB_ERR)
			{
				return;
			}
			m_struScreenCtrlCmd.struScreenCtrlParam.struRemoteCtrlParam.byRemoteCtrlCmd = nSel+1;
			if (nSel+1 == 3 || nSel +1 == 4 || nSel+1 == 5 || nSel+1 == 9 || nSel+1== 10) //打开、关闭、删除文件、运行应用程序、停止应用程序
			{
				m_struScreenCtrlCmd.struScreenCtrlParam.struRemoteCtrlParam.dwCtrlParam = m_dwFileIndex;
			}
			m_bGraspMsg = FALSE;
			break;
		}
	case 6: //聚光灯
		{
			nSel = m_cmbSplotLight.GetCurSel();
			if (nSel == CB_ERR)
			{
				return;
			}
			m_struScreenCtrlCmd.struScreenCtrlParam.struSpotLight.byCmd = nSel;
			if (nSel == 1 || nSel == 2) //打开聚光灯/聚光灯位置移动
			{
				m_struScreenCtrlCmd.struScreenCtrlParam.struSpotLight.dwRadius = m_dwSplotLightRadius;
				m_struScreenCtrlCmd.struScreenCtrlParam.struSpotLight.struPoint.wX = m_dwX;
				m_struScreenCtrlCmd.struScreenCtrlParam.struSpotLight.struPoint.wY = m_dwY;
			}
			m_bGraspMsg = FALSE;
			break;
		}
	case 7: //触摸板
		{
			m_bGraspMsg = TRUE;
			break;
		}
	case 8: //多媒体操作
		{
			m_struScreenCtrlCmd.struScreenCtrlParam.struMediaListParam.byOperateCmd = m_cmbMediaOperate.GetCurSel()+1;
			m_bGraspMsg = FALSE;
			break;
		}
	}
	if (!m_bGraspMsg)
	{
		if (NET_DVR_SendRemoteConfig(m_lCtrlHandle, ENUM_DVR_SCREEN_CTRL_CMD, (char*)&m_struScreenCtrlCmd, sizeof(m_struScreenCtrlCmd)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SendRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
		}
	}
}

void CDlgInteractiveControl::OnBtnInteractiveExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInteractiveControl::OnSelchangeComboCtrlType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbCtrlType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	GetDlgItem(IDC_COMBO_MARK_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_MARK_TOOLS)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_LINE_SIZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MARK_RED)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MARK_GREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MARK_BLUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_PPT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_REMOTE_CTRL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FILE_INDEX)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SPOTLIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SPOTLIGHT_RADIUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
	switch (nSel+1)
	{
	case 1: //鼠标
		{
			break;
		}
	case 2: //标注
		{
			GetDlgItem(IDC_COMBO_MARK_TYPE)->EnableWindow(TRUE);
			OnSelchangeComboMarkType();
			break;
		}
	case 3: //键盘
		{
			break;
		}
	case 4: //PPT
		{
			GetDlgItem(IDC_COMBO_PPT)->EnableWindow(TRUE);
			OnSelchangeComboPpt();
			break;
		}
	case 5: //远程控制
		{
			GetDlgItem(IDC_COMBO_REMOTE_CTRL)->EnableWindow(TRUE);
			break;
		}
	case 6: //聚光灯
		{
			GetDlgItem(IDC_COMBO_SPOTLIGHT)->EnableWindow(TRUE);
			OnSelchangeComboSpotlight();
			break;
		}
	}
}

void CDlgInteractiveControl::OnSelchangeComboPpt() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbPPT.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	if (nSel+1 == 7) //页面跳转
	{
		GetDlgItem(IDC_EDIT_PAGE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PAGE)->EnableWindow(FALSE);
	}
}

void CDlgInteractiveControl::OnSelchangeComboMarkTools() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbMarkTools.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	if (nSel+1 == 1) //画笔
	{
		GetDlgItem(IDC_EDIT_MARK_RED)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MARK_GREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MARK_BLUE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MARK_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MARK_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MARK_BLUE)->EnableWindow(FALSE);
	}
}

void CDlgInteractiveControl::OnSelchangeComboSpotlight() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbSplotLight.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	if (nSel == 1 || nSel == 2) //开启聚光灯/聚光灯移动
	{
		GetDlgItem(IDC_EDIT_SPOTLIGHT_RADIUS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_SPOTLIGHT_RADIUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
	}
}

void CDlgInteractiveControl::OnSelchangeComboMarkType()
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbMarkType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	if (nSel+1 == 1) //正常标注
	{
		GetDlgItem(IDC_COMBO_MARK_TOOLS)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LINE_SIZE)->EnableWindow(TRUE);
		OnSelchangeComboMarkTools();
	}
	else
	{
		GetDlgItem(IDC_COMBO_MARK_TOOLS)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LINE_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MARK_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MARK_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MARK_BLUE)->EnableWindow(FALSE);
	}
}

void CDlgInteractiveControl::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_lCtrlHandle == -1)
	{
		return;
	}
	if (!NET_DVR_StopRemoteConfig(m_lCtrlHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
	}
}

BOOL CDlgInteractiveControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbCtrlType.SetCurSel(0);
	OnSelchangeComboCtrlType();
	m_lCtrlHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_START_SCREEN_CRTL, NULL, 0, g_RemoteConfigCallback, this);
//     NET_SDK_LED_SCREEN_CHECK_PARAM struParam = { 0 };
//     struParam.dwSize = sizeof(struParam);
//     struParam.byOperateType = 1;
//     struParam.byIsRGBSynChk = 1;
//     struParam.dwRectCount = 1;
//     struParam.wRgbPermil = 100;
//     struParam.struRectList[0].dwWidth = 1920;
//     struParam.struRectList[0].dwHeight = 1080;
//     m_lCtrlHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_SDK_LED_SCREEN_CHECK, &struParam, struParam.dwSize, g_RemoteConfigCallback, this);
	if (m_lCtrlHandle < 0)
	{
		char sTitle[64] = {0};
		char sMsg[64] = {0};
		g_StringLanType(sTitle, "屏幕互动", "Screen Interactive");
		g_StringLanType(sMsg, "初始化失败", "Initialize failed.");
		MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_START_SCREEN_CRTL");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig NET_DVR_START_SCREEN_CRTL");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgInteractiveControl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!m_bGraspMsg)
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
	
	BOOL bSendCmmd = FALSE;
	
	CRect rcClient;
	GetDlgItem(IDC_STATIC_CLIENT)->GetWindowRect(&rcClient);
	ScreenToClient(&rcClient);
	CPoint ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(&ptCursor);
	
	int nSel = m_cmbCtrlType.GetCurSel();
	switch (nSel+1)
	{
	case 1: //鼠标
		{
			if (PtInRect(rcClient, ptCursor))
			{
				m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.struMousePoint.wX = (DWORD)((double)(ptCursor.x-rcClient.left)*10000/rcClient.Width());
				m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.struMousePoint.wY = (DWORD)((double)(ptCursor.y-rcClient.top)*10000/rcClient.Height());
				switch (pMsg->message)
				{
				case WM_LBUTTONDOWN:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 1;
						bSendCmmd = TRUE;
						break;
					}
				case WM_LBUTTONUP:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 2;
						bSendCmmd = TRUE;
						break;
					}
				case WM_RBUTTONDOWN:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 3;
						bSendCmmd = TRUE;
						break;
					}
				case WM_RBUTTONUP:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 4;
						bSendCmmd = TRUE;
						break;
					}
				case WM_MOUSEMOVE:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 5;
						bSendCmmd = TRUE;
						break;
					}
				case NM_CLICK:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 6;
						bSendCmmd = TRUE;
						break;
					}
				case NM_DBLCLK:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 7;
						bSendCmmd = TRUE;
						break;
					}
				case NM_RCLICK:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 8;
						bSendCmmd = TRUE;
						break;
					}
				}
			}
			break;
		}
	case 2: //标注
		{
			if (PtInRect(rcClient, ptCursor))
			{
				m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.struPoint.wX = (DWORD)((double)(ptCursor.x-rcClient.left)*10000/rcClient.Width());
				m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.struPoint.wY = (DWORD)((double)(ptCursor.y-rcClient.top)*10000/rcClient.Height());
				if (pMsg->message == WM_LBUTTONDOWN)
				{
					m_bLButtonDown = TRUE;
					m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.byMouseEvent = 1;
					bSendCmmd = TRUE;
				}
				if (pMsg->message == WM_LBUTTONUP)
				{
					m_bLButtonDown = FALSE;
					m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.byMouseEvent = 2;
					bSendCmmd = TRUE;
				}
				if (pMsg->message == WM_MOUSEMOVE && m_bLButtonDown)
				{
					m_struScreenCtrlCmd.struScreenCtrlParam.struMarkParam.byMouseEvent = 3;
					bSendCmmd = TRUE;
				}
			}
			break;
		}
	case 3: //键盘
		{
			if (pMsg->message == WM_KEYDOWN)
			{
				m_struScreenCtrlCmd.struScreenCtrlParam.struKeyboardInfo.dwKeyValue = pMsg->wParam;
				bSendCmmd = TRUE;
			}
			break;
		}
	case 4: //PPT
		{
			nSel = m_cmbPPT.GetCurSel();
			if (nSel+1 == 8) //激光笔
			{
				if (PtInRect(rcClient, ptCursor))
				{
					m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.struMousePoint.wX = (DWORD)((double)(ptCursor.x-rcClient.left)*10000/rcClient.Width());
					m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.struMousePoint.wY = (DWORD)((double)(ptCursor.y-rcClient.top)*10000/rcClient.Height());
					if (pMsg->message == WM_LBUTTONDOWN)
					{
						m_bLButtonDown = TRUE;
						m_struScreenCtrlCmd.struScreenCtrlParam.struPPTParam.byPPTAction = 8;
						bSendCmmd = TRUE;
					}
					if (pMsg->message == WM_LBUTTONUP)
					{
						m_bLButtonDown = FALSE;
						m_struScreenCtrlCmd.struScreenCtrlParam.struPPTParam.byPPTAction = 9;
						bSendCmmd = TRUE;
					}
					if (pMsg->message == WM_MOUSEMOVE && m_bLButtonDown == TRUE)
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struPPTParam.byPPTAction = 10;
						bSendCmmd = TRUE;
					}
				}
			}
			break;
		}
	case 7: //触摸板
		{
			if (PtInRect(rcClient, ptCursor))
			{
				switch (pMsg->message)
				{
				case WM_LBUTTONDOWN:
					{
						m_bLButtonDown = TRUE;
						m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 1;
						m_ptPrePoint = ptCursor; //记录原点
						bSendCmmd = TRUE;
						break;
					}
				case WM_LBUTTONUP:
					{
						m_bLButtonDown = FALSE;
						m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 2;
						bSendCmmd = TRUE;
						break;
					}
				case WM_RBUTTONDOWN:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 3;
						bSendCmmd = TRUE;
						break;
					}
				case WM_RBUTTONUP:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 4;
						bSendCmmd = TRUE;
						break;
					}
				case WM_MOUSEMOVE:
					{
						if (m_bLButtonDown)
						{
							m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 5;
							m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.iXDisplacement = (DWORD)((double)(ptCursor.x-rcClient.left)*10000/rcClient.Width());
							m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.iYDisplacement = (DWORD)((double)(ptCursor.y-rcClient.top)*10000/rcClient.Height());
							m_ptPrePoint = ptCursor; //记录原点
							bSendCmmd = TRUE;
						}
						break;
					}
				case NM_CLICK:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 6;
						bSendCmmd = TRUE;
						break;
					}
				case NM_DBLCLK:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 7;
						bSendCmmd = TRUE;
						break;
					}
				case NM_RCLICK:
					{
						m_struScreenCtrlCmd.struScreenCtrlParam.struTouchPadParam.byMouseEvent = 8;
						bSendCmmd = TRUE;
						break;
					}
				}
			}
			break;
		}
	}
	if (bSendCmmd)
	{
 		if (NET_DVR_SendRemoteConfig(m_lCtrlHandle, ENUM_DVR_SCREEN_CTRL_CMD, (char*)&m_struScreenCtrlCmd, sizeof(m_struScreenCtrlCmd)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SendRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
		}
		return TRUE;
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
}

BOOL CDlgInteractiveControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bGraspMsg)
	{
		return CDialog::OnMouseWheel(nFlags, zDelta, pt);
	}
	
	BOOL bSendCmmd = FALSE;
	
	CRect rcClient;
	GetDlgItem(IDC_STATIC_CLIENT)->GetWindowRect(&rcClient);
	ScreenToClient(&rcClient);
	CPoint ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(&ptCursor);
	
	int nSel = m_cmbCtrlType.GetCurSel();
	switch (nSel+1)
	{
	case 1: //鼠标
		{
			if (PtInRect(rcClient, ptCursor))
			{
				m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.struMousePoint.wX = (DWORD)((double)(ptCursor.x-rcClient.left)*10000/rcClient.Width());
				m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.struMousePoint.wY = (DWORD)((double)(ptCursor.y-rcClient.top)*10000/rcClient.Height());
				if (zDelta == 120) //向上滚动
				{
					m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 12;
					bSendCmmd = TRUE;
				}
				else if (zDelta == -120) //向下滚动
				{
					m_struScreenCtrlCmd.struScreenCtrlParam.struMouseParam.byMouseEvent = 11;
					bSendCmmd = TRUE;
				}
			}
		}
	}
	if (bSendCmmd)
	{
		if (NET_DVR_SendRemoteConfig(m_lCtrlHandle, ENUM_DVR_SCREEN_CTRL_CMD, (char*)&m_struScreenCtrlCmd, sizeof(m_struScreenCtrlCmd)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SendRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig ENUM_DVR_SCREEN_CTRL_CMD");
		}
		return TRUE;
	}
	else
	{
 		return CDialog::OnMouseWheel(nFlags, zDelta, pt);
	}
}

void CDlgInteractiveControl::OnSelchangeComboRemoteCtrl() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbRemoteCtrl.GetCurSel();
	if (nSel+1 == 3 || nSel+1 == 4 || nSel+1 == 5 || nSel+1 == 8 || nSel+1 == 9 || nSel+1 == 10)
	{
		GetDlgItem(IDC_EDIT_FILE_INDEX)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_FILE_INDEX)->EnableWindow(FALSE);
	}
}
