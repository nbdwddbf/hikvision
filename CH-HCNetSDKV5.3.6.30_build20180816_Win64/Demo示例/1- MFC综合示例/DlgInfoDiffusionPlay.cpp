// DlgInfoDiffusionPlay.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionPlay.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionPlay dialog

void CALLBACK ProcessInsertPlayProgress(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{

    CDlgInfoDiffusionPlay* pDlg = (CDlgInfoDiffusionPlay*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    CString strTips;
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        if (lpBuffer == NULL || dwBufLen != sizeof(NET_DVR_INSERTPLAY_PROGRESS_RESULT))
        {
            return;
        }
        LPNET_DVR_INSERTPLAY_PROGRESS_RESULT lpProgress = (LPNET_DVR_INSERTPLAY_PROGRESS_RESULT)lpBuffer;
        if (lpProgress->dwSubProgressNum == 0)
        {
            strTips.Format("终端插播总进度[%d", lpProgress->dwMainProgress);
            strTips += _T("%]");
        }
        else
        {
            strTips.Format("终端组插播进度[%d", lpProgress->dwMainProgress);
            strTips += _T("%]");
        }
        pDlg->ShowReleaseProgress(lpProgress->dwMainProgress, strTips);

    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS && *(DWORD*)lpBuffer == NET_SDK_CALLBACK_STATUS_SUCCESS)
    {
        strTips += _T("完成插播[100%]");
        pDlg->ShowReleaseProgress(100, strTips);
        pDlg->PostMessage(WM_STOP_REMOTE_CFG, 0, 0);

    }

}

CDlgInfoDiffusionPlay::CDlgInfoDiffusionPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionPlay::IDD, pParent)
    , m_dateTime(COleDateTime::GetCurrentTime())
    , m_timeTime(COleDateTime::GetCurrentTime())
    , m_csCtrlType(_T(""))
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionPlay)
	m_dwTerminalID = 0;
	m_dwProgramID = 0;
	m_dwProgramDuration = 0;
	m_dwPrtScnID = 0;
	m_dwMaterialID = 0;
	m_dwPlayCount = 0;
	m_dwPositionHeight = 0;
	m_dwPositionWidth = 0;
	m_dwPositionX = 0;
	m_dwPositionY = 0;
	m_bFontEnable = FALSE;
	m_dwFontSize = 0;
	m_dwFontSpeed = 0;
	m_dwBackBlue = 0;
	m_dwBackGreen = 0;
	m_dwBackRed = 0;
	m_dwFontBlue = 0;
	m_dwFontGreen = 0;
	m_dwFontRed = 0;
	m_bPlanEnable = FALSE;
	m_dwTransparent = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_nCurSelTerminal = -1;
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
	m_pImageBuffer = NULL;
	m_lpControl = new NET_DVR_PLAY_CONTROL;
	memset(m_lpControl, 0, sizeof(*m_lpControl));
	m_lpControl->dwSize = sizeof(*m_lpControl);
}


void CDlgInfoDiffusionPlay::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionPlay)
    DDX_Control(pDX, IDC_COMBO_FONT, m_cmbFontDirect);
    DDX_Control(pDX, IDC_COMBO_PLAY_MODE, m_cmbPlayMode);
    DDX_Control(pDX, IDC_COMBO_CTRL_TYPE, m_cmbCtrlType);
    DDX_Control(pDX, IDC_COMBO_INSERT_TYPE, m_cmbInsertType);
    DDX_Control(pDX, IDC_COMBO_TARGET_TYPE, m_cmbTargetType);
    DDX_Control(pDX, IDC_COMBO_PLAN_TYPE, m_cmbPlanType);
    DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
    DDX_Text(pDX, IDC_EDIT_TERMINAL_ID, m_dwTerminalID);
    DDX_Text(pDX, IDC_EDIT_PROGRAM_ID, m_dwProgramID);
    DDX_Text(pDX, IDC_EDIT_PROGRAM_DURATION, m_dwProgramDuration);
    DDX_Text(pDX, IDC_EDIT_PRTSCN_ID, m_dwPrtScnID);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_ID, m_dwMaterialID);
    DDX_Text(pDX, IDC_EDIT_PLAY_COUNT, m_dwPlayCount);
    DDX_Text(pDX, IDC_EDIT_POSITION_HEIGHT, m_dwPositionHeight);
    DDX_Text(pDX, IDC_EDIT_POSITION_WIDTH, m_dwPositionWidth);
    DDX_Text(pDX, IDC_EDIT_POSITION_X, m_dwPositionX);
    DDX_Text(pDX, IDC_EDIT_POSITION_Y, m_dwPositionY);
    DDX_Check(pDX, IDC_CHECK_FONT_ENABLE, m_bFontEnable);
    DDX_Text(pDX, IDC_EDIT_FONT_SIZE, m_dwFontSize);
    DDX_Text(pDX, IDC_EDIT_FONT_SPEED, m_dwFontSpeed);
    DDX_Text(pDX, IDC_EDIT_BACK_BLUE, m_dwBackBlue);
    DDX_Text(pDX, IDC_EDIT_BACK_GREEN, m_dwBackGreen);
    DDX_Text(pDX, IDC_EDIT_BACK_RED, m_dwBackRed);
    DDX_Text(pDX, IDC_EDIT_FONT_BLUE, m_dwFontBlue);
    DDX_Text(pDX, IDC_EDIT_FONT_GREEN, m_dwFontGreen);
    DDX_Text(pDX, IDC_EDIT_FONT_RED, m_dwFontRed);
    DDX_Check(pDX, IDC_CHECK_PLAN, m_bPlanEnable);
    DDX_Text(pDX, IDC_EDIT_TRANSPARENT, m_dwTransparent);
    //}}AFX_DATA_MAP
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DATE, m_dateTime);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_timeTime);
    DDX_CBString(pDX, IDC_COMBO_TARGET_TYPE, m_csCtrlType);
    DDX_Control(pDX, IDC_INSERTPLAY_PROGRESS, m_progressInsertPlay);
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionPlay, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionPlay)
	ON_CBN_SELCHANGE(IDC_COMBO_CTRL_TYPE, OnSelchangeComboCtrlType)
	ON_CBN_SELCHANGE(IDC_COMBO_INSERT_TYPE, OnSelchangeComboInsertType)
	ON_CBN_SELCHANGE(IDC_COMBO_TARGET_TYPE, OnSelchangeComboTargetType)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_CONTROL, OnBtnControl)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_BN_CLICKED(IDC_BTN_PRTSCN, OnBtnPrtscn)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, OnClickListTerminal)
	ON_CBN_SELCHANGE(IDC_COMBO_PLAY_MODE, OnSelchangeComboPlayMode)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_STOP_REMOTE_CFG, OnStopRemoteConfig)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionPlay message handlers

BOOL CDlgInfoDiffusionPlay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitTerminalCtrlList();
	m_cmbCtrlType.SetCurSel(0);
	OnSelchangeComboCtrlType();
	m_cmbTargetType.SetCurSel(0);
	OnSelchangeComboTargetType();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionPlay::OnSelchangeComboCtrlType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbCtrlType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strCtrlType;
	m_cmbCtrlType.GetLBText(nSel, strCtrlType);
	if (0 == strcmp(strCtrlType, "insert"))
	{
		GetDlgItem(IDC_COMBO_INSERT_TYPE)->EnableWindow(TRUE);
		m_cmbInsertType.SetCurSel(0);
		OnSelchangeComboInsertType();
	}
	else
	{
		GetDlgItem(IDC_COMBO_INSERT_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MATERIAL_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PROGRAM_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLAY_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PLAY_COUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PROGRAM_DURATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POSITION_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POSITION_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POSITION_WIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POSITION_HEIGHT)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_BACK_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BACK_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BACK_BLUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_BLUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_SPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FONT_ENABLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_FONT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRANSPARENT)->EnableWindow(FALSE);

	}
}

void CDlgInfoDiffusionPlay::OnSelchangeComboInsertType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbInsertType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strInsertType;
	m_cmbInsertType.GetLBText(nSel, strInsertType);
	if (0 == strcmp(strInsertType, "material"))
	{
		GetDlgItem(IDC_EDIT_MATERIAL_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PROGRAM_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PLAY_MODE)->EnableWindow(TRUE);
		m_cmbPlayMode.SetCurSel(0);
		OnSelchangeComboPlayMode();
		GetDlgItem(IDC_EDIT_POSITION_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POSITION_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POSITION_WIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POSITION_HEIGHT)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_BACK_RED)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_BACK_GREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_BACK_BLUE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FONT_RED)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FONT_GREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FONT_BLUE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FONT_SIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FONT_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_FONT_ENABLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FONT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TRANSPARENT)->EnableWindow(TRUE);
	}
	else if (0 == strcmp(strInsertType, "program"))
	{
		GetDlgItem(IDC_EDIT_MATERIAL_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BACK_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BACK_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BACK_BLUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_BLUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FONT_SPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FONT_ENABLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_FONT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRANSPARENT)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_PROGRAM_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PLAY_MODE)->EnableWindow(TRUE);
		m_cmbPlayMode.SetCurSel(0);
		OnSelchangeComboPlayMode();
		GetDlgItem(IDC_EDIT_POSITION_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POSITION_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POSITION_WIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POSITION_HEIGHT)->EnableWindow(TRUE);
	}
}

void CDlgInfoDiffusionPlay::OnSelchangeComboTargetType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbTargetType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strTargetType;
	m_cmbTargetType.GetLBText(nSel, strTargetType);
	if (0 == strcmp(strTargetType, "terminals"))
	{
		char szLan[512] = {0};
		g_StringLanType(szLan, "终端编号", "Terminal No.");
		GetDlgItem(IDC_STAT_TERMINAL_ID)->SetWindowText(szLan);
	}
	else if (0 == strcmp(strTargetType, "terminalGroups"))
	{
		char szLan[512] = {0};
		g_StringLanType(szLan, "终端组编号", "Group No.");
		GetDlgItem(IDC_STAT_TERMINAL_ID)->SetWindowText(szLan);
	}
	RefreshTernimalList(strTargetType);
}

void CDlgInfoDiffusionPlay::InitTerminalCtrlList()
{
	DWORD dwExStyle = m_listTerminal.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listTerminal.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listTerminal.InsertColumn(0, szLan);
	m_listTerminal.SetColumnWidth(0, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "编号", "Number");
	m_listTerminal.InsertColumn(1, szLan);
	m_listTerminal.SetColumnWidth(1, 100);
}

void CDlgInfoDiffusionPlay::RefreshTernimalList(CString strTargetType)
{
	m_listTerminal.DeleteAllItems();
	CString str;
	if (0 == strcmp(strTargetType, "terminals"))
	{
		for (int nTerCnt = 0; nTerCnt < m_lpControl->dwTerminalCount; nTerCnt++)
		{
			str.Format("%d", nTerCnt+1);
			m_listTerminal.InsertItem(nTerCnt, str);
			str.Format("%d", m_lpControl->dwTerminalList[nTerCnt]);
			m_listTerminal.SetItemText(nTerCnt, 1, str);
		}
	}
	else if (0 == strcmp(strTargetType, "terminalGroups"))
	{
		for (int nGrpCnt = 0; nGrpCnt < m_lpControl->dwGroupCount; nGrpCnt++)
		{
			str.Format("%d", nGrpCnt+1);
			m_listTerminal.InsertItem(nGrpCnt, str);
			str.Format("%d", m_lpControl->dwTerminalGroupList[nGrpCnt]);
			m_listTerminal.SetItemText(nGrpCnt, 1, str);
		}
	}
}

void CDlgInfoDiffusionPlay::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int nSel = m_cmbTargetType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strTargetType;
	m_cmbTargetType.GetLBText(nSel, strTargetType);
	int nIndex = m_listTerminal.GetItemCount();
	if (0 == strcmp(strTargetType, "terminals"))
	{
		m_lpControl->dwTerminalList[nIndex] = m_dwTerminalID;
		m_lpControl->dwTerminalCount++;
	}
    else if (0 == strcmp(strTargetType, "terminalGroups") || 0 == strcmp(strTargetType, "byOrg"))
	{
		m_lpControl->dwTerminalGroupList[nIndex] = m_dwTerminalID;
		m_lpControl->dwGroupCount++;
	}
	CString str;
	str.Format("%d", nIndex+1);
	m_listTerminal.InsertItem(nIndex, str);
	m_listTerminal.SetItemState(m_nCurSelTerminal, 0, -1);
	m_listTerminal.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listTerminal.SetFocus();
	m_nCurSelTerminal = nIndex;
	str.Format("%d", m_dwTerminalID);
	m_listTerminal.SetItemText(nIndex, 1, str);
}

void CDlgInfoDiffusionPlay::OnBtnControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_INSERTPLAY_PROGRESS_COND struCond = { 0 };
	int nSel = m_cmbCtrlType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbCtrlType.GetLBText(nSel, m_lpControl->szControlType);
	
	nSel = m_cmbTargetType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbTargetType.GetLBText(nSel, m_lpControl->szTargetType);
	if (0 == strcmp(m_lpControl->szControlType, "insert"))
	{
		nSel = m_cmbInsertType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "播放控制", "Play Control");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbInsertType.GetLBText(nSel, m_lpControl->struInsertInfo.szInsertType);
		if (0 == strcmp(m_lpControl->struInsertInfo.szInsertType, "material"))
		{
            struCond.dwInsertNo = m_dwMaterialID;
            struCond.byInsertType = 1;
			m_lpControl->struInsertInfo.dwMaterialID = m_dwMaterialID;
			nSel = m_cmbPlayMode.GetCurSel();
			if (nSel == CB_ERR)
			{
				char szLan1[512] = {0};
				char szLan2[512] = {0};
				g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
				g_StringLanType(szLan2, "播放控制", "Play Control");
				MessageBox(szLan1, szLan2, MB_ICONWARNING);
				return;
			}
			m_cmbPlayMode.GetLBText(nSel, m_lpControl->struInsertInfo.szPlayMode);
			if (0 == strcmp(m_lpControl->struInsertInfo.szPlayMode, "byTime"))
			{
				m_lpControl->struInsertInfo.dwDuration = m_dwProgramDuration;
			}
			else if (0 == strcmp(m_lpControl->struInsertInfo.szPlayMode, "byCount"))
			{
				m_lpControl->struInsertInfo.dwCount = m_dwPlayCount;
			}
            else if (0 == strcmp(m_lpControl->struInsertInfo.szPlayMode, "byEndTime"))
            {
                CString strTime;
                strTime.Format("%04d%02d%02dT%02d:%02d:%02d+08", m_dateTime.GetYear(), m_dateTime.GetMonth(),
                    m_dateTime.GetDay(), m_timeTime.GetHour(), m_timeTime.GetMinute(), m_timeTime.GetSecond());
                memcpy(m_lpControl->struInsertInfo.szEndTime, strTime.GetBuffer(0), strTime.GetLength());
            }
			m_lpControl->struInsertInfo.dwPositionX = m_dwPositionX;
			m_lpControl->struInsertInfo.dwPositionY = m_dwPositionY;
			m_lpControl->struInsertInfo.dwPositionWidth = m_dwPositionWidth;
			m_lpControl->struInsertInfo.dwPostionHeight = m_dwPositionHeight;

			m_lpControl->struInsertInfo.struChacEff.dwFontSize = m_dwFontSize;
			m_lpControl->struInsertInfo.struChacEff.struFontColor.dwRed = m_dwFontRed;
			m_lpControl->struInsertInfo.struChacEff.struFontColor.dwGreen = m_dwFontGreen;
			m_lpControl->struInsertInfo.struChacEff.struFontColor.dwBlue = m_dwFontBlue;
			m_lpControl->struInsertInfo.struChacEff.struBackColor.dwRed = m_dwBackRed;
			m_lpControl->struInsertInfo.struChacEff.struBackColor.dwGreen = m_dwBackGreen;
			m_lpControl->struInsertInfo.struChacEff.struBackColor.dwBlue = m_dwBackBlue;
			m_lpControl->struInsertInfo.struChacEff.dwBackTransparent = m_dwTransparent;
			nSel = m_cmbFontDirect.GetCurSel();
			if (nSel == CB_ERR)
			{
				char szLan1[512] = {0};
				char szLan2[512] = {0};
				g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
				g_StringLanType(szLan2, "播放控制", "Play Control");
				//MessageBox(szLan1, szLan2, MB_ICONWARNING);
				//return;
			}
			m_cmbFontDirect.GetLBText(nSel, m_lpControl->struInsertInfo.struChacEff.szScrollDirection);
			m_lpControl->struInsertInfo.struChacEff.bySubtitlesEnabled = m_bFontEnable;
			m_lpControl->struInsertInfo.struChacEff.dwScrollSpeed = m_dwFontSpeed;
		}
		else if (0 == strcmp(m_lpControl->struInsertInfo.szInsertType, "program"))
		{
            struCond.dwInsertNo = m_dwProgramID;
            struCond.byInsertType = 2;
			m_lpControl->struInsertInfo.dwProgramID = m_dwProgramID;
			nSel = m_cmbPlayMode.GetCurSel();
			if (nSel == CB_ERR)
			{
				char szLan1[512] = {0};
				char szLan2[512] = {0};
				g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
				g_StringLanType(szLan2, "播放控制", "Play Control");
				//MessageBox(szLan1, szLan2, MB_ICONWARNING);
				//return;
			}
			m_cmbPlayMode.GetLBText(nSel, m_lpControl->struInsertInfo.szPlayMode);
			if (0 == strcmp(m_lpControl->struInsertInfo.szPlayMode, "byTime"))
			{
				m_lpControl->struInsertInfo.dwDuration = m_dwProgramDuration;
			}
			else if (0 == strcmp(m_lpControl->struInsertInfo.szPlayMode, "byCount"))
			{
				m_lpControl->struInsertInfo.dwCount = m_dwPlayCount;
			}
			m_lpControl->struInsertInfo.dwPositionX = m_dwPositionX;
			m_lpControl->struInsertInfo.dwPositionY = m_dwPositionY;
			m_lpControl->struInsertInfo.dwPositionWidth = m_dwPositionWidth;
			m_lpControl->struInsertInfo.dwPostionHeight = m_dwPositionHeight;
		}

        struCond.dwSize = sizeof(struCond);
        if (0 == strcmp(m_csCtrlType, "terminalGroups"))
        {
            struCond.byProgressType = 1;
            struCond.dwGroupNo = m_lpControl->dwTerminalGroupList[0];
        }
        else if (0 == strcmp(m_csCtrlType, "terminals"))
        {
            struCond.byProgressType = 2;
            struCond.dwTerminalNo = m_lpControl->dwTerminalList[0];
        }
	


	}
    else if(0 == strcmp(m_lpControl->szControlType, "planCtrl"))
    {
        m_lpControl->struPlanCtrl.byEnable = m_bPlanEnable;
        nSel = m_cmbPlanType.GetCurSel();
        if (nSel == CB_ERR)
        {
            char szLan1[512] = {0};
            char szLan2[512] = {0};
            g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
            g_StringLanType(szLan2, "计划控制", "Plan Control");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
    	m_cmbPlanType.GetLBText(nSel,m_lpControl->struPlanCtrl.szPlanType);
    }
	
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertPlayControlParamsStruToXml(m_lpControl, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/TerminalMgr/terminals/control\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
    struInputParam.dwRecvTimeOut = 10000;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	delete[] pInputBuff;
	pInputBuff = NULL;
    if (0 == strcmp(m_lpControl->szControlType, "insert"))
    {
        m_lConfigHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_INSERTPLAY_PROGRESS, &struCond, sizeof(struCond), ProcessInsertPlayProgress, this);
        if (m_lConfigHandle < 0)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_INSERTPLAY_PROGRESS");
            return;
        }
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_INSERTPLAY_PROGRESS");

        ShowReleaseProgress(0, "");
    }
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionPlay::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelTerminal < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择终端/终端组", "Please choose a terminal/group first.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	int nSel = m_cmbTargetType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strTargetType;
	m_cmbTargetType.GetLBText(nSel, strTargetType);
	if (0 == strcmp(strTargetType, "terminals"))
	{
		for (int nTerCnt = m_nCurSelTerminal; nTerCnt < m_listTerminal.GetItemCount()-1; nTerCnt++)
		{
			m_listTerminal.SetItemText(nTerCnt, 1, m_listTerminal.GetItemText(nTerCnt+1, 1));
			m_lpControl->dwTerminalList[nTerCnt] = m_lpControl->dwTerminalList[nTerCnt+1];
		}
		m_lpControl->dwTerminalList[m_listTerminal.GetItemCount()-1] = 0;
		m_lpControl->dwTerminalCount--; //数量-1;
	}
	else if (0 == strcmp(strTargetType, "terminalGroups"))
	{
		for (int nGrpCnt = m_nCurSelTerminal; nGrpCnt < m_listTerminal.GetItemCount()-1; nGrpCnt++)
		{
			m_listTerminal.SetItemText(nGrpCnt, 1, m_listTerminal.GetItemText(nGrpCnt+1, 1));
			m_lpControl->dwTerminalGroupList[nGrpCnt] = m_lpControl->dwTerminalGroupList[nGrpCnt+1];
		}
		m_lpControl->dwTerminalGroupList[m_listTerminal.GetItemCount()-1] = 0;
		m_lpControl->dwGroupCount--; //数量-1;
	}
	m_listTerminal.DeleteItem(m_listTerminal.GetItemCount()-1);
	m_nCurSelTerminal = -1;
}

void CDlgInfoDiffusionPlay::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionPlay::OnBtnMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_nCurSelTerminal < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择终端/终端组", "Please choose a terminal/group first.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	int nSel = m_cmbTargetType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strTargetType;
	m_cmbTargetType.GetLBText(nSel, strTargetType);
	if (0 == strcmp(strTargetType, "byTerminal"))
	{
		m_lpControl->dwTerminalList[m_nCurSelTerminal] = m_dwTerminalID;
	}
	else if (0 == strcmp(strTargetType, "byGroup"))
	{
		m_lpControl->dwTerminalGroupList[m_nCurSelTerminal] = m_dwTerminalID;
	}
	CString str;
	str.Format("%d", m_dwTerminalID);
	m_listTerminal.SetItemText(m_nCurSelTerminal, 1, str);
}

void CDlgInfoDiffusionPlay::OnBtnPrtscn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/TerminalMgr/screenShot/%d\r\n", m_dwPrtScnID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	m_pImageBuffer = new char[IMAGE_BUFFER];
	memset(m_pImageBuffer, 0, sizeof(char)*IMAGE_BUFFER);

	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pImageBuffer, 0, IMAGE_BUFFER);
	struOutputParam.lpOutBuffer = m_pImageBuffer;
	struOutputParam.dwOutBufferSize = IMAGE_BUFFER;
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] m_pImageBuffer;
		m_pImageBuffer = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	CString strImageFilePath;
	strImageFilePath.Format("C:\\Picture");
	if (!PathFileExists(strImageFilePath))
	{
		if (!CreateDirectory(strImageFilePath, NULL))
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "创建目录失败", "Create directory failed.");
			g_StringLanType(szLan2, "播放控制", "Play Control");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			delete[] m_pImageBuffer;
		    m_pImageBuffer = NULL;
			return;
		}
	}
    CTime time(time(NULL));
	strImageFilePath.Format("C:\\Picture\\%d%02d%02d%02d%02d%02d.jpg",
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	CFile file;
	if (!file.Open(strImageFilePath, CFile::modeCreate|CFile::modeWrite))
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "创建文件失败", "Create file failed.");
		g_StringLanType(szLan2, "播放控制", "Play Control");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		delete[] m_pImageBuffer;
		m_pImageBuffer = NULL;
		return;
	}
	file.Write(m_pImageBuffer, struOutputParam.dwOutBufferSize);
	file.Close();
}

void CDlgInfoDiffusionPlay::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_lpControl;
	m_lpControl = NULL;
	delete[] m_pOutputXmlBuffer;
	m_pOutputXmlBuffer = NULL;
}

void CDlgInfoDiffusionPlay::OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
		int nSel = m_cmbTargetType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "播放控制", "Play Control");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		CString strTargetType;
		m_cmbTargetType.GetLBText(nSel, strTargetType);
		if (0 == strcmp(strTargetType, "terminals"))
		{
			m_dwTerminalID = m_lpControl->dwTerminalList[m_nCurSelTerminal];
		}
		else if (0 == strcmp(strTargetType, "terminalGroups"))
		{
			m_dwTerminalID = m_lpControl->dwTerminalGroupList[m_nCurSelTerminal];
		}
		
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgInfoDiffusionPlay::OnSelchangeComboPlayMode() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbPlayMode.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strMode;
	m_cmbPlayMode.GetLBText(nSel, strMode);
	if (0 == strcmp(strMode, "byTime"))
	{
		GetDlgItem(IDC_EDIT_PROGRAM_DURATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PLAY_COUNT)->EnableWindow(FALSE);
	}
	else if (0 == strcmp(strMode, "byCount"))
	{
		GetDlgItem(IDC_EDIT_PROGRAM_DURATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PLAY_COUNT)->EnableWindow(TRUE);
	}
}

void CDlgInfoDiffusionPlay::ShowReleaseProgress(DWORD dwProgress, CString strTips)
{
    m_progressInsertPlay.SetPos(dwProgress);
    GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(strTips);
}

DWORD CDlgInfoDiffusionPlay::GetRemoteConfigState()
{
    DWORD dwState = 0;
    if (!NET_DVR_GetRemoteConfigState(m_lConfigHandle, &dwState))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetRemoteConfigState");
    }
    return dwState;
}

LRESULT CDlgInfoDiffusionPlay::OnStopRemoteConfig(WPARAM wParam, LPARAM lParam)
{
    StopRemoteConfig();
    return 0;
}

void CDlgInfoDiffusionPlay::StopRemoteConfig()
{
    Sleep(100);
    if (m_lConfigHandle >= 0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lConfigHandle))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig");
            m_lConfigHandle = -1;
        }
    }
}
