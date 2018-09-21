# Microsoft Developer Studio Project File - Name="TatniumD3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TatniumD3D - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TatniumD3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TatniumD3D.mak" CFG="TatniumD3D - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TatniumD3D - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TatniumD3D - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TatniumD3D - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "TATNIUMD3D_EXPORTS" /D "_MBCS" /YX /GF /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "TATNIUMD3D_EXPORTS" /D "_MBCS" /YX /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:IX86 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib Dxguid.lib /nologo /subsystem:windows /dll /machine:IX86 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "TatniumD3D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "TATNIUMD3D_EXPORTS" /D "_MBCS" /FR /YX /GZ /c
# ADD CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "TATNIUMD3D_EXPORTS" /D "_MBCS" /FR /YX /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:IX86 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib Dxguid.lib detours.lib ddraw.lib /nologo /subsystem:windows /dll /machine:IX86 /out:".\Debug/catalyst.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /incremental:no /debug

!ENDIF 

# Begin Target

# Name "TatniumD3D - Win32 Release"
# Name "TatniumD3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "d3d9_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CRC32.cpp
DEP_CPP_CRC32=\
	".\CRC32.h"\
	".\main.h"\
	
# End Source File
# Begin Source File

SOURCE=d3d9dev.cpp
DEP_CPP_D3D9D=\
	".\CRC32.h"\
	".\CVAR.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\main.h"\
	".\MemHacks.h"\
	".\Menu.h"\
	".\Radar.h"\
	".\Zoom.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	

!IF  "$(CFG)" == "TatniumD3D - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "TatniumD3D - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=d3d9int.cpp
DEP_CPP_D3D9I=\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\main.h"\
	".\Menu.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	

!IF  "$(CFG)" == "TatniumD3D - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "TatniumD3D - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=d3d9tex.cpp
DEP_CPP_D3D9T=\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\main.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	

!IF  "$(CFG)" == "TatniumD3D - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "TatniumD3D - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3drender.cpp
DEP_CPP_D3DRE=\
	".\d3drender.h"\
	".\main.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	
# End Source File
# End Group
# Begin Group "ddraw"

# PROP Default_Filter ""
# End Group
# Begin Group "hax c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Hooks.cpp
DEP_CPP_HOOKS=\
	".\AddLog.h"\
	".\CVAR.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\main.h"\
	".\MemHacks.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Input.cpp
DEP_CPP_INPUT=\
	".\CVAR.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\Input.h"\
	".\main.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MemHacks.cpp
DEP_CPP_MEMHA=\
	".\CVAR.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\main.h"\
	".\MemHacks.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Zoom.cpp
DEP_CPP_ZOOM_=\
	".\CVAR.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\main.h"\
	".\Zoom.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	
# End Source File
# End Group
# Begin Group "users c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AmHttpSocket.cpp
DEP_CPP_AMHTT=\
	".\AmHttpSocket.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Login.cpp
DEP_CPP_LOGIN=\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Login.h"\
	".\Menu.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Menu.cpp
DEP_CPP_MENU_=\
	".\AmHttpSocket.h"\
	".\CVAR.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\Login.h"\
	".\main.h"\
	".\MemHacks.h"\
	".\Menu.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	
# End Source File
# End Group
# Begin Source File

SOURCE=d3d9.cpp
DEP_CPP_D3D9_=\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\main.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	

!IF  "$(CFG)" == "TatniumD3D - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "TatniumD3D - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=main.cpp
DEP_CPP_MAIN_=\
	".\AmHttpSocket.h"\
	".\CRC32.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\Input.h"\
	".\main.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	

!IF  "$(CFG)" == "TatniumD3D - Win32 Release"

# ADD CPP /nologo /GX /O2

!ELSEIF  "$(CFG)" == "TatniumD3D - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Radar.cpp
DEP_CPP_RADAR=\
	".\CVAR.h"\
	".\d3d9.h"\
	".\d3d9dev.h"\
	".\d3d9int.h"\
	".\d3d9tex.h"\
	".\d3drender.h"\
	".\Hooks.h"\
	".\main.h"\
	".\Radar.h"\
	{$(INCLUDE)}"d3d9.h"\
	{$(INCLUDE)}"d3d9caps.h"\
	{$(INCLUDE)}"d3d9types.h"\
	{$(INCLUDE)}"d3dx9.h"\
	{$(INCLUDE)}"d3dx9anim.h"\
	{$(INCLUDE)}"d3dx9core.h"\
	{$(INCLUDE)}"d3dx9effect.h"\
	{$(INCLUDE)}"d3dx9math.h"\
	{$(INCLUDE)}"d3dx9math.inl"\
	{$(INCLUDE)}"d3dx9mesh.h"\
	{$(INCLUDE)}"d3dx9shader.h"\
	{$(INCLUDE)}"d3dx9shape.h"\
	{$(INCLUDE)}"d3dx9tex.h"\
	{$(INCLUDE)}"d3dx9xof.h"\
	
# End Source File
# Begin Source File

SOURCE=.\Udtr.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "d3d9_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CRC32.h
# End Source File
# Begin Source File

SOURCE=d3d9dev.h
# End Source File
# Begin Source File

SOURCE=d3d9int.h
# End Source File
# Begin Source File

SOURCE=d3d9tex.h
# End Source File
# Begin Source File

SOURCE=.\d3drender.h
# End Source File
# End Group
# Begin Group "hax"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Hooks.h
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# Begin Source File

SOURCE=.\MemHacks.h
# End Source File
# Begin Source File

SOURCE=.\Zoom.h
# End Source File
# End Group
# Begin Group "users h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AddLog.h
# End Source File
# Begin Source File

SOURCE=.\AmHttpSocket.h
# End Source File
# Begin Source File

SOURCE=.\CVAR.h
# End Source File
# Begin Source File

SOURCE=.\Login.h
# End Source File
# Begin Source File

SOURCE=.\Menu.h
# End Source File
# End Group
# Begin Group "ddraw h"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=d3d9.h
# End Source File
# Begin Source File

SOURCE=main.h
# End Source File
# Begin Source File

SOURCE=.\Radar.h
# End Source File
# Begin Source File

SOURCE=.\Updtr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Reminder.txt
# End Source File
# End Target
# End Project
