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


#include "abstracthttpclient.h"
#include <QUrl>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>

/**
 * This is a constructor for AbstractHTTPClient class.
 *
 * @brief AbstractHTTPClient::AbstractHTTPClient Constructor method.
 * @param bURL the base URL.
 * @param parent the parent.
 */
AbstractHTTPClient::AbstractHTTPClient(QString &bURL, QString user, QString pass, QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    _baseURL = bURL;
    _contentType = QString("application/json");
    _username = user;
    _password = pass;
}

/**
 * Returns the base URL.
 *
 * @brief AbstractHTTPClient::baseURL Returns the base URL.
 * @return the base URL.
 */
QString AbstractHTTPClient::baseURL(){
    return _baseURL;
}

/**
 * Sets user name.
 *
 * @brief AbstractHTTPClient::setUserName Sets user name.
 * @param str a string that represents the user name.
 */
void AbstractHTTPClient::setUserName(QString &str){
    _username = str;
}

/**
 * Sets the user password.
 *
 * @brief AbstractHTTPClient::setPassword Sets the password.
 * @param str a string that represents the user password.
 */
void AbstractHTTPClient::setPassword(QString &str){
    _password = str;
}


/**
 * Sets the MIME type for HTTP responses (e.g. application/xml).
 *
 * @brief AbstractHTTPClient::setContentType Sets the MIME type.
 * @param str a string that represents the MIME type.
 */
void AbstractHTTPClient::setContentType(QString &str){
    _contentType = str;
}

/**
 * Performs HTTP gets operation.
 *
 * @brief AbstractHTTPClient::doGet HTTP gets operation.
 * @param url a string that represents the URL
 * @return returns QByteArray.
 */
QByteArray AbstractHTTPClient::doGet(QString &url){
    QUrl _url(url);
    QNetworkRequest request( _url );

    prepareRequest(request);

    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));

    QNetworkReply *reply = manager->get( request );
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));

    timeoutTimer.start(2000);

    loop.exec();

    QByteArray arr = reply->readAll();

    return arr;
}

/**
 * Performs Put operations.
 *
 * @brief AbstractHTTPClient::doPut Put operation.
 * @param url a string that represents the HTTP put operation.
 * @param content a QByteArray.
 * @return returns a QByteArray.
 */
QByteArray AbstractHTTPClient::doPut(QString &url, QByteArray &content){
    return doHttpOperation(url, content, PUT);
}


/**
 * Performs Post operations.
 *
 * @brief AbstractHTTPClient::doPost Post operation.
 * @param url a string that represents the HTTP post operation.
 * @param content a QByteArray.
 * @return returns a QByteArray.
 */
QByteArray AbstractHTTPClient::doPost(QString &url, QByteArray &content){
    return doHttpOperation(url, content, POST);
}

/**
 * Performs a request with a do Delete operation.
 *
 * @brief AbstractHTTPClient::doDelete Delete operation
 * @param url a string that represents the do Delete operation
 * @return returns a QByteArray.
 */
QByteArray AbstractHTTPClient::doDelete(QString &url){
    QUrl _url(url);
    QNetworkRequest request( _url );

    prepareRequest(request);

    QNetworkReply *reply = manager->deleteResource(request);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));

    timeoutTimer.start(2000);

    loop.exec();

    QByteArray arr = reply->readAll();
    return arr;
}

/**
 * Performs a do asynchronous get operation.
 *
 * @brief AbstractHTTPClient::doAsyncGet Asynchronous get operation.
 * @param url a string that represents the do asynchronous get operation.
 * @return returns a QNetworkReply.
 */
QNetworkReply* AbstractHTTPClient::doAsyncGet(QString &url){
    return doAsyncGet(url, _contentType.toStdString().c_str());
}

/**
 * Performs a do asynchronous get operation.
 *
 * @brief AbstractHTTPClient::doAsyncGet Asynchronous get operation.
 * @param url a string that represents the do asynchronous get operation.
 * @param accept.
 * @return returns a QNetworkReply.
 */
QNetworkReply* AbstractHTTPClient::doAsyncGet(QString &url, const char* accept){
    QUrl _url(url);
    QNetworkRequest request( _url );

    prepareRequest(request);
    request.setRawHeader(QByteArray("accept"), QByteArray(accept));

    QNetworkReply *reply = manager->get( request );

    return reply;
}

/**
 * Method that prepares requests.
 *
 * @brief AbstractHTTPClient::prepareRequest Prepares Requests.
 * @param request a QNetworkRequest.
 */
void AbstractHTTPClient::prepareRequest(QNetworkRequest &request){
    QString concatenated = _username + ":" + _password;
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());
    request.setRawHeader(QByteArray("accept"), QByteArray(_contentType.toStdString().c_str()));
}


QByteArray AbstractHTTPClient::doHttpOperation(QString &url, QByteArray &content, HTTPOperation op){
    QUrl _url(url);
    QNetworkRequest request( _url );

    prepareRequest(request);
    request.setRawHeader("content-type", _contentType.toStdString().c_str());

    QNetworkReply *reply = NULL;

    switch(op){
    case POST:
        reply = manager->post(request,content);
        break;
    case PUT:
        reply = manager->put(request,content);
        break;
    }

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));

    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));

    timeoutTimer.start(2000);

    loop.exec();

    if(reply->error() != QNetworkReply::NoError){
        return QByteArray();
    }

    QByteArray arr = reply->readAll();

    return arr;
}
