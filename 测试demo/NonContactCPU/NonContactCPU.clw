; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNonContactCPUDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NonContactCPU.h"

ClassCount=4
Class1=CNonContactCPUApp
Class2=CNonContactCPUDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_NONCONTACTCPU_DIALOG

[CLS:CNonContactCPUApp]
Type=0
HeaderFile=NonContactCPU.h
ImplementationFile=NonContactCPU.cpp
Filter=N

[CLS:CNonContactCPUDlg]
Type=0
HeaderFile=NonContactCPUDlg.h
ImplementationFile=NonContactCPUDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=NonContactCPUDlg.h
ImplementationFile=NonContactCPUDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NONCONTACTCPU_DIALOG]
Type=1
Class=CNonContactCPUDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDOK_POWER_ON,button,1342242817
Control3=IDC_RADIO_A,button,1342177289
Control4=IDC_RADIO_B,button,1342177289
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_APDU,edit,1351680004
Control7=IDC_EDIT_DATA,edit,1352734916
Control8=IDOK_BTN_EXC,button,1342242817
Control9=IDC_BTN_OPENPORT,button,1342242816
Control10=IDC_BTN_CLOSEPORT,button,1342242816

