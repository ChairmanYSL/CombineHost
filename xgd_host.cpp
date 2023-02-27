#include "xgd_host.h"
#include "ui_xgd_host.h"
#include "tool.h"

XGD_HOST::XGD_HOST(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::XGD_HOST)
{
    ui->setupUi(this);
    //init display baud rate list
    QStringList BaudRate;
    BaudRate << "1200"<< "2400"<< "4800"<< "9600"<< "14400"<<"19200"<<"38400"<<"56000"<<"576000"<<"115200"<<"230400"<<"460800"<<"921600";
    ui->comboBox_BaudRate->addItems(BaudRate);
    ui->comboBox_BaudRate->setCurrentIndex(9);

    //init display brand list
    init_config_dir();

    //init config download counter map
    config_load_map.insert("AID_Counter", 0);
    config_load_map.insert("AID_Cur_Index", 0);
    config_load_map.insert("CAPK_Counter", 0);
    config_load_map.insert("CAPK_Cur_Index", 0);
    config_load_map.insert("ExecptionFile_Counter", 0);
    config_load_map.insert("ExecptionFile_Cur_Index", 0);
    config_load_map.insert("DRL_Counter", 0);
    config_load_map.insert("DRL_Cur_Index", 0);
    config_load_map.insert("SimData_Counter", 0);
    config_load_map.insert("SimData_Cur_Index", 0);
    config_load_map.insert("Revokey_Counter", 0);
    config_load_map.insert("Revokey_Cur_Index", 0);
    config_load_map.insert("PreProcess_Counter", 0);
    config_load_map.insert("PreProcess_Cur_Index", 0);

//    QMapIterator<QString, quint8> it(config_load_map);
//    while(it.hasNext())
//    {
//        it.next();
//        qDebug()<<it.key()<<":"<<it.value();
//    }

    //init input num and format
    ui->lineEdit_Amt->setText("0.01");
    ui->lineEdit_AmtOther->setText("0.00");
    ui->lineEdit_TransType->setText("00");
    ui->lineEdit_HostResCode->setText("00");

    QRegExp regexp_amt("^([0-9]{1,10}.[0-9]{2})$");
    ui->lineEdit_Amt->setValidator(new QRegExpValidator(regexp_amt, this));
    ui->lineEdit_AmtOther->setValidator(new QRegExpValidator(regexp_amt, this));
    QRegExp regexp_transtype("[0-9]{2}");
    ui->lineEdit_TransType->setValidator(new QRegExpValidator(regexp_transtype, this));

    //init Message Text
    ui->plainTextEdit_Message->clear();
    ui->plainTextEdit_Message->setReadOnly(true);
    ui->plainTextEdit_Message->setVerticalScrollBar(ui->verticalScrollBar_Message);
    ui->plainTextEdit_Message->insertPlainText("Welcome!\n");

    connect(ui->action_Open, &QAction::triggered, this, &XGD_HOST::open_log);
    connect(ui->action_Close, &QAction::triggered, this, &XGD_HOST::close_log);
}

XGD_HOST::~XGD_HOST()
{
    m_serial.close();
    delete ui;
}

void XGD_HOST::init_config_dir()
{
    QStringList CardBrand;
    cur_config_dir = QCoreApplication::applicationDirPath() + "/Config";
    QDir dir;
    QStringList file_list;

    //init card brand
    dir.setPath(cur_config_dir);
    if(dir.exists())
    {
        CardBrand = dir.entryList();
        qDebug()<<"CardBrand.count: "<<CardBrand.count();
        if(CardBrand.count() > 2)
        {
            CardBrand.removeFirst();    //remove '.' and '..'
            CardBrand.removeFirst();

            ui->comboBox_Brand->addItems(CardBrand);
            cur_brand = CardBrand.at(0);
        }
    }

    if(cur_brand.isEmpty() == false)
    {
        //init AID config list
        ui->comboBox_AID->clear();
        dir.setPath(cur_config_dir+"/"+cur_brand+"/AID");
        if(dir.exists())
        {
            file_list = dir.entryList();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_AID->addItems(file_list);
            }
        }
        //init CAPK config list
        ui->comboBox_CAPK->clear();
        dir.setPath(cur_config_dir+"/"+cur_brand+"/CAPK");
        if(dir.exists())
        {
            file_list = dir.entryList();
            qDebug()<<"file list count"<<file_list.count();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_CAPK->addItems(file_list);
            }
        }
        //init Exception File config list
        ui->comboBox_ExceptionFile->clear();
        dir.setPath(cur_config_dir+"/"+cur_brand+"/Exception_File");
        if(dir.exists())
        {
            file_list = dir.entryList();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_ExceptionFile->addItems(file_list);
            }
        }
        //init PreProcess config list
        ui->comboBox_PreProcess->clear();
        dir.setPath(cur_config_dir+"/"+cur_brand+"/PreProcess");
        if(dir.exists())
        {
            file_list = dir.entryList();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_PreProcess->addItems(file_list);
            }
        }
        //init Revocation_CAPK config list
        ui->comboBox_Revokey->clear();
        dir.setPath(cur_config_dir+"/"+cur_brand+"/Revocation_CAPK");
        if(dir.exists())
        {
            file_list = dir.entryList();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_Revokey->addItems(file_list);
            }
        }
        //init SimData config list
        ui->comboBox_SimData->clear();
        dir.setPath(cur_config_dir+"/"+cur_brand+"/SimData");
        if(dir.exists())
        {
            file_list = dir.entryList();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_SimData->addItems(file_list);
            }
        }
        //init DRL config list
        ui->comboBox_DRL->clear();
        dir.setPath(cur_config_dir+"/"+cur_brand+"/DRL");
        if(dir.exists())
        {
            file_list = dir.entryList();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_DRL->addItems(file_list);
            }
        }
    }
}

void XGD_HOST::on_pushButton_ScanSerial_clicked()
{
    ui->comboBox_SerialPort->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info: infos)
    {
        QSerialPort serial_port;
        serial_port.setPort(info);
        ui->comboBox_SerialPort->addItem(info.portName());
    }
}

void XGD_HOST::on_pushButton_OpenSerial_clicked()
{
    QString serialport_name;
    QByteArray recv_term_data;
    QString cur_baud_rate;

    serialport_name = ui->comboBox_SerialPort->currentText().toUtf8();

    m_serial.setPortName(serialport_name);

    if(m_serial.isOpen() == true)
    {
        m_serial.close();
    }
    m_serial.open(QIODevice::ReadWrite);
    if(m_serial.isOpen() != true)
    {
        QMessageBox::critical(this, "Error", "Open Serial Port Error!!!");
        return;
    }
    show_message("open "+serialport_name+" Success!\n");

    cur_baud_rate = ui->comboBox_BaudRate->currentText();
    m_serial.setBaudRate(cur_baud_rate.toUInt());
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);

    connect(&m_serial, &QSerialPort::errorOccurred, this, &XGD_HOST::handleError);
    connect(&m_serial, &QSerialPort::readyRead, this, &XGD_HOST::readTermData);
}

void XGD_HOST::handleError(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::ResourceError)
    {
        QMessageBox::critical(this, "Error", "Serial Erro Code:"+m_serial.errorString());
        m_serial.close();
    }
}

void XGD_HOST::readTermData()
{
    QByteArray term_data = m_serial.readAll();

    if(term_data.isEmpty())
    {
        qDebug()<<"Recv Term Data is null!"<<endl;
        QMessageBox::information(this, "info", "Receive Term Data is Null");
        return ;
    }

    TraceHexFromByteArray("Recv Term Data" ,term_data);

    if(term_data.at(0) != 0x02)
    {
        QMessageBox::critical(this, "Error", "Error protocol header!!!");
        return ;
    }

    char temp = term_data.data()[1];
    deal_term_data(term_data, (XGD_HOST::MsgType)(quint8)temp);
    m_serial.flush();
}

void XGD_HOST::on_pushButton_ClrMessage_clicked()
{
    ui->plainTextEdit_Message->clear();
}

void XGD_HOST::tlv2qmap(QString tlv_data, QMap<QString, QString> &p_map)
{
    int i = 0,t_len,l_len,v_len;
    QByteArray Tag_Byte, Value_Byte, temp_byte;
    QString Tag_str,Value_str;

    convertStringToHex(tlv_data, temp_byte);

    qDebug()<<"in tlv2qmap tlv data len: "<<temp_byte.length();
    while(i < temp_byte.length())
    {
        //judge T
        if((temp_byte.data()[i] & 0x1F) == 0x1F)
        {
            if((temp_byte.data()[i+1] & 0x80) == 0x80)
            {
                t_len = 3;
            }
            else
            {
                t_len = 2;
            }
        }
        else
        {
            t_len = 1;
        }
        qDebug()<<"t_len:"<<t_len;
        Tag_Byte = temp_byte.mid(i, t_len);
        qDebug()<<"Tag in hex: "<<Tag_Byte;
        //judge L
        i += t_len;
        if((temp_byte.data()[i] & 0x80) == 0x80)
        {
            l_len = (int)(temp_byte.data()[i] & 0x7F) + 1;
        }
        else
        {
            l_len = 1;
        }
        qDebug()<<"l_len:"<<t_len;

        switch (l_len)
        {
            case 1:
                v_len = (int)temp_byte.at(i);
                break;
            case 2:
                v_len = (quint16)temp_byte.at(i+1) + (quint16)(temp_byte.at(i)<<8);
                break;
            case 3:
                v_len = (quint32)temp_byte.at(i+2) + (quint32)(temp_byte.at(i+1)<<8) + (quint32)(temp_byte.at(i) << 16);
                break;
            default:
                return ;
        }
        qDebug()<<"v_len:"<<v_len;
        i+=l_len;
        //judge V
        Value_Byte = temp_byte.mid(i, v_len);
        i+=v_len;
        qDebug()<<"Value in hex:"<<Value_Byte;
        Value_str = convertHexToString(Value_Byte);
        Tag_str = convertHexToString(Tag_Byte);
        p_map.insert(Tag_str, Value_str);
    }

    QMapIterator<QString, QString> it(p_map);
    while (it.hasNext())
    {
        it.next();
        qDebug()<<it.key()<<":"<<it.value();
    }
}

int XGD_HOST::tlv2qmap(QByteArray tlv_data)
{
    int i = 0,t_len,l_len,v_len;
    QByteArray Tag_Byte, Value_Byte;
    QString Tag_str,Value_str;

    qDebug()<<"in tlv2qmap tlv data len: "<<tlv_data.length();
    while(i < tlv_data.length())
    {
        //judge T
        if((tlv_data.data()[i] & 0x1F) == 0x1F)
        {
            if((tlv_data.data()[i+1] & 0x80) == 0x80)
            {
                t_len = 3;
            }
            else
            {
                t_len = 2;
            }
        }
        else
        {
            t_len = 1;
        }
        qDebug()<<"t_len:"<<t_len;
        Tag_Byte = tlv_data.mid(i, t_len);
        qDebug()<<"Tag in hex: "<<Tag_Byte;
        //judge L
        i += t_len;
        if((tlv_data.data()[i] & 0x80) == 0x80)
        {
            l_len = (int)(tlv_data.data()[i] & 0x7F) + 1;
        }
        else
        {
            l_len = 1;
        }
        qDebug()<<"l_len:"<<t_len;

        switch (l_len)
        {
            case 1:
                v_len = (int)tlv_data.at(i);
                break;
            case 2:
                v_len = (quint16)tlv_data.at(i+1) + (quint16)(tlv_data.at(i)<<8);
                break;
            case 3:
                v_len = (quint32)tlv_data.at(i+2) + (quint32)(tlv_data.at(i+1)<<8) + (quint32)(tlv_data.at(i) << 16);
                break;
            default:
                return -1;
        }
        qDebug()<<"v_len:"<<v_len;
        i+=l_len;
        //judge V
        Value_Byte = tlv_data.mid(i, v_len);
        i+=v_len;
        qDebug()<<"Value in hex:"<<Value_Byte;
        Value_str = convertHexToString(Value_Byte);
        Tag_str = convertHexToString(Tag_Byte);
        tlv_map.insert(Tag_str, Value_str);
    }

    QMapIterator<QString, QString> it(tlv_map);
    while (it.hasNext())
    {
        it.next();
        qDebug()<<it.key()<<":"<<it.value();
    }

    return 0;
}

void XGD_HOST::deal_term_data(QByteArray term_data, MsgType msg_type)
{
    QByteArray tlv_data;
    int data_len,ret;
    QString disp_message;

    qDebug()<<"msg_type:"<<msg_type;

    switch (msg_type)
    {
        case AID_DOWNLOAD_RECV:
            deal_aid_download();
            return ;    //this item don't need parse tlv
        case CAPK_DOWNLOAD_RECV:
            deal_capk_download();
            return ;    //this item don't need parse tlv
        case SIMDATA_DOWNLOAD_RECV:
            deal_simdata_download();
            return ;    //this item don't need parse tlv
        case BLACKLIST_DOWNLOAD_RECV:
            deal_blacklist_download();
            return ;    //this item don't need parse tlv
        case REVOKEY_DOWNLOAD_RECV:
            deal_revokey_download();
            return ;    //this item don't need parse tlv
        case DRL_DOWNLOAD_RECV:
            deal_drl_download();
            return ;    //this item don't need parse tlv
        case TRANS_REQ_RECV:
            deal_trans_request();
            return ;    //this item don't need parse tlv
        case ADVICE_RECV:
            show_message("Advice Message:\n");
            deal_advice(term_data);
            return ;

        default:
            break;
    }

    //below item need parse tlv
    data_len = (quint8)(term_data.data()[2])*256 + (quint8)(term_data.data()[3]);
    tlv_data = term_data.mid(4,data_len);

    qDebug()<<"reveive tlv data len:"<<data_len;
    qDebug()<<"reveive tlv data :"<<tlv_data;

    tlv_map.clear();
    ret =  tlv2qmap(tlv_data);
    if(ret != 0)
    {
        qDebug()<<"Parse TLV error!"<<endl;
    }

    switch (msg_type)
    {
        case FINANCE_REQ_RECV:
            show_message("Finance Request Message:\n");
            deal_finance_request();
            break;
        case AUTHORIZE_REQ_RECV:
            show_message("Authorization Request Message:\n");
            deal_authorize_request();
            break;
        case FINANCE_CONFIRM_RECV:
            show_message("Finance Confirm Message:\n");
            deal_finance_confirm();
            break;
        case BATCH_UPLOAD_RECV:
            show_message("Batch Upload Message:\n");
            deal_batch_upload();
            break;
        case REDO_RECV:
            show_message("Redo Message:\n");
            break;
        case FIALFLOW_UPLOAD_RECV:
            show_message("Upload Fail-Flow Message:\n");
            break;
        case TRANS_RESULT_RECV:
            show_message("Transaction Result Message:\n");
            deal_trans_result();
            break;
        case ELECCHIP_ELECSIGN_RECV:
            show_message("Elctric Chip && Elctric Sign Message:\n");
            break;
        case TERM_OUTCOME_RECV:
            show_message("Terminal OutCome Message:\n");
            deal_term_outcome();
            break;
        default:
            QMessageBox::critical(this, "Error", "Error protocol MsgType!!!");
            return ;
    }
}

void XGD_HOST::show_message(QString text)
{
    if(!ui->plainTextEdit_Message->isReadOnly())
    {
        ui->plainTextEdit_Message->setReadOnly(true);
    }
    //move mouse cursor to end of text
    ui->plainTextEdit_Message->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

    if(ui->plainTextEdit_Message->toPlainText().size()>1024*1024*4)
    {
        ui->plainTextEdit_Message->clear();
    }
    ui->plainTextEdit_Message->insertPlainText(text);
    //slide scrollbar to bottom
    ui->verticalScrollBar_Message->setSliderPosition(ui->verticalScrollBar_Message->maximum());
}

void XGD_HOST::deal_simdata_download()
{
    QByteArray send_data,temp;
    int send_data_len = 0;
    char high,low;

    send_data.clear();
    send_data.append(STX);
    send_data.append(SIMDATA_DOWNLOAD_SEND);

    if(config_load_map.find("SimData_Cur_Index").value() == (config_load_map.find("SimData_Counter").value())) //find no aid to download,finish
    {
        qDebug()<<"SimData_Cur_Index: "<< config_load_map.find("SimData_Cur_Index").value();
        qDebug()<<"SimData_Counter: "<< config_load_map.find("SimData_Counter").value();
        qDebug()<<"no SimData to download!!!";
        QString endLine("0003030100");
        temp.clear();
        convertStringToHex(endLine, temp);
        send_data.append(temp);
        qDebug()<<"send data:"<<send_data;
        m_serial.write(send_data);
        config_load_map.find("SimData_Cur_Index").value() = 0; //reset index
        return;
    }

    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_SimData->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/SimData/"+config_name);
    qDebug()<<"DRL file name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open SimData xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse SimData xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Download SimData Message:\n");
    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    quint8 index;

    index =  config_load_map.find("SimData_Cur_Index").value();

    while (index > 0)
    {
        n = n.nextSibling();
        index--;
    }

    if(n.isNull() != true)
    {
        QDomElement e = n.toElement();
        QDomNodeList list = e.childNodes();

        for(int i = 0;i < list.count(); i++)
        {
            QDomNode node = list.at(i);
            if(node.isElement())
            {
                temp.clear();
                convertStringToHex(node.toElement().attribute("label"), temp);
                send_data.append(temp); //t
                send_data_len += temp.size();
                temp.clear();
                convertStringToHex(node.toElement().text(), temp);
                if(temp.size()>127) //fixme:需要完善一下L的解析，现在是写死的T最多两个字节
                {
                    if(temp.size() <= 256)
                    {
                        send_data.append(0x81);
                        send_data_len += 1;
                    }
                }
                send_data.append(temp.size());  //l
                send_data_len += 1;
                send_data.append(temp); //v
                send_data_len += temp.size();
                show_message(node.toElement().attribute("label") + ":" +node.toElement().text()+"\n");
            }
        }
    }
    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);
    qDebug()<<"send data size:"<<send_data.size();
    qDebug()<<"send data:"<<send_data;

    show_message("\n");
    show_message("\n");

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"write data act num:"<<ret;
    config_load_map.find("SimData_Cur_Index").value() += 1;
}

void XGD_HOST::deal_revokey_download()
{
    QByteArray send_data,temp;
    int send_data_len = 0;
    char high,low;

    send_data.clear();
    send_data.append(STX);
    send_data.append(REVOKEY_DOWNLOAD_SEND);

    if(config_load_map.find("Revokey_Cur_Index").value() == (config_load_map.find("Revokey_Counter").value())) //find no aid to download,finish
    {
        qDebug()<<"Revokey_Cur_Index: "<< config_load_map.find("Revokey_Cur_Index").value();
        qDebug()<<"Revokey_Counter: "<< config_load_map.find("Revokey_Counter").value();
        qDebug()<<"no Revokey to download!!!";
        QString endLine("0003030100");
        temp.clear();
        convertStringToHex(endLine, temp);
        send_data.append(temp);
        qDebug()<<"send data:"<<send_data;
        m_serial.write(send_data);
        config_load_map.find("Revokey_Cur_Index").value() = 0; //reset index
        return;
    }

    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_Revokey->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/Revocation_CAPK/"+config_name);
    qDebug()<<"DRL file name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open Revocation_CAPK xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse Revocation_CAPK xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Download Revocation_CAPK Message:\n");
    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    quint8 index;

    index =  config_load_map.find("Revokey_Cur_Index").value();

    while (index > 0)
    {
        n = n.nextSibling();
        index--;
    }

    if(n.isNull() != true)
    {
        QDomElement e = n.toElement();
        QDomNodeList list = e.childNodes();

        for(int i = 0;i < list.count(); i++)
        {
            QDomNode node = list.at(i);
            if(node.isElement())
            {
                temp.clear();
                convertStringToHex(node.toElement().attribute("label"), temp);
                send_data.append(temp); //t
                send_data_len += temp.size();
                temp.clear();
                convertStringToHex(node.toElement().text(), temp);
                if(temp.size()>127) //fixme:需要完善一下L的解析，现在是写死的T最多两个字节
                {
                    if(temp.size() <= 256)
                    {
                        send_data.append(0x81);
                        send_data_len += 1;
                    }
                }
                send_data.append(temp.size());  //l
                send_data_len += 1;
                send_data.append(temp); //v
                send_data_len += temp.size();
                show_message(node.toElement().attribute("label") + ":" +node.toElement().text()+"\n");
            }
        }
    }
    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);
    qDebug()<<"send data size:"<<send_data.size();
    qDebug()<<"send data:"<<send_data;

    show_message("\n");
    show_message("\n");

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"write data act num:"<<ret;
    config_load_map.find("Revokey_Cur_Index").value() += 1;
}

void XGD_HOST::deal_blacklist_download()
{
    QByteArray send_data,temp;
    int send_data_len = 0;
    char high,low;

    send_data.clear();
    send_data.append(STX);
    send_data.append(BLACKLIST_DOWNLOAD_SEND);

    if(config_load_map.find("ExecptionFile_Cur_Index").value() == (config_load_map.find("ExecptionFile_Counter").value())) //find no aid to download,finish
    {
        qDebug()<<"ExecptionFile_Cur_Index: "<< config_load_map.find("ExecptionFile_Cur_Index").value();
        qDebug()<<"ExecptionFile_Counter: "<< config_load_map.find("ExecptionFile_Counter").value();
        qDebug()<<"no ExecptionFile to download!!!";
        QString endLine("0003030100");
        temp.clear();
        convertStringToHex(endLine, temp);
        send_data.append(temp);
        qDebug()<<"send data:"<<send_data;
        m_serial.write(send_data);
        config_load_map.find("ExecptionFile_Cur_Index").value() = 0; //reset index
        return;
    }


    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_ExceptionFile->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/Exception_File/"+config_name);
    qDebug()<<"Exception_File name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open Exception_File xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse ExecptionFile xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Download ExecptionFile Message:\n");
    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    quint8 index;

    index =  config_load_map.find("ExecptionFile_Cur_Index").value();

    while (index > 0)
    {
        n = n.nextSibling();
        index--;
    }

    if(n.isNull() != true)
    {
        QDomElement e = n.toElement();
        QDomNodeList list = e.childNodes();

        for(int i = 0;i < list.count(); i++)
        {
            QDomNode node = list.at(i);
            if(node.isElement())
            {
                temp.clear();
                convertStringToHex(node.toElement().attribute("label"), temp);
                send_data.append(temp); //t
                send_data_len += temp.size();
                temp.clear();
                convertStringToHex(node.toElement().text(), temp);
                if(temp.size()>127) //fixme:需要完善一下L的解析，现在是写死的T最多两个字节
                {
                    if(temp.size() <= 256)
                    {
                        send_data.append(0x81);
                        send_data_len += 1;
                    }
                }
                send_data.append(temp.size());  //l
                send_data_len += 1;
                send_data.append(temp); //v
                send_data_len += temp.size();
                show_message(node.toElement().attribute("label") + ":" +node.toElement().text()+"\n");
            }
        }
    }
    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);
    qDebug()<<"send data size:"<<send_data.size();
    qDebug()<<"send data:"<<send_data;

    show_message("\n");
    show_message("\n");

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"write data act num:"<<ret;
    config_load_map.find("ExecptionFile_Cur_Index").value() += 1;
}

void XGD_HOST::deal_drl_download()
{
    QByteArray send_data,temp;
    int send_data_len = 0;
    char high,low;

    send_data.clear();
    send_data.append(STX);
    send_data.append(DRL_DOWNLOAD_SEND);

    if(config_load_map.find("DRL_Cur_Index").value() == (config_load_map.find("DRL_Counter").value())) //find no aid to download,finish
    {
        qDebug()<<"DRL_Cur_Index: "<< config_load_map.find("DRL_Cur_Index").value();
        qDebug()<<"CAPK_Counter: "<< config_load_map.find("DRL_Counter").value();
        qDebug()<<"no DRL to download!!!";
        QString endLine("0003030100");
        temp.clear();
        convertStringToHex(endLine, temp);
        send_data.append(temp);
        qDebug()<<"send data:"<<send_data;
        m_serial.write(send_data);
        config_load_map.find("DRL_Cur_Index").value() = 0; //reset index
        return;
    }

    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_DRL->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/DRL/"+config_name);
    qDebug()<<"DRL file name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open DRL xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse DRL xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Download DRL Message:\n");
    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    quint8 index;

    index =  config_load_map.find("DRL_Cur_Index").value();

    while (index > 0)
    {
        n = n.nextSibling();
        index--;
    }

    if(n.isNull() != true)
    {
        QDomElement e = n.toElement();
        QDomNodeList list = e.childNodes();

        for(int i = 0;i < list.count(); i++)
        {
            QDomNode node = list.at(i);
            if(node.isElement())
            {
                temp.clear();
                convertStringToHex(node.toElement().attribute("label"), temp);
                send_data.append(temp); //t
                send_data_len += temp.size();
                temp.clear();
                convertStringToHex(node.toElement().text(), temp);
                if(temp.size()>127) //fixme:需要完善一下L的解析，现在是写死的T最多两个字节
                {
                    if(temp.size() <= 256)
                    {
                        send_data.append(0x81);
                        send_data_len += 1;
                    }
                }
                send_data.append(temp.size());  //l
                send_data_len += 1;
                send_data.append(temp); //v
                send_data_len += temp.size();
                show_message(node.toElement().attribute("label") + ":" +node.toElement().text()+"\n");
            }
        }
    }
    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);
    qDebug()<<"send data size:"<<send_data.size();
    qDebug()<<"send data:"<<send_data;

    show_message("\n");
    show_message("\n");

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"write data act num:"<<ret;
    config_load_map.find("DRL_Cur_Index").value() += 1;
}

void XGD_HOST::deal_capk_download()
{
    QByteArray send_data,temp;
    int send_data_len = 0;
    char high,low;

    send_data.clear();
    send_data.append(STX);
    send_data.append(CAPK_DOWNLOAD_SEND);

    if(config_load_map.find("CAPK_Cur_Index").value() == (config_load_map.find("CAPK_Counter").value())) //find no aid to download,finish
    {
        qDebug()<<"CAPK_Cur_Index: "<< config_load_map.find("CAPK_Cur_Index").value();
        qDebug()<<"CAPK_Counter: "<< config_load_map.find("CAPK_Counter").value();
        qDebug()<<"no capk to download!!!";
        QString endLine("0003030100");
        temp.clear();
        convertStringToHex(endLine, temp);
        send_data.append(temp);
        qDebug()<<"send data:"<<send_data;
        m_serial.write(send_data);
        config_load_map.find("CAPK_Cur_Index").value() = 0; //reset index
        return;
    }

    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_CAPK->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/CAPK/"+config_name);
    qDebug()<<"CAPK file name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open CAPK xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse CAPK xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Download CAPK Message:\n");
    QDomNode rootNode = xml_doc.firstChild();

    //return root element
    QDomElement rootElement = xml_doc.documentElement();

    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    quint8 index;

    index =  config_load_map.find("CAPK_Cur_Index").value();

    while (index > 0)
    {
        n = n.nextSibling();
        index--;
    }

    if(n.isNull() != true)
    {
        QDomElement e = n.toElement();
        QDomNodeList list = e.childNodes();

        for(int i = 0;i < list.count(); i++)
        {
            QDomNode node = list.at(i);
            if(node.isElement())
            {
                temp.clear();
                convertStringToHex(node.toElement().attribute("label"), temp);
                send_data.append(temp); //t
                send_data_len += temp.size();
                temp.clear();
                convertStringToHex(node.toElement().text(), temp);
                if(temp.size()>127) //fixme:需要完善一下L的解析，现在是写死的T最多两个字节
                {
                    if(temp.size() <= 256)
                    {
                        send_data.append(0x81);
                        send_data_len += 1;
                    }
                }
                send_data.append(temp.size());  //l
                send_data_len += 1;
                send_data.append(temp); //v
                send_data_len += temp.size();
                show_message(node.toElement().attribute("label") + ":" +node.toElement().text()+"\n");
            }
        }
    }
    qDebug()<<"send data len:"<<send_data_len;
    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);
    qDebug()<<"send data size:"<<send_data.size();
    qDebug()<<"send data:"<<send_data;

    show_message("\n");
    show_message("\n");

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"write data act num:"<<ret;
    config_load_map.find("CAPK_Cur_Index").value() += 1;
}

void XGD_HOST::deal_aid_download()
{
    QByteArray send_data,temp;
    int send_data_len = 0;
    char high,low;

    send_data.clear();
    send_data.append(STX);
    send_data.append(AID_DOWNLOAD_SEND);

    if(config_load_map.find("AID_Cur_Index").value() == (config_load_map.find("AID_Counter").value())) //find no aid to download,finish
    {
        qDebug()<<"AID_Cur_Index: "<< config_load_map.find("AID_Cur_Index").value();
        qDebug()<<"AID_Counter: "<< config_load_map.find("AID_Counter").value();
        qDebug()<<"no aid to download!!!";
        QString endLine("0003030100");
        temp.clear();
        convertStringToHex(endLine, temp);
        send_data.append(temp);
        qDebug()<<"send data:"<<send_data;
        m_serial.write(send_data);
        config_load_map.find("AID_Cur_Index").value() = 0; //reset index
        return;
    }

    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_AID->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/AID/"+config_name);
    qDebug()<<"AID file name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open AID xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse AID xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Download AID Message:\n");
    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    quint8 index;

    index =  config_load_map.find("AID_Cur_Index").value();

    while (index > 0)
    {
        n = n.nextSibling();
        index--;
    }

    if(n.isNull() != true)
    {
        QDomElement e = n.toElement();
        QDomNodeList list = e.childNodes();

        for(int i = 0;i < list.count(); i++)
        {
            QDomNode node = list.at(i);
            if(node.isElement())
            {
                temp.clear();
                convertStringToHex(node.toElement().attribute("label"), temp);
                send_data.append(temp); //t
                send_data_len += temp.size();
                temp.clear();
                convertStringToHex(node.toElement().text(), temp);
                if(temp.size()>127) //fixme:需要完善一下L的解析，现在是写死的T最多两个字节
                {
                    if(temp.size() <= 256)
                    {
                        send_data.append(0x81);
                        send_data_len += 1;
                    }
                }
                send_data.append(temp.size());  //l
                send_data_len += 1;
                send_data.append(temp); //v
                send_data_len += temp.size();
                show_message(node.toElement().attribute("label") + ":" +node.toElement().text()+"\n");
            }
        }
    }
    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);
    qDebug()<<"send data size:"<<send_data.size();
    qDebug()<<"send data:"<<send_data;

    show_message("\n");
    show_message("\n");

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"write data act num:"<<ret;
    config_load_map.find("AID_Cur_Index").value() += 1;
}

void XGD_HOST::on_comboBox_Brand_currentTextChanged(const QString &arg1)
{
    cur_brand = arg1;
    QDir dir;
    QStringList file_list;

    //flush AID config list
    ui->comboBox_AID->clear();
    dir.setPath(cur_config_dir+"/"+cur_brand+"/AID");
    if(dir.exists())
    {
        file_list = dir.entryList();
        if(file_list.count() > 2)
        {
            file_list.removeFirst();
            file_list.removeFirst();
            for(int i = 0; i < file_list.count(); i++)
            {
                QString temp = file_list.at(i).section(".",0,0).trimmed();
                file_list.replace(i, temp);
            }
            ui->comboBox_AID->addItems(file_list);
        }
    }

    //flush CAPK config list
    ui->comboBox_CAPK->clear();
    dir.setPath(cur_config_dir+"/"+cur_brand+"/CAPK");
    if(dir.exists())
    {
        file_list = dir.entryList();
        if(file_list.count() > 2)
        {
            file_list.removeFirst();
            file_list.removeFirst();
            for(int i = 0; i < file_list.count(); i++)
            {
                QString temp = file_list.at(i).section(".",0,0).trimmed();
                file_list.replace(i, temp);
            }
            ui->comboBox_CAPK->addItems(file_list);
        }
    }

    //flush Exception File config list
    ui->comboBox_ExceptionFile->clear();
    dir.setPath(cur_config_dir+"/"+cur_brand+"/Exception_File");
    if(dir.exists())
    {
        file_list = dir.entryList();
        if(file_list.count() > 2)
        {
            file_list.removeFirst();
            file_list.removeFirst();
            for(int i = 0; i < file_list.count(); i++)
            {
                QString temp = file_list.at(i).section(".",0,0).trimmed();
                file_list.replace(i, temp);
            }
            ui->comboBox_ExceptionFile->addItems(file_list);
        }
    }

    //flush DRL config list
    ui->comboBox_DRL->clear();
    dir.setPath(cur_config_dir+"/"+cur_brand+"/DRL");
    if(dir.exists())
    {
        file_list = dir.entryList();
        if(file_list.count() > 2)
        {
            file_list.removeFirst();
            file_list.removeFirst();
            for(int i = 0; i < file_list.count(); i++)
            {
                QString temp = file_list.at(i).section(".",0,0).trimmed();
                file_list.replace(i, temp);
            }
            ui->comboBox_DRL->addItems(file_list);
        }
    }

    //flush SimData config list
    ui->comboBox_SimData->clear();
    dir.setPath(cur_config_dir+"/"+cur_brand+"/SimData");
    if(dir.exists())
    {
            file_list = dir.entryList();
            if(file_list.count() > 2)
            {
                file_list.removeFirst();
                file_list.removeFirst();
                for(int i = 0; i < file_list.count(); i++)
                {
                    QString temp = file_list.at(i).section(".",0,0).trimmed();
                    file_list.replace(i, temp);
                }
                ui->comboBox_SimData->addItems(file_list);
            }
    }

    //flush Revokey config list
    ui->comboBox_Revokey->clear();
    dir.setPath(cur_config_dir+"/"+cur_brand+"/Revocation_CAPK");
    if(dir.exists())
    {
        file_list = dir.entryList();
        if(file_list.count() > 2)
        {
            file_list.removeFirst();
            file_list.removeFirst();
            for(int i = 0; i < file_list.count(); i++)
            {
                QString temp = file_list.at(i).section(".",0,0).trimmed();
                file_list.replace(i, temp);
            }
            ui->comboBox_Revokey->addItems(file_list);
        }
    }

    //flush PreProcess config list
    ui->comboBox_PreProcess->clear();
    dir.setPath(cur_config_dir+"/"+cur_brand+"/PreProcess");
    if(dir.exists())
    {
        file_list = dir.entryList();
        if(file_list.count() > 2)
        {
            file_list.removeFirst();
            file_list.removeFirst();
            for(int i = 0; i < file_list.count(); i++)
            {
                QString temp = file_list.at(i).section(".",0,0).trimmed();
                file_list.replace(i, temp);
            }
            ui->comboBox_PreProcess->addItems(file_list);
        }
    }
}

void XGD_HOST::on_pushButton_DownloadAid_clicked()
{
    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_AID->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/AID/"+config_name);
    qDebug()<<"AID file name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open AID xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse AID xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Load AID:"+config_name+"\n");

    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    int i = 0;
    while(n.isNull() != true)
    {
        qDebug()<<"node name:"<<n.nodeName();
        i+=1;
        n = n.nextSibling();
    }
    qDebug()<<"this xml has aid:"<<i;
    config_load_map.find("AID_Counter").value() = i;
    config_load_map.find("AID_Cur_Index").value() = 0;

    QMapIterator<QString, quint8> it(config_load_map);
    while(it.hasNext())
    {
        it.next();
        qDebug()<<it.key()<<":"<<it.value();
    }
}

//void XGD_HOST::convertStringToHex(const QString &str, QByteArray &byteData)
//{
//    int hexdata, lowhexdata;
//    int hexdatalen = 0;
//    int len = str.length();
//    byteData.resize(len/2);
//    char lstr,hstr;

//    for(int i = 0; i < len; )
//    {
//        hstr = str[i].toLatin1();
//        if(hstr == ' ')
//        {
//            i++;
//            continue;
//        }
//        i++;
//        if(i >= len)
//        {
//            break;
//        }
//        lstr = str[i].toLatin1();
//        hexdata =convertCharToHex(hstr);
//        lowhexdata = convertCharToHex(lstr);
//        if((hexdata == 16) || (lowhexdata == 16))
//        {
//            break;
//        }
//        else
//        {
//            hexdata = hexdata * 16 + lowhexdata;
//        }
//        i++;
//        byteData[hexdatalen] = (char)hexdata;
//        hexdatalen++;
//    }
//    byteData.resize(hexdatalen);
//}

//char XGD_HOST::convertCharToHex(char ch)
//{
//    if((ch >= '0' && (ch <= '9')))
//        return ch - 0x30;
//    else if((ch >= 'A') && (ch <= 'F'))
//        return ch - 'A' + 10;
//    else if((ch >= 'a') && (ch <= 'f'))
//        return ch - 'a' + 10;
//    else
//        return (-1);
//}

void XGD_HOST::on_pushButton_DownloadCAPK_clicked()
{
    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_CAPK->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/CAPK/"+config_name);
    qDebug()<<"CAPK file name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open CAPK xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse CAPK xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Load CAPK:"+config_name + "\n");

    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    int i = 0;
    while(n.isNull() != true)
    {
        qDebug()<<"node name:"<<n.nodeName();
        i+=1;
        n = n.nextSibling();
    }
    qDebug()<<"this xml has capk:"<<i;
    config_load_map.find("CAPK_Counter").value() = i;
    config_load_map.find("CAPK_Cur_Index").value() = 0;

    QMapIterator<QString, quint8> it(config_load_map);
    while(it.hasNext())
    {
        it.next();
        qDebug()<<it.key()<<":"<<it.value();
    }
}

void XGD_HOST::on_verticalScrollBar_Message_sliderMoved(int position)
{
    qDebug()<<"position: "<<position;

//    ui->plainTextEdit_Message->verticalScrollBar()->rol
//    ui->plainTextEdit_Message->move(0,0);
}

void XGD_HOST::on_pushButton_DownloadExcet_clicked()
{
    QDomDocument xml_doc;
    QFile file;
    QString config_name = ui->comboBox_ExceptionFile->currentText()+".xml";

    file.setFileName(cur_config_dir + "/"+cur_brand+"/Exception_File/"+config_name);
    qDebug()<<"Exception_File name:"<<file.fileName();

    if(file.open(QIODevice::ReadOnly) != true)
    {
        qDebug()<<"Open Exception_File xml fail!!!"<<endl;
        return;
    }

    if(xml_doc.setContent(&file) != true)
    {
        qDebug()<<"Parse Exception_File xml fail,Check file format!!"<<endl;
        return;
    }
    file.close();

    show_message("Load Exception_File:"+config_name + "\n");

    QDomNode rootNode = xml_doc.firstChild();
    qDebug()<<qPrintable(rootNode.nodeName()+"\n")<<qPrintable(rootNode.nodeValue());
    //return root element
    QDomElement rootElement = xml_doc.documentElement();
    //return first child node of root node
    QDomNode n = rootElement.firstChild();
    int i = 0;
    while(n.isNull() != true)
    {
        qDebug()<<"node name:"<<n.nodeName();
        i+=1;
        n = n.nextSibling();
    }
    qDebug()<<"this xml has exception file:"<<i;
    config_load_map.find("ExecptionFile_Counter").value() = i;
    config_load_map.find("ExecptionFile_Cur_Index").value() = 0;

    QMapIterator<QString, quint8> it(config_load_map);
    while(it.hasNext())
    {
        it.next();
        qDebug()<<it.key()<<":"<<it.value();
    }
}

void XGD_HOST::deal_trans_request()
{
    QByteArray send_data;
    int send_data_len = 0, temp_len = 0;
    QString temp_str;
    QByteArray temp_byte;
    char low,high;

    show_message("Transaction Request Message:\n");

    send_data.append(STX);
    send_data.append(TRANS_REQ_SEND);
    //load 9F02
    if(AmtPresentFlag)
    {
        temp_str.clear();
        temp_str.append("9F02");
        temp_byte.clear();
        convertStringToHex(temp_str, temp_byte);
        send_data.append(temp_byte);
        send_data_len += temp_byte.size();
        qDebug()<<"LINE:  "<<__LINE__<<"send data len: "<<send_data_len<<endl;

        temp_str.clear();
        temp_str = ui->lineEdit_Amt->text();
        qDebug()<<"9F02 Empty:"<<temp_str.isEmpty();
        if(temp_str.isEmpty() != true)
        {
            send_data.append(0x06);
            send_data_len += 1;
            qDebug()<<"LINE:  "<<__LINE__<<"send data len: "<<send_data_len<<endl;
            qDebug()<<"get amt from widget:"<<temp_str;

            temp_str.remove('.');
            if(temp_str.size() < 12) //补高位的0
            {
                temp_len = temp_str.size();
                for(int i = 0; i < 12-temp_len; i++)
                {
                    temp_str.insert(0, '0');
                }
            }
            qDebug()<<"cur amount: "<<temp_str;
            show_message("9F02: "+temp_str+"\n");
            temp_byte.clear();
            convertStringToHex(temp_str, temp_byte);
            TraceHexFromByteArray("9F02 in hex", temp_byte);

            send_data.append(temp_byte);
            TraceHexFromByteArray("after append 9F02", send_data);
            send_data_len += temp_byte.size();
            qDebug()<<"LINE:  "<<__LINE__<<"send data len: "<<send_data_len<<endl;
        }
        else
        {
            TraceHexFromByteArray("cur send data:", send_data);

            temp_str.clear();
            temp_str.append("00");
            temp_byte.clear();
            show_message("9F02: 0\n");
            convertStringToHex(temp_str,temp_byte);

            TraceHexFromByteArray("temp_byte:", temp_byte);
            send_data.append(temp_byte);
            send_data_len += temp_byte.size();
            qDebug()<<"LINE:  "<<__LINE__<<"send data len: "<<send_data_len<<endl;
        }
    }

    //load 9F03
    if(AmtOtherPresentFlag)
    {
        temp_str.clear();
        temp_str.append("9F03");
        temp_byte.clear();
        convertStringToHex(temp_str, temp_byte);
        send_data.append(temp_byte);
        send_data_len += temp_byte.size();
        qDebug()<<"LINE:  "<<__LINE__<<"send data len: "<<send_data_len<<endl;

        temp_str.clear();
        temp_str = ui->lineEdit_AmtOther->text();
        qDebug()<<"9F03 Empty:"<<temp_str.isEmpty();
        if(temp_str.isEmpty() != true)
        {
            send_data.append(0x06);
            send_data_len += 1;
            qDebug()<<"LINE:  "<<__LINE__<<"send data len: "<<send_data_len<<endl;

            qDebug()<<"get amt other from widget:"<<temp_str;

            temp_str.remove('.');
            if(temp_str.size() < 12) //补高位的0
            {
                temp_len = temp_str.size();
                for(int i = 0; i < 12-temp_len; i++)
                {
                    temp_str.insert(0, '0');
                }
            }
            qDebug()<<"cur amount other: "<<temp_str;
            show_message("9F03: "+temp_str+"\n");
            temp_byte.clear();
            convertStringToHex(temp_str, temp_byte);
            TraceHexFromByteArray("9F03 in hex", temp_byte);

            send_data.append(temp_byte);
            TraceHexFromByteArray("after append 9F03", send_data);

            send_data_len += temp_byte.size();
            qDebug()<<"LINE:  "<<__LINE__<<"send data len: "<<send_data_len<<endl;
        }
        else
        {
            temp_str.clear();
            temp_str.append("00");
            temp_byte.clear();
            show_message("9F03: 0\n");
            convertStringToHex(temp_str,temp_byte);
            send_data.append(temp_byte);
            send_data_len += temp_byte.size();
        }
    }

    //load 9C
    if(TransTypePresentFlag)
    {
        temp_str.clear();
        temp_str.append("9C");
        temp_byte.clear();
        convertStringToHex(temp_str, temp_byte);
        send_data.append(temp_byte);
        send_data_len += temp_byte.size();

        temp_str = ui->lineEdit_TransType->text();
        if(temp_str.isEmpty() != true)
        {
            send_data.append(0x01);
            send_data_len += 1;
            qDebug()<<"get trans type from widget:"<<temp_str;
            show_message("9C: "+temp_str+"\n");
            temp_byte.clear();
            convertStringToHex(temp_str, temp_byte);
            send_data.append(temp_byte);
            send_data_len += temp_byte.size();
        }
        else
        {
            temp_str.clear();
            temp_str.append("00");
            temp_byte.clear();
            show_message("9C: 0\n");
            convertStringToHex(temp_str,temp_byte);
            send_data.append(temp_byte);
            send_data_len += temp_byte.size();
        }
    }

    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);

    qDebug()<<"send data size:"<<send_data.size();
    TraceHexFromByteArray("send data", send_data);

    show_message("\n");
    show_message("\n");

    int ret = 0;
    QString str_data;
    QByteArray byte_data;
    str_data = convertHexToString(send_data);
//    ret = m_serial.write(send_data);
    byte_data = str_data.toLatin1();
    qDebug()<<"send asc data:"<<byte_data;
    ret = m_serial.write(byte_data);
}

void XGD_HOST::on_pushButton_StartTrans_clicked()
{
    deal_trans_request();
}

void XGD_HOST::deal_trans_result()
{
    QString trans_result = tlv_map.find("03").value();
    QString cur_brand = ui->comboBox_Brand->currentText();
    QString trans_outcome = tlv_map.find("DF23").value();
    QString trans_cvm = tlv_map.find("FF8109").value(); //set for discover
    QString script_result = tlv_map.find("DF31").value();
    QString oda_result = tlv_map.find("DFC10B").value();
    QString str_outcome = tlv_map.find("DF8129").value();
    QString data_record = tlv_map.find("FF8105").value();
    QString disp_message;
    QByteArray temp_byte;

    //show transaction result
    if(!trans_result.isEmpty() || !trans_result.isNull())
    {
        convertStringToHex(trans_result, temp_byte);
        show_trans_result(cur_brand, temp_byte.at(0));
    }

    //show DF23
    if(!trans_outcome.isEmpty() || !trans_outcome.isNull())
    {
        temp_byte.clear();
        convertStringToHex(trans_outcome,temp_byte);
        show_trans_outcome(cur_brand, temp_byte.at(0));
    }

    //show  cvm
    if(!trans_cvm.isEmpty() || !trans_cvm.isNull())
    {
        temp_byte.clear();
        convertStringToHex(trans_cvm, temp_byte);
        switch (temp_byte.at(0))
        {
            case 0x00:
                show_message("CVM:  No CVM\n");
                break;
            case 0x10:
                show_message("CVM:  Signature\n");
                break;
            case 0x20:
                show_message("CVM:  Online PIN\n");
                break;
            case 0x30:
                show_message("CVM:  CDCVM\n");
                break;
            case 0x40:
                show_message("CVM:  N/A\n");
                break;
            default:
                show_message("CVM:   Invalid data\n");
                break;
        }
    }
    //show scpite result
    if(!script_result.isEmpty() || !script_result.isNull())
    {
        show_message("Script Result:"+script_result+"\n");
    }

    //show oda result
    if(!oda_result.isEmpty() || !oda_result.isNull())
    {
        show_message("ODA Result:");
        if(oda_result == "00")
        {
            show_message("ODA not Performed\n");
        }
        else if(oda_result == "01")
        {
            show_message("fDDA Succeed\n");
        }
        else if(oda_result == "02")
        {
            show_message("fDDA Failed\n");
        }
        else if(oda_result == "03")
        {
            show_message("SDA Succeed\n");
        }
        else if(oda_result == "04")
        {
            show_message("SDA Failed\n");
        }
        else if(oda_result == "05")
        {
            show_message("DDA Succeed\n");
        }
        else if(oda_result == "06")
        {
            show_message("DDA Failed\n");
        }
        else if(oda_result == "07")
        {
            show_message("CDA Succeed\n");
        }
        else if(oda_result == "08")
        {
            show_message("CDA Failed\n");
        }
        else if(oda_result == "09")
        {
            show_message("Online fDDA Succeed and Display\n");
        }
        else if(oda_result == "0A")
        {
            show_message("Online fDDA Failed and Display\n");
        }
        else if(oda_result == "0B")
        {
            show_message("Online SDA Succeed and Display\n");
        }
        else if(oda_result == "0C")
        {
            show_message("Online SDA Failed and Display\n");
        }
        else if(oda_result == "0D")
        {
            show_message("Online ODA Failed and Display\n");
        }
        else
        {
            show_message("Invalid Data\n");
        }
    }

    //show transaction outcome for jcb
    show_trans_outcome(str_outcome);

    //show data record for jcb
    show_data_record(data_record);

    QMapIterator<QString, QString> it(tlv_map);
    while (it.hasNext())
    {
        it.next();
        if(it.key() == "03" || it.key() == "DF23" || it.key() == "FF8109" || it.key() == "DF31" || it.key() == "DFC10B" || it.key() == "DF8129" || it.key() == "FF8105")
        {
            continue;
        }
        else
        {
            disp_message.clear();
            disp_message.append(it.key()+": "+it.value());
            show_message(disp_message+"\n");
        }

    }
    show_message("\n");
    show_message("\n");

    //send response to term
    QByteArray send_data;
    QString temp_str;

    send_data.append(STX);
    send_data.append(TRANS_RESULT_SEND);
    temp_str.append("0003030100");
    temp_byte.clear();
    convertStringToHex(temp_str,temp_byte);
    send_data.append(temp_byte);

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"act write byte: "<<ret;
}

void XGD_HOST::deal_finance_request()
{
    QString disp_message;
    QString cur_brand = ui->comboBox_Brand->currentText();

    QMapIterator<QString, QString> it(tlv_map);
    while (it.hasNext())
    {
        it.next();
        if(it.key() == "99" || it.key() == "56" || it.key() == "9F6B")
        {
            continue;
        }
        else
        {
            disp_message.clear();
            disp_message.append(it.key()+": "+it.value());
            show_message(disp_message+"\n");
        }
        if(it.key() == "99")
        {
            disp_message.clear();
            disp_message.append("Online Encrypted PIN: "+it.value());
            show_message(disp_message+"\n");
        }
    }

    if(cur_brand == "ExpressPay")
    {
        if(tlv_map.find("56") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 1 Data: "+tlv_map.find("56").value());
            show_message(disp_message+"\n");
        }
        if(tlv_map.find("9F6B") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 2 Data: "+tlv_map.find("9F6B").value());
            show_message(disp_message+"\n");
        }
    }

    show_message("\n");
    show_message("\n");

    //send response to term
    QByteArray send_data,temp_byte;
    QString temp_str;
    int send_data_len = 0;
    char high,low;

    send_data.append(STX);
    send_data.append(FINANCE_REQ_SEND);

    send_data.append(0x8A);
    send_data_len += 1;
    temp_str = ui->lineEdit_HostResCode->text();
    qDebug()<<"8A from host:"<<temp_str;
    send_data.append(0x02);
    send_data_len += 1;
    send_data.append(temp_str.toLatin1());
    send_data_len += 2;

    temp_str = ui->lineEdit_HostAuthData->text();
    if(temp_str.isEmpty() == false)
    {
        send_data.append(0x91);
        send_data +=1 ;
        temp_byte.clear();
        convertStringToHex(temp_str, temp_byte);
        send_data.append(temp_byte.size());
        send_data += 1;
        send_data.append(temp_byte);
        send_data_len += temp_byte.size();
    }

    temp_str = ui->lineEdit_IssuerScript->text();
    if(temp_str.isEmpty() == false)
    {
        temp_byte.clear();
        convertStringToHex(temp_str, temp_byte);
        send_data.append(temp_byte);
        send_data_len += temp_byte.size();
    }

    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);

    TraceHexFromByteArray("send data:", send_data);

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"act write byte: "<<ret;

}

void XGD_HOST::on_checkBox_Amt_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        AmtPresentFlag = false;
    }
    else
    {
        AmtPresentFlag = true;
    }
}

void XGD_HOST::on_checkBox_AmtOther_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        AmtOtherPresentFlag = false;
    }
    else
    {
        AmtOtherPresentFlag = true;
    }
}

void XGD_HOST::on_checkBox_TransType_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        TransTypePresentFlag = false;
    }
    else
    {
        TransTypePresentFlag = true;
    }
}

//void XGD_HOST::on_action_Close_stateChanged(int arg1)
//{
//    qDebug()<<"close log arg1: "<<arg1;
//}

//void XGD_HOST::on_action_Open_stateChanged(int arg1)
//{
//    qDebug()<<"open log arg1: "<<arg1;
//}

void XGD_HOST::deal_finance_confirm()
{
    QString disp_message;
    QString cur_brand = ui->comboBox_Brand->currentText();
    QByteArray temp_byte;

    qDebug()<<"cur brand:"<<cur_brand;
    if(tlv_map.find("03") != tlv_map.end())
    {
        qDebug()<<"find 03!"<<endl;
        QString trans_result = tlv_map.find("03").value();
        temp_byte.clear();
        convertStringToHex(trans_result, temp_byte);
        show_trans_result(cur_brand, temp_byte.at(0));
    }

    QMapIterator<QString, QString> it(tlv_map);
    while (it.hasNext())
    {
        it.next();
        if(it.key() == "DF31" || it.key() == "03" || it.key() == "DF30" || it.key() == "56" || it.key() == "9F6B" || it.key() == "FF8186")
        {
            continue;
        }
        else
        {
            disp_message.clear();
            disp_message.append(it.key()+": "+it.value());
            show_message(disp_message+"\n");
        }
        if(it.key() == "DF31")
        {
            disp_message.clear();
            disp_message.append("Scripte Result: "+it.value());
            show_message(disp_message+"\n");
        }
    }

    if(cur_brand == "ExpressPay")
    {
        if(tlv_map.find("56") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 1 Data: "+tlv_map.find("56").value());
            show_message(disp_message+"\n");
        }
        if(tlv_map.find("9F6B") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 2 Data: "+tlv_map.find("9F6B").value());
            show_message(disp_message+"\n");
        }
    }
    else if(cur_brand == "Discover")
    {
        if(tlv_map.find("DF30") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Data Storage Write Results: "+tlv_map.find("DF30").value());
            show_message(disp_message+"\n");
        }
    }
    else if(cur_brand == "Paywave")
    {
        qDebug()<<"start parse FF8186!"<<endl;
        if(tlv_map.find("FF8186") != tlv_map.end())
        {
            qDebug()<<"find it!fuck!!!"<<endl;
            show_message("Result Indicator:\n");
            QString paywave_resIndicator = tlv_map.find("FF8186").value();
            temp_byte.clear();
            qDebug()<<"FF8186 value:"<<endl;
            convertStringToHex(paywave_resIndicator, temp_byte);
            qDebug()<<"change to hex:"<<temp_byte;
            qDebug()<<"temp_byte.size:"<<temp_byte.size();
            if(temp_byte.size() == 1)
            {
                if((temp_byte.at(0) & 0x01) == 0x01)
                {
                    show_message("  fDDA verification not performed\n");
                }
                else
                {
                    if((temp_byte.at(0) & 0x02) == 0x02)
                    {
                        show_message("  fDDA verification is performed and successful\n");
                    }
                    else
                    {
                        show_message("  fDDA verification is performed and failed\n");
                    }
                }
                if((temp_byte.at(0) & 0x04) == 0x04)
                {
                    show_message("  Application expired\n");
                }
                else
                {
                    show_message("  Application not expired\n");
                }
                if((temp_byte.at(0) & 0x08) == 0x08)
                {
                    show_message("  Application PAN on the Terminal Exception File\n");
                }
                else
                {
                    show_message("  Application PAN is not on the Terminal Exception File\n");
                }
                if((temp_byte.at(0) & 0x10) == 0x10)
                {
                    show_message("  Online Required by Reader Indicator\n");
                }
                else
                {
                    show_message("  Decline Required by Reader Indicator\n");
                }
            }
        }
    }

    show_message("\n");
    show_message("\n");

    QByteArray send_data;
    QString temp_str;

    send_data.append(STX);
    send_data.append(FINANCE_CONFIRM_SEND);

    temp_str.append("0003030100");
    temp_byte.clear();
    convertStringToHex(temp_str,temp_byte);
    send_data.append(temp_byte);

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"act write serial:"<<ret;
}

void XGD_HOST::show_trans_result(QString cardBrand, quint8 trans_result)
{
    qDebug()<<"cur card brand:"<<cardBrand;
    qDebug()<<"trans res:"<<trans_result;

    if(cardBrand == "Discover")
    {
        switch (trans_result)
        {
            case 0x61:
                show_message("TransResult:  Offline Approved\n");
                break;
            case 0x62:
                show_message("TransResult:  Offline Declined\n");
                break;
            case 0x63:
                show_message("TransResult:   Online Approved\n");
                break;
            case 0x64:
                show_message("TransResult:   Online Declined\n");
                break;
            case 0x65:
                show_message("TransResult:   Approved Please Sign\n");
                break;
            case 0x66:
                show_message("TransResult:   Please use another Card\n");
                break;
            case 0x67:
                show_message("TransResult:   Please enter PIN\n");
                break;
            case 0x68:
                show_message("TransResult:   Please present card again\n");
                break;
            case 0x69:
                show_message("TransResult:   Insert, Swipe the Card\n");
                break;
            case 0x6A:
                show_message("TransResult:   Insert, Swipe the Card\n");
                break;
            default:
                show_message("TransResult:   Invalid data\n");
                break;
        }
    }
    else if(cardBrand == "EMV_PBOC")
    {
        switch (trans_result)
        {
            case 0x01:
                show_message("交易结果:  交易批准\n");
                break;
            case 0x02:
                show_message("交易结果:  交易拒绝\n");
                break;
            case 0x03:
                show_message("交易结果:   交易终止\n");
                break;
            case 0x04:
                show_message("交易结果:   交易终止，服务不支持\n");
                break;
            case 0x05:
                show_message("交易结果:   交易强制批准\n");
                break;
            default:
                show_message("TransResult:   Invalid data\n");
                break;
        }
    }
    else if(cardBrand == "qPBOC")
    {
        switch (trans_result)
        {
            case 0x11:
                show_message("交易结果:  交易脱机批准\n");
                break;
            case 0x12:
                show_message("交易结果:  交易脱机拒绝\n");
                break;
            case 0x13:
                show_message("交易结果:   交易终止\n");
                break;
            case 0x14:
                show_message("交易结果:   交易联机批准\n");
                break;
            case 0x15:
                show_message("交易结果:   交易联机拒绝\n");
                break;
            case 0x16:
                show_message("交易结果:   交易联机不成功，脱机拒绝\n");
                break;
            case 0x17:
                show_message("交易结果:   交易拒绝，并显示黑名单卡\n");
                break;
            case 0x18:
                show_message("交易结果:   交易联机，并显示卡片过有效期\n");
                break;
            case 0x19:
                show_message("交易结果:   交易拒绝，并显示卡片过有效期\n");
                break;
            default:
                show_message("TransResult:   Invalid data\n");
                break;
        }
    }
    else if(cardBrand == "ExpressPay")
    {
        switch (trans_result)
        {
            case 0x41:
                show_message("TransResult:  Transaction approved\n");
                break;
            case 0x42:
                show_message("TransResult:  Transaction approved with Cardholder signature\n");
                break;
            case 0x43:
                show_message("TransResult:   Transaction declined\n");
                break;
            case 0x44:
                show_message("TransResult:   Try Another Interface\n");
                break;
            case 0x45:
                show_message("TransResult:   Premature termination or Request another payment\n");
                break;
            default:
                show_message("TransResult:   Invalid data\n");
                break;
        }
    }
}

void XGD_HOST::show_trans_outcome(QString outcome)
{
    QString str_temp;
    show_message("Transaction Outcome:\n");

    str_temp = outcome.mid(1, 2);
    if(str_temp.isEmpty() || str_temp.size() < 2)
    {
        qDebug()<<"Show Outcome Status fail!length invalid!"<<endl;
        return;
    }
    show_message("    Outcome Status:");
    if(str_temp == "10")
    {
        show_message("Approved\n");
    }
    else if(str_temp == "20")
    {
        show_message("Declined\n");
    }
    else if(str_temp == "30")
    {
        show_message("Online Request\n");
    }
    else if(str_temp == "40")
    {
        show_message("End Application\n");
    }
    else if(str_temp == "50")
    {
        show_message("Select Next\n");
    }
    else if(str_temp == "60")
    {
        show_message("Try Another Interface\n");
    }
    else if(str_temp == "A0")
    {
        show_message("End Application (with restart – communication error)\n");
    }
    else if(str_temp == "B0")
    {
        show_message("End Application (with restart - On-Device CVM)\n");
    }
    else if(str_temp == "C0")
    {
        show_message("Online Request (Two Presentments)\n");
    }
    else if(str_temp == "D0")
    {
        show_message("Online Request (Present and Hold)\n");
    }
    else
    {
        show_message("Invalid Data\n");
    }

    str_temp = outcome.mid(3, 2);
    if(str_temp.isEmpty() || str_temp.size() < 2)
    {
        qDebug()<<"Show Start fail!length invalid!"<<endl;
        return;
    }
    show_message("    Start:");
    if(str_temp == "00")
    {
        show_message("A\n");
    }
    else if(str_temp == "10")
    {
        show_message("B\n");
    }
    else if(str_temp == "20")
    {
        show_message("C\n");
    }
    else if(str_temp == "30")
    {
        show_message("D\n");
    }
    else if(str_temp == "F0")
    {
        show_message("N/A\n");
    }
    else
    {
        show_message("Invalid Data\n");
    }

    str_temp = outcome.mid(5, 2);
    if(str_temp.isEmpty() || str_temp.size() < 2)
    {
        qDebug()<<"Show Online Response Data fail!length invalid!"<<endl;
        return;
    }
    show_message("    Online Response Data:");
    if(str_temp == "10")
    {
        show_message("EMV Data\n");
    }
    else if(str_temp == "20")
    {
        show_message("Any\n");
    }
    else if(str_temp == "F0")
    {
        show_message("N/A\n");
    }
    else
    {
        show_message("Invalid Data\n");
    }

    str_temp = outcome.mid(7, 2);
    if(str_temp.isEmpty() || str_temp.size() < 2)
    {
        qDebug()<<"Show CVM fail!length invalid!"<<endl;
        return;
    }
    show_message("    CVM:");
    if(str_temp == "00")
    {
        show_message("No CVM\n");
    }
    else if(str_temp == "10")
    {
        show_message("Obtain Signature\n");
    }
    else if(str_temp == "20")
    {
        show_message("Online PIN\n");
    }
    else if(str_temp == "30")
    {
        show_message("Confirmation Code Verified\n");
    }
    else if(str_temp == "F0")
    {
        show_message("N/A\n");
    }
    else
    {
        show_message("Invalid Data\n");
    }

    str_temp = outcome.mid(9, 2);
    if(str_temp.isEmpty() || str_temp.size() < 2)
    {
        qDebug()<<"Show Flag fail!length invalid!"<<endl;
        return;
    }
    show_message("    Flag:\n");

    QByteArray byte_temp;
    convertStringToHex(str_temp,byte_temp);

    if((byte_temp.at(0) & 0x80) == 0x80)
    {
        show_message("        UI Request on Outcome Present:yes\n");
    }
    else
    {
        show_message("        UI Request on Outcome Present:no\n");
    }
    if((byte_temp.at(0) & 0x40) == 0x40)
    {
        show_message("        UI Request on Restart Present:yes\n");
    }
    else
    {
        show_message("        UI Request on Restart Present:no\n");
    }
    if((byte_temp.at(0) & 0x20) == 0x20)
    {
        show_message("        Data Record Present:yes\n");
    }
    else
    {
        show_message("        Data Record Present:no\n");
    }
    if((byte_temp.at(0) & 0x10) == 0x10)
    {
        show_message("        Discretionary Data Present:yes\n");
    }
    else
    {
        show_message("        Discretionary Data Present:no\n");
    }
    if((byte_temp.at(0) & 0x08) == 0x08)
    {
        show_message("        Receipt:yes\n");
    }
    else
    {
        show_message("        Receipt:no\n");
    }

    str_temp = outcome.mid(11, 2);
    if(str_temp.isEmpty() || str_temp.size() < 2)
    {
        qDebug()<<"Show AIP fail!length invalid!"<<endl;
        return;
    }
    show_message("    AIP:\n");
    if(str_temp == "10")
    {
        show_message("Contant Chip\n");
    }
    else if(str_temp == "F0")
    {
        show_message("N/A\n");
    }
    else
    {
        show_message("Invalid Data\n");
    }

    str_temp = outcome.mid(13, 2);
    if(str_temp.isEmpty() || str_temp.size() < 2)
    {
        qDebug()<<"Show Field Off Request fail!length invalid!"<<endl;
        return;
    }
    show_message("    Field Off Request:\n");
    if(str_temp == "FF")
    {
        show_message("N/A\n");
    }
    else
    {
        show_message(str_temp+"\n");
    }

    str_temp = outcome.mid(15, 4);
    if(str_temp.isEmpty() || str_temp.size() < 4)
    {
        qDebug()<<"Show Field Off Request fail!length invalid!"<<endl;
        return;
    }
    show_message("    Removal Timeout:"+str_temp+"\n");
}

void XGD_HOST::show_trans_outcome(QString cardBrand, quint8 trans_outcome)
{
    qDebug()<<"cur card brand:"<<cardBrand;
    qDebug()<<"trans res:"<<trans_outcome;

    if(cardBrand == "Discover")
    {
        switch (trans_outcome)
        {
            case 0x01:
                show_message("TransOutcome:  Card not accepted\n");
                break;
            case 0x02:
                show_message("TransOutcome:  Please present only one card\n");
                break;
            case 0x03:
                show_message("TransOutcome:  Offline Approved\n");
                break;
            case 0x04:
                show_message("TransOutcome:  Offline Declined\n");
                break;
            case 0x05:
                show_message("TransOutcome:  Online Approved\n");
                break;
            case 0x06:
                show_message("TransOutcome:  Online Declined\n");
                break;
            case 0x1A:
                show_message("TransOutcome:  Approved Please Sign\n");
                break;
            case 0x1B:
                show_message("TransOutcome:  Please enter PIN\n");
                break;
            case 0x1C:
                show_message("TransOutcome:  Insert, Swipe the Card\n");
                break;
            case 0x1D:
                show_message("TransOutcome:   Please use another Card\n");
                break;
            case 0x1E:
                show_message("TransOutcome:   Please present card again\n");
                break;
            case 0x1F:
                show_message("TransOutcome:   Please present the card\n");
                break;
            case 0x20:
                show_message("TransOutcome:   Please authenticate yourself to your device and try again\n");
                break;
            case 0x21:
                show_message("TransOutcome:   Please look at your handset to obtain further instructions\n");
                break;
            case 0x22:
                show_message("TransOutcome:   Terminated\n");
                break;
            default:
                show_message("TransOutcome:   Invalid data\n");
                break;
        }
    }
    else if(cardBrand == "ExpressPay")
    {
        switch (trans_outcome)
        {
            case 0x03:
                show_message("TransOutcome:  Approved\n");
                break;
            case 0x1A:
                show_message("TransOutcome:  Approved Please Sign\n");
                break;
            case 0x07:
                show_message("TransOutcome:  Not Authorized\n");
                break;
            case 0x1D:
                show_message("TransOutcome:  Please Insert Card\n");
                break;
            case 0x0F:
                show_message("TransOutcome:  Processing Error\n");
                break;
            case 0x1C:
                show_message("TransOutcome:  Insert, Swipe or Try Another Card\n");
                break;
            default:
                show_message("TransOutcome:   Invalid data\n");
                break;
        }
    }
}

void XGD_HOST::deal_authorize_request()
{
    QString disp_message;
    QString cur_brand = ui->comboBox_Brand->currentText();

    QMapIterator<QString, QString> it(tlv_map);
    while (it.hasNext())
    {
        it.next();
        if(it.key() == "99" || it.key() == "56" || it.key() == "9F6B")
        {
            continue;
        }
        else
        {
            disp_message.clear();
            disp_message.append(it.key()+": "+it.value());
            show_message(disp_message+"\n");
        }
        if(it.key() == "99")
        {
            disp_message.clear();
            disp_message.append("Online Encrypted PIN: "+it.value());
            show_message(disp_message+"\n");
        }
    }

    if(cur_brand == "ExpressPay")
    {
        if(tlv_map.find("56") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 1 Data: "+tlv_map.find("56").value());
            show_message(disp_message+"\n");
        }
        if(tlv_map.find("9F6B") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 2 Data: "+tlv_map.find("9F6B").value());
            show_message(disp_message+"\n");
        }
    }

    show_message("\n");
    show_message("\n");

    //send response to term
    QByteArray send_data,temp_byte;
    QString temp_str;
    int send_data_len = 0;
    char high,low;

    send_data.append(STX);
    send_data.append(AUTHORIZE_REQ_SEND);

    send_data.append(0x8A);
    send_data_len += 1;
    temp_str = ui->lineEdit_HostResCode->text();
    qDebug()<<"8A from host:"<<temp_str;
    send_data.append(0x02);
    send_data_len += 1;
    send_data.append(temp_str.toLatin1());
    send_data_len += 2;

    temp_str = ui->lineEdit_HostAuthData->text();
    if(temp_str.isEmpty() == false)
    {
        send_data.append(0x91);
        send_data +=1 ;
        temp_byte.clear();
        convertStringToHex(temp_str, temp_byte);
        send_data.append(temp_byte.size());
        send_data += 1;
        send_data.append(temp_byte);
        send_data_len += temp_byte.size();
    }

    temp_str = ui->lineEdit_IssuerScript->text();
    if(temp_str.isEmpty() == false)
    {
        temp_byte.clear();
        convertStringToHex(temp_str, temp_byte);
        send_data.append(temp_byte);
        send_data_len += temp_byte.size();
    }

    high = (send_data_len>>8) & 0xFF;
    low = (send_data_len) & 0xFF;
    send_data.insert(2, high);
    send_data.insert(3,low);

    TraceHexFromByteArray("send data:", send_data);

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"act write byte: "<<ret;
}

void XGD_HOST::deal_batch_upload()
{
    QString disp_message;
    QString cur_brand = ui->comboBox_Brand->currentText();
    QString trans_result = tlv_map.find("03").value();
    QByteArray temp_byte;

    convertStringToHex(trans_result, temp_byte);
    show_trans_result(cur_brand, temp_byte.at(0));

    QMapIterator<QString, QString> it(tlv_map);
    while (it.hasNext())
    {
        it.next();
        if(it.key() == "DF31" || it.key() == "03" || it.key() == "DF30" || it.key() == "56" || it.key() == "9F6B")
        {
            continue;
        }
        else
        {
            disp_message.clear();
            disp_message.append(it.key()+": "+it.value());
            show_message(disp_message+"\n");
        }
        if(it.key() == "DF31")
        {
            disp_message.clear();
            disp_message.append("Scripte Result: "+it.value());
            show_message(disp_message+"\n");
        }
    }

    if(cur_brand == "ExpressPay")
    {
        if(tlv_map.find("56") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 1 Data: "+tlv_map.find("56").value());
            show_message(disp_message+"\n");
        }
        if(tlv_map.find("9F6B") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Track 2 Data: "+tlv_map.find("9F6B").value());
            show_message(disp_message+"\n");
        }
    }
    else if(cur_brand == "Discover")
    {
        if(tlv_map.find("DF30") != tlv_map.end())
        {
            disp_message.clear();
            disp_message.append("Data Storage Write Results: "+tlv_map.find("DF30").value());
            show_message(disp_message+"\n");
        }    }

    show_message("\n");
    show_message("\n");

    QByteArray send_data;
    QString temp_str;

    send_data.append(STX);
    send_data.append(BATCH_UPLOAD_SEND);

    temp_str.append("0003030100");
    temp_byte.clear();
    convertStringToHex(temp_str,temp_byte);
    send_data.append(temp_byte);

    int ret;
    ret = m_serial.write(send_data);
    qDebug()<<"act write serial:"<<ret;
}

void XGD_HOST::deal_term_outcome()
{
    QString UIReqOnOutcome = tlv_map.find("DF8116").value();
    QString UIReqOnRestart = tlv_map.find("DF8117").value();
    QByteArray temp_byte;

    if(UIReqOnOutcome.isEmpty() == false)
    {
        show_message("UI Request on Outcome:");
        show_ui(UIReqOnOutcome);
    }

    if(UIReqOnRestart.isEmpty() == false)
    {
        show_message("UI Request on Restart:");
        show_ui(UIReqOnRestart);
    }
}

void XGD_HOST::deal_advice(QByteArray term_data)
{
    int data_len = (quint8)(term_data.data()[2])*256 + (quint8)(term_data.data()[3]);
    QString disp_mess(term_data.mid(4, data_len));

    show_message(disp_mess);
}

void XGD_HOST::open_log()
{
    qInstallMessageHandler(outputMessage);
    ui->action_Open->setChecked(true);
    ui->action_Close->setChecked(false);
}

void XGD_HOST::close_log()
{
    qInstallMessageHandler(nullptr);
    ui->action_Close->setChecked(true);
    ui->action_Open->setChecked(false);
}

void XGD_HOST::show_ui(QString ui_str)
{
    QString temp_str;

    temp_str = ui_str.mid(1, 2);
    if(temp_str.isEmpty() || temp_str.size() < 2)
    {
        qDebug()<<"parse UI Message Identifier fail!length invalid!"<<endl;
        return;
    }
    show_message("Message Identifier:");
    if(temp_str == "03")
    {
        show_message("Approved\n");
    }
    else if(temp_str == "07")
    {
        show_message("Not Authorised\n");
    }
    else if(temp_str == "09")
    {
        show_message("Please enter your PIN\n");
    }
    else if(temp_str == "15")
    {
        show_message("Present Card\n");
    }
    else if(temp_str == "16")
    {
        show_message("Processing\n");
    }
    else if(temp_str == "17")
    {
        show_message("Card Read OK\n");
    }
    else if(temp_str == "19")
    {
        show_message("Please Present One Card Only\n");
    }
    else if(temp_str == "1A")
    {
        show_message("Approved – Please Sign\n");
    }
    else if(temp_str == "1B")
    {
        show_message("Authorising, Please Wait\n");
    }
    else if(temp_str == "1C")
    {
        show_message("Insert, Swipe or Try another card\n");
    }
    else if(temp_str == "1D")
    {
        show_message("Please insert card\n");
    }
    else if(temp_str == "20")
    {
        show_message("See Phone for Instructions\n");
    }
    else if(temp_str == "21")
    {
        show_message("Present Card Again\n");
    }
    else
    {
        show_message("Invalid Data\n");
    }

    temp_str = ui_str.mid(3, 2);
    if(temp_str.isEmpty() || temp_str.size() < 2)
    {
        qDebug()<<"parse UI Status fail!length invalid!"<<endl;
        return;
    }
    show_message("Status:");
    if(temp_str == "00")
    {
        show_message("NOT READY\n");
    }
    else if(temp_str == "01")
    {
        show_message("IDLE\n");
    }
    else if(temp_str == "02")
    {
        show_message("READY TO READ\n");
    }
    else if(temp_str == "03")
    {
        show_message("PROCESSING\n");
    }
    else if(temp_str == "04")
    {
        show_message("CARD READ SUCCESSFULLY\n");
    }
    else if(temp_str == "05")
    {
        show_message("PROCESSING ERROR\n");
    }
    else if(temp_str == "FF")
    {
        show_message("N/A\n");
    }
    else
    {
        show_message("Invalid Data\n");
    }

    temp_str = ui_str.mid(5, 6);
    if(temp_str.isEmpty() || temp_str.size() < 6)
    {
        qDebug()<<"parse UI Hold Time fail!length invalid!"<<endl;
        return;
    }
    show_message("Hold Time:"+temp_str+"\n");

    temp_str = ui_str.mid(10, 16);
    if(temp_str.isEmpty() == false && temp_str.size() == 16)
    {
        show_message("Language Preference:"+temp_str+"\n");
    }

    temp_str = ui_str.mid(26, 2);
    if(temp_str.isEmpty() || temp_str.size() < 2)
    {
        qDebug()<<"parse UI Value Qualifier fail!length invalid!"<<endl;
        return;
    }
    show_message("Value Qualifier:");
    if(temp_str == "20")
    {
        show_message("Balance\n");
    }

    temp_str = ui_str.mid(28, 12);
    if(temp_str.isEmpty() == false && temp_str.size() == 12)
    {
        show_message("Value:"+temp_str+"\n");
    }

    temp_str = ui_str.mid(40, 4);
    if(temp_str.isEmpty() == false && temp_str.size() == 4)
    {
        show_message("Currency Code:"+temp_str+"\n");
    }
}

void XGD_HOST::init_tlv_map()
{
    tlv_map.clear();

    tlv_map.insert("TVR", "95");
    tlv_map.insert("Script Result", "DF31");
    tlv_map.insert("ODA Result", "DFC10B");
    tlv_map.insert("TSI", "9B");
}

void XGD_HOST::show_data_record(QString data_record)
{
    QMap<QString, QString>p_map;
    show_message("Data Record:\n");

    tlv2qmap(data_record, p_map);
    QMapIterator<QString,QString> it(p_map);
    while (it.hasNext())
    {
        it.next();
        if(it.key() == "DF43")
        {
            show_message("    Transaction Mode:");
            if(it.value() == "01")
            {
                show_message("EMV Mode\n");
            }
            else if(it.value() == "02")
            {
                show_message("Magstripe Mode\n");
            }
            else if(it.value() == "04")
            {
                show_message("Legacy Mode\n");
            }
            else
            {
                show_message("Invalid Data\n");
            }
        }
        else
        {
            show_message("    "+it.key()+":"+it.value()+"\n");
        }
    }
}
