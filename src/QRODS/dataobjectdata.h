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


#ifndef DATAOBJECTDATA_H
#define DATAOBJECTDATA_H

#include <QObject>
#include <QString>

enum SpecColType {NORMAL, STRUCT_FILE_COLL, MOUNTED_COLL, LINKED_COLL};

class DataObjectData : public QObject
{
    Q_OBJECT
public:
    explicit DataObjectData(QObject *parent = 0);

    int id() const;
    int collectionId() const;
    const QString& dataName() const;
    const QString& collectionName() const;
    int dataReplicationNumber() const;
    int dataVersion() const;
    const QString& dataTypeName() const;
    long long int dataSize() const;
    const QString& resourceGroupName() const;
    const QString& resourceName() const;
    const QString& dataPath() const;
    const QString& dataOwnerName() const;
    const QString& dataOwnerZone() const;
    const QString& replicationStatus() const;
    const QString& dataStatus() const;
    const QString& checksum() const;
    const QString& expiry() const;
    int dataMapId() const;
    const QString& comments() const;
    long long int createdAt() const;
    long long int updatedAt() const;
    SpecColType specColType() const;
    const QString& objectPath() const;

    void setId(int );
    void setCollectionId(int );
    void setDataName(const QString& );
    void setCollectionName(const QString& );
    void setDataReplicationNumber(int );
    void setDataVersion(int );
    void setDataTypeName(const QString& );
    void setDataSize(long long int );
    void setResourceGroupName(const QString& );
    void setResourceName(const QString& );
    void setDataPath(const QString& );
    void setDataOwnerName(const QString& );
    void setDataOwnerZone(const QString& );
    void setReplicationStatus(const QString& );
    void setDataStatus(const QString& );
    void setChecksum(const QString& );
    void setExpiry(const QString& );
    void setDataMapId(int );
    void setComments(const QString& );
    void setCreatedAt(long long int );
    void setUpdatedAt(long long int );
    void setSpecColType(SpecColType );
    void setObjectPath(const QString& );

signals:

public slots:

private:
    int _id;
    int _collectionId;
    QString _dataName;
    QString _collectionName;
    int _dataReplicationNumber;
    int _dataVersion;
    QString _dataTypeName;
    long long int _dataSize;
    QString _resourceGroupName;
    QString _resourceName;
    QString _dataPath;
    QString _dataOwnerName;
    QString _dataOwnerZone;
    QString _replicationStatus;
    QString _dataStatus;
    QString _checksum;
    QString _expiry;
    int _dataMapId;
    QString _comments;
    long long int _createdAt;
    long long int _updatedAt;
    SpecColType _specColType;
    QString _objectPath;
};

#endif // DATAOBJECTDATA_H
