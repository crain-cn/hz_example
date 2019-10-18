# Microsoft Developer Studio Project File - Name="raindiy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=raindiy - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "raindiy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "raindiy.mak" CFG="raindiy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "raindiy - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "raindiy - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "raindiy - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "raindiy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"Release/raindiy.pch" /Yu"stdafx.h" /Fo"Release/" /Fd"Release/" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "raindiy - Win32 Release"
# Name "raindiy - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\create.cpp
# End Source File
# Begin Source File

SOURCE=.\DerverLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\myprocess.cpp
# End Source File
# Begin Source File

SOURCE=.\MyProcess1.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenMyFile.cpp
# End Source File
# Begin Source File

SOURCE=.\raindiy.cpp
# End Source File
# Begin Source File

SOURCE=.\rainmain.cpp
# End Source File
# Begin Source File

SOURCE=.\RainPe.cpp
# End Source File
# Begin Source File

SOURCE=.\RainService.cpp
# End Source File
# Begin Source File

SOURCE=.\RainSSDT.cpp
# End Source File
# Begin Source File

SOURCE=.\RainStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadPE.cpp
# End Source File
# Begin Source File

SOURCE=.\reateListView.cpp
# End Source File
# Begin Source File

SOURCE=.\rightmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\SDTShadowRestore.cpp
# End Source File
# Begin Source File

SOURCE=.\Shellicon.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\create.h
# End Source File
# Begin Source File

SOURCE=.\DerverLoad.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\myprocess.h
# End Source File
# Begin Source File

SOURCE=.\MyProcess1.h
# End Source File
# Begin Source File

SOURCE=.\OpenMyFile.h
# End Source File
# Begin Source File

SOURCE=.\PE.H
# End Source File
# Begin Source File

SOURCE=.\rainmain.h
# End Source File
# Begin Source File

SOURCE=.\rainpe.h
# End Source File
# Begin Source File

SOURCE=.\RainService.h
# End Source File
# Begin Source File

SOURCE=.\RainSSDT.h
# End Source File
# Begin Source File

SOURCE=.\RainStatus.h
# End Source File
# Begin Source File

SOURCE=.\ReadPE.h
# End Source File
# Begin Source File

SOURCE=.\reateListView.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\rightmenu.h
# End Source File
# Begin Source File

SOURCE=.\SDTShadowRestore.h
# End Source File
# Begin Source File

SOURCE=.\Shellicon.h
# End Source File
# Begin Source File

SOURCE=.\SkinMagicLib.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\rain.ico
# End Source File
# Begin Source File

SOURCE=.\res\rain1.ico
# End Source File
# Begin Source File

SOURCE=.\raindiy.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\corona.smf
# End Source File
# Begin Source File

SOURCE=.\res\Devior.smf
# End Source File
# Begin Source File

SOURCE=.\res\fish.smf
# End Source File
# Begin Source File

SOURCE=.\res\King.smf
# End Source File
# Begin Source File

SOURCE=.\res\Kromo.smf
# End Source File
# Begin Source File

SOURCE=".\res\x-plus.smf"
# End Source File
# Begin Source File

SOURCE=.\res\xpblue.smf
# End Source File
# Begin Source File

SOURCE=.\res\xpgrean.smf
# End Source File
# Begin Source File

SOURCE=.\res\xpsteel.smf
# End Source File
# Begin Source File

SOURCE=.\res\DETOURS.lib
# End Source File
# Begin Source File

SOURCE=.\res\SkinMagicLib.lib
# End Source File
# End Target
# End Project
