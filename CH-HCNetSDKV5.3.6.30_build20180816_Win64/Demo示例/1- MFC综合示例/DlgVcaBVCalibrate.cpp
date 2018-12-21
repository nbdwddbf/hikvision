// DlgVcaBVCalibrate.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaBVCalibrate.h"
#include "DlgPtzCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBVCalibrate dialog


CDlgVcaBVCalibrate::CDlgVcaBVCalibrate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaBVCalibrate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaBVCalibrate)
	m_dwCameraHeight = 0;
	m_fPitchAngle = 0.0f;
	m_fInclineAngle = 0.0f;
	m_bEnable = FALSE;
	m_dwSampleCameraHeight = 0;
	m_dwSampleHumanHeight = 0;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_dwCameraHeightSample = 0;
	m_fInclineAngleSample = 0.0f;
	m_fPitchAngleSample = 0.0f;
	m_fBvCalibration = 0.0f;
	m_iID = 0;
    m_dwPicID = 0;
    m_dwPicLen = 0;
    m_csSaveAddress = "";
    m_dwBvPicID = 0;
    m_fPointX = 0.0f;
    m_fPointY = 0.0f;
    m_dwVcaNumber = 0;
    m_dwHumanHeight = 0;
    m_dwCameraHeightBv = 0;
    m_fPitchAngleBv = 0.0f;
    m_fInclineAngleBv = 0.0f;
    m_dwHcorrectionPictureID = 0;
    m_dwHcorrectionHumanHeight = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
	m_lPlayHandle = -1;
	m_iCaliType = 0;

	memset(&m_struDirectCaliCfg, 0, sizeof(m_struDirectCaliCfg));
	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	memset(&m_struPoint, 0, sizeof(m_struPoint));
	memset(&m_struGetSampleCaliCfg, 0, sizeof(m_struGetSampleCaliCfg));
	memset(&m_struVerifyRect, 0, sizeof(m_struVerifyRect));
    memset(&m_struBvCalibInfo, 0, sizeof(m_struBvCalibInfo));

    m_pRecvicBuffer = new char[640 * 480];
}

CDlgVcaBVCalibrate::~CDlgVcaBVCalibrate()
{
	StopPlay();
    if (m_pRecvicBuffer != NULL)
    {
        delete[] m_pRecvicBuffer;
    }
    m_pRecvicBuffer = NULL;
}

void CDlgVcaBVCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaBVCalibrate)
	DDX_Control(pDX, IDC_COMBO_GET_CALIB_TYPE, m_comGetCalibType);
	DDX_Control(pDX, IDC_COMBO_CALIB_TYPE, m_comCalibType);
	DDX_Control(pDX, IDC_COMBO_VIDEO_TYPE, m_comVideoType);
	DDX_Control(pDX, IDC_COMBO_CAILB_ID_SAMPLE, m_comCailbIDSample);
	DDX_Control(pDX, IDC_COMBO_CAILB_ID, m_comCailbID);
    DDX_Control(pDX, IDC_COMBO_PARAM_NUMBER, m_comParamNumber);
	DDX_Text(pDX, IDC_EDIT_CAMEAR_HEIGHT, m_dwCameraHeight);
	DDX_Text(pDX, IDC_EDIT_PITCH_ANGLE, m_fPitchAngle);
	DDX_Text(pDX, IDC_EDIT_INCLINE_ANGLE, m_fInclineAngle);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_CAMEAR_HEIGHT, m_dwSampleCameraHeight);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_HUMAN_HEIGHT, m_dwSampleHumanHeight);
	DDX_Text(pDX, IDC_EDIT_POINT_X, m_fX);
	DDX_Text(pDX, IDC_EDIT_POINT_Y, m_fY);
	DDX_Text(pDX, IDC_EDIT_CAMEAR_HEIGHT_SAMPLE, m_dwCameraHeightSample);
	DDX_Text(pDX, IDC_EDIT_INCLINE_ANGLE_SAMPLE, m_fInclineAngleSample);
	DDX_Text(pDX, IDC_EDIT_PITCH_ANGLE_SAMPLE, m_fPitchAngleSample);
	DDX_Text(pDX, IDC_EDIT_BV_CALIBRATION, m_fBvCalibration);
	DDX_Text(pDX, IDC_EDIT_ID, m_iID);
    DDX_Text(pDX, IDC_EDIT_PICTURE_ID, m_dwPicID);
    DDX_Text(pDX, IDC_EDIT_PICTURE_LEN, m_dwPicLen);
    DDX_Text(pDX, IDC_EDIT_SAVE_ADDRESS, m_csSaveAddress);
    DDX_Text(pDX, IDC_EDIT_PIC_ID, m_dwBvPicID);
    DDX_Text(pDX, IDC_EDIT_VCA_POINT_X, m_fPointX);
    DDX_Text(pDX, IDC_EDIT_VCA_POINT_Y, m_fPointY);
    DDX_Text(pDX, IDC_EDIT_VCA_NUMBER, m_dwVcaNumber);
    DDX_Text(pDX, IDC_EDIT_HUMAN_HEIGHT, m_dwHumanHeight);
    DDX_Text(pDX, IDC_EDIT_CAMERA_HEIGHT_BV, m_dwCameraHeightBv);
    DDX_Text(pDX, IDC_EDIT_PITCH_ANGLE_BV, m_fPitchAngleBv);
    DDX_Text(pDX, IDC_EDIT_INCLINE_ANGLE_BV, m_fInclineAngleBv);
    DDX_Text(pDX, IDC_EDIT_HCORRECTION_PICTURE, m_dwHcorrectionPictureID);
    DDX_Text(pDX, IDC_EDIT_HCORRECTION_HUMAN_HEIGHT, m_dwHcorrectionHumanHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaBVCalibrate, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaBVCalibrate)
	ON_BN_CLICKED(IDC_BTN_GET_DIRECT_CALI, OnBtnGetDirectCali)
	ON_BN_CLICKED(IDC_BTN_SET_DIRECT_CALI, OnBtnSetDirectCali)
	ON_BN_CLICKED(IDC_BTN_BEGIN_CALIB, OnBtnBeginCalib)
	ON_BN_CLICKED(IDC_BTN_SET_CALIB, OnBtnSetCalib)
	ON_BN_CLICKED(IDC_BTN_END_CALIB, OnBtnEndCalib)
	ON_BN_CLICKED(IDC_BTN_GET_CALIB, OnBtnGetCalib)
	ON_CBN_SELCHANGE(IDC_COMBO_CAILB_ID_SAMPLE, OnSelchangeComboCailbIdSample)
	ON_BN_CLICKED(IDC_BTN_VERIFY_BV_CALIBRATION, OnBtnVerifyBvCalibration)
	ON_BN_CLICKED(IDC_BTN_GET_OUTPUT_VIDEO_TYPE, OnBtnGetOutputVideoType)
	ON_BN_CLICKED(IDC_BTN_SET_OUTPUT_VIDEO_TYPE, OnBtnSetOutputVideoType)
	ON_BN_CLICKED(IDC_BTN_GET_CALIB_TYPE, OnBtnGetCalibType)
	ON_CBN_SELCHANGE(IDC_COMBO_CALIB_TYPE, OnSelchangeComboCalibType)
    ON_BN_CLICKED(IDC_BTN_GET_PICTURE_INFO, OnBtnGetPictureInfo)
    ON_BN_CLICKED(IDC_BTN_SAVE_VCA_POINT, OnBtnSaveVcaPoint)
    ON_BN_CLICKED(IDC_BTN_GET_BV_CALIB_RESULT, OnBtnGetBvCalibResult)
    ON_CBN_SELCHANGE(IDC_COMBO_PARAM_NUMBER, OnSelchangeComboParamNumber)
    ON_BN_CLICKED(IDC_BTN_GET_BV_HCORRECTION, OnBtnGetBvHcorrection)
    ON_BN_CLICKED(IDC_BUTTON_DEL_BV_CALIB_PIC, OnButtonDelBvCalibPic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBVCalibrate message handlers

BOOL CDlgVcaBVCalibrate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_PLAYWND)->GetClientRect(&m_rcWndRect);
	// TODO: Add extra initialization here
	RealPlay();
	
	m_comCalibType.SetCurSel(0);
    m_comParamNumber.SetCurSel(0);

	OnSelchangeComboCalibType() ;

	OnBtnGetCalibType();
	
	OnBtnGetOutputVideoType();

    GetDlgItem(IDC_EDIT_PICTURE_ID)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_PICTURE_LEN)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_SAVE_ADDRESS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_CAMERA_HEIGHT_BV)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_PITCH_ANGLE_BV)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_INCLINE_ANGLE_BV)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_HCORRECTION_HUMAN_HEIGHT)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 	GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);


// 
// 	if (ENUM_BV_CALIBRATION_DIRECT == m_iCaliType)
// 	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);
// 
// 		
// 		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);
// 	} 
// 	else if(ENUM_BV_CALIBRATION_SAMPLE == m_iCaliType)
// 	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 	}
// 	else if (ENUM_BV_CALIBRATION_NONE == m_iCaliType)
// 	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);
// 
// 		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 		
// 		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);
// 		
// 		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LONG CDlgVcaBVCalibrate::RealPlay()
{
    NET_DVR_CLIENTINFO struPlay;
    struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
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

    return m_lPlayHandle;
}

BOOL CDlgVcaBVCalibrate::StopPlay()
{
    BOOL bRet = FALSE;
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

void CDlgVcaBVCalibrate::DrawVerifyCalibration()
{
    CString str;
    CPen    *green_pen;
    green_pen = new CPen;
    green_pen ->CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    
    GetDlgItem(IDC_PLAYWND)->Invalidate(FALSE);
    
    CBrush brTmp;
    brTmp.CreateSolidBrush(RGB(0,255,0));
    //Draw the bitmap
    CRect rect;
    GetDlgItem(IDC_PLAYWND)->GetClientRect(&rect);
    CPaintDC dc2(GetDlgItem(IDC_PLAYWND));
    m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
    
    m_pDCRect = GetDlgItem(IDC_PLAYWND)->GetDC();
    
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
    GetDlgItem(IDC_PLAYWND)->ReleaseDC(m_pDCRect);
    delete green_pen;
    
}

BOOL CDlgVcaBVCalibrate::PreTranslateMessage(MSG* pMsg) 
{
	CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
    GetCursorPos(&pt);
    TRACE("pt %d %d \n",pt.x, pt.y);
    switch(pMsg->message) 
    {
    case WM_LBUTTONDOWN:
        if(PtInRect(&rcWnd,pt))
        { 
           m_struPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
           m_struPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
		   OnBtnSetCalib() ;
		   //DrawVerifyCalibration();
        }
        break;
    }
	return CDialog::PreTranslateMessage(pMsg);
}
void CDlgVcaBVCalibrate::OnBtnGetDirectCali() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_DIRECT != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CALIBRATION, m_lChannel, &m_struDirectCaliCfg, sizeof(m_struDirectCaliCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel); 
		return ;
    }

	m_bEnable = m_struDirectCaliCfg.byEnable;
	
	if(BV_DIRECT_CALIBRATE == m_struDirectCaliCfg.byCalibrationType)
	{
		m_dwCameraHeight = m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.dwCameraHeight;
		m_fPitchAngle = m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fPitchAngle;
		m_fInclineAngle = m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fInclineAngle;
	}
	else
	{
		g_StringLanType(szLan, "错误的直接标定类型!", "Error Direct Calibration Type");
        AfxMessageBox(szLan);
		return;
	}

	UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnBtnSetDirectCali() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_DIRECT != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	memset(&m_struDirectCaliCfg, 0, sizeof(m_struDirectCaliCfg));
	m_struDirectCaliCfg.dwSize = sizeof(m_struDirectCaliCfg);
	m_struDirectCaliCfg.byEnable = m_bEnable;
	m_struDirectCaliCfg.byCalibrationType = BV_DIRECT_CALIBRATE;
	m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.dwCameraHeight = m_dwCameraHeight;
	m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fPitchAngle = m_fPitchAngle;
	m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fInclineAngle = m_fInclineAngle;

    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CALIBRATION, m_lChannel, &m_struDirectCaliCfg, sizeof(m_struDirectCaliCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CALIBRATION Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CALIBRATION Chan[%d]", m_lChannel); 
		return ;
    }

}

void CDlgVcaBVCalibrate::SetSampleCailbCfg()
{
	if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_CONTROL_BV_SAMPLE_CALIB, &m_struSampleCaliCfg, sizeof(m_struSampleCaliCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CONTROL_BV_SAMPLE_CALIB Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CONTROL_BV_SAMPLE_CALIB Chan[%d]", m_lChannel); 
		return ;
    }
}

void CDlgVcaBVCalibrate::OnBtnBeginCalib() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	m_struSampleCaliCfg.dwSize = sizeof(m_struSampleCaliCfg);
	m_struSampleCaliCfg.dwChannel = m_lChannel;
	m_struSampleCaliCfg.byCommand = ENUM_BV_SAMPLE_CALIB_BEGIN;
	m_struSampleCaliCfg.uCalibParam.struCalibBegin.dwCameraHeight = m_dwSampleCameraHeight;
	m_struSampleCaliCfg.uCalibParam.struCalibBegin.dwHumanHeight = m_dwSampleHumanHeight;
	SetSampleCailbCfg();
}

void CDlgVcaBVCalibrate::OnBtnSetCalib() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}
	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	m_struSampleCaliCfg.dwSize = sizeof(m_struSampleCaliCfg);
	m_struSampleCaliCfg.dwChannel = m_lChannel;
	m_struSampleCaliCfg.byCommand = ENUM_BV_SAMPLE_CALIB_SETTING;
	m_struSampleCaliCfg.uCalibParam.struCalibSet.struCalibPoint.byCalibPtID = m_comCailbID.GetCurSel()+1;
	memcpy(&m_struSampleCaliCfg.uCalibParam.struCalibSet.struCalibPoint.struPoint, &m_struPoint, sizeof(m_struPoint));
	SetSampleCailbCfg();
}

void CDlgVcaBVCalibrate::OnBtnEndCalib() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	m_struSampleCaliCfg.dwSize = sizeof(m_struSampleCaliCfg);
	m_struSampleCaliCfg.dwChannel = m_lChannel;
	m_struSampleCaliCfg.byCommand = ENUM_BV_SAMPLE_CALIB_END;
	SetSampleCailbCfg();
}

void CDlgVcaBVCalibrate::OnBtnGetCalib() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}
	
	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_BV_SAMPLE_CALIB_CFG, m_lChannel, &m_struGetSampleCaliCfg, sizeof(m_struGetSampleCaliCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_SAMPLE_CALIB_CFG Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_SAMPLE_CALIB_CFG Chan[%d]", m_lChannel); 
		return ;
    }

	m_dwCameraHeightSample = m_struGetSampleCaliCfg.dwCameraHeight;
	m_fPitchAngleSample = m_struGetSampleCaliCfg.fPitchAngle;
	m_fInclineAngleSample = m_struGetSampleCaliCfg.fInclineAngle;
    m_comCailbIDSample.SetCurSel(0);
	m_iID = m_struGetSampleCaliCfg.struCalibPoint[0].byCalibPtID;
	m_fX = m_struGetSampleCaliCfg.struCalibPoint[0].struPoint.fX;
	m_fY = m_struGetSampleCaliCfg.struCalibPoint[0].struPoint.fY;
	UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnSelchangeComboCailbIdSample() 
{
	// TODO: Add your control notification handler code here
	int i = m_comCailbIDSample.GetCurSel();
    if (i >= 5)
    {
        m_iID = m_struGetSampleCaliCfg.struCalibPointEx[i - 5].byCalibPtID;
        m_fX = m_struGetSampleCaliCfg.struCalibPointEx[i - 5].struPoint.fX;
        m_fY = m_struGetSampleCaliCfg.struCalibPointEx[i - 5].struPoint.fY;
    }
    else
    {
        m_iID = m_struGetSampleCaliCfg.struCalibPoint[i].byCalibPtID;
        m_fX = m_struGetSampleCaliCfg.struCalibPoint[i].struPoint.fX;
        m_fY = m_struGetSampleCaliCfg.struCalibPoint[i].struPoint.fY;
    }

	UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnBtnVerifyBvCalibration() 
{
	// TODO: Add your control notification handler code here
	float fHeight = 0;
	if (NET_DVR_VerifyCalibration(m_lServerID, NET_DVR_VERIFY_BV_CALIBRATION, m_lChannel, &m_struPoint, sizeof(m_struPoint), &fHeight, sizeof(fHeight)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_VERIFY_BV_CALIBRATION Chan[%d]", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_VERIFY_BV_CALIBRATION Chan[%d]", m_lChannel);
	}

	m_fBvCalibration = fHeight;
	UpdateData(FALSE);
	//DrawVerifyCalibration();
}

void CDlgVcaBVCalibrate::OnBtnGetOutputVideoType() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_OUTPUT_VIDEO_TYPE struVideoType = {0};

	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_OUTPUT_VIDEO_TYPE, m_lChannel, &struVideoType, sizeof(struVideoType), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel); 
		return ;
    }

	m_comVideoType.SetCurSel(struVideoType.byType - 1);
}

void CDlgVcaBVCalibrate::OnBtnSetOutputVideoType() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_OUTPUT_VIDEO_TYPE struVideoType = {0};
	struVideoType.dwSize = sizeof(struVideoType);
	struVideoType.byType = m_comVideoType.GetCurSel() + 1;
   if (NET_DVR_SetDVRConfig(m_lServerID,  NET_DVR_SET_OUTPUT_VIDEO_TYPE, m_lChannel, &struVideoType, sizeof(struVideoType)))
   {
	   g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel);
   }
   else
   {
	   g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel); 
	   return ;
   }
}

void CDlgVcaBVCalibrate::OnBtnGetCalibType() 
{
	// TODO: Add your control notification handler code here
	
	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_BV_CALIB_TYPE, m_lChannel, &m_iCaliType, sizeof(m_iCaliType), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_CALIB_TYPE Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_CALIB_TYPE Chan[%d]", m_lChannel); 
		return ;
    }

	m_comGetCalibType.SetCurSel(m_iCaliType);
}

void CDlgVcaBVCalibrate::OnSelchangeComboCalibType() 
{
	// TODO: Add your control notification handler code here
	int i = m_comCalibType.GetCurSel();

	if (ENUM_BV_CALIBRATION_DIRECT == i)
	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_SHOW);

		
		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_VERIFY_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_NOTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
	} 
	else if(ENUM_BV_CALIBRATION_SAMPLE == i)
	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_VERIFY_BV_CALIBRATION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAILB_NOTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BV_CALIBRATION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BV_CALIBRATION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_SHOW);
	}
	else if (ENUM_BV_CALIBRATION_NONE == i)
	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_VERIFY_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_NOTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
	}
}



void CDlgVcaBVCalibrate::OnBtnGetPictureInfo()
{
    // TODO: Add your control notification handler code here

    //NET_DVR_GET_BV_CALIB_PIC
    UpdateData(TRUE);
    NET_DVR_BV_CALIB_COND struBvCalibCond = { 0 };
    struBvCalibCond.dwSize = sizeof(struBvCalibCond);
    struBvCalibCond.dwChannels = m_lChannel;
    DWORD dwStatusList = 0;

    m_struBvCalibPic.dwSize = sizeof(m_struBvCalibPic);
    m_struBvCalibPic.pPicBuffer1 = new char[640 * 960 * 1.5];
    m_struBvCalibPic.pPicBuffer2 = new char[640 * 960 * 1.5];
    if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_BV_CALIB_PIC, 1, &struBvCalibCond, sizeof(struBvCalibCond), &dwStatusList, &m_struBvCalibPic, sizeof(m_struBvCalibPic)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_CALIB_PIC Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_CALIB_PIC Chan[%d]", m_lChannel);
        return;
    }
    m_dwPicID = m_struBvCalibPic.dwPicID;
    m_dwPicLen = m_struBvCalibPic.dwPicLen1;
    char* pAddress = "c:\\BvCalibPic.jpeg";
    m_csSaveAddress = pAddress;
    UpdateData(FALSE);

    //CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))WritePictureData, (LPVOID)this, 0, NULL);

    char cFilename[256] = { 0 };
    HANDLE hFile;
    DWORD dwReturn;

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    sprintf(cFilename, "%s", g_struLocalParam.chPictureSavePath);
    if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
    {
        CreateDirectory(cFilename, NULL);
    }

    sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());
    hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "picname1:%s", cFilename);
    WriteFile(hFile, m_struBvCalibPic.pPicBuffer1, m_struBvCalibPic.dwPicLen1, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    delete[]m_struBvCalibPic.pPicBuffer1;
    m_struBvCalibPic.pPicBuffer1 = NULL;

    sprintf(cFilename, "%s(2)", cFilename);
    hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "picname2:%s", cFilename);
    WriteFile(hFile, m_struBvCalibPic.pPicBuffer2, m_struBvCalibPic.dwPicLen2, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    delete[]m_struBvCalibPic.pPicBuffer2;
    m_struBvCalibPic.pPicBuffer2 = NULL;
}

void CDlgVcaBVCalibrate::OnBtnSaveVcaPoint()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struBvCalibInfo.struBVCalibParam[m_comParamNumber.GetCurSel()].dwPicID = m_dwBvPicID;
    m_struBvCalibInfo.struBVCalibParam[m_comParamNumber.GetCurSel()].struPoint.fX = m_fPointX;
    m_struBvCalibInfo.struBVCalibParam[m_comParamNumber.GetCurSel()].struPoint.fY = m_fPointY;
    UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnBtnGetBvCalibResult()
{
    // TODO: Add your control notification handler code here
    //NET_DVR_GET_BV_CALIB_RESULT
    UpdateData(TRUE);
    m_struBvCalibInfo.dwSize = sizeof(m_struBvCalibInfo);
    m_struBvCalibInfo.dwBVCalibNumber = m_dwVcaNumber;
    m_struBvCalibInfo.dwHumanHeight = m_dwHumanHeight;
    m_struBvCalibInfo.dwChannel = m_lChannel;
    DWORD dwStatusList = 0;
    NET_DVR_BV_CALIB_RESULT struBvCalibResult = { 0 };
    struBvCalibResult.dwSize = sizeof(struBvCalibResult);
    if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_BV_CALIB_RESULT, 1, &m_struBvCalibInfo, sizeof(m_struBvCalibInfo), &dwStatusList, &struBvCalibResult, sizeof(struBvCalibResult)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_CALIB_RESULT Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_CALIB_RESULT Chan[%d]", m_lChannel);
        return;
    }
    m_dwCameraHeightBv = struBvCalibResult.dwCameraHeight;
    m_fPitchAngleBv = struBvCalibResult.fPitchAngle;
    m_fInclineAngleBv = struBvCalibResult.fInclineAngle;
    UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnSelchangeComboParamNumber()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_dwBvPicID = m_struBvCalibInfo.struBVCalibParam[m_comParamNumber.GetCurSel()].dwPicID;
    m_fPointX = m_struBvCalibInfo.struBVCalibParam[m_comParamNumber.GetCurSel()].struPoint.fX;
    m_fPointY = m_struBvCalibInfo.struBVCalibParam[m_comParamNumber.GetCurSel()].struPoint.fY;
    UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnBtnGetBvHcorrection()
{
    // TODO: Add your control notification handler code here
    //NET_DVR_GET_BV_HCORRECTION
    UpdateData(TRUE);
    NET_DVR_BV_HCORRECTION_COND struBvHcorrectionCond = { 0 };
    struBvHcorrectionCond.dwSize = sizeof(struBvHcorrectionCond);
    struBvHcorrectionCond.dwChannels = m_lChannel;
    struBvHcorrectionCond.dwPicID = m_dwHcorrectionPictureID;
    DWORD dwStatusList = 0;
    NET_DVR_BV_HCORRECTION_CFG struBvHcorrectionCfg = { 0 };
    struBvHcorrectionCfg.dwSize = sizeof(struBvHcorrectionCfg);
    if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_BV_HCORRECTION, 1, &struBvHcorrectionCond, sizeof(struBvHcorrectionCond), &dwStatusList, &struBvHcorrectionCfg, sizeof(struBvHcorrectionCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_HCORRECTION Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_HCORRECTION Chan[%d]", m_lChannel);
        return;
    }
    m_dwHcorrectionHumanHeight = struBvHcorrectionCfg.dwHumanHeight;
    UpdateData(FALSE);
}

void WINAPI CDlgVcaBVCalibrate::WritePictureData(LPVOID pM)
{
    //     CDlgVcaBVCalibrate *pVcaBVCalibrate = (CDlgVcaBVCalibrate *)pM;
    //     char* pAddress = "c:\\BvCalibPic.jpg";
    //     
    //     FILE *fp = fopen(pAddress, "wb");
    //     if (fp == NULL)
    //     {
    //         return;
    //     }
    //     
    //     if (pVcaBVCalibrate->m_struBvCalibPic.pPicBuffer == NULL)
    //     {
    //         return;
    //     }
    //     
    //     int iCount = pVcaBVCalibrate->m_struBvCalibPic.dwPicLen/1000;
    //     char* pBuffer = pVcaBVCalibrate->m_struBvCalibPic.pPicBuffer;
    //     for (int i = 0; i<iCount; ++i)
    //     {
    //         int res = 0;
    //         int wri = 1000;//pVcaBVCalibrate->m_struBvCalibPic.dwPicLen;
    //         
    //         while (1)
    //         {
    //             if((res=fwrite(pBuffer, 1, wri, fp)) != wri)
    //             {
    //                 wri -= res;
    //                 pBuffer += res;
    //             }
    //             else
    //             {
    //                 pBuffer += res;
    //                 break;
    //             }
    //         }
    //     }
    // 
    //     int res = 0;
    //     int wri = pVcaBVCalibrate->m_struBvCalibPic.dwPicLen%1000;//pVcaBVCalibrate->m_struBvCalibPic.dwPicLen;
    //     
    //     while (1)
    //     {
    //         if((res=fwrite(pBuffer, 1, wri, fp)) != wri)
    //         {
    //             wri -= res;
    //             pBuffer += res;
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }
    //     
    //     
    //     if(fclose(fp))
    //     {
    //         return;
    //     }
    //     fp = NULL;
    // 
    //     if (pVcaBVCalibrate->m_struBvCalibPic.pPicBuffer != NULL)
    //     {
    //         delete []pVcaBVCalibrate->m_struBvCalibPic.pPicBuffer;
    //         pVcaBVCalibrate->m_struBvCalibPic.pPicBuffer = NULL;
    //     }

}

void CDlgVcaBVCalibrate::OnButtonDelBvCalibPic()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_BV_HCORRECTION_COND struBvHcorrectionCond = { 0 };
    struBvHcorrectionCond.dwSize = sizeof(struBvHcorrectionCond);
    struBvHcorrectionCond.dwChannels = m_lChannel;
    struBvHcorrectionCond.dwPicID = m_dwHcorrectionPictureID;

    if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_DEL_BV_CALIB_PIC, &struBvHcorrectionCond, sizeof(struBvHcorrectionCond)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_BV_CALIB_PIC FAILED");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_BV_CALIB_PIC SUCC");
    }
}

