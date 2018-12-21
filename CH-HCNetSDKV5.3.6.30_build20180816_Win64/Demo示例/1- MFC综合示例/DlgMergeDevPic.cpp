// DlgMergeDevPic.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMergeDevPic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDevPic dialog


CDlgMergeDevPic::CDlgMergeDevPic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMergeDevPic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMergeDevPic)
	m_bFlash = FALSE;
	m_bPicExist = FALSE;
	m_bShow = FALSE;
	m_bTranslucent = FALSE;
	m_dwHeight = 0;
	m_csPicName = _T("");
	m_csPicPath = _T("");
	m_dwWidth = 0;
	m_dwX = 0;
	m_dwY = 0;
	m_csUploadProgress = _T("");
	m_dwPicHeight = 0;
	m_dwPicWidth = 0;
    m_lUploadByBufHandle = -1;
    m_dwSendBufLen = 0;
    m_pszUploadPicBuf = NULL;
	//}}AFX_DATA_INIT
    memset(m_struOutputPicCfg, 0 , sizeof(m_struOutputPicCfg)); 
}


void CDlgMergeDevPic::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMergeDevPic)
    DDX_Control(pDX, IDC_COMBO_PIC_WIN_NO, m_comboPicWinNo);
    DDX_Control(pDX, IDC_COMBO_PIC_NO, m_comboPicNo);
    DDX_Control(pDX, IDC_COMBO_OUTPUT_NO, m_comboOutputNo);
    DDX_Check(pDX, IDC_CHK_FALSH, m_bFlash);
    DDX_Check(pDX, IDC_CHK_PIC_EXIST, m_bPicExist);
    DDX_Check(pDX, IDC_CHK_SHOW, m_bShow);
    DDX_Check(pDX, IDC_CHK_TRANSLUCENT, m_bTranslucent);
    DDX_Text(pDX, IDC_EDIT_HEIGHT, m_dwHeight);
    DDX_Text(pDX, IDC_EDIT_PIC_NAME, m_csPicName);
    DDX_Text(pDX, IDC_EDIT_PIC_PATH, m_csPicPath);
    DDX_Text(pDX, IDC_EDIT_WIDTH, m_dwWidth);
    DDX_Text(pDX, IDC_EDIT_X, m_dwX);
    DDX_Text(pDX, IDC_EDIT_Y, m_dwY);
    DDX_Text(pDX, IDC_STATIC_UPLOAD_PROGRESS, m_csUploadProgress);
    DDX_Text(pDX, IDC_EDIT_PIC_HEIGHT, m_dwPicHeight);
    DDX_Text(pDX, IDC_EDIT_PIC_WIDTHMERGE, m_dwPicWidth);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_UPLOAD_PIC_TYPE, m_cmUploadSendPicType);
}


BEGIN_MESSAGE_MAP(CDlgMergeDevPic, CDialog)
	//{{AFX_MSG_MAP(CDlgMergeDevPic)
	ON_CBN_SELCHANGE(IDC_COMBO_PIC_NO, OnSelchangeComboPicNo)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_UPLOAD, OnBtnUpload)
	ON_BN_CLICKED(IDC_BTN_GET_PIC_INFO, OnBtnGetPicInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_NO, OnSelchangeComboOutputNo)
	ON_CBN_SELCHANGE(IDC_COMBO_PIC_WIN_NO, OnSelchangeComboPicWinNo)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIST, OnBtnExist)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SET_PIC_INFO, OnBtnSetPicInfo)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_UPLOAD_BY_BUF, OnBnClickedBtnUploadByBuf)
    ON_WM_DESTROY()
END_MESSAGE_MAP()


DWORD WINAPI CDlgMergeDevPic::PicUpLoadByBufThread(LPVOID pParam)
{
    CDlgMergeDevPic *pThis = (CDlgMergeDevPic*)pParam;
    
    DWORD iPos = 0;
    int iRet = -1;
    CString csStr = "";
    CString szUpProgress = "";
    BOOL bKeepLoop = TRUE;
    while (bKeepLoop)
    {
        if (pThis->m_lUploadByBufHandle < 0)
        {
            bKeepLoop = FALSE;
        }
        iRet = NET_DVR_GetUploadState(pThis->m_lUploadByBufHandle, &iPos);
        if (iRet == -1)
        {
            continue;
        }
        switch (iRet)
        {
        case 1:
            csStr = _T("上传成功");
            bKeepLoop = FALSE;
            pThis->MessageBox(csStr);
            break;
        case 2:
            csStr = _T("正在上传");
            break;
        case 3:
            csStr = _T("上传失败");
            bKeepLoop = FALSE;
            pThis->MessageBox(csStr);
            break;
        case 4:
            csStr = _T("网络断开，状态未知");
            bKeepLoop = FALSE;
            pThis->MessageBox(csStr);
            break;
        default:
            break;
        }
        szUpProgress.Format("%s...%d", csStr, iPos);
        pThis->SetDlgItemTextA(IDC_STATIC_UPLOAD_PROGRESS, szUpProgress);
        if (iPos == 100)
        {
            bKeepLoop = FALSE;
            g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Upload finish!");
            if (!NET_DVR_UploadClose(pThis->m_lUploadByBufHandle))
            {
                g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose Failed");
                pThis->m_lUploadByBufHandle = -1;
                return -1;
            }
            else
            {
                g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose succ");
                iPos = 0;
            }
            pThis->m_lUploadByBufHandle = -1;
        }
        Sleep(10);
    }

    if (pThis->m_lUploadByBufHandle >= 0)
    {
        NET_DVR_UploadClose(pThis->m_lUploadByBufHandle);
        pThis->m_lUploadByBufHandle = -1;
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDevPic message handlers

BOOL CDlgMergeDevPic::OnInitDialog() 
{
    CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    //控件初始化
    int i = 0;

    for (i = 0; i < 16; i++)
    {
        sprintf(m_szLan, "%d", i + 1);
        m_comboPicNo.AddString(m_szLan);
        m_comboPicNo.SetItemData(i, i+1); 
    }

    NET_DVR_DISPLAYCFG struOutput = {0};
    DWORD dwReturned = 0;

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYNO, 0, &struOutput, sizeof(struOutput), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYNO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEOWALLDISPLAYNO");

        int iBnc = 0;
        int iVga = 0;
        int iHdmi = 0;
        int iDvi = 0;
        int iUnknown = 0;

        for (i = 0; i < MAX_DISPLAY_NUM; i++)
        {
            switch (struOutput.struDisplayParam[i].byDispChanType)
            {
            case 1:
                sprintf(m_szLan, "BNC%d", iBnc + 1);                
                iBnc++;
            	break;
            case 2:
                sprintf(m_szLan, "VGA%d", iVga + 1);
                iVga++;
                break;
            case 3:
                sprintf(m_szLan, "HDMI%d", iHdmi + 1);
                iHdmi++;
                break;
            case 4:
                sprintf(m_szLan, "DVI%d", iDvi + 1);
                iDvi++;
                break;
            case 0xff:
                break;
            default:
                sprintf(m_szLan, "Unknown%d", iUnknown + 1);
                break;                
            }

            if (struOutput.struDisplayParam[i].byDispChanType != 0xff)
            {
                int iIndex = m_comboOutputNo.AddString(m_szLan);
                m_comboOutputNo.SetItemData(iIndex, struOutput.struDisplayParam[i].dwDisplayNo);
            }
        }
    }

    memset(m_struOutputPicCfg, 0, sizeof(m_struOutputPicCfg));

    for (i = 0; i < 4; i++)
    {
        m_struOutputPicCfg[i].dwSize = sizeof(m_struOutputPicCfg[i]);
    }
	
    m_lUploadHandle = -1;

    SetTimer(NULL, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMergeDevPic::OnSelchangeComboPicNo() 
{
	// TODO: Add your control notification handler code here
    OnBtnGetPicInfo();	
}

void CDlgMergeDevPic::OnBtnBrowse() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    CFileException fileException;
    static char szFilter[]="ALL File(*.*)|*.*||";
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
        szFilter);
    
    if (dlg.DoModal()==IDOK)
    {
        m_csPicPath = dlg.GetPathName();   
        UpdateData(FALSE);
	}
}

void CDlgMergeDevPic::OnBtnUpload() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    memset(&m_struPicCfg, 0, sizeof(m_struPicCfg));
    m_struPicCfg.dwSize = sizeof(m_struPicCfg);
    m_struPicCfg.byUseType = 4;
    m_struPicCfg.bySequence = m_comboPicNo.GetItemData(m_comboPicNo.GetCurSel());
    m_struPicCfg.struBasemapCfg.byMapNum = 1;
    m_struPicCfg.struBasemapCfg.byScreenIndex = 1;
    m_struPicCfg.struBasemapCfg.wSourHeight = m_dwPicHeight;
    m_struPicCfg.struBasemapCfg.wSourWidth = m_dwPicWidth;    
    strncpy((char *)m_struPicCfg.sPicName, (LPCSTR)m_csPicName, sizeof(m_struPicCfg.sPicName));
    m_struPicCfg.sPicName[m_csPicName.GetLength()] = 0; 
    m_lUploadHandle = NET_DVR_PicUpload(m_lUserID, m_csPicPath, &m_struPicCfg);
    if (m_lUploadHandle == -1)
    {
        MessageBox("NET_DVR_PicUpload failed");
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PicUpload failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PicUpload succ");
	}	
}

void CDlgMergeDevPic::OnBtnGetPicInfo() 
{
	// TODO: Add your control notification handler code here
    int iSel = m_comboPicNo.GetCurSel();

    if (iSel == CB_ERR)
    {
        return;
    }

    DWORD dwReturned = 0;
    NET_DVR_OUTPUT_PIC_INFO struPicInfo = {0};

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_OUTPUT_PIC_INFO, iSel + 1, &struPicInfo, sizeof(struPicInfo), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_PIC_INFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_PIC_INFO");
        m_bPicExist = struPicInfo.byUsed;
        m_csPicName = struPicInfo.sPicName;
        UpdateData(FALSE);
    }	
}

void CDlgMergeDevPic::OnSelchangeComboOutputNo() 
{
	// TODO: Add your control notification handler code here
    int iSel = m_comboOutputNo.GetCurSel();

    if (iSel == CB_ERR)
    {
        return;
    }

    DWORD dwOutputNo = m_comboOutputNo.GetItemData(iSel);

    DWORD dwReturned = 0;
    char sBuffer[4 + sizeof(m_struOutputPicCfg)] = {0};

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_OUTPUT_ALL_PIC_WIN_CFG, dwOutputNo, sBuffer, sizeof(sBuffer), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_ALL_PIC_WIN_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_ALL_PIC_WIN_CFG");
        memcpy(m_struOutputPicCfg, sBuffer + 4, sizeof(m_struOutputPicCfg));
        m_comboPicWinNo.SetCurSel(0); 
        UpdateData(FALSE); 
    }

    OnSelchangeComboPicWinNo();	
}

void CDlgMergeDevPic::OnSelchangeComboPicWinNo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    int iSel = m_comboPicWinNo.GetCurSel();

    if (iSel == CB_ERR)
    {
        return;
    }

    m_bShow = m_struOutputPicCfg[iSel].byEnable;
    m_bFlash = m_struOutputPicCfg[iSel].byFlash;
    m_bTranslucent = m_struOutputPicCfg[iSel].byTranslucent;
    m_dwX = m_struOutputPicCfg[iSel].struRect.dwXCoordinate;
    m_dwY = m_struOutputPicCfg[iSel].struRect.dwYCoordinate;
    m_dwWidth = m_struOutputPicCfg[iSel].struRect.dwWidth;
    m_dwHeight = m_struOutputPicCfg[iSel].struRect.dwHeight;
    
    UpdateData(FALSE);	
}

void CDlgMergeDevPic::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int iOutputSel = m_comboOutputNo.GetCurSel();
    int iOutputPicWinSel = m_comboPicWinNo.GetCurSel();

    if (iOutputSel == CB_ERR || iOutputPicWinSel == CB_ERR)
    {
        return;
    }

    DWORD dwOutputNo = m_comboOutputNo.GetItemData(iOutputSel);
    DWORD dwPicWinNo = 0x01000000 | (dwOutputNo << 16) | (iOutputPicWinSel + 1);

    m_struOutputPicCfg[iOutputPicWinSel].dwSize = sizeof(m_struOutputPicCfg[0]);
    m_struOutputPicCfg[iOutputPicWinSel].byEnable = m_bShow;
    m_struOutputPicCfg[iOutputPicWinSel].byFlash = m_bFlash;
    m_struOutputPicCfg[iOutputPicWinSel].byTranslucent = m_bTranslucent;
    m_struOutputPicCfg[iOutputPicWinSel].struRect.dwXCoordinate = m_dwX;
    m_struOutputPicCfg[iOutputPicWinSel].struRect.dwYCoordinate = m_dwY;
    m_struOutputPicCfg[iOutputPicWinSel].struRect.dwWidth = m_dwWidth;
    m_struOutputPicCfg[iOutputPicWinSel].struRect.dwHeight = m_dwHeight;
    m_struOutputPicCfg[iOutputPicWinSel].dwOutputPicNo = m_comboPicNo.GetItemData(m_comboPicNo.GetCurSel()) ;
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_OUTPUT_PIC_WIN_CFG, dwPicWinNo, &m_struOutputPicCfg[iOutputPicWinSel], sizeof(m_struOutputPicCfg[iOutputPicWinSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_PIC_WIN_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_PIC_WIN_CFG");
    }
	
}

void CDlgMergeDevPic::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    int iOutputSel = m_comboOutputNo.GetCurSel();
    int iOutputPicWinSel = m_comboPicWinNo.GetCurSel();
    
    if (iOutputSel == CB_ERR || iOutputPicWinSel == CB_ERR)
    {
        return;
    }
    DWORD dwReturned = 0;
    DWORD dwOutputNo = m_comboOutputNo.GetItemData(iOutputSel);
    DWORD dwPicWinNo = 0x01000000 | (dwOutputNo << 16) | (iOutputPicWinSel + 1);

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_OUTPUT_PIC_WIN_CFG, dwPicWinNo, &m_struOutputPicCfg[iOutputPicWinSel], sizeof(m_struOutputPicCfg[iOutputPicWinSel]), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_PIC_WIN_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_PIC_WIN_CFG");
    }

    m_bShow = m_struOutputPicCfg[iOutputPicWinSel].byEnable;
    m_bFlash = m_struOutputPicCfg[iOutputPicWinSel].byFlash;
    m_bTranslucent = m_struOutputPicCfg[iOutputPicWinSel].byTranslucent;
    m_dwX = m_struOutputPicCfg[iOutputPicWinSel].struRect.dwXCoordinate;
    m_dwY = m_struOutputPicCfg[iOutputPicWinSel].struRect.dwYCoordinate;
    m_dwWidth = m_struOutputPicCfg[iOutputPicWinSel].struRect.dwWidth;
    m_dwHeight = m_struOutputPicCfg[iOutputPicWinSel].struRect.dwHeight;

    UpdateData(FALSE);	
}

void CDlgMergeDevPic::OnBtnExist() 
{
	// TODO: Add your control notification handler code here
    KillTimer(NULL);

    OnCancel();	
}

void CDlgMergeDevPic::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
    int iSel = m_comboPicNo.GetCurSel();
    if (iSel == CB_ERR)
    {
        return;
    }

    iSel++;

    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_DELETE_OUPUT_PIC, &iSel, sizeof(iSel)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DELETE_OUPUT_PIC");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_DELETE_OUPUT_PIC");
    }	
}


#if (_MSC_VER >= 1500)	//vs2008
void CDlgMergeDevPic::OnTimer(UINT_PTR nIDEvent) 
#else
void CDlgMergeDevPic::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
    int iPos = 0;
    CString csStr = "";
    CString szUpProgress = "";
    char sTemp[128] = {0};

    int iRet = NET_DVR_GetPicUploadState(m_lUploadHandle);
    if (1 == iRet || 3 == iRet)
    {
        if (m_lUploadHandle != -1)
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
    }
    switch (iRet)
    {
    case 1:
        csStr = _T("上传成功");
        SetDlgItemTextA(IDC_STATIC_UPLOAD_PROGRESS, csStr);
        MessageBox(csStr);
        break;
    case 2:
        csStr = _T("正在上传");
        break;
    case 3:
        csStr = _T("上传失败");
        SetDlgItemTextA(IDC_STATIC_UPLOAD_PROGRESS, csStr);
        MessageBox(csStr);
        break;
    case 4:
        csStr = _T("上传异常");
        MessageBox(csStr);
        break;
    default:
        break;
    }

    iPos = NET_DVR_GetPicUploadProgress(m_lUploadHandle);
    if (iPos <= 0)
    {
        return;
    }
    szUpProgress.Format("%s...%d", csStr, iPos);
    SetDlgItemTextA(IDC_STATIC_UPLOAD_PROGRESS, szUpProgress);
    if (iPos == 100)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Upload finish!");
        if (m_lUploadHandle != -1)
        {
            if (!NET_DVR_CloseUploadHandle(m_lUploadHandle))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CloseUploadHandle Failed");
                return;
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CloseUploadHandle succ");
                iPos = 0;
                m_lUploadHandle = -1;
            }
        }
    }

	CDialog::OnTimer(nIDEvent);
}

void CDlgMergeDevPic::OnBtnSetPicInfo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int iSel = m_comboPicNo.GetCurSel();

    if (iSel == CB_ERR)
    {
        return;
    }

    NET_DVR_OUTPUT_PIC_INFO struPicInfo = {0};

    struPicInfo.dwSize = sizeof(struPicInfo);

    memcpy(struPicInfo.sPicName, m_csPicName, min(NAME_LEN, m_csPicName.GetLength()));

    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_OUTPUT_PIC_INFO, iSel + 1, &struPicInfo, sizeof(struPicInfo)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_PIC_INFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_PIC_INFO");
    }
}


void CDlgMergeDevPic::OnBnClickedBtnUploadByBuf()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    memset(&m_struPicCfg, 0, sizeof(m_struPicCfg));
    m_struPicCfg.dwSize = sizeof(m_struPicCfg);
    m_struPicCfg.byUseType = 4;
    m_struPicCfg.bySequence = m_comboPicNo.GetItemData(m_comboPicNo.GetCurSel());
    m_struPicCfg.struBasemapCfg.byMapNum = 1;
    m_struPicCfg.struBasemapCfg.byScreenIndex = 1;
    m_struPicCfg.struBasemapCfg.wSourHeight = m_dwPicHeight;
    m_struPicCfg.struBasemapCfg.wSourWidth = m_dwPicWidth;
    strncpy((char *)m_struPicCfg.sPicName, (LPCSTR)m_csPicName, sizeof(m_struPicCfg.sPicName));
    m_struPicCfg.sPicName[m_csPicName.GetLength()] = 0;

    if (m_lUploadByBufHandle <= -1)
    {
        m_lUploadByBufHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_PIC_BY_BUF, NULL, 0, NULL, NULL, 0);
        if (m_lUploadByBufHandle == -1)
        {
            MessageBox("NET_DVR_UploadFile_V40 failed");
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 failed");
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 SUCC");
        }
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 handle=[%d]", m_lUploadByBufHandle);

    if (m_csPicPath == "")
    {
        MessageBox("Please choose picture file!!");
        return;
    }

    if (ReadPictureInfoToBuf((const char*)m_csPicPath) == FALSE)
    {
        delete[] m_pszUploadPicBuf;
        m_pszUploadPicBuf = NULL;
        m_dwSendBufLen = 0;
        return;
    }

    NET_DVR_SEND_PARAM_IN strSendParamIn = { 0 };
    strSendParamIn.pSendData = m_pszUploadPicBuf;
    strSendParamIn.dwSendDataLen = m_dwSendBufLen;
    strSendParamIn.pSendAppendData = (BYTE*)&m_struPicCfg;
    strSendParamIn.dwSendAppendDataLen = sizeof(NET_DVR_PICTURECFG);
    strSendParamIn.byPicType = m_cmUploadSendPicType.GetCurSel() + 1;
    if (NET_DVR_UploadSend(m_lUploadByBufHandle, &strSendParamIn, NULL) < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadSend error!");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadSend [%d] SUCC!", strSendParamIn.dwSendDataLen + strSendParamIn.dwSendAppendDataLen);
    }

    m_dwSendBufLen = 0;
    delete[] m_pszUploadPicBuf;
    m_pszUploadPicBuf = NULL;

    //以下代码创建线程获取上传进度
    DWORD dwThreadID = 0;
    m_hPicUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(PicUpLoadByBufThread), this, 0, &dwThreadID);
    if (m_hPicUpLoadThread == NULL)
    {
        char szLan[128] = { 0 };
        g_StringLanType(szLan, "开启获取图片上传进度线程失败!", "open get UpLoad picture progress thread Fail!");
        AfxMessageBox(szLan);
        return;
    }
}


BOOL CDlgMergeDevPic::ReadPictureInfoToBuf(const char* sFilePath)
{
    if (sFilePath == NULL)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "read picture information to buffer error, filePath is null");
        return FALSE;
    }
    FILE* pFile = fopen(sFilePath, "rb");
    if (pFile == NULL)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "open picture file error!!");
        return FALSE;
    }

    long lFilelength;
    fseek(pFile, 0L, SEEK_END);
    lFilelength = ftell(pFile);
    fseek(pFile, 0L, SEEK_SET);

    if (lFilelength >= MAX_UPLOAD_PIC_LEN)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "picture is too long!!");
        fclose(pFile);
        return FALSE;
    }
    
    if (0 != m_dwSendBufLen || NULL != m_pszUploadPicBuf)
    {
        delete[] m_pszUploadPicBuf;
        m_pszUploadPicBuf = NULL;
        m_dwSendBufLen = 0;
    }
    m_pszUploadPicBuf = new BYTE[lFilelength];
    m_dwSendBufLen = lFilelength;

    memset(m_pszUploadPicBuf, 0, m_dwSendBufLen);
    
    fread(m_pszUploadPicBuf, lFilelength, 1, pFile);
    fclose(pFile);
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "read picture to buffer SUCC!!");

    return TRUE;
}


void CDlgMergeDevPic::OnDestroy()
{
    if (m_lUploadByBufHandle >= 0)
    {
        NET_DVR_UploadClose(m_lUploadByBufHandle);
        m_lUploadByBufHandle = -1;
    }

    CDialog::OnDestroy();

    // TODO:  在此处添加消息处理程序代码
}


