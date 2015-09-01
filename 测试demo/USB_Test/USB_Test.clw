; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUSB_TestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "USB_Test.h"

ClassCount=4
Class1=CUSB_TestApp
Class2=CUSB_TestDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_USB_TEST_DIALOG

[CLS:CUSB_TestApp]
Type=0
HeaderFile=USB_Test.h
ImplementationFile=USB_Test.cpp
Filter=N

[CLS:CUSB_TestDlg]
Type=0
HeaderFile=USB_TestDlg.h
ImplementationFile=USB_TestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=USB_TestDlg.h
ImplementationFile=USB_TestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_USB_TEST_DIALOG]
Type=1
Class=CUSB_TestDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BTN_FINDDEV,button,1342242816
Control4=IDC_BTN_CLOSEDEV,button,1342242816
Control5=IDC_BTN_BEEP,button,1342242816

