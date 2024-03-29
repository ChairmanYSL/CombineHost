#ifndef TOOL_H
#define TOOL_H

#include <QString>
#include <QByteArray>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QApplication>

char convertCharToHex(char ch);
void convertStringToHex(const QString &str, QByteArray &byteData);
void TraceHexFromByteArray(const char *title, QByteArray src);
QString convertHexToString(QByteArray byteData);
char convertHexToChar(char hex);
void Hex2String(QString &str, const QByteArray &byteData);
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);


#endif // TOOL_H
