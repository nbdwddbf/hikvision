// DlgInfoDiffusionContent.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionContent.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionContent dialog


CDlgInfoDiffusionContent::CDlgInfoDiffusionContent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionContent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionContent)
	m_dwLayerNo = 0;
	m_dwMarqueeScrollSpeed = 0;
	m_dwMaterialID = 0;
	m_dwPosHeight = 0;
	m_dwPosWidth = 0;
	m_dwPosX = 0;
	m_dwPosY = 0;
	m_dwDuration = 0;
	m_bFontEnable = FALSE;
	m_dwBackGreen = 0;
	m_dwBackRed = 0;
	m_dwBackBlue = 0;
	m_dwFontBlue = 0;
	m_dwFontGreen = 0;
	m_dwFontRed = 0;
	m_dwFontSize = 0;
	m_dwFontSpeed = 0;
	m_dwTransparent = 0;
	//}}AFX_DATA_INIT
	m_bNewOrEdit = TRUE; //新建
	memset(&m_struContent, 0, sizeof(m_struContent));
	m_nCurSelItem = -1;
}


void CDlgInfoDiffusionContent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionContent)
	DDX_Control(pDX, IDC_COMBO_SWITCH_EFFECT1, m_cmbSwitchEffect);
	DDX_Control(pDX, IDC_COMBO_FONT, m_cmbFont);
	DDX_Control(pDX, IDC_COMBO_WIN_MATERIAL, m_cmbWinMaterialType);
	DDX_Control(pDX, IDC_COMBO_STATIC_MATERIAL_TYPE, m_cmbStaticMaterialType);
	DDX_Control(pDX, IDC_LIST_PLAY, m_listPlay);
	DDX_Control(pDX, IDC_COMBO_EFFECT, m_cmbEffect);
	DDX_Control(pDX, IDC_COMBO_DURATION_TYPE, m_cmbDurationType);
	DDX_Control(pDX, IDC_COMBO_MARQUEE_SCROLL_TYPE, m_cmbMarqueeScrollType);
	DDX_Control(pDX, IDC_COMBO_MARQUEE_SCROLL_DIRECTION, m_cmbMarqueeScrollDiretion);
	DDX_Text(pDX, IDC_EDIT_LAYER_NO, m_dwLayerNo);
	DDX_Text(pDX, IDC_EDIT_MARQUEE_SCROLL_SPEED, m_dwMarqueeScrollSpeed);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_ID, m_dwMaterialID);
	DDX_Text(pDX, IDC_EDIT_POS_HEIGHT, m_dwPosHeight);
	DDX_Text(pDX, IDC_EDIT_POS_WIDTH, m_dwPosWidth);
	DDX_Text(pDX, IDC_EDIT_POS_X, m_dwPosX);
	DDX_Text(pDX, IDC_EDIT_POS_Y, m_dwPosY);
	DDX_Text(pDX, IDC_EDIT_DURATION, m_dwDuration);
	DDX_Check(pDX, IDC_CHECK_FONT_ENABLE, m_bFontEnable);
	DDX_Text(pDX, IDC_EDIT_BACK_GREEN, m_dwBackGreen);
	DDX_Text(pDX, IDC_EDIT_BACK_RED, m_dwBackRed);
	DDX_Text(pDX, IDC_EDIT_BACK_BLUE, m_dwBackBlue);
	DDX_Text(pDX, IDC_EDIT_FONT_BLUE, m_dwFontBlue);
	DDX_Text(pDX, IDC_EDIT_FONT_GREEN, m_dwFontGreen);
	DDX_Text(pDX, IDC_EDIT_FONT_RED, m_dwFontRed);
	DDX_Text(pDX, IDC_EDIT_FONT_SIZE, m_dwFontSize);
	DDX_Text(pDX, IDC_EDIT_FONT_SPEED, m_dwFontSpeed);
	DDX_Text(pDX, IDC_EDIT_TRANSPARENT, m_dwTransparent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionContent, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionContent)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_CBN_SELCHANGE(IDC_COMBO_EFFECT, OnSelchangeComboEffect)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PLAY, OnClickListPlay)
	ON_CBN_SELCHANGE(IDC_COMBO_WIN_MATERIAL, OnSelchangeComboWinMaterial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionContent message handlers

void CDlgInfoDiffusionContent::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgInfoDiffusionContent::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struContent.struPosition.dwPositionX = m_dwPosX;
	m_struContent.struPosition.dwPositionY = m_dwPosY;
	m_struContent.struPosition.dwWidth = m_dwPosWidth;
	m_struContent.struPosition.dwHeight = m_dwPosHeight;
	m_struContent.dwLayerID = m_dwLayerNo;
	int nSel = m_cmbWinMaterialType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbWinMaterialType.GetLBText(nSel, m_struContent.sWinMaterialType);
	if (0 == strcmp(m_struContent.sWinMaterialType, "static"))
	{
		nSel = m_cmbStaticMaterialType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbStaticMaterialType.GetLBText(nSel, m_struContent.sStaticMaterialType);
	}
	else
	{
		memset(m_struContent.sStaticMaterialType, 0, sizeof(m_struContent.sStaticMaterialType));
	}

	CDialog::OnOK();
}

BOOL CDlgInfoDiffusionContent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitPlayListCtrl();
	if (m_bNewOrEdit)
	{
		SetWindowText("新建窗口");
	}
	else
	{
		SetWindowText("编辑窗口");
		UpdateContent();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionContent::SetContent(const LPNET_DVR_CONTENT lpstruContent)
{
	m_bNewOrEdit = FALSE; //编辑
	memcpy(&m_struContent, lpstruContent, sizeof(*lpstruContent));
}

void CDlgInfoDiffusionContent::GetContent(LPNET_DVR_CONTENT lpstruContent)
{
	if (lpstruContent == NULL)
	{
		return;
	}
	memcpy(lpstruContent, &m_struContent, sizeof(m_struContent));
}

void CDlgInfoDiffusionContent::UpdateContent()
{
	m_dwPosX = m_struContent.struPosition.dwPositionX;
	m_dwPosY = m_struContent.struPosition.dwPositionY;
	m_dwPosWidth = m_struContent.struPosition.dwWidth;
	m_dwPosHeight = m_struContent.struPosition.dwHeight;
	m_dwLayerNo = m_struContent.dwLayerID;
	m_cmbWinMaterialType.SetCurSel(m_cmbWinMaterialType.FindString(-1, m_struContent.sWinMaterialType));
	OnSelchangeComboWinMaterial();
	if (0 == strcmp(m_struContent.sWinMaterialType, "static"))
	{
		m_cmbStaticMaterialType.SetCurSel(m_cmbStaticMaterialType.FindString(-1, m_struContent.sStaticMaterialType));
	}
	else
	{
		m_cmbStaticMaterialType.SetCurSel(-1);
	}
	RefreshPlayList();
	UpdatePlayItem(m_nCurSelItem);

	UpdateData(FALSE);
}

void CDlgInfoDiffusionContent::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int nIndex = m_listPlay.GetItemCount();
	if (nIndex >= MAX_ITEMS_A_PLAYLIST)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "播放列表已满", "The play list is full.");
		g_StringLanType(szLan2, "窗口管理", "Window Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}

	m_struContent.struPlayList[nIndex].dwPlayID = nIndex+1;
	m_struContent.struPlayList[nIndex].dwMaterialID = m_dwMaterialID;
	int nSel = m_cmbEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbEffect.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].szPlayEffect);
	if (0 == strcmp(m_struContent.struPlayList[nIndex].szPlayEffect, "marquee"))
	{
		nSel = m_cmbMarqueeScrollType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbMarqueeScrollType.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struMarquee.szScrollType);
		nSel = m_cmbMarqueeScrollDiretion.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbMarqueeScrollDiretion.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struMarquee.szScrollDirection);
		m_struContent.struPlayList[nIndex].struMarquee.dwScrollSpeed = m_dwMarqueeScrollSpeed;
	}
	nSel = m_cmbDurationType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbDurationType.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struPlayDuration.szDurationType);
	m_struContent.struPlayList[nIndex].struPlayDuration.dwDuration = m_dwDuration;

	m_struContent.struPlayList[nIndex].struCharactersEffect.dwFontSize = m_dwFontSize;
	m_struContent.struPlayList[nIndex].struCharactersEffect.bySubtitlesEnabled = m_bFontEnable;
	nSel = m_cmbFont.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbFont.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struCharactersEffect.szScrollDirection);
	m_struContent.struPlayList[nIndex].struCharactersEffect.dwScrollSpeed = m_dwFontSpeed;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struFontColor.dwRed = m_dwFontRed;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struFontColor.dwGreen = m_dwFontGreen;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struFontColor.dwBlue =  m_dwFontBlue;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struBackColor.dwRed = m_dwBackRed;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struBackColor.dwGreen = m_dwBackGreen;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struBackColor.dwBlue =  m_dwBackBlue;
	m_struContent.struPlayList[nIndex].struCharactersEffect.dwBackTransparent = m_dwTransparent;
	
	nSel = m_cmbSwitchEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSwitchEffect.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].szSwitchEffect);

	CString str;
	str.Format("%d", nIndex+1);
	m_listPlay.InsertItem(nIndex, str);
	m_listPlay.SetItemState(m_nCurSelItem, 0, -1);
	m_listPlay.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listPlay.SetFocus();
	m_nCurSelItem = nIndex;
	RefreshPlayItem(nIndex);
}

void CDlgInfoDiffusionContent::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelItem < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请先选择播放项目", "Please choose a play item first.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	for (int nCnt = m_nCurSelItem; nCnt < m_listPlay.GetItemCount()-1; nCnt++)
	{
		m_listPlay.SetItemText(nCnt, 1, m_listPlay.GetItemText(nCnt+1, 1));
		m_listPlay.SetItemText(nCnt, 2, m_listPlay.GetItemText(nCnt+1, 2));
		m_listPlay.SetItemText(nCnt, 3, m_listPlay.GetItemText(nCnt+1, 3));
		m_listPlay.SetItemText(nCnt, 4, m_listPlay.GetItemText(nCnt+1, 4));
		m_listPlay.SetItemText(nCnt, 5, m_listPlay.GetItemText(nCnt+1, 5));
		m_listPlay.SetItemText(nCnt, 6, m_listPlay.GetItemText(nCnt+1, 6));
		m_listPlay.SetItemText(nCnt, 7, m_listPlay.GetItemText(nCnt+1, 7));
		m_listPlay.SetItemText(nCnt, 8, m_listPlay.GetItemText(nCnt+1, 8));
		m_listPlay.SetItemText(nCnt, 9, m_listPlay.GetItemText(nCnt+1, 9));
		m_listPlay.SetItemText(nCnt, 10, m_listPlay.GetItemText(nCnt+1, 10));
		m_listPlay.SetItemText(nCnt, 11, m_listPlay.GetItemText(nCnt+1, 11));
		m_listPlay.SetItemText(nCnt, 12, m_listPlay.GetItemText(nCnt+1, 12));
		m_listPlay.SetItemText(nCnt, 13, m_listPlay.GetItemText(nCnt+1, 13));
		m_listPlay.SetItemText(nCnt, 14, m_listPlay.GetItemText(nCnt+1, 14));
		m_struContent.struPlayList[nCnt].dwMaterialID = m_struContent.struPlayList[nCnt+1].dwMaterialID;
		memcpy(m_struContent.struPlayList[nCnt].szPlayEffect, m_struContent.struPlayList[nCnt+1].szPlayEffect, sizeof(m_struContent.struPlayList[nCnt].szPlayEffect));
		memcpy(m_struContent.struPlayList[nCnt].struMarquee.szScrollType, m_struContent.struPlayList[nCnt+1].struMarquee.szScrollType, sizeof(m_struContent.struPlayList[nCnt].struMarquee.szScrollType));
		memcpy(m_struContent.struPlayList[nCnt].struMarquee.szScrollDirection, m_struContent.struPlayList[nCnt+1].struMarquee.szScrollDirection, sizeof(m_struContent.struPlayList[nCnt].struMarquee.szScrollDirection));
		m_struContent.struPlayList[nCnt].struMarquee.dwScrollSpeed = m_struContent.struPlayList[nCnt+1].struMarquee.dwScrollSpeed;
		memcpy(m_struContent.struPlayList[nCnt].struPlayDuration.szDurationType, m_struContent.struPlayList[nCnt+1].struPlayDuration.szDurationType, sizeof(m_struContent.struPlayList[nCnt].struPlayDuration.szDurationType));
		m_struContent.struPlayList[nCnt].struPlayDuration.dwDuration = m_struContent.struPlayList[nCnt+1].struPlayDuration.dwDuration;

		m_struContent.struPlayList[nCnt].struCharactersEffect.dwFontSize = m_struContent.struPlayList[nCnt+1].struCharactersEffect.dwFontSize;
		memcpy(m_struContent.struPlayList[nCnt].struCharactersEffect.szScrollDirection,m_struContent.struPlayList[nCnt+1].struCharactersEffect.szScrollDirection,sizeof(m_struContent.struPlayList[nCnt].struCharactersEffect.szScrollDirection));
		m_struContent.struPlayList[nCnt].struCharactersEffect.dwScrollSpeed = m_struContent.struPlayList[nCnt+1].struCharactersEffect.dwScrollSpeed;
		m_struContent.struPlayList[nCnt].struCharactersEffect.struFontColor.dwRed = m_struContent.struPlayList[nCnt+1].struCharactersEffect.struFontColor.dwRed;
		m_struContent.struPlayList[nCnt].struCharactersEffect.struFontColor.dwGreen = m_struContent.struPlayList[nCnt+1].struCharactersEffect.struFontColor.dwGreen;
		m_struContent.struPlayList[nCnt].struCharactersEffect.struFontColor.dwBlue =  m_struContent.struPlayList[nCnt+1].struCharactersEffect.struFontColor.dwBlue;
		m_struContent.struPlayList[nCnt].struCharactersEffect.struBackColor.dwRed = m_struContent.struPlayList[nCnt+1].struCharactersEffect.struBackColor.dwRed;
		m_struContent.struPlayList[nCnt].struCharactersEffect.struBackColor.dwGreen = m_struContent.struPlayList[nCnt+1].struCharactersEffect.struBackColor.dwGreen;
		m_struContent.struPlayList[nCnt].struCharactersEffect.struBackColor.dwBlue =  m_struContent.struPlayList[nCnt+1].struCharactersEffect.struBackColor.dwBlue;
		m_struContent.struPlayList[nCnt].struCharactersEffect.dwBackTransparent = m_struContent.struPlayList[nCnt+1].struCharactersEffect.dwBackTransparent;
		memcpy(m_struContent.struPlayList[nCnt].szSwitchEffect,m_struContent.struPlayList[nCnt+1].szSwitchEffect,sizeof(m_struContent.struPlayList[nCnt].szSwitchEffect));
	}
	memset(&m_struContent.struPlayList[m_listPlay.GetItemCount()-1], 0, sizeof(m_struContent.struPlayList[m_listPlay.GetItemCount()-1]));
	m_listPlay.DeleteItem(m_listPlay.GetItemCount()-1);
	m_nCurSelItem = -1;
}

void CDlgInfoDiffusionContent::OnBtnMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_nCurSelItem < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请先选择播放项目", "Please choose a play item first.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}

	int  nIndex = m_nCurSelItem;
	memset(&m_struContent.struPlayList[nIndex], 0, sizeof(m_struContent.struPlayList[nIndex]));
	m_struContent.struPlayList[nIndex].dwPlayID = nIndex+1;
	m_struContent.struPlayList[nIndex].dwMaterialID = m_dwMaterialID;
	int nSel = m_cmbEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbEffect.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].szPlayEffect);
	if (0 == strcmp(m_struContent.struPlayList[nIndex].szPlayEffect, "marquee"))
	{
		nSel = m_cmbMarqueeScrollType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbMarqueeScrollType.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struMarquee.szScrollType);
		nSel = m_cmbMarqueeScrollDiretion.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		m_cmbMarqueeScrollDiretion.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struMarquee.szScrollDirection);
		m_struContent.struPlayList[nIndex].struMarquee.dwScrollSpeed = m_dwMarqueeScrollSpeed;
	}
	nSel = m_cmbDurationType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbDurationType.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struPlayDuration.szDurationType);
	m_struContent.struPlayList[nIndex].struPlayDuration.dwDuration = m_dwDuration;

	m_struContent.struPlayList[nIndex].struCharactersEffect.dwFontSize = m_dwFontSize;
	m_struContent.struPlayList[nIndex].struCharactersEffect.bySubtitlesEnabled = m_bFontEnable;
	nSel = m_cmbFont.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbFont.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].struCharactersEffect.szScrollDirection);
	m_struContent.struPlayList[nIndex].struCharactersEffect.dwScrollSpeed = m_dwFontSpeed;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struFontColor.dwRed = m_dwFontRed;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struFontColor.dwGreen = m_dwFontGreen;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struFontColor.dwBlue =  m_dwFontBlue;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struBackColor.dwRed = m_dwBackRed;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struBackColor.dwGreen = m_dwBackGreen;
	m_struContent.struPlayList[nIndex].struCharactersEffect.struBackColor.dwBlue =  m_dwBackBlue;
	m_struContent.struPlayList[nIndex].struCharactersEffect.dwBackTransparent = m_dwTransparent;
	
	nSel = m_cmbSwitchEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "窗口配置", "Windows Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSwitchEffect.GetLBText(nSel, (char*)m_struContent.struPlayList[nIndex].szSwitchEffect);

	RefreshPlayItem(nIndex);
}

void CDlgInfoDiffusionContent::InitPlayListCtrl()
{
	DWORD dwExStyle = m_listPlay.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listPlay.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listPlay.InsertColumn(0, szLan);
	m_listPlay.SetColumnWidth(0, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "素材编号", "Material No.");
	m_listPlay.InsertColumn(1, szLan);
	m_listPlay.SetColumnWidth(1, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "播放效果", "Play Effect");
	m_listPlay.InsertColumn(2, szLan);
	m_listPlay.SetColumnWidth(2, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "播放时间类型", "Play Duration Type");
	m_listPlay.InsertColumn(3, szLan);
	m_listPlay.SetColumnWidth(3, 100);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "时间", "Duration");
	m_listPlay.InsertColumn(4, szLan);
	m_listPlay.SetColumnWidth(4, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "滚动类型", "Scroll Type");
	m_listPlay.InsertColumn(5, szLan);
	m_listPlay.SetColumnWidth(5, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "方向", "Direction");
	m_listPlay.InsertColumn(6, szLan);
	m_listPlay.SetColumnWidth(6, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "速度", "Speed");
	m_listPlay.InsertColumn(7, szLan);
	m_listPlay.SetColumnWidth(7, 60);

	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"字体大小","FontSize");
	m_listPlay.InsertColumn(8,szLan);
	m_listPlay.SetColumnWidth(8,60);

	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"字体颜色","FontColor");
	m_listPlay.InsertColumn(9,szLan);
	m_listPlay.SetColumnWidth(9,60);

	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"背景颜色","BackColor");
	m_listPlay.InsertColumn(10,szLan);
	m_listPlay.SetColumnWidth(10,60);

	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"文字滚动方向","ScrollDirection");
	m_listPlay.InsertColumn(11,szLan);
	m_listPlay.SetColumnWidth(11,60);

	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"文字滚动速度","ScrollSpeed");
	m_listPlay.InsertColumn(12,szLan);
	m_listPlay.SetColumnWidth(12,60);


	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"背景透明度","BackTransparent");
	m_listPlay.InsertColumn(13,szLan);
	m_listPlay.SetColumnWidth(13,60);

	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"窗口素材切换效果","SwitchEffect");
	m_listPlay.InsertColumn(14,szLan);
	m_listPlay.SetColumnWidth(14,60);


}

void CDlgInfoDiffusionContent::RefreshPlayList()
{
	m_listPlay.DeleteAllItems();
	for (int nCnt = 0; nCnt < MAX_ITEMS_A_PLAYLIST; nCnt++)
	{
		if (0 == m_struContent.struPlayList[nCnt].dwPlayID)
		{
			break;
		}
		CString str;
		str.Format("%d", nCnt+1);
		m_listPlay.InsertItem(nCnt, str);
		m_listPlay.SetItemState(m_nCurSelItem, 0, -1);
		m_listPlay.SetItemState(nCnt, LVIS_SELECTED, LVIS_SELECTED);
		m_listPlay.SetFocus();
		m_nCurSelItem = nCnt;
		RefreshPlayItem(nCnt);
	}
}

void CDlgInfoDiffusionContent::RefreshPlayItem(int nItemIndex)
{
	if (nItemIndex < 0 && nItemIndex >= MAX_ITEMS_A_PLAYLIST)
	{
		return;
	}
	CString str;
	str.Format("%d", m_struContent.struPlayList[nItemIndex].dwMaterialID);
	m_listPlay.SetItemText(nItemIndex, 1, str);
	m_listPlay.SetItemText(nItemIndex, 2, m_struContent.struPlayList[nItemIndex].szPlayEffect);
	m_listPlay.SetItemText(nItemIndex, 3, m_struContent.struPlayList[nItemIndex].struPlayDuration.szDurationType);
	str.Format("%d", m_struContent.struPlayList[nItemIndex].struPlayDuration.dwDuration);
	m_listPlay.SetItemText(nItemIndex, 4, str);
	if (0 == strcmp(m_struContent.struPlayList[nItemIndex].szPlayEffect, "marquee"))
	{
		m_listPlay.SetItemText(nItemIndex, 5, m_struContent.struPlayList[nItemIndex].struMarquee.szScrollType);
		m_listPlay.SetItemText(nItemIndex, 6, m_struContent.struPlayList[nItemIndex].struMarquee.szScrollDirection);
		str.Format("%d", m_struContent.struPlayList[nItemIndex].struMarquee.dwScrollSpeed);
		m_listPlay.SetItemText(nItemIndex, 7, str);
	}
	else
	{
		m_listPlay.SetItemText(nItemIndex, 5, _T(""));
		m_listPlay.SetItemText(nItemIndex, 6, _T(""));
		m_listPlay.SetItemText(nItemIndex, 7, _T(""));
	}
	str.Format("%d",m_struContent.struPlayList[nItemIndex].struCharactersEffect.dwFontSize);
	m_listPlay.SetItemText(nItemIndex, 8, str);
	str.Format("(%d,%d,%d)",m_struContent.struPlayList[nItemIndex].struCharactersEffect.struFontColor.dwRed,
		m_struContent.struPlayList[nItemIndex].struCharactersEffect.struFontColor.dwGreen,
		m_struContent.struPlayList[nItemIndex].struCharactersEffect.struFontColor.dwBlue);
	m_listPlay.SetItemText(nItemIndex, 9, str);
	str.Format("(%d,%d,%d)",m_struContent.struPlayList[nItemIndex].struCharactersEffect.struBackColor.dwRed,
		m_struContent.struPlayList[nItemIndex].struCharactersEffect.struBackColor.dwGreen,
		m_struContent.struPlayList[nItemIndex].struCharactersEffect.struBackColor.dwBlue);
	m_listPlay.SetItemText(nItemIndex, 10, str);
	m_listPlay.SetItemText(nItemIndex,11,m_struContent.struPlayList[nItemIndex].struCharactersEffect.szScrollDirection);
	str.Format("%d",m_struContent.struPlayList[nItemIndex].struCharactersEffect.dwScrollSpeed);
	m_listPlay.SetItemText(nItemIndex, 12, str);
	m_listPlay.SetItemText(nItemIndex,14,m_struContent.struPlayList[nItemIndex].szSwitchEffect);
	str.Format("%d",m_struContent.struPlayList[nItemIndex].struCharactersEffect.dwBackTransparent);
	m_listPlay.SetItemText(nItemIndex, 13, str);
}

void CDlgInfoDiffusionContent::UpdatePlayItem(int nItemIndex)
{
	if (nItemIndex < 0 && nItemIndex >= MAX_ITEMS_A_PLAYLIST)
	{
		return;
	}
	m_dwMaterialID = m_struContent.struPlayList[nItemIndex].dwMaterialID;
	m_cmbEffect.SetCurSel(m_cmbEffect.FindString(-1, (char*)m_struContent.struPlayList[nItemIndex].szPlayEffect));
	OnSelchangeComboEffect();
	m_cmbDurationType.SetCurSel(m_cmbDurationType.FindString(-1, (char*)m_struContent.struPlayList[nItemIndex].struPlayDuration.szDurationType));
	m_dwDuration = m_struContent.struPlayList[nItemIndex].struPlayDuration.dwDuration;
	m_cmbMarqueeScrollType.SetCurSel(m_cmbMarqueeScrollType.FindString(-1, (char*)m_struContent.struPlayList[nItemIndex].struMarquee.szScrollType));
	m_cmbMarqueeScrollDiretion.SetCurSel(m_cmbMarqueeScrollDiretion.FindString(-1, (char*)m_struContent.struPlayList[nItemIndex].struMarquee.szScrollDirection));
	m_dwMarqueeScrollSpeed = m_struContent.struPlayList[nItemIndex].struMarquee.dwScrollSpeed;
	m_dwFontSize= m_struContent.struPlayList[nItemIndex].struCharactersEffect.dwFontSize;
	m_bFontEnable = m_struContent.struPlayList[nItemIndex].struCharactersEffect.bySubtitlesEnabled;
	m_cmbFont.SetCurSel(m_cmbFont.FindString(-1,(char*)m_struContent.struPlayList[nItemIndex].struCharactersEffect.szScrollDirection));
	m_dwFontSpeed = m_struContent.struPlayList[nItemIndex].struCharactersEffect.dwScrollSpeed  ;
	m_dwFontRed = m_struContent.struPlayList[nItemIndex].struCharactersEffect.struFontColor.dwRed ;
	m_dwFontGreen = m_struContent.struPlayList[nItemIndex].struCharactersEffect.struFontColor.dwGreen ;
	m_dwFontBlue = m_struContent.struPlayList[nItemIndex].struCharactersEffect.struFontColor.dwBlue ;
	m_dwBackRed = m_struContent.struPlayList[nItemIndex].struCharactersEffect.struBackColor.dwRed ;
	m_dwBackGreen = m_struContent.struPlayList[nItemIndex].struCharactersEffect.struBackColor.dwGreen ;
	m_dwBackBlue = m_struContent.struPlayList[nItemIndex].struCharactersEffect.struBackColor.dwBlue ;
	m_dwTransparent = m_struContent.struPlayList[nItemIndex].struCharactersEffect.dwBackTransparent ;
	m_cmbSwitchEffect.SetCurSel(m_cmbSwitchEffect.FindString(-1,(char*)m_struContent.struPlayList[nItemIndex].szSwitchEffect));

	UpdateData(FALSE);
}

void CDlgInfoDiffusionContent::OnSelchangeComboEffect() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strPlayEffect;
	m_cmbEffect.GetLBText(nSel, strPlayEffect);
	if (0 == strcmp(strPlayEffect, "marquee"))
	{
		GetDlgItem(IDC_COMBO_MARQUEE_SCROLL_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MARQUEE_SCROLL_DIRECTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MARQUEE_SCROLL_SPEED)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_MARQUEE_SCROLL_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MARQUEE_SCROLL_DIRECTION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MARQUEE_SCROLL_SPEED)->EnableWindow(FALSE);
	}
}

void CDlgInfoDiffusionContent::OnClickListPlay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listPlay.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelItem = m_listPlay.GetNextSelectedItem(pos);
		UpdatePlayItem(m_nCurSelItem);
	}
	
	*pResult = 0;
}

void CDlgInfoDiffusionContent::OnSelchangeComboWinMaterial() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbWinMaterialType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strMaterialType;
	m_cmbWinMaterialType.GetLBText(nSel, strMaterialType);
	if (0 == strcmp(strMaterialType, "static"))
	{
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_TYPE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_STATIC_MATERIAL_TYPE)->EnableWindow(FALSE);
	}
}
