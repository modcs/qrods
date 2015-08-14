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


#ifndef DATAOBJECTCLIENT_H
#define DATAOBJECTCLIENT_H

#include <QString>
#include <QList>
#include <QNetworkReply>
#include "abstracthttpclient.h"
#include "metadataentry.h"

enum MetadataOperation{
    ADD_METADATA,
    DELETE_METADATA
};

class DataObjectClient:  public AbstractHTTPClient
{
    Q_OBJECT
public:
    explicit DataObjectClient(QString &baseURL, QString user, QString pass, QObject *parent = 0);

    void removeDataObject(QString &path, bool force = false);    
    void addCollectionMetadata(QString &path, MetadataEntry &);
    void deleteDataObjectMetadata(QString &path, MetadataEntry &);
    QList<MetadataEntry*>* getDataObjectMetadata(QString &path);
    void getDataObjectMetadataAsync(QString &path);
public slots:
    void replyFinished(QNetworkReply *reply);
signals:
    void metaData(QList<MetadataEntry*>*);
    void entryAdded(MetadataEntry*);
    void entryRemoved(MetadataEntry*);
    void modelChanged();
private:
    void getDataObjectMetadataFinished(QNetworkReply *reply);
    void doMetadataOperation(QString &path, MetadataEntry &entry, MetadataOperation op);
};

#endif // DATAOBJECTCLIENT_H
