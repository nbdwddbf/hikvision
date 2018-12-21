#ifndef __MCU_GENERAL_DEFINE_H__
#define __MCU_GENERAL_DEFINE_H__

#define MAX_XML_ELEM_LEN       128
//---------------------------------------------------------------
#define MAX_MEMBER_COUNT       256
#define MAX_LOOP_TREM_COUNT    256
#define MAX_WIN_TERM_COUNT     256
#define MAX_MEMBER_VIEW_COUNT  256
//---------------------------------------------------------------
#define MAX_TERM_COUNT  64
#define MAX_GROUP_COUNT 32

//---------------------------------------------------------------
//ª·“ÈÃÌº”
struct Member
{
    DWORD  dwID;
    char   szTermNO[MAX_XML_ELEM_LEN];
    char   szIsChairMan[MAX_XML_ELEM_LEN];
};
struct LoopTerminal
{
    DWORD  dwID;
	char   szTermNO[MAX_XML_ELEM_LEN];
};
struct WinTerminal
{
    DWORD  dwWinNO;
    char   szTermNO[MAX_XML_ELEM_LEN];
    BOOL   bFixed;
};
struct MemberView
{
	//DWORD  dwID;
    char   szID[MAX_XML_ELEM_LEN];
    char   szViewMode[MAX_XML_ELEM_LEN];
    char   szTermNO[MAX_XML_ELEM_LEN];
};
//struct SoundIntensityPriorityForLayout
//{
//	BOOL    bEnable;
//	DWORD   dwWinNO;
//};
struct Loop
{
	BOOL           bEnable;
	DWORD          dwLoopInterval;
	LoopTerminal   lstLoopTerm[MAX_LOOP_TREM_COUNT];	
};
struct ConferenceLayout
{
	char                             szWinMode[MAX_XML_ELEM_LEN];
	//<SoundIntensityPriority>
	BOOL    bSoundIntensPriEnable;
	DWORD   dwWinNO;
	//</SoundIntensityPriority>
	WinTerminal                      lstWinTerm[MAX_WIN_TERM_COUNT];
	Loop                             struLoop;
	
};
struct ConferenceTime
{
	char szStartTime[MAX_XML_ELEM_LEN];
	char szEndTime  [MAX_XML_ELEM_LEN];
};
struct Regular
{
	char  szRegularType[MAX_XML_ELEM_LEN];
	char  szWeekDate[MAX_XML_ELEM_LEN];
	DWORD dwMonthDate;
	DWORD dwRepeatTimes;
};
//struct SoundIntensityPriorityForBase
//{
//	DWORD   dwTimeDelay;
//};
struct ConferenceBasicInfo
{
	char                          szConfName[MAX_XML_ELEM_LEN];
    char                          szTimeType[MAX_XML_ELEM_LEN];
	ConferenceTime                struConfTime;
    DWORD                         dwDuration;
	char                          szConfContent[MAX_XML_ELEM_LEN];
	DWORD                         dwMemberNum;
	Member                        lstMember[MAX_XML_ELEM_LEN];
	char                          szConfType[MAX_XML_ELEM_LEN];
	Regular                       struRegular;
	char                          szNotification[MAX_XML_ELEM_LEN];
	DWORD                         dwAutoRemindTime;
	//<SoundIntensityPriority>
	DWORD   dwTimeDelay;
	//<SoundIntensityPriority>
};
struct Conference
{
	char                szID[MAX_XML_ELEM_LEN];
	BOOL                bEnabled;
	ConferenceBasicInfo struBaseInfo;
	ConferenceLayout    struLayout;
	MemberView          lstMembView[MAX_MEMBER_VIEW_COUNT];
	
};

//---------------------------------------------------------------
struct TermGroupInfo
{
	char  szID[MAX_XML_ELEM_LEN];
	BOOL  bEnabled;
	char  szGroupName[MAX_XML_ELEM_LEN];
	DWORD dwTermNum;
	char  TermNOList[MAX_TERM_COUNT][MAX_XML_ELEM_LEN];
};
//---------------------------------------------------------------

#endif