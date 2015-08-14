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


#ifndef QRODS_P_H
#define QRODS_P_H
#include "qrods.h"
#include "collectionclient.h"
#include "filecontentsclient.h"
#include "dataobjectclient.h"
#include "qmetadatamodel_p.h"
#include "serverinfoclient.h"
#include <QList>

#define QRODS_VERSION "0.0.1"

class QRODSPrivate
{

private:
    QString _host;
    int _port;
    QString _user;
    QString _password;
    QString _currentPath;
    QString _version;
    CollectionClient *collectionClient;
    FileContentsClient *fileClient;
    DataObjectClient *dataClient;
    ServerInfoClient *serverClient;
    QMetadataModel *dataModel;
    QRODS *qrods;

public:
    QRODSPrivate(QRODS *qrods);

    bool connectToServer(QString path, bool secureHttp);

    void setUser(QString &user);
    void setPassword(QString &password);
    void setHost(QString &host);
    void setPort(int port);

    QString& getQRODSVersion();
    QString& user();
    QString& password();
    QString& host();
    int port();

    void addCollection(QString &path);
    void removeCollection(QString &path);
    void uploadFile(QString &remotePath, QString &localPath);
    void getFile(QString &remotePath, QString &localPath);
    QList<MetadataEntry*>* getDataObjectMetadata(QString &path);
    void addCollectionMetadata(QString &path, MetadataEntry &entry);
    void deleteCollectionMetadata(QString &path, MetadataEntry &entry);    
    void getCollectionDataLazy(FileListingEntry* entry) const;
    void removeDataObject(QString &path, bool force);
    void setDataPath(QString &dataObj);
    void getNextPage(FileListingEntry* entry) const;
    QMetadataModel *getDataModel();

public:

    QMap<QString, FileListingEntry*> _collections;
    FileListingEntry* _rootNode = 0;

    QScrollBar* bar = 0;
    int oldValue;
    QMap<QString, FileListingEntry*> nodes;
    QMap<QString, QModelIndex> indexes;
    QMap<FileListingEntry::EntryColumn, QString> columns;
    QList<FileListingEntry::EntryColumn> visibleColumns;

    QAbstractItemView* view = NULL;
};

#endif // QRODS_P_H
