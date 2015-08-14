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


#include "filelistingentry.h"
#include <QDateTime>

/**
 * This is a constructor for AbstractHTTPClient class.
 *
 * @brief FileListingEntry::FileListingEntry Constructor method.
 * @param parent the parent.
 */
FileListingEntry::FileListingEntry(QObject *parent) :
    QObject(parent)
{
    _children = new QList<FileListingEntry*>();
}

/**
 * Sets parent path.
 *
 * @brief FileListingEntry::setParentPath Sets parent path.
 * @param str a string that represents the path.
 */
void FileListingEntry::setParentPath(QString& str){
    _parentPath = str;
}

/**
 * Sets the path.
 *
 * @brief FileListingEntry::setPathOrName Sets the path.
 * @param str a string that represents the path.
 */
void FileListingEntry::setPathOrName(QString& str){
    _pathOrName = str;
}

/**
 * Sets special object path.
 *
 * @brief FileListingEntry::setSpecialObjectPath Sets special object path.
 * @param str a string that represents the path.
 */
void FileListingEntry::setSpecialObjectPath(QString& str){
    _specialObjectPath = str;
}

/**
 * Sets object type.
 *
 * @brief FileListingEntry::setObjectType Sets object type.
 * @param tp the object type.
 */
void FileListingEntry::setObjectType(ObjectType tp){
    _objectType = tp;
}

/**
 * Sets the creation date.
 *
 * @brief FileListingEntry::setCreatedAt Sets the creation date.
 * @param at the date.
 */
void FileListingEntry::setCreatedAt(long long int at){
    _createdAt = at;
}

/**
 * Sets the modification date.
 *
 * @brief FileListingEntry::setModifiedAt Sets the modification date.
 * @param at the date.
 */
void FileListingEntry::setModifiedAt(long long int at){
    _modifiedAt = at;
}

/**
 * Sets the data size.
 *
 * @brief FileListingEntry::setDataSize Sets the data size.
 * @param size the size.
 */
void FileListingEntry::setDataSize(long long int size){
    _dataSize = size;
}

/**
 * Sets the owner name.
 *
 * @brief FileListingEntry::setOwnerName Sets the owner name.
 * @param str a string that represents the owner name.
 */
void FileListingEntry::setOwnerName(QString& str){
    _ownerName = str;
}

/**
 * Sets owner zone.
 *
 * @brief FileListingEntry::setOwnerZone Sets owner zone.
 * @param str a string that represents the owner zone.
 */
void FileListingEntry::setOwnerZone(QString& str){
    _ownerZone = str;
}

/**
 * Sets the id for the FileListingEntry.
 *
 * @brief FileListingEntry::setId Sets the id.
 * @param i an integer that is the id.
 */
void FileListingEntry::setId(int i){
    _id = i;
}

/**
 * Sets the row of the FileListingEntry
 *
 * @brief FileListingEntry::setRow Sets the row.
 * @param i an integer that is the row.
 */
void FileListingEntry::setRow(int i){
    _row = i;
}

/**
 * Sets the Offset.
 *
 * @brief FileListingEntry::setOffset Sets the Offset.
 * @param off an integer that is the offset.
 */
void FileListingEntry::setOffset(int off){
    _offset = off;
}

/**
 * Sets the presence of more pages.
 *
 * @brief FileListingEntry::setHasMorePages Sets the presence of more pages.
 * @param b a boolean that represents the presence of more pages.
 */
void FileListingEntry::setHasMorePages(bool b){
    _hasmorepages = b;
}

/**
 * Gets the parent path.
 *
 * @brief FileListingEntry::parentPath Gets the parent path.
 * @return returns the parent path.
 */
const QString& FileListingEntry::parentPath() const{
    return _parentPath;
}

/**
 * Gets the path or name.
 *
 * @brief FileListingEntry::pathOrName Gets the path or name.
 * @return returns the path or name.
 */
const QString& FileListingEntry::pathOrName() const{
    return _pathOrName;
}

/**
 * Gets special object path.
 *
 * @brief FileListingEntry::specialObjectPath Gets special object path.
 * @return returns special object path.
 */
const QString& FileListingEntry::specialObjectPath() const{
    return _specialObjectPath;
}

/**
 * Gets the object type.
 *
 * @brief FileListingEntry::objectType Gets the object type.
 * @return returns the object type.
 */
FileListingEntry::ObjectType FileListingEntry::objectType() const{
    return _objectType;
}

/**
 * Gets the creation date.
 *
 * @brief FileListingEntry::createdAt Gets the creation date.
 * @return returns the creation date.
 */
long long int FileListingEntry::createdAt() const{
    return _createdAt;
}

/**
 * Gets the last modification date.
 *
 * @brief FileListingEntry::modifiedAt Gets the last modification date.
 * @return returns the last modification date.
 */
long long int FileListingEntry::modifiedAt() const{
    return _modifiedAt;
}

/**
 * Gets the data size.
 *
 * @brief FileListingEntry::dataSize Gets the data size.
 * @return returns the data size.
 */
long long int FileListingEntry::dataSize() const{
    return _dataSize;
}

/**
 * Gets the owner name.
 *
 * @brief FileListingEntry::ownerName Gets the owner name.
 * @return returns the owner name.
 */
const QString& FileListingEntry::ownerName() const{
    return _ownerName;
}

/**
 * Gets the owner zone.
 *
 * @brief FileListingEntry::ownerZone Gets the owner zone.
 * @return returns the owner zone.
 */
const QString& FileListingEntry::ownerZone() const{
    return _ownerZone;
}

/**
 * Checks if the ObjectType is a collection.
 *
 * @brief FileListingEntry::isCollection Checks if the ObjectType is a collection.
 * @return returns true if the objectType is a collection or false otherwise.
 */
bool FileListingEntry::isCollection(){
    if(this->objectType() == COLLECTION){
        return true;
    }
    return false;
}

/**
 * Gets id.
 *
 * @brief FileListingEntry::id Gets id.
 * @return returns the id.
 */
int FileListingEntry::id() const{
    return _id;
}

/**
 * Gets the row.
 *
 * @brief FileListingEntry::row Gets the row.
 * @return returns the row.
 */
int FileListingEntry::row() const{
    return _row;
}

/**
 * Returns the presence of more pages of collections or data objects.
 *
 * @brief FileListingEntry::hasMorePages Returns the presence of more pages
 * @return returns a boolean.
 */
bool FileListingEntry::hasMorePages(){
    return this->hasMoreCollections() || this->hasMoreDataObjects();
}

/**
 * Gets the offset.
 *
 * @brief FileListingEntry::offset Gets the offset.
 * @return returns the offset.
 */
int FileListingEntry::offset(){
    return _offset;
}

/**
 * Gets the collection offset.
 *
 * @brief FileListingEntry::collectionsOffset Gets the collection offset.
 * @return returns the collection offset.
 */
int FileListingEntry::collectionsOffset(){
    return _collectionsOffset;
}

/**
 * Gets the data object offset.
 *
 * @brief FileListingEntry::dataObjectsOffset Gets the data object offset.
 * @return returns the data object offset.
 */
int FileListingEntry::dataObjectsOffset(){
    return _dataObjectsOffset;
}

/**
 * Checks the presence of more collections.
 *
 * @brief FileListingEntry::hasMoreCollections Checks the presence of more collections.
 * @return returns a boolean.
 */
bool FileListingEntry::hasMoreCollections(){
    return _hasmorecollections;
}

/**
 * Gets the presence of more data objects.
 *
 * @brief FileListingEntry::hasMoreDataObjects Gets the presence of more data objects.
 * @return returns a boolean representing the presence of more data objects.
 */
bool FileListingEntry::hasMoreDataObjects(){
    return _hasmoredataobjects;
}

/**
 * Sets the collection offset.
 *
 * @brief FileListingEntry::setCollectionsOffset Sets the collection offset.
 * @param offset the offset.
 */
void FileListingEntry::setCollectionsOffset(int offset){
    this->_collectionsOffset = offset;
}

/**
 * Sets data object offset.
 *
 * @brief FileListingEntry::setDataObjectsOffset Sets data object offset.
 * @param offset the offset.
 */
void FileListingEntry::setDataObjectsOffset(int offset){
    this->_dataObjectsOffset = offset;
}

/**
 * Sets the presence of more collections.
 *
 * @brief FileListingEntry::setHasMoreCollections Sets the presence of more collections.
 * @param b a boolean which sets the presence or not of more collections.
 */
void FileListingEntry::setHasMoreCollections( bool b ){
    this->_hasmorecollections = b;
}

/**
 * Sets the presence of more data objects.
 *
 * @brief FileListingEntry::setHasMoreDataObjects Sets the presence of more data objects.
 * @param b a boolean that sets the presence or not of more data objects.
 */
void FileListingEntry::setHasMoreDataObjects( bool b ){
    this->_hasmoredataobjects = b;
}

/**
 * Gets the full path.
 *
 * @brief FileListingEntry::getFullPath Gets the full path.
 * @return returns a string that represents the path or nome.
 */
const QString FileListingEntry::getFullPath() const{
    if(_objectType == DATA_OBJECT ){
        QString str( parentPath() );
        str.append("/").append( pathOrName() );

        return str;
    }
    return pathOrName();
}

/**
 * Deletes the children.
 *
 * @brief FileListingEntry::deleteChildren Deletes the children.
 */
void FileListingEntry::deleteChildren()
{
    QListIterator<FileListingEntry*> iter(*this->children());
    while( iter.hasNext() ){
        FileListingEntry *next = iter.next();
        next->deleteChildren();
        delete next;
    }
}

/**
 * Sets parent nodes.
 *
 * @brief FileListingEntry::setParentNode Sets parent nodes.
 * @param parent the parent.
 */
void FileListingEntry::setParentNode(FileListingEntry *parent){
    this->_parentNode = parent;
}

/**
 * Gets the parent node.
 *
 * @brief FileListingEntry::parentNode Gets the parent node.
 * @return returns the parent node.
 */
FileListingEntry* FileListingEntry::parentNode(){
    return _parentNode;
}

/**
 * Gets the children.
 *
 * @brief FileListingEntry::children Gets the children.
 * @return returns the children.
 */
QList<FileListingEntry*> * FileListingEntry::children(){
    return _children;
}

/**
 * Adds a child.
 *
 * @brief FileListingEntry::addChild Adds a child.
 * @param entry a FileListingEntry.
 */
void FileListingEntry::addChild(FileListingEntry* entry){
    int size = children()->size();
    entry->setRow(size);
    children()->append(entry);
}

/**
 * Gets the flag.
 *
 * @brief FileListingEntry::flag Gets the flag.
 * @return returns the flag.
 */
bool FileListingEntry::flag(){
    return _flag;
}

/**
 * Sets the flag.
 *
 * @brief FileListingEntry::setFlag Sets the flag.
 * @param b a boolean.
 */
void FileListingEntry::setFlag(bool b){
    this->_flag = b;
}

QVariant FileListingEntry::getField(FileListingEntry::EntryColumn col){
    QDateTime  date;
    switch(col){
    case PARENT_PATH:
        return QVariant(_parentPath);
    case PATH_OR_NAME:

        if(_objectType == COLLECTION){
            int index = _pathOrName.lastIndexOf("/");
            QStringRef subString(&_pathOrName, index + 1,_pathOrName.size() - index);
            return QVariant(subString.toString());
        }else{
            return QVariant(_pathOrName);
        }

    case SPECIAL_OBJECT_PATH:
        return QVariant(_specialObjectPath);
    case OBJECT_TYPE:
        switch(_objectType){
        case UNKNOWN:
            return tr("Unknown");
        case DATA_OBJECT:
            return tr("Data object");
        case COLLECTION:
            return tr("Collection");
        case UNKNOWN_FILE:
            return tr("Unknown file");
        case LOCAL_FILE:
            return tr("Local file");
        case LOCAL_DIR:
            return tr("Local dir");
        case NO_INPUT:
            return tr("No input");
        }
    case CREATED_AT:
        date.setMSecsSinceEpoch(_createdAt);
        return date.toString();
    case MODIFIED_AT:
        date.setMSecsSinceEpoch(_modifiedAt);
        return date.toString();
    case DATA_SIZE:
        if(_dataSize){
            return QVariant(_dataSize);
        }else{
            return tr("");
        }
    case OWNER_NAME:
        return QVariant(_ownerName);
    case OWNER_ZONE:
        return QVariant(_ownerZone);
    case ID:
        return QVariant(_id);
    case IS_COLLECTION:
        if(_objectType == COLLECTION){
            return tr("True");
        }else{
            return tr("False");
        }
    }

    return QVariant();
}
