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


#include "xmlparser.h"
#include <QDomDocument>
#include <QNetworkReply>
#include <QDomNamedNodeMap>
#include <QDomAttr>

/**
 * This is a constructor for XMLParser class.
 *
 * @brief XMLParser::XMLParser Constructor.
 * @param parent the parent.
 */
XMLParser::XMLParser( QObject *parent ): ResultsParser(parent)
{

}

/**
 * This is a constructor for XMLParser class.
 *
 * @brief XMLParser::~XMLParser Constructor.
 */
XMLParser::~XMLParser()
{

}

/**
 * Method used to pass the parse reulsts.
 *
 * @brief XMLParser::parseResult parse reults.
 * @param parent the parent.
 * @param reply a QNetworkReply.
 * @return returns a boolean that inform if the FileListingEntry hasMorePages.
 */
bool XMLParser::parseResult(FileListingEntry *parent, QNetworkReply *reply){
    QByteArray arr = reply->readAll();

    QDomDocument document;
    document.setContent(arr);

    //get the root element
    QDomElement root = document.firstChildElement();
    QDomNodeList list = root.elementsByTagName("children");

    QString collectionName = root.elementsByTagName("collectionName").at(0).toElement().text();
    QString collectionParentName = root.elementsByTagName("collectionParentName").at(0).toElement().text();
    QString collectionOwnerName = root.elementsByTagName("collectionOwnerName").at(0).toElement().text();
    QString collectionOwnerZone = root.elementsByTagName("collectionOwnerZone").at(0).toElement().text();
    int collectionId = root.elementsByTagName("collectionOwnerZone").at(0).toElement().text().toInt();

    QString collectionCreatedAtS = root.elementsByTagName("createdAt").at(0).toElement().text();
    QString collectionModifiedAtS = root.elementsByTagName("modifiedAt").at(0).toElement().text();
    QDateTime collectionModifiedAtD = QDateTime::fromString( collectionModifiedAtS.mid(0,19) ,
            "yyyy-MM-ddThh:mm:ss" );
    QDateTime collectionCreatedAtD = QDateTime::fromString( collectionCreatedAtS.mid(0,19) ,
            "yyyy-MM-ddThh:mm:ss" );
    long long int collectionCreatedAt = collectionModifiedAtD.toMSecsSinceEpoch();
    long long int collectionModifiedAt = collectionCreatedAtD.toMSecsSinceEpoch();

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

    for( int i = 0; i < list.size(); i++){
        QDomElement node = list.at(i).toElement();
        QDomNodeList children = node.childNodes();
        QMap<QString, QString> child;

        for(int j = 0; j < children.size(); j++){
            child[children.at(j).toElement().nodeName()] = children.at(j).toElement().text();
        }

        QDomNamedNodeMap attrMap = node.attributes();

        for(int j = 0; j < children.size(); j++){
            QDomAttr attr = attrMap.item(j).toAttr();
            child[attr.name()] = attr.value();
        }

        QString pathOrName = child["pathOrName"];
        QString parentPath = child["parentPath"];
        QString objectType = child["objectType"];

        QDateTime modifiedAtD = QDateTime::fromString( child["modifiedAt"].mid(0,19) ,
                "yyyy-MM-ddThh:mm:ss" );
        QDateTime createdAtD = QDateTime::fromString( child["createdAt"].mid(0,19) ,
                "yyyy-MM-ddThh:mm:ss" );

        long long int createdAt = createdAtD.toMSecsSinceEpoch();
        long long int modifiedAt = modifiedAtD.toMSecsSinceEpoch();


        long long int dataSize = child["dataSize"].toLongLong();
        QString ownerName = child["ownerName"];
        QString ownerZone = child["ownerZone"];
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

