/********************************************************************************
** Form generated from reading UI file 'xgd_host.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XGD_HOST_H
#define UI_XGD_HOST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XGD_HOST
{
public:
    QAction *action_Open;
    QAction *action_Close;
    QWidget *centralwidget;
    QGroupBox *groupBox_Config;
    QComboBox *comboBox_AID;
    QLabel *label_AID;
    QPushButton *pushButton_DownloadAid;
    QLabel *label_CAPK;
    QComboBox *comboBox_CAPK;
    QPushButton *pushButton_DownloadCAPK;
    QLabel *label_ExceptionFile;
    QComboBox *comboBox_ExceptionFile;
    QPushButton *pushButton_DownloadExcet;
    QLabel *label_DRL;
    QComboBox *comboBox_DRL;
    QPushButton *pushButton_DownloadDRL;
    QLabel *label_SimData;
    QComboBox *comboBox_SimData;
    QPushButton *pushButton_DownloadSimdata;
    QLabel *label_RevoKey;
    QComboBox *comboBox_Revokey;
    QPushButton *pushButton_DownloadRevokey;
    QLabel *label_PreProcess;
    QComboBox *comboBox_PreProcess;
    QPushButton *pushButton_DownloadPreprocess;
    QGroupBox *groupBox_HostResCode;
    QLineEdit *lineEdit_HostResCode;
    QGroupBox *groupBox_IssuerScript;
    QLineEdit *lineEdit_IssuerScript;
    QGroupBox *groupBox_HostAuthData;
    QLineEdit *lineEdit_HostAuthData;
    QGroupBox *groupBox_Amount;
    QLineEdit *lineEdit_Amt;
    QGroupBox *groupBox_AmtOther;
    QLineEdit *lineEdit_AmtOther;
    QGroupBox *groupBox_TransType;
    QLineEdit *lineEdit_TransType;
    QPushButton *pushButton_StartTrans;
    QPushButton *pushButton_ClrMessage;
    QTabWidget *tabWidget_Settings;
    QWidget *tab_commsetting;
    QLabel *label_SerialPort;
    QLabel *label_SerialBaud;
    QPushButton *pushButton_ScanSerial;
    QPushButton *pushButton_OpenSerial;
    QComboBox *comboBox_SerialPort;
    QComboBox *comboBox_BaudRate;
    QWidget *tab_othsetting;
    QLineEdit *lineEdit_IPPort;
    QLabel *label_IPAddress;
    QLabel *label_IPPort;
    QPushButton *pushButton_ListenPort;
    QPushButton *pushButton_ClosePort;
    QComboBox *comboBox_IPAddress;
    QWidget *tab_readercontroller;
    QPushButton *pushButton_RCSingle;
    QPushButton *pushButton_RCBatch;
    QPushButton *pushButton_RCEcho;
    QWidget *tab_RCSetting;
    QLabel *label_TimeDelay;
    QLineEdit *lineEdit_TimeDelay;
    QLineEdit *lineEdit_Resend;
    QLabel *label_Resend;
    QGroupBox *groupBox_Message;
    QPlainTextEdit *plainTextEdit_Message;
    QScrollBar *verticalScrollBar_Message;
    QGroupBox *groupBox_Brand;
    QComboBox *comboBox_Brand;
    QCheckBox *checkBox_Amt;
    QCheckBox *checkBox_AmtOther;
    QCheckBox *checkBox_TransType;
    QGroupBox *groupBox_TransType_2;
    QLineEdit *lineEdit_TransType_2;
    QGroupBox *groupBox_TransType_4;
    QLineEdit *lineEdit_TransType_4;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menuLog_File;

    void setupUi(QMainWindow *XGD_HOST)
    {
        if (XGD_HOST->objectName().isEmpty())
            XGD_HOST->setObjectName(QString::fromUtf8("XGD_HOST"));
        XGD_HOST->resize(1320, 687);
        action_Open = new QAction(XGD_HOST);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Close = new QAction(XGD_HOST);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        centralwidget = new QWidget(XGD_HOST);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_Config = new QGroupBox(centralwidget);
        groupBox_Config->setObjectName(QString::fromUtf8("groupBox_Config"));
        groupBox_Config->setGeometry(QRect(820, 20, 481, 601));
        comboBox_AID = new QComboBox(groupBox_Config);
        comboBox_AID->setObjectName(QString::fromUtf8("comboBox_AID"));
        comboBox_AID->setGeometry(QRect(140, 20, 191, 31));
        label_AID = new QLabel(groupBox_Config);
        label_AID->setObjectName(QString::fromUtf8("label_AID"));
        label_AID->setGeometry(QRect(30, 30, 72, 15));
        pushButton_DownloadAid = new QPushButton(groupBox_Config);
        pushButton_DownloadAid->setObjectName(QString::fromUtf8("pushButton_DownloadAid"));
        pushButton_DownloadAid->setGeometry(QRect(380, 20, 93, 31));
        label_CAPK = new QLabel(groupBox_Config);
        label_CAPK->setObjectName(QString::fromUtf8("label_CAPK"));
        label_CAPK->setGeometry(QRect(30, 80, 72, 15));
        comboBox_CAPK = new QComboBox(groupBox_Config);
        comboBox_CAPK->setObjectName(QString::fromUtf8("comboBox_CAPK"));
        comboBox_CAPK->setGeometry(QRect(140, 70, 191, 31));
        pushButton_DownloadCAPK = new QPushButton(groupBox_Config);
        pushButton_DownloadCAPK->setObjectName(QString::fromUtf8("pushButton_DownloadCAPK"));
        pushButton_DownloadCAPK->setGeometry(QRect(380, 70, 93, 31));
        label_ExceptionFile = new QLabel(groupBox_Config);
        label_ExceptionFile->setObjectName(QString::fromUtf8("label_ExceptionFile"));
        label_ExceptionFile->setGeometry(QRect(11, 130, 111, 20));
        comboBox_ExceptionFile = new QComboBox(groupBox_Config);
        comboBox_ExceptionFile->setObjectName(QString::fromUtf8("comboBox_ExceptionFile"));
        comboBox_ExceptionFile->setGeometry(QRect(140, 120, 191, 31));
        pushButton_DownloadExcet = new QPushButton(groupBox_Config);
        pushButton_DownloadExcet->setObjectName(QString::fromUtf8("pushButton_DownloadExcet"));
        pushButton_DownloadExcet->setGeometry(QRect(380, 120, 93, 31));
        label_DRL = new QLabel(groupBox_Config);
        label_DRL->setObjectName(QString::fromUtf8("label_DRL"));
        label_DRL->setGeometry(QRect(20, 180, 31, 20));
        comboBox_DRL = new QComboBox(groupBox_Config);
        comboBox_DRL->setObjectName(QString::fromUtf8("comboBox_DRL"));
        comboBox_DRL->setGeometry(QRect(140, 170, 191, 31));
        pushButton_DownloadDRL = new QPushButton(groupBox_Config);
        pushButton_DownloadDRL->setObjectName(QString::fromUtf8("pushButton_DownloadDRL"));
        pushButton_DownloadDRL->setGeometry(QRect(380, 170, 93, 31));
        label_SimData = new QLabel(groupBox_Config);
        label_SimData->setObjectName(QString::fromUtf8("label_SimData"));
        label_SimData->setGeometry(QRect(20, 230, 61, 20));
        comboBox_SimData = new QComboBox(groupBox_Config);
        comboBox_SimData->setObjectName(QString::fromUtf8("comboBox_SimData"));
        comboBox_SimData->setGeometry(QRect(140, 220, 191, 31));
        pushButton_DownloadSimdata = new QPushButton(groupBox_Config);
        pushButton_DownloadSimdata->setObjectName(QString::fromUtf8("pushButton_DownloadSimdata"));
        pushButton_DownloadSimdata->setGeometry(QRect(380, 220, 93, 31));
        label_RevoKey = new QLabel(groupBox_Config);
        label_RevoKey->setObjectName(QString::fromUtf8("label_RevoKey"));
        label_RevoKey->setGeometry(QRect(20, 290, 61, 20));
        comboBox_Revokey = new QComboBox(groupBox_Config);
        comboBox_Revokey->setObjectName(QString::fromUtf8("comboBox_Revokey"));
        comboBox_Revokey->setGeometry(QRect(140, 280, 191, 31));
        pushButton_DownloadRevokey = new QPushButton(groupBox_Config);
        pushButton_DownloadRevokey->setObjectName(QString::fromUtf8("pushButton_DownloadRevokey"));
        pushButton_DownloadRevokey->setGeometry(QRect(380, 280, 93, 31));
        label_PreProcess = new QLabel(groupBox_Config);
        label_PreProcess->setObjectName(QString::fromUtf8("label_PreProcess"));
        label_PreProcess->setGeometry(QRect(20, 350, 81, 20));
        comboBox_PreProcess = new QComboBox(groupBox_Config);
        comboBox_PreProcess->setObjectName(QString::fromUtf8("comboBox_PreProcess"));
        comboBox_PreProcess->setGeometry(QRect(140, 340, 191, 31));
        pushButton_DownloadPreprocess = new QPushButton(groupBox_Config);
        pushButton_DownloadPreprocess->setObjectName(QString::fromUtf8("pushButton_DownloadPreprocess"));
        pushButton_DownloadPreprocess->setGeometry(QRect(380, 340, 93, 31));
        groupBox_HostResCode = new QGroupBox(groupBox_Config);
        groupBox_HostResCode->setObjectName(QString::fromUtf8("groupBox_HostResCode"));
        groupBox_HostResCode->setGeometry(QRect(90, 390, 291, 61));
        lineEdit_HostResCode = new QLineEdit(groupBox_HostResCode);
        lineEdit_HostResCode->setObjectName(QString::fromUtf8("lineEdit_HostResCode"));
        lineEdit_HostResCode->setGeometry(QRect(10, 20, 271, 31));
        groupBox_IssuerScript = new QGroupBox(groupBox_Config);
        groupBox_IssuerScript->setObjectName(QString::fromUtf8("groupBox_IssuerScript"));
        groupBox_IssuerScript->setGeometry(QRect(90, 450, 291, 61));
        lineEdit_IssuerScript = new QLineEdit(groupBox_IssuerScript);
        lineEdit_IssuerScript->setObjectName(QString::fromUtf8("lineEdit_IssuerScript"));
        lineEdit_IssuerScript->setGeometry(QRect(10, 20, 271, 31));
        groupBox_HostAuthData = new QGroupBox(groupBox_Config);
        groupBox_HostAuthData->setObjectName(QString::fromUtf8("groupBox_HostAuthData"));
        groupBox_HostAuthData->setGeometry(QRect(90, 520, 291, 61));
        lineEdit_HostAuthData = new QLineEdit(groupBox_HostAuthData);
        lineEdit_HostAuthData->setObjectName(QString::fromUtf8("lineEdit_HostAuthData"));
        lineEdit_HostAuthData->setGeometry(QRect(10, 20, 271, 31));
        groupBox_Amount = new QGroupBox(centralwidget);
        groupBox_Amount->setObjectName(QString::fromUtf8("groupBox_Amount"));
        groupBox_Amount->setGeometry(QRect(10, 100, 141, 61));
        lineEdit_Amt = new QLineEdit(groupBox_Amount);
        lineEdit_Amt->setObjectName(QString::fromUtf8("lineEdit_Amt"));
        lineEdit_Amt->setGeometry(QRect(10, 20, 121, 31));
        groupBox_AmtOther = new QGroupBox(centralwidget);
        groupBox_AmtOther->setObjectName(QString::fromUtf8("groupBox_AmtOther"));
        groupBox_AmtOther->setGeometry(QRect(10, 175, 141, 61));
        lineEdit_AmtOther = new QLineEdit(groupBox_AmtOther);
        lineEdit_AmtOther->setObjectName(QString::fromUtf8("lineEdit_AmtOther"));
        lineEdit_AmtOther->setGeometry(QRect(10, 20, 121, 31));
        groupBox_TransType = new QGroupBox(centralwidget);
        groupBox_TransType->setObjectName(QString::fromUtf8("groupBox_TransType"));
        groupBox_TransType->setGeometry(QRect(10, 250, 141, 61));
        lineEdit_TransType = new QLineEdit(groupBox_TransType);
        lineEdit_TransType->setObjectName(QString::fromUtf8("lineEdit_TransType"));
        lineEdit_TransType->setGeometry(QRect(10, 20, 121, 31));
        pushButton_StartTrans = new QPushButton(centralwidget);
        pushButton_StartTrans->setObjectName(QString::fromUtf8("pushButton_StartTrans"));
        pushButton_StartTrans->setGeometry(QRect(190, 320, 101, 41));
        pushButton_ClrMessage = new QPushButton(centralwidget);
        pushButton_ClrMessage->setObjectName(QString::fromUtf8("pushButton_ClrMessage"));
        pushButton_ClrMessage->setGeometry(QRect(190, 390, 93, 28));
        tabWidget_Settings = new QTabWidget(centralwidget);
        tabWidget_Settings->setObjectName(QString::fromUtf8("tabWidget_Settings"));
        tabWidget_Settings->setGeometry(QRect(10, 460, 291, 151));
        tab_commsetting = new QWidget();
        tab_commsetting->setObjectName(QString::fromUtf8("tab_commsetting"));
        label_SerialPort = new QLabel(tab_commsetting);
        label_SerialPort->setObjectName(QString::fromUtf8("label_SerialPort"));
        label_SerialPort->setGeometry(QRect(30, 30, 31, 20));
        label_SerialBaud = new QLabel(tab_commsetting);
        label_SerialBaud->setObjectName(QString::fromUtf8("label_SerialBaud"));
        label_SerialBaud->setGeometry(QRect(30, 80, 41, 16));
        pushButton_ScanSerial = new QPushButton(tab_commsetting);
        pushButton_ScanSerial->setObjectName(QString::fromUtf8("pushButton_ScanSerial"));
        pushButton_ScanSerial->setGeometry(QRect(200, 5, 81, 51));
        pushButton_OpenSerial = new QPushButton(tab_commsetting);
        pushButton_OpenSerial->setObjectName(QString::fromUtf8("pushButton_OpenSerial"));
        pushButton_OpenSerial->setGeometry(QRect(200, 65, 81, 51));
        comboBox_SerialPort = new QComboBox(tab_commsetting);
        comboBox_SerialPort->setObjectName(QString::fromUtf8("comboBox_SerialPort"));
        comboBox_SerialPort->setGeometry(QRect(80, 20, 111, 31));
        comboBox_BaudRate = new QComboBox(tab_commsetting);
        comboBox_BaudRate->setObjectName(QString::fromUtf8("comboBox_BaudRate"));
        comboBox_BaudRate->setGeometry(QRect(80, 70, 111, 31));
        tabWidget_Settings->addTab(tab_commsetting, QString());
        tab_othsetting = new QWidget();
        tab_othsetting->setObjectName(QString::fromUtf8("tab_othsetting"));
        lineEdit_IPPort = new QLineEdit(tab_othsetting);
        lineEdit_IPPort->setObjectName(QString::fromUtf8("lineEdit_IPPort"));
        lineEdit_IPPort->setGeometry(QRect(70, 70, 51, 31));
        label_IPAddress = new QLabel(tab_othsetting);
        label_IPAddress->setObjectName(QString::fromUtf8("label_IPAddress"));
        label_IPAddress->setGeometry(QRect(10, 24, 72, 21));
        label_IPPort = new QLabel(tab_othsetting);
        label_IPPort->setObjectName(QString::fromUtf8("label_IPPort"));
        label_IPPort->setGeometry(QRect(10, 74, 72, 21));
        pushButton_ListenPort = new QPushButton(tab_othsetting);
        pushButton_ListenPort->setObjectName(QString::fromUtf8("pushButton_ListenPort"));
        pushButton_ListenPort->setGeometry(QRect(150, 60, 61, 41));
        pushButton_ClosePort = new QPushButton(tab_othsetting);
        pushButton_ClosePort->setObjectName(QString::fromUtf8("pushButton_ClosePort"));
        pushButton_ClosePort->setGeometry(QRect(220, 60, 51, 41));
        comboBox_IPAddress = new QComboBox(tab_othsetting);
        comboBox_IPAddress->setObjectName(QString::fromUtf8("comboBox_IPAddress"));
        comboBox_IPAddress->setGeometry(QRect(80, 20, 140, 31));
        tabWidget_Settings->addTab(tab_othsetting, QString());
        tab_readercontroller = new QWidget();
        tab_readercontroller->setObjectName(QString::fromUtf8("tab_readercontroller"));
        pushButton_RCSingle = new QPushButton(tab_readercontroller);
        pushButton_RCSingle->setObjectName(QString::fromUtf8("pushButton_RCSingle"));
        pushButton_RCSingle->setGeometry(QRect(30, 10, 93, 41));
        pushButton_RCBatch = new QPushButton(tab_readercontroller);
        pushButton_RCBatch->setObjectName(QString::fromUtf8("pushButton_RCBatch"));
        pushButton_RCBatch->setGeometry(QRect(30, 70, 93, 41));
        pushButton_RCEcho = new QPushButton(tab_readercontroller);
        pushButton_RCEcho->setObjectName(QString::fromUtf8("pushButton_RCEcho"));
        pushButton_RCEcho->setGeometry(QRect(150, 40, 93, 41));
        tabWidget_Settings->addTab(tab_readercontroller, QString());
        tab_RCSetting = new QWidget();
        tab_RCSetting->setObjectName(QString::fromUtf8("tab_RCSetting"));
        label_TimeDelay = new QLabel(tab_RCSetting);
        label_TimeDelay->setObjectName(QString::fromUtf8("label_TimeDelay"));
        label_TimeDelay->setGeometry(QRect(10, 70, 81, 21));
        lineEdit_TimeDelay = new QLineEdit(tab_RCSetting);
        lineEdit_TimeDelay->setObjectName(QString::fromUtf8("lineEdit_TimeDelay"));
        lineEdit_TimeDelay->setGeometry(QRect(102, 66, 151, 31));
        lineEdit_Resend = new QLineEdit(tab_RCSetting);
        lineEdit_Resend->setObjectName(QString::fromUtf8("lineEdit_Resend"));
        lineEdit_Resend->setGeometry(QRect(102, 16, 151, 31));
        label_Resend = new QLabel(tab_RCSetting);
        label_Resend->setObjectName(QString::fromUtf8("label_Resend"));
        label_Resend->setGeometry(QRect(30, 20, 72, 21));
        tabWidget_Settings->addTab(tab_RCSetting, QString());
        groupBox_Message = new QGroupBox(centralwidget);
        groupBox_Message->setObjectName(QString::fromUtf8("groupBox_Message"));
        groupBox_Message->setGeometry(QRect(340, 10, 471, 611));
        plainTextEdit_Message = new QPlainTextEdit(groupBox_Message);
        plainTextEdit_Message->setObjectName(QString::fromUtf8("plainTextEdit_Message"));
        plainTextEdit_Message->setGeometry(QRect(3, 20, 461, 581));
        verticalScrollBar_Message = new QScrollBar(groupBox_Message);
        verticalScrollBar_Message->setObjectName(QString::fromUtf8("verticalScrollBar_Message"));
        verticalScrollBar_Message->setGeometry(QRect(442, 21, 21, 579));
        verticalScrollBar_Message->setOrientation(Qt::Vertical);
        groupBox_Brand = new QGroupBox(centralwidget);
        groupBox_Brand->setObjectName(QString::fromUtf8("groupBox_Brand"));
        groupBox_Brand->setGeometry(QRect(10, 20, 291, 71));
        comboBox_Brand = new QComboBox(groupBox_Brand);
        comboBox_Brand->setObjectName(QString::fromUtf8("comboBox_Brand"));
        comboBox_Brand->setGeometry(QRect(10, 20, 271, 31));
        checkBox_Amt = new QCheckBox(centralwidget);
        checkBox_Amt->setObjectName(QString::fromUtf8("checkBox_Amt"));
        checkBox_Amt->setGeometry(QRect(200, 118, 121, 31));
        checkBox_Amt->setTabletTracking(false);
        checkBox_Amt->setAcceptDrops(false);
        checkBox_Amt->setAutoFillBackground(false);
        checkBox_Amt->setIconSize(QSize(30, 30));
        checkBox_Amt->setChecked(true);
        checkBox_AmtOther = new QCheckBox(centralwidget);
        checkBox_AmtOther->setObjectName(QString::fromUtf8("checkBox_AmtOther"));
        checkBox_AmtOther->setGeometry(QRect(200, 198, 121, 19));
        checkBox_AmtOther->setChecked(true);
        checkBox_TransType = new QCheckBox(centralwidget);
        checkBox_TransType->setObjectName(QString::fromUtf8("checkBox_TransType"));
        checkBox_TransType->setGeometry(QRect(200, 273, 111, 19));
        checkBox_TransType->setChecked(true);
        groupBox_TransType_2 = new QGroupBox(centralwidget);
        groupBox_TransType_2->setObjectName(QString::fromUtf8("groupBox_TransType_2"));
        groupBox_TransType_2->setGeometry(QRect(10, 320, 141, 61));
        lineEdit_TransType_2 = new QLineEdit(groupBox_TransType_2);
        lineEdit_TransType_2->setObjectName(QString::fromUtf8("lineEdit_TransType_2"));
        lineEdit_TransType_2->setGeometry(QRect(10, 20, 121, 31));
        groupBox_TransType_4 = new QGroupBox(centralwidget);
        groupBox_TransType_4->setObjectName(QString::fromUtf8("groupBox_TransType_4"));
        groupBox_TransType_4->setGeometry(QRect(10, 380, 141, 61));
        lineEdit_TransType_4 = new QLineEdit(groupBox_TransType_4);
        lineEdit_TransType_4->setObjectName(QString::fromUtf8("lineEdit_TransType_4"));
        lineEdit_TransType_4->setGeometry(QRect(10, 20, 121, 31));
        XGD_HOST->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(XGD_HOST);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        XGD_HOST->setStatusBar(statusbar);
        menubar = new QMenuBar(XGD_HOST);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1320, 23));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        menuLog_File = new QMenu(menu_F);
        menuLog_File->setObjectName(QString::fromUtf8("menuLog_File"));
        XGD_HOST->setMenuBar(menubar);

        menubar->addAction(menu_F->menuAction());
        menu_F->addAction(menuLog_File->menuAction());
        menuLog_File->addAction(action_Open);
        menuLog_File->addAction(action_Close);

        retranslateUi(XGD_HOST);

        tabWidget_Settings->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(XGD_HOST);
    } // setupUi

    void retranslateUi(QMainWindow *XGD_HOST)
    {
        XGD_HOST->setWindowTitle(QCoreApplication::translate("XGD_HOST", "XGD_HOST", nullptr));
        action_Open->setText(QCoreApplication::translate("XGD_HOST", "Open", nullptr));
        action_Close->setText(QCoreApplication::translate("XGD_HOST", " Close", nullptr));
        groupBox_Config->setTitle(QCoreApplication::translate("XGD_HOST", "Config", nullptr));
        label_AID->setText(QCoreApplication::translate("XGD_HOST", "AID", nullptr));
        pushButton_DownloadAid->setText(QCoreApplication::translate("XGD_HOST", "DownLoad", nullptr));
        label_CAPK->setText(QCoreApplication::translate("XGD_HOST", "CAPK", nullptr));
        pushButton_DownloadCAPK->setText(QCoreApplication::translate("XGD_HOST", "DownLoad", nullptr));
        label_ExceptionFile->setText(QCoreApplication::translate("XGD_HOST", "Exception File", nullptr));
        pushButton_DownloadExcet->setText(QCoreApplication::translate("XGD_HOST", "DownLoad", nullptr));
        label_DRL->setText(QCoreApplication::translate("XGD_HOST", "DRL", nullptr));
        pushButton_DownloadDRL->setText(QCoreApplication::translate("XGD_HOST", "DownLoad", nullptr));
        label_SimData->setText(QCoreApplication::translate("XGD_HOST", "SimData", nullptr));
        pushButton_DownloadSimdata->setText(QCoreApplication::translate("XGD_HOST", "DownLoad", nullptr));
        label_RevoKey->setText(QCoreApplication::translate("XGD_HOST", "RevoKey", nullptr));
        pushButton_DownloadRevokey->setText(QCoreApplication::translate("XGD_HOST", "DownLoad", nullptr));
        label_PreProcess->setText(QCoreApplication::translate("XGD_HOST", "PreProcess", nullptr));
        pushButton_DownloadPreprocess->setText(QCoreApplication::translate("XGD_HOST", "DownLoad", nullptr));
        groupBox_HostResCode->setTitle(QCoreApplication::translate("XGD_HOST", "Issuer Response Code", nullptr));
        groupBox_IssuerScript->setTitle(QCoreApplication::translate("XGD_HOST", "Issuer Script", nullptr));
        groupBox_HostAuthData->setTitle(QCoreApplication::translate("XGD_HOST", "Issuer Authentication Data", nullptr));
        groupBox_Amount->setTitle(QCoreApplication::translate("XGD_HOST", "Amount", nullptr));
        groupBox_AmtOther->setTitle(QCoreApplication::translate("XGD_HOST", "Amount Other", nullptr));
        groupBox_TransType->setTitle(QCoreApplication::translate("XGD_HOST", "TransType", nullptr));
        pushButton_StartTrans->setText(QCoreApplication::translate("XGD_HOST", "Start Trans", nullptr));
        pushButton_ClrMessage->setText(QCoreApplication::translate("XGD_HOST", "Clear", nullptr));
        label_SerialPort->setText(QCoreApplication::translate("XGD_HOST", "Port", nullptr));
        label_SerialBaud->setText(QCoreApplication::translate("XGD_HOST", "Baud", nullptr));
        pushButton_ScanSerial->setText(QCoreApplication::translate("XGD_HOST", "Scan", nullptr));
        pushButton_OpenSerial->setText(QCoreApplication::translate("XGD_HOST", "Open", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_commsetting), QCoreApplication::translate("XGD_HOST", "Serial Port", nullptr));
        lineEdit_IPPort->setText(QCoreApplication::translate("XGD_HOST", "8182", nullptr));
        label_IPAddress->setText(QCoreApplication::translate("XGD_HOST", "Address", nullptr));
        label_IPPort->setText(QCoreApplication::translate("XGD_HOST", "Port", nullptr));
        pushButton_ListenPort->setText(QCoreApplication::translate("XGD_HOST", "Listen", nullptr));
        pushButton_ClosePort->setText(QCoreApplication::translate("XGD_HOST", "Close", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_othsetting), QCoreApplication::translate("XGD_HOST", "NetWork", nullptr));
        pushButton_RCSingle->setText(QCoreApplication::translate("XGD_HOST", "Single", nullptr));
        pushButton_RCBatch->setText(QCoreApplication::translate("XGD_HOST", "Batch", nullptr));
        pushButton_RCEcho->setText(QCoreApplication::translate("XGD_HOST", "Echo", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_readercontroller), QCoreApplication::translate("XGD_HOST", "RC Test", nullptr));
        label_TimeDelay->setText(QCoreApplication::translate("XGD_HOST", "Time Delay", nullptr));
        lineEdit_TimeDelay->setText(QCoreApplication::translate("XGD_HOST", "1", nullptr));
        lineEdit_Resend->setText(QCoreApplication::translate("XGD_HOST", "3", nullptr));
        label_Resend->setText(QCoreApplication::translate("XGD_HOST", "Resend", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_RCSetting), QCoreApplication::translate("XGD_HOST", "RC Test Setting", nullptr));
        groupBox_Message->setTitle(QCoreApplication::translate("XGD_HOST", "Message", nullptr));
        groupBox_Brand->setTitle(QCoreApplication::translate("XGD_HOST", "Brand", nullptr));
        checkBox_Amt->setText(QCoreApplication::translate("XGD_HOST", "9F02 present", nullptr));
        checkBox_AmtOther->setText(QCoreApplication::translate("XGD_HOST", "9F03 present", nullptr));
        checkBox_TransType->setText(QCoreApplication::translate("XGD_HOST", "9C present", nullptr));
        groupBox_TransType_2->setTitle(QCoreApplication::translate("XGD_HOST", "TransType", nullptr));
        groupBox_TransType_4->setTitle(QCoreApplication::translate("XGD_HOST", "TransType", nullptr));
        menu_F->setTitle(QCoreApplication::translate("XGD_HOST", "File(&F)", nullptr));
        menuLog_File->setTitle(QCoreApplication::translate("XGD_HOST", "Log File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XGD_HOST: public Ui_XGD_HOST {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XGD_HOST_H
