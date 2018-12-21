#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"
#include "ATLComTime.h"
#include "afxwin.h"


// CDlgVehicleInfo 对话框

class CDlgVehicleInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVehicleInfo)

public:
	CDlgVehicleInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVehicleInfo();

// 对话框数据
	enum { IDD = IDD_DLG_GET_VEHICLE_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    void AddToVehicleInfoList(const NET_DVR_VEHICLE_INFO_CFG& struVehicleInfoCfg);
    afx_msg LRESULT OnMsgAddVehicleInfoCfgToList(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgGetVehicleInfoCfgFinish(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGet();
    CListCtrl m_vehicleinfolist;
    virtual BOOL OnInitDialog();
    CDateTimeCtrl m_starttimectrl;
    COleDateTime m_startdate;
    COleDateTime m_starttime;
    COleDateTime m_enddate;
    COleDateTime m_endtime;
    CString m_vehicleinfo;
    CComboBox m_region;
    LONG m_lVehicleInfoCfgHandle;
    LONG m_lUserID;
    LONG m_iDeviceIndex;
    LONG m_lChannel;
    void ProcessGetVehicleInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
};
