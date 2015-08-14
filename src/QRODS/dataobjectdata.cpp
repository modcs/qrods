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


#include "dataobjectdata.h"

/**
 * This is a constructor for DataObjectData class.
 *
 * @brief DataObjectData::DataObjectData Constructor method.
 * @param parent the parent Qt widget.
 */
DataObjectData::DataObjectData(QObject *parent) :
    QObject(parent)
{
}

/**
 * Returns id.
 *
 * @brief DataObjectData::id Returns id.
 * @return  returns the id.
 */
int DataObjectData::id() const
{
    return _id;
}

/**
 * Returns collection Id.
 *
 * @brief DataObjectData::collectionId Returns collection Id.
 * @return returns the collectionId.
 */
int DataObjectData::collectionId() const
{
    return _collectionId;
}

/**
 * Returns data name.
 *
 * @brief DataObjectData::dataName Returns data name.
 * @return returns dataName.
 */
const QString& DataObjectData::dataName() const
{
    return _dataName;
}

/**
 * Returns collection name.
 *
 * @brief DataObjectData::collectionName Returns collection name.
 * @return returns collectionName.
 */
const QString& DataObjectData::collectionName() const
{
    return _collectionName;
}

/**
 * Returns data replication number.
 *
 * @brief DataObjectData::dataReplicationNumber Returns data replication number.
 * @return returns dataReplicationNumber.
 */
int DataObjectData::dataReplicationNumber() const
{
    return _dataReplicationNumber;
}

/**
 * Returns data version.
 *
 * @brief DataObjectData::dataVersion Returns data version.
 * @return returns dataVersion.
 */
int DataObjectData::dataVersion() const
{
    return _dataVersion;
}

/**
 * Returns data type name.
 *
 * @brief DataObjectData::dataTypeName Returns data type name.
 * @return returns dataTypeName.
 */
const QString& DataObjectData::dataTypeName() const
{
    return _dataTypeName;
}

/**
 * Returns data size.
 *
 * @brief DataObjectData::dataSize Returns data size.
 * @return returns dataSize.
 */
long long int DataObjectData::dataSize() const
{
    return _dataSize;
}

/**
 * Returns resource group name.
 *
 * @brief DataObjectData::resourceGroupName Returns resource group name.
 * @return returns resourceGroupName.
 */
const QString& DataObjectData::resourceGroupName() const
{
    return _resourceGroupName;
}

/**
 * Returns resource name.
 *
 * @brief DataObjectData::resourceName Returns resource name.
 * @return returns resourceName.
 */
const QString& DataObjectData::resourceName() const
{
    return _resourceName;
}

/**
 * Returns data path.
 *
 * @brief DataObjectData::dataPath Returns data path.
 * @return returns dataPath.
 */
const QString& DataObjectData::dataPath() const
{
    return _dataPath;
}

/**
 * Returns data owner name.
 *
 * @brief DataObjectData::dataOwnerName Returns data owner name.
 * @return returns dataOwnerName.
 */
const QString& DataObjectData::dataOwnerName() const
{
    return _dataOwnerName;
}

/**
 * Returns data owner zone.
 *
 * @brief DataObjectData::dataOwnerZone Returns data owner zone.
 * @return returns dataOwnerZone.
 */
const QString& DataObjectData::dataOwnerZone() const
{
    return _dataOwnerZone;
}

/**
 * Returns replication status.
 *
 * @brief DataObjectData::replicationStatus Returns replication status.
 * @return returns replicationStatus.
 */
const QString& DataObjectData::replicationStatus() const
{
    return _replicationStatus;
}

/**
 * Returns data status.
 *
 * @brief DataObjectData::dataStatus Returns data status.
 * @return returns dataStatus.
 */
const QString& DataObjectData::dataStatus() const
{
    return _dataStatus;
}

/**
 * Returns checksum.
 *
 * @brief DataObjectData::checksum Returns checksum.
 * @return returns checksum.
 */
const QString& DataObjectData::checksum() const
{
    return _checksum;
}

/**
 * Returns expiry.
 *
 * @brief DataObjectData::expiry Returns expiry.
 * @return returns expiry.
 */
const QString& DataObjectData::expiry() const
{
    return _expiry;
}

/**
 * Returns data map id.
 *
 * @brief DataObjectData::dataMapId Returns data map id.
 * @return returns dataMapId.
 */
int DataObjectData::dataMapId() const
{
    return _dataMapId;
}

/**
 * Returns comments.
 *
 * @brief DataObjectData::comments Returns comments.
 * @return retuns comments.
 */
const QString& DataObjectData::comments() const
{
    return _comments;
}

/**
 * Returns the data when the object was created.
 *
 * @brief DataObjectData::createdAt Returns the creation data.
 * @return returns createAt.
 */
long long int DataObjectData::createdAt() const
{
    return _createdAt;
}

/**
 * Returns the last update data.
 *
 * @brief DataObjectData::updatedAt Returns the last update data.
 * @return returns updateAt.
 */
long long int DataObjectData::updatedAt() const
{
    return _updatedAt;
}

/**
 * Returns the specified column type.
 *
 * @brief DataObjectData::specColType Returns the specified column type.
 * @return returns the specified column type.
 */
SpecColType DataObjectData::specColType() const
{
    return _specColType;
}

/**
 * Returns the object path.
 *
 * @brief DataObjectData::objectPath Returns the object path.
 * @return returns the objectPath.
 */
const QString& DataObjectData::objectPath() const
{
    return _objectPath;
}

/**
 * Sets the object id.
 *
 * @brief DataObjectData::setId Sets the id.
 * @param i the id.
 */
void DataObjectData::setId(int i)
{
    _id = i;
}

/**
 * Sets collection id.
 *
 * @brief DataObjectData::setCollectionId Sets collection id.
 * @param i the collection id.
 */
void DataObjectData::setCollectionId(int i)
{
    _collectionId = i;
}

/**
 * Sets data name.
 *
 * @brief DataObjectData::setDataName Sets data name.
 * @param str a string to set as the data name.
 */
void DataObjectData::setDataName(const QString& str)
{
    _dataName = str;
}

/**
 * Sets collection name.
 *
 * @brief DataObjectData::setCollectionName Sets collection name.
 * @param str a string tha represents the collection name.
 */
void DataObjectData::setCollectionName(const QString& str)
{
    _collectionName = str;
}

/**
 * Sets data replication number.
 *
 * @brief DataObjectData::setDataReplicationNumber Sets data replication number.
 * @param i an integer that is the replication number.
 */
void DataObjectData::setDataReplicationNumber(int i)
{
    _dataReplicationNumber = i;
}

/**
 * Sets data version.
 *
 * @brief DataObjectData::setDataVersion Sets data version.
 * @param i an integer to set the data version.
 */
void DataObjectData::setDataVersion(int i)
{
    _dataVersion = i;
}

/**
 * Sets data type name.
 *
 * @brief DataObjectData::setDataTypeName Sets data type name.
 * @param str a string that is the data type name.
 */
void DataObjectData::setDataTypeName(const QString& str)
{
    _dataTypeName = str;
}

/**
 * Sets data size.
 *
 * @brief DataObjectData::setDataSize Sets data size.
 * @param i the data size.
 */
void DataObjectData::setDataSize(long long int i)
{
    _dataSize = i;
}

/**
 * Sets resouce group name.
 *
 * @brief DataObjectData::setResourceGroupName Sets resouce group name.
 * @param str a string that is the resource group name.
 */
void DataObjectData::setResourceGroupName(const QString& str)
{
    _resourceGroupName = str;
}

/**
 * Sets resource name.
 *
 * @brief DataObjectData::setResourceName Sets resource name.
 * @param str a string that is the resource name.
 */
void DataObjectData::setResourceName(const QString& str)
{
    _resourceName = str;
}

/**
 * Sets data path.
 *
 * @brief DataObjectData::setDataPath Sets data path.
 * @param str a string that is the data path.
 */
void DataObjectData::setDataPath(const QString& str)
{
    _dataPath = str;
}

/**
 * Sets data owner name.
 *
 * @brief DataObjectData::setDataOwnerName Sets data owner name.
 * @param str a string that is the data owner name.
 */
void DataObjectData::setDataOwnerName(const QString& str)
{
    _dataOwnerName = str;
}

/**
 * Sets the data owner zone.
 *
 * @brief DataObjectData::setDataOwnerZone Sets the data owner zone.
 * @param str a string that is the data owner zone.
 */
void DataObjectData::setDataOwnerZone(const QString& str)
{
    _dataOwnerZone = str;
}

/**
 * Sets the replication status.
 *
 * @brief DataObjectData::setReplicationStatus Sets the replication status.
 * @param str a string that represents the replication status.
 */
void DataObjectData::setReplicationStatus(const QString& str)
{
    _replicationStatus = str;
}

/**
 * Sets the data status.
 *
 * @brief DataObjectData::setDataStatus Sets the data status.
 * @param str a string that represents the data status.
 */
void DataObjectData::setDataStatus(const QString& str)
{
    _dataStatus = str;
}

/**
 * Sets the checksum.
 *
 * @brief DataObjectData::setChecksum Sets the checksum.
 * @param str a string that represents the checksum.
 */
void DataObjectData::setChecksum(const QString& str)
{
    _checksum = str;
}

/**
 * Sets the expiry.
 *
 * @brief DataObjectData::setExpiry Sets the expiry.
 * @param str a string that represents the expiry.
 */
void DataObjectData::setExpiry(const QString& str)
{
    _expiry = str;
}

/**
 * Sets data map id.
 *
 * @brief DataObjectData::setDataMapId Sets data map id.
 * @param i an integer that represents the id.
 */
void DataObjectData::setDataMapId(int i)
{
    _dataMapId = i;
}

/**
 * Sets comments.
 *
 * @brief DataObjectData::setComments Sets comments.
 * @param str a string that represents the comments.
 */
void DataObjectData::setComments(const QString& str)
{
    _comments = str;
}

/**
 * Sets the created data.
 *
 * @brief DataObjectData::setCreatedAt Sets the created data.
 * @param i i variable that represents the data.
 */
void DataObjectData::setCreatedAt(long long int i)
{
    _createdAt = i;
}

/**
 * Sets the update data.
 *
 * @brief DataObjectData::setUpdatedAt Sets the update data.
 * @param i the update data.
 */
void DataObjectData::setUpdatedAt(long long int i)
{
    _updatedAt = i;
}

/**
 * Sets the specified column type.
 *
 * @brief DataObjectData::setSpecColType Sets the specified column type.
 * @param s the column type.
 */
void DataObjectData::setSpecColType(SpecColType s)
{
    _specColType = s;
}

/**
 * Sets object path.
 *
 * @brief DataObjectData::setObjectPath Sets object path.
 * @param str a string that is the object path.
 */
void DataObjectData::setObjectPath(const QString& str)
{
    _objectPath = str;
}
