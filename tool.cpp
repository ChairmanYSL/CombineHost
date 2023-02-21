#include "tool.h"

void convertStringToHex(const QString &str, QByteArray &byteData)
{
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.length();

    byteData.resize(len/2);
    char lstr,hstr;

    for(int i = 0; i < len; )
    {
        hstr = str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
        {
            break;
        }
        lstr = str[i].toLatin1();
        hexdata =convertCharToHex(hstr);
        lowhexdata = convertCharToHex(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
        {
            break;
        }
        else
        {
            hexdata = hexdata * 16 + lowhexdata;
        }
        i++;
        byteData[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    byteData.resize(hexdatalen);
}

char convertCharToHex(char ch)
{
    if((ch >= '0' && (ch <= '9')))
        return ch - 0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch - 'A' + 10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch - 'a' + 10;
    else
        return (-1);
}

QString convertHexToString(QByteArray byteData)
{
    int len = byteData.count();
    int hexdata;
    char lstr,hstr;
    QString str;

    qDebug()<<"byte data len:"<<len;

    for(int i = 0; i < len; i++)
    {
        hexdata = (quint8)byteData.data()[i];
        hstr = convertHexToChar(hexdata >> 4);
        str.append(hstr);
        lstr = convertHexToChar(hexdata & 0x0F);
        str.append(lstr);
    }

    return str;
}

char convertHexToChar(char hex)
{
    if(hex >= 0 && hex <= 9)
    {
        return hex + 0x30;
    }
    else if(hex >= 10 && hex <= 15)
    {
        return hex + 55;
    }
    else
    {
        return (-1);
    }
}

void Hex2String(QString &str, const QByteArray &byteData)
{
    foreach(int hex, byteData)
    {
        str += QString::number(hex, 16).toUpper();
    }
}


void TraceHexFromByteArray(const char *title, QByteArray src)
{
    QString info_log;

    qDebug()<<title<<":\n";
    for(int i = 0; i < src.count(); i++)
    {
        info_log.append(QObject::tr("0x%1 ").arg((quint8)src.at(i), 2, 16, QLatin1Char('0')).toUpper());
    }
    qDebug()<<info_log;
}
