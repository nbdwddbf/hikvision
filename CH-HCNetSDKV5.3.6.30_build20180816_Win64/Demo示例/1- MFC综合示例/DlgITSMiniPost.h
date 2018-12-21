#if !defined(AFX_DLGITSMINIPOST_H__F86621D7_45EB_454B_8450_C43592BF68A8__INCLUDED_)
#define AFX_DLGITSMINIPOST_H__F86621D7_45EB_454B_8450_C43592BF68A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSMiniPost.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSMiniPost dialog

class CDlgITSMiniPost : public CDialog
{
// Construction
public:
	CDlgITSMiniPost(CWnd* pParent = NULL);   // standard constructor
    ~CDlgITSMiniPost();
// Dialog Data
	//{{AFX_DATA(CDlgITSMiniPost)
	enum { IDD = IDD_DLG_ITS_MINI_POST };
	CListCtrl	m_listTrafficFlow;
	CListCtrl	m_listTrafficData;
	CComboBox	m_comVehicleLogorecog;
	CComboBox	m_comExecuteCtrl;
	CComboBox	m_comDirection;
	CComboBox	m_comDataType;
	BOOL	m_bChkEffective_AlarmType;
	BOOL	m_bChkVehColor_Black;
	BOOL	m_bChkVehColor_Brown;
	BOOL	m_bChkVehColor_Bule;
	BOOL	m_bChkEffective_Channel;
	BOOL	m_bChkVehColor_DarkGrey;
	BOOL	m_bChkEffective_DataType;
	BOOL	m_bChkEffective_Time;
	BOOL	m_bChkEffective_License;
	BOOL	m_bChkEffective_PlateType;
	BOOL	m_bChkEffective_PlateColor;
	BOOL	m_bChkEffective_VehicleBrand;
	BOOL	m_bChkEffective_VehicleColor;
	BOOL	m_bChkEffective_VehicleType;
	BOOL	m_bChkEffective_Direction;
	BOOL	m_bChkEffective_EvadeType;
	BOOL	m_bChkEffective_EventType;
	BOOL	m_bChkEffective_Illegal;
	BOOL	m_bChkEffective_MaxSpeed;
	BOOL	m_bChkEffective_MinSpeed;
	BOOL	m_bChkEffective_LaneNo;
	BOOL	m_bChkPlateType_02TypeCivil;
	BOOL	m_bChkPlateType_Agricultural;
	BOOL	m_bChkPlateType_CivilAndMilitary;
	BOOL	m_bChkPlateType_Double;
	BOOL	m_bChkPlateType_Embassy;
	BOOL	m_bChkPlateType_MotorCycle;
	BOOL	m_bChkPlateType_PoliceCar;
	BOOL	m_bChkPlateType_PoliceWagon;
	BOOL	m_bChkPlateColor_Black;
	BOOL	m_bChkPlateColor_Blue;
	BOOL	m_bChkPlateColor_Green;
	BOOL	m_bChkPlateColor_White;
	BOOL	m_bChkPlateColor_Yellow;
	BOOL	m_bChkIllegal_DedicatedLane;
	BOOL	m_bChkIllegal_EmergencyLaneOccupancy;
	BOOL	m_bChkIllegal_GreenParking;
	BOOL	m_bChkIllegal_LaneChange;
	BOOL	m_bChkIllegal_LowSpeed;
	BOOL	m_bChkIllegal_NonMotorLane;
	BOOL	m_bChkIllegal_Other;
	BOOL	m_bChkIllegal_OverLaneLine;
	BOOL	m_bChkIllegal_OverSpeed;
	BOOL	m_bChkIllegal_Parking;
	BOOL	m_bChkIllegal_Pedestrians;
	BOOL	m_bChkIllegal_ProhibitionSign;
	BOOL	m_bChkIllegal_RoadParking;
	BOOL	m_bChkIllegal_Retention;
	BOOL	m_bChkIllegal_RunRedLight;
	BOOL	m_bChkIllegal_SafetyBelt;
	BOOL	m_bChkIllegal_TravelAgainstGuiding;
	BOOL	m_bChkIllegal_TurnAround;
	BOOL	m_bChkIllegal_WrongDir;
	BOOL	m_bChkEvent_BlackList;
	BOOL	m_bChkEvent_Congestion;
	BOOL	m_bChkEvent_Crowd;
	BOOL	m_bChkEvent_LaneChange;
	BOOL	m_bChkEvent_NonMotorVeh;
	BOOL	m_bChkEvent_Other;
	BOOL	m_bChkEvent_OverSpeed;
	BOOL	m_bChkEvent_Parking;
	BOOL	m_bChkEvent_Pedestrians;
	BOOL	m_bChkEvent_PressLine;
	BOOL	m_bChkEvent_Smoke;
	BOOL	m_bChkEvent_ThrowThings;
	BOOL	m_bChkEvent_TurnAround;
	BOOL	m_bChkEvent_WrongDir;
	BOOL	m_bChkForenSice_CityRoad;
	BOOL	m_bChkForenSice_FreeWay;
	BOOL	m_bChkForenSice_LaneChange;
	BOOL	m_bChkForenSice_NonMotorVeh;
	BOOL	m_bChkForenSice_Other;
	BOOL	m_bChkForenSice_PressLine;
	BOOL	m_bChkForenSice_WrongDir;
	BOOL	m_VehType_FreightCar;
	BOOL	m_VehType_LittleFreightCar;
	BOOL	m_VehType_MediumPassengerCarriage;
	BOOL	m_VehType_MicroBus;
	BOOL	m_VehType_Other;
	BOOL	m_VehType_PassengerCarriage;
	BOOL	m_VehType_Passer;
	BOOL	m_VehType_SUVAndMPV;
	BOOL	m_VehType_ThreeWheeler;
	BOOL	m_VehType_TwoWheeler;
	BYTE	m_byLaneNo;
	CString	m_csLicense;
	DWORD	m_dwLowSpeed;
	DWORD	m_dwOverSpeed;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	BOOL	m_bChkVehColor_Deongaree;
	BOOL	m_bChkVehColor_Gray;
	BOOL	m_bChkVehColor_Green;
	BOOL	m_bChkVehColor_Pink;
	BOOL	m_bChkVehColor_Purple;
	BOOL	m_bChkVehColor_Red;
	BOOL	m_bChkVehColor_Silvery;
	BOOL	m_bChkVehColor_White;
	BOOL	m_bChkVehColor_Yellow;
	BOOL	m_VehType_Car;
	COleDateTime	m_trafficFlowStartDate;
	COleDateTime	m_trafficFlowStartTime;
	COleDateTime	m_trafficFlowStopDate;
	COleDateTime	m_trafficFlowStopTime;
	BYTE	m_byTrafficFlowLaneNo;
	BOOL	m_bChkTrafficData_Channel1;
	BOOL	m_bChkTrafficData_Channel10;
	BOOL	m_bChkTrafficData_Channel11;
	BOOL	m_bChkTrafficData_Channel12;
	BOOL	m_bChkTrafficData_Channel13;
	BOOL	m_bChkTrafficData_Channel14;
	BOOL	m_bChkTrafficData_Channel15;
	BOOL	m_bChkTrafficData_Channel16;
	BOOL	m_bChkTrafficData_Channel17;
	BOOL	m_bChkTrafficData_Channel18;
	BOOL	m_bChkTrafficData_Channel19;
	BOOL	m_bChkTrafficData_Channel2;
	BOOL	m_bChkTrafficData_Channel20;
	BOOL	m_bChkTrafficData_Channel21;
	BOOL	m_bChkTrafficData_Channel22;
	BOOL	m_bChkTrafficData_Channel23;
	BOOL	m_bChkTrafficData_Channel24;
	BOOL	m_bChkTrafficData_Channel25;
	BOOL	m_bChkTrafficData_Channel26;
	BOOL	m_bChkTrafficData_Channel27;
	BOOL	m_bChkTrafficData_Channel28;
	BOOL	m_bChkTrafficData_Channel29;
	BOOL	m_bChkTrafficData_Channel3;
	BOOL	m_bChkTrafficData_Channel30;
	BOOL	m_bChkTrafficData_Channel31;
	BOOL	m_bChkTrafficData_Channel32;
	BOOL	m_bChkTrafficData_Channel4;
	BOOL	m_bChkTrafficData_Channel5;
	BOOL	m_bChkTrafficData_Channel6;
	BOOL	m_bChkTrafficData_Channel7;
	BOOL	m_bChkTrafficData_Channel8;
	BOOL	m_bChkTrafficData_Channel9;
	BOOL	m_bChkTrafficFlow_Channel1;
	BOOL	m_bChkTrafficFlow_Channel10;
	BOOL	m_bChkTrafficFlow_Channel11;
	BOOL	m_bChkTrafficFlow_Channel12;
	BOOL	m_bChkTrafficFlow_Channel13;
	BOOL	m_bChkTrafficFlow_Channel14;
	BOOL	m_bChkTrafficFlow_Channel15;
	BOOL	m_bChkTrafficFlow_Channel16;
	BOOL	m_bChkTrafficFlow_Channel17;
	BOOL	m_bChkTrafficFlow_Channel18;
	BOOL	m_bChkTrafficFlow_Channel19;
	BOOL	m_bChkTrafficFlow_Channel2;
	BOOL	m_bChkTrafficFlow_Channel20;
	BOOL	m_bChkTrafficFlow_Channel21;
	BOOL	m_bChkTrafficFlow_Channel22;
	BOOL	m_bChkTrafficFlow_Channel23;
	BOOL	m_bChkTrafficFlow_Channel24;
	BOOL	m_bChkTrafficFlow_Channel25;
	BOOL	m_bChkTrafficFlow_Channel26;
	BOOL	m_bChkTrafficFlow_Channel27;
	BOOL	m_bChkTrafficFlow_Channel28;
	BOOL	m_bChkTrafficFlow_Channel29;
	BOOL	m_bChkTrafficFlow_Channel3;
	BOOL	m_bChkTrafficFlow_Channel30;
	BOOL	m_bChkTrafficFlow_Channel31;
	BOOL	m_bChkTrafficFlow_Channel32;
	BOOL	m_bChkTrafficFlow_Channel4;
	BOOL	m_bChkTrafficFlow_Channel5;
	BOOL	m_bChkTrafficFlow_Channel6;
	BOOL	m_bChkTrafficFlow_Channel7;
	BOOL	m_bChkTrafficFlow_Channel8;
	BOOL	m_bChkTrafficFlow_Channel9;
	BOOL	m_bChkQueryCond_Channel;
	BOOL	m_bChkQueryCond_LaneNo;
	BOOL	m_bChkQueryCond_Time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSMiniPost)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSMiniPost)
	afx_msg void OnBtnGetTrafficData();
    afx_msg LRESULT OnMsgGetTrafficDataFinish(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnMsgGetTrafficFlowFinish(WPARAM wParam,LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetTrafficFlow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG        m_lServerID; // 用户ID
    int         m_iDevIndex; // 设备索引
    LONG        m_lChannel;
    LONG        m_lTrafficDataHandle;
    LONG        m_lTrafficFlowHandle;
    NET_DVR_TRAFFIC_DATA_QUERY_COND m_struTrafficDataQueryCond;
    NET_DVR_TRAFFIC_FLOW_QUERY_COND m_struTrafficFlowQueryCond;

    void SetTrafficDataCond();
    void ProcGetTrafficData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void AddTrafficDataItem(const NET_DVR_TRAFFIC_DATA_QUERY_RESULT &Item); 
    void StopTrafficData();

    void SetTrafficFlowCond();
    void ProcGetTrafficFlow(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void AddTrafficFlowItem(const NET_DVR_TRAFFIC_FLOW_QUERY_RESULT &Item); 
    void StopTrafficFlow();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSMINIPOST_H__F86621D7_45EB_454B_8450_C43592BF68A8__INCLUDED_)
