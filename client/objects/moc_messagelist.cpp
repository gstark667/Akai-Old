/****************************************************************************
** Meta object code from reading C++ file 'messagelist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../messagelist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'messagelist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MessageList_t {
    QByteArrayData data[12];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MessageList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MessageList_t qt_meta_stringdata_MessageList = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MessageList"
QT_MOC_LITERAL(1, 12, 14), // "friendSelected"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 45, 4), // "item"
QT_MOC_LITERAL(5, 50, 13), // "groupSelected"
QT_MOC_LITERAL(6, 64, 13), // "updateFriends"
QT_MOC_LITERAL(7, 78, 7), // "friends"
QT_MOC_LITERAL(8, 86, 12), // "updateGroups"
QT_MOC_LITERAL(9, 99, 6), // "groups"
QT_MOC_LITERAL(10, 106, 9), // "addFriend"
QT_MOC_LITERAL(11, 116, 8) // "addGroup"

    },
    "MessageList\0friendSelected\0\0"
    "QListWidgetItem*\0item\0groupSelected\0"
    "updateFriends\0friends\0updateGroups\0"
    "groups\0addFriend\0addGroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MessageList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,
      10,    1,   56,    2, 0x0a /* Public */,
      11,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,    7,
    QMetaType::Void, QMetaType::QStringList,    9,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void MessageList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MessageList *_t = static_cast<MessageList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->friendSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->groupSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->updateFriends((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->updateGroups((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 4: _t->addFriend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->addGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MessageList::*_t)(QListWidgetItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MessageList::friendSelected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MessageList::*_t)(QListWidgetItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MessageList::groupSelected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MessageList::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_MessageList.data,
      qt_meta_data_MessageList,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MessageList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MessageList::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MessageList.stringdata0))
        return static_cast<void*>(const_cast< MessageList*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int MessageList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MessageList::friendSelected(QListWidgetItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MessageList::groupSelected(QListWidgetItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
