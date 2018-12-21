// DlgITSMiniPost.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSMiniPost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSMiniPost dialog


CDlgITSMiniPost::CDlgITSMiniPost(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSMiniPost::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSMiniPost)
	m_bChkEffective_AlarmType = FALSE;
	m_bChkVehColor_Black = FALSE;
	m_bChkVehColor_Brown = FALSE;
	m_bChkVehColor_Bule = FALSE;
	m_bChkEffective_Channel = FALSE;
	m_bChkVehColor_DarkGrey = FALSE;
	m_bChkEffective_DataType = FALSE;
	m_bChkEffective_Time = FALSE;
	m_bChkEffective_License = FALSE;
	m_bChkEffective_PlateType = FALSE;
	m_bChkEffective_PlateColor = FALSE;
	m_bChkEffective_VehicleBrand = FALSE;
	m_bChkEffective_VehicleColor = FALSE;
	m_bChkEffective_VehicleType = FALSE;
	m_bChkEffective_Direction = FALSE;
	m_bChkEffective_EvadeType = FALSE;
	m_bChkEffective_EventType = FALSE;
	m_bChkEffective_Illegal = FALSE;
	m_bChkEffective_MaxSpeed = FALSE;
	m_bChkEffective_MinSpeed = FALSE;
	m_bChkEffective_LaneNo = FALSE;
	m_bChkPlateType_02TypeCivil = FALSE;
	m_bChkPlateType_Agricultural = FALSE;
	m_bChkPlateType_CivilAndMilitary = FALSE;
	m_bChkPlateType_Double = FALSE;
	m_bChkPlateType_Embassy = FALSE;
	m_bChkPlateType_MotorCycle = FALSE;
	m_bChkPlateType_PoliceCar = FALSE;
	m_bChkPlateType_PoliceWagon = FALSE;
	m_bChkPlateColor_Black = FALSE;
	m_bChkPlateColor_Blue = FALSE;
	m_bChkPlateColor_Green = FALSE;
	m_bChkPlateColor_White = FALSE;
	m_bChkPlateColor_Yellow = FALSE;
	m_bChkIllegal_DedicatedLane = FALSE;
	m_bChkIllegal_EmergencyLaneOccupancy = FALSE;
	m_bChkIllegal_GreenParking = FALSE;
	m_bChkIllegal_LaneChange = FALSE;
	m_bChkIllegal_LowSpeed = FALSE;
	m_bChkIllegal_NonMotorLane = FALSE;
	m_bChkIllegal_Other = FALSE;
	m_bChkIllegal_OverLaneLine = FALSE;
	m_bChkIllegal_OverSpeed = FALSE;
	m_bChkIllegal_Parking = FALSE;
	m_bChkIllegal_Pedestrians = FALSE;
	m_bChkIllegal_ProhibitionSign = FALSE;
	m_bChkIllegal_RoadParking = FALSE;
	m_bChkIllegal_Retention = FALSE;
	m_bChkIllegal_RunRedLight = FALSE;
	m_bChkIllegal_SafetyBelt = FALSE;
	m_bChkIllegal_TravelAgainstGuiding = FALSE;
	m_bChkIllegal_TurnAround = FALSE;
	m_bChkIllegal_WrongDir = FALSE;
	m_bChkEvent_BlackList = FALSE;
	m_bChkEvent_Congestion = FALSE;
	m_bChkEvent_Crowd = FALSE;
	m_bChkEvent_LaneChange = FALSE;
	m_bChkEvent_NonMotorVeh = FALSE;
	m_bChkEvent_Other = FALSE;
	m_bChkEvent_OverSpeed = FALSE;
	m_bChkEvent_Parking = FALSE;
	m_bChkEvent_Pedestrians = FALSE;
	m_bChkEvent_PressLine = FALSE;
	m_bChkEvent_Smoke = FALSE;
	m_bChkEvent_ThrowThings = FALSE;
	m_bChkEvent_TurnAround = FALSE;
	m_bChkEvent_WrongDir = FALSE;
	m_bChkForenSice_CityRoad = FALSE;
	m_bChkForenSice_FreeWay = FALSE;
	m_bChkForenSice_LaneChange = FALSE;
	m_bChkForenSice_NonMotorVeh = FALSE;
	m_bChkForenSice_Other = FALSE;
	m_bChkForenSice_PressLine = FALSE;
	m_bChkForenSice_WrongDir = FALSE;
	m_VehType_FreightCar = FALSE;
	m_VehType_LittleFreightCar = FALSE;
	m_VehType_MediumPassengerCarriage = FALSE;
	m_VehType_MicroBus = FALSE;
	m_VehType_Other = FALSE;
	m_VehType_PassengerCarriage = FALSE;
	m_VehType_Passer = FALSE;
	m_VehType_SUVAndMPV = FALSE;
	m_VehType_ThreeWheeler = FALSE;
	m_VehType_TwoWheeler = FALSE;
	m_byLaneNo = 0;
	m_csLicense = _T("");
	m_dwLowSpeed = 0;
	m_dwOverSpeed = 0;
	m_startDate = COleDateTime::GetCurrentTime();
	m_startTime = COleDateTime::GetCurrentTime();
	m_stopDate = COleDateTime::GetCurrentTime();
	m_stopTime = COleDateTime::GetCurrentTime();
	m_bChkVehColor_Deongaree = FALSE;
	m_bChkVehColor_Gray = FALSE;
	m_bChkVehColor_Green = FALSE;
	m_bChkVehColor_Pink = FALSE;
	m_bChkVehColor_Purple = FALSE;
	m_bChkVehColor_Red = FALSE;
	m_bChkVehColor_Silvery = FALSE;
	m_bChkVehColor_White = FALSE;
	m_bChkVehColor_Yellow = FALSE;
	m_VehType_Car = FALSE;
	m_trafficFlowStartDate = COleDateTime::GetCurrentTime();
	m_trafficFlowStartTime = COleDateTime::GetCurrentTime();
	m_trafficFlowStopDate = COleDateTime::GetCurrentTime();
	m_trafficFlowStopTime = COleDateTime::GetCurrentTime();
	m_byTrafficFlowLaneNo = 0;
	m_bChkTrafficData_Channel1 = FALSE;
	m_bChkTrafficData_Channel10 = FALSE;
	m_bChkTrafficData_Channel11 = FALSE;
	m_bChkTrafficData_Channel12 = FALSE;
	m_bChkTrafficData_Channel13 = FALSE;
	m_bChkTrafficData_Channel14 = FALSE;
	m_bChkTrafficData_Channel15 = FALSE;
	m_bChkTrafficData_Channel16 = FALSE;
	m_bChkTrafficData_Channel17 = FALSE;
	m_bChkTrafficData_Channel18 = FALSE;
	m_bChkTrafficData_Channel19 = FALSE;
	m_bChkTrafficData_Channel2 = FALSE;
	m_bChkTrafficData_Channel20 = FALSE;
	m_bChkTrafficData_Channel21 = FALSE;
	m_bChkTrafficData_Channel22 = FALSE;
	m_bChkTrafficData_Channel23 = FALSE;
	m_bChkTrafficData_Channel24 = FALSE;
	m_bChkTrafficData_Channel25 = FALSE;
	m_bChkTrafficData_Channel26 = FALSE;
	m_bChkTrafficData_Channel27 = FALSE;
	m_bChkTrafficData_Channel28 = FALSE;
	m_bChkTrafficData_Channel29 = FALSE;
	m_bChkTrafficData_Channel3 = FALSE;
	m_bChkTrafficData_Channel30 = FALSE;
	m_bChkTrafficData_Channel31 = FALSE;
	m_bChkTrafficData_Channel32 = FALSE;
	m_bChkTrafficData_Channel4 = FALSE;
	m_bChkTrafficData_Channel5 = FALSE;
	m_bChkTrafficData_Channel6 = FALSE;
	m_bChkTrafficData_Channel7 = FALSE;
	m_bChkTrafficData_Channel8 = FALSE;
	m_bChkTrafficData_Channel9 = FALSE;
	m_bChkTrafficFlow_Channel1 = FALSE;
	m_bChkTrafficFlow_Channel10 = FALSE;
	m_bChkTrafficFlow_Channel11 = FALSE;
	m_bChkTrafficFlow_Channel12 = FALSE;
	m_bChkTrafficFlow_Channel13 = FALSE;
	m_bChkTrafficFlow_Channel14 = FALSE;
	m_bChkTrafficFlow_Channel15 = FALSE;
	m_bChkTrafficFlow_Channel16 = FALSE;
	m_bChkTrafficFlow_Channel17 = FALSE;
	m_bChkTrafficFlow_Channel18 = FALSE;
	m_bChkTrafficFlow_Channel19 = FALSE;
	m_bChkTrafficFlow_Channel2 = FALSE;
	m_bChkTrafficFlow_Channel20 = FALSE;
	m_bChkTrafficFlow_Channel21 = FALSE;
	m_bChkTrafficFlow_Channel22 = FALSE;
	m_bChkTrafficFlow_Channel23 = FALSE;
	m_bChkTrafficFlow_Channel24 = FALSE;
	m_bChkTrafficFlow_Channel25 = FALSE;
	m_bChkTrafficFlow_Channel26 = FALSE;
	m_bChkTrafficFlow_Channel27 = FALSE;
	m_bChkTrafficFlow_Channel28 = FALSE;
	m_bChkTrafficFlow_Channel29 = FALSE;
	m_bChkTrafficFlow_Channel3 = FALSE;
	m_bChkTrafficFlow_Channel30 = FALSE;
	m_bChkTrafficFlow_Channel31 = FALSE;
	m_bChkTrafficFlow_Channel32 = FALSE;
	m_bChkTrafficFlow_Channel4 = FALSE;
	m_bChkTrafficFlow_Channel5 = FALSE;
	m_bChkTrafficFlow_Channel6 = FALSE;
	m_bChkTrafficFlow_Channel7 = FALSE;
	m_bChkTrafficFlow_Channel8 = FALSE;
	m_bChkTrafficFlow_Channel9 = FALSE;
	m_bChkQueryCond_Channel = FALSE;
	m_bChkQueryCond_LaneNo = FALSE;
	m_bChkQueryCond_Time = FALSE;
	//}}AFX_DATA_INIT
    memset(&m_struTrafficDataQueryCond, 0, sizeof(m_struTrafficDataQueryCond));
    memset(&m_struTrafficFlowQueryCond, 0, sizeof(m_struTrafficFlowQueryCond));
    m_lServerID = -1; // 用户ID
    m_iDevIndex = -1; // 设备索引
    m_lChannel = -1;
    m_lTrafficDataHandle = -1;
    m_lTrafficFlowHandle = -1;
}

CDlgITSMiniPost::~CDlgITSMiniPost()
{
    StopTrafficData();
    StopTrafficFlow();
}

void CDlgITSMiniPost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSMiniPost)
	DDX_Control(pDX, IDC_LIST_TRAFFIC_FLOW_, m_listTrafficFlow);
	DDX_Control(pDX, IDC_LIST_TRAFFIC_DATA, m_listTrafficData);
	DDX_Control(pDX, IDC_COMBO_VEHICLE_LOGORECOG, m_comVehicleLogorecog);
	DDX_Control(pDX, IDC_COMBO_EXECUTECTRL, m_comExecuteCtrl);
	DDX_Control(pDX, IDC_COMBO_DIRECTION, m_comDirection);
	DDX_Control(pDX, IDC_COMBO_DATATYPE, m_comDataType);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_ALARMTYPE, m_bChkEffective_AlarmType);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_BLACK_VEHICLE, m_bChkVehColor_Black);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_BROWN_VEHICLE, m_bChkVehColor_Brown);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_BULE_VEHICLE, m_bChkVehColor_Bule);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_CHANNEL, m_bChkEffective_Channel);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_DARKGREY_VEHICLE, m_bChkVehColor_DarkGrey);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_DATATYPE, m_bChkEffective_DataType);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_TIME, m_bChkEffective_Time);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_LICENSE, m_bChkEffective_License);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_PLATETYPE, m_bChkEffective_PlateType);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_PLATECOLOER, m_bChkEffective_PlateColor);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_VEHICLEBRAND, m_bChkEffective_VehicleBrand);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_VEHICLECOLOER, m_bChkEffective_VehicleColor);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_VEHICLETYPE, m_bChkEffective_VehicleType);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_DIRECTION, m_bChkEffective_Direction);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_EVADETYPE, m_bChkEffective_EvadeType);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_EVENTTYPE, m_bChkEffective_EventType);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_ILLEGAL, m_bChkEffective_Illegal);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_MAXSPEED, m_bChkEffective_MaxSpeed);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_MINSPEED, m_bChkEffective_MinSpeed);
	DDX_Check(pDX, IDC_CHECK_EFFECTIVE_LANENO, m_bChkEffective_LaneNo);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_02TYPE_CIVIL_LICENSE, m_bChkPlateType_02TypeCivil);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_AGRICULTURAL_LICENSE, m_bChkPlateType_Agricultural);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_CIVIL_AND_MILITARY, m_bChkPlateType_CivilAndMilitary);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_DOUBLE_LICENSE, m_bChkPlateType_Double);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_EMBASSY_LICENSE, m_bChkPlateType_Embassy);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_MOTORCYCLE_LICENSE, m_bChkPlateType_MotorCycle);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_POLICE_CAR, m_bChkPlateType_PoliceCar);
	DDX_Check(pDX, IDC_CHECK_PLATETYPE_POLICE_WAGON, m_bChkPlateType_PoliceWagon);
	DDX_Check(pDX, IDC_CHECK_PLATECOLOR_BLACK_LICENSE, m_bChkPlateColor_Black);
	DDX_Check(pDX, IDC_CHECK_PLATECOLOR_BLUE_LICENSE, m_bChkPlateColor_Blue);
	DDX_Check(pDX, IDC_CHECK_PLATECOLOR_GREEN_LICENSE, m_bChkPlateColor_Green);
	DDX_Check(pDX, IDC_CHECK_PLATECOLOR_WHITE_LICENSE, m_bChkPlateColor_White);
	DDX_Check(pDX, IDC_CHECK_PLATECOLOR_YELLOW_LICENSE, m_bChkPlateColor_Yellow);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_DEDICATED_LANE, m_bChkIllegal_DedicatedLane);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_EMERGENCY_LANE_OCCUPANCY, m_bChkIllegal_EmergencyLaneOccupancy);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_GREEN_PARKING, m_bChkIllegal_GreenParking);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_LANE_CHANGE, m_bChkIllegal_LaneChange);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_LOWSPEED, m_bChkIllegal_LowSpeed);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_NONMOTOR_LANE, m_bChkIllegal_NonMotorLane);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_OTHER, m_bChkIllegal_Other);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_OVERLANELINE, m_bChkIllegal_OverLaneLine);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_OVERSPEED, m_bChkIllegal_OverSpeed);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_PARKING, m_bChkIllegal_Parking);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_PEDESTRIANS, m_bChkIllegal_Pedestrians);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_PROHIBITION_SIGN, m_bChkIllegal_ProhibitionSign);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_ROAD_PARKING, m_bChkIllegal_RoadParking);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_ROAD_RETENTION, m_bChkIllegal_Retention);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_RUNREDLIGHT, m_bChkIllegal_RunRedLight);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_SAFETY_BELT, m_bChkIllegal_SafetyBelt);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_TRAVEL_AGAINST_GUIDING, m_bChkIllegal_TravelAgainstGuiding);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_TURN_AROUND, m_bChkIllegal_TurnAround);
	DDX_Check(pDX, IDC_CHECK_ILLEGAL_WRONGDIR, m_bChkIllegal_WrongDir);
	DDX_Check(pDX, IDC_CHECK_EVENT_BLACK_LIST, m_bChkEvent_BlackList);
	DDX_Check(pDX, IDC_CHECK_EVENT_CONGESTION, m_bChkEvent_Congestion);
	DDX_Check(pDX, IDC_CHECK_EVENT_CROWD, m_bChkEvent_Crowd);
	DDX_Check(pDX, IDC_CHECK_EVENT_LANE_CHANGE, m_bChkEvent_LaneChange);
	DDX_Check(pDX, IDC_CHECK_EVENT_NONMOTOR_VEHICLE, m_bChkEvent_NonMotorVeh);
	DDX_Check(pDX, IDC_CHECK_EVENT_OTHER, m_bChkEvent_Other);
	DDX_Check(pDX, IDC_CHECK_EVENT_OVER_SPEED, m_bChkEvent_OverSpeed);
	DDX_Check(pDX, IDC_CHECK_EVENT_PARKING, m_bChkEvent_Parking);
	DDX_Check(pDX, IDC_CHECK_EVENT_PEDESTRIANS, m_bChkEvent_Pedestrians);
	DDX_Check(pDX, IDC_CHECK_EVENT_PRESS_LINE, m_bChkEvent_PressLine);
	DDX_Check(pDX, IDC_CHECK_EVENT_SMOKE, m_bChkEvent_Smoke);
	DDX_Check(pDX, IDC_CHECK_EVENT_THROW_THINGS, m_bChkEvent_ThrowThings);
	DDX_Check(pDX, IDC_CHECK_EVENT_TURN_AROUND, m_bChkEvent_TurnAround);
	DDX_Check(pDX, IDC_CHECK_EVENT_WRONG_DIR, m_bChkEvent_WrongDir);
	DDX_Check(pDX, IDC_CHECK_FORENSICE_CITY_ROAD, m_bChkForenSice_CityRoad);
	DDX_Check(pDX, IDC_CHECK_FORENSICE_FREEWAY, m_bChkForenSice_FreeWay);
	DDX_Check(pDX, IDC_CHECK_FORENSICE_LANE_CHANGE, m_bChkForenSice_LaneChange);
	DDX_Check(pDX, IDC_CHECK_FORENSICE_NONMOTOR_VEHICLE, m_bChkForenSice_NonMotorVeh);
	DDX_Check(pDX, IDC_CHECK_FORENSICE_OTHER, m_bChkForenSice_Other);
	DDX_Check(pDX, IDC_CHECK_FORENSICE_PRESS_LINE, m_bChkForenSice_PressLine);
	DDX_Check(pDX, IDC_CHECK_FORENSICE_WRONG_DIR, m_bChkForenSice_WrongDir);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_FREIGHT_CAR, m_VehType_FreightCar);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_LITTLE_FREIGHT_CAR, m_VehType_LittleFreightCar);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_MEDIUM_PASSENGER_CARRIAGE, m_VehType_MediumPassengerCarriage);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_MICROBUS, m_VehType_MicroBus);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_OTHER_VEHICLE, m_VehType_Other);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_PASSENGER_CARRIAGE, m_VehType_PassengerCarriage);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_PASSER, m_VehType_Passer);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_SUV_AND_MPV, m_VehType_SUVAndMPV);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_THREE_WHEELER, m_VehType_ThreeWheeler);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_TWO_WHEELER, m_VehType_TwoWheeler);
	DDX_Text(pDX, IDC_EDIT_LANE_NO, m_byLaneNo);
	DDX_Text(pDX, IDC_EDIT_LICENSE, m_csLicense);
	DDX_Text(pDX, IDC_EDIT_LOW_SPEED, m_dwLowSpeed);
	DDX_Text(pDX, IDC_EDIT_OVER_SPEED, m_dwOverSpeed);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
	DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
	DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_DEONGAREE_VEHICLE, m_bChkVehColor_Deongaree);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_GRAY_VEHICLE, m_bChkVehColor_Gray);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_GREEN_VEHICLE, m_bChkVehColor_Green);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_PINK_VEHICLE, m_bChkVehColor_Pink);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_PURPLE_VEHICLE, m_bChkVehColor_Purple);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_RED_VEHICLE, m_bChkVehColor_Red);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_SILVERY_VEHICLE, m_bChkVehColor_Silvery);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_WHITE_VEHICLE, m_bChkVehColor_White);
	DDX_Check(pDX, IDC_CHECK_VEHCOLOR_YELLOW_VEHICLE, m_bChkVehColor_Yellow);
	DDX_Check(pDX, IDC_CHECK_VEHTYPE_CAR, m_VehType_Car);
	DDX_DateTimeCtrl(pDX, IDC_TRAFFIC_FLOW_START_DATE, m_trafficFlowStartDate);
	DDX_DateTimeCtrl(pDX, IDC_TRAFFIC_FLOW_START_TIME, m_trafficFlowStartTime);
	DDX_DateTimeCtrl(pDX, IDC_TRAFFIC_FLOW_STOP_DATE, m_trafficFlowStopDate);
	DDX_DateTimeCtrl(pDX, IDC_TRAFFIC_FLOW_STOP_TIME, m_trafficFlowStopTime);
	DDX_Text(pDX, IDC_EDIT_TRAFFIC_FLOW_LANE_NO, m_byTrafficFlowLaneNo);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_1, m_bChkTrafficData_Channel1);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_10, m_bChkTrafficData_Channel10);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_11, m_bChkTrafficData_Channel11);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_12, m_bChkTrafficData_Channel12);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_13, m_bChkTrafficData_Channel13);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_14, m_bChkTrafficData_Channel14);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_15, m_bChkTrafficData_Channel15);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_16, m_bChkTrafficData_Channel16);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_17, m_bChkTrafficData_Channel17);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_18, m_bChkTrafficData_Channel18);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_19, m_bChkTrafficData_Channel19);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_2, m_bChkTrafficData_Channel2);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_20, m_bChkTrafficData_Channel20);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_21, m_bChkTrafficData_Channel21);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_22, m_bChkTrafficData_Channel22);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_23, m_bChkTrafficData_Channel23);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_24, m_bChkTrafficData_Channel24);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_25, m_bChkTrafficData_Channel25);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_26, m_bChkTrafficData_Channel26);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_27, m_bChkTrafficData_Channel27);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_28, m_bChkTrafficData_Channel28);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_29, m_bChkTrafficData_Channel29);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_3, m_bChkTrafficData_Channel3);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_30, m_bChkTrafficData_Channel30);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_31, m_bChkTrafficData_Channel31);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_32, m_bChkTrafficData_Channel32);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_4, m_bChkTrafficData_Channel4);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_5, m_bChkTrafficData_Channel5);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_6, m_bChkTrafficData_Channel6);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_7, m_bChkTrafficData_Channel7);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_8, m_bChkTrafficData_Channel8);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_DATA_CHANNEL_9, m_bChkTrafficData_Channel9);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_1, m_bChkTrafficFlow_Channel1);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_10, m_bChkTrafficFlow_Channel10);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_11, m_bChkTrafficFlow_Channel11);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_12, m_bChkTrafficFlow_Channel12);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_13, m_bChkTrafficFlow_Channel13);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_14, m_bChkTrafficFlow_Channel14);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_15, m_bChkTrafficFlow_Channel15);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_16, m_bChkTrafficFlow_Channel16);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_17, m_bChkTrafficFlow_Channel17);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_18, m_bChkTrafficFlow_Channel18);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_19, m_bChkTrafficFlow_Channel19);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_2, m_bChkTrafficFlow_Channel2);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_20, m_bChkTrafficFlow_Channel20);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_21, m_bChkTrafficFlow_Channel21);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_22, m_bChkTrafficFlow_Channel22);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_23, m_bChkTrafficFlow_Channel23);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_24, m_bChkTrafficFlow_Channel24);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_25, m_bChkTrafficFlow_Channel25);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_26, m_bChkTrafficFlow_Channel26);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_27, m_bChkTrafficFlow_Channel27);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_28, m_bChkTrafficFlow_Channel28);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_29, m_bChkTrafficFlow_Channel29);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_3, m_bChkTrafficFlow_Channel3);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_30, m_bChkTrafficFlow_Channel30);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_31, m_bChkTrafficFlow_Channel31);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_32, m_bChkTrafficFlow_Channel32);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_4, m_bChkTrafficFlow_Channel4);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_5, m_bChkTrafficFlow_Channel5);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_6, m_bChkTrafficFlow_Channel6);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_7, m_bChkTrafficFlow_Channel7);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_8, m_bChkTrafficFlow_Channel8);
	DDX_Check(pDX, IDC_CHECK_TRAFFIC_FLOW_CHANNEL_9, m_bChkTrafficFlow_Channel9);
	DDX_Check(pDX, IDC_CHECK_QUERYCOND_CHANNEL, m_bChkQueryCond_Channel);
	DDX_Check(pDX, IDC_CHECK_QUERYCOND_LANENO, m_bChkQueryCond_LaneNo);
	DDX_Check(pDX, IDC_CHECK_QUERYCOND_TIME, m_bChkQueryCond_Time);
	//}}AFX_DATA_MAP
}

// CDlgITSMiniPost message handlers
#define WM_AC_GETTRAFFICDATA_FINISH 10001
#define WM_AC_GETTRAFFICFLOW_FINISH 10002
void CALLBACK g_fGetTrafficData(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
void CALLBACK g_fGetTrafficFlow(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);

BEGIN_MESSAGE_MAP(CDlgITSMiniPost, CDialog)
	//{{AFX_MSG_MAP(CDlgITSMiniPost)
	ON_BN_CLICKED(IDC_BTN_GET_TRAFFIC_DATA, OnBtnGetTrafficData)
	ON_BN_CLICKED(IDC_BTN_GET_TRAFFIC_FLOW_, OnBtnGetTrafficFlow)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_AC_GETTRAFFICDATA_FINISH, OnMsgGetTrafficDataFinish)
    ON_MESSAGE(WM_AC_GETTRAFFICFLOW_FINISH, OnMsgGetTrafficFlowFinish)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////


void CALLBACK g_fGetTrafficData(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgITSMiniPost* pDlg = (CDlgITSMiniPost*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcGetTrafficData(dwType,lpBuffer,dwBufLen);
    
}

void CALLBACK g_fGetTrafficFlow(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgITSMiniPost* pDlg = (CDlgITSMiniPost*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcGetTrafficFlow(dwType,lpBuffer,dwBufLen);
    
}

void CDlgITSMiniPost::ProcGetTrafficData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_TRAFFIC_DATA_QUERY_RESULT* pTrafficDataCfg = (NET_DVR_TRAFFIC_DATA_QUERY_RESULT*)lpBuffer;
        AddTrafficDataItem(*pTrafficDataCfg);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_AC_GETTRAFFICDATA_FINISH,0,0);
        }
	}
}

void CDlgITSMiniPost::ProcGetTrafficFlow(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_TRAFFIC_FLOW_QUERY_RESULT* pTrafficFlowCfg = (NET_DVR_TRAFFIC_FLOW_QUERY_RESULT*)lpBuffer;
        AddTrafficFlowItem(*pTrafficFlowCfg);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_AC_GETTRAFFICFLOW_FINISH,0,0);
        }
    }
}

void CDlgITSMiniPost::AddTrafficDataItem(const NET_DVR_TRAFFIC_DATA_QUERY_RESULT &Item)
{
    BOOL bTemp = FALSE;

    int iItemCount = m_listTrafficData.GetItemCount();
	m_listTrafficData.InsertItem(iItemCount, "");
    
    char szStr[2560] = {0};

    //0通道号
	bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
	bTemp = (Item.dwChannel>>0)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "通道1;");
    }

	bTemp = (Item.dwChannel>>1)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道2;", szStr);
    }

	bTemp = (Item.dwChannel>>2)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道3;", szStr);
    }

	bTemp = (Item.dwChannel>>3)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道4;", szStr);
    }

	bTemp = (Item.dwChannel>>4)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道5;", szStr);
    }

	bTemp = (Item.dwChannel>>5)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道6;", szStr);
    }

	bTemp = (Item.dwChannel>>6)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道7;", szStr);
    }
	
	bTemp = (Item.dwChannel>>7)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道8;", szStr);
    }
	
	bTemp = (Item.dwChannel>>8)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道9;", szStr);
    }
	
	bTemp = (Item.dwChannel>>9)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道10;", szStr);
    }
	
	bTemp = (Item.dwChannel>>10)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道11;", szStr);
    }

	bTemp = (Item.dwChannel>>11)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道12;", szStr);
    }
	
	bTemp = (Item.dwChannel>>12)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道13;", szStr);
    }
	
	bTemp = (Item.dwChannel>>13)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道14;", szStr);
    }
	
	bTemp = (Item.dwChannel>>14)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道15;", szStr);
    }
	
	bTemp = (Item.dwChannel>>15)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道16;", szStr);
    }
	
	bTemp = (Item.dwChannel>>16)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道17;", szStr);
    }
	
	bTemp = (Item.dwChannel>>17)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道18;", szStr);
    }
	
	bTemp = (Item.dwChannel>>18)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道19;", szStr);
    }
	
	bTemp = (Item.dwChannel>>19)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道20;", szStr);
    }
	
	bTemp = (Item.dwChannel>>20)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道21;", szStr);
    }

	bTemp = (Item.dwChannel>>21)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道22;", szStr);
    }
	
	bTemp = (Item.dwChannel>>22)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道23;", szStr);
    }
	
	bTemp = (Item.dwChannel>>23)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道24;", szStr);
    }
	
	bTemp = (Item.dwChannel>>24)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道25;", szStr);
    }
	
	bTemp = (Item.dwChannel>>25)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道26;", szStr);
    }
	
	bTemp = (Item.dwChannel>>26)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道27;", szStr);
    }
	
	bTemp = (Item.dwChannel>>27)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道28;", szStr);
    }
	
	bTemp = (Item.dwChannel>>28)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道29;", szStr);
    }
	
	bTemp = (Item.dwChannel>>29)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道30;", szStr);
    }
	
	bTemp = (Item.dwChannel>>30)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道31;", szStr);
    }

	bTemp = (Item.dwChannel>>31)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道32;", szStr);
    }
 	m_listTrafficData.SetItemText(iItemCount, 0, szStr);
	

    //1车牌号
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", Item.sLicense);
	m_listTrafficData.SetItemText(iItemCount, 1, szStr);

    //2车牌类型
    bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
    bTemp = Item.dwPlateType &0x01;
    if (bTemp)
    {
        sprintf(szStr, "未知;");
    }

    bTemp = (Item.dwPlateType>>1)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s标准民用车与军车;", szStr);
    }

    bTemp = (Item.dwPlateType>>2)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s02式民用车牌;", szStr);
    }

    bTemp = (Item.dwPlateType>>3)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s武警车;", szStr);
    }

    bTemp = (Item.dwPlateType>>4)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s警车;", szStr);
    }

    bTemp = (Item.dwPlateType>>5)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s民用车双行尾牌;", szStr);
    }

    bTemp = (Item.dwPlateType>>6)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s使馆车牌;", szStr);
    }

    bTemp = (Item.dwPlateType>>7)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s农用车;", szStr);
    }

    bTemp = (Item.dwPlateType>>8)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s摩托车;", szStr);
    }

    m_listTrafficData.SetItemText(iItemCount, 2, szStr);

    //3车牌颜色
    bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
    bTemp = Item.dwPlateColor &0x01;
    if (bTemp)
    {
        sprintf(szStr, "未知;");
    }

    bTemp = (Item.dwPlateColor>>1)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s黄色;", szStr);
    }

    bTemp = (Item.dwPlateColor>>2)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s白色;", szStr);
    }

    bTemp = (Item.dwPlateColor>>3)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s黑色;", szStr);
    }

    bTemp = (Item.dwPlateColor>>4)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s绿色;", szStr);
    }

    bTemp = (Item.dwPlateColor>>5)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s蓝色;", szStr);
    }

    m_listTrafficData.SetItemText(iItemCount, 3, szStr);


    //4车身颜色
    bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
    bTemp = Item.dwVehicleColor &0x01;
    if (bTemp)
    {
        sprintf(szStr, "未知;");
    }
    
    bTemp = (Item.dwVehicleColor>>1)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s白色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>2)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s银色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>3)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s灰色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>4)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s黑色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>5)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s红色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>6)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s深蓝色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>7)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s蓝色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>8)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s黄色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>9)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s绿色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>10)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s棕色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>11)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s粉色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>12)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s紫色;", szStr);
    }

    bTemp = (Item.dwVehicleColor>>13)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s深灰色;", szStr);
    }

    m_listTrafficData.SetItemText(iItemCount, 4, szStr);

    //5车辆类型
    bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
    bTemp = Item.dwVehicleType &0x01;
    if (bTemp)
    {
        sprintf(szStr, "未知;");
    }
    
    bTemp = (Item.dwVehicleType>>1)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s客车;", szStr);
    }

    bTemp = (Item.dwVehicleType>>2)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s大货车;", szStr);
    }

    bTemp = (Item.dwVehicleType>>3)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s轿车;", szStr);
    }

    bTemp = (Item.dwVehicleType>>4)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s面包车;", szStr);
    }

    bTemp = (Item.dwVehicleType>>5)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s小货车;", szStr);
    }

    bTemp = (Item.dwVehicleType>>6)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s行人;", szStr);
    }

    bTemp = (Item.dwVehicleType>>7)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s二轮车;", szStr);
    }

    bTemp = (Item.dwVehicleType>>8)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s三轮车;", szStr);
    }

    m_listTrafficData.SetItemText(iItemCount, 5, szStr);

    //6违法类型
    bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
    bTemp = Item.dwIllegalType &0x01;
    if (bTemp)
    {
        sprintf(szStr, "未知;");
    }
    
    bTemp = (Item.dwIllegalType>>1)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s低速;", szStr);
    }

    bTemp = (Item.dwIllegalType>>2)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s超速;", szStr);
    }

    bTemp = (Item.dwIllegalType>>3)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s逆行;", szStr);
    }

    bTemp = (Item.dwIllegalType>>4)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s闯红灯;", szStr);
    }

    bTemp = (Item.dwIllegalType>>5)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s压车道线;", szStr);
    }

    bTemp = (Item.dwIllegalType>>6)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s不按导向;", szStr);
    }

    bTemp = (Item.dwIllegalType>>7)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s路口滞留;", szStr);
    }

    bTemp = (Item.dwIllegalType>>8)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s机占非;", szStr);
    }

    bTemp = (Item.dwIllegalType>>9)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s违法变道;", szStr);
    }

    bTemp = (Item.dwIllegalType>>10)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s不按车道;", szStr);
    }

    bTemp = (Item.dwIllegalType>>11)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s违反禁令;", szStr);
    }

    bTemp = (Item.dwIllegalType>>12)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s路口停车;", szStr);
    }

    bTemp = (Item.dwIllegalType>>13)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s绿灯停车;", szStr);
    }

    bTemp = (Item.dwIllegalType>>14)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s未礼让行人;", szStr);
    }

    bTemp = (Item.dwIllegalType>>15)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s违章停车;", szStr);
    }

    bTemp = (Item.dwIllegalType>>16)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s违章掉头;", szStr);
    }

    bTemp = (Item.dwIllegalType>>17)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s占用应急车道;", szStr);
    }

    bTemp = (Item.dwIllegalType>>18)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s未系安全带;", szStr);
    }

    m_listTrafficData.SetItemText(iItemCount, 6, szStr);

    //7事件类型
    bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
    bTemp = Item.dwEventType &0x01;
    if (bTemp)
    {
        sprintf(szStr, "其他;");
    }
    
    bTemp = (Item.dwEventType>>1)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s拥堵;", szStr);
    }

    bTemp = (Item.dwEventType>>2)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s停车;", szStr);
    }

    bTemp = (Item.dwEventType>>3)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s逆行;", szStr);
    }

    bTemp = (Item.dwEventType>>4)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s行人;", szStr);
    }

    bTemp = (Item.dwEventType>>5)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s抛洒物;", szStr);
    }

    bTemp = (Item.dwEventType>>6)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s烟雾;", szStr);
    }

    bTemp = (Item.dwEventType>>7)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s压线;", szStr);
    }

    bTemp = (Item.dwEventType>>8)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s黑名单;", szStr);
    }

    bTemp = (Item.dwEventType>>9)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s超速;", szStr);
    }

    bTemp = (Item.dwEventType>>10)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s变道;", szStr);
    }

    bTemp = (Item.dwEventType>>11)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s掉头;", szStr);
    }

    bTemp = (Item.dwEventType>>12)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s机占非;", szStr);
    }

    bTemp = (Item.dwEventType>>13)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s加塞;", szStr);
    }

    m_listTrafficData.SetItemText(iItemCount, 7, szStr);

    //8取证类型
    bTemp = FALSE;
    memset(szStr, 0, sizeof(szStr));
    bTemp = Item.dwForensiceType &0x01;
    if (bTemp)
    {
        sprintf(szStr, "其他;");
    }
    
    bTemp = (Item.dwForensiceType>>1)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s城市公路违法停车;", szStr);
    }

    bTemp = (Item.dwForensiceType>>2)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s高速公路违法停车;", szStr);
    }

    bTemp = (Item.dwForensiceType>>3)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s压线;", szStr);
    }

    bTemp = (Item.dwForensiceType>>4)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s逆行;", szStr);
    }

    bTemp = (Item.dwForensiceType>>5)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s违法变道;", szStr);
    }

    bTemp = (Item.dwForensiceType>>6)&0x01;
    if (bTemp)
    {
        sprintf(szStr, "%s机占非;", szStr);
    }

    m_listTrafficData.SetItemText(iItemCount, 8, szStr);

    //9车辆主品牌
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d(可参考车辆主品牌.xlsx);", Item.wVehicleLogoRecog);
    m_listTrafficData.SetItemText(iItemCount, 9, szStr);

    //10车道号
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d;", Item.byLaneNo);
    m_listTrafficData.SetItemText(iItemCount, 10, szStr);

    //11监测方向
    memset(szStr, 0, sizeof(szStr));
    if (1 == Item.byDirection)
    {
        sprintf(szStr, "上行");
    } 
    else if (2 == Item.byDirection)
    {
        sprintf(szStr, "下行");
    }
    else if (3 == Item.byDirection)
    {
        sprintf(szStr, "双向");
    }
    else if (4 == Item.byDirection)
    {
        sprintf(szStr, "由东向西");
    }
    else if (5 == Item.byDirection)
    {
        sprintf(szStr, "由南向北");
    }
    else if (6 == Item.byDirection)
    {
        sprintf(szStr, "由西向东");
    }
    else if (7 == Item.byDirection)
    {
        sprintf(szStr, "由北向南");
    }

    m_listTrafficData.SetItemText(iItemCount, 11, szStr);

    //12速度
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%dkm/h;", Item.wSpeed);
    m_listTrafficData.SetItemText(iItemCount, 12, szStr);


    //13数据类型
    memset(szStr, 0, sizeof(szStr));
    if (0 == Item.byDataType)
    {
        sprintf(szStr, "卡口");
    } 
    else if (1 == Item.byDataType)
    {
        sprintf(szStr, "违法");
    }
    else if (2 == Item.byDataType)
    {
        sprintf(szStr, "事件");
    }
    else if (3 == Item.byDataType)
    {
        sprintf(szStr, "取证");
    }

    m_listTrafficData.SetItemText(iItemCount, 13, szStr);


    //14图片信息
    char chRelativeTime[128] = {0};
    char chAbsTime[128] = {0};
    char chPicType[32] = {0};
    memset(szStr, 0, sizeof(szStr));
    for(int i = 0; i<MAX_TRAFFIC_PICTURE_NUM; i++)
    {
        sprintf(chRelativeTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",Item.struTrafficPic[i].struRelativeTime.wYear, \
            Item.struTrafficPic[i].struRelativeTime.byMonth, Item.struTrafficPic[i].struRelativeTime.byDay, Item.struTrafficPic[i].struRelativeTime.byHour,\
            Item.struTrafficPic[i].struRelativeTime.byMinute, Item.struTrafficPic[i].struRelativeTime.bySecond, Item.struTrafficPic[i].struRelativeTime.wMilliSec);

        sprintf(chAbsTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",Item.struTrafficPic[i].struAbsTime.wYear, \
            Item.struTrafficPic[i].struAbsTime.byMonth, Item.struTrafficPic[i].struAbsTime.byDay, Item.struTrafficPic[i].struAbsTime.byHour,\
            Item.struTrafficPic[i].struAbsTime.byMinute, Item.struTrafficPic[i].struAbsTime.bySecond, Item.struTrafficPic[i].struAbsTime.wMilliSec);

        if (0 == Item.struTrafficPic[i].byPicType)
        {
            sprintf(chPicType, "车牌图");
        } 
        else if (1 == Item.struTrafficPic[i].byPicType)
        {
            sprintf(chPicType, "抓拍原图");
        }
        else if (2 == Item.struTrafficPic[i].byPicType)
        {
            sprintf(chPicType, "合成图");
        }
        else if (3 == Item.struTrafficPic[i].byPicType)
        {
            sprintf(chPicType, "特写图");
        }

        sprintf(szStr, "%s第%d张图{相对时标:%s,绝对时标:%s,图片名称:%s,图片类型:%s};", szStr, i, chRelativeTime, chAbsTime, \
            Item.struTrafficPic[i].szPicName, chPicType);
    }
    m_listTrafficData.SetItemText(iItemCount, 14, szStr);
}

void CDlgITSMiniPost::AddTrafficFlowItem(const NET_DVR_TRAFFIC_FLOW_QUERY_RESULT &Item)
{
    BOOL bTemp = FALSE;
    
    int iItemCount = m_listTrafficFlow.GetItemCount();
    m_listTrafficFlow.InsertItem(iItemCount, "");
    
    char szStr[1280] = {0};

    //0开始时间
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",Item.struStartTime.wYear, \
        Item.struStartTime.byMonth, Item.struStartTime.byDay, Item.struStartTime.byHour,\
        Item.struStartTime.byMinute, Item.struStartTime.bySecond, Item.struStartTime.wMilliSec);
    m_listTrafficFlow.SetItemText(iItemCount, 0, szStr);

    //1结束时间
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",Item.struEndTime.wYear, \
        Item.struEndTime.byMonth, Item.struEndTime.byDay, Item.struEndTime.byHour,\
        Item.struEndTime.byMinute, Item.struEndTime.bySecond, Item.struEndTime.wMilliSec);
    m_listTrafficFlow.SetItemText(iItemCount, 1, szStr);

    //2通道号
    memset(szStr, 0, sizeof(szStr));
	bTemp = (Item.dwChannel>>0)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "通道1;");
    }

	bTemp = (Item.dwChannel>>1)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道2;", szStr);
    }

	bTemp = (Item.dwChannel>>2)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道3;", szStr);
    }

	bTemp = (Item.dwChannel>>3)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道4;", szStr);
    }

	bTemp = (Item.dwChannel>>4)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道5;", szStr);
    }

	bTemp = (Item.dwChannel>>5)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道6;", szStr);
    }

	bTemp = (Item.dwChannel>>6)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道7;", szStr);
    }
	
	bTemp = (Item.dwChannel>>7)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道8;", szStr);
    }
	
	bTemp = (Item.dwChannel>>8)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道9;", szStr);
    }
	
	bTemp = (Item.dwChannel>>9)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道10;", szStr);
    }
	
	bTemp = (Item.dwChannel>>10)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道11;", szStr);
    }

	bTemp = (Item.dwChannel>>11)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道12;", szStr);
    }
	
	bTemp = (Item.dwChannel>>12)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道13;", szStr);
    }
	
	bTemp = (Item.dwChannel>>13)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道14;", szStr);
    }
	
	bTemp = (Item.dwChannel>>14)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道15;", szStr);
    }
	
	bTemp = (Item.dwChannel>>15)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道16;", szStr);
    }
	
	bTemp = (Item.dwChannel>>16)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道17;", szStr);
    }
	
	bTemp = (Item.dwChannel>>17)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道18;", szStr);
    }
	
	bTemp = (Item.dwChannel>>18)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道19;", szStr);
    }
	
	bTemp = (Item.dwChannel>>19)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道20;", szStr);
    }
	
	bTemp = (Item.dwChannel>>20)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道21;", szStr);
    }

	bTemp = (Item.dwChannel>>21)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道22;", szStr);
    }
	
	bTemp = (Item.dwChannel>>22)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道23;", szStr);
    }
	
	bTemp = (Item.dwChannel>>23)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道24;", szStr);
    }
	
	bTemp = (Item.dwChannel>>24)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道25;", szStr);
    }
	
	bTemp = (Item.dwChannel>>25)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道26;", szStr);
    }
	
	bTemp = (Item.dwChannel>>26)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道27;", szStr);
    }
	
	bTemp = (Item.dwChannel>>27)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道28;", szStr);
    }
	
	bTemp = (Item.dwChannel>>28)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道29;", szStr);
    }
	
	bTemp = (Item.dwChannel>>29)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道30;", szStr);
    }
	
	bTemp = (Item.dwChannel>>30)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道31;", szStr);
    }

	bTemp = (Item.dwChannel>>31)&0x01;
	if (bTemp)
    {
        sprintf(szStr, "%s通道32;", szStr);
    }
    //sprintf(szStr, "%d", Item.dwChannel);
    m_listTrafficFlow.SetItemText(iItemCount, 2, szStr);

    //3车流量
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwFlow);
    m_listTrafficFlow.SetItemText(iItemCount, 3, szStr);

    //4车道号
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.byLaneNo);
    m_listTrafficFlow.SetItemText(iItemCount, 4, szStr);

 

}


LRESULT CDlgITSMiniPost::OnMsgGetTrafficDataFinish(WPARAM wParam,LPARAM lParam)
{
    StopTrafficData();
    return 0;
}

LRESULT CDlgITSMiniPost::OnMsgGetTrafficFlowFinish(WPARAM wParam,LPARAM lParam)
{
    StopTrafficFlow();
    return 0;
}

void CDlgITSMiniPost::StopTrafficData()
{
    char szLan[128] = {0};
    if (m_lTrafficDataHandle>=0)
    {
		if (!NET_DVR_StopRemoteConfig(m_lTrafficDataHandle))
        {
            g_StringLanType(szLan, "交通数据查询停止失败", "Traffic Data List Stop Failed");
            AfxMessageBox(szLan);
            return;
        }
        m_lTrafficDataHandle = -1;
    }
}

void CDlgITSMiniPost::StopTrafficFlow()
{
    char szLan[128] = {0};
    if (m_lTrafficFlowHandle>=0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lTrafficFlowHandle))
        {
            g_StringLanType(szLan, "交通流量查询停止失败", "Traffic Flow List Stop Failed");
            AfxMessageBox(szLan);
            return;
        }
        m_lTrafficFlowHandle = -1;
    }
}

void CDlgITSMiniPost::OnBtnGetTrafficData() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};

    if (m_lTrafficDataHandle>=0)
    {
        StopTrafficData();
    }
    
    SetTrafficDataCond();
    m_lTrafficDataHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_TRAFFIC_DATA,&m_struTrafficDataQueryCond,sizeof(m_struTrafficDataQueryCond),g_fGetTrafficData, this);
    if (m_lTrafficDataHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRAFFIC_DATA");
        return;
    }
    else
    {
        m_listTrafficData.DeleteAllItems();
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRAFFIC_DATA");
	}
}

BOOL CDlgITSMiniPost::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    char szLanTemp[128] = {0};
    m_listTrafficData.SetExtendedStyle(m_listTrafficData.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "通道号", "Channel");
    m_listTrafficData.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车牌号", "License");
    m_listTrafficData.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车牌类型", "Plate Type");
    m_listTrafficData.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车牌颜色", "Plate Color");
    m_listTrafficData.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车身颜色", "Vehicle Color");
    m_listTrafficData.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车辆类型", "Vehicle Type");
    m_listTrafficData.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "违法类型", "Illegal Type");
    m_listTrafficData.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "事件类型", "Event Type");
    m_listTrafficData.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "取证类型", "Forensice Type");
    m_listTrafficData.InsertColumn(8, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车辆主品牌", "Vehicle Logo");
    m_listTrafficData.InsertColumn(9, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车道号", "Lane No");
    m_listTrafficData.InsertColumn(10, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "监测方向", "Direction");
    m_listTrafficData.InsertColumn(11, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "速度", "Speed");
    m_listTrafficData.InsertColumn(12, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "数据类型", "Data Type");
    m_listTrafficData.InsertColumn(13, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "图片参数", "Picture Info");
    m_listTrafficData.InsertColumn(14, szLanTemp, LVCFMT_LEFT, 1000, -1);

   
    m_listTrafficFlow.SetExtendedStyle(m_listTrafficFlow.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "开始时间", "Start Time");
    m_listTrafficFlow.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);    
    g_StringLanType(szLanTemp, "结束时间", "End Time");
    m_listTrafficFlow.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);   
    g_StringLanType(szLanTemp, "通道号", "Channel");
    m_listTrafficFlow.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车流量", "Flow");
    m_listTrafficFlow.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "车道号", "Lane No");
    m_listTrafficFlow.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 60, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgITSMiniPost::SetTrafficDataCond()
{
    UpdateData(TRUE);
    memset(&m_struTrafficDataQueryCond, 0, sizeof(m_struTrafficDataQueryCond));
    m_struTrafficDataQueryCond.dwSize = sizeof(m_struTrafficDataQueryCond);

    m_struTrafficDataQueryCond.dwQueryCond = 0;
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_Channel << 0);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_Time << 1);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_License << 2);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_PlateType << 3);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_PlateColor << 4);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_VehicleColor << 5);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_VehicleType << 6);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_VehicleBrand << 7);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_LaneNo << 8);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_Direction << 9);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_MinSpeed << 10);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_MaxSpeed << 11);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_DataType << 12);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_AlarmType<< 13);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_Illegal<< 14);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_EventType<< 15);
    m_struTrafficDataQueryCond.dwQueryCond |= (m_bChkEffective_EvadeType<< 16);
    
    m_struTrafficDataQueryCond.dwChannel = 0;
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel1 << 0);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel2 << 1);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel3 << 2);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel4 << 3);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel5 << 4);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel6 << 5);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel7 << 6);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel8 << 7);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel9 << 8);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel10 << 9);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel11 << 10);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel12 << 11);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel13 << 12);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel14 << 13);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel15 << 14);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel16 << 15);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel17 << 16);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel18 << 17);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel19 << 18);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel20 << 19);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel21 << 20);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel22 << 21);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel23 << 22);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel24 << 23);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel25 << 24);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel26 << 25);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel27 << 26);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel28 << 28);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel29 << 29);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel30 << 29);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel31 << 30);
    m_struTrafficDataQueryCond.dwChannel |= (m_bChkTrafficData_Channel32 << 31);

    m_struTrafficDataQueryCond.struStartTime.wYear = m_startDate.GetYear();
    m_struTrafficDataQueryCond.struStartTime.byMonth = m_startDate.GetMonth();
    m_struTrafficDataQueryCond.struStartTime.byDay = m_startDate.GetDay();
    m_struTrafficDataQueryCond.struStartTime.byHour = m_startTime.GetHour();
    m_struTrafficDataQueryCond.struStartTime.byMinute = m_startTime.GetMinute();
    m_struTrafficDataQueryCond.struStartTime.bySecond = m_startTime.GetSecond();
    
    m_struTrafficDataQueryCond.struEndTime.wYear = m_stopDate.GetYear();
    m_struTrafficDataQueryCond.struEndTime.byMonth = m_stopDate.GetMonth();
    m_struTrafficDataQueryCond.struEndTime.byDay = m_stopDate.GetDay();
    m_struTrafficDataQueryCond.struEndTime.byHour = m_stopTime.GetHour();
    m_struTrafficDataQueryCond.struEndTime.byMinute = m_stopTime.GetMinute();
	m_struTrafficDataQueryCond.struEndTime.bySecond = m_stopTime.GetSecond();

    memcpy(m_struTrafficDataQueryCond.sLicense, m_csLicense.GetBuffer(0), m_csLicense.GetLength());

    m_struTrafficDataQueryCond.dwPlateType = 0;
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_CivilAndMilitary << 1);
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_02TypeCivil << 2);
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_PoliceCar << 3);
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_PoliceWagon << 4);
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_Double << 5);
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_Embassy << 6);
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_Agricultural << 7);
    m_struTrafficDataQueryCond.dwPlateType |= (m_bChkPlateType_MotorCycle << 8);

    m_struTrafficDataQueryCond.dwPlateColor = 0;
    m_struTrafficDataQueryCond.dwPlateColor |= (m_bChkPlateColor_Yellow << 1);
    m_struTrafficDataQueryCond.dwPlateColor |= (m_bChkPlateColor_White << 2);
    m_struTrafficDataQueryCond.dwPlateColor |= (m_bChkPlateColor_Black << 3);
    m_struTrafficDataQueryCond.dwPlateColor |= (m_bChkPlateColor_Green << 4);
    m_struTrafficDataQueryCond.dwPlateColor |= (m_bChkPlateColor_Blue << 5);

    m_struTrafficDataQueryCond.dwVehicleColor = 0;
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_White << 1);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Silvery << 2);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Gray << 3);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Black << 4);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Red << 5);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Deongaree << 6);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Bule << 7);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Yellow << 8);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Green << 9);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Brown << 10);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Pink << 11);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_Purple << 12);
    m_struTrafficDataQueryCond.dwVehicleColor |= (m_bChkVehColor_DarkGrey << 13);

    m_struTrafficDataQueryCond.dwVehicleType = 0;
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_PassengerCarriage << 1);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_FreightCar << 2);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_Car << 3);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_MicroBus << 4);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_LittleFreightCar << 5);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_Passer << 6);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_TwoWheeler << 7);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_ThreeWheeler << 8);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_SUVAndMPV << 9);
    m_struTrafficDataQueryCond.dwVehicleType |= (m_VehType_MediumPassengerCarriage << 10);

    m_struTrafficDataQueryCond.dwIllegalType = 0;
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_LowSpeed << 1);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_OverSpeed << 2);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_WrongDir << 3);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_RunRedLight << 4);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_OverLaneLine << 5);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_TravelAgainstGuiding << 6);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_Retention << 7);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_NonMotorLane << 8);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_LaneChange << 9);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_DedicatedLane << 10);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_ProhibitionSign << 11);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_RoadParking << 12);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_GreenParking << 13);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_Pedestrians << 14);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_Parking << 15);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_TurnAround << 16);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_EmergencyLaneOccupancy << 17);
    m_struTrafficDataQueryCond.dwIllegalType |= (m_bChkIllegal_SafetyBelt << 18);

    m_struTrafficDataQueryCond.dwEventType = 0;
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_Congestion << 1);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_Parking << 2);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_WrongDir << 3);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_Pedestrians << 4);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_ThrowThings << 5);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_Smoke << 6);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_PressLine << 7);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_BlackList << 8);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_OverSpeed << 9);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_LaneChange << 10);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_TurnAround << 11);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_NonMotorVeh << 12);
    m_struTrafficDataQueryCond.dwEventType |= (m_bChkEvent_Crowd << 13);

    m_struTrafficDataQueryCond.dwForensiceType = 0;
    m_struTrafficDataQueryCond.dwForensiceType |= (m_bChkForenSice_CityRoad << 1);
    m_struTrafficDataQueryCond.dwForensiceType |= (m_bChkForenSice_FreeWay << 2);
    m_struTrafficDataQueryCond.dwForensiceType |= (m_bChkForenSice_PressLine << 3);
    m_struTrafficDataQueryCond.dwForensiceType |= (m_bChkForenSice_WrongDir << 4);
    m_struTrafficDataQueryCond.dwForensiceType |= (m_bChkForenSice_LaneChange << 5);
    m_struTrafficDataQueryCond.dwForensiceType |= (m_bChkForenSice_NonMotorVeh << 6);

    m_struTrafficDataQueryCond.wVehicleLogoRecog = m_comVehicleLogorecog.GetCurSel();
    m_struTrafficDataQueryCond.byLaneNo = m_byLaneNo;
    m_struTrafficDataQueryCond.byDirection = m_comDirection.GetCurSel() + 1;
    m_struTrafficDataQueryCond.wMinSpeed = m_dwLowSpeed;
    m_struTrafficDataQueryCond.wMaxSpeed = m_dwOverSpeed;
    m_struTrafficDataQueryCond.byDataType = m_comDataType.GetCurSel();
    if (2 == m_comExecuteCtrl.GetCurSel())
    {
        m_struTrafficDataQueryCond.byExecuteCtrl = 0xff;
    } 
    else
    {
         m_struTrafficDataQueryCond.byExecuteCtrl = m_comExecuteCtrl.GetCurSel();
    }
   

}

void CDlgITSMiniPost::SetTrafficFlowCond()
{
    UpdateData(TRUE);
    memset(&m_struTrafficFlowQueryCond, 0, sizeof(m_struTrafficFlowQueryCond));
    m_struTrafficFlowQueryCond.dwSize = sizeof(m_struTrafficFlowQueryCond);

    m_struTrafficFlowQueryCond.dwQueryCond = 0;
    m_struTrafficFlowQueryCond.dwQueryCond |= (m_bChkQueryCond_Channel << 0);
    m_struTrafficFlowQueryCond.dwQueryCond |= (m_bChkQueryCond_Time << 1);
    m_struTrafficFlowQueryCond.dwQueryCond |= (m_bChkQueryCond_LaneNo << 2);

    m_struTrafficFlowQueryCond.dwChannel = 0;
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel1 << 0);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel2 << 1);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel3 << 2);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel4 << 3);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel5 << 4);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel6 << 5);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel7 << 6);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel8 << 7);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel9 << 8);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel10 << 9);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel11 << 10);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel12 << 11);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel13 << 12);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel14 << 13);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel15 << 14);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel16 << 15);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel17 << 16);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel18 << 17);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel19 << 18);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel20 << 19);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel21 << 20);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel22 << 21);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel23 << 22);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel24 << 23);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel25 << 24);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel26 << 25);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel27 << 26);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel28 << 28);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel29 << 29);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel30 << 29);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel31 << 30);
    m_struTrafficFlowQueryCond.dwChannel |= (m_bChkTrafficFlow_Channel32 << 31);

    m_struTrafficFlowQueryCond.struStartTime.wYear = m_trafficFlowStartDate.GetYear();
    m_struTrafficFlowQueryCond.struStartTime.byMonth = m_trafficFlowStartDate.GetMonth();
    m_struTrafficFlowQueryCond.struStartTime.byDay = m_trafficFlowStartDate.GetDay();
    m_struTrafficFlowQueryCond.struStartTime.byHour = m_trafficFlowStartTime.GetHour();
    m_struTrafficFlowQueryCond.struStartTime.byMinute = m_trafficFlowStartTime.GetMinute();
    m_struTrafficFlowQueryCond.struStartTime.bySecond = m_trafficFlowStartTime.GetSecond();
    
    m_struTrafficFlowQueryCond.struEndTime.wYear = m_trafficFlowStopDate.GetYear();
    m_struTrafficFlowQueryCond.struEndTime.byMonth = m_trafficFlowStopDate.GetMonth();
    m_struTrafficFlowQueryCond.struEndTime.byDay = m_trafficFlowStopDate.GetDay();
    m_struTrafficFlowQueryCond.struEndTime.byHour = m_trafficFlowStopTime.GetHour();
    m_struTrafficFlowQueryCond.struEndTime.byMinute = m_trafficFlowStopTime.GetMinute();
	m_struTrafficFlowQueryCond.struEndTime.bySecond = m_trafficFlowStopTime.GetSecond();

    m_struTrafficFlowQueryCond.byLaneNo = m_byTrafficFlowLaneNo;
}

void CDlgITSMiniPost::OnBtnGetTrafficFlow() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    
    if (m_lTrafficFlowHandle>=0)
    {
        StopTrafficFlow();
    }
    
    SetTrafficFlowCond();
    m_lTrafficFlowHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_TRAFFIC_FLOW,&m_struTrafficFlowQueryCond,sizeof(m_struTrafficFlowQueryCond),g_fGetTrafficFlow, this);
    if (m_lTrafficFlowHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRAFFIC_FLOW");
        return;
    }
    else
    {
        m_listTrafficFlow.DeleteAllItems();
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRAFFIC_FLOW");
	}
}

