// DlgDecoderAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDecoderAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoderAbility dialog


CDlgDecoderAbility::CDlgDecoderAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDecoderAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDecoderAbility)
	m_byDecChanNums = 0;
	m_byDispChanSeq = 0;
	m_byDspNums = 0;
	m_byScreenX = 0;
	m_byScreenY = 0;
	m_byStartScreenNums = 0;
	m_byStartChan = 0;
	m_bySupportScreenNums = 0;
	m_byDispChanNums = 0;
	m_byDispStartChan = 0;
	//}}AFX_DATA_INIT
}


void CDlgDecoderAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDecoderAbility)
	DDX_Control(pDX, IDC_COMBO_DISP_SEQ, m_cmDispSeq);
	DDX_Control(pDX, IDC_COMBO_WINDOW_DISPMODE, m_cmWindowDispMode);
	DDX_Control(pDX, IDC_COMBO_SUPRES, m_cmSupRes);
	DDX_Control(pDX, IDC_COMBO_DISPWINDOWCHANTYPE, m_cmDispWindowChanType);
	DDX_Control(pDX, IDC_COMBO_CHANDISPMODE, m_cmDispMode);
	DDX_Text(pDX, IDC_EDIT_DECCHANNUMS, m_byDecChanNums);
	DDX_Text(pDX, IDC_EDIT_DISPCHANSEQ, m_byDispChanSeq);
	DDX_Text(pDX, IDC_EDIT_DSPNUM, m_byDspNums);
	DDX_Text(pDX, IDC_EDIT_SCREEN_X, m_byScreenX);
	DDX_Text(pDX, IDC_EDIT_SCREEN_Y, m_byScreenY);
	DDX_Text(pDX, IDC_EDIT_START_SCREENNUM, m_byStartScreenNums);
	DDX_Text(pDX, IDC_EDIT_STARTCHAN, m_byStartChan);
	DDX_Text(pDX, IDC_EDIT_SUPPORT_SCREENNUMS, m_bySupportScreenNums);
	DDX_Text(pDX, IDC_EDIT_DISP_CHANNUMS, m_byDispChanNums);
	DDX_Text(pDX, IDC_EDIT_DISP_STARTCHAN, m_byDispStartChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDecoderAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgDecoderAbility)
	ON_BN_CLICKED(IDC_BTN_RFRESH, OnBtnRfresh)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANDISPMODE, OnSelchangeComboDispmode)
	ON_CBN_SELCHANGE(IDC_COMBO_DISP_SEQ, OnSelchangeComboDispSeq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoderAbility message handlers

BOOL CDlgDecoderAbility::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csStr;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	for (int i=0; i<MAX_DISPNUM_V41; i++)
	{
		csStr.Format("%d", i+1);
		m_cmDispSeq.AddString(csStr);
	}
	OnBtnRfresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDecoderAbility::OnBtnRfresh() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struMatrixAbility, 0, sizeof(m_struMatrixAbility)); 
	if (NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDeviceIndex].lLoginID, MATRIXDECODER_ABILITY_V41, NULL, 0, (char*)&m_struMatrixAbility, sizeof(m_struMatrixAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "MATRIXDECODER_ABILITY_V41 SUCE");
		SetInfoToDlg(&m_struMatrixAbility);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "MATRIXDECODER_ABILITY_V41 failed");
		MessageBox("MATRIXDECODER_ABILITY_V41 failed");
	}
}

void CDlgDecoderAbility::SetInfoToDlg(LPNET_DVR_MATRIX_ABILITY_V41 lpInter)
{
	m_byDspNums = lpInter->byDspNums;
	m_byDecChanNums = lpInter->byDecChanNums;
	m_byStartChan = lpInter->byStartChan;

	m_bySupportScreenNums = lpInter->struBigScreenInfo.bySupportBigScreenNums;
	m_byStartScreenNums = lpInter->struBigScreenInfo.byStartBigScreenNum;
	m_byScreenX = lpInter->struBigScreenInfo.byMaxScreenX;
	m_byScreenY = lpInter->struBigScreenInfo.byMaxScreenY;

	m_cmDispMode.SetCurSel(-1);
	m_cmDispSeq.SetCurSel(-1);
	//OnSelchangeComboDispSeq();

	UpdateData(FALSE);
}

void CDlgDecoderAbility::OnSelchangeComboDispmode()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString csStr;
	int i = 0;
	DWORD dwDispMode = m_cmDispMode.GetCurSel();
	char sResStr[64] = {0};
	m_cmSupRes.ResetContent();
	GetResolutionString(0, sResStr);
	csStr.Format("%s", sResStr);
	m_cmSupRes.AddString(csStr);
	if (dwDispMode == 0)
	{
		m_byDispChanNums = m_struMatrixAbility.struBncInfo.byChanNums;
		m_byDispStartChan = m_struMatrixAbility.struBncInfo.byStartChan;
		if (m_struMatrixAbility.struBncInfo.dwSupportResolution[i] != 0)
		{
			memset(sResStr, 0, sizeof(sResStr));
			GetResolutionString(m_struMatrixAbility.struBncInfo.dwSupportResolution[i], sResStr);
			csStr.Format("%s", sResStr);
			m_cmSupRes.AddString(csStr);
		}
		/*for (i = 0; i<MAX_SUPPORT_RES; i++)
		{
			if (m_struMatrixAbility.struBncInfo.dwSupportResolution[i] != 0)
			{
				memset(sResStr, 0, sizeof(sResStr));
				GetResolutionString(m_struMatrixAbility.struBncInfo.dwSupportResolution[i], sResStr);
				csStr.Format("%s", sResStr);
				m_cmSupRes.AddString(csStr);
			}
		}*/	
	}
	if (dwDispMode == 1)
	{	
		m_byDispChanNums = m_struMatrixAbility.struVgaInfo.byChanNums;
		m_byDispStartChan = m_struMatrixAbility.struVgaInfo.byStartChan;
		for (i = 0; i<MAX_SUPPORT_RES; i++)
		{
			if (m_struMatrixAbility.struVgaInfo.dwSupportResolution[i] != 0)
			{
				memset(sResStr, 0, sizeof(sResStr));
				GetResolutionString(m_struMatrixAbility.struVgaInfo.dwSupportResolution[i], sResStr);
				csStr.Format("%s", sResStr);
				m_cmSupRes.AddString(csStr);
			}
		}
	}
	else if (dwDispMode == 2)
	{
		m_byDispChanNums = m_struMatrixAbility.struHdmiInfo.byChanNums;
		m_byDispStartChan = m_struMatrixAbility.struHdmiInfo.byStartChan;
		for (i = 0; i<MAX_SUPPORT_RES; i++)
		{
			if (m_struMatrixAbility.struHdmiInfo.dwSupportResolution[i] != 0)
			{	
				memset(sResStr, 0, sizeof(sResStr));
				GetResolutionString(m_struMatrixAbility.struHdmiInfo.dwSupportResolution[i],sResStr);
				csStr.Format("%s", sResStr);
				m_cmSupRes.AddString(csStr);
			}
		}
	}
	else if (dwDispMode == 3)
	{
		m_byDispChanNums = m_struMatrixAbility.struDviInfo.byChanNums;
		m_byDispStartChan = m_struMatrixAbility.struDviInfo.byStartChan;
		for (i = 0; i<MAX_SUPPORT_RES; i++)
		{
			if (m_struMatrixAbility.struDviInfo.dwSupportResolution[i] != 0)
			{
				memset(sResStr, 0, sizeof(sResStr));
				GetResolutionString(m_struMatrixAbility.struDviInfo.dwSupportResolution[i],sResStr);
				csStr.Format("%s", sResStr);
				m_cmSupRes.AddString(csStr);
			}
		}
	}
	m_cmSupRes.SetCurSel(0);
	UpdateData(FALSE);
}

void CDlgDecoderAbility::GetResolutionString(DWORD dwRes, char *lpResString)
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
		sprintf(lpResString, "%s", "ERROR");
		break;
	}
}

void CDlgDecoderAbility::OnSelchangeComboDispSeq()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString csStr;

	DWORD dwIndex = m_cmDispSeq.GetCurSel();
	m_cmDispWindowChanType.SetCurSel(m_struMatrixAbility.struDispMode[dwIndex].byDispChanType);
	m_byDispChanSeq = m_struMatrixAbility.struDispMode[dwIndex].byDispChanSeq;
	m_cmWindowDispMode.ResetContent();
	for (int i=0; i<MAX_WINDOWS_NUM; i++)
	{
		if (m_struMatrixAbility.struDispMode[dwIndex].byDispMode[i] != 0)
		{
			csStr.Format("%d", m_struMatrixAbility.struDispMode[dwIndex].byDispMode[i]);
			m_cmWindowDispMode.AddString(csStr);
		}
	}
	m_cmWindowDispMode.SetCurSel(0);
	UpdateData(FALSE);
}

