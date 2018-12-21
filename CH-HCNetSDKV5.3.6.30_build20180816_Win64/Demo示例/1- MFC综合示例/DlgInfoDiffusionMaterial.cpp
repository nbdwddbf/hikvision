// DlgInfoDiffusionMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionMaterial.h"
#include "DlgInfoDiffusionClock.h"
#include "DlgInfoDiffusionClockWeather.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionMaterial dialog


CDlgInfoDiffusionMaterial::CDlgInfoDiffusionMaterial(CWnd* pParent /*=NULL*/)
: CDialog(CDlgInfoDiffusionMaterial::IDD, pParent)
, m_dwOrgNo(0)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionMaterial)
	m_szWebUrl = _T("");
	m_szStreamUrl = _T("");
	m_dwStreamPort = 0;
	m_szStreamIPAddr = _T("");
	m_szStreamHostName = _T("");
	m_szRssUrl = _T("");
	m_szPropRemarks = _T("");
	m_szPropName = _T("");
	m_dwMaterialSize = 0;
	m_szMaterialRemarks = _T("");
	m_szMaterialPath = _T("");
	m_szMaterialName = _T("");
	m_dwDownMaterialIndex = 0;
	m_szSavePath = _T("");
	m_szApproveRemarks = _T("");
	m_dwPlayDuration = 0;
	m_tmStartTime = COleDateTime::GetCurrentTime();
	m_tmStartDate = COleDateTime::GetCurrentTime();
	m_tmEndTime = COleDateTime::GetCurrentTime();
	m_tmEndDate = COleDateTime::GetCurrentTime();
	m_sUploader = _T("");
	m_dwStartPosition = 0;
	m_dwMaterialNo = 0;
	m_dwStaticMinSize = 0;
	m_dwStaticMaxSize = 0;
	m_dwMaxResults = 0;
	m_dwMaterialID = 0;
	m_sSearchID = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(&m_struMaterial, 0, sizeof(m_struMaterial));
	m_struMaterial.dwSize = sizeof(m_struMaterial);
	memset(&m_struDescription, 0, sizeof(m_struDescription));
	m_lpResult = new NET_DVR_MATERIAL_SEARCH_RESULT;
	memset(m_lpResult, 0, sizeof(*m_lpResult));
	m_iCurSelMaterial = -1;
	m_lUpdownloadHandle = -1;
	m_bUploading = FALSE;
	m_bDownloading = FALSE;
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
}


void CDlgInfoDiffusionMaterial::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionMaterial)
    DDX_Control(pDX, IDC_COMBO_MATERIAL_APPROVE_STATE, m_cmbSearchApproveState);
    DDX_Control(pDX, IDC_COMBO_MATERIAL_DYNAMIC_TYPE, m_cmbSearchDynamicType);
    DDX_Control(pDX, IDC_COMBO_MATERIAL_SHARE_PROP, m_cmbSearchShareProp);
    DDX_Control(pDX, IDC_COMBO_MATERIAL_STATIC_TYPE, m_cmbSearchStaticType);
    DDX_Control(pDX, IDC_COMBO_SEARCH_MATERIAL_TYPE, m_cmbSearchMaterialType);
    DDX_Control(pDX, IDC_LIST_MATERIAL, m_listMaterial);
    DDX_Control(pDX, IDC_COMBO_APPROVE, m_cmbApprove);
    DDX_Control(pDX, IDC_COMBO_SHARE_PROP, m_cmbShareProp);
    DDX_Control(pDX, IDC_COMBO_EDIT_SHARE_PROP, m_cmbEditShareProp);
    DDX_Control(pDX, IDC_STATIC_PROGRESS, m_statProgress);
    DDX_Control(pDX, IDC_COMBO_DYNAMIC_MATERIAL_TYPE, m_cmbDynamicMaterialType);
    DDX_Control(pDX, IDC_COMBO_MATERIAL_TYPE, m_cmbMaterialType);
    DDX_Control(pDX, IDC_COMBO_STATIC_MATERIAL_FORMAT, m_cmbStaticMaterialFormat);
    DDX_Control(pDX, IDC_COMBO_STATIC_MATERIAL_TYPE, m_cmbStaticMaterialType);
    DDX_Control(pDX, IDC_COMBO_STREAM_ADDR_TYPE, m_cmbStreamAddrType);
    DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
    DDX_Text(pDX, IDC_EDIT_WEB_URL, m_szWebUrl);
    DDX_Text(pDX, IDC_EDIT_STREAM_URL, m_szStreamUrl);
    DDX_Text(pDX, IDC_EDIT_STREAM_PORT, m_dwStreamPort);
    DDX_Text(pDX, IDC_EDIT_STREAM_IPADDR, m_szStreamIPAddr);
    DDX_Text(pDX, IDC_EDIT_STREAM_HOST_NAME, m_szStreamHostName);
    DDX_Text(pDX, IDC_EDIT_RSS_URL, m_szRssUrl);
    DDX_Text(pDX, IDC_EDIT_PROP_REMARKS, m_szPropRemarks);
    DDX_Text(pDX, IDC_EDIT_PROP_NAME, m_szPropName);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_SIZE, m_dwMaterialSize);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_REMARKS, m_szMaterialRemarks);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_PATH, m_szMaterialPath);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_NAME, m_szMaterialName);
    DDX_Text(pDX, IDC_EDIT_DOWN_MATERIAL_INDEX, m_dwDownMaterialIndex);
    DDX_Text(pDX, IDC_EDIT_SAVE_PATH, m_szSavePath);
    DDX_Text(pDX, IDC_EDIT_APPROVE_REMARKS, m_szApproveRemarks);
    DDX_Text(pDX, IDC_EDIT_PLAY_DURATION, m_dwPlayDuration);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_tmStartTime);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_tmStartDate);
    DDX_DateTimeCtrl(pDX, IDC_END_TIME, m_tmEndTime);
    DDX_DateTimeCtrl(pDX, IDC_END_DATE, m_tmEndDate);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_UPLOADER, m_sUploader);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_START_POSITION, m_dwStartPosition);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_NO, m_dwMaterialNo);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_MIN_SIZE, m_dwStaticMinSize);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_MAX_SIZE, m_dwStaticMaxSize);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_MAX_RESULTS, m_dwMaxResults);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_ID, m_dwMaterialID);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_SEARCH_ID, m_sSearchID);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_EDIT_SET_TYPE, m_comOperatorType);
    DDX_Text(pDX, IDC_EDIT_ORG_NO, m_dwOrgNo);
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionMaterial, CDialog)
//{{AFX_MSG_MAP(CDlgInfoDiffusionMaterial)
ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
ON_BN_CLICKED(IDC_BTN_MATERIAL_DEL, OnBtnMaterialDel)
ON_BN_CLICKED(IDC_BTN_MATERIAL_GET, OnBtnMaterialGet)
ON_BN_CLICKED(IDC_BTN_MATERIAL_SET, OnBtnMaterialSet)
ON_BN_CLICKED(IDC_BTN_MATERIAL_CHOOSE, OnBtnMaterialChoose)
ON_BN_CLICKED(IDC_BTN_MATERIAL_DOWNLOAD, OnBtnMaterialDownload)
ON_BN_CLICKED(IDC_BTN_MATERIAL_SAVE, OnBtnMaterialSave)
ON_BN_CLICKED(IDC_BTN_MATERIAL_UPLOAD, OnBtnMaterialUpload)
ON_CBN_SELCHANGE(IDC_COMBO_DYNAMIC_MATERIAL_TYPE, OnSelchangeComboDynamicMaterialType)
ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL_TYPE, OnSelchangeComboMaterialType)
ON_CBN_SELCHANGE(IDC_COMBO_STATIC_MATERIAL_TYPE, OnSelchangeComboStaticMaterialType)
ON_CBN_SELCHANGE(IDC_COMBO_STREAM_ADDR_TYPE, OnSelchangeComboStreamAddrType)
ON_WM_TIMER()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_BTN_MATERIAL_SEARCH, OnBtnMaterialSearch)
ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_MATERIAL_TYPE, OnSelchangeComboSearchMaterialType)
ON_NOTIFY(NM_CLICK, IDC_LIST_MATERIAL, OnClickListMaterial)
//}}AFX_MSG_MAP
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MATERIAL, &CDlgInfoDiffusionMaterial::OnLvnItemchangedListMaterial)
ON_BN_CLICKED(IDC_BTN_BATCH_DEL, &CDlgInfoDiffusionMaterial::OnBnClickedBtnBatchDel)
ON_BN_CLICKED(IDC_BTN_BATCH_SET, &CDlgInfoDiffusionMaterial::OnBnClickedBtnBatchSet)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionMaterial message handlers

void CDlgInfoDiffusionMaterial::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strCommand;
	strCommand.Format("DELETE /ISAPI/Publish/MaterialMgr/material/%d\r\n", m_dwMaterialNo);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/MaterialMgr/material/%d\r\n", m_dwMaterialNo);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
	struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
	struOutputParam.dwOutBufferSize = MAX_LEN_XML;
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	memset(&m_struMaterial, 0, sizeof(m_struMaterial));
	m_struMaterial.dwSize = sizeof(m_struMaterial);
	ConvertMaterialParamsXmlToStru(m_pOutputXmlBuffer, &m_struMaterial);
	
	m_szPropName = m_struMaterial.szMaterialName;
	m_szPropRemarks = m_struMaterial.szMaterialRemarks;
	m_cmbEditShareProp.SetCurSel(m_cmbEditShareProp.FindString(-1, m_struMaterial.szSharePropery));
	m_cmbApprove.SetCurSel(m_cmbApprove.FindString(-1, m_struMaterial.szApprove));
	m_szApproveRemarks = m_struMaterial.szApproveRemarks;
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struMaterial.dwSize = sizeof(m_struMaterial);
	strcpy(m_struMaterial.szMaterialName, m_szPropName);
	strcpy(m_struMaterial.szMaterialRemarks, m_szPropRemarks);
	int nSel = m_cmbEditShareProp.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbEditShareProp.GetLBText(nSel, m_struMaterial.szSharePropery);
	nSel = m_cmbApprove.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbApprove.GetLBText(nSel, m_struMaterial.szApprove);
	strcpy(m_struMaterial.szApproveRemarks, m_szApproveRemarks);
	
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertMaterialParamsStruToXml(&m_struMaterial, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/MaterialMgr/material/%d\r\n", m_dwMaterialNo);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	delete[] pInputBuff;
	pInputBuff = NULL;
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialChoose() 
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	int nCurSel = m_cmbStaticMaterialType.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strStaticMaterialType;
	m_cmbStaticMaterialType.GetLBText(nCurSel, strStaticMaterialType);
	nCurSel = m_cmbStaticMaterialFormat.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strStaticMaterialFormat;
	m_cmbStaticMaterialFormat.GetLBText(nCurSel, strStaticMaterialFormat);
	if (0 == strcmp(strStaticMaterialType, "picture")) //图片
	{
		strFilter.Format("Picture(*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T(")|*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T("|All Files(*.*)|*.*||");
	}
	else if (0 == strcmp(strStaticMaterialType, "flash")) //动画
	{
		strFilter.Format("Flash(*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T(")|*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T("|All Files(*.*)|*.*||");
	}
	else if (0 == strcmp(strStaticMaterialType, "audio")) //音频
	{
		strFilter.Format("Audio(*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T(")|*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T("|All Files(*.*)|*.*||");
	}
	else if (0 == strcmp(strStaticMaterialType, "video")) //视屏
	{
		strFilter.Format("Video(*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T(")|*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T("|All Files(*.*)|*.*||");
	}
	else if (0 == strcmp(strStaticMaterialType, "document")) //文件
	{
		strFilter.Format("Document(*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T(")|*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T("|All Files(*.*)|*.*||");
	}
	else if (0 == strcmp(strStaticMaterialType, "template")) //模板
	{
		strFilter.Format("Template(*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T(")|*.");
		strFilter += strStaticMaterialFormat;
		strFilter += _T("|All Files(*.*)|*.*||");
	}
	CFileDialog fileChose(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fileChose.DoModal() != IDOK)
	{
		return;
	}
	m_szMaterialPath = fileChose.GetPathName();
	CFile file;
	if (!file.Open(m_szMaterialPath, CFile::modeRead))
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "打开文件失败", "Open file failed.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_dwMaterialSize = file.GetLength();
	file.Close();
	CString strSize;
	strSize.Format("%u", m_dwMaterialSize);
	GetDlgItem(IDC_EDIT_MATERIAL_SIZE)->SetWindowText(strSize);
	GetDlgItem(IDC_EDIT_MATERIAL_PATH)->SetWindowText(m_szMaterialPath);
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialDownload() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_bUploading || m_bDownloading)
	{
		return;
	}
	
	m_lUpdownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_PUBLISH_MATERIAL, &m_dwDownMaterialIndex, sizeof(m_dwDownMaterialIndex), m_szSavePath.GetBuffer(0));
	if (m_lUpdownloadHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_PUBLISH_MATERIAL");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_PUBLISH_MATERIAL");
	
	m_bDownloading = TRUE;
	m_ctrlProgress.SetPos(0);
	m_statProgress.SetWindowText(_T("0%"));
	SetTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS, 100, NULL);
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialSave() 
{
	// TODO: Add your control notification handler code here
	CString strFilter = _T("All Files(*.*)|*.*||");
	CFileDialog fileChose(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fileChose.DoModal() != IDOK)
	{
		return;
	}
	m_szSavePath = fileChose.GetPathName();
	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(m_szSavePath);
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialUpload() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_bUploading || m_bDownloading)
	{
		return;
	}
	
	//memset(&m_struMaterial, 0, sizeof(m_struMaterial));
	m_struMaterial.dwSize = sizeof(m_struMaterial);
	int nCurSel = m_cmbMaterialType.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strMaterialType;
	m_cmbMaterialType.GetLBText(nCurSel, strMaterialType);
	memcpy(m_struMaterial.szMaterialType, strMaterialType, strlen(strMaterialType));
	memcpy(m_struMaterial.szMaterialName, m_szMaterialName, strlen(m_szMaterialName));
	memcpy(m_struMaterial.szMaterialRemarks, m_szMaterialRemarks, strlen(m_szMaterialRemarks));
	strcpy(m_struMaterial.szApprove, "notApprove");
	strcpy(m_struMaterial.szApproveRemarks, "none");
    m_struMaterial.dwOrgNo = m_dwOrgNo;
	nCurSel = m_cmbShareProp.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbShareProp.GetLBText(nCurSel, m_struMaterial.szSharePropery);
	memcpy(m_struMaterial.szUploadUser, g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, sizeof(m_struMaterial.szUploadUser));
	CTime time(time(NULL));
	sprintf(m_struMaterial.szUploadTime, "%d%02d%02dT%02d%02d%02d+08",
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	
	if (0 == strcmp(strMaterialType, "static")) //静态素材
	{
		nCurSel = m_cmbStaticMaterialType.GetCurSel();
		if (nCurSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "素材管理", "Material Management");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		CString strStaticMaterialType;
		m_cmbStaticMaterialType.GetLBText(nCurSel, strStaticMaterialType);
		memcpy(m_struMaterial.struStaticMaterial.szStaticMaterialType, strStaticMaterialType, strlen(strStaticMaterialType));
		if(0 != strcmp(strStaticMaterialType,"clock") && 0 != strcmp(strStaticMaterialType,"weather") )
		{			
			nCurSel = m_cmbStaticMaterialFormat.GetCurSel();
			if (nCurSel == CB_ERR)
			{
				char szLan1[512] = {0};
				char szLan2[512] = {0};
				g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
				g_StringLanType(szLan2, "素材管理", "Material Management");
				MessageBox(szLan1, szLan2, MB_ICONWARNING);
				return;
			}
			CString strStaticMaterialFormat;
			m_cmbStaticMaterialFormat.GetLBText(nCurSel, strStaticMaterialFormat);
			memcpy(m_struMaterial.struStaticMaterial.szStaticMaterialFormat, strStaticMaterialFormat, strlen(strStaticMaterialFormat));
		}
		m_struMaterial.struStaticMaterial.dwFileSize = m_dwMaterialSize;
		m_struMaterial.struStaticMaterial.dwDuration = m_dwPlayDuration;
		
		char* pInputBuff = NULL;
		DWORD dwInputSize = 0;
		ConvertMaterialParamsStruToXml(&m_struMaterial, &pInputBuff, dwInputSize);
		char szOutputBuff[1024] = {0};
		
		if(0 == strcmp(strStaticMaterialType,"clock") || 0 == strcmp(strStaticMaterialType,"weather") )
		{
			CString strCommand = _T("POST /ISAPI/Publish/MaterialMgr/material\r\n");
			NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
			struInputParam.dwSize = sizeof(struInputParam);
			struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
			struInputParam.dwRequestUrlLen = strCommand.GetLength();
			struInputParam.lpInBuffer = pInputBuff;
			struInputParam.dwInBufferSize = dwInputSize;
			
			char szStatusBuff[1024] = {0};
			NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
			struOutputParam.dwSize = sizeof(struOutputParam);
			struOutputParam.lpStatusBuffer = szStatusBuff;
			struOutputParam.dwStatusSize = sizeof(szStatusBuff);
			
			if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
				delete[] pInputBuff;
				pInputBuff = NULL;
				return;
			}
		}
		else
		{			
			m_lUpdownloadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_PUBLISH_MATERIAL, pInputBuff, dwInputSize, m_szMaterialPath.GetBuffer(0), szOutputBuff, sizeof(szOutputBuff));
			if (m_lUpdownloadHandle == -1)
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_MATERIAL");
				delete[] pInputBuff;
				pInputBuff = NULL;
				return;
			}
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_MATERIAL");
			m_dwMaterialID = GetResponseStatusID(szOutputBuff);
			delete[] pInputBuff;
			pInputBuff = NULL;
			
			m_bUploading = TRUE;
			m_ctrlProgress.SetPos(0);
			m_statProgress.SetWindowText(_T("0%"));
			SetTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS, 100, NULL);
		}
	}
	else if (0 == strcmp(strMaterialType, "dynamic")) //动态素材
	{
		nCurSel = m_cmbDynamicMaterialType.GetCurSel();
		if (nCurSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "素材管理", "Material Management");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		CString strDynamicMaterialType;
		m_cmbDynamicMaterialType.GetLBText(nCurSel, strDynamicMaterialType);
		memcpy(m_struMaterial.struDynamicMaterial.szDynamicMaterialType, strDynamicMaterialType, strlen(strDynamicMaterialType));
		if (0 == strcmp(strDynamicMaterialType, "streamMedia"))
		{
			nCurSel = m_cmbStreamAddrType.GetCurSel();
			if (nCurSel == CB_ERR)
			{
				char szLan1[512] = {0};
				char szLan2[512] = {0};
				g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
				g_StringLanType(szLan2, "素材管理", "Material Management");
				MessageBox(szLan1, szLan2, MB_ICONWARNING);
				return;
			}
			CString strAddrType;
			m_cmbStreamAddrType.GetLBText(nCurSel, strAddrType);
			memcpy(m_struMaterial.struDynamicMaterial.struStreamMedia.struAddress.szAddressType, strAddrType, strlen(strAddrType));
			if (0 == strcmp(strAddrType, "hostname"))
			{
				memcpy(m_struMaterial.struDynamicMaterial.struStreamMedia.struAddress.szHostName, m_szStreamHostName, strlen(m_szStreamHostName));
			}
			else if (0 == strcmp(strAddrType, "ipaddress"))
			{
				memcpy(m_struMaterial.struDynamicMaterial.struStreamMedia.struAddress.struIPAddr.szIpV4, m_szStreamIPAddr, strlen(m_szStreamIPAddr));
			}
			m_struMaterial.struDynamicMaterial.struStreamMedia.struAddress.dwPortNo = m_dwStreamPort;
			memcpy(m_struMaterial.struDynamicMaterial.struStreamMedia.szUrl, m_szStreamUrl, strlen(m_szStreamUrl));
		}
		else if (0 == strcmp(strDynamicMaterialType, "web"))
		{
			memcpy(m_struMaterial.struDynamicMaterial.szWebUrl, m_szWebUrl, strlen(m_szWebUrl));
		}
		else if (0 == strcmp(strDynamicMaterialType, "rss"))
		{
			memcpy(m_struMaterial.struDynamicMaterial.szRssUrl, m_szRssUrl, strlen(m_szRssUrl));
		}
		
		char* pInputBuff = NULL;
		DWORD dwInputSize = 0;
		ConvertMaterialParamsStruToXml(&m_struMaterial, &pInputBuff, dwInputSize);
		
		CString strCommand = _T("POST /ISAPI/Publish/MaterialMgr/material\r\n");
		NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
		struInputParam.dwSize = sizeof(struInputParam);
		struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
		struInputParam.dwRequestUrlLen = strCommand.GetLength();
		struInputParam.lpInBuffer = pInputBuff;
		struInputParam.dwInBufferSize = dwInputSize;
		
		char szStatusBuff[1024] = {0};
		NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
		struOutputParam.dwSize = sizeof(struOutputParam);
		struOutputParam.lpStatusBuffer = szStatusBuff;
		struOutputParam.dwStatusSize = sizeof(szStatusBuff);
		
		if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
			delete[] pInputBuff;
			pInputBuff = NULL;
			return;
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
		m_dwMaterialID = GetResponseStatusID(szStatusBuff);
		delete[] pInputBuff;
		pInputBuff = NULL;
	}
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionMaterial::OnSelchangeComboDynamicMaterialType() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_cmbDynamicMaterialType.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		return;
	}
	CString strDynamicMaterialType;
	m_cmbDynamicMaterialType.GetLBText(nCurSel, strDynamicMaterialType);
	if (0 == strcmp(strDynamicMaterialType, "streamMedia")) //流媒体
	{
		GetDlgItem(IDC_COMBO_STREAM_ADDR_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_HOST_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_IPADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_PORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_URL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WEB_URL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RSS_URL)->EnableWindow(FALSE);
	}
	else if (0 == strcmp(strDynamicMaterialType, "web")) //Web
	{
		GetDlgItem(IDC_COMBO_STREAM_ADDR_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_HOST_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_IPADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_URL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEB_URL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RSS_URL)->EnableWindow(FALSE);
	}
	else if (0 == strcmp(strDynamicMaterialType, "rss")) //Rss
	{
		GetDlgItem(IDC_COMBO_STREAM_ADDR_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_HOST_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_IPADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_URL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEB_URL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RSS_URL)->EnableWindow(TRUE);
	}
}

void CDlgInfoDiffusionMaterial::OnSelchangeComboMaterialType() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_cmbMaterialType.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		return;
	}
	CString strMaterialType;
	m_cmbMaterialType.GetLBText(nCurSel, strMaterialType);
	if (0 == strcmp(strMaterialType, "static")) //静态素材
	{
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_FORMAT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MATERIAL_PATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_MATERIAL_CHOOSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DYNAMIC_MATERIAL_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STREAM_ADDR_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_HOST_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_IPADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_URL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEB_URL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RSS_URL)->EnableWindow(FALSE);
	}
	else if (0 == strcmp(strMaterialType, "dynamic")) //动态素材
	{
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_FORMAT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MATERIAL_PATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_MATERIAL_CHOOSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DYNAMIC_MATERIAL_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_STREAM_ADDR_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_HOST_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_IPADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_PORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_URL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WEB_URL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RSS_URL)->EnableWindow(TRUE);
	}
}

void CDlgInfoDiffusionMaterial::OnSelchangeComboStaticMaterialType() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_cmbStaticMaterialType.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		return;
	}
	CString strStaticMaterialType;
	m_cmbStaticMaterialType.GetLBText(nCurSel, strStaticMaterialType);
	if (0 == strcmp(strStaticMaterialType, "picture")) //图片
	{
		m_cmbStaticMaterialFormat.ResetContent();
		m_cmbStaticMaterialFormat.AddString("bmp");
		m_cmbStaticMaterialFormat.AddString("gif");
		m_cmbStaticMaterialFormat.AddString("jpg");
		m_cmbStaticMaterialFormat.AddString("png");
		m_cmbStaticMaterialFormat.SetCurSel(0);
	}
	else if (0 == strcmp(strStaticMaterialType, "flash")) //动画
	{
		m_cmbStaticMaterialFormat.ResetContent();
		m_cmbStaticMaterialFormat.AddString("swf");
		m_cmbStaticMaterialFormat.SetCurSel(0);
	}
	else if (0 == strcmp(strStaticMaterialType, "audio")) //音频
	{
		m_cmbStaticMaterialFormat.ResetContent();
		m_cmbStaticMaterialFormat.AddString("mp3");
		m_cmbStaticMaterialFormat.AddString("wav");
		m_cmbStaticMaterialFormat.AddString("wma");
		m_cmbStaticMaterialFormat.SetCurSel(0);
	}
	else if (0 == strcmp(strStaticMaterialType, "video")) //视屏
	{
		m_cmbStaticMaterialFormat.ResetContent();
		m_cmbStaticMaterialFormat.AddString("rm");
		m_cmbStaticMaterialFormat.AddString("rmvb");
		m_cmbStaticMaterialFormat.AddString("asf");
		m_cmbStaticMaterialFormat.AddString("avi");
		m_cmbStaticMaterialFormat.AddString("mpg");
		m_cmbStaticMaterialFormat.AddString("3gp");
		m_cmbStaticMaterialFormat.AddString("mov");
		m_cmbStaticMaterialFormat.AddString("mkv");
		m_cmbStaticMaterialFormat.AddString("wmv");
		m_cmbStaticMaterialFormat.AddString("flv");
		m_cmbStaticMaterialFormat.AddString("mp4");
		m_cmbStaticMaterialFormat.SetCurSel(0);
	}
	else if (0 == strcmp(strStaticMaterialType, "document")) //文件
	{
		m_cmbStaticMaterialFormat.ResetContent();
		m_cmbStaticMaterialFormat.AddString("txt");
		m_cmbStaticMaterialFormat.AddString("ppt");
		m_cmbStaticMaterialFormat.AddString("pptx");
		m_cmbStaticMaterialFormat.AddString("doc");
		m_cmbStaticMaterialFormat.AddString("docx");
		m_cmbStaticMaterialFormat.AddString("xls");
		m_cmbStaticMaterialFormat.AddString("xlsx");
		m_cmbStaticMaterialFormat.AddString("pdf");
		m_cmbStaticMaterialFormat.SetCurSel(0);
	}
	else if (0 == strcmp(strStaticMaterialType, "template")) //模板
	{
		m_cmbStaticMaterialFormat.ResetContent();
		m_cmbStaticMaterialFormat.AddString("tpl");
		m_cmbStaticMaterialFormat.AddString("dstpl");
		m_cmbStaticMaterialFormat.SetCurSel(0);
	}
	
	if(0 == strcmp(strStaticMaterialType,"clock") || 0 == strcmp(strStaticMaterialType,"weather") )
	{
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_FORMAT)->EnableWindow(FALSE);
		
	}
	else
	{
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_FORMAT)->EnableWindow(TRUE);
	}
}

void CDlgInfoDiffusionMaterial::OnSelchangeComboStreamAddrType() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_cmbStreamAddrType.GetCurSel();
	if (nCurSel == CB_ERR)
	{
		return;
	}
	CString strAddrType;
	m_cmbStreamAddrType.GetLBText(nCurSel, strAddrType);
	if (0 == strcmp(strAddrType, "hostname"))
	{
		GetDlgItem(IDC_EDIT_STREAM_HOST_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STREAM_IPADDR)->EnableWindow(FALSE);
	}
	else if (0 == strcmp(strAddrType, "ipaddress"))
	{
		GetDlgItem(IDC_EDIT_STREAM_HOST_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STREAM_IPADDR)->EnableWindow(TRUE);
	}
}

BOOL CDlgInfoDiffusionMaterial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbMaterialType.SetCurSel(0);
	OnSelchangeComboMaterialType();
	m_ctrlProgress.SetRange(0, 100);
	m_ctrlProgress.SetStep(1);
	m_ctrlProgress.SetPos(0);
	m_statProgress.SetWindowText(_T("0%"));
	InitMaterialList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgInfoDiffusionMaterial::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgInfoDiffusionMaterial::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_UPDOWNLOAD_MATERIAL_PROGRESS)
	{
		DWORD dwProgress = 0;
		LONG lStatus = -1;
		if (m_bUploading)
		{
			lStatus = NET_DVR_GetUploadState(m_lUpdownloadHandle, &dwProgress);
			if (lStatus == -1)
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetUploadState");
				if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
				}
				else
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
				}
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetUploadState");
			}
		}
		else if (m_bDownloading)
		{
			lStatus = NET_DVR_GetDownloadState(m_lUpdownloadHandle, &dwProgress);
			if (lStatus == -1)
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDownloadState");
				if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
				}
				else
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
				}
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDownloadState");
			}
		}
		switch (lStatus)
		{
		case 1: //上传或下载成功
			{
				m_ctrlProgress.SetPos(dwProgress);
				CString str;
				str.Format("%d", dwProgress);
				str += _T("%");
				m_statProgress.SetWindowText(str);
				if (m_bUploading)
				{
					if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
					}
					else
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
					}
					m_bUploading = FALSE;
				}
				else if (m_bDownloading)
				{
					if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
					}
					else
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
					}
					m_bDownloading = FALSE;
				}
				m_lUpdownloadHandle = -1;
				KillTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "素材管理", "Material Management");
				g_StringLanType(sMsg, "上传/下载完成", "Upload/Download finished.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
				break;
			}
		case 2: //正在上传或下载
			{
				m_ctrlProgress.SetPos(dwProgress);
				CString str;
				str.Format("%d", dwProgress);
				str += _T("%");
				m_statProgress.SetWindowText(str);
				break;
			}
		case 3: //上传或下载失败
			{
				if (m_bUploading)
				{
					if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
					}
					else
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
					}
					m_bUploading = FALSE;
				}
				else if (m_bDownloading)
				{
					if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
					}
					else
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
					}
					m_bDownloading = FALSE;
				}
				m_lUpdownloadHandle = -1;
				KillTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "素材管理", "Material Management");
				g_StringLanType(sMsg, "上传/下载失败", "Upload/Download failed.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
				break;
			}
		case 4: //网络断开
			{
				if (m_bUploading)
				{
					if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
					}
					else
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
					}
					m_bUploading = FALSE;
				}
				else if (m_bDownloading)
				{
					if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
					}
					else
					{
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
					}
					m_bDownloading = FALSE;
				}
				m_lUpdownloadHandle = -1;
				KillTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "素材管理", "Material Management");
				g_StringLanType(sMsg, "网络断开", "Network disconnection.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
				break;
			}
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgInfoDiffusionMaterial::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_lpResult)
	{
		delete m_lpResult;
		m_lpResult = NULL;
	}
	if (m_pOutputXmlBuffer)
	{
		delete[] m_pOutputXmlBuffer;
		m_pOutputXmlBuffer = NULL;
	}
}

void CDlgInfoDiffusionMaterial::OnBtnMaterialSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	strcpy(m_struDescription.sSearchID, m_sSearchID);
	int nSel = m_cmbSearchApproveState.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSearchApproveState.GetLBText(nSel, m_struDescription.sApproveState);
	strcpy(m_struDescription.sUploader, m_sUploader);
	nSel = m_cmbSearchShareProp.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSearchShareProp.GetLBText(nSel, m_struDescription.sShareProperty);
	nSel = m_cmbSearchMaterialType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "素材管理", "Material Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSearchMaterialType.GetLBText(nSel, m_struDescription.sMaterialType);
	if (0 == strcmp(m_struDescription.sMaterialType, "static"))
	{
		nSel = m_cmbSearchStaticType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "素材管理", "Material Management");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbSearchStaticType.GetLBText(nSel, m_struDescription.sStaticMaterialType);
		m_struDescription.dwMinStaticMaterialSize = m_dwStaticMinSize;
		m_struDescription.dwMaxStaticMaterialSize = m_dwStaticMaxSize;
	}
	else if (0 == strcmp(m_struDescription.sMaterialType, "dynamic"))
	{
		nSel = m_cmbSearchDynamicType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "素材管理", "Material Management");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbSearchDynamicType.GetLBText(nSel, m_struDescription.sDynamicMaterialType);
	}
	m_struDescription.dwMaxResults = m_dwMaxResults;
	m_struDescription.dwSearchResultsPosition = m_dwStartPosition;
	m_struDescription.struTimeRange.struBeginTime.dwYear = m_tmStartDate.GetYear();
	m_struDescription.struTimeRange.struBeginTime.dwMonth = m_tmStartDate.GetMonth();
	m_struDescription.struTimeRange.struBeginTime.dwDay = m_tmStartDate.GetDay();
	m_struDescription.struTimeRange.struBeginTime.dwHour = m_tmStartTime.GetHour();
	m_struDescription.struTimeRange.struBeginTime.dwMinute = m_tmStartTime.GetMinute();
	m_struDescription.struTimeRange.struBeginTime.dwSecond = m_tmStartTime.GetSecond();
	m_struDescription.struTimeRange.struEndTime.dwYear = m_tmEndDate.GetYear();
	m_struDescription.struTimeRange.struEndTime.dwMonth = m_tmEndDate.GetMonth();
	m_struDescription.struTimeRange.struEndTime.dwDay = m_tmEndDate.GetDay();
	m_struDescription.struTimeRange.struEndTime.dwHour = m_tmEndTime.GetHour();
	m_struDescription.struTimeRange.struEndTime.dwMinute = m_tmEndTime.GetMinute();
	m_struDescription.struTimeRange.struEndTime.dwSecond = m_tmEndTime.GetSecond();
	
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertMaterialSearchDescriptionParamsStruToXml(&m_struDescription, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("POST /ISAPI/Publish/MaterialMgr/materialSearch\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
	struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
	struOutputParam.dwOutBufferSize = MAX_LEN_XML;
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	memset(m_lpResult, 0, sizeof(*m_lpResult));
	ConvertMaterialSearchResultXmlToStru(m_pOutputXmlBuffer, m_lpResult);
	RefreshMaterialList();
}

void CDlgInfoDiffusionMaterial::OnSelchangeComboSearchMaterialType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbSearchMaterialType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strType;
	m_cmbSearchMaterialType.GetLBText(nSel, strType);
	if (0 == strType.Compare("static"))
	{
		GetDlgItem(IDC_COMBO_MATERIAL_STATIC_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MATERIAL_MIN_SIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MATERIAL_MAX_SIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MATERIAL_DYNAMIC_TYPE)->EnableWindow(FALSE);
	}
	else if (0 == strType.Compare("dynamic"))
	{
		GetDlgItem(IDC_COMBO_MATERIAL_STATIC_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MATERIAL_MIN_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MATERIAL_MAX_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MATERIAL_DYNAMIC_TYPE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_MATERIAL_STATIC_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MATERIAL_MIN_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MATERIAL_MAX_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MATERIAL_DYNAMIC_TYPE)->EnableWindow(FALSE);
	}
}

void CDlgInfoDiffusionMaterial::OnClickListMaterial(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDlgInfoDiffusionMaterial::InitMaterialList()
{
	DWORD dwExStyle = m_listMaterial.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listMaterial.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listMaterial.InsertColumn(0, szLan);
	m_listMaterial.SetColumnWidth(0, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "素材编号", "Material No.");
	m_listMaterial.InsertColumn(1, szLan);
	m_listMaterial.SetColumnWidth(1, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "素材名称", "Material Name");
	m_listMaterial.InsertColumn(2, szLan);
	m_listMaterial.SetColumnWidth(2, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "素材类型", "Material Type");
	m_listMaterial.InsertColumn(3, szLan);
	m_listMaterial.SetColumnWidth(3, 80);
}

void CDlgInfoDiffusionMaterial::RefreshMaterialList()
{
	CString str;
	for (int nCnt = 0; nCnt < m_lpResult->dwNumOfMatches; nCnt++)
	{
		if (0 == m_lpResult->struMaterialList[nCnt].dwMaterialID)
		{
			continue;
		}
		str.Format("%d", nCnt+1);
		m_listMaterial.InsertColumn(nCnt, str);
		str.Format("%d", m_lpResult->struMaterialList[nCnt].dwMaterialID);
		m_listMaterial.SetItemText(nCnt, 1, str);
		m_listMaterial.SetItemText(nCnt, 2, m_lpResult->struMaterialList[nCnt].szMaterialName);
		m_listMaterial.SetItemText(nCnt, 3, m_lpResult->struMaterialList[nCnt].szMaterialType);
	}
}


void CDlgInfoDiffusionMaterial::OnLvnItemchangedListMaterial(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    *pResult = 0;
}


void CDlgInfoDiffusionMaterial::OnBnClickedBtnBatchDel()
{
    // TODO:  在此添加控件通知处理程序代码
    /*
    POSITION pos = m_listMaterial.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        return;
    }
    else
    {
        m_nCountId = 0;
        memset(m_nArrayId, 0, MAX_ID);
        int arry[MAX_ID] = { 0 };
        while (pos)
        {
            int nItem = m_listMaterial.GetNextSelectedItem(pos);
            CString strid = m_listMaterial.GetItemText(nItem, 1);
            int intId = atoi(strid);
            m_nArrayId[m_nCountId] = intId;
            m_nCountId++;
            arry[m_nCountId] = nItem;
            //m_listProgram.DeleteItem(nItem);
        }
    }*/
    m_nCountId = 2;
    m_nArrayId[0] = 106;
    m_nArrayId[1] = 107;
    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    if (!ConvertMaterialIdToXml(m_nArrayId, m_nCountId, &pInputBuff, dwInputSize))
    {
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    CString strCommand;
    strCommand.Format("DELETE /ISAPI/Publish/MaterialMgr/material\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");


    if (pInputBuff != NULL)
    {
        delete[] pInputBuff;
        pInputBuff = NULL;
    }
}


void CDlgInfoDiffusionMaterial::OnBnClickedBtnBatchSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    /*
    POSITION pos = m_listMaterial.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        return;
    }
    else
    {
        m_nCountId = 0;
        memset(m_nArrayId, 0, MAX_ID);
        int arry[MAX_ID] = { 0 };
        while (pos)
        {
            int nItem = m_listMaterial.GetNextSelectedItem(pos);
            CString strid = m_listMaterial.GetItemText(nItem, 1);
            int intId = atoi(strid);
            m_nArrayId[m_nCountId] = intId;
            m_nCountId++;
            arry[m_nCountId] = nItem;
        }
    }*/
    m_nCountId = 2;
    m_nArrayId[0] = 1;
    m_nArrayId[1] = 2;
    int nSel = m_comOperatorType.GetCurSel();
    if (nSel == CB_ERR)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
        g_StringLanType(szLan2, "素材管理", "Material Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_comOperatorType.GetLBText(nSel, m_struMaterial.szOperatorType);
    
    if (!strcmp(m_struMaterial.szOperatorType, "remark"))
    {
        strcpy(m_struMaterial.szMaterialRemarks, m_szPropRemarks);
    }
    else if (!strcmp(m_struMaterial.szOperatorType, "property"))
    {

        nSel = m_cmbEditShareProp.GetCurSel();
        if (nSel == CB_ERR)
        {
            char szLan1[512] = { 0 };
            char szLan2[512] = { 0 };
            g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
            g_StringLanType(szLan2, "素材管理", "Material Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        m_cmbEditShareProp.GetLBText(nSel, m_struMaterial.szSharePropery);
    }
    else if (!strcmp(m_struMaterial.szOperatorType, "approve"))
    {

        nSel = m_cmbApprove.GetCurSel();
        if (nSel == CB_ERR)
        {
            char szLan1[512] = { 0 };
            char szLan2[512] = { 0 };
            g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
            g_StringLanType(szLan2, "素材管理", "Material Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        m_cmbApprove.GetLBText(nSel, m_struMaterial.szApprove);
        strcpy(m_struMaterial.szApproveRemarks, m_szApproveRemarks);
    }
    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    if (!(ConvertMaterialBatchInfoToXml(m_nArrayId, m_nCountId, &m_struMaterial, &pInputBuff, dwInputSize)))
    {
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }

    CString strCommand;
    strCommand.Format("PUT /ISAPI/Publish/MaterialMgr/materialBatchInfo\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        if (pInputBuff != NULL)
        {
            delete [] pInputBuff;
            pInputBuff = NULL;   
        }
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    if (pInputBuff != NULL)
    {
        delete [] pInputBuff;
        pInputBuff = NULL;
    }
    return;
}
