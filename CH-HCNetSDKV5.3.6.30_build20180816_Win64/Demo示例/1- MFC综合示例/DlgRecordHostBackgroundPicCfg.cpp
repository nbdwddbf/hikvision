// DlgRecordHostBackgroundPicCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostBackgroundPicCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostBackgroundPicCfg dialog


CDlgRecordHostBackgroundPicCfg::CDlgRecordHostBackgroundPicCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostBackgroundPicCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostBackgroundPicCfg)
		// NOTE: the ClassWizard will add member initialization here
	m_bEnable = FALSE;        
	m_dwPicSize = 0;
	m_dwPicType = 0;
	m_dwPicWidth = 0;
	m_dwPicHeight = 0;
	m_dwUploadProgress = 0;
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CDlgRecordHostBackgroundPicCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostBackgroundPicCfg)
	ON_BN_CLICKED(IDC_RAD_PIC_UPLOAD, OnRadPicUpload)
	ON_BN_CLICKED(IDC_RAD_PIC_CFG, OnRadPicCfg)
	ON_BN_CLICKED(IDC_RAD_PIC_QUERY, OnRadPicQuery)
	ON_BN_CLICKED(IDC_RAD_PIC_DEL, OnRadPicDel)
	ON_BN_CLICKED(IDC_BTN_START_UPLOAD, OnBtnStartUpload)
	ON_BN_CLICKED(IDC_BTN_STOP_UPLOAD, OnBtnStopUpload)
    ON_BN_CLICKED(IDC_BTN_GET_UPLOAD_STATE, OnBtnGetUploadState)
	ON_BN_CLICKED(IDC_BTN_GET_PIC, OnBtnGetBGPicCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PIC, OnBtnSetBGPicCfg)
	ON_BN_CLICKED(IDC_BTN_QUERY_PIC, OnBtnSetBGPicQuery)
	ON_BN_CLICKED(IDC_BTN_DEL_PIC, OnBtnSetBGPicDel)
    ON_BN_CLICKED(IDC_BTN_SELECT_FILE, OnBtnSelectFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgRecordHostBackgroundPicCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordHostBackgroundPicCfg)
	
	DDX_Control(pDX, IDC_COM_DIRECTED_CHANNEL, m_comDirectedChannel);
    DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Control(pDX, IDC_COM_DIRECTED_CHANNEL, m_comDirectedChannel);
	DDX_Control(pDX, IDC_CHK_ENABLE, m_chkEnable);

	DDX_Control(pDX, IDC_STAT_PROGRESS, m_labProgress);
    
	DDX_Control(pDX, IDC_EDT_PIC_SIZE, m_edtPicSize);
	DDX_Control(pDX, IDC_EDT_PIC_WIDTH, m_edtPicWidth);
	DDX_Control(pDX, IDC_EDT_PIC_HEIGHT, m_edtPicHeight);
	DDX_Control(pDX, IDC_EDT_PIC_NAME, m_edtPicName);
	DDX_Control(pDX, IDC_EDT_PIC_ID, m_edtPicID);
	DDX_Control(pDX, IDC_EDT_FILE_NAME, m_edtFileName);
    DDX_Control(pDX, IDC_BTN_SELECT_FILE, m_btnSelectFile);

	DDX_Control(pDX, IDC_COM_PIC_TYPE, m_comPicType);
	DDX_Control(pDX, IDC_RAD_PIC_UPLOAD, m_radPicUpload);
	DDX_Control(pDX, IDC_BTN_START_UPLOAD, m_btnStartUpload);
	DDX_Control(pDX, IDC_BTN_STOP_UPLOAD, m_btnStopUpload);
	DDX_Control(pDX, IDC_BTN_GET_UPLOAD_STATE, m_btnGetUploadState);
	DDX_Control(pDX, IDC_COM_UPLOAD_STATE, m_comUploadState);
	DDX_Control(pDX, IDC_RAD_PIC_CFG, m_radPicCfg);
	DDX_Control(pDX, IDC_BTN_GET_PIC, m_btnGetPic);
	DDX_Control(pDX, IDC_BTN_SET_PIC, m_btnSetPic);
	DDX_Control(pDX, IDC_RAD_PIC_QUERY, m_radPicQuery);
	DDX_Control(pDX, IDC_BTN_QUERY_PIC, m_btnQueryPic);
	DDX_Control(pDX, IDC_RAD_PIC_DEL, m_radPicDel);
	DDX_Control(pDX, IDC_BTN_DEL_PIC, m_btnDelPic);

	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);

    DDX_Text(pDX, IDC_COM_DIRECTED_CHANNEL, m_dwChannel);
    DDX_Text(pDX, IDC_EDT_PIC_SIZE, m_dwPicSize);
    DDX_Text(pDX, IDC_EDT_PIC_WIDTH, m_dwPicWidth);
	DDX_Text(pDX, IDC_EDT_PIC_HEIGHT, m_dwPicHeight);
	DDX_Text(pDX, IDC_EDT_PIC_NAME, m_strPicName);
	DDX_Text(pDX, IDC_EDT_PIC_ID, m_strPicID);
	DDX_Text(pDX, IDC_EDT_FILE_NAME, m_strFileName);

	DDX_Text(pDX, IDC_STAT_PROGRESS, m_dwUploadProgress);
	
	//}}AFX_DATA_MAP
}

BOOL CDlgRecordHostBackgroundPicCfg::OnInitDialog()
{
    CDialog::OnInitDialog();
	
	//FIXME:
	//m_comDirectedChannel.InsertStream(0, _T(""));
	//m_comDirectedChannel.SetCurSel(0);

    m_dwChannel = 1;

    m_comPicType.InsertString(0, _T("0-YUV"));
	m_comPicType.InsertString(1, _T("1-JPEG"));
	m_comPicType.SetCurSel(0);

	m_comUploadState.InsertString(0, _T("-1-上传失败"));
	m_comUploadState.InsertString(1, _T("1-上传成功"));
	m_comUploadState.InsertString(2, _T("2-正在上传"));
	m_comUploadState.InsertString(3, _T("3-上传失败"));
	m_comUploadState.InsertString(4, _T("4-网络断开"));
	m_comUploadState.InsertString(5, _T("5-未知状态"));
	m_comUploadState.InsertString(6, _T("6-硬盘错误"));
	m_comUploadState.InsertString(7, _T("7-无审讯文件存放盘"));
	m_comUploadState.InsertString(8, _T("8-容量不足"));
	m_comUploadState.InsertString(9, _T("9-设备资源不足"));
	m_comUploadState.InsertString(10, _T("10-文件个数超过最大值"));
	m_comUploadState.SetCurSel(0);


	m_btnStartUpload.EnableWindow(FALSE);
	m_btnStopUpload.EnableWindow(FALSE);
	m_btnGetUploadState.EnableWindow(FALSE);
	m_comUploadState.EnableWindow(FALSE);
    m_btnSelectFile.EnableWindow(FALSE);

	m_btnGetPic.EnableWindow(FALSE);
	m_btnSetPic.EnableWindow(FALSE);
	m_btnQueryPic.EnableWindow(FALSE);
	m_btnDelPic.EnableWindow(FALSE);
	//
	m_chkEnable.EnableWindow(FALSE);
	m_comDirectedChannel.EnableWindow(FALSE);	
	m_edtPicSize.EnableWindow(FALSE);
	m_edtPicWidth.EnableWindow(FALSE);
	m_edtPicHeight.EnableWindow(FALSE);
	m_comPicType.EnableWindow(FALSE);
	m_edtPicName.EnableWindow(FALSE);
	m_edtPicID.EnableWindow(FALSE);
	m_edtFileName.EnableWindow(FALSE);


    m_dwPicWidth  = 1920;
	m_dwPicHeight = 1080;

    UpdateData(FALSE);

    return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostBackgroundPicCfg message handlers

void CDlgRecordHostBackgroundPicCfg::OnRadPicUpload() 
{
	// TODO: Add your control notification handler code here
	m_btnStartUpload.EnableWindow(TRUE);
	m_btnStopUpload.EnableWindow(TRUE);
	m_btnGetUploadState.EnableWindow(TRUE);
	m_comUploadState.EnableWindow(TRUE);
    m_btnSelectFile.EnableWindow(TRUE);

	m_btnGetPic.EnableWindow(FALSE);
	m_btnSetPic.EnableWindow(FALSE);
	m_btnQueryPic.EnableWindow(FALSE);
	m_btnDelPic.EnableWindow(FALSE);
	//
	m_chkEnable.EnableWindow(FALSE);
	m_comDirectedChannel.EnableWindow(TRUE);	
	m_edtPicSize.EnableWindow(TRUE);
	m_edtPicWidth.EnableWindow(TRUE);
	m_edtPicHeight.EnableWindow(TRUE);
	m_comPicType.EnableWindow(TRUE);
	m_edtPicName.EnableWindow(TRUE);
	m_edtPicID.EnableWindow(FALSE);
	m_edtFileName.EnableWindow(TRUE);

}

void CDlgRecordHostBackgroundPicCfg::OnRadPicCfg()
{
	m_btnStartUpload.EnableWindow(FALSE);
	m_btnStopUpload.EnableWindow(FALSE);
	m_btnGetUploadState.EnableWindow(FALSE);
	m_comUploadState.EnableWindow(FALSE);
    m_btnSelectFile.EnableWindow(FALSE);

	m_btnGetPic.EnableWindow(TRUE);
	m_btnSetPic.EnableWindow(TRUE);

	m_btnQueryPic.EnableWindow(FALSE);
	m_btnDelPic.EnableWindow(FALSE);
	//
	m_chkEnable.EnableWindow(TRUE);
	m_comDirectedChannel.EnableWindow(FALSE);	
	m_edtPicSize.EnableWindow(FALSE);
	m_edtPicWidth.EnableWindow(FALSE);
	m_edtPicHeight.EnableWindow(FALSE);
	m_comPicType.EnableWindow(FALSE);
	m_edtPicName.EnableWindow(FALSE);
	m_edtPicID.EnableWindow(TRUE);
	m_edtFileName.EnableWindow(FALSE);
}
void CDlgRecordHostBackgroundPicCfg::OnRadPicQuery()
{
	m_btnStartUpload.EnableWindow(FALSE);
	m_btnStopUpload.EnableWindow(FALSE);
	m_btnGetUploadState.EnableWindow(FALSE);
	m_comUploadState.EnableWindow(FALSE);
    m_btnSelectFile.EnableWindow(FALSE);

	m_btnGetPic.EnableWindow(FALSE);
	m_btnSetPic.EnableWindow(FALSE);

	m_btnQueryPic.EnableWindow(TRUE);

	m_btnDelPic.EnableWindow(FALSE);
	//
	m_chkEnable.EnableWindow(FALSE);
	m_comDirectedChannel.EnableWindow(FALSE);	
	m_edtPicSize.EnableWindow(FALSE);
	m_edtPicWidth.EnableWindow(FALSE);
	m_edtPicHeight.EnableWindow(FALSE);
	m_comPicType.EnableWindow(FALSE);
	m_edtPicName.EnableWindow(FALSE);
	m_edtPicID.EnableWindow(TRUE);
	m_edtFileName.EnableWindow(FALSE);
}

void CDlgRecordHostBackgroundPicCfg::OnRadPicDel()
{
	m_btnStartUpload.EnableWindow(FALSE);
	m_btnStopUpload.EnableWindow(FALSE);
	m_btnGetUploadState.EnableWindow(FALSE);
	m_comUploadState.EnableWindow(FALSE);
    m_btnSelectFile.EnableWindow(FALSE);

	m_btnGetPic.EnableWindow(FALSE);
	m_btnSetPic.EnableWindow(FALSE);
	m_btnQueryPic.EnableWindow(FALSE);

	m_btnDelPic.EnableWindow(TRUE);
	//
	m_chkEnable.EnableWindow(FALSE);
	m_comDirectedChannel.EnableWindow(FALSE);	
	m_edtPicSize.EnableWindow(FALSE);
	m_edtPicWidth.EnableWindow(FALSE);
	m_edtPicHeight.EnableWindow(FALSE);
	m_comPicType.EnableWindow(FALSE);
	m_edtPicName.EnableWindow(FALSE);
	m_edtPicID.EnableWindow(TRUE);
	m_edtFileName.EnableWindow(FALSE);
}

void CDlgRecordHostBackgroundPicCfg::OnBtnSelectFile()
{
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                    (LPCTSTR)_TEXT("YUV Files(*.yuv420)|*.yuv420|JPG Files(*.jpg)|*.jpg|All Files (*.*)|*.*||"),
                    NULL);

    if(dlg.DoModal()==IDOK)
    {
	    m_strFileName = dlg.GetPathName();
        m_strPicName  = dlg.GetFileName();

        CString strExtName = dlg.GetFileExt();
        strExtName.MakeLower();

        if (strExtName.Compare("jpg") == 0 || strExtName.Compare("jpeg") == 0)
        {
            m_comPicType.SetCurSel(1);
            Image* img = Image::FromFile((WCHAR*)m_strFileName.AllocSysString());
            
            if (img)
            {
                m_dwPicWidth  = img->GetWidth();
                m_dwPicHeight = img->GetHeight();
                delete img;
            } 
        }
        else
        {
            m_comPicType.SetCurSel(0);
        }

	    CFileStatus fileStatus;   
	    if (CFile::GetStatus(m_strFileName, fileStatus))  
	    {  
		    m_dwPicSize = fileStatus.m_size;  
        }
    }
    else
    {
	    return;
    }
    UpdateData(FALSE);
}

void CDlgRecordHostBackgroundPicCfg::OnBtnStartUpload()
{
    UpdateData(TRUE);
    
    NET_DVR_BACKGROUND_PIC_PRARAM struBGPicParam = {0};
    
    struBGPicParam.dwSize = sizeof(struBGPicParam);
    
    struBGPicParam.dwChannel = m_dwChannel;

    struBGPicParam.dwPicSize = m_dwPicSize;
    struBGPicParam.wPicWidth = m_dwPicWidth;
    struBGPicParam.wPicHeight = m_dwPicHeight;
    struBGPicParam.byPicType  = m_comPicType.GetCurSel();

	char szFileName[256];
	strncpy(szFileName, m_strFileName.GetBuffer(m_strFileName.GetLength()), NAME_LEN);
    strncpy(struBGPicParam.szPicName, m_strPicName.GetBuffer(m_strPicName.GetLength()), NAME_LEN);

    NET_DVR_UPLOAD_DB_OUT struUploadOut = {0};
    //struUploadOut.dwSize = sizeof(struUploadOut);
    strncpy(&(struUploadOut.szFileID[0]), m_strPicID.GetBuffer(m_strPicID.GetLength()), MAX_ID_LEN);

	m_lUploadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_BACKGROUND_PIC, &struBGPicParam, sizeof(struBGPicParam), szFileName, &struUploadOut,  sizeof(struUploadOut));

    if (m_lUploadHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "UPLOAD_BACKGROUND_PIC");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "UPLOAD_BACKGROUND_PIC");
        m_strPicID = struUploadOut.szFileID;
    }
    UpdateData(FALSE);

}

void CDlgRecordHostBackgroundPicCfg::OnBtnStopUpload()
{
	if (NET_DVR_UploadClose(m_lUploadHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
	}
}

void CDlgRecordHostBackgroundPicCfg::OnBtnGetUploadState()
{
    LONG lState = NET_DVR_GetUploadState(m_lUploadHandle, &m_dwUploadProgress);

    if (lState < 1)
    {
        m_comUploadState.SetCurSel(0);
    }
    else
    {
        m_comUploadState.SetCurSel(lState);
    }

    UpdateData(FALSE); 
}

void CDlgRecordHostBackgroundPicCfg::OnBtnGetBGPicCfg()
{
    UpdateData(TRUE);

    NET_DVR_BACKGROUND_PIC_INFO struBGPicInfo = {0};
    struBGPicInfo.dwSize = sizeof(struBGPicInfo);

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = NULL;
    struSTDConfig.dwCondSize = 0;
    struSTDConfig.lpOutBuffer = &struBGPicInfo;
    struSTDConfig.dwOutSize = sizeof(struBGPicInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_BACKGROUND_PIC_INFO, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BACKGROUND_PIC_INFO");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BACKGROUND_PIC_INFO");
    }

    m_strPicID = struBGPicInfo.byPicID;

    if (struBGPicInfo.byEnable == 1)
    {
        m_bEnable = TRUE;
    }
    else
    {
        m_bEnable = FALSE;
    }

    UpdateData(FALSE);
}

void CDlgRecordHostBackgroundPicCfg::OnBtnSetBGPicCfg()
{
    UpdateData(TRUE);

    NET_DVR_BACKGROUND_PIC_INFO struBGPicInfo = {0};
    struBGPicInfo.dwSize = sizeof(struBGPicInfo);

    if (m_chkEnable.GetCheck() == BST_CHECKED)
    {
        struBGPicInfo.byEnable = 1;
    }
    else
    {
        struBGPicInfo.byEnable = 0;
    }

    strncpy((char*)(struBGPicInfo.byPicID), m_strPicID.GetBuffer(m_strPicID.GetLength()), MAX_ID_LEN);

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = NULL;
    struSTDConfig.dwCondSize = 0;
    struSTDConfig.lpInBuffer = &struBGPicInfo;
    struSTDConfig.dwInSize = sizeof(struBGPicInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_BACKGROUND_PIC_INFO, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_BACKGROUND_PIC_INFO");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BACKGROUND_PIC_INFO");
    }
}

void CDlgRecordHostBackgroundPicCfg::OnBtnSetBGPicQuery()
{
    UpdateData(TRUE);
	NET_DVR_BACKGROUND_PIC_CFG struBGPicCfg = {0};
	struBGPicCfg.dwSize = sizeof(struBGPicCfg);

    NET_DVR_BACKGROUND_PIC_COND struBGPicCond = {0};
    struBGPicCond.dwSize = sizeof(struBGPicCond);
    strncpy((char*)(struBGPicCond.szFileID), m_strPicID.GetBuffer(m_strPicID.GetLength()), MAX_FILE_ID_LEN);

	NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &struBGPicCond;
    struSTDConfig.dwCondSize = sizeof(struBGPicCond);
    struSTDConfig.lpOutBuffer = &struBGPicCfg;
    struSTDConfig.dwOutSize = sizeof(struBGPicCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

	if (NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_BACKGROUND_PIC_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BACKGROUND_PIC_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BACKGROUND_PIC_CFG");
    }

    m_dwPicSize = struBGPicCfg.dwPicSize;
    m_dwPicType = struBGPicCfg.dwPicType;
    m_dwPicWidth = struBGPicCfg.wPicWidth;
    m_dwPicHeight = struBGPicCfg.wPicHeight;
    m_strPicName = (char*)struBGPicCfg.byPicName;

	m_comPicType.SetCurSel(m_dwPicType);

	UpdateData(FALSE);

}

void CDlgRecordHostBackgroundPicCfg::OnBtnSetBGPicDel()
{
	UpdateData(TRUE);

    NET_DVR_BACKGROUND_PIC_COND struBGPicCond = {0};
    struBGPicCond.dwSize = sizeof(struBGPicCond);
    strncpy((char*)(struBGPicCond.szFileID), m_strPicID.GetBuffer(m_strPicID.GetLength()), MAX_FILE_ID_LEN);

    NET_DVR_STD_CONTROL struSTDControl = {0};
    struSTDControl.lpCondBuffer = &struBGPicCond;
    struSTDControl.dwCondSize = sizeof(struBGPicCond);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDControl.lpStatusBuffer = m_szStatusBuf;
    struSTDControl.dwStatusSize = ISAPI_STATUS_LEN;

    if (NET_DVR_STDControl(m_lUserID, NET_DVR_DEL_BACKGROUND_PIC, &struSTDControl))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_DEL_BACKGROUND_PIC");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DEL_BACKGROUND_PIC");
    }
}




