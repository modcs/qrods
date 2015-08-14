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


#include "collectionclient.h"
#include "filelistingentry.h"
#include <QUrl>
#include <QNetworkReply>
#include <QByteArray>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>
#include "jsonparser.h"
#include "xmlparser.h"
#include "callcontroller.h"

/**
 * This is a constructor for CollectionClient class.
 *
 * @brief CollectionClient::CollectionClient Constructor method.
 * @param bURL the base URL.
 * @param parent the parent Qt widget.
 */
CollectionClient::CollectionClient(QString &bURL, QString user, QString pass, QObject *parent) :
    AbstractHTTPClient(bURL, user, pass, parent)
{

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    map["UNKNOWN"] = FileListingEntry::UNKNOWN;
    map["DATA_OBJECT"] = FileListingEntry::DATA_OBJECT;
    map["COLLECTION"] = FileListingEntry::COLLECTION;
    map["UNKNOWN_FILE"] = FileListingEntry::UNKNOWN_FILE;
    map["LOCAL_FILE"] = FileListingEntry::LOCAL_FILE;
    map["LOCAL_DIR"] = FileListingEntry::LOCAL_DIR;
    map["NO_INPUT"] = FileListingEntry::NO_INPUT;

    _hasMorePages = false;

    setXMLParser();
}

/**
 * Gets a collection data asynchronously.
 *
 * @brief CollectionClient::getCollectionDataAsync Asynchronously gets a collection data.
 * @param path the path that represents the specified collection data.
 */
void CollectionClient::getCollectionDataAsync(QString &path){
    QString query("?listing=true");

    QString url = baseURL() + path + query;

    QNetworkReply* reply = doAsyncGet(url);

    QVariant variant("getCollectionDataAsync");
    reply->setProperty("method", variant);
}

/**
 * Gets a collection data through a lazyloading method.
 *
 * @brief CollectionClient::getCollectionDataLazy Gets a collection data through a lazyloading method.
 * @param path the path that represents the specified collection data.
 */
void CollectionClient::getCollectionDataLazy(QString &path){
    _offset = 0;
    _path = path;
    _hasMorePages = false;

    //FIXME - This parameter cannot be fixed (data, collections or both). It should
    //be user-definable
    QString type("both");

    getCollectionDataPaged(path, type, _offset);
}

/**
 * Gets a collection data through a lazyloading method by a FileListingEntry.
 *
 * @brief CollectionClient::getCollectionDataLazy Gets a collection data by a FileListingEntry.
 * @param entry the FileListingEntry.
 */
void CollectionClient::getCollectionDataLazy(FileListingEntry* entry){
    entry->setDataObjectsOffset(0);
    entry->setCollectionsOffset(0);

    entry->setHasMoreCollections(true);
    entry->setHasMoreDataObjects(true);

    QString type("collections");

    QString path = entry->pathOrName();

    _collections[path] = entry;

    getCollectionDataPaged(entry, type, 0);
}

/**
 * Gets the next page of a collection data.
 *
 * @brief CollectionClient::getNextPage Gets next page.
 */
void CollectionClient::getNextPage(){

    if( _isFetching ){
        return;
    }

    QString type("data");

    _isFetching = true;

    _hasMorePages = false;

    getCollectionDataPaged(_path, type, _offset);
}

/**
 * Gets the next page of a collection data by a FileListingEntry.
 *
 * @brief CollectionClient::getNextPage Gets next page by a FileListingEntry.
 * @param entry the entry that represents a FileListingEntry.
 */
void CollectionClient::getNextPage(FileListingEntry* entry){
    if( _isFetching ){
        return;
    }      

    QString data("data");
    QString collections("collections");

    if(entry->hasMoreCollections()){
        getCollectionDataPaged(entry, collections, entry->collectionsOffset());
    }else if(entry->hasMoreDataObjects()){
        getCollectionDataPaged(entry, data, entry->dataObjectsOffset());
    }
}

/**
 * Method that peforms a check to identify or not next pages.
 *
 * @brief CollectionClient::hasMorePages Identify or not next pages.
 * @return returns true if there are next pages.
 */
bool CollectionClient::hasMorePages(){
    return _hasMorePages;
}

/**
 * Gets a collection data in form of pages.
 *
 * @brief CollectionClient::getCollectionDataPaged Gets a collection data in form of pages.
 * @param path the path that represents the specified collection.
 * @param type a string that represents the type.
 * @param offset an integer representing the offset.
 */
void CollectionClient::getCollectionDataPaged(QString &path, QString &type, int offset){

    QString query("?listing=true&offset=");

    QString strOff = QString::number(offset);
    query.append(strOff);
    query.append("&listType=");
    query.append(type);

    QString url = baseURL() + path + query;

    QNetworkReply* reply = doAsyncGet(url);


    QVariant variant("getCollectionDataPaged");
    reply->setProperty("method", variant);
}

/**
 * Gets a collection data in form of pages from a FileListingEntry.
 *
 * @brief CollectionClient::getCollectionDataPaged Gets a collection data in form of pages from a FileListingEntry.
 * @param entry the entry that is a FileListingEntry.
 * @param type a string that is the type.
 * @param offset an integer that is the offset.
 */
void CollectionClient::getCollectionDataPaged(FileListingEntry* entry, QString &type, int offset){

    QString query("?listing=true&offset=");

    QString strOff = QString::number(offset);
    query.append(strOff);
    query.append("&listType=");
    query.append(type);

    QString url = baseURL() + entry->pathOrName() + query;

    QNetworkReply* reply = doAsyncGet(url);


    QVariant variant("getCollectionDataPagedE");
    reply->setProperty("method", variant);

    QVariant vtype(type);
    reply->setProperty("type", vtype);

    QVariant vpath(entry->pathOrName());
    reply->setProperty("path", vpath);
}

/**
 * Adds a collection.
 *
 * @brief CollectionClient::addCollection Adds a collection.
 * @param path a string that represents the path in which a collection will be added.
 */
void CollectionClient::addCollection(QString &path){
    callController.waitForResource();

    QString url = baseURL() + path;

    QByteArray bar;
    doPut(url, bar);

    emit(modelChanged());
}

/**
 * Removes a collection.
 *
 * @brief CollectionClient::removeCollection Removes a collection.
 * @param path a string that represents the path of the collection to be removed.
 */
void CollectionClient::removeCollection(QString &path){
    callController.waitForResource();

    QString url = baseURL() + path + "?force=true";
    doDelete(url);

    emit(modelChanged());
}

/**
 * Slot that is fired when getCollectionDataAsync() finishes.
 *
 * @brief CollectionClient::replyFinished Comfirms that the getCollectionData() method has finished.
 * @param reply a QNetworkReply.
 */
void CollectionClient::replyFinished(QNetworkReply *reply){
    QString str = reply->property("method").toString();

    if(str == "getCollectionDataAsync"){
        getCollectionDataFinished(reply);

    } else if( str == "getCollectionDataPagedE"){
        getCollectionDataPagedFinished(reply);
    }
}

/**
 * Comfirms that all collection data has been received.
 *
 * @brief CollectionClient::getCollectionDataFinished Comfirms that all collection data has been received.
 * @param reply a reply that represents the QNetworkReply.
 */
void CollectionClient::getCollectionDataFinished(QNetworkReply *reply){

    if(reply->error() != QNetworkReply::NoError){
        emit( collectionData(NULL) );
        return;
    }

    QList<FileListingEntry*> *list = new QList<FileListingEntry*>();

    QByteArray arr = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(arr);

    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray children = jsonObject["children"].toArray();

    for(int i = 0; i < children.count(); i++){
        QJsonObject child = children.at(i).toObject();

        QString pathOrName = child["pathOrName"].toString();
        QString parentPath = child["parentPath"].toString();
        QString objectType = child["objectType"].toString();
        long long int createdAt = child["createdAt"].toString().toLongLong();
        long long int modifiedAt = child["modifiedAt"].toString().toLongLong();
        long long int dataSize = child["dataSize"].toString().toLongLong();
        QString ownerName = child["ownerName"].toString();
        QString ownerZone = child["ownerZone"].toString();
        int id = child["id"].toInt();

        FileListingEntry *entry = new FileListingEntry(this);

        entry->setPathOrName(pathOrName);
        entry->setParentPath(parentPath);
        entry->setObjectType(map[objectType]);
        entry->setCreatedAt(createdAt);
        entry->setModifiedAt(modifiedAt);
        entry->setDataSize(dataSize);
        entry->setOwnerName(ownerName);
        entry->setOwnerZone(ownerZone);
        entry->setId(id);

        list->append(entry);
    }

    emit( collectionData(list) );
}

/**
 * Comfirms that all pages of a collection has been received.
 *
 * @brief CollectionClient::getCollectionDataPagedFinished Comfirms that all pages of a collection has been received.
 * @param reply a reply that is a QNetworkReply.
 */
void CollectionClient::getCollectionDataPagedFinished(QNetworkReply *reply){

    if(reply->error() != QNetworkReply::NoError){
        emit( getPageData(NULL, -1, -1) );
        return;
    }    

    QString path = reply->property("path").toString();
    FileListingEntry* parent = _collections[path];
    QString type = reply->property("type").toString();

    bool hasMorePages = parser->parseResult(parent, reply);

    _isFetching = false;

    if(type == "collections"){
        if(!hasMorePages){
            getNextPage(parent);
        }
    }

    int beginIndex = 0;
    int endIndex = 0;

    if(parent->children()->size() > 0){
        endIndex = parent->children()->last()->row();
    }

    if(type == "data"){
        emit( getPageData(parent, beginIndex, endIndex) );
    }
}

/**
 * Sets a JSONParser.
 *
 * @brief CollectionClient::setJSONParser Sets a JSONParser.
 */
void CollectionClient::setJSONParser(){
    if(parser){
        delete parser;
    }

    parser = new JSONParser(this);
    QString type("application/json");
    setContentType(type);
}

/**
 * Sets a XMLParser.
 *
 * @brief CollectionClient::setXMLParser Sets a XMLParser.
 */
void CollectionClient::setXMLParser(){
    if(parser){
        delete parser;
    }

    parser = new XMLParser(this);
    QString type("application/xml");
    setContentType(type);
}
