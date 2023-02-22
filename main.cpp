#include "xgd_host.h"
#include <QApplication>
#include "tool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XGD_HOST w;

    qInstallMessageHandler(outputMessage);
    w.show();

    return a.exec();
}
