#ifndef COLLECTIONCLIENTSYNC_H
#define COLLECTIONCLIENTSYNC_H

#include "collectionclient.h"
#include "filelistingentry.h"
#include <QObject>

class CollectionClientSync: QObject
{
    Q_OBJECT
public:
    CollectionClientSync(CollectionClient*);

    //FileListingEntry* getCollectionDataPaged(FileListingEntry *entry, QString &type, int offset);
    FileListingEntry* getCollectionDataLazy(FileListingEntry* entry);
public slots:
     void getPageData(FileListingEntry*, int firstIndex, int endIndex);
private:
    CollectionClient* client;
    FileListingEntry* result;
};

#endif // COLLECTIONCLIENTSYNC_H
