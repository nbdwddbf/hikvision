// DlgVcaBehaviorCalibrate.cpp : implementation file
//
#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaBehaviorCalibrate.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCalibrate dialog
#define  USERDEFINE_VALUE  0.005

CDlgVcaBehaviorCalibrate::CDlgVcaBehaviorCalibrate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaBehaviorCalibrate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaBehaviorCalibrate)
	m_fCameraHeight = 0.0f;
	m_fCameraAngle = 0.0f;
	m_fCameraHorizon = 0.0f;
	m_bAngle = FALSE;
	m_bHeight = FALSE;
	m_bHorizon = FALSE;
	m_bEanbleCal = FALSE;
	m_fHeight = 0.0f;
	m_fLength = 0.0f;
	//}}AFX_DATA_INIT
	m_lServerID	= -1;
	m_iDevIndex	= -1;
	m_lChannel	= -1;
    memset(&m_chFilename[0], 0, sizeof(m_chFilename));
    memset(&m_struCalibrateCfg, 0, sizeof(m_struCalibrateCfg));
    m_iCalibrateLineType = 0;
    memset(&m_struBehaOutCal, 0, sizeof(m_struBehaOutCal));
    memset(&m_struBehaviorInCalibration, 0, sizeof(m_struBehaviorInCalibration));
    memset(&m_struVerifyLineSeg, 0, sizeof(m_struVerifyLineSeg));
    m_bMouseMove = FALSE;
    m_iCaliLineCount = 0;
    m_iInSampleCount = 0;
    m_bDrawLine = FALSE;
    m_lPUServerID = -1;
    m_lPlayHandle = -1;
    memset(&m_struPuStream, 0, sizeof(m_struPuStream));

}

void CDlgVcaBehaviorCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaBehaviorCalibrate)
	DDX_Control(pDX, IDC_COMBO_CALIBRATION_MODE, m_comboCalibrationMode);
	DDX_Control(pDX, IDC_COMBO_CHECKTYPE, m_comboChkType);
	DDX_Control(pDX, IDC_CHECK_CALIBRATE, m_ChkCalibrate);
	DDX_Control(pDX, IDC_STATIC_PIC_SHOW, m_staticPic);
	DDX_Text(pDX, IDC_EDIT_CAMERA_HEIGHT, m_fCameraHeight);
	DDX_Text(pDX, IDC_EDIT_CAMERA_ANGLE, m_fCameraAngle);
	DDX_Text(pDX, IDC_EDIT_CAMERA_HORIZON, m_fCameraHorizon);
	DDX_Check(pDX, IDC_CHK_ANGLE, m_bAngle);
	DDX_Check(pDX, IDC_CHK_HEIGHT, m_bHeight);
	DDX_Check(pDX, IDC_CHK_HORIZON, m_bHorizon);
	DDX_Check(pDX, IDC_CHECK_CAL, m_bEanbleCal);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fHeight);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_fLength);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgVcaBehaviorCalibrate, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaBehaviorCalibrate)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_CALIBRATE, OnCheckCalibrate)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_CHECKTYPE, OnSelchangeComboChecktype)
	ON_BN_CLICKED(IDC_BTN_SET_CAMERA_HEIGHT, OnBtnSetCameraHeight)
	ON_BN_CLICKED(IDC_RADIO_HEIGHT, OnRadioHeight)
	ON_BN_CLICKED(IDC_RADIO_LENGTH, OnRadioLength)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BUTTON_RE_CAPTURE, OnButtonReCapture)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_CALIBRATION_MODE, OnSelchangeComboCalibrationMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCalibrate message handlers

BOOL CDlgVcaBehaviorCalibrate::OnInitDialog() 
{
	CDialog::OnInitDialog();

    GetDlgItem(IDC_STATIC_PIC_SHOW)->GetClientRect(&m_rcRect);

    if (!CaptureBmp())
	{
		return FALSE;
	}
	
    InitWnd();

	m_comboChkType.SetCurSel(0);
    OnSelchangeComboChecktype();

	HBITMAP hBmp = 0;
	char ch[256] = {0};
	Sleep(200);	
	hBmp = m_pic.LoadPicture(m_chFilename);
	if (hBmp == 0)
	{
		TRACE("LoadPicture fail\n");
		//return FALSE;
	}
		
	if (!GetCursetCalibrate())
	{
        AfxMessageBox("fail to get calibrate");
        return FALSE;
	}
	
    SetCalibrateTypeToWnd(m_struCalibrateCfg.byCalibrationType);
    OnSelchangeComboCalibrationMode();

    if (BEHAVIOR_IN_CALIBRATE == m_struCalibrateCfg.byCalibrationType)
    {
        SetCameraParamWnd(m_struCalibrateCfg.uCalibrateParam.struBehaviorInCalibration.struCameraParam);
    }
    else if (BEHAVIOR_OUT_CALIBRATE == m_struCalibrateCfg.byCalibrationType)
    {
        SetCameraParamWnd(m_struCalibrateCfg.uCalibrateParam.struBehaviorOutCalibration.struCameraParam);
    }

    m_iCalibrateLineType = 0;  
    ((CButton*)GetDlgItem(IDC_RADIO_HEIGHT))->SetCheck(1);

    m_bEanbleCal = m_struCalibrateCfg.byEnable;
    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaBehaviorCalibrate::SetCalibrateTypeToWnd(int nCalibrateType)
{
    for (int i = 0; i < m_comboCalibrationMode.GetCount(); i++)
    {
        if (m_comboCalibrationMode.GetItemData(i) == nCalibrateType)
        {
            m_comboCalibrationMode.SetCurSel(i);
        }
    }
}

int  CDlgVcaBehaviorCalibrate::GetCalibrateTypeFromWnd()
{
    return m_comboCalibrationMode.GetItemData(m_comboCalibrationMode.GetCurSel());
}

void CDlgVcaBehaviorCalibrate::InitWnd()
{
    char szLan[128] = {0};
    int iIndex = 0;
    m_comboChkType.ResetContent();    
    g_StringLanType(szLan, "竖直高度", "Height");
    m_comboChkType.AddString(szLan);
    g_StringLanType(szLan, "水平长度", "Length");
    m_comboChkType.AddString(szLan);

    m_comboCalibrationMode.ResetContent();
    iIndex = 0;
    g_StringLanType(szLan, "室外模式", "Out Mode");
    m_comboCalibrationMode.AddString(szLan);
    m_comboCalibrationMode.SetItemData(iIndex, BEHAVIOR_OUT_CALIBRATE);
    iIndex++;
    
    g_StringLanType(szLan, "室内模式", "In Mode");
    m_comboCalibrationMode.AddString(szLan);
    m_comboCalibrationMode.SetItemData(iIndex, BEHAVIOR_IN_CALIBRATE);
    iIndex++;
}

void CDlgVcaBehaviorCalibrate::OnPaint() 
{
    CPaintDC dc(this); // device context for painting
    
    //Draw the bitmap
    GetDlgItem(IDC_STATIC_PIC_SHOW)->GetClientRect(&m_rcRect);
    CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC_SHOW));
    m_pic.DrawPicture(dc2.m_hDC, m_rcRect.left, m_rcRect.top, m_rcRect.Width(), m_rcRect.Height());
    CDC *pDc = NULL;
    pDc = GetDlgItem(IDC_STATIC_PIC_SHOW)->GetDC();
	if (0 == m_ChkCalibrate.GetCheck())
	{
        if (BEHAVIOR_IN_CALIBRATE == GetCalibrateTypeFromWnd())
        {
            DrawBehaviorInCalibrate(pDc->m_hDC, m_struBehaviorInCalibration);
        }
        else if (BEHAVIOR_OUT_CALIBRATE == GetCalibrateTypeFromWnd())
        {
            DrawBehaviorOutCalibrate(pDc->m_hDC, m_struBehaOutCal);
        }
	}
	else if (1 == m_ChkCalibrate.GetCheck())
	{
        DrawCalibrateLine(pDc->m_hDC, &m_struVerifyLineSeg);
	}	
    if (pDc != NULL)
    {
        ReleaseDC(pDc);
        pDc = NULL;
    }

    // Do not call CDialog::OnPaint() for painting messages
}

void CDlgVcaBehaviorCalibrate::DrawCalibrateLine(HDC hDC,  NET_DVR_LINE_SEGMENT const *lpLineSegment)
{
    DRAW_VCA_POINT_PARAM struVcaPointParam;
    memset(&struVcaPointParam, 0, sizeof(struVcaPointParam));
    struVcaPointParam.color = RGB(7, 24, 237);
    memcpy(&struVcaPointParam.rcWnd, &m_rcRect, sizeof(struVcaPointParam.rcWnd));
    memcpy(&struVcaPointParam.struVcaPoint, &lpLineSegment->struStartPoint, sizeof(struVcaPointParam.struVcaPoint));
    CDrawFun::DrawVcaPoint(hDC, &struVcaPointParam);
    
    memcpy(&struVcaPointParam.struVcaPoint, &lpLineSegment->struEndPoint, sizeof(struVcaPointParam.struVcaPoint));
    CDrawFun::DrawVcaPoint(hDC, &struVcaPointParam); 

    DRAW_LINE_SEGMENT_PARAM struLineSegParam;
    memset(&struLineSegParam,0, sizeof(struLineSegParam));
    struLineSegParam.color = RGB(5, 239, 17);
    memcpy(&struLineSegParam.rcWnd, &m_rcRect, sizeof(struLineSegParam.rcWnd));
    memcpy(&struLineSegParam.struLineSegment, lpLineSegment, sizeof(struLineSegParam.struLineSegment));
    
    CDrawFun::DrawLineSegment(hDC, &struLineSegParam);
}

void CDlgVcaBehaviorCalibrate::DrawBehaviorInCalibrate(HDC hDc, const NET_DVR_BEHAVIOR_IN_CALIBRATION& struInCalibrate)
{
    DRAW_RECT_PARAM struRectParam;
    memset(&struRectParam, 0, sizeof(struRectParam));
    memcpy(&struRectParam.rcWnd, &m_rcRect, sizeof(struRectParam.rcWnd));
    struRectParam.color = RGB(5, 239, 17);
    

    for (int i = 0; i < struInCalibrate.dwCalSampleNum; i++)
    {
        memcpy(&struRectParam.struVcaRect, &struInCalibrate.struCalSample[i].struVcaRect, sizeof(struRectParam.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struRectParam);

        DrawCalibrateLine(hDc, &struInCalibrate.struCalSample[i].struLineSegment);
    }
}

void CDlgVcaBehaviorCalibrate::DrawBehaviorOutCalibrate(HDC hDc, const NET_DVR_BEHAVIOR_OUT_CALIBRATION&  struOutCalibrate)
{   
    for (int i = 0; i < struOutCalibrate.dwLineSegNum; i++)
    {
        DrawCalibrateLine(hDc, &struOutCalibrate.struLineSegment[i]);
    }
}

BOOL CDlgVcaBehaviorCalibrate::GetCursetCalibrate()
{
    memset(&m_struCalibrateCfg, 0, sizeof(m_struCalibrateCfg));
	DWORD dwReturned;
	BOOL bResult = FALSE;

    bResult = NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CALIBRATION, m_lChannel, &m_struCalibrateCfg, sizeof(m_struCalibrateCfg), &dwReturned);
	
	if (bResult)
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel);
        if (BEHAVIOR_OUT_CALIBRATE == m_struCalibrateCfg.byCalibrationType)
        {

            memcpy(&m_struBehaOutCal, &m_struCalibrateCfg.uCalibrateParam.struBehaviorOutCalibration, sizeof(m_struBehaOutCal));
        }
        else if (BEHAVIOR_IN_CALIBRATE == m_struCalibrateCfg.byCalibrationType)
        {
            memcpy(&m_struBehaviorInCalibration, &m_struCalibrateCfg.uCalibrateParam.struBehaviorInCalibration, sizeof(m_struBehaviorInCalibration));
        }
		return TRUE;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel);   
		return FALSE;
	}
	
    return TRUE;
}

/*********************************************************
  Function:	SaveCursetCalibrate
  Desc:		Save parameter
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgVcaBehaviorCalibrate::SaveCursetCalibrate()
{
    UpdateData(TRUE);
    
    BOOL bResult = FALSE;
    m_struCalibrateCfg.byEnable = m_bEanbleCal;
    m_struCalibrateCfg.byCalibrationType = GetCalibrateTypeFromWnd();
    

    if (BEHAVIOR_IN_CALIBRATE == m_struCalibrateCfg.byCalibrationType)
    {
        GetCameraParamWnd(m_struBehaviorInCalibration.struCameraParam);
        memcpy(&m_struCalibrateCfg.uCalibrateParam.struBehaviorInCalibration, &m_struBehaviorInCalibration, sizeof(m_struBehaviorInCalibration));
    }
    else if (BEHAVIOR_OUT_CALIBRATE == m_struCalibrateCfg.byCalibrationType)
    {
        GetCameraParamWnd(m_struBehaOutCal.struCameraParam);
        memcpy(&m_struCalibrateCfg.uCalibrateParam.struBehaviorOutCalibration, &m_struBehaOutCal, sizeof(m_struBehaOutCal));
    }
    
	bResult = NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CALIBRATION, m_lChannel, &m_struCalibrateCfg, sizeof(m_struCalibrateCfg));
	if (bResult)
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CALIBRATION");
        char szLan[128] = {0};
        g_StringLanType(szLan, "保存标定线配置信息成功!", "Success to save calibrate line");
        AfxMessageBox(szLan);
		return TRUE;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CALIBRATION");
        char szLan[128] = {0};
        g_StringLanType(szLan, "保存标定线配置信息失败!", "Fail to save calibrate line");
     	AfxMessageBox(szLan);
		
		return FALSE;
	}
    return TRUE;
}

void CDlgVcaBehaviorCalibrate::GetCameraParamWnd(NET_DVR_CAMERA_PARAM& struCameraParam)
{
    struCameraParam.byEnableHeight = m_bHeight;
    struCameraParam.fCameraHeight = m_fCameraHeight;

    struCameraParam.byEnableAngle = m_bAngle;
    struCameraParam.fCameraAngle = m_fCameraAngle;

    struCameraParam.byEnableHorizon = m_bHorizon;
    struCameraParam.fHorizon = m_fCameraHorizon;
}

void CDlgVcaBehaviorCalibrate::SetCameraParamWnd(NET_DVR_CAMERA_PARAM& struCameraParam)
{
    m_bHeight = struCameraParam.byEnableHeight;
    m_fCameraHeight = struCameraParam.fCameraHeight;
        
    m_bAngle = struCameraParam.byEnableAngle;
    m_fCameraAngle = struCameraParam.fCameraAngle;
    
    m_bHorizon = struCameraParam.byEnableHorizon;
    m_fCameraHorizon = struCameraParam.fHorizon;
}
void CDlgVcaBehaviorCalibrate::OnCheckCalibrate() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_ChkCalibrate.GetCheck())
	{
		m_comboChkType.EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_LENGTH)->EnableWindow(TRUE);
		m_pic.FreePicture();
		
		if(!m_pic.LoadPicture(m_chFilename))
		{
            char szLan[128] = {0};
            g_StringLanType(szLan, "重新装载图片失败!", "Fail to reload picture");
			AfxMessageBox(szLan);
			return;
		}
		
	}
	else if (1 == m_ChkCalibrate.GetCheck())
	{
		m_comboChkType.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_LENGTH)->EnableWindow(FALSE);
	}
    Invalidate(TRUE);
}

void CDlgVcaBehaviorCalibrate::OnBtnSave() 
{
// 	// TODO: Add your control notification handler code here
	BOOL bResult = FALSE;
	bResult = SaveCursetCalibrate();
}

/*********************************************************
  Function:	CaptureBmp
  Desc:		capture bmp
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgVcaBehaviorCalibrate::CaptureBmp()
{
	UpdateData(TRUE);
	CString sTemp;
	CTime time = CTime::GetCurrentTime();
	
	sTemp.Format("%s\\", g_struLocalParam.chPictureSavePath);		
	if (GetFileAttributes(sTemp) != FILE_ATTRIBUTE_DIRECTORY)
	{
		CreateDirectory(sTemp, NULL);
	}

    sprintf(m_chFilename, "%s\\JPEG_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.bmp", \
		g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIPInFileName, m_lChannel,	\
		time.GetYear(), time.GetMonth(), time.GetDay(), \
		time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());

//     NET_DVR_CLIENTINFO struPlay = {0};
//     struPlay.hPlayWnd 	= GetDlgItem(IDC_STATIC_REALPLAY)->GetSafeHwnd(); 
//     struPlay.lChannel 	= m_lChannel; 
//     struPlay.lLinkMode 	= 0;
//     struPlay.sMultiCastIP = "";	
// 
//     long lRealPlayHandle = -1;
//     lRealPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE);
//     if (lRealPlayHandle < 0 )
//     {
//         MessageBox("Fail to Preview");
//         return FALSE;
//     }

    StartPlay();
    BOOL    bFlag = FALSE;
    bFlag = NET_DVR_CapturePicture(m_lPlayHandle, m_chFilename);
    if (bFlag)
    {
        CString sTemp;	
        sTemp.Format("Capture picture succ %s!",m_chFilename);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CapturePicture file[%s]", m_chFilename);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CapturePicture");
        AfxMessageBox("Fail to capture picture!");
    }

    Sleep(500);
    StopPlay();
//     if (lRealPlayHandle >= 0)
//     {
//         NET_DVR_StopRealPlay(lRealPlayHandle);
//     }
    
    return bFlag;
    
}

void CDlgVcaBehaviorCalibrate::OnSelchangeComboChecktype() 
{

}


void CDlgVcaBehaviorCalibrate::OnBtnSetCameraHeight() 
{

}


void CDlgVcaBehaviorCalibrate::OnRadioHeight() 
{
	// TODO: Add your control notification handler code here
    m_iCalibrateLineType = HEIGHT_LINE; 
	
}

void CDlgVcaBehaviorCalibrate::OnRadioLength() 
{
	// TODO: Add your control notification handler code here
	m_iCalibrateLineType = LENGTH_LINE; 
}

void CDlgVcaBehaviorCalibrate::OnButtonReCapture() 
{
	// TODO: Add your control notification handler code here
    // TODO: Add your control notification handler code here
    if (!CaptureBmp())
    {
        return;
    }
    
    if(!m_pic.LoadPicture(m_chFilename))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "重新装载图片失败", "Reload picture fail");
        AfxMessageBox(szLan);
        return;
    }
    // 	
    if (1 == m_ChkCalibrate.GetCheck())
    {
        GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(FALSE);
        
        //Draw the bitmap
        CRect rect;
        GetDlgItem(IDC_STATIC_PIC_SHOW)->GetWindowRect(&rect);
        CPaintDC dc2(GetDlgItem(IDC_STATIC_PIC_SHOW));
        m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
    }
    else
    {
//        DrawCurAllCalibrateLine();
	}	
}

void CDlgVcaBehaviorCalibrate::OnBtnRefresh() 
{

}

void CDlgVcaBehaviorCalibrate::OnSelchangeComboCalibrationMode() 
{
	
}

BOOL CDlgVcaBehaviorCalibrate::PreTranslateMessage(MSG* pMsg) 
{
    GetDlgItem(IDC_STATIC_PIC_SHOW)->GetWindowRect(&m_rcRect);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);
    if (PtInRect(m_rcRect, pt))
    {
        if (1 == m_ChkCalibrate.GetCheck())
        {
            PreDrawVerifyLine(pMsg, pt);
        }
        else
        {
            if (BEHAVIOR_IN_CALIBRATE == GetCalibrateTypeFromWnd())
            {
                PreDrawInCalibrate(pMsg, pt);
            }
            else if (BEHAVIOR_OUT_CALIBRATE == GetCalibrateTypeFromWnd())
            {
                 PreDrawOutCalibrate(pMsg, pt);
            }
        }
    }
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CDlgVcaBehaviorCalibrate::PreDrawVerifyLine(MSG* pMsg, CPoint& pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        m_struVerifyLineSeg.byLineMode = m_comboChkType.GetCurSel();
        m_struVerifyLineSeg.fValue = 0;
        m_struVerifyLineSeg.struStartPoint.fX = (float)(pt.x - m_rcRect.left) / m_rcRect.Width();
        m_struVerifyLineSeg.struStartPoint.fY = (float)(pt.y - m_rcRect.top) / m_rcRect.Height();
        memcpy(&m_struVerifyLineSeg.struEndPoint, &m_struVerifyLineSeg.struStartPoint, sizeof(m_struVerifyLineSeg.struEndPoint));
        m_bMouseMove = TRUE;
        GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
        OnPaint();
        break;
    case WM_MOUSEMOVE:
        if (m_bMouseMove)
        {
            m_struVerifyLineSeg.struEndPoint.fX = (float)(pt.x - m_rcRect.left) / m_rcRect.Width();
            m_struVerifyLineSeg.struEndPoint.fY = (float)(pt.y - m_rcRect.top) / m_rcRect.Height();
            //GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
            GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
            OnPaint();
        }
        
        break;
    case WM_LBUTTONUP:
        {
            m_bMouseMove = FALSE;
            BOOL bResult =  FALSE;
            float fHeight = 0;
            char szLan[128] ;
            if (0 == m_comboChkType.GetCurSel())
            {
                
                m_struVerifyLineSeg.byLineMode = HEIGHT_LINE;
                bResult = NET_DVR_VerifyCalibration(m_lServerID, NET_DVR_VERIFY_BEHAVIOR_CALIBRATION, m_lChannel, &m_struVerifyLineSeg, sizeof(m_struVerifyLineSeg), &fHeight, sizeof(fHeight));
                if (!bResult)
                {
                    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_VERIFY_BEHAVIOR_CALIBRATION");
                    
                    g_StringLanType(szLan, "获取校验竖直高度失败!", "Fail to get height verify calibration");
                    AfxMessageBox(szLan);
                    
                    memset(&m_struVerifyLineSeg, 0, sizeof(m_struVerifyLineSeg));
                    //					delete lpCheckLine;
                    Invalidate(TRUE);
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_VERIFY_BEHAVIOR_CALIBRATION");
                    m_struVerifyLineSeg.fValue = fHeight;
                }
            }
            else if (1 == m_comboChkType.GetCurSel())
            {
                float fLength = 0;
                m_struVerifyLineSeg.byLineMode = LENGTH_LINE;
                bResult = NET_DVR_VerifyCalibration(m_lServerID, NET_DVR_VERIFY_BEHAVIOR_CALIBRATION, m_lChannel, &m_struVerifyLineSeg, sizeof(m_struVerifyLineSeg), &fLength, sizeof(fLength));
                if (!bResult)
                {
                    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_VERIFY_BEHAVIOR_CALIBRATION");
                    g_StringLanType(szLan, "获取校验水平长度失败!", "Fail to get length verify calibration");
                    AfxMessageBox(szLan);
                    memset(&m_struVerifyLineSeg, 0, sizeof(m_struVerifyLineSeg));
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_VERIFY_BEHAVIOR_CALIBRATION");
                    m_struVerifyLineSeg.fValue = fLength;
                }
            }
            GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
            OnPaint();
        }
        break;
    case WM_RBUTTONDOWN:
        memset(&m_struVerifyLineSeg, 0, sizeof(m_struVerifyLineSeg));
        GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
        OnPaint();
        break;
    default:
        break;
    }
    return TRUE;
}

BOOL CDlgVcaBehaviorCalibrate::PreDrawOutCalibrate(MSG* pMsg,CPoint& pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if(m_struBehaOutCal.dwLineSegNum < MAX_LINE_SEG_NUM)
        {
            UpdateData(TRUE);
            m_bMouseMove = TRUE;
            m_iCaliLineCount  = m_struBehaOutCal.dwLineSegNum;
            m_struBehaOutCal.dwLineSegNum += 1;
            m_struBehaOutCal.struLineSegment[m_iCaliLineCount].byLineMode =  m_iCalibrateLineType;
            if (HEIGHT_LINE == m_iCalibrateLineType)
            {
                m_struBehaOutCal.struLineSegment[m_iCaliLineCount].fValue = m_fHeight;
            }
            else
            {
                m_struBehaOutCal.struLineSegment[m_iCaliLineCount].fValue = m_fLength;
            }
            
            m_struBehaOutCal.struLineSegment[m_iCaliLineCount].struStartPoint.fX = (float)(pt.x - m_rcRect.left) / m_rcRect.Width();
            m_struBehaOutCal.struLineSegment[m_iCaliLineCount].struStartPoint.fY = (float)(pt.y - m_rcRect.top) / m_rcRect.Height();
            memcpy(&m_struBehaOutCal.struLineSegment[m_iCaliLineCount].struEndPoint, &m_struBehaOutCal.struLineSegment[m_iCaliLineCount].struStartPoint, sizeof(m_struBehaOutCal.struLineSegment[m_iCaliLineCount].struStartPoint));
        }
        break;
    case WM_MOUSEMOVE:
        if (m_bMouseMove)
        {
            m_struBehaOutCal.struLineSegment[m_iCaliLineCount].struEndPoint.fX = (float)(pt.x - m_rcRect.left) / m_rcRect.Width();
            m_struBehaOutCal.struLineSegment[m_iCaliLineCount].struEndPoint.fY = (float)(pt.y - m_rcRect.top) / m_rcRect.Height();

        }
        break;
    case WM_LBUTTONUP:
        m_iCaliLineCount += 1;
        m_bMouseMove = FALSE;
        break;
    case WM_RBUTTONDOWN:
        {
            m_iCaliLineCount = 0;
            memset(&m_struBehaOutCal, 0, sizeof(m_struBehaOutCal));
        }

        break; 
    default:
        break;
    }
    GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
    OnPaint();
    return TRUE;
}


BOOL CDlgVcaBehaviorCalibrate::PreDrawInCalibrate(MSG* pMsg,CPoint& pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        {
            UpdateData(TRUE);
            if (m_iInSampleCount < MAX_SAMPLE_NUM)
            {
                m_bMouseMove = TRUE;
                if (!m_bDrawLine)
                {
                    m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struVcaRect.fX = (float)(pt.x - m_rcRect.left) / m_rcRect.Width();
                    m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struVcaRect.fY = (float)(pt.y - m_rcRect.top) / m_rcRect.Height();
                }
                else
                {
                    m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struLineSegment.struStartPoint.fX = (float)(pt.x - m_rcRect.left) / m_rcRect.Width();
                    m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struLineSegment.struStartPoint.fY = (float)(pt.y - m_rcRect.top) / m_rcRect.Height();
                    m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struLineSegment.fValue = m_fHeight;
                    memcpy(&m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struLineSegment.struEndPoint, &m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struLineSegment.struStartPoint, sizeof(NET_VCA_POINT));
                }
            }
        }
        break;
    case WM_MOUSEMOVE:
        if (m_bMouseMove)
        {
            if (!m_bDrawLine)
            {
                m_struBehaviorInCalibration.dwCalSampleNum = m_iInSampleCount+1;
                m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struVcaRect.fWidth = 
                    (float)(pt.x - m_rcRect.left) / m_rcRect.Width() - m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struVcaRect.fX;
                m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struVcaRect.fHeight = 
                    (float)(pt.y - m_rcRect.top) / m_rcRect.Height() - m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struVcaRect.fY;
            }
            else
            {
                m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struLineSegment.struEndPoint.fX = (float)(pt.x - m_rcRect.left) / m_rcRect.Width();
                m_struBehaviorInCalibration.struCalSample[m_iInSampleCount].struLineSegment.struEndPoint.fY = (float)(pt.y - m_rcRect.top) / m_rcRect.Height();
            }
                                    
        }
        break;
    case WM_LBUTTONUP:
        m_bMouseMove = FALSE;
        if (!m_bDrawLine)
        {
            
        }
        else
        {
            m_iInSampleCount++;
        }
        m_bDrawLine = !m_bDrawLine;
        break;
    case WM_RBUTTONDOWN:
        m_iInSampleCount = 0;

        m_struBehaviorInCalibration.dwCalSampleNum = 0;
        memset(m_struBehaviorInCalibration.struCalSample, 0, sizeof(m_struBehaviorInCalibration.struCalSample));
        break;
    default:
        break;
    }
    GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
    OnPaint();
    return TRUE;   
}

BOOL CDlgVcaBehaviorCalibrate::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG, m_lChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG");
        return FALSE;
    }
}


LONG CDlgVcaBehaviorCalibrate::StartPlay()
{
    if (GetPuStreamCfg(m_struPuStream))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        m_lPUServerID = NET_DVR_Login_V30(m_struPuStream.struDevChanInfo.struIP.sIpV4, m_struPuStream.struDevChanInfo.wDVRPort,
            (char*)m_struPuStream.struDevChanInfo.sUserName, (char*)m_struPuStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (m_lPUServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return m_lPUServerID;
        }
        
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_STATIC_REALPLAY)->GetSafeHwnd();
        struPlay.lChannel 	= m_struPuStream.struDevChanInfo.byChannel; 
        struPlay.lLinkMode 	= 0;
        struPlay.sMultiCastIP = "";	
        
        m_lPlayHandle = NET_DVR_RealPlay_V30(m_lPUServerID, &struPlay, NULL, NULL, TRUE); 
        
        BOOL bRet = FALSE;
        if (m_lPlayHandle < 0)
        {
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
            AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
        }
        else
        {
            g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
        }
        return m_lPlayHandle;
    }
    else // 到设备去取流预览
    {
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_STATIC_REALPLAY)->GetSafeHwnd();
        struPlay.lChannel 	= m_lChannel; 
        struPlay.lLinkMode 	= 0;
        struPlay.sMultiCastIP = "";	
        
        m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
        BOOL bRet = FALSE;
        if (m_lPlayHandle < 0)
        {
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
            AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
        }
        else
        {
            g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
        }
        return m_lPlayHandle;
    } 

}

BOOL CDlgVcaBehaviorCalibrate::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    
    if (m_lPUServerID >= 0)
    {
        NET_DVR_Logout_V30(m_lPUServerID);
        m_lPUServerID = -1;
    }
    return TRUE;
}
