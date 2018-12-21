// DlgUploadLogo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgUploadLogo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgUploadLogo dialog


CDlgUploadLogo::CDlgUploadLogo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUploadLogo::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgUploadLogo)
	m_strLogodir = _T("");
	m_dwXcoordinate = 0;
	m_dwYcoordinate = 0;
	m_bFlush = FALSE;
	m_bTranslucent = FALSE;
	m_dwHeight = 0;
	m_dwWidth = 0;
	m_bChkEnableOverlay = FALSE;
	//}}AFX_DATA_INIT
    m_iChannelNumber = 0; 
    m_lStartChan = 0; 
}


void CDlgUploadLogo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgUploadLogo)
	DDX_Control(pDX, IDC_COMBODECCHAN, m_DecChanCtrl);
	DDX_Text(pDX, IDC_LOGODIR, m_strLogodir);
	DDX_Text(pDX, IDC_XCOORDINATE, m_dwXcoordinate);
	DDX_Text(pDX, IDC_YCOORDINATE, m_dwYcoordinate);
	DDX_Check(pDX, IDC_FLUSH, m_bFlush);
	DDX_Check(pDX, IDC_TRANSLUCENT, m_bTranslucent);
	DDX_Text(pDX, IDC_EDIT_PIC_HEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDIT_PIC_WIDTH, m_dwWidth);
	DDX_Check(pDX, IDC_CHK_ENABLE_OVERLAY, m_bChkEnableOverlay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUploadLogo, CDialog)
	//{{AFX_MSG_MAP(DlgUploadLogo)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_UPLOADLOGOBTN, OnUploadlogobtn)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_SHOWLOGO, OnShowlogo)
	ON_BN_CLICKED(IDC_HIDELOGO, OnHidelogo)
	ON_BN_CLICKED(IDC_BTN_GET_LOGO_OVERLAYCFG, OnBtnGetLogoOverlaycfg)
	ON_BN_CLICKED(IDC_BTN_SET_LOGO_OVERLAYCFG, OnBtnSetLogoOverlaycfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgUploadLogo message handlers

void CDlgUploadLogo::OnBrowse() 
{
	// TODO: Add your control notification handler code here
//     static char szFilter[]="All File(*.bmp*)|*.bmp*||";
//     CFileDialog dlg(TRUE,"*.bmp*","a.bmp",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
//         szFilter);
	static char szFilter[]="All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
    if (dlg.DoModal()==IDOK)
    {
        m_strLogodir = dlg.GetPathName();
        UpdateData(FALSE);
    }	
}

void CDlgUploadLogo::OnUploadlogobtn() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    CFile file;
    if (!file.Open(m_strLogodir, CFile::shareDenyNone))
    {
        return;
        file.Close();
    }    
    
    file.Seek(0, CFile::begin);
    DWORD dwFileSize = (DWORD)(file.GetLength());
    if (dwFileSize == 0)
    {
        file.Close();
        return;
    }

    char *pBuf = new char[dwFileSize];
    file.Read(pBuf, dwFileSize);
    file.Close();

    NET_DVR_DISP_LOGOCFG LogCfg;
    memset(&LogCfg, 0, sizeof(NET_DVR_DISP_LOGOCFG));
    LogCfg.dwCorordinateX = m_dwXcoordinate;
    LogCfg.dwCorordinateY = m_dwYcoordinate;
	LogCfg.wPicWidth = m_dwWidth;
	LogCfg.wPicHeight = m_dwHeight;
    LogCfg.byTranslucent = m_bTranslucent;
    LogCfg.byFlash = m_bFlush;
    LogCfg.dwLogoSize = dwFileSize;
    if (!NET_DVR_UploadLogo(m_lServerID, m_DecChanCtrl.GetCurSel() + m_lStartChan, &LogCfg, pBuf))
    {
        if (NULL != pBuf)
        {
            delete []pBuf;
            pBuf = NULL;
        }

        CString tmp;
        tmp = NET_DVR_GetErrorMsg();
        MessageBox(tmp);
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_UploadLogo");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_UploadLogo");
    }

    if (NULL != pBuf)
    {
        delete []pBuf;
        pBuf = NULL;
    }
    
    MessageBox("Upload logo succ");
    return;
}

void CDlgUploadLogo::OnExit() 
{
    CDialog::OnCancel();
}

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgUploadLogo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
    CString tmp;
    NET_DVR_MATRIX_ABILITY m_Ability;
    memset(&m_Ability, 0, sizeof(NET_DVR_MATRIX_ABILITY));
    if (!NET_DVR_GetDeviceAbility(m_lServerID, MATRIXDECODER_ABILITY, NULL, 0, (char*)&m_Ability, sizeof(NET_DVR_MATRIX_ABILITY)))
    {
        tmp.Format("Error code:%d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
//       return FALSE;
    }
    else
    {        
        m_lStartChan = m_Ability.byStartChan;
        m_iChannelNumber = m_Ability.byDecNums;
    }

    for (int i = 0; i < m_iChannelNumber; i++)
    {
        tmp.Format("chan%d", i + m_lStartChan);
        m_DecChanCtrl.AddString(tmp);
    }

	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    m_iCurChanIndex = g_pMainDlg->GetCurChanIndex();
    if (m_iCurChanIndex >= MIRROR_CHAN_INDEX && g_struDeviceInfo[m_iDevIndex].byMirrorChanNum > 0)//支持导播通道
    {
        m_iChannel = g_struDeviceInfo[m_iDevIndex].struMirrorChan[m_iCurChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
    }
    else
    {
        m_iChannel = g_struDeviceInfo[m_iDevIndex].pStruChanInfo[m_iCurChanIndex].iChannelNO;
    }
	OnBtnGetLogoOverlaycfg();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgUploadLogo::OnShowlogo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	if (NET_DVR_LogoSwitch(m_lServerID, m_DecChanCtrl.GetCurSel() + m_lStartChan, NET_DVR_SHOWLOGO))
	{
        MessageBox("Show Logo succ");
	}
    else
    {
        MessageBox(NET_DVR_GetErrorMsg());    
    }
}

void CDlgUploadLogo::OnHidelogo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (NET_DVR_LogoSwitch(m_lServerID, m_DecChanCtrl.GetCurSel() + m_lStartChan, NET_DVR_HIDELOGO))
    {
        MessageBox("Hide Logo succ");
    }
    else
    {
        MessageBox(NET_DVR_GetErrorMsg());    
    }
}

void CDlgUploadLogo::OnBtnGetLogoOverlaycfg() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struLogoOverlay, 0, sizeof(m_struLogoOverlay));
	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_LOGO_OVERLAYCFG, m_iChannel, &m_struLogoOverlay,
		sizeof(m_struLogoOverlay), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOGO_OVERLAYCFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOGO_OVERLAYCFG");
	}
	m_bChkEnableOverlay = m_struLogoOverlay.byEnable;
	m_dwXcoordinate = m_struLogoOverlay.dwCoordinateX;
	m_dwYcoordinate = m_struLogoOverlay.dwCoordinateY;
	m_dwWidth = m_struLogoOverlay.wPicWidth;
	m_dwHeight = m_struLogoOverlay.wPicHeight;
	UpdateData(FALSE);
}

void CDlgUploadLogo::OnBtnSetLogoOverlaycfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLogoOverlay.byEnable = m_bChkEnableOverlay;
	m_struLogoOverlay.dwCoordinateX = m_dwXcoordinate;
	m_struLogoOverlay.dwCoordinateY = m_dwYcoordinate;
	m_struLogoOverlay.wPicHeight = m_dwHeight;
	m_struLogoOverlay.wPicWidth = m_dwWidth;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_LOGO_OVERLAYCFG, m_iChannel, &m_struLogoOverlay, sizeof(m_struLogoOverlay)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOGO_OVERLAYCFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOGO_OVERLAYCFG");
	}
}
