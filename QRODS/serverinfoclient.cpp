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


#include "serverinfoclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QTimer>

/**
 * This is a constructor for ServerInfoClient class.
 *
 * @brief ServerInfoClient::ServerInfoClient Constructor method.
 * @param bURL the base URL.
 * @param parent the parent.
 */
ServerInfoClient::ServerInfoClient(QString &bURL, QString user, QString pass, QObject *parent) :
    AbstractHTTPClient(bURL, user, pass, parent)
{    
}

/**
 * Loads Server information.
 *
 * @brief ServerInfoClient::loadServerInfo
 */
bool ServerInfoClient::loadServerInfo(){
    QString url = baseURL();

    QUrl _url(url);
    QNetworkRequest request( _url );

    prepareRequest(request);
    request.setRawHeader(QByteArray("accept"), QByteArray("application/json"));

    QEventLoop loop;

    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));

    //REST request
    QNetworkReply *reply = manager->get( request );
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));

    //Wait 2000 miliseconds
    timeoutTimer.start(2000);

    loop.exec();

    if(reply->bytesAvailable() == 0)
    {        
        return false;
    }

    QByteArray arr = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(arr);
    QJsonObject jsonObject = jsonResponse.object();

    _initializeDate = jsonObject["initializeDate"].toString().toLongLong();
    _serverBootTime = jsonObject["serverBootTime"].toString().toLongLong();
    _currentServerTime = jsonObject["currentServerTime"].toString().toLongLong();
    _icatEnabled = jsonObject["icatEnabled"].toString();
    _relVersion =  jsonObject["relVersion"].toString();
    _apiVersion =  jsonObject["apiVersion"].toString();
    _rodsZone =  jsonObject["rodsZone"].toString();

    return true;

}

/**
 * Returns initializeDate.
 *
 * @brief ServerInfoClient::initializeDate Returns initializeDate.
 * @return returns initializeDate.
 */
long long int  ServerInfoClient::initializeDate() const{
    return _initializeDate;
}

/**
 * Gets icatEnabled.
 *
 * @brief ServerInfoClient::icatEnabled Gets icatEnabled.
 * @return returns icatEnabled.
 */
const QString& ServerInfoClient::icatEnabled() const{
    return _icatEnabled;
}

/**
 * Gets server boot time.
 *
 * @brief ServerInfoClient::serverBootTime Gets server boot time.
 * @return returns serverBootTime
 */
long long int  ServerInfoClient::serverBootTime() const{
    return _serverBootTime;
}

/**
 * Gets iRODS version.
 *
 * @brief ServerInfoClient::relVersion Gets iRODS version.
 * @return returns iRODS version.
 */
const QString& ServerInfoClient::relVersion() const{
    return _relVersion;
}

/**
 * Gets API version.
 *
 * @brief ServerInfoClient::apiVersion Gets API version.
 * @return returns API version.
 */
const QString& ServerInfoClient::apiVersion() const{
    return _apiVersion;
}

/**
 * Gets iRODS zone.
 *
 * @brief ServerInfoClient::rodsZone Gets iRODS zone.
 * @return returns iRODS zone.
 */
const QString& ServerInfoClient::rodsZone() const{
    return _rodsZone;
}

/**
 * Gets current server time.
 *
 * @brief ServerInfoClient::currentServerTime Gets current server time.
 * @return returns current server time.
 */
long long int  ServerInfoClient::currentServerTime() const{
    return _currentServerTime;
}
