// DlgVcaChanCtrlCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaChanCtrlCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChanCtrlCfg dialog



CDlgVcaChanCtrlCfg::CDlgVcaChanCtrlCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaChanCtrlCfg::IDD, pParent)
    , m_iRelatedChan1(0)
    , m_iRelatedChan2(0)
    , m_iRelatedChan3(0)
    , m_iRelatedChan4(0)
{
	//{{AFX_DATA_INIT(CDlgVcaChanCtrlCfg)
	m_bChkStreamWithVca = FALSE;
	m_bChkEnable = FALSE;
	//}}AFX_DATA_INIT
	m_iVcaChannel = -1;
	m_bSupportChanEx = FALSE;
	memset(&m_struVcaCtrlInfo, 0, sizeof(m_struVcaCtrlInfo));
    memset(&m_struVcaCtrlCfg, 0, sizeof(m_struVcaCtrlCfg));
}


void CDlgVcaChanCtrlCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaChanCtrlCfg)
	DDX_Control(pDX, IDC_COMBO_VCA_MODE, m_comboVcaMode);
	DDX_Control(pDX, IDC_COMBO_CHAN_VCATYPE, m_comboChanVcaType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChan);
	DDX_Check(pDX, IDC_CHK_STREAM_WITH_VCA, m_bChkStreamWithVca);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL1, m_iRelatedChan1);
    DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL2, m_iRelatedChan2);
    DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL3, m_iRelatedChan3);
    DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL4, m_iRelatedChan4);
}


BEGIN_MESSAGE_MAP(CDlgVcaChanCtrlCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaChanCtrlCfg)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN_VCATYPE, OnSelchangeComboChanVcatype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChanCtrlCfg message handlers
BOOL CDlgVcaChanCtrlCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	char szLan[128] = {0};
    
	g_AddChanInfoToComBox(m_comboChan,m_iDevIndex, FALSE);
	
	memset(&m_struVcaDevAbility, 0, sizeof(NET_VCA_DEV_ABILITY));
	if(!NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDevIndex].lLoginID,  VCA_DEV_ABILITY, NULL, 0, (char*)&m_struVcaDevAbility, sizeof(NET_VCA_DEV_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_DEV_ABILITY");
		g_StringLanType(szLan, "设备不支持", "Device does not support");
		AfxMessageBox(szLan);
        return FALSE;
	}
	else 
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_DEV_ABILITY");
    }
	
	m_bSupportChanEx = (m_struVcaDevAbility.bySupport>>1)&1;
    
    m_comboChanVcaType.ResetContent();
    int index = 0;
    if (m_struVcaDevAbility.byBBaseChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析基本版", "Behavior of basic");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_BASE);
        index++;
    }
    if (m_struVcaDevAbility.byBAdvanceChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析高级版", "Behavior of advanced");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_ADVANCE);
        index++;
    }
    if (m_struVcaDevAbility.byBFullChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析完整版", "Behavior of full");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_FULL);
        index++;
    }
    if (m_struVcaDevAbility.byPlateChanNum> 0)
    {   
		g_StringLanType(szLan, "车牌识别", "Plate Recognition");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_PLATE);
        index++;
    }
    if (m_struVcaDevAbility.byATMChanNum > 0)
    {
        m_comboChanVcaType.InsertString(index, "ATM");
        m_comboChanVcaType.SetItemData(index, VCA_ATM);
        index++;
    }
	if (m_struVcaDevAbility.byPDCChanNum > 0)
    {   
		g_StringLanType(szLan, "客流统计", "PDC");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_PDC);
        index++;
    }
    if (m_struVcaDevAbility.byITSChanNum > 0)
    {;
		g_StringLanType(szLan, "交通事件", "ITS");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_ITS);
        index++;
    }
    
    if (m_struVcaDevAbility.byBPrisonChanNum > 0)
    {   
		g_StringLanType(szLan, "行为监狱版(监舍)", "Behavior of prison");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_PRISON);
        index++;
    }	

	if (m_struVcaDevAbility.byFSnapChanNum > 0)
	{   
		g_StringLanType(szLan, "人脸抓拍", "Face Snap");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_FACE_SNAP);
        index++;
	}
	
	if (m_struVcaDevAbility.byFSnapRecogChanNum > 0)
	{   
		g_StringLanType(szLan, "人脸抓拍与识别", "Face Snap and Recognition");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_FACE_SNAPRECOG);
        index++;
	}
	
	if (m_struVcaDevAbility.byFRetrievalChanNum > 0)
	{
		g_StringLanType(szLan, "人脸后检索", "Face Retrieval");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_FACE_RETRIEVAL);
        index++;
	}
	
	if (m_struVcaDevAbility.byFRecogChanNum > 0)
	{   
		g_StringLanType(szLan, "人脸识别", "Face Recognize");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_FACE_RECOG);
        index++;
	}

	if (m_struVcaDevAbility.byBPPerimeterChanNum > 0)
	{  
	    g_StringLanType(szLan, "行为监狱版(周界)", "Prison perimeter");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_PRISON_PERIMETER);
        index++;
	}
	
	if (m_struVcaDevAbility.byTPSChanNum > 0)
	{
		g_StringLanType(szLan, "交通诱导", "TPS");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_TPS);
        index++;
	}

	if (m_struVcaDevAbility.byTFSChanNum > 0)
	{   
		g_StringLanType(szLan, "交通违章取证", "TFS");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_TFS);
		index++;
	}
	
	if (m_struVcaDevAbility.byFSnapBFullChanNum > 0)
	{   
		g_StringLanType(szLan, "人脸抓拍和行为分析", "BEHAVIOR_FACESNA");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_FACESNAP);
		index++;
	}
	
	if (m_struVcaDevAbility.byHeatMapChanNum > 0)
	{   
		g_StringLanType(szLan, "热度图", "HEATMAP");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_HEATMAP);
		index++;
	}

	if (m_struVcaDevAbility.bySmartVehicleNum > 0)
	{   
		g_StringLanType(szLan, "SMART事件+车辆检测", "Smart+Vehicle");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_SMART_VEHICLE_DETECTION);
		index++;
	}

	if (m_struVcaDevAbility.bySmartHVTNum > 0)
	{   
		g_StringLanType(szLan, "SMART事件+混行检测", "Smart+HVT");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_SMART_HVT_DETECTION);
		index++;
	}

	if (m_struVcaDevAbility.bySmartNum > 0)
	{   
		g_StringLanType(szLan, "SMART事件", "Smart Event");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_SMART_EVENT);
		index++;
	}
	
	if (m_struVcaDevAbility.byVehicleNum > 0)
	{   
		g_StringLanType(szLan, "车辆检测", "Vehicle");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_VEHICLE_DETECTION);
		index++;
	}

    if (m_struVcaDevAbility.bySmartRoadDetectionNum > 0)
    {   
        g_StringLanType(szLan, "SMART事件+道路监控", "Smart + Road Detection");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_SMART_ROAD_DETECTION);
        index++;
	}

    if (m_struVcaDevAbility.bySmartFaceDetectionNum > 0)
    {   
        g_StringLanType(szLan, "SMART事件+人脸侦测", "Smart + Face Detection");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_SMART_FACE_DETECTION);
        index++;
	}

    if (m_struVcaDevAbility.bySmartHeatMapNum > 0)
    {   
        g_StringLanType(szLan, "SMART事件+热度图", "Smart + Heat Map");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_SMART_HEATMAP);
        index++;
	}

    if (m_struVcaDevAbility.byHumanRecognitionNum > 0)
    {
        g_StringLanType(szLan, "人体识别", "Human");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_HUMAN_RECOGNITION);
        index++;
    }

    if (m_struVcaDevAbility.byEdcationStudentNum > 0)
    {
        g_StringLanType(szLan, "教育录播", "Edcation Student");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_EDUCATION_STUDENT_DETECTION);
        index++;
    }

    if (m_struVcaDevAbility.byRoadDetectionNum > 0)
    {
        g_StringLanType(szLan, "道路监控", "Road Detection");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_ROAD_DETECTION);
        index++;
    }

    if (m_struVcaDevAbility.byPersonDensityDetection > 0)
    {
        g_StringLanType(szLan, "人员密度检测", "PersonDensityDetection");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_PERSON_DENSITY_DETECTION);
        index++;
    }

    if (m_struVcaDevAbility.bySafetyHelmetDetection > 0)
    {
        g_StringLanType(szLan, "安全帽检测", "SafetyHelmetDetection");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_SAFETY_HELMET_DETECTION);
        index++;
    }

    if (m_struVcaDevAbility.byPerimeterCapture > 0)
    {
        g_StringLanType(szLan, "周界抓拍", "PerimeterCapture");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_PERIMETER_CAPTURE);
        index++;
    }

    if (m_struVcaDevAbility.byHeelPDC > 0)
    {
        g_StringLanType(szLan, "倾斜客流", "HeelPDC");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_HEEL_PDC);
        index++;
    }

    if (m_struVcaDevAbility.by12MPLiveView > 0)
    {
        g_StringLanType(szLan, "1200W预览", "12MPLiveView");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_12MPLIVE_VIEW);
        index++;
    }

    if (m_struVcaDevAbility.byTeacherBehaviorDetectNum > 0)
    {
        g_StringLanType(szLan, "教师行为检测", "TeacherBehaviorDetect");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_TEACHER_BEHAVIOR_DETECTION);
        index++;
    }

    if (m_struVcaDevAbility.byMixedTargetDetection > 0)
    {
        g_StringLanType(szLan, "混合目标检测", "MixedTargetDetect");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_MIXED_TARGET_DETECTION);
        index++;
    }

    if (m_struVcaDevAbility.byFaceContrast > 0)
    {
        g_StringLanType(szLan, "人脸对比检测", "FaceContrast");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_FACE_CONTRAST);
        index++;
    }

    if (m_struVcaDevAbility.byCityManagement > 0)
    {
        g_StringLanType(szLan, "智慧城市检测", "CityManagement");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_CITY_MANAGEMENT);
        index++;
    }

    if (m_struVcaDevAbility.byMixedTargetDetectionSmart > 0)
    {
        g_StringLanType(szLan, "混合目标抓拍+Smart", "MixedTargetDetectionSmart");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_MIXED_TARGET_DETECTION_SMART);
        index++;
    }


    GetVcaCtrlCfg();
    
    m_comboChan.SetCurSel(0);
//	OnSelchangeComboChannel();
	
	return TRUE;
}

void CDlgVcaChanCtrlCfg::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bSupportChanEx)
	{
		GetVcaCtrlInfoFromWnd(m_struVcaCtrlInfo);
	}
	else
	{
		GetVcaCtrlFromWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
	}
    
}

void CDlgVcaChanCtrlCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	GetVcaCtrlCfg();
}

void CDlgVcaChanCtrlCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	SetVcaCtrlCfg();
}


BOOL CDlgVcaChanCtrlCfg::SetVcaCtrlToWnd(NET_VCA_CTRLINFO const &struVcaCtrlInfo)
{
	
    for (int i = 0; i < m_comboChanVcaType.GetCount(); i++)
    {
        if (m_comboChanVcaType.GetItemData(i) == struVcaCtrlInfo.byVCAType)
        {
            m_comboChanVcaType.SetCurSel(i);
            break;
        }
    }
	
    m_bChkStreamWithVca = struVcaCtrlInfo.byStreamWithVCA;
    m_bChkEnable = struVcaCtrlInfo.byVCAEnable;

	ShowVcaChanModeParam(struVcaCtrlInfo.byVCAType,struVcaCtrlInfo.byMode);

	UpdateData(FALSE);
    return TRUE;
}

BOOL CDlgVcaChanCtrlCfg::GetVcaCtrlFromWnd(NET_VCA_CTRLINFO &struVcaCtrlInfo)
{
    struVcaCtrlInfo.byVCAEnable     = m_bChkEnable;
    struVcaCtrlInfo.byStreamWithVCA = m_bChkStreamWithVca;
    struVcaCtrlInfo.byVCAType       = m_comboChanVcaType.GetItemData(m_comboChanVcaType.GetCurSel());

	if (struVcaCtrlInfo.byVCAType == VCA_ATM ||
		struVcaCtrlInfo.byVCAType == VCA_TFS ||
		struVcaCtrlInfo.byVCAType == VCA_BEHAVIOR_FULL) 
	{   
		int nCurSelMode         = m_comboVcaMode.GetCurSel();
		struVcaCtrlInfo.byMode  = m_comboVcaMode.GetItemData(nCurSelMode);
	}

    return TRUE;
}

BOOL CDlgVcaChanCtrlCfg::SetVcaCtrlCfg()
{
    UpdateData(TRUE);
	BOOL bRet = FALSE;
    DWORD dwStatus = 0xffffffff; 
	m_iVcaChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
	char szLan[128] = {0};

	if (m_bSupportChanEx)
	{
		NET_DVR_VCA_CTRLINFO_COND struCond = {0};
		struCond.dwSize = sizeof(struCond);
		struCond.struStreamInfo.dwChannel = m_iVcaChannel;
		m_struVcaCtrlInfo.dwSize = sizeof(NET_DVR_VCA_CTRLINFO_CFG);
		BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_VCA_CTRLINFO_CFG, 1, &struCond,sizeof(struCond),&dwStatus, &m_struVcaCtrlInfo, sizeof(m_struVcaCtrlInfo));
		
		if (!(bRet && (0 == dwStatus)))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_CTRLINFO_CFG");         
			if (dwStatus != 0)
			{
				sprintf(szLan,"NET_DVR_SET_VCA_CTRLINFO_CFG  Failed Error[%d]",dwStatus);
				AfxMessageBox(szLan);
			}
			bRet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_CTRLINFO_CFG");            
			bRet = TRUE;
		}
	}
	else
	{
		if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, m_iVcaChannel, &m_struVcaCtrlCfg, sizeof(m_struVcaCtrlCfg)))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_CTRLCFG");            
			bRet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_CTRLCFG");            
			bRet = TRUE;
		}
	}
    
    return bRet;
}

BOOL CDlgVcaChanCtrlCfg::GetVcaCtrlCfg()
{
	BOOL bRet = FALSE;
	char szLan[128] = {0};
	DWORD dwReturn = 0;
	m_iVcaChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
	if (m_bSupportChanEx)
	{
		DWORD dwStatus = 0;
		NET_DVR_VCA_CTRLINFO_COND struCond = {0};
		struCond.dwSize = sizeof(struCond);
		struCond.struStreamInfo.dwChannel = m_iVcaChannel;
		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_VCA_CTRLINFO_CFG, 1, &struCond,sizeof(struCond),&dwStatus, &m_struVcaCtrlInfo, sizeof(m_struVcaCtrlInfo));
		
		if (!(bRet && (0 == dwStatus)))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_CTRLINFO_CFG");    
			if (dwStatus != 0)
			{
				sprintf(szLan,"NET_DVR_GET_VCA_CTRLINFO_CFG  Failed Error[%d]",dwStatus);
				AfxMessageBox(szLan);
			}
			bRet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_CTRLINFO_CFG");            
			SetVcaCtrlInfoToWnd(m_struVcaCtrlInfo);
            bRet = TRUE;
		}	
	}
	else
	{
		if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VCA_CTRLCFG, m_iVcaChannel, &m_struVcaCtrlCfg, sizeof(m_struVcaCtrlCfg), &dwReturn))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_CTRLCFG");            
			bRet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_CTRLCFG");            
			SetVcaCtrlToWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1]);
            bRet = TRUE;
		}
	}
	
	UpdateData(FALSE);
    return bRet;
}

void CDlgVcaChanCtrlCfg::OnSelchangeComboChannel() 
{
    UpdateData(TRUE);
	m_iVcaChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
    SetVcaCtrlToWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
    UpdateData(FALSE);
}
    
BOOL CDlgVcaChanCtrlCfg::SetVcaCtrlInfoToWnd(NET_DVR_VCA_CTRLINFO_CFG const &struVcaCtrlInfo)
{
	
    for (int i = 0; i < m_comboChanVcaType.GetCount(); i++)
    {
        if (m_comboChanVcaType.GetItemData(i) == struVcaCtrlInfo.byVCAType )
        {
            m_comboChanVcaType.SetCurSel(i);
            break;
        }
    }
	
    m_bChkStreamWithVca = struVcaCtrlInfo.byStreamWithVCA;
    m_bChkEnable = struVcaCtrlInfo.byVCAEnable;

	ShowVcaChanModeParam(struVcaCtrlInfo.byVCAType,struVcaCtrlInfo.byMode);

    m_iRelatedChan1 = struVcaCtrlInfo.wRelatedChannel[0];
    m_iRelatedChan2 = struVcaCtrlInfo.wRelatedChannel[1];
    m_iRelatedChan3 = struVcaCtrlInfo.wRelatedChannel[2];
    m_iRelatedChan4 = struVcaCtrlInfo.wRelatedChannel[3];

	UpdateData(FALSE);
    return TRUE;
}

BOOL CDlgVcaChanCtrlCfg::GetVcaCtrlInfoFromWnd(NET_DVR_VCA_CTRLINFO_CFG &struVcaCtrlInfo)
{
    struVcaCtrlInfo.byVCAEnable = m_bChkEnable;
    struVcaCtrlInfo.byStreamWithVCA = m_bChkStreamWithVca;
    struVcaCtrlInfo.byVCAType = m_comboChanVcaType.GetItemData(m_comboChanVcaType.GetCurSel());
    struVcaCtrlInfo.byMode = m_comboVcaMode.GetCurSel();

	if (struVcaCtrlInfo.byVCAType == VCA_ATM ||
		struVcaCtrlInfo.byVCAType == VCA_TFS ||
		struVcaCtrlInfo.byVCAType == VCA_BEHAVIOR_FULL)
	{   
		int nCurSelMode         = m_comboVcaMode.GetCurSel();
		struVcaCtrlInfo.byMode  = m_comboVcaMode.GetItemData(nCurSelMode);
	}

    struVcaCtrlInfo.wRelatedChannel[0] = m_iRelatedChan1;
    struVcaCtrlInfo.wRelatedChannel[1] = m_iRelatedChan2;
    struVcaCtrlInfo.wRelatedChannel[2] = m_iRelatedChan3;
    struVcaCtrlInfo.wRelatedChannel[3] = m_iRelatedChan4;

    return TRUE;
}

void CDlgVcaChanCtrlCfg::OnSelchangeComboChanVcatype() 
{
	int nCurSelType = m_comboChanVcaType.GetCurSel();
	if (nCurSelType != CB_ERR)
	{
		int nVcaType = m_comboChanVcaType.GetItemData(nCurSelType);
		ShowVcaChanModeParam(nVcaType,0);
	}
}


void CDlgVcaChanCtrlCfg::ShowVcaChanModeParam(int nVcaChanType,int nChanMode)
{   
	m_comboVcaMode.ResetContent();
    
	BOOL bShowVcaModeWnd = FALSE;
	char szLan[128] = {0};
	if (nVcaChanType == VCA_ATM)
	{
		g_StringLanType(szLan, "面板", "Panel");
		m_comboVcaMode.InsertString(0,szLan);
		m_comboVcaMode.SetItemData(0,VCA_ATM_PANEL);
		
		g_StringLanType(szLan, "环境", "Surround");
		m_comboVcaMode.InsertString(1,szLan);
		m_comboVcaMode.SetItemData(1,VCA_ATM_SURROUND);

		g_StringLanType(szLan, "人脸", "Face");
		m_comboVcaMode.InsertString(2,szLan);
		m_comboVcaMode.SetItemData(2,VCA_ATM_FACE);

		g_StringLanType(szLan, "防护舱", "SafetyCabin");
		m_comboVcaMode.InsertString(3,szLan);
		m_comboVcaMode.SetItemData(3,VCA_ATM_SAFETYCABIN);

		m_comboVcaMode.SetCurSel(0);
		bShowVcaModeWnd = TRUE;
	}
	else if (nVcaChanType == VCA_TFS)
	{
		g_StringLanType(szLan, "城市道路", "City road");
		m_comboVcaMode.InsertString(0,szLan);
		m_comboVcaMode.SetItemData(0,TFS_CITYROAD);
		
		g_StringLanType(szLan, "高速道路", "Free way");
		m_comboVcaMode.InsertString(1,szLan);
		m_comboVcaMode.SetItemData(1,TFS_FREEWAY);

		m_comboVcaMode.SetCurSel(0);
		bShowVcaModeWnd = TRUE;
	}
	else if (nVcaChanType == VCA_BEHAVIOR_FULL)
	{
		g_StringLanType(szLan, "系统默认", "Default");
		m_comboVcaMode.InsertString(0,szLan);
		m_comboVcaMode.SetItemData(0,BEHAVIOR_SCENE_DEFAULT);
		
		g_StringLanType(szLan, "围墙", "Wall");
		m_comboVcaMode.InsertString(1,szLan);
		m_comboVcaMode.SetItemData(1,BEHAVIOR_SCENE_WALL);

		g_StringLanType(szLan, "室内", "Indoor");
		m_comboVcaMode.InsertString(2,szLan);
		m_comboVcaMode.SetItemData(2,BEHAVIOR_SCENE_INDOOR);
		
		m_comboVcaMode.SetCurSel(0);
		bShowVcaModeWnd = TRUE;
	}

	GetDlgItem(IDC_STATIC_VCA_MODE)->ShowWindow(bShowVcaModeWnd);
	GetDlgItem(IDC_COMBO_VCA_MODE)->ShowWindow(bShowVcaModeWnd);

	if (bShowVcaModeWnd)
	{
		int nCount = m_comboVcaMode.GetCount();
		for (int i = 0; i < nCount; i++)
		{
			if (m_comboVcaMode.GetItemData(i) == nChanMode)
			{
				m_comboVcaMode.SetCurSel(i);
				break;
			}
		}
	}
}
