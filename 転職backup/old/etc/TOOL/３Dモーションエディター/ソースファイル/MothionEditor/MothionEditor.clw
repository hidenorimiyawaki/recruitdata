; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CMothionEditorDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MothionEditor.h"
LastPage=0

ClassCount=6
Class1=CMothionEditorApp
Class2=CMothionEditorDoc
Class3=CMothionEditorView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=CEditDialog
Resource3=IDD_EDIT_DIALOG

[CLS:CMothionEditorApp]
Type=0
HeaderFile=MothionEditor.h
ImplementationFile=MothionEditor.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CMothionEditorApp

[CLS:CMothionEditorDoc]
Type=0
HeaderFile=MothionEditorDoc.h
ImplementationFile=MothionEditorDoc.cpp
Filter=N
LastObject=ID_FILE_SAVE_EX
BaseClass=CDocument
VirtualFilter=DC

[CLS:CMothionEditorView]
Type=0
HeaderFile=MothionEditorView.h
ImplementationFile=MothionEditorView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CMothionEditorView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_EDIT_COPY
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=MothionEditor.cpp
ImplementationFile=MothionEditor.cpp
Filter=D
LastObject=ID_APP_EXIT

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
Command1=ID_FILE_SAVE_AS
Command2=ID_FILE_LOAD_EX
Command3=ID_FILE_SAVE_EX
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_APP_ABOUT
CommandCount=8

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

[DLG:IDD_EDIT_DIALOG]
Type=1
Class=CEditDialog
ControlCount=37
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_PARTS_NO,edit,1350631552
Control9=IDC_SLIDER_PARTS_NO,msctls_trackbar32,1342242840
Control10=IDC_EDIT_POSX,edit,1350631552
Control11=IDC_SLIDER_POSX,msctls_trackbar32,1342242840
Control12=IDC_EDIT_POSY,edit,1350631552
Control13=IDC_SLIDER_POSY,msctls_trackbar32,1342242840
Control14=IDC_EDIT_POSZ,edit,1350631552
Control15=IDC_SLIDER_POSZ,msctls_trackbar32,1342242840
Control16=IDC_EDIT_ROTX,edit,1350631552
Control17=IDC_SLIDER_ROTX,msctls_trackbar32,1342242840
Control18=IDC_EDIT_ROTY,edit,1350631552
Control19=IDC_SLIDER_ROTY,msctls_trackbar32,1342242840
Control20=IDC_EDIT_ROTZ,edit,1350631552
Control21=IDC_SLIDER_ROTZ,msctls_trackbar32,1342242840
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,button,1342177287
Control25=IDC_CHECK_ATTACK,button,1342242819
Control26=IDC_CHECK_GARD,button,1342242819
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDIT_FRAME,edit,1350631552
Control30=IDC_SLIDER_FRAME,msctls_trackbar32,1342242840
Control31=IDC_CHECK_ANIMATION,button,1342242819
Control32=IDC_BUTTON_PLAY,button,1342242816
Control33=IDC_BUTTON_STOP,button,1342242816
Control34=IDC_BUTTON_BACK,button,1342242816
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EDIT_TIME,edit,1350631552
Control37=IDC_SLIDER_TIME,msctls_trackbar32,1342242840

[CLS:CEditDialog]
Type=0
HeaderFile=EditDialog.h
ImplementationFile=EditDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CEditDialog
VirtualFilter=dWC

