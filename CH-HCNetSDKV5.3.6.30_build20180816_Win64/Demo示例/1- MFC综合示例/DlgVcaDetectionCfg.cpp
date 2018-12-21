// DlgVcaDetectionCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaDetectionCfg.h"
#include "DlgRemoteAlarmInHandle.h"
#include "DlgRemoteAlarmInPtzInvoke.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDetectionCfg dialog


CDlgVcaDetectionCfg::CDlgVcaDetectionCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaDetectionCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaDetectionCfg)
	m_bEnable = FALSE;
    m_lUserID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
    m_pStruDetectionCfg = NULL;
    m_pStruAlarmInCfgV40 = NULL;
    //}}AFX_DATA_INIT
}

/*********************************************************
  Function:	~CDlgVcaDetectionCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgVcaDetectionCfg::~CDlgVcaDetectionCfg()
{
    if(m_pStruDetectionCfg != NULL)
    {
        delete m_pStruDetectionCfg;
        m_pStruDetectionCfg = NULL;
    }

	if (m_pStruAlarmInCfgV40 != NULL)
    {
        delete m_pStruAlarmInCfgV40;
        m_pStruAlarmInCfgV40 = NULL;
    }
}


void CDlgVcaDetectionCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaDetectionCfg)
	DDX_Control(pDX, IDC_CMB_CHANNEL, m_cmbChannel);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaDetectionCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaDetectionCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_LINKAGE, OnBtnLinkage)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_PTZ, OnBtnPtz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDetectionCfg message handlers

void CDlgVcaDetectionCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    if (m_lChannel < 0)
    {
        return;
    }
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_VCA_DETION_CFG_V40,m_lChannel,m_pStruDetectionCfg,sizeof(*m_pStruDetectionCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_DETION_CFG_V40");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_DETION_CFG_V40");
    }
    m_bEnable = m_pStruDetectionCfg->byEnable;


    UpdateData(false);
}

BOOL CDlgVcaDetectionCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    if (m_pStruDetectionCfg == NULL)
    {
        m_pStruDetectionCfg = new NET_DVR_VCA_DETECTION_CFG_V40;
    }

    if (m_pStruDetectionCfg != NULL)
    {
        memset(m_pStruDetectionCfg,0,sizeof(NET_DVR_VCA_DETECTION_CFG_V40));
    }

    if (m_pStruAlarmInCfgV40 == NULL)
    {
        m_pStruAlarmInCfgV40 = new NET_DVR_ALARMINCFG_V40;
    }
    memset(m_pStruAlarmInCfgV40,0, sizeof(NET_DVR_ALARMINCFG_V40));

    AddChanInfo();
	// TODO: Add extra initialization here
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaDetectionCfg::AddChanInfo()
{
    m_cmbChannel.ResetContent();
    char szLan[128] = {0};
    CString csStr;
    int iIndex = 0;
    int i;
//     for(i=0; i< (g_struDeviceInfo[m_iDevIndex].iDeviceChanNum - g_struDeviceInfo[m_iDevIndex].iIPChanNum) ; i++)
//     {
//         csStr.Format("%s %d", "Camera", g_struDeviceInfo[m_iDevIndex].iStartChan + i);
//         m_cmbChannel.AddString(csStr);
//         m_cmbChannel.SetItemData(iIndex++, g_struDeviceInfo[m_iDevIndex].iStartChan + i);
//     }
//     
//     for(i=0; i<g_struDeviceInfo[m_iDevIndex].iIPChanNum; i++)
//     {
//         if (g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40[0].struIPDevInfo[i].byEnable)
//         {
//             g_StringLanType(szLan, "IPCamera", "IPChannel");
//             csStr.Format("%s %d", szLan, 1 + i);
//             m_cmbChannel.AddString(csStr);
//             m_cmbChannel.SetItemData(iIndex++, g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40[0].dwStartDChan + i);
//         }
//         
//     }
    
     for(i=0; i< g_struDeviceInfo[m_iDevIndex].iDeviceChanNum ; i++)
     {
             m_cmbChannel.AddString(g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].chChanName);
             m_cmbChannel.SetItemData(iIndex++, g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO);
      }
    m_cmbChannel.SetCurSel(0);
}

void CDlgVcaDetectionCfg::OnBtnLinkage() 
{
	// TODO: Add your control notification handler code here
    CDlgRemoteAlarmInHandle dlg;
    LOCAL_ALARMIN_HANDLE struLocalAlarmHandle = {0};
    int i = 0;
    struLocalAlarmHandle.struAlarmHandleType.dwHandleType = m_pStruDetectionCfg->dwHandleType;
    struLocalAlarmHandle.struAlarmHandleType.dwMaxRelAlarmOutChanNum = m_pStruDetectionCfg->dwMaxRelAlarmOutChanNum;
    memcpy(struLocalAlarmHandle.struAlarmHandleType.dwRelAlarmOut,m_pStruDetectionCfg->dwRelAlarmOut, sizeof(DWORD)*MAX_ALARMOUT_V40);
    
    memcpy(struLocalAlarmHandle.struAlarmTime,m_pStruDetectionCfg->struAlarmSched, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
    memcpy(struLocalAlarmHandle.dwRelRecordChan, m_pStruDetectionCfg->dwRelRecordChan, sizeof(DWORD)*MAX_CHANNUM_V40);
    
      dlg.m_lpAlarmInV40 = &struLocalAlarmHandle;
    
    dlg.m_iChanCount = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    dlg.m_iAnaChanCount = g_struDeviceInfo[m_iDevIndex].iAnalogChanNum;
    
    if (g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40 != NULL)
    {
        dlg.m_iDStartChannel = g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan;
     }
     else
     {
         dlg.m_iDStartChannel = 33;
     }

     dlg.m_lStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;
     if (g_struDeviceInfo[m_iDevIndex].pStruIPAlarmOutCfgV40 != NULL)
     {
         dlg.m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum + g_struDeviceInfo[m_iDevIndex].pStruIPAlarmOutCfgV40->dwCurIPAlarmOutNum;
     }
     else
     {
         dlg.m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;
     }
 
//     dlg.m_dwAlarmInNum = m_dwAlarmInNum;
//     dlg.m_lAlarmInIndex = m_iAlarmInIndex;
    dlg.m_dwDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lUserID;
    dlg.m_bSetHolidayCfg = FALSE;

    memcpy(&(dlg.m_struHolidayHandle.struAlarmTime), m_pStruDetectionCfg->struHolidayTime, sizeof(m_pStruDetectionCfg->struHolidayTime));
  
   // memcpy()
    if (dlg.DoModal()==IDOK)
    {
        m_pStruDetectionCfg->dwHandleType = struLocalAlarmHandle.struAlarmHandleType.dwHandleType;
        memcpy(m_pStruDetectionCfg->dwRelAlarmOut, struLocalAlarmHandle.struAlarmHandleType.dwRelAlarmOut, sizeof(DWORD)*MAX_ALARMOUT_V40);
        memcpy(m_pStruDetectionCfg->struAlarmSched, struLocalAlarmHandle.struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
        memcpy(m_pStruDetectionCfg->dwRelRecordChan, struLocalAlarmHandle.dwRelRecordChan,  sizeof(DWORD)*MAX_CHANNUM_V40);
        memcpy(m_pStruDetectionCfg->struHolidayTime, &(dlg.m_struHolidayHandle.struAlarmTime),sizeof(m_pStruDetectionCfg->struHolidayTime));
	}       
}

void CDlgVcaDetectionCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    
    if (m_lChannel < 0)
    {
        return;
    }
    DWORD dwReturn = 0;
    m_pStruDetectionCfg->byEnable = m_bEnable;
    if (!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_VCA_DETION_CFG_V40,m_lChannel,m_pStruDetectionCfg,sizeof(*m_pStruDetectionCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_DETION_CFG_V40");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_DETION_CFG_V40");
    }
    
    UpdateData(false);
}

void CDlgVcaDetectionCfg::OnBtnPtz() 
{
    // TODO: Add your control notification handler code here
    CDlgRemoteAlarmInPtzInvoke dlg;
    dlg.m_lpAlarmInV40 = m_pStruAlarmInCfgV40;
    //Get PTZ Info
    GetPTZInfo();
    dlg.m_iChanCount = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    dlg.m_iAnalogChanNum = g_struDeviceInfo[m_iDevIndex].iAnalogChanNum;
    dlg.m_lStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;
    if (g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40 != NULL)
    {
        dlg.m_iDStartChannel = g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan;
    }
    else
    {
        dlg.m_iDStartChannel = 33;
    }
    
    dlg.m_iDeviceIndex = m_iDevIndex;

    if (dlg.DoModal()==IDOK)
    {
        
    }
    //Updata PTZ Info
    UpdataPTZInfo();
    
   
}

void CDlgVcaDetectionCfg::GetPTZInfo()
{
    m_pStruAlarmInCfgV40->dwEnablePresetChanNum = m_pStruDetectionCfg->dwEnablePresetChanNum;
    memcpy(m_pStruAlarmInCfgV40->struPresetChanInfo, m_pStruDetectionCfg->struPresetChanInfo, sizeof(NET_DVR_PRESETCHAN_INFO)*MAX_CHANNUM_V40);

    m_pStruAlarmInCfgV40->dwEnableCruiseChanNum = m_pStruDetectionCfg->dwEnableCruiseChanNum;
    memcpy(m_pStruAlarmInCfgV40->struCruiseChanInfo, m_pStruDetectionCfg->struCruiseChanInfo, sizeof(NET_DVR_CRUISECHAN_INFO)*MAX_CHANNUM_V40);


    m_pStruAlarmInCfgV40->dwEnablePtzTrackChanNum = m_pStruDetectionCfg->dwEnablePtzTrackChanNum;
    memcpy(m_pStruAlarmInCfgV40->struPtzTrackInfo, m_pStruDetectionCfg->struPtzTrackInfo, sizeof(NET_DVR_PTZTRACKCHAN_INFO)*MAX_CHANNUM_V40);

}
void CDlgVcaDetectionCfg::UpdataPTZInfo()
{
    m_pStruDetectionCfg->dwEnablePresetChanNum = m_pStruAlarmInCfgV40->dwEnablePresetChanNum;
    memcpy(m_pStruDetectionCfg->struPresetChanInfo, m_pStruAlarmInCfgV40->struPresetChanInfo, sizeof(NET_DVR_PRESETCHAN_INFO)*MAX_CHANNUM_V40);
    
    m_pStruDetectionCfg->dwEnableCruiseChanNum = m_pStruAlarmInCfgV40->dwEnableCruiseChanNum;
    memcpy( m_pStruDetectionCfg->struCruiseChanInfo, m_pStruAlarmInCfgV40->struCruiseChanInfo,sizeof(NET_DVR_CRUISECHAN_INFO)*MAX_CHANNUM_V40);
    
    
    m_pStruDetectionCfg->dwEnablePtzTrackChanNum = m_pStruAlarmInCfgV40->dwEnablePtzTrackChanNum;
    memcpy(m_pStruDetectionCfg->struPtzTrackInfo, m_pStruAlarmInCfgV40->struPtzTrackInfo, sizeof(NET_DVR_PTZTRACKCHAN_INFO)*MAX_CHANNUM_V40);
}