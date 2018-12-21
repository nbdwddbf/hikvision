// DlgVcaObjectColor.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaObjectColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaObjectColor dialog


CDlgVcaObjectColor::CDlgVcaObjectColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaObjectColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaObjectColor)
	m_nColorHue = 0;
	m_nColorBrightNess = 0;
	m_nColorSaturation = 0;
	m_strPicPath = _T("");
	m_nPicHeight = 0;
	m_nPicWidth = 0;
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT

	m_pPicBuffer = NULL;
	m_nPicBufferLen = 0;
	memset(&m_struObjectColor,0,sizeof(m_struObjectColor));
    
	m_nPicDataLen = 0;
	m_nPicBufferLen = 512 * 1024; 
	m_pPicBuffer = new BYTE[m_nPicBufferLen];
}

CDlgVcaObjectColor::~CDlgVcaObjectColor()
{
	if (m_pPicBuffer != NULL)
	{
		delete[] m_pPicBuffer;
	}
}

void CDlgVcaObjectColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaObjectColor)
	DDX_Control(pDX, IDC_COMBO_COLOR_MODE, m_comboColorMode);
	DDX_Control(pDX, IDC_COMBO_PICTYPE, m_comboPicType);
	DDX_Control(pDX, IDC_COMBO_OBJECT_TYPE, m_comboObjType);
	DDX_Text(pDX, IDC_EDIT_HUE, m_nColorHue);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_nColorBrightNess);
	DDX_Text(pDX, IDC_EDIT_SATURATION, m_nColorSaturation);
	DDX_Text(pDX, IDC_EDIT_PICPATH, m_strPicPath);
	DDX_Text(pDX, IDC_EDIT_PICHEIGHT, m_nPicHeight);
	DDX_Text(pDX, IDC_EDIT_PICWIDTH, m_nPicWidth);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaObjectColor, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaObjectColor)
	ON_BN_CLICKED(IDC_BTN_SELPIC, OnBtnSelPic)
	ON_BN_CLICKED(IDC_BTN_SAVEPIC, OnBtnSavePic)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR_MODE, OnSelchangeComboColorMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaObjectColor message handlers

BOOL CDlgVcaObjectColor::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCtrlState();

	return TRUE;
}

void CDlgVcaObjectColor::OnBtnSelPic() 
{   
	CString strFilter = "jpg(*.jpg)|*.jpg|All Files (*.*)|*.*||";
	
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,this);

	if (dlg.DoModal() == IDOK)
	{   
		m_strPicPath = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PICPATH,m_strPicPath);

		GetPicSize(m_strPicPath);
		ReadPicData(m_strPicPath);
	}
}

void CDlgVcaObjectColor::OnBtnSavePic() 
{   
	if (m_struObjectColor.byColorMode != COLOR_MODE_PIC ||
		m_struObjectColor.uObjColor.struPicture.dwPicDataLen == 0)
	{
		char szText[64] = "\0";
		g_StringLanType(szText, "没有图片数据", "No picture data exist");
		AfxMessageBox(szText);
		return;
	}

	CString strFilter = "jpg(*.jpg)|*.jpg||";
	
	CFileDialog dlg(FALSE,"jpg",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,this);
	
	if (dlg.DoModal() == IDOK)
	{   
		CString strFilePath = dlg.GetPathName();
		ExportPicData(strFilePath);
	}
}

void CDlgVcaObjectColor::OnBtnGet() 
{   
	char szError[32] = "\0";
	if (!GetObjectColor())
	{
       	g_StringLanType(szError, "获取失败","Get failed");
		AfxMessageBox(szError);
		
	}
	else
	{
		LoadWndContent();
	}
}

void CDlgVcaObjectColor::OnBtnSet() 
{   
	SaveWndContent();

	char szError[32] = "\0";
	if (SetObjectColor())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaObjectColor::InitCtrlState()
{   
	m_comboObjType.ResetContent();
	m_comboColorMode.ResetContent();
	m_comboPicType.ResetContent();

	char szText[64] = "\0";
	g_StringLanType(szText, "上衣", "Coat");
	m_comboObjType.InsertString(0,szText);
	m_comboObjType.SetItemData(0,ENUM_OBJECT_TYPE_COAT);

	g_StringLanType(szText, "颜色值", "Color Value");
	m_comboColorMode.InsertString(0,szText);
	m_comboColorMode.SetItemData(0,COLOR_MODE_RGB);
	g_StringLanType(szText, "图片", "Picture");
	m_comboColorMode.InsertString(1,szText);
	m_comboColorMode.SetItemData(1,COLOR_MODE_PIC);

	m_comboPicType.InsertString(0,"jpg");
	m_comboPicType.SetItemData(0,PIC_TYPE_JPG);

	m_comboObjType.SetCurSel(0);
	m_comboColorMode.SetCurSel(0);
	m_comboPicType.SetCurSel(0);

	OnSelchangeComboColorMode();
}


void CDlgVcaObjectColor::GetPicSize(CString strFilePath)
{   
	WCHAR wszFilePath[MAX_PATH + 1] = L"\0";
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,strFilePath,strFilePath.GetLength(),wszFilePath,MAX_PATH);
 	Gdiplus::Bitmap picFile(wszFilePath);
	m_nPicWidth = picFile.GetWidth();
	m_nPicHeight = picFile.GetHeight();
	UpdateData(FALSE);
}

BOOL CDlgVcaObjectColor::ReadPicData(CString strFilePath)
{
	CFile file;
	if (!file.Open(strFilePath,CFile::modeRead,NULL))
	{
		char szText[64] = "\0";
    	g_StringLanType(szText, "读取图片文件出错", "Read picture file error");
		AfxMessageBox(szText);
		return FALSE;
	}

	DWORD dwFileLen = file.GetLength();
	if (m_nPicBufferLen < dwFileLen)
	{
		if (m_pPicBuffer != NULL)
		{
			delete[] m_pPicBuffer;
			m_pPicBuffer = NULL;
			m_nPicBufferLen = 0;
		}
	}
	
	if (m_pPicBuffer == NULL)
	{   
		m_nPicBufferLen = dwFileLen;
		m_pPicBuffer = new BYTE[m_nPicBufferLen];
	}
    
	m_nPicDataLen = dwFileLen;
	file.Read(m_pPicBuffer,m_nPicDataLen);
	file.Close();
	return TRUE;
}

BOOL CDlgVcaObjectColor::ExportPicData(CString strFilePath)
{
	CFile file;
	if (!file.Open(strFilePath,CFile::modeCreate|CFile::modeWrite))
	{
		if (!file.Open(strFilePath,CFile::modeRead,NULL))
		{
			char szText[64] = "\0";
			g_StringLanType(szText, "创建文件出错", "Create picture file error");
			AfxMessageBox(szText);
			return FALSE;
		}
	}

	if (m_struObjectColor.byColorMode != COLOR_MODE_PIC ||
		m_struObjectColor.uObjColor.struPicture.dwPicDataLen == 0)
	{
		char szText[64] = "\0";
		g_StringLanType(szText, "没有图片数据", "No picture data exist");
		AfxMessageBox(szText);
		return FALSE;
	}

	file.Write(m_pPicBuffer,m_struObjectColor.uObjColor.struPicture.dwPicDataLen);
	file.Close();
	return TRUE;
}

void CDlgVcaObjectColor::OnSelchangeComboColorMode() 
{
	int nColorModeIndex = m_comboColorMode.GetCurSel();
	if (nColorModeIndex != CB_ERR)
	{
		DWORD dwColorMode = m_comboColorMode.GetItemData(nColorModeIndex);
		
		GetDlgItem(IDC_EDIT_HUE)->EnableWindow(dwColorMode == COLOR_MODE_RGB);
		GetDlgItem(IDC_EDIT_SATURATION)->EnableWindow(dwColorMode == COLOR_MODE_RGB);
		GetDlgItem(IDC_EDIT_BRIGHTNESS)->EnableWindow(dwColorMode == COLOR_MODE_RGB);
		GetDlgItem(IDC_COMBO_PICTYPE)->EnableWindow(dwColorMode == COLOR_MODE_PIC);
		GetDlgItem(IDC_BTN_SELPIC)->EnableWindow(dwColorMode == COLOR_MODE_PIC);
		GetDlgItem(IDC_BTN_SAVEPIC)->EnableWindow(dwColorMode == COLOR_MODE_PIC);
	}
}


void CDlgVcaObjectColor::LoadWndContent()
{
	m_bEnable = m_struObjectColor.byEnable;
	
	DWORD dwColorMode = m_struObjectColor.byColorMode;
	if (dwColorMode == COLOR_MODE_RGB)
	{   
		NET_DVR_COLOR& struColor = m_struObjectColor.uObjColor.struColor;
		m_nColorHue         = struColor.byHue;
		m_nColorSaturation  = struColor.bySaturation;
		m_nColorBrightNess  = struColor.byBrightness;
		
	}
	else if (dwColorMode == COLOR_MODE_PIC)
	{   
		NET_DVR_PIC& struPic = m_struObjectColor.uObjColor.struPicture;
		m_nPicWidth      = struPic.dwPicWidth;
		m_nPicHeight     = struPic.dwPicHeight;
		m_pPicBuffer     = struPic.byPicDataBuff;
        
		int nPicTypeCount = m_comboPicType.GetCount();
		for (int i = 0; i < nPicTypeCount; i++)
		{
			if (m_comboPicType.GetItemData(i) == struPic.byPicType)
			{
				m_comboPicType.SetCurSel(i);
				break;
			}
		}
	}

	int nColorModeCount = m_comboColorMode.GetCount();
	for (int i = 0; i < nColorModeCount; i++)
	{
		if (m_comboColorMode.GetItemData(i) == dwColorMode)
		{
			m_comboColorMode.SetCurSel(i);
			break;
		}
	}

	OnSelchangeComboColorMode();

	UpdateData(FALSE);
}

void CDlgVcaObjectColor::SaveWndContent()
{   
	UpdateData(TRUE);
    
	m_struObjectColor.byEnable = m_bEnable;

	DWORD dwColorMode             = m_comboColorMode.GetItemData(m_comboColorMode.GetCurSel());
	m_struObjectColor.byColorMode = dwColorMode;
	m_struObjectColor.dwSize      = sizeof(m_struObjectColor);
	if (dwColorMode == COLOR_MODE_RGB)
	{   
		NET_DVR_COLOR& struColor = m_struObjectColor.uObjColor.struColor;
		struColor.byHue          = m_nColorHue;
		struColor.bySaturation   = m_nColorSaturation;
		struColor.byBrightness   = m_nColorBrightNess;

	}
	else if (dwColorMode == COLOR_MODE_PIC)
	{   
		NET_DVR_PIC& struPic = m_struObjectColor.uObjColor.struPicture;
		struPic.byPicType        = (BYTE)m_comboPicType.GetItemData(m_comboPicType.GetCurSel());
		struPic.dwPicDataBuffLen = m_nPicBufferLen;
		struPic.byPicDataBuff    = m_pPicBuffer;
		struPic.dwPicDataLen     = m_nPicDataLen;
		struPic.dwPicWidth       = m_nPicWidth;
	    struPic.dwPicHeight      = m_nPicHeight;
	}
}


BOOL CDlgVcaObjectColor::GetObjectColor()
{
	NET_DVR_OBJECT_COLOR_COND struObjColorCond = {0};
	struObjColorCond.dwChannel = m_lChannel;
	struObjColorCond.dwObjType = m_comboObjType.GetItemData(m_comboObjType.GetCurSel());

	m_struObjectColor.uObjColor.struPicture.dwPicDataBuffLen = m_nPicBufferLen;
	m_struObjectColor.uObjColor.struPicture.byPicDataBuff = m_pPicBuffer;

	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_OBJECT_COLOR, 1,(LPVOID)&struObjColorCond, sizeof(struObjColorCond),
		&dwStatus,&m_struObjectColor, sizeof(m_struObjectColor)) || dwStatus != 0)
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_OBJECT_COLOR Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_OBJECT_COLOR Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaObjectColor::SetObjectColor()
{
	NET_DVR_OBJECT_COLOR_COND struObjColorCond = {0};
	struObjColorCond.dwChannel = m_lChannel;
	struObjColorCond.dwObjType = m_comboObjType.GetItemData(m_comboObjType.GetCurSel());
    
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_OBJECT_COLOR,1,(LPVOID)&struObjColorCond, sizeof(struObjColorCond),
		&dwStatus,&m_struObjectColor, sizeof(m_struObjectColor)) || dwStatus != 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_OBJECT_COLOR Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_OBJECT_COLOR Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}
