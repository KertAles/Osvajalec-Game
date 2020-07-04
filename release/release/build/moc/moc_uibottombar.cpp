/****************************************************************************
** Meta object code from reading C++ file 'uibottombar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SuperProjekt/UI/uibottombar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uibottombar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UIBottomBar_t {
    QByteArrayData data[15];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UIBottomBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UIBottomBar_t qt_meta_stringdata_UIBottomBar = {
    {
QT_MOC_LITERAL(0, 0, 11), // "UIBottomBar"
QT_MOC_LITERAL(1, 12, 14), // "endTurnClicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "moveClicked"
QT_MOC_LITERAL(4, 40, 13), // "attackClicked"
QT_MOC_LITERAL(5, 54, 14), // "destroyClicked"
QT_MOC_LITERAL(6, 69, 17), // "makeArcherClicked"
QT_MOC_LITERAL(7, 87, 17), // "makeKnightClicked"
QT_MOC_LITERAL(8, 105, 18), // "makePikemanClicked"
QT_MOC_LITERAL(9, 124, 17), // "makeWorkerClicked"
QT_MOC_LITERAL(10, 142, 15), // "makeFortClicked"
QT_MOC_LITERAL(11, 158, 15), // "makeFarmClicked"
QT_MOC_LITERAL(12, 174, 15), // "makeMineClicked"
QT_MOC_LITERAL(13, 190, 19), // "makeWoodcampClicked"
QT_MOC_LITERAL(14, 210, 18) // "queueButtonClicked"

    },
    "UIBottomBar\0endTurnClicked\0\0moveClicked\0"
    "attackClicked\0destroyClicked\0"
    "makeArcherClicked\0makeKnightClicked\0"
    "makePikemanClicked\0makeWorkerClicked\0"
    "makeFortClicked\0makeFarmClicked\0"
    "makeMineClicked\0makeWoodcampClicked\0"
    "queueButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UIBottomBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UIBottomBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UIBottomBar *_t = static_cast<UIBottomBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->endTurnClicked(); break;
        case 1: _t->moveClicked(); break;
        case 2: _t->attackClicked(); break;
        case 3: _t->destroyClicked(); break;
        case 4: _t->makeArcherClicked(); break;
        case 5: _t->makeKnightClicked(); break;
        case 6: _t->makePikemanClicked(); break;
        case 7: _t->makeWorkerClicked(); break;
        case 8: _t->makeFortClicked(); break;
        case 9: _t->makeFarmClicked(); break;
        case 10: _t->makeMineClicked(); break;
        case 11: _t->makeWoodcampClicked(); break;
        case 12: _t->queueButtonClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UIBottomBar::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UIBottomBar.data,
      qt_meta_data_UIBottomBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UIBottomBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UIBottomBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UIBottomBar.stringdata0))
        return static_cast<void*>(const_cast< UIBottomBar*>(this));
    if (!strcmp(_clname, "UIComponent"))
        return static_cast< UIComponent*>(const_cast< UIBottomBar*>(this));
    return QObject::qt_metacast(_clname);
}

int UIBottomBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
