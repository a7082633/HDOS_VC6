; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEasyTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EasyTest.h"

ClassCount=4
Class1=CEasyTestApp
Class2=CEasyTestDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EASYTEST_DIALOG

[CLS:CEasyTestApp]
Type=0
HeaderFile=EasyTest.h
ImplementationFile=EasyTest.cpp
Filter=N

[CLS:CEasyTestDlg]
Type=0
HeaderFile=EasyTestDlg.h
ImplementationFile=EasyTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=EasyTestDlg.h
ImplementationFile=EasyTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EASYTEST_DIALOG]
Type=1
Class=CEasyTestDlg
ControlCount=1
Control1=IDC_BTN_DEBUG,button,1342242816

