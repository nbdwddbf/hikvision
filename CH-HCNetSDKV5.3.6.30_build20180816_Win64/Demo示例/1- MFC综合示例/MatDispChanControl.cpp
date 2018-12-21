// MatDispChanControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatDispChanControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatDispChanControl dialog

CMatDispChanControl::CMatDispChanControl(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDispChanControl::IDD, pParent)
	,m_iDeviceIndex(-1)
	,m_lServerID(-1)
{
	//{{AFX_DATA_INIT(CMatDispChanControl)
	m_bySubWindowIndex = 0;
	//}}AFX_DATA_INIT
    for(int i = 0; i < 16; i ++)
    {
        memset(&m_DispChanCfg[i], 0, sizeof(NET_DVR_VGA_DISP_CHAN_CFG));
    }    
}


void CMatDispChanControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDispChanControl)
	DDX_Control(pDX, IDC_COMBOBNCSCALE, m_BNCScaleCtrl);
	DDX_Control(pDX, IDC_COMBOVEDIOFORMAT, m_VedioFormatCtrl);
	DDX_Control(pDX, IDC_COMBOAUDIOSUBWNW, m_comboAudioWindow);
	DDX_Control(pDX, IDC_COMBOSUBWINDOWDECCHAN, m_ComboSubWindowDecChan);
	DDX_Control(pDX, IDC_COMBOSUBWINDOWNUM, m_ComboSubWindowNum);
	DDX_Control(pDX, IDC_COMBODISPCHAN, m_ComboDispChan);
	DDX_Control(pDX, IDC_COMBOOPENAUDIO, m_ComboOpenAudio);
	DDX_Control(pDX, IDC_COMBOPICMODE, m_ComboPicMode);
	DDX_Control(pDX, IDC_COMBOVGARESOLURION, m_ComboVgaResolution);
	DDX_Text(pDX, IDC_EDIT_SUBWINDOWINDEX, m_bySubWindowIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatDispChanControl, CDialog)
	//{{AFX_MSG_MAP(CMatDispChanControl)
	ON_CBN_SELCHANGE(IDC_COMBODISPCHAN, OnSelchangeCombodispchan)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_RENEWWINDOW, OnRenewwindow)
	ON_BN_CLICKED(IDC_ENLARGEWINDOW, OnEnlargewindow)
	ON_BN_CLICKED(IDC_DISPCHANCFG, OnDispchancfg)
	ON_CBN_SELCHANGE(IDC_COMBOSUBWINDOWNUM, OnSelchangeCombosubwindownum)
	ON_BN_CLICKED(IDC_SURE, OnSure)
	ON_BN_CLICKED(IDC_SUBSURE, OnSubsure)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatDispChanControl message handlers

BOOL CMatDispChanControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    CString tmp;
    memset(&m_Ability, 0, sizeof(NET_DVR_MATRIX_ABILITY_V41));
    if (!NET_DVR_GetDeviceAbility(m_lServerID, MATRIXDECODER_ABILITY_V41, NULL, 0, (char*)&m_Ability, sizeof(NET_DVR_MATRIX_ABILITY_V41)))
    {
        tmp.Format("Error code : %d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
        return FALSE;
    }

    int i = 0;
    int ChanNo = -1;
    char szLan[128] = {0};

	m_iVGAResolutionNum = 0;
	m_iHDMIResolutionNum = 0;
	m_iDVIResolutionNum = 0;
	for (i = 0; i < MAX_SUPPORT_RES; i ++)
	{
		if (m_Ability.struVgaInfo.dwSupportResolution[i] != 0)
		{
			m_iVGAResolutionNum ++;
		}
	}
	
	for (i = 0; i < MAX_SUPPORT_RES; i ++)
	{
		if (m_Ability.struHdmiInfo.dwSupportResolution[i] != 0)
		{
			m_iHDMIResolutionNum ++;
		}
	}

	for (i = 0; i < MAX_SUPPORT_RES; i ++)
	{
		if (m_Ability.struDviInfo.dwSupportResolution[i] != 0)
		{
			m_iDVIResolutionNum ++;
		}
	}

    for(i = 0; i < m_Ability.struBncInfo.byChanNums; i++)
    {
        //ChanNo = m_Ability.struBncInfo.byStartChan + i;
        ChanNo = i + 1;
		g_StringLanType(szLan, "BNC", "BNC");
        tmp.Format("%s %d", szLan, ChanNo);
        m_ComboDispChan.AddString(tmp);
    }

	for(i = 0; i < m_Ability.struVgaInfo.byChanNums; i++)
    {
        //ChanNo = m_Ability.struVgaInfo.byStartChan + i;
        ChanNo = i + 1;
		g_StringLanType(szLan, "VGA", "VGA");
        tmp.Format("%s %d", szLan, ChanNo);
        m_ComboDispChan.AddString(tmp);
    }

	for(i = 0; i < m_Ability.struHdmiInfo.byChanNums; i++)
    {
        //ChanNo = m_Ability.struHdmiInfo.byStartChan + i;
        ChanNo = i + 1;
		g_StringLanType(szLan, "HDMI", "HDMI");
        tmp.Format("%s %d", szLan, ChanNo);
        m_ComboDispChan.AddString(tmp);
    }

	for(i = 0; i < m_Ability.struDviInfo.byChanNums; i++)
    {
        //ChanNo = m_Ability.struDviInfo.byStartChan + i;
        ChanNo = i + 1;
		g_StringLanType(szLan, "DVI", "DVI");
        tmp.Format("%s %d", szLan, ChanNo);
        m_ComboDispChan.AddString(tmp);
    }

    for(i = 0; i < m_Ability.byDecChanNums; i++)
    {
        ChanNo = m_Ability.byStartChan + i;
        g_StringLanType(szLan, "通道", "Chan");
        tmp.Format("%s %d", szLan, ChanNo);
        m_ComboSubWindowDecChan.InsertString(i, tmp);
    }
    
	int iDispNums = 0;
    for(i = 0; i < m_Ability.struBncInfo.byChanNums; i++)
    {
        if (!NET_DVR_MatrixGetDisplayCfg_V41(m_lServerID, m_Ability.struBncInfo.byStartChan + i, &m_DispChanCfg[iDispNums + i]))
        {
            TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", m_Ability.struBncInfo.byStartChan + i, NET_DVR_GetLastError());
        }
    }  

	iDispNums += m_Ability.struBncInfo.byChanNums;

//  	NET_DVR_VGA_DISP_CHAN_CFG_V40 struTest = {0};
//  	int iRet = NET_DVR_MatrixGetDisplayCfg_V40(m_lServerID,29,&struTest);
    for(i = 0; i < m_Ability.struVgaInfo.byChanNums; i++)
    {
        if (!NET_DVR_MatrixGetDisplayCfg_V41(m_lServerID, i + m_Ability.struVgaInfo.byStartChan, &m_DispChanCfg[iDispNums + i]))
        {
            TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", i, NET_DVR_GetLastError());
        }
    } 

	iDispNums += m_Ability.struVgaInfo.byChanNums;
	for(i = 0; i < m_Ability.struHdmiInfo.byChanNums; i++)
    {
        if (!NET_DVR_MatrixGetDisplayCfg_V41(m_lServerID, m_Ability.struHdmiInfo.byStartChan + i, &m_DispChanCfg[iDispNums + i]))
        {
            TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", m_Ability.struHdmiInfo.byStartChan + i, NET_DVR_GetLastError());
        }
    }
	
	iDispNums += m_Ability.struHdmiInfo.byChanNums;
    for(i = 0; i < m_Ability.struDviInfo.byChanNums; i++)
    {
        if (!NET_DVR_MatrixGetDisplayCfg_V41(m_lServerID, m_Ability.struDviInfo.byStartChan + i, &m_DispChanCfg[iDispNums + i]))
        {
            TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", m_Ability.struDviInfo.byStartChan + i, NET_DVR_GetLastError());
        }
    }   

	//放大子窗口号使能
	GetDlgItem(IDC_EDIT_SUBWINDOWINDEX)->EnableWindow(FALSE);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
    
void CMatDispChanControl::OnSelchangeCombodispchan() 
{
	UpdateData(TRUE);
	char temp[20] = {0};
    int i = 0;
	int iIndex = 0;
    CString sTemp;
    m_ComboPicMode.ResetContent();
    int iMaxWindows = 0;
	char sResStr[64] = {0};
	DWORD dwDispChanIndex = m_ComboDispChan.GetCurSel();
	m_ComboVgaResolution.ResetContent();
	int  iKeep = 0;

	if (dwDispChanIndex < m_Ability.struBncInfo.byChanNums)
	{
        GetDlgItem(IDC_COMBOVGARESOLURION)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBOBNCSCALE)->EnableWindow(TRUE);
		DWORD dwSeq = m_ComboDispChan.GetCurSel();
		//画面模式
		for (i = 0;i < MAX_DISPNUM_V41;i++)
		{
			if (m_Ability.struDispMode[i].byDispChanType != 0)
			{
				continue;
			}
			break;
		}
		iKeep = i + dwDispChanIndex;
		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{						
			if (m_Ability.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sTemp.Format("%d", m_Ability.struDispMode[iKeep].byDispMode[i]);
				m_ComboPicMode.AddString(sTemp);
			}
		}
		//分辨率
		for (i=0; i<MAX_SUPPORT_RES; i++)
		{
			memset(sResStr, 0, sizeof(sResStr));
			GetResolutionString(m_Ability.struBncInfo.dwSupportResolution[i], sResStr);
			sTemp.Format("%s", sResStr);
			if (m_ComboVgaResolution.FindStringExact(0, sResStr) == CB_ERR)
			{
				m_ComboVgaResolution.AddString(sTemp);
				iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
				m_ComboVgaResolution.SetItemData(iIndex, m_Ability.struBncInfo.dwSupportResolution[i]);
			}
		}
		DWORD dwDispChanRes = m_DispChanCfg[dwDispChanIndex].dwResolution;
		memset(sResStr, 0, sizeof(sResStr));
		GetResolutionString(dwDispChanRes, sResStr);
		sTemp.Format("%s", sResStr);
		iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
		if (iIndex != CB_ERR)
		{
			m_ComboVgaResolution.SetCurSel(iIndex);
		}
    }
    else if((dwDispChanIndex >= m_Ability.struBncInfo.byChanNums) && (dwDispChanIndex < m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums))
    {
		GetDlgItem(IDC_COMBOVGARESOLURION)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBOBNCSCALE)->EnableWindow(FALSE);

		DWORD dwSeq = m_ComboDispChan.GetCurSel() - m_Ability.struBncInfo.byChanNums;
		DWORD dwDispChanIndex = m_ComboDispChan.GetCurSel();
		for (i = 0;i < MAX_DISPNUM_V41;i++)
		{
			if (m_Ability.struDispMode[i].byDispChanType != 1)
			{
				continue;
			}
			break;
		}
		iKeep = i + dwSeq;
		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{			
			if (m_Ability.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sTemp.Format("%d", m_Ability.struDispMode[iKeep].byDispMode[i]);
				m_ComboPicMode.AddString(sTemp);
			}
		}

		for (i=0; i<MAX_SUPPORT_RES; i++)
		{
			//if(m_Ability.struVgaInfo.dwSupportResolution[i] != 0)
			memset(sResStr, 0, sizeof(sResStr));
			GetResolutionString(m_Ability.struVgaInfo.dwSupportResolution[i], sResStr);
			sTemp.Format("%s", sResStr);
			if (m_ComboVgaResolution.FindStringExact(0, sResStr) == CB_ERR)
			{
				m_ComboVgaResolution.AddString(sTemp);
				iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
				m_ComboVgaResolution.SetItemData(iIndex, m_Ability.struVgaInfo.dwSupportResolution[i]);
			}
		}
		DWORD dwDispChanRes = m_DispChanCfg[dwDispChanIndex].dwResolution;
		memset(sResStr, 0, sizeof(sResStr));
		GetResolutionString(dwDispChanRes, sResStr);
		sTemp.Format("%s", sResStr);
		iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
		if (iIndex != CB_ERR)
		{
			m_ComboVgaResolution.SetCurSel(iIndex);
		}
    }
	else if ((dwDispChanIndex >= (m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums)) && \
		(dwDispChanIndex < m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums))
    {
		GetDlgItem(IDC_COMBOVGARESOLURION)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBOBNCSCALE)->EnableWindow(FALSE);
		DWORD dwSeq = m_ComboDispChan.GetCurSel() - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums;
		for (i = 0;i < MAX_DISPNUM_V41;i++)
		{
			if (m_Ability.struDispMode[i].byDispChanType != 2)
			{
				continue;
			}
			break;
		}
		iKeep = i + dwSeq;

		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{			
			if (m_Ability.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sTemp.Format("%d", m_Ability.struDispMode[iKeep].byDispMode[i]);
				m_ComboPicMode.AddString(sTemp);
			}
		}

		for (i=0; i<MAX_SUPPORT_RES; i++)
		{
			memset(sResStr, 0, sizeof(sResStr));
			GetResolutionString(m_Ability.struHdmiInfo.dwSupportResolution[i], sResStr);
			sTemp.Format("%s", sResStr);
			if (m_ComboVgaResolution.FindStringExact(0, sResStr) == CB_ERR)
			{
				m_ComboVgaResolution.AddString(sTemp);
				iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
				m_ComboVgaResolution.SetItemData(iIndex, m_Ability.struHdmiInfo.dwSupportResolution[i]);
			}
		}
		DWORD dwDispChanRes = m_DispChanCfg[dwDispChanIndex].dwResolution;
		memset(sResStr, 0, sizeof(sResStr));
		GetResolutionString(dwDispChanRes, sResStr);
		sTemp.Format("%s", sResStr);
		iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
		if (iIndex != CB_ERR)
		{
			m_ComboVgaResolution.SetCurSel(iIndex);
		}
    }
	else if ((dwDispChanIndex >= m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums) && \
		(m_ComboDispChan.GetCurSel() < m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums + m_Ability.struDviInfo.byChanNums))
    {
		GetDlgItem(IDC_COMBOVGARESOLURION)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBOBNCSCALE)->EnableWindow(FALSE);
		DWORD dwSeq = m_ComboDispChan.GetCurSel() - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums - m_Ability.struHdmiInfo.byChanNums;
		for (i = 0;i < MAX_DISPNUM_V41;i++)
		{
			if (m_Ability.struDispMode[i].byDispChanType != 3)
			{
				continue;
			}
			break;
		}
		iKeep = i + dwSeq;

		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{			
			if (m_Ability.struDispMode[dwDispChanIndex].byDispMode[i] != 0)
			{
				sTemp.Format("%d", m_Ability.struDispMode[dwDispChanIndex].byDispMode[i]);
				m_ComboPicMode.AddString(sTemp);
			}
		}

		for (i=0; i<MAX_SUPPORT_RES; i++)
		{
			memset(sResStr, 0, sizeof(sResStr));
			GetResolutionString(m_Ability.struDviInfo.dwSupportResolution[i], sResStr);
			sTemp.Format("%s", sResStr);
			if (m_ComboVgaResolution.FindStringExact(0, sResStr) == CB_ERR)
			{
				m_ComboVgaResolution.AddString(sTemp);
				iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
				m_ComboVgaResolution.SetItemData(iIndex, m_Ability.struDviInfo.dwSupportResolution[i]);
			}
		}
		DWORD dwDispChanRes = m_DispChanCfg[dwDispChanIndex].dwResolution;
		memset(sResStr, 0, sizeof(sResStr));
		GetResolutionString(dwDispChanRes, sResStr);
		sTemp.Format("%s", sResStr);
		iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
		if (iIndex != CB_ERR)
		{
			m_ComboVgaResolution.SetCurSel(iIndex);
		}
    }

	m_ComboSubWindowNum.ResetContent();
    m_comboAudioWindow.ResetContent();

    for (i = 0; i < MAX_WINDOWS_NUM; i++)
    {
        if (m_Ability.struDispMode[dwDispChanIndex].byDispMode[i] > iMaxWindows)
        {
            iMaxWindows = m_Ability.struDispMode[dwDispChanIndex].byDispMode[i];
        }
    }
    for(i = 1; i <= iMaxWindows; i++)
    {
        sTemp.Format("%d", i);
        m_ComboSubWindowNum.InsertString(i - 1, sTemp);
        m_comboAudioWindow.InsertString(i - 1, sTemp);
    }

	//音频是否开启
    m_ComboOpenAudio.SetCurSel(m_DispChanCfg[dwDispChanIndex].byAudio);
	//显示画面模式
	sTemp.Format("%d", m_DispChanCfg[dwDispChanIndex].dwWindowMode);

	iIndex = m_ComboPicMode.FindStringExact(0, sTemp);
	if (iIndex != CB_ERR)
	{
		m_ComboPicMode.SetCurSel(iIndex);
	}
	//视频制式
    m_VedioFormatCtrl.SetCurSel(m_DispChanCfg[dwDispChanIndex].byVedioFormat - 1);
	//分辨率
	memset(sResStr, 0, sizeof(sResStr));
	GetResolutionString(m_DispChanCfg[dwDispChanIndex].dwResolution, sResStr);
	sTemp.Format("%s", sResStr);
	iIndex = m_ComboVgaResolution.FindStringExact(0, sTemp);
	if (iIndex != CB_ERR)
	{
		m_ComboVgaResolution.SetCurSel(iIndex);
	}
	//音频开始子窗口
    m_comboAudioWindow.SetCurSel(m_DispChanCfg[dwDispChanIndex].byAudioWindowIdx - 1);
    //子窗口关键解码通道
	int subsel = m_ComboSubWindowNum.GetCurSel();
    m_ComboSubWindowDecChan.SetCurSel(m_DispChanCfg[dwDispChanIndex].byJoinDecChan[subsel] - m_Ability.byStartChan);
    
	m_BNCScaleCtrl.SetCurSel(m_DispChanCfg[dwDispChanIndex].byScale);

	//放大子窗口
	if (m_DispChanCfg[dwDispChanIndex].byEnlargeStatus == 1)
	{
		GetDlgItem(IDC_EDIT_SUBWINDOWINDEX)->EnableWindow(TRUE);
		m_bySubWindowIndex = m_DispChanCfg[dwDispChanIndex].byEnlargeSubWindowIndex;
	}
	else
	{
		m_bySubWindowIndex = 0;
		GetDlgItem(IDC_EDIT_SUBWINDOWINDEX)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CMatDispChanControl::OnExit() 
{
    CDialog::OnCancel();
}

void CMatDispChanControl::OnRenewwindow() 
{
    UpdateData(TRUE);
    int sel = m_ComboDispChan.GetCurSel();
	int iChanIndex = 0;
    if(sel < m_Ability.struBncInfo.byChanNums)
    {
		iChanIndex = sel + m_Ability.struBncInfo.byStartChan;
        //if (!NET_DVR_MatrixDiaplayControl(m_lServerID, sel + m_Ability.byStartChan, DISP_CMD_RENEW_WINDOW , m_ComboSubWindowNum.GetCurSel() + m_Ability.byStartChan))
        if(!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_RENEW_WINDOW , m_ComboSubWindowNum.GetCurSel()))
		{
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
        }
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "RENEW_WINDOW SUCC");
		}
    }
    else if ((sel >= m_Ability.struBncInfo.byChanNums) && (sel < m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byStartChan;
		if (!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_RENEW_WINDOW , m_ComboSubWindowNum.GetCurSel()))
        {
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
        }
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "RENEW_WINDOW SUCC");
		}
    }
    else if ((sel >= m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums) && (sel < m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byStartChan;
		if (!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_RENEW_WINDOW , m_ComboSubWindowNum.GetCurSel()))
        {
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
        }
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "RENEW_WINDOW SUCC");
		}
    }
	else if ((sel >= m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums) && \
		(sel < m_Ability.struDviInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums - m_Ability.struHdmiInfo.byChanNums + m_Ability.struDviInfo.byStartChan;
		if (!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_RENEW_WINDOW , m_ComboSubWindowNum.GetCurSel()))
        {
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
        }
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "RENEW_WINDOW SUCC");
		}
    }
}

void CMatDispChanControl::OnEnlargewindow() 
{
	UpdateData(TRUE);
    int sel = m_ComboDispChan.GetCurSel();
	int iChanIndex = 0;
    if(sel < m_Ability.struBncInfo.byChanNums)
    {
		iChanIndex = sel + m_Ability.struBncInfo.byStartChan;
        if (!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_ENLARGE_WINDOW , m_ComboSubWindowNum.GetCurSel() + 1))
        {
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ENLARGE_WINDOW FAILED");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ENLARGE_WINDOW SUCC");
		}
    }
    else if ((sel >= m_Ability.struBncInfo.byChanNums) && (sel < m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byStartChan;
		if (!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_ENLARGE_WINDOW , m_ComboSubWindowNum.GetCurSel() + 1))
        {
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ENLARGE_WINDOW FAILED");
        }	
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ENLARGE_WINDOW SUCC");
		}
    }
    else if ((sel >= m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums) && (sel < m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byStartChan;
		if (!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_ENLARGE_WINDOW , m_ComboSubWindowNum.GetCurSel() + 1))
        {
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ENLARGE_WINDOW FAILED");
        }
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ENLARGE_WINDOW SUCC");
		}
    }
	else if ((sel >= m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums) && \
		(sel < m_Ability.struDviInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums - m_Ability.struHdmiInfo.byChanNums + m_Ability.struDviInfo.byStartChan;
		if (!NET_DVR_MatrixDiaplayControl(m_lServerID, iChanIndex, DISP_CMD_ENLARGE_WINDOW , m_ComboSubWindowNum.GetCurSel() + 1))
        {
            CString sTemp;
            sTemp.Format("ERROR: NET_DVR_MatrixDiaplayControl = %d \n", NET_DVR_GetLastError());
            AfxMessageBox(sTemp);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ENLARGE_WINDOW FAILED");
        }
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ENLARGE_WINDOW SUCC");
		}
    }
}

void CMatDispChanControl::OnDispchancfg() 
{
	UpdateData(TRUE);
	CString str;
    int sel = m_ComboDispChan.GetCurSel();
	int iChanIndex;
    if(sel < m_Ability.struBncInfo.byChanNums)
    {
		iChanIndex = sel + m_Ability.struBncInfo.byStartChan;
        TRACE("sel = %d, m_DispChanCfg[sel].byJoinDecChan[0] = %d", sel, m_DispChanCfg[sel].byJoinDecChan[0]);
		if (!NET_DVR_MatrixSetDisplayCfg_V41(m_lServerID, iChanIndex, &m_DispChanCfg[sel])) 
        {
            str.Format("Error code : %d", NET_DVR_GetLastError());
            AfxMessageBox(str);			
            return;
        }
    }
    else if ((sel >= m_Ability.struBncInfo.byChanNums) && (sel < m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byStartChan;
        TRACE("sel = %d, m_DispChanCfg[sel].byJoinDecChan[0] = %d", sel, m_DispChanCfg[sel].byJoinDecChan[0]);
        if (!NET_DVR_MatrixSetDisplayCfg_V41(m_lServerID, iChanIndex, &m_DispChanCfg[sel])) 
        {
            str.Format("Error code : %d", NET_DVR_GetLastError());
            AfxMessageBox(str);
            return;
        }
    }
    else if ((sel >= m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums) && (sel < m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byStartChan;
		TRACE("sel = %d, m_DispChanCfg[sel].byJoinDecChan[0] = %d", sel, m_DispChanCfg[sel].byJoinDecChan[0]);
        if (!NET_DVR_MatrixSetDisplayCfg_V41(m_lServerID, iChanIndex, &m_DispChanCfg[sel])) 
        {
            str.Format("Error code : %d", NET_DVR_GetLastError());
            AfxMessageBox(str);
            return;
        }
    }
	else if ((sel >= m_Ability.struVgaInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums) && \
		(sel < m_Ability.struDviInfo.byChanNums + m_Ability.struHdmiInfo.byChanNums + m_Ability.struBncInfo.byChanNums + m_Ability.struVgaInfo.byChanNums))
    {
		iChanIndex = sel - m_Ability.struVgaInfo.byChanNums - m_Ability.struBncInfo.byChanNums - m_Ability.struHdmiInfo.byChanNums + m_Ability.struDviInfo.byStartChan;
		TRACE("sel = %d, m_DispChanCfg[sel].byJoinDecChan[0] = %d", sel, m_DispChanCfg[sel].byJoinDecChan[0]);
        if (!NET_DVR_MatrixSetDisplayCfg_V41(m_lServerID, iChanIndex, &m_DispChanCfg[sel])) 
        {
            str.Format("Error code : %d", NET_DVR_GetLastError());
            AfxMessageBox(str);
            return;
        }	
    }

    AfxMessageBox("Set Success");
}

void CMatDispChanControl::OnSelchangeCombosubwindownum() 
{
	UpdateData(TRUE);
	int sel = m_ComboDispChan.GetCurSel();
	int subSel = m_ComboSubWindowNum.GetCurSel();
   // m_ComboSubWindowDecChan.SetCurSel(m_DispChanCfg[sel].byJoinDecChan[m_ComboSubWindowNum.GetCurSel()] - m_Ability.byStartChan);
    m_ComboSubWindowDecChan.SetCurSel(m_DispChanCfg[sel].byJoinDecChan[subSel] - m_Ability.byStartChan);
	UpdateData(FALSE);
}

void CMatDispChanControl::OnSure() 
{
	UpdateData(TRUE);
	int sel = m_ComboDispChan.GetCurSel();
	int iResSel = m_ComboVgaResolution.GetCurSel();
	m_DispChanCfg[sel].dwResolution = m_ComboVgaResolution.GetItemData(iResSel);
	/*if (iResSel < m_iVGAResolutionNum)
	{
		m_DispChanCfg[sel].dwResolution = m_Ability.struVgaInfo.dwSupportResolution[iResSel];
	}
	else if (iResSel >= m_iVGAResolutionNum && iResSel<(m_iHDMIResolutionNum + m_iVGAResolutionNum))
	{
		iResSel -= m_iVGAResolutionNum; 
		m_DispChanCfg[sel].dwResolution = m_Ability.struHdmiInfo.dwSupportResolution[iResSel];
	}
	else if (iResSel >= m_iVGAResolutionNum+m_iHDMIResolutionNum && (iResSel<m_iHDMIResolutionNum + m_iVGAResolutionNum + m_iDVIResolutionNum))
	{
		iResSel = iResSel - m_iVGAResolutionNum - m_iHDMIResolutionNum;
		m_DispChanCfg[sel].dwResolution = m_Ability.struDviInfo.dwSupportResolution[iResSel];
	}

	m_ComboPicMode.GetLBText(m_ComboPicMode.GetCurSel(), temp);
	CString str;
	for (i = 1; i <= 16; i++)
	{
		str.Format("%d", i);
		if (strcmp(temp, str) == 0)
		{
			m_DispChanCfg[sel].dwWindowMode = i;
			break;
		}
	}*/
	m_DispChanCfg[sel].dwWindowMode = GetDlgItemInt(IDC_COMBOPICMODE);
	
	m_DispChanCfg[sel].byScale = m_BNCScaleCtrl.GetCurSel();
    if (m_DispChanCfg[sel].byScale == -1)
    {
        m_DispChanCfg[sel].byScale = 0;
    }

	m_DispChanCfg[sel].byAudio = m_ComboOpenAudio.GetCurSel();
    if (m_DispChanCfg[sel].byAudio == -1)
    {
        m_DispChanCfg[sel].byAudio = 0;
    }
    m_DispChanCfg[sel].byVedioFormat = m_VedioFormatCtrl.GetCurSel() + 1;
	
    m_DispChanCfg[sel].byAudioWindowIdx = m_comboAudioWindow.GetCurSel() + 1;
    int subWindowsel = m_ComboSubWindowNum.GetCurSel();
    
    m_DispChanCfg[sel].byJoinDecChan[subWindowsel] = m_ComboSubWindowDecChan.GetCurSel() + m_Ability.byStartChan;
    TRACE("sel = %d, subWindowsel = %d , m_DispChanCfg[sel].byJoinDecChan[subWindowsel] = %d", sel, subWindowsel, m_DispChanCfg[sel].byJoinDecChan[subWindowsel]);
}

void CMatDispChanControl::OnSubsure() 
{
	UpdateData(TRUE);
	int sel = m_ComboDispChan.GetCurSel();

    int subWindowsel = m_ComboSubWindowNum.GetCurSel();
    int i = m_ComboSubWindowDecChan.GetCurSel();
    m_DispChanCfg[sel].byJoinDecChan[subWindowsel] = m_ComboSubWindowDecChan.GetCurSel() + m_Ability.byStartChan;
    TRACE("sel = %d, subWindowsel = %d , m_DispChanCfg[sel].byJoinDecChan[subWindowsel] = %d", sel, subWindowsel, m_DispChanCfg[sel].byJoinDecChan[subWindowsel]);
}

void CMatDispChanControl::OnClear() 
{
	UpdateData(TRUE);
	int sel = m_ComboDispChan.GetCurSel();

	if (sel == CB_ERR)
	{
		return;
	}
    memset(&m_DispChanCfg[sel], 0, sizeof(NET_DVR_MATRIX_VOUTCFG));
}

void CMatDispChanControl::GetResolutionString(DWORD dwRes, char *lpResString)
{
	switch (dwRes)
	{
	case NOT_AVALIABLE:
		sprintf(lpResString, "%s", "NOT_AVALIABLE");
		break;
	case SVGA_60HZ:
		sprintf(lpResString, "%s", "SVGA_60HZ");
		break;
	case SVGA_75HZ:
		sprintf(lpResString, "%s", "SVGA_75HZ");
		break;	
	case XGA_60HZ:
		sprintf(lpResString, "%s", "XGA_60HZ");
		break;	
	case XGA_75HZ:
		sprintf(lpResString, "%s", "XGA_75HZ");
		break;	
	case SXGA_60HZ:
		sprintf(lpResString, "%s", "SXGA_60HZ");
		break;	
	case SXGA2_60HZ:
		sprintf(lpResString, "%s", "SXGA2_60HZ");
		break;	
	case _720P_60HZ:
		sprintf(lpResString, "%s", "_720P_60HZ");
		break;	
	case _720P_50HZ:
		sprintf(lpResString, "%s", "_720P_50HZ");
		break;	
	case _1080I_60HZ:
		sprintf(lpResString, "%s", "_1080I_60HZ");
		break;	
	case _1080I_50HZ:
		sprintf(lpResString, "%s", "_1080I_50HZ");
		break;	
	case _1080P_60HZ:
		sprintf(lpResString, "%s", "_1080P_60HZ");
		break;
	case _1080P_50HZ:
		sprintf(lpResString, "%s", "_1080P_50HZ");
		break;	
	case _1080P_30HZ:
		sprintf(lpResString, "%s", "_1080P_30HZ");
		break;	
	case _1080P_25HZ:
		sprintf(lpResString, "%s", "_1080P_25HZ");
		break;	
	case _1080P_24HZ:
		sprintf(lpResString, "%s", "_1080P_24HZ");
		break;	
	case UXGA_60HZ:
		sprintf(lpResString, "%s", "UXGA_60HZ");
		break;
	case UXGA_30HZ:
		sprintf(lpResString, "%s", "UXGA_30HZ");
		break;	
	case WSXGA_60HZ:
		sprintf(lpResString, "%s", "WSXGA_60HZ");
		break;	
	case WUXGA_60HZ:
		sprintf(lpResString, "%s", "WUXGA_60HZ");
		break;
	case WUXGA_30HZ:
		sprintf(lpResString, "%s", "WUXGA_30HZ");
		break;
	case WXGA_60HZ:
		sprintf(lpResString, "%s", "WXGA_60HZ");
		break;
	default:
		break;
	}
}
