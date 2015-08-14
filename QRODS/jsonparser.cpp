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


#include "jsonparser.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkReply>


/**
 * This is a constructor for JSONParser class.
 *
 * @brief JSONParser::JSONParser Constructor method.
 * @param parent the parent.
 */
JSONParser::JSONParser( QObject *parent ): ResultsParser(parent)
{

}

/**
 * This is a constructor for JSONParser class.
 *
 * @brief JSONParser::~JSONParser Constructor method.
 */
JSONParser::~JSONParser()
{

}

/**
 * Method responsable for perfoming the JSONParser operations.
 *
 * @brief JSONParser::parseResult JSONParser method.
 * @param parent the parent.
 * @param reply a QNetworkReply.
 * @return returns a boolean that represents the presence of more pages.
 */
bool JSONParser::parseResult(FileListingEntry *parent, QNetworkReply *reply){
    QByteArray arr = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(arr);

    QJsonObject jsonObject = jsonResponse.object();

    QJsonArray children = jsonObject["children"].toArray();

    QString collectionName = jsonObject["collectionName"].toString();
    QString collectionParentName = jsonObject["collectionParentName"].toString();
    QString collectionOwnerName = jsonObject["collectionOwnerName"].toString();
    QString collectionOwnerZone = jsonObject["collectionOwnerZone"].toString();
    int collectionId = jsonObject["collectionId"].toInt();
    long long int collectionCreatedAt = jsonObject["createdAt"].toString().toLongLong();
    long long int collectionModifiedAt = jsonObject["modifiedAt"].toString().toLongLong();
    FileListingEntry::ObjectType collectionObjectType = FileListingEntry::COLLECTION;
    long long int collectionDataSize = 0;

    parent->setCreatedAt(collectionCreatedAt);
    parent->setDataSize(collectionDataSize);
    parent->setId(collectionId);
    parent->setModifiedAt(collectionModifiedAt);
    parent->setObjectType(collectionObjectType);
    parent->setOwnerName(collectionOwnerName);
    parent->setOwnerZone(collectionOwnerZone);
    parent->setParentPath(collectionParentName);
    parent->setPathOrName(collectionName);

    int totalrecords = 0;

    QString type = reply->property("type").toString();

    int offset = 0;

    QString data("data");

    if(type.compare(data) == 0){
        offset = parent->dataObjectsOffset();
    }else{
        offset = parent->collectionsOffset();
    }

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
        totalrecords = child["totalRecords"].toInt();

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

        parent->addChild(entry);
        entry->setParentNode(parent);

        offset++;
    }

    bool hasMorePages = offset < totalrecords;

    if(type == "collections"){
        parent->setHasMoreCollections(hasMorePages);
        parent->setCollectionsOffset(offset);
    }else{
        parent->setHasMoreDataObjects(hasMorePages);
        parent->setDataObjectsOffset(offset);
    }

    return hasMorePages;
}

