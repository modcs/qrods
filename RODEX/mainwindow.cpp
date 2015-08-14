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


#include "mainwindow.h"
#include "metadataentry.h"
#include "ui_mainwindow.h"
#include "metadatadialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTreeView>
#include <QListView>
#include <QStringListModel>
#include <QModelIndexList>
#include <QString>
#include <QFileDialog>
#include <QSettings>
#include <QHeaderView>
#include <QInputDialog>

/**
 * Loads the credentials.
 *
 * @brief MainWindow::loadCredentials Loads the credentials.
 * @param credentials the credential to be loaded.
 * @return returns a boolean.
 */
void MainWindow::loadCredentials(Credentials *credentials)
{
    QString deployRootPath = QDir::cleanPath(QDir::currentPath()+QString::fromStdString("/../RODEX/"));
    QSettings settings(QString(deployRootPath + "/config.ini"), QSettings::IniFormat);

    credentials->host = settings.value("config/irods/host", "Host not properly specified.").toString();
    credentials->port = settings.value("config/irods/port", "Port not properly specified.").toString().toInt();
    credentials->user = settings.value("config/irods/user", "User not properly specified.").toString();
    credentials->path = settings.value("config/irods/path", "Path not properly specified.").toString();

    bool ok;
    QString text = QInputDialog::getText(this, tr("Password"),
                                            tr("Insert Password:"), QLineEdit::Password,
                                            tr("rods"), &ok);
    if (ok && !text.isEmpty())
    {
       credentials->password = text; 
    }    

    QString boolean(settings.value("config/irods/secureHttp", "Http mode not properly specified.").toString());
    credentials->isAdoptingHTTPs = QString::compare(boolean,"false") == 0 ? false : true ;
    credentials->user = settings.value("config/irods/user", "User not properly specified.").toString();    
}

/**
 * This is the constructor for MainWindow class
 *
 * @brief MainWindow::MainWindow The constructor.
 * @param parent the QWidget parent.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    Credentials credentials;
    this->loadCredentials(&credentials);

    model = new QRODS(this);
    model->setUser(credentials.user);

    ui->setupUi(this);

    //connect( model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChanged(QModelIndex,QModelIndex)));

    model->setHost(credentials.host);
    model->setPort(credentials.port);
    model->setPassword(credentials.password);

    if(model->connectToServer(credentials.path, credentials.isAdoptingHTTPs)){
        ui->tableView->setModel(model);
        ui->listView->setModel(model);
        ui->treeView->setModel(model);

        ui->metaDataView->setModel(model->getDataModel()); //this data model must come from QRODS. e.g., qRODS->getDataModel();

        model->addView(ui->treeView);

        QList<FileListingEntry::EntryColumn> visibleColumns;

        visibleColumns << FileListingEntry::PATH_OR_NAME << FileListingEntry::PARENT_PATH <<  FileListingEntry::DATA_SIZE << FileListingEntry::MODIFIED_AT;

        model->setVisibleColumns(visibleColumns);

        connect(model, SIGNAL(layoutChanged()), this, SLOT(layoutChanged()));
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setText("Server not found. Check the server configuration file and try again");
        messageBox.exec();
    }
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Adds a collection.
 *
 * @brief MainWindow::on_addCollectionBtn_clicked Adds a collection.
 */
void MainWindow::on_addCollectionBtn_clicked()
{
    QString str = ui->lineEdit->text();

    model->addCollection(str);
}

/**
 * Deletes a collection.
 *
 * @brief MainWindow::on_deleteCollectionBtn_clicked Deletes a collection.
 */
void MainWindow::on_deleteCollectionBtn_clicked()
{
    QString collectionName = ui->lineEdit->text();

    if(!collectionName.isEmpty())
    {
        model->removeCollection(collectionName);
    }
    else
    {
        FileListingEntry* entry;

        if(ui->tabWidget->currentIndex() == 0)
        {
            entry = static_cast<FileListingEntry *>
                    (ui->listView->selectionModel()->selectedIndexes().at(0).internalPointer());
        }
        else if(ui->tabWidget->currentIndex() == 1)
        {
            entry = static_cast<FileListingEntry *>
                    (ui->tableView->selectionModel()->selectedIndexes().at(0).internalPointer());
        }
        else
        {
            entry = static_cast<FileListingEntry *>
                    (ui->treeView->selectionModel()->selectedIndexes().at(0).internalPointer());
        }

        if(entry->isCollection()){
            QString remotePath;
            remotePath.append(entry->pathOrName());

            model->removeCollection(remotePath);
        }
    }
}

/**
 * Downloads a file.
 *
 * @brief MainWindow::on_downloadButton_clicked Downloads a file.
 */
void MainWindow::on_downloadButton_clicked()
{
    QString localPath = ui->localPathEdt->text();
    FileListingEntry* entry;

    if(ui->tabWidget->currentIndex() == 0)
    {
        entry = static_cast<FileListingEntry *>
                (ui->listView->selectionModel()->selectedIndexes().at(0).internalPointer());
    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
        entry = static_cast<FileListingEntry *>
                (ui->tableView->selectionModel()->selectedIndexes().at(0).internalPointer());
    }
    else
    {
        entry = static_cast<FileListingEntry *>
                (ui->treeView->selectionModel()->selectedIndexes().at(0).internalPointer());
    }

    if(!entry->isCollection()){

        QString remotePath;
        remotePath.append(entry->parentPath())
                .append("/")
                .append(entry->pathOrName());

        model->getFile(remotePath, localPath);

        QMessageBox messageBox;
        messageBox.setText("File " + entry->pathOrName() + "\n downloaded to " + localPath);
        messageBox.exec();
    }
}

/**
 * Selects a file.
 *
 * @brief MainWindow::on_selectFileBtn_clicked Selects a file.
 */
void MainWindow::on_selectFileBtn_clicked()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Open file..."),
                                              QString(), tr("All Files (*)"));

    ui->localPathEdt->setText(fn);
}

/**
 * Uploads a file.
 *
 * @brief MainWindow::on_uploadBtn_clicked Uploads a file.
 */
void MainWindow::on_uploadBtn_clicked()
{
    QString localPath = ui->localPathEdt->text();
    QString remotePath = ui->remotePathEdt->text();

    model->uploadFile(remotePath, localPath);    
}

/**
 * Opens the metadata dialog for the selected file.
 *
 * @brief MainWindow::on_listView_doubleClicked Opens the metadata dialog.
 * @param index
 */
void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    (void)index;
    FileListingEntry* entry = static_cast<FileListingEntry *>
                (ui->listView->selectionModel()->selectedIndexes().at(0).internalPointer());

    QString path;

    if(!entry->isCollection()){
        path.append(entry->parentPath())
                .append("/")
                .append(entry->pathOrName());
    }else{
        path.append(entry->pathOrName());
    }


    QList<MetadataEntry*>* result = model->getDataObjectMetadata(path);


    MetadataDialog* dlg = new MetadataDialog(path, this->model, this);
    dlg->setContents(result);
    dlg->show();

}

/**
 * Deletes a file.
 *
 * @brief MainWindow::on_deleteBtn_clicked Deletes a file.
 */
void MainWindow::on_deleteBtn_clicked()
{
    FileListingEntry* entry = NULL;

    if(ui->tabWidget->currentIndex() == 0)
    {
        if(ui->listView->selectionModel()->selectedIndexes().size() > 0)
        {
            entry = static_cast<FileListingEntry *>
                    (ui->listView->selectionModel()->selectedIndexes().at(0).internalPointer());
        }
    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
        if(ui->tableView->selectionModel()->selectedIndexes().size() > 0)
        {
            entry = static_cast<FileListingEntry *>
                (ui->tableView->selectionModel()->selectedIndexes().at(0).internalPointer());
        }
    }
    else
    {
        if(ui->treeView->selectionModel()->selectedIndexes().size() > 0)
        {
            entry = static_cast<FileListingEntry *>
                        (ui->treeView->selectionModel()->selectedIndexes().at(0).internalPointer());
        }

    }

    if(entry != NULL && !entry->isCollection()){
        QString remotePath;

        remotePath.append(entry->parentPath())
                .append("/")
                .append(entry->pathOrName());

        QString adjustedPath = remotePath.mid(1, remotePath.length() -1);

        model->removeDataObject(adjustedPath,false);
    }
    else{
        QMessageBox messageBox;
        messageBox.setText("Select a file");
        messageBox.exec();
    }
}

/**
 * Updates the QRODS model.
 *
 * @brief MainWindow::on_nextPageBtn_clicked
 */
void MainWindow::on_nextPageBtn_clicked()
{
    model->modelChanged();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    (void)index;    
}

/**
 * Shows the table view.
 *
 * @brief MainWindow::on_tableView_clicked Shows the table view.
 * @param index
 */
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    FileListingEntry* entry = static_cast<FileListingEntry *>( index.internalPointer() );

    QString path;

    if(!entry->isCollection()){
        path.append(entry->parentPath())
                .append("/")
                .append(entry->pathOrName());
    }else{
        path.append(entry->pathOrName());
    }

    model->setDataPath(path);
}

/**
 * Updates the table view and tree view according to the column contents.
 *
 * @brief MainWindow::layoutChanged
 */
void MainWindow::layoutChanged(){
    ui->tableView->resizeColumnsToContents();

    ui->treeView->resizeColumnToContents(0);
    ui->treeView->resizeColumnToContents(1);
    ui->treeView->resizeColumnToContents(2);
    ui->treeView->resizeColumnToContents(3);
}
