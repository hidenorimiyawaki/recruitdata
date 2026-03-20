; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CRenbanEditorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RenbanEditor.h"

ClassCount=4
Class1=CRenbanEditorApp
Class2=CRenbanEditorDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_RENBANEDITOR_DIALOG
Class4=CDefDialog
Resource4=IDD_DEFDIALOG

[CLS:CRenbanEditorApp]
Type=0
HeaderFile=RenbanEditor.h
ImplementationFile=RenbanEditor.cpp
Filter=N
LastObject=CRenbanEditorApp

[CLS:CRenbanEditorDlg]
Type=0
HeaderFile=RenbanEditorDlg.h
ImplementationFile=RenbanEditorDlg.cpp
Filter=D
LastObject=IDC_EDITADDLES
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=RenbanEditorDlg.h
ImplementationFile=RenbanEditorDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_RENBANEDITOR_DIALOG]
Type=1
Class=CRenbanEditorDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDITADDLES,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SLIDEREDIT,msctls_trackbar32,1342242840
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDITNOWNO,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDITNOWTIME,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_BUTTON_BROWS,button,1342242816
Control14=IDC_BUTTON_DATASAVE,button,1342242816
Control15=IDC_BUTTON_DATALOAD,button,1342242816

[DLG:IDD_DEFDIALOG]
Type=1
Class=CDefDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_MAXHTMLNUM,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDITDEFTIME,edit,1350631552
Control6=IDC_STATIC,static,1342308352

[CLS:CDefDialog]
Type=0
HeaderFile=DefDialog.h
ImplementationFile=DefDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CDefDialog
VirtualFilter=dWC

