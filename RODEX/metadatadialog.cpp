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


#include "metadatadialog.h"
#include "ui_metadatadialog.h"
#include <QStringList>

/**
 * This is a constructor for MetadataDialog class.
 *
 * @brief MetadataDialog::MetadataDialog the Constructor.
 * @param path the metadata path.
 * @param qrsm a pointer to QRODS instance.
 * @param parent the QWidget parent.
 */
MetadataDialog::MetadataDialog(QString& path, QRODS *qrsm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MetadataDialog),
    qrsm(qrsm),
    path(path)
{
    ui->setupUi(this);   
    model = new QStringListModel(this);

    ui->tableView->setModel(qrsm->getDataModel());

    qrsm->setDataPath(path);
}

/**
 * @brief MetadataDialog::~MetadataDialog
 */
MetadataDialog::~MetadataDialog()
{
    delete ui;
}

/**
 * Sets the content to be shown.
 *
 * @brief MetadataDialog::setContents Sets the content.
 * @param contents a List of metadata entries.
 */
void MetadataDialog::setContents(QList<MetadataEntry*>* contents){
    QStringList* list = new QStringList();

    QString header("Value \t data \t unit");
    QString sep("__________________________________");

    list->append(header);
    list->append(sep);

    for(int i = 0; i < contents->length(); i++){
        MetadataEntry* entry = contents->at(i);
        QString str;
        str.append(entry->attribute()).append(" \t ").append(entry->value())
                .append(" \t ").append(entry->unit());

        list->append(str);
    }

    model->setStringList(*list);
}

/**
 * Adds a metadata entry.
 *
 * @brief MetadataDialog::on_addMetadataBtn_clicked Adds a metadata.
 */
void MetadataDialog::on_addMetadataBtn_clicked()
{
    QString attribute = ui->attributeEdt->text();
    QString value = ui->valueEdt->text();
    QString unit = ui->unitEdt->text();

    MetadataEntry entry(attribute, value, unit);

    qrsm->addCollectionMetadata(path, entry);
}

/**
 * Removes the selected metadata entry.
 *
 * @brief MetadataDialog::on_removeMetadataBtn_clicked Removes a metadata entry.
 */
void MetadataDialog::on_removeMetadataBtn_clicked()
{
    if(entry){
        QString attribute = entry->attribute();
        QString value = entry->value();
        QString unit = entry->unit();       

        MetadataEntry entry(attribute, value, unit);

        qrsm->deleteCollectionMetadata(path, entry);
    }
}

/**
 * An event that sets the MetadataEntry for the table view.
 *
 * @brief MetadataDialog::on_tableView_clicked sets the MetadataEntry for the table view.
 * @param index a QModelIndex.
 */
void MetadataDialog::on_tableView_clicked(const QModelIndex &index)
{
    if(index.internalPointer()){
        entry = static_cast<MetadataEntry *>( index.internalPointer() );
    }
}
