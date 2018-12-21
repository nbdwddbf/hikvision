// DlgUploadFile.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgUploadFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadFile dialog


CDlgUploadFile::CDlgUploadFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUploadFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUploadFile)
	m_strFileName = _T("");
	m_strCameraID = _T("");
	m_tmBeginDate = 0;
	m_tmBeginTime = 0;
	m_tmEndDate = 0;
	m_tmEndTime = 0;
	m_csFileName = _T("");
	m_dwStoragePoolID = 0;
	//}}AFX_DATA_INIT
}


void CDlgUploadFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUploadFile)
	DDX_Control(pDX, IDC_CMD_VEDIOENC_TYPE, m_cmdVedioEncType);
	DDX_Control(pDX, IDC_CMD_AUDIOENC_TYPE, m_cmbAudioEncType);
	DDX_Control(pDX, IDC_CMB_FORMATTYPE, m_cmbFormatType);
	DDX_Control(pDX, IDC_CMB_FILETYPE, m_cmbFileType);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_CAMERAID, m_strCameraID);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN_DATE, m_tmBeginDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN_TIME, m_tmBeginTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_DATE, m_tmEndDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_TIME, m_tmEndTime);
	DDX_Text(pDX, IDC_EDIT_CS_UPLOADFILENAME, m_csFileName);
	DDX_Text(pDX, IDC_EDIT_STORAGEID, m_dwStoragePoolID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUploadFile, CDialog)
	//{{AFX_MSG_MAP(CDlgUploadFile)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_FILE, OnButtonBrowseFile)
	ON_BN_CLICKED(ID_UPLOAD, OnUpload)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadFile message handlers

void CDlgUploadFile::OnButtonBrowseFile() 
{
	// TODO: Add your control notification handler code here
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFileName = dlg.GetPathName();
       
        UpdateData(FALSE);
	}
    AA();
}

void CDlgUploadFile::OnUpload() 
{
	// TODO: Add your control notification handler code here
    
    UpdateData(TRUE);
    char szFileName[MAX_PATH];
    strcpy(szFileName, m_strFileName);
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
        g_StringLanType(szLan, "录像文件为空", "Record file is empty");
        AfxMessageBox(szLan);
    }
    cFile.Close();
    
    
    NET_DVR_UPLOAD_RECORD_INFO struRecordInfo = {0};
    
    struRecordInfo.dwSize = sizeof(struRecordInfo);
    struRecordInfo.dwRecordType = m_cmbFileType.GetCurSel();
    memcpy(struRecordInfo.sCameraID,m_strCameraID, m_strCameraID.GetLength());

    //memcpy(struRecordInfo.struStartTime
    struRecordInfo.struStartTime.wYear      = m_tmBeginDate.GetYear();
    struRecordInfo.struStartTime.byMonth    = m_tmBeginDate.GetMonth();
    struRecordInfo.struStartTime.byDay      = m_tmBeginDate.GetDay();
    struRecordInfo.struStartTime.byHour     = m_tmBeginTime.GetHour();
    struRecordInfo.struStartTime.byMinute   = m_tmBeginTime.GetMinute();
    struRecordInfo.struStartTime.bySecond   = m_tmBeginTime.GetSecond();

    struRecordInfo.struStopTime.wYear      = m_tmEndDate.GetYear();
    struRecordInfo.struStopTime.byMonth    = m_tmEndDate.GetMonth();
    struRecordInfo.struStopTime.byDay      = m_tmEndDate.GetDay();
    struRecordInfo.struStopTime.byHour     = m_tmEndTime.GetHour();
    struRecordInfo.struStopTime.byMinute   = m_tmEndTime.GetMinute();
    struRecordInfo.struStopTime.bySecond   = m_tmEndTime.GetSecond();
    struRecordInfo.byISO8601 = g_bISO8601;
    struRecordInfo.cStartTimeDifferenceH = g_iHourDiffWithUTC;
    struRecordInfo.cStartTimeDifferenceM = g_iMinDiffWithUTC;
    struRecordInfo.cStopTimeDifferenceH = g_iHourDiffWithUTC;
    struRecordInfo.cStopTimeDifferenceM = g_iMinDiffWithUTC;

    struRecordInfo.dwStoragePoolID = m_dwStoragePoolID;
    DWORD dwCurIndex = m_cmbFormatType.GetCurSel();
    
    if (dwCurIndex >=0 && dwCurIndex <=8 )
    {
        struRecordInfo.byFormatType = dwCurIndex +1;
    }
    else
    {
        struRecordInfo.byFormatType = 0xff;
    }

    dwCurIndex = m_cmdVedioEncType.GetCurSel();

    if (dwCurIndex == 3 ||dwCurIndex == 4)
    {
        dwCurIndex +=4;
    }
    struRecordInfo.byVideoEncType = dwCurIndex;

    dwCurIndex = m_cmbAudioEncType.GetCurSel();
    
    if (dwCurIndex == 3 ||dwCurIndex == 4)
    {
        dwCurIndex = 0xff;
    }
    struRecordInfo.byAudioEncType = dwCurIndex;

    char szRetUrl[1024] = {0};
    m_lUploadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_RECORD_FILE, &struRecordInfo, sizeof(struRecordInfo), szFileName,szRetUrl,1024);
    CString strTest(szRetUrl);
    if (-1 == m_lUploadHandle)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile UPLOAD_RECORD_FILE");
        AfxMessageBox("NET_DVR_UploadFile failed");
       		NET_DVR_UploadClose(m_lUploadHandle);
                 GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("Upload File Failed!");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile UPLOAD_RECORD_FILE");
        GetDlgItem(IDC_STATIC_RET_NAME)->SetWindowText(szRetUrl);
          m_csFileName = szRetUrl;
         //sprintf(m_csFileName,"%s",szRetUrl);
     
        m_timerHandle =	SetTimer(UPLOAD_RECORD_TIMER, 50, NULL);
        //由于证书文件只有几KB，很小，故短暂sleep，就能上传完毕
        Sleep(500);
    }
    
    UpdateData(FALSE);

}

void CDlgUploadFile::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgUploadFile::AA()
{
    UpdateData(TRUE);
       
    NET_DVR_TIME_EX struBeginTime = {0};
    NET_DVR_TIME_EX struEndTime = {0};


    if(m_strFileName.GetLength() == 0)
    {
        return;
    }

    if (m_strFileName.Find("_D"))
    {
        return ;
    }
    DWORD dwLen =   m_strFileName.GetLength() - m_strFileName.Find("_D");
    CString strData = m_strFileName.Right(dwLen);

    strData = strData.Left(31);
   
    strData = strData.Right(29);

    struBeginTime.wYear = atoi(strData.Left(4));
    strData = strData.Right(strData.GetLength() - 4);
    struBeginTime.byMonth = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
    struBeginTime.byDay = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
    struBeginTime.byHour = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
    struBeginTime.byMinute = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
    struBeginTime.bySecond = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 3);

     struEndTime.wYear = atoi(strData.Left(4));
     strData = strData.Right(strData.GetLength() - 4);
     struEndTime.byMonth = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
     struEndTime.byDay = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
     struEndTime.byHour = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
     struEndTime.byMinute = atoi(strData.Left(2));
     strData = strData.Right(strData.GetLength() - 2);
     struEndTime.bySecond = atoi(strData.Left(2));
   
     
     CTime timeBeginTmp(struBeginTime.wYear, struBeginTime.byMonth, struBeginTime.byDay,
         struBeginTime.byHour, struBeginTime.byMinute, struBeginTime.bySecond);
     
     CTime timeEndTmp(struEndTime.wYear, struEndTime.byMonth, struEndTime.byDay,
         struEndTime.byHour, struEndTime.byMinute, struEndTime.bySecond);
     
     m_tmBeginDate = timeBeginTmp;
     m_tmBeginTime = timeBeginTmp;
     
     m_tmEndDate = timeEndTmp;
     m_tmEndTime = timeEndTmp;


     //解析Camera ID
   
     strData = m_strFileName.Right(m_strFileName.GetLength() - m_strFileName.Find("_") -1);
     dwLen = strData.Find("_D");
     strData = strData.Left(dwLen);

     m_strCameraID = strData;
     
     UpdateData(FALSE);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgUploadFile::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgUploadFile::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
    char szLan[128] = {0};
   if (nIDEvent == UPLOAD_RECORD_TIMER)
    {
        DWORD dwProgress = 0;
        int state = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);
        
        if (state == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
           // m_strUploadStatus.Format(szLan);
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (state == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:%d", "Is uploading,progress:%d");
           
            CString	strUploadStatus;
            strUploadStatus.Format(szLan, dwProgress);
             GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(strUploadStatus);
        }
        else if (state == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (state == 4)
        {
            g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        
        // 		g_StringLanType(szLan, "上传状态%d", "Upload successfully");
        // 		m_strUploadStatus.Format(szLan,state);
        if (state != 2)
        {        
            KillTimer(UPLOAD_RECORD_TIMER);
            NET_DVR_UploadClose(m_lUploadHandle);
        }
    }
    
    
    UpdateData(FALSE);
    
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgUploadFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbAudioEncType.SetCurSel(0);
    m_cmbFormatType.SetCurSel(0);
    m_cmdVedioEncType.SetCurSel(0);
    m_cmbFileType.SetCurSel(0);

    CTime timeCur = CTime::GetCurrentTime();
    CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
    CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
    m_tmBeginDate = timeStart;
    m_tmBeginTime = timeStart;
    m_tmEndDate = timeStop;
    m_tmEndTime = timeStop;

    	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
