// JPEGPicDownload.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgSmartSearchPicture.h"
#include "Picture.h"
#include "DlgPictureUpload.h"
#include "DlgVcaSingleProcImg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgSmartSearchPicture *g_pDlgRemoteFile;

/////////////////////////////////////////////////////////////////////////////
// CDlgSmartSearchPicture dialog
// extern	SERVER_INFO serverinfo[MAXIPNUMBER];
// extern	CLIENTPARAM	ClientParam;
// extern	LOCAL_PARAM ClientParam;
// LOCAL_PARAM
CPicture *pSmartPicture = NULL;

UINT GetSmartPicThread(LPVOID pParam)
{
	CDlgSmartSearchPicture *GetPic = (CDlgSmartSearchPicture *)pParam;
	CString csFileName;
	CString csPicTime;
	CString csCardNum;
	CString csTemp,csDir;
	char nFileName[256] = {0};
	char sMessageCn[256] = {0};
	char sMessageEn[256] = {0};
	int fileselpos = 0;
	
	char szLan[256] = {0};

	while (GetPic->pos)
	{
		if (!GetPic->m_bDown)
		{			
			break;	
		}
		fileselpos = GetPic->m_PicList.GetNextSelectedItem(GetPic->pos);
		csFileName.Format("%s",GetPic->m_PicList.GetItemText(fileselpos,0));
		if (csFileName.IsEmpty())
		{
			g_StringLanType(szLan, "下载", "Download");
			GetPic->GetDlgItem(IDC_DOWNLOAD)->SetWindowText(szLan);
			GetPic->GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_HIDE);
			GetPic->m_downProgress.SetPos(0);
			GetPic->m_bDown = FALSE;
			CloseHandle(GetPic->m_hGetThread);
			GetPic->m_hGetThread = NULL;
			g_StringLanType(szLan, "文件名为空!", "File name is blank!");
			AfxMessageBox(szLan);
			return 1;
		}
			
		csPicTime.Format("%s", GetPic->m_PicList.GetItemText(fileselpos,2));
		csCardNum.Format("%s", GetPic->m_PicList.GetItemText(fileselpos,3));
		sprintf(GetPic->filenamedownload, "%s", csFileName);
		
		csDir.Format("%s\\", g_struLocalParam.chPictureSavePath);

		BOOL bShowIpv6 = g_ValidIPv6((BYTE*)g_struDeviceInfo[GetPic->m_iDeviceIndex].chDeviceIP);
		if (bShowIpv6)
		{
			sprintf(nFileName, "%s_ipv6_%02d_D%s_%s_%d.jpg",csDir, GetPic->m_iChannel, csPicTime,csCardNum, fileselpos + 1);
		} 
		else
		{
			sprintf(nFileName, "%s%s_%02d_D%s_%s_%d.jpg",csDir, g_struDeviceInfo[GetPic->m_iDeviceIndex].chDeviceIP, GetPic->m_iChannel, csPicTime,csCardNum, fileselpos + 1);
		}
		
    	if (NET_DVR_GetPicture(GetPic->m_lServerID, GetPic->filenamedownload, nFileName))
		{			
     		Sleep(10);
			GetPic->nDownPics++;
			GetPic->m_downProgress.SetPos(GetPic->nDownPics*100/GetPic->nSelPics);
		}
	}
	
	GetPic->m_downProgress.SetPos(0);
	g_StringLanType(szLan, "下载", "Download");
	GetPic->GetDlgItem(IDC_DOWNLOAD)->SetWindowText(szLan);
	GetPic->GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_HIDE);
	GetPic->m_bDown = FALSE;
	CloseHandle(GetPic->m_hGetThread);
	GetPic->m_hGetThread = NULL;
	sprintf(sMessageCn, "选择了 %d 张图片,下载了 %d 张图片", GetPic->nSelPics, GetPic->nDownPics);
	sprintf(sMessageEn, "selected %d picture，downloaded %d picture", GetPic->nSelPics, GetPic->nDownPics);
	g_StringLanType(szLan, sMessageCn, sMessageEn);
	AfxMessageBox(szLan);	
	GetPic->nSelPics = 0;
	GetPic->nDownPics = 0;	
	return 0;
}


UINT SmartSearchPicThread(LPVOID pParam)
{
    CDlgSmartSearchPicture *RPic = (CDlgSmartSearchPicture *)pParam;
    LONG bRet = -1;
    CString tempstring;
    char tempfile[100];
    
    char szLan[256] = {0};
 
    NET_DVR_SMART_SEARCH_PIC_RET  struSearchRet = {0};

    while (1)
    {	
        if (!RPic->m_bSearchDown)
        {
            return 0;	
        }
        bRet = NET_DVR_FindNextSmartPicture(RPic->m_lFileHandle, &struSearchRet);
        if (bRet == NET_DVR_FILE_SUCCESS)
        {	
            strncpy(tempfile,struSearchRet.sFileName,PICTURE_NAME_LEN);
            RPic->m_PicList.InsertItem(RPic->m_iFileNum,tempfile,0);	

            
            if (struSearchRet.wPicType ==0)
            {
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,1,"Vehicle"); 

                
            }
            else if (struSearchRet.wPicType == 1 || struSearchRet.wPicType == 2)
            {
                if (struSearchRet.wPicType == 1)
                {
                    RPic->m_PicList.SetItemText(RPic->m_iFileNum,1,"Human Feature");
                }
                else if (struSearchRet.wPicType == 2)
                {   
                    RPic->m_PicList.SetItemText(RPic->m_iFileNum,1,"Find Pic By Pic");
                }
                else
                {
                    RPic->m_PicList.SetItemText(RPic->m_iFileNum,1,"Unkown");
                }
            }
            else if (struSearchRet.wPicType == 3 || struSearchRet.wPicType == 4 || struSearchRet.wPicType == 5|| \
                struSearchRet.wPicType == 6 || struSearchRet.wPicType == 7 || struSearchRet.wPicType == 8|| \
                struSearchRet.wPicType == 9 || struSearchRet.wPicType == 10 || struSearchRet.wPicType == 11  ||\
                struSearchRet.wPicType == 12 )
            {
                if (struSearchRet.wPicType == 3)
                {
                    g_StringLanType(szLan,"穿越警戒线","穿越警戒线");
                }
                else if (struSearchRet.wPicType == 4)
                {   
                    g_StringLanType(szLan,"区域入侵","区域入侵");
                }
                else if (struSearchRet.wPicType == 5)
                {
                    g_StringLanType(szLan,"物品遗留","物品遗留");
                }
                else if (struSearchRet.wPicType == 6)
                {   
                    g_StringLanType(szLan,"物品拿取","物品拿取");
                }
                else if (struSearchRet.wPicType == 7)
                {
                    g_StringLanType(szLan,"进入区域","进入区域");
                }
                else if (struSearchRet.wPicType == 8)
                {   
                    g_StringLanType(szLan,"离开区域","离开区域");
                }
                else if (struSearchRet.wPicType == 9)
                {
                    g_StringLanType(szLan,"非法停车","非法停车");
                }
                else if (struSearchRet.wPicType == 10)
                {   
                    g_StringLanType(szLan,"徘徊","徘徊");
                }
                else if (struSearchRet.wPicType == 11)
                {
                    g_StringLanType(szLan,"人员聚集","人员聚集");
                }
                else if (struSearchRet.wPicType == 12)
                {   
                    g_StringLanType(szLan,"快速移动","快速移动");
                }
                
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,1,szLan);
            }
            else  
            {	
                sprintf(szLan,"Unkown Type[%d]",struSearchRet.wPicType);
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,1,szLan);
            }

            tempstring.Format("%d",struSearchRet.dwFileSize);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum,2,tempstring);
            
            tempstring.Format("%04d%02d%02d%02d%02d%02d",struSearchRet.struTime.wYear, struSearchRet.struTime.byMonth,\
                struSearchRet.struTime.byDay,struSearchRet.struTime.byHour,\
                struSearchRet.struTime.byMinute,struSearchRet.struTime.bySecond);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum,3,tempstring);

            if (struSearchRet.wPicType ==0)
            {               
                tempstring.Format("%s",struSearchRet.uPicFeature.struPlateInfo.sLicense);
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,4,tempstring);
                
                tempstring.Format("X:%f,Y:%f,Width:%f,Height:%f",struSearchRet.uPicFeature.struPlateInfo.struPlateRect.fX*1000,\
                    struSearchRet.uPicFeature.struPlateInfo.struPlateRect.fY*1000,\
                    struSearchRet.uPicFeature.struPlateInfo.struPlateRect.fWidth*1000, struSearchRet.uPicFeature.struPlateInfo.struPlateRect.fHeight*1000);
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,5,tempstring);     
                
            }
            else if (struSearchRet.wPicType == 1 || struSearchRet.wPicType == 2)
            {
                tempstring.Format("%d",struSearchRet.uPicFeature.struFaceSubInfo.dwSimilarity);
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,4,tempstring);
                
                tempstring.Format("X:%f,Y:%f,Width:%f,Height:%f",struSearchRet.uPicFeature.struFaceSubInfo.struVcaRect.fX *1000,\
                    struSearchRet.uPicFeature.struFaceSubInfo.struVcaRect.fY*1000,\
                    struSearchRet.uPicFeature.struFaceSubInfo.struVcaRect.fWidth*1000, struSearchRet.uPicFeature.struFaceSubInfo.struVcaRect.fHeight*1000);
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,5,tempstring);
            }
            else if (struSearchRet.wPicType == 3 || struSearchRet.wPicType == 4 || struSearchRet.wPicType == 5|| \
                struSearchRet.wPicType == 6 || struSearchRet.wPicType == 7 || struSearchRet.wPicType == 8|| \
                struSearchRet.wPicType == 9 || struSearchRet.wPicType == 10 || struSearchRet.wPicType == 11  ||\
                struSearchRet.wPicType == 12 )
            {                
                tempstring.Format("X:%f,Y:%f,Width:%f,Height:%f",struSearchRet.uPicFeature.struBehavior.struVcaRect.fX*1000,\
                    struSearchRet.uPicFeature.struBehavior.struVcaRect.fY*1000,\
                    struSearchRet.uPicFeature.struBehavior.struVcaRect.fWidth*1000, struSearchRet.uPicFeature.struBehavior.struVcaRect.fHeight*1000);
                RPic->m_PicList.SetItemText(RPic->m_iFileNum,4,tempstring);
            }
            
                 RPic->m_iFileNum++;
            TRACE("m_iFileNum is %d\n", RPic->m_iFileNum);
        }
        else
        {
            if (bRet == NET_DVR_ISFINDING)
            {
                Sleep(5);
                continue;
            }
            if ( (bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND) )
            {
                g_StringLanType(szLan, "查找", "search");
                RPic->GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
                RPic->m_bSearchDown = FALSE;
                (RPic->GetDlgItem(IDC_STATICSTATE))->ShowWindow(SW_HIDE);
                g_StringLanType(szLan, "查找到图片数:", "Searched picture sum:");
                tempstring.Format("%s%d", szLan, RPic->m_iFileNum);
                AfxMessageBox(tempstring);
                RPic->m_iFileNum = 0;
                break;
            }
            else
            {
                g_StringLanType(szLan, "查找", "search");
                RPic->GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
                RPic->m_bSearchDown = FALSE;
                (RPic->GetDlgItem(IDC_STATICSTATE))->ShowWindow(SW_HIDE);
                char szLan[128] = {0};
                sprintf(szLan,"exception end!%d",NET_DVR_GetLastError());
                AfxMessageBox(szLan);
                break;
            }
        }
 
    }
    
    CloseHandle(RPic->m_hFileThread);
    RPic->m_hFileThread = NULL;
    NET_DVR_CloseSmartSearchPicture(RPic->m_lFileHandle);
    
    return 0;
}


CDlgSmartSearchPicture::CDlgSmartSearchPicture(CWnd* pParent /*=NULL*/)
: CDialog(CDlgSmartSearchPicture::IDD, pParent)
, m_bVcaRectOnly(FALSE)
, m_strFilePath(_T(""))
, m_dwPID(0)
, m_dwUploadProgress(_T(""))
, m_bHumanMisinfo(FALSE)
{
	//{{AFX_DATA_INIT(CDlgSmartSearchPicture)
	m_sCardNum = _T("");
	m_bChkCard = FALSE;
	m_ctDateStart = 0;
	m_ctDateStop = 0;
	m_ctTimeStart = 0;
	m_ctTimeStop = 0;
	m_bContinue = FALSE;
	m_sLicense = _T("");
	m_fWidth = 0.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fHeight = 0.0f;
	m_dwFaceScore = 0;
	//}}AFX_DATA_INIT
    m_lBackupHandle = -1;
	m_bBackuping = FALSE;
	m_hBackupThread = NULL;
    memset(&m_struFindPictureParam, 0, sizeof(m_struFindPictureParam));
    memset(&m_struDiskList, 0, sizeof(m_struDiskList));
    memset(&m_struSmartPic, 0,sizeof(m_struSmartPic));
    memset(&m_struDFProcImgRet,0,sizeof(m_struDFProcImgRet));
	m_iIPChanNum = 0;
	m_iChanNum = 0;
    m_pPicInfo = NULL;
}

CDlgSmartSearchPicture::~CDlgSmartSearchPicture()
{     
    if (NULL != m_pPicInfo)
    {
        delete []m_pPicInfo;
        m_pPicInfo = NULL;
    }
}

void CDlgSmartSearchPicture::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgSmartSearchPicture)
    DDX_Control(pDX, IDC_COMBO_DETECT_FACE_RESULT, m_cmbDetectFaceRet);
    DDX_Control(pDX, IDC_COMBO_SEX, m_cmbSex);
    DDX_Control(pDX, IDC_COMBO_EYEGLASS, m_cmbEyeGlass);
    DDX_Control(pDX, IDC_COMBO_AGE, m_cmbAge);
    DDX_Control(pDX, IDC_SHOWJPEG, m_ShowJpegCtrl);
    DDX_Control(pDX, IDC_DOWNPROGRESS, m_downProgress);
    DDX_Control(pDX, IDC_REMOTEPICLIST, m_PicList);
    DDX_Control(pDX, IDC_PICTYPE, m_PicTypeCtrl);
    DDX_Control(pDX, IDC_COMBO_CHAN, m_ChannelCtrl);
    DDX_DateTimeCtrl(pDX, IDC_DATESTART, m_ctDateStart);
    DDX_DateTimeCtrl(pDX, IDC_DATESTOP, m_ctDateStop);
    DDX_DateTimeCtrl(pDX, IDC_TIMESTART, m_ctTimeStart);
    DDX_DateTimeCtrl(pDX, IDC_TIMESTOP, m_ctTimeStop);
    DDX_Text(pDX, IDC_EDIT_LICENSE, m_sLicense);
    DDX_Text(pDX, IDC_EDIT_WIDTH_RECT, m_fWidth);
    DDX_Text(pDX, IDC_EDIT_X, m_fX);
    DDX_Text(pDX, IDC_EDIT_Y, m_fY);
    DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fHeight);
    DDX_Text(pDX, IDC_EDIT_FACESCORE, m_dwFaceScore);
    DDX_Control(pDX, IDC_COMBO_COUNTRY, m_comboCountry);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK1, m_bVcaRectOnly);
    DDX_Text(pDX, IDC_EDT_FILE_PATH, m_strFilePath);
    DDX_Text(pDX, IDC_EDT_PIC_ID, m_dwPID);
    DDX_Text(pDX, IDC_STAT_PROGRESS, m_dwUploadProgress);
    DDX_Control(pDX, IDC_BEHAVIOUR_SEARCHTYPE_COMBO, m_comBehaviorSearchType);
    DDX_Check(pDX, IDC_CHECK2, m_bHumanMisinfo);
}


BEGIN_MESSAGE_MAP(CDlgSmartSearchPicture, CDialog)
	//{{AFX_MSG_MAP(CDlgSmartSearchPicture)
	ON_BN_CLICKED(IDC_SEARCHLIST, OnSearchlist)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_CHECKCARD, OnCheckcard)
	ON_NOTIFY(NM_CLICK, IDC_REMOTEPICLIST, OnClickRemotepiclist)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
	ON_CBN_SELCHANGE(IDC_PICTYPE, OnSelchangePictype)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_FILE, OnButtonBrowseFile)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_CBN_SELCHANGE(IDC_COMBO_DETECT_FACE_RESULT, OnSelchangeComboDetectFaceResult)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &CDlgSmartSearchPicture::OnBnClickedBtnSelectFile)
    ON_BN_CLICKED(IDC_BTN_START_UPLOAD, &CDlgSmartSearchPicture::OnBnClickedBtnStartUpload)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CDlgSmartSearchPicture::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSmartSearchPicture message handlers

void CDlgSmartSearchPicture::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CDlgSmartSearchPicture::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL CDlgSmartSearchPicture::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	
	// TODO: Add extra initialization here
	g_pDlgRemoteFile = this;
	
	pSmartPicture = NULL;
	m_bDown = FALSE;
	m_hFileThread = NULL;
	m_hGetThread = NULL;
	m_iFileNum = 0;
	m_lFileHandle = 0;
	nSelPics = 0;
	nDownPics = 0;
	m_lServerID = -1;
	m_bSearchDown = FALSE;
	m_downProgress.SetRange(0,100);
	m_downProgress.SetPos(0);
    memset(&m_struFaceAnalysisDataOut, 0, sizeof(m_struFaceAnalysisDataOut));


    char szLan[128] = { 0 };

    m_comboCountry.ResetContent();

    g_StringLanType(szLan, "不支持", "not support");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(0, 0);

    g_StringLanType(szLan, "无法识别", "Unrecognized");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(1, 0xe);

    g_StringLanType(szLan, "捷克共和国", "CZ");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(2, 1);

    g_StringLanType(szLan, "法国", "France");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(3, 2);

    g_StringLanType(szLan, "德国", "Germany");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(4, 3);

    g_StringLanType(szLan, "西班牙", "Spain");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(5, 4);

    g_StringLanType(szLan, "意大利", "Italy");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(6, 5);

    g_StringLanType(szLan, "荷兰", "Holland");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(7, 6);

    g_StringLanType(szLan, "波兰", "Polland");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(8, 7);

    g_StringLanType(szLan, "斯洛伐克", "Slovakia");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(9, 8);

    g_StringLanType(szLan, "白俄罗斯", "Belarus");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(10, 9);

    g_StringLanType(szLan, "摩尔多瓦", "Moldova");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(11, 10);

    g_StringLanType(szLan, "俄罗斯", "Russia");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(12, 11);

    g_StringLanType(szLan, "乌克兰", "Ukraine");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(13, 12);

    g_StringLanType(szLan, "加拿大", "Canada");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(14, 169);

    g_StringLanType(szLan, "美国", "US");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(15, 172);

    g_StringLanType(szLan, "澳大利亚", "Australia");
    m_comboCountry.AddString(szLan);
    m_comboCountry.SetItemData(16, 227);

    m_comboCountry.SetCurSel(0);
 
    UpdateData(FALSE); 
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgSmartSearchPicture::GetDiskList(NET_DVR_DISKABILITY_LIST &struDiskList)
{
    memset(&m_struDiskList, 0, sizeof(m_struDiskList));
    if (!NET_DVR_GetDiskList(m_lServerID, &struDiskList))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDiskList");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDiskList");
        return TRUE;
    }
}

void CDlgSmartSearchPicture::OnSearchlist() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = { 0 };

    UpdateData(TRUE);
    if (m_lServerID == -1)
    {
        g_StringLanType(szLan, "请选择服务器", "Please select server!");
        AfxMessageBox(szLan);
        return;
    }
    if (!m_bSearchDown)
    {
        DWORD dwTest = m_ChannelCtrl.GetCurSel();
        m_iChannel = m_ChannelCtrl.GetItemData(m_ChannelCtrl.GetCurSel());

        GetFindPictureParamFromWnd();


        m_lFileHandle = NET_DVR_SmartSearchPicture(m_lServerID, &m_struSmartPic);

        if (m_pPicInfo != NULL)
        {
            delete[]m_pPicInfo;
            m_pPicInfo = NULL;
        }
        if (m_lFileHandle < 0)
        {
            g_StringLanType(szLan, "获取图片列表失败", "Get Smart picture list failed!");
            AfxMessageBox(szLan);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SmartSearchPicture");
            return;
        }
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SmartSearchPicture");

        m_PicList.DeleteAllItems();
        m_iFileNum = 0;
        DWORD dwThreadId;
        if (m_hFileThread == NULL)
            m_hFileThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(SmartSearchPicThread), this, 0, &dwThreadId);
        if (m_hFileThread == NULL)
        {
            g_StringLanType(szLan, "创建线程失败", "Open thread failed!");
            AfxMessageBox(szLan);
            return;
        }
        m_bSearchDown = TRUE;
        g_StringLanType(szLan, "停止搜索", "Stop search");
        GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
        GetDlgItem(IDC_STATICSTATE)->ShowWindow(SW_SHOW);
    }
    else
    {
        m_bSearchDown = FALSE;
        if (m_lFileHandle != -1)
        {
            NET_DVR_CloseSmartSearchPicture(m_lFileHandle);
        }
        CloseHandle(m_hFileThread);
        m_hFileThread = NULL;
        g_StringLanType(szLan, "查找", "Search");
        GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
        GetDlgItem(IDC_STATICSTATE)->ShowWindow(SW_HIDE);
        g_StringLanType(szLan, "检索到图片数目:", "Search picture sum:");
        CString tempstring;
        tempstring.Format("%s[%d]", szLan, m_iFileNum);
        AfxMessageBox(tempstring);
        m_iFileNum = 0;
    }
}

void CDlgSmartSearchPicture::OnDownload() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};

	if (!m_bDown)
	{
		pos = m_PicList.GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			g_StringLanType(szLan, "请选择文件!", "Please select the file!");
			AfxMessageBox(szLan);
			return;
		}
		m_bDown = TRUE;
		nSelPics = m_PicList.GetSelectedCount();
		nDownPics = 0;

		DWORD dwThreadId;
		if (!m_hGetThread)
		{
			m_hGetThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetSmartPicThread),this,0,&dwThreadId);
		}
		else
		{
			TerminateThread(m_hGetThread, 0);
			m_hGetThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetSmartPicThread),this,0,&dwThreadId);
		}
		GetDlgItem(IDC_DOWNLOAD)->SetWindowText("Stop download");
		GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_SHOW);
	}
	else
	{
		if (!m_hGetThread)
		{
			g_StringLanType(szLan, "请选择文件!", "Please select the file!");
			AfxMessageBox(szLan);
			return;
		}
		m_bDown = FALSE;
	}
	UpdateData(FALSE);
}

void CDlgSmartSearchPicture::OnCheckcard() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bChkCard)
	{
		GetDlgItem(IDC_CARDNUM)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CARDNUM)->EnableWindow(FALSE);	
	}
	UpdateData(FALSE);	
}

void CDlgSmartSearchPicture::OnClickRemotepiclist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION tempPos;
	tempPos = m_PicList.GetFirstSelectedItemPosition();
	if (tempPos == NULL)
	{
		return;
	}
	CString csFileName;
	CString csPicTime;
	CString csCardNum;
	CString csTemp,csDir;
	char nFileName[256];
	CString csMessage;
	int fileselpos = 0;
    CString csVectInfo;

	fileselpos = m_PicList.GetNextSelectedItem(tempPos);
	csFileName.Format("%s",m_PicList.GetItemText(fileselpos,0));
	if (csFileName.IsEmpty())
	{
		return;
	}
	csPicTime.Format("%s", m_PicList.GetItemText(fileselpos,3));
 
	sprintf(filenamedownload, "%s", csFileName);
	csDir.Format("%s\\", g_struLocalParam.chDownLoadPath);

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	BOOL bShowIpv6 = g_ValidIPv6((BYTE*)g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
	if (bShowIpv6)
	{
		sprintf(nFileName, "%s_ipv6_%02d_D%s_%sjpg",csDir, m_iChannel, csPicTime, csCardNum);
	} 
	else
	{
		sprintf(nFileName, "%s%s_%02d_D%s_%sjpg",csDir, g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, m_iChannel, csPicTime, csCardNum);
	}

    /*if(!NET_DVR_GetPicture(m_lServerID, filenamedownload, nFileName))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPicture");
        return;
	}

	*/
    char *sSavedFileBuf = NULL;
       DWORD dwRetLen = 0;
      
       if(NET_DVR_GetPicture_V30(m_lServerID, filenamedownload, sSavedFileBuf, 0, &dwRetLen))
       {
           if(0 != dwRetLen)
           {
               sSavedFileBuf = new char[dwRetLen];
               memset(sSavedFileBuf, 0, dwRetLen);
               
               if(NET_DVR_GetPicture_V30(m_lServerID, filenamedownload, sSavedFileBuf, dwRetLen, &dwRetLen))
               {
                   if (NULL != sSavedFileBuf && 0 != dwRetLen)
                   {
                       
                       char cFilename[256] = {0};
                       HANDLE hFile;
                       DWORD dwReturn;
                       
                       SYSTEMTIME t;
                       GetLocalTime(&t);
                       char chTime[128];
                       sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
                       
                       sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
                       if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
                       {
                           CreateDirectory(cFilename, NULL);
                       }
                       
                       
                       sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
                       
                       //sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime, i);
                       hFile = CreateFile(nFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                       if (hFile == INVALID_HANDLE_VALUE)
                       {
                           return;
                       }
                       WriteFile(hFile, sSavedFileBuf, dwRetLen, &dwReturn, NULL);
                       CloseHandle(hFile);
                       hFile = NULL;                       
                   }
               }
               else
               {
                   return;
               }
               
               if (NULL != sSavedFileBuf)
               {
                   delete[]sSavedFileBuf;
                   sSavedFileBuf = NULL;
               }
           }
       }
 
 
    
	CRect rc;
	CDC* pDC = m_ShowJpegCtrl.GetDC();
	m_ShowJpegCtrl.GetClientRect(&rc);
	pDC->SetViewportOrg(rc.left, rc.top);
	rc.bottom = -rc.bottom;	
	if (!pSmartPicture)
	{
		pSmartPicture = new CPicture;	
	}	
	pSmartPicture->LoadPicture(nFileName, pDC->m_hDC, abs(rc.Width()), abs(rc.Height()));
	
    DeleteFile(nFileName);
    DWORD dwPicType = atoi(m_PicList.GetItemText(fileselpos,1));
    switch (dwPicType)
    {
    case 0:
    case 1:
    case 2:
        csVectInfo.Format("%s",m_PicList.GetItemText(fileselpos,5));
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        csVectInfo.Format("%s",m_PicList.GetItemText(fileselpos,4));
        break;
    default:
        break;
    }
    NET_VCA_RECT struRect = {0};
    COLORREF vtcolor;
	vtcolor = RGB(255, 0, 0);

    


     
    float fTemp = 0.0;
    csTemp = csVectInfo.Left(csVectInfo.Find(",Y"));
    
    
    
    struRect.fX = g_GetFloatValue(atoi(csTemp.Right(csTemp.GetLength() - 2))/1000.0);
    
    csVectInfo = csVectInfo.Right(csVectInfo.GetLength() - csVectInfo.Find("Y"));
    csTemp = csVectInfo.Left(csVectInfo.Find(",W"));
    struRect.fY = g_GetFloatValue(atoi(csTemp.Right(csTemp.GetLength() - 2))/1000.0);
    
    csVectInfo = csVectInfo.Right(csVectInfo.GetLength() - csVectInfo.Find("W"));
    csTemp = csVectInfo.Left(csVectInfo.Find(",H"));
    struRect.fWidth = g_GetFloatValue(atoi(csTemp.Right(csTemp.GetLength() - 6))/1000.0);
    
    csVectInfo = csVectInfo.Right(csVectInfo.GetLength() - csVectInfo.Find("H"));
    struRect.fHeight = g_GetFloatValue(atoi(csVectInfo.Right(csVectInfo.GetLength() - 7))/1000.0);
    
    

	GetDlgItem(IDC_SHOWJPEG)->GetWindowRect(&m_rcWnd);
    CDC *cCDC = GetDlgItem(IDC_SHOWJPEG)->GetDC();
    g_DrawRect(cCDC->m_hDC,struRect,m_rcWnd,0,vtcolor);
	*pResult = 0;
}


void CDlgSmartSearchPicture::F_Close()
{
	if (m_hGetThread)
	{
		TerminateThread(m_hGetThread, 0);	
		CloseHandle(m_hGetThread);
		m_hGetThread = NULL;
	}

	if (m_hFileThread)
	{
		TerminateThread(m_hFileThread, 0);
		CloseHandle(m_hFileThread);
		m_hFileThread = NULL;
	}

	if (pSmartPicture)
	{
		pSmartPicture->FreePicture();
		delete pSmartPicture;
		pSmartPicture = NULL;		
	}
}

void CDlgSmartSearchPicture::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
/*********************************************************
Function:	CheckInitParam
Desc:		check device parameters and initialize dialog parameters
Input:	
Output:	
Return:	    TRUE,check correct, parameters initialized; FALSE,check error, not initialized;
**********************************************************/
BOOL CDlgSmartSearchPicture::CheckInitParam()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		UpdateData(FALSE);
		return FALSE;
	}
    m_iDeviceIndex = iDeviceIndex;
    m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    m_iChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
    m_iIPChanNum = g_struDeviceInfo[m_iDeviceIndex].iIPChanNum;
    m_lServerType = g_struDeviceInfo[m_iDeviceIndex].iDeviceType;
    m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
    
    if (m_lServerID < 0)
    {
        return FALSE;
	}

	if ( m_iDeviceIndex == -1 || m_iDeviceIndex != iDeviceIndex)
	{
		// m_iChanIndex = -1;
	}
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	if (iChanIndex == -1)
	{
		iChanIndex = 0;
	}
	
	UpdateData(TRUE);
	AddHumanFeatureInfo();

    DWORD dwIndex = 0;
    m_ChannelCtrl.ResetContent();
   
    for (int i = 0; i< g_struDeviceInfo[iDeviceIndex].iDeviceChanNum; i++)
    {
        m_ChannelCtrl.AddString(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
        m_ChannelCtrl.SetItemData(dwIndex, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO);
        dwIndex++;
    }
    m_ChannelCtrl.SetCurSel(0);
    m_iChannel = 0;
    
    m_PicList.SetExtendedStyle(m_PicList.GetExtendedStyle()|LVS_EX_FULLROWSELECT); 
    
    char szLan[128] = {0};

    
    CTime time1 = CTime::GetCurrentTime();
    CTime time(time1.GetYear(),time1.GetMonth(),time1.GetDay(),0,0,0);
    CTime time0(time1.GetYear(),time1.GetMonth(),time1.GetDay(),23,59,59);
    m_ctDateStart = time;
    m_ctTimeStart = time;
    m_ctDateStop = time;
    m_ctTimeStop = time0;
    m_lStartChan = 0;	
    
    m_PicTypeCtrl.ResetContent();
    
    g_StringLanType(szLan, "车辆检测", "All");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(0, 0);
    
    g_StringLanType(szLan, "人脸属性", "Schedule");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(1, 1);
    
    g_StringLanType(szLan, "以图索图", "Motion Detect");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(2, 2);
    
    g_StringLanType(szLan, "行为分析", "Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(3, 3); 
    
    m_PicTypeCtrl.SetCurSel(0);
    RefreshPicShowList();

    //行为分析搜索类型
    m_comBehaviorSearchType.ResetContent();

    g_StringLanType(szLan, "穿越警戒线", "LineDetection");
    m_comBehaviorSearchType.AddString(szLan);

    g_StringLanType(szLan, "区域入侵", "FiledDetection");
    m_comBehaviorSearchType.AddString(szLan);

    g_StringLanType(szLan, "进入区域", "RegionEnterDetection");
    m_comBehaviorSearchType.AddString(szLan);

    g_StringLanType(szLan, "离开区域", "RegionExitDetection");
    m_comBehaviorSearchType.AddString(szLan);

    m_comBehaviorSearchType.SetCurSel(0);

	UpdateData(FALSE); 
 
    return TRUE;
}
/*********************************************************
  Function:	SetParentWnd
  Desc:		transmit the handle of parent dialog box
  Input:	hhWnd, pointer to handle array
  Output:	
  Return:	
**********************************************************/
void CDlgSmartSearchPicture::SetParentWnd(HWND *hhWnd, int iParentNum)
{
	VERIFY(iParentNum==2);
	m_hPareDlgWnd=hhWnd[0];
	m_hPareTabWnd=hhWnd[1];
}

void CDlgSmartSearchPicture::GetFindPictureParamFromWnd()
{
    //struPictureParam.lChannel = m_ChannelCtrl.GetCurSel()+m_lStartChan;
    UpdateData(TRUE);
    char szLan[128]= {0};
   // memset(&m_struSmartPic, 0,sizeof(m_struSmartPic));
    m_struSmartPic.dwChanNo = m_ChannelCtrl.GetItemData(m_ChannelCtrl.GetCurSel());
    
    m_struSmartPic.struStartTime.wYear = (WORD)m_ctDateStart.GetYear();
    m_struSmartPic.struStartTime.byMonth = (WORD)m_ctDateStart.GetMonth();
    m_struSmartPic.struStartTime.byDay = (WORD)m_ctDateStart.GetDay();
    m_struSmartPic.struStartTime.byHour = (char)m_ctTimeStart.GetHour();
    m_struSmartPic.struStartTime.byMinute = (char)m_ctTimeStart.GetMinute();
    m_struSmartPic.struStartTime.bySecond = (char)m_ctTimeStart.GetSecond();
    m_struSmartPic.struEndTime.wYear = (WORD)m_ctDateStop.GetYear();
    m_struSmartPic.struEndTime.byMonth = (WORD)m_ctDateStop.GetMonth();
    m_struSmartPic.struEndTime.byDay = (WORD)m_ctDateStop.GetDay();
    m_struSmartPic.struEndTime.byHour = (char)m_ctTimeStop.GetHour();
    m_struSmartPic.struEndTime.byMinute = (char)m_ctTimeStop.GetMinute();
    m_struSmartPic.struEndTime.bySecond = (char)m_ctTimeStop.GetSecond();
    m_struSmartPic.byISO8601 = g_bISO8601;
    m_struSmartPic.cStartTimeDifferenceH = g_iHourDiffWithUTC;
    m_struSmartPic.cStartTimeDifferenceM = g_iMinDiffWithUTC;
    m_struSmartPic.cStopTimeDifferenceH = g_iHourDiffWithUTC;
    m_struSmartPic.cStopTimeDifferenceM = g_iMinDiffWithUTC;

    m_struSmartPic.wSearchType = m_PicTypeCtrl.GetItemData(m_PicTypeCtrl.GetCurSel());

    switch(m_struSmartPic.wSearchType)
    {
    case 0:
        strncpy((char*)m_struSmartPic.uSmartSearchCond.struVehiclePara.sLicense, m_sLicense.GetBuffer(0), sizeof(m_struSmartPic.uSmartSearchCond.struVehiclePara.sLicense));

        m_struSmartPic.uSmartSearchCond.struVehiclePara.byCountry = m_comboCountry.GetItemData(m_comboCountry.GetCurSel());
        break;

    case 1:
        m_struSmartPic.uSmartSearchCond.struHumaFeature.byAgeGroup = m_cmbAge.GetCurSel();
        m_struSmartPic.uSmartSearchCond.struHumaFeature.byEyeGlass = m_cmbEyeGlass.GetItemData(m_cmbEyeGlass.GetCurSel());
        m_struSmartPic.uSmartSearchCond.struHumaFeature.bySex = m_cmbSex.GetItemData(m_cmbSex.GetCurSel());

        break;
    case 2:
        {
            if (m_bVcaRectOnly)
            {
                memset(&m_struSmartPic.uSmartSearchCond.struHumaPic, 0, sizeof(m_struSmartPic.uSmartSearchCond.struHumaPic));
                m_struSmartPic.uSmartSearchCond.struHumaPic.dwFaceScore = m_dwFaceScore;
                m_struSmartPic.uSmartSearchCond.struHumaPic.byVcaRectOnly = 1;
                m_struSmartPic.uSmartSearchCond.struHumaPic.dwPID = m_dwPID;
                m_struSmartPic.uSmartSearchCond.struHumaPic.dwFaceSearchNum = m_struFaceAnalysisDataOut.dwFaceAnalysisNum;
                for (int i = 0; i < NET_DVR_MAX_FACE_SEARCH_NUM; i++)
                {
                    memcpy(&m_struSmartPic.uSmartSearchCond.struHumaPic.struMultiVcaRect[i], &m_struFaceAnalysisDataOut.struVcaRect[i], sizeof(m_struSmartPic.uSmartSearchCond.struHumaPic.struMultiVcaRect[i]));
                }
            }
            else
            {
                m_struSmartPic.uSmartSearchCond.struHumaPic.dwFaceScore = m_dwFaceScore;
                m_struSmartPic.uSmartSearchCond.struHumaPic.struVcaRect.fX = m_fX;
                m_struSmartPic.uSmartSearchCond.struHumaPic.struVcaRect.fY = m_fY;
                m_struSmartPic.uSmartSearchCond.struHumaPic.struVcaRect.fWidth = m_fWidth;
                m_struSmartPic.uSmartSearchCond.struHumaPic.struVcaRect.fHeight = m_fHeight;
                /*m_struSmartPic.uSmartSearchCond.struHumaPic.dwFaceScore = 80;*/
                CFile cFile;

                if (!cFile.Open(m_csFilePath, CFile::modeRead))
                {
                    g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
                    AfxMessageBox(szLan);
                }
                else
                {
                    m_struSmartPic.uSmartSearchCond.struHumaPic.dwImageLen = (DWORD)cFile.GetLength();
                    if (m_struSmartPic.uSmartSearchCond.struHumaPic.dwImageLen == 0)
                    {
                        g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
                        AfxMessageBox(szLan);
                    }

                    m_pPicInfo = new BYTE[m_struSmartPic.uSmartSearchCond.struHumaPic.dwImageLen];
                    cFile.Read(m_pPicInfo, m_struSmartPic.uSmartSearchCond.struHumaPic.dwImageLen);
                    m_struSmartPic.uSmartSearchCond.struHumaPic.pImage = m_pPicInfo;

                    cFile.Close();
                }
            }

        }
        break;
    case 3:
    {
        if (m_comBehaviorSearchType.GetCurSel() == 0)
        {
            m_struSmartPic.uSmartSearchCond.struBehaviourCond.dwSearchType = 0x1;
        }
        else if (m_comBehaviorSearchType.GetCurSel() == 1)
        {
            m_struSmartPic.uSmartSearchCond.struBehaviourCond.dwSearchType = 0x2;
        }
        else if (m_comBehaviorSearchType.GetCurSel() == 2)
        {
            m_struSmartPic.uSmartSearchCond.struBehaviourCond.dwSearchType = 0x10;
        }
        else if (m_comBehaviorSearchType.GetCurSel() == 3)
        {
            m_struSmartPic.uSmartSearchCond.struBehaviourCond.dwSearchType = 0x20;
        }
        m_struSmartPic.uSmartSearchCond.struBehaviourCond.byHumanMisinfo = m_bHumanMisinfo;
    }
        break;
    default:
        break;
    }

  
}

/******************************************
函数:	ProcessFileSize
描述:	
输入:	
输出:	
返回值: 
******************************************/
DWORD CDlgSmartSearchPicture::ProcessFileSize(CString csFileSize)
{
    DWORD dwFileSize = 0;
    if (csFileSize[csFileSize.GetLength()-1] == 'M')
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength() - 1));
        dwFileSize *= (1024*1024);
    }
    else if (csFileSize[csFileSize.GetLength()-1] == 'K')
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength() - 1));
        dwFileSize *= 1024;
    }
    else
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength()));
    }
    return dwFileSize;
}

BOOL CDlgSmartSearchPicture::GetBackupPictureParamFromWnd_FILE(NET_DVR_BACKUP_PICTURE_PARAM &struBackPicturParam)
{
	UpdateData(TRUE);

 /*   CString csDiskDesc = "";
    char szLan[128] = {0};
    if (m_comboDiskList.GetCurSel() != CB_ERR)
    {
        m_comboDiskList.GetLBText(m_comboDiskList.GetCurSel(), csDiskDesc);
    }
    else
    {
        g_StringLanType(szLan, "请选择磁盘备份列表", "Please select backup disk");
        AfxMessageBox(szLan);
		return FALSE;
    }

	struBackPicturParam.dwSize = sizeof(struBackPicturParam);

    strncpy((char*)(struBackPicturParam.byDiskDes), (char*)csDiskDesc.GetBuffer(0), sizeof(struBackPicturParam.byDiskDes));
    struBackPicturParam.byContinue = m_bContinue;
    
    int iItemCount = 0;
    int iIndex = 0;
    POSITION pos = m_PicList.GetFirstSelectedItemPosition();
    CString csFileSize;
	CString csFileTime;
    while ((pos != NULL) && (iItemCount < ARRAY_SIZE(struBackPicturParam.struPicture)))
    {
        iIndex = m_PicList.GetNextSelectedItem(pos);
        sprintf(struBackPicturParam.struPicture[iItemCount].sFileName, "%s", m_PicList.GetItemText(iIndex, 0));

		csFileSize = m_PicList.GetItemText(iIndex, 1);
        struBackPicturParam.struPicture[iItemCount].dwFileSize = ProcessFileSize(csFileSize);

		csFileTime = m_PicList.GetItemText(iIndex, 2);
		sscanf(csFileTime, "%04d%02d%02d%02d%02d%02d", &(struBackPicturParam.struPicture[iItemCount].struTime.dwYear),\
			                                           &(struBackPicturParam.struPicture[iItemCount].struTime.dwMonth),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwDay),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwHour),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwMinute),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwSecond));

        iItemCount++;
    }
    struBackPicturParam.dwPicNum = iItemCount; 
*/
    return TRUE;
}


	

void CDlgSmartSearchPicture::PostNcDestroy() 
{
	
	CDialog::PostNcDestroy();
}

void CDlgSmartSearchPicture::OnUpload() 
{
	// TODO: Add your control notification handler code here
    CDlgPictureUpload dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_ChannelCtrl.GetItemData(m_ChannelCtrl.GetCurSel());
    dlg.m_lDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void CDlgSmartSearchPicture::RefreshPicShowList()
{
     
  
    m_PicList.DeleteAllItems();
    
    int iCount = m_PicList.GetHeaderCtrl()->GetItemCount();

	int i = 0;
    for (i = 0; i< iCount;i++)
    {
        m_PicList.DeleteColumn(0);
    }

    for (i = 0; i< iCount;i++)
    {
        m_PicList.GetHeaderCtrl()->DeleteItem(0);
    }
     char szLan[128] = {0};

    if (m_PicTypeCtrl.GetCurSel() == 0)
    { 
        g_StringLanType(szLan, "图片名称", "pic name");
        m_PicList.InsertColumn(0,szLan,LVCFMT_LEFT,140,-1);
        
        g_StringLanType(szLan, "图片类型", "pic type");
        m_PicList.InsertColumn(1,szLan,LVCFMT_LEFT,80,-1);


        g_StringLanType(szLan, "图片大小", "pic size");
        m_PicList.InsertColumn(2,szLan,LVCFMT_LEFT,60,-1);
        
        g_StringLanType(szLan, "图片时间", "pic time");
        m_PicList.InsertColumn(3,szLan,LVCFMT_LEFT,110,-1);
        
        g_StringLanType(szLan, "车牌号", "card num");
        m_PicList.InsertColumn(4,szLan,LVCFMT_LEFT,80,-1);
                     
        g_StringLanType(szLan, "子图坐标", "vca rect");
        m_PicList.InsertColumn(5,szLan,LVCFMT_LEFT,100,-1);
    }
    else if(m_PicTypeCtrl.GetCurSel() == 1 || m_PicTypeCtrl.GetCurSel() == 2)
    {
        g_StringLanType(szLan, "图片名称", "pic name");
        m_PicList.InsertColumn(0,szLan,LVCFMT_LEFT,140,-1);
        
        g_StringLanType(szLan, "图片类型", "pic type");
        m_PicList.InsertColumn(1,szLan,LVCFMT_LEFT,80,-1);
        
        
        g_StringLanType(szLan, "图片大小", "pic size");
        m_PicList.InsertColumn(2,szLan,LVCFMT_LEFT,60,-1);
        
        g_StringLanType(szLan, "图片时间", "pic time");
        m_PicList.InsertColumn(3,szLan,LVCFMT_LEFT,110,-1);
        
        g_StringLanType(szLan, "相似度", "Similarity");
        m_PicList.InsertColumn(4,szLan,LVCFMT_LEFT,80,-1);
        
        g_StringLanType(szLan, "子图坐标", "vca rect");
        m_PicList.InsertColumn(5,szLan,LVCFMT_LEFT,100,-1);
    }
    else if(m_PicTypeCtrl.GetCurSel() == 3)
    {        
        g_StringLanType(szLan, "图片名称", "pic name");
        m_PicList.InsertColumn(0,szLan,LVCFMT_LEFT,140,-1);
        
        g_StringLanType(szLan, "图片类型", "pic type");
        m_PicList.InsertColumn(1,szLan,LVCFMT_LEFT,80,-1);
        
        
        g_StringLanType(szLan, "图片大小", "pic size");
        m_PicList.InsertColumn(2,szLan,LVCFMT_LEFT,60,-1);
        
        g_StringLanType(szLan, "图片时间", "pic time");
        m_PicList.InsertColumn(3,szLan,LVCFMT_LEFT,110,-1);
        
        g_StringLanType(szLan, "区域坐标", "vca rect");
        m_PicList.InsertColumn(4,szLan,LVCFMT_LEFT,100,-1);
    }
    else
    {
        
        g_StringLanType(szLan, "图片名称", "pic name");
        m_PicList.InsertColumn(0,szLan,LVCFMT_LEFT,140,-1);
        
        g_StringLanType(szLan, "图片类型", "pic type");
        m_PicList.InsertColumn(1,szLan,LVCFMT_LEFT,80,-1);
        
        
        g_StringLanType(szLan, "图片大小", "pic size");
        m_PicList.InsertColumn(2,szLan,LVCFMT_LEFT,60,-1);
        
        g_StringLanType(szLan, "图片时间", "pic time");
        m_PicList.InsertColumn(3,szLan,LVCFMT_LEFT,110,-1);
        
        g_StringLanType(szLan, "车牌号", "card num");
        m_PicList.InsertColumn(4,szLan,LVCFMT_LEFT,80,-1);
        
        g_StringLanType(szLan, "子图坐标", "vca rect");
        m_PicList.InsertColumn(5,szLan,LVCFMT_LEFT,100,-1);
    }

}

void CDlgSmartSearchPicture::AddHumanFeatureInfo()
{    
    m_cmbAge.ResetContent();
    DWORD dwIndex = 0;
    char szTemp[128] = {0};
    g_StringLanType(szTemp,"不关注","NOT ATTENTION");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,0);
    dwIndex++;

    g_StringLanType(szTemp,"婴幼儿","INFANT");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_INFANT);
    dwIndex++;
    
    g_StringLanType(szTemp,"儿童","CHILD");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_CHILD);
    dwIndex++;
    
    g_StringLanType(szTemp,"少年","YOUNGSTER");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_YOUNGSTER);
    dwIndex++;
    
    g_StringLanType(szTemp,"青少年","ADOLESCENT");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_ADOLESCENT);
    dwIndex++;
    
    g_StringLanType(szTemp,"青年","YOUTH");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_YOUTH);
    dwIndex++;
    
    g_StringLanType(szTemp,"壮年","PRIME");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_PRIME);
    dwIndex++;
    
    g_StringLanType(szTemp,"中年","MIDLIFE");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex, ENUM_AGE_GROUP_MIDLIFE);
    dwIndex++;
    
    g_StringLanType(szTemp,"中老年","MIDAGE");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_MIDAGE);
    dwIndex++;
    
    g_StringLanType(szTemp,"老年","OLD");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_OLD);
    dwIndex++;

    m_cmbAge.SetCurSel(0);

    dwIndex = 0;


    m_cmbEyeGlass.ResetContent();

    g_StringLanType(szTemp,"不关注","No Attention");
    m_cmbEyeGlass.AddString(szTemp);
    m_cmbEyeGlass.SetItemData(dwIndex,0);
    dwIndex++;

    g_StringLanType(szTemp,"是","YES");
    m_cmbEyeGlass.AddString(szTemp);
    m_cmbEyeGlass.SetItemData(dwIndex,1);
    dwIndex++;

    g_StringLanType(szTemp,"不带","NO");
    m_cmbEyeGlass.AddString(szTemp);
    m_cmbEyeGlass.SetItemData(dwIndex,2);
    dwIndex++;
    m_cmbEyeGlass.SetCurSel(0);


    dwIndex = 0;
    m_cmbSex.ResetContent();
    
    g_StringLanType(szTemp,"不关注","No Attention");
    m_cmbSex.AddString(szTemp);
    m_cmbSex.SetItemData(dwIndex,0);
    dwIndex++;
    
    g_StringLanType(szTemp,"男","MAN");
    m_cmbSex.AddString(szTemp);
    m_cmbSex.SetItemData(dwIndex,1);
    dwIndex++;
    
    g_StringLanType(szTemp,"女","WOMEN");
    m_cmbSex.AddString(szTemp);
    m_cmbSex.SetItemData(dwIndex,2);
    dwIndex++;
    m_cmbSex.SetCurSel(0);
}

void CDlgSmartSearchPicture::OnSelchangePictype() 
{
	// TODO: Add your control notification handler code here
	RefreshPicShowList();
}

void CDlgSmartSearchPicture::OnButtonBrowseFile() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    char szLan[128] = {0};
    OPENFILENAME ofn = {0};
    CRect struRect;
    
 

    memset(m_chFilename, 0, MAX_PATH);
    
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = this->GetSafeHwnd();
    ofn.lpstrFilter = "All Files\0*.*\0\0";
    ofn.lpstrFile   = m_chFilename;
    ofn.nMaxFile    = MAX_PATH;
    ofn.Flags       = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
   
   

    if (GetOpenFileName(&ofn))
    {
        m_csFilePath.Format("%s", m_chFilename);
    }
    
    if (strlen(m_chFilename) == 0)
    {
        return;
    }
   
    CRect rc;
   	CDC* pDC = m_ShowJpegCtrl.GetDC();
    m_ShowJpegCtrl.GetClientRect(&rc);
    pDC->SetViewportOrg(rc.left, rc.top);
    rc.bottom = -rc.bottom;	
    if (!pSmartPicture)
    {
        pSmartPicture = new CPicture;	
    }	
	pSmartPicture->LoadPicture(m_chFilename, pDC->m_hDC, abs(rc.Width()), abs(rc.Height()));

	UpdateData(FALSE);

}

void CDlgSmartSearchPicture::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
    CDlgVcaSingleProcImg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_ChannelCtrl.GetItemData(m_ChannelCtrl.GetCurSel());
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.m_pStruRecvBuf = &m_struDFProcImgRet;
    DWORD dwRet = dlg.DoModal();
    if(dwRet ==IDOK || dwRet == IDCANCEL)
    {
       m_csFilePath = dlg.m_chFilename;
        m_bDetectSuccess = dlg.m_bDetectSuccess;
    }

    if (!m_bDetectSuccess) // Detect fail
    {
       return;
    }
    
// m_struDFProcImgRet.dwSubImageNum =2;
// 
// m_struDFProcImgRet.struProcImg[0].struVcaRect.fX = 0.100;
// m_struDFProcImgRet.struProcImg[0].struVcaRect.fY =0.100;
// m_struDFProcImgRet.struProcImg[0].struVcaRect.fHeight =0.200;
// m_struDFProcImgRet.struProcImg[0].struVcaRect.fWidth=0.200;
// 
// m_struDFProcImgRet.struProcImg[1].struVcaRect.fX = 0.300;
// m_struDFProcImgRet.struProcImg[1].struVcaRect.fY =0.300;
// m_struDFProcImgRet.struProcImg[1].struVcaRect.fHeight =0.200;
// m_struDFProcImgRet.struProcImg[1].struVcaRect.fWidth=0.200;


    CRect rc;
    CDC* pDC = m_ShowJpegCtrl.GetDC();
    m_ShowJpegCtrl.GetClientRect(&rc);
    pDC->SetViewportOrg(rc.left, rc.top);
    rc.bottom = -rc.bottom;	
    if (!pSmartPicture)
    {
        pSmartPicture = new CPicture;	
    }	
    pSmartPicture->LoadPicture((LPSTR)(LPCTSTR)m_csFilePath, pDC->m_hDC, abs(rc.Width()), abs(rc.Height()));
    NET_VCA_RECT struRect = {0};
    COLORREF vtcolor;
    vtcolor = RGB(255, 0, 0); 

    

    m_cmbDetectFaceRet.EnableWindow(TRUE);
    m_cmbDetectFaceRet.ResetContent();
    char szLan[128]= {0};
    char szLanCn[128] = {0};
    char szLanEn[128] = {0};
    int i = 0;

 
    for(i = 0; i< m_struDFProcImgRet.dwSubImageNum; i++)
    {
        sprintf(szLanCn,"检测人脸%d",i+1);
        sprintf(szLanEn,"Face Detect %d st",i);
        g_StringLanType(szLan, szLanCn, szLanEn);
        m_cmbDetectFaceRet.AddString(szLan);
    }

    m_cmbDetectFaceRet.SetCurSel(0);
   OnSelchangeComboDetectFaceResult();
        
    UpdateData(FALSE);
}

void CDlgSmartSearchPicture::OnSelchangeComboDetectFaceResult() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_VCA_RECT struRect = {0};
    COLORREF vtcolor;
    vtcolor = RGB(255, 0, 0); 
    int iCurSelectIndex = m_cmbDetectFaceRet.GetCurSel();
    struRect.fX = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fX;
    struRect.fY = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fY;
    struRect.fHeight = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fHeight;
    struRect.fWidth = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fWidth;

    m_fX = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fX;
    m_fY = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fY;
    m_fHeight = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fHeight;
    m_fWidth = m_struDFProcImgRet.struProcImg[iCurSelectIndex].struVcaRect.fWidth;
    m_dwFaceScore = m_struDFProcImgRet.struProcImg[iCurSelectIndex].dwFaceScore;

    GetDlgItem(IDC_SHOWJPEG)->GetWindowRect(&m_rcWnd);

    CDC *cCDC = GetDlgItem(IDC_SHOWJPEG)->GetDC();
 
    g_DrawRect(cCDC->m_hDC,struRect,m_rcWnd,0,vtcolor);

    UpdateData(FALSE);

}


void CDlgSmartSearchPicture::OnBnClickedBtnSelectFile()
{
    UpdateData(TRUE);

    char szLan[1024] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        SetDlgItemText(IDC_EDT_FILE_PATH, m_strFilePath);
    }

    m_hFile = CreateFile(m_strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == m_hFile)
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
        return;
    }
    BY_HANDLE_FILE_INFORMATION struFileInfo = { 0 };
    if (!GetFileInformationByHandle(m_hFile, &struFileInfo))
    {
        g_StringLanType(szLan, "获取文件信息失败", "Get file info failed ");
        AfxMessageBox(szLan);
        return;
    }

    m_iFileSize = (((INT64)struFileInfo.nFileSizeHigh << 32)) + (INT64)struFileInfo.nFileSizeLow;
    if (m_iFileSize == 0)
    {
        g_StringLanType(szLan, "文件为空", "Configure file is empty");
        AfxMessageBox(szLan);
        return;
    }
}

DWORD  GetUpLoaFaceAnalysisDataThread(LPVOID pParam)
{
    CDlgSmartSearchPicture *pThis = (CDlgSmartSearchPicture*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };
    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            NET_DVR_GetUploadResult(pThis->m_lUploadHandle, &pThis->m_struFaceAnalysisDataOut, sizeof(pThis->m_struFaceAnalysisDataOut));
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:", "Is uploading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
                pThis->m_bUpLoading = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
                break;
            }

        }

        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_UploadClose(pThis->m_lUploadHandle);
            pThis->m_bUpLoading = FALSE;
        }
    }
    return FALSE;
}



void CDlgSmartSearchPicture::OnBnClickedBtnStartUpload()
{
    UpdateData(TRUE);

    m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_FACE_ANALYSIS_DATA, NULL, 0, m_strFilePath, NULL, 0);

    if (m_lUploadHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "UPLOAD_FACE_ANALYSIS_DATA");
        m_bUpLoading = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "UPLOAD_FACE_ANALYSIS_DATA");
        DWORD dwThreadId = 0;
        m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoaFaceAnalysisDataThread), this, 0, &dwThreadId);
        if (m_hUpLoadThread == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        m_bUpLoading = TRUE;
    }
    UpdateData(FALSE);
}


void CDlgSmartSearchPicture::OnBnClickedButtonUpdate()
{
    m_dwPID = m_struFaceAnalysisDataOut.dwPID;
    UpdateData(FALSE);
}
