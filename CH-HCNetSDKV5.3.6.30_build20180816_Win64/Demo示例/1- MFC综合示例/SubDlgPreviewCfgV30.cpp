// SubDlgPreviewCfgV30.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgPreviewCfgV30.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgPreviewCfgV30 dialog


CSubDlgPreviewCfgV30::CSubDlgPreviewCfgV30(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgPreviewCfgV30::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgPreviewCfgV30)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSubDlgPreviewCfgV30::~CSubDlgPreviewCfgV30()
{
}

void CSubDlgPreviewCfgV30::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgPreviewCfgV30)
	DDX_Control(pDX, IDC_PREVIEW_NUMBER, m_ctlPreviewNumber);
	DDX_Control(pDX, IDC_ENABLE_AUDIO, m_ctlEnableAudio);
	DDX_Control(pDX, IDC_SWITCH_TIME, m_ctlSwitchTime);
	DDX_Control(pDX, IDC_PREVIEW_MODE, m_ctlPreviewMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgPreviewCfgV30, CDialog)
	//{{AFX_MSG_MAP(CSubDlgPreviewCfgV30)
	ON_BN_CLICKED(IDC_BTN_SET_PREVIEWCFG, OnBtnSetPreviewcfg)
	ON_CBN_DROPDOWN(IDC_PREVIEW_MODE, OnDropdownPreviewMode)
	ON_CBN_SELCHANGE(IDC_PREVIEW_MODE, OnSelchangePreviewMode)
	ON_CBN_SELCHANGE(IDC_PREVIEW_NUMBER, OnSelchangePreviewNumber)
	ON_BN_CLICKED(IDC_BTN_GET_PREVIEWCFG, OnBtnGetPreviewcfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSubDlgPreviewCfgV30::F_Get(void)
{
	m_ctlPreviewNumber.SetCurSel(m_stPreviewCfgV30.byPreviewNumber);
	m_ctlEnableAudio.SetCurSel(m_stPreviewCfgV30.byEnableAudio);
	m_ctlSwitchTime.SetCurSel(m_stPreviewCfgV30.wSwitchTime);

 	m_ctlPreviewMode.SetCurSel(m_stPreviewCfgV30.byPreviewNumber);
//     OnSelchangePreviewMode();
    m_ctlPreviewMode.EnableWindow(FALSE);
	F_GetSwitchSeq(m_stPreviewCfgV30.byPreviewNumber);
}

void CSubDlgPreviewCfgV30::F_Set(void)
{
	m_stPreviewCfgV30.byPreviewNumber = m_ctlPreviewNumber.GetCurSel();
	m_stPreviewCfgV30.byEnableAudio = m_ctlEnableAudio.GetCurSel();
	m_stPreviewCfgV30.wSwitchTime = m_ctlSwitchTime.GetCurSel();
	
	F_SetSwitchSeq(m_stPreviewCfgV30.byPreviewNumber);
}

void CSubDlgPreviewCfgV30::F_GetSwitchSeq(int nPreviewMode)
{
    int iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	for (int i = 0; i < MAX_WINDOW_V30; i++)
	{
		m_SubDlgWndSequence[i].OnInitialize(g_struDeviceInfo[iDevIndex].iDeviceChanNum, g_struDeviceInfo[iDevIndex].iIPChanNum, g_struDeviceInfo[iDevIndex].iStartChan);
		m_SubDlgWndSequence[i].OnSetCurSel(m_stPreviewCfgV30.bySwitchSeq[nPreviewMode][i]);
	}
}

void CSubDlgPreviewCfgV30::F_SetSwitchSeq(int nPreviewMode)
{
	for (int i = 0; i < MAX_WINDOW_V30; i++)
	{
		m_stPreviewCfgV30.bySwitchSeq[nPreviewMode][i] = m_SubDlgWndSequence[i].OnGetCurSel();
	}
}

void CSubDlgPreviewCfgV30::F_ResizeWnd(int nMaxWndNumber)
{
	int nWndWidth = 0;
	int nWndHeight = 0;
	int nWndX = 0;
	int nWndY = 0;
	int nFactor = 0;

	int i = 0;
	int j = 0;
	int nTmp = 0;
	DOUBLE dfTmp = 0;
	const DOUBLE DOUBLE_ZERO = 0e032;
	CRect rtPre(0, 0, 0, 0);
	CRect rtCur(0, 0, 0, 0);
	CRect rtArea(0, 0, 0, 0);

	//////////////////////////////////////////////////////////////////////////
	
	if (nMaxWndNumber > MAX_WINDOW_V30)
	{
		nMaxWndNumber = MAX_WINDOW_V30;
	}
	for (i = 0; i < nMaxWndNumber; i++)
    {
        if (NULL == m_SubDlgWndSequence[i].m_hWnd)
		{
			m_SubDlgWndSequence[i].Create(IDD_SUBDLG_WND_SEQUENCE, this);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	
	for (i = 0; i < nMaxWndNumber; i++)
	{
		dfTmp = sqrt((double)(nMaxWndNumber+i));
		nTmp = (int)dfTmp;
		dfTmp -= (double)((int)dfTmp);
		if (dfTmp <= DOUBLE_ZERO && dfTmp >= DOUBLE_ZERO)
		{
			nFactor = nTmp;
			if (!nFactor)
			{
				return;
			}
			break;
		}
	}

    
    GetDlgItem(IDC_WND_AREA)->GetWindowRect(&rtArea);
    if (0 == nFactor)
	{
		return; 
	}
	nWndWidth = rtArea.Width() / nFactor;
	nWndHeight = rtArea.Height() / nFactor;

	//////////////////////////////////////////////////////////////////////////
	//assign windows position
	for (i = 0; i < nFactor; i++)
	{//row
		for (j = 0; j < nFactor; j++)
		{
			if (0 == i && 0 == j)
			{
				rtCur = CRect(rtArea.left, rtArea.top, rtArea.left+nWndWidth, rtArea.top+nWndHeight);
			}else if (0 == i)
			{
				m_SubDlgWndSequence[j-1].GetWindowRect(&rtPre);
				rtCur = CRect(rtPre.right, rtArea.top, rtPre.right+nWndWidth, rtArea.top+nWndHeight);
			}else if (0 == j)
			{
				m_SubDlgWndSequence[nFactor*(i-1)].GetWindowRect(&rtPre);
				rtCur = CRect(rtArea.left, rtPre.bottom, rtArea.left+nWndWidth, rtPre.bottom+nWndHeight);
			}
			else
			{
				m_SubDlgWndSequence[nFactor*(i-1)+(j-1)].GetWindowRect(&rtPre);
				rtCur = CRect(rtPre.right, rtPre.bottom, rtPre.right+nWndWidth, rtPre.bottom+nWndHeight);
			}
			if (nFactor*i+j >= nMaxWndNumber)
			{
				break;
			}
			m_SubDlgWndSequence[nFactor*i+j].MoveWindow(rtCur);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//show windows(1~byScreenNum)
	for (i = 0; i < nMaxWndNumber; i++)
	{
		m_SubDlgWndSequence[i].ShowWindow(SW_SHOW);
	}
}



BOOL CSubDlgPreviewCfgV30::OnInitDialog() 
{
    CDialog::OnInitDialog();  
    GetDlgItem(IDC_BTN_SET_PREVIEWCFG)->EnableWindow(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgPreviewCfgV30::GetPreviewCfg()
{
	DWORD dwReturned = 0;

	memset(&m_stPreviewCfgV30, 0, sizeof(m_stPreviewCfgV30));
    if (0 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_GET_PREVIEWCFG_V30;
    }
    else if (1 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_GET_PREVIEWCFG_AUX_V30;
    }
    else if (2 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_GET_ZERO_PREVIEWCFG_V30;
    }
    else if (3 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_GET_VGA_PREVIEWCFG;
    }

	m_stPreviewCfgV30.dwSize = sizeof(m_stPreviewCfgV30);
	if (!NET_DVR_GetDVRConfig(m_lServerID, m_dwCommand, 0, &m_stPreviewCfgV30, sizeof(m_stPreviewCfgV30), &dwReturned))
	{
        if (m_dwCommand == NET_DVR_GET_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_GET_PREVIEWCFG_AUX_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PREVIEWCFG_AUX_V30");
        }
        else if (m_dwCommand == NET_DVR_GET_ZERO_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ZERO_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_GET_VGA_PREVIEWCFG)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VGA_PREVIEWCFG");
        }
	}
	else
	{
		F_ResizeWnd(MAX_WINDOW_V30);
		F_Get();
        
        GetDlgItem(IDC_BTN_SET_PREVIEWCFG)->EnableWindow(TRUE);
        if (m_dwCommand == NET_DVR_GET_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_GET_PREVIEWCFG_AUX_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PREVIEWCFG_AUX_V30");
        }
        else if (m_dwCommand == NET_DVR_GET_ZERO_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ZERO_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_GET_VGA_PREVIEWCFG)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VGA_PREVIEWCFG");
        }

	}

}

void CSubDlgPreviewCfgV30::OnBtnSetPreviewcfg() 
{
	UpdateData(TRUE);
 	F_Set();
    if (0 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_SET_PREVIEWCFG_V30;
    }
    else if (1 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_SET_PREVIEWCFG_AUX_V30;
    }
    else if (2 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_SET_ZERO_PREVIEWCFG_V30;
    }
    else if (3 == m_iPreviewType)
    {
        m_dwCommand = NET_DVR_SET_VGA_PREVIEWCFG;
    }

	int i=0, j=0;
	for (i=0; i<MAX_PREVIEW_MODE; i++)
	{
		for (j=0; j<MAX_WINDOW_V30; j++)
		{
			if(m_stPreviewCfgV30.bySwitchSeq[i][j] == 0)
			{
				m_stPreviewCfgV30.bySwitchSeq[i][j] = 0xff;
			}
		}
	}
	if (!NET_DVR_SetDVRConfig(m_lServerID, m_dwCommand, 0, &m_stPreviewCfgV30, sizeof(m_stPreviewCfgV30)))
	{
        if (m_dwCommand == NET_DVR_SET_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_SET_PREVIEWCFG_AUX_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PREVIEWCFG_AUX_V30");
        }
        else if (m_dwCommand == NET_DVR_SET_ZERO_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ZERO_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_SET_VGA_PREVIEWCFG)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VGA_PREVIEWCFG");
        }
	}
	else
	{
        if (m_dwCommand == NET_DVR_SET_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_SET_PREVIEWCFG_AUX_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PREVIEWCFG_AUX_V30");
        }
        else if (m_dwCommand == NET_DVR_SET_ZERO_PREVIEWCFG_V30)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ZERO_PREVIEWCFG_V30");
        }
        else if (m_dwCommand == NET_DVR_SET_VGA_PREVIEWCFG)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VGA_PREVIEWCFG");
        }
    }
}

void CSubDlgPreviewCfgV30::OnDropdownPreviewMode() 
{
	// TODO: Add your control notification handler code here

	int nIndex = m_ctlPreviewMode.GetCurSel();

	if (-1 == nIndex)
	{
		return;
	}
	F_SetSwitchSeq(nIndex);
}

void CSubDlgPreviewCfgV30::OnSelchangePreviewMode() 
{
	int nIndex = m_ctlPreviewMode.GetCurSel();

	if (-1 == nIndex)
	{
		return;
	}
	F_GetSwitchSeq(nIndex);	
}

void CSubDlgPreviewCfgV30::OnSelchangePreviewNumber() 
{
    int nIndex = m_ctlPreviewNumber.GetCurSel();
    
    if (-1 == nIndex)
    {
        return;
    }
	F_ResizeWnd(MAX_WINDOW_V30);
    m_ctlPreviewMode.SetCurSel(nIndex);
    OnSelchangePreviewMode();
}

void CSubDlgPreviewCfgV30::OnBtnGetPreviewcfg() 
{
    GetPreviewCfg();
}
