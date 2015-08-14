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


#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>
#include <QList>
#include <QStringListModel>
#include "qrods.h"

namespace Ui {
class MetadataDialog;
}

class MetadataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MetadataDialog(QString &path, QRODS* model, QWidget *parent = 0);
    ~MetadataDialog();
    void setContents(QList<MetadataEntry*>*);

private slots:
    void on_addMetadataBtn_clicked();

    void on_removeMetadataBtn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MetadataDialog *ui;
    QStringListModel* model;
    QRODS* qrsm;
    QString path;
    MetadataEntry* entry = NULL;
};

#endif // METADATADIALOG_H
