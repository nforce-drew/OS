/****************************************************************************
** Meta object code from reading C++ file 'Admin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Admin/Admin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Admin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Admin_t {
    QByteArrayData data[15];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Admin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Admin_t qt_meta_stringdata_Admin = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Admin"
QT_MOC_LITERAL(1, 6, 10), // "deleteTask"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 19), // "setEnabledDeleteBtn"
QT_MOC_LITERAL(4, 38, 13), // "slotReadyRead"
QT_MOC_LITERAL(5, 52, 9), // "slotError"
QT_MOC_LITERAL(6, 62, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(7, 91, 3), // "err"
QT_MOC_LITERAL(8, 95, 13), // "slotConnected"
QT_MOC_LITERAL(9, 109, 20), // "slotSendDataToServer"
QT_MOC_LITERAL(10, 130, 4), // "TYPE"
QT_MOC_LITERAL(11, 135, 8), // "dataType"
QT_MOC_LITERAL(12, 144, 5), // "char*"
QT_MOC_LITERAL(13, 150, 4), // "data"
QT_MOC_LITERAL(14, 155, 3) // "len"

    },
    "Admin\0deleteTask\0\0setEnabledDeleteBtn\0"
    "slotReadyRead\0slotError\0"
    "QAbstractSocket::SocketError\0err\0"
    "slotConnected\0slotSendDataToServer\0"
    "TYPE\0dataType\0char*\0data\0len"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Admin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       8,    0,   50,    2, 0x08 /* Private */,
       9,    3,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12, QMetaType::UInt,   11,   13,   14,

       0        // eod
};

void Admin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Admin *_t = static_cast<Admin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deleteTask(); break;
        case 1: _t->setEnabledDeleteBtn(); break;
        case 2: _t->slotReadyRead(); break;
        case 3: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->slotConnected(); break;
        case 5: _t->slotSendDataToServer((*reinterpret_cast< TYPE(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject Admin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Admin.data,
      qt_meta_data_Admin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Admin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Admin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Admin.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Admin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
