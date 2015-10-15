; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPCSCDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PCSC Demo.h"

ClassCount=4
Class1=CPCSCDemoApp
Class2=CPCSCDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PCSCDEMO_DIALOG

[CLS:CPCSCDemoApp]
Type=0
HeaderFile=PCSC Demo.h
ImplementationFile=PCSC Demo.cpp
Filter=N

[CLS:CPCSCDemoDlg]
Type=0
HeaderFile=PCSC DemoDlg.h
ImplementationFile=PCSC DemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=PCSC DemoDlg.h
ImplementationFile=PCSC DemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PCSCDEMO_DIALOG]
Type=1
Class=CPCSCDemoDlg
ControlCount=8
Control1=IDC_BTN_TEST,button,1073807360
Control2=IDC_STATIC_DEV,static,1073872896
Control3=IDC_EDIT_DATA,edit,1352732676
Control4=IDC_BTN_CLEAR,button,1342242816
Control5=IDC_BTN_OPENDEV,button,1342242816
Control6=IDC_BTN_CLOSEDEV,button,1342242816
Control7=IDC_EDIT_APDU,edit,1351680004
Control8=IDC_BTN_EXCAPDU,button,1342242816

