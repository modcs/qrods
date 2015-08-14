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


#ifndef QRODS_H
#define QRODS_H

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include "qmetadatamodel.h"
#include "filelistingentry.h"
#include "qrods_global.h"

class QRODSPrivate;

class QRODSSHARED_EXPORT QRODS : public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit QRODS(QObject *parent = 0);
    explicit QRODS(QObject *parent, QString &host, int port, QString &user, QString &password);

    void setUser(QString &user);
    void setPassword(QString &password);
    void setHost(QString &string);
    void setPort(int port);

    QString& getQRODSVersion();
    QString& user();
    QString& password();
    QString& host();
    int port();

    QMetadataModel *getDataModel();
    void addCollection(QString &path);
    void removeCollection(QString &path);
    void uploadFile(QString &remotePath, QString &localPath);
    void getFile(QString &remotePath, QString &localPath);
    QList<MetadataEntry*>* getDataObjectMetadata(QString &path);
    void removeDataObject(QString &path, bool force = false);
    void setDataPath(QString &dataObj);
    void addCollectionMetadata(QString &path, MetadataEntry &);
    void deleteCollectionMetadata(QString &path, MetadataEntry &);

    virtual bool connectToServer();
    virtual bool connectToServer(QString path);
    virtual bool connectToServer(QString path, bool secureHttp);

    QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex	parent(const QModelIndex & index) const;
    QVariant	data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    int	rowCount(const QModelIndex & parent = QModelIndex()) const;
    int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const;
    void setRootPath(const QString path);

    void addView(QAbstractItemView* view);
    void setVisibleColumns(QList<FileListingEntry::EntryColumn> & columns);

protected:
    FileListingEntry* nodeFromIndex( const QModelIndex &index) const;
    void loadMorePages( FileListingEntry *entry );

public slots:
    void getPageData(FileListingEntry*, int firstIndex, int endIndex);

    void valueChanged(int);
    void expanded(const QModelIndex &);
    void collapsed(const QModelIndex & index);
    void modelChanged();

signals:
    void notifyModelUpdated();

private:
    QRODSPrivate * d_ptr;
    Q_DECLARE_PRIVATE(QRODS)
};

#endif // QRODS_H
