# Microsoft Developer Studio Project File - Name="ClientDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ClientDemo - Win32 Debug En
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo.mak" CFG="ClientDemo - Win32 Debug En"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo - Win32 Release En" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo - Win32 Debug En" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseVC60"
# PROP Intermediate_Dir "ReleaseVC60"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "../incCn" /I "./" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "DEMO_LAN_CN" /FAcs /Fa"VC60/" /FR"VC60/" /Fo"VC60/" /Fd"VC60/" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /I "../include" /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /fo"Release/ClientDemo.res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/ClientDemo.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib winmm.lib GdiPlus.lib IPHlpApi.Lib shlwapi.lib /nologo /subsystem:windows /incremental:yes /pdb:"../lib/ClientDemo.pdb" /debug /machine:I386 /out:"../lib/ClientDemo.exe" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none /map

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../incCn" /I "./" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "DEMO_LAN_CN" /FR"DVC60/" /Fp"DVC60/ClientDemo.pch" /YX /Fo"DVC60/" /Fd"DVC60/" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /I "../include" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 GdiPlus.lib HCNetSDK.lib PlayCtrl.lib ws2_32.lib winmm.lib IPHlpApi.Lib Shlwapi.lib /nologo /subsystem:windows /pdb:"../lib/ClientDemo.pdb" /debug /machine:I386 /out:"../lib/ClientDemo.exe" /libpath:"../lib" /libpath:"../incCn"
# SUBTRACT LINK32 /pdb:none /incremental:no /map

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Release En"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ClientDemo___Win32_Release_En"
# PROP BASE Intermediate_Dir "ClientDemo___Win32_Release_En"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ClientDemo___Win32_Release_En"
# PROP Intermediate_Dir "ClientDemo___Win32_Release_En"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "../incEn" /I "./" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "DEMO_LAN_EN" /FAcs /Fa"En/" /FR"En/" /Fo"En/" /Fd"En/" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /I "../include" /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /I "../include" /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib DsSdk.lib winmm.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"msvcp60.lib" /out:"..\lib\ClientDemo.exe" /libpath:"../lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib winmm.lib GdiPlus.lib IPHlpApi.Lib Shlwapi.lib /nologo /subsystem:windows /pdb:"VC60/ClientDemoEn.pdb" /map:"En/ClientDemoEn.map" /debug /machine:I386 /out:"../lib/ClientDemoEn.exe" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Debug En"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ClientDemo___Win32_Debug_En"
# PROP BASE Intermediate_Dir "ClientDemo___Win32_Debug_En"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_En"
# PROP Intermediate_Dir "Debug_En"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../incEn" /I "./" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "DEMO_LAN_EN" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /I "../include" /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /I "../include" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib DsSdk.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcp60.lib" /out:"../lib/ClientDemo.exe" /pdbtype:sept /libpath:"../lib"
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 GdiPlus.lib HCNetSDK.lib PlayCtrl.lib ws2_32.lib winmm.lib IPHlpApi.Lib Shlwapi.lib /nologo /subsystem:windows /pdb:"En/ClientDemoEnD.pdb" /debug /machine:I386 /out:"../lib/ClientDemoEnD.exe" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "ClientDemo - Win32 Release"
# Name "ClientDemo - Win32 Debug"
# Name "ClientDemo - Win32 Release En"
# Name "ClientDemo - Win32 Debug En"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\B10SeriesConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ClientDemo.rc

!IF  "$(CFG)" == "ClientDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Debug"

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Release En"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Debug En"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ClientDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemoEn.rc

!IF  "$(CFG)" == "ClientDemo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Release En"

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Debug En"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ConvertC10S21Param.cpp
# End Source File
# Begin Source File

SOURCE=.\DecoderCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogMultiNetCard.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogRecordTimeSpan.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg67DVSCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAbilityAutoDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgACAlarmInOutCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgACCardParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAccessCameraCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCardPasswdCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCardPasswdParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCardUserInfoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCaseSensor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsExternalDevCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsFingerPrintCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgACSGateTimeCFG.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsPersonnelChannelCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsPhoneDoorRightCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsSmsCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsSnapCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAcsWorkStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAES.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCenterNetCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCenterServerCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmChanAblitity.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmExceptionHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHost.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAudioAssociateAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostDataUploadMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostDialParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEnableCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEventTrigger.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostExternalDevLimitValue.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostExternalDevState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostExternalModule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostFaultProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostGetAllModule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostGPRS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostHistoryData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLED.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLEDBrightness.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLogSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostModuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostNetCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostPointCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostPrinter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostReportMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostRs485.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostSensorLinkage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostSubsystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTransparent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTriggerCode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostZoomAddr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmKeyboardUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmNetUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOperatorUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOutCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmPicCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmTamper.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAntiSneakHostCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAreaMaskCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAreaMonitorCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAtmFrameFormatV30.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioDiacriticalCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioInVolumeCfg1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioOutVolumeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioUploadDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioUploadDownload.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoReboot.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAutoUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBatchConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBathcUserRightCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBatteryPower.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBellFileCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBroadCast.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBuiltinSupplementLight.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBvCalibParamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgC10S21Config.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCameraSetupCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCardReaderCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCaseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCcdParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCenterPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCertInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChanInputAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChannelInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCheckTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgClearAcsParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCloudStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCloudStorageCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCloudStoragePhoneTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCMSParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCodeSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCommuSecurity.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCompressionV30.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConferenceParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConferenceRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigAll.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigFlash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConnectList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCourseCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCourseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCourseList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateVD.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGCreateWall.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCuntomProtocal.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCurrentEncodeAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCVR.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecoderAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecoderControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecorder.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecWinStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecWinStatusUniform.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDelayPreviewCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceAudioTalkCode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceLanguageEncode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceSelfCheckState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDevServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDevWorkMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDH3.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiagnosticServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiskQuota.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDoorConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDoTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDPCCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDynChanAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEctChanStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEctWorkState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgESataMiniSasUsage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEthernetIpv6Cfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEventCardLinkageCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExternalDev.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEZVIZAccessCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFiberRingCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFibreDev.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFireDetection.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFishEye.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyeCorrect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyeFECWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFishEyePtzControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyePtzPlayWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyeTrackCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFormatHD.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFortify.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFrameCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFTPUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCardCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCardInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGB28181ServerCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGBT28181ProAccessUniform.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGBT28181ProtocolAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetAccessDeviceChannelInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllPointCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllRs485Cfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllRs485Slot.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllSensor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetDigitalChannelStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGetWifiClientListInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGISInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGopInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGroupCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHardDiskCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHeatMapCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHolidayCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIDSMainBoard.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImageDiffDetectionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImExportIPCCfgFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInChanVideoLostCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionCapabilites.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionClock.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionClockWeather.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionContent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionMaterial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionProgram.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionRelease.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionScheduleSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionScheduleSelfdefine.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionShutdown.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTermainlServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTerminal.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTerminalUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTernimalPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionVolum.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionXmlCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionXmlUpdownload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfrareCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfrared.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInqMixAudioInCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInquestCaseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInquestDvr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInquestEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInquestFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInqUserRight.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInteractive.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveFileInfoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveScreenConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveScreenFileUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIOOutCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgDDNS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgEasyDDNS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgIPServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgStreamServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAddrFilterCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPCFrontAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPCPlateRecog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSimpIntellCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSpecial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSpeclalEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPDomeLocalCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIpViewCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIscsiCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgISPParamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITCAblity.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITCIOinCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSBaseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSImageMergeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSIOinCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSIpcCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSMiniPost.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSOverlapCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSRoadInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSWorkState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJpegCaptureCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJpegFTP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJPEGSnatchConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyboardCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLampCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLampControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdMatrixRelation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdMatrixSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdParamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdScene.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLCDScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLCDScreenDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdSerial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdSplice.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdSwitchCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLcdUserCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLedConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLedConfigDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLedConfigRecv.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLEDTimerSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLimitAngle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLinkStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLiteStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalInputInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalLogConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalRecordSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLockedInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManualSnap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMasterSlaveTracking.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecBigScrSplice.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecodeChanJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatOutputCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatUnitedSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUAbilityDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUAddConference.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUCall.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUClearConfHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUConferenceCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUDelConference.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUGetConfStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUGetDailyDistribution.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUGetTermGroupList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUSearchConference.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUTerminalCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUTerminalGroupCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMCUTerminalManageCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDecOsd.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDev.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDevPic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDevResource.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMicrophoneStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMixAudioInCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMixAudioOutCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMobileTriggerCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgModifyRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMonitorInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMonitorLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMouseEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMultiCardCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMultilStreamRelChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraEventVedio.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraHttps.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraRecordPackage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetServiceCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkBonding.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkFlowTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNVRCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNVRIPCCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOneKeyBackupCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOneKeyPublish.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOneOutputScheduleRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOnlineUserList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOutputCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOutputScheduleRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPanoramaImage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPassiveTransCode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPassiveWin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPdcCalibration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPdcResult.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPdcRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPdcRuleCfgEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPDCSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPersonnelStatis.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPicModelCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPictureUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayBack.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayDvrRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLocalFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLockFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPosChanFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPosConnectMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPosFilterEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPosFilterRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPositionTrackCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPosManage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPosRecvData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPOSRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPosSerialPortRecvData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPostRadarCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPPPCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPPTDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreviewSwitchCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPreviewWin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPrivateProtocolCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProductAcs.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProductAlarmHostCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProductCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProductionTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProductVcaCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzCfgCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPTZCruise.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzLockCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzParkActionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPTZPreset.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzScope.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPTZTasks.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzTrackParamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPUStream.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQuickAddIpc.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRaidConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgReaderAntiSneakHostCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHost.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostAudioEffectiveCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostBackgroundPicCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostDirectedStrategyCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostEndTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostFilePublish.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostFilmModeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostFrameCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostRTMPCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostV120.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostVideoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordPublishCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordStreamTransType.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRegionList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAdvanceNetConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmDetectFace.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInPtzInvoke.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControllerCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControllerManage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteEmailAddReceiver.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteFanException.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideArea.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteIPAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteMotionDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteNetNFS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemotePullException.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecordSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteShowString.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteStreamRecordSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInLost.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteZone.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRoiCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRtspConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSafeCabinState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSafetyCabin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScaleOutCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSceneChangeUpdate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSceneTimeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScreenCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScreenLogoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScreenLogoCfgUniform.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSDIAutoTrackCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSDIMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSecurityCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSenceControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSenceControlUniform.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSensorAddPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSensorCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSerialTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSignalLightSync.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSizeFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSlaveCameraInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSmartSearchPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSmartStoragedDetection.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSneakAndLock.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSnmpCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSoftHardAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSplitterStartTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSplitterTransparent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStorageServerSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStreamAttachInfoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStreamID.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStreamManualRecordAndLock.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStreamRecordInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStreamRecordStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStreamSrcCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSubIPCCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSubITSCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSubsysNetCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSystemTimeAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgT1test.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTalkMREx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTerminalConferenceStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermManage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThermalDoubleSpectrum.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThirdGenerationCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThreeDimensionaPtz.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgThscreen.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTimeCorrect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTmeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTPSRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTransAutoReboot.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTransCompression.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTransConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTransDevStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTransStreamSrcCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrialAudioActivation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrialCaseParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrialDVR.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrialHostStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTrialPIPCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTsSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUniformInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpgradeIPC.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUploadCalibrationFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUploadFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUploadLogo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpnpCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpStreamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAidRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVCAAlarmLogo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAlarmTimeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAuxAreaList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBaselineScene.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCalibrate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBlackList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBVCalibrate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaChanCtrlCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaChannelWorkMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDetectionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVCADetionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAccessCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDrawMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaEnterRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFace.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceMatchLogSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceSnapCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindBackgroundPic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindSnapData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaForensicsModeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFunCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITCTriggerCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCalibrate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsSched.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLaneCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLF.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaMaskRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaObjectColor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaParamkey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaPositionRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaRemoteChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaResetCounterCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVCARuleColorCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSavePathConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneAidRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneITSCalibrate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneLaneCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneRegionList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneTpsRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneTrafficCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSingleProcImg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSnapDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaTrackCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaVQDAlarmPic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaVQDEventRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaWorkStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVCSExternalMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVedioAudioInCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVedioImgDB.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVehicleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVehicleControlCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVehicleMvaCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVehicleRecogCFG.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomAlarmCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomAuthCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomCall.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomCallRoomCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomDeviceIDCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomElevatorCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomGateway.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomIOInCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomIOOutCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomNoticeDataCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomOpTimeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomPrivilegePwdCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomRelateDevCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomStreamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoOut.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoOutResolutionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoWallElse.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVISDevInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVISRegisterInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVoiceTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVQDCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVqdPlan.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWall.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallBasemapWin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallCfgUniform.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallVirLED.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallWin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallWinVideoWall.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWD1Enable.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWDRCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWeekPlan.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWhiteList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWifi.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWifiDHCPCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWIFIServerCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWinPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWirelessBusinessSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWirelessDial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWirelessServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAlarmAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlDecoderAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlEventAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlItcAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlJpegCapAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlLCDAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlNetAppAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlRaidAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlSerialAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlVideoPic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlWallAblity.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgZeroChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgZoneLinkageChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawFun.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoDiffusionParamsConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\JPEGPicDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\Markup.cpp
# End Source File
# Begin Source File

SOURCE=.\MatCodeSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\MatCycLink.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDecDnsCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDecoderStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDispChan.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDispChanControl.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDynamicTest.cpp
# End Source File
# Begin Source File

SOURCE=.\MatPassive.cpp
# End Source File
# Begin Source File

SOURCE=.\MatPlayBack.cpp
# End Source File
# Begin Source File

SOURCE=.\MatTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\MatVedioPlatform.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PTZButton.cpp
# End Source File
# Begin Source File

SOURCE=.\PTZButton1.cpp
# End Source File
# Begin Source File

SOURCE=.\PtzControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundIn.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgAdapterCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgAlarmCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgArrayCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgATMInfoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgBTS.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgCVRCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgDeviceCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgDVRNVRCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgExceptionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgMatDecCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgNetworkCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgPDCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgPreviewCfgV30.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgSerialCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgUserCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgVDCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgWndSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeSegment.cpp
# End Source File
# Begin Source File

SOURCE=.\UserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VcaCommonOperations.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveSound.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLParamsConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlUserAbility.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Alarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\audio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\camera.bmp
# End Source File
# Begin Source File

SOURCE=.\res\camera.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\dev_alarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fortify.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fortify_alarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\IPChan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\p_r_a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PAUSE_ENABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PLAY_DISABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\PLAY_ENABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\playAndAlarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rec_play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_disable.ico
# End Source File
# Begin Source File

SOURCE=.\res\STOP.ICO
# End Source File
# Begin Source File

SOURCE=.\res\STOP_DISABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\tree.bmp
# End Source File
# End Group
# Begin Group "includeCn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\incCn\DataType.h
# End Source File
# Begin Source File

SOURCE=..\incCn\DecodeCardSdk.h
# End Source File
# Begin Source File

SOURCE=..\incCn\HCNetSDK.h
# End Source File
# Begin Source File

SOURCE=..\incCn\plaympeg4.h
# End Source File
# End Group
# Begin Group "includeEn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\incEn\DataType.h
# End Source File
# Begin Source File

SOURCE=..\incEn\DecodeCardSdk.h
# End Source File
# Begin Source File

SOURCE=..\incEn\HCNetSDK.h
# End Source File
# Begin Source File

SOURCE=..\incEn\plaympeg4.h
# End Source File
# End Group
# Begin Group "xml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\xml\tinystr.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\tinystr.h
# End Source File
# Begin Source File

SOURCE=.\xml\tinyxml.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\tinyxml.h
# End Source File
# Begin Source File

SOURCE=.\xml\tinyxmlerror.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\tinyxmlparser.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\XmlBase.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\XmlBase.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\B10SeriesConfig.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConvertC10S21Param.h
# End Source File
# Begin Source File

SOURCE=.\DecoderCfg.h
# End Source File
# Begin Source File

SOURCE=.\DeviceDlg.h
# End Source File
# Begin Source File

SOURCE=.\DialogMultiNetCard.h
# End Source File
# Begin Source File

SOURCE=.\DialogRecordTimeSpan.h
# End Source File
# Begin Source File

SOURCE=.\Dlg67DVSCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAbilityAutoDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgACAlarmInOutCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgACCardParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgAccessCameraCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCardPasswdCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCardPasswdParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCardUserInfoCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCaseSensor.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsExternalDevCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsFingerPrintCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgACSGateTimeCFG.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsPersonnelChannelCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsPhoneDoorRightCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsSmsCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsSnapCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAcsWorkStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddDevice.h
# End Source File
# Begin Source File

SOURCE=.\DlgAES.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCenterNetCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCenterServerCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmChanAblitity.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmExceptionHandle.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHost.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAudioAssociateAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostDataUploadMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostDialParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEnableCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEventTrigger.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostExternalDevLimitValue.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostExternalDevState.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostExternalModule.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostFaultProcess.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostGetAllModule.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostGPRS.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostHistoryData.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLED.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLEDBrightness.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLogSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostModuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostNetCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostPointCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostPrinter.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostReportMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostRs485.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostSensorLinkage.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostSubsystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTransparent.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTriggerCode.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostZoomAddr.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmKeyboardUser.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmNetUser.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOperatorUser.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOutCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmPicCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmTamper.h
# End Source File
# Begin Source File

SOURCE=.\DlgAntiSneakHostCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAreaMaskCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAreaMonitorCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAtmFrameFormatV30.h
# End Source File
# Begin Source File

SOURCE=.\DlgAudioChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAudioDiacriticalCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAudioInVolumeCfg1.h
# End Source File
# Begin Source File

SOURCE=.\DlgAudioOutVolumeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoReboot.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\DlgBatchConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgBathcUserRightCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgBatteryPower.h
# End Source File
# Begin Source File

SOURCE=.\DlgBellFileCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgBroadCast.h
# End Source File
# Begin Source File

SOURCE=.\DlgBuiltinSupplementLight.h
# End Source File
# Begin Source File

SOURCE=.\DlgBvCalibParamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgC10S21Config.h
# End Source File
# Begin Source File

SOURCE=.\DlgCameraSetupCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgCardReaderCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgCaseInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgCcdParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgCenterPoint.h
# End Source File
# Begin Source File

SOURCE=.\DlgCertInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgChanInputAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgChannelInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgCheckTime.h
# End Source File
# Begin Source File

SOURCE=.\DlgClearAcsParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgCloudStorage.h
# End Source File
# Begin Source File

SOURCE=.\DlgCloudStorageCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgCloudStoragePhoneTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgCMSParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgCodeSplitter.h
# End Source File
# Begin Source File

SOURCE=.\DlgCommuSecurity.h
# End Source File
# Begin Source File

SOURCE=.\DlgCompressionV30.h
# End Source File
# Begin Source File

SOURCE=.\DlgConferenceParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgConferenceRegion.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigAll.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigFlash.h
# End Source File
# Begin Source File

SOURCE=.\DlgConnectList.h
# End Source File
# Begin Source File

SOURCE=.\DlgCourseCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgCourseInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgCourseList.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateVD.h
# End Source File
# Begin Source File

SOURCE=.\DLGCreateWall.h
# End Source File
# Begin Source File

SOURCE=.\DlgCuntomProtocal.h
# End Source File
# Begin Source File

SOURCE=.\DlgCurrentEncodeAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgCVR.h
# End Source File
# Begin Source File

SOURCE=.\DlgDebug.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecoderAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecoderControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecorder.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecWinStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecWinStatusUniform.h
# End Source File
# Begin Source File

SOURCE=.\DlgDelayPreviewCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceAudioTalkCode.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceLanguageEncode.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceSelfCheckState.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceState.h
# End Source File
# Begin Source File

SOURCE=.\DlgDevServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgDevWorkMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgDH3.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiagnosticServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiskQuota.h
# End Source File
# Begin Source File

SOURCE=.\DlgDoorConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgDoTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgDPCCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgDynChanAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgEctChanStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgEctWorkState.h
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeJoint.h
# End Source File
# Begin Source File

SOURCE=.\DlgESataMiniSasUsage.h
# End Source File
# Begin Source File

SOURCE=.\DlgEthernetIpv6Cfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgEventCardLinkageCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgExternalDev.h
# End Source File
# Begin Source File

SOURCE=.\DlgEZVIZAccessCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgFiberRingCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgFibreDev.h
# End Source File
# Begin Source File

SOURCE=.\DlgFireDetection.h
# End Source File
# Begin Source File

SOURCE=.\DlgFishEye.h
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyeCorrect.h
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyeFECWnd.h
# End Source File
# Begin Source File

SOURCE=.\DlgFishEyePtzControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyePtzPlayWnd.h
# End Source File
# Begin Source File

SOURCE=.\DlgFisheyeTrackCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgFormatHD.h
# End Source File
# Begin Source File

SOURCE=.\DlgFortify.h
# End Source File
# Begin Source File

SOURCE=.\DlgFrameCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgFTPUpload.h
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCardCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCardInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgGB28181ServerCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgGBT28181ProAccessUniform.h
# End Source File
# Begin Source File

SOURCE=.\DlgGBT28181ProtocolAccess.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetAccessDeviceChannelInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllPointCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllRs485Cfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllRs485Slot.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllSensor.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllSensorJoint.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetAllSensorJointCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetDigitalChannelStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgGetWifiClientListInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgGISInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgGopInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgGroupCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgHardDiskCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgHeatMapCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgHolidayCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgIDSMainBoard.h
# End Source File
# Begin Source File

SOURCE=.\DlgImageDiffDetectionCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgImExportIPCCfgFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgInChanVideoLostCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionCapabilites.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionClock.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionClockWeather.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionContainer.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionContent.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionMaterial.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionPlay.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionProgram.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionRelease.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionSchedule.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionScheduleSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionScheduleSelfdefine.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionShutdown.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTermainlServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTerminal.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTerminalUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionTernimalPreview.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionVolum.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionXmlCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoDiffusionXmlUpdownload.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfrareCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfrared.h
# End Source File
# Begin Source File

SOURCE=.\DlgInqMixAudioInCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgInquestCaseInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgInquestDvr.h
# End Source File
# Begin Source File

SOURCE=.\DlgInquestEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgInquestFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgInqUserRight.h
# End Source File
# Begin Source File

SOURCE=.\DlgInteractive.h
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveFileInfoCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveScreenConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgInteractiveScreenFileUpload.h
# End Source File
# Begin Source File

SOURCE=.\DlgIOOutCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgDDNS.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgEasyDDNS.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgIPServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgStreamServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAddrFilterCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPCFrontAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPCPlateRecog.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSimpIntellCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSpecial.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSpeclalEx.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPDomeLocalCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgIscsiCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgISPParamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITCAblity.h
# End Source File
# Begin Source File

SOURCE=.\DlgITCIOinCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSBaseInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSImageMergeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSIOinCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSIpcCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSMiniPost.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSMonitor.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSOverlapCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSRoadInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSUpload.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSWorkState.h
# End Source File
# Begin Source File

SOURCE=.\DlgJpegCaptureCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgJpegFTP.h
# End Source File
# Begin Source File

SOURCE=.\DlgJPEGSnatchConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyboardCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgLampCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgLampControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdMatrixRelation.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdMatrixSwitch.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdParamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdScene.h
# End Source File
# Begin Source File

SOURCE=.\DlgLCDScreen.h
# End Source File
# Begin Source File

SOURCE=.\DlgLCDScreenDisplay.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdSerial.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdSplice.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdSwitchCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgLcdUserCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgLedConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLedConfigDisplay.h
# End Source File
# Begin Source File

SOURCE=.\DlgLedConfigRecv.h
# End Source File
# Begin Source File

SOURCE=.\DlgLEDTimerSwitch.h
# End Source File
# Begin Source File

SOURCE=.\DlgLimitAngle.h
# End Source File
# Begin Source File

SOURCE=.\DlgLinkStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgLiteStorage.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalInputInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalLogConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalRecordSchedule.h
# End Source File
# Begin Source File

SOURCE=.\DlgLockedInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgLogSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgManualSnap.h
# End Source File
# Begin Source File

SOURCE=.\DlgMasterSlaveTracking.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecBigScrSplice.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecodeChanJoint.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatOutputCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatUnitedSystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUAbilityDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUAddConference.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUCall.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUClearConfHistory.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUConferenceCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUDelConference.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUGetConfStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUGetDailyDistribution.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUGetTermGroupList.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUSearchConference.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUTerminalCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUTerminalGroupCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgMCUTerminalManageCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDecOsd.h
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDev.h
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDevPic.h
# End Source File
# Begin Source File

SOURCE=.\DlgMergeDevResource.h
# End Source File
# Begin Source File

SOURCE=.\DlgMicrophoneStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgMixAudioInCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgMixAudioOutCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgMobileTriggerCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgModifyRecord.h
# End Source File
# Begin Source File

SOURCE=.\DlgMonitorInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgMonitorLocation.h
# End Source File
# Begin Source File

SOURCE=.\DlgMouseEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgMultiCardCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgMultilStreamRelChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraEventVedio.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraHttps.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraRecordPackage.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraSeries.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetServiceCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkBonding.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkFlowTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgNVRCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgNVRIPCCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgOneKeyBackupCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgOneKeyPublish.h
# End Source File
# Begin Source File

SOURCE=.\DlgOneOutputScheduleRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgOnlineUserList.h
# End Source File
# Begin Source File

SOURCE=.\DlgOutput.h
# End Source File
# Begin Source File

SOURCE=.\DlgOutputCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgOutputScheduleRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPanoramaImage.h
# End Source File
# Begin Source File

SOURCE=.\DlgPassiveTransCode.h
# End Source File
# Begin Source File

SOURCE=.\DlgPassiveWin.h
# End Source File
# Begin Source File

SOURCE=.\DlgPdcCalibration.h
# End Source File
# Begin Source File

SOURCE=.\DlgPdcResult.h
# End Source File
# Begin Source File

SOURCE=.\DlgPdcRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPdcRuleCfgEx.h
# End Source File
# Begin Source File

SOURCE=.\DlgPDCSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgPersonnelStatis.h
# End Source File
# Begin Source File

SOURCE=.\DlgPicModelCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPictureUpload.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayBack.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayConvert.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayDvrRecord.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLocalFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLockFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayMotion.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteTime.h
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPosChanFilter.h"
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPosConnectMode.h"
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPosFilterEffect.h"
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPosFilterRule.h"
# End Source File
# Begin Source File

SOURCE=.\DlgPositionTrackCfg.h
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPosManage.h"
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPosRecvData.h"
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPOSRegion.h"
# End Source File
# Begin Source File

SOURCE="E:\brunch\美分7204ST\代码\code\win32\ClientDemo\DlgPosSerialPortRecvData.h"
# End Source File
# Begin Source File

SOURCE=.\DlgPostRadarCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPPPCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPPTDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreviewSwitchCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPreviewWin.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrivateProtocolCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgProductAcs.h
# End Source File
# Begin Source File

SOURCE=.\DlgProductAlarmHostCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgProductCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgProductionTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgProductVcaCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzCfgCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgPTZCruise.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzLockCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzParkActionCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPTZPreset.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzScope.h
# End Source File
# Begin Source File

SOURCE=.\DlgPTZTasks.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzTrackParamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPUStream.h
# End Source File
# Begin Source File

SOURCE=.\DlgQuickAddIpc.h
# End Source File
# Begin Source File

SOURCE=.\DlgRaidConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgReaderAntiSneakHostCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHost.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHost1.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostAudioEffectiveCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostBackgroundPicCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostDirectedStrategyCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostEndTime.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostFilePublish.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostFilmModeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostFrameCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostRTMPCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostV120.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordHostVideoCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordLabel.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordPublishCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordStreamTransType.h
# End Source File
# Begin Source File

SOURCE=.\DlgRegionList.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmDetectFace.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInHandle.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInPtzInvoke.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControllerCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControllerManage.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlPlay.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteEmailAddReceiver.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteFanException.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideArea.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteIPAccess.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteMotionDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteNetNFS.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemotePullException.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecordSchedule.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteShowString.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteStreamRecordSchedule.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInLost.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteZone.h
# End Source File
# Begin Source File

SOURCE=.\DlgRoiCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRtspConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgSafeCabinState.h
# End Source File
# Begin Source File

SOURCE=.\DlgSafetyCabin.h
# End Source File
# Begin Source File

SOURCE=.\DlgScaleOutCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSceneChangeUpdate.h
# End Source File
# Begin Source File

SOURCE=.\DlgSceneTimeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgScreenCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgScreenLogoCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgScreenLogoCfgUniform.h
# End Source File
# Begin Source File

SOURCE=.\DlgSDIAutoTrackCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSDIMatrix.h
# End Source File
# Begin Source File

SOURCE=.\DlgSecurityCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSenceControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgSenceControlUniform.h
# End Source File
# Begin Source File

SOURCE=.\DlgSensorAddPreview.h
# End Source File
# Begin Source File

SOURCE=.\DlgSensorCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSerialTrans.h
# End Source File
# Begin Source File

SOURCE=.\DlgSignalLightSync.h
# End Source File
# Begin Source File

SOURCE=.\DlgSizeFilter.h
# End Source File
# Begin Source File

SOURCE=.\DlgSlaveCameraInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgSmartSearchPicture.h
# End Source File
# Begin Source File

SOURCE=.\DlgSmartStoragedDetection.h
# End Source File
# Begin Source File

SOURCE=.\DlgSneakAndLock.h
# End Source File
# Begin Source File

SOURCE=.\DlgSnmpCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSoftHardAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgSplitterStartTrans.h
# End Source File
# Begin Source File

SOURCE=.\DlgSplitterTransparent.h
# End Source File
# Begin Source File

SOURCE=.\DlgStorageServerSwitch.h
# End Source File
# Begin Source File

SOURCE=.\DlgStreamAttachInfoCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgStreamID.h
# End Source File
# Begin Source File

SOURCE=.\DlgStreamManualRecordAndLock.h
# End Source File
# Begin Source File

SOURCE=.\DlgStreamRecordInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgStreamRecordStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgStreamSrcCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSubIPCCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSubITSCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSubsysNetCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSystemTimeAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgT1test.h
# End Source File
# Begin Source File

SOURCE=.\DlgTalkMREx.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermGroup.h
# End Source File
# Begin Source File

SOURCE=.\DlgTerminalConferenceStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermManage.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermPlay.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermState.h
# End Source File
# Begin Source File

SOURCE=.\DlgThermalDoubleSpectrum.h
# End Source File
# Begin Source File

SOURCE=.\DlgThirdGenerationCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgThreeDimensionaPtz.h
# End Source File
# Begin Source File

SOURCE=.\DlgThscreen.h
# End Source File
# Begin Source File

SOURCE=.\DlgTimeCorrect.h
# End Source File
# Begin Source File

SOURCE=.\DlgTmeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgTPSRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgTransAutoReboot.h
# End Source File
# Begin Source File

SOURCE=.\DlgTransCompression.h
# End Source File
# Begin Source File

SOURCE=.\DlgTransConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgTransDevStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgTransStreamSrcCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrialAudioActivation.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrialCaseParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrialDVR.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrialHostStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgTrialPIPCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgTsSeries.h
# End Source File
# Begin Source File

SOURCE=.\DlgUniformInterface.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpgradeIPC.h
# End Source File
# Begin Source File

SOURCE=.\DlgUploadCalibrationFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgUploadFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgUploadLogo.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpnpCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpStreamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAidRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVCAAlarmLogo.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAlarmTimeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAuxAreaList.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBaselineScene.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCalibrate.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBlackList.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBVCalibrate.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaChanCtrlCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaChannelWorkMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDataBase.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDetectionCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVCADetionCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAccessCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevChannel.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDrawMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaEnterRegion.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFace.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDataBase.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceMatchLogSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceSnapCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindBackgroundPic.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindSnapData.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaForensicsModeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFunCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITCTriggerCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCalibrate.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsSched.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLaneCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLF.h
# End Source File
# Begin Source File

SOURCE=.\DlgvcaMaskRegion.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaObjectColor.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaParamkey.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaPositionRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaRemoteChannel.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaResetCounterCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVCARuleColorCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSavePathConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneITSCalibrate.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneLaneCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneRegionList.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSceneTpsRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSingleProcImg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSnapDatabase.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaTrackCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaVQDAlarmPic.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaVQDEventRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaWorkStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgVCSExternalMatrix.h
# End Source File
# Begin Source File

SOURCE=.\DlgVedioAudioInCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVedioImgDB.h
# End Source File
# Begin Source File

SOURCE=.\DlgVehicleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVehicleControlCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVehicleMvaCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomAlarmCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomAuthCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomCall.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomCallRoomCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomDeviceIDCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomElevatorCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomGateway.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomIOInCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomIOOutCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomNoticeDataCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomOpTimeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomPrivilegePwdCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomRelateDevCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoIntercomStreamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoOut.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoOutResolutionCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoWallElse.h
# End Source File
# Begin Source File

SOURCE=.\DlgVISDevInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgVISRegisterInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgVoiceTalk.h
# End Source File
# Begin Source File

SOURCE=.\DlgVQDCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVqdPlan.h
# End Source File
# Begin Source File

SOURCE=.\DlgWall.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallBasemapWin.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallCfgUniform.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallPreview.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallVirLED.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallWin.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallWinVideoWall.h
# End Source File
# Begin Source File

SOURCE=.\DlgWD1Enable.h
# End Source File
# Begin Source File

SOURCE=.\DlgWDRCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgWeekPlan.h
# End Source File
# Begin Source File

SOURCE=.\DlgWhiteList.h
# End Source File
# Begin Source File

SOURCE=.\DlgWifi.h
# End Source File
# Begin Source File

SOURCE=.\DlgWifiDHCPCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgWIFIServerCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgWinPreview.h
# End Source File
# Begin Source File

SOURCE=.\DlgWirelessBusinessSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgWirelessDial.h
# End Source File
# Begin Source File

SOURCE=.\DlgWirelessServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAlarmAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlDecoderAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlEventAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlItcAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlJpegCapAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlLCDAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlNetAppAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlRaidAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlSerialAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlVideoPic.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlWallAblity.h
# End Source File
# Begin Source File

SOURCE=.\DlgZeroChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgZoneLinkageChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\DrawFun.h
# End Source File
# Begin Source File

SOURCE=.\GeneralDef.h
# End Source File
# Begin Source File

SOURCE=.\InfoDiffusionParamsConvert.h
# End Source File
# Begin Source File

SOURCE=..\..\src\export\header\InterfaceBase.h
# End Source File
# Begin Source File

SOURCE=.\IPExport.h
# End Source File
# Begin Source File

SOURCE=.\IPHlpApi.h
# End Source File
# Begin Source File

SOURCE=.\IPTypes.h
# End Source File
# Begin Source File

SOURCE=.\JPEGPicDownload.h
# End Source File
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# Begin Source File

SOURCE=.\MatCodeSplitter.h
# End Source File
# Begin Source File

SOURCE=.\MatCycLink.h
# End Source File
# Begin Source File

SOURCE=.\MatDecDnsCfg.h
# End Source File
# Begin Source File

SOURCE=.\MatDecoderStatus.h
# End Source File
# Begin Source File

SOURCE=.\MatDispChan.h
# End Source File
# Begin Source File

SOURCE=.\MatDispChanControl.h
# End Source File
# Begin Source File

SOURCE=.\MatDynamicTest.h
# End Source File
# Begin Source File

SOURCE=.\MatPassive.h
# End Source File
# Begin Source File

SOURCE=.\MatPlayBack.h
# End Source File
# Begin Source File

SOURCE=.\MatTrans.h
# End Source File
# Begin Source File

SOURCE=.\MatVedioPlatform.h
# End Source File
# Begin Source File

SOURCE=.\MCUGeneralDef.h
# End Source File
# Begin Source File

SOURCE=.\ModifyRecord.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\PTZButton.h
# End Source File
# Begin Source File

SOURCE=.\PTZButton1.h
# End Source File
# Begin Source File

SOURCE=.\PtzControl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SoundIn.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgAdapterCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgAlarmCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgArrayCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgATMInfoCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgBTS.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgCVRCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgDeviceCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgDVRNVRCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgExceptionCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgMatDeccfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgNetworkCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgPDCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgPreviewCfgV30.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgSerialCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgUserCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgVDCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgWndSequence.h
# End Source File
# Begin Source File

SOURCE=.\TimeSegment.h
# End Source File
# Begin Source File

SOURCE=.\UserDlg.h
# End Source File
# Begin Source File

SOURCE=.\VcaCommonOperations.h
# End Source File
# Begin Source File

SOURCE=.\WaveSound.h
# End Source File
# Begin Source File

SOURCE=.\XMLParamsConvert.h
# End Source File
# Begin Source File

SOURCE=.\XmlUserAbility.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DlgAlarmExceptionHandle.asp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\advanced\preview\win32\vc60\HCPreview.dsp
# End Source File
# Begin Source File

SOURCE=.\Modification.txt
# End Source File
# End Target
# End Project
# Section ClientDemo : {D40BF1F1-1BAD-408E-AFBD-6697451DEB0D}
# 	1:17:IDD_DLG_CLEAR_ACS:213
# 	2:16:Resource Include:resource.h
# 	2:17:IDD_DLG_CLEAR_ACS:IDD_DLG_CLEAR_ACS
# 	2:20:DlgClearAcsParam.cpp:DlgClearAcsParam.cpp
# 	2:18:DlgClearAcsParam.h:DlgClearAcsParam.h
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# 	2:24:CLASS: CDlgClearAcsParam:CDlgClearAcsParam
# End Section
# Section ClientDemo : {9EA5DF43-1BB5-4A53-AF5E-8742B5A1D82A}
# 	1:21:IDD_DLG_LCD_PARAM_CFG:191
# 	2:16:Resource Include:resource.h
# 	2:16:DlgLcdParamCfg.h:DlgLcdParamCfg.h
# 	2:10:ENUM: enum:enum
# 	2:22:CLASS: CDlgLcdParamCfg:CDlgLcdParamCfg
# 	2:19:Application Include:clientdemo.h
# 	2:21:IDD_DLG_LCD_PARAM_CFG:IDD_DLG_LCD_PARAM_CFG
# 	2:18:DlgLcdParamCfg.cpp:DlgLcdParamCfg.cpp
# End Section
# Section ClientDemo : {C62679FA-7A7D-4A2B-95C2-415A0602940D}
# 	1:18:IDD_DLG_MULTI_CARD:218
# 	2:23:CLASS: CDlgMultiCardCfg:CDlgMultiCardCfg
# 	2:16:Resource Include:resource.h
# 	2:19:DlgMultiCardCfg.cpp:DlgMultiCardCfg.cpp
# 	2:17:DlgMultiCardCfg.h:DlgMultiCardCfg.h
# 	2:18:IDD_DLG_MULTI_CARD:IDD_DLG_MULTI_CARD
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# 	2:20:DlgITSOverlapCfg.cpp:DlgITSOverlapCfg.cpp
# End Section
# Section ClientDemo : {949BA2D5-7001-4D10-9FCC-DD85550B423A}
# 	1:21:IDD_DLG_MERGE_DEV_OSD:246
# 	2:16:Resource Include:resource.h
# 	2:18:DlgMergeDecOsd.cpp:DlgMergeDecOsd.cpp
# 	2:16:DlgMergeDecOsd.h:DlgMergeDecOsd.h
# 	2:10:ENUM: enum:enum
# 	2:21:IDD_DLG_MERGE_DEV_OSD:IDD_DLG_MERGE_DEV_OSD
# 	2:22:CLASS: CDlgMergeDecOsd:CDlgMergeDecOsd
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {6B4C841D-CDF9-4F5C-B646-ED730AECE0C5}
# 	1:17:IDD_DLG_WALL_CFG1:232
# 	2:16:Resource Include:resource.h
# 	2:14:DlgWallCfg.cpp:DlgWallCfg1.cpp
# 	2:18:CLASS: CDlgWallCfg:CDlgWallCfg
# 	2:10:ENUM: enum:enum
# 	2:16:IDD_DLG_WALL_CFG:IDD_DLG_WALL_CFG1
# 	2:19:Application Include:clientdemo.h
# 	2:12:DlgWallCfg.h:DlgWallCfg1.h
# End Section
# Section ClientDemo : {B6614ED6-E53C-4F7D-ADB2-6A681F10E9CF}
# 	1:11:IDD_DLG_VQD:153
# 	2:16:Resource Include:resource.h
# 	2:11:DlgVQDCfg.h:DlgVQDCfg.h
# 	2:10:ENUM: enum:enum
# 	2:17:CLASS: CDlgVQDCfg:CDlgVQDCfg
# 	2:11:IDD_DLG_VQD:IDD_DLG_VQD
# 	2:19:Application Include:clientdemo.h
# 	2:13:DlgVQDCfg.cpp:DlgVQDCfg.cpp
# End Section
# Section ClientDemo : {CDD5B024-BE9B-4A96-B82C-B061C945CDFE}
# 	1:15:IDD_DIA_ACS_CFG:256
# 	2:16:Resource Include:resource.h
# 	2:10:ENUM: enum:enum
# 	2:11:DlgAcsCfg.h:DlgAcsCfg.h
# 	2:15:IDD_DIA_ACS_CFG:IDD_DIA_ACS_CFG
# 	2:19:Application Include:clientdemo.h
# 	2:13:DlgAcsCfg.cpp:DlgAcsCfg.cpp
# 	2:16:CLASS: DlgAcsCfg:DlgAcsCfg
# End Section
# Section ClientDemo : {C217F823-7FB9-42D8-B7DB-6FDA50F35A4E}
# 	1:22:IDD_DLG_SNEAK_AND_LOCK:220
# 	2:16:Resource Include:resource.h
# 	2:23:CLASS: CDlgSneakAndLock:CDlgSneakAndLock
# 	2:22:IDD_DLG_SNEAK_AND_LOCK:IDD_DLG_SNEAK_AND_LOCK
# 	2:10:ENUM: enum:enum
# 	2:17:DlgSneakAndLock.h:DlgSneakAndLock.h
# 	2:19:DlgSneakAndLock.cpp:DlgSneakAndLock.cpp
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {5A6319FB-F729-4519-8FBA-C980CF2ABE59}
# 	1:17:IDD_DLG_MERGE_DEV:251
# 	2:16:Resource Include:resource.h
# 	2:15:DlgMergeDev.cpp:DlgMergeDev.cpp
# 	2:17:IDD_DLG_MERGE_DEV:IDD_DLG_MERGE_DEV
# 	2:13:DlgMergeDev.h:DlgMergeDev.h
# 	2:10:ENUM: enum:enum
# 	2:19:CLASS: CDlgMergeDev:CDlgMergeDev
# 	2:19:Application Include:clientdemo.h
# 	2:21:CLASS: CDlgWallVirLED:CDlgWallVirLED
# End Section
# Section ClientDemo : {C8BA8E49-5578-4D46-A065-BCC5B4576783}
# 	1:22:IDD_DLG_STREAM_SRC_CFG:129
# 	2:16:Resource Include:resource.h
# 	2:10:ENUM: enum:enum
# 	2:22:IDD_DLG_STREAM_SRC_CFG:IDD_DLG_STREAM_SRC_CFG
# 	2:23:CLASS: CDlgStreamSrcCfg:CDlgStreamSrcCfg
# 	2:17:DlgStreamSrcCfg.h:DlgStreamSrcCfg.h
# 	2:19:DlgStreamSrcCfg.cpp:DlgStreamSrcCfg.cpp
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {C8899C02-75CC-4505-AB77-313BC90B61BF}
# 	1:11:IDD_DLG_CVR:147
# 	2:16:Resource Include:resource.h
# 	2:11:IDD_DLG_CVR:IDD_DLG_CVR
# 	2:10:DlgCVR.cpp:DlgCVR.cpp
# 	2:10:ENUM: enum:enum
# 	2:14:CLASS: CDlgCVR:CDlgCVR
# 	2:8:DlgCVR.h:DlgCVR.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {7EA63ED1-ED07-46F0-AF9A-DB0F376F0870}
# 	1:28:IDD_DLG_ALARMHOST_RS485_CFG1:210
# 	2:16:Resource Include:resource.h
# 	2:27:IDD_DLG_ALARMHOST_RS485_CFG:IDD_DLG_ALARMHOST_RS485_CFG1
# 	2:21:DlgAlarmHostRs485.cpp:DlgAlarmHostRs486.cpp
# 	2:10:ENUM: enum:enum
# 	2:19:DlgAlarmHostRs485.h:DlgAlarmHostRs486.h
# 	2:19:Application Include:clientdemo.h
# 	2:25:CLASS: CDlgAlarmHostRs485:CDlgAlarmHostRs485
# End Section
# Section ClientDemo : {73C990A2-4D5F-4DA9-BAD4-79171AD781CC}
# 	1:20:IDD_DLG_GATEWAY_CFG1:216
# 	2:16:Resource Include:resource.h
# 	2:11:IDD_DLG_CVR:IDD_DLG_CVR
# 	2:10:DlgCVR.cpp:DlgCVR.cpp
# 	2:10:ENUM: enum:enum
# 	2:14:CLASS: CDlgCVR:CDlgCVR
# 	2:8:DlgCVR.h:DlgCVR.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {F53AD0C7-6269-4702-974A-86DAC228E0C0}
# 	1:22:IDD_SUBDLG_PRODUCT_ACS:219
# 	2:16:Resource Include:resource.h
# 	2:21:CLASS: CDlgProductAcs:CDlgProductAcs
# 	2:10:ENUM: enum:enum
# 	2:17:DlgProductAcs.cpp:DlgProductAcs.cpp
# 	2:19:Application Include:clientdemo.h
# 	2:15:DlgProductAcs.h:DlgProductAcs.h
# 	2:22:IDD_SUBDLG_PRODUCT_ACS:IDD_SUBDLG_PRODUCT_ACS
# End Section
# Section ClientDemo : {B67A6555-F1C6-418F-9A35-FA3CAA4C4AF7}
# 	1:19:IDD_DLG_COURSE_LIST:328
# 	2:16:Resource Include:resource.h
# 	2:20:CLASS: DlgCourseList:DlgCourseList
# 	2:15:DlgCourseList.h:DlgCourseList.h
# 	2:10:ENUM: enum:enum
# 	2:17:DlgCourseList.cpp:DlgCourseList.cpp
# 	2:19:Application Include:clientdemo.h
# 	2:19:IDD_DLG_COURSE_LIST:IDD_DLG_COURSE_LIST
# End Section
# Section ClientDemo : {4A3FD95B-4EF8-4BE8-A9F7-632519BF4B4E}
# 	1:29:IDD_DLG_RECORD_HOST_FRAME_CFG:315
# 	2:16:Resource Include:resource.h
# 	2:23:DlgRecordHostFrameCfg.h:DlgRecordHostFrameCfg1.h
# 	2:25:DlgRecordHostFrameCfg.cpp:DlgRecordHostFrameCfg1.cpp
# 	2:29:CLASS: CDlgRecordHostFrameCfg:CDlgRecordHostFrameCfg
# 	2:10:ENUM: enum:enum
# 	2:29:IDD_DLG_RECORD_HOST_FRAME_CFG:IDD_DLG_RECORD_HOST_FRAME_CFG
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {586080B7-5FDD-4494-ABA8-7D3382C02E72}
# 	1:30:IDD_DIG_EVENT_CARD_LINKAGE_CFG:300
# 	2:16:Resource Include:resource.h
# 	2:25:DlgAcsCardUserInfoCfg.cpp:DlgAcsCardUserInfoCfg1.cpp
# 	2:10:ENUM: enum:enum
# 	2:29:CLASS: CDlgAcsCardUserInfoCfg:CDlgAcsCardUserInfoCfg
# 	2:23:DlgAcsCardUserInfoCfg.h:DlgAcsCardUserInfoCfg1.h
# 	2:25:IDD_DLG_ACS_CARD_USERINFO:IDD_DLG_ACS_CARD_USERINFO
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {664F5D5A-CA96-4B8F-93E5-00D0301EEE87}
# 	1:25:IDD_DLG_ACS_CARD_USERINFO:301
# 	2:16:Resource Include:resource.h
# 	2:25:DlgAcsCardUserInfoCfg.cpp:DlgAcsCardUserInfoCfg1.cpp
# 	2:10:ENUM: enum:enum
# 	2:29:CLASS: CDlgAcsCardUserInfoCfg:CDlgAcsCardUserInfoCfg
# 	2:23:DlgAcsCardUserInfoCfg.h:DlgAcsCardUserInfoCfg1.h
# 	2:25:IDD_DLG_ACS_CARD_USERINFO:IDD_DLG_ACS_CARD_USERINFO
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {A9824EC2-BE99-48A7-BDB7-623ECD2C031C}
# 	1:24:IDD_DLG_SMART_SEARCH_PIC:308
# 	2:16:Resource Include:resource.h
# 	2:25:DlgSmartSearchPicture.cpp:DlgSmartSearchPicture.cpp
# 	2:29:CLASS: CDlgSmartSearchPicture:CDlgSmartSearchPicture
# 	2:24:IDD_DLG_SMART_SEARCH_PIC:IDD_DLG_SMART_SEARCH_PIC
# 	2:10:ENUM: enum:enum
# 	2:23:DlgSmartSearchPicture.h:DlgSmartSearchPicture.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {1A53BCF0-2E20-4AAC-808C-B5E7A7BB0C24}
# 	1:20:IDD_DLG_GATEWAY_CARD:299
# 	2:16:Resource Include:resource.h
# 	2:15:DlgAcsSnapCfg.h:DlgAcsSnapCfg.h
# 	2:10:ENUM: enum:enum
# 	2:20:IDD_DLG_ACS_SNAP_CFG:IDD_DLG_ACS_SNAP_CFG
# 	2:17:DlgAcsSnapCfg.cpp:DlgAcsSnapCfg.cpp
# 	2:20:CLASS: DlgAcsSnapCfg:DlgAcsSnapCfg
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {A817E26E-54EF-4BB9-84BE-0041EBA92E50}
# 	1:25:IDD_DLG_VIDEOWALL_ELSESET:230
# 	2:16:Resource Include:resource.h
# 	2:24:CLASS: CDlgVideoWallElse:CDlgVideoWallElse
# 	2:25:IDD_DLG_VIDEOWALL_ELSESET:IDD_DLG_VIDEOWALL_ELSESET
# 	2:20:DlgVideoWallElse.cpp:DlgVideoWallElse.cpp
# 	2:10:ENUM: enum:enum
# 	2:18:DlgVideoWallElse.h:DlgVideoWallElse.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {7A1A5203-001D-447C-857A-E32688BA5E92}
# 	1:30:IDD_DIG_EVENT_CARD_LINKAGE_CFG:300
# 	2:16:Resource Include:resource.h
# 	2:24:DlgEventCardLinkageCfg.h:DlgEventCardLinkageCfg1.h
# 	2:26:DlgEventCardLinkageCfg.cpp:DlgEventCardLinkageCfg1.cpp
# 	2:29:CLASS: DlgEventCardLinkageCfg:DlgEventCardLinkageCfg
# 	2:10:ENUM: enum:enum
# 	2:23:CLASS: CDlgDecWinStatus:CDlgDecWinStatus
# 	2:19:Application Include:clientdemo.h
# 	2:30:IDD_DIG_EVENT_CARD_LINKAGE_CFG:IDD_DIG_EVENT_CARD_LINKAGE_CFG
# End Section
# Section ClientDemo : {81A838EC-BDD0-4F7F-BF56-72AFCB3EEFB7}
# 	1:28:IDD_DIG_ANTI_SNEAK_HOST_CFG1:282
# 	2:16:Resource Include:resource.h
# 	2:21:DlgAntiSneakHostCfg.h:DlgAntiSneakHostCfg.h
# 	2:10:ENUM: enum:enum
# 	2:26:CLASS: DlgAntiSneakHostCfg:DlgAntiSneakHostCfg
# 	2:27:IDD_DIG_ANTI_SNEAK_HOST_CFG:IDD_DIG_ANTI_SNEAK_HOST_CFG1
# 	2:23:DlgAntiSneakHostCfg.cpp:DlgAntiSneakHostCfg.cpp
# 	2:19:Application Include:clientdemo.h
# 	2:16:DlgITSBaseInfo.h:DlgITSBaseInfo.h
# 	2:18:DlgITSBaseInfo.cpp:DlgITSBaseInfo.cpp
# 	2:22:CLASS: CDlgITSBaseInfo:CDlgITSBaseInfo
# 	2:24:IDD_DLG_ITS_GET_BASEINFO:IDD_DLG_ITS_GET_BASEINFO
# End Section
# Section ClientDemo : {2F9071CB-4969-4BE8-9DB5-DAB995B846D9}
# 	1:21:IDD_DLG_CLOUD_STORAGE:327
# 	2:16:Resource Include:resource.h
# 	2:23:CLASS: CDlgCloudStorage:CDlgCloudStorage
# 	2:19:DlgCloudStorage.cpp:DlgCloudStorage.cpp
# 	2:10:ENUM: enum:enum
# 	2:21:IDD_DLG_CLOUD_STORAGE:IDD_DLG_CLOUD_STORAGE
# 	2:19:Application Include:clientdemo.h
# 	2:17:DlgCloudStorage.h:DlgCloudStorage.h
# End Section
# Section ClientDemo : {CC41842C-4255-4CB0-A1F0-8C51245FC7F7}
# 	1:19:IDD_DLG_ACS_SMS_CFG:268
# 	2:16:Resource Include:resource.h
# 	2:19:CLASS: DlgAcsSmsCfg:DlgAcsSmsCfg
# 	2:16:DlgAcsSmsCfg.cpp:DlgAcsSmsCfg.cpp
# 	2:19:IDD_DLG_ACS_SMS_CFG:IDD_DLG_ACS_SMS_CFG
# 	2:10:ENUM: enum:enum
# 	2:14:DlgAcsSmsCfg.h:DlgAcsSmsCfg.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {495A5CEB-23F4-4FB0-BFD1-660C1479537F}
# 	1:38:IDD_DLG_RECORD_HOST_BACKGROUND_PIC_CFG:324
# 	2:16:Resource Include:resource.h
# 	2:33:DlgRecordHostBackgroundPicCfg.cpp:DlgRecordHostBackgroundPicCfg1.cpp
# 	2:10:ENUM: enum:enum
# 	2:37:CLASS: CDlgRecordHostBackgroundPicCfg:CDlgRecordHostBackgroundPicCfg
# 	2:31:DlgRecordHostBackgroundPicCfg.h:DlgRecordHostBackgroundPicCfg1.h
# 	2:19:Application Include:clientdemo.h
# 	2:38:IDD_DLG_RECORD_HOST_BACKGROUND_PIC_CFG:IDD_DLG_RECORD_HOST_BACKGROUND_PIC_CFG
# End Section
# Section ClientDemo : {CC235959-24D2-45A3-BE5F-92BA470B268B}
# 	1:24:IDD_DLG_ITS_GET_BASEINFO:113
# 	2:16:Resource Include:resource.h
# 	2:17:DlgVCAAlarmLogo.h:DlgVCAAlarmLogo.h
# 	2:22:CLASS: DlgVCAAlarmLogo:DlgVCAAlarmLogo
# 	2:19:DlgVCAAlarmLogo.cpp:DlgVCAAlarmLogo.cpp
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# 	2:16:DlgITSBaseInfo.h:DlgITSBaseInfo.h
# 	2:18:DlgITSBaseInfo.cpp:DlgITSBaseInfo.cpp
# 	2:22:CLASS: CDlgITSBaseInfo:CDlgITSBaseInfo
# 	2:24:IDD_DLG_ITS_GET_BASEINFO:IDD_DLG_ITS_GET_BASEINFO
# End Section
# Section ClientDemo : {0EFB9BCA-A308-4AEC-814A-CB4615A57982}
# 	1:29:IDD_DLG_RECORD_HOST_VIDEO_CFG:310
# 	2:16:Resource Include:resource.h
# 	2:29:IDD_DLG_RECORD_HOST_VIDEO_CFG:IDD_DLG_RECORD_HOST_VIDEO_CFG
# 	2:10:ENUM: enum:enum
# 	2:29:CLASS: CDlgRecordHostVideoCfg:CDlgRecordHostVideoCfg
# 	2:25:DlgRecordHostVideoCfg.cpp:DlgRecordHostVideoCfg1.cpp
# 	2:23:DlgRecordHostVideoCfg.h:DlgRecordHostVideoCfg1.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {23A387E2-8B1C-4DB5-BB2B-B28E1BBFD7BA}
# 	1:21:IDD_DIG_RECORD_STATUS:329
# 	2:16:Resource Include:resource.h
# 	2:19:DlgRecordStatus.cpp:DlgRecordStatus.cpp
# 	2:23:CLASS: CDlgRecordStatus:CDlgRecordStatus
# 	2:10:ENUM: enum:enum
# 	2:21:IDD_DIG_RECORD_STATUS:IDD_DIG_RECORD_STATUS
# 	2:19:Application Include:clientdemo.h
# 	2:17:DlgRecordStatus.h:DlgRecordStatus.h
# End Section
# Section ClientDemo : {48D0927D-82B2-4A9F-8C3D-7812174A0536}
# 	1:24:IDD_DLG_AC_CARDREADERCFG:212
# 	2:16:Resource Include:resource.h
# 	2:20:DlgCardReaderCfg.cpp:DlgCardReaderCfg.cpp
# 	2:24:IDD_DLG_AC_CARDREADERCFG:IDD_DLG_AC_CARDREADERCFG
# 	2:10:ENUM: enum:enum
# 	2:24:CLASS: CDlgCardReaderCfg:CDlgCardReaderCfg
# 	2:18:DlgCardReaderCfg.h:DlgCardReaderCfg.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {F7D361DF-1A56-47EF-8123-B535F4A62737}
# 	1:27:IDD_DLG_ACCESSCARD_WEEKPLAN:221
# 	2:16:Resource Include:resource.h
# 	2:18:DlgWallControl.cpp:DlgWallControl1.cpp
# 	2:16:DlgWallControl.h:DlgWallControl1.h
# 	2:10:ENUM: enum:enum
# 	2:22:CLASS: CDlgWallControl:CDlgWallControl
# 	2:19:Application Include:clientdemo.h
# 	2:29:IDD_Dlg_VIDEOWALL_WALLCONTORL:IDD_Dlg_VIDEOWALL_WALLCONTORL1
# End Section
# Section ClientDemo : {77BCB671-7B08-4BDF-9314-A9BF85994733}
# 	1:21:IDD_DLG_VCA_ALARMLOGO:225
# 	2:16:Resource Include:resource.h
# 	2:33:DlgRemoteStreamRecordSchedule.cpp:DlgRemoteStreamRecordSchedule.cpp
# 	2:31:IDD_DLG_REMOTE_RECORD_SCHEDULE1:IDD_DLG_REMOTE_RECORD_SCHEDULE1
# 	2:10:ENUM: enum:enum
# 	2:37:CLASS: CDlgRemoteStreamRecordSchedule:CDlgRemoteStreamRecordSchedule
# 	2:19:Application Include:clientdemo.h
# 	2:31:DlgRemoteStreamRecordSchedule.h:DlgRemoteStreamRecordSchedule.h
# End Section
# Section ClientDemo : {11794CB1-819F-4B90-9024-BE2C00BA0D6B}
# 	1:23:IDD_DLG_DEC_WIN_STATUS1:226
# 	2:16:Resource Include:resource.h
# 	2:19:DlgDecWinStatus.cpp:DlgDecWinStatus1.cpp
# 	2:22:IDD_DLG_DEC_WIN_STATUS:IDD_DLG_DEC_WIN_STATUS1
# 	2:17:DlgDecWinStatus.h:DlgDecWinStatus1.h
# 	2:10:ENUM: enum:enum
# 	2:23:CLASS: CDlgDecWinStatus:CDlgDecWinStatus
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {CAD3294D-8F29-435F-9E9E-F2A4B3F305AF}
# 	1:30:IDD_Dlg_VIDEOWALL_WALLCONTORL1:244
# 	2:16:Resource Include:resource.h
# 	2:18:DlgWallControl.cpp:DlgWallControl1.cpp
# 	2:16:DlgWallControl.h:DlgWallControl1.h
# 	2:10:ENUM: enum:enum
# 	2:22:CLASS: CDlgWallControl:CDlgWallControl
# 	2:19:Application Include:clientdemo.h
# 	2:29:IDD_Dlg_VIDEOWALL_WALLCONTORL:IDD_Dlg_VIDEOWALL_WALLCONTORL1
# End Section
# Section ClientDemo : {ACF3C939-30B7-454F-AF19-43EF5FEDD288}
# 	1:20:IDD_DLG_GATEWAY_CARD:215
# 	2:16:Resource Include:resource.h
# 	2:19:DlgGatewayCardCfg.h:DlgGatewayCardCfg.h
# 	2:20:IDD_DLG_GATEWAY_CARD:IDD_DLG_GATEWAY_CARD
# 	2:10:ENUM: enum:enum
# 	2:25:CLASS: CDlgGatewayCardCfg:CDlgGatewayCardCfg
# 	2:21:DlgGatewayCardCfg.cpp:DlgGatewayCardCfg.cpp
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {FD725C6D-B659-48AD-A24B-0A7595CCC7BB}
# 	1:12:IDD_DLG_ACDC:214
# 	2:16:Resource Include:resource.h
# 	2:21:CLASS: CDlgDoorConfig:CDlgDoorConfig
# 	2:12:IDD_DLG_ACDC:IDD_DLG_ACDC
# 	2:10:ENUM: enum:enum
# 	2:17:DlgDoorConfig.cpp:DlgDoorConfig.cpp
# 	2:15:DlgDoorConfig.h:DlgDoorConfig.h
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {C0951E9F-4796-4842-8950-761AD82542C5}
# 	1:36:IDD_DLG_RECORD_HOST_AUDIO_EFFECT_CFG:316
# 	2:16:Resource Include:resource.h
# 	2:36:IDD_DLG_RECORD_HOST_AUDIO_EFFECT_CFG:IDD_DLG_RECORD_HOST_AUDIO_EFFECT_CFG
# 	2:10:ENUM: enum:enum
# 	2:32:DlgRecordHostAudioEffectiveCfg.h:DlgRecordHostAudioEffectiveCfg1.h
# 	2:34:DlgRecordHostAudioEffectiveCfg.cpp:DlgRecordHostAudioEffectiveCfg1.cpp
# 	2:38:CLASS: CDlgRecordHostAudioEffectiveCfg:CDlgRecordHostAudioEffectiveCfg
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {3D1896DD-6AD4-4E0D-BEDF-61DE8FC10258}
# 	1:18:IDD_DLG_LCD_SPLICE:181
# 	2:16:Resource Include:resource.h
# 	2:14:DlgLcdSplice.h:DlgLcdSplice.h
# 	2:16:DlgLcdSplice.cpp:DlgLcdSplice.cpp
# 	2:20:CLASS: CDlgLcdSplice:CDlgLcdSplice
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# 	2:18:IDD_DLG_LCD_SPLICE:IDD_DLG_LCD_SPLICE
# End Section
# Section ClientDemo : {0291907E-43BA-498B-9105-260CEBB79621}
# 	1:25:IDD_DLG_LCD_MATRIX_SWITCH:172
# 	2:16:Resource Include:resource.h
# 	2:25:IDD_DLG_LCD_MATRIX_SWITCH:IDD_DLG_LCD_MATRIX_SWITCH
# 	2:22:DlgLcdMatrixSwitch.cpp:DlgLcdMatrixSwitch.cpp
# 	2:20:DlgLcdMatrixSwitch.h:DlgLcdMatrixSwitch.h
# 	2:10:ENUM: enum:enum
# 	2:26:CLASS: CDlgLcdMatrixSwitch:CDlgLcdMatrixSwitch
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {746DA24B-A603-4C44-986D-5830E7B5BEC3}
# 	1:30:IDD_DLG_SCREEN_EXTERNAL_MATRIX:199
# 	2:16:Resource Include:resource.h
# 	2:25:DlgAcsCardUserInfoCfg.cpp:DlgAcsCardUserInfoCfg1.cpp
# 	2:10:ENUM: enum:enum
# 	2:29:CLASS: CDlgAcsCardUserInfoCfg:CDlgAcsCardUserInfoCfg
# 	2:23:DlgAcsCardUserInfoCfg.h:DlgAcsCardUserInfoCfg1.h
# 	2:25:IDD_DLG_ACS_CARD_USERINFO:IDD_DLG_ACS_CARD_USERINFO
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {6592327B-D7FE-4FB0-B361-C05154014B90}
# 	1:26:IDD_DLG_GBT28181_PROTOCOL2:242
# 	2:16:Resource Include:resource.h
# 	2:35:CLASS: CDlgGBT28181ProAccessUniform:CDlgGBT28181ProAccessUniform
# 	2:27:DlgGBT28181ProtocolAccess.h:DlgGBT28181ProtocolAccess2.h
# 	2:10:ENUM: enum:enum
# 	2:17:CLASS: GBT28181BM:GBT28181BM
# 	2:25:IDD_DLG_GBT28181_PROTOCOL:IDD_DLG_GBT28181_PROTOCOL1
# 	2:19:Application Include:clientdemo.h
# 	2:33:CLASS: CDlgGBT28181ProtocolAccess:CDlgGBT28181ProtocolAccess
# 	2:29:DlgGBT28181ProtocolAccess.cpp:DlgGBT28181ProtocolAccess1.cpp
# End Section
# Section ClientDemo : {277EC097-D9CF-48C1-BF23-F63AB8BB9EAA}
# 	1:27:IDD_DIG_ANTI_SNEAK_HOST_CFG:302
# 	2:16:Resource Include:resource.h
# 	2:21:DlgAntiSneakHostCfg.h:DlgAntiSneakHostCfg.h
# 	2:10:ENUM: enum:enum
# 	2:26:CLASS: DlgAntiSneakHostCfg:DlgAntiSneakHostCfg
# 	2:27:IDD_DIG_ANTI_SNEAK_HOST_CFG:IDD_DIG_ANTI_SNEAK_HOST_CFG
# 	2:23:DlgAntiSneakHostCfg.cpp:DlgAntiSneakHostCfg.cpp
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {724B12CA-E7EE-4B24-A606-3844581C992B}
# 	1:24:IDD_DLG_ACS_FINGER_PRINT:261
# 	2:16:Resource Include:resource.h
# 	2:24:IDD_DLG_ACS_FINGER_PRINT:IDD_DLG_ACS_FINGER_PRINT
# 	2:22:DlgAcsFingerPrintCfg.h:DlgAcsFingerPrintCfg.h
# 	2:10:ENUM: enum:enum
# 	2:24:DlgAcsFingerPrintCfg.cpp:DlgAcsFingerPrintCfg.cpp
# 	2:19:Application Include:clientdemo.h
# 	2:27:CLASS: DlgAcsFingerPrintCfg:DlgAcsFingerPrintCfg
# End Section
# Section ClientDemo : {BC3A29A9-0BAA-4CEF-982F-1BB56970110B}
# 	1:27:IDD_DLG_ALARMHOST_NET_USER1:211
# 	2:16:Resource Include:resource.h
# 	2:19:DlgMultiCardCfg.cpp:DlgMultiCardCfg.cpp
# 	2:17:DlgMultiCardCfg.h:DlgMultiCardCfg.h
# 	2:18:IDD_DLG_MULTI_CARD:IDD_DLG_MULTI_CARD
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {895F296F-BAE5-4303-8168-12A622CC2E62}
# 	1:29:IDD_DLG_DIRECTED_STRATEGY_CFG:317
# 	2:34:DlgRecordHostDirectedStrategyCfg.h:DlgRecordHostDirectedStrategyCfg1.h
# 	2:29:IDD_DLG_DIRECTED_STRATEGY_CFG:IDD_DLG_DIRECTED_STRATEGY_CFG
# 	2:16:Resource Include:resource.h
# 	2:40:CLASS: CDlgRecordHostDirectedStrategyCfg:CDlgRecordHostDirectedStrategyCfg
# 	2:10:ENUM: enum:enum
# 	2:36:DlgRecordHostDirectedStrategyCfg.cpp:DlgRecordHostDirectedStrategyCfg1.cpp
# 	2:19:Application Include:clientdemo.h
# 	2:27:CLASS: DlgAcsFingerPrintCfg:DlgAcsFingerPrintCfg
# End Section
