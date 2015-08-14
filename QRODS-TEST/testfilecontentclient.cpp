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
#include "qrods.h"
#include "collectionclientsync.h"
#include <QDebug>
#include <QList>
#include <QFileDialog>
#include <QSettings>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

QRODS *model ;
QString collecUrl;


QString largeTestFilesDir = QString("testFiles");
QString files_10MB_directory = QString("files_10MB");
QString files_100MB_directory = QString("files_100MB");
QString files_1GB_directory = QString("files_1GB");
QString files_10GB_directory = QString("files_10GB");
QString files_100GB_directory = QString("files_100GB");

QString deployRootPathTestAux;

bool fileExistsRemote(QString & collection, QString &fileName);
static QString pathTestCollection;
static QString pathTestCollectionfiles_10MB;
static QString pathTestCollectionfiles_100MB;
static QString pathTestCollectionfiles_1GB;
static QString pathTestCollectionfiles_10GB;
static QString pathTestCollectionfiles_100GB;


TestFileContentClient::TestFileContentClient(QString &newHost, QString &newport, QString &newUser, QString &newPassword, bool isSecureHttps, QString &_testFile, QVector<QString> _testFileNames, QString deployRootPathTestArg){
    testFile = QString(_testFile);
    testFileNames= _testFileNames;
    deployRootPathTestAux = deployRootPathTestArg;
    host = QString (newHost);
    port = QString(newport);
    user = QString(newUser);
    password = QString(newPassword);
    secureHttps = isSecureHttps;
    if(isSecureHttps)
        hostFull = QString("https://"+host);
    else
        hostFull = QString("http://"+host);

    objectsBefore;
    objectsAfter;

    collecUrl = QString(hostFull+":"+port+"/irods-rest/rest/collection/");
    path = QString("/tempZone/home/rods");
    pathTestCollection = QString("/tempZone/home/test/alpha");
    pathTestCollectionfiles_10MB = QString(pathTestCollection + "/" + "testFiles/files_10MB");
    pathTestCollectionfiles_100MB = QString(pathTestCollection + "/" + "testFiles/files_100MB");
    pathTestCollectionfiles_1GB = QString(pathTestCollection + "/" + "testFiles/files_1GB");
    pathTestCollectionfiles_10GB = QString(pathTestCollection + "/" + "testFiles/files_10GB");
    pathTestCollectionfiles_100GB = QString(pathTestCollection + "/" + "testFiles/files_100GB");

    model = new QRODS();
    pathToTheFile = QString(QDir::cleanPath(pathTestCollection+"/"+testFile));
    localPath = QString(QDir::cleanPath(QDir::currentPath()+"/"+testFile));
    anotherPathToTheFile = QString(QDir::cleanPath("tempZone/home/test/alpha/"+testFile)); // FIX ME, foi preciso criar outra variavel para passar o "path" sem uma barra dobrada " // "
}

void TestFileContentClient::initTestCase() {
    model = new QRODS();
    model->setUser(user);
    model->setHost(host);
    model->setPort(port.toInt());
    model->setPassword(password);
    model->connectToServer(path, secureHttps);

    // Remove previous "test" collections
    model->removeCollection(pathTestCollection);
}

void TestFileContentClient::cleanupTestCase() {
}

void TestFileContentClient::init() {

    /* A sample file: log.txt */
    if(!createTextFiles(testFile,1)){

    }
    model->addCollection(pathTestCollection);


    // Creating test Collections for larger file uploads

    model->addCollection(pathTestCollectionfiles_10MB);
    model->addCollection(pathTestCollectionfiles_100MB);
    model->addCollection(pathTestCollectionfiles_1GB);
    model->addCollection(pathTestCollectionfiles_10GB);
    model->addCollection(pathTestCollectionfiles_100GB);


    objectsBefore = 0;
    objectsAfter = 0;
    createTestFolders(); //locally


}

void TestFileContentClient::cleanup() {
    QString correctPath(pathTestCollection.mid(1));
    model->removeCollection(correctPath);
    //Delete the local tests folder
    removeDir(largeTestFilesDir);
}

/**
 * Test to fetch a file from the iRODS
 * @brief TestFileContentClient::testGetFile Test to fetch a file from the iRODS
 */
void TestFileContentClient::testGetFile(){
   // QSKIP("SKIPPING this test.");

    QString localFile(QDir::cleanPath(QDir::currentPath()+"/"+"newLog.txt"));
    QVERIFY(fileExistsLocal(localFile) == false);

    model->uploadFile(pathToTheFile, localPath);

    bool flag=false;
    int counter = 0;

    do{
        flag=fileExistsRemote(pathTestCollection,testFile);
        counter += 3500;
        qDebug() << "\tChecking if the file is on the remothe path..";
    }while((flag==false) || (counter>120000));
    model->getFile(anotherPathToTheFile, localFile);

    // It's necessary to wait some seconds before trying to access the file on the local disk.
    QTest::qWait(2000);


    QVERIFY(fileExistsLocal(localFile) == true);
    deleteLocalFile(localFile);

}

/**
 * Upload 5 different size files.
 * @brief TestFileContentClient::testUploadDifferentSizeFiles Upload 5 different size files.
 */
void TestFileContentClient::testUploadDifferentSizeFiles(){
    QSKIP("SKIPPING this test.");

    int sizes [5] = {1800000, 18000000, 162000000, 1620000000, 16200000000};

    QString names [5] = {"10MB_", "100MB_", "1GB_", "10GB_", "100GB_"};

    for (int var = 0; var < 5; ++var) {
        QTime myTimer;
        myTimer.start();
        uploadAndAssertLargeFilesAux(1, files_10MB_directory, sizes[var],names[var],pathTestCollectionfiles_10MB);

    }

}

/**
 * Uploads a file of 1.3 KB and verifies whether the file was uploaded.
 * @brief TestFileContentClient::testUploadOnlyOneSmallFile Uploads an small file and asserts its remote existence.
 */
void TestFileContentClient::testUploadOnlyOneSmallFile(){
    QSKIP("SKIPPING this test.");
    uploadAndAssertLargeFilesAux(1, files_10MB_directory, 180,"smallFile_",pathTestCollectionfiles_10MB);
}

/**
 * Uploads 10000 files of 10 MB and verifies whether the files were uploaded.
 * @brief TestFileContentClient::testUploadOnlyOneSmallFile Uploads 10000 files of 10 MB and asserts its remote existence.
 */
void TestFileContentClient::testUpload_10000Files_10MB(){
    QSKIP("SKIPPING this test.");
    uploadAndAssertLargeFilesAux(10000, files_10MB_directory, 1800000,"10MB_",pathTestCollectionfiles_10MB);
}

/**
 * Uploads 1000 files of 100 MB and verifies whether the files were uploaded.
 * @brief TestFileContentClient::testUploadOnlyOneSmallFile Uploads 1000 files of 100 MB and asserts its remote existence.
 */
void TestFileContentClient::testUpload_1000Files_100MB(){
    QSKIP("SKIPPING this test.");
    uploadAndAssertLargeFilesAux(1000, files_100MB_directory, 18000000,"100MB_",pathTestCollectionfiles_100MB);
}

/**
 * Uploads 100 files of 1 GB and verifies whether the files were uploaded.
 * @brief TestFileContentClient::testUploadOnlyOneSmallFile Uploads 100 files of 1 GB and asserts its remote existence.
 */
void TestFileContentClient::testUpload_100Files_1GB(){
    QSKIP("SKIPPING this test.");
    uploadAndAssertLargeFilesAux(100, files_1GB_directory, 162000000,"1GB_", pathTestCollectionfiles_1GB);
}

/**
 * Uploads 10 files of 10 GB and verifies whether the files were uploaded.
 * @brief TestFileContentClient::testUploadOnlyOneSmallFile Uploads 10 files of 10 GB and asserts its remote existence.
 */
void TestFileContentClient::testUpload_10File_10GB(){
    QSKIP("SKIPPING this test.");
    uploadAndAssertLargeFilesAux(10, files_10GB_directory, 1620000000,"10GB_", pathTestCollectionfiles_10GB);
}

/**
 * Uploads 1 file of 100 GB and verifies whether the files were uploaded.
 * @brief TestFileContentClient::testUploadOnlyOneSmallFile Uploads 1 file of 100 GB and asserts its remote existence.
 */
void TestFileContentClient::testUpload_1File_100GB(){
    QSKIP("SKIPPING this test.");
    uploadAndAssertLargeFilesAux(1, files_100GB_directory, 16200000000,"100GB_", pathTestCollectionfiles_100GB);
}

/**
 * Test the upload of files with different name sizes in terms of caracteres (8,65,128,200,251).
 * @brief TestFileContentClient::testUploadFilesWithLargeNames Test the upload of files with different name sizes.
 */
void TestFileContentClient::testUploadFilesWithLargeNames(){
    QSKIP("SKIPPING this test.");
    int lengths [] = {8,65,128,200,251};
    for(int i = 0; i<5;i++){
        uploadAndAssertLargeFilesAux(1, files_10MB_directory, 180,getRandomString(lengths[i]), pathTestCollectionfiles_10MB);
    }
}


/**
 * Auxiliary method for upload a set of files.
 * @brief TestFileContentClient::testUploadOnlyOneSmallFile Auxiliary method for upload a set of files.
 * @param number the number of files to be uploaded
 * @param dirTest the local folder where the files
 * @param size the size in bytes of the file
 * @param fileNameInitials the initias fo name the file (it is added a number when generating the files)
 * @param pathTestCollection the specific path to the test collection, each size of files owns a separated collection (inside the collection named test). For example. we can have the colection "tempZone/home/test/alpha/testFiles/files_10MB", specific to the files of size 10MB.
 */
void TestFileContentClient::uploadAndAssertLargeFilesAux(int number, QString dirTest, int size, QString fileNameInitials, QString pathTestCollection){
    QString numberString = NULL;
    QString fileName = NULL;
    QString localPathDir = NULL; 
    createMultipleLargeFiles(dirTest,fileNameInitials, size, number);

    for(int i = 0; i < number ;i++){
       numberString = QVariant(i).toString();
        localPathDir = deployRootPathTestAux+"/"+largeTestFilesDir +"/"+dirTest;
        fileName = fileNameInitials +""+ numberString;
        uploadFileAux(localPathDir, pathTestCollection, fileName);
    }

}

/**
 * Auxiliary metthod to be used in performance tests, it is, to return milliseconds converted to hours, minutes and seconds.
 * @brief TestFileContentClient::getFormatedTime Auxiliary metthod to be used in performance tests, it is, to return milliseconds converted to hours, minutes and seconds.
 * @param milliseconds how long time in milliseconds
 * @return the formated String representing the time
 */
QString TestFileContentClient::getFormatedTime(int milliseconds){
    int seconds    = ((int) milliseconds /1000)%60 ;
    int minutes    = ((((int) milliseconds /1000) - seconds)/60) %60;
    int hours      = (((((int) milliseconds /1000) - seconds)/60) - minutes)/60;

    QString fullTime(QString::number(hours)+" h: "+QString::number(minutes)+" m: "+QString::number(seconds)+" s");

    return fullTime;
}


/**
 * Auxiliary method for upload only one file. It is used by method TestFileContentClient::uploadAndAssertLargeFilesAux
 * @brief TestFileContentClient::uploadFileAux Auxiliary method for upload only one file.
 * @param localdir the local folder in which the file will be loaded and uploaded in the remote iRODS
 * @param collectionPath the collection remote name used to save the corresponding file
 * @param file the uploaded file
 */
void TestFileContentClient::uploadFileAux(QString localdir, QString collectionPath, QString file){
    QString _localPath((QDir::cleanPath(localdir + "/"+ file)));
    QString remoteCollectionPath(QString(QDir::cleanPath(collectionPath+"/"+file)));

    QString anotherPath = QString(QDir::cleanPath(remoteCollectionPath));
    model->uploadFile(anotherPath, _localPath);
    bool flag=false;
    do{
        flag=fileExistsRemote(collectionPath,file);
    }while(flag==false);
    QString message("\t --- When uploading "+file);
    QVERIFY2(flag,message.toStdString().c_str());
}

/**
 * Auxiliary method to create a file to be used by the tests.
 * @brief TestFileContentClient::createTextFiles Auxiliary method to create a file to be used by the tests.
 * @param baseFileName the name of the file
 * @return true if the file was created
 */
bool TestFileContentClient::createTextFiles(QString &baseFileName){
    QString localFilePathName(QDir::currentPath()+"/"+baseFileName);
    if(fileExistsLocal(localFilePathName)){
        qDebug() << "The file already exists!!";
        return true;
    }

    /* Try and open a file for output */
    QFile localFilePath(QDir::cleanPath(localFilePathName));
    localFilePath.open(QIODevice::WriteOnly);
    if(!localFilePath.isOpen()){
        qDebug() << "There's a file or unable do create a new one.";
        return false;
    }
    /* Point a QTextStream object at the file */
    QTextStream outStream(&localFilePath);
    QString fooText("MoDCS\nEMC\niRODS\nCIn-UFPE\nCNPQ\nCapes\nFACEPE\nFADE\nGoogle");

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
 * Verifies whether one file exists at iRODS.
 * @brief TestFileContentClient::fileExistsRemote Verifies whether one file exists at iRODS.
 * @param collection the corresponding collection where the file resides.
 * @param fileName the name of the file
 * @return true if the file exists
 */
bool TestFileContentClient::fileExistsRemote(QString & collection, QString &fileName){
    CollectionClient coll(collecUrl, user, password);
    FileListingEntry* _rootNode = new FileListingEntry();
    QString tempPathTestCollection(collection);
    _rootNode->setPathOrName(tempPathTestCollection);
    _rootNode->setObjectType(FileListingEntry::COLLECTION);
    _rootNode->setHasMoreCollections(true);

    CollectionClientSync collSync(&coll);
    collSync.getCollectionDataLazy(_rootNode);
    QList<FileListingEntry*> * list = _rootNode->children();
    for(int i = 0; i<list->count();i++){
        FileListingEntry* entry = list->at(i);
        if(entry->objectType()==FileListingEntry::DATA_OBJECT && QString::compare(entry->pathOrName(),fileName)==0){
            return true;
         }
    }
    return false;
}

/**
 * Verifies how many files have in the pathTestCollection.
 * @brief TestFileContentClient::getCurrentListSize  Verifies how many files have in the pathTestCollection.
 * @return how many files have in the pathTestCollection
 */
int TestFileContentClient::getCurrentListSize()
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
 * Deletes a local file.
 * @brief TestFileContentClient::deleteLocalFile Deletes a local file.
 * @param localFilePath the file to be deleted.
 */
void TestFileContentClient::deleteLocalFile(QString & localFilePath){
    QFile localFile(localFilePath);
    if (localFile.exists()){
            localFile.remove();
    }
    localFile.close();

}

/**
 * Generates a ramdom string.
 * @brief TestFileContentClient::getRandomString Generates a ramdom string.
 * @param length the size of the string
 * @return the generated string
 */
QString TestFileContentClient::getRandomString(int length){
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = length; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}


/**
 * Deletes a local folder.
 * @brief TestFileContentClient::removeDir Deletes a local folder.
 * @param foldername the name of the folder to be deleted
 */
void TestFileContentClient::removeDir(QString foldername){

      QString foldername_full_path = deployRootPathTestAux +"/"+ foldername;

      QDir dir;
      dir.setPath(foldername_full_path);
      if (!removeDirectory(dir)) {
          qDebug() << "It was not possible to delete folder "+ foldername+".";
      }
}

/**
 * Auxiliary method used by TestFileContentClient::removeDir to delete a specific folder.
 * @brief TestFileContentClient::removeDirectory
 * @param dir the folder to be deleted
 * @return true if the folder was deleted
 */
bool TestFileContentClient::removeDirectory( QDir dir ){
    bool ok = dir.exists();
    if ( ok )
    {
        QFileInfoList entries = dir.entryInfoList( QDir::NoDotAndDotDot |
                QDir::Dirs | QDir::Files );
        foreach ( QFileInfo entryInfo, entries )
        {
            QString path = entryInfo.absoluteFilePath();
            if ( entryInfo.isDir() )
            {
                if ( ! removeDirectory( QDir( path ) ) )
                {
                    ok = false;
                    break;
                }
            }
            else
            {
                QFile file( path );
                if ( ! file.remove() )
                {
                    ok = false;
                    break;
                }
            }
        }
    }

    if ( ok && ! dir.rmdir( dir.absolutePath() ) )
        ok = false;

    return ok;
}

/**
 * Creates all the test folders for different file sizes.
 * @brief TestFileContentClient::createTestFolders Creates all the test folders for different file sizes.
 */
void TestFileContentClient::createTestFolders(){
          createFolder(largeTestFilesDir);
          createFolder(largeTestFilesDir +"/"+files_10MB_directory);
          createFolder(largeTestFilesDir +"/"+files_100MB_directory);
          createFolder(largeTestFilesDir +"/"+files_1GB_directory);
          createFolder(largeTestFilesDir +"/"+files_10GB_directory);
          createFolder(largeTestFilesDir +"/"+files_100GB_directory);


    }

/**
 * Auxiliary method to create one local folder.
 * @brief TestFileContentClient::createFolder Auxiliary method to create one local folder.
 * @param folder the folder to be created
 */
void TestFileContentClient::createFolder(QString folder){
        if (!QDir(folder).exists()) {
            QDir().mkdir(folder);
        }
    }

/**
 * Creates a set of local files.
 * @brief TestFileContentClient::createMultipleLargeFiles Creates a set of local files.
 * @param subDir the local folder
 * @param fileNameInitials the inicial names for each file
 * @param size the size in bytes to the files
 * @param number the quantity of files to be created
 *
 */
void TestFileContentClient::createMultipleLargeFiles(QString subDir, QString fileNameInitials, int size, int number){

    QString fileName = NULL;
    QString numberString = NULL;
    for(int i = 0; i < number; i++){

        numberString = QVariant(i).toString();
        fileName = largeTestFilesDir +"/"+subDir+"/"+fileNameInitials +""+ numberString;
        if(!  createTextFiles( fileName,size)){
          qDebug() << "File "<< fileName << " has not been created!";
        }

    }

    QDir Dir(largeTestFilesDir +"/"+subDir);
 }

/**
 * Creates a file with an specific size
 * @brief TestFileContentClient::createTextFiles Creates a file with an specific size
 * @param baseFileName the file name
 * @param size the size in bytes of the file
 * @return true if the file was created
 */
bool TestFileContentClient::createTextFiles(QString baseFileName, int size){
    QString localFilePathName(QDir::currentPath()+"/"+baseFileName);
    if(  fileExistsLocal(localFilePathName)){
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

    if(!  fileExistsLocal(baseFileName)){
        qDebug() << "Created but I can't find it!";
        return false;
    }
    return true;

}


/**
 * Verifies if a file exists locally
 * @brief TestFileContentClient::fileExistsLocal  Verifies if a file exists locally
 * @param fileName the name of the file
 * @return true if the file exists
 */
bool TestFileContentClient::fileExistsLocal(QString & fileName){
    QFile localFilePath(fileName);

    if (!localFilePath.open(QIODevice::ReadOnly) || !localFilePath.exists()){
        localFilePath.close();
        return false;
    }
    localFilePath.close();
    return true;
}
