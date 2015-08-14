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


#include "testdataobjectclient.h"
#include "qrods.h"
#include "collectionclientsync.h"
#include "dataobjectclientasync.h"
#include "collectionclient.h"
#include "metadataentry.h"

#include <QDebug>
#include <QList>
#include <QFileDialog>
#include <QSettings>
#include <QTime>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

TestDataObjectClient::TestDataObjectClient(QString &newHost, QString &newport, QString &newUser, QString &newPassword,bool isSecureHttps, QString &_testFile){
    testFile = QString(_testFile);
    host = QString (newHost);
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
    dataObjUrl = QString(hostFull+":"+port+"/irods-rest/rest/dataObject/");
    path = QString("/tempZone/home/rods");
    pathTestCollection = QString("/tempZone/home/test/alpha");
    model = new QRODS();
    pathToTheFile = QString(QDir::cleanPath(pathTestCollection+"/"+testFile));
    localPath = QString(QDir::cleanPath(QDir::currentPath()+"/"+testFile));
    anotherPathToTheFile = QString(QDir::cleanPath("tempZone/home/test/alpha/"+testFile)); // FIX ME, foi preciso criar outra variavel para passar o "path" sem uma barra dobrada " // "
}

void TestDataObjectClient::initTestCase() {
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

}

void TestDataObjectClient::cleanupTestCase() {

}

void TestDataObjectClient::init() {


    model->addCollection(pathTestCollection);

    model->uploadFile(pathToTheFile, localPath);


}

void TestDataObjectClient::cleanup() {


    QString correctPath(pathTestCollection.mid(1)); // because of "/"
    model->removeCollection(correctPath);

    objectsBefore = 0; // necessary variable
    objectsAfter = 0; // necessary variable


}

/**
 * Test to remove a file from the iRODS
 * @brief TestDataObjectClient::testRemoveDataObject Test to remove a file from the iRODS
 */
void TestDataObjectClient::testRemoveDataObject(){
    QSKIP("I'm skipping this test.");

    /* Get actual size of list*/
    objectsBefore = getCurrentListSize();
    QVERIFY(objectsBefore == 1);

    /* Remove the file */
    model->removeDataObject(anotherPathToTheFile, true); // Using the "force" flag

    /* Get actual size of list after the removal*/
    objectsAfter = getCurrentListSize();
    QCOMPARE(objectsBefore-1,objectsAfter);
}

/**
 * Test to add metadata to a file on iRODS
 * @brief TestDataObjectClient::testAddFileMetadata Test to add metadata to a file on iRODS
 */
void TestDataObjectClient::testAddFileMetadata(){
    QSKIP("I'm skipping this test.");

    /* Assert file not exists on iRODS*/
    if(!fileExistsRemote(pathTestCollection,testFile))
        QFAIL("The requested file is not at the iRODS server.");

    /* Assert there is no metadata */
    QList<MetadataEntry*>* metadataEntry = model->getDataObjectMetadata(anotherPathToTheFile);
    if(!metadataEntry->isEmpty())
        QFAIL("\n\tThe requested file has some metadata...");

    /* Insert metadata */
    QString att("Time");
    QString value(QTime::currentTime().toString());
    QString unit("Seconds");
    MetadataEntry newMetadata(att,value,unit);

    model->addCollectionMetadata(anotherPathToTheFile,newMetadata);

    QList<MetadataEntry*>* metadataEntry2;
    int loopCount = 500;
    do{

        metadataEntry2 = model->getDataObjectMetadata(anotherPathToTheFile);
        QTest::qWait(loopCount); // waiting for the update of metadata file at the iRODS server

}while(metadataEntry2->isEmpty());

    if(!metadataEntry2->isEmpty()){
        QCOMPARE(metadataEntry2->at(0)->value().toInt(),value.toInt());
    }
    else
        QFAIL("Failed, there is no metadata or the library returned void.");
}

/**
 * Test to get metadata from a file on iRODS
 * @brief TestDataObjectClient::getDataObjectMetadata Test to get metadata from a file on iRODS
 */
void TestDataObjectClient::getDataObjectMetadata(){
    QSKIP("I'm skipping this test.");

    /* Assert file is on the iRODS server */
    if(!fileExistsRemote(pathTestCollection,testFile))
        QFAIL("The requested file is not at the iRODS server.");

    /* Assert there is no metadata */
    QList<MetadataEntry*>* metadataEntry = model->getDataObjectMetadata(anotherPathToTheFile);
    if(!metadataEntry->isEmpty())
        QFAIL("The requested file has some metadata...");

    /* Insert metadata */
    QString att("Weight");
    QString value("70");
    QString unit("Kg");

    MetadataEntry newMetadata(att,value,unit);
    model->addCollectionMetadata(anotherPathToTheFile,newMetadata);

    QList<MetadataEntry*>* metadataEntry2;
    int loopCount = 500;

    do{
        metadataEntry2 = model->getDataObjectMetadata(anotherPathToTheFile);
        QTest::qWait(loopCount); // waiting for the update of file metadata at the iRODS server

    }while(metadataEntry2->isEmpty());

    if(!metadataEntry2->isEmpty()){
        QCOMPARE(metadataEntry2->at(0)->value().toInt(),value.toInt());
    }
    else
        QFAIL("Failed, there is no metadata or the library returned void.");
}

/**
 * Test to get metadata from a file on iRODS asynchronously
 * @brief TestDataObjectClient::getDataObjectMetadataAsync Test to get metadata from a file on iRODS asynchronously
 */
void TestDataObjectClient::getDataObjectMetadataAsync(){
    QSKIP("I'm skipping this test.");

    /* Assert file is on the iRODS server */
    if(!fileExistsRemote(pathTestCollection,testFile))
        QFAIL("The requested file is not at the iRODS server.");

    /* Assert there is no metadata */
    QList<MetadataEntry*>* metadataEntry = model->getDataObjectMetadata(anotherPathToTheFile);
    if(!metadataEntry->isEmpty())
        QFAIL("The requested file has some metadata...");

    /* Insert metadata */
    QString att("Weight");
    QString value("70");
    QString unit("Kg");
    MetadataEntry newMetadata(att,value,unit);

    model->addCollectionMetadata(anotherPathToTheFile,newMetadata);

    /* Assert there is a new metadata using the async mode */
    DataObjectClient dataObjClient(dataObjUrl, user, password);
    DataObjectClientAsync dataObjectAsync(&dataObjClient);
    /* get metadata from a file on iRODS asynchronously */
    QList<MetadataEntry*> * list = dataObjectAsync.getDataObjectMetadataAsync(anotherPathToTheFile);

    if(list->isEmpty()){
        QFAIL("Failed, there is no metadata or the library returned void.");
    }
    else
        QCOMPARE(list->at(0)->value().toInt(),value.toInt());
}

/**
 * Test to insert a huge number of metadata to a file on iRODS
 * @brief TestDataObjectClient::testMetadataCapacity Test to insert a huge number of metadata to a file on iRODS
 */
void TestDataObjectClient::testMetadataCapacity(){
    //QSKIP("I'm skipping this test.");

    /* Assert file is on the iRODS server */
    if(!fileExistsRemote(pathTestCollection,testFile))
        QFAIL("The requested file is not at the iRODS server.");


    /* Assert there is no metadata */
    QList<MetadataEntry*>* metadataEntry = model->getDataObjectMetadata(anotherPathToTheFile);
    if(!metadataEntry->isEmpty())
        QFAIL("The requested file has some metadata...");

    int metadataLimitCandidate = 100;

    int i = 0;
    for(; i<metadataLimitCandidate;i++){
        QString att(QString::number(i));
        QString value(QTime::currentTime().toString());
        QString unit("Seconds");
        MetadataEntry newMetadata(att,value,unit);

        model->addCollectionMetadata(anotherPathToTheFile,newMetadata);
    }

     /* Metadata retrieving */

    int loopCount = 30000;
    QList<MetadataEntry*>* metadataEntry2;
    do{
        metadataEntry2 = new QList<MetadataEntry*>;

        metadataEntry2 = model->getDataObjectMetadata(anotherPathToTheFile);
        QTest::qWait(loopCount); // waiting for the update of file metadata at the iRODS server

    }while(metadataEntry2->isEmpty());

    /* If empty response */
    if(metadataEntry2->isEmpty()){
        QFAIL("Failed, there is no metadata or the library returned void.");
    }
    /* Non-empty response, but is necessary to check if the Metadata count is equal to the inserted amount */
    else {
        QCOMPARE(QString::compare(QString::number( metadataEntry2->count() ), QString::number(i) ), 0);
    }

}

/**
 * Verifies how many files have in the pathTestCollection.
 * @brief TestDataObjectClient::getCurrentListSize  Verifies how many files have in the pathTestCollection.
 * @return how many files have in the pathTestCollection
 */
int TestDataObjectClient::getCurrentListSize(){
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
 * Verifies whether one file exists at iRODS.
 * @brief TestDataObjectClient::fileExistsRemote Verifies whether one file exists at iRODS.
 * @param collection the corresponding collection where the file resides.
 * @param fileName the name of the file
 * @return true if the file exists
 */
bool TestDataObjectClient::fileExistsRemote(QString & collection, QString &fileName){

    CollectionClient coll(collecUrl, user, password);

    FileListingEntry* _rootNode = new FileListingEntry();

    QString tempPathTestCollection(collection);
    _rootNode->setPathOrName(tempPathTestCollection);
    _rootNode->setObjectType(FileListingEntry::COLLECTION);
    _rootNode->setHasMoreCollections(true);

    CollectionClientSync collSync(&coll);
    collSync.getCollectionDataLazy(_rootNode);

    QList<FileListingEntry*> * list = _rootNode->children();
    for(int i = 0; i < list->count( ); i++){

        FileListingEntry* entry = list->at(i);

        if(entry->objectType()==FileListingEntry::DATA_OBJECT && QString::compare(entry->pathOrName(),fileName)==0){
            return true;
         }
    }
    return false;
}

/**
 * Auxiliary method to create a file to be used by the tests.
 * @brief TestDataObjectClient::createTextFiles Auxiliary method to create a file to be used by the tests.
 * @param baseFileName the name of the file
 * @return true if the file was created
 */
bool TestDataObjectClient::createTextFiles(QString baseFileName, int size){
    QString localFilePathName(QDir::currentPath()+"/"+baseFileName);
    if(fileExistsLocal(localFilePathName)){
        return true;
    }

    /* Try and open a file for output */
    QFile localFilePath(QDir::cleanPath(localFilePathName));
    localFilePath.open(QIODevice::WriteOnly);
    if(!localFilePath.isOpen()){
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
 * Verifies if a file exists locally
 * @brief TestDataObjectClient::fileExistsLocal  Verifies if a file exists locally
 * @param fileName the name of the file
 * @return true if the file exists
 */
bool TestDataObjectClient::fileExistsLocal(QString & fileName){
    QFile localFilePath(fileName);

    if (!localFilePath.open(QIODevice::ReadOnly) || !localFilePath.exists()){
        return false;
    }
    return true;
}

/**
 * Deletes a file locally
 * @brief TestDataObjectClient::deleteFiles  Deletes a file locally
 * @param fileName the name of the file
 * @return true if the file has been deleted
 */
bool TestDataObjectClient::deleteFiles(QString &fileName){
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
 * @brief TestDataObjectClient::getFormatedTime Auxiliary method to be used in performance tests, it is, to return milliseconds converted to hours, minutes and seconds.
 * @param milliseconds how long time in milliseconds
 * @return the formated String representing the time
 */
QString TestDataObjectClient::getFormatedTime(int milliseconds){
    int seconds    = ((int) milliseconds /1000)%60 ;
    int minutes    = ((((int) milliseconds /1000) - seconds)/60) %60;
    int hours      = (((((int) milliseconds /1000) - seconds)/60) - minutes)/60;

    QString fullTime(QString::number(hours)+" h: "+QString::number(minutes)+" m: "+QString::number(seconds)+" s");

    return fullTime;
}
