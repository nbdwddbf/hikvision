// DlgInfoDiffusionClockWeather.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionClockWeather.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionClockWeather dialog


CDlgInfoDiffusionClockWeather::CDlgInfoDiffusionClockWeather(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionClockWeather::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionClockWeather)
	m_byAir = FALSE;
	m_byCity = FALSE;
	m_byContent = FALSE;
	m_byHum = FALSE;
	m_byTemp = FALSE;
	m_byUpdate = FALSE;
	m_byDate = FALSE;
	m_byIcon = FALSE;
	m_byWind = FALSE;
	m_dwAirBackB = 0;
	m_dwAirBackG = 0;
	m_dwAirBackR = 0;
	m_dwAirFontB = 0;
	m_dwAirFontG = 0;
	m_dwAirFontR = 0;
	m_dwAirFontSize = 0;
	m_dwAirH = 0;
	m_dwAirW = 0;
	m_dwAirX = 0;
	m_dwAirY = 0;
	m_dwCityBackB = 0;
	m_dwCityBackG = 0;
	m_dwCityBackR = 0;
	m_dwCityFontB = 0;
	m_dwCityFontG = 0;
	m_dwCityFontR = 0;
	m_dwCityFontSize = 0;
	m_dwCityH = 0;
	m_dwCityW = 0;
	m_dwCityX = 0;
	m_dwCityY = 0;
	m_dwContentBackB = 0;
	m_dwContentBackG = 0;
	m_dwContentBackR = 0;
	m_dwContentFontB = 0;
	m_dwContentFontG = 0;
	m_dwContentFontR = 0;
	m_dwContentFontSize = 0;
	m_dwContentH = 0;
	m_dwContentW = 0;
	m_dwContentY = 0;
	m_dwContentX = 0;
	m_dwDateBackB = 0;
	m_dwDateBackG = 0;
	m_dwDateBackR = 0;
	m_dwDateFontB = 0;
	m_dwDateFontG = 0;
	m_dwDateFontR = 0;
	m_dwDateFontSize = 0;
	m_dwDateH = 0;
	m_dwDateW = 0;
	m_dwDateX = 0;
	m_dwDateY = 0;
	m_dwHumBackB = 0;
	m_dwHumBackG = 0;
	m_dwHumBackR = 0;
	m_dwHumFontB = 0;
	m_dwHumFontG = 0;
	m_dwHumFontR = 0;
	m_dwHumFontSize = 0;
	m_dwHumH = 0;
	m_dwHumX = 0;
	m_dwHumY = 0;
	m_dwTempBackB = 0;
	m_dwTempBackG = 0;
	m_dwTempBackR = 0;
	m_dwTempFontB = 0;
	m_dwTempFontG = 0;
	m_dwTempFontR = 0;
	m_dwTempFontSize = 0;
	m_dwTempH = 0;
	m_dwTempW = 0;
	m_dwTempX = 0;
	m_dwTempY = 0;
	m_dwUpdateBackB = 0;
	m_dwUpdateBackG = 0;
	m_dwUpdateBackR = 0;
	m_dwUpdateFontB = 0;
	m_dwUpdateFontG = 0;
	m_dwUpdateFontR = 0;
	m_dwUpdateFontSize = 0;
	m_dwUpdateH = 0;
	m_dwUpdateW = 0;
	m_dwUpdateX = 0;
	m_dwUpdateY = 0;
	m_dwWeateBackPic = 0;
	m_dwWeaIconW = 0;
	m_dwWeaH = 0;
	m_dwWeaIconH = 0;
	m_dwWeaIconX = 0;
	m_dwWeaIconY = 0;
	m_dwWeaW = 0;
	m_dwWindFontB = 0;
	m_dwWindFontG = 0;
	m_dwWindFontR = 0;
	m_dwWindBackB = 0;
	m_dwWindBackG = 0;
	m_dwWindBackR = 0;
	m_dwWindFontSize = 0;
	m_dwWindX = 0;
	m_dwWindY = 0;
	m_dwWindH = 0;
	m_dwHumW = 0;
	m_dwWindW = 0;
	//}}AFX_DATA_INIT
}


void CDlgInfoDiffusionClockWeather::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionClockWeather)
	DDX_Check(pDX, IDC_CHECK_AIR, m_byAir);
	DDX_Check(pDX, IDC_CHECK_CITY, m_byCity);
	DDX_Check(pDX, IDC_CHECK_CONTENT, m_byContent);
	DDX_Check(pDX, IDC_CHECK_HUM, m_byHum);
	DDX_Check(pDX, IDC_CHECK_TEMP, m_byTemp);
	DDX_Check(pDX, IDC_CHECK_UPDATE, m_byUpdate);
	DDX_Check(pDX, IDC_CHECK_WEATHER_DATE, m_byDate);
	DDX_Check(pDX, IDC_CHECK_WEATHER_ICON, m_byIcon);
	DDX_Check(pDX, IDC_CHECK_WIND, m_byWind);
	DDX_Text(pDX, IDC_EDIT_AIR_BACK_B, m_dwAirBackB);
	DDX_Text(pDX, IDC_EDIT_AIR_BACK_G, m_dwAirBackG);
	DDX_Text(pDX, IDC_EDIT_AIR_BACK_R, m_dwAirBackR);
	DDX_Text(pDX, IDC_EDIT_AIR_FONT_B, m_dwAirFontB);
	DDX_Text(pDX, IDC_EDIT_AIR_FONT_G, m_dwAirFontG);
	DDX_Text(pDX, IDC_EDIT_AIR_FONT_R, m_dwAirFontR);
	DDX_Text(pDX, IDC_EDIT_AIR_FONT_SIZE, m_dwAirFontSize);
	DDX_Text(pDX, IDC_EDIT_AIR_HEIGHT, m_dwAirH);
	DDX_Text(pDX, IDC_EDIT_AIR_WIDTH, m_dwAirW);
	DDX_Text(pDX, IDC_EDIT_AIR_X, m_dwAirX);
	DDX_Text(pDX, IDC_EDIT_AIR_Y, m_dwAirY);
	DDX_Text(pDX, IDC_EDIT_CITY_BACK_B, m_dwCityBackB);
	DDX_Text(pDX, IDC_EDIT_CITY_BACK_G, m_dwCityBackG);
	DDX_Text(pDX, IDC_EDIT_CITY_BACK_R, m_dwCityBackR);
	DDX_Text(pDX, IDC_EDIT_CITY_FONT_B, m_dwCityFontB);
	DDX_Text(pDX, IDC_EDIT_CITY_FONT_G, m_dwCityFontG);
	DDX_Text(pDX, IDC_EDIT_CITY_FONT_R, m_dwCityFontR);
	DDX_Text(pDX, IDC_EDIT_CITY_FONT_SIZE, m_dwCityFontSize);
	DDX_Text(pDX, IDC_EDIT_CITY_HEIGHT, m_dwCityH);
	DDX_Text(pDX, IDC_EDIT_CITY_WIDTH, m_dwCityW);
	DDX_Text(pDX, IDC_EDIT_CITY_X, m_dwCityX);
	DDX_Text(pDX, IDC_EDIT_CITY_Y, m_dwCityY);
	DDX_Text(pDX, IDC_EDIT_CONTENT_BACK_B, m_dwContentBackB);
	DDX_Text(pDX, IDC_EDIT_CONTENT_BACK_G, m_dwContentBackG);
	DDX_Text(pDX, IDC_EDIT_CONTENT_BACK_R, m_dwContentBackR);
	DDX_Text(pDX, IDC_EDIT_CONTENT_FONT_B, m_dwContentFontB);
	DDX_Text(pDX, IDC_EDIT_CONTENT_FONT_G, m_dwContentFontG);
	DDX_Text(pDX, IDC_EDIT_CONTENT_FONT_R, m_dwContentFontR);
	DDX_Text(pDX, IDC_EDIT_CONTENT_FONT_SIZE, m_dwContentFontSize);
	DDX_Text(pDX, IDC_EDIT_CONTENT_HEIGHT, m_dwContentH);
	DDX_Text(pDX, IDC_EDIT_CONTENT_WIDTH, m_dwContentW);
	DDX_Text(pDX, IDC_EDIT_CONTENT_Y, m_dwContentY);
	DDX_Text(pDX, IDC_EDIT_CONTENT_X, m_dwContentX);
	DDX_Text(pDX, IDC_EDIT_DATE_BACK_B, m_dwDateBackB);
	DDX_Text(pDX, IDC_EDIT_DATE_BACK_G, m_dwDateBackG);
	DDX_Text(pDX, IDC_EDIT_DATE_BACK_R, m_dwDateBackR);
	DDX_Text(pDX, IDC_EDIT_DATE_FONT_B, m_dwDateFontB);
	DDX_Text(pDX, IDC_EDIT_DATE_FONT_G, m_dwDateFontG);
	DDX_Text(pDX, IDC_EDIT_DATE_FONT_R, m_dwDateFontR);
	DDX_Text(pDX, IDC_EDIT_DATE_FONT_SIZE, m_dwDateFontSize);
	DDX_Text(pDX, IDC_EDIT_DATE_HIGHT, m_dwDateH);
	DDX_Text(pDX, IDC_EDIT_DATE_WIDTH, m_dwDateW);
	DDX_Text(pDX, IDC_EDIT_DATE_X, m_dwDateX);
	DDX_Text(pDX, IDC_EDIT_DATE_Y, m_dwDateY);
	DDX_Text(pDX, IDC_EDIT_HUM_BACK_B, m_dwHumBackB);
	DDX_Text(pDX, IDC_EDIT_HUM_BACK_G, m_dwHumBackG);
	DDX_Text(pDX, IDC_EDIT_HUM_BACK_R, m_dwHumBackR);
	DDX_Text(pDX, IDC_EDIT_HUM_FONT_B, m_dwHumFontB);
	DDX_Text(pDX, IDC_EDIT_HUM_FONT_G, m_dwHumFontG);
	DDX_Text(pDX, IDC_EDIT_HUM_FONT_R, m_dwHumFontR);
	DDX_Text(pDX, IDC_EDIT_HUM_FONT_SIZE, m_dwHumFontSize);
	DDX_Text(pDX, IDC_EDIT_HUM_HEIGHT, m_dwHumH);
	DDX_Text(pDX, IDC_EDIT_HUM_X, m_dwHumX);
	DDX_Text(pDX, IDC_EDIT_HUM_Y, m_dwHumY);
	DDX_Text(pDX, IDC_EDIT_TEMP_BACK_B, m_dwTempBackB);
	DDX_Text(pDX, IDC_EDIT_TEMP_BACK_G, m_dwTempBackG);
	DDX_Text(pDX, IDC_EDIT_TEMP_BACK_R, m_dwTempBackR);
	DDX_Text(pDX, IDC_EDIT_TEMP_FONT_B, m_dwTempFontB);
	DDX_Text(pDX, IDC_EDIT_TEMP_FONT_G, m_dwTempFontG);
	DDX_Text(pDX, IDC_EDIT_TEMP_FONT_R, m_dwTempFontR);
	DDX_Text(pDX, IDC_EDIT_TEMP_FONT_SIZE, m_dwTempFontSize);
	DDX_Text(pDX, IDC_EDIT_TEMP_HEIGHT, m_dwTempH);
	DDX_Text(pDX, IDC_EDIT_TEMP_WIDTH, m_dwTempW);
	DDX_Text(pDX, IDC_EDIT_TEMP_X, m_dwTempX);
	DDX_Text(pDX, IDC_EDIT_TEMP_Y, m_dwTempY);
	DDX_Text(pDX, IDC_EDIT_UPDATE_BACK_B, m_dwUpdateBackB);
	DDX_Text(pDX, IDC_EDIT_UPDATE_BACK_G, m_dwUpdateBackG);
	DDX_Text(pDX, IDC_EDIT_UPDATE_BACK_R, m_dwUpdateBackR);
	DDX_Text(pDX, IDC_EDIT_UPDATE_FONT_B, m_dwUpdateFontB);
	DDX_Text(pDX, IDC_EDIT_UPDATE_FONT_G, m_dwUpdateFontG);
	DDX_Text(pDX, IDC_EDIT_UPDATE_FONT_R, m_dwUpdateFontR);
	DDX_Text(pDX, IDC_EDIT_UPDATE_FONT_SIZE, m_dwUpdateFontSize);
	DDX_Text(pDX, IDC_EDIT_UPDATE_HEIGHT, m_dwUpdateH);
	DDX_Text(pDX, IDC_EDIT_UPDATE_WIDTH, m_dwUpdateW);
	DDX_Text(pDX, IDC_EDIT_UPDATE_X, m_dwUpdateX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_Y, m_dwUpdateY);
	DDX_Text(pDX, IDC_EDIT_WEATHER_BACK_PIC, m_dwWeateBackPic);
	DDX_Text(pDX, IDC_EDIT_WEATHER_ICON_WIDTH, m_dwWeaIconW);
	DDX_Text(pDX, IDC_EDIT_WEATHER_HEIGHT, m_dwWeaH);
	DDX_Text(pDX, IDC_EDIT_WEATHER_ICON_HEIGHT, m_dwWeaIconH);
	DDX_Text(pDX, IDC_EDIT_WEATHER_ICON_X, m_dwWeaIconX);
	DDX_Text(pDX, IDC_EDIT_WEATHER_ICON_Y, m_dwWeaIconY);
	DDX_Text(pDX, IDC_EDIT_WEATHER_WIDTH, m_dwWeaW);
	DDX_Text(pDX, IDC_EDIT_WIDN_FONT_B, m_dwWindFontB);
	DDX_Text(pDX, IDC_EDIT_WIDN_FONT_G, m_dwWindFontG);
	DDX_Text(pDX, IDC_EDIT_WIDN_FONT_R, m_dwWindFontR);
	DDX_Text(pDX, IDC_EDIT_WIND_BACK_B, m_dwWindBackB);
	DDX_Text(pDX, IDC_EDIT_WIND_BACK_G, m_dwWindBackG);
	DDX_Text(pDX, IDC_EDIT_WIND_BACK_R, m_dwWindBackR);
	DDX_Text(pDX, IDC_EDIT_WIND_FONT_SIZE, m_dwWindFontSize);
	DDX_Text(pDX, IDC_EDIT_WIND_X, m_dwWindX);
	DDX_Text(pDX, IDC_EDIT_WIND_Y, m_dwWindY);
	DDX_Text(pDX, IDC_EDIT_WIND_HEIGHT, m_dwWindH);
	DDX_Text(pDX, IDC_EDIT_HUM_WIDTH, m_dwHumW);
	DDX_Text(pDX, IDC_EDIT_WIND_WIDTH, m_dwWindW);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionClockWeather, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionClockWeather)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionClockWeather message handlers


void CDlgInfoDiffusionClockWeather::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struMaterial->struStaticMaterial.struWeather.dwTotalHeight = m_dwWeaH;
	m_struMaterial->struStaticMaterial.struWeather.dwTotalWidth = m_dwWeaW;
	m_struMaterial->struStaticMaterial.struWeather.dwBackPicId = m_dwWeateBackPic;
	m_struMaterial->struStaticMaterial.struWeather.byIconEnable = m_byIcon;
	m_struMaterial->struStaticMaterial.struWeather.dwIconX = m_dwWeaIconX;
	m_struMaterial->struStaticMaterial.struWeather.dwIconY = m_dwWeaIconY;
	m_struMaterial->struStaticMaterial.struWeather.dwIconH = m_dwWeaIconH;
	m_struMaterial->struStaticMaterial.struWeather.dwIconW = m_dwWeaIconW;
	
	m_struMaterial->struStaticMaterial.struWeather.struDate.byEnable = m_byDate;
	m_struMaterial->struStaticMaterial.struWeather.struDate.dwFontSize = m_dwDateFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struDate.struFontColor.dwRed = m_dwDateFontR;
	m_struMaterial->struStaticMaterial.struWeather.struDate.struFontColor.dwGreen = m_dwDateFontG;
	m_struMaterial->struStaticMaterial.struWeather.struDate.struFontColor.dwBlue = m_dwDateFontB;
	m_struMaterial->struStaticMaterial.struWeather.struDate.struBackColor.dwRed = m_dwDateBackR;
	m_struMaterial->struStaticMaterial.struWeather.struDate.struBackColor.dwGreen = m_dwDateBackG;
	m_struMaterial->struStaticMaterial.struWeather.struDate.struBackColor.dwBlue = m_dwDateBackB;
	m_struMaterial->struStaticMaterial.struWeather.struDate.dwPositionX = m_dwDateX;
	m_struMaterial->struStaticMaterial.struWeather.struDate.dwPositionY = m_dwDateY;
	m_struMaterial->struStaticMaterial.struWeather.struDate.dwHeight = m_dwDateH;
	m_struMaterial->struStaticMaterial.struWeather.struDate.dwWidth = m_dwDateW;

	m_struMaterial->struStaticMaterial.struWeather.struTemp.byEnable = m_byTemp;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.dwFontSize = m_dwTempFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.struFontColor.dwRed = m_dwTempFontR;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.struFontColor.dwGreen = m_dwTempFontG;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.struFontColor.dwBlue = m_dwTempFontB;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.struBackColor.dwRed = m_dwTempBackR;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.struBackColor.dwGreen = m_dwTempBackG;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.struBackColor.dwBlue = m_dwTempBackB;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.dwPositionX = m_dwTempX;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.dwPositionY = m_dwTempY;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.dwHeight = m_dwTempH;
	m_struMaterial->struStaticMaterial.struWeather.struTemp.dwWidth = m_dwTempW;

	m_struMaterial->struStaticMaterial.struWeather.struContent.byEnable = m_byContent;
	m_struMaterial->struStaticMaterial.struWeather.struContent.dwFontSize = m_dwContentFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struContent.struFontColor.dwRed = m_dwContentFontR;
	m_struMaterial->struStaticMaterial.struWeather.struContent.struFontColor.dwGreen = m_dwContentFontG;
	m_struMaterial->struStaticMaterial.struWeather.struContent.struFontColor.dwBlue = m_dwContentFontB;
	m_struMaterial->struStaticMaterial.struWeather.struContent.struBackColor.dwRed = m_dwContentBackR;
	m_struMaterial->struStaticMaterial.struWeather.struContent.struBackColor.dwGreen = m_dwContentBackG;
	m_struMaterial->struStaticMaterial.struWeather.struContent.struBackColor.dwBlue = m_dwContentBackB;
	m_struMaterial->struStaticMaterial.struWeather.struContent.dwPositionX = m_dwContentX;
	m_struMaterial->struStaticMaterial.struWeather.struContent.dwPositionY = m_dwContentY;
	m_struMaterial->struStaticMaterial.struWeather.struContent.dwHeight = m_dwContentH;
	m_struMaterial->struStaticMaterial.struWeather.struContent.dwWidth = m_dwContentW;

	m_struMaterial->struStaticMaterial.struWeather.struCity.byEnable = m_byCity;
	m_struMaterial->struStaticMaterial.struWeather.struCity.dwFontSize = m_dwCityFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struCity.struFontColor.dwRed = m_dwCityFontR;
	m_struMaterial->struStaticMaterial.struWeather.struCity.struFontColor.dwGreen = m_dwCityFontG;
	m_struMaterial->struStaticMaterial.struWeather.struCity.struFontColor.dwBlue = m_dwCityFontB;
	m_struMaterial->struStaticMaterial.struWeather.struCity.struBackColor.dwRed = m_dwCityBackR;
	m_struMaterial->struStaticMaterial.struWeather.struCity.struBackColor.dwGreen = m_dwCityBackG;
	m_struMaterial->struStaticMaterial.struWeather.struCity.struBackColor.dwBlue = m_dwCityBackB;
	m_struMaterial->struStaticMaterial.struWeather.struCity.dwPositionX = m_dwCityX;
	m_struMaterial->struStaticMaterial.struWeather.struCity.dwPositionY = m_dwCityY;
	m_struMaterial->struStaticMaterial.struWeather.struCity.dwHeight = m_dwCityH;
	m_struMaterial->struStaticMaterial.struWeather.struCity.dwWidth = m_dwCityW;

	m_struMaterial->struStaticMaterial.struWeather.struHum.byEnable = m_byHum;
	m_struMaterial->struStaticMaterial.struWeather.struHum.dwFontSize = m_dwHumFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struHum.struFontColor.dwRed = m_dwHumFontR;
	m_struMaterial->struStaticMaterial.struWeather.struHum.struFontColor.dwGreen = m_dwHumFontG;
	m_struMaterial->struStaticMaterial.struWeather.struHum.struFontColor.dwBlue = m_dwHumFontB;
	m_struMaterial->struStaticMaterial.struWeather.struHum.struBackColor.dwRed = m_dwHumBackR;
	m_struMaterial->struStaticMaterial.struWeather.struHum.struBackColor.dwGreen = m_dwHumBackG;
	m_struMaterial->struStaticMaterial.struWeather.struHum.struBackColor.dwBlue = m_dwHumBackB;
	m_struMaterial->struStaticMaterial.struWeather.struHum.dwPositionX = m_dwHumX;
	m_struMaterial->struStaticMaterial.struWeather.struHum.dwPositionY = m_dwHumY;
	m_struMaterial->struStaticMaterial.struWeather.struHum.dwHeight = m_dwHumH;
	m_struMaterial->struStaticMaterial.struWeather.struHum.dwWidth = m_dwHumW;

	m_struMaterial->struStaticMaterial.struWeather.struAir.byEnable = m_byAir;
	m_struMaterial->struStaticMaterial.struWeather.struAir.dwFontSize = m_dwAirFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struAir.struFontColor.dwRed = m_dwAirFontR;
	m_struMaterial->struStaticMaterial.struWeather.struAir.struFontColor.dwGreen = m_dwAirFontG;
	m_struMaterial->struStaticMaterial.struWeather.struAir.struFontColor.dwBlue = m_dwAirFontB;
	m_struMaterial->struStaticMaterial.struWeather.struAir.struBackColor.dwRed = m_dwAirBackR;
	m_struMaterial->struStaticMaterial.struWeather.struAir.struBackColor.dwGreen = m_dwAirBackG;
	m_struMaterial->struStaticMaterial.struWeather.struAir.struBackColor.dwBlue = m_dwAirBackB;
	m_struMaterial->struStaticMaterial.struWeather.struAir.dwPositionX = m_dwAirX;
	m_struMaterial->struStaticMaterial.struWeather.struAir.dwPositionY = m_dwAirY;
	m_struMaterial->struStaticMaterial.struWeather.struAir.dwHeight = m_dwAirH;
	m_struMaterial->struStaticMaterial.struWeather.struAir.dwWidth = m_dwAirW;

	m_struMaterial->struStaticMaterial.struWeather.struUpdate.byEnable = m_byUpdate;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.dwFontSize = m_dwUpdateFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.struFontColor.dwRed = m_dwUpdateFontR;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.struFontColor.dwGreen = m_dwUpdateFontG;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.struFontColor.dwBlue = m_dwUpdateFontB;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.struBackColor.dwRed = m_dwUpdateBackR;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.struBackColor.dwGreen = m_dwUpdateBackG;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.struBackColor.dwBlue = m_dwUpdateBackB;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.dwPositionX = m_dwUpdateX;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.dwPositionY = m_dwUpdateY;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.dwHeight = m_dwUpdateH;
	m_struMaterial->struStaticMaterial.struWeather.struUpdate.dwWidth = m_dwUpdateW;

	m_struMaterial->struStaticMaterial.struWeather.struWind.byEnable = m_byWind;
	m_struMaterial->struStaticMaterial.struWeather.struWind.dwFontSize = m_dwWindFontSize;
	m_struMaterial->struStaticMaterial.struWeather.struWind.struFontColor.dwRed = m_dwWindFontR;
	m_struMaterial->struStaticMaterial.struWeather.struWind.struFontColor.dwGreen = m_dwWindFontG;
	m_struMaterial->struStaticMaterial.struWeather.struWind.struFontColor.dwBlue = m_dwWindFontB;
	m_struMaterial->struStaticMaterial.struWeather.struWind.struBackColor.dwRed = m_dwWindBackR;
	m_struMaterial->struStaticMaterial.struWeather.struWind.struBackColor.dwGreen = m_dwWindBackG;
	m_struMaterial->struStaticMaterial.struWeather.struWind.struBackColor.dwBlue = m_dwWindBackB;
	m_struMaterial->struStaticMaterial.struWeather.struWind.dwPositionX = m_dwWindX;
	m_struMaterial->struStaticMaterial.struWeather.struWind.dwPositionY = m_dwWindY;
	m_struMaterial->struStaticMaterial.struWeather.struWind.dwHeight = m_dwWindH;
	m_struMaterial->struStaticMaterial.struWeather.struWind.dwWidth = m_dwWindW;

	CDialog::OnOK();
	
}

void CDlgInfoDiffusionClockWeather::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
