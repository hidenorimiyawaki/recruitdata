; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CSpriteToolView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SpriteTool.h"
LastPage=0

ClassCount=7
Class1=CSpriteToolApp
Class2=CSpriteToolDoc
Class3=CSpriteToolView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_CASH_DIALOG
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CCashDialog
Resource3=IDD_ABOUTBOX
Class7=CGlidTypeDialog
Resource4=IDD_GLID_TYPE_DIALOG

[CLS:CSpriteToolApp]
Type=0
HeaderFile=SpriteTool.h
ImplementationFile=SpriteTool.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CSpriteToolApp

[CLS:CSpriteToolDoc]
Type=0
HeaderFile=SpriteToolDoc.h
ImplementationFile=SpriteToolDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSpriteToolView]
Type=0
HeaderFile=SpriteToolView.h
ImplementationFile=SpriteToolView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=SpriteTool.cpp
ImplementationFile=SpriteTool.cpp
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
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE_EX
Command3=ID_FILE_LOAD_EX
Command4=ID_FILE_SAVE
Command5=ID_APP_EXIT
Command6=ID_GLID_TYPE_OPEN
Command7=AFX_ID_GLID_ON
Command8=AFX_ID_GLID_OFF
Command9=AFX_ID_MODE_DIVIDE
Command10=AFX_ID_MODE_SET
Command11=AFX_ID_ALPHA_ON
Command12=AFX_ID_ALPHA_OFF
Command13=AFX_ID_SNAP_ON
Command14=AFX_ID_SNAP_OFF
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_CASH_DIALOG]
Type=1
Class=CCashDialog
ControlCount=8
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_BIT_TEST,static,1342181383
Control4=IDC_STATIC,static,1342308352
Control5=IDC_LIST_CASH,listbox,1352728835
Control6=IDC_EDIT_CAPTION,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CCashDialog]
Type=0
HeaderFile=CashDialog.h
ImplementationFile=CashDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AFX_ID_GLID_OFF

[DLG:IDD_GLID_TYPE_DIALOG]
Type=1
Class=CGlidTypeDialog
ControlCount=21
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_COLOR,static,1342181383
Control4=IDC_STATIC,button,1342177287
Control5=IDC_EDIT_R,edit,1350631552
Control6=IDC_EDIT_G,edit,1350631552
Control7=IDC_EDIT_B,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_SLIDER_R,msctls_trackbar32,1342242840
Control13=IDC_SLIDER_G,msctls_trackbar32,1342242840
Control14=IDC_SLIDER_B,msctls_trackbar32,1342242840
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_COMBO_WIDTH,combobox,1344340226
Control19=IDC_COMBO_HEIGHT,combobox,1344340226
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352

[CLS:CGlidTypeDialog]
Type=0
HeaderFile=GlidTypeDialog.h
ImplementationFile=GlidTypeDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=AFX_ID_GLID_OFF
VirtualFilter=dWC

