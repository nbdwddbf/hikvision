// DlgManualSnap.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgManualSnap.h"
#include "DlgPtzCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgManualSnap dialog
CDlgManualSnap *g_lManualSnapDlg = NULL;


CDlgManualSnap::CDlgManualSnap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManualSnap::IDD, pParent)
    , m_iChannelID(0)
{
	//{{AFX_DATA_INIT(CDlgManualSnap)
	m_bOSDClose = FALSE;
	m_iVehicleIndex = 0;
	m_csTrafficLight = _T("");
	m_byLaneNo = 0;
	m_dwSnapWaitTime = 0;
	m_dwIntervalTime1 = 0;
	m_dwIntervalTime2 = 0;
	m_dwIntervalTime3 = 0;
	m_dwIntervalTime4 = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1; // 用户ID
    m_iDevIndex = -1; // 设备索引
    m_lChannel = -1;
	m_lPlayHandle = -1;
	m_bCloseIn = FALSE;
	memset(&m_struManualSnap, 0, sizeof(m_struManualSnap));
    memset(&m_struResult, 0, sizeof(m_struResult));
}

CDlgManualSnap::~CDlgManualSnap()
{

	StopRealPlay();
}

void CDlgManualSnap::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgManualSnap)
    DDX_Control(pDX, IDC_COMBO_SNAP_TIMES, m_comSnapTimes);
    DDX_Control(pDX, IDC_COMBO_VEHICLE_COLOR, m_comVehicleColor);
    DDX_Control(pDX, IDC_REALTIME_LIST, m_RealtimeList);
    DDX_Check(pDX, IDC_CHECK_CLOSE_OSD, m_bOSDClose);
    DDX_Text(pDX, IDC_EDIT_VEHICLE_INDEX, m_iVehicleIndex);
    DDX_Text(pDX, IDC_EDIT_TRAFFIC_LIGHT, m_csTrafficLight);
    DDX_Text(pDX, IDC_EDIT_LANE_NO, m_byLaneNo);
    DDX_Text(pDX, IDC_EDIT_SNAP_TIME, m_dwSnapWaitTime);
    DDX_Text(pDX, IDC_EDIT_TIME1, m_dwIntervalTime1);
    DDX_Text(pDX, IDC_EDIT_TIME2, m_dwIntervalTime2);
    DDX_Text(pDX, IDC_EDIT_TIME3, m_dwIntervalTime3);
    DDX_Text(pDX, IDC_EDIT_TIME4, m_dwIntervalTime4);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_CHANNEL_ID, m_iChannelID);
}


BEGIN_MESSAGE_MAP(CDlgManualSnap, CDialog)
	//{{AFX_MSG_MAP(CDlgManualSnap)
	ON_BN_CLICKED(IDC_BTN_MANUAL_SNAP, OnBtnManualSnap)
	ON_BN_CLICKED(IDC_BTN_PTZ_CTRL, OnBtnPTZCtrl)
	ON_BN_CLICKED(IDC_BTN_CONTINUOUS_SHOOT, OnBtnContinuousShoot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CDlgManualSnap message handlers

long CDlgManualSnap::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_lChannel;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE); 
    if (m_lPlayHandle == -1) 
    {
        AfxMessageBox("Fail to Preview");
        return m_lPlayHandle;
    }
//     else
//     {
//         if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawManualSnapShow, 0)) 
//         {
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun Fail");
//             AfxMessageBox("Fail to set DrawFun callback");
//         }
//         
//     }
    return m_lPlayHandle;
}

BOOL CDlgManualSnap::StopRealPlay()
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

BOOL CDlgManualSnap::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	char szLanTemp[128] = {0};

    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
    m_bCloseIn = TRUE;

	if (m_lPlayHandle >= 0)
    {
        StopRealPlay();
    }
	
    StartRealPlay();

	m_RealtimeList.SetExtendedStyle(m_RealtimeList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	g_StringLanType(szLanTemp, "通过时间", "Time");
    m_RealtimeList.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 120, -1);
	g_StringLanType(szLanTemp, "车牌颜色", "License Plate Color");
    m_RealtimeList.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车辆类型", "Vehicle Type");
	m_RealtimeList.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "牌照信息", "License Info");
    m_RealtimeList.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 75, -1);
	g_StringLanType(szLanTemp, "车辆信息", "Vehicle Info");
    m_RealtimeList.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 110, -1);
	g_StringLanType(szLanTemp, "车辆速度", "Vehicle Speed");
    m_RealtimeList.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车辆图片", "Vehicle Image");
    m_RealtimeList.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 200, -1);
	g_StringLanType(szLanTemp, "车牌图片", "License Plate Image");
    m_RealtimeList.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 200, -1);
	g_StringLanType(szLanTemp, "车道号", "Lane No.");
    m_RealtimeList.InsertColumn(8, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "违规行为", "Violation Rule");
	m_RealtimeList.InsertColumn(9, szLanTemp, LVCFMT_LEFT, 150, -1);
	g_StringLanType(szLanTemp, "车标", "Vehicle Sign");
	m_RealtimeList.InsertColumn(10, szLanTemp, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLanTemp, "车牌亮度", "License Plate Bright");
    m_RealtimeList.InsertColumn(11, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "车牌号码", "License Plate No.");
    m_RealtimeList.InsertColumn(12, szLanTemp, LVCFMT_LEFT, 60, -1);

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void g_VehicleLogo(BYTE byVehicleLogoType, char* szLogoLan)
{
	switch(byVehicleLogoType)
	{
	case 1:
		g_StringLanType(szLogoLan, "大众", "Volkswagen");
		break;
	case 2:
		g_StringLanType(szLogoLan, "别克", "Buick");
		break;
	case 3:
		g_StringLanType(szLogoLan, "宝马", "BMW");
		break;
	case 4:
		g_StringLanType(szLogoLan, "本田", "Honda");
		break;
	case 5:
		g_StringLanType(szLogoLan, "标致", "Peugeot");
		break;
	case 6:
		g_StringLanType(szLogoLan, "丰田", "Toyota");
		break;
	case 7:
		g_StringLanType(szLogoLan, "福特", "Ford");
		break;
	case 8:
		g_StringLanType(szLogoLan, "日产", "Nissan");
		break;
	case 9:
		g_StringLanType(szLogoLan, "奥迪", "Audi");
		break;
	case 10:
		g_StringLanType(szLogoLan, "马自达", "Mazda");
		break;
	case 11:
		g_StringLanType(szLogoLan, "雪佛兰", "Chevrolet");
		break;
	case 12:
		g_StringLanType(szLogoLan, "雪铁龙", "Citroen");
		break;
	case 13:
		g_StringLanType(szLogoLan, "现代", "Hyundai");
		break;
	case 14:
		g_StringLanType(szLogoLan, "奇瑞", "Qirui");
		break;
	case 15:
		g_StringLanType(szLogoLan, "起亚", "KIA");
		break;
	case 16:
		g_StringLanType(szLogoLan, "荣威", "ROEWE");
		break;
	case 17:
		g_StringLanType(szLogoLan, "三菱", "MITSUBISHI");
		break;
	case 18:
		g_StringLanType(szLogoLan, "斯柯达", "SKODA");
		break;
	case 19:
		g_StringLanType(szLogoLan, "吉利", "GEELY");
		break;
	case 20:
		g_StringLanType(szLogoLan, "中华", "ZHONGHUA");
		break;
	case 21:
		g_StringLanType(szLogoLan, "沃尔沃", "VOLVO");
		break;
	case 22:
		g_StringLanType(szLogoLan, "雷克萨斯", "LEXUS");
		break;
	case 23:
		g_StringLanType(szLogoLan, "菲亚特", "FIAT");
		break;
	case 24:
		g_StringLanType(szLogoLan, "帝豪", "EMGRAND");
		break;
	case 25:
		g_StringLanType(szLogoLan, "东风", "DONGFENG");
		break;
	case 26:
		g_StringLanType(szLogoLan, "比亚迪", "BYD");
		break;
	case 27:
		g_StringLanType(szLogoLan, "铃木", "SUZUKI");
		break;
	case 28:
		g_StringLanType(szLogoLan, "金杯", "JINBEI");
		break;
	case 29:
		g_StringLanType(szLogoLan, "海马", "HAIMA");
		break;
	case 30:
		g_StringLanType(szLogoLan, "五菱", "SGMW");
		break;

	case 31:
		g_StringLanType(szLogoLan, "江淮", "JAC");
		break;
	case 32:
		g_StringLanType(szLogoLan, "斯巴鲁", "SUBARU");
		break;
	case 33:
		g_StringLanType(szLogoLan, "英伦", "ENGLON");
		break;
	case 34:
		g_StringLanType(szLogoLan, "长城", "GREATWALL");
		break;
	case 35:
		g_StringLanType(szLogoLan, "哈飞", "HAFEI");
		break;
	case 36:
		g_StringLanType(szLogoLan, "五十铃", "ISUZU");
		break;
	case 37:
		g_StringLanType(szLogoLan, "东南", "SOUEAST");
		break;
	case 38:
		g_StringLanType(szLogoLan, "长安", "CHANA");
		break;
	case 39:
		g_StringLanType(szLogoLan, "福田", "FOTON");
		break;
	case 40:
		g_StringLanType(szLogoLan, "夏利", "XIALI");
		break;
	case 41:
		g_StringLanType(szLogoLan, "奔驰", "BENZ");
		break;
	case 42:
		g_StringLanType(szLogoLan, "一汽", "FAW");
		break;
	case 43:
		g_StringLanType(szLogoLan, "依维柯", "NAVECO");
		break;
	case 44:
		g_StringLanType(szLogoLan, "力帆", "LIFAN");
		break;
	case 45:
		g_StringLanType(szLogoLan, "一汽奔腾", "BESTURN");
		break;
	case 46:
		g_StringLanType(szLogoLan, "皇冠", "CROWN");
		break;
	case 47:
		g_StringLanType(szLogoLan, "雷诺", "RENAULT");
		break;
	case 48:
		g_StringLanType(szLogoLan, "JMC", "JMC");
		break;
	case 49:
		g_StringLanType(szLogoLan, "MG名爵", "MG");
		break;
	case 50:
		g_StringLanType(szLogoLan, "凯马", "KAMA");
		break;
	case 51:
		g_StringLanType(szLogoLan, "众泰", "ZOTYE");
		break;
	case 52:
		g_StringLanType(szLogoLan, "昌河", "CHANGHE");
		break;
	case 53:
		g_StringLanType(szLogoLan, "厦门金龙", "XMKINGLONG");
		break;
	case 54:
		g_StringLanType(szLogoLan, "上海汇众", "HUIZHONG");
		break;
	case 55:
		g_StringLanType(szLogoLan, "苏州金龙", "SZKINGLONG");
		break;
	case 56:
		g_StringLanType(szLogoLan, "海格", "HIGER");
		break;
	case 57:
		g_StringLanType(szLogoLan, "宇通", "YUTONG");
		break;
	case 58:
		g_StringLanType(szLogoLan, "中国重汽", "CNHTC");
		break;
	case 59:
		g_StringLanType(szLogoLan, "北奔重卡", "BEIBEN");
		break;
	case 60:
		g_StringLanType(szLogoLan, "华菱星马", "XINGMA");
		break;
	case 61:
		g_StringLanType(szLogoLan, "跃进", "YUEJIN");
		break;
	case 62:
		g_StringLanType(szLogoLan, "黄海", "HUANGHAI");
		break;
	default:
		g_StringLanType(szLogoLan, "其他", "Other");
		break;
	}
}

void CDlgManualSnap::OnBtnManualSnap()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString csTemp;

	char szFileName[256] = {0};
	char szSubPicFilePath[256] = {0};  
	char szSubPlateFilePath[256] = {0};
	char szPicDataTime[256] = {0};
	char szPlateDataTime[256] = {0};
	char szPlateFileName[256] = {0};

	m_struManualSnap.byOSDEnable = m_bOSDClose;
    m_struManualSnap.byChannel = m_iChannelID;
	m_struResult.pBuffer1 = new BYTE[2 * 1024 * 1024];
    memset(m_struResult.pBuffer1, 0, 2 * 1024 * 1024);
	
	m_struResult.pBuffer2 = new BYTE[1024 * 1024];
    memset(m_struResult.pBuffer2, 0, 1024 * 1024);

	if (!NET_DVR_ManualSnap(m_lServerID, &m_struManualSnap, &m_struResult))
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ManualSnap");
        return;
    }  
    else
	{
		//通过时间
        csTemp.Format("%s", m_struResult.byAbsTime);
        m_RealtimeList.InsertItem(0, csTemp, -1);
        
		//车辆种类
		if (0 != m_struResult.byVehicleType)
		{
			switch (m_struResult.byVehicleType)
			{
			case 0:
				g_StringLanType(szLan, "未知", "UnKnow");		
				csTemp.Format("%s", szLan);
				break;
			case 1:
				g_StringLanType(szLan, "客车", "Passenger Carriage");	
				csTemp.Format("%s", szLan);
				break;
			case 2:
				g_StringLanType(szLan, "货车", "Freight Car");	
				csTemp.Format("%s", szLan);
				break;
			case 3:
				g_StringLanType(szLan, "轿车", "Car");
				csTemp.Format("%s", szLan);
				break;
			case 4:
				g_StringLanType(szLan, "面包车", "Microbus");
				csTemp.Format("%s", szLan);
				break;
			case 5:
				g_StringLanType(szLan, "小货车", "Little Freight Car");
				csTemp.Format("%s", szLan);
				break;
			case 6:
				g_StringLanType(szLan, "行人", "Passer");	
				csTemp.Format("%s", szLan);
				break;
			case 7:
				g_StringLanType(szLan, "二轮车", "Two-wheeler");	
				csTemp.Format("%s", szLan);
				break;
			case 8:
				g_StringLanType(szLan, "三轮车", "Three-wheeler");	
				csTemp.Format("%s", szLan);
				break;
			default:
				g_StringLanType(szLan, "未知", "UnKnow");		
				csTemp.Format("%s", szLan);
				break;
			}
		}
		else
		{
			//车辆类型
			switch (m_struResult.struVehicleInfo.byVehicleType)
			{
			case 0:
				g_StringLanType(szLan, "其他车辆", "Other Vehicles");	
				csTemp.Format("%s", szLan);
				//pDatabaseParam->m_csVehicleType.Format("其他车辆");
				break;
			case 1:
				g_StringLanType(szLan, "小型车", "Small Cars");	
				csTemp.Format("%s", szLan);
				//pDatabaseParam->m_csVehicleType.Format("小型车");
				break;
			case 2:
				g_StringLanType(szLan, "大型车", "Oversize Vehicle");	
				csTemp.Format("%s", szLan);
				//pDatabaseParam->m_csVehicleType.Format("大型车");
				break;
			case 3:
				g_StringLanType(szLan, "行人", "Passer");	
				csTemp.Format("%s", szLan);
				//pDatabaseParam->m_csVehicleType.Format("行人");
				break;
			case 4:
				g_StringLanType(szLan, "二轮车", "Two-wheeler");	
				csTemp.Format("%s", szLan);
				//pDatabaseParam->m_csVehicleType.Format("二轮车");
				break;
			case 5:
				g_StringLanType(szLan, "三轮车", "Three-wheeler");	
				csTemp.Format("%s", szLan);
				//pDatabaseParam->m_csVehicleType.Format("三轮车");
				break;
			default:
				g_StringLanType(szLan, "未知", "UnKnow");	
				csTemp.Format("%s", szLan);
				//pDatabaseParam->m_csVehicleType.Format("未知");
				break;
			}
		}
		m_RealtimeList.SetItemText(0, 2, csTemp);

		//车牌颜色
		switch(m_struResult.struPlateInfo.byColor)
		{
		case VCA_BLUE_PLATE:
			g_StringLanType(szLan, "蓝色", "Blue");	
			csTemp.Format("%s", szLan);
			//csTemp.Format("蓝色");
			break;
			
		case VCA_YELLOW_PLATE:
			g_StringLanType(szLan, "黄色", "Yellow");	
			csTemp.Format("%s", szLan);
			//csTemp.Format("黄色");
			break;
			
		case VCA_WHITE_PLATE:
			g_StringLanType(szLan, "白色", "White");	
			csTemp.Format("%s", szLan);
			//csTemp.Format("白色");
			break;
			
		case VCA_BLACK_PLATE:
			g_StringLanType(szLan, "黑色", "Black");	
			csTemp.Format("%s", szLan);
			//csTemp.Format("黑色");
			break;
			
		default:
			g_StringLanType(szLan, "未知", "UnKnow");	
			csTemp.Format("%s", szLan);
			break;
		} 
		m_RealtimeList.SetItemText(0, 1, csTemp);

		//车辆序号
        m_iVehicleIndex = m_struResult.struVehicleInfo.dwIndex;

		//车辆颜色
		m_comVehicleColor.SetCurSel(m_struResult.struVehicleInfo.byColor);

		//牌照信息
        csTemp.Format("%s", m_struResult.struPlateInfo.sLicense);
        m_RealtimeList.SetItemText(0, 3, csTemp);

		//车牌类型
        switch(m_struResult.struPlateInfo.byPlateType)
        {
        case VCA_STANDARD92_PLATE:
			g_StringLanType(szLan, "标准民用车与军车", "civil and military ");	
			csTemp.Format("%s", szLan);
            //csTemp.Format("标准民用车与军车");
            break;
            
        case VCA_STANDARD02_PLATE:
			g_StringLanType(szLan, "02式民用车牌", "02 type of civil license");	
			csTemp.Format("%s", szLan);
            //csTemp.Format("02式民用车牌");
            break;
            
        case VCA_WJPOLICE_PLATE:
			g_StringLanType(szLan, "武警车", "Police Car");	
			csTemp.Format("%s", szLan);
            //csTemp.Format("武警车");
            break;
            
        case VCA_JINGCHE_PLATE:
			g_StringLanType(szLan, "警车", "Police Wagon");	
			csTemp.Format("%s", szLan);
            //csTemp.Format("警车");
            break;
            
        case STANDARD92_BACK_PLATE:
			g_StringLanType(szLan, "民用车双行尾牌", "Double license");	
			csTemp.Format("%s", szLan);
            //csTemp.Format("民用车双行尾牌");
            break;
			
		case VCA_SHIGUAN_PLATE:
			g_StringLanType(szLan, "使馆车牌", "Embassy license");	
			csTemp.Format("%s", szLan);
			//csTemp.Format("使馆车牌");
			break;
			
		case VCA_NONGYONG_PLATE:
			g_StringLanType(szLan, "农用车牌", "Agricultural license");	
			csTemp.Format("%s", szLan);
			//csTemp.Format("农用车牌");
			break;
		case VCA_MOTO_PLATE:
			g_StringLanType(szLan, "摩托车车牌", "Motorcycle license");	
			csTemp.Format("%s", szLan);
			//csTemp.Format("摩托车车牌");
			break;
        case NEW_ENERGY_PLATE:
            g_StringLanType(szLan, "新能源车车牌", "new energy license");	
            csTemp.Format("%s", szLan);
			break;
            
        default:
			g_StringLanType(szLan, "未知", "UnKnow");	
			csTemp.Format("%s", szLan);
            //csTemp.Format("未知");
            break;
        }       
        m_RealtimeList.SetItemText(0, 4, csTemp);

        //速度
        csTemp.Format("%dkm/h", m_struResult.struVehicleInfo.wSpeed);
        m_RealtimeList.SetItemText(0, 5, csTemp);

		//车牌亮度
		csTemp.Format("%d", m_struResult.struPlateInfo.byBright);
		m_RealtimeList.SetItemText(0, 11, csTemp);
		
		//车牌号码
       	csTemp.Format("%s", m_struResult.struPlateInfo.sLicense);
		m_RealtimeList.SetItemText(0, 12, csTemp);

		//抓拍类型
		switch(m_struResult.byTrafficLight)
		{
		case 0:
			g_StringLanType(szLan, "非红绿灯时抓拍", "Non light Capture");	
			m_csTrafficLight.Format("%s", szLan);
			//pDatabaseParam->m_csSnapMode.Format("非红绿灯时抓拍");
			break;
		case 1:
			g_StringLanType(szLan, "绿灯时抓拍", "Capture in green light");	
			m_csTrafficLight.Format("%s", szLan);
			//pDatabaseParam->m_csSnapMode.Format("绿灯时抓拍");
			break;
		case 2:
			g_StringLanType(szLan, "红灯时抓拍", "Capture in red light");	
			m_csTrafficLight.Format("%s", szLan);
			//pDatabaseParam->m_csSnapMode.Format("红灯时抓拍");
			break;
		default:
			g_StringLanType(szLan, "未知", "UnKnow");	
			m_csTrafficLight.Format("%s", szLan);
			//pDatabaseParam->m_csSnapMode.Format("未知");
			break;
        }

		//车道号
		g_StringLanType(szLan, "车道号", "Lane");	
		csTemp.Format("%s:%d", szLan, m_struResult.byDriveChan);                  
        m_RealtimeList.SetItemText(0, 8, csTemp);

		//违规类型
		switch(m_struResult.struVehicleInfo.byIllegalType)
		{
		case 0:
			g_StringLanType(szLan, "正常", "Normal");
			csTemp.Format("%s\n", szLan);
			g_StringLanType(szLan, "卡口", "Intelligent Monitoring and Recording System");
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 1:
			g_StringLanType(szLan, "低速", "Low Speed");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 2:
			g_StringLanType(szLan, "超速", "Over Speed");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 3:
			g_StringLanType(szLan, "逆行", "Go in the Wrong Direction");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 4:
			g_StringLanType(szLan, "违反交通灯指示", "Run the Red Light");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 5:
			g_StringLanType(szLan, "压车道线", "Over Lane Line");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 6:
			g_StringLanType(szLan, "不按导向", "Travel against Guiding");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 7:
			g_StringLanType(szLan, "路口滞留", "Intersection retention");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 8:
			g_StringLanType(szLan, "机占非", "Motor Vehicle Running on Non-Motor Vehicle Lane");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 9:
			g_StringLanType(szLan, "违法变道", "Illegal Lane Change");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 10:
			g_StringLanType(szLan, "占用专用车道", "Take up dedicated lane");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		case 11:
			g_StringLanType(szLan, "闯禁令", "Violation of Prohibition sign");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		default:
			g_StringLanType(szLan, "未知", "Unknown");
			csTemp.Format("%s\n", szLan);
			sprintf(szSubPicFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			sprintf(szSubPlateFilePath, "%s\\%s", g_struLocalParam.chPictureSavePath, szLan);
			break;
		}
		m_RealtimeList.SetItemText(0, 9, csTemp);

		//车标
		g_VehicleLogo(m_struResult.struVehicleInfo.byVehicleLogoRecog, szLan);
		csTemp.Format("%s\n", szLan);
		m_RealtimeList.SetItemText(0, 10, csTemp);

		//车辆图片
		if (m_struResult.dwPicLen != 0 && m_struResult.byResultType == 1)
		{
			if (GetFileAttributes(szSubPicFilePath) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(szSubPicFilePath, NULL);
			}
			if (GetFileAttributes(szSubPlateFilePath) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(szSubPlateFilePath, NULL);
			}
			
			char szTime[9] = {0};
			memcpy(szTime, m_struResult.byAbsTime, 8);
			sprintf(szPicDataTime,"%s\\%s", szSubPicFilePath,szTime);  
			sprintf(szPlateDataTime,"%s\\%s", szSubPlateFilePath,szTime); 
			if (GetFileAttributes(szPicDataTime) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(szPicDataTime, NULL);
			}
			if (GetFileAttributes(szPlateDataTime) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(szPlateDataTime, NULL);
			}
			
			sprintf(szFileName, "%s\\%s.jpg", szPicDataTime/*szSubPicFilePath*/, m_struResult.byAbsTime);
			
            HANDLE lHandle = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            m_RealtimeList.SetItemText(0, 6, szFileName);
            if (lHandle == INVALID_HANDLE_VALUE)
            {
                TRACE("create file failed! Error code:%d", WSAGetLastError());
                return;
            }	
			DWORD dwReturn = 0;	
            WriteFile(lHandle, m_struResult.pBuffer1, m_struResult.dwPicLen, &dwReturn, NULL);
            CloseHandle(lHandle);			
		}

		//车牌图片
		if (m_struResult.dwPicPlateLen != 0 && m_struResult.byResultType == 1)
		{
			g_StringLanType(szLan, "车牌", "License plate");
			sprintf(szPlateFileName, "%s\\%s%s.jpg", szPlateDataTime/*szSubPlateFilePath*/, szLan, m_struResult.byAbsTime);                    
			m_RealtimeList.SetItemText(0, 7, szPlateFileName);	
			if (m_struResult.dwPicPlateLen != 0 && m_struResult.byResultType == 1)
			{
				sprintf(szPlateFileName, "%s\\%s%s.jpg", szPlateDataTime/*szSubPlateFilePath*/, szLan, m_struResult.byAbsTime);                    
				m_RealtimeList.SetItemText(0, 7, szPlateFileName);	
				HANDLE lHandle = CreateFile(szPlateFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (lHandle == INVALID_HANDLE_VALUE)
				{
					TRACE("create file failed! Error code:%d", WSAGetLastError());
					return;
				}                
				DWORD dwReturn = 0;	
				WriteFile(lHandle, m_struResult.pBuffer2, m_struResult.dwPicPlateLen, &dwReturn, NULL);
				CloseHandle(lHandle);
			}
		}

		 //视频文件
		if (m_struResult.byResultType == 0)
        {
			csTemp.Format("%s\\", szPicDataTime/*g_LocalParam.chPicFilePath*/);		
			DWORD dwRet = GetFileAttributes(csTemp);
			if ((dwRet == -1) || !(dwRet & FILE_ATTRIBUTE_DIRECTORY))
			{
				CreateDirectory(csTemp, NULL);
			}
            //视频文件
            sprintf(szFileName, "%s\\%s.mp4", szPicDataTime/*g_LocalParam.chPicFilePath*/, m_struResult.byAbsTime);
            
            HANDLE lHandle = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (lHandle == INVALID_HANDLE_VALUE)
            {
                TRACE("create file failed! Error code:%d", WSAGetLastError());
                return;
            }
            
            DWORD dwReturn = 0;	
            
            WriteFile(lHandle, m_struResult.pBuffer1, m_struResult.dwVideoLen, &dwReturn, NULL);
            CloseHandle(lHandle);
        }


		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ManualSnap");

	}

	if (NULL != m_struResult.pBuffer1)
	{
		delete []m_struResult.pBuffer1;
		m_struResult.pBuffer1 = NULL;
	}
	
	if (NULL != m_struResult.pBuffer2)
	{
		delete []m_struResult.pBuffer2;
		m_struResult.pBuffer2 = NULL;
	}
}

void CDlgManualSnap::OnBtnPTZCtrl()
{
	CDlgPtzCtrl dlg;
    dlg.m_lPlayHandle = m_lPlayHandle;
    dlg.DoModal();	
}

void CDlgManualSnap::OnBtnContinuousShoot() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_SNAPCFG struSnapCfg;
    memset(&struSnapCfg, 0, sizeof(NET_DVR_SNAPCFG));
    struSnapCfg.dwSize = sizeof(NET_DVR_SNAPCFG);
    struSnapCfg.byRelatedDriveWay = m_byLaneNo;
    struSnapCfg.bySnapTimes = m_comSnapTimes.GetCurSel();
    struSnapCfg.wSnapWaitTime = m_dwSnapWaitTime;
    struSnapCfg.wIntervalTime[0] = m_dwIntervalTime1;
    struSnapCfg.wIntervalTime[1] = m_dwIntervalTime2;
    struSnapCfg.wIntervalTime[2] = m_dwIntervalTime3;
    struSnapCfg.wIntervalTime[3] = m_dwIntervalTime4;
    
    if (!NET_DVR_ContinuousShoot(m_lServerID, &struSnapCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ContinuousShoot");
        return;
	} 
}
