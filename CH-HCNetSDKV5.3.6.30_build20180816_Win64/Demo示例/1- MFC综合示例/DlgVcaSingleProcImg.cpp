// DlgVcaSingleProcImg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSingleProcImg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSingleProcImg dialog
DWORD g_dwFaceNum = 0;


CDlgVcaSingleProcImg::CDlgVcaSingleProcImg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSingleProcImg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaSingleProcImg)
	m_bDrawMaxFilter = FALSE;
	m_bDrawMiniFilter = FALSE;
	m_bChkFilterActive = FALSE;
	m_bChkDrawPolygon = FALSE;
	m_dwImageWidth = 0;
	m_bChkEnable = FALSE;
	m_dwImageHeight = 0;
	m_csFilePath = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel  = -1;
    memset(&m_rcWndRect, 0, sizeof(m_rcWndRect));
    m_bMouseMove = FALSE;
    m_bDrawRect = FALSE;
	m_dwPosNum = 0;
	memset(&m_struFDProcImgCfg, 0, sizeof(m_struFDProcImgCfg));
	memset(&m_struMaxFilter, 0, sizeof(m_struMaxFilter));
	memset(&m_struMiniFilter, 0, sizeof(m_struMiniFilter));
	memset(&m_struFacePicInfo[0], 0, MAX_HUMAN_PICTURE_NUM*sizeof(LOCAL_FACE_PICTURE_INFO));
	m_bCloseIn = FALSE;
    m_bMouseMovePolggon = FALSE;
    m_bNeedRedraw = FALSE;
	m_dwFileSize = 0;
	 m_bDetectSuccess = FALSE;
}


void CDlgVcaSingleProcImg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSingleProcImg)
	DDX_Control(pDX, IDC_COMBO_CHOOSE_PIC_NO, m_comboChoosePicNo);
	DDX_Control(pDX, IDC_COMBO_SENSITIVITY, m_comboSensitivity);
	DDX_Check(pDX, IDC_CHK_DRAW_MAXFILTER, m_bDrawMaxFilter);
	DDX_Check(pDX, IDC_CHK_DRAW_MINIFILTER, m_bDrawMiniFilter);
	DDX_Check(pDX, IDC_CHK_FILTER_ACTIVE, m_bChkFilterActive);
	DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bChkDrawPolygon);
	DDX_Text(pDX, IDC_EDIT_IMAGE_WIDTH, m_dwImageWidth);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	DDX_Text(pDX, IDC_EDIT_IMAGE_HEIGHT, m_dwImageHeight);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_csFilePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSingleProcImg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSingleProcImg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHK_DRAW_MAXFILTER, OnChkDrawMaxfilter)
	ON_BN_CLICKED(IDC_BUTTON_RECAPTURE, OnButtonRecapture)
	ON_BN_CLICKED(IDC_CHK_FILTER_ACTIVE, OnChkFilterActive)
	ON_BN_CLICKED(IDC_CHK_DRAW_MINIFILTER, OnChkDrawMinifilter)
	ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_SCAN, OnBtnScan)
	ON_BN_CLICKED(IDC_BTN_GET_PICMODEL, OnBtnGetPicmodel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSingleProcImg message handlers
BOOL CDlgVcaSingleProcImg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    char szLan[128] = {0};
    // TODO: Add extra initialization here
    GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&m_rcWndRect);
	m_bNeedRedraw = TRUE;//Redraw polygon
    m_bCloseIn = TRUE;//Polygon is closed or not
	m_comboSensitivity.SetCurSel(0);
	m_dwImageHeight = 1200;
	m_dwImageWidth = 1600;

	
//	StartRealPlay();
//     if (!CaptureBmp())
//     {
//         g_StringLanType(szLan, "抓图失败", "Fail to capture BMP");
//         AfxMessageBox(szLan);
//     }
    
//     HBITMAP hBmp = 0;
//     char ch[256] = {0};
//     Sleep(200);	
//     hBmp = m_pic.LoadPicture(m_chFilename);
//     if (hBmp == 0)
//     {
//         TRACE("LoadPicture fail\n");
//         return FALSE;
//     }
    
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

/******************************************
函数:	SetPdcCalibrationWnd
描述:	show pdc parameter
输入:	
输出:	
返回值: 
******************************************/
// BOOL CDlgVcaSingleProcImg::SetCalibrationWnd(NET_DVR_CALIBRATION_CFG struCalibration)
// {
//     DrawFilter();
//     return TRUE;
// }

void CDlgVcaSingleProcImg::DrawPolygon()
{
    CString str;
    CPen    *green_pen;
    green_pen = new CPen;
    green_pen ->CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
    
    CBrush brTmp;
    brTmp.CreateSolidBrush(RGB(255,255,255));   
    m_pDCRect = GetDlgItem(IDC_STATIC_PIC)->GetDC();
	    
    m_pDCRect->SetBkMode(TRANSPARENT);
    
    m_pDCRect->SelectObject(green_pen);
    
    CRect rectDraw;
    memset(&rectDraw, 0, sizeof(rectDraw));
	CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rcWnd);
    
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 255, 0);
    memcpy(&struPolygonParam.rcWnd, &rcWnd, sizeof(rcWnd));
    memcpy(&struPolygonParam.struVcaPolygon, &m_struFDProcImgCfg.struPolygon, sizeof(struPolygonParam.struVcaPolygon));
    struPolygonParam.bCloseIn = m_bCloseIn;
    struPolygonParam.bMouseMove = m_bMouseMove;
    
    CDrawFun::DrawVcaPolygon(m_pDCRect->GetSafeHdc(), &struPolygonParam);
	
    m_pDCRect->SelectObject(green_pen);
    GetDlgItem(IDC_STATIC_PIC)->ReleaseDC(m_pDCRect);
    delete green_pen;
}

void CDlgVcaSingleProcImg::DrawFilter()
{
    CString str;
    CPen    *green_pen;
    green_pen = new CPen;
    green_pen ->CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    
    GetDlgItem(IDC_STATIC_PIC)->Invalidate(FALSE);
    
    CBrush brTmp;
    brTmp.CreateSolidBrush(RGB(0,255,0));
    //Draw the bitmap
    CRect rect;
    GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&rect);
    CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC));
    m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
    
    m_pDCRect = GetDlgItem(IDC_STATIC_PIC)->GetDC();
    
    m_pDCRect->SetBkMode(TRANSPARENT);
    
    m_pDCRect->SelectObject(green_pen);
    
    CRect rectDraw;
    memset(&rectDraw, 0, sizeof(rectDraw));
    
	if (m_bDrawMaxFilter)
	{
		rectDraw.left = (int)(m_struMaxFilter.fX*m_rcWndRect.Width());
		rectDraw.top = (int)(m_struMaxFilter.fY*m_rcWndRect.Height());
		rectDraw.right = (int)((m_struMaxFilter.fX+m_struMaxFilter.fWidth)*m_rcWndRect.Width());
		rectDraw.bottom = (int)((m_struMaxFilter.fY+m_struMaxFilter.fHeight)*m_rcWndRect.Height());
	}

	if (m_bDrawMiniFilter)
	{
		rectDraw.left = (int)(m_struMiniFilter.fX*m_rcWndRect.Width());
		rectDraw.top = (int)(m_struMiniFilter.fY*m_rcWndRect.Height());
		rectDraw.right = (int)((m_struMiniFilter.fX+m_struMiniFilter.fWidth)*m_rcWndRect.Width());
		rectDraw.bottom = (int)((m_struMiniFilter.fY+m_struMiniFilter.fHeight)*m_rcWndRect.Height());
	}
    
    FrameRect(m_pDCRect->GetSafeHdc(), rectDraw, brTmp);
    m_pDCRect->SelectObject(green_pen);
    GetDlgItem(IDC_STATIC_PIC)->ReleaseDC(m_pDCRect);
    delete green_pen;
}

BOOL CDlgVcaSingleProcImg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
	CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rcWnd);
    GetCursorPos(&pt);
//    TRACE("pt %d %d \n",pt.x, pt.y);
    switch(pMsg->message) 
    {
    case WM_LBUTTONDOWN:
        if(PtInRect(&rcWnd,pt) && ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)))//按CTRL键 画图
        {
			if (m_bChkFilterActive)
			{
				if (m_bDrawMaxFilter)
				{
					m_struMaxFilter.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
					m_struMaxFilter.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
					DrawFilter();
					m_bMouseMove = TRUE;
				}
				if (m_bDrawMiniFilter)
				{
					m_struMiniFilter.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
					m_struMiniFilter.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
					DrawFilter();
					m_bMouseMove = TRUE;
				}
			}
			if (m_bChkDrawPolygon)
			{
//				TRACE("多边形\n");
				if(m_bNeedRedraw)
				{			
					if(m_bCloseIn)
					{
						m_dwPosNum = 0;
						m_struFDProcImgCfg.struPolygon.dwPointNum = m_dwPosNum;		
					}
					if(m_dwPosNum>9)
					{
						char szLan[128] = {0};
						g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 10");
						AfxMessageBox(szLan);
						return TRUE;
					}
					if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum-1].fX-0.01\
						&& (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum-1].fY-0.01)
					{
						char szLan[128] = {0};
						g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
						AfxMessageBox(szLan);
						return TRUE;
					}
					m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
					m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
					m_dwPosNum++;
					m_struFDProcImgCfg.struPolygon.dwPointNum = m_dwPosNum;	
					DrawPolygon();  
					m_bCloseIn = FALSE;
					m_bMouseMovePolggon = FALSE;
				}
			}
        }
        break;
    case WM_MOUSEMOVE:
        GetCursorPos(&pt);
        if(PtInRect(&rcWnd,pt) && ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)))//按CTRL键 画图
        {
			if (m_bChkFilterActive && m_bMouseMove)
			{
				if (m_bDrawMaxFilter)
				{
					m_struMaxFilter.fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() - m_struMaxFilter.fX;
					m_struMaxFilter.fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() - m_struMaxFilter.fY;
					DrawFilter();
				}
				if (m_bDrawMiniFilter)
				{
					m_struMiniFilter.fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() - m_struMiniFilter.fX;
					m_struMiniFilter.fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() - m_struMiniFilter.fY;
					DrawFilter();
				}
			}
			if (m_bChkDrawPolygon/* && m_bMouseMovePolggon*/)
			{
//				TRACE("多边形2\n");
//				if(m_dwPosNum > 9)
//				{
//					return TRUE;
//				}
//				if( m_bNeedRedraw && !m_bCloseIn)
//				{
					m_bMouseMovePolggon = TRUE;
//					m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
//					m_struFDProcImgCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
//					m_struFDProcImgCfg.struPolygon.dwPointNum = m_dwPosNum+1;	
//					DrawPolygon();
//				}
			}
        }
        break;
    case WM_LBUTTONUP:
		if(PtInRect(&rcWnd,pt) && m_bMouseMove && m_bChkFilterActive && ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)))//按CTRL键 画图
        {
			m_bMouseMove = FALSE;
		}
        break;
	case WM_RBUTTONDOWN:
        if(m_bChkDrawPolygon && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) 
            && PtInRect(&rcWnd,pt))
        {
			if(m_dwPosNum > 9)
			{
				return TRUE;
			}
			for(i=0; i<m_dwPosNum; i++)
			{
				if(m_struFDProcImgCfg.struPolygon.struPos[i].fX != m_struFDProcImgCfg.struPolygon.struPos[i+1].fX)
				{
					bXOneLine = FALSE;
					break;
				}
			}
			for(i=0; i<m_dwPosNum; i++)
			{
				if(m_struFDProcImgCfg.struPolygon.struPos[i].fY != m_struFDProcImgCfg.struPolygon.struPos[i+1].fY)
				{
					bYOneLine = FALSE;
					break;
				}
			}
			bOneLine = bXOneLine||bYOneLine;
			if(bOneLine)
			{
				char szlan[128] = {0};
				g_StringLanType(szlan, "所画点成一线，无法构成区域!","The points is on a line and can't create a rectangle!");
				AfxMessageBox(szlan);
				return TRUE;
			}
			if( m_bNeedRedraw && !m_bCloseIn)
			{
				if(m_bMouseMovePolggon)
				{
					m_struFDProcImgCfg.struPolygon.dwPointNum--;
					m_struFDProcImgCfg.struPolygon.struPos[m_struFDProcImgCfg.struPolygon.dwPointNum].fX = 0;
					m_struFDProcImgCfg.struPolygon.struPos[m_struFDProcImgCfg.struPolygon.dwPointNum].fY = 0;
					DrawPolygon();
					m_bMouseMovePolggon = FALSE;
				}
				m_bCloseIn = TRUE;
			}
		}
        break;
    }

	return CDialog::PreTranslateMessage(pMsg);
}

/*********************************************************
Function:	CaptureJpeg
Desc:		Capture Jpege
Input:	none
Output:	none
Return:	BOOL
**********************************************************/
BOOL CDlgVcaSingleProcImg::CaptureBmp()
{
    UpdateData(TRUE);
    CString sTemp;
    CTime time = CTime::GetCurrentTime();
    
    sTemp.Format("%s\\", g_struLocalParam.chPictureSavePath);		
    if (GetFileAttributes(sTemp) != FILE_ATTRIBUTE_DIRECTORY)
    {
        CreateDirectory(sTemp, NULL);
    }
    
    NET_DVR_JPEGPARA struJpegPara;
    memset(&struJpegPara, 0, sizeof(NET_DVR_JPEGPARA));
    struJpegPara.wPicQuality = (WORD)g_struDeviceInfo[m_iDevIndex].pStruChanInfo[m_lChannel].iPicQuality;
    struJpegPara.wPicSize = (WORD)g_struDeviceInfo[m_iDevIndex].pStruChanInfo[m_lChannel].iPicResolution;

    sprintf(m_chFilename, "%s\\JPEG_%02d_%4d%02d%02d_%02d%02d%02d_%d.bmp", \
        g_struLocalParam.chPictureSavePath, m_lChannel,	\
        time.GetYear(), time.GetMonth(), time.GetDay(), \
        time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());
    
    if (NET_DVR_CapturePicture(m_lPlayHandle, m_chFilename))
    {
        CString sTemp;	
        sTemp.Format("Succ to capture bmp%s!",m_chFilename);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CapturePicture file[%s]", m_chFilename);
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CapturePicture");
        AfxMessageBox("Fail to captur bmp!");
        return FALSE;
    }
    return TRUE;
}

void CDlgVcaSingleProcImg::OnButtonRecapture() 
{
    // TODO: Add your control notification handler code here
    if (!CaptureBmp())
    {
        return;
    }
    Sleep(400);
    if(!m_pic.LoadPicture(m_chFilename))
    {
        AfxMessageBox("Fail to reload picture");
        return;
    }
    
    GetDlgItem(IDC_STATIC_PIC)->Invalidate(FALSE);
    
    //Draw the bitmap
    CRect rect;
    GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&rect);
    CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC));
    m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
    
//    SetCalibrationWnd(m_struCalibrationCfg);
}


long CDlgVcaSingleProcImg::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_lChannel;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PIC)->GetSafeHwnd();;
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE);  
    if (m_lPlayHandle == -1) 
    {
        AfxMessageBox("Fail to preview");
        return m_lPlayHandle;
    }
    return m_lPlayHandle;
}

BOOL CDlgVcaSingleProcImg::StopRealPlay()
{
    BOOL bRet;
    if (m_lPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
        if (!bRet)
        {
            AfxMessageBox("Fail to stop preview");
        }
    }
    return bRet;
}

void CDlgVcaSingleProcImg::PostNcDestroy() 
{
//	StopRealPlay();
    
	CDialog::PostNcDestroy();
}

void CDlgVcaSingleProcImg::OnPaint() 
{
//    TRACE("onpaint");
    CPaintDC dc(this); // device context for painting
    
    CRect rect;
    GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&rect);
    CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC));
    m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
    
    DrawFilter();
	DrawPolygon();
    // Do not call CDialog::OnPaint() for painting messages
}

void CDlgVcaSingleProcImg::OnRButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    memset(&m_struMaxFilter, 0, sizeof(m_struMaxFilter));
	memset(&m_struMiniFilter, 0, sizeof(m_struMiniFilter));
    DrawFilter();
    CDialog::OnRButtonDown(nFlags, point);
}

void CDlgVcaSingleProcImg::OnChkDrawMaxfilter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bMouseMove = FALSE;
	if (m_bDrawMaxFilter)
	{
		m_bDrawMiniFilter = FALSE;
		m_bChkDrawPolygon = FALSE;
	}
	OnPaint();
	UpdateData(FALSE);
}

void CDlgVcaSingleProcImg::OnChkFilterActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bMouseMove = FALSE;
	m_bChkDrawPolygon = FALSE;
}

void CDlgVcaSingleProcImg::OnChkDrawMinifilter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bMouseMove = FALSE;
	if (m_bDrawMiniFilter)
	{
		m_bDrawMaxFilter = FALSE;
		m_bChkDrawPolygon = FALSE;
	}
	OnPaint();
	UpdateData(FALSE);
}

void CDlgVcaSingleProcImg::OnChkDrawPolygon() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	BOOL bCheck = m_bChkDrawPolygon;
// 	int i = 0;
	if (!m_bChkDrawPolygon)
	{
		m_dwPosNum = 0;
		memset(&m_struFDProcImgCfg.struPolygon, 0, sizeof(NET_VCA_POLYGON));
		DrawPolygon();
	}
}

void CDlgVcaSingleProcImg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	CFile file;
	char *sFileBuf;
	BOOL bRet = TRUE;
	DWORD dwFileSize = 0;
	sFileBuf = NULL;
	if (!file.Open(m_chFilename, CFile::shareDenyNone))
	{
		file.Close();
		return;
	}
	file.Seek(0, CFile::begin);
	dwFileSize = (DWORD)(file.GetLength());
	if (dwFileSize == 0)
	{
		file.Close();
		return;
	}
    m_dwFileSize = dwFileSize;
	
	sFileBuf = new char[dwFileSize + 4];
	if (sFileBuf == NULL)
	{
		return;
	}
	file.Read(sFileBuf, dwFileSize);
	file.Close();

	m_struFDProcImgCfg.struFDImage.pImage = new BYTE[m_dwFileSize];
	if (m_struFDProcImgCfg.struFDImage.pImage == NULL)
	{
		return;
	}
	memset(m_struFDProcImgCfg.struFDImage.pImage, 0, m_dwFileSize);
	memcpy(m_struFDProcImgCfg.struFDImage.pImage, sFileBuf, m_dwFileSize);
	m_struFDProcImgCfg.byEnable = m_bChkEnable;
	m_struFDProcImgCfg.bySensitivity = m_comboSensitivity.GetCurSel();
	m_struFDProcImgCfg.struFDImage.dwHeight = m_dwImageHeight;
	m_struFDProcImgCfg.struFDImage.dwWidth = m_dwImageWidth;
	m_struFDProcImgCfg.struFDImage.dwImageLen = m_dwFileSize;
	m_struFDProcImgCfg.struSizeFilter.byActive = m_bChkFilterActive;
	memcpy(&m_struFDProcImgCfg.struSizeFilter.struMaxRect, &m_struMaxFilter, sizeof(m_struMaxFilter));
	memcpy(&m_struFDProcImgCfg.struSizeFilter.struMiniRect, &m_struMiniFilter, sizeof(m_struMiniFilter));
	m_struFDProcImgCfg.dwSize = sizeof(m_struFDProcImgCfg);

	NET_VCA_FD_PROCIMG_RESULT_V50 struRecvBuf = {0};
	for (i=0; i<MAX_TARGET_NUM; i++)
	{
		m_pStruRecvBuf->struProcImg[i].pImage = new BYTE[10 * 1024];
		memset(m_pStruRecvBuf->struProcImg[i].pImage, 0, 10*1024);
	}
	m_bDetectSuccess = NET_DVR_DetectImage_V50(m_lServerID, &m_struFDProcImgCfg, &struRecvBuf);
	if (m_bDetectSuccess)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DetectImage_V50");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DetectImage_V50");
		return;
	}

	if (m_pStruRecvBuf->dwSubImageNum > 0)
	{
		g_dwFaceNum = 0;
		for (i=0; i<m_pStruRecvBuf->dwSubImageNum; i++)
		{
			if (m_pStruRecvBuf->struProcImg[i].dwImageLen > 0 && m_pStruRecvBuf->struProcImg[i].pImage != NULL)
			{			
				char cFilename[256] = {0};
				HANDLE hFile;
				DWORD dwReturn;

				SYSTEMTIME t;
				GetLocalTime(&t);
				char chTime[128];
				sprintf(chTime,"Face_%d_%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",i+1,t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);

				sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
				if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
				{
					CreateDirectory(cFilename, NULL);
				}

				sprintf(cFilename, "%s\\PricImg[%s].jpg",cFilename, chTime);
				hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					return;
				}
				WriteFile(hFile, m_pStruRecvBuf->struProcImg[i].pImage, m_pStruRecvBuf->struProcImg[i].dwImageLen, &dwReturn, NULL);
				CloseHandle(hFile);
				hFile = NULL;
			}

			if (g_dwFaceNum < MAX_HUMAN_PICTURE_NUM)
			{
				m_struFacePicInfo[g_dwFaceNum].dwImageID = m_pStruRecvBuf->dwImageId;
				m_struFacePicInfo[g_dwFaceNum].dwFaceScore = m_pStruRecvBuf->struProcImg[i].dwFaceScore;
				memcpy(&m_struFacePicInfo[g_dwFaceNum].struVcaRect, &m_pStruRecvBuf->struProcImg[i].struVcaRect, sizeof(NET_VCA_RECT));
				g_struFacePic[g_dwFaceNum].dwImageID = m_pStruRecvBuf->dwImageId;
				g_struFacePic[g_dwFaceNum].dwFaceScore = m_pStruRecvBuf->struProcImg[i].dwFaceScore;
				memcpy(&g_struFacePic[g_dwFaceNum].struVcaRect, &m_pStruRecvBuf->struProcImg[i].struVcaRect, sizeof(NET_VCA_RECT));
				g_dwFaceNum++;
			}
		}        
	}

	if (m_struFDProcImgCfg.struFDImage.pImage != NULL)
	{
		delete []m_struFDProcImgCfg.struFDImage.pImage;
		m_struFDProcImgCfg.struFDImage.pImage = NULL;
	}

	for (i=0; i<MAX_TARGET_NUM; i++)
	{
		if (m_pStruRecvBuf->struProcImg[i].pImage != NULL)
		{
			delete []m_pStruRecvBuf->struProcImg[i].pImage;
			m_pStruRecvBuf->struProcImg[i].pImage = NULL;
		}
	}
	if (sFileBuf != NULL)
	{
		delete []sFileBuf;
		sFileBuf = NULL;
	}
}

void CDlgVcaSingleProcImg::OnBtnScan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
		
	char szLan[128] = {0};
    OPENFILENAME ofn = {0};
	CRect struRect;
	
    memset(m_chFilename, 0, MAX_PATH);
    
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = this->GetSafeHwnd();
    ofn.lpstrFilter = "All Files\0*.*\0\0";
    ofn.lpstrFile   = m_chFilename;
    ofn.nMaxFile    = MAX_PATH;
    ofn.Flags       = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
    
    if (GetOpenFileName(&ofn))
    {
        m_csFilePath.Format("%s", m_chFilename);
    }
	
	if (strlen(m_chFilename) == 0)
	{
		return;
	}

	if(!m_pic.LoadPicture(m_chFilename))
	{
		AfxMessageBox("Fail to reload picture");
		return;
	}

	GetDlgItem(IDC_STATIC_PIC)->Invalidate(FALSE);
	GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&struRect);
	CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC));
    m_pic.DrawPicture(dc2.m_hDC, struRect.left, struRect.top, struRect.Width(), struRect.Height());
	UpdateData(FALSE);
}

void CDlgVcaSingleProcImg::OnBtnGetPicmodel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iFacePicNo = m_comboChoosePicNo.GetCurSel();
	NET_VCA_PICMODEL_RESULT struRecvBuf = {0};
	struRecvBuf.pImage = new BYTE[10 * 1024];
	if (struRecvBuf.pImage == NULL)
	{
		return;
	}
	memset(struRecvBuf.pImage, 0, 10*1024);
	struRecvBuf.pModel = new BYTE[70 * 1024];
	if (struRecvBuf.pModel == NULL)
	{
		return;
	}
	memset(struRecvBuf.pModel, 0, 70*1024);
	NET_VCA_REGISTER_PIC struInBuf = {0};
	struInBuf.dwImageID = m_struFacePicInfo[iFacePicNo].dwImageID;
	struInBuf.dwFaceScore = m_struFacePicInfo[iFacePicNo].dwFaceScore;
	memcpy(&struInBuf.struVcaRect, &m_struFacePicInfo[iFacePicNo].struVcaRect, sizeof(NET_VCA_RECT));
	if (NET_DVR_GetPictureModel(m_lServerID, &struInBuf, &struRecvBuf))
	{
//		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPictureModel piclen=[%d] modellen[]", struRecvBuf.dwImageLen/*, struRecvBuf.dwModelLen*/);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindBackgroundPic");
		delete []struRecvBuf.pImage;
		struRecvBuf.pImage = NULL;
		delete []struRecvBuf.pModel;
		struRecvBuf.pModel = NULL;
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPictureModel");
		return;
	}

	g_struFaceModel[iFacePicNo].dwFacePicLen = struRecvBuf.dwImageLen;
	g_struFaceModel[iFacePicNo].dwFaceModelLen = struRecvBuf.dwModelLen;
	memcpy(g_struFaceModel[iFacePicNo].byFacePic, struRecvBuf.pImage, struRecvBuf.dwImageLen);
	memcpy(g_struFaceModel[iFacePicNo].byModelData, struRecvBuf.pModel, struRecvBuf.dwModelLen);

	if (struRecvBuf.pImage!= NULL)
	{
		delete []struRecvBuf.pImage;
	    struRecvBuf.pImage = NULL;
	}
	
	if (struRecvBuf.pModel!= NULL)
	{
		delete []struRecvBuf.pModel;
        struRecvBuf.pModel = NULL;
	}
	
}
