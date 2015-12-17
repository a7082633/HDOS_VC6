; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHD_BHGXDLL_DEMODlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HD_BHGXDLL_DEMO.h"

ClassCount=4
Class1=CHD_BHGXDLL_DEMOApp
Class2=CHD_BHGXDLL_DEMODlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_HD_BHGXDLL_DEMO_DIALOG

[CLS:CHD_BHGXDLL_DEMOApp]
Type=0
HeaderFile=HD_BHGXDLL_DEMO.h
ImplementationFile=HD_BHGXDLL_DEMO.cpp
Filter=N

[CLS:CHD_BHGXDLL_DEMODlg]
Type=0
HeaderFile=HD_BHGXDLL_DEMODlg.h
ImplementationFile=HD_BHGXDLL_DEMODlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=HD_BHGXDLL_DEMODlg.h
ImplementationFile=HD_BHGXDLL_DEMODlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_HD_BHGXDLL_DEMO_DIALOG]
Type=1
Class=CHD_BHGXDLL_DEMODlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BTN_OPENDEVICE,button,1342242816
Control4=IDC_BTN_CLOSEDEVICE,button,1342242816
Control5=IDC_BTN_READBIN,button,1342242816

