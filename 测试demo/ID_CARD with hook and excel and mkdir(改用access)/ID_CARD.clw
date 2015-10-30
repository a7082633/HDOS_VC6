; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialogQueryData
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ID_CARD.h"

ClassCount=4
Class1=CID_CARDApp
Class2=CID_CARDDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ID_CARD_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_QUERYDATA
Class4=CDialogQueryData
Resource4=IDD_ABOUTBOX
Resource5=IDD_DIALOG1

[CLS:CID_CARDApp]
Type=0
HeaderFile=ID_CARD.h
ImplementationFile=ID_CARD.cpp
Filter=N

[CLS:CID_CARDDlg]
Type=0
HeaderFile=ID_CARDDlg.h
ImplementationFile=ID_CARDDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CID_CARDDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ID_CARDDlg.h
ImplementationFile=ID_CARDDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ID_CARD_DIALOG]
Type=1
Class=CID_CARDDlg
ControlCount=33
Control1=IDOK,button,1073807361
Control2=IDC_BTN_OPENDEV,button,1342242816
Control3=IDC_BTN_CLOSEDEV,button,1073807360
Control4=IDC_STATIC_STATE,static,1342308352
Control5=IDC_STATIC_STATE_CARD,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_NAME,edit,1350631552
Control15=IDC_EDIT_SEX,edit,1350631552
Control16=IDC_EDIT_NATION,edit,1350631552
Control17=IDC_EDIT_ADDR,edit,1350631552
Control18=IDC_EDIT_BORNDATE,edit,1350631552
Control19=IDC_EDIT_DEADLINE,edit,1350631552
Control20=IDC_EDIT_SIGNADDR,edit,1350631552
Control21=IDC_EDIT_CARDNO,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_BTN_CLA_CONTENT,button,1342242816
Control25=IDC_STATIC,button,1342177287
Control26=IDC_BTN_SELCTPHODIR,button,1073807360
Control27=IDC_BTN_IDCARD_EXCEL,button,1073807360
Control28=IDC_EDIT_PHOTODIR,edit,1082198144
Control29=IDC_EDIT_INFODIR,edit,1082198144
Control30=IDC_BUTTON_TEST,button,1073807360
Control31=IDC_BTN_OPENHOOK,button,1073807360
Control32=IDC_BTN_CLOSEHOOK,button,1073807360
Control33=IDC_BTN_OPENQUERY,button,1342242816

[DLG:IDD_DIALOG_QUERYDATA]
Type=1
Class=CDialogQueryData
ControlCount=10
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_BTN_QUERY,button,1342242816
Control4=IDC_BTN_SHOWALL,button,1342242816
Control5=IDC_LIST_DATA,SysListView32,1350631681
Control6=IDC_COMBO_EXPRESSION,combobox,1344340226
Control7=IDC_EDIT_EXPRESSION,edit,1350631552
Control8=IDC_BTN_EXPORT,button,1342242816
Control9=IDC_BTN_BACKUP,button,1342242816
Control10=IDC_BTN_OPENBACKUP,button,1342242816

[CLS:CDialogQueryData]
Type=0
HeaderFile=DialogQueryData.h
ImplementationFile=DialogQueryData.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_EXPRESSION
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

