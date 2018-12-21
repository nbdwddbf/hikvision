// DlgMatDecBigScrSplice.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMatDecBigScrSplice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMatDecBigScrSplice dialog


CDlgMatDecBigScrSplice::CDlgMatDecBigScrSplice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMatDecBigScrSplice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMatDecBigScrSplice)
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgMatDecBigScrSplice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMatDecBigScrSplice)
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_cmResolution);
	DDX_Control(pDX, IDC_COMBO_SCREENSPLICE_VIDEOFORMAT, m_cmFormat);
	DDX_Control(pDX, IDC_COMBO_MODE_Y, m_cmModeY);
	DDX_Control(pDX, IDC_COMBO_MODE_X, m_cmModeX);
	DDX_Control(pDX, IDC_COMBO_DECODERCHANNUM, m_cmDecoderChanNum);
	DDX_Control(pDX, IDC_COMBO_SCREENSEQ, m_cmScreenSeq);
	DDX_Control(pDX, IDC_COMBO_FOLLOWSCREENSEQ, m_cmFollowScreenSeq);
	DDX_Control(pDX, IDC_COMBO_DISPCHANNUM, m_cmDispChanNum);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMatDecBigScrSplice, CDialog)
	//{{AFX_MSG_MAP(CDlgMatDecBigScrSplice)
	ON_BN_CLICKED(IDC_BTN_FOLLOWSCREEN_OK, OnBtnFollowscreenOk)
	ON_CBN_SELCHANGE(IDC_COMBO_FOLLOWSCREENSEQ, OnSelchangeComboFollowscreenseq)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SCREENSEQ, OnSelchangeComboScreenseq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMatDecBigScrSplice message handlers

BOOL CDlgMatDecBigScrSplice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	memset(&m_struMatrixDecAbility, 0, sizeof(m_struMatrixDecAbility));
    if (!NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDeviceIndex].lLoginID, MATRIXDECODER_ABILITY_V41, NULL, 0, (char*)&m_struMatrixDecAbility, sizeof(m_struMatrixDecAbility)))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return FALSE;
    }
	
	//大屏序号初始化
	CString csStr;
	int i = 0;
    for(i = 0; i < m_struMatrixDecAbility.struBigScreenInfo.bySupportBigScreenNums; i++)
    {
        csStr.Format("%d", i + 1);
        m_cmScreenSeq.AddString(csStr);
    }

	//从屏序号初始化
	DWORD dwModeIndex = m_struMatrixDecAbility.struBigScreenInfo.byMaxScreenX * m_struMatrixDecAbility.struBigScreenInfo.byMaxScreenY;
	for(i=0; i<dwModeIndex; i++)
	{
		csStr.Format("%d", i+1);
		m_cmFollowScreenSeq.AddString(csStr);
	}
	//显示通道初始化
	for (i=0; i<m_struMatrixDecAbility.struBncInfo.byChanNums; i++)
	{
		csStr.Format("BNC%d", i+1);
		m_cmDispChanNum.AddString(csStr);
	}

	for (i=0; i<m_struMatrixDecAbility.struVgaInfo.byChanNums; i++)
	{
		csStr.Format("VGA%d", i+1);
		m_cmDispChanNum.AddString(csStr);
	}

	for (i=0; i<m_struMatrixDecAbility.struHdmiInfo.byChanNums; i++)
	{
		csStr.Format("HDMI%d", i+1);
		m_cmDispChanNum.AddString(csStr);
	}
	
	for (i=0; i<m_struMatrixDecAbility.struDviInfo.byChanNums; i++)
	{
		csStr.Format("DVI%d", i+1);
		m_cmDispChanNum.AddString(csStr);
	}

	//解码通道初始化
	for (i=0; i<m_struMatrixDecAbility.byDecChanNums; i++)
	{
		csStr.Format("%d", i + 1);
		m_cmDecoderChanNum.AddString(csStr);
	}

	//拼接模式初始化
	for (i=0; i<m_struMatrixDecAbility.struBigScreenInfo.byMaxScreenX; i++)
	{
		csStr.Format("%d", i+1);
		m_cmModeX.AddString(csStr);
	}
	for (i=0; i<m_struMatrixDecAbility.struBigScreenInfo.byMaxScreenY; i++)
	{
		csStr.Format("%d", i+1);
		m_cmModeY.AddString(csStr);
	}

	//分辨率初始化
	char szLan[128] = {0};
// 	m_iVGAResolutionNum = 0;
// 	m_iHDMIResolutionNum = 0;
// 	m_iDVIResolutionNum = 0;
	int iIndex = 0;
	GetResolutionString(0, szLan);
	m_cmResolution.AddString(szLan);
	for (i=0; i<MAX_SUPPORT_RES; i++)
	{
		GetResolutionString(m_struMatrixDecAbility.struVgaInfo.dwSupportResolution[i], szLan);
		if (CB_ERR == m_cmResolution.FindStringExact(0, szLan))
		{
			m_cmResolution.AddString(szLan);
			iIndex = m_cmResolution.FindStringExact(0, szLan);
			m_cmResolution.SetItemData(iIndex, m_struMatrixDecAbility.struVgaInfo.dwSupportResolution[i]);
		}
	}
	for (i=0; i<MAX_SUPPORT_RES; i++)
	{
		if (m_struMatrixDecAbility.struHdmiInfo.dwSupportResolution[i] !=0)
		{
			GetResolutionString(m_struMatrixDecAbility.struHdmiInfo.dwSupportResolution[i], szLan);
			if (CB_ERR == m_cmResolution.FindStringExact(0, szLan))
			{
				m_cmResolution.AddString(szLan);
				iIndex = m_cmResolution.FindStringExact(0, szLan);
				m_cmResolution.SetItemData(iIndex, m_struMatrixDecAbility.struHdmiInfo.dwSupportResolution[i]);
			}
		}
	}
	for (i=0; i<MAX_SUPPORT_RES; i++)
	{
		if (m_struMatrixDecAbility.struDviInfo.dwSupportResolution[i] !=0)
		{
			GetResolutionString(m_struMatrixDecAbility.struDviInfo.dwSupportResolution[i], szLan);
			if (CB_ERR == m_cmResolution.FindStringExact(0,szLan))
			{
				m_cmResolution.AddString(szLan);
				iIndex = m_cmResolution.FindStringExact(0, szLan);
				m_cmResolution.SetItemData(iIndex, m_struMatrixDecAbility.struDviInfo.dwSupportResolution[i]);
			}
		}
	}
	UpdateData(FALSE);
	memset(&m_struBigScreenCfg, 0, sizeof(m_struBigScreenCfg));

	m_cmScreenSeq.SetCurSel(0);
	OnSelchangeComboScreenseq();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMatDecBigScrSplice::OnBtnFollowscreenOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwFollowSeq = m_cmFollowScreenSeq.GetCurSel();
	DWORD dwChanNum = m_cmDispChanNum.GetCurSel();
	if(dwChanNum < m_struMatrixDecAbility.struBncInfo.byChanNums)
	{
		m_struBigScreenCfg.struFollowSingleScreen[dwFollowSeq].byDispNum = dwChanNum + m_struMatrixDecAbility.struBncInfo.byStartChan;
	}
	else if ((dwChanNum >= m_struMatrixDecAbility.struBncInfo.byChanNums) && (dwChanNum < m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struVgaInfo.byChanNums))
    {
		m_struBigScreenCfg.struFollowSingleScreen[dwFollowSeq].byDispNum = dwChanNum - m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struVgaInfo.byStartChan;
	}
	else if ((dwChanNum >= m_struMatrixDecAbility.struVgaInfo.byChanNums + m_struMatrixDecAbility.struBncInfo.byChanNums) && (dwChanNum < m_struMatrixDecAbility.struVgaInfo.byChanNums + m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struHdmiInfo.byChanNums))
    {
		m_struBigScreenCfg.struFollowSingleScreen[dwFollowSeq].byDispNum = dwChanNum - m_struMatrixDecAbility.struVgaInfo.byChanNums - m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struHdmiInfo.byStartChan;
	}
	else if ((dwChanNum >= m_struMatrixDecAbility.struVgaInfo.byChanNums + m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struHdmiInfo.byChanNums) && \
		(dwChanNum < m_struMatrixDecAbility.struDviInfo.byChanNums + m_struMatrixDecAbility.struHdmiInfo.byChanNums + m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struVgaInfo.byChanNums))
    {
		m_struBigScreenCfg.struFollowSingleScreen[dwFollowSeq].byDispNum = dwChanNum - m_struMatrixDecAbility.struVgaInfo.byChanNums - m_struMatrixDecAbility.struBncInfo.byChanNums - m_struMatrixDecAbility.struHdmiInfo.byChanNums + m_struMatrixDecAbility.struDviInfo.byStartChan;
	}
	m_struBigScreenCfg.struFollowSingleScreen[dwFollowSeq].byScreenSeq = dwFollowSeq + 1;
}

void CDlgMatDecBigScrSplice::OnSelchangeComboFollowscreenseq() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwFollowSeq = m_cmFollowScreenSeq.GetCurSel();
	DWORD dwChanNum = m_struBigScreenCfg.struFollowSingleScreen[dwFollowSeq].byDispNum;
	DWORD dwSel = 0;
	if (dwFollowSeq>=(m_struBigScreenCfg.byModeX*m_struBigScreenCfg.byModeY))
	{
		m_cmDispChanNum.SetCurSel(-1);
	}
	else
	{
		if(dwChanNum < m_struMatrixDecAbility.struVgaInfo.byStartChan)
		{
			dwSel = dwChanNum - m_struMatrixDecAbility.struBncInfo.byStartChan;
		}
		else if ((dwChanNum >= m_struMatrixDecAbility.struVgaInfo.byStartChan) && (dwChanNum <m_struMatrixDecAbility.struHdmiInfo.byStartChan))
		{
			dwSel = dwChanNum - m_struMatrixDecAbility.struVgaInfo.byStartChan + m_struMatrixDecAbility.struBncInfo.byChanNums;
		}
		else if ((dwChanNum >= m_struMatrixDecAbility.struHdmiInfo.byStartChan) && (dwChanNum <m_struMatrixDecAbility.struDviInfo.byStartChan))
		{
			dwSel = dwChanNum - m_struMatrixDecAbility.struHdmiInfo.byStartChan + m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struVgaInfo.byChanNums;
		}
		else if (dwChanNum >= m_struMatrixDecAbility.struDviInfo.byStartChan)
		{
			dwSel = dwChanNum - m_struMatrixDecAbility.struDviInfo.byStartChan + m_struMatrixDecAbility.struBncInfo.byChanNums + m_struMatrixDecAbility.struVgaInfo.byChanNums + m_struMatrixDecAbility.struHdmiInfo.byChanNums;
		}
		m_cmDispChanNum.SetCurSel(dwSel);
	}
	UpdateData(FALSE);
}

void CDlgMatDecBigScrSplice::OnBtnGet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwReturned = 0;
	DWORD dwChanNum = m_cmScreenSeq.GetCurSel() + 1;
	memset(&m_struBigScreenCfg, 0, sizeof(m_struBigScreenCfg));
	m_struBigScreenCfg.dwSize = sizeof(m_struBigScreenCfg);
    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_MATRIX_BIGSCREENCFG_GET, dwChanNum, &m_struBigScreenCfg, sizeof(m_struBigScreenCfg), &dwReturned))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MATRIX_BIGSCREENCFG_GET failed");
        MessageBox("NET_DVR_MATRIX_BIGSCREENCFG_GET failed");
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MATRIX_BIGSCREENCFG_GET succ");
	}
	SetBigScreenInfoToDlg();
    UpdateData(FALSE);
}

void CDlgMatDecBigScrSplice::SetBigScreenInfoToDlg()
{
	char szBuf[128] = {0};
	m_cmDecoderChanNum.SetCurSel(m_struBigScreenCfg.byMainDecodeSystem - 1); //解码其中byMainDecodeSystem表示解码通道号
	m_bEnable = m_struBigScreenCfg.byEnable;
	m_cmModeX.SetCurSel(m_struBigScreenCfg.byModeX - 1);
	m_cmModeY.SetCurSel(m_struBigScreenCfg.byModeY - 1);
	m_cmDecoderChanNum.SetCurSel(m_struBigScreenCfg.byMainDecodeSystem - 1);
	m_cmFollowScreenSeq.SetCurSel(0);
	m_cmFormat.SetCurSel(m_struBigScreenCfg.byVideoStandard);

	GetResolutionString(m_struBigScreenCfg.dwResolution, szBuf);
	int iIndex = m_cmResolution.FindStringExact(0, szBuf);
	m_cmResolution.SetCurSel(iIndex);

	UpdateData(FALSE);
	OnSelchangeComboFollowscreenseq();
	UpdateData(FALSE);
}

void CDlgMatDecBigScrSplice::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwChanNum = m_cmScreenSeq.GetCurSel() + 1;
    m_struBigScreenCfg.dwSize = sizeof(m_struBigScreenCfg);
    m_struBigScreenCfg.byEnable = m_bEnable;
    m_struBigScreenCfg.byModeX = m_cmModeX.GetCurSel() + 1;
    m_struBigScreenCfg.byModeY = m_cmModeY.GetCurSel() + 1; 
	m_struBigScreenCfg.byMainDecodeSystem = m_cmDecoderChanNum.GetCurSel() + 1;

	//获取分辨率的值
	int iResSel = m_cmResolution.GetCurSel();
// 	if (iResSel < m_iVGAResolutionNum)
// 	{
// 		m_struBigScreenCfg.dwResolution = m_struMatrixDecAbility.struVgaInfo.dwSupportResolution[iResSel];
// 	}
// 	else if (iResSel >= m_iVGAResolutionNum && iResSel<(m_iHDMIResolutionNum + m_iVGAResolutionNum))
// 	{
// 		iResSel -= m_iVGAResolutionNum; 
// 		m_struBigScreenCfg.dwResolution = m_struMatrixDecAbility.struHdmiInfo.dwSupportResolution[iResSel];
// 	}
// 	else if (iResSel >= m_iVGAResolutionNum+m_iHDMIResolutionNum && (iResSel<m_iHDMIResolutionNum + m_iVGAResolutionNum + m_iDVIResolutionNum))
// 	{
// 		iResSel = iResSel - m_iVGAResolutionNum - m_iHDMIResolutionNum;
// 		m_struBigScreenCfg.dwResolution = m_struMatrixDecAbility.struDviInfo.dwSupportResolution[iResSel];
// 	}
	m_struBigScreenCfg.dwResolution = m_cmResolution.GetItemData(iResSel);
	m_struBigScreenCfg.byVideoStandard = m_cmFormat.GetCurSel();
    if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_MATRIX_BIGSCREENCFG_SET, dwChanNum, &m_struBigScreenCfg, sizeof(m_struBigScreenCfg)))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MATRIX_BIGSCREENCFG_SET failed");
        MessageBox("NET_DVR_MATRIX_BIGSCREENCFG_SET failed");
        return;
    }
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MATRIX_BIGSCREENCFG_SET succ");
    MessageBox("set success!");
}

void CDlgMatDecBigScrSplice::GetResolutionString(DWORD dwRes, char *lpResString)
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

void CDlgMatDecBigScrSplice::OnSelchangeComboScreenseq() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnGet();
}
