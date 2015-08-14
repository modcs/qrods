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


#include "filecontentsclient.h"
#include "callcontroller.h"
#include <QFile>
#include <QHttpMultiPart>
#include <QHttpPart>

/**
 * This is a constructor for FileContentsClient class.
 *
 * @brief FileContentsClient::FileContentsClient Constructor method.
 * @param bURL the base URL.
 * @param parent the parent Qt widget.
 */
FileContentsClient::FileContentsClient(QString &bURL, QString user, QString pass, QObject *parent) :
    AbstractHTTPClient(bURL, user, pass, parent)
{
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

/**
 * Uploads a file to the server.
 *
 * @brief FileContentsClient::uploadFile Uploads a file.
 * @param remotePath the path in the server.
 * @param localPath the local path.
 */
void FileContentsClient::uploadFile(QString &remotePath, QString &localPath){


    callController.waitForResource();

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uploadFile\""));
    QFile *file = new QFile(localPath);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(imagePart);

    QUrl url( baseURL() + remotePath );
    QNetworkRequest request(url);

    prepareRequest(request);

    QString str("multipart/form-data; boundary=");
    str.append(multiPart->boundary());

    QByteArray contentType = str.toUtf8();

    request.setRawHeader("content-type", contentType);

    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply); //delete the multiPart with the reply

    QVariant method("POST");
    reply->setProperty("method", method);
}

/**
 * Gets a file.
 *
 * @brief FileContentsClient::getFile Gets a file.
 * @param remotePath a string that is the destination path.
 * @param localPath a string that is the source path.
 */
void FileContentsClient::getFile(QString &remotePath, QString &localPath){
    if(remotePath.at(0) == '/')
    {
        remotePath = remotePath.mid(1, remotePath.length() -1);
    }

    QString url = baseURL() + remotePath;
    QNetworkReply *reply = doAsyncGet(url, "application/octet-stream");
    QVariant variant(localPath);
    QVariant method("GET");

    reply->setProperty("local-file-name", variant);
    reply->setProperty("method", method);
}

/**
 * Certifies that the reply has been received.
 *
 * @brief FileContentsClient::replyFinished Certifies that the reply has been received.
 * @param reply a QNetworkReply.
 */
void FileContentsClient::replyFinished(QNetworkReply *reply){
    QVariant v = reply->property("method");
    QString method = v.toString();

    if(method == "POST"){
        postFinished(reply);
    }else{
        getFinished(reply);
    }
}

/**
 * Finishes an operation.
 *
 * @brief FileContentsClient::getFinished Finishes an operation.
 * @param reply a QNetworkReply.
 */
void FileContentsClient::getFinished(QNetworkReply *reply){    
    if(!reply->error())
    {
        QVariant variant = reply->property("local-file-name");
        QString str = variant.toString();

        QFile *file = new QFile(str);

        if(file->open(QFile::Append)) {
            file->write(reply->readAll());
            file->flush(); file->close();
        }
    }
    reply->deleteLater();
}

/**
 * Finishes a POST operation.
 *
 * @brief FileContentsClient::postFinished Finishes a POST operation.
 * @param reply a QNetworkReply.
 */
void FileContentsClient::postFinished(QNetworkReply *reply){
    if(!reply->error()) {
        emit(modelChanged());
    }
    reply->deleteLater();    
}
