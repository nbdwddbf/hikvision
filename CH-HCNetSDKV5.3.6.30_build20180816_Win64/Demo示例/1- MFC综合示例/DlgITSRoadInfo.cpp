// DlgITSRoadInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSRoadInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSRoadInfo dialog


CDlgITSRoadInfo::CDlgITSRoadInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSRoadInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSRoadInfo)
	m_dwChannel = 0;
	m_csDeviceName = _T("");
	m_dwDeviceNum = 0;
	m_dwDeviceState = 0;
	m_dwDirectionNO = 0;
	m_csDeviceID = _T("");
	m_dwLaneID = 0;
	m_csMonitorID = _T("");
	m_csMonitorInfo = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
    m_byRelateChan = 0;
}


void CDlgITSRoadInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSRoadInfo)
	DDX_Control(pDX, IDC_COMBO_TRIGGER_MODE, m_comboTriggerMode);
	DDX_Control(pDX, IDC_COMBO_DEVICETYPE, m_comboDeviceType);
	DDX_Control(pDX, IDC_COMBO_DEVICE_NO, m_comboDeviceNO);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_dwChannel);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_csDeviceName);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NUM, m_dwDeviceNum);
	DDX_Text(pDX, IDC_EDIT_DEVICE_STATE, m_dwDeviceState);
	DDX_Text(pDX, IDC_EDIT_DIRECTION_NO, m_dwDirectionNO);
	DDX_Text(pDX, IDC_EDIT_ITS_DEVICE_ID, m_csDeviceID);
	DDX_Text(pDX, IDC_EDIT_LANE_ID, m_dwLaneID);
	DDX_Text(pDX, IDC_EDIT_MONITOR_ID, m_csMonitorID);
	DDX_Text(pDX, IDC_EDIT_MONITOR_INFO, m_csMonitorInfo);
    DDX_Text(pDX, IDC_EDIT_RELATE_CHAN, m_byRelateChan);
 
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSRoadInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgITSRoadInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_NO, OnSelchangeComboDeviceNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSRoadInfo message handlers
BOOL CDlgITSRoadInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	char szLan[128] = {0};
	for (int i=0; i<32; i++)
	{
		sprintf(szLan, "%d", i+1);
		m_comboDeviceNO.InsertString(i,szLan);
	}
	m_comboDeviceNO.SetCurSel(0);
	return TRUE;
}

void CDlgITSRoadInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struRoadInfo, 0, sizeof(m_struRoadInfo));
	DWORD dwReturn = 0;
	char csTemp[49] = {0};
	if (NET_DVR_GetDVRConfig(m_lServerID, NET_ITS_GET_ROAD_INFO, m_dwChannel, &m_struRoadInfo,
		sizeof(m_struRoadInfo), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_GET_ROAD_INFO");
	}
	else
	{
		int iErr = NET_DVR_GetLastError();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_GET_ROAD_INFO");
	}

//	m_dwChannel = m_struRoadInfo.dwChannel;
	m_comboTriggerMode.SetCurSel(m_struRoadInfo.byTriggerMode);
	m_dwDeviceNum = m_struRoadInfo.dwDeviceNum;
	memcpy(csTemp, m_struRoadInfo.byMonitoringSiteID, 48);
	m_csMonitorID.Format(csTemp);
	memset(csTemp, 0, 49);
	memcpy(csTemp, m_struRoadInfo.byRoadInfo, 48);
	m_csMonitorInfo.Format(csTemp);

	m_comboDeviceNO.SetCurSel(0);
	m_comboDeviceType.SetCurSel(m_struRoadInfo.struSingleDevice[0].dwDeviceType);
	m_dwDirectionNO = m_struRoadInfo.struSingleDevice[0].dwDirID;
    m_dwLaneID = m_struRoadInfo.struSingleDevice[0].dwLaneID;
	m_dwDeviceState = m_struRoadInfo.struSingleDevice[0].dwDeviceState;
    m_byRelateChan = m_struRoadInfo.struSingleDevice[0].byRelateChan;
	memset(csTemp, 0, 49);
	memcpy(csTemp, m_struRoadInfo.struSingleDevice[0].byDeviceName,32);
	m_csDeviceName.Format(csTemp);
	memset(csTemp, 0, 49);
	memcpy(csTemp, m_struRoadInfo.struSingleDevice[0].byDeviceID, 48);
	m_csDeviceID.Format(csTemp);
	UpdateData(FALSE);
}

void CDlgITSRoadInfo::OnSelchangeComboDeviceNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char csTemp[49] = {0};
	int iSel = m_comboDeviceNO.GetCurSel();
	m_comboDeviceNO.SetCurSel(0);
	m_comboDeviceType.SetCurSel(m_struRoadInfo.struSingleDevice[iSel].dwDeviceType);
	m_dwDirectionNO = m_struRoadInfo.struSingleDevice[iSel].dwDirID;
    m_dwLaneID = m_struRoadInfo.struSingleDevice[iSel].dwLaneID;
	m_dwDeviceState = m_struRoadInfo.struSingleDevice[iSel].dwDeviceState;
    m_byRelateChan = m_struRoadInfo.struSingleDevice[iSel].byRelateChan;
	memset(csTemp, 0, 49);
	memcpy(csTemp, m_struRoadInfo.struSingleDevice[iSel].byDeviceName,32);
	m_csDeviceName.Format(csTemp);
	memset(csTemp, 0, 49);
	memcpy(csTemp, m_struRoadInfo.struSingleDevice[iSel].byDeviceID, 48);
	m_csDeviceID.Format(csTemp);
	UpdateData(FALSE);
}
