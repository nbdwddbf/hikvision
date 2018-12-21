// DlgPanoramaImage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPanoramaImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPanoramaImage dialog


CDlgPanoramaImage::CDlgPanoramaImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPanoramaImage::IDD, pParent)
    , m_byBrightness(0)
{
	//{{AFX_DATA_INIT(CDlgPanoramaImage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    memset(&m_struPanoramaImage, 0, sizeof(m_struPanoramaImage));

    m_lChannel = -1;
    m_lUserID = -1;
    m_iDeviceIndex = -1;
    m_iAdjustmentRange = -1;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    n_byR = 0;
    m_byG = 0;
    m_byB = 0;
}


void CDlgPanoramaImage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPanoramaImage)
    //DDX_Control(pDX, IDC_COMBO_FUSION_WAY, m_comFusionWay);
    DDX_Control(pDX, IDC_COMBO_FUSION_MODE, m_comFusionMode);
    DDX_Control(pDX, IDC_COMBO_TYPE, m_comType);
    DDX_Control(pDX, IDC_COMBO_SENSOR_NO, m_comSensorNo);
    DDX_Text(pDX, IDC_EDIT_ADJUSTMENT_RANGE, m_iAdjustmentRange);
    DDX_Text(pDX, IDC_EDIT_R, n_byR);
    DDX_Text(pDX, IDC_EDIT_G, m_byG);
    DDX_Text(pDX, IDC_EDIT_B, m_byB);
    //}}AFX_DATA_MAP


    DDX_Control(pDX, IDC_COMBO_RGB_TYPE, m_cmbRgbType);
    DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_byBrightness);
    DDX_Control(pDX, IDC_COMBO_PREVIEW_MODE, m_cmbPreviewMode);
}


BEGIN_MESSAGE_MAP(CDlgPanoramaImage, CDialog)
	//{{AFX_MSG_MAP(CDlgPanoramaImage)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
    ON_BN_CLICKED(IDC_BTN_ADJUSTMENT, OnBtnSensorAdjustment)
    ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
    ON_BN_CLICKED(IDC_BTN_SENSOR_INFO, OnBtnSensorInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPanoramaImage message handlers

void CDlgPanoramaImage::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struPanoramaImage.dwSize = sizeof(m_struPanoramaImage);
  
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struPanoramaImage;
    struCfg.dwOutSize = sizeof(m_struPanoramaImage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_PANORAMAIMAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PANORAMAIMAGE");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PANORAMAIMAGE");
    }

    m_comFusionMode.SetCurSel(m_struPanoramaImage.byFusionMode);
    //m_comFusionWay.SetCurSel(m_struPanoramaImage.byFusionWay);
    m_cmbPreviewMode.SetCurSel(m_struPanoramaImage.byPreviewMode);
    UpdateData(FALSE);	
}

void CDlgPanoramaImage::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_struPanoramaImage.byFusionMode = m_comFusionMode.GetCurSel();
    //m_struPanoramaImage.byFusionWay = m_comFusionWay.GetCurSel();
    m_struPanoramaImage.byPreviewMode = m_cmbPreviewMode.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struPanoramaImage;
    struCfg.dwInSize = sizeof(m_struPanoramaImage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_PANORAMAIMAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PANORAMAIMAGE");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PANORAMAIMAGE");
    }
}

void CDlgPanoramaImage::OnBtnSensorAdjustment() 
{
    UpdateData(TRUE);
    char szLan[128] = {0};
    NET_DVR_SENSOR_ADJUSTMENT m_struSensorAdjustment = {0};
    m_struSensorAdjustment.dwSize = sizeof(m_struSensorAdjustment);
    m_struSensorAdjustment.byType = m_comType.GetCurSel();
    m_struSensorAdjustment.bySensorNo = m_comSensorNo.GetCurSel()+1;
    m_struSensorAdjustment.iAdjustMentRange = m_iAdjustmentRange;
    m_struSensorAdjustment.byR = n_byR;
    m_struSensorAdjustment.byG = m_byG;
    m_struSensorAdjustment.byB = m_byB;
    m_struSensorAdjustment.byBrightness = m_byBrightness;
    m_struSensorAdjustment.byRgbType = m_cmbRgbType.GetCurSel();
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struSensorAdjustment;
    struControl.dwCondSize = sizeof(m_struSensorAdjustment);
    
    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
    
    if(!NET_DVR_STDControl(m_lUserID, NET_DVR_SET_SENSOR_ADJUSTMENT, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SENSOR_ADJUSTMENT");
//         sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
//         AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SENSOR_ADJUSTMENT");
    }
}

void CDlgPanoramaImage::OnBtnReset() 
{
    UpdateData(TRUE);
    char szLan[128] = {0};
    NET_DVR_SENSOR_RESET m_struSensorReset = {0};
    m_struSensorReset.dwSize = sizeof(m_struSensorReset);
    m_struSensorReset.bySensorNo = m_comSensorNo.GetCurSel()+1;
  
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struSensorReset;
    struControl.dwCondSize = sizeof(m_struSensorReset);
    
    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
    
    if(!NET_DVR_STDControl(m_lUserID, NET_DVR_SENSOR_RESET_CTRL, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SENSOR_RESET_CTRL");
        //         sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        //         AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SENSOR_RESET_CTRL");
    }
}

void CDlgPanoramaImage::OnBtnSensorInfo()
{
    UpdateData(TRUE);
    NET_DVR_SENSOR_ADJUSTMENT_INFO m_struSensorAdjustmentInfo = {0};
    m_struSensorAdjustmentInfo.dwSize = sizeof(m_struSensorAdjustmentInfo);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    int iSensorNo = m_comSensorNo.GetCurSel()+1;
    struCfg.lpCondBuffer = &iSensorNo;
    struCfg.dwCondSize = sizeof(int);

    struCfg.lpOutBuffer = &m_struSensorAdjustmentInfo;
    struCfg.dwOutSize = sizeof(m_struSensorAdjustmentInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_SENSOR_ADJUSTMENT_INFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SENSOR_ADJUSTMENT_INFO");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SENSOR_ADJUSTMENT_INFO");
    }
    char szAdjustmentInfo[1024] = {0};
    sprintf(szAdjustmentInfo, "dwSize:%d,iPan:%d,iTilt:%d,iRotation:%d,iFieldAngle:%d,RgbType:%d,R:%d,G:%d,B:%d£¬Brightness£º%d", \
        m_struSensorAdjustmentInfo.dwSize, m_struSensorAdjustmentInfo.iPan, m_struSensorAdjustmentInfo.iTilt, \
        m_struSensorAdjustmentInfo.iRotation, m_struSensorAdjustmentInfo.iFieldAngle, m_struSensorAdjustmentInfo.byRgbType,
        m_struSensorAdjustmentInfo.byR, m_struSensorAdjustmentInfo.byG, m_struSensorAdjustmentInfo.byB, m_struSensorAdjustmentInfo.byBrightness);
    MessageBox(szAdjustmentInfo);
    return;
}
