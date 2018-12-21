// DlgCertInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCertInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCertInfo dialog


CDlgCertInfo::CDlgCertInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCertInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCertInfo)
	m_wCertFunc = 0;
	m_dwKeyAlgorithm = 0;
	m_dwKeyLen = 0;
	m_strCertPassword = _T("");
	m_wCertType = 0;
	m_dwValidDays = 0;
	m_dwCertVersion = 0;
	m_strCountry = _T("");
	m_strEmail = _T("");
 	m_byCertFileType = 0;
	m_strLocality = _T("");
	m_strState = _T("");
	m_strOrganization = _T("");
	m_strUnit = _T("");
	m_strCommonName = _T("");
	m_strCertFilePath = _T("");
	m_strStatus = _T("");
	m_strUploadStatus = _T("");
	m_tmrBeginDate = 0;
	m_tmrBeginTime = 0;
	m_tmrEndDate = 0;
	m_tmrEndTime = 0;
	m_dwSelfSignAlgorithm = 0;
	m_strSelfSignCommonName = _T("");
	m_strSelfSignCountry = _T("");
	m_strSelfSignEmail = _T("");
	m_strSelfSignLocality = _T("");
	m_strSelfSignOrganization = _T("");
	m_strSelfSignSN = _T("");
	m_strSelfSignState = _T("");
	m_strSelfSignUnit = _T("");
	//}}AFX_DATA_INIT
	m_lDownloadHandle = -1;
	m_lUploadHandle = -1;
	m_timerHandle = -1;
}


void CDlgCertInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCertInfo)
	DDX_Text(pDX, IDC_EDIT_CERT_FUNC, m_wCertFunc);
	DDX_Text(pDX, IDC_EDIT_CERT_KEY_ALGORITHM, m_dwKeyAlgorithm);
	DDX_Text(pDX, IDC_EDIT_CERT_KEY_LEN, m_dwKeyLen);
	DDX_Text(pDX, IDC_EDIT_CERT_PASSWD, m_strCertPassword);
	DDX_Text(pDX, IDC_EDIT_CERT_TYPE, m_wCertType);
	DDX_Text(pDX, IDC_EDIT_CERT_VALID_DAYS, m_dwValidDays);
	DDX_Text(pDX, IDC_EDIT_CERT_VERSION, m_dwCertVersion);
	DDX_Text(pDX, IDC_EDIT_COUNTRY, m_strCountry);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_strEmail);
	DDX_Text(pDX, IDC_EDIT_FILE_TYPE, m_byCertFileType);
	DDX_Text(pDX, IDC_EDIT_LOCALITY, m_strLocality);
	DDX_Text(pDX, IDC_EDIT_STATE, m_strState);
	DDX_Text(pDX, IDC_EDIT_ORGANIZATION, m_strOrganization);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_strUnit);
	DDX_Text(pDX, IDC_EDIT_COMMON_NAME, m_strCommonName);
	DDX_Text(pDX, IDC_EDIT_CERT_FILE_PATH, m_strCertFilePath);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_STATIC_UPLOAD_STATUS, m_strUploadStatus);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN_DATE, m_tmrBeginDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN_TIME, m_tmrBeginTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_DATE, m_tmrEndDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_TIME, m_tmrEndTime);
	DDX_Text(pDX, IDC_EDIT_CERT_SIGN_ALGORITHM, m_dwSelfSignAlgorithm);
	DDX_Text(pDX, IDC_EDIT_COMMON_NAME_SELF_SIGN, m_strSelfSignCommonName);
	DDX_Text(pDX, IDC_EDIT_COUNTRY_SELF_SIGN, m_strSelfSignCountry);
	DDX_Text(pDX, IDC_EDIT_EMAIL_SELF_SIGN, m_strSelfSignEmail);
	DDX_Text(pDX, IDC_EDIT_LOCALITY_SELF_SIGN, m_strSelfSignLocality);
	DDX_Text(pDX, IDC_EDIT_ORGANIZATION_SELF_SIGN, m_strSelfSignOrganization);
	DDX_Text(pDX, IDC_EDIT_SN_SELF_SIGN, m_strSelfSignSN);
	DDX_Text(pDX, IDC_EDIT_STATE_SELF_SIGN, m_strSelfSignState);
	DDX_Text(pDX, IDC_EDIT_UNIT_SELF_SIGN, m_strSelfSignUnit);
	DDX_Control(pDX, IDC_COMBO_CERT_REQUEST, m_comboCertRequest);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCertInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgCertInfo)
 	ON_BN_CLICKED(IDC_BUTTON_CERT_CREATE, OnButtonCertCreate)
	ON_BN_CLICKED(IDC_BUTTON_CERT_DEL, OnButtonCertDel)
	ON_BN_CLICKED(IDC_BUTTON_CERT_GET, OnButtonCertGet)
	ON_BN_CLICKED(IDC_BUTTON_CERT_UPLOAD, OnButtonCertUpload)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_CERT_FILE, OnButtonBrowseCertFile)
	ON_BN_CLICKED(IDC_BUTTON_CERT_DOWNLOAD, OnButtonCertDownload)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCertInfo message handlers

BOOL CDlgCertInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCertInfo::OnButtonCertCreate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	NET_DVR_CERT_INFO struCertInfo;
	memset(&struCertInfo, 0, sizeof(NET_DVR_CERT_INFO));

	struCertInfo.dwSize = sizeof(NET_DVR_CERT_INFO);
	struCertInfo.struCertParam.wCertFunc = m_wCertFunc;
	struCertInfo.struCertParam.wCertType = m_wCertType;
	struCertInfo.struCertParam.byFileType = m_byCertFileType;

	struCertInfo.struCertParam.dwSize = sizeof(NET_DVR_CERT_PARAM);
	struCertInfo.byVersion = m_dwCertVersion;
	struCertInfo.dwValidDays = m_dwValidDays;
	struCertInfo.byKeyAlgorithm = m_dwKeyAlgorithm;
	struCertInfo.byKeyLen = m_dwKeyLen;
	strcpy((char*)struCertInfo.byPasswd, m_strCertPassword);

	strcpy((char*)struCertInfo.struCertName.byCountry, m_strCountry);
	strcpy((char*)struCertInfo.struCertName.byState, m_strState);
	strcpy((char*)struCertInfo.struCertName.byLocality, m_strLocality);
	strcpy((char*)struCertInfo.struCertName.byOrganization, m_strOrganization);
	strcpy((char*)struCertInfo.struCertName.byUnit, m_strUnit);
	strcpy((char*)struCertInfo.struCertName.byCommonName, m_strCommonName);
	strcpy((char*)struCertInfo.struCertName.byEmail, m_strEmail);
    
    if (!NET_DVR_RemoteControl(m_lUserID,NET_DVR_CREATE_CERT,&struCertInfo,sizeof(struCertInfo)))//
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CREATE_CERT");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_CREATE_CERT failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
    }
    else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CREATE_CERT");
	}


}

void CDlgCertInfo::OnButtonCertDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	NET_DVR_CERT_PARAM struCertParam;
	memset(&struCertParam, 0, sizeof(NET_DVR_CERT_PARAM));
	
	struCertParam.dwSize = sizeof(NET_DVR_CERT_PARAM);
	struCertParam.wCertFunc = m_wCertFunc;
	struCertParam.wCertType = m_wCertType;
	struCertParam.byFileType = m_byCertFileType;
	
    DWORD dwReturned = 0;
    if (!NET_DVR_RemoteControl(m_lUserID,NET_DVR_DELETE_CERT,&struCertParam,sizeof(struCertParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DELETE_CERT");
        AfxMessageBox("NET_DVR_DELETE_CERT failed");
    }
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DELETE_CERT");
	}
}

void CDlgCertInfo::OnButtonCertGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	NET_DVR_CERT_PARAM struCertParam;
	memset(&struCertParam, 0, sizeof(NET_DVR_CERT_PARAM));

	NET_DVR_CERT_INFO struCertInfo;
	memset(&struCertInfo, 0, sizeof(NET_DVR_CERT_INFO));
	
	struCertParam.dwSize = sizeof(NET_DVR_CERT_PARAM);
	struCertParam.wCertFunc = m_wCertFunc;
	struCertParam.wCertType = m_wCertType;
	struCertParam.byFileType = m_byCertFileType;
	

    DWORD dwReturn = 0;
    DWORD dwStatus = 0;

    if (!NET_DVR_GetDeviceConfig(m_lUserID,NET_DVR_GET_CERT,0,&struCertParam,sizeof(struCertParam),&dwStatus,&struCertInfo,\
                                sizeof(NET_DVR_CERT_INFO)))
    {
        unsigned int uiError = NET_DVR_GetLastError();
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceConfig");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_GetDeviceConfig failed!,command [NET_DVR_GET_CERT],err[%d]",uiError);
        AfxMessageBox(szLan);
        return ;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceConfig");
	}

  


	m_wCertFunc = struCertInfo.struCertParam.wCertFunc;
	m_wCertType = struCertInfo.struCertParam.wCertType;
	m_byCertFileType = struCertInfo.struCertParam.byFileType;
	
	m_dwCertVersion = struCertInfo.byVersion;
	m_dwValidDays = struCertInfo.dwValidDays;
	m_dwKeyAlgorithm = struCertInfo.byKeyAlgorithm;
	m_dwKeyLen = struCertInfo.byKeyLen;
	m_strCertPassword.Format("%s", struCertInfo.byPasswd);

	m_strCountry.Format("%s", struCertInfo.struCertName.byCountry);
	m_strState.Format("%s", struCertInfo.struCertName.byState);
	m_strLocality.Format("%s", struCertInfo.struCertName.byLocality);
	m_strOrganization.Format("%s", struCertInfo.struCertName.byOrganization);
	m_strUnit.Format("%s", struCertInfo.struCertName.byUnit);
	m_strCommonName.Format("%s", struCertInfo.struCertName.byCommonName);
	m_strEmail.Format("%s", struCertInfo.struCertName.byEmail);

	m_strSelfSignCountry.Format("%s", struCertInfo.struIssuerName.byCountry);
	m_strSelfSignState.Format("%s", struCertInfo.struIssuerName.byState);
	m_strSelfSignLocality.Format("%s", struCertInfo.struIssuerName.byLocality);
	m_strSelfSignOrganization.Format("%s", struCertInfo.struIssuerName.byOrganization);
	m_strSelfSignUnit.Format("%s", struCertInfo.struIssuerName.byUnit);
	m_strSelfSignCommonName.Format("%s", struCertInfo.struIssuerName.byCommonName);
	m_strSelfSignEmail.Format("%s", struCertInfo.struIssuerName.byEmail);

	m_dwSelfSignAlgorithm = struCertInfo.bySignatureAlgorithm;
	m_strSelfSignSN.Format("%s", struCertInfo.serialNumber);

	if(0 == struCertInfo.struBeginTime.wYear || 0 == struCertInfo.struEndTime.wYear)
	{
		UpdateData(FALSE);
		return;
	}


	CTime timeBeginTmp(struCertInfo.struBeginTime.wYear, struCertInfo.struBeginTime.byMonth, struCertInfo.struBeginTime.byDay,
		struCertInfo.struBeginTime.byHour, struCertInfo.struBeginTime.byMinute, struCertInfo.struBeginTime.bySecond);

	CTime timeEndTmp(struCertInfo.struEndTime.wYear, struCertInfo.struEndTime.byMonth, struCertInfo.struEndTime.byDay,
		struCertInfo.struEndTime.byHour, struCertInfo.struEndTime.byMinute, struCertInfo.struEndTime.bySecond);

	m_tmrBeginDate = timeBeginTmp;
	m_tmrBeginTime = timeBeginTmp;

	m_tmrEndDate = timeEndTmp;
	m_tmrEndTime = timeEndTmp;


	UpdateData(FALSE);

}

void CDlgCertInfo::OnButtonBrowseCertFile() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[] = "All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		m_strCertFilePath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgCertInfo::OnButtonCertUpload() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szFileName[MAX_PATH];
	strcpy(szFileName, m_strCertFilePath);
	CFile cFile;
	char szLan[128] = {0};
	if (!cFile.Open(szFileName, NULL))
	{
		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
		AfxMessageBox(szLan);
		return;
	}
	DWORD dwFileSize = (DWORD)cFile.GetLength();
	if (dwFileSize == 0)
	{
		g_StringLanType(szLan, "证书文件为空", "Cert file is empty");
		AfxMessageBox(szLan);
	}
	cFile.Close();


	NET_DVR_CERT_PARAM struCertParam;
	memset(&struCertParam, 0, sizeof(NET_DVR_CERT_PARAM));
	
	struCertParam.dwSize = sizeof(NET_DVR_CERT_PARAM);
	struCertParam.wCertFunc = m_wCertFunc;
	struCertParam.wCertType = m_wCertType;
	struCertParam.byFileType = m_byCertFileType;
 
	m_lUploadHandle = NET_DVR_UploadFile(m_lUserID, UPLOAD_CERT_FILE, &struCertParam, sizeof(NET_DVR_CERT_PARAM), szFileName);
	if (-1 == m_lUploadHandle)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile");
		AfxMessageBox("NET_DVR_UploadFile failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile");
	    m_timerHandle =	SetTimer(UPLOAD_TIMER, 50, NULL);
		//由于证书文件只有几KB，很小，故短暂sleep，就能上传完毕
 		Sleep(500);
// 		NET_DVR_UploadClose(lHandle);
	}


}



void CDlgCertInfo::OnButtonCertDownload() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char cFilename[256] = {0};
	CString sTemp = "c:\\Certifacate";
	CTime time = CTime::GetCurrentTime();	
	DWORD dwRet = GetFileAttributes(sTemp);
	if ((dwRet == -1) || !(dwRet & FILE_ATTRIBUTE_DIRECTORY))
	{
		CreateDirectory(sTemp, NULL);
	}

	sprintf(cFilename, "%s\\%s_%4d%02d%02d_%02d%02d%02d.cert", \
		sTemp, g_struDeviceInfo[m_iDevIndex].chDeviceIPInFileName, \
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

	NET_DVR_CERT_PARAM struCertParam;
	memset(&struCertParam, 0, sizeof(NET_DVR_CERT_PARAM));
	
	struCertParam.dwSize = sizeof(NET_DVR_CERT_PARAM);
	struCertParam.wCertFunc = m_wCertFunc;
	struCertParam.wCertType = m_wCertType;
	struCertParam.byFileType = m_byCertFileType;

	m_lDownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_CERT, &struCertParam, sizeof(struCertParam), cFilename);
	if (m_lDownloadHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload[%s]", cFilename);
		m_timerHandle = SetTimer(DOWNLOAD_TIMER, 50, NULL);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload[%s]", cFilename);
		char szLan[128] = {0};
		g_StringLanType(szLan, "证书下载失败", "Certificate download failed");
		AfxMessageBox(szLan);
	}

}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgCertInfo::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgCertInfo::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	char szLan[128] = {0};
	if (nIDEvent == DOWNLOAD_TIMER)
	{
		DWORD dwProgress = 0;
		DWORD dwState = 0;
	    dwState = NET_DVR_GetDownloadState(m_lDownloadHandle, &dwProgress);
		 
		if (dwState == 1)
		{
			g_StringLanType(szLan, "下载成功", "Download successfully");
			m_strStatus.Format(szLan);
		}
		else if (dwState == 2)
		{
			g_StringLanType(szLan, "正在下载,已下载:%d", "Is Downloading,progress:%d");
			m_strStatus.Format(szLan, dwProgress);
		}
		else if (dwState == 3)
		{
			g_StringLanType(szLan, "下载失败", "Download failed");
			m_strStatus.Format(szLan);
		}
		else if (dwState == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_strStatus.Format(szLan);
			if (100 == dwProgress )
			{
				KillTimer(m_timerHandle);
				g_StringLanType(szLan, "下载成功", "Download successfully");
				m_strStatus.Format(szLan);
			}

		}		
		if (dwState != 2)
		{        
			KillTimer(DOWNLOAD_TIMER);
			NET_DVR_StopDownload(m_lDownloadHandle);
		}
	}
	else if (nIDEvent == UPLOAD_TIMER)
	{
		DWORD dwProgress = 0;
		int state = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);
		
		if (state == 1)
		{
			g_StringLanType(szLan, "上传成功", "Upload successfully");
			m_strUploadStatus.Format(szLan);
		}
		else if (state == 2)
		{
			g_StringLanType(szLan, "正在上传,已上传:%d", "Is uploading,progress:%d");
			m_strUploadStatus.Format(szLan, dwProgress);
		}
		else if (state == 3)
		{
			g_StringLanType(szLan, "上传失败", "Upload failed");
			m_strUploadStatus.Format(szLan);
		}
		else if (state == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_strUploadStatus.Format(szLan);
		}
		
// 		g_StringLanType(szLan, "上传状态%d", "Upload successfully");
// 		m_strUploadStatus.Format(szLan,state);
		if (state != 2)
		{        
			KillTimer(UPLOAD_TIMER);
			NET_DVR_UploadClose(m_lUploadHandle);
		}
	}
	
	
	UpdateData(FALSE);

	CDialog::OnTimer(nIDEvent);
}
