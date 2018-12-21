/**********************************************************
FileName:    DlgJPEGSnatchConfig.cpp
Description: jpeg capture configuration  
Date:        2008/05/29
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp    
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/29>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgJPEGSnatchConfig.h"
#include ".\dlgjpegsnatchconfig.h"


// CDlgJPEGSnatchConfig dialog
/*********************************************************
  Function:	CDlgJPEGSnatchConfig
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgJPEGSnatchConfig, CDialog)
CDlgJPEGSnatchConfig::CDlgJPEGSnatchConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJPEGSnatchConfig::IDD, pParent)
	, m_pChanInfo(NULL)
	, m_pCompresscfgAbility(NULL)
{
		m_pCompresscfgAbility = new NET_DVR_COMPRESSIONCFG_ABILITY;
		memset(m_pCompresscfgAbility, 0, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY));
}

/*********************************************************
  Function:	~CDlgJPEGSnatchConfig
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgJPEGSnatchConfig::~CDlgJPEGSnatchConfig()
{
	if (m_pChanInfo != NULL)
	{
		m_pChanInfo = NULL;
	}
	if (m_pCompresscfgAbility != NULL)
	{
		delete m_pCompresscfgAbility;
		m_pCompresscfgAbility = NULL;
	}

}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgJPEGSnatchConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgJPEGSnatchConfig)
	DDX_Control(pDX, IDC_COMBO_JPEG_RESOLUTION, m_comboJpegResolution);
	DDX_Control(pDX, IDC_COMBO_JPEG_QUALITY, m_comboJpegQuality);
        //}}AFX_DATA_MAP

}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgJPEGSnatchConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgJPEGSnatchConfig)	
	ON_BN_CLICKED(IDC_BTN_JPEG_CONFIG_EXIT, OnBnClickedBtnJpegConfigExit)
	ON_BN_CLICKED(IDC_BTN_CAPTURE, OnBtnCapture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CDlgJPEGSnatchConfig message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgJPEGSnatchConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_iDeviceIndex = m_pChanInfo->iDeviceIndex;
	int iChanIndex = m_pChanInfo->iChannelNO; //m_pChanInfo->iChanIndex + g_struDeviceInfo[m_iDeviceIndex].iStartChan;
    
    m_comboJpegResolution.ResetContent();
    m_comboJpegResolution.AddString("CIF");
    m_comboJpegResolution.SetItemData(0, 0);
    m_comboJpegResolution.AddString("QCIF");
    m_comboJpegResolution.SetItemData(1, 1);
    m_comboJpegResolution.AddString("4CIF");
    m_comboJpegResolution.SetItemData(2, 2);
    m_comboJpegResolution.SetCurSel(0);
 
    if (m_iDeviceIndex >= 0)
	{
		if (GetCompressCfgAbility(iChanIndex))
		{
			GetResolutionAbility();
		}
	}
    m_comboJpegResolution.AddString("auto");
    m_comboJpegResolution.SetItemData(m_comboJpegResolution.GetCount(), 0xff);
	m_comboJpegQuality.SetCurSel(m_pChanInfo->iPicQuality);
	m_comboJpegResolution.SetCurSel(m_pChanInfo->iPicResolution);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


/*********************************************************
  Function:	OnBnClickedBtnJpegConfigExit
  Desc:		do not configure
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgJPEGSnatchConfig::OnBnClickedBtnJpegConfigExit()
{
	if (m_pCompresscfgAbility != NULL)
	{
		delete m_pCompresscfgAbility;
		m_pCompresscfgAbility = NULL;
	}
	CDialog::OnCancel();
}

void CDlgJPEGSnatchConfig::GetResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (MAIN_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboJpegResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboJpegResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboJpegResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

BOOL CDlgJPEGSnatchConfig::GetCompressCfgAbility(DWORD dwIPChanIndex)
{
    if (!NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDeviceIndex].lLoginID, PIC_CAPTURE_ABILITY, (char*)&dwIPChanIndex, sizeof(dwIPChanIndex), (char*)m_pCompresscfgAbility, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PIC_CAPTURE_ABILITY");
        return FALSE;    
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PIC_CAPTURE_ABILITY");
        return TRUE;
    }
}


/*********************************************************
  Function:	OnBtnCapture
  Desc:		capture
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgJPEGSnatchConfig::OnBtnCapture() 
{
	UpdateData(TRUE);
	char cFilename[256] = {0};
 	CString sTemp;
	int iDeviceIndex = m_pChanInfo->iDeviceIndex;
	int iChanIndex = m_pChanInfo->iChanIndex;
 	CTime time = CTime::GetCurrentTime();
	m_pChanInfo->iPicResolution = m_comboJpegResolution.GetCurSel();
	m_pChanInfo->iPicQuality = m_comboJpegQuality.GetCurSel();
 	sTemp.Format("%s\\", g_struLocalParam.chPictureSavePath);
	DWORD dwRet = GetFileAttributes(sTemp);
	if ((dwRet == -1) || !(dwRet & FILE_ATTRIBUTE_DIRECTORY))
 	{
 		CreateDirectory(sTemp, NULL);
 	}
	NET_DVR_JPEGPARA struJpegPara;
	memset(&struJpegPara, 0, sizeof(NET_DVR_JPEGPARA));
	struJpegPara.wPicQuality = (WORD)m_comboJpegQuality.GetCurSel(); 
    m_comboJpegResolution.SetItemData(m_comboJpegResolution.GetCount() - 1, 0xff);
    struJpegPara.wPicSize = m_comboJpegResolution.GetItemData(m_comboJpegResolution.GetCurSel());
	int iChanShowNum = m_pChanInfo->iChannelNO; //iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
    sprintf(cFilename, "%s\\JPEG_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.jpg", \
 		g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, iChanShowNum,	\
 		time.GetYear(), time.GetMonth(), time.GetDay(), \
 		time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());
 	if (!g_struLocalParam.bUseCard)
 	{
		if (NET_DVR_CaptureJPEGPicture(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanShowNum, &struJpegPara, cFilename))
		{
			CString sTemp;	
			sTemp.Format("JPEG capture succ %s!",cFilename);
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CaptureJPEGPicture file[%s]", cFilename);
			AfxMessageBox(sTemp); 
			return;
		}
 		else
 		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CaptureJPEGPicture");
 			AfxMessageBox("JPEG capture failed!");
 		}
 	}
}
