// DlgInfoDiffusionClock.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionClock dialog


CDlgInfoDiffusionClock::CDlgInfoDiffusionClock(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionClock::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionClock)
	m_bIconEnable = FALSE;
	m_bHmsEnable = FALSE;
	m_bWeekEnable = FALSE;
	m_bYmdEnable = FALSE;
	m_dwBackPic = 0;
	m_dwClockH = 0;
	m_dwIconH = 0;
	m_szIconType = _T("");
	m_dwIconW = 0;
	m_dwIconX = 0;
	m_dwIconY = 0;
	m_dwClockW = 0;
	m_dwHmsBackB = 0;
	m_dwHmsBackG = 0;
	m_dwHmsBackR = 0;
	m_dwHmsFontB = 0;
	m_dwHmsFontG = 0;
	m_dwHmsFontR = 0;
	m_dwWeekBackB = 0;
	m_dwWeekBackG = 0;
	m_dwWeekBackR = 0;
	m_dwWeekFontB = 0;
	m_dwWeekFontG = 0;
	m_dwWeekFontR = 0;
	m_dwWeekFontSize = 0;
	m_dwWeekH = 0;
	m_dwWeekW = 0;
	m_dwWeekX = 0;
	m_dwWeekY = 0;
	m_dwYmdFontB = 0;
	m_dwYmdBackB = 0;
	m_dwYmdBackG = 0;
	m_dwYmdBackR = 0;
	m_dwYmdFontSize = 0;
	m_dwYmdFontG = 0;
	m_dwYmdH = 0;
	m_dwYmdW = 0;
	m_dwYmdX = 0;
	m_dwYmdY = 0;
	m_dwYmsFontSize = 0;
	m_dwYmsH = 0;
	m_dwYmsW = 0;
	m_dwYmsX = 0;
	m_dwYmsY = 0;
	m_dwYmdFontR = 0;
	//}}AFX_DATA_INIT

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
}


void CDlgInfoDiffusionClock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionClock)
	DDX_Check(pDX, IDC_CHECK_COLCK_ICON, m_bIconEnable);
	DDX_Check(pDX, IDC_CHECK_HMS, m_bHmsEnable);
	DDX_Check(pDX, IDC_CHECK_WEEK, m_bWeekEnable);
	DDX_Check(pDX, IDC_CHECK_YMD, m_bYmdEnable);
	DDX_Text(pDX, IDC_EDIT_CLOCK_BACK_PIC, m_dwBackPic);
	DDX_Text(pDX, IDC_EDIT_CLOCK_HEIGHT, m_dwClockH);
	DDX_Text(pDX, IDC_EDIT_CLOCK_ICON_HEIGHT, m_dwIconH);
	DDX_Text(pDX, IDC_EDIT_CLOCK_ICON_TYPE, m_szIconType);
	DDX_Text(pDX, IDC_EDIT_CLOCK_ICON_WIDTH, m_dwIconW);
	DDX_Text(pDX, IDC_EDIT_CLOCK_ICON_X, m_dwIconX);
	DDX_Text(pDX, IDC_EDIT_CLOCK_ICON_Y, m_dwIconY);
	DDX_Text(pDX, IDC_EDIT_CLOCKWIDTH, m_dwClockW);
	DDX_Text(pDX, IDC_EDIT_HMS_BACK_B, m_dwHmsBackB);
	DDX_Text(pDX, IDC_EDIT_HMS_BACK_G, m_dwHmsBackG);
	DDX_Text(pDX, IDC_EDIT_HMS_BACK_R, m_dwHmsBackR);
	DDX_Text(pDX, IDC_EDIT_HMS_FONT_B, m_dwHmsFontB);
	DDX_Text(pDX, IDC_EDIT_HMS_FONT_G, m_dwHmsFontG);
	DDX_Text(pDX, IDC_EDIT_HMS_FONT_R, m_dwHmsFontR);
	DDX_Text(pDX, IDC_EDIT_WEEK_BACK_B, m_dwWeekBackB);
	DDX_Text(pDX, IDC_EDIT_WEEK_BACK_G, m_dwWeekBackG);
	DDX_Text(pDX, IDC_EDIT_WEEK_BACK_R, m_dwWeekBackR);
	DDX_Text(pDX, IDC_EDIT_WEEK_FONT_B, m_dwWeekFontB);
	DDX_Text(pDX, IDC_EDIT_WEEK_FONT_G, m_dwWeekFontG);
	DDX_Text(pDX, IDC_EDIT_WEEK_FONT_R, m_dwWeekFontR);
	DDX_Text(pDX, IDC_EDIT_WEEK_FONT_SIZE, m_dwWeekFontSize);
	DDX_Text(pDX, IDC_EDIT_WEEK_HEIGHT, m_dwWeekH);
	DDX_Text(pDX, IDC_EDIT_WEEK_WIDTH, m_dwWeekW);
	DDX_Text(pDX, IDC_EDIT_WEEK_X, m_dwWeekX);
	DDX_Text(pDX, IDC_EDIT_WEEK_Y, m_dwWeekY);
	DDX_Text(pDX, IDC_EDIT_YMD_B, m_dwYmdFontB);
	DDX_Text(pDX, IDC_EDIT_YMD_BACK_B, m_dwYmdBackB);
	DDX_Text(pDX, IDC_EDIT_YMD_BACK_G, m_dwYmdBackG);
	DDX_Text(pDX, IDC_EDIT_YMD_BACK_R, m_dwYmdBackR);
	DDX_Text(pDX, IDC_EDIT_YMD_FONT_SIZE, m_dwYmdFontSize);
	DDX_Text(pDX, IDC_EDIT_YMD_G, m_dwYmdFontG);
	DDX_Text(pDX, IDC_EDIT_YMD_HEIGHT, m_dwYmdH);
	DDX_Text(pDX, IDC_EDIT_YMD_WIDTH, m_dwYmdW);
	DDX_Text(pDX, IDC_EDIT_YMD_X, m_dwYmdX);
	DDX_Text(pDX, IDC_EDIT_YMD_Y, m_dwYmdY);
	DDX_Text(pDX, IDC_EDIT_YMS_FONT_SIZE, m_dwYmsFontSize);
	DDX_Text(pDX, IDC_EDIT_YMS_HEIGHT, m_dwYmsH);
	DDX_Text(pDX, IDC_EDIT_YMS_WIDTH, m_dwYmsW);
	DDX_Text(pDX, IDC_EDIT_YMS_X, m_dwYmsX);
	DDX_Text(pDX, IDC_EDIT_YMS_Y, m_dwYmsY);
	DDX_Text(pDX, IDC_EDIT1_YMD_R, m_dwYmdFontR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionClock, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionClock)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionClock message handlers


void CDlgInfoDiffusionClock::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struMaterial->struStaticMaterial.struLock.dwTotalHeight = m_dwClockH;
	m_struMaterial->struStaticMaterial.struLock.dwTotalWidth = m_dwClockW;
	m_struMaterial->struStaticMaterial.struLock.dwBackPicId = m_dwBackPic;
	m_struMaterial->struStaticMaterial.struLock.byIconEnable = m_bIconEnable;
	m_struMaterial->struStaticMaterial.struLock.dwIconX = m_dwIconX;
	m_struMaterial->struStaticMaterial.struLock.dwIconY = m_dwIconY;
	m_struMaterial->struStaticMaterial.struLock.dwIconH = m_dwIconH;
	m_struMaterial->struStaticMaterial.struLock.dwIconW = m_dwIconW;
	memcpy(m_struMaterial->struStaticMaterial.struLock.szIconType,m_szIconType,sizeof(m_szIconType));

	m_struMaterial->struStaticMaterial.struLock.struYmd.byEnable = m_bYmdEnable;
	m_struMaterial->struStaticMaterial.struLock.struYmd.dwFontSize = m_dwYmdFontSize;
	m_struMaterial->struStaticMaterial.struLock.struYmd.struFontColor.dwRed = m_dwYmdFontR;
	m_struMaterial->struStaticMaterial.struLock.struYmd.struFontColor.dwGreen = m_dwYmdFontG;
	m_struMaterial->struStaticMaterial.struLock.struYmd.struFontColor.dwBlue = m_dwYmdFontB;
	m_struMaterial->struStaticMaterial.struLock.struYmd.struBackColor.dwRed = m_dwYmdBackR;
	m_struMaterial->struStaticMaterial.struLock.struYmd.struBackColor.dwGreen = m_dwYmdBackG;
	m_struMaterial->struStaticMaterial.struLock.struYmd.struBackColor.dwBlue = m_dwYmdBackB;
	m_struMaterial->struStaticMaterial.struLock.struYmd.dwPositionX = m_dwYmdX;
	m_struMaterial->struStaticMaterial.struLock.struYmd.dwPositionY = m_dwYmdY;
	m_struMaterial->struStaticMaterial.struLock.struYmd.dwHeight = m_dwYmdH;
	m_struMaterial->struStaticMaterial.struLock.struYmd.dwWidth = m_dwYmdW;

	m_struMaterial->struStaticMaterial.struLock.struHms.byEnable = m_bHmsEnable;
	m_struMaterial->struStaticMaterial.struLock.struHms.dwFontSize = m_dwYmsFontSize;
	m_struMaterial->struStaticMaterial.struLock.struHms.struFontColor.dwRed = m_dwHmsFontR;
	m_struMaterial->struStaticMaterial.struLock.struHms.struFontColor.dwGreen = m_dwHmsFontG;
	m_struMaterial->struStaticMaterial.struLock.struHms.struFontColor.dwBlue = m_dwHmsFontB;
	m_struMaterial->struStaticMaterial.struLock.struHms.struBackColor.dwRed = m_dwHmsBackR;
	m_struMaterial->struStaticMaterial.struLock.struHms.struBackColor.dwGreen = m_dwHmsBackG;
	m_struMaterial->struStaticMaterial.struLock.struHms.struBackColor.dwBlue = m_dwHmsBackB;
	m_struMaterial->struStaticMaterial.struLock.struHms.dwPositionX = m_dwYmsX;
	m_struMaterial->struStaticMaterial.struLock.struHms.dwPositionY = m_dwYmsY;
	m_struMaterial->struStaticMaterial.struLock.struHms.dwHeight = m_dwYmsH;
	m_struMaterial->struStaticMaterial.struLock.struHms.dwWidth = m_dwYmsW;

	m_struMaterial->struStaticMaterial.struLock.struWeek.byEnable = m_bWeekEnable;
	m_struMaterial->struStaticMaterial.struLock.struWeek.dwFontSize = m_dwWeekFontSize;
	m_struMaterial->struStaticMaterial.struLock.struWeek.struFontColor.dwRed = m_dwWeekFontR;
	m_struMaterial->struStaticMaterial.struLock.struWeek.struFontColor.dwGreen = m_dwWeekFontG;
	m_struMaterial->struStaticMaterial.struLock.struWeek.struFontColor.dwBlue = m_dwWeekFontB;
	m_struMaterial->struStaticMaterial.struLock.struWeek.struBackColor.dwRed = m_dwWeekBackR;
	m_struMaterial->struStaticMaterial.struLock.struWeek.struBackColor.dwGreen = m_dwWeekBackG;
	m_struMaterial->struStaticMaterial.struLock.struWeek.struBackColor.dwBlue = m_dwWeekBackB;
	m_struMaterial->struStaticMaterial.struLock.struWeek.dwPositionX = m_dwWeekX;
	m_struMaterial->struStaticMaterial.struLock.struWeek.dwPositionY = m_dwWeekY;
	m_struMaterial->struStaticMaterial.struLock.struWeek.dwHeight = m_dwWeekH;
	m_struMaterial->struStaticMaterial.struLock.struWeek.dwWidth = m_dwWeekW;

	CDialog::OnOK();

}

void CDlgInfoDiffusionClock::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
