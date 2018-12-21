// DlgDecoderControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDecoderControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoderControl dialog


CDlgDecoderControl::CDlgDecoderControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDecoderControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDecoderControl)
	m_BVcaInfo = FALSE;
	m_BSpartan = FALSE;
	m_dwDecChan = 1;
	m_dwDefog = 0;
	m_dwLowLight = 0;
	//}}AFX_DATA_INIT
}


void CDlgDecoderControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDecoderControl)
	DDX_Control(pDX, IDC_SLIDER_DECODE_LOWLIGHT, m_sliLowLight);
	DDX_Control(pDX, IDC_SLIDER_DECODE_DEFOG, m_sliDefog);
	DDX_Control(pDX, IDC_COMBOSCALESTATUS, m_cmbScaleStatus);
	DDX_Control(pDX, IDC_COMBODECODEDELAY, m_cmbDelay);
	DDX_Control(pDX, IDC_COMBODECODE_3DNOISEREDUCTION, m_cmbNoiseReduction);
	DDX_Check(pDX, IDC_CHK_DECODE_DECVCAINFO, m_BVcaInfo);
	DDX_Check(pDX, IDC_CHK_DECODE_SPARTAN, m_BSpartan);
	DDX_Text(pDX, IDC_EDT_DECODE_CHANNEL, m_dwDecChan);
	DDX_Text(pDX, IDC_EDT_DECODE_DEFOG, m_dwDefog);
	DDX_Text(pDX, IDC_EDT_DECODE_LOWLIGHT, m_dwLowLight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDecoderControl, CDialog)
	//{{AFX_MSG_MAP(CDlgDecoderControl)
	ON_BN_CLICKED(IDC_BUT_DECODE_GET, OnButDecodeGet)
	ON_BN_CLICKED(IDC_BUT_DECODE_SET, OnButDecodeSet)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DECODE_DEFOG, OnCDrawSliderDecodeDefog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DECODE_LOWLIGHT, OnCDSliderDecodeLowlight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoderControl message handlers

void CDlgDecoderControl::OnButDecodeGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_MATRIX_DECCHAN_CONTROL struDecChan = {0}; 

	if (!NET_DVR_MatrixGetDecChanCfg(m_lUserID, m_dwDecChan, &struDecChan) )
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_MatrixGetDecChanCfg" );
		return; 
	}	
	if (struDecChan.byDecChanScaleStatus == 0xff)
	{
		m_cmbScaleStatus.SetCurSel(6);
    }
	else
		m_cmbScaleStatus.SetCurSel(struDecChan.byDecChanScaleStatus); 

	m_cmbNoiseReduction.SetCurSel(struDecChan.byNoiseReduction);
	m_BSpartan = 	struDecChan.byEnableSpartan ; 
	m_BVcaInfo = 	struDecChan.byEnableVcaDec ;
	m_sliLowLight.SetPos(struDecChan.byLowLight);
	m_sliDefog.SetPos(struDecChan.byDefog); 
	UpdateData(FALSE);
}

void CDlgDecoderControl::OnButDecodeSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	//NET_DVR_MATRIX_DECCHAN_CONTROL struDecChanCtrl = {0};
	NET_DVR_MATRIX_DECCHAN_CONTROL struDecChan = {0}; 
	struDecChan.dwSize = sizeof(struDecChan);
	struDecChan.byDecChanScaleStatus = m_cmbScaleStatus.GetCurSel();
	struDecChan.byNoiseReduction = m_cmbNoiseReduction.GetCurSel(); 
	struDecChan.byEnableSpartan = m_BSpartan; 
	struDecChan.byEnableVcaDec = m_BVcaInfo;  
	struDecChan.byLowLight = m_sliLowLight.GetPos(); 
	struDecChan.byDefog = m_sliDefog.GetPos(); 
    if (m_cmbDelay.GetCurSel() < 6)
    {
        struDecChan.byDecodeDelay = m_cmbDelay.GetCurSel();
    }
    else
    {
        struDecChan.byDecodeDelay = 0xff;
    }
	if (!NET_DVR_MatrixSetDecChanCfg(m_lUserID, m_dwDecChan, &struDecChan))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_MatrixSetDecChanCfg" ); 
		return;
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_MatrixSetDecChanCfg" );
}

BOOL CDlgDecoderControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
	m_lUserID = g_struDeviceInfo[m_lDeviceID].lLoginID; 
	m_sliLowLight.SetRange(0, 8);
	m_sliDefog.SetRange(0, 7); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDecoderControl::OnCDrawSliderDecodeDefog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	m_dwDefog = m_sliDefog.GetPos(); 
	UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgDecoderControl::OnCDSliderDecodeLowlight(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	m_dwLowLight = m_sliLowLight.GetPos(); 
	UpdateData(FALSE); 
	*pResult = 0;
}
