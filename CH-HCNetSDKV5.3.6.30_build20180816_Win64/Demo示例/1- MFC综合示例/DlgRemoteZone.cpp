/**********************************************************
FileName:    DlgRemoteZone.cpp
Description: setup the zone and dst configure      
Date:        2008/11/19
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/11/19>       <created>
***********************************************************/

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteZone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteZone dialog

/*********************************************************
  Function:	CDlgRemoteZone
  Desc:		Constructor
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
CDlgRemoteZone::CDlgRemoteZone(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteZone::IDD, pParent)
	, m_iDeviceIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgRemoteZone)
	//}}AFX_DATA_INIT
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteZone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteZone)
	DDX_Control(pDX, IDC_COMBO_ZONEINDEX, m_comboZone);
	DDX_Control(pDX, IDC_COMBO_WEEKNO2, m_comboWeekNo2);
	DDX_Control(pDX, IDC_COMBO_WEEKNO, m_comboWeekNo);
	DDX_Control(pDX, IDC_COMBO_WEEKDATE2, m_comboWeekDate2);
	DDX_Control(pDX, IDC_COMBO_WEEKDATE, m_comboWeekDate);
	DDX_Control(pDX, IDC_COMBO_MONTH, m_comboMonth);
	DDX_Control(pDX, IDC_COMBO_MONTH2, m_comboMonth2);
	DDX_Control(pDX, IDC_COMBO_MINUTE2, m_comboMinute2);
	DDX_Control(pDX, IDC_COMBO_MINUTE, m_comboMinute);
	DDX_Control(pDX, IDC_COMBO_HOUR2, m_comboHour2);
	DDX_Control(pDX, IDC_COMBO_HOUR, m_comboHour);
	DDX_Control(pDX, IDC_COMBO_ENABLEDST, m_comboEnableDst);
	DDX_Control(pDX, IDC_COMBO_DSTOFFSET, m_comboDstOffSet);
	//}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteZone, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteZone)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteZone message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteZone::OnInitDialog() 
{
	CDialog::OnInitDialog();
	DWORD dwReturned = 0;
	char szLan[128] = {0};
	memset(&m_struZoneAndDst, 0, sizeof(NET_DVR_ZONEANDDST));
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_ZONEANDDST, 0, &m_struZoneAndDst, sizeof(NET_DVR_ZONEANDDST), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ZONEANDDST");
		GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
		g_StringLanType(szLan, "获取时区和夏令时配置失败!", "get time zone and daylight time configuration");
		AfxMessageBox(szLan);
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ZONEANDDST");
		m_comboEnableDst.SetCurSel(m_struZoneAndDst.dwEnableDST);
		m_comboDstOffSet.SetCurSel(m_struZoneAndDst.byDSTBias/30-1);
		m_comboMonth.SetCurSel(m_struZoneAndDst.struBeginPoint.dwMonth);		
		m_comboWeekNo.SetCurSel(m_struZoneAndDst.struBeginPoint.dwWeekNo);
		m_comboWeekDate.SetCurSel(m_struZoneAndDst.struBeginPoint.dwWeekDate);
		m_comboHour.SetCurSel(m_struZoneAndDst.struBeginPoint.dwHour);
		m_comboMinute.SetCurSel(m_struZoneAndDst.struBeginPoint.dwMin);

		m_comboMonth2.SetCurSel(m_struZoneAndDst.struEndPoint.dwMonth);		
		m_comboWeekNo2.SetCurSel(m_struZoneAndDst.struEndPoint.dwWeekNo);
		m_comboWeekDate2.SetCurSel(m_struZoneAndDst.struEndPoint.dwWeekDate);
		m_comboHour2.SetCurSel(m_struZoneAndDst.struEndPoint.dwHour);
		m_comboMinute2.SetCurSel(m_struZoneAndDst.struEndPoint.dwMin);
	}

	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteZone::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnBtnSet
  Desc:		setup the zone and dst configure
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteZone::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struZoneAndDst.dwEnableDST=m_comboEnableDst.GetCurSel();
	m_struZoneAndDst.byDSTBias = (BYTE)((m_comboDstOffSet.GetCurSel()+1)*30);
	m_struZoneAndDst.struBeginPoint.dwMonth=m_comboMonth.GetCurSel();		
	m_struZoneAndDst.struBeginPoint.dwWeekNo=m_comboWeekNo.GetCurSel();
	m_struZoneAndDst.struBeginPoint.dwWeekDate=m_comboWeekDate.GetCurSel();
	m_struZoneAndDst.struBeginPoint.dwHour=m_comboHour.GetCurSel();
	m_struZoneAndDst.struBeginPoint.dwMin=m_comboMinute.GetCurSel();

	m_struZoneAndDst.struEndPoint.dwMonth=m_comboMonth2.GetCurSel();		
	m_struZoneAndDst.struEndPoint.dwWeekNo=m_comboWeekNo2.GetCurSel();
	m_struZoneAndDst.struEndPoint.dwWeekDate=m_comboWeekDate2.GetCurSel();
	m_struZoneAndDst.struEndPoint.dwHour=m_comboHour2.GetCurSel();
	m_struZoneAndDst.struEndPoint.dwMin=m_comboMinute2.GetCurSel();
	char szLan[128] = {0};	
	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_ZONEANDDST, 0, &m_struZoneAndDst, sizeof(NET_DVR_ZONEANDDST)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ZONEANDDST");
		g_StringLanType(szLan, "设置时区和夏令时配置失败!", "set time zone and daylight time configuration failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ZONEANDDST");
		g_StringLanType(szLan, "设置时区和夏令时配置成功!", "set time zone and daylight time configuration successfully");
		AfxMessageBox(szLan);
	}
}
