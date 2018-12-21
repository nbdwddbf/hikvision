/**********************************************************
FileName:    DlgLogSearch.cpp
Description: search log     
Date:        2008/05/17
Note: 		 <global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp    
Modification History:      
<version> <time>         <desc>
<1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgLogSearch.h"
#include ".\dlglogsearch.h"


// CDlgLogSearch dialog
CDlgLogSearch * pLogSearch = NULL;

void ParaTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp)
{
    switch(stLogInfo.dwParaType)
    {
    case PARA_VIDEOOUT:
        szTemp.Format("VIDEOOUT");
        break;
    case PARA_IMAGE:
        szTemp.Format("IMAGE");
        break;
    case PARA_ENCODE:
        szTemp.Format("ENCODE");
        break;
    case PARA_NETWORK:
        szTemp.Format("NETWORK");
        break;
    case PARA_ALARM:
        szTemp.Format("ALARM");
        break;
    case PARA_EXCEPTION:
        szTemp.Format("EXCEPTION");
        break;
    case PARA_DECODER:
        szTemp.Format("DECODER");
        break;
    case PARA_RS232:
        szTemp.Format("RS232");
        break;
    case PARA_PREVIEW:
        szTemp.Format("PREVIEW");
        break;
    case PARA_SECURITY:
        szTemp.Format("SECURITY");
        break;
    case PARA_DATETIME:
        szTemp.Format("sys DATETIME");
        break;
    case PARA_FRAMETYPE:
        szTemp.Format("FRAMETYPE");
        break;
    case PARA_DETECTION:
        szTemp.Format("Detection");
        break;
    case PARA_VCA_RULE:
        szTemp.Format("VCA Rule");
        break;
    case PARA_VCA_CTRL:
        szTemp.Format("VCA Ctrl");
        break;
    case PARA_VCA_PLATE:
        szTemp.Format("VCA plate");
        break;
	//2010-04-13 
	case PARA_CODESPLITTER:
        szTemp.Format("CODESPLITTER");
        break;
    case PARA_RS485:
        szTemp.Format("RS485");
        break;
    case PARA_DEVICE:
        szTemp.Format("DEVICE");
        break;
    case PARA_HARDDISK:
        szTemp.Format("HARDDISK");
        break;
    case PARA_AUTOBOOT:
        szTemp.Format("AUTOBOOT");
        break;
    case PARA_HOLIDAY:
        szTemp.Format("HOLIDAY");
        break;
    case PARA_IPC	:
        szTemp.Format("IPC");
        break;
    default:
        break;
    }
}


/*********************************************************
Function:	AlarmMinorTypeMap
Desc:		主类型为报警的次类型映射
Input:	stLogInfo, log information; szTemp, log string;
Output:	none
Return:	none
**********************************************************/
void AlarmMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp)
{
    CString szParaType;
    switch(stLogInfo.dwMinorType)
    {
		//alarm
    case MINOR_ALARM_IN:
        szTemp.Format("ALARM_IN[%d]", stLogInfo.dwAlarmInPort);
        break;
    case MINOR_ALARM_OUT:
        szTemp.Format("ALARM_OUT[%d]",stLogInfo.dwAlarmOutPort);
        break;
    case MINOR_MOTDET_START:
        szTemp.Format("MOTDET_START[%d]", stLogInfo.dwChannel);
        break;
    case MINOR_MOTDET_STOP:
        szTemp.Format("MOTDET_STOP");
        break;
    case MINOR_HIDE_ALARM_START:
        szTemp.Format("HIDE_ALARM_START");
        break;
    case MINOR_HIDE_ALARM_STOP:
        szTemp.Format("HIDE_ALARM_STOP");
        break;
    case MINOR_VCA_ALARM_START:
        szTemp.Format("VCA_ALARM_START");
        break;
    case MINOR_VCA_ALARM_STOP:
        szTemp.Format("VCA_ALARM_STOP");
        break;
	case MINOR_NETALARM_START:
        szTemp.Format("NETALARM_START");
        break;
	case MINOR_NETALARM_STOP:
        szTemp.Format("NETALARM_STOP");
        break;
	case MINOR_WIRELESS_ALARM_START:
        szTemp.Format("WIRELESS_ALARM_START");
        break;
	case MINOR_WIRELESS_ALARM_STOP:
        szTemp.Format("WIRELESS_ALARM_STOP");
        break;
	case MINOR_PIR_ALARM_START:
        szTemp.Format("PIR_ALARM_START");
        break;
	case MINOR_PIR_ALARM_STOP:
        szTemp.Format("PIR_ALARM_STOP");
        break;
	case MINOR_CALLHELP_ALARM_START:
        szTemp.Format("CALLHELP_ALARM_START");
        break;
	case MINOR_CALLHELP_ALARM_STOP:
        szTemp.Format("CALLHELP_ALARM_STOP");
        break;
	case MINOR_DETECTFACE_ALARM_START:
        szTemp.Format("DETECTFACE_ALARM_START");
        break;
	case MINOR_DETECTFACE_ALARM_STOP:
        szTemp.Format("DETECTFACE_ALARM_STOP");
        break;
	case MINOR_VQD_ALARM_START:
		szTemp.Format("VQD Alarm Start");
		break;
	case MINOR_VQD_ALARM_STOP:
		szTemp.Format("VQD Alarm Stop");
		break;
    case MINOR_VCA_SECNECHANGE_DETECTION://场景变更侦测日志查询2013-07-17
        szTemp.Format("VCA_SECNECHANGE_DETECTION");
		break;
    case MINOR_SMART_REGION_EXITING_BEGIN:
        szTemp.Format("Region Exiting Begin");
		break;
    case MINOR_SMART_REGION_EXITING_END:
        szTemp.Format("Region Exiting End");
		break;
    case MINOR_SMART_LOITERING_BEGIN:
        szTemp.Format("Loitering Begin");
		break;
    case MINOR_SMART_LOITERING_END:
        szTemp.Format("Loitering End");
		break;
#ifdef NET_DVR_SET_TRAVERSE_PLANE_DETECTION
	case MINOR_VCA_ALARM_LINE_DETECTION_BEGIN:
		szTemp.Format("TRAVERSE_PLANE_DETECTION START");
		break;
	case MINOR_VCA_ALARM_LINE_DETECTION_END:
		szTemp.Format("TRAVERSE_PLANE_DETECTION Stop");
		break;
#endif //NET_DVR_SET_TRAVERSE_PLANE_DETECTION
	case MINOR_VCA_ALARM_INTRUDE_BEGIN:
		szTemp.Format("NTRUDE Start");
		break;
	case MINOR_VCA_ALARM_INTRUDE_END:
		szTemp.Format("NTRUDE Stop");
		break;
	case MINOR_VCA_ALARM_AUDIOINPUT:
		szTemp.Format("AudioInput Exception");
		break;
	case MINOR_VCA_ALARM_AUDIOABNORMAL:
		szTemp.Format("AudioInput Stop");
		break;
	case MINOR_VCA_DEFOCUS_DETECTION_BEGIN:
		szTemp.Format("defous detection Start");
		break;
	case MINOR_VCA_DEFOCUS_DETECTION_END:
		szTemp.Format("defous detection Stop");
		break;
	case MINOR_EXT_ALARM:
		szTemp.Format("external alarm");
		break;
	case MINOR_VCA_FACE_ALARM_BEGIN:
		szTemp.Format("SMD face alarm start");
		break;
    case MINOR_SMART_REGION_ENTRANCE_BEGIN:
        szTemp.Format("Region Entrance Begin");
        break;
    case MINOR_SMART_REGION_ENTRANCE_END:
        szTemp.Format("Region Entrance End");
        break;
    case MINOR_SMART_PEOPLE_GATHERING_BEGIN:
        szTemp.Format("People Gathering Begin");
		break;
    case MINOR_SMART_PEOPLE_GATHERING_END:
        szTemp.Format("People Gathering End");
		break;
    case MINOR_SMART_FAST_MOVING_BEGIN:
        szTemp.Format("Fast Moving Begin");
		break;
    case MINOR_SMART_FAST_MOVING_END:
        szTemp.Format("Fast Moving End");
		break;
	case MINOR_VCA_FACE_ALARM_END:
		szTemp.Format("SMD face alarm end");
		break;
	case MINOR_VCA_SCENE_CHANGE_ALARM_BEGIN:
		szTemp.Format("SMD scene change alarm start");
		break;
	case MINOR_VCA_SCENE_CHANGE_ALARM_END:
		szTemp.Format("SMD scene change alarm stop");
		break;
	case MINOR_VCA_ALARM_AUDIOINPUT_BEGIN:
		szTemp.Format("SMD alarm audio input start");
		break;
	case MINOR_VCA_ALARM_AUDIOINPUT_END:
		szTemp.Format("SMD alarm audio input stop");
		break;
	case MINOR_VCA_ALARM_AUDIOABNORMAL_BEGIN:
		szTemp.Format("SMD alarm audio abnormal start");
		break;
	case MINOR_VCA_ALARM_AUDIOABNORMAL_END:
		szTemp.Format("SMD alarm audio abnormal end");
		break;
	case MINOR_VCA_LECTURE_DETECTION_BEGIN:
		szTemp.Format("Lecture Start");
		break;
	case MINOR_VCA_LECTURE_DETECTION_END:
		szTemp.Format("Lecture End");
		break;
	case MINOR_VCA_ANSWER_DETECTION_BEGIN:
		szTemp.Format("Answering Questions Start");
		break;
	case MINOR_VCA_ANSWER_DETECTION_END:
		szTemp.Format("Answering Questions End");
		break;
    case MINOR_SMART_PARKING_BEGIN:
        szTemp.Format("Parking Begin");
		break;
    case MINOR_SMART_PARKING_END:
        szTemp.Format("Parking End");
		break;
    case MINOR_SMART_UNATTENDED_BAGGAGE_BEGIN:
        szTemp.Format("Unattended Baggage Begin");
		break;
    case MINOR_SMART_UNATTENDED_BAGGAGE_END:
        szTemp.Format("Unattended Baggage End");
		break;
    case MINOR_SMART_OBJECT_REMOVAL_BEGIN:
        szTemp.Format("Object Removal Begin");
		break;
    case MINOR_SMART_OBJECT_REMOVAL_END:
        szTemp.Format("Object Removal End");
		break;
    case MINOR_THERMAL_FIREDETECTION:
        szTemp.Format("Thermal Fire Detection Begin");
		break;
	case MINOR_THERMAL_FIREDETECTION_END:
        szTemp.Format("Thermal Fire Detection End");
		break;
    case MINOR_ALARMIN_SHORT_CIRCUIT:
        szTemp.Format("MINOR_ALARMIN_SHORT_CIRCUIT");
        break;
    case MINOR_ALARMIN_BROKEN_CIRCUIT:
        szTemp.Format("MINOR_ALARMIN_BROKEN_CIRCUIT");
        break;
    case MINOR_ALARMIN_EXCEPTION:
        szTemp.Format("MINOR_ALARMIN_EXCEPTION");
        break;
    case MINOR_ALARMIN_RESUME:
        szTemp.Format("MINOR_ALARMIN_RESUME");
        break;
    case MINOR_HOST_DESMANTLE_ALARM:
        szTemp.Format("MINOR_HOST_DESMANTLE_ALARM");
        break;
    case MINOR_HOST_DESMANTLE_RESUME:
        szTemp.Format("MINOR_HOST_DESMANTLE_RESUME");
        break;
    case MINOR_CARD_READER_DESMANTLE_ALARM:
        szTemp.Format("MINOR_CARD_READER_DESMANTLE_ALARM");
        break;
    case MINOR_CARD_READER_DESMANTLE_RESUME:
        szTemp.Format("MINOR_CARD_READER_DESMANTLE_RESUME");
        break;
    case  MINOR_CASE_SENSOR_ALARM:
        szTemp.Format(" MINOR_CASE_SENSOR_ALARM");
        break;
    case MINOR_CASE_SENSOR_RESUME:
        szTemp.Format("MINOR_CASE_SENSOR_RESUME");
        break;
    case MINOR_STRESS_ALARM:
        szTemp.Format("MINOR_STRESS_ALARM");
        break;
    case  MINOR_OFFLINE_ECENT_NEARLY_FULL:
        szTemp.Format(" MINOR_OFFLINE_ECENT_NEARLY_FULL");
        break;
    case  MINOR_CARD_MAX_AUTHENTICATE_FAIL:
        szTemp.Format(" MINOR_CARD_MAX_AUTHENTICATE_FAIL");
        break;
    case  MINOR_SD_CARD_FULL:
        szTemp.Format(" MINOR_SD_CARD_FULL");
        break;
    case  MINOR_LINKAGE_CAPTURE_PIC:
        szTemp.Format(" MINOR_LINKAGE_CAPTURE_PIC");
        break;
	case  MINOR_SECURITY_MODULE_DESMANTLE_ALARM:
		szTemp.Format(" MINOR_SECURITY_MODULE_DESMANTLE_ALARM");
		break;
	case  MINOR_SECURITY_MODULE_DESMANTLE_RESUME:
		szTemp.Format(" MINOR_SECURITY_MODULE_DESMANTLE_RESUME");
		break;
    case MINOR_SMART_VANDALPROOF_BEGIN:
        szTemp.Format("VandalProof Detection Begin");
        break;
    case MINOR_SMART_VANDALPROOF_END:
        szTemp.Format("VandalProof Detection End");
		break;
    case MINOR_FACESNAP_MATCH_ALARM_START:
        szTemp.Format("MINOR_FACESNAP_MATCH_ALARM_START");
        break;
    case MINOR_FACESNAP_MATCH_ALARM_STOP:
        szTemp.Format("MINOR_FACESNAP_MATCH_ALARM_STOP");
        break;
    case MINOR_WHITELIST_FACESNAP_MATCH_ALARM_START:
        szTemp.Format("MINOR_WHITELIST_FACESNAP_MATCH_ALARM_START");
        break;
    case MINOR_WHITELIST_FACESNAP_MATCH_ALARM_STOP:
        szTemp.Format("MINOR_WHITELIST_FACESNAP_MATCH_ALARM_STOP");
        break;
    case MINOR_THERMAL_SHIPSDETECTION:
        szTemp.Format("Ships Detection");
        break;
    case MINOR_THERMAL_THERMOMETRY_EARLYWARNING_BEGIN:
        szTemp.Format("Thermometry Early warning Begin");
        break;
    case MINOR_THERMAL_THERMOMETRY_EARLYWARNING_END:
        szTemp.Format("Thermometry Early warning End");
        break;
    case MINOR_THERMAL_THERMOMETRY_ALARM_BEGIN:
        szTemp.Format("Thermometry Alarm Begin");
        break;
    case MINOR_THERMAL_THERMOMETRY_ALARM_END:
        szTemp.Format("Thermometry Alarm End");
        break;
	case MINOR_THERMAL_THERMOMETRY_DIFF_ALARM_BEGIN:
		szTemp.Format("Thermometry Alarm Diff Begin");
		break;
	case MINOR_THERMAL_THERMOMETRY_DIFF_ALARM_END:
		szTemp.Format("Thermometry Alarm Diff End");
		break;
    case  MINOR_POS_START_ALARM:
        szTemp.Format(" MINOR_POS_START_ALARM");
        break;
    case  MINOR_POS_END_ALARM:
        szTemp.Format(" MINOR_POS_END_ALARM");
        break;
    case  MINOR_FACE_IMAGE_QUALITY_LOW:
        szTemp.Format(" MINOR_FACE_IMAGE_QUALITY_LOW");
        break;
    case  MINOR_FINGE_RPRINT_QUALITY_LOW:
        szTemp.Format(" MINOR_FINGE_RPRINT_QUALITY_LOW");
        break;
    case MINOR_FIRE_IMPORT_SHORT_CIRCUIT:
        szTemp.Format("MINOR_FIRE_IMPORT_SHORT_CIRCUIT");
        break;
    case MINOR_FIRE_IMPORT_BROKEN_CIRCUIT:
        szTemp.Format("MINOR_FIRE_IMPORT_BROKEN_CIRCUIT");
        break;
    case MINOR_FIRE_IMPORT_RESUME:
        szTemp.Format("MINOR_FIRE_IMPORT_RESUME");
        break;
    case MINOR_FIRE_BUTTON_TRIGGER:
        szTemp.Format("MINOR_FIRE_BUTTON_TRIGGER");
        break;
    case MINOR_FIRE_BUTTON_RESUME:
        szTemp.Format("MINOR_FIRE_BUTTON_RESUME");
        break;
    case MINOR_MAINTENANCE_BUTTON_TRIGGER:
        szTemp.Format("MINOR_MAINTENANCE_BUTTON_TRIGGER");
        break;
    case MINOR_MAINTENANCE_BUTTON_RESUME:
        szTemp.Format("MINOR_MAINTENANCE_BUTTON_RESUME");
        break;
    case MINOR_EMERGENCY_BUTTON_TRIGGER:
        szTemp.Format("MINOR_EMERGENCY_BUTTON_TRIGGER");
        break;
    case MINOR_EMERGENCY_BUTTON_RESUME:
        szTemp.Format("MINOR_EMERGENCY_BUTTON_RESUME");
        break;
    case MINOR_DISTRACT_CONTROLLER_ALARM:
        szTemp.Format("MINOR_DISTRACT_CONTROLLER_ALARM");
        break;
    case MINOR_DISTRACT_CONTROLLER_RESUME:
        szTemp.Format("MINOR_DISTRACT_CONTROLLER_RESUME");
        break;
    case MINOR_PERSON_DENSITY_DETECTION_START:
        szTemp.Format("MINOR_PERSON_DENSITY_DETECTION_START");
        break;
    case MINOR_PERSON_DENSITY_DETECTION_END:
        szTemp.Format("MINOR_PERSON_DENSITY_DETECTION_END");
        break;
    case MINOR_ALARM_CUSTOM1:
        szTemp.Format("MINOR_ALARM_CUSTOM1");
        break;
    case MINOR_ALARM_CUSTOM2:
        szTemp.Format("MINOR_ALARM_CUSTOM2");
        break;
    case MINOR_ALARM_CUSTOM3:
        szTemp.Format("MINOR_ALARM_CUSTOM3");
        break;
    case MINOR_ALARM_CUSTOM4:
        szTemp.Format("MINOR_ALARM_CUSTOM4");
        break;
    case MINOR_ALARM_CUSTOM5:
        szTemp.Format("MINOR_ALARM_CUSTOM5");
        break;
    case MINOR_ALARM_CUSTOM6:
        szTemp.Format("MINOR_ALARM_CUSTOM6");
        break;
    case MINOR_ALARM_CUSTOM7:
        szTemp.Format("MINOR_ALARM_CUSTOM7");
        break;
    case MINOR_ALARM_CUSTOM8:
        szTemp.Format("MINOR_ALARM_CUSTOM8");
        break;
    case MINOR_ALARM_CUSTOM9:
        szTemp.Format("MINOR_ALARM_CUSTOM9");
        break;
    case MINOR_ALARM_CUSTOM10:
        szTemp.Format("MINOR_ALARM_CUSTOM10");
        break;
    case MINOR_ALARM_CUSTOM11:
        szTemp.Format("MINOR_ALARM_CUSTOM11");
        break;
    case MINOR_ALARM_CUSTOM12:
        szTemp.Format("MINOR_ALARM_CUSTOM12");
        break;
    case MINOR_ALARM_CUSTOM13:
        szTemp.Format("MINOR_ALARM_CUSTOM13");
        break;
    case MINOR_ALARM_CUSTOM14:
        szTemp.Format("MINOR_ALARM_CUSTOM14");
        break;
    case MINOR_ALARM_CUSTOM15:
        szTemp.Format("MINOR_ALARM_CUSTOM15");
        break;
    case MINOR_ALARM_CUSTOM16:
        szTemp.Format("MINOR_ALARM_CUSTOM16");
        break;
    case MINOR_ALARM_CUSTOM17:
        szTemp.Format("MINOR_ALARM_CUSTOM17");
        break;
    case MINOR_ALARM_CUSTOM18:
        szTemp.Format("MINOR_ALARM_CUSTOM18");
        break;
    case MINOR_ALARM_CUSTOM19:
        szTemp.Format("MINOR_ALARM_CUSTOM19");
        break;
    case MINOR_ALARM_CUSTOM20:
        szTemp.Format("MINOR_ALARM_CUSTOM20");
        break;
    case MINOR_ALARM_CUSTOM21:
        szTemp.Format("MINOR_ALARM_CUSTOM21");
        break;
    case MINOR_ALARM_CUSTOM22:
        szTemp.Format("MINOR_ALARM_CUSTOM22");
        break;
    case MINOR_ALARM_CUSTOM23:
        szTemp.Format("MINOR_ALARM_CUSTOM23");
        break;
    case MINOR_ALARM_CUSTOM24:
        szTemp.Format("MINOR_ALARM_CUSTOM24");
        break;
    case MINOR_ALARM_CUSTOM25:
        szTemp.Format("MINOR_ALARM_CUSTOM25");
        break;
    case MINOR_ALARM_CUSTOM26:
        szTemp.Format("MINOR_ALARM_CUSTOM26");
        break;
    case MINOR_ALARM_CUSTOM27:
        szTemp.Format("MINOR_ALARM_CUSTOM27");
        break;
    case MINOR_ALARM_CUSTOM28:
        szTemp.Format("MINOR_ALARM_CUSTOM28");
        break;
    case MINOR_ALARM_CUSTOM29:
        szTemp.Format("MINOR_ALARM_CUSTOM29");
        break;
    case MINOR_ALARM_CUSTOM30:
        szTemp.Format("MINOR_ALARM_CUSTOM30");
        break;
    case MINOR_ALARM_CUSTOM31:
        szTemp.Format("MINOR_ALARM_CUSTOM31");
        break;
    case MINOR_ALARM_CUSTOM32:
        szTemp.Format("MINOR_ALARM_CUSTOM32");
        break;
    case MINOR_ALARM_CUSTOM33:
        szTemp.Format("MINOR_ALARM_CUSTOM33");
        break;
    case MINOR_ALARM_CUSTOM34:
        szTemp.Format("MINOR_ALARM_CUSTOM34");
        break;
    case MINOR_ALARM_CUSTOM35:
        szTemp.Format("MINOR_ALARM_CUSTOM35");
        break;
    case MINOR_ALARM_CUSTOM36:
        szTemp.Format("MINOR_ALARM_CUSTOM36");
        break;
    case MINOR_ALARM_CUSTOM37:
        szTemp.Format("MINOR_ALARM_CUSTOM37");
        break;
    case MINOR_ALARM_CUSTOM38:
        szTemp.Format("MINOR_ALARM_CUSTOM38");
        break;
    case MINOR_ALARM_CUSTOM39:
        szTemp.Format("MINOR_ALARM_CUSTOM39");
        break;
    case MINOR_ALARM_CUSTOM40:
        szTemp.Format("MINOR_ALARM_CUSTOM40");
        break;
    case MINOR_ALARM_CUSTOM41:
        szTemp.Format("MINOR_ALARM_CUSTOM41");
        break;
    case MINOR_ALARM_CUSTOM42:
        szTemp.Format("MINOR_ALARM_CUSTOM42");
        break;
    case MINOR_ALARM_CUSTOM43:
        szTemp.Format("MINOR_ALARM_CUSTOM43");
        break;
    case MINOR_ALARM_CUSTOM44:
        szTemp.Format("MINOR_ALARM_CUSTOM44");
        break;
    case MINOR_ALARM_CUSTOM45:
        szTemp.Format("MINOR_ALARM_CUSTOM45");
        break;
    case MINOR_ALARM_CUSTOM46:
        szTemp.Format("MINOR_ALARM_CUSTOM46");
        break;
    case MINOR_ALARM_CUSTOM47:
        szTemp.Format("MINOR_ALARM_CUSTOM47");
        break;
    case MINOR_ALARM_CUSTOM48:
        szTemp.Format("MINOR_ALARM_CUSTOM48");
        break;
    case MINOR_ALARM_CUSTOM49:
        szTemp.Format("MINOR_ALARM_CUSTOM49");
        break;
    case MINOR_ALARM_CUSTOM50:
        szTemp.Format("MINOR_ALARM_CUSTOM50");
        break;
    case MINOR_ALARM_CUSTOM51:
        szTemp.Format("MINOR_ALARM_CUSTOM51");
        break;
    case MINOR_ALARM_CUSTOM52:
        szTemp.Format("MINOR_ALARM_CUSTOM52");
        break;
    case MINOR_ALARM_CUSTOM53:
        szTemp.Format("MINOR_ALARM_CUSTOM53");
        break;
    case MINOR_ALARM_CUSTOM54:
        szTemp.Format("MINOR_ALARM_CUSTOM54");
        break;
    case MINOR_ALARM_CUSTOM55:
        szTemp.Format("MINOR_ALARM_CUSTOM55");
        break;
    case MINOR_ALARM_CUSTOM56:
        szTemp.Format("MINOR_ALARM_CUSTOM56");
        break;
    case MINOR_ALARM_CUSTOM57:
        szTemp.Format("MINOR_ALARM_CUSTOM57");
        break;
    case MINOR_ALARM_CUSTOM58:
        szTemp.Format("MINOR_ALARM_CUSTOM58");
        break;
    case MINOR_ALARM_CUSTOM59:
        szTemp.Format("MINOR_ALARM_CUSTOM59");
        break;
    case MINOR_ALARM_CUSTOM60:
        szTemp.Format("MINOR_ALARM_CUSTOM60");
        break;
    case MINOR_ALARM_CUSTOM61:
        szTemp.Format("MINOR_ALARM_CUSTOM61");
        break;
    case MINOR_ALARM_CUSTOM62:
        szTemp.Format("MINOR_ALARM_CUSTOM62");
        break;
    case MINOR_ALARM_CUSTOM63:
        szTemp.Format("MINOR_ALARM_CUSTOM63");
        break;
    case MINOR_ALARM_CUSTOM64:
        szTemp.Format("MINOR_ALARM_CUSTOM64");
        break;
    case MINOR_SAFETY_HELMET_ALARM_START:
        szTemp.Format("MINOR_SAFETY_HELMET_ALARM_START");
        break;
    case MINOR_SAFETY_HELMET_ALARM_STOP:
        szTemp.Format("MINOR_SAFETY_HELMET_ALARM_STOP");
        break;
    case MINOR_HFPD_ALARM_START:
        szTemp.Format("MINOR_HFPD_ALARM_START");
        break;
    case MINOR_HFPD_ALARM_STOP:
        szTemp.Format("MINOR_HFPD_ALARM_STOP");
        break;
    case MINOR_MIXED_TARGET_ALARM_START:
        szTemp.Format("MINOR_MIXED_TARGET_ALARM_START");
        break;
    case MINOR_MIXED_TARGET_ALARM_STOP:
        szTemp.Format("MINOR_MIXED_TARGET_ALARM_STOP");
        break;
    case MINOR_VCA_GET_UP_ALARM_BEGIN:
        szTemp.Format("MINOR_VCA_GET_UP_ALARM_BEGIN");
        break;
    case MINOR_VCA_GET_UP_ALARM_END:
        szTemp.Format("MINOR_VCA_GET_UP_ALARM_END");
        break;
    case MINOR_VCA_ADV_REACH_HEIGHT_ALARM_BEGIN:
        szTemp.Format("MINOR_VCA_ADV_REACH_HEIGHT_ALARM_BEGIN");
        break;
    case MINOR_VCA_ADV_REACH_HEIGHT_ALARM_END:
        szTemp.Format("MINOR_VCA_ADV_REACH_HEIGHT_ALARM_END");
        break;
    case MINOR_VCA_TOILET_TARRY_ALARM_BEGIN:
        szTemp.Format("MINOR_VCA_TOILET_TARRY_ALARM_BEGIN");
        break;
    case MINOR_VCA_TOILET_TARRY_ALARM_END:
        szTemp.Format("MINOR_VCA_TOILET_TARRY_ALARM_END");
        break;
    case MINOR_HUMAN_RECOGNITION_ALARM_BEGIN:
        szTemp.Format("MINOR_HUMAN_RECOGNITION_ALARM_BEGIN");
        break;
    case MINOR_HUMAN_RECOGNITION_ALARM_END:
        szTemp.Format("MINOR_HUMAN_RECOGNITION_ALARM_END");
        break;
    case MINOR_FACE_THERMOMETRY_ALARM:
        szTemp.Format("MINOR_FACE_THERMOMETRY_ALARM");
        break;
    case MINOR_STUDENTS_STOODUP_ALARM_BEGIN:
        szTemp.Format("MINOR_STUDENTS_STOODUP_ALARM_BEGIN ");
        break;
    case MINOR_STUDENTS_STOODUP_ALARM_END:
        szTemp.Format("MINOR_STUDENTS_STOODUP_ALARM_END");
        break;
    case MINOR_FRAMES_PEOPLE_COUNTING_ALARM:
        szTemp.Format("MINOR_FRAMES_PEOPLE_COUNTING_ALARM ");
        break;
    case  MINOR_CHANNEL_CONTROLLER_DESMANTLE_ALARM:
        szTemp.Format(" MINOR_CHANNEL_CONTROLLER_DESMANTLE_ALARM");
        break;
    case  MINOR_CHANNEL_CONTROLLER_DESMANTLE_RESUME:
        szTemp.Format(" MINOR_CHANNEL_CONTROLLER_DESMANTLE_RESUME");
        break;
    case  MINOR_CHANNEL_CONTROLLER_FIRE_IMPORT_ALARM:
        szTemp.Format(" MINOR_CHANNEL_CONTROLLER_FIRE_IMPORT_ALARM");
        break;
    case  MINOR_CHANNEL_CONTROLLER_FIRE_IMPORT_RESUME:
        szTemp.Format(" MINOR_CHANNEL_CONTROLLER_FIRE_IMPORT_RESUME");
        break;
    case MINOR_FACE_SNAP_ALARM_BEGIN:
        szTemp.Format("MINOR_FACE_SNAP_ALARM_BEGIN ");
        break;
    case MINOR_FACE_SNAP_ALARM_END:
        szTemp.Format("MINOR_FACE_SNAP_ALARM_END");
        break;
    case MINOR_HEART_RATE_ABNORMAL_BEGIN:
        szTemp.Format("MINOR_HEART_RATE_ABNORMAL_BEGIN");
        break;
    case MINOR_HEART_RATE_ABNORMAL_END:
        szTemp.Format("MINOR_HEART_RATE_ABNORMAL_END");
        break;
    case MINOR_BLOOD_OXYGEN_ABNORMAL_BEGIN:
        szTemp.Format("MINOR_BLOOD_OXYGEN_ABNORMAL_BEGIN");
        break;
    case MINOR_BLOOD_OXYGEN_ABNORMAL_END:
        szTemp.Format("MINOR_BLOOD_OXYGEN_ABNORMAL_END");
        break;
    case MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN:
        szTemp.Format("MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN");
        break;
    case MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_END:
        szTemp.Format("MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_END");
        break;
    case MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN:
        szTemp.Format("MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN");
        break;
    case MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_END:
        szTemp.Format("MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_END");
        break;
    case MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_BEGIN:
        szTemp.Format("MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_BEGIN ");
        break;
    case MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_END:
        szTemp.Format("MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_END");
        break;
    case MINOR_PERIMETER_CAPTURE_ALARM_BEGIN:
        szTemp.Format("MINOR_PERIMETER_CAPTURE_ALARM_BEGIN ");
        break;
    case MINOR_PERIMETER_CAPTURE_ALARM_END:
        szTemp.Format("MINOR_PERIMETER_CAPTURE_ALARM_END");
        break;
    case MINOR_PERSON_QUEUE_TIME_ALARM_BEGIN:
        szTemp.Format("MINOR_PERSON_QUEUE_TIME_ALARM_BEGIN");
        break;
    case MINOR_PERSON_QUEUE_TIME_ALARM_END:
        szTemp.Format("MINOR_PERSON_QUEUE_TIME_ALARM_END");
        break;
    case MINOR_PERSON_QUEUE_COUNTING_ALARM_BEGIN:
        szTemp.Format("MINOR_PERSON_QUEUE_COUNTING_ALARM_BEGIN");
        break;
    case MINOR_PERSON_QUEUE_COUNTING_ALARM_END:
        szTemp.Format("MINOR_PERSON_QUEUE_COUNTING_ALARM_END");
        break;

    case MINOR_ACCESS_CONTROLLER_EVENT:
        szTemp.Format("MINOR_ACCESS_CONTROLLER_EVENT");
        break;
    case MINOR_VIDEO_INTERCOM_EVENT:
        szTemp.Format("MINOR_VIDEO_INTERCOM_EVENT");
        break;
    case MINOR_GJD_EVENT:
        szTemp.Format("MINOR_GJD_EVENT");
        break;
    case MINOR_LUMINITE_EVENT:
        szTemp.Format("MINOR_LUMINITE_EVENT");
        break;
    case MINOR_OPTEX_EVENT:
        szTemp.Format("MINOR_OPTEX_EVENT");
        break;
    case MINOR_CAMERA_DETECTOR_EVENT:
        szTemp.Format("MINOR_CAMERA_DETECTOR_EVENT");
        break;

    case MINOR_REMOTE_CREATE_STORAGE_POOL:
        szTemp.Format("MINOR_REMOTE_CREATE_STORAGE_POOL");
        break;
    case MINOR_REMOTE_DEL_STORAGE_POOL:
        szTemp.Format("MINOR_REMOTE_DEL_STORAGE_POOL");
        break;
    case MINOR_REMOTE_CLOUD_ENABLE:
        szTemp.Format("MINOR_REMOTE_CLOUD_ENABLE");
        break;
    case MINOR_REMOTE_CLOUD_DISABLE:
        szTemp.Format("MINOR_REMOTE_CLOUD_DISABLE");
        break;
    case MINOR_REMOTE_CLOUD_MODIFY_PARAM:
        szTemp.Format("MINOR_REMOTE_CLOUD_MODIFY_PARAM");
        break;
    case MINOR_REMOTE_CLOUD_MODIFY_VOLUME:
        szTemp.Format("MINOR_REMOTE_CLOUD_MODIFY_VOLUME");
        break;

    case MINOR_UNREGISTERED_STREET_VENDOR_ALARM:
        szTemp.Format("MINOR_UNREGISTERED_STREET_VENDOR_ALARM");
        break;
    case MINOR_VCA_LEAVE_POSITION_START:
        szTemp.Format("MINOR_VCA_LEAVE_POSITION_START ");
        break;
    case MINOR_VCA_LEAVE_POSITION_STOP:
        szTemp.Format("MINOR_VCA_LEAVE_POSITION_STOP");
        break;
    case MINOR_VCA_STOOODUP_START:
        szTemp.Format("MINOR_VCA_STOOODUP_START ");
        break;
    case MINOR_VCA_STOOODUP_STOP:
        szTemp.Format("MINOR_VCA_STOOODUP_STOP");
        break;
    case MINOR_VCA_PEOPLENUM_CHANGE_START:
        szTemp.Format("MINOR_VCA_PEOPLENUM_CHANGE_START ");
        break;
    case MINOR_VCA_PEOPLENUM_CHANGE_STOP:
        szTemp.Format("MINOR_VCA_PEOPLENUM_CHANGE_STOP");
        break;
    case MINOR_VCA_RUNNING_START:
        szTemp.Format("MINOR_VCA_RUNNING_START ");
        break;
    case MINOR_VCA_RUNNING_STOP:
        szTemp.Format("MINOR_VCA_RUNNING_STOP");
        break;
    case MINOR_VCA_VIOLENT_MOTION_START:
        szTemp.Format("MINOR_VCA_VIOLENT_MOTION_START ");
        break;
    case MINOR_VCA_VIOLENT_MOTION_STOP:
        szTemp.Format("MINOR_VCA_VIOLENT_MOTION_STOP");
        break;
    case MINOR_VCA_FAIL_DOWN_START:
        szTemp.Format("MINOR_VCA_FAIL_DOWN_START ");
        break;
    case MINOR_VCA_FAIL_DOWN_STOP:
        szTemp.Format("MINOR_VCA_FAIL_DOWN_STOP");
        break;
    case MINOR_VCA_RETENTION_START:
        szTemp.Format("MINOR_VCA_RETENTION_START");
        break;
    case MINOR_VCA_RETENTION_STOP:
        szTemp.Format("MINOR_VCA_RETENTION_STOP");
        break;

    default:
        szTemp.Format("0x%x", stLogInfo.dwMinorType);
        break;
    }
}

/*********************************************************
Function:	ExceptionMinorTypeMap
Desc:		主类型为异常的次类型映射
Input:	stLogInfo, log information; szTemp, log string;
Output:	none
Return:	none
**********************************************************/
void ExceptionMinorTypeMap(const  NET_DVR_LOG_V50 &stLogInfo, CString &szTemp)
{
    CString szParaType;
    switch(stLogInfo.dwMinorType)
    {
        //exception
	case MINOR_RAID_ERROR:
        szTemp.Format("RAID_ERROR");
        break;
    case MINOR_VI_LOST:
        szTemp.Format("VI_LOST");
        break;
    case MINOR_ILLEGAL_ACCESS:
        szTemp.Format("ILLEGAL_ACCESS");
        break;
    case MINOR_HD_FULL:
        szTemp.Format("HD_FULL[%d]", stLogInfo.dwDiskNumber);
        break;
    case MINOR_HD_ERROR:
        szTemp.Format("HD_ERROR[%d]", stLogInfo.dwDiskNumber);
        break;
    case MINOR_REC_ERROR:
        szTemp.Format("REC_ERROR");
        break;
    case MINOR_DCD_LOST:
        szTemp.Format("DCD_LOST");
        break;
    case MINOR_IPC_NO_LINK:
        szTemp.Format("IPC_NO_LINK");
        break;
    case MINOR_IP_CONFLICT:
        szTemp.Format("IP_CONFLICT");
        break;
    case MINOR_NET_BROKEN:
        szTemp.Format("NET_BROKEN");
        break;
    case MINOR_VI_EXCEPTION:
        szTemp.Format("VI_EXCEPTION");
        break;
    case MINOR_IPC_IP_CONFLICT:
        szTemp.Format("IPC_IP_CONFLICT");
        break;
    case MINOR_SENCE_EXCEPTION:
        szTemp.Format("SENCE_EXCEPTION");
        break;
	case MINOR_RESOLUTION_MISMATCH:
        szTemp.Format("RESOLUTION_MISMATCH");
        break;
	case MINOR_RECORD_OVERFLOW:
        szTemp.Format("RECORD_OVERFLOW");
        break;
	case MINOR_DSP_ABNORMAL:
        szTemp.Format("DSP_ABNORMAL");
        break;
    case MINOR_ANR_RECORD_FAIED:
        szTemp.Format("ANR_RECORD_FAIED");
        break;
    case MINOR_DIAL_EXCEPTION:
        szTemp.Format("DIAL_EXCEPTION");
        break;
	case MINOR_SPARE_WORK_DEVICE_EXCEPT:
        szTemp.Format("SPARE_WORK_DEVICE_EXCEPT");
        break;
	case MINOR_START_IPC_MAS_FAILED:
        szTemp.Format("START_IPC_MAS_FAILED");
        break;
	case MINOR_IPCM_CRASH:
        szTemp.Format("IPCM_ABNORMAL_RESTART");
        break;
    case MINOR_POE_POWER_EXCEPTION:
        szTemp.Format("POE_POWER_EXCEPTION");
        break;
    case MINOR_UPLOAD_DATA_CS_EXCEPTION:
        szTemp.Format("MINOR_UPLOAD_DATA_CS_EXCEPTION");
        break;
    case MINOR_RS485_DEVICE_ABNORMAL:
        szTemp.Format("MINOR_RS485_DEVICE_ABNORMAL");
        break;
    case MINOR_RS485_DEVICE_REVERT:
        szTemp.Format("MINOR_RS485_DEVICE_REVERT");
        break;
    case MINOR_SYNC_IPC_PASSWD:
        szTemp.Format("MINOR_SYNC_IPC_PASSWD");
        break;
    case MINOR_EZVIZ_OFFLINE:
        szTemp.Format("MINOR_EZVIZ_OFFLINE");
        break;
    case MINOR_ACCESSORIES_PLATE:
        szTemp.Format("MINOR_ACCESSORIES_PLATE");
        break;
    case MINOR_KMS_EXPAMSION_DISK_LOST:
        szTemp.Format("MINOR_KMS_EXPAMSION_DISK_LOST");
        break;
    case MINOR_ABNORMAL_PORT:
        szTemp.Format("MINOR_ABNORMAL_PORT");
        break;
    case MINOR_CAMERA_ANGLE_ANOMALY:
        szTemp.Format("MINOR_CAMERA_ANGLE_ANOMALY");
        break;
    case MINOR_DATA_DISK_ERROE:
        szTemp.Format("MINOR_DATA_DISK_ERROE");
        break;
    case MINOR_INTELLIGENT_SYSTEM_RUNNING_ERROR:
        szTemp.Format("MINOR_INTELLIGENT_SYSTEM_RUNNING_ERROR");
        break;
    case MINOR_FACESNAP_RESOLUTION_OVERFLOW:
        szTemp.Format("MINOR_FACESNAP_RESOLUTION_OVERFLOW");
        break;
    case MINOR_SMD_RESOLUTION_OVERFLOW:
        szTemp.Format("MINOR_SMD_RESOLUTION_OVERFLOW");
        break;
    case MINOR_AUDIO_LOSS_EXCEPTION:
        szTemp.Format("MINOR_AUDIO_LOSS_EXCEPTION");
        break;
    case MINOR_SAFETY_HELMET_EXCEPTION:
        szTemp.Format("MINOR_SAFETY_HELMET_EXCEPTION");
        break;
    case MINOR_VCA_PIC_LENGTH_OVERFLOW:
        szTemp.Format("MINOR_VCA_PIC_LENGTH_OVERFLOW");
        break;
    case MINOR_FACE_MODEL_EXCEPTION:
        szTemp.Format("MINOR_FACE_MODEL_EXCEPTION");
        break;
    case MINOR_CLUSTER_DEVICE_OFFLINE:
        szTemp.Format("MINOR_CLUSTER_DEVICE_OFFLINE");
        break;
    case MINOR_CLUSTER_CONFIG_FAILED:
        szTemp.Format("MINOR_CLUSTER_CONFIG_FAILED");
        break;
    case MINOR_CLUSTER_DISASTER_TOLERANCE_EXCEPT:
        szTemp.Format("MINOR_CLUSTER_DISASTER_TOLERANCE_EXCEPT");
        break;
    case MINOR_CLUSTER_STORFULL_EXCEPTION:
        szTemp.Format("MINOR_CLUSTER_STORFULL_EXCEPTION");
        break;
    case MINOR_CLUSTER_VERSION_EXCEPTION:
        szTemp.Format("MINOR_CLUSTER_VERSION_EXCEPTION");
        break;
    case MINOR_CLUSTER_OFFLINENODE_EXCEPTION:
        szTemp.Format("MINOR_CLUSTER_OFFLINENODE_EXCEPTION");
        break;
    case MINOR_CLUSTER_RECORDCYCLE_EXCEPTION:
        szTemp.Format("MINOR_CLUSTER_RECORDCYCLE_EXCEPTION");
        break;
    case MINOR_CLUSTER_IPCTRANSFER_EXCEPTION:
        szTemp.Format("MINOR_CLUSTER_IPCTRANSFER_EXCEPTION");
        break;
    case MINOR_CLUSTER_IPCONFLICT_EXCEPTION:
        szTemp.Format("MINOR_CLUSTER_IPCONFLICT_EXCEPTION");
        break;
    case MINOR_GET_SUB_STREAM_FAILURE:
        szTemp.Format("MINOR_GET_SUB_STREAM_FAILURE");
        break;
    case MINOR_HDD_SHM_DETECT_EXCEPTION:
        szTemp.Format("MINOR_HDD_SHM_DETECT_EXCEPTION");
        break;
    case MINOR_DEV_POWER_ON:
        szTemp.Format("MINOR_DEV_POWER_ON");
        break;
    case MINOR_DEV_POWER_OFF:
        szTemp.Format("MINOR_DEV_POWER_OFF");
        break;
    case MINOR_WATCH_DOG_RESET:
        szTemp.Format("MINOR_WATCH_DOG_RESET");
        break;
    case  MINOR_LOW_BATTERY:
        szTemp.Format(" MINOR_LOW_BATTERY");
        break;
    case MINOR_BATTERY_RESUME:
        szTemp.Format("MINOR_BATTERY_RESUME");
        break;
    case MINOR_AC_OFF:
        szTemp.Format("MINOR_AC_OFF");
        break;
    case MINOR_AC_RESUME:
        szTemp.Format("MINOR_AC_RESUME");
        break;
    case MINOR_NET_RESUME:
        szTemp.Format("MINOR_NET_RESUME");
        break;
    case MINOR_FLASH_ABNORMAL:
        szTemp.Format("MINOR_FLASH_ABNORMAL");
        break;
    case MINOR_CARD_READER_OFFLINE:
        szTemp.Format("MINOR_CARD_READER_OFFLINE");
        break;
    case MINOR_CARD_READER_RESUME:
        szTemp.Format("MINOR_CAED_READER_RESUME");
        break;
	case MINOR_AI_LOST:
		szTemp.Format("AI_LOST");
        break;
    case MINOR_INDICATOR_LIGHT_OFF:
        szTemp.Format("MINOR_INDICATOR_LIGHT_OFF");
        break;
    case MINOR_INDICATOR_LIGHT_RESUME:
        szTemp.Format("MINOR_INDICATOR_LIGHT_RESUME");
        break;
    case MINOR_CHANNEL_CONTROLLER_OFF:
        szTemp.Format("MINOR_CHANNEL_CONTROLLER_OFF");
        break;
    case MINOR_CHANNEL_CONTROLLER_RESUME:
        szTemp.Format("MINOR_CHANNEL_CONTROLLER_RESUME");
        break;
    case MINOR_SECURITY_MODULE_OFF:
        szTemp.Format("MINOR_SECURITY_MODULE_OFF");
        break;
    case MINOR_SECURITY_MODULE_RESUME:
        szTemp.Format("MINOR_SECURITY_MODULE_RESUME");
        break;
    case MINOR_LOCAL_CONTROL_NET_BROKEN:
        szTemp.Format("MINOR_LOCAL_CONTROL_NET_BROKEN");
        break;
    case MINOR_LOCAL_CONTROL_NET_RSUME:
        szTemp.Format("MINOR_LOCAL_CONTROL_NET_RSUME");
        break;
    case MINOR_MASTER_RS485_LOOPNODE_BROKEN:
        szTemp.Format("MINOR_MASTER_RS485_LOOPNODE_BROKEN");
        break;
    case MINOR_MASTER_RS485_LOOPNODE_RESUME:
        szTemp.Format("MINOR_MASTER_RS485_LOOPNODE_RESUME");
        break;
    case MINOR_LOCAL_CONTROL_OFFLINE:
        szTemp.Format("MINOR_LOCAL_CONTROL_OFFLINE");
        break;
    case MINOR_LOCAL_CONTROL_RESUME:
        szTemp.Format("MINOR_LOCAL_CONTROL_RESUME");
        break;
    case MINOR_LOCAL_DOWNSIDE_RS485_LOOPNODE_BROKEN:
        szTemp.Format("MINOR_LOCAL_DOWNSIDE_RS485_LOOPNODE_BROKEN");
        break;
    case MINOR_LOCAL_DOWNSIDE_RS485_LOOPNODE_RESUME:
        szTemp.Format("MINOR_LOCAL_DOWNSIDE_RS485_LOOPNODE_RESUME");
        break;
    case MINOR_DISTRACT_CONTROLLER_ONLINE:
        szTemp.Format("MINOR_DISTRACT_CONTROLLER_ONLINE");
        break;
    case MINOR_DISTRACT_CONTROLLER_OFFLINE:
        szTemp.Format("MINOR_DISTRACT_CONTROLLER_OFFLINE");
        break;
    case MINOR_SDCARD_ABNORMAL:
        szTemp.Format("MINOR_SDCARD_ABNORMAL");
        break;
    case MINOR_SDCARD_DAMAGE:
        szTemp.Format("MINOR_SDCARD_DAMAGE");
        break;
	case MINOR_POC_ABNORMAL:
		szTemp.Format("MINOR_POC_ABNORMAL");
		break;
    case MINOR_BATTERY_ELECTRIC_LOW:
        szTemp.Format("MINOR_BATTERY_ELECTRIC_LOW");
        break;
    case MINOR_BATTERY_ELECTRIC_RESUME:
        szTemp.Format("MINOR_BATTERY_ELECTRIC_RESUME");
        break;
    case MINOR_ID_CARD_READER_NOT_CONNECT:
        szTemp.Format("MINOR_ID_CARD_READER_NOT_CONNECT");
        break;
    case MINOR_ID_CARD_READER_RESUME:
        szTemp.Format("MINOR_ID_CARD_READER_RESUME");
        break;
    case MINOR_FINGER_PRINT_MODULE_NOT_CONNECT:
        szTemp.Format("MINOR_FINGER_PRINT_MODULE_NOT_CONNECT");
        break;
    case MINOR_FINGER_PRINT_MODULE_RESUME:
        szTemp.Format("MINOR_FINGER_PRINT_MODULE_RESUME");
        break;
    case MINOR_CAMERA_NOT_CONNECT:
        szTemp.Format("MINOR_CAMERA_NOT_CONNECT");
        break;
    case MINOR_CAMERA_RESUME:
        szTemp.Format("MINOR_CAMERA_RESUME");
        break;
    case MINOR_COM_NOT_CONNECT:
        szTemp.Format("MINOR_COM_NOT_CONNECT");
        break;
    case MINOR_COM_RESUME:
        szTemp.Format("MINOR_COM_RESUME");
        break;
    case MINOR_DEVICE_NOT_AUTHORIZE:
        szTemp.Format("MINOR_DEVICE_NOT_AUTHORIZE");
        break;
    case MINOR_PEOPLE_AND_ID_CARD_DEVICE_ONLINE:
        szTemp.Format("MINOR_PEOPLE_AND_ID_CARD_DEVICE_ONLINE");
        break;
    case MINOR_PEOPLE_AND_ID_CARD_DEVICE_OFFLINE:
        szTemp.Format("MINOR_PEOPLE_AND_ID_CARD_DEVICE_OFFLINE");
        break;
    case MINOR_LOCAL_LOGIN_LOCK:
        szTemp.Format("MINOR_LOCAL_LOGIN_LOCK");
        break;
    case MINOR_LOCAL_LOGIN_UNLOCK:
        szTemp.Format("MINOR_LOCAL_LOGIN_UNLOCK");
        break;
    case MINOR_SUBMARINEBACK_COMM_BREAK:
        szTemp.Format("MINOR_SUBMARINEBACK_COMM_BREAK");
        break;
    case MINOR_SUBMARINEBACK_COMM_RESUME:
        szTemp.Format("MINOR_SUBMARINEBACK_COMM_RESUME");
        break;
    case MINOR_MOTOR_SENSOR_EXCEPTION:
        szTemp.Format("MINOR_MOTOR_SENSOR_EXCEPTION");
        break;
    case MINOR_CAN_BUS_EXCEPTION:
        szTemp.Format("MINOR_CAN_BUS_EXCEPTION");
        break;
    case MINOR_CAN_BUS_RESUME:
        szTemp.Format("MINOR_CAN_BUS_RESUME");
        break;
    case MINOR_GATE_TEMPERATURE_OVERRUN:
        szTemp.Format("MINOR_GATE_TEMPERATURE_OVERRUN");
        break;
    case MINOR_IR_EMITTER_EXCEPTION:
        szTemp.Format("MINOR_IR_EMITTER_EXCEPTION");
        break;
    case MINOR_IR_EMITTER_RESUME:
        szTemp.Format("MINOR_IR_EMITTER_RESUME");
        break;
    case MINOR_LAMP_BOARD_COMM_EXCEPTION:
        szTemp.Format("MINOR_LAMP_BOARD_COMM_EXCEPTION");
        break;
    case MINOR_LAMP_BOARD_COMM_RESUME:
        szTemp.Format("MINOR_LAMP_BOARD_COMM_RESUME");
        break;
    case MINOR_IR_ADAPTOR_COMM_EXCEPTION:
        szTemp.Format("MINOR_IR_ADAPTOR_COMM_EXCEPTION");
        break;
    case MINOR_IR_ADAPTOR_COMM_RESUME:
        szTemp.Format("MINOR_IR_ADAPTOR_COMM_RESUME");
        break;
    case MINOR_EXCEPTION_CUSTOM1:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM1");
        break;
    case MINOR_EXCEPTION_CUSTOM2:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM2");
        break;
    case MINOR_EXCEPTION_CUSTOM3:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM3");
        break;
    case MINOR_EXCEPTION_CUSTOM4:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM4");
        break;
    case MINOR_EXCEPTION_CUSTOM5:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM5");
        break;
    case MINOR_EXCEPTION_CUSTOM6:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM6");
        break;
    case MINOR_EXCEPTION_CUSTOM7:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM7");
        break;
    case MINOR_EXCEPTION_CUSTOM8:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM8");
        break;
    case MINOR_EXCEPTION_CUSTOM9:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM9");
        break;
    case MINOR_EXCEPTION_CUSTOM10:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM10");
        break;
    case MINOR_EXCEPTION_CUSTOM11:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM11");
        break;
    case MINOR_EXCEPTION_CUSTOM12:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM12");
        break;
    case MINOR_EXCEPTION_CUSTOM13:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM13");
        break;
    case MINOR_EXCEPTION_CUSTOM14:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM14");
        break;
    case MINOR_EXCEPTION_CUSTOM15:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM15");
        break;
    case MINOR_EXCEPTION_CUSTOM16:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM16");
        break;
    case MINOR_EXCEPTION_CUSTOM17:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM17");
        break;
    case MINOR_EXCEPTION_CUSTOM18:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM18");
        break;
    case MINOR_EXCEPTION_CUSTOM19:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM19");
        break;
    case MINOR_EXCEPTION_CUSTOM20:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM20");
        break;
    case MINOR_EXCEPTION_CUSTOM21:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM21");
        break;
    case MINOR_EXCEPTION_CUSTOM22:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM22");
        break;
    case MINOR_EXCEPTION_CUSTOM23:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM23");
        break;
    case MINOR_EXCEPTION_CUSTOM24:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM24");
        break;
    case MINOR_EXCEPTION_CUSTOM25:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM25");
        break;
    case MINOR_EXCEPTION_CUSTOM26:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM26");
        break;
    case MINOR_EXCEPTION_CUSTOM27:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM27");
        break;
    case MINOR_EXCEPTION_CUSTOM28:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM28");
        break;
    case MINOR_EXCEPTION_CUSTOM29:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM29");
        break;
    case MINOR_EXCEPTION_CUSTOM30:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM30");
        break;
    case MINOR_EXCEPTION_CUSTOM31:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM31");
        break;
    case MINOR_EXCEPTION_CUSTOM32:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM32");
        break;
    case MINOR_EXCEPTION_CUSTOM33:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM33");
        break;
    case MINOR_EXCEPTION_CUSTOM34:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM34");
        break;
    case MINOR_EXCEPTION_CUSTOM35:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM35");
        break;
    case MINOR_EXCEPTION_CUSTOM36:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM36");
        break;
    case MINOR_EXCEPTION_CUSTOM37:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM37");
        break;
    case MINOR_EXCEPTION_CUSTOM38:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM38");
        break;
    case MINOR_EXCEPTION_CUSTOM39:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM39");
        break;
    case MINOR_EXCEPTION_CUSTOM40:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM40");
        break;
    case MINOR_EXCEPTION_CUSTOM41:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM41");
        break;
    case MINOR_EXCEPTION_CUSTOM42:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM42");
        break;
    case MINOR_EXCEPTION_CUSTOM43:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM43");
        break;
    case MINOR_EXCEPTION_CUSTOM44:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM44");
        break;
    case MINOR_EXCEPTION_CUSTOM45:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM45");
        break;
    case MINOR_EXCEPTION_CUSTOM46:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM46");
        break;
    case MINOR_EXCEPTION_CUSTOM47:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM47");
        break;
    case MINOR_EXCEPTION_CUSTOM48:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM48");
        break;
    case MINOR_EXCEPTION_CUSTOM49:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM49");
        break;
    case MINOR_EXCEPTION_CUSTOM50:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM50");
        break;
    case MINOR_EXCEPTION_CUSTOM51:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM51");
        break;
    case MINOR_EXCEPTION_CUSTOM52:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM52");
        break;
    case MINOR_EXCEPTION_CUSTOM53:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM53");
        break;
    case MINOR_EXCEPTION_CUSTOM54:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM54");
        break;
    case MINOR_EXCEPTION_CUSTOM55:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM55");
        break;
    case MINOR_EXCEPTION_CUSTOM56:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM56");
        break;
    case MINOR_EXCEPTION_CUSTOM57:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM57");
        break;
    case MINOR_EXCEPTION_CUSTOM58:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM58");
        break;
    case MINOR_EXCEPTION_CUSTOM59:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM59");
        break;
    case MINOR_EXCEPTION_CUSTOM60:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM60");
        break;
    case MINOR_EXCEPTION_CUSTOM61:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM61");
        break;
    case MINOR_EXCEPTION_CUSTOM62:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM62");
        break;
    case MINOR_EXCEPTION_CUSTOM63:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM63");
        break;
    case MINOR_EXCEPTION_CUSTOM64:
        szTemp.Format("MINOR_EXCEPTION_CUSTOM64");
        break;
    default:
        szTemp.Format("0x%x", stLogInfo.dwMinorType);
        break;
    }
}

/*********************************************************
Function:	OperationMinorTypeMap
Desc:		主类型为操作的次类型映射
Input:	stLogInfo, log information; szTemp, log string;
Output:	none
Return:	none
**********************************************************/
void OperationMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp)
{
    CString szParaType;
    switch(stLogInfo.dwMinorType)
    {
        //operation
    case MINOR_START_DVR:
        szTemp.Format("START_DVR");
        break;
    case MINOR_REMOTE_FACE_BASE_CREATE:
        szTemp.Format("MINOR_REMOTE_FACE_BASE_CREATE");
        break;
    case MINOR_REMOTE_FACE_BASE_MODIFY:
        szTemp.Format("MINOR_REMOTE_FACE_BASE_MODIFY");
        break;
    case MINOR_REMOTE_FACE_BASE_DELETE:
        szTemp.Format("MINOR_REMOTE_FACE_BASE_DELETE");
        break;
    case MINOR_REMOTE_FACE_DATA_APPEND:
        szTemp.Format("MINOR_REMOTE_FACE_DATA_APPEND");
        break;
    case MINOR_REMOTE_FACE_DATA_SEARCH:
        szTemp.Format("MINOR_REMOTE_FACE_DATA_SEARCH");
        break;
    case MINOR_REMOTE_FACE_DATA_ANALYSIS:
        szTemp.Format("MINOR_REMOTE_FACE_DATA_ANALYSIS");
        break;
    case MINOR_REMOTE_FACE_DATA_EDIT:
        szTemp.Format("MINOR_REMOTE_FACE_DATA_EDIT");
        break;
    case MINOR_REMOTE_FACE_DATA_DELET:
        szTemp.Format("MINOR_REMOTE_FACE_DATA_DELET");
        break;
    case MINOR_REMOTE_VCA_ANALYSIS_CFG:
        szTemp.Format("MINOR_REMOTE_VCA_ANALYSIS_CFG");
        break;
    case MINOR_LOCAL_FACE_BASE_IMPORT:
        szTemp.Format("MINOR_LOCAL_FACE_BASE_IMPORT");
        break;
    case MINOR_LOCAL_FACE_BASE_EXPORT:
        szTemp.Format("MINOR_LOCAL_FACE_BASE_EXPORT");
        break;
    case MINOR_LOCAL_FACE_BASE_CREATE:
        szTemp.Format("MINOR_LOCAL_FACE_BASE_CREATE");
        break;
    case MINOR_LOCAL_FACE_BASE_MODIFY:
        szTemp.Format("MINOR_LOCAL_FACE_BASE_MODIFY");
        break;
    case MINOR_LOCAL_FACE_BASE_DELETE:
        szTemp.Format("MINOR_LOCAL_FACE_BASE_DELETE");
        break;
    case MINOR_LOCAL_FACE_DATA_APPEND:
        szTemp.Format("MINOR_LOCAL_FACE_DATA_APPEND");
        break;
    case MINOR_LOCAL_FACE_DATA_SEARCH:
        szTemp.Format("MINOR_LOCAL_FACE_DATA_SEARCH");
        break;
    case MINOR_LOCAL_FACE_DATA_ANALYSIS:
        szTemp.Format("MINOR_LOCAL_FACE_DATA_ANALYSIS");
        break;
    case MINOR_LOCAL_FACE_DATA_EDIT:
        szTemp.Format("MINOR_LOCAL_FACE_DATA_EDIT");
        break;
    case MINOR_LOCAL_FACE_DATA_DELETE:
        szTemp.Format("MINOR_LOCAL_FACE_DATA_DELETE");
        break;
    case MINOR_LOCAL_VCA_ANALYSIS_CFG:
        szTemp.Format("MINOR_LOCAL_VCA_ANALYSIS_CFG");
        break;
    case MINOR_REMOTE_HFPD_CFG:
        szTemp.Format("MINOR_REMOTE_HFPD_CFG");
        break;
    case MINOR_REMOTE_IOTCFGFILE_INPUT:
        szTemp.Format("MINOR_REMOTE_IOTCFGFILE_INPUT");
        break;
    case MINOR_REMOTE_IOTCFGFILE_OUTPUT:
        szTemp.Format("MINOR_REMOTE_IOTCFGFILE_OUTPUT");
        break;
    case MINOR_LOCAL_IOT_ADD:
        szTemp.Format("MINOR_LOCAL_IOT_ADD");
        break;
    case MINOR_REMOTE_IOT_ADD:
        szTemp.Format("MINOR_REMOTE_IOT_ADD");
        break;
    case MINOR_LOCAL_IOT_DEL:
        szTemp.Format("MINOR_LOCAL_IOT_DEL");
        break;
    case MINOR_REMOTE_IOT_DEL:
        szTemp.Format("MINOR_REMOTE_IOT_DEL");
        break;
    case MINOR_LOCAL_IOT_SET:
        szTemp.Format("MINOR_LOCAL_IOT_SET");
        break;
    case MINOR_REMOTE_IOT_SET:
        szTemp.Format("MINOR_REMOTE_IOT_SET");
        break;
    case MINOR_LOCAL_IOTCFGFILE_INPUT:
        szTemp.Format("MINOR_LOCAL_IOTCFGFILE_INPUT");
        break;
    case MINOR_LOCAL_IOTCFGFILE_OUTPUT:
        szTemp.Format("MINOR_LOCAL_IOTCFGFILE_OUTPUT");
        break;
    case MINOR_REMOTE_FACE_CONTRAST_TASK:
        szTemp.Format("MINOR_REMOTE_FACE_CONTRAST_TASK");
        break;
    case MINOR_STOP_DVR:
        szTemp.Format("STOP_DVR");
        break;
    case MINOR_STOP_ABNORMAL:
        szTemp.Format("STOP_ABNORMAL");
        break;
    case MINOR_REBOOT_DVR:
        szTemp.Format("REBOOT_DVR");
        break;
    case MINOR_LOCAL_LOGIN:
        szTemp.Format("LOCAL_LOGIN");
        break;
    case MINOR_LOCAL_LOGOUT:
        szTemp.Format("%s", "LOCAL_LOGOUT");
        break;
    case MINOR_LOCAL_CFG_PARM:
        ParaTypeMap(stLogInfo, szParaType);
        szTemp.Format("%s-%s", "LOCAL_CFG_PARM", szParaType.GetBuffer(0));
        break;
    case MINOR_LOCAL_PLAYBYFILE:
        szTemp.Format("%s","LOCAL_PLAYBYFILE");
        break;
    case MINOR_LOCAL_PLAYBYTIME:
        szTemp.Format("%s", "LOCAL_PLAYBYTIME");
        break;
    case MINOR_LOCAL_START_REC:
        szTemp.Format("%s", "LOCAL_START_REC");
        break;
    case MINOR_LOCAL_STOP_REC:
        szTemp.Format("%s", "LOCAL_STOP_REC");
        break;
    case MINOR_LOCAL_PTZCTRL:
        szTemp.Format("%s", "LOCAL_PTZCTRL");
        break;
    case MINOR_LOCAL_PREVIEW:
        szTemp.Format("%s", "LOCAL_PREVIEW");
        break;
    case MINOR_LOCAL_MODIFY_TIME:
        szTemp.Format("%s", "LOCAL_MODIFY_TIME");
        break;
    case MINOR_LOCAL_UPGRADE:
        szTemp.Format("%s", "LOCAL_UPGRADE");
        break;
    case MINOR_LOCAL_COPYFILE:
        szTemp.Format("%s", "LOCAL_COPYFILE");
        break;
        
    case MINOR_LOCAL_LOCKFILE:
        szTemp.Format("%s", "LOCAL_LOCKFILE");
        break;
    case MINOR_LOCAL_UNLOCKFILE:
        szTemp.Format("%s", "LOCAL_UNLOCKFILE");
        break;
    case MINOR_LOCAL_FORMAT_HDD:
        szTemp.Format("%s", "LOCAL_FORMAT_HDD");
        break;
        
    case MINOR_REMOTE_LOGIN:
        szTemp.Format("%s", "REMOTE_LOGIN");
        break;
    case MINOR_REMOTE_LOGOUT:
        szTemp.Format("%s", "REMOTE_LOGOUT");
        break;
    case MINOR_REMOTE_START_REC:
        szTemp.Format("%s", "REMOTE_START_REC");
        break;
    case MINOR_REMOTE_STOP_REC:
        szTemp.Format("%s","REMOTE_STOP_REC");
        break;
    case MINOR_START_TRANS_CHAN:
        szTemp.Format("%s", "START_TRANS_CHAN");
        break;
    case MINOR_STOP_TRANS_CHAN:
        szTemp.Format("%s","STOP_TRANS_CHAN");
        break;
    case MINOR_REMOTE_GET_PARM:
        ParaTypeMap(stLogInfo, szParaType);
        szTemp.Format("%s-%s", "REMOTE_GET_PARM", szParaType.GetBuffer(0));
        break;
    case MINOR_REMOTE_CFG_PARM:
        ParaTypeMap(stLogInfo, szParaType);
        szTemp.Format("%s-%s", "REMOTE_CFG_PARM", szParaType.GetBuffer(0));
        break;
    case MINOR_REMOTE_GET_STATUS:
        szTemp.Format("%s", "REMOTE_GET_STATUS");
        break;
    case MINOR_REMOTE_ARM:
        szTemp.Format("%s", "REMOTE_ARM");
        break;
    case MINOR_REMOTE_DISARM:
        szTemp.Format("%s", "REMOTE_DISARM");
        break;
    case MINOR_REMOTE_REBOOT:
        szTemp.Format("%s", "REMOTE_REBOOT");
        break;
    case MINOR_START_VT:
        szTemp.Format("%s", "START_VT");
        break;
    case MINOR_STOP_VT:
        szTemp.Format("%s", "STOP_VT");
        break;
    case MINOR_REMOTE_UPGRADE:
        szTemp.Format("%s", "REMOTE_UPGRADE");
        break;
    case MINOR_REMOTE_PLAYBYFILE:
        szTemp.Format("%s", "REMOTE_PLAYBYFILE");
        break;
    case MINOR_REMOTE_PLAYBYTIME:
        szTemp.Format("%s", "REMOTE_PLAYBYTIME");
        break;
    case MINOR_REMOTE_PTZCTRL:
        szTemp.Format("%s", "REMOTE_PTZCTRL");
        break;
    case MINOR_REMOTE_STOP:
        szTemp.Format("%s", "REMOTE_STOP");
        break;
        
    case MINOR_REMOTE_LOCKFILE:
        szTemp.Format("%s", "REMOTE_LOCKFILE");
        break;
    case MINOR_REMOTE_CFGFILE_OUTPUT:
        szTemp.Format("%s", "REMOTE_CFGFILE_OUTPUT");
        break;
       
    case MINOR_REMOTE_CFGFILE_INTPUT:
        szTemp.Format("%s", "REMOTE_CFGFILE_INTPUT");
        break;
    case MINOR_REMOTE_FORMAT_HDD:
        szTemp.Format("%s", "REMOTE_FORMAT_HDD");
        break;
    case MINOR_REMOTE_IPC_ADD:
        szTemp.Format("%s", "REMOTE_IPC_ADD");
        break;
    case MINOR_REMOTE_IPC_DEL:
        szTemp.Format("%s", "REMOTE_IPC_DEL");
        break;

    case MINOR_REMOTE_IPC_SET:
        szTemp.Format("%s", "REMOTE_IPC_SET");
        break;
    case  MINOR_REBOOT_VCA_LIB:
        szTemp.Format("%s", "REBOOT_VCA_LIB");
        break;
    case MINOR_REMOTE_ADD_NAS:
        szTemp.Format("%s", "REMOTE_ADD_NAS");
        break;		
    case MINOR_REMOTE_DEL_NAS:
        szTemp.Format("%s", "REMOTE_DEL_NAS");
        break;
    case MINOR_REMOTE_SET_NAS:
        szTemp.Format("%s", "REMOTE_SET_NAS");
        break;
    case MINOR_LOCAL_START_REC_CDRW:
        szTemp.Format("%s", "LOCAL_START_REC_CDRW");
        break;
    case MINOR_LOCAL_STOP_REC_CDRW:
        szTemp.Format("%s", "LOCAL_STOP_REC_CDRW");
        break;
    case MINOR_REMOTE_START_REC_CDRW:
        szTemp.Format("%s", "REMOTE_START_REC_CDRW");
        break;
    case MINOR_REMOTE_STOP_REC_CDRW:
        szTemp.Format("%s", "REMOTE_STOP_REC_CDRW");
        break;
    case MINOR_LOCAL_INQUEST_RESUME:
        szTemp.Format("%s", "LOCAL_INQUEST_RESUME");
        break;
    case MINOR_REMOTE_INQUEST_RESUME:
        szTemp.Format("%s", "REMOTE_INQUEST_RESUME");
        break;
    case MINOR_LOCAL_ADD_FILE:
        szTemp.Format("%s", "LOCAL_ADD_FILE");
        break;
    case MINOR_LOCAL_DEL_FILE:
        szTemp.Format("%s", "LOCAL_DEL_FILE");
        break;
    case MINOR_REMOTE_INQUEST_ADD_FILE:
        szTemp.Format("%s", "REMOTE_INQUEST_ADD_FILE");
        break;
	case MINOR_LOCAL_OPERATE_LOCK :
		szTemp.Format("%s", "LOCAL_OPERATE_LOCK");
        break;
	case MINOR_LOCAL_OPERATE_UNLOCK:
		szTemp.Format("%s", "LOCAL_OPERATE_UNLOCK");
        break;
	case MINOR_REMOTE_DELETE_HDISK:
		szTemp.Format("%s", "REMOTE_DELETE_HDISK");
        break;
	case MINOR_REMOTE_LOAD_HDISK:
		szTemp.Format("%s", "REMOTE_LOAD_HDISK");
        break;
	case MINOR_REMOTE_UNLOAD_HDISK:
		szTemp.Format("%s", "REMOTE_UNLOAD_HDISK");
        break;
        //local
    case MINOR_LOCAL_CFGFILE_OUTPUT:
        szTemp.Format("%s", "LOCAL_CFGFILE_OUTPUT");
        break;
    case MINOR_LOCAL_CFGFILE_INPUT:
        szTemp.Format("%s", "LOCAL_CFGFILE_INPUT");
        break;
    case MINOR_LOCAL_DVR_ALARM:
        szTemp.Format("%s", "LOCAL_DVR_ALARM");
        break;
    case MINOR_REMOTE_DVR_ALARM:
        szTemp.Format("%s", "REMOTE_DVR_ALARM");
        break;
    case MINOR_IPC_ADD:
        szTemp.Format("%s", "IPC_ADD");
        break;
    case MINOR_IPC_DEL:
        szTemp.Format("%s", "IPC_DEL");
        break;
    case MINOR_IPC_SET:
        szTemp.Format("%s", "IPC_SET");
        break;
    case MINOR_LOCAL_START_BACKUP:
        szTemp.Format("%s", "LOCAL_START_BACKUP");
        break;
    case MINOR_LOCAL_STOP_BACKUP:
        szTemp.Format("%s", "LOCAL_STOP_BACKUP");
        break;
    case MINOR_LOCAL_COPYFILE_START_TIME:
        szTemp.Format("%s", "LOCAL_COPYFILE_START_TIME");
        break;
    case MINOR_LOCAL_COPYFILE_END_TIME:
        szTemp.Format("%s", "LOCAL_COPYFILE_START_TIME");
        break;
    case MINOR_LOCAL_ADD_NAS:
        szTemp.Format("%s", "LOCAL_ADD_NAS");
        break;
    case MINOR_LOCAL_DEL_NAS:
        szTemp.Format("%s", "LOCAL_DEL_NAS");
        break;
    case MINOR_LOCAL_SET_NAS:
        szTemp.Format("%s", "LOCAL_SET_NAS");
        break;
	//2010-04-13 
	case MINOR_FANABNORMAL:
        szTemp.Format("%s", "FANABNORMAL");
        break;
    case  MINOR_FANRESUME:
        szTemp.Format("%s", "FANRESUME");
        break;
    case MINOR_SUBSYSTEM_ABNORMALREBOOT:
        szTemp.Format("%s", "SUBSYSTEM_ABNORMALREBOOT");
        break;	 
    case MINOR_MATRIX_STARTBUZZER:
        szTemp.Format("%s", "MATRIX_STARTBUZZER");
        break;	 
    case MINOR_NET_ABNORMAL:
        szTemp.Format("%s", "NET_ABNORMAL");
        break;	 
	case MINOR_MEM_ABNORMAL:
        szTemp.Format("%s", "MEM_ABNORMAL");
        break;
    case MINOR_FILE_ABNORMAL:
        szTemp.Format("%s", "FILE_ABNORMAL");
        break;
    case MINOR_SUBSYSTEMREBOOT:
        szTemp.Format("%s", "SUBSYSTEMREBOOT");
        break;	 
    case MINOR_MATRIX_STARTTRANSFERVIDEO:
        szTemp.Format("%s", "MATRIX_STARTTRANSFERVIDEO");
        break;	 
    case MINOR_MATRIX_STOPTRANSFERVIDEO:
        szTemp.Format("%s", "MATRIX_STOPTRANSFERVIDEO");
        break;	 
	case MINOR_REMOTE_SET_ALLSUBSYSTEM:
        szTemp.Format("%s", "REMOTE_SET_ALLSUBSYSTEM");
        break;
    case MINOR_REMOTE_GET_ALLSUBSYSTEM:
        szTemp.Format("%s", "REMOTE_GET_ALLSUBSYSTEM");
        break;
    case MINOR_REMOTE_SET_PLANARRAY:
        szTemp.Format("%s", "REMOTE_SET_PLANARRAY");
        break;	 
    case MINOR_REMOTE_GET_PLANARRAY:
        szTemp.Format("%s", "REMOTE_GET_PLANARRAY");
        break;	 
    case MINOR_MATRIX_STARTTRANSFERAUDIO:
        szTemp.Format("%s", "MATRIX_STARTTRANSFERAUDIO");
        break;	 
	case MINOR_MATRIX_STOPRANSFERAUDIO:
        szTemp.Format("%s", "MATRIX_STOPRANSFERAUDIO");
        break;
    case MINOR_LOGON_CODESPITTER:
        szTemp.Format("%s", "LOGON_CODESPITTER");
        break;
    case MINOR_LOGOFF_CODESPITTER:
        szTemp.Format("%s", "LOGOFF_CODESPITTER");
        break;	 
    case MINOR_START_DYNAMIC_DECODE:
        szTemp.Format("%s", "START_DYNAMIC_DECODE");
        break;	 
    case MINOR_STOP_DYNAMIC_DECODE:
        szTemp.Format("%s", "STOP_DYNAMIC_DECODE");
        break;	 
	case MINOR_GET_CYC_CFG:
        szTemp.Format("%s", "GET_CYC_CFG");
        break;
    case MINOR_SET_CYC_CFG:
        szTemp.Format("%s", "SET_CYC_CFG");
        break;
    case MINOR_START_CYC_DECODE:
        szTemp.Format("%s", "START_CYC_DECODE");
        break;	 
    case MINOR_STOP_CYC_DECODE:
        szTemp.Format("%s", "STOP_CYC_DECODE");
        break;	 
    case MINOR_GET_DECCHAN_STATUS:
        szTemp.Format("%s", "GET_DECCHAN_STATUS");
        break;	 
	case MINOR_GET_DECCHAN_INFO:
        szTemp.Format("%s", "GET_DECCHAN_INFO");
        break;
    case MINOR_START_PASSIVE_DEC:
        szTemp.Format("%s", "START_PASSIVE_DEC");
        break;
    case MINOR_STOP_PASSIVE_DEC:
        szTemp.Format("%s", "STOP_PASSIVE_DEC");
        break;	 
    case MINOR_CTRL_PASSIVE_DEC:
        szTemp.Format("%s", "CTRL_PASSIVE_DEC");
        break;	 
    case MINOR_RECON_PASSIVE_DEC:
        szTemp.Format("%s", "RECON_PASSIVE_DEC");
        break;			
	case MINOR_GET_DEC_CHAN_SW:
        szTemp.Format("%s", "GET_DEC_CHAN_SW");
        break;
    case MINOR_SET_DEC_CHAN_SW:
        szTemp.Format("%s", "SET_DEC_CHAN_SW");
        break;	 
    case MINOR_CTRL_DEC_CHAN_SCALE:
        szTemp.Format("%s", "CTRL_DEC_CHAN_SCALE");
        break;	 
    case MINOR_SET_REMOTE_REPLAY:
        szTemp.Format("%s", "SET_REMOTE_REPLAY");
        break;	 
	case MINOR_GET_REMOTE_REPLAY:
        szTemp.Format("%s", "GET_REMOTE_REPLAY");
        break;
    case MINOR_CTRL_REMOTE_REPLAY:
        szTemp.Format("%s", "CTRL_REMOTE_REPLAY");
        break;
    case MINOR_SET_DISP_CFG:
        szTemp.Format("%s", "SET_DISP_CFG");
        break;	 
    case MINOR_GET_DISP_CFG:
        szTemp.Format("%s", "GET_DISP_CFG");
        break;	 
    case MINOR_SET_PLANTABLE:
        szTemp.Format("%s", "SET_PLANTABLE");
        break;	 
	case MINOR_GET_PLANTABLE:
        szTemp.Format("%s", "GET_PLANTABLE");
        break;
    case MINOR_START_PPPPOE:
        szTemp.Format("%s", "START_PPPPOE");
        break;	 
    case MINOR_STOP_PPPPOE:
        szTemp.Format("%s", "STOP_PPPPOE");
        break;	 
    case MINOR_UPLOAD_LOGO:
        szTemp.Format("%s", "UPLOAD_LOGO");
        break;	 
    case MINOR_LOCAL_CONF_REB_RAID:
        szTemp.Format("%s", "LOCAL_CONF_REB_RAID");
        break;
    case MINOR_LOCAL_CONF_SPARE:
        szTemp.Format("%s", "LOCAL_CONF_SPARE");
        break;
    case MINOR_LOCAL_ADD_RAID:
        szTemp.Format("%s", "LOCAL_ADD_RAID");
        break;
    case MINOR_LOCAL_DEL_RAID:
        szTemp.Format("%s", "LOCAL_DEL_RAID");
        break;
    case MINOR_LOCAL_MIG_RAID:
        szTemp.Format("%s", "LOCAL_MIG_RAID");
        break;
    case MINOR_LOCAL_REB_RAID:
        szTemp.Format("%s", "LOCAL_REB_RAID");
        break;
    case MINOR_LOCAL_QUICK_CONF_RAID:
        szTemp.Format("%s", "LOCAL_QUICK_CONF_RAID");
        break;
    case MINOR_LOCAL_ADD_VD:
        szTemp.Format("%s", "LOCAL_ADD_VD");
        break;
    case MINOR_LOCAL_DEL_VD:
        szTemp.Format("%s", "LOCAL_DEL_VD");
        break;
    case MINOR_LOCAL_RP_VD:
        szTemp.Format("%s", "LOCAL_RP_VD");
        break;
    case MINOR_LOCAL_FORMAT_EXPANDVD:
        szTemp.Format("%s", "LOCAL_FORMAT_EXPANDVD");
        break;
    case MINOR_LOCAL_RAID_UPGRADE:
        szTemp.Format("%s", "LOCAL_RAID_UPGRADE");
		break;
	case MINOR_LOCAL_STOP_RAID:
        szTemp.Format("%s", "LOCAL_STOP_RAID");
        break;
    case MINOR_REMOTE_CONF_REB_RAID:
        szTemp.Format("%s", "REMOTE_CONF_REB_RAID");
        break;
    case MINOR_REMOTE_CONF_SPARE:
        szTemp.Format("%s", "REMOTE_CONF_SPARE");
        break;
    case MINOR_REMOTE_ADD_RAID:
        szTemp.Format("%s", "REMOTE_ADD_RAID");
        break;
    case MINOR_REMOTE_DEL_RAID:
        szTemp.Format("%s", "REMOTE_DEL_RAID");
        break;
    case MINOR_REMOTE_MIG_RAID:
        szTemp.Format("%s", "REMOTE_MIG_RAID");
        break;
    case MINOR_REMOTE_REB_RAID:
        szTemp.Format("%s", "REMOTE_REB_RAID");
        break;
    case MINOR_REMOTE_QUICK_CONF_RAID:
        szTemp.Format("%s", "REMOTE_QUICK_CONF_RAID");
        break;
    case MINOR_REMOTE_ADD_VD:
        szTemp.Format("%s", "REMOTE_ADD_VD");
        break;
    case MINOR_REMOTE_DEL_VD:
        szTemp.Format("%s", "REMOTE_DEL_VD");
        break;
    case MINOR_REMOTE_RP_VD:
        szTemp.Format("%s", "REMOTE_RP_VD");
        break;
    case MINOR_REMOTE_FORMAT_EXPANDVD:
        szTemp.Format("%s", "REMOTE_FORMAT_EXPANDVD");
        break;
    case MINOR_REMOTE_RAID_UPGRADE:
        szTemp.Format("%s", "REMOTE_RAID_UPGRADE");
        break;
	case MINOR_REMOTE_STOP_RAID:
        szTemp.Format("%s", "REMOTE_STOP_RAID");
        break;
	case MINOR_LOCAL_START_PIC_REC:
        szTemp.Format("%s", "LOCAL_START_PIC_REC");
        break;
    case MINOR_LOCAL_STOP_PIC_REC:
        szTemp.Format("%s", "LOCAL_STOP_PIC_REC");
        break;
    case MINOR_LOCAL_SET_SNMP:
        szTemp.Format("%s", "LOCAL_SET_SNMP");
        break;
	case MINOR_LOCAL_TAG_OPT:
        szTemp.Format("%s", "LOCAL_TAG_OPT");
        break;
	case MINOR_REMOTE_START_PIC_REC:
        szTemp.Format("%s", "REMOTE_START_PIC_REC");
        break;
    case MINOR_REMOTE_STOP_PIC_REC:
        szTemp.Format("%s", "REMOTE_STOP_PIC_REC");
        break;
    case MINOR_REMOTE_SET_SNMP:
        szTemp.Format("%s", "REMOTE_SET_SNMP");
        break;
	case MINOR_REMOTE_TAG_OPT:
        szTemp.Format("%s", "REMOTE_TAG_OPT");
        break;
    case MINOR_REMOTE_INQUEST_DEL_FILE:
        szTemp.Format("%s", "REMOTE_INQUEST_DEL_FILE");
        break;
	case MINOR_LOCAL_VOUT_SWITCH:
        szTemp.Format("%s", "LOCAL_VOUT_SWITCH");
        break;
	case MINOR_STREAM_CABAC:
        szTemp.Format("%s", "STREAM_CABAC");
        break;
    case MINOR_LOCAL_SPARE_OPT:
        szTemp.Format("%s", "LOCAL_SPARE_OPT");
        break;
	case MINOR_REMOTE_SPARE_OPT:
        szTemp.Format("%s", "REMOTE_SPARE_OPT");
        break;
	case MINOR_LOCAL_IPCCFGFILE_OUTPUT:
        szTemp.Format("%s", "LOCAL_IPCCFGFILE_OUTPUT");
        break;
	case MINOR_LOCAL_IPCCFGFILE_INPUT:
        szTemp.Format("%s", "LOCAL_IPCCFGFILE_INPUT");
        break;
	case MINOR_LOCAL_IPC_UPGRADE:
        szTemp.Format("%s", "LOCAL_IPC_UPGRADE");
        break;
	case MINOR_REMOTE_IPCCFGFILE_OUTPUT:
        szTemp.Format("%s", "REMOTE_IPCCFGFILE_OUTPUT");
        break;
	case MINOR_REMOTE_IPCCFGFILE_INPUT:
        szTemp.Format("%s", "REMOTE_IPCCFGFILE_INPUT");
        break;
	case MINOR_REMOTE_IPC_UPGRADE:
        szTemp.Format("%s", "REMOTE_IPC_UPGRADE");
        break;
    case MINOR_LOCAL_UNLOAD_HDISK:
        szTemp.Format("%s", "LOCAL_UNLOAD_HDISK");
        break;
    case MINOR_LOCAL_AUDIO_MIX:
        szTemp.Format("%s", "LOCAL_AUDIO_MIX");
        break;
    case MINOR_REMOTE_AUDIO_MIX:
        szTemp.Format("%s", "REMOTE_AUDIO_MIX");
        break;
    case MINOR_LOCAL_TRIAL_PAUSE:
        szTemp.Format("%s", "LOCAL_TRIAL_PAUSE");
        break;
    case MINOR_LOCAL_TRIAL_RESUME:
        szTemp.Format("%s", "LOCAL_TRIAL_RESUME");
        break;
    case MINOR_REMOTE_TRIAL_PAUSE:
        szTemp.Format("%s", "REMOTE_TRIAL_PAUSE");
        break;
    case MINOR_REMOTE_TRIAL_RESUME:
        szTemp.Format("%s", "REMOTE_TRIAL_RESUME");
        break;
	case MINOR_REMOTE_MODIFY_VERIFICATION_CODE:
		szTemp.Format("%s", "MINOR_REMOTE_MODIFY_VERIFICATION_CODE");
		break;
    case MINOR_LOCAL_MAKECALL:
        szTemp.Format("%s", "MINOR_LOCAL_MAKECALL");
        break;
    case MINOR_LOCAL_REJECTCALL:
        szTemp.Format("%s", "MINOR_LOCAL_REJECTCALL");
        break;
    case MINOR_LOCAL_ANSWERCALL:
        szTemp.Format("%s", "MINOR_LOCAL_ANSWERCALL");
        break;
    case MINOR_LOCAL_HANGUPCALL:
        szTemp.Format("%s", "MINOR_LOCAL_HANGUPCALL");
        break;
    case MINOR_REMOTE_MAKECALL:
        szTemp.Format("%s", "MINOR_REMOTE_MAKECALL");
        break;
    case MINOR_REMOTE_REJECTCALL:
        szTemp.Format("%s", "MINOR_REMOTE_REJECTCALL");
        break;
    case MINOR_REMOTE_ANSWERCALL:
        szTemp.Format("%s", "MINOR_REMOTE_ANSWERCALL");
        break;
    case MINOR_REMOTE_HANGUPCALL:
        szTemp.Format("%s", "MINOR_REMOTE_HANGUPCALL");
        break;
	case MINOR_LOCAL_LOAD_HDISK:
        szTemp.Format("%s", "LOCAL_LOAD_HDISK");
        break;
	case MINOR_LOCAL_DELETE_HDISK:
        szTemp.Format("%s", "LOCAL_DELETE_HDISK");
        break;
	case MINOR_LOCAL_MAIN_AUXILIARY_PORT_SWITCH:
		szTemp.Format("%s", "LOCAL_MAIN_AUXILIARY_PORT_SWITCH");
        break;
	case MINOR_LOCAL_HARD_DISK_CHECK:
		szTemp.Format("%s", "LOCAL_HARD_DISK_CHECK");
        break;
	case MINOR_LOCAL_PIN:
		szTemp.Format("%s", "LOCAL_PIN");
		break;
	case MINOR_LOCAL_DIAL:
		szTemp.Format("%s", "LOCAL_DIAL");
        break;
    case MINOR_SMS_CONTROL:
        szTemp.Format("%s", "SMS_CONTROL");
        break;
    case MINOR_CALL_ONLINE:
        szTemp.Format("%s", "CALL_ONLINE");
        break;
    case MINOR_REMOTE_PIN:
        szTemp.Format("%s", "REMOTE_PIN");
        break;
    case MINOR_REMOTE_SMS_SEND:
        szTemp.Format("%s", "REMOTE_SMS_SEND");
        break;
    case MINOR_LOCAL_SMS_SEND:
        szTemp.Format("%s", "LOCAL_SMS_SEND");
        break;
    case MINOR_ALARM_SMS_SEND:
        szTemp.Format("%s", "ALARM_SMS_SEND");
        break;
    case MINOR_SMS_RECV:
        szTemp.Format("%s", "SMS_RECV");
        break;
    case MINOR_LOCAL_SMS_SEARCH: 
        szTemp.Format("%s", "LOCAL_SMS_SEARCH ");
        break;
    case MINOR_REMOTE_SMS_SEARCH:
        szTemp.Format("%s", "REMOTE_SMS_SEARCH");
        break;
    case MINOR_LOCAL_SMS_READ:
        szTemp.Format("%s", "LOCAL_SMS_READ");
        break;
    case MINOR_REMOTE_SMS_READ:
        szTemp.Format("%s", "REMOTE_SMS_READ");
        break;
    case MINOR_REMOTE_DIAL_CONNECT:
        szTemp.Format("%s", "REMOTE_DIAL_CONNECT");
        break;
    case MINOR_REMOTE_DIAL_DISCONN:
        szTemp.Format("%s", "REMOTE_DIAL_DISCONN");
        break;
    case MINOR_LOCAL_WHITELIST_SET:
        szTemp.Format("%s", "LOCAL_WHITELIST_SET");
        break;
    case MINOR_REMOTE_WHITELIST_SET:
        szTemp.Format("%s", "REMOTE_WHITELIST_SET");
        break;
    case MINOR_LOCAL_DIAL_PARA_SET:
        szTemp.Format("%s", "LOCAL_DIAL_PARA_SET");
        break;
    case MINOR_REMOTE_DIAL_PARA_SET:
        szTemp.Format("%s", "REMOTE_DIAL_PARA_SET");
        break;
    case MINOR_LOCAL_DIAL_SCHEDULE_SET:
        szTemp.Format("%s", "LOCAL_DIAL_SCHEDULE_SET");
        break;
    case MINOR_REMOTE_DIAL_SCHEDULE_SET:
        szTemp.Format("%s", "REMOTE_DIAL_SCHEDULE_SET");
        break;
    case MINOR_PLAT_OPER:
        szTemp.Format("%s", "PLAT_OPER");
        break;
    case MINOR_REMOTE_CFG_POE_WORK_MODE:
        szTemp.Format("%s", "MINOR_REMOTE_CFG_POE_WORK_MODE");
        break;
    case MINOR_LOCAL_CFG_POE_WORK_MODE:
        szTemp.Format("%s", "MINOR_LOCAL_CFG_POE_WORK_MODE");
        break;
    case MINOR_REMOTE_CFG_FACE_CONTRAST:
        szTemp.Format("%s", "MINOR_REMOTE_CFG_FACE_CONTRAST");
        break;
    case MINOR_LOCAL_CFG_FACE_CONTRAST:
        szTemp.Format("%s", "MINOR_LOCAL_CFG_FACE_CONTRAST");
        break;
    case MINOR_REMOTE_CFG_WHITELIST_FACE_CONTRAST:
        szTemp.Format("%s", "MINOR_REMOTE_CFG_WHITELIST_FACE_CONTRAST");
        break;
    case MINOR_LOCAL_CFG_WHITELIST_FACE_CONTRAST:
        szTemp.Format("%s", "MINOR_LOCAL_CFG_WHITELIST_FACE_CONTRAST");
        break;
    case MINOR_REMOTE_DEVICE_CONTROL:
        szTemp.Format("%s", "REMOTE_DEVICE_CONTROL");
        break;
    case MINOR_REMOTE_SET_GATE_PARM_CFG:
        szTemp.Format("%s", "REMOTE_SET_GATE_PARM_CFG");
        break;
    case MINOR_REMOTE_GET_GATE_PARM_CFG:
        szTemp.Format("%s", "REMOTE_GET_GATE_PARM_CFG");
        break;
    case MINOR_REMOTE_SET_DATAUPLOAD_PARM_CFG:
        szTemp.Format("%s", "REMOTE_SET_DATAUPLOAD_PARM_CFG");
        break;
    case MINOR_REMOTE_GET_DATAUPLOAD_PARM_CFG:
        szTemp.Format("%s", "REMOTE_GET_DATAUPLOAD_PARM_CFG");
        break;
    case MINOR_REMOTE_GET_BASE_INFO:
        szTemp.Format("%s", "REMOTE_GET_BASE_INFO");
        break;
    case MINOR_REMOTE_GET_OVERLAP_CFG:
        szTemp.Format("%s", "REMOTE_GET_OVERLAP_CFG");
        break;
    case MINOR_REMOTE_SET_OVERLAP_CFG:
        szTemp.Format("%s", "REMOTE_SET_OVERLAP_CFG");
        break;
    case MINOR_REMOTE_GET_ROAD_INFO:
        szTemp.Format("%s", "REMOTE_GET_ROAD_INFO");
        break;
    case MINOR_REMOTE_START_TRANSCHAN:
        szTemp.Format("%s", "REMOTE_START_TRANSCHAN");
        break;
    case MINOR_REMOTE_GET_ECTWORKSTATE:
        szTemp.Format("%s", "REMOTE_GET_ECTWORKSTATE");
        break;
    case MINOR_REMOTE_GET_ECTCHANINFO:
        szTemp.Format("%s", "REMOTE_GET_ECTCHANINFO");
        break;
        //2013-11-19
	case MINOR_REMOTE_ADD_EXTERNAL_DEVICE_INFO:
		szTemp.Format("%s", "REMOTE_ADD_EXTERNAL_DEVICE_INFO");
		break;
	case MINOR_REMOTE_MOD_EXTERNAL_DEVICE_INFO:
		szTemp.Format("%s", "REMOTE_MOD_EXTERNAL_DEVICE_INFO");
		break;
	case MINOR_REMOTE_GET_ENDETCFG:
		szTemp.Format("%s", "REMOTE_GET_ENDETCFG");
		break;
	case MINOR_REMOTE_SET_ENDETCFG:
		szTemp.Format("%s", "REMOTE_SET_ENDETCFG");
		break;
	case MINOR_REMOTE_ENDEV_ISSUEDDATA:
		szTemp.Format("%s", "REMOTE_ENDEV_ISSUEDDATA");
		break;
	case MINOR_REMOTE_DEL_ENDEV_ISSUEDDATA:
		szTemp.Format("%s", "REMOTE_DEL_ENDEV_ISSUEDDATA");
		break;

	case MINOR_LOCAL_ADD_CAR_INFO:
		szTemp.Format("%s", "LOCAL_ADD_CAR_INFO");
		break;
	case MINOR_LOCAL_MOD_CAR_INFO:
		szTemp.Format("%s", "LOCAL_MOD_CAR_INFO");
		break;
	case MINOR_LOCAL_DEL_CAR_INFO:
		szTemp.Format("%s", "LOCAL_DEL_CAR_INFO");
		break;
	case MINOR_LOCAL_FIND_CAR_INFO:
		szTemp.Format("%s", "LOCAL_FIND_CAR_INFO");
		break;
	case MINOR_LOCAL_ADD_MONITOR_INFO:
		szTemp.Format("%s", "LOCAL_ADD_MONITOR_INFO");
		break;
	case MINOR_LOCAL_MOD_MONITOR_INFO:
		szTemp.Format("%s", "LOCAL_MOD_MONITOR_INFO");
		break;
	case MINOR_LOCAL_DEL_MONITOR_INFO:
		szTemp.Format("%s", "LOCAL_DEL_MONITOR_INFO");
		break;
	case MINOR_LOCAL_FIND_MONITOR_INFO:
		szTemp.Format("%s", "LOCAL_FIND_MONITOR_INFO");
		break;

	case MINOR_LOCAL_FIND_NORMAL_PASS_INFO:
		szTemp.Format("%s", "LOCAL_FIND_NORMAL_PASS_INFO");
		break;
	case MINOR_LOCAL_FIND_ABNORMAL_PASS_INFO:
		szTemp.Format("%s", "LOCAL_FIND_ABNORMAL_PASS_INFO");
		break;
	case MINOR_LOCAL_FIND_PEDESTRIAN_PASS_INFO:
		szTemp.Format("%s", "LOCAL_FIND_PEDESTRIAN_PASS_INFO");
		break;
	case MINOR_LOCAL_PIC_PREVIEW:
		szTemp.Format("%s", "LOCAL_PIC_PREVIEW");
		break;
	case MINOR_LOCAL_SET_GATE_PARM_CFG:
		szTemp.Format("%s", "LOCAL_SET_GATE_PARM_CFG");
		break;

	case MINOR_LOCAL_GET_GATE_PARM_CFG:
		szTemp.Format("%s", "LOCAL_GET_GATE_PARM_CFG");
		break;
	case MINOR_LOCAL_SET_DATAUPLOAD_PARM_CFG:
		szTemp.Format("%s", "LOCAL_SET_DATAUPLOAD_PARM_CFG");
		break;
	case MINOR_LOCAL_GET_DATAUPLOAD_PARM_CFG:
		szTemp.Format("%s", "LOCAL_GET_DATAUPLOAD_PARM_CFG");
		break;
		//2013-11-19
	case MINOR_LOCAL_DEVICE_CONTROL:
		szTemp.Format("%s", "LOCAL_DEVICE_CONTROL");
		break;
	case MINOR_LOCAL_ADD_EXTERNAL_DEVICE_INFO:
		szTemp.Format("%s", "LOCAL_ADD_EXTERNAL_DEVICE_INFO");
		break;
	case MINOR_LOCAL_MOD_EXTERNAL_DEVICE_INFO:
		szTemp.Format("%s", "LOCAL_MOD_EXTERNAL_DEVICE_INFO");
		break;
	case MINOR_LOCAL_DEL_EXTERNAL_DEVICE_INFO:
		szTemp.Format("%s", "LOCAL_DEL_EXTERNAL_DEVICE_INFO");
		break;
	case MINOR_LOCAL_FIND_EXTERNAL_DEVICE_INFO:
		szTemp.Format("%s", "LOCAL_FIND_EXTERNAL_DEVICE_INFO");
		break;
	case MINOR_LOCAL_ADD_CHARGE_RULE:
		szTemp.Format("%s", "LOCAL_ADD_CHARGE_RULE");
		break;	
	case MINOR_LOCAL_MOD_CHARGE_RULE:
		szTemp.Format("%s", "LOCAL_MOD_CHARGE_RULE");
		break;
	case MINOR_LOCAL_DEL_CHARGE_RULE:
		szTemp.Format("%s", "LOCAL_DEL_CHARGE_RULE");
		break;	
	case MINOR_LOCAL_FIND_CHARGE_RULE:
		szTemp.Format("%s", "LOCAL_FIND_CHARGE_RULE");
		break;
	case MINOR_LOCAL_COUNT_NORMAL_CURRENTINFO:
		szTemp.Format("%s", "LOCAL_COUNT_NORMAL_CURRENTINFO");
		break;	
	case MINOR_LOCAL_EXPORT_NORMAL_CURRENTINFO_REPORT:
		szTemp.Format("%s", "LOCAL_EXPORT_NORMAL_CURRENTINFO_REPORT");
		break;
	case MINOR_LOCAL_COUNT_ABNORMAL_CURRENTINFO:
		szTemp.Format("%s", "LOCAL_COUNT_ABNORMAL_CURRENTINFO");
		break;	
	case MINOR_LOCAL_EXPORT_ABNORMAL_CURRENTINFO_REPORT:
		szTemp.Format("%s", "LOCAL_EXPORT_ABNORMAL_CURRENTINFO_REPORT");
		break;
	case MINOR_LOCAL_COUNT_PEDESTRIAN_CURRENTINFO:
		szTemp.Format("%s", "LOCAL_COUNT_PEDESTRIAN_CURRENTINFO");
		break;
	case MINOR_LOCAL_EXPORT_PEDESTRIAN_CURRENTINFO_REPORT:
		szTemp.Format("%s", "LOCAL_EXPORT_PEDESTRIAN_CURRENTINFO_REPORT");
		break;
	case MINOR_LOCAL_FIND_CAR_CHARGEINFO:
		szTemp.Format("%s", "LOCAL_FIND_CAR_CHARGEINFO");
		break;
	case MINOR_LOCAL_COUNT_CAR_CHARGEINFO:
		szTemp.Format("%s", "LOCAL_COUNT_CAR_CHARGEINFO");
		break;
	case MINOR_LOCAL_EXPORT_CAR_CHARGEINFO_REPORT:
		szTemp.Format("%s", "LOCAL_EXPORT_CAR_CHARGEINFO_REPORT");
		break;
	case MINOR_LOCAL_FIND_SHIFTINFO:
		szTemp.Format("%s", "LOCAL_FIND_SHIFTINFO");
		break;
	case MINOR_LOCAL_FIND_CARDINFO:
		szTemp.Format("%s", "LOCAL_FIND_CARDINFO");
		break;
	case MINOR_LOCAL_ADD_RELIEF_RULE:
		szTemp.Format("%s", "LOCAL_ADD_RELIEF_RULE");
		break;
	case MINOR_LOCAL_MOD_RELIEF_RULE:
		szTemp.Format("%s", "LOCAL_MOD_RELIEF_RULE");
		break;
	case MINOR_LOCAL_DEL_RELIEF_RULE:
		szTemp.Format("%s", "LOCAL_DEL_RELIEF_RULE");
		break;
	case MINOR_LOCAL_FIND_RELIEF_RULE:
		szTemp.Format("%s", "LOCAL_FIND_RELIEF_RULE");
		break;
	case MINOR_LOCAL_GET_ENDETCFG:
		szTemp.Format("%s", "LOCAL_GET_ENDETCFG");
		break;
	case MINOR_LOCAL_SET_ENDETCFG:
		szTemp.Format("%s", "LOCAL_SET_ENDETCFG");
		break;
	case MINOR_LOCAL_SET_ENDEV_ISSUEDDATA:
		szTemp.Format("%s", "LOCAL_SET_ENDEV_ISSUEDDATA");
		break;
	case MINOR_LOCAL_DEL_ENDEV_ISSUEDDATA:
		szTemp.Format("%s", "LOCAL_DEL_ENDEV_ISSUEDDATA");
		break;

    case MINOR_REMOTE_OPEN_DOOR:
        szTemp.Format("%s", "MINOR_REMOTE_OPEN_DOOR");
        break;
    case MINOR_REMOTE_CLOSE_DOOR:
        szTemp.Format("%s", "MINOR_REMOTE_CLOSE_DOOR");
        break;
    case MINOR_REMOTE_ALWAYS_OPEN:
        szTemp.Format("%s", "MINOR_REMOTE_ALWAYS_OPEN");
        break;
    case MINOR_REMOTE_ALWAYS_CLOSE:
        szTemp.Format("%s", "MINOR_REMOTE_ALWAYS_CLOSE");
        break;
    case MINOR_REMOTE_CHECK_TIME:
        szTemp.Format("%s", "MINOR_REMOTE_CHECK_TIME");
        break;
    case MINOR_LOCAL_CHECK_TIME:
        szTemp.Format("%s", "MINOR_LOCAL_CHECK_TIME");
        break;
    case MINOR_NTP_CHECK_TIME:
        szTemp.Format("%s", "MINOR_NTP_CHECK_TIME");
        break;
    case MINOR_REMOTE_CLEAR_CARD:
        szTemp.Format("%s", "MINOR_REMOTE_CLEAR_CARD");
        break;
    case MINOR_REMOTE_RESTORE_CFG:
        szTemp.Format("%s", "MINOR_REMOTE_RESTORE_CFG");
        break;
    case MINOR_ALARMIN_ARM:
        szTemp.Format("%s", "MINOR_ALARMIN_ARM");
        break;
    case MINOR_ALARMIN_DISARM:
        szTemp.Format("%s", "MINOR_ALARMIN_DISARM");
        break;
    case MINOR_REMOTE_ALARMOUT_OPEN_MAN :
        szTemp.Format("%s", "MINOR_REMOTE_ALARMOUT_OPEN_MAN ");
        break;
    case MINOR_REMOTE_ALARMOUT_CLOSE_MAN:
        szTemp.Format("%s", "MINOR_REMOTE_ALARMOUT_CLOSE_MAN");
        break;
    case MINOR_LOCAL_RESTORE_CFG:
        szTemp.Format("%s", "MINOR_LOCAL_RESTORE_CFG");
        break;
    case MINOR_MOD_NET_REPORT_CFG:
        szTemp.Format("%s", "MINOR_MOD_NET_REPORT_CFG");
        break;
    case MINOR_MOD_GPRS_REPORT_PARAM:
        szTemp.Format("%s", "MINOR_MOD_GPRS_REPORT_PARAM");
        break;
    case MINOR_MOD_REPORT_GROUP_PARAM:
        szTemp.Format("%s", "MINOR_MOD_REPORT_GROUP_PARAM");
        break;
    case MINOR_UNLOCK_PASSWORD_OPEN_DOOR:
        szTemp.Format("%s", "MINOR_UNLOCK_PASSWORD_OPEN_DOOR");
        break;

    case MINOR_REMOTE_CAPTURE_PIC:
        szTemp.Format("%s", "MINOR_REMOTE_CAPTURE_PIC");
        break;

    case MINOR_AUTO_RENUMBER:
        szTemp.Format("%s", "MINOR_AUTO_RENUMBER");
        break;
    case MINOR_AUTO_COMPLEMENT_NUMBER:
        szTemp.Format("%s", "MINOR_AUTO_COMPLEMENT_NUMBER");
        break;
    case MINOR_NORMAL_CFGFILE_INPUT:
        szTemp.Format("%s", "MINOR_NORMAL_CFGFILE_INPUT");
        break;
    case MINOR_NORMAL_CFGFILE_OUTTPUT:
        szTemp.Format("%s", "MINOR_NORMAL_CFGFILE_OUTTPUT");
        break;
    case MINOR_CARD_RIGHT_INPUT:
        szTemp.Format("%s", "MINOR_CARD_RIGHT_INPUT");
        break;
    case MINOR_CARD_RIGHT_OUTTPUT:
        szTemp.Format("%s", "MINOR_CARD_RIGHT_OUTTPUT");
        break;
    case MINOR_LOCAL_USB_UPGRADE:
        szTemp.Format("%s", "MINOR_LOCAL_USB_UPGRADE");
        break;
    case MINOR_REMOTE_VISITOR_CALL_LADDER:
        szTemp.Format("%s", "MINOR_REMOTE_VISITOR_CALL_LADDER");
        break;
    case MINOR_REMOTE_HOUSEHOLD_CALL_LADDER:
        szTemp.Format("%s", "MINOR_REMOTE_HOUSEHOLD_CALL_LADDER");
        break;
    case MINOR_REMOTE_ACTUAL_GUARD:
        szTemp.Format("%s", "MINOR_REMOTE_ACTUAL_GUARD");
        break;
    case MINOR_REMOTE_ACTUAL_UNGUARD:
        szTemp.Format("%s", "MINOR_REMOTE_ACTUAL_UNGUARD");
        break;
    case MINOR_REMOTE_CONTROL_NOT_CODE_OPER_FAILED:
        szTemp.Format("%s", "MINOR_REMOTE_CONTROL_NOT_CODE_OPER_FAILED");
        break;
    case MINOR_REMOTE_CONTROL_CLOSE_DOOR:
        szTemp.Format("%s", "MINOR_REMOTE_CONTROL_CLOSE_DOOR");
        break;
    case MINOR_REMOTE_CONTROL_OPEN_DOOR:
        szTemp.Format("%s", "MINOR_REMOTE_CONTROL_OPEN_DOOR");
        break;
    case MINOR_REMOTE_CONTROL_ALWAYS_OPEN_DOOR:
        szTemp.Format("%s", "MINOR_REMOTE_CONTROL_ALWAYS_OPEN_DOOR");
        break;
    case MINOR_OPERATION_CUSTOM1:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM1");
        break;
    case MINOR_OPERATION_CUSTOM2:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM2");
        break;
    case MINOR_OPERATION_CUSTOM3:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM3");
        break;
    case MINOR_OPERATION_CUSTOM4:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM4");
        break;
    case MINOR_OPERATION_CUSTOM5:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM5");
        break;
    case MINOR_OPERATION_CUSTOM6:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM6");
        break;
    case MINOR_OPERATION_CUSTOM7:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM7");
        break;
    case MINOR_OPERATION_CUSTOM8:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM8");
        break;
    case MINOR_OPERATION_CUSTOM9:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM9");
        break;
    case MINOR_OPERATION_CUSTOM10:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM10");
        break;
    case MINOR_OPERATION_CUSTOM11:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM11");
        break;
    case MINOR_OPERATION_CUSTOM12:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM12");
        break;
    case MINOR_OPERATION_CUSTOM13:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM13");
        break;
    case MINOR_OPERATION_CUSTOM14:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM14");
        break;
    case MINOR_OPERATION_CUSTOM15:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM15");
        break;
    case MINOR_OPERATION_CUSTOM16:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM16");
        break;
    case MINOR_OPERATION_CUSTOM17:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM17");
        break;
    case MINOR_OPERATION_CUSTOM18:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM18");
        break;
    case MINOR_OPERATION_CUSTOM19:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM19");
        break;
    case MINOR_OPERATION_CUSTOM20:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM20");
        break;
    case MINOR_OPERATION_CUSTOM21:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM21");
        break;
    case MINOR_OPERATION_CUSTOM22:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM22");
        break;
    case MINOR_OPERATION_CUSTOM23:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM23");
        break;
    case MINOR_OPERATION_CUSTOM24:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM24");
        break;
    case MINOR_OPERATION_CUSTOM25:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM25");
        break;
    case MINOR_OPERATION_CUSTOM26:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM26");
        break;
    case MINOR_OPERATION_CUSTOM27:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM27");
        break;
    case MINOR_OPERATION_CUSTOM28:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM28");
        break;
    case MINOR_OPERATION_CUSTOM29:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM29");
        break;
    case MINOR_OPERATION_CUSTOM30:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM30");
        break;
    case MINOR_OPERATION_CUSTOM31:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM31");
        break;
    case MINOR_OPERATION_CUSTOM32:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM32");
        break;
    case MINOR_OPERATION_CUSTOM33:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM33");
        break;
    case MINOR_OPERATION_CUSTOM34:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM34");
        break;
    case MINOR_OPERATION_CUSTOM35:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM35");
        break;
    case MINOR_OPERATION_CUSTOM36:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM36");
        break;
    case MINOR_OPERATION_CUSTOM37:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM37");
        break;
    case MINOR_OPERATION_CUSTOM38:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM38");
        break;
    case MINOR_OPERATION_CUSTOM39:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM39");
        break;
    case MINOR_OPERATION_CUSTOM40:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM40");
        break;
    case MINOR_OPERATION_CUSTOM41:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM41");
        break;
    case MINOR_OPERATION_CUSTOM42:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM42");
        break;
    case MINOR_OPERATION_CUSTOM43:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM43");
        break;
    case MINOR_OPERATION_CUSTOM44:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM44");
        break;
    case MINOR_OPERATION_CUSTOM45:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM45");
        break;
    case MINOR_OPERATION_CUSTOM46:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM46");
        break;
    case MINOR_OPERATION_CUSTOM47:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM47");
        break;
    case MINOR_OPERATION_CUSTOM48:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM48");
        break;
    case MINOR_OPERATION_CUSTOM49:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM49");
        break;
    case MINOR_OPERATION_CUSTOM50:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM50");
        break;
    case MINOR_OPERATION_CUSTOM51:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM51");
        break;
    case MINOR_OPERATION_CUSTOM52:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM52");
        break;
    case MINOR_OPERATION_CUSTOM53:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM53");
        break;
    case MINOR_OPERATION_CUSTOM54:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM54");
        break;
    case MINOR_OPERATION_CUSTOM55:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM55");
        break;
    case MINOR_OPERATION_CUSTOM56:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM56");
        break;
    case MINOR_OPERATION_CUSTOM57:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM57");
        break;
    case MINOR_OPERATION_CUSTOM58:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM58");
        break;
    case MINOR_OPERATION_CUSTOM59:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM59");
        break;
    case MINOR_OPERATION_CUSTOM60:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM60");
        break;
    case MINOR_OPERATION_CUSTOM61:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM61");
        break;
    case MINOR_OPERATION_CUSTOM62:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM62");
        break;
    case MINOR_OPERATION_CUSTOM63:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM63");
        break;
    case MINOR_OPERATION_CUSTOM64:
        szTemp.Format("%s", "MINOR_OPERATION_CUSTOM64");
        break;

    case MINOR_LOCAL_SET_DEVICE_ACTIVE:
        szTemp.Format("%s", "MINOR_LOCAL_SET_DEVICE_ACTIVE");
        break;
    case MINOR_REMOTE_SET_DEVICE_ACTIVE:
        szTemp.Format("%s", "MINOR_REMOTE_SET_DEVICE_ACTIVE");
        break;
    case MINOR_LOCAL_PARA_FACTORY_DEFAULT:
        szTemp.Format("%s", "MINOR_LOCAL_PARA_FACTORY_DEFAULT");
        break;
    case MINOR_REMOTE_PARA_FACTORY_DEFAULT:
        szTemp.Format("%s", "MINOR_REMOTE_PARA_FACTORY_DEFAULT");
        break;
    case MINOR_UPLAOD_STATIC_MATERIAL:
        szTemp.Format("%s", "MINOR_UPLAOD_STATIC_MATERIAL");
        break;
    case MINOR_UPLOAD_DYNAMIC_MATERIAL:
        szTemp.Format("%s", "MINOR_UPLOAD_DYNAMIC_MATERIAL");
        break;
    case MINOR_DELETE_MATERIAL:
        szTemp.Format("%s", "MINOR_DELETE_MATERIAL");
        break;
    case MINOR_DOWNLOAD_STATIC_MATERIAL:
        szTemp.Format("%s", "MINOR_DOWNLOAD_STATIC_MATERIAL");
        break;
    case MINOR_COVER_STATIC_MATERIAL:
        szTemp.Format("%s", "MINOR_COVER_STATIC_MATERIAL");
        break;
    case  MINOR_APPROVE_MATERIAL:
        szTemp.Format("%s", "MINOR_APPROVE_MATERIAL");
        break;
    case MINOR_UPLAOD_PROGRAM:
        szTemp.Format("%s", "MINOR_UPLAOD_PROGRAM");
        break;
    case MINOR_DOWNLOAD_PROGRAM:
        szTemp.Format("%s", "MINOR_DOWNLOAD_PROGRAM");
        break;
    case MINOR_DELETE_PROGRAM:
        szTemp.Format("%s", "MINOR_DELETE_PROGRAM");
        break;
    case MINOR_MODIFY_PROGRAM:
        szTemp.Format("%s", "MINOR_MODIFY_PROGRAM");
        break;
    case MINOR_APPROVE_PRAGRAM:
        szTemp.Format("%s", "MINOR_APPROVE_PRAGRAM");
        break;
    case  MINOR_UPLAOD_SCHEDULE:
        szTemp.Format("%s", "MINOR_UPLAOD_SCHEDULE");
        break;
    case MINOR_DOWNLOAD_SCHEDULE:
        szTemp.Format("%s", "MINOR_DOWNLOAD_SCHEDULE");
        break;
    case MINOR_DELETE_SCHEDULE:
        szTemp.Format("%s", "MINOR_DELETE_SCHEDULE");
        break;
    case MINOR_MODIFY_SCHEDULE:
        szTemp.Format("%s", "MINOR_MODIFY_SCHEDULE");
        break;
    case MINOR_RELEASE_SCHEDULE:
        szTemp.Format("%s", "MINOR_RELEASE_SCHEDULE");
        break;
    case MINOR_ADD_TERMINAL:
        szTemp.Format("%s", "MINOR_ADD_TERMINAL");
        break;
    case  MINOR_DELETE_TERMINAL:
        szTemp.Format("%s", "MINOR_DELETE_TERMINAL");
        break;
    case MINOR_MODIFY_TERMIANL_PARAM:
        szTemp.Format("%s", "MINOR_MODIFY_TERMIANL_PARAM");
        break;
    case  MINOR_MODIFY_TERMIANL_PLAY_PARAM:
        szTemp.Format("%s", "MINOR_MODIFY_TERMIANL_PLAY_PARAM");
        break;
    case MINOR_ADD_TERMIANL_GROUP:
        szTemp.Format("%s", "MINOR_ADD_TERMIANL_GROUP");
        break;
    case MINOR_MODIFY_TERMINAL_GROUP_PARAM:
        szTemp.Format("%s", "MINOR_MODIFY_TERMINAL_GROUP_PARAM");
        break;
    case MINOR_DELETE_TERMIANL_GROUP:
        szTemp.Format("%s", "MINOR_DELETE_TERMIANL_GROUP");
        break;
    case MINOR_TERMINAL_PLAY_CONTROL:
        szTemp.Format("%s", "MINOR_TERMINAL_PLAY_CONTROL");
        break;

    case  MINOR_TERMINAL_ON_OFF_LINE:
        szTemp.Format("%s", "MINOR_TERMINAL_ON_OFF_LINE");
        break;
    case MINOR_SET_SWITCH_PLAN:
        szTemp.Format("%s", "MINOR_SET_SWITCH_PLAN");
        break;
    case  MINOR_SET_VOLUME_PLAN:
        szTemp.Format("%s", "MINOR_SET_VOLUME_PLAN");
        break;
    case MINOR_TERMINAL_SCREENSHOT:
        szTemp.Format("%s", "MINOR_TERMINAL_SCREENSHOT");
        break;
    case  MINOR_LOCAL_RESET_LOGIN_PASSWORD:
        szTemp.Format("%s", "MINOR_LOCAL_RESET_LOGIN_PASSWORD");
        break;
    case MINOR_REMOTE_RESET_LOGIN_PASSWORD:
        szTemp.Format("%s", "MINOR_REMOTE_RESET_LOGIN_PASSWORD");
        break;
    default:
        szTemp.Format("0x%x", stLogInfo.dwMinorType);
        break;
    }
}

/*********************************************************
Function:	InfoMinorTypeMap
Desc:		get the string of the log minor type 
Input:	stLogInfo, log information; szTemp, log string;
Output:	none
Return:	none
**********************************************************/
void InfoMinorTypeMap(NET_DVR_LOG_V50 stLogInfo, CString &szTemp)
{
    CString szParaType;
    switch(stLogInfo.dwMinorType)
    {
        //information
    case MINOR_HDD_INFO:
        szTemp.Format("%s", "HDD_INFO");
        break;
    case MINOR_SMART_INFO:
        szTemp.Format("%s", "SMART_INFO");
        break;
    case MINOR_REC_START:
        szTemp.Format("%s", "REC_START");
        break;
    case MINOR_REC_STOP:
        szTemp.Format("%s", "REC_STOP");
        break;
    case MINOR_REC_OVERDUE:
        szTemp.Format("%s", "REC_OVERDUE");
        break;	 
    case MINOR_LINK_START:
        szTemp.Format("%s", "LINK_START");
        break;	 
    case MINOR_LINK_STOP:
        szTemp.Format("%s", "LINK_STOP");
        break;	 
	case MINOR_NET_DISK_INFO:
		szTemp.Format("%s", "NET_DISK_INFO");
        break;
    case MINOR_RAID_INFO:
        szTemp.Format("%s", "RAID_INFO");
        break;
	case MINOR_RUN_STATUS_INFO:
		szTemp.Format("%s","RUN_STATUS_INFO");
		break;
	case MINOR_SPARE_START_BACKUP:
        szTemp.Format("%s", "SPARE_START_BACKUP");
        break;	 
    case MINOR_SPARE_STOP_BACKUP:
        szTemp.Format("%s", "SPARE_STOP_BACKUP");
        break;	 
	case MINOR_SPARE_CLIENT_INFO:
		szTemp.Format("%s", "SPARE_CLIENT_INFO");
        break;
    case MINOR_ANR_RECORD_START:
        szTemp.Format("%s", "ANR_RECORD_START");
        break;
	case MINOR_ANR_RECORD_END:
		szTemp.Format("%s","ANR_RECORD_END");
		break;
	case MINOR_ANR_ADD_TIME_QUANTUM:
        szTemp.Format("%s", "MINOR_ANR_ADD_TIME_QUANTUM");
        break;
	case MINOR_ANR_DEL_TIME_QUANTUM:
		szTemp.Format("%s","MINOR_ANR_DEL_TIME_QUANTUM");
		break;
    case MINOR_PLAT_INFO:
        szTemp.Format("%s","PLAT_INFO");
        break;
    case MINOR_DIAL_STAT:
        szTemp.Format("%s","DIAL_STAT");
        break;
	case MINOR_UNLOCK_RECORD:
		szTemp.Format("%s","MINOR_UNLOCK_RECORD");
		break;
	case MINOR_VIS_ALARM:
		szTemp.Format("%s","MINOR_ZONE_ALARM");
		break;
	case MINOR_TALK_RECORD:
		szTemp.Format("%s","MINOR_TALK_RECORD");
		break;
    case MINOR_ACCESSORIES_MESSAGE:
        szTemp.Format("%s", "MINOR_ACCESSORIES_MESSAGE");
        break;
    case MINOR_KMS_EXPAMSION_DISK_INSERT:
        szTemp.Format("%s", "MINOR_KMS_EXPAMSION_DISK_INSERT");
        break;
    case MINOR_IPC_CONNECT:
        szTemp.Format("%s", "MINOR_IPC_CONNECT");
        break;
    case MINOR_INTELLIGENT_BOARD_STATUS:
        szTemp.Format("%s", "MINOR_INTELLIGENT_BOARD_STATUS");
        break;
    case MINOR_IPC_CONNECT_STATUS:
        szTemp.Format("%s", "MINOR_IPC_CONNECT_STATUS");
        break;
    case MINOR_AUTO_TIMING:
        szTemp.Format("%s", "MINOR_AUTO_TIMING");
        break;
    case MINOR_EZVIZ_OPERATION:
        szTemp.Format("%s", "MINOR_EZVIZ_OPERATION");
        break;
    default:
        szTemp.Format("0x%x", stLogInfo.dwMinorType);
        break;
    }
}


void EventMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp)
{
    char  szLan[128];
    switch(stLogInfo.dwMinorType)
    {
        case MINOR_LEGAL_CARD_PASS:
            sprintf(szLan, "MINOR_LEGAL_CARD_PASS");     
            break; 
        case MINOR_CARD_AND_PSW_PASS:
            sprintf(szLan, "MINOR_CARD_AND_PSW_PASS");     
            break; 
        case MINOR_CARD_AND_PSW_FAIL:
            sprintf(szLan, " MINOR_CARD_AND_PSW_FAIL");     
            break; 
        case MINOR_CARD_AND_PSW_TIMEOUT:
            sprintf(szLan, "MINOR_CARD_AND_PSW_TIMEOUT");     
            break; 
        case MINOR_CARD_AND_PSW_OVER_TIME:
            sprintf(szLan, "MINOR_CARD_AND_PSW_OVER_TIME");     
            break; 
        case MINOR_CARD_NO_RIGHT:
            sprintf(szLan, "MINOR_CARD_NO_RIGHT");     
            break; 
        case MINOR_CARD_INVALID_PERIOD:
            sprintf(szLan, "MINOR_CARD_INVALID_PERIOD");
            break; 
        case MINOR_CARD_OUT_OF_DATE:
            sprintf(szLan, "MINOR_CARD_OUT_OF_DATE");
            break; 
        case MINOR_INVALID_CARD:
            sprintf(szLan, "MINOR_INVALID_CARD");
            break; 
        case  MINOR_ANTI_SNEAK_FAIL:
            sprintf(szLan, "MINOR_ANTI_SNEAK_FAIL");     
            break; 
        case MINOR_INTERLOCK_DOOR_NOT_CLOSE:
            sprintf(szLan, "MINOR_INTERLOCK_DOOR_NOT_CLOSE");
            break; 
        case MINOR_NOT_BELONG_MULTI_GROUP:
            sprintf(szLan, "MINOR_NOT_BELONG_MULTI_GROUP");
            break; 
        case MINOR_INVALID_MULTI_VERIFY_PERIOD:
            sprintf(szLan, "MINOR_INVALID_MULTI_VERIFY_PERIOD");
            break;    
        case  MINOR_MULTI_VERIFY_SUPER_RIGHT_FAIL:
            sprintf(szLan, "MINOR_MULTI_VERIFY_SUPER_RIGHT_FAIL");     
            break; 
        case MINOR_MULTI_VERIFY_REMOTE_RIGHT_FAIL:
            sprintf(szLan, "MINOR_MULTI_VERIFY_REMOTE_RIGHT_FAIL");
            break; 
        case MINOR_MULTI_VERIFY_SUCCESS:
            sprintf(szLan, "MINOR_MULTI_VERIFY_SUCCESS");
            break; 
        case MINOR_LEADER_CARD_OPEN_BEGIN:
            sprintf(szLan, "MINOR_LEADER_CARD_OPEN_BEGIN");
            break; 
        case  MINOR_LEADER_CARD_OPEN_END:
            sprintf(szLan, "MINOR_LEADER_CARD_OPEN_END");     
            break; 
        case MINOR_ALWAYS_OPEN_BEGIN:
            sprintf(szLan, "MINOR_ALWAYS_OPEN_BEGIN");
            break; 
        case MINOR_ALWAYS_OPEN_END:
            sprintf(szLan, "MINOR_ALWAYS_OPEN_END");
            break; 
        case  MINOR_LOCK_OPEN:
            sprintf(szLan, "MINOR_LOCK_OPEN");     
            break; 
        case MINOR_LOCK_CLOSE:
            sprintf(szLan, "MINOR_LOCK_CLOSE");
            break; 
        case MINOR_DOOR_BUTTON_PRESS:
            sprintf(szLan, "MINOR_DOOR_BUTTON_PRESS");
            break; 
        case MINOR_DOOR_BUTTON_RELEASE:
            sprintf(szLan, "MINOR_DOOR_BUTTON_RELEASE");
            break; 
        case MINOR_DOOR_OPEN_NORMAL:
            sprintf(szLan, "MINOR_DOOR_OPEN_NORMAL");
            break; 
        case MINOR_DOOR_CLOSE_NORMAL:
            sprintf(szLan, "MINOR_DOOR_CLOSE_NORMAL");     
            break; 
        case MINOR_DOOR_OPEN_ABNORMAL:
            sprintf(szLan, "MINOR_DOOR_OPEN_ABNORMAL");
            break; 
        case MINOR_DOOR_OPEN_TIMEOUT:
            sprintf(szLan, "MINOR_DOOR_OPEN_TIMEOUT");
            break; 
        case MINOR_ALARMOUT_ON:
            sprintf(szLan, "MINOR_ALARMOUT_ON");
            break; 
        case MINOR_ALARMOUT_OFF:
            sprintf(szLan, "MINOR_ALARMOUT_OFF");
            break; 
        case MINOR_ALWAYS_CLOSE_BEGIN:
            sprintf(szLan, "MINOR_ALWAYS_CLOSE_BEGIN");
            break; 
        case MINOR_ALWAYS_CLOSE_END:
            sprintf(szLan, "MINOR_ALWAYS_CLOSE_END");
            break;
        case MINOR_MULTI_VERIFY_NEED_REMOTE_OPEN:
            sprintf(szLan, "MINOR_MULTI_VERIFY_NEED_REMOTE_OPEN");
            break;
        
        case MINOR_MULTI_VERIFY_SUPERPASSWD_VERIFY_SUCCESS:
            sprintf(szLan, "MINOR_MULTI_VERIFY_SUPERPASSWD_VERIFY_SUCCESS");
            break; 
        case MINOR_MULTI_VERIFY_REPEAT_VERIFY:
            sprintf(szLan, "MINOR_MULTI_VERIFY_REPEAT_VERIFY");
            break;
        case MINOR_MULTI_VERIFY_TIMEOUT :
            sprintf(szLan, "MINOR_MULTI_VERIFY_TIMEOUT");
            break;
        case MINOR_DOORBELL_RINGING :
            sprintf(szLan, "MINOR_DOORBELL_RINGING");
            break;
        case MINOR_FINGERPRINT_COMPARE_PASS :
            sprintf(szLan, "MINOR_FINGERPRINT_COMPARE_PASS");
            break;
        case MINOR_FINGERPRINT_COMPARE_FAIL :
            sprintf(szLan, "MINOR_FINGERPRINT_COMPARE_FAIL");
            break;
        case MINOR_CARD_FINGERPRINT_VERIFY_PASS :
            sprintf(szLan, "MINOR_CARD_FINGERPRINT_VERIFY_PASS");
            break;
        case MINOR_CARD_FINGERPRINT_VERIFY_FAIL :
            sprintf(szLan, "MINOR_CARD_FINGERPRINT_VERIFY_FAIL");
            break;
        case MINOR_CARD_FINGERPRINT_VERIFY_TIMEOUT :
            sprintf(szLan, "MINOR_CARD_FINGERPRINT_VERIFY_TIMEOUT");
            break;
        case MINOR_CARD_FINGERPRINT_PASSWD_VERIFY_PASS :
            sprintf(szLan, "MINOR_CARD_FINGERPRINT_PASSWD_VERIFY_PASS");
            break;
        case MINOR_CARD_FINGERPRINT_PASSWD_VERIFY_FAIL :
            sprintf(szLan, "MINOR_CARD_FINGERPRINT_PASSWD_VERIFY_FAIL");
            break;
        case MINOR_CARD_FINGERPRINT_PASSWD_VERIFY_TIMEOUT :
            sprintf(szLan, "MINOR_CARD_FINGERPRINT_PASSWD_VERIFY_TIMEOUT");
            break;
        case MINOR_FINGERPRINT_PASSWD_VERIFY_PASS :
            sprintf(szLan, "MINOR_FINGERPRINT_PASSWD_VERIFY_PASS");
            break;
        case MINOR_FINGERPRINT_PASSWD_VERIFY_FAIL :
            sprintf(szLan, "MINOR_FINGERPRINT_PASSWD_VERIFY_FAIL");
            break;
        case MINOR_FINGERPRINT_PASSWD_VERIFY_TIMEOUT :
            sprintf(szLan, "MINOR_FINGERPRINT_PASSWD_VERIFY_TIMEOUT");
            break;
        case MINOR_FINGERPRINT_INEXISTENCE :
            sprintf(szLan, "MINOR_FINGERPRINT_INEXISTENCE");
            break;
        case MINOR_CARD_PLATFORM_VERIFY :
            sprintf(szLan, "MINOR_CARD_PLATFORM_VERIFY");
            break;
        case MINOR_CALL_CENTER:
            sprintf(szLan, "MINOR_CALL_CENTER");
            break;
        case MINOR_FIRE_RELAY_TURN_ON_DOOR_ALWAYS_OPEN:
            sprintf(szLan, "MINOR_FIRE_RELAY_TURN_ON_DOOR_ALWAYS_OPEN");
            break;
        case MINOR_FIRE_RELAY_RECOVER_DOOR_RECOVER_NORMAL:
            sprintf(szLan, "MINOR_FIRE_RELAY_RECOVER_DOOR_RECOVER_NORMAL");
            break;
        case MINOR_FACE_AND_FP_VERIFY_PASS:
            sprintf(szLan, "MINOR_FACE_AND_FP_VERIFY_PASS");
            break;
        case MINOR_FACE_AND_FP_VERIFY_FAIL:
            sprintf(szLan, "MINOR_FACE_AND_FP_VERIFY_FAIL");
            break;
        case MINOR_FACE_AND_FP_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_FACE_AND_FP_VERIFY_TIMEOUT");
            break;
        case MINOR_FACE_AND_PW_VERIFY_PASS:
            sprintf(szLan, "MINOR_FACE_AND_PW_VERIFY_PASS");
            break;
        case MINOR_FACE_AND_PW_VERIFY_FAIL:
            sprintf(szLan, "MINOR_FACE_AND_PW_VERIFY_FAIL");
            break;
        case MINOR_FACE_AND_PW_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_FACE_AND_PW_VERIFY_TIMEOUT");
            break;
        case MINOR_FACE_AND_CARD_VERIFY_PASS:
            sprintf(szLan, "MINOR_FACE_AND_CARD_VERIFY_PASS");
            break;
        case MINOR_FACE_AND_CARD_VERIFY_FAIL:
            sprintf(szLan, "MINOR_FACE_AND_CARD_VERIFY_FAIL");
            break;
        case MINOR_FACE_AND_CARD_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_FACE_AND_CARD_VERIFY_TIMEOUT");
            break;
        case MINOR_FACE_AND_PW_AND_FP_VERIFY_PASS:
            sprintf(szLan, "MINOR_FACE_AND_PW_AND_FP_VERIFY_PASS");
            break;
        case MINOR_FACE_AND_PW_AND_FP_VERIFY_FAIL:
            sprintf(szLan, "MINOR_FACE_AND_PW_AND_FP_VERIFY_FAIL");
            break;
        case MINOR_FACE_AND_PW_AND_FP_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_FACE_AND_PW_AND_FP_VERIFY_TIMEOUT");
            break;
        case MINOR_FACE_CARD_AND_FP_VERIFY_PASS:
            sprintf(szLan, "MINOR_FACE_CARD_AND_FP_VERIFY_PASS");
            break;
        case MINOR_FACE_CARD_AND_FP_VERIFY_FAIL:
            sprintf(szLan, "MINOR_FACE_CARD_AND_FP_VERIFY_FAIL");
            break;
        case MINOR_FACE_CARD_AND_FP_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_FACE_CARD_AND_FP_VERIFY_TIMEOUT");
            break;
        case MINOR_EMPLOYEENO_AND_FP_VERIFY_PASS:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FP_VERIFY_PASS");
            break;
        case MINOR_EMPLOYEENO_AND_FP_VERIFY_FAIL:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FP_VERIFY_FAIL");
            break;
        case MINOR_EMPLOYEENO_AND_FP_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FP_VERIFY_TIMEOUT");
            break;
        case MINOR_EMPLOYEENO_AND_FP_AND_PW_VERIFY_PASS:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FP_AND_PW_VERIFY_PASS");
            break;
        case MINOR_EMPLOYEENO_AND_FP_AND_PW_VERIFY_FAIL:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FP_AND_PW_VERIFY_FAIL");
            break;
        case MINOR_EMPLOYEENO_AND_FP_AND_PW_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FP_AND_PW_VERIFY_TIMEOUT");
            break;
        case MINOR_FACE_VERIFY_PASS:
            sprintf(szLan, "MINOR_FACE_VERIFY_PASS");
            break;
        case MINOR_FACE_VERIFY_FAIL:
            sprintf(szLan, "MINOR_FACE_VERIFY_FAIL");
            break;
        case MINOR_EMPLOYEENO_AND_FACE_VERIFY_PASS:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FACE_VERIFY_PASS");
            break;
        case MINOR_EMPLOYEENO_AND_FACE_VERIFY_FAIL:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FACE_VERIFY_FAIL");
            break;
        case MINOR_EMPLOYEENO_AND_FACE_VERIFY_TIMEOUT:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_FACE_VERIFY_TIMEOUT");
            break;
        case MINOR_FACE_RECOGNIZE_FAIL:
            sprintf(szLan, "MINOR_FACE_RECOGNIZE_FAIL");
            break;
        case MINOR_FIRSTCARD_AUTHORIZE_BEGIN:
            sprintf(szLan, "MINOR_FIRSTCARD_AUTHORIZE_BEGIN");
            break;
        case MINOR_FIRSTCARD_AUTHORIZE_END:
            sprintf(szLan, "MINOR_FIRSTCARD_AUTHORIZE_END");
            break;
        case MINOR_DOORLOCK_INPUT_SHORT_CIRCUIT:
            sprintf(szLan, "MINOR_DOORLOCK_INPUT_SHORT_CIRCUIT");
            break;
        case MINOR_DOORLOCK_INPUT_BROKEN_CIRCUIT:
            sprintf(szLan, "MINOR_DOORLOCK_INPUT_BROKEN_CIRCUIT");
            break;
        case MINOR_DOORLOCK_INPUT_EXCEPTION:
            sprintf(szLan, "MINOR_DOORLOCK_INPUT_EXCEPTION");
            break;
        case MINOR_DOORCONTACT_INPUT_SHORT_CIRCUIT:
            sprintf(szLan, "MINOR_DOORCONTACT_INPUT_SHORT_CIRCUIT");
            break;
        case MINOR_DOORCONTACT_INPUT_BROKEN_CIRCUIT:
            sprintf(szLan, "MINOR_DOORCONTACT_INPUT_BROKEN_CIRCUIT");
            break;
        case MINOR_DOORCONTACT_INPUT_EXCEPTION:
            sprintf(szLan, "MINOR_DOORCONTACT_INPUT_EXCEPTION");
            break;
        case MINOR_OPENBUTTON_INPUT_SHORT_CIRCUIT:
            sprintf(szLan, "MINOR_OPENBUTTON_INPUT_SHORT_CIRCUIT");
            break;
        case MINOR_OPENBUTTON_INPUT_BROKEN_CIRCUIT:
            sprintf(szLan, "MINOR_OPENBUTTON_INPUT_BROKEN_CIRCUIT");
            break;
        case MINOR_OPENBUTTON_INPUT_EXCEPTION:
            sprintf(szLan, "MINOR_OPENBUTTON_INPUT_EXCEPTION");
            break;
        case MINOR_DOORLOCK_OPEN_EXCEPTION:
            sprintf(szLan, "MINOR_DOORLOCK_OPEN_EXCEPTION");
            break;
        case MINOR_DOORLOCK_OPEN_TIMEOUT:
            sprintf(szLan, "MINOR_DOORLOCK_OPEN_TIMEOUT");
            break;
        case MINOR_FIRSTCARD_OPEN_WITHOUT_AUTHORIZE:
            sprintf(szLan, "MINOR_FIRSTCARD_OPEN_WITHOUT_AUTHORIZE");
            break;
        case MINOR_CALL_LADDER_RELAY_BREAK:
            sprintf(szLan, "MINOR_CALL_LADDER_RELAY_BREAK");
            break;
        case MINOR_CALL_LADDER_RELAY_CLOSE:
            sprintf(szLan, "MINOR_CALL_LADDER_RELAY_CLOSE");
            break;
        case MINOR_AUTO_KEY_RELAY_BREAK:
            sprintf(szLan, "MINOR_AUTO_KEY_RELAY_BREAK");
            break;
        case MINOR_AUTO_KEY_RELAY_CLOSE:
            sprintf(szLan, "MINOR_AUTO_KEY_RELAY_CLOSE");
            break;
        case MINOR_KEY_CONTROL_RELAY_BREAK:
            sprintf(szLan, "MINOR_KEY_CONTROL_RELAY_BREAK");
            break;
        case MINOR_KEY_CONTROL_RELAY_CLOSE:
            sprintf(szLan, "MINOR_KEY_CONTROL_RELAY_CLOSE");
            break;
        case MINOR_EMPLOYEENO_AND_PW_PASS:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_PW_PASS");
            break;
        case MINOR_EMPLOYEENO_AND_PW_FAIL:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_PW_FAIL");
            break;
        case MINOR_EMPLOYEENO_AND_PW_TIMEOUT:
            sprintf(szLan, "MINOR_EMPLOYEENO_AND_PW_TIMEOUT");
            break;
        case MINOR_HUMAN_DETECT_FAIL:
            sprintf(szLan, "MINOR_HUMAN_DETECT_FAIL");
            break;
        case MINOR_PEOPLE_AND_ID_CARD_COMPARE_PASS:
            sprintf(szLan, "MINOR_PEOPLE_AND_ID_CARD_COMPARE_PASS");
            break;
        case MINOR_PEOPLE_AND_ID_CARD_COMPARE_FAIL:
            sprintf(szLan, "MINOR_PEOPLE_AND_ID_CARD_COMPARE_FAIL");
            break;
        case MINOR_CERTIFICATE_BLACK_LIST:
            sprintf(szLan, "MINOR_CERTIFICATE_BLACK_LIST");
            break;
        case MINOR_MAC_DETECT:
            sprintf(szLan, "MINOR_MAC_DETECT");
            break;
        case MINOR_LEGAL_MESSAGE:
            sprintf(szLan, "MINOR_LEGAL_MESSAGE");
            break;
        case MINOR_ILLEGAL_MESSAGE:
            sprintf(szLan, "MINOR_ILLEGAL_MESSAGE");
            break;
        case MINOR_DOOR_OPEN_OR_DORMANT_FAIL:
            sprintf(szLan, "MINOR_DOOR_OPEN_OR_DORMANT_FAIL");
            break;
        case MINOR_AUTH_PLAN_DORMANT_FAIL:
            sprintf(szLan, "MINOR_AUTH_PLAN_DORMANT_FAIL");
            break;
        case MINOR_CARD_ENCRYPT_VERIFY_FAIL:
            sprintf(szLan, "MINOR_CARD_ENCRYPT_VERIFY_FAIL");
            break;
        case MINOR_SUBMARINEBACK_REPLY_FAIL:
            sprintf(szLan, "MINOR_SUBMARINEBACK_REPLY_FAIL");
            break;
        case MINOR_DOOR_OPEN_OR_DORMANT_OPEN_FAIL:
            sprintf(szLan, "MINOR_DOOR_OPEN_OR_DORMANT_OPEN_FAIL");
            break;
        case MINOR_HEART_BEAT:
            sprintf(szLan, "MINOR_HEART_BEAT");
            break;
        case MINOR_DOOR_OPEN_OR_DORMANT_LINKAGE_OPEN_FAIL:
            sprintf(szLan, "MINOR_DOOR_OPEN_OR_DORMANT_LINKAGE_OPEN_FAIL");
            break;
        case MINOR_TRAILING:
            sprintf(szLan, "MINOR_TRAILING");
            break;
        case MINOR_REVERSE_ACCESS:
            sprintf(szLan, "MINOR_REVERSE_ACCESS");
            break;
        case MINOR_FORCE_ACCESS:
            sprintf(szLan, "MINOR_FORCE_ACCESS");
            break;
        case MINOR_CLIMBING_OVER_GATE:
            sprintf(szLan, "MINOR_CLIMBING_OVER_GATE");
            break;
        case MINOR_PASSING_TIMEOUT:
            sprintf(szLan, "MINOR_PASSING_TIMEOUT");
            break;
        case MINOR_INTRUSION_ALARM:
            sprintf(szLan, "MINOR_INTRUSION_ALARM");
            break;
        case MINOR_FREE_GATE_PASS_NOT_AUTH:
            sprintf(szLan, "MINOR_FREE_GATE_PASS_NOT_AUTH");
            break;
        case MINOR_DROP_ARM_BLOCK:
            sprintf(szLan, "MINOR_DROP_ARM_BLOCK");
            break;
        case MINOR_DROP_ARM_BLOCK_RESUME:
            sprintf(szLan, "MINOR_DROP_ARM_BLOCK_RESUME");
            break;
        case MINOR_LOCAL_FACE_MODELING_FAIL:
            sprintf(szLan, "MINOR_LOCAL_FACE_MODELING_FAIL");
            break;
        case MINOR_STAY_EVENT:
            sprintf(szLan, "MINOR_STAY_EVENT");
            break;
        case MINOR_EVENT_CUSTOM1:
            sprintf(szLan, "MINOR_EVENT_CUSTOM1");
            break;
        case MINOR_EVENT_CUSTOM2:
            sprintf(szLan, "MINOR_EVENT_CUSTOM2");
            break;
        case MINOR_EVENT_CUSTOM3:
            sprintf(szLan, "MINOR_EVENT_CUSTOM3");
            break;
        case MINOR_EVENT_CUSTOM4:
            sprintf(szLan, "MINOR_EVENT_CUSTOM4");
            break;
        case MINOR_EVENT_CUSTOM5:
            sprintf(szLan, "MINOR_EVENT_CUSTOM5");
            break;
        case MINOR_EVENT_CUSTOM6:
            sprintf(szLan, "MINOR_EVENT_CUSTOM6");
            break;
        case MINOR_EVENT_CUSTOM7:
            sprintf(szLan, "MINOR_EVENT_CUSTOM7");
            break;
        case MINOR_EVENT_CUSTOM8:
            sprintf(szLan, "MINOR_EVENT_CUSTOM8");
            break;
        case MINOR_EVENT_CUSTOM9:
            sprintf(szLan, "MINOR_EVENT_CUSTOM9");
            break;
        case MINOR_EVENT_CUSTOM10:
            sprintf(szLan, "MINOR_EVENT_CUSTOM10");
            break;
        case MINOR_EVENT_CUSTOM11:
            sprintf(szLan, "MINOR_EVENT_CUSTOM11");
            break;
        case MINOR_EVENT_CUSTOM12:
            sprintf(szLan, "MINOR_EVENT_CUSTOM12");
            break;
        case MINOR_EVENT_CUSTOM13:
            sprintf(szLan, "MINOR_EVENT_CUSTOM13");
            break;
        case MINOR_EVENT_CUSTOM14:
            sprintf(szLan, "MINOR_EVENT_CUSTOM14");
            break;
        case MINOR_EVENT_CUSTOM15:
            sprintf(szLan, "MINOR_EVENT_CUSTOM15");
            break;
        case MINOR_EVENT_CUSTOM16:
            sprintf(szLan, "MINOR_EVENT_CUSTOM16");
            break;
        case MINOR_EVENT_CUSTOM17:
            sprintf(szLan, "MINOR_EVENT_CUSTOM17");
            break;
        case MINOR_EVENT_CUSTOM18:
            sprintf(szLan, "MINOR_EVENT_CUSTOM18");
            break;
        case MINOR_EVENT_CUSTOM19:
            sprintf(szLan, "MINOR_EVENT_CUSTOM19");
            break;
        case MINOR_EVENT_CUSTOM20:
            sprintf(szLan, "MINOR_EVENT_CUSTOM20");
            break;
        case MINOR_EVENT_CUSTOM21:
            sprintf(szLan, "MINOR_EVENT_CUSTOM21");
            break;
        case MINOR_EVENT_CUSTOM22:
            sprintf(szLan, "MINOR_EVENT_CUSTOM22");
            break;
        case MINOR_EVENT_CUSTOM23:
            sprintf(szLan, "MINOR_EVENT_CUSTOM23");
            break;
        case MINOR_EVENT_CUSTOM24:
            sprintf(szLan, "MINOR_EVENT_CUSTOM24");
            break;
        case MINOR_EVENT_CUSTOM25:
            sprintf(szLan, "MINOR_EVENT_CUSTOM25");
            break;
        case MINOR_EVENT_CUSTOM26:
            sprintf(szLan, "MINOR_EVENT_CUSTOM26");
            break;
        case MINOR_EVENT_CUSTOM27:
            sprintf(szLan, "MINOR_EVENT_CUSTOM27");
            break;
        case MINOR_EVENT_CUSTOM28:
            sprintf(szLan, "MINOR_EVENT_CUSTOM28");
            break;
        case MINOR_EVENT_CUSTOM29:
            sprintf(szLan, "MINOR_EVENT_CUSTOM29");
            break;
        case MINOR_EVENT_CUSTOM30:
            sprintf(szLan, "MINOR_EVENT_CUSTOM30");
            break;
        case MINOR_EVENT_CUSTOM31:
            sprintf(szLan, "MINOR_EVENT_CUSTOM31");
            break;
        case MINOR_EVENT_CUSTOM32:
            sprintf(szLan, "MINOR_EVENT_CUSTOM32");
            break;
        case MINOR_EVENT_CUSTOM33:
            sprintf(szLan, "MINOR_EVENT_CUSTOM33");
            break;
        case MINOR_EVENT_CUSTOM34:
            sprintf(szLan, "MINOR_EVENT_CUSTOM34");
            break;
        case MINOR_EVENT_CUSTOM35:
            sprintf(szLan, "MINOR_EVENT_CUSTOM35");
            break;
        case MINOR_EVENT_CUSTOM36:
            sprintf(szLan, "MINOR_EVENT_CUSTOM36");
            break;
        case MINOR_EVENT_CUSTOM37:
            sprintf(szLan, "MINOR_EVENT_CUSTOM37");
            break;
        case MINOR_EVENT_CUSTOM38:
            sprintf(szLan, "MINOR_EVENT_CUSTOM38");
            break;
        case MINOR_EVENT_CUSTOM39:
            sprintf(szLan, "MINOR_EVENT_CUSTOM39");
            break;
        case MINOR_EVENT_CUSTOM40:
            sprintf(szLan, "MINOR_EVENT_CUSTOM40");
            break;
        case MINOR_EVENT_CUSTOM41:
            sprintf(szLan, "MINOR_EVENT_CUSTOM41");
            break;
        case MINOR_EVENT_CUSTOM42:
            sprintf(szLan, "MINOR_EVENT_CUSTOM42");
            break;
        case MINOR_EVENT_CUSTOM43:
            sprintf(szLan, "MINOR_EVENT_CUSTOM43");
            break;
        case MINOR_EVENT_CUSTOM44:
            sprintf(szLan, "MINOR_EVENT_CUSTOM44");
            break;
        case MINOR_EVENT_CUSTOM45:
            sprintf(szLan, "MINOR_EVENT_CUSTOM45");
            break;
        case MINOR_EVENT_CUSTOM46:
            sprintf(szLan, "MINOR_EVENT_CUSTOM46");
            break;
        case MINOR_EVENT_CUSTOM47:
            sprintf(szLan, "MINOR_EVENT_CUSTOM47");
            break;
        case MINOR_EVENT_CUSTOM48:
            sprintf(szLan, "MINOR_EVENT_CUSTOM48");
            break;
        case MINOR_EVENT_CUSTOM49:
            sprintf(szLan, "MINOR_EVENT_CUSTOM49");
            break;
        case MINOR_EVENT_CUSTOM50:
            sprintf(szLan, "MINOR_EVENT_CUSTOM50");
            break;
        case MINOR_EVENT_CUSTOM51:
            sprintf(szLan, "MINOR_EVENT_CUSTOM51");
            break;
        case MINOR_EVENT_CUSTOM52:
            sprintf(szLan, "MINOR_EVENT_CUSTOM52");
            break;
        case MINOR_EVENT_CUSTOM53:
            sprintf(szLan, "MINOR_EVENT_CUSTOM53");
            break;
        case MINOR_EVENT_CUSTOM54:
            sprintf(szLan, "MINOR_EVENT_CUSTOM54");
            break;
        case MINOR_EVENT_CUSTOM55:
            sprintf(szLan, "MINOR_EVENT_CUSTOM55");
            break;
        case MINOR_EVENT_CUSTOM56:
            sprintf(szLan, "MINOR_EVENT_CUSTOM56");
            break;
        case MINOR_EVENT_CUSTOM57:
            sprintf(szLan, "MINOR_EVENT_CUSTOM57");
            break;
        case MINOR_EVENT_CUSTOM58:
            sprintf(szLan, "MINOR_EVENT_CUSTOM58");
            break;
        case MINOR_EVENT_CUSTOM59:
            sprintf(szLan, "MINOR_EVENT_CUSTOM59");
            break;
        case MINOR_EVENT_CUSTOM60:
            sprintf(szLan, "MINOR_EVENT_CUSTOM60");
            break;
        case MINOR_EVENT_CUSTOM61:
            sprintf(szLan, "MINOR_EVENT_CUSTOM61");
            break;
        case MINOR_EVENT_CUSTOM62:
            sprintf(szLan, "MINOR_EVENT_CUSTOM62");
            break;
        case MINOR_EVENT_CUSTOM63:
            sprintf(szLan, "MINOR_EVENT_CUSTOM63");
            break;
        case MINOR_EVENT_CUSTOM64:
            sprintf(szLan, "MINOR_EVENT_CUSTOM64");
            break;
        default:
            sprintf(szLan, "Main Event unknow");    
    }
    szTemp = szLan; 
}




/*********************************************************
Function:	GetLogFileThread
Desc:		get log file thread
Input:		pParam, parameter pointer
Output:	
Return:	
**********************************************************/
UINT GetLogFileThread(LPVOID pParam)
{
    UNREFERENCED_PARAMETER(pParam);
    
    LONG bRet = -1;
	
	NET_DVR_LOG_MATRIX struFileInfoMatrix = {0};
	
    NET_DVR_LOG_V50 struFileInfo;

//	NET_DVR_LOG_V30 struFileInfo;
 //   NET_DVR_LOG struFileInfo = {0};
	
    CString csTmp;
    char szLan[128] = {0};
	char szNetUser[17] = {0};
	char szPanelUser[17] = {0};
    while (1) 
    {
		if (pLogSearch->m_bVideoPlatLog)
		{
			bRet = NET_DVR_FindNextLog_MATRIX(pLogSearch->m_lLogHandle, &struFileInfoMatrix);
			if (bRet == NET_DVR_FILE_SUCCESS)
			{
				csTmp.Format("%d", pLogSearch->m_lLogNum+1);
				pLogSearch->m_listDeviceLog.InsertItem(pLogSearch->m_lLogNum, csTmp,0);
				csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struFileInfoMatrix.strLogTime.dwYear, struFileInfoMatrix.strLogTime.dwMonth, struFileInfoMatrix.strLogTime.dwDay, \
					struFileInfoMatrix.strLogTime.dwHour,struFileInfoMatrix.strLogTime.dwMinute, struFileInfoMatrix.strLogTime.dwSecond);
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 1, csTmp);	
				switch(struFileInfoMatrix.dwMajorType)
				{
				case 1:
					g_StringLanType(szLan, "报警", "Alarm");
					csTmp.Format("%s",szLan);
					break;
				case 2:
					g_StringLanType(szLan, "异常", "Abnormal");
					csTmp.Format("%s",szLan);
					break;
				case 3:
					g_StringLanType(szLan, "操作", "Operation");
					csTmp.Format("%s",szLan);
					break;
				case 4:
					g_StringLanType(szLan, "附加信息", "Additional information");
					csTmp.Format("%s",szLan);
					break;
				default:
					g_StringLanType(szLan, "未知类型", "Unknown");
					csTmp.Format("%s",szLan);
					break;
				}
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 2, csTmp);
				memcpy(&struFileInfo, &struFileInfoMatrix, sizeof(struFileInfoMatrix)); 
				if (MAJOR_INFORMATION == struFileInfo.dwMajorType)
				{
					InfoMinorTypeMap(struFileInfo, csTmp);
				}
				else if(MAJOR_OPERATION == struFileInfo.dwMajorType)
				{
					OperationMinorTypeMap(struFileInfo, csTmp);
				}
				else if(MAJOR_ALARM == struFileInfo.dwMajorType)
				{
					AlarmMinorTypeMap(struFileInfo, csTmp);
				}
				else if(MAJOR_EXCEPTION == struFileInfo.dwMajorType)
				{
					ExceptionMinorTypeMap(struFileInfo, csTmp);
				}
				
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 3, csTmp);
				
				memset(szNetUser,0,17);
				memset(szPanelUser,0,17);
				memcpy(szNetUser, struFileInfoMatrix.sNetUser,MAX_NAMELEN);
				memcpy(szPanelUser, struFileInfoMatrix.sPanelUser, MAX_NAMELEN);
				sprintf(szLan, "[%s-%s]", szNetUser, szPanelUser);
				if (struFileInfoMatrix.dwChannel > 0)
				{
					sprintf(szLan, "%schan[%d]", szLan, struFileInfoMatrix.dwChannel);
				}
				
				if (struFileInfoMatrix.dwAlarmInPort != 0)
				{
					sprintf(szLan, "%sAlarmIn[%d]", szLan, struFileInfoMatrix.dwAlarmInPort);
				}
				
				if (struFileInfoMatrix.dwAlarmOutPort != 0)
				{
					sprintf(szLan, "%sAlarmOut[%d]", szLan, struFileInfoMatrix.dwAlarmOutPort);
				}
				
				if (pLogSearch->ValidIPv6(struFileInfoMatrix.struRemoteHostAddr.byIPv6))
				{
					csTmp.Format("%s-%s",struFileInfoMatrix.struRemoteHostAddr.byIPv6, szLan);
				}
				else
				{
					csTmp.Format("%s-%s",struFileInfoMatrix.struRemoteHostAddr.sIpV4, szLan);
				}
				
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 4, csTmp);
				
				if (struFileInfoMatrix.dwInfoLen > 0)
				{
					csTmp.Format("%s",struFileInfoMatrix.sInfo);
				}
				else
				{
					csTmp.Format("");
				}
				
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 5, csTmp);
				
				pLogSearch->m_lLogNum++;
			}
			else
			{
				if (bRet == NET_DVR_ISFINDING)
				{
					pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
					pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("日志搜索中......");
					Sleep(5);
					continue;
				}
				if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
				{
					g_StringLanType(szLan, "搜索日志", "Search Log");
					pLogSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
					pLogSearch->m_bSearch = FALSE;
					pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
					g_StringLanType(szLan, "搜索日志结束!", "Search log Ending");
					AfxMessageBox(szLan);
					break;
				}
				else
				{
					g_StringLanType(szLan, "搜索日志", "Search Log");
					pLogSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
					pLogSearch->m_bSearch = FALSE;
					g_StringLanType(szLan, "由于服务器忙,或网络故障,搜索日志异常终止!",\
						"Since the server is busy, or network failure, search the log abnormal termination");
					AfxMessageBox(szLan);
					break;
				}
			}
		}
		else
		{
            bRet = NET_DVR_FindNextLog_V50(pLogSearch->m_lLogHandle, &struFileInfo);
 			//bRet = NET_DVR_FindNextLog_V30(pLogSearch->m_lLogHandle, &struFileInfo);
 //           bRet = NET_DVR_FindNextLog(pLogSearch->m_lLogHandle, &struFileInfo);
			if (bRet == NET_DVR_FILE_SUCCESS)
			{
				csTmp.Format("%d", pLogSearch->m_lLogNum+1);
				pLogSearch->m_listDeviceLog.InsertItem(pLogSearch->m_lLogNum, csTmp,0);
                if (struFileInfo.struLogTime.cTimeDifferenceH != 0x7F && struFileInfo.struLogTime.cTimeDifferenceM != 0x7F)
                {
                    csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d %02d:%02d", struFileInfo.struLogTime.wYear, struFileInfo.struLogTime.byMonth, struFileInfo.struLogTime.byDay, \
                        struFileInfo.struLogTime.byHour, struFileInfo.struLogTime.byMinute, struFileInfo.struLogTime.bySecond,
                        struFileInfo.struLogTime.cTimeDifferenceH, struFileInfo.struLogTime.cTimeDifferenceM);
                }
                else
                {
                    csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struFileInfo.struLogTime.wYear, struFileInfo.struLogTime.byMonth, struFileInfo.struLogTime.byDay, \
                        struFileInfo.struLogTime.byHour, struFileInfo.struLogTime.byMinute, struFileInfo.struLogTime.bySecond);
                }
                
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 1, csTmp);	
				switch(struFileInfo.dwMajorType)
				{
				case 1:
					g_StringLanType(szLan, "报警", "Alarm");
					csTmp.Format("%s",szLan);
					break;
				case 2:
					g_StringLanType(szLan, "异常", "Abnormal");
					csTmp.Format("%s",szLan);
					break;
				case 3:
					g_StringLanType(szLan, "操作", "Operation");
					csTmp.Format("%s",szLan);
					break;
				case 4:
					g_StringLanType(szLan, "附加信息", "Additional information");
					csTmp.Format("%s",szLan);
					break;
				default:
					g_StringLanType(szLan, "未知类型", "Unknown");
					csTmp.Format("%s",szLan);
					break;
				}
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 2, csTmp);
				
				if (MAJOR_INFORMATION == struFileInfo.dwMajorType)
				{
					InfoMinorTypeMap(struFileInfo, csTmp);
				}
				else if(MAJOR_OPERATION == struFileInfo.dwMajorType)
				{
					OperationMinorTypeMap(struFileInfo, csTmp);
				}
				else if(MAJOR_ALARM == struFileInfo.dwMajorType)
				{
					AlarmMinorTypeMap(struFileInfo, csTmp);
				}
				else if(MAJOR_EXCEPTION == struFileInfo.dwMajorType)
				{
					ExceptionMinorTypeMap(struFileInfo, csTmp);
				}
				
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 3, csTmp);
				
				memset(szNetUser,0,17);
				memset(szPanelUser,0,17);
				memcpy(szNetUser, struFileInfo.sNetUser,MAX_NAMELEN);
				memcpy(szPanelUser, struFileInfo.sPanelUser, MAX_NAMELEN);
				memset(szLan, 0, 128);
				sprintf(szLan, "[%s-%s]", szNetUser, szPanelUser);
				if (struFileInfo.dwChannel > 0)
				{
					sprintf(szLan, "%schan[%d]", szLan, struFileInfo.dwChannel);
				}
				
				if (struFileInfo.dwAlarmInPort != 0)
				{
					sprintf(szLan, "%sAlarmIn[%d]", szLan, struFileInfo.dwAlarmInPort);
				}
				
				if (struFileInfo.dwAlarmOutPort != 0)
				{
					sprintf(szLan, "%sAlarmOut[%d]", szLan, struFileInfo.dwAlarmOutPort);
				}
				
// 				if (pLogSearch->ValidIPv6(struFileInfo.struRemoteHostAddr.byIPv6))
// 				{
// 					csTmp.Format("%s-%s",struFileInfo.struRemoteHostAddr.byIPv6, szLan);
// 				}
// 				else
// 				{
// 					csTmp.Format("%s-%s",struFileInfo.struRemoteHostAddr.sIpV4, szLan);
// 				}

				//csTmp.Format("%s-%s",struFileInfo.struRemoteHostAddr.sIpV4, szLan);
                CString iptemp = "";
                iptemp.Format("%s", struFileInfo.struRemoteHostAddr.sIpV4);
                pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 4, iptemp);
				
                if (struFileInfo.dwInfoLen > 0)
                {
                    csTmp.Format("%s", struFileInfo.sInfo);
                }
                else
                {
                    csTmp.Format("");
                }
				
				pLogSearch->m_listDeviceLog.SetItemText(pLogSearch->m_lLogNum, 5, csTmp);
				
				pLogSearch->m_lLogNum++;
			}
			else
			{
				if (bRet == NET_DVR_ISFINDING)
				{
					pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
					pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("日志搜索中......");
					Sleep(5);
					continue;
				}
				if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
				{
					g_StringLanType(szLan, "搜索日志", "Search Log");
					pLogSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
					pLogSearch->m_bSearch = FALSE;
					pLogSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
					g_StringLanType(szLan, "搜索日志结束!", "Search log Ending");
					AfxMessageBox(szLan);
					break;
				}
				else
				{
					g_StringLanType(szLan, "搜索日志", "Search Log");
					pLogSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
					pLogSearch->m_bSearch = FALSE;
					g_StringLanType(szLan, "由于服务器忙,或网络故障,搜索日志异常终止!",\
						"Since the server is busy, or network failure, search the log abnormal termination");
					AfxMessageBox(szLan);
					break;
				}
			}
		}
	}
    CloseHandle(pLogSearch->m_hFileThread);
    pLogSearch->m_hFileThread = NULL;
    NET_DVR_FindLogClose_V30(pLogSearch->m_lLogHandle);
    return 0;
}

/*********************************************************
Function:	CDlgLogSearch
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgLogSearch, CDialog)
CDlgLogSearch::CDlgLogSearch(CWnd* pParent /*=NULL*/)
: CDialog(CDlgLogSearch::IDD, pParent)
, m_ctTimeStart(0)
, m_ctDateStart(0)
, m_ctDateStop(0)
, m_ctTimeStop(0)
, m_iDeviceIndex(-1)
, m_lLoginID(-1)
, m_hFileThread(NULL)
, m_iMode(0)
, m_iMajType(0)
, m_iMinType(0)
, m_bSearch(FALSE)
, m_lLogHandle(-1)
, m_lLogNum(0)
, m_bChkSmart(FALSE)
{
}
/*********************************************************
Function:	~CDlgLogSearch
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgLogSearch::~CDlgLogSearch()
{
    if (m_hFileThread != NULL)
    {
        CloseHandle(m_hFileThread);
        m_hFileThread = NULL;
    }
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgLogSearch::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLogSearch)
	DDX_Control(pDX, IDC_COMBO_SEQUENCE, m_comboSequence);
    DDX_Control(pDX, IDC_COMBO_MODE, m_comboMode);
    DDX_Control(pDX, IDC_COMBO_MAJOR_TYPE, m_comboMajorType);
    DDX_Control(pDX, IDC_COMBO_MINOR_TYPE, m_comboMinorType);
    DDX_DateTimeCtrl(pDX, IDC_TIME_LOG_START, m_ctTimeStart);
    DDX_DateTimeCtrl(pDX, IDC_DATE_LOG_START, m_ctDateStart);
    DDX_DateTimeCtrl(pDX, IDC_DATE_LOG_STOP, m_ctDateStop);
    DDX_DateTimeCtrl(pDX, IDC_TIME_LOG_STOP, m_ctTimeStop);
    DDX_Control(pDX, IDC_LIST_DEVICE_LOG, m_listDeviceLog);
    DDX_Check(pDX, IDC_CHK_SMART, m_bChkSmart);
	DDX_Check(pDX, IDC_CHECK_VIDEOPLAT, m_bVideoPlatLog);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgLogSearch, CDialog)
//{{AFX_MSG_MAP(CDlgLogSearch)	
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBnClickedBtnSearch)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_DEVICE_LOG, OnDblclkListDeviceLog)
ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
ON_CBN_SELCHANGE(IDC_COMBO_MINOR_TYPE, OnSelchangeComboMinorType)
	ON_BN_CLICKED(IDC_CHECK_VIDEOPLAT, OnCheckVideoplat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgLogSearch message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgLogSearch::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    CenterWindow();
    m_bSearch = FALSE;
    m_hFileThread = NULL;
    
    pLogSearch = this;
    char szLan[128] = {0};
    
	CString tmp;
    tmp.Format("全部日志");
    m_comboSequence.InsertString(0, tmp);
    tmp.Format("78K");
    m_comboSequence.InsertString(1, tmp);
    for (int i = 0; i < 80; i++)
    {
        tmp.Format("Slot:%d", i + 1);
        m_comboSequence.InsertString(i + 2, tmp);
    }

    m_listDeviceLog.SetExtendedStyle(m_listDeviceLog.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "No.");
    m_listDeviceLog.InsertColumn(0, szLan, LVCFMT_RIGHT, 60, -1);
    g_StringLanType(szLan, "日志时间", "Log Time");
    m_listDeviceLog.InsertColumn(1, szLan, LVCFMT_LEFT, 140, -1);
    g_StringLanType(szLan, "主类型", "Major Type");
    m_listDeviceLog.InsertColumn(2, szLan, LVCFMT_LEFT,80, -1);
    g_StringLanType(szLan, "次类型", "Minor Type");
    m_listDeviceLog.InsertColumn(3, szLan, LVCFMT_LEFT, 150, -1);
    g_StringLanType(szLan, "远程主机", "Remote Host");
    m_listDeviceLog.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "描述", "Description");
    m_listDeviceLog.InsertColumn(5, szLan, LVCFMT_LEFT, 251, -1);
    
    m_lLogNum = 0;
    m_lLogHandle = -1;	
    CTime ctCurTime = CTime::GetCurrentTime();
    CTime time(ctCurTime.GetYear(),ctCurTime.GetMonth(),ctCurTime.GetDay(),0,0,0);
    CTime time0(ctCurTime.GetYear(),ctCurTime.GetMonth(),ctCurTime.GetDay(),23,59,59);
    m_ctDateStart = time;
    m_ctTimeStart = time;
    m_ctDateStop = ctCurTime;
    m_ctTimeStop = time0;
    m_iMode = 2;
    m_iMajType = 0;
    m_iMinType = 0;
    m_comboMode.SetCurSel(m_iMode);
    m_comboMajorType.SetCurSel(m_iMajType);
    m_comboMinorType.SetCurSel(m_iMinType);
    AddMinorString();
    CheckInitParam();
    UpdateData(FALSE); 
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

inline BOOL CDlgLogSearch::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************
Function:	CheckInitParam
Desc:		check current device parameters, and initialize log search box corresponding parameters
Input:	
Output:	
Return:	TRUE,correct parameters; FALSE,wrong parameters;
**********************************************************/
BOOL CDlgLogSearch::CheckInitParam()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    EnableCtrl(TRUE);
    if (iDeviceIndex == -1)
    {
        m_lLoginID = -1;
        EnableCtrl(FALSE);
        return FALSE;
    }
    
    if (m_iDeviceIndex == iDeviceIndex)
    {
        return TRUE;
    }
    else
    {
        m_iDeviceIndex = iDeviceIndex;
        m_listDeviceLog.DeleteAllItems();
    }
    
    m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    
    if (m_lLoginID < 0)
    {
        EnableCtrl(FALSE);
        return FALSE;
    }
    GetDlgItem(IDC_STATIC_DEVNAME)->SetWindowText(g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName);
    GetDlgItem(IDC_STATIC_DEV_STATE_IP)->SetWindowText(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
    EnableWindow(TRUE);
    return TRUE;
}

/*********************************************************
Function:	AddMinorString
Desc:		add the minor type to combo
Input:	none
Output:	none
Return:	none
**********************************************************/
void CDlgLogSearch::AddMinorString()
{
    CString szTemp;
    int iSel = 0;
    m_comboMinorType.ResetContent();
    m_comboMinorType.AddString("All");
    m_comboMinorType.SetItemData(iSel, 0);
    m_comboMinorType.SetCurSel(0);
    
    szTemp.Format("ALARM_IN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_ALARM_IN);
    
    szTemp.Format("ALARM_OUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_ALARM_OUT);
    
    szTemp.Format("MOTDET_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_MOTDET_START);
    
    szTemp.Format("MOTDET_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_MOTDET_STOP);
    
    szTemp.Format("HIDE_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HIDE_ALARM_START);
    
    szTemp.Format("HIDE_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HIDE_ALARM_STOP);
    
    szTemp.Format("VCA_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_START);
    
    szTemp.Format("VCA_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_STOP);

	//场景变更侦测日志查询2013-07-17
	szTemp.Format("VCA_SECNECHANGE_DETECTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_SECNECHANGE_DETECTION);

	szTemp.Format("WIRELESS_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_WIRELESS_ALARM_START);
	
	szTemp.Format("WIRELESS_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_WIRELESS_ALARM_STOP);
	
	szTemp.Format("PIR_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PIR_ALARM_START);
	
	szTemp.Format("PIR_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PIR_ALARM_STOP);
	
	szTemp.Format("CALLHELP_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CALLHELP_ALARM_START);
	
	szTemp.Format("CALLHELP_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CALLHELP_ALARM_STOP);
    
	szTemp.Format("DETECTFACE_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DETECTFACE_ALARM_START);
	
	szTemp.Format("DETECTFACE_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DETECTFACE_ALARM_STOP);

	szTemp.Format("DETECTFACE_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DETECTFACE_ALARM_STOP);

#ifdef NET_DVR_SET_TRAVERSE_PLANE_DETECTION
	szTemp.Format("TRAVERSE_PLANE_DETECTION start");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_LINE_DETECTION_BEGIN );
	
	szTemp.Format("TRAVERSE_PLANE_DETECTION end");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_LINE_DETECTION_END);
#endif //NET_DVR_SET_TRAVERSE_PLANE_DETECTION
	
	szTemp.Format("field start");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_INTRUDE_BEGIN);
	
	szTemp.Format("field end");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_INTRUDE_END);
	
	szTemp.Format("Audio Exception");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_AUDIOINPUT);
	
	szTemp.Format("Voice ABNORMAL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_AUDIOABNORMAL);
	
	szTemp.Format("defous detection start");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_DEFOCUS_DETECTION_BEGIN);
	
	szTemp.Format("defous detection end");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_DEFOCUS_DETECTION_END);

	szTemp.Format("external alarm");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_EXT_ALARM);

	szTemp.Format("ALARM_VCA_LECTURE_DETECTION_BEGIN");//2014-03-21
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_VCA_LECTURE_DETECTION_BEGIN);
	
	szTemp.Format("ALARM_VCA_LECTURE_DETECTION_END");//2014-03-21
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_VCA_LECTURE_DETECTION_END);
	
	szTemp.Format("ALARM_AUDIOSTEEPDROP");//2014-03-21
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_VCA_ALARM_AUDIOSTEEPDROP);
	
	szTemp.Format("ALARM_VCA_ANSWER_DETECTION_BEGIN");//2014-03-21
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_VCA_ANSWER_DETECTION_BEGIN);
	
	szTemp.Format("ALARM_VCA_ANSWER_DETECTION_END");//2014-03-21
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_VCA_ANSWER_DETECTION_END);

    szTemp.Format("SMART_REGION_ENTRANCE_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_SMART_REGION_ENTRANCE_BEGIN);

    szTemp.Format("SMART_REGION_ENTRANCE_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_REGION_ENTRANCE_END);

    szTemp.Format("SMART_PEOPLE_GATHERING_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_PEOPLE_GATHERING_BEGIN);

    szTemp.Format("SMART_PEOPLE_GATHERING_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_PEOPLE_GATHERING_END);

    szTemp.Format("SMART_FAST_MOVING_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_FAST_MOVING_BEGIN);

    szTemp.Format("SMART_FAST_MOVING_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_FAST_MOVING_END);

    szTemp.Format("SMART_REGION_EXITING_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_REGION_EXITING_BEGIN);

    szTemp.Format("SMART_REGION_EXITING_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_REGION_EXITING_END);

    szTemp.Format("SMART_LOITERING_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_LOITERING_BEGIN);

    szTemp.Format("SMART_LOITERING_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_LOITERING_END);

    szTemp.Format("SMART_PARKING_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_PARKING_BEGIN);

    szTemp.Format("SMART_PARKING_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_PARKING_END);

    szTemp.Format("SMART_UNATTENDED_BAGGAGE_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_UNATTENDED_BAGGAGE_BEGIN);

    szTemp.Format("SMART_UNATTENDED_BAGGAGE_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_UNATTENDED_BAGGAGE_END);

    
    szTemp.Format("SMART_OBJECT_REMOVAL_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_OBJECT_REMOVAL_BEGIN);

    szTemp.Format("SMART_OBJECT_REMOVAL_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_OBJECT_REMOVAL_END);
    
    szTemp.Format("THERMAL_FIREDETECTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_FIREDETECTION);

	szTemp.Format("THERMAL_FIREDETECTION_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_FIREDETECTION_END);

    szTemp.Format("MINOR_SMART_VANDALPROOF_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_VANDALPROOF_BEGIN);
    
    szTemp.Format("MINOR_SMART_VANDALPROOF_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_VANDALPROOF_END);

    szTemp.Format("MINOR_FACESNAP_MATCH_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FACESNAP_MATCH_ALARM_START);

    szTemp.Format("MINOR_FACESNAP_MATCH_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FACESNAP_MATCH_ALARM_STOP);

    szTemp.Format("MINOR_WHITELIST_FACESNAP_MATCH_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_WHITELIST_FACESNAP_MATCH_ALARM_START);

    szTemp.Format("MINOR_WHITELIST_FACESNAP_MATCH_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_WHITELIST_FACESNAP_MATCH_ALARM_STOP);

    szTemp.Format("%s", "MINOR_POS_START_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_POS_START_ALARM);

    szTemp.Format("%s", "MINOR_POS_END_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_POS_END_ALARM);

    szTemp.Format("%s", "MINOR_SAFETY_HELMET_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SAFETY_HELMET_ALARM_START);

    szTemp.Format("%s", "MINOR_SAFETY_HELMET_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SAFETY_HELMET_ALARM_STOP);

    szTemp.Format("%s", "MINOR_HFPD_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HFPD_ALARM_START);

    szTemp.Format("%s", "MINOR_HFPD_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HFPD_ALARM_STOP);

    szTemp.Format("%s", "MINOR_MIXED_TARGET_ALARM_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_MIXED_TARGET_ALARM_START);

    szTemp.Format("%s", "MINOR_MIXED_TARGET_ALARM_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_MIXED_TARGET_ALARM_STOP);

    szTemp.Format("%s", "MINOR_VCA_GET_UP_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_GET_UP_ALARM_BEGIN);

    szTemp.Format("%s", "MINOR_VCA_GET_UP_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_GET_UP_ALARM_END);

    szTemp.Format("%s", "MINOR_VCA_ADV_REACH_HEIGHT_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ADV_REACH_HEIGHT_ALARM_BEGIN);

    szTemp.Format("%s", "MINOR_VCA_ADV_REACH_HEIGHT_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_ADV_REACH_HEIGHT_ALARM_END);

    szTemp.Format("%s", "MINOR_VCA_TOILET_TARRY_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_TOILET_TARRY_ALARM_BEGIN);

    szTemp.Format("%s", "MINOR_VCA_TOILET_TARRY_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_TOILET_TARRY_ALARM_END);

    szTemp.Format("%s", "MINOR_HUMAN_RECOGNITION_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HUMAN_RECOGNITION_ALARM_BEGIN);

    szTemp.Format("%s", "MINOR_HUMAN_RECOGNITION_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HUMAN_RECOGNITION_ALARM_END);

    szTemp.Format("%s", "MINOR_STUDENTS_STOODUP_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_STUDENTS_STOODUP_ALARM_BEGIN);

    szTemp.Format("%s", "MINOR_STUDENTS_STOODUP_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_STUDENTS_STOODUP_ALARM_END);

    szTemp.Format("%s", "MINOR_FRAMES_PEOPLE_COUNTING_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FRAMES_PEOPLE_COUNTING_ALARM);

    szTemp.Format("%s", "MINOR_FACE_SNAP_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FACE_SNAP_ALARM_BEGIN);

    szTemp.Format("%s", "MINOR_FACE_SNAP_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FACE_SNAP_ALARM_END);

    szTemp.Format("%s", "MINOR_FACE_THERMOMETRY_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FACE_THERMOMETRY_ALARM);

    szTemp.Format("MINOR_HEART_RATE_ABNORMAL_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HEART_RATE_ABNORMAL_BEGIN);

    szTemp.Format("MINOR_HEART_RATE_ABNORMAL_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HEART_RATE_ABNORMAL_END);

    szTemp.Format("MINOR_BLOOD_OXYGEN_ABNORMAL_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_BLOOD_OXYGEN_ABNORMAL_BEGIN);

    szTemp.Format("MINOR_BLOOD_OXYGEN_ABNORMAL_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_BLOOD_OXYGEN_ABNORMAL_END);

    szTemp.Format("MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN);

    szTemp.Format("MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SYSTOLIC_BLOOD_PRESSURE_ABNORMAL_END);

    szTemp.Format("MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_BEGIN);

    szTemp.Format("MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DIASTOLIC_BLOOD_PRESSURE_ABNORMAL_END);

    szTemp.Format("MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_BEGIN);

    szTemp.Format("MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_TEACHER_BEHAVIOR_DETECT_ALARM_END);

    szTemp.Format("MINOR_PERIMETER_CAPTURE_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PERIMETER_CAPTURE_ALARM_BEGIN);

    szTemp.Format("MINOR_PERIMETER_CAPTURE_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PERIMETER_CAPTURE_ALARM_END);

    szTemp.Format("MINOR_UNREGISTERED_STREET_VENDOR_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_UNREGISTERED_STREET_VENDOR_ALARM);

    szTemp.Format("MINOR_VCA_LEAVE_POSITION_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_LEAVE_POSITION_START);

    szTemp.Format("MINOR_VCA_LEAVE_POSITION_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_LEAVE_POSITION_STOP);

    szTemp.Format("MINOR_VCA_STOOODUP_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_STOOODUP_START);

    szTemp.Format("MINOR_VCA_STOOODUP_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_STOOODUP_STOP);

    szTemp.Format("MINOR_VCA_PEOPLENUM_CHANGE_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_PEOPLENUM_CHANGE_START);

    szTemp.Format("MINOR_VCA_PEOPLENUM_CHANGE_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_PEOPLENUM_CHANGE_STOP);

    szTemp.Format("MINOR_VCA_RUNNING_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_RUNNING_START);

    szTemp.Format("MINOR_VCA_RUNNING_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_RUNNING_STOP);

    szTemp.Format("MINOR_VCA_VIOLENT_MOTION_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_VIOLENT_MOTION_START);

    szTemp.Format("MINOR_VCA_VIOLENT_MOTION_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_VIOLENT_MOTION_STOP);

    szTemp.Format("MINOR_VCA_FAIL_DOWN_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_FAIL_DOWN_START);

    szTemp.Format("MINOR_VCA_FAIL_DOWN_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_FAIL_DOWN_STOP);

    szTemp.Format("MINOR_VCA_RETENTION_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_RETENTION_START);

    szTemp.Format("MINOR_VCA_RETENTION_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_RETENTION_STOP);

    szTemp.Format("MINOR_UNREGISTERED_STREET_VENDOR_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_UNREGISTERED_STREET_VENDOR_ALARM);

    szTemp.Format("MINOR_PERSON_QUEUE_TIME_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PERSON_QUEUE_TIME_ALARM_BEGIN);

    szTemp.Format("MINOR_PERSON_QUEUE_TIME_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PERSON_QUEUE_TIME_ALARM_END);

    szTemp.Format("MINOR_PERSON_QUEUE_COUNTING_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PERSON_QUEUE_COUNTING_ALARM_BEGIN);

    szTemp.Format("MINOR_PERSON_QUEUE_COUNTING_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PERSON_QUEUE_COUNTING_ALARM_END);

    szTemp.Format("MINOR_ACCESS_CONTROLLER_EVENT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_ACCESS_CONTROLLER_EVENT);

    szTemp.Format("MINOR_VIDEO_INTERCOM_EVENT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VIDEO_INTERCOM_EVENT);

    szTemp.Format("MINOR_GJD_EVENT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_GJD_EVENT);

    szTemp.Format("MINOR_LUMINITE_EVENT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LUMINITE_EVENT);

    szTemp.Format("MINOR_OPTEX_EVENT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_OPTEX_EVENT);

    szTemp.Format("MINOR_CAMERA_DETECTOR_EVENT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CAMERA_DETECTOR_EVENT);

    szTemp.Format("MINOR_REMOTE_CREATE_STORAGE_POOL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CREATE_STORAGE_POOL);

    szTemp.Format("MINOR_REMOTE_DEL_STORAGE_POOL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DEL_STORAGE_POOL);

    szTemp.Format("MINOR_REMOTE_CLOUD_ENABLE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CLOUD_ENABLE);

    szTemp.Format("MINOR_REMOTE_CLOUD_DISABLE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CLOUD_DISABLE);

    szTemp.Format("MINOR_REMOTE_CLOUD_MODIFY_PARAM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CLOUD_MODIFY_PARAM);

    szTemp.Format("MINOR_REMOTE_CLOUD_MODIFY_VOLUME");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CLOUD_MODIFY_VOLUME);


    //exception
    szTemp.Format("---Excp----------");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, 0);
    
	szTemp.Format("RAID_ERROR");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_RAID_ERROR);

    szTemp.Format("VI_LOST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VI_LOST);
    
    szTemp.Format("ILLEGAL_ACCESS");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_ILLEGAL_ACCESS);
    
    szTemp.Format("HD_FULL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HD_FULL);
    
    szTemp.Format("HD_ERROR");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HD_ERROR);
    
    szTemp.Format("REC_ERROR");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REC_ERROR);
    
    szTemp.Format("DCD_LOST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DCD_LOST);
    
    szTemp.Format("IPC_NO_LINK");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IPC_NO_LINK);
    
    szTemp.Format("IP_CONFLICT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IP_CONFLICT);
    
    szTemp.Format("NET_BROKEN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_NET_BROKEN);
    
    szTemp.Format("VI_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VI_EXCEPTION);

    szTemp.Format("IPC_IP_CONFLICT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IPC_IP_CONFLICT);

    szTemp.Format("SENCE_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SENCE_EXCEPTION);

	szTemp.Format("RESOLUTION_MISMATCH");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_RESOLUTION_MISMATCH);

	szTemp.Format("RECORD_OVERFLOW");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_RECORD_OVERFLOW);
    
    szTemp.Format("DIAL_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DIAL_EXCEPTION);
    
    szTemp.Format("POE_POWER_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_POE_POWER_EXCEPTION);

    szTemp.Format("MINOR_UPLOAD_DATA_CS_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_UPLOAD_DATA_CS_EXCEPTION);

	szTemp.Format("AI_LOST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_AI_LOST);

    szTemp.Format("MINOR_ACCESSORIES_PLATE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_ACCESSORIES_PLATE);

    szTemp.Format("MINOR_KMS_EXPAMSION_DISK_LOST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_KMS_EXPAMSION_DISK_LOST);

    szTemp.Format("MINOR_ABNORMAL_PORT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_ABNORMAL_PORT);

    szTemp.Format("MINOR_CAMERA_ANGLE_ANOMALY");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CAMERA_ANGLE_ANOMALY);

    szTemp.Format("MINOR_DATA_DISK_ERROE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DATA_DISK_ERROE);

    szTemp.Format("MINOR_INTELLIGENT_SYSTEM_RUNNING_ERROR");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_INTELLIGENT_SYSTEM_RUNNING_ERROR);

    szTemp.Format("MINOR_FACESNAP_RESOLUTION_OVERFLOW");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FACESNAP_RESOLUTION_OVERFLOW);

    szTemp.Format("MINOR_SMD_RESOLUTION_OVERFLOW");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMD_RESOLUTION_OVERFLOW);

    szTemp.Format("MINOR_AUDIO_LOSS_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_AUDIO_LOSS_EXCEPTION);

    szTemp.Format("MINOR_SAFETY_HELMET_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SAFETY_HELMET_EXCEPTION);

    szTemp.Format("MINOR_VCA_PIC_LENGTH_OVERFLOW");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VCA_PIC_LENGTH_OVERFLOW);

    szTemp.Format("MINOR_FACE_MODEL_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_FACE_MODEL_EXCEPTION);

    szTemp.Format("MINOR_CLUSTER_DEVICE_OFFLINE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_DEVICE_OFFLINE);

    szTemp.Format("MINOR_CLUSTER_CONFIG_FAILED");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_CONFIG_FAILED);

    szTemp.Format("MINOR_CLUSTER_DISASTER_TOLERANCE_EXCEPT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_DISASTER_TOLERANCE_EXCEPT);

    szTemp.Format("MINOR_CLUSTER_STORFULL_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_STORFULL_EXCEPTION);

    szTemp.Format("MINOR_CLUSTER_VERSION_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_VERSION_EXCEPTION);

    szTemp.Format("MINOR_CLUSTER_OFFLINENODE_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_OFFLINENODE_EXCEPTION);

    szTemp.Format("MINOR_CLUSTER_RECORDCYCLE_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_RECORDCYCLE_EXCEPTION);

    szTemp.Format("MINOR_CLUSTER_IPCTRANSFER_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_IPCTRANSFER_EXCEPTION);

    szTemp.Format("MINOR_CLUSTER_IPCONFLICT_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_CLUSTER_IPCONFLICT_EXCEPTION);

    szTemp.Format("MINOR_GET_SUB_STREAM_FAILURE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_GET_SUB_STREAM_FAILURE);

    szTemp.Format("MINOR_HDD_SHM_DETECT_EXCEPTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HDD_SHM_DETECT_EXCEPTION);

    //operation
    szTemp.Format("%s", "---Oper----------");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, 0);
    szTemp.Format("START_DVR");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_START_DVR);
    
    szTemp.Format("STOP_DVR");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_STOP_DVR);
    
    szTemp.Format("STOP_ABNORMAL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_STOP_ABNORMAL);
    
    szTemp.Format("REBOOT_DVR");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REBOOT_DVR);
    
    szTemp.Format("LOCAL_LOGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_LOGIN);
    
    szTemp.Format("%s", "LOCAL_LOGOUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_LOGOUT);
    
    szTemp.Format("LOCAL_CFG_PARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFG_PARM);
    
    szTemp.Format("%s","LOCAL_PLAYBYFILE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PLAYBYFILE);
    
    szTemp.Format("%s", "LOCAL_PLAYBYTIME");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PLAYBYTIME);
    
    szTemp.Format("%s", "LOCAL_START_REC");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_START_REC);
    
    szTemp.Format("%s", "LOCAL_STOP_REC");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_STOP_REC);
    
    szTemp.Format("%s", "LOCAL_PTZCTRL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PTZCTRL);
    
    szTemp.Format("%s", "LOCAL_PREVIEW");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PREVIEW);
    
    szTemp.Format("%s", "LOCAL_MODIFY_TIME");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MODIFY_TIME);
    
    szTemp.Format("%s", "LOCAL_UPGRADE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_UPGRADE);
    
    szTemp.Format("%s", "LOCAL_COPYFILE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COPYFILE);
    
    
    szTemp.Format("%s", "LOCAL_LOCKFILE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_LOCKFILE);
    
    szTemp.Format("%s", "LOCAL_UNLOCKFILE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_UNLOCKFILE);
    
    szTemp.Format("%s", "LOCAL_FORMAT_HDD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FORMAT_HDD);
    
    szTemp.Format("%s", "LOCAL_CFGFILE_OUTPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFGFILE_OUTPUT);
    
    szTemp.Format("%s", "LOCAL_CFGFILE_INPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFGFILE_INPUT);
    
    szTemp.Format("%s", "LOCAL_DVR_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DVR_ALARM);
    szTemp.Format("%s", "IPC_ADD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IPC_ADD);
    
    szTemp.Format("%s", "IPC_DEL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IPC_DEL);
    
    szTemp.Format("%s", "IPC_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IPC_SET);
    
    m_comboMinorType.AddString("LOCAL_START_BACKUP");
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_START_BACKUP);
    m_comboMinorType.AddString("LOCAL_STOP_BACKUP");
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_STOP_BACKUP);
    m_comboMinorType.AddString("LOCAL_COPYFILE_START_TIME");
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COPYFILE_START_TIME);
    m_comboMinorType.AddString("LOCAL_COPYFILE_END_TIME");
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COPYFILE_END_TIME);
	//m_comboMinorType.AddString("LOCAL_COPYFILE_END_TIME");
    
	szTemp.Format("%s", "LOCAL_OPERATE_LOCK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_OPERATE_LOCK );
	
	szTemp.Format("%s", "LOCAL_OPERATE_UNLOCK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_OPERATE_UNLOCK );	
    
	szTemp.Format("%s", "LOCAL_TAG_OPT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_TAG_OPT);
	
	szTemp.Format("%s", "LOCAL_VOUT_SWITCH");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_VOUT_SWITCH);
    
	szTemp.Format("%s", "STREAM_CABAC");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_STREAM_CABAC);
	
	szTemp.Format("%s", "LOCAL_LOAD_HDISK");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_LOAD_HDISK);
	
	szTemp.Format("%s", "LOCAL_DELETE_HDISK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DELETE_HDISK);

	szTemp.Format("%s", "LOCAL_MAIN_AUXILIARY_PORT_SWITCH");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MAIN_AUXILIARY_PORT_SWITCH);

	szTemp.Format("%s", "LOCAL_HARD_DISK_CHECK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_HARD_DISK_CHECK);

	szTemp.Format("%s", "LOCAL_PIN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PIN);

	szTemp.Format("%s", "LOCAL_DIAL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DIAL);

	//ITS的操作日志 bg
	szTemp.Format("%s", "LOCAL_ADD_CAR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_ADD_CAR_INFO);

	szTemp.Format("%s", "LOCAL_MOD_CAR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MOD_CAR_INFO);

	szTemp.Format("%s", "LOCAL_DEL_CAR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DEL_CAR_INFO);

	szTemp.Format("%s", "LOCAL_FIND_CAR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_CAR_INFO);

	szTemp.Format("%s", "LOCAL_ADD_MONITOR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_ADD_MONITOR_INFO);

	szTemp.Format("%s", "LOCAL_MOD_MONITOR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MOD_MONITOR_INFO);

	szTemp.Format("%s", "LOCAL_DEL_MONITOR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DEL_MONITOR_INFO);

	szTemp.Format("%s", "LOCAL_FIND_MONITOR_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_MONITOR_INFO);

	szTemp.Format("%s", "LOCAL_FIND_NORMAL_PASS_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_NORMAL_PASS_INFO);

	szTemp.Format("%s", "LOCAL_FIND_ABNORMAL_PASS_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_ABNORMAL_PASS_INFO);

	szTemp.Format("%s", "LOCAL_FIND_PEDESTRIAN_PASS_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_PEDESTRIAN_PASS_INFO);

	szTemp.Format("%s", "LOCAL_PIC_PREVIEW");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PIC_PREVIEW);

	szTemp.Format("%s", "LOCAL_SET_GATE_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SET_GATE_PARM_CFG);

	szTemp.Format("%s", "LOCAL_GET_GATE_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_GET_GATE_PARM_CFG);

	szTemp.Format("%s", "LOCAL_SET_DATAUPLOAD_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SET_DATAUPLOAD_PARM_CFG);

	szTemp.Format("%s", "LOCAL_GET_DATAUPLOAD_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_GET_DATAUPLOAD_PARM_CFG);

	//2013-11-19
	szTemp.Format("%s", "LOCAL_DEVICE_CONTROL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DEVICE_CONTROL);

	szTemp.Format("%s", "LOCAL_ADD_EXTERNAL_DEVICE_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_ADD_EXTERNAL_DEVICE_INFO);

	szTemp.Format("%s", "LOCAL_MOD_EXTERNAL_DEVICE_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MOD_EXTERNAL_DEVICE_INFO);

	szTemp.Format("%s", "LOCAL_DEL_EXTERNAL_DEVICE_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DEL_EXTERNAL_DEVICE_INFO);

	szTemp.Format("%s", "LOCAL_FIND_EXTERNAL_DEVICE_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_EXTERNAL_DEVICE_INFO);

	szTemp.Format("%s", "LOCAL_ADD_CHARGE_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_ADD_CHARGE_RULE);

	szTemp.Format("%s", "LOCAL_MOD_CHARGE_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MOD_CHARGE_RULE);

	szTemp.Format("%s", "LOCAL_DEL_CHARGE_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DEL_CHARGE_RULE);

	szTemp.Format("%s", "LOCAL_FIND_CHARGE_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_CHARGE_RULE);

	szTemp.Format("%s", "LOCAL_COUNT_NORMAL_CURRENTINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COUNT_NORMAL_CURRENTINFO);

	szTemp.Format("%s", "LOCAL_EXPORT_NORMAL_CURRENTINFO_REPORT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_EXPORT_NORMAL_CURRENTINFO_REPORT);

	szTemp.Format("%s", "LOCAL_COUNT_ABNORMAL_CURRENTINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COUNT_ABNORMAL_CURRENTINFO);

	szTemp.Format("%s", "LOCAL_EXPORT_ABNORMAL_CURRENTINFO_REPORT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_EXPORT_ABNORMAL_CURRENTINFO_REPORT);

	szTemp.Format("%s", "LOCAL_COUNT_PEDESTRIAN_CURRENTINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COUNT_PEDESTRIAN_CURRENTINFO);

	szTemp.Format("%s", "LOCAL_EXPORT_PEDESTRIAN_CURRENTINFO_REPORT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_EXPORT_PEDESTRIAN_CURRENTINFO_REPORT);

	szTemp.Format("%s", "LOCAL_FIND_CAR_CHARGEINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_CAR_CHARGEINFO);

	szTemp.Format("%s", "LOCAL_COUNT_CAR_CHARGEINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_COUNT_CAR_CHARGEINFO);

	szTemp.Format("%s", "LOCAL_EXPORT_CAR_CHARGEINFO_REPORT");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_EXPORT_CAR_CHARGEINFO_REPORT);
	
	szTemp.Format("%s", "LOCAL_FIND_SHIFTINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_SHIFTINFO);

	szTemp.Format("%s", "LOCAL_FIND_CARDINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_CARDINFO);

	szTemp.Format("%s", "LOCAL_ADD_RELIEF_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_ADD_RELIEF_RULE);

	szTemp.Format("%s", "LOCAL_MOD_RELIEF_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MOD_RELIEF_RULE);

	szTemp.Format("%s", "LOCAL_DEL_RELIEF_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DEL_RELIEF_RULE);
	
	szTemp.Format("%s", "LOCAL_FIND_RELIEF_RULE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FIND_RELIEF_RULE);

	szTemp.Format("%s", "LOCAL_GET_ENDETCFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_GET_ENDETCFG);

	szTemp.Format("%s", "LOCAL_SET_ENDETCFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SET_ENDETCFG);

	szTemp.Format("%s", "LOCAL_SET_ENDEV_ISSUEDDATA");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SET_ENDEV_ISSUEDDATA);

	szTemp.Format("%s", "LOCAL_DEL_ENDEV_ISSUEDDATA");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DEL_ENDEV_ISSUEDDATA);
	//ITS的操作日志 ed
    //wireless Operation start
    szTemp.Format("%s", "LOCAL_SMS_SEND");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SMS_SEND);

    szTemp.Format("%s", "ALARM_SMS_SEND");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_ALARM_SMS_SEND);

    szTemp.Format("%s", "SMS_RECV");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_SMS_RECV);

    szTemp.Format("%s", "LOCAL_SMS_SEARCH");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SMS_SEARCH);

    szTemp.Format("%s", "LOCAL_SMS_READ");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SMS_READ);

    szTemp.Format("%s", "LOCAL_WHITELIST_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_WHITELIST_SET);

    szTemp.Format("%s", "LOCAL_DIAL_PARA_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DIAL_PARA_SET);

    szTemp.Format("%s", "LOCAL_DIAL_SCHEDULE_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DIAL_SCHEDULE_SET);

    szTemp.Format("%s", "PLAT_OPER");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_PLAT_OPER);

    szTemp.Format("%s", "LOCAL_SET_DEVICE_ACTIVE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_SET_DEVICE_ACTIVE);

    szTemp.Format("%s", "LOCAL_PARA_FACTORY_DEFAULT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_PARA_FACTORY_DEFAULT);

    szTemp.Format("%s", "LOCAL_RESTORE_CFG");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_RESTORE_CFG);
    //wireless Operation end
    ////remote 
    szTemp.Format("%s", "---Remote----------");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, 0);
    
    szTemp.Format("%s", "REMOTE_LOGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_LOGIN);
    
    szTemp.Format("%s", "REMOTE_LOGOUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_LOGOUT);
    
    szTemp.Format("%s", "REMOTE_START_REC");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_START_REC);
    
    szTemp.Format("%s","REMOTE_STOP_REC");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_STOP_REC);
    
    szTemp.Format("%s", "START_TRANS_CHAN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_START_TRANS_CHAN);
    
    szTemp.Format("%s","STOP_TRANS_CHAN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_STOP_TRANS_CHAN);
    
    szTemp.Format("REMOTE_GET_PARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_PARM);
    
    szTemp.Format("REMOTE_CFG_PARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFG_PARM);
    
    szTemp.Format("%s", "REMOTE_GET_STATUS");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_STATUS);
    
    szTemp.Format("%s", "REMOTE_ARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_ARM);
    
    szTemp.Format("%s", "REMOTE_DISARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DISARM);
    
    szTemp.Format("%s", "REMOTE_REBOOT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_REBOOT);
    
    szTemp.Format("%s", "START_VT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_START_VT);
    
    szTemp.Format("%s", "STOP_VT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_STOP_VT);
    
    szTemp.Format("%s", "REMOTE_UPGRADE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_UPGRADE);
    
    szTemp.Format("%s", "REMOTE_PLAYBYFILE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PLAYBYFILE);
    
    szTemp.Format("%s", "REMOTE_PLAYBYTIME");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PLAYBYTIME);
    
    szTemp.Format("%s", "REMOTE_PTZCTRL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PTZCTRL);
    
    szTemp.Format("%s", "REMOTE_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_STOP);
    
    
    szTemp.Format("%s", "REMOTE_LOCKFILE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_LOCKFILE);
    
    szTemp.Format("%s", "REMOTE_CFGFILE_OUTPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFGFILE_OUTPUT);
    
    
    szTemp.Format("%s", "REMOTE_CFGFILE_INTPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFGFILE_INTPUT);
    
    szTemp.Format("%s", "REMOTE_FORMAT_HDD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FORMAT_HDD);
    szTemp.Format("%s", "REMOTE_DVR_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DVR_ALARM);
    szTemp.Format("%s", "REMOTE_IPC_ADD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IPC_ADD);    
    
    szTemp.Format("%s", "REMOTE_IPC_DEL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IPC_DEL);
    
    szTemp.Format("%s", "REMOTE_IPC_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IPC_SET);
    
    szTemp.Format("%s", "REBOOT_VCA_LIB");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REBOOT_VCA_LIB);

    szTemp.Format("%s", "REMOTE_INQUEST_DEL_FILE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_INQUEST_DEL_FILE);

    szTemp.Format("%s", "LOCAL_UNLOAD_HDISK");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_UNLOAD_HDISK);

    szTemp.Format("%s", "LOCAL_AUDIO_MIX");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_AUDIO_MIX);

    szTemp.Format("%s", "REMOTE_AUDIO_MIX");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_AUDIO_MIX);

    szTemp.Format("%s", "LOCAL_TRIAL_PAUSE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_TRIAL_PAUSE);

    szTemp.Format("%s", "LOCAL_TRIAL_RESUME");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_TRIAL_RESUME);

    szTemp.Format("%s", "REMOTE_TRIAL_PAUSE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_TRIAL_PAUSE);

    szTemp.Format("%s", "REMOTE_TRIAL_RESUME");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_TRIAL_RESUME);

	szTemp.Format("%s", "MINOR_REMOTE_MODIFY_VERIFICATION_CODE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_MODIFY_VERIFICATION_CODE);

    szTemp.Format("%s", "MINOR_LOCAL_MAKECALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MAKECALL);

    szTemp.Format("%s", "MINOR_LOCAL_REJECTCALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_REJECTCALL);

    szTemp.Format("%s", "MINOR_LOCAL_ANSWERCALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_ANSWERCALL);

    szTemp.Format("%s", "MINOR_LOCAL_HANGUPCALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_HANGUPCALL);

    szTemp.Format("%s", "MINOR_REMOTE_MAKECALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_MAKECALL);

    szTemp.Format("%s", "MINOR_REMOTE_REJECTCALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_REJECTCALL);

    szTemp.Format("%s", "MINOR_REMOTE_ANSWERCALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_ANSWERCALL);

    szTemp.Format("%s", "MINOR_REMOTE_HANGUPCALL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_HANGUPCALL);

    szTemp.Format("%s", "LOCAL_DELETE_HDISK");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_DELETE_HDISK);

	szTemp.Format("%s", "LOCAL_MAIN_AUXILIARY_PORT_SWITCH");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_MAIN_AUXILIARY_PORT_SWITCH);
	
	szTemp.Format("%s", "LOCAL_HARD_DISK_CHECK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_HARD_DISK_CHECK);

	szTemp.Format("%s", "REMOTE_DELETE_HDISK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DELETE_HDISK);
	
	szTemp.Format("%s", "REMOTE_LOAD_HDISK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_LOAD_HDISK  );
	
	szTemp.Format("%s", "REMOTE_UNLOAD_HDISK");
    m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_UNLOAD_HDISK );

	szTemp.Format("%s", "SMS_CONTROL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_SMS_CONTROL);

	szTemp.Format("%s", "CALL_ONLINE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_CALL_ONLINE);

	szTemp.Format("%s", "REMOTE_PIN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PIN);
    
	//ITS操作日志类型 Remote bg
	szTemp.Format("%s", "REMOTE_DEVICE_CONTROL");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DEVICE_CONTROL);

	szTemp.Format("%s", "REMOTE_SET_GATE_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SET_GATE_PARM_CFG);

	szTemp.Format("%s", "REMOTE_GET_GATE_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_GATE_PARM_CFG);

	szTemp.Format("%s", "REMOTE_SET_DATAUPLOAD_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SET_DATAUPLOAD_PARM_CFG);

	szTemp.Format("%s", "REMOTE_GET_DATAUPLOAD_PARM_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_DATAUPLOAD_PARM_CFG);

	szTemp.Format("%s", "REMOTE_GET_BASE_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_BASE_INFO);

	szTemp.Format("%s", "REMOTE_GET_OVERLAP_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_OVERLAP_CFG);

	szTemp.Format("%s", "REMOTE_SET_OVERLAP_CFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SET_OVERLAP_CFG);

	szTemp.Format("%s", "REMOTE_GET_ROAD_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_ROAD_INFO);

	szTemp.Format("%s", "REMOTE_START_TRANSCHAN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_START_TRANSCHAN);

	szTemp.Format("%s", "REMOTE_GET_ECTWORKSTATE");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_ECTWORKSTATE);

	szTemp.Format("%s", "REMOTE_GET_ECTCHANINFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_ECTCHANINFO);

	//2013-11-19
	szTemp.Format("%s", "REMOTE_ADD_EXTERNAL_DEVICE_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_ADD_EXTERNAL_DEVICE_INFO);
	
	szTemp.Format("%s", "REMOTE_MOD_EXTERNAL_DEVICE_INFO");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_MOD_EXTERNAL_DEVICE_INFO);
	
	szTemp.Format("%s", "REMOTE_GET_ENDETCFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_GET_ENDETCFG);
	
	szTemp.Format("%s", "REMOTE_SET_ENDETCFG");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SET_ENDETCFG);
	
	szTemp.Format("%s", "REMOTE_ENDEV_ISSUEDDATA");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_ENDEV_ISSUEDDATA);
	
	szTemp.Format("%s", "REMOTE_DEL_ENDEV_ISSUEDDATA");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DEL_ENDEV_ISSUEDDATA);

	//日志类型（新增）2013-06-09
	szTemp.Format("%s", "REMOTE_ON_CTRL_LAMP");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_ON_CTRL_LAMP);
	
	szTemp.Format("%s", "REMOTE_OFF_CTRL_LAMP");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_OFF_CTRL_LAMP );
	//ITS操作日志类型 Remote ed
    //remote wireless Operation start
    szTemp.Format("%s", "REMOTE_SMS_SEND");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SMS_SEND );

    szTemp.Format("%s", "REMOTE_SMS_SEARCH");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SMS_SEARCH );

    szTemp.Format("%s", "REMOTE_SMS_READ");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SMS_READ );

    szTemp.Format("%s", "REMOTE_DIAL_DISCONN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DIAL_DISCONN );

    szTemp.Format("%s", "REMOTE_DIAL_CONNECT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DIAL_CONNECT );

    szTemp.Format("%s", "REMOTE_WHITELIST_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_WHITELIST_SET );

    szTemp.Format("%s", "REMOTE_DIAL_PARA_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DIAL_PARA_SET );

    szTemp.Format("%s", "REMOTE_DIAL_SCHEDULE_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_DIAL_SCHEDULE_SET  );

    szTemp.Format("%s", "REMOTE_SET_DEVICE_ACTIVE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_SET_DEVICE_ACTIVE );

    szTemp.Format("%s", "MINOR_REMOTE_CFG_POE_WORK_MODE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFG_POE_WORK_MODE);

    szTemp.Format("%s", "MINOR_LOCAL_CFG_POE_WORK_MODE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFG_POE_WORK_MODE);

    szTemp.Format("%s", "MINOR_REMOTE_CFG_FACE_CONTRAST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFG_FACE_CONTRAST);

    szTemp.Format("%s", "MINOR_LOCAL_CFG_FACE_CONTRAST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFG_FACE_CONTRAST);

    szTemp.Format("%s", "MINOR_REMOTE_CFG_WHITELIST_FACE_CONTRAST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_CFG_WHITELIST_FACE_CONTRAST);

    szTemp.Format("%s", "MINOR_LOCAL_CFG_WHITELIST_FACE_CONTRAST");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CFG_WHITELIST_FACE_CONTRAST);
    
    szTemp.Format("%s", "REMOTE_PARA_FACTORY_DEFAULT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_PARA_FACTORY_DEFAULT  );

    szTemp.Format("%s", "REMOTE_RESTORE_CFG");
    m_comboMinorType.AddString(szTemp);
    iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_RESTORE_CFG);

    szTemp.Format("%s", "MINOR_LOCAL_CHECK_TIME");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_CHECK_TIME);

    //remote wireless Operation end

    //information
    szTemp.Format("%s", "--INFOR-------------");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, 0);
    
    szTemp.Format("%s", "HDD_INFO");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_HDD_INFO);
    
    szTemp.Format("%s", "SMART_INFO");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_SMART_INFO);
    
    szTemp.Format("%s", "REC_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REC_START);
    
    szTemp.Format("%s", "REC_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REC_STOP);
    
    szTemp.Format("%s", "REC_OVERDUE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REC_OVERDUE);
    
    szTemp.Format("%s", "LINK_START");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LINK_START);
    
    szTemp.Format("%s", "LINK_STOP");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LINK_STOP);
    
    szTemp.Format("%s", "NET_DISK_INFO");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_NET_DISK_INFO);

    szTemp.Format("%s", "RAID_INFO");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_RAID_INFO);

	szTemp.Format("%s", "RUN_STATUS_INFO ");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_RUN_STATUS_INFO );

    szTemp.Format("%s", "PLAT_INFO");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_PLAT_INFO );

    szTemp.Format("%s", "DIAL_STAT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_DIAL_STAT );
    
	szTemp.Format("%s", "UNLOCK_RECORD ");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_UNLOCK_RECORD);
	
	szTemp.Format("%s", "ZONE_ALARM");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_VIS_ALARM);
	
	szTemp.Format("%s", "MINOR_TALK_RECORD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_TALK_RECORD );

    szTemp.Format("%s", "MINOR_ACCESSORIES_MESSAGE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_ACCESSORIES_MESSAGE);

    szTemp.Format("%s", "MINOR_THERMAL_SHIPSDETECTION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_SHIPSDETECTION);

    szTemp.Format("%s", "MINOR_KMS_EXPAMSION_DISK_INSERT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_KMS_EXPAMSION_DISK_INSERT);

    szTemp.Format("%s", "MINOR_IPC_CONNECT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IPC_CONNECT);

    szTemp.Format("%s", "MINOR_INTELLIGENT_BOARD_STATUS");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_INTELLIGENT_BOARD_STATUS);

    szTemp.Format("%s", "MINOR_IPC_CONNECT_STATUS");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_IPC_CONNECT_STATUS);

    szTemp.Format("%s", "MINOR_AUTO_TIMING");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_AUTO_TIMING);

    szTemp.Format("%s", "MINOR_EZVIZ_OPERATION");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_EZVIZ_OPERATION);
    szTemp.Format("%s", "MINOR_THERMAL_THERMOMETRY_EARLYWARNING_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_THERMOMETRY_EARLYWARNING_BEGIN);

    szTemp.Format("%s", "MINOR_THERMAL_THERMOMETRY_EARLYWARNING_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_THERMOMETRY_EARLYWARNING_END);

    szTemp.Format("%s", "MINOR_THERMAL_THERMOMETRY_ALARM_BEGIN");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_THERMOMETRY_ALARM_BEGIN);

    szTemp.Format("%s", "MINOR_THERMAL_THERMOMETRY_ALARM_END");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_THERMOMETRY_ALARM_END);

	szTemp.Format("%s", "MINOR_THERMAL_THERMOMETRY_DIFF_ALARM_BEGIN");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_THERMOMETRY_DIFF_ALARM_BEGIN);

	szTemp.Format("%s", "MINOR_THERMAL_THERMOMETRY_DIFF_ALARM_END");
	m_comboMinorType.AddString(szTemp);
	iSel++;
	m_comboMinorType.SetItemData(iSel, MINOR_THERMAL_THERMOMETRY_DIFF_ALARM_END);

    szTemp.Format("%s", "MINOR_LOCAL_RESET_LOGIN_PASSWORD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_RESET_LOGIN_PASSWORD);

    szTemp.Format("%s", "MINOR_REMOTE_RESET_LOGIN_PASSWORD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_RESET_LOGIN_PASSWORD);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_BASE_CREATE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_BASE_CREATE);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_BASE_MODIFY");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_BASE_MODIFY);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_BASE_DELETE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_BASE_DELETE);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_DATA_APPEND");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_DATA_APPEND);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_DATA_SEARCH");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_DATA_SEARCH);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_DATA_ANALYSIS");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_DATA_ANALYSIS);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_DATA_EDIT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_DATA_EDIT);

    szTemp.Format("%s", "MINOR_REMOTE_FACE_DATA_DELET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_FACE_DATA_DELET);

    szTemp.Format("%s", "MINOR_REMOTE_VCA_ANALYSIS_CFG");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_VCA_ANALYSIS_CFG);

    szTemp.Format("%s", "MINOR_LOCAL_FACE_BASE_IMPORT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_BASE_IMPORT);

    szTemp.Format("%s", "MINOR_LOCAL_FACE_BASE_EXPORT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_BASE_EXPORT);

    szTemp.Format("%s", "MINOR_LOCAL_FACE_BASE_CREATE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_BASE_CREATE);

    szTemp.Format("%s", "MINOR_LOCAL_FACE_BASE_MODIFY");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_BASE_MODIFY);


    szTemp.Format("%s", "MINOR_LOCAL_FACE_BASE_DELETE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_BASE_DELETE);


    szTemp.Format("%s", "MINOR_LOCAL_FACE_DATA_APPEND");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_DATA_APPEND);


    szTemp.Format("%s", "MINOR_LOCAL_FACE_DATA_SEARCH");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_DATA_SEARCH);

    szTemp.Format("%s", "MINOR_LOCAL_FACE_DATA_ANALYSIS");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_DATA_ANALYSIS);

    szTemp.Format("%s", "MINOR_LOCAL_FACE_DATA_EDIT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_DATA_EDIT);

    szTemp.Format("%s", "MINOR_LOCAL_FACE_DATA_DELETE");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_FACE_DATA_DELETE);

    szTemp.Format("%s", "MINOR_LOCAL_VCA_ANALYSIS_CFG");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_VCA_ANALYSIS_CFG);

    szTemp.Format("%s", "MINOR_REMOTE_HFPD_CFG");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_HFPD_CFG);

    szTemp.Format("%s", "MINOR_REMOTE_IOTCFGFILE_INPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IOTCFGFILE_INPUT);

    szTemp.Format("%s", "MINOR_REMOTE_IOTCFGFILE_OUTPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IOTCFGFILE_OUTPUT);

    szTemp.Format("%s", "MINOR_LOCAL_IOT_ADD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_IOT_ADD);

    szTemp.Format("%s", "MINOR_REMOTE_IOT_ADD");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IOT_ADD);

    szTemp.Format("%s", "MINOR_LOCAL_IOT_DEL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_IOT_DEL);

    szTemp.Format("%s", "MINOR_REMOTE_IOT_DEL");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IOT_DEL);

    szTemp.Format("%s", "MINOR_LOCAL_IOT_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_IOT_SET);

    szTemp.Format("%s", "MINOR_REMOTE_IOT_SET");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_REMOTE_IOT_SET);

    szTemp.Format("%s", "MINOR_LOCAL_IOTCFGFILE_INPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_IOTCFGFILE_INPUT);

    szTemp.Format("%s", "MINOR_LOCAL_IOTCFGFILE_OUTPUT");
    m_comboMinorType.AddString(szTemp);
    iSel++;
    m_comboMinorType.SetItemData(iSel, MINOR_LOCAL_IOTCFGFILE_OUTPUT);
}
/*********************************************************
Function:	OnBnClickedBtnSearch
Desc:		search log
Input:	
Output:	
Return:	
**********************************************************/
void CDlgLogSearch::OnBnClickedBtnSearch()
{
    UpdateData(TRUE);
    char szLan[128] = {0};
    if (!m_bSearch)
    {
        

        NET_DVR_FIND_LOG_COND struFindLogCond = { 0 };
        m_iMode = m_comboMode.GetCurSel();
        m_iMajType = m_comboMajorType.GetCurSel();
        m_iMinType = m_comboMinorType.GetItemData(m_comboMinorType.GetCurSel());
        
        struFindLogCond.dwMainType = m_iMajType;
        struFindLogCond.dwSubType = m_iMinType;
        struFindLogCond.dwSelectMode = m_iMode;
        struFindLogCond.bOnlySmart = m_bChkSmart;
        

        struFindLogCond.struStartTime.wYear = (WORD)m_ctDateStart.GetYear();
        struFindLogCond.struStartTime.byMonth = (char)m_ctDateStart.GetMonth();
        struFindLogCond.struStartTime.byDay = (char)m_ctDateStart.GetDay();
        struFindLogCond.struStartTime.byHour = (char)m_ctTimeStart.GetHour();
        struFindLogCond.struStartTime.byMinute = (char)m_ctTimeStart.GetMinute();
        struFindLogCond.struStartTime.bySecond = (char)m_ctTimeStart.GetSecond();
        struFindLogCond.struStartTime.byISO8601 = g_bISO8601;
        struFindLogCond.struStartTime.cTimeDifferenceH = g_iHourDiffWithUTC;
        struFindLogCond.struStartTime.cTimeDifferenceM = g_iMinDiffWithUTC;

        struFindLogCond.struEndTime.wYear = (WORD)m_ctDateStop.GetYear();
        struFindLogCond.struEndTime.byMonth = (char)m_ctDateStop.GetMonth();
        struFindLogCond.struEndTime.byDay = (char)m_ctDateStop.GetDay();
        struFindLogCond.struEndTime.byHour = (char)m_ctTimeStop.GetHour();
        struFindLogCond.struEndTime.byMinute = (char)m_ctTimeStop.GetMinute();
        struFindLogCond.struEndTime.bySecond = (char)m_ctTimeStop.GetSecond();
        struFindLogCond.struEndTime.byISO8601 = g_bISO8601;
        struFindLogCond.struEndTime.cTimeDifferenceH = g_iHourDiffWithUTC;
        struFindLogCond.struEndTime.cTimeDifferenceM = g_iMinDiffWithUTC;
        

        if (m_bVideoPlatLog)
        {
			NET_DVR_VEDIOPLATLOG struVedioPlat = {0};
			struVedioPlat.byDevSequence = m_comboSequence.GetCurSel();
			if (m_comboSequence.GetCurSel() == 0)
			{
				struVedioPlat.byDevSequence = 0xff;
			}
			else if (m_comboSequence.GetCurSel() == 1)
			{
				struVedioPlat.byDevSequence = 0xfe;
			}
			else
			{
				struVedioPlat.byDevSequence = m_comboSequence.GetCurSel() - 2;
			}
			
			struVedioPlat.bySearchCondition = 0;
            NET_DVR_TIME StartTime;
            NET_DVR_TIME StopTime;
            StartTime.dwYear = (WORD)m_ctDateStart.GetYear();
            StartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
            StartTime.dwDay = (WORD)m_ctDateStart.GetDay();
            StartTime.dwHour = (char)m_ctTimeStart.GetHour();
            StartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
            StartTime.dwSecond = (char)m_ctTimeStart.GetSecond();

            StopTime.dwYear = (WORD)m_ctDateStop.GetYear();
            StopTime.dwMonth = (WORD)m_ctDateStop.GetMonth();
            StopTime.dwDay = (WORD)m_ctDateStop.GetDay();
            StopTime.dwHour = (char)m_ctTimeStop.GetHour();
            StopTime.dwMinute = (char)m_ctTimeStop.GetMinute();
            StopTime.dwSecond = (char)m_ctTimeStop.GetSecond();
			m_lLogHandle = NET_DVR_FindDVRLog_Matrix(m_lLoginID, m_iMode, m_iMajType, m_iMinType, &struVedioPlat, &StartTime, &StopTime);
		}
		else
		{
            m_lLogHandle = NET_DVR_FindDVRLog_V50(m_lLoginID, &struFindLogCond);
	 //		m_lLogHandle = NET_DVR_FindDVRLog_V30(m_lLoginID, m_iMode, m_iMajType, m_iMinType, &StartTime, &StopTime, m_bChkSmart);
    //        m_lLogHandle = NET_DVR_FindDVRLog(m_lLoginID, m_iMode, m_iMajType, m_iMinType, &StartTime, &StopTime);
		}
		if (m_lLogHandle < 0)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FindDVRLog_V50");
            
            g_StringLanType(szLan, "搜索日志失败", "Search log failed");
            AfxMessageBox(szLan);
            return;
        }
        m_bSearch = TRUE;
        m_lLogNum = 0;
        m_listDeviceLog.DeleteAllItems();
        DWORD dwThreadId;
        if (m_hFileThread == NULL)
        {
            m_hFileThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetLogFileThread),this,0,&dwThreadId);		
        }
        if (m_hFileThread == NULL)
        {
            g_StringLanType(szLan, "打开线程失败", "Open thread failed");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止搜索", "Stop Search");
        GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
        m_bSearch = TRUE;
    }
    else
    {
        if (!NET_DVR_FindLogClose_V30(m_lLogHandle))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FindLogClose_V30");
        }
        m_lLogHandle = -1;
        g_StringLanType(szLan, "搜索日志", "Search Log");
        GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
        m_bSearch = FALSE;
        m_lLogNum = 0;
        if (m_hFileThread)
        {
            TerminateThread(m_hFileThread, 0);
            CloseHandle(m_hFileThread);
            m_hFileThread = NULL;
        }
        
        m_hFileThread = NULL;
    }
}

/*********************************************************
Function:	DoHide()
Desc:		release resource while hiding search interface
Input:	
Output:	
Return:	
**********************************************************/
void CDlgLogSearch::DoHide()
{
    m_listDeviceLog.DeleteAllItems();
    if (m_hFileThread)
    {
        TerminateThread(m_hFileThread, 0);
        CloseHandle(m_hFileThread);
        m_hFileThread = NULL;
        NET_DVR_FindLogClose_V30(m_lLogHandle);
    }
    ShowWindow(SW_HIDE);
}

/*********************************************************
Function: OnDblclkListDeviceLog	
Desc:		show the detail information
Input:	none
Output:	none
Return:	none
**********************************************************/
void CDlgLogSearch::OnDblclkListDeviceLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
    UNREFERENCED_PARAMETER(pNMHDR);
    //	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
    int iItemSel = 0;
    char* pTxt = new char[11024];
    
    POSITION  iPos = m_listDeviceLog.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    iItemSel = m_listDeviceLog.GetNextSelectedItem(iPos);//%s\t%s\tm_listAllLog.GetItemText(iItemSel,1),\m_listAllLog.GetItemText(iItemSel,2)
    //csTxt.Format("%s",m_listDeviceLog.GetItemText(iItemSel,5));
    m_listDeviceLog.GetItemText(iItemSel, 5, pTxt, 11024);
    MessageBox(pTxt);
    
    if (OpenClipboard())   
    {   
        HGLOBAL   clipbuffer;   
        char   *   buffer;   
        EmptyClipboard();   
        clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,  11024);   
        buffer   =   (char*)GlobalLock(clipbuffer);   
        strcpy(buffer,   LPCSTR(pTxt));   
        GlobalUnlock(clipbuffer);   
        SetClipboardData(CF_TEXT,clipbuffer);   
        CloseClipboard();   
    } 
    delete[] pTxt; 
    *pResult = 0;	
}

void CDlgLogSearch::OnBtnExit() 
{
    // TODO: Add your control notification handler code here
    if (m_hFileThread)
    {
        TerminateThread(m_hFileThread, 0);
        CloseHandle(m_hFileThread);
        m_hFileThread = NULL;
        NET_DVR_FindLogClose_V30(m_lLogHandle);
    }
    CDialog::OnCancel();
}

/*********************************************************
Function:	EnableCtrl
Desc:		make the control enable or not
Input:	bEnable, TRUE/FALSE
Output:	none
Return:	none
**********************************************************/
void CDlgLogSearch::EnableCtrl(BOOL bEnable)
{
    GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMBO_MAJOR_TYPE)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMBO_MINOR_TYPE)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMBO_MODE)->EnableWindow(bEnable);
}

void CDlgLogSearch::OnSelchangeComboMinorType() 
{
    // TODO: Add your control notification handler code here
    DWORD dwIndex = 0;
    dwIndex = m_comboMinorType.GetItemData(m_comboMinorType.GetCurSel());
    TRACE("----MINOR INDEX key--- %x\n", dwIndex);
}

void CDlgLogSearch::OnCheckVideoplat() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bVideoPlatLog)
	{
		GetDlgItem(IDC_STATIC_SEQUENCE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_SEQUENCE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_SEQUENCE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_SEQUENCE)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}
