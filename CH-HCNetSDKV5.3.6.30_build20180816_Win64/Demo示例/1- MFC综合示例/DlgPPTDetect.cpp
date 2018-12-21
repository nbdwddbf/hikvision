// DlgPPTDetect.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPPTDetect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPPTDetect dialog


CDlgPPTDetect::CDlgPPTDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPPTDetect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPPTDetect)
	m_bPartScreen = FALSE;
	m_bPPTDetect = FALSE;
	m_height = 0;
	m_levelDetect = 0;
	m_width = 0;
	m_x = 0;
	m_y = 0;
    m_dwChangePixelNum = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = -1;
	m_lLoginID = -1;
}


void CDlgPPTDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPPTDetect)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_Check(pDX, IDC_CHK_PART_SCREEN, m_bPartScreen);
	DDX_Check(pDX, IDC_CHK_PPT_DETECT, m_bPPTDetect);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_LEVEL_DETECT, m_levelDetect);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_Y, m_y);
    DDX_Text(pDX, IDC_CHANGE_PIXEL_NUM, m_dwChangePixelNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPPTDetect, CDialog)
	//{{AFX_MSG_MAP(CDlgPPTDetect)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPPTDetect message handlers

void CDlgPPTDetect::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	int iIndex = m_comboChannel.GetCurSel();
	char szLan[128];
	if (iIndex == -1)
	{
		g_StringLanType(szLan,"通道无效","channel invalied!");
		AfxMessageBox("通道无效");
		return;
	}
	int iChannel = m_comboChannel.GetItemData(iIndex);
	DWORD dwRet = 0;
	m_struPPTDetectCfg.dwSize = sizeof(m_struPPTDetectCfg);
    if (!NET_DVR_GetDVRConfig(m_lLoginID,NET_DVR_GET_PPT_DETECT_CFG,iChannel,&m_struPPTDetectCfg,sizeof(m_struPPTDetectCfg),&dwRet))
    {
        g_StringLanType(szLan,"获取PPT检测参数失败","get NET_DVR_GET_PPT_DETECT_CFG failed");
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_FAIL_T,"NET_DVR_GET_PPT_DETECT_CFG");
        
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_GET_PPT_DETECT_CFG");
    }
	m_bPartScreen = m_struPPTDetectCfg.byEnablePartScreen;
	m_bPPTDetect = m_struPPTDetectCfg.byEnablePPTDetect;
	m_levelDetect = m_struPPTDetectCfg.byPptDetLevel;
	m_width = m_struPPTDetectCfg.wWidth;
	m_height = m_struPPTDetectCfg.wHeight;
	m_x = m_struPPTDetectCfg.wX;
	m_y = m_struPPTDetectCfg.wY;
    m_dwChangePixelNum = m_struPPTDetectCfg.dwChangePixelNum;
	UpdateData(FALSE);
}

void CDlgPPTDetect::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	int iIndex = m_comboChannel.GetCurSel();
	char szLan[128];
	if (iIndex == -1)
	{
		g_StringLanType(szLan,"通道无效","channel invalied!");
		AfxMessageBox("通道无效");
		return;
	}
	int iChannel = m_comboChannel.GetItemData(iIndex);
	UpdateData(TRUE);
	m_struPPTDetectCfg.dwSize = sizeof(m_struPPTDetectCfg);
	m_struPPTDetectCfg.byEnablePartScreen = m_bPartScreen;
	m_struPPTDetectCfg.byEnablePPTDetect = m_bPPTDetect;
	m_struPPTDetectCfg.byPptDetLevel = m_levelDetect;
	m_struPPTDetectCfg.wWidth = m_width;
	m_struPPTDetectCfg.wHeight = m_height;
	m_struPPTDetectCfg.wX = m_x;
	m_struPPTDetectCfg.wY = m_y;
    m_struPPTDetectCfg.dwChangePixelNum = m_dwChangePixelNum;
	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_PPT_DETECT_CFG,iChannel,&m_struPPTDetectCfg,sizeof(m_struPPTDetectCfg)))
	{
		g_StringLanType(szLan,"设置PPT检测参数失败","get NET_DVR_SET_PPT_DETECT_CFG failed");
		sprintf(szLan,"设置PPT检测参数失败!,错误码:%d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_FAIL_T,"NET_DVR_SET_PPT_DETECT_CFG");
        
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_SET_PPT_DETECT_CFG");
    }

}

BOOL CDlgPPTDetect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comboChannel.ResetContent();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	char szLan[128] = {0};
	NET_DVR_PPT_CHANNEL_CFG struPPTChannelCfg = {0};
	memset(&struPPTChannelCfg,0,sizeof(struPPTChannelCfg));
	struPPTChannelCfg.dwSize = sizeof(NET_DVR_PPT_CHANNEL_CFG);
	int index = 0;
	DWORD dwRet = 0;
    if(NET_DVR_GetDVRConfig(m_lLoginID,NET_DVR_GET_PPT_CHANNEL,0,&struPPTChannelCfg,sizeof(struPPTChannelCfg),&dwRet))
    {
        for (int i = 0; i < MAX_PPT_CHAN; i++)
        {
            if (struPPTChannelCfg.byChan[i])
            {
                m_comboChannel.AddString(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
                m_comboChannel.SetItemData(index,g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
                index++;
            }
        }
        if (index == 0)
        {
            g_StringLanType(szLan,"无通道支持PPT检测","No channel support for PPT detection");
            AfxMessageBox(szLan);
            return FALSE;
        }
        g_StringLanType(szLan,"获取通道成功","get DVR_GET_PPT_SUPPORT_CHANNAL success");
        m_comboChannel.SetCurSel(0);
    }
    else
    {
        g_StringLanType(szLan,"获取通道失败","get NET_DVR_GET_PPT_CHANNEL failed");
        return FALSE;
    }
    
    OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
