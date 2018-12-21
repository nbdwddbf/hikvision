//DlgScreenLogoCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgScreenLogoCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenLogoCfg dialog


CDlgScreenLogoCfg::CDlgScreenLogoCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScreenLogoCfg::IDD, pParent)
, m_lUploadHandle(-1)
{
	//{{AFX_DATA_INIT(CDlgScreenLogoCfg)
	m_csFilePath = _T("");
	m_byLogoSequence = 1;
	m_byMapNum = 1;
	m_byScreenIndex = 1;
	m_wSourWidth = 1;
	m_wSourHeight = 1;
	m_csProgress = _T("");
	//}}AFX_DATA_INIT
}

CDlgScreenLogoCfg::~CDlgScreenLogoCfg()
{

}
void CDlgScreenLogoCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScreenLogoCfg)
	DDX_Control(pDX, IDC_PROGRESS_UPLOAD, m_progress);
	DDX_Control(pDX, IDC_COMBO_USETYPE, m_cmUseType);
	DDX_Control(pDX, IDC_COMBO_LOGOSTATUS, m_cmLogoStatus);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_csFilePath);
	DDX_Text(pDX, IDC_EDIT_LOGOSEQUENCE, m_byLogoSequence);
	DDX_Text(pDX, IDC_EDIT_MAPNUM, m_byMapNum);
	DDX_Text(pDX, IDC_EDIT_SCREENINDEX, m_byScreenIndex);
	DDX_Text(pDX, IDC_EDIT_SOURWIDTH, m_wSourWidth);
	DDX_Text(pDX, IDC_EDIT_SOURHEIGHT, m_wSourHeight);
	DDX_Text(pDX, IDC_STATIC_PROGRESS, m_csProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScreenLogoCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgScreenLogoCfg)
	ON_BN_CLICKED(IDC_BTN_BROWSEFILE, OnBtnBrowsefile)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_CTRL, OnBtnCtrl)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenLogoCfg message handlers

BOOL CDlgScreenLogoCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitComboBox();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_cmLogoStatus.SetCurSel(0);
	m_cmUseType.SetCurSel(0);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	UpdateData(FALSE);
	SetTimer(NULL, 1000, NULL);
	return TRUE; 
}

void CDlgScreenLogoCfg::InitComboBox()
{
	char szLan[128] = {0};
	m_cmUseType.ResetContent();
	g_StringLanType(szLan, "OSD", "OSD");
	m_cmUseType.AddString(szLan);
	g_StringLanType(szLan, "底图", "BACKGROUND PICTURE");
	m_cmUseType.AddString(szLan);

	m_cmLogoStatus.ResetContent();
	g_StringLanType(szLan, "显示", "SHOW");
	m_cmLogoStatus.AddString(szLan);
	g_StringLanType(szLan, "隐藏", "HIDD");
	m_cmLogoStatus.AddString(szLan);
	UpdateData(FALSE);
}

void CDlgScreenLogoCfg::OnBtnBrowsefile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	if (m_cmUseType.GetCurSel() == -1)
	{
		MessageBox("请先选择图片用途");
		return;
	}
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
			//logo大小小于100K
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

void CDlgScreenLogoCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struPicCfg, 0, sizeof(m_struPicCfg));
	m_struPicCfg.dwSize = sizeof(m_struPicCfg);
	m_struPicCfg.byUseType = 1;
	m_struPicCfg.bySequence = m_byLogoSequence;
	m_struPicCfg.struBasemapCfg.byMapNum = m_byMapNum;
	m_struPicCfg.struBasemapCfg.byScreenIndex = m_byScreenIndex;
	m_struPicCfg.struBasemapCfg.wSourHeight = m_wSourHeight;
	m_struPicCfg.struBasemapCfg.wSourWidth = m_wSourWidth;

//#ifdef CVCS_DEMO_V11
	m_lUploadHandle = NET_DVR_PicUpload(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_csFilePath, &m_struPicCfg);
	if (m_lUploadHandle == -1)
	{
		MessageBox("NET_DVR_PicUpload failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PicUpload failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PicUpload succ");
	}
//#endif
}

void CDlgScreenLogoCfg::OnBtnCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BYTE byCtrlCmd = 0;
	if (m_cmLogoStatus.GetCurSel() == 0)
	{
		byCtrlCmd = NET_DVR_SHOWLOGO;
	}
	else if (m_cmLogoStatus.GetCurSel() == 1)
	{
		byCtrlCmd = NET_DVR_HIDELOGO;
	}
	BYTE byUseType = m_cmUseType.GetCurSel()+1;
//#ifdef CVCS_DEMO_V11
	if (!NET_DVR_PicControl(g_struDeviceInfo[m_iDeviceIndex].lLoginID, byUseType, m_byLogoSequence, byCtrlCmd))
	{
		MessageBox("NET_DVR_PicControl Failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PicControl Failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PicControl Succ");
	}
//#endif
}

void CDlgScreenLogoCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgScreenLogoCfg::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgScreenLogoCfg::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	int iPos = 0;
	CString csStr;
	char sTemp[128] = {0};
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
//#ifdef DVCS_DEMO
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
//#endif
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}
