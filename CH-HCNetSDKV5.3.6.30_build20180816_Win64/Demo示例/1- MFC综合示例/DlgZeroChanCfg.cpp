// DlgZeroChanCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgZeroChanCfg.h"
#include "SubDlgPreviewCfgV30.h"
#include "DlgPreviewSwitchCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgZeroChanCfg dialog

CDlgZeroChanCfg::CDlgZeroChanCfg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgZeroChanCfg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgZeroChanCfg)
    m_iBitRate = 0;
    m_bEnableZeroChanCfg = FALSE;
    //}}AFX_DATA_INIT
    memset(&m_struZeroChanCfg, 0, sizeof(m_struZeroChanCfg));
    memset(&m_struZeroZoomCfg, 0, sizeof(m_struZeroZoomCfg));
    memset(&m_struMainPreviewCfg, 0, sizeof(m_struMainPreviewCfg));
    memset(&m_struAuxPreviewCfg, 0, sizeof(m_struAuxPreviewCfg));
    m_iDevIndex = -1;
    m_lServerID = -1;
}

void CDlgZeroChanCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgZeroChanCfg)
	DDX_Control(pDX, IDC_COMBO_PREVIEW_TYPE, m_comboPreviewType);
    DDX_Control(pDX, IDC_COMBO_FRAME_RATE, m_comboFrameRate);
    DDX_Control(pDX, IDC_COMBO_MAX_BIT_RATE, m_comboBitRate);
    DDX_Text(pDX, IDC_EDIT_BIT_RATE, m_iBitRate);
    DDX_Check(pDX, IDC_CHK_ZEROCHANCFG, m_bEnableZeroChanCfg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZeroChanCfg, CDialog)
//{{AFX_MSG_MAP(CDlgZeroChanCfg)
ON_BN_CLICKED(IDC_CHK_ZEROCHANCFG, OnChkZerochancfg)
ON_CBN_SELCHANGE(IDC_COMBO_MAX_BIT_RATE, OnSelchangeComboMaxBitRate)
	ON_BN_CLICKED(IDC_BTN_PREVIEWCFG, OnBtnPreviewcfg)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW_SWITCH, OnButtonPreviewSwitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZeroChanCfg message handlers

BOOL CDlgZeroChanCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

    return TRUE;  
}

void CDlgZeroChanCfg::OnOK() 
{
    UpdateData(TRUE);
    m_struZeroChanCfg.byEnable = m_bEnableZeroChanCfg;
    m_struZeroChanCfg.dwVideoFrameRate = m_comboFrameRate.GetCurSel();
    if (m_comboBitRate.GetCurSel() == 22)	//adjust bit rate settings
    {
        m_struZeroChanCfg.dwVideoBitrate = m_iBitRate*1024;		
        if (m_struZeroChanCfg.dwVideoBitrate < 32*1024)
        {
            m_struZeroChanCfg.dwVideoBitrate = 32*1024;
        }
        if (m_struZeroChanCfg.dwVideoBitrate > 8192*1024)
        {
            m_struZeroChanCfg.dwVideoBitrate =  8192*1024;
        }
        m_struZeroChanCfg.dwVideoBitrate |= 0x80000000;
    }
    else
    {
        m_struZeroChanCfg.dwVideoBitrate = m_comboBitRate.GetCurSel()+2;
    }
        
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ZEROCHANCFG, 1, &m_struZeroChanCfg, sizeof(m_struZeroChanCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ZEROCHANCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ZEROCHANCFG");
        //AfxMessageBox("NET_DVR_SET_ZEROCHANCFG fail");
    }
    
//     m_struZeroZoomCfg.byState = 0;
//     if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ZERO_ZOOM, 1, &m_struZeroZoomCfg, sizeof(m_struZeroZoomCfg)))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ZERO_ZOOM");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ZERO_ZOOM");
//         AfxMessageBox("NET_DVR_SET_ZERO_ZOOM fail");
//     }

    //CDialog::OnOK();
}

void CDlgZeroChanCfg::OnChkZerochancfg() 
{
    UpdateData(TRUE);
    EnableZeroChanCfg(m_bEnableZeroChanCfg);
}

void CDlgZeroChanCfg::EnableZeroChanCfg(BOOL bEnable)
{
    GetDlgItem(IDC_COMBO_FRAME_RATE)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMBO_MAX_BIT_RATE)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(bEnable);
}


void CDlgZeroChanCfg::OnSelchangeComboMaxBitRate() 
{
    UpdateData(TRUE);
    if (m_comboBitRate.GetCurSel() == 22)	//self-define bitrate
    {
        GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
    }
}

void CDlgZeroChanCfg::OnBtnPreviewcfg() 
{
	CSubDlgPreviewCfgV30 dlg;
    dlg.m_iPreviewType = m_comboPreviewType.GetCurSel();
    if (dlg.m_iPreviewType == CB_ERR)
    {
        return;
    }
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void  CDlgZeroChanCfg::CurCfgUpdate()
{
    if (!CheckInitParam())
    {

    }
}

BOOL CDlgZeroChanCfg::CheckInitParam()
{
    m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;

    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ZEROCHANCFG, 1, &m_struZeroChanCfg, sizeof(m_struZeroChanCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ZEROCHANCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ZEROCHANCFG");
        //AfxMessageBox("NET_DVR_GET_ZEROCHANCFG fail");
        return FALSE;
    }
    
    //  Zero Chan Config
    m_bEnableZeroChanCfg = m_struZeroChanCfg.byEnable;
    EnableZeroChanCfg(m_struZeroChanCfg.byEnable);
    m_comboFrameRate.SetCurSel(m_struZeroChanCfg.dwVideoFrameRate);
    if ((m_struZeroChanCfg.dwVideoBitrate >> 31) & 0x01)
    {
        GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
        m_comboBitRate.SetCurSel(22);		//adjust bit rate settings
        m_iBitRate = (m_struZeroChanCfg.dwVideoBitrate & 0x7fffffff)/1024;
    }
    else
    {
        m_comboBitRate.SetCurSel(m_struZeroChanCfg.dwVideoBitrate-2);			
        m_iBitRate = 0;
        GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
    }
    // Zero Chan Config
    
    m_comboPreviewType.SetCurSel(0);
    UpdateData(FALSE);
    return TRUE;
}

void CDlgZeroChanCfg::OnButtonPreviewSwitch() 
{
	// TODO: Add your control notification handler code here
	CDlgPreviewSwitchCfg dlg;

    dlg.m_lUserID = m_lServerID;
    dlg.m_dwDevIndex = m_iDevIndex;
    dlg.DoModal();
}
