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


#include "qrods.h"
#include <QListIterator>
#include <QModelIndex>
#include <QScrollBar>
#include <QTreeView>
#include "qrods_p.h"

#include "callcontroller.h"
#include <QModelIndex>

#include <QVariant>
#include <QList>

#include <QScrollBar>
#include "collectionclient.h"
#include "filecontentsclient.h"
#include "dataobjectclient.h"


/**
 * This is a constructor for QRODS class.
 *
 * @brief QRODS::QRODS Constructor.
 * @param parent the parent Qt widget.
 */
QRODS::QRODS(QObject *parent)
    : QAbstractItemModel(parent),
      d_ptr(new QRODSPrivate(this))
{    
    callController.setQRODS(this);
}

/**
 * This is a constructor for QRODS class.
 *
 * @brief QRODS::QRODS Constructor
 * @param parent the parent Qt widget.
 * @param host that has the Rest API system running.
 * @param port adopted to communicate with the iRODS.
 * @param user present on the iRODS system.
 * @param password for connection to that user in the iRODS system.
 */
QRODS::QRODS(QObject *parent, QString &host, int port, QString &user, QString &password)
    : QAbstractItemModel(parent),
        d_ptr(new QRODSPrivate(this))
{    
    setHost(host);
    setPort(port);
    setUser(user);
    setPassword(password);

    callController.setQRODS(this);
}

/**
 * This method returns a QRODS metadata model.
 *
 * @brief QRODS::getDataModel returns a QRODS.
 * @return a QRODS data model.
 */
QMetadataModel *QRODS::getDataModel()
{
    Q_D(QRODS);
    return d->getDataModel();
}

/**
 * This method adds a collection according to the path received as parameter.
 *
 * @brief QRODS::addCollection adds a collection.
 * @param path a string parameter that represents the path where the collection will be created.
 */
void QRODS::addCollection(QString &path)
{
    Q_D(QRODS);
    d->addCollection(path);
}

/**
 * This method removes the collection passed as parameter.
 *
 * @brief QRODS::removeCollection removes a collection.
 * @param path a string that represents the path of the collection to be removed.
 */
void QRODS::removeCollection(QString &path)
{
    Q_D(QRODS);    
    d->removeCollection(path);
}

/**
 * This method uploads a file from the local path to the remote path specified as parameters.
 *
 * @brief QRODS::uploadFile uploads a file.
 * @param remotePath a string that represents the path on the iRODS system.
 * @param localPath a string that represents the source path.
 */
void QRODS::uploadFile(QString &remotePath, QString &localPath)
{
    Q_D(QRODS);    
    d->uploadFile(remotePath, localPath);
}

/**
 * This method download a file located in remotePath to
 * the localPath
 *
 * @brief QRODS::getFile get a file.
 * @param remotePath a string that represents the path on the iRODS system.
 * @param localPath a string that represents the local path.
 */
void QRODS::getFile(QString &remotePath, QString &localPath)
{
    Q_D(QRODS);
    d->getFile(remotePath, localPath);
}

/**
 * This method gets a list of metadata related to a specified remote object.
 *
 * @brief QRODS::getDataObjectMetadata gets the object data of a metadata.
 * @param path a string that represents the object path.
 * @return a list of object data of the metadata entry specfied as parameter.
 */
QList<MetadataEntry*>* QRODS::getDataObjectMetadata(QString &path)
{
    Q_D(QRODS);
    return d->getDataObjectMetadata(path);
}

/**
 * This method adds a metadata entry to a remote object specified in path.
 *
 * @brief QRODS::addCollectionMetadata adds a collection to a metadata.
 * @param path a string that represents the path of the collection to be added.
 * @param map represents the metadata entry.
 */
void QRODS::addCollectionMetadata(QString &path, MetadataEntry &entry)
{
    Q_D(QRODS);
    d->addCollectionMetadata(path, entry);
}


/**
 * This method deletes a metada entry from a remote object specified in path.
 *
 * @brief QRODS::deleteCollectionMetadata
 * @param path
 * @param entry
 */
void  QRODS::deleteCollectionMetadata(QString &path, MetadataEntry &entry)
{
    Q_D(QRODS);
    d->deleteCollectionMetadata(path, entry);
}


/**
 * This method removes a data object specified as parameter.
 *
 * @brief QRODS::removeDataObject
 * @param path a string that represents the object to be removed.
 * @param force a boolean to force the remove operation.
 */
void QRODS::removeDataObject(QString &path, bool force)
{
    Q_D(QRODS);

    beginResetModel();

    d->removeDataObject(path, force);
}

/**
 * Sets the path of a remote object associated with the
 * QRODS metadata model.
 *
 * @brief QRODS::setDataPath Sets the path of a remote
 * object associated with the QRODS metadata model.
 * @param dataObj a data object.
 */
void QRODS::setDataPath(QString &dataObj)
{
    Q_D(QRODS);
    d->setDataPath(dataObj);
}

/**
 * Sets the IRODS user.
 *
 * @brief QRODS::setUser sets the user.
 * @param user a string that represents the user.
 */
void QRODS::setUser(QString &user)
{
    Q_D(QRODS);
    d->setUser(user);
}

/**
 * Sets the IRODS password associated with the user.
 *
 * @brief QRODS::setPassword sets the password.
 * @param password a string that represents the password.
 */
void QRODS::setPassword(QString &password){
    Q_D(QRODS);
    d->setPassword(password);
}

/**
 * Sets the IRODS host.
 *
 * @brief QRODS::setHost sets the host.
 * @param host a string that represents the host.
 */
void QRODS::setHost(QString &host){
    Q_D(QRODS);
    d->setHost(host);
}

/**
 * Sets the Port.
 *
 * @brief QRODS::setPort sets the Port.
 * @param port an integer that represents the port to be used for communication with iRODS system.
 */
void QRODS::setPort(int port){
    Q_D(QRODS);
    d->setPort(port);
}

/**
 * Returns the QRODS Version.
 *
 * @brief QRODS::getQRODSVersion gets QRODS version.
 * @return the QRODS version.
 */
QString& QRODS::getQRODSVersion(){
    Q_D(QRODS);
    return d->getQRODSVersion();
}


/**
 * Returns the iRODS user.
 *
 * @brief QRODS::user gets user.
 * @return the iRODS user.
 */
QString& QRODS::user(){
    Q_D(QRODS);
    return d->user();
}

/**
 * Returns the password.
 *
 * @brief QRODS::password returns the password.
 * @return the password.
 */
QString& QRODS::password(){
    Q_D(QRODS);
    return d->password();
}

/**
 * Returns the host.
 *
 * @brief QRODS::host returns the host.
 * @return the host.
 */
QString& QRODS::host(){
    Q_D(QRODS);
    return d->host();
}

/**
 * Returns the port.
 *
 * @brief QRODS::port gets the port.
 * @return the port
 */
int QRODS::port(){
    Q_D(QRODS);
    return d->port();
}

/**
 * This method connects to the server in the iRODS zone specified by parameter.
 *
 * @brief QRODS::connectToServer connets to a server.
 * @param path a string that represents the iRODS zone.
 */
bool QRODS::connectToServer(QString path){
    return this->connectToServer(path, false);
}

/**
 * Connects to the server dopting
 * the default zone /tempZone/home/rods..
 *
 * @brief QRODS::connectToServer connects to the server adopting
 * the default zone /tempZone/home/rods.
 */
bool QRODS::connectToServer(){
    QString path("/tempZone/home/rods");
    return this->connectToServer(path, false);
}

/**
 * This method connects to the server in the iRODS zone specified by parameter.
 * The other parameter specifies if https will be adopted or not.
 *
 * @brief QRODS::connectToServer connects to server.
 * @param path a string that represents the server to be connected.
 * @param secureHttp a boolean that specify if HTTPS must be considered or not.
 */
bool QRODS::connectToServer(QString path, bool secureHttp){

    Q_D(QRODS);
    return d->connectToServer(path, secureHttp);
}

/**
 * Slot that reload the model in case of model changes.
 * For instance, object delete or upload.
 *
 * @brief QRODS::modelChanged resets the QRODS model.
 */
void QRODS::modelChanged()
{
    Q_D(QRODS);

    QString path = d->_rootNode->pathOrName();
    FileListingEntry::ObjectType type = d->_rootNode->objectType();

    delete(d->_rootNode);

    beginResetModel();

    d->_rootNode = new FileListingEntry(this);
    d->_rootNode->setPathOrName(path);
    d->_rootNode->setObjectType(type);

    d->getCollectionDataLazy(d->_rootNode);
}

/**
 * Returns a QModelIndex according to the parent passed by parameter.
 *
 * @brief QRODS::index returns an index.
 * @param row row.
 * @param column column.
 * @param parent parent.
 * @return returns a QModelIndex.
 */
QModelIndex	QRODS::index(int row, int column, const QModelIndex & parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    FileListingEntry* father = nodeFromIndex(parent);
    FileListingEntry* child = father->children()->value(row);

    if(child){
        return createIndex(row, column, child);
    }else{
        return QModelIndex();
    }
}

/**
 * Returns a QModelIndex parent according to the child passed as parameter.
 *
 * @brief QRODS::parent returns a QModelIndex.
 * @param child a QModelIndex.
 * @return returns a QModelIndex.
 */
QModelIndex	QRODS::parent(const QModelIndex & child) const
{
    Q_D(const QRODS);
    if (!child.isValid())
        return QModelIndex();

    FileListingEntry* entry = nodeFromIndex(child);
    FileListingEntry* parent = entry->parentNode();

    if(parent == d->_rootNode || !parent){
        return QModelIndex();
    }

    return createIndex(parent->row(), 0, parent);
}

/**
 * Returns the data representation to be displayed in the
 * model View according to the role passed as parameter.
 *
 * @brief QRODS::data Returns QRODS data as a QVariant.
 * @param index a QModelIndex.
 * @param role an integer that represents a role.
 * @return returns QRODS data as a QVariant.
 */
QVariant QRODS::data(const QModelIndex & index, int role) const
{
   Q_D(const QRODS);

   if (!index.isValid())
        return QVariant();

   if (role != Qt::DisplayRole)
        return QVariant();

   FileListingEntry* entry = nodeFromIndex(index);

   if (!entry)
       return QVariant();

   FileListingEntry::EntryColumn column = d->visibleColumns[index.column()];

   return entry->getField(column);  
}

/**
 * Returns the number of rows related to the view.
 *
 * @brief QRODS::rowCount Returns the number of rows.
 * @param parent the parent.
 * @return returns the number of rows as an integer.
 */
int	QRODS::rowCount(const QModelIndex & parent) const
{
    FileListingEntry *parentItem;

    if (parent.column() > 0)
        return 0;

    parentItem = nodeFromIndex(parent);

    if(parentItem){
        return parentItem->children()->size();
    }else{
        return 0;
    }
}

/**
 * Returns the number of columns of the view.
 *
 * @brief QRODS::columnCount Returns the number of columns.
 * @param parent the parent.
 * @return returns the number of columns for the table view.
 */
int	QRODS::columnCount(const QModelIndex & parent) const
{
    (void)parent;
    Q_D(const QRODS);
    return d->visibleColumns.size();
}

/**
 * Returns the QRODS header data associated with a view column.
 *
 * @brief QRODS::headerData Returns the QRODS header data.
 * @param section an integer that is the section.
 * @param orientation the vertical and horizontal orientation.
 * @param role an integer that represents the role.
 * @return returns the QRODS header data as a QVariant.
 */
QVariant QRODS::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_D(const QRODS);

    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractItemModel::headerData(section, orientation, role);

    FileListingEntry::EntryColumn col = d->visibleColumns[section];

    return QVariant( d->columns[col] );
}

/**
 * Returns TRUE if the QModelIndex passed as parameter has children.
 *
 * @brief QRODS::hasChildren checks if the QModelIndex has children.
 * @param parent a QModelIndex.
 * @return returns TRUE if the QModelIndex passed as parameter has children.
 */
bool QRODS::hasChildren(const QModelIndex &parent) const
{
    Q_D(const QRODS);

    FileListingEntry* entry = nodeFromIndex(parent);

    if(!entry){
        return false;
    }

    if(entry->isCollection() && (entry != d->_rootNode)  && (entry->collectionsOffset() < 0 && entry->dataObjectsOffset() < 0)){
        entry->setFlag(true);

        d->getCollectionDataLazy(entry);
    }

    return entry->isCollection();
}

/**
 * Slot to be fired when the iRODS rest responds to a collection listing.
 * It is responsible for notifying the QRODS that the model should be updated.
 *
 * @brief QRODS::getPageData Gets page data.
 * @param entry a FileListingEntry.
 * @param firstIndex an integer that is the first index.
 * @param endIndex an integer that is the last index.
 */
void QRODS::getPageData(FileListingEntry *entry, int firstIndex, int endIndex){
    Q_D(QRODS);
    (void)firstIndex;
    (void)endIndex;

    endResetModel();

    if(!entry){        
        return;
    }

    emit(notifyModelUpdated());

    if(d->bar){
        d->bar->setValue(d->oldValue);
    }

    if(QTreeView* v = dynamic_cast<QTreeView*>(d->view)) {
        for(QModelIndex i : d->indexes.values())
        {
            v->setExpanded(i, true);
        }
    }
}

/**
 * Sets the root path related to QRODS instance. For instance,
 * if the root path is /tempZone/home/rods, QRODS instance will
 * be able to manage objects/collections/metadata that are contained
 * in this path.
 *
 * @brief QRODS::setRootPath Sets the root path.
 * @param path a string that represents the QRODS server path.
 */
void QRODS::setRootPath(const QString path){
    beginResetModel();

    this->connectToServer(path);
}

/**
  * This method associates a QAbstractItemView to QRODS. This
  * association permits the QRODS control the view in case of
  * model updates.
  *
  * @brief QRODS::addView Adds a view.
  * @param view a QAbstractItemView.
  */
 void QRODS::addView(QAbstractItemView *view){
    Q_D(QRODS);

    d->bar = view->verticalScrollBar();
    d->view = view;

    connect( d->bar, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)) );

    if(QTreeView* v = dynamic_cast<QTreeView*>(view)) {
        connect( v, SIGNAL(expanded(QModelIndex)), this, SLOT(expanded(QModelIndex)) );
        connect( v, SIGNAL(collapsed(QModelIndex)), this, SLOT(collapsed(QModelIndex)) );
    }
 }

 /**
  * Loads more pages considering the value index passed as parameter.
  *
  * @brief QRODS::valueChanged Loads more pages.
  * @param val an integer that represents the index value.
  */
 void QRODS::valueChanged(int val){
    Q_D(QRODS);

    if(val == d->bar->maximum()){
        d->oldValue = val;

        loadMorePages(d->_rootNode);

        QMapIterator<QString, FileListingEntry* > iter(d->nodes);
        while(iter.hasNext())
        {
            iter.next();
            loadMorePages( iter.value() );
        }
    }
 }

 /**
  * Expands the FileListingEntry according to the QModelIndex passed by parameter.
  *
  * @brief QRODS::expanded Expands the QRODS data.
  * @param index a QModelIndex.
  */
 void QRODS::expanded(const QModelIndex & index){
    Q_D(QRODS);

    FileListingEntry* entry = nodeFromIndex(index);
    if(entry){
        d->nodes[entry->pathOrName()] = entry;
        d->indexes[entry->pathOrName()] = index;
    }
 }

 /**
  * Collapses the QModelIndex passed as parameter.
  *
  * @brief QRODS::collapsed Collapses the QModelIndex.
  * @param index a QModelIndex.
  */
 void QRODS::collapsed(const QModelIndex & index){

     Q_D(QRODS);

     FileListingEntry* entry = nodeFromIndex(index);

     if(entry){
         d->nodes.remove(entry->pathOrName());
         d->indexes.remove(entry->pathOrName());
     }
 }

 /**
  * Returns a FileListingEntry node according to the QModelIndex passed as parameter.
  *
  * @brief QRODS::nodeFromIndex Returns a FileListingEntry node.
  * @param index the QModelIndex.
  * @return returns a FileListingEntry node according to the QModelIndex passed as parameter.
  */
 FileListingEntry* QRODS::nodeFromIndex(const QModelIndex &index) const{
     Q_D(const QRODS);

     if (index.isValid()) {
         return static_cast<FileListingEntry *>(index.internalPointer());
     } else {
         return d->_rootNode;
     }
 }

 /**
  * Loads pages according to the FileListingEntry passed as parameter.
  *
  * @brief QRODS::loadMorePages Loads pages.
  * @param entry a FileListingEntry.
  */
 void QRODS::loadMorePages( FileListingEntry *entry ){
     Q_D(const QRODS);

     if( entry->hasMorePages() ){
         beginResetModel();

         d->getNextPage(entry);
     }
 }

 /**
  * @brief QRODS::setVisibleColumns
  * @param columns
  */
 void QRODS::setVisibleColumns(QList<FileListingEntry::EntryColumn> & columns){
    Q_D(QRODS);

    d->visibleColumns = columns;
 }
