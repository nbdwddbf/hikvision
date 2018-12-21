// DlgVehicleRecogCFG.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVehicleRecogCFG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleRecogCFG dialog


CDlgVehicleRecogCFG::CDlgVehicleRecogCFG(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVehicleRecogCFG::IDD, pParent)
    , m_ctTimeSet(0)
    , m_ctDateSet(0)
    , m_dwMilisecondSet(0)
    , m_cJsonPath(_T(""))
    , m_csDevDataIndex(_T(""))
{
	//{{AFX_DATA_INIT(CDlgVehicleRecogCFG)
	m_bChkCompleteTask = FALSE;
	m_bChkExecutionTask = FALSE;
	m_bChkFacePicCopilot = FALSE;
	m_bChkFacePicMain = FALSE;
	m_bChkPicOverlay = FALSE;
	m_bChkPicUpdata = FALSE;
	m_bChkPlateBaffleCopilot = FALSE;
	m_bChkPlateBaffleMain = FALSE;
	m_bChkPlatePic = FALSE;
	m_bChkPlateRecog = FALSE;
	m_bChkSafetyBeltCopilot = FALSE;
	m_bChkSafetyBeltMain = FALSE;
	m_bChkSafetyBeltPicCopilot = FALSE;
	m_bChkSafetyBeltPicMain = FALSE;
	m_bChkVehicleBrand = FALSE;
	m_bChkVehicleColor = FALSE;
	m_bChkVehiclePic = FALSE;
	m_bChkVehicleType = FALSE;
	m_bChkWaitTask = FALSE;
    m_bChkPicUpdataURL = FALSE;
    m_bChkYellowCar = FALSE;
    m_bChkMobilePhone = FALSE;
    m_bChkPendant = FALSE;
    m_bChkDangerousVehicles = FALSE;
    m_bChkPDVS = FALSE;
	m_fx = 0.0f;
	m_fY = 0.0f;
	m_csDataIndex = _T("");
	m_csDataIndex2 = _T("");
	m_csLicense = _T("");
	m_csPicPath = _T("");
	m_csPicURL = _T("");
	m_fWidth = 0.0f;
	m_dwTaskNo = 0;
	m_dwTaskNo2 = 0;
	m_fHeight = 0.0f;
	//}}AFX_DATA_INIT

	m_lChannel = -1;
	m_lUserID = -1;
	m_lDevIndex = -1;
    m_dwPostID = 0;
	m_lHandle = -1;
	m_bGetNext = FALSE;
	m_hGetInfoThread = NULL;
	m_iStruCount = 0;

	memset(&m_struVehRecogCond, 0, sizeof(m_struVehRecogCond));
	memset(&m_struVehRecogCfg, 0, sizeof(m_struVehRecogCfg));
	memset(&m_struVehRecogTaskCond, 0, sizeof(m_struVehRecogTaskCond));
	memset(&m_struVehRecogTaskInfo, 0, sizeof(m_struVehRecogTaskInfo));
    memset(&m_struVehicleRecogTaskResult, 0, sizeof(m_struVehicleRecogTaskResult));
    m_pJsonInfo = NULL;
}

CDlgVehicleRecogCFG::~CDlgVehicleRecogCFG()
{
	if (m_hGetInfoThread)
	{
		TerminateThread(m_hGetInfoThread, 0);	
		CloseHandle(m_hGetInfoThread);
		m_hGetInfoThread = NULL;
	}
    if (NULL != m_pJsonInfo)
    {
        delete[]m_pJsonInfo;
        m_pJsonInfo = NULL;
    }
}

void CDlgVehicleRecogCFG::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVehicleRecogCFG)
    DDX_Control(pDX, IDC_COMBO_PIC_DATA_TYPE, m_comPicDataType);
    DDX_Control(pDX, IDC_LIST_VEHICLE, m_lstVehicle);
    DDX_Check(pDX, IDC_CHK_COMPLETE_TASK, m_bChkCompleteTask);
    DDX_Check(pDX, IDC_CHK_EXECUTION_TASK, m_bChkExecutionTask);
    DDX_Check(pDX, IDC_CHK_FACE_PIC_COPILOT, m_bChkFacePicCopilot);
    DDX_Check(pDX, IDC_CHK_FACE_PIC_MAIN, m_bChkFacePicMain);
    DDX_Check(pDX, IDC_CHK_PIC_OVERLAY, m_bChkPicOverlay);
    DDX_Check(pDX, IDC_CHK_PIC_UPDATA, m_bChkPicUpdata);
    DDX_Check(pDX, IDC_CHK_PLATE_BAFFLE_COPILOT, m_bChkPlateBaffleCopilot);
    DDX_Check(pDX, IDC_CHK_PLATE_BAFFLE_MAIN, m_bChkPlateBaffleMain);
    DDX_Check(pDX, IDC_CHK_PLATE_PIC, m_bChkPlatePic);
    DDX_Check(pDX, IDC_CHK_PLATE_RECOG, m_bChkPlateRecog);
    DDX_Check(pDX, IDC_CHK_PIC_UPDATA_URL, m_bChkPicUpdataURL);
    DDX_Check(pDX, IDC_CHK_YELLOW_CAR, m_bChkYellowCar);
    DDX_Check(pDX, IDC_CHK_MOBILE_PHONE, m_bChkMobilePhone);
    DDX_Check(pDX, IDC_CHK_PENDANT, m_bChkPendant);
    DDX_Check(pDX, IDC_CHK_DANGEROUS_VEHICLES, m_bChkDangerousVehicles);
    DDX_Check(pDX, IDC_CHK_PDVS, m_bChkPDVS);
    DDX_Check(pDX, IDC_CHK_SAFETY_BELT_COPILOT, m_bChkSafetyBeltCopilot);
    DDX_Check(pDX, IDC_CHK_SAFETY_BELT_MAIN, m_bChkSafetyBeltMain);
    DDX_Check(pDX, IDC_CHK_SAFETY_BELT_PIC_COPILOT, m_bChkSafetyBeltPicCopilot);
    DDX_Check(pDX, IDC_CHK_SAFETY_BELT_PIC_MIAN, m_bChkSafetyBeltPicMain);
    DDX_Check(pDX, IDC_CHK_VEHICLE_BRAND, m_bChkVehicleBrand);
    DDX_Check(pDX, IDC_CHK_VEHICLE_COLOR, m_bChkVehicleColor);
    DDX_Check(pDX, IDC_CHK_VEHICLE_PIC, m_bChkVehiclePic);
    DDX_Check(pDX, IDC_CHK_VEHICLE_TYPE, m_bChkVehicleType);
    DDX_Check(pDX, IDC_CHK_WAITTASK, m_bChkWaitTask);
    DDX_Text(pDX, IDC_EDIT_COORD_X, m_fx);
    DDX_Text(pDX, IDC_EDIT_COORD_Y, m_fY);
    DDX_Text(pDX, IDC_EDIT_DATAINDEX, m_csDataIndex);
    DDX_Text(pDX, IDC_EDIT_DATAINDEX2, m_csDataIndex2);
    DDX_Text(pDX, IDC_EDIT_LICENSE, m_csLicense);
    DDX_Text(pDX, IDC_EDIT_PIC_PATH, m_csPicPath);
    DDX_Text(pDX, IDC_EDIT_PIC_URL, m_csPicURL);
    DDX_Text(pDX, IDC_EDIT_PLANE_WIDTH, m_fWidth);
    DDX_Text(pDX, IDC_EDIT_TASKNO, m_dwTaskNo);
    DDX_Text(pDX, IDC_EDIT_TASKNO2, m_dwTaskNo2);
    DDX_Text(pDX, IDC_EDIT_PLANE_LENGTH, m_fHeight);
    DDX_Text(pDX, IDC_EDIT_POST_ID, m_dwPostID);
    DDX_DateTimeCtrl(pDX, IDC_TIME_POST_TIME, m_ctTimeSet);
    DDX_DateTimeCtrl(pDX, IDC_DATE_POST_TIME, m_ctDateSet);
    DDX_Text(pDX, IDC_EDIT_POST_TIME_MILISECOND, m_dwMilisecondSet);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_JSON_DATAPATH, m_cJsonPath);
    DDX_Text(pDX, IDC_EDIT_DEV_DATAINDEX, m_csDevDataIndex);
}


BEGIN_MESSAGE_MAP(CDlgVehicleRecogCFG, CDialog)
	//{{AFX_MSG_MAP(CDlgVehicleRecogCFG)
	ON_CBN_SELCHANGE(IDC_COMBO_PIC_DATA_TYPE, OnSelchangeComboPicDataType)
	ON_BN_CLICKED(IDC_BTN_PATH, OnBtnPath)
	ON_BN_CLICKED(IDC_BTN_SET_VEHICLE_DETECTION, OnBtnSetVehicleDetection)
	ON_BN_CLICKED(IDC_BTN_GET_VEHICLE_DETECTION, OnBtnGetVehicleDetection)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_JSON_PATH, &CDlgVehicleRecogCFG::OnBnClickedBtnJsonPath)
    ON_BN_CLICKED(IDC_BTN_SET_VEHICLERECOG_TASK_V50, &CDlgVehicleRecogCFG::OnBnClickedBtnSetVehiclerecogTaskV50)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleRecogCFG message handlers

BOOL CDlgVehicleRecogCFG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comPicDataType.SetCurSel(0);
	OnSelchangeComboPicDataType();
	
    CTime ctCurTime = CTime::GetCurrentTime();
    CTime time(ctCurTime.GetYear(), ctCurTime.GetMonth(), ctCurTime.GetDay(), 0, 0, 0);
    m_ctDateSet = time;
    m_ctTimeSet = time;
	char szLanTemp[128] = {0};
	m_lstVehicle.SetExtendedStyle(m_lstVehicle.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	//g_StringLanType(szLanTemp, "数据流水号", "Data Index");
    //m_lstVehicle.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 0, -1);
	g_StringLanType(szLanTemp, "通道号", "Channel");
    m_lstVehicle.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "数据流水号", "Data Index");
	m_lstVehicle.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "任务处理号", "Task No");
    m_lstVehicle.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "任务进度", "Task Progress");
    m_lstVehicle.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "任务状态", "Task State");
    m_lstVehicle.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车牌识别", "Plate Recog");
    m_lstVehicle.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车辆类型识别", "Vehicle Type");
    m_lstVehicle.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车身颜色识别", "Vehicle Color");
    m_lstVehicle.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车辆品牌识别", "Vehicle Brand");
    m_lstVehicle.InsertColumn(8, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "遮挡板识别(主驾驶)", "Plate Baffle(Main)");
    m_lstVehicle.InsertColumn(9, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "安全带识别(主驾驶)", "Safety Belt(Main)");
    m_lstVehicle.InsertColumn(10, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "遮挡板识别(副驾驶)", "Plate Baffle(Copilot)");
    m_lstVehicle.InsertColumn(11, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "安全带识别(副驾驶)", "Safety Belt(Copilot)");
    m_lstVehicle.InsertColumn(12, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车辆图片叠加", "Picture Overlay");
    m_lstVehicle.InsertColumn(13, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "上传图片(SDK)", "Picture Updata(SDK)");
    m_lstVehicle.InsertColumn(14, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "上传图片(URL)", "Picture Updata(URL)");
    m_lstVehicle.InsertColumn(15, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "黄标车", "standard yellow cars");
    m_lstVehicle.InsertColumn(16, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "打手机", "Mobile phone");
    m_lstVehicle.InsertColumn(17, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "挂件", "Pendant");
    m_lstVehicle.InsertColumn(18, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "危险品车", "Dangerous Vehicles");
    m_lstVehicle.InsertColumn(19, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车辆天窗站人", "PDVS");
    m_lstVehicle.InsertColumn(20, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "卡口ID", "Post ID");
    m_lstVehicle.InsertColumn(21, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "过车时间", "Post Time");
    m_lstVehicle.InsertColumn(22, szLanTemp, LVCFMT_LEFT, 60, -1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVehicleRecogCFG::OnSelchangeComboPicDataType() 
{
	// TODO: Add your control notification handler code here
	int i = m_comPicDataType.GetCurSel();	

	if(0 == i)
	{
		GetDlgItem(IDC_EDIT_PIC_PATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PIC_URL)->EnableWindow(FALSE);
	}
	else if(1 == i)
	{
		GetDlgItem(IDC_EDIT_PIC_PATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PIC_URL)->EnableWindow(TRUE);
	}
}

void CDlgVehicleRecogCFG::OnBtnPath() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csPicPath = dlg.GetPathName();
        UpdateData(FALSE);
	}
}

void CDlgVehicleRecogCFG::OnBtnSetVehicleDetection() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	DWORD dwStatus = 0;
	DWORD dwFileSize = 0;
	char szLan[128] = {0};
	CFile cFile;
	char szFileName[MAX_PATH] = {0};
	if(0 == m_comPicDataType.GetCurSel())
	{
		strcpy(szFileName, m_csPicPath);
		if (!cFile.Open(szFileName, CFile::modeRead))
		{
			g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
			AfxMessageBox(szLan);
			return;
		}

		dwFileSize = (DWORD)cFile.GetLength();
		if (dwFileSize == 0)
		{
			g_StringLanType(szLan, "图片文件为空", "Picture file is empty");
			AfxMessageBox(szLan);
		}

		cFile.Close();
	}
	m_struVehRecogCond.dwSize = sizeof(m_struVehRecogCond);
	m_struVehRecogCond.dwChannel = m_lChannel;

	m_struVehRecogCfg.dwSize = sizeof(m_struVehRecogCfg);
	strncpy((char*)(m_struVehRecogCfg.sDataIndex), (char*)m_csDataIndex.GetBuffer(0), sizeof(m_struVehRecogCfg.sDataIndex));
	m_struVehRecogCfg.wTaskNo = m_dwTaskNo;
	m_struVehRecogCfg.struPlateRect.fX = m_fx;
	m_struVehRecogCfg.struPlateRect.fY = m_fY;
	m_struVehRecogCfg.struPlateRect.fHeight = m_fHeight;
	m_struVehRecogCfg.struPlateRect.fWidth = m_fWidth;
	strncpy((char*)(m_struVehRecogCfg.sLicense), (char*)m_csLicense.GetBuffer(0), sizeof(m_struVehRecogCfg.sLicense));
    
	m_struVehRecogCfg.dwRecogOperate = 0;
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkPlateRecog << 0);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkVehicleType << 1);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkVehicleColor << 2);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkVehicleBrand << 3);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkPlateBaffleMain << 4);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkSafetyBeltMain << 5);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkPlateBaffleCopilot << 6);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkSafetyBeltCopilot << 7);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkPicOverlay << 8);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkPicUpdata << 9);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPicUpdataURL << 10);
	m_struVehRecogCfg.dwRecogOperate |= (m_bChkYellowCar << 11);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkMobilePhone << 12);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPendant << 13);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkDangerousVehicles << 14);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPDVS << 15);

	m_struVehRecogCfg.dwDataUploadType = 0;
	m_struVehRecogCfg.dwDataUploadType |= (m_bChkPlatePic << 0);
	m_struVehRecogCfg.dwDataUploadType |= (m_bChkVehiclePic << 1);
	m_struVehRecogCfg.dwDataUploadType |= (m_bChkFacePicMain << 2);
	m_struVehRecogCfg.dwDataUploadType |= (m_bChkFacePicCopilot << 3);
	m_struVehRecogCfg.dwDataUploadType |= (m_bChkSafetyBeltPicMain << 4);
	m_struVehRecogCfg.dwDataUploadType |= (m_bChkSafetyBeltPicCopilot << 5);

    m_struVehRecogCfg.dwPostID = m_dwPostID;

    m_struVehRecogCfg.struPostTime.wYear = (WORD)m_ctDateSet.GetYear();
    m_struVehRecogCfg.struPostTime.byMonth = m_ctDateSet.GetMonth();
    m_struVehRecogCfg.struPostTime.byDay = m_ctDateSet.GetDay();
    m_struVehRecogCfg.struPostTime.byHour = m_ctTimeSet.GetHour();
    m_struVehRecogCfg.struPostTime.byMinute= m_ctTimeSet.GetMinute();
    m_struVehRecogCfg.struPostTime.bySecond = m_ctTimeSet.GetSecond();
    m_struVehRecogCfg.struPostTime.wMilliSec =(WORD)m_dwMilisecondSet;
	//m_struVehRecogCfg.dwDataLen = dwFileSize;
	m_struVehRecogCfg.byPicDataType = m_comPicDataType.GetCurSel();
	if (0 == m_comPicDataType.GetCurSel())
	{
		strncpy((char*)(m_struVehRecogCfg.sPicDataPath), (char*)m_csPicPath.GetBuffer(0), sizeof(m_struVehRecogCfg.sPicDataPath));
	} 
	else
	{
		strncpy((char*)(m_struVehRecogCfg.sPicDataPath), (char*)m_csPicURL.GetBuffer(0), sizeof(m_struVehRecogCfg.sPicDataPath));
	}
   
    //Json数据读取start
    CFile cJsonFile;

    if (!cJsonFile.Open(m_cJsonPath, CFile::modeRead))
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
    }
    else
    {
        m_struVehRecogCfg.dwJsonLen = (DWORD)cJsonFile.GetLength();
        if (m_struVehRecogCfg.dwJsonLen == 0)
        {
            g_StringLanType(szLan, "Json文件为空", "Configure file is empty");
            AfxMessageBox(szLan);
        }

        m_pJsonInfo = new BYTE[m_struVehRecogCfg.dwJsonLen];
        cJsonFile.Read(m_pJsonInfo, m_struVehRecogCfg.dwJsonLen);
        m_struVehRecogCfg.pJsonBuffer = m_pJsonInfo;

        cJsonFile.Close();
    }
    //end

	BOOL bRet = NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_VEHICLE_RECOG_TASK, 1, &m_struVehRecogCond, sizeof(m_struVehRecogCond), \
	&dwStatus, &m_struVehRecogCfg, (sizeof(m_struVehRecogCfg)));	
	if (bRet)
	{
		if (dwStatus != 0)
		{
			sprintf(szLan,"错误状态返回值:%d",dwStatus);
			AfxMessageBox(szLan);
		}

		g_pMainDlg->AddLog(m_lDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VEHICLE_RECOG_TASK Success");
	}
	else
	{        
		g_pMainDlg->AddLog(m_lDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VEHICLE_RECOG_TASK Fail");
	}
}

void CDlgVehicleRecogCFG::AddVehDetectInfoToDlg(LPNET_DVR_VEHICLE_RECOG_TASK_INFO lpInter)
{
	BOOL bEnable = FALSE;

	int iItemCount = m_lstVehicle.GetItemCount();

	m_lstVehicle.InsertItem(iItemCount, "");
	
	char szStr[128] = {0};
	char szOperateInfo[1280] = {0};
	
	sprintf(szStr, "%d", lpInter->dwChannel);
	m_lstVehicle.SetItemText(iItemCount, 0, szStr);

	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%s", lpInter->sDataIndex);
	m_lstVehicle.SetItemText(iItemCount, 1, szStr);	

	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d", lpInter->wTaskNo);
	m_lstVehicle.SetItemText(iItemCount, 2, szStr);	

	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d", lpInter->wTaskProgress);
	m_lstVehicle.SetItemText(iItemCount, 3, szStr);	

	memset(szStr, 0, sizeof(szStr));
	if(0 == lpInter->byTaskState)
	{
		g_StringLanType(szStr, "等待中", "Waiting");
		m_lstVehicle.SetItemText(iItemCount, 4, szStr);
	}
	else if(1 == lpInter->byTaskState)
	{
		g_StringLanType(szStr, "执行中", "Execution");
		m_lstVehicle.SetItemText(iItemCount, 4, szStr);
	}
	else if(2 == lpInter->byTaskState)
	{
		g_StringLanType(szStr, "已完成", "Finish");
		m_lstVehicle.SetItemText(iItemCount, 4, szStr);		
	}

	
	for(int i = 0; i<=15; i++)
	{
		memset(szStr, 0, sizeof(szStr));
		bEnable = (lpInter->dwRecogOperate >>i) &0x01;
		if(bEnable)
		{
			g_StringLanType(szStr, "启用", "Enable");
			m_lstVehicle.SetItemText(iItemCount, 5+i, szStr);
		}
		else
		{
			g_StringLanType(szStr, "不启用", "Disable");
			m_lstVehicle.SetItemText(iItemCount, 5+i, szStr);	
		}
	}

    sprintf(szStr, "%d", lpInter->dwPostID);
    m_lstVehicle.SetItemText(iItemCount, 21, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d-%d-%d %d:%d:%d.%d", lpInter->struPostTime.wYear, lpInter->struPostTime.byMonth, lpInter->struPostTime.byDay/
        lpInter->struPostTime.byHour, lpInter->struPostTime.byMinute, lpInter->struPostTime.bySecond, lpInter->struPostTime.wMilliSec);
    m_lstVehicle.SetItemText(iItemCount, 22, szStr);
}

DWORD WINAPI CDlgVehicleRecogCFG::GetVehInfoThread(LPVOID lpVehInfo)
{
	CDlgVehicleRecogCFG* pThis = reinterpret_cast<CDlgVehicleRecogCFG*>(lpVehInfo);
    int iRet = 0;
	char szLan[128] = {0};
	char szInfoBuf[128] = {0};
	while (pThis->m_bGetNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struVehRecogTaskInfo, sizeof(NET_DVR_VEHICLE_RECOG_TASK_INFO)); 
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddVehDetectInfoToDlg(&pThis->m_struVehRecogTaskInfo);
			//pThis->m_iStruCount++;
		}
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				g_StringLanType(szLan, "车辆检测信息获取结束!", "Get Vehicle Detection Info Finish");
				sprintf(szInfoBuf, "%s[Info Count:%d]", szLan, pThis->m_lstVehicle.GetItemCount());
				AfxMessageBox(szInfoBuf);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "车辆检测信息获取失败", "Get Vehicle Detection Info Failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "未知状态", "Unknown status");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	//UpdateData(FALSE);
	return 0 ;
}

void CDlgVehicleRecogCFG::OnBtnGetVehicleDetection() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	m_struVehRecogTaskCond.dwSize = sizeof(m_struVehRecogTaskCond);
	m_struVehRecogTaskCond.dwChannel = m_lChannel;
	strncpy((char*)(m_struVehRecogTaskCond.sDataIndex), (char*)m_csDataIndex2.GetBuffer(0), sizeof(m_struVehRecogTaskCond.sDataIndex));
	m_struVehRecogTaskCond.wTaskNo = m_dwTaskNo2;
	
	m_struVehRecogTaskCond.byTask = 0;
	m_struVehRecogTaskCond.byTask |= (m_bChkCompleteTask << 0);
	m_struVehRecogTaskCond.byTask |= (m_bChkExecutionTask << 1);
	m_struVehRecogTaskCond.byTask |= (m_bChkWaitTask << 2);
    strncpy((char*)(m_struVehRecogTaskCond.sDevDataIndex), (char*)m_csDevDataIndex.GetBuffer(0), sizeof(m_struVehRecogTaskCond.sDevDataIndex));
	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			m_bGetNext = FALSE;
			g_StringLanType(szLan, "车辆检测信息获取失败", "Stop Vehicle Detection Info Failed");
			AfxMessageBox(szLan);
			return;
		}
	}
	
	m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_VEHICLE_RECOG_TASK, &m_struVehRecogTaskCond, sizeof(m_struVehRecogTaskCond), NULL, NULL);
	if (m_lHandle >= 0)
	{
		m_bGetNext = TRUE;
		DWORD dwThreadId;
		m_lstVehicle.DeleteAllItems();
		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetVehInfoThread), this, 0, &dwThreadId);
	}
	else
	{
		g_StringLanType(szLan, "车辆检测信息获取失败", "Stop Vehicle Detection Info Failed");
		AfxMessageBox(szLan);
		return;
	}
}


void CDlgVehicleRecogCFG::OnBnClickedBtnJsonPath()
{
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_cJsonPath = dlg.GetPathName();
        UpdateData(FALSE);
    }
}


void CDlgVehicleRecogCFG::OnBnClickedBtnSetVehiclerecogTaskV50()
{
    UpdateData(TRUE);

    DWORD dwStatus = 0;
    DWORD dwFileSize = 0;
    char szLan[128] = { 0 };
    CFile cFile;
    char szFileName[MAX_PATH] = { 0 };
    if (0 == m_comPicDataType.GetCurSel())
    {
        strcpy(szFileName, m_csPicPath);
        if (!cFile.Open(szFileName, CFile::modeRead))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
            return;
        }

        dwFileSize = (DWORD)cFile.GetLength();
        if (dwFileSize == 0)
        {
            g_StringLanType(szLan, "图片文件为空", "Picture file is empty");
            AfxMessageBox(szLan);
        }

        cFile.Close();
    }
    m_struVehRecogCond.dwSize = sizeof(m_struVehRecogCond);
    m_struVehRecogCond.dwChannel = m_lChannel;

    m_struVehRecogCfg.dwSize = sizeof(m_struVehRecogCfg);
    strncpy((char*)(m_struVehRecogCfg.sDataIndex), (char*)m_csDataIndex.GetBuffer(0), sizeof(m_struVehRecogCfg.sDataIndex));
    m_struVehRecogCfg.wTaskNo = m_dwTaskNo;
    m_struVehRecogCfg.struPlateRect.fX = m_fx;
    m_struVehRecogCfg.struPlateRect.fY = m_fY;
    m_struVehRecogCfg.struPlateRect.fHeight = m_fHeight;
    m_struVehRecogCfg.struPlateRect.fWidth = m_fWidth;
    strncpy((char*)(m_struVehRecogCfg.sLicense), (char*)m_csLicense.GetBuffer(0), sizeof(m_struVehRecogCfg.sLicense));

    m_struVehRecogCfg.dwRecogOperate = 0;
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPlateRecog << 0);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkVehicleType << 1);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkVehicleColor << 2);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkVehicleBrand << 3);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPlateBaffleMain << 4);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkSafetyBeltMain << 5);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPlateBaffleCopilot << 6);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkSafetyBeltCopilot << 7);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPicOverlay << 8);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPicUpdata << 9);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPicUpdataURL << 10);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkYellowCar << 11);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkMobilePhone << 12);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPendant << 13);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkDangerousVehicles << 14);
    m_struVehRecogCfg.dwRecogOperate |= (m_bChkPDVS << 15);

    m_struVehRecogCfg.dwDataUploadType = 0;
    m_struVehRecogCfg.dwDataUploadType |= (m_bChkPlatePic << 0);
    m_struVehRecogCfg.dwDataUploadType |= (m_bChkVehiclePic << 1);
    m_struVehRecogCfg.dwDataUploadType |= (m_bChkFacePicMain << 2);
    m_struVehRecogCfg.dwDataUploadType |= (m_bChkFacePicCopilot << 3);
    m_struVehRecogCfg.dwDataUploadType |= (m_bChkSafetyBeltPicMain << 4);
    m_struVehRecogCfg.dwDataUploadType |= (m_bChkSafetyBeltPicCopilot << 5);

    m_struVehRecogCfg.dwPostID = m_dwPostID;

    m_struVehRecogCfg.struPostTime.wYear = (WORD)m_ctDateSet.GetYear();
    m_struVehRecogCfg.struPostTime.byMonth = m_ctDateSet.GetMonth();
    m_struVehRecogCfg.struPostTime.byDay = m_ctDateSet.GetDay();
    m_struVehRecogCfg.struPostTime.byHour = m_ctTimeSet.GetHour();
    m_struVehRecogCfg.struPostTime.byMinute = m_ctTimeSet.GetMinute();
    m_struVehRecogCfg.struPostTime.bySecond = m_ctTimeSet.GetSecond();
    m_struVehRecogCfg.struPostTime.wMilliSec = (WORD)m_dwMilisecondSet;
    //m_struVehRecogCfg.dwDataLen = dwFileSize;
    m_struVehRecogCfg.byPicDataType = m_comPicDataType.GetCurSel();
    if (0 == m_comPicDataType.GetCurSel())
    {
        strncpy((char*)(m_struVehRecogCfg.sPicDataPath), (char*)m_csPicPath.GetBuffer(0), sizeof(m_struVehRecogCfg.sPicDataPath));
    }
    else
    {
        strncpy((char*)(m_struVehRecogCfg.sPicDataPath), (char*)m_csPicURL.GetBuffer(0), sizeof(m_struVehRecogCfg.sPicDataPath));
    }

    //Json数据读取start
    CFile cJsonFile;

    if (!cJsonFile.Open(m_cJsonPath, CFile::modeRead))
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
    }
    else
    {
        m_struVehRecogCfg.dwJsonLen = (DWORD)cJsonFile.GetLength();
        if (m_struVehRecogCfg.dwJsonLen == 0)
        {
            g_StringLanType(szLan, "Json文件为空", "Configure file is empty");
            AfxMessageBox(szLan);
        }

        m_pJsonInfo = new BYTE[m_struVehRecogCfg.dwJsonLen];
        cJsonFile.Read(m_pJsonInfo, m_struVehRecogCfg.dwJsonLen);
        m_struVehRecogCfg.pJsonBuffer = m_pJsonInfo;

        cJsonFile.Close();
    }
    //end

    NET_DVR_IN_PARAM struInputPapam = { 0 };
    NET_DVR_OUT_PARAM struOutputPapam = { 0 };
    struInputPapam.struCondBuf.pBuf = &m_struVehRecogCond;
    struInputPapam.struCondBuf.nLen = sizeof(NET_DVR_VEHICLE_RECOG_COND);
    struInputPapam.struInParamBuf.pBuf = &m_struVehRecogCfg;
    struInputPapam.struInParamBuf.nLen = sizeof(NET_DVR_VEHICLE_RECOG_CFG);
    struOutputPapam.lpStatusList = &dwStatus;
    struOutputPapam.struOutBuf.pBuf = &m_struVehicleRecogTaskResult;
    struOutputPapam.struOutBuf.nLen = sizeof(NET_DVR_VEHICLERECOG_TASK_RESULT);

    BOOL bRet = NET_DVR_SetDeviceConfigEx(m_lUserID, NET_DVR_SET_VEHICLE_RECOG_TASK_V50, 1, &struInputPapam, &struOutputPapam);
    if (bRet)
    {
        if (dwStatus != 0)
        {
            sprintf(szLan, "错误状态返回值:%d", dwStatus);
            AfxMessageBox(szLan);
        }

        g_pMainDlg->AddLog(m_lDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VEHICLE_RECOG_TASK_V50 Success");
    }
    else
    {
        g_pMainDlg->AddLog(m_lDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VEHICLE_RECOG_TASK_V50 Fail");
    }

    m_csDevDataIndex = m_struVehicleRecogTaskResult.sDevDataIndex;
    UpdateData(FALSE);
}
