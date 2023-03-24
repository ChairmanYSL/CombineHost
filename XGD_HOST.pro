QT       += core gui xml serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    avl.cpp \
    main.cpp \
    tool.cpp \
    xgd_host.cpp

HEADERS += \
#    avl.h \
    tool.h \
    xgd_host.h

FORMS += \
    xgd_host.ui

#CONFIG += console

# 版本信息
VERSION = 0.0.0.2
# 图标
RC_ICONS = app.ico
# 公司名称
QMAKE_TARGET_COMPANY = "Shenzhen Xinguodu Technology Co., Ltd"
# 产品名称
QMAKE_TARGET_PRODUCT = "XGD_HOST"
# 文件说明
QMAKE_TARGET_DESCRIPTION = "EMV Test Host"
# 版权信息
QMAKE_TARGET_COPYRIGHT = "Powered by bruce lee. All rights reserved."
# 中文（简体）
RC_LANG = 0x0004


#UI_DIR = ./UI
DEFINES += QT_MESSAGELOGCONTEXT

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

