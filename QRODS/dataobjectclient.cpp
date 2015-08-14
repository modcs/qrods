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


#include "dataobjectclient.h"
#include "callcontroller.h"
#include <QUrl>
#include <QNetworkReply>
#include <QByteArray>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

/**
 * This is a constructor for DataObjectClient class.
 *
 * @brief DataObjectClient::DataObjectClient Constructor for DataObjectClient class.
 * @param bURL a string that represents the base URL.
 * @param parent the parent Qt widget.
 */
DataObjectClient::DataObjectClient(QString &bURL, QString user, QString pass, QObject *parent) :
    AbstractHTTPClient(bURL, user, pass, parent)
{
    connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
}

/**
 * Removes a data object.
 *
 * @brief DataObjectClient::removeDataObject Removes a data object.
 * @param path a string that represents the path of the object to be removed.
 * @param force a boolean for ensuring the remove operation.
 */
void DataObjectClient::removeDataObject(QString &path, bool force)
{

    callController.waitForResource();

    QString url = baseURL() + path;

    if(force){
        url += "?force=true";
    }

    doDelete(url);

    emit(modelChanged());
}

/**
 * Adds a collection metadata.
 *
 * @brief DataObjectClient::addCollectionMetadata Adds a collection metadata.
 * @param path a string that represents the path for the collection metadata to be added.
 * @param entry entry that represents the MetadataEntry.
 */
void DataObjectClient::addCollectionMetadata(QString &path, MetadataEntry &entry){
    doMetadataOperation(path, entry, ADD_METADATA);
}


void DataObjectClient::deleteDataObjectMetadata(QString &path, MetadataEntry & entry){
    doMetadataOperation(path, entry, DELETE_METADATA);
}

/**
 * Gets data object metadata.
 *
 * @brief DataObjectClient::getDataObjectMetadata Gets metadata.
 * @param path a string that represents the path of the metadata.
 * @return returns a QList composed of MetadataEntry entities.
 */
QList<MetadataEntry*>* DataObjectClient::getDataObjectMetadata(QString &path){
     QList<MetadataEntry*>* list = new QList<MetadataEntry*>();

     QString url = baseURL() + path + "/metadata";

     QByteArray arr = doGet(url);

     QJsonDocument jsonResponse = QJsonDocument::fromJson(arr);
     QJsonObject jsonObject = jsonResponse.object();
     QJsonArray children = jsonObject["metadataEntries"].toArray();

     for(int i = 0; i < children.count(); i++){
         QJsonObject child = children.at(i).toObject();

         QString attribute = child["attribute"].toString();
         QString value = child["value"].toString();
         QString unit = child["unit"].toString();

         MetadataEntry* entry = new MetadataEntry(attribute, value, unit);

         list->append(entry);
     }

     return list;
}

/**
 * Gets data object metadata asynchronously.
 *
 * @brief DataObjectClient::getDataObjectMetadataAsync Gets data object.
 * @param path the path that represents the metadata object.
 */
void DataObjectClient::getDataObjectMetadataAsync(QString &path){
    QString query("/metadata");
    QString url = baseURL() + path + query;
    QNetworkReply* reply = doAsyncGet(url);

    QVariant variant("getDataObjectMetadataAsync");
    reply->setProperty("method", variant);
}

/**
 * Confirms that the operation getDAtaObjectMetadataAsync() has finished.
 *
 * @brief DataObjectClient::replyFinished Confirms that the operation getDAtaObjectMetadataAsync() has finished.
 * @param reply reply that is a QNetworkReply.
 */
void DataObjectClient::replyFinished(QNetworkReply *reply){
    QString str = reply->property("method").toString();

    if(str == "getDataObjectMetadataAsync"){
        getDataObjectMetadataFinished(reply);
    }
}

/**
 * Finishes the data object metadata async operation.
 *
 * @brief DataObjectClient::getDataObjectMetadataFinished Finishes the data object metadata async operation.
 * @param reply a reply that is a QNetworkReply.
 */
void DataObjectClient::getDataObjectMetadataFinished(QNetworkReply *reply){
    QList<MetadataEntry*>* list = new QList<MetadataEntry*>();

    QByteArray arr = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(arr);
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray children = jsonObject["metadataEntries"].toArray();

    for(int i = 0; i < children.count(); i++){
        QJsonObject child = children.at(i).toObject();

        QString attribute = child["attribute"].toString();
        QString value = child["value"].toString();
        QString unit = child["unit"].toString();

        MetadataEntry* entry = new MetadataEntry(attribute, value, unit);

        list->append(entry);
    }

    emit( metaData(list) );
}

/**
 * Adds a collection metadata.
 *
 * @brief DataObjectClient::addCollectionMetadata Adds a collection metadata.
 * @param path a string that represents the path for the collection metadata to be added.
 * @param entry entry that represents the MetadataEntry.
 */
void DataObjectClient::doMetadataOperation(QString &path, MetadataEntry &entry, MetadataOperation op){
    QJsonObject entryJson;

    entryJson["attribute"] = entry.attribute();
    entryJson["value"] = entry.value();
    entryJson["unit"] = entry.unit();

    QJsonArray entries;
    entries.append(entryJson);

    QJsonObject jsonObj;

    jsonObj["metadataEntries"] = entries;

    QJsonDocument doc(jsonObj);

    QString url = baseURL() + path + "/metadata";

    QByteArray arr = doc.toJson();

    QByteArray bar;

    switch(op){
    case ADD_METADATA:
        bar = doPut(url, arr);        
        break;
    case DELETE_METADATA:
        bar = doPost(url, arr);
        break;
    }

    //metadata added successfully, update datamodel
    if(bar.size()){
        QString attr(entry.attribute());
        QString val(entry.value());
        QString unit(entry.unit());

        MetadataEntry* e = new MetadataEntry(attr, val, unit);

        switch(op){
        case ADD_METADATA:
            emit(entryAdded(e));
            break;
        case DELETE_METADATA:
            emit(entryRemoved(e));
            break;
        }
    }
}
