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


#ifndef FILELISTINGENTRY_H
#define FILELISTINGENTRY_H

#include <QString>
#include <QObject>
#include <QVariant>
#include "qrods_global.h"

class QRODSSHARED_EXPORT FileListingEntry: public QObject
{
    Q_OBJECT
public:

    enum ObjectType { UNKNOWN, DATA_OBJECT, COLLECTION, UNKNOWN_FILE, LOCAL_FILE, LOCAL_DIR, NO_INPUT };

    enum EntryColumn {
        PARENT_PATH = 0,
        PATH_OR_NAME = 1,
        SPECIAL_OBJECT_PATH = 2,
        OBJECT_TYPE = 3,
        CREATED_AT = 4,
        MODIFIED_AT = 5,
        DATA_SIZE = 6,
        OWNER_NAME = 7,
        OWNER_ZONE = 8,
        ID = 9,
        IS_COLLECTION = 10
    };

    explicit FileListingEntry(QObject *parent = 0);

    QVariant getField(FileListingEntry::EntryColumn col);

    const QString& parentPath() const;
    const QString& pathOrName() const;
    const QString& specialObjectPath() const;
    ObjectType objectType() const;
    long long int createdAt() const;
    long long int modifiedAt() const;
    long long int dataSize() const;
    const QString& ownerName() const;
    const QString& ownerZone() const;
    int id() const;
    bool isCollection() ;
    int row() const;

    int offset();
    bool hasMorePages();

    int collectionsOffset();
    int dataObjectsOffset();

    bool hasMoreCollections();
    bool hasMoreDataObjects();

    void setCollectionsOffset(int);
    void setDataObjectsOffset(int);

    void setHasMoreCollections( bool );
    void setHasMoreDataObjects( bool );

    const QString getFullPath() const;

    void setParentPath(QString& );
    void setPathOrName(QString& );
    void setSpecialObjectPath(QString& );
    void setObjectType(ObjectType);
    void setCreatedAt(long long int );
    void setModifiedAt(long long int);
    void setDataSize(long long int);
    void setOwnerName(QString& );
    void setOwnerZone(QString& );
    void setId(int );
    void setRow( int );

    void setOffset(int);
    void setHasMorePages(bool);

    void deleteChildren();

    void setParentNode( FileListingEntry * );
    FileListingEntry* parentNode();
    QList<FileListingEntry*> * children();
    void addChild(FileListingEntry*);

    bool flag();
    void setFlag(bool);

private:
    QString _parentPath;
    QString _pathOrName;
    QString _specialObjectPath;
    ObjectType _objectType;
    long long int _createdAt;
    long long int _modifiedAt;
    long long int _dataSize;
    QString _ownerName;
    QString _ownerZone;
    int _id;
    int _row;

    int _offset = -1;
    bool _hasmorepages;

    int _collectionsOffset = -1;
    int _dataObjectsOffset = -1;

    bool _hasmorecollections = true;
    bool _hasmoredataobjects = true;

    bool _flag = false;

    FileListingEntry *_parentNode = 0;
    QList<FileListingEntry*> *_children;
};

#endif // FILELISTINGENTRY_H
