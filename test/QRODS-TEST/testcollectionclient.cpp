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


#include "qrods.h"
#include "collectionclientsync.h"
#include "testcollectionclient.h"
#include <QDebug>
#include <QList>
#include <QFileDialog>
#include <QSettings>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

TestCollectionClient::TestCollectionClient(QString &newHost, QString &newport, QString &newUser, QString &newPassword, bool isSecureHttps, QString &_testFile){
    testFile = QString(_testFile);
    testDownloadFile = QString("DownloadedFile.txt");
    host = QString(newHost);
    port = QString(newport);
    user = QString(newUser);
    password = QString(newPassword);
    secureHttps = isSecureHttps;
    if(isSecureHttps)
        hostFull = QString("https://"+host);
    else
        hostFull = QString("http://"+host);

    objectsBefore=0;
    objectsAfter=0;

    collecUrl = QString(hostFull+":"+port+"/irods-rest/rest/collection/");
    path = QString("/tempZone/home/rods");
    pathTestCollection = QString("/tempZone/home/test/alpha");
    model = new QRODS();
    pathToTheFile = QString(QDir::cleanPath(pathTestCollection+"/"+testFile));
    localPath = QString(QDir::cleanPath(QDir::currentPath()+"/"+testFile));
    anotherPathToTheFile = QString(QDir::cleanPath("tempZone/home/test/alpha/"+testFile)); // FIX ME, foi preciso criar outra variavel para passar o "path" sem uma barra dobrada " // "
}

void TestCollectionClient::initTestCase() {
    model = new QRODS();
    model->setUser(user);
    model->setHost(host);
    model->setPort(port.toInt());
    model->setPassword(password);
    model->connectToServer(path, secureHttps);


    /* A sample file: log.txt */
    if(!createTextFiles(testFile,1)){
        qDebug() << "File "<< testFile << " has not been created!";
    }

    QTest::qWait(3500);
}

void TestCollectionClient::cleanupTestCase() {

}

void TestCollectionClient::init() {
    //CREATE COLLECTION
    model->addCollection(pathTestCollection);
    QString newPathToTheFile(QDir::cleanPath(pathTestCollection.mid(1)+"/"+testFile));
    QTest::qWait(2000);
    //UPLOAD FILE TO THE CREATED COLLECTION
    model->uploadFile(newPathToTheFile, localPath);

    QTest::qWait(3500);
}

void TestCollectionClient::cleanup() {

    QString correctPath(pathTestCollection.mid(1));
    model->removeCollection(correctPath);

    objectsBefore = 0;
    objectsAfter = 0;

}

/**
 * Test to add one collection with one file inside and assert its existence on iRODS.
 * @brief TestCollectionClient::testAddCollection Test to add one collection with one file inside and assert its existence on iRODS.
 */
void TestCollectionClient::testAddCollection(){
    //QSKIP("SKIPPING this test.");

    QString ordinaryCollection("/tempZone/home/test/emc");

    model->addCollection(ordinaryCollection);

    QString altPathToTheFile("tempZone/home/test/emc/log.txt");
    model->uploadFile(altPathToTheFile, localPath);

    objectsBefore = getCurrentListSize(ordinaryCollection);
    QCOMPARE(objectsBefore,1);
    model->removeCollection(ordinaryCollection);

}



/**
 * Test to remove one collection from iRODS and assert that it does not exists anymore.
 * @brief TestCollectionClient::testRemoveCollection Test to remove one collection from iRODS and assert that it does not exists anymore.
 */
void TestCollectionClient::testRemoveCollection(){
    QSKIP("SKIPPING this test.");

    QVERIFY(collectionExists(pathTestCollection));

    model->removeCollection(pathTestCollection);

    QVERIFY(!collectionExists(pathTestCollection));
}


/**
 * Test to add a number of collections (variable numberOfCollections)  and assert its existence.
 * @brief TestCollectionClient::testAddCollections Test to add a number of collections and assert its existence.
 */
void TestCollectionClient::testAddManyCollections(){
    //QSKIP("SKIPPING this test.");
    int numberOfCollections = 100;
    int count = 0;

    for(int i = 0; i < numberOfCollections; i++){
        QString tempCollection(pathTestCollection+"/test"+QString::number(i));

        model->addCollection(tempCollection);
        QString tempFilePath(pathTestCollection+"/test"+QString::number(i)+"/"+testFile);
        model->uploadFile(tempFilePath,localPath);

        count++;
    }

    QCOMPARE(getCurrentListSize()-1,numberOfCollections);

 }

/**
 * Auxiliary method used to get how many objects the test collection has.
 * @brief TestCollectionClient::getCurrentListSize Auxiliary method used to get how many objects the test collection has.
 * @return the number of objects inside the collection.
 */
int TestCollectionClient::getCurrentListSize()
{

    CollectionClient coll(collecUrl, user, password);
    FileListingEntry* _rootNode = new FileListingEntry();
    _rootNode->setPathOrName(pathTestCollection);
    _rootNode->setObjectType(FileListingEntry::COLLECTION);
    _rootNode->setHasMoreCollections(true);

    CollectionClientSync collSync(&coll);
    collSync.getCollectionDataLazy(_rootNode);

    QList<FileListingEntry*> * list = _rootNode->children();

    return list->size();

}

/**
 * Auxiliary method used to get how many objects one specific collection has.
 * @brief TestCollectionClient::getCurrentListSize Auxiliary method used to get how many objects one specific collection has.
 * @param _pathTestCollection the desired collection to verify its content size
 * @return the number of objects inside the collection
 */
int TestCollectionClient::getCurrentListSize(QString &_pathTestCollection)
{
    CollectionClient coll(collecUrl, user, password);
    FileListingEntry* _rootNode = new FileListingEntry();
    _rootNode->setPathOrName(_pathTestCollection);
    _rootNode->setObjectType(FileListingEntry::COLLECTION);
    _rootNode->setHasMoreCollections(true);

    CollectionClientSync collSync(&coll);
    collSync.getCollectionDataLazy(_rootNode);

    QList<FileListingEntry*> * list = _rootNode->children();
    return list->size();
}

/**
 * Auxiliary method used to verify if a collection exists
 * @brief TestCollectionClient::collectionExists Auxiliary method used to verify if a collection exists
 * @param _pathTestCollection the collection to verify its existence
 * @return true if the collection exists
 */
bool TestCollectionClient::collectionExists(QString &_pathTestCollection)
{
    CollectionClient coll(collecUrl, user, password);

    FileListingEntry* _rootNode = new FileListingEntry();

    QString tempPathTestCollection(_pathTestCollection);
    _rootNode->setPathOrName(tempPathTestCollection);
    _rootNode->setObjectType(FileListingEntry::COLLECTION);
    _rootNode->setHasMoreCollections(true);

    CollectionClientSync collSync(&coll);
    collSync.getCollectionDataLazy(_rootNode);

    QList<FileListingEntry*> * list = _rootNode->children();


    if (list->empty())
        return false;
    else
        return true;
}


/**
 * Auxiliary method used to create text files informing its name and size
 * @brief TestCollectionClient::createTextFiles Auxiliary method used to create text files informing its name and size
 * @param baseFileName the file name
 * @param size the files size
 * @return true if the file was created
 */
bool TestCollectionClient::createTextFiles(QString baseFileName, int size){
    QString localFilePathName(QDir::currentPath()+"/"+baseFileName);
    if(fileExistsLocal(localFilePathName)){
        qDebug() << "The file already exists!!";
        return true;
    }

    /* Try and open a file for output */
    QFile localFilePath(QDir::cleanPath(localFilePathName));
    localFilePath.open(QIODevice::WriteOnly);
    if(!localFilePath.isOpen()){
        qDebug() << "There's a file already using this name on the specified folder!";
        return false;
    }
    /* Point a QTextStream object at the file */
    QTextStream outStream(&localFilePath);
    QString fooText("MoDCSRG");
    if(size>1){
        for(int i = 1; i<size;i++){
            outStream << fooText;
        }
    }
    outStream << fooText;
    /* Close the file */
    localFilePath.close();
    /* Test if the file has been recorded*/

    if(!fileExistsLocal(baseFileName)){
        qDebug() << "Created but I can't find it!";
        return false;
    }
    return true;

}

/**
 * Auxiliary method that verifies if a file exists locally.
 * @brief TestCollectionClient::fileExistsLocal Auxiliary method that verifies if a file exists locally.
 * @param fileName the file name
 * @return true if the file exists
 */
bool TestCollectionClient::fileExistsLocal(QString & fileName){
    QFile localFilePath(fileName);

    if (!localFilePath.open(QIODevice::ReadOnly) || !localFilePath.exists()){
        return false;
    }
    return true;
}

/**
 * Auxiliary method used to delete a local file.
 * @brief TestCollectionClient::deleteFiles Auxiliary method used to delete a local file.
 * @param fileName the file name
 * @return true if the file was deleted
 */
bool TestCollectionClient::deleteFiles(QString &fileName){
    QString localFilePath(QDir::cleanPath(QDir::currentPath()+"/"+fileName));
    QFile localFile(localFilePath);
    if (fileExistsLocal(fileName)){
            localFile.remove();
    }
    if (fileExistsLocal(fileName)){
            return false;
    }
    return true;
}

/**
 * Auxiliary metthod to be used in performance tests, it is, to return milliseconds converted to hours, minutes and seconds.
 * @brief TestCollectionClient::getFormatedTime Auxiliary method to be used in performance tests, it is, to return milliseconds converted to hours, minutes and seconds.
 * @param milliseconds how long time in milliseconds
 * @return the formated String representing the time
 */
QString TestCollectionClient::getFormatedTime(int milliseconds){
    int seconds    = ((int) milliseconds /1000)%60 ;
    int minutes    = ((((int) milliseconds /1000) - seconds)/60) %60;
    int hours      = (((((int) milliseconds /1000) - seconds)/60) - minutes)/60;

    QString fullTime(QString::number(hours)+" h: "+QString::number(minutes)+" m: "+QString::number(seconds)+" s");

    return fullTime;
}
