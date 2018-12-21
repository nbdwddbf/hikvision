/**********************************************************
FileName:    DlgRemoteAlarmInPtzInvoke.cpp
Description: PTZ movement on alarm     
Date:        2008/05/17
Note: 		<glocal structure> refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteAlarmInPtzInvoke.h"
#include ".\dlgremotealarminptzinvoke.h"


// CDlgRemoteAlarmInPtzInvoke dialog
/*********************************************************
  Function:	CDlgRemoteAlarmInPtzInvoke
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteAlarmInPtzInvoke, CDialog)
CDlgRemoteAlarmInPtzInvoke::CDlgRemoteAlarmInPtzInvoke(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteAlarmInPtzInvoke::IDD, pParent)
	, m_iPresetNo(1)
	, m_iCruiseNo(1)
	, m_iTrackNo(1)
	, m_bPreset(FALSE)
	, m_bCruise(FALSE)
	, m_bTrack(FALSE)
	, m_lpAlarmInV40(NULL)
	, m_nChannel(0)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_iAnalogChanNum(0)
	, m_iDStartChannel(0)
    , m_iPresetDurationTime(0)
{
}

/*********************************************************
  Function:	~CDlgRemoteAlarmInPtzInvoke
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteAlarmInPtzInvoke::~CDlgRemoteAlarmInPtzInvoke()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteAlarmInPtzInvoke)
	DDX_Control(pDX, IDC_COMBO_PTZ_LINKAGE_CHAN, m_comboChan);
	DDX_Text(pDX, IDC_EDIT_PRESET_NO, m_iPresetNo);
	DDX_Text(pDX, IDC_EDIT_TRACK_NO, m_iTrackNo);
	DDX_Text(pDX, IDC_EDIT_CRUISE_NO, m_iCruiseNo);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_PRESET_DURATION_TIME, m_iPresetDurationTime);
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteAlarmInPtzInvoke, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteAlarmInPtzInvoke)	
	ON_BN_CLICKED(ID_BTN_PTZ_OK, OnBnClickedBtnPtzOk)
	ON_BN_CLICKED(ID_BTN_PTZ_EXIT, OnBnClickedBtnPtzExit)
	ON_CBN_SELCHANGE(IDC_COMBO_PTZ_LINKAGE_CHAN, OnCbnSelchangeComboPtzLinkage)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CRUISE, OnDeltaposSpinCruise)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PRESET, OnDeltaposSpinPreset)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRACK, OnDeltaposSpinTrack)
	ON_BN_CLICKED(IDC_RADIO_CRUISE, OnRadioCruise)
	ON_BN_CLICKED(IDC_RADIO_PRESET, OnRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_TRACK, OnRadioTrack)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgRemoteAlarmInPtzInvoke message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteAlarmInPtzInvoke::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CString sTemp;
	char szLan[128] = {0};
	int iChanShow = 0;
	int iCopyIndex = 0;
	int i =0;
    m_comboChan.ResetContent();
	
	for (i=0; i<MAX_CHANNUM_V40; i++)//PTZ parameter settings only valid for analog channels
	{
		iChanShow = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO;
		if (i<m_iAnalogChanNum && g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
		{
			sTemp.Format(ANALOG_C_FORMAT, iChanShow);
			m_comboChan.AddString(sTemp);
			m_comboChan.SetItemData(iCopyIndex, iChanShow);	
			iCopyIndex++;
		}
		else if(i >= m_iAnalogChanNum && g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
		{

			sTemp.Format(DIGITAL_C_FORMAT, iChanShow - m_iDStartChannel + 1);
			m_comboChan.AddString(sTemp);
			m_comboChan.SetItemData(iCopyIndex, iChanShow);	
			iCopyIndex++;
		}
	}

	m_comboChan.SetCurSel(0);
	m_nChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
    int iStartNum = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
 m_bPreset = FALSE;
    for (i = 0; i < m_lpAlarmInV40->dwEnablePresetChanNum; i++)
    {
        if ((m_nChannel) == m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan)
        {
            m_bPreset = TRUE;
            m_iPresetNo = m_lpAlarmInV40->struPresetChanInfo[i].dwPresetPointNo;
            m_iPresetDurationTime = m_lpAlarmInV40->byPresetDurationTime[i];
            break;
        }
		else if (INVALID_VALUE_UINT32 == m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan)
        {
			break;
		}      
    }
	
    m_bCruise = FALSE;
    for (i = 0; i < m_lpAlarmInV40->dwEnableCruiseChanNum; i++)
    {
        if ((m_nChannel) == m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan)
        {
            m_bCruise = TRUE;
            m_iCruiseNo = m_lpAlarmInV40->struCruiseChanInfo[i].dwCruiseNo;
            break;
        }
        else if (INVALID_VALUE_UINT32 ==  m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan)
        {
            break;
        }
        
    }
	
	m_bTrack = FALSE;
    for ( i = 0; i < m_lpAlarmInV40->dwEnablePtzTrackChanNum; i++)
    {
        if ((m_nChannel) == m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan)
        {
            m_bTrack = TRUE;
            m_iCruiseNo = m_lpAlarmInV40->struPtzTrackInfo[i].dwPtzTrackNo;
            break;
        }
        else if (INVALID_VALUE_UINT32== m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan)
        {
            break;
        }
		
    }
	((CButton *)GetDlgItem(IDC_RADIO_PRESET))->SetCheck(m_bPreset);
	((CButton *)GetDlgItem(IDC_RADIO_CRUISE))->SetCheck(m_bCruise);
	((CButton *)GetDlgItem(IDC_RADIO_TRACK))->SetCheck(m_bTrack);
	EnableCtrl();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}

/*********************************************************
  Function:	OnBnClickedBtnPtzOk
  Desc:		Set external PTZ movements on alarm in
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::OnBnClickedBtnPtzOk()
{
	UpdateData(TRUE);
 SaveLastInfoToCfg();
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnPtzExit
  Desc:		Cancel external PTZ movements on alarm in
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::OnBnClickedBtnPtzExit()
{
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnCbnSelchangeComboPtzLinkage
  Desc:		Display external PTZ movements on alarm in
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::OnCbnSelchangeComboPtzLinkage()
{
	UpdateData(TRUE);
	int iStartNum = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
	int i = 0;
    m_nChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
    //Preset
    m_bPreset = FALSE;
    m_bCruise = FALSE;
    m_bTrack = FALSE;
	
    for (i =0 ; i < m_lpAlarmInV40->dwEnablePresetChanNum; i++)
    {
        if (m_nChannel == m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan)
        {
            m_bPreset = TRUE;
            m_iPresetNo = m_lpAlarmInV40->struPresetChanInfo[i].dwPresetPointNo;
            m_iPresetDurationTime = m_lpAlarmInV40->byPresetDurationTime[i];
            break;
        }
        else if (INVALID_VALUE_UINT32 == m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan)
        {
            break;
        }
    }
	
    //curise
	
    for (i =0 ; i < m_lpAlarmInV40->dwEnableCruiseChanNum; i++)
    {
        if (m_nChannel == m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan)
        {
            m_bCruise = TRUE;
            m_iCruiseNo = m_lpAlarmInV40->struCruiseChanInfo[i].dwCruiseNo;
            break;
        }
        else if (INVALID_VALUE_UINT32 == m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan)
        {
            break;
        }
		
    }
	
    //ptz
    
    for (i =0 ; i < m_lpAlarmInV40->dwEnablePtzTrackChanNum; i++)
    {
        if (m_nChannel  == m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan)
        {
            m_bTrack = TRUE;
            m_iTrackNo = m_lpAlarmInV40->struPtzTrackInfo[i].dwPtzTrackNo;
            break;
        }
        else if (INVALID_VALUE_UINT32 == m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan)
        {
            break;
        }
        
    }
	((CButton *)GetDlgItem(IDC_RADIO_PRESET))->SetCheck(m_bPreset);
	((CButton *)GetDlgItem(IDC_RADIO_CRUISE))->SetCheck(m_bCruise);
	((CButton *)GetDlgItem(IDC_RADIO_TRACK))->SetCheck(m_bTrack);
    EnableCtrl();

	UpdateData(FALSE);
}

void CDlgRemoteAlarmInPtzInvoke::OnDeltaposSpinCruise(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta < 0)
	{
		if (m_iCruiseNo < MAX_CRUISE_V30)//MAX_CRUISE_V30
		{
			m_iCruiseNo += 1;
		}
		else
		{
			m_iCruiseNo = 1;
		}
	}
	else
	{
		if (m_iCruiseNo > 1)
		{
			m_iCruiseNo -= 1;
		}	
		else
		{
			m_iCruiseNo = MAX_CRUISE_V30;//
		}
	}

	UpdateData(FALSE);
		
	*pResult = 0;
}

void CDlgRemoteAlarmInPtzInvoke::OnDeltaposSpinPreset(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta < 0)
	{
		if (m_iPresetNo < MAX_PRESET_V30)//MAX_CRUISE_V30
		{
			m_iPresetNo += 1;
		}
		else
		{
			m_iPresetNo = 1;
		}
	}
	else
	{
		if (m_iPresetNo > 1)
		{
			m_iPresetNo -= 1;
		}	
		else
		{
			m_iPresetNo = MAX_PRESET_V30;//
		}
	}

	UpdateData(FALSE);	
	*pResult = 0;
}

void CDlgRemoteAlarmInPtzInvoke::OnDeltaposSpinTrack(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMUpDown->iDelta < 0)
	{
		if (m_iTrackNo < MAX_TRACK_V30)//MAX_CRUISE_V30
		{
			m_iTrackNo += 1;
		}
		else
		{
			m_iTrackNo = 1;
		}
	}
	else
	{
		if (m_iTrackNo > 1)
		{
			m_iTrackNo -= 1;
		}	
		else
		{
			m_iTrackNo = MAX_TRACK_V30;//
		}
	}

	UpdateData(FALSE);	
	*pResult = 0;
}

void CDlgRemoteAlarmInPtzInvoke::OnRadioPreset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bPreset = TRUE;
	m_bCruise = FALSE;
	m_bTrack = FALSE;
	EnableCtrl();
	UpdateData(FALSE);
}

void CDlgRemoteAlarmInPtzInvoke::OnRadioCruise() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bPreset = FALSE;
	m_bCruise = TRUE;
	m_bTrack = FALSE;
	EnableCtrl();
	UpdateData(FALSE);	
}


void CDlgRemoteAlarmInPtzInvoke::OnRadioTrack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_bPreset = FALSE;
	m_bCruise = FALSE;
	m_bTrack = TRUE;
	EnableCtrl();
	UpdateData(FALSE);	
}

void CDlgRemoteAlarmInPtzInvoke::EnableCtrl()
{
	GetDlgItem(IDC_EDIT_PRESET_NO)->EnableWindow(m_bPreset);
	GetDlgItem(IDC_EDIT_CRUISE_NO)->EnableWindow(m_bCruise);
	GetDlgItem(IDC_EDIT_TRACK_NO)->EnableWindow(m_bTrack);
	GetDlgItem(IDC_SPIN_PRESET)->EnableWindow(m_bPreset);
	GetDlgItem(IDC_SPIN_CRUISE)->EnableWindow(m_bCruise);
	GetDlgItem(IDC_SPIN_TRACK)->EnableWindow(m_bTrack);
}

/*********************************************************
  Function:	FindDataInPresetInfo
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::FindDataInPresetInfo(DWORD dwFindData)
{
    int i = 0;
    BOOL bFindData = FALSE;
    int iCurIndex = 0;
    
    bFindData = FALSE;
    for ( i = 0; i < m_lpAlarmInV40->dwEnablePresetChanNum; i++)
    {
        if (m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan == dwFindData)
        {
            bFindData = TRUE;
            break;
        }
    }
    
    if (bFindData)
    {
        iCurIndex = m_lpAlarmInV40->dwEnablePresetChanNum;
        for (i ; i< iCurIndex; i++)
        {
            if ( (i+1) != MAX_CHANNUM_V40)
            {
                m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan = m_lpAlarmInV40->struPresetChanInfo[i+1].dwEnablePresetChan;
                m_lpAlarmInV40->struPresetChanInfo[i].dwPresetPointNo = m_lpAlarmInV40->struPresetChanInfo[i+1].dwPresetPointNo;
                m_lpAlarmInV40->byPresetDurationTime[i] = m_lpAlarmInV40->byPresetDurationTime[i + 1];
            }
            else
            {
                m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->struPresetChanInfo[i].dwPresetPointNo = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->byPresetDurationTime[i] = 0;
                break;
            } 
            
            if (i == iCurIndex -1)
            {
                m_lpAlarmInV40->struPresetChanInfo[i+1].dwEnablePresetChan = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->struPresetChanInfo[i+1].dwPresetPointNo = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->byPresetDurationTime[i + 1] = 0;
                m_lpAlarmInV40->dwEnablePresetChanNum--;
            }
        }
    }
}

/*********************************************************
  Function:	FindDataInCruiseInfo
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::FindDataInCruiseInfo(DWORD dwFindData)
{
    int i = 0;
    BOOL bFindData = FALSE;
    int iCurIndex = 0;
    
    for ( i = 0; i < m_lpAlarmInV40->dwEnableCruiseChanNum; i++)
    {
        if (m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan == dwFindData)
        {
            bFindData = TRUE;
            break;
        }
    }
    
    if (bFindData)
    {
        iCurIndex = m_lpAlarmInV40->dwEnableCruiseChanNum;
        for (i ; i< iCurIndex; i++)
        {
            if ( (i+1) != MAX_CHANNUM_V40)
            {
                m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan = m_lpAlarmInV40->struCruiseChanInfo[i+1].dwEnableCruiseChan;
                m_lpAlarmInV40->struCruiseChanInfo[i].dwCruiseNo = m_lpAlarmInV40->struCruiseChanInfo[i+1].dwCruiseNo;
            }
            else
            {
                m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->struCruiseChanInfo[i].dwCruiseNo = INVALID_VALUE_UINT32;
                break;
            } 
            
            if (i == iCurIndex -1)
            {
                m_lpAlarmInV40->struCruiseChanInfo[i+1].dwEnableCruiseChan = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->struCruiseChanInfo[i+1].dwCruiseNo = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->dwEnableCruiseChanNum--;
            }
        }
    }
}



/*********************************************************
  Function:	FindDataInPtzInfo
  Desc:		Find Find In NET_DVR_PTZTRACKCHAN_INFO
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::FindDataInPtzInfo(DWORD dwFindData)
{
    int i = 0;
    BOOL bFindData = FALSE;
    int iCurIndex = 0;
    
    bFindData = FALSE;
    for ( i = 0; i < m_lpAlarmInV40->dwEnablePtzTrackChanNum; i++)
    {
        if (m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan == dwFindData)
        {
            bFindData = TRUE;
            break;
        }
    }
    
    if (bFindData)
    {
        iCurIndex = m_lpAlarmInV40->dwEnablePtzTrackChanNum;
        for (i ; i< iCurIndex; i++)
        {
            if ( (i+1) != MAX_CHANNUM_V40)
            {
                m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan = m_lpAlarmInV40->struPtzTrackInfo[i+1].dwEnablePtzTrackChan;
                m_lpAlarmInV40->struPtzTrackInfo[i].dwPtzTrackNo = m_lpAlarmInV40->struPtzTrackInfo[i+1].dwPtzTrackNo;
            }
            else
            {
                m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->struPtzTrackInfo[i].dwPtzTrackNo = INVALID_VALUE_UINT32;
                break;
            } 
            
            if (i == iCurIndex -1)
            {
                m_lpAlarmInV40->struPtzTrackInfo[i+1].dwEnablePtzTrackChan = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->struPtzTrackInfo[i+1].dwPtzTrackNo = INVALID_VALUE_UINT32;
                m_lpAlarmInV40->dwEnablePtzTrackChanNum--;
            }
        }
    }
}

void CDlgRemoteAlarmInPtzInvoke::SaveLastInfoToCfg()
{
    UpdateData(TRUE);
    m_nChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
    /*	m_lpAlarmInV40->byChannel = m_nChannel - iStartNum  ;*/
    BOOL bFindData = FALSE;
    int iCurIndex = 0;
    int i = 0;
    if (m_bPreset)
    {
        bFindData = FALSE;
        for (i = 0; i < m_lpAlarmInV40->dwEnablePresetChanNum; i++)
        {
            if ( m_lpAlarmInV40->struPresetChanInfo[i].dwEnablePresetChan == m_nChannel)
            {
                m_lpAlarmInV40->struPresetChanInfo[i].dwPresetPointNo = (DWORD)m_iPresetNo;
                m_lpAlarmInV40->byPresetDurationTime[i] = (BYTE)m_iPresetDurationTime;
                bFindData = TRUE;
                break;
            }
        }
        
        //Not found, add directly behind
        if (!bFindData)
        {
            m_lpAlarmInV40->struPresetChanInfo[m_lpAlarmInV40->dwEnablePresetChanNum].dwEnablePresetChan =m_nChannel ;
            m_lpAlarmInV40->struPresetChanInfo[m_lpAlarmInV40->dwEnablePresetChanNum].dwPresetPointNo = (DWORD)m_iPresetNo;
            m_lpAlarmInV40->byPresetDurationTime[m_lpAlarmInV40->dwEnablePresetChanNum++] = (BYTE)m_iPresetDurationTime;
        }
        
        
        //find Cruise Info has this channel Info
        FindDataInCruiseInfo(m_nChannel );  
        //find PTZ Info has this channel Info
        FindDataInPtzInfo(m_nChannel);
    }
    
    if (m_bCruise)
    {
        bFindData = FALSE;
        
        for ( i = 0; i < m_lpAlarmInV40->dwEnableCruiseChanNum; i++)
        {
            if (m_lpAlarmInV40->struCruiseChanInfo[i].dwEnableCruiseChan == m_nChannel)
            {
                m_lpAlarmInV40->struCruiseChanInfo[i].dwCruiseNo = (DWORD)m_iCruiseNo;
                bFindData = TRUE;
                break;
            }
        }
        
        //Not found, add directly behind
        if (!bFindData)
        {
            m_lpAlarmInV40->struCruiseChanInfo[m_lpAlarmInV40->dwEnableCruiseChanNum].dwEnableCruiseChan = m_nChannel ;
            m_lpAlarmInV40->struCruiseChanInfo[m_lpAlarmInV40->dwEnableCruiseChanNum++].dwCruiseNo = (DWORD)m_iCruiseNo;
        }
        
        
        //find Preset Info has this channel Info
        FindDataInPresetInfo(m_nChannel );
        
        //find Ptz Info has this channel Info
        FindDataInPtzInfo(m_nChannel);
        
    }
    
    
    if(m_bTrack)
    {
        bFindData = FALSE;
        for (i = 0; i < m_lpAlarmInV40->dwEnablePtzTrackChanNum; i++)
        {
            if ( m_lpAlarmInV40->struPtzTrackInfo[i].dwEnablePtzTrackChan == m_nChannel)
            {
                m_lpAlarmInV40->struPtzTrackInfo[i].dwPtzTrackNo = (DWORD)m_iTrackNo;
                bFindData = TRUE;
                break;
            }
        }
        
        //Not found, add directly behind
        if (!bFindData)
        {
            m_lpAlarmInV40->struPtzTrackInfo[m_lpAlarmInV40->dwEnablePtzTrackChanNum].dwEnablePtzTrackChan = m_nChannel;
            m_lpAlarmInV40->struPtzTrackInfo[m_lpAlarmInV40->dwEnablePtzTrackChanNum++].dwPtzTrackNo = (DWORD)m_iTrackNo;
        }
        
        //find Preset Info has this channel Info
        FindDataInPresetInfo(m_nChannel);
        
        //find Cruise Info has this channel Info
        FindDataInCruiseInfo(m_nChannel);
        
        
    }
}