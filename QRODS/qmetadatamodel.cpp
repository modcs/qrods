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


#include "qmetadatamodel_p.h"

/**
 * This is a constructor for QMetadataModel class.
 *
 * @brief QMetadataModel::QMetadataModel Constructor method.
 * @param parent the parent Qt widget.
 */
QMetadataModel::QMetadataModel(QObject *parent)
    : QAbstractTableModel(parent),
    d_ptr(new QMetadataModelPrivate(this))
{
    _list = new QList<MetadataEntry*>();
}

/**
 * Updates the metadata model after adding a metadata entry.
 *
 * @brief QMetadataModelPrivate::entryAdded Appends a metadata entry.
 * @param entry a MetadataEntry.
 */
void QMetadataModel::entryAdded(MetadataEntry *entry){
    _list->append(entry);
    emit( layoutChanged() );
}

/**
 * Updates the metadata model after removing a metadata entry.
 *
 * @brief QMetadataModelPrivate::entryRemoved Removes a metadata entry.
 * @param entry a MetadataEntry.
 */
void QMetadataModel::entryRemoved(MetadataEntry *entry){

    int pos = -1;

    for( int i=0; i< _list->size(); ++i )
    {
        if( (entry->attribute() == _list->at(i)->attribute()) &&
            (entry->value() == _list->at(i)->value()) &&
            (entry->unit() == _list->at(i)->unit())
           ) {
            pos = i;
            break;
        }
    }

    if(pos >= 0){
        _list->removeAt(pos);
    }

    emit( layoutChanged() );
}

/**
 * Confirms that the metadata has been received.
 *
 * @brief QMetadataModelPrivate::metaDataReceived Confirms that the metadata has been received.
 * @param list a list of MetadataEntry.
 */
void QMetadataModel::metaDataReceived(QList<MetadataEntry*>* list){
    _list = list;
    emit(layoutChanged());
}


/**
 * Sets data path.
 *
 * @brief QMetadataModel::setDataPath Sets data path.
 * @param dataObj a string that is the data object path.
 */
void QMetadataModel::setDataPath(QString &dataObj)
{
     Q_D(QMetadataModel);
    _dataPath = dataObj;
    d->getDataObjectMetadataAsync(_dataPath);
}

QMetadataModelPrivate *QMetadataModel::getPrivateInstance()
{
    return this->d_ptr;
}


/**
 * Returns the number of rows.
 *
 * @brief QMetadataModel::rowCount Returns the number of rows.
 * @param parent the parent.
 * @return returns the number of rows.
 */
int QMetadataModel::rowCount(const QModelIndex &parent) const{
    (void)parent;
    return this->_list->size();
}


/**
 * Returns the number of columns.
 *
 * @brief QMetadataModel::columnCount Returns the number of columns.
 * @param parent the parent.
 * @return returns the number of columns.
 */
int QMetadataModel::columnCount(const QModelIndex &parent) const{
    (void)parent;
    return 3;
}

/**
 * Returns the metadata atribute data.
 *
 * @brief QMetadataModel::data Returns the metadata atribute data.
 * @param index a QModelIndex.
 * @param role an integer.
 * @return returns returns the metadata information as a QVariant.
 */
QVariant QMetadataModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid() || this->_list->size() <= index.row())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
            case 0:{
                return QVariant(_list->at(index.row())->attribute());
            }
            case 1: return QVariant(_list->at(index.row())->value());
            case 2: return QVariant(_list->at(index.row())->unit());
            default:
                break;
        }
    }
    return QVariant();
}


/**
 * Creates an index.
 *
 * @brief QMetadataModel::index Creates an index.
 * @param row the row.
 * @param column the column
 * @param parent the parent.
 * @return returns a QModelIndex.
 */
QModelIndex	QMetadataModel::index(int row, int column, const QModelIndex & parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();


    MetadataEntry* entry = _list->at(row);

    return createIndex(row, column, entry);
}


/**
 * Returns the metadata header data as a QVariant.
 *
 * @brief QMetadataModel::headerData Returns the metadata header data
 * @param section an integer that represents the section.
 * @param orientation the horizontal and vertical orientation.
 * @param role an integer that is the role.
 * @return returns the metadata header data as a QVariant.
 */
QVariant QMetadataModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractItemModel::headerData(section, orientation, role);

    QString returnValue;
    switch (section) {
        case 0: returnValue = tr("Attribute");
            break;
        case 1: returnValue = tr("Value");
            break;
        case 2: returnValue = tr("Unit");
            break;
        default: return QVariant();
    }
    return returnValue;
}
