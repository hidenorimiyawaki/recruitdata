; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CBmpDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MapEditor.h"
LastPage=0

ClassCount=13
Class1=CMapEditorApp
Class2=CMapEditorDoc
Class3=CMapEditorView
Class4=CMainFrame

ResourceCount=8
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMapData
Resource3=IDD_ATTR_DIALOG
Class7=CSizeDialog
Resource4=IDD_DATA_DIALOG
Class8=CDataDialog
Class9=CBmpDialog
Resource5=IDD_CURSOL_DIALOG
Resource6=IDD_SIZE_DIALOG
Class10=CAttrDialog
Class11=CAttrData
Class12=CCursolSizeDialog
Resource7=IDD_BMP_DIALOG
Class13=CGlidColorDialog
Resource8=IDD_GLID_COLOR_DIALOG

[CLS:CMapEditorApp]
Type=0
HeaderFile=MapEditor.h
ImplementationFile=MapEditor.cpp
Filter=N
LastObject=CMapEditorApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CMapEditorDoc]
Type=0
HeaderFile=MapEditorDoc.h
ImplementationFile=MapEditorDoc.cpp
Filter=N
LastObject=CMapEditorDoc

[CLS:CMapEditorView]
Type=0
HeaderFile=MapEditorView.h
ImplementationFile=MapEditorView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CMapEditorView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=AFX_ID_SET_ATTR




[CLS:CAboutDlg]
Type=0
HeaderFile=MapEditor.cpp
ImplementationFile=MapEditor.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
CommandCount=0

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_NEXT_PANE
Command9=ID_PREV_PANE
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_CUT
Command13=ID_EDIT_UNDO
CommandCount=13

[CLS:CMapData]
Type=0
HeaderFile=MapData.h
ImplementationFile=MapData.cpp
BaseClass=generic CWnd
Filter=W
LastObject=CMapData

[DLG:IDD_BMP_DIALOG]
Type=1
Class=CBmpDialog
ControlCount=1
Control1=IDC_FIELD_BMP,static,1342177294

[DLG:IDD_SIZE_DIALOG]
Type=1
Class=CSizeDialog
ControlCount=8
Control1=IDC_EDIT_X_SIZE,edit,1350631552
Control2=IDC_EDIT_Y_SIZE,edit,1350631552
Control3=IDC_EDIT_PALET_No,edit,1350631552
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_TEXT_X,static,1342308352
Control7=IDC_TEXT_Y,static,1342308352
Control8=IDC_TXT_PALET,static,1342308352

[CLS:CSizeDialog]
Type=0
HeaderFile=SizeDialog.h
ImplementationFile=SizeDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_X_SIZE

[CLS:CBmpDialog]
Type=0
HeaderFile=BmpDialog.h
ImplementationFile=BmpDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CBmpDialog
VirtualFilter=dWC

[DLG:IDD_ATTR_DIALOG]
Type=1
Class=?
ControlCount=8
Control1=IDC_TEXT_FLOOR,static,1342308352
Control2=IDC_COMBO_FLOOR,combobox,1344340226
Control3=IDC_TEXT_STEP,static,1342308352
Control4=IDC_COMBO_STEP,combobox,1344340226
Control5=IDC_TEXT_DAMAGE,static,1342308352
Control6=IDC_COMBO_DAMAGE,combobox,1344340226
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[DLG:IDD_DATA_DIALOG]
Type=1
Class=CDataDialog
ControlCount=10
Control1=IDC_COMBO_FLOOR,combobox,1344340227
Control2=IDC_COMBO_STEP,combobox,1344340227
Control3=IDC_COMBO_DAMAGE,combobox,1344340227
Control4=IDC_EDIT_PALET,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC_FLOOR,static,1342308352
Control8=IDC_STATIC_STEP,static,1342308352
Control9=IDC_STATIC_DAMAGE,static,1342308352
Control10=IDC_PALET,static,1342308352

[CLS:CDataDialog]
Type=0
HeaderFile=DataDialog.h
ImplementationFile=DataDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CDataDialog
VirtualFilter=dWC

[CLS:CAttrDialog]
Type=0
HeaderFile=AttrDialog.h
ImplementationFile=AttrDialog.cpp
BaseClass=generic CWnd
Filter=W

[CLS:CAttrData]
Type=0
HeaderFile=AttrData.h
ImplementationFile=AttrData.cpp
BaseClass=generic CWnd
Filter=W

[DLG:IDD_CURSOL_DIALOG]
Type=1
Class=CCursolSizeDialog
ControlCount=6
Control1=IDC_EDIT_CURSOL_X_SIZE,edit,1350631552
Control2=IDC_EDIT_CURSOL_Y_SIZE,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_C_TEXT_X,static,1342308352
Control6=IDC_C_TEXT_Y,static,1342308352

[CLS:CCursolSizeDialog]
Type=0
HeaderFile=CursolSizeDialog.h
ImplementationFile=CursolSizeDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CCursolSizeDialog
VirtualFilter=dWC

[DLG:IDD_GLID_COLOR_DIALOG]
Type=1
Class=CGlidColorDialog
ControlCount=10
Control1=IDC_EDIT_R,edit,1350631552
Control2=IDC_EDIT_G,edit,1350631552
Control3=IDC_EDIT_B,edit,1350631552
Control4=IDC_SAMPLE_BUTTON,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC_R,static,1342308352
Control8=IDC_STATIC_G,static,1342308352
Control9=IDC_STATIC_B,static,1342308352
Control10=IDC_SAMPLE_COLOR,static,1342177294

[CLS:CGlidColorDialog]
Type=0
HeaderFile=GlidColorDialog.h
ImplementationFile=GlidColorDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=AFX_ID_SET_GLID_COLOR
VirtualFilter=dWC

