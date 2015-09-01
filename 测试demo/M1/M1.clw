; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialogLoadKey
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "M1.h"

ClassCount=5
Class1=CM1App
Class2=CM1Dlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_M1_DIALOG
Class4=CDialogLoadKey
Resource4=IDD_DIALOG_LOADKEY
Class5=CDlialogPass
Resource5=IDD_DIALOG_PASS

[CLS:CM1App]
Type=0
HeaderFile=M1.h
ImplementationFile=M1.cpp
Filter=N

[CLS:CM1Dlg]
Type=0
HeaderFile=M1Dlg.h
ImplementationFile=M1Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CM1Dlg

[CLS:CAboutDlg]
Type=0
HeaderFile=M1Dlg.h
ImplementationFile=M1Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_M1_DIALOG]
Type=1
Class=CM1Dlg
ControlCount=34
Control1=IDOK,button,1342242817
Control2=IDC_BTN_RQE,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO_KEYA,button,1342177289
Control5=IDC_RADIO_KEYB,button,1342177289
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_SN,edit,1484849280
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_PASS,edit,1350631552
Control10=IDC_BTN_RA,button,1476460544
Control11=IDC_BTN_RA2,button,1476460544
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_BLOCKN,edit,1350631552
Control15=IDC_BTN_RA3,button,1342242816
Control16=IDC_EDIT_DATA,edit,1352734916
Control17=IDC_STATIC,button,1342177287
Control18=IDC_BTN_WRITEHEX,button,1342242816
Control19=IDC_EDIT_WRITEDATA,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_VALUE,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_BTN_INITIAL,button,1342242816
Control25=IDC_BTN_INCREMENT,button,1342242816
Control26=IDC_BTN_DESCMENT,button,1342242816
Control27=IDC_BTN_READVAL,button,1342242816
Control28=IDC_BTN_CLEAR,button,1342242816
Control29=IDC_BTN_RASTR,button,1342242816
Control30=IDC_BTN_WRITESTR,button,1342242816
Control31=IDC_BTN_RAALL,button,1342242816
Control32=IDC_BTN_LOADKEY,button,1342242816
Control33=IDC_BTN_OPENPORT,button,1342242816
Control34=IDC_BTN_CLOSEPORT,button,1342242816

[CLS:CDialogLoadKey]
Type=0
HeaderFile=DialogLoadKey.h
ImplementationFile=DialogLoadKey.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO_S70
VirtualFilter=dWC

[DLG:IDD_DIALOG_LOADKEY]
Type=1
Class=CDialogLoadKey
ControlCount=8
Control1=IDC_RADIO_S50,button,1342373897
Control2=IDC_RADIO_S70,button,1342242825
Control3=IDC_RADIO_KEYA,button,1342373897
Control4=IDC_RADIO_KEYB,button,1342242825
Control5=IDC_BTN_DOWNLOAD,button,1342242816
Control6=IDC_LIST,SysListView32,1350631425
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG_PASS]
Type=1
Class=CDlialogPass
ControlCount=1
Control1=IDC_EDIT_PASS,edit,1350631552

[CLS:CDlialogPass]
Type=0
HeaderFile=DlialogPass.h
ImplementationFile=DlialogPass.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

