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


#ifndef TESTFILECONTENTCLIENT_H
#define TESTFILECONTENTCLIENT_H

#include <QObject>
#include <QtTest/QTest>
#include "qrods.h"
#include <QDir>


class TestFileContentClient : public QObject
{
    Q_OBJECT
public:
    explicit TestFileContentClient(QString &newHost, QString &newport, QString &newUser, QString &newPassword, bool isSecureHttps, QString & _testFile, QVector<QString> _testFileNames,QString deployRootPathTest);
private slots:
    
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    
    void testGetFile();
    void testUploadFilesWithLargeNames();

    void testUploadOnlyOneSmallFile();
    void testUpload_10000Files_10MB();
    void testUpload_1000Files_100MB();
    void testUpload_100Files_1GB();
    void testUpload_10File_10GB();
    void testUpload_1File_100GB();
    void testUploadDifferentSizeFiles();


private:
    void forceFileRemoval(QRODS *qrods, bool force);

    int  getCurrentListSize();
    void uploadFileAux(QString dir, QString collectionPath, QString file);
    bool fileExistsLocal(QString &localFilePath);
    bool fileExistsRemote(QString & collection, QString &fileName);
    void deleteLocalFile(QString & localFilePath);
    QString getRandomString(int length);
    bool createSingleTextFiles(QString &baseFileName);
    void createMultipleLargeFiles(QString subDir, QString fileNameInitials, int size, int number);
    void createSingleFiles();
    bool createTextFiles(QString &baseFileName);
    QString getFormatedTime(int milliseconds);
    void fillTestFileNamesAndSizes();
    void createTestFolders();
    bool createTextFiles(QString baseFileName, int size);
    bool createLargeFilesByDownload(QString &testFileMediumSize,QString &address);
    bool deleteFiles(QString &fileName);
    bool removeDirectory( QDir dir );
    void createFolder(QString folder);
    void removeDir(QString foldername);
    void uploadAndAssertLargeFilesAux(int number, QString dirTest, int size, QString fileNameInitials, QString pathTestCollection);

    QString testFile;
    QString testFileMediumSize;
    QVector<QString> testFileNames;
    QString host;
    QString hostFull;
    QString port;
    QString user;
    QString password;
    bool secureHttps;
    int objectsBefore;
    int objectsAfter;
    //QString collecUrl;
    QString fileContUrl;
    QString dataObjUrl;
    QString path;
    QRODS *model ;
    QString pathToTheFile;
    QString anotherPathToTheFile;
    QString localPath;

    
};

#endif // TESTFILECONTENTCLIENT_H
