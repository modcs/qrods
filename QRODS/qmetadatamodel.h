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


#ifndef QMETADATAMODEL_H
#define QMETADATAMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include "metadataentry.h"
#include "qrods_global.h"

class QMetadataModelPrivate;

class QRODSSHARED_EXPORT QMetadataModel :  public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QMetadataModel(QObject *parent = 0);
    void setDataPath(QString &dataObj);
    QMetadataModelPrivate *getPrivateInstance();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column, const QModelIndex & parent) const;

private:
    QString _dataPath;
    QList<MetadataEntry*>* _list;

    QMetadataModelPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QMetadataModel)

public slots:
    void entryRemoved(MetadataEntry *entry);
    void metaDataReceived(QList<MetadataEntry*>*);
    void entryAdded(MetadataEntry *entry);
};

#endif // QMETADATAMODEL_H
