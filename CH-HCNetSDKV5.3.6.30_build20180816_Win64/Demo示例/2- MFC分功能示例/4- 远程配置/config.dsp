# Microsoft Developer Studio Project File - Name="config" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=config - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "config.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "config.mak" CFG="config - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "config - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "config - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "config - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../头文件" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "DEMO_LAN_CN" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib winmm.lib /nologo /subsystem:windows /pdb:"bin/config.pdb" /machine:I386 /out:"bin/config.exe" /libpath:"../../../库文件"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "config - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../头文件" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib winmm.lib /nologo /subsystem:windows /pdb:"bin/config.pdb" /debug /machine:I386 /out:"bin/config.exe" /pdbtype:sept /libpath:"../../../库文件"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "config - Win32 Release"
# Name "config - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\config.cpp
# End Source File
# Begin Source File

SOURCE=.\config.rc
# End Source File
# Begin Source File

SOURCE=.\configDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExceptionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPPPCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInPtzInvoke.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideArea.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteMotionDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecordSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteShowString.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInLost.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSerialCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\configDlg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgExceptionCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPPPCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInHandle.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInPtzInvoke.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideArea.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteMotionDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecordSchedule.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteShowString.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInLost.h
# End Source File
# Begin Source File

SOURCE=.\DlgSerialCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserCfg.h
# End Source File
# Begin Source File

SOURCE=.\GeneralDef.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\config.ico
# End Source File
# Begin Source File

SOURCE=.\res\config.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
