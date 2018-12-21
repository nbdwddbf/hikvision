/**********************************************************
FileName:    DlgChannelInfo.cpp
Description: channel info    
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp 
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgChannelInfo.h"
#include ".\dlgchannelinfo.h"


// CDlgChannelInfo dialog
/*********************************************************
  Function:	CDlgChannelInfo
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgChannelInfo, CDialog)
CDlgChannelInfo::CDlgChannelInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChannelInfo::IDD, pParent)
	, m_csChanName(_T(""))
	, m_iChanNo(0)
	, m_csLocalNodeName(_T(""))
	, m_csDeviceIP(_T(""))
	, m_bChanged(FALSE)
	, m_pChanInfo(NULL)
{
}

/*********************************************************
  Function:	~CDlgChannelInfo
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgChannelInfo::~CDlgChannelInfo()
{
	if (m_pChanInfo != NULL)
	{
		m_pChanInfo = NULL;
	}
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		map between control and data
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChannelInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgChannelInfo)
    DDX_Control(pDX, IDC_COMBO_PREVIEW_PROTOCOL_TYPE, m_cmPreviewProtocolType);
    DDX_Control(pDX, IDC_COMBO_PASSBACK_RECORD, m_comboPassbackRecord);
    DDX_Text(pDX, IDC_CHANNAME, m_csChanName);
    DDX_Text(pDX, IDC_CHANNO, m_iChanNo);
    DDX_Control(pDX, IDC_COMBO_PREVIEW_TYPE, m_cmPreviewMode);
    DDX_Text(pDX, IDC_CHANINFO_DEV_NAME, m_csLocalNodeName);
    DDX_Text(pDX, IDC_CHAN_DEVICE_IP, m_csDeviceIP);
    DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_comboProtocol);
    DDX_Control(pDX, IDC_COMBO_TRANSPORT_TYPE, m_comboTransportType);
    //}}AFX_DATA_MAP

    DDX_Control(pDX, IDC_COMBO_VIDEO_CODING_TYPE, m_comVideoCodingType);
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		message map list
  Input:	
  Output:	
  Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgChannelInfo, CDialog)
//{{AFX_MSG_MAP(CDlgChannelInfo)
ON_BN_CLICKED(ID_OK, OnBnClickedOk)
ON_BN_CLICKED(ID_CANCEL, OnBnClickedCancel)
ON_UPDATE_COMMAND_UI(ID_MENU_CHANNEL_INFO, OnUpdateMenuChannelInfo)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// CDlgChannelInfo message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize channel info dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgChannelInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_PASSBACKRECORD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_PASSBACK_RECORD)->ShowWindow(SW_HIDE);
    AddStreamType();
	if (m_pChanInfo == NULL)
	{
		return FALSE;
	}

	m_iChanNo = m_pChanInfo->iChannelNO;
	m_csChanName.Format("%s",m_pChanInfo->chChanName);
	m_csLocalNodeName.Format("%s",g_struDeviceInfo[m_pChanInfo->iDeviceIndex].chLocalNodeName);
	m_csDeviceIP.Format("%s",g_struDeviceInfo[m_pChanInfo->iDeviceIndex].chDeviceIP);
// 	m_comboProtocol.SetCurSel(m_pChanInfo->dwProtocol& 0x7fffffff);
// //	m_comboProtocol.SetCurSel( ( (m_pChanInfo->dwProtocol& 0x7fffffff) >= 7) ? ((m_pChanInfo->dwProtocol& 0x7fffffff)-3) : (m_pChanInfo->dwProtocol& 0x7fffffff));
// 	m_comboTransportType.SetCurSel((m_pChanInfo->dwProtocol>>31) & 0x01);


    m_comboProtocol.SetCurSel(m_pChanInfo->dwLinkMode);
    for (int i = 0; i < m_comboTransportType.GetCount(); i++)
    {
        if (m_comboTransportType.GetItemData(i) == m_pChanInfo->dwStreamType)
        {
            m_comboTransportType.SetCurSel(i);
            break;
        }
    }
    // m_comboTransportType.SetCurSel(g_struDeviceInfo[m_pChanInfo->iDeviceIndex].pStruChanInfo[m_pChanInfo->iChanIndex].dwStreamType);
    //m_cmPreviewMode.SetCurSel(g_struDeviceInfo[m_pChanInfo->iDeviceIndex].pStruChanInfo[m_pChanInfo->iChanIndex].dwPreviewMode);
    //m_cmPreviewProtocolType.SetCurSel(g_struDeviceInfo[m_pChanInfo->iDeviceIndex].pStruChanInfo[m_pChanInfo->iChanIndex].nPreviewProtocolType);
    
    m_comboProtocol.SetCurSel(m_pChanInfo->dwLinkMode);
    //m_comboTransportType.SetCurSel(m_pChanInfo->dwStreamType);
    m_cmPreviewMode.SetCurSel(m_pChanInfo->dwPreviewMode);
    m_cmPreviewProtocolType.SetCurSel(m_pChanInfo->nPreviewProtocolType);
    m_comVideoCodingType.SetCurSel(m_pChanInfo->nVideoCodingType);
	if ((g_struDeviceInfo[m_pChanInfo->iDeviceIndex].bySupport2 & 0x4) == 0x4)
	{
		GetDlgItem(IDC_STATIC_PASSBACKRECORD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_PASSBACK_RECORD)->ShowWindow(SW_SHOW);
		m_comboPassbackRecord.SetCurSel(m_pChanInfo->bPassbackRecord);
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgChannelInfo::AddStreamType()
{
    char szLan[128] = { 0 };
    int index = 0;

    m_comboTransportType.ResetContent();
    g_StringLanType(szLan, "主码流", "MainCode");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 0);
    index++;

    g_StringLanType(szLan, "子码流", "SubCode");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 1);
    index++;

    g_StringLanType(szLan, "码流3", "ThirdCode");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 2);
    index++;

    g_StringLanType(szLan, "码流4/转码流", "TransCode");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 3);
    index++;

    g_StringLanType(szLan, "码流5", "FifthCode");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 4);
    index++;

    g_StringLanType(szLan, "码流6(自定义)", "SixthCode(Custom)");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 5);
    index++;

    g_StringLanType(szLan, "码流7(自定义)", "SeventhCode(Custom)");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 7);
    index++;

    g_StringLanType(szLan, "码流8(自定义)", "EighthCode(Custom)");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 8);
    index++;

    g_StringLanType(szLan, "码流9(自定义)", "NinthCode(Custom)");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 9);
    index++;

    g_StringLanType(szLan, "码流10(自定义)", "TenthCode(Custom)");
    m_comboTransportType.AddString(szLan);
    m_comboTransportType.SetItemData(index, 10);
    index++;
}

/*********************************************************
  Function:	OnBnClickedOk
  Desc:		modify channel info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChannelInfo::OnBnClickedOk()
{
	UpdateData(TRUE);
	for (int i = 0; i < g_struDeviceInfo[m_pChanInfo->iDeviceIndex].iDeviceChanNum; i++)
	{
		if (i == m_pChanInfo->iChanIndex)
		{
			continue;
		}

		if (0 == strcmp(g_struDeviceInfo[m_pChanInfo->iDeviceIndex].pStruChanInfo[i].chChanName,m_csChanName))
		{
			char szLan[1024] = {0};
			g_StringLanType(szLan, "该通道名称已存在!", "this channel name is existed!");
			AfxMessageBox(szLan);
			return;
		}
	}

	DWORD dwTemp = m_comboProtocol.GetCurSel();
// 	if(dwTemp >= 4)
// 	{
// 		dwTemp += 3;
// 	}

	dwTemp |=(m_comboTransportType.GetCurSel()<< 31);

	if (strcmp(m_pChanInfo->chChanName,m_csChanName) != 0 || m_pChanInfo->dwProtocol != dwTemp || m_pChanInfo->dwProtocol!=m_cmPreviewMode.GetCurSel())
	{
		m_bChanged = TRUE;
	}

	sprintf(m_pChanInfo->chChanName,"%s",m_csChanName.GetBuffer(0));
	m_pChanInfo->dwProtocol = dwTemp;
	m_pChanInfo->dwPreviewMode = m_cmPreviewMode.GetCurSel();
	m_pChanInfo->nPreviewProtocolType = m_cmPreviewProtocolType.GetCurSel();
    m_pChanInfo->nVideoCodingType = m_comVideoCodingType.GetCurSel();
    m_pChanInfo->dwStreamType = m_comboTransportType.GetItemData(m_comboTransportType.GetCurSel());
    m_pChanInfo->dwLinkMode = m_comboProtocol.GetCurSel();
    m_pChanInfo->nPreviewProtocolType = m_pChanInfo->nPreviewProtocolType;
    m_pChanInfo->dwPreviewMode = m_pChanInfo->dwPreviewMode;

	if (m_comboPassbackRecord.GetCurSel() < 0)
    {
        m_pChanInfo->bPassbackRecord = FALSE;
    }
    else
    {
        m_pChanInfo->bPassbackRecord = m_comboPassbackRecord.GetCurSel();
    }
    m_pChanInfo->nPreviewProtocolType = m_cmPreviewProtocolType.GetCurSel();
	OnOK();
}

/*********************************************************
  Function:	OnBnClickedCancel
  Desc:	    cancel channel info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChannelInfo::OnBnClickedCancel()
{
	OnCancel();
}

void CDlgChannelInfo::OnUpdateMenuChannelInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
