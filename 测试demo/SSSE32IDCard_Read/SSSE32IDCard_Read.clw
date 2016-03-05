; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSSSE32IDCard_ReadDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SSSE32IDCard_Read.h"

ClassCount=4
Class1=CSSSE32IDCard_ReadApp
Class2=CSSSE32IDCard_ReadDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SSSE32IDCARD_READ_DIALOG

[CLS:CSSSE32IDCard_ReadApp]
Type=0
HeaderFile=SSSE32IDCard_Read.h
ImplementationFile=SSSE32IDCard_Read.cpp
Filter=N

[CLS:CSSSE32IDCard_ReadDlg]
Type=0
HeaderFile=SSSE32IDCard_ReadDlg.h
ImplementationFile=SSSE32IDCard_ReadDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SSSE32IDCard_ReadDlg.h
ImplementationFile=SSSE32IDCard_ReadDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SSSE32IDCARD_READ_DIALOG]
Type=1
Class=CSSSE32IDCard_ReadDlg
ControlCount=7
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_BTN_OPEN,button,1342242816
Control4=IDC_BTN_CLOSE,button,1342242816
Control5=IDC_BTN_FINDCARD,button,1342242816
Control6=IDC_BTN_SELECTC,button,1342242816
Control7=IDC_BTN_READ,button,1342242816

