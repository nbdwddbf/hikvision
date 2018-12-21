// DlgAtmFrameFormatV30.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAtmFrameFormatV30.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NET_INTERCEPTION 0
#define SERIAL_INTERCEPTION  2
#define NET_PROTOCOL 1
#define SERIAL_PROTOCOL 3
#define SERIAL_SERVER 4

////////////////////////////////////////////////////////////////////////////
// CDlgAtmFrameFormatV30 dialog/
CDlgAtmFrameFormatV30* g_pDlgAtmFrameForamtV31 = NULL;

/******************************************
Function:	CDlgAtmFrameFormatV30
Description:	Constructor Function
Input:	
Output:	
return: 
******************************************/
CDlgAtmFrameFormatV30::CDlgAtmFrameFormatV30(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAtmFrameFormatV30::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAtmFrameFormatV30)
	m_bEnableAtm = FALSE;
	m_bEnableDelayTime = FALSE;
	m_bEnableFilter = FALSE;
	m_csActionCode = _T("");
	m_csAtmIP = _T("");
	m_iAtmPort = 0;
	m_csEndCode = _T("");
	m_csFilterText = _T("");
	m_csLengthEndCode = _T("");
	m_dwDelayTime = 0;
	m_dwLengthFixLen = 0;
	m_dwLengthPos = 0;
	m_byLocationMultiplierValue = 0;
	m_dwLocationOffsetPos = 0;
	m_dwLocationRelativeOffset = 0;
	m_csLocationTokenCode = _T("");
	m_dwMaxLength = 0;
	m_dwMinLength = 0;
	m_dwOsdPosX = 0;
	m_dwOsdPosY = 0;
	m_csPreCode = _T("");
	m_csStartCode = _T("");
	m_dwLengthLen = 0;
	m_byBeginPos = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_iChannelNum = -1;

    memset(&m_struAtmFrameFormatV30, 0, sizeof(m_struAtmFrameFormatV30));
    memset(&m_struAtmProtocol, 0, sizeof(m_struAtmProtocol));
}

/******************************************
Function:	DoDataExchange
Description:	the map between control and variable
Input:	
Output:	
return: 
******************************************/
void CDlgAtmFrameFormatV30::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAtmFrameFormatV30)
	DDX_Control(pDX, IDC_LIST_RECORD_CHANNEL, m_listRecordChannel);
	DDX_Control(pDX, IDC_COMBO_START_MODE, m_comboStartMode);
	DDX_Control(pDX, IDC_COMBO_OSD_MODE, m_comboOsdMode);
	DDX_Control(pDX, IDC_COMBO_LOCATION_OFFSET_MODE, m_comboLocationOffsetMode);
	DDX_Control(pDX, IDC_COMBO_LOCATION_CODE_MODE, m_comboLocationCodeMode);
	DDX_Control(pDX, IDC_COMBO_LENGTH_END_CODE, m_comboLengthEndCode);
	DDX_Control(pDX, IDC_COMBO_LENGTH_MODE, m_comboLengthMode);
	DDX_Control(pDX, IDC_COMBO_INPUT_MODE, m_comboInputMode);
	DDX_Control(pDX, IDC_COMBO_FRAME_TYPE, m_comboFrameType);
	DDX_Control(pDX, IDC_COMBO_FILTER_MODE, m_comboFilterMode);
	DDX_Control(pDX, IDC_COMBO_END_MODE, m_comboEndMode);
	DDX_Control(pDX, IDC_COMBO_ATM_TYPE, m_comboAtmType);
	DDX_Control(pDX, IDC_COMBO_ACTION_TYPE, m_comboActionType);
	DDX_Control(pDX, IDC_COMBO_ACTION_CODE_MODE, m_comboActionCodeMode);
	DDX_Check(pDX, IDC_CHK_ENABLE_ATM, m_bEnableAtm);
	DDX_Check(pDX, IDC_CHECK_ENABLE_DELAYTIME, m_bEnableDelayTime);
	DDX_Check(pDX, IDC_CHECK_ENABLE_FILTER, m_bEnableFilter);
	DDX_Text(pDX, IDC_EDIT_ACTION_CODE, m_csActionCode);
	DDX_Text(pDX, IDC_EDIT_ATM_IP, m_csAtmIP);
	DDX_Text(pDX, IDC_EDIT_ATM_PORT, m_iAtmPort);
	DDX_Text(pDX, IDC_EDIT_END_CODE, m_csEndCode);
	DDX_Text(pDX, IDC_EDIT_FILTER_TEXT, m_csFilterText);
	DDX_Text(pDX, IDC_EDIT_LENGTH_END_CODE, m_csLengthEndCode);
	DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_dwDelayTime);
	DDX_Text(pDX, IDC_EDIT_LENGTH_FIX_LENGTH, m_dwLengthFixLen);
	DDX_Text(pDX, IDC_EDIT_LENGTH_POS, m_dwLengthPos);
	DDX_Text(pDX, IDC_EDIT_LOCATION_MULTIPLIER_VALUE, m_byLocationMultiplierValue);
	DDX_Text(pDX, IDC_EDIT_LOCATION_OFFSET_POS, m_dwLocationOffsetPos);
	DDX_Text(pDX, IDC_EDIT_LOCATION_RELATIVE_OFFSET, m_dwLocationRelativeOffset);
	DDX_Text(pDX, IDC_EDIT_LOCATION_TOKEN_CODE, m_csLocationTokenCode);
	DDX_Text(pDX, IDC_EDIT_MAX_LENNGH, m_dwMaxLength);
	DDX_Text(pDX, IDC_EDIT_MIN_LENGTH, m_dwMinLength);
	DDX_Text(pDX, IDC_EDIT_OSD_POS_X, m_dwOsdPosX);
	DDX_Text(pDX, IDC_EDIT_OSD_POS_Y, m_dwOsdPosY);
	DDX_Text(pDX, IDC_EDIT_PRE_CODE, m_csPreCode);
	DDX_Text(pDX, IDC_EDIT_START_CODE, m_csStartCode);
	DDX_Text(pDX, IDC_EDITLENGTH_LEN, m_dwLengthLen);
	DDX_Text(pDX, IDC_EDIT_BEGIN_POS, m_byBeginPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAtmFrameFormatV30, CDialog)
	//{{AFX_MSG_MAP(CDlgAtmFrameFormatV30)
	ON_BN_CLICKED(IDC_CHK_ENABLE_ATM, OnChkEnableAtm)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUT_MODE, OnSelchangeComboInputMode)
	ON_CBN_SELCHANGE(IDC_COMBO_ATM_TYPE, OnSelchangeComboAtmType)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAME_TYPE, OnSelchangeComboFrameType)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTION_TYPE, OnSelchangeComboActionType)
	ON_BN_CLICKED(IDC_BTN_PACKAGE_CONFIRM, OnBtnPackageConfirm)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_FILTER, OnCheckEnableFilter)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_DELAYTIME, OnCheckEnableDelaytime)
	ON_CBN_SELCHANGE(IDC_COMBO_OSD_MODE, OnSelchangeComboOsdMode)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCATION_OFFSET_MODE, OnSelchangeComboLocationOffsetMode)
	ON_CBN_SELCHANGE(IDC_COMBO_LENGTH_MODE, OnSelchangeComboLengthMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAtmFrameFormatV30 message handlers

/******************************************
Function:	OnOK    
Description:   Function
Input:	
Output:	
return: void
******************************************/
void CDlgAtmFrameFormatV30::OnOK() 
{
	// TODO: Add extra validation here
   
    UpdateData(TRUE);
    m_struAtmFrameFormatV30.byEnable = m_bEnableAtm;
    m_struAtmFrameFormatV30.byInputMode = m_comboInputMode.GetCurSel();
    memcpy(m_struAtmFrameFormatV30.struAtmIp.sIpV4 ,m_csAtmIP.GetBuffer(0), 16);
    m_struAtmFrameFormatV30.wAtmPort = (WORD)m_iAtmPort;
    if (m_comboAtmType.GetCurSel() == CB_ERR)
    {
        m_struAtmFrameFormatV30.dwAtmType = 0;
    }
    else{
        m_struAtmFrameFormatV30.dwAtmType = m_comboAtmType.GetItemData(m_comboAtmType.GetCurSel());
    }

    SetIdentificat(&m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struIdentification);
    SetFilter(&m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struFilter);
    SetOverlayChannel(&m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struOverlayChan);
    
    if (NET_DVR_SetAtmFrameFormat_V30(m_lServerID, 0, &m_struAtmFrameFormatV30))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAtmFrameFormat_V30");
        AfxMessageBox("Config successfully, it will take effect after reboot");
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAtmFrameFormat_V30");
    }
 
//	CDialog::OnOK();
}

/******************************************
Function:	OnCancel
Description: function for Cancel Event
Input:	
Output:	
return: void
******************************************/
void CDlgAtmFrameFormatV30::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlgAtmFrameFormatV30::OnInitDialog() 
{
	CDialog::OnInitDialog();

    g_pDlgAtmFrameForamtV31 = this;
    
    m_listRecordChannel.SetExtendedStyle(LVS_EX_CHECKBOXES);
    int i;
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    char szLan[128] = {0};
    m_listRecordChannel.DeleteAllItems();
    for (i = 0; i < m_iChannelNum; i++)
    {
        sprintf(sbufCn, "Channel%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listRecordChannel.InsertItem(i, szLan);
    }

    if (NET_DVR_GetAtmFrameFormat_V30(m_lServerID, 0, &m_struAtmFrameFormatV30))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetAtmFrameFormat_V30");
        
        GetFrameFormatSet(m_struAtmFrameFormatV30);
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetAtmFrameFormat_V30");
    }
    

    if (NET_DVR_GetAtmProtocol(m_lServerID, &m_struAtmProtocol))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetAtmProtocol");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetAtmProtocol");
    }
	
    m_bEnableAtm = m_struAtmFrameFormatV30.byEnable;
    UpdateData(FALSE);
    OnChkEnableAtm();

    m_comboInputMode.SetCurSel(m_struAtmFrameFormatV30.byInputMode);
    OnSelchangeComboInputMode();
    
    m_csAtmIP = m_struAtmFrameFormatV30.struAtmIp.sIpV4;
    m_iAtmPort = m_struAtmFrameFormatV30.wAtmPort;
  
    GetIdentificatSet(m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struIdentification);
    GetFilterSet(m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struFilter);
    GetOverlayChannelSet(m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struOverlayChan);
    
    UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgAtmFrameFormatV30::GetFrameFormatSet(NET_DVR_ATM_FRAMEFORMAT_V30 struAtmFrameFormatV30)
{

    return TRUE;
}


void CDlgAtmFrameFormatV30::OnChkEnableAtm() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    EnableAtmWnd(m_bEnableAtm); //Enable or Disable ATM control

}

/******************************************
Function:	
Description:	
Input:	
Output:	
return: 
******************************************/
BOOL CDlgAtmFrameFormatV30::EnableAtmWnd(BOOL m_bEnableAtm)
{
    GetDlgItem(IDC_COMBO_INPUT_MODE)->EnableWindow(m_bEnableAtm);
    GetDlgItem(IDC_COMBO_ATM_TYPE)->EnableWindow(m_bEnableAtm);
    GetDlgItem(IDC_EDIT_ATM_IP)->EnableWindow(m_bEnableAtm);
    GetDlgItem(IDC_EDIT_ATM_PORT)->EnableWindow(m_bEnableAtm);
    OnSelchangeComboAtmType();
      
    return TRUE;
}

void CDlgAtmFrameFormatV30::OnSelchangeComboInputMode() 
{
	// TODO: Add your control notification handler code here
    int nInputMode = m_comboInputMode.GetCurSel();
    int nIndex = 0 ;
	if (NET_INTERCEPTION == nInputMode)
	{
        m_comboAtmType.ResetContent();
        nIndex = 0;
        for (int i = 0; i < m_struAtmProtocol.struNetListenList.dwAtmProtoNum; i++)
        {
            m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struNetListenList.struAtmProtoType[nIndex].chDesc);
            m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struNetListenList.struAtmProtoType[nIndex].dwAtmType);
            nIndex++;
        }
        m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struCustomProto.chDesc);
        m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struCustomProto.dwAtmType);
       GetDlgItem(IDC_EDIT_ATM_IP)->EnableWindow(m_bEnableAtm);
       GetDlgItem(IDC_EDIT_ATM_PORT)->EnableWindow(FALSE);

	}
    else if (SERIAL_INTERCEPTION == nInputMode)
    {
        m_comboAtmType.ResetContent();
        nIndex = 0;
        for (int i = 0; i < m_struAtmProtocol.struSerialListenList.dwAtmProtoNum; i++)
        {
            m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struSerialListenList.struAtmProtoType[nIndex].chDesc);
            m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struSerialListenList.struAtmProtoType[nIndex].dwAtmType);
            nIndex++;
        }
        m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struCustomProto.chDesc);
        m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struCustomProto.dwAtmType);
       GetDlgItem(IDC_EDIT_ATM_IP)->EnableWindow(FALSE);
       GetDlgItem(IDC_EDIT_ATM_PORT)->EnableWindow(FALSE);
    }
    else if (NET_PROTOCOL == nInputMode)
    {
        m_comboAtmType.ResetContent();
        nIndex = 0;
        for (int i = 0; i < m_struAtmProtocol.struNetProtoList.dwAtmProtoNum; i++)
        {
            m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struNetProtoList.struAtmProtoType[nIndex].chDesc);
            m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struNetProtoList.struAtmProtoType[nIndex].dwAtmType);
            nIndex++;
        }
        GetDlgItem(IDC_EDIT_ATM_IP)->EnableWindow(FALSE);
       GetDlgItem(IDC_EDIT_ATM_PORT)->EnableWindow(m_bEnableAtm);
    }
    else if (SERIAL_PROTOCOL == nInputMode)
    {
        m_comboAtmType.ResetContent();
        nIndex = 0;
        for (int i = 0; i < m_struAtmProtocol.struSerialProtoList.dwAtmProtoNum; i++)
        {
            m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struSerialProtoList.struAtmProtoType[nIndex].chDesc);
            m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struSerialProtoList.struAtmProtoType[nIndex].dwAtmType);
            nIndex++;
        }
        GetDlgItem(IDC_EDIT_ATM_IP)->EnableWindow(FALSE);
       GetDlgItem(IDC_EDIT_ATM_PORT)->EnableWindow(FALSE);
    }
    else if (SERIAL_SERVER == nInputMode)
    {
        m_comboAtmType.ResetContent();
        nIndex = 0;
        for (int i = 0; i < m_struAtmProtocol.struSerialListenList.dwAtmProtoNum; i++)
        {
            m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struSerialListenList.struAtmProtoType[nIndex].chDesc);
            m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struSerialListenList.struAtmProtoType[nIndex].dwAtmType);
            nIndex++;
        }
        
        m_comboAtmType.InsertString(nIndex, m_struAtmProtocol.struSerialListenList.struAtmProtoType[ATM_CUSTOM_PROTO -1].chDesc);
        m_comboAtmType.SetItemData(nIndex, m_struAtmProtocol.struSerialListenList.struAtmProtoType[ATM_CUSTOM_PROTO -1].dwAtmType);
        GetDlgItem(IDC_EDIT_ATM_IP)->EnableWindow(m_bEnableAtm);
       GetDlgItem(IDC_EDIT_ATM_PORT)->EnableWindow(m_bEnableAtm);

    }
    else 
    {
        TRACE("\nInputMode ERROR\n");
    }
    BOOL bfalg = FALSE;
    for (int i = 0;  i <= nIndex; i ++)
    {
        if (m_comboAtmType.GetItemData(i) == m_struAtmFrameFormatV30.dwAtmType)
        {
            bfalg = TRUE;
            m_comboAtmType.SetCurSel(i);
            OnSelchangeComboAtmType();    
        }
    }

    if (bfalg == FALSE)
    {
        m_comboAtmType.SetCurSel(0);
        OnSelchangeComboAtmType();
    }
    
}

void CDlgAtmFrameFormatV30::OnSelchangeComboAtmType() 
{
	// TODO: Add your control notification handler code here
	if (m_comboAtmType.GetItemData(m_comboAtmType.GetCurSel()) == ATM_CUSTOM_PROTO)
	{
        EnableAtmTypeWnd(m_bEnableAtm);

        GetIdentificatSet(m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struIdentification);
        GetFilterSet(m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struFilter);
        m_comboFrameType.SetCurSel(0);
        OnSelchangeComboFrameType();
        GetOverlayChannelSet(m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struOverlayChan);
	}
    else
    {
        EnableAtmTypeWnd(FALSE);
    }
}

BOOL CDlgAtmFrameFormatV30::EnableAtmTypeWnd(BOOL bEnable)
{

        GetDlgItem(IDC_EDIT_START_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        GetDlgItem(IDC_EDIT_START_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_COMBO_START_MODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_COMBO_END_MODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_EDIT_END_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        
GetDlgItem(IDC_CHECK_ENABLE_FILTER)->EnableWindow(bEnable && m_bEnableAtm);
        
    EnableFilterWnd(bEnable && m_bEnableFilter && m_bEnableAtm);
        
        GetDlgItem(IDC_CHECK_ENABLE_DELAYTIME)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(bEnable && m_bEnableDelayTime && m_bEnableAtm);
        
        GetDlgItem(IDC_LIST_RECORD_CHANNEL)->EnableWindow(bEnable && m_bEnableAtm);
        GetDlgItem(IDC_COMBO_FRAME_TYPE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_COMBO_ACTION_TYPE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        
        GetDlgItem(IDC_COMBO_LOCATION_OFFSET_MODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_EDIT_LOCATION_OFFSET_POS)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_COMBO_LOCATION_CODE_MODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_EDIT_LOCATION_TOKEN_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_EDIT_LOCATION_MULTIPLIER_VALUE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_EDIT_LOCATION_RELATIVE_OFFSET)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_COMBO_OSD_MODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        
        
        
        
        
        
        GetDlgItem(IDC_COMBO_LENGTH_MODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_EDIT_LENGTH_FIX_LENGTH)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_EDIT_OSD_POS_X)->EnableWindow(bEnable && m_bEnableAtm);
        GetDlgItem(IDC_EDIT_OSD_POS_Y)->EnableWindow(bEnable && m_bEnableAtm);
        GetDlgItem(IDC_EDIT_MAX_LENNGH)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_EDIT_MIN_LENGTH)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_COMBO_LENGTH_END_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_EDIT_LENGTH_END_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        GetDlgItem(IDC_EDIT_LENGTH_POS)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_EDITLENGTH_LEN)->EnableWindow(bEnable && m_bEnableAtm);
        GetDlgItem(IDC_EDIT_PRE_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        GetDlgItem(IDC_COMBO_ACTION_CODE_MODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
        GetDlgItem(IDC_EDIT_ACTION_CODE)->EnableWindow(bEnable && m_bEnableAtm);
        
        
    GetDlgItem(IDC_BTN_PACKAGE_CONFIRM)->EnableWindow(bEnable && m_bEnableAtm);
    return TRUE;
}

void CDlgAtmFrameFormatV30::OnSelchangeComboFrameType() 
{
	// TODO: Add your control notification handler code here
    int nFrameTypeIndex = m_comboFrameType.GetCurSel();
	if ( 3 == nFrameTypeIndex)
	{
        m_comboActionType.EnableWindow(TRUE);
        m_comboActionType.SetCurSel(0);
        OnSelchangeComboActionType();
        EnableActionWnd(TRUE);
	}
    else
    {
        m_comboActionType.EnableWindow(FALSE);
        NET_DVR_ATM_PACKAGE_OTHERS struAtmPackage;
        if ( 0 == nFrameTypeIndex)
        {
            memcpy(&struAtmPackage, &m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struCardNoPara, sizeof(struAtmPackage));
        }
        else if ( 1 == nFrameTypeIndex)
        {
            memcpy(&struAtmPackage, &m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struAmountPara, sizeof(struAtmPackage));
        }
        else if ( 2 == nFrameTypeIndex)
        {
            memcpy(&struAtmPackage, &m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struSerialNoPara, sizeof(struAtmPackage));
        }
        else
        {
            TRACE("\nErrror\n");//Error
        }
        EnableActionWnd(FALSE);       
        GetAtmPackageSet(struAtmPackage);
    }
    UpdateData(FALSE);
}

BOOL CDlgAtmFrameFormatV30::EnableActionWnd(BOOL bActionWnd)
{
    GetDlgItem(IDC_COMBO_ACTION_CODE_MODE)->EnableWindow(bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_ACTION_CODE)->EnableWindow(bActionWnd && m_bEnableAtm);
    
    GetDlgItem(IDC_COMBO_LENGTH_MODE)->EnableWindow(!bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_LENGTH_FIX_LENGTH)->EnableWindow(!bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_MIN_LENGTH)->EnableWindow(!bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_MAX_LENNGH)->EnableWindow(!bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_COMBO_LENGTH_END_CODE)->EnableWindow(!bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_LENGTH_END_CODE)->EnableWindow(!bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_LENGTH_POS)->EnableWindow(!bActionWnd && m_bEnableAtm);
    GetDlgItem(IDC_EDITLENGTH_LEN)->EnableWindow(!bActionWnd && m_bEnableAtm);
    return TRUE;
}

void CDlgAtmFrameFormatV30::OnSelchangeComboActionType() 
{
	// TODO: Add your control notification handler code here
    
    int nActionIndex = m_comboActionType.GetCurSel();
    GetAtmPackageActionSet(m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struTradeActionPara[nActionIndex]);
    UpdateData(FALSE);
}

BOOL CDlgAtmFrameFormatV30::GetAtmPackageSet(NET_DVR_ATM_PACKAGE_OTHERS struAtmPackage)
{

    // Location
    GetLocationParaSet(struAtmPackage.struPackageLocation);

    // length
    GetPackageLengthSet(struAtmPackage.struPackageLength);
    
    //OSD
    GetOsdPositionSet(struAtmPackage.struOsdPosition);

    //PreCode
    m_csPreCode = struAtmPackage.struPreCode.code;

    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetAtmPackage(LPNET_DVR_ATM_PACKAGE_OTHERS lpAtmPackage)
{
    //Location
    SetLocationParam(&lpAtmPackage->struPackageLocation);

    //Length
    SetPackageLength(&lpAtmPackage->struPackageLength);

    //OSD
    SetOsdPosition(&lpAtmPackage->struOsdPosition);

    memcpy(lpAtmPackage->struPreCode.code, m_csPreCode.GetBuffer(0), 12);

    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::GetAtmPackageActionSet(NET_DVR_ATM_PACKAGE_ACTION struAtmPackageAction)
{

    //Location
    GetLocationParaSet(struAtmPackageAction.struPackageLocation);
    //OSD
    GetOsdPositionSet(struAtmPackageAction.struOsdPosition); 
    //Transection Type
    m_comboActionCodeMode.SetCurSel(struAtmPackageAction.byActionCodeMode);
    

    m_csActionCode = struAtmPackageAction.struActionCode.code;
    //
    m_csPreCode = struAtmPackageAction.struPreCode.code;
    
    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetAtmPackageAction(LPNET_DVR_ATM_PACKAGE_ACTION lpAtmPackageAction)
{
    //Location
    SetLocationParam(&lpAtmPackageAction->struPackageLocation);

    //OSD
    SetOsdPosition(&lpAtmPackageAction->struOsdPosition);

    //
    lpAtmPackageAction->byActionCodeMode =  m_comboActionCodeMode.GetCurSel();
    memcpy(lpAtmPackageAction->struActionCode.code, m_csActionCode.GetBuffer(0), 12);

    //
    memcpy(lpAtmPackageAction->struPreCode.code, m_csPreCode.GetBuffer(0), 12);
    
    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::GetLocationParaSet(NET_DVR_PACKAGE_LOCATION struPackageLocation)
{
    m_comboLocationOffsetMode.SetCurSel(struPackageLocation.byOffsetMode);
    OnSelchangeComboLocationOffsetMode();

    m_dwLocationOffsetPos = struPackageLocation.dwOffsetPos;
    m_csLocationTokenCode = struPackageLocation.struTokenCode.code;
    m_byLocationMultiplierValue = struPackageLocation.byMultiplierValue;
    m_dwLocationRelativeOffset = struPackageLocation.byEternOffset;
    m_comboLocationCodeMode.SetCurSel(struPackageLocation.byCodeMode);
    
    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetLocationParam(LPNET_DVR_PACKAGE_LOCATION lpPackageLocation)
{
    lpPackageLocation->byOffsetMode = m_comboLocationOffsetMode.GetCurSel();
    lpPackageLocation->dwOffsetPos = m_dwLocationOffsetPos;
    memcpy(lpPackageLocation->struTokenCode.code, m_csLocationTokenCode.GetBuffer(0), 12);
    lpPackageLocation->byMultiplierValue = m_byLocationMultiplierValue;
    lpPackageLocation->byEternOffset = m_dwLocationRelativeOffset;
    lpPackageLocation->byCodeMode = m_comboLocationCodeMode.GetCurSel();
    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::GetOsdPositionSet(NET_DVR_OSD_POSITION sturOsdPosition)
{
    m_comboOsdMode.SetCurSel(sturOsdPosition.byPositionMode);
    OnSelchangeComboOsdMode();
    m_dwOsdPosX = sturOsdPosition.dwPosX;
    m_dwOsdPosY = sturOsdPosition.dwPosY;
    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetOsdPosition(LPNET_DVR_OSD_POSITION lpOsdPosition)
{
    lpOsdPosition->byPositionMode = m_comboOsdMode.GetCurSel();
    lpOsdPosition->dwPosX = m_dwOsdPosX;
    lpOsdPosition->dwPosY = m_dwOsdPosY; 
    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::GetPackageLengthSet(NET_DVR_PACKAGE_LENGTH struPackageLength)
{

    m_comboLengthMode.SetCurSel(struPackageLength.byLengthMode);
    OnSelchangeComboLengthMode();
    m_dwLengthFixLen = struPackageLength.dwFixLength;
    
    m_dwMaxLength = struPackageLength.dwMaxLength;
    m_dwMinLength = struPackageLength.dwMinLength;
    m_comboLengthEndCode.SetCurSel(struPackageLength.byEndMode);
    m_csLengthEndCode = struPackageLength.struEndCode.code;
    m_dwLengthPos = struPackageLength.dwLengthPos;
    m_dwLengthLen = struPackageLength.dwLengthLen;
    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetPackageLength(LPNET_DVR_PACKAGE_LENGTH lpPackageLength)
{
    lpPackageLength->byLengthMode = m_comboLengthMode.GetCurSel();
    lpPackageLength->dwFixLength = m_dwLengthFixLen;
    
    lpPackageLength->dwMaxLength = m_dwMaxLength;
    lpPackageLength->dwMinLength = m_dwMinLength;
    lpPackageLength->byEndMode = m_comboLengthEndCode.GetCurSel();
    memcpy(lpPackageLength->struEndCode.code, m_csLengthEndCode.GetBuffer(0), 12);
    lpPackageLength->dwLengthPos = m_dwLengthPos;
    lpPackageLength->dwLengthLen = m_dwLengthLen;
    return TRUE;
}


BOOL CDlgAtmFrameFormatV30::GetIdentificatSet(NET_DVR_IDENTIFICAT struIdentificat)
{

    m_comboStartMode.SetCurSel(struIdentificat.byStartMode);
    m_csStartCode = struIdentificat.struStartCode.code;
    m_comboEndMode.SetCurSel(struIdentificat.byEndMode);
    m_csEndCode = struIdentificat.struEndCode.code;

    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetIdentificat(LPNET_DVR_IDENTIFICAT lpIdentificat)
{
    lpIdentificat->byStartMode = m_comboStartMode.GetCurSel();
    memcpy(lpIdentificat->struStartCode.code, m_csStartCode.GetBuffer(0), 12);
    
    lpIdentificat->byEndMode = m_comboEndMode.GetCurSel();
    memcpy(lpIdentificat->struEndCode.code, m_csEndCode.GetBuffer(0), 12);

    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::GetFilterSet(NET_DVR_FILTER struFilter)
{   
    m_comboFilterMode.SetCurSel(struFilter.byMode);
    m_csFilterText = struFilter.byFilterText;
    m_bEnableFilter = struFilter.byEnable;
    m_byBeginPos = struFilter.byFrameBeginPos;
 
        UpdateData(FALSE);
    OnCheckEnableFilter();

    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetFilter(LPNET_DVR_FILTER lpFilter)
{
    lpFilter->byEnable = m_bEnableFilter;
    lpFilter->byFrameBeginPos = m_byBeginPos;
    lpFilter->byMode = m_comboFilterMode.GetCurSel();
    memcpy(lpFilter->byFilterText, m_csFilterText.GetBuffer(0), 16);

    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::GetOverlayChannelSet(NET_DVR_OVERLAY_CHANNEL struOverlayChannel)
{
    for (int i = 0; i < m_iChannelNum; i++ )
    {
        if (struOverlayChannel.byChannel[i])
        {
            m_listRecordChannel.SetCheck(i);
        }
	}

    m_dwDelayTime = struOverlayChannel.dwDelayTime;
    m_bEnableDelayTime = struOverlayChannel.byEnableDelayTime;
    UpdateData(FALSE);
    OnCheckEnableDelaytime();

    return TRUE;
}

BOOL CDlgAtmFrameFormatV30::SetOverlayChannel(LPNET_DVR_OVERLAY_CHANNEL lpOverlayChannel)
{
    
    for (int i = 0; i < m_iChannelNum; i++)
    {
        lpOverlayChannel->byChannel[i] = (BYTE)m_listRecordChannel.GetCheck(i);
    }

    lpOverlayChannel->dwDelayTime = m_dwDelayTime;
    lpOverlayChannel->byEnableDelayTime = m_bEnableDelayTime;
    return TRUE;
}

void CDlgAtmFrameFormatV30::OnBtnPackageConfirm() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int nFrameTypeIndex = m_comboFrameType.GetCurSel();    
    if (3 == nFrameTypeIndex) 
    {
        int nActionIndex = m_comboActionType.GetCurSel();

        SetAtmPackageAction(&m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struTradeActionPara[nActionIndex]);
    }
    else
    {
        if (0 == nFrameTypeIndex)
        {
            SetAtmPackage(&m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struCardNoPara);
        }
        else if (1 == nFrameTypeIndex)
        {
            SetAtmPackage(&m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struAmountPara);
        }
        else if (2 == nFrameTypeIndex)
        {
            SetAtmPackage(&m_struAtmFrameFormatV30.struAtmUserDefineProtocol.struSerialNoPara);
        }
        else
        {
            TRACE("\nERROR\n");
        }
    }
}

void CDlgAtmFrameFormatV30::OnCheckEnableFilter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    EnableFilterWnd(m_bEnableFilter);
}

BOOL CDlgAtmFrameFormatV30::EnableFilterWnd(BOOL bEnable)
{
    GetDlgItem(IDC_COMBO_FILTER_MODE)->EnableWindow(bEnable && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_FILTER_TEXT)->EnableWindow(bEnable && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_BEGIN_POS)->EnableWindow(bEnable && m_bEnableAtm);
    return TRUE;
}

void CDlgAtmFrameFormatV30::OnCheckEnableDelaytime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(m_bEnableDelayTime && m_bEnableAtm);
    
}

void CDlgAtmFrameFormatV30::OnSelchangeComboOsdMode() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_comboOsdMode.GetCurSel()) //not display
	{
        GetDlgItem(IDC_EDIT_OSD_POS_X)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_OSD_POS_Y)->EnableWindow(FALSE);
	}
    else if (1 == m_comboOsdMode.GetCurSel())
    {
        GetDlgItem(IDC_EDIT_OSD_POS_X)->EnableWindow(m_bEnableAtm);
        GetDlgItem(IDC_EDIT_OSD_POS_Y)->EnableWindow(m_bEnableAtm); 
    }
}



void CDlgAtmFrameFormatV30::OnSelchangeComboLocationOffsetMode() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_comboLocationOffsetMode.GetCurSel())   //token
	{
       EnableAtmLocationWnd(TRUE);
	} 
	else if (1 == m_comboLocationOffsetMode.GetCurSel())
	{
        EnableAtmLocationWnd(FALSE);
	}
}

void CDlgAtmFrameFormatV30::EnableAtmLocationWnd(BOOL bEnableToken)
{
    GetDlgItem(IDC_COMBO_LOCATION_CODE_MODE)->EnableWindow(bEnableToken && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_LOCATION_TOKEN_CODE)->EnableWindow(bEnableToken && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_LOCATION_MULTIPLIER_VALUE)->EnableWindow(bEnableToken && m_bEnableAtm);
    GetDlgItem(IDC_EDIT_LOCATION_RELATIVE_OFFSET)->EnableWindow(bEnableToken && m_bEnableAtm);

    GetDlgItem(IDC_EDIT_LOCATION_OFFSET_POS)->EnableWindow(!bEnableToken && m_bEnableAtm);
}

void CDlgAtmFrameFormatV30::OnSelchangeComboLengthMode() 
{
	// TODO: Add your control notification handler code here
    GetDlgItem(IDC_EDIT_LENGTH_FIX_LENGTH)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_MIN_LENGTH)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_MAX_LENNGH)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_LENGTH_END_CODE)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_LENGTH_END_CODE)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_LENGTH_POS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDITLENGTH_LEN)->EnableWindow(FALSE);
    if (0 == m_comboLengthMode.GetCurSel()) //variable
    {
        GetDlgItem(IDC_EDIT_MIN_LENGTH)->EnableWindow(m_bEnableAtm);
        GetDlgItem(IDC_EDIT_MAX_LENNGH)->EnableWindow(m_bEnableAtm);    
        GetDlgItem(IDC_COMBO_LENGTH_END_CODE)->EnableWindow(m_bEnableAtm);
        GetDlgItem(IDC_EDIT_LENGTH_END_CODE)->EnableWindow(m_bEnableAtm);
    }
    else if (1 == m_comboLengthMode.GetCurSel()) // fixed
    {
        GetDlgItem(IDC_EDIT_LENGTH_FIX_LENGTH)->EnableWindow(m_bEnableAtm);
    }
    else if (2 == m_comboLengthMode.GetCurSel()) //Get from message
    {
        GetDlgItem(IDC_EDIT_LENGTH_POS)->EnableWindow(m_bEnableAtm);
        GetDlgItem(IDC_EDITLENGTH_LEN)->EnableWindow(m_bEnableAtm);
    }
}
