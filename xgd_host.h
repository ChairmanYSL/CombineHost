#ifndef XGD_HOST_H
#define XGD_HOST_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QMap>
#include <QtXml>
#include <QFile>
#include <QProcess>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QList>
#include <QTextCursor>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHttpPart>
#include <QUdpSocket>
#include <QAbstractSocket>
#include "tcpserver.h"
#include <QtNetwork/QNetworkInterface>

#define STX 0x02
#define COMMU_SERIAL 0x03
#define COMMU_TCP    0x04

QT_BEGIN_NAMESPACE
namespace Ui { class XGD_HOST; }
QT_END_NAMESPACE

class XGD_HOST : public QMainWindow
{
    Q_OBJECT

public:
    XGD_HOST(QWidget *parent = nullptr);
    ~XGD_HOST();

    enum MsgType
    {
        FINANCE_REQ_SEND = 1,
        AUTHORIZE_REQ_SEND,
        FINANCE_CONFIRM_SEND,
        BATCH_UPLOAD_SEND,
        ADVICE_SEND,
        REDO_SEND,
        FIALFLOW_UPLOAD_SEND,
        RC_DOWNLOAD_CONFIG=10,

        FINANCE_REQ_RECV = 65, //0x41
        AUTHORIZE_REQ_RECV,
        FINANCE_CONFIRM_RECV,
        BATCH_UPLOAD_RECV,
        ADVICE_RECV,
        REDO_RECV,
        FIALFLOW_UPLOAD_RECV,

        TRANS_REQ_SEND = 128, //0x80
        TRANS_RESULT_SEND,
        CAPK_DOWNLOAD_SEND,
        AID_DOWNLOAD_SEND,
        SIMDATA_DOWNLOAD_SEND,
        BLACKLIST_DOWNLOAD_SEND,
        REVOKEY_DOWNLOAD_SEND,
        ELECCHIP_ELECSIGN_SEND,
        DRL_DOWNLOAD_SEND,
        TERM_OUTCOME_SEND,

        TRANS_REQ_RECV = 192, //0xC0
        TRANS_RESULT_RECV,
        CAPK_DOWNLOAD_RECV,
        AID_DOWNLOAD_RECV,
        SIMDATA_DOWNLOAD_RECV,
        BLACKLIST_DOWNLOAD_RECV,
        REVOKEY_DOWNLOAD_RECV,
        ELECCHIP_ELECSIGN_RECV,
        DRL_DOWNLOAD_RECV,
        TERM_OUTCOME_RECV,
        RC_UPLOAD_RESULT,
    };

    QMap<QString, QString> tlv_map;   //hashmap,function is similar to avl tree in emvbase,it provides key-value data-struct to save tags
    int tlv2qmap(QByteArray tlv_data);
    void tlv2qmap(QString tlv_data, QMap<QString, QString> &p_map);
    QString select_file_name;
//    QDomDocument xml_doc;
    QMap<QString, quint8> config_load_map;
    bool AmtPresentFlag=true;
    bool AmtOtherPresentFlag=true;
    bool TransTypePresentFlag=true;

private slots:
    void on_pushButton_ScanSerial_clicked();

    void on_pushButton_OpenSerial_clicked();

    void on_pushButton_ClrMessage_clicked();

    void handleError(QSerialPort::SerialPortError error);

    void readTermData();

    void on_comboBox_Brand_currentTextChanged(const QString &arg1);

    void on_pushButton_DownloadAid_clicked();

    void on_pushButton_DownloadCAPK_clicked();

    void on_verticalScrollBar_Message_sliderMoved(int position);

    void on_pushButton_DownloadExcet_clicked();

    void on_pushButton_StartTrans_clicked();

    void on_checkBox_Amt_stateChanged(int arg1);

    void on_checkBox_AmtOther_stateChanged(int arg1);

    void on_checkBox_TransType_stateChanged(int arg1);

//    void on_action_Close_stateChanged(int arg1);

//    void on_action_Open_stateChanged(int arg1);


    void on_pushButton_DownloadSimdata_clicked();

    void on_pushButton_DownloadRevokey_clicked();

    void on_pushButton_DownloadDRL_clicked();

    void on_pushButton_RCSingle_clicked();

    void on_pushButton_RCBatch_clicked();

    void resend_http_get();

    void on_pushButton_RCEcho_clicked();

    void on_pushButton_ListenPort_clicked();

    void on_pushButton_ClosePort_clicked();

    void on_tabWidget_Settings_tabBarClicked(int index);

private:
    Ui::XGD_HOST *ui;
    QSerialPort m_serial;
    QString cur_brand;
    QString cur_config_dir;
    QByteArray download_counter;
    QString cur_IPPort;
    QString cur_IPAddress;
    QByteArray dataFromHttp;
    QTimer timer;
    QByteArray dataFromTerm;
    int resend;
    bool batchReceive = false;
    bool AutoFlag = false;
    QUdpSocket m_udpsock;
    TCPServer m_tcpserver;
    int commuType;

    void init_tlv_map();
    void open_log();
    void close_log();
    void init_config_dir();
    void deal_term_data(QByteArray term_data, MsgType msg_type);
    void deal_finance_request();
    void show_message(QString text);
    void deal_authorize_request();
    void deal_finance_confirm();
    void deal_batch_upload();
    void deal_advice(QByteArray term_data);
    void deal_redo(QByteArray term_data);
    void deal_failflow_upload(QByteArray term_data);
    void deal_trans_request();
    void deal_trans_result();
    void deal_capk_download();
    void deal_aid_download();
    void deal_simdata_download();
    void deal_blacklist_download();
    void deal_revokey_download();
    void deal_elecchip_elecsign(QByteArray term_data);
    void deal_drl_download();
//    void deal_config_download(QString config_type, MsgType msg_type);
    void deal_term_outcome();
    void show_trans_result(QString cardBrand, quint8 trans_result);
    void show_trans_outcome(QString cardBrand, quint8 trans_outcome);
    void show_trans_outcome(QString outcome);
    void show_ui(QString ui_str);
    void show_data_record(QString data_record);
    void serialRead();
    void show_uiRequest(QString UIRequest, int step);
    void deal_http_get(QNetworkReply *reply);
    void deal_http_post(QByteArray dataSend);
    void deal_http_trace(QNetworkReply *reply);
    int send_http_get();
    void handleUDPPortData();
    void udpRead();
    void deal_tcp_data(QByteArray data);
};
#endif // XGD_HOST_H
