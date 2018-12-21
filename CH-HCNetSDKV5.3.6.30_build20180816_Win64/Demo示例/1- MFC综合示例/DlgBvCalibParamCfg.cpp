// DlgBvCalibParamCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgBvCalibParamCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBvCalibParamCfg dialog


CDlgBvCalibParamCfg::CDlgBvCalibParamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBvCalibParamCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBvCalibParamCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginID  = -1;
	m_iDevIndex = -1;
	m_lChannel  = -1;
    
	memset(m_fReprojectMatrix,   0,sizeof(m_fReprojectMatrix));
	memset(m_fLCamInternalMatrix,0,sizeof(m_fLCamInternalMatrix));
	memset(m_fLDistCoeffs,       0,sizeof(m_fLDistCoeffs));
	memset(m_fLRotateMatrix,     0,sizeof(m_fLRotateMatrix));
	memset(m_fLProjectMatrix,    0,sizeof(m_fLProjectMatrix));
	memset(m_fRCamInternalMatrix,0,sizeof(m_fRCamInternalMatrix));
	memset(m_fRDistCoeffs,       0,sizeof(m_fRDistCoeffs));
	memset(m_fRRotateMatrix,     0,sizeof(m_fRRotateMatrix));
	memset(m_fRProjectMatrix,    0,sizeof(m_fRProjectMatrix));
	memset(&m_struBvCalibParam,  0,sizeof(m_struBvCalibParam));

    memset(m_fRotateMatrix, 0, sizeof(m_fRotateMatrix));
    memset(m_fTransMatrix, 0, sizeof(m_fTransMatrix));
	m_struBvCalibParam.dwSize = sizeof(m_struBvCalibParam);
}


void CDlgBvCalibParamCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBvCalibParamCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_1,m_fReprojectMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_2,m_fReprojectMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_3,m_fReprojectMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_4,m_fReprojectMatrix[0][3]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_1,m_fReprojectMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_2,m_fReprojectMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_3,m_fReprojectMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_4,m_fReprojectMatrix[1][3]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_1,m_fReprojectMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_2,m_fReprojectMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_3,m_fReprojectMatrix[2][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_4,m_fReprojectMatrix[2][3]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_1,m_fReprojectMatrix[3][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_2,m_fReprojectMatrix[3][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_3,m_fReprojectMatrix[3][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_4,m_fReprojectMatrix[3][3]);


	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_1_1,m_fLCamInternalMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_1_2,m_fLCamInternalMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_1_3,m_fLCamInternalMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_2_1,m_fLCamInternalMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_2_2,m_fLCamInternalMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_2_3,m_fLCamInternalMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_3_1,m_fLCamInternalMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_3_2,m_fLCamInternalMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_3_3,m_fLCamInternalMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_1_1,m_fRCamInternalMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_1_2,m_fRCamInternalMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_1_3,m_fRCamInternalMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_2_1,m_fRCamInternalMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_2_2,m_fRCamInternalMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_2_3,m_fRCamInternalMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_3_1,m_fRCamInternalMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_3_2,m_fRCamInternalMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_3_3,m_fRCamInternalMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_1,m_fLDistCoeffs[0]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_2,m_fLDistCoeffs[1]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_3,m_fLDistCoeffs[2]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_4,m_fLDistCoeffs[3]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_5,m_fLDistCoeffs[4]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_6,m_fLDistCoeffs[5]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_7,m_fLDistCoeffs[6]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_8,m_fLDistCoeffs[7]);

	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_1,m_fRDistCoeffs[0]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_2,m_fRDistCoeffs[1]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_3,m_fRDistCoeffs[2]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_4,m_fRDistCoeffs[3]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_5,m_fRDistCoeffs[4]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_6,m_fRDistCoeffs[5]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_7,m_fRDistCoeffs[6]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_8,m_fRDistCoeffs[7]);

	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_1_1,m_fLRotateMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_1_2,m_fLRotateMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_1_3,m_fLRotateMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_2_1,m_fLRotateMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_2_2,m_fLRotateMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_2_3,m_fLRotateMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_3_1,m_fLRotateMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_3_2,m_fLRotateMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_3_3,m_fLRotateMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_1_1,m_fRRotateMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_1_2,m_fRRotateMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_1_3,m_fRRotateMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_2_1,m_fRRotateMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_2_2,m_fRRotateMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_2_3,m_fRRotateMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_3_1,m_fRRotateMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_3_2,m_fRRotateMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_3_3,m_fRRotateMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_1,m_fLProjectMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_2,m_fLProjectMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_3,m_fLProjectMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_4,m_fLProjectMatrix[0][3]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_1,m_fLProjectMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_2,m_fLProjectMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_3,m_fLProjectMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_4,m_fLProjectMatrix[1][3]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_1,m_fLProjectMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_2,m_fLProjectMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_3,m_fLProjectMatrix[2][2]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_4,m_fLProjectMatrix[2][3]);

	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_1,m_fRProjectMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_2,m_fRProjectMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_3,m_fRProjectMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_4,m_fRProjectMatrix[0][3]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_1,m_fRProjectMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_2,m_fRProjectMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_3,m_fRProjectMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_4,m_fRProjectMatrix[1][3]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_1,m_fRProjectMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_2,m_fRProjectMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_3,m_fRProjectMatrix[2][2]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_4,m_fRProjectMatrix[2][3]);

    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_1_1, m_fRotateMatrix[0][0]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_1_2, m_fRotateMatrix[0][1]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_1_3, m_fRotateMatrix[0][2]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_2_1, m_fRotateMatrix[1][0]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_2_2, m_fRotateMatrix[1][1]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_2_3, m_fRotateMatrix[1][2]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_3_1, m_fRotateMatrix[2][0]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_3_2, m_fRotateMatrix[2][1]);
    DDX_Text(pDX, IDC_EDIT_ROTATE_MATRIX_3_3, m_fRotateMatrix[2][2]);

    DDX_Text(pDX, IDC_EDIT_TRANS_MATRIX_1, m_fTransMatrix[0]);
    DDX_Text(pDX, IDC_EDIT_TRANS_MATRIX_2, m_fTransMatrix[1]);
    DDX_Text(pDX, IDC_EDIT_TRANS_MATRIX_3, m_fTransMatrix[2]);
 
	DDX_Control(pDX, IDC_COMBO_LENS_TYPE, m_comLensType);
}


BEGIN_MESSAGE_MAP(CDlgBvCalibParamCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgBvCalibParamCfg)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgBvCalibParamCfg::OnBnClickedButtonExport)
    ON_BN_CLICKED(IDOK, &CDlgBvCalibParamCfg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBvCalibParamCfg message handlers
BOOL CDlgBvCalibParamCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comLensType.SetCurSel(0);
    if (GetBvCalibParam())
	{
		LoadWndContent();
	}
	else
	{   
		char szError[32] = "\0";
		g_StringLanType(szError, "获取图像校正参数失败","Get bv calib param failed");
		AfxMessageBox(szError);
	}
	return TRUE;
}

void CDlgBvCalibParamCfg::OnOK() 
{   
	if (!UpdateData(TRUE))
	{
		return;
	}
	SaveWndContent();
	char szError[32] = "\0";
	if (SetBvCalibParam())
	{
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}


BOOL CDlgBvCalibParamCfg::GetBvCalibParam()
{   
	DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_BV_CORRECT_PARAM, m_lChannel, &m_struBvCalibParam, sizeof(m_struBvCalibParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgBvCalibParamCfg::SetBvCalibParam()
{
	BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_BV_CORRECT_PARAM, m_lChannel, &m_struBvCalibParam, sizeof(m_struBvCalibParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgBvCalibParamCfg::LoadWndContent()
{   
	memcpy(m_fReprojectMatrix,   m_struBvCalibParam.fReprojectMatrix                ,sizeof(m_fReprojectMatrix));
	memcpy(m_fLCamInternalMatrix,m_struBvCalibParam.struLCamParam.fCamInternalMatrix,sizeof(m_fLCamInternalMatrix));
	memcpy(m_fLDistCoeffs,       m_struBvCalibParam.struLCamParam.fDistCoeffs       ,sizeof(m_fLDistCoeffs));
	memcpy(m_fLRotateMatrix,     m_struBvCalibParam.struLCamParam.fRotateMatrix     ,sizeof(m_fLRotateMatrix));
	memcpy(m_fLProjectMatrix,    m_struBvCalibParam.struLCamParam.fProjectMatrix    ,sizeof(m_fLProjectMatrix));
	memcpy(m_fRCamInternalMatrix,m_struBvCalibParam.struRCamParam.fCamInternalMatrix,sizeof(m_fRCamInternalMatrix));
	memcpy(m_fRDistCoeffs,       m_struBvCalibParam.struRCamParam.fDistCoeffs       ,sizeof(m_fRDistCoeffs));
	memcpy(m_fRRotateMatrix,     m_struBvCalibParam.struRCamParam.fRotateMatrix     ,sizeof(m_fRRotateMatrix));
	memcpy(m_fRProjectMatrix,    m_struBvCalibParam.struRCamParam.fProjectMatrix    ,sizeof(m_fRProjectMatrix));
	m_comLensType.SetCurSel(m_struBvCalibParam.byLensType);
    memcpy(m_fRotateMatrix, m_struBvCalibParam.fRotateMatrix, sizeof(m_fRotateMatrix));
    memcpy(m_fTransMatrix, m_struBvCalibParam.fTransMatrix, sizeof(m_fTransMatrix));
	UpdateData(FALSE);
}

void CDlgBvCalibParamCfg::SaveWndContent()
{   
	UpdateData(TRUE);
	memcpy(m_struBvCalibParam.fReprojectMatrix                ,m_fReprojectMatrix    ,sizeof(m_fReprojectMatrix));
	memcpy(m_struBvCalibParam.struLCamParam.fCamInternalMatrix,m_fLCamInternalMatrix ,sizeof(m_fLCamInternalMatrix));
	memcpy(m_struBvCalibParam.struLCamParam.fDistCoeffs       ,m_fLDistCoeffs        ,sizeof(m_fLDistCoeffs));
	memcpy( m_struBvCalibParam.struLCamParam.fRotateMatrix    ,m_fLRotateMatrix      ,sizeof(m_fLRotateMatrix));
	memcpy(m_struBvCalibParam.struLCamParam.fProjectMatrix    ,m_fLProjectMatrix     ,sizeof(m_fLProjectMatrix));
	memcpy(m_struBvCalibParam.struRCamParam.fCamInternalMatrix,m_fRCamInternalMatrix ,sizeof(m_fRCamInternalMatrix));
	memcpy(m_struBvCalibParam.struRCamParam.fDistCoeffs       ,m_fRDistCoeffs        ,sizeof(m_fRDistCoeffs));
	memcpy(m_struBvCalibParam.struRCamParam.fRotateMatrix     ,m_fRRotateMatrix      ,sizeof(m_fRRotateMatrix));
	memcpy(m_struBvCalibParam.struRCamParam.fProjectMatrix    ,m_fRProjectMatrix     ,sizeof(m_fRProjectMatrix));
	m_struBvCalibParam.byLensType = m_comLensType.GetCurSel();
    memcpy(m_struBvCalibParam.fRotateMatrix, m_fRotateMatrix, sizeof(m_fRotateMatrix));
    memcpy(m_struBvCalibParam.fTransMatrix, m_fTransMatrix, sizeof(m_fTransMatrix));
}

//获取相机校正参数
bool CDlgBvCalibParamCfg::getBVCorrectParam(NET_DVR_BV_CORRECT_PARAM &bv_correct_param)
{
    DWORD dwOutLength = 0;
    bool ret = NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_BV_CORRECT_PARAM, 1, &bv_correct_param, sizeof(NET_DVR_BV_CORRECT_PARAM), &dwOutLength);
    if (!ret)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        return false;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        return true;
    }
}

//将内参由SDK结构体转换为BV
bool CDlgBvCalibParamCfg::toolChangeDvrToBvCalib(NET_DVR_BV_CORRECT_PARAM dvr_calib_param, BV_CALIB_PARAM &bv_calib)
{
    char szLan[128] = { 0 };
    float offset = 0;
    if (dvr_calib_param.byLensType == 7 || dvr_calib_param.byLensType == 9 || dvr_calib_param.byLensType == 10)
    {
        offset = 0.f;
    }
    else if (dvr_calib_param.byLensType == 8)
    {
        offset = 1000.f;
    }
    else if (dvr_calib_param.byLensType == 2)
    {
        offset = 3000.f;
    }
    else
    {
        sprintf(szLan, "镜头焦距值有误!设备可能为进行标定!\n镜头焦距类型为：%d", dvr_calib_param.byLensType);
        MessageBox(szLan);
        //return false; //todo debug 发布时需要放开注释
    }

    memcpy(bv_calib.reproject_mat,
        dvr_calib_param.fReprojectMatrix,
        sizeof(bv_calib.reproject_mat));

    memcpy(bv_calib.l_cam_param.cam_internal_mat,
        dvr_calib_param.struLCamParam.fCamInternalMatrix,
        sizeof(bv_calib.l_cam_param.cam_internal_mat));

    memcpy(bv_calib.l_cam_param.dist_coeffs,
        dvr_calib_param.struLCamParam.fDistCoeffs,
        sizeof(bv_calib.l_cam_param.dist_coeffs));

    memcpy(bv_calib.l_cam_param.project_mat,
        dvr_calib_param.struLCamParam.fProjectMatrix,
        sizeof(bv_calib.l_cam_param.project_mat));

    memcpy(bv_calib.l_cam_param.rotate_mat,
        dvr_calib_param.struLCamParam.fRotateMatrix,
        sizeof(bv_calib.l_cam_param.rotate_mat));

    memcpy(bv_calib.r_cam_param.cam_internal_mat,
        dvr_calib_param.struRCamParam.fCamInternalMatrix,
        sizeof(bv_calib.r_cam_param.cam_internal_mat));

    memcpy(bv_calib.r_cam_param.dist_coeffs,
        dvr_calib_param.struRCamParam.fDistCoeffs,
        sizeof(bv_calib.r_cam_param.dist_coeffs));

    memcpy(bv_calib.r_cam_param.project_mat,
        dvr_calib_param.struRCamParam.fProjectMatrix,
        sizeof(bv_calib.r_cam_param.project_mat));

    memcpy(bv_calib.r_cam_param.rotate_mat,
        dvr_calib_param.struRCamParam.fRotateMatrix,
        sizeof(bv_calib.r_cam_param.rotate_mat));

    memcpy(bv_calib.rot,
        dvr_calib_param.fRotateMatrix,
        sizeof(bv_calib.rot));

    memcpy(bv_calib.trans,
        dvr_calib_param.fTransMatrix,
        sizeof(bv_calib.trans));

  //  memset(bv_calib.rot, 0, sizeof(bv_calib.rot));
   // memset(bv_calib.trans, 0, sizeof(bv_calib.trans));

    // 数值修正，防止SDK传输溢出
    bv_calib.reproject_mat[2][3] += offset;

    bv_calib.l_cam_param.cam_internal_mat[0][0] += offset;
    bv_calib.l_cam_param.cam_internal_mat[1][1] += offset;
    bv_calib.r_cam_param.cam_internal_mat[0][0] += offset;
    bv_calib.r_cam_param.cam_internal_mat[1][1] += offset;

    bv_calib.l_cam_param.project_mat[0][0] += offset;
    bv_calib.l_cam_param.project_mat[1][1] += offset;
    bv_calib.r_cam_param.project_mat[0][0] += offset;
    bv_calib.r_cam_param.project_mat[1][1] += offset;

    return true;
}

//导出标定数据到文件
bool CDlgBvCalibParamCfg::toolExportCalibParamToTxt(char *calib_rst_file_path, BV_CALIB_PARAM calib_param, float focalLenth)
{
    int     i, j;
    FILE   *file;

    fopen_s(&file, calib_rst_file_path, "w+");

    fprintf_s(file, "M_l:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.l_cam_param.cam_internal_mat[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "M_r:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.r_cam_param.cam_internal_mat[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "D_l:\n");
    for (i = 0; i < 8; i++)
    {
        fprintf_s(file, "%4.6f ", calib_param.l_cam_param.dist_coeffs[i]);
    }
    fprintf_s(file, "\n\n");

    fprintf_s(file, "D_r:\n");
    for (i = 0; i < 8; i++)
    {
        fprintf_s(file, "%4.6f ", calib_param.r_cam_param.dist_coeffs[i]);
    }
    fprintf_s(file, "\n\n");

    fprintf_s(file, "R:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.rot[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "T:\n");
    for (i = 0; i < 3; i++)
    {
        fprintf_s(file, "%4.6f ", calib_param.trans[i]);
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "R_l:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.l_cam_param.rotate_mat[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "R_r:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.r_cam_param.rotate_mat[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "P_l:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.l_cam_param.project_mat[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "P_r:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.r_cam_param.project_mat[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "Q:\n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            fprintf_s(file, "%4.6f ", calib_param.reproject_mat[i][j]);
        }
        fprintf_s(file, "\n");
    }
    fprintf_s(file, "\n");

    fprintf_s(file, "focalLenth: %0.1fmm\n", focalLenth);

    fclose(file);

    return true;
}

CString CDlgBvCalibParamCfg::BrowseFolderParam(HWND hWnd, LPCTSTR lpTitle)
{

    char szPath[MAX_PATH] = { 0 };
    BROWSEINFO m_bi;

    m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    m_bi.hwndOwner = hWnd;
    m_bi.pidlRoot = NULL;
    m_bi.lpszTitle = lpTitle;
    m_bi.lpfn = NULL;
    m_bi.lParam = NULL;
    m_bi.pszDisplayName = szPath;

    LPITEMIDLIST pidl = ::SHBrowseForFolder(&m_bi);
    if (pidl)
    {
        if (!::SHGetPathFromIDList(pidl, szPath))
        {
            szPath[0] = 0;
        }

        IMalloc * pMalloc = NULL;
        if (SUCCEEDED(::SHGetMalloc(&pMalloc)))  // 取得IMalloc分配器接口
        {
            pMalloc->Free(pidl);    // 释放内存
            pMalloc->Release();       // 释放接口
        }
    }
    return szPath;
}

//导出设备内参
void CDlgBvCalibParamCfg::OnBnClickedButtonExport()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[MAX_PATH] = { 0 };
    char szTemp[512] = { 0 };
    NET_DVR_BV_CORRECT_PARAM bv_correct_param;
    BV_CALIB_PARAM bv_calib;
    if (!getBVCorrectParam(bv_correct_param))
    {
        MessageBox("获取设备内参失败!");
        return;
    }
    if (!toolChangeDvrToBvCalib(bv_correct_param, bv_calib))
    {
        MessageBox("内参转换失败!");
        return;
    }

    CString strFilePath = _T("");
    strFilePath = BrowseFolderParam(this->m_hWnd, "选择目录");
    if (strFilePath.IsEmpty())
    {
        MessageBox("保存文件路径不能为空");
        return;
    }

    CTime ctime = CTime::GetCurrentTime();

    sprintf(szLan, "%s\\%d_%d_%d_%d_%d_%d_%d_CalibParam.txt", strFilePath, ctime.GetYear(),
        ctime.GetMonth(), ctime.GetDay(), ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond(), ctime.GetTickCount);

    float focalLenth = 0.0f;
    //qDebug()<<"bv_correct_param.byLensType:"<<bv_correct_param.byLensType;
    switch (bv_correct_param.byLensType)//0-未知,1-8mm,2-12mm,3-16mm,4-25mm,5-35mm,6-50mm,7-4mm,8-6mm，9-2.0mm，10-2.8mm
    {
    case 1:
        focalLenth = 8;
        break;
    case 2:
        focalLenth = 12;
        break;
    case 3:
        focalLenth = 16;
        break;
    case 4:
        focalLenth = 25;
        break;
    case 5:
        focalLenth = 35;
        break;
    case 6:
        focalLenth = 50;
        break;
    case 7:
        focalLenth = 4;
        break;
    case 8:
        focalLenth = 6;
        break;
    case 9:
        focalLenth = 2;
        break;
    case 10:
        focalLenth = 2.8;
        break;
    default:
        break;
    }
    //qDebug()<<"focalLenth:"<<focalLenth;
    if (toolExportCalibParamToTxt(szLan, bv_calib, focalLenth))
    {
        sprintf(szTemp, "导出成功!\n文件路径为：%s", szLan);
        MessageBox(szTemp);
    }
    else
    {
        MessageBox("导出失败!");
    }
}


void CDlgBvCalibParamCfg::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgBvCalibParamCfg::OnOK();
}
