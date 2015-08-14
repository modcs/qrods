/****************************************************************************
** Meta object code from reading C++ file 'testfilecontentclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testfilecontentclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testfilecontentclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TestFileContentClient_t {
    QByteArrayData data[15];
    char stringdata[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestFileContentClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestFileContentClient_t qt_meta_stringdata_TestFileContentClient = {
    {
QT_MOC_LITERAL(0, 0, 21), // "TestFileContentClient"
QT_MOC_LITERAL(1, 22, 12), // "initTestCase"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 15), // "cleanupTestCase"
QT_MOC_LITERAL(4, 52, 4), // "init"
QT_MOC_LITERAL(5, 57, 7), // "cleanup"
QT_MOC_LITERAL(6, 65, 11), // "testGetFile"
QT_MOC_LITERAL(7, 77, 29), // "testUploadFilesWithLargeNames"
QT_MOC_LITERAL(8, 107, 26), // "testUploadOnlyOneSmallFile"
QT_MOC_LITERAL(9, 134, 26), // "testUpload_10000Files_10MB"
QT_MOC_LITERAL(10, 161, 26), // "testUpload_1000Files_100MB"
QT_MOC_LITERAL(11, 188, 23), // "testUpload_100Files_1GB"
QT_MOC_LITERAL(12, 212, 22), // "testUpload_10File_10GB"
QT_MOC_LITERAL(13, 235, 22), // "testUpload_1File_100GB"
QT_MOC_LITERAL(14, 258, 28) // "testUploadDifferentSizeFiles"

    },
    "TestFileContentClient\0initTestCase\0\0"
    "cleanupTestCase\0init\0cleanup\0testGetFile\0"
    "testUploadFilesWithLargeNames\0"
    "testUploadOnlyOneSmallFile\0"
    "testUpload_10000Files_10MB\0"
    "testUpload_1000Files_100MB\0"
    "testUpload_100Files_1GB\0testUpload_10File_10GB\0"
    "testUpload_1File_100GB\0"
    "testUploadDifferentSizeFiles"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestFileContentClient[] = {

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
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

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

void TestFileContentClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TestFileContentClient *_t = static_cast<TestFileContentClient *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->init(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->testGetFile(); break;
        case 5: _t->testUploadFilesWithLargeNames(); break;
        case 6: _t->testUploadOnlyOneSmallFile(); break;
        case 7: _t->testUpload_10000Files_10MB(); break;
        case 8: _t->testUpload_1000Files_100MB(); break;
        case 9: _t->testUpload_100Files_1GB(); break;
        case 10: _t->testUpload_10File_10GB(); break;
        case 11: _t->testUpload_1File_100GB(); break;
        case 12: _t->testUploadDifferentSizeFiles(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TestFileContentClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestFileContentClient.data,
      qt_meta_data_TestFileContentClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TestFileContentClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestFileContentClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TestFileContentClient.stringdata))
        return static_cast<void*>(const_cast< TestFileContentClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TestFileContentClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
