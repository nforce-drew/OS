/****************************************************************************
** Meta object code from reading C++ file 'MyClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MyClient/MyClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyClient_t {
    QByteArrayData data[16];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyClient_t qt_meta_stringdata_MyClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MyClient"
QT_MOC_LITERAL(1, 9, 13), // "slotReadyRead"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "slotError"
QT_MOC_LITERAL(4, 34, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(5, 63, 3), // "err"
QT_MOC_LITERAL(6, 67, 21), // "slotSendFilesToServer"
QT_MOC_LITERAL(7, 89, 13), // "slotConnected"
QT_MOC_LITERAL(8, 103, 13), // "slotReconnect"
QT_MOC_LITERAL(9, 117, 16), // "slotDroppedFiles"
QT_MOC_LITERAL(10, 134, 8), // "newFiles"
QT_MOC_LITERAL(11, 143, 17), // "slotCancelClicked"
QT_MOC_LITERAL(12, 161, 19), // "slotDownloadClicked"
QT_MOC_LITERAL(13, 181, 16), // "slotSolveClicked"
QT_MOC_LITERAL(14, 198, 22), // "setDeleteBtnFileEnable"
QT_MOC_LITERAL(15, 221, 17) // "deleteFileClicked"

    },
    "MyClient\0slotReadyRead\0\0slotError\0"
    "QAbstractSocket::SocketError\0err\0"
    "slotSendFilesToServer\0slotConnected\0"
    "slotReconnect\0slotDroppedFiles\0newFiles\0"
    "slotCancelClicked\0slotDownloadClicked\0"
    "slotSolveClicked\0setDeleteBtnFileEnable\0"
    "deleteFileClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    1,   70,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    1,   76,    2, 0x08 /* Private */,
      11,    0,   79,    2, 0x08 /* Private */,
      12,    0,   80,    2, 0x08 /* Private */,
      13,    0,   81,    2, 0x08 /* Private */,
      14,    0,   82,    2, 0x08 /* Private */,
      15,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotReadyRead(); break;
        case 1: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 2: _t->slotSendFilesToServer(); break;
        case 3: _t->slotConnected(); break;
        case 4: _t->slotReconnect(); break;
        case 5: _t->slotDroppedFiles((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 6: _t->slotCancelClicked(); break;
        case 7: _t->slotDownloadClicked(); break;
        case 8: _t->slotSolveClicked(); break;
        case 9: _t->setDeleteBtnFileEnable(); break;
        case 10: _t->deleteFileClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyClient::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MyClient.data,
    qt_meta_data_MyClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyClient.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MyClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
