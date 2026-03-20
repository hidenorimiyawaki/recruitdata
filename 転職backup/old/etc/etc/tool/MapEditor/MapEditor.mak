# Microsoft Developer Studio Generated NMAKE File, Based on MapEditor.dsp
!IF "$(CFG)" == ""
CFG=MapEditor - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの MapEditor - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "MapEditor - Win32 Release" && "$(CFG)" != "MapEditor - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "MapEditor.mak" CFG="MapEditor - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "MapEditor - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "MapEditor - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MapEditor - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MapEditor.exe"


CLEAN :
	-@erase "$(INTDIR)\AttrData.obj"
	-@erase "$(INTDIR)\BmpDialog.obj"
	-@erase "$(INTDIR)\DataDialog.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MapData.obj"
	-@erase "$(INTDIR)\MapEditor.obj"
	-@erase "$(INTDIR)\MapEditor.pch"
	-@erase "$(INTDIR)\MapEditor.res"
	-@erase "$(INTDIR)\MapEditorDoc.obj"
	-@erase "$(INTDIR)\MapEditorView.obj"
	-@erase "$(INTDIR)\SizeDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MapEditor.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MapEditor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\MapEditor.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MapEditor.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MapEditor.pdb" /machine:I386 /out:"$(OUTDIR)\MapEditor.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AttrData.obj" \
	"$(INTDIR)\BmpDialog.obj" \
	"$(INTDIR)\DataDialog.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MapData.obj" \
	"$(INTDIR)\MapEditor.obj" \
	"$(INTDIR)\MapEditorDoc.obj" \
	"$(INTDIR)\MapEditorView.obj" \
	"$(INTDIR)\SizeDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MapEditor.res"

"$(OUTDIR)\MapEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MapEditor.exe"


CLEAN :
	-@erase "$(INTDIR)\AttrData.obj"
	-@erase "$(INTDIR)\BmpDialog.obj"
	-@erase "$(INTDIR)\DataDialog.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MapData.obj"
	-@erase "$(INTDIR)\MapEditor.obj"
	-@erase "$(INTDIR)\MapEditor.pch"
	-@erase "$(INTDIR)\MapEditor.res"
	-@erase "$(INTDIR)\MapEditorDoc.obj"
	-@erase "$(INTDIR)\MapEditorView.obj"
	-@erase "$(INTDIR)\SizeDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MapEditor.exe"
	-@erase "$(OUTDIR)\MapEditor.ilk"
	-@erase "$(OUTDIR)\MapEditor.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MapEditor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\MapEditor.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MapEditor.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MapEditor.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MapEditor.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AttrData.obj" \
	"$(INTDIR)\BmpDialog.obj" \
	"$(INTDIR)\DataDialog.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MapData.obj" \
	"$(INTDIR)\MapEditor.obj" \
	"$(INTDIR)\MapEditorDoc.obj" \
	"$(INTDIR)\MapEditorView.obj" \
	"$(INTDIR)\SizeDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MapEditor.res"

"$(OUTDIR)\MapEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MapEditor.dep")
!INCLUDE "MapEditor.dep"
!ELSE 
!MESSAGE Warning: cannot find "MapEditor.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MapEditor - Win32 Release" || "$(CFG)" == "MapEditor - Win32 Debug"
SOURCE=.\AttrData.cpp

"$(INTDIR)\AttrData.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\BmpDialog.cpp

"$(INTDIR)\BmpDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\DataDialog.cpp

"$(INTDIR)\DataDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\MapData.cpp

"$(INTDIR)\MapData.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\MapEditor.cpp

"$(INTDIR)\MapEditor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\MapEditor.rc

"$(INTDIR)\MapEditor.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MapEditorDoc.cpp

"$(INTDIR)\MapEditorDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\MapEditorView.cpp

"$(INTDIR)\MapEditorView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\SizeDialog.cpp

"$(INTDIR)\SizeDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MapEditor.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MapEditor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MapEditor.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MapEditor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MapEditor.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

