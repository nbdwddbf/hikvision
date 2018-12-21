// DlgUploadCalibrationFile.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgUploadCalibrationFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadCalibrationFile dialog


CDlgUploadCalibrationFile::CDlgUploadCalibrationFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUploadCalibrationFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUploadCalibrationFile)
	m_strFileName = _T("");
	//}}AFX_DATA_INIT
    m_lUserID = -1;
    m_iDevIndex = -1;
    m_lUploadHandle = -1;
}


void CDlgUploadCalibrationFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUploadCalibrationFile)
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUploadCalibrationFile, CDialog)
	//{{AFX_MSG_MAP(CDlgUploadCalibrationFile)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_FILE, OnButtonBrowseFile)
	ON_BN_CLICKED(ID_UPLOAD, OnUpload)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL2, OnCancel2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadCalibrationFile message handlers

void CDlgUploadCalibrationFile::OnButtonBrowseFile() 
{
	// TODO: Add your control notification handler code here
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFileName = dlg.GetPathName();
        
        UpdateData(FALSE);
	}
}

void CDlgUploadCalibrationFile::OnUpload() 
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
        g_StringLanType(szLan, "标定文件为空", "Calibration file is empty");
        AfxMessageBox(szLan);
    }
    cFile.Close();
  
    m_lUploadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_CALIBRATION_FILE, NULL, 0, szFileName, NULL, 0);
    if (-1 == m_lUploadHandle)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_CALIBRATION_FILE");
        AfxMessageBox("NET_DVR_UploadFile_V40 failed");
        NET_DVR_UploadClose(m_lUploadHandle);
        GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("Upload CalibrationFile Failed!");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_CALIBRATION_FILE");
    }
    
    UpdateData(FALSE);
	
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgUploadCalibrationFile::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgUploadCalibrationFile::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default

    char szLan[128] = {0};
    if (nIDEvent == UPLOAD_CALIBRATION_FILE_TIMER)
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
            KillTimer(UPLOAD_CALIBRATION_FILE_TIMER);
            NET_DVR_UploadClose(m_lUploadHandle);
        }
    }
    
    
    UpdateData(FALSE);
    
	CDialog::OnTimer(nIDEvent);
}

void CDlgUploadCalibrationFile::OnCancel2() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
