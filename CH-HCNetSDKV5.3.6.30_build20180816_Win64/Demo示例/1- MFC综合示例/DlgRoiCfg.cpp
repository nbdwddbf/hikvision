// DlgRoiCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRoiCfg.h"
#include "DlgCompressionV30.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgRoiCfg *lpRoiCfgDlg = NULL;
RECT g_rectRoiShow;
RECT g_rectRoiSetArea;

/////////////////////////////////////////////////////////////////////////////
// CDlgRoiCfg dialog

void CALLBACK DrawRoiDetectShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
//      SetBkMode(hDc, TRANSPARENT);
//      SetTextColor(hDc, RGB(255, 255, 255));
 	
     lpRoiCfgDlg->F_DrawFun(lRealHandle, hDc, dwUser);     
}

CDlgRoiCfg::CDlgRoiCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRoiCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRoiCfg)
	m_bSingleEnable = FALSE;
//	m_bEnableAll = FALSE;
	m_csRoiName = _T("");
	//}}AFX_DATA_INIT
	m_lPlayHandle = -1;
	m_bFixRoi = FALSE;
	m_bTrackRoi = FALSE;
	m_dwRoiID = 0;
	m_bMouseMove = FALSE;

	memset(&m_struRoiDetectCond, 0, sizeof(m_struRoiDetectCond));
	memset(&m_struRoiDetectCfg, 0, sizeof(m_struRoiDetectCfg));
	memset(&m_struRoiRect, 0, sizeof(m_struRoiRect));
	memset(&m_struChannelGroup, 0, sizeof(m_struChannelGroup));
	memset(&m_struRoidetectNum, 0, sizeof(m_struRoidetectNum));
}


void CDlgRoiCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRoiCfg)
	DDX_Control(pDX, IDC_COMBO_TRACKTYPE, m_comboTrackType);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Control(pDX, IDC_COMBO_IMAGE_QUALITY_LEVEL, m_comboImageQualityLevel);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBO_ROIID, m_comboRoiID);
	DDX_Control(pDX, IDC_PLAYWND, m_wndPlay);
	DDX_Check(pDX, IDC_CHK_SINGLE_ENABLE, m_bSingleEnable);
	DDX_Text(pDX, IDC_EDIT_ROI_NAME, m_csRoiName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRoiCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRoiCfg)
	ON_BN_CLICKED(IDC_BTN_OUT, OnBtnOut)
	ON_BN_CLICKED(IDC_RADIO_FIXROI, OnRadioFixroi)
	ON_BN_CLICKED(IDC_RADIO_TRACKROI, OnRadioTrackroi)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_GET_ROIINFO, OnBtnGetRoiinfo)
	ON_CBN_SELCHANGE(IDC_COMBO_ROIID, OnSelchangeComboRoiid)
	ON_BN_CLICKED(IDC_BTN_GETALL, OnBtnGetall)
	ON_BN_CLICKED(IDC_BTN_TRACK, OnBtnTrack)
	ON_BN_CLICKED(IDC_BTN_TRACK_GET, OnBtnTrackGet)
	ON_WM_LBUTTONDOWN()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTN_TEST_COMPRESSV30, OnBtnTestCompressv30)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRoiCfg message handlers

BOOL CDlgRoiCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	lpRoiCfgDlg = this;
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);

	Play();
	// TODO: Add extra initialization here
	m_comboRoiID.SetCurSel(0);
	m_bFixRoi = TRUE;
	m_comboStreamType.SetCurSel(0);
	m_comboType.SetCurSel(0);
	m_comboImageQualityLevel.SetCurSel(0);
	m_bSingleEnable = TRUE;

	m_comboTrackType.SetCurSel(0);
	GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(FALSE);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgRoiCfg::Play()
{
	char szLan[128] = {0};
	char szTemp[256] = {0};
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
	
	m_lPlayHandle = NET_DVR_RealPlay_V30(m_lLoginID, &struPlayInfo, NULL, NULL, TRUE); 
	BOOL bRet = FALSE;
	if (m_lPlayHandle < 0)
	{
		g_StringLanType(szLan, "预览失败", "Realplay failed");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
        AfxMessageBox(szTemp);
		return FALSE;
	}
	
	bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawRoiDetectShow, 0);
	
	return TRUE;
}

void CDlgRoiCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
	if (m_bFixRoi)
	{
		F_DrawRect(hDc);
	}
}

void CDlgRoiCfg::F_DrawRect(HDC hDc)
{
	COLORREF color;
	color = RGB(255, 255, 0);
	
	COLORREF vtcolor;
	vtcolor = RGB(255, 0, 0);
	
	if (m_bFixRoi || m_struRoiRect[m_dwRoiID].fX != 0 || m_struRoiRect[m_dwRoiID].fY != 0 ||\
		m_struRoiRect[m_dwRoiID].fHeight != 0 || m_struRoiRect[m_dwRoiID].fWidth !=0)
	{
		CDlgRoiCfg::DrawITCRect(hDc, m_struRoiRect[m_dwRoiID], m_rcWnd, 0, vtcolor);
	}
}


void CDlgRoiCfg::DrawITCRect(HDC hDc, NET_VCA_RECT struRect,  CRect rcWnd, DWORD dwCurRect, COLORREF color)
{
    CPen DrawPen;
// 	COLORREF color;
// 	color = RGB(255, 255, 0);
    
    DrawPen.CreatePen(PS_SOLID, 1, color);
    CBrush brTmp;
    brTmp.CreateSolidBrush(color);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    CRect rect;
    rect.left = (int)(struRect.fX * rcWnd.Width());
    rect.top = (int)(struRect.fY * rcWnd.Height());
    rect.right = (int)((struRect.fX + struRect.fWidth) * rcWnd.Width());
    rect.bottom = (int)((struRect.fY + struRect.fHeight) * rcWnd.Height());
    FrameRect(hDc, rect, brTmp);
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);

}

void CDlgRoiCfg::OnBtnOut() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
    if(m_lPlayHandle >= 0)
	{
		if(!NET_DVR_StopRealPlay(m_lPlayHandle))
		{
			g_StringLanType(szLan, "停止预览失败", "Stop play failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);
		}
        m_lPlayHandle = -1;
	}

	CDialog::OnCancel();
}

BOOL CDlgRoiCfg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	CPoint pt(0, 0);
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
	GetCursorPos(&pt);
	ScreenToClient(&m_rcWnd);
	ScreenToClient(&pt);

	m_dwRoiID = m_comboRoiID.GetCurSel();

	//memset(&m_struRoiRect[m_dwRoiID], 0, sizeof(NET_VCA_RECT));	

	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
		if ((!m_comboType.GetCurSel()) && (GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))
		{
			
			if (PtInRect(&m_rcWnd, pt))
			{
				pt.x -= m_rcWnd.left;
				pt.y -= m_rcWnd.top;
				m_struRoiRect[m_dwRoiID].fX = (float)pt.x/(float)m_rcWnd.Width();
				m_struRoiRect[m_dwRoiID].fY = (float)pt.y/(float)m_rcWnd.Height();
			}
			m_bMouseMove = TRUE;
		}
		break;
	case WM_MOUSEMOVE:
		if ((!m_comboType.GetCurSel()) && m_bMouseMove && (GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0) )
		{
			if (PtInRect(&m_rcWnd, pt))
			{
				pt.x -= m_rcWnd.left;
				pt.y -= m_rcWnd.top;
				m_struRoiRect[m_dwRoiID].fWidth = (float)(pt.x - (m_struRoiRect[m_dwRoiID].fX*m_rcWnd.Width()))/(float)m_rcWnd.Width();
				m_struRoiRect[m_dwRoiID].fHeight = (float)(pt.y - (m_struRoiRect[m_dwRoiID].fY*m_rcWnd.Height()))/(float)m_rcWnd.Height();
			}
		}		
		break;
	case WM_LBUTTONUP:
		m_bMouseMove = FALSE;
		break;
	case WM_RBUTTONDOWN:
		m_bMouseMove = FALSE;	
		break;
	default:
		break;
		}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgRoiCfg::OnRadioFixroi() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bFixRoi = TRUE;
	m_bTrackRoi = FALSE;

	UpdateData(FALSE);
}

void CDlgRoiCfg::OnRadioTrackroi() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bFixRoi = FALSE;
	m_bTrackRoi = TRUE;

	//GetDlgItem(IDC_COMBO_ROIID)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgRoiCfg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iAssVal = m_dwRoiID;
	memset(&m_struRoiDetectCfg[iAssVal], 0, sizeof(NET_DVR_ROI_DETECT_CFG));
	memset(&m_struRoiDetectCond[iAssVal], 0, sizeof(NET_DVR_ROI_DETECT_COND));

	//配置条件
	m_struRoiDetectCond[iAssVal].dwSize = sizeof(NET_DVR_ROI_DETECT_COND);

	m_struRoiDetectCond[iAssVal].struMultiStreamCfg.dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
	m_struRoiDetectCond[iAssVal].struMultiStreamCfg.dwStreamType = m_comboStreamType.GetCurSel();
	
	m_struRoiDetectCond[iAssVal].struMultiStreamCfg.struStreamInfo.dwChannel = m_lChannel;
	m_struRoiDetectCond[iAssVal].struMultiStreamCfg.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	
	int itype = m_comboType.GetCurSel();
	if (/*m_bFixRoi*/!itype)
	{
		m_struRoiDetectCond[iAssVal].byRoiDetectType = DETECT_FIX_ROI;
	} 
	else
	{
		m_struRoiDetectCond[iAssVal].byRoiDetectType = DETECT_TRACK_ROI;
	}
	m_struRoiDetectCond[iAssVal].dwRoiID = m_dwRoiID+1;
	m_struRoiDetectCond[iAssVal].byRoiDetectTrackType = m_comboTrackType.GetCurSel();

	//配置内容
	m_struRoiDetectCfg[iAssVal].dwSize = sizeof(NET_DVR_ROI_DETECT_CFG);
	m_struRoiDetectCfg[iAssVal].dwStreamType = m_comboStreamType.GetCurSel();

	if (/*m_bFixRoi*/!itype)
	{
		m_struRoiDetectCfg[iAssVal].byRoiDetectType = DETECT_FIX_ROI;

		m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiFixRectCfg.byEnableFixRoi = m_bSingleEnable;
		m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiFixRectCfg.byImageQualityLevel = m_comboImageQualityLevel.GetCurSel()+1;
		memcpy(&m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiFixRectCfg.szFixRoiName, m_csRoiName, 32);
		memcpy(&m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiFixRectCfg.struRoiRect, &m_struRoiRect[m_dwRoiID], sizeof(NET_VCA_RECT));
	} 
	else
	{
		m_struRoiDetectCfg[iAssVal].byRoiDetectType = DETECT_TRACK_ROI;
		m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiTrackRectCfg.byModeType = m_comboTrackType.GetCurSel();
		m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiTrackRectCfg.byEnableTrackRoi = m_bSingleEnable;
		m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiTrackRectCfg.byImageQualityLevel = m_comboImageQualityLevel.GetCurSel()+1;
	}
}

void CDlgRoiCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i = 0;
	int j = 0;
	int iCount = 0;
	char szLan[128] = {0};
	for (i = 0; i < 24; i++)
	{
		if (m_struRoiDetectCond[i].dwRoiID != 0)
		{
			iCount++;
		}
	}

	LPNET_DVR_ROI_DETECT_COND pRoiDetectCond = NULL;
	LPNET_DVR_ROI_DETECT_CFG pRoiDetectCfg = NULL;

	LPNET_DVR_ROI_DETECT_COND pRoiDetectCondTemp = NULL;
	LPNET_DVR_ROI_DETECT_CFG pRoiDetectCfgTemp = NULL;

	pRoiDetectCond = new NET_DVR_ROI_DETECT_COND[iCount];
	if (NULL == pRoiDetectCond)
	{
		g_StringLanType(szLan,"申请内存失败","new memory failed");
		AfxMessageBox(szLan);
		return;
	}
	pRoiDetectCondTemp = pRoiDetectCond;

	pRoiDetectCfg = new NET_DVR_ROI_DETECT_CFG[iCount];
	if (NULL == pRoiDetectCfg)
	{
		g_StringLanType(szLan,"申请内存失败","new memory failed");
		AfxMessageBox(szLan);
		return;
	}
	pRoiDetectCfgTemp = pRoiDetectCfg;

	for (j=0; j<24; j++)
 	{
// 		for (i = 0; i< 24; i++)
// 		{
			if (m_struRoiDetectCond[j].dwRoiID != 0)
			{
				memcpy(pRoiDetectCondTemp, &m_struRoiDetectCond[j], sizeof(NET_DVR_ROI_DETECT_COND));
				memcpy(pRoiDetectCfgTemp, &m_struRoiDetectCfg[j], sizeof(NET_DVR_ROI_DETECT_CFG));

				pRoiDetectCondTemp++;
 				pRoiDetectCfgTemp++;
			}

/* 		}*/
	}

	DWORD *pStatus = new DWORD[iCount];
	memset(pStatus, 0, sizeof(DWORD)*iCount);
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_ROI_DETECT, iCount, pRoiDetectCond, iCount*sizeof(NET_DVR_ROI_DETECT_COND), \
		pStatus, pRoiDetectCfg, (iCount*(sizeof(NET_DVR_ROI_DETECT_CFG))));	
	if (bRet)
	{
		g_StringLanType(szLan,"设置Roi区域成功","Success to Set Roi detect Info");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Roi detect Info Success");
		AfxMessageBox(szLan);
	}
	else
	{        
		g_StringLanType(szLan,"设置Roi区域失败","Fail to Set Roi detect Info");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set Roi detect Info Fail");
		AfxMessageBox(szLan);
	}

	for (i=0; i<iCount; i++)
	{
		if (*pStatus != 0)
		{
			sprintf(szLan,"配置项:%d, 错误状态返回值:%d",i+1,*pStatus);
			AfxMessageBox(szLan);
		}
		sprintf(szLan,"配置项:%d, 正确状态返回值:%d",i+1,*pStatus);
		AfxMessageBox(szLan);
		pStatus++;
	}

	delete [] pRoiDetectCond;
	delete [] pRoiDetectCfg;
}

void CDlgRoiCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szLantemp[512] = {0};
	int i = 0;
	int j = 0;
	int iFixCount = 0;
	int iTrackCount = 0;

	memset(&m_struChannelGroup, 0, sizeof(m_struChannelGroup));

	m_struChannelGroup.dwSize = sizeof(m_struChannelGroup);
	m_struChannelGroup.dwGroup = 1;
	
	m_struChannelGroup.struMultiStreamCfg.dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
	m_struChannelGroup.struMultiStreamCfg.dwStreamType = m_comboStreamType.GetCurSel();
	m_struChannelGroup.struMultiStreamCfg.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	m_struChannelGroup.struMultiStreamCfg.struStreamInfo.dwChannel = m_lChannel;


	DWORD *pStatus = new DWORD;
	memset(pStatus, 0, sizeof(DWORD));

	memset(&m_struRoidetectNum, 0, sizeof(m_struRoidetectNum));

	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_ROI_DETECT_NUM, 1, &m_struChannelGroup, sizeof(m_struChannelGroup), \
		pStatus, &m_struRoidetectNum, sizeof(m_struRoidetectNum));
	if (!bRet && (*pStatus == 0))
	{
		g_StringLanType(szLan,"获取ROI检测区域ID数量","Fail to Get Roi Detect Num");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Fail to Get Roi Detect Num");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan,"获取ROI检测区域ID数量信息","Succ to Get Roi Detect Num");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Succ to Get Roi Detect Num");
		sprintf(szLantemp,"%s:\n\t \
FixRoiID1:%d    FixRoiID2:%d   FixRoiID3:%d   FixRoiID4:%d  \n\t \
FixRoiNameID1: %s    FixRoiNameID2: %s    FixRoiNameID3: %s   FixRoiNameID4: %s\n\t \
TrackRoiID1:%d   TrackRoiID2:%d   TrackRoiID3:%d   TrackRoiID4:%d\n\t ", szLan, \
			m_struRoidetectNum.dwRoiFixID[0], m_struRoidetectNum.dwRoiFixID[1], m_struRoidetectNum.dwRoiFixID[2], m_struRoidetectNum.dwRoiFixID[3], \
			m_struRoidetectNum.szFixRoiName[0], m_struRoidetectNum.szFixRoiName[1], m_struRoidetectNum.szFixRoiName[2], m_struRoidetectNum.szFixRoiName[3], \
			m_struRoidetectNum.dwRoiTrackID[0], m_struRoidetectNum.dwRoiTrackID[1], m_struRoidetectNum.dwRoiTrackID[2], m_struRoidetectNum.dwRoiTrackID[3]);
		AfxMessageBox(szLantemp);
	}

}

void CDlgRoiCfg::OnBtnGetRoiinfo()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	NET_DVR_ROI_DETECT_COND struRoiDetectCond = {0};
	NET_DVR_ROI_DETECT_CFG  struRoiDetectCfg = {0};

	struRoiDetectCond.dwSize = sizeof(struRoiDetectCond);
	struRoiDetectCond.dwRoiID = m_comboRoiID.GetCurSel()+1;
	int iRoiID = m_comboRoiID.GetCurSel();
	struRoiDetectCond.byRoiDetectTrackType = m_comboTrackType.GetCurSel();

	int itype = m_comboType.GetCurSel();
	if (!itype)
	{
		struRoiDetectCond.byRoiDetectType = DETECT_FIX_ROI;
	} 
	else
	{
		struRoiDetectCond.byRoiDetectType = DETECT_TRACK_ROI;
	}
	
	struRoiDetectCond.struMultiStreamCfg.dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
	struRoiDetectCond.struMultiStreamCfg.dwStreamType = m_comboStreamType.GetCurSel();
	struRoiDetectCond.struMultiStreamCfg.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	struRoiDetectCond.struMultiStreamCfg.struStreamInfo.dwChannel = m_lChannel;

	DWORD *pStatus = new DWORD;
	memset(pStatus, 0, sizeof(DWORD));
	
	memset(&struRoiDetectCfg, 0, sizeof(struRoiDetectCfg));
	
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_ROI_DETECT, 1, &struRoiDetectCond, sizeof(struRoiDetectCond), \
		pStatus, &struRoiDetectCfg, sizeof(struRoiDetectCfg));
	if (!bRet || (*pStatus != 0))
	{
		g_StringLanType(szLan,"获取ROI检测区域信息","Fail to Get Roi Detect Info");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Fail to Get Roi Detect Info");
		AfxMessageBox(szLan);
		return;
	}
	
	if (struRoiDetectCfg.byRoiDetectType == DETECT_FIX_ROI)
	{
		m_bFixRoi = TRUE;
		m_bTrackRoi = FALSE;
        char szFixRoiName[33] = { 0 };
        memcpy(szFixRoiName, struRoiDetectCfg.uRoiDetectInfo.strRoiFixRectCfg.szFixRoiName, 32);

		memcpy(&m_struRoiRect[iRoiID], &struRoiDetectCfg.uRoiDetectInfo.strRoiFixRectCfg.struRoiRect, sizeof(NET_VCA_RECT));
		m_comboStreamType.SetCurSel(struRoiDetectCfg.dwStreamType);
		m_bSingleEnable = struRoiDetectCfg.uRoiDetectInfo.strRoiFixRectCfg.byEnableFixRoi;
		m_comboImageQualityLevel.SetCurSel(struRoiDetectCfg.uRoiDetectInfo.strRoiFixRectCfg.byImageQualityLevel - 1);
		m_csRoiName.Format("%s", szFixRoiName);	
	}
	else
	{
		m_bFixRoi = FALSE;
		m_bTrackRoi = TRUE;

		m_comboImageQualityLevel.SetCurSel(struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byImageQualityLevel - 1);
		m_bSingleEnable = struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byEnableTrackRoi;
		m_comboStreamType.SetCurSel(struRoiDetectCfg.dwStreamType);	
		m_comboTrackType.SetCurSel(struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byModeType);
	}
 	UpdateData(FALSE);
}

void CDlgRoiCfg::OnSelchangeComboRoiid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iAssVal = m_dwRoiID;
	
	if (m_struRoiDetectCond[iAssVal].byRoiDetectType == DETECT_FIX_ROI)
	{
		m_bFixRoi = TRUE;
		m_bTrackRoi = FALSE;
		m_comboStreamType.SetCurSel(m_struRoiDetectCond[iAssVal].struMultiStreamCfg.dwStreamType);
        char szFixRoiName[33] = { 0 };
        memcpy(szFixRoiName, m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiFixRectCfg.szFixRoiName, 32);

		m_bSingleEnable = m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiFixRectCfg.byEnableFixRoi;
		m_comboImageQualityLevel.SetCurSel(m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiFixRectCfg.byImageQualityLevel - 1);
        m_csRoiName.Format("%s", szFixRoiName);
	} 
	else
	{
		m_bFixRoi = FALSE;
		m_bTrackRoi = TRUE;

		m_comboImageQualityLevel.SetCurSel(m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiTrackRectCfg.byImageQualityLevel);
		m_bSingleEnable = m_struRoiDetectCfg[iAssVal].uRoiDetectInfo.strRoiTrackRectCfg.byEnableTrackRoi;
		
		m_comboStreamType.SetCurSel(m_struRoiDetectCfg[iAssVal].dwStreamType);	
	}

	UpdateData(FALSE);
}

void CDlgRoiCfg::OnBtnGetall() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	int i = 0;
	int iCount = 8;	
	NET_DVR_ROI_DETECT_COND struRoiDetectCond[8];
	memset(&struRoiDetectCond, 0, sizeof(struRoiDetectCond));
	
	NET_DVR_ROI_DETECT_CFG struRoiDetectCfg[8];
	memset(&struRoiDetectCfg, 0, sizeof(NET_DVR_ROI_DETECT_CFG));
	
	NET_DVR_ROI_DETECT_CFG struRoiDetectCfgMod[8];
	memset(&struRoiDetectCfgMod, 0, sizeof(NET_DVR_ROI_DETECT_CFG));
	
	for (i = 0; i < iCount; i++)
	{
		struRoiDetectCond[i].dwSize = sizeof(NET_DVR_ROI_DETECT_COND);
		struRoiDetectCond[i].byRoiDetectType = 0;
		struRoiDetectCond[i].dwRoiID = i+1;
		struRoiDetectCond[i].struMultiStreamCfg.dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
		struRoiDetectCond[i].struMultiStreamCfg.dwStreamType = 0;
		struRoiDetectCond[i].struMultiStreamCfg.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
		struRoiDetectCond[i].struMultiStreamCfg.struStreamInfo.dwChannel = 1;
	}
	
	DWORD *pStatus = new DWORD[iCount];
	memset(pStatus, 0, sizeof(DWORD)*iCount);
	
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_ROI_DETECT, iCount, &struRoiDetectCond, \
		sizeof(NET_DVR_ROI_DETECT_COND)*iCount, pStatus, &struRoiDetectCfg, sizeof(NET_DVR_ROI_DETECT_CFG)*iCount);
	if (!bRet)
	{
		delete [] pStatus;
		DWORD iRet = NET_DVR_GetLastError();
		return;
	}
	
	for (i = 0; i < iCount; i++)
	{
		if (*pStatus != 0)
		{
			sprintf(szLan, "配置项:%d,返回状态:%d", i+1, *pStatus);
			AfxMessageBox(szLan);
		}
		sprintf(szLan, "配置项:%d,返回状态:%d", i+1, *pStatus);
		AfxMessageBox(szLan);
		pStatus++;
	}
}

void CDlgRoiCfg::OnBtnTrack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	int iCount = 1;
	NET_DVR_ROI_DETECT_COND struRoiDetectCond = {0};
	NET_DVR_ROI_DETECT_CFG struRoiDetectCfg = {0};

	struRoiDetectCond.dwSize = sizeof(NET_DVR_ROI_DETECT_COND);
	struRoiDetectCond.dwRoiID = m_comboRoiID.GetCurSel()+1;
	struRoiDetectCond.byRoiDetectType = DETECT_TRACK_ROI;
	struRoiDetectCond.struMultiStreamCfg.dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
	struRoiDetectCond.struMultiStreamCfg.dwStreamType = m_comboStreamType.GetCurSel();
	struRoiDetectCond.struMultiStreamCfg.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	struRoiDetectCond.struMultiStreamCfg.struStreamInfo.dwChannel = m_lChannel;
	struRoiDetectCond.byRoiDetectTrackType = m_comboTrackType.GetCurSel();

	struRoiDetectCfg.dwSize = sizeof(NET_DVR_ROI_DETECT_CFG);
	struRoiDetectCfg.byRoiDetectType = DETECT_TRACK_ROI;
	struRoiDetectCfg.dwStreamType = m_comboStreamType.GetCurSel();
	struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byEnableTrackRoi = m_bSingleEnable;
	struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byImageQualityLevel = m_comboImageQualityLevel.GetCurSel()+1;
	struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byModeType = m_comboTrackType.GetCurSel();

	DWORD *pStatus = new DWORD;
	memset(pStatus, 0, sizeof(DWORD));

	BOOL bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_ROI_DETECT, iCount, &struRoiDetectCond, iCount*sizeof(NET_DVR_ROI_DETECT_COND), \
		pStatus, &struRoiDetectCfg, (iCount*(sizeof(NET_DVR_ROI_DETECT_CFG))));	
	if (bRet)
	{
		g_StringLanType(szLan,"设置Roi跟踪模式成功","Success to Set Roi detect Info");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Roi detect Info Success");
		AfxMessageBox(szLan);
	}
	else
	{        
		g_StringLanType(szLan,"设置Roi跟踪模式失败","Fail to Set Roi detect Info");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set Roi detect Info Fail");
		AfxMessageBox(szLan);
	}
	
	for (int i=0; i<iCount; i++)
	{
		if (*pStatus != 0)
		{
			sprintf(szLan,"配置项:%d, 错误状态返回值:%d",i+1,*pStatus);
			AfxMessageBox(szLan);
		}
		sprintf(szLan,"配置项:%d, 正确状态返回值:%d",i+1,*pStatus);
		AfxMessageBox(szLan);
		pStatus++;
	}
}

void CDlgRoiCfg::OnBtnTrackGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	NET_DVR_ROI_DETECT_COND struRoiDetectCond = {0};
	NET_DVR_ROI_DETECT_CFG  struRoiDetectCfg = {0};

	struRoiDetectCond.dwSize = sizeof(struRoiDetectCond);
	struRoiDetectCond.dwRoiID = m_comboRoiID.GetCurSel()+1;
	int iRoiID = m_comboRoiID.GetCurSel();
	
	struRoiDetectCond.byRoiDetectType = DETECT_TRACK_ROI;
	
	struRoiDetectCond.struMultiStreamCfg.dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
	struRoiDetectCond.struMultiStreamCfg.dwStreamType = m_comboStreamType.GetCurSel();
	struRoiDetectCond.struMultiStreamCfg.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	struRoiDetectCond.struMultiStreamCfg.struStreamInfo.dwChannel = m_lChannel;
	struRoiDetectCond.byRoiDetectTrackType = m_comboTrackType.GetCurSel();
	
	DWORD *pStatus = new DWORD;
	memset(pStatus, 0, sizeof(DWORD));
	
	memset(&struRoiDetectCfg, 0, sizeof(struRoiDetectCfg));

	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_ROI_DETECT, 1, &struRoiDetectCond, sizeof(struRoiDetectCond), \
		pStatus, &struRoiDetectCfg, sizeof(struRoiDetectCfg));
	if (!bRet || (*pStatus != 0))
	{
		g_StringLanType(szLan,"获取跟踪ROI检测区域信息失败","Fail to Get Roi Track Detect Info");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Fail to Get Roi Track Detect Info");
		AfxMessageBox(szLan);
		return;
	}
		
	m_comboImageQualityLevel.SetCurSel(struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byImageQualityLevel - 1);
	m_bSingleEnable = struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byEnableTrackRoi;
	m_comboStreamType.SetCurSel(struRoiDetectCfg.dwStreamType);	
	m_comboTrackType.SetCurSel(struRoiDetectCfg.uRoiDetectInfo.strRoiTrackRectCfg.byModeType);

 	UpdateData(FALSE);
}

void CDlgRoiCfg::OnBtnTestCompressv30() 
{
	// TODO: Add your control notification handler code here
	CDlgCompressionV30 dlg;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();

}
