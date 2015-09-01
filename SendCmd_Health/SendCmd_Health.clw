; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSendCmd_HealthDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SendCmd_Health.h"

ClassCount=4
Class1=CSendCmd_HealthApp
Class2=CSendCmd_HealthDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SENDCMD_HEALTH_DIALOG

[CLS:CSendCmd_HealthApp]
Type=0
HeaderFile=SendCmd_Health.h
ImplementationFile=SendCmd_Health.cpp
Filter=N

[CLS:CSendCmd_HealthDlg]
Type=0
HeaderFile=SendCmd_HealthDlg.h
ImplementationFile=SendCmd_HealthDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SendCmd_HealthDlg.h
ImplementationFile=SendCmd_HealthDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SENDCMD_HEALTH_DIALOG]
Type=1
Class=CSendCmd_HealthDlg
ControlCount=12
Control1=IDOK,button,1073807360
Control2=IDC_BTN_OPEN,button,1342242816
Control3=IDC_BTN_CLOSE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_APDU,edit,1350631552
Control6=IDC_BTN_SENDAPDU,button,1342242816
Control7=IDC_BTN_USERPOWERON,button,1342242816
Control8=IDC_EDIT_DATA,edit,1352732804
Control9=IDC_BTN_SAMPOWERON,button,1342242816
Control10=IDC_RADIO_USER,button,1342177289
Control11=IDC_RADIO_SAM,button,1342177289
Control12=IDC_STATIC,button,1342177287

