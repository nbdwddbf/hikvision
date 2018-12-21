// DlgPdcCalibration.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPdcCalibration.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcCalibration dialog

#define  USERDEFINE_VALUE  0.005

CDlgPdcCalibration::CDlgPdcCalibration(CWnd* pParent /*=NULL*/)
: CDialog(CDlgPdcCalibration::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgPdcCalibration)
    m_bVerifyCalibration = FALSE;
	m_bDraw = FALSE;
	m_bEnable = FALSE;
	m_bLine = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel  = -1;
    memset(&m_struCalibrationCfg, 0, sizeof(m_struCalibrationCfg));
    memset(&m_struPdcCalibration, 0, sizeof(m_struPdcCalibration));
    memset(&m_struPdcLineCalib, 0, sizeof(m_struPdcLineCalib));
    memset(&m_rcWndRect, 0, sizeof(m_rcWndRect));
    m_bMouseMove = FALSE;
    m_bDrawRect = FALSE;
    m_iCalibrationType = 0;
}

void CDlgPdcCalibration::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPdcCalibration)
    DDX_Check(pDX, IDC_CHK_VERIFY_CALIBRTION, m_bVerifyCalibration);
	DDX_Check(pDX, IDC_CHK_DRAW, m_bDraw);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHK_LINE, m_bLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPdcCalibration, CDialog)
//{{AFX_MSG_MAP(CDlgPdcCalibration)
ON_BN_CLICKED(IDC_BTN_SET_CALIBRATION, OnBtnSetCalibration)
ON_BN_CLICKED(IDC_BUTTON_RECAPTURE, OnButtonRecapture)
ON_WM_PAINT()
ON_BN_CLICKED(IDC_CHK_VERIFY_CALIBRTION, OnChkVerifyCalibrtion)
ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHK_DRAW, OnChkDraw)
    ON_BN_CLICKED(IDC_CHK_LINE, OnChkLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcCalibration message handlers

BOOL CDlgPdcCalibration::OnInitDialog() 
{
    CDialog::OnInitDialog();
    UpdateData(TRUE);
    char szLan[128] = {0};
    // TODO: Add extra initialization here
    GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&m_rcWndRect);
    if (!CaptureBmp())
    {
        g_StringLanType(szLan, "抓图失败", "Fail to capture BMP");
        AfxMessageBox(szLan);
    }
    
    HBITMAP hBmp = 0;
    char ch[256] = {0};
    Sleep(200);	
    hBmp = m_pic.LoadPicture(m_chFilename);
    if (hBmp == 0)
    {
        TRACE("LoadPicture fail\n");
        return FALSE;
    }
    
    
    DWORD dwReturn;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CALIBRATION, m_lChannel, &m_struCalibrationCfg, sizeof(m_struCalibrationCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALIBRATION m_lChannel[%d] ",m_lChannel);
        g_StringLanType(szLan, "获取标定校验失败", "Fail to get calibration");
        AfxMessageBox(szLan);
        //return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALIBRATION m_lChannel[%d] ",m_lChannel);
    }
    
	m_bEnable = m_struCalibrationCfg.byEnable;
    m_iCalibrationType = m_struCalibrationCfg.byCalibrationType;
    if (PDC_LINE_CALIBRATE == m_iCalibrationType)
    {
        memcpy(&m_struPdcLineCalib, &m_struCalibrationCfg.uCalibrateParam.struPDCLineCalibration, sizeof(m_struPdcLineCalib));
        m_bLine = TRUE;
        PdcLineCalibration();
    }
    else
    {
        memcpy(&m_struPdcCalibration, &m_struCalibrationCfg.uCalibrateParam.struPDCCalibration, sizeof(m_struCalibrationCfg));   
        m_bDraw = TRUE;
    }
    
    UpdateData(FALSE);
    OnChkLine();
    OnChkDraw();
    SetCalibrationWnd(m_struCalibrationCfg);

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
BOOL CDlgPdcCalibration::SetCalibrationWnd(NET_DVR_CALIBRATION_CFG struCalibration)
{
    if (PDC_LINE_CALIBRATE == m_iCalibrationType)
    {
       // PdcLineCalibration();
    } 
    else
    {
        DrawCalibration();
    }
  
    return TRUE;
}

void CDlgPdcCalibration::PdcLineCalibration()
{
    CString str;
    CPen    *green_pen;
    green_pen = new CPen;
    green_pen ->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

    GetDlgItem(IDC_STATIC_PIC)->Invalidate(FALSE);

    CBrush brTmp;
    brTmp.CreateSolidBrush(RGB(255, 0, 0));
    //Draw the bitmap
    CRect rect;
    GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&rect);
    CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC));

    m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());

    m_pDCRect = GetDlgItem(IDC_STATIC_PIC)->GetDC();
    
    m_pDCRect->SetBkMode(TRANSPARENT);
    
    m_pDCRect->SelectObject(green_pen);


    CPoint cStartPointTemp;
         
    cStartPointTemp.x = m_struPdcLineCalib.struCalibrationLine.struStart.fX * rect.Width() + USERDEFINE_VALUE;
    cStartPointTemp.y = m_struPdcLineCalib.struCalibrationLine.struStart.fY * rect.Height() + USERDEFINE_VALUE;
         
    CPoint cEndPointTemp;
      
    cEndPointTemp.x = m_struPdcLineCalib.struCalibrationLine.struEnd.fX * rect.Width() + USERDEFINE_VALUE;
    cEndPointTemp.y = m_struPdcLineCalib.struCalibrationLine.struEnd.fY * rect.Height() + USERDEFINE_VALUE;

    MoveToEx(m_pDCRect->GetSafeHdc(), cStartPointTemp.x, cStartPointTemp.y, NULL);
    LineTo(m_pDCRect->GetSafeHdc(), cEndPointTemp.x, cEndPointTemp.y);

    m_pDCRect->SelectObject(green_pen);
    GetDlgItem(IDC_STATIC_PIC)->ReleaseDC(m_pDCRect);
    delete green_pen;

//     CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC));
//     HDC hDc = dc2.m_hDC;
//     SetBkMode(hDc, TRANSPARENT);
//     SetTextColor(hDc, RGB(194, 235, 146));

//     DRAW_LINE_PARAM  struLaneLineParam ;
//     struLaneLineParam.color = RGB(255,0,0);
//     NET_ITC_LINE struLaneLine = {0};
//     memcpy(&struLaneLine.struLine, &m_struPdcCalibration.struRectList, sizeof(NET_VCA_LINE));
//     struLaneLine.struLine = m_struPdcLineCalib.struCalibrationLine;
//     memcpy(&struLaneLineParam.rcWnd, &m_rcWndRect, sizeof(m_rcWndRect));
//     memcpy(&struLaneLineParam.struVcaLine, &struLaneLine.struLine, sizeof(struLaneLine.struLine));
    
    //CDrawFun::DrawLine(hDc, &struLaneLineParam);

//     SetBkMode(hDc, TRANSPARENT);
//     CPen   DrawPen;	
//     
//     DrawPen.CreatePen(PS_SOLID, 2, lpDrawLine->color);
//     
//     HGDIOBJ hOldPen = SelectObject(hDc, DrawPen);
//     
//     
//     CPoint cStartPointTemp;
//     
//     cStartPointTemp.x = lpDrawLine->struVcaLine.struStart.fX * lpDrawLine->rcWnd.Width() + USERDEFINE_VALUE;
//     cStartPointTemp.y = lpDrawLine->struVcaLine.struStart.fY * lpDrawLine->rcWnd.Height() + USERDEFINE_VALUE;
//     
//     CPoint cEndPointTemp;
//     
//     cEndPointTemp.x = lpDrawLine->struVcaLine.struEnd.fX * lpDrawLine->rcWnd.Width() + USERDEFINE_VALUE;
//     cEndPointTemp.y = lpDrawLine->struVcaLine.struEnd.fY * lpDrawLine->rcWnd.Height() + USERDEFINE_VALUE;
//     
//     MoveToEx(hDc, cStartPointTemp.x, cStartPointTemp.y, NULL);
//     LineTo(hDc, cEndPointTemp.x, cEndPointTemp.y);
//     
//     SelectObject(hDc, hOldPen);
//    DrawPen.DeleteObject();
}

void CDlgPdcCalibration::DrawCalibration()
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
    
    for (int iRectIndex = 0; iRectIndex < m_struPdcCalibration.struRectList.byRectNum; iRectIndex++)
    {
        rectDraw.left = (int)(m_struPdcCalibration.struRectList.struVcaRect[iRectIndex].fX*m_rcWndRect.Width());
        rectDraw.top = (int)(m_struPdcCalibration.struRectList.struVcaRect[iRectIndex].fY*m_rcWndRect.Height());
        rectDraw.right = (int)((m_struPdcCalibration.struRectList.struVcaRect[iRectIndex].fX+m_struPdcCalibration.struRectList.struVcaRect[iRectIndex].fWidth)*m_rcWndRect.Width());
        rectDraw.bottom = (int)((m_struPdcCalibration.struRectList.struVcaRect[iRectIndex].fY+m_struPdcCalibration.struRectList.struVcaRect[iRectIndex].fHeight)*m_rcWndRect.Height());
        FrameRect(m_pDCRect->GetSafeHdc(), rectDraw, brTmp);
    }
    m_pDCRect->SelectObject(green_pen);
    GetDlgItem(IDC_STATIC_PIC)->ReleaseDC(m_pDCRect);
    delete green_pen;
}

void CDlgPdcCalibration::OnBtnSetCalibration() 
{
    char szLan[128] = {0};
    SetCalibration();
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CALIBRATION, m_lChannel, &m_struCalibrationCfg, sizeof(m_struCalibrationCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CALIBRATION m_lChannel[%d] code[%d]",m_lChannel, NET_DVR_GetLastError());
        g_StringLanType(szLan, "设置标定失败", "Fail to set calibration");
        AfxMessageBox(szLan);
    }
    else
    {
       g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CALIBRATION m_lChannel[%d] ",m_lChannel);
       g_StringLanType(szLan, "设置标定成功", "Succ to set calibration");
       AfxMessageBox(szLan);
    }
}

BOOL CDlgPdcCalibration::SetCalibration()
{
    UpdateData(TRUE);    
    
    m_struCalibrationCfg.byEnable = m_bEnable;

    if (PDC_LINE_CALIBRATE == m_iCalibrationType)
    {
        m_struCalibrationCfg.byCalibrationType = PDC_LINE_CALIBRATE; 
        memcpy(&m_struCalibrationCfg.uCalibrateParam.struPDCLineCalibration, &m_struPdcLineCalib, sizeof(m_struPdcLineCalib));
    } 
    else
    {
        m_struCalibrationCfg.byCalibrationType = PDC_CALIBRATE; 
        memcpy(&m_struCalibrationCfg.uCalibrateParam.struPDCCalibration, &m_struPdcCalibration, sizeof(m_struPdcCalibration));
    }
    return TRUE;
}

BOOL CDlgPdcCalibration::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
    CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rcWnd);
    GetCursorPos(&pt);
    TRACE("pt %d %d \n",pt.x, pt.y);

    if (PDC_LINE_CALIBRATE == m_iCalibrationType)
    {
        switch(pMsg->message) 
        {
        case WM_LBUTTONDOWN:
            if (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)
            {
                if (PtInRect(&rcWnd,pt))
                {
                    if(!m_bMouseMove)
                    {
                        m_struPdcLineCalib.struCalibrationLine.struStart.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcLineCalib.struCalibrationLine.struStart.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();		
                        m_struPdcLineCalib.struCalibrationLine.struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcLineCalib.struCalibrationLine.struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_bMouseMove = TRUE;
                    }
                    else
                    {
                        if ((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcLineCalib.struCalibrationLine.struStart.fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcLineCalib.struCalibrationLine.struStart.fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcLineCalib.struCalibrationLine.struStart.fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcLineCalib.struCalibrationLine.struStart.fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_struPdcLineCalib.struCalibrationLine.struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcLineCalib.struCalibrationLine.struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = FALSE;
                    }
                    PdcLineCalibration();
                }          
            }
            break;
        case WM_MOUSEMOVE:
            GetCursorPos(&pt);
            if (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_bMouseMove)
                    {
                        m_struPdcLineCalib.struCalibrationLine.struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcLineCalib.struCalibrationLine.struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();	
                        PdcLineCalibration();
                    }
                }         
            } 
            break;
        case WM_LBUTTONUP:
            m_bMouseMove = FALSE;
            break;
        }
    }
    else
    {
        switch(pMsg->message) 
        {
        case WM_LBUTTONDOWN:
            if(PtInRect(&rcWnd,pt) && ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)))//按CTRL键 画图
            {
                if (m_bVerifyCalibration)
                {
                    m_struVerifyPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                    m_struVerifyPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                    
                    NET_DVR_VerifyCalibration(m_lServerID, NET_DVR_PDC_VERIFY_CALIBRATION, m_lChannel, &m_struVerifyPoint, sizeof(m_struVerifyPoint), &m_struVerifyRect, sizeof(m_struVerifyRect));
                    DrawVerifyCalibration();
                }
                else if (m_bDraw)
                {
                    m_struPdcCalibration.struRectList.struVcaRect[m_struPdcCalibration.struRectList.byRectNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                    m_struPdcCalibration.struRectList.struVcaRect[m_struPdcCalibration.struRectList.byRectNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                    m_struPdcCalibration.struRectList.byRectNum++;
                    DrawCalibration();
                    m_bMouseMove = TRUE;
                }
            }
            break;
        case WM_MOUSEMOVE:
            GetCursorPos(&pt);
            if(PtInRect(&rcWnd,pt) && m_bMouseMove && m_bDraw && ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)))//按CTRL键 画图
            {
                int temp = m_struPdcCalibration.struRectList.byRectNum -1;
                
                m_struPdcCalibration.struRectList.struVcaRect[temp].fWidth = \
                    (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() - m_struPdcCalibration.struRectList.struVcaRect[temp].fX;
                m_struPdcCalibration.struRectList.struVcaRect[temp].fHeight = \
                    (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() - m_struPdcCalibration.struRectList.struVcaRect[temp].fY;
                m_bDrawRect = TRUE;
                DrawCalibration();
            }
            
            break;
        case WM_LBUTTONUP:
            if (m_bDrawRect == TRUE)
            {
                /*m_struPdcCalibration.struRectList.byRectNum++*/;
                m_bDrawRect = FALSE;
            }
            m_bMouseMove = FALSE;
            break;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPdcCalibration::DrawVerifyCalibration()
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
    
    CRect rectVerify;
    memset(&rectVerify, 0, sizeof(rectVerify));
    rectVerify.left = (int)(m_struVerifyRect.fX*m_rcWndRect.Width());
    rectVerify.top = (int)(m_struVerifyRect.fY*m_rcWndRect.Height());
    rectVerify.right = (int)((m_struVerifyRect.fX+m_struVerifyRect.fWidth)*m_rcWndRect.Width());
    rectVerify.bottom = (int)((m_struVerifyRect.fY+m_struVerifyRect.fHeight)*m_rcWndRect.Height());
    
    FrameRect(m_pDCRect->GetSafeHdc(), rectVerify,brTmp );
    
    m_pDCRect->SelectObject(green_pen);
    GetDlgItem(IDC_STATIC_PIC)->ReleaseDC(m_pDCRect);
    delete green_pen;
    
}

/*********************************************************
Function:	CaptureJpeg
Desc:		Capture Jpege
Input:	none
Output:	none
Return:	BOOL
**********************************************************/
BOOL CDlgPdcCalibration::CaptureBmp()
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

    sprintf(m_chFilename, "%s\\JPEG_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.bmp", \
        g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIPInFileName, m_lChannel,	\
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

void CDlgPdcCalibration::OnButtonRecapture() 
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
    
    SetCalibrationWnd(m_struCalibrationCfg);
}


long CDlgPdcCalibration::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_lChannel;
    struClientInfo.hPlayWnd = NULL;
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE);  
    if (m_lPlayHandle == -1) 
    {
        AfxMessageBox("Fail to preview");
        return m_lPlayHandle;
    }
    return m_lPlayHandle;
}

BOOL CDlgPdcCalibration::StopRealPlay()
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

void CDlgPdcCalibration::OnPaint() 
{
    TRACE("onpaint");
    CPaintDC dc(this); // device context for painting
    
    CRect rect;
    GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&rect);
    CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC));
    m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
    
    if (PDC_LINE_CALIBRATE == m_iCalibrationType)
    {
         PdcLineCalibration();
    } 
    else
    {
        DrawCalibration();
    }

    if (m_bVerifyCalibration)
    {
        
    }
    // Do not call CDialog::OnPaint() for painting messages
}

void CDlgPdcCalibration::OnChkVerifyCalibrtion() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    GetDlgItem(IDC_CHK_DRAW)->EnableWindow(!m_bVerifyCalibration);
    OnPaint();
}

void CDlgPdcCalibration::OnRButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    memset(&m_struPdcCalibration, 0, sizeof(m_struPdcCalibration));
    DrawCalibration();
    CDialog::OnRButtonDown(nFlags, point);
}

void CDlgPdcCalibration::OnChkDraw() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    if (m_bDraw)
    {
        m_bLine = FALSE;
        m_iCalibrationType = PDC_CALIBRATE; 
    }
    UpdateData(FALSE);
}

void CDlgPdcCalibration::OnChkLine()
{
    UpdateData(TRUE);
    if (m_bLine)
    {
        m_bDraw = FALSE;
        m_iCalibrationType = PDC_LINE_CALIBRATE; 
    }
    UpdateData(FALSE);
}
