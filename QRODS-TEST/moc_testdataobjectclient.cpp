/****************************************************************************
** Meta object code from reading C++ file 'testdataobjectclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testdataobjectclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testdataobjectclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TestDataObjectClient_t {
    QByteArrayData data[11];
    char stringdata[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestDataObjectClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestDataObjectClient_t qt_meta_stringdata_TestDataObjectClient = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TestDataObjectClient"
QT_MOC_LITERAL(1, 21, 12), // "initTestCase"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 15), // "cleanupTestCase"
QT_MOC_LITERAL(4, 51, 4), // "init"
QT_MOC_LITERAL(5, 56, 7), // "cleanup"
QT_MOC_LITERAL(6, 64, 20), // "testRemoveDataObject"
QT_MOC_LITERAL(7, 85, 19), // "testAddFileMetadata"
QT_MOC_LITERAL(8, 105, 21), // "getDataObjectMetadata"
QT_MOC_LITERAL(9, 127, 26), // "getDataObjectMetadataAsync"
QT_MOC_LITERAL(10, 154, 20) // "testMetadataCapacity"

    },
    "TestDataObjectClient\0initTestCase\0\0"
    "cleanupTestCase\0init\0cleanup\0"
    "testRemoveDataObject\0testAddFileMetadata\0"
    "getDataObjectMetadata\0getDataObjectMetadataAsync\0"
    "testMetadataCapacity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestDataObjectClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

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

       0        // eod
};

void TestDataObjectClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestDataObjectClient *_t = static_cast<TestDataObjectClient *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->init(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->testRemoveDataObject(); break;
        case 5: _t->testAddFileMetadata(); break;
        case 6: _t->getDataObjectMetadata(); break;
        case 7: _t->getDataObjectMetadataAsync(); break;
        case 8: _t->testMetadataCapacity(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TestDataObjectClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestDataObjectClient.data,
      qt_meta_data_TestDataObjectClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TestDataObjectClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestDataObjectClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TestDataObjectClient.stringdata))
        return static_cast<void*>(const_cast< TestDataObjectClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TestDataObjectClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
