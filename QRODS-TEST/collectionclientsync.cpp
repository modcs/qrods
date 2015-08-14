#include "collectionclientsync.h"
#include <QEventLoop>
CollectionClientSync::CollectionClientSync(CollectionClient* client)
{
    this->client = client;

    connect(client, SIGNAL(getPageData(FileListingEntry*,int,int)), this, SLOT(getPageData(FileListingEntry*,int,int)));
}

/**
 * Auxiliary method used to make it possible monitor the response for a listing task by using the method exec() of class QEventLoop.
 * @brief CollectionClientSync::getCollectionDataLazy
 * @param entry the corresponding collection
 * @return return the collection object with result
 */
FileListingEntry* CollectionClientSync::getCollectionDataLazy(FileListingEntry* entry){

    QEventLoop loop;
    QObject::connect(client, SIGNAL(getPageData(FileListingEntry*,int,int)), &loop, SLOT(quit()));
    this->client->getCollectionDataLazy(entry);

    loop.exec();


    return this->result;
}

void CollectionClientSync::getPageData(FileListingEntry* entry, int firstIndex, int endIndex){
    this->result = entry;
}
