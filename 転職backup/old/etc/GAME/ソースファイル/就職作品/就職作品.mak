# Microsoft Developer Studio Generated NMAKE File, Based on 就職作品.dsp
!IF "$(CFG)" == ""
CFG=就職作品 - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの 就職作品 - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "就職作品 - Win32 Release" && "$(CFG)" != "就職作品 - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "就職作品.mak" CFG="就職作品 - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "就職作品 - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "就職作品 - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "就職作品 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\就職作品.exe"


CLEAN :
	-@erase "$(INTDIR)\bg.obj"
	-@erase "$(INTDIR)\billbord.obj"
	-@erase "$(INTDIR)\enemy.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\player.obj"
	-@erase "$(INTDIR)\tama.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\就職作品.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\就職作品.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\就職作品.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\就職作品.pdb" /machine:I386 /out:"$(OUTDIR)\就職作品.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bg.obj" \
	"$(INTDIR)\billbord.obj" \
	"$(INTDIR)\enemy.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\model.obj" \
	"$(INTDIR)\player.obj" \
	"$(INTDIR)\tama.obj"

"$(OUTDIR)\就職作品.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "就職作品 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\就職作品.exe"


CLEAN :
	-@erase "$(INTDIR)\bg.obj"
	-@erase "$(INTDIR)\billbord.obj"
	-@erase "$(INTDIR)\enemy.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\player.obj"
	-@erase "$(INTDIR)\tama.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\就職作品.exe"
	-@erase "$(OUTDIR)\就職作品.ilk"
	-@erase "$(OUTDIR)\就職作品.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\就職作品.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\就職作品.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\就職作品.pdb" /debug /machine:I386 /out:"$(OUTDIR)\就職作品.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bg.obj" \
	"$(INTDIR)\billbord.obj" \
	"$(INTDIR)\enemy.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\model.obj" \
	"$(INTDIR)\player.obj" \
	"$(INTDIR)\tama.obj"

"$(OUTDIR)\就職作品.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("就職作品.dep")
!INCLUDE "就職作品.dep"
!ELSE 
!MESSAGE Warning: cannot find "就職作品.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "就職作品 - Win32 Release" || "$(CFG)" == "就職作品 - Win32 Debug"
SOURCE=.\bg.cpp

"$(INTDIR)\bg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\billbord.cpp

"$(INTDIR)\billbord.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\enemy.cpp

"$(INTDIR)\enemy.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\model.cpp

"$(INTDIR)\model.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\player.cpp

"$(INTDIR)\player.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tama.cpp

"$(INTDIR)\tama.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

