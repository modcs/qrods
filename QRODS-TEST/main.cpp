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


#include "testfilecontentclient.h"
#include "testdataobjectclient.h"
#include "testcollectionclient.h"
#include <QtTest/QtTest>
#include <QCoreApplication>
#include <QFile>
#include <QSettings>
#include <string>
#include <iostream>


QString deployRootPathTest = QDir::cleanPath(QDir::currentPath()+QString::fromStdString("/"));
QSettings settingsTest(QString(deployRootPathTest + "/config.ini"), QSettings::IniFormat);

QVector<QString> testFileNames;
QVector<int> testFileSizes;

QString getHostTest(){
    return settingsTest.value("config/irods/host", "Host not properly specified.").toString();
}

QString getPortTest(){
    return settingsTest.value("config/irods/port", "Port not properly specified.").toString();
}

QString getUserTest(){
    return settingsTest.value("config/irods/user", "User not properly specified.").toString();
}

QString getPasswordPathTest(){
    return settingsTest.value("config/irods/passwordPath", "Password not properly specified.").toString();
}

bool secureHttpTest(){
    QString boolean(settingsTest.value("config/irods/secureHttp", "Http mode not properly specified.").toString());
    return QString::compare(boolean,"false") == 0 ? false : true ;
}


/**
 * Main class used to execute all the tests at once or separately.
 * @brief main Main class used to execute all the tests at once or separately.
 */
int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);

    QString host(getHostTest());
    qDebug() << "Used host: "<< deployRootPathTest << "\t -- " << host;
    QString port(getPortTest());
    QString user(getUserTest());
    QString password("rods");
    bool secureHttps = secureHttpTest();
    QString testFileNormalSize("log.txt");


    TestFileContentClient testFileContentClient(host, port, user, password, secureHttps, testFileNormalSize,testFileNames, deployRootPathTest);
    TestDataObjectClient testaDataObjectClient(host, port, user, password, secureHttps, testFileNormalSize);
    TestCollectionClient testCollectionClient(host, port, user, password, secureHttps, testFileNormalSize);


    /* Runs each test class*/
    QTest::qExec(&testaDataObjectClient, argc, argv) ;
    QTest::qExec(&testFileContentClient, argc, argv) ;
    QTest::qExec(&testCollectionClient, argc, argv) ;

    return 0;
}
