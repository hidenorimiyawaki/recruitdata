; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCameraDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "vectorsettool.h"
LastPage=0

ClassCount=6
Class1=CMainFrame
Class2=CVectorSetToolApp
Class3=CAboutDlg
Class4=CVectorSetToolDoc
Class5=CVectorSetToolView

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class6=CCameraDialog
Resource3=IDD_CAMERA_DIALOG

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CVectorSetToolApp]
Type=0
BaseClass=CWinApp
HeaderFile=VectorSetTool.h
ImplementationFile=VectorSetTool.cpp
Filter=N
VirtualFilter=AC
LastObject=AFX_ID_SNAP_OFF

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=VectorSetTool.cpp
ImplementationFile=VectorSetTool.cpp
Filter=D
VirtualFilter=dWC
LastObject=AFX_ID_DELETE_POINT

[CLS:CVectorSetToolDoc]
Type=0
BaseClass=CDocument
HeaderFile=VectorSetToolDoc.h
ImplementationFile=VectorSetToolDoc.cpp
LastObject=CVectorSetToolDoc

[CLS:CVectorSetToolView]
Type=0
BaseClass=CView
HeaderFile=VectorSetToolView.h
ImplementationFile=VectorSetToolView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CVectorSetToolView

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
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=AFX_ID_FILE_SAVE_EX
Command4=AFX_ID_FILE_LOAD_EX
Command5=ID_APP_EXIT
Command6=AFX_ID_EDIT_POINT
Command7=AFX_ID_CHANGE_POINT
Command8=AFX_ID_DELETE_POINT
Command9=AFX_ID_SET_OBJECT_POINT
Command10=AFX_ID_CHANGE_OBJECT_POINT
Command11=AFX_ID_DELETE_OBJECT_POINT
Command12=AFX_ID_OBJECT_1
Command13=AFX_ID_OBJECT_2
Command14=AFX_ID_SNAP_ON
Command15=AFX_ID_SNAP_OFF
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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

[DLG:IDD_CAMERA_DIALOG]
Type=1
Class=CCameraDialog
ControlCount=23
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_MOVE_X,edit,1350631552
Control8=IDC_EDIT_MOVE_Y,edit,1350631552
Control9=IDC_EDIT_MOVE_Z,edit,1350631552
Control10=IDC_BUTTON_MOVE,button,1342242816
Control11=IDC_STATIC,button,1342177287
Control12=IDC_BUTTON_UP,button,1342242816
Control13=IDC_BUTTON_DOWN,button,1342242816
Control14=IDC_BUTTON_LEFT,button,1342242816
Control15=IDC_BUTTON_RIGHT,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_EDIT_OFFSET,edit,1350631552
Control18=IDC_BUTTON_DEFAULT,button,1342242816
Control19=IDC_STATIC,button,1342177287
Control20=IDC_BUTTON_SET_POINT,button,1342242816
Control21=IDC_STATIC,button,1342177287
Control22=IDC_COMBO_OBJECT,combobox,1344340226
Control23=IDC_BUTTON_SET_OBJECT,button,1342242816

[CLS:CCameraDialog]
Type=0
HeaderFile=CameraDialog.h
ImplementationFile=CameraDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AFX_ID_CHANGE_OBJECT_POINT

