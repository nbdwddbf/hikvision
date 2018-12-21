// DlgVideoIntercomNoticeDataCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomNoticeDataCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomNoticeDataCfg dialog


CDlgVideoIntercomNoticeDataCfg::CDlgVideoIntercomNoticeDataCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomNoticeDataCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomNoticeDataCfg)
	m_strNoticeDetail = _T("");
	m_strNoticeNumber = _T("");
	m_strNoticeTheme = _T("");
	m_dtNoticeTime = COleDateTime::GetCurrentTime();
	m_strPicPath[0] = _T("");
	m_strPicPath[1] = _T("");
	m_strPicPath[2] = _T("");
	m_strPicPath[3] = _T("");
	m_strPicPath[4] = _T("");
	m_strPicPath[5] = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
}


void CDlgVideoIntercomNoticeDataCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomNoticeDataCfg)
	DDX_Control(pDX, IDC_NOTICE_DATETIME, m_ctrlNoticeDataTime);
	DDX_Control(pDX, IDC_COMBO_NOTICE_LEVEL, m_comboNoticeLevel);
	DDX_Text(pDX, IDC_EDIT_NOTICE_DETAIL, m_strNoticeDetail);
	DDX_Text(pDX, IDC_EDIT_NOTICE_NUMBER, m_strNoticeNumber);
	DDX_Text(pDX, IDC_EDIT_NOTICE_THEME, m_strNoticeTheme);
	DDX_DateTimeCtrl(pDX, IDC_NOTICE_DATETIME, m_dtNoticeTime);
	DDX_Text(pDX, IDC_EDIT_PATH_PIC1, m_strPicPath[0]);
	DDX_Text(pDX, IDC_EDIT_PATH_PIC2, m_strPicPath[1]);
	DDX_Text(pDX, IDC_EDIT_PATH_PIC3, m_strPicPath[2]);
	DDX_Text(pDX, IDC_EDIT_PATH_PIC4, m_strPicPath[3]);
	DDX_Text(pDX, IDC_EDIT_PATH_PIC5, m_strPicPath[4]);
	DDX_Text(pDX, IDC_EDIT_PATH_PIC6, m_strPicPath[5]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomNoticeDataCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomNoticeDataCfg)
	ON_BN_CLICKED(IDC_BTN_SEL_PIC1, OnBtnSelPic1)
	ON_BN_CLICKED(IDC_BTN_SEL_PIC2, OnBtnSelPic2)
	ON_BN_CLICKED(IDC_BTN_SEL_PIC3, OnBtnSelPic3)
	ON_BN_CLICKED(IDC_BTN_SEL_PIC4, OnBtnSelPic4)
	ON_BN_CLICKED(IDC_BTN_SEL_PIC5, OnBtnSelPic5)
	ON_BN_CLICKED(IDC_BTN_SEL_PIC6, OnBtnSelPic6)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomNoticeDataCfg message handlers
BOOL CDlgVideoIntercomNoticeDataCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlNoticeDataTime.SetFormat("yyyy/MM/dd hh:mm:ss");

	m_comboNoticeLevel.ResetContent();

	char szText[64] = "\0";
	g_StringLanType(szText,"广告","Advertisement");
	m_comboNoticeLevel.InsertString(0,szText);
	m_comboNoticeLevel.SetItemData(0,1);

	g_StringLanType(szText,"物业通知","Property Notification");
	m_comboNoticeLevel.InsertString(1,szText);
	m_comboNoticeLevel.SetItemData(1,2);

	g_StringLanType(szText,"报警","Alarm");
	m_comboNoticeLevel.InsertString(2,szText);
	m_comboNoticeLevel.SetItemData(2,3);

    g_StringLanType(szText,"通知类信息","Notice Info");
    m_comboNoticeLevel.InsertString(3,szText);
	m_comboNoticeLevel.SetItemData(3,4);

	m_comboNoticeLevel.SetCurSel(0);

	return TRUE;
}

void CDlgVideoIntercomNoticeDataCfg::OnBtnSelPic1() 
{
	TCHAR szFilters[]= _T("Image(*.jpg)|*.jpg|All Files (*.*)|*.*||");
	
	CFileDialog fileDlg(TRUE,NULL,NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	
	if(fileDlg.DoModal() == IDOK)
	{
		m_strPicPath[0] = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH_PIC1,m_strPicPath[0]);
	}
}

void CDlgVideoIntercomNoticeDataCfg::OnBtnSelPic2() 
{
	TCHAR szFilters[]= _T("Image(*.jpg)|*.jpg|All Files (*.*)|*.*||");
	
	CFileDialog fileDlg(TRUE,NULL,NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	
	if(fileDlg.DoModal() == IDOK)
	{
		m_strPicPath[1] = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH_PIC2,m_strPicPath[1]);
	}
}

void CDlgVideoIntercomNoticeDataCfg::OnBtnSelPic3() 
{
	TCHAR szFilters[]= _T("Image(*.jpg)|*.jpg|All Files (*.*)|*.*||");
	
	CFileDialog fileDlg(TRUE,NULL,NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	
	if(fileDlg.DoModal() == IDOK)
	{
		m_strPicPath[2] = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH_PIC3,m_strPicPath[2]);
	}
}

void CDlgVideoIntercomNoticeDataCfg::OnBtnSelPic4() 
{
	TCHAR szFilters[]= _T("Image(*.jpg)|*.jpg|All Files (*.*)|*.*||");
	
	CFileDialog fileDlg(TRUE,NULL,NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	
	if(fileDlg.DoModal() == IDOK)
	{
		m_strPicPath[3] = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH_PIC4,m_strPicPath[3]);
	}
}

void CDlgVideoIntercomNoticeDataCfg::OnBtnSelPic5() 
{
	TCHAR szFilters[]= _T("Image(*.jpg)|*.jpg|All Files (*.*)|*.*||");
	
	CFileDialog fileDlg(TRUE,NULL,NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	
	if(fileDlg.DoModal() == IDOK)
	{
		m_strPicPath[4] = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH_PIC5,m_strPicPath[4]);
	}
}

void CDlgVideoIntercomNoticeDataCfg::OnBtnSelPic6() 
{
	TCHAR szFilters[]= _T("Image(*.jpg)|*.jpg|All Files (*.*)|*.*||");
	
	CFileDialog fileDlg(TRUE,NULL,NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	
	if(fileDlg.DoModal() == IDOK)
	{
		m_strPicPath[5] = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH_PIC6,m_strPicPath[5]);
	}
}

void CDlgVideoIntercomNoticeDataCfg::OnBtnSet() 
{
	char szError[32] = "\0";
	if (SetNoticeData())
	{   
		g_StringLanType(szError, "下发公告信息成功","Sent notification successfully");
	}
	else
	{
		g_StringLanType(szError, "下发公告信息失败","Sent notification failed");
	}
	AfxMessageBox(szError);
}

BOOL CDlgVideoIntercomNoticeDataCfg::SetNoticeData()
{   
	BOOL bRst = FALSE;

	NET_DVR_NOTICE_DATA struNoticeData = {0};
	GetParamFromWnd(&struNoticeData);

	if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_NOTICE_DATA,&struNoticeData,sizeof(struNoticeData)))
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_REMOTECONTROL_NOTICE_DATA");
		bRst = TRUE;
	}
	else
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_REMOTECONTROL_NOTICE_DATA");
		bRst = FALSE;
	}

	for (int i = 0; i < MAX_NOTICE_PIC_NUM; i++)
	{
		if (struNoticeData.struNoticePic[i].dwPicDataLen > 0 && struNoticeData.struNoticePic[i].pPicData != NULL)
		{
			delete[] struNoticeData.struNoticePic[i].pPicData;
			struNoticeData.struNoticePic[i].pPicData = NULL;
		}
	}
	return bRst;
}

void CDlgVideoIntercomNoticeDataCfg::GetParamFromWnd(NET_DVR_NOTICE_DATA* pNoticeData)
{   
	UpdateData(TRUE);
	memset(pNoticeData,0,sizeof(NET_DVR_NOTICE_DATA));

	pNoticeData->dwSize = sizeof(NET_DVR_NOTICE_DATA);
	pNoticeData->struTime.wYear = m_dtNoticeTime.GetYear();
	pNoticeData->struTime.byMonth = m_dtNoticeTime.GetMonth();
	pNoticeData->struTime.byDay = m_dtNoticeTime.GetDay();
	pNoticeData->struTime.byHour = m_dtNoticeTime.GetHour();
	pNoticeData->struTime.byMinute = m_dtNoticeTime.GetMinute();
	pNoticeData->struTime.bySecond = m_dtNoticeTime.GetSecond();

	strncpy((char*)pNoticeData->byNoticeNumber,m_strNoticeNumber,MAX_NOTICE_NUMBER_LEN);
	strncpy((char*)pNoticeData->byNoticeTheme,m_strNoticeTheme,MAX_NOTICE_THEME_LEN);
	strncpy((char*)pNoticeData->byNoticeDetail,m_strNoticeDetail,MAX_NOTICE_DETAIL_LEN);

	pNoticeData->byLevel = m_comboNoticeLevel.GetItemData(m_comboNoticeLevel.GetCurSel());
    
	int nPicIndex = 0;
	for (int i = 0; i < MAX_NOTICE_PIC_NUM; i++)
	{
		CFile picFile;
		if (picFile.Open(m_strPicPath[i],CFile::modeRead|CFile::shareDenyWrite,NULL))
		{   
			DWORD dwFileLength = picFile.GetLength();
			picFile.SeekToBegin();
			pNoticeData->struNoticePic[nPicIndex].dwPicDataLen = dwFileLength;
			pNoticeData->struNoticePic[nPicIndex].pPicData = new BYTE[dwFileLength];
			picFile.Read(pNoticeData->struNoticePic[nPicIndex].pPicData,dwFileLength);
			pNoticeData->byPicNum++;
			nPicIndex++;
			picFile.Close();
		}
	}
	
}


