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


#include "qrods_p.h"

/**
 * Constructor of QRODSPrivate.
 *
 * @brief QRODSPrivate::QRODSPrivate constructor.
 * @param qrods
 */
QRODSPrivate::QRODSPrivate(QRODS *qrods){
    columns[FileListingEntry::PARENT_PATH]  = QString::fromStdString("Parent path");
    columns[FileListingEntry::PATH_OR_NAME]  = QString::fromStdString("Name");
    columns[FileListingEntry::SPECIAL_OBJECT_PATH]  = QString::fromStdString("Special object path");
    columns[FileListingEntry::OBJECT_TYPE]  = QString::fromStdString("Type");
    columns[FileListingEntry::CREATED_AT]  = QString::fromStdString("Created at");
    columns[FileListingEntry::MODIFIED_AT]  = QString::fromStdString("Modified at");
    columns[FileListingEntry::DATA_SIZE]  = QString::fromStdString("Size");
    columns[FileListingEntry::OWNER_NAME]  = QString::fromStdString("Owner");
    columns[FileListingEntry::OWNER_ZONE]  = QString::fromStdString("Zone");
    columns[FileListingEntry::ID]  = QString::fromStdString("Id");
    columns[FileListingEntry::IS_COLLECTION]  = QString::fromStdString("Is collection");

    visibleColumns << FileListingEntry::PATH_OR_NAME << FileListingEntry::PARENT_PATH <<  FileListingEntry::OBJECT_TYPE;

    this->qrods = qrods;
    this->_version = QObject::tr(QRODS_VERSION);
}

/**
 * Sets the IRODS user.
 *
 * @brief QRODSPrivate::setUser sets the user.
 * @param user a string that represents the user.
 */
void QRODSPrivate::setUser(QString &user)
{
    this->_user = user;
}

/**
 * Sets the IRODS password associated with the user.
 *
 * @brief QRODSPrivate::setPassword sets the password.
 * @param password a string that represents the password.
 */
void QRODSPrivate::setPassword(QString &password)
{
    this->_password = password;
}

/**
 * Sets the IRODS host.
 *
 * @brief QRODSPrivate::setHost sets the host.
 * @param host a string that represents the host.
 */

void QRODSPrivate::setHost(QString &host)
{
    this->_host = host;
}

/**
 * Sets the Port.
 *
 * @brief QRODSPrivate::setPort sets the Port.
 * @param port an integer that represents the port to be used for communication with iRODS system.
 */
void QRODSPrivate::setPort(int port)
{
    this->_port = port;
}

/**
 * Returns the QRODS Version.
 *
 * @brief QRODSPrivate::getQRODSVersion gets QRODS version.
 * @return the QRODS version.
 */
QString& QRODSPrivate::getQRODSVersion(){
    return this->_version;
}

/**
 * Returns the iRODS user.
 *
 * @brief QRODSPrivate::user gets user.
 * @return the iRODS user.
 */
QString& QRODSPrivate::user()
{
    return this->_user;
}

/**
 * Returns the password.
 *
 * @brief QRODSPrivate::password returns the password.
 * @return the password.
 */
QString& QRODSPrivate::password()
{
    return this->_password;
}

/**
 * Returns the host.
 *
 * @brief QRODSPrivate::host returns the host.
 * @return the host.
 */
QString& QRODSPrivate::host()
{
    return this->_host;
}

/**
 * Returns the port.
 *
 * @brief QRODSPrivate::port gets the port.
 * @return the port
 */
int QRODSPrivate::port()
{
    return this->_port;
}

/**
 * This method adds a collection according to the path received as parameter.
 *
 * @brief QRODSPrivate::addCollection adds a collection.
 * @param path a string parameter that represents the path where the collection will be created.
 */
void QRODSPrivate::addCollection(QString &path)
{
    this->collectionClient->addCollection(path);
}

/**
 * This method removes the collection passed as parameter.
 *
 * @brief QRODSPrivate::removeCollection removes a collection.
 * @param path a string that represents the path of the collection to be removed.
 */
void QRODSPrivate::removeCollection(QString &path)
{
    this->qrods->beginResetModel();
    this->collectionClient->removeCollection(path);
}

/**
 * This method uploads a file from the local path to the remote path specified as parameters.
 *
 * @brief QRODSPrivate::uploadFile uploads a file.
 * @param remotePath a string that represents the path on the iRODS system.
 * @param localPath a string that represents the source path.
 */
void QRODSPrivate::uploadFile(QString &remotePath, QString &localPath)
{
    this->fileClient->uploadFile(remotePath, localPath);
}

/**
 * This method download a file located in remotePath to
 * the localPath
 *
 * @brief QRODSPrivate::getFile get a file.
 * @param remotePath a string that represents the path on the iRODS system.
 * @param localPath a string that represents the local path.
 */
void QRODSPrivate::getFile(QString &remotePath, QString &localPath)
{
    this->fileClient->getFile(remotePath, localPath);
}

/**
 * This method gets a list of metadata related to a specified remote object.
 *
 * @brief QRODSPrivate::getDataObjectMetadata gets the object data of a metadata.
 * @param path a string that represents the object path.
 * @return a list of object data of the metadata entry specfied as parameter.
 */
QList<MetadataEntry*>* QRODSPrivate::getDataObjectMetadata(QString &path)
{
    return this->dataClient->getDataObjectMetadata(path);
}

/**
 * This method adds a metadata entry to a remote object specified in path.
 *
 * @brief QRODSPrivate::addCollectionMetadata adds a collection to a metadata.
 * @param path a string that represents the path of the collection to be added.
 * @param map represents the metadata entry.
 */
void QRODSPrivate::addCollectionMetadata(QString &path, MetadataEntry &entry)
{
    this->dataClient->addCollectionMetadata(path, entry);
}

/**
 * This method deletes a metada entry from a remote object specified in path.
 *
 * @brief QRODSPrivate::deleteCollectionMetadata
 * @param path
 * @param entry
 */
void QRODSPrivate::deleteCollectionMetadata(QString &path, MetadataEntry &entry)
{
    this->dataClient->deleteDataObjectMetadata(path, entry);
}

/**
 * List the collection contents by using a load lazing approach.
 *
 * @brief QRODSPrivate::getCollectionDataLazy List the collection
 * contents by using a load lazing approach.
 * @param entry The iRODS object descriptor.
 */
void QRODSPrivate::getCollectionDataLazy(FileListingEntry* entry) const
{
    this->collectionClient->getCollectionDataLazy(entry);
}

/**
 * This method removes a data object specified as parameter.
 *
 * @brief QRODSPrivate::removeDataObject
 * @param path a string that represents the object to be removed.
 * @param force a boolean to force the remove operation.
 */
void QRODSPrivate::removeDataObject(QString &path, bool force)
{
    this->dataClient->removeDataObject(path, force);
}

/**
 * Sets the path of a remote object associated with the
 * QRODS metadata model.
 *
 * @brief QRODSPrivate::setDataPath Sets the path of a remote
 * object associated with the QRODS metadata model.
 * @param dataObj a data object.
 */
void QRODSPrivate::setDataPath(QString &dataObj)
{
    this->dataModel->setDataPath(dataObj);
}

/**
 * This method is called when a new page is requested by
 * lazy loading collection listing approach.
 * @brief QRODSPrivate::getNextPage
 * @param entry
 */
void QRODSPrivate::getNextPage(FileListingEntry* entry) const
{
    this->collectionClient->getNextPage(entry);
}

/**
 * This method returns a QRODS metadata model.
 *
 * @brief QRODSPrivate::getDataModel returns a QRODS.
 * @return a QRODS data model.
 */
QMetadataModel *QRODSPrivate::getDataModel()
{
    return this->dataModel;
}

/**
 * This method connects to the server in the iRODS zone specified by parameter.
 *
 * @brief QRODSPrivate::connectToServer connets to a server.
 * @param path a string that represents the iRODS zone.
 */
bool QRODSPrivate::connectToServer(QString path, bool secureHttp)
{
    QString baseURL1;

    if ( secureHttp ){
        baseURL1.append("https://");
    }
    else{
        baseURL1.append("http://");
    }

    baseURL1.append(this->host())
                   .append(":")
                   .append(QString::number(this->port()));

    QString url1 = baseURL1;

    this->collectionClient = new CollectionClient(url1.append("/irods-rest/rest/collection/"), this->user(), this->password(), this->qrods);

    QString infoURL = baseURL1 + "/irods-rest/rest/server";

    this->serverClient = new ServerInfoClient(infoURL, this->user(), this->password(), this->qrods);

    url1 = baseURL1;

    this->fileClient = new FileContentsClient(url1.append("/irods-rest/rest/fileContents/"), this->user(), this->password(), this->qrods);

    url1 = baseURL1;

    this->dataClient = new DataObjectClient(url1.append("/irods-rest/rest/dataObject/"), this->user(), this->password(), this->qrods);

    this->dataModel = new QMetadataModel();
    this->dataModel->getPrivateInstance()->setDataObjectClient(this->dataClient);

    this->_rootNode = new FileListingEntry(this->qrods);
    this->_rootNode->setPathOrName(path);
    this->_rootNode->setObjectType(FileListingEntry::COLLECTION);

    QObject::connect(this->collectionClient, SIGNAL(getPageData(FileListingEntry*, int, int)),
                this->qrods, SLOT(getPageData(FileListingEntry*, int, int)));

    QObject::connect(this->fileClient, SIGNAL(modelChanged()),
                this->qrods, SLOT(modelChanged()));

    QObject::connect(this->collectionClient, SIGNAL(modelChanged()),
                this->qrods, SLOT(modelChanged()));

    QObject::connect(this->dataClient, SIGNAL(modelChanged()),
                this->qrods, SLOT(modelChanged()));

    QObject::connect(this->dataClient, SIGNAL(entryAdded(MetadataEntry*)),
            this->dataModel, SLOT(entryAdded(MetadataEntry*)));

    QObject::connect(this->dataClient, SIGNAL(entryRemoved(MetadataEntry*)),
            this->dataModel, SLOT(entryRemoved(MetadataEntry*)));

    //Check iRODS Compatibility
    if(this->serverClient->loadServerInfo()){

        if(this->serverClient->relVersion().left(7) == "rods4.1"){
            this->collectionClient->setXMLParser();
        }else if(this->serverClient->relVersion().left(7) == "rods4.0"){
            this->collectionClient->setJSONParser();
        }

        this->qrods->beginResetModel();
        this->collectionClient->getCollectionDataLazy(this->_rootNode);

        return true;
    }
    else
    {
        return false;
    }
}
