/**********************************************************
FileName:    DlgRemoteAlarmInPtzInvoke.cpp
Description: 告警触发云台处理      
Date:        
Note: 		
Modification History:      
<version> <time>         <desc>
    
***********************************************************/


#include "stdafx.h"
#include "config.h"
#include "DlgRemoteAlarmInPtzInvoke.h"


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
	, m_iPresetNo(0)
	, m_iCruiseNo(0)
	, m_iTrackNo(0)
	, m_bPreset(FALSE)
	, m_bCruise(FALSE)
	, m_bTrack(FALSE)
	, m_lpAlarmIn(NULL)
	, m_nChannel(0)
	, m_iChanCount(0)
	, m_lStartChannel(0)
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
	DDX_Control(pDX, IDC_COMBO_PTZ_LINKAGE__CHAN, m_comboChan);
	DDX_Text(pDX, IDC_EDIT_PRESET_NO, m_iPresetNo);
	DDX_Text(pDX, IDC_EDIT_TRACK_NO, m_iTrackNo);
	DDX_Text(pDX, IDC_EDIT_CRUISE_NO, m_iCruiseNo);
	//}}AFX_DATA_MAP

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
	ON_CBN_SELCHANGE(IDC_COMBO_PTZ_LINKAGE__CHAN, OnCbnSelchangeComboPtzLinkage)
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
	m_comboChan.ResetContent();
	for (int i=0; i<m_iChanCount; i++)
	{
		g_StringLanType(szLan, "通道", "Channel");
		sTemp.Format("%s%d", szLan, (m_lStartChannel+i));
		m_comboChan.AddString(sTemp);
	}
	m_nChannel = 0;
	m_comboChan.SetCurSel(m_nChannel);
	m_bPreset = m_lpAlarmIn->byEnablePreset[m_nChannel];
	m_bCruise = m_lpAlarmIn->byEnableCruise[m_nChannel];
	m_bTrack = m_lpAlarmIn->byEnablePtzTrack[m_nChannel];
	m_iPresetNo = m_lpAlarmIn->byPresetNo[m_nChannel];
	m_iCruiseNo = m_lpAlarmIn->byCruiseNo[m_nChannel];
	m_iTrackNo = m_lpAlarmIn->byPTZTrack[m_nChannel];
	((CButton *)GetDlgItem(IDC_RADIO_PRESET))->SetCheck(m_bPreset);
	((CButton *)GetDlgItem(IDC_RADIO_CRUISE))->SetCheck(m_bCruise);
	((CButton *)GetDlgItem(IDC_RADIO_TRACK))->SetCheck(m_bTrack);
	EnableCtrl();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}

/*********************************************************
  Function:	OnBnClickedBtnPtzOk
  Desc:		设置告警输入触发的云台相关操作
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::OnBnClickedBtnPtzOk()
{
	UpdateData(TRUE);
	m_nChannel = m_comboChan.GetCurSel();
	m_lpAlarmIn->byEnablePreset[m_nChannel] = m_bPreset;
	m_lpAlarmIn->byEnableCruise[m_nChannel] = m_bCruise;
	m_lpAlarmIn->byEnablePtzTrack[m_nChannel] = m_bTrack;
	m_lpAlarmIn->byPresetNo[m_nChannel] = m_iPresetNo;
	m_lpAlarmIn->byCruiseNo[m_nChannel] = m_iCruiseNo;
	m_lpAlarmIn->byPTZTrack[m_nChannel] = m_iTrackNo;

	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnPtzExit
  Desc:		取消告警输入触发的云台相关操作的设置
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
  Desc:		显示对应告警输入的联动操作
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInPtzInvoke::OnCbnSelchangeComboPtzLinkage()
{
	UpdateData(TRUE);
	m_nChannel = m_comboChan.GetCurSel();
	m_bPreset = m_lpAlarmIn->byEnablePreset[m_nChannel];
	m_bCruise = m_lpAlarmIn->byEnableCruise[m_nChannel];
	m_bTrack = m_lpAlarmIn->byEnablePtzTrack[m_nChannel];
	m_iPresetNo = m_lpAlarmIn->byPresetNo[m_nChannel];
	m_iCruiseNo = m_lpAlarmIn->byCruiseNo[m_nChannel];
	m_iTrackNo = m_lpAlarmIn->byPTZTrack[m_nChannel];

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

