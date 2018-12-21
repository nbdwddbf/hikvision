//DlgScreenLogoCfg1.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgScreenLogoCfgUniform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenLogoCfgUniform dialog


CDlgScreenLogoCfgUniform::CDlgScreenLogoCfgUniform(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScreenLogoCfgUniform::IDD, pParent)
, m_lUploadHandle(-1)
{
	//{{AFX_DATA_INIT(CDlgScreenLogoCfgUniform)
	m_csFilePath = _T("");
	m_byMapNum = 1;
	m_byScreenIndex = 1;
	m_wSourWidth = 1;
	m_wSourHeight = 1;
	m_csProgress = _T("");
	m_dwWallNoCtrl = 0;
	m_dwWallNoUpload = 1;
	m_csPictureName = _T("");
	m_BPictureExist = FALSE;
	m_dwLogSeq = 0;
	//}}AFX_DATA_INIT
}

CDlgScreenLogoCfgUniform::~CDlgScreenLogoCfgUniform()
{

}
void CDlgScreenLogoCfgUniform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScreenLogoCfgUniform)
	DDX_Control(pDX, IDC_PROGRESS_UPLOAD, m_progress);
	DDX_Control(pDX, IDC_COMBO_USETYPE, m_cmUseType);
	DDX_Control(pDX, IDC_COMBO_LOGOSTATUS, m_cmLogoStatus);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_csFilePath);
	DDX_Text(pDX, IDC_EDIT_MAPNUM, m_byMapNum);
	DDX_Text(pDX, IDC_EDIT_SCREENINDEX, m_byScreenIndex);
	DDX_Text(pDX, IDC_EDIT_SOURWIDTH, m_wSourWidth);
	DDX_Text(pDX, IDC_EDIT_SOURHEIGHT, m_wSourHeight);
	DDX_Text(pDX, IDC_STATIC_PROGRESS, m_csProgress);
	DDX_Text(pDX, IDC_EDIT_WALL_NO_CTRL, m_dwWallNoCtrl);
	DDX_Text(pDX, IDC_EDIT_WALL_NO_UPLOAD, m_dwWallNoUpload);
	DDX_Text(pDX, IDC_EDT_PICTURENAME, m_csPictureName);
	DDX_Check(pDX, IDC_CHK_PICTURE_EXIST, m_BPictureExist);
	DDX_Text(pDX, IDC_EDIT_LOGOSEQUENCE, m_dwLogSeq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScreenLogoCfgUniform, CDialog)
	//{{AFX_MSG_MAP(CDlgScreenLogoCfgUniform)
	ON_BN_CLICKED(IDC_BTN_BROWSEFILE, OnBtnBrowsefile)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_CTRL, OnBtnCtrl)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BUT_DELETE_PICTURE, OnButDeletePicture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenLogoCfgUniform message handlers

BOOL CDlgScreenLogoCfgUniform::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitComboBox();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_cmLogoStatus.SetCurSel(0);
	m_cmUseType.SetCurSel(0);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	return TRUE; 
}

void CDlgScreenLogoCfgUniform::InitComboBox()
{
	char szLan[128] = {0};
	m_cmUseType.ResetContent();
	g_StringLanType(szLan, "OSD", "OSD");
	m_cmUseType.AddString(szLan);
	g_StringLanType(szLan, "µ×Í¼", "BACKGROUND PICTURE");
	m_cmUseType.AddString(szLan);

	m_cmLogoStatus.ResetContent();
	g_StringLanType(szLan, "ÏÔÊ¾", "SHOW");
	m_cmLogoStatus.AddString(szLan);
	g_StringLanType(szLan, "Òþ²Ø", "HIDD");
	m_cmLogoStatus.AddString(szLan);
	UpdateData(FALSE);
}

void CDlgScreenLogoCfgUniform::OnBtnBrowsefile() 
{
	// TODO: Add your control notification handler code here
    
// 	if (m_cmUseType.GetCurSel() == -1)
// 	{
// 		MessageBox("ÇëÏÈÑ¡ÔñÍ¼Æ¬ÓÃÍ¾");
// 		return;
// 	}
    UpdateData(TRUE);     
	CFileException fileException;
	static char szFilter[]="ALL File(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	
	if (dlg.DoModal()==IDOK)
	{
		m_csFilePath = dlg.GetPathName();
		if (!m_logoFile.Open(m_csFilePath, CFile::modeRead, &fileException))
		{
			CString csStr;
			csStr.Format("File Open failed , err = %d\n", fileException);
			MessageBox(csStr);
			return;
		}
		else
		{
			//logo´óÐ¡Ð¡ÓÚ100K
			if ((m_cmUseType.GetCurSel() == 0) && (m_logoFile.GetLength() > 100*1000))
			{
				MessageBox("The logo File larger than 100K\n Please select again");
			}
			m_logoFile.Close();
		}
		GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
        UpdateData(FALSE); 
	}	
}

void CDlgScreenLogoCfgUniform::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struPicCfg, 0, sizeof(m_struPicCfg));
	m_struPicCfg.dwSize = sizeof(m_struPicCfg);
    m_struPicCfg.bySequence = m_dwLogSeq; 
	m_struPicCfg.byUseType = 1;
	m_struPicCfg.struBasemapCfg.byMapNum = m_byMapNum;
	m_struPicCfg.struBasemapCfg.byScreenIndex = m_byScreenIndex;
	m_struPicCfg.struBasemapCfg.wSourHeight = m_wSourHeight;
	m_struPicCfg.struBasemapCfg.wSourWidth = m_wSourWidth;
    m_struPicCfg.dwVideoWall = m_dwWallNoUpload << 24; 
    strcpy((char *)m_struPicCfg.sPicName, (LPCTSTR)m_csPictureName); 
//	m_struPicCfg.byWallNo = (BYTE)m_dwWallNoUpload;
    char szLan[128] = {0}; 
	m_lUploadHandle = NET_DVR_PicUpload(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_csFilePath, &m_struPicCfg);
	if (m_lUploadHandle == -1)
	{
        g_StringLanType(szLan, "ÉÏ´«Í¼Æ¬Ê§°Ü", "Failed to upload picture"); 
        sprintf(szLan, "%s , Error Code %d", szLan, NET_DVR_GetLastError()); 
		MessageBox(szLan, "Error");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PicUpload failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PicUpload succ");
        SetTimer(NULL, 100, NULL);
	}
}

void CDlgScreenLogoCfgUniform::OnBtnCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_BASEMAP_PIC_INFO struPicInfo = {0};
    struPicInfo.dwSize = sizeof(struPicInfo); 
    DWORD channelEx = m_dwLogSeq; 
    DWORD dwRet; 
    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_BASEMAP_PIC_INFO, channelEx, &struPicInfo, sizeof(NET_DVR_BASEMAP_PIC_INFO), &dwRet))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BASEMAP_PIC_INFO");
        AfxMessageBox("»ñÈ¡µ×Í¼ÐÅÏ¢Ê§°Ü");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BASEMAP_PIC_INFO");
        
        m_csPictureName.Format("%s", struPicInfo.sPicName);
        m_BPictureExist = struPicInfo.byUsed;
        UpdateData(FALSE);
	}

}

void CDlgScreenLogoCfgUniform::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgScreenLogoCfgUniform::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgScreenLogoCfgUniform::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	int iPos = 0;
	CString csStr;
	char sTemp[128] = {0};
	if(-1 == m_lUploadHandle)
	{
		Sleep(1000);
		return;
	}

	iPos = NET_DVR_GetPicUploadProgress(m_lUploadHandle);
	if (iPos <= 0)
	{
		return;
	}
	if (iPos == 100)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Upload finish!");
		if (!NET_DVR_CloseUploadHandle(m_lUploadHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CloseUploadHandle Failed");
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CloseUploadHandle succ");
			iPos = 0;
		}
	}
	//csStr.Format("NET_DVR_GetPicUploadProgress %%%d", iPos);
	m_csProgress.Format("%%%d", iPos);
	m_progress.SetPos(iPos);
#ifdef DVCS_DEMO
	if (1 == NET_DVR_GetPicUploadState(m_lUploadHandle))
	{
		if (!NET_DVR_CloseUploadHandle(m_lUploadHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CloseUploadHandle failed");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CloseUploadHandle SUCC");
		}
	}
#endif
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CDlgScreenLogoCfgUniform::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	int iPos;
	if (!NET_DVR_CloseUploadHandle(m_lUploadHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CloseUploadHandle Failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CloseUploadHandle succ");
		iPos = 0;
		m_csProgress.Format("%%%d", iPos);
		m_progress.SetPos(iPos);
	}
	UpdateData(FALSE);
}

void CDlgScreenLogoCfgUniform::OnButDeletePicture() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    if (!NET_DVR_RemoteControl(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_DELETE_PICTURE, &m_dwLogSeq, sizeof(DWORD)))
    {
        CString csError; 
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DELETE_PICTURE");
        csError.Format("É¾³ýÍ¼Æ¬Ê§°Ü, Error Code %d", NET_DVR_GetLastError());
        MessageBox(csError); 
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_DELETE_PICTURE");
        AfxMessageBox("³É¹¦É¾³ýÍ¼Æ¬");
        m_dwLogSeq = 0; 
        m_csPictureName = ""; 
        m_BPictureExist = 0; 
        UpdateData(FALSE); 
	}
}
