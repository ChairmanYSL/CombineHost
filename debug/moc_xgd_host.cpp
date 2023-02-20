/****************************************************************************
** Meta object code from reading C++ file 'xgd_host.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../xgd_host.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xgd_host.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_XGD_HOST_t {
    QByteArrayData data[9];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XGD_HOST_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XGD_HOST_t qt_meta_stringdata_XGD_HOST = {
    {
QT_MOC_LITERAL(0, 0, 8), // "XGD_HOST"
QT_MOC_LITERAL(1, 9, 32), // "on_pushButton_ScanSerial_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 32), // "on_pushButton_OpenSerial_clicked"
QT_MOC_LITERAL(4, 76, 32), // "on_pushButton_ClrMessage_clicked"
QT_MOC_LITERAL(5, 109, 11), // "handleError"
QT_MOC_LITERAL(6, 121, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(7, 150, 5), // "error"
QT_MOC_LITERAL(8, 156, 12) // "readTermData"

    },
    "XGD_HOST\0on_pushButton_ScanSerial_clicked\0"
    "\0on_pushButton_OpenSerial_clicked\0"
    "on_pushButton_ClrMessage_clicked\0"
    "handleError\0QSerialPort::SerialPortError\0"
    "error\0readTermData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XGD_HOST[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       8,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

       0        // eod
};

void XGD_HOST::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XGD_HOST *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_ScanSerial_clicked(); break;
        case 1: _t->on_pushButton_OpenSerial_clicked(); break;
        case 2: _t->on_pushButton_ClrMessage_clicked(); break;
        case 3: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 4: _t->readTermData(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject XGD_HOST::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_XGD_HOST.data,
    qt_meta_data_XGD_HOST,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *XGD_HOST::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XGD_HOST::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_XGD_HOST.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int XGD_HOST::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
