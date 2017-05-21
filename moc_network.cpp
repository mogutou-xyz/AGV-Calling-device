/****************************************************************************
** Meta object code from reading C++ file 'network.h'
**
** Created: Sat May 20 18:23:08 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "network.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_network[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      21,    8,    8,    8, 0x08,
      34,    8,    8,    8, 0x08,
      75,    8,    8,    8, 0x08,
      90,    8,    8,    8, 0x08,
     100,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_network[] = {
    "network\0\0LinkClose()\0NewConnect()\0"
    "DisplayERR(QAbstractSocket::SocketError)\0"
    "GetHeartbeat()\0Timeout()\0Disconnect()\0"
};

void network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        network *_t = static_cast<network *>(_o);
        switch (_id) {
        case 0: _t->LinkClose(); break;
        case 1: _t->NewConnect(); break;
        case 2: _t->DisplayERR((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 3: _t->GetHeartbeat(); break;
        case 4: _t->Timeout(); break;
        case 5: _t->Disconnect(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData network::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject network::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_network,
      qt_meta_data_network, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &network::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *network::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_network))
        return static_cast<void*>(const_cast< network*>(this));
    return QThread::qt_metacast(_clname);
}

int network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void network::LinkClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
