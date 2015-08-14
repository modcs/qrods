//The MIT License (MIT)

//Copyright (c) <2015> <CIn-UFPE>

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#ifndef TESTDATAOBJECT_H
#define TESTDATAOBJECT_H

#include <QObject>
#include <QtTest/QTest>
#include "qrods.h"

class TestDataObjectClient : public QObject
{
    Q_OBJECT
public:
    explicit TestDataObjectClient(QString &newHost, QString &newport, QString &newUser, QString &newPassword,bool isSecureHttps, QString &_testFile);

private slots:

    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testRemoveDataObject();
    void testAddFileMetadata();
    void getDataObjectMetadata();
    void getDataObjectMetadataAsync();
    void testMetadataCapacity();
    //void testRetrieveMetadataCapacity();

private:
    int getCurrentListSize();
    bool fileExistsRemote(QString & collection, QString &fileName);
    MetadataEntry getTestMetadata();
    bool createTextFiles(QString baseFileName, int size);
    bool fileExistsLocal(QString & fileName);
    bool deleteFiles(QString &fileName);
    QString getFormatedTime(int milliseconds);


    QString testFile;
    QString host;
    QString hostFull;
    QString port;
    QString user;
    QString password;
    bool secureHttps;
    int objectsBefore;
    int objectsAfter;
    QString collecUrl;
    QString fileContUrl;
    QString dataObjUrl;
    QString path;
    QString pathTestCollection;
    QRODS *model ;
    QString pathToTheFile;
    QString anotherPathToTheFile; // without double bars " // "
    QString localPath;
};

#endif // TESTDATAOBJECT_H
