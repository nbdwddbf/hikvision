// DlgDPCCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDPCCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDPCCfg dialog

//CDlgDPCCfg *lpDPCCfgDlg = NULL;

CDlgDPCCfg::CDlgDPCCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDPCCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDPCCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_lChannel = 1;
	m_iDevIndex = -1;
	m_lPlayHandle = -1;
	memset(&m_struDpcParam, 0, sizeof(m_struDpcParam));
	m_struDpcParam.dwSize = sizeof(m_struDpcParam);
}


void CDlgDPCCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDPCCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_DPC_MODE, m_comboDPCMode);
}


BEGIN_MESSAGE_MAP(CDlgDPCCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgDPCCfg)
	ON_BN_CLICKED(IDC_BTN_DPC_CORRECT, OnBtnDpcCorrect)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_DPC_RIGHT, OnBtnDpcRight)
	ON_BN_CLICKED(IDC_BTN_DPC_DOWN, OnBtnDpcDown)
	ON_BN_CLICKED(IDC_BTN_DPC_UP, OnBtnDpcUp)
	ON_BN_CLICKED(IDC_BTN_DPC_LEFT, OnBtnDpcLeft)
	ON_BN_CLICKED(IDC_BTN_DPC_CORRECT_CANCEL, OnBtnDpcCorrectCancel)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_DPC_SAVE, &CDlgDPCCfg::OnBnClickedBtnDpcSave)
    ON_BN_CLICKED(IDC_BTN_ALL_CORRECT, &CDlgDPCCfg::OnBnClickedBtnAllCorrect)
    ON_CBN_SELCHANGE(IDC_COMBO_DPC_MODE, &CDlgDPCCfg::OnCbnSelchangeComboDpcMode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDPCCfg message handlers

// void CALLBACK DrawDPCShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
// {
// // 	SetBkMode(hDc, TRANSPARENT);
// // 	SetTextColor(hDc, RGB(255, 255, 255));
// //	lpDPCCfgDlg->F_DrawFun(lRealHandle, hDc, dwUser);     
// }

BOOL CDlgDPCCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//lpDPCCfgDlg = this;
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
	ScreenToClient(&m_rcWnd);
    m_comboDPCMode.SetCurSel(0);
	
	Play();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CDlgDPCCfg::~CDlgDPCCfg()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	
	CloseShowDPC();
}

BOOL CDlgDPCCfg::Play()
{
	char szLan[64] = {0};
	char szTemp[128] = {0};
	NET_DVR_CLIENTINFO struPlayInfo; 
	memset(&struPlayInfo, 0, sizeof(NET_DVR_CLIENTINFO));
	
    struPlayInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
	struPlayInfo.lChannel = m_lChannel;
	struPlayInfo.lLinkMode = 0;
	
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	
	m_lPlayHandle = NET_DVR_RealPlay_V30(m_lUserID, &struPlayInfo, NULL, NULL, TRUE); 
	BOOL bRet = FALSE;
	if (m_lPlayHandle < 0)
	{
		g_StringLanType(szLan, "预览失败", "Realplay failed");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
        AfxMessageBox(szTemp);
		return FALSE;
	}
	
	//bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawDPCShow, 0);
	
	ShowDPC();

	return TRUE;
}

void CDlgDPCCfg::CloseShowDPC()
{
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_CROSS_DISPALY_CLOSE;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_CROSS_DISPALY_CLOSE");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("坏点检测十字叉显示关闭 失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_CROSS_DISPALY_CLOSE");
        return; 
	} 
}

void CDlgDPCCfg::ShowDPC() 
{
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_CROSS_DISPALY_OPEN;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_CROSS_DISPALY_OPEN");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("坏点检测十字叉显示开启 失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_CROSS_DISPALY_OPEN");
        return; 
	} 
}

void CDlgDPCCfg::OnBtnDpcCorrect() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_CORRECT;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL PDC_CORRECT");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("校正失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL PDC_CORRECT");
        return; 
	} 
}

void CDlgDPCCfg::OnBtnDpcCorrectCancel() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_CORRECT_CANCEL;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_CORRECT_CANCEL");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("取消校正失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_CORRECT_CANCEL");
        return; 
	} 	
}

void CDlgDPCCfg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);

    UpdateData(TRUE);

    if (!m_rcWnd.PtInRect(point) || m_comboDPCMode.GetCurSel() != 0)
    {
        return;
    }

    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();

	
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_POINT;
	m_struDpcParam.struPoint.fX = (float)(point.x - m_rcWnd.left) / (float)m_rcWnd.Width();
	m_struDpcParam.struPoint.fY  = (float)(point.y - m_rcWnd.top)  / (float)m_rcWnd.Height();

	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_POINT");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("坏点校正坐标 设置失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_POINT");
        return; 
	} 	
}

void CDlgDPCCfg::OnBtnDpcRight() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_RIGHT;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_RIGHT");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("坏点校正坐标点向右偏移 失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_RIGHT");
        return; 
	} 
}

void CDlgDPCCfg::OnBtnDpcDown() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_DOWN;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_DOWN");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("坏点校正坐标点向下偏移 失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_DOWN");
        return; 
	} 
}

void CDlgDPCCfg::OnBtnDpcUp() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_UP;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_UP");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("坏点校正坐标点向上偏移 失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_UP");
        return; 
	} 
}

void CDlgDPCCfg::OnBtnDpcLeft() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
	m_struDpcParam.dwChannel = m_lChannel;
	m_struDpcParam.wCtrlType = DPC_LEFT;
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_LEFT");
        return; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("坏点校正坐标点向左偏移 失败, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_LEFT");
        return; 
	} 
}




void CDlgDPCCfg::OnBnClickedBtnDpcSave()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
    m_struDpcParam.dwChannel = m_lChannel;
    m_struDpcParam.wCtrlType = DPC_SAVE;
    if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_ALL_CORRECT");
        return;
    }
    else
    {
        CString csError;
        csError.Format(_T("坏点保存 失败, Error Code %d"), NET_DVR_GetLastError());
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_SAVE");
        return;
    }
}


void CDlgDPCCfg::OnBnClickedBtnAllCorrect()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struDpcParam.byDPCMode = m_comboDPCMode.GetCurSel();
    m_struDpcParam.dwChannel = m_lChannel;
    m_struDpcParam.wCtrlType = DPC_ALL_CORRECT;
    if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_DPC_CTRL, &m_struDpcParam, sizeof(m_struDpcParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DPC_CTRL DPC_ALL_CORRECT");
        return;
    }
    else
    {
        CString csError;
        csError.Format(_T("所有坏点校正 失败, Error Code %d"), NET_DVR_GetLastError());
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DPC_CTRL DPC_ALL_CORRECT");
        return;
    }
}


void CDlgDPCCfg::OnCbnSelchangeComboDpcMode()
{
    // TODO:  在此添加控件通知处理程序代码

    if (m_comboDPCMode.GetCurSel() == 0)
    {
        GetDlgItem(IDC_BTN_DPC_UP)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_DPC_LEFT)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_DPC_RIGHT)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_DPC_DOWN)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_DPC_CORRECT_CANCEL)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_DPC_SAVE)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_ALL_CORRECT)->ShowWindow(TRUE);
        ShowDPC();
    }
    else if (m_comboDPCMode.GetCurSel() == 1)
    {
        GetDlgItem(IDC_BTN_DPC_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_DPC_LEFT)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_DPC_RIGHT)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_DPC_DOWN)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_DPC_CORRECT_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_DPC_SAVE)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ALL_CORRECT)->ShowWindow(FALSE);
        CloseShowDPC();
    }
}

