/****************************************************************************
** Meta object code from reading C++ file 'betteroption.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../betteroption.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'betteroption.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_betterOption_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_betterOption_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_betterOption_t qt_meta_stringdata_betterOption = {
    {
QT_MOC_LITERAL(0, 0, 12), // "betterOption"
QT_MOC_LITERAL(1, 13, 13), // "isOpenChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "CountMaxed"
QT_MOC_LITERAL(4, 39, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(5, 63, 13) // "clearUserFile"

    },
    "betterOption\0isOpenChanged\0\0CountMaxed\0"
    "on_pushButton_4_clicked\0clearUserFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_betterOption[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void betterOption::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<betterOption *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->isOpenChanged(); break;
        case 1: _t->CountMaxed(); break;
        case 2: _t->on_pushButton_4_clicked(); break;
        case 3: _t->clearUserFile(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (betterOption::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&betterOption::isOpenChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (betterOption::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&betterOption::CountMaxed)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject betterOption::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_betterOption.data,
    qt_meta_data_betterOption,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *betterOption::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *betterOption::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_betterOption.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int betterOption::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void betterOption::isOpenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void betterOption::CountMaxed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
