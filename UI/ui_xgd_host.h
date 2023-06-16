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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XGD_HOST
{
public:
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
    QGroupBox *groupBox_Amount;
    QLineEdit *lineEdit_Amt;
    QGroupBox *groupBox_AmtOther;
    QLineEdit *lineEdit_AmtOther;
    QGroupBox *groupBox_TransType;
    QLineEdit *lineEdit_TransType;
    QPushButton *pushButton_StartTrans;
    QGroupBox *groupBox_HostResCode;
    QLineEdit *lineEdit_HostResCode;
    QGroupBox *groupBox_IssuerScript;
    QLineEdit *lineEdit_IssuerScript;
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
    QGroupBox *groupBox_Message;
    QTextEdit *textEdit_Message;
    QScrollBar *verticalScrollBar_Message;
    QGroupBox *groupBox_Brand;
    QComboBox *comboBox_Brand;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *XGD_HOST)
    {
        if (XGD_HOST->objectName().isEmpty())
            XGD_HOST->setObjectName(QString::fromUtf8("XGD_HOST"));
        XGD_HOST->resize(1320, 687);
        centralwidget = new QWidget(XGD_HOST);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_Config = new QGroupBox(centralwidget);
        groupBox_Config->setObjectName(QString::fromUtf8("groupBox_Config"));
        groupBox_Config->setGeometry(QRect(800, 20, 501, 571));
        comboBox_AID = new QComboBox(groupBox_Config);
        comboBox_AID->setObjectName(QString::fromUtf8("comboBox_AID"));
        comboBox_AID->setGeometry(QRect(130, 20, 191, 31));
        label_AID = new QLabel(groupBox_Config);
        label_AID->setObjectName(QString::fromUtf8("label_AID"));
        label_AID->setGeometry(QRect(20, 30, 72, 15));
        pushButton_DownloadAid = new QPushButton(groupBox_Config);
        pushButton_DownloadAid->setObjectName(QString::fromUtf8("pushButton_DownloadAid"));
        pushButton_DownloadAid->setGeometry(QRect(370, 20, 93, 31));
        label_CAPK = new QLabel(groupBox_Config);
        label_CAPK->setObjectName(QString::fromUtf8("label_CAPK"));
        label_CAPK->setGeometry(QRect(20, 80, 72, 15));
        comboBox_CAPK = new QComboBox(groupBox_Config);
        comboBox_CAPK->setObjectName(QString::fromUtf8("comboBox_CAPK"));
        comboBox_CAPK->setGeometry(QRect(130, 70, 191, 31));
        pushButton_DownloadCAPK = new QPushButton(groupBox_Config);
        pushButton_DownloadCAPK->setObjectName(QString::fromUtf8("pushButton_DownloadCAPK"));
        pushButton_DownloadCAPK->setGeometry(QRect(370, 70, 93, 31));
        label_ExceptionFile = new QLabel(groupBox_Config);
        label_ExceptionFile->setObjectName(QString::fromUtf8("label_ExceptionFile"));
        label_ExceptionFile->setGeometry(QRect(11, 130, 111, 20));
        comboBox_ExceptionFile = new QComboBox(groupBox_Config);
        comboBox_ExceptionFile->setObjectName(QString::fromUtf8("comboBox_ExceptionFile"));
        comboBox_ExceptionFile->setGeometry(QRect(130, 120, 191, 31));
        pushButton_DownloadExcet = new QPushButton(groupBox_Config);
        pushButton_DownloadExcet->setObjectName(QString::fromUtf8("pushButton_DownloadExcet"));
        pushButton_DownloadExcet->setGeometry(QRect(370, 120, 93, 31));
        label_DRL = new QLabel(groupBox_Config);
        label_DRL->setObjectName(QString::fromUtf8("label_DRL"));
        label_DRL->setGeometry(QRect(10, 180, 111, 20));
        comboBox_DRL = new QComboBox(groupBox_Config);
        comboBox_DRL->setObjectName(QString::fromUtf8("comboBox_DRL"));
        comboBox_DRL->setGeometry(QRect(130, 170, 191, 31));
        pushButton_DownloadDRL = new QPushButton(groupBox_Config);
        pushButton_DownloadDRL->setObjectName(QString::fromUtf8("pushButton_DownloadDRL"));
        pushButton_DownloadDRL->setGeometry(QRect(370, 170, 93, 31));
        label_SimData = new QLabel(groupBox_Config);
        label_SimData->setObjectName(QString::fromUtf8("label_SimData"));
        label_SimData->setGeometry(QRect(10, 230, 111, 20));
        comboBox_SimData = new QComboBox(groupBox_Config);
        comboBox_SimData->setObjectName(QString::fromUtf8("comboBox_SimData"));
        comboBox_SimData->setGeometry(QRect(130, 220, 191, 31));
        pushButton_DownloadSimdata = new QPushButton(groupBox_Config);
        pushButton_DownloadSimdata->setObjectName(QString::fromUtf8("pushButton_DownloadSimdata"));
        pushButton_DownloadSimdata->setGeometry(QRect(370, 220, 93, 31));
        label_RevoKey = new QLabel(groupBox_Config);
        label_RevoKey->setObjectName(QString::fromUtf8("label_RevoKey"));
        label_RevoKey->setGeometry(QRect(10, 290, 111, 20));
        comboBox_Revokey = new QComboBox(groupBox_Config);
        comboBox_Revokey->setObjectName(QString::fromUtf8("comboBox_Revokey"));
        comboBox_Revokey->setGeometry(QRect(130, 280, 191, 31));
        pushButton_DownloadRevokey = new QPushButton(groupBox_Config);
        pushButton_DownloadRevokey->setObjectName(QString::fromUtf8("pushButton_DownloadRevokey"));
        pushButton_DownloadRevokey->setGeometry(QRect(370, 280, 93, 31));
        label_PreProcess = new QLabel(groupBox_Config);
        label_PreProcess->setObjectName(QString::fromUtf8("label_PreProcess"));
        label_PreProcess->setGeometry(QRect(10, 350, 111, 20));
        comboBox_PreProcess = new QComboBox(groupBox_Config);
        comboBox_PreProcess->setObjectName(QString::fromUtf8("comboBox_PreProcess"));
        comboBox_PreProcess->setGeometry(QRect(130, 340, 191, 31));
        pushButton_DownloadPreprocess = new QPushButton(groupBox_Config);
        pushButton_DownloadPreprocess->setObjectName(QString::fromUtf8("pushButton_DownloadPreprocess"));
        pushButton_DownloadPreprocess->setGeometry(QRect(370, 340, 93, 31));
        groupBox_Amount = new QGroupBox(centralwidget);
        groupBox_Amount->setObjectName(QString::fromUtf8("groupBox_Amount"));
        groupBox_Amount->setGeometry(QRect(10, 120, 141, 61));
        lineEdit_Amt = new QLineEdit(groupBox_Amount);
        lineEdit_Amt->setObjectName(QString::fromUtf8("lineEdit_Amt"));
        lineEdit_Amt->setGeometry(QRect(10, 20, 121, 31));
        groupBox_AmtOther = new QGroupBox(centralwidget);
        groupBox_AmtOther->setObjectName(QString::fromUtf8("groupBox_AmtOther"));
        groupBox_AmtOther->setGeometry(QRect(160, 120, 141, 61));
        lineEdit_AmtOther = new QLineEdit(groupBox_AmtOther);
        lineEdit_AmtOther->setObjectName(QString::fromUtf8("lineEdit_AmtOther"));
        lineEdit_AmtOther->setGeometry(QRect(10, 20, 121, 31));
        groupBox_TransType = new QGroupBox(centralwidget);
        groupBox_TransType->setObjectName(QString::fromUtf8("groupBox_TransType"));
        groupBox_TransType->setGeometry(QRect(10, 190, 141, 61));
        lineEdit_TransType = new QLineEdit(groupBox_TransType);
        lineEdit_TransType->setObjectName(QString::fromUtf8("lineEdit_TransType"));
        lineEdit_TransType->setGeometry(QRect(10, 20, 121, 31));
        pushButton_StartTrans = new QPushButton(centralwidget);
        pushButton_StartTrans->setObjectName(QString::fromUtf8("pushButton_StartTrans"));
        pushButton_StartTrans->setGeometry(QRect(190, 200, 101, 41));
        groupBox_HostResCode = new QGroupBox(centralwidget);
        groupBox_HostResCode->setObjectName(QString::fromUtf8("groupBox_HostResCode"));
        groupBox_HostResCode->setGeometry(QRect(10, 260, 291, 61));
        lineEdit_HostResCode = new QLineEdit(groupBox_HostResCode);
        lineEdit_HostResCode->setObjectName(QString::fromUtf8("lineEdit_HostResCode"));
        lineEdit_HostResCode->setGeometry(QRect(10, 20, 271, 31));
        groupBox_IssuerScript = new QGroupBox(centralwidget);
        groupBox_IssuerScript->setObjectName(QString::fromUtf8("groupBox_IssuerScript"));
        groupBox_IssuerScript->setGeometry(QRect(10, 330, 291, 61));
        lineEdit_IssuerScript = new QLineEdit(groupBox_IssuerScript);
        lineEdit_IssuerScript->setObjectName(QString::fromUtf8("lineEdit_IssuerScript"));
        lineEdit_IssuerScript->setGeometry(QRect(10, 20, 271, 31));
        pushButton_ClrMessage = new QPushButton(centralwidget);
        pushButton_ClrMessage->setObjectName(QString::fromUtf8("pushButton_ClrMessage"));
        pushButton_ClrMessage->setGeometry(QRect(190, 400, 93, 28));
        tabWidget_Settings = new QTabWidget(centralwidget);
        tabWidget_Settings->setObjectName(QString::fromUtf8("tabWidget_Settings"));
        tabWidget_Settings->setGeometry(QRect(10, 440, 291, 151));
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
        tabWidget_Settings->addTab(tab_othsetting, QString());
        groupBox_Message = new QGroupBox(centralwidget);
        groupBox_Message->setObjectName(QString::fromUtf8("groupBox_Message"));
        groupBox_Message->setGeometry(QRect(310, 10, 471, 581));
        textEdit_Message = new QTextEdit(groupBox_Message);
        textEdit_Message->setObjectName(QString::fromUtf8("textEdit_Message"));
        textEdit_Message->setGeometry(QRect(3, 20, 461, 551));
        verticalScrollBar_Message = new QScrollBar(groupBox_Message);
        verticalScrollBar_Message->setObjectName(QString::fromUtf8("verticalScrollBar_Message"));
        verticalScrollBar_Message->setGeometry(QRect(443, 21, 20, 549));
        verticalScrollBar_Message->setOrientation(Qt::Vertical);
        groupBox_Brand = new QGroupBox(centralwidget);
        groupBox_Brand->setObjectName(QString::fromUtf8("groupBox_Brand"));
        groupBox_Brand->setGeometry(QRect(10, 20, 291, 71));
        comboBox_Brand = new QComboBox(groupBox_Brand);
        comboBox_Brand->setObjectName(QString::fromUtf8("comboBox_Brand"));
        comboBox_Brand->setGeometry(QRect(10, 20, 271, 31));
        XGD_HOST->setCentralWidget(centralwidget);
        menubar = new QMenuBar(XGD_HOST);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1320, 26));
        XGD_HOST->setMenuBar(menubar);
        statusbar = new QStatusBar(XGD_HOST);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        XGD_HOST->setStatusBar(statusbar);

        retranslateUi(XGD_HOST);

        tabWidget_Settings->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(XGD_HOST);
    } // setupUi

    void retranslateUi(QMainWindow *XGD_HOST)
    {
        XGD_HOST->setWindowTitle(QCoreApplication::translate("XGD_HOST", "XGD_HOST", nullptr));
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
        groupBox_Amount->setTitle(QCoreApplication::translate("XGD_HOST", "Amount", nullptr));
        groupBox_AmtOther->setTitle(QCoreApplication::translate("XGD_HOST", "Amount Other", nullptr));
        groupBox_TransType->setTitle(QCoreApplication::translate("XGD_HOST", "TransType", nullptr));
        pushButton_StartTrans->setText(QCoreApplication::translate("XGD_HOST", "Start Trans", nullptr));
        groupBox_HostResCode->setTitle(QCoreApplication::translate("XGD_HOST", "Issuer Response Code", nullptr));
        groupBox_IssuerScript->setTitle(QCoreApplication::translate("XGD_HOST", "Issuer Script", nullptr));
        pushButton_ClrMessage->setText(QCoreApplication::translate("XGD_HOST", "Clear", nullptr));
        label_SerialPort->setText(QCoreApplication::translate("XGD_HOST", "Port", nullptr));
        label_SerialBaud->setText(QCoreApplication::translate("XGD_HOST", "Baud", nullptr));
        pushButton_ScanSerial->setText(QCoreApplication::translate("XGD_HOST", "Scan", nullptr));
        pushButton_OpenSerial->setText(QCoreApplication::translate("XGD_HOST", "Open", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_commsetting), QCoreApplication::translate("XGD_HOST", "Serial Port", nullptr));
        tabWidget_Settings->setTabText(tabWidget_Settings->indexOf(tab_othsetting), QCoreApplication::translate("XGD_HOST", "Other Setting", nullptr));
        groupBox_Message->setTitle(QCoreApplication::translate("XGD_HOST", "Message", nullptr));
        groupBox_Brand->setTitle(QCoreApplication::translate("XGD_HOST", "Brand", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XGD_HOST: public Ui_XGD_HOST {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XGD_HOST_H
