; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SpeakerID.h"

ClassCount=7
Class1=CSpeakerIDApp
Class2=CSpeakerIDDlg

ResourceCount=10
Resource2=IDD_SPEAKERID_DIALOG (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=CUserNameDlg
Resource3=IDD_USERINFO (English (U.S.))
Class4=CUserPasswordDlg
Resource4=IDD_USERINFO
Resource5=IDD_USERPASS
Resource6=IDD_OPTIONS
Resource7=IDD_OPTIONS (English (U.S.))
Class5=COptionsDlg
Class6=CColorFrame
Resource8=IDD_USERPASS (English (U.S.))
Resource9=IDD_ABOUT
Class7=CAboutDlg
Resource10=IDD_SPEAKERID_DIALOG

[CLS:CSpeakerIDApp]
Type=0
HeaderFile=SpeakerID.h
ImplementationFile=SpeakerID.cpp
Filter=N
LastObject=CSpeakerIDApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSpeakerIDDlg]
Type=0
HeaderFile=SpeakerIDDlg.h
ImplementationFile=SpeakerIDDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_ABOUT



[DLG:IDD_SPEAKERID_DIALOG (English (U.S.))]
Type=1
Class=CSpeakerIDDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_REMOVEUSER,button,1476461312
Control4=IDC_USERSLIST,SysListView32,1350631433
Control5=IDC_NEWUSER,button,1342242816
Control6=IDC_MODIFYUSER,button,1476460544
Control7=IDC_STATIC,static,1342308352
Control8=IDC_OPTIONS,button,1342242816

[CLS:CUserNameDlg]
Type=0
HeaderFile=UserNameDlg.h
ImplementationFile=UserNameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserNameDlg
VirtualFilter=dWC

[DLG:IDD_USERINFO (English (U.S.))]
Type=1
Class=CUserNameDlg
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NAME,combobox,1344340226
Control4=IDC_MSGICON,static,1342177283
Control5=IDC_SMSG,static,1342308352
Control6=IDOK,button,1342242816
Control7=IDCANCEL,button,1342242816

[DLG:IDD_USERPASS (English (U.S.))]
Type=1
Class=CUserPasswordDlg
ControlCount=9
Control1=IDC_STEP,button,1342177287
Control2=IDC_RECORD,button,1342242816
Control3=IDC_PLAY,button,1476460544
Control4=IDC_OSIL,static,1350565892
Control5=IDOK,button,1476460544
Control6=IDCANCEL,button,1342242816
Control7=IDC_SMSG,static,1342308352
Control8=IDC_SMSGICON,static,1342177283
Control9=IDC_RECDEV,button,1342242816

[CLS:CUserPasswordDlg]
Type=0
HeaderFile=userpassworddlg.h
ImplementationFile=userpassworddlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CUserPasswordDlg

[DLG:IDD_SPEAKERID_DIALOG]
Type=1
Class=CSpeakerIDDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_REMOVEUSER,button,1476461312
Control4=IDC_USERSLIST,SysListView32,1350631433
Control5=IDC_NEWUSER,button,1342242816
Control6=IDC_MODIFYUSER,button,1476460544
Control7=IDC_STATIC,static,1342308352
Control8=IDC_OPTIONS,button,1342242816
Control9=IDC_ABOUT,button,1342242816

[DLG:IDD_USERINFO]
Type=1
Class=CUserNameDlg
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NAME,combobox,1344340226
Control4=IDC_MSGICON,static,1342177283
Control5=IDC_SMSG,static,1342308352
Control6=IDOK,button,1342242816
Control7=IDCANCEL,button,1342242816

[DLG:IDD_USERPASS]
Type=1
Class=CUserPasswordDlg
ControlCount=9
Control1=IDC_STEP,button,1342177287
Control2=IDC_RECORD,button,1342242816
Control3=IDC_PLAY,button,1476460544
Control4=IDC_OSIL,static,1350565892
Control5=IDOK,button,1476460544
Control6=IDCANCEL,button,1342242816
Control7=IDC_SMSG,static,1342308352
Control8=IDC_SMSGICON,static,1342177283
Control9=IDC_RECDEV,button,1342242816

[DLG:IDD_OPTIONS]
Type=1
Class=COptionsDlg
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_REPNUM,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MINLEN,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SECURITY,combobox,1344340035
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816

[CLS:COptionsDlg]
Type=0
HeaderFile=OptionsDlg.h
ImplementationFile=OptionsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=COptionsDlg
VirtualFilter=dWC

[CLS:CColorFrame]
Type=0
HeaderFile=ColorFrame.h
ImplementationFile=ColorFrame.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CColorFrame

[DLG:IDD_OPTIONS (English (U.S.))]
Type=1
Class=COptionsDlg
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_REPNUM,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MINLEN,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SECURITY,combobox,1344340035
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816

[DLG:IDD_ABOUT]
Type=1
Class=CAboutDlg
ControlCount=26
Control1=IDC_STATIC,static,1342308353
Control2=IDC_ME,static,1342308353
Control3=IDC_STATIC,static,1342308353
Control4=IDC_DR,static,1342308353
Control5=IDC_STATIC,static,1342308353
Control6=IDC_JHE,static,1342308353
Control7=IDC_STATIC,static,1342308353
Control8=IDC_CM,static,1342308353
Control9=IDC_FC,static,1342308353
Control10=IDC_DP,static,1342308353
Control11=IDC_TH,static,1342308353
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308353
Control16=IDC_FD,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_JM,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_CT,static,1342308352
Control21=IDC_STATIC,static,1342308353
Control22=IDC_STATIC,static,1342308353
Control23=IDOK,button,1342242816
Control24=IDC_STATIC,static,1342308352
Control25=IDC_SB,static,1342308353
Control26=IDC_STATIC,static,1342308353

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SB
VirtualFilter=dWC

