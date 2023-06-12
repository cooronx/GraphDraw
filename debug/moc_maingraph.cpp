/****************************************************************************
** Meta object code from reading C++ file 'maingraph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../maingraph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maingraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainGraph_t {
    QByteArrayData data[16];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainGraph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainGraph_t qt_meta_stringdata_MainGraph = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MainGraph"
QT_MOC_LITERAL(1, 10, 6), // "newAni"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 10), // "QTimeLine*"
QT_MOC_LITERAL(4, 29, 6), // "logAdd"
QT_MOC_LITERAL(5, 36, 8), // "viewLog*"
QT_MOC_LITERAL(6, 45, 8), // "GraphDfs"
QT_MOC_LITERAL(7, 54, 10), // "customVex*"
QT_MOC_LITERAL(8, 65, 8), // "startvex"
QT_MOC_LITERAL(9, 74, 7), // "Kruskal"
QT_MOC_LITERAL(10, 82, 4), // "Prim"
QT_MOC_LITERAL(11, 87, 12), // "VisitingLine"
QT_MOC_LITERAL(12, 100, 11), // "customLine*"
QT_MOC_LITERAL(13, 112, 9), // "saveGraph"
QT_MOC_LITERAL(14, 122, 9), // "readGraph"
QT_MOC_LITERAL(15, 132, 6) // "addAni"

    },
    "MainGraph\0newAni\0\0QTimeLine*\0logAdd\0"
    "viewLog*\0GraphDfs\0customVex*\0startvex\0"
    "Kruskal\0Prim\0VisitingLine\0customLine*\0"
    "saveGraph\0readGraph\0addAni"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainGraph[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   65,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    1,   70,    2, 0x0a /* Public */,
      13,    0,   73,    2, 0x0a /* Public */,
      14,    0,   74,    2, 0x0a /* Public */,
      15,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void MainGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainGraph *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newAni((*reinterpret_cast< QTimeLine*(*)>(_a[1]))); break;
        case 1: _t->logAdd((*reinterpret_cast< viewLog*(*)>(_a[1]))); break;
        case 2: _t->GraphDfs((*reinterpret_cast< customVex*(*)>(_a[1]))); break;
        case 3: { int _r = _t->Kruskal();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->Prim();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->VisitingLine((*reinterpret_cast< customLine*(*)>(_a[1]))); break;
        case 6: _t->saveGraph(); break;
        case 7: _t->readGraph(); break;
        case 8: _t->addAni((*reinterpret_cast< QTimeLine*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTimeLine* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< viewLog* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< customLine* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTimeLine* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainGraph::*)(QTimeLine * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainGraph::newAni)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainGraph::*)(viewLog * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainGraph::logAdd)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainGraph::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MainGraph.data,
    qt_meta_data_MainGraph,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainGraph.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainGraph::newAni(QTimeLine * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainGraph::logAdd(viewLog * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
