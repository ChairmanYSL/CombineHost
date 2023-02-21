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
    //TODO: here to add init config list and brand list,take cmd command to get dir name and show
    QStringList CardBrand;
    cur_config_dir = QCoreApplication::applicationDirPath() + "/Config";

    QDir dir;
    dir.setPath(cur_config_dir);
    if(dir.exists())
    {
        CardBrand = dir.entryList();
        if(CardBrand.count() > 2)
        {
            CardBrand.removeFirst();    //remove '.' and '..'
            CardBrand.removeFirst();

            ui->comboBox_Brand->addItems(CardBrand);
            cur_brand = CardBrand.at(0);
        }
    }

    //init AID config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/AID");
    QStringList file_list;

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
        ui->comboBox_AID->clear();
        ui->comboBox_AID->addItems(file_list);
    }

    //init CAPK config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/CAPK");

    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_CAPK->clear();
    ui->comboBox_CAPK->addItems(file_list);


    //init Exception File config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/Exception_File");

    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_ExceptionFile->clear();
    ui->comboBox_ExceptionFile->addItems(file_list);

    //init PreProcess config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/PreProcess");

    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_PreProcess->clear();
    ui->comboBox_PreProcess->addItems(file_list);

    //init Revocation_CAPK config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/Revocation_CAPK");
    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_Revokey->clear();
    ui->comboBox_Revokey->addItems(file_list);

    //init SimData config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/SimData");

    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_SimData->clear();
    ui->comboBox_SimData->addItems(file_list);

    //init DRL config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/DRL");

    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_DRL->clear();
    ui->comboBox_DRL->addItems(file_list);

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
}

XGD_HOST::~XGD_HOST()
{
    m_serial.close();
    delete ui;
}

void XGD_HOST::on_pushButton_ScanSerial_clicked()
{
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
}

void XGD_HOST::on_pushButton_ClrMessage_clicked()
{
    ui->plainTextEdit_Message->clear();
}

int XGD_HOST::tlv2qmap(QByteArray tlv_data)
{
    int i = 0,t_len,l_len,v_len,j=0;
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
            break;
        case FINANCE_CONFIRM_RECV:
            show_message("Finance Confirm Message:\n");
            break;
        case BATCH_UPLOAD_RECV:
            show_message("Batch Upload Message:\n");
            break;
        case ADVICE_RECV:
            show_message("Advice Message:\n");
            break;
        case REDO_RECV:
            show_message("Redo Message:\n");
            break;
        case FIALFLOW_UPLOAD_RECV:
            show_message("Upload Fail-Flow Message:\n");
            break;
        case TRANS_RESULT_RECV:
            deal_trans_result();
            show_message("Transaction Result Message:\n");
            break;
        case ELECCHIP_ELECSIGN_RECV:
            show_message("Elctric Chip && Elctric Sign Message:\n");
            break;
        case TERM_OUTCOME_RECV:
            show_message("Terminal OutCome Message:\n");
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
    dir.setPath(cur_config_dir);

    //flush AID config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/AID");
    QStringList file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_AID->clear();
    ui->comboBox_AID->addItems(file_list);

    //flush CAPK config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/CAPK");
    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_CAPK->clear();
    ui->comboBox_CAPK->addItems(file_list);

    //flush Exception File config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/Exception_File");
    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_ExceptionFile->clear();
    ui->comboBox_ExceptionFile->addItems(file_list);

    //flush DRL config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/DRL");
    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_DRL->clear();
    ui->comboBox_DRL->addItems(file_list);

    //flush SimData config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/SimData");
    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_SimData->clear();
    ui->comboBox_SimData->addItems(file_list);

    //flush Revokey config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/Revocation_CAPK");
    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_Revokey->clear();
    ui->comboBox_Revokey->addItems(file_list);

    //flush PreProcess config list
    dir.setPath(cur_config_dir+"/"+cur_brand+"/PreProcess");
    file_list = dir.entryList();
    file_list.removeFirst();
    file_list.removeFirst();
    for(int i = 0; i < file_list.count(); i++)
    {
        QString temp = file_list.at(i).section(".",0,0).trimmed();
        file_list.replace(i, temp);
    }
    ui->comboBox_PreProcess->clear();
    ui->comboBox_PreProcess->addItems(file_list);
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

    int ret;
    ret = m_serial.write(send_data);
}

void XGD_HOST::on_pushButton_StartTrans_clicked()
{
    deal_trans_request();
}

void XGD_HOST::deal_trans_result()
{
    quint8 trans_result = tlv_map.find("03").value().toUInt();
    quint8 trans_outcome = tlv_map.find("DF23").value().toUInt();
    quint8 trans_cvm = tlv_map.find("FF8109").value().toUInt();
    QString disp_message;

//    tlv_map.find("03")->isNull();
    //show transaction result
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

    //show transaction outcome
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

    //show  cvm
    switch (trans_cvm)
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

    QMapIterator<QString, QString> it(tlv_map);
    while (it.hasNext())
    {
        it.next();
        if(it.key() == "03" || it.key() == "DF23" || it.key() == "FF8109")
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
    QByteArray send_data,temp_byte;
    QString temp_str;

    send_data.append(STX);
    send_data.append(TRANS_RESULT_SEND);
    temp_str.append("0003030100");
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
        if(tlv_map.find("56")->isNull() != true)
        {
            disp_message.clear();
            disp_message.append("Track 1 Data: "+tlv_map.find("56").value());
            show_message(disp_message+"\n");
        }
        if(tlv_map.find("9F6B")->isNull() != true)
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