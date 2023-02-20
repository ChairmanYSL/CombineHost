#include "xgd_host.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XGD_HOST w;
    w.show();

    return a.exec();
}
